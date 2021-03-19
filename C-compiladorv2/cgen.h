#include "globals.h"

#ifndef _CGEN_H_
#define _CGEN_H_

typedef enum {Empty, IntConst, String} OperandKind;

typedef enum instrucao {ADD, SUB, MULT, DIV,
      VEC, VEC_ADDR,
      EQUAL, NE, LTHAN, LET, GTHAN, GET, ASN,
      FUNC, RTN, GET_PARAM, SET_PARAM, CALL, PARAM_LIST,
      JPF, GOTO, LBL, HLT} InstructionKind;

typedef struct  {
    OperandKind kind;
    union {
        int val;
        struct {
            char * name;
            struct ScopeRec * scope;
        } variable;
    } contents;
} Operand;


typedef struct Quad {
    InstructionKind instruction;
    Operand op1, op2, op3;
    int linha;
    int display;
    struct Quad * next;
} * Quadruple;

typedef struct Location {
    Quadruple * quad;
    struct Location * next;
} * LocationStack;

typedef struct Param {
    int * count;
    struct Param * next;
} * ParamStack;

Quadruple * insertQuad(Quadruple q);

Quadruple createQuad(InstructionKind instruction, Operand op1, Operand op2, Operand op3);

void pushLocation(LocationStack ls);

void popLocation();

LocationStack createLocation(Quadruple * quad);

void updateLocation(Operand op);

void pushParam(int * count);

void popParam();

void preparaVazio();

void printIntermediateCode();

Quadruple getCodigoIntermediario(void);

void codeGen(TreeNode * syntaxTree, char * codefile);

void verificaFimInstrucaoAnterior(void);

#endif
