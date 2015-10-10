#-------------------------------------------------
#
# Makefile Generator
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tradebook
TEMPLATE = app

CONFIG += c++11
QMAKE_CLEAN += ${TARGET} Makefile 

SOURCES += main.cpp\
        gui.cpp

HEADERS  += gui.h
