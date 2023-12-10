/**
  ******************************************************************************
  * @file    platform_update.c
  * @version V1.0
  * @date    2023-12-10
  * @brief   这个文件是数据库的底层文件,会从底层文件里面读取信息,进行信息的更新
  * @author  XvSenfeng(焦浩洋)
  ******************************************************************************
  * @attention
  * 本程序由XvSenfeng创建并免费开源共享
  * 你可以任意查看、使用和修改，并应用到自己的项目之中
  * 程序版权归XvSenfeng所有，任何人或组织不得将其据为己有
  * 如果你发现程序中的漏洞或者笔误，可通过邮件向我们反馈：1458612070@qq.com
  * 发送邮件之前，你可以先到更新动态页面查看最新程序，如果此问题已经修改，则无需再发邮件
  * https://github.com/XuSenfeng
  ******************************************************************************
  */ 


#include "platform_update.h"
extern manager_t manager;
/**
  * @brief  更新现在的数据,把数据写入到文件里面
  * @param  无
  * @retval 无
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
    //获取部门的链表
    fprintf(message_f, "%d\n", manager.departments_LM.uxNumberOfItems);
    list_test = listGET_HEAD_ENTRY(&manager.departments_LM);
    department = listGET_LIST_ITEM_OWNER(list_test);
    for(i=0;i<manager.departments_LM.uxNumberOfItems;i++)
    {
        //进入一个门诊
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
    //输入医生
    list_test = listGET_HEAD_ENTRY(&manager.doctors_LM);
    doctor = listGET_LIST_ITEM_OWNER(list_test);
    fprintf(message_f, "%d\n", manager.doctors_LM.uxNumberOfItems);
    for(i=0;i<manager.doctors_LM.uxNumberOfItems;i++)
    {
        fprintf(message_f, "%s %s %s %s %s %d %s\n", doctor->login.id, doctor->login.name, doctor->login.passwd, doctor->service, doctor->level, doctor->num_to_accept, doctor->workday);
        list_test = listGET_NEXT(list_test);
        doctor = listGET_LIST_ITEM_OWNER(list_test);
    }
    //输入病人
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
  * @brief  根据一个人输入的信息判断是不是正确的
  * @param  id: 输入的id
  * @param  passwd:输入的密码
  * @param  message:要核对的登录信息结构体
  * @retval 正确:1 不正确:2
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
  * @brief  从文件中获取需要的信息
  * @param  file_name: 文件的名字
  * @retval 无
  */
void platform_department_init(int8_t *file_name)
{
    //部门初始化
    FILE *message_f;
    int32_t i, j, management_num, service_num, patient_num;
    one_department_t *department;
    outpatient_service_t *service;
    int8_t pat_message[140];
    int8_t name[21];
    //医生初始化
    int32_t doctor_num;
    int8_t id[21], passwd[30], work[20], status, level[30]; 
    int8_t workday[15];
    message_f = fopen(file_name, "r");
    fscanf(message_f, "%d", &management_num);
    //printf("*******部门初始化*****%d\r\n", management_num);
    for(i=0;i<management_num;i++)
    {
        //读取格式化的部门信息
        fscanf(message_f, "%s %d", name, &service_num);
        department = platform_init_department(name);
        for(j=0;j<service_num;j++)
        {
            //初始化现有的门诊
            fscanf(message_f, "%s", name);
            platform_init_service(name, department);
        }
    }
#if DEBUG
    ListItem_t *list_test, *list_test2;
    /*测试代码, 会显示现在已经注册的所有的部门以及门诊*/
    printf("现在有%d个部门\r\n", manager.departments_LM.uxNumberOfItems);
    list_test = listGET_HEAD_ENTRY(&manager.departments_LM);
    department = listGET_LIST_ITEM_OWNER(list_test);
    for(i=0;i<manager.departments_LM.uxNumberOfItems;i++)
    {
        printf("部门%s下面有%d个门诊\r\n", department->name, department->services_LM.uxNumberOfItems);
        list_test2 = listGET_HEAD_ENTRY(&department->services_LM);
        service = listGET_LIST_ITEM_OWNER(list_test2);
        for(j=0;j<department->services_LM.uxNumberOfItems;j++)
        {
            printf("门诊%d是: %s\r\n", j+1, service->name);
            list_test2 = listGET_NEXT(list_test2);
            service = listGET_LIST_ITEM_OWNER(list_test2);
        }


        list_test = listGET_NEXT(list_test);
        department = listGET_LIST_ITEM_OWNER(list_test);
    }
    
   if((service = platform_get_service("小儿内科"))!= -1)
   {
        printf("找到了%s\r\n", service->name);
   }
#endif
    //在这里注册的是医生
   fscanf(message_f, "%d", &doctor_num);
   for(i=0;i<doctor_num;i++)
   {
        fscanf(message_f, "%s %s %s %s %s %d %s", id, name, passwd, work, level, &management_num, workday);
        platform_add_doctor(name, id, passwd, work, level, management_num, workday);
   }
    //在这里注册病人
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
    printf("一共有%d个病人\r\n", manager.patient_LM.uxNumberOfItems);
    for(i=0;i<manager.patient_LM.uxNumberOfItems;i++)
    {
        printf("患者 %d 的名字是 %s 现在的状态是 %d\r\n", i+1, patient->login.name, patient->doctor_L.xItemValue);
        list_test = listGET_NEXT(list_test);
        patient = listGET_LIST_ITEM_OWNER(list_test);
    }
#endif
}
/**
  * @brief  从文件中获取需要的信息
  * @param  无
  * @retval 无
  */
void platform_test(void)
{
    uint32_t ret;
    ListItem_t * doctor_list, * patient_list;
    doctor_t * doctor;
    patient_t * patient;
    printf("platform\r\n");
    printf("链表里面有:%d\r\n", listCURRENT_LIST_LENGTH(&manager.doctors_LM));
    doctor_list = listGET_HEAD_ENTRY(&manager.doctors_LM);
    doctor = (doctor_t *)listGET_LIST_ITEM_OWNER(doctor_list);
    printf("医生的信息: %s %s %s\r\n", doctor->login.id, doctor->login.name, doctor->login.passwd);
    platform_add_patient("史凯歌", "222", "123456", 0, "1001", "无");
    patient_list = listGET_HEAD_ENTRY(&manager.patient_LM);
    patient = (patient_t *)listGET_LIST_ITEM_OWNER(patient_list);
    printf("患者的信息: %s %s %s\r\n", patient->login.id, patient->login.name, patient->login.passwd);
    platform_patient_appointment(patient, "1001");
    ret = platform_get_patient_status(patient);
    if(ret==WITHOUT_APPLICATION)
    {
        printf("没有预约\r\n");
    }
    else if(ret = 1)
    {
        printf("预约成功\r\n");
    }

}


/**
  * @brief  初始化一个管理者
  * @param  无
  * @retval 无
  */
void platform_manage_init()
{
    strcpy(manager.login.id, "000");
    strcpy(manager.login.name, "manage");   
    strcpy(manager.login.passwd, "123456");   
    vListInitialise(&manager.doctors_LM);
    vListInitialise(&manager.patient_LM);
    vListInitialise(&manager.departments_LM);
    platform_add_patient("manager", "000", "123456", '0', "0", "无");
    platform_department_init("document.txt");
}
/**
  * @brief  删除管理者
  * @param  无
  * @retval 无
  */
void platform_manage_out()
{
    patient_t *patient;
    patient = platform_get_patient("000");
    if(patient!=-1)
    platform_del_patient(patient);
    else
    printf("删除管理员病人失败");
}

/**
  * @brief  申请一个医生的的结构体,并挂载在
  * @param  name:他的名字
  * @param  id:他的id
  * @param  passwd:他的密码
  * @param  work:他的职位
  * @param  level:他的职称
  * @retval 成功返回医生结构体,失败返回-1
  */
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

/**
  * @brief  添加一个医生
  * @param  name:他的名字
  * @param  id:他的id
  * @param  passwd:他的密码
  * @param  work:他的职位
  * @param  level:他的职称
  * @param  num_to_acp:他的最大接待数
  * @param  workday: 工作时间
  * @retval 成功返回医生结构体,失败返回-1
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
        //printf("添加医生 %s 编号 %s 失败,请不要输入重复的编号的医生...\r\n", name, id);
        return -1;
    }
    strcpy(doctor->workday, workday);
    strcpy(doctor->level, level);
    doctor->num_to_accept = num_to_acp;
    return doctor;
}

/**
  * @brief  获取一个医生的结构体
  * @param  id:他的id
  * @retval 成功返回医生结构体,失败返回-1
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
        //printf("医生%s找到了\r\n", doctor->login.name);
        return doctor;
    }else{
        return -1;
    }
}
/**
  * @brief  获取一个病人的结构体
  * @param  id:他的id
  * @retval 成功返回病人结构体,失败返回-1
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
  * @brief  给一个病人进行预约
  * @param  patient:病人的结构体
  * @param  id:预约的医生的id
  * @retval 成功返回1,失败返回-1
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
/**
  * @brief  删除一个医生
  * @param  doctor:要删除的医生结构体
  * @retval 无
  */
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

/**
  * @brief  删除一个病人
  * @param  doctor:要删除的病人结构体
  * @retval 无
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
  * @brief  申请一个部门的的结构体,并挂载在管理者名下
  * @param  name: 要添加的部门
  * @retval 返回获取到的部门结构体
  */
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
/**
  * @brief  申请一个部门的的结构体,并挂载在管理者名下申请一个门诊的的结构体,并挂载在部门名下
  * @param  name:要添加的门诊
  * @param  department:要挂载的部门
  * @retval 返回获取到的门诊结构体
  */
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
/**
  * @brief  初始化一个病人
  * @param  name:病人的名字
  * @param  id:病人的id
  * @param  passwd:病人的密码
  * @param  message:要展示的信息
  * @retval 返回获取到的病人结构体
  */
patient_t * platform_init_patient(int8_t *name, int8_t *id, int8_t *passwd, int8_t *message)
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
    //设置初始的时候没有信息
    strcpy(patient_to_init->message, message);
    return patient_to_init;
}
/**
  * @brief  添加一个病人
  * @param  name:病人的名字
  * @param  id:病人的id
  * @param  passwd:病人的密码
  * @param  status:当前状态'0'没有预约, '1'预约没有初诊, '2'等待复诊
  * @param  doc_id:医生的id
  * @param  message:要展示的信息
  * @retval 返回获取到的病人结构体
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
        patient = platform_init_patient(name, id, passwd, message);
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
/**
  * @brief  获取一个病人的状态
  * @param  无
  * @retval 当前状态0没有预约, 1预约没有初诊, 2等待复诊
  */
uint32_t platform_get_patient_status(patient_t *patient)
{
    return patient->doctor_L.xItemValue;
}

/**
  * @brief  对病人进行就诊
  * @param  doctor:医生
  * @param  patient:要处理的病人
  * @param  choice:要处理的方式,'1':等待复诊, '2': 结束治疗
  * @retval 无
  */
void platform_doc_deal_pat(doctor_t *doctor, patient_t *patient, int8_t choice)
{
    if(choice == '1')
    {
        //病人需要进一步治疗
        patient->doctor_L.xItemValue = 2;
        //把他放到队尾
        uxListRemove(&patient->doctor_L);
        vListInsertEnd(&doctor->patient_LM, &patient->doctor_L);

    }else if(choice == '2')
    {
        patient->doctor_L.xItemValue = 0;
        //设置病人存储的医生为0
        patient->doc_id[0] = '0';
        patient->doc_id[1] = '\0';
        uxListRemove(&patient->doctor_L);
    }


}
