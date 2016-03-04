#Este es un ejemplo de uso para streaming udp
# -i /dev/video0 == Es la fuente del video
# -s 640x480 == Tamanio del video
# -r 10 == 10 fps
# -fflags nobuffer -an == Que no haya buffer y que no transmita sonido
# -f mpegts udp://<ipDestino>:<puertoDestino> == A donde voy a enviar el video
ffmpeg -i /dev/video0 -s 640x480 -pix_fmt yuv420p -r 10 -fflags nobuffer -an -f mpegts udp://127.0.0.1:10000

#Para consumir este servicio en vlc poner en una terminal
#vlc udp://@:10000 
#O entrar a vlc buscar donde dice abrir desde red y poner
#udp://@:10000 

