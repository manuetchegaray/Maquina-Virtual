#include <stdio.h>
#include <string.h>
#include "memoria.h"
 
void inicializarMV(MV *mv, uint16_t tamCodigo)
{
    // 1. Limpiar memoria física y registros a cero
    memset(mv->reg, 0, sizeof(mv->reg));

    // 2. Configurar Segmento de Código (empieza en 0)
    mv->tabla[SEG_CODIGO].base    = 0;
    mv->tabla[SEG_CODIGO].tamanio = tamCodigo;

    // 3. Configurar Segmento de Datos (empieza justo después del código)
    mv->tabla[SEG_DATOS].base     = tamCodigo;
    mv->tabla[SEG_DATOS].tamanio  = (uint16_t)(MEMORY_SIZE - tamCodigo);

    // 4. Invalidar el resto de la tabla de segmentos
    for (int i = 2; i < SEG_TABLE; i++) {
        mv->tabla[i].base    = 0xFFFF;
        mv->tabla[i].tamanio = 0xFFFF;
    }

    // 5. Cargar registros de segmento y puntero de instrucción
    mv->reg[CS] = ((uint32_t)SEG_CODIGO << 16);   /* 0x00000000 */
    mv->reg[DS] = ((uint32_t)SEG_DATOS  << 16);   /* 0x00010000 */
    mv->reg[IP] = mv->reg[CS];                    /* IP arranca en CS */
}
 
vm_error_t cargarPrograma(MV *mv, const char *ruta, uint16_t *tamCodigo)
{
    FILE *arch;
    uint8_t cabecera[TAM_CABECERA];
    uint16_t tam;

    arch = fopen(ruta, "rb");
    if (arch == NULL)
        return ERR_ARCHIVO;

    if (fread(cabecera, 1, TAM_CABECERA, arch) != TAM_CABECERA) {
        fclose(arch);
        return ERR_CABECERA;
    }

    if (memcmp(cabecera, "VMX26", 5) != 0) {
        fclose(arch);
        return ERR_CABECERA;
    }

    if (cabecera[5] != VERSION_MV) {
        fclose(arch);
        return ERR_VERSION;
    }

    tam = (uint16_t)((cabecera[6] << 8) | cabecera[7]);

    if (tam > MEMORY_SIZE) {
        fclose(arch);
        return ERR_TAMANIO;
    }

    memset(mv->mem, 0, MEMORY_SIZE);


    /* el segmento de codigo arranca al comienzo de la memoria */
    if (fread(mv->mem, 1, tam, arch) != tam) {
        fclose(arch);
        return ERR_TAMANIO;
    }

    fclose(arch);
    *tamCodigo = tam;
    return OK;
}

int ipEnSegmentoDeCodigo(MV *mv)
{
    uint16_t seg = (uint16_t)(mv->reg[IP] >> 16);
    uint16_t off = (uint16_t)(mv->reg[IP] & 0xFFFF);

    if (seg != SEG_CODIGO)
        return 0;

    return off < mv->tabla[SEG_CODIGO].tamanio;
}

void informarError(int codigo)
{
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
        default:
            printf("Error desconocido.\n");
            break;
    }
}

void mostrarUso(void)
{
    printf("Uso: vmx filename.vmx [-d]\n");
    printf("  filename.vmx  programa en lenguaje maquina\n");
    printf("  -d            muestra el codigo desensamblado\n");
}

int ejecutarInstruccion(MV *mv)
{
    (void)mv;
    printf("ejecutarInstruccion() todavia no esta implementada.\n");
    return ERR_INSTRUCCION;
}

void disassembler(MV *mv)
{
    (void)mv;
    printf("disassembler() todavia no esta implementado.\n");
}
