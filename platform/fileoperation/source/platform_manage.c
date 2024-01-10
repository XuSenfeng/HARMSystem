/**
  ******************************************************************************
  * @file    platform_manage.c
  * @version V1.0
  * @date    2023-12-10
  * @brief   这个文件是数据库的API层,主要是为了实现管理员的命令API函数
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


#include "platform_manage.h"
extern manager_t manager;
/**
  * @brief  获取登录信息
  * @param  message:返回的显示信息
  * @retval 无
  */
void platform_get_manage_login_data(int8_t *message)
{
    sprintf(message, "\0");
    sprintf(message, "尊敬的 %s 先生/女士 欢迎使用\r\n", manager.login.name);
    //printf(message);
    //printf("4444444444");
}
/**
  * @brief  获取病人的信息
  * @param  message:返回的显示信息
  * @param  begin:起始位置
  * @param  num:获取的数量
  * @retval 无
  */
void platform_manage_getpat_data(int8_t *message, int32_t begin, int32_t num){

    patient_t *patient;
    doctor_t *doctor;
    int32_t i, k=0, j, t;
    int8_t status;
    ListItem_t *list_test;
    int8_t str1[] = "没有预约";
    int8_t str2[] = "预约了没有治疗";
    int8_t str3[] = "等待复诊";
    //清空缓冲区
    sprintf(message, "\0");

    list_test = listGET_HEAD_ENTRY(&manager.patient_LM);
    //跳过管理员使用的病人
    list_test = listGET_NEXT(list_test);
    patient = listGET_LIST_ITEM_OWNER(list_test);
    for(i=0;i<manager.patient_LM.uxNumberOfItems;i++)
    {
        status = patient->doctor_L.xItemValue;
        if(k>=begin && k<begin + num){
            sprintf(message, "%s病人 %d 号的id是: %s 名字: %s 当前的状态是 %s\r\n", 
            message, k+1, patient->login.id, patient->login.name, 
            status==0?str1:(status==1?str2:str3));
            if(status!=0)
            {
                doctor = platform_get_doc(patient->doc_id);
                if(doctor!=ERROR)
                {
                    sprintf(message, "%s当前他的医生是 %s %s\r\n", 
                    message, doctor->login.name, doctor->login.id);
                }
            }
        }
        k++;
        list_test = listGET_NEXT(list_test);
        patient = listGET_LIST_ITEM_OWNER(list_test);

    }

}
/**
  * @brief  改变一个医生的信息
  * @param  doctor:要修改的医生
  * @param  message:返回的显示信息
  * @param  parameter:获取到的参数 int8_t (*doc_msg)[31]类型 1选择 2修改以后得值
  * @retval 无
  */
void platform_manage_chg_doc(doctor_t *doctor,int8_t* message, int8_t (*doc_msg)[31]){
    outpatient_service_t *service1, *service2;
    if(doc_msg[1][0]=='1')
    {
        //改名字
        sprintf(message, "名字 %s 改为 %s\r\n", doctor->login.name, doc_msg[2]);
        strcpy(doctor->login.name, doc_msg[2]);
        
    }else if(doc_msg[1][0]=='2')
    {
        //改职称
        sprintf(message, "职称 %s 改为 %s\r\n", doctor->level, doc_msg[2]);
        strcpy(doctor->level, doc_msg[2]);
        //根据职称设置官职
        if(strcmp(doc_msg[2], DOC_LEVE_1)==0)
        {
            doctor->manage_L.xItemValue = 1;
        }
        if(strcmp(doc_msg[2], DOC_LEVE_2)==0)
        {
            doctor->manage_L.xItemValue = 2;
        }
        if(strcmp(doc_msg[2], DOC_LEVE_3)==0)
        {
            doctor->manage_L.xItemValue = 3;
        }
        if(strcmp(doc_msg[2], DOC_LEVE_4)==0)
        {
            doctor->manage_L.xItemValue = 4;
        }
        if(strcmp(doc_msg[2], DOC_LEVE_5)==0)
        {
            doctor->manage_L.xItemValue = 5;
        }
        uxListRemove(&doctor->manage_L);
        vListInsert(&manager.doctors_LM, &doctor->manage_L);
    }else if(doc_msg[1][0]=='3'){
        //登录密码
        sprintf(message, "密码 %s 改为 %s\r\n", doctor->login.passwd, doc_msg[2]);
        strcpy(doctor->login.passwd, doc_msg[2]);
    }else if(doc_msg[1][0]=='4'){
        //部门
        service1 = platform_get_service(doctor->service);
        if(service1 != ERROR){
            service2 = platform_get_service(doc_msg[2]);
            if(service2 != ERROR){
                strcpy(doctor->service, doc_msg[2]);
                uxListRemove(&doctor->service_L);
                vListInsertEnd(&service2->doctors_LM, &doctor->service_L);
                sprintf(message, "更新成功\r\n");
            }else{
                sprintf(message, "医生新的部门没找到,不进行更新\r\n");
            }
        }else{
            sprintf(message, "医生本来的部门没找到, 比进行更新\r\n");
        }
    }
}
/**
  * @brief  改变一个病人的信息
  * @param  patient:要修改的病人
  * @param  message:返回的显示信息
  * @param  parameter:获取到的参数 int8_t (*pat_msg)[31]类型 1选择 2修改以后得值
  * @retval 无
  */
void platform_manage_chg_pat(patient_t *patient,int8_t* message, int8_t (*pat_msg)[31]){

    if(pat_msg[1][0]=='1')
    {
        //改名字
        sprintf(message, "名字 %s 改为 %s\r\n", patient->login.name, pat_msg[2]);
        strcpy(patient->login.name, pat_msg[2]);
        
    }else if(pat_msg[1][0]=='2'){
        //登录密码
        sprintf(message, "密码 %s 改为 %s\r\n", patient->login.passwd, pat_msg[2]);
        strcpy(patient->login.passwd, pat_msg[2]);
    }
}
/**
  * @brief  添加一个医生
  * @param  message:返回的显示信息
  * @param  parameter:获取到的参数 int8_t (*doc_msg)[31]类型, 0名字 1职位 2职称 3密码 4工作时间 5-0接待人数
  * @retval 无
  */
void platform_manage_add_doc(int8_t *message, int8_t *parameter)
{
    int8_t (*doc_msg)[31] =parameter ;
    int8_t doc_id[21];
    time_t timep;
    struct tm *p;
    doctor_t *doctor;
    time(&timep);
    p=gmtime(&timep);
    sprintf(doc_id, "%04d%02d%02d%04d",1900+p->tm_year, 1+p->tm_mon, p->tm_mday, manager.doctors_LM.uxNumberOfItems);
    //printf("测试 %s %s %s\r\n", doc_id, doc_msg[1], doc_msg[2]);while(1);
    doctor = platform_add_doctor(doc_msg[0], doc_id, doc_msg[3], doc_msg[1], doc_msg[2], doc_msg[5][0], doc_msg[4], 0, doc_msg[5][1]);
    if(doctor != ERROR)
    {
        sprintf(message, "添加成功\r\n");
        
    }else{
        sprintf(message, "添加失败,输入信息有误\r\n");
    }

}

void platform_manage_get_msg(int8_t *message, int parameter)
{
    doctor_t *doctor;
    ListItem_t *list_test, *list_test3, *list_test2;
    int32_t i, j, t, max, num;
    one_department_t *department;
    outpatient_service_t *service;
    //清空信息
    sprintf(message, "\0");
    
    
    if(parameter == 1 ){
        //跳过获取接待过病人最多的医生的信息
        list_test = listGET_HEAD_ENTRY(&manager.doctors_LM);
        doctor = listGET_LIST_ITEM_OWNER(list_test);
        max = doctor->num_had_accept;
        for(i=0;i<manager.doctors_LM.uxNumberOfItems;i++)
        {
            if(doctor->num_had_accept>max)
                max = doctor->num_had_accept;
            list_test = listGET_NEXT(list_test);
            doctor = listGET_LIST_ITEM_OWNER(list_test);
        }
        list_test = listGET_NEXT(list_test);
        doctor = listGET_LIST_ITEM_OWNER(list_test);
        for(i=0;i<manager.doctors_LM.uxNumberOfItems;i++)
        {
            if(doctor->num_had_accept == max)
                sprintf(message, "%s%s门诊的 %s 医生,目前接待病人 %d个\r\n", 
                message, doctor->service, 
                doctor->login.name, doctor->num_had_accept);
            list_test = listGET_NEXT(list_test);
            doctor = listGET_LIST_ITEM_OWNER(list_test);
        }
    }else if(parameter==2){
        max = 0;
        list_test = listGET_HEAD_ENTRY(&manager.departments_LM);
        department = listGET_LIST_ITEM_OWNER(list_test);
        for(i=0;i<manager.departments_LM.uxNumberOfItems;i++)
        {
            //获取到一个部门
            num = 0;
            //遍历部门下面的所有门诊
            list_test2 = listGET_HEAD_ENTRY(&department->services_LM);
            service = listGET_LIST_ITEM_OWNER(list_test2);
            for(j=0;j<department->services_LM.uxNumberOfItems;j++)
            {

                //获取所有医生
                list_test3 = listGET_HEAD_ENTRY(&service->doctors_LM);
                doctor = listGET_LIST_ITEM_OWNER(list_test3);
                for(t=0;t<service->doctors_LM.uxNumberOfItems;t++)
                {
                    num += doctor->num_had_accept;
                    list_test3 = listGET_NEXT(list_test3);
                    doctor = listGET_LIST_ITEM_OWNER(list_test3);
                }

                list_test2 = listGET_NEXT(list_test2);
                service = listGET_LIST_ITEM_OWNER(list_test2);

                
            }
            

            if(max<num)
                max = num;
            list_test = listGET_NEXT(list_test);
            department = listGET_LIST_ITEM_OWNER(list_test);

        }
        list_test = listGET_HEAD_ENTRY(&manager.departments_LM);
        department = listGET_LIST_ITEM_OWNER(list_test);
        for(i=0;i<manager.departments_LM.uxNumberOfItems;i++)
        {
            //获取到一个部门
            num = 0;
            //遍历部门下面的所有门诊
            list_test2 = listGET_HEAD_ENTRY(&department->services_LM);
            service = listGET_LIST_ITEM_OWNER(list_test2);
            for(j=0;j<department->services_LM.uxNumberOfItems;j++)
            {

                //获取所有医生
                list_test3 = listGET_HEAD_ENTRY(&service->doctors_LM);
                doctor = listGET_LIST_ITEM_OWNER(list_test3);
                for(t=0;t<service->doctors_LM.uxNumberOfItems;t++)
                {
                    num += doctor->num_had_accept;
                    list_test3 = listGET_NEXT(list_test3);
                    doctor = listGET_LIST_ITEM_OWNER(list_test3);
                }

                list_test2 = listGET_NEXT(list_test2);
                service = listGET_LIST_ITEM_OWNER(list_test2);
                
            }
            

            if(max==num)
                sprintf(message, "%s%s部门 为最受欢迎的部门,目前接待病人 %d个\r\n", 
                message, department->name, num);

            list_test = listGET_NEXT(list_test);
            department = listGET_LIST_ITEM_OWNER(list_test);

        }
    }
}


/**
  * @brief  这个是管理者的命令接口,根据命令返回信息
  * @param  commend:获取到的命令
  * @param  message:返回的显示信息
  * @param  parameter:一个参数
  * @retval 无
  */
void platform_manage_commend(int8_t commend,int8_t *message, void *parameter)
{
    int8_t (*doc_msg)[31];
    int32_t *p;
    doctor_t *doctor;
    patient_t *patient;
    switch (commend)
    {
    case 1:
        //获取登录信息
        platform_get_manage_login_data(message);
        break;
    case 2:
        //返回病人的数量
        *(int *)parameter = listCURRENT_LIST_LENGTH(&manager.patient_LM);
        break;
    case 3:
        //获取某一系列病人的信息
        //参数是一个int32_t的数组, 数字的第一个数字是起始位置,第二个数字是结束的位置
        p = parameter;
        platform_manage_getpat_data(message, *p, *(p+1));
        break;
    case 4:
        //获取一个医生的信息
        //参数是医生的id
        doctor = platform_get_doc(parameter);
        if(doctor != ERROR)
        {
            sprintf(message, "医生 %s 编号 %s 职称 %s 部门 %s\r\n",
            doctor->login.name, 
            doctor->login.id, 
            doctor->level, 
            doctor->service);
        }else{
            sprintf(message, "没有这一个医生\r\n");
            *(int8_t *)parameter = 0;
        }
        break;
    case 5:
        //删除一个医生
        //参数是医生的id
        doctor = platform_get_doc(parameter);
        if(doctor!= ERROR)
        {
            sprintf(message, "已经删除医生 %s 编号 %s 职称 %s 部门 %s\r\n",
            doctor->login.name, 
            doctor->login.id, 
            doctor->level, 
            doctor->service);
            platform_del_doctor(doctor);
        }else{
            sprintf(message, "没有这一个医生\r\n");
        }
        break;
    case 6:
        //对医生的信息进行修改
        /*参数是 (*doc_msg)[31]
        第一个字符串是医生的id
        第二个参数的[0]位置保存有要改变的参数
        第三个参数是改变以后的参数*/
        doc_msg = parameter;
        doctor = platform_get_doc(doc_msg[0]);
        //printf("测试");while(1);
        if(doctor!=ERROR)
        {
            
            platform_manage_chg_doc(doctor, message, parameter);
        }else{
            sprintf(message, "没有这一个医生\r\n");
        }
        break;
    case 7:
        //参数是部门的名字字符串
        platform_department_init(parameter);
        sprintf(message, "添加成功\r\n");
        break;
    case 8:
        //添加一个医生
        //获取到的参数 int8_t (*doc_msg)[31]类型, 0名字 1职位 2职称 3密码 4工作时间 5-0接待人数
        platform_manage_add_doc(message, parameter);
        break;
    case 9:
        //获取一个医生的信息
        //参数是医生的id
        patient = platform_get_patient(parameter);
        if(patient != ERROR)
        {
            sprintf(message, "病人 %s 编号 %s\r\n",
            patient->login.name, 
            patient->login.id);
        }else{
            sprintf(message, "没有这一个病人\r\n");
            *(int8_t *)parameter = 0;
        }
        break;
    case 10:
        //删除一个病人
        //参数是病人的id
        patient = platform_get_patient(parameter);
        if(patient!=ERROR)
        {
            sprintf(message, "已经删除病人 %s 编号 %s\r\n",
            patient->login.name, 
            patient->login.id);
            platform_del_patient(patient);
        }else{
            sprintf(message, "没有这一个病人\r\n");
        }
        break;
    case 11:
        //对病人进行修改
        /*参数是 (*p)[31]
        第一个字符串是病人的id
        第二个参数的[0]位置保存有要改变的参数
        第三个参数是改变以后的参数*/
        doc_msg = parameter;
        patient = platform_get_patient(doc_msg[0]);
        //printf("测试");while(1);
        if(patient!=ERROR)
        {
            
            platform_manage_chg_pat(patient, message, parameter);
        }else{
            sprintf(message, "没有这一个病人\r\n");
        }
        break;
    case 12:
        //获取一些其他的信息
        platform_manage_get_msg(message, parameter);
        break;
    default:
        break;
    }
}