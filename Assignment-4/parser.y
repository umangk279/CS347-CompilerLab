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

void yyerror(char *s){
}
int yywrap()
{ }

%}

%union{ char Char;}

%token <Char> NEW_LINE SELECT PROJECT CARTESIAN_PRODUCT EQUI_JOIN STR NAME NUM AND OR NOT LB RB LT GT LTE GTE EQ NEQ COMMA DOT

%start SMT_LIST

%%
SMT_LIST: SMT NEW_LINE SMT_LIST 
    | SMT 
    | error NEW_LINE {printf ("%d: INVALID SYNTAX\n",i++);} SMT_LIST    
    ;

SMT:    QUERY
        { 
          printf("Query: %s\n",query);
          process_query(query, query_type);
        }
        ;

QUERY:  SELECTION { query_type = selection; printf("%d: VALID SYNTAX\n",i++); printf("Processing SELECT QUERY\n"); }
        | PROJECTION { query_type = projection; printf("%d: VALID SYNTAX\n",i++); printf("Processing PROJECT QUERY\n"); }
        | CART_PRODUCT { query_type = cart_product; printf("%d: VALID SYNTAX\n",i++); printf("Processing CARTESIAN_PRODUCT QUERY\n");  }
        | EQ_JOIN { query_type = eq_join; printf("%d: VALID SYNTAX\n",i++); printf("Processing EQUI_JOIN QUERY\n");  }       
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

ATTRIBUTE_LIST:   ATTRIBUTE | ATTRIBUTE COMMA ATTRIBUTE_LIST
                  ;

ATTRIBUTE:   NAME | NAME DOT NAME
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

EQUI_CONDITION:  EXPRESSION EQ EXPRESSION
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

void get_all_table_attributes(FILE* fp)
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
            token = strtok(NULL,",\n");
        }
    }

    if(fgets(str,500,fp)!=NULL)
    {
        char* token = strtok(str,",\n");
        struct attribute_list* temp = al_front;
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

void process_query(char* query, int query_type)
{
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
            if(query[i]!=' '&&query[i]!='\t')
                condition[k++] = query[i];
            i++;
        }
        condition[k] = '\0';
        printf("Condition: %s\n",condition);

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
        printf("%s",fname);

        FILE* fp = fopen(fname,"r");
        if(fp==NULL) 
        {
            printf("File %s does not exist\n", fname);
            return;
        }

        get_all_table_attributes(fp);

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
    {printf("HERE\n");}


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
        printf("%s\n",fname);

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
        printf("%s\n",fname2);

        FILE* fp = fopen(fname,"r");
        if(fp==NULL)
        {
            printf("%s not found.\n",fname);
            return;
        }
        else
            fclose(fp);

        fp = fopen(fname2,"r");
        if(fp==NULL)
        {
            printf("%s not found.\n",fname2);
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
    {}

}

int main(int argc, char *argv[]){

  query = (char*)malloc(10000*sizeof(char));
    query[0]= '\0';
  yyparse();
  return 0;
}