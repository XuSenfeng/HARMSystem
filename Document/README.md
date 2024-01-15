# 医院预约管理系统









> 作者: 焦浩洋(XvSenfeng)
>
> 学号: 1231002004
>
> 班级: 信息工程学院23级2班, 电子信息专业







日期: 2023-12-6

开源协议: MIT

使用编译工具gcc version 8.1.0 (x86_64-posix-sjlj-rev0, Built by MinGW-W64 project)

使用脚本工具GNU Make 4.3

[XuSenfeng/HARMSystem: 医院管理系统(C语言大作业) (github.com)](https://github.com/XuSenfeng/HARMSystem)











## 简介

![image-20240115101911632](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401151147692.png)

### 文件

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

### 代码结构

使用四层结构实现医院预约管理系统, 管理app两层以及数据库两层, 只需要移植六个函数就可以在不同的数据库之间移植, 医院的结构, 医生信息,  病人信息全部可以动态加载

![image-20240115111324724](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401151113763.png)

### 界面

![image-20240115115417778](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401151154817.png)

## 思路

### 数据管理(数据库层)

主要使用链表进行实现, 实现行外部文件加载信息以及在应用平台通过命令进行加载信息, 以及对于数据进行不同方式的修改

所有的部门信息, 除了管理者以外的用户信息从外部的文件进行加载, 请按文件的格式进行提供信息

主要的查询路径有两种

![image-20240115111420087](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401151114145.png)

1. 

> 通过管理者查找下面的部门, 之后从部门, 门诊, 医生, 病人的链表依次进行
>
> 主要用于按照部门进行筛选的时候, 通过比较部门以及门诊的名字进行比对

2. 

> 所有的医生和病人会直接挂载在管理者的对象下面, 直接遍历链表实现对于医生或者病人的具体信息

### 上层操作(用户层)

主要用于实现一个用户友好的界面, 有三种不同的用户

进入以后用户进行选择实际的登录方式, 这时候输入的信息会用于之后的权限设定

病人可以选择登录自己的用户或者新建用户, 之后查看现有的医生, 根据医生的id给自己进行预约

医生可以查看自己的病人, 对病人进行治疗,并且给病人发送自定义信息

管理员可以添加删除医生, 删除病人, 修改医生或者病人的信息, 查看所有的医生和病人, 或者从文件里面导入新的数据等

> 管理员的登录id: 000, 登录密码123456, 不可修改

### API层(两层)

应用平台调用数据库的API实现应用不同的功能

使用到的函数有六个会在移植部分讲解

### 主要数据类型(对象, 功能以及权限)

#### 部门

![image-20240115120434893](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401151204927.png)

保存有一个部门的名字, 部门下面的门诊的管理节点, 以及一个用于管理他的管理者的节点项

主要用于在进行门诊相关操作的时候进行查找

#### 门诊

![image-20240115120507977](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401151205008.png)

保存有门诊的名字, 门诊的医生的管理节点以及用于管理他的部门的节点项

#### 管理者

![image-20240115120617765](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401151206799.png)

保管有部门, 医生, 病人的管理节点, 自己的个人信息

拥有最大的权限, 可以实现对于医生的信息的修改, 病人的信息的修改以及对某一条预约的封存

可以通过文件等方式进行医生以及病人的添加, 同时可以查看当前医院的一些指标

> 主要的功能在platform_manage.c文件中实现, 对应函数说明见函数注释

#### 医生

![image-20240115120820444](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401151208485.png)

保存有医生的基本信息, 医生的工作时间, 医生的病人的接待数, 最大接待数量等基本信息, 以及用于管理的他的部门的节点和管理者节点

医生的主要权限就是查看自己的信息, 以及预约了自己的病人的信息, 并且对病人进行治疗, 治疗的时候有多种不同的治疗方式, 比如需要继续治疗, 和不需要等

> 主要的功能在platform_doctor.c文件中实现, 对应函数说明见函数注释

#### 病人

![image-20240115120928537](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401151209573.png)

保存有病人的基本信息, 病人的提示信息, 病人的状态, 以及用于管理的他的医生的节点(没有预约的时候是不进行挂载)

病人的主要权限就是查看医生的信息, 以及通过医生的信息可以对自己进行预约

在没有用户的时候可以进行创建用户

> 主要的功能在platform_patient.c文件中实现, 对应函数说明见函数注释

#### 信息结构体

![image-20240115131422761](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401151314791.png)

保存基本信息, id, 密码, 名字等

主要用于登录时候的信息的验证, 以及在后续进行查找时候的权限的管理

## 算法

### 主要使用的数据类型(链表)

![image-20240115110522899](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401151105943.png)

> 在文件list.c和.h里面将链表的操作单独抽象出来
>
> 主要的操作包括新建链表, 初始化链表, 多种方式的插入, 删除链表, 获取链表的拥有者等

在实现链表操作的时候主要实现以下功能

#### 链表插入(有序)

获取链表管理节点, 之后遍历链表, 依次比较链表的每一项的大小, 在发现新节点的数值在某两个节点之间的时候进行节点指针的更新

![image-20240115115631718](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401151156757.png)

#### 链表插入(尾部)

采用遍历的方式首先获取管理节点, 之后从管理节点处获取尾部节点, 将尾节点指针指向新节点

![image-20240115115916545](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401151159589.png)

#### 链表删除

获取链表管理节点, 之后遍历链表, 依次比较链表的指针, 在发现节点的时候对前后节点的指向进行更新

![image-20240115120014061](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401151200099.png)

### 链表查找

使用遍历的方式进行查找

#### 其他

使用宏定义等实现链表的快速获取特征值, 拥有者, 根节点快速获取链表项个数等

### 排序算法(冒泡排序)

比较相邻的元素。如果第一个比第二个大，就交换他们两个。

对每一对相邻元素作同样的工作，从开始第一对到结尾的最后一对。这步做完后，最后的元素会是最大的数。

针对所有的元素重复以上的步骤，除了最后一个。

持续每次对越来越少的元素重复上面的步骤，直到没有任何一对数字需要比较。

## 数据文件格式

![image-20240110134237312](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101342364.png)

### 数据文件逐项分析

+ 医院拥有的部门数量

之后按照数量排列部门, 每一行依次是部门的名字, 下面的科室个数, 和科室的名字

+ 医生的数量

之后按照医生的数量每一行依次是医生的id, 医生的名字, 医生的登录密码, 医生的诊室, 医生的职位, 医生最大接待数量, 医生的工作时间, 医生已经接待的病人数量和他的收益

+ 病人的数量

按照病人的数量之后就是病人的id, 病人的名字, 病人的登录密码, 当前的状态(0:没有预约, 1:预约了等待治疗, 2:复诊), 预约的医生的id(没有预约的时候为0), 医生的留言

### 文件数据的处理(数据的初始化)

+ 部门以及门诊

根据文件的内容依次申请多个部门结构体, 使用malloc, 没有个数限制, 并进行初始化数据的写入, 之后使用链表挂载的方式进行连接, 部门在管理者下面, 门诊在部门下面

+ 医生

根据获取的信息进行医生结构的申请, 并进行数据的写入, 之后会根据医生的部门名字, 通过部门查找的方式找到对应的部门进行链表的挂载, 以及根据自己的职称在管理者下面进行排序挂载

+ 病人

根据病人的信息进行初始化, 初始化过后会根据预约状态进行处理, 如果已经进行预约, 就对医生进行查找, 通过管理者下面的医生节点进行遍历, 找到以后进行挂载

## 代码特点

### 函数命名

函数名第一段是实际的存在的层, 有app层和platformceng

第二段是所在的文件名, 比如doctor, patient等, 用于方便查找

之后是对于函数功能的描述

+ 示例

```c
platform_patient_getdoc_data_num
```

### 变量名

主要使用的链表项会使用xxx_L或者list_xxx, 链表的根节点(用于管理)会使用xxx_LM

结构体在命名的时候会使用xxx_t

### 其他变量

为了方便在不同平台下的移植, 将所有的变量按照长度以及有无符号进行命名, 在type.h文件中进行定义

### 宏定义

主要使用的命令会在头文件中以类似于函数名的方式进行存放

### 文件名

按照 平台名_职能.c进行命名, 例如`app_doctor.c`文件中存放的是app层中医生相关的代码

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

![image-20240115101911632](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401151019666.png)

直接打开output文件夹里面的result.exe文件, 需要在同一个文件夹下面有数据存放的document.txt

![image-20240110135530459](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101355483.png)

### 整体思路

在进入的时候从文件中获取到数据, 之后对数据暂存在内存里面, 在用户进行操作的时候进行内存中数据的更新, 退出的时候重新对数据文件进行写入

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

##### 查看医生信息

![image-20240114235505206](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401142355253.png)

有四种方式进行查看医生的信息

![image-20240115131129547](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401151311600.png)

在显示的时候支持向上翻页, 选择页数以及随时退出, 在病人界面可以直接选择这时候进行预约

##### 预约医生

![image-20240110125930529](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101259566.png)

##### 查看当前状态

![image-20240110125943131](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101259171.png)

##### 取消预约

![image-20240110130021819](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101300861.png)

![image-20240110130030712](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101300754.png)

### 医生

#### 登录

![image-20240110130134040](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101301080.png)

和病人的相同

#### 登陆成功

![image-20240110130149209](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101301250.png)

登陆以后会显示当前的状态, 包括等待治疗的病人以及已经治疗过的病人和当前的收益

##### 查看病人信息

![image-20240115133005835](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401151330889.png)

##### 对病人进行治疗

![image-20240110130859973](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101309014.png)

自动获取到预约时间最长的病人, 进行治疗会改变病人的状态, 请他换医生会取消他的预约, 暂时不进行治疗会把他放在当前等待治疗的病人队列最后

![image-20240110131046028](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101310070.png)

之后可以选择给病人传达信息, 这个信息会显示在病人的登录界面

![image-20240110131135508](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101311549.png)

![image-20240110131228833](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101312872.png)

##### 显示当前信息

![image-20240110131201702](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101312742.png)

### 管理员

#### 登录

![image-20240110131304645](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101313687.png)

管理员的id默认为000, 不可以修改

#### 登陆成功

![image-20240115133137418](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401151331470.png)

##### 获取医生信息和病人获取的相同

##### 获取病人信息

![image-20240110131501929](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101315009.png)

##### 删除医生

![image-20240110131553429](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101315472.png)

![image-20240110131627188](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101316229.png)

会清除当前医生的病人的预约信息

##### 修改医生信息

![image-20240110131749746](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101317786.png)

可以选择某一个医生的某一条信息

##### 添加医生

![image-20240110131933586](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101319630.png)

![image-20240110132716028](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101327072.png)

##### 修改病人信息和医生类似

![image-20240110132911231](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101329270.png)

![image-20240110133259426](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101332481.png)

##### 病人信息封存(病人之后不能通过这一条信息进行登录)

![image-20240115133242689](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401151332739.png)

![image-20240115133329151](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401151333198.png)

> 信息不会丢失, 但是病人无法通过密码进行登录

![image-20240115133452413](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401151334458.png)

##### 从文件添加信息

![image-20240115133526777](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401151335826.png)

> 输入文件名就可以进行信息的补充

##### 查看其他信息

![image-20240110133503642](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101335682.png)

![image-20240110133515508](https://picture-01-1316374204.cos.ap-beijing.myqcloud.com/image/202401101335550.png)

### 退出

会把信息更新到记录的文件里面

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

## 心得

作为一个大一的大学生，在完成C语言大作业——医院管理系统的过程中，我收获了许多经验和心得。以下是我在编写这个系统时的一些体会：

首先，系统功能的设计是非常重要的。在开始编写代码之前，我首先进行了对医院管理系统的功能进行梳理和规划。通过细致分析和理解需求，我确定了系统所需要实现的功能模块，包括医生信息管理、患者信息管理、挂号和退号、病历管理等等。这些功能模块的清晰定义和合理划分，为后续代码的编写提供了良好的基础。

其次，良好的代码结构和逻辑也是至关重要的。在编写代码时，我尽量遵循C语言的编码规范，注重良好的变量命名和函数命名，使得代码易于理解和维护。我将系统的各个功能模块进行模块化设计，将它们封装成独立的函数，通过函数的调用和返回值来实现功能之间的逻辑关联。这种结构化的编程风格不仅提高了代码的可读性，还方便了代码的调试和扩展。

此外，代码的健壮性和安全性也是需要重视的。在输入输出交互的过程中，我增加了一些错误处理和异常处理的机制，避免程序因为输入错误或者其他异常导致的崩溃或者意外结果。例如，在输入患者信息时，我使用了合理的校验机制，确保输入的数据格式正确和完整；在处理某些操作时，我增加了异常处理的逻辑，防止程序异常退出。

最后，充分利用计算机科学的相关知识来提高程序效率和性能。在实现系统功能的过程中，我运用了一些数据结构和算法的知识，如链表、查找、排序等，来提高查询、排序和数据访问的效率。通过充分利用计算机的计算能力和存储能力，我尽可能地优化了代码的性能。

总的来说，完成这个医院管理系统的大作业是一次非常有挑战性的体验。通过这个过程，我不仅提升了对C语言的理解和熟练程度，还锻炼了问题分析和解决问题的能力。希望在今后的学习中，能够继续不断提高自己的编程水平和技术能力。
