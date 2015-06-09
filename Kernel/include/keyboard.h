#ifndef KEAYBOARD_H_
#define	KEYBOARD_H_

uint8_t check_special_key(uint8_t c);
int is_alpha(unsigned char scancode);

uint8_t scancode_to_char(uint8_t c);


#endif