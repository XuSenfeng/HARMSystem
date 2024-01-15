/**
  ******************************************************************************
  * @file    platform_manage.c
  * @version V1.0
  * @date    2023-12-10
  * @brief   ����ǹ�������صĲ�����ʵ��, platform_login, platform_manage_commend����������
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

#include "app_manage.h"


/**
  * @brief  ҽ���ĵ�¼����
  * @param  login_data:һ�������¼����Ϣ�Ľṹ��
  * @retval ��
  */
int32_t app_manage_login(base_data *login_data)
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
        ret = platform_login(login_data->id, login_data->passwd, '3');
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
  * @brief  ��ʾ����ҽ������Ϣ,����ֱ��ʹ�ò����ļ������ʵ��
  * @param  login_data:һ�������¼����Ϣ�Ľṹ��
  * @retval ��
  */
void app_manage_get_doc_msg(base_data *login_data){
    app_patient_get_doc_msg(login_data);
}


/**
  * @brief  ����չʾ���еĲ�����Ϣ
  * @param  login_data:һ�������¼����Ϣ�Ľṹ��
  * @param  message:������Ϣʹ�õ��ַ���
  * @retval ��
  */
void app_manage_aply_pta_message(base_data *login_data, int8_t *message)
{
    int32_t n;
    int8_t choice, times, left;
    int8_t page_s;
    int32_t parameter[3], i;
        int32_t num_page;

    platform_manage_commend(COMMEND_MAN_GET_PAT_NUM, 0, &n);
    n -=1;
    system("CLS");
    printf("һ���� %d ������\r\n", n);
    times = n/MESSAGE_STEP;
    left = n%MESSAGE_STEP;
    for(i=0;i<=times;i++){
        //ѭ����ӡÿһ�����ŵ���Ϣ
        parameter[0] = i*MESSAGE_STEP;
        if(i==times)
        {
            if(left != 0){
                parameter[1] = left;
            }else
                break;
        }else
            parameter[1] = MESSAGE_STEP;

        platform_manage_commend(COMMEND_MAN_GET_PAT_DATA, message, parameter);
        printf(message);
        printf("\r\n �� %d ҳ �� %d ҳ  ����u���Ϸ�ҳ p�˳� ��������n + ҳ��\r\n", i+1, times + 1);
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
        system("CLS");
    }
}

/**
  * @brief  ɾ��ĳһ��ҽ��
  * @param  login_data:һ�������¼����Ϣ�Ľṹ��
  * @param  message:������Ϣʹ�õ��ַ���
  * @retval ��
  */
void app_manage_del_doctor(base_data *login_data, int8_t *message){
    int8_t doc_id[21], choice;
    system("CLS");
    printf("������������Ҫɾ����ĳһ��ҽ����id: ");
    scanf("%s", doc_id);
    printf("����ȷ����Ҫɾ����һλҽ��:\r\n");
    platform_manage_commend(COMMEND_MAN_GET_DOC_BY_id, message, doc_id);
    printf(message);
    if(doc_id[0]!=0)
    {
        printf("1. ȷ��\r\n");
        printf("2. ȡ��\r\n");
        choice = app_get_choice();
        if(choice == '1')
        {
            platform_manage_commend(COMMEND_MAN_DEL_DOC_BY_id, message, doc_id);
            printf(message);
            system("pause");
        }
    }else{
        system("pause");
    }

}
/**
  * @brief  �޸�ҽ������Ϣ
  * @param  login_data:һ�������¼����Ϣ�Ľṹ��
  * @param  message:������Ϣʹ�õ��ַ���
  * @retval ��
  */
void app_manage_amend_doctor(base_data *login_data, int8_t *message)
{
    //��Ϣ����1: id, 2:ѡ�� 3:���Ժ��ֵ
    int8_t doc_msg[3][31], choice;
    system("CLS");
    printf("����������Ҫ���ĵ�ҽ����id: ");
    scanf("%s", doc_msg[0]);
    printf("����ȷ����Ҫ�޸���һλҽ��:\r\n");
    platform_manage_commend(COMMEND_MAN_GET_DOC_BY_id, message, doc_msg[0]);
    printf(message);
    if(doc_msg[0][0]!=0)
    {
        printf("1. ȷ��\r\n");
        printf("2. ȡ��\r\n");
        printf("����������ѡ��: ");
        choice = app_get_choice();
        if(choice == '1')
        {
            printf("�����޸�ҽ������Ϣ����һ����?\r\n");
            printf("1. ����\r\n");
            printf("2. ְ��\r\n");
            printf("3. ��¼����\r\n");
            printf("4. ����\r\n");
            printf("����������ѡ��: ");
            doc_msg[1][0] = app_get_choice();
            if(choice == '1' && choice == '2' && choice == '3'){
                printf("�������޸��Ժ��ֵ: ");
                scanf("%s", doc_msg[2]);
            }else{
                printf("��ѡ����������ְ��\r\n");
                printf("1. %s\r\n", DOC_LEVE_1);
                printf("2. %s\r\n", DOC_LEVE_2);
                printf("3. %s\r\n", DOC_LEVE_3);
                printf("4. %s\r\n", DOC_LEVE_4);
                printf("5. %s\r\n", DOC_LEVE_5);
                printf("���������ѡ��: ");
                choice = app_get_choice();
                if(choice == '1')
                {
                    strcpy(doc_msg[2], DOC_LEVE_1);
                }else if(choice == '2')
                {
                    strcpy(doc_msg[2], DOC_LEVE_2); 
                }else if(choice == '3')
                {
                    strcpy(doc_msg[2], DOC_LEVE_3);
                }else if(choice == '4')
                {
                    strcpy(doc_msg[2], DOC_LEVE_4);
                }else if(choice == '5')
                {
                    strcpy(doc_msg[2], DOC_LEVE_5);
                }else {
                    printf("��������!!\r\n");
                    system("pause");
                    return;
                }
            }

            platform_manage_commend(COMMEND_MAN_CHG_DOC_BY_id, message, doc_msg);
            printf(message);
            system("pause");
        }
    }else{
        system("pause");
    }
}

/**
  * @brief  ͨ���ļ������Ϣ
  * @param  login_data:һ�������¼����Ϣ�Ľṹ��
  * @param  message:������Ϣʹ�õ��ַ���
  * @retval ��
  */
void app_manage_add_msg_file(base_data *login_data, int8_t *message)
{
    int8_t choice;
    int8_t name[50];
    system("CLS");
    printf("������һ���ļ����������Ϣ\r\n");
    printf("����ذ��ո������ļ���ʽ!!!!!!!!!\r\n");
    printf("����ذ�������ȷ��·��!!!!!!!!!\r\n");
    printf("�ļ���ʽ����\r\n");
    printf("**************************************************\r\n");
    printf("�������ŵĸ���(����)\r\n");
    printf("���Ÿ�������Ϣ: �������� ��������������� ���ո������벿������\r\n");
    printf("ҽ���ĸ���(����)\r\n");
    printf("ҽ����������Ϣ: ҽ����� ���� ��¼���� ���� ְ�� �Ӵ���������� ����ʱ�� �Ѿ��Ӵ��Ĳ����� ��ǰ�Ĺ���\r\n");
    printf("���˵ĸ���(����)\r\n");
    printf("���˸�������Ϣ: ���˱�� ���� ��¼���� ��ǰ״̬(0 û��ԤԼ 1 ԤԼδ���� 2 ����) ����ҽ����� ҽ����������Ϣ\r\n");
    printf("**************************************************\r\n");
    printf("1. ȷ��\r\n");
    printf("2. ȡ��\r\n");
    printf("����������ѡ��: ");
    choice = app_get_choice();
    if(choice == '1')
    {
        printf("\r\n�������ļ���: ");
        scanf("%s", name);
        platform_manage_commend(COMMEND_MAN_ADD_MSG_BY_FILE, message, name);
        printf(message);
        system("pause");
    }
    
}
/**
  * @brief  ���һ��ҽ��
  * @param  login_data:һ�������¼����Ϣ�Ľṹ��
  * @param  message:������Ϣʹ�õ��ַ���
  * @retval ��
  */
void app_manage_add_doctor(base_data *login_data, int8_t *message)
{
    int8_t choice;
    int8_t doc_msg[6][31];
    
    while(1){
        system("CLS");
        printf("������������һ��ҽ��\r\n");
        printf("�����������ȷ����Ϣ!!!\r\n");
        printf("1. ȷ��\r\n");
        printf("2. ȡ��\r\n");
        printf("����������ѡ��: ");
        choice = app_get_choice();
        if(choice == '1')
        {
            printf("������ҽ��������: ");
            scanf("%s", doc_msg[0]);
            printf("������ҽ���Ĳ���: ");
            scanf("%s", doc_msg[1]);
            printf("����ְ��: ֪��ר�� ����ҽʦ ������ҽʦ ����ҽʦ ҽʦ\r\n");
            printf("������ҽ����ְ��: ");
            scanf("%s", doc_msg[2]);
            printf("������ҽ��������: ");
            scanf("%s", doc_msg[3]);
            printf("������ҽ���Ĺ�����(ʮ��λ����һ�ܵ�������1.���� 0.��Ϣ): ");
            scanf("%s", doc_msg[4]);
            printf("������ҽ��������������: ");
            scanf("%d", &doc_msg[5][0]);
            printf("������ҽ�����νӴ��۸�: ");
            scanf("%d", &doc_msg[5][1]);   
            platform_manage_commend(COMMEND_MAN_ADD_NEW_DOC, message, doc_msg);
            printf(message);
            system("pause");
        }else
        {
            printf("�˳�\r\n");
            system("pause");
        }
        printf("�����Ƿ������� 1�� 0�˳�:");
        choice = app_get_choice();
        if(choice == '0')
            break;
    }
}
/**
  * @brief  ɾ��ĳһ������ͨ��id
  * @param  login_data:һ�������¼����Ϣ�Ľṹ��
  * @param  message:������Ϣʹ�õ��ַ���
  * @retval ��
  */
void app_manage_del_patient(base_data *login_data, int8_t *message)
{
    int8_t choice;
    int8_t pat_id[31];
    system("CLS");
    printf("���������ѡ����һ������\r\n");
    printf("1. ȷ��\r\n");
    printf("2. ȡ��\r\n");
    printf("����������ѡ��: ");
    choice = app_get_choice();
    if(choice == '1')
    {
        printf("����������Ҫ����ԤԼ��id: ");
        scanf("%s", pat_id);
        platform_manage_commend(COMMEND_MAN_GET_ONE_PAT, message, pat_id);
        printf(message);
        if(pat_id[0]!=0)
        {
            printf("1. ȷ��\r\n");
            printf("2. ȡ��\r\n");
            choice = app_get_choice();
            if(choice == '1')
            {
                platform_manage_commend(COMMEND_MAN_DEL_PAT_BY_id, message, pat_id);
                printf(message);
                system("pause");
            }
        }else{
            system("pause");
        }

    }else{
        printf("�˳�\r\n");
        system("pause");
    }
}
/**
  * @brief  �޸�ĳһ�����˵���Ϣ
  * @param  login_data:һ�������¼����Ϣ�Ľṹ��
  * @param  message:������Ϣʹ�õ��ַ���
  * @retval ��
  */
void app_manage_amend_pat(base_data *login_data, int8_t *message)
{
    //��Ϣ����1: id, 2:ѡ�� 3:���Ժ��ֵ
    int8_t pat_msg[3][31], choice;
    while(1){
        system("CLS");
        printf("����������Ҫ���ĵĲ��˵�id: ");
        scanf("%s", pat_msg[0]);
        printf("����ȷ����Ҫ�޸���һλ����:\r\n");
        platform_manage_commend(COMMEND_MAN_GET_ONE_PAT, message, pat_msg[0]);
        printf(message);
        if(pat_msg[0][0]!=0)
        {
            printf("1. ȷ��\r\n");
            printf("2. ȡ��\r\n");
            printf("����������ѡ��: ");
            choice = app_get_choice();
            if(choice == '1')
            {
                printf("�����޸�ҽ������Ϣ����һ����?\r\n");
                printf("1. ����\r\n");
                printf("2. ��¼����\r\n");
                printf("����������ѡ��: ");
                pat_msg[1][0] = app_get_choice();
                if(pat_msg[1][0] == '1' || pat_msg[1][0] == '2'){
                    printf("�������޸��Ժ��ֵ: ");
                    scanf("%s", pat_msg[2]);
                    platform_manage_commend(COMMEND_MAN_CHG_PAT_BY_id, message, pat_msg);
                    printf(message);
                }
                system("pause");
            }
        }else{
            system("pause");
        }
        printf("�����Ƿ�����޸� 1�� 0�˳�:");
        choice = app_get_choice();
        if(choice == '0')
            break;
    }
}

void app_manage_show_msg(base_data *login_data, int8_t *message){
    int8_t choice;
    system("CLS");
    printf("********************************************\r\n");
    printf("*                                          *\r\n");
    printf("*           ��ѡ����Ҫ�鿴����Ϣ           *\r\n");
    printf("*                                          *\r\n");
    printf("********************************************\r\n");
    printf("1.�鿴��ǰ���ܻ�ӭ��ҽ��\r\n");
    printf("2.�鿴��ǰ�������ܻ�ӭ�Ĳ���\r\n");
    printf("����������ѡ��: ");
    choice = app_get_choice();
    if(choice == '1')
    {
        platform_manage_commend(COMMEND_MAN_GET_OTHER_MSG, message, 1);
    }else if(choice == '2')
    {
        platform_manage_commend(COMMEND_MAN_GET_OTHER_MSG, message, 2);
    }
    printf(message);
    system("pause");
}

/**
  * @brief  ����Ա���ܵĴ�����
  * @param  login_data:һ�������¼����Ϣ�Ľṹ��
  * @retval ��
  */
void app_manage_dealwith(base_data *login_data)
{
    system("CLS");
    int8_t choice;
    int8_t data[1024] = {0};
    platform_manage_commend(COMMEND_MAN_GET_SELF_DATA, data, 0);
    printf(data);

    while(1){

        printf("********************************************\r\n");
        printf("*                                          *\r\n");
        printf("*            ��ѡ������Ҫ�ķ���            *\r\n");
        printf("*                                          *\r\n");
        printf("********************************************\r\n");
        printf("1. ��ȡ��ǰ����ҽ������Ϣ\r\n");
        printf("2. ��ʾ���еĲ��˵���Ϣ\r\n");
        printf("3. ɾ��ĳһ��ҽ��\r\n");
        printf("4. �޸�ĳһ��ҽ������Ϣ(�����޸�id)\r\n");
        printf("5. ���һ��ҽ��\r\n");
        printf("6. ���ĳһ��ԤԼ(���˲���ͨ�������id���е�¼,��¼�����ٸ���)\r\n");
        printf("7. �޸�ĳһ�����˵���Ϣ(�����޸�id)\r\n");
        printf("8. ��һ���ļ����油�����ڵ��ļ���Ϣ\r\n");
        printf("9. �鿴һЩ������Ϣ\r\n");
        printf("0. �˳�\r\n");
        printf("����ѡ����: ");
        choice = app_get_choice();
        switch (choice)
        {
        case '1':
            app_manage_get_doc_msg(login_data);
            break;
        case '2':
            app_manage_aply_pta_message(login_data, data);
            break;      
        case '3':
            app_manage_del_doctor(login_data, data);
            break;
        case '4':
            app_manage_amend_doctor(login_data, data);
            break;
        case '5':
            app_manage_add_doctor(login_data, data);
            break;
        case '6':
            app_manage_del_patient(login_data, data);
            break;
        case '7':
            app_manage_amend_pat(login_data, data);
            break;
        case '8':
            app_manage_add_msg_file(login_data, data);
            break;
        case '9':
            app_manage_show_msg(login_data, data);
            break;        
        default:
            break;
        }

        system("CLS");
        if(choice == '0')
            break;
    }
}
