#ifndef SCR_SAVER_H_
#define SCR_SAVER_H_

#define MINSCRSAVERTIME 3600 //1 hour

#include <stdint.h>
#include "video_manager.h"
#include "sys_lib.h"

void kuyum();
void lucas();
void maggie();
void show_screensaver();
int validateScreenTime(int time);

#endif