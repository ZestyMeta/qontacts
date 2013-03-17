QT += core gui testlib widgets
CONFIG += testcase

TARGET = tst_mainwindow
TEMPLATE = app
DESTDIR = bin
MOC_DIR = build
LIBS += -lqontacts -L../../src/lib
PRE_TARGETDEPS = ../../src/lib/libqontacts.a
INCLUDEPATH += ../../src/

SOURCES += tst_mainwindow.cpp
