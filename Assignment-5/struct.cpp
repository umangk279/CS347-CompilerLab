#include<bits/stdc++.h>
#include "struct.h"

using namespace std;

int symbol_table::search_function(string name)
{
	int size = this->global_symbol_table.size();
	for(int i=0; i<size; i++)
	{
		if(this->global_symbol_table[i]->name == name)
			return 1;
	}	
	return 0;
}

int symbol_table::add_function(string name, int return_type)
{
	func* temp = new func(name,return_type);
	this->global_symbol_table.push_back(temp);
	return this->global_symbol_table.size()-1;
}

void intermediate_code::insert(string s)
{
	this->output.push_back(s);
	this->index++;
	return;
}


variable* symbol_table::search_cur_var(int active_function_index, int decl_level, string name)
{
	if(active_function_index<0 || active_function_index>=global_symbol_table.size())
		return NULL;
	variable* ret = NULL;
	int size = this->global_symbol_table[active_function_index]->var_list.size();
	int level = -1;
	for(int i=0; i<size; i++)
	{
		if(global_symbol_table[active_function_index]->var_list[i]->name == name
			&& global_symbol_table[active_function_index]->var_list[i]->decl_level == decl_level)
		{
			if(global_symbol_table[active_function_index]->var_list[i]->decl_level >= level)
			{
				level = global_symbol_table[active_function_index]->var_list[i]->decl_level;
				ret = global_symbol_table[active_function_index]->var_list[i];
			}
		}
	}

	return ret;
}

int symbol_table::add_variable(int active_function_index, string name, int level, int type, int num_type, int dimension)
{
	if(active_function_index<0 || active_function_index>=global_symbol_table.size())
		return -1;
	variable* v = new variable(name,type,level,num_type, dimension);
	global_symbol_table[active_function_index]->var_list.push_back(v);
	return global_symbol_table[active_function_index]->var_list.size()-1;
}


int symbol_table::search_parameter(string name, int active_function_index)
{
	//cout<<"Searching parameter for active_function_index: "<<active_function_index<<endl;
	if(active_function_index<0 || active_function_index>=global_symbol_table.size())
		return -1;
	//cout<<"Begin"<<endl;
	int size = this->global_symbol_table[active_function_index]->param_list.size();
	for(int i=0; i<size; i++)
	{
		if(global_symbol_table[active_function_index]->param_list[i]->name == name)
			return i;
	}
	return -1;
}

void symbol_table::display_symbol_table()
{
	cout<<"Symbol Table:"<<endl;
	for(int i=0; i<global_symbol_table.size(); i++)
	{
		cout<<"Index: "<<i<<endl;
		cout<<"Function Name: "<<global_symbol_table[i]->name<<endl;
		cout<<"Return Type:"<<global_symbol_table[i]->return_type<<endl;
		cout<<"Parameter List: ";
		for(int x=0; x<global_symbol_table[i]->param_list.size(); x++)
		{
			cout<<global_symbol_table[i]->param_list[x]->name<<" ";
		}
		cout<<endl;

		cout<<"Variable List: "<<endl;
		for(int x=0; x<global_symbol_table[i]->var_list.size(); x++)
		{
			cout<<"Name: "<<global_symbol_table[i]->var_list[x]->name<<" "<<"Type: "<<global_symbol_table[i]->var_list[x]->num_type<<endl;
		}
		cout<<endl;
	}
}

void symbol_table::change_type(int active_function_index, vector<int>& indices,int type)
{
	if(active_function_index<0 || active_function_index>=global_symbol_table.size())
		return;

	int size = indices.size();
	for(int i=0; i<size; i++)
	{
		cout<<indices[i]<<" ";
		if(indices[i]<0 || indices[i]>=global_symbol_table[active_function_index]->var_list.size())
			continue;
		global_symbol_table[active_function_index]->var_list[indices[i]]->num_type = type;
	}
}

int symbol_table::add_parameter(int active_function_index, string name, int type, int num_type)
{
	//cout<<"Adddddddddddd at active_function_index: "<<active_function_index<<" Size:"<<global_symbol_table.size()<<endl;
	if(active_function_index<0 || active_function_index>=global_symbol_table.size())
		return -1;

	//cout<<"Adding parameter"<<endl;
	parameter* p = new parameter(name, type, num_type);
	global_symbol_table[active_function_index]->param_list.push_back(p);
	return global_symbol_table[active_function_index]->param_list.size()-1;
}

void symbol_table::set_no_of_parameters(int active_function_index, int no_of_parameters)
{
	if(active_function_index<0 || active_function_index>=global_symbol_table.size())
		return;

	global_symbol_table[active_function_index]->no_of_parameters = no_of_parameters;
	return;
}

void intermediate_code::insert2(string s, string op, string op2, string result)
{
	string str = s+" "+op+" "+op2+" "+result;
	this->insert(str);
}

variable* symbol_table::search_global_var(int active_function_index, int decl_level, string name)
{
	if(active_function_index<0 || active_function_index>=global_symbol_table.size())
		return NULL;

	variable* index = this->search_cur_var(active_function_index,decl_level,name);
	if(index!=NULL)
		return index;

	else
	{
		int parameter = search_parameter(name,active_function_index);
		if(parameter == -1)
		{
			return this->search_cur_var(0,decl_level,name);
		}
		else
		{
			if(global_symbol_table[active_function_index]->param_list[parameter]->type == 5)
			{
				index = new variable("_Tparam",global_symbol_table[active_function_index]->param_list[parameter]->type,1,global_symbol_table[active_function_index]->param_list[parameter]->num_type,1);
				
			}
			else
			{
				if(global_symbol_table[active_function_index]->param_list[parameter]->num_type == 1)
				{
					index = new variable("_Tparam",global_symbol_table[active_function_index]->param_list[parameter]->type,1,global_symbol_table[active_function_index]->param_list[parameter]->num_type,1);
				}
				if(global_symbol_table[active_function_index]->param_list[parameter]->num_type == 2)
				{
					index = new variable("_Fparam",global_symbol_table[active_function_index]->param_list[parameter]->type,1,global_symbol_table[active_function_index]->param_list[parameter]->num_type,1);
				
				}
			}

			return index;
		}
	}
}