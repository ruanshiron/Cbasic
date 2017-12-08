#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct SP
{
    int maSP;
    char tenSP[20];
    char motaSP[100];
    int giaSP;
    int SL;
    struct SP * next;
};

struct SP *head =NULL;

struct mangSP
{
    int maSP;
    char tenSP[20];
    char motaSP[100];
    int giaSP;
    int SL;
};

struct mangSP sanPham[100];//= (struct mangSP*) malloc(sizeof(struct mangSP));
//
int menu()
{
    printf("1. Nhap SP\n2. SANPHAM.txt\n3. Tim theo maSP\n4. Thoat\n");
    
    char s[10];
    int c;
    scanf("%[^\n]%*c", s);
    c = atoi(s);
    return c;
}

////
    void chenVaoDanhSach(char *, char *, char *, int, int);
    int nhapTuBanPHim(char *, char *, char *, int *, int *);
    void ghiVaoFile();
////
void nhapSP()
{
    char maSP[10];
    char tenSP[20];
    char motaSP[100];
    int giaSP;
    int SL;
    
    if (nhapTuBanPHim(maSP,tenSP,motaSP,&giaSP,&SL)) 
    {
        chenVaoDanhSach(maSP,tenSP,motaSP,giaSP,SL);
        ghiVaoFile();
    }
}
    //
        int laSoNguyen(char *);
        int laMaSP(int);
    //
    int nhapTuBanPHim(char *maSP, char * tenSP, char * motaSP, int * giaSP, int * SL)
    {
        do 
        {
            printf("maSP:");
            scanf("%[^\n]%*c", maSP);
            if (laSoNguyen(maSP)==0) return 0;
        } while (!laMaSP(atoi(maSP)));
        printf("tenSP:");
        scanf("%[^\n]%*c", tenSP);
        printf("motaSP:");
        scanf("%[^\n]%*c", motaSP);
        printf("giaSP:");
        scanf("%d%*c", giaSP);
        printf("SL:");
        scanf("%d%*c", SL);
        
        return 1;
    }
        int laSoNguyen(char *xau)
        {
            int i;
            int l=strlen(xau);
            for(i=0; i<l; i++)
            {
                if ((xau[i]>='0')&&(xau[i]<='9'));
                else return 0;
            }
            return 1;
        }
        int laMaSP(int maSP)
        {
            if ((maSP>=101)&&(maSP<=500)) return 1;
            return 0;
        }
    //
        void chenVao_dau_DanhSach(struct SP**);
        struct SP *timChenVaoSau(int);
    
    void chenVaoDanhSach(char *maSP, char * tenSP, char * motaSP, int giaSP, int SL)
    {
        struct SP *link = (struct SP*) malloc(sizeof(struct SP));

        link->maSP = atoi(maSP);
        strcpy(link->tenSP, tenSP);
        strcpy(link->motaSP, motaSP);
        link->giaSP= giaSP;
        link->SL= SL;

        if (head==NULL) chenVao_dau_DanhSach(&link);
        else if (head->maSP>link->maSP) chenVao_dau_DanhSach(&link);
        else 
        {
            struct SP *chenVaoSau = timChenVaoSau(link->maSP);
            //
            link->next = chenVaoSau->next;
            chenVaoSau->next = link;
        }
        //free(link);
    }
    //
        void chenVao_dau_DanhSach(struct SP** link)
        {
            (*link)->next = head;
            head = (*link);
        }
        //
        struct SP *timChenVaoSau(int maSP)
        {
            struct SP *insert=head;
            struct SP *aft_insert=head->next;
            while (insert != NULL)
            {
                if (insert->next==NULL)
                {
                    return insert;
                }
                else if ((insert->maSP<maSP) && (aft_insert->maSP>maSP))
                {
                    return insert;
                }
                aft_insert = aft_insert->next;
                insert = insert->next;
            }
        }
    
    void ghiVaoFile()
    {
        struct SP *duyet = head;
        FILE *f;
        f= fopen("SANPHAM.txt","w+");
        while (duyet!=NULL)
        {
            fprintf(f, "%d, %s, %s, %d, %d\n", duyet->maSP, duyet->tenSP, duyet->motaSP, duyet->giaSP, duyet->SL);
            duyet= duyet->next;
        }
        fclose(f);
    }

//
    void ghiVaoMang(struct mangSP, int);
////
void docFile()
{
    FILE *f;
    f = fopen("SANPHAM.txt", "r");
    if (f==NULL) perror("LOI");
    else {
        int i=0;
        while (1)
        {
            struct mangSP tem;
            if (fscanf(f, "%d, %[^,], %[^,], %d, %d\n",&tem.maSP, tem.tenSP, tem.motaSP, &tem.giaSP, &tem.SL)==EOF) break;
            ghiVaoMang(tem, i);
            i++;
        }
    }
    fclose(f);
}
    //
    void ghiVaoMang(struct mangSP tem, int i)
    {
        sanPham[i].maSP= tem.maSP;
        strcpy(sanPham[i].tenSP, tem.tenSP);
        strcpy(sanPham[i].motaSP, tem.motaSP);
        sanPham[i].giaSP= tem.giaSP;
        sanPham[i].SL= tem.SL;
    }

////
    //
    int BinarySearch(struct mangSP a[], int left, int right, int maSP, int *count);
void timMaSP()
{
    printf("Nhap maSP:");
    int maSP;
    scanf("%d%*c", &maSP);
    int n=0, count=0;
    while (1)
    {
        if (sanPham[n].maSP>100) n++;
        else break;
    }
    int ketqua= BinarySearch(sanPham, 0, n, maSP, &count);
    printf("%d, %s, %s, %d, %d\n",sanPham[ketqua].maSP, sanPham[ketqua].tenSP, sanPham[ketqua].motaSP, sanPham[ketqua].giaSP, sanPham[ketqua].SL);
    printf("%d\n", count);
}
// /
    int BinarySearch(struct mangSP a[], int left, int right, int maSP, int *count)
    { 
        if (left > right) return -1;
        
        int mid = (left + right) / 2;
        
        if (maSP == a[mid].maSP) 
            return mid;

            if (maSP < a[mid].maSP) 
            return BinarySearch(a,left,mid-1,maSP, &*count);

        if (maSP > a[mid].maSP) 
                return BinarySearch(a,mid+1,right,maSP, &*count);

        (*count)++;
    }
/*--MAIN--*/
int main()
{
    int c;
    while (c!=4)
    {
        c = menu();
        switch (c)
        {
            case 1: nhapSP(); 
            break;
            case 2: docFile();
            break;
            case 3: timMaSP();
            break;
        }
    }
    free(head);
    return 1;
}



