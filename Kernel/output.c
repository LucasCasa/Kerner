#include <stdint.h>

static uint8_t * const video = (uint8_t*)0xB8000;
static uint8_t * currentVideo = (uint8_t*)0xB8000;

char getSeconds();
char getMinutes();
char getHour();
int getDay();
int getMonth();
int getYear();
int setHour();

char BCDtoDecimal(char num);
char DecimaltoBCD(char num);
void printNumber(uint8_t n);
void print_standby();

/* OJO CON EL TEMA DEL MODIFICADOR */
void putChar(char c,char mod){
	int aux;
	switch(c){
			case '\n':
				aux = currentVideo - 0xB8000;
				currentVideo = 0xB8000 + (aux + 160) - (aux % 160);
				*(currentVideo++) = ':';
				*(currentVideo++) = 0x04;
				*(currentVideo++) = ')';
				*(currentVideo++) = 0x04;
				break;
			case '\b':
				if((int)(currentVideo - 0xB8000) % 160 > 4){
					if(*currentVideo =='_'){
						*currentVideo = 0;
					}
					currentVideo -=2;
					*(currentVideo) = 0;
				}
				break;
			case 0:
				break;
			default:
				*(currentVideo++) = c;
				*(currentVideo++) = mod;
				break;
		}
	if(currentVideo > 0xB8000 + 160*25){
		currentVideo = video;
	}
}
/*void putScanCode(unsigned char value){
	putChar(scancodeToChar(value),0x02);
}*/

void printMessage(char* message, char mod, int size){
	for( int i = 0 ; i<size ; i++ ){
		putChar(message[i],mod);
	}
}


void eraseScreen(){
	for(int j = 0; j<25;j++){
		for(int i = 0;i<160;i++){
		video[160*j + i] = 0;
		}
	}
}
void setTime(){
	int aux = BCDtoDecimal(getHour());
	aux -=3;
	setHour(DecimaltoBCD(aux));
}

void showRTC(){
	currentVideo = video;
	unsigned char tvalue;
	unsigned char tvalue2;
	unsigned char tvalue3;
	unsigned char tvalue4;
	unsigned char tvalue5;
	unsigned int tvalue6;


	eraseScreen();
	currentVideo = video + 66;
	printNumber(BCDtoDecimal(getHour()));
	currentVideo = video;
	//setHour();
	tvalue = getSeconds();
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
	currentVideo = video;
}

void printNumber(uint8_t n){
	if(n < 10){
		putChar(n + '0',0x04);
	}else{
		printNumber(n / 10);
		putChar((n % 10) + '0',0x04);
	}
	
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
	if(*currentVideo == '_'){
		*currentVideo = aux;
		*(currentVideo +1 ) = 0x02;
	} else{
		aux = *currentVideo;
		*currentVideo = '_';
		*(currentVideo+1) = 0x02;
	}
}