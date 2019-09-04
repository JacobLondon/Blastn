TARGET=blastn
CC=g++
CPPFLAGS=-std=c++17

TYPESF=util/types
SMTHWF=lib/smith_waterman
SPLITF=lib/split
PREPAREF=lib/prepare
DUSTF=lib/dust
MATCHF=lib/match
EXTENDF=lib/extend
TESTF=util/test
MAINF=main

FILES=$(TYPESF).cpp \
	$(SMTHWF).cpp $(SPLITF).cpp \
	$(PREPAREF).cpp $(DUSTF).cpp $(MATCHF).cpp $(EXTENDF).cpp \
	$(TESTF).cpp $(MAINF).cpp

.PHONY: all clean

all:
	$(CC) -o $(TARGET) $(FILES) $(CPPFLAGS)
clean:
	rm $(TARGET) $(OBJS) core
