#ifndef SYS_H_
#define SYS_H_

#include "stdint.h"

#define WRITE 1
#define DEL_CHAR 2
#define SCR_CHAR 3
#define GET_MOD 4
#define ERASE_SCR 5
#define GET_STR 6
#define GET_CHAR 7
#define RTC_READ 8
#define RTC_WRITE 9
#define COLORS 10

char read(char* buff, char size);
char read_char();
char sys_manager(int order, uint64_t arg1, uint64_t arg2);

#endif