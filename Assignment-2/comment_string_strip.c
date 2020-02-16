#include <stdio.h>
#include <ctype.h>
#include " "


int main (int a, int b)
{
  int c;
  
  remove(" ");
  remove(" ");

  
  FILE *fp_lexeme;
  fp_lexeme = fopen(" ", " ");


  
  while(c=lex(fp_lexeme))
  {
    
      switch(c)
      {
          case(0):fprintf(fp_lexeme," ");break;
          case(1):fprintf(fp_lexeme," ");break;
          case(2):fprintf(fp_lexeme," ");break;
          case(3):fprintf(fp_lexeme," ");break;
          case(4):fprintf(fp_lexeme," ");break;
          case(5):fprintf(fp_lexeme," ");break;
          case(6):fprintf(fp_lexeme," ");break;
          case(7):fprintf(fp_lexeme," ");break;
          case(8):fprintf(fp_lexeme," ");break;
          case(9):fprintf(fp_lexeme," ");break;
          case(10):fprintf(fp_lexeme," ");break;
          case(11):fprintf(fp_lexeme," ");break;
          case(12):fprintf(fp_lexeme," ");break;
          case(13):fprintf(fp_lexeme," ");break;
          case(14):fprintf(fp_lexeme," ");break;
          case(15):fprintf(fp_lexeme," ");break;
          case(16):fprintf(fp_lexeme," ");break;
          case(17):fprintf(fp_lexeme," ");break;
          case(18):break;
          case(19):break;
      case(20):fprintf(fp_lexeme," ");break;
      }
    }

    
  fclose(fp_lexeme);
}
