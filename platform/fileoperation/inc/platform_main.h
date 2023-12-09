#ifndef PLATFORM_MAIN_H
#define PLATFORM_MAIN_H
#include "type.h"
#include "list.h"
#include "app_main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//ԤԼ״̬
#define WITHOUT_APPLICATION             0
#define FIRST_VISIT_DOCTOR              1
#define SUBSQUENT_VISIT                 2

/*֪��ר�ҡ�����ҽʦ��������ҽʦ������ҽʦ��ҽʦ��*/
#define DOC_LEVE_1              "֪��ר��"
#define DOC_LEVE_2              "����ҽʦ"
#define DOC_LEVE_3              "������ҽʦ"
#define DOC_LEVE_4              "����ҽʦ"
#define DOC_LEVE_5              "ҽʦ"




//���Դ��뿪��
#define DEBUG                           0
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
    int8_t service[21];
    int8_t level[30];
    int8_t workday[15];
    int32_t num_to_accept;
}doctor_t;

//���˵Ķ���
typedef struct{
    message_to_login_t login;
    ListItem_t manage_L;
    ListItem_t doctor_L;
    char doc_id[21];
}patient_t;

void platform_init();
void platform_out();
int32_t platform_login(int8_t *id, int8_t *passwd, int8_t choice);
outpatient_service_t * platform_get_service(char *name);
void platform_department_init(int8_t *file_name);
#endif /*PLATFORM_MAIN_H*/
