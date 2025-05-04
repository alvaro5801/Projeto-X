#include "../include/screen.h"
#include "../include/keyboard.h"
#include "../include/timer.h"
#include "../include/Batalha.h"
#include "../include/visual.h"

#include <stdio.h>
#include <unistd.h>

// Definições de tamanho e posição da *área total* da box com borda
//Tamanho 80x24
#define OPCOES_BOX_START_X 5
#define OPCOES_BOX_START_Y 16
#define OPCOES_BOX_WIDTH   70 // Largura total, incluindo as bordas verticais
#define OPCOES_BOX_HEIGHT  7  // Altura total, incluindo as bordas horizontais

int gerenciarTurnoJogador() {
    int key = 0;

    // Desenhar a linha divisória
    screenSetColor(LIGHTGRAY, BLACK);
    screenGotoxy(1, 15); // Posição Y da linha
    for (int i = 0; i < MAXX; i++) {
        printf("-");
    }
    screenSetColor(WHITE, BLACK); // Reseta a cor

    desenharBoxOpcoes(); // Desenha a box com contorno e as opções dentro
    screenUpdate();      // Atualiza a tela

    while (1) {
        if (keyhit()) {
            key = readch();

            switch (key) {
                case 'q':
                case 'Q':

                    return realizarAtaque();

                case 'w':
                case 'W':

                    return realizarDefesa();

                case 'e':
                case 'E':

                    return realizarCura();

                case 'r':
                case 'R':
                    realizarIrritar();
                    return realizarIrritar();

                case 'x':
                case 'X':
                    screenGotoxy(OPCOES_BOX_START_X, OPCOES_BOX_START_Y + OPCOES_BOX_HEIGHT + 1);
                    screenSetColor(WHITE, BLACK);
                    printf("Saindo da batalha...");
                    screenUpdate();
                    usleep(1000000);
                    return 0;
            }
        }
        usleep(10000);
    }
}
