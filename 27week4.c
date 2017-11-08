/*by Nguyen The Vinh*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct errorStack
{
    char e;
    char reverse;
    int line;
    int num;
    struct errorStack *next;
};

struct errorStack *top=NULL;

int menu()
{
    printf("1. Nhap ten file, show file\n");
    printf("2. Kiem tra cac ky tu Ngoac\n");
    printf("3. Thoat.\n");
    int c;
    scanf("%d",&c);
    return c;
}

int showFile(char *fN)
{
    printf("Nhap ten file: ");
    scanf("%s", fN);
    FILE *f;
    f = fopen(fN, "r+");
    if (f == NULL) 
    {
        perror("KHONG TON TAI FILE");
        return 1;
    }
    char code[500000];
    do
    {
        if (fscanf(f, "%[^\0]\0", code)==EOF) break;
    }
    while (f);
    printf("\n%s\n", code);
    fclose(f);
    return 0;
}

struct errorStack* pop()
{
    struct errorStack *link = top;
    if (top!=NULL) top = top->next;
    link->next = NULL;
    return link;
}

void push(char c, int line, int num)
{
    struct errorStack *link = (struct errorStack *)malloc(sizeof(struct errorStack));
    link->e = c;
    link->line = line;
    link->num = num;

    if (c == '(') link->reverse= ')';
    else if (c == '[') link->reverse= ']';
    else if (c == '{') link->reverse= '}';

    link->next = top;
    top = link;
}

int isEmpty()
{
    if (top == NULL) return 1;
    return 0;
}

int isBracket(char c)
{
    if ((c == '(') || (c == '[') || (c == '{')) return 1;
    if ((c == ']') || (c == '}') || (c == ')')) return -1;
    return 0; 
}

void errorDetail()
{
    struct errorStack *temp=(struct errorStack *)malloc(sizeof(struct errorStack));
    struct errorStack *topT= NULL;
    while (top!=NULL)
    {
        if (isBracket(top->e)==-1)
        {
            temp = pop();
            temp->next = topT;
            topT = temp; 
        }
        else if (isBracket(top->e)==1) 
        {
            if (topT == NULL) 
            {
                printf("Ln %d, Col %d: Loi thieu dau dong ngoac.\n", top->line, top->num);
                pop();
            }
            else 
            {
                printf("Ln %d, Col %d: Ngoac dong khong tuong ung voi ngoac mo.\n", top->line, top->num);
                topT=topT->next;
                pop();
            }    
        }
    }
}

int getError(char *fN)
{
    //Kiểm tra và đưa các dấu ngoặc vào Stack - Có thể đưa đoạn này vào Hàm
    FILE *f;
    f = fopen(fN, "r+");
    if (f == NULL) 
    {
        perror("KHONG TON TAI FILE");
        return 1;
    }

    int line=1, num=0;
    do
    {
        char c = fgetc(f);
        if (c == EOF) break;
        else if (c == '\n') 
        {
            line++;
            num = 0;
        }     
        num++;

        //không thể dùng if (top!=NULL) || (c == top->reverse) vì trong trường hợp top = NULL không có dữ liệu reverse => Dumping trace stacking
        if (top!=NULL) 
        {
            if (c == top->reverse) pop();
        }
        if (isBracket(c)!=0) push(c,line,num);
    } while (f);
    fclose(f);

    //Kiểm tra Stack
    if (isEmpty() == 0) printf("Loi su dung ngoac trong code: \n");
    else printf("KHONG co loi %d.\n", isEmpty());

    //Đánh giá lỗi
    errorDetail();
    return 0;
}

int main()
{
    int c=0;
    char fileName[255];
    while (c!=3)
    {
        c=menu();
        switch (c)
        {
            case 1: showFile(fileName); break;
            case 2: getError(fileName); break;
        }
    }
    return 0;
}