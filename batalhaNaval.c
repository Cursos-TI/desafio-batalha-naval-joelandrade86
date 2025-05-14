#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 10
#define AGUA 0
#define NAVIO 3

// Função para inicializar o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("  ");
    for (int j = 0; j < TAMANHO; j++) {
        printf("%c ", 'A' + j);
    }
    printf("\n");
    for (int i = 0; i < TAMANHO; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < TAMANHO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Função para verificar se uma posição é válida
int posicaoValida(int linha, int coluna) {
    return (linha >= 0 && linha < TAMANHO && coluna >= 0 && coluna < TAMANHO);
}

// Função para verificar se há sobreposição em uma posição
int verificarSobreposicao(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    return (posicaoValida(linha, coluna) && tabuleiro[linha][coluna] == NAVIO);
}

// Função para posicionar um navio horizontalmente
int posicionarNavioHorizontal(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int tamanho) {
    if (coluna + tamanho > TAMANHO) {
        return 0; // Não cabe no tabuleiro
    }
    for (int j = 0; j < tamanho; j++) {
        if (verificarSobreposicao(tabuleiro, linha, coluna + j)) {
            return 0; // Já existe um navio nessa posição
        }
    }
    for (int j = 0; j < tamanho; j++) {
        tabuleiro[linha][coluna + j] = NAVIO;
    }
    return 1; // Posicionamento bem-sucedido
}

// Função para posicionar um navio verticalmente
int posicionarNavioVertical(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int tamanho) {
    if (linha + tamanho > TAMANHO) {
        return 0; // Não cabe no tabuleiro
    }
    for (int i = 0; i < tamanho; i++) {
        if (verificarSobreposicao(tabuleiro, linha + i, coluna)) {
            return 0; // Já existe um navio nessa posição
        }
    }
    for (int i = 0; i < tamanho; i++) {
        tabuleiro[linha + i][coluna] = NAVIO;
    }
    return 1; // Posicionamento bem-sucedido
}

// Função para posicionar um navio na diagonal principal (aumentando linha e coluna)
int posicionarNavioDiagonalPrincipal(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int tamanho) {
    if (linha + tamanho > TAMANHO || coluna + tamanho > TAMANHO) {
        return 0; // Não cabe no tabuleiro
    }
    for (int k = 0; k < tamanho; k++) {
        if (verificarSobreposicao(tabuleiro, linha + k, coluna + k)) {
            return 0; // Já existe um navio nessa posição
        }
    }
    for (int k = 0; k < tamanho; k++) {
        tabuleiro[linha + k][coluna + k] = NAVIO;
    }
    return 1; // Posicionamento bem-sucedido
}

// Função para posicionar um navio na diagonal secundária (aumentando linha e diminuindo coluna)
int posicionarNavioDiagonalSecundaria(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int tamanho) {
    if (linha + tamanho > TAMANHO || coluna - tamanho + 1 < 0) {
        return 0; // Não cabe no tabuleiro
    }
    for (int k = 0; k < tamanho; k++) {
        if (verificarSobreposicao(tabuleiro, linha + k, coluna - k)) {
            return 0; // Já existe um navio nessa posição
        }
    }
    for (int k = 0; k < tamanho; k++) {
        tabuleiro[linha + k][coluna - k] = NAVIO;
    }
    return 1; // Posicionamento bem-sucedido
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];
    srand(time(NULL)); // Inicializa a semente aleatória

    inicializarTabuleiro(tabuleiro);

    int naviosPosicionados = 0;

    // Posicionar dois navios horizontalmente ou verticalmente (tamanho 3 para exemplo)
    while (naviosPosicionados < 2) {
        int orientacao = rand() % 2; // 0 para horizontal, 1 para vertical
        int linha = rand() % TAMANHO;
        int coluna = rand() % TAMANHO;
        int tamanho = 3;

        if (orientacao == 0) {
            if (posicionarNavioHorizontal(tabuleiro, linha, coluna, tamanho)) {
                naviosPosicionados++;
            }
        } else {
            if (posicionarNavioVertical(tabuleiro, linha, coluna, tamanho)) {
                naviosPosicionados++;
            }
        }
    }

    // Posicionar dois navios na diagonal (tamanho 2 para exemplo)
    while (naviosPosicionados < 4) {
        int tipoDiagonal = rand() % 2; // 0 para principal, 1 para secundária
        int linha = rand() % TAMANHO;
        int coluna = rand() % TAMANHO;
        int tamanho = 2;

        if (tipoDiagonal == 0) {
            if (posicionarNavioDiagonalPrincipal(tabuleiro, linha, coluna, tamanho)) {
                naviosPosicionados++;
            }
        } else {
            if (posicionarNavioDiagonalSecundaria(tabuleiro, linha, coluna, tamanho)) {
                naviosPosicionados++;
            }
        }
    }

    exibirTabuleiro(tabuleiro);

    return 0;
}