#ifndef APP_PATIENT_H
#define APP_PATIENT_H
#include "app_main.h"
#include <conio.h>
/*************����************/
//��ȡ�Լ��ĵ�¼��Ϣ
#define COMMEND_PAT_GET_SELF_DATA       1
//��ȡҽ��������
#define COMMEND_PAT_SET_DOC_NUM         2
//����ĳһ��ҽ��
#define COMMEND_PAT_APP_DOC             3
//��ȡҽ����Ϣͨ������
#define COMMEND_PAT_GET_DOC_DTA_D       4
//����һ���µĲ���
#define COMMEND_PAT_APLY_NEW_PAT        5
//��ȡҽ������Ϣͨ��ְ��
#define COMMEND_PAT_GET_DOC_DTA_L       6




//��ʾ��Ϣ��ʱ��Ĳ���
#define MESSAGE_STEP                    2
#define MESSAGE_STEP_L                  5

void app_patient_dealwith(base_data *login_data);
int32_t app_patient_login(base_data *login_data);

#endif // !APP_PATIENT_H