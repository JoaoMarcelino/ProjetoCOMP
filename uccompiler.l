//uc2018293871 Sofia Silva
//uc2018279700 João Marcelino

%X COMMENT CHARS

// \n

/* */

id			[a-zA-Z"_"][a-zA-Z0-9"_"]*
intlit 		[0-9]+

carater 	[^["'"\\n]]
escape		[\\n\\t"\\""\'""\""\\[1-7]{1,3}]
chrlit 		{carater}|{escape}

fract 		[0-9]*"."[0-9]*
signal 		["+"|"-"|""]
expoente 	{signal}["e"|"E"][0-9]+
reallit 	{fract}|{fract}{expoente}|{intlit}{expoente}

reserved	["["|"]"|"--"|"++"]  

%{
	//sempre que for lida 1 char aumentar ncol,
	//sempre que for encontrado \n reset ncol add nline
	int nline=0,ncol=0; 
	int willPrint=0;
%}

%%
"char"          {if(willPrint)printf("CHAR");}
"else"          {if(willPrint)printf("ELSE");}
"while"         {if(willPrint)printf("WHILE");}
"if"            {if(willPrint)printf("IF");}
"int"           {if(willPrint)printf("INT");}
"short"         {if(willPrint)printf("SHORT");}
"double"        {if(willPrint)printf("DOUBLE");}
"return"        {if(willPrint)printf("RETURN");}
"void"          {if(willPrint)printf("VOID");}
"&"             {if(willPrint)printf("BITWISEAND");}
"|"             {if(willPrint)printf("BITEWISEOR");}
"^"             {if(willPrint)printf("BITEWISEXOR");}
"&&"            {if(willPrint)printf("AND");}
"="             {if(willPrint)printf("ASSIGN");}
"*"             {if(willPrint)printf("MUL");}
","             {if(willPrint)printf("COMMA");}
"/"             {if(willPrint)printf("DIV");}
"=="            {if(willPrint)printf("EQ");}
">="            {if(willPrint)printf("GE");}
">"             {if(willPrint)printf("GT");}
"{"             {if(willPrint)printf("LBRACE");}
"<="            {if(willPrint)printf("LE");}
"("             {if(willPrint)printf("LPAR");}
"<"             {if(willPrint)printf("LT");}
"-"             {if(willPrint)printf("MINUS");}
"%"             {if(willPrint)printf("MOD");}
"!="            {if(willPrint)printf("NE");}
"!"             {if(willPrint)printf("NOT");}
"||"            {if(willPrint)printf("OR");}
"+"             {if(willPrint)printf("PLUS");}
"}"             {if(willPrint)printf("RBRACE");}
")"             {if(willPrint)printf("RPAR");}
";"             {if(willPrint)printf("SEMI");}
{reserved}		{if(willPrint)printf("RESERVED");}

{id}			{if(willPrint)printf("ID(%s)",&yytext[0]);}
{intlit}		{if(willPrint)printf("INTLIT(%s)",&yytext[0]);}
{chrlit}		{if(willPrint)printf("CHRLIT(%s)",&yytext[0]);}
{reallit}		{if(willPrint)printf("REALLIT(%s)",&yytext[0]);}

%%

int main(int argc, char *argv[ ]){
	if (argc>=1){
		if (*argv[1]=="-1")
			willPrint=1;
		else if (*argv[1]=="-e1")
			willPrint=0;
	}
	yylex();
	return 0;
}

int yywrap() {
	return 1;
}