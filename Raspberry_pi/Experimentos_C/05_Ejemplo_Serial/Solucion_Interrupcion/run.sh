gcc -o MonitorSerial main.c comn_serial.c
./MonitorSerial /dev/ttyACM1 9600

#Tavera tenia la siguiente configuracion para la comunicacion en una raspberry:
#./MonitorSerial /dev/ttyAMA0 115200
