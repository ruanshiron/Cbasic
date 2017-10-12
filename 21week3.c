/*By Nguyen The Vinh*/


#include <stdio.h>
#include <stdlib.h>

struct num 
{
    int data;
    struct num* next;
};

void make_NULL(struct num** List)
{
    *List = NULL;
}

void add_head(struct num** link, struct num** List)
{
    (*link)->next = *List;
    *List = *link;
}

struct num* creat_link(int data, struct num* link)
{
    link = (struct num*) malloc(sizeof(struct num));
    link->data = data;
    return link;
}

struct num* add_behind(int data, struct num* current)
{
    struct num* behind_current = current->next;
    while (1)
    {
        if (current->next == NULL)
        {
            return current;
        }
        else if ((current->data <= data) && (behind_current->data) >= data)
        {
            return current;
        }
        behind_current = behind_current->next;
        current = current->next;
    }
}

void insert(int data, struct num** List)
{
    struct num* link = creat_link(data,link);
    struct num* current = *List;

    if (!(*List)) add_head(&link, List);
    else if (current->data > data) add_head(&link, List);
    else
    { 
        current = add_behind(data, current);
        link->next = current->next;
        current->next = link;
    }
}

void make_List(struct num** List)
{
    int n;
    printf("\nNhap so phan tu: ");
    scanf("%d", &n);

    int i;
    for (i=0; i<n; i++)
    {
        int data;
        printf("#%d: ", i+1);
        scanf("%d", &data);
        insert(data, List);
    }
}

void print_List(struct num* List)
{
    struct num* now_printf = List;
    printf("\n");
    while (now_printf != NULL)
    {
        printf("%d ", now_printf->data);
        now_printf = now_printf->next;
    }
}

struct num* combine_List(struct num** List1, struct num** List2)
{
    struct num* List;
    make_NULL(&List);
    struct num* current;
    
    struct num* current1 = *List1;
    struct num* current2 = *List2;

    //Tao diem dau danh sach tu 1 trong 2 danh sach cu
    if (current1==NULL) return *List2;
    else if (current2==NULL) return *List1;
    else 
    {
        if (current1->data <= current2->data)
        {
            List = current1;
            current1 = current1->next;
        }
        else 
        {
            List = current2;
            current2 = current2->next;
        }
    }
    //
    current = List;

    printf("\n");

    // Duoi day la ham chay de gop 2 List Lai voi nhau 
    while (1)
    {
        if (current1 == NULL) 
        {
            current->next = current2; 
            break;
        }
        else if (current2 == NULL) 
        {
            current->next = current1;
            break;
        }
        else if (current1->data >= current2->data) 
        {
            current->next = current2;
            current2 = current2->next;
            current=current->next;       
        }
        else if (current1->data < current2->data)
        {
            current->next = current1;
            current1 = current1->next;     
            current=current->next;
        }     
        else if (current->next == NULL) break;
    }

    return List;
}
int main()
{
    struct num *List1;
    struct num *List2;
    struct num *CombineList;

    make_NULL(&List1);
    make_NULL(&List2);
    make_NULL(&CombineList);

    make_List(&List1);
    make_List(&List2);

    print_List(List1);
    print_List(List2);

    CombineList = combine_List(&List1, &List2);
    print_List(CombineList);
    return 0;
}