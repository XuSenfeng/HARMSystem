#include "platform_patient.h"
extern manager_t manager;

platform_patient_getdoc_data_d(int8_t *message, int32_t begin, int32_t num){
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
                    sprintf(message, "%s\t\t医生 %s 的id是 %s\r\n", message, doctor->login.id, doctor->login.name);
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

//这个是用户的平台接口,根据命令返回信息
void platform_patient_commend(int8_t commend, char *id, char *message, void *parameter)
{
    patient_t *patient;
    int32_t ret;
    patient = platform_get_patient(id);
    int32_t *p;
    if(patient != -1)
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
}