#ifndef APP_MAIN_H
#define APP_MAIN_H
#include "list.h"
void platform_test(void);
//登录信息
typedef struct
{
    char id[21];
    char name[21];
    char passwd[31];
}message_to_login_t;

//医院医生结构的结构体,待实现
typedef struct{

}department_t;

//管理者的对象
typedef struct {
    message_to_login_t login;   //登录信息
    List_t doctors_LM;       //管理所有的医生
    List_t patient_LM;      //管理所有的病人
}manager_t;


//医生的对象
typedef struct 
{
    message_to_login_t login;   //登录信息
    ListItem_t manage_L;    //他自己的管理节点
    List_t patient_LM;       //管理他的所有病人的管理节点
}doctor_t;

//病人的对象
typedef struct{
    message_to_login_t login;
    ListItem_t manage_L;
    ListItem_t doctor_L;
}patient_t;


#endif // !APP_MAIN_H