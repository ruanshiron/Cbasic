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

struct queue_student *front=NULL;
struct queue_student *rear=NULL;
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
    else if (rear!=front)
    {
        del = front;
        front = front->next;
    }
    else 
    {
        del = rear;
        rear=NULL;
        front=NULL;
    }
    return del;
}

// in ra bằng dequeue
void print_to_file()
{
    FILE *f;
    f = fopen("sinhvien2.dat","w+");
    struct queue_student *print ;
    do
    {
        print = dequeue();
        if (print!=NULL)
            fprintf(f,"%s,%s,%lf\n", print->id, print->name, print->cbasic);
        else break;
    } while(front!=NULL);

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
            enqueue(id,name,cbasic);
        } while(getc(f)!=EOF);
    }
    fclose(f);

    //In ra de check 
    

    print_to_file();

    return 0;
}