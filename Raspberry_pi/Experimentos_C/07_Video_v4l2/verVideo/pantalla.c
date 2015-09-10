#include "pantalla.h"
#include "SDL.h"
#include "SDL_image.h"

SDL_Surface* screen;
SDL_RWops* buffer_stream;
SDL_Surface* frame;
SDL_Rect position = {.x = 0, .y = 0};

void init_pantalla(struct v4l2_format format)
{
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_JPG);	
	
	// Get the screen's surface.
	screen = SDL_SetVideoMode(
			format.fmt.pix.width,
			format.fmt.pix.height,
			32, SDL_HWSURFACE
	);
}

void pintar_pantalla_paso2(void* buffer, int tamBuffer)
{
	// Create a stream based on our buffer.
	buffer_stream = SDL_RWFromMem(buffer, tamBuffer);

	// Create a surface using the data coming out of the above stream.
	SDL_FreeSurface(frame);
	frame = IMG_Load_RW(buffer_stream, 0);

	// Blit the surface and flip the screen.
	SDL_BlitSurface(frame, NULL, screen, &position);
	SDL_Flip(screen);
}

void close_pantalla()
{
	SDL_FreeSurface(frame);
	SDL_RWclose(buffer_stream);
	IMG_Quit();
	SDL_Quit();
}
