# Docker Practice

* 镜像(Image)
* 容器(Container)
* 仓库(Repository)

利用`docker —version`检测版本

### 获取镜像

`docker pull [选项][Docker Registry地址]<仓库名>:<标签>`

`docker pull ubuntu:14.04`

**docker run命令参数**

### image文件

```shell
# 列出本机的所有image文件
$ docker image ls
# 删除image文件
$ docker iamge rm(imageName)
```

尽量使用别人制作好的image文件,而不是自己制作.

运行image文件

```shell
$ docker container run hello-world
```

　可以利用Ctrl+d或者exit退出容器

可以利用`docker container kill`终止容器运行

#### docker container exec

用于进入一个正在运行的docker容器.如果docker run命令运行容器的时候,没有使用-it参数,就要用这个命令进入容器.一旦进入容器,就可以在容器的Shell执行命令了.

```shell
$ docker container exec -it [containerID] /bin/bash
```

docker container cp 命令用于从正在运行的Docker容器中,将文件拷贝到本机

```shell
$ docker container cp [containID]:[/path/to/file] .
```

## 运行

```shell
$ docker run -it --rm ubuntu:14.04 bash
```

`docker run`就是运行容器的命令,参数:

* -it:这个两个参数,一个是-i:交互式操作,一个是-t终端.打算进入bash执行一些命令并查看返回结果哦,因此我们需要交互式终端
* —rm:这个参数是说容器推出之后随之将其删除
* ubuntu是指容器镜像
* bash:放在镜像名后的是命令,这个是启动交互式Shell,因此用的是bash

通过exit退出容器



以特定格式显示

利用`docker image -q`显示镜像ID

可以利用—filter配合-q产生出指定范围的ID列表,

或者利用自定义的format样式显示信息

```
$ docker images --format "{{.ID}}:{{.Repository}}"
```



## Docker数据管理

容器中管理数据主要有两种方式:

* 数据卷
* 数据卷容器

### 创建一个数据卷

在用`docker run`命令的时候,使用-v标记来创建一个数据卷并挂载到容器里.在一次run中多次使用可以挂载多个数据卷.

```shell
$ sudo docker run -d -P --name web -v /webapp training/webapp python app.py
```

创建一个名为web的容器,并加载一个数据卷到容器的/webapp目录

### 挂载一个主机目录作为数据卷

使用-v标记也可以指定挂载一个本地主机的目录到容器中去

```shell
$ sudo docker run -d -P --name web -v /src/webapp:/opt/webapp training/webapp python app.py
```

上面的命令加载主机的/src/webapp目录到容器的/opt/webapp目录.

可以通过:ro将挂载指定为只读

---

### 数据卷容器





---

sudo docker run -it  ros /bin/bash











