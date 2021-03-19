%{
#define YYPARSER /* distinguishes Yacc output from other code files */

#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"

#define YYSTYPE TreeNode *
static char * savedName; /* for use in assignments */
static int savedLineNo;  /* ditto */
static TreeNode * savedTree; /* stores syntax tree for later return */
static int yylex(void);
static int yyerror(char * message);
static TreeNode * insertIOFunctions();

%}

%token IF ELSE WHILE RETURN
%token ID NUM
%token INT VOID
%token PLUS MINUS TIMES OVER LT LTEQ GT GTEQ ASSIGN NEQ EQ SEMI COMMA LPAREN
RPAREN LBRACK RBRACK LBRACE RBRACE
%token ERROR
%nonassoc RPAREN
%nonassoc ELSE

%% /* Grammar for C- */

program    		: declaration_list { savedTree = insertIOFunctions();
                                         savedTree->sibling->sibling = $1;
                                       }
           		;
declaration_list	: declaration_list declaration
                 	{
				YYSTYPE t = $1;
                   		if (t != NULL) {
					while (t->sibling != NULL) {
						 t = t->sibling;
					}
                    	 		t->sibling = $2;
                    			$$ = $1;
				} else {
					$$ = $2;
				}
                 	}
            		| declaration  { $$ = $1; }
            		;
declaration     : var_declaration { $$ = $1; }
            		| fun_declaration { $$ = $1; }
            		;
var_declaration     	: type_specifier id SEMI
			{
				$$ = $1;
				$$->child[0] = $2;
				$$->child[0]->type = $$->type;
        $$->child[0]->varMemK = LocalK;
			}
            		| type_specifier id LBRACK num RBRACK SEMI
			{
				$$ = $1;
				$$->child[0] = $2;
				$$->child[0]->kind.exp = VectorK;
				$$->child[0]->type = $$->type;
        $$->child[0]->varMemK = LocalK;
				$$->child[0]->child[0] = $4;
				$$->child[0]->child[0]->type = Integer;
			}
            		;
type_specifier 	: INT
			{
				$$ = newStmtNode(IntegerK);
				$$->attr.name = "int";
				$$->type = Integer;
			}
                 	| VOID
			{
				$$ = newStmtNode(VoidK);
				$$->attr.name = "void";
				$$->type = Void;
			}
            		;
fun_declaration		: type_specifier id LPAREN params RPAREN compound_declaration
			{
				$$ = $1;
				$$->child[0] = $2;
				$$->child[0]->type = $$->type;
				$$->child[0]->kind.exp = FunctionK;
                $$->child[0]->varMemK = FUNCTIONK;
				$$->child[0]->child[0] = $4;
				$$->child[0]->child[1] = $6;
			}
			;
params			: param_list { $$ = $1; }
			| VOID { $$ = NULL; }
			;
param_list 		: param_list COMMA param
			{
				YYSTYPE t = $1;
				if (t != NULL) {
					while (t->sibling != NULL) {
						t = t->sibling;
					}
					t->sibling = $3;
					$$ = $1;
				} else {
					$$ = $3;
				}
			}
			| param { $$ = $1; }
			;
param 			: type_specifier id
			{
				$$ = $1;
				$$->child[0] = $2;
				$$->child[0]->type = $$->type;
                $$->child[0]->varMemK = ParamK;
			}
			| type_specifier id LBRACK RBRACK
			{
				$$ = $1;
				$$->child[0] = $2;
				$$->child[0]->type = $$->type;
                $$->child[0]->varMemK = ParamK;
                $$->child[0]->kind.exp = VectorK;
			}
			;
compound_declaration		: LBRACE local_declaration statement_list RBRACE
			{
				$$ = newStmtNode(CompK);
				$$->child[0] = $2;
				$$->child[1] = $3;
			}
			;
local_declaration 	: local_declaration var_declaration
			{
				YYSTYPE t = $1;
				if (t != NULL) {
					while (t->sibling != NULL) {
						t = t->sibling;
					}
					t->sibling = $2;
					$$ = $1;
				} else {
					$$ = $2;
				}
			}
			| null { $$ = $1; }
			;
statement_list 	: statement_list statement
			{
				YYSTYPE t = $1;
				if (t != NULL) {
					while (t->sibling != NULL) {
						t = t->sibling;
					}
					t->sibling = $2;
					$$ = $1;
				} else {
					$$ = $2;
				}
			}
			| null { $$ = $1; }
			;
statement 	: expression_declaration { $$ = $1; }
			| compound_declaration { $$ = $1; }
			| selection_declaration { $$ = $1; }
			| iteration_declaration { $$ = $1; }
			| return_declaration { $$ = $1; }
			;
expression_declaration 		: expression SEMI { $$ = $1; }
			| SEMI { $$ = NULL; }
			;
selection_declaration	 	: IF LPAREN expression RPAREN statement
			{
				$$ = newStmtNode(IfK);
				$$->child[0] = $3;
				$$->child[1] = $5;
			}
			| IF LPAREN expression RPAREN statement ELSE statement
			{
				$$ = newStmtNode(IfK);
				$$->child[0] = $3;
				$$->child[1] = $5;
				$$->child[2] = $7;
			}
			;
iteration_declaration 		: WHILE LPAREN expression RPAREN statement
			{
				$$ = newStmtNode(WhileK);
				$$->child[0] = $3;
				$$->child[1] = $5;
			}
			;
return_declaration 		: RETURN SEMI
			{
				$$ = newStmtNode(ReturnK);
			}
			| RETURN expression SEMI
			{
				$$ = newStmtNode(ReturnK);
				$$->child[0] = $2;
			}
			;
expression 		: var ASSIGN expression
			{
				$$ = newExpNode(OpK);
				$$->attr.op = ASSIGN;
				$$->child[0] = $1;
				$$->child[1] = $3;
			}
			| simple_expression { $$ = $1; }
			;
var 			: id
			{
				$$ = $1;
                $$->type = Integer;
                $$->varAccess = AccessingK;
			}
			| id LBRACK expression RBRACK
			{
				$$ = $1;
				$$->kind.exp = VectorK;
                $$->type = Integer;
                $$->varAccess = AccessingK;
				$$->child[0] = $3;
			}
			;
simple_expression 	: sum_expression relation sum_expression
			{
				$$ = $2;
				$$->child[0] = $1;
				$$->child[1] = $3;
			}
			| sum_expression
			{
				$$ = $1;
			}
			;
relation 	: LTEQ
			{
				$$ = newExpNode(OpK);
				$$->attr.op = LTEQ;
			}
			| LT
			{
				$$ = newExpNode(OpK);
				$$->attr.op = LT;
			}
			| GT
			{
				$$ = newExpNode(OpK);
				$$->attr.op = GT;
			}
			| GTEQ
			{
				$$ = newExpNode(OpK);
				$$->attr.op = GTEQ;
			}
			| EQ
			{
				$$ = newExpNode(OpK);
				$$->attr.op = EQ;
			}
			| NEQ
			{
				$$ = newExpNode(OpK);
				$$->attr.op = NEQ;
			}
			;
sum_expression 		: sum_expression sum term
			{
				$$ = $2;
				$$->child[0] = $1;
				$$->child[1] = $3;
			}
			| term { $$ = $1; }
			;
sum		: PLUS
			{
				$$ = newExpNode(OpK);
				$$->attr.op = PLUS;
			}
			| MINUS
			{
				$$ = newExpNode(OpK);
				$$->attr.op = MINUS;
			}
			;
term 			: term times factor
			{
				$$ = $2;
				$$->child[0] = $1;
				$$->child[1] = $3;
			}
			| factor { $$ = $1; }
			;
times 		: TIMES
			{
				$$ = newExpNode(OpK);
				$$->attr.op = TIMES;
			}
			| OVER
			{
				$$ = newExpNode(OpK);
				$$->attr.op = OVER;
			}
			;
factor 			: LPAREN expression RPAREN { $$ = $2; }
			| var { $$ = $1; }
			| activation { $$ = $1; }
			| num { $$ = $1; }
			;
activation 		: var LPAREN args RPAREN
			{
				$$ = $1;
				$$->kind.exp = CallK;
				$$->child[0] = $3;
			}
			;
args 			: arg_list { $$ = $1; }
			|   null { $$ = $1; }
			;
arg_list 		: arg_list COMMA expression
			{
				YYSTYPE t = $1;
				if (t != NULL) {
					while (t->sibling != NULL) {
						t = t->sibling;
					}
					t->sibling = $3;
					$$ = $1;
				} else {
					$$ = $3;
				}
			}
			| expression { $$ = $1; }
			;
id			: ID
			{
				$$ = newExpNode(IdK);
				$$->attr.name = copyString(tokenString);
                $$->varAccess = DeclaringK;
			}
			;
num			: NUM
			{
				$$ = newExpNode(ConstK);
				$$->attr.val = atoi(tokenString);
			}
			;
null			: { $$ = NULL; }
			;
%%

int yyerror(char * message)
{ fprintf(listing,"Syntax error at line %d: %s\n",lineno,message);
  fprintf(listing,"Current token: ");
  printToken(yychar,tokenString);
  Error = TRUE;
  return 0;
}

/* yylex calls getToken to make Yacc/Bison output
 * compatible with ealier versions of the TINY scanner
 */
static int yylex(void)
{ return getToken(); }

TreeNode * parse(void)
{ yyparse();
  return savedTree;
}

/* Insere as funções input e output na árvore sintática */
static TreeNode * insertIOFunctions() {
    /*********** Output **********/
    TreeNode * output = newExpNode(FunctionK);
    output->attr.name = "output";
    output->type = Void;
    output->varMemK = FUNCTIONK;
    output->lineno = 0;

    TreeNode * voidNode = newStmtNode(VoidK);
    voidNode->attr.name = "void";
    voidNode->type = Void;
    voidNode->child[0] = output;

    /********** Input **********/
    TreeNode * input = newExpNode(FunctionK);
    input->attr.name = "input";
    input->type = Integer;
    input->varMemK = FUNCTIONK;
    input->lineno = 0;

    TreeNode * intNode = newStmtNode(IntegerK);
    intNode->attr.name = "int";
    intNode->type = Integer;
    intNode->child[0] = input;

    /********** Adicionando na árvore **********/
    intNode->sibling = voidNode;
    return intNode;
}
