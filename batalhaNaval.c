#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 10
#define NAVIOS 4
#define TAMANHO_NAVIO 3
#define MAR 0
#define NAVIO 3
#define HABILIDADE 5

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

void aplicarHabilidade(int origemX, int origemY, int tipo) {
    int efeito[5][5] = {0};
    
    switch (tipo) {
        case 1: // Cone
            efeito[0][2] = 1;
            efeito[1][1] = efeito[1][2] = efeito[1][3] = 1;
            efeito[2][0] = efeito[2][1] = efeito[2][2] = efeito[2][3] = efeito[2][4] = 1;
            break;
        case 2: // Cruz
            efeito[0][2] = efeito[1][2] = efeito[2][0] = efeito[2][1] = efeito[2][2] = efeito[2][3] = efeito[2][4] = efeito[3][2] = efeito[4][2] = 1;
            break;
        case 3: // Octaedro
            efeito[0][2] = efeito[1][1] = efeito[1][3] = efeito[2][0] = efeito[2][1] = efeito[2][2] = efeito[2][3] = efeito[2][4] = efeito[3][1] = efeito[3][3] = efeito[4][2] = 1;
            break;
    }
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int x = origemX + i - 2;
            int y = origemY + j - 2;
            if (x >= 0 && x < TAMANHO && y >= 0 && y < TAMANHO && efeito[i][j] == 1) {
                if (tabuleiro[x][y] != NAVIO) {
                    tabuleiro[x][y] = HABILIDADE;
                }
            }
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
    
    // Aplicação de habilidades
    aplicarHabilidade(4, 4, 1); // Cone
    aplicarHabilidade(7, 7, 2); // Cruz
    aplicarHabilidade(2, 2, 3); // Octaedro
    
    exibirTabuleiro();
    return 0;
}
