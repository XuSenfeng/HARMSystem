/**
  ******************************************************************************
  * @file    app_patient.c
  * @version V1.0
  * @date    2023-12-10
  * @brief   这个是相关病人的操作,主要会调用平台的platform_login, platform_patient_commend函数
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

#include "app_patient.h"


/**
  * @brief  用户登录处理函数
  * @param  login_data:一个保存自己登录的信息的结构体
  * @retval 登录是否成功, 1成功, -1失败
  */
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
            if(ret ==ERROR)
            {
                num--;
                printf("\r\nid或者密码错误, 请重新输入 %s %s\r\n", login_data->id, login_data->passwd);
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
        return 1;
    }else
    {
        printf("\r\n输入有误返回上一级\r\n");
        system("pause");
        system("cls");
    }
}



/**
  * @brief  调用接口获取并显示某个时间段医生信息
  * @param  login_data:一个保存自己登录的信息的结构体
  * @param  data:数据暂存数组
  * @param  choice:筛选模式, 0所有, 1按照部门, 2按照可以接待
  * @retval 无
  */
void app_patient_get_doc_msg_tim(base_data *login_data, int8_t *data, int32_t choice_n)
{
    int8_t choice, times, left;
    int8_t page_s;
    char parameter[50], i;
    parameter[49] = choice_n;
    int32_t num_page;

    printf("请输入查询的是哪一天?\r\n");
    printf("周日:0 周一:1 周二:2 周三:3 周四:4 周五:5 周六:6\r\n");
    printf("您的选择是: ");
    scanf("%d", &parameter[0]);
    printf("请输入查询的是上午还是下午?\r\n");
    printf("1. 上午\r\n");
    printf("2. 下午\r\n");
    printf("您的选择是: ");   
    scanf("%d", &parameter[1]);
    if(choice_n==1)
    {
        printf("请输入你想查询的部门的名字: ");
        scanf("%s", &parameter[4]);
    }
    platform_patient_commend(COMMEND_PAT_GET_DOC_MSG_TIM_NUM, login_data->id, data, parameter);
    printf("一共有 %d 个医生\r\n", parameter[2]);
    system("pause");
    //按照不同的职称
    if(parameter[2]>0){
        times = parameter[2]/MESSAGE_STEP_L;
        left = parameter[2]%MESSAGE_STEP_L;
        parameter[2] = parameter[0]*2 + parameter[1]-1;
        for(i=0;i<=times;i++){
            system("CLS");
            parameter[0] = i*MESSAGE_STEP_L;
            if(i==times)
            {
                if(left != 0){
                    parameter[1] = left;
                }else
                    break;
            }else
                parameter[1] = MESSAGE_STEP_L;
            platform_patient_commend(COMMEND_PAT_GET_DOC_DTA_T, login_data->id, data, parameter);

            printf(data);
            printf("\r\n 第 %d 页 共 %d 页  输入u向上翻页 p退出 或者输入n + 页数跳转到对应页\r\n", i+1, times + 1);
            if(login_data->identity == '1')
                printf("输入 c 可以直接对医生进行预约\r\n");
            page_s = getch();
            if(page_s=='u')
                i-=2;
            if(i<-1)
                i=-1;
            if(page_s=='p')
                break;
            if(page_s=='n'){
                scanf("%d", &num_page);
                if(num_page <= times+1 && num_page > 0){
                    i = num_page-2;
                }else
                    i--;
            }
            if(login_data->identity == '1')
                if(page_s=='c'){
                    app_patient_aply_doc(login_data, data);
                    fflush(stdin);
                }           
        }
    }else{
        printf("没有符合条件的人\r\n");
        system("pause");
    }
}

/**
  * @brief  调用接口获取并显示所有医生的信息
  * @param  login_data:一个保存自己登录的信息的结构体
  * @retval 无
  */
void app_patient_get_doc_msg(base_data *login_data)
{
    int32_t num_data[3];
    int8_t choice, times, left;
    int8_t data[1024], page_s;
    int32_t parameter[3], i;
    int8_t doc_id[21];
    int32_t num_page;
    //获取现有的医生的数量
    platform_patient_commend(COMMEND_PAT_SET_DOC_NUM, login_data->id, 0, num_data);
    printf("一共有 %d 个部门, %d 个医生\r\n", num_data[0], num_data[1]);
    system("pause");
    while(1){
        system("CLS");
        printf("请选择观看模式\r\n");
        printf("1. 根据部门显示医生\r\n");
        printf("2. 按照职称显示所有医生\r\n");
        printf("3. 显示某一个医生的详细信息(通过id)\r\n");
        printf("4. 显示某一个时间段的所有医生\r\n");
        printf("5. 显示某个部门的在某个时间段上班的所有医生\r\n");
        printf("6. 显示某个时间段上还可以预约的所有医生\r\n");
        printf("0. 返回\r\n");
        printf("请输入您的选择: ");
        choice = app_get_choice();
        switch (choice)
        {
        case '1':
            //将所有的信息分层依次获取显示
            times = num_data[2]/MESSAGE_STEP;
            left = num_data[2]%MESSAGE_STEP;
            for(i=0;i<=times;i++){
                //循环打印每一个部门的信息
                system("CLS");
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
            printf("\r\n 第 %d 页 共 %d 页  输入u向上翻页 p退出 或者输入n + 页数\r\n", i+1, times + 1);
                if(login_data->identity == '1')
                    printf("输入 c 可以直接对医生进行预约\r\n");

                page_s = getch();
                //检测是否需要会退回去
                if(page_s=='u')
                    i-=2;
                if(i<-1)
                    i=-1; 
                if(page_s=='p')
                    break;
                if(page_s=='n'){
                    scanf("%d", &num_page);
                if(num_page <= times+1 && num_page > 0){
                    i = num_page-2;
                }else
                    i--;
                }
                if(login_data->identity == '1')
                    if(page_s=='c'){
                        app_patient_aply_doc(login_data, data);
                        fflush(stdin);
                    } 
            }
            break;
        case '2':
            //按照不同的职称
            times = num_data[1]/MESSAGE_STEP_L;
            left = num_data[1]%MESSAGE_STEP_L;
            for(i=0;i<=times;i++){
                system("CLS");
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
            printf("\r\n 第 %d 页 共 %d 页  输入u向上翻页 p退出 或者输入n + 页数\r\n", i+1, times + 1);
            if(login_data->identity == '1')
            printf("输入 c 可以直接对医生进行预约\r\n");

                page_s = getch();
                if(page_s=='u')
                    i-=2;
                if(i<-1)
                    i=-1;
                if(page_s=='p')
                    break;
                if(page_s=='n'){
                    scanf("%d", &num_page);
                if(num_page <= times+1 && num_page > 0){
                    i = num_page-2;
                }else
                    i--;
                }
                if(login_data->identity == '1')
                    if(page_s=='c'){
                        app_patient_aply_doc(login_data, data);
                        fflush(stdin);
                    }
            }
            break;
        case '3':
            printf("请输入您想获取的医生的id: ");
            scanf("%s", doc_id);
            platform_patient_commend(COMMEND_PAT_GET_DOC_MSG_id, login_data->id, data, doc_id);
            printf(data);
            system("pause");
            break;
        case '4':
            app_patient_get_doc_msg_tim(login_data, data, 0);
            break;
        case '5':
            app_patient_get_doc_msg_tim(login_data, data, 1);
            break;
        case '6':
            app_patient_get_doc_msg_tim(login_data, data, 2);
            break;
        default:
            return;
            break;
        }
    }
}
/**
  * @brief  功能3: 显示自己的状态
  * @param  login_data:一个保存自己登录的信息的结构体
  * @param  message:一个保存返回信息的字符串
  * @retval 无
  */
void app_patient_show_self(base_data *login_data, int8_t *message)
{
    platform_patient_commend(COMMEND_PAT_GET_SELF_DATA, login_data->id, message, 0);
    printf("%s", message);
    system("pause");
}
/**
  * @brief  功能2: 根据病人输入的id申请一个医生的预约
  * @param  login_data:一个保存自己登录的信息的结构体
  * @param  message:一个保存返回信息的字符串
  * @retval 无
  */
void app_patient_aply_doc(base_data *login_data, int8_t *message)
{
    int8_t doc_id[21];
    printf("请输入您想预约的医生的id: ");
    scanf("%s", doc_id);
    platform_patient_commend(COMMEND_PAT_APP_DOC, login_data->id, message, doc_id);
    printf(message);
    system("pause");
}


/**
  * @brief  病人主要的处理函数
  * @param  login_data:一个保存自己登录的信息的结构体
  * @retval 无
  */
void app_patient_dealwith(base_data *login_data)
{
    system("CLS");
    int8_t choice;
    int8_t data[1024] = {0};
    platform_patient_commend(COMMEND_PAT_GET_SELF_DATA, login_data->id, data);
    printf("%s", data);

    while(1){

        printf("********************************************\r\n");
        printf("*                                          *\r\n");
        printf("*            请选择你需要的服务            *\r\n");
        printf("*                                          *\r\n");
        printf("********************************************\r\n");
        printf("1. 获取当前医生的信息\r\n");
        printf("2. 申请某一个医生的预约\r\n");
        printf("3. 再次显示当前状态\r\n");
        printf("4. 取消预约\r\n");
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
            break;
        case '4':
            platform_patient_commend(COMMEND_PAT_DEL_DOC_APLY, login_data->id, data, 0);
            printf(data);
            system("pause");
            break;
        default:
            break;
        }

        system("CLS");
        if(choice == '0')
            break;
    }
}