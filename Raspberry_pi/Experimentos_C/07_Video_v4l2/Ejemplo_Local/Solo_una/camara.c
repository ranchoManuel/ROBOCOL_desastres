#include "camara.h"
#include <stdlib.h>				//1
#include <stdio.h>				//1
#include <fcntl.h>				//1
#include <linux/videodev2.h>	//1
#include <string.h>				//memset
#include <sys/mman.h>
#include "main.h"

int camara_fd, type, continuar;
struct v4l2_format format;
struct v4l2_buffer bufferinfo;
char *buffer_start;

pthread_t tcamara;

//Get a frame
void* tomarCamara()
{
	while(continuar)
	{
		//8.1) Put the buffer in the incoming queue.
		if(ioctl(camara_fd, VIDIOC_QBUF, &bufferinfo) < 0) closeWithError("VIDIOC_QBUF");

		//8.2) The buffer's waiting in the outgoing queue.
		if(ioctl(camara_fd, VIDIOC_DQBUF, &bufferinfo) < 0) closeWithError("VIDIOC_QBUF");

		pintar_pantalla_paso1(buffer_start, bufferinfo.length);
	}

	puts("Paro el Thread");
	pthread_exit(NULL);
}

void init_camaras(int cantPuertos, int argc, char* argv[])
{
	//Estos son para el Thread de la camara
	int err, i;
	char errMsj[1024];//posible mensaje de error

	//for(i=cantPuertos+1; i<argc; i++)
	{
		//1) Open a descriptor to the device. This is done UNIX-style, basic I/O.
		//camara_fds[i-(cantPuertos+1)]
		camara_fd = open(argv[2], O_RDWR);
		if(camara_fd == -1) closeWithError("Unable to open camera");
		puts("1) camera open");

		//2) Retrieve the device’s capabilities
		struct v4l2_capability cap;
		if(ioctl(camara_fd, VIDIOC_QUERYCAP, &cap) < 0) closeWithError("VIDIOC_QUERYCAP");
		puts("2) The v4l2_capability structure if filled with information about the device");
		// http://linuxtv.org/downloads/v4l-dvb-apis/vidioc-querycap.html#device-capabilities

		if(!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))
			closeWithError("The device does not handle single-planar video capture.");

		//3) Set our video format
		//To see a list with all available formats in your device:
		//v4l2-ctl -d /dev/video0 --list-formats-ext
		//chose MJPEG because it is extremely easy to display using the SDL
		format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		format.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
		format.fmt.pix.width = 640;
		format.fmt.pix.height = 480;
		if(ioctl(camara_fd, VIDIOC_S_FMT, &format) < 0) closeWithError("VIDIOC_S_FMT");

		//4) Inform the device about your future buffers
		//we’ll use a single buffer, and map our memory using mmap.
		//All this information is sent using the VIDIOC_REQBUFS call and a v4l2_requestbuffers structure:
		struct v4l2_requestbuffers bufrequest;
		bufrequest.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		bufrequest.memory = V4L2_MEMORY_MMAP; //Hay mas opciones: http://linuxtv.org/downloads/v4l-dvb-apis/buffer.html#v4l2-memory
		bufrequest.count = 1;
		if(ioctl(camara_fd, VIDIOC_REQBUFS, &bufrequest) < 0) closeWithError("VIDIOC_REQBUFS");

		//5) Allocate your buffers
		memset(&bufferinfo, 0, sizeof(bufferinfo));
		bufferinfo.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		bufferinfo.memory = V4L2_MEMORY_MMAP;
		bufferinfo.index = 0;
		if(ioctl(camara_fd, VIDIOC_QUERYBUF, &bufferinfo) < 0) closeWithError("VIDIOC_QUERYBUF");

		//Here again, think about cleaning up the area.
		//Your frame is going to be stored in there, you don’t want garbage messing around.
		buffer_start = mmap(NULL, bufferinfo.length, PROT_READ | PROT_WRITE, MAP_SHARED, camara_fd, bufferinfo.m.offset);
		if(buffer_start == MAP_FAILED) closeWithError("mmap");
		memset(buffer_start, 0, bufferinfo.length);

		//7) Activate streaming
		type = bufferinfo.type;
		if(ioctl(camara_fd, VIDIOC_STREAMON, &type) < 0) closeWithError("VIDIOC_STREAMON");
	}

	//Aqui se crea el thread de lectura
	continuar=true;
	err = pthread_create(&(tcamara), NULL, &tomarCamara, NULL);
  if(err != 0)
  {
		sprintf(errMsj,"Can't create thread:[%s]", strerror(err));
		closeWithError(errMsj);
  }
  else printf("Thread created successfully\n");
  printf(KCYN"___________________________\n"RESET);
}

void close_camara()
{
	continuar=false;
	//9) Deactivate streaming
	if(ioctl(camara_fd, VIDIOC_STREAMOFF, &type) < 0) closeWithError("VIDIOC_STREAMOFF");
	memset(buffer_start, 0, bufferinfo.length);
	memset(&bufferinfo, 0, sizeof(bufferinfo));
	memset(&format, 0, sizeof(format));

  	close(camara_fd);
	puts("Cerro todo");
}
