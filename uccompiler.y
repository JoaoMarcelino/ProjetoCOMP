/*
uc2018293871 Sofia Silva
uc2018279700 João Marcelino
*/

%{
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    #include "y.tab.h"
    int yylex(void);
    void yyerror (const char *s);
    int main(void);

    #define SIZE 100

    typedef struct  node*nodeptr;

    typedef struct node{
        char *id;
        char *type;
        nodeptr nodeNext;
        nodeptr nodeBrother;
        int value;
    }node;


    nodeptr createNode(){
        nodeptr aux;
        aux=(nodeptr)malloc(sizeof(nodeptr));

        if (aux!=NULL){
            aux->id=malloc(SIZE*sizeof(char));
            aux->type=malloc(SIZE*sizeof(char));
            aux->nodeNext=NULL;
            aux->nodeBrother= NULL;
        }
        return aux;
    }

    nodeptr insertNode(nodeptr node, char *id, char *type){
        nodeptr aux = createNode();

        aux->id = id;
        aux->type= type;
        /* Adicionar no inicio */
        aux->nodeBrother= node;
        aux->nodeNext= NULL;

        return aux;
    }

    void freeTree(nodeptr first){
        nodeptr aux=first;
        nodeptr aux2;
        while (aux->nodeNext!=NULL){
            free(aux->id);
            free(aux->type);
            freeTree(aux->nodeBrother);
            aux2=aux->nodeNext;
            free(aux);
            aux=aux2;
        }
        free(aux2);
    }


    void printTree(nodeptr node){
        nodeptr aux = node;
        int i=0;
        while (aux){
            printf("%d %s ",i++,aux->type);
            if (aux->nodeBrother){
                printTree(aux->nodeBrother);
            }
            aux=aux->nodeNext;
        }
    }

    void joinNodes(nodeptr node1, nodeptr node2){
        node1->nodeBrother = node2;
    }

    /*
    () normal
    [] opcional
    {} zero ou mais repetições
    FunctionsAndDeclarations −→ (FunctionDefinition | FunctionDeclaration | Declaration) {FunctionDefinition | FunctionDeclaration | Declaration}


FunctionDefinition −→ TypeSpec FunctionDeclarator FunctionBody
    
    FunctionBody −→ LBRACE [DeclarationsAndStatements] RBRACE
    DeclarationsAndStatements −→ Statement DeclarationsAndStatements | Declaration DeclarationsAndStatements | Statement | Declaration
FunctionDeclaration −→ TypeSpec FunctionDeclarator SEMI
    
    FunctionDeclarator −→ ID LPAR ParameterList RPAR
    ParameterList −→ ParameterDeclaration {COMMA ParameterDeclaration}
    ParameterDeclaration −→ TypeSpec [ID]

Declaration −→ TypeSpec Declarator {COMMA Declarator} SEMI
    TypeSpec −→ CHAR | INT | VOID | SHORT | DOUBLE
    Declarator −→ ID [ASSIGN Expr]
    
    Statement −→ [Expr] SEMI
    Statement −→ LBRACE {Statement} RBRACE
    Statement −→ IF LPAR Expr RPAR Statement [ELSE Statement]
    Statement −→ WHILE LPAR Expr RPAR Statement
    Statement −→ RETURN [Expr] SEMI
    
    Expr −→ Expr (ASSIGN | COMMA) Expr
    Expr −→ Expr (PLUS | MINUS | MUL | DIV | MOD) Expr
    Expr −→ Expr (OR | AND | BITWISEAND | BITWISEOR | BITWISEXOR) Expr
    Expr −→ Expr (EQ | NE | LE | GE | LT | GT) Expr
    Expr −→ (PLUS | MINUS | NOT) Expr
    Expr −→ ID LPAR [Expr {COMMA Expr}] RPAR
    Expr −→ ID | INTLIT | CHRLIT | REALLIT | LPAR Expr RPAR

    */
%}

%union{
    struct node *node;
    char* id;
}

%type <node> FunctionsAndDec
%type <node> FunctionsAndDeclarations
%type <node> FuctionsAndDecExtra
%type <node> TypeSpec
%type <node> FunctionDeclarator
%type <node> ParameterList
%type <node> ParameterExtra
%type <node> ParameterDeclaration
%type <node> FunctionHelper
%type <node> FunctionBody
%type <node> DeclarationsAndStatements
%type <node> DeclarationsAndStatementsRep
%type <node> Declaration
%type <node> DeclarationExtra
%type <node> Declarator
%type <node> Statement
%type <node> StatementBrace
%type <node> StatementElse
%type <node> StatementReturn
%type <node> Expr







%token CHAR
%token ELSE
%token WHILE
%token IF
%token INT
%token SHORT
%token DOUBLE
%token RETURN
%token VOID
%token BITWISEAND
%token BITWISEOR
%token BITWISEXOR
%token AND
%token ASSIGN
%token MUL
%token COMMA
%token DIV
%token EQ
%token GE
%token GT
%token LBRACE
%token LE
%token LPAR
%token LT
%token MINUS
%token MOD
%token NE
%token NOT
%token OR
%token PLUS
%token RBRACE
%token RPAR
%token SEMI
%token RESERVED

%token <id> CHRLIT
%token <id> REALLIT
%token <id> INTLIT
%token <id> ID



%right "then" ELSE

%right ASSIGN
%left COMMA
%right EQ NE LE GE LT GT
%left PLUS MINUS NOT
%left MUL DIV MOD
%left OR AND BITWISEAND BITWISEOR BITWISEXOR
%right LPAR LBRACE


%%
FunctionsAndDec: TypeSpec FunctionsAndDeclarations                  {joinNodes($1,$2);$$=insertNode($1,NULL,"PROGRAM");printTree($$);}
    ;

FunctionsAndDeclarations: FunctionDeclarator FuctionsAndDecExtra    {joinNodes($1,$2);$$ = $1;}
    | Declaration FuctionsAndDecExtra                               {joinNodes($1,$2);$$ = $1;}
    ;

FuctionsAndDecExtra:  FunctionsAndDeclarations                      {$$ = $1;}
    |                                                               {$$ = NULL;}
    ;

TypeSpec: CHAR                                                      {$$=insertNode(NULL,NULL,"CHAR");}
    | INT                                                           {$$=insertNode(NULL,NULL,"INT");}
    | VOID                                                          {$$=insertNode(NULL,NULL,"VOID");}
    | SHORT                                                         {$$=insertNode(NULL,NULL,"SHORT");}
    | DOUBLE                                                        {$$=insertNode(NULL,NULL,"DOUBLE");}
    ;

FunctionDeclarator: ID LPAR ParameterList RPAR FunctionHelper       {joinNodes($3,$5); $$=insertNode($3, $1,"ID");}
    ;

ParameterList: TypeSpec ParameterDeclaration ParameterExtra         {joinNodes($2,$3);joinNodes($1,$2);$$ = $1;}
    ;

ParameterExtra: COMMA TypeSpec ParameterDeclaration ParameterExtra  {joinNodes($3,$4);joinNodes($2,$3);$$=insertNode($2, NULL,"COMMA");}
    |                                                               {$$ = NULL;}
    ;      

ParameterDeclaration: ID                                            {$$ = insertNode(NULL, $1,"ID");}
    |                                                               {$$ = NULL;}
    ;

FunctionHelper:   LBRACE FunctionBody RBRACE                        {$$ = $2;}
    | SEMI                                                          {$$ = NULL;}
    ;

FunctionBody: DeclarationsAndStatements                             {$$ = $1;}
    |                                                               {$$ = NULL;}
    ;

DeclarationsAndStatements: Statement DeclarationsAndStatementsRep   {joinNodes($1,$2); $$ = $1;}
	| TypeSpec Declaration DeclarationsAndStatementsRep             {joinNodes($2,$3);joinNodes($1,$2); $$ = $1;}
    ;

DeclarationsAndStatementsRep: DeclarationsAndStatements             {$$ = $1;};
    |                                                               {$$ = NULL;}
    ;

Declaration: ID Declarator DeclarationExtra                         {joinNodes($2,$3); $$=insertNode($2, $1,"ID");}
    ;

DeclarationExtra: COMMA ID Declarator DeclarationExtra              {nodeptr aux; joinNodes($3,$4); aux = insertNode($3,$2,"ID"); $$ =insertNode(aux,NULL,"COMMA"); }
    | SEMI                                                          {$$ = NULL;}
    ;

Declarator: ASSIGN Expr                                             {$$=insertNode($2,NULL,"ASSIGN");}
    |                                                               {$$ = NULL;}
    ;


Statement: Expr SEMI                                                {$$ = $1;}
    | SEMI                                                          {$$ =  NULL;}

    | LBRACE StatementBrace                                         {$$ = $2;}

    | IF LPAR Expr RPAR Statement StatementElse                     {joinNodes($5,$6); joinNodes($3,$5); $$=insertNode($3,NULL,"IF");}
    
    | WHILE LPAR Expr RPAR Statement                                {joinNodes($3,$5); $$=insertNode($3,NULL,"WHILE");}

    | RETURN StatementReturn                                        {$$=insertNode($2,NULL,"RETURN");}
    ;

StatementBrace: Statement RBRACE                                    {$$=insertNode($1,NULL,"STATEMENT");}
    | RBRACE                                                        {$$ = NULL;}
    ;

StatementElse: ELSE Statement                                       {$$=insertNode($2,NULL,"STATEMENT");}
    | %prec "then"                                                  {$$ = NULL;}
    ;

StatementReturn: SEMI                                               {$$ = NULL;}
    | Expr SEMI                                                     {$$ = $1;}
    ;

Expr: Expr ASSIGN Expr                                              {joinNodes($1,$3); $$=insertNode($1,NULL,"ASSIGN");}
    | Expr COMMA Expr                                               {joinNodes($1,$3); $$=insertNode($1,NULL,"COMMA");}
    
    | Expr PLUS Expr                                                {joinNodes($1,$3); $$=insertNode($1,NULL,"PLUS");}
    | Expr MINUS Expr                                               {joinNodes($1,$3); $$=insertNode($1,NULL,"MINUS");}
    | Expr MUL Expr                                                 {joinNodes($1,$3); $$=insertNode($1,NULL,"MUL");}
    | Expr DIV Expr                                                 {joinNodes($1,$3); $$=insertNode($1,NULL,"DIV");}
    | Expr MOD Expr                                                 {joinNodes($1,$3); $$=insertNode($1,NULL,"MOD");}

    | Expr OR Expr                                                  {joinNodes($1,$3); $$=insertNode($1,NULL,"OR");}
    | Expr AND Expr                                                 {joinNodes($1,$3); $$=insertNode($1,NULL,"AND");}
    | Expr BITWISEAND Expr                                          {joinNodes($1,$3); $$=insertNode($1,NULL,"BITWISEAND");}
    | Expr BITWISEOR Expr                                           {joinNodes($1,$3); $$=insertNode($1,NULL,"BITWISEOR");}
    | Expr BITWISEXOR Expr                                          {joinNodes($1,$3); $$=insertNode($1,NULL,"BITWISEXOR");}

    | Expr EQ Expr                                                  {joinNodes($1,$3); $$=insertNode($1,NULL,"EQ");}
    | Expr NE Expr                                                  {joinNodes($1,$3); $$=insertNode($1,NULL,"NE");}
    | Expr LE Expr                                                  {joinNodes($1,$3); $$=insertNode($1,NULL,"LE");}
    | Expr GE Expr                                                  {joinNodes($1,$3); $$=insertNode($1,NULL,"GE");}
    | Expr LT Expr                                                  {joinNodes($1,$3); $$=insertNode($1,NULL,"LT");}
    | Expr GT Expr                                                  {joinNodes($1,$3); $$=insertNode($1,NULL,"GT");}

    | PLUS Expr                                                     {$$=insertNode($2,NULL,"PLUS");}
    | MINUS Expr                                                    {$$=insertNode($2,NULL,"MINUS");}
    | NOT Expr                                                      {$$=insertNode($2,NULL,"NOT");}

    | ID                                                            {$$=insertNode(NULL,$1,"ID");}
    | INTLIT                                                        {$$=insertNode(NULL,$1,"INTLIT");}
    | CHRLIT                                                        {$$=insertNode(NULL,$1,"CHRLIT");}
    | REALLIT                                                       {$$=insertNode(NULL,$1,"REALLIT");}
    | ID LPAR Expr RPAR                                             {$$=insertNode($3,$1,"ID");}
    | LPAR Expr RPAR                                                {$$ = $2;}
    ;

%%


