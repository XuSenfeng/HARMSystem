#include "platform_doctor.h"

void platform_get_doctor_login_data(doctor_t *doctor, int8_t * message)
{
    sprintf(message, " %s 医生您好\r\n", doctor->login.name);
    sprintf(message, "%s您当前有%d个病人待处理\r\n", message,doctor->patient_LM.uxNumberOfItems);
    
}

void platform_doctor_getpat_data(doctor_t *doctor, int8_t *message, int32_t begin, int32_t num){

    patient_t *patient;
    outpatient_service_t *service;
    int32_t i, k=0;
    ListItem_t *list_test;
    //清空缓冲区
    sprintf(message, "\0");
    /*测试代码, 会显示现在已经注册的所有的部门以及门诊*/
    list_test = listGET_HEAD_ENTRY(&doctor->patient_LM);
    patient = listGET_LIST_ITEM_OWNER(list_test);
    
    for(i=0;i<doctor->patient_LM.uxNumberOfItems;i++)
    {
        if(k>=begin && k<begin + num)
            sprintf(message, "%s 病人%d号 %s %s 当前的状态是 %d\r\n", 
            message, k+1,
            patient->login.name, patient->login.id, 
            patient->doctor_L.xItemValue);
        
        k++;
        list_test = listGET_NEXT(list_test);
        patient = listGET_LIST_ITEM_OWNER(list_test);

    }

}


//这个是用户的平台接口,根据命令返回信息
void platform_doctor_commend(int8_t commend, int8_t *id, int8_t *message, void *parameter)
{
    
    doctor_t *doctor;
    int32_t ret;
    doctor = platform_get_doc(id);
    //printf("获取医生信息%s", doctor->login.name);while(1);
    int32_t *p;
    int8_t (*p_8)[30];
    int8_t id_n[21];

    if(doctor != -1)
    {
        switch (commend)
        {
        case 1:
            //获取登录信息
            platform_get_doctor_login_data(doctor, message);
            break;
        case 2:
            //获取有多少的病人待处理
            *(int *)parameter = listCURRENT_LIST_LENGTH(&doctor->patient_LM);
            break;
        case 3:
            p = parameter;
            platform_doctor_getpat_data(doctor, message, *p, *(p+1));
            break;
        case 4:

            break;
        case 5:

            break;
        case 6:

            break;
        default:
            break;
        }
    }else
    {
        sprintf(message, "获取医生失败\r\n");
    }
}