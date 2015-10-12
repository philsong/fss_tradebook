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
	       trade.cpp\
	       database.cpp\
	       tradebook.cpp

HEADERS  += gui.h\
			trade.h\
			database.h\
			tradebook.h
