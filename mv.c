#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mv.h"


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
    strcpy(mv->FUNCIONES[DIV].nombre, "DIV");
    mv->FUNCIONES[DIV].func = div;
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
    strcpy(mv->FUNCIONES[JN].nombre, "JN");
    mv->FUNCIONES[JN].func = jn;
    strcpy(mv->FUNCIONES[JZ].nombre, "JZ");
    mv->FUNCIONES[JZ].func = jz;
    strcpy(mv->FUNCIONES[JC].nombre, "JN");
    mv->FUNCIONES[JC].func = jc;
    strcpy(mv->FUNCIONES[JV].nombre, "JN");
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

void init_registros(MV *mv)
{
    strcpy(mv->reg[IP], "IP");
    strcpy(mv->reg[OPC], "OPC");
    strcpy(mv->reg[OP1], "OP1");
    strcpy(mv->reg[OP2], "OP2");

    strcpy(mv->reg[LAR], "LAR");
    strcpy(mv->reg[MAR], "MAR");
    strcpy(mv->reg[MBR], "MBR");


    // Bloque de registros generales
    strcpy(mv->reg[EAX], "EAX");
    strcpy(mv->reg[EBX], "EBX");
    strcpy(mv->reg[ECX], "ECX");
    strcpy(mv->reg[EDX], "EDX");
    strcpy(mv->reg[EEX], "EEX");
    strcpy(mv->reg[EFX], "EFX");

    // Acumulador y código de condición
    strcpy(mv->reg[AC], "AC");
    strcpy(mv->reg[CC], "CC");

    // Segmentos
    strcpy(mv->reg[CS], "CS");
    strcpy(mv->reg[DS], "DS");

    mv->reg[ECX] = -1;
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