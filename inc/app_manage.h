#ifndef APP_MANAGE_H
#define APP_MANAGE_H
#include "app_main.h"
#define COMMEND_MAN_GET_SELF_DATA       1
#define COMMEND_MAN_GET_PAT_NUM         2
#define COMMEND_MAN_GET_PAT_DATA        3
#define COMMEND_MAN_GET_DOC_BY_id       4
#define COMMEND_MAN_DEL_DOC_BY_id       5
#define COMMEND_MAN_CHG_DOC_BY_id       6
#define COMMEND_MAN_ADD_MSG_BY_FILE     7
#define COMMEND_MAN_ADD_NEW_DOC         8
#define COMMEND_MAN_GET_ONE_PAT         9
#define COMMEND_MAN_DEL_PAT_BY_id       10
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
