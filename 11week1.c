#include <stdio.h>
int main()
{
    int x, a[100], n, i;
    printf("X= ");
    scanf("%d", &x);
    printf("So phan tu trong mang: ");
    scanf("%d", &n);
    printf("A: ");
    for (i=0; i<n; i++)
    {
        scanf("%d", &a[i]);
    }

    int *p1, *p2, *plim;
    for (p1 = p2 = a, plim= a+n; p1<plim; p1++)
    {
        if (*p1 != x) *p2++= *p1;
        n=p2-a;
    }
    
    for (i=0; i<n; i++)
    {
        printf("%d ", a[i]);
    }

    

    
}