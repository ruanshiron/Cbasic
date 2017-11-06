/*by Nguyen The Vinh*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node {
    char c;
    struct node *next;
};

struct node *front=NULL;    //Queue
struct node *rear=NULL;

struct node *top=NULL;    //Stack  

int getfromkeyboard(char *str)
{
    printf("Nhap xau: ");
    scanf("%s", str);
    return strlen(str);
}

void push(char c)
{
    struct node *link= (struct node *)malloc(sizeof(struct node));
    link->c = c;
    link->next = top;
    top = link;
}

int instack(char *str)
{
    int i=0;
    while (str[i]!='\0')
    {
        push(str[i]);
        i++;
    }
    return 1;
}

void enqueue(char c)
{
    struct node *link= (struct node *)malloc(sizeof(struct node));
    link->c = c;
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

int inqueue(char *str)
{
    int i=0;
    while (str[i]!='\0')
    {
        enqueue(str[i]);
        i++;
    }
    return 1;
}

char pop()
{
    char c;
    c = top->c;
    top = top ->next;
    return c;
}

char dequeue()
{
    char c;
    c = front->c;
    front = front ->next;
    return c;
}

int compare(int c)
{
    int i;
    for (i=0; i<c; i++)
    {
        if (pop()!=dequeue()) return 0; 
    }
    return 1;
}

int main()
{
    char str[100];
    int c=getfromkeyboard(str);

    instack(str);
    inqueue(str);

    if (compare(c) == 1) printf("Xau dau vao la palindromes.\n");
    else printf("KHONG la palindromes.\n");
    return 0;
}