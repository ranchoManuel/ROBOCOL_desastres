#include <stdlib.h>			//1
#include <stdio.h>			//1
#include <fcntl.h>			//1
#include <linux/videodev2.h>	//1
#include <string.h>			//memset
#include <sys/mman.h>
#include <unistd.h>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core/utility.hpp"

#include "opencv2/highgui/highgui_c.h"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RESET "\033[0m"

using namespace std;
using namespace cv;

void closeWithError(char *error)
{
	char errMsj[1024];
	sprintf(errMsj, KRED"%s"RESET, error);
	perror(errMsj);
	exit(1);
}

int main(int argc, char** argv )
{
  if ( argc != 2 )
  {
    printf("usage: DisplayImage.out <Image_Path>\n");
    return -1;
  }

  Mat image = imread( argv[1], 1 );

  if(!image.data)
  {
    printf("No image data \n");
    return -1;
  }
  namedWindow("Display Image", CV_WINDOW_AUTOSIZE );

  for(int i = 0; i<1; i++)
  {
    puts(".");
    sleep(1);
    imshow("Display Image", image);
  }
  cvWaitKey(0);

  return 0;
}

/*
int main(void)
{
	//1) Open a descriptor to the device. This is done UNIX-style, basic I/O.
	int camara_fd = open("/dev/video0", O_RDWR);
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
	struct v4l2_format format;
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
	struct v4l2_buffer bufferinfo;
	memset(&bufferinfo, 0, sizeof(bufferinfo));

	bufferinfo.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	bufferinfo.memory = V4L2_MEMORY_MMAP;
	bufferinfo.index = 0;
	if(ioctl(camara_fd, VIDIOC_QUERYBUF, &bufferinfo) < 0) closeWithError("VIDIOC_QUERYBUF");

	//Here again, think about cleaning up the area.
	//Your frame is going to be stored in there, you don’t want garbage messing around.
	char* buffer_start = mmap
	(
		NULL,
		bufferinfo.length,
		PROT_READ | PROT_WRITE,
		MAP_SHARED,
		camara_fd,
		bufferinfo.m.offset
	);
	if(buffer_start == MAP_FAILED) closeWithError("mmap");
	memset(buffer_start, 0, bufferinfo.length);

	//6) Get a frame
	//------------------------en for -----------------------
	memset(&bufferinfo, 0, sizeof(bufferinfo));

	bufferinfo.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	bufferinfo.memory = V4L2_MEMORY_MMAP;
	bufferinfo.index = 0; /* Queueing buffer index 0. */

/*
	// Activate streaming
	int type = bufferinfo.type;
	if(ioctl(camara_fd, VIDIOC_STREAMON, &type) < 0) closeWithError("VIDIOC_STREAMON");

	//TODO QUITAR -----------------
	// Initialise everything.
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_JPG);

	// Get the screen's surface.
	SDL_Surface* screen = SDL_SetVideoMode(
			format.fmt.pix.width,
			format.fmt.pix.height,
			32, SDL_HWSURFACE
	);

	SDL_RWops* buffer_stream;
	SDL_Surface* frame;
	SDL_Rect position = {.x = 0, .y = 0};
	//---------------------------------------

	/* Here is where you typically start two loops:
	 * - One which runs for as long as you want to
	 *   capture frames (shoot the video).
	 * - One which iterates over your buffers everytime. */

/*
	int ix;
	for(ix=0; ix<100; ix++)
	{
		// Put the buffer in the incoming queue.
		if(ioctl(camara_fd, VIDIOC_QBUF, &bufferinfo) < 0) closeWithError("VIDIOC_QBUF");

		// The buffer's waiting in the outgoing queue.
		if(ioctl(camara_fd, VIDIOC_DQBUF, &bufferinfo) < 0) closeWithError("VIDIOC_QBUF");

		//TODO QUITAR -----------------
		// Create a stream based on our buffer.
		buffer_stream = SDL_RWFromMem(buffer_start, bufferinfo.length);

		// Create a surface using the data coming out of the above stream.
		frame = IMG_Load_RW(buffer_stream, 0);

		// Blit the surface and flip the screen.
		SDL_BlitSurface(frame, NULL, screen, &position);
		SDL_Flip(screen);
		printf("%d/100\n", ix);
	}

	// Free everything, and unload SDL & Co.
	SDL_FreeSurface(frame);
	SDL_RWclose(buffer_stream);
	IMG_Quit();
	SDL_Quit();
	//-----------------------------

	/* Your loops end here. */
/*
	// Deactivate streaming
	if(ioctl(camara_fd, VIDIOC_STREAMOFF, &type) < 0) closeWithError("VIDIOC_STREAMOFF");

  close(camara_fd);
	puts("Cerro todo");

  return EXIT_SUCCESS;
}
*/
