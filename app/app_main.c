#include "app_main.h"

int main(void)
{
    base_data login_data;
    //平台初始化
    platform_init();
    while(1)
    {
        login_data.identity = app_welcome();
        if(login_data.identity != '0'){
            if(app_login(&login_data)==1)
            {
                app_successed_login(&login_data);
            }
            
        }else
        {
            break;
        }
    }
    //平台退出函数
    printf("退出\r\n");
    platform_out();
    system("pause");
    return 0;
}