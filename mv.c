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
    strcpy(mv->FUNCIONES[NOT_].nombre, "NOT");
    mv->FUNCIONES[NOT_].func = not_;

    strcpy(mv->FUNCIONES[STOP].nombre, "STOP");
    mv->FUNCIONES[STOP].func = stop;
}

void init_regs(tmv *mv)
{
    strcpy(mv->REGS[IP].nombre, "IP");
    strcpy(mv->REGS[OPC].nombre, "OPC");
    strcpy(mv->REGS[OP1].nombre, "OP1");
    strcpy(mv->REGS[OP2].nombre, "OP2");

    strcpy(mv->REGS[LAR].nombre, "LAR");
    strcpy(mv->REGS[MAR].nombre, "MAR");
    strcpy(mv->REGS[MBR].nombre, "MBR");


    // Bloque de registros generales
    strcpy(mv->REGS[EAX].nombre, "EAX");
    strcpy(mv->REGS[EBX].nombre, "EBX");
    strcpy(mv->REGS[ECX].nombre, "ECX");
    strcpy(mv->REGS[EDX].nombre, "EDX");
    strcpy(mv->REGS[EEX].nombre, "EEX");
    strcpy(mv->REGS[EFX].nombre, "EFX");

    // Acumulador y código de condición
    strcpy(mv->REGS[AC].nombre, "AC");
    strcpy(mv->REGS[CC].nombre, "CC");

    // Segmentos
    strcpy(mv->REGS[CS].nombre, "CS");
    strcpy(mv->REGS[DS].nombre, "DS");

    mv->REGS[ECX].dato = -1;
}

int ejecutarInstruccion(mv *mv)
{
    (void)mv;
    printf("ejecutarInstruccion() todavia no esta implementada.\n");
    return ERR_INSTRUCCION;
}
 
void disassembler(mv *mv)
{
    (void)mv;
    printf("disassembler() todavia no esta implementado.\n");
}