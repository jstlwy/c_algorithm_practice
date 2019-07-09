CC = gcc
CFLAGS = -Wall -Werror -g
LDFLAGS = -lncurses
OBJFILES = input.o utils.o arraysort.o linklist.o listsort.o unionfind.o main.o
TARGET = test

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET)
