/*by Nguyen The Vinh*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack_student
{
    char id[10];
    char name[30];
    double cbasic;
    struct stack_student *next;
};

struct stack_student *head;

void add_top(char *id, char *name, char *cbasic)
{
    struct stack_student *link = (struct stack_student *)malloc(sizeof(struct stack_student));

    strcpy(link->id, id);
    strcpy(link->name, name);
    link->cbasic = (double)atof(cbasic);

    link->next = head;
    head = link;
}

void print_stack()
{
    struct stack_student *print = head;

    while(print!= NULL)
    {
        printf("%s,%s,%lf\n", print->id, print->name, print->cbasic);
        print= print->next;
    }
}

int main()
{
    FILE *f;
    f = fopen("sinhvien.dat", "r+");
    if (f==NULL) perror("Khong doc duoc FILE");
    else 
    {
        char id[10], name[30], cbasic[10];

        do 
        {
            if (fscanf(f, "%[^,],%[^,],%s", id, name, cbasic) == EOF) break;
            add_top(id,name,cbasic);
        } while(getc(f)!=EOF);
    }
    fclose(f);

    print_stack();

    return 0;
}