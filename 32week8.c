#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct word
{
    char word[255];
    int count;
    struct word *left;
    struct word *right;
};

struct word *root=NULL;

int menu()
{
    printf("1. Input File\n2. Search\n3. All words List\n4.Thoat\n");
    
    char s[10];
    int c;
    scanf("%[^\n]%*c", s);
    c = atoi(s);
    return c;
}

struct word* search(char *word) 
{
    if (root==NULL) return NULL;
    struct word *current = root;

    while(strcmp(current->word,word)!=0) 
    {
        if(strcmp(word, current->word)<0) 
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

int insert(char *word)
{
    struct word * re=search(word);
    if (re!= NULL) {
        re->count= re->count +1;
        return 1;
    }


    struct word *temp = (struct word *)malloc(sizeof(struct word));
    struct word *parent;
    struct word *current;

    strcpy(temp->word, word);
    temp->left = NULL;
    temp->right = NULL;
    temp->count = 1;

    
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
            if (strcmp(word, parent->word)<0)
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


int isWord(char word)
{
    if ((word>='a')&&(word<='z')) return 1;
    else if ((word>='A')&&(word<='Z')) return 1;
    else return 0;     
}

char* substring(char* s,int pos)    
{   
    char* t = &s[pos];
    s[pos-1] = '\0';
    return t;
}


int addWord(char *word)
{
    int i,wrongWord=0;
    for (i=0; i<strlen(word); i++)
    {
        if (!isWord(word[i])) 
        {
            word[i]=' ';
            wrongWord=1;
        }  
    }
    if (wrongWord==1)
    {
        while (1)
        {
            char buf[255];
            if (sscanf(word,"%s", buf)==EOF) break;
            word = substring(word, strlen(buf)+1);
            addWord(buf);
        }
    }
    else insert(word);
    return 0;
}

int getWords(char *fileName)
{
    FILE *f;
    f = fopen(fileName, "r+");
    if (f == NULL) 
    {
        perror("Can't open File\n");
        return -1;
    }

    while (1)
    {
        char word[255];
        if (fscanf(f,"%s", word)==EOF) break;
        addWord(word);
    }
    fclose(f);
    return 0;
}

void pre_order_traversal(struct word* root) 
{
   if(root != NULL) 
   {
      pre_order_traversal(root->left);
      printf("%s\n",root->word);
      pre_order_traversal(root->right);
   }
}

int putList(char *fileName)
{    
    pre_order_traversal(root);
    return 0;
}

int getFile(char *fileName)
{
    root=NULL;
    printf("Text Here:");
    scanf("%[^\n]%*c", fileName);

    char *text= (char *)malloc(sizeof(char));
    FILE *f;
    f = fopen(fileName, "r+");
    if (f == NULL) 
    {
        perror("Can't open File\n");
        return -1;
    }
    while (1)
    {
        if (fscanf(f,"%[^\0]",text)==EOF) break;
    } 
    printf("%s", text);
    fclose(f);
    getWords(fileName);
    return 1;
}

void showWord()
{
    char word[255];
    printf("Nhap tu can tim:");
    scanf("%[^\n]%*c", word);
    struct word* re = search(word);
    if (re!= NULL) {
        printf("%s x%d\n", re->word, re->count);
    }
    else {
        printf("Khong tim thay\n");
    }
}

int main()
{
    int c;
    char *fileName = (char *)malloc(sizeof(char));
    while (c!=4)
    {
        c = menu();
        switch (c)
        {
            case 1: getFile(fileName); 
            break;
            case 2: showWord();
            break;
            case 3: putList(fileName);
            break;
        }
    }
    free(fileName);
    return 0;
}