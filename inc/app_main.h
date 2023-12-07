#ifndef APP_MAIN_H
#define APP_MAIN_H
#include "list.h"
void platform_test(void);
//��¼��Ϣ
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


#endif // !APP_MAIN_H