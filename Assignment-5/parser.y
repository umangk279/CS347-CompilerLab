%{
	#include <bits/stdc++.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "struct.h"
	using namespace std;

	extern int yylex();

	int lineno = 0;
	void yyerror(string s)
	{
		//fprintf(stderr,"Error at line %d\n%s", lineno,s);
		cerr<<"Error at line "<<lineno<<endl<<s<<endl;
	}

	symbol_table ST;
	int active_function_index = 0;
	int level = 0;
	intermediate_code code;
	int gtemp = 0;
	int cond_tag = 0;
	int loop_tag = 0;
	temp_data all_temp_var;
	int function_call_index = -1;
	int max_param = 0;
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
	int no_of_parameters;
	expression_* exp;
	id_array_* ia_;
	assignment_* ass;
	case_* casee;
	case_list_* cl;
	d_* dc;
	stmt_* statement;
	plist_list_* pll;
	ifexp_* ie;
	n_* nnnn;
	loop_* loop;
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
%type<type> func_type_id 
%type<int_val> decl_id_array
%type<variable_list> var_list
%type<type> decl
%type<no_of_parameters> param_decl
%type<no_of_parameters> func_params
%type<exp> expression
%type<ia_> id_array
%type<exp> unary_expression
%type<exp> term
%type<exp> factor
%type<exp> operation
%type<exp> comparison
%type<exp> condition
%type<exp> bool_conditions
%type<ass> assignment
%type<casee> c
%type<cl> case_statement
%type<dc> d
%type<cl> case_list
%type<cl> case_statement_block
%type<statement> switch_case_statement
%type<statement> stmt 
%type<statement> stmt_block
%type<statement> stmt_list
%type<cl> default_statemnt
%type<pll> plist_list
%type<pll> plist
%type<exp> function_call
%type<ie> if_condition
%type<statement> if_block
%type<statement> loop_block
%type<nnnn> n
%type<loop> while_condition
%type<loop> forexp

%%

prog: stmt_list { printf("Accepted\n"); }
	  ;

stmt_list: stmt_list stmt
		   |
		   ;

stmt: RETURN SEMI
	  {
	  		$$ = new stmt_(1);
	  		$$->next.clear();
			$$->break_list.clear();
			$$->continue_list.clear();
			code.insert2("return","--","--","--");
	  }
	  | RETURN bool_conditions SEMI
	  {
	  		$$ = new stmt_(1);
	  		$$->next.clear();
			$$->break_list.clear();
			$$->continue_list.clear();
			code.insert2("return",$2->temp_name,"--","--");
	  }
	  | BREAK SEMI
	  {
	  		$$ = new stmt_(1);
	  		$$->next.clear();
			$$->break_list.push_back(code.get_index());
			code.insert2("goto","---","---","---");
			$$->continue_list.clear();
	  }
	  | CONTINUE SEMI
	  {
	  		$$ = new stmt_(1);
	  		$$->next.clear();
			$$->continue_list.push_back(code.get_index());
			code.insert2("goto","---","---","---");
			$$->break_list.clear();
	  }
	  | var_dec SEMI
	  | func_dec
	  {
	  		$$ = new stmt_(2);
	  		$$->next.clear();
			$$->break_list.clear();
			$$->continue_list.clear();
	  }
	  | if_block
	  {
	  		$$ = new stmt_(1);
	  		$$->error = false;
			$$->next.insert($$->next.end(),$1->next.begin(),$1->next.end());
			$$->break_list.clear();
			$$->continue_list.clear();
	  }
	  | loop_block
	  | stmt_block
	  {
	  	$$ = $1;
	  }
	  | switch_case_statement
	  {
	  		$$ = new stmt_(1);
	  		$$->error = false;
			$$->next.insert($$->next.end(),$1->next.begin(),$1->next.end());
			$$->break_list.clear();
			$$->continue_list.clear();
	  }
	  | assignment SEMI
	  {
	  		$$ = new stmt_(0);
	  		$$->next.clear();
			$$->break_list.clear();
			$$->continue_list.clear();
	  }
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

var_list: var_list COMMA decl_id_array
		  {
		  		$$ = new varList();
		  		$$->indices = $1->indices;
		  		$$->indices.push_back($3);
		  }
		  | decl_id_array
		  {
		  		$$ = new varList();
		  		$$->indices.push_back($1);
		  }
		  ;

func_dec:	func_header left_curly stmt_list right_curly
			;

func_header: func_type_id LB func_params RB
			;

func_type_id: type ID
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
			 {
			 	$$ = $1;
			 	ST.set_no_of_parameters(active_function_index,$$);
			 }
			 |
			 {
			 	$$ = 0;
			 	ST.set_no_of_parameters(active_function_index,$$);
			 }
			 ;

param_decl: param_decl COMMA decl
			{
				if(active_function_index!=-1)
				{
						if($3!=ERROR)
					{
						$$ = $1+1;
					}
					else
						$$ = $1;
				}
			}
			| decl
			{
				if(active_function_index!=-1)
				{
					if($1!=ERROR)
					{
						$$ = 1;
					}
					else
						$$ = 0;
				}
			}
			;

decl: type ID
	  {
		  	if(active_function_index!=-1)
		  	{
		  		string name($2);
		  		//cout<<"decl: active_function_index: "<<active_function_index<<endl;
		  		if(ST.search_parameter(name,active_function_index) == -1)
		  		{
		  			int index = ST.add_parameter(active_function_index, name, SIMPLE, $1);
		  			//cout<< "Parameter "<<name <<"added at index "<<index<<"for active_function_index: "<<active_function_index<<endl;
		  			$$ = $1;
		  		}
		  		else
		  		{
		  			//cout<<"I came here!"<< name<<endl;
		  			$$ = ERROR;
		  			yyerror("Variable previously listed as argument");
		  		}
		  	}
	  }
	  | type ID LSQ RSQ
	  {
		  	if(active_function_index!=-1)
		  	{
		  		string name = $2;
		  		if(ST.search_parameter(name,active_function_index) == -1)
		  		{
		  			int index = ST.add_parameter(active_function_index, name, ARRAY, $1);
		  			$$ = $1;
		  		}
		  		else
		  		{
		  			$$ = ERROR;
		  			yyerror("Variable previously listed as argument");
		  		}
		  	}
	  }
	  ;

type: INT { $$ = INT_TYPE; }
	  | FLOAT { $$ = FLOAT_TYPE; }
	  | VOID { $$ = VOID_TYPE; }
	  ;

if_block:	if_condition stmt ELSE n d stmt
			{
				cout<<"In if block"<<endl;
				$$ = new stmt_(1);
				if(active_function_index<=0)
				{
					yyerror("If can not be defined globally");
				}
				if((!$2->break_list.empty()) || (!$6->break_list.empty()))
				{
					yyerror("can not define break statement with in if block\nAborting");
					exit(1);
				}
				if(!($2->continue_list.empty()) || !($6->continue_list.empty()) )
				{
					yyerror("can not define break statement with in if block\nAborting");
					exit(1);
				}
				string tag = get_conditional_tag();
				code.patch_tag(tag,$1->false_list,$5->position);
				$$->break_list.clear();
				$$->continue_list.clear();
				$$->next.insert($$->next.end(),$2->next.begin(),$2->next.end());
				$$->next.insert($$->next.end(),$6->next.begin(),$6->next.end());
				$$->next.insert($$->next.end(),$4->next.begin(),$4->next.end());
			}
			| if_condition stmt
			{
				cout<<"In if block"<<endl;
				$$ = new stmt_(1);
				if(active_function_index<=0)
				{
					yyerror("If can not be defined globally");
				}
				if((!$2->break_list.empty()))
				{
					yyerror("can not define break statement with in if block\nAborting");
					exit(1);
				}
				if(!($2->continue_list.empty()))
				{
					yyerror("can not define break statement with in if block\nAborting");
					exit(1);
				}
				$$->break_list.clear();
				$$->continue_list.clear();
				$$->next.insert($$->next.end(),$1->false_list.begin(),$1->false_list.end());
				$$->next.insert($$->next.end(),$2->next.begin(),$2->next.end());
			}
			;

if_condition: IF LB assignment RB
			  {
			  		if($3->type!=ERROR)
			  		{
			  			$$ = new ifexp_(code.get_index());
			  			code.insert2("!=",$3->temp_name,"0","--");
			  		}
			  		else
			  		{
			  			$$ = new ifexp_(-1);
			  			yyerror("If condition invalid");
			  		}
			  }
			  ;

loop_block:	while_condition stmt
			{
				$$ = new stmt_(1);
				string tag = get_loop_tag();
				code.patch_tag(tag,$2->next,$1->jump_back_address);
				code.patch_tag_no_put(tag,$2->continue_list,$1->jump_back_address);
				code.insert2("goto","--","--",tag);
				$$->break_list.clear();
				$$->continue_list.clear();
				$$->next.insert($$->next.end(),$1->false_list.begin(),$1->false_list.end());
				$$->next.insert($$->next.end(),$2->break_list.begin(),$2->break_list.end());
			}
			| forexp d assignment d d RB stmt
			{
				$$ = new stmt_(1);
				string tag = get_loop_tag();
				code.patch_tag(tag,$7->next,$2->position);
				code.patch_tag_no_put(tag,$7->continue_list,$2->position);
				code.insert2("goto","--","--",tag);
				$$->break_list.clear();
				$$->continue_list.clear();
				string tag1 = get_loop_tag();
				code.put_tag($1->jump_back_address,tag1);
				code.gen_at_pos("goto -- --- "+tag1,$4->position);
				vector<int> temp;
				string tag2 = get_loop_tag();
				if(!($1->false_list.empty()))
				{
					
					temp.push_back(*($1->false_list.begin()) + 1);
					code.patch_tag(tag2,temp,$5->position);
				}
				$$->next.insert($$->next.end(),$1->false_list.begin(),$1->false_list.end());
				$$->next.insert($$->next.end(),$7->break_list.begin(),$7->break_list.end());
			}
			;

while_condition: WHILE d LB assignment RB
				{
					if(active_function_index<=0)
					{
					yyerror("Loops can not be global");
					}
					if($4->type!=ERROR)
					{
						$$ = new loop_(code.get_index(),$2->position);
						code.insert2("!=",$4->temp_name,"0","--");
					}
					else
					{
						yyerror("Invalid condition in while");
					}
				}
				;


forexp: FOR LB assignment SEMI d assignment SEMI
		{
			if(active_function_index<=0)
			{
				yyerror("Loops can not be global");
			}
			if($3->type != ERROR && $6->type != ERROR)
			{
				$$ = new loop_(code.get_index(), $5->position);
				code.insert2("!=",$6->temp_name,"0","--");
				code.insert2("goto","--","--","--");
			}
			else
			{
				yyerror("Invalid condition used in for");
			}
		}

stmt_block: left_curly stmt_list right_curly
			{
				$$ = new stmt_(0);
				$$->error = false;
				$$->next.insert($$->next.end(),$2->next.begin(),$2->next.end());
				$$->break_list.insert($$->break_list.end(),$2->break_list.begin(),$2->break_list.end());
				$$->continue_list.insert($$->continue_list.end(),$2->continue_list.begin(),$2->continue_list.end());
			}
			;

switch_case_statement: SWITCH LB operation RB LCURLY case_statement_block RCURLY
					{
						$$ = new stmt_(1);
						$$->next.insert($$->next.end(),$6->false_list.begin(),$6->false_list.end());
						$$->next.insert($$->next.end(),$6->break_list.begin(),$6->break_list.end());
						$$->next.insert($$->next.end(),$6->next.begin(),$6->next.end());
						$$->break_list.clear();
						$$->continue_list.clear();
						if(active_function_index <= 0)
						{
								yyerror("Switches can not be global");
						}
						code.patch_switch($3->temp_name,$6->false_list);
					}
					;

case_statement_block: case_list default_statemnt
				{
					string tag1 = get_conditional_tag();
					string tag2 = get_conditional_tag();
					code.patch_tag(tag2,$1->next,$2->second_address);
					vector<int> temp_index;
					if(!($1->false_list.empty())) temp_index.push_back($1->false_list.back());
					code.patch_tag(tag1,temp_index,$2->first_address);
					$$ = new case_list_($2->first_address,$2->second_address);
					$$->false_list.insert($$->false_list.end(),$1->false_list.begin(),$1->false_list.end());
					$$->false_list.insert($$->false_list.end(),$2->false_list.begin(),$2->false_list.end());
					$$->next.insert($$->next.end(),$2->next.begin(),$2->next.end());
					$$->break_list.insert($$->break_list.end(),$1->break_list.begin(),$1->break_list.end());
					$$->break_list.insert($$->break_list.end(),$2->break_list.begin(),$2->break_list.end());
				}
				| case_list
				{
					$$ = new case_list_($1->first_address,$1->second_address);
					$$->false_list.insert($$->false_list.end(),$1->false_list.begin(),$1->false_list.end());
					$$->break_list.insert($$->break_list.end(),$1->break_list.begin(),$1->break_list.end());
					$$->next.insert($$->next.end(),$1->next.begin(),$1->next.end());
					if(!($$->false_list.empty()))
					{
						$$->next.push_back($$->false_list.back());
					}
				}
				;

case_list: case_list case_statement
			{
				string tag1 = get_conditional_tag();
				string tag2 = get_conditional_tag();
				code.patch_tag(tag2,$1->next,$2->second_address);
				vector<int> temp_index;
				if(!($1->false_list.empty())) temp_index.push_back($1->false_list.back());	
				code.patch_tag(tag1,temp_index,$2->first_address);
				$$ = new case_list_($2->first_address,$2->second_address);
				$$->false_list.insert($$->false_list.end(),$1->false_list.begin(),$1->false_list.end());
				$$->false_list.insert($$->false_list.end(),$2->false_list.begin(),$2->false_list.end());
				$$->next.insert($$->next.end(),$2->next.begin(),$2->next.end());
				$$->break_list.insert($$->break_list.end(),$1->break_list.begin(),$1->break_list.end());
				$$->break_list.insert($$->break_list.end(),$2->break_list.begin(),$2->break_list.end());
			}
			| case_statement
			{
				$$ = new case_list_($1->first_address,$1->second_address);
				$$->false_list.insert($$->false_list.end(),$1->false_list.begin(),$1->false_list.end());
				$$->next.insert($$->next.end(),$1->next.begin(),$1->next.end());
				$$->break_list.insert($$->break_list.end(),$1->break_list.begin(),$1->break_list.end());
			}
			;

case_statement: CASE c operation COLON  d d stmt
				{
					$$ = new case_list_($2->first_address,$6->position);
					$$->false_list.push_back($5->position);
					code.back_patch_special("!=",$3->temp_name,"--","--",$5->position);
					//continue check
					int jump = code.get_index();
					code.insert2("goto"," "," "," ");
					$$->next.insert($$->next.end(),$7->next.begin(),$7->next.end());
					$$->next.push_back(jump);
					$$->break_list.insert($$->break_list.end(),$7->break_list.begin(),$7->break_list.end());
				}
				;

c:  
	{
		$$ = new case_(code.get_index());
		code.insert("");
	};

d:
	{
		$$ = new d_(code.get_index());
		code.insert("");
	}

n:
	{
		$$ = new n_(code.get_index());
		code.insert2("goto","--","--","--");
	}

default_statemnt: DEFAULT COLON c stmt
					{
						$$ = new case_list_($3->first_address,$3->first_address);
						$$->false_list.clear();
						//check continue
						int jump = code.get_index();
						code.insert2("goto"," "," "," ");
						$$->next.insert($$->next.end(),$4->next.begin(),$4->next.end());
						$$->next.push_back(jump);
						$$->break_list.insert($$->break_list.end(),$4->break_list.begin(),$4->break_list.end());
						$$->false_list.clear();
					}
					;

assignment:	id_array ASSIGN bool_conditions
			{
				if($1->var!=NULL)
				{
					int type = get_compatible_type_term($1->var->num_type,$3->type);
					if(type!=ERROR)
					{
						if($1->var->type==SIMPLE)
						{
							code.insert2("=",$3->temp_name," ",$1->var->name);
						}
						else
						{
							string t = "T"+to_string(gtemp);
							gtemp++;
							code.insert2("addr",$1->var->name," ",t);
							code.insert2("=", $3->temp_name," ",t);
						}
						$$ = new assignment_(type,"ERROR");
					}
					else
					{
						$$ = new assignment_(ERROR,"ERROR");
						yyerror("Incompatible data tyoes for assignment");
					}
				}
			}
			| bool_conditions
			{
				$$ = new assignment_($1->type,$1->temp_name);
			}
			;

bool_conditions:	bool_conditions AND condition
					{
						int type = get_compatible_type_comparison($1->type,$3->type);
						$$ = new expression_(type);
						if(type!=ERROR)
						{
							code.insert2("&&",$1->temp_name,$3->temp_name,$$->temp_name);
						}
					}
					| bool_conditions OR condition
					{
						int type = get_compatible_type_comparison($1->type,$3->type);
						$$ = new expression_(type);
						if(type!=ERROR)
						{
							code.insert2("||",$1->temp_name,$3->temp_name,$$->temp_name);
						}
					}
					| condition
					{
						$$ = new expression_($1->type,$1->temp_name);
						// if($1->type!=ERROR)
						// {
						// 	code.insert2("=",$1->temp_name," ",$$->temp_name);
						// }
					}
					;

condition: comparison
		  {
		  		$$ = new expression_($1->type,$1->temp_name);
		  		// if($1->type!=ERROR)
		  		// {
		  		// 	code.insert2("=",$1->temp_name," ",$$->temp_name);
		  		// }
		  }
		  | operation
		  {
		  		$$ = new expression_($1->type,$1->temp_name);
		  		// if($1->type!=ERROR)
		  		// {
		  		// 	code.insert2("=",$1->temp_name," ",$$->temp_name);
		  		// }
		  }
		  ;

comparison: operation GT operation
			{
				int type = get_compatible_type_comparison($1->type,$3->type);
				$$ = new expression_(type);
				if(type!=ERROR)
				{
					code.insert2(">",$1->temp_name," ",$3->temp_name);
				}
				else
				{
					yyerror("Relational operation on non-compatible data types.");
				}
			}
			| operation GTE operation
			{
				int type = get_compatible_type_comparison($1->type,$3->type);
				$$ = new expression_(type);
				if(type!=ERROR)
				{
					code.insert2(">=",$1->temp_name," ",$3->temp_name);
				}
				else
				{
					yyerror("Relational operation on non-compatible data types.");
				}
			}
			| operation LT operation
			{
				int type = get_compatible_type_comparison($1->type,$3->type);
				$$ = new expression_(type);
				if(type!=ERROR)
				{
					code.insert2("<",$1->temp_name," ",$3->temp_name);
				}
				else
				{
					yyerror("Relational operation on non-compatible data types.");
				}
			}
			| operation LTE operation
			{
				int type = get_compatible_type_comparison($1->type,$3->type);
				$$ = new expression_(type);
				if(type!=ERROR)
				{
					code.insert2("<=",$1->temp_name," ",$3->temp_name);
				}
				else
				{
					yyerror("Relational operation on non-compatible data types.");
				}
			}
			| operation EQ operation
			{
				int type = get_compatible_type_comparison($1->type,$3->type);
				$$ = new expression_(type);
				if(type!=ERROR)
				{
					code.insert2("==",$1->temp_name," ",$3->temp_name);
				}
				else
				{
					yyerror("Relational operation on non-compatible data types.");
				}
			}
			| operation NEQ operation
			{
				int type = get_compatible_type_comparison($1->type,$3->type);
				$$ = new expression_(type);
				if(type!=ERROR)
				{
					code.insert2("!=",$1->temp_name," ",$3->temp_name);
				}
				else
				{
					yyerror("Relational operation on non-compatible data types.");
				}
			}
			;

operation: operation PLUS term
			{
				int type = get_compatible_type_term($1->type,$3->type);
				$$ = new expression_(type);
				if(type!=ERROR)
				{
					code.insert2("+",$1->temp_name," ",$3->temp_name);
				}
				else
				{
					yyerror("Addition operation on non-compatible data types.");
				}
			}
		   | operation MINUS term
		   {
		   		int type = get_compatible_type_term($1->type,$3->type);
				$$ = new expression_(type);
				if(type!=ERROR)
				{
					code.insert2("-",$1->temp_name," ",$3->temp_name);
				}
				else
				{
					yyerror("Subtraction operation on non-compatible data types.");
				}
		   }
		   | term
		   {
		   		$$ = new expression_($1->type,$1->temp_name);
		   		// if($1->type!=ERROR)
		   		// {
		   		// 	code.insert2("=",$1->temp_name," ",$$->temp_name);
		   		// }
		   }
		   ;

term: term MULTIPLY factor
	  {
	  	int type = get_compatible_type_term($1->type,$3->type);
	  	$$ = new expression_(type);
	  	if(type!=ERROR)
	  	{
	  		code.insert2("*",$1->temp_name," ",$$->temp_name);
	  	}
	  	else
	  	{
	  		yyerror("Multiply operation on non-compatible data types");
	  	}
	  }
	  | term DIVIDE factor
	  {
	  	int type = get_compatible_type_term($1->type,$3->type);
	  	$$ = new expression_(type);
	  	if(type!=ERROR)
	  	{
	  		code.insert2("/",$1->temp_name," ",$$->temp_name);
	  	}
	  	else
	  	{
	  		yyerror("Division operation on non-compatible data types");
	  	}
	  }
	  | factor
	  {
	  	$$ = new expression_($1->type,$1->temp_name);
	  	// if($1->type!=ERROR)
	  	// {
	  	// 	code.insert2("=",$1->temp_name," ",$$->temp_name);
	  	// }
	  }
	  ;

factor: unary_expression
		{
			$$ = new expression_($1->type,$1->temp_name);
			// if($1->type!=ERROR)
			// {
			// 	code.insert2("=",$1->temp_name," ",$$->temp_name);
			// }
		}
		;

unary_expression: expression
				{
					$$ = new expression_($1->type,$1->temp_name);
					// if($1->type != ERROR)
					// {
					// 	code.insert2("=",$1->temp_name," ",$$->temp_name);
					// }
				}
				| NOT unary_expression
				{
					if($2->type==FLOAT_TYPE)
					{
						$$ = new expression_(ERROR);
						yyerror("Invalid opaeration.");
					}
					else
					{
						$$ = new expression_($2->type);
						if($2->type!=ERROR)
						{
							code.insert2("NOT",$2->temp_name," ",$$->temp_name);
						}
					}
				}
				| MINUS unary_expression
				{
					if($2->type!=BOOL_TYPE)
					{
						$$ = new expression_($2->type);
						if($2->type != ERROR)
						{
							code.insert2("MINUS",$2->temp_name," ",$$->temp_name);
						}
					}
					else
					{
						yyerror("Invalid operation");
						$$ = new expression_(ERROR);
					}
				}
				| DECREMENT unary_expression
				{
					if($2->type!=BOOL_TYPE && $2->type!=FLOAT_TYPE)
					{
						$$ = new expression_($2->type);
						if($2->type!=ERROR)
						{
							code.insert2("-",$2->temp_name," 1 ",$$->temp_name);
						}
					}
					else
					{
						$$ = new expression_(ERROR);
						yyerror("Invalid operation.");
					}
				}
				| INCREMENT unary_expression
				{
					if($2->type!=BOOL_TYPE && $2->type!=FLOAT_TYPE)
					{
						$$ = new expression_($2->type);
						if($2->type!=ERROR)
						{
							code.insert2("+",$2->temp_name," 1 ",$$->temp_name);
						}
					}
					else
					{
						$$ = new expression_(ERROR);
						yyerror("Invalid operation.");
					}
				}
				;

expression: NUM_FLOAT
			{
				$$ = new expression_(FLOAT_TYPE);
				code.insert2("=",to_string($1)," ",$$->temp_name);
			}
			| NUM_INT
			{
				$$ = new expression_(INT_TYPE);
				code.insert2("=",to_string($1)," ",$$->temp_name);
			}
			| id_array
			{
				if($1->var == NULL)
				{
					//yyerror("Variable not declared");
					$$ = new expression_(ERROR);
				}
				else 
				{
					$$ = new expression_($1->var->num_type);
					code.insert2("=", $1->var->name," ",$$->temp_name);
				}
				
			}
			| LB bool_conditions RB
			{

				$$ = new expression_($2->type,$2->temp_name);
			}
			| function_call
			{
				$$ = new expression_($1->type,$1->temp_name);
			}
			;

function_call: ID LB plist RB
			{
				string name($1);
				function_call_index = ST.search_function(name);
				if(function_call_index != -1)
				{
					int compatiblity = ST.check_parameter_compatibility(function_call_index,$3->type_list);
					if(compatiblity!=-1)
					{
						string result_func = ST.generate_function_call(function_call_index,$3);
						$$ = new expression_(compatiblity,result_func);
					}
					else
					{
						$$ = new expression_(ERROR,"ERROR");
					}
				}
				else
				{
					yyerror("Function "+name+" not declared");
					$$ = new expression_(ERROR,"ERROR");
				}
			}

			 ;

plist: plist_list 
		{
			$$ = new plist_list_();
			$$->type_list = $1->type_list;
			$$->name_list = $1->name_list;
		}
		| 
		{
			$$ = new plist_list_();
			$$->type_list.clear();
			$$->name_list.clear();
		}
		;

plist_list: plist_list COMMA condition
		{
			$$ = new plist_list_();
			$$->type_list.insert($$->type_list.end(),$1->type_list.begin(),$1->type_list.end());
			$$->name_list.insert($$->name_list.end(),$1->name_list.begin(),$1->name_list.end());
			$$->type_list.push_back($3->type);
			$$->name_list.push_back($3->temp_name);
		}
		| condition
		{
			$$ = new plist_list_();
			$$->type_list.push_back($1->type);
			$$->name_list.push_back($1->temp_name);
		}
		;

decl_id_array: ID 
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
								if(ST.search_parameter(s,active_function_index) == -1)
								{
									int index = ST.add_variable(active_function_index,s,level,SIMPLE,INT_TYPE,0);
									$$ = index;
								}
								else
								{
									yyerror("variable re-declared");
									$$ = -1;
								}
							}
						
						}
						else
						{
							yyerror("variable re-declared");
							$$ = -1;
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
								if(ST.search_parameter(s,active_function_index) == -1)
								{
									int index = ST.add_variable(active_function_index,s,level,ARRAY,INT_TYPE,$3);
									$$ = index;
								}
								else
								{
									yyerror("variable re-declared");
									$$ = -1;
								}
							}
						
						}
						else
						{
							yyerror("variable re-declared");
							$$ =-1;
						}

					}
					cout<<"variable "<<$1<<" added successfully"<<endl;
		  		}
		  }
		  ;

id_array: ID
		  {
		  		if(active_function_index!=-1)
		  		{
		  			string s = $1;
		  			variable* v = ST.search_global_var(active_function_index,level,s);
		  			if(v==NULL)
		  			{
		  				string err = "Variable "+s+" not declared.";
		  				yyerror(err);
		  			}
		  			else
		  			{
		  				if(v->type!=SIMPLE)
		  				{
		  					v=NULL;
		  					yyerror("Variable "+s+" declared as array");
		  				}
		  			}
		  			$$ = new id_array_(v);
		  		}
		  }
		  | ID LSQ NUM_INT RSQ
		  {
		  		if(active_function_index!=-1)
		  		{
		  			string s($1);
		  			variable* v = ST.search_global_var(active_function_index,level,s);
		  			if(v == NULL)
		  			{
		  				string err = "Variable "+s+" not declared.";
		  				yyerror(err);
		  			}

		  			if(v!=NULL)
		  			{
		  				if(v->type != ARRAY)
		  				{
		  					v= NULL;
		  					string err = "Variable "+s+" not declared as array.";
		  					yyerror(err);
		  				}
		  			}

		  			if(v!=NULL)
		  			{
		  				string temp = "_T"+to_string(gtemp);
		  				gtemp++;
		  				code.insert2("=",to_string($3)," ",temp);
		  				all_temp_var.temp_var_name.push_back(temp);
		  			}

		  		$$ = new id_array_(v);
		  		}
		  }
		  ;

left_curly : LCURLY
			{ level++; }
			;

right_curly: RCURLY
			{ level--; }
			;
%%

int main()
{
	yyparse();
	ST.display_symbol_table();
	cout<<"--------------------"<<endl;
	code.print();
	cout<<"--------------------"<<endl;
}