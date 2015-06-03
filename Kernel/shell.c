#include "include/typedef.h"

Command commands[5];
int number_of_commands = 3;

void init_commands(char index, char * name, char* description, void (*function)());
void maggie();
void showRTC();
void shell_erase_screen();

void shell_init(){
	init_commands(0,"clear","borra la pantalla",&shell_erase_screen);
	init_commands(1,"time","muestra el reloj" , &showRTC);
	init_commands(2,"maggie", "BEST COMMAND EVER", &maggie);
	shell_erase_screen();
	printMessage("Bienvenidos al mejor TP de la historia\n", 0x12);
}
void init_commands(char index, char * name, char* description, void (*function)()){
	commands[index].name = name;
	commands[index].description = description;
	commands[index].function = function;
}
void shell_command(){
	char* aux = get_command();
	for(int i = 0;i<number_of_commands;i++){
		if(strcmp(aux,commands[i].name) == 0){
			commands[i].function();
		}
	}
	/*if(strcmp(aux,"time") == 0){
		showRTC();
		new_line();
	}else if(strcmp(aux,"clear") == 0){
		shell_erase_screen();
	}else if(strcmp(aux,"maggie") == 0){
		maggie();
	}*/

}

void shell_show_commands(){
	
}

void shell_erase_screen(){
	_call_int80(5);
}


char aux;
void shell_print_standby(){
	if(get_modifier() == 0x22){
		_put_modifier(aux);
	}else{
		aux = get_modifier();
		_put_modifier(0x22);
	}
	
}
void shell_set_last_modifier(){
	_put_modifier(aux);
}

void maggie(){

printMessage(" _______  _______  _______  _______ _________ _______ \n",0x02);
printMessage("(       )(  ___  )(  ____ \\(  ____ \\\\__   __/(  ____ \\ \n",0x02);
printMessage("| () () || (   ) || (    \\/| (    \\/   ) (   | (    \\/ \n",0x02);
printMessage("| || || || (___) || |      | |         | |   | (__  \n",0x02);
printMessage("| |(_)| ||  ___  || | ____ | | ____    | |   |  __)   \n",0x02);
printMessage("| |   | || (   ) || | \\_  )| | \\_  )   | |   | (   \n",0x02);
printMessage("| )   ( || )   ( || (___) || (___) |___) (___| (____/\\ \n",0x02);
printMessage("|/     \\||/     \\|(_______)(_______)\\_______/(_______/ \n",0x02);

}