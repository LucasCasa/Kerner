#include <stdint.h>
#include "include/handlers.h"


static int i = 0;
static int time = 0;
static char light = 0;
static char aux = 1;
uint16_t sleep_time = 0;
extern void lights(char l);

void timer_handler(){
	time++;
	sleep_time++;
	if(sleep_time >= 100){
		if(sleep_time < 110){
			save_screen();
			sleep_time = 110;
		}
		if((sleep_time % 10) == 0){
			shell_show_screensaver();
		}
	}else{
		if(time >= 10){
			shell_print_standby();
			time = 0;
		}
	}
	
	light = (light ^ aux);
	aux*=2;
	if(aux > 4){
		aux = 1;
	}
	lights(2);
}

void keyboard_handler(uint8_t scancode){
	if(scancode != 250){
		if(sleep_time >= 100){
			restore_screen();
		}
		sleep_time = 0;
		if(check_special_key(scancode)){
			keyboard_set_key(scancode_to_char(scancode));
			putChar(scancode_to_char(scancode),0x02);
		}
	}
}


