#include "app_main.h"
#include "platform_main.h"
#include <stdio.h>
int main(void)
{
    uint8_t choice;
    printf("main\r\n");
    //ƽ̨��ʼ��
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
    //ƽ̨�˳�����
    platform_out();
    return 0;
}