gcc -pthread -o main main.c comn_sockets.c
#gnome-terminal -e "bash -c \"vlc udp://@:10000; exec bash\""
./main 1234 127.0.0.1 $(ls /dev/video*)
