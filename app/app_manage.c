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

void app_manage_dealwith(base_data *login_data)
{

}