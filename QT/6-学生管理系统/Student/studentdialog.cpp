#include "studentdialog.h"
#include "ui_studentdialog.h"

StudentDialog::StudentDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StudentDialog)
{
    ui->setupUi(this);
    createDB();
    createTable();
    queryTable();
}

StudentDialog::~StudentDialog()
{
    delete ui;
}

//插入
void StudentDialog::on_insertButton_clicked()
{
    QSqlQuery query;
    int id = ui->IDEdit->text().toInt();
    if(id == 0){
        QMessageBox::critical(this,"ERROR","学号插入不合法!");
        return;
    }
    QString name = ui->nameEdit->text();
    if(name == ""){

        QMessageBox::critical(this,"ERROR","姓名插入不合法!");
        return;
    }
    double score = ui->scoreEdit->text().toDouble();

    if(score<0 ||score >100){
        QMessageBox::critical(this,"ERROR","成绩插入不合法!");
        return;
    }
    QString str = QString("INSERT INTO student (id,name,score) VALUES(%1,'%2',%3)"
                                    ).arg(id).arg(name).arg(score);


    if(query.exec(str)==false){
        qDebug()<<str;
    }else{
        qDebug()<<"插入数据成功!";
        queryTable();
    }

}
//删除
void StudentDialog::on_deletButton_clicked()
{
    QSqlQuery query;
    int id = ui->IDEdit->text().toInt();
    QString str = QString("DELETE FROM student WHERE id = %1").arg(id);
    if(QMessageBox::question(this,"删除","确定进行删除?",QMessageBox::Yes|QMessageBox::No)==QMessageBox::No){
        return;
    }
    if(query.exec(str)==false){
        qDebug()<<str;
    }else{
        qDebug()<<"删除操作成功";
        queryTable();
    }
}
//修改 根据ID修改成绩
void StudentDialog::on_updateButton_clicked()
{
    QSqlQuery query;
    int id = ui->IDEdit->text().toInt();
    double score = ui->scoreEdit->text().toDouble();
    QString str = QString("UPDATE student SET score=%1 WHERE id = %2").arg(score).arg(id);
    if(query.exec(str)==false){
        qDebug()<<str;
    }else{
        qDebug()<<"修改操作成功!";
        queryTable();
    }
}
//排序查询
void StudentDialog::on_sortButton_clicked()
{
    //获取排序列名
    QString value = ui->valueComboBox->currentText();
    //获取排序方式
    QString condition;
    if(ui->condComboBox->currentIndex() == 0){
        condition = "ASC";//降序
    }else{
        condition = "DESC";//升序
    }
    QString str = QString("SELECT * FROM student ORDER BY %1 %2").arg(value).arg(condition);

    model.setQuery(str);
    ui->tableView->setModel(&model);
}

//创建数据库
void StudentDialog::createDB(){
    //添加数据库驱动
    db = QSqlDatabase::addDatabase("QSQLITE");
    //设置数据库名字(文件名)
    db.setDatabaseName("student.db");
    //打开数据库
    if(db.open()==true){
        qDebug()<<"创建/打开数据库成功!";
    }else{
        qDebug()<<"创建/打开数据库失败!";
    }
    //

}
//创建数据表
void StudentDialog::createTable(){
    QSqlQuery query;
    QString str= QString("CREATE TABLE student ("
                         "id INT PRIMARY KEY NOT NULL,"
                         "name TEXT NOT NULL,"
                         "score REAL NOT NULL)");
    if(query.exec(str)==false){
        qDebug()<<str;
    }else{
        qDebug()<<"创建数据表成功!";
    }
}
//查询
void StudentDialog::queryTable(){
    QString str = QString("SELECT * FROM student");
    model.setQuery(str);
    ui->tableView->setModel(&model);
}
