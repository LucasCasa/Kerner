
//syscall 1 ---> escribo en pantalla
//syscall 2 ---> borro caracter
//syscall 3 ---> devuelvo el ultimo caracter
//syscall 4 ---> modifica el modificador del video
//syscall 5 ---> clear screen

#include "stdint.h"

static uint8_t * const video = (uint8_t*)0xB8000;
static uint8_t * currentVideo = (uint8_t*)0xB8000;
static uint8_t * saved_current_video;
static char * command = 0xB8000;
char* saved_shell[160*25];

void sys_write(char c,char mod);
char sys_get_screen_char();
void sys_delete_char();
void modifie(char mod);
char check_end_of_screen();


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
		case 5:
			erase_screen();
			reset_current_video();
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
	if((int)(currentVideo - 0xB8000) % 160 > 4 || ((uint64_t) currentVideo - (uint64_t)command) > 150){
		*(currentVideo + 1) = 0x00;
		currentVideo -=2;
		*(currentVideo) = 0;
		*(currentVideo +1) = 0x00;
	}
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
void save_screen(){
	for(int i = 0; i<160*25;i++){
		saved_shell[i] = video[i];
	}
	saved_current_video = currentVideo;
}
void restore_screen(){
	for(int i = 0; i<160*25;i++){
		video[i] = saved_shell[i];
	}
	currentVideo = saved_current_video;
}
void new_line(){
	*currentVideo = 0;
	shell_set_last_modifier();
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
				if(check_end_of_screen()){
					command -= 160;
				}
				shell_command();
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
		check_end_of_screen();
	
	
}

char check_end_of_screen(){
	if(currentVideo >= 0xB8000 + 160*25){
		scroll();
		currentVideo = 0xB8000 + 160*24;
		draw_new_line();
		return 1;
	}
	return 0;
}
void scroll(){
	int j = 0;
	for(int i = 160;i<160*25;i++,j++){
		video[j] = video[i];
		video[i] = 0;
	}
}

void erase_screen(){
	for(int j = 0; j<25*160;j++){
		video[j] = 0;
	}
}