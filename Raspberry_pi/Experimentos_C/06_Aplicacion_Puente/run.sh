
gcc -pthread -o appPuente main.c comn_sockets.c comn_serial.c
gnome-terminal -e "bash -c \"./appPuente 1234 /dev/ttyACM0 9600; exec bash\""
gnome-terminal -e "bash -c \"./chatClient 127.0.0.1 1234; exec bash\""
