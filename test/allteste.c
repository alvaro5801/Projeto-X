#include "../include/screen.h"
#include "../include/keyboard.h"
#include "../include/timer.h"
#include "../include/Batalha.h"
#include "../include/utils.h"
#include "../include/barradevida.h"


#include <stdio.h>
#include <unistd.h>

int main() {

    int posicao_X_inimigo = 51;
    int posicao_Y_inimigo = 14;
    int vida_do_inimigo = 150;
    int vida_maxima_do_inimigo = 150;

    int posicao_X_jogador = 2;
    int posicao_Y_jogador = 14;
    int vida_Do_jogador = 100;
    int vida_Maxima_Do_jogador = 100;

    screenInit(0);
    keyboardInit();


    desenharBarraDeVida( posicao_X_jogador , posicao_Y_jogador , vida_Do_jogador , vida_Maxima_Do_jogador); //Jogador
    desenharBarraDeVida( posicao_X_inimigo , posicao_Y_inimigo , vida_do_inimigo , vida_maxima_do_inimigo); //Inimigo
    int dano = gerenciarTurnoJogador() ;

    vida_do_inimigo = vida_do_inimigo - dano;
    desenharBarraDeVida( posicao_X_inimigo , posicao_Y_inimigo , vida_do_inimigo , vida_maxima_do_inimigo); //Inimigo

    screenGotoxy(1, MAXY);
    printf("Enter para sair.");
    getchar();

    screenDestroy();
    keyboardDestroy();


    return 0;
}
