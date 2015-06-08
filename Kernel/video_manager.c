#include "stdint.h"
#include "video_manager.h"


void set_default_modifiers(char s, char n){
	str_modifier = s;
	num_modifier = n;
	set_new_modifier();
}
void set_new_modifier(){
	for(int i = 0; i<160*25;i++){
		if(isNumber(video[i]) || i % 160 < 4){
			video[++i] = num_modifier;
		}else{
			video[++i] = str_modifier;
		}
	}
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
		*(currentVideo + 1) = str_modifier;
		currentVideo -=2;
		*(currentVideo) = 0;
		*(currentVideo +1) = str_modifier;
	}
}
void draw_new_line(){
	*(currentVideo++) = '>';
	*(currentVideo++) = num_modifier;
	*(currentVideo++) = ':';
	*(currentVideo++) = num_modifier;
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
void sys_write(char c,uint8_t mod){
	switch(c){
		case '\n':
			new_line();
			set_command_line();

			break;
		case '\b':
			sys_delete_char();
		case 0:
			break;
		default:
			*(currentVideo++) = c;
			if(mod == 0xFF){
				if(isNumber(c)){
					*(currentVideo++) = num_modifier;
				}else{
					*(currentVideo++) = str_modifier;
				}
			}else{
				*(currentVideo++) = mod;
			}
			break;
	}
	check_end_of_screen();	
}

char check_end_of_screen(){
	if(currentVideo >= 0xB8000 + 160*25){
		scroll();
		currentVideo = 0xB8000 + 160*24;
		draw_new_line();
		set_command_line();
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
	while( j < 160*25){
		video[++j] = str_modifier;
		j++;
	}
}

void erase_screen(){
	for(int j = 0; j<25*160;j++){
		video[j++] = 0;
		video[j] = (num_modifier & 0xF0) + (num_modifier >> 4);
	}
}
void print_standby(){
	if(get_modifier() == 0x22){
		modifie(saved_modifier);
	}else{
		saved_modifier = get_modifier();
		modifie(0x22);
	}
	
}
void set_command_line(){
	command_line = (int)currentVideo - ((int)(currentVideo - video) % 160);
}

int ssaver = 0;
void show_screensaver(){
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
	print_message(" _______  _______  _______  _______ _________ _______ \n",0xFF);
	print_message("(       )(  ___  )(  ____ \\(  ____ \\\\__   __/(  ____ \\ \n",0xFF);
	print_message("| () () || (   ) || (    \\/| (    \\/   ) (   | (    \\/ \n",0xFF);
	print_message("| || || || (___) || |      | |         | |   | (__  \n",0xFF);
	print_message("| |(_)| ||  ___  || | ____ | | ____    | |   |  __)   \n",0xFF);
	print_message("| |   | || (   ) || | \\_  )| | \\_  )   | |   | (   \n",0xFF);
	print_message("| )   ( || )   ( || (___) || (___) |___) (___| (____/\\ \n",0xFF);
	print_message("|/     \\||/     \\|(_______)(_______)\\_______/(_______/ \n",0xFF);
}

void lucas(){
	print_message(" _                 _______  _______  _______ \n",0xFF);
	print_message("( \\      |\\     /|(  ____ \\(  ___  )(  ____ \\ \n",0xFF);
	print_message("| (      | )   ( || (    \\/| (   ) || (    \\/ \n",0xFF);
	print_message("| |      | |   | || |      | (___) || (_____  \n",0xFF);
	print_message("| |      | |   | || |      |  ___  |(_____  ) \n",0xFF);
	print_message("| |      | |   | || |      | (   ) |      ) | \n",0xFF);
	print_message("| (____/\\| (___) || (____/\\| )   ( |/\\____) | \n",0xFF);
	print_message("(_______/(_______)(_______/|/     \\|\\_______) \n",0xFF);
}

void kuyum(){
	print_message(" _                                   _______ \n",0xFF);
	print_message("| \\    /\\|\\     /||\\     /||\\     /|(       )\n",0xFF);
	print_message("|  \\  / /| )   ( |( \\   / )| )   ( || () () | \n",0xFF);
	print_message("|  (_/ / | |   | | \\ (_) / | |   | || || || | \n",0xFF);
	print_message("|   _ (  | |   | |  \\   /  | |   | || |(_)| | \n",0xFF);
	print_message("|  ( \\ \\ | |   | |   ) (   | |   | || |   | | \n",0xFF);
	print_message("|  /  \\ \\| (___) |   | |   | (___) || )   ( | \n",0xFF);
	print_message("|_/    \\/(_______)   \\_/   (_______)|/     \\| \n",0xFF);
}
