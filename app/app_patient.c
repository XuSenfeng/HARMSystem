/**
  ******************************************************************************
  * @file    app_patient.c
  * @version V1.0
  * @date    2023-12-10
  * @brief   �������ز��˵Ĳ���,��Ҫ�����ƽ̨��platform_login, platform_patient_commend����
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

#include "app_patient.h"


/**
  * @brief  �û���¼������
  * @param  login_data:һ�������Լ���¼����Ϣ�Ľṹ��
  * @retval ��¼�Ƿ�ɹ�, 1�ɹ�, -1ʧ��
  */
int32_t app_patient_login(base_data *login_data)
{
    int8_t choice, num=3;
    int32_t ret;
    int8_t message[200];
    int8_t parameter[3][30];
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
            scanf("%s", login_data->id);
            printf("��������������:");
            fflush(stdin);
            app_get_passwd(login_data->passwd);
            fflush(stdin);
            ret = platform_login(login_data->id, login_data->passwd, '1');
            if(ret ==ERROR)
            {
                num--;
                printf("\r\nid�����������, ���������� %s %s\r\n", login_data->id, login_data->passwd);
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
    }else if(choice == '2')
    {
        //֮ǰû���û�
        printf("*******************\r\n");
        printf("*    �û�ע��     *\r\n");
        printf("*******************\r\n");
        printf("������������ʵ����: \r\n");
        fflush(stdin);
        scanf("%s", parameter[0]);
        fflush(stdin);
        printf("��������������: ");
        app_get_passwd(parameter[1]);
        //printf("�����������: %s\r\n", parameter[1]);
        //��������
        login_data->id[0] = 0;
        platform_patient_commend(COMMEND_PAT_APLY_NEW_PAT, login_data->id, message, parameter);
        printf(message);
        system("pause");
        system("cls");
        return 1;
    }else
    {
        printf("\r\n�������󷵻���һ��\r\n");
        system("pause");
        system("cls");
    }
}



/**
  * @brief  ���ýӿڻ�ȡ����ʾĳ��ʱ���ҽ����Ϣ
  * @param  login_data:һ�������Լ���¼����Ϣ�Ľṹ��
  * @param  data:�����ݴ�����
  * @param  choice:ɸѡģʽ, 0����, 1���ղ���, 2���տ��ԽӴ�
  * @retval ��
  */
void app_patient_get_doc_msg_tim(base_data *login_data, int8_t *data, int32_t choice_n)
{
    int8_t choice, times, left;
    int8_t page_s;
    char parameter[50], i;
    parameter[49] = choice_n;
    int32_t num_page;

    printf("�������ѯ������һ��?\r\n");
    printf("����:0 ��һ:1 �ܶ�:2 ����:3 ����:4 ����:5 ����:6\r\n");
    printf("����ѡ����: ");
    scanf("%d", &parameter[0]);
    printf("�������ѯ�������绹������?\r\n");
    printf("1. ����\r\n");
    printf("2. ����\r\n");
    printf("����ѡ����: ");   
    scanf("%d", &parameter[1]);
    if(choice_n==1)
    {
        printf("�����������ѯ�Ĳ��ŵ�����: ");
        scanf("%s", &parameter[4]);
    }
    platform_patient_commend(COMMEND_PAT_GET_DOC_MSG_TIM_NUM, login_data->id, data, parameter);
    printf("һ���� %d ��ҽ��\r\n", parameter[2]);
    system("pause");
    //���ղ�ͬ��ְ��
    if(parameter[2]>0){
        times = parameter[2]/MESSAGE_STEP_L;
        left = parameter[2]%MESSAGE_STEP_L;
        parameter[2] = parameter[0]*2 + parameter[1]-1;
        for(i=0;i<=times;i++){
            system("CLS");
            parameter[0] = i*MESSAGE_STEP_L;
            if(i==times)
            {
                if(left != 0){
                    parameter[1] = left;
                }else
                    break;
            }else
                parameter[1] = MESSAGE_STEP_L;
            platform_patient_commend(COMMEND_PAT_GET_DOC_DTA_T, login_data->id, data, parameter);

            printf(data);
            printf("\r\n �� %d ҳ �� %d ҳ  ����u���Ϸ�ҳ p�˳� ��������n + ҳ����ת����Ӧҳ\r\n", i+1, times + 1);
            if(login_data->identity == '1')
                printf("���� c ����ֱ�Ӷ�ҽ������ԤԼ\r\n");
            page_s = getch();
            if(page_s=='u')
                i-=2;
            if(i<-1)
                i=-1;
            if(page_s=='p')
                break;
            if(page_s=='n'){
                scanf("%d", &num_page);
                if(num_page <= times+1 && num_page > 0){
                    i = num_page-2;
                }else
                    i--;
            }
            if(login_data->identity == '1')
                if(page_s=='c'){
                    app_patient_aply_doc(login_data, data);
                    fflush(stdin);
                }           
        }
    }else{
        printf("û�з�����������\r\n");
        system("pause");
    }
}

/**
  * @brief  ���ýӿڻ�ȡ����ʾ����ҽ������Ϣ
  * @param  login_data:һ�������Լ���¼����Ϣ�Ľṹ��
  * @retval ��
  */
void app_patient_get_doc_msg(base_data *login_data)
{
    int32_t num_data[3];
    int8_t choice, times, left;
    int8_t data[1024], page_s;
    int32_t parameter[3], i;
    int8_t doc_id[21];
    int32_t num_page;
    //��ȡ���е�ҽ��������
    platform_patient_commend(COMMEND_PAT_SET_DOC_NUM, login_data->id, 0, num_data);
    printf("һ���� %d ������, %d ��ҽ��\r\n", num_data[0], num_data[1]);
    system("pause");
    while(1){
        system("CLS");
        printf("��ѡ��ۿ�ģʽ\r\n");
        printf("1. ���ݲ�����ʾҽ��\r\n");
        printf("2. ����ְ����ʾ����ҽ��\r\n");
        printf("3. ��ʾĳһ��ҽ������ϸ��Ϣ(ͨ��id)\r\n");
        printf("4. ��ʾĳһ��ʱ��ε�����ҽ��\r\n");
        printf("5. ��ʾĳ�����ŵ���ĳ��ʱ����ϰ������ҽ��\r\n");
        printf("6. ��ʾĳ��ʱ����ϻ�����ԤԼ������ҽ��\r\n");
        printf("0. ����\r\n");
        printf("����������ѡ��: ");
        choice = app_get_choice();
        switch (choice)
        {
        case '1':
            //�����е���Ϣ�ֲ����λ�ȡ��ʾ
            times = num_data[2]/MESSAGE_STEP;
            left = num_data[2]%MESSAGE_STEP;
            for(i=0;i<=times;i++){
                //ѭ����ӡÿһ�����ŵ���Ϣ
                system("CLS");
                parameter[0] = i*MESSAGE_STEP;
                if(i==times)
                {
                    if(left != 0){
                        parameter[1] = left;
                    }else
                        break;
                }else
                    parameter[1] = MESSAGE_STEP;
                platform_patient_commend(COMMEND_PAT_GET_DOC_DTA_D, login_data->id, data, parameter);
                printf(data);
            printf("\r\n �� %d ҳ �� %d ҳ  ����u���Ϸ�ҳ p�˳� ��������n + ҳ��\r\n", i+1, times + 1);
                if(login_data->identity == '1')
                    printf("���� c ����ֱ�Ӷ�ҽ������ԤԼ\r\n");

                page_s = getch();
                //����Ƿ���Ҫ���˻�ȥ
                if(page_s=='u')
                    i-=2;
                if(i<-1)
                    i=-1; 
                if(page_s=='p')
                    break;
                if(page_s=='n'){
                    scanf("%d", &num_page);
                if(num_page <= times+1 && num_page > 0){
                    i = num_page-2;
                }else
                    i--;
                }
                if(login_data->identity == '1')
                    if(page_s=='c'){
                        app_patient_aply_doc(login_data, data);
                        fflush(stdin);
                    } 
            }
            break;
        case '2':
            //���ղ�ͬ��ְ��
            times = num_data[1]/MESSAGE_STEP_L;
            left = num_data[1]%MESSAGE_STEP_L;
            for(i=0;i<=times;i++){
                system("CLS");
                parameter[0] = i*MESSAGE_STEP_L;
                if(i==times)
                {
                    if(left != 0){
                        parameter[1] = left;
                    }else
                        break;
                }else
                    parameter[1] = MESSAGE_STEP_L;
                platform_patient_commend(COMMEND_PAT_GET_DOC_DTA_L, login_data->id, data, parameter);
                printf(data);
            printf("\r\n �� %d ҳ �� %d ҳ  ����u���Ϸ�ҳ p�˳� ��������n + ҳ��\r\n", i+1, times + 1);
            if(login_data->identity == '1')
            printf("���� c ����ֱ�Ӷ�ҽ������ԤԼ\r\n");

                page_s = getch();
                if(page_s=='u')
                    i-=2;
                if(i<-1)
                    i=-1;
                if(page_s=='p')
                    break;
                if(page_s=='n'){
                    scanf("%d", &num_page);
                if(num_page <= times+1 && num_page > 0){
                    i = num_page-2;
                }else
                    i--;
                }
                if(login_data->identity == '1')
                    if(page_s=='c'){
                        app_patient_aply_doc(login_data, data);
                        fflush(stdin);
                    }
            }
            break;
        case '3':
            printf("�����������ȡ��ҽ����id: ");
            scanf("%s", doc_id);
            platform_patient_commend(COMMEND_PAT_GET_DOC_MSG_id, login_data->id, data, doc_id);
            printf(data);
            system("pause");
            break;
        case '4':
            app_patient_get_doc_msg_tim(login_data, data, 0);
            break;
        case '5':
            app_patient_get_doc_msg_tim(login_data, data, 1);
            break;
        case '6':
            app_patient_get_doc_msg_tim(login_data, data, 2);
            break;
        default:
            return;
            break;
        }
    }
}
/**
  * @brief  ����3: ��ʾ�Լ���״̬
  * @param  login_data:һ�������Լ���¼����Ϣ�Ľṹ��
  * @param  message:һ�����淵����Ϣ���ַ���
  * @retval ��
  */
void app_patient_show_self(base_data *login_data, int8_t *message)
{
    platform_patient_commend(COMMEND_PAT_GET_SELF_DATA, login_data->id, message, 0);
    printf("%s", message);
    system("pause");
}
/**
  * @brief  ����2: ���ݲ��������id����һ��ҽ����ԤԼ
  * @param  login_data:һ�������Լ���¼����Ϣ�Ľṹ��
  * @param  message:һ�����淵����Ϣ���ַ���
  * @retval ��
  */
void app_patient_aply_doc(base_data *login_data, int8_t *message)
{
    int8_t doc_id[21];
    printf("����������ԤԼ��ҽ����id: ");
    scanf("%s", doc_id);
    platform_patient_commend(COMMEND_PAT_APP_DOC, login_data->id, message, doc_id);
    printf(message);
    system("pause");
}


/**
  * @brief  ������Ҫ�Ĵ�����
  * @param  login_data:һ�������Լ���¼����Ϣ�Ľṹ��
  * @retval ��
  */
void app_patient_dealwith(base_data *login_data)
{
    system("CLS");
    int8_t choice;
    int8_t data[1024] = {0};
    platform_patient_commend(COMMEND_PAT_GET_SELF_DATA, login_data->id, data);
    printf("%s", data);

    while(1){

        printf("********************************************\r\n");
        printf("*                                          *\r\n");
        printf("*            ��ѡ������Ҫ�ķ���            *\r\n");
        printf("*                                          *\r\n");
        printf("********************************************\r\n");
        printf("1. ��ȡ��ǰҽ������Ϣ\r\n");
        printf("2. ����ĳһ��ҽ����ԤԼ\r\n");
        printf("3. �ٴ���ʾ��ǰ״̬\r\n");
        printf("4. ȡ��ԤԼ\r\n");
        printf("0. �˳�\r\n");
        printf("����ѡ����: ");
        choice = app_get_choice();
        switch (choice)
        {
        case '1':
            app_patient_get_doc_msg(login_data);
            break;
        case '2':
            app_patient_aply_doc(login_data, data);
            break;      
        case '3':
            app_patient_show_self(login_data, data);
            break;
        case '4':
            platform_patient_commend(COMMEND_PAT_DEL_DOC_APLY, login_data->id, data, 0);
            printf(data);
            system("pause");
            break;
        default:
            break;
        }

        system("CLS");
        if(choice == '0')
            break;
    }
}