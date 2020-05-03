#ifndef STRUCT_H
#define STRUCT_H


#include<bits/stdc++.h>
using namespace std;

class parameter
{
public:
	string name;
	int type;
	parameter(string name, int type)
	{
		this->name = name;
		this->type = type;
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
	func(string name, int return_type)
	{
		this->name = name;
		this->return_type = return_type;
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
	int add_variable(int active_function_index, string name, int level, int type, int num_type, int dimension);
	int search_parameter(string name, int active_function_index);
	void change_type(int active_function_index, vector<int> &indices,int type);
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
};

class varList
{
public:
	vector<int> indices;
	varList()
	{}
};


#endif