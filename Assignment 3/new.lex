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
%} 

TYPE auto|const|unsigned|extern|signed|register|volatile|static|void|short|long|char|int|float|double|_Bool|complex

%% 
({TYPE}[ \t]+)*{TYPE}[ \t]*"*"*([ \t])*[_a-zA-Z_][a-zA-Z0-9_]*\(.*\);    {chars++; func_dec++;}
({TYPE}[ \t]+)*{TYPE}[ \t]*"*"*([ \t])*[_a-zA-Z_][a-zA-Z0-9_]*\(.*\)([ \t\n])*\{    {chars++; func_def++;printf("ALOOOOOOO=$%s$\n",yytext);printf("ahhhh=$%s$\n",yytext); for(j=0; j<yyleng; j++) {if(yytext[j]=='\n') source_code_statements++;}}
({TYPE}[ \t]+)*{TYPE}[ \t]*"*"*([ \t])*[_a-zA-Z_][a-zA-Z0-9_]*[ \t]*[=\[,]?([^\(\)\n])*; {chars++; var_dec++;printf("FUCK YOU=$%s$\n",yytext);}
.  {chars++;}
([ \t\n])*#[ \t\n]*"define"[ \t\n]   {macros++;}
.?\n    {source_code_statements++; if(chars==0) blank_lines++; chars=0;printf("%dHI=$%s$\n",++i,yytext);}
<<EOF>> {source_code_statements++; printf("ECHOOOO"); return 0;}

%% 

int yywrap(){} 

// driver code 
int main() 
{ 

	file.open(Input.c); 
	fstream file2;
    file2.open("comment_strip.c",ios::out); 
    enum states { TEXT, 
                SAW_SLASH, 
                SAW_STAR, 
                SINGLE_COMMENT, 
                MULTI_COMMENT } state = TEXT;
    int multi  = 0;
    int single = 0;

    char c;
	while (file.get(c))
  	{
	    switch( state )
	    {
	      case TEXT :
	        switch( c )
	        {
	          case '/'  : state = SAW_SLASH; break;
	          default   : file2.put(c); break;
	        }
	        break;

	      case SAW_SLASH :
	        switch( c )
	        {
	          case '/'  : state = SINGLE_COMMENT; break;
	          case '*'  : state = MULTI_COMMENT; break;
	          default   : file2.put(c); state = TEXT; break;
	        }
	        break;

	      case SAW_STAR :
	        switch( c )
	        {
	          case '/'  : state = TEXT; multi++; break;
	          case '*'  : break;
	          case '\n' : multi++; // fall through
	          default   : state = MULTI_COMMENT; break;
	        }
	        break;

	      case SINGLE_COMMENT :
	        switch( c )
	        {
	          case '\n' : file2.put(c); state = TEXT; single++; // fall through
	          default   : break;
	        }
	        break;

	      case MULTI_COMMENT :
	        switch( c )
	        {
	          case '*'  : state = SAW_STAR; break;
	          case '\n' : multi++; // fall through
	          default   : break;
	        }
	        break;

	      default: // NOT REACHABLE
	        break;
	    }
  	}

  	comments=multi+single;
  	file.close();
    file2.close();

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
