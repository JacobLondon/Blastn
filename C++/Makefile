CC=g++

TARGET=blastn
# dependency order
TYPESF=types
SMTHWF=smith_waterman
SPLITF=split
PREPAREF=prepare
DUSTF=dust
MATCHF=match
EXTENDF=extend
MAINF=main

OBJS=$(TYPESF).o \
	$(SMTHWF).o $(SPLITF).o \
	$(PREPAREF).o $(DUSTF).o $(MATCHF).o $(EXTENDF).o \
	$(MAINF).o

%.o: %.cpp
	$(CC) -c $< -o $@
all: $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)
	rm $(OBJS)
clean:
	rm $(TARGET) $(OBJS) core