#include <regex>
#include <iterator>
#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>



using namespace std;


int main(int argc, char* argv[]);
int main(int argc, char* argv[])
{
     int count=0;
    const string s = "Quick \n brown\t\n fox.";
    ifstream f; //taking file as inputstream
    f.open(argv[1]);
    string str;
       if(f) {
          ostringstream ss;
          ss << f.rdbuf(); // reading data
          str = ss.str();
       }
   // cout<<str;
 
    regex macro("(\\s)*#(\\s)*(define)\\s"); 
    regex words_regex("(([a-zA-Z_][a-zA-Z_0-9]*[\\s\\*]*?)\\(([^!@#$+%^;\\{\\}]*?)\\)[\\s]*\\{)");
    regex var_dec("((auto\\s*|const\\s*|unsigned\\s*|extern\\s*|signed\\s*|register\\s*|volatile\\s*|static\\s*|void\\s*|short\\s*|long\\s*|char\\s*|int\\s*|float\\s*|double\\s*|_Bool\\s*|complex\\s*)+)[\\s\\*]*?([a-zA-Z_][a-zA-Z_0-9]*[\\s\\*]*?)\\(([^!@#$+%^;\\{\\}]*?)\\)[\\s]*\\{");
    //regex words_regex("(([a-zA-Z_][a-zA-Z_0-9]*)[\\s\\*]*?)\\(");
    auto words_begin = sregex_iterator(str.begin(), str.end(), macro);
    auto words_end = sregex_iterator();
    cout<<typeid(words_regex).name()<<endl;
    cout << "Found " 
              << distance(words_begin, words_end) 
              << " words:\n";
 
    for (sregex_iterator i = words_begin; i != words_end; ++i) {
        smatch match = *i;                                                 
        string match_str = match.str(); 
        cout << match_str << '\n';
        count++;
    }   
    cout<<count;
}