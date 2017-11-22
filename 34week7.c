#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char passAdmin[] = {'a','d','m','i','n','\0'};

struct user 
{
    char username[255];
    char password[255];

    struct user *left;
    struct user *right;
};

struct user *root = NULL;
struct user *nowUser = NULL;

int insert(char *username, char *password)
{
    struct user *temp = (struct user *)malloc(sizeof(struct user));
    struct user *parent;
    struct user *current;
    strcpy(temp->username, username);
    strcpy(temp->password, password);
    //temp->password[strlen(password)-1]='\0';
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
            if (strcmp(username, parent->username)<0)
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

int get_all_users()
{
    FILE *f;
    f = fopen("pass.txt", "r+");
    if (f == NULL) 
    {
        perror("LOI DOC FILE\n"); 
        return 1;
    }
    do 
    {
        char username[255];
        char password[255];
        //Nếu dùng %[^ ] %[\n] thì có vấn đè với chiều dài sâu trong password
        if (fscanf(f, "%[^ ] %[^\n]\n", username, password) == EOF) return 0;
        password[strlen(password)-1]='\0';
        insert(username, password);
    } while (1);

    fclose(f);
}

int isAdmin(char *username, char *password)
{
    
    if (strcmp(username,"admin")!=0) return 0;
    //printf("%s %s \n", passAdmin, password);
    //printf("%d\n", strcmp(password, passAdmin));
    if (strcmp(password, passAdmin) == 0)
    {
        nowUser = NULL;
        return 1;
    }
}

struct user* search(char *username) 
{
    struct user *current = root;

    while(strcmp(current->username,username)!=0) {

        if(strcmp(username, current->username)<0) {
            current = current->left;
        }
        else {                
            current = current->right;
        }

        if(current == NULL) {
            return NULL;
        }
    }

    
   
    return current;
}

int isUser(char *username, char *password)
{
    nowUser = search(username);
    //printf("%s %s\n",nowUser->username, nowUser->password);
    //printf("%d %d\n", strlen(password), strlen(nowUser->password));
    if (nowUser == NULL) return 0;
    else 
    {
        if (strcmp(password, nowUser->password)==0) return 1;
    }
    return 0;
}

int login()
{
    int errorTime=0;
    while (errorTime!=3)
    {
        char username[255];
        char password[255];
        printf("username: ");
        scanf("%[^\n]%*c", username);
        printf("password: ");
        scanf("%[^\n]%*c", password);

        if (isAdmin(username, password)==1) return -1;
        if (isUser(username, password)) return 1;
        //if (isUser(username, password)) return 1;

        errorTime=errorTime+1;
    }
    return 0;
}

void pre_order_traversal(struct user* root) 
{
   if(root != NULL) 
   {
      printf("%s\n",root->username);
      pre_order_traversal(root->left);
      pre_order_traversal(root->right);
   }
}

void f_pre_order_traversal(struct user* root, FILE *f)
{
    if(root != NULL) 
   {
      fprintf(f, "%s %s\n",root->username, root->password);
      f_pre_order_traversal(root->left, f);
      f_pre_order_traversal(root->right,f );
   }
}

int rightPassword(char *password)
{
    int i;
    for (i=0; i<strlen(password); i++)
    {
        if (password[i]>'A'&&password[i]<'Z') ;
        else if (password[i]>'a'&&password[i]<'z') ;
        else if (password[i]>'0'&&password[i]<'9') ;
        else if (password[i]=='$'||password[i]=='_');
        else return 0;
    }
    return 1;
}

void userMenu()
{
    int c=0;
    char password[255];
    while (c!=2)
    {
        printf("1. Doi mat khau\n2. Thoat\n");
        scanf("%d%*c", &c);
        if (c==1) 
        {
            
            printf("Nhap mat khau moi: ");
            while (1)
            {
                scanf("%[^\n]", password);
                if (rightPassword(password)==1) break;
            }
        }
    }
    strcpy(nowUser->password, password);
}

int rightUsername(char *username)
{
    int i=0;
    if (strlen(username)<6) return 0;
    for (i=0; i<strlen(username); i++)
    {
        if (username[i]==' ') return 0;
    }
    return 1;
}

void addUser()
{
    char username[255];
    char password[255];
    printf("New Username: ");
    while (1)
    {
        scanf("%[^\n]%*c", username);
        if (rightUsername(username)==1) break;

    }
    printf("Password: ");
    while (1)
    {
        scanf("%[^\n]%*c", password);
        if (rightPassword(password)==1) break;
    }
    printf("%s %s\n", username, password);

    insert(username, password);
}

void changePassword()
{
    char username[255];
    char password[255];
    printf("Username can thay doi: ");
    scanf("%s", username);
    struct user *changer = search(username);
    if (changer == NULL) printf("Khong tim thay username\n");
    else {
        printf("New Password for %s: ", changer->username);
        while (1)
        {
            scanf("%*c%[^\n]", password);
            if (rightPassword(password)==1) break;
        }
        printf("Xac nhan: %s\n", password);
        strcpy(changer->password, password);
    }
}

void adminMenu()
{
    int c=0;
    while(c!=4)
    {
        printf("1. Them User\n2. Doi mat khau User\n3. Danh sach User\n4. Thoat\n");
        scanf("%d%*c", &c);
        switch (c)
        {
            case 1: addUser(); break;
            case 2: changePassword(); break;
            case 3: pre_order_traversal(root); break; 
        }

    }
}

void put_all_users()
{
    FILE *f;
    f = fopen("pass.txt", "w+");
    f_pre_order_traversal(root, f);
    fclose(f);
}

int main()
{
    get_all_users();
    //pre_order_traversal(root);
    int c=1;
    while (c)
    {
        c=login();
        if (c==1) userMenu();
        else if (c==-1) adminMenu();
    }
    put_all_users();
    return 0;
}