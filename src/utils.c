#include "../include/screen.h"
#include "../include/keyboard.h"
#include "../include/timer.h"
#include "../include/Batalha.h"
#include "../include/visual.h"
#include "../include/inimigo.h"
#include "../include/barradevida.h"
#include "../include/utils.h"

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#define OPCOES_BOX_START_X 5
#define OPCOES_BOX_START_Y 16
#define OPCOES_BOX_WIDTH   70
#define OPCOES_BOX_HEIGHT  7

int gerenciarTurnoJogador(Inimigo *inimigo, int *vidaJogador, int *vidaInimigo) {
    int key = 0;
    int danoJogador = 0;
    int resultadoTurno = 1; // 1: continuar, 0: sair da batalha
    bool jogadorAgir = true;  // Flag para controlar o turno (true = jogador, false = inimigo)
    int vidaMaximaJogador = 100; // Assumindo 100, ajuste se for diferente

    while (*vidaJogador > 0 && *vidaInimigo > 0) {

        // --- Redesenhar Interface ---
        desenharBoxOpcoes(); // Desenha a caixa de opções

        // Limpa linhas de status antigas
        screenGotoxy(OPCOES_BOX_START_X, OPCOES_BOX_START_Y + OPCOES_BOX_HEIGHT + 1);
        printf("                                                            "); // Linha para status jogador
        screenGotoxy(OPCOES_BOX_START_X, OPCOES_BOX_START_Y + OPCOES_BOX_HEIGHT + 2);
        printf("                                                            "); // Linha para status inimigo

        // Atualiza barras de vida (desenhar sempre, mesmo antes da ação)
        desenharBarraDeVida(2, 14, *vidaJogador, vidaMaximaJogador); // Jogador
        desenharBarraDeVida(51, 14, *vidaInimigo, inimigo->vidaMaxima); // Inimigo
        screenUpdate(); // Mostra barras atualizadas e box

        // --- Turno do Jogador ---
        if (jogadorAgir) {
            screenGotoxy(OPCOES_BOX_START_X, OPCOES_BOX_START_Y + OPCOES_BOX_HEIGHT + 1);
            screenSetColor(WHITE, BLACK);
            printf("Sua vez! Escolha (Q:Atk, W:Def, E:Cura, R:Irrita, X:Sair): ");
            screenUpdate(); // Mostra o prompt

            key = 0; // Reseta tecla
            while (key == 0) { // Loop de espera por input válido
                if (keyhit()) {
                    key = readch();
                    screenGotoxy(OPCOES_BOX_START_X, OPCOES_BOX_START_Y + OPCOES_BOX_HEIGHT + 1); // Posiciona para msg de ação
                    screenSetColor(WHITE, BLACK); // Cor para mensagem de ação

                    switch (key) {
                        case 'q': case 'Q':
                            danoJogador = realizarAtaque(); // Função retorna o dano/resultado do dado
                            *vidaInimigo -= danoJogador; // Aplica o dano
                            if (*vidaInimigo < 0) *vidaInimigo = 0; // Garante que vida não fique negativa
                            printf("Você atacou! Dano causado: %d. Vida Inimigo: %d/%d     ", danoJogador, *vidaInimigo, inimigo->vidaMaxima);
                        jogadorAgir = false; // Passa o turno
                        break;
                        case 'w': case 'W':
                            // A função realizarDefesa() apenas mostra msg no seu código atual.
                            realizarDefesa(); // Mostra a mensagem "Você defendeu!"
                            printf("Você se prepara para defender no próximo turno!          "); // Mensagem mais clara
                            // Aqui você poderia setar uma flag, ex: bool jogadorDefendendo = true;
                            jogadorAgir = false; // Passa o turno
                            break;
                        case 'e': case 'E':
                        { // Bloco para variável local 'cura'
                            int cura = realizarCura(); // Função retorna valor do dado
                            *vidaJogador += cura; // Adiciona cura à vida
                            if (*vidaJogador > vidaMaximaJogador) *vidaJogador = vidaMaximaJogador; // Limita à vida máxima
                            printf("Você se curou em %d! Vida atual: %d/%d           ", cura, *vidaJogador, vidaMaximaJogador);
                            jogadorAgir = false; // Passa o turno
                        }
                        break;
                        case 'r': case 'R':
                            realizarIrritar(); // Mostra mensagem "Irritou o inimigo!"
                            printf("Você irritou o inimigo! Ele parece mais nervoso...       ");
                            //inimigo->podeUsarIrritar = true;
                            jogadorAgir = false; // Passa o turno
                            break;
                        case 'x': case 'X':
                            printf("Saindo da batalha...                                   ");
                            screenUpdate();
                            usleep(1000000);
                            return 0; // Sai da função e da batalha
                        default:
                            key = 0; // Tecla inválida, continua esperando
                            printf("Tecla inválida! Use Q, W, E, R ou X.                   ");
                            screenUpdate();
                            usleep(500000);
                            // Re-exibe prompt após erro
                            screenGotoxy(OPCOES_BOX_START_X, OPCOES_BOX_START_Y + OPCOES_BOX_HEIGHT + 1);
                            screenSetColor(WHITE, BLACK);
                            printf("Sua vez! Escolha (Q:Atk, W:Def, E:Cura, R:Irrita, X:Sair): ");
                            screenUpdate();
                            break; // Volta para o loop while(key==0)
                    }
                }
                usleep(50000); // Pausa curta no loop de espera
            }

            screenUpdate(); // Garante que a mensagem da ação seja exibida
            usleep(1500000); // Pausa de 1.5s para ler o resultado da ação do jogador

        }

        // --- Verificar Fim de Jogo após ação do Jogador ---
        if (*vidaInimigo <= 0 || *vidaJogador <= 0) {
            break; // Sai do loop principal da batalha
        }

        // --- Turno do Inimigo ---
        if (!jogadorAgir) { // Executa somente se o jogador acabou de agir
            executarTurnoInimigo(inimigo, vidaJogador); // Função executa a ação e imprime status
            jogadorAgir = true; // Devolve o turno para o jogador na próxima iteração
            screenUpdate(); // Mostra a ação do inimigo
            usleep(1500000); // Pausa de 1.5s para ler a ação do inimigo
        }

        // --- Verificar Fim de Jogo após ação do Inimigo ---
        if (*vidaInimigo <= 0 || *vidaJogador <= 0) {
            break; // Sai do loop principal da batalha
        }

    }
    // --- Fim da Batalha ---
    screenGotoxy(OPCOES_BOX_START_X, OPCOES_BOX_START_Y + OPCOES_BOX_HEIGHT + 3); // Posição para mensagem final
    screenSetColor(YELLOW, BLACK); // Destaca a mensagem final
    if (*vidaJogador <= 0) {
        printf("VOCÊ FOI DERROTADO! Pressione Enter para sair.             ");
        resultadoTurno = 0; // Derrota
    } else if (*vidaInimigo <= 0) {
        printf("VOCÊ VENCEU A BATALHA! Pressione Enter para sair.          ");
        resultadoTurno = 1; // Vitória
    } else {
        printf("Batalha interrompida. Pressione Enter para sair.         ");
        resultadoTurno = 0;
    }
    screenUpdate();

    // Espera um Enter para finalizar e limpar a tela
    fflush(stdin);
    while (readch() != '\n'); // Espera pela tecla Enter

    return resultadoTurno;
}

// Função auxiliar para o turno do inimigo
void executarTurnoInimigo(Inimigo *inimigo, int *vidaJogador) {
    int acaoInimigo = escolherAcaoInimigo(inimigo);
    int dano = 0;
    int vidaMaximaJogador = 100;

    screenGotoxy(OPCOES_BOX_START_X, OPCOES_BOX_START_Y + OPCOES_BOX_HEIGHT + 2); // Linha de status do inimigo
    screenSetColor(LIGHTRED, BLACK); // Cor para ação inimiga

    switch (acaoInimigo) {
        case 0: // Ataque Inimigo
            dano = realizarAtaque();
            // Lógica de defesa do jogador deveria ser aplicada aqui se W foi usado antes
            *vidaJogador -= dano;
            if (*vidaJogador < 0) *vidaJogador = 0;
            printf("Inimigo atacou! Dano recebido: %d. Sua Vida: %d/%d     ", dano, *vidaJogador, vidaMaximaJogador);
        break;
        case 1: // Defesa Inimigo
            realizarDefesa(); // Apenas mostra mensagem no código atual
            printf("Inimigo se defende, parecendo mais resistente!          ");
            break;
        case 2: // Cura Inimigo
        {
            int cura = realizarCura();
            inimigo->vida += cura;
            if (inimigo->vida > inimigo->vidaMaxima) inimigo->vida = inimigo->vidaMaxima;
            printf("Inimigo se curou em %d! Vida Inimigo: %d/%d         ", cura, inimigo->vida, inimigo->vidaMaxima);
        }
        break;
        case 3: // Irritar Inimigo
            realizarIrritar();
            printf("Inimigo tenta te irritar! Mantenha a calma!             ");
            break;
        case -1: // Inimigo não pode agir
            printf("Inimigo está atordoado ou não pode agir!                ");
            break;
        default:
            printf("Ação desconhecida do inimigo. Algo estranho aconteceu. ");
            break;
    }
}
