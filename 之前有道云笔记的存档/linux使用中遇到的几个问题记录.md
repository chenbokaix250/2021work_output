#### 输入法乱码
```
cd ~/.config
sudo rm -rf SogouPY* sogou*
```

#### caffe的路径

`~/Downloads/caffe-master$`

#### ros版本查询
```
roscore
rosparam list
rosparam get /rosdistro`
```
kinetic

#### jupyter进入方式

```
ipython notebook 
jupyter notebook
```

#### tensorflow API引入错误:

`protoc object_detection/protos/*.proto --python_out=.`

#### pycaffe兼容问题
```
protoc 需要2.6.1 而 tensorflow models 需要3.0+版本

PYTHONPATH在catkin_make中需要是/opt/ros/hydro/lib/python2.7/dist-packages/catkin 

pycaffe需要是/home/cold/Downloads/caffe-master/python

更改PYTHONPATH是在~/.bashrc完成的 更改后运行source ~/.bashrc立刻生效

使用python时 无法 import caffe时


gedit ~/.bashrc
export PYTHONPATH=/home/cold/Downloads/caffe-master/python
```



