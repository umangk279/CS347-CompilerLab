#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <regex>

using namespace std;

// Using a stack to check if all parenthesis are matched in the code.
int checkBalancedParenthesis(string str)
{
  stack<char> st;
  char c;

  for(int i=0; i<str.length(); i++)
  {
    if(str[i]=='(' || str[i]=='{' || str[i]=='[')
      st.push(str[i]);

    else if(str[i]==')')
    {
      c = st.top();
      st.pop();
      if(c!='(')
        return -1;
    }
    else if(str[i]=='}')
    {
      c = st.top();
      st.pop();
      if(c!='{')
        return -2;
    }
    else if(str[i]==']')
    {
      c = st.top();
      st.pop();
      if(c!='[')
        return -3;
    }
  }

  if(st.empty())
    return 1;
  return 0;
}

int main(int argc, char* argv[])
{
	int source_code_statements = 0; 
	int blank_lines=0;
	int comments=0;
	int macros=0;
	int var_dec=0;
	int func_dec=0;
	int func_def=0;
	
	string line;
	ifstream file;

	file.open(argv[1]);

  // Matching every line with the regular expression to find the number of blank lines.
	regex re_blank("(\\s)*");
	while (getline(file, line))
	{
        source_code_statements++;
        if(regex_match(line,re_blank))
        {
        	blank_lines++;
        	continue;
        }
	}

	file.close();

	// Using a state machine to count and then strip single and multi-line comments
  file.open(argv[1]); 
	fstream file2;
  file2.open("comment_strip.c",ios::out); 
  
  enum states { TEXT, 
                SAW_SLASH, 
                SAW_STAR, 
                SINGLE_COMMENT, 
                MULTI_COMMENT } state = TEXT;
  
  int multi  = 0; //number of multi-line comments (using /* */)
  int single = 0; //number of single-line comments (using //)

  char c;
	while (file.get(c))
  	{
	    switch( state )
	    {
	      case TEXT :
	        switch( c )
	        {
	          case '/'  : state = SAW_SLASH; break;
	          default   : file2.put(c); break;
	        }
	        break;

	      case SAW_SLASH :
	        switch( c )
	        {
	          case '/'  : state = SINGLE_COMMENT; break;
	          case '*'  : state = MULTI_COMMENT; break;
	          default   : file2.put(c); state = TEXT; break;
	        }
	        break;

	      case SAW_STAR :
	        switch( c )
	        {
	          case '/'  : state = TEXT; multi++; break;
	          case '*'  : break;
	          case '\n' : multi++; // fall through
	          default   : state = MULTI_COMMENT; break;
	        }
	        break;

	      case SINGLE_COMMENT :
	        switch( c )
	        {
	          case '\n' : file2.put(c); state = TEXT; single++; // fall through
	          default   : break;
	        }
	        break;

	      case MULTI_COMMENT :
	        switch( c )
	        {
	          case '*'  : state = SAW_STAR; break;
	          case '\n' : multi++; // fall through
	          default   : break;
	        }
	        break;

	      default: // NOT REACHABLE
	        break;
	    }
  	}

  comments=multi+single;
  file.close();
  file2.close();

  // Content inside a string is removed to prevent any mismatches.
	file.open("comment_strip.c",ios::in);
	file2.open("comment_string_strip.c",ios::out);

	while (getline(file, line))
	{
       string str;
       regex re("\".*?\""); 
       str = regex_replace(line,re,"\" \"");
       file2 << str; 
       file2 << "\n";
	}

	file.close();
	file2.close();

  // Counting the number of lines with variable declarations using a regular expression.
  regex re_var_dec("((auto\\s*|const\\s*|unsigned\\s*|extern\\s*|signed\\s*|register\\s*|volatile\\s*|static\\s*|void\\s*|short\\s*|long\\s*|char\\s*|int\\s*|float\\s*|double\\s*|_Bool\\s*|complex\\s*)+)[ \\*]+[\\s\\*]*?[a-zA-Z_][a-zA-Z_0-9]*\\s*([^\\(\\))]*);");
     
  file.open("comment_string_strip.c");
  while(getline(file,line))
  {
    if(regex_search(line,re_var_dec))
    {
      //cout<<"hi"<<endl;
      cout<<line<<endl;
      var_dec++;
    }
  }
  file.close();  

  // Dumping the file content into a string for matching regular expressions.
	file.open("comment_string_strip.c");
	string str;
    if(file) 
    {
        ostringstream ss;
        ss << file.rdbuf(); //reading data from the file
        str = ss.str();
    }

  // Checking if the last line is a blank line.
  bool end_line = str[str.length()-1]=='\n';
  source_code_statements += end_line;
  blank_lines += end_line;

  // Printing all the counts in case of a paranthesis mismatch
  // Note that the number of Function declarations and definitions are not counted in case of parenthesis mismatch.
  int check = checkBalancedParenthesis(str);
  if(check!=1)
  {
    cout<<"Source Code Statements: "<<source_code_statements<<endl;
    cout<<"Blank Lines: "<<blank_lines<<endl;
    cout<<"Comment Lines: "<<comments<<endl;
    cout<<"Macros: "<<macros<<endl;
    cout<<"Variable Declarations: "<<var_dec<<endl;
    if(check==0)
    {
      cout<<"Parenthesis Mismatch"<<endl;
    }
    if(check==-1)
    {
      cout<<"( ) Mismatch"<<endl;
    }
    if(check==-2)
    {
      cout<<"{ } Mismatch"<<endl;
    }
    if(check==-3)
    {
      cout<<"[ ] Mismatch"<<endl;
    }
    exit(0);
  }

  // Using regular expressions to find instances of macro statements, function declarations and function definitions.

  regex re_macro("(\\s)*#(\\s)*(define)\\s"); 
  // (partial)regex re_fun_dec("(([a-zA-Z_][a-zA-Z_0-9]*[\\s\\*]*?){2,}\\(([^!@#$+%^;\\{\\}]*?)\\)[\\s]*;)");
  regex re_fun_dec("((auto\\s*|const\\s*|unsigned\\s*|extern\\s*|signed\\s*|register\\s*|volatile\\s*|static\\s*|void\\s*|short\\s*|long\\s*|char\\s*|int\\s*|float\\s*|double\\s*|_Bool\\s*|complex\\s*)+)[ \\*]+[\\s\\*]*?[a-zA-Z_][a-zA-Z_0-9]*\\(([^!@#$+%^;\\{\\}]*?)\\)[\\s]*;");
  regex re_fun_def("((auto\\s*|const\\s*|unsigned\\s*|extern\\s*|signed\\s*|register\\s*|volatile\\s*|static\\s*|void\\s*|short\\s*|long\\s*|char\\s*|int\\s*|float\\s*|double\\s*|_Bool\\s*|complex\\s*)+)[ \\*]+[\\s\\*]*?([a-zA-Z_][a-zA-Z_0-9]*[\\s\\*]*?)\\(([^!@#$+%^;\\{\\}]*?)\\)[\\s]*\\{");
 
  // Counting the macro statements
  auto words_begin = sregex_iterator(str.begin(), str.end(), re_macro);
  auto words_end = sregex_iterator();
  macros = distance(words_begin, words_end);

  // Counting the function declarations
  words_begin = sregex_iterator(str.begin(), str.end(), re_fun_dec);
  words_end = sregex_iterator();
  func_dec = distance(words_begin, words_end);

  // Counting the function definitions
  words_begin = sregex_iterator(str.begin(), str.end(), re_fun_def);
  words_end = sregex_iterator();
  func_def = distance(words_begin, words_end);

  // Printing the final outputs
  cout<<"Source Code Statements: "<<source_code_statements<<endl;
  cout<<"Blank Lines: "<<blank_lines<<endl;
  cout<<"Comment Lines: "<<comments<<endl;
  cout<<"Macros: "<<macros<<endl;
  cout<<"Function Declarations: "<<func_dec<<endl;
  cout<<"Function Definitions: "<<func_def<<endl;
  cout<<"Variable Declarations: "<<var_dec<<endl;

  //TEST CODE FOR DEBUGGING

  //cout<<str;
  //cout<<typeid(words_regex).name()<<endl;
  // cout << "Found " 
  //           << distance(words_begin, words_end) 
  //           << " words:\n";

  //           int count=0;
  // for (sregex_iterator i = words_begin; i != words_end; ++i) {
  //     smatch match = *i;                                                 
  //     string match_str = match.str(); 
  //     cout <<count<<"  "<< match_str << '\n';
  //     count++;
  // }   
  // cout<<count;

  file.close();
}