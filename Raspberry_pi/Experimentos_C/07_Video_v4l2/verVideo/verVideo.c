#include "SDL/SDL.h"
#include "SDL_image.h"

int main( int argc, char* args[] )
{
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

  // Create a stream based on our buffer.
  buffer_stream = SDL_RWFromMem(buffer_start, bufferinfo.length);

  // Create a surface using the data coming out of the above stream.
  picture = IMG_Load_RW(buffer_stream);

  // Blit the surface and flip the screen.
  SDL_BlitSurface(picture, NULL, screen, &position);
  SDL_Flip(screen);

  // Free everything, and unload SDL & Co.
  SDL_FreeSurface(picture);
  SDL_RWclose(buffer_stream);
  IMG_Quit();
  SDL_Quit();

  return 0;
}
