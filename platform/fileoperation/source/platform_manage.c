#include "platform_manage.h"
extern manager_t manager;
//��ȡ��¼��Ϣ
void platform_get_manage_login_data(int8_t *message)
{
    sprintf(message, "�𾴵� %s ����/Ůʿ ��ӭʹ��\r\n", manager.login.name);
}

//������û���ƽ̨�ӿ�,�����������Ϣ
void platform_manage_commend(int8_t commend, char *id, char *message, void *parameter)
{

    switch (commend)
    {
    case 1:
        //��ȡ��¼��Ϣ
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