#include "app_dispose.h"
#include <stdio.h>

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
    printf("*                                          data:2023-12-7       *\r\n");
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
//�û���¼������
int32_t app_patient_login()
{
    int8_t choice, num=3;
    int8_t id[21], passwd[31];
    int32_t ret;
    printf("������֮ǰ�Ƿ�ע����û�?\r\n");
    printf("1.�ǵ� 2.û��\r\n");
    printf("����ѡ����: ");
    choice = app_get_choice();
    if(choice == '1' )
    {
        while(1){
            //֮ǰ�����û�
            printf("����������id: ");
            fflush(stdin);
            scanf("%s", id);
            printf("��������������:");
            fflush(stdin);
            scanf("%s", passwd);
            fflush(stdin);
            ret = platform_login(id, passwd, '1');
            if(ret == -1)
            {
                num--;
                printf("id�����������, ���������� %s %s\r\n", id, passwd);
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
        //֮ǰû���û�

    }
}
//ҽ���ĵ�¼����,�ɹ��Ļ�����1,���򷵻�0
int32_t app_doctor_login()
{
    int8_t choice, num=3;
    int8_t id[21], passwd[31];
    int32_t ret;
    while(1){
        //֮ǰ�����û�
        printf("����������id: ");
        fflush(stdin);
        scanf("%s", id);
        printf("��������������:");
        fflush(stdin);
        scanf("%s", passwd);
        fflush(stdin);
        ret = platform_login(id, passwd, '2');
        if(ret == -1)
        {
            num--;
            printf("id�����������, ����������");
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
}
int32_t app_manage_login()
{
    int8_t choice, num=3;
    int8_t id[21], passwd[31];
    int32_t ret;
    while(1){
        //֮ǰ�����û�
        printf("����������id: ");
        fflush(stdin);
        scanf("%s", id);
        printf("��������������:");
        fflush(stdin);
        scanf("%s", passwd);
        fflush(stdin);
        ret = platform_login(id, passwd, '3');
        if(ret == -1)
        {
            num--;
            printf("id�����������, ����������");
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
}
void app_login(int8_t choice)
{
    uint8_t ret;
    printf("����ѡ����: %c\r\n", choice);
    switch (choice)
    {
    case '1':
        if(app_patient_login())
        {

        }
        break;
    case '2':
        if(app_doctor_login())
        {

        }
        break;
    case '3':
        if(app_manage_login()){

        }
        break;
    default:
    printf("������������,����������!\r\n");
        break;
    }
}