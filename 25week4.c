#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct queue_student
{
    char id[10];
    char name[30];
    double cbasic;

    struct queue_student *next;
};

struct queue_student *front;
struct queue_student *rear;
//int rear = 0;

void enqueue(char *id, char *name, char *cbasic)
{
    struct queue_student *link = (struct queue_student*) malloc(sizeof(struct queue_student));

    strcpy(link->id, id);
    strcpy(link->name, name);
    link->cbasic = (double)atof(cbasic);
    link->next = NULL;

    if (front == NULL) 
    {
        front = link; 
        rear = link;
    }
    else 
    {
        rear->next = link;
        rear = link;
    }    
}

struct queue_student* dequeue()
{
    struct queue_student *del;
    if (front == NULL) return NULL;
    del = front;
    front = front->next;
    return del;
}

//Hàm In khác để check việc in ra bằng dequeue
/*void print()
{
    struct queue_student *print = front;

    while(print!= NULL)
    {
        printf("%s,%s,%lf\n", print->id, print->name, print->cbasic);
        print= print->next;
    }
}*/

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
            enqueue(id,name,cbasic);
        } while(getc(f)!=EOF);
    }
    fclose(f);

    //In ra de check 
    do
    {
        struct queue_student *print = (struct queue_student*) malloc(sizeof(struct queue_student));
        print = dequeue();
        if (print == NULL) break;
        printf("\n%s %s %lf", print->id, print->name, print->cbasic);
    } while(1);
    printf("\n");

    return 0;
}