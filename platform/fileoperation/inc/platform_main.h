#ifndef PLATFORM_MAIN_H
#define PLATFORM_MAIN_H
#include "type.h"
#include "list.h"
#include "app_main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
//预约状态
#define WITHOUT_APPLICATION             0
#define FIRST_VISIT_DOCTOR              1
#define SUBSQUENT_VISIT                 2

/*知名专家、主任医师、副主任医师、主治医师和医师。*/
#define DOC_LEVE_1              "知名专家"
#define DOC_LEVE_2              "主任医师"
#define DOC_LEVE_3              "副主任医师"
#define DOC_LEVE_4              "主治医师"
#define DOC_LEVE_5              "医师"




//测试代码开关
#define DEBUG                           0
//基础信息结构体
typedef struct
{
    int8_t id[21];      //id
    int8_t name[21];    //名字
    int8_t passwd[31];  //密码
}message_to_login_t;

//单个科室的结构体
typedef struct{
    int8_t name[20];        //门诊的名字
    ListItem_t department_L;    //所在的部门
    List_t doctors_LM;      //下面的所有医生
}outpatient_service_t;

//单个的部门 
typedef struct 
{
    int8_t name[20];        //部门的名字
    ListItem_t manage_L;    //保存门诊所在的管理者
    List_t services_LM;     //保存下面的门诊
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
    ListItem_t service_L;   //在某一个部门下面的链表
    List_t patient_LM;       //管理他的所有病人的管理节点
    int8_t service[21];     //保存医生的部门的名字
    int8_t level[30];       //保存医生的等级的名字
    int8_t workday[15];     //保存医生的工作时间信息
    int32_t num_to_accept;  //保存医生最大的接待量
}doctor_t;

//病人的对象
typedef struct{
    message_to_login_t login;       //登录信息
    ListItem_t manage_L;            //管理节点
    ListItem_t doctor_L;            //医生节点
    int8_t doc_id[21];              //自己的医生的id
    int8_t message[140];            //医生发过来的信息
}patient_t;

void platform_init();
void platform_out();
int32_t platform_login(int8_t *id, int8_t *passwd, int8_t choice);
#endif /*PLATFORM_MAIN_H*/
