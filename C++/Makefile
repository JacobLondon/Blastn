CC=g++

TARGET=blastn.out
# dependency order
TYPESF=types
SMTHWF=smith_waterman
SPLITF=split
PREPAREF=prepare
MATCHF=match
MAINF=main

OBJS=$(TYPESF).o \
	$(SMTHWF).o $(SPLITF).o \
	$(PREPAREF).o $(MATCHF).o \
	$(MAINF).o

%.o: %.cpp
	$(CC) -c $< -o $@
all: $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)
	rm $(OBJS)
clean:
	rm $(TARGET)