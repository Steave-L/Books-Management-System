#include "LinkList.h"
#include "Root.h"
#include "Welcome.h"

int main()
{
    system("chcp 65001 > nul"); // 将终端代码页切换到 UTF-8

    LinkList head = Link_Init();        //初始化图书库链表头节点和用户链表头节点
    UserList UserHead = User_ListInit();

    if (head == NULL || UserHead == NULL)
    {
        free(head);
        free(UserHead);
        printf("链表为NULL！程序退出。\n");
        return 0;
    }

    File_Read(head);            //从文件中读入记录的图书库链表和用户数据链表
    User_FileRead(UserHead);

    Welcom_LoginInterface(UserHead,head);   //进入登录主界面


    User_FileSave(UserHead);    //退出时更新用户数据链表和图书库链表
    File_Save(head);

    User_ListDestroy(UserHead); //销毁用户链表和图书链表
    Link_Destroy(head);

    return 0;
}