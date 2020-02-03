### c++类成员的初始化 
使用初始化列表进行初始化的方法
```
class Student{
    
public:
    Student(string in_name,int in_age):name(in_name),age(in_age){}
private:
    string name;
    int    age;
};
```
等价于:
```
class Student{
public:
    Student(string in_name,int in_age)
    {
        name = in_name;
        age = in_age;
    }
private:
    string name;
    int age;
};

```

### 类模板
```
template <class type> class class-name {

}
```
在这里，type 是占位符类型名称，可以在类被实例化的时候进行指定。您可以使用一个逗号分隔的列表来定义多个泛型数据类型



