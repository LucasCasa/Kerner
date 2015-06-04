
//syscall 1 ---> escribo en pantalla
//syscall 2 ---> borro caracter
//syscall 3 ---> devuelvo el ultimo caracter
//syscall 4 ---> modifica el modificador del video
//syscall 5 ---> clear screen
// syscall 6 --->

#include "stdint.h"

static uint8_t * const video = (uint8_t*)0xB8000;
static uint8_t * currentVideo = (uint8_t*)0xB8000;
static uint8_t * saved_current_video;
static char * command_line = 0xB8000;
char* saved_shell[160*25];
char saved_modifier;
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
		case 6:
			return keyboard_get_key();
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
	if((int)currentVideo - (int)command_line > 4){
		*(currentVideo + 1) = 0x00;
		currentVideo -=2;
		*(currentVideo) = 0;
		*(currentVideo +1) = 0x00;
	}
}
char* get_command(){
	return command_line;
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
	set_command_line();
}
void save_screen(){
	for(int i = 0; i<160*25;i++){
		saved_shell[i] = video[i];
	}
	saved_current_video = currentVideo;
	currentVideo = video;
}
void restore_screen(){
	for(int i = 0; i<160*25;i++){
		video[i] = saved_shell[i];
	}
	currentVideo = saved_current_video;
	set_command_line();
}
void new_line(){
	*currentVideo = 0;
	*(currentVideo+1) = saved_modifier;
	int aux;
	aux = currentVideo - 0xB8000;
	currentVideo = 0xB8000 + (aux + 160) - (aux % 160);
	set_command_line();
	draw_new_line();
}
void sys_write(char c,char mod){
	switch(c){
			case '\n':
				new_line();			
				/*if(check_end_of_screen()){
					command -= 160;
				}
				shell_command();*/
				set_command_line();
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
		set_command_line();
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
void print_standby(){
	if(get_modifier() == 0x22){
		_put_modifier(saved_modifier);
	}else{
		saved_modifier = get_modifier();
		_put_modifier(0x22);
	}
	
}

void set_command_line(){
	command_line = (int)currentVideo - ((int)(currentVideo - video) % 160);
}
int ssaver = 0;
show_screensaver(){
	erase_screen();
	reset_current_video();
	switch(ssaver){
		case 0:
			lucas();
			ssaver++;
			break;
		case 1:
			maggie();
			ssaver++;
			break;
		case 2:
			kuyum();
			ssaver = 0;
			break;
	}
}

void maggie(){
	print_message(" _______  _______  _______  _______ _________ _______ \n",0x02);
	print_message("(       )(  ___  )(  ____ \\(  ____ \\\\__   __/(  ____ \\ \n",0x02);
	print_message("| () () || (   ) || (    \\/| (    \\/   ) (   | (    \\/ \n",0x02);
	print_message("| || || || (___) || |      | |         | |   | (__  \n",0x02);
	print_message("| |(_)| ||  ___  || | ____ | | ____    | |   |  __)   \n",0x02);
	print_message("| |   | || (   ) || | \\_  )| | \\_  )   | |   | (   \n",0x02);
	print_message("| )   ( || )   ( || (___) || (___) |___) (___| (____/\\ \n",0x02);
	print_message("|/     \\||/     \\|(_______)(_______)\\_______/(_______/ \n",0x02);
}

void lucas(){
	print_message(" _                 _______  _______  _______ \n",0x03);
	print_message("( \\      |\\     /|(  ____ \\(  ___  )(  ____ \\ \n",0x03);
	print_message("| (      | )   ( || (    \\/| (   ) || (    \\/ \n",0x03);
	print_message("| |      | |   | || |      | (___) || (_____  \n",0x03);
	print_message("| |      | |   | || |      |  ___  |(_____  ) \n",0x03);
	print_message("| |      | |   | || |      | (   ) |      ) | \n",0x03);
	print_message("| (____/\\| (___) || (____/\\| )   ( |/\\____) | \n",0x03);
	print_message("(_______/(_______)(_______/|/     \\|\\_______) \n",0x03);
}

void kuyum(){
	print_message(" _                                   _______ \n",0x04);
	print_message("| \\    /\\|\\     /||\\     /||\\     /|(       )\n",0x04);
	print_message("|  \\  / /| )   ( |( \\   / )| )   ( || () () | \n",0x04);
	print_message("|  (_/ / | |   | | \\ (_) / | |   | || || || | \n",0x04);
	print_message("|   _ (  | |   | |  \\   /  | |   | || |(_)| | \n",0x04);
	print_message("|  ( \\ \\ | |   | |   ) (   | |   | || |   | | \n",0x04);
	print_message("|  /  \\ \\| (___) |   | |   | (___) || )   ( | \n",0x04);
	print_message("|_/    \\/(_______)   \\_/   (_______)|/     \\| \n",0x04);
}
