
#include "include/handlers.h"


static int i = 0;
static int time = 0;
static char light = 0;
static char aux = 1;

extern void lights(char l);

void timer_handler(){
	time++;
	if(time == 10){
		print_standby();
		time = 0;
	}
	light = (light ^ aux);
	aux*=2;
	if(aux > 4){
		aux = 1;
	}
	lights(2);
}

void keyboard_handler(char scancode){
	if(check_special_key(scancode)){
			putChar(scancode_to_char(scancode),0x02);
	}
		
}


