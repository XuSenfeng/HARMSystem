#ifndef APP_MANAGE_H
#define APP_MANAGE_H
#include "app_main.h"
/*************����****************/
//��ȡ�Լ��ĵ�¼��Ϣ
#define COMMEND_MAN_GET_SELF_DATA       1
//��ȡ���ڵĲ��˵�����
#define COMMEND_MAN_GET_PAT_NUM         2
//��ȡ���˵���Ϣ
#define COMMEND_MAN_GET_PAT_DATA        3
//��ȡĳһ��ҽ������Ϣͨ��id
#define COMMEND_MAN_GET_DOC_BY_id       4
//ɾ��ĳһ��ҽ��ͨ��id
#define COMMEND_MAN_DEL_DOC_BY_id       5
//����ĳһ��ҽ����ĳһ����Ϣ
#define COMMEND_MAN_CHG_DOC_BY_id       6
//ͨ���ļ������Ϣ
#define COMMEND_MAN_ADD_MSG_BY_FILE     7
//���һ���µ�ҽ��
#define COMMEND_MAN_ADD_NEW_DOC         8
//��ȡĳһ�����˵���Ϣͨ��id
#define COMMEND_MAN_GET_ONE_PAT         9
//ɾ��ĳһ������
#define COMMEND_MAN_DEL_PAT_BY_id       10
//�޸�ĳһ������
#define COMMEND_MAN_CHG_PAT_BY_id       11
//�޸�ĳһ������
#define COMMEND_MAN_GET_OTHER_MSG       12

/*֪��ר�ҡ�����ҽʦ��������ҽʦ������ҽʦ��ҽʦ��*/
#define DOC_LEVE_1              "֪��ר��"
#define DOC_LEVE_2              "����ҽʦ"
#define DOC_LEVE_3              "������ҽʦ"
#define DOC_LEVE_4              "����ҽʦ"
#define DOC_LEVE_5              "ҽʦ"


#define MESSAGE_STEP                    5

void platform_patient_getdoc_data_L(int8_t *message, int32_t begin, int32_t num);
void app_manage_dealwith(base_data *login_data);
int32_t app_manage_login(base_data *login_data);
#endif // !APP_MANAGE_H
