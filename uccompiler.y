%{
    #include <stdio.h>
    int yylex(void);
    void yyerror (const char *s);

    /*
    () normal
    [] opcional
    {} zero ou mais repetições
    FunctionsAndDeclarations −→ (FunctionDefinition | FunctionDeclaration | Declaration) {FunctionDefinition | FunctionDeclaration | Declaration}

    TypeSpecHelper −→ TypeSpec FunctionDeclarator

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

%token NUMBER
%right '='
%left '+' '-'
%left '*' '/'
%right '('

%%
FunctiosAndDeclarations: FunctionDefinition FunctiosAndDeclarations {}
    |  FunctionDeclaration FunctiosAndDeclarations                  {}
    | Declaration FunctiosAndDeclarations                           {}
    ;
FunctionDefinition: 
    TypeSpec FunctionDeclarator 
    ;

FunctionBody: ;

DeclarationsAndStatements: ;

FunctionDeclaration: ;

FunctionDeclarator: ;

ParameterList: ;

ParameterDeclaration: ;

Declaration: ;

TypeSpec: ;

Declarator: ;

Statement: ;

Expr: ;




%%

int main() {
    yyparse();
    return 0;
}