CC= i586-poky-linux-uclibc-gcc
CFLAGS=-I../

ODIR = ./obj
CDIR=..
HDIR=..

_OBJ= command.o robocol_list.o robocol_queue.o

OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

all: driver

driver: $(CDIR)/driver.c $(OBJ)
	$(CC) $^ -o $(ODIR)/driver.o -lm

$(ODIR)/%.o: $(CDIR)/%.c $(HDIR)/%.h
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm $(ODIR)/*.o
