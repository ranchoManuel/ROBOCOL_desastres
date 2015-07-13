CC_GAL= i586-poky-linux-uclibc-gcc
CC_RPi=gcc
CFLAGS=-I../

ODIR = ./obj
CDIR=..
HDIR=..

_OBJ= command.o robocol_list.o robocol_queue.o uart.o

OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

all: driver

driver: $(CDIR)/driver.c $(OBJ)
	$(CC_RPi) $^ -o $(ODIR)/driver.o -lm

$(ODIR)/%.o: $(CDIR)/%.c $(HDIR)/%.h
	$(CC_RPi) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm $(ODIR)/*.o
