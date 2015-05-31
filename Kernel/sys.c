
//syscall 1 ---> escribo en pantalla
//syscall 2 ---> borro caracter
//syscall 3 ---> devuelvo el ultimo caracter
//syscall 4 ---> modifica el modificador del video
#include "stdint.h"

static uint8_t * const video = (uint8_t*)0xB8000;
static uint8_t * currentVideo = (uint8_t*)0xB8000;
static char * command = 0xB8000;

void sys_write(char c,char mod);
char sys_get_screen_char();
void sys_delete_char();
void modifie(char mod);


char sys_manager(int order,char modifier, char other_modifier){
	switch(order){
		case 1:
			sys_write(modifier,other_modifier);
			break;

		case 2:
			sys_delete_char();
			break;

		case 3:
			return sys_get_screen_char();
			break;
		case 4:
			modifie(modifier);
			break;
	}
	return 0;
}
char get_modifier(){
	return *(currentVideo +1);
}
void modifie(char mod){
	*(currentVideo + 1) = mod;
}
char sys_get_screen_char(){
	return *(currentVideo - 2);
}
void sys_delete_char(){
		*(currentVideo + 1) = 0x00;
		currentVideo -=2;
		*(currentVideo) = 0;
		*(currentVideo +1) = 0x00;
}
char* get_command(){
	return command;
}
void draw_new_line(){
	*(currentVideo++) = '>';
	*(currentVideo++) = 0x04;
	*(currentVideo++) = ':';
	*(currentVideo++) = 0x04;
}
void reset_current_video(){
	currentVideo = video;
	draw_new_line();
}
void new_line(){
	*currentVideo = 0;
	int aux;
	aux = currentVideo - 0xB8000;
	currentVideo = 0xB8000 + (aux + 160) - (aux % 160);
	draw_new_line();
	command = currentVideo - 160;
}
void sys_write(char c,char mod){
	switch(c){
			case '\n':
				new_line();			
				do_command();
				command = currentVideo;
				break;
			case '\b':
				sys_delete_char();
			case 0:
				break;
			default:
				*(currentVideo++) = c;
				*(currentVideo++) = mod;
				break;
		}

	if(currentVideo >= 0xB8000 + 160*25){
		currentVideo = video;
	}
	
}
