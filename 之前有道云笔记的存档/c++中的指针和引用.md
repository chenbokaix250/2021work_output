### （int*、int&、int*&、int&*、int**）之间的区别

指针 ---- 指向某一块内存的变量，其本身存储的信息就是内存地址的首地址，其类型决定指向内存的大小.

变量 ---- 某一块内存地址数据值的名字.

引用 ---- 变量的别名.

int
```
#include <iostream>
using namespace std;

void swap1(int a, int b){
    int tmp;
    tmp = a;
    a = b;
    b = tmp;
}
int main(){
    int a = 1;
    int b = 2;
    swap1(a, b);
    cout<<"a = "<<a<<endl;
    cout<<"b = "<<b<<endl;
    
    return 0;
}
``` 
交换只是交换了形参的值,交换失败

---

int*
```
#include <iostream>
using namespace std;

void swap2(int *a, int *b){
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

int main(){
    int a = 1;
    int b = 2;
    swap2(&a, &b);
    cout<<"a = "<<a<<endl;
    cout<<"b = "<<b<<endl;
  
    return 0;
}
```
传入地址，就可以直接操作实参的值,交换成功

---
int&
```
#include <iostream>
using namespace std;

void swap3(int& a, int& b){
    int tmp;
    tmp = a;
    a = b;
    b = tmp;
}

int main(){
    int a = 1;
    int b = 2;
    swap3(a, b);    
        cout<<"a = "<<a<<endl;
    cout<<"b = "<<b<<endl;
    system("pause");
    return 0;
}
```
引用也是可以直接访问到实参和控制实参的,交换成功

---
int*&
```
#include <iostream>
using namespace std;

void swap5(int *&a, int *&b){
    int tem = *a;
    *a = *b;
    *b = tem;
}

int main(){
    int a = 1;
    int b = 2;

    int *aPtr = &a;
    int *bPtr = &b;
    int *&arPtr = aPtr;
    int *&brPtr = bPtr;

    swap5(arPtr, brPtr);

    cout<<"a = "<<a<<endl;
    cout<<"b = "<<b<<endl;
    system("pause");
    return 0;
}
```
交换成功。这个稍微复杂一点，int*&  value这样一个声明，我们从最接近value的符号看起，是个&，说明value是一个引用，它是一个什么引用呢？再看*，它是一个指针的引用，即指针的别名，我们用*value就可以访问到实参的值了。所以，其交换函数的内部逻辑跟int *是一样的。


***
int &*
交换成功。这样定义就不合法，如果从字面上来看，我们分析一下，如int &* value，最接近value的是*，说明value是一个指针，再看前面的是&，说明是一个指针的引用，而指针是无法被引用的，所以，这样的定义是不合法的，不要记这个。

***
int**
```
#include <iostream>
using namespace std;

void swap6(int **a, int **b){
    int tmp;
    tmp = **a;
    **a = **b;
    **b = tmp;
}

int main(){
    int a = 1;
    int b = 2;
    int *aPtr = &a;//指向数据的指针
    int *bPtr = &b;//指向数据的指针
    int **aaPtr = &aPtr;//指向指针的地址的指针
    int **bbPtr = &bPtr;//指向指针的地址的指针
    swap4(aaPtr, bbPtr);
    cout<<"a = "<<a<<endl;
    cout<<"b = "<<b<<endl;
    system("pause");
    return 0;
}
```
交换成功。同样的，比如int **value， 最接近value的是*，说明value是一个指针，在前一个是*，说明是一个指向指针的指针，这样是合法的，那么如何访问value代表的实际参数的值呢？很简单，用**value就可以了，记住*是一个操作符，如同&一样，不过&是取地址操作符，而*是取值操作符。