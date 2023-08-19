C = gcc
CFLAGS = -Wall 

all: scanner.x

scanner.x: scanner.o parser.o
		$(CC) $(CFLAGS) scanner.o parser.o -o scanner.x

scanner.o: scanner.c scanner.h parser.h
		$(CC) $(CFLAGS) -c scanner.c

parser.o: parser.c parser.h
		$(CC) $(CFLAGS) -c parser.c

clean:
	rm scanner.x
	rm scanner.o
	rm parser.o
