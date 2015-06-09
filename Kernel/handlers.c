#include <stdint.h>
#include "include/handlers.h"


static int time = 0;
uint16_t sleep_time = 0;
uint32_t screensaver_time = 5 * 1000 / 55;

void timer_handler(){
	time++;
	sleep_time++;
	if(sleep_time >= screensaver_time){
		if(sleep_time < screensaver_time + 10){
			save_screen();
			sleep_time = screensaver_time + 10;
		}
		if((sleep_time % 10) == 0){
			show_screensaver();
		}
	}else{
		if(time >= 10){
			print_standby();
			time = 0;
		}
	}
}

void keyboard_handler(uint8_t scancode){
	if(scancode != 250){
		
		if(sleep_time >= screensaver_time){
			restore_screen();
		}else{
			if(check_special_key(scancode)){
				if(keyboard_set_key(scancode_to_char(scancode)))
					sys_write(scancode_to_char(scancode),0xFF);
			}
		}
		sleep_time = 0;
	}

}


