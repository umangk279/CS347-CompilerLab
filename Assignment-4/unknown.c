#include<stdio.h>
#include <stdlib.h>
#include<string.h>

int main()
{
	FILE* fp = fopen("Employee.csv", "r");
	char* ptr;

	double id;
	char name[50];
	double salary;

	char str[200];
	fgets(str,200,fp);

	printf("%s", str);
	while(fgets(str,200,fp)!=NULL)
	{
		char temp[200];
		strcpy(temp,str);
		char* token = strtok(str,",\n");
		id = strtod(token,&ptr);
		token = strtok(NULL,",\n");
		strcpy(name,token);
		token = strtok(NULL,",\n");
		salary = strtod(token,&ptr);

		if(salary>200)
			printf("%s",temp);
	}	
	return 0;
}