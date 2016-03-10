gcc -pthread -o main main.c comn_sockets.c
#gnome-terminal -e "bash -c \"vlc udp://@:10000; exec bash\""
./main 1235 $(ls /dev/video*)
