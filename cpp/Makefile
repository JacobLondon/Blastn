TARGET=blastn
CXX=g++
# C++ 17, Warnings, Optimizations
CXXFLAGS=-std=c++17 -Wall -Wextra -march=native -O3 -lm -lpthread -fopenmp -pipe
OBJ_FILES=lib/blastn.o lib/dust.o lib/hsp.o lib/match.o lib/output.o \
		  lib/pairs.o lib/prepare.o lib/sort.o lib/split.o \
		  lib/extend/extend.o lib/extend/interface.o lib/extend/smith_waterman.o \
		  util/display.o util/globals.o util/test.o util/types.o \
		  main.o

.PHONY: clean

$(TARGET) : $(OBJ_FILES)
	$(CXX) -o $(TARGET) $(OBJ_FILES) $(CXXFLAGS)

clean:
	rm -rf $(TARGET) $(OBJ_FILES)
