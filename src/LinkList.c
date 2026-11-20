/*链表底层操作函数*/

#include "LinkLIst.h"

// 图书链表初始化
LinkList Link_Init(void)
{
    LinkList head = (LinkList)malloc(sizeof(node));
    if (head == NULL)
    {
        printf("内存分配失败！，链表未创建。\n");
        return NULL;
    }

    head->next = head;
    head->prev = head;
    head->size = 0;
    return head;
}

// 判断链表是否为空
bool Is_Empty(LinkList head)
{
    return head->next == head;
}

// 创建一个新的图书节点
node *Link_CreatNode(char *name,
                     char *writer,
                     char *press,
                     char *year,
                     int inventory,
                     int BorrowTime,
                     char *class)
{
    node *new = (node *)malloc(sizeof(node));

    if (new == NULL)
    {
        printf("内存分配失败！,新节点未创建。\n");
        return NULL;
    }

    // 将新的图书节点赋传入的参数值
    strncpy(new->book.name, name, 50);
    strncpy(new->book.writer, writer, 50);
    strncpy(new->book.press, press, 50);
    strncpy(new->book.year, year, 20);
    new->book.inventory = inventory;

    new->book.BorrowTime = BorrowTime;
    strncpy(new->book.class, class, 20);

    return new;
}

// 添加图书节点(头插)
void Link_HeadInsert(LinkList head, node *new)
{
    if (new == NULL)
    {
        printf("new node is NULL!\n");
        return;
    }

    new->next = head->next;
    new->prev = head;

    head->next->prev = new;

    head->next = new;

    head->size++;
    // printf("节点添加成功!\n");
}

// 删除编号节点：
node *Link_PosDelete(LinkList head, int pos)
{
    if (pos < 1 || pos > head->size)
    {
        printf("编号输入有误！\n");
        return NULL;
    }

    node *temp = head->next;

    for (int i = 1; i < pos; i++)
    {
        temp = temp->next;
    }

    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;

    temp->next = temp;
    temp->prev = temp;

    head->size--;
    return temp;
}

/*查找函数*/
// 按位次链表查询信息（考虑能查询所有信息）
node *Link_PosSearch(LinkList head, int pos)
{
    // 与按位次删除类似
    if (pos < 1 || pos > head->size)
    {
        printf("位次输入有误！\n");
        return NULL;
    }

    node *temp = head->next;

    for (int i = 1; i < pos; i++)
    {
        temp = temp->next;
    }

    return temp;
}

// 按书名等字符串查找(多次查找)
///@param pos 查找开始节点的位次，指针类型，同时可以返回找到节点的位次
///@return 找到目标时返回相应节点，未找到时返回NULL
node *Link_CharSearch(LinkList head, char *str, int *pos)
{
    // 已经遍历完
    if (*pos < 1 || *pos > head->size)
    {
        return NULL;
    }

    node *temp = head->next;

    // 将temp移动到位次为*pos上
    for (int i = 1; i < *pos; i++)
        temp = temp->next;

    int find_flag = 0;
    // 循环将字符串与三个信息进行比较，如果相同就退出并返回temp
    for (; temp != head; temp = temp->next)
    {
        if (strcmp(temp->book.name, str) == 0)
        {
            find_flag = 1;
            break;
        }
        if (strcmp(temp->book.writer, str) == 0)
        {
            find_flag = 1;
            break;
        }
        if (strcmp(temp->book.press, str) == 0)
        {
            find_flag = 1;
            break;
        }
        if (strcmp(temp->book.year, str) == 0)
        {
            find_flag = 1;
            break;
        }
        // 未找到时位次加1，指向下一个节点
        (*pos)++;
    }

    // 未找到时返回NULL
    if (find_flag == 0)
        temp = NULL;

    return temp;
}

// 按库存数量整形数据查找(多次查找)
///@param pos 开始查找节点的位次，指针类型，同时可以返回找到节点的位次
///@return 找到目标时返回相应节点，未找到时返回NULL
node *Link_NumSearch(LinkList head, int num, int *pos)
{
    // 已经遍历完
    if (*pos < 1 || *pos > head->size)
    {
        return NULL;
    }

    node *temp = head->next;

    // 将temp移动到位次为*pos上
    for (int i = 1; i < *pos;)
        temp = temp->next;
    int find_flag = 0;

    // 循环将库存进行比较，如果相同就退出并返回temp
    for (; temp != head; temp = temp->next)
    {
        if (temp->book.inventory == num)
        {
            find_flag = 1;
            break;
        }

        // 未找到时位次加1，指向下一个节点
        (*pos)++;
    }

    // 未找到时返回NULL
    if (find_flag == 0)
        temp = NULL;

    return temp;
}

/*打印函数*/
// 打印单个节点信息
void Link_NodePrint(node *node)
{
    printf("---------------\n");
    printf("书名：      %s\n", node->book.name);
    printf("作者:       %s\n", node->book.writer);
    printf("出版社:     %s\n", node->book.press);
    printf("出版年份:   %s\n", node->book.year);
    printf("库存数量:   %d\n", node->book.inventory);

    printf("借阅次数:   %d\n", node->book.BorrowTime);
    printf("类别:       %s\n", node->book.class);
    printf("---------------\n");
}

// 遍历打印链表
void Link_Print(LinkList head)
{
    if (Is_Empty(head))
    {
        printf("Link list is empty!\n");
        return;
    }
    printf("\n====================================================\n");
    node *temp = head->next;
    int index = 1;
    for (; temp != head; temp = temp->next)
    {

        printf("图书编号:   %d\n", index);
        Link_NodePrint(temp);
        index++;
    }
    printf("\n====================================================\n");
}

// 销毁链表
void Link_Destroy(LinkList head)
{
    node *temp = head->next;

    while (temp != head)
    {
        node *p = temp->next;
        free(temp);
        temp = p;
    }
    free(head);
}

/*文件IO*/
// 保存文件
void File_Save(LinkList head)
{
    FILE *fpw = fopen("./inc/Book.txt", "w");
    node *temp = head->prev;
    for (; temp != head; temp = temp->prev)
    {
        fprintf(fpw, "%s %s %s %s %d %d %s\n", temp->book.name, temp->book.writer, temp->book.press,
                temp->book.year, temp->book.inventory, temp->book.BorrowTime, temp->book.class);
    }
    fclose(fpw);
}

// 读入文件
void File_Read(LinkList head)
{
    FILE *fpr = fopen("./inc/Book.txt", "r");
    if (fpr == NULL)
    {
        printf("Book.txt note found\n");
        return;
    }

    char name[50];   // 书名
    char writer[50]; // 作者
    char press[50];  // 出版社
    char year[20];   // 出版年份
    int inventory;
    int read_flag = 0;

    int BorrowTime; // 新增借阅频率
    char class[20]; // 新增图书类别
    // 从文件中读入数据到new节点当中
    while (fscanf(fpr, "%s %s %s %s %d %d %s", name, writer, press, year, &inventory,
                  &BorrowTime, class) == 7)
    {
        node *new = Link_CreatNode(name, writer, press, year, inventory, BorrowTime, class);
        Link_HeadInsert(head, new);
        read_flag = 1;
    }

    if (read_flag == 0)
    {
        printf("Book.txt is empty!\n");
    }
    fclose(fpr);
}

// 关于时间的模糊搜索（多次查找）：
///@param pos 查找开始节点的位次，指针类型，同时可以返回找到节点的位次
///@return 找到目标时返回相应节点，未找到时返回NULL
node *Link_FuzzySearch(LinkList head, char *year, int *pos)
{
    // 已经遍历完
    if (*pos < 1 || *pos > head->size)
    {
        return NULL;
    }

    node *temp = head->next;

    // 将temp移动到位次为*pos上
    for (int i = 1; i < *pos; i++)
        temp = temp->next;

    char s1[5];
    strncpy(s1, year, 4); // 用于记录输入的年份
    strtok(s1, ".");      // 并且在'.'的位置分隔，防止年份不是四位
    s1[4] = '\0';         // 末尾加上字符串终止符

    int find_flag = 0;
    // 循环将年份与大致年份比较，如果在范围区间就退出并返回temp
    for (; temp != head; temp = temp->next)
    {
        char s2[5]; // 用于记录节点的年份
        strncpy(s2, temp->book.year, 4);
        strtok(s2, "."); // 防止年份不是四位
        s2[4] = '\0';

        if (strcmp(s1, s2) == 0)
        {
            find_flag = 1;
            break;
        }
    }

    if (find_flag == 0)
    {
        temp = NULL;
    }
    return temp;
}

// 新增对链表的排序(拓展)（按借阅次数从高到底排序）
node *Link_CharBubbleSort(LinkList head)
{
    int swap_flag = 0;
    for (int i = 0; i < head->size; i++)
    {
        node *p = head->next;
        swap_flag = 0;
        for (int j = 0; j < head->size - i; j++)
        {
            if (p->book.BorrowTime < p->next->book.BorrowTime)
            {
                // 保存要交换节点
                node *NextNode = p->next;

                // 先更新相邻节点的链接
                p->next = NextNode->next;
                NextNode->prev = p->prev;

                // 更新相邻节点块前后节点连接
                p->prev->next = NextNode;
                NextNode->next->prev = p;

                // 最后交换相邻节点链接
                p->prev = NextNode;
                NextNode->next = p;

                swap_flag = 1;
                continue; // ！！！这里需要跳过下一行的p = p->next，
                          // 因为交换完后p已经到下一个节点位置
            }
            p = p->next; // 内存循环由p遍历
        }
        if (swap_flag == 0)
            break;
    }
    node *temp = head->next;
    return temp; // 返回最受欢迎图书
}

// //新增图书统计，报表的生成（拓展）
// void Link_Count(LinkList head)
// {
// }
