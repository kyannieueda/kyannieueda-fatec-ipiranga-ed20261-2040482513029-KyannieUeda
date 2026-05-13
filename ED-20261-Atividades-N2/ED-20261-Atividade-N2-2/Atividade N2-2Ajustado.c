/*------------------------------------------------------------------*/
/* FATEC-Ipiranga                                                   */
/* ADS - Estrutura de Dados                                         */
/* Id da Atividade: N2-2                                            */
/* Objetivo: Calcular altura e fator de balanceamento em árvore AVL */               
/*                                                                  */
/* Autor: Kyannie Risame Ueda da Mata                               */
/* Data: 12/05/2026                                                 */
/*------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
 
// ============================================================
// Estrutura do Nó
// ============================================================
struct No {
    int valor;
    int altura;
    struct No *esq;
    struct No *dir;
};
 
// ============================================================
// Função auxiliar: retorna o maior entre dois inteiros
// ============================================================
int max(int a, int b) {
    return (a > b) ? a : b;
}
 
// ============================================================
// Função: calcularAltura
// COM printf demonstrando o cálculo a cada nó visitado
// ============================================================
int calcularAltura(struct No* n) {
    if (n == NULL) {
        return -1;
    }
    int alturaEsq = calcularAltura(n->esq);
    int alturaDir = calcularAltura(n->dir);
    int resultado = 1 + max(alturaEsq, alturaDir);
 
    printf("No %2d: 1 + max(H_esq:%d, H_dir:%d) = Altura %d\n",
           n->valor, alturaEsq, alturaDir, resultado);
 
    return resultado;
}
 
// ============================================================
// Função: obterFB (Fator de Balanceamento)
// FB = altura(filho_esq) - altura(filho_dir)
// ============================================================
int obterFB(struct No* n) {
    if (n == NULL) {
        return 0;
    }
    int alturaEsq = calcularAltura(n->esq);
    int alturaDir = calcularAltura(n->dir);
    return alturaEsq - alturaDir;
}
 
// ============================================================
// Função auxiliar: cria um novo nó com o valor informado
// ============================================================
struct No* criarNo(int valor) {
    struct No* novo = (struct No*) malloc(sizeof(struct No));
    novo->valor = valor;
    novo->altura = 0;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}
 
// ============================================================
// Função: inserir
// Insere valor na árvore respeitando a regra BST:
//   menor  → vai para a esquerda
//   maior  → vai para a direita
//   igual  → ignora (sem duplicatas)
// ============================================================
struct No* inserir(struct No* raiz, int valor) {
    if (raiz == NULL) {
        return criarNo(valor);
    }
    if (valor < raiz->valor) {
        printf("  %d < %d -> vai para a ESQUERDA\n", valor, raiz->valor);
        raiz->esq = inserir(raiz->esq, valor);
    } else if (valor > raiz->valor) {
        printf("  %d > %d -> vai para a DIREITA\n", valor, raiz->valor);
        raiz->dir = inserir(raiz->dir, valor);
    } else {
        printf("  %d ja existe na arvore, ignorado.\n", valor);
    }
    return raiz;
}
 
// ============================================================
// Função: liberarArvore
// Libera toda a memória alocada recursivamente
// ============================================================
void liberarArvore(struct No* n) {
    if (n == NULL) return;
    liberarArvore(n->esq);
    liberarArvore(n->dir);
    free(n);
}

int main() {
    int n, valor;
    struct No* raiz = NULL;
 
    printf("=== Arvore Binaria de Busca (BST) ===\n");
    printf("Quantos nos deseja inserir? ");
    scanf("%d", &n);
 
    printf("\n--- Inserindo nos ---\n");
    for (int i = 1; i <= n; i++) {
        printf("Digite o valor do No %d: ", i);
        scanf("%d", &valor);
        raiz = inserir(raiz, valor);
    }
 
    // Calculando e exibindo a altura da árvore completa
    printf("\n=== Calculo de Alturas ===\n");
    printf("\nIniciando Calculos Recursivos ----\n");
    int alturaTotal = calcularAltura(raiz);
    printf("Altura total da arvore (raiz No %d): %d\n", raiz->valor, alturaTotal);
 
    // Calculando e exibindo o FB da raiz
    printf("\n=== Fator de Balanceamento (FB) da Raiz ===\n");
    int fb = obterFB(raiz);
    printf("FB do No %d (raiz): %d", raiz->valor, fb);
    if (fb >= -1 && fb <= 1)
        printf(" -- BALANCEADO\n");
    else
        printf(" -- DESBALANCEADO (AVL requer FB entre -1 e 1)\n");
 
    printf("\n(FB ideal entre -1 e +1. |FB| >= 2 indica desbalanceamento)\n");
 
    // Liberando memória
    liberarArvore(raiz);
 
    return 0;
}
 
