#include <stdio.h>
#define EOI 0	
#define SEMI 1	
#define PLUS 2	
#define TIMES 3	
#define LP 4	
#define RP 5	
#define MINUS 6
#define DIV 7
#define LT 8
#define GT 9
#define EQUAL 10
#define COL 11
#define IF 12
#define THEN 13
#define WHILE 14
#define DO 15
#define BEGIN 16
#define END 17
#define ID 18
#define CONST 19
#define NUM_OR_ID 20

extern char *yytext;		/* in lex.c			*/
extern int yyleng;
extern yylineno;

int installID(char*);
int searchID(char*);
int lex(FILE*);
