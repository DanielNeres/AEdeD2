#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 50000


void calcularPulos(int *pulo, char *pat, int m) {
    int i;
    for (i = 0; i < 256; i++) {
        pulo[i] = m; 
    }
    for (i = 0; i < m - 1; i++) {
        pulo[(unsigned char)pat[i]] = m - i - 1; 
    }
}

int main() {
    char string[MAX + 1];
    int comp = 0;
    FILE *arquivo = fopen("Pi.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    char *matricula = "20230114"; 
    int matricula_len = strlen(matricula);

    int pulo[256];
    calcularPulos(pulo, matricula, matricula_len); 

    int N = 0, limit = 50000000; 
    short achou = 0;

    while (N < limit && !achou) {
        size_t bytesLidos = fread(string, 1, MAX, arquivo);
        string[bytesLidos] = '\0'; 

        int i = 0;
        while (i <= bytesLidos - matricula_len) {
            int j = matricula_len - 1;

        
            while (j >= 0 && string[i + j] == matricula[j]) {
                comp++;
                j--;
            }

            if (j < 0) {
                achou = 1;
                printf("Matricula encontrada na posicao: %d\n", N + i);
                break;
            } else {
                i += pulo[(unsigned char)string[i + j]];
            }
        }

        N += bytesLidos;
        if (bytesLidos < MAX) {
            break;
        }
    }

    if (!achou) {
        printf("Matricula nao encontrada.\n");
    }
    printf("%d", comp);

    fclose(arquivo);
    return 0;
}
