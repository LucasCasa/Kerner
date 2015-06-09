#ifndef CHANGETIME_H

#define CHANGETIME_H

#define SI 1
#define NO 0

void changeTime();

void showRTC();

int validate(int value,int maxValue, int minValue);
int setDate(int parameters[6]);
void readKeyboard(char* buff);
int validateDay(int day, int month, int year);
void callSetters(unsigned int parameters[6]);

int MAX_VALUES[]={9999,12,31,23,59,59};
int MIN_VALUES[]={0,1,1,0,0,0};
char INPUT_YEAR[]="Enter new year:";
char INPUT_MONTH[]="Enter new month:";
char INPUT_DAY[]="Enter new day:";
char INPUT_HOUR[]="Enter new hour:";
char INPUT_MIN[]="Enter new minute:";
char INPUT_SEC[]="Emter new secomd:";
char * INPUT[]={INPUT_YEAR,INPUT_MONTH,INPUT_DAY,INPUT_HOUR,INPUT_MIN,INPUT_SEC};


#endif
