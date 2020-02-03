单例模式也称为单件莫斯/单子模式.
其意图是保证一个类仅有一个实例,并提供一个访问它的全局访问点,该实例被所有程序模块共享.

<<设计模式>>中的实现:定义一个单例类,使用类的私有静态指针变量指向类的唯一实例,并用一个公有的静态方法获取该实例.

单例模式通过类本身来管理其唯一实例,这种特性提供了解决问题的方法.唯一的实例是类的一个普通对象,但设计这个类时,让它只能创建一个实例并提供对此实例的全局访问.唯一实例类Singleton在静态成员函数中隐藏创建实例的操作.习惯上把这个成员函数叫做instance(),它的返回值是唯一实例的指针.

```
class CSingleton  
{  
private:  
    CSingleton()   //构造函数是私有的  
    {  
    }  
    static CSingleton *m_pInstance;  
public:  
    static CSingleton * GetInstance()  
    {  
        if(m_pInstance == NULL)  //判断是否第一次调用  
            m_pInstance = new CSingleton();  
        return m_pInstance;  
    }  
};  
```

用户访问唯一私立的方法是Getinstance()成员函数.如果不通过这个函数,任何创建爱你实例的尝试都将失败,因为累的构造函数是私有的.GetInstance()使用懒惰初始化,也就是说它的返回值是当这个函数首次被访问时被创建的.

```
#include <iostream>>  
  
using namespace std;  
  
class Singleton  
  
{  
  
public:  
  
    static Singleton *GetInstance();  
  
private:  
  
    Singleton()  
  
    {  
  
        cout << "Singleton ctor" << endl;  
  
    }  
  
    ~Singleton()  
  
    {  
  
        cout << "Singleton dtor" << endl;  
  
    }  
  
    static Singleton *m_pInstance;  
  
    class Garbo  
  
    {  
  
    public:  
  
        ~Garbo()  
  
        {  
  
            if (Singleton::m_pInstance)  
  
            {  
  
                cout << "Garbo dtor" << endl;  
  
                delete Singleton::m_pInstance;  
  
            }  
  
        }  
  
    };  
  
    static Garbo garbo;  
  
};  
  
Singleton::Garbo Singleton::garbo;  // 一定要初始化，不然程序结束时不会析构garbo  
  
Singleton *Singleton::m_pInstance = NULL;  
  
Singleton *Singleton::GetInstance()  
  
{  
  
    if (m_pInstance == NULL)  
  
        m_pInstance = new Singleton;  
  
    return m_pInstance;  
  
}  
  
int main()  
  
{  
  
    Singleton *p1 = Singleton::GetInstance();  
  
    Singleton *p2 = Singleton::GetInstance();  
  
    if (p1 == p2)  
  
        cout << "p1 == p2" << endl;  
  
    return 0;  
  
} 

```

输出结果如下：

Singleton ctor

p1 == p2

Garbo dtor

Singleton dtor