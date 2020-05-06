#ifndef STRUCT_H
#define STRUCT_H


#include<bits/stdc++.h>
using namespace std;
extern void yyerror(string s);
extern int gtemp;
extern int cond_tag;
extern int loop_tag;
extern int max_param;

#define INT_TYPE 1
#define FLOAT_TYPE 2
#define VOID_TYPE 3
#define BOOL_TYPE 4
#define ERROR -1
#define SIMPLE 4
#define ARRAY 5

int get_compatible_type_term(int type1, int type2);
int get_compatible_type_comparison(int type1, int type2);

string get_conditional_tag();
string get_loop_tag();

class temp_data
{
public:
	vector<string> temp_var_name; 
};

extern temp_data all_temp_var;

class parameter
{
public:
	string name;
	int type;
	int num_type;
	parameter(string name, int type, int num_type)
	{
		this->name = name;
		this->type = type;
		this->num_type = num_type;
	} 
};

class variable
{
public:
	string name;
	int type;
	int num_type;
	int dimension;
	int decl_level;
	variable(string name, int type, int decl_level,int num_type, int dimension)
	{
		this->name = name;
		this->type = type;
		this->decl_level = decl_level;
		this->num_type = num_type;
		this->dimension = dimension;
	}
};

class func
{
public:
	string name;
	int return_type;
	vector<parameter* > param_list;
	vector<variable* > var_list;
	int no_of_parameters;
	func(string name, int return_type)
	{
		this->name = name;
		this->return_type = return_type;
		this->no_of_parameters = 0;
	}
};

class plist_list_
{
public:
	vector<int> type_list;
	vector<string> name_list;
};

class symbol_table
{
public:
	vector<func* > global_symbol_table;
	symbol_table()
	{}
	void display_symbol_table();
	int search_function(string name);
	int add_function(string name, int return_type);
	variable* search_cur_var(int active_function_index, int decl_level, string name);
	variable* search_global_var(int active_function_index, int decl_level, string name);
	int add_variable(int active_function_index, string name, int level, int type, int num_type, int dimension);
	int search_parameter(string name, int active_function_index);
	int add_parameter(int active_function_index, string name, int type, int num_type);
	void change_type(int active_function_index, vector<int> &indices,int type);
	void set_no_of_parameters(int active_function_index,int no_of_parameters);
	int check_parameter_compatibility(int call_function_index,vector<int> type_list);
	string generate_function_call(int call_function_index, plist_list_* temp);
};

class intermediate_code
{
public:
	vector<string> output;
	int index;
	intermediate_code()
	{
		this->index = 0;
	}
	void insert(string s);
	void insert2(string s, string op, string op2, string result);
	int get_index();
	void back_patch_special(string op,string op1,string op2,string result,int index);
	void put_tag(int index, string tag);
	void patch_tag(string tag, vector<int>indices, int index);
	void patch_switch(string tag, vector<int> indices);
	void patch_tag_no_put(string tag,vector<int> indices,int index);
	void gen_at_pos(string tag,int index);
	void print();
};

class varList
{
public:
	vector<int> indices;
	varList()
	{}
};

class expression_
{
public:
	string temp_name;
	int type;
	variable* var;
	expression_(int type)
	{
		this->type = type;
		if(type!=-1)
		{
			string temp = to_string(gtemp);
			gtemp++;
			if(type==2)
			{
				this->temp_name = "_F"+temp;
				all_temp_var.temp_var_name.push_back(this->temp_name);
			}
			else
			{
				this->temp_name = "_T"+temp;				
				all_temp_var.temp_var_name.push_back(this->temp_name);
			}
			this->var = NULL;
		}
		else
		{
			this->temp_name = "ERROR";
			this->var = NULL;
		}
	}
	expression_(int type, string name)
	{
		this->type = type;
		if(type!=-1)
		{
			this->temp_name = name;
		}
		else
			this->temp_name = "ERROR";
		this->var = NULL;
	}
};

class id_array_
{
public:
	variable* var;
	id_array_(variable* v1)
	{
		this->var = v1;
	}
};

class bool_conditions_
{
public:
	int type;
	string temp_name;
	bool_conditions_(int type)
	{
		this->type = type;
		if(type!=-1)
		{
			string temp = to_string(gtemp);
			gtemp++;
			if(type == 1)
			{
				this->temp_name = "_T"+temp;
				all_temp_var.temp_var_name.push_back(this->temp_name);
			}
			else
			{
				this->temp_name = "_F"+temp;
				all_temp_var.temp_var_name.push_back(this->temp_name);
			}
			
		}
		else
				this->temp_name = "ERROR";
	}
	bool_conditions_(int type, string name)
	{
		this->type = type;
		if(type!=-1)
		{
			this->temp_name = name;
		}
		else
			this->temp_name = "ERROR";
	}
};

class assignment_
{
public:
	int type;
	string temp_name;
	int valid_global;
	assignment_(int type, string temp_name)
	{
		this->type = type;
		this->temp_name = temp_name;
		this->valid_global = 0;
	}
};

class case_
{
public:
	int first_address;
	case_(int first_address)
	{
		this->first_address = first_address;
	}
};

class case_list_
{
public:
	int first_address;
	int second_address;
	vector<int> next;
	vector<int> break_list;
	vector<int> continue_list;
	vector<int> false_list;
	case_list_(int first_address, int second_address)
	{
		this->first_address = first_address;
		this->second_address = second_address;
	}
};

class d_
{
public:
	int position;
	d_(int position)
	{
		this->position = position;
	}
};

class stmt_
{
public:
	vector<int> next;
	vector<int> break_list;
	vector<int> continue_list;
	int valid_global;
	int error;
	int loop;
	stmt_(int valid_global)
	{
		this->valid_global = valid_global;
		this->error = false;
		this->loop = false;
	}
};

class n_{
public:
	vector<int> next;
	n_(int index){
		this->next.push_back(index);
	}
};

class ifexp_
{
public:
	vector<int> false_list;
	ifexp_(int index)
	{
		this->false_list.push_back(index);
	}
};

class loop_
{
public:
	vector<int> false_list;
	int jump_back_address;
	loop_(int index,int jump_back_address){
		this->false_list.push_back(index);
		this->jump_back_address = jump_back_address;
	}
};


#endif