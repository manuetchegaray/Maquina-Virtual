#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memoria.h"
//Carga la tabla de instrucciones: para cada código de operación
//Los códigos que no existen quedan con func = NULL

void init_funciones(MV *mv){
    memset(mv->FUNCIONES, 0, sizeof(mv->FUNCIONES));
    
    strcpy(mv->FUNCIONES[MOV].nombre, "MOV");
    mv->FUNCIONES[MOV].func = mov;
    strcpy(mv->FUNCIONES[ADD].nombre, "ADD");
    mv->FUNCIONES[ADD].func = add;
    strcpy(mv->FUNCIONES[SUB].nombre, "SUB");
    mv->FUNCIONES[SUB].func = sub;
    strcpy(mv->FUNCIONES[MUL].nombre, "MUL");
    mv->FUNCIONES[MUL].func = mul;
    strcpy(mv->FUNCIONES[DIV_].nombre, "DIV");
    mv->FUNCIONES[DIV_].func = div_;
    strcpy(mv->FUNCIONES[CMP].nombre, "CMP");
    mv->FUNCIONES[CMP].func = cmp;
    strcpy(mv->FUNCIONES[AND].nombre, "AND");
    mv->FUNCIONES[AND].func = and;
    strcpy(mv->FUNCIONES[OR].nombre, "OR");
    mv->FUNCIONES[OR].func = or;
    strcpy(mv->FUNCIONES[XOR].nombre, "XOR");
    mv->FUNCIONES[XOR].func = xor;
    strcpy(mv->FUNCIONES[SWAP].nombre, "SWAP");
    mv->FUNCIONES[SWAP].func = swap;
    strcpy(mv->FUNCIONES[SHL].nombre, "SHL");
    mv->FUNCIONES[SHL].func = shl;
    strcpy(mv->FUNCIONES[SHR].nombre, "SHR");
    mv->FUNCIONES[SHR].func = shr;
    strcpy(mv->FUNCIONES[SAR].nombre, "SAR");
    mv->FUNCIONES[SAR].func = sar;
    strcpy(mv->FUNCIONES[LDL].nombre, "LDL");
    mv->FUNCIONES[LDL].func = ldl;
    strcpy(mv->FUNCIONES[LDH].nombre, "LDH");
    mv->FUNCIONES[LDH].func = ldh;
    strcpy(mv->FUNCIONES[RND].nombre, "RND");
    mv->FUNCIONES[RND].func = rnd;


    strcpy(mv->FUNCIONES[SYS].nombre, "SYS");
    mv->FUNCIONES[SYS].func = sys;
    strcpy(mv->FUNCIONES[JMP].nombre, "JMP");
    mv->FUNCIONES[JMP].func = jmp;
    strcpy(mv->FUNCIONES[JP].nombre, "JP");
    mv->FUNCIONES[JP].func = jp;
    strcpy(mv->FUNCIONES[JN_].nombre, "JN");
    mv->FUNCIONES[JN_].func = jn_;
    strcpy(mv->FUNCIONES[JZ].nombre, "JZ");
    mv->FUNCIONES[JZ].func = jz;
    strcpy(mv->FUNCIONES[JC].nombre, "JC");
    mv->FUNCIONES[JC].func = jc;
    strcpy(mv->FUNCIONES[JV].nombre, "JV");
    mv->FUNCIONES[JV].func = jv;
    strcpy(mv->FUNCIONES[JNP].nombre, "JNP");
    mv->FUNCIONES[JNP].func = jnp;
    strcpy(mv->FUNCIONES[JNZ].nombre, "JNZ");
    mv->FUNCIONES[JNZ].func = jnz;
    strcpy(mv->FUNCIONES[JNN].nombre, "JNN");
    mv->FUNCIONES[JNN].func = jnn;
    strcpy(mv->FUNCIONES[NOT].nombre, "NOT");
    mv->FUNCIONES[NOT].func = not;

    strcpy(mv->FUNCIONES[STOP].nombre, "STOP");
    mv->FUNCIONES[STOP].func = stop;
}

//Devuelve el nombre de un registro a partir de su código (0..31).

static const char *NOMBRE_REG[CANTREG] = {
    [IP]  = "IP",  [OPC] = "OPC", [OP1] = "OP1", [OP2] = "OP2",
    [LAR] = "LAR", [MAR] = "MAR", [MBR] = "MBR",
    [EAX] = "EAX", [EBX] = "EBX", [ECX] = "ECX",
    [EDX] = "EDX", [EEX] = "EEX", [EFX] = "EFX",
    [AC]  = "AC",  [CC]  = "CC",
    [CS]  = "CS",  [DS]  = "DS"
};

const char *nombreRegistro(uint8_t codigo){
    codigo &= 0x1F;   /* por los 3 bits reservados del byte de registro */
    return NOMBRE_REG[codigo] != NULL ? NOMBRE_REG[codigo] : "?";
}


/* ===== Dos operandos ===== */
int mov(MV *mv)   { 
    return OK; 
}
int add(MV *mv){ 
    return OK; 
}
int sub(MV *mv){ 
    return OK; 
}
int mul(MV *mv){ 
    return OK; 
}
int div_(MV *mv){ 
    return OK; 
}
int cmp(MV *mv) { 
    return OK; 
}
int and(MV *mv)  { 
    return OK; 
}
int or(MV *mv)  { 
    return OK; 
}
int xor(MV *mv) { 
    return OK; 
}
int swap(MV *mv) { 
    return OK; 
}
int shl(MV *mv){ 
    return OK; 
}
int shr(MV *mv)  { 
    return OK; 
}
int sar(MV *mv) { 
    return OK; 
}
int ldl(MV *mv){ 
    return OK; 
}
int ldh(MV *mv) { 
    return OK; 
}
int rnd(MV *mv) { 
    return OK; 
}

/* ===== Un operando ===== */
int sys(MV *mv) { 
    return OK; 
}
int jmp(MV *mv)  { 
    return OK; 
}
int jp(MV *mv) { 
    return OK; 
}
int jn_(MV *mv){ 
    return OK; 
}
int jz(MV *mv)  { 
    return OK; 
}
int jc(MV *mv) { 
    return OK;
}
int jv(MV *mv) { 
    return OK; 
}
int jnp(MV *mv){ 
    return OK; 
}
int jnn(MV *mv) { 
    return OK; 
}
int jnz(MV *mv) { 
    return OK; 
}
int not(MV *mv){ 
    return OK; 
}

/* ===== Sin operandos ===== */
int stop(MV *mv){
    mv->reg[IP] = 0xFFFFFFFF;
    return OK;
}



 //OPERANDOS Y CODIGO DE CONDICION

/* Arma la dirección lógica de un operando de memoria:
 * toma el segmento del registro base y le suma el desplazamiento. */
static uint32_t dirLogicaOperando(MV *mv, uint32_t valor){
    uint8_t  reg    = (uint8_t)(valor & 0xFF) & 0x1F;
    int16_t  offset = (int16_t)(valor >> 8);
    uint16_t seg    = (uint16_t)(mv->reg[reg] >> 16);
    uint16_t off    = (uint16_t)(mv->reg[reg] & 0xFFFF);

    return ((uint32_t)seg << 16) | (uint16_t)(off + offset);
}

/* Devuelve el valor de un operando (registro, inmediato o memoria). */
int leerOperando(MV *mv, uint32_t op, int32_t *valor){
    uint8_t  tipo  = (uint8_t)(op >> 24);
    uint32_t crudo = op & 0x00FFFFFF;

    if (tipo == TIPO_REGISTRO) {
        *valor = (int32_t)mv->reg[crudo & 0x1F];
        return OK;
    }
    if (tipo == TIPO_INMEDIATO) {
        *valor = (int16_t)crudo;          /* extensión de signo */
        return OK;
    }
    if (tipo == TIPO_MEMORIA)
        return leerMemoria(mv, dirLogicaOperando(mv, crudo), 4, valor);

    return ERR_INSTRUCCION;               /* operando inexistente */
}

/* Guarda un valor en un operando. Un inmediato no se puede escribir. */
int escribirOperando(MV *mv, uint32_t op, int32_t valor){
    uint8_t  tipo  = (uint8_t)(op >> 24);
    uint32_t crudo = op & 0x00FFFFFF;

    if (tipo == TIPO_REGISTRO) {
        mv->reg[crudo & 0x1F] = (uint32_t)valor;
        return OK;
    }
    if (tipo == TIPO_MEMORIA)
        return escribirMemoria(mv, dirLogicaOperando(mv, crudo), 4, valor);

    return ERR_INSTRUCCION;               /* inmediato o inexistente */
}

/* Actualiza N y Z, y pone C y V en 0.
 * Se usa en las operaciones que no pueden desbordar: MOV, AND, OR, XOR, NOT, SWAP. */
void actualizarCCSimple(MV *mv, int32_t resultado){
    uint32_t cc = 0;

    if (resultado < 0)  cc |= CC_N;
    if (resultado == 0) cc |= CC_Z;

    mv->reg[CC] = cc;
}

/* Actualiza los cuatro indicadores a partir del resultado "real" en 64 bits.
 *   N, Z -> según el resultado ya truncado a 32 bits (el que se guarda)
 *   C    -> el resultado real no entra en 32 bits
 *   V    -> el resultado guardado es distinto del real (quedó mal) */
void actualizarCC(MV *mv, int64_t resultado){
    int32_t res32 = (int32_t)resultado;
    uint32_t cc = 0;

    if (res32 < 0)  cc |= CC_N;
    if (res32 == 0) cc |= CC_Z;
    if (((uint64_t)resultado >> 32) != 0) cc |= CC_C;
    if (res32 != resultado)               cc |= CC_V;

    mv->reg[CC] = cc;
}

//Ejecuta UNA instrucción, la que apunta IP:
//   1. traduce IP (dirección lógica) a dirección física
//  2. decodifica la instrucción y carga OPC, OP1 y OP2
//   3. avanza IP a la instrucción siguiente
//   4. llama a la función de la instrucción (mov, add, ...) 

int ejecutarInstruccion(MV *mv){
    uint16_t seg = (uint16_t)(mv->reg[IP] >> 16);
    uint16_t off = (uint16_t)(mv->reg[IP] & 0xFFFF);
    uint16_t dir = mv->tabla[seg].base + off;    /* dirección física */

    uint8_t  opc;
    uint32_t opA, opB;
    int tam = decodificarInstruccion(mv, dir, &opc, &opA, &opB);

    mv->reg[OPC] = opc;
    mv->reg[OP1] = opA;
    mv->reg[OP2] = opB;

    mv->reg[IP] += tam;     /* IP apunta a la próxima instrucción */

    if (mv->FUNCIONES[opc].func == NULL)
        return ERR_INSTRUCCION;

    return mv->FUNCIONES[opc].func(mv);
}
 
// Ejecuta instrucciones mientras IP esté dentro
//del segmento de código. Corta si alguna devuelve un error.
//STOP pone IP en -1, así que también corta el ciclo. 
int ejecutarPrograma(MV *mv){
    int err = OK;

    while (err == OK && ipEnSegmentoDeCodigo(mv))
        err = ejecutarInstruccion(mv);

    return err;
}



/* Lee 'tam' bytes de memoria a partir de 'dir' y los arma en un entero
 * (el primer byte es el más significativo).
 * Sirve para leer el valor "crudo" de un operando tal cual está en memoria. */
static uint32_t leerBytes(MV *mv, uint16_t dir, int tam){
    uint32_t valor = 0;
    for (int i = 0; i < tam; i++)
        valor = (valor << 8) | mv->mem[dir + i];
    return valor;
}

/* Decodifica la instrucción que empieza en la dirección física 'dir'.
 * Devuelve:
 *   opc  -> código de operación (5 bits)
 *   opA  -> operando A con el formato de OP1: tipo en el byte alto,
 *            valor crudo en los 3 bytes bajos (0 si no existe)
 *   opB  -> operando B con el mismo formato (0 si no existe)
 * y como resultado de la función, el tamaño total de la instrucción en bytes. */

int decodificarInstruccion(MV *mv, uint16_t dir, uint8_t *opc, uint32_t *opA, uint32_t *opB){
    uint8_t primer = mv->mem[dir];
    uint8_t tipoA, tipoB;
    uint16_t pos = dir + 1;     // los operandos empiezan después del primer byte 

    *opc = COD_OP(primer);

    if (*opc & 0x10) {                 // 0x10..0x1F: dos operandos 
        tipoB = TIPO_B(primer);
        tipoA = TIPO_A2(primer);
    } else if (*opc == STOP) {         // sin operandos 
        tipoB = TIPO_NINGUNO;
        tipoA = TIPO_NINGUNO;
    } else {                           //0x00..0x0E: un operando 
        tipoB = TIPO_NINGUNO;
        tipoA = TIPO_A1(primer);
    }

    //en memoria van en orden inverso: primero B, después A.
    //El tamaño en bytes de cada operando coincide con su tipo. 
    *opB = ((uint32_t)tipoB << 24) | leerBytes(mv, pos, tipoB);
    pos += tipoB;
    *opA = ((uint32_t)tipoA << 24) | leerBytes(mv, pos, tipoA);
    pos += tipoA;

    if (tipoB == TIPO_NINGUNO) *opB = 0;
    if (tipoA == TIPO_NINGUNO) *opA = 0;

    return pos - dir;
}


/* Imprime un operando (en formato OP1/OP2) como en Assembler:
 *   registro   -> EAX
 *   inmediato  -> 10     (decimal, con signo)
 *   memoria    -> [DS+5] (registro base + desplazamiento con signo) */

static void imprimirOperando(uint32_t op)
{
    uint8_t  tipo  = op >> 24;
    uint32_t valor = op & 0x00FFFFFF;

    switch (tipo) {
        case TIPO_REGISTRO:
            printf("%s", nombreRegistro((uint8_t)valor));
            break;
        case TIPO_INMEDIATO:
            printf("%d", (int16_t)valor);
            break;
        case TIPO_MEMORIA: {
            int16_t offset = (int16_t)(valor >> 8);   /* 2 bytes altos */
            uint8_t reg    = (uint8_t)(valor & 0xFF); /* byte bajo */
            printf("[%s", nombreRegistro(reg));
            if (offset > 0)      printf("+%d", offset);
            else if (offset < 0) printf("%d", offset); /* el %d ya pone el '-' */
            printf("]");
            break;
        }
    }
}

// Recorre el segmento de código y muestra cada instrucción con el formato
//[0000] B1 00 0A 00 05 9B | ADD [DS+5], 10 
void disassembler(MV *mv){
    uint16_t dir = mv->tabla[SEG_CODIGO].base;
    uint16_t fin = dir + mv->tabla[SEG_CODIGO].tamanio;

    while (dir < fin) {
        uint8_t  opc;
        uint32_t opA, opB;
        int tam = decodificarInstruccion(mv, dir, &opc, &opA, &opB);

        /* dirección física y bytes de la instrucción */
        printf("[%04X]", dir);
        for (int i = 0; i < tam; i++)
            printf(" %02X", mv->mem[dir + i]);

        /* mnemónico */
        if (mv->FUNCIONES[opc].func == NULL)
            printf(" | ???");
        else
            printf(" | %s", mv->FUNCIONES[opc].nombre);

        /* operandos */
        if (opA != 0) {
            printf(" ");
            imprimirOperando(opA);
        }
        if (opB != 0) {
            printf(", ");
            imprimirOperando(opB);
        }
        printf("\n");

        dir += tam;
    }
}

