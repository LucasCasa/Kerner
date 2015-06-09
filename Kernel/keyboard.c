#include <stdint.h>
#include "keyboard.h"

uint8_t left_shift = 0;
uint8_t right_shift = 0;
uint8_t caps_lock = 0;

uint8_t keyboard[90][2] = {
	{0,0},//000
	{0,0},//001 ESCAPE
	{'1','!'},	//002
	{'2','@'},	//003
	{'3','#'},	//004
	{'4','$'},	//005
	{'5','%'},	//006
	{'6','^'},	//007
	{'7','&'},	//008
	{'8','*'},	//009
	{'9','('},	//010
	{'0',')'},	//011
	{'-','_'},	//012
	{'=','+'},	//013
	{'\b','\b'},	//014 BACKSPACE
	{'\t','\t'},	//015 TAB
	{'q','Q'},	//016
	{'w','W'},	//017
	{'e','E'},	//018
	{'r','R'},	//019
	{'t','T'},	//020
	{'y','Y'},	//021
	{'u','U'},	//022
	{'i','I'},	//023
	{'o','O'},	//024
	{'p','P'},	//025
	{'[','{'},	//026
	{']','}'},	//027
	{'\n','\n'},	//028
	{0,0},//029 CTRL IZQ
	{'a','A'},	//030
	{'s','S'},	//031
	{'d','D'},	//032
	{'f','F'},	//033
	{'g','G'},	//034
	{'h','H'},	//035
	{'j','J'},	//036
	{'k','K'},	//037
	{'l','L'},	//038
	{';',':'},	//039
	{'\'','\"'},	//040
	{'`','~'},	//041
	{0,0},//042 SHIFT IZQ
	{'\\','|'},	//043
	{'z','Z'},	//044
	{'x','X'},	//045
	{'c','C'},	//046
	{'v','V'},	//047
	{'b','B'},	//048
	{'n','N'},	//049
	{'m','M'},	//050
	{',','<'},	//051
	{'.','>'},	//052
	{'/','?'},	//053 
	{0,0},//054 SHIFT DER
	{'*','*'},	//055 KEY *
	{0,0},//056 ALT IZQ
	{' ',' '},	//057 SPACE
	{0,0},//058 CAPSLOCK
	{0,0},//059 F1
	{0,0},//060 F2
	{0,0},//061 F3
	{0,0},//062 F4
	{0,0},//063 F5
	{0,0},//064 F6
	{0,0},//065 F7
	{0,0},//066 F8
	{0,0},//067 F9
	{0,0},//068 F10
	{0,0},//069 NUM LOCK
	{0,0},//070 SCROLL LOCK
	{'7','7'},	//071 KEY 7
	{'8','8'},	//072 KEY 8
	{'9','9'},	//073 KEY 9
	{'-','-'},	//074 KEY -
	{'4','4'},	//075 KEY 4
	{'5','5'},	//076 KEY 5
	{'6','6'},	//077 KEY 6
	{'+','+'},	//078 KEY +
	{'1','1'},	//079 KEY 1
	{'2','2'},	//080 KEY 2
	{'3','3'},	//081 KEY 3
	{'0','0'},	//082 KEY 0
	{'.','.'},	//083 KEY .
	{0,0},//084 SYS REQ (AT)
	{'+','*'},	//085
	{'+','*'},	//086
	{0,0},//087 F11
	{0,0},//088 F12
	{'+','*'},	//089
};
uint8_t check_special_key(uint8_t c){
	if(c == 58){
		if(caps_lock){
			caps_lock = 0;
		}else{
			caps_lock = 1;
		}
		return 0;
	}else if(c == 54){
		right_shift = 1;
		return 0;
	}else if(c == 42){
		left_shift = 1;
		return 0;
	}else if(c == 54 + 0x80){
		right_shift = 0;
		return 0;
	}else if(c == 42 + 0x80){
		left_shift = 0;
		return 0;
	}else if(c > 90){
		return 0;
	}
	return 1;
}
int is_alpha(unsigned char scancode){
	return ( (keyboard[scancode][0] >= (unsigned char)'a')  && (keyboard[scancode][0] <= (unsigned char)'z') );
}

uint8_t scancode_to_char(uint8_t c) {
	int key;
	
	
	//Con este if determino si imprimo en Mayuscula o Minuscula
	if( caps_lock == 0 ){
		if( left_shift || right_shift ){
			key = 1;
		} else {
			key = 0;
		}
	} else {
		if( left_shift || right_shift ) {
			if( is_alpha(c) ){
				key = 0;
			} else {
				key = 1;
			}
		}else{
			if( is_alpha(c) ){
				key = 1;
			} else {
				key = 0;
			}
		}
	}
	return keyboard[c][key];
}