#ifndef PLATFORM_MAIN_H
#define PLATFORM_MAIN_H
#include "type.h"
#include "list.h"
#include "app_main.h"
typedef struct
{
    int8_t id[21];
    int8_t name[21];
    int8_t passwd[31];
}message_to_login_t;

//单个科室的结构体
typedef struct{
    int8_t name[20];
    ListItem_t department_L;
    List_t doctors_LM;
}outpatient_service_t;
//呼吸内科的结构体

//单个的门诊
typedef struct 
{
    int8_t name[20];
    ListItem_t manage_L;    //保存门诊所在的管理者
    List_t services_LM;
}one_department_t;


//管理者的对象
typedef struct {
    message_to_login_t login;   //登录信息
    List_t doctors_LM;       //管理所有的医生
    List_t patient_LM;      //管理所有的病人
    List_t departments_LM;
}manager_t;


//医生的对象
typedef struct 
{
    message_to_login_t login;   //登录信息
    ListItem_t manage_L;    //他自己的管理节点
    ListItem_t service_L;
    List_t patient_LM;       //管理他的所有病人的管理节点
    char service[21];
}doctor_t;

//病人的对象
typedef struct{
    message_to_login_t login;
    ListItem_t manage_L;
    ListItem_t doctor_L;
}patient_t;

void platform_init();
void platform_out();
void platform_manage_init();
doctor_t * platform_init_doctor(char *name, char *id, char *passwd , char *work);
int32_t platform_login(int8_t *id, int8_t *passwd, int8_t choice);
patient_t * platform_init_patient(char *name, char *id, char *passwd);
outpatient_service_t * platform_get_service(char *name);
one_department_t * platform_init_department(char *name);
outpatient_service_t * platform_init_service(char *name, one_department_t* department);

#endif /*PLATFORM_MAIN_H*/
