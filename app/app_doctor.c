#include "app_doctor.h"

//ҽ���ĵ�¼����,�ɹ��Ļ�����1,���򷵻�0
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
        scanf("%s", login_data->passwd);
        fflush(stdin);
        ret = platform_login(login_data->id, login_data->passwd, '2');
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

void app_doctor_get_pat_msg(base_data *login_data)
{
    int32_t n;
    int8_t choice, times, left;
    int8_t data[1024], page_s;
    int32_t parameter[3], i;
    platform_doctor_commend(COMMEND_DOC_GET_PAT_NUM, login_data->id, 0, &n);
    system("CLS");
    printf("һ���� %d ������\r\n", n);
    //
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
        
        platform_doctor_commend(COMMEND_PAT_GET_DOC_DTA_D, login_data->id, data, parameter);
        //
        printf(data);
        printf("\r\n ����u���Ϸ�ҳ \r\n");
        page_s = getch();
        if(page_s=='u')
            i-=2;
        if(i<-1)
            i=-1;
        
        system("CLS");
    }




}

void app_doctor_dealwith(base_data *login_data)
{
    system("CLS");
    int8_t choice;
    int8_t data[1024] = {0};
    printf("ҽ��id %s ", login_data->id);
    platform_doctor_commend(COMMEND_DOC_GET_SELF_DATA, login_data->id, data, 0);
    printf("%s", data);

    while(1){

        printf("********************************************\r\n");
        printf("*                                          *\r\n");
        printf("*            ��ѡ������Ҫ�ķ���            *\r\n");
        printf("*                                          *\r\n");
        printf("********************************************\r\n");
        printf("1. ��ȡ��ǰ���в���\r\n");
        printf("2. ��ʾ���еĲ��˵���Ϣ\r\n");
        printf("3. �Բ��˽�������\r\n");
        printf("0. �˳�\r\n");
        printf("����ѡ����: ");
        choice = app_get_choice();
        switch (choice)
        {
        case '1':
            app_doctor_get_pat_msg(login_data);
            break;
        case '2':
            //app_doctor_show_pa(login_data, data);
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
    system("CLS");
    printf("");
}