#ifndef APP_DOCTOR_H
#define APP_DOCTOR_H
#include "app_main.h"
/****************����******************/
//��ȡ�Լ��ĵ�¼��Ϣ
#define COMMEND_DOC_GET_SELF_DATA           1
//��ȡ�Լ��Ĳ��˵�����
#define COMMEND_DOC_GET_PAT_NUM             2
//��ȡ���˵���Ϣ
#define COMMEND_DOC_GET_PAT_DTA_D           3
//��ȡ���ڵ�һ�����˵���Ϣ
#define COMMEND_DOC_GET_FIRST_PAT           4
//�Բ��˽�������
#define COMMEND_DOC_DEAL_FST_PAT            5
//����һ�����˷�����Ϣ
#define COMMEND_DOC_ADD_PAT_MSG             6



//��ʾ���˵�ʱ��Ĳ���
#define MESSAGE_STEP                       5
void app_doctor_dealwith(base_data *login_data);
int32_t app_doctor_login(base_data *login_data);


#endif // !APP_DOCTOR_H