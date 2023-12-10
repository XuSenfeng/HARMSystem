/**
  ******************************************************************************
  * @file    platform_update.c
  * @version V1.0
  * @date    2023-12-10
  * @brief   ����ļ������ݿ�ĵײ��ļ�,��ӵײ��ļ������ȡ��Ϣ,������Ϣ�ĸ���
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


#include "platform_update.h"
extern manager_t manager;
/**
  * @brief  �������ڵ�����,������д�뵽�ļ�����
  * @param  ��
  * @retval ��
  */
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
        fprintf(message_f, "%s %s %s %s %s %d %s\n", doctor->login.id, doctor->login.name, doctor->login.passwd, doctor->service, doctor->level, doctor->num_to_accept, doctor->workday);
        list_test = listGET_NEXT(list_test);
        doctor = listGET_LIST_ITEM_OWNER(list_test);
    }
    //���벡��
    list_test = listGET_HEAD_ENTRY(&manager.patient_LM);
    patient = listGET_LIST_ITEM_OWNER(list_test);
    fprintf(message_f, "%d\n", manager.patient_LM.uxNumberOfItems);
    for(i=0;i<manager.patient_LM.uxNumberOfItems;i++)
    {
        fprintf(message_f, "%s %s %s %d %s %s", patient->login.id, patient->login.name, patient->login.passwd, patient->doctor_L.xItemValue,  patient->doc_id, patient->message);
        list_test = listGET_NEXT(list_test);
        patient = listGET_LIST_ITEM_OWNER(list_test);
    }  
    fclose(message_f);

}
/**
  * @brief  ����һ�����������Ϣ�ж��ǲ�����ȷ��
  * @param  id: �����id
  * @param  passwd:���������
  * @param  message:Ҫ�˶Եĵ�¼��Ϣ�ṹ��
  * @retval ��ȷ:1 ����ȷ:2
  */
int platform_is_right(char *id, char *passwd, message_to_login_t * message)
{
    if((strcmp(id, message->id)==0) && (strcmp(passwd, message->passwd)==0))
    {

        return 1;
    }else{
        return -1;
    }
}
/**
  * @brief  ���ļ��л�ȡ��Ҫ����Ϣ
  * @param  file_name: �ļ�������
  * @retval ��
  */
void platform_department_init(int8_t *file_name)
{
    //���ų�ʼ��
    FILE *message_f;
    int32_t i, j, management_num, service_num, patient_num;
    one_department_t *department;
    outpatient_service_t *service;
    int8_t pat_message[140];
    int8_t name[21];
    //ҽ����ʼ��
    int32_t doctor_num;
    int8_t id[21], passwd[30], work[20], status, level[30]; 
    int8_t workday[15];
    message_f = fopen(file_name, "r");
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
        fscanf(message_f, "%s %s %s %s %s %d %s", id, name, passwd, work, level, &management_num, workday);
        platform_add_doctor(name, id, passwd, work, level, management_num, workday);
   }
    //������ע�Ს��
    fscanf(message_f, "%d", &patient_num);
   for(i=0;i<patient_num;i++)
   {
        fscanf(message_f, "%s %s %s %c %s", id, name, passwd, &status, work);
        fgets(pat_message, 140, message_f);
        platform_add_patient(name, id, passwd, status ,work, pat_message);
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
/**
  * @brief  ���ļ��л�ȡ��Ҫ����Ϣ
  * @param  ��
  * @retval ��
  */
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
    platform_add_patient("ʷ����", "222", "123456", 0, "1001", "��");
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


/**
  * @brief  ��ʼ��һ��������
  * @param  ��
  * @retval ��
  */
void platform_manage_init()
{
    strcpy(manager.login.id, "000");
    strcpy(manager.login.name, "manage");   
    strcpy(manager.login.passwd, "123456");   
    vListInitialise(&manager.doctors_LM);
    vListInitialise(&manager.patient_LM);
    vListInitialise(&manager.departments_LM);
    platform_add_patient("manager", "000", "123456", '0', "0", "��");
    platform_department_init("document.txt");
}
/**
  * @brief  ɾ��������
  * @param  ��
  * @retval ��
  */
void platform_manage_out()
{
    patient_t *patient;
    patient = platform_get_patient("000");
    if(patient!=-1)
    platform_del_patient(patient);
    else
    printf("ɾ������Ա����ʧ��");
}

/**
  * @brief  ����һ��ҽ���ĵĽṹ��,��������
  * @param  name:��������
  * @param  id:����id
  * @param  passwd:��������
  * @param  work:����ְλ
  * @param  level:����ְ��
  * @retval �ɹ�����ҽ���ṹ��,ʧ�ܷ���-1
  */
static doctor_t * platform_init_doctor(char *name, char *id, char *passwd , char *work, char *level)
{
    outpatient_service_t * service;
    doctor_t *doctor_to_init;
    doctor_to_init = malloc(sizeof(doctor_t));

    //����ְ�����ù�ְ
    if(strcmp(level, DOC_LEVE_1)==0)
    {
        doctor_to_init->manage_L.xItemValue = 1;
    }
    if(strcmp(level, DOC_LEVE_2)==0)
    {
        doctor_to_init->manage_L.xItemValue = 2;
    }
    if(strcmp(level, DOC_LEVE_3)==0)
    {
        doctor_to_init->manage_L.xItemValue = 3;
    }
    if(strcmp(level, DOC_LEVE_4)==0)
    {
        doctor_to_init->manage_L.xItemValue = 4;
    }
    if(strcmp(level, DOC_LEVE_5)==0)
    {
        doctor_to_init->manage_L.xItemValue = 5;
    }

    /**********************�ڵ�ĳ�ʼ��**************************/
    //�����ڹ���������
    vListInitialiseItem(&doctor_to_init->manage_L);
    vListInitialiseItem(&doctor_to_init->service_L);
    vListInsert(&manager.doctors_LM, &doctor_to_init->manage_L);
    //printf("%s", work);
    service = platform_get_service(work);
    if(service!=-1){
        vListInsert(&service->doctors_LM, &doctor_to_init->service_L);
    }else{
        //printf("ҽ�����ز���ʧ��...");
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

/**
  * @brief  ���һ��ҽ��
  * @param  name:��������
  * @param  id:����id
  * @param  passwd:��������
  * @param  work:����ְλ
  * @param  level:����ְ��
  * @param  num_to_acp:�������Ӵ���
  * @param  workday: ����ʱ��
  * @retval �ɹ�����ҽ���ṹ��,ʧ�ܷ���-1
  */
doctor_t * platform_add_doctor(int8_t *name, int8_t *id, int8_t *passwd , int8_t *work, int8_t *level, int32_t num_to_acp, int8_t *workday)
{
    int32_t i = listCURRENT_LIST_LENGTH(&manager.doctors_LM);
    int8_t flog = 0;
    ListItem_t *list_doc = listGET_HEAD_ENTRY(&manager.doctors_LM);
    doctor_t  *doctor = listGET_LIST_ITEM_OWNER(list_doc);
    while(i--)
    {
        
        if(strcmp(id, doctor->login.id)==0)
        {
            //printf("id = %s %s\r\n", id, doctor->login.id);
            flog=1;
        }
        list_doc = listGET_NEXT(list_doc);
        doctor = listGET_LIST_ITEM_OWNER(list_doc);
    }
    if(flog==0)
    {
        doctor = platform_init_doctor(name, id, passwd , work, level);
    }else
    {
        //printf("���ҽ�� %s ��� %s ʧ��,�벻Ҫ�����ظ��ı�ŵ�ҽ��...\r\n", name, id);
        return -1;
    }
    strcpy(doctor->workday, workday);
    strcpy(doctor->level, level);
    doctor->num_to_accept = num_to_acp;
    return doctor;
}

/**
  * @brief  ��ȡһ��ҽ���Ľṹ��
  * @param  id:����id
  * @retval �ɹ�����ҽ���ṹ��,ʧ�ܷ���-1
  */
doctor_t *platform_get_doc(char *id)
{
    doctor_t *doctor=NULL;
    ListItem_t *doc_list;
    int i, flog=0;
    doc_list = listGET_HEAD_ENTRY(&manager.doctors_LM);
    doctor = listGET_LIST_ITEM_OWNER(doc_list);
    i = listCURRENT_LIST_LENGTH(&manager.doctors_LM);
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
        //printf("ҽ��%s�ҵ���\r\n", doctor->login.name);
        return doctor;
    }else{
        return -1;
    }
}
/**
  * @brief  ��ȡһ�����˵Ľṹ��
  * @param  id:����id
  * @retval �ɹ����ز��˽ṹ��,ʧ�ܷ���-1
  */
patient_t* platform_get_patient(char *id)
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
        return -1;
    }
}
/**
  * @brief  ��һ�����˽���ԤԼ
  * @param  patient:���˵Ľṹ��
  * @param  id:ԤԼ��ҽ����id
  * @retval �ɹ�����1,ʧ�ܷ���-1
  */
int32_t platform_patient_appointment(patient_t *patient, char *doc_id)
{
    doctor_t *doctor=NULL;
    ListItem_t doc_list;
    int i;
    doctor = platform_get_doc(doc_id);
    if(patient->doctor_L.xItemValue != 0)
    {
        uxListRemove(&patient->doctor_L);
        patient->doctor_L.xItemValue = 0;
    }

    if(doctor!=-1)
    {
#if DEBUG
        printf("�Ѿ�ԤԼ��ҽ�� %s \r\n", doctor->login.name);
#endif
        vListInsertEnd(&doctor->patient_LM, &patient->doctor_L);
        patient->doctor_L.xItemValue = 1;
        strcpy(patient->doc_id, doc_id);
        return 1;
    }else{
#if DEBUG
        printf("ҽ��������\r\n");
#endif
        return -1;
    }

}
/**
  * @brief  ɾ��һ��ҽ��
  * @param  doctor:Ҫɾ����ҽ���ṹ��
  * @retval ��
  */
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
    free(doctor);
}

/**
  * @brief  ɾ��һ������
  * @param  doctor:Ҫɾ���Ĳ��˽ṹ��
  * @retval ��
  */
void platform_del_patient(patient_t *patient)
{
    ListItem_t *list;
    if(patient->doctor_L.pvContainer!=NULL)
        uxListRemove(&patient->doctor_L);
    uxListRemove(&patient->manage_L);
    free(patient);
}
/**
  * @brief  ����һ�����ŵĵĽṹ��,�������ڹ���������
  * @param  name: Ҫ��ӵĲ���
  * @retval ���ػ�ȡ���Ĳ��Žṹ��
  */
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
/**
  * @brief  ����һ�����ŵĵĽṹ��,�������ڹ�������������һ������ĵĽṹ��,�������ڲ�������
  * @param  name:Ҫ��ӵ�����
  * @param  department:Ҫ���صĲ���
  * @retval ���ػ�ȡ��������ṹ��
  */
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
/**
  * @brief  ��ʼ��һ������
  * @param  name:���˵�����
  * @param  id:���˵�id
  * @param  passwd:���˵�����
  * @param  message:Ҫչʾ����Ϣ
  * @retval ���ػ�ȡ���Ĳ��˽ṹ��
  */
patient_t * platform_init_patient(int8_t *name, int8_t *id, int8_t *passwd, int8_t *message)
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
    listSET_LIST_ITEM_OWNER(&patient_to_init->doctor_L, patient_to_init);
    listSET_LIST_ITEM_OWNER(&patient_to_init->manage_L, patient_to_init);
    strcpy(patient_to_init->login.id, id);
    strcpy(patient_to_init->login.name, name);
    strcpy(patient_to_init->login.passwd, passwd);
    //���õ�ǰ��״̬��û��ԤԼ
    patient_to_init->doctor_L.xItemValue=0;
    //���ó�ʼ��ʱ��û����Ϣ
    strcpy(patient_to_init->message, message);
    return patient_to_init;
}
/**
  * @brief  ���һ������
  * @param  name:���˵�����
  * @param  id:���˵�id
  * @param  passwd:���˵�����
  * @param  status:��ǰ״̬'0'û��ԤԼ, '1'ԤԼû�г���, '2'�ȴ�����
  * @param  doc_id:ҽ����id
  * @param  message:Ҫչʾ����Ϣ
  * @retval ���ػ�ȡ���Ĳ��˽ṹ��
  */
void *platform_add_patient(int8_t *name, int8_t *id, int8_t *passwd, int8_t status, int8_t *doc_id, int8_t *message)
{
    
    doctor_t *doctor;
    int32_t i = listCURRENT_LIST_LENGTH(&manager.patient_LM);
    int8_t flog = 0;
    ListItem_t *list_pantient = listGET_HEAD_ENTRY(&manager.patient_LM);
    patient_t *patient = listGET_LIST_ITEM_OWNER(list_pantient);
    while(i--)
    {
        //�Ƚ���û����ӹ���ͬ����
        if(strcmp(id, patient->login.id)==0)
        {
            flog=1;
        }
        list_pantient = listGET_NEXT(list_pantient);
        patient = listGET_LIST_ITEM_OWNER(list_pantient);
    }
    if(flog==0)
    {
        patient = platform_init_patient(name, id, passwd, message);
    }else
    {
        //printf("\r\n��Ӳ��� %s ��� %s ʧ��,�벻Ҫ�����ظ��ı�ŵĲ���...\r\n", name, id);
        return -1;
    }
    strcpy(patient->doc_id, doc_id);
    doctor = platform_get_doc(doc_id);
    if(doctor != -1)
    {
        if(status == '1')
        {
            vListInsertEnd(&doctor->patient_LM, &patient->doctor_L);
            patient->doctor_L.xItemValue = 1;
        }else if(status == '2'){
            vListInsertEnd(&doctor->patient_LM, &patient->doctor_L);
            patient->doctor_L.xItemValue = 2;
        }
    }
    return patient;
    
}
/**
  * @brief  ��ȡһ�����˵�״̬
  * @param  ��
  * @retval ��ǰ״̬0û��ԤԼ, 1ԤԼû�г���, 2�ȴ�����
  */
uint32_t platform_get_patient_status(patient_t *patient)
{
    return patient->doctor_L.xItemValue;
}

/**
  * @brief  �Բ��˽��о���
  * @param  doctor:ҽ��
  * @param  patient:Ҫ����Ĳ���
  * @param  choice:Ҫ����ķ�ʽ,'1':�ȴ�����, '2': ��������
  * @retval ��
  */
void platform_doc_deal_pat(doctor_t *doctor, patient_t *patient, int8_t choice)
{
    if(choice == '1')
    {
        //������Ҫ��һ������
        patient->doctor_L.xItemValue = 2;
        //�����ŵ���β
        uxListRemove(&patient->doctor_L);
        vListInsertEnd(&doctor->patient_LM, &patient->doctor_L);

    }else if(choice == '2')
    {
        patient->doctor_L.xItemValue = 0;
        //���ò��˴洢��ҽ��Ϊ0
        patient->doc_id[0] = '0';
        patient->doc_id[1] = '\0';
        uxListRemove(&patient->doctor_L);
    }


}
