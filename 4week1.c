#include <stdio.h>
#include <string.h>
int symmetry(char *s)
{
    int l, i;
    l=strlen(s)/2;
    for (i=0; i<l; i++)
    {
        if (s[i]!=s[strlen(s)-i-1]) return 0;
    }
    return 1;
}
int main()
{
    char s[50];
    printf("Nhap Xau: ");
    scanf("%s",s);
    if (symmetry(s)==1) printf("Xau da cho doi xung \n");
    else printf("Xau da cho khong doi xung!\n");
    return 0;
}