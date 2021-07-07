# RCS-Tutorial

#### 介绍
This is for RCS beginner.

#### 软件架构
该程序在两台计算机上运行，有三个模块，分别为（计算机1）模块A，模块B和（计算机2）模块C。 
程序运行流程为： 
模块B(发送消息A,B)--->模块A(接收消息A,B,并进行处理，发送消息C)。 
模块A(发送消息C)--->模块C(接收消息C)。


#### 安装教程

1. 确认依赖环境：boost（常用版本有1.54,1.55和1.58）和Java，如果没有Java，需要按以下步骤安装java。(其实安装java的过程即把安装包解压到合适的位置，之后建立软连接)
update-alternatives --install /usr/bin/java java /opt/jdk1.7.0_79/bin/java 300 
update-alternatives --install /usr/bin/javac javac /opt/jdk1.7.0_79/bin/javac 300 
update-alternatives --install /usr/bin/jar jar /opt/jdk1.7.0_79/bin/jar 300
2. 下载RCS安装包/获取团队现成安装包：
http://www.isd.mel.nist.gov/projects/rcslib/rcslib-2014.04.29.tar.gz
3. 解压安装包
4. 执行下列语句
```
cd rcslib-2014.04.29(对应安装包名字)
./configure -enable-ALLJAVA
[修改Makefile中的prefix选项为 /opt/rcslib/build，此处将生成lib与include]
make 
make check
make install(可能需要root权限)
```
#### 使用说明

三步使用RCS
一是如何使用C++来编写NMLmessage，二是主程序中如何使用NML来通信，三是如何写配置文件

##### 编写C++NMLmessage
NML message存放在src文件夹下，通常与应用程序在同一级目录下。这种目录结构能够最小化修改文件目录。

message文件夹内需要copy以下几个基本的文件：
-Makefile
-NMLmsgExn2.cc
-NMLmsgExn.hh
-CommonDefinitionX可用可不用，如果不用，则对应将头文件中的引用注释即可。
其中，
* Makefile文件，该文件需要针对头文件、目标文件和NML_CODEGEN的安装位置，进行修改。通常NML_CODEGEN的安装位置为：```/usr/local/bin/CodeGenCmdLine.jar```。
如果编译message时，出现unable to access jarfile，这种情况下需要利用错误信息和之前rcd的安装信息来查找jar文件，find命令参考如下：
```find /opt -name CodeGenCmdLine.jar```
```find /usr -name CodeGenCmdLine.jar```
要特别注意makefile文件中，如果定义了make clean -\rm -f *.cc的话最后把其删除，以免make clean误删除一些自定义的cc文件。
```
clean:
    -\rm -f *.o lib*.a lib*.so lib*.la *.lib *.ddll
```
* CommonDefinitionX和NMLmsgExn.hh不用改，是NML通信使用的模块。
* 特别注意车上的模板是NMLmsgExn2.cc。此文件同样不要重命名，不要删除。
* 自定义message，以“...n.hh”结尾，以表明是用NML通信。
  其中，需要引入头文件包括：
```
// Prevent Multiple Inclusion
#ifndef MESSAGEAN_HH
#define MESSAGEAN_HH
// Include Files
#include "rcs.hh"     // Common RCS definitions
#include "NMLmsgExn.hh"
#include "CommonDefinitionX.hh"
```
  定义MESSAGEA_MSG_TYPE.
```
// Define the integer type ids.
#define MESSAGEA_MSG_TYPE 40101
```
接下来则是消息的定义，可以根据自己的需要，自定义一些数据结构：
```C++
struct UserType{
int int_array[2];
std::string v_str;
};
// Define the NML Message Classes
class MESSAGEA_MSG : public NMLmsgEx
{
public:
//Constructor
MESSAGEA_MSG();
// CMS Update Function
void update(CMS *);
// Place custom variables here.
char v_char;
double v_double;
UserType usertype_data;
};
// Declare NML format function
extern int MessageAFormat(NMLTYPE, void *, CMS *);
#endif // MESSAGEAN_HH
```

##### 主程序采用NML进行消息传递
1. NML通信模块启用
    在主程序中需要引用使用的NMLmessage的头文件。此外，在启用NML时使用，使用以下语句：
    ```
    set_rcs_print_destination(RCS_PRINT_TO_STDOUT);
    nml_start();
    ```
    在程序通信结束后，需要清空和关闭NML：
    ```
    nml_cleanup();
    ```
2. NML通信类的初始化
    NML的使用建立在NML通信类的基础上，初始化NML通信类采用以下命令，但需要已经写好nml配置文件，关于配置文件的要求，可以参见“配置ＮＭＬ文件（configuration file）”一节：
    ```NML * MESSAGE_CHANNEL = new NML(formatFunction,"buffer", "process", "config.nml");```
    其中，参数buffer对应配置文件中B的名称，process对应P的名称，config.nml对应nml的文件名。
    formatFunction一般在nml message文件的最后有同名的定义。
    如果配置文件中Process对应的master为1，NML 通信类初始化后，才会启动buffer的master。
3. NML通信消息的初始化 
    针对写消息的模块，采用
    ```
    Message_data = new MESSAGEA_MSG;
    ```
    针对读消息的模块，采用
    ```
    Message_data = (MESSAGEC_MSG *) MESSAGE_CHANNEL->get_address();
    ```
    需要注意的是，接收的buffer，不需要重新```new MESSAGEA_MSG```。发送的Buffer，需要在构造函数中```new MESSAGEA_MSG```开辟新空间。
4. 消息读写
    消息读采用以下命令判断接收是否正常，如果正常，可以直接使用buffer中定义变量：
    ```
    MESSAGE_CHANNEL ->blocking_read(0.2) 
    ```
    消息写采用以下命令：
    ```
    MESSAGE_CHANNEL ->write(Message_data)
    ```
##### 配置ＮＭＬ文件（configuration file）
以下部分是对ＮＭＬ官方文档的说明和一些实践中经验的补充。不同于官方文档，我们直接以我们车上的ＮＭＬ（bin/UGVAuto.nml）为模板，来说明。如果想使用，建议直接用模板修改，而不要从头到尾写。
**ＮＭＬ配置文件主要包括四个部分，分别是：注释，消息，进程，server。**
1.注释
注释以'\#'开头，我们可以看到有一行以\#开头，如下：
\# Name                     Type       Host                    size     neut      RPC#  buffer#      MP     . . .
这就是注释。
为了更好的表示消息的写法，特意加了该注释。


2.消息(buffer)
消息对应在src/message里面的文件，只有定义了消息的头文件，才能够被其他程序调用。只有此处配置正确，才能保证消息的正常收发。
对于代表buffer的.hh文件，可用Makefile文件对message进行修改和编译，每次修改.hh文件都需要重新编译，编译生成新的/Test/lib/libTest.a文件。
Message名称都以n结尾，如MessageAn.hh MessageBn.hh MessageCn.hh等。这是在message文件夹里的Makefile中约定的，方便统一管理。而在.nml配置文件中，我们将后缀n略去。
消息以Ｂ开头，我们以现有模板的注释行为例，一一介绍该如何编写和定义消息。
\# Buffers    
\# Name	Type	Host	size	neut RPC#	buffer#	MP . . .
B MessageA	SHMEM	172.23.100.205	1024	0	*	1001	*	50001	bsem=5421	TCP=5421 xdr

* Name是消息名称，对应到src/message里面的文件。
* Type表示的是消息的使用形式，包括三种方式：SHMEM(share memory)，GLOBMEM(global memory)，LOCMEM(local memory)(对远程的Buffer有三种方式：TCP, UDP, RPC)。
* Host表示的是buffer所在的主机名，如果消息只是在同一台机器上传递，则这里写什么都问题不大，最好写localhost。需要特别注意的是，如果是不同机器传递某一个消息，需要给消息写一个server，来负责传递，则这里要写的是该消息的server所在的主机名（或主机IP地址）。这里可以看到，host1和host4是有通信关系的，很多消息都在这两台机子中间传递。因此， 规划模块在host1上，与之相关的server也在host1上，因此此处的Host也是写host1。
* size表示的是消息的大小，单位字节，这里要根据msg定义的数据结构来确认

* neut　0或1都可以，区别是什么官方文档并未介绍清楚，如果没有处理器不兼容，则设0。通常取0即可。
* RPC# 已经被官方弃用，因此统一用符号来占位。
* buffer# buffer的序列号，需要保证**唯一**即可。
* MP：max_procs，可以用符号占位。
* [Type-spec data]：对于SHMEM，需要一个**唯一**的共享内存键。后面接着“TCP=”，后面的数字必须大于1024。后面接着"bsem="，后面的数字与TCP不同即可。

这里要注意的是，如果用了两个不同的nml文件，如果有共同的buffer，后面的[Type-spec data]必须是一致的，否则无法通信。

3.进程(Process)
进程以Ｐ开头。
\# Name                 Buffer                     Type         Host        Ops    server       timeout     master     cnum
\# ModuleA
P ModuleA	MessageA	LOCAL	172.23.100.205	R	0	0.1	1	1	waitformaster

* Name是进程名称，一般对应到bin里面的可运行程序，有可能一个程序有多个进程。
* Buffer表示的是该进程使用的消息名称，必须在Buffer中定义。
* Type只能是 "LOCAL" , "REMOTE","AUTO"。这个与进程的位置无关，表示的是进程如何访问消息。对于SERVER来说直接访问，则是用LOCAL。如果用TCP、UDP访问或者本行的Buffer需与其他主机通信（读或写），且server程序不在本机，则是用REMOTE。
* Host表示的是进程所在主机ip地址。
* Ops表示进程对消息的操作方式，R表示读，W表示写，RW表示既读又写。
* server 对于svr而言为1，否则为0。
* timeout 互斥时间通常写为0.1。
* master 表示指定消息的传递指定哪一个process是master，注意master可以不唯一，且至少需要有一个master，建议如现有文件中所有process对应buffer都为1。如果对于不是master的process，其在c++使用NML，建立new CHANNEL时，会一直等待程序的master建立好后，才能够正常初始化，否则会一直中断在此。这个Bug通过调试模式可以发现；或者发现程序没有报错，但也并没有运行至期望的语句时可能出现。
* cnum 除非GLOBMEM，否则没用。GLOBMEM时表示Process的序列标示，互不相同即可。

4.Server
Server是一种特殊的进程，其写法与进程类似。在/src/server下可用Makefile文件对server进行修改和编译，每次修改.cc文件都需要重新编译，编译生成新的/Test/bin/*svr 文件。

\#Server
\# Name	Buffer	Type	Host	0ps	server  timeout	master  cnum
P ServerAsvr MessageA	LOCAL	172.23.100.210	RW	1	0.1	1	51
注意：
server的Type都是LOCAL，Host是server程序所在主机地址。Ops一般为RW操作，server为1，master为1即可。


#### 参与贡献

1. 李峻翔 Junxiang Li 
2. 刘伯凯 Bokai Liu 
