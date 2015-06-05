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
int validate(char * aux, int * resp, int maxValue, int minValue);
int setDate(int parameters[6]);
char * readKeyboard();
int validateDay(int day, int month, int year);



void changeTime(){
	int parameters[6];
	int size = 6,i=0;
	int resp=NO;
	//int year,month,day,hour,min,sec;
	showRTC(); //Imprime el tiempo para que lo vea antes de preguntarle por cambiar
	while(i<size && resp==NO){
		char * aux;
		int value;
		int resp;
		print_message(INPUT[i],0x0F);
		aux=readKeyboard();
		resp=validate(aux,&value,MAX_VALUES[i],MIN_VALUES[i]); //Valida que se hayan escrito numeros de como maximo 2 caracteres y que este correcto el parametro
		if(resp==SI){
			if(i==2 && validateDay(value,parameters[i-1],parameters[i-2])==NO){
				resp==NO;
			}
			else{
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

int 
validate(char * aux, int * resp, int maxValue, int minValue){
	int length = strlen(aux);
	int value=0;
	if(length>2 || length<0)
		return NO;
	for(int i=0;i<length;i++){
		if(isNumber(aux[i])){
				value+=(aux[i]-'0')*pow(10,i);
		}else{
			return NO;
		}
	}
	if(value>maxValue || value<minValue)
		return NO;
	*resp=value;
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
	char aux[80];
	while((c = keyboard_get_key()) != '\n'&& j<19){ //lee lo ultimo que se escribio en el teclado
			aux[j] = c;
			j++;
	}
	aux[j] = 0;
	return aux;
}
