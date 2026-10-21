#include "joystick.h"
int fd = 0;
long long last_time = 0;

void joystick_update(Joystick *joystick, struct js_event *event)
{
  if(event->type != JS_EVENT_AXIS)
  {
    return;
  }
  switch(event->number)
  { 
    case 0:
      joystick->x = event->value;
      break;
    case 1:
      joystick->y = event->value;
      break;
    case 2:
      joystick->rotation = event->value;
      break;
    case 3:
      joystick->throttle = event->value;
      break;
  }
}
int main(void)
{
  fd = open("/dev/input/js0", O_RDONLY);
  if(fd < 3)
  {
   perror("Joystick");
   return 1;
  }


  Joystick joystick = {0};
  struct js_event event;

  while(1)
 {
  if(read(fd, &event, sizeof(event)) == sizeof(event))
  {
   event.type &= ~JS_EVENT_INIT;
   struct timespec now;
   clock_gettime(CLOCK_MONOTONIC, &now);
   long long time_ms = now.tv_sec * 1000LL + now.tv_nsec / 1000000LL;
   joystick_update(&joystick, &event);
   if(time_ms - last_time >= 100)
   {
   printf("X : %6d, Y : %6d, ROT %6d, THR %6d\r\n", joystick.x, joystick.y, joystick.rotation, joystick.throttle);
   }
}
 }
 return 0;
}
