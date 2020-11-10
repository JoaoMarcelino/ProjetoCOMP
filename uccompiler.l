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

	int willPrint=0;
	int LexicalErrors=0;
	int treePrint=0;
	int SintaxErrors=0;

	//sempre que for lida 1 char aumentar ncol,
	//sempre que for encontrado \n reset ncol add nline
	int nline=1,ncol=1;
	int comline=0,comcol=1; 
	int longComment=0;
%}
/*<CHARS>{escape}	{numChar++;if(willPrint)printf("CHRLIT(%s)\n",&yytext[0]);if(numChar>1)printf("ERROR INVALID CHAR");}
*/

%%

"/*"			{comline=0; comcol=yyleng; longComment=1; BEGIN COMMENT;}
"//"			{comline=0; comcol=yyleng; longComment=0; BEGIN COMMENT;}
<COMMENT>"*/" 	{comcol+=yyleng; if(longComment){ nline+=comline; ncol+=comcol; BEGIN 0;}}
<COMMENT>\n		{comline++; comcol=1; if(!longComment){ nline+=comline; ncol=comcol; BEGIN 0;}}
<COMMENT><<EOF>> {if(longComment){if(LexicalErrors)printf("Line %d, col %d: unterminated comment\n",nline,ncol);}nline+=comline;ncol=comcol;BEGIN 0;}
<COMMENT>.		{comcol+=yyleng;}

'({char}|{escape})' {if(willPrint)printf("CHRLIT(%s)\n",&yytext[0]);ncol+=yyleng; yylval.id = strdup(yytext); return CHRLIT;}
'({char}|(\\.))*' {if(LexicalErrors)printf("Line %d, col %d: invalid char constant (%s)\n",nline,ncol,&yytext[0]);ncol+=yyleng;}
'({char}|(\\.))*(\\?) {if(LexicalErrors)printf("Line %d, col %d: unterminated char constant\n",nline,ncol);ncol+=yyleng;}


"char"          {if(willPrint)printf("CHAR\n"); return CHAR;ncol+=yyleng;}
"else"          {if(willPrint)printf("ELSE\n"); return ELSE;ncol+=yyleng;}
"while"         {if(willPrint)printf("WHILE\n"); return WHILE;ncol+=yyleng;}
"if"            {if(willPrint)printf("IF\n"); return IF;ncol+=yyleng;}
"int"           {if(willPrint)printf("INT\n"); return INT;ncol+=yyleng;}
"short"         {if(willPrint)printf("SHORT\n"); return SHORT;ncol+=yyleng;}
"double"        {if(willPrint)printf("DOUBLE\n"); return DOUBLE;ncol+=yyleng;}
"return"        {if(willPrint)printf("RETURN\n"); return RETURN;ncol+=yyleng;}
"void"          {if(willPrint)printf("VOID\n"); return VOID;ncol+=yyleng;}
"&"             {if(willPrint)printf("BITWISEAND\n"); return BITWISEAND;ncol+=yyleng;}
"|"             {if(willPrint)printf("BITWISEOR\n"); return BITWISEOR;ncol+=yyleng;}
"^"             {if(willPrint)printf("BITWISEXOR\n"); return BITWISEXOR;ncol+=yyleng;}
"&&"            {if(willPrint)printf("AND\n"); return AND;ncol+=yyleng;}
"="             {if(willPrint)printf("ASSIGN\n"); return ASSIGN;ncol+=yyleng;}
"*"             {if(willPrint)printf("MUL\n"); return MUL;ncol+=yyleng;}
","             {if(willPrint)printf("COMMA\n"); return COMMA;ncol+=yyleng;}
"/"             {if(willPrint)printf("DIV\n"); return DIV;ncol+=yyleng;}
"=="            {if(willPrint)printf("EQ\n"); return EQ;ncol+=yyleng;}
">="            {if(willPrint)printf("GE\n"); return GE;ncol+=yyleng;}
">"             {if(willPrint)printf("GT\n"); return GT;ncol+=yyleng;}
"{"             {if(willPrint)printf("LBRACE\n"); return LBRACE;ncol+=yyleng;}
"<="            {if(willPrint)printf("LE\n"); return LE;ncol+=yyleng;}
"("             {if(willPrint)printf("LPAR\n"); return LPAR;ncol+=yyleng;}
"<"             {if(willPrint)printf("LT\n"); return LT;ncol+=yyleng;}
"-"             {if(willPrint)printf("MINUS\n"); return MINUS;ncol+=yyleng;}
"%"             {if(willPrint)printf("MOD\n"); return MOD;ncol+=yyleng;}
"!="            {if(willPrint)printf("NE\n"); return NE;ncol+=yyleng;}
"!"             {if(willPrint)printf("NOT\n"); return NOT;ncol+=yyleng;}
"||"            {if(willPrint)printf("OR\n"); return OR;ncol+=yyleng;}
"+"             {if(willPrint)printf("PLUS\n"); return PLUS;ncol+=yyleng;}
"}"             {if(willPrint)printf("RBRACE\n"); return RBRACE;ncol+=yyleng;}
")"             {if(willPrint)printf("RPAR\n"); return RPAR;ncol+=yyleng;}
";"             {if(willPrint)printf("SEMI\n"); return SEMI;ncol+=yyleng;}
{reserved}		{if(willPrint)printf("RESERVED(%s)\n",&yytext[0]); return RESERVED;ncol+=yyleng;} 
{reallit}		{if(willPrint)printf("REALLIT(%s)\n",&yytext[0]);  yylval.id = strdup(yytext); return REALLIT;ncol+=yyleng;}
{intlit}		{if(willPrint)printf("INTLIT(%s)\n",&yytext[0]);   yylval.id = strdup(yytext); return INTLIT;ncol+=yyleng;}
{id}			{if(willPrint)printf("ID(%s)\n",&yytext[0]);       yylval.id = strdup(yytext); return ID;ncol+=yyleng;}

\r\n|\n|\r		{nline++;ncol=1;}
\f|\v|\t|" "	{ncol++;}
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
	return 0;
}

int yywrap() {
	return 1;
}