### 常用层
常用层对应于core模块，core内部定义了一系列常用的网络层，包括全连接、激活层等


#### Dense层

`keras.layers.core.Dense(units, activation=None, use_bias=True, kernel_initializer='glorot_uniform', bias_initializer='zeros', kernel_regularizer=None, bias_regularizer=None, activity_regularizer=None, kernel_constraint=None, bias_constraint=None)`

Dense就是常用的全连接层，所实现的运算是
`output = activation（dot（input，kernel） + bias）`
* activation 是逐元素计算的激活函数
* kernel 是本层的权值矩阵
* bias 是偏置向量
* use_bias = True 时添加
* 

#### activation层
`keras.layers.core.Activation(activation)`
激活层对一个层的输出施加激活函数
* activation：将要使用的激活函数，为预定义激活函数名或一个xxx的函数
#### Dropout层
`kers,layers.core.Dropout(rate,noise_shape=None,seed=None)`
为输入数据施加Dropout，Dropout将在训练过程中每次更新参数时按一定概率随机断开输入神经元，Dropout层用于防止过拟合
* rate 0~1的浮点数，控制断开比例
* noise_shape 整数张量
* seed 整数 随机种子
* 
#### SGD
`keras。optimizers.SGD(lr=0.01,momentum=0.0,decay=0.0,nesterov=False)`
随机梯度下降优化器
包含扩展功能的支持 动量优化 学习率衰减
* lr：float>=0 学习率
* mementum：float >= 0 参数用于加速SGD在相关方向上前进，并抑制震荡
* decay float >=0 每次餐宿更新后学习率衰减值
* nesterov boolean 是否使用Nesterov
*

#### Conv1D
`keras.layers.Conv1D(filters, kernel_size, strides=1, padding='valid', data_format='channels_last', dilation_rate=1, activation=None, use_bias=True, kernel_initializer='glorot_uniform', bias_initializer='zeros', kernel_regularizer=None, bias_regularizer=None, activity_regularizer=None, kernel_constraint=None, bias_constraint=None)`

1D卷积层
该层创建了一个卷积核,该卷积核以单个维度上的层输入进行卷积,以生成输出张量.如果 use_bias为True,则会创建一个偏置向量并将其添加到输出中.最后,如果activation不是None,它也会应用于输出.
当使用该层作为模型第一层时,需要提供input_shape参数(整数元祖或None)
* filter 整数 输出空间的维度
* kernel_size 一个整数 或者单个整数标识的元祖或列表
* strides 一个整数,指明卷积的步长
* padding valid/causal/same之一
* data_format 字符串顺序
* dilation_rate 整数 用于膨胀卷积的膨胀率

#### Flatten
`keras.layers.Flatten(data_format=None)`
将输入展平 不影响批量大小


