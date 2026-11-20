#ifndef __WELCOME_H
#define __WELCOME_H

#include "Root.h"

void Welcom_LoginInterface(UserList UserHead,LinkList head);
bool Welcom_NeedContinue(void);
bool Welcom_RootLogin(void);
User *Welcom_UserLogin(UserList UserHead);
void Welcom_UserCreate(UserList UserHead);
void Welcom_RootInterface(UserList UserHead,LinkList head);
void Welcom_UserInterface(User *user, LinkList head);

#endif
