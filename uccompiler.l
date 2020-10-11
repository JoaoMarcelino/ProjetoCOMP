/*
uc2018293871 Sofia Silva
uc2018279700 João Marcelino
*/

%X COMMENT CHARS


id			[a-zA-Z"_"][a-zA-Z0-9"_"]*
intlit 		[0-9]+

carater 	[^["'"\\n]]
escape		[\\n\\t"\\""\'""\""\\[1-7]{1,3}]
chrlit 		{carater}|{escape}

fract 		[0-9]*"."[0-9]*
signal 		["-"|"+"|""]
expoente 	{signal}["e"|"E"][0-9]+
reallit 	{fract}{expoente}|{intlit}{expoente}|{fract}

reserved	["["|"]"|"--"|"++"]  

%{	
	#include <string.h>
	#include <stdio.h>
	//sempre que for lida 1 char aumentar ncol,
	//sempre que for encontrado \n reset ncol add nline
	int nline=0,ncol=0; 
	int willPrint=0;
	int longComment=0;
%}

%%
"/*"			{longComment=1;BEGIN COMMENT;}
"//"			{longComment=0;BEGIN COMMENT;}

<COMMENT>"*/" 	{if(longComment)BEGIN 0;}
<COMMENT>"\n"	{if(!longComment)BEGIN 0;}
<COMMENT>.		;

"char"          {if(willPrint)printf("CHAR\n");}
"else"          {if(willPrint)printf("ELSE\n");}
"while"         {if(willPrint)printf("WHILE\n");}
"if"            {if(willPrint)printf("IF\n");}
"int"           {if(willPrint)printf("INT\n");}
"short"         {if(willPrint)printf("SHORT\n");}
"double"        {if(willPrint)printf("DOUBLE\n");}
"return"        {if(willPrint)printf("RETURN\n");}
"void"          {if(willPrint)printf("VOID\n");}
"&"             {if(willPrint)printf("BITWISEAND\n");}
"|"             {if(willPrint)printf("BITEWISEOR\n");}
"^"             {if(willPrint)printf("BITEWISEXOR\n");}
"&&"            {if(willPrint)printf("AND\n");}
"="             {if(willPrint)printf("ASSIGN\n");}
"*"             {if(willPrint)printf("MUL\n");}
","             {if(willPrint)printf("COMMA\n");}
"/"             {if(willPrint)printf("DIV\n");}
"=="            {if(willPrint)printf("EQ\n");}
">="            {if(willPrint)printf("GE\n");}
">"             {if(willPrint)printf("GT\n");}
"{"             {if(willPrint)printf("LBRACE\n");}
"<="            {if(willPrint)printf("LE\n");}
"("             {if(willPrint)printf("LPAR\n");}
"<"             {if(willPrint)printf("LT\n");}
"-"             {if(willPrint)printf("MINUS\n");}
"%"             {if(willPrint)printf("MOD\n");}
"!="            {if(willPrint)printf("NE\n");}
"!"             {if(willPrint)printf("NOT\n");}
"||"            {if(willPrint)printf("OR\n");}
"+"             {if(willPrint)printf("PLUS\n");}
"}"             {if(willPrint)printf("RBRACE\n");}
")"             {if(willPrint)printf("RPAR\n");}
";"             {if(willPrint)printf("SEMI\n");}

{reallit}		{if(willPrint)printf("REALLIT(%s)\n",&yytext[0]);}
{id}			{if(willPrint)printf("ID(%s)\n",&yytext[0]);}
{intlit}		{if(willPrint)printf("INTLIT(%s)\n",&yytext[0]);}
{chrlit}		{if(willPrint)printf("CHRLIT(%s)\n",&yytext[0]);}

.				{ncol++;}
"\n"			{nline++;ncol=0;}

%%

/*
ERROS NO CODIGO!
{reserved}		{if(willPrint)printf("RESERVED");}  
*/

int main(int argc, char *argv[ ]){
	if (argc>=2){
		if (!strcmp(argv[1],"-1"))
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