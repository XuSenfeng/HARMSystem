#include "app_doctor.h"

//医生的登录函数,成功的话返回1,否则返回0
int32_t app_doctor_login(base_data *login_data)
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
        ret = platform_login(login_data->id, login_data->passwd, '2');
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

void app_doctor_get_pat_msg(base_data *login_data)
{
    int32_t n;
    int8_t choice, times, left;
    int8_t data[1024], page_s;
    int32_t parameter[3], i;
    platform_doctor_commend(COMMEND_DOC_GET_PAT_NUM, login_data->id, 0, &n);
    system("CLS");
    printf("一共有 %d 个患者\r\n", n);
    //
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
        
        platform_doctor_commend(COMMEND_PAT_GET_DOC_DTA_D, login_data->id, data, parameter);
        //
        printf(data);
        printf("\r\n 输入u向上翻页 \r\n");
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
    printf("医生id %s ", login_data->id);
    platform_doctor_commend(COMMEND_DOC_GET_SELF_DATA, login_data->id, data, 0);
    printf("%s", data);

    while(1){

        printf("********************************************\r\n");
        printf("*                                          *\r\n");
        printf("*            请选择你需要的服务            *\r\n");
        printf("*                                          *\r\n");
        printf("********************************************\r\n");
        printf("1. 获取当前所有病人\r\n");
        printf("2. 显示所有的病人的信息\r\n");
        printf("3. 对病人进行治疗\r\n");
        printf("0. 退出\r\n");
        printf("您的选择是: ");
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