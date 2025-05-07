#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define o tamanho do tabuleiro
#define TAMANHO 10

// Define o tamanho dos navios
#define TAMANHO_NAVIO 3

// Funções para o jogo
void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]);
void posicionarNavios(int tabuleiro[TAMANHO][TAMANHO], int navioHorizontal[TAMANHO_NAVIO], int navioVertical[TAMANHO_NAVIO]);
void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]);
int verificarPosicaoValida(int linha, int coluna);
int verificarSobreposicao(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int tamanho, int orientacao);

int main() {
    // Representa o tabuleiro
    int tabuleiro[TAMANHO][TAMANHO];

    // Representa os navios
    int navioHorizontal[TAMANHO_NAVIO] = {3, 3, 3};
    int navioVertical[TAMANHO_NAVIO] = {3, 3, 3};

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Inicializa o tabuleiro com água (0)
    inicializarTabuleiro(tabuleiro);

    // Posiciona os navios no tabuleiro
    posicionarNavios(tabuleiro, navioHorizontal, navioVertical);

    // Exibe o tabuleiro com os navios posicionados
    printf("Tabuleiro com os navios posicionados:\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}

// Função para inicializar o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = 0; // 0 representa água
        }
    }
}

// Função para verificar se uma posição está dentro dos limites do tabuleiro
int verificarPosicaoValida(int linha, int coluna) {
    return (linha >= 0 && linha < TAMANHO && coluna >= 0 && coluna < TAMANHO);
}

// Função para verificar se há sobreposição ao posicionar um navio
int verificarSobreposicao(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int tamanho, int orientacao) {
    if (orientacao == 0) { // Horizontal
        for (int i = 0; i < tamanho; i++) {
            if (!verificarPosicaoValida(linha, coluna + i) || tabuleiro[linha][coluna + i] == 3) {
                return 1; // Há sobreposição ou posição inválida
            }
        }
    } else { // Vertical
        for (int i = 0; i < tamanho; i++) {
            if (!verificarPosicaoValida(linha + i, coluna) || tabuleiro[linha + i][coluna] == 3) {
                return 1; // Há sobreposição ou posição inválida
            }
        }
    }
    return 0; // Sem sobreposição
}

// Função para posicionar os navios aleatoriamente no tabuleiro
void posicionarNavios(int tabuleiro[TAMANHO][TAMANHO], int navioHorizontal[TAMANHO_NAVIO], int navioVertical[TAMANHO_NAVIO]) {
    int linha, coluna, orientacao;

    // Posiciona o navio horizontalmente
    do {
        linha = rand() % TAMANHO;
        coluna = rand() % (TAMANHO - TAMANHO_NAVIO + 1); // Garante que o navio caiba horizontalmente
        orientacao = 0; // 0 para horizontal
    } while (verificarSobreposicao(tabuleiro, linha, coluna, TAMANHO_NAVIO, orientacao));

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha][coluna + i] = 3;
    }

    // Posiciona o navio verticalmente
    do {
        linha = rand() % (TAMANHO - TAMANHO_NAVIO + 1); // Garante que o navio caiba verticalmente
        coluna = rand() % TAMANHO;
        orientacao = 1; // 1 para vertical
    } while (verificarSobreposicao(tabuleiro, linha, coluna, TAMANHO_NAVIO, orientacao));

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna] = 3;
    }
}

// Função para exibir o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    // Imprime os cabeçalhos das colunas (A, B, C...)
    printf("  ");
    for (int j = 0; j < TAMANHO; j++) {
        printf("%c ", 'A' + j);
    }
    printf("\n");

    // Imprime o tabuleiro
    for (int i = 0; i < TAMANHO; i++) {
        printf("%2d ", i + 1); // Imprime os números das linhas
        for (int j = 0; j < TAMANHO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}