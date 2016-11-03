#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "common.h"

class QPushButton;
class QVBoxLayout;
class QHBoxLayout;
class QTableWidget;
class AddDialog;
class RemoveDialog;
class QErrorMessage;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void addTableLine(BookBase &bookInfo);
    void removeRow(int row);
    void saveData();

private:
    void readData();

    void createButton();
    QPushButton *addLine;
    QPushButton *removeLine;
    QPushButton *quit;
    QVBoxLayout *pushButtonLayout;

    void createTable();
    QTableWidget *table;

    AddDialog *addDialog;
    RemoveDialog *removeDialog;
    QErrorMessage *errorBox;
};

#endif // MAINWINDOW_H
