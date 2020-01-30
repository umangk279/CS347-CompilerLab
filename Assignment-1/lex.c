#include "lex.h"
#include <stdio.h>
#include <ctype.h>


char* yytext = ""; /* Lexeme (not '\0'
                      terminated)              */
int yyleng   = 0;  /* Lexeme length.           */
int yylineno = 0;  /* Input line number        */

char symbol_table[25][25];
int numSym=-1;

FILE* fp_symTable;

int installID(char* buffer)
{
  strcpy(symbol_table[++numSym],buffer);
  fp_symTable = fopen("SymbolTable.txt", "a+");
  fprintf(fp_symTable,"%d %s\n",numSym,buffer);
  fclose(fp_symTable);
  return numSym;
}


int searchID(char* buffer)
{
  int i;
  for(i=0;i<=numSym;i++)
  {
    if(!strcmp(symbol_table[i],buffer))
      return i;
  }
  return -1;
}


int lex(FILE* fp_lexeme){

   static char input_buffer[1024];
   char        *current;

   current = yytext + yyleng; /* Skip current
                                 lexeme        */

   while(1){       /* Get the next one         */
      while(!*current ){
         /* Get new lines, skipping any leading
         * white space on the line,
         * until a nonblank line is found.
         */

         current = input_buffer;
         if(!gets(input_buffer)){
            *current = '\0' ;

            return EOI;
         }
         ++yylineno;
         while(isspace(*current))
            ++current;
      }
      for(; *current; ++current){
         /* Get the next token */
         yytext = current;
         yyleng = 1;
         int isConst = 1,j;
         switch( *current ){
           case ';':
            return SEMI;
           case '+':
            return PLUS;
           case '-':
            return MINUS;
           case '*':
            return TIMES;
           case '/':
            return DIV;
           case '(':
            return LP;
           case ')':
            return RP;
           case '<':
            return LT;
           case '>':
            return GT;
           case '=':
            return EQUAL;
           case ':':
            return COL;
           case '\n':
           case '\t':
           case ' ' :
            break;
           default:
            if(!isalnum(*current))
               fprintf(stderr, "Not alphanumeric \n", *current);
            else{
               while(isalnum(*current))
                  ++current;
               yyleng = current - yytext;
               char subbuff[yyleng+1];
               memcpy( subbuff, yytext, yyleng );
               subbuff[yyleng] = '\0';
             if(strcmp(subbuff, "if") == 0)
             {
                return IF;
             }
             else if(strcmp(subbuff, "then") == 0)
             {
                return THEN;
             }
             else if(strcmp(subbuff, "while") == 0)
             {
                return WHILE;
             }
             else if(strcmp(subbuff, "do") == 0)
             {
                return DO;
             }
             else if(strcmp(subbuff, "begin") == 0)
             {
                return BEGIN;
             }
             else if(strcmp(subbuff, "end") == 0)
             {
                return END;
             }
             else
              {
                for(j=0;j<yyleng;j++)
                {
                  //printf("%c-%d\n",subbuff[j],j);
                  if(!isdigit(subbuff[j])) 
                    {
                      isConst=0; 
                      break;
                    }
                }
                if(isConst)
                {
                  fprintf(fp_lexeme,"<CONST,%s> ",subbuff);
                  return CONST;
                }
                else
                {
                  int attribute;
                  int c=searchID(subbuff);
                  if(c!=-1)
                    {attribute =c;}
                  else{
                      attribute=installID(subbuff);
                  }
                  fprintf(fp_lexeme,"<ID,%d> ",attribute);
                  return ID;
                }
              }
            }
            break;
         }
      }
   }
}


// static int Lookahead = -1; /* Lookahead token  */

// int match(int token){
//    /* Return true if "token" matches the
//       current lookahead symbol.                */

//    if(Lookahead == -1)
//       Lookahead = lex();

//    return token == Lookahead;
// }

// void advance(void){
// /* Advance the lookahead to the next
//    input symbol.                               */

//     Lookahead = lex();
// }
