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
        nodeptr nodeChild;
        int value;
    }node;


    nodeptr createNode(){
        nodeptr aux;
        aux=(nodeptr)malloc(sizeof(nodeptr));

        if (aux!=NULL){
            aux->id=malloc(SIZE*sizeof(char));
            aux->type=malloc(SIZE*sizeof(char));
            aux->nodeNext=NULL;
            aux->nodeChild= NULL;
        }
        return aux;
    }

    nodeptr insertNode(nodeptr node, char *id, char *type){
        nodeptr aux = createNode();

        aux->id = id;
        aux->type= type;
        /* Adicionar no inicio */
        aux->nodeChild= node;
        aux->nodeNext= NULL;

        return aux;
    }

    void freeTree(nodeptr first){
        nodeptr aux=first;
        nodeptr aux2;
        while (aux->nodeNext!=NULL){
            free(aux->id);
            free(aux->type);
            freeTree(aux->nodeChild);
            aux2=aux->nodeNext;
            free(aux);
            aux=aux2;
        }
        free(aux2);
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
FunctionsAndDec: TypeSpec FunctionsAndDeclarations {}
    ;

FunctionsAndDeclarations: FunctionDeclarator FuctionsAndDecExtra    {}
    |   Declaration FuctionsAndDecExtra                             {}
    ;

FuctionsAndDecExtra:  FunctionsAndDeclarations                      {}
    |                                                               {}
    ;

TypeSpec: CHAR                                                      {}
    | INT                                                           {}
    | VOID                                                          {}
    | SHORT                                                         {}
    | DOUBLE                                                        {}
    ;

FunctionDeclarator: ID LPAR ParameterList RPAR FunctionHelper       {}
    ;

ParameterList: TypeSpec ParameterDeclaration ParameterExtra         {}
    ;

ParameterExtra: COMMA TypeSpec ParameterDeclaration ParameterExtra  {}
    |                                                               {}
    ;      
ParameterDeclaration: ID                                            {}
    |                                                               {}
    ;

FunctionHelper:   LBRACE FunctionBody RBRACE                        {}
    | SEMI                                                          {}
    ;

FunctionBody: DeclarationsAndStatements                             {}
    |                                                               {}
    ;

DeclarationsAndStatements: Statement DeclarationsAndStatementsRep   {}
	| TypeSpec Declaration DeclarationsAndStatementsRep             {}
    ;

DeclarationsAndStatementsRep: DeclarationsAndStatements             {}
    |                                                               {}
    ;

Declaration: ID Declarator DeclarationExtra                         {}
    ;

DeclarationExtra: COMMA ID Declarator DeclarationExtra              {}
    | SEMI                                                          {}
    ;

Declarator: ASSIGN Expr                                             {}
    |                                                               {}
    ;


Statement: Expr SEMI {}
    | SEMI  {}

    | LBRACE StatementBrace {}

    | IF LPAR Expr RPAR Statement StatementElse {}
    
    | WHILE LPAR Expr RPAR Statement {}

    | RETURN StatementReturn {}
    ;

StatementBrace: Statement RBRACE {}
    | RBRACE {}
    ;

StatementElse: ELSE Statement   {}
    | %prec "then"              {}
    ;

StatementReturn: SEMI {}
    | Expr SEMI {}
    ;

Expr: Expr ASSIGN Expr {}
    | Expr COMMA Expr {}
    
    | Expr PLUS Expr    {}
    | Expr MINUS Expr   {}
    | Expr MUL Expr     {}
    | Expr DIV Expr     {}
    | Expr MOD Expr     {}

    | Expr OR Expr          {}
    | Expr AND Expr         {}
    | Expr BITWISEAND Expr  {}
    | Expr BITWISEOR Expr   {}
    | Expr BITWISEXOR Expr  {}

    | Expr EQ Expr          {}
    | Expr NE Expr          {}
    | Expr LE Expr          {}
    | Expr GE Expr          {}
    | Expr LT Expr          {}
    | Expr GT Expr          {}

    | PLUS Expr             {}
    | MINUS Expr            {}
    | NOT Expr              {}

    | ID                {}
    | INTLIT            {}
    | CHRLIT            {}
    | REALLIT           {}
    | ID LPAR Expr RPAR {}
    | LPAR Expr RPAR    {}
    ;

%%


