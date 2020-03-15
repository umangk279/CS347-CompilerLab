%{
#include <stdio.h>
extern FILE *yyin;
extern int yylex();
extern int yyparse();
int i=1;
void yyerror(char *s){
}
int yywrap()
{ }

%}

%union{ char Char;}

%token <Char> NEW_LINE SELECT PROJECT CARTESIAN_PRODUCT EQUI_JOIN STR NAME NUM AND OR NOT LB RB LT GT LTE GTE EQ NEQ COMMA DOT

%start SMT_LIST

%%
SMT_LIST: SMT NEW_LINE SMT_LIST
    | SMT
    | error NEW_LINE {printf ("%d: INVALID SYNTAX\n",i++);} SMT_LIST    
    ;

SMT:    QUERY
        {printf("%d: VALID SYNTAX\n",i++);};

QUERY:  SELECTION
        | PROJECTION
        | CART_PRODUCT
        | EQ_JOIN        |
        ;

SELECTION:    SELECT LT CONDITIONS GT LB TABLE_NAME RB
              ;

PROJECTION:   PROJECT LT ATTRIBUTE_LIST GT LB TABLE_NAME RB
              ;

CART_PRODUCT:     LB TABLE_NAME RB CARTESIAN_PRODUCT LB TABLE_NAME RB
                  ;

EQ_JOIN:    LB TABLE_NAME RB EQUI_JOIN LT EQUI_CONDITIONS GT LB TABLE_NAME RB
            ;

CONDITIONS: CONDITION2 OR CONDITIONS
            | CONDITION2
            ;

CONDITION2: CONDITION AND CONDITION2
            | CONDITION
            ;

CONDITION:  EXPRESSION OPR EXPRESSION
            | LB CONDITIONS RB
            | NOT LB CONDITIONS RB
            ;

OPR:    LT | GT | LTE | GTE | NEQ | EQ
        ;

EXPRESSION:    ATTRIBUTE_LIST | DATA
               ;

ATTRIBUTE_LIST:   ATTRIBUTE | ATTRIBUTE COMMA ATTRIBUTE_LIST
                  ;

ATTRIBUTE:   NAME | NAME DOT NAME
             ;

DATA:   NUM | STR
        ;

TABLE_NAME:    NAME
               ;

EQUI_CONDITIONS: EQUI_CONDITION2 OR EQUI_CONDITIONS
            | EQUI_CONDITION2
            ;

EQUI_CONDITION2: EQUI_CONDITION AND EQUI_CONDITION2
            | EQUI_CONDITION
            ;

EQUI_CONDITION:  EXPRESSION EQ EXPRESSION
            | LB EQUI_CONDITIONS RB
            ;
%%

int main(int argc, char *argv[]){
  yyparse();
  return 0;
}