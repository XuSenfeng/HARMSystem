#ifndef APP_MAIN_H
#define APP_MAIN_H
#include "list.h"
#include "platform_main.h"
#include <stdio.h>
//保存登录信息的结构体
typedef struct{
    int8_t id[21];      //保存登录的人的id
    int8_t passwd[31];  //保存登录的人的密码
    int8_t identity;    //保存登录的人的身份'1'病人, '2'医生 '3'管理者
}base_data;

#endif // !APP_MAIN_H