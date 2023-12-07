#ifndef PLATFORM_MAIN_H
#define PLATFORM_MAIN_H
#include "type.h"
#include "list.h"
#include "app_main.h"


void platform_init();
void platform_out();
void platform_manage_init();
doctor_t * platform_get_doctor(char *name, char *id, char *passwd);
void *platform_login(int8_t *id, int8_t *passwd, int8_t choice);
patient_t * platform_get_patient(char *name, char *id, char *passwd);
#endif /*PLATFORM_MAIN_H*/
