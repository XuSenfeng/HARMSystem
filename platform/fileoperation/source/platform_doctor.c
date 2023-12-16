/**
  ******************************************************************************
  * @file    platform_dictor.c
  * @version V1.0
  * @date    2023-12-10
  * @brief   这个文件是数据库的API层,主要是为了实现医生的命令API函数
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

#include "platform_doctor.h"


/**
  * @brief  获取医生的登录时候显示的
  * @param  医生结构体指针指向想要获取信息的医生
  * @param  获取到的信息应该保存的结构体
  * @retval 无
  */
void platform_get_doctor_login_data(doctor_t *doctor, int8_t * message)
{
    sprintf(message, " %s 医生您好\r\n", doctor->login.name);
    sprintf(message, "%s您当前有%d个病人待处理\r\n", message,doctor->patient_LM.uxNumberOfItems);
    
}
/**
  * @brief  获取医生的病人部分信息
  * @param  医生结构体指针指向想要获取信息的医生
  * @param  获取到的信息应该保存的结构体
  * @param  起始的病人的位数
  * @param  结束的病人的位数
  * @retval 无
  */
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

/**
  * @brief  获取医生的首个病人的信息,方便进行医治,没有病人的时候也会有对应的处理
  * @param  医生结构体指针指向想要获取信息的医生
  * @param  获取到的信息应该保存的结构体
  * @retval 无
  */
void platform_doctor_get_first_pat(doctor_t *doctor, int8_t* message){
    ListItem_t *list_pat;
    patient_t *patient;
    if(doctor->patient_LM.uxNumberOfItems>0)
    {
        //当医生有待处理的病人的时候
        list_pat = listGET_HEAD_ENTRY(&doctor->patient_LM);
        patient = listGET_LIST_ITEM_OWNER(list_pat);
        sprintf(message, "成功获取到一位病人,将为您调取他的信息....\r\n");
        sprintf(message, "%s这个病人的名字是 %s\r\n", message, patient->login.name);
        sprintf(message, "%s他当前的状态是 %s \r\n", message, patient->doctor_L.xItemValue=='0'?"还没有初诊":"初诊的等待复诊");

    }else
    {
        //没有要处理的病人
        sprintf(message, "您现在没有病人等待处理,请耐心等待...\r\n");
    }
}
/**
  * @brief  医生对病人进行治疗
  * @param  医生结构体指针指向想要获取信息的医生
  * @param  获取到的信息应该保存的结构体
  * @param  具体的处理方式 '1'病人需要复诊 '2'病人不需要复诊 '3'让病人去其他的诊室
  * @retval 无
  */
void platform_doctor_deal_first_pat(doctor_t *doctor,int8_t *message, int8_t choice)
{
    ListItem_t *list_pat;
    patient_t *patient;
    if(doctor->patient_LM.uxNumberOfItems>0)
    {
        //有可以治疗的病人
        list_pat = listGET_HEAD_ENTRY(&doctor->patient_LM);
        patient = listGET_LIST_ITEM_OWNER(list_pat);
        sprintf(patient->message, "\0");
        if(choice == '1'){
            platform_doc_deal_pat(doctor, patient, '1');
            sprintf(message, "已经治疗过了,病人会在之后进行复诊\r\n");
            sprintf(patient->message, "已经治疗过了,在之后进行复诊");
        }
        else if(choice == '2'){
            platform_doc_deal_pat(doctor, patient, '2');
            sprintf(message, "已经治疗过了, 恭喜病人痊愈!!!\r\n");
            sprintf(patient->message, "已经治疗过了,恭喜病人痊愈!!!");
        }
        else if(choice == '3'){
            platform_doc_deal_pat(doctor, patient, '3');
            sprintf(message, "已经让病人移步其他的诊室\r\n");
            sprintf(patient->message, "请您移步其他的诊室");
        }

    }else
    {
        sprintf(message, "你现在没有病人....\r\n请耐心等待\r\n");
    }
}
/**
  * @brief  医生给病人发消息
  * @param  医生结构体指针指向想要获取信息的医生
  * @param  获取到的信息应该保存的结构体
  * @param  要发送的消息
  * @retval 无
  */
void platform_doctor_send_msg(doctor_t *doctor,int8_t *message, int8_t *doc_msg){
    ListItem_t *list_pat;
    patient_t *patient;
    if(doctor->patient_LM.uxNumberOfItems>0)
    {
        sprintf(patient->message, "\0");
        //有可以传递信息的病人
        list_pat = listGET_HEAD_ENTRY(&doctor->patient_LM);
        patient = listGET_LIST_ITEM_OWNER(list_pat);
        sprintf(patient->message, "%s", doc_msg);
        sprintf(message, "添加成功\r\n");
    }else
    {
        sprintf(message, "你现在没有病人....\r\n请耐心等待\r\n");
    }

}
/**
  * @brief  这个是用户的平台接口,根据命令返回信息
  * @param  命令
  * @param  登录的医生的id
  * @param  获取到的信息应该保存的结构体
  * @param  其它参数
  * @retval 无
  */
void platform_doctor_commend(int8_t commend, int8_t *id, int8_t *message, void *parameter)
{
    
    doctor_t *doctor;
    int32_t ret;
    doctor = platform_get_doc(id);
    //printf("获取医生信息%s", doctor->login.name);while(1);
    int32_t *p;
    int8_t (*p_8)[30];
    int8_t id_n[21];
    if(doctor != ERROR)
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
            /*获取第一个病人的信息,
            第二个参数是一个数组,有三位int32位的数字,第一个数字是起始的个数,第二个数字是结束的数字*/
            platform_doctor_get_first_pat(doctor, message);
            break;
        case 5:
            /*治疗第一个病人
            参数是治疗的方式int8_t类型
            '1': 进一步治疗
            '2': 治疗结束
            '3': 不治疗,请他走人*/
            platform_doctor_deal_first_pat(doctor, message, parameter);
            break;
        case 6:
            /*向第一个病人发送信息
            参数是要发送的信息*/
            platform_doctor_send_msg(doctor, message, parameter);
            break;
        default:
            break;
        }
    }else
    {
        sprintf(message, "获取医生失败\r\n");
    }
}