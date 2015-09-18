#-------------------------------------------------
#
# Project created by QtCreator 2015-09-18T11:57:16
#
#-------------------------------------------------

QT       += core gui
QT += webkit webkitwidgets
CONFIG += qt

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = htmlpunk_new
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    CodeEditor.cpp \
    CodeHighlighter.cpp \
    LineNumberArea.cpp \
    TidyWorker.cpp

HEADERS  += MainWindow.h \
    CodeEditor.h \
    CodeHighlighter.h \
    LineNumberArea.h \
    TidyWorker.h

FORMS    += main.ui
LIBS += -ltidy
