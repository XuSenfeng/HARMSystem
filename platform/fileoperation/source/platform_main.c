
#include "platform_main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
manager_t manager;
void platform_test(void)
{
    ListItem_t * doctor_list, * patient_list;
    doctor_t * doctor;
    patient_t * patient;
    printf("platform\r\n");
    platform_get_doctor("jiao", "111", "123456");
    printf("����������:%d\r\n", listCURRENT_LIST_LENGTH(&manager.doctors_LM));
    doctor_list = listGET_HEAD_ENTRY(&manager.doctors_LM);
    doctor = (doctor_t *)listGET_LIST_ITEM_OWNER(doctor_list);
    printf("ҽ������Ϣ: %s %s %s\r\n", doctor->login.id, doctor->login.name, doctor->login.passwd);
    platform_get_patient("dong", "222", "123456");
    patient_list = listGET_HEAD_ENTRY(&manager.patient_LM);
    patient = (patient_t *)listGET_LIST_ITEM_OWNER(patient_list);
    printf("���ߵ���Ϣ: %s %s %s\r\n", patient->login.id, patient->login.name, patient->login.passwd);
}
void platform_manage_init()
{
    strcpy(manager.login.id, "000");
    strcpy(manager.login.name, "manage");   
    strcpy(manager.login.passwd, "123456");   
    vListInitialise(&manager.doctors_LM);
    vListInitialise(&manager.patient_LM);
}
//����һ��ҽ���ĵĽṹ��,�������ڹ���������
doctor_t * platform_get_doctor(char *name, char *id, char *passwd)
{
    doctor_t *doctor_to_init;
    doctor_to_init = malloc(sizeof(doctor_t));
    /**********************�ڵ�ĳ�ʼ��**************************/
    //�����ڹ���������
    vListInitialiseItem(&doctor_to_init->manage_L);
    vListInsertEnd(&manager.doctors_LM, &doctor_to_init->manage_L);
    //���ظ��ڵ�
    doctor_to_init->manage_L.pvOwner = doctor_to_init;
    vListInitialise(&doctor_to_init->patient_LM);
    /************************************************************/
    //�������ʼ�����ָ�����Ϣ
    strcpy(doctor_to_init->login.id, id);
    strcpy(doctor_to_init->login.name, name);
    strcpy(doctor_to_init->login.passwd, passwd);


    return doctor_to_init;
}

//����һ�����ߵĵĽṹ��,�������ڹ���������
patient_t * platform_get_patient(char *name, char *id, char *passwd)
{
    patient_t *patient_to_init;
    patient_to_init = malloc(sizeof(patient_t));
    /**********************�ڵ�ĳ�ʼ��**************************/
    //�����ڹ���������
    vListInitialiseItem(&patient_to_init->manage_L);
    vListInitialiseItem(&patient_to_init->doctor_L);
    vListInsertEnd(&manager.patient_LM, &patient_to_init->manage_L);
    //���ظ��ڵ�
    patient_to_init->manage_L.pvOwner = (void *)patient_to_init;
    /************************************************************/
    //�������ʼ�����ָ�����Ϣ
    strcpy(patient_to_init->login.id, id);
    strcpy(patient_to_init->login.name, name);
    strcpy(patient_to_init->login.passwd, passwd);
    
    return patient_to_init;
}


//����һ�����������Ϣ�ж��ǲ�����ȷ��
int platform_is_right(char *id, char *passwd, message_to_login_t * message)
{
    if((strcmp(id, message->id)==0) && (strcmp(passwd, message->passwd)==0))
    {

        return 1;
    }else{
        return -1;
    }
}

//����һ���˵�id�Լ������ж��Ƿ��½�ɹ�,�ɹ��Ļ����ض�Ӧ���Ǹ��˵Ľṹ��
void *platform_login(int8_t *id, int8_t *passwd, int8_t choice)
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
            return &manager;
        }else
            return -1;
        
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
                return doctor;
            }
            list_to_use = listGET_NEXT(list_to_use);
            doctor = (doctor_t *)listGET_LIST_ITEM_OWNER(list_to_use);
        }
        return -1;
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
                return patient;
            }
            list_to_use = listGET_NEXT(list_to_use);
            patient = (patient_t *)listGET_LIST_ITEM_OWNER(list_to_use);
        }
        return -1;
    }else
    {
        return (void *)-1;
    }
}
/*********************************************ƽ̨����ʹ�õĺ���***********************************************/
//ƽ̨���غ���,����ƽ̨�ĳ�ʼ��,��ȡ����
void platform_init()
{
    platform_manage_init();
    platform_test();
}
//�������ڵ�����,������д�뵽�ļ�����
void platform_update(){

}


//ƽ̨�˳�����,��Ҫ�����ͷſռ�
void platform_out()
{
    doctor_t *doctor;
    patient_t *patient;
    //�ѵ�ǰ�����ݴ洢����
    platform_update();
    //�ͷ��ڴ�
    while(listCURRENT_LIST_LENGTH(&manager.doctors_LM))
    {
        doctor = listGET_HEAD_ENTRY(&manager.doctors_LM);
        uxListRemove(doctor);
    }
    while(listCURRENT_LIST_LENGTH(&manager.patient_LM))
    {
        patient = listGET_HEAD_ENTRY(&manager.patient_LM);
        uxListRemove(doctor);
    }
}