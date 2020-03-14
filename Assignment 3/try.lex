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
    int j=0;
	int a=0,b=0,c=0,d;
	int total_multilines=0, cmnt_start=0;
	int bl=0;
%} 

%x COMMENT
TYPE auto|const|unsigned|extern|signed|register|volatile|static|void|short|long|char|int|float|double|_Bool|complex

%% 
"//".*   {chars++;a++;}
"/*"     { chars++;cmnt_start=source_code_statements;BEGIN COMMENT; printf("%s,%d\n",yytext,source_code_statements);}
<COMMENT>{
"*/"      {chars++;c++;total_multilines+=source_code_statements-cmnt_start+1;BEGIN(INITIAL);}
[^*\n]+   {chars++;}
"*"       {chars++;}
\n { yylineno++;source_code_statements++;if(chars==0) bl++;chars=0; }
\n[ \t]*/\n	{bl++; source_code_statements++;}
}
({TYPE}[ \t]+)*{TYPE}([ \t"*"])+([ \t])*[_a-zA-Z_][a-zA-Z0-9_]*[ \t]*\(.*\);    {chars++; func_dec++; printf("LOL%s\n",yytext);}
({TYPE}[ \t]+)*{TYPE}([ \t"*"])+([ \t])*[_a-zA-Z_][a-zA-Z0-9_]*\(.*\)[ \t\n]*\{    {chars++; func_def++;printf("ALOOOOOOO=$%s$\n",yytext);printf("ahhhh=$%s$\n",yytext); for(j=0; j<yyleng; j++) {if(yytext[j]=='\n') source_code_statements++;}}
({TYPE}[ \t]+)*{TYPE}([ \t"*"])+([ \t])*[_a-zA-Z_][a-zA-Z0-9_]*[ \t]*[=\[,]?([^\(\)\n])*; {chars++; var_dec++;printf("FUCK YOU=$%s$\n",yytext);}
([ \t\n])*#[ \t\n]*"define"[ \t]/[^\n]*\n   {macros++; source_code_statements++;}
.  {chars++;}
.?\n    {source_code_statements++; if(chars==0) blank_lines++; chars=0;printf("%dHI=$%s$\n",++i,yytext);}
<<EOF>> {source_code_statements++; printf("ECHOOOO"); return 0;}
\n[ \t]*/\n {bl++; source_code_statements++;}
%% 

int yywrap(){} 

// driver code 
int main(int argc, char* argv[]) 
{ 
	
	extern FILE *yyin, *yyout; 
	yyin = fopen("Input.c", "r"); 
	yyout = fopen("Output.txt", "w"); 
	yylex(); 
	printf("Source Code Statements: %d\n",source_code_statements);
	printf("Blank Lines: %d\n",bl);
	printf("Macros: %d\n",macros);
	printf("Function Declarations: %d\n",func_dec);
	printf("Function Definitions: %d\n", func_def);
	printf("Variable Declarations: %d\n", var_dec);
	printf("Comments: %d\n", total_multilines+a);
	return 0; 
} 