TARGET=blastn
CXX=g++
CXXFLAGS=-std=c++17 -Wall -Wextra
OBJ_FILES=lib/dust.o lib/extend.o lib/match.o lib/pairs.o \
		  lib/prepare.o lib/smith_waterman.o lib/sort.o lib/split.o \
		  util/globals.o util/test.o util/types.o  \
		  main.o

.PHONY: clean

$(TARGET) : $(OBJ_FILES)
	$(CXX) -o $(TARGET) $(OBJ_FILES)

clean:
	rm -rf $(TARGET) $(OBJ_FILES)
