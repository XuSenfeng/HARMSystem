#include "app_manage.h"
int32_t app_manage_login(base_data *login_data)
{
    int8_t choice, num=3;
    int32_t ret;
    while(1){
        //之前存在用户
        printf("请输入您的id: ");
        fflush(stdin);
        scanf("%s", login_data->id);
        printf("请输入您的密码:");
        fflush(stdin);
        scanf("%s", login_data->passwd);
        fflush(stdin);
        ret = platform_login(login_data->id, login_data->passwd, '3');
        if(ret == -1)
        {
            num--;
            printf("id或者密码错误, 请重新输入");
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
//显示所有医生的信息,这里直接使用病人文件下面的实现
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
        printf("*            请选择你需要的服务            *\r\n");
        printf("*                                          *\r\n");
        printf("********************************************\r\n");
        printf("1. 获取当前所有医生的信息\r\n");
        printf("2. 显示所有的病人的信息\r\n");
        printf("3. 删除某一个医生\r\n");
        printf("4. 修改某一个医生的信息(不能修改id)\r\n");
        printf("5. 添加一个医生\r\n");
        printf("6. 删除某一个病人\r\n");
        printf("7. 修改某一个病人的信息(不能修改id)\r\n");
        printf("0. 退出\r\n");
        printf("您的选择是: ");
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
