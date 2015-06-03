#include "include/typedef.h"

Command commands[5];
char comm[20];
int number_of_commands = 5;
char aux;


void init_commands(char index, char * name, char* description, void (*function)());
void maggie();
void lucas();
void showRTC();
void shell_erase_screen();
void _shutdown_asm();

void shell_init(){
	init_commands( 0 , "clear" , "borra la pantalla" , &shell_erase_screen);
	init_commands( 1 , "time" , "muestra el reloj" , &showRTC);
	init_commands( 2 , "maggie" , "BEST COMMAND EVER" , &maggie);
	init_commands( 3 , "lucas" , "HOLA GENTE" , &lucas);
	init_commands( 4 , "shutdown" , "APAGA" , &_shutdown_asm);
	shell_erase_screen();
	printMessage("Bienvenidos al mejor TP de la historia\n", 0x12);
}
void init_commands(char index, char * name, char* description, void (*function)()){
	commands[index].name = name;
	commands[index].description = description;
	commands[index].function = function;
}
void shell_command(){
	char c = 0,j = 0;
	while(!keyboard_is_empty() && (c = keyboard_get_key()) != '\n' && j<19){
		comm[j] = c;
		j++;
	}
	comm[j] = 0;
	for(int i = 0;i<number_of_commands;i++){
		if(strcmp(comm,commands[i].name) == 0){
			commands[i].function();
		}
	}

}

void shell_show_commands(){
	
}

void shell_erase_screen(){
	_call_int80(5);
}



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
int ssaver = 0;
shell_show_screensaver(){
	shell_erase_screen();
	if(ssaver){
		maggie();
		ssaver = 0;
	}else{
		lucas();
		ssaver = 1;
	}
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

void lucas(){
	printMessage(" _                 _______  _______  _______ \n",0x03);
	printMessage("( \\      |\\     /|(  ____ \\(  ___  )(  ____ \\ \n",0x03);
	printMessage("| (      | )   ( || (    \\/| (   ) || (    \\/ \n",0x03);
	printMessage("| |      | |   | || |      | (___) || (_____  \n",0x03);
	printMessage("| |      | |   | || |      |  ___  |(_____  ) \n",0x03);
	printMessage("| |      | |   | || |      | (   ) |      ) | \n",0x03);
	printMessage("| (____/\\| (___) || (____/\\| )   ( |/\\____) | \n",0x03);
	printMessage("(_______/(_______)(_______/|/     \\|\\_______) \n",0x03);
}

void kuyum(){
printMessage(" _                                   _______ \n",0x04);
printMessage("| \\    /\\|\\     /||\\     /||\\     /|(       )\n",0x04);
printMessage("|  \\  / /| )   ( |( \\   / )| )   ( || () () | \n",0x04);
printMessage("|  (_/ / | |   | | \\ (_) / | |   | || || || | \n",0x04);
printMessage("|   _ (  | |   | |  \\   /  | |   | || |(_)| | \n",0x04);
printMessage("|  ( \\ \\ | |   | |   ) (   | |   | || |   | | \n",0x04);
printMessage("|  /  \\ \\| (___) |   | |   | (___) || )   ( | \n",0x04);
printMessage("|_/    \\/(_______)   \\_/   (_______)|/     \\| \n",0x04);
                                             
}