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

## 测试

### 主界面

![image-20240110122232630](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101222678.png)

选择想要登录的用户身份, 医生和病人身份信息存放在文件document.txt文件里面(文件数据格式在后面)

> 在进行选择的时候只会获取输入的第一个字符

### 病人

#### 登录

![image-20240110124919141](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101249189.png)

可以选择使用之前的账号进行登录或者创建一个新的账户

+ 已经有账号

![image-20240110125137890](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101251931.png)

通过账号密码进行登录, 有三次输入错误的机会

+ 新账号

![image-20240110125643761](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101256841.png)

输入用户的名字以及密码会自动创建一个新的账户, 通过时间创建id



#### 登陆成功

![image-20240110125727649](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101257688.png)

![image-20240110125257576](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101254800.png)

登陆以后会在上面显示当前的用户的状态, 以及是否有医生给他的留言

+ 查看医生信息

![image-20240110125751149](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101257190.png)

有四种方式进行查看医生的信息

![image-20240110125824756](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101258797.png)

在显示的时候支持向上翻页

+ 预约医生

![image-20240110125930529](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101259566.png)

+ 查看当前状态

![image-20240110125943131](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101259171.png)

+ 取消预约

![image-20240110130021819](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101300861.png)

![image-20240110130030712](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101300754.png)

### 医生

#### 登录

![image-20240110130134040](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101301080.png)

和病人的相同

#### 登陆成功

![image-20240110130149209](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101301250.png)

登陆以后会显示当前的状态, 包括等待治疗的病人以及已经治疗过的病人和当前的收益

+ 查看病人信息

![image-20240110130648597](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101306638.png)

+ 对病人进行治疗

![image-20240110130859973](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101309014.png)

自动获取到预约时间最长的病人, 进行治疗会改变病人的状态, 请他换医生会取消他的预约, 暂时不进行治疗会把他放在当前等待治疗的病人队列最后

![image-20240110131046028](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101310070.png)

之后可以选择给病人传达信息, 这个信息会显示在病人的登录界面

![image-20240110131135508](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101311549.png)

![image-20240110131228833](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101312872.png)

+ 显示当前信息

![image-20240110131201702](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101312742.png)

### 管理员

#### 登录

![image-20240110131304645](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101313687.png)

管理员的id默认为000, 不可以修改

#### 登陆成功

![image-20240110131404362](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101314404.png)

+ 获取医生信息和病人获取的相同

+ 获取病人信息

![image-20240110131501929](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101315009.png)

+ 删除医生

![image-20240110131553429](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101315472.png)

![image-20240110131627188](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101316229.png)

会清除当前医生的病人的预约信息

+ 修改医生信息

![image-20240110131749746](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101317786.png)

可以选择某一个医生的某一条信息

+ 添加医生

![image-20240110131933586](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101319630.png)

![image-20240110132716028](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101327072.png)

+ 删除和修改病人信息和医生类似

![image-20240110132848269](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101328311.png)

![image-20240110132911231](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101329270.png)

![image-20240110133259426](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101332481.png)

+ 从文件添加信息

![image-20240110133423392](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101334434.png)

![image-20240110133437093](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101334130.png)

+ 查看其他信息

![image-20240110133503642](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101335682.png)

![image-20240110133515508](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101335550.png)

### 退出

会把信息更新到记录的文件里面

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

## 数据文件格式

![image-20240110134237312](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101342364.png)

+ 医院拥有的部门数量

之后按照数量排列部门, 每一行依次是部门的名字, 下面的科室个数, 和科室的名字

+ 医生的数量

之后按照医生的数量每一行依次是医生的id, 医生的名字, 医生的登录密码, 医生的诊室, 医生的职位, 医生最大接待数量, 医生的工作时间, 医生已经接待的病人数量和他的收益

+ 病人的数量

按照病人的数量之后就是病人的id, 病人的名字, 病人的登录密码, 当前的状态(0:没有预约, 1:预约了等待治疗, 2:复诊), 预约的医生的id(没有预约的时候为0), 医生的留言

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

> commend: 选择需要完成的任务
>
> id: 当前登录的人的id
>
> message: 需要返回的显示信息
>
> parameter: 需要用到的其它参数(详细的解释看注释)

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

