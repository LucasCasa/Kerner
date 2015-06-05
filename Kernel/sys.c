#include <stdint.h>
//syscall 1 ---> escribo en pantalla
//syscall 2 ---> borro caracter
//syscall 3 ---> devuelvo el ultimo caracter
//syscall 4 ---> modifica el modificador del video
//syscall 5 ---> clear screen
// syscall 6 ---> palabra que se escribio.

char read(char* buff, char size);

char sys_manager(int order,uint64_t arg1, uint64_t arg2){
	switch(order){
		case 1:
			sys_write((char) arg1,(char) arg2);
			break;

		case 2:
			sys_delete_char();
			break;

		case 3:
			return sys_get_screen_char();
			break;
		case 4:
			modifie((char)arg1);
			break;
		case 5:
			erase_screen();
			reset_current_video();
			break;
		case 6:
			return read( (uint8_t*) arg1,(uint8_t) arg2);
			break;
	}
	return 0;
}
char read(char* buff, char size){
	if(keyboard_is_empty())
		return 0;

	if(size == 0)
		size == 255;

	char c;
	for(int i= 0; i<size && (c = keyboard_get_key()) != '\n';i++){
		buff[i] = c;
	}
	return 1;
}