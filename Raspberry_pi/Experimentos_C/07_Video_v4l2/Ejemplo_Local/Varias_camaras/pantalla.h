#ifndef PANTALLA_H
#define PANTALLA_H

#include <linux/videodev2.h>

void init_pantalla(struct v4l2_format format);

void pintar_pantalla_paso2(void* buffer, int tamBuffer);

void close_pantalla();

#endif
