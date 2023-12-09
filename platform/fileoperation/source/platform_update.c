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
    platform_add_patient("manager", "000", "123456", '0', "0");
    platform_department_init();
}
void platform_manage_out()
{
    patient_t *patient;
    patient = platform_get_patient("000");
    if(patient!=-1)
    platform_del_patient(patient);
    else
    printf("删除管理员病人失败");
}
//申请一个医生的的结构体,并挂载在管理者名下
static doctor_t * platform_init_doctor(char *name, char *id, char *passwd , char *work, char *level)
{
    outpatient_service_t * service;
    doctor_t *doctor_to_init;
    doctor_to_init = malloc(sizeof(doctor_t));

    //根据职称设置官职
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

    /**********************节点的初始化**************************/
    //挂载在管理者名下
    vListInitialiseItem(&doctor_to_init->manage_L);
    vListInitialiseItem(&doctor_to_init->service_L);
    vListInsert(&manager.doctors_LM, &doctor_to_init->manage_L);
    //printf("%s", work);
    service = platform_get_service(work);
    if(service!=-1){
        vListInsert(&service->doctors_LM, &doctor_to_init->service_L);
    }else{
        //printf("医生挂载部门失败...");
        while(1);
    }
    //挂载父节点
    listSET_LIST_ITEM_OWNER(&doctor_to_init->manage_L, doctor_to_init);
    listSET_LIST_ITEM_OWNER(&doctor_to_init->service_L, doctor_to_init);
    vListInitialise(&doctor_to_init->patient_LM);
    /************************************************************/
    //在这里初始化各种个人信息
    strcpy(doctor_to_init->login.id, id);
    strcpy(doctor_to_init->login.name, name);
    strcpy(doctor_to_init->login.passwd, passwd);
    strcpy(doctor_to_init->service, work);

    return doctor_to_init;
}
//添加一个医生
doctor_t * platform_add_doctor(char *name, char *id, char *passwd , char *work, char *level, int32_t num_to_acp)
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
        //printf("添加医生 %s 编号 %s 失败,请不要输入重复的编号的医生...\r\n", name, id);
        return -1;
    }
    strcpy(doctor->level, level);
    doctor->num_to_accept = num_to_acp;
    return doctor;
}
//获取一个医生的结构体
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
        //printf("医生%s找到了\r\n", doctor->login.name);
        return doctor;
    }else{
        return -1;
    }
}
//获取一个病人的结构体
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
        printf("已经预约到医生 %s \r\n", doctor->login.name);
#endif
        vListInsertEnd(&doctor->patient_LM, &patient->doctor_L);
        patient->doctor_L.xItemValue = 1;
        strcpy(patient->doc_id, doc_id);
        return 1;
    }else{
#if DEBUG
        printf("医生不存在\r\n");
#endif
        return -1;
    }

}
//删除一个医生
void platform_del_doctor(doctor_t *doctor)
{
    ListItem_t *list;
    //把这个医生从体系里面删除出去
    uxListRemove(&doctor->manage_L);
    uxListRemove(&doctor->service_L);
     
    while(listCURRENT_LIST_LENGTH(&doctor->patient_LM))
    {
        //设置这一个医生的所有的病人的状态为没有预约
        list = listGET_HEAD_ENTRY(&doctor->patient_LM);
        list->xItemValue=0;
        uxListRemove(list);
    }
    free(doctor);
}
//删除一个病人
void platform_del_patient(patient_t *patient)
{
    ListItem_t *list;
    if(patient->doctor_L.pvContainer!=NULL)
        uxListRemove(&patient->doctor_L);
    uxListRemove(&patient->manage_L);
    free(patient);
}
//申请一个部门的的结构体,并挂载在管理者名下
one_department_t * platform_init_department(char *name)
{
    one_department_t *department;
    department = malloc(sizeof(one_department_t));
    vListInitialise(&department->services_LM);
    vListInitialiseItem(&department->manage_L);
    vListInsertEnd(&manager.departments_LM, &department->manage_L);
    //设置父节点
    listSET_LIST_ITEM_OWNER(&department->manage_L, department);
    strcpy(department->name, name);
    return department;
}

//申请一个门诊的的结构体,并挂载在部门名下
outpatient_service_t * platform_init_service(char *name, one_department_t* department)
{
    outpatient_service_t *service;
    service = malloc(sizeof(outpatient_service_t));
    vListInitialise(&service->doctors_LM);
    vListInitialiseItem(&service->department_L);
    //fscanf(message_f, "%s", service->name);
    strcpy(service->name, name);
    //把某一个科室注册到部门下面
    vListInsertEnd(&department->services_LM, &service->department_L);
    listSET_LIST_ITEM_OWNER(&service->department_L, service);
    return service;
}

//申请一个患者的的结构体,并挂载在管理者名下
patient_t * platform_init_patient(char *name, char *id, char *passwd)
{
    patient_t *patient_to_init;
    patient_to_init = malloc(sizeof(patient_t));
    /**********************节点的初始化**************************/
    //挂载在管理者名下
    vListInitialiseItem(&patient_to_init->manage_L);
    vListInitialiseItem(&patient_to_init->doctor_L);
    vListInsertEnd(&manager.patient_LM, &patient_to_init->manage_L);
    //挂载父节点
    patient_to_init->manage_L.pvOwner = (void *)patient_to_init;
    /************************************************************/
    //在这里初始化各种个人信息
    listSET_LIST_ITEM_OWNER(&patient_to_init->doctor_L, patient_to_init);
    listSET_LIST_ITEM_OWNER(&patient_to_init->manage_L, patient_to_init);
    strcpy(patient_to_init->login.id, id);
    strcpy(patient_to_init->login.name, name);
    strcpy(patient_to_init->login.passwd, passwd);
    //设置当前的状态是没有预约
    patient_to_init->doctor_L.xItemValue=0;

    return patient_to_init;
}
//添加一个病人,参数一:名字, 参数二: id, 参数3: 当前状态'0'没有预约, '1'预约没有初诊, '2'等待复诊, 参数四,医生的id
void *platform_add_patient(int8_t *name, int8_t *id, int8_t *passwd, int8_t status, int8_t *doc_id)
{
    
    doctor_t *doctor;
    int32_t i = listCURRENT_LIST_LENGTH(&manager.patient_LM);
    int8_t flog = 0;
    ListItem_t *list_pantient = listGET_HEAD_ENTRY(&manager.patient_LM);
    patient_t *patient = listGET_LIST_ITEM_OWNER(list_pantient);
    while(i--)
    {
        //比较有没有添加过相同的人
        if(strcmp(id, patient->login.id)==0)
        {
            flog=1;
        }
        list_pantient = listGET_NEXT(list_pantient);
        patient = listGET_LIST_ITEM_OWNER(list_pantient);
    }
    if(flog==0)
    {
        patient = platform_init_patient(name, id, passwd);
    }else
    {
        //printf("\r\n添加病人 %s 编号 %s 失败,请不要输入重复的编号的病人...\r\n", name, id);
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

uint32_t platform_get_patient_status(patient_t *patient)
{
    return patient->doctor_L.xItemValue;
}


