/**
  ******************************************************************************
  * @file    platform_manage.c
  * @version V1.0
  * @date    2023-12-10
  * @brief   这个是管理者相关的操作的实现, platform_login, platform_manage_commend函数被调用
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

#include "app_manage.h"


/**
  * @brief  医生的登录界面
  * @param  login_data:一个保存登录的信息的结构体
  * @retval 无
  */
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
        app_get_passwd(login_data->passwd);
        fflush(stdin);
        ret = platform_login(login_data->id, login_data->passwd, '3');
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
  * @brief  显示所有医生的信息,这里直接使用病人文件下面的实现
  * @param  login_data:一个保存登录的信息的结构体
  * @retval 无
  */
void app_manage_get_doc_msg(base_data *login_data){
    app_patient_get_doc_msg(login_data);
}


/**
  * @brief  依次展示所有的病人信息
  * @param  login_data:一个保存登录的信息的结构体
  * @param  message:传递信息使用的字符串
  * @retval 无
  */
void app_manage_aply_pta_message(base_data *login_data, int8_t *message)
{
    int32_t n;
    int8_t choice, times, left;
    int8_t page_s;
    int32_t parameter[3], i;
        int32_t num_page;

    platform_manage_commend(COMMEND_MAN_GET_PAT_NUM, 0, &n);
    n -=1;
    system("CLS");
    printf("一共有 %d 个患者\r\n", n);
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

        platform_manage_commend(COMMEND_MAN_GET_PAT_DATA, message, parameter);
        printf(message);
        printf("\r\n 第 %d 页 共 %d 页  输入u向上翻页 p退出 或者输入n + 页数\r\n", i+1, times + 1);
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
        system("CLS");
    }
}

/**
  * @brief  删除某一个医生
  * @param  login_data:一个保存登录的信息的结构体
  * @param  message:传递信息使用的字符串
  * @retval 无
  */
void app_manage_del_doctor(base_data *login_data, int8_t *message){
    int8_t doc_id[21], choice;
    system("CLS");
    printf("现在请你输入要删除的某一个医生的id: ");
    scanf("%s", doc_id);
    printf("请您确定您要删除这一位医生:\r\n");
    platform_manage_commend(COMMEND_MAN_GET_DOC_BY_id, message, doc_id);
    printf(message);
    if(doc_id[0]!=0)
    {
        printf("1. 确定\r\n");
        printf("2. 取消\r\n");
        choice = app_get_choice();
        if(choice == '1')
        {
            platform_manage_commend(COMMEND_MAN_DEL_DOC_BY_id, message, doc_id);
            printf(message);
            system("pause");
        }
    }else{
        system("pause");
    }

}
/**
  * @brief  修改医生的信息
  * @param  login_data:一个保存登录的信息的结构体
  * @param  message:传递信息使用的字符串
  * @retval 无
  */
void app_manage_amend_doctor(base_data *login_data, int8_t *message)
{
    //信息数组1: id, 2:选择 3:改以后的值
    int8_t doc_msg[3][31], choice;
    system("CLS");
    printf("请输入您想要更改的医生的id: ");
    scanf("%s", doc_msg[0]);
    printf("请您确定您要修改这一位医生:\r\n");
    platform_manage_commend(COMMEND_MAN_GET_DOC_BY_id, message, doc_msg[0]);
    printf(message);
    if(doc_msg[0][0]!=0)
    {
        printf("1. 确定\r\n");
        printf("2. 取消\r\n");
        printf("请输入您的选择: ");
        choice = app_get_choice();
        if(choice == '1')
        {
            printf("您想修改医生的信息的哪一部分?\r\n");
            printf("1. 名字\r\n");
            printf("2. 职称\r\n");
            printf("3. 登录密码\r\n");
            printf("4. 部门\r\n");
            printf("请输入您的选择: ");
            doc_msg[1][0] = app_get_choice();
            if(choice == '1' && choice == '2' && choice == '3'){
                printf("请输入修改以后的值: ");
                scanf("%s", doc_msg[2]);
            }else{
                printf("请选择现在他的职称\r\n");
                printf("1. %s\r\n", DOC_LEVE_1);
                printf("2. %s\r\n", DOC_LEVE_2);
                printf("3. %s\r\n", DOC_LEVE_3);
                printf("4. %s\r\n", DOC_LEVE_4);
                printf("5. %s\r\n", DOC_LEVE_5);
                printf("请输入你的选择: ");
                choice = app_get_choice();
                if(choice == '1')
                {
                    strcpy(doc_msg[2], DOC_LEVE_1);
                }else if(choice == '2')
                {
                    strcpy(doc_msg[2], DOC_LEVE_2); 
                }else if(choice == '3')
                {
                    strcpy(doc_msg[2], DOC_LEVE_3);
                }else if(choice == '4')
                {
                    strcpy(doc_msg[2], DOC_LEVE_4);
                }else if(choice == '5')
                {
                    strcpy(doc_msg[2], DOC_LEVE_5);
                }else {
                    printf("输入有误!!\r\n");
                    system("pause");
                    return;
                }
            }

            platform_manage_commend(COMMEND_MAN_CHG_DOC_BY_id, message, doc_msg);
            printf(message);
            system("pause");
        }
    }else{
        system("pause");
    }
}

/**
  * @brief  通过文件添加信息
  * @param  login_data:一个保存登录的信息的结构体
  * @param  message:传递信息使用的字符串
  * @retval 无
  */
void app_manage_add_msg_file(base_data *login_data, int8_t *message)
{
    int8_t choice;
    int8_t name[50];
    system("CLS");
    printf("即将从一个文件里面添加信息\r\n");
    printf("请务必按照给定的文件格式!!!!!!!!!\r\n");
    printf("请务必按输入正确的路径!!!!!!!!!\r\n");
    printf("文件格式如下\r\n");
    printf("**************************************************\r\n");
    printf("各个部门的个数(数字)\r\n");
    printf("部门个数条信息: 部门名字 部门下面门诊个数 按照个数输入部门名字\r\n");
    printf("医生的个数(数字)\r\n");
    printf("医生个数条信息: 医生编号 名字 登录密码 门诊 职称 接待的最大病人数 工作时间 已经接待的病人数 当前的工资\r\n");
    printf("病人的个数(数字)\r\n");
    printf("病人个数条信息: 病人编号 名字 登录密码 当前状态(0 没有预约 1 预约未就诊 2 复诊) 接诊医生编号 医生给他的信息\r\n");
    printf("**************************************************\r\n");
    printf("1. 确定\r\n");
    printf("2. 取消\r\n");
    printf("请输入您的选择: ");
    choice = app_get_choice();
    if(choice == '1')
    {
        printf("\r\n请输入文件名: ");
        scanf("%s", name);
        platform_manage_commend(COMMEND_MAN_ADD_MSG_BY_FILE, message, name);
        printf(message);
        system("pause");
    }
    
}
/**
  * @brief  添加一个医生
  * @param  login_data:一个保存登录的信息的结构体
  * @param  message:传递信息使用的字符串
  * @retval 无
  */
void app_manage_add_doctor(base_data *login_data, int8_t *message)
{
    int8_t choice;
    int8_t doc_msg[6][31];
    
    while(1){
        system("CLS");
        printf("现在你可以添加一个医生\r\n");
        printf("请务必输入正确的信息!!!\r\n");
        printf("1. 确定\r\n");
        printf("2. 取消\r\n");
        printf("请输入您的选择: ");
        choice = app_get_choice();
        if(choice == '1')
        {
            printf("请输入医生的名字: ");
            scanf("%s", doc_msg[0]);
            printf("请输入医生的部门: ");
            scanf("%s", doc_msg[1]);
            printf("现有职称: 知名专家 主任医师 副主任医师 主治医师 医师\r\n");
            printf("请输入医生的职称: ");
            scanf("%s", doc_msg[2]);
            printf("请输入医生的密码: ");
            scanf("%s", doc_msg[3]);
            printf("请输入医生的工作日(十四位代表一周的上下午1.工作 0.休息): ");
            scanf("%s", doc_msg[4]);
            printf("请输入医生的最大接诊数量: ");
            scanf("%d", &doc_msg[5][0]);
            printf("请输入医生单次接待价格: ");
            scanf("%d", &doc_msg[5][1]);   
            platform_manage_commend(COMMEND_MAN_ADD_NEW_DOC, message, doc_msg);
            printf(message);
            system("pause");
        }else
        {
            printf("退出\r\n");
            system("pause");
        }
        printf("请问是否继续添加 1是 0退出:");
        choice = app_get_choice();
        if(choice == '0')
            break;
    }
}
/**
  * @brief  删除某一个病人通过id
  * @param  login_data:一个保存登录的信息的结构体
  * @param  message:传递信息使用的字符串
  * @retval 无
  */
void app_manage_del_patient(base_data *login_data, int8_t *message)
{
    int8_t choice;
    int8_t pat_id[31];
    system("CLS");
    printf("现在你可以选择封存一个病人\r\n");
    printf("1. 确定\r\n");
    printf("2. 取消\r\n");
    printf("请输入您的选择: ");
    choice = app_get_choice();
    if(choice == '1')
    {
        printf("请输入您想要封存的预约的id: ");
        scanf("%s", pat_id);
        platform_manage_commend(COMMEND_MAN_GET_ONE_PAT, message, pat_id);
        printf(message);
        if(pat_id[0]!=0)
        {
            printf("1. 确定\r\n");
            printf("2. 取消\r\n");
            choice = app_get_choice();
            if(choice == '1')
            {
                platform_manage_commend(COMMEND_MAN_DEL_PAT_BY_id, message, pat_id);
                printf(message);
                system("pause");
            }
        }else{
            system("pause");
        }

    }else{
        printf("退出\r\n");
        system("pause");
    }
}
/**
  * @brief  修改某一个病人的信息
  * @param  login_data:一个保存登录的信息的结构体
  * @param  message:传递信息使用的字符串
  * @retval 无
  */
void app_manage_amend_pat(base_data *login_data, int8_t *message)
{
    //信息数组1: id, 2:选择 3:改以后的值
    int8_t pat_msg[3][31], choice;
    while(1){
        system("CLS");
        printf("请输入您想要更改的病人的id: ");
        scanf("%s", pat_msg[0]);
        printf("请您确定您要修改这一位病人:\r\n");
        platform_manage_commend(COMMEND_MAN_GET_ONE_PAT, message, pat_msg[0]);
        printf(message);
        if(pat_msg[0][0]!=0)
        {
            printf("1. 确定\r\n");
            printf("2. 取消\r\n");
            printf("请输入您的选择: ");
            choice = app_get_choice();
            if(choice == '1')
            {
                printf("您想修改医生的信息的哪一部分?\r\n");
                printf("1. 名字\r\n");
                printf("2. 登录密码\r\n");
                printf("请输入您的选择: ");
                pat_msg[1][0] = app_get_choice();
                if(pat_msg[1][0] == '1' || pat_msg[1][0] == '2'){
                    printf("请输入修改以后的值: ");
                    scanf("%s", pat_msg[2]);
                    platform_manage_commend(COMMEND_MAN_CHG_PAT_BY_id, message, pat_msg);
                    printf(message);
                }
                system("pause");
            }
        }else{
            system("pause");
        }
        printf("请问是否继续修改 1是 0退出:");
        choice = app_get_choice();
        if(choice == '0')
            break;
    }
}

void app_manage_show_msg(base_data *login_data, int8_t *message){
    int8_t choice;
    system("CLS");
    printf("********************************************\r\n");
    printf("*                                          *\r\n");
    printf("*           请选择你要查看的信息           *\r\n");
    printf("*                                          *\r\n");
    printf("********************************************\r\n");
    printf("1.查看当前最受欢迎的医生\r\n");
    printf("2.查看当前收益最受欢迎的部门\r\n");
    printf("请输入您的选择: ");
    choice = app_get_choice();
    if(choice == '1')
    {
        platform_manage_commend(COMMEND_MAN_GET_OTHER_MSG, message, 1);
    }else if(choice == '2')
    {
        platform_manage_commend(COMMEND_MAN_GET_OTHER_MSG, message, 2);
    }
    printf(message);
    system("pause");
}

/**
  * @brief  管理员的总的处理函数
  * @param  login_data:一个保存登录的信息的结构体
  * @retval 无
  */
void app_manage_dealwith(base_data *login_data)
{
    system("CLS");
    int8_t choice;
    int8_t data[1024] = {0};
    platform_manage_commend(COMMEND_MAN_GET_SELF_DATA, data, 0);
    printf(data);

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
        printf("6. 封存某一个预约(病人不能通过再这个id进行登录,记录不可再更改)\r\n");
        printf("7. 修改某一个病人的信息(不能修改id)\r\n");
        printf("8. 从一个文件里面补充现在的文件信息\r\n");
        printf("9. 查看一些其他信息\r\n");
        printf("0. 退出\r\n");
        printf("您的选择是: ");
        choice = app_get_choice();
        switch (choice)
        {
        case '1':
            app_manage_get_doc_msg(login_data);
            break;
        case '2':
            app_manage_aply_pta_message(login_data, data);
            break;      
        case '3':
            app_manage_del_doctor(login_data, data);
            break;
        case '4':
            app_manage_amend_doctor(login_data, data);
            break;
        case '5':
            app_manage_add_doctor(login_data, data);
            break;
        case '6':
            app_manage_del_patient(login_data, data);
            break;
        case '7':
            app_manage_amend_pat(login_data, data);
            break;
        case '8':
            app_manage_add_msg_file(login_data, data);
            break;
        case '9':
            app_manage_show_msg(login_data, data);
            break;        
        default:
            break;
        }

        system("CLS");
        if(choice == '0')
            break;
    }
}
