#ifndef APP_DOCTOR_H
#define APP_DOCTOR_H
#include "app_main.h"

#define COMMEND_DOC_GET_SELF_DATA           1
#define COMMEND_DOC_GET_PAT_NUM             2
#define COMMEND_PAT_GET_DOC_DTA_D           3


#define MESSAGE_STEP                       5
void app_doctor_dealwith(base_data *login_data);
int32_t app_doctor_login(base_data *login_data);


#endif // !APP_DOCTOR_H