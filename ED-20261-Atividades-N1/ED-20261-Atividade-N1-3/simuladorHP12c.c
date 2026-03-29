/*-------------------------------------------------------------------------------------------------*/
/*                                FATEC-Ipiranga                                                   */        
/*                            ADS - Estrutura de Dados                                             */
/*                             Id da Atividade: N1-3                                               */
/* Objetivo: Desenvolveer uma aplicação que simule a HP12c usando estrutura de dados de pilha      */
/*                                                                                                 */
/*                                  Autor: Kyannie da Mata                                         */
/*                                                                   Data:24/03/2026               */
/*-------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 4  // tamanho fixo da pilha (X, Y, Z, T)

// Estrutura da HP12c
typedef struct {
    double stack[MAX]; // vetor que representa a pilha: 0=X, 1=Y, 2=Z, 3=T
} HP12C;

// Inicializa a pilha com zero
void init(HP12C *hp) {
    for (int i = 0; i < MAX; i++) { // percorre todas as posições
        hp->stack[i] = 0; // coloca 0 em cada posição
    }
}

// Mostra o estado atual da pilha
void mostrar(HP12C *hp) {
    printf("T: %.2f | Z: %.2f | Y: %.2f | X: %.2f\n",
           hp->stack[3], // posição T
           hp->stack[2], // posição Z
           hp->stack[1], // posição Y
           hp->stack[0]  // posição X (display)
    );
}

// Função PUSH (insere número na pilha), desloca os valores
void push(HP12C *hp, double valor) {
    hp->stack[3] = hp->stack[2]; // T recebe o valor de Z
    hp->stack[2] = hp->stack[1]; // Z recebe o valor de Y
    hp->stack[1] = hp->stack[0]; // Y recebe o valor de X
    hp->stack[0] = valor;        // X recebe o novo valor digitado
}

// Função para verificar se a entrada é número
int verificarNumero(char *parte) {

    // Se começar com '-' e tiver mais coisa depois, é número negativo
    if (*parte == '-' && *(parte + 1) != '\0') {
        parte++; // pula o sinal e continua verificando
    }

    // Percorre cada caractere da string
    while (*parte) {
        // Se não for número nem ponto, não é válido
        if (!isdigit(*parte) && *parte != '.') {
            return 0; // retorna falso (não é número)
        }
        parte++; // passa para o próximo caractere
    }

    return 1; // se passou por tudo, é número
}

// Função POP, remove o valor de X e reorganiza a pilha
double pop(HP12C *hp) {
    double x = hp->stack[0]; // guarda o valor atual de X

    // Desloca os valores para baixo
    hp->stack[0] = hp->stack[1]; // X recebe Y
    hp->stack[1] = hp->stack[2]; // Y recebe Z
    hp->stack[2] = hp->stack[3]; // Z recebe T
    // T permanece igual

    return x; // retorna o valor que estava em X
}

// Função que realiza as operações matemáticas
void operar(HP12C *hp, char op) {

    double x = pop(hp); // pega o valor de X
    double y = pop(hp); // pega o valor de Y
    double resultado;   // variável para guardar o resultado

    // Verifica qual operação foi digitada
    switch(op) {

        case '+': 
            resultado = y + x;
            break;

        case '-': 
            resultado = y - x;
            break;

        case '*': 
            resultado = y * x;
            break;

        case '/': 
            if (x == 0) { 
                printf("Erro: divisão por zero!\n");
                return;
            }
            resultado = y / x;
            break;

        default: 
            printf("Operador inválido!\n");
            return;
    }

    
    printf("Operação: %.2f %c %.2f = %.2f\n", y, op, x, resultado);

    // Coloca o resultado de volta na pilha
    push(hp, resultado);
}


int main() {

    HP12C hp; // cria a calculadora
    init(&hp); // inicializa a pilha com zeros

    char entrada[200]; // string para guardar a expressão digitada

    printf("Digite a expressao em RPN:\n");
    fgets(entrada, sizeof(entrada), stdin); // lê a entrada do usuário

    // Remove o ENTER do final da string
    entrada[strcspn(entrada, "\n")] = '\0';

    // Divide a string em partes separadas por espaço
    char *parte = strtok(entrada, " ");

    // Enquanto ainda existir parte para processar
    while (parte != NULL) {

        printf("\nEntrada: %s\n", parte); 

        // Se for número
        if (verificarNumero(parte)) {
            double valor = atof(parte); // converte texto para número
            push(&hp, valor); // insere na pilha
        }
        // Se for operador
        else if (strlen(parte) == 1) {
            operar(&hp, parte[0]); // realiza a operação
        }
        // Se não for nenhum dos dois
        else {
            printf("Entrada inválida: %s\n", parte);
            return 1;
        }

        mostrar(&hp); // mostra o estado da pilha após cada passo

        parte = strtok(NULL, " "); // pega a próxima parte
    }

    
    printf("\nResultado final: %.2f\n", hp.stack[0]);

    return 0; 
}