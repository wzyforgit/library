#include "adddialog.h"
#include "common.h"
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>

void AddDialog::createEdit()
{
    book=new QLabel(tr("Book:"));
    writer=new QLabel(tr("Writer:"));
    ISBN=new QLabel(tr("ISBN:"));
    info=new QLabel(tr("More Infomation:"));

    bookLine=new QLineEdit;
    writerLine=new QLineEdit;
    ISBNLine=new QLineEdit;
    infoLine=new QLineEdit;

    bookLine->setFocus();

    mainLayout->addWidget(book,0,0);
    mainLayout->addWidget(bookLine,0,1);
    mainLayout->addWidget(writer,1,0);
    mainLayout->addWidget(writerLine,1,1);
    mainLayout->addWidget(ISBN,2,0);
    mainLayout->addWidget(ISBNLine,2,1);
    mainLayout->addWidget(info,3,0);
    mainLayout->addWidget(infoLine,3,1);
}

void AddDialog::createButton()
{
    OK=new QPushButton(tr("OK"));
    cancel=new QPushButton(tr("Cancel"));
    mainLayout->addWidget(OK,4,0);
    mainLayout->addWidget(cancel,4,1);

    connect(cancel,SIGNAL(clicked()),this,SLOT(close()));
    connect(OK,SIGNAL(clicked()),this,SLOT(emitInfo()));
}

void AddDialog::emitInfo()
{
    BookBase bookEmit;
    bookEmit.infos[0]=bookLine->text();
    bookEmit.infos[1]=writerLine->text();
    bookEmit.infos[2]=ISBNLine->text();
    bookEmit.infos[3]=infoLine->text();
    emit getNewBook(bookEmit);
    bookLine->clear();
    writerLine->clear();
    ISBNLine->clear();
    infoLine->clear();
    close();
}

AddDialog::AddDialog(QWidget *parent) : QDialog(parent)
{
    mainLayout=new QGridLayout;
    createEdit();
    createButton();
    setLayout(mainLayout);
    setWindowTitle(tr("Add"));
    setFixedSize(230,185);
}
