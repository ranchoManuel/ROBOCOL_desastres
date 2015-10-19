gcc -pthread -o camaraLocal main.c camara.c pantalla.c $(pkg-config --cflags --libs sdl SDL_image)
./camaraLocal 1234 $(ls /dev/video*)
#Para que no lo vaya a prender por accidente elimino el ejectuable
rm camaraLocal 
