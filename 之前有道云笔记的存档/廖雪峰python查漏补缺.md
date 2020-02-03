* 以Unicode表示的str通过encode()方法可以编码为指定的bytes
* 纯英文的str可以用ASCII编码为bytes，内容是一样的，含有中文的str可以用UTF-8编码为bytes。含有中文的str无法用ASCII编码，因为中文编码的范围超过了ASCII编码的范围，Python会报错。

---
```
#!/usr/bin/env python3
# -*- coding: utf-8 -*-
```
第一行注释是为了告诉Linux/OS X系统，这是一个Python可执行程序，Windows系统会忽略这个注释；

第二行注释是为了告诉Python解释器，按照UTF-8编码读取源代码，否则，你在源代码中写的中文输出可能会有乱码。

##### 常用的占位符
* %d 整数
* %f 浮点数
* %s 字符串
* %x 十六进制整数
---

#### list
* append方法
* pop方法
* insert方法
* len方法

---

#### tuple
* tuple的陷阱：当你定义一个tuple时，在定义的时候，tuple的元素就必须被确定下来

---

定义默认参数要牢记一点：默认参数必须指向不变对象！