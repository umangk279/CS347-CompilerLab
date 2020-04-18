%{
	#include <stdlib.h>
	#include <string.h>
	#include "parser.tab.h"

	extern char* query;

	struct attributes_in_query
	{
	    char* att_name;
	    struct attributes_in_query* next;
	};
	
	struct attributes_in_query* aiq_front = NULL;
	struct attributes_in_query* aiq_end = NULL;
%}

ws				[ \t]*
name		    [a-zA-Z][0-9a-zA-Z_]*
digits 						([0-9]+)
float             ([0-9]*\.?[0-9]+|[0-9]+)
number                ({digits}|{float})

%%
"\n"                        {strcat(query,yytext); return NEW_LINE;}
{ws}"SELECT"{ws}            {strcat(query,yytext); return SELECT;}
{ws}"PROJECT"{ws}           {strcat(query,yytext); return PROJECT;}
{ws}"CARTESIAN_PRODUCT"{ws} {strcat(query,yytext); return CARTESIAN_PRODUCT;}
{ws}"EQUI_JOIN"{ws}			{strcat(query,yytext); return EQUI_JOIN;}
{ws}"AND"{ws}   {strcat(query,"&&"); return AND;}
{ws}"OR"{ws}    {strcat(query,"||"); return OR;}
{ws}"NOT"{ws}   {strcat(query,"!"); return NOT;}
\'[^\']*\'					{yytext[0]='"'; yytext[yyleng-1]='"'; strcat(query,yytext); return STR;}
\"[^\"]*\"					{strcat(query,yytext); return STR;}
{name}          {strcat(query,yytext); 
					struct attributes_in_query* temp = (struct attributes_in_query* )malloc(sizeof(struct attributes_in_query));
					temp->att_name = (char*) malloc(50*sizeof(char));
					strcpy(temp->att_name,yytext);
					temp->next = NULL;
					if(aiq_end == NULL){ aiq_end=temp; aiq_front=temp;}
					else { aiq_end->next = temp; aiq_end = temp;}
				return NAME;}
{number}        {strcat(query,yytext); return NUM;}
{ws}"("{ws}     {strcat(query,yytext); return LB;}
{ws}")"{ws}     {strcat(query,yytext); return RB;}
{ws}"<"{ws}     {strcat(query,yytext); return LT;}
{ws}">"{ws}     {strcat(query,yytext); return GT;}
{ws}"<="{ws}    {strcat(query,yytext); return LTE;}
{ws}">="{ws}    {strcat(query,yytext); return GTE;}
{ws}"="{ws}     {strcat(query,"=="); return EQ;}
{ws}"<>"{ws}    {strcat(query,"!="); return NEQ;}
{ws}"!="{ws}    {strcat(query,yytext); return NEQ;}
{ws}","{ws}		{strcat(query,yytext); return COMMA;}
{ws}"."{ws}		{strcat(query,yytext); return DOT;}
%%
