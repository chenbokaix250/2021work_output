## `*args` 和 `***kwargs`

`*args` 可以将不定数量的参数传递给一个函数

`**kwargs` 将不定长度的键值对,作为参数传递给一个函数,如果在一个函数里处理带名字的参数,应该使用`**kwargs`

```
def test_args_kwargs(arg1,arg2,arg3):
    print(arg1)
    print(arg2)
    print(arg3)

# 使用 *args

args = (2,3,5)
test_args_kwargs(*args)

# 使用 **kwargs

kwargs = {'arg1':2,'arg2':3,'arg3':5}
test_args_kwargs(**kwargs)

```

---

## Debugging
利用Python debugger(pdb)来进行代码调试

使用Python debugger运行脚本
`python -m pdb script.py`
会在脚本第一行指令处停止执行,这在脚本很短时有帮助

也可以在脚本内部设置断点
利用`pdb.set_trace()`

命令列表:
* c:继续执行
* n:继续执行一行

---

## 生成器 Generators
迭代器(iterators)是一个让程序员可以遍历一个容器的对象.
**一个迭代器在遍历并读取一个容器的数据元素时,并不会执行一个迭代.**
* 可迭代对象(Iterable)
* 迭代器(Iterator)
* 迭代(Iteration)


任意对象,可以返回一个迭代器的`__iter__`方法,或者定义可以支持下标索引的`__getitem__`方法,他就是一个可迭代对象.
任意对象,只要定义了next或者`__next__`方法,就是一个迭代器.

生成器也是一种迭代器,但是只对其迭代一次.

生成器最佳应用场景是:你不想同一时间将所有计算出来的大量结果集分配到内存当中,特别是结果集里还包含循环.

---

## Map,Filter和Reduce

Map会将一个函数映射到一个输入列表的所有元素上.规范:
`map(function_to_apply,list_of_inputs)`

filter过滤列表中的元素,并且返回一个由所有符合要求的元素构成的列表

Reduce当需要对一个列表进行一些计算并返回结果时.

---

set数据结构

set行为类似于list,但区别在于set不能包含重复值.

利用set来检查列表中是否包含重复的元素
```
#for循环
some_list = ['a','b','c','b','d','m','n','n']

duplicates = []
for value in some_list:
    if some_list.count(value)>1:
        if value not in duplicates:
            duplicates.append(value)
print(duplicates)

## 使用集合(sets)方法

some_list = ['a','b','c','b','d','m','n','n']

duplicates = set([x for x in some_list if some_list.count(x)>1])
print(duplicates)

```

求两个集合的交集和差集的使用

```
# 交集
valid = set(['yellow','red','blue','green','black'])
input_set = set(['red','brown'])
print(input_set.intersection(valid))

# 差集
valid = set(['yellow','red','blue','green','black'])
input_set = set(['red','brown'])
print(input_set.difference(valid))
```

---

## 三元运算符

三元运算符也被称作条件表达式

```
# 如果条件为真,返回真,否则返回假
condition_is_true if condition else condition_is_false

is_fat = True
state = "fat" if is_fat else "not fat"
```

利用元祖的三元运算符
```
# (返回假,返回真)[真或假]
(if_test_is_false,if_test_is_true)[test]

fat = True
fitness = ('skinny','fat')[fat]
print('Ali is',fitness)
```

---

## 装饰器

装饰器(Decorators)是修改其他函数的功能的函数.

**一切皆对象**
```python
def hi(name='yasoob'):
    return 'hi ' + name 
print(hi()) 
# hi yasoob
# 甚至可以将一个函数赋值给一个变量
greet = hi
#没有使用hi(),而是hi 说明并不是在调用hi函数,而是将它放在greet变量里
print(greet())
# hi yasoob

del hi 

# print(hi())
# NameError: name 'hi' is not defined    
print(greet())
# hi yasoob
```

### 在函数中定义函数

在一个函数中定义另一个函数:
```python
def hi(name='yasoob'):
    print('now you are inside the hi() function')

    def greet():
        return 'now you are in the greet() function'
    def welcome():
        return 'now you are in the welcome() function'

    print(greet())
    print(welcome())
    print('now you are back in the hi() function')

hi()

# output:
# now you are inside the hi() function
# now you are in the greet() function
# now you are in the welcome() function
# now you are back in the hi() function

greet()

# output: NameError: name 'greet' is not defined

# 调用hi()时,greet()和welcome()将会同时被调用.
# 在hi()之外是不能访问的
```

可以创建嵌套的函数,函数也能返回函数

```python
def hi(name='yasoob'):
    def greet():
        return 'now you are in the greet() function'

    def welcome():
        return 'now you are in the welcome() function'

    if name == 'yasoob':
        return greet
    else:
        return welcome

a = hi()
print(a)
print(a())
```

### 将函数作为参数传给另一个函数

```python
def hi():
    return  'hi  yasoob!'
def doSomethingBeforeHi(func):
    print('I am doing some boring work before executing hi()')
    print(func())

doSomethingBeforeHi(hi)
```

### 第一个装饰器
```python
def a_new_decorator(a_func):
    def wrapTheFunction():
        print('I am doing some boring work before executing a_func()')
        a_func()
        print('I am doing some boring work after executing  a_func()')
    return wrapTheFunction

def a_function_requiring_decoration():
    print('I am the function which needs some decoration to remove my foul smell')

a_function_requiring_decoration()

a_function_requiring_decoration = a_new_decorator(a_function_requiring_decoration)

a_function_requiring_decoration()
```

利用装饰符号`@`进行改写
```python
@a_new_decorator
def a_function_requiring_decoration():
    print('I am the function which needs some decoration to remove my foul smell')

a_function_requiring_decoration()

a_function_requiring_decoration = a_new_decorator(a_function_requiring_decoration)

print(a_function_requiring_decoration.__name)
# output:wrapTheFunction
#wrapTheFunction重写了函数的名字和注释文档 
```
Python提供了`functools.wraps`来避免这个问题

利用`functools.wraps`进行改写

```python
from functools import wraps

def a_new_decorator(a_func):
    @wraps(a_func)
    def wrapTheFunction():
        print('I am doing some boring work before executing a func()')
        a_func()
        print('I am doing some boring work after executing a func()')
    return wrapTheFunction

@a_new_decorator
def a_function_requiring_decoration():
    print('I am the function which needs some decoration to remvoe my foul smell')
print(a_function_requiring_decoration.__name__)

#output:a_function_requiring_decoration
```

#### 装饰器的蓝本规范:
```python
from functools import wraps
def decoratpr_name(f):
    @wraps(f)
    def decorated(*args,**kwargs):
        if not can_run:
            return 'Function will not run'
        return f(*args,**kwargs)
    return decorated
@decorator_name
def func():
    return('Function is running')

can_run = True
print(func())

can_run = False 
print(func())
```
`@wraps`接受一个函数来进行装饰,并加入复制函数名称,注释文档,参数列表等待功能
这可以在装饰器里面访问在装饰之前的函数的属性


### 使用场景

#### 授权(Authorization)
装饰器能有助于检测某个人是否被授权去使用一个web应用的端点.
基于装饰器的授权:
```python
from functools import wraps

def requires_auth(f):
    @wraps(f)
    def decorated(*args,**kwargs):
        auth = request.authorization
        if not auth or not check_auth(auth.username,auth.password):
            authenticate()
        return f(*args,**kwargs)
    return decorated
```

#### 日志(Logging)
日志是装饰器运用的另一个亮点
```python
from functools import wraps

def logit(func):
    @wraps(func)
    def with_logging(*args,**kwargs):
        print(func.__name__+'was called')
        return func(*args,**kwargs)
    return with_logging
@logit
def addition_func(x):
    return x+x
result = addition_func(4)
```

### 函数中嵌入装饰器


```python
from functools import wraps

def logit(logfile='out.log'):
    def logging_decorator(func):
        @wraps(func)
        def wrapped_function(*args,**kwargs):
            log_string = func.__name__ + 'was called'
            print(log_string)
            with open(logfile,'a') as opened_file:
                opened_file/write(log_string + '/n')
            return func(*args,**kwargs)
        return wrapped_function
    return logging_decorator
@logit()
def myfunc1():
    pass
myfunc1()

@logit(logfile='func2.log')
def myfunc2():
    pass
myfunc2()
```

### 装饰器类

可以利用类来构建装饰器
```python
from functools import wraps

class logit(object):
    def __init__(self.logfile='out.log'):
        self.logfile = logfile 
    def __call__(self,func):
        @wraps(func)
        def wrapped_function(*args,**kwargs):
            log_string = func.__name__ + 'was called'
            print(log_string)
            with open(self.logfile,'a') as opened_file:
                opened_file.write(log_string + '\n')
            self.notify()
            reutrn func(*args,**kwargs)
        return wrapped_function

    def notify(self):
        pass

@logit
def myfunc1():
    pass
```

## Global和Return

global变量意味着可以在函数以外的区域访问这个变量
return多个变量时,可以`return name,age`

## 对象变动

Python中可变(mutable)与不可变(immutable)的数据类型
```python
foo = ['hi'] 
print(foo) # Output: ['hi']

bar = foo 
bar += ['bye'] 
print(foo)
```

每当将一个变量赋值为另一个可变类型的变量时,对这个数据的任意改动会同时反映到这两个变量上去.


## `__slot__`魔法

使用`__slot__`,可以控制Python去额外分配内存保存所有属性,只给一个固定集合的属性分配空间.
```python
#不使⽤ __slots__:

class MyClass(object):

    def __init__(self, name, identifier):
    self.name = name 
    self.identifier = identifier 
    self.set_up() # ...

#使⽤ __slots__:

class MyClass(object):
    
    __slots__ = ['name', 'identifier'] 
    def __init__(self, name, identifier):
        self.name = name
        self.identifier = identifier
        self.set_up() # ...

#第⼆段代码会为你的内存减轻负担。通过这个技巧，有些⼈已经看到内存占⽤率⼏乎 40%~50%的减少。
```

## 虚拟环境
`virtualenv`针对每个程序创建独立(隔离)的Python环境

`pip install virtualenv`

重要的命令是:
```
virtualenv myproject
source bin/activate

#退出virtualenv

deactivate
```



## 容器Collections

### defaultdict


defaultdict与dict类型不同,不需要检查key

### counter
Counter是一个计数器,可以用来针对某项数据进行计数

可以利用它统计一个文件

```python
with  open('filenmae','rb') as f:
    line_count = Counter(f)
print(line_count)
```

### deque

deque提供了一个双端队列,可以从头/尾两端添加或删除元素.
```python
d = deque()
d.append('1')
d.pop()
d.popleft()
```
### namedtuple

一个元祖是一个不可变的列表

### enum.Enum
枚举对象
Enums组织各种东西的方式

### 枚举 Enumerate

## 自省对象

### `__dir__`

dir可以返回所有方法的名字

type 与id
type返回一个对象的类型
id返回不同种类对象的唯一ID

## inspect模块

## 推导式 Comprehension

## lambda表达式
一行函数 也被称为匿名函数 

原型 `lambda 参数:操作(参数)`

## open函数
```
with open('photo.jpg','r+') a f:
    jpgdata = f.read()
```

open的第一个参数是文件名.第二个决定了这个文件如何被打开
* 读取文件,传入r
* 读取并写入文件,传入r+
* 覆盖写入文件,传入w
* 文件末尾附加内容,传入a

---















































