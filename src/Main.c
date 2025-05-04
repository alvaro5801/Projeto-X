#include "../include/screen.h"
#include "../include/keyboard.h"
#include "../include/timer.h"
#include "../include/Batalha.h"
#include "../include/utils.h"
#include "../include/barradevida.h"
#include "../include/bonecos.h"

#include <stdio.h>
#include <unistd.h>

int posicao_X_inimigo = 51;
int posicao_Y_inimigo = 14;
int vida_do_inimigo = 150;
int vida_maxima_do_inimigo = 150;
int posicao_X_inimigo_boneco = 24;
int posicao_Y_inimigo_boneco = 1;

int posicao_X_jogador = 2;
int posicao_Y_jogador = 14;
int vida_Do_jogador = 100;
int vida_Maxima_Do_jogador = 100;
int posicao_X_jogador_boneco = 2;
int posicao_Y_jogador_boneco = 0;

void inicial() {

    inimigoboneco( posicao_X_inimigo_boneco , posicao_Y_inimigo_boneco);
    jogadorboneco( posicao_X_jogador_boneco , posicao_Y_jogador_boneco );
    desenharBarraDeVida( posicao_X_jogador , posicao_Y_jogador , vida_Do_jogador , vida_Maxima_Do_jogador); //Jogador
    desenharBarraDeVida( posicao_X_inimigo , posicao_Y_inimigo , vida_do_inimigo , vida_maxima_do_inimigo); //Inimigo

}



 int main() {

     screenInit(0);
     keyboardInit();

     inicial();

     int atitude = gerenciarTurnoJogador() ;

     vida_do_inimigo = vida_do_inimigo - atitude;

     desenharBarraDeVida( posicao_X_inimigo , posicao_Y_inimigo , vida_do_inimigo , vida_maxima_do_inimigo); //Inimigo


     getchar();
     screenGotoxy(1, MAXY);
     printf("Enter para sair.");
     getchar();

     screenDestroy();
     keyboardDestroy();


 return 0;
 }
