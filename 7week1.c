#include <stdio.h>
#include <string.h>
int main()
{
    char s[255];
    printf("Nhap xau: ");
    scanf("%[^\n]", s);
    int i,one=0;
    for (i=0; i<strlen(s); i++)
    {
        printf("%c", s[i]);
        if ((s[i]==' ')&&(one==0))
        {
            printf("\n");
            one++;
        }
    }
    printf("\n");
    return 0;
}