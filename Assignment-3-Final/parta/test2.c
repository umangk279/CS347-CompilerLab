#include <stdio.h>
#include <ctype.h>
#include "lex.h"


int main (int a, int b)
{
  int c;
  //removing the files if they already exist
  remove("Lexemes.txt");
  remove("SymbolTable.txt");

  //opening Lexemes.txt to write tokens
  FILE *fp_lexeme;
  fp_lexeme = fopen("Lexemes.txt", "w");


  //getting the lexemes from input file
  while(c=lex(fp_lexeme))
  {
    //printing lexemes on the basis of value returned
      switch(c)
      {
          case(0):fprintf(fp_lexeme,"<END OF INPUT> ");break;
          case(1):fprintf(fp_lexeme,"<SEMI> ");break;
          case(2):fprintf(fp_lexeme,"<PLUS> ");break;
          case(3):fprintf(fp_lexeme,"<TIMES> ");break;
          case(4):fprintf(fp_lexeme,"<LP> ");break;
          case(5):fprintf(fp_lexeme,"<RP> ");break;
          case(6):fprintf(fp_lexeme,"<MINUS> ");break;
          case(7):fprintf(fp_lexeme,"<DIV> ");break;
          case(8):fprintf(fp_lexeme,"<LT> ");break;
          case(9):fprintf(fp_lexeme,"<GT> ");break;
          case(10):fprintf(fp_lexeme,"<EQUAL> ");break;
          case(11):fprintf(fp_lexeme,"<COL> ");break;
          case(12):fprintf(fp_lexeme,"<IF> ");break;
          case(13):fprintf(fp_lexeme,"<THEN> ");break;
          case(14):fprintf(fp_lexeme,"<WHILE> ");break;
          case(15):fprintf(fp_lexeme,"<DO> ");break;
          case(16):fprintf(fp_lexeme,"<BEGIN> ");break;
          case(17):fprintf(fp_lexeme,"<END> ");break;
          case(18):break;
          case(19):break;
      case(20):fprintf(fp_lexeme,"<NUM_OR_ID> ");break;
      }
    }

    //closing Lexeme.txt
  fclose(fp_lexeme);
}