#include<bits/stdc++.h>
using namespace std;

int main()
{
	FILE* fp = fopen("Employee.csv", "r");
	char* ptr;


	char str[200];
	while(fgets(str,200,fp)!=NULL)
	{
		char temp[200];
		strcpy(temp,str);
		char* token = strtok(str,",\n");
		printf("%s",token);
		token = strtok(NULL,",\n");
		token = strtok(NULL,",\n");
		printf("\n");
	}
	return 0;
}
