#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memoria.h"
//Carga la tabla de instrucciones: para cada código de operación
//Los códigos que no existen quedan con func = NULL

void init_funciones(MV *mv)
{
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

const char *nombreRegistro(uint8_t codigo)
{
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
int stop(MV *mv)
{
    mv->reg[IP] = 0xFFFFFFFF;
    return OK;
}

//Ejecuta UNA instrucción, la que apunta IP:
//   1. traduce IP (dirección lógica) a dirección física
//  2. decodifica la instrucción y carga OPC, OP1 y OP2
//   3. avanza IP a la instrucción siguiente
//   4. llama a la función de la instrucción (mov, add, ...) 

int ejecutarInstruccion(MV *mv)
{
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
int ejecutarPrograma(MV *mv)
{
    int err = OK;

    while (err == OK && ipEnSegmentoDeCodigo(mv))
        err = ejecutarInstruccion(mv);

    return err;
}

/* Desensambla y muestra las instrucciones cargadas en memoria. */
void disassembler(MV *mv)
{
    (void)mv;
    printf("disassembler() todavia no esta implementado.\n");
}
