#include <stdio.h>
#include <string.h>
int main()
{
    char s[255];
    printf("Nhap xau: ");
    scanf("%[^\n]", s);
    int i;
    for (i=0; i<strlen(s); i++)
    {
        printf("%c", s[i]);
        if ((s[i]==' ')&&(s[i-1]!=' ')) printf("\n");
    }
    printf("\n");
    return 0;
}