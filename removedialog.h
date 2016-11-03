#ifndef REMOVEDIALOG_H
#define REMOVEDIALOG_H

#include <QDialog>

class QPushButton;
class QLineEdit;
class QGridLayout;

class RemoveDialog : public QDialog
{
    Q_OBJECT
public:
    RemoveDialog(QWidget *parent = 0);
signals:
    getDeleteRow(int);
public slots:
    void sendRow();
private:
    QPushButton *OK;
    QPushButton *cancel;
    QLineEdit *editer;
    QGridLayout *All;
};

#endif // REMOVEDIALOG_H
