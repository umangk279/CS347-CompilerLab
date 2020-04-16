#include<bits/stdc++.h>
using namespace std;

int main()
{
	FILE* fp = fopen("Employee.csv", "r");
	FILE* fp2 = fopen("Employee2.csv", "r");

	char str[200];
	char str2[200];

	fgets(str,200,fp);
	fgets(str2,200,fp2);
	str[strlen(str)-1]='\0';

	printf("%s,%s",str,str2);

	fclose(fp2);

	while(fgets(str,200,fp)!=NULL)
	{
		str[strlen(str)-1]='\0';
		fp2 = fopen("Employee2.csv", "r");

		fgets(str2,200,fp2);
		while(fgets(str2,200,fp2)!=NULL)
		{
			printf("%s,%s",str,str2);
		}
		fclose(fp2);
	}
	fclose(fp);

	return 0;
}
