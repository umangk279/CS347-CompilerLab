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