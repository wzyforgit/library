#-------------------------------------------------
#
# Project created by QtCreator 2016-11-01T10:38:47
#
#-------------------------------------------------

QT       += core gui \
            sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tableDisplay
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    adddialog.cpp \
    removedialog.cpp

HEADERS  += mainwindow.h \
    adddialog.h \
    common.h \
    removedialog.h
