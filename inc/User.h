#ifndef __USER_H
#define __USER_H

#include "LinkList.h"

//用户信息链表
typedef struct User{
    LinkList head;  //借过的图书链表
    char ID[10];    //ID
    char password[18];  //密码
    struct User* next;
    struct User* prev;
}User,*UserList;

UserList User_ListInit(void);
User *User_NodeCreate(char *ID,char *password);
void User_ListInsert(UserList UserHead,User *new);
bool User_ListIsEmpty(UserList UserHead);
User *User_ListIDSearch(UserList UserHead,char *ID);
User *User_ListIDDelete(UserList UserHead,char *ID);
void User_FreeUserNode(User *user);

void User_ListDestroy(UserList UserHead);
void User_FileSave(UserList UserHead);
void User_FileRead(UserList UserHead);
void User_BorrowFileSave(User *user);
void User_BorrowFileRead(User *user);
void User_ListPrint(UserList UserHead);

void User_Search(LinkList head);
void User_Borrow(LinkList head,User *user);
void User_Return(LinkList head, User *user);
void User_PrintBorrowBook(User *user);

#endif
