#include "assembly.h"
#include "code.h"
#include "util.h"

char temp[100];

//Opcodes
const char * toBinaryOpcode(Opcode op) {
    const char * strings[] = {
      //"add",  "addi",   "sub",    "subi",   "mul",    "div",
      "000001", "000011", "000110", "000111", "001010", "001100",
      //"and",  "or",     "xor",    "not",
      "010110", "010010", "010100", "010000",
      //"mov",  "lw",     "li",     "la",     "sw",
      "011010", "101001", "101011", "101111", "101000",
      //"beq",  "bne",    "blt",    "blet",   "bgt",    "bget",   "j",      "jal",    "jr",
      "011110", "011111", "100001", "100101", "100000", "100010", "110000", "110001", "110010",
      //"nop",  "hlt",
      "000000", "111111",
      //"in",   "out"
      "111000", "111001"
    };
    return strings[op];
}

//Registradores
const char * toBinaryRegister(RegisterName rn) {
    const char * strings[] = {
        // "$0", "$v0",   "$out",  "$sp",  "$inv",   "$gp",   "$fp",   "$a0",
        "00000", "00001", "00010", "00011", "00100", "00101", "00110", "00111",
        // "$a1", "$a2",  "$a3",   "$s0",   "$s1",   "$s2",   "$s3",   "$s4",
        "01000", "01001", "01010", "01011", "01100", "01101", "01110", "01111",
        // "$s5", "$s6",  "$s7",   "$s8",   "$s9",   "$t0",   "$t1",   "$t2",
        "10000", "10001", "10010", "10011", "10100", "10101", "10110", "10111",
        // "$t3", "$t4",  "$t5",   "$t6",   "$t7",   "$t8",   "$t9",   "$ra"
        "11000", "11001", "11010", "11011", "11100", "11101", "11110", "11111"
    };
    return strings[rn];
}

const char * getZeros(int n) {
    int i = 0;
    char * zeros = (char *) malloc(n + 1);
    while(i < n) {
        zeros[i++] = '0';
    }
    zeros[i] = '\0';
    return zeros;
}

const char * decimalToBinaryStr(unsigned x, int qtdBits) {
    int i = 0;
    qtdBits--;
    char * bin = (char *) malloc(qtdBits + 1);
    for (unsigned bit = 1u << qtdBits; bit != 0; bit >>= 1) {
        bin[i++] = (x & bit) ? '1' : '0';
    }
    bin[i] = '\0';
    return bin;
}

void geraCodigoBinario(Objeto codigoObjeto) {
    emitCode("\n########## Binary ##########\n");
    Objeto obj = codigoObjeto;
    char str[26];
    int linha = 0;

    memset(temp, '\0', sizeof(temp));
    strcat(temp, "[00");
    sprintf(str, "%d", linha++);
    strcat(temp, str);
    strcat(temp, "] ");
    strcat(temp, toBinaryOpcode(_JUMP));
    strcat(temp, " ");
    strcat(temp, decimalToBinaryStr(getLinhaLabel((char*) "main"), 26));
    strcat(temp, ";  Jump main()");
    emitCode(temp);

    while(obj != NULL) {
        memset(temp, '\0', sizeof(temp));
        strcat(temp, "[");
        if (linha<10){
          strcat(temp, "00");
        } else
        if (linha<100){
          strcat(temp, "0");
        }
        sprintf(str, "%d", linha++);
        strcat(temp, str);
        strcat(temp, "] ");

        // Traduz o opcode para binário
        strcat(temp, toBinaryOpcode(obj->opcode));
        strcat(temp, " ");

        switch(obj->type) {
            case TYPE_R:
                strcat(temp, toBinaryRegister(obj->op2->enderecamento.registrador));
                strcat(temp, " ");
                strcat(temp, toBinaryRegister(obj->op3->enderecamento.registrador));
                strcat(temp, " ");
                strcat(temp, toBinaryRegister(obj->op1->enderecamento.registrador));
                strcat(temp, " ");
                strcat(temp, getZeros(11));
                break;
            case TYPE_I:
                if(obj->opcode == _LOADI) {
                    strcat(temp, getZeros(5));
                    strcat(temp, " ");
                    strcat(temp, toBinaryRegister(obj->op1->enderecamento.registrador));
                    strcat(temp, " ");
                    strcat(temp, decimalToBinaryStr(obj->op2->enderecamento.imediato, 16));
                    break;
                } else if(obj->opcode == _BLT || obj->opcode == _BLET || obj->opcode == _BGT || obj->opcode == _BGET
                    || obj->opcode == _BEQ || obj->opcode == _BNE) {
                        strcat(temp, toBinaryRegister(obj->op1->enderecamento.registrador));
                        strcat(temp, " ");
                        strcat(temp, toBinaryRegister(obj->op2->enderecamento.registrador));
                        strcat(temp, " ");
                        strcat(temp, decimalToBinaryStr(getLinhaLabel(obj->op3->enderecamento.label), 16));
                        break;
                }

                if(obj->op2 == NULL) {
                    strcat(temp, getZeros(5));
                } else {
                    if(obj->op2->tipoEnderecamento == RegisterAddressing) {
                        strcat(temp, toBinaryRegister(obj->op2->enderecamento.registrador));
                    } else if(obj->op2->tipoEnderecamento == IndexedAddressing) {
                        strcat(temp, toBinaryRegister(obj->op2->enderecamento.indexado.registrador));
                        strcat(temp, " ");
                        strcat(temp, toBinaryRegister(obj->op1->enderecamento.registrador));
                        strcat(temp, " ");
                        strcat(temp, decimalToBinaryStr(obj->op2->enderecamento.indexado.offset, 16));
                        break;
                    }
                }
                strcat(temp, " ");

                if(obj->op1 == NULL) {
                    strcat(temp, getZeros(5));
                } else {
                    if(obj->op1->tipoEnderecamento == RegisterAddressing) {
                        strcat(temp, toBinaryRegister(obj->op1->enderecamento.registrador));
                    }
                }
                strcat(temp, " ");

                if(obj->op3 == NULL) {
                    strcat(temp, getZeros(16));
                } else {
                    if(obj->op3->tipoEnderecamento == ImmediateAddressing) {
                        strcat(temp, decimalToBinaryStr(obj->op3->enderecamento.imediato, 16));
                    } else if(obj->op3->tipoEnderecamento == LabelAddressing) {
                        strcat(temp, decimalToBinaryStr(getLinhaLabel(obj->op3->enderecamento.label), 16));
                    }
                }

                break;
            case TYPE_J:
                if(obj->opcode == _JUMP || obj->opcode == _JUMPAL) {
                    strcat(temp, decimalToBinaryStr(getLinhaLabel(obj->op1->enderecamento.label), 26));
                } else { // HLT, NOP
                    strcat(temp, getZeros(26));
                }
                break;
        }
        strcat(temp, " (op: ");
        strcat(temp, toStringOpcode(obj->opcode));
        strcat(temp, ")");
        emitCode(temp);
        obj = obj->next;
    }
}
