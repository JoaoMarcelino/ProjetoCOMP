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

    int isDefinition;
    int isStatement;
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
        nodeptr aux= node;
        int count=0;
        while(aux){
            if (strcmp(aux->type,"Statement")==0){
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
        if (num)
            printf("\n");
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
                printf("%s(%s)",aux->type, aux->id);

            }else if(strcmp(aux->type,"StatList")==0){
                //print de StatLists
                if (needsStatList(aux->nodeNext)){
                     printPontos(nPontos);
                    printf("%s",aux->type);

                }else{
                    //StatLists Redundantes
                    nPontos-=2;
                }

            }else if (strcmp(aux->type,"Statement")==0){
                //Statements
                if(!check){
                    nPontos-=2;
                    check=1;
                }
                
                
            }else{
                printPontos(nPontos);
                printf("%s",aux->type);
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
        if(isDefinition){
            return insertNode(node,NULL, "FuncDefinition");
        }else{
            return insertNode(node,NULL, "FuncDeclaration");
        }
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
    | TypeSpec Declaration FuctionsAndDecExtra                               {printf("FunctionsAndDeclarations\n"); joinNodes($1,$2); $$ = insertNode($1,NULL,"Declaration"); joinNodes($$,$3);}
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

FunctionDeclarator: ID LPAR ParameterList RPAR FunctionHelper       {nodeptr aux = insertNode($3,NULL,"ParamList"); joinNodes(aux,$5); $$ = insertNode(NULL, $1,"Id");joinNodes($$,aux);}
    ;

ParameterList: TypeSpec ParameterDeclaration ParameterExtra         {joinNodes($1,$2); $$ = insertNode($1, NULL,"ParamDeclaration"); joinNodes($$,$3);}
    ;

ParameterExtra: COMMA TypeSpec ParameterDeclaration ParameterExtra  { joinNodes($2,$3); $$ = insertNode($2, NULL,"ParamDeclaration");joinNodes($$,$4);}
    |                                                               {$$ = NULL;}
    ;      

ParameterDeclaration: ID                                            {$$ = insertNode(NULL,$1,"Id");}
    |                                                               {$$ = NULL;}
    ;

FunctionHelper:   LBRACE FunctionBody RBRACE                        {isDefinition=1; $$ = insertNode($2,NULL, "FuncBody");}
    | SEMI                                                          {isDefinition = 0; $$ = NULL;}
    ;

FunctionBody: DeclarationsAndStatements                             {if(isStatement)  $$ = insertNode($1,NULL,"StatList");}
    |                                                               {$$ = NULL;}
    ;

DeclarationsAndStatements: Statement DeclarationsAndStatementsRep   {isStatement=1;joinNodes($1,$2);$$=$1;}
	| TypeSpec Declaration DeclarationsAndStatementsRep             {isStatement=0; joinNodes($1,$2);$$=insertNode($1, NULL, "Declaration"); joinNodes($$,$3);}
    ;

DeclarationsAndStatementsRep: DeclarationsAndStatements             {$$ = $1;};
    |                                                               {$$ = NULL;}
    ;

Declaration: Declarator DeclarationExtra                            {joinNodes($1,$2);$$ = $1;}
    | error SEMI                                                    {printf("erro");$$ = insertNode(NULL,NULL,NULL);}
    ;

DeclarationExtra: COMMA Declarator DeclarationExtra                 {joinNodes($2,$3); $$ = $2;}
    | SEMI                                                          {$$ = NULL;}
    ;

Declarator:ID ASSIGN Expr                                           {nodeptr aux = insertNode(NULL, $1,"Id"); joinNodes(aux, $3); $$ = aux;}
    | ID                                                            {$$ = insertNode(NULL, $1,"Id");}
    ;


Statement: Expr SEMI                                                {$$ = insertNode($1,NULL,"Statement");}
    | error SEMI                                                    {$$ = insertNode(NULL,NULL,NULL);}

    | LBRACE StatementBrace                                         {$$ = $2;}

    | IF LPAR Expr RPAR Statement StatementElse                     {nodeptr aux=insertNode($5,NULL,"Statement");aux=insertNode(aux,NULL,"StatList");
                                                                     nodeptr aux2=insertNode($6,NULL,"Statement");aux2=insertNode(aux2,NULL,"StatList");
                                                                     joinNodes(aux,aux2); joinNodes($3,aux); $$ = insertNode($3,NULL,"If");}
    
    | WHILE LPAR Expr RPAR Statement                                {nodeptr aux=insertNode($5,NULL,"StatList"); joinNodes($3,aux); $$ = insertNode($3,NULL,"While");}

    | RETURN StatementReturn                                        {$$ = insertNode($2,NULL,"Return");}

    ;

StatementBrace: Statement RBRACE                                    {$$ = $1;}
    | Statement StatementBrace                                      {joinNodes($1,$2);$$ = $1;}
    | error RBRACE                                                  {$$ = insertNode(NULL,NULL,NULL);}
    ;

StatementElse: ELSE Statement                                       {$$ = $2;}
    | %prec "then"                                                  {$$ = NULL;}
    ;

StatementReturn: SEMI                                               {$$ = NULL;}
    | Expr SEMI                                                     {$$ = $1;}
    ;

Expr: Expr ASSIGN Expr                                              {joinNodes($1,$3); $$ = insertNode($1,NULL,"Store");}
    | Expr COMMA Expr                                               {joinNodes($1,$3); $$ = insertNode($1,NULL,"Comma");}
    
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

    | PLUS Expr                                                     {$$ = insertNode($2,NULL,"Plus");}
    | MINUS Expr                                                    {$$ = insertNode($2,NULL,"Minus");}
    | NOT Expr                                                      {$$ = insertNode($2,NULL,"Not");}

    | ID                                                            {$$ = insertNode(NULL,$1,"Id");}
    | INTLIT                                                        {$$ = insertNode(NULL,$1,"IntLit");}
    | CHRLIT                                                        {$$ = insertNode(NULL,$1,"ChrLit");}
    | REALLIT                                                       {$$ = insertNode(NULL,$1,"RealLit");}
    | ID LPAR Expr RPAR                                             {nodeptr aux = insertNode(NULL,$1,"Id"); joinNodes(aux,$3); $$= insertNode(aux,NULL,"Call");}
    | ID LPAR error RPAR                                            {$$ = insertNode(NULL,NULL,NULL);}
    | LPAR Expr RPAR                                                {$$ = $2;}
    | LPAR error RPAR                                               {$$ = insertNode(NULL,NULL,NULL);}
    ;


%%


void yyerror (char *s) {
    printf ( "Line %d, col %d: %s: %s\n" , nline , ncol ,s , yytext );
    treePrint = 0;
}

