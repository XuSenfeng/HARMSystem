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
//��ȡĳһ��ҽ���Ĺ���ʱ����Ϣ
#define COMMEND_PAT_GET_DOC_TIME        7
//ɾ���Լ���ԤԼ
#define COMMEND_PAT_DEL_DOC_APLY        8
//ͨ��id��ȡĳһ��ҽ������Ϣ
#define COMMEND_PAT_GET_DOC_MSG_id      9
//ͨ��ʱ���ȡĳҽ������Ϣ
#define COMMEND_PAT_GET_DOC_MSG_TIM_NUM 10
//��ȡҽ������Ϣͨ��ʱ��
#define COMMEND_PAT_GET_DOC_DTA_T       11

//��ʾ��Ϣ��ʱ��Ĳ���
#define MESSAGE_STEP                    10
#define MESSAGE_STEP_L                  5

void app_patient_dealwith(base_data *login_data);
int32_t app_patient_login(base_data *login_data);

#endif // !APP_PATIENT_H