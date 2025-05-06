#ifndef INIMIGO_H
#define INIMIGO_H

#include <stdbool.h>

typedef struct {
    int vida;
    int vidaMaxima;
    int ataque;
    int defesa;

    // Comportamento do inimigo
    int acoesDisponiveis[4]; // Índices das ações (0: Ataque, 1: Defesa, 2: Cura, 3: Irritar)
    int numAcoesDisponiveis;

    bool podeUsarIrritar; // Flag para controlar se o inimigo pode usar "Irritar"
} Inimigo;

void inicializarInimigo(Inimigo *inimigo, int vida, int ataque, int defesa);
int escolherAcaoInimigo(Inimigo *inimigo);

#endif
