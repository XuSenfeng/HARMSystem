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

void app_patient_dealwith(base_data *login_data)
{
    //system("CLS");
    int8_t data[100];
    printf("����, �û�\r\n");
    platform_get_login_data(login_data->identity, data,login_data->id);
    printf("��ȡ��: %s", data);
    while(1);
}