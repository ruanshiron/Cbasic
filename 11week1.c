#include <stdio.h>
int main()
{
    FILE *f1, *f2;
    char s[255],c;
    f1 = fopen("lab1.txt", "r");
    f2 = fopen("lab2.txt", "w");
    
    //fputc(fgetc(f1),f2);
    while((c = fgetc(f1)) != EOF)
    {
        fputc(c,f2);
    }

    fclose(f1);
    fclose(f2);
    return 0;   
}