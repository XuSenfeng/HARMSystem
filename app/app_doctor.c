/**
  ******************************************************************************
  * @file    app_doctor.c
  * @version V1.0
  * @date    2023-12-10
  * @brief   ����ļ���app��ε�ҽ����صĲ���platform_login, platform_doctor_commend
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

#include "app_doctor.h"
/**
  * @brief  ҽ���ĵ�¼����,�ɹ��Ļ�����1,���򷵻�0
  * @param  login_data:һ�������¼����Ϣ�Ľṹ��
  * @retval 1�ɹ���¼-1��¼ʧ��
  */
int32_t app_doctor_login(base_data *login_data)
{
    int8_t choice, num=3;
    int32_t ret;
    while(1){
        //֮ǰ�����û�
        printf("����������id: ");
        fflush(stdin);
        scanf("%s", login_data->id);
        printf("��������������:");
        fflush(stdin);
        app_get_passwd(login_data->passwd);
        fflush(stdin);
        ret = platform_login(login_data->id, login_data->passwd, '2');
        if(ret == ERROR)
        {
            num--;
            printf("\r\nid�����������, ����������\r\n");
            if(num==0)
            {
                return ERROR;
            }
        }
        else
        {
            return 1;
        }
    }
}
/**
  * @brief  ҽ����ȡ�Լ��Ĳ��˵���Ϣ
  * @param  login_data:һ�������¼����Ϣ�Ľṹ��
  * @param  message:���淵����Ϣ�Ľṹ��
  * @retval ��
  */
void app_doctor_get_pat_msg(base_data *login_data, int8_t *message)
{
    int32_t n;
    int8_t choice, times, left;
    int8_t page_s;
    int32_t parameter[3], i;
    platform_doctor_commend(COMMEND_DOC_GET_PAT_NUM, login_data->id, 0, &n);
    system("CLS");
    printf("һ���� %d ������\r\n", n);

    times = n/MESSAGE_STEP;
    left = n%MESSAGE_STEP;
    for(i=0;i<=times;i++){
        //ѭ����ӡÿһ������
        parameter[0] = i*MESSAGE_STEP;
        if(i==times)
        {
            if(left != 0){
                parameter[1] = left;
            }else
                break;
        }else
            parameter[1] = MESSAGE_STEP;
        
        platform_doctor_commend(COMMEND_DOC_GET_PAT_DTA_D, login_data->id, message, parameter);
        printf(message);
        printf("\r\n ����u���Ϸ�ҳ \r\n");
        page_s = getch();
        if(page_s=='u')
            i-=2;
        if(i<-1)
            i=-1;
    }
    system("pause");
}
/**
  * @brief  ҽ�����Լ��Ĳ��˽������ƴ���
  * @param  login_data:һ�������¼����Ϣ�Ľṹ��
  * @param  message:���淵����Ϣ�Ľṹ��
  * @retval ��
  */
void app_doctor_deal_pat(base_data *login_data, int8_t *message)
{
    int8_t choice[2];
    int8_t msg_to_pat[100];
    system("CLS");
    printf("��������������ԤԼ�Ĳ��˽��д���....\r\n");
    platform_doctor_commend(COMMEND_DOC_GET_FIRST_PAT, login_data->id, message, 0);
    printf(message);
    printf("����ȷ���Ƿ�Ҫ������������\r\n");
    printf("1. ��������,��Ҫ��һ������\r\n");
    printf("2. ���ƽ���,���˲���Ҫ��һ������\r\n");
    printf("3. ��������������,����ȥ��ĵط�����\r\n");
    printf("4. ��ʱ�Ȳ���������\r\n");
    printf("����������ѡ��: ");
    choice[0] = app_get_choice();
    printf("�����Ƿ���Ҫ������׷����Ϣ?\r\n");
    printf("1. ȷ��\r\n");
    printf("2. ȡ��\r\n");
    printf("����������ѡ��: ");
    choice[1] = app_get_choice();
    if(choice[1] == '1')
    {
        //printf("\r\n�������Ϣ��������ز�Ҫ�пո�ͻ���!!!!!!!!\r\n");
        printf("���������봫�����Ϣ: ");
        scanf("%s", msg_to_pat);
        platform_doctor_commend(COMMEND_DOC_ADD_PAT_MSG, login_data->id, message, msg_to_pat);
        printf(message); 
    }
    switch (choice[0])
    {
    case '1':
        //���Ĳ��˵�״̬,��������Ϣ������
        platform_doctor_commend(COMMEND_DOC_DEAL_FST_PAT, login_data->id, message, choice);
        printf(message);
        break;
    case '2':
        //����Ȭ��
        platform_doctor_commend(COMMEND_DOC_DEAL_FST_PAT, login_data->id, message, choice);
        printf(message);

        break;   
    case '3':
        //�벡������
        platform_doctor_commend(COMMEND_DOC_DEAL_FST_PAT, login_data->id, message, choice);
        printf(message); 
        break;
    case '4':
        //��������
        break;
    default:
        break;
    }
    system("pause");
}
/**
  * @brief  ҽ�����ܵĴ�����
  * @param  login_data:һ�������¼����Ϣ�Ľṹ��
  * @retval ��
  */
void app_doctor_dealwith(base_data *login_data)
{
    system("CLS");
    int8_t choice;
    int8_t data[1024] = {0};
    //printf("ҽ��id %s ", login_data->id);
    platform_doctor_commend(COMMEND_DOC_GET_SELF_DATA, login_data->id, data, 0);
    printf("%s", data);

    while(1){

        printf("********************************************\r\n");
        printf("*                                          *\r\n");
        printf("*            ��ѡ������Ҫ�ķ���            *\r\n");
        printf("*                                          *\r\n");
        printf("********************************************\r\n");
        printf("1. ��ȡ��ǰ���������в���\r\n");
        printf("2. �Բ��˽�������\r\n");
        printf("3. �ٴλ�ȡ��¼ʱ�����Ϣ�ܽ�\r\n");
        printf("0. �˳�\r\n");
        printf("����ѡ����: ");
        choice = app_get_choice();
        switch (choice)
        {
        case '1':
            app_doctor_get_pat_msg(login_data, data);
            break;
        case '2':
            app_doctor_deal_pat(login_data, data);
            break;      
        case '3':
            platform_doctor_commend(COMMEND_DOC_GET_SELF_DATA, login_data->id, data, 0);
            printf("%s", data);
            system("pause");
            system("CLS");
        default:
            break;
        }

        system("CLS");
        if(choice == '0')
            break;
    }
    system("CLS");
    printf("");
}