CC=gcc
CFLAGS=-I. -std=c99
OBJ=vsftool.o
DEPS=

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

vsftool: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
