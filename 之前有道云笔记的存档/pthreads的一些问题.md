Pthreads 指定 API 来处理线程要求的大部分行为. 这些行为包括创建和终止线程、等待线程完成、以及管理线程之间的交互. 后面的目录中存在各种锁定机制，能够阻止两个线程同时尝试修改相同的数据值，这些锁定机制包括互斥锁、条件变量.

在 Linux 环境下，可以在 Shell 中通过 man 查询到 Pthreads 的部分函数命令,如： man pthread_create


### 线程的创建和管理
每个线程都有一个在进程中唯一的线程标识符，用一个数据类型 pthread_t 表示，该数据类型在 Linux 中就是一个无符号长整型数据.

##### 创建新的线程
```
int pthread_create (pthread_t *thread,pthread_attr_t *attr,void *(*start_routine)(void *),void *arg)
```
若创建成功，返回0；若出错，则返回错误编号. thread 是线程标识符，但这个参数不是由用户指定的，而是由 pthread_create 函数在创建时将新的线程的标识符放到这个变量中. attr 指定线程的属性，可以用 NULL 表示默认属性. start_routine 指定线程开始运行的函数，arg 是 start_routine 所需要的参数，是一个无类型指针.

默认地,线程在被创建时要被赋予一定的属性，这个属性存放在数据类型 pthread_attr_t 中，它包含了线程的调度策略，堆栈的相关信息，join or detach 的状态等.

pthread_attr_init 和 pthread_attr_destroy 函数分别用来创建和销毁pthrea_attr_t,具体函数声明可参考man.

##### 结束线程
当发生一下情况时,线程就会结束:

* 线程运行的函数return了，也就是线程的任务已经完成；

* 线程调用了 pthread_exit 函数；

* 其他线程调用 pthread_cancel 结束这个线程；

* 进程调用 exec() or exit()，结束了；

* main() 函数先结束了，而且 main() 自己没有调用 pthread_exit 来等所有线程完成任务.

两个函数:
`void pthread_exit (void *retval)`
retval是由用户制定的参数,pthread_exit 完成之后可以通过这个参数获得线程的退出状态.
`int pthread_cancel (pthread_t thread)`
一个线程可以通过调用 pthread_cancel 函数来请求取消同一进程中的线程，这个线程由thread 参数指定. 如果操作成功则返回0，失败则返回对应的错误编号.

#####　对线程的阻塞
阻塞是线程之间同步的一种方法：
`int pthread_join(pthread_t threadid, void **value_ptr)`
pthread_join函数会让调用它的线程等待threadid 线程运行结束之后再运行. value_ptr 存放了其他线程的返回值. 一个可以被join的线程，仅仅可以被别的一个线程 join，如果同时有多个线程尝试 join 同一个线程时，最终结果是未知的. 另外，线程不能 join 自己.

创建一个线程时，要赋予它一定的属性，这其中就包括joinable or detachable 的属性，只有被声明成joinable的线程，可以被其他线程join. POSIX标准的最终版本指出线程应该被设置成joinable的. 

POSIX标准没有规定一个线程的堆栈大小. 安全可移植的程序不会依赖于具体实现默认的堆栈限制，而是显式地调用 pthread_attr_setstacksize 来分配足够的堆栈空间.

调用pthread_self 可以返回它的 thread ID. pthread_equal 比较两个线程的 ID,如果不同则返回0,否则返回一个非零值.

##### 互斥锁 Mutex
Mutex 常常被用来保护那些可以被多个线程访问的共享资源，比如可以防止多个线程同时更新同一个数据时出现混乱.
使用互斥锁的一般步骤是:

创建一个互斥锁，即声明一个pthread_mutex_t类型的数据,然后初始化，只有初始化之后才能使用；

多个线程尝试锁定这个互斥锁；

只有一个成功锁定互斥锁，成为互斥锁的拥有者，然后进行一些指令；

拥有者解锁互斥锁；

其他线程尝试锁定这个互斥锁，重复上面的过程；

最后互斥锁被显式地调用 pthread_mutex_destroy 来进行销毁.



