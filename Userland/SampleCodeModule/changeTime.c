#include "changeTime.h"
#include "lib.h"


void changeTime(){
	unsigned int parameters[6];
	int size = 6,i=0;
	//int year,month,day,hour,min,sec;
	showRTC(); //Imprime el tiempo para que lo vea antes de preguntarle por cambiar
	while(i<size){
		char * aux;
		int value;
		print_message(INPUT[i],0xFF);
		aux=readKeyboard();
		value=atoi(aux);
		if(validate(value,MAX_VALUES[i],MIN_VALUES[i])){
			if(i==2 && validateDay(value,parameters[i-1],parameters[i-2])==NO){	
					;
			}else{
					parameters[i]=value;
					i++;				
			}
		}
	}
	callSetters(parameters);
	showRTC();
}

void callSetters(unsigned int parameters[6]){
	for(int i=0; i<6; i++){
		_call_int80(9,i,parameters[i]);
	}
}

//Valida que el numbero que halla escrito el usuario este entre el menor y mayor numero, si es un mes lo valido despues	
int validate(int value,int maxValue, int minValue){
	if(value>maxValue || value<minValue)
		return NO;
	return SI;
}

int validateDay(int day, int month, int year){
	if(month == 2){
		if(day == 29){
			if(year%4==0)
				return NO;
		}else if(day>29)
			return NO;
	}else if(month == 4 || month == 6 || month ==9 || month == 11){
		if(day>30){
			return NO;
		}
	}
	return SI;
}

char * readKeyboard(){
	char c = 0,j = 0;
	char aux[80];
	while((c = get_char()) != '\n'&& j<80){ //lee lo ultimo que se escribio en el teclado
			aux[j] = c;
			j++;
	}
	aux[j] = 0;
	return aux;
}
