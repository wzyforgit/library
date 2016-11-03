#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include "common.h"

class QLabel;
class QLineEdit;
class QPushButton;
class QGridLayout;
class QHBoxLayout;

class AddDialog : public QDialog
{
    Q_OBJECT
public:
    AddDialog(QWidget *parent = 0);

signals:
    getNewBook(BookBase &);

public slots:
    void emitInfo();

private:
    void createEdit();
    void createButton();

    QLabel *book;
    QLabel *writer;
    QLabel *ISBN;
    QLabel *info;

    QLineEdit *bookLine;
    QLineEdit *writerLine;
    QLineEdit *ISBNLine;
    QLineEdit *infoLine;

    QPushButton *OK;
    QPushButton *cancel;

    QGridLayout *mainLayout;
};

#endif // ADDDIALOG_H
