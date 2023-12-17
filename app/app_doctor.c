/**
  ******************************************************************************
  * @file    app_doctor.c
  * @version V1.0
  * @date    2023-12-10
  * @brief   这个文件是app层次的医生相关的操作platform_login, platform_doctor_commend
  * @author  XvSenfeng(焦浩洋)
  ******************************************************************************
  * @attention
  * 本程序由XvSenfeng创建并免费开源共享
  * 你可以任意查看、使用和修改，并应用到自己的项目之中
  * 程序版权归XvSenfeng所有，任何人或组织不得将其据为己有
  * 如果你发现程序中的漏洞或者笔误，可通过邮件向我们反馈：1458612070@qq.com
  * 发送邮件之前，你可以先到更新动态页面查看最新程序，如果此问题已经修改，则无需再发邮件
  * https://github.com/XuSenfeng
  ******************************************************************************
  */ 

#include "app_doctor.h"
/**
  * @brief  医生的登录函数,成功的话返回1,否则返回0
  * @param  login_data:一个保存登录的信息的结构体
  * @retval 1成功登录-1登录失败
  */
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
        app_get_passwd(login_data->passwd);
        fflush(stdin);
        ret = platform_login(login_data->id, login_data->passwd, '2');
        if(ret == ERROR)
        {
            num--;
            printf("\r\nid或者密码错误, 请重新输入\r\n");
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
  * @brief  医生获取自己的病人的信息
  * @param  login_data:一个保存登录的信息的结构体
  * @param  message:保存返回信息的结构体
  * @retval 无
  */
void app_doctor_get_pat_msg(base_data *login_data, int8_t *message)
{
    int32_t n;
    int8_t choice, times, left;
    int8_t page_s;
    int32_t parameter[3], i;
    platform_doctor_commend(COMMEND_DOC_GET_PAT_NUM, login_data->id, 0, &n);
    system("CLS");
    printf("一共有 %d 个患者\r\n", n);

    times = n/MESSAGE_STEP;
    left = n%MESSAGE_STEP;
    for(i=0;i<=times;i++){
        //循环打印每一个病人
        parameter[0] = i*MESSAGE_STEP;
        if(i==times)
        {
            if(left != 0){
                parameter[1] = left;
            }else
                break;
        }else
            parameter[1] = MESSAGE_STEP;
        
        platform_doctor_commend(COMMEND_DOC_GET_PAT_DTA_D, login_data->id, message, parameter);
        printf(message);
        printf("\r\n 输入u向上翻页 \r\n");
        page_s = getch();
        if(page_s=='u')
            i-=2;
        if(i<-1)
            i=-1;
    }
    system("pause");
}
/**
  * @brief  医生对自己的病人进行治疗处理
  * @param  login_data:一个保存登录的信息的结构体
  * @param  message:保存返回信息的结构体
  * @retval 无
  */
void app_doctor_deal_pat(base_data *login_data, int8_t *message)
{
    int8_t choice[2];
    int8_t msg_to_pat[100];
    system("CLS");
    printf("即将对现在您的预约的病人进行传唤....\r\n");
    platform_doctor_commend(COMMEND_DOC_GET_FIRST_PAT, login_data->id, message, 0);
    printf(message);
    printf("请您确定是否要对他进行治疗\r\n");
    printf("1. 进行治疗,需要进一步治疗\r\n");
    printf("2. 治疗结束,病人不需要进一步治疗\r\n");
    printf("3. 不对他进行治疗,请他去别的地方就诊\r\n");
    printf("4. 暂时先不进行治疗\r\n");
    printf("请输入您的选择: ");
    choice[0] = app_get_choice();
    printf("请问是否需要给病人追加信息?\r\n");
    printf("1. 确定\r\n");
    printf("2. 取消\r\n");
    printf("请输入您的选择: ");
    choice[1] = app_get_choice();
    if(choice[1] == '1')
    {
        //printf("\r\n输入的信息里面请务必不要有空格和换行!!!!!!!!\r\n");
        printf("请输入您想传达的信息: ");
        scanf("%s", msg_to_pat);
        platform_doctor_commend(COMMEND_DOC_ADD_PAT_MSG, login_data->id, message, msg_to_pat);
        printf(message); 
    }
    switch (choice[0])
    {
    case '1':
        //更改病人的状态,并发送信息给病人
        platform_doctor_commend(COMMEND_DOC_DEAL_FST_PAT, login_data->id, message, choice);
        printf(message);
        break;
    case '2':
        //病人痊愈
        platform_doctor_commend(COMMEND_DOC_DEAL_FST_PAT, login_data->id, message, choice);
        printf(message);

        break;   
    case '3':
        //请病人走人
        platform_doctor_commend(COMMEND_DOC_DEAL_FST_PAT, login_data->id, message, choice);
        printf(message); 
        break;
    case '4':
        //不做处理
        break;
    default:
        break;
    }
    system("pause");
}
/**
  * @brief  医生的总的处理函数
  * @param  login_data:一个保存登录的信息的结构体
  * @retval 无
  */
void app_doctor_dealwith(base_data *login_data)
{
    system("CLS");
    int8_t choice;
    int8_t data[1024] = {0};
    //printf("医生id %s ", login_data->id);
    platform_doctor_commend(COMMEND_DOC_GET_SELF_DATA, login_data->id, data, 0);
    printf("%s", data);

    while(1){

        printf("********************************************\r\n");
        printf("*                                          *\r\n");
        printf("*            请选择你需要的服务            *\r\n");
        printf("*                                          *\r\n");
        printf("********************************************\r\n");
        printf("1. 获取当前待处理所有病人\r\n");
        printf("2. 对病人进行治疗\r\n");
        printf("3. 再次获取登录时候的信息总结\r\n");
        printf("0. 退出\r\n");
        printf("您的选择是: ");
        choice = app_get_choice();
        switch (choice)
        {
        case '1':
            app_doctor_get_pat_msg(login_data, data);
            break;
        case '2':
            app_doctor_deal_pat(login_data, data);
            break;      
        case '3':
            platform_doctor_commend(COMMEND_DOC_GET_SELF_DATA, login_data->id, data, 0);
            printf("%s", data);
            system("pause");
            system("CLS");
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