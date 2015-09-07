all: des
des: uartDesastres.c uart.c uart.h
	gcc uartDesastres.c uart.c -o des.rpi

.PHONY: clean
clean:
	rm -f ./*.rpi
