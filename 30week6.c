/*by Nguyen The Vinh*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct student
{
    int id;
    char name[30];
    double cbasic;
};

double getPoint()
{
    double p;
    do {
    scanf("%lf", &p);
    } while ((p<0)||(p>10));
    return p;
}

void getToFile()
{
    struct student temp;
    FILE *f;
    f = fopen("SV.dat", "w+");
    if (f == NULL) perror("LOI MO FILE\n");
    else 
    {
        while (f)
        {
            printf("name: ");
            scanf("%*c%[^\n]", temp.name);
            //printf("%s", temp.name);
            if (strcmp(temp.name, "###")==0) break;
            printf("maSV: ");
            scanf("%d", &temp.id);
            printf("cbasic: ");
            temp.cbasic=getPoint();

            fprintf(f, "%s,%d,%lf\n", temp.name, temp.id, temp.cbasic);
        }
    }   
    fclose(f);
}

void getToArray(struct student *st, int *count)
{
    FILE *f;
    f = fopen("SV.dat", "r+");
    int i=0;
    do
    {
        char cbasic[10];
        char id[10];
        if (fscanf(f, "%[^,],%[^,],%[^\n]", st[i].name, id, cbasic)==EOF) break;
        st[i].id = (int)atoi(id);
        st[i].cbasic = (double)atof(cbasic);
        (*count)++;
        i++;
    } while(fgetc(f)!=EOF);
    fclose(f);
}

void sortAndPrint(struct student *st, int count)
{
    int i,j;
    for (i=0; i<count; i++) 
    {
        for (j=count-1; j>i; j--)
            if(st[j - 1].id > st[j].id) 
            {
                struct student temp = st[j-1];
                st[j-1] = st[j];
                st[j] = temp;
            } 
    }

    for (i=0; i<count; i++)
    {
        printf("%30s | %10d | %10lf\n", st[i].name, st[i].id, st[i].cbasic);
    }
}

struct student BinarySearch(struct student *st, int left, int right, int id)
{ 
    struct student none;
    strcpy(none.name,"###");
    none.id = -1;
    none.cbasic = -1;

 	if (left > right) return none;
 
 	int mid = (left + right) / 2;
 
 	if (id == st[mid].id) 
 		return st[mid];
  	if (id > st[mid].id) 
 		return BinarySearch(st,left,mid-1,id);
 
 	if (id < st[mid].id) 
 		return BinarySearch(st,mid+1,right,id);
 
}

void searchAndPrint(struct student *st, int count)
{
    int id;
    printf("_Tim theo maSV:  ");
    scanf("%d", &id);

    struct student find = BinarySearch(st, 0, count-1, id);

    printf("%30s | %10d | %10lf\n", find.name, find.id, find.cbasic);
}

int menu()
{
    printf("1. Nhap va Luu SV.dat\n");
    printf("2. Doc SV.dat\n");
    printf("3. Sap xep\n");
    printf("4. Tim Kiem (Binary Search)\n");
    printf("5. Thoat.\n");
    char s[10];
    scanf("%s",s);
    int c = atoi(s);
    return c;
}

int main()
{
    int c, count=0;
    struct student st[100];
    do
    {
        c = menu();
        switch (c)
        {
            case 1: getToFile(); break; 
            case 2: getToArray(st, &count); break;
            case 3: sortAndPrint(st, count); break;
            case 4: searchAndPrint(st, count); break;
        }
    }
    while (c!=5);
    return 0;
}