#include <stdio.h>

#define N 10       // Tamanho do tabuleiro
#define NAVIO 3    // Marca do navio
#define TAM 3      // Tamanho de cada navio

// Verifica se o navio pode ser colocado
int podePosicionar(int tab[N][N], int lin, int col, int dLin, int dCol) {
    for(int i = 0; i < TAM; i++) {
        int l = lin + i * dLin;
        int c = col + i * dCol;

        if(l < 0 || l >= N || c < 0 || c >= N) return 0;   // Fora do tabuleiro
        if(tab[l][c] == NAVIO) return 0;                   // Sobreposição
    }
    return 1;
}

// Posiciona o navio depois da validação
void posicionar(int tab[N][N], int lin, int col, int dLin, int dCol) {
    for(int i = 0; i < TAM; i++) {
        tab[lin + i * dLin][col + i * dCol] = NAVIO;
    }
}

int main() {
    int tab[N][N] = {0}; // Inicializa tudo com água (0)


    printf("\n====== TABULEIRO BATALHA NAVAL ======\n");

    // --- Navios retos ---
    if(podePosicionar(tab, 1, 1, 0, 1))  // Horizontal →
        posicionar(tab, 1, 1, 0, 1);

    if(podePosicionar(tab, 4, 6, 1, 0))  // Vertical ↓
        posicionar(tab, 4, 6, 1, 0);

    // --- Navios diagonais ---
    if(podePosicionar(tab, 7, 0, 1, 1))  // Diagonal ↘
        posicionar(tab, 7, 0, 1, 1);

    if(podePosicionar(tab, 0, 9, 1, -1)) // Diagonal ↙
        posicionar(tab, 0, 9, 1, -1);

    // --- Exibe o tabuleiro com coordenadas ---
    printf("\n     ");
    for(int c = 0; c < N; c++) {
        printf("%2d ", c);  // Cabeçalho das colunas
    }
    printf("\n");

    printf("    +");
    for(int c = 0; c < N; c++) printf("---");
    printf("+\n");

    for(int i = 0; i < N; i++) {
        printf("%2d | ", i); // Numeração das linhas
        for(int j = 0; j < N; j++) {
            printf("%d  ", tab[i][j]);
        }
        printf("|\n");
    }

    printf("    +");
    for(int c = 0; c < N; c++) printf("---");
    printf("+\n");

    return 0;
}
