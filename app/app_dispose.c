#include "app_dispose.h"

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



void app_login(base_data *login_data)
{
    
    printf("您的选择是: %c\r\n", login_data->identity);
    switch (login_data->identity)
    {
    case '1':
        if(app_patient_login(login_data))
        {

        }
        break;
    case '2':
        if(app_doctor_login(login_data))
        {

        }
        break;
    case '3':
        if(app_manage_login(login_data)){

        }
        break;
    default:
    printf("您的输入有误,请重新输入!\r\n");
        break;
    }
}

void app_successed_login(base_data *login_data)
{
    printf("登录成功!!! %c\r\n", login_data->identity);
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

void app_get_passwd(char *password)
{
    int i = 0; //记录密码长度
    char c; //用于实现密码隐式输入
    while (1) {
    c = _getch(); //用 _getch() 函数输入，字符不会显示在屏幕上
    if (c == '\r') { //遇到回车，表明密码输入结束
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