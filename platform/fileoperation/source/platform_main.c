
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
    printf("����������:%d\r\n", listCURRENT_LIST_LENGTH(&manager.doctors_LM));
    doctor_list = listGET_HEAD_ENTRY(&manager.doctors_LM);
    doctor = (doctor_t *)listGET_LIST_ITEM_OWNER(doctor_list);
    printf("ҽ������Ϣ: %s %s %s\r\n", doctor->login.id, doctor->login.name, doctor->login.passwd);
    platform_init_patient("dong", "222", "123456");
    patient_list = listGET_HEAD_ENTRY(&manager.patient_LM);
    patient = (patient_t *)listGET_LIST_ITEM_OWNER(patient_list);
    printf("���ߵ���Ϣ: %s %s %s\r\n", patient->login.id, patient->login.name, patient->login.passwd);
}

void platform_department_init(void)
{
    //���ų�ʼ��
    FILE *message_f;
    int32_t i, j, management_num, service_num;
    one_department_t *department;
    outpatient_service_t *service;
    ListItem_t *list_test, *list_test2;
    int8_t name[21];
    //ҽ����ʼ��
    int32_t doctor_num;
    int8_t id[21], passwd[21], work[20]; 

    message_f = fopen("document.txt", "r");
    fscanf(message_f, "%d", &management_num);
    printf("*******���ų�ʼ��*****%d\r\n", management_num);
    for(i=0;i<management_num;i++)
    {
        //��ȡ��ʽ���Ĳ�����Ϣ
        fscanf(message_f, "%s %d", name, &service_num);
        department = platform_init_department(name);
        for(j=0;j<service_num;j++)
        {
            //��ʼ�����е�����
            fscanf(message_f, "%s", name);
            platform_init_service(name, department);
        }
    }
    /**/
    printf("������%d������\r\n", manager.departments_LM.uxNumberOfItems);
    list_test = listGET_HEAD_ENTRY(&manager.departments_LM);
    department = listGET_LIST_ITEM_OWNER(list_test);
    for(i=0;i<manager.departments_LM.uxNumberOfItems;i++)
    {
        printf("����%s������%d������\r\n", department->name, department->services_LM.uxNumberOfItems);
        list_test2 = listGET_HEAD_ENTRY(&department->services_LM);
        service = listGET_LIST_ITEM_OWNER(list_test2);
        for(j=0;j<department->services_LM.uxNumberOfItems;j++)
        {
            printf("����%d��: %s\r\n", j+1, service->name);
            list_test2 = listGET_NEXT(list_test2);
            service = listGET_LIST_ITEM_OWNER(list_test2);
        }


        list_test = listGET_NEXT(list_test);
        department = listGET_LIST_ITEM_OWNER(list_test);
    }
    
   if((service = platform_get_service("С���ڿ�"))!= -1)
   {
        printf("�ҵ���%s\r\n", service->name);
   }
    
   fscanf(message_f, "%d", &doctor_num);
   for(i=0;i<doctor_num;i++)
   {
        fscanf(message_f, "%s %s %s %s", id, name, passwd, work);
        platform_init_doctor(name, id, passwd, work);
   }


    fclose(message_f);

}
//�����еĲ��������ȡĳһ������,�����ǲ��ŵ�����
outpatient_service_t * platform_get_service(char *name)
{
    int32_t i, j;
    one_department_t *department;
    outpatient_service_t *service;
    ListItem_t *list_test, *list_test2;
    //��ȡ���ŵ�����
    list_test = listGET_HEAD_ENTRY(&manager.departments_LM);
    department = listGET_LIST_ITEM_OWNER(list_test);
    for(i=0;i<manager.departments_LM.uxNumberOfItems;i++)
    {
        //��ȡĳ�����������
        list_test2 = listGET_HEAD_ENTRY(&department->services_LM);
        service = listGET_LIST_ITEM_OWNER(list_test2);
        for(j=0;j<department->services_LM.uxNumberOfItems;j++)
        {
            if(strcmp(service->name, name)==0)
                return service;
            list_test2 = listGET_NEXT(list_test2);
            service = listGET_LIST_ITEM_OWNER(list_test2);
        }
        list_test = listGET_NEXT(list_test);
        department = listGET_LIST_ITEM_OWNER(list_test);
    }
    return -1;

}



void platform_manage_init()
{
    int i, j;
    strcpy(manager.login.id, "000");
    strcpy(manager.login.name, "manage");   
    strcpy(manager.login.passwd, "123456");   
    vListInitialise(&manager.doctors_LM);
    vListInitialise(&manager.patient_LM);
    vListInitialise(&manager.departments_LM);
    platform_department_init();
}
//����һ��ҽ���ĵĽṹ��,�������ڹ���������
doctor_t * platform_init_doctor(char *name, char *id, char *passwd , char *work)
{
    outpatient_service_t * service;
    doctor_t *doctor_to_init;
    doctor_to_init = malloc(sizeof(doctor_t));
    /**********************�ڵ�ĳ�ʼ��**************************/
    //�����ڹ���������
    vListInitialiseItem(&doctor_to_init->manage_L);
    vListInitialiseItem(&doctor_to_init->service_L);
    vListInsertEnd(&manager.doctors_LM, &doctor_to_init->manage_L);
    printf("%s", work);
    service = platform_get_service(work);
    if(service!=-1){
        vListInsertEnd(&service->doctors_LM, &doctor_to_init->service_L);
    }else{
        printf("ҽ�����ز���ʧ��...");
        while(1);
    }
    //���ظ��ڵ�
    listSET_LIST_ITEM_OWNER(&doctor_to_init->manage_L, doctor_to_init);
    listSET_LIST_ITEM_OWNER(&doctor_to_init->service_L, doctor_to_init);
    vListInitialise(&doctor_to_init->patient_LM);
    /************************************************************/
    //�������ʼ�����ָ�����Ϣ
    strcpy(doctor_to_init->login.id, id);
    strcpy(doctor_to_init->login.name, name);
    strcpy(doctor_to_init->login.passwd, passwd);
    strcpy(doctor_to_init->service, work);

    return doctor_to_init;
}

//����һ�����ŵĵĽṹ��,�������ڹ���������
one_department_t * platform_init_department(char *name)
{
    one_department_t *department;
    department = malloc(sizeof(one_department_t));
    vListInitialise(&department->services_LM);
    vListInitialiseItem(&department->manage_L);
    vListInsertEnd(&manager.departments_LM, &department->manage_L);
    //���ø��ڵ�
    listSET_LIST_ITEM_OWNER(&department->manage_L, department);
    strcpy(department->name, name);
    return department;
}

//����һ������ĵĽṹ��,�������ڲ�������
outpatient_service_t * platform_init_service(char *name, one_department_t* department)
{
    outpatient_service_t *service;
    service = malloc(sizeof(outpatient_service_t));
    vListInitialise(&service->doctors_LM);
    vListInitialiseItem(&service->department_L);
    //fscanf(message_f, "%s", service->name);
    strcpy(service->name, name);
    //��ĳһ������ע�ᵽ��������
    vListInsertEnd(&department->services_LM, &service->department_L);
    listSET_LIST_ITEM_OWNER(&service->department_L, service);
    return service;
}

//����һ�����ߵĵĽṹ��,�������ڹ���������
patient_t * platform_init_patient(char *name, char *id, char *passwd)
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
                return 1;
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
                return 1;
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
    int32_t i, j;
    one_department_t *department;
    outpatient_service_t *service;
    doctor_t *doctor;
    FILE *message_f;
    message_f = fopen("document.txt", "w");
    ListItem_t *list_test2, *list_test;
    //��ȡ���ŵ�����
    fprintf(message_f, "%d\n", manager.departments_LM.uxNumberOfItems);
    list_test = listGET_HEAD_ENTRY(&manager.departments_LM);
    department = listGET_LIST_ITEM_OWNER(list_test);
    for(i=0;i<manager.departments_LM.uxNumberOfItems;i++)
    {
        //����һ������
        fprintf(message_f, "%s %d", department->name, department->services_LM.uxNumberOfItems);
        list_test2 = listGET_HEAD_ENTRY(&department->services_LM);
        service = listGET_LIST_ITEM_OWNER(list_test2);
        for(j=0;j<department->services_LM.uxNumberOfItems;j++)
        {
            fprintf(message_f, " %s", service->name);
            list_test2 = listGET_NEXT(list_test2);
            service = listGET_LIST_ITEM_OWNER(list_test2);
        }
        fprintf(message_f, "\n");
        list_test = listGET_NEXT(list_test);
        department = listGET_LIST_ITEM_OWNER(list_test);
    }
    //����ҽ��
    list_test = listGET_HEAD_ENTRY(&manager.doctors_LM);
    doctor = listGET_LIST_ITEM_OWNER(list_test);
    fprintf(message_f, "%d\n", manager.doctors_LM.uxNumberOfItems);
    for(i=0;i<manager.doctors_LM.uxNumberOfItems;i++)
    {
        fprintf(message_f, "%s %s %s %s\n", doctor->login.id, doctor->login.name, doctor->login.passwd, doctor->service);
        list_test = listGET_NEXT(list_test);
        doctor = listGET_LIST_ITEM_OWNER(list_test);
    }

    fclose(message_f);

}


//ƽ̨�˳�����,��Ҫ�����ͷſռ�
void platform_out()
{
    int32_t i, j;
    ListItem_t *list_now, *list_next;
    doctor_t *doctor;
    patient_t *patient;
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