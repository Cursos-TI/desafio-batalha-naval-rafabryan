#include <stdio.h>

#define TAMANHO 10
#define NAVIO 3

void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = 0; // Representando água
        }
    }
}

void imprimirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int posicionarNavioHorizontal(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    if (coluna + NAVIO > TAMANHO) return 0; // Verifica se cabe no tabuleiro
    for (int i = 0; i < NAVIO; i++) {
        if (tabuleiro[linha][coluna + i] != 0) return 0; // Verifica sobreposição
    }
    for (int i = 0; i < NAVIO; i++) {
        tabuleiro[linha][coluna + i] = 3; // Marca posição do navio
    }
    return 1;
}

int posicionarNavioVertical(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    if (linha + NAVIO > TAMANHO) return 0; // Verifica se cabe no tabuleiro
    for (int i = 0; i < NAVIO; i++) {
        if (tabuleiro[linha + i][coluna] != 0) return 0; // Verifica sobreposição
    }
    for (int i = 0; i < NAVIO; i++) {
        tabuleiro[linha + i][coluna] = 3; // Marca posição do navio
    }
    return 1;
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];
    inicializarTabuleiro(tabuleiro);

    // Definição fixa das posições iniciais dos navios
    int linhaH = 2, colunaH = 4;
    int linhaV = 5, colunaV = 6;
    
    if (!posicionarNavioHorizontal(tabuleiro, linhaH, colunaH)) {
        printf("Falha ao posicionar navio horizontal!\n");
    }
    if (!posicionarNavioVertical(tabuleiro, linhaV, colunaV)) {
        printf("Falha ao posicionar navio vertical!\n");
    }

    imprimirTabuleiro(tabuleiro);
    return 0;
}

