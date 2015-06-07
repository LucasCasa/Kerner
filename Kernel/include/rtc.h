#ifndef RTC_H
	#define RTC_H
	#define ANIO 9
	#define MES 8
	#define DIA 7
	#define HORA 4
	#define MIN 2
	#define SEC 0

	/* agarra el valor desado */
	unsigned char getValue(char r);
	/* setea el valor value*/
	void setValue(char r,unsigned char value);
#endif
