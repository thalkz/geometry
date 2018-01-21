#-------------------------------------------------
#
# Project created by QtCreator 2013-09-12T03:27:41
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Cube
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gldisplay.cpp \
    mesh.cpp

HEADERS  += mainwindow.h \
    gldisplay.h \
    mesh.h

FORMS    += mainwindow.ui

RESOURCES +=
