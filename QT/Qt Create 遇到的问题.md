# Qt学习中的记录


# Qt Create 遇到的问题

Q1:在 macOS 上的 Qt Creator 中出現 No valid kits found

https://blog.yowko.com/no-valid-kits-found-on-mac/

Q2:书籍下载

https://gitee.com/feiyangqingyun/qtkaifajingyan/blob/master/Qt%20Creator%E5%BF%AB%E9%80%9F%E5%85%A5%E9%97%A8_%E7%AC%AC%E4%B8%89%E7%89%88__%E9%9C%8D%E4%BA%9A%E9%A3%9E%E7%BC%96%E8%91%97.z01

Q3:Qt 5.5 'QApplication'file not found 解决办法
https://blog.csdn.net/Sub_lele/article/details/52240474


Q4：使用Assitant
使用Assitant可以查看各种类的用法

只安装`Qt create`是没有的 需要安装完整的`qt-opensource-mac-x64-5.14.2.dmg`
然后在`Qt5.14.2/5.14.2/clang/bin`目录中

---

常用的工具
* assistant
* qmake
* designer
* uic
* rcc
* moc
* qtcreator

利用`qmake -project` 生成和工程名相同的`.pro`文件
一般添加`QT+= widgets`,然后利用qmake连接pro文件,生成`Makefile`
然后make

利用designer可以直接进行界面设计,为`ui`文件.然后利用uic转换为h文件
`uic designer.ui -o ui_designer.h`

rcc是将资源文件转义程`.h`文件

---

##第一个Qt函数

```c++

int main(int argc,char** argv)
{
    //创建Qt应用程序对象
    QApplication app(argc,argv);
    //创建爱你标签控件
    QLabel label("Hello Qt!");
    //显示标签控件
    label.show();
    //让应用程序进入事件循环
    return app.exec());
}
```

利用`qmake -project` 生成和工程名相同的`.pro`文件
一般添加`QT+= widgets`,然后利用qmake连接pro文件,生成`Makefile`
然后make

```bash
Hello$ qmake -project
Hello$ ls 
Hello$ Hello.pro   main.cpp 
Hello$ qmake
Hello$ ls
Hello$ Hello.pro   main.cpp  Makefile
Hello$ make
Hello$ Hello Hello.pro main.cpp main.o Makefile
Hello$ ./Hello
```

## Qt中文编码
Qt中文编码 利用utf-8能正确显示
如果需要编码转换,需要利用`QTextCodec`:

```c++
QTextCodec *codec = QTextCodec::codecForName("GBK");
QString string = codec->toUnicode("GBK编码的中文字符串");

```


## 父窗口

创建控件时,可以指定停靠在某个父窗口上面,这时控件将作为子窗口被束缚在其父窗口的内部,伴随其一起移动/隐藏/显示和关闭.否则该控件将作为独立窗口显示在屏幕上,且游离在其他窗口外

QWidget及其子类的对象可以做为其它控件的父窗口
常用的父窗口类有如下三个:

1. QWidget
2. QMainWindow(主窗口)
3. QDialog(对话框)

调试窗口的位置和大小
```c++
void move(int x,int y);
void resize(int w,int h);
```


## 信号与槽函数

信号的定义
```c++
class XX:public QObject{
    Q_OBJECT
signals:
    void signal_func(..);//信号函数
}

//信号函数只需声明,不能写定义
```

槽函数定义:
```c++
class XX:public QObject{
    Q_OBJECT
public slots:
    void slot_func(...){...}//槽函数    
}

//槽函数可以连接到某个信号上,当信号被发射时,槽函数将被触发和执行,另外槽函数也可以当做普通的成员函数直接调用.
```

信号和槽的连接

```
QObject::connet(const QObject* sender,const char* signal,const QObejct* receiver,const char* method);
```

参数:

sender:信号发送对象指针
signal:要发送的信号函数,可以使用"SIGNAL(..)"宏进行类型转换
receiver:信号的接收对象指针
method:接收信号后要执行的槽函数,可以使用"SLOT(..)"宏进行类型转换

```c++
QObject::connect(&button,SIGNAL(clicked(void)),&label,SLOT(close(void)));

//button的按下触发clicked信号 将label执行关闭操作
```
信号和槽连接时的语法要求

* 信号和槽参数要一致.
* 可以带有缺省参数
* 信号函数的参数可以多于槽函数,多余参数将被忽略

```c++
// param consistency
QObject::connect(A,SIGNAL(sigfun(int)),B,SLOT(slotfun(int))); //ok
QObject::connect(A,SIGNAL(sigfun(int)),B,SLOT(slotfun(int,int)));//error

```
QSlider //滑块
```c++
void setRange(int min,int max);//设置滑动范围
void setValue(int)[slot];//设置当前位置
void valueChanged(int value)[signal];//滑块滑动时发送信号
```
QSpinBox //选值框
```c++
void setRange(int min,int max);//设置数值改变范围
void setValue(int)[slot];//设置当前数值
void valueChanged(int value)[signal];//选值框数值改变时发送信号
```
利用滑块改变选值框的值

`Qobject::connect(&slider,SIGNAL(valueChanged(int)),&spin,SLOT(setValue(int)));`

利用选值框改变滑块位置

`Qobject::connect(&spin,SIGNAL(valueChanged(int)),&slider,SLOT(setValue(int)));`


## QT面向对象

设置文本对齐方式
`setAlignment(Qt::AlignRight)`

设置多个参数 用`|`隔开
`setAlignment(Qt::AlignHCenter|Qt::AlignVCenter)`

设置label的字体大小
```c++
QFont font;
font.setPointSize(20);
m_label->setFont(font);
```

创建布局器(垂直)
```
QVBoxLayout* layout = new QVBoxLayout(this);
layout->addWidget(m_label);
layout->addWidget(m_button);
setLayout(layout);
```



数字验证器
`setValidator(new QDoubleValidator(this));`
设置验证器 new数字验证器对象 参数是父窗口指针

**案例** 获取系统时间

槽函数设计:
`connect(m_button,SIGNAL(clicked(void)),thismSLOT(getTime(void)));`

发射信号:
`emit mySignal(str);`
label边框效果设置:
`m_label->setFrameStyle(QFrame::Panel|QFrane::Sunken);`

获取当前系统时间
`QTime time = QTime::currentTime();`
//设置格式
`QString str = time.toString("hh:mm:ss");`
//显示时间
`setText(str);`


**案例** 图片显示器

利用create中ui设置连接槽 生成槽函数.

绘图事件处理
```c++
QPainter painter(this);//创建画家对象
QRect rect = ui->frame->frameRect();//获取绘图所在的矩形区域
QImage image("资源文件目录");//构建图形对象
painter.drawImage(rect.image);//使用painter将image图片画到rect
```
坐标值平移,让rect和painter使用相同坐标系
`rect.translate(ui->frame->pos());`

时间事件处理
```c++
//虚函数方式
void timerEvent(QTimerEvent *);q

//设置随即种子
qsrand(QTime::currentTime().msec());

m_timer = startTimer(50);//开始定时器
killTimer(m_timer);//结束定时器

//槽函数实现方式
m_timer.start(50);
m_timer.stop(50);

//定义槽函数onTimeout()和发送信号timeout
//定时器到时时,发送timeout信号
connect(&m_timer,SIGNAL(timeout(),this,SLOT(onTimeout()));

```

##鼠标键盘事件

QWidget类定义虚函数提供鼠标事件的处理,其参数QMouseEvent描述了鼠标事件的细节:
```c++
virtual void mousePressEvent(QMouseEvent* e);//鼠标按下
virtual void mouseReleaseEvent(QMouseEvent* e);//鼠标抬起
virtual void mouseDoubleClickEvent(QMouseEvent* e);//鼠标双击
virtual void mouseMoveEvent(QMouseEvent* e);//鼠标移动
```

重写虚函数 利用其event形参变量的成员button进行判断
```
void MouseDialog::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt;;LeftButton){
        xxxx;
    }
}
```

## 键盘处理按键
QWidget类定义了以下虚函数提供对键盘事件的处理,其参数QKeyEvent描述了键盘事件的细节:
```c++
virtual void keyPressEvent(QKeyEvent* e);//按键按下
virtual void keyReleaseEvent(QKeyEvent* e);//按键抬起
```
重写虚函数 利用其event形参变量的
```c++
void keyPressEvent(QKeyEvent *event){
    if(event->key()== Qt::Key_Up){
        xxx;
    }
}
```

---

sqlite数据库

数据库是以一定方式村塾在一起,能为多个用户共享,具有尽可能小的冗余特性,是与应用程序彼此独立的数据集合

相关术语:
* DB    数据库(database)
* DBMS  数据库管理系统
* DBA   数据库管理员
* RDB   关系型数据库

数据库操作语言(SQL)

常用的SQL语句
数据操作语言(DML):SELECT INSERT DELETE UPDATE
数据定义语言(DDL):CREATE TABLE

Sqlite的两种指令 
一种是自身配置和格式控制相关指令,都以`.`开头
一种是SQL语言,实现对数据库的增删改查等操作,这些以";"结束

其中:
.help可以获取帮助信息
.exit或.quit可以退出SQLite的命令节目,回到系统的控制终端
`Ctrl+L`可以进行清屏


Sqlite的常用命令

.database  查看数据库的名字和对应的文件名
.table     查看数据表的名字
.schema    查看数据表创建时信息
.mode      设置显示模式
.nullvalue 设置空白字段显示的字符串
.header on 显示数据表的表头

Sqlite命令行程序(SQL语句)
创建数据表
`CREATE TABLE 表名(列名1 类型[约束],列名2 类型[约束],...);`
常用的类型
INT(整型) TEXT(字符串) REAL(浮点数)
常用的约束:
`PRIMARY KEY(主键):表示该列数据唯一,可以加快数据访问`
`NOT NULL(非空):该列数据不能为空`

向数据表中插入数据
`INSERT INTO 表名(列名1,列名2,...) VALUES(数值1,数值2,...);`
如果要为表中的所有列添加值,并且插入列的顺序和创建表的顺序相同,可以不需要在Sqlite查询中指定列名
`INSERT INTO 表名 VALUES(数值1,数值2,...);`
从数据表删除数据
`DELETE FROM 表名 WHERE 条件表达式;`

修改数据表中的数据
`UPDATE表名 SET 列名1=新数值,列名2=新数值,.... WHERE 条件表达式;`

查询数据表中的数据
```
SELETE 列名1,列名2,... FROM表名;
SELETE 列名1,列名2,... FROM表名WHERE条件表达式;
SELECT 列名1,列名2,... FROM表名WHERE条件表达式 ORDER BY 列名排序方式
```

模糊查询
`SELECT 列名1,列名2,.. FROM表名WHERE列名LIKE模糊匹配条件;`


**案例** 学生数据管理平台

```c++
QSqlDatabase db;//建立Qt和数据库链接
QSqlQueryModel model;//保存结果集

//成员函数
void createDB();//创建数据库
void createTable();//创建数据表
void queryTabel();//查询

//添加数据库驱动
QSQLDatabase::addDatabase("QSQLITE")
//设置数据库名字
setDatabaseName("sqlite.db")
//打开数据库
db.open()


//创建数据表
QSqlQuery query;
QString str = QString("CREATE TABLE student("
                    "id TNT PRIMARY KEY NOT NULL,"
                    "name TEXT NOT NULL,"
                    "score REEAL NOT NULL)");
query.exec(str);//创建成功返回true 否则返回yes


//查询
QString str = QString("mouseDoubleClickEvent * FROM student");
model.setQuery(str);
//利用tableView显示
ui->tableView->setModel(&model);


//增删改查的具体实现

//增加
QSqlQuery query;
QString name = ui->nameEdit->text();//从控件获取插入值 根据不同类型进行转换 toInt() toDouble() toString()
QString str = QString("INERTINTOstudentVALUES(%1,%2,%3)").arg(id).arg(name).arg(score);
query.exec(str);

//删除
QSqlQuery query;
int id = ui->idEdit->text().toInt();
QString str = QString("DELETE FROM student WHERE id = %1").arg(id);
query.exec(str);

//修改
QSqlQuery query;
int id = ui->idEdit->text().toInt();
double score = ui->scoreEdit->text().toDouble();
QString str = QString("UPDATE student SET score=%1 WHERE id=%2").arg(score).arg(id);
query.exec(str);

//排序
conodition = "ASC/DESC";//升序/降序
QString str = QString("SELECT * FROM student ORDER BY %1 %2").arg(value).arg(condition)
model.setQuery(str);
ui->tableView->setModel(&model);//显示结果
```
---

**案例** 聊天室

1. 需求分析
2. 概要设计
3. 详细设计
4. 代码编写
5. 测试/升级维护

![截屏2021-04-29 下午3.44.58.png](https://i.loli.net/2021/04/29/eNya5DEtInwBPSR.png)

![截屏2021-04-29 下午3.44.44.png](https://i.loli.net/2021/04/29/rRCiGqzg5h1Vvwu.png)

### 服务器 QTcpServer

QTcpServer类提供了一个基于TCP的服务器,通过该类可以快速建立TCP服务器,并接受客户端的连接请求

QTcpServer::listen()函数可以指定服务器的端口号,该函数可以监听主机IP地址(QHostAddress)

设置监听后,每当检测到客户端发来连接请求,将会发送信号`newConnection()`,可以自定义槽函数,在其中调用`nextPendingConnection()`获取和客服端通信的套接字.

过程伪代码
```c++
//创建QTcpServer对象
QTcpServer tcpServer;
//开启TCP服务器,监听所有地址
tcpServer.listen(QHostAddress::Any,port)
//连接客户端连接时的槽函数
connect(&tcpServer,SIGNAL(newConnection()),this,SLOT(onNewConnection()));
```

服务器:接收客户端发来的消息
```c++
void ServerDialog::onReadyRead(){
    for(int i=0;i<clientList.size();i++)//遍历检查哪个客户端有消息到来
        if(clientList.at(i)->bytesAvaliable()){
            QByteArray buf = clientList.at(i)->readAll();//读取消息并保存
            ui->listWidget->addItem(buf);//显示消息到界面
            sendMessage(buf);//转发消息给其他在线客户端
        }
}
```
### 客户端 
```
QTcpSocket tcpSocket;//和服务器通信的tcp套接字
tcpSocket.connectToHost(serverIP,serverPort);//向服务器发送连接请求

//和服务器连接时发送信号connected
connect(&tcpSocket,SIGNAL(connected()),this,SLOT(onConnected()));
//当收到服务器转发消息时发送readyRead()信号
connect(&tcpSocket,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
```

客户端:发送聊天消息
点击发送按钮向服务器发送聊天消息
```c++
void ClientDialog::on_sendButton_clicked(){
    QString msg = ui->messageEdit->text();//获取用户输入的聊天内容
    msg = username + ":" + msg;//消息修饰
    tcpSocket.write(msg.toUtf8();//向服务器发送聊天消息
    ui->messageEdit->clear();//清空已输入的消息
}
```

客户端;接收聊天消息
检测信号"readyRead"有消息到来则读取
```c++
void ClientDialog;;onReadyRead(){
    if(tcpSocket.bytesAvaliable()){//获取等待读取消息字节数
        QByteArray buf = tcpSocket.readAll();//读取消息并保存
        ui->listWidget->addItem(buf);//显示消息
    }
}
```
---























