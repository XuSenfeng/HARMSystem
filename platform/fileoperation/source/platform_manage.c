#include "platform_manage.h"
extern manager_t manager;
//获取登录信息
void platform_get_manage_login_data(int8_t *message)
{
    sprintf(message, "尊敬的 %s 先生/女士 欢迎使用\r\n", manager.login.name);
}

//这个是用户的平台接口,根据命令返回信息
void platform_manage_commend(int8_t commend, char *id, char *message, void *parameter)
{

    switch (commend)
    {
    case 1:
        //获取登录信息
        platform_get_manage_login_data(message);
        break;
    case 2:

        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        break;
    default:
        break;
    }
}