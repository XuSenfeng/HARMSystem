#ifndef APP_DISPOSE_H
#define APP_DISPOSE_H
#include "type.h"
#include "app_main.h" 
int8_t app_get_choice();
int8_t app_welcome(void);
void app_successed_login(base_data *login_data);
void app_get_passwd(char *password);
#endif // !APP_DISPOSE_H