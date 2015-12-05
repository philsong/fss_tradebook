#-------------------------------------------------
#
# Makefile Generator
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tradebook
TEMPLATE = app

CONFIG += c++11
LIBS += -lpqxx -lpq
QMAKE_CLEAN += ${TARGET} Makefile

OBJECTS_DIR = generated_files
MOC_DIR = generated_files

SOURCES += src/main.cpp\
	       src/gui.cpp\
	       src/trade.cpp\
	       src/database.cpp\
	       src/tradebook.cpp\
		   src/contract.cpp

HEADERS  += src/gui.hpp\
			src/trade.hpp\
			src/database.hpp\
			src/tradebook.hpp\
			src/contract.hpp
