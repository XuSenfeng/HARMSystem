#include "app_dispose.h"
#include <stdio.h>

int8_t app_get_choice()
{
    int8_t choice;
    fflush(stdin);
    //获取第一个不是空格的字符
    while(1){
        scanf("%1c", &choice);
        if(choice != ' ')
            break;
    }
    fflush(stdin);
    return choice;
}

//登录界面显示函数
int8_t app_welcome(void)
{
    int8_t choice;
    printf("*****************************************************************\r\n");
    printf("*                       欢迎使用医院管理系统                    *\r\n");
    printf("*                                         author:XvSenfeng      *\r\n");
    printf("*                                          data:2023-12-7       *\r\n");
    printf("*                               web:https://github.com/XuSenfeng*\r\n");
    printf("*****************************************************************\r\n");
    printf("请选择您的身份:\r\n");
    printf("1. 患者(进行挂号)\r\n");
    printf("2. 医生\r\n");
    printf("3. 管理员\r\n");
    printf("0. 退出\r\n");
    printf("你的身份是: ");
    choice = app_get_choice();
    return choice;
}
//用户登录处理函数
int32_t app_patient_login()
{
    int8_t choice, num=3;
    int8_t id[21], passwd[31];
    int32_t ret;
    printf("请问您之前是否注册过用户?\r\n");
    printf("1.是的 2.没有\r\n");
    printf("您的选择是: ");
    choice = app_get_choice();
    if(choice == '1' )
    {
        while(1){
            //之前存在用户
            printf("请输入您的id: ");
            fflush(stdin);
            scanf("%s", id);
            printf("请输入您的密码:");
            fflush(stdin);
            scanf("%s", passwd);
            fflush(stdin);
            ret = platform_login(id, passwd, '1');
            if(ret == -1)
            {
                num--;
                printf("id或者密码错误, 请重新输入 %s %s\r\n", id, passwd);
                if(num==0)
                {
                    return -1;
                }
            }
            else
            {
                return 1;
            }
        }
    }else
    {
        //之前没有用户

    }
}
//医生的登录函数,成功的话返回1,否则返回0
int32_t app_doctor_login()
{
    int8_t choice, num=3;
    int8_t id[21], passwd[31];
    int32_t ret;
    while(1){
        //之前存在用户
        printf("请输入您的id: ");
        fflush(stdin);
        scanf("%s", id);
        printf("请输入您的密码:");
        fflush(stdin);
        scanf("%s", passwd);
        fflush(stdin);
        ret = platform_login(id, passwd, '2');
        if(ret == -1)
        {
            num--;
            printf("id或者密码错误, 请重新输入");
            if(num==0)
            {
                return -1;
            }
        }
        else
        {
            return 1;
        }
    }
}
int32_t app_manage_login()
{
    int8_t choice, num=3;
    int8_t id[21], passwd[31];
    int32_t ret;
    while(1){
        //之前存在用户
        printf("请输入您的id: ");
        fflush(stdin);
        scanf("%s", id);
        printf("请输入您的密码:");
        fflush(stdin);
        scanf("%s", passwd);
        fflush(stdin);
        ret = platform_login(id, passwd, '3');
        if(ret == -1)
        {
            num--;
            printf("id或者密码错误, 请重新输入");
            if(num==0)
            {
                return -1;
            }
        }
        else
        {
            return 1;
        }
    }
}
void app_login(int8_t choice)
{
    uint8_t ret;
    printf("您的选择是: %c\r\n", choice);
    switch (choice)
    {
    case '1':
        if(app_patient_login())
        {

        }
        break;
    case '2':
        if(app_doctor_login())
        {

        }
        break;
    case '3':
        if(app_manage_login()){

        }
        break;
    default:
    printf("您的输入有误,请重新输入!\r\n");
        break;
    }
}