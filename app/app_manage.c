#include "app_manage.h"
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
        if(ret == -1)
        {
            num--;
            printf("\r\nid�����������, ����������\r\n");
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
//��ʾ����ҽ������Ϣ,����ֱ��ʹ�ò����ļ������ʵ��
void app_manage_get_doc_msg(base_data *login_data){
    app_patient_get_doc_msg(login_data);
}



//����չʾ���еĲ�����Ϣ
void app_manage_aply_pta_message(base_data *login_data, int8_t *message)
{
    int32_t n;
    int8_t choice, times, left;
    int8_t page_s;
    int32_t parameter[3], i;
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
        printf("\r\n ����u���Ϸ�ҳ \r\n");
        page_s = getch();
        if(page_s=='u')
            i-=2;
        if(i<-1)
            i=-1;
        
        system("CLS");
    }
    system("pause");
}


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
            printf("�������޸��Ժ��ֵ: ");
            scanf("%s", doc_msg[2]);
            printf("\r\n����%s\r\n, ", doc_msg[0]);
            platform_manage_commend(COMMEND_MAN_CHG_DOC_BY_id, message, doc_msg);
            printf(message);
            system("pause");
        }
    }else{
        system("pause");
    }
}


void app_manage_add_msg_file(base_data *login_data, int8_t *message)
{
    int8_t choice;
    int8_t name[50];
    system("CLS");
    printf("������һ���ļ����������Ϣ\r\n");
    printf("����ذ��ո������ļ���ʽ,�����������!!!!!!!!!\r\n");
    printf("����ذ�������ȷ��·��, �����������!!!!!!!!!\r\n");
    printf("�ļ���ʽ����\r\n");
    printf("**************************************************\r\n");
    printf("�������ŵĸ���(����)\r\n");
    printf("���Ÿ�������Ϣ: �������� ��������������� ���ո������벿������\r\n");
    printf("ҽ���ĸ���(����)\r\n");
    printf("ҽ����������Ϣ: ҽ����� ���� ��¼���� ���� ְ�� �Ӵ����������\r\n");
    printf("���˵ĸ���(����)\r\n");
    printf("���˸�������Ϣ: ���˱�� ���� ��¼���� ��ǰ״̬(0 û��ԤԼ 1 ԤԼδ���� 2 ����) ����ҽ�����\r\n");
    printf("**************************************************\r\n");
    printf("1. ȷ��\r\n");
    printf("2. ȡ��\r\n");
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

//�ܵĴ�����
void app_manage_dealwith(base_data *login_data)
{
    system("CLS");
    int8_t choice;
    int8_t data[1024] = {0};
    platform_patient_commend(COMMEND_MAN_GET_SELF_DATA, login_data->id, data);
    printf("%s", data);

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
        printf("6. ɾ��ĳһ������\r\n");
        printf("7. �޸�ĳһ�����˵���Ϣ(�����޸�id)\r\n");
        printf("8. ��һ���ļ����油�����ڵ��ļ���Ϣ\r\n");
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
            break;
        case '6':
            break;
        case '7':
            break;
        case '8':
            app_manage_add_msg_file(login_data, data);
            break;
        
        default:
            break;
        }

        system("CLS");
        if(choice == '0')
            break;
    }
}
