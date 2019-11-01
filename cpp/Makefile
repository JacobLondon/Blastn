TARGET=blastn
CXX=g++
# C++ 17, Warnings, Optimizations
CXXFLAGS=-std=c++17 -Wall -Wextra -O3 -lm -lpthread -fopenmp
OBJ_FILES=lib/blastn.o lib/dust.o lib/extend.o lib/hsp.o lib/interface.o \
		  lib/match.o lib/output.o lib/pairs.o lib/prepare.o \
		  lib/smith_waterman.o lib/sort.o lib/split.o \
		  util/display.o util/globals.o util/test.o util/types.o \
		  main.o

.PHONY: clean

$(TARGET) : $(OBJ_FILES)
	$(CXX) -o $(TARGET) $(OBJ_FILES) $(CXXFLAGS)

clean:
	rm -rf $(TARGET) $(OBJ_FILES)
