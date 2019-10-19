TARGET=blastn
CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -Os -ggdb
OBJ_FILES=lib/blastn.o lib/dust.o lib/extend.o lib/match.o lib/output.o \
		 lib/pairs.o lib/prepare.o lib/smith_waterman.o lib/sort.o lib/split.o \
		 structures/hash_table.o structures/memory.o structures/vector.o \
		 util/globals.o util/test.o util/types.o util/util.o \
		 main.o

.PHONY: clean

$(TARGET) : $(OBJ_FILES)
	$(CC) -o $(TARGET) $(OBJ_FILES) $(CFLAGS)

clean:
	rm -rf $(TARGET) $(OBJ_FILES)
