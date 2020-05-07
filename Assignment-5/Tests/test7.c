int factorial(int n){
  if(n == 1 || n == 0){
    return 1;
  }
    int t;
    t = factorial(n-1)*n;
  return t;


}


int main(){
  int r;
  r = factorial(5);


}
