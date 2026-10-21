#ifndef JOYSTICK_H
#define JOYSTICK_H
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/joystick.h>
#include <unistd.h>
#include <time.h>
typedef struct
{
 int x;
 int y;
 int rotation;
 int throttle;
} Joystick;

void joystick_update(Joystick *joystick, struct js_event*event);

#endif

