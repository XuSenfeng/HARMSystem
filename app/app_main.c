#include "app_main.h"
#include "platform_main.h"
#include <stdio.h>
int main(void)
{
    uint8_t choice;
    printf("main\r\n");
    //平台初始化
    platform_init();
    while(1)
    {
        choice = app_welcome();
        if(choice != '0'){
            app_login(choice);
            
        }else
        {
            break;
        }
    }
    //平台退出函数
    platform_out();
    return 0;
}