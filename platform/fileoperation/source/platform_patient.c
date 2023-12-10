/**
  ******************************************************************************
  * @file    platform_patient.c
  * @version V1.0
  * @date    2023-12-10
  * @brief   这个文件是数据库的API层,主要是为了实现病人的命令API函数
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


#include "platform_patient.h"
extern manager_t manager;

void platform_patient_getdoc_data_d(int8_t *message, int32_t begin, int32_t num){
    one_department_t *department;
    outpatient_service_t *service;
    doctor_t *doctor;
    int32_t i, k=0, j, t;
    ListItem_t *list_test, *list_test2, *list_test3;
    //清空缓冲区
    sprintf(message, "\0");
    /*测试代码, 会显示现在已经注册的所有的部门以及门诊*/
    list_test = listGET_HEAD_ENTRY(&manager.departments_LM);
    department = listGET_LIST_ITEM_OWNER(list_test);
    for(i=0;i<manager.departments_LM.uxNumberOfItems;i++)
    {
        if(k>=begin && k<begin + num)
            sprintf(message, "%s\r\n部门 %s 下面有 %d 个门诊\r\n", message, department->name, department->services_LM.uxNumberOfItems);
        list_test2 = listGET_HEAD_ENTRY(&department->services_LM);
        service = listGET_LIST_ITEM_OWNER(list_test2);
        for(j=0;j<department->services_LM.uxNumberOfItems;j++)
        {
            if(k>=begin && k<begin + num)
                sprintf(message, "%s\t门诊%d是: %s\r\n", message, j+1, service->name);
            
            //获取所有医生
            list_test3 = listGET_HEAD_ENTRY(&service->doctors_LM);
            doctor = listGET_LIST_ITEM_OWNER(list_test3);
            for(t=0;t<service->doctors_LM.uxNumberOfItems;t++)
            {
                if(k>=begin && k<begin + num)
                    sprintf(message, "%s\t\t医生 %s 的id是 %s  %s\r\n", message, doctor->login.id, doctor->login.name, doctor->level);
                list_test3 = listGET_NEXT(list_test3);
                doctor = listGET_LIST_ITEM_OWNER(list_test3);
            }

            list_test2 = listGET_NEXT(list_test2);
            service = listGET_LIST_ITEM_OWNER(list_test2);

            
        }
        k++;
        list_test = listGET_NEXT(list_test);
        department = listGET_LIST_ITEM_OWNER(list_test);

    }

}

void platform_patient_getdoc_data_L(int8_t *message, int32_t begin, int32_t num){

    doctor_t *doctor;
    outpatient_service_t *service;
    int32_t i, k=0, j, t;
    ListItem_t *list_test, *list_test2, *list_test3;
    //清空缓冲区
    sprintf(message, "\0");
    /*测试代码, 会显示现在已经注册的所有的部门以及门诊*/
    list_test = listGET_HEAD_ENTRY(&manager.doctors_LM);
    doctor = listGET_LIST_ITEM_OWNER(list_test);
    for(i=0;i<manager.doctors_LM.uxNumberOfItems;i++)
    {
        
        if(k>=begin && k<begin + num)
            sprintf(message, "%s%s %s 医生职位是 %s 预约id是 %s 还可以接待%d个人\r\n", 
            message, doctor->level,
            doctor->login.name, doctor->service, 
            doctor->login.id, doctor->num_to_accept - doctor->patient_LM.uxNumberOfItems);
        k++;
        list_test = listGET_NEXT(list_test);
        doctor = listGET_LIST_ITEM_OWNER(list_test);

    }

}


//这个是用户的平台接口,根据命令返回信息
void platform_patient_commend(int8_t commend, char *id, char *message, void *parameter)
{
    patient_t *patient;
    int32_t ret;
    patient = platform_get_patient(id);
    int32_t *p;
    int8_t (*p_8)[30];
    int8_t id_n[21];
    time_t timep;
    struct tm *p_tm;
    if(patient != -1 || strlen(id)==0)
    {
        switch (commend)
        {
        case 1:
            //获取登录信息
            //printf("病人%s, %s\r\n", patient->login.name, patient->login.passwd);
            platform_get_patient_login_data(patient, message);
            break;
        case 2:
            *(int *)parameter = listCURRENT_LIST_LENGTH(&manager.doctors_LM);
            break;
        case 3:
            //申请某一个医生
            ret  = platform_patient_appointment(patient, parameter);
            if(ret == 1)
            {
                sprintf(message, "更新成功\r\n");
            }else
            {
                sprintf(message, "更新失败,请检查您输入的id\r\n");
            }
            break;
        case 4:
            p = parameter;
            platform_patient_getdoc_data_d(message, *p, *(p+1));
            break;
        case 5:
            p_8 = parameter;
            sprintf(message, "");
            time(&timep);
            p_tm=gmtime(&timep);
            sprintf(id_n, "%04d%02d%02d%04d",1900+p_tm->tm_year, 1+p_tm->tm_mon, p_tm->tm_mday, manager.patient_LM.uxNumberOfItems);
            //printf("年%d 月%d 日%d\r\n", 1900+p_tm->tm_year, 1+p_tm->tm_mon, p_tm->tm_mday);
            patient = platform_add_patient(*p_8, id_n, *(p_8+1), '0', "0", "无");
            if(patient==-1)
            {
                sprintf(message, "获取用户失败,原因是生成的id重复,请检查后台的数据\r\n");
            }else
            {
                sprintf(message, "用户 %s 申请成功, 您的id是 %s 请记牢作为登录凭证\r\n", patient->login.name, patient->login.id);
                //保存用户信息
                strcpy(id, patient->login.id);
                sprintf(message, "%s您当前的密码是 %s\r\n",message,  *(p_8+1));
            }
            break;
        case 6:
            p = parameter;
            platform_patient_getdoc_data_L(message, *p, *(p+1));
            break;
        default:
            break;
        }
    }else
    {
        sprintf(message, "获取病人失败\r\n");
    }
}

//获取登录信息
void platform_get_patient_login_data(patient_t *patient, int8_t *message)
{
    uint32_t status;
    doctor_t *doctor;
    
    status = platform_get_patient_status(patient);
    sprintf(message, "尊敬的 %s 先生/女士\r\n", patient->login.name);
    if(status == WITHOUT_APPLICATION)
        sprintf(message, "%s您当前的预约状态是没有预约\r\n", message);
    else if(status == FIRST_VISIT_DOCTOR)
        sprintf(message, "%s您当前的预约状态是预约没有初诊\r\n", message);
    else if(status == SUBSQUENT_VISIT)
        sprintf(message, "%s您当前的预约状态是等待复诊\r\n", message);
    if(patient->doctor_L.xItemValue!=0)
    {
        doctor = platform_get_doc(patient->doc_id);
        sprintf(message, "%s您当前的是 %s 门诊的 %s 医生\r\n", message, doctor->service, doctor->login.name);
    }
    sprintf(message, "%s您当前的信息: \r\n%s\r\n", message, patient->message);
}