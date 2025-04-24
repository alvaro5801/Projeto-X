#include <stdio.h>
#include "../include/screen.h"
#include "../include/keyboard.h"
#include "../include/timer.h"

#include "../include/Batalha.h"

#include <unistd.h>

int main() {
    screenInit(0);
    keyboardInit();
    timerInit(1000); // Intervalo de 1 segundo

    int vidaJogador = 100;
    int vidaMaximaJogador = 100;
    int tempoPassado = 0;
    int timerInterval = 1000; // Intervalo de 1 segundo
    int timerSpeed = 1;      // 1 = normal, >1 = acelerar, <1 = desacelerar
    int paused = 0;          // 0 = não pausa, 1 = pausa

    while (vidaJogador > 0) {
        screenClear(); // Clear
        desenharBarraDeVida(10, 5, vidaJogador, vidaMaximaJogador);
        screenUpdate();

        if (!paused) {
            if (timerTimeOver()) {
                vidaJogador -= 1;
                tempoPassado++;
                timerUpdateTimer(timerInterval);
                //printf("Tempo: %d, Vida: %d, Interval: %d, Speed: %d, Paused: %d\n", tempoPassado, vidaJogador, timerInterval, timerSpeed, paused); // Debug
            }
        }

        //  tecla de entrada
        if (keyhit()) {
            int key = readch();
            switch (key) {/Resume
                    paused = !paused;
                    break;
                case 'o': // Speed up
                    if (timerInterval > 100) {
                        timerInterval -= 100;
                        timerSpeed++;
                        timerUpdateTimer(timerInterval);// atualiza o cronometro
                    }
                    break;
                case 'l': // deminuir a velocidade
                    if (timerInterval < 5000) {
                        timerInterval += 100;
                        timerSpeed--;
                        timerUpdateTimer(timerInterval); // atualiza o cronometro
                    }
                    break;
                case 'q': // Quit
                    vidaJogador = 0; // Force game over
                    break;
            }
        }

        usleep(10000); // Controla a velocidade do loop
    }

    screenClear();
    desenharBarraDeVida(10, 5, vidaJogador, vidaMaximaJogador);
    screenUpdate();

    if (vidaJogador <= 0) {
        printf("\nPerdeu!\n");
    } else {
        printf("\nFim.\n");
    }

    printf("Enter para sair.");
    getchar();

    screenDestroy();
    keyboardDestroy();
    timerDestroy();

    return 0;
}
