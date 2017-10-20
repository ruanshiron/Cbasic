/*by Nguyen The Vinh*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 6

struct queue_student
{
    char id[10];
    char name[30];
    double cbasic;
};

struct queue_student student[MAX];
int top = 0;
int rear = -1;
int count = 0;


int empty_queue()
{
    if (count==0) return 1;
    else return 0; 
}

int full_queue()
{
    if (count==MAX) return 1;
    else return 0;
}

void add_student(char *id, char *name, double cbasic)
{
    if (full_queue()==0)
    {
        if (rear+1==MAX) rear=-1;
        ++rear;
        strcpy(student[rear].id, id);
        strcpy(student[rear].name, name);
        student[rear].cbasic = cbasic;

        //rintf("%s, %s, %lf\n", student[rear].id, student[rear].name, student[rear].cbasic);
        count++;
    }
}

struct queue_student remove_student()
{
    struct queue_student current_top;
    if (empty_queue()!=1)
    {
        current_top = student[top++];
        if (top == MAX) top = 0;
        count--;
    }
    return current_top;
}

int main()
{
    FILE *f;
    f = fopen("sinhvien.dat", "r+");
    if (f == NULL) perror("Khong the mo FILE");
    else 
    {
        do 
        {
            char id[10], name[30], cbasic[10];
            if (fscanf(f, "%[^,],%[^,],%s", id, name, cbasic) == EOF) break;
            add_student(id, name, (double)atof(cbasic));
        } while(getc(f)!=EOF);
    }
    fclose(f);
    
    while(count!=0)
    {
        struct queue_student print = remove_student();
        printf("%s, %s, %lf\n", print.id, print.name, print.cbasic);
    }
    return 0;
}