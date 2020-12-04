/*
uc2018293871 Sofia Silva
uc2018279700 João Marcelino
*/

/* ISTO FUNFA MAS O CODIGO FICA TERRIVELMENTE FEIO \\\'|\\\"| */

%X COMMENT CHARS


id			[a-zA-Z_][a-zA-Z0-9_]*
intlit 		[0-9]+

char 		[^'\n\\]

numEscape	\\[0-7]{1,3}
escape		(\\n|\\t|\\\\|\\\'|\\\"|{numEscape})
qt			"'"

error1		[0-7]{1,2}[^"'"\n[0-7]]|[0-7]{3}{char}
error2	 	{escape}{escape}+
error3		{char}({char}+|{escape}+)

fract 		([0-9]+"."[0-9]*)|([0-9]*"."[0-9]+)
signal 		"-"|"+"|""
expoente 	("e"|"E"){signal}[0-9]+
reallit 	{fract}{expoente}|{intlit}{expoente}|{fract}

words		"auto"|"break"|"case"|"const"|"continue"|"default"|"do"|"register"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"volatile"|"enum"|"extern"|"float"|"for"|"goto"
moreWords	"_Bool"|"_Complex"|"_Imaginary"|"inline"|"long"|"restrict"
reserved	"["|"]"|"--"|"++"|{words}|{moreWords}


%{																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																														
	#include <string.h>
	#include <stdio.h>
	#include "y.tab.h"
	#include "tabela_simbolos.h"
	#include "functions.h"

	int willPrint=0;
	int LexicalErrors=0;
	int treePrint=0;
	int SintaxErrors=0;
	int yyleng;

	nodeptr tree;

	//sempre que for lida 1 char aumentar ncol,
	//sempre que for encontrado \n reset ncol add nline
	int nline=1,ncol=1;
	int comline=0,comcol=1; 
	int longComment=0;
	int comment;
%}
/*<CHARS>{escape}	{numChar++;if(willPrint)printf("CHRLIT(%s)\n",&yytext[0]);if(numChar>1)printf("ERROR INVALID CHAR");}
*/

%%


\/\/.*            {ncol+=yyleng;}
"/*"              { BEGIN COMMENT;comcol=ncol;comline=nline;ncol+=yyleng;}
<COMMENT>.        {ncol+=yyleng;}
<COMMENT>\n       {nline++;ncol=1;}
<COMMENT>"*/"     { BEGIN 0;ncol+=yyleng;}
<COMMENT><<EOF>>  {printf("Line %d, col %d: unterminated comment\n",comline,comcol); BEGIN 0;}


'({char}|{escape})' {if(willPrint)printf("CHRLIT(%s)\n",&yytext[0]);ncol+=yyleng; yylval.id = strdup(yytext); return CHRLIT;}
'({char}|(\\.))*' {if(LexicalErrors)printf("Line %d, col %d: invalid char constant (%s)\n",nline,ncol,&yytext[0]);ncol+=yyleng;}
'({char}|(\\.))*(\\?) {if(LexicalErrors)printf("Line %d, col %d: unterminated char constant\n",nline,ncol);ncol+=yyleng;}


"char"          {ncol+=yyleng;if(willPrint)printf("CHAR\n"); return CHAR;}
"else"          {ncol+=yyleng;if(willPrint)printf("ELSE\n"); return ELSE;}
"while"         {ncol+=yyleng;if(willPrint)printf("WHILE\n"); return WHILE;}
"if"            {ncol+=yyleng;if(willPrint)printf("IF\n"); return IF;}
"int"           {ncol+=yyleng;if(willPrint)printf("INT\n"); return INT;}
"short"         {ncol+=yyleng;if(willPrint)printf("SHORT\n"); return SHORT;}
"double"        {ncol+=yyleng;if(willPrint)printf("DOUBLE\n"); return DOUBLE;}
"return"        {ncol+=yyleng;if(willPrint)printf("RETURN\n"); return RETURN;}
"void"          {ncol+=yyleng;if(willPrint)printf("VOID\n"); return VOID;}
"&"             {ncol+=yyleng;if(willPrint)printf("BITWISEAND\n"); return BITWISEAND;}
"|"             {ncol+=yyleng;if(willPrint)printf("BITWISEOR\n"); return BITWISEOR;}
"^"             {ncol+=yyleng;if(willPrint)printf("BITWISEXOR\n"); return BITWISEXOR;}
"&&"            {ncol+=yyleng;if(willPrint)printf("AND\n"); return AND;}
"="             {ncol+=yyleng;if(willPrint)printf("ASSIGN\n"); return ASSIGN;}
"*"             {ncol+=yyleng;if(willPrint)printf("MUL\n"); return MUL;}
","             {ncol+=yyleng;if(willPrint)printf("COMMA\n"); return COMMA;}
"/"             {ncol+=yyleng;if(willPrint)printf("DIV\n"); return DIV;}
"=="            {ncol+=yyleng;if(willPrint)printf("EQ\n"); return EQ;}
">="            {ncol+=yyleng;if(willPrint)printf("GE\n"); return GE;}
">"             {ncol+=yyleng;if(willPrint)printf("GT\n"); return GT;}
"{"             {ncol+=yyleng;if(willPrint)printf("LBRACE\n"); return LBRACE;}
"<="            {ncol+=yyleng;if(willPrint)printf("LE\n"); return LE;}
"("             {ncol+=yyleng;if(willPrint)printf("LPAR\n"); return LPAR;}
"<"             {ncol+=yyleng;if(willPrint)printf("LT\n"); return LT;}
"-"             {ncol+=yyleng;if(willPrint)printf("MINUS\n"); return MINUS;}
"%"             {ncol+=yyleng;if(willPrint)printf("MOD\n"); return MOD;}
"!="            {ncol+=yyleng;if(willPrint)printf("NE\n"); return NE;}
"!"             {ncol+=yyleng;if(willPrint)printf("NOT\n"); return NOT;}
"||"            {ncol+=yyleng;if(willPrint)printf("OR\n"); return OR;}
"+"             {ncol+=yyleng;if(willPrint)printf("PLUS\n"); return PLUS;}
"}"             {ncol+=yyleng;if(willPrint)printf("RBRACE\n"); return RBRACE;}
")"             {ncol+=yyleng;if(willPrint)printf("RPAR\n"); return RPAR;}
";"             {ncol+=yyleng;if(willPrint)printf("SEMI\n"); return SEMI;}
{reserved}		{ncol+=yyleng;if(willPrint)printf("RESERVED(%s)\n",&yytext[0]); return RESERVED;} 
{reallit}		{ncol+=yyleng;if(willPrint)printf("REALLIT(%s)\n",&yytext[0]);  yylval.id = strdup(yytext); return REALLIT;}
{intlit}		{ncol+=yyleng;if(willPrint)printf("INTLIT(%s)\n",&yytext[0]);   yylval.id = strdup(yytext); return INTLIT;}
{id}			{ncol+=yyleng;if(willPrint)printf("ID(%s)\n",&yytext[0]);       yylval.id = strdup(yytext); return ID;}

\r\n|\n|\r		{nline++;ncol=1;}
\f|\v|\t|" "	{ncol++;}
<<EOF>>			{ncol++;return 0;}
.				{if(LexicalErrors)printf("Line %d, col %d: illegal character (%s)\n",nline,ncol, &yytext[0]);ncol++;}
%%


int main(int argc, char *argv[ ]){
	if (argc>=2){
		if (!strcmp(argv[1],"-l")){
			willPrint=1;
			LexicalErrors=1;
			yylex();
		}
			
		else if (!strcmp(argv[1],"-e1")){
			LexicalErrors=1;
			yylex();
		}
			
		else if (!strcmp(argv[1],"-t")){
			LexicalErrors=1;
			treePrint=1;
			yyparse();
		}
			
		else if (!strcmp(argv[1],"-e2")){
			LexicalErrors=1;
			SintaxErrors=1;
			yyparse();
		}
			
	}else{
		LexicalErrors=1;
		SintaxErrors=1;
		yyparse();
	}

	globalTable(tree);

	return 0;
}

int yywrap() {
	return 1;
}