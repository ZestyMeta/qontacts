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
    contactdetailview.cpp \
    contactdetailtypedelegate.cpp \
    contactlist.cpp
HEADERS  += mainwindow.h \
    contactdetailview.h \
    contactdetailtypedelegate.h \
    contactlist.h
FORMS    += mainwindow.ui \
    contactlist.ui
