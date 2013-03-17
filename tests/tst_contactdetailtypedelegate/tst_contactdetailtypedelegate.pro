QT += core gui testlib
CONFIG += testcase

TARGET = tst_contactdetailtypedelegate
TEMPLATE = app
DESTDIR = bin
MOC_DIR = build
LIBS += -lqontacts -L../../src/lib
PRE_TARGETDEPS = ../../src/lib/libqontacts.a

SOURCES += tst_contactdetailtypedelegate.cpp
