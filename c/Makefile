CC=gcc
TARGET=blastn

SPLIT=lib/split.c
MAP=tools/map.c
STRING=tools/string.c
TYPES=tools/types.c
VECTOR=tools/vector.c
GLOBALS=util/globals.c
MAIN=main.c

FILES= $(SPLIT) \
	$(TYPES) $(STRING) $(VECTOR) $(MAP) $(GLOBALS) \
	$(MAIN)

.PHONY: all clean

all:
	$(CC) -o $(TARGET) $(FILES)
clean:
	rm $(TARGET) core
