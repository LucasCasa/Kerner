#ifndef LIB_H
#define LIB_H

#include <stdint.h>

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

int isNumber(char a);

void print_message(uint8_t* message, uint8_t mod);
void print_number(uint32_t n);

int strcmp(const uint8_t *s1, const uint8_t *s2);
int atoi(char * string);
int strlen(const char * str);
int isNumber(char a);
int pow(int x, unsigned int y);
void putChar(uint8_t c,uint8_t mod);
void printf(const char * string, ...);
char get_char();

#endif