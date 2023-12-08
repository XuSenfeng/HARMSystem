#include "platform_patient.h"

void platform_get_patient_login_data(patient_t *patient_t, int8_t *message)
{
    uint32_t status;
    status = platform_get_patient_status(patient_t);
    sprintf(message, "尊敬的 %s 先生/女士\r\n", patient_t->login.name);
    if(status == WITHOUT_APPLICATION)
        sprintf(message, "%s您当前的预约状态是没有预约\r\n", message);
    else if(status == FIRST_VISIT_DOCTOR)
        sprintf(message, "%s您当前的预约状态是预约没有初诊\r\n", message);
    else if(status == SUBSQUENT_VISIT)
        sprintf(message, "%s您当前的预约状态是等待复诊\r\n", message);
}