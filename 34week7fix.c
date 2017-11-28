//by Nguyen The Vinh

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct user 
{
    char username[255];
    char password[255];
    struct user *left;
    struct user *right;
};

struct user *root= NULL;
struct user *nowUser= NULL;

//Ham duyet tree
void pre_order_traversal(struct user* root) 
{
   if(root != NULL) 
   {
      printf("%s %s\n",root->username, root->password);
      pre_order_traversal(root->left);
      pre_order_traversal(root->right);
   }
}

struct user* search(char *username) 
{
    struct user *current = root;

    while(strcmp(current->username,username)!=0) 
    {
        if(strcmp(username, current->username)<0) 
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

//Them mot user vao tree
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

//Them user tu trong file vao tree
int getAllUsers()
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
        //password[strlen(password)-1]='\0';
        insert(username, password);
    } while (1);

    fclose(f);
}

//Ham kiem tra chuan password
int isPassword(char *password)
{
    int i;
    if (strcmp(password, "admin")==0) return 1;
    if (strlen(password)<6) return 0;
    for (i=0; i<strlen(password); i++)
    {
        if (password[i]>='A'&&password[i]<='Z') ;
        else if (password[i]>='a'&&password[i]<='z') ;
        else if (password[i]>='0'&&password[i]<='9') ;
        else if (password[i]=='$'||password[i]=='_');
        else return 0;
    }
    return 1;
}

//Ham kiem tra chuan username
int isUsername(char *username)
{
    int i=0;
    for (i=0; i<strlen(username); i++)
    {
        if (username[i]==' ') return 0;
    }
    return 1;
}

//Ham xac dinh User
int isUser(char *username, char *password)
{
    nowUser = search(username);
    //printf("%s %s\n",nowUser->username, nowUser->password);
    //printf("%d %d\n", strlen(password), strlen(nowUser->password));
    if (nowUser == NULL) return 0;
    if (strcmp(password, nowUser->password)==0) return 1;
    return 0;
}

//Ham xac dinh Admin
int isAdmin(char *username, char *password)
{
    if (strcmp(username,"admin")!=0) return 0;
    if (strcmp(password,"admin")==0) return 1;
    return 0;
}

//thay mat khau nguoi dung
int changePassword()
{
    char password[255];
    printf("New Password:");
    do {
        scanf("%[^\n]%*c", password);
    } while(!isPassword(password));

    strcpy(nowUser->password,password);
    return 1;
}

//them user
void addUser()
{
    char username[255];
    char password[255];
    printf("New Username: ");
    while (1)
    {
        scanf("%[^\n]%*c", username);
        if (isUsername(username)) break;

    }
    printf("Password: ");
    while (1)
    {
        scanf("%[^\n]%*c", password);
        if (isPassword(password)) break;
    }
    printf("%s %s\n", username, password);

    insert(username, password);
}

//doi mat khau nguoi dung cho admin
int changeUserPassword()
{
    char username[255];
    printf("Username Needle:");
    do {
        scanf("%[^\n]%*c", username);
    } while (!isUsername(username));

    nowUser = search(username);
    changePassword();
}

//Ham xac dinh user/admin
int login()
{
    int errorTime=0;
    char username[255];
    char password[255];
    while (errorTime!=3)
    {
        printf("Username:");
        do {
            scanf("%[^\n]%*c", username);
            //Loi thoat cho phan dang nhap
            if (strcmp(username,"###")==0) return 0;
        } while (!isUsername(username));
        printf("Password:");
        do {
            scanf("%[^\n]%*c", password);
        } while (!isPassword(password));

        if (isAdmin(username,password)) return -1;
        if (isUser(username,password)) return 1;
        errorTime++;
    }
    return 0;
}

int menuUser()
{
    printf("1. Change your Password\n2. Exit\n");
    char s[10];
    scanf("%s%*c",s);
    int c= atoi(s);
    return c;
}

//menu cua User
int userMenu()
{
    int d=1;
    do
    {
        d = menuUser();
        //scanf("%d%*c",&d);
        if (d==1) changePassword();

    } while (d!=2);
    return 0;
}

int menuAdmin()
{
    printf("1. Add User\n2. Change UserPassword\n3. User List\n4. Exit\n");
    char s[10];
    scanf("%s%*c",s);
    int c = atoi(s);
    return c;
}
//menu Admin
int adminMenu()
{
    int c=0;
    while (c!=4)
    {
        c = menuAdmin();
        switch (c)
        {
            case 1: addUser(); break;
            case 2: changeUserPassword(); break;
            case 3: pre_order_traversal(root); break;
        }
    }
}

//Duyet User & xuat file
void putUser(struct user* root, FILE *f) 
{
   if(root != NULL) 
   {
      fprintf(f,"%s %s\n",root->username, root->password);
      putUser(root->left,f);
      putUser(root->right,f);
   }
}
//In User ra file   
void putAllUsers()
{
    FILE *f;
    f = fopen("pass.txt", "w+");
    putUser(root,f);
    fclose(f);
}

int main()
{
    int c = 1;
    getAllUsers();
    pre_order_traversal(root);
    while (c)
    {
        c = login();
        printf("%d\n", c);
        switch (c)
        {
            case 1: userMenu(); break; 
            case -1: adminMenu(); break;
        }
    }
    putAllUsers();
}