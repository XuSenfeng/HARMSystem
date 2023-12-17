/**
  ******************************************************************************
  * @file    app_dispose.c
  * @version V1.0
  * @date    2023-12-10
  * @brief   这个是app层次相关的三个用户的通用文件
  * @author  XvSenfeng(焦浩洋)
  ******************************************************************************
  * @attention
  * 本程序由XvSenfeng创建并免费开源共享
  * 你可以任意查看、使用和修改，并应用到自己的项目之中
  * 程序版权归XvSenfeng所有，任何人或组织不得将其据为己有
  * 如果你发现程序中的漏洞或者笔误，可通过邮件向我们反馈：1458612070@qq.com
  * 发送邮件之前，你可以先到更新动态页面查看最新程序，如果此问题已经修改，则无需再发邮件
  * https://github.com/XuSenfeng
  ******************************************************************************
  */ 

#include "app_dispose.h"
/**
  * @brief  获取一个选择,返回所有输入值的第一个数
  * @param  无
  * @retval 输入的值的第一个字符
  */
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
/**
  * @brief  登录界面显示函数,并且获取想要登录的人的身份
  * @param  无
  * @retval 身份'1'病人'2'医生'3'管理者
  */
int8_t app_welcome(void)
{
    int8_t choice;
    system("CLS");
    printf("*****************************************************************\r\n");
    printf("*                       欢迎使用医院管理系统                    *\r\n");
    printf("*                                         author:XvSenfeng      *\r\n");
    printf("*                                          date:2023-12-7       *\r\n");
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


/**
  * @brief  检测某一个人是否可以成功登陆
  * @param  login_data:一个保存登录的信息的结构体
  * @retval 无
  */
int8_t app_login(base_data *login_data)
{
    
    printf("您的选择是: %c\r\n", login_data->identity);
    switch (login_data->identity)
    {
    case '1':
        if(app_patient_login(login_data)==1)
        {
            return 1;
        }
        break;
    case '2':
        if(app_doctor_login(login_data)==1)
        {
            return 1;
        }
        break;
    case '3':
        if(app_manage_login(login_data)==1){
            return 1;
        }
        break;
    default:
        printf("您的输入有误,请重新输入!\r\n");
        return ERROR;
        break;
    }
    return ERROR;
}
/**
  * @brief  成功登陆以后在这里根据不同的选择进入不同的执行函数
  * @param  login_data:一个保存登录的信息的结构体
  * @retval 无
  */
void app_successed_login(base_data *login_data)
{
    switch (login_data->identity)
    {
    case '1':
        app_patient_dealwith(login_data);
        break;
    case '2':
        app_doctor_dealwith(login_data);
        break;
    case '3':
        app_manage_dealwith(login_data);
        break;  
    default:
        break;
    }
}
/**
  * @brief  用于获取一个登录的密码,会在屏幕显示*
  * @param password:保存密码的字符串
  * @retval 无
  */
void app_get_passwd(char *password)
{
    int i = 0; //记录密码长度
    char c; //用于实现密码隐式输入
    while (1) {
    c = _getch(); //用 _getch() 函数输入，字符不会显示在屏幕上
    if (c == '\r') { //遇到回车，表明密码输入结束
        password[i]=0;
        break; //while 循环的出口
    }
    else if (c == '\b') { //遇到退格，需要删除前一个星号
        printf("\b \b");  //退格，打一个空格，再退格，实质上是用空格覆盖掉星号
        --i;
    }
    else {
        password[i++] = c;//将字符放入数组
        printf("*");     
    }
}
}