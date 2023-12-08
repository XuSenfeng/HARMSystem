#ifndef PLATFORM_PATIENT_H
#define PLATFORM_PATIENT_H

#include "platform_main.h"
#include "platform_update.h"
void platform_get_patient_login_data(patient_t *patient_t, int8_t *message);
void platform_patient_commend(int8_t commend, char *id, char *message, void *parameter);


#endif // !PLATFORM_PATIENT_H