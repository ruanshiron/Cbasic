#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int num;
    char order[10], name[30];
    double mark;
} student;

int getnumber(FILE *file)
{
    char num[8];
    int n;
    fgets(num,8,file);
    n=atoi(num);
    return n;
}

void getnum(int *num, FILE *file)
{
    char n[4];
    fscanf(file, "%[^,]", n);
    fgetc(file);
    *num = atoi(n);
}

void getorder(char name[], FILE *file)
{
    fscanf(file, "%[^,]", name);
    fgetc(file);
}

void getname(char name[], FILE *file)
{
    fscanf(file, "%[^,]", name);
    fgetc(file);
}

void getmark(double *mark, FILE *file)
{
    char n[4];
    fgets(n, 4, file);
    *mark = atof(n);
}

int main()
{
    FILE *fin, *fout;
    student s[100];
    int n;
    fin = fopen("thisinh.dat", "r");
    if (fin==NULL) perror  ("Error file openning");
        else 
        {
            int i;
            n=getnumber(fin);
            char buff[255];
            for (i=0;i<n; i++)
            {
                getnum(&s[i].num,fin);
                getorder(s[i].order,fin);
                getname(s[i].name,fin);
                getmark(&s[i].mark,fin);

                printf(" %d",s[i].num);
                printf(" %s",s[i].order);
                printf(" %s",s[i].name);
                printf(" %.2f",s[i].mark);
                printf("\n");
            }
        }

    fout = fopen("thisinh2.dat", "w+");
    int i,n2=0;
    for (i=0; i<n; i++)
    {
        if (s[i].mark<5) ;
        else 
        {
            n2++;
        }
    }
    fprintf(fout,"%d",n2);
    fputc('\n',fout);
    for (i=0; i<n; i++)
    {
        if (s[i].mark<5) ;
        else 
        {
            fprintf(fout,"%d,%s,%s,%f",s[i].num,s[i].order,s[i].name,s[i].mark);
            fputc('\n',fout);
        }
    }
    fclose(fout);
    fclose(fin);
}