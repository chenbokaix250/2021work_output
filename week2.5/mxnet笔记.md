# Mxnet 笔记

MXnet中利用NDArray作为存储和变换数据的主要工具

NDArray提供了GPU计算和自动求梯度等功能,更适合深度学习中使用.

NDAarray支持大量的运算符

两个形状相同的NDArray按元素运算时,可能会触发广播机制(先适当复制元素使这两个NDArray形状相同后再按元素运算)


在NDArray中,索引从0开始逐一递增


可以利用Python中自带的id函数,查看对应的内存地址是否相同

可以通过array函数和asnumpy函数令数据在NDArray和Numpy格式之间互相变换


MXNet提供了autograd模块来自动求梯度

调用record函数后,MXNet会记录并计算梯度
默认情况下,autograd还会将运行模式从预测模式转为训练模式.可以通过调用is_training函数来查看

---

### 关于在MXNet上查阅函数和类

* 想知道一个模块里面提供了哪些可以调用的函数和类的时候,可以使用dir函数
* 想了解某个函数或者类的具体用法时,可以使用help函数(利用q退出或者ctrl+z)
* 在jupyter记事本里,可以使用?来讲文档显示在另外一个窗口(nd.random?)

使用Gluon可以更简洁的实现模型

在Gluon中,data模块提供有关数据处理的工具,nn模块定义了大量神经网络的层,loss模块定义了各种损失

XMNet的initializer模块提供了模型参数初始化的各种方法