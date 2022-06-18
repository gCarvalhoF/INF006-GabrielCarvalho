#include <stdio.h>
#include <stdlib.h>
typedef struct Acao
{
    char tipo;
    float valor;
    int qtd;
    struct Acao *prox;
} Acao;

typedef struct Titulo
{
    int id;
    char sigla[5];
    Acao *compra;
    Acao *venda;
    float cotacao;
    struct Titulo *prox;

} Titulo;

// Funções referentes aos titulos
Titulo *criarTitulo()
{
    Titulo *novo = (Titulo *)malloc(sizeof(Titulo));

    printf("Informe a sigla do titulo: ");
    scanf("%s", novo->sigla);
    getchar();

    novo->id = 0;
    novo->cotacao = 0;
    novo->compra = NULL;
    novo->venda = NULL;
    novo->prox = NULL;

    return novo;
}

void inserirTitulo(Titulo **inicioLista)
{
    Titulo *current;
    Titulo *novo;

    current = *inicioLista;
    novo = criarTitulo();

    if (current == NULL)
        *inicioLista = novo;
    else
    {
        while (current->prox != NULL)
            current = current->prox;
        novo->id = current->id + 1;
        current->prox = novo;
    }
}

Titulo **getTituloById(int id, Titulo **inicioLista)
{
    Titulo *current = *inicioLista;

    while (current != NULL)
    {
        if (current->id == id)
            break;

        current = current->prox;
    }

    return current;
}

void listarTitulos(Titulo *inicioLista)
{
    Titulo *current;

    current = inicioLista;

    do
    {
        printf("%d - %s \n", current->id, current->sigla);

        current = current->prox;
    } while (current != NULL);
}

// Funções referentes às operações (Compra e Venda)

Acao *criarOperacao()
{
    Acao *novaOperacao = (Acao *)malloc(sizeof(Acao));

    printf("Informe o tipo de operacao (c - compra / v - Venda): ");
    scanf("%c", &novaOperacao->tipo);

    printf("Informe o valor da operacao: R$");
    scanf("%f", &novaOperacao->valor);

    printf("Informe a quantidade de titulos: ");
    scanf("%d", &novaOperacao->qtd);

    novaOperacao->prox = NULL;

    return novaOperacao;
}

void inserirOperacao(int id, Titulo **inicioTitulos)
{
    Titulo *title;
    title = getTituloById(id, inicioTitulos);

    Acao *novaOperacao;
    novaOperacao = criarOperacao();
    Acao *current = NULL;

    if (novaOperacao->tipo == 'c')
    {
        if (title->compra == NULL)
        {
            title->compra = novaOperacao;
        }
        else
            current = title->compra;
    }
    else
    {
        if (title->compra == NULL)
        {
            title->compra = novaOperacao;
        }
        else
            current = title->compra;
    }

    if (current != NULL)
    {
        while (current->prox != NULL)
            current = current->prox;
        current->prox = novaOperacao;
    }
}

void listarOperacoes(Acao *inicioLista)
{
    Acao *current;

    current = inicioLista;

    do
    {
        printf("%d - %c \n", current->valor, current->tipo);

        current = current->prox;
    } while (current != NULL);
}

void main()
{
    Titulo *inicioTitulos = NULL;
    Titulo *titulo;
    int id = -1;
    int opcao = -1, opcaoSecundaria = -1;

    while (opcao != 0)
    {
        printf("Menu \n");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            inserirTitulo(&inicioTitulos);
            break;

        case 2:
            listarTitulos(inicioTitulos);
            break;

        case 3:
            listarTitulos(inicioTitulos);
            printf("Qual titulo deseja operar? ->");
            scanf("%d", &id);
            getchar();

            inserirOperacao(id, &inicioTitulos);
            break;

        case 4:
            listarTitulos(inicioTitulos);
            printf("Qual titulo deseja verificar? \n->");
            scanf("%d", &id);
            titulo = getTituloById(id, &inicioTitulos);

            printf("%d", titulo->compra->valor);

            printf("1- Listar Operacoes de Compra \n2- Listar Operacoes de Venda \n3- Listar todas as operacoes");
            scanf("%d", &opcaoSecundaria);
            if (opcaoSecundaria == 1)
                listarOperacoes(titulo->compra);
            else if (opcaoSecundaria == 2)
                listarOperacoes(titulo->venda);
            else if (opcaoSecundaria == 3)
            {
                listarOperacoes(titulo->compra);
                listarOperacoes(titulo->venda);
            }

            break;

        default:
            break;
        }
    }
}