#ifndef __ROOT_H
#define __ROOT_H

#define ROOTID "root"
#define ROOTPASSWARD "root"

#include "LinkLIst.h"
#include "User.h"

void Root_AddBook(LinkList head);
void Root_DeleteBook(LinkList head);
void Root_ChangeInformation(LinkList head);
void Root_PrintBookList(LinkList head);

void Root_AddUser(UserList UserHead);
void Root_UserDelet(UserList UserHead);
void Root_UserChange(UserList UserHead);
void Root_PrintUserList(UserList UserHead);

void Root_FuzzySearch(LinkList head);
void Root_BrrowTimeSort(LinkList head);

#endif
