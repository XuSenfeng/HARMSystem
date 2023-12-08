#ifndef APP_MAIN_H
#define APP_MAIN_H
#include "list.h"
#include "platform_main.h"
#include <stdio.h>

typedef struct{
    int8_t id[21];
    int8_t passwd[31];
    int8_t identity;
}base_data;

#endif // !APP_MAIN_H