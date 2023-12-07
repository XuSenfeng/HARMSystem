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
    printf("��������: ");
    choice = app_get_choice();
    return choice;
}
//��¼������
void app_patient_login()
{
    int8_t choice, num=3;
    int8_t id[21], passwd[31];
    patient_t* patient = 0;
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
            patient = (patient_t *)platform_login(id, passwd, '1');
            if(patient == -1)
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
                printf("�յ���%s %s %s\r\n", patient->login.id, patient->login.name, patient->login.passwd);
                return patient;
            }
        }
    }else
    {
        //֮ǰû���û�

    }
}

void app_doctor_login()
{
    int8_t choice, num=3;
    int8_t id[21], passwd[31];
    doctor_t* doctor;
    while(1){
        //֮ǰ�����û�
        printf("����������id: ");
        fflush(stdin);
        scanf("%s", id);
        printf("��������������:");
        fflush(stdin);
        scanf("%s", passwd);
        fflush(stdin);
        doctor = (patient_t *)platform_login(id, passwd, '2');
        if(doctor == -1)
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
            printf("�յ���%s %s %s\r\n", doctor->login.id, doctor->login.name, doctor->login.passwd);
            return doctor;
        }
    }
}
void app_manage_login()
{

}
void app_login(int8_t choice)
{
    uint8_t ret;
    printf("����ѡ����: %c\r\n", choice);
    switch (choice)
    {
    case '1':
        app_patient_login();
        break;
    case '2':
        app_doctor_login();
        break;
    case '3':
        app_manage_login();
        break;
    default:
    printf("������������,����������!\r\n");
        break;
    }
}