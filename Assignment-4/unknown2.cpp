#include<bits/stdc++.h>
using namespace std;

class _Employee {
public :
	double id;
	char name2[50];
	string name;
	double salary;
};
class _Employee2 {
public :
	double id;
	char name2[50];
	string name;
	double salary;
};
int main()
{
	FILE* fp = fopen("Employee.csv", "r");
	FILE* fp2 = fopen("Employee2.csv", "r");

	char* ptr;

	_Employee Employee;
	_Employee2 Employee2;

	cout<<"Here\n";
	char str[200];
	char str2[200];

	char temp[200];
	char temp2[200];

	fgets(str,200,fp);
	fgets(str2,200,fp2);
	str[strlen(str)-1]='\0';

	cout<<"Here\n";
	printf("%s,%s",str,str2);

	fclose(fp2);

	while(fgets(str,200,fp)!=NULL)
	{
		strcpy(temp,str);
		temp[strlen(temp)-1]='\0';

		char* token = strtok(str,",\n");
		Employee.id = strtod(token,&ptr);

		token = strtok(NULL,",\n");
		strcpy(Employee.name2,token);
		Employee.name = Employee.name2;

		token = strtok(NULL,",\n");
		Employee.salary = strtod(token,&ptr);

		fp2 = fopen("Employee2.csv", "r");

		fgets(str2,200,fp2);
		while(fgets(str2,200,fp2)!=NULL)
		{
			strcpy(temp2,str2);
			char* token = strtok(str2,",\n");
			Employee2.id = strtod(token,&ptr);

			token = strtok(NULL,",\n");
			strcpy(Employee2.name2,token);
			Employee2.name = Employee2.name2;
			
			token = strtok(NULL,",\n");
			Employee2.salary = strtod(token,&ptr);
			if(Employee.id==Employee2.id)
				printf("%s,%s",temp,temp2);
		}
		fclose(fp2);
	}
	fclose(fp);

	return 0;
}
