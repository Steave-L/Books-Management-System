/*用户有关函数*/
#include "User.h"

/* 用户链表底层操作 */

// 用户链表初始化
UserList User_ListInit(void)
{
    UserList UserHead = (UserList)malloc(sizeof(User));
    if (UserHead == NULL)
    {
        printf("内存分配失败，用户列表头节点未创建");
        return NULL;
    }

    UserHead->next = UserHead;
    UserHead->prev = UserHead;

    // strcpy(UserHead->ID, ROOTID);
    // strcpy(UserHead->password, ROOTPASSWARD);    //将管理员密码保存到头节点（未用上，宏定义在root.h当中）
    UserHead->head = NULL; // 初始化时指向空，防止操作野指针，导致程序出问题不好排查

    return UserHead;
}

User *User_NodeCreate(char *ID, char *password)
{
    User *new = (User *)malloc(sizeof(User));
    if (new == NULL)
    {
        printf("内存分配失败，用户创建失败\n");
        return NULL;
    }

    // 对用户借阅书本链表初始化
    new->head = Link_Init();
    if (new->head == NULL)
    {
        free(new);
        return NULL;
    }

    strcpy(new->ID, ID);
    strcpy(new->password, password);
    return new;
}

// 用户链表插入(头插)
void User_ListInsert(UserList UserHead, User *new)
{
    if (new == NULL)
    {
        printf("new node is NULL!\n");
        return;
    }

    new->next = UserHead->next;
    new->prev = UserHead;

    UserHead->next->prev = new;
    UserHead->next = new;
}

// 判断用户链表是否为空
bool User_ListIsEmpty(UserList UserHead)
{
    return UserHead->next == UserHead;
}

// 查找用户ID
User *User_ListIDSearch(UserList UserHead, char *ID)
{
    if (User_ListIsEmpty(UserHead))
    {
        printf("UserList is empty!\n");
        return NULL;
    }

    User *temp = UserHead->next;
    int found_flag = 0;

    for (; temp != UserHead; temp = temp->next)
    {
        // 找到用户链表中用户账户ID相同的节点
        if (strcmp(ID, temp->ID) == 0)
        {
            found_flag = 1;
            break;
        }
    }

    if (found_flag == 0)
        temp = NULL;

    return temp;
}

// 根据ID剔除用户节点
User *User_ListIDDelete(UserList UserHead, char *ID)
{
    User *temp = User_ListIDSearch(UserHead, ID);
    if (temp != NULL)
    {
        // 将temp前后两节点链接，剔除temp节点
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;

        temp->next = temp;
        temp->prev = temp;
    }
    return temp;
}

// 用户节点销毁（主要是封装销毁用户借阅图书的链表）
void User_FreeUserNode(User *user)
{
    Link_Destroy(user->head);
    free(user);
}

// 循环打印用户列表
void User_ListPrint(UserList UserHead)
{
    if (User_ListIsEmpty(UserHead))
    {
        printf("Link list is empty!\n");
        return;
    }
    printf("\n====================================================\n");
    User *temp = UserHead->next;
    for (; temp != UserHead; temp = temp->next)
    {
        printf("---------------\n");
        printf("ID:       %s\n", temp->ID);
        printf("Passward: %s\n", temp->password);
        printf("---------------\n");
    }
    printf("\n====================================================\n");
}

// 销毁用户链表
void User_ListDestroy(UserList UserHead)
{
    User *temp = UserHead->next;
    while (temp != UserHead)
    {
        User *p = temp->next;
        Link_Destroy(temp->head);
        free(temp);
        temp = p;
    }
    free(UserHead);
}

// 用户链表的文件IO
// 保存用户信息到用户链表当中
void User_FileSave(UserList UserHead)
{
    FILE *fpw = fopen("./inc/User/User.txt", "w");
    User *temp = UserHead->prev;

    // //将头节点的数据也打印到文件当中（头节点存放的是管理员ID和密码）
    // fprintf(fpw, "%s %s\n", UserHead->ID, UserHead->password);

    for (; temp != UserHead; temp = temp->prev)
    {
        fprintf(fpw, "%s %s\n", temp->ID, temp->password);
    }

    fclose(fpw);
}

// 读取用户信息链表
void User_FileRead(UserList UserHead)
{
    FILE *fpr = fopen("./inc/User/User.txt", "r");
    if (fpr == NULL)
    {
        printf("Book.txt note found\n");
        return;
    }

    char ID[10];       // ID
    char password[18]; // 密码
    int read_flag = 0;
    // 从文件中读入数据到new节点当中
    while (fscanf(fpr, "%s %s", ID, password) == 2)
    {
        User *new = User_NodeCreate(ID, password);
        User_ListInsert(UserHead, new);
        read_flag = 1;
    }

    if (read_flag == 0)
    {
        printf("User.txt is empty!\n");
    }
    fclose(fpr);
}

// 保存用户借阅书籍的信息文件
void User_BorrowFileSave(User *user)
{
    char userfile[50];
    sprintf(userfile, "./inc/User/User_%s.txt", user->ID);
    FILE *fpw = fopen(userfile, "w");
    node *temp = user->head->prev;

    for (; temp != user->head; temp = temp->prev)
    {
        fprintf(fpw, "%s %s %s %s %d %d %s\n", temp->book.name, temp->book.writer, temp->book.press,
                temp->book.year, temp->book.inventory, temp->book.BorrowTime, temp->book.class);
    }
    fclose(fpw);
}

// 读取用户借阅书籍的信息文件
void User_BorrowFileRead(User *user)
{
    char userfile[50];
    sprintf(userfile, "./inc/User/User_%s.txt", user->ID);
    FILE *fpr = fopen(userfile, "r");
    if (fpr == NULL)
    {
        printf("%s note found\n", userfile);
        return;
    }

    char name[50];   // 书名
    char writer[50]; // 作者
    char press[50];  // 出版社
    char year[20];   // 出版年份
    int inventory;

    int BorrowTime; // 新增借阅频率
    char class[20]; // 新增图书类别

    int read_flag = 0;
    // 从文件中读入数据到new节点当中
    while (fscanf(fpr, "%s %s %s %s %d %d %s", name, writer, press, year, &inventory,
                  &BorrowTime, class) == 7)
    {
        node *new = Link_CreatNode(name, writer, press, year, inventory, BorrowTime, class);
        Link_HeadInsert(user->head, new);
        read_flag = 1;
    }

    if (read_flag == 0)
    {
        printf("%s is empty\n", userfile);
    }
    fclose(fpr);
}

/*用户相关功能，面向对象相关函数*/

// 用户根据不同条件查询图书信息
void User_Search(LinkList head)
{
    system("cls");
    printf("\n=========================查询图书===================\n");
    printf("搜索（书名、作者、出版社、出版年份）***1\n");
    printf("搜索库存********************************2\n");
    printf("搜索大致年份****************************3\n");
    printf("退出************************************4\n");
    printf("\n====================================================\n");
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

    int pos = 1; // 位次
    int find_flag = 0;
    node *temp;

    switch (control)
    {
    case 1:
        /*查询函数重复使用*/
        system("cls");
        printf("输入要查询的书名、作者、出版社或者出版年份：");
        char str[50];
        scanf("%s", str);

        pos = 1; // 位次
        find_flag = 0;

        temp = Link_CharSearch(head, str, &pos);
        while (temp != NULL)
        {
            find_flag = 1;
            Link_NodePrint(temp);
            pos++;
            temp = Link_CharSearch(head, str, &pos);
        }

        if (find_flag == 0)
        {
            printf("图书库中未找到 %s 的相关图书信息\n", str);
        }

        break;

    case 2:
        system("cls");
        printf("输入要查询的库存数量：");
        int num;
        scanf("%d", &num);
        find_flag = 0;

        temp = Link_NumSearch(head, num, &pos);
        while (temp != NULL)
        {
            find_flag == 1;
            Link_NodePrint(temp);
            pos++;
            temp = Link_NumSearch(head, num, &pos);
        }

        if (find_flag == 0)
        {
            printf("图书库中未找到库存为 %d 的相关图书信息\n", num);
        }
        break;
    case 3:
        /*查询函数重复使用*/
        system("cls");
        printf("输入要查询的大致出版年份：");
        char year[20];
        scanf("%s", year);

        pos = 1; // 位次
        find_flag = 0;

        temp = Link_FuzzySearch(head, year, &pos);
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

        break;
    case 4:

        break;
    }
}

// 图书借阅
void User_Borrow(LinkList head, User *user)
{
    system("cls");
    printf("\n=======================借阅图书======================\n");
    printf("搜索借取书名****************************1\n");
    printf("搜索借取编号****************************2\n");
    printf("退出***********************************3\n");
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
    int pos = 1; // 因为书名唯一，pos只是用来传入函数参数

    switch (control)
    {
    case 1:
        system("cls");
        printf("输入借阅的图书的书名：");
        char str[50];
        scanf("%s", str);

        temp = Link_CharSearch(head, str, &pos);

        if (temp != NULL)
        {
            if (temp->book.inventory > 0)
            {
                temp->book.inventory--;  // 库存减一
                temp->book.BorrowTime++; // 借阅次数加一
                /* 记录用户信息 */
                // 将借阅的图书信息存入到用户节点当中
                node *new = Link_CreatNode(temp->book.name, temp->book.writer, temp->book.press,
                                           temp->book.year, 1, temp->book.BorrowTime, temp->book.class);
                // 用户借过的书库存为1

                // 查询是否已经借阅该图书，如果借阅过就再借阅一本，否则就插入新节点
                int pos = 1;
                node *p = Link_CharSearch(user->head, new->book.name, &pos);
                if (p == NULL)
                {
                    Link_HeadInsert(user->head, new);
                }
                else
                {
                    free(new); //!!!!!不插入时一定记得free，防止内存泄漏
                    p->book.inventory++;
                }
                printf("借阅图书成功！\n");
            }
            else
            {
                printf("%s 库存不足，借阅图书失败！\n", str);
            }
        }
        else
        {
            printf("图书库中未找到 %s", str);
        }
        break;
    case 2:
        // system("cls");
        printf("要借阅的图书编号：");
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
        if (temp->book.inventory > 0)
        {
            temp->book.inventory--;
            temp->book.BorrowTime++; // 借阅次数加一
            /* 记录用户信息 */
            // 将借阅的图书信息存入到用户节点当中
            node *new = Link_CreatNode(temp->book.name, temp->book.writer,temp->book.press,
                                        temp->book.year, 1,temp->book.BorrowTime, temp->book.class);
            // 用户借过的书库存为1，借阅次数无意义

            // 查询是否已经借阅该图书，如果借阅过就再借阅一本，否则就插入新节点
            int pos = 1;
            node *p = Link_CharSearch(user->head, new->book.name, &pos);
            if (p == NULL)
            {
                Link_HeadInsert(user->head, new);
            }
            else
            {
                free(new); //!!!!!不插入时一定记得free，防止内存泄漏
                p->book.inventory++;
            }

            printf("借阅图书成功！\n");
        }
        else
        {
            printf("%s 库存不足，借阅图书失败！\n", temp->book.name);
        }

        break;
    case 3:

        break;
    }
}

// 图书归还
void User_Return(LinkList head, User *user)
{
    // User_PrintBook(user);
    system("cls");
    printf("\n=======================归还图书======================\n");
    printf("归还书名****************************1\n");
    printf("归还编号****************************2\n");
    printf("查询已借书**************************3\n");
    printf("退出********************************4\n");
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
    int pos;
    node *temp;

    switch (control)
    {
    case 1:
        printf("输入要归还的书名：");
        char name[50];
        scanf("%s", name);

        /*查询图书（与case2 类似，有优化合并的选项）*/
        pos = 1;
        temp = Link_CharSearch(user->head, name, &pos); // pos传回位次，可用来剔除要归还图书的节点
        // 当借过的图书中为找到输入的书名时：
        if (temp == NULL)
        {
            printf("未借阅 %s 一书\n", name);
        }
        else
        {
            int Inpos = 1;
            node *InBookList = Link_CharSearch(head, temp->book.name, &Inpos);
            if (InBookList == NULL)
            {
                printf("图书库中未录用 %s 一书\n", temp->book.name);
            }
            else
            {
                InBookList->book.inventory++;
                temp->book.inventory--;

                printf("%s 归还成功！\n", temp->book.name);
                // 当借的书为0时，剔除节点
                if (temp->book.inventory == 0)
                {
                    /*剔除节点*/
                    // 按位次删除节点
                    free(Link_PosDelete(user->head, pos));
                }
            }
        }

        break;

    case 2:
        printf("输入要归还的书编号：");
        int num;
        while (1)
        {
            if (scanf("%d", &num) != 1 || num < 1 || num > user->head->size)
            {
                while (getchar() != '\n')
                    ;
                printf("编号输入有误，请重新输入：");
                continue;
            }
            break;
        }
        /*查询图书*/

        temp = Link_PosSearch(user->head, num);
        // 当temp为NULL时，未借阅此书
        if (temp == NULL)
        {
            printf("未借阅编号为 %d 一书\n", num);
        }
        else
        {
            int Inpos = 1;
            node *InBookList = Link_CharSearch(head, temp->book.name, &Inpos);

            // InBookList为NULL时，图书库中未找到该书
            if (InBookList == NULL)
            {
                printf("图书库中未录用 %s 一书\n", temp->book.name);
            }
            else
            {
                // 图书库找到时，库存加一，借阅书数量减一
                InBookList->book.inventory++;
                temp->book.inventory--;

                printf("%s 归还成功！\n", temp->book.name);
                // 当借的书为0时，剔除节点
                if (temp->book.inventory == 0)
                {
                    /*剔除节点*/
                    // 按位次删除节点
                    free(Link_PosDelete(user->head, num));
                }
            }

            break;
        }

        break;
    case 3:
        User_PrintBorrowBook(user);
        break;
    case 4:
        break;
    }
}

// 用户信息打印（借过的图书）
void User_PrintBorrowBook(User *user)
{
    system("cls");
    printf("ID: %s 借阅的图书:\n", user->ID);
    Link_Print(user->head);
}
