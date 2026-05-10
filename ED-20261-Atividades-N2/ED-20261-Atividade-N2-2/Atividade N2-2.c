/*------------------------------------------------------------------*/
/* FATEC-Ipiranga                                                   */
/* ADS - Estrutura de Dados                                         */
/* Id da Atividade: N2-2                                            */
/* Objetivo: Calcular altura e fator de balanceamento em árvore AVL */               
/*                                                                  */
/* Autor: Kyannie Risame Ueda da Mata                               */
/* Data: 09/05/2026                                                 */
/*------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>


// Estrutura do Nó
struct No {
    int valor;
    int altura;
    struct No *esq;
    struct No *dir;
};

// Função auxiliar: retorna o maior entre dois inteiros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Função: calcularAltura
// Caso base: nó NULL retorna -1
// Caso recursivo: 1 + max(altura_esq, altura_dir)
int calcularAltura(struct No* n) {
    if (n == NULL) {
        return -1;
    }
    int alturaEsq = calcularAltura(n->esq);
    int alturaDir = calcularAltura(n->dir);
    return 1 + max(alturaEsq, alturaDir);
}


// Função: obterFB (Fator de Balanceamento)
// FB = altura(filho_esq) - altura(filho_dir)
int obterFB(struct No* n) {
    if (n == NULL) {
        return 0;
    }
    int alturaEsq = calcularAltura(n->esq);
    int alturaDir = calcularAltura(n->dir);
    return alturaEsq - alturaDir;
}


// Função auxiliar: cria um novo nó com o valor informado
struct No* criarNo(int valor) {
    struct No* novo = (struct No*) malloc(sizeof(struct No));
    novo->valor = valor;
    novo->altura = 0;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

int main() {
    // Criando os nós
    struct No* no20 = criarNo(20);
    struct No* no10 = criarNo(10);
    struct No* no5  = criarNo(5);
    struct No* no2  = criarNo(2);

    // Conectando os nós: linha reta à esquerda
    no20->esq = no10;
    no10->esq = no5;
    no5->esq  = no2;
    // Todos os ponteiros ->dir permanecem NULL

    // Calculando e exibindo a altura de cada nó
    printf("=== Calculo de Alturas ===\n");
    printf("Altura do No 2  (folha): %d\n", calcularAltura(no2));
    printf("Altura do No 5        : %d\n", calcularAltura(no5));
    printf("Altura do No 10       : %d\n", calcularAltura(no10));
    printf("Altura do No 20 (raiz): %d\n", calcularAltura(no20));

    // Calculando e exibindo o FB de cada nó
    printf("\n=== Fator de Balanceamento (FB) ===\n");
    printf("FB do No 2  : %d\n", obterFB(no2));
    printf("FB do No 5  : %d\n", obterFB(no5));
    printf("FB do No 10 : %d\n", obterFB(no10));
    printf("FB do No 20 : %d  <-- Desbalanceado!\n", obterFB(no20));

    printf("\n(FB ideal entre -1 e +1. |FB| >= 2 indica desbalanceamento)\n");

    // Liberando memória alocada
    free(no2);
    free(no5);
    free(no10);
    free(no20);

    return 0;
}
