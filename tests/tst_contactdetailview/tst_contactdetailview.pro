QT += core gui testlib
CONFIG += testcase

TARGET = tst_contactdetailview
TEMPLATE = app
DESTDIR = bin
MOC_DIR = build
LIBS += -lqontacts -L../../src/lib

SOURCES += tst_contactdetailview.cpp
