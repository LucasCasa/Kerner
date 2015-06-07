#include "changeTime.h"
#include "lib.h"

#define SI 1
#define NO 0

char MAX_VALUES[]={99,12,31,23,59,59};
char MIN_VALUES[]={0,1,1,0,0,0};
char INPUT_YEAR[]="Ingrese nuevo Anio: ";
char INPUT_MONTH[]="Ingrese nuevo Mes: ";
char INPUT_DAY[]="Ingrese nuevo Dia: ";
char INPUT_HOUR[]="Ingrese nueva Hora: ";
char INPUT_MIN[]="Ingrese nuevo Minuto: ";
char INPUT_SEC[]="Ingrese nuevo Segundo: ";
char * INPUT[]={INPUT_YEAR,INPUT_MONTH,INPUT_DAY,INPUT_HOUR,INPUT_MIN,INPUT_SEC};
void showRTC();
int validate(int value,int maxValue, int minValue);
int setDate(int parameters[6]);
char * readKeyboard();
int validateDay(int day, int month, int year);



void changeTime(){
	int parameters[6];
	int size = 6,i=0;
	//int year,month,day,hour,min,sec;
	showRTC(); //Imprime el tiempo para que lo vea antes de preguntarle por cambiar
	while(i<size){
		char * aux;
		int value;
		print_message(INPUT[i],0x0F);
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
	setDate(parameters);
	showRTC();

}

int 
setDate(int parameters[6]){
	
}

//Valida que el numbero que halla escrito el usuario este entre el menor y mayor numero, si es un mes lo valido despues	
int validate(int value,int maxValue, int minValue){
	if(value>maxValue || value<minValue)
		return NO;
	return SI;
}

int
validateDay(int day, int month, int year){
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
	char aux[3];
	while((c = get_char()) != '\n'&& j<3){ //lee lo ultimo que se escribio en el teclado
			aux[j] = c;
			j++;
	}
	aux[j] = 0;
	return aux;
}
