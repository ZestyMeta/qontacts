QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qontacts
TEMPLATE = app
LIBS += -lqontacts -L../src/lib
DESTDIR = bin
MOC_DIR = build
UI_DIR = build
RCC_DIR = build

SOURCES += main.cpp
