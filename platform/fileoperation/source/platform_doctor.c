#include "platform_doctor.h"

void platform_get_doctor_login_data(doctor_t *doctor, int8_t * message)
{
    sprintf(message, " %s ҽ������\r\n", doctor->login.name);
    sprintf(message, "%s����ǰ��%d�����˴�����\r\n", message,doctor->patient_LM.uxNumberOfItems);
    
}

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
//��ȡҽ�����׸����˵���Ϣ,�������ҽ��
void platform_doctor_get_first_pat(doctor_t *doctor, int8_t* message){
    ListItem_t *list_pat;
    patient_t *patient;
    if(doctor->patient_LM.uxNumberOfItems>0)
    {
        list_pat = listGET_HEAD_ENTRY(&doctor->patient_LM);
        patient = listGET_LIST_ITEM_OWNER(list_pat);
        sprintf(message, "�ɹ���ȡ��һλ����,��Ϊ����ȡ������Ϣ....\r\n");
        sprintf(message, "%s������˵������� %s\r\n", message, patient->login.name);
        sprintf(message, "%s����ǰ��״̬�� %s \r\n", message, patient->doctor_L.xItemValue=='0'?"��û�г���":"����ĵȴ�����");

    }else
    {
        sprintf(message, "������û�в��˵ȴ�����,�����ĵȴ�...\r\n");
    }
}
//ҽ���Բ��˽�������
void platform_doctor_deal_first_pat(doctor_t *doctor,int8_t *message, int8_t choice)
{
    ListItem_t *list_pat;
    patient_t *patient;
    if(doctor->patient_LM.uxNumberOfItems>0)
    {
        list_pat = listGET_HEAD_ENTRY(&doctor->patient_LM);
        patient = listGET_LIST_ITEM_OWNER(list_pat);
        if(choice == '1'){
            platform_doc_deal_pat(doctor, patient, '1');
            sprintf(message, "�Ѿ����ƹ���,���˻���֮����и���\r\n");
        }
        else if(choice == '2'){
            platform_doc_deal_pat(doctor, patient, '2');
            sprintf(message, "�Ѿ����ƹ���, ��ϲ����Ȭ��!!!\r\n");

        }
        else if(choice == '3'){
            platform_doc_deal_pat(doctor, patient, '3');
            sprintf(message, "�Ѿ��ò����Ʋ�����������\r\n");
        }

    }else
    {
        sprintf(message, "������û�в���....\r\n�����ĵȴ�\r\n");
    }
}

//������û���ƽ̨�ӿ�,�����������Ϣ
void platform_doctor_commend(int8_t commend, int8_t *id, int8_t *message, void *parameter)
{
    
    doctor_t *doctor;
    int32_t ret;
    doctor = platform_get_doc(id);
    //printf("��ȡҽ����Ϣ%s", doctor->login.name);while(1);
    int32_t *p;
    int8_t (*p_8)[30];
    int8_t id_n[21];

    if(doctor != -1)
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
            platform_doctor_get_first_pat(doctor, message);
            break;
        case 5:
            platform_doctor_deal_first_pat(doctor, message, parameter);
            break;
        case 6:

            break;
        default:
            break;
        }
    }else
    {
        sprintf(message, "��ȡҽ��ʧ��\r\n");
    }
}