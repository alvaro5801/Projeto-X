#include "../include/screen.h"
#include "../include/keyboard.h"
#include "../include/timer.h"
#include "../include/Batalha.h"
#include "../include/utils.h"

#include <stdio.h>
#include <unistd.h>

 int main() {

 screenInit(0);
 keyboardInit();


 gerenciarTurnoJogador();

 screenGotoxy(1, MAXY);
 printf("Enter para sair.             ");
 getchar();

 screenDestroy();
 keyboardDestroy();


 return 0;
 }
