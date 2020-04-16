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
        {printf("QUERY -> SELECTION | PROJECTION | CART_PRODUCT | EQ_JOIN\n");};

SELECTION:    SELECT LT CONDITIONS GT LB TABLE_NAME RB
        {printf("SELECTION -> SELECT LT CONDITIONS GT LB TABLE_NAME RB\n");};

PROJECTION:   PROJECT LT ATTRIBUTE_LIST GT LB TABLE_NAME RB
        {printf("PROJECTION -> PROJECT LT ATTRIBUTE_LIST GT LB TABLE_NAME RB\n");};

CART_PRODUCT:     LB TABLE_NAME RB CARTESIAN_PRODUCT LB TABLE_NAME RB
        {printf("CART_PRODUCT -> LB TABLE_NAME RB CARTESIAN_PRODUCT LB TABLE_NAME RB\n");};

EQ_JOIN:    LB TABLE_NAME RB EQUI_JOIN LT EQUI_CONDITIONS GT LB TABLE_NAME RB
        {printf("EQ_JOIN -> LB TABLE_NAME RB EQUI_JOIN LT EQUI_CONDITIONS GT LB TABLE_NAME RB\n");};

CONDITIONS: CONDITION2 OR CONDITIONS
            | CONDITION2
            {printf("CONDITIONS -> CONDITION AND CONDITIONS | CONDITION OR CONDITIONS | NOT CONDITIONS | LB CONDITIONS RB | CONDITION\n");};
CONDITION2: CONDITION AND CONDITION2
            | CONDITION
            ;

CONDITION:  EXPRESSION OPR EXPRESSION
            | LB CONDITIONS RB
            | NOT LB CONDITIONS RB
            {printf("CONDITION -> EXPRESSION OPR EXPRESSION | LB CONDITION RB\n");};

OPR:    LT | GT | LTE | GTE | NEQ | EQ
        {printf("OPR -> LT | GT | LTE | GTE | NEQ | EQ\n");};

EXPRESSION:    ATTRIBUTE_LIST | DATA
        {printf("EXPRESSION -> ATTRIBUTE_LIST | DATA\n");};

ATTRIBUTE_LIST:   ATTRIBUTE | ATTRIBUTE COMMA ATTRIBUTE_LIST
        {printf("ATTRIBUTE_LIST -> ATTRIBUTE | ATTRIBUTE COMMA ATTRIBUTE_LIST\n");};

ATTRIBUTE:   NAME | NAME DOT NAME
        {printf("ATTRIBUTE -> NAME | NAME DOT NAME\n");};

DATA:   NUM | STR
        {printf("DATA -> NUM | STR\n");};

TABLE_NAME:    NAME
        {printf("TABLE_NAME -> NAME\n");};

EQUI_CONDITIONS: EQUI_CONDITION2 OR EQUI_CONDITIONS
            | EQUI_CONDITION2
            {printf("EQUI_CONDITIONS -> EQUI_CONDITION AND EQUI_CONDITIONS | EQUI_CONDITION OR EQUI_CONDITIONS | LB EQUI_CONDITIONS RB | EQUI_CONDITION\n");};

EQUI_CONDITION2: EQUI_CONDITION AND EQUI_CONDITION2
            | EQUI_CONDITION
            ;

EQUI_CONDITION:  EXPRESSION EQ EXPRESSION
            | LB EQUI_CONDITIONS RB
            {printf("EQUI_CONDITION -> EXPRESSION EQ EXPRESSION | LB EQUI_CONDITION RB\n");};
%%

int main(int argc, char *argv[]){
  yyparse();
  return 0;
}