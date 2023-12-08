
#include "platform_main.h"

manager_t manager;
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
    platform_add_patient("史凯歌", "222", "123456", 0, "1001");
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
//对文件进行读操作
void platform_department_init(void)
{
    //部门初始化
    FILE *message_f;
    int32_t i, j, management_num, service_num, patient_num;
    one_department_t *department;
    outpatient_service_t *service;

    int8_t name[21];
    //医生初始化
    int32_t doctor_num;
    int8_t id[21], passwd[30], work[20], status; 

    message_f = fopen("document.txt", "r");
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
        fscanf(message_f, "%s %s %s %s", id, name, passwd, work);
        platform_add_doctor(name, id, passwd, work);
   }
    //在这里注册病人
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
    printf("一共有%d个病人\r\n", manager.patient_LM.uxNumberOfItems);
    for(i=0;i<manager.patient_LM.uxNumberOfItems;i++)
    {
        printf("患者 %d 的名字是 %s 现在的状态是 %d\r\n", i+1, patient->login.name, patient->doctor_L.xItemValue);
        list_test = listGET_NEXT(list_test);
        patient = listGET_LIST_ITEM_OWNER(list_test);
    }
#endif

}
//从现有的部门里面获取某一个部门,参数是部门的名字
outpatient_service_t * platform_get_service(char *name)
{
    int32_t i, j;
    one_department_t *department;
    outpatient_service_t *service;
    ListItem_t *list_test, *list_test2;
    //获取部门的链表
    list_test = listGET_HEAD_ENTRY(&manager.departments_LM);
    department = listGET_LIST_ITEM_OWNER(list_test);
    for(i=0;i<manager.departments_LM.uxNumberOfItems;i++)
    {
        //获取某个门诊的链表
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



//根据一个人输入的信息判断是不是正确的
int platform_is_right(char *id, char *passwd, message_to_login_t * message)
{
    if((strcmp(id, message->id)==0) && (strcmp(passwd, message->passwd)==0))
    {

        return 1;
    }else{
        return -1;
    }
}

//根据一个人的id以及密码判断是否登陆成功,成功的话返回对应的那个人的结构体
int32_t platform_login(int8_t *id, int8_t *passwd, int8_t choice)
{
    ListItem_t *list_to_use;
    doctor_t *doctor;
    patient_t *patient;
    int num_to_get;
    if(choice == '3')
    {
        //管理员
        //printf("管理员登录\r\n");
        if(platform_is_right(id, passwd, &manager.login)==1)
        {
            return 1;
        }else
            return -1;
        
    }else if(choice == '2')
    {
        //医生
        //printf("医生登录\r\n");
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
        //患者
        //printf("患者登录\r\n");
        //获取要遍历的患者列表以及患者信息
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
/*********************************************平台设置使用的函数***********************************************/
//平台加载函数,用于平台的初始化,获取数据
void platform_init()
{
    platform_manage_init();
#if DEBUG
    platform_test();
#endif
}
//更新现在的数据,把数据写入到文件里面
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
        fprintf(message_f, "%s %s %s %s\n", doctor->login.id, doctor->login.name, doctor->login.passwd, doctor->service);
        list_test = listGET_NEXT(list_test);
        doctor = listGET_LIST_ITEM_OWNER(list_test);
    }
    //输入病人
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


//平台退出函数,主要用于释放空间
void platform_out()
{
    int32_t i, j;
    ListItem_t *list_now, *list_next;
    doctor_t *doctor;
    patient_t *patient;
    //把当前的数据存储起来
    platform_update();
    //释放内存
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
    //获取部门的链表

    while(listCURRENT_LIST_LENGTH(&manager.departments_LM))
    {
        list_test = listGET_HEAD_ENTRY(&manager.departments_LM);
        department = listGET_LIST_ITEM_OWNER(list_test);
        //获取某个门诊的链表
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
            sprintf(message, "获取失败%s\r\n", id);
    }
}
