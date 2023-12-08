#ifndef PLATFORM_UPDATE_H
#define PLATFORM_UPDATE_H
#include "platform_main.h"
void platform_manage_init();
doctor_t * platform_add_doctor(char *name, char *id, char *passwd , char *work);
one_department_t * platform_init_department(char *name);
outpatient_service_t * platform_init_service(char *name, one_department_t* department);
patient_t * platform_init_patient(char *name, char *id, char *passwd);
int32_t platform_patient_appointment(patient_t *patient, char *doc_id);
uint32_t platform_get_patient_status(patient_t *patient);
void platform_del_doctor(doctor_t *doctor);
#endif // !PLATFORM_UPDATE_H