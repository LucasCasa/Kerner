


void shell_init(){
	shell_erase_screen();
	printMessage("Bienvenidos al mejor TP de la historia\n", 0x12);
}

void shell_command(){
	char* aux = get_command();
	if(strcmp(aux,"time") == 0){
		showRTC();
		new_line();
	}else if(strcmp(aux,"clear") == 0){
		shell_erase_screen();
	}

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