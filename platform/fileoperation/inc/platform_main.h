#ifndef PLATFORM_MAIN_H
#define PLATFORM_MAIN_H
#include "type.h"
#include "list.h"
#include "app_main.h"
typedef struct
{
    int8_t id[21];
    int8_t name[21];
    int8_t passwd[31];
}message_to_login_t;

//�������ҵĽṹ��
typedef struct{
    int8_t name[20];
    ListItem_t department_L;
    List_t doctors_LM;
}outpatient_service_t;
//�����ڿƵĽṹ��

//����������
typedef struct 
{
    int8_t name[20];
    ListItem_t manage_L;    //�����������ڵĹ�����
    List_t services_LM;
}one_department_t;


//�����ߵĶ���
typedef struct {
    message_to_login_t login;   //��¼��Ϣ
    List_t doctors_LM;       //�������е�ҽ��
    List_t patient_LM;      //�������еĲ���
    List_t departments_LM;
}manager_t;


//ҽ���Ķ���
typedef struct 
{
    message_to_login_t login;   //��¼��Ϣ
    ListItem_t manage_L;    //���Լ��Ĺ���ڵ�
    ListItem_t service_L;
    List_t patient_LM;       //�����������в��˵Ĺ���ڵ�
    char service[21];
}doctor_t;

//���˵Ķ���
typedef struct{
    message_to_login_t login;
    ListItem_t manage_L;
    ListItem_t doctor_L;
}patient_t;

void platform_init();
void platform_out();
void platform_manage_init();
doctor_t * platform_init_doctor(char *name, char *id, char *passwd , char *work);
int32_t platform_login(int8_t *id, int8_t *passwd, int8_t choice);
patient_t * platform_init_patient(char *name, char *id, char *passwd);
outpatient_service_t * platform_get_service(char *name);
one_department_t * platform_init_department(char *name);
outpatient_service_t * platform_init_service(char *name, one_department_t* department);

#endif /*PLATFORM_MAIN_H*/
