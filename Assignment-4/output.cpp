#include<bits/stdc++.h>
using namespace std;

int main()
{
	FILE* fp = fopen("Employee.csv", "r");
	char* ptr;

	double id;
	char name2[50];
	string name;
	double salary;

	char str[200];
	fgets(str,200,fp);

	printf("%s",str);
	while(fgets(str,200,fp)!=NULL)
	{
		char temp[200];
		strcpy(temp,str);
		char* token = strtok(str,",\n");
		id = strtod(token,&ptr);
		token = strtok(NULL,",\n");
		strcpy(name2,token);
		name = name2;
		token = strtok(NULL,",\n");
		salary = strtod(token,&ptr);
		if(id==1)
			printf("%s",temp);
	}
	return 0;
}
