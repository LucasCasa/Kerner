#include <stdint.h>

char getSeconds();
char getMinutes();
char getHour();
int getDay();
int getMonth();
int getYear();
int setHour();

extern void _put_char(char c, char mod);
extern char _get_screen_char();
extern void _delete_char();
extern void _put_modifier(char mod);
extern char get_modifier();

char BCDtoDecimal(char num);
char DecimaltoBCD(char num);
void printNumber(uint8_t n);
void print_standby();


/* OJO CON EL TEMA DEL MODIFICADOR */
void putChar(char c,char mod){
	_put_char(c,mod);
}
/*void putScanCode(unsigned char value){
	putChar(scancodeToChar(value),0x02);
}*/



void eraseScreen(){
	for(int j = 0; j<25*160;j++){
		_put_char((char) 1,(char) 0);
	}
}
void setTime(){
	int aux = BCDtoDecimal(getHour());
	aux -=3;
	setHour(DecimaltoBCD(aux));
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
	printMessage("Day: ",0x02,5);
	printNumber(BCDtoDecimal(tvalue4));
	printMessage(" Month: ",0x02,8);
	printNumber(BCDtoDecimal(tvalue5));
	printMessage(" Year: ",0x02,7); //COMO implemento la ñ??
	printNumber(BCDtoDecimal(tvalue6));
	printMessage(" Time: ",0x02,7);
	printNumber(BCDtoDecimal(tvalue3));
	printMessage(":",0x02,1);
	printNumber(BCDtoDecimal(tvalue2));
	printMessage(":",0x02,1);
	printNumber(BCDtoDecimal(tvalue));
}
char BCDtoDecimal(char num){
	int aux = 0;
	aux = (num >> 4) * 10;
	aux += (num & 15);
	return aux;
}
char DecimaltoBCD(char n){
	int result = 0;
	while(n>10){
		result++;
		n -= 10;
	}
	result = (result << 4);
	result += n;
	return result;
}
char aux;
void print_standby(){
	if(get_modifier() == 0x22){
		_put_modifier(0x00);
	}else{
		_put_modifier(0x22);
	}
	
}