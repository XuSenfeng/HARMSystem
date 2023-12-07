
#include "platform_main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
manager_t manager;
void platform_test(void)
{
    ListItem_t * doctor_list, * patient_list;
    doctor_t * doctor;
    patient_t * patient;
    printf("platform\r\n");
    platform_get_doctor("jiao", "111", "123456");
    printf("链表里面有:%d\r\n", listCURRENT_LIST_LENGTH(&manager.doctors_LM));
    doctor_list = listGET_HEAD_ENTRY(&manager.doctors_LM);
    doctor = (doctor_t *)listGET_LIST_ITEM_OWNER(doctor_list);
    printf("医生的信息: %s %s %s\r\n", doctor->login.id, doctor->login.name, doctor->login.passwd);
    platform_get_patient("dong", "222", "123456");
    patient_list = listGET_HEAD_ENTRY(&manager.patient_LM);
    patient = (patient_t *)listGET_LIST_ITEM_OWNER(patient_list);
    printf("患者的信息: %s %s %s\r\n", patient->login.id, patient->login.name, patient->login.passwd);
}
void platform_manage_init()
{
    strcpy(manager.login.id, "000");
    strcpy(manager.login.name, "manage");   
    strcpy(manager.login.passwd, "123456");   
    vListInitialise(&manager.doctors_LM);
    vListInitialise(&manager.patient_LM);
}
//申请一个医生的的结构体,并挂载在管理者名下
doctor_t * platform_get_doctor(char *name, char *id, char *passwd)
{
    doctor_t *doctor_to_init;
    doctor_to_init = malloc(sizeof(doctor_t));
    /**********************节点的初始化**************************/
    //挂载在管理者名下
    vListInitialiseItem(&doctor_to_init->manage_L);
    vListInsertEnd(&manager.doctors_LM, &doctor_to_init->manage_L);
    //挂载父节点
    doctor_to_init->manage_L.pvOwner = doctor_to_init;
    vListInitialise(&doctor_to_init->patient_LM);
    /************************************************************/
    //在这里初始化各种个人信息
    strcpy(doctor_to_init->login.id, id);
    strcpy(doctor_to_init->login.name, name);
    strcpy(doctor_to_init->login.passwd, passwd);


    return doctor_to_init;
}

//申请一个患者的的结构体,并挂载在管理者名下
patient_t * platform_get_patient(char *name, char *id, char *passwd)
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
    strcpy(patient_to_init->login.id, id);
    strcpy(patient_to_init->login.name, name);
    strcpy(patient_to_init->login.passwd, passwd);
    
    return patient_to_init;
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
void *platform_login(int8_t *id, int8_t *passwd, int8_t choice)
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
            return &manager;
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
                return doctor;
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
                return patient;
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
    platform_test();
}
//更新现在的数据,把数据写入到文件里面
void platform_update(){

}


//平台退出函数,主要用于释放空间
void platform_out()
{
    doctor_t *doctor;
    patient_t *patient;
    //把当前的数据存储起来
    platform_update();
    //释放内存
    while(listCURRENT_LIST_LENGTH(&manager.doctors_LM))
    {
        doctor = listGET_HEAD_ENTRY(&manager.doctors_LM);
        uxListRemove(doctor);
    }
    while(listCURRENT_LIST_LENGTH(&manager.patient_LM))
    {
        patient = listGET_HEAD_ENTRY(&manager.patient_LM);
        uxListRemove(doctor);
    }
}