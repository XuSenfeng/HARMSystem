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
        scanf("%s", login_data->passwd);
        fflush(stdin);
        ret = platform_login(login_data->id, login_data->passwd, '3');
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
//��ʾ����ҽ������Ϣ,����ֱ��ʹ�ò����ļ������ʵ��
void app_manage_get_doc_msg(base_data *login_data){
    app_patient_get_doc_msg(login_data);
}
void app_manage_dealwith(base_data *login_data)
{
    system("CLS");
    int8_t choice;
    int8_t data[120] = {0};
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
        printf("0. �˳�\r\n");
        printf("����ѡ����: ");
        choice = app_get_choice();
        switch (choice)
        {
        case '1':
            app_patient_get_doc_msg(login_data);
            break;
        case '2':
            //app_manage_aply_doc(login_data, data);
            break;      
        case '3':
            //app_patient_show_self(login_data, data);
        default:
            break;
        }

        system("CLS");
        if(choice == '0')
            break;
    }
}
