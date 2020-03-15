%{ 
	/*Definition section */
	#include <stdio.h>
	int source_code_statements = 0;
	int blank_lines=0;
	int macros=0;
	int var_dec=0;
	int func_dec=0;
	int func_def=0;
    int i=0;
    int j=0;
	int single_comment=0;
	int non_blank_lines=0;
	int total_multilines=0, cmnt_start=0;
%}

%x COMMENT
%x BLANK
TYPE auto|const|unsigned|extern|signed|register|volatile|static|void|short|long|char|int|float|double|_Bool|complex

%%

"//".*   {single_comment++;}
"/*"     {cmnt_start=source_code_statements;BEGIN COMMENT;}
<COMMENT>{
"*/"      {total_multilines+=source_code_statements-cmnt_start+1;BEGIN(INITIAL);}
\n { yylineno++;source_code_statements++;}
}
({TYPE}[ \t]+)*{TYPE}([ \t"*"])+([ \t])*[_a-zA-Z_][a-zA-Z0-9_]*[ \t]*\(.*\);    {func_dec++;}
({TYPE}[ \t]+)*{TYPE}([ \t"*"])+([ \t])*[_a-zA-Z_][a-zA-Z0-9_]*[ \t]*\(.*\)([ \t\n])*\{   {func_def++; for(j=0; j<yyleng; j++) {if(yytext[j]=='\n') source_code_statements++;}}
({TYPE}[ \t]+)*{TYPE}([ \t"*"])+([ \t])*[_a-zA-Z_][a-zA-Z0-9_]*[ \t]*[=\[,]?([^\(\)\n])*; {var_dec++;}
([ \t\n])*#[ \t\n]*"define"[ \t]/[^\n]*\n   {macros++; source_code_statements++;}
.?\n    {source_code_statements++; }
<BLANK>^[ \t]*\n		{blank_lines++;}
<BLANK>\n		{non_blank_lines++;}

%%


int yywrap(){} 

// driver code 
int main(int argc, char* argv[]) 
{ 
	
	extern FILE *yyin,*yyout; 
	yyin = fopen(argv[1], "r");
	yyout = fopen("Output.txt", "w");
	yylex(); 
	fclose(yyin);
	yyin = fopen(argv[1], "r");
	BEGIN(BLANK);
	yylex();
	printf("Source Code Statements: %d\n",blank_lines+non_blank_lines+1);
	printf("Blank Lines: %d\n",blank_lines);
	printf("Macros: %d\n",macros);
	printf("Function Declarations: %d\n",func_dec);
	printf("Function Definitions: %d\n", func_def);
	printf("Variable Declarations: %d\n", var_dec);
	printf("Comments: %d\n", total_multilines+single_comment);
	return 0; 
} 