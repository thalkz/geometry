#-------------------------------------------------
#
# Project created by QtCreator 2013-09-12T03:27:41
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Topology
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gldisplay.cpp \
    mesh.cpp \
    triangle.cpp \
    vertrex.cpp

HEADERS  += mainwindow.h \
    gldisplay.h \
    mesh.h \
    triangle.h \
    vertrex.h

FORMS    += mainwindow.ui
