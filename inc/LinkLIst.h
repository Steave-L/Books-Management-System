#ifndef __LINKLIST_H
#define __LINKLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//图书结构体
typedef struct {
    char name[50];      //书名
    char writer[50];    //作者
    char press[50];     //出版社
    char year[20];           //出版年份
    int inventory;      //库存数量

    int BorrowTime;       //新增借阅频率
    char class[20];       //新增图书类别
}Book;

//双向循环链表存放图书数据
typedef struct node{
    Book book;
    int size;       //记录链表的节点数量，用于记录图书编号
    struct node *next;
    struct node *prev;
}node,*LinkList;

LinkList Link_Init(void);
bool Is_Empty(LinkList head);
node *Link_CreatNode(char *name,
                     char *writer,
                     char *press,
                     char *year,
                     int inventory,
                     int BorrowTime,
                     char *class);
void Link_HeadInsert(LinkList head, node *new);

node *Link_PosDelete(LinkList head, int pos);
node *Link_PosSearch(LinkList head,int pos);
node *Link_CharSearch(LinkList head,char *str , int *pos);
node *Link_NumSearch(LinkList head,int num, int *pos);

void Link_NodePrint(node *node);
void Link_Print(LinkList head);
void Link_Destroy(LinkList head);
void File_Save(LinkList head);
void File_Read(LinkList head);

node *Link_FuzzySearch(LinkList head, char *year, int *pos);    //新增的年份模糊搜索
node *Link_CharBubbleSort(LinkList head);                        //新增对链表的排序(拓展)（按借阅次数从高到底排序）

#endif
