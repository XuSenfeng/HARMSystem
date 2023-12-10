#ifndef PLATFORM_UPDATE_H
#define PLATFORM_UPDATE_H
#include "platform_main.h"
void platform_manage_init();
doctor_t * platform_add_doctor(char *name, char *id, char *passwd , char *work, char *level, int32_t num_to_acp, int8_t *workday);
one_department_t * platform_init_department(char *name);
outpatient_service_t * platform_init_service(char *name, one_department_t* department);
patient_t * platform_init_patient(char *name, char *id, char *passwd);
int32_t platform_patient_appointment(patient_t *patient, char *doc_id);
uint32_t platform_get_patient_status(patient_t *patient);
void platform_del_doctor(doctor_t *doctor);
patient_t* platform_get_patient(char *id);
doctor_t *platform_get_doc(char *id);
void *platform_add_patient(int8_t *name, int8_t *id, int8_t *passwd, int8_t status, int8_t *doc_id);
void platform_manage_out();
void platform_doc_deal_pat(doctor_t *doctor, patient_t *patient, int8_t choice);
void platform_del_patient(patient_t *patient);
#endif // !PLATFORM_UPDATE_H