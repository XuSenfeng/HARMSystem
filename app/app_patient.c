#include "app_patient.h"

//用户登录处理函数
int32_t app_patient_login(base_data *login_data)
{
    int8_t choice, num=3;

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
            scanf("%s", login_data->id);
            printf("请输入您的密码:");
            fflush(stdin);
            scanf("%s", login_data->passwd);
            fflush(stdin);
            ret = platform_login(login_data->id, login_data->passwd, '1');
            if(ret == -1)
            {
                num--;
                printf("id或者密码错误, 请重新输入 %s %s\r\n", login_data->id, login_data->passwd);
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

void app_patient_dealwith(base_data *login_data)
{
    //system("CLS");
    int8_t data[100];
    printf("您好, 用户\r\n");
    platform_get_login_data(login_data->identity, data,login_data->id);
    printf("获取到: %s", data);
    while(1);
}