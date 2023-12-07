#ifndef PLATFORM_MAIN_H
#define PLATFORM_MAIN_H
#include "type.h"
#include "list.h"
#include "app_main.h"
typedef struct
{
    char id[21];
    char name[21];
    char passwd[31];
}message_to_login_t;

//ҽԺҽ���ṹ�Ľṹ��,��ʵ��
typedef struct{

}department_t;

//�����ߵĶ���
typedef struct {
    message_to_login_t login;   //��¼��Ϣ
    List_t doctors_LM;       //�������е�ҽ��
    List_t patient_LM;      //�������еĲ���
}manager_t;


//ҽ���Ķ���
typedef struct 
{
    message_to_login_t login;   //��¼��Ϣ
    ListItem_t manage_L;    //���Լ��Ĺ���ڵ�
    List_t patient_LM;       //�����������в��˵Ĺ���ڵ�
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
doctor_t * platform_get_doctor(char *name, char *id, char *passwd);
int32_t platform_login(int8_t *id, int8_t *passwd, int8_t choice);
patient_t * platform_get_patient(char *name, char *id, char *passwd);
#endif /*PLATFORM_MAIN_H*/
