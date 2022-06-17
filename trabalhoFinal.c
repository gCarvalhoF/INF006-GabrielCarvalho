#include <stdio.h>
#include <stdlib.h>

typedef struct Titulo
{
    int qtd;
    char op;
    float valor;
    struct Titulo *prox;

} Titulo;

Titulo *criarTitulo()
{
    Titulo *novo = (Titulo *)malloc(sizeof(Titulo));

    printf("Informe a quantidade de titulos: ");
    scanf("%d", &novo->qtd);
    getchar();

    printf("Informe o tipo de operacao (c - compra / v - venda): ");
    scanf("%c", &novo->op);

    printf("Informe o preco da operacao: R$");
    scanf("%f", &novo->valor);

    novo->prox = NULL;

    return novo;
}

int inserirNaLista()
{
    // Titulo *current = *inicioLista;
    Titulo *novo = criarTitulo();

    printf("%d -", novo->qtd);
    // if (current == NULL)
    //     *inicioLista = novo;
}

void main()
{
    inserirNaLista();
}