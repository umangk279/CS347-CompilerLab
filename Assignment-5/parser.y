%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	void yyerror(char *s)
	{
		fprintf(stderr,"Syntax error\n");
	}

%}

%union{ char Char;}

%token INT FLOAT VOID
%token IF ELSE FOR WHILE BREAK CONTINUE
%token SWITCH CASE DEFAULT RETURN PRINT
%token PLUS MINUS MULTIPLY DIVIDE MOD
%token ASSIGN OR AND NOT SEMI COMMA COLON
%token LT GT LTE GTE EQ NEQ LB RB LSQ RSQ LCURLY RCURLY INCREMENT DECREMENT
%token ID NUM_INT NUM_FLOAT

%left OR AND EQ NEQ GT LT
%left PLUS MINUS MULTIPLY DIVIDE NOT

%%

prog: stmt_list { printf("Accepted\n"); }
	  ;

stmt_list: stmt_list stmt
		   |
		   ;

stmt: RETURN SEMI
	  | RETURN bool_conditions SEMI
	  | var_dec SEMI
	  | func_dec
	  | if_block
	  | loop_block
	  | stmt_block
	  | assignment SEMI
	  | SEMI
	  ;

var_dec: type var_list;

var_list: var_list COMMA id_array
		  | id_array
		  ;

func_dec:	func_header LCURLY stmt_list RCURLY
			;

func_header: type ID LB func_params RB
			 ;

func_params: param_decl
			 |
			 ;

param_decl: param_decl COMMA decl
			| decl
			;

decl: type ID
	  | type ID LSQ RSQ
	  ;

type: INT | FLOAT | VOID
			;

if_block:	if_condition stmt ELSE stmt
			| if_condition stmt;

if_condition: IF LB bool_conditions RB
			  ;

loop_block:	while_condition stmt
			| for_condition stmt
			;

while_condition: WHILE LB bool_conditions RB
				;

for_condition: FOR LB bool_conditions SEMI bool_conditions SEMI bool_conditions RB

stmt_block: LCURLY stmt_list RCURLY
			;

assignment:	id_array ASSIGN bool_conditions
			;

bool_conditions:	bool_conditions AND condition
					| bool_conditions OR condition
					| condition
					;

condition: comparison | operation
		   ;

comparison: operation GT operation
			| operation GTE operation
			| operation LT operation
			| operation LTE operation
			| operation EQ operation
			| operation NEQ operation
			;

operation: operation PLUS term
		   | operation MINUS term
		   | term
		   ;

term: term MULTIPLY factor
	  | term DIVIDE factor
	  | factor
	  ;

factor: unary_expression;

unary_expression: expression
				| NOT unary_expression
				| MINUS unary_expression
				| DECREMENT unary_expression
				| INCREMENT unary_expression
				;

expression: NUM_FLOAT
			| NUM_INT
			| id_array
			| LB bool_conditions RB
			;

id_array: ID 
		  | ID LSQ condition RSQ
		  ;

%%

int main()
{
	yyparse();
}