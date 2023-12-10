/**
  ******************************************************************************
  * @file    app_main.c
  * @version V1.0
  * @date    2023-12-10
  * @brief   这个是app的主函数文件,是一个死循环, 调用了platform_init, platform_out
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
            if(app_login(&login_data) == 1)
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