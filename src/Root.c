/*管理员有关函数*/
#include "Root.h"

/*面向对象函数*/

// 管理员增加一个节点
void Root_AddBook(LinkList head)
{
    char name[50];   // 书名
    char writer[50]; // 作者
    char press[50];  // 出版社
    char year[20];   // 出版年份
    int inventory;

    char class[20];       //新增图书类别
    system("cls");

    printf("\n=======================增加图书======================\n");

    printf("请输入书名：");
    scanf("%s", name);
    printf("请输入作者：");
    scanf("%s", writer);
    printf("请输入出版社：");
    scanf("%s", press);
    printf("请输入出版年份：");
    scanf("%s", year);
    printf("请输入库存数量：");
    scanf("%d", &inventory);

    printf("请输入图书类别：");
    scanf("%s", class);

    node *new = Link_CreatNode(name, writer, press, year, inventory,0,class); //借阅次数为0

    Link_HeadInsert(head, new);
}

// 管理员删除图书
void Root_DeleteBook(LinkList head)
{
    system("cls");
    printf("\n=======================删除图书======================\n");
    printf("搜索要删除的书名*********************1\n");
    printf("搜索要删除的编号*********************2\n");
    printf("退出********************************3\n");
    printf("\n====================================================\n");

    int control;
    while (1)
    {
        printf("输入要进行的操作：");
        if (scanf("%d", &control) != 1 || control < 1 || control > 3)
        {
            printf("输入有误！");
            while (getchar() != '\n')
                ;
            continue;
        }
        break;
    }

    node *temp;
    int pos = 1;

    switch (control)
    {
    case 1:
        system("cls");
        printf("输入要删除的图书的书名：");
        char str[50];
        scanf("%s", str);
        pos = 1;
        temp = Link_CharSearch(head, str, &pos);

        if (temp == NULL)
        {
            printf("图书库中未找到 %s 一书,删除失败\n", str);
        }
        else
        {
            Link_PosDelete(head, pos);
            printf("图书已成功删除：");
            Link_NodePrint(temp);
            free(temp);
        }
        break;

    case 2:
        system("cls");
        printf("输入要删除的图书的编号：");

        int num;
        while (1)
        {
            if (scanf("%d", &num) != 1 || num < 1 || num > head->size)
            {
                printf("编号输入有误,重新输入:");
                while (getchar() != '\n')
                    ;
                continue;
            }
            break;
        }

        temp = Link_PosSearch(head, num);

        if (temp == NULL)
        {
            printf("图书库中未找到编号为 %d 一书,删除失败\n", num);
        }
        else
        {
            Link_PosDelete(head, pos);
            printf("下列图书已成功删除：");
            Link_NodePrint(temp);
            free(temp);
        }
        break;
    case 3:

        break;
    }
}

// 管理员更新图书信息
void Root_ChangeInformation(LinkList head)
{
    system("cls");
    printf("\n====================更新图书信息=====================\n");
    printf("搜索要更新的书名*********************1\n");
    printf("搜索要更新的编号*********************2\n");
    printf("退出********************************3\n");
    printf("\n====================================================\n");

    int control;
    while (1)
    {
        printf("输入要进行的操作：");
        if (scanf("%d", &control) != 1 || control < 1 || control > 3)
        {
            printf("输入有误！");
            while (getchar() != '\n')
                ;
            continue;
        }
        break;
    }

    node *temp;
    int pos = 1;

    switch (control)
    {
    case 1:
        system("cls");
        printf("输入要更新的图书的书名：");
        char str[50];
        scanf("%s", str);
        pos = 1;
        temp = Link_CharSearch(head, str, &pos);

        if (temp == NULL)
        {
            printf("图书库中未找到 %s 一书,删除失败\n", str);
        }
        else
        {
            printf("请输入新书名：");
            scanf("%s", temp->book.name);
            printf("请输入新作者：");
            scanf("%s", temp->book.writer);
            printf("请输入新出版社：");
            scanf("%s", temp->book.press);
            printf("请输入新出版年份：");
            scanf("%s", temp->book.year);
            printf("请输入新库存数量：");
            scanf("%d", &(temp->book.inventory));

            printf("图书更新成功！\n");
        }
        break;

    case 2:
        system("cls");
        printf("输入要更新的图书的编号：");

        int num;
        while (1)
        {
            if (scanf("%d", &num) != 1 || num < 1 || num > head->size)
            {
                printf("编号输入有误,重新输入:");
                while (getchar() != '\n')
                    ;
                continue;
            }
            break;
        }

        temp = Link_PosSearch(head, num);

        if (temp == NULL)
        {
            printf("图书库中未找到编号为 %d 一书,删除失败\n", num);
        }
        else
        {
            printf("请输入新书名：");
            scanf("%s", temp->book.name);
            printf("请输入新作者：");
            scanf("%s", temp->book.writer);
            printf("请输入新出版社：");
            scanf("%s", temp->book.press);
            printf("请输入新出版年份：");
            scanf("%s", temp->book.year);
            printf("请输入新库存数量：");
            scanf("%d", &(temp->book.inventory));

            printf("图书更新成功！\n");
        }
        break;
    case 3:

        break;
    }
}

// 管理员图书信息显示
void Root_PrintBookList(LinkList head)
{
    system("cls");
    Link_Print(head);
}

// 管理员添加新用户
void Root_AddUser(UserList UserHead)
{
    char ID[10];       // ID
    char password[18]; // 密码

    printf("请输入新用户ID:");
    scanf("%s", ID);
    printf("请输入新用户密码：");
    scanf("%s", password);

    User *new = User_NodeCreate(ID, password);
    User_ListInsert(UserHead, new);
    printf("用户创建成功！\n");
}

// 管理员删除用户
void Root_UserDelet(UserList UserHead)
{
    printf("输入要删除用户的ID：");
    char ID[10];
    scanf("%s", ID);

    User *temp = User_ListIDDelete(UserHead, ID);

    if (temp != NULL)
    {
        printf("已删除ID为 %s 的用户\n", ID);
        User_FreeUserNode(temp);
    }
    else
    {
        printf("未找到ID为 %s 的用户\n", ID);
    }
}

// 管理员更新用户信息
void Root_UserChange(UserList UserHead)
{
    printf("输入要更新用户的ID：");
    char ID[10];
    scanf("%s", ID);

    User *temp = User_ListIDSearch(UserHead, ID);

    if (temp != NULL)
    {
        printf("设置新ID为：");
        scanf("%s", temp->ID);
        printf("设置新密码为：");
        scanf("%s", temp->password);
        printf("更新成功！");
    }
    else
    {
        printf("未找到ID为 %s 的用户\n", ID);
    }
}

// 打印用户列表
void Root_PrintUserList(UserList UserHead)
{
    printf("用户列表：\n");
    User_ListPrint(UserHead);
}

// 管理员模糊搜索
void Root_FuzzySearch(LinkList head)
{
    system("cls");
    printf("输入要查询的大致出版年份：");
    char year[20];
    scanf("%s", year);

    int pos = 1; // 位次
    int find_flag = 0;

    node *temp = Link_FuzzySearch(head, year, &pos);
    while (temp != NULL)
    {
        find_flag = 1;
        Link_NodePrint(temp);
        pos++;
        temp = Link_FuzzySearch(head, year, &pos);
    }

    if (find_flag == 0)
    {
        printf("图书库中未找到年份为 %s 的相关图书信息\n", year);
    }
}

//按借阅次数由高到底排序，并输出给出最受欢迎图书
void Root_BrrowTimeSort(LinkList head)
{
    node * temp = Link_CharBubbleSort(head);
    Root_PrintBookList(head);
    printf("最受欢迎图书为：\n");
    Link_NodePrint(temp);
}
