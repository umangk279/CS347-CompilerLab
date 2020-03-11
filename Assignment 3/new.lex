%{ 
	/*Definition section */
	#include <stdio.h>
	int source_code_statements = 0;
	int blank_lines=0;
	int comments=0;
	int macros=0;
	int var_dec=0;
	int func_dec=0;
	int func_def=0;
    int chars = 0;
    int i=0;
%} 

%% 
.  {chars++;}
([ \t\n])*#[ \t\n]*"define"[ \t\n]   {macros++;printf("YYTEXT=$%s$\n",yytext);}
.?\n    {source_code_statements++; if(chars==0) blank_lines++; chars=0;printf("%dHI=$%s$\n",++i,yytext);}
<<EOF>> {source_code_statements++;printf("EOF\n");return;}

%% 

int yywrap(){} 

// driver code 
int main() 
{ 

	
	extern FILE *yyin, *yyout; 

	yyin = fopen("Input.c", "r"); 

	
	yyout = fopen("Output.txt", "w"); 

	yylex(); 

	printf("Source Code Statements: %d\n",source_code_statements);
	printf("Blank Lines: %d\n",blank_lines);
	printf("Macros: %d\n",macros);
	printf("Function Declarations: %d\n",func_dec);
	printf("Function Definitions: %d\n", func_def);
	printf("Variable Declarations: %d\n", var_dec);
	return 0; 
} 
