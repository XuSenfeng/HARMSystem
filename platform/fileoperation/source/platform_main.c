
#include "platform_main.h"

manager_t manager;
void platform_test(void)
{
    uint32_t ret;
    ListItem_t * doctor_list, * patient_list;
    doctor_t * doctor;
    patient_t * patient;
    printf("platform\r\n");
    printf("����������:%d\r\n", listCURRENT_LIST_LENGTH(&manager.doctors_LM));
    doctor_list = listGET_HEAD_ENTRY(&manager.doctors_LM);
    doctor = (doctor_t *)listGET_LIST_ITEM_OWNER(doctor_list);
    printf("ҽ������Ϣ: %s %s %s\r\n", doctor->login.id, doctor->login.name, doctor->login.passwd);
    platform_add_patient("ʷ����", "222", "123456", 0, "1001");
    patient_list = listGET_HEAD_ENTRY(&manager.patient_LM);
    patient = (patient_t *)listGET_LIST_ITEM_OWNER(patient_list);
    printf("���ߵ���Ϣ: %s %s %s\r\n", patient->login.id, patient->login.name, patient->login.passwd);
    platform_patient_appointment(patient, "1001");
    ret = platform_get_patient_status(patient);
    if(ret==WITHOUT_APPLICATION)
    {
        printf("û��ԤԼ\r\n");
    }
    else if(ret = 1)
    {
        printf("ԤԼ�ɹ�\r\n");
    }

}
//���ļ����ж�����
void platform_department_init(void)
{
    //���ų�ʼ��
    FILE *message_f;
    int32_t i, j, management_num, service_num, patient_num;
    one_department_t *department;
    outpatient_service_t *service;

    int8_t name[21];
    //ҽ����ʼ��
    int32_t doctor_num;
    int8_t id[21], passwd[30], work[20], status; 

    message_f = fopen("document.txt", "r");
    fscanf(message_f, "%d", &management_num);
    //printf("*******���ų�ʼ��*****%d\r\n", management_num);
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
#if DEBUG
    ListItem_t *list_test, *list_test2;
    /*���Դ���, ����ʾ�����Ѿ�ע������еĲ����Լ�����*/
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
#endif
    //������ע�����ҽ��
   fscanf(message_f, "%d", &doctor_num);
   for(i=0;i<doctor_num;i++)
   {
        fscanf(message_f, "%s %s %s %s", id, name, passwd, work);
        platform_add_doctor(name, id, passwd, work);
   }
    //������ע�Ს��
    fscanf(message_f, "%d", &patient_num);
   for(i=0;i<patient_num;i++)
   {
        fscanf(message_f, "%s %s %s %c %s", id, name, passwd, &status, work);
        platform_add_patient(name, id, passwd, status ,work);
   }
#if DEBUG
    patient_t *patient;
    list_test = listGET_HEAD_ENTRY(&manager.patient_LM);
    patient = listGET_LIST_ITEM_OWNER(list_test);
    printf("һ����%d������\r\n", manager.patient_LM.uxNumberOfItems);
    for(i=0;i<manager.patient_LM.uxNumberOfItems;i++)
    {
        printf("���� %d �������� %s ���ڵ�״̬�� %d\r\n", i+1, patient->login.name, patient->doctor_L.xItemValue);
        list_test = listGET_NEXT(list_test);
        patient = listGET_LIST_ITEM_OWNER(list_test);
    }
#endif

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
#if DEBUG
    platform_test();
#endif
}
//�������ڵ�����,������д�뵽�ļ�����
void platform_update(){
    int32_t i, j;
    one_department_t *department;
    outpatient_service_t *service;
    doctor_t *doctor;
    patient_t *patient;
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
    //���벡��
    list_test = listGET_HEAD_ENTRY(&manager.patient_LM);
    patient = listGET_LIST_ITEM_OWNER(list_test);
    fprintf(message_f, "%d\n", manager.patient_LM.uxNumberOfItems);
    for(i=0;i<manager.patient_LM.uxNumberOfItems;i++)
    {
        fprintf(message_f, "%s %s %d %s %s\n", patient->login.id, patient->login.name, patient->doctor_L.xItemValue,patient->login.passwd,  patient->doc_id);
        list_test = listGET_NEXT(list_test);
        patient = listGET_LIST_ITEM_OWNER(list_test);
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

void platform_get_login_data(int8_t choice, char *message, char *id)
{
    patient_t *patient;
    if(choice == '1')
    {

        patient = platform_get_patient(id);
        if(patient!=NULL)
            platform_get_patient_login_data(patient, message);
        else
            sprintf(message, "��ȡʧ��%s\r\n", id);
    }
}
