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

struct stack_student *head=NULL;

void add_top(char *id, char *name, char *cbasic)
{
    struct stack_student *link = (struct stack_student *)malloc(sizeof(struct stack_student));

    strcpy(link->id, id);
    strcpy(link->name, name);
    link->cbasic = (double)atof(cbasic);

    link->next = head;
    head = link;
}

struct stack_student* delete_first()
{

   //luu tham chieu toi first link
   struct stack_student *tempLink = head;
	
   //danh dau next toi first link la first 
   if (head!=NULL) head = head->next;
	
   //tra ve link bi xoa
   return tempLink;
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

void print_stack_to_file()
{
    FILE *f;
    f = fopen("sinhvien2.dat","w+");
    while (1)
    {
        struct stack_student *delete = delete_first();
        if (delete!=NULL)
            fprintf(f,"%s,%s,%lf\n", delete->id, delete->name, delete->cbasic);
        else break;
    }
    fclose(f);
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

    print_stack_to_file();

    return 0;
}