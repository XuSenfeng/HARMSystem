#ifndef APP_MANAGE_H
#define APP_MANAGE_H
#include "app_main.h"
#define COMMEND_MAN_GET_SELF_DATA       1

void platform_patient_getdoc_data_L(int8_t *message, int32_t begin, int32_t num);
void app_manage_dealwith(base_data *login_data);
int32_t app_manage_login(base_data *login_data);
#endif // !APP_MANAGE_H
