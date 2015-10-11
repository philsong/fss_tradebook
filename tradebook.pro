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
LIBS += -lpqxx -lpq
QMAKE_CLEAN += ${TARGET} Makefile 

SOURCES += main.cpp\
	       gui.cpp\
	       database.cpp\

HEADERS  += gui.h\
			database.h\
