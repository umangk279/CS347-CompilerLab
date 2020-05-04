#ifndef STRUCT_H
#define STRUCT_H


#include<bits/stdc++.h>
using namespace std;
extern int gtemp;

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
		}
		else
			this->temp_name = "ERROR";
	}
};


#endif