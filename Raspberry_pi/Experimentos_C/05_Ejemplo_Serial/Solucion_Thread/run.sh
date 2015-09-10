gcc -pthread -o MonitorSerial main.c comn_serial.c
./MonitorSerial /dev/ttyUSB0 115200

#Tavera tenia la siguiente configuracion para la comunicacion en una raspberry:
#./MonitorSerial /dev/ttyAMA0 115200
