 #include "include/keyboard_buffer.h"

 char Cbuffer[255];

 char actual_pos = 0;
 char last_pos = 0;
 char Csize = 0;
char C_is_empty();

void clean_set_char(char c){
		Cbuffer[last_pos++] = c;
		Csize++;
	if( last_pos == KB_SIZE )
		last_pos = 0;
}

void clean_size(){
	return Csize;
}
char clean_get_char(){
	char c;

	while(C_is_empty()) {}

	c = Cbuffer[actual_pos++];

	if( actual_pos == KB_SIZE )
		actual_pos = 0;

	if(Csize > 0) 
		Csize--;
	return c;
}

char C_is_empty(){
	return (actual_pos == last_pos);
}