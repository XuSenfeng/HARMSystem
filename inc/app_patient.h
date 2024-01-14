#ifndef APP_PATIENT_H
#define APP_PATIENT_H
#include "app_main.h"
#include <conio.h>
/*************命令************/
//获取自己的登录信息
#define COMMEND_PAT_GET_SELF_DATA       1
//获取医生的数量
#define COMMEND_PAT_SET_DOC_NUM         2
//申请某一个医生
#define COMMEND_PAT_APP_DOC             3
//获取医生信息通过部门
#define COMMEND_PAT_GET_DOC_DTA_D       4
//申请一个新的病人
#define COMMEND_PAT_APLY_NEW_PAT        5
//获取医生的信息通过职称
#define COMMEND_PAT_GET_DOC_DTA_L       6
//获取某一个医生的工作时间信息
#define COMMEND_PAT_GET_DOC_TIME        7
//删除自己的预约
#define COMMEND_PAT_DEL_DOC_APLY        8
//通过id获取某一个医生的信息
#define COMMEND_PAT_GET_DOC_MSG_id      9
//通过时间获取某医生的信息
#define COMMEND_PAT_GET_DOC_MSG_TIM_NUM 10
//获取医生的信息通过时间
#define COMMEND_PAT_GET_DOC_DTA_T       11

//显示信息的时候的步长
#define MESSAGE_STEP                    10
#define MESSAGE_STEP_L                  5

void app_patient_dealwith(base_data *login_data);
int32_t app_patient_login(base_data *login_data);

#endif // !APP_PATIENT_H