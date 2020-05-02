%{
	#include <bits/stdc++.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "struct.h"
	#define INT_TYPE 1
	#define FLOAT_TYPE 2
	#define VOID_TYPE 3
	using namespace std;

	extern int yylex();

	int lineno = 0;
	void yyerror(char *s)
	{
		fprintf(stderr,"Error at line %d\n%s", lineno,s);
	}

	symbol_table ST;
	int active_function_index = 0;
	int level = 0;
%}

%union{ 
	char* Char;
	int int_val;
	float float_val;
	int type;
}

%token<type> INT FLOAT VOID
%token IF ELSE FOR WHILE BREAK CONTINUE
%token SWITCH CASE DEFAULT RETURN PRINT
%token PLUS MINUS MULTIPLY DIVIDE MOD
%token ASSIGN OR AND NOT SEMI COMMA COLON
%token LT GT LTE GTE EQ NEQ LB RB LSQ RSQ LCURLY RCURLY INCREMENT DECREMENT
%token<Char> ID 
%token<int_val> NUM_INT 
%token<float_val> NUM_FLOAT

%left OR AND EQ NEQ GT LT
%left PLUS MINUS MULTIPLY DIVIDE NOT

%type<type> type

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

func_dec:	func_header left_curly stmt_list right_curly
			;

func_header: type ID LB func_params RB
			{
				string s($2);
				cout<<"$1:type: "<<$1<<endl;
				cout<<"$2:id: "<<s<<endl;
			}
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

type: INT { $$ = INT_TYPE; }
	  | FLOAT 
	  | VOID 
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

stmt_block: left_curly stmt_list right_curly
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

left_curly : LCURLY;

right_curly: RCURLY;
%%

int main()
{
	yyparse();
}