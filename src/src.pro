QT += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qontacts
TEMPLATE = lib
CONFIG += staticlib
DESTDIR = lib
MOC_DIR = build
UI_DIR = build
RCC_DIR = build

SOURCES += mainwindow.cpp \
    contactlist.cpp \
    contactdetails.cpp
HEADERS  += mainwindow.h \
    contactlist.h \
    contactdetails.h
FORMS    += mainwindow.ui \
    contactlist.ui \
    contactdetails.ui
