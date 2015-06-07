#include "stdint.h"

typedef struct {
  char* name;
  char* description;
  void(* function)();
  
} Command;

Command commands[7];
char comm[20];
int number_of_commands = 7;
char aux;
char name[20] = {0};

extern char bss;
extern char endOfBinary;

const char* time_str = "muestra el reloj";
const char* help_str = "muestra comandos disponibles";
const char* change_time_str = "cambia fecha y hora del sistema";
const char* whoami_str = "te dice quien sos";
const char* keyboard_str = "muestra la distribucion de las teclas";
const char* modi_str = "cambiar colores de la consola";
const char* clear_str = "borra la pantalla";
void * memset(void * destiny, int32_t c, uint64_t length);
void init_commands(char index, char * name, char* description, void (*function)());
void maggie();
void lucas();
void showRTC();
void shell_erase_screen();
void _shutdown_asm();
void changeTime();
void shell_show_commands();
void shell_exit();
void whoami();
void show_keyboard();
void modifie_colors();

int main(){
	memset(&bss, 0, &endOfBinary - &bss);

	shell_erase_screen();
	print_message("Bienvenidos al mejor TP de la historia\n", 0x12);
	init_commands(0,"clear", clear_str ,&shell_erase_screen);
	init_commands(1,"time", time_str , &showRTC);
	init_commands(2,"help" , help_str, &shell_show_commands);
	init_commands(3,"change time", change_time_str , &changeTime);
	init_commands(4, "whoami", whoami_str , &whoami);
	init_commands(5, "keyboard" , keyboard_str, &show_keyboard);
	init_commands(6, "modifiers" ,modi_str, &modifie_colors);
	while(1){
		shell_command();
	}
}

void init_commands(char index, char * name, char* description, void (*function)()){
	commands[index].name = name;
	commands[index].description = description;
	commands[index].function = function;
}

void shell_command(){
	char valid_command = 0;
	char c = 0,j = 0;
	int size;
	while((c = get_char()) != '\n'){
		comm[j++] = c;
	}

	comm[j] = 0;
	for(int i = 0;i<number_of_commands;i++){
		if(strcmp(comm,commands[i].name) == 0){
			commands[i].function();
			valid_command = 1;
		}
	}
	if(valid_command == 0){
		print_message("Comando Invalido\n",0xFF);
	}

}

void shell_exit(){
    
}

void shell_show_commands(){
	for(int i=0 ;i<number_of_commands;i++){
		print_message(commands[i].name, 0xFF);
		print_message(" - ", 0xFF);
		print_message(commands[i].description, 0xFF);
		print_message("\n",0xFF);
	}
}

void shell_erase_screen(){
	_call_int80(5);
}


void shell_set_last_modifier(){
	_put_modifier(aux);
}

void showRTC(){
	unsigned char anio,mes,dia,hora,min,seg;
	anio=getYear();
	mes=getMonth();
	dia=getDay();
	hora=getHour();
	min=getMinute();
	seg=getSecond();
	printf("Day: %d Month: %d Year: %d\n",dia,mes,anio);
	printf("Time: %d:%d:%d \n",hora,min,seg);
}

void whoami(){
	if(name[0] == 0){
		char c = 0,i = 0;
		print_message("No se... Quien sos?\n",0x0FF);
		while((c = get_char()) != '\n' && i<19){
			name[i++] = c;
		}
	}else{
		printf(name);
	}
}

