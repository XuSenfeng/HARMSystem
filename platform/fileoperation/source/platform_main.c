/**
  ******************************************************************************
  * @file    platform_main.c
  * @version V1.0
  * @date    2023-12-10
  * @brief   这个文件是数据库的API层,主要是为了实现数据库初始化,退出函数以及获取某一个人是否在数据库里面的结果,用于登录
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



#include "platform_main.h"



manager_t manager;





/**
  * @brief  根据一个人的id以及密码判断是否登陆成功,成功的话返回对应的那个人的结构体
  * @param  id:登录的id
  * @param  passwd:登录的密码
  * @param  choice:登录的选择'1'病人'2'医生'3'管理员
  * @retval 1成功 ERROR失败
  */
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
            return ERROR;
        
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
        return ERROR;
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
        return ERROR;
    }else
    {
        return (void *)ERROR;
    }
}
/*********************************************平台设置使用的函数***********************************************/

/**
  * @brief  平台加载函数,用于平台的初始化,获取数据
  * @param  无
  * @retval 无
  */
void platform_init()
{
    platform_manage_init();
#if DEBUG
    platform_test();
#endif
}



/**
  * @brief  平台退出函数,主要用于释放空间,以及保存信息
  * @param  无
  * @retval 无
  */
void platform_out()
{
    int32_t i, j;
    ListItem_t *list_now, *list_next;
    doctor_t *doctor;
    patient_t *patient;
    platform_manage_out();
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

