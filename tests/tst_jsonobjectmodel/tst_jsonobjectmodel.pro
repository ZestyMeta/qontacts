QT += core gui testlib widgets
CONFIG += testcase

TARGET = tst_jsonobjectmodel
TEMPLATE = app
DESTDIR = bin
MOC_DIR = build
LIBS += -lqontacts -L../../src/lib
PRE_TARGETDEPS = ../../src/lib/libqontacts.a
INCLUDEPATH += ../../src/

SOURCES += tst_jsonobjectmodel.cpp
