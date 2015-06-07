#ifndef SHELL_H_

#define SHELL_H_

typedef struct {
  char* name;
  char* description;
  void(* function)();
  
} Command;


void * memset(void * destiny, int32_t c, uint64_t length);
void init_commands(char index, char * name, char* description, void (*function)());
void showRTC();
void shell_command();
void shell_erase_screen();
void _shutdown_asm();
void changeTime();
void shell_show_commands();
void shell_exit();
void whoami();
void show_keyboard();
void modifie_colors();

const char* time_str = "Muestra el reloj";
const char* help_str = "Muestra comandos disponibles";
const char* change_time_str = "Cambia la fecha y hora del sistema";
const char* whoami_str = "Dice quien eres";
const char* keyboard_str = "Muestra la distribucion de las teclas";
const char* modi_str = "Cambiar colores de la consola";
const char* clear_str = "Borra la pantalla";

#endif