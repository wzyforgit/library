#include "removedialog.h"
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QRegExpValidator>

void RemoveDialog::sendRow()
{
    if(!editer->text().isEmpty())
    {
        emit getDeleteRow(editer->text().toInt());
        editer->clear();
        close();
    }
    else
    {
        ;
    }
}

RemoveDialog::RemoveDialog(QWidget *parent) : QDialog(parent)
{
    OK=new QPushButton("OK");
    cancel=new QPushButton("Cancel");
    editer=new QLineEdit;
    All=new QGridLayout;

    editer->setPlaceholderText("Enter the number of row");
    QRegExp regExp("([1-9])|([1-9][0-9]+)");
    editer->setValidator(new QRegExpValidator(regExp,this));
    editer->setFocus();

    connect(OK,SIGNAL(clicked()),this,SLOT(sendRow()));
    connect(cancel,SIGNAL(clicked()),this,SLOT(close()));

    All->addWidget(editer,0,0,1,2);
    All->addWidget(OK,1,0,1,1);
    All->addWidget(cancel,1,1,1,1);

    setWindowTitle(tr("Remove"));
    setFixedSize(180,105);
    setLayout(All);
}
