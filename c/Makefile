TARGET=blastn
CC=gcc
CFLAGS=-ggdb -Wall -std=c11 -ICollections-C/src/include
OBJ_FILES=lib/dust.o lib/prepare.o lib/smith_waterman.o lib/split.o \
		 tools/map.o tools/string.o tools/types.o tools/vector.o \
		 util/globals.o util/test.o \
		 main.o

.PHONY: clean

$(TARGET) : $(OBJ_FILES)
	$(CC) -o $(TARGET) $(OBJ_FILES)

clean:
	rm -rf $(TARGET) $(OBJ_FILES)
