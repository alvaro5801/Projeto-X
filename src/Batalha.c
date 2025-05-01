#include "../include/Batalha.h"
#include "../include/screen.h"
#include "../include/keyboard.h"
#include "../include/timer.h"

#include <stdio.h>
#include <unistd.h>

// Definições de tamanho e posição da *área total* da box com borda
//Tamanho 80x24
#define OPCOES_BOX_START_X 5
#define OPCOES_BOX_START_Y 16
#define OPCOES_BOX_WIDTH   70 // Largura total, incluindo as bordas verticais
#define OPCOES_BOX_HEIGHT  7  // Altura total, incluindo as bordas horizontais

// --- Funções tampa burraco--- retorna somente o resultado se vai da dano, diminuir o dano etc..
void realizarAtaque() {
    screenGotoxy(OPCOES_BOX_START_X, OPCOES_BOX_START_Y + OPCOES_BOX_HEIGHT + 1);
    screenSetColor(WHITE, BLACK);
    printf("Atacou!           ");
    screenUpdate();
    usleep(1000000);
}

void realizarDefesa() {
    screenGotoxy(OPCOES_BOX_START_X, OPCOES_BOX_START_Y + OPCOES_BOX_HEIGHT + 1);
    screenSetColor(WHITE, BLACK);
    printf("Você defendeu!          ");
    screenUpdate();
    usleep(1000000);
}

void realizarCura() {
    screenGotoxy(OPCOES_BOX_START_X, OPCOES_BOX_START_Y + OPCOES_BOX_HEIGHT + 1);
    screenSetColor(WHITE, BLACK);
    printf("Se curou!          ");
    screenUpdate();
    usleep(1000000);
}

void realizarIrritar() {
    screenGotoxy(OPCOES_BOX_START_X, OPCOES_BOX_START_Y + OPCOES_BOX_HEIGHT + 1);
    screenSetColor(WHITE, BLACK);
    printf("Irritou o inimigo! ");
    screenUpdate();
    usleep(1000000);
}
// --------------------------------------------------------
