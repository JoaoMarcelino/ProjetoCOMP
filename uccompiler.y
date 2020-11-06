%{
    #include <stdio.h>
    int yylex(void);
    void yyerror (const char *s);
    #define NSYMS 100

    symtab tab[NSYMS];

    symtab *symlook(char *varname); 

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
int value;
char *others;
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
%token <others> CHRLIT
%token <others> REALLIT
%token <value> INTLIT
%token <id> ID


%right ASSIGN
%left PLUS MINUS
%left MUL DIV
%right LPAR


symtab *symlook(char *varname)
{
int i;
  
for(i=0; i<NSYMS; i++)
 {
        if(tab[i].name && strcmp(varname, tab[i].name)==0)   
                return &tab[i];
        if(!tab[i].name)
        {
                tab[i].name=varname;
                return &tab[i];
        }
 }
yyerror("variaveis a mais...");
    exit(1);
}




%%
FunctionsAndDec: TypeSpec FunctionDeclaration {}
    ;

FunctiosAndDeclarations: FunctionDeclarator FuctionsAndDecExtra  {}
    |   Declaration FuctionsAndDecExtra                          {}
    ;

FuctionsAndDecExtra:  FunctionsAndDeclarations {}
    |       {}
    ;

FunctionDeclarator: ID LPAR ParameterList RPAR FunctionHelper       {}
    ;

ParameterList: TypeSpec ParameterDeclaration ParameterExtra {}
    ;

ParameterExtra: COMMA TypeSpec ParameterDeclaration ParameterExtra {}
    | {}
    ;      
ParameterDeclaration: ID {}
    | {}
    ;

FunctionHelper:   LBRACE FunctionBody RBRACE    {}
    | SEMI {}
    ;

FunctionBody: DeclarationsAndStatements {}
    | {}
    ;

DeclarationsAndStatements: Statement DeclarationsAndStatementsRep {}
	| TypeSpec Declaration DeclarationsAndStatementsRep {}
    ;

DeclarationsAndStatementsRep: DeclarationsAndStatements {}
    | {}
    ;

Declaration: ID Declarator DeclarationExtra {}
    ;

DeclarationExtra: COMMA ID Declarator DeclarationExtra {}
    | SEMI      {}
    ;

Declarator: ASSIGN Expr {}
    | \e  {}
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

StatementElse: ELSE Statement {}
    | {}
    ;

StatementReturn: SEMI {}
    | Expr SEMI {}
    ;

Expr: Expr ASSIGN Expr {}
    | Expr COMMA Expr {}
    
    | Expr PLUS Expr    {$$ = $1 + $3;}
    | Expr MINUS Expr   {$$ = $1 - $3;}
    | Expr MUL Expr     {$$ = $1 * $3;}
    | Expr DIV Expr     {$$ = $1 / $3;}
    | Expr MOD Expr     {$$ = $1 + $3;}

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

    | ID PAR Expr ExprRep RPAR  {}
    | INTLIT LPAR Expr RPAR     {}
    | CHRLIT LPAR Expr RPAR     {}
    | REALLIT LPAR Expr RPAR    {}
    ;

ExprRep: COMMA Expr ExprRep {}
    | {}
    ;

%%

int main() {
    yyparse();
    return 0;
}