### c++中map的使用

```
template < class Key,                                     // map::key_type
           class T,                                       // map::mapped_type
           class Compare = less<Key>,                     // map::key_compare
           class Alloc = allocator<pair<const Key,T> >    // map::allocator_type
           > class map;
```

map是一种容易,用来存储若干元素,这些元素都是由关键值(key值)和映射值配对组成的

`typede pair<const Key,T> value_type`
在map内部的元素通常按照其Key值排序,且排序方式是根据某种明确/严格的弱排序标准进行的,这种排序标准是由map内部的比较对象指定的
map通常使用二叉搜索树实现

#### map容器的属性

* 关联性
* 有序行
* 映射
* 唯一Key值
* 分配感知


map常用函数
* 构造函数
* clear
* erase
* insert
* find
* begin/end
* rbegin/rend map的反向迭代器的起始位置与终点位置

***
### unordered_map

```
template < class Key,                                    // unordered_map::key_type
           class T,                                      // unordered_map::mapped_type
           class Hash = hash<Key>,                       // unordered_map::hasher
           class Pred = equal_to<Key>,                   // unordered_map::key_equal
           class Alloc = allocator< pair<const Key,T> >  // unordered_map::allocator_type
           > class unordered_map;
           
```
unordered_map 是一种关联容器，用于存储由关键值 (Key Value，以下称为Key 值) 和映射值 (Mapped Value，以下称为映射值) 组成的元素，并且允许根据其 Key 值快速检索各个元素。

在 unordered_map 容器中，Key 值通常用来唯一标识元素，映射值是与该 Key 值关联内容的对象。Key 值与映射值的类型可能不同。 

在 unordered_map 内部，元素没有按照其 Key 值与映射值的任何顺序进行排序 ，而是根据它们的 Hash 值组织成桶，允许它们通过其 Key 值直接快速访问单个元素（通常具有常数等级的平均时间复杂度）。 
unordered_map 容器与 map 容器相比，通过 Key 值访问各个元素的速度更快，然而通过其元素子集进行范围迭代的效率通常较低。 
unordered_map 实现了直接访问操作符 (operator[])，它允许使用 Key 值作为输入参数，直接访问映射值。 
容器中的迭代器至少是前向迭代器。

#### 容器属性
* 关联性
* 无序性
* 映射
* 唯一关键值
* 分配器感知

***
#### map, hash_map, unordered_map 的区别

##### 头文件
1. map:#include <map>
2. hash_map:#include <hash_map>
3. unordered_map:#include <unordered_map>

##### 内部实现机理
map： 
map 内部实现了一个红黑树，该结构具有自动排序的功能，因此map内部的所有元素都是有序的，红黑树的每一个节点都代表着map的一个元素，因此，对于map进行的查找，删除，添加等一系列的操作都相当于是对红黑树进行这样的操作，故红黑树的效率决定了map的效率，map只需要提供比较函数（一般为小于函数）即可完成比较；

hash_map： 
hash_map 需要提供 hash 函数，以及等于函数；

unordered_map： 
unordered_map 内部实现了一个 Hash 表，所以其元素的排列顺序是杂乱无序的。

##### 优缺点
map： 
优点： 
有序性：这是map结构最大的优点，其元素的有序性在很多应用中都会简化很多的操作；
红黑树，内部实现一个红黑书使得 map 的很多操作在 log n 的时间复杂度下就可以实现，因此效率非常的高；
缺点： 
空间占用率高，因为 map 内部实现了红黑树，虽然提高了运行效率，但是因为每一个节点都需要额外保存父节点，子节点以及红/黑性质，使得每一个节点都占用大量的空间；
适用于具有顺序要求的问题；

hash_map： 
优点： 
hash_map 查找速度会比map快，而且查找速度基本和数据量大小无关，属于常数级别（但不能说一定比 map 的 log n 级别快，因为 hash 函数本身也有耗时）；
缺点： 
空间占用多，如果对内存使用很严格，需要认真考虑是否使用 hash_map ；特别是当 hash_map 对象特别多时，更加难以控制；
适用于对效率要求较高的环境；

unordered_map： 
优点： 
内部实现了 Hash 表，所以查找速度很快；
缺点： 
Hash 表的建立比较比较费时；
适用于查找问题；