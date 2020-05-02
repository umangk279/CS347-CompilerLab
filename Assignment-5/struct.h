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
	variable(string name, int type)
	{
		this->name = name;
		this->type = type;
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
	int search_function(string name);
	int add_function(string name, int return_type);
};

class type_{
public:	
	int type;
	type_(int type){
		this->type = type;
	}
};


#endif