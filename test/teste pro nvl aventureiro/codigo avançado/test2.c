#include <stdio.h>

#define N 10         // Tamanho do tabuleiro (10x10)
#define SHIP_SIZE 3  // Tamanho fixo dos navios
#define EMPTY 0
#define SHIP 3

// Orientações possíveis para posicionamento
typedef enum {
    HORIZONTAL,    // linha fixa, coluna aumenta
    VERTICAL,      // coluna fixa, linha aumenta
    DIAG_DOWN_RIGHT, // linha e coluna aumentam (↘)
    DIAG_DOWN_LEFT   // linha aumenta, coluna diminui (↙)
} Orientation;

/*
 * Verifica se um navio pode ser colocado nas coordenadas (row,col) com
 * determinada orientação e tamanho, sem sair do tabuleiro e sem sobreposição.
 * Retorna 1 se válido, 0 caso contrário.
 */
int can_place(int board[N][N], int row, int col, Orientation orient) {
    for (int i = 0; i < SHIP_SIZE; ++i) {
        int r = row;
        int c = col;
        if (orient == HORIZONTAL) {
            c = col + i;
            r = row;
        } else if (orient == VERTICAL) {
            r = row + i;
            c = col;
        } else if (orient == DIAG_DOWN_RIGHT) {
            r = row + i;
            c = col + i;
        } else if (orient == DIAG_DOWN_LEFT) {
            r = row + i;
            c = col - i;
        }

        // verificar limites
        if (r < 0 || r >= N || c < 0 || c >= N) return 0;

        // verificar sobreposição
        if (board[r][c] != EMPTY) return 0;
    }
    return 1;
}

/*
 * Coloca o navio (assume que can_place já foi checado). Marca as posições com SHIP (3).
 */
void place_ship(int board[N][N], int row, int col, Orientation orient) {
    for (int i = 0; i < SHIP_SIZE; ++i) {
        int r = row;
        int c = col;
        if (orient == HORIZONTAL) {
            c = col + i;
        } else if (orient == VERTICAL) {
            r = row + i;
        } else if (orient == DIAG_DOWN_RIGHT) {
            r = row + i;
            c = col + i;
        } else if (orient == DIAG_DOWN_LEFT) {
            r = row + i;
            c = col - i;
        }
        board[r][c] = SHIP;
    }
}

/*
 * Função para imprimir o tabuleiro.
 * Mostra índices de linha e coluna para facilitar visualização.
 */
void print_board(int board[N][N]) {
    printf("   ");
    for (int c = 0; c < N; ++c) printf("%2d ", c);
    printf("\n");

    printf("  +");
    for (int c = 0; c < N; ++c) printf("---");
    printf("+\n");

    for (int r = 0; r < N; ++r) {
        printf("%2d|", r);
        for (int c = 0; c < N; ++c) {
            // imprime 0 (água) ou 3 (navio) com espaçamento
            printf(" %d ", board[r][c]);
        }
        printf("|\n");
    }

    printf("  +");
    for (int c = 0; c < N; ++c) printf("---");
    printf("+\n");
}

int main(void) {
    // Inicializa tabuleiro 10x10 com zeros (água)
    int board[N][N] = { {0} };

    // Escolhi coordenadas fixas (conforme simplificações do enunciado).
    // Garanto que os navios não saem do tabuleiro e não se sobrepõem.
    // Você pode alterar estas coordenadas se quiser testar outros posicionamentos.

    // Navio 1: Horizontal (linha 1, col 1 -> col 1,2,3)
    int r1 = 1, c1 = 1;
    Orientation o1 = HORIZONTAL;

    // Navio 2: Vertical (linha 4 -> 4,5,6; coluna 6)
    int r2 = 4, c2 = 6;
    Orientation o2 = VERTICAL;

    // Navio 3: Diagonal descendo para a direita (↘)
    // Ex.: começa em (7,0) -> (7,0),(8,1),(9,2)
    int r3 = 7, c3 = 0;
    Orientation o3 = DIAG_DOWN_RIGHT;

    // Navio 4: Diagonal descendo para a esquerda (↙)
    // Ex.: começa em (0,9) -> (0,9),(1,8),(2,7)
    int r4 = 0, c4 = 9;
    Orientation o4 = DIAG_DOWN_LEFT;

    // Vetor de navios para iteração
    int starts_r[4] = {r1, r2, r3, r4};
    int starts_c[4] = {c1, c2, c3, c4};
    Orientation orients[4] = {o1, o2, o3, o4};

    // Tentar posicionar cada navio com validação
    for (int i = 0; i < 4; ++i) {
        if (!can_place(board, starts_r[i], starts_c[i], orients[i])) {
            // Caso raro com as coordenadas escolhidas:
            printf("ERRO: nao foi possivel posicionar o navio %d na posicao (%d,%d) com orientacao %d\n",
                   i+1, starts_r[i], starts_c[i], orients[i]);
            return 1; // encerra com erro
        }
        place_ship(board, starts_r[i], starts_c[i], orients[i]);
    }

    // Exibe o tabuleiro final
    print_board(board);

    return 0;
}
