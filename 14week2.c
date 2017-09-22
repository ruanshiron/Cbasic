#include <stdio.h>
#include <string.h>
int main()
{
    FILE *fin, *fout;
    char buf[255];
    fin = fopen("file_1.c", "r+");
    fout = fopen("file_2.c", "w+");
    while (fgets(buf,255,fin)!=NULL)
    {
        fputs(buf,fout);
    }
    fclose(fin);
    fclose(fout);
}