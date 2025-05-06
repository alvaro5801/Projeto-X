// Dentro de src/inimigo.c (crie este arquivo)
#include "../include/inimigo.h"
#include "../include/Dado.h" // Para rolar o dado

#include <stdlib.h> // Para rand()

void inicializarInimigo(Inimigo *inimigo, int vida, int ataque, int defesa) {
    inimigo->vida = vida;
    inimigo->vidaMaxima = vida;
    inimigo->ataque = ataque;
    inimigo->defesa = defesa;


    // Inicializar ações disponíveis
    inimigo->acoesDisponiveis[0] = 0; // Ataque
    inimigo->acoesDisponiveis[1] = 1; // Defesa
    inimigo->numAcoesDisponiveis = 2;

    inimigo->podeUsarIrritar = false; // Inimigo começa sem poder usar "Irritar"
}

int escolherAcaoInimigo(Inimigo *inimigo) {
    // Lógica para o inimigo escolher uma ação
    if (inimigo->numAcoesDisponiveis == 0) {
        return -1; // Inimigo não pode agir (paralisado)
    }
    int indiceAcao = rand() % inimigo->numAcoesDisponiveis;
    return inimigo->acoesDisponiveis[indiceAcao];
}
