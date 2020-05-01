%{
	#include <stdlib.h>
	#include <string.h>
	#include "parser.tab.h"

%}

ws	[ \t]*
id 	[a-zA-Z_][a-zA-Z0-9_]*
float	[0-9]+"."[0-9]+ 
int		[0-9]+

%%
"//"[^\n]*			{	/* do nothing for comment */}

"int"			{ return(INT); }
"float"			{ return(FLOAT); }
"void"			{ return(VOID); }

"if"			{ return(IF); }
"else"			{ return(ELSE); }

"for"			{ return(FOR); }
"while"			{ return(WHILE); }

"break"			{ return(BREAK); }
"continue"		{ return(CONTINUE); }

"switch"		{ return(SWITCH); }
"case"			{ return(CASE); }
"default"		{ return(DEFAULT); }

"return"		{ return(RETURN); }
"printf"		{ return(PRINT); }

"+"				{ return(PLUS); }
"-"				{ return(MINUS); }
"*"				{ return(MULTIPLY); }
"/"				{ return(DIVIDE); }
"%"				{ return(MOD); }
"="				{ return(ASSIGN); }
"||"			{ return(OR); }
"&&"			{ return(AND); }
"!"				{ return(NOT); }
";"				{ return(SEMI); }
","				{ return(COMMA); }
":"				{ return(COLON); }
"<"				{ return(LT); }
">"				{ return(GT); }
"<="			{ return(LTE); }
">="			{ return(GTE); }
"=="			{ return(EQ); }
"!="			{ return(NEQ); }

"("				{ return(LB); }
")"				{ return(RB); }
"["				{ return(LSQ); }
"]"				{ return(RSQ); }
"{"				{ return(LCURLY); }
"}"				{ return(RCURLY); }
"++"			{ return(INCREMENT); }
"--"			{ return(DECREMENT); }

{id}			{ return(ID); }
{int}			{ return(NUM_INT); }
{float}			{ return(NUM_FLOAT); }
{ws}			{  }
\n 				{  }
.				{ printf("Unrecognized token\n"); }

%%

int yywrap(void) 
{
    return 1;
}
