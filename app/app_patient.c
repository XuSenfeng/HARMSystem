#include "app_patient.h"

//用户登录处理函数
int32_t app_patient_login(base_data *login_data)
{
    int8_t choice, num=3;
    int32_t ret;
    int8_t message[200];
    int8_t parameter[3][30];
    printf("请问您之前是否注册过用户?\r\n");
    printf("1.是的 2.没有\r\n");
    printf("您的选择是: ");
    choice = app_get_choice();
    if(choice == '1' )
    {
        while(1){
            //之前存在用户
            printf("请输入您的id: ");
            fflush(stdin);
            scanf("%s", login_data->id);
            printf("请输入您的密码:");
            fflush(stdin);
            app_get_passwd(login_data->passwd);
            fflush(stdin);
            ret = platform_login(login_data->id, login_data->passwd, '1');
            if(ret == -1)
            {
                num--;
                printf("\r\nid或者密码错误, 请重新输入 %s %s\r\n", login_data->id, login_data->passwd);
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
    }else if(choice == '2')
    {
        //之前没有用户
        printf("*******************\r\n");
        printf("*    用户注册     *\r\n");
        printf("*******************\r\n");
        printf("请输入您的真实姓名: \r\n");
        fflush(stdin);
        scanf("%s", parameter[0]);
        fflush(stdin);
        printf("请输入您的密码: ");
        app_get_passwd(parameter[1]);
        //printf("输入的密码是: %s\r\n", parameter[1]);
        //归零数组
        login_data->id[0] = 0;
        platform_patient_commend(COMMEND_PAT_APLY_NEW_PAT, login_data->id, message, parameter);
        printf(message);
        system("pause");
        system("cls");

    }else
    {
        printf("\r\n输入有误返回上一级\r\n");
        system("pause");
        system("cls");
    }
}
//功能1: 显示所有医生的信息
void app_patient_get_doc_msg(base_data *login_data)
{
    int32_t n;
    int8_t choice, times, left;
    int8_t data[1024], page_s;
    int32_t parameter[3], i;
    platform_patient_commend(COMMEND_PAT_SET_DOC_NUM, login_data->id, 0, &n);
    printf("一共有 %d 个医生\r\n", n);
    system("pause");
    system("CLS");
    printf("请选择观看模式\r\n");
    printf("1. 根据部门显示医生\r\n");
    printf("2. 按照职称显示所有医生\r\n");
    printf("请输入您的选择: ");
    choice = app_get_choice();
    switch (choice)
    {
    case '1':
        times = n/MESSAGE_STEP;
        left = n%MESSAGE_STEP;
        for(i=0;i<=times;i++){
            //循环打印每一个部门的信息
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
            printf("\r\n 输入u向上翻页 \r\n");
            page_s = getch();
            if(page_s=='u')
                i-=2;
            if(i<-1)
                i=-1;
            
            system("CLS");
        }
        break;
        case '2':
        times = n/MESSAGE_STEP_L;
        left = n%MESSAGE_STEP_L;
        for(i=0;i<=times;i++){
            //循环打印每一个部门的信息
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
            printf("\r\n 输入u向上翻页 \r\n");
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
//功能3: 显示自己的状态
void app_patient_show_self(base_data *login_data, int8_t *message)
{
    platform_patient_commend(COMMEND_PAT_GET_SELF_DATA, login_data->id, message, 0);
    printf("%s", message);
    system("pause");
}
//功能2: 申请一个医生的预约
void app_patient_aply_doc(base_data *login_data, int8_t *message)
{
    int8_t doc_id[21];
    printf("请输入您想预约的医生的id: ");
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
        printf("*            请选择你需要的服务            *\r\n");
        printf("*                                          *\r\n");
        printf("********************************************\r\n");
        printf("1. 获取当前所有医生的信息\r\n");
        printf("2. 申请某一个医生的预约\r\n");
        printf("3. 再次显示当前状态\r\n");
        printf("0. 退出\r\n");
        printf("您的选择是: ");
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