/**
  ******************************************************************************
  * @file    platform_dictor.c
  * @version V1.0
  * @date    2023-12-10
  * @brief   ����ļ������ݿ��API��,��Ҫ��Ϊ��ʵ��ҽ��������API����
  * @author  XvSenfeng(������)
  ******************************************************************************
  * @attention
  * ��������XvSenfeng��������ѿ�Դ����
  * ���������鿴��ʹ�ú��޸ģ���Ӧ�õ��Լ�����Ŀ֮��
  * �����Ȩ��XvSenfeng���У��κ��˻���֯���ý����Ϊ����
  * ����㷢�ֳ����е�©�����߱��󣬿�ͨ���ʼ������Ƿ�����1458612070@qq.com
  * �����ʼ�֮ǰ��������ȵ����¶�̬ҳ��鿴���³�������������Ѿ��޸ģ��������ٷ��ʼ�
  * https://github.com/XuSenfeng
  ******************************************************************************
  */ 

#include "platform_doctor.h"


/**
  * @brief  ��ȡҽ���ĵ�¼ʱ����ʾ��
  * @param  ҽ���ṹ��ָ��ָ����Ҫ��ȡ��Ϣ��ҽ��
  * @param  ��ȡ������ϢӦ�ñ���Ľṹ��
  * @retval ��
  */
void platform_get_doctor_login_data(doctor_t *doctor, int8_t * message)
{
    sprintf(message, " %s ҽ������\r\n", doctor->login.name);
    sprintf(message, "%s����ǰ��%d�����˴�����\r\n", message,doctor->patient_LM.uxNumberOfItems);
    
}
/**
  * @brief  ��ȡҽ���Ĳ��˲�����Ϣ
  * @param  ҽ���ṹ��ָ��ָ����Ҫ��ȡ��Ϣ��ҽ��
  * @param  ��ȡ������ϢӦ�ñ���Ľṹ��
  * @param  ��ʼ�Ĳ��˵�λ��
  * @param  �����Ĳ��˵�λ��
  * @retval ��
  */
void platform_doctor_getpat_data(doctor_t *doctor, int8_t *message, int32_t begin, int32_t num){

    patient_t *patient;
    outpatient_service_t *service;
    int32_t i, k=0;
    ListItem_t *list_test;
    //��ջ�����

    sprintf(message, "\0");
    /*���Դ���, ����ʾ�����Ѿ�ע������еĲ����Լ�����*/
    list_test = listGET_HEAD_ENTRY(&doctor->patient_LM);
    patient = listGET_LIST_ITEM_OWNER(list_test);
    
    for(i=0;i<doctor->patient_LM.uxNumberOfItems;i++)
    {
        if(k>=begin && k<begin + num)
            sprintf(message, "%s ����%d�� %s %s ��ǰ��״̬�� %d\r\n", 
            message, k+1,
            patient->login.name, patient->login.id, 
            patient->doctor_L.xItemValue);
        
        k++;
        list_test = listGET_NEXT(list_test);
        patient = listGET_LIST_ITEM_OWNER(list_test);

    }

}

/**
  * @brief  ��ȡҽ�����׸����˵���Ϣ,�������ҽ��,û�в��˵�ʱ��Ҳ���ж�Ӧ�Ĵ���
  * @param  ҽ���ṹ��ָ��ָ����Ҫ��ȡ��Ϣ��ҽ��
  * @param  ��ȡ������ϢӦ�ñ���Ľṹ��
  * @retval ��
  */
void platform_doctor_get_first_pat(doctor_t *doctor, int8_t* message){
    ListItem_t *list_pat;
    patient_t *patient;
    if(doctor->patient_LM.uxNumberOfItems>0)
    {
        //��ҽ���д�����Ĳ��˵�ʱ��
        list_pat = listGET_HEAD_ENTRY(&doctor->patient_LM);
        patient = listGET_LIST_ITEM_OWNER(list_pat);
        sprintf(message, "�ɹ���ȡ��һλ����,��Ϊ����ȡ������Ϣ....\r\n");
        sprintf(message, "%s������˵������� %s\r\n", message, patient->login.name);
        sprintf(message, "%s����ǰ��״̬�� %s \r\n", message, patient->doctor_L.xItemValue=='0'?"��û�г���":"����ĵȴ�����");

    }else
    {
        //û��Ҫ����Ĳ���
        sprintf(message, "������û�в��˵ȴ�����,�����ĵȴ�...\r\n");
    }
}
/**
  * @brief  ҽ���Բ��˽�������
  * @param  ҽ���ṹ��ָ��ָ����Ҫ��ȡ��Ϣ��ҽ��
  * @param  ��ȡ������ϢӦ�ñ���Ľṹ��
  * @param  ����Ĵ���ʽ '1'������Ҫ���� '2'���˲���Ҫ���� '3'�ò���ȥ����������
  * @retval ��
  */
void platform_doctor_deal_first_pat(doctor_t *doctor,int8_t *message, int8_t choice)
{
    ListItem_t *list_pat;
    patient_t *patient;
    if(doctor->patient_LM.uxNumberOfItems>0)
    {
        //�п������ƵĲ���
        list_pat = listGET_HEAD_ENTRY(&doctor->patient_LM);
        patient = listGET_LIST_ITEM_OWNER(list_pat);
        sprintf(patient->message, "\0");
        if(choice == '1'){
            platform_doc_deal_pat(doctor, patient, '1');
            sprintf(message, "�Ѿ����ƹ���,���˻���֮����и���\r\n");
            sprintf(patient->message, "�Ѿ����ƹ���,��֮����и���");
        }
        else if(choice == '2'){
            platform_doc_deal_pat(doctor, patient, '2');
            sprintf(message, "�Ѿ����ƹ���, ��ϲ����Ȭ��!!!\r\n");
            sprintf(patient->message, "�Ѿ����ƹ���,��ϲ����Ȭ��!!!");
        }
        else if(choice == '3'){
            platform_doc_deal_pat(doctor, patient, '3');
            sprintf(message, "�Ѿ��ò����Ʋ�����������\r\n");
            sprintf(patient->message, "�����Ʋ�����������");
        }

    }else
    {
        sprintf(message, "������û�в���....\r\n�����ĵȴ�\r\n");
    }
}
/**
  * @brief  ҽ�������˷���Ϣ
  * @param  ҽ���ṹ��ָ��ָ����Ҫ��ȡ��Ϣ��ҽ��
  * @param  ��ȡ������ϢӦ�ñ���Ľṹ��
  * @param  Ҫ���͵���Ϣ
  * @retval ��
  */
void platform_doctor_send_msg(doctor_t *doctor,int8_t *message, int8_t *doc_msg){
    ListItem_t *list_pat;
    patient_t *patient;
    if(doctor->patient_LM.uxNumberOfItems>0)
    {
        sprintf(patient->message, "\0");
        //�п��Դ�����Ϣ�Ĳ���
        list_pat = listGET_HEAD_ENTRY(&doctor->patient_LM);
        patient = listGET_LIST_ITEM_OWNER(list_pat);
        sprintf(patient->message, "%s", doc_msg);
        sprintf(message, "��ӳɹ�\r\n");
    }else
    {
        sprintf(message, "������û�в���....\r\n�����ĵȴ�\r\n");
    }

}
/**
  * @brief  ������û���ƽ̨�ӿ�,�����������Ϣ
  * @param  ����
  * @param  ��¼��ҽ����id
  * @param  ��ȡ������ϢӦ�ñ���Ľṹ��
  * @param  ��������
  * @retval ��
  */
void platform_doctor_commend(int8_t commend, int8_t *id, int8_t *message, void *parameter)
{
    
    doctor_t *doctor;
    int32_t ret;
    doctor = platform_get_doc(id);
    //printf("��ȡҽ����Ϣ%s", doctor->login.name);while(1);
    int32_t *p;
    int8_t (*p_8)[30];
    int8_t id_n[21];
    if(doctor != ERROR)
    {
        switch (commend)
        {
        case 1:
            //��ȡ��¼��Ϣ
            platform_get_doctor_login_data(doctor, message);
            break;
        case 2:
            //��ȡ�ж��ٵĲ��˴�����
            *(int *)parameter = listCURRENT_LIST_LENGTH(&doctor->patient_LM);
            break;
        case 3:
            //��ȡҽ���Ĳ��ֲ�����Ϣ
            p = parameter;
            platform_doctor_getpat_data(doctor, message, *p, *(p+1));
            break;
        case 4:
            /*��ȡ��һ�����˵���Ϣ,
            �ڶ���������һ������,����λint32λ������,��һ����������ʼ�ĸ���,�ڶ��������ǽ���������*/
            platform_doctor_get_first_pat(doctor, message);
            break;
        case 5:
            /*���Ƶ�һ������
            ���������Ƶķ�ʽint8_t����
            '1': ��һ������
            '2': ���ƽ���
            '3': ������,��������*/
            platform_doctor_deal_first_pat(doctor, message, parameter);
            break;
        case 6:
            /*���һ�����˷�����Ϣ
            ������Ҫ���͵���Ϣ*/
            platform_doctor_send_msg(doctor, message, parameter);
            break;
        default:
            break;
        }
    }else
    {
        sprintf(message, "��ȡҽ��ʧ��\r\n");
    }
}