#include <unistd.h>

int main(void)
{
  char *losArgs[] = { "ffmpeg", "-i", "/dev/video0", "-s", "640x480", "-pix_fmt", "yuv420p", "-r", "10", "-fflags", "nobuffer", "-an", "-f", "mpegts", "udp://127.0.0.1:10000", NULL };
  execvp(losArgs[0], execArgs);

  return 0;
}
