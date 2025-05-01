#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/timer.h"
#include "../include/screen.h"
#include "../include/keyboard.h"

#include "../include/Dado.h"

int main() {
    screenInit(0);
    keyboardInit();

    int dado1 = 0;
    int dado2 = 0;

    printf("Rolando os dados...\n");
    for (int i = 0; i < 2; i++) {
        if (i == 0) {
            dado1 = rolarDado20();
        } else { // i == 1
            dado2 = rolarDado20();
        }

        usleep(50000);
    }

    printf("\nValores guardados:\n");
    printf("Dado 1: %d\n", dado1);
    printf("Dado 2: %d\n", dado2);

    printf("\nEnter para sair.\n");
    getchar();

    screenDestroy();
    keyboardDestroy();
    timerDestroy();

    return 0;
}
