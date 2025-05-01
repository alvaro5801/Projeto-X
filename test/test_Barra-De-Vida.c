#include <stdio.h>
#include "../include/screen.h"
#include "../include/keyboard.h"
#include "../include/timer.h"

#include "../include/Batalha.h"

#include <unistd.h>

int main() {
    screenInit(0);
    keyboardInit();
    timerInit(1000); // Initial timer interval (1 second)

    int vidaJogador = 100;
    int vidaMaximaJogador = 100;
    int tempoPassado = 0;
    int timerInterval = 1000; // Current timer interval
    int timerSpeed = 1;      // 1 = normal, >1 = speed up, <1 = slow down
    int paused = 0;          // 0 = not paused, 1 = paused

    while (vidaJogador > 0) {
        screenClear(); // Clear the screen before drawing
        desenharBarraDeVida(10, 5, vidaJogador, vidaMaximaJogador);
        screenUpdate();

        if (!paused) {
            if (timerTimeOver()) {
                vidaJogador -= 1;
                tempoPassado++;
                timerUpdateTimer(timerInterval);
                //printf("Tempo: %d, Vida: %d, Interval: %d, Speed: %d, Paused: %d\n",
                //       tempoPassado, vidaJogador, timerInterval, timerSpeed, paused); // Debug
            }
        }

        // Handle keyboard input
        if (keyhit()) {
            int key = readch();
            switch (key) {
                case 'p': // Pause/Resume
                    paused = !paused;
                    break;
                case 'o': // Speed up
                    if (timerInterval > 100) {
                        timerInterval -= 100;
                        timerSpeed++;
                        timerUpdateTimer(timerInterval); // Update timer immediately
                    }
                    break;
                case 'l': // Slow down
                    if (timerInterval < 5000) {
                        timerInterval += 100;
                        timerSpeed--;
                        timerUpdateTimer(timerInterval); // Update timer immediately
                    }
                    break;
                case 'q': // Quit
                    vidaJogador = 0; // Force game over
                    break;
            }
        }

        usleep(10000); // Small delay to control loop speed
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
