#ifndef APP_MANAGE_H
#define APP_MANAGE_H
#include "app_main.h"
/*************命令****************/
//获取自己的登录信息
#define COMMEND_MAN_GET_SELF_DATA       1
//获取现在的病人的数量
#define COMMEND_MAN_GET_PAT_NUM         2
//获取病人的信息
#define COMMEND_MAN_GET_PAT_DATA        3
//获取某一个医生的信息通过id
#define COMMEND_MAN_GET_DOC_BY_id       4
//删除某一个医生通过id
#define COMMEND_MAN_DEL_DOC_BY_id       5
//更改某一个医生的某一条信息
#define COMMEND_MAN_CHG_DOC_BY_id       6
//通过文件添加信息
#define COMMEND_MAN_ADD_MSG_BY_FILE     7
//添加一个新的医生
#define COMMEND_MAN_ADD_NEW_DOC         8
//获取某一个病人的信息通过id
#define COMMEND_MAN_GET_ONE_PAT         9
//删除某一个病人
#define COMMEND_MAN_DEL_PAT_BY_id       10
//修改某一个病人
#define COMMEND_MAN_CHG_PAT_BY_id       11
//修改某一个病人
#define COMMEND_MAN_GET_OTHER_MSG       12

/*知名专家、主任医师、副主任医师、主治医师和医师。*/
#define DOC_LEVE_1              "知名专家"
#define DOC_LEVE_2              "主任医师"
#define DOC_LEVE_3              "副主任医师"
#define DOC_LEVE_4              "主治医师"
#define DOC_LEVE_5              "医师"


#define MESSAGE_STEP                    5

void platform_patient_getdoc_data_L(int8_t *message, int32_t begin, int32_t num);
void app_manage_dealwith(base_data *login_data);
int32_t app_manage_login(base_data *login_data);
#endif // !APP_MANAGE_H
