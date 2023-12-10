/**
  ******************************************************************************
  * @file    app_main.c
  * @version V1.0
  * @date    2023-12-10
  * @brief   �����app���������ļ�,��һ����ѭ��, ������platform_init, platform_out
  * @author  XvSenfeng(������)
  ******************************************************************************
  * @attention
  * ��������XvSenfeng��������ѿ�Դ����
  * ���������鿴��ʹ�ú��޸ģ���Ӧ�õ��Լ�����Ŀ֮��
  * �����Ȩ��XvSenfeng���У��κ��˻���֯���ý����Ϊ����
  * ����㷢�ֳ����е�©�����߱��󣬿�ͨ���ʼ������Ƿ�����1458612070@qq.com
  * �����ʼ�֮ǰ��������ȵ����¶�̬ҳ��鿴���³�������������Ѿ��޸ģ��������ٷ��ʼ�
  * https://github.com/XuSenfeng
  ******************************************************************************
  */ 

#include "app_main.h"

int main(void)
{
    base_data login_data;
    //ƽ̨��ʼ��
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
    //ƽ̨�˳�����
    printf("�˳�\r\n");
    platform_out();
    system("pause");
    return 0;
}