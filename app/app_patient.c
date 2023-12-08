#include "app_patient.h"

//�û���¼������
int32_t app_patient_login(base_data *login_data)
{
    int8_t choice, num=3;

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
            scanf("%s", login_data->id);
            printf("��������������:");
            fflush(stdin);
            scanf("%s", login_data->passwd);
            fflush(stdin);
            ret = platform_login(login_data->id, login_data->passwd, '1');
            if(ret == -1)
            {
                num--;
                printf("id�����������, ���������� %s %s\r\n", login_data->id, login_data->passwd);
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
//����1: ��ʾ����ҽ������Ϣ
void app_patient_get_doc_msg(base_data *login_data)
{
    int32_t n;
    int8_t choice, times, left;
    int8_t data[1024], page_s;
    int32_t parameter[3], i;
    platform_patient_commend(COMMEND_PAT_SET_DOC_NUM, login_data->id, 0, &n);
    printf("һ���� %d ��ҽ��\r\n", n);
    system("pause");
    system("CLS");
    printf("��ѡ��ۿ�ģʽ\r\n");
    printf("1. ���ݲ�����ʾҽ��\r\n");
    printf("2. ��ʾĳһ����������ҽ��\r\n");
    choice = app_get_choice();
    switch (choice)
    {
    case '1':
        times = n/MESSAGE_STEP;
        left = n%MESSAGE_STEP;
        for(i=0;i<=times;i++){
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
            printf("\r\n ����u���Ϸ�ҳ \r\n");
            page_s = getch();
            if(page_s=='u')
                i-=2;
            if(i<-1)
                i=-1;
            
            system("CLS");
        }

        break;
    
    default:
        break;
    }
}
//����3: ��ʾ�Լ���״̬
void app_patient_show_self(base_data *login_data, int8_t *message)
{
    platform_patient_commend(COMMEND_PAT_GET_SELF_DATA, login_data->id, message, 0);
    printf("%s", message);
    system("pause");
}
//����2: ����һ��ҽ����ԤԼ
void app_patient_aply_doc(base_data *login_data, int8_t *message)
{
    int8_t doc_id[21];
    printf("����������ԤԼ��ҽ����id: ");
    scanf("%s", doc_id);
    platform_patient_commend(COMMEND_PAT_APP_DOC, login_data->id, message, doc_id);
    printf(message);
    system("pause");
}


void app_patient_dealwith(base_data *login_data)
{
    system("CLS");
    int8_t choice;
    int8_t data[120] = {0};
    platform_patient_commend(COMMEND_PAT_GET_SELF_DATA, login_data->id, data);
    printf("%s", data);

    while(1){

        printf("********************************************\r\n");
        printf("*                                          *\r\n");
        printf("*            ��ѡ������Ҫ�ķ���            *\r\n");
        printf("*                                          *\r\n");
        printf("********************************************\r\n");
        printf("1. ��ȡ��ǰ����ҽ������Ϣ\r\n");
        printf("2. ����ĳһ��ҽ����ԤԼ\r\n");
        printf("3. �ٴ���ʾ��ǰ״̬\r\n");
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
        default:
            break;
        }

        system("CLS");
        if(choice == '0')
            break;
    }
}