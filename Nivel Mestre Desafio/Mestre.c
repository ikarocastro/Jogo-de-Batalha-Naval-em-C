#include <stdio.h>
#include <string.h>

/*
  Batalha Naval - Habilidades com Áreas de Efeito
  - Tabuleiro 10x10
  - Navios representados com valor 3
  - Áreas afetadas por habilidades representadas com valor 5
  - Água = 0
  - Matrizes de habilidade usam 0/1 e são construídas dinamicamente com loops e condicionais.
*/

/* Tamanho do tabuleiro */
#define ROWS 10
#define COLS 10

/* Tamanho das matrizes de habilidade (usar tamanho ímpar facilita o centramento) */
#define SKILL_N 5   /* 5x5 é suficiente para os exemplos (pode trocar por 7 se quiser) */

/* Códigos no tabuleiro */
#define WATER 0
#define SHIP 3
#define AFFECTED 5

/* Função para inicializar tabuleiro com água (0) */
void init_board(int board[ROWS][COLS]) {
    int r, c;
    for (r = 0; r < ROWS; ++r)
        for (c = 0; c < COLS; ++c)
            board[r][c] = WATER;
}

/* Exemplo simples: posiciona alguns navios fixos (valores 3) para visualização */
void place_example_ships(int board[ROWS][COLS]) {
    /* Navio horizontal de tamanho 4 */
    board[1][2] = SHIP;
    board[1][3] = SHIP;
    board[1][4] = SHIP;
    board[1][5] = SHIP;

    /* Navio vertical de tamanho 3 */
    board[4][7] = SHIP;
    board[5][7] = SHIP;
    board[6][7] = SHIP;

    /* Submarino (single cell) */
    board[8][1] = SHIP;
}

/* Constrói uma matriz 5x5 que representa um CONE apontando para baixo.
   Lógica: para cada linha r (0..n-1), preencher colunas entre mid - r e mid + r (expansão para baixo).
   Usa condicionais dentro de loops aninhados. */
void build_cone(int cone[SKILL_N][SKILL_N]) {
    int n = SKILL_N;
    int mid = n / 2; /* posição do meio (coluna do "topo" do cone) */
    /* Inicializa com 0 */
    for (int r = 0; r < n; ++r)
        for (int c = 0; c < n; ++c)
            cone[r][c] = 0;

    /* Construção dinâmica do cone */
    for (int r = 0; r < n; ++r) {
        /* Largura do cone na linha r: de mid - r até mid + r (limitado pelos índices válidos) */
        int left = mid - r;
        int right = mid + r;
        for (int c = 0; c < n; ++c) {
            if (c >= left && c <= right) {
                /* Marcamos como 1 (afetado) */
                cone[r][c] = 1;
            } else {
                cone[r][c] = 0;
            }
        }
    }
}

/* Constrói uma matriz 5x5 que representa uma CRUZ com origem no centro.
   Lógica: marcar toda a linha central e toda a coluna central. */
void build_cross(int cross[SKILL_N][SKILL_N]) {
    int n = SKILL_N;
    int mid = n / 2;
    for (int r = 0; r < n; ++r)
        for (int c = 0; c < n; ++c)
            cross[r][c] = 0;

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            /* Se estiver na linha central OU na coluna central -> 1 */
            if (r == mid || c == mid) cross[r][c] = 1;
            else cross[r][c] = 0;
        }
    }
}

/* Constrói uma matriz 5x5 que representa a vista frontal de um octaedro (um LOSANGO/diamante).
   Lógica: pontos cuja distância de Manhattan ao centro <= radius (aqui radius = mid). */
void build_octahedron(int oct[SKILL_N][SKILL_N]) {
    int n = SKILL_N;
    int mid = n / 2;
    int radius = mid; /* Para 5x5, radius = 2 */
    for (int r = 0; r < n; ++r)
        for (int c = 0; c < n; ++c)
            oct[r][c] = 0;

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            int manhattan = (r > mid ? r - mid : mid - r) + (c > mid ? c - mid : mid - c);
            if (manhattan <= radius) oct[r][c] = 1;
            else oct[r][c] = 0;
        }
    }
}

/* Sobrepõe uma matriz de habilidade (valores 0/1) ao tabuleiro, centrando a matriz
   no ponto de origem (orig_r, orig_c). A sobreposição respeita limites do tabuleiro.
   Regras visuais:
    - se board[r][c] == SHIP (3), mantemos 3 (priorizamos mostrar o navio)
    - se board[r][c] != SHIP e skill == 1, marcamos como AFFECTED (5)
*/
void overlay_skill(int board[ROWS][COLS], int skill[SKILL_N][SKILL_N], int orig_r, int orig_c) {
    int n = SKILL_N;
    int mid = n / 2;

    /* top-left no tabuleiro onde a skill[0][0] iria */
    int top = orig_r - mid;
    int left = orig_c - mid;

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            if (skill[r][c] == 1) {
                int board_r = top + r;
                int board_c = left + c;
                /* Verifica limites do tabuleiro */
                if (board_r >= 0 && board_r < ROWS && board_c >= 0 && board_c < COLS) {
                    /* Só sobrescreve se não for navio (3). Mantemos navio visualmente. */
                    if (board[board_r][board_c] != SHIP) {
                        board[board_r][board_c] = AFFECTED;
                    }
                }
            }
        }
    }
}

/* Função para imprimir o tabuleiro no console.
   Mostra números (0 água, 3 navio, 5 área afetada) com uma legenda. */
void print_board(int board[ROWS][COLS]) {
    printf("Legenda: 0=agua  3=navio  5=area_afetada\n\n");
    printf("   "); /* Cabeçalho colunas */
    int c;
    for (c = 0; c < COLS; ++c) printf("%2d ", c);
    printf("\n");
    int r;
    for (r = 0; r < ROWS; ++r) {
        printf("%2d ", r); /* Cabeçalho linhas */
        for (c = 0; c < COLS; ++c) {
            printf("%2d ", board[r][c]);
        }
        printf("\n");
    }
}

/* Imprime uma matriz de habilidade (0/1) para debug/visualização */
void print_skill_matrix(int skill[SKILL_N][SKILL_N], const char *name) {
    printf("\nMatriz de habilidade: %s (%dx%d)\n", name, SKILL_N, SKILL_N);
    for (int r = 0; r < SKILL_N; ++r) {
        for (int c = 0; c < SKILL_N; ++c) {
            printf("%d ", skill[r][c]);
        }
        printf("\n");
    }
}

int main() {
    int board[ROWS][COLS];
    init_board(board);
    place_example_ships(board);

    /* Matrizes de habilidade (0/1) */
    int cone[SKILL_N][SKILL_N];
    int cross[SKILL_N][SKILL_N];
    int octa[SKILL_N][SKILL_N];

    /* Constroi as matrizes dinamicamente com loops e condicionais */
    build_cone(cone);
    build_cross(cross);
    build_octahedron(octa);

    /* Para fins de demonstração, imprimimos as matrizes de habilidade no console */
    print_skill_matrix(cone, "CONE (apontando para baixo)");
    print_skill_matrix(cross, "CRUZ (origem centro)");
    print_skill_matrix(octa, "OCTAHEDRO / LOSANGO (vista frontal)");

    /* Pontos de origem no tabuleiro (definidos no código conforme simplificação)
       - Cada origem é (linha, coluna) */
    int origin_cone_r = 0, origin_cone_c = 4;   /* cone no topo, centralizado col 4 */
    int origin_cross_r = 3, origin_cross_c = 2; /* cruz centrada em (3,2) */
    int origin_octa_r = 5, origin_octa_c = 5;  /* octaedro no centro-ish */

    /* Sobrepõe as habilidades ao tabuleiro (com validação de limites internamente) */
    overlay_skill(board, cone, origin_cone_r, origin_cone_c);
    overlay_skill(board, cross, origin_cross_r, origin_cross_c);
    overlay_skill(board, octa, origin_octa_r, origin_octa_c);

    /* Exibe o tabuleiro final */
    printf("\nTabuleiro com navios (3) e areas de habilidade (5):\n\n");
    print_board(board);

    return 0;
}
