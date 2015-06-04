#include <stdint.h>
#include "include/keyboard_buffer.h"
//El Buffer de Teclado guarda Scan Codes
uint8_t keyboard_buffer[KB_SIZE];

// Indices para iterar sobre el buffer ciclico 
uint8_t keyboard_actual=0;
uint8_t keyboard_last=0;
uint8_t size = 0;
//Inicialmente los estados de shift y capslock estan en cero
unsigned char lastKeyRead = 0;


uint8_t keyboard_is_full(){
	return (size == KB_SIZE);
}

uint8_t keyboard_is_empty() {
	return (keyboard_actual == keyboard_last);
}

void keyboard_clear() {
	keyboard_actual = 0;
	keyboard_last = 0;	
	size = 0;
}
uint8_t keyboard_size(){
	return size;	
}
uint8_t keyboard_set_key(uint8_t c) {
	if( !keyboard_is_full() ) {
		if(c == '\b' && size > 0){
			keyboard_last--;
			size--;
		}else if(c == 0){
			//NOP
		}else{
			keyboard_buffer[keyboard_last++] = c;
			size++;
		}
		if( keyboard_last == KB_SIZE )
			keyboard_last = 0;

		return 1;
	}
	return 0;
}

uint8_t keyboard_get_key(){
	uint8_t c;

	while( keyboard_is_empty() ); 
	
	if( !keyboard_is_empty() ) {
		c = keyboard_buffer[keyboard_actual++];
		if( keyboard_actual == KB_SIZE )
			keyboard_actual = 0;

		lastKeyRead = c;
		if(size > 0) 
			size--;
		
		return c;
	}
	return 0;
}

unsigned char keyboard_last_key_read(void) {
	return lastKeyRead;
}

