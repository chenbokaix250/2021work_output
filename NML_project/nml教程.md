# NML工程安装

## java安装

此处安装java版本为jdk1.8.0_281

https://blog.csdn.net/mucaoyx/article/details/82949450

https://blog.csdn.net/lengconglin/article/details/77016911

1.jdk 解压到home目录下

2.切换到/usr/lib目录下cd /usr/lib，并新建jdk目录，sudo mkdir jdk

3.将解压的jdk文件复制到新建的/usr/lib/jdk目录下来：sudo mv ~/jdk1.8.0_281/usr/lib/jdk 执行命令后可到 usr/lib/jdk 目录下查看是否复制成功

4.配置java环境变量，这里是将环境变量配置在etc/profile，即为所有用户配置JDK环境，使用命令sudo gedit /etc/profile打开/etc/profile文件，在末尾添加以下几行文字：

*#set java environment*   

export JAVA_HOME=/usr/lib/jdk/jdk1.8.0_281

export JRE_HOME=${JAVA_HOME}/jre    

export CLASSPATH=.:${JAVA_HOME}/lib:${JRE_HOME}/lib     

export PATH=${JAVA_HOME}/bin:$PATH 

5.使用 source /etc/profile 使配置立马生效

6.配置软连接

sudo update-alternatives --install /usr/bin/java java /usr/lib/jdk/jdk1.8.0_281/bin/java 300    

sudo update-alternatives --install /usr/bin/javac javac /usr/lib/jdk/jdk1.8.0_281/bin/javac 300 

sudo update-alternatives --install /usr/bin/jar jar /opt/jdk1.8.0_281/bin/jar 300

7.测试安装，在终端输入java -version 

![](/home/ref/Pictures/20170809210820400.png)

## NML安装

https://www.cnblogs.com/AIpower/p/12743445.html

1.解压安装包

2.执行下列语句

```
cd rcslib-2014.04.29(对应安装包名字)
./configure -enable-ALLJAVA
[修改Makefile中的prefix选项为 /opt/rcslib/build，此处将生成lib与include]
make 
make check
make install(可能需要root权限)
```

3.执行文件

电脑1：

执行moduleB -> 发送（消息A，B）

执行moduleA -> 接收（消息A，B），发送C

电脑2：

执行moduleC,接收消息C

还需执行./run.sh 文件

注：

原工程需要删除

RCS-Tutorial/HelloWorldModule/ThreeModulesNMLComm/bin

下ServerAsvr文件，重新编译

即：ServerAsvr.cc  所在路经下的makefile文件