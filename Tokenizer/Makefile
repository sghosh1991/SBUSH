# I am a comment, and I want to say that the variable CC will be
# the compiler to use.
CC=gcc
# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.

CFLAGS=-g -c
all: hello

hello: shell.o parser.o stringTokenizer.o execute.o
	$(CC) shell.o parser.o stringTokenizer.o -lreadline -o hello

shell.o: shell.c
	$(CC) $(CFLAGS) shell.c 

parser.o: parser.c
	$(CC) $(CFLAGS) parser.c

stringTokenizer.o: stringTokenizer.c
	$(CC) $(CFLAGS) stringTokenizer.c

execute.o: execute.c
	$(CC) $(CFLAGS) execute.c

clean:
	rm -rf *o hello
