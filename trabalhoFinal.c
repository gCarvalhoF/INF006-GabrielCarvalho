#include <stdio.h>
#include <stdlib.h>

typedef struct Titulo
{
    char sigla[5];
    int qtd;
    char op;
    float valor;
    struct Titulo *prox;

} Titulo;

Titulo *criarTitulo()
{
    Titulo *novo = (Titulo *)malloc(sizeof(Titulo));

    printf("Informe a sigla do titulo: ");
    scanf("%s", novo->sigla);
    getchar();

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

void inserirNaLista(Titulo **inicioLista)
{
    Titulo *current ;
    Titulo *novo;

    current = *inicioLista;
    novo = criarTitulo();

    if (current == NULL)
        *inicioLista = novo;
    else
    {
        while (current->prox != NULL)
            current = current->prox;
        current->prox = novo;
    }
}

void listarTitulos(Titulo *inicioLista)
{
    Titulo *current;

    current = inicioLista;

    do
    {
        printf("%s ", current->sigla);
        printf("%c ", current->op);
        printf("%d ", current->qtd);
        printf("R$ %.2f\n", current->valor);

        current = current->prox;
    } while (current != NULL);
}

void main()
{
    Titulo *inicioCompra = NULL;
    Titulo *inicioVenda = NULL;
    int opcao = -1;

    while (opcao != 0)
    {
        printf("Menu \n");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            inserirNaLista(&inicioCompra);
            break;
        case 2:
            listarTitulos(inicioCompra);
            break;

        default:
            break;
        }
    }
}