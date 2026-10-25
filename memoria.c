#include <stdio.h>
#include <string.h>     
#include "memoria.h"
#include <stdlib.h>
 

/* Arma un entero de 2 bytes a partir de 2 bytes en big endian. */
static uint16_t leer16(const uint8_t *b){
    return (uint16_t)((b[0] << 8) | b[1]);
}

/* Lee y valida la cabecera del .vmx (version 1 o 2). */
vm_error_t leerCabecera(FILE *arch, Cabecera *cab){
    uint8_t buf[TAM_CABECERA_V2];

    if (fread(buf, 1, 6, arch) != 6 || memcmp(buf, "VMX26", 5) != 0)
        return ERR_CABECERA;

    memset(cab, 0, sizeof(*cab));
    cab->version = buf[5];

    if (cab->version == 1) {
        if (fread(buf + 6, 1, TAM_CABECERA_V1 - 6, arch) != TAM_CABECERA_V1 - 6)
            return ERR_CABECERA;
        cab->tamCode = leer16(buf + 6);
    }
    else if (cab->version == 2) {
        if (fread(buf + 6, 1, TAM_CABECERA_V2 - 6, arch) != TAM_CABECERA_V2 - 6)
            return ERR_CABECERA;
        cab->tamCode    = leer16(buf + 6);
        cab->tamData    = leer16(buf + 8);
        cab->tamExtra   = leer16(buf + 10);
        cab->tamStack   = leer16(buf + 12);
        cab->tamConst   = leer16(buf + 14);
        cab->entryPoint = leer16(buf + 16);
    }
    else
        return ERR_VERSION;

    return OK;
}

/* Si el segmento tiene tamaño > 0, lo agrega en la siguiente entrada libre de la tabla,
 * a partir de la direccion fisica 'base', y deja su registro apuntando al comienzo.
 * Si su tamaño es 0, no crea entrada y el registro queda en -1. */
static void agregarSegmento(MV *mv, int *entrada, uint32_t *base, uint16_t tam, int regSeg){
    if (tam == 0) {
        mv->reg[regSeg] = SEG_NULO;
        return;
    }
    mv->tabla[*entrada].base    = (uint16_t)*base;
    mv->tabla[*entrada].tamanio = tam;
    mv->reg[regSeg] = (uint32_t)*entrada << 16;   /* entrada en los 16 bits altos, offset 0 */

    *base += tam;
    (*entrada)++;
}

/* Arma la tabla de segmentos en el orden Param, Const, Code, Data, Extra, Stack
 * (solo los de tamaño > 0) y carga los registros de segmento. */
vm_error_t armarSegmentos(MV *mv, const Cabecera *cab, uint16_t tamParam){
    uint32_t total = (uint32_t)tamParam + cab->tamConst + cab->tamCode
                   + cab->tamData + cab->tamExtra + cab->tamStack;
    int entrada = 0;
    uint32_t base = 0;

    if (total > mv->tamMem)
        return ERR_MEMORIA;

    memset(mv->reg, 0, sizeof(mv->reg));
    memset(mv->tabla, 0, sizeof(mv->tabla));      /* entradas sin usar: base 0, tamaño 0 */

    agregarSegmento(mv, &entrada, &base, tamParam,      PS);
    agregarSegmento(mv, &entrada, &base, cab->tamConst, KS);
    agregarSegmento(mv, &entrada, &base, cab->tamCode,  CS);
    agregarSegmento(mv, &entrada, &base, cab->tamData,  DS);
    agregarSegmento(mv, &entrada, &base, cab->tamExtra, ES);
    agregarSegmento(mv, &entrada, &base, cab->tamStack, SS);
    return OK;
}

/* Devuelve la direccion fisica donde empieza el segmento apuntado por un registro de segmento. */
static uint16_t baseSegmento(MV *mv, int regSeg){
    return mv->tabla[mv->reg[regSeg] >> 16].base;
}

/* Escribe un entero de 2 o 4 bytes en big endian. */
static void escribir16(uint8_t *b, uint16_t v){
    b[0] = (uint8_t)(v >> 8);
    b[1] = (uint8_t)v;
}

static void escribir32(uint8_t *b, uint32_t v){
    b[0] = (uint8_t)(v >> 24);
    b[1] = (uint8_t)(v >> 16);
    b[2] = (uint8_t)(v >> 8);
    b[3] = (uint8_t)v;
}

/* Guarda el estado de la MV en un archivo .vmi:
 * header (8 bytes) + 32 registros (4 bytes c/u) + tabla de segmentos (8 x 4 bytes) + memoria. */
vm_error_t guardarImagen(MV *mv, const char *ruta){
    FILE *arch = fopen(ruta, "wb");
    uint8_t buf[8];

    if (arch == NULL)
        return ERR_ARCHIVO;

    /* header: "VMI26", version 1, tamaño de la memoria en KiB */
    memcpy(buf, "VMI26", 5);
    buf[5] = 1;
    escribir16(buf + 6, (uint16_t)(mv->tamMem / 1024));
    fwrite(buf, 1, 8, arch);

    /* registros */
    for (int i = 0; i < CANTREG; i++) {
        escribir32(buf, mv->reg[i]);
        fwrite(buf, 1, 4, arch);
    }

    /* tabla de segmentos: base y tamaño, 2 bytes cada uno */
    for (int i = 0; i < SEG_TABLE; i++) {
        escribir16(buf, mv->tabla[i].base);
        escribir16(buf + 2, mv->tabla[i].tamanio);
        fwrite(buf, 1, 4, arch);
    }

    /* memoria principal completa */
    fwrite(mv->mem, 1, mv->tamMem, arch);

    fclose(arch);
    return OK;
}
 
vm_error_t cargarPrograma(MV *mv, const char *ruta){
    FILE *arch;
    Cabecera cab;
    vm_error_t err;

    arch = fopen(ruta, "rb");
    if (arch == NULL)
        return ERR_ARCHIVO;

    err = leerCabecera(arch, &cab);
    if (err != OK  ) {
        fclose(arch);
        return err;
    }
    /* version 1: como en la Parte I, el Data Segment ocupa el resto de la memoria */
    if (cab.version == 1) {
        uint32_t resto = (cab.tamCode < mv->tamMem) ? mv->tamMem - cab.tamCode : 0;
        cab.tamData = (resto > 0xFFFF) ? 0xFFFF : (uint16_t)resto;
    }

    err = armarSegmentos(mv, &cab, 0);   /* Param Segment: todavia sin -p */
    if (err != OK) {
        fclose(arch);
        return err;
    }

    /* despues de la cabecera viene el codigo y a continuacion las constantes */
    if (fread(mv->mem + baseSegmento(mv, CS), 1, cab.tamCode, arch) != cab.tamCode
        || (cab.tamConst > 0
            && fread(mv->mem + baseSegmento(mv, KS), 1, cab.tamConst, arch) != cab.tamConst)) {
        fclose(arch);
        return ERR_TAMANIO;
    }
    fclose(arch);

    /* IP: entrada del Code Segment en los 16 bits altos, entry point en los bajos */
    mv->reg[IP] = mv->reg[CS] | cab.entryPoint;

    /* SP: pila vacia, apunta justo despues del final del Stack Segment */
    if (mv->reg[SS] != SEG_NULO)
        mv->reg[SP] = mv->reg[SS] + cab.tamStack;

    return OK;
}

int ipEnSegmentoDeCodigo(MV *mv){
    uint16_t seg = (uint16_t)(mv->reg[IP] >> 16);
    uint16_t off = (uint16_t)(mv->reg[IP] & 0xFFFF);

    if (seg != (uint16_t)(mv->reg[CS] >> 16))
        return 0;

    return off < mv->tabla[seg].tamanio;
}

void informarError(int codigo){
    switch (codigo) {
        case ERR_ARCHIVO:
            printf("Error: no se pudo abrir el archivo.\n");
            break;
        case ERR_CABECERA:
            printf("Error: el archivo no es un ejecutable valido.\n");
            break;
        case ERR_VERSION:
            printf("Error: version de la maquina virtual no soportada.\n");
            break;
        case ERR_TAMANIO:
            printf("Error: el codigo no entra en la memoria principal.\n");
            break;
        case ERR_INSTRUCCION:
            printf("Error: instruccion invalida.\n");
            break;
        case ERR_DIV_CERO:
            printf("Error: division por cero.\n");
            break;
        case ERR_SEGMENTO:
            printf("Error: fallo de segmento.\n");
            break;
        case ERR_MEMORIA:
            printf("Error: memoria insuficiente.\n");
            break;
        case ERR_STACK_OVF:
            printf("Error: stack overflow.\n");
            break;
        case ERR_STACK_UNF:
            printf("Error: stack underflow.\n");
            break;
        default:
            printf("Error desconocido.\n");
            break;
    }
}

void mostrarUso(void){
    printf("Uso: vmx [filename.vmx] [filename.vmi] [m=M] [-d] [-p param1 ... paramN]\n");
    printf("  filename.vmx  programa en lenguaje maquina\n");
    printf("  filename.vmi  archivo de imagen de la maquina virtual\n");
    printf("  m=M           tamanio de la memoria principal en KiB (por defecto %d)\n", MEM_SIZE_KIB);
    printf("  -d            muestra el codigo desensamblado\n");
    printf("  -p            parametros para la subrutina principal (siempre al final)\n");
    printf("Es obligatorio indicar al menos un .vmx o un .vmi\n");
}

// ACCESO A MEMORIA

/* -Traduce una dirección lógica (segmento + offset) a dirección física,
 -verificando que el acceso de 'cantBytes' entre dentro del segmento.
 - Devuelve ERR_SEGMENTO si el segmento no existe o el acceso se pasa. */

int traducirDireccion(MV *mv, uint32_t dirLogica, int cantBytes, uint16_t *dirFisica){
    uint16_t seg = (uint16_t)(dirLogica >> 16);
    uint16_t off = (uint16_t)(dirLogica & 0xFFFF);

    if (seg >= SEG_TABLE || mv->tabla[seg].tamanio == 0)
        return ERR_SEGMENTO;

    if (off + cantBytes > mv->tabla[seg].tamanio)
        return ERR_SEGMENTO;

    *dirFisica = mv->tabla[seg].base + off;
    return OK;
}

/* Lee 'cantBytes' de memoria desde una dirección lógica (big-endian).
 * Carga LAR, MAR y MBR como pide el enunciado. ?? consultar*/
int leerMemoria(MV *mv, uint32_t dirLogica, int cantBytes, int32_t *valor){
    uint16_t dirFisica;
    uint32_t v = 0;                    /* sin signo: los corrimientos son seguros */
    int err = traducirDireccion(mv, dirLogica, cantBytes, &dirFisica);

    if (err != OK)
        return err;

    mv->reg[LAR] = dirLogica;
    mv->reg[MAR] = ((uint32_t)cantBytes << 16) | dirFisica;

    for (int i = 0; i < cantBytes; i++)
        v = (v << 8) | mv->mem[dirFisica + i];

    mv->reg[MBR] = v;
    *valor = (int32_t)v;
    return OK;
}

/* Escribe 'cantBytes' en memoria desde una dirección lógica .
 * Carga LAR, MAR y MBR como pide el enunciado. ??? consultar */
int escribirMemoria(MV *mv, uint32_t dirLogica, int cantBytes, int32_t valor){
    uint16_t dirFisica;
    uint32_t v;
    int err = traducirDireccion(mv, dirLogica, cantBytes, &dirFisica);

    if (err != OK)
        return err;

    mv->reg[LAR] = dirLogica;
    mv->reg[MAR] = ((uint32_t)cantBytes << 16) | dirFisica;
    mv->reg[MBR] = (uint32_t)valor;

    v = (uint32_t)valor;
    for (int i = 0; i < cantBytes; i++)
        mv->mem[dirFisica + i] = (uint8_t)(v >> (8 * (cantBytes - 1 - i)));

    return OK;
}

/* Crea la memoria principal de 'kib' KiB, inicializada en cero. */
vm_error_t crearMemoria(MV *mv, uint32_t kib){
    mv->tamMem = kib * 1024;
    mv->mem = (uint8_t *)calloc(mv->tamMem, 1);
    if (mv->mem == NULL)
        return ERR_MEMORIA;
    return OK;
}

/* Libera la memoria principal. */
void liberarMemoria(MV *mv){
    free(mv->mem);
    mv->mem = NULL;
    mv->tamMem = 0;
}