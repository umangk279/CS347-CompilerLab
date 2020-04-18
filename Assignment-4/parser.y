%{
#include <stdio.h>
#include <string.h>

#define selection 1
#define projection 2
#define cart_product 3
#define eq_join 4
#define numeric 5
#define isString 6

extern FILE *yyin;
#define YYSTYPE char*
extern int yylex();
extern int yyparse();
int i=1;

int query_type;
char* query;

struct attributes_in_query
{
    char* att_name;
    struct attributes_in_query* next;
};

struct attribute_list
{
    char* att_name;
    int att_type;
    struct attribute_list* next;
    int in_query;
};

extern struct attributes_in_query* aiq_front;
extern struct attributes_in_query* aiq_end;

struct attribute_list* al_front = NULL;
struct attribute_list* al_end = NULL;

struct attribute_list* al2_front = NULL;
struct attribute_list* al2_end = NULL;

void yyerror(char *s){
}
int yywrap()
{ }

%}

%union{ char Char;}

%token <Char> NEW_LINE SELECT PROJECT CARTESIAN_PRODUCT EQUI_JOIN STR NAME NUM AND OR NOT LB RB LT GT LTE GTE EQ NEQ COMMA DOT

%start SMT

%%

SMT:    QUERY
        { 
          process_query(query, query_type);
          return 0;
        }
        | error {remove("output.cpp"); remove("output");printf ("INVALID SYNTAX\n"); return 0;}
        ;

QUERY:  SELECTION { query_type = selection; printf("VALID SYNTAX\n"); printf("Processing SELECT QUERY\n"); }
        | PROJECTION { query_type = projection; printf("VALID SYNTAX\n"); printf("Processing PROJECT QUERY\n"); }
        | CART_PRODUCT { query_type = cart_product; printf("VALID SYNTAX\n"); printf("Processing CARTESIAN_PRODUCT QUERY\n");  }
        | EQ_JOIN { query_type = eq_join; printf("VALID SYNTAX\n"); printf("Processing EQUI_JOIN QUERY\n");  }       
        |
        ;

SELECTION:    SELECT LT CONDITIONS GT LB TABLE_NAME RB
              ;

PROJECTION:   PROJECT LT ATTRIBUTE_LIST GT LB TABLE_NAME RB
              ;

CART_PRODUCT:     LB TABLE_NAME RB CARTESIAN_PRODUCT LB TABLE_NAME RB
                  ;

EQ_JOIN:    LB TABLE_NAME RB EQUI_JOIN LT EQUI_CONDITIONS GT LB TABLE_NAME RB
            ;

CONDITIONS: CONDITION2 OR CONDITIONS
            | CONDITION2
            ;

CONDITION2: CONDITION AND CONDITION2
            | CONDITION
            ;

CONDITION:  EXPRESSION OPR EXPRESSION
            | LB CONDITIONS RB
            | NOT LB CONDITIONS RB
            ;

OPR:    LT | GT | LTE | GTE | NEQ | EQ
        ;

EXPRESSION:    ATTRIBUTE_LIST | DATA
               ;

EQUI_EXPRESSION:    EQUI_ATTRIBUTE_LIST
               ;

ATTRIBUTE_LIST:   ATTRIBUTE | ATTRIBUTE COMMA ATTRIBUTE_LIST
                  ;

EQUI_ATTRIBUTE_LIST:   EQUI_ATTRIBUTE | EQUI_ATTRIBUTE COMMA EQUI_ATTRIBUTE_LIST
                  ;

ATTRIBUTE:   NAME | NAME DOT NAME
             ;

EQUI_ATTRIBUTE:   NAME DOT NAME
             ;

DATA:   NUM | STR
        ;

TABLE_NAME:    NAME
               ;

EQUI_CONDITIONS: EQUI_CONDITION2 OR EQUI_CONDITIONS
            | EQUI_CONDITION2
            ;

EQUI_CONDITION2: EQUI_CONDITION AND EQUI_CONDITION2
            | EQUI_CONDITION
            ;

EQUI_CONDITION:  EQUI_EXPRESSION EQ EQUI_EXPRESSION
            | LB EQUI_CONDITIONS RB
            ;
%%

int check_numeric(char* token)
{
    int len = strlen(token);
    for(int i=0; i<len; i++)
    {
        if(!(isdigit(token[i]) || token[i]=='-' || token[i]=='.')) return 0;
    }
    return 1;
}

void get_all_table_attributes(FILE* fp, int i)
{
    char str[500];
    if(fgets(str,500,fp)!=NULL)
    {
        char* token = strtok(str,",\n");
        while(token!=NULL)
        {
            struct attribute_list* temp = (struct attribute_list*) malloc(sizeof(struct attribute_list));
            temp->att_name = (char*)malloc(50*sizeof(char));
            strcpy(temp->att_name, token);
            temp->att_type = numeric;
            temp->in_query = 0;
            temp->next = NULL;
            if (i == 0)
            {
                if(al_front == NULL && al_end == NULL)
                {
                    al_front = temp;
                    al_end = temp;
                }
                else
                {
                    al_end->next = temp;
                    al_end = temp;
                }
            }
            else
            {
                if(al2_front == NULL && al2_end == NULL)
                {
                    al2_front = temp;
                    al2_end = temp;
                }
                else
                {
                    al2_end->next = temp;
                    al2_end = temp;
                }
            }
            token = strtok(NULL,",\n");
        }
    }

    if(fgets(str,500,fp)!=NULL)
    {
        char* token = strtok(str,",\n");
        struct attribute_list* temp;
        if (i == 0) temp = al_front;
        else temp = al2_front;
        while(token!=NULL)
        {
            if(!check_numeric(token))
                temp->att_type = isString;

            temp = temp->next;
            token = strtok(NULL,",\n");
        }
    }
    return;
}

int validate_attributes(char* fname)
{
    fname[strlen(fname)-4]='\0';
    struct attributes_in_query* temp = aiq_front;
    while(temp!=NULL)
    {
        if(strcmp(temp->att_name,fname)==0)
        {
            temp = temp->next;
            continue;
        }
        struct attribute_list* t = al_front;
        while(t!=NULL)
        {
            if(strcmp(t->att_name,temp->att_name)==0)
            {
                t->in_query = 1;
                break;
            }
            t = t->next;
        }
        if(t==NULL)
            return 0;
        temp=temp->next;
    }
    return 1;
}

int validate_attributes2(char* fname, char* fname2)
{
    fname[strlen(fname)-4]='\0';
    fname2[strlen(fname2)-4]='\0';
    struct attributes_in_query* temp = aiq_front;

    while(temp!=NULL)
    {
        if(strcmp(temp->att_name,fname)==0 || strcmp(temp->att_name,fname2)==0)
        {
            temp = temp->next;
            continue;
        }
        //printf("%s\n",temp->att_name);
        struct attribute_list* t = al_front;

        while(t!=NULL)
        {
            if(strcmp(t->att_name,temp->att_name)==0)
            {
                t->in_query = 1;
                break;
            }
            t = t->next;
        }
        if(t==NULL)
        {
            struct attribute_list* t2 = al2_front;
            while(t2!=NULL)
            {
                if(strcmp(t2->att_name,temp->att_name)==0)
                {
                    t2->in_query = 1;
                    break;
                }
                t2 = t2->next;
            }
            if(t2==NULL)
                return 0;
        }
        temp=temp->next;
    }
    return 1;
}

void process_query(char* query, int query_type)
{
    remove("output.cpp");
    remove("output");
    if(query_type==selection)
    {
        int i =0;
        int len = strlen(query);
        int j=len-1;
        while(query[i]!='<')
            i++;
        while(query[j]!='>')
            j--;
        char* condition = (char*)malloc(500*sizeof(char));
        int k=0;
        i++;
        while(i<j)
        {
            if(query[i]!=' ' && query[i]!='\t')
                condition[k++] = query[i];
            i++;
        }
        condition[k] = '\0';

        while(query[i]!='(' && i<len)
            i++;
        i++;
        
        k=0;
        char* fname = (char*)malloc(500*sizeof(char));
        while(i<len && query[i]!=')')
        {
            if(query[i]!=' '&&query[i]!='\t')
                fname[k++] = query[i];
            i++;
        }
        fname[k]='\0';
        strcat(fname,".csv");

        FILE* fp = fopen(fname,"r");
        if(fp==NULL) 
        {
            printf("File %s does not exist\n", fname);
            return;
        }

        get_all_table_attributes(fp,0);

        if(validate_attributes(fname)==0)
        {
            printf("Attributes in the input query are not correct.\n");
            return;
        }

        else
        {
            FILE* fp2 = fopen("output.cpp","w");
            fprintf(fp2, "#include<bits/stdc++.h>\nusing namespace std;\n\n");
            fprintf(fp2,"int main()\n{\n");
            fprintf(fp2,"\tFILE* fp = fopen(\"%s.csv\", \"r\");\n",fname);
            fprintf(fp2,"\tchar* ptr;\n\n");

            struct attribute_list* temp = al_front;
            while(temp!=NULL)
            {
                if(temp->att_type == numeric)
                    fprintf(fp2,"\tdouble %s;\n",temp->att_name);
                else if(temp->att_type == isString)
                {
                    fprintf(fp2,"\tchar %s2[50];\n",temp->att_name);
                    fprintf(fp2,"\tstring %s;\n",temp->att_name);
                }
                temp = temp->next;
            }
            fprintf(fp2,"\n\tchar str[200];\n");
            fprintf(fp2,"\tfgets(str,200,fp);\n\n");
            fputs("\tprintf(\"\%s\",str);\n",fp2);
            fprintf(fp2,"\twhile(fgets(str,200,fp)!=NULL)\n\t{\n");
            fprintf(fp2,"\t\tchar temp[200];\n");
            fprintf(fp2,"\t\tstrcpy(temp,str);\n");

            temp = al_front;
            int i=0;
            while(temp!=NULL)
            {
                if(i==0)
                {
                    fprintf(fp2,"\t\tchar* token = strtok(str,\",\\n\");\n");
                    i++;
                }
                else
                    fprintf(fp2,"\t\ttoken = strtok(NULL,\",\\n\");\n");
                if(temp->att_type == numeric)
                {
                    fprintf(fp2,"\t\t%s = strtod(token,&ptr);\n",temp->att_name);
                }
                else
                {
                    fprintf(fp2,"\t\tstrcpy(%s2,token);\n",temp->att_name);
                    fprintf(fp2,"\t\t%s = %s2;\n",temp->att_name, temp->att_name);
                }
                temp=temp->next;
            }
            fprintf(fp2,"\t\tif(%s)\n",condition);
            fputs("\t\t\tprintf(\"\%s\",temp);\n\t}\n",fp2);
            fprintf(fp2,"\treturn 0;\n}\n");
            fclose(fp2);
        }

        fclose(fp);
    }

    else if(query_type==projection)
    {
        int i =0;
        int len = strlen(query);

        while(query[i]!='(' && i<len)
            i++;
        i++;
        
        int k=0;
        char* fname = (char*)malloc(500*sizeof(char));
        while(i<len && query[i]!=')')
        {
            if(query[i]!=' '&&query[i]!='\t')
                fname[k++] = query[i];
            i++;
        }
        fname[k]='\0';
        strcat(fname,".csv");

        FILE* fp = fopen(fname,"r");
        if(fp==NULL) 
        {
            printf("File %s does not exist\n", fname);
            return;
        }

        get_all_table_attributes(fp,0);

        if(validate_attributes(fname)==0)
        {
            printf("Attributes in the input query are not correct.\n");
            return;
        }

        else
        {
            FILE* fp2 = fopen("output.cpp","w");
            fprintf(fp2, "#include<bits/stdc++.h>\nusing namespace std;\n\n");
            fprintf(fp2,"int main()\n{\n");
            fprintf(fp2,"\tFILE* fp = fopen(\"%s.csv\", \"r\");\n",fname);
            fprintf(fp2,"\tchar* ptr;\n\n");

            struct attribute_list* temp = al_front;
            
            fprintf(fp2,"\n\tchar str[200];\n");
            fprintf(fp2,"\twhile(fgets(str,200,fp)!=NULL)\n\t{\n");
            fprintf(fp2,"\t\tchar temp[200];\n");
            fprintf(fp2,"\t\tstrcpy(temp,str);\n");

            temp = al_front;
            int i=0;
            while(temp!=NULL)
            {
                if (temp->in_query == 1)
                {
                    if(i==0)
                    {
                        fprintf(fp2,"\t\tchar* token = strtok(str,\",\\n\");\n");
                        fputs("\t\tprintf(\"\%s\",token);\n",fp2);
                        i++;
                    }
                    else
                    {
                        fprintf(fp2,"\t\ttoken = strtok(NULL,\",\\n\");\n");
                        fputs("\t\tprintf(\",\%s\",token);\n",fp2);
                    }
                }
                else
                {
                    if(i==0)
                    {
                        fprintf(fp2,"\t\tchar* token = strtok(str,\",\\n\");\n");
                        i++;
                    }
                    else
                    {
                        fprintf(fp2,"\t\ttoken = strtok(NULL,\",\\n\");\n");
                    }
                }
                temp=temp->next;
            }
            fputs("\t\tprintf(\"\\n\");\n\t}\n",fp2);
            fprintf(fp2,"\treturn 0;\n}\n");
            fclose(fp2);
        }

        fclose(fp);
    }


    else if(query_type==cart_product)
    {
        int i=0;
        int len = strlen(query);

        while(query[i]!='(')
            i++;
        i++;
        int k=0;
        char* fname = (char*)malloc(500*sizeof(char));
        while(i<len && query[i]!=')')
        {
            if(query[i]!=' '&&query[i]!='\t')
                fname[k++] = query[i];
            i++;
        }
        fname[k]='\0';
        strcat(fname,".csv");

        k=len-1;
        while(query[i]!='(')
            i++;
        i++;
        k=0;
        char* fname2 = (char*)malloc(500*sizeof(char));
        while(i<len && query[i]!=')')
        {
            if(query[i]!=' '&&query[i]!='\t')
                fname2[k++] = query[i];
            i++;
        }
        fname2[k]='\0';
        strcat(fname2,".csv");

        FILE* fp = fopen(fname,"r");
        if(fp==NULL)
        {
            printf("File %s does not exist.\n",fname);
            return;
        }
        else
            fclose(fp);

        fp = fopen(fname2,"r");
        if(fp==NULL)
        {
            printf("File %s does not exist.\n",fname2);
            return;
        }
        else
            fclose(fp);

        fp = fopen("output.cpp","w");
        fprintf(fp, "#include<bits/stdc++.h>\nusing namespace std;\n\n");
        fprintf(fp,"int main()\n{\n");
        fprintf(fp,"\tFILE* fp = fopen(\"%s\", \"r\");\n",fname);
        fprintf(fp,"\tFILE* fp2 = fopen(\"%s\", \"r\");\n\n",fname2);
        fprintf(fp,"\tchar str[200];\n");
        fprintf(fp,"\tchar str2[200];\n\n");
        fprintf(fp,"\tfgets(str,200,fp);\n");
        fprintf(fp,"\tfgets(str2,200,fp2);\n");
        fprintf(fp,"\tstr[strlen(str)-1]=\'\\0\';\n\n");
        fputs("\tprintf(\"\%s,\%s\",str,str2);\n\n",fp);
        fprintf(fp,"\tfclose(fp2);\n\n");
        fprintf(fp,"\twhile(fgets(str,200,fp)!=NULL)\n\t{\n");
        fprintf(fp,"\t\tstr[strlen(str)-1]=\'\\0\';\n");
        fprintf(fp,"\t\tfp2 = fopen(\"%s\", \"r\");\n\n",fname2);
        fprintf(fp,"\t\tfgets(str2,200,fp2);\n");
        fprintf(fp,"\t\twhile(fgets(str2,200,fp2)!=NULL)\n\t\t{\n");
        fputs("\t\t\tprintf(\"\%s,\%s\",str,str2);\n\t\t}\n",fp);
        fprintf(fp,"\t\tfclose(fp2);\n\t}\n");
        fprintf(fp,"\tfclose(fp);\n\n");
        fprintf(fp,"\treturn 0;\n}\n");

        fclose(fp);

    }
    else if(query_type==eq_join)
    {
        int i =0;
        int len = strlen(query);
        int j=len-1;
        while(query[i]!='<')
            i++;
        while(query[j]!='>')
            j--;
        char* condition = (char*)malloc(500*sizeof(char));
        int k=0;
        i++;
        while(i<j)
        {
            if(query[i]!=' ' && query[i]!='\t')
                condition[k++] = query[i];
            i++;
        }
        condition[k] = '\0';
        printf("Condition: %s\n",condition); //1

        i=0;
        while(query[i]!='(')
            i++;
        i++;
        k=0;
        char* fname = (char*)malloc(500*sizeof(char));
        while(i<len && query[i]!=')')
        {
            if(query[i]!=' '&&query[i]!='\t')
                fname[k++] = query[i];
            i++;
        }
        fname[k]='\0';
        strcat(fname,".csv");

        while(query[i]!='(')
            i++;
        i++;
        k=0;
        char* fname2 = (char*)malloc(500*sizeof(char));
        while(i<len && query[i]!=')')
        {
            if(query[i]!=' '&&query[i]!='\t')
                fname2[k++] = query[i];
            i++;
        }
        fname2[k]='\0';
        strcat(fname2,".csv");

        FILE* fp = fopen(fname,"r");
        if(fp==NULL) 
        {
            printf("File %s does not exist\n", fname);
            return;
        }

        get_all_table_attributes(fp,0);

        FILE* fp2 = fopen(fname2,"r");
        if(fp2==NULL) 
        {
            printf("File %s does not exist\n", fname2);
            return;
        }

        get_all_table_attributes(fp2,1);

        if(validate_attributes2(fname, fname2)==0)
        {
            printf("Attributes in the input query are not correct.\n");
            return;
        }

        else
        {
            if(strcmp(fname,fname2)==0)
            {
                fp = fopen("output.cpp","w");
                fprintf(fp, "#include<bits/stdc++.h>\nusing namespace std;\n\n");
                fprintf(fp,"class _%s {\n",fname);
                fprintf(fp,"public :\n");
                struct attribute_list* temp = al_front;
                while(temp!=NULL)
                {
                    if(temp->att_type == numeric)
                        fprintf(fp,"\tdouble %s;\n",temp->att_name);
                    else if(temp->att_type == isString)
                    {
                        fprintf(fp,"\tchar %s2[50];\n",temp->att_name);
                        fprintf(fp,"\tstring %s;\n",temp->att_name);
                    }
                    temp = temp->next;
                }
                fprintf(fp,"};\n\n");

                fprintf(fp,"int main()\n{\n");
                fprintf(fp,"\tFILE* fp = fopen(\"%s.csv\", \"r\");\n",fname);
                fprintf(fp,"\tFILE* fp2 = fopen(\"%s.csv\", \"r\");\n\n",fname2);
                fprintf(fp,"\tchar* ptr;\n\n");

                fprintf(fp,"\t_%s %s;\n",fname,fname);
                fprintf(fp,"\t_%s %s2;\n\n",fname,fname);

                fprintf(fp,"\tchar str[200];\n");
                fprintf(fp,"\tchar str2[200];\n\n");
                fprintf(fp,"\tchar temp[200];\n");
                fprintf(fp,"\tchar temp2[200];\n\n");
                fprintf(fp,"\tfgets(str,200,fp);\n");
                fprintf(fp,"\tfgets(str2,200,fp2);\n");
                fprintf(fp,"\tstr[strlen(str)-1]=\'\\0\';\n\n");
                fputs("\tprintf(\"\%s,\%s\",str,str2);\n\n",fp);
                fprintf(fp,"\tfclose(fp2);\n\n");

                fprintf(fp,"\twhile(fgets(str,200,fp)!=NULL)\n\t{\n");
                fprintf(fp,"\t\tstrcpy(temp,str);\n");
                fprintf(fp,"\t\ttemp[strlen(temp)-1]=\'\\0\';\n\n");

                temp = al_front;
                int i=0;
                while(temp!=NULL)
                {
                    if(i==0)
                    {
                        fprintf(fp,"\t\tchar* token = strtok(str,\",\\n\");\n");
                        i++;
                    }
                    else
                        fprintf(fp,"\t\ttoken = strtok(NULL,\",\\n\");\n");
                    if(temp->att_type == numeric)
                    {
                        fprintf(fp,"\t\t%s.%s = strtod(token,&ptr);\n\n",fname,temp->att_name);
                    }
                    else
                    {
                        fprintf(fp,"\t\tstrcpy(%s.%s2,token);\n",fname,temp->att_name);
                        fprintf(fp,"\t\t%s.%s = %s.%s2;\n\n",fname,temp->att_name,fname,temp->att_name);
                    }
                    temp=temp->next;
                }

                fprintf(fp,"\t\tfp2 = fopen(\"%s.csv\", \"r\");\n\n",fname2);
                fprintf(fp,"\t\tfgets(str2,200,fp2);\n");
                fprintf(fp,"\t\twhile(fgets(str2,200,fp2)!=NULL)\n\t\t{\n");
                fprintf(fp,"\t\t\tstrcpy(temp2,str2);\n");

                temp = al2_front;
                i=0;
                while(temp!=NULL)
                {
                    if(i==0)
                    {
                        fprintf(fp,"\t\t\tchar* token = strtok(str2,\",\\n\");\n");
                        i++;
                    }
                    else
                        fprintf(fp,"\t\t\ttoken = strtok(NULL,\",\\n\");\n");
                    if(temp->att_type == numeric)
                    {
                        fprintf(fp,"\t\t\t%s2.%s = strtod(token,&ptr);\n\n",fname2,temp->att_name);
                    }
                    else
                    {
                        fprintf(fp,"\t\t\tstrcpy(%s2.%s2,token);\n",fname2,temp->att_name);
                        fprintf(fp,"\t\t\t%s2.%s = %s2.%s2;\n\n",fname2,temp->att_name,fname2,temp->att_name);
                    }
                    temp=temp->next;
                }

                char* condition_changed = (char*) malloc(200*sizeof(char));
                int k = 0;
                int lhs = 1;
                for(i=0; i<=strlen(condition)-strlen(fname); i++)
                {
                    int found = 1;
                    for(int j=0; j<strlen(fname); j++)
                    {
                        if(condition[i+j]!=fname[j])
                        {
                            found = 0;
                            break;
                        }
                    }
                    if(found==0)
                        condition_changed[k++] = condition[i];
                    else
                    {
                        for(int x=i; x<i+strlen(fname); x++)
                        {
                            condition_changed[k++] = condition[x];
                        }
                        if(lhs==0)
                        {
                            condition_changed[k++] = '2';
                            lhs=1;
                        }
                        else lhs=0;
                        i=i+strlen(fname)-1;
                    }
                }
                while(i<strlen(condition))
                    condition_changed[k++] = condition[i++];
                condition_changed[k]='\0';
                fprintf(fp,"\t\t\t//Changed condition: %s\n", condition_changed);
                fprintf(fp,"\t\t\tif(%s)\n",condition_changed);
                fputs("\t\t\t\tprintf(\"\%s,\%s\",temp,temp2);\n\t\t}\n",fp);
                fprintf(fp,"\t\tfclose(fp2);\n\t}\n");
                fprintf(fp,"\tfclose(fp);\n\n");
                fprintf(fp,"\treturn 0;\n}\n");

                fclose(fp);
            }

            else
            {

                fp = fopen("output.cpp","w");
                fprintf(fp, "#include<bits/stdc++.h>\nusing namespace std;\n\n");

                fprintf(fp,"class _%s {\n",fname);
                fprintf(fp,"public :\n");
                struct attribute_list* temp = al_front;
                while(temp!=NULL)
                {
                    if(temp->att_type == numeric)
                        fprintf(fp,"\tdouble %s;\n",temp->att_name);
                    else if(temp->att_type == isString)
                    {
                        fprintf(fp,"\tchar %s2[50];\n",temp->att_name);
                        fprintf(fp,"\tstring %s;\n",temp->att_name);
                    }
                    temp = temp->next;
                }
                fprintf(fp,"};\n");

                fprintf(fp,"class _%s {\n",fname2);
                fprintf(fp,"public :\n");
                temp = al2_front;
                while(temp!=NULL)
                {
                    if(temp->att_type == numeric)
                        fprintf(fp,"\tdouble %s;\n",temp->att_name);
                    else if(temp->att_type == isString)
                    {
                        fprintf(fp,"\tchar %s2[50];\n",temp->att_name);
                        fprintf(fp,"\tstring %s;\n",temp->att_name);
                    }
                    temp = temp->next;
                }
                fprintf(fp,"};\n");

                fprintf(fp,"int main()\n{\n");
                fprintf(fp,"\tFILE* fp = fopen(\"%s.csv\", \"r\");\n",fname);
                fprintf(fp,"\tFILE* fp2 = fopen(\"%s.csv\", \"r\");\n\n",fname2);
                fprintf(fp,"\tchar* ptr;\n\n");

                fprintf(fp,"\t_%s %s;\n",fname,fname);
                fprintf(fp,"\t_%s %s;\n",fname2,fname2);

                fprintf(fp,"\tchar str[200];\n");
                fprintf(fp,"\tchar str2[200];\n\n");
                fprintf(fp,"\tchar temp[200];\n");
                fprintf(fp,"\tchar temp2[200];\n\n");
                fprintf(fp,"\tfgets(str,200,fp);\n");
                fprintf(fp,"\tfgets(str2,200,fp2);\n");
                fprintf(fp,"\tstr[strlen(str)-1]=\'\\0\';\n\n");
                fputs("\tprintf(\"\%s,\%s\",str,str2);\n\n",fp);
                fprintf(fp,"\tfclose(fp2);\n\n");
                fprintf(fp,"\twhile(fgets(str,200,fp)!=NULL)\n\t{\n");
                fprintf(fp,"\t\tstrcpy(temp,str);\n");
                fprintf(fp,"\t\ttemp[strlen(temp)-1]=\'\\0\';\n");

                temp = al_front;
                int i=0;
                while(temp!=NULL)
                {
                    if(i==0)
                    {
                        fprintf(fp,"\t\tchar* token = strtok(str,\",\\n\");\n");
                        i++;
                    }
                    else
                        fprintf(fp,"\t\ttoken = strtok(NULL,\",\\n\");\n");
                    if(temp->att_type == numeric)
                    {
                        fprintf(fp,"\t\t%s.%s = strtod(token,&ptr);\n",fname,temp->att_name);
                    }
                    else
                    {
                        fprintf(fp,"\t\tstrcpy(%s.%s2,token);\n",fname,temp->att_name);
                        fprintf(fp,"\t\t%s.%s = %s.%s2;\n",fname,temp->att_name,fname,temp->att_name);
                    }
                    temp=temp->next;
                }

                fprintf(fp,"\t\tfp2 = fopen(\"%s.csv\", \"r\");\n\n",fname2);
                fprintf(fp,"\t\tfgets(str2,200,fp2);\n");
                fprintf(fp,"\t\twhile(fgets(str2,200,fp2)!=NULL)\n\t\t{\n");
                fprintf(fp,"\t\t\tstrcpy(temp2,str2);\n");

                temp = al2_front;
                i=0;
                while(temp!=NULL)
                {
                    if(i==0)
                    {
                        fprintf(fp,"\t\t\tchar* token = strtok(str2,\",\\n\");\n");
                        i++;
                    }
                    else
                        fprintf(fp,"\t\t\ttoken = strtok(NULL,\",\\n\");\n");
                    if(temp->att_type == numeric)
                    {
                        fprintf(fp,"\t\t\t%s.%s = strtod(token,&ptr);\n",fname2,temp->att_name);
                    }
                    else
                    {
                        fprintf(fp,"\t\t\tstrcpy(%s.%s2,token);\n",fname2,temp->att_name);
                        fprintf(fp,"\t\t\t%s.%s = %s.%s2;\n",fname2,temp->att_name,fname2,temp->att_name);
                    }
                    temp=temp->next;
                }

                fprintf(fp,"\t\t\tif(%s)\n",condition);
                fputs("\t\t\t\tprintf(\"\%s,\%s\",temp,temp2);\n\t\t}\n",fp);
                fprintf(fp,"\t\tfclose(fp2);\n\t}\n");
                fprintf(fp,"\tfclose(fp);\n\n");
                fprintf(fp,"\treturn 0;\n}\n");
                fclose(fp);
            }
            
        }

    }

}

int main(int argc, char *argv[]){

  query = (char*)malloc(10000*sizeof(char));
    query[0]= '\0';
  yyparse();
  return 0;
}

