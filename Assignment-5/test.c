int a;
float b;
a = 2;
b = 1.2;

void sum(int c,int b){
  int a;
  a = 10;
}


 int  difference(int a,int b){
   return a-b;
 }

 void arr2(){
    int f[3];
    f[0] = 1;
    f[1] = 2;
    f[2] = 3;
    int r;
    r = f[0]*f[1]*f[2];
}

int f(int y){
  if(y == 0 || y== 1){
    return y;
  }
  return f(y-1)+ f(y-2);
}

int main(){

  int e;
  e = 3;
  e = ++a;
  float c;
  c = a+b;
  c = a/b;
  int d;
  d = a-b;
  d = a*b;
  

  int i;
  i = 4;

  for(i = 0;i<5;i=i+1){
  b = b+5;
  }

  while(i > 3) {
    a = a + 1;
    --i;
  }
 
  switch(i){
      case 3:{
        break;
      }
      case 4:{
        break;
      }
      case 5:{
        break;
      }
 
  }

if (i < 3) {
  i=4;
  }
  else { 
     i=2;
   }

int r;
r = difference(5,3);
int s;
s = difference(3,5);

}