#ifndef VIDEO_MANAGER_H
#define VIDEO_MANAGER_H

static uint8_t * const video = (uint8_t*)0xB8000;
static uint8_t * currentVideo = (uint8_t*)0xB8000;
static uint8_t * saved_current_video;
static char * command_line = 0xB8000;

char str_modifier = 0x02;
char num_modifier = 0x04;

char* saved_shell[160*25];
char saved_modifier;

void sys_write(char c,uint8_t mod);
char sys_get_screen_char();
void sys_delete_char();
void modifie(char mod);
char check_end_of_screen();
void set_default_modifiers(char s, char n);
void set_new_modifier();
void draw_new_line();
void reset_current_video();
void save_screen();
void restore_screen();
void new_line();
void scroll();
void erase_screen();
void print_standby();
void show_screensaver();


#endif VIDEO_MANAGER_H
