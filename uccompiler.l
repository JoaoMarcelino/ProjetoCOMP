/*
uc2018293871 Sofia Silva
uc2018279700 João Marcelino
{escape}({char}+|{escape}+)
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
	//sempre que for lida 1 char aumentar ncol,
	//sempre que for encontrado \n reset ncol add nline
	int nline=1,ncol=1;
	int comline=0,comcol=1; 
	int willPrint=0;
	int longComment=0;
%}
/*<CHARS>{escape}	{numChar++;if(willPrint)printf("CHRLIT(%s)\n",&yytext[0]);if(numChar>1)printf("ERROR INVALID CHAR");}
*/

%%

"/*"			{comline=0; comcol=yyleng; longComment=1; BEGIN COMMENT;}
"//"			{comline=0; comcol=yyleng; longComment=0; BEGIN COMMENT;}
<COMMENT>"*/" 	{comcol+=yyleng; if(longComment){ nline+=comline; ncol+=comcol; BEGIN 0;}}
<COMMENT>\n		{comline++; comcol=1; if(!longComment){ nline+=comline; ncol=comcol; BEGIN 0;}}
<COMMENT><<EOF>> {if(longComment){printf("Line %d, col %d: unterminated comment\n",nline,ncol);}nline+=comline;ncol=comcol;BEGIN 0;}
<COMMENT>.		{comcol+=yyleng;}

'({char}|{escape})' {if(willPrint)printf("CHRLIT(%s)\n",&yytext[0]);ncol+=yyleng;}
'({char}|(\\.))*' {printf("Line %d, col %d: invalid char constant (%s)\n",nline,ncol,&yytext[0]);ncol+=yyleng;}
'({char}|(\\.))*(\\?) {printf("Line %d, col %d: unterminated char constant\n",nline,ncol);ncol+=yyleng;}


"char"          {ncol+=yyleng;if(willPrint)printf("CHAR\n");}
"else"          {ncol+=yyleng;if(willPrint)printf("ELSE\n");}
"while"         {ncol+=yyleng;if(willPrint)printf("WHILE\n");}
"if"            {ncol+=yyleng;if(willPrint)printf("IF\n");}
"int"           {ncol+=yyleng;if(willPrint)printf("INT\n");}
"short"         {ncol+=yyleng;if(willPrint)printf("SHORT\n");}
"double"        {ncol+=yyleng;if(willPrint)printf("DOUBLE\n");}
"return"        {ncol+=yyleng;if(willPrint)printf("RETURN\n");}
"void"          {ncol+=yyleng;if(willPrint)printf("VOID\n");}
"&"             {ncol+=yyleng;if(willPrint)printf("BITWISEAND\n");}
"|"             {ncol+=yyleng;if(willPrint)printf("BITWISEOR\n");}
"^"             {ncol+=yyleng;if(willPrint)printf("BITWISEXOR\n");}
"&&"            {ncol+=yyleng;if(willPrint)printf("AND\n");}
"="             {ncol+=yyleng;if(willPrint)printf("ASSIGN\n");}
"*"             {ncol+=yyleng;if(willPrint)printf("MUL\n");}
","             {ncol+=yyleng;if(willPrint)printf("COMMA\n");}
"/"             {ncol+=yyleng;if(willPrint)printf("DIV\n");}
"=="            {ncol+=yyleng;if(willPrint)printf("EQ\n");}
">="            {ncol+=yyleng;if(willPrint)printf("GE\n");}
">"             {ncol+=yyleng;if(willPrint)printf("GT\n");}
"{"             {ncol+=yyleng;if(willPrint)printf("LBRACE\n");}
"<="            {ncol+=yyleng;if(willPrint)printf("LE\n");}
"("             {ncol+=yyleng;if(willPrint)printf("LPAR\n");}
"<"             {ncol+=yyleng;if(willPrint)printf("LT\n");}
"-"             {ncol+=yyleng;if(willPrint)printf("MINUS\n");}
"%"             {ncol+=yyleng;if(willPrint)printf("MOD\n");}
"!="            {ncol+=yyleng;if(willPrint)printf("NE\n");}
"!"             {ncol+=yyleng;if(willPrint)printf("NOT\n");}
"||"            {ncol+=yyleng;if(willPrint)printf("OR\n");}
"+"             {ncol+=yyleng;if(willPrint)printf("PLUS\n");}
"}"             {ncol+=yyleng;if(willPrint)printf("RBRACE\n");}
")"             {ncol+=yyleng;if(willPrint)printf("RPAR\n");}
";"             {ncol+=yyleng;if(willPrint)printf("SEMI\n");}
{reserved}		{ncol+=yyleng;if(willPrint)printf("RESERVED(%s)\n",&yytext[0]);} 
{reallit}		{ncol+=yyleng;if(willPrint)printf("REALLIT(%s)\n",&yytext[0]);}
{intlit}		{ncol+=yyleng;if(willPrint)printf("INTLIT(%s)\n",&yytext[0]);}
{id}			{ncol+=yyleng;if(willPrint)printf("ID(%s)\n",&yytext[0]);}

\r\n|\n|\r		{nline++;ncol=1;}
\f|\v|\t|" "	{ncol++;}
.				{printf("Line %d, col %d: illegal character (%s)\n",nline,ncol, &yytext[0]);ncol++;}
%%


int main(int argc, char *argv[ ]){
	if (argc>=2){
		if (!strcmp(argv[1],"-l"))
			willPrint=1;
		else if (!strcmp(argv[1],"-e1"))
			willPrint=0;
	}
	yylex();
	return 0;
}

int yywrap() {
	return 1;
}

void yyerror (const char *s) { 
     printf ("%s: %s\n", s, yytext);
}