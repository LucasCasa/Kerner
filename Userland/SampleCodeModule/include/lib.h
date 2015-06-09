#ifndef LIB_H
#define LIB_H

#include <stdint.h>

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

int isNumber(char a);

void print_message(char* message, uint8_t mod);
void print_number(uint32_t n);

int strcmp(char *s1, char *s2);
int atoi(char * string);
int strlen(const char * str);
int isNumber(char a);
int pow(int x, unsigned int y);
void putChar(uint8_t c,uint8_t mod);
void printf(const char * string, uint8_t mod, ...);
char get_char();

#endif