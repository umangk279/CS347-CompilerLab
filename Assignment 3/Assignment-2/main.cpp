#include<bits/stdc++.h>
#include<iostream>
#include<fstream>
#include<string.h>

using namespace std;

int main(int argc, char* argv[])
{
	
	int source_code_statements = 0;
	int blank_lines=0;
	int macros=0;
	int variables=0;
	int func_dec=0;
	int func_def=0;
	int comments=0;

	string line;
	ifstream file;

	//SOURCE CODE AND BLANK LINE

	file.open(argv[1]);

	while (getline(file, line))
	{
        source_code_statements++;
        if(line=="")
        {
        	blank_lines++;
        	continue;
        }
	}

    cout<<"Source Code Statements: "<<source_code_statements<<endl;
    cout<<"Blank Line: "<<blank_lines<<endl;
    file.close();


    //COMMENT LINE AND COMMENT STRIPING
    file.open(argv[1]); 
	fstream file2;
    file2.open("comment_strip.c",ios::out); 
    enum states { TEXT, 
                SAW_SLASH, 
                SAW_STAR, 
                SINGLE_COMMENT, 
                MULTI_COMMENT } state = TEXT;
    int multi  = 0;
    int single = 0;

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

  	cout<<"Multi: "<<multi<<endl;
  	cout<<"Single: "<<single<<endl;
  	cout<<"Comments: "<<multi+single<<endl;

    file.close();
    file2.close();

    //STRING STRIPING
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

	//MACRO LINES
	// TODO: with regex
    file.open("comment_string_strip.c",ios::out); 
    while (getline(file, line))
    {
        string temp=line.substr(0,8);
        if(temp.compare("#define ")==0)
        	macros++;
    }
    cout<<"Macros: "<<macros<<endl;
    file.close();

    //FUNCTION DEFINITION


    //FUNCTION DECLARATION
    file.open("comment_string_strip.c"); 

    regex re("(([a-zA-Z_][a-zA-Z_0-9]*[\\s\\*]*?){2,}\\(([^!@#$+%^;\\{\\}]*?)\\)[\\s]*;)");
    //regex var_dec("((auto\\s*|const\\s*|unsigned\\s*|extern\\s*|signed\\s*|register\\s*|volatile\\s*|static\\s*|void\\s*|short\\s*|long\\s*|char\\s*|int\\s*|float\\s*|double\\s*|_Bool\\s*|complex\\s*)+)[\\s\\*]*?[a-zA-Z_][a-zA-Z_0-9]*\\s*[;,\\[=](.*?)");
    //regex var_dec("((auto\\s*|const\\s*|unsigned\\s*|extern\\s*|signed\\s*|register\\s*|volatile\\s*|static\\s*|void\\s*|short\\s*|long\\s*|char\\s*|int\\s*|float\\s*|double\\s*|_Bool\\s*|complex\\s*)+)[\\s\\*]*?[a-zA-Z_][a-zA-Z_0-9]*\\s*;");
    regex var_dec("((auto\\s*|const\\s*|unsigned\\s*|extern\\s*|signed\\s*|register\\s*|volatile\\s*|static\\s*|void\\s*|short\\s*|long\\s*|char\\s*|int\\s*|float\\s*|double\\s*|_Bool\\s*|complex\\s*)+)[ \\*]+[\\s\\*]*?[a-zA-Z_][a-zA-Z_0-9]*\\s*[;,\\[=](.*?)");
  
    //regex var_dec("(([a-zA-Z_][a-zA-Z_0-9]*[\\s\\*]*?){2,}[\\s]*;)");
    //regex var_dec("([a-zA-Z0-9_]+)(\\s+)(([a-zA-Z_\\*]?[a-zA-Z0-9_]*(=[a-zA-Z0-9]+)?)[,;]?((\\s*)[a-zA-Z_\\*]?[a-zA-Z0-9_]*?(=[a-zA-Z0-9]+)?[,;])*)");
    while (getline(file, line))
    {
        if (regex_match(line, re))
        	func_dec++;
        //cout<<regex_match(line,re)<<endl<<line<<endl;
        if (regex_match(line, var_dec))
        	variables++;
    }
    cout<<"Function Declaration: "<<func_dec<<endl;
    cout<<"Variable Declaration: "<<variables<<endl;
    file.close();


    return 0;
}
