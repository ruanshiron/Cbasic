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
struct student *current;

struct student_clone
{
    char id[10];
    char name[30];
    double cbasic;
} ;

int menu()
{
    int c;
    printf("1. Them 1 sinh vien\n");
    printf("2. Tim Theo MSSV\n");
    printf("3. Xoa Theo MSSV\n");
    printf("4. Xem tat ca\n");
    printf("5. Thoat\n");
    printf("6. Xuat file\n");
    printf("7. Doc file sinhvien.dat va sinh vien co Cbasic>4\n");
    scanf("%d%*c",&c);
    return c;
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

    link->next = head;
    head = link;
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

void putfile()
{
    FILE * file;
    struct student *fout = head;
    file = fopen("sinhvien.dat","w+");
    while (fout != NULL)
    {
        fprintf(file, "%s,%s,%lf", fout->id, fout->name, fout->cbasic);
        fputc('\n',file);
        fout=fout->next;
    }
    fclose(file);
}

void readfile()
{
    FILE * fin;
    struct student_clone sv[100];
    int count=0;
    fin = fopen("sinhvien.dat", "r+");
    printf("start");
    if (fin == NULL) perror("LOI KHONG THAY DU LIEU");
    else {
        do
        {
            char cbasic[10];
            if (fscanf(fin,"%[^,],%[^,],%s",sv[count].id, sv[count].name, cbasic) == EOF) break;
            sv[count].cbasic=(double)atof(cbasic);
            count++;
        } while (fgetc(fin)!= EOF);
        
    }
    fclose(fin);

    int i;
    for (i=0; i<count; i++)
    {
        printf("\nID: %s", sv[i].id);
        printf("\nNAME: %s", sv[i].name);
        printf("\nCbasic: %lf\n", sv[i].cbasic);
    }
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
            case 6: putfile(); break;
            case 7: readfile(); break;
        }
    }
    return 0;
}
