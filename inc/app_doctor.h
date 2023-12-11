#ifndef APP_DOCTOR_H
#define APP_DOCTOR_H
#include "app_main.h"
/****************命令******************/
//获取自己的登录信息
#define COMMEND_DOC_GET_SELF_DATA           1
//获取自己的病人的数量
#define COMMEND_DOC_GET_PAT_NUM             2
//获取病人的信息
#define COMMEND_DOC_GET_PAT_DTA_D           3
//获取现在第一个病人的信息
#define COMMEND_DOC_GET_FIRST_PAT           4
//对病人进行治疗
#define COMMEND_DOC_DEAL_FST_PAT            5
//给第一个病人发送信息
#define COMMEND_DOC_ADD_PAT_MSG             6



//显示病人的时候的步长
#define MESSAGE_STEP                       5
void app_doctor_dealwith(base_data *login_data);
int32_t app_doctor_login(base_data *login_data);


#endif // !APP_DOCTOR_H