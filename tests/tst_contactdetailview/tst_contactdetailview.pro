QT += core gui testlib
CONFIG += testcase

TARGET = tst_contactdetailview
TEMPLATE = app
DESTDIR = bin
MOC_DIR = build
LIBS += -lqontacts -L../../src/lib
PRE_TARGETDEPS = ../../src/lib/libqontacts.a

SOURCES += tst_contactdetailview.cpp
