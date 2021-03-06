#include "globals.h"
#include "util.h"

/* Procedure printToken prints a token
 * and its lexeme to the listing file
 */
void printToken( TokenType token, const char* tokenString ) {
  switch (token){
    case ELSE:
    case IF:
    case INT:
    case RETURN:
    case VOID:
    case WHILE:
      fprintf(listing, "reserved word: %s\n",tokenString);
      break;
    case PLUS: fprintf(listing,"+\n"); break;
    case MINUS: fprintf(listing,"-\n"); break;
    case TIMES: fprintf(listing,"*\n"); break;
    case OVER: fprintf(listing,"/\n"); break;
    case LT: fprintf(listing,"<\n"); break;
    case LTEQ: fprintf(listing,"<=\n"); break;
    case GT: fprintf(listing,">\n"); break;
    case GTEQ: fprintf(listing,">=\n"); break;
    case ASSIGN: fprintf(listing,":=\n"); break;
    case NEQ: fprintf(listing,"!=\n"); break;
    case EQ: fprintf(listing,"=\n"); break;
    case SEMI: fprintf(listing,";\n"); break;
    case COMMA: fprintf(listing,",\n"); break;
    case LPAREN: fprintf(listing,"(\n"); break;
    case RPAREN: fprintf(listing,")\n"); break;
    case LBRACK: fprintf(listing,"[\n"); break;
    case RBRACK: fprintf(listing,"]\n"); break;
    case LBRACE: fprintf(listing,"{\n"); break;
    case RBRACE: fprintf(listing,"}\n"); break;
    case ENDFILE: fprintf(listing,"EOF\n"); break;
    case NUM:
      fprintf(listing,"NUM, value = %s\n",tokenString);
      break;
    case ID:
      fprintf(listing,"ID, name = %s\n",tokenString);
      break;
    case ERROR:
      fprintf(listing,"ERROR: %s\n",tokenString);
      break;
    default: /* should never happen */
      fprintf(listing,"Unknown token: %d\n",token);
  }
}

/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
TreeNode * newStmtNode(StmtKind kind){
  TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = StmtK;
    t->kind.stmt = kind;
    t->lineno = lineno;
  }
  return t;
}

/* Function newExpNode creates a new expression
 * node for syntax tree construction
 */
TreeNode * newExpNode(ExpKind kind){
  TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = ExpK;
    t->kind.exp = kind;
    t->lineno = lineno;
    t->type = Void;
  }
  return t;
}

/* Function copyString allocates and makes a new
 * copy of an existing string
 */
char * copyString(char * s){
  int n;
  char * t;
  if (s==NULL) return NULL;
  n = strlen(s)+1;
  t = malloc(n);
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else strcpy(t,s);
  return t;
}

/* Variable indentno is used by printTree to
 * store current number of spaces to indent
 */
static int indentno = 0;

/* macros to increase/decrease indentation */
#define INDENT indentno+=2
#define UNINDENT indentno-=2

/* printSpaces indents by printing spaces */
static void printSpaces(void){
  int i;
  for (i=0;i<indentno;i++)
    fprintf(listing," ");
}

/* procedure printTree prints a syntax tree to the
 * listing file using indentation to indicate subtrees
 */

void printTree( TreeNode * tree ) {
   int i;
   INDENT;
   while (tree != NULL) {
       printSpaces();
       if (tree->nodekind == StmtK) {
           switch (tree->kind.stmt) {
               case IntegerK: fprintf(listing, "int\n"); break;
               case VoidK: fprintf(listing, "void\n"); break;
               case IfK: fprintf(listing, "if\n"); break;
               case ElseK:	fprintf(listing, "else\n");	break;
               case ReturnK: fprintf(listing, "return\n");	break;
               case WhileK: fprintf(listing, "while\n"); break;
               case CompK: fprintf(listing, "Compound Declaration:\n");	break;
           }
       } else if (tree->nodekind == ExpK) {
           switch (tree->kind.exp) {
               case OpK: fprintf(listing, "Op: "); printToken(tree->attr.op,"\0"); break;
               case ConstK: fprintf(listing, "Const: %d\n", tree->attr.val); break;
               case CallK: fprintf(listing, "Function Call %s\n", tree->attr.name); break;
               case IdK: fprintf(listing, "ID: %s\n", tree->attr.name); break;
               case VectorK: fprintf(listing, "Vector: %s\n", tree->attr.name); break;
               case FunctionK: fprintf(listing, "Function: %s\n", tree->attr.name); break;
               default: fprintf(listing,"ExpNode Unknown\n"); break;
           }
       } else {
           fprintf(listing, "Unknown type\n");
       }
       for (i = 0; i < MAXCHILDREN; i++) {
           printTree(tree->child[i]);
       }
       tree = tree->sibling;
   }
   UNINDENT;
}
