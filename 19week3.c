/*by Nguyen The Vinh*/

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
//struct student *current;

int menu()
{
    int c;
    printf("1. Them 1 sinh vien (Tu dong sap xep)\n");
    printf("2. Tim Theo MSSV\n");
    printf("3. Xoa Theo MSSV\n");
    printf("4. Xem tat ca\n");
    printf("5. Thoat\n");
    scanf("%d%*c",&c);
    return c;
}

struct student* insertwhere(double cbasic)
{
    struct student *insert=head;
    struct student *aft_insert=head->next;
    if (insert->next==NULL)
    {
        return insert;
    }
    else if ((insert->cbasic<cbasic) && (aft_insert->cbasic>cbasic))
    {
        return insert;
    }
    aft_insert = aft_insert->next;
    insert = insert->next;
}

void insert()
{
    char name[30];
    char id[10];
    double cbasic;
    printf("\n");
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
    if (head==NULL) 
    {
        link->next = head;
        head=link;
    }
    else if (head->cbasic>link->cbasic) 
    {
        link->next=head;
        head=link;
    }
    else 
    {
        link->next=insertwhere(cbasic)->next;     
        insertwhere(cbasic)->next=link;
    }
    /*link->next = ?;
    head = link;*/
}

void printall()
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

int find()
{
    char id[10];
    printf("\nMSSV can tim: ");
    scanf("%s", id);
    struct student *fid = head;
    while(fid != NULL)
    {
        if (strcmp(fid->id,id)==0) 
        {
            printf("\nResult: \n");
            printf("\nID: %s", fid->id);
            printf("\nNAME: %s", fid->name);
            printf("\nCbasic: %lf\n\n", fid->cbasic);
            return 1;
        }
        fid = fid->next;
    }
    printf("\nKhong tim thay ket qua.\n");
    return 0;
}

int delete()
{
    struct student *del = head;
    struct student *prv = NULL;

    char id[10];
    printf("\nMSSV can xoa: ");
    scanf("%s", id);
    if (head == NULL) return 0;
    while (del!=NULL)
    {
        if (strcmp(del->id, id)==0) break;
        prv = del;
        del = del->next;  
    }
    if (del==NULL) printf("\nKhong co ket qua,\n");
    else if (del->next==NULL) prv->next=NULL;
    else if (del == head) head = head->next;
    else prv->next = del->next;
}

int main()
{       
    int c;
    while (c!=5)
    {
        c=menu();
        switch (c)
        {
            case 1: insert(); break;
            case 2: find(); break;
            case 3: delete(); break;
            case 4: printall(); break;
        }
    }
    return 0;
}