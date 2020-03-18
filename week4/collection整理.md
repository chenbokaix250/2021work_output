# collection 容器数据类型

模块实现了特定目标的容器 以提供python标准内建容器 dict list set 和tuple的替代选择

* namedtuple 创建命名元祖子类的工厂函数
* deque 类似列表(list)的容器,实现了在两端快速添加(append)和弹出(pop)
* ChainMap 类似字典(dict的容器类,将多个映射集合到一个视图里面
* Counter 字典的子类,提供了可哈希对象的技术功能
* OrderedDict 字典的子类,保存了他们被添加的顺序
* defaultdict 字典的子类,提供了一个工厂函数,为字典查询提供一个默认值
* UserDict 封装了字典对象,简化了字典子类化
* UserList 封装了列表对象,简化了列表子类化
* UserString 封装了列表对象,简化了字符串子类化

## Counter 对象
一个计数器工具提供快速和方便的计数 
```
>>> # Tally occurrences of words in a list
>>> cnt = Counter()
>>> for word in ['red', 'blue', 'red', 'green', 'blue', 'blue']:
...     cnt[word] += 1
>>> cnt
Counter({'blue': 3, 'red': 2, 'green': 1})

>>> # Find the ten most common words in Hamlet
>>> import re
>>> words = re.findall(r'\w+', open('hamlet.txt').read().lower())
>>> Counter(words).most_common(10)
[('the', 1143), ('and', 966), ('to', 762), ('of', 669), ('i', 631),
 ('you', 554),  ('a', 546), ('my', 514), ('hamlet', 471), ('in', 451)]
```

## deque 对象
`class collections.deque([iterable[,maxlen]])`
返回一个新的双向队列对象,从左到右初始化(append),从iterable(迭代对象)数据创建.
Deque队列是由栈或者queue队列生成的.Deque支持线程安全,内存高效.

如果maxlen没有指定或者是None,deques可以增加到任意长度
### 双向队列(deque)对象支持的方法:
* append(x) 添加x到右端
* appendleft(x) 添加x到左端
* clear() 移除所有元素,使其长度为0
* copy() 创建一份浅拷贝
* count(x) 计算deque中元素等于x的个数
* extend(iterable) 扩展deque右侧,通过添加iterable参数中的元素
* extendleft(iterable) 从左侧扩展
* index(x[,start[,stio]]) 返回在中的位置
* insert(i,x) 在位置插入x
* pop() 移出并返回一个元素
* popleft() 移出并返回一个元素 最左侧的那个
* remove(value) 移除找到的第一个value
* reverse() 将deque逆序排列 返回None























