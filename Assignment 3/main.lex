

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

%} 

re_var_dec	(("auto"[ \t]*|"const"[ \t]*|"unsigned"[ \t]*|"extern"[ \t]*|"signed"[ \t]*|"register"[ \t]*|"volatile"[ \t]*|"static"[ \t]*|"void"[ \t]*|"short"[ \t]*|"long"[ \t]*|"char"[ \t]*|"int"[ \t]*|"float"[ \t]*|"double"[ \t]*|"_Bool"[ \t]*|"complex"[ \t]*)+)[ \*]+[ \t\*]*?[a-zA-Z_][a-zA-Z_0-9]*[\t ]]*([^\(\))]*);\n
re_macro	([ \t\n])*#[ \t\n]*(define)[ \t\n]
re_fun_dec	((auto[ \t\n]*|const[ \t\n]*|unsigned[ \t\n]*|extern[ \t\n]*|signed[ \t\n]*|register[ \t\n]*|volatile[ \t\n]*|static[ \t\n]*|void[ \t\n]*|short[ \t\n]*|long[ \t\n]*|char[ \t\n]*|int[ \t\n]*|float[ \t\n]*|double[ \t\n]*|_Bool[ \t\n]*|complex[ \t\n]*)+)[ \*]+[[ \t\n]\*]*?[a-zA-Z_][a-zA-Z_0-9]*\(([^!@#$+%^;\{\}]*?)\)[ \t\n]*;




%% 
{re_var_dec}	{var_dec++; printf("YYTEXT=%s\n",yytext);}
{re_macro}	{macros++;}


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
