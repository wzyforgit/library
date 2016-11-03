#include "mainwindow.h"
#include "common.h"
#include "adddialog.h"
#include "removedialog.h"
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QErrorMessage>
#include <QtSql>
#include <windows.h>

void MainWindow::readData()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QObject::tr("library.db"));

    if(!db.open())
    {
        errorBox->showMessage(tr("can not open database"));
    }
    else
    {
        QSqlQuery query;
        query.exec("SELECT * FROM books");
        if(!query.isActive())
        {
            errorBox->showMessage(tr("Inquire fail\nMaybe nothing in this database"));
        }
        else
        {
            while(query.next())
            {
                BookBase bookInfo;
                for(int i=0;i<bookInfo.indexNum;++i)
                {
                    bookInfo.infos[i]=query.value(i).toString();
                }
                addTableLine(bookInfo);
            }
        }
    }
}

void MainWindow::saveData()
{
    QSqlQuery query;
    query.exec("SELECT * FROM books");
    if(query.isActive())
    {
        query.exec("DROP TABLE books");
    }
    query.exec("CREATE TABLE books"
               "(book CHAR(30) NOT NULL,"
               "writer CHAR(30) NOT NULL,"
               "ISBN CHAR(30) NOT NULL,"
               "info text NOT NULL,"
               "PRIMARY KEY (ISBN));");
    for(int i=0;i<table->rowCount();++i)
    {
        QString insertString("INSERT INTO books VALUES(");
        for(int j=0;;++j)
        {
            insertString+='\"';
            insertString+=table->item(i,j)->text();
            if(j==table->columnCount()-1)
            {
                insertString+="\"";
                break;
            }
            else
            {
                insertString+="\",";
            }
        }
        insertString+=")";
        query.exec(insertString);
    }
    close();
}

void MainWindow::createButton()
{
    addLine=new QPushButton(tr("Add"));
    removeLine=new QPushButton(tr("Remove"));
    quit=new QPushButton(tr("Quit&&Save"));
    addDialog=new AddDialog(this);
    addDialog->setModal(true);
    removeDialog=new RemoveDialog(this);
    removeDialog->setModal(true);

    pushButtonLayout=new QVBoxLayout;
    pushButtonLayout->addWidget(addLine);
    pushButtonLayout->addWidget(removeLine);
    pushButtonLayout->addWidget(quit);
    pushButtonLayout->addStretch();

    connect(quit,SIGNAL(clicked()),this,SLOT(saveData()));

    connect(addLine,SIGNAL(clicked()),addDialog,SLOT(show()));
    connect(addDialog,SIGNAL(getNewBook(BookBase&)),this,SLOT(addTableLine(BookBase&)));

    connect(removeLine,SIGNAL(clicked()),removeDialog,SLOT(show()));
    connect(removeDialog,SIGNAL(getDeleteRow(int)),this,SLOT(removeRow(int)));

    setStyleSheet("QPushButton { color: black; background-color: skyblue }");
}

void MainWindow::removeRow(int row)
{
    table->removeRow(row-1);
}

void MainWindow::addTableLine(BookBase &bookInfo)
{
    table->setRowCount(table->rowCount()+1);
    QTableWidgetItem *tableInfo[4];
    for(int i=0;i<4;++i)
    {
        tableInfo[i]=new QTableWidgetItem;
    }
    for(int i=0;i<bookInfo.indexNum;++i)
    {
        tableInfo[i]->setText(bookInfo.infos[i]);
    }
    for(int i=0;i<4;++i)
    {
        table->setItem(table->rowCount()-1,i,tableInfo[i]);
    }
}

void MainWindow::createTable()
{
    //新建x行x列的表格
    table = new QTableWidget(0,4);

    //设置表格列标题
    QStringList headerLabels;
    headerLabels << "Book" << "Writer" << "ISBN" << "More Information";
    table->setHorizontalHeaderLabels(headerLabels);

    //设置表格行标题的对齐方式
    table->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);

    //自动调整最后一列的宽度使它和表格的右边界对齐
    table->horizontalHeader()->setStretchLastSection(true);

    //设置表格的选择方式
    table->setSelectionBehavior(QAbstractItemView::SelectItems);

    //设置编辑方式
    table->setEditTriggers(QAbstractItemView::DoubleClicked);

    //设置表格样式
    table->setFrameStyle(1);
    table->setStyleSheet("selection-background-color:lightblue;");
    table->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    errorBox=new QErrorMessage;
    errorBox->setWindowTitle(tr("Error"));
    errorBox->setModal(true);

    createTable();
    readData();
    createButton();
    auto All=new QHBoxLayout;
    All->addLayout(pushButtonLayout);
    All->addWidget(table);

    auto center=new QWidget(this);
    center->setLayout(All);
    setCentralWidget(center);
    resize(640,320);
    setWindowTitle(tr("Book Manager (By Tom Wang(version 0.1))"));
    setWindowFlags(Qt::WindowMinimizeButtonHint|Qt::WindowMaximizeButtonHint);
}

MainWindow::~MainWindow()
{
}
