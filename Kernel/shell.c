typedef struct {
  char* name;
  char* description;
  void(* function)();
  
} Command;

Command commands[7];
char comm[20];
int number_of_commands = 7;
char aux;


void init_commands(char index, char * name, char* description, void (*function)());
void maggie();
void lucas();
void showRTC();
void shell_erase_screen();
void _shutdown_asm();
void changeTime();
void shell_show_commands();
void shell_exit();

void shell_init(){
	init_commands(0,"clear","borra la pantalla",&shell_erase_screen);
	init_commands(1,"time","muestra el reloj" , &showRTC);
	init_commands(2,"help" , "muestra comandos disponibles", &shell_show_commands);
	init_commands(3,"change time", "cambia fecha y hora del sistema" , &changeTime);
	init_commands(4,"shutdown","cerrar el proyecto", &shell_exit);
	init_commands( 5 , "maggie" , "BEST COMMAND EVER" , &maggie);
	init_commands( 6, "lucas" , "HOLA GENTE" , &lucas);
	shell_erase_screen();
	print_message("Bienvenidos al mejor TP de la historia\n", 0x12);
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
	while((c = clean_get_char()) != '\n' && j<19){
		comm[j] = c;
		j++;
	}
	//size = _call_int80(6,comm,0);	

	comm[size] = 0;
	for(int i = 0;i<number_of_commands;i++){
		if(strcmp(comm,commands[i].name) == 0){
			commands[i].function();
			valid_command = 1;
		}
	}
	if(valid_command == 0){
		//print_message("Comando Invalido\n");
	}

}

void shell_exit(){
    
}

void shell_show_commands(){
	for(int i=0 ;i<number_of_commands;i++){
		print_message(commands[i].name, 0x05);
		print_message(" - ", 0x05);
		print_message(commands[i].description, 0x05);
		print_message("\n",0x05);
	}
}

void shell_erase_screen(){
	_call_int80(5);
}


void shell_set_last_modifier(){
	_put_modifier(aux);
}

void showRTC(){
	unsigned char tvalue;
	unsigned char tvalue2;
	unsigned char tvalue3;
	unsigned char tvalue4;
	unsigned char tvalue5;
	unsigned int tvalue6;
	
	tvalue =  getSeconds();
	tvalue2 = getMinutes();
	tvalue3 = getHour();
	tvalue4 = getDay();
	tvalue5 = getMonth();
	tvalue6 = getYear();
	print_message("Day: ",0x02);
	print_number(BCDtoDecimal(tvalue4));
	print_message(" Month: ",0x02);
	print_number(BCDtoDecimal(tvalue5));
	print_message(" Year: ",0x02); //COMO implemento la ñ??
	print_number(BCDtoDecimal(tvalue6));
	print_message(" Time: ",0x02);
	print_number(BCDtoDecimal(tvalue3));
	print_message(":",0x02);
	print_number(BCDtoDecimal(tvalue2));
	print_message(":",0x02);
	print_number(BCDtoDecimal(tvalue));
	print_message("\n");
}

