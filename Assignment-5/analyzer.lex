%{
	#include <bits/stdc++.h>
	#include <stdlib.h>
	#include <string.h>
	#include "parser.tab.h"
	#include "struct.h"
	using namespace std;

	extern int lineno;

%}

%s START
%x COMMENT

ws	[ \t]*
id 	[a-zA-Z_][a-zA-Z0-9_]*
float	[0-9]+"."[0-9]+ 
int		[0-9]+

%%

"/*"			{ BEGIN(COMMENT); }
<COMMENT>"*/"	{ BEGIN(START); }
<COMMENT>.		{		}
"//"[^\n]*			{	/* do nothing for comment */}

"int"			{ yylval.type = INT;
					return(INT); }
"float"			{ yylval.type = FLOAT;
					return(FLOAT); }
"void"			{ yylval.type = VOID;
					return(VOID); }

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

{id}			{   yylval.Char = strdup(yytext);
					return(ID); }
{int}			{ yylval.int_val = atoi(yytext);
					return(NUM_INT); }
{float}			{ yylval.float_val = atof(yytext);
					return(NUM_FLOAT); }
{ws}			{  }
\n 				{  lineno++; }
.				{ printf("Unrecognized token at line %d\n",lineno); exit(0); }

%%

int yywrap(void) 
{
    return 1;
}
