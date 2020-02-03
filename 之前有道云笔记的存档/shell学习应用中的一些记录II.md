#### linux里source sh bash ./ 的区别

1. source a.sh
在当前shell内去读取,执行a.sh,而a.sh不需要有'执行权限' source命令可以简写为'.'

`. a.sh`
2. sh / bash 打开一个subshell去读取,执行a.sh,而a.sh不需要有'执行权限' 

通常在subshell里运行的脚本里设置变量,不会影响到父shell的.

3. ./
打开一个subshell去读取,执行a.sh 但是需要执行权限
可以用chmod +x 添加执行权限


### 记录os.path.dirname(__file__)

os.path.dirname(__file__)返回脚本的路径，但是需要注意一下几点:
* 必须是实际存在的.py文件，如果在命令行执行，则会引发异常NameError: name '__file__' is not defined；
* 在运行的时候如果输入完整的执行的路径，则返回.py文件的全路径如：Python c:/test/test.py 则返回路径 c:/test ，如果是python test.py 则返回空；
* 结合os.path.abspath用，效果会好，如果大家看过一些python架构的代码的话，会发现经常有这样的组合：os.path.dirname(os.path.abspath(__file__)),os.path.abspath(__file__)返回的是.py文件的绝对路径。



### Python configparser模块常用方法
configparser模块 可以用来读取配置文件.是一个内置模块,不需要独立安装

##### 简单读取配置文件实例
read(filename) 直接读取文件内容
get(section,option) 获取section下具体某一配置项的值(返回的是字符串)
sections() 得到所有的section,并以列表的形式返回
options(section) 得到该section的所有option
items(section) 键值对的形式 得到该section的所有option
getint(section,option)/cnf.getboolean(section,option)/getfloat(section,option) 获取整型/布尔型和浮点型的option的值

##### nohup命令
`$nohup Command [Arg ...][&]`
该命令可以在你退出帐户/关闭终端之后继续运行相应的进程。nohup 就是不挂起的意思（no hang up）。

##### eval的用法
`eval command-line`
其中command－line是在终端上键入的一条普通命令行。然而当在它前面放上eval时，其结果是shell在执行命令行之前扫描它两次。

#### DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"详解

```
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "${DIR}/.."
```
${BASH_SOURCE[0]}表示bash脚本的第一个参数,如果第一个参数是bash,表明这是要执行bash脚本,这时"${BASH_SOURCE[0]}"自动转换为第二个参数.

例如:
```
bash modules/tools/planning_traj_plot/run.sh 
modules/tools/planning_traj_plot/example_data/1_planning.pb.txt 
modules/tools/planning_traj_plot/example_data/1_localization.pb.tx

```

"${BASH_SOURCE[0]}"代表的是“modules/tools/planning_traj_plot/run.sh”。 
"dirname"表示提取参数里的目录，dirname "${BASH_SOURCE[0]}"表示提取bash脚本第一个参数里的目录，例如：“modules/tools/planning_traj_plot/run.sh”的目录为”modules/tools/planning_traj_plot”。 
cd "$( dirname "${BASH_SOURCE[0]}" )”表示切换到刚才提取的目录，例如：对于上述示例中的的目录：“modules/tools/planning_traj_plot”，cd "$( dirname "${BASH_SOURCE[0]}" )"表示在当前目录的基础上，切换到子目录“modules/tools/planning_traj_plot”。 
DIR=cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd则表示，如果第一条语句顺利执行，就执行pwd显示当前目录，并将结果赋值给变量“DIR”。 
cd "${DIR}/..”不必细说，就是切换到“DIR”变量所指目录的上一级目录。

例如:
```
#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
echo ${DIR}
cd "${DIR}/.."
```
当前目录为`/home/davidhopper/code/apollo`,执行
```
bash modules/tools/planning_traj_plot/run.sh 
modules/tools/planning_traj_plot/example_data/1_planning.pb.txt 
modules/tools/planning_traj_plot/example_data/1_localization.pb.tx

```
结果是`/home/davidhopper/code/apollo/modules/tools/planning_traj_plot`

#### Apollo项目类创建之工厂模式分析

