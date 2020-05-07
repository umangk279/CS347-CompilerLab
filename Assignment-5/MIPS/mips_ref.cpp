#include<bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

vector<string> lines;  //3AC code lines
vector<string> data_items;
vector<string> data_size;
ofstream mipsfile;
ofstream mipsfile1;  //for .data

vector<string> parameter_mips;
class float_count{
public:
  int count;
  float_count(){
    count = 0;
  }
  string get_count(string t){
        string s = "float_const" + to_string(count);
        count++;
        mipsfile1<<s<<": .float "<<t<<endl;
        return s;
  }
};
float_count f_const;

void handle_param(vector<string> linevec)
{
  string param_name=linevec[2];
  parameter_mips.push_back(param_name);
}
void store_stack(){
  for(int i=0;i<data_items.size();i++){
    mipsfile<<"la $t0, "<<data_items[i]<<endl;
    stringstream temp(data_size[i]);
    int size = 0;
    temp >> size;
    for(int j=0;j<size;j= j+4){
      mipsfile<<"l.s $f0, "<<to_string(j)<<"($t0)"<<endl;
      mipsfile<<"s.s $f0, "<<"0($sp)"<<endl;
      mipsfile<<"addiu $sp, $sp, -4"<<endl;
    }
  }
}
void copy_parameter(int no_param){
  for(int i=0;i<no_param;i++){
    if(parameter_mips[i][1] == 'T'){
        mipsfile<<"la $t0, "<<parameter_mips[i]<<endl;
        mipsfile<<"lw $t1, "<<"0($t0)"<<endl;
        mipsfile<<"la $t2, "<<"_Tparam_"<<i<<endl;
        mipsfile<<"sw $t1, "<<"0($t2)"<<endl;
    }
    if(parameter_mips[i][1] == 'F'){
      mipsfile<<"la $t0, "<<parameter_mips[i]<<endl;
      mipsfile<<"l.s $f1, "<<"0($t0)"<<endl;
      mipsfile<<"la $t2, "<<"_Tparam_"<<i<<endl;
      mipsfile<<"s.s $f1, "<<"0($t2)"<<endl;
    }
  }
}

void handle_call(vector<string> linevec)
{
  string func_name=linevec[2];
  string no_params=linevec[3];
  int no_param=0;
  stringstream temp(no_params);
  temp>>no_param;
  if(no_param > parameter_mips.size()){
    cout<<"ERROR in mips"<<endl;
    exit(1);
  }
  store_stack();
  copy_parameter(no_param);
  mipsfile<<"jal "<<func_name<<endl;
  if(no_param +1 == parameter_mips.size()){
    mipsfile<<"la $t0, "<< parameter_mips[no_param]<<endl;
    mipsfile<<"s.s $f11, "<<"0($t0)"<<endl;
  }
  mipsfile<<"lw $ra, "<<"4($sp)"<<endl;
  parameter_mips.clear();
}

void genarate_micro_op_int(string op,string opr1,string opr2,string result){
  int first=0;mipsfile<<"la $t"<<first<<", "<<opr1<<endl;
  int secnd=1;mipsfile<<"la $t"<<secnd<<", "<<opr2<<endl;
  int thrd=2;mipsfile<<"la $t"<<thrd<<", "<<result<<endl;
  int frth=3;mipsfile<<"lw $t"<<frth<<", "<<"0($t"<<first<<")"<<endl;
  int fifth=4;mipsfile<<"lw $t"<<fifth<<", "<<"0($t"<<secnd<<")"<<endl;
  int sixth=5;mipsfile<<op<<" $t"<<sixth<<", "<<"$t"<<frth<<", "<<"$t"<<fifth<<endl;
  mipsfile<<"sw $t"<<sixth<<", 0($t"<<thrd<<")"<<endl;
}
void genarate_micro_op_int_div(string op,string opr1,string opr2,string result){
  int first=0;mipsfile<<"la $t"<<first<<", "<<opr1<<endl;
  int secnd=1;mipsfile<<"la $t"<<secnd<<", "<<opr2<<endl;
  int thrd=2;mipsfile<<"la $t"<<thrd<<", "<<result<<endl;
  int frth=3;mipsfile<<"lw $t"<<frth<<", "<<"0($t"<<first<<")"<<endl;
  int fifth=4;mipsfile<<"lw $t"<<fifth<<", "<<"0($t"<<secnd<<")"<<endl;
  int sixth=5;mipsfile<<op<<" $t"<<frth<<", "<<"$t"<<fifth<<endl;
  mipsfile<<"mflo "<<"$t5 "<<endl;
  mipsfile<<"sw $t"<<sixth<<", 0($t"<<thrd<<")"<<endl;
}
void genarate_micro_op_float(string op,string opr1,string opr2,string result){
  int first=0;mipsfile<<"la $t"<<first<<", "<<opr1<<endl;
  int secnd=1;mipsfile<<"la $t"<<secnd<<", "<<opr2<<endl;
  int thrd=2;mipsfile<<"la $t"<<thrd<<", "<<result<<endl;
  int frth=3;mipsfile<<"l.s $f"<<frth<<", "<<"0($t"<<first<<")"<<endl;
  int fifth=4;mipsfile<<"l.s $f"<<fifth<<", "<<"0($t"<<secnd<<")"<<endl;
  int sixth=5;mipsfile<<op<<" $f"<<sixth<<", "<<"$f"<<frth<<", "<<"$f"<<fifth<<endl;
  mipsfile<<"s.s $f"<<sixth<<", 0($t"<<thrd<<")"<<endl;

}
void genarate_micro_op_float_int(string op,string opr1,string opr2,string result){
  int first=0;mipsfile<<"la $t"<<first<<", "<<opr1<<endl;
  int secnd=1;mipsfile<<"la $t"<<secnd<<", "<<opr2<<endl;
  int thrd=2;mipsfile<<"la $t"<<thrd<<", "<<result<<endl;
  int frth=3;mipsfile<<"l.s $f"<<frth<<", "<<"0($t"<<first<<")"<<endl;
  int fifth=4;mipsfile<<"l.s $f"<<fifth<<", "<<"0($t"<<secnd<<")"<<endl;
  if(opr1[1] == 'T'){
    mipsfile<<"cvt.s.w $f"<<frth<<", "<<"$f"<<frth<<endl;
  }
  if(opr2[1] == 'T'){
    mipsfile<<"cvt.s.w $f"<<fifth<<", "<<"$f"<<fifth<<endl;
  }
  int sixth=5;mipsfile<<op<<" $f"<<sixth<<", "<<"$f"<<frth<<", "<<"$f"<<fifth<<endl;
  mipsfile<<"s.s $f"<<sixth<<", 0($t"<<thrd<<")"<<endl;
}
void handle_num_assignment(vector<string> linevec){
  if(linevec[4][0]!= '_'){
    cout<<"ERROR : problem in intermediate\n";
    exit(0);
  }
  if(linevec[4][1]== 'F'){
    mipsfile<<"la $t0, "<<linevec[4]<<endl;
    string s = f_const.get_count(linevec[2]);
    mipsfile<<"l.s $f0, "<<s<<endl;
    mipsfile<<"s.s $f0, "<<"0($t0)"<<endl;
  }
  if(linevec[4][1] == 'T'){
    mipsfile<<"la $t0, "<<linevec[4]<<endl;
    mipsfile<<"li $t1, "<<linevec[2]<<endl;
    mipsfile<<"sw $t1, "<<"0($t0)"<<endl;
  }
}
void handle_id_first_assignment(vector<string> linevec){
  if(linevec[4][0]!= '_'){
    cout<<"ERROR : problem in intermediate\n";
    exit(0);
  }
  if(linevec[4][1]== 'F'){
    mipsfile<<"la $t0, "<<linevec[2]<<endl;
    mipsfile<<"la $t1, "<<linevec[4]<<endl;
    mipsfile<<"l.s $f0, "<<"0($t0)"<<endl;
    mipsfile<<"s.s $f0, "<<"0($t1)"<<endl;
  }
  if(linevec[4][1]== 'T'){
    mipsfile<<"la $t0, "<<linevec[2]<<endl;
    mipsfile<<"la $t1, "<<linevec[4]<<endl;
    mipsfile<<"lw $t2, "<<"0($t0)"<<endl;
    mipsfile<<"sw $t2, "<<"0($t1)"<<endl;
  }
}
void handle_id_second_assignment(vector<string> linevec){
  if(linevec[2][0]!= '_'){
    cout<<"ERROR : problem in intermediate\n";
    exit(0);
  }
  if(linevec[2][1]== 'F'){
    mipsfile<<"la $t0, "<<linevec[2]<<endl;
    mipsfile<<"la $t1, "<<linevec[4]<<endl;
    mipsfile<<"l.s $f0, "<<"0($t0)"<<endl;
    mipsfile<<"s.s $f0, "<<"0($t1)"<<endl;
  }
  if(linevec[2][1]== 'T'){
    mipsfile<<"la $t0, "<<linevec[2]<<endl;
    mipsfile<<"la $t1, "<<linevec[4]<<endl;
    mipsfile<<"lw $t2, "<<"0($t0)"<<endl;
    mipsfile<<"sw $t2, "<<"0($t1)"<<endl;
  }
}
void handle_temp_to_temp_assignment(vector<string> linevec){
  if(linevec[2][0]!= '_' || linevec[4][0]!= '_' ){
    cout<<"ERROR : problem in intermediate\n";
    exit(0);
  }
  if(linevec[2][1]== 'F' && linevec[4][1]== 'F'){
    mipsfile<<"la $t0, "<<linevec[2]<<endl;
    mipsfile<<"la $t1, "<<linevec[4]<<endl;
    mipsfile<<"l.s $f0, "<<"0($t0)"<<endl;
    mipsfile<<"s.s $f0, "<<"0($t1)"<<endl;
  }

  if(linevec[2][1]== 'T' && linevec[4][1]== 'T'){
    mipsfile<<"la $t0, "<<linevec[2]<<endl;
    mipsfile<<"la $t1, "<<linevec[4]<<endl;
    mipsfile<<"lw $t2, "<<"0($t0)"<<endl;
    mipsfile<<"sw $t2, "<<"0($t1)"<<endl;
  }
  if(linevec[2][1]== 'T' && linevec[4][1] == 'F'){
    mipsfile<<"la $t0, "<<linevec[2]<<endl;
    mipsfile<<"la $t1, "<<linevec[4]<<endl;
    mipsfile<<"lw $t2, "<<"0($t0)"<<endl;
    mipsfile<<"mtc1 $t2, "<<"$f0"<<endl;
    mipsfile<<"cvt.s.w $f0, "<<"$f0"<<endl;
    mipsfile<<"s.s $f0, "<<"0($t1)"<<endl;
  }
  if(linevec[2][1]== 'F' && linevec[4][1]== 'T'){
    mipsfile<<"la $t0, "<<linevec[2]<<endl;
    mipsfile<<"la $t1, "<<linevec[4]<<endl;
    mipsfile<<"l.s $f0, "<<"0($t0)"<<endl;
    mipsfile<<"cvt.w.s $f0, "<<"$f0"<<endl;
    mipsfile<<"s.s $f0, "<<"0($t1)"<<endl;
  }
}

void handle_assignment(vector<string> linevec){

  if(linevec.size()<=4) return;
  if(linevec[1].empty() || linevec[2].empty() || linevec[3].empty() || linevec[4].empty()){
      return;
  }
  if(isdigit(linevec[2][0])){
    handle_num_assignment(linevec);
  }
  else
  {
    if(linevec[2][0]!='_')
    {
      handle_id_first_assignment(linevec);
    }
    else
    {
      if(linevec[4][0]!='_')
      {
        handle_id_second_assignment(linevec);
      }
      else
      {
        handle_temp_to_temp_assignment(linevec);
      }
    }
  }
}
void handle_rel_op_float(string op,string opr1,string opr2,string result){
  if(op == "==" || op == "!="){
    mipsfile<<"c.eq.s "<<opr1<<", "<<opr2<<endl;
    if(op == "=="){
      mipsfile<<"bc1t "<<result<<endl;
    }
    if(op == "!="){
      mipsfile<<"bc1f "<<result<<endl;
    }
  }
  if(op == ">" || op == "<"){
    if(op == ">"){
      mipsfile<<"c.lt.s "<<opr2<<", "<<opr1<<endl;
      mipsfile<<"bc1t "<<result<<endl;
    }
    if(op == "<" ){
      mipsfile<<"c.lt.s "<<opr1<<", "<<opr2<<endl;
      mipsfile<<"bc1t "<<result<<endl;

    }
  }
  if(op == ">=" || op == "<="){
    if(op == ">="){
      mipsfile<<"c.le.s "<<opr2<<", "<<opr1<<endl;
      mipsfile<<"bc1t "<<result<<endl;
    }
    if(op == "<=" ){
      mipsfile<<"c.le.s "<<opr1<<", "<<opr2<<endl;
      mipsfile<<"bc1t "<<result<<endl;
    }
  }
}
void handle_rel_op_int(string op,string opr1,string opr2,string result){
    if(op == "=="){
      mipsfile<<"beq "<<opr1<<", "<<opr2<<", "<<result<<endl;
    }
   if(op == "!="){
     mipsfile<<"bne "<<opr1<<", "<<opr2<<", "<<result<<endl;
   }
   if(op == "<="){
     mipsfile<<"ble "<<opr1<<", "<<opr2<<", "<<result<<endl;
   }
   if(op == ">="){
     mipsfile<<"bge "<<opr1<<", "<<opr2<<", "<<result<<endl;
   }
   if(op == "<"){
     mipsfile<<"blt "<<opr1<<", "<<opr2<<", "<<result<<endl;
   }
   if(op == ">"){
     mipsfile<<"bgt "<<opr1<<", "<<opr2<<", "<<result<<endl;
   }
}

void handle_rel_op(vector<string> linevec){
  if(linevec[4].empty()){
    cout<<"problem in intermediate\n"<< endl;
    exit(1);
  }
  if(linevec[4][linevec[4].size()-1] != ':'){
    cout<<"problem in intermediate\n"<< endl;
    exit(0);
  }
  else{
    linevec[4][linevec[4].size()-1] = ' ';
  }
  if(linevec[2][1]== 'F' && linevec[3][1]== 'F'){
    mipsfile<<"la $t0, "<<linevec[2]<<endl;
    mipsfile<<"la $t1, "<<linevec[3]<<endl;
    mipsfile<<"l.s $f0, "<<"0($t0)"<<endl;
    mipsfile<<"l.s $f1, "<<"0($t1)"<<endl;
    handle_rel_op_float(linevec[1],"$f0","$f1",linevec[4]);
  }
  if(linevec[2][1]== 'T' && linevec[3][1]== 'T'){
    mipsfile<<"la $t0, "<<linevec[2]<<endl;
    mipsfile<<"la $t1, "<<linevec[3]<<endl;
    mipsfile<<"lw $t2, "<<"0($t0)"<<endl;
    mipsfile<<"lw $t3, "<<"0($t1)"<<endl;
    handle_rel_op_int(linevec[1],"$t2","$t3",linevec[4]);
  }
  if(linevec[2][1]== 'T' && linevec[3][1]== 'F'){
    mipsfile<<"la $t0, "<<linevec[2]<<endl;
    mipsfile<<"la $t1, "<<linevec[3]<<endl;
    mipsfile<<"l.s $f0, "<<"0($t0)"<<endl;
    mipsfile<<"cvt.s.w $f0, "<<"$f0"<<endl;
    mipsfile<<"l.s $f1, "<<"0($t1)"<<endl;
    handle_rel_op_float(linevec[1],"$f0","$f1",linevec[4]);
  }
  if(linevec[2][1]== 'F' && linevec[3][1]== 'T'){
    mipsfile<<"la $t0, "<<linevec[2]<<endl;
    mipsfile<<"la $t1, "<<linevec[3]<<endl;
    mipsfile<<"l.s $f0, "<<"0($t0)"<<endl;
    mipsfile<<"l.s $f1, "<<"0($t1)"<<endl;
    mipsfile<<"cvt.s.w $f1, "<<"$f1"<<endl;
    handle_rel_op_float(linevec[1],"$f0","$f1",linevec[4]);
  }
}

vector<std::string> split(string line){
  // string tok;
  // stringstream ss(line);
  vector<std::string> linevec;
  // // while(getline(ss, tok,' ')) {
  // //     linevec.push_back(tok);
  // // }
  istringstream ss(line);
    do {
        string word;
        ss >> word;
        linevec.push_back(word);
    } while (ss);
  return linevec;
}

void readfile(string filename){
  std::ifstream fin;
  std::string line;
  fin.open(filename.c_str());
  while(fin.good()){
    getline(fin,line);
    if(line != ""){
      lines.push_back(line);
    }
  }
  fin.close();
}

void generate_data_segment(){  //in mipsfile1 --output1.mips
    mipsfile1<<".data"<< endl;
    for(int i=0;i< data_items.size();i++){
        mipsfile1<< data_items[i] <<":"<< " .space " <<data_size[i]<<endl; // needs attention fora array declaration
    }
     mipsfile1<<"newline:"<<" .asciiz "<<"\""<<"\\"<<"n"<<"\""<<endl;
}
int tokenise_data_segment(){
  for(int i=0;i<lines.size();i++){
    vector<string> tokens = split(lines[i]);
    if(tokens.empty()){
      continue;
    }
    if(tokens[0] != "#" && tokens[0] != "##" ) return i;
    if(tokens[0] == "##" ) continue;
    if(tokens.size() < 3) continue;
    else{
      data_items.push_back(tokens[1]);
      data_size.push_back(tokens[2]);
    }
  }
  return lines.size();
}
bool check_array(string s){
    bool x =false;
    for(int i=0;i<s.size();i++){
      if(s[i]=='[') x=true;
    }
    return x;
}
void extract_op_array(string input,string &address,string &offset){
    string temp;
    for(int i=0;i<input.size();i++){
        if(input[i] == '['){
          address = temp;
          temp.clear();
          continue;
        }
        if(input[i] == ']') break;
        temp = temp + input[i];
    }
    offset = temp;
}
void handle_array_assignment(vector<string> linevec)
{
  if(linevec[1].empty() || linevec[2].empty() || linevec[3].empty()){
      return;
  }
  if(linevec[1] != "="){
    cout<<"problem in intermediate code\n";
    exit(1);
  }
  bool first = check_array(linevec[2]);
  bool second = check_array(linevec[3]);
  if(first && second){
    cout<<"problem in intermediate code\n";
    exit(1);
  }
  if(first){
     string address,offset;
     extract_op_array(linevec[2],address,offset);
     if(address.empty() || offset.empty()) return;
     mipsfile<<"la $t0, "<<address<<endl;
     mipsfile<<"lw $t1, "<<"0($t0)"<<endl;
     mipsfile<<"la $t2, "<<offset<<endl;
     mipsfile<<"lw $t3, "<<"0($t2)"<<endl;
     mipsfile<<"add $t3, $t3, $t3"<<endl;
     mipsfile<<"add $t3, $t3, $t3"<<endl;
     mipsfile<<"add $t4, $t1, $t3"<<endl;
     mipsfile<<"l.s $f0, "<<"0($t4)"<<endl;
     mipsfile<<"la $t5, "<<linevec[3]<<endl;
     mipsfile<<"s.s $f0, "<<"0($t5)"<<endl;
      return;
  }
  if(second){
      string address,offset;
      extract_op_array(linevec[3],address,offset);
      if(address.empty() || offset.empty()) return;
      mipsfile<<"la $t0, "<<address<<endl;
      mipsfile<<"lw $t1, "<<"0($t0)"<<endl;
      mipsfile<<"la $t2, "<<offset<<endl;
      mipsfile<<"lw $t3, "<<"0($t2)"<<endl;
      mipsfile<<"add $t3, $t3, $t3"<<endl;
      mipsfile<<"add $t3, $t3, $t3"<<endl;
      mipsfile<<"add $t4, $t1, $t3"<<endl;
      mipsfile<<"la $t5, "<<linevec[2]<<endl;
      mipsfile<<"l.s $f0, "<<"0($t5)"<<endl;
      mipsfile<<"s.s $f0, "<<"0($t4)"<<endl;
      return;
  }
    cout<<"problem in intermediate code\n";
    exit(1);
}

void handle_bool_op(string op,string opr1,string opr2,string result){
  mipsfile<<"la $t0, "<<opr1<<endl;
  mipsfile<<"la $t1, "<<opr2<<endl;
  mipsfile<<"la $t2, "<<result<<endl;
  mipsfile<<"lw $t3, "<<"0($t0)"<<endl;
  mipsfile<<"lw $t4, "<<"0($t1)"<<endl;
  if(op == "AND"){
    mipsfile<<"and $t5, $t3, $t4"<<endl;
  }
  if(op == "OR"){
      mipsfile<<"or $t5, $t3, $t4"<<endl;
  }

  mipsfile<<"sw $t5, "<<"0($t2)"<<endl;
}
void handle_digit_multiply(vector<string> linevec){
  if(isdigit(linevec[2][0]) && isdigit(linevec[3][0])){
    cout<<"problem in intermediate\n";
    exit(1);
  }
  if(isdigit(linevec[2][0])){
    mipsfile<<"la $t0, "<<linevec[3]<<endl;
    mipsfile<<"li $t1, "<<linevec[2]<<endl;
    mipsfile<<"lw $t2, "<<"0($t0)"<<endl;
    mipsfile<<"mul $t3, $t1, $t2"<<endl;
    mipsfile<<"la $t4, "<<linevec[4]<<endl;
    mipsfile<<"sw $t3, "<<"0($t4)"<<endl;
  }
  if(isdigit(linevec[3][0])){
    mipsfile<<"la $t0, "<<linevec[2]<<endl;
    mipsfile<<"li $t1, "<<linevec[3]<<endl;
    mipsfile<<"lw $t2, "<<"0($t0)"<<endl;
    mipsfile<<"mul $t3, $t1, $t2"<<endl;
    mipsfile<<"la $t4, "<<linevec[4]<<endl;
    mipsfile<<"sw $t3, "<<"0($t4)"<<endl;
  }
}
void restore_stack(){
    for(int i=data_items.size()-1;i>=0;i--){
      mipsfile<<"la $t0, "<<data_items[i]<<endl;
      stringstream temp(data_size[i]);
      int size = 0;
      temp >> size;
      for(int j=size-4;j>=0;j= j-4){
        mipsfile<<"addiu $sp, $sp, 4"<<endl;
        mipsfile<<"l.s $f0, "<<"0($sp)"<<endl;
        mipsfile<<"s.s $f0, "<<to_string(j)<<"($t0)"<<endl;
      }
    }
}
void handle_func_begin(vector<string> linevec){
  mipsfile<<"move $fp, $sp"<<endl;
  mipsfile<<"sw $ra, 0($sp)"<<endl;
  mipsfile<<"addiu $sp, $sp, -4"<<endl;
}
void handle_func_end(vector<string> linevec){
  if(linevec[3] == "main") return;
  mipsfile<<"lw $ra, 0($fp)"<<endl;
  mipsfile<<"addiu $sp, $sp, 4"<<endl;
  restore_stack();
  mipsfile<<"addiu $fp, $sp, 4"<<endl;
  mipsfile<<"jr $ra"<<endl;
}

void generate_each_instruction(vector<string> linevec)
{
  //mipsfile << text << endl;
  if (linevec[0] == "5") cout << linevec[1] << endl << linevec[2];
  if(linevec.size() == 3)
  {            // change if the tokeniser become correct
    if(linevec[1].empty()) 
    {
    	//cout << "y" << endl;
    	return;
    }
    if(linevec[1][linevec[1].size()-1] == ':')
    {
      if(linevec[1] == "main:")
      {
          mipsfile<< ".globl main"<< endl;
      }
      mipsfile<< linevec[1] << endl;
      return;
    }
  }
  if(linevec.size() == 5)
  {
     //cout << linevec[0] << endl;
     handle_array_assignment(linevec);
     return;
  }
  if(linevec.size()<=4) return;
  if(linevec[1].empty() || linevec[2].empty() || linevec[3].empty() || linevec[4].empty())
  {
      return;
  }

  if(linevec[1]=="+")
  {
    if(linevec[2][1]=='T'&&linevec[3][1]=='T'&&linevec[4][1]=='T')
    {
      genarate_micro_op_int("add",linevec[2],linevec[3],linevec[4]);
    }
    else if(linevec[2][1]=='F'&&linevec[3][1]=='F'&&linevec[4][1]=='F')
    {
      genarate_micro_op_float("add.s",linevec[2],linevec[3],linevec[4]);
    }
    else{
      genarate_micro_op_float_int("add.s",linevec[2],linevec[3],linevec[4]);
    }
  }
  if(linevec[1]=="-")
  {
    if(linevec[2][1]=='T'&&linevec[3][1]=='T'&&linevec[4][1]=='T')
    {
      genarate_micro_op_int("sub",linevec[2],linevec[3],linevec[4]);
    }
    else if(linevec[2][1]=='F'&&linevec[3][1]=='F'&&linevec[4][1]=='F')
    {
      genarate_micro_op_float("sub.s",linevec[2],linevec[3],linevec[4]);
    }
    else{
      genarate_micro_op_float_int("sub.s",linevec[2],linevec[3],linevec[4]);
    }
  }
  if(linevec[1]=="*")
  {
    if(linevec[2][1]=='T'&&linevec[3][1]=='T'&&linevec[4][1]=='T')
    {
      genarate_micro_op_int("mul",linevec[2],linevec[3],linevec[4]);
    }
    else if(linevec[2][1]=='F'&&linevec[3][1]=='F'&&linevec[4][1]=='F')
    {
      genarate_micro_op_float("mul.s",linevec[2],linevec[3],linevec[4]);
    }
    else{
      if(isdigit(linevec[2][0]) || isdigit(linevec[3][0]) ){
        handle_digit_multiply(linevec);
      }
      else{
        genarate_micro_op_float_int("mul.s",linevec[2],linevec[3],linevec[4]);
      }
    }
  }
  if(linevec[1]=="/")
  {
    if(linevec[2][1]=='T'&&linevec[3][1]=='T'&&linevec[4][1]=='T')
    {
        genarate_micro_op_int_div("div",linevec[2],linevec[3],linevec[4]);
    }
    else if(linevec[2][1]=='F'&&linevec[3][1]=='F'&&linevec[4][1]=='F')
    {
      genarate_micro_op_float("div.s",linevec[2],linevec[3],linevec[4]);
    }
    else{
      genarate_micro_op_float_int("div.s",linevec[2],linevec[3],linevec[4]);
    }
  }
  if(linevec[1] == "="){
      handle_assignment(linevec);

  }
  if(linevec[1] == "==" || linevec[1] == "!=" || linevec[1] == "<=" || linevec[1] == ">=" || linevec[1] == "<" || linevec[1] == ">"){
      handle_rel_op(linevec);
  }
  if(linevec[1]== "addr"){
    bool add_flag = true;
    if(linevec[2].size() >=3 ){
      if(linevec[2][2] == 'p'){
        add_flag = false;
      }
    }
    if(add_flag == true){
      mipsfile<<"la $t0, "<<linevec[2]<<endl;
      mipsfile <<"la $t1, "<<linevec[4]<<endl;
      mipsfile <<"sw $t0, "<<"0($t1)"<<endl;
    }
    else{
      mipsfile<<"la $t0, "<<linevec[2]<<endl;
      mipsfile <<"la $t1, "<<linevec[4]<<endl;
      mipsfile <<"lw $t2, "<<"0($t0)"<<endl;
      mipsfile<<"sw $t2, "<<"0($t1)"<<endl;
    }
  }
  if(linevec[1] == "NOT"){
    if(linevec[2][1]!= 'T' || linevec[4][1]!= 'T' ){
      cout<<"problem in intermediate\n";
      exit(1);
    }
    mipsfile<<"la $t0, "<<linevec[2]<<endl;
    mipsfile<<"la $t3, "<<linevec[4]<<endl;
    mipsfile<<"lw $t1, "<<"0($t0)"<<endl;
    mipsfile<<"xori $t2, $t1, 1"<<endl;
    mipsfile<<"sw $t2, "<<"0($t3)"<<endl;
  }
  if(linevec[1] == "AND" || linevec[1] == "OR"){
    if(linevec[2][1]!= 'T' || linevec[3][1]!= 'T' || linevec[4][1]!= 'T'){
      cout<<"problem in intermediate\n";
      exit(1);
    }
      handle_bool_op(linevec[1],linevec[2],linevec[3],linevec[4]);
  }
  if(linevec[1] == "goto"){
    if(linevec[4].empty()){
      cout<<"problem in intermediate\n"<< endl;
      exit(1);
    }
    if(linevec[4][linevec[4].size()-1] != ':'){
      cout<<"problem in intermediate\n"<< endl;
      exit(0);
    }
    else{
      linevec[4][linevec[4].size()-1] = ' ';
    }
    mipsfile<<"j "<<linevec[4]<<endl;
  }
  if(linevec[1] == "UMINUS"){
    if(linevec[2][1] == 'F'){
      mipsfile<<"la $t0, "<<linevec[2]<<endl;
      mipsfile<<"l.s $f1, "<<"0($t0)"<<endl;
      mipsfile<<"l.s $f2, "<<"0($t0)"<<endl;
      mipsfile<<"add.s $f2, $f2, $f2"<<endl;
      mipsfile<<"sub.s $f1, $f1, $f2"<<endl;
      mipsfile<<"la $t3, "<<linevec[4]<<endl;
      mipsfile<<"s.s $f1, "<<"0($t3)"<<endl;
    }
    if(linevec[2][1] == 'T'){
        mipsfile<<"la $t0, "<<linevec[2]<<endl;
        mipsfile<<"lw $t1, "<<"0($t0)"<<endl;
        mipsfile<<"lw $t2, "<<"0($t0)"<<endl;
        mipsfile<<"add $t2, $t2, $t2"<<endl;
        mipsfile<<"sub $t1, $t1, $t2"<<endl;
        mipsfile<<"la $t3, "<<linevec[4]<<endl;
        mipsfile<<"sw $t1, "<<"0($t3)"<<endl;
    }
  }
  if(linevec[1] == "func"){
    if(linevec[2]== "begin"){
      handle_func_begin(linevec);
    }
    if(linevec[2]=="end"){
      if(linevec[3] != "main"){
        handle_func_end(linevec);
      }
    }
  }
  if(linevec[1] == "param" || linevec[1] == "refparam"){
    handle_param(linevec);
  }
  if(linevec[1]== "call"){
    handle_call(linevec);
  }
  if(linevec[1] == "return"){
    if(linevec[2][0] == '_'){
        mipsfile<<"la $t0, "<< linevec[2]<<endl;
        mipsfile<<"l.s $f11, "<<"0($t0)"<<endl;
    }
    handle_func_end(linevec);
  }
  if(linevec[1] == "print"){
    if(linevec[2][1] == 'T'){
      mipsfile<<"lw $a0, "<<linevec[2]<<endl;
      mipsfile<<"li $v0, 1"<<endl;
      mipsfile<<"syscall"<<endl;
      mipsfile<<"li $v0, 4"<<endl;
      mipsfile<<"la $a0 newline"<<endl;
      mipsfile<<"syscall"<<endl;
    }
    if(linevec[2][1] == 'F'){
      mipsfile<<"l.s $f12, "<<linevec[2]<<endl;
      mipsfile<<"li $v0, 2"<<endl;
      mipsfile<<"syscall"<<endl;
      mipsfile<<"li $v0, 4"<<endl;
      mipsfile<<"la $a0 newline"<<endl;
      mipsfile<<"syscall"<<endl;
    }
  }

}

void generate()
{
  int index = tokenise_data_segment();
  //cout << index << endl << endl;
  generate_data_segment();
  fstream file;
  int line;
  mipsfile<<".text"<<endl;
  mipsfile<<"j main"<<endl;
  for(line = index; line < lines.size(); line++){
    vector<string> linevec = split(lines[line]);  //split
    mipsfile << linevec[0] << endl;
    generate_each_instruction(linevec);
    mipsfile << endl;
  }

}

int main(int argc, char** argv)
{
  if(argc < 2){
    cout<<"give intermediate file name \n";
    exit(1);
  }
  readfile(argv[1]);  //input 3AC file
  mipsfile.open ("output1_ref.mips", ios::out | ios::trunc);
  mipsfile1.open ("output_ref.mips", ios::out | ios::trunc);
  generate();
  mipsfile.close();
  mipsfile1.close();
  std::ifstream ifile("output1_ref.mips");
  std::ofstream ofile("output_ref.mips", std::ios::app);
  if (!ifile.is_open()) {
    cout<< "could not open file \n";
    exit(1);
  }
  else if (!ofile.is_open()) {
    cout<< "could not open file \n";
    exit(1);
  }
  else {
    ofile << ifile.rdbuf();
  }
  ifile.close();
  ofile.close();
  return 0;
}