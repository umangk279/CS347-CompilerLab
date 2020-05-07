#include<bits/stdc++.h>

using namespace std;

ifstream interfile;
ofstream mipsfile;
ofstream datafile; // for .data file

vector<string> content;
vector<string> data_name;
vector<string> data_size;

vector<string> parameters;

class count_float
{
public:
	int count;
	count_float()
	{
		this->count = 0;
	}
	string get_count(string str)
	{
		string s = "float_const" + to_string(count);
		count++;
		datafile << s << ": .float " << str << endl;
		return s;
	}
};
count_float cf;

void restore_system_stack()
{
    for (int i = data_name.size() - 1; i >= 0; i--)
    {
      mipsfile<<"la $t0, "<<data_name[i]<<endl;
      stringstream temp(data_size[i]);
      int size = 0;
      temp >> size;
      for (int j = size - 4; j >= 0; j = j - 4)
      {
        mipsfile<<"addiu $sp, $sp, 4"<<endl;
        mipsfile<<"l.s $f0, "<<"0($sp)"<<endl;
        mipsfile<<"s.s $f0, "<<to_string(j)<<"($t0)"<<endl;
      }
    }
    return;
}

void func_return (vector<string> v)
{
	//mipsfile << v[0] << " return" << endl;
	if(v[3] == "main") return;
  	mipsfile<<"lw $ra, 0($fp)"<<endl;
  	mipsfile<<"addiu $sp, $sp, 4"<<endl;
  	restore_system_stack();
  	mipsfile<<"addiu $fp, $sp, 4"<<endl;
  	mipsfile<<"jr $ra"<<endl;
	return;
}

void copy_parameters (int num)
{
	for(int i = 0; i < num; i++)
	{
	    if (parameters[i][1] == 'T')
	    {
	        mipsfile<<"la $t0, "<<parameters[i]<<endl;
	        mipsfile<<"lw $t1, "<<"0($t0)"<<endl;
	        mipsfile<<"la $t2, "<<"_Tparam_"<<i<<endl;
	        mipsfile<<"sw $t1, "<<"0($t2)"<<endl;
	    }
	    if (parameters[i][1] == 'F')
	    {
	      mipsfile<<"la $t0, "<<parameters[i]<<endl;
	      mipsfile<<"l.s $f1, "<<"0($t0)"<<endl;
	      mipsfile<<"la $t2, "<<"_Tparam_"<<i<<endl;
	      mipsfile<<"s.s $f1, "<<"0($t2)"<<endl;
	    }
  	}
  	return;
}

void store_stack ()
{
	for(int i = 0; i < data_name.size(); i++)
	{
	    mipsfile<<"la $t0, "<<data_name[i]<<endl;
	    stringstream temp(data_size[i]);
	    int size = 0;
	    temp >> size;
	    for(int j = 0; j < size; j = j+4)
	    {
	      mipsfile<<"l.s $f0, "<<to_string(j)<<"($t0)"<<endl;
	      mipsfile<<"s.s $f0, 0($sp)"<<endl;
	      mipsfile<<"addiu $sp, $sp, -4"<<endl;
	    }
  	}
	return;
}

void func_call (vector<string> v)
{
	//mipsfile << v[0] << " call" << endl;
	string function_name = v[2];
	string number_of_parameters = v[3];
	int num = 0;
	stringstream temp(number_of_parameters);
	temp >> num;

	if(num > parameters.size())
	{
	    cout<<"Parameter Overflow Error at "<<v[0]<<endl;
	    exit(1);
  	}
  	store_stack();
  	copy_parameters(num);
  	mipsfile<<"jal "<<function_name<<endl;
  	if(num == parameters.size() - 1)
  	{
	    mipsfile<<"la $t0, "<<parameters[num]<<endl;
	    mipsfile<<"s.s $f11, 0($t0)"<<endl;
  	}
  	mipsfile<<"lw $ra, 4($sp)"<<endl;
  	parameters.clear();
	return;
}

void func_parameters (vector<string> v)
{
	//mipsfile << v[0] << " parameters" << endl;
	string parameter_name = v[2];
	parameters.push_back(parameter_name);
	return;
}

void func_end (vector<string> v)
{
  	mipsfile<<"lw $ra, 0($fp)"<<endl;
  	mipsfile<<"addiu $sp, $sp, 4"<<endl;
  	restore_system_stack();
  	mipsfile<<"addiu $fp, $sp, 4"<<endl;
  	mipsfile<<"jr $ra"<<endl;
	return;
}

void func_begin (vector<string> v)
{
	mipsfile<<"move $fp, $sp"<<endl;
	mipsfile<<"sw $ra, 0($sp)"<<endl;
	mipsfile<<"addiu $sp, $sp, -4"<<endl;
	return;
}

void bool_operation (string op, string operand1, string operand2, string res)
{
	//mipsfile << "Okay till here!" << endl;
	mipsfile<<"la $t0, "<<operand1<<endl;
	mipsfile<<"la $t1, "<<operand2<<endl;
	mipsfile<<"la $t2, "<<res<<endl;
	mipsfile<<"lw $t3, 0($t0)"<<endl;
	mipsfile<<"lw $t4, 0($t1)"<<endl;

	if(op == "AND") mipsfile<<"and $t5, $t3, $t4"<<endl;
	else if(op == "OR") mipsfile<<"or $t5, $t3, $t4"<<endl;

	mipsfile<<"sw $t5, 0($t2)"<<endl;

	return;
}

void relational_operation_int (string op, string operand1, string operand2, string res)
{
	//mipsfile << " : int" << endl;
	if(op == "==")
    	mipsfile<<"beq "<<operand1<<", "<<operand2<<", "<<res<<endl;
    
    else if(op == "!=")
    	mipsfile<<"bne "<<operand1<<", "<<operand2<<", "<<res<<endl;
    
    else if(op == "<=")
     	mipsfile<<"ble "<<operand1<<", "<<operand2<<", "<<res<<endl;
   
   	else if(op == ">=")
     	mipsfile<<"bge "<<operand1<<", "<<operand2<<", "<<res<<endl;
   
   	else if(op == "<")
     	mipsfile<<"blt "<<operand1<<", "<<operand2<<", "<<res<<endl;
   
   	else if(op == ">")
     	mipsfile<<"bgt "<<operand1<<", "<<operand2<<", "<<res<<endl;
   
	return;
}

void relational_operation_float (string op, string operand1, string operand2, string res)
{
	//mipsfile << " : float" << endl;
	if (op == "==" or op == "!=")
	{
	    mipsfile<<"c.eq.s "<<operand1<<", "<<operand2<<endl;
	    if (op == "==") mipsfile<<"bc1t "<<res<<endl;
	    else mipsfile<<"bc1f "<<res<<endl;
  	}
  	if (op == ">" or op == "<")
  	{
	    if(op == ">")
	    {
	    	mipsfile<<"c.lt.s "<<operand2<<", "<<operand1<<endl;
	      	mipsfile<<"bc1t "<<res<<endl;
	    }
	    else
	    {
	      	mipsfile<<"c.lt.s "<<operand1<<", "<<operand2<<endl;
	      	mipsfile<<"bc1t "<<res<<endl;
	    }
  	}
  	if(op == ">=" or op == "<=")
  	{
	    if(op == ">=")
	    {
	      	mipsfile<<"c.le.s "<<operand2<<", "<<operand1<<endl;
	      	mipsfile<<"bc1t "<<res<<endl;
	    }
	    else
	    {
	      	mipsfile<<"c.le.s "<<operand1<<", "<<operand2<<endl;
	      	mipsfile<<"bc1t "<<res<<endl;
	    }
  	}
	return;
}

void relational_operation (vector<string> v)
{
	//cout << "okay till here" << endl;
	if ( v[4].empty() )
	{
	    cout << "Problem in Intermediate Code : " << v[0] << endl;
		exit(1);
  	}

  	if ( v[4][v[4].size()-1] != ':')
  	{
	    cout << "Problem in Intermediate Code : " << v[0] << endl;
		exit(1);
  	}
  	else v[4][v[4].size()-1] = ' ';

  	if(v[2][1]== 'F' and v[3][1]== 'F')
  	{
	    mipsfile<<"la $t0, "<<v[2]<<endl;
	    mipsfile<<"la $t1, "<<v[3]<<endl;
	    mipsfile<<"l.s $f0, 0($t0)"<<endl;
	    mipsfile<<"l.s $f1, 0($t1)"<<endl;
	    relational_operation_float(v[1],"$f0","$f1",v[4]);
	    return;
  	}

  	if(v[2][1]== 'T' and v[3][1]== 'T')
  	{
	    mipsfile<<"la $t0, "<<v[2]<<endl;
	    mipsfile<<"la $t1, "<<v[3]<<endl;
	    mipsfile<<"lw $t2, 0($t0)"<<endl;
	    mipsfile<<"lw $t3, 0($t1)"<<endl;
	    relational_operation_int(v[1],"$t2","$t3",v[4]);
	    return;

  	}
  	if(v[2][1]== 'T' and v[3][1]== 'F')
  	{
	    mipsfile<<"la $t0, "<<v[2]<<endl;
	    mipsfile<<"la $t1, "<<v[3]<<endl;
	    mipsfile<<"l.s $f0, 0($t0)"<<endl;
	    mipsfile<<"cvt.s.w $f0, $f0"<<endl;
	    mipsfile<<"l.s $f1, 0($t1)"<<endl;
	    relational_operation_float(v[1],"$f0","$f1",v[4]);
	    return;
  	}
  	if(v[2][1]== 'F' and v[3][1]== 'T')
  	{
	    mipsfile<<"la $t0, "<<v[2]<<endl;
	    mipsfile<<"la $t1, "<<v[3]<<endl;
	    mipsfile<<"l.s $f0, 0($t0)"<<endl;
	    mipsfile<<"l.s $f1, 0($t1)"<<endl;
	    mipsfile<<"cvt.s.w $f1, $f1"<<endl;
	    relational_operation_float(v[1],"$f0","$f1",v[4]);
	    return;
  	}

	return;
}

void temp_assignment (vector<string> v)
{
	if (v[2][0] != '_' or v[4][0] != '_' )
	{
		cout << "Problem in Intermediate Code : " << v[0] << endl;
		exit(1);
	}

	if (v[2][1] == 'F' and v[4][1] == 'F')
	{
	    mipsfile<<"la $t0, "<<v[2]<<endl;
	    mipsfile<<"la $t1, "<<v[4]<<endl;
	    mipsfile<<"l.s $f0, "<<"0($t0)"<<endl;
	    mipsfile<<"s.s $f0, "<<"0($t1)"<<endl;
	    return;
	}
	if (v[2][1] == 'T' and v[4][1] == 'T')
	{
	    mipsfile<<"la $t0, "<<v[2]<<endl;
	    mipsfile<<"la $t1, "<<v[4]<<endl;
	    mipsfile<<"lw $t2, "<<"0($t0)"<<endl;
	    mipsfile<<"sw $t2, "<<"0($t1)"<<endl;
	    return;
	}
	if (v[2][1] == 'T' and v[4][1] == 'F')
	{
		mipsfile<<"la $t0, "<<v[2]<<endl;
	    mipsfile<<"la $t1, "<<v[4]<<endl;
	    mipsfile<<"lw $t2, "<<"0($t0)"<<endl;
	    mipsfile<<"mtc1 $t2, "<<"$f0"<<endl;
	    mipsfile<<"cvt.s.w $f0, "<<"$f0"<<endl;
	    mipsfile<<"s.s $f0, "<<"0($t1)"<<endl;
	}
	if (v[2][1] == 'F'  and  v[4][1] == 'T')
	{
	    mipsfile<<"la $t0, "<<v[2]<<endl;
	    mipsfile<<"la $t1, "<<v[4]<<endl;
	    mipsfile<<"l.s $f0, "<<"0($t0)"<<endl;
	    mipsfile<<"cvt.w.s $f0, "<<"$f0"<<endl;
	    mipsfile<<"s.s $f0, "<<"0($t1)"<<endl;
	}
	return;
}

void id_first_assignment (vector<string> v)
{
	//mipsfile << v[0] << "  first" << endl;
	if (v[4][0] != '_')
	{
		cout << "Problem in Intermediate Code : " << v[0] << endl;
		exit(1);
	}
	if (v[4][1] == 'T')
	{
		mipsfile<<"la $t0, "<<v[2]<<endl;
	    mipsfile<<"la $t1, "<<v[4]<<endl;
	    mipsfile<<"lw $t2, "<<"0($t0)"<<endl;
	    mipsfile<<"sw $t2, "<<"0($t1)"<<endl;

	}
	else if (v[4][1] == 'F')
	{
		mipsfile<<"la $t0, "<<v[2]<<endl;
	    mipsfile<<"la $t1, "<<v[4]<<endl;
	    mipsfile<<"l.s $f0, "<<"0($t0)"<<endl;
	    mipsfile<<"s.s $f0, "<<"0($t1)"<<endl;
	}
	return;
}

void id_second_assignment (vector<string> v)
{
	//mipsfile << v[0] << "  second" << endl;
	if (v[2][0] != '_')
	{
		cout << "Problem in Intermediate Code : " << v[0] << endl;
		exit(1);
	}
	if (v[2][1] == 'T')
	{
		mipsfile<<"la $t0, "<<v[2]<<endl;
    	mipsfile<<"la $t1, "<<v[4]<<endl;
    	mipsfile<<"lw $t2, "<<"0($t0)"<<endl;
    	mipsfile<<"sw $t2, "<<"0($t1)"<<endl;
	}
	else if (v[2][1] == 'F')
	{
		mipsfile<<"la $t0, "<<v[2]<<endl;
    	mipsfile<<"la $t1, "<<v[4]<<endl;
    	mipsfile<<"l.s $f0, "<<"0($t0)"<<endl;
    	mipsfile<<"s.s $f0, "<<"0($t1)"<<endl;
	}
	return;
}

void num_assignment (vector<string> v)
{
	//cout << "okay till here" << endl;
	if (v[4][0] != '_')
	{
		cout << "Problem in Intermediate Code : " << v[0] << endl;
		exit(1);
	}
	if (v[4][1] == 'T')
	{
		mipsfile<<"la $t0, "<<v[4]<<endl;
	    mipsfile<<"li $t1, "<<v[2]<<endl;
	    mipsfile<<"sw $t1, "<<"0($t0)"<<endl;
	}
	else if (v[4][1] == 'F')
	{
		mipsfile<<"la $t0, "<<v[4]<<endl;
	    string str = cf.get_count(v[2]);
	    mipsfile<<"l.s $f0, "<<str<<endl;
	    mipsfile<<"s.s $f0, "<<"0($t0)"<<endl;
	}	
	return;
}

void simple_assignment (vector<string> v)
{
	if (isdigit(v[2][0]))
	{
		num_assignment(v);
		return;
	}
	if (v[2][0] != '_')
	{
		id_first_assignment(v);
		return;
	}
	else if (v[4][0] != '_')
	{
		id_second_assignment(v);
		return;
	}
	else 
	{
		temp_assignment(v);
		return;
	}
	return;
}

void int_operation_div (string op, string operand1, string operand2, string res)
{
	mipsfile<<"la $t0, "<<operand1<<endl;
  	mipsfile<<"la $t1, "<<operand2<<endl;
	mipsfile<<"la $t2, "<<res<<endl;
	mipsfile<<"lw $t3, 0($t0)"<<endl;
	mipsfile<<"lw $t4, 0($t1)"<<endl;
	mipsfile<<op<<" $t3, $t4"<<endl;
	mipsfile<<"mflo $t5 "<<endl;
	mipsfile<<"sw $t5, 0($t2)"<<endl;
	return;
}

void num_multiplication (vector<string> v)
{
	if(isdigit(v[2][0]) and isdigit(v[3][0]))
	{
	    cout << "Problem in Intermediate Code : " << v[0] << endl;
		exit(1);
	}
	  
	if(isdigit(v[2][0]))
	{
	    mipsfile<<"la $t0, "<<v[3]<<endl;
	    mipsfile<<"li $t1, "<<v[2]<<endl;
	    mipsfile<<"lw $t2, 0($t0)"<<endl;
	    mipsfile<<"mul $t3, $t1, $t2"<<endl;
	    mipsfile<<"la $t4, "<<v[4]<<endl;
	    mipsfile<<"sw $t3, 0($t4)"<<endl;
	    return;
	}

	if(isdigit(v[3][0]))
	{
	    mipsfile<<"la $t0, "<<v[2]<<endl;
	    mipsfile<<"li $t1, "<<v[3]<<endl;
	    mipsfile<<"lw $t2, 0($t0)"<<endl;
	    mipsfile<<"mul $t3, $t1, $t2"<<endl;
	    mipsfile<<"la $t4, "<<v[4]<<endl;
	    mipsfile<<"sw $t3, 0($t4)"<<endl;
	  	return;
	}
	return;
}

void int_operation (string op, string operand1, string operand2, string res)
{
	mipsfile<<"la $t0, "<<operand1<<endl;
  	mipsfile<<"la $t1, "<<operand2<<endl;
	mipsfile<<"la $t2, "<<res<<endl;
	mipsfile<<"lw $t3, 0($t0)"<<endl;
	mipsfile<<"lw $t4, 0($t1)"<<endl;
	mipsfile<<op<<" $t5, $t3, $t4"<<endl;
	mipsfile<<"sw $t5, 0($t2)"<<endl;
	return;
}

void float_operation (string op, string operand1, string operand2, string res)
{
	mipsfile<<"la $t0, "<<operand1<<endl;
  	mipsfile<<"la $t1, "<<operand2<<endl;
	mipsfile<<"la $t2, "<<res<<endl;
	mipsfile<<"l.s $t3, 0($t0)"<<endl;
	mipsfile<<"l.s $t4, 0($t1)"<<endl;
	mipsfile<<op<<" $f5, $f3, $f4"<<endl;
	mipsfile<<"s.s $f5, 0($t2)"<<endl;
	return;
}

void float_operation_int (string op, string operand1, string operand2, string res)
{
	mipsfile<<"la $t0, "<<operand1<<endl;
  	mipsfile<<"la $t1, "<<operand2<<endl;
	mipsfile<<"la $t2, "<<res<<endl;
	mipsfile<<"l.s $t3, 0($t0)"<<endl;
	mipsfile<<"l.s $t4, 0($t1)"<<endl;
	if(operand1[1] == 'T')
    	mipsfile<<"cvt.s.w $f3, $f3"<<endl;
  	if(operand2[1] == 'T')
    	mipsfile<<"cvt.s.w $f4, $f4"<<endl;
	mipsfile<<op<<" $f5, $f3, $f4"<<endl;
	mipsfile<<"s.s $f5, 0($t2)"<<endl;
	return;
}

void get_address_array (string array, string &addr, string &off)
{
	//cout << "okay till here" << endl;
	string temp;
	for (int i = 0; i < array.size(); i++)
	{
		if (array[i] == '[')
		{
			addr = temp;
			temp.clear();
			continue;
		}
		if (array[i] == ']') break;
		temp = temp + array[i];
	}
	off = temp;
	return;
}

bool check_array(string word)
{
	for( int i = 0; i < word.size(); i++)
  		if(word[i] == '[') return true;
    return false;
}

void array_assignment (vector<string> v)
{
	//cout << "okay till here" << endl;
	if (v[1].empty() or v[2].empty() or v[3].empty()) 
		return;
	if (v[1] != "=") 
	{
		cout << "Problem in Intermediate Code : " << v[0] << endl;
		exit(1);
	}

	bool a = check_array(v[2]);
	bool b = check_array(v[3]);
	if (a and b) 
	{
		cout << "Problem in Intermediate Code : " << v[0] << endl;
		exit(1);
	}
	//cout << a << "  " << b << endl;
	string address, offset;
	if (a)
	{
		get_address_array(v[2], address, offset);
		if(address.empty() or offset.empty()) return;
	     mipsfile<<"la $t0, "<<address<<endl;
	     mipsfile<<"lw $t1, "<<"0($t0)"<<endl;
	     mipsfile<<"la $t2, "<<offset<<endl;
	     mipsfile<<"lw $t3, "<<"0($t2)"<<endl;
	     mipsfile<<"add $t3, $t3, $t3"<<endl;
	     mipsfile<<"add $t3, $t3, $t3"<<endl;
	     mipsfile<<"add $t4, $t1, $t3"<<endl;
	     mipsfile<<"l.s $f0, "<<"0($t4)"<<endl;
	     mipsfile<<"la $t5, "<<v[3]<<endl;
	     mipsfile<<"s.s $f0, "<<"0($t5)"<<endl;
	    return;
		// cout << v[0] << " " << address << " "<< offset ;
		// cout << endl;
	}
	else if (b)
	{
		get_address_array(v[3], address, offset);
		if(address.empty() or offset.empty()) return;
	      mipsfile<<"la $t0, "<<address<<endl;
	      mipsfile<<"lw $t1, "<<"0($t0)"<<endl;
	      mipsfile<<"la $t2, "<<offset<<endl;
	      mipsfile<<"lw $t3, "<<"0($t2)"<<endl;
	      mipsfile<<"add $t3, $t3, $t3"<<endl;
	      mipsfile<<"add $t3, $t3, $t3"<<endl;
	      mipsfile<<"add $t4, $t1, $t3"<<endl;
	      mipsfile<<"la $t5, "<<v[2]<<endl;
	      mipsfile<<"l.s $f0, "<<"0($t5)"<<endl;
	      mipsfile<<"s.s $f0, "<<"0($t4)"<<endl;
      	return;
	}
	else 
	{
		cout << "Problem in Intermediate Code : " << v[0] << endl;
		exit(1);
	}
	return;
}

void generate_instruction (vector<string> v)
{
	//cout << "okay till here" << endl;
	//Error? if (v[0] == "5") cout << v[1] << endl << v[2];
	if (v.size() == 3)
	{
		// HANDLING LABELS
		if(v[1][v[1].size()-1] == ':')
	    {
	      if(v[1] == "main:") 
	      	mipsfile<< ".globl main"<< endl;
	      mipsfile<< v[1] << endl;
	      //cout << "y" << endl;
	      return;
	    }
	}

	// HANDLING ARRAY ASSIGNMENT 
	if (v.size() == 5)
	{
		array_assignment(v);
		return;
	} 

	if (v.size() <= 4) return;
	if (v[1].empty() or v[2].empty() or v[3].empty() or v[4].empty())
		return;

	// HANDLING ARITHMETIC OPERATIONS
	if (v[1] == "+")
  	{
	    if(v[2][1]=='T' and v[3][1]=='T' and v[4][1]=='T')
	    	int_operation("add", v[2], v[3], v[4]);

	    else if(v[2][1]=='F' and v[3][1]=='F' and v[4][1]=='F')
			float_operation("add.s", v[2], v[3], v[4]);
	  
	    else float_operation_int("add.s", v[2], v[3], v[4]);

	    return;
  	}

  	if (v[1] == "-")
  	{
	    if(v[2][1]=='T' and v[3][1]=='T' and v[4][1]=='T')
	     	int_operation("sub", v[2], v[3], v[4]);

	    else if(v[2][1]=='F' and v[3][1]=='F' and v[4][1]=='F')
	      	float_operation("sub.s", v[2], v[3], v[4]);

	    else float_operation_int("sub.s", v[2], v[3], v[4]);
	    
	    return;
  	}

  	if (v[1] == "*")
  	{
	    if (v[2][1]=='T' and v[3][1]=='T' and v[4][1]=='T')
		    int_operation("mul", v[2], v[3], v[4]);
	    
	    else if (v[2][1]=='F' and v[3][1]=='F' and v[4][1]=='F')
	      	float_operation("mul.s", v[2], v[3], v[4]);
	    
	    else
	    {
	      	if (isdigit(v[2][0]) or isdigit(v[3][0]))
	        	num_multiplication(v);

	      	else float_operation_int("mul.s", v[2], v[3], v[4]);
	    }
	    return;
  	}
  	
  	if (v[1] == "/")
  	{
	    if(v[2][1]=='T' and v[3][1]=='T' and v[4][1]=='T')
		    int_operation_div("div", v[2], v[3], v[4]);
	    
	    else if(v[2][1]=='F' and v[3][1]=='F' and v[4][1]=='F')
		    float_operation("div.s", v[2], v[3], v[4]);
	    
	    else float_operation_int("div.s", v[2], v[3], v[4]);

	    return;
  	}

  	// HANDLING SIMPLE ASSIGNMENT 
	if (v[1] == "=")
	{
		simple_assignment(v);
		return;
	}

  	// HANDLING RELATIONAL OPERATIONS
	if (v[1] == "==" or v[1] == "!=" or v[1] == "<=" or 
		v[1] == ">=" or v[1] == "<"  or v[1] == ">")
	{
    	relational_operation(v);
    	return;
  	}

  	// HANDLING ADDRESS IN ARRAY
  	if(v[1]== "addr")
  	{
	    bool flag = true;
	    if (v[2].size() >= 3)
	      	if(v[2][2] == 'p') flag = false;
	     
	    if( flag )
	    {
	      	mipsfile<<"la $t0, "<<v[2]<<endl;
	      	mipsfile <<"la $t1, "<<v[4]<<endl;
	      	mipsfile <<"sw $t0, "<<"0($t1)"<<endl;
	    }
	    else
	    {
	      	mipsfile<<"la $t0, "<<v[2]<<endl;
	      	mipsfile <<"la $t1, "<<v[4]<<endl;
	      	mipsfile <<"lw $t2, "<<"0($t0)"<<endl;
	      	mipsfile<<"sw $t2, "<<"0($t1)"<<endl;
    	}

    	return;
  	}

  	// HANDLING BOOLEAN OPERATIONS
  	if(v[1] == "NOT" or v[1] == "AND" or v[1] == "OR")
  	{
  		if(v[1] == "NOT")
  		{
		    if(v[2][1]!= 'T' or v[4][1]!= 'T' )
		    {
		    	cout << "Problem in Intermediate Code : " << v[0] << endl;
				exit(1);
		    }
		    mipsfile<<"la $t0, "<<v[2]<<endl;
		    mipsfile<<"la $t3, "<<v[4]<<endl;
		    mipsfile<<"lw $t1, 0($t0)"<<endl;
		    mipsfile<<"xori $t2, $t1, 1"<<endl;
		    mipsfile<<"sw $t2, 0($t3)"<<endl;
		    return;
  		}

  		if(v[2][1]!= 'T' or v[3][1]!= 'T' or v[4][1]!= 'T')
	    {
	      cout << "Problem in Intermediate Code : " << v[0] << endl;
		  exit(1);
	    }
	    bool_operation(v[1], v[2], v[3], v[4]);
  		return;
  	}

  	// HANDLING GOTO FUNCTIONALITY
  	if(v[1] == "goto")
  	{
	    if (v[4].empty())
	    {
		    cout << "Problem in Intermediate Code : " << v[0] << endl;
			exit(1);
	    }
	    if (v[4][v[4].size()-1] != ':')
	    {
	      	cout << "Problem in Intermediate Code : " << v[0] << endl;
			exit(1);
	    }
	    else v[4][v[4].size()-1] = ' ';
	    mipsfile<<"j "<<v[4]<<endl;
	    return;
  	}

  	// HANDLING UNARY MINUS
  	if(v[1] == "UMINUS")
  	{
	    if (v[2][1] == 'F')
	    {
		    mipsfile<<"la $t0, "<<v[2]<<endl;
		    mipsfile<<"l.s $f1, "<<"0($t0)"<<endl;
		    mipsfile<<"l.s $f2, "<<"0($t0)"<<endl;
		    mipsfile<<"add.s $f2, $f2, $f2"<<endl;
		    mipsfile<<"sub.s $f1, $f1, $f2"<<endl;
		    mipsfile<<"la $t3, "<<v[4]<<endl;
		    mipsfile<<"s.s $f1, "<<"0($t3)"<<endl;
		    return;
	    }
	    if (v[2][1] == 'T')
	    {
	    	mipsfile<<"la $t0, "<<v[2]<<endl;
	        mipsfile<<"lw $t1, "<<"0($t0)"<<endl;
	        mipsfile<<"lw $t2, "<<"0($t0)"<<endl;
	        mipsfile<<"add $t2, $t2, $t2"<<endl;
	        mipsfile<<"sub $t1, $t1, $t2"<<endl;
	        mipsfile<<"la $t3, "<<v[4]<<endl;
	        mipsfile<<"sw $t1, "<<"0($t3)"<<endl;
	        return;
	    }
  	}

	// HANDLING FUNCTION START & END
	if(v[1] == "func")
	{
    	if(v[2]== "begin")
    	{
      		func_begin(v);
      		return;
    	}
    	if(v[2]=="end")
    	{
      		if(v[3] != "main")
      		{
        		func_end(v);
        		return;
      		}
    	}
    	return;
  	}

  	// HANDLING PARAMETERS OF FUNCTION
  	if (v[1] == "param" or v[1] == "refparam")
  	{
  		func_parameters(v);
  		return;
  	}

  	// HANDLING CALL FUNCTIONALITY
  	if (v[1] == "call")
  	{
  		func_call(v);
  		return;
  	}

  	// HANDLING RETURN FUNCTIONALITY
  	if (v[1] == "return")
  	{
  		if (v[2][0] == '_')
  		{
  			mipsfile<<"la $t0, "<< v[2]<<endl;
        	mipsfile<<"l.s $f11, 0($t0)"<<endl;
  		}
  		func_return(v);
  		return;
  	}

  	// HANDLING PRINT FUNCTIONALITY
  	if (v[1] == "print")
  	{
	    if (v[2][1] == 'T')
	    {
	      	mipsfile<<"lw $a0, "<<v[2]<<endl;
	      	mipsfile<<"li $v0, 1"<<endl;
	      	mipsfile<<"syscall"<<endl;
	      	mipsfile<<"li $v0, 4"<<endl;
	      	mipsfile<<"la $a0 newline"<<endl;
	      	mipsfile<<"syscall"<<endl;
	    }
	    if(v[2][1] == 'F')
	    {
	      	mipsfile<<"l.s $f12, "<<v[2]<<endl;
	      	mipsfile<<"li $v0, 2"<<endl;
	      	mipsfile<<"syscall"<<endl;
	      	mipsfile<<"li $v0, 4"<<endl;
	      	mipsfile<<"la $a0 newline"<<endl;
	      	mipsfile<<"syscall"<<endl;
	    }
  	}

	else mipsfile << v[0] << endl;
	return;
}

vector<string> split_tokens (string line)
{
	//cout << "okay till here" << endl;
	vector<string> v;
	istringstream stream(line);
	string word;
	do 
	{
		stream >> word;
		v.push_back(word);
	} 
	while (stream);
	return v;
}

void generate_data_file()
{
	datafile << ".data" << endl;
	for(int i=0; i<data_name.size(); i++)
	{
		datafile << data_name[i] << " : " ;
		datafile << ".space " << data_size[i] << endl;
	}
	datafile << "newline:"<<" .asciiz "<<"\""<<"\\"<<"n"<<"\""<<endl;
}

int tokenize_intermediate ()
{
	//cout << "okay till here" << endl;
	for(int i=0; i<content.size(); i++)
	{
		vector<string> tokens = split_tokens(content[i]);
		if (tokens.empty()) continue;
		if(tokens[0] != "#" and tokens[0] != "##" ) return i;
    	if(tokens[0] == "##" ) continue;
    	if(tokens.size() < 3) continue;
    	else
    	{
	      data_name.push_back(tokens[1]);
	      data_size.push_back(tokens[2]);
	    }
	}
	// vector<string> temp = split_tokens(content[0]);
	// for(int i=0; i<temp.size(); i++)
	// 	cout << temp[i] << endl;
	return content.size();
}

void generate_mips ()
{
	//cout << "okay till here" << endl;
	int index = tokenize_intermediate();
	//cout << index << endl;
	generate_data_file();
	mipsfile << ".text" << endl;
  	mipsfile << "j main" << endl;

  	for(int l = index; l < content.size(); l++)
  	{
  		vector<string> v = split_tokens(content[l]);
  		mipsfile << v[0] << endl;
  		generate_instruction(v);
  		mipsfile << endl;
  	}

	return;
}

void readfile (string name)
{
	interfile.open(name, ios::in);
	string line;
	while(interfile.good())
	{
		getline(interfile, line);
		if (line != "") 
			content.push_back(line);
	}
	interfile.close();
	return;
}

int main (int argc, char **argv)
{
	if (argc < 2) {
		cout << "Intermediate file name not specified" << endl;
		exit(1);
	}
	readfile(argv[1]); 
	// for(int i=0; i<content.size(); i++)
	// 	cout << content[i] << endl;
	//interfile.open(argv[1], ios::in);
	mipsfile.open ("output.mips", ios::out | ios::trunc);
	datafile.open ("data.mips", ios::out | ios::trunc);
	generate_mips();
	mipsfile.close();
	datafile.close();

	ifstream ifile("output.mips");
	ofstream ofile("data.mips");

	if (!ifile.is_open()) 
	{
	    cout << "File output.mips cannot Open!" << endl;
	    exit(1);
  	}
  	else if (!ofile.is_open()) 
  	{
	    cout << "File data.mips cannot Open!" << endl;
	    exit(1);
  	}
  	else ofile << ifile.rdbuf();
  	ifile.close();
  	ofile.close();

	return 0;
}