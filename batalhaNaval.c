#include <stdio.h>

#define TAM 10         // Tamanho do tabuleiro 10x10
#define NAVIO 3        // Valor representando parte de navio
#define AGUA 0         // Valor representando água
#define HABILIDADE 5   // Valor para representar a área de efeito da habilidade
#define TAM_HABIL 5    // Tamanho das matrizes de habilidade (5x5)

// Verifica se está dentro dos limites do tabuleiro
int dentro_limites(int linha, int coluna) {
    return linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM;
}

// Verifica se um navio pode ser colocado sem sair do tabuleiro ou sobrepor outro
int pode_colocar_navio(int tab[TAM][TAM], int lin, int col, int d_l, int d_c) {
    for (int i = 0; i < NAVIO; i++) {
        int l = lin + i * d_l;
        int c = col + i * d_c;
        if (!dentro_limites(l, c) || tab[l][c] == NAVIO)
            return 0;
    }
    return 1;
}

// Coloca um navio no tabuleiro
void colocar_navio(int tab[TAM][TAM], int lin, int col, int d_l, int d_c) {
    for (int i = 0; i < NAVIO; i++) {
        int l = lin + i * d_l;
        int c = col + i * d_c;
        tab[l][c] = NAVIO;
    }
}

// Cria uma matriz cone (topo fino, base larga)
void criar_matriz_cone(int mat[TAM_HABIL][TAM_HABIL]) {
    for (int i = 0; i < TAM_HABIL; i++) {
        for (int j = 0; j < TAM_HABIL; j++) {
            if (j >= (TAM_HABIL / 2 - i) && j <= (TAM_HABIL / 2 + i))
                mat[i][j] = 1;
            else
                mat[i][j] = 0;
        }
    }
}

// Cria uma matriz cruz (linha e coluna central ativadas)
void criar_matriz_cruz(int mat[TAM_HABIL][TAM_HABIL]) {
    for (int i = 0; i < TAM_HABIL; i++) {
        for (int j = 0; j < TAM_HABIL; j++) {
            if (i == TAM_HABIL / 2 || j == TAM_HABIL / 2)
                mat[i][j] = 1;
            else
                mat[i][j] = 0;
        }
    }
}

// Cria uma matriz octaedro (losango)
void criar_matriz_octaedro(int mat[TAM_HABIL][TAM_HABIL]) {
    for (int i = 0; i < TAM_HABIL; i++) {
        for (int j = 0; j < TAM_HABIL; j++) {
            if (abs(i - TAM_HABIL / 2) + abs(j - TAM_HABIL / 2) <= TAM_HABIL / 2)
                mat[i][j] = 1;
            else
                mat[i][j] = 0;
        }
    }
}

// Aplica uma matriz de habilidade sobre o tabuleiro centralizada no ponto dado
void aplicar_habilidade(int tab[TAM][TAM], int origem_l, int origem_c, int matriz[TAM_HABIL][TAM_HABIL]) {
    for (int i = 0; i < TAM_HABIL; i++) {
        for (int j = 0; j < TAM_HABIL; j++) {
            int l = origem_l + i - TAM_HABIL / 2;
            int c = origem_c + j - TAM_HABIL / 2;
            if (dentro_limites(l, c) && matriz[i][j] == 1 && tab[l][c] == AGUA) {
                tab[l][c] = HABILIDADE;
            }
        }
    }
}

// Imprime o tabuleiro de forma clara
void imprimir_tabuleiro(int tab[TAM][TAM]) {
    printf("\nLegenda: 0 = Água | 3 = Navio | 5 = Habilidade\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM][TAM] = {0}; // Inicializa tabuleiro com água

    // ------ POSICIONANDO OS NAVIOS --------
    if (pode_colocar_navio(tabuleiro, 1, 1, 0, 1)) // horizontal
        colocar_navio(tabuleiro, 1, 1, 0, 1);
    if (pode_colocar_navio(tabuleiro, 5, 2, 1, 0)) // vertical
        colocar_navio(tabuleiro, 5, 2, 1, 0);
    if (pode_colocar_navio(tabuleiro, 0, 0, 1, 1)) // diagonal principal
        colocar_navio(tabuleiro, 0, 0, 1, 1);
    if (pode_colocar_navio(tabuleiro, 0, 9, 1, -1)) // diagonal secundária
        colocar_navio(tabuleiro, 0, 9, 1, -1);

    // ------ MATRIZES DE HABILIDADE --------
    int cone[TAM_HABIL][TAM_HABIL];
    int cruz[TAM_HABIL][TAM_HABIL];
    int octaedro[TAM_HABIL][TAM_HABIL];

    criar_matriz_cone(cone);
    criar_matriz_cruz(cruz);
    criar_matriz_octaedro(octaedro);

    // ------ APLICANDO AS HABILIDADES --------
    aplicar_habilidade(tabuleiro, 6, 6, cone);       // Aplica cone centrado em (6,6)
    aplicar_habilidade(tabuleiro, 3, 3, cruz);       // Aplica cruz centrado em (3,3)
    aplicar_habilidade(tabuleiro, 8, 2, octaedro);   // Aplica octaedro centrado em (8,2)

    // ------ IMPRIMIR RESULTADO FINAL --------
    imprimir_tabuleiro(tabuleiro);

    return 0;
}