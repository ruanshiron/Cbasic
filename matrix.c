#include <stdio.h>
#include <stdlib.h>

void mat_print(int *C,int m,int n)
{
    int i,j;
    printf("C =");
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++) printf("%3d",C[i*n+j]);
        printf("\n   ");
    }
    printf("\n");
}

void mat_sum()
{
    int i,j,m,n,*A,*B,*C;
    printf("Please enter the number of rows: ");
    scanf("%d",&m);
    printf("Please enter the number of columns: ");
    scanf("%d",&n);
    A= (int *) malloc(m*n*sizeof(int));
    B= (int *) malloc(m*n*sizeof(int));
    C= (int *) malloc(m*n*sizeof(int));
    printf("Please enter the elements of matrix A:\n");
    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
        {
            printf("A[%d][%d] = ",i+1,j+1);
            scanf("%d",&A[i*n+j]);
        }
    printf("Please enter the elements of matrix B:\n");
    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
        {
            printf("B[%d][%d] = ",i+1,j+1);
            scanf("%d",&B[i*n+j]);
        }

    for(i=0;i<m;i++)
        for(j=0;j<m;j++) C[i*n+j] = A[i*n+j] + B[i*n+j];
    mat_print(C,m,n);
}

void mat_mul()
{
    int m,n,p,i,j,a,b,*A,*B,*C;
    printf("Please enter the number of rows of matrix A: ");
    scanf("%d",&m);
    printf("Please enter the number of columns of matrix A: ");
    scanf("%d",&n);
    printf("Please enter the number of columns of matrix B: ");
    scanf("%d",&p);
    
    for(i=0;i<p;i++)
        for(j=0;j<m;j++)
        {
            int tong,x,y;
            tong=0;x=0;y=0;
            for(int k=0;k<n;k++)
            {
                tong=A[x*n+j]*B[i*p+y];
                x++;
                y++;
                C[i*p+j];
            }
        }
/*  A= (int *) malloc(m*n*sizeof(int));
    B= (int *) malloc(n*p*sizeof(int));
    C= (int *) calloc(m*p,sizeof(int));
    printf("Please enter the elements of matrix A:\n");
    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
        {
            printf("A[%d][%d] = ",i+1,j+1);
            scanf("%d",&A[i*n+j]);
        }
    printf("Please enter the elements of matrix B:\n");
    for(i=0;i<n;i++)
        for(j=0;j<p;j++)
        {
            printf("B[%d][%d] = ",i+1,j+1);
            scanf("%d",&B[i*p+j]);
        }
    
    for(i=0;i<m;i++)
        for(j=0;j<p;j++)
        {
            b=0;
            for(a=j;a<n;a++)
            {
                C[i*p+j]+=A[i*n+a]*B[b*p+j];
                b++;
            }
        }
    mat_print(C,m,p);*/
}

int main()
{
    //mat_sum();
    mat_mul();
    return 0;
}