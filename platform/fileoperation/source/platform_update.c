#include "platform_update.h"
extern manager_t manager;
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
static doctor_t * platform_init_doctor(char *name, char *id, char *passwd , char *work)
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
doctor_t * platfor_add_doctor(char *name, char *id, char *passwd , char *work)
{
    int32_t i = listCURRENT_LIST_LENGTH(&manager.doctors_LM);
    int8_t flog = 0;
    ListItem_t *list_doc = listGET_HEAD_ENTRY(&manager.doctors_LM);
    doctor_t  *doctor = listGET_LIST_ITEM_OWNER(list_doc);
    while(i--)
    {
        
        if(strcmp(id, doctor->login.id)==0)
        {
            printf("id = %s %s\r\n", id, doctor->login.id);
            flog=1;
        }
        list_doc = listGET_NEXT(list_doc);
        doctor = listGET_LIST_ITEM_OWNER(list_doc);
    }
    if(flog==0)
    {
        doctor = platform_init_doctor(name, id, passwd , work);
    }else
    {
        printf("���ҽ�� %s ��� %s ʧ��,�벻Ҫ�����ظ��ı�ŵ�ҽ��...\r\n", name, id);
        return -1;
    }
    return doctor;
}

int32_t platform_get_doc(char *id)
{
    doctor_t *doctor=NULL;
    ListItem_t *doc_list;
    int i, flog=0;
    doc_list = listGET_HEAD_ENTRY(&manager.doctors_LM);
    doctor = listGET_LIST_ITEM_OWNER(doc_list);
    i = listGET_ITEM_VALUE_OF_HEAD_ENTRY(&manager.doctors_LM);
    while(i--)
    {
        if(strcmp(doctor->login.id, id)==0)
        {
            flog=1;
            break;
        }
        doc_list = listGET_NEXT(doc_list);
        doctor = listGET_LIST_ITEM_OWNER(doc_list);
    }
    if(flog)
    {
        return doctor;
    }else{
        return NULL;
    }
}
int32_t platform_get_patient(char *id)
{
    patient_t *patient=NULL;
    ListItem_t *pat_list;
    int i, flog=0;
    pat_list = listGET_HEAD_ENTRY(&manager.patient_LM);
    patient = listGET_LIST_ITEM_OWNER(pat_list);
    i = listCURRENT_LIST_LENGTH(&manager.patient_LM);
    while(i--)
    {
        if(strcmp(patient->login.id, id)==0)
        {
            flog=1;
            break;
        }
        pat_list = listGET_NEXT(pat_list);
        patient = listGET_LIST_ITEM_OWNER(pat_list);
    }
    if(flog)
    {
        return patient;
    }else{
        return NULL;
    }
}
int32_t platform_patient_appointment(patient_t *patient, char *doc_id)
{
    doctor_t *doctor=NULL;
    ListItem_t doc_list;
    int i;
    doctor = platform_get_doc(doc_id);
    if(doctor!=NULL)
    {
        printf("�Ѿ�ԤԼ��ҽ�� %s \r\n", doctor->login.name);
        vListInsertEnd(&doctor->patient_LM, &patient->doctor_L);
        patient->doctor_L.xItemValue = 1;
        return 1;
    }else{
        printf("ҽ��������\r\n");
        return -1;
    }

}
//ɾ��һ��ҽ��
void platform_del_doctor(doctor_t *doctor)
{
    ListItem_t *list;
    //�����ҽ������ϵ����ɾ����ȥ
    uxListRemove(&doctor->manage_L);
    uxListRemove(&doctor->service_L);
     
    while(listCURRENT_LIST_LENGTH(&doctor->patient_LM))
    {
        //������һ��ҽ�������еĲ��˵�״̬Ϊû��ԤԼ
        list = listGET_HEAD_ENTRY(&doctor->patient_LM);
        list->xItemValue=0;
        uxListRemove(list);
    }
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
    //���õ�ǰ��״̬��û��ԤԼ
    patient_to_init->doctor_L.xItemValue=0;

    return patient_to_init;
}

uint32_t platform_get_patient_status(patient_t *patient)
{
    return patient->doctor_L.xItemValue;
}

void platform_get_patient_login_data(patient_t *patient_t, int8_t *message)
{
    uint32_t status;
    status = platform_get_patient_status(patient_t);
    sprintf(message, "�𾴵� %s ����/Ůʿ\r\n", patient_t->login.name);
    if(status == WITHOUT_APPLICATION)
        sprintf(message, "%s����ǰ��ԤԼ״̬��û��ԤԼ\r\n", message);
    else if(status == FIRST_VISIT_DOCTOR)
        sprintf(message, "%s����ǰ��ԤԼ״̬��ԤԼû�г���\r\n", message);
    else if(status == SUBSQUENT_VISIT)
        sprintf(message, "%s����ǰ��ԤԼ״̬�ǵȴ�����\r\n", message);
}
