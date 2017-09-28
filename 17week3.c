#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct student
{
    char id[10];
    char name[30];
    double cbasic;
    struct student *next;
} ;
struct student *head;
struct student *current;

void addst(int i)
{
    char name[30],id[10];
    double  cbasic;
    printf("%d.\n",i+1);
    printf("ID: ");
    scanf("%s", id);
    printf("NAME: ");
    scanf("%*c%[^\n]", name);
    printf("Cbasic: ");
    scanf("%lf", &cbasic);

    struct student *link = (struct student*) malloc(sizeof(struct student));
    link->cbasic = cbasic;
    strcpy(link->name,name);
    strcpy(link->id,id);

    link->next = head;
    head = link;

}

void printst(int n)
{
    struct student *prt = head;

    while(prt != NULL)
    {
        printf("\nID: %s", prt->id);
        printf("\nNAME: %s", prt->name);
        printf("\nCbasic: %lf\n", prt->cbasic);
        prt = prt->next;
    }
}

int main()
{
    int n,i;
    printf("Nhap so sinh vien: ");
    scanf("%d", &n);

    for(i=0;i<n;i++)
    {
        addst(i);
    }

    printst(n);
}