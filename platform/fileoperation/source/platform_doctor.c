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
//获取医生的首个病人的信息,方便进行医治
void platform_doctor_get_first_pat(doctor_t *doctor, int8_t* message){
    ListItem_t *list_pat;
    patient_t *patient;
    if(doctor->patient_LM.uxNumberOfItems>0)
    {
        list_pat = listGET_HEAD_ENTRY(&doctor->patient_LM);
        patient = listGET_LIST_ITEM_OWNER(list_pat);
        sprintf(message, "成功获取到一位病人,将为您调取他的信息....\r\n");
        sprintf(message, "%s这个病人的名字是 %s\r\n", message, patient->login.name);
        sprintf(message, "%s他当前的状态是 %s \r\n", message, patient->doctor_L.xItemValue=='0'?"还没有初诊":"初诊的等待复诊");

    }else
    {
        sprintf(message, "您现在没有病人等待处理,请耐心等待...\r\n");
    }
}
//医生对病人进行治疗
void platform_doctor_deal_first_pat(doctor_t *doctor,int8_t *message, int8_t choice)
{
    ListItem_t *list_pat;
    patient_t *patient;
    if(doctor->patient_LM.uxNumberOfItems>0)
    {
        list_pat = listGET_HEAD_ENTRY(&doctor->patient_LM);
        patient = listGET_LIST_ITEM_OWNER(list_pat);
        if(choice == '1'){
            platform_doc_deal_pat(doctor, patient, '1');
            sprintf(message, "已经治疗过了,病人会在之后进行复诊\r\n");
        }
        else if(choice == '2'){
            platform_doc_deal_pat(doctor, patient, '2');
            sprintf(message, "已经治疗过了, 恭喜病人痊愈!!!\r\n");

        }
        else if(choice == '3'){
            platform_doc_deal_pat(doctor, patient, '3');
            sprintf(message, "已经让病人移步其他的诊室\r\n");
        }

    }else
    {
        sprintf(message, "你现在没有病人....\r\n请耐心等待\r\n");
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
            //获取医生的部分病人信息
            p = parameter;
            platform_doctor_getpat_data(doctor, message, *p, *(p+1));
            break;
        case 4:
            platform_doctor_get_first_pat(doctor, message);
            break;
        case 5:
            platform_doctor_deal_first_pat(doctor, message, parameter);
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