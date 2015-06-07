
void modifie_colors(){
	print_message("Selecciona color:\n",0xFF);
	print_message("1- Fondo Negro, Letras Verdes,  Numeros Rojos (default)\n",0xFF);
	print_message("2- Fondo Azul,  Letras Blancas, Numeros Verdes \n",0xFF);
	print_message("3- Fondo Negro, Letras Amarillas,  Numeros celestes \n",0xFF);
	print_message("4- Fondo Gris,  Letras Negras, Numeros Azules \n",0xFF);
	print_message("5- Fondo Negro, Letras Rojas,   Numeros Blancos \n",0xFF);
	char c = 0,i = 0,res = 0;
	do{
	c = 0;
	i = 0;
	res = 0;
	print_message("Ingrese valor:\n",0xFF);
	while( (c = get_char())  != '\n'){
		i++;
		//print_message(c);
		if(isNumber(c)){
			res = (c - '0') ;
			print_number(c);
		}else{
			res = 0;
		}
	}
	}while(i > 1 || res == 0);
	print_number(res);

	switch(res){
		case 1:
			_call_int80(10,0x02,0x04);
			break;
		case 2:
			_call_int80(10,0x1F,0x12);
			break;
		case 3:
			_call_int80(10,0x0E,0x0B);
			break;
		case 4:
			_call_int80(10,0x70,0x71);
			break;
		case 5:
			_call_int80(10,0x04,0x0F);
			break;
	}
}
