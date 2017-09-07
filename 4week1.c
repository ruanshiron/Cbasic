#include <stdio.h>
void same(int a[], int b[], int n, int m)
{
    int i, j, c[100] = {0}, d=0;
    for (i=0; i<n; i++)
    {
        for (j=0; j<m; j++)
        {
            if (a[i]==b[j])
            { 
                c[i]++;
                d++;
                i++;
            }
            
        }
    }
    printf("So phan tu chung: %d\n", d);
    printf("Danh sach cac phan tu: ");
    for (i=0; i<n; i++)
    {
        if (c[i]>0) printf("%d, ", a[i]);
    }
    printf("\n");
}

void bubblesort(int a[], int n)
{
    int i,j, temp;
    for (i=n; i>0; i--)
    {
        for (j=1; j<i; j++)
        {
            if (a[j]<a[j-1])
            {
                temp = a[j];
                a[j] = a[j-1];
                a[j-1] = temp;
            }
        }
    }

}
void show(int a[], int n)
{
    int i;
    for (i=0; i<n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}
void sort(int a[], int b[], int n, int m)
{
    printf("Sau khi sap xep:\n");
    bubblesort(a,n);
    bubblesort(b,m);
    printf("A: ");
    show(a,n);
    printf("B: ");
    show(b,m);

}

void group(int c[] ,int a[], int b[], int n, int m)
{
    int i,l;
    l=m+n;
    for (i=0; i<l; i++)
    {
        if (i<n) c[i]=a[i];
        else c[i]=b[i-n];
    }
    bubblesort(c,l);
    show(c,l);
}

int main()
{
    int m,n,a[100],b[100],i;
    printf("n= ");
    scanf("%d", &n);
    printf("m= ");
    scanf("%d", &m);

    printf("Mang A co n phan tu:   \n");
    for (i=0; i<n; i++)
    {
        printf("A[%d]= ", i+1);
        scanf("%d", &a[i]);
    }

    printf("Mang B co m phan tu:   \n");
    for (i=0; i<m; i++)
    {
        printf("B[%d]= ", i+1);
        scanf("%d", &b[i]);
    }

    same(a,b,n,m);

    sort(a,b,n,m);

    int c[200];
    group(c,a,b,n,m);


}