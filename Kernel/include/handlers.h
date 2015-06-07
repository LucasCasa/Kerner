#ifndef HANDLERS_H_
#define HANDLERS_H_

void timer_handler();
void keyboard_handler(uint8_t scancode);

extern void shell_show_screensaver();
extern void shell_print_standby();

#endif 
