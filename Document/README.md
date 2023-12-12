# 医院预约管理系统

作者: 焦浩洋(XvSenfeng)

日期: 2023-12-6

开源协议: MIT

使用编译工具gcc version 8.1.0 (x86_64-posix-sjlj-rev0, Built by MinGW-W64 project)

使用脚本工具GNU Make 4.3

## 简介

使用四层结构实现医院预约管理系统, 管理app两层以及数据库两层, 只需要移植六个函数就可以在不同的数据库之间移植, 医院的结构, 医生信息,  病人信息全部可以动态加载

![image-20231211155449983](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202312111554040.png)

+ 数据库层

主要使用链表进行实现, 实现行外部文件加载信息以及在应用平台通过命令进行加载信息, 以及对于数据进行不同方式的修改

所有的部门信息, 除了管理者以外的用户信息从外部的文件进行加载, 请按文件的格式进行提供信息

![image-20231211155337282](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202312111553389.png)

![image-20231211155405205](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202312111554261.png)

![image-20231211155433054](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202312111554113.png)

+ 应用平台

有三种不同的用户, 病人可以选择登录自己的用户或者新建用户, 之后查看现有的医生, 根据医生的id给自己进行预约

医生可以查看自己的病人, 对病人进行治疗,并且给病人发送自定义信息

管理员可以添加删除医生, 删除病人, 修改医生或者病人的信息, 查看所有的医生和病人, 或者从文件里面导入新的数据

> 管理员的登录id: 000, 登录密码123456, 不可修改

+ API层(两层)

应用平台调用数据库的API实现应用不同的功能

使用到的函数有六个会在移植部分详细讲解

## 编译

使用make以及gcc进行编译

+ 获得成品

```bash
make compile
```

+ 编译并且运行

```bash
make run
```

## 文件介绍

+ .git: git管理代码迭代
+ .vscode: 使用vscode的生成的项目文件
+ app: 应用层次的文件存放位置
+ + app_dispose.c, app_main.c最上层的文件,实现app
    + app_doctor.c, app_dispose.c, app_patient.c, API层, 调用数据库的接口实现各种功能
+ Document:文档
+ inc: app的头文件存放位置
+ output: 生成的文件的存放的位置
+ platform: 平台层, 可以在这里实现不同数据库的平台
+ + fileoperation: 通过文件管理数据, 本次作业实现的
    + + inc: 头文件位置
        + source: 源代码
        + + list.c: 使用到的数据类型操控函数
            + platform_main.c, platform_doctor.c, platform_patient.c, platform_manage.c, API层实现需要数据传递的函数
            + platform_update.c, 操控信息的底层函数
    + MySQL: 其他数据库, 待实现
+ Makefile: 编译脚本

## 移植

只要实现以下六个函数就可以

```c
void platform_init();
void platform_out();
int32_t platform_login(int8_t *id, int8_t *passwd, int8_t choice);
void platform_doctor_commend(int8_t commend, char *id, char *message, void *parameter);
void platform_manage_commend(int8_t commend,char *message, void *parameter);
void platform_patient_commend(int8_t commend, char *id, char *message, void *parameter);
```

+ platform_init

在platform_main.c文件里面, 主要实现平台在加载的时候需要做的事,比如信息的加载

+ platform_out

在platform_main.c文件里面, 主要实现平台在退出的时候需要做的事,比如信息的保存

+ platform_login

在platform_main.c文件里面, 检测某一个用户是否存在以及是否登录成功

+ platform_doctor_commend

在platform_doctor.c文件里面医生的命令接口, 根据医生发过来的命令以及信息操作底层数据

+ platform_manage_commend

在platform_manage.c文件里面医生的命令接口, 根据管理员发过来的命令以及信息操作底层数据

+ platform_patient_commend

在platform_patien.c文件里面医生的命令接口, 根据病人发过来的命令以及信息操作底层数据

