#include <stdio.h>
#include <stdlib.h>

typedef struct No {
  int chave;
  struct No *esq;
  struct No *dir;
  int altura;
} No;

int altura(No *n) {
  if (n == NULL)
    return 0;
  return n->altura;
}

int maximo(int a, int b) { return (a > b) ? a : b; }

No *novoNo(int chave) {
  No *no = (No *)malloc(sizeof(No));
  no->chave = chave;
  no->esq = NULL;
  no->dir = NULL;
  no->altura = 1;
  return (no);
}

No *rotacaodir(No *y) {
  No *x = y->esq;
  No *aux = x->dir;

  x->dir = y;
  y->esq = aux;

  y->altura = maximo(altura(y->esq), altura(y->dir)) + 1;
  x->altura = maximo(altura(x->esq), altura(x->dir)) + 1;

  return x;
}

No *rotacaoesq(No *x) {
  No *y = x->dir;
  No *aux = y->esq;

  y->esq = x;
  x->dir = aux;

  x->altura = maximo(altura(x->esq), altura(x->dir)) + 1;
  y->altura = maximo(altura(y->esq), altura(y->dir)) + 1;

  return y;
}

int obterBalanceamento(No *n) {
  if (n == NULL)
    return 0;
  return altura(n->esq) - altura(n->dir);
}

No *inserir(No *no, int chave) {
  if (no == NULL)
    return (novoNo(chave));

  if (chave < no->chave)
    no->esq = inserir(no->esq, chave);
  else if (chave > no->chave)
    no->dir = inserir(no->dir, chave);
  else {
    return no;
  }

  no->altura = 1 + maximo(altura(no->esq), altura(no->dir));

  int balanceamento = obterBalanceamento(no);

  if (balanceamento > 1 && chave < no->esq->chave)
    return rotacaodir(no);

  if (balanceamento < -1 && chave > no->dir->chave)
    return rotacaoesq(no);

  if (balanceamento > 1 && chave > no->esq->chave) {
    no->esq = rotacaoesq(no->esq);
    return rotacaodir(no);
  }
  if (balanceamento < -1 && chave < no->dir->chave) {
    no->dir = rotacaodir(no->dir);
    return rotacaoesq(no);
  }
  return no;
}

void preOrdem(No *raiz) {
  if (raiz != NULL) {
    printf("%d ", raiz->chave);
    preOrdem(raiz->esq);
    preOrdem(raiz->dir);
  }
}

int main() {
  No *raiz = NULL;
  raiz = inserir(raiz, 10);
  raiz = inserir(raiz, 20);
  raiz = inserir(raiz, 30);
  raiz = inserir(raiz, 40);
  raiz = inserir(raiz, 50);
  raiz = inserir(raiz, 60);
  raiz = inserir(raiz, 55);

  printf("Preordem da árvore AVL é: \n");
  preOrdem(raiz);

  return 0;
}