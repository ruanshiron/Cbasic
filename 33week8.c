#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct word
{
    char eng[20];
    char viet[20];
    struct word *left;
    struct word *right;
};

struct word *root=NULL;

int menu()
{
    printf("1. Doc data\n2. Data\n3. Dich\n4. Thoat\n");
    
    char s[10];
    int c;
    scanf("%[^\n]%*c", s);
    c = atoi(s);
    return c;
}

int insert(char *eng, char *viet)
{
    struct word *temp = (struct word *)malloc(sizeof(struct word));
    struct word *parent;
    struct word *current;

    strcpy(temp->eng, eng);
    strcpy(temp->viet, viet);
    
    temp->left = NULL;
    temp->right = NULL;
    
    if (root == NULL) 
    {
        root = temp;
    }
    else
    {
        current = root;
        parent = NULL;

        while (1)
        {
            parent = current;
            if (strcmp(eng, parent->eng)<0)
            {
                current = current->left;

                if (current == NULL) 
                {
                    parent->left = temp;
                    return 0;
                }
            }
            else
            {
                current = current->right;

                if (current == NULL)
                {
                    parent->right = temp;
                    return 0;
                }
            }
        }
    }
}


int getFile()
{
    char eng[20];
    char viet[20];
    FILE *f;
    f = fopen("data.txt", "r+");
    if (f == NULL) 
    {
        perror("Can't open File\n");
        return -1;
    }
    while (1)
    {
        if (fscanf(f,"%s    %[^\n]\n",eng , viet)==EOF) break;
        viet[strlen(viet)]='\0';
        insert(eng, viet);
    } 
    fclose(f);
    return 1;
}

void pre_order_traversal(struct word* root) 
{
   if(root != NULL) 
   {   
      pre_order_traversal(root->left);
      printf("%s: %s\n",root->eng, root->viet);
      pre_order_traversal(root->right);
   }
}

void putData()
{
    pre_order_traversal(root);
}

struct word* search(char *eng) 
{
    struct word *current = root;

    while(strcmp(current->eng,eng)!=0) 
    {
        if(strcmp(eng, current->eng)<0) 
        {
            current = current->left;
        }
        else 
        {                
            current = current->right;
        }

        if(current == NULL) 
        {
            return NULL;
        }
    }   
    return current;
}

void addWord()
{
    int n,i;
    printf("Nhap so tu can bo sung: ");
    scanf("%d",&n);
    for(i=0; i<n; i++)
    {
        char eng[20];
        char viet[20];
        printf("Tieng Anh:");
        scanf("%s%*c", eng);
        printf("Tieng Viet:");
        scanf("%[^\n]%*c", viet);
        insert(eng, viet);
    }
}

int wordEx(char *text, char *tran)
{
    if (strlen(text)==0) return 0;
    else {
        char word[20];
        sscanf(text, "%s", word);
        printf("%s: ", word);
        int l = strlen(word);
        struct word *re= search(word);
        if (re!=NULL) 
        {
            printf("%s\n", re->viet);
            if (strlen(tran)!=0) strcat(tran, re->viet);
            else strcpy(tran, re->viet);
            strcat(tran, " ");
        }
        else 
        {
            printf("No data\n");
            return -1;
        }
        wordEx(text+l+1, tran);
    }
}

int translateOption()
{
    char text[255];
    printf("Nhap cau:");
    scanf("%[^\n]%*c",text);
    printf("\n");
    char tran[255]; tran[0]='\0';
    if (root==NULL) return 0;
    if (wordEx(text, tran)==-1) 
    {
        printf("Thieu tu\n\n");
        addWord();
    }
    else printf("\nTranlate: %s\n", tran);
}

void putWord(struct word* root, FILE *f) 
{
   if(root != NULL) 
   {
      fprintf(f,"%s    %s\n",root->eng, root->viet);
      putWord(root->left,f);
      putWord(root->right,f);
   }
}

void putDataFile()
{
    FILE *f;
    f = fopen("data.txt", "w+");
    putWord(root,f);
    fclose(f);
}

int main()
{
    int c;
    
    while (c!=4)
    {
        c = menu();
        switch (c)
        {
            case 1: getFile(); 
            break;
            case 2: putData();
            break;
            case 3: translateOption();
            break;
        }
    }
    putDataFile();
    return 0;
}