#include <stdint.h>

set_screensaver_time(){
	char value[10];
	uint8_t c = 1;
	uint32_t res = 0;
	uint8_t i = 0;
	uint8_t flag = 0;
	do{
		i = 0;
		c = 1;
		print_message("Ingrese valor (en segundos): \n ",0xFF);
		while((c = get_char()) != '\n'){
			value[i] = c;
			i++;
		}
		res = atoi(value);
	}while(res == -1);
	_call_int80(11,res);
}