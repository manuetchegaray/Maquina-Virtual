#pragma once
#include <stdint.h> //Te da tipos de tamaño exacto: uint8_t (1 byte), uint16_t (2) y uint32_t (4).

#define MV_H

#define MEMORY_SIZE 16384           // 16 KiB
#define CANTREG 32
#define SEG_TABLE 8
#define CANT_INSTR  32   

/* cabecera del archivo .vmx */
#define TAM_CABECERA 8
#define VERSION_MV   1


//  REGISTROS
#define IP 0 //
#define OPC 1 //
#define OP1 2 //
#define OP2 3 //instruction pointer
#define LAR 4
#define MAR 5
#define MBR 6
//7-8-9 Reservados
#define EAX 10
#define EBX 11
#define ECX 12
#define EDX 13
#define EEX 14
#define EFX 15
#define AC 16 //acumulador
#define CC 17 //condition code
//18 - 25 RESERVADOS
#define CS 26 //code segment
#define DS 27 //data segment
//28 -31 reservados

#define CC_N (1u << 31)   /* signo          */
#define CC_Z (1u << 30)   /* cero           */
#define CC_C (1u << 29)   /* acarreo        */
#define CC_V (1u << 28)   /* desbordamiento */

#define SEG_CODIGO  0
#define SEG_DATOS   1
#define SEG_INVALIDO 0xFFFF   /* base y tamaño de las entradas sin usar */

/*Instrucciones*/

/*Dos operandos*/
#define MOV  0x10
#define ADD  0x11
#define SUB  0x12
#define MUL  0x13
#define DIV_  0x14
#define CMP  0x15
#define AND  0x16
#define OR   0x17
#define XOR  0x18
#define SWAP 0x19
#define SHL  0x1A
#define SHR  0x1B
#define SAR  0x1C
#define LDL  0x1D
#define LDH  0x1E
#define RND  0x1F

/*Un operando*/
#define SYS  0x00
#define JMP  0x01
#define JP   0x02
#define JN_   0x03
#define JZ   0x04
#define JC   0x05
#define JV   0x06
#define JNP  0x07
#define JNN  0x08
#define JNZ  0x09
#define NOT  0x0A

/*Sin operandos*/
#define STOP 0x0F

/*Operandos*/
#define TIPO_NINGUNO    0   /*0 byes*/
#define TIPO_REGISTRO   1   /* 1 byte  */
#define TIPO_INMEDIATO  2   /* 2 bytes */
#define TIPO_MEMORIA    3   /* 3 bytes */

#define COD_OP(b)       ((b) & 0x1F)
#define TIPO_B(b)       (((b) >> 6) & 0x03)   /* solo con dos operandos */
#define TIPO_A2(b)      (((b) >> 4) & 0x03)   /* tipo de A, dos operandos */
#define TIPO_A1(b)      (((b) >> 6) & 0x03)   /* tipo de A, un operando */

/*Llamadas al sistema*/
#define SYS_READ   1
#define SYS_WRITE  2
 
/* modos de lectura / escritura, en EAX */
#define MODO_DECIMAL  0x01
#define MODO_CARACTER 0x02
#define MODO_OCTAL    0x04
#define MODO_HEXA     0x08
#define MODO_BINARIO  0x10

/*Errores*/
/* Tipo de dato para el manejo de errores */
typedef int vm_error_t;

#define OK                0
#define ERR_ARCHIVO       1
#define ERR_CABECERA      2
#define ERR_VERSION       3
#define ERR_TAMANIO       4
#define ERR_INSTRUCCION   5
#define ERR_DIV_CERO      6
#define ERR_SEGMENTO      7

typedef struct {
    uint16_t base; /*Direccion fisica del comienzo del segmento*/
    uint16_t tamanio; /*Cantidad de byte que ocupa*/
} Segmento;

typedef struct MV MV;
typedef int (*tOperacion)(MV *mv);

typedef struct {
    char nombre[6];
    tOperacion func;
} tfunc;

struct MV {
    uint8_t  mem[MEMORY_SIZE];
    uint32_t reg[CANTREG];
    Segmento tabla[SEG_TABLE];
    tfunc    FUNCIONES[CANT_INSTR];
};


/* mv.c : tabla de funciones y motor */
void init_funciones(MV *mv);
int  ejecutarInstruccion(MV *mv);
void disassembler(MV *mv);

/* dos operandos */
int mov(MV *mv);
int add(MV *mv);
int sub(MV *mv);
int mul(MV *mv);
int div_(MV *mv);
int cmp(MV *mv);
int and(MV *mv);
int or(MV *mv);
int xor(MV *mv);
int swap(MV *mv);
int shl(MV *mv);
int shr(MV *mv);
int sar(MV *mv);
int ldl(MV *mv);
int ldh(MV *mv);
int rnd(MV *mv);
 
/* un operando */
int sys(MV *mv);
int jmp(MV *mv);
int jp(MV *mv);
int jn_(MV *mv);
int jz(MV *mv);
int jc(MV *mv);
int jv(MV *mv);
int jnp(MV *mv);
int jnn(MV *mv);
int jnz(MV *mv);
int not(MV *mv);
 
/* sin operandos */
int stop(MV *mv);