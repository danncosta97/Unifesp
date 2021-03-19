#ifndef _ASSEMBLY_H_
#define _ASSEMBLY_H_

#include "cgen.h"

typedef enum opcode {_ADD, _ADDI, _SUB, _SUBI, _MULT, _DIV,
      _AND, _OR, _XOR, _NOT,
      _MOV, _LOAD, _LOADI, _LOADA, _STORE,
      _BEQ, _BNE, _BLT, _BLET, _BGT, _BGET, _JUMP, _JUMPAL, _JUMPR,
      _NOP, _HLT,
      _IN, _OUT} Opcode;


static const enum opcode opcode_map[] = {_ADD, _ADDI, _SUB, _SUBI, _MULT, _DIV,
      _AND, _OR, _XOR, _NOT,
      _MOV, _LOAD, _LOADI, _LOADA, _STORE,
      _BEQ, _BNE, _BLT, _BLET, _BGT, _BGET, _JUMP, _JUMPAL, _JUMPR,
      _NOP, _HLT,
      _IN, _OUT};

typedef enum type {
    TYPE_R, TYPE_I, TYPE_J
} Type;

typedef enum registerName {
    $0, $v0, $out, $sp, $inv, $gp, $fp, $a0,
    $a1, $a2, $a3, $s0, $s1, $s2, $s3, $s4,
    $s5, $s6, $s7, $s8, $s9, $t0, $t1, $t2,
    $t3, $t4, $t5, $t6, $t7, $t8, $t9, $ra
} RegisterName;

typedef enum addressingType {
    ImmediateAddressing, RegisterAddressing, IndexedAddressing, LabelAddressing
} AddressingType;

typedef struct instOperand {
    union {
        int imediato;
        RegisterName registrador;
        struct {
            RegisterName registrador;
            int offset;
        } indexado;
        char * label;
    } enderecamento;
    AddressingType tipoEnderecamento;
} * InstOperand;

typedef struct EscopoGen {
    int argRegCount;
    int savedRegCount;
    int tempRegCount;
    int quantidadeParametros;
    int quantidadeVariaveis;
    int tamanhoBlocoMemoria;
    const char * nome;
    struct registrador * regList;
    struct EscopoGen * next;
} * EscopoGen;

typedef struct registrador {
    Operand op;
    RegisterName regName;
    struct registrador * next;
} * Registrador;

typedef struct objeto {
    Opcode opcode;
    Type type;
    InstOperand op1;
    InstOperand op2;
    InstOperand op3;
    struct objeto * next;
} * Objeto;

typedef struct label {
    char * nome;
    int linha;
    struct label * next;
} * Label;

const char * toStringOpcode(enum opcode op);

EscopoGen createEscopoGen(const char *);
void pushEscopoGen(EscopoGen eg);
void popEscopoGen(void);

Registrador createRegistrador(Operand op, RegisterName regName);
void insertRegistrador(Registrador r);
void removeRegistrador(RegisterName name);

Registrador getRegistrador(RegisterName name);
void moveRegistrador(RegisterName dest, RegisterName orig);

InstOperand getRegByName(char * name);

void geraCodigoObjeto(Quadruple q);

void printCode(Objeto instrucao);

Objeto createObjInst(Opcode opcode, Type type, InstOperand op1, InstOperand op2, InstOperand op3);

Objeto insertObjInst(Objeto obj);

Objeto getCodigoObjeto(void);

void espReg(void);

InstOperand getImediato(int valor);

InstOperand getOperandLabel(char * name);

Label createLabel(char * nome, int linha);
void insertLabel(char * nome, int linha);
int getLinhaLabel(char * nome);

#endif
