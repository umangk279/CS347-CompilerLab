%{
	#include <bits/stdc++.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "struct.h"
	#define INT_TYPE 1
	#define FLOAT_TYPE 2
	#define VOID_TYPE 3
	#define ERROR -1
	#define SIMPLE 4
	#define ARRAY 5
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
	intermediate_code code;
%}

%code requires{
	#ifndef _STRUCT_H_INCLUDED_
	#define _STRUCT_H_INCLUDED_
	#include "struct.h"
	#endif
}

%union{ 
	char* Char;
	int int_val;
	float float_val;
	int type;
	varList * variable_list;
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
%type<type> func_header 
%type<int_val> id_array
%type<variable_list> var_list

%%

prog: stmt_list { printf("Accepted\n"); }
	  ;

stmt_list: stmt_list stmt
		   |
		   ;

stmt: RETURN SEMI
	  | RETURN bool_conditions SEMI
	  | BREAK SEMI
	  | CONTINUE SEMI
	  | var_dec SEMI
	  | func_dec
	  | if_block
	  | loop_block
	  | stmt_block
	  | switch_case_statement
	  | assignment SEMI
	  | SEMI
	  ;

var_dec: type var_list
		{
			if(active_function_index!=-1)
			{
				ST.change_type(active_function_index,$2->indices,$1);
			}
		}
		;

var_list: var_list COMMA id_array
		  {
		  		$$ = new varList();
		  		$$->indices = $1->indices;
		  		$$->indices.push_back($3);
		  }
		  | id_array
		  {
		  		$$ = new varList();
		  		$$->indices.push_back($1);
		  }
		  ;

func_dec:	func_header left_curly stmt_list right_curly
			;

func_header: type ID LB func_params RB
			{
				string name = $2;
				if(ST.search_function(name)==1)
				{
					$$ = ERROR;
					yyerror("Function already declared");
					active_function_index = -1;
				}
				else
				{
					$$ = $1;
					active_function_index = ST.add_function(name,$1);
					level =1;
					string s = "function_"+name+":";
					code.insert(s);
					cout<<"Function added successfully"<<endl;
				}
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
	  | FLOAT { $$ = FLOAT_TYPE; }
	  | VOID { $$ = VOID_TYPE; }
	  ;

if_block:	if_condition stmt ELSE stmt
			| if_condition stmt;

if_condition: IF LB assignment RB
			  ;

loop_block:	while_condition stmt
			| for_condition stmt
			;

while_condition: WHILE LB assignment RB
				;

for_condition: FOR LB assignment SEMI assignment SEMI assignment RB

stmt_block: left_curly stmt_list right_curly
			;

switch_case_statement: SWITCH LB operation RB left_curly case_statement_block right_curly
					;

case_statement_block: case_list default_statemnt
				| case_list
				;

case_list: case_list case_statement
			| case_statement
			;

case_statement: CASE operation COLON stmt
				;

default_statemnt: DEFAULT COLON stmt
					;

assignment:	id_array ASSIGN bool_conditions
			| bool_conditions
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
		  {
				if(active_function_index!=-1)
				{
					string s = $1;
					variable* v = ST.search_cur_var(active_function_index, level, s);

					if(v==NULL)
					{
						int index = ST.add_variable(active_function_index,s,level,SIMPLE,INT_TYPE,0);
						$$ = index;
					}
					else
					{
						if(v->decl_level != level)
						{
							if(level!=2)
							{
								int index = ST.add_variable(active_function_index,s,level,SIMPLE,INT_TYPE,0);
								$$ = index;
							}

							else
							{
								if(ST.search_parameter(s,active_function_index) == 0)
								{
									int index = ST.add_variable(active_function_index,s,level,SIMPLE,INT_TYPE,0);
									$$ = index;
								}
								else
								{
									yyerror("variable re-declared");
								}
							}
						
						}
						else
						{
							yyerror("variable re-declared");
						}

					}
				}  
		  }
		  | ID LSQ NUM_INT RSQ
		  {
		  		if(active_function_index!=-1)
		  		{
		  			string s = $1;
					variable* v = ST.search_cur_var(active_function_index, level, s);

					if(v==NULL)
					{
						int index = ST.add_variable(active_function_index,s,level,ARRAY,INT_TYPE,$3);
						$$ = index;
					}
					else
					{
						if(v->decl_level != level)
						{
							if(level!=2)
							{
								int index = ST.add_variable(active_function_index,s,level,ARRAY,INT_TYPE,$3);
								$$ = index;
							}

							else
							{
								if(ST.search_parameter(s,active_function_index) == 0)
								{
									int index = ST.add_variable(active_function_index,s,level,ARRAY,INT_TYPE,$3);
									$$ = index;
								}
								else
								{
									yyerror("variable re-declared");
								}
							}
						
						}
						else
						{
							yyerror("variable re-declared");
						}

					}
					cout<<"variable "<<$1<<" added successfully"<<endl;
		  		}
		  }
		  ;

left_curly : LCURLY
			{ level++; }
			;

right_curly: RCURLY;
%%

int main()
{
	yyparse();
	ST.display_symbol_table();
}