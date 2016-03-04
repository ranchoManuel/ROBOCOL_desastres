#include "camara.h"
#include <stdlib.h>				//1
#include <stdio.h>				//1
#include <fcntl.h>				//1
#include <linux/videodev2.h>	//1
#include <string.h>				//memset
#include <sys/mman.h>
#include "main.h"

#define MAX_CAMERA 10

int camara_fd[MAX_CAMERA], type, continuar, cantCamaras, selectedCamera;
struct v4l2_format format;
struct v4l2_buffer bufferinfo[MAX_CAMERA];
char* buffer_start[MAX_CAMERA];

pthread_t tcamara;

void* tomarCamara()
{
	usleep(1000); //dejar pasar una decima de segundo para que inicialize la pantalla
	while(continuar)
	{
		//8.1) Put the buffer in the incoming queue.
		if(ioctl(camara_fd[selectedCamera], VIDIOC_QBUF, &bufferinfo[selectedCamera]) < 0) closeWithError("[Camaras]\tVIDIOC_QBUF");

		//8.2) The buffer's waiting in the outgoing queue.
		if(ioctl(camara_fd[selectedCamera], VIDIOC_DQBUF, &bufferinfo[selectedCamera]) < 0) closeWithError("[Camaras]\tVIDIOC_QBUF");

		pintar_pantalla_paso1(buffer_start[selectedCamera], bufferinfo[selectedCamera].length);
	}

	puts("[Camaras]\tParo el Thread");
	pthread_exit(NULL);
}

void init_camaras(int cantPuertos, int argc, char* argv[])
{
	//En estos se crean las estructuras de datos que guardan la informacion de todas las camaras
	cantCamaras=argc-(cantPuertos+1);
	selectedCamera=0;
	if(cantCamaras > MAX_CAMERA) closeWithError("[Camaras]\tSe necesita que MAX_CAMERA sea mayor a su valor actual");
	printf("[Camaras]\tCantidad de camaras = %d\n", cantCamaras);

	//Estos son para el Thread de la camara
	int err, i, esta;
	char errMsj[1024];//posible mensaje de error

	struct v4l2_capability cap;

	//Estructura usada en el paso 3, es una variable global para poder usarla en el main
	format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	format.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
	format.fmt.pix.width = 640;
	format.fmt.pix.height = 480;

	//Estructura usada en el paso 4
	struct v4l2_requestbuffers bufrequest;
	bufrequest.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	bufrequest.memory = V4L2_MEMORY_MMAP; //Hay mas opciones: http://linuxtv.org/downloads/v4l-dvb-apis/buffer.html#v4l2-memory
	bufrequest.count = 1;

	for(i=cantPuertos+1; i<argc; i++)
	{
		esta=i-(cantPuertos+1);
		printf("[Camaras]\tIndexCAM = %d\n",esta);
		//1) Open a descriptor to the device. This is done UNIX-style, basic I/O.
		camara_fd[esta] = open(argv[i], O_RDWR);
		if(camara_fd[esta] == -1)
		{
			sprintf(errMsj,"[Camaras]\tUnable to open camera:[%s]", argv[i]);
			closeWithError(errMsj);
		}
		printf("[Camaras]\t1) camera open: %s\n", argv[i]);

		//2) Retrieve the device’s capabilities
		if(ioctl(camara_fd[esta], VIDIOC_QUERYCAP, &cap) < 0)
		{
			sprintf(errMsj,"[Camaras]\tVIDIOC_QUERYCAP:[%s]", argv[i]);
			closeWithError(errMsj);
		}
		printf("[Camaras]\t2) The v4l2_capability structure if filled with information about the device: %s\n", argv[i]);
		// http://linuxtv.org/downloads/v4l-dvb-apis/vidioc-querycap.html#device-capabilities

		//3) Check the device’s capabilities
		if(!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))
		{
			sprintf(errMsj,"[Camaras]\tThe device %s does not handle single-planar video capture.", argv[i]);
			closeWithError(errMsj);
		}
		printf("[Camaras]\t3) The device %s can handle single-planar video capture.\n", argv[i]);

		//4) Set our video format
		//To see a list with all available formats in your device:
		//v4l2-ctl -d /dev/video0 --list-formats-ext
		//chose MJPEG because it is extremely easy to display using the SDL
		if(ioctl(camara_fd[esta], VIDIOC_S_FMT, &format) < 0)
		{
			sprintf(errMsj,"[Camaras]\tVIDIOC_S_FMT:[%s]", argv[i]);
			closeWithError(errMsj);
		}
		printf("[Camaras]\t4) video format ok: %s\n", argv[i]);

		//5) Inform the device about your future buffers
		//we’ll use a single buffer, and map our memory using mmap.
		//All this information is sent using the VIDIOC_REQBUFS call and a v4l2_requestbuffers structure:
		if(ioctl(camara_fd[esta], VIDIOC_REQBUFS, &bufrequest) < 0) closeWithError("[Camaras]\tVIDIOC_REQBUFS");
		printf("[Camaras]\t5) video REQBUFS ok: %s\n", argv[i]);

		//6) Allocate your buffers
		memset(&bufferinfo[esta], 0, sizeof(bufferinfo[esta]));
		bufferinfo[esta].type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		bufferinfo[esta].index = 0;
		bufferinfo[esta].memory = V4L2_MEMORY_MMAP;
		if(ioctl(camara_fd[esta], VIDIOC_QUERYBUF, &bufferinfo[esta]) < 0) closeWithError("[Camaras]\tVIDIOC_QUERYBUF");
		printf("[Camaras]\t6) video QUERYBUF ok: %s\n", argv[i]);

		//7) Here again, think about cleaning up the area.
		//Your frame is going to be stored in there, you don’t want garbage messing around.
		buffer_start[esta] = mmap( NULL, bufferinfo[esta].length, PROT_READ | PROT_WRITE, MAP_SHARED, camara_fd[esta], bufferinfo[esta].m.offset);
		if(buffer_start[esta] == MAP_FAILED) closeWithError("[Camaras]\tmmap");
		printf("[Camaras]\t7) mmap ok: %s\n", argv[i]);
		memset(buffer_start[esta], 0, bufferinfo[esta].length);

		//8) Activate streaming
		type = bufferinfo[esta].type;
		if(ioctl(camara_fd[esta], VIDIOC_STREAMON, &type) < 0) closeWithError("[Camaras]\tVIDIOC_STREAMON");
		printf("[Camaras]\t8) video STREAMON ok: %s\n", argv[i]);
	}

	//Aqui se crea el thread de lectura
	continuar=true;
	err = pthread_create(&(tcamara), NULL, &tomarCamara, NULL);
	if(err != 0)
	{
		sprintf(errMsj,"[Camaras]\tCan't create thread:[%s]", strerror(err));
		closeWithError(errMsj);
	}
	else printf("[Camaras]\tThread created successfully\n");
	printf(KCYN"___________________________\n"RESET);
}

void close_camaras()
{
	continuar=false;
	//9) Deactivate streaming
	usleep(100); //Algo de tiempo para que pare el thread

	int i;
	for(i=0; i<cantCamaras; i++) close(camara_fd[i]);
	puts("[Camaras]\tCerro todo");
}

void next_camera()
{selectedCamera=(selectedCamera+1)%cantCamaras;}

void prev_camera()
{selectedCamera=(selectedCamera-1 < 0)?cantCamaras-1: selectedCamera-1;}
