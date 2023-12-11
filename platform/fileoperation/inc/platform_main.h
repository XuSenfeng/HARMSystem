#ifndef PLATFORM_MAIN_H
#define PLATFORM_MAIN_H
#include "type.h"
#include "list.h"
#include "app_main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
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
//������Ϣ�ṹ��
typedef struct
{
    int8_t id[21];      //id
    int8_t name[21];    //����
    int8_t passwd[31];  //����
}message_to_login_t;

//�������ҵĽṹ��
typedef struct{
    int8_t name[20];        //���������
    ListItem_t department_L;    //���ڵĲ���
    List_t doctors_LM;      //���������ҽ��
}outpatient_service_t;

//�����Ĳ��� 
typedef struct 
{
    int8_t name[20];        //���ŵ�����
    ListItem_t manage_L;    //�����������ڵĹ�����
    List_t services_LM;     //�������������
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
    ListItem_t service_L;   //��ĳһ���������������
    List_t patient_LM;       //�����������в��˵Ĺ���ڵ�
    int8_t service[21];     //����ҽ���Ĳ��ŵ�����
    int8_t level[30];       //����ҽ���ĵȼ�������
    int8_t workday[15];     //����ҽ���Ĺ���ʱ����Ϣ
    int32_t num_to_accept;  //����ҽ�����ĽӴ���
}doctor_t;

//���˵Ķ���
typedef struct{
    message_to_login_t login;       //��¼��Ϣ
    ListItem_t manage_L;            //����ڵ�
    ListItem_t doctor_L;            //ҽ���ڵ�
    int8_t doc_id[21];              //�Լ���ҽ����id
    int8_t message[140];            //ҽ������������Ϣ
}patient_t;

void platform_init();
void platform_out();
int32_t platform_login(int8_t *id, int8_t *passwd, int8_t choice);
#endif /*PLATFORM_MAIN_H*/
