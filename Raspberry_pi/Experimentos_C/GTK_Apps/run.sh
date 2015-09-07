gcc -o Main app.c `pkg-config --libs gtk+-3.0` `pkg-config --cflags gtk+-3.0`
./Main
