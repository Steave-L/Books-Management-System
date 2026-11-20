/*界面有关函数*/
#include "Root.h"
#include "Welcome.h"

// 登录界面
void Welcom_LoginInterface(UserList UserHead, LinkList head)
{
    system("cls");
    printf("\n=========================图书管理系统========================\n");
    printf("管理员登录*******************************1\n");
    printf("用户登录*********************************2\n");
    printf("没有账号？创建用户***********************3\n");
    printf("退出*************************************4\n");
    printf("\n============================欢迎！===========================\n");

    int control;
    while (1)
    {
        printf("输入要进行的操作：");
        if (scanf("%d", &control) != 1 || control < 1 || control > 4)
        {
            printf("输入有误！");
            while (getchar() != '\n')
                ;
            continue;
        }
        break;
    }

    char YN;
    switch (control)
    {
    case 1:
        system("cls");
        if (Welcom_RootLogin())
        {
            while (1)
            {
                Welcom_RootInterface(UserHead, head);

                // 是否继续判断
                if (Welcom_NeedContinue())
                {
                    continue;
                }
                break;
            }
        }
        break;

    case 2:
        system("cls");
        User *user = Welcom_UserLogin(UserHead);
        if (user != NULL)
        {
            User_BorrowFileRead(user);
            while (1)
            {
                Welcom_UserInterface(user, head);

                // 是否继续判断
                if (Welcom_NeedContinue())
                {
                    continue;
                }
                break;
            }

            User_BorrowFileSave(user);
        }
        break;
    case 3:
        system("cls");
        Welcom_UserCreate(UserHead);
        break;
    case 4:
        system("cls");
        printf("再见！\n");
        break;
    }
}

// 是否继续函数
bool Welcom_NeedContinue(void)
{
    /*是否继续函数（重复使用）*/
    char YN;
    while (getchar() != '\n')
        ; // 需要清除缓冲区
    printf("是否继续使用？(Y/N):");
    scanf("%c", &YN);

    if (YN == 'Y' || YN == 'y')
    {
        system("cls");
        return true;
    }
    else
    {
        system("cls");
        printf("再见！\n");
        return false;
    }
}

// 管理员登录
bool Welcom_RootLogin(void)
{
    char ID[10];       // ID
    char password[18]; // 密码

    printf("请输入ID:");
    scanf("%s", ID);
    printf("请输入密码：");
    scanf("%s", password);

    if (strcmp(ID, ROOTID) == 0 && strcmp(password, ROOTPASSWARD) == 0)
    {
        printf("管理员账户密码输入正确！\n");
        return true;
    }
    else
    {
        printf("管理员账户密码输入错误！\n");
        return false;
    }
}

// 用户登录
///@return 输入正确返回用户节点，输入错误返回NULL。
User *Welcom_UserLogin(UserList UserHead)
{
    char ID[10];       // ID
    char password[18]; // 密码

    printf("请输入ID:");
    scanf("%s", ID);
    printf("请输入密码：");
    scanf("%s", password);

    User *temp = User_ListIDSearch(UserHead, ID);
    int right_flag = 0;

    if (temp != NULL)
    {
        if (strcmp(password, temp->password) == 0)
        {
            right_flag = 1;
        }
    }

    if (right_flag == 1)
    {
        printf("用户账户密码输入正确！\n");
    }
    else
    {
        printf("用户账户密码输入错误！\n");
        temp = NULL;
    }

    return temp;
}

// 创建用户
void Welcom_UserCreate(UserList UserHead)
{
    Root_AddUser(UserHead);
}

// 管理员主界面
void Welcom_RootInterface(UserList UserHead, LinkList head)
{
    // system("cls");
    printf("\n=============================ROOT===========================\n");
    printf("图书信息录入*********************************1\n");
    printf("图书信息删除*********************************2\n");
    printf("图书信息更新*********************************3\n");
    printf("图书信息显示*********************************4\n");
    printf("图书年份搜索*********************************5\n");
    printf("图书借阅次数排序输出*************************6\n");
    printf("添加新用户  *********************************7\n");
    printf("删除用户    *********************************8\n");
    printf("更新用户信息*********************************9\n");
    printf("查看用户列表*********************************10\n");
    printf("退出*****************************************11\n");
    printf("\n============================================================\n");

    int control;
    while (1)
    {
        printf("输入要进行的操作：");
        if (scanf("%d", &control) != 1 || control < 1 || control > 11)
        {
            printf("输入有误！");
            while (getchar() != '\n')
                ;
            continue;
        }
        break;
    }

    switch (control)
    {
    case 1:
        Root_AddBook(head);
        File_Save(head); // 更新完后即保存
        break;

    case 2:
        Root_DeleteBook(head);
        File_Save(head);
        break;
    case 3:
        Root_ChangeInformation(head);
        File_Save(head);
        break;
    case 4:
        Root_PrintBookList(head);
        break;
    case 5:
        Root_FuzzySearch(head);
        break;
    case 6:
        Root_BrrowTimeSort(head);
        File_Save(head);
        break;
    case 7:
        Root_AddUser(UserHead);
        User_FileSave(UserHead);
        break;
    case 8:
        Root_UserDelet(UserHead);
        User_FileSave(UserHead);
        break;
    case 9:
        Root_UserChange(UserHead);
        User_FileSave(UserHead);
        break;
    case 10:
        Root_PrintUserList(UserHead);
        break;
    case 11:

        break;
    }
}

// 用户主界面
void Welcom_UserInterface(User *user, LinkList head)
{
    // system("cls");
    printf("\n=============================USER===========================\n");
    printf("图书查询*********************************1\n");
    printf("图书借阅*********************************2\n");
    printf("图书归还*********************************3\n");
    printf("借阅查询*********************************4\n");
    printf("退出*************************************5\n");
    printf("\n============================================================\n");

    int control;
    while (1)
    {
        printf("输入要进行的操作：");
        if (scanf("%d", &control) != 1 || control < 1 || control > 5)
        {
            printf("输入有误！");
            while (getchar() != '\n')
                ;
            continue;
        }
        break;
    }

    switch (control)
    {
    case 1:
        User_Search(head);
        break;

    case 2:
        User_Borrow(head, user);
        File_Save(head); // 借完书后即保存（因为是从头开始写，当书库过多时是否会影响时间复杂度？）
        User_BorrowFileSave(user);
        break;
    case 3:
        User_Return(head, user);
        File_Save(head);
        User_BorrowFileSave(user);
        break;
    case 4:
        User_PrintBorrowBook(user);
        break;
    case 5:
        break;
    }
}
