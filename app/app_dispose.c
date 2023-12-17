/**
  ******************************************************************************
  * @file    app_dispose.c
  * @version V1.0
  * @date    2023-12-10
  * @brief   �����app�����ص������û���ͨ���ļ�
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

#include "app_dispose.h"
/**
  * @brief  ��ȡһ��ѡ��,������������ֵ�ĵ�һ����
  * @param  ��
  * @retval �����ֵ�ĵ�һ���ַ�
  */
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
/**
  * @brief  ��¼������ʾ����,���һ�ȡ��Ҫ��¼���˵����
  * @param  ��
  * @retval ���'1'����'2'ҽ��'3'������
  */
int8_t app_welcome(void)
{
    int8_t choice;
    system("CLS");
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


/**
  * @brief  ���ĳһ�����Ƿ���Գɹ���½
  * @param  login_data:һ�������¼����Ϣ�Ľṹ��
  * @retval ��
  */
int8_t app_login(base_data *login_data)
{
    
    printf("����ѡ����: %c\r\n", login_data->identity);
    switch (login_data->identity)
    {
    case '1':
        if(app_patient_login(login_data)==1)
        {
            return 1;
        }
        break;
    case '2':
        if(app_doctor_login(login_data)==1)
        {
            return 1;
        }
        break;
    case '3':
        if(app_manage_login(login_data)==1){
            return 1;
        }
        break;
    default:
        printf("������������,����������!\r\n");
        return ERROR;
        break;
    }
    return ERROR;
}
/**
  * @brief  �ɹ���½�Ժ���������ݲ�ͬ��ѡ����벻ͬ��ִ�к���
  * @param  login_data:һ�������¼����Ϣ�Ľṹ��
  * @retval ��
  */
void app_successed_login(base_data *login_data)
{
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
/**
  * @brief  ���ڻ�ȡһ����¼������,������Ļ��ʾ*
  * @param password:����������ַ���
  * @retval ��
  */
void app_get_passwd(char *password)
{
    int i = 0; //��¼���볤��
    char c; //����ʵ��������ʽ����
    while (1) {
    c = _getch(); //�� _getch() �������룬�ַ�������ʾ����Ļ��
    if (c == '\r') { //�����س������������������
        password[i]=0;
        break; //while ѭ���ĳ���
    }
    else if (c == '\b') { //�����˸���Ҫɾ��ǰһ���Ǻ�
        printf("\b \b");  //�˸񣬴�һ���ո����˸�ʵ�������ÿո񸲸ǵ��Ǻ�
        --i;
    }
    else {
        password[i++] = c;//���ַ���������
        printf("*");     
    }
}
}