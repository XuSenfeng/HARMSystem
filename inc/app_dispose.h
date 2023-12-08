#ifndef APP_DISPOSE_H
#define APP_DISPOSE_H
#include "type.h"
#include "app_main.h" 

int8_t app_welcome(void);
void app_successed_login(base_data *login_data);
int32_t platform_get_patient(char *id);
#endif // !APP_DISPOSE_H