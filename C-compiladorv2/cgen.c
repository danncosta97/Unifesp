#include "globals.h"
#include "symtab.h"
#include "code.h"
#include "cgen.h"

#define INDENT indent+=4
#define UNINDENT indent-=4

static int linha = 0;
static char tempString[20];
static int temporario = 1;
static int label = 1;
static int indent = 0;

ParamStack paramHead = NULL;

Quadruple head = NULL;

LocationStack locationHead = NULL;

Operand operandoAtual;

Operand vazio;

InstructionKind instrucaoAtual;

Quadruple ultimaQuadrupla;

static void cGen (TreeNode * tree);

static char * createLabel() {
    char * temp = (char *) malloc(5);
    sprintf(temp, "L%d", label);
    ++label;
    return temp;
}

static char * createTemporaryOperandName() {
    char * temp = (char *) malloc(5);
    sprintf(temp, "t%d", temporario);
    ++temporario;
    return temp;
}


static Operand createTemporaryOperand() {
    Operand temp;
    char * tempName =  createTemporaryOperandName();
    temp.kind = String;
    temp.contents.variable.scope = NULL;
    temp.contents.variable.name = tempName;
    return temp;
}

static void genStmt(TreeNode * tree) {
    INDENT;
    TreeNode * p1, * p2, * p3;
    Operand op1, op2, op3;
    Quadruple * q;
    switch (tree->kind.stmt) {
        case VoidK:
            emitComment("-> type void", indent);
            p1 = tree->child[0];
            cGen(p1);
            emitComment("<- type void\n", indent);
            break;

        case IntegerK:
            emitComment("-> type int", indent);
            p1 = tree->child[0];
            cGen(p1);
            emitComment("<- type int\n", indent);
            break;

        case CompK:
            p1 = tree->child[0];
            if(p1) { /* Parâmetros */
                cGen(p1);
            }
            p2 = tree->child[1];
            if(p2) { /* Expressões */
                cGen(p2);
            }
            break;

        case IfK:
            emitComment("-> if", indent);
            p1 = tree->child[0];
            p2 = tree->child[1];
            p3 = tree->child[2];
            emitComment("-> if: test expression", indent);
            cGen(p1);
            op1 = operandoAtual;
            instrucaoAtual = JPF;
            q = insertQuad(createQuad(instrucaoAtual, op1, vazio, vazio));
            pushLocation(createLocation(q));
            emitComment("<- if: test expression", indent);

            emitComment("-> if: if block", indent);

            cGen(p2);
            emitComment("<- if: if block", indent);

            op2.kind = String;
            op2.contents.variable.name = createLabel();
            op2.contents.variable.scope = tree->scope;

            updateLocation(op2);
            popLocation();

            if(p3 != NULL) {
                q = insertQuad(createQuad(GOTO, vazio, vazio, vazio));
                pushLocation(createLocation(q));
            }


            insertQuad(createQuad(LBL, op2, vazio, vazio));
            emitComment("-> if: else/end block", indent);

            cGen(p3);

            if(p3 != NULL) {
                op1.kind = String;
                op1.contents.variable.name = createLabel();
                op1.contents.variable.scope = tree->scope;

                updateLocation(op1);
                popLocation();

                insertQuad(createQuad(LBL, op1, vazio, vazio));
            }
            emitComment("<- if: else/end block", indent);
            emitComment("<- if", indent);
            break;

        case ElseK:
            break;

        case WhileK:
            emitComment("-> while", indent);
            p1 = tree->child[0];
            p2 = tree->child[1];

            emitComment("-> while: test expression", indent);

            op1.kind = String;
            op1.contents.variable.name = createLabel();
            op1.contents.variable.scope = tree->scope;
            insertQuad(createQuad(LBL, op1, vazio, vazio));
            cGen(p1);
            op2 = operandoAtual;
            instrucaoAtual = JPF;
            q = insertQuad(createQuad(instrucaoAtual, op2, vazio, vazio));
            pushLocation(createLocation(q));

            emitComment("<- while: test expression", indent);

            emitComment("-> while: while block", indent);
            cGen(p2);
            instrucaoAtual = GOTO;
            insertQuad(createQuad(instrucaoAtual, op1, vazio, vazio));
            emitComment("<- while: while block", indent);

            op3.kind = String;
            op3.contents.variable.name = createLabel();
            op3.contents.variable.scope = tree->scope;
            insertQuad(createQuad(LBL, op3, vazio, vazio));
            updateLocation(op3);
            popLocation();
            emitComment("<- while", indent);
            break;

        case ReturnK:
            emitComment("-> return", indent);
            p1 = tree->child[0];
            emitComment("-> return: expression", indent);
            cGen(p1);
            if(p1) {
                op1 = operandoAtual;
            } else {
                op1 = vazio;
            }
            instrucaoAtual = RTN;
            insertQuad(createQuad(instrucaoAtual, op1, vazio, vazio));
            emitComment("<- return: expression", indent);
            emitComment("<- return", indent);
            break;
    }
    UNINDENT;
}

static void genExp(TreeNode * tree) {
    INDENT;
    Quadruple q;
    TreeNode * p1, * p2;
    Operand op1, op2, op3;
    int qtdParams, display = -1;

    switch (tree->kind.exp) {
        case ConstK:
            emitComment("-> constant", indent);
            sprintf(tempString, "%d", tree->attr.val);
            emitComment(tempString, indent);
            operandoAtual.kind = IntConst;
            operandoAtual.contents.val = tree->attr.val;
            emitComment("<- constant", indent);
            break;

        case IdK:
            emitComment("-> identifier", indent);
            emitComment(tree->attr.name, indent);
            operandoAtual.kind = String;
            operandoAtual.contents.variable.name = tree->attr.name;
            operandoAtual.contents.variable.scope = tree->scope;
            emitComment("<- identifier", indent);
            break;

        case VectorK:
            emitComment("-> vector", indent);
            emitComment(tree->attr.name, indent);
            p1 = tree->child[0];
            operandoAtual.kind = String;
            operandoAtual.contents.variable.name = tree->attr.name;
            operandoAtual.contents.variable.scope = tree->scope;
            op1 = operandoAtual;
            emitComment("-> vector: position", indent);
            cGen(p1);
            op2 = operandoAtual;
            emitComment("<- vector: position", indent);
            instrucaoAtual = VEC;
            op3 = createTemporaryOperand();
            operandoAtual = op3;
            if(tree->varAccess == AccessingK) {
                ultimaQuadrupla = createQuad(instrucaoAtual, op1, op2, op3);
                insertQuad(ultimaQuadrupla);
            }
            emitComment("<- vector", indent);
            break; /* VectorK */

        case FunctionK:
            verificaFimInstrucaoAnterior();
            emitComment("-> function declaration", indent);
            emitComment(tree->attr.name, indent);

            if(strcmp(tree->attr.name, "input") && strcmp(tree->attr.name, "output")) {
                op1.kind = String;
                op1.contents.variable.name = tree->attr.name;
                op1.contents.variable.scope = tree->scope;
                insertQuad(createQuad(FUNC, op1, vazio, vazio));

                p1 = tree->child[0];
                while(p1 != NULL) {
                    op2.kind = String;
                    op2.contents.variable.name = p1->child[0]->attr.name;
                    op2.contents.variable.scope = p1->child[0]->scope;
                    insertQuad(createQuad(GET_PARAM, op2, vazio, vazio));
                    p1 = p1->sibling;
                }

                p2 = tree->child[1];
                cGen(p2);
            }

            emitComment("<- function declaration", indent);
            break;

        case CallK:
            emitComment("-> function call", indent);
            emitComment(tree->attr.name, indent);
            p1 = tree->child[0];
            op1.kind = String;
            op1.contents.variable.name = tree->attr.name;
            op1.contents.variable.scope = tree->scope;
            qtdParams = getQuantidadeParametros(tree);
            pushParam(&qtdParams);
            if(qtdParams > 0) {
                op2.kind = IntConst;
                op2.contents.val = qtdParams;
            } else {
                op2.kind = IntConst;
                op2.contents.val = 0;
            }

            instrucaoAtual = PARAM_LIST;
            op3.kind = IntConst;
            op3.contents.val = getQuantidadeParametros(tree);
            insertQuad(createQuad(instrucaoAtual, op3, vazio, vazio));
            emitComment("-> function call: arguments", indent);
            while(p1 != NULL) {
                cGen(p1);
                instrucaoAtual = SET_PARAM;
                insertQuad(createQuad(instrucaoAtual, operandoAtual, vazio, vazio));
                --qtdParams;
                if(!strcmp(tree->attr.name, "output") && p1->sibling == NULL) {
                    display = p1->attr.val;
                }
                p1 = p1->sibling;
            }
            popParam();
            emitComment("<- function call: arguments", indent);
            instrucaoAtual = CALL;
            operandoAtual = createTemporaryOperand();
            q = createQuad(instrucaoAtual, op1, op2, operandoAtual);
            if(display != -1) {
                q->display = display;
            }
            insertQuad(q);
            emitComment("<- function call", indent);
            break;

        case OpK:
            if(tree->attr.op == ASSIGN) {

                emitComment("-> assign", indent);
                p1 = tree->child[0];
                p2 = tree->child[1];
                op3 = vazio;

                emitComment("-> assign: right argument", indent);
                cGen(p2);
                op2 = operandoAtual;
                emitComment("<- assign: right argument", indent);

                emitComment("-> assign: left argument", indent);
                cGen(p1);
                op1 = operandoAtual;
                emitComment("<- assign: left argument", indent);

                if(p1->kind.exp == VectorK) {
                     ultimaQuadrupla->instruction = VEC_ADDR;
                     if(ultimaQuadrupla->op2.kind == IntConst) {
                         op3.kind = IntConst;
                         op3.contents.val = ultimaQuadrupla->op2.contents.val;

                         op1 = ultimaQuadrupla->op1;
                     }
                }

                instrucaoAtual = ASN;
                insertQuad(createQuad(instrucaoAtual, op1, op2, op3));
                emitComment("<- assign", indent);

            } else {

                emitComment("-> arithmetic operator", indent);
                p1 = tree->child[0];
                p2 = tree->child[1];
                emitComment("-> arithmetic operator: left argument", indent);
                cGen(p1);
                op1 = operandoAtual;
                emitComment("<- arithmetic operator: left argument", indent);
                emitComment("-> arithmetic operator: right argument", indent);
                cGen(p2);
                op2 = operandoAtual;
                emitComment("<- arithmetic operator: right argument", indent);

                switch (tree->attr.op) {
                    case PLUS:
                        emitComment("arithmetic operator: +", indent);
                        instrucaoAtual = ADD;
                        break;
                    case MINUS:
                        emitComment("arithmetic operator: -", indent);
                        instrucaoAtual = SUB;
                        break;
                    case TIMES:
                        emitComment("arithmetic operator: *", indent);
                        instrucaoAtual = MULT;
                        break;
                    case OVER:
                        emitComment("arithmetic operator: /", indent);
                        instrucaoAtual = DIV;
                        break;
                    case LT:
                        emitComment("relational operator: <", indent);
                        instrucaoAtual = LTHAN;
                        break;
                    case LTEQ:
                        emitComment("relational operator: <=", indent);
                        instrucaoAtual = LET;
                        break;
                    case GT:
                        emitComment("relational operator: >", indent);
                        instrucaoAtual = GTHAN;
                        break;
                    case GTEQ:
                        emitComment("relational operator: >=", indent);
                        instrucaoAtual = GET;
                        break;
                    case EQ:
                        emitComment("relational operator: ==", indent);
                        instrucaoAtual = EQUAL;
                        break;
                    case NEQ:
                        emitComment("relational operator: !=", indent);
                        instrucaoAtual = NE;
                        break;
                    default:
                        emitComment("BUG: Unknown operator", indent);
                        break;
                }

                operandoAtual = createTemporaryOperand();
                insertQuad(createQuad(instrucaoAtual, op1, op2, operandoAtual));
                emitComment("<- Operator", indent);

            }
            break;
    default:
        break;
    }
    UNINDENT;
}

static void cGen(TreeNode * tree) {
    if (tree != NULL) {
        switch (tree->nodekind) {
            case StmtK:
                genStmt(tree);
                break;
            case ExpK:
                genExp(tree);
                break;
            default:
                break;
        }
        if(paramHead == NULL) {
            cGen(tree->sibling);
        } else {
            if(paramHead->count == 0) {
                cGen(tree->sibling);
            }
        }
    }
}

void verificaFimInstrucaoAnterior(void) {
    if(head != NULL) {
        Quadruple temp = head;
        while(temp->next != NULL) {
            temp = temp->next;
        }
        if(temp->instruction != RTN) {
            insertQuad(createQuad(RTN, vazio, vazio, vazio));
        }
    }
}


void codeGen(TreeNode * syntaxTree, char * codefile) {
    char * s = (char *) malloc(strlen(codefile) + 7);
    strcpy(s, "File: ");
    strcat(s, codefile);
    emitComment("C- compilation for the intermediate code", indent);
    emitComment(s, indent);
    /* Antes de iniciar, prepara o operando vazio */
    preparaVazio();
    cGen(syntaxTree);
    /* finish */
    emitComment("Fim da execução.", indent);
    insertQuad(createQuad(HLT, vazio, vazio, vazio));
    emitCode("\n********** Intermediate Code **********\n");
    printIntermediateCode();
}

void printIntermediateCode() {
    Quadruple q = head;
    char quad[100];
    while(q != NULL) {
        sprintf(quad, "%d: (", q->linha);
        strcat(quad, toString(q->instruction));
        if(q->op1.kind == String) {
            strcat(quad, ", ");
            strcat(quad, q->op1.contents.variable.name);
        } else if(q->op1.kind == IntConst) {
            sprintf(tempString, ", %d", q->op1.contents.val);
            strcat(quad,tempString);
        } else {
            strcat(quad, ", _");
        }

        if(q->op2.kind == String) {
            strcat(quad, ", ");
            strcat(quad, q->op2.contents.variable.name);
        } else if(q->op2.kind == IntConst) {
            sprintf(tempString, ", %d", q->op2.contents.val);
            strcat(quad,tempString);
        } else {
            strcat(quad, ", _");
        }

        if(q->op3.kind == String) {
            strcat(quad, ", ");
            strcat(quad, q->op3.contents.variable.name);
            strcat(quad, ")");
        } else if(q->op3.kind == IntConst) {
            sprintf(tempString, ", %d", q->op3.contents.val);
            strcat(quad,tempString);
            strcat(quad, ")");
        } else {
            strcat(quad, ", _)");
        }
        emitCode(quad);
        q = q->next;
    }
}

void pushLocation(LocationStack ls) {
    if(locationHead == NULL) {
        locationHead = ls;
        locationHead->next = NULL;
    } else {
        ls->next = locationHead;
        locationHead = ls;
    }
}

void popLocation() {
    if(locationHead != NULL) {
        LocationStack ls = locationHead;
        locationHead = locationHead->next;
        free(ls);
        ls = NULL;
    }
}

LocationStack createLocation(Quadruple * quad) {
    LocationStack ls = (LocationStack) malloc(sizeof(struct Location));
    ls->quad = quad;
    ls->next = NULL;
    return ls;
}

void updateLocation(Operand op) {
    Quadruple q = *locationHead->quad;
    if(q->instruction != JPF) {
        q->op1 = op;
    } else {
        q->op2 = op;
    }
    *locationHead->quad = q;
}

void pushParam(int * count) {
    ParamStack ps = (ParamStack) malloc(sizeof(struct Param));
    ps->count = count;
    ps->next = NULL;
    if(paramHead == NULL) {
        paramHead = ps;
    } else {
        ps->next = paramHead;
        paramHead = ps;
    }
}

void popParam(void) {
    if(paramHead != NULL) {
        ParamStack ps = paramHead;
        paramHead = paramHead->next;
        free(ps);
        ps = NULL;
    }
}

Quadruple createQuad(InstructionKind instruction, Operand op1, Operand op2, Operand op3) {
    Quadruple q = (Quadruple) malloc(sizeof(struct Quad));
    q->instruction = instruction;
    q->op1 = op1;
    q->op2 = op2;
    q->op3 = op3;
    q->linha = ++linha;
    q->next = NULL;
    return q;
}

Quadruple * insertQuad(Quadruple q) {
    Quadruple * ptr = (Quadruple *) malloc(sizeof(struct Quad));
    if(head == NULL) {
        head = q;
        head->next = NULL;
        ptr = &head;
    } else {
        Quadruple temp = head;
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = q;
        temp->next->next = NULL;
        ptr = &temp->next;
    }
    return ptr;
}

void preparaVazio(void) {
    vazio.kind = Empty;
    vazio.contents.variable.name = NULL;
    vazio.contents.variable.scope = NULL;
}

Quadruple getCodigoIntermediario(void) {
    return head;
}
