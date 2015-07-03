all: uartTest.rpi
uartTest.rpi: uartTest.c
	gcc uartTest.c -o uartTest.rpi

test1: uart_robocol.h uart_robocol.c uart_test.c
	gcc uart_robocol.c uart_test.c -o test1.rpi

test2: uart_robocol.h uart_robocol.c uart_test2.c
	gcc uart_robocol.c uart_test2.c -o test2.rpi

.PHONY: clean
clean:
	rm -f ./*.rpi
