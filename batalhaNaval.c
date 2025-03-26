#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 10
#define NAVIOS 4
#define TAMANHO_NAVIO 3
#define MAR 0
#define NAVIO 3

int tabuleiro[TAMANHO][TAMANHO];

void inicializarTabuleiro() {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = MAR;
        }
    }
}

int podeColocarNavio(int linha, int coluna, int direcao, int diagonal) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int x = linha + (diagonal ? i : (direcao == 1 ? i : 0));
        int y = coluna + (diagonal ? i : (direcao == 0 ? i : 0));

        if (x >= TAMANHO || y >= TAMANHO || tabuleiro[x][y] != MAR) {
            return 0;
        }
    }
    return 1;
}

void colocarNavio(int linha, int coluna, int direcao, int diagonal) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int x = linha + (diagonal ? i : (direcao == 1 ? i : 0));
        int y = coluna + (diagonal ? i : (direcao == 0 ? i : 0));
        tabuleiro[x][y] = NAVIO;
    }
}

void posicionarNavios() {
    srand(time(NULL));
    int colocados = 0;
    
    while (colocados < NAVIOS) {
        int linha = rand() % TAMANHO;
        int coluna = rand() % TAMANHO;
        int diagonal = (colocados >= 2); // Dois primeiros horizontais/verticais, os outros dois diagonais
        int direcao = rand() % 2; // 0 para horizontal, 1 para vertical
        
        if (podeColocarNavio(linha, coluna, direcao, diagonal)) {
            colocarNavio(linha, coluna, direcao, diagonal);
            colocados++;
        }
    }
}

void exibirTabuleiro() {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    inicializarTabuleiro();
    posicionarNavios();
    exibirTabuleiro();
    return 0;
}
