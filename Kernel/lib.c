#include <stdint.h>
#include <stdarg.h>


void * memset(void * destination, int32_t c, uint64_t length)
{
	uint8_t chr = (uint8_t)c;
	uint8_t * dst = (uint8_t*)destination;

	while(length--)
		dst[length] = chr;

	return destination;
}

void * memcpy(void * destination, const void * source, uint64_t length)
{
	/*
	* memcpy does not support overlapping buffers, so always do it
	* forwards. (Don't change this without adjusting memmove.)
	*
	* For speedy copying, optimize the common case where both pointers
	* and the length are word-aligned, and copy word-at-a-time instead
	* of byte-at-a-time. Otherwise, copy by bytes.
	*
	* The alignment logic below should be portable. We rely on
	* the compiler to be reasonably intelligent about optimizing
	* the divides and modulos out. Fortunately, it is.
	*/
	uint64_t i;

	if ((uint64_t)destination % sizeof(uint32_t) == 0 &&
		(uint64_t)source % sizeof(uint32_t) == 0 &&
		length % sizeof(uint32_t) == 0)
	{
		uint32_t *d = (uint32_t *) destination;
		const uint32_t *s = (const uint32_t *)source;

		for (i = 0; i < length / sizeof(uint32_t); i++)
			d[i] = s[i];
	}
	else
	{
		uint8_t * d = (uint8_t*)destination;
		const uint8_t * s = (const uint8_t*)source;

		for (i = 0; i < length; i++)
			d[i] = s[i];
	}

	return destination;
}

void print_message(uint8_t* message, uint8_t mod){
	int i = 0;
	while(message[i] != 0){
		_put_char(message[i],mod);
		i++;
	}
}

void print_number(uint32_t n){
	if(n < 10){
		_put_char(n + '0',0x04);
	}else{
		print_number(n / 10);
		_put_char((n % 10) + '0',0x04);
	}
}
int strcmp(const uint8_t *s1, const uint8_t *s2) {
  int ret = 0;
  while (!(ret = *(uint8_t *) s1 - *(uint8_t *) s2) && *s2) ++s1, ++s2;
  if (ret < 0)
    ret = -1;
  else if (ret > 0)
    ret = 1 ;
  return ret;
}
int strlen(const char * str){
	int size =0;
	for(int i=0;str[i]!=0;i++){
		size++;
	}
	return size;
}

int isNumber(char a){
	if(a=='0' || a=='1' || a=='2' || a=='3' || a=='4' || a=='5' || a=='6' || a=='7' || a=='8' || a=='9')
		return 1;
	else
		return 0;
}

int pow(int x, unsigned int y){
	int resp=1;
	for(int i=1;i<y;i++){
		resp*=x;
	}
	return resp;
}
void putChar(uint8_t c,uint8_t mod){
	_put_char(c,mod);
}

uint8_t BCDtoDecimal(uint8_t num){
	int aux = 0;
	aux = (num >> 4) * 10;
	aux += (num & 15);
	return aux;
}
uint8_t DecimaltoBCD(uint8_t n){
	int result = 0;
	while(n>10){
		result++;
		n -= 10;
	}
	result = (result << 4);
	result += n;
	return result;
}

void printf(const char * string, ...){
	char c;
	va_list listpointer;
	va_start(listpointer, string);
	for(int i=0; string[i] != '\0'; i++){
		c = string[i];
		if(c=='\n'){
			new_line();
		}
		else if(c == '%'){
			switch(string[i+1]){
				case 'd':	print_number(va_arg(listpointer,int));
							i++;
							break;
				case 's':	print_message(va_arg(listpointer,char *), 15);
							i++;
							break;
				default: 	_put_char(string[i], 15);
							break;
			}
		}
		else{
			_put_char(string[i], 15); // 15 para fondo negro letras blancas
		}
	}
	va_end(listpointer);
}