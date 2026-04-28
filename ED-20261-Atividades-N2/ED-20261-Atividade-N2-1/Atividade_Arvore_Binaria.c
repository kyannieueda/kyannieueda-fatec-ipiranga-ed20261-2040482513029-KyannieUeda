/*--------------------------------------------------*/
/* FATEC-Ipiranga                                   */ 
/* ADS - Estrutura de Dados                         */
/* Id da Atividade: N2-1                            */
/* Objetivo: Explorar Árvore Binária                */
/*                                                  */
/* Autor: Kyannie Risame Ueda da Mata               */
/* Data: 28/04/2026                                 */
/*--------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

/*Estrutura do nó*/
typedef struct No {
    int valor;
    struct No *esq;
    struct No *dir;
} No;

/*Criação de inserção*/
No *criarNo(int valor) {
    No *novo = (No *)malloc(sizeof(No));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

No *inserir(No *raiz, int valor) {
    if (raiz == NULL) return criarNo(valor);
    if (valor < raiz->valor)
        raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->valor)
        raiz->dir = inserir(raiz->dir, valor);
    return raiz;
}

/* Função de criação da Raiz */
void exibirRaiz(No *raiz) {
    printf("==================================================\n");
    printf("RAIZ:\n");
    if (raiz != NULL)
        printf("  %d\n", raiz->valor);
    else
        printf("  (árvore vazia)\n");
}

/* Função de criação de nós internos */
void exibirNosInternos(No *no) {
    if (no == NULL) return;
    if (no->esq != NULL || no->dir != NULL)
        printf("  %d\n", no->valor);
    exibirNosInternos(no->esq);
    exibirNosInternos(no->dir);
}

/* Função de criação de nós externos */
void exibirFolhas(No *no) {
    if (no == NULL) return;
    if (no->esq == NULL && no->dir == NULL)
        printf("  %d\n", no->valor);
    exibirFolhas(no->esq);
    exibirFolhas(no->dir);
}

/* Níveis - Conta quantos nós existem em um nível específico */
int contarNivel(No *no, int nivelAtual, int nivelAlvo) {
    if (no == NULL) return 0;
    if (nivelAtual == nivelAlvo) return 1;
    return contarNivel(no->esq, nivelAtual + 1, nivelAlvo) +
           contarNivel(no->dir, nivelAtual + 1, nivelAlvo);
}

/* Imprime os valores de todos os nós em um nível específico */
void imprimirNosDoNivel(No *no, int nivelAtual, int nivelAlvo) {
    if (no == NULL) return;
    if (nivelAtual == nivelAlvo) {
        printf("  %d\n", no->valor);
        return;
    }
    imprimirNosDoNivel(no->esq, nivelAtual + 1, nivelAlvo);
    imprimirNosDoNivel(no->dir, nivelAtual + 1, nivelAlvo);
}

/* Calcula a altura da árvore (número de níveis) */
int altura(No *no) {
    if (no == NULL) return 0;
    int altEsq = altura(no->esq);
    int altDir = altura(no->dir);
    return 1 + (altEsq > altDir ? altEsq : altDir);
}

/*Função para exibir os níveis*/
void exibirNiveis(No *raiz) {
    printf("==================================================\n");
    printf("NÍVEIS:\n");
    int totalNiveis = altura(raiz);
    for (int nivel = 1; nivel <= 7; nivel++) {
        printf("  Nível %d:", nivel);
        if (nivel > totalNiveis || contarNivel(raiz, 1, nivel) == 0) {
            printf(" (vazio)\n");
        } else {
            printf("\n");
            imprimirNosDoNivel(raiz, 1, nivel);
        }
    }
}

/* Grau de cada nó */
int calcularGrau(No *no) {
    if (no == NULL) return -1;
    int grau = 0;
    if (no->esq != NULL) grau++;
    if (no->dir != NULL) grau++;
    return grau;
}

/*Função para exibir os graus*/
void exibirGraus(No *no) {
    if (no == NULL) return;
    printf("  %d → grau %d\n", no->valor, calcularGrau(no));
    exibirGraus(no->esq);
    exibirGraus(no->dir);
}

/*Ancestrais*/
/* Retorna 1 se encontrou o valor; imprime o caminho de volta (ancestrais) */
int exibirAncestral(No *no, int valorAlvo) {
    if (no == NULL) return 0;
    if (no->valor == valorAlvo) return 1;
    if (exibirAncestral(no->esq, valorAlvo) ||
        exibirAncestral(no->dir, valorAlvo)) {
        printf("  %d\n", no->valor);
        return 1;
    }
    return 0;
}

/*Descendentes*/
/* Primeiro localiza o nó; depois imprime toda a subárvore (exceto a raiz) */
No *buscarNo(No *no, int valor) {
    if (no == NULL) return NULL;
    if (no->valor == valor) return no;
    No *resultado = buscarNo(no->esq, valor);
    if (resultado != NULL) return resultado;
    return buscarNo(no->dir, valor);
}

void exibirDescendentes(No *no, int imprimirRaiz) {
    if (no == NULL) return;
    if (!imprimirRaiz) {          /* pula a própria raiz da busca */
        exibirDescendentes(no->esq, 1);
        exibirDescendentes(no->dir, 1);
        return;
    }
    printf("  %d\n", no->valor);
    exibirDescendentes(no->esq, 1);
    exibirDescendentes(no->dir, 1);
}

/* Altura de um determinado nó*/
int alturaDono(No *raiz, int valor) {
    No *alvo = buscarNo(raiz, valor);
    if (alvo == NULL) return -1;
    return altura(alvo) - 1;   /* altura da subárvore - 1 */
}

/* Profundidade de um determinado nó */
int profundidade(No *no, int valor, int nivel) {
    if (no == NULL) return -1;
    if (no->valor == valor) return nivel;
    int esq = profundidade(no->esq, valor, nivel + 1);
    if (esq != -1) return esq;
    return profundidade(no->dir, valor, nivel + 1);
}

/* Sub-árvore */
void exibirSubArvore(No *no, char *prefixo, int ehFilhoDir) {
    if (no == NULL) return;

    /* Imprime o prefixo acumulado + conector */
    printf("%s", prefixo);
    if (ehFilhoDir == -1) {           /* raiz da sub-árvore */
        printf("%d\n", no->valor);
    } else if (ehFilhoDir) {
        printf("└── %d\n", no->valor);
    } else {
        printf("├── %d\n", no->valor);
    }

    /* Monta novo prefixo para os filhos */
    char novoPrefixo[256];
    if (ehFilhoDir == -1) {
        snprintf(novoPrefixo, sizeof(novoPrefixo), "%s", prefixo);
    } else if (ehFilhoDir) {
        snprintf(novoPrefixo, sizeof(novoPrefixo), "%s    ", prefixo);
    } else {
        snprintf(novoPrefixo, sizeof(novoPrefixo), "%s│   ", prefixo);
    }

    if (no->esq != NULL || no->dir != NULL) {
        if (no->esq != NULL)
            exibirSubArvore(no->esq, novoPrefixo, 0);
        if (no->dir != NULL)
            exibirSubArvore(no->dir, novoPrefixo, 1);
    }
}
