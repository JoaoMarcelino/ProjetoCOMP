/*
uc2018293871 Sofia Silva
uc2018279700 João Marcelino
*/

%{
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include "y.tab.h"
    #define SIZE 100

    int yylex(void);
    int main(void);
    void yyerror (char *s);
    

    extern int treePrint;
	extern int SintaxErrors;
    extern int nline,ncol;
    extern char* yytext;
    extern int yyleng; 
    extern int comment,comcol,comline;


    int hasStatementList =0;
    

    typedef struct  node *nodeptr;

    typedef struct node{
        char *id;
        char *type;
        nodeptr nodeNext;
        nodeptr nodeBrother;
        int value;
    }Node;


    nodeptr createNode(){
        nodeptr aux = (nodeptr )malloc(sizeof(Node));

        if (aux!=NULL){
            aux->id=malloc(SIZE*sizeof(char));
            aux->type=malloc(SIZE*sizeof(char));
            aux->nodeNext=NULL;
            aux->nodeBrother= NULL;
        }
        return aux;
    }

    nodeptr insertNode(nodeptr node, char *id, char *type){
        nodeptr aux = (nodeptr)malloc(sizeof(Node));
        aux->id = id;
        aux->type= type;
        /* Adicionar no inicio */
        aux->nodeBrother= NULL;
        aux->nodeNext= node;

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

    /* IF statementlist tiver amis do que 2 statements mostrar esse node especifico*/
    
    /*
    void printTree(nodeptr node){
        nodeptr aux = node;
        int i=0;
        while (aux){
            if (aux->nodeNext){
                printf("%d %s %s\nnext->",i++,aux->type, aux->id);
                printTree(aux->nodeNext);
            }
            else if (aux->nodeBrother){
                printf("%d %s %s\nbrother->",i++,aux->type, aux->id);
            }
            else{
                printf("%d %s %s\n",i++,aux->type, aux->id);
            }
            aux=aux->nodeBrother;
        }
    }


    else if(strcmp(aux->type,"StatList")==0){
                //print de StatLists
                if (needsStatList(aux->nodeNext)){
                     printPontos(nPontos);
                    printf("%s \n",aux->type);

                }else{
                    //StatLists Redundantes
                    nPontos-=2;
                }

            }else if (strcmp(aux->type,"Statement")==0){
                //Statements
                nPontos-=2;
            }




    
    */
    
    int needsStatList(nodeptr node){
        nodeptr aux= node->nodeNext;
        int count=0;
        while(aux){
            if(strcmp(aux->type,"Else") && strcmp(aux->type,"Null") ){
                count++;    
            }
            if (count==2){
                return 1;
            }
            aux= aux->nodeBrother;
        }
        return 0;
    }


    void printPontos(int num){
        int i=0;
        //printf("%.2d",num);
        for(;i<num;i++){
            printf(".");
        }
    }
    
    void printTree(nodeptr node, int nPontos){
        nodeptr aux =node;
        int check =0;

         while (aux){
            if(aux->id){
                //print de Ids
                printPontos(nPontos);
                printf("%s(%s)\n",aux->type, aux->id);

            }
            else if(!strcmp(aux->type,"Else") ){

            }
            else if(!strcmp(aux->type,"StatList")){
                if (needsStatList(aux)){
                    printPontos(nPontos);
                    printf("%s\n",aux->type);
                }
                else{
                    if(!check){
                        nPontos -=2;
                        check=1;
                    }
                    
                }
            }
            else{
                printPontos(nPontos);
                printf("%s\n",aux->type);
            }

            if (aux->nodeNext){
                printTree(aux->nodeNext, nPontos + 2);
            }
            aux=aux->nodeBrother;
        }
    }


    void joinNodes(nodeptr node1, nodeptr node2){
        nodeptr aux = node1;
        if(aux){

            while(aux->nodeBrother){
                aux=aux->nodeBrother;
            }
            aux->nodeBrother = node2;
        }else if(node2){
            node1 = node2;
        }

    }

    nodeptr checkFuncHelper(nodeptr node){

        nodeptr aux = node;
        int i =0;
        while(i!=3){
            aux=aux->nodeBrother;
            i+=1;
        }
        if(aux){
            return insertNode(node,NULL, "FuncDefinition");
        }else{
            return insertNode(node,NULL, "FuncDeclaration");
        }
    }

    nodeptr DeclarationFunc(nodeptr main,nodeptr typespec, nodeptr declarations){
        nodeptr aux= declarations;
        nodeptr node;
        nodeptr typeaux;
        char * type = typespec->type;
        while(aux){
            //printf("%p, %p, %p\n",main, declarations,node);
            typeaux = insertNode(NULL,NULL,type);
            joinNodes(typeaux, aux->nodeNext);
            node = insertNode(typeaux, NULL, "Declaration");
            if (main)
                joinNodes(main, node);
            else main = node;
            
            aux=aux->nodeBrother;
        }
        return main;
    }
    /*Declaration:TypeSpec Declarator DeclarationExtra                    {joinNodes($1,$2);$$ = insertNode($1,NULL,"Declaration"); joinNodes($$,$3);} 
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



        
    %right ASSIGN
    %left COMMA
    %right EQ NE LE GE LT GT
    %left PLUS MINUS NOT
    %left MUL DIV MOD
    %left OR AND BITWISEAND BITWISEOR BITWISEXOR
    %right LPAR LBRACE

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
%type <node> StatementList
%type <node> Statement
%type <node> StatementBrace
%type <node> StatementElse
%type <node> StatementReturn
%type <node> Expr



%token <id> CHRLIT
%token <id> REALLIT
%token <id> INTLIT
%token <id> ID


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


%right "then" ELSE

%left COMMA
%right ASSIGN
%left OR
%left AND 
%left BITWISEOR
%left BITWISEXOR
%left BITWISEAND
%left EQ NE 
%left LE GE LT GT
%left PLUS MINUS
%left MUL DIV MOD
%right NOT 
%left RPAR LPAR




%%
FunctionsAndDec: FunctionsAndDeclarations                  {$$ = insertNode($1,NULL,"Program");if(treePrint)printTree($$,0);}
    ;

FunctionsAndDeclarations: TypeSpec FunctionDeclarator FuctionsAndDecExtra    {joinNodes($1,$2);$$ = checkFuncHelper($1);joinNodes($$, $3);}
    | Declaration FuctionsAndDecExtra                               {joinNodes($1,$2);$$=$1;}
    | error SEMI FuctionsAndDecExtra                                {$$ = insertNode(NULL,NULL,NULL);}
    ;

FuctionsAndDecExtra: FunctionsAndDeclarations                       {$$ = $1;}
    |                                                               {$$ = NULL;}
    ;

TypeSpec: CHAR                                                      {$$ = insertNode(NULL,NULL,"Char");}
    | INT                                                           {$$ = insertNode(NULL,NULL,"Int");}
    | VOID                                                          {$$ = insertNode(NULL,NULL,"Void");}
    | SHORT                                                         {$$ = insertNode(NULL,NULL,"Short");}
    | DOUBLE                                                        {$$ = insertNode(NULL,NULL,"Double");}
    ;

FunctionDeclarator: ID LPAR ParameterList RPAR FunctionHelper       {nodeptr aux = insertNode($3,NULL,"ParamList");joinNodes(aux,$5); $$ = insertNode(NULL, $1,"Id");joinNodes($$,aux);}
    ;

ParameterList: TypeSpec ParameterDeclaration ParameterExtra         {joinNodes($1,$2); $$ = insertNode($1, NULL,"ParamDeclaration"); joinNodes($$,$3);}
    ;

ParameterExtra: COMMA TypeSpec ParameterDeclaration ParameterExtra  { joinNodes($2,$3); $$ = insertNode($2, NULL,"ParamDeclaration");joinNodes($$,$4);}
    |                                                               {$$ = NULL;}
    ;      

ParameterDeclaration: ID                                            {$$ = insertNode(NULL,$1,"Id");}
    |                                                               {$$ = NULL;}
    ;

FunctionHelper:   LBRACE FunctionBody RBRACE                        { $$ = insertNode($2,NULL, "FuncBody");}
    | SEMI                                                          { $$ = NULL;}
    ;

FunctionBody: DeclarationsAndStatements                             {$$=$1; }
    |                                                               {$$ = NULL;}
    ;

DeclarationsAndStatements: StatementList DeclarationsAndStatementsRep { joinNodes($1,$2);$$ =  $1;}
	| Declaration DeclarationsAndStatementsRep                      {joinNodes($1,$2);$$=$1;}
    
    ;

DeclarationsAndStatementsRep: DeclarationsAndStatements             {$$ = $1;};
    |                                                               {$$ = NULL;}
    ;

Declaration:TypeSpec Declarator DeclarationExtra                    {joinNodes($1,$2);$$ = insertNode($1,NULL,"Declaration");nodeptr aux=NULL; aux=DeclarationFunc(aux, $1, $3);joinNodes($$,aux);}
    | TypeSpec error SEMI                                           {$$ = insertNode(NULL,NULL,NULL);}
    ;

DeclarationExtra: COMMA Declarator DeclarationExtra                 {$2=insertNode($2,NULL,"Declarator");joinNodes($2,$3);$$=$2;}
    | SEMI                                                          {$$ = NULL;}
    ;

Declarator:ID ASSIGN Expr                                           {nodeptr aux = insertNode(NULL, $1,"Id"); joinNodes(aux, $3); $$ = aux;}
    | ID                                                            {$$ = insertNode(NULL, $1,"Id");}
    ;

StatementList: Statement                                             {$$=insertNode($1,NULL,"StatList");}
    | error SEMI                                                    {$$ = insertNode(NULL,NULL,NULL);}
    ;

Statement: Expr SEMI                                                {$$ = $1;}
    | SEMI                                                          {$$ = insertNode(NULL,NULL,"Null");}

    | LBRACE StatementBrace                                         {$$ = $2;}
    | LBRACE RBRACE                                                 {$$ = insertNode(NULL,NULL,"Null");}

    | IF LPAR Expr RPAR StatementList StatementElse                 {joinNodes($3,$5);$3=insertNode($3,NULL,"If");joinNodes($3,$6);$$=$3;}
    
    | WHILE LPAR Expr RPAR StatementList                            {joinNodes($3, $5);$$= insertNode($3,NULL,"While");}

    | RETURN StatementReturn                                        {$$ = insertNode($2,NULL,"Return");}

    ;

StatementBrace: Statement RBRACE                                    {$$ = $1;/* Necessário Retirar Nulo quando Statement é apenas isso */}
    | Statement StatementBrace                                      {joinNodes($1,$2);$$ = $1;}
    ;


StatementElse: ELSE StatementList                                   {$$ = insertNode($2, NULL, "Else");}
    | %prec "then"                                                  {$$ = insertNode(NULL,NULL,"Null");$$= insertNode($$, NULL, "Else");}
    ;

StatementReturn: SEMI                                               {$$ = insertNode(NULL,NULL,"Null");}
    | Expr SEMI                                                     {$$ = $1;}
    ;


Expr: Expr ASSIGN Expr                                              {joinNodes($1,$3); $$ = insertNode($1,NULL,"Store");}
    | Expr COMMA Expr                                               {joinNodes($1,$3); $$ = insertNode($1, NULL,"Comma"); /* Retirar Comma as vezes*/}
    
    | Expr PLUS Expr                                                {joinNodes($1,$3); $$ = insertNode($1,NULL,"Add");}
    | Expr MINUS Expr                                               {joinNodes($1,$3); $$ = insertNode($1,NULL,"Sub");}
    | Expr MUL Expr                                                 {joinNodes($1,$3); $$ = insertNode($1,NULL,"Mul");}
    | Expr DIV Expr                                                 {joinNodes($1,$3); $$ = insertNode($1,NULL,"Div");}
    | Expr MOD Expr                                                 {joinNodes($1,$3); $$ = insertNode($1,NULL,"Mod");}

    | Expr OR Expr                                                  {joinNodes($1,$3); $$ = insertNode($1,NULL,"Or");}
    | Expr AND Expr                                                 {joinNodes($1,$3); $$ = insertNode($1,NULL,"And");}
    | Expr BITWISEAND Expr                                          {joinNodes($1,$3); $$ = insertNode($1,NULL,"BitWiseAnd");}
    | Expr BITWISEOR Expr                                           {joinNodes($1,$3); $$ = insertNode($1,NULL,"BitWiseOr");}
    | Expr BITWISEXOR Expr                                          {joinNodes($1,$3); $$ = insertNode($1,NULL,"BitWiseXor");}

    | Expr EQ Expr                                                  {joinNodes($1,$3); $$ = insertNode($1,NULL,"Eq");}
    | Expr NE Expr                                                  {joinNodes($1,$3); $$ = insertNode($1,NULL,"Ne");}
    | Expr LE Expr                                                  {joinNodes($1,$3); $$ = insertNode($1,NULL,"Le");}
    | Expr GE Expr                                                  {joinNodes($1,$3); $$ = insertNode($1,NULL,"Ge");}
    | Expr LT Expr                                                  {joinNodes($1,$3); $$ = insertNode($1,NULL,"Lt");}
    | Expr GT Expr                                                  {joinNodes($1,$3); $$ = insertNode($1,NULL,"Gt");}

    | PLUS Expr %prec NOT                                           {$$ = insertNode($2,NULL,"Plus");}
    | MINUS Expr %prec NOT                                          {$$ = insertNode($2,NULL,"Minus");}
    | NOT Expr                                                      {$$ = insertNode($2,NULL,"Not");}

    | ID                                                            {$$ = insertNode(NULL,$1,"Id");}
    | INTLIT                                                        {$$ = insertNode(NULL,$1,"IntLit");}
    | CHRLIT                                                        {$$ = insertNode(NULL,$1,"ChrLit");}
    | REALLIT                                                       {$$ = insertNode(NULL,$1,"RealLit");}
    | ID LPAR Expr RPAR                                             {nodeptr aux = insertNode(NULL,$1,"Id"); joinNodes(aux,$3); $$= insertNode(aux,NULL,"Call");}
    | ID LPAR error RPAR                                            {$$ = insertNode(NULL,NULL,NULL); ncol-=1;}
    | LPAR Expr RPAR                                                {$$ = $2;}
    | LPAR error RPAR                                               {$$ = insertNode(NULL,NULL,NULL);ncol-=1;}
    ;

%%


void yyerror (char *s) {
    int col = ncol - (int) yyleng ;
    if (col<=0){
        col=1;
    }
    

    printf ("Line %d, col %d: %s: %s\n" , nline , col ,s , yytext );
    treePrint=0;
}

