反射特性:
    只根据类的名字就可以获取该类的实例
    
    定义好Person后,并不知道谁将会实现该接口,甚至不知道什么时候会实现它.所以无法通过new操作符来实例化对象
    
    某个未来的时候,有人编写类Tom的一个类.但此时你不可能实例化Tom这个类,智能编写下面这种代码:
    
    ```
    std::string className=/* 从配置文件中读取*/
    Person *p = getNewInstance<Person>(className);
    
    ```
    程序从配置文件中读取到"Tom"这个字符串保存到变量className中.
    接下来使用函数getNewInstance就可以获取到Tom实例化的对象.
    
    
###完整实例

>main 函数
```

#include "Person.h"
#incldue "Reflector.h"

int _tmain(int argc,char* argv[])
{
    
    Person *allen = getNewInstance<Person>("Allen");
    Person *luffy = getNewInstance<Person>("Luffy");
    
    allen->show();
    lyffy->show();
    
    delete allen;
    delete luffy;
    
    return 0;
}

```

