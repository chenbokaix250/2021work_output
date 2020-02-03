## python中执行shell命令

python中执行shell命令的四种方法

##### 1.os模块的os.system()这个函数来执行shell命令

```
import os

os.systen('ls')

```
注:这个方法得不到shell命令的输出

##### 2.os模块的os.popen()函数
```
import os
str = os.popen('ls').read()
a = str.split("\n")
for b in a:
    print b
```
注:这个方法能得到命令执行后的结果是一个字符串,要自行处理才能得到想要的信息.


##### 3.commands模块 
可以很方便的取得命令的输出(包括标准和错误输出)和执行状态位

```
import commands
a,b = commands.getstatusoutput('ls')
```
commands.getstatusoutput(cmd)返回 (status,output)
commands.getoutput(cmd)只返回输出结果
commands.getstatus(file)返回 ls -ld file 的执行结果字符串,调用了getoutput,不建议使用这个方法

##### 4.subprocess模块
使用subprocess模块可以创建新的进程,可以与新建进程的输入/输出/错误管道连通,并可以获得新建进程执行的返回状态.使用subprocess模块的目的是代替以上惨重旧的函数或者模块

```
import subprocess
