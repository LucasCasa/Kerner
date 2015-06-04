#include <stdint.h>
#include "include/handlers.h"

extern void shell_show_screensaver();
extern void shell_print_standby();

static int i = 0;
static int time = 0;
static char light = 0;
static char aux = 1;
uint16_t sleep_time = 0;

void timer_handler(){
	time++;
	sleep_time++;
	if(sleep_time >= 100){
		if(sleep_time < 110){
			save_screen();
			sleep_time = 110;
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
		
		if(sleep_time >= 100){
			restore_screen();
		}else{
			if(check_special_key(scancode)){
				keyboard_set_key(scancode_to_char(scancode));
				putChar(scancode_to_char(scancode),0x02);
			}
		}
		if(scancode_to_char(scancode) == '\n'){
			shell_enter_pressed();
		}
		sleep_time = 0;
	}

}


