CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS =

TARGET = appclication

OBJFILES = main.o utils.o ListTextASCII.o HashTable.o HashFunction.o Set.o BPE.o utf8Coder.o


all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJFILES) $(TARGET)

rebuild: clean all
