#ifndef CHANGETIME_H

#define CHANGETIME_H

#define SI 1
#define NO 0

void changeTime();

void showRTC();
int validate(int value,int maxValue, int minValue);
int setDate(int parameters[6]);
char * readKeyboard();
int validateDay(int day, int month, int year);

int MAX_VALUES[]={9999,12,31,23,59,59};
int MIN_VALUES[]={0,1,1,0,0,0};
char INPUT_YEAR[]="Ingrese nuevo Anio:\n";
char INPUT_MONTH[]="Ingrese nuevo Mes:\n";
char INPUT_DAY[]="Ingrese nuevo Dia:\n";
char INPUT_HOUR[]="Ingrese nueva Hora:\n";
char INPUT_MIN[]="Ingrese nuevo Minuto:\n";
char INPUT_SEC[]="Ingrese nuevo Segundo:\n";
char * INPUT[]={INPUT_YEAR,INPUT_MONTH,INPUT_DAY,INPUT_HOUR,INPUT_MIN,INPUT_SEC};


#endif
