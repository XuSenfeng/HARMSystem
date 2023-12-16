/**
  ******************************************************************************
  * @file    platform_main.c
  * @version V1.0
  * @date    2023-12-10
  * @brief   ����ļ������ݿ��API��,��Ҫ��Ϊ��ʵ�����ݿ��ʼ��,�˳������Լ���ȡĳһ�����Ƿ������ݿ�����Ľ��,���ڵ�¼
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



#include "platform_main.h"



manager_t manager;





/**
  * @brief  ����һ���˵�id�Լ������ж��Ƿ��½�ɹ�,�ɹ��Ļ����ض�Ӧ���Ǹ��˵Ľṹ��
  * @param  id:��¼��id
  * @param  passwd:��¼������
  * @param  choice:��¼��ѡ��'1'����'2'ҽ��'3'����Ա
  * @retval 1�ɹ� ERRORʧ��
  */
int32_t platform_login(int8_t *id, int8_t *passwd, int8_t choice)
{
    ListItem_t *list_to_use;
    doctor_t *doctor;
    patient_t *patient;
    int num_to_get;
    if(choice == '3')
    {
        //����Ա
        //printf("����Ա��¼\r\n");
        if(platform_is_right(id, passwd, &manager.login)==1)
        {
            return 1;
        }else
            return ERROR;
        
    }else if(choice == '2')
    {
        //ҽ��
        //printf("ҽ����¼\r\n");
        num_to_get = listCURRENT_LIST_LENGTH(&manager.doctors_LM);
        list_to_use = listGET_HEAD_ENTRY(&manager.doctors_LM);
        doctor = (doctor_t *)listGET_LIST_ITEM_OWNER(list_to_use);
        while(num_to_get--)
        {
            if(platform_is_right(id, passwd, &doctor->login)==1){
                return 1;
            }
            list_to_use = listGET_NEXT(list_to_use);
            doctor = (doctor_t *)listGET_LIST_ITEM_OWNER(list_to_use);
        }
        return ERROR;
    }else if(choice == '1')
    {
        //����
        //printf("���ߵ�¼\r\n");
        //��ȡҪ�����Ļ����б��Լ�������Ϣ
        num_to_get = listCURRENT_LIST_LENGTH(&manager.patient_LM);
        list_to_use = listGET_HEAD_ENTRY(&manager.patient_LM);
        patient = (patient_t *)listGET_LIST_ITEM_OWNER(list_to_use);
        //printf("patient=  %s %s\r\n",patient->login.id, patient->login.passwd);
        while(num_to_get--)
        {
            if(platform_is_right(id, passwd, &patient->login)==1){
                return 1;
            }
            list_to_use = listGET_NEXT(list_to_use);
            patient = (patient_t *)listGET_LIST_ITEM_OWNER(list_to_use);
        }
        return ERROR;
    }else
    {
        return (void *)ERROR;
    }
}
/*********************************************ƽ̨����ʹ�õĺ���***********************************************/

/**
  * @brief  ƽ̨���غ���,����ƽ̨�ĳ�ʼ��,��ȡ����
  * @param  ��
  * @retval ��
  */
void platform_init()
{
    platform_manage_init();
#if DEBUG
    platform_test();
#endif
}



/**
  * @brief  ƽ̨�˳�����,��Ҫ�����ͷſռ�,�Լ�������Ϣ
  * @param  ��
  * @retval ��
  */
void platform_out()
{
    int32_t i, j;
    ListItem_t *list_now, *list_next;
    doctor_t *doctor;
    patient_t *patient;
    platform_manage_out();
    //�ѵ�ǰ�����ݴ洢����
    platform_update();
    //�ͷ��ڴ�
    while(listCURRENT_LIST_LENGTH(&manager.doctors_LM))
    {
        list_now = listGET_HEAD_ENTRY(&manager.doctors_LM);
        doctor = listGET_LIST_ITEM_OWNER(list_now);
        uxListRemove(list_now);
        free(doctor);
    }
    while(listCURRENT_LIST_LENGTH(&manager.patient_LM))
    {
        list_now = listGET_HEAD_ENTRY(&manager.patient_LM);
        patient = listGET_LIST_ITEM_OWNER(list_now);
        uxListRemove(list_now);
        free(patient);
    }

    one_department_t *department;
    outpatient_service_t *service;
    ListItem_t *list_test, *list_test2;
    //��ȡ���ŵ�����

    while(listCURRENT_LIST_LENGTH(&manager.departments_LM))
    {
        list_test = listGET_HEAD_ENTRY(&manager.departments_LM);
        department = listGET_LIST_ITEM_OWNER(list_test);
        //��ȡĳ�����������
        while(listCURRENT_LIST_LENGTH(&department->services_LM))
        {
            list_now = listGET_HEAD_ENTRY(&department->services_LM);
            service = listGET_LIST_ITEM_OWNER(list_now);
            uxListRemove(list_now);
            free(service);
        }
        uxListRemove(list_test);
        free(department);
    }
    
}

