%{
	#include <stdlib.h>
	#include <string.h>
	#include "parser.tab.h"
%}
ws				[ \t]*
name		    {ws}[0-9a-zA-Z_]*{ws}
digits 						([0-9]+)
float             ([0-9]*\.?[0-9]+|[0-9]+)
number                ({digits}|{float})

%%
"\n"                        {return NEW_LINE;}
{ws}"SELECT"{ws}            {return SELECT;}
{ws}"PROJECT"{ws}           {return PROJECT;}
{ws}"CARTESIAN_PRODUCT"{ws} {return CARTESIAN_PRODUCT;}
{ws}"EQUI_JOIN"{ws}			{return EQUI_JOIN;}
{ws}"AND"{ws}   {return AND;}
{ws}"OR"{ws}    {return OR;}
{ws}"NOT"{ws}   {return NOT;}
\'[^\']*\'					{return STR;}
\"[^\"]*\"					{return STR;}
{name}          {return NAME;}
{number}        {return NUM;}
{ws}"("{ws}     {return LB;}
{ws}")"{ws}     {return RB;}
{ws}"<"{ws}     {return LT;}
{ws}">"{ws}     {return GT;}
{ws}"<="{ws}    {return LTE;}
{ws}">="{ws}    {return GTE;}
{ws}"="{ws}     {return EQ;}
{ws}"<>"{ws}    {return NEQ;}
{ws}"!="{ws}    {return NEQ;}
{ws}","{ws}		{return COMMA;}
{ws}"."{ws}		{return DOT;}
%%