#include "assembly.h"
#include "globals.h"
#include "cgen.h"
#include "code.h"
#include "symtab.h"
#include "util.h"

#define INDENT indent+=4
#define UNINDENT indent-=4

static int indent = 0;
static char temp[100];
static int linha = 0;

Objeto objHead = NULL;

Label labelHead = NULL;

EscopoGen escopoHead = NULL;

InstOperand rtnAddrReg;
InstOperand rtnValReg;
InstOperand stackReg;
InstOperand outputReg;
InstOperand rzero;
InstOperand globalReg;

RegisterName tempReg[10] = {
    $t0, $t1, $t2, $t3, $t4, $t5, $t6, $t7, $t8, $t9
};

RegisterName savedReg[10] = {
    $s0, $s1, $s2, $s3, $s4, $s5, $s6, $s7, $s8, $s9
};

RegisterName argReg[4] = {
    $a0, $a1, $a2, $a3
};

const char * toStringOpcode(Opcode op) {
    const char * strings[] = {
        "add", "addi", "sub", "subi", "mul", "div",
        "and", "or", "xor", "not",
        "mov", "lw", "li", "la", "sw",
        "beq", "bne", "blt", "blet", "bgt", "bget", "j", "jal", "jr",
        "nop", "hlt",
        "in", "out"
    };
    return strings[op];
}

const char * toStringRegName(RegisterName rn) {
    const char * strings[] = {
     "$0", "$v0", "$out", "$sp", "$inv", "$gp", "$fp", "$a0",
	   "$a1", "$a2", "$a3", "$s0", "$s1", "$s2", "$s3", "$s4",
	   "$s5", "$s6", "$s7", "$s8", "$s9", "$t0", "$t1", "$t2",
	   "$t3", "$t4", "$t5", "$t6", "$t7", "$t8", "$t9", "$ra"
    };
    return strings[rn];
}

InstOperand getTempReg(int i) {
    //loop temp reg use
    if(i > 9) {
        escopoHead->tempRegCount = 0;
        i = 0;
    }
    InstOperand operando = (InstOperand) malloc(sizeof(struct instOperand));
    operando->tipoEnderecamento = RegisterAddressing;
    operando->enderecamento.registrador = tempReg[i];
    return operando;
}

InstOperand getSavedReg(int i) {
    //loop save reg, saving before use
    if(i > 9) {
        escopoHead->savedRegCount = 0;
        i = 0;
    }
    InstOperand operando = (InstOperand) malloc(sizeof(struct instOperand));
    operando->tipoEnderecamento = RegisterAddressing;
    operando->enderecamento.registrador = savedReg[i];
    return operando;
}

InstOperand getArgReg(int i) {
    InstOperand operando = (InstOperand) malloc(sizeof(struct instOperand));
    operando->tipoEnderecamento = RegisterAddressing;
    operando->enderecamento.registrador = argReg[i];
    if(i > 3) {
        operando->enderecamento.registrador = $inv;
    }
    return operando;
}

InstOperand getMemLocation(RegisterName registrador) {
    InstOperand operando = (InstOperand) malloc(sizeof(struct instOperand));
    operando->tipoEnderecamento = IndexedAddressing;
    operando->enderecamento.indexado.offset = 0;
    operando->enderecamento.indexado.registrador = registrador;
    return operando;
}

InstOperand getMemIndexedLocation(RegisterName registrador, int offset) {
    InstOperand operando = (InstOperand) malloc(sizeof(struct instOperand));
    operando->tipoEnderecamento = IndexedAddressing;
    operando->enderecamento.indexado.offset = offset;
    operando->enderecamento.indexado.registrador = registrador;
    return operando;
}

InstOperand getStackOperandLocation(Operand op) {
    int memloc = getMemoryLocation(op.contents.variable.name, op.contents.variable.scope);
    int offset = memloc - (escopoHead->tamanhoBlocoMemoria - 1);
    InstOperand operando = (InstOperand) malloc(sizeof(struct instOperand));
    operando->tipoEnderecamento = IndexedAddressing;
    operando->enderecamento.indexado.offset = offset;
    operando->enderecamento.indexado.registrador = $sp;
    return operando;
}

InstOperand getGlobalOperandLocation(Operand op) {
    int offset = getMemoryLocation(op.contents.variable.name, op.contents.variable.scope);
    InstOperand operando = (InstOperand) malloc(sizeof(struct instOperand));
    operando->tipoEnderecamento = IndexedAddressing;
    operando->enderecamento.indexado.offset = offset;
    operando->enderecamento.indexado.registrador = $gp;
    return operando;
}

InstOperand getStackLocation(int offset) {
    InstOperand operando = (InstOperand) malloc(sizeof(struct instOperand));
    operando->tipoEnderecamento = IndexedAddressing;
    operando->enderecamento.indexado.offset = offset;
    operando->enderecamento.indexado.registrador = $sp;
    return operando;
}

void pushStackSpace(int n) {
    printCode(insertObjInst(createObjInst(_ADDI, TYPE_I, stackReg, stackReg, getImediato(n))));
}

void popStackSpace(int n) {
    printCode(insertObjInst(createObjInst(_SUBI, TYPE_I, stackReg, stackReg, getImediato(n))));
}

InstOperand getOperandRegName(Operand op) {
    InstOperand rs, rt;
    char * regName;
    Operand operand;

    /* OPERANDO */
    if(op.kind == String) {
        rs = getRegByName(op.contents.variable.name);
        if(rs == NULL) {
            if(op.contents.variable.scope == NULL) {
                rs = getTempReg(escopoHead->tempRegCount++);
                insertRegistrador(createRegistrador(op, rs->enderecamento.registrador));
                printCode(insertObjInst(createObjInst(_LOAD, TYPE_I, rs, getRegByName(op.contents.variable.name), NULL)));
            } else if(op.contents.variable.scope == globalScope) {
                rs = getSavedReg(escopoHead->savedRegCount++);
                insertRegistrador(createRegistrador(op, rs->enderecamento.registrador));
                printCode(insertObjInst(createObjInst(_LOAD, TYPE_I, rs, getGlobalOperandLocation(op), NULL)));
            } else {
                rs = getSavedReg(escopoHead->savedRegCount++);
                insertRegistrador(createRegistrador(op, rs->enderecamento.registrador));
                printCode(insertObjInst(createObjInst(_LOAD, TYPE_I, rs, getStackOperandLocation(op), NULL)));
            }
        }
    } else {
        rt = getImediato(op.contents.val);
        rs = getTempReg(escopoHead->tempRegCount++);
        regName = (char *) toStringRegName(rs->enderecamento.registrador);
        operand.kind = String;
        operand.contents.variable.name = regName;
        operand.contents.variable.scope = NULL;
        insertRegistrador(createRegistrador(operand, rs->enderecamento.registrador));
        printCode(insertObjInst(createObjInst(_LOADI, TYPE_I, rs, rt, NULL)));
    }
    return rs;
}

InstOperand getVectorRegName(Operand op) {
    InstOperand reg = getRegByName(op.contents.variable.name);
    if(reg == NULL) {
        reg = getSavedReg(escopoHead->savedRegCount++);
        insertRegistrador(createRegistrador(op, reg->enderecamento.registrador));
        if(op.contents.variable.scope == globalScope) {
            printCode(insertObjInst(createObjInst(_LOADA, TYPE_I, reg, getGlobalOperandLocation(op), NULL)));
        } else {
            printCode(insertObjInst(createObjInst(_LOADA, TYPE_I, reg, getStackOperandLocation(op), NULL)));
        }
    }
    return reg;
}

InstOperand getTempRegName(Operand op) {
    InstOperand reg;
    // temp res
    reg = getTempReg(escopoHead->tempRegCount++);
    insertRegistrador(createRegistrador(op, reg->enderecamento.registrador));
    return reg;
}

void genCodeAritmetica(Quadruple q, Opcode op) {
    InstOperand op1, op2, op3;

    op1 = getOperandRegName(q->op1);
    op3 = getTempRegName(q->op3); //res

    if(q->op2.kind == String) {
        op2 = getOperandRegName(q->op2);
        printCode(insertObjInst(createObjInst(op, TYPE_R, op3, op1, op2)));
    } else { //immediate
        op2 = getImediato(q->op2.contents.val);
        int nextInstruction = op + 1;
        printCode(insertObjInst(createObjInst(opcode_map[nextInstruction], TYPE_I, op3, op1, op2)));
    }
}

void genCodeLogica(Quadruple q, Opcode op, Operand label) {
    InstOperand op1, op2, op3;

    op1 = getOperandRegName(q->op1);
    /*desvio*/
    op3 = getOperandLabel(label.contents.variable.name);

    if(q->op2.kind == String) {
        op2 = getOperandRegName(q->op2);
        printCode(insertObjInst(createObjInst(op, TYPE_I, op1, op2, op3)));
    } else {
        op2 = getOperandRegName(q->op2);
        printCode(insertObjInst(createObjInst(op, TYPE_I, op1, op2, op3)));
    }
}

void genCodeAtr(Quadruple q) {
    InstOperand reg = getOperandRegName(q->op2);
    if(q->op1.contents.variable.scope == NULL) {
        // Vector [var]
        InstOperand r = getRegByName(q->op1.contents.variable.name);
        printCode(insertObjInst(createObjInst(_STORE, TYPE_I, reg, getMemLocation(r->enderecamento.registrador), NULL)));
    } else if(q->op1.contents.variable.scope == globalScope) {
        if(q->op3.kind != Empty) {
            // Vector [const]
            InstOperand r = getOperandRegName(q->op1);
            printCode(insertObjInst(createObjInst(_STORE, TYPE_I, reg, getMemIndexedLocation(r->enderecamento.registrador, q->op3.contents.val), NULL)));
        } else {
            // Var comum
            printCode(insertObjInst(createObjInst(_STORE, TYPE_I, reg, getGlobalOperandLocation(q->op1), NULL)));
            InstOperand regAux = getRegByName(q->op1.contents.variable.name);
            if(regAux != NULL) {
                removeRegistrador(regAux->enderecamento.registrador);
            }
        }
    } else {
        if(q->op3.kind != Empty) {
            // Vector [const]
            InstOperand r = getOperandRegName(q->op1);
            printCode(insertObjInst(createObjInst(_STORE, TYPE_I, reg, getMemIndexedLocation(r->enderecamento.registrador, q->op3.contents.val), NULL)));
        } else {
            // Var comum
            printCode(insertObjInst(createObjInst(_STORE, TYPE_I, reg, getStackOperandLocation(q->op1), NULL)));
            InstOperand regAux = getRegByName(q->op1.contents.variable.name);
            if(regAux != NULL) {
                removeRegistrador(regAux->enderecamento.registrador);
            }
        }
    }
}

void genCodeCall(Quadruple q) {
    int tamanhoBlocoMemoria;

    if(!strcmp(q->op1.contents.variable.name, "input")) {
        printCode(insertObjInst(createObjInst(_HLT, TYPE_J, NULL, NULL, NULL)));
        printCode(insertObjInst(createObjInst(_IN, TYPE_I, getTempRegName(q->op3), NULL, NULL)));
    } else if(!strcmp(q->op1.contents.variable.name, "output")) {
        printCode(insertObjInst(createObjInst(_OUT, TYPE_I, getArgReg(0), NULL, getImediato(q->display))));
    } else if(!strcmp(escopoHead->nome, "main")) {
        tamanhoBlocoMemoria = getTamanhoBlocoMemoriaEscopo(q->op1.contents.variable.name);
        printCode(insertObjInst(createObjInst(_JUMPAL, TYPE_J, getOperandLabel(q->op1.contents.variable.name), NULL, NULL)));
        printCode(insertObjInst(createObjInst(_MOV, TYPE_I, getTempRegName(q->op3), rtnValReg, NULL)));
        popStackSpace(tamanhoBlocoMemoria + 1);
    } else {
        tamanhoBlocoMemoria = getTamanhoBlocoMemoriaEscopo(q->op1.contents.variable.name);
        printCode(insertObjInst(createObjInst(_STORE, TYPE_I, rtnAddrReg, getStackLocation(1), NULL))); // sw $ra
        printCode(insertObjInst(createObjInst(_JUMPAL, TYPE_J, getOperandLabel(q->op1.contents.variable.name), NULL, NULL)));
        popStackSpace(tamanhoBlocoMemoria + 1); // +1 $ra
        printCode(insertObjInst(createObjInst(_LOAD, TYPE_I, rtnAddrReg, getStackLocation(1), NULL))); // lw $ra
        printCode(insertObjInst(createObjInst(_MOV, TYPE_I, getTempRegName(q->op3), rtnValReg, NULL)));
    }
}

void genCodeSetParam(Quadruple q) {
    InstOperand reg;
    BucketList var = NULL;
    if(q->op1.kind == String && q->op1.contents.variable.scope != NULL) {
        var = getVarFromSymtab(q->op1.contents.variable.name, q->op1.contents.variable.scope);
    }

    if(escopoHead->argRegCount < 4) {
        if(q->op1.kind == String) {
            if(var != NULL && var->treeNode->kind.exp == VectorK) {
                printCode(insertObjInst(createObjInst(_LOADA, TYPE_I, getArgReg(escopoHead->savedRegCount), getStackOperandLocation(q->op1), NULL)));
            } else {
                reg = getOperandRegName(q->op1);
                if(getArgReg(escopoHead->argRegCount)->enderecamento.registrador != reg->enderecamento.registrador) {
                    printCode(insertObjInst(createObjInst(_MOV, TYPE_I, getArgReg(escopoHead->argRegCount), reg, NULL)));
                    moveRegistrador(getArgReg(escopoHead->argRegCount)->enderecamento.registrador, reg->enderecamento.registrador);
                }
            }
        } else {
            printCode(insertObjInst(createObjInst(_LOADI, TYPE_I, getArgReg(escopoHead->argRegCount), getImediato(q->op1.contents.val), NULL)));
        }
        escopoHead->argRegCount++;
    } else {

        if(q->op1.kind == String) {
            if(var != NULL && var->treeNode->kind.exp == VectorK) { // Vetor
                printCode(insertObjInst(createObjInst(_LOADA, TYPE_I, getSavedReg(escopoHead->savedRegCount), getStackOperandLocation(q->op1), NULL)));
            } else {
                printCode(insertObjInst(createObjInst(_LOAD, TYPE_I, getSavedReg(escopoHead->savedRegCount), getStackOperandLocation(q->op1), NULL)));
            }
        } else {
            printCode(insertObjInst(createObjInst(_LOADI, TYPE_I, getSavedReg(escopoHead->savedRegCount), getImediato(q->op1.contents.val), NULL)));
        }
        printCode(insertObjInst(createObjInst(_STORE, TYPE_I, getSavedReg(escopoHead->savedRegCount), getStackOperandLocation(q->op1), NULL)));
        escopoHead->savedRegCount++;
    }
}

void genCodeGetParam(Quadruple q) {
    if(escopoHead->argRegCount < 4) {
        InstOperand arg = getArgReg(escopoHead->argRegCount);
        insertRegistrador(createRegistrador(q->op1, arg->enderecamento.registrador));
        InstOperand saved = getSavedReg(escopoHead->savedRegCount);
        insertRegistrador(createRegistrador(q->op1, saved->enderecamento.registrador));
        printCode(insertObjInst(createObjInst(_MOV, TYPE_I, saved, arg, NULL)));
        moveRegistrador(saved->enderecamento.registrador, arg->enderecamento.registrador);
        escopoHead->argRegCount++;
        escopoHead->savedRegCount++;
    } else if(escopoHead->argRegCount >= 4) {
        insertRegistrador(createRegistrador(q->op1, getSavedReg(escopoHead->savedRegCount)->enderecamento.registrador));
        printCode(insertObjInst(createObjInst(_LOAD, TYPE_I, getSavedReg(escopoHead->savedRegCount), getStackOperandLocation(q->op1), NULL)));
        escopoHead->savedRegCount++;
    }
}

void genCodeRtn(Quadruple q) {
    InstOperand reg;
    if(strcmp(escopoHead->nome, "main")) { //main só output
        if(q->op1.kind != Empty) {
            reg = getOperandRegName(q->op1);
            printCode(insertObjInst(createObjInst(_MOV, TYPE_I, rtnValReg, reg, NULL)));
        }
        printCode(insertObjInst(createObjInst(_JUMPR, TYPE_I, rtnAddrReg, NULL, NULL)));
    }
}

void genCodeVec(Quadruple q) {
    InstOperand reg = getVectorRegName(q->op1); //vet addr
    if(q->op2.kind == String) {
        InstOperand temp = getTempRegName(q->op3);
        printCode(insertObjInst(createObjInst(_ADD, TYPE_R, temp, reg, getOperandRegName(q->op2))));
        printCode(insertObjInst(createObjInst(_LOAD, TYPE_I, temp, getMemIndexedLocation(temp->enderecamento.registrador, 0), NULL)));
    } else {
        printCode(insertObjInst(createObjInst(_LOAD, TYPE_I, getTempRegName(q->op3), getMemIndexedLocation(reg->enderecamento.registrador, q->op2.contents.val), NULL)));
    }
}

void genCodeVecAddr(Quadruple q) {
    InstOperand reg = getVectorRegName(q->op1); //vet addr
    if(q->op2.kind == String) {
        /* Vet addr base + variable*/
        printCode(insertObjInst(createObjInst(_ADD, TYPE_R, getTempRegName(q->op3), reg, getOperandRegName(q->op2))));
    }
}

void genCodeFunct(Quadruple q) {
    memset(temp, '\0', sizeof(temp));
    strcat(temp, "\n");
    strcat(temp, q->op1.contents.variable.name);
    strcat(temp, ":");
    insertLabel(q->op1.contents.variable.name, linha);
    emitCode(temp);
    pushEscopoGen(createEscopoGen(q->op1.contents.variable.name));

    if(!strcmp(escopoHead->nome, "main")) {
        pushStackSpace(escopoHead->tamanhoBlocoMemoria + getTamanhoBlocoMemoriaEscopoGlobal() - 1);
    } else {
        pushStackSpace(escopoHead->tamanhoBlocoMemoria + 1); // +1 $ra
    }
}

void genCodeLabel(Quadruple q) {

    memset(temp, '\0', sizeof(temp));
    strcat(temp, ".");
    strcat(temp, q->op1.contents.variable.name);
    strcat(temp, "\t");

    insertLabel(q->op1.contents.variable.name, linha);
    emitCode(temp);
}

void printCode(Objeto instrucao) {
    char aux[20];
    memset(temp, '\0', sizeof(temp));
    sprintf(temp, "%d:\t", linha++);
    strcat(temp, toStringOpcode(instrucao->opcode));
    strcat(temp, "\t");
    if(instrucao->op1 != NULL) {
        if(instrucao->op1->tipoEnderecamento == ImmediateAddressing) {
            sprintf(aux, "%d", instrucao->op1->enderecamento.imediato);
            strcat(temp, aux);
        } else if(instrucao->op1->tipoEnderecamento == RegisterAddressing) {
            strcat(temp, toStringRegName(instrucao->op1->enderecamento.registrador));
        } else if(instrucao->op1->tipoEnderecamento == IndexedAddressing) {
            sprintf(aux, "%d(%s)", instrucao->op1->enderecamento.indexado.offset, toStringRegName(instrucao->op1->enderecamento.indexado.registrador));
            strcat(temp, aux);
        } else { // Label
            strcat(temp, instrucao->op1->enderecamento.label);
        }
    }
    if(instrucao->op2 != NULL) {
        strcat(temp, ", ");
        if(instrucao->op2->tipoEnderecamento == ImmediateAddressing) {
            sprintf(aux, "%d", instrucao->op2->enderecamento.imediato);
            strcat(temp, aux);
        } else if(instrucao->op2->tipoEnderecamento == RegisterAddressing) {
            strcat(temp, toStringRegName(instrucao->op2->enderecamento.registrador));
        } else if(instrucao->op2->tipoEnderecamento == IndexedAddressing) {
            sprintf(aux, "%d(%s)", instrucao->op2->enderecamento.indexado.offset, toStringRegName(instrucao->op2->enderecamento.indexado.registrador));
            strcat(temp, aux);
        } else { // Label
            strcat(temp, instrucao->op2->enderecamento.label);
        }
    }
    if(instrucao->op3 != NULL) {
        strcat(temp, ", ");
        if(instrucao->op3->tipoEnderecamento == ImmediateAddressing) {
            sprintf(aux, "%d", instrucao->op3->enderecamento.imediato);
            strcat(temp, aux);
        } else if(instrucao->op3->tipoEnderecamento == RegisterAddressing) {
            strcat(temp, toStringRegName(instrucao->op3->enderecamento.registrador));
        } else if(instrucao->op3->tipoEnderecamento == IndexedAddressing) {
            sprintf(aux, "%d(%s)", instrucao->op3->enderecamento.indexado.offset, toStringRegName(instrucao->op3->enderecamento.indexado.registrador));
            strcat(temp, aux);
        } else { // Label
            strcat(temp, instrucao->op3->enderecamento.label);
        }
    }
    emitObjectCode(temp, indent);
}

void geraCodigoObjeto(Quadruple q) {
    INDENT;
    emitCode("\n########## Assembly ##########");
    espReg(); //registradores especiais
    while(q != NULL) {
        switch (q->instruction) {
            case ADD:
                genCodeAritmetica(q, _ADD);
                break;

            case SUB:
                genCodeAritmetica(q, _SUB);
                break;

            case MULT:
                genCodeAritmetica(q, _MULT);
                break;

            case DIV:
                genCodeAritmetica(q, _DIV);
                break;

            case EQUAL:
                genCodeLogica(q, _BEQ, q->next->op2);
                break;

            case NE:
                genCodeLogica(q, _BNE, q->next->op2);
                break;

            case LTHAN:
                genCodeLogica(q, _BLT, q->next->op2);
                break;

            case LET:
                genCodeLogica(q, _BLET, q->next->op2);
                break;

            case GTHAN:
                genCodeLogica(q, _BGT, q->next->op2);
                break;

            case GET:
                genCodeLogica(q, _BGET, q->next->op2);
                break;

            case ASN:
                genCodeAtr(q);
                break;

            case VEC:
                genCodeVec(q);
                break;

            case VEC_ADDR:
                genCodeVecAddr(q);
                break;

            case FUNC:
                genCodeFunct(q);
                escopoHead->savedRegCount = 0;
                break;

            case RTN:
                genCodeRtn(q);
                break;

            case GET_PARAM:
                genCodeGetParam(q);
                break;

            case SET_PARAM:
                genCodeSetParam(q);
                break;

            case CALL:
                genCodeCall(q);
                escopoHead->argRegCount = 0;
                break;

            case GOTO:
                printCode(insertObjInst(createObjInst(_JUMP, TYPE_J, getOperandLabel(q->op1.contents.variable.name), NULL, NULL)));
                break;

            case LBL:
                genCodeLabel(q);
                break;

            case HLT:
                printCode(insertObjInst(createObjInst(_HLT, TYPE_J, NULL, NULL, NULL)));
                break;

            case PARAM_LIST:
                escopoHead->argRegCount = 0;
                break;

            default:
                break;
        }
        q = q->next;
    }
}

EscopoGen createEscopoGen(const char * nome) {
    EscopoGen eg = (EscopoGen) malloc(sizeof(struct EscopoGen));
    eg->argRegCount = 0;
    eg->savedRegCount = 0;
    eg->tempRegCount = 0;
    BucketList bl = st_bucket_func((char *) nome);
    eg->quantidadeParametros = getQuantidadeParametros(bl->treeNode);
    eg->quantidadeVariaveis = getQuantidadeVariaveis(bl->treeNode);
    eg->tamanhoBlocoMemoria = getTamanhoBlocoMemoriaEscopo((char *) nome);
    eg->nome = nome;
    eg->regList = NULL;
    eg->next = NULL;
    return eg;
}

void pushEscopoGen(EscopoGen eg) {
    if(escopoHead == NULL) {
        escopoHead = eg;
    } else {
        eg->next = escopoHead;
        escopoHead = eg;
    }
}

void popEscopoGen() {
    if(escopoHead != NULL) {
        EscopoGen eg = escopoHead;
        escopoHead = eg->next;
        free(eg);
    }
}

Registrador createRegistrador(Operand op, RegisterName regName) {
    Registrador r = (Registrador) malloc(sizeof(struct registrador));
    r->op = op;
    r->regName = regName;
    r->next = NULL;
    return r;
}

void insertRegistrador(Registrador r) {
    Registrador head;
    if(escopoHead != NULL) {
        head = escopoHead->regList;
    }

    if(head == NULL) {
        escopoHead->regList = r;
    } else {
        Registrador temp = head;
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = r;
    }
}

void moveRegistrador(RegisterName dest, RegisterName orig) {
    Registrador origem = getRegistrador(orig);
    origem->regName = dest;
    removeRegistrador(dest);
}

void removeRegistrador(RegisterName name) {
    Registrador atual, anterior;
    if(escopoHead != NULL) {
        atual = escopoHead->regList;
    }
    if(name == atual->regName) {
        escopoHead->regList = atual->next;
        free(atual);
        atual = NULL;
        return;
    }

    anterior = atual;
    atual = atual->next;

    while(atual != NULL && anterior != NULL) {
        if(name == atual->regName) {
            anterior->next = atual->next;
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->next;
    }
}

Registrador getRegistrador(RegisterName name) {
    Registrador reg;
    if(escopoHead != NULL) {
        reg = escopoHead->regList;
    }
    while(reg != NULL) {
        if(name == reg->regName) {
            return reg;
        }
        reg = reg->next;
    }
    return NULL;
}

InstOperand getRegByName(char * name) {
    Registrador reg;
    if(escopoHead != NULL) {
        reg = escopoHead->regList;
    }
    while(reg != NULL) {
        if(!strcmp(name, reg->op.contents.variable.name)) {
            InstOperand operando = (InstOperand) malloc(sizeof(struct instOperand));
            operando->tipoEnderecamento = RegisterAddressing;
            operando->enderecamento.registrador = reg->regName;
            return operando;
        }
        reg = reg->next;
    }
    return NULL;
}

void freeParamList(Registrador head) {
    Registrador temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

Objeto createObjInst(Opcode opcode, Type type, InstOperand op1, InstOperand op2, InstOperand op3) {
    Objeto obj = (Objeto) malloc(sizeof(struct objeto));
    obj->opcode = opcode;
    obj->type = type;
    obj->op1 = op1;
    obj->op2 = op2;
    obj->op3 = op3;
    obj->next = NULL;
    return obj;
}

Objeto insertObjInst(Objeto obj) {
    if(objHead == NULL) {
        objHead = obj;
    } else {
        Objeto temp = objHead;
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = obj;
    }
    return obj;
}

void espReg(void) {

    rtnAddrReg = (InstOperand) malloc(sizeof(struct instOperand));
    rtnAddrReg->tipoEnderecamento = RegisterAddressing;
    rtnAddrReg->enderecamento.registrador = $ra;

    rtnValReg = (InstOperand) malloc(sizeof(struct instOperand));
    rtnValReg->tipoEnderecamento = RegisterAddressing;
    rtnValReg->enderecamento.registrador = $v0;

    stackReg = (InstOperand) malloc(sizeof(struct instOperand));
    stackReg->tipoEnderecamento = RegisterAddressing;
    stackReg->enderecamento.registrador = $sp;

    outputReg = (InstOperand) malloc(sizeof(struct instOperand));
    outputReg->tipoEnderecamento = RegisterAddressing;
    outputReg->enderecamento.registrador = $out;

    rzero = (InstOperand) malloc(sizeof(struct instOperand));
    rzero->tipoEnderecamento = RegisterAddressing;
    rzero->enderecamento.registrador = $0;

    globalReg = (InstOperand) malloc(sizeof(struct instOperand));
    globalReg->tipoEnderecamento = RegisterAddressing;
    globalReg->enderecamento.registrador = $gp;
}

InstOperand getImediato(int valor) {
    InstOperand imediato = (InstOperand) malloc(sizeof(struct instOperand));
    imediato->tipoEnderecamento = ImmediateAddressing;
    imediato->enderecamento.imediato = valor;
    return imediato;
}

InstOperand getOperandLabel(char * name) {
    InstOperand label = (InstOperand) malloc(sizeof(struct instOperand));
    label->tipoEnderecamento = LabelAddressing;
    label->enderecamento.label = name;
    return label;
}

Label createLabel(char * nome, int linha) {
    Label l = (Label) malloc(sizeof(struct label));
    l->nome = nome;
    l->linha = linha;
    l->next = NULL;
    return l;
}

void insertLabel(char * nome, int linha) {
    Label l = createLabel(nome, linha);
    if(labelHead == NULL) {
        labelHead = l;
    } else {
        Label temp = labelHead;
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = l;
    }
}

int getLinhaLabel(char * nome) {
    Label l;
    if(labelHead != NULL) {
        l = labelHead;
    }
    while(l != NULL) {
        if(!strcmp(nome, l->nome)) {
            return l->linha + 1;
        }
        l = l->next;
    }
    return -1;
}

Objeto getCodigoObjeto(void) {
    return objHead;
}
