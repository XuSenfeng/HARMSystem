#ifndef APP_MAIN_H
#define APP_MAIN_H
#include "list.h"
#include "platform_main.h"
#include <stdio.h>
//�����¼��Ϣ�Ľṹ��
typedef struct{
    int8_t id[21];      //�����¼���˵�id
    int8_t passwd[31];  //�����¼���˵�����
    int8_t identity;    //�����¼���˵����'1'����, '2'ҽ�� '3'������
}base_data;

#endif // !APP_MAIN_H