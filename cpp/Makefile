TARGET=blastn
CC=g++
CPPFLAGS=-std=c++17

DUSTF=lib/dust
EXTENDF=lib/extend
MATCHF=lib/match
PREPAREF=lib/prepare
SMTHWF=lib/smith_waterman
SPLITF=lib/split

GLOBALSF=util/globals
TYPESF=util/types
TESTF=util/test

MAINF=main

FILES=$(TYPESF).cpp \
	$(SMTHWF).cpp $(SPLITF).cpp \
	$(PREPAREF).cpp $(DUSTF).cpp $(MATCHF).cpp $(EXTENDF).cpp \
	$(TESTF).cpp $(GLOBALSF).cpp \
	$(MAINF).cpp

.PHONY: all clean

all:
	$(CC) -o $(TARGET) $(FILES) $(CPPFLAGS)
clean:
	rm $(TARGET) $(OBJS) core
