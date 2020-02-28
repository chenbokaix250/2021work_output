# python整理回顾



```python
#python里单引号‘sth’和双引号“sth”是一样的
str1 = 'stringa'
str2 = "stringb"

# 操作符
# 幂运算**,不能用^
# /默认是浮点运算的除法,//才是整形运算的除法,%是取余操作
# += 自增,-=自减
# e/E记法,1.3e4表示1.3乘以10的4次方
8/3=2.667
8//3=2
8%3=2
num1=8/3
tpye(num1) -> float
1.3e6=1300000

# 类型转换
# int() 总是下取整
# type()获得对象类型

int(12.6)=12
float(12)=12.0
str(12)='12'
type(str(12))=str

# 5.输入
# raw_input()和input()函数
# python2里面，raw_input()函数无论用户输入什么，都默认为字符串，如果是数字，则需要转换；
# input()函数区分字符串和数字，需要用户明确，数字就直接输入，字符串需要加引号输入；
# python3里面只有input()函数，但这是完全与py2里的raw_input()一样，即一切作为字串，需要自己转换；

var=input('please input your msg')
int_var=int(input('input your msg'))
float_var=float(input('input your msg'))

# GUI界面
# sudo zypper in python3-easygui
# import easygui
# 消息框 easygui.msgbox('msg_text')
# 多按钮消息框 easygui.buttonbox(msg='msg', tilte='title', choices=('1st', '2nd', '3rd'))
# 选择消息框 easygui.choicebox(msg='msg', tilte='title', choices=('1st', '2nd', '3rd'))
# 文本输入框 easygui.enterbox('enter your text here')
# 默认输入（是修饰参数） easygui.enterbox('enter your text here', default='default_text')
# 对话框获取数字 输入框获得文本，int()或float()转换即可
# 整数框 easygui.integerbox('enter an integer number')


# 判断
# 缩进（全局统一的缩进），==是验证相等的，=是赋值符
# if语句，and对条件做'与运算'，or对条件做'或运算'，not对条件做'非运算'

if a >= 12:
    block1
elif b >= 10:
    block2
elif c >= 9:
    block3
else:
    block4
if age >= 16:
    if grade >= 9:
if age >= 16 and grade >= 9:    等同上例
if color=='red' or color=='blue':
if not (age<16): 等同于 if age >= 16:

   
# 循环
# for循环，需要自定义变量i（可随意指定）
# range(a,b)            # 指定for计数范围
# range(4) = range(0,4) = range(0,1,2,3)    # 从0起计数的简写
# range(1,10,2)         # 1到10，步长为2
# while循环
# continue  调到下次迭代
# break     完全跳出循环

for i in (1,2,3):       # 用[1,2,3]也可
    print (i, 'times 8 =', i*8)             # 注意py3要有()，print是函数
for i in (10,0,-1):     # 反向计数
while a == '3':
    block1
for i in range(1,6):
    print ...
    if i == 3:
        continue        # 换为break则完全跳出循环
    print ...
# 注释
# 单行注释用'#'
# 多行注释用'''或"""，不同类型的三引号可以嵌套，但只限一次嵌套
# Shift+Enter 复制抬头并换行

# 11.嵌套/可变循环
# 嵌套循环，循环内嵌套循环，range()函数使用固定的数值范围

for multiplier in range (5, 8):
        # 外循环使用5,6,7三个值
    for i in range (1, 11): 
           # 内循环使用1:10十个值
        print i, "x", multiplier, "=", i * multiplier
      # 打印需要在内循环实现
    print

# 可变循环，range()函数中使用变量，循环变量由用户定义(可变的)

numStars = int(raw_input ("How many stars do you want? "))
for i in range(1, numStars + 1):        # 捕获用户定义的变量值，根据需要打印结果

# 可变嵌套循环，嵌套循环中一个或多个循环在range()函数中使用了变量
numLines = int(raw_input ('How many lines of stars do you want? '))
numStars = int(raw_input ('How many stars per line? '))
for line in range(0, numLines):
    for star in range(0, numStars): 
        print '*',
    print
numBlocks = int(raw_input('How many blocks of stars do you want? '))
for block in range(1, numBlocks + 1):
    for line in range(1, block * 2 ): 
        for star in range(1, (block + line) * 2):
            print '*',
        print
    print
    
# 决策树

print "\tDog \tBun \tKetchup\tMustard\tOnions"
count = 1
for dog in [0, 1]: 
    for bun in [0, 1]: 
        for ketchup in [0, 1]: 
            for mustard in [0, 1]: 
                for onion in [0, 1]: 
                    print "#", count, "\t",
                    print dog, "\t", bun, "\t", ketchup, "\t",
                    print mustard, "\t", onion
                    count = count + 1



# 12.列表、字典
## list=[] 创建列表，文本需要引号，数字不用
# list.append() 向列表末尾添加元素，文本需要引号
# 对象.操作() # 这是操作对象的方式
# 列表可以包含任何类型的数据，甚至包含其他列表
# 获得元素用索引号，列表索引号从0开始（与Perl一致），第1项是list[0]，第4项是list[3]
## 列表分片（切片）用索引号区间
# type(list[1])=str，type(list[1:2])=list，捕获元素和切片获得的结果类型是不一样的
# 分片可以简写，省略开头或结尾，list[:], list[:4], list[5:]
# 修改某元素，可直接用索引号，list[3]="test"
# 增加元素，append()末尾加一个, extend()末尾加多个, insert()任意位置加一个

# append('l'), extend(['l', 'm', 'n']), insert(3, 'ist')
# append() 只增加一个元素；若为append(['l', 'm', 'n'])则向list中增加一个“列表”元素
# extend() 后面跟列表，向原列表中增加新列表中的所有元素
# insert() 需要指定新元素的索引位置，以及增加的元素

# 删除元素，remove()按元素值删除，del()按索引删除，pop()剪切元素（默认尾部）

list.remove('ele')  # remove 是对象操作
del list[3]         # del 是保留字
lastletter = list.pop() # pop 是对象操作
third = list.pop(2) # 支持按索引剪切元素

# 搜索元素，in 关键字，"if 'a' in list:"
# 查找索引，index()，"list.index('c')"
# 循环处理列表元素，"for ele in list:"   # ele是循环变量
# 排序列表元素，list.sort() 对字母和数字按从小到大升序排列 # 排序会修改原列表
# 逆序列表元素，list.reverse() 对字母和数字逆序（降序）排列   # list.sort(reverse=True)
# 排序列表的副本，不修改原list，sorted()，"new = sorted(original)"    # 是函数
## tuple=() 创建元组，不可改变的列表，"my_tuple=('a', 'b', 'c')"
# list of list,双重列表，classMarks = [[55,63,77,81], [65,61,67,72], [97,95,92,88]]
# 获取双重列表的值，"dlist[0] = [1,2,3,4]", "dlist[0][0] = [1]"
## dict={} 创建空字典，再 dict['key']='val' 向其中增加元素，指定新的键值对就会添加进去
# dict={'key':'val'， ‘key2':'val2'} 创建有键值对的字典
# 查找字典，dict['key']='val'
# 列表有序，字典无序；列表使用'索引'访问，字典使用'键'访问
# keys()，列出所有键，values()，列出所有值
# del dict['ele']   # 删除dict字典中键为'ele'的键值对
# dict.clear()      # 清空字典
# 'ele' in dict     # dict字典中是否存在键为'ele'的键值对

## Python有三种动作：保留字，函数，对象操作；
# del list(3) 保留字 删除list列表的第4个元素
# new = sorted(yuan) 函数 获得yuan列表的排序副本new
# list.append('new') 对象操作 向list列表末尾增加元素new
## Python中三种括号的使用：
# list[], tuple(), dict{}
## 要获得有序打印的字典，需要使用sorted函数对字典的键进行排序
# for k in sorted(keys):    # 获得排序副本，逐个读入循环变量k
#   print k, keys[k]        # 打印时，按照键-打印值


# 13.函数
# 函数定义，"def 函数名(参数名):   折行后写代码块"
# def func(parameter):
#     blocks
# 函数调用，"函数名(参数值)"   # '参数值'将代替'参数名'出现在函数中
# 可以一次传入多个参数，用逗号隔开即可；参数达到5个或6个就应该放入list来传参了
# def func(par1,par2):     # 所有参数均用'参数值'代替'参数名'
# 参数可以直接使用上文中的变量

def printhello(name1, name2):
    print ("hello", name1, name2)
printhello('zhang', 'zhu')  # 调用，参数为zhang, zhu

# 变量作用域
# 局部变量local只作用于函数内；全局变量global作用于整个程序；
# 函数内不能改变全局变量，强制修改会临时创建一个同名的局部变量；
# 强制全局，函数内创建的一般为局部变量，但可通过global将其作用域提升到全局

# 对象
# 基本步骤：定义类(定义类方法，定义类属性)，建立初始化方法，创建类的实例(定义实例方法，定义实例属性)
'''
class Human:            # 建立Human类
    def walk(self):     # 定义类的方法walk
zhang = Human()         # 建立Human类的实例zhang
zhang.name = 'zhang san'
zhang.sex = 'nan'
zhang.high = '17x'      # 定义实例zhang的属性
zhang.walk()            # 实例zhang调用Human类中的方法
'''
# 初始化对象，初始化对象为编写者希望的状态或条件，以备使用， __init__() 方法
'''
class Human:
    def __init__(self, name, sex, high):    # self是实例引用，告诉'方法'哪个'实例'引用它
        self.name = name                    # 逐个属性定义
        self.sex = sex
        self.high = high                    # 将参数作为变量传入
'''
# Python有内置的 __init__( ) 方法来创建对象，自定义 __init__( ) 可以覆盖默认方法
# Python有默认的 __str__( ) 方法来打印内容，自定义 __str__( ) 可以覆盖默认方法
'''
    def __str__(self):
        msg = 'Hi, This is a' + self.sex + ' man named ' + self.name
'''

# 定义类，在类属性下新建init方法和属性、str方法；创建类的实例（对象），创建对象的方法、属性和输出
# 限制对象数据被访问，只能通过对象的方法来获取和修改数据，称为数据隐藏
# 多态性，类下面，不同实例可以拥有同名、但操作不同的方法（个性）
# 继承性，类下面，所有实例都继承了所属类的属性和方法（共性）
# 代码桩，用于代替'未完成的代码块'的关键字，本质是一种占位符，Python用pass作为占位符

# 模块
# 函数是少量重用代码块；模块是大量类似重用代码块的集合；
# 模块创建，和定义函数一样，一个模块文件中可以包含一个或多个函数
# 将完成类似功能的多个函数都放在一个模块文件中，也包括def 函数名(参数列表): 代码块 return返回值
# 模块调用，import my_module (模块名为my_module.py)  # 使用函数需要加模块名，module.func()
# 模块调用，from module import sub_func      # 调用模块中的具体函数，使用函数不用加模块名
# Python标准模块，time模块，random模块
# random.randint(0,10) 用于生成随机整数
# random.random() 生成0到1之间的随机数， random.random()*10 会生成0到10之间的数(范围*10)

# 事件
# 不断寻找事件的特殊循环，称为事件循环；内存中存储事件的部分，称为事件队列；
# 键盘事件
# 鼠标事件
# 定时器事件


# 格式化打印
# Python默认在每个print()函数后面自动换行
# Python3要在同一行打印多个内容，必须都在()内，用逗号隔开，如"print('hi', 'min!', 'welcome!')"
# 字串拼接直接用加号+，如"a='first', b='second', c=a+b, c='first second'"
# 自己增加换行符，直接print()空行，或在print()中加入'\n'换行符
# 换行符 \n，制表符 \t
# 字符串中插入变量，用百分号%实现格式字符串
# 数字格式化，%i打印为下取整整数，%.2f打印为2位浮点数，%+f打印时总显示正负号
# %.4e打印为4位浮点数的e记法，%g自动浮点数或e记法，%%打印出一个%
# 格式化多个字符串，将多个字串放入元组()中依次格式化，也可以提前赋值，元组中放入变量列表
# 格式化文本保存，直接赋值给变量，而不用print()

name = 'zhang san'
print('my name is %s' % name)       # %s 指str字符串， %i 指int整型， %f 指float浮点型
print('%+.2f' % 12.3457)            # 显示正负号，2位浮点数
print('% .2f' % -12.345)            # 显示负号，正号显示空格，不影响对齐，取2位浮点数
print('%.3e' % 1223334)             # 3位浮点数e记法，结果为1.223e+06
print('%g' % 2345346)               # 自动识别浮点数和大数，大数使用e记法打印
math=12.321
eng=21.342
print('math is %.2f, and eng is %.2f' % (math, eng))        # 变量构建元组
print('math is %.2f, and eng is %.2f' % (12.321, 21.342))   # 数值构建元组
var='%.2f' % 12.34567               # 将格式化后的12.34赋值给变量var


# format()格式化，不用再区分不同类型的%符号(%s, %i, %f)

print('{people} will {action}'.format(people='I',action='come'))
print('{0} will {1}'.format('He', 'go'))        # 通过变量位置(索引0开始)调用
words={'people':'He','action':'go'}             # 借助字典传入参数
print('{people} will {action}'.format(**words)) # 字典前加**，可在format()中调用
print('{:^20}'.format('something'))             # 以20为制表位宽度，:^居中排列，:<居左, :>居右
print('{:.1f}'.format(3.1415926))               # 作为float浮点型数据，'.1'保留一位小数
print('{:.4f}'.format(3.1))                     # 作为float浮点型数据，'.4'保留一位小数，不足用0补齐
print('{:,}'.format(983290189382.234))          # 逗号千位分隔符
print('{:,.4f}'.format(983290189382.234))       # 逗号分隔符在前，精度控制在后，逗号分割、4位浮点数

# 分割字符串，name_list = name_string.split(',')  # 以逗号为分隔符，拆分单词
# 连接字符串，long_string = ' '.join(word_list)   # 用空格连接单词列表，形成句子
# 搜索字符串，特定开头，startswith()，特定结尾，endswith()，常用在比较或if语句中

name='Zhangsan'
name.startswith('Z')        # 是否以Z开头，True
name.startswith('Zhe')      # 是否以Zhe开头，False
name.endswith('n')          # 是否以n结尾，True
name.endswith('saan')       # 是否以saan结尾，False

# 字串中搜索，in关键字搜索是否存在，index()搜索索引位置

a='long short multi line string'
if 'multi' in a:                    # in判断字符串是否存在于变量a中
    position = a.index('multi')     # a.index()搜索字符串在变量a中的索引位置
    print ("found 'multi' at index", position)

# 删除行尾字符或空白符，strip()

a='hello smith orderated'
a.strip('ed')   # 指定字符串'ed'，删除末尾存在的字符'ed'，若不存在则不修改
a.strip()       # 没有指定参数，删除末尾的空白符(空格\s、制表符\t、换行符\n)

# 改变大小写，全小写lower()，首字母大写capitalize()，全大写upper()

a='HELlo'
a.lower()       # hello
a.capitalize()  # Hello
a.upper()       # HELLO


# 文件读写
# 基本流程：打开文件、读文件、处理、关闭文件
# 打开文件，关闭文件
# 读文件
# 逐行读取
# 写文件，追加模式

my_file = open('notes.txt', 'r')    # 打开文件，读方式打开read        r方式打开后，才能进行操作
lines = my_file.readlines()         # 逐行读取全部内容
fisrt_line = my_file.readline()     # 读入一行
my_file.close()                     # 关闭文件
my_file.seek(0)                     # 单行读取几行后，可回到起始位置
my_file = open('notes.txt', 'w')    # 打开文件，写方式打开write       w方式打开后，支持写入操作
my_file = open('notes.txt', 'a')    # 打开文件，追加方式打开append
my_file.write('new info to write')  # 写入内容
my_file.close()                     # 关闭文件
my_file = open("file.txt", 'w')
print >> my_file, "Hello there, neighbor!"      # print()重定向写入文件，后面跟内容
my_file.close()                     # 关闭文件

# 用pickle模块读写，需要'import pickle'

import pickle                       # 导入模块
pickle_file = open('my_pickled_list.pkl', 'w')  # 写方式打开
pickle.dump(my_list, pickle_file)   # .dump方式将my_list写入pickle_file
pickle_file.close()
pickle_file = open('my_pickled_list.pkl', 'r')  # 读方式打开
recovered_list = pickle.load(pickle_file)       # 还原之前的内容
pickle_file.close()



# 随机数
# 产生随机数需要import random模块
# 生成随机整数

s = random.randint(1,6)     # 在1-6中随机生成整数
sides = [1,2,3,4,5,6]
s = random.choice(sides)    # 6个面中随机选一个，生成1-6中的一个随机数

# random.randint()中的范围是双包含的，randint(1,6)是指1-6的数
# 循环部分，range()是半包含的，不含后面的数，range(1,6)是指1-5的数


```

