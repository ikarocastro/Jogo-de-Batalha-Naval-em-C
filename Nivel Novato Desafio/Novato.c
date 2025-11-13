#include <stdio.h>

int main() {

        int tabuleiro [10][10];
        int i, j;

        printf("\n====== TABULEIRO BATALHA NAVAL ======\n\n");

        /* inicializa tabuleiro com zeros */
        for (i = 0; i < 10; i++) {
                for (j = 0; j < 10; j++) {
                        tabuleiro[i][j] = 0;
                }
        }

        /* posiciona o navio na linha 3, colunas E-F-G */
        for (j = 4; j <= 6; j++) {  /* colunas E (4), F (5), G (6) */
                tabuleiro[3][j] = 3;    /* linha 3 */
        }

        /* posiciona os números 2 verticalmente nas linhas 6, 7 e 8, coluna H */
        for (i = 6; i <= 8; i++) {  /* linhas 6, 7 e 8 */
                tabuleiro[i][7] = 3;    /* coluna H (7) */
        }


        /* imprime cabeçalho horizontal: letras A-J */
        printf("   "); /* espaço para a coluna dos números */
        for (j = 0; j < 10; j++) {
                printf(" %c", 'A' + j);
        }
        printf("\n");

        /* imprime linhas com número à esquerda e valores do tabuleiro */
        for (i = 0; i < 10; i++) {
                printf("%d  ", i); /* rótulo da linha */
                for (j = 0; j < 10; j++) {
                        printf(" %d", tabuleiro[i][j]);
                }
                printf("\n");
        }


   
        return 0;
}