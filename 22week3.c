/*by Nguyen The Vinh*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 8


struct stack_student
{
    char id[10];
    char name[30];
    double cbasic;
};

struct stack_student stack[MAX];
static int top=-1; 

void print_stack()
{
    int i=0;
    while (i!=top)
    {
        printf("%s,%s,%lf\n", stack[i].id, stack[i].name, stack[i].cbasic);
        i++;
    }
}

int main()
{
    FILE *f;
    f = fopen("sinhvien.dat", "r+");
    do 
    {
        char cbasic[10];
        top++;
        if (fscanf(f, "%[^,],%[^,],%s", stack[top].id, stack[top].name, cbasic) == EOF) break;
        stack[top].cbasic = (double)atof(cbasic);
    } while(getc(f)!=EOF);
    fclose(f);
    print_stack();
    return 0;
}