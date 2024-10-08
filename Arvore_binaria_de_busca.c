#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

struct Info{
    char nome[100];
    int mat;
    int turma;
    float nota;
};

struct Node{
    struct Info info;
    struct Node *esq;
    struct Node *dir;
};

struct Info criarInfo(int mat, char *nome, int turma, float nota);
struct Node* criarNode(struct Info info);
int comparar(struct Info a, struct Info b);
struct Node *inserir(struct Node *raiz, struct Info info);
void percorrer_arvores_preordem(struct Node *raiz, int profundidade);
void percorrer_arvores_inordem(struct Node *raiz, int profundidade, char *posicao);
void percorrer_arvores_posordem(struct Node *raiz, int profundidade);
int maior(int a, int b);
int altura(struct Node *raiz);

int main(){

    FILE *arquivo;
    arquivo = fopen("dados.txt", "rt");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    struct Info informacao[100];
    int index = 0;
    int quantidade = 0;
    int mat, turma;
    char nome[100];

    while (fscanf(arquivo, "%d | %[^|] | %d\n", &mat, nome, &turma) == 3) {
        informacao[quantidade] = criarInfo(mat, nome, turma, rand() % 10);
        quantidade++;
        if (quantidade >= 100) {
            break;
        }
    }

    fclose(arquivo);
    /*
    for (index = 0; index < quantidade; index++) {
        printf("%d %s %d %.2f\n", informacao[index].mat, informacao[index].nome, informacao[index].turma, informacao[index].nota);
    }*/
    
    struct Node* raiz = 0;
    for(index = 0; index < quantidade; index++){
        raiz = inserir(raiz, informacao[index]);
    }
    percorrer_arvores_inordem(raiz, 0, "raiz");
    printf("%d\n", altura(raiz));
}

struct Info criarInfo(int mat, char *nome, int turma, float nota){
    struct Info res;
    strcpy(res.nome, nome);
    res.mat = mat;
    res.turma = turma;
    res.nota = nota;
    return res;
}

struct Node* criarNode(struct Info info){
    struct Node* res = (struct Node*)malloc(sizeof(struct Node));
    res->info = info;
    res->dir = 0;
    res->esq = 0;
    return res;
}

int comparar(struct Info a, struct Info b){
    return strcmp(a.nome, b.nome);
}

struct Node *inserir(struct Node *raiz, struct Info info){
    if(raiz == 0){
        return criarNode(info);
    }
    int x = comparar(raiz->info, info);
    if(x < 0){
        raiz->dir = inserir(raiz->dir, info);
    }else if(x > 0){
        raiz->esq = inserir(raiz->esq, info);
    }
    return raiz;
}

int maior(int a, int b) { return a > b ? a : b; }

int altura(struct Node *raiz) {
    if (raiz == 0) {
        return -1;
    } else {
        int he = altura(raiz->esq);
        int hd = altura(raiz->dir);
        return 1 + maior(he, hd);
    }
}

void percorrer_arvores_preordem(struct Node *raiz, int profundidade){
    if (raiz != NULL){
        printf("Nome: %s, Mat: %d, Turma: %d, Nota: %.2f\n", raiz->info.nome, raiz->info.mat, raiz->info.turma, raiz->info.nota);
        percorrer_arvores_preordem(raiz->esq, ++profundidade);
        percorrer_arvores_preordem(raiz->dir, ++profundidade);
    }
}

void percorrer_arvores_posordem(struct Node *raiz, int profundidade){
    if (raiz == NULL){
        return;
    }
    percorrer_arvores_posordem(raiz->esq, ++profundidade);
    percorrer_arvores_posordem(raiz->dir, ++profundidade);
    printf("Nome: %s, Mat: %d, Turma: %d, Nota: %.2f\n", raiz->info.nome, raiz->info.mat, raiz->info.turma, raiz->info.nota);
}

void percorrer_arvores_inordem(struct Node *raiz, int profundidade, char *posicao){
    if (raiz != NULL){
    percorrer_arvores_inordem(raiz->esq, ++profundidade, "esquerda");
    printf("%s ==  Nome: %s, Mat: %d, Turma: %d, Nota: %.2f\n", posicao, raiz->info.nome, raiz->info.mat, raiz->info.turma, raiz->info.nota);
    percorrer_arvores_inordem(raiz->dir, ++profundidade, "direita");
    }
}

// parada no pai do elemento procurado (gdb) b percorrer_arvores_preordem if raiz != 0 && ((raiz->dir && raiz->dir->info.mat == 3 && raiz->dir->info.turma == 2) || (raiz->esq && raiz->esq->info.mat == 3 && raiz->esq->info.turma == 2))
// elemento procurado (gdb) p raiz->dir->info.nome ou p raiz->esq->info.nome     
// filho direito do elemento procurado (gdb) p raiz->dir->dir->info.nome ou p raiz->esq->dir->info.nome
// filho esquerdo do elemento procurado (gdb) p raiz->dir->esq->info.nome ou p raiz->esq->esq->info.nome