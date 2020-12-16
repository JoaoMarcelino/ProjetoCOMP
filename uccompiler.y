/*
uc2018293871 Sofia Silva
uc2018279700 João Marcelino
*/

%{
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include "y.tab.h"
    #include "functions.h"
    #define SIZE 100

    int yylex(void);
    int main(void);
    void yyerror (char *s);
    int yydebug = 0;
    

    extern int treePrint;
	extern int SintaxErrors;
    extern int nline,ncol;
    extern char* yytext;
    extern int yyleng; 
    extern int comment,comcol,comline;
    
    extern nodeptr tree;


    int hasStatementList =0;
    int comma=0;


nodeptr insertNode(nodeptr node, char *id, char *type){
    nodeptr aux = (nodeptr)malloc(sizeof(Node));
    aux->id = id;
    aux->type= type;
    /* Adicionar no inicio */
    aux->nodeBrother= NULL;
    aux->nodeNext= node;

    return aux;
};

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

};


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
};

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
};



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
        //printf("%.2d",nPontos);
        if(aux->id){
            //print de Ids
            
            printPontos(nPontos);
            printf("%s(%s)\n",aux->type, aux->id);

        }else if(!strcmp(aux->type,"Else") ){
            
        }
        else if(!strcmp(aux->type,"StatList")){
            
            if (needsStatList(aux)){
                if (check==1){
                    check=0;
                    printPontos(nPontos+=2);
                    printf("%s\n",aux->type);
                }else{
                    printPontos(nPontos);
                    printf("%s\n",aux->type);
                }
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
        
        if (check==1){
            check=0;
            nPontos+=2;
        }
        aux=aux->nodeBrother;
    }
}





    
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
%type <node> ExprComma



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
%left LPAR

%right "then" ELSE



%%
FunctionsAndDec: FunctionsAndDeclarations                           {$$ = insertNode($1,NULL,"Program");tree=$$;}
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

DeclarationsAndStatements: StatementList DeclarationsAndStatementsRep { if($1){ joinNodes($1,$2);$$ =  $1;} else{$$=$2;}}
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

StatementList: Statement                                            {$$=$1;}
    | error SEMI                                                    {$$ = insertNode(NULL,NULL,NULL);}
    ;

Statement:  SEMI                                                    {$$ = NULL;}
    | Expr SEMI                                                     {$$ = $1;}
    | LBRACE RBRACE                                                 {$$ = NULL;}

    | LBRACE StatementBrace RBRACE                                  {if($2){$$ = insertNode($2,NULL,"StatList");}else{$$=$2;}}
    | LBRACE error RBRACE                                           {$$ = insertNode(NULL,NULL,NULL);}

    | IF LPAR Expr RPAR StatementList StatementElse                 {if(!$5){$5=insertNode(NULL,NULL,"Null");} $5=insertNode($5,NULL,"StatList"); if(!$6){$6=insertNode(NULL,NULL,"Null");} $6=insertNode($6,NULL,"StatList"); joinNodes($5,$6);joinNodes($3,$5);$3=insertNode($3,NULL,"If");$$=$3;}

    | WHILE LPAR Expr RPAR StatementList                            {if(!$5){$5=insertNode(NULL,NULL,"Null");} $5=insertNode($5,NULL,"StatList"); joinNodes($3, $5);$$= insertNode($3,NULL,"While");}

    | RETURN StatementReturn                                        {$$ = insertNode($2,NULL,"Return");}

    ;

StatementBrace: StatementBrace StatementList                         {if($1){ joinNodes($1,$2);$$ =  $1;} else{$$=$2;}}
    | StatementList                                                  {$$ = $1;}
    ;


StatementElse: ELSE StatementList                                   {$$ = $2;}
    | %prec "then"                                                  {$$ = NULL;}

    ;

StatementReturn: SEMI                                               {$$ = insertNode(NULL,NULL,"Null");}
    | Expr SEMI                                                     {$$ = $1;}
    ;




Expr: Expr ASSIGN Expr                                              {joinNodes($1,$3); $$ = insertNode($1,NULL,"Store");}
    | Expr COMMA Expr                                               {joinNodes($1,$3); $$ = insertNode($1, NULL,"Comma");}
    
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

    
    | ID LPAR ExprComma RPAR                                        {nodeptr aux = insertNode(NULL,$1,"Id"); joinNodes(aux,$3); $$= insertNode(aux,NULL,"Call");}
    | ID LPAR RPAR                                                  {nodeptr aux = insertNode(NULL,$1,"Id"); $$= insertNode(aux,NULL,"Call");}
    | ID LPAR error RPAR                                            {$$ = insertNode(NULL,NULL,NULL);}
    | LPAR Expr RPAR                                                {$$ = $2;}
    | LPAR error RPAR                                               {$$ = insertNode(NULL,NULL,NULL);}

    | REALLIT                                                       {$$ = insertNode(NULL,$1,"RealLit");}
    | CHRLIT                                                        {$$ = insertNode(NULL,$1,"ChrLit");}
    | INTLIT                                                        {$$ = insertNode(NULL,$1,"IntLit");}
    | ID                                                            {$$ = insertNode(NULL,$1,"Id");}
    ;

ExprComma: ExprComma COMMA Expr                                     {joinNodes($1,$3);}
    | Expr %prec "then"                                             {$$=$1;}
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

