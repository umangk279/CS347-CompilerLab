int f(int y){
	if(y == 0 || y== 1){
		return y;
	}
	return f(y-1)+ f(y-2);
}
int main(){
	int c,i;
	for(i=0;i<6;++i){
		c= c+ 2;
		if(c > 9 ) break;
	}
}