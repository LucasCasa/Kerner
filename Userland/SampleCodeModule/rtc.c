#include "rtc.h"
#include "lib.h"
extern void _set_value(char r,unsigned char value);
extern int _get_value(char r);

unsigned char getValue(char r);
void setValue(char r,unsigned char value);

unsigned char getValue(char r){
	return _get_value(r);
}

void setValue(char r,unsigned char value){
	_set_value(r,value);
}


void setDate(unsigned int parameters[6]){
	setYear(DecimaltoBCD(parameters[0]%100));
	setMonth(DecimaltoBCD(parameters[1]));
	setDay(DecimaltoBCD(parameters[2]));
	setHour(DecimaltoBCD(parameters[3]));
	setMinute(DecimaltoBCD(parameters[4]));
	setSecond(DecimaltoBCD(parameters[5]));
}

void setYear(unsigned char value){
	setValue(ANIO,value);
}
void setMonth(unsigned char value){
	setValue(MES,value);

}
void setDay(unsigned char value){
	setValue(DIA,value);

}
void setHour(unsigned char value){
	setValue(HORA,value);

}
void setMinute(unsigned char value){
	setValue(MIN,value);
}
void setSecond(unsigned char value){
	setValue(SEC,value);
}

unsigned char getYear(){
	return BCDtoDecimal(getValue(ANIO));
}

unsigned char getMonth(){
	return BCDtoDecimal(getValue(MES));
}

unsigned char getDay(){
	return BCDtoDecimal(getValue(DIA));
}

unsigned char getHour(){
	return BCDtoDecimal(getValue(HORA));
}

unsigned char getMinute(){
	return BCDtoDecimal(getValue(MIN));
}

unsigned char getSecond(){
	return BCDtoDecimal(getValue(SEC));
}
