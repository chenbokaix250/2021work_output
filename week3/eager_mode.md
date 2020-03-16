# eager模式



## eager模式下的运算

从TensorFlow2.0开始,默认情况下会启用Eager模式执行.TensorFlow的Eager模式是一个命令式/由运行定义的接口,一旦从python被调用,其操作立即被执行,无需事先构建静态图.

```
from __future__ import absolute_import, division, print_function
import tensorflow as tf
```

tf.Tensor对象具有数据类型和形状

```
print(tf.add(1,2))
tf.Tensor(3,shape=(),dtype=int32)
```

Numpy数组和tf.Tensors之间的区别:

* 张量可以由GPU支持
* 张量是不可变的
* Numpy ndarray和tf.Tensors直接很容易转换

```
import numpy as np
ndarray = np.ones([2,2])
tensor = tf.multiply(ndarray,36)
print(tensor)
print(np.add(tensor,1))
print(tensor.numpy())
```

##  数据集

使用tf.data.Dataset API构建管道 以便为模型提供数据.



## 自定义层

利用layers创建层 包括Dense Conv2D LSTM BatchNormalization Droput等等

可以通过variables kernel bias参数得到网络的变量/权重矩阵/偏置等

```
print(layer.variables) # 包含了权重和偏置
[<tf.Variable 'dense_1/kernel:0' shape=(6, 100) dtype=float32, numpy=
array([[-0.18237606,  0.16415142,  0.20687856,  0.23396944,  0.09779547,
        -0.14794639, -0.10231382, -0.22263053, -0.0950674 ,  0.18697281,
         ...
        -0.10450925, -0.12111329, -0.2259491 ,  0.12304659, -0.04047236]],
      dtype=float32)>, <tf.Variable 'dense_1/bias:0' shape=(100,) dtype=float32, numpy=
array([0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.,
       0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.,
       0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.,
       0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.,
       0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.,
       0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.],
      dtype=float32)>]
      
print(layer.kernel, layer.bias)  # 也可以分别取出权重和偏置
<tf.Variable 'dense_1/kernel:0' shape=(6, 100) dtype=float32, numpy=
array([[-0.18237606,  0.16415142,  0.20687856,  0.23396944,  0.09779547,
        -0.14794639, -0.10231382, -0.22263053, -0.0950674 ,  0.18697281,
         ...
        -0.10348159, -0.07493602, -0.1722112 , -0.23290877,  0.18784209],
       [ 0.13477843,  0.11936818, -0.21257897,  0.21244659, -0.18786472,
        -0.06494723, -0.07063387, -0.07994832, -0.11256738, -0.22335076,
        -0.02153319, -0.20943552, -0.21425952, -0.12278055, -0.00619341,
        -0.09176037, -0.1766775 , -0.21622379, -0.04250833,  0.23764552,
         0.21168886,  0.09459655, -0.07919639, -0.21559525,  0.20465617,
        -0.20613717,  0.13103445,  0.21384992,  0.04693423,  0.20122723,
         0.12190209,  0.22194327, -0.05410977, -0.1792583 , -0.03342254,
         0.09272121,  0.06039228,  0.09666802, -0.22759588, -0.14688678,
         0.12520896,  0.15474696, -0.23104139,  0.18017791, -0.02388267,
        -0.01371126,  0.2352383 , -0.10501392,  0.01626216, -0.14222105,
         0.13740788,  0.18499441,  0.03618436, -0.01862051, -0.1401035 ,
        -0.01304157, -0.04905747, -0.07051091,  0.10759439, -0.08964662,
        -0.01344521, -0.17841959, -0.17568308, -0.12892699,  0.11976974,
         0.02280475,  0.16669382,  0.21027894,  0.21428709, -0.04820213,
        -0.22136293, -0.13934767,  0.142024  , -0.07064074,  0.1470062 ,
         0.00042979, -0.2371952 , -0.06649312,  0.10123204, -0.20473264,
        -0.09161748,  0.20804678, -0.22195774, -0.09219673,  0.02311908,
         0.13456099,  0.14470674, -0.05369592,  0.02126037,  0.0682667 ,
         0.08384518,  0.17998771, -0.1927835 , -0.11473013, -0.01386146,
        -0.10450925, -0.12111329, -0.2259491 ,  0.12304659, -0.04047236]],
      dtype=float32)> <tf.Variable 'dense_1/bias:0' shape=(100,) dtype=float32, numpy=
array([0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.,
       0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.,
       0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.,
       0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.,
       0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.,
       0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.],
      dtype=float32)>
```

## 实现自定义网络层

实现自定义层的方法是扩展tf.keras.Layer类并实现:

* `__init__()`函数,可以在其中执行所有与输入无关的初始化
* build函数,可以获得输入张量的形状,并可以进行其余的初始化
* call()函数,构建网络结构,进行前向传播

在`__init__`中创建网络的优点是**它可以根据图层将要操作的输入的形状启用后期的网络构建**.在init中创建变量意味着需要明确指定创建变量所需要的形状

```python
class MyDense(tf.keras.layers.Layer):
    def __init__(self, n_outputs):
        super(MyDense, self).__init__()
        self.n_outputs = n_outputs

    def build(self, input_shape):
        self.kernel = self.add_variable('kernel',
                                       shape=[int(input_shape[-1]),
                                             self.n_outputs])
    def call(self, input):
        return tf.matmul(input, self.kernel)
layer = MyDense(10)
print(layer(tf.ones([6, 5])))
print(layer.trainable_variables)
```

## 网络层组合

很多网络通过叠加不同的结构层组合而成 在TensorFlow2中要创建一个包含多个网络层的结构,一般继承与tf.keras.Model类

```python
class MyDense(tf.keras.layers.Layer):
    def __init__(self, n_outputs):
        super(MyDense, self).__init__()
        self.n_outputs = n_outputs

    def build(self, input_shape):
        self.kernel = self.add_variable('kernel',
                                       shape=[int(input_shape[-1]),
                                             self.n_outputs])
    def call(self, input):
        return tf.matmul(input, self.kernel)
layer = MyDense(10)
print(layer(tf.ones([6, 5])))
print(layer.trainable_variables)
```

如果模型是线性的,可以直接用tf.keras.Sequential来构造

```python
seq_model = tf.keras.Sequential(
[
    tf.keras.layers.Conv2D(1, 1, input_shape=(None, None, 3)),
    tf.keras.layers.BatchNormalization(),
    tf.keras.layers.Conv2D(2, 1, padding='same'),
    tf.keras.layers.BatchNormalization(),
    tf.keras.layers.Conv2D(3, 1),
    tf.keras.layers.BatchNormalization(),

])
seq_model(tf.ones([1,2,3,3]))

```

