#include "app_dispose.h"

int8_t app_get_choice()
{
    int8_t choice;
    fflush(stdin);
    //��ȡ��һ�����ǿո���ַ�
    while(1){
        scanf("%1c", &choice);
        if(choice != ' ')
            break;
    }
    fflush(stdin);
    return choice;
}

//��¼������ʾ����
int8_t app_welcome(void)
{
    int8_t choice;
    printf("*****************************************************************\r\n");
    printf("*                       ��ӭʹ��ҽԺ����ϵͳ                    *\r\n");
    printf("*                                         author:XvSenfeng      *\r\n");
    printf("*                                          date:2023-12-7       *\r\n");
    printf("*                               web:https://github.com/XuSenfeng*\r\n");
    printf("*****************************************************************\r\n");
    printf("��ѡ���������:\r\n");
    printf("1. ����(���йҺ�)\r\n");
    printf("2. ҽ��\r\n");
    printf("3. ����Ա\r\n");
    printf("0. �˳�\r\n");
    printf("��������: ");
    choice = app_get_choice();
    return choice;
}



void app_login(base_data *login_data)
{
    
    printf("����ѡ����: %c\r\n", login_data->identity);
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
    printf("������������,����������!\r\n");
        break;
    }
}

void app_successed_login(base_data *login_data)
{
    printf("��¼�ɹ�!!! %c\r\n", login_data->identity);
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

