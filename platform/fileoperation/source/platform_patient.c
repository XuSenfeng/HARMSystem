#include "platform_patient.h"

void platform_get_patient_login_data(patient_t *patient_t, int8_t *message)
{
    uint32_t status;
    status = platform_get_patient_status(patient_t);
    sprintf(message, "�𾴵� %s ����/Ůʿ\r\n", patient_t->login.name);
    if(status == WITHOUT_APPLICATION)
        sprintf(message, "%s����ǰ��ԤԼ״̬��û��ԤԼ\r\n", message);
    else if(status == FIRST_VISIT_DOCTOR)
        sprintf(message, "%s����ǰ��ԤԼ״̬��ԤԼû�г���\r\n", message);
    else if(status == SUBSQUENT_VISIT)
        sprintf(message, "%s����ǰ��ԤԼ״̬�ǵȴ�����\r\n", message);
}