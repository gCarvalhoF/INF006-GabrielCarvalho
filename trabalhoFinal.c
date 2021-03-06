#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    Acao cotacao;
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

Titulo *getTituloById(int id, Titulo **inicioLista)
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
    printf("\t T I T U L O S  R E G I S T R A D O S\n");
    printf("--------------------------------------------\n");

    do
    {
        printf("%d - %s \n", current->id, current->sigla);

        current = current->prox;
    } while (current != NULL);
    printf("--------------------------------------------\n");

}

Titulo *criarTitArq(int id, char sigla[])
{
    Titulo *novo = (Titulo *)malloc(sizeof(Titulo));

    novo->id = id;
    strcpy(novo->sigla, sigla);
    novo->prox = NULL;
    novo->compra = NULL;
    novo->venda = NULL;
}

void carregarTitulos(Titulo **inicioLista)
{
    int id;
    char sigla[5];

    Titulo *current = *inicioLista;
    FILE *file = fopen("./titulos.txt", "a+");

    if (file == NULL)
    {
        printf("Não foi possível abrir o arquivo.\n");
    }
    else
    {
        while (fscanf(file, "%d %s", &id, sigla) != EOF)
        {
            current = *inicioLista;

            if (*inicioLista == NULL)
            {
                *inicioLista = criarTitArq(id, sigla);
            }
            else
            {
                while (current->prox != NULL)
                {
                    current = current->prox;
                }
                current->prox = criarTitArq(id, sigla);
            }
        }
    }
    fclose(file);
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

void realizarOperacoes(int id, Titulo **inicioTitulos)
{
    int novaQtdVenda = 0, novaQtdCompra = 0;
    Titulo *title;
    title = *inicioTitulos;

    while (title != NULL)
    {
        if (title->id == id)
            break;

        title = title->prox;
    }

    Acao *tempCompra = title->compra, *prevCompra;
    Acao *tempVenda = title->venda, *prevVenda;

    // If head node itself holds the key to be deleted
    if (tempCompra != NULL && tempVenda != NULL && (tempCompra->valor == tempVenda->valor))

    {
        if (tempCompra->qtd == tempVenda->qtd)
        {
            title->compra = tempCompra->prox; // Changed head
            title->venda = tempVenda->prox;

            title->cotacao = *tempVenda;
            // Changed head

            free(tempCompra); // free old head
            free(tempVenda);  // free old head

            return;
        }
        else
        {
            novaQtdCompra = tempCompra->qtd - tempVenda->qtd;
            novaQtdVenda = tempVenda->qtd - tempCompra->qtd;

            tempVenda->qtd = novaQtdVenda;
            tempCompra->qtd = novaQtdCompra;

            title->cotacao = *tempVenda;

            if (novaQtdCompra <= 0)
            {
                if (tempCompra->prox == NULL)
                    title->compra = NULL;
                else
                {
                    title->compra = tempCompra->prox;
                    free(tempCompra);
                }
                return;
            }

            if (novaQtdVenda <= 0)
            {
                if (tempVenda->prox == NULL)
                    title->venda = NULL;
                else
                {
                    title->venda = tempVenda->prox;
                    free(tempVenda);
                }
                return;
            }
        }

        // Search for the key to be deleted, keep track of the
        // previous node as we need to change 'prev->next'
        while ((tempCompra != NULL || tempVenda != NULL) && tempCompra->valor < tempVenda->valor)
        {
            prevCompra = tempCompra;
            prevVenda = tempVenda;

            tempCompra = tempCompra->prox;
            tempVenda = tempVenda->prox;
        }

        if (tempCompra->valor == tempVenda->valor && !(tempCompra->qtd == tempVenda->qtd))
        {

            novaQtdCompra = tempCompra->qtd - tempVenda->qtd;
            novaQtdVenda = tempVenda->qtd - tempCompra->qtd;

            tempVenda->qtd = novaQtdVenda;
            tempCompra->qtd = novaQtdCompra;

            title->cotacao = *tempVenda;

            if (tempCompra->qtd <= 0)
            {
                prevCompra->prox = tempCompra->prox;
                free(tempCompra);
            }

            else if (tempVenda->qtd <= 0)
            {
                prevVenda->prox = tempVenda->prox;
                free(tempVenda);
            }
            return;
        }

        // If key was not present in linked list
        if (tempCompra == NULL || tempVenda == NULL)
            return;

        // Unlink the node from linked list
        prevCompra->prox = tempCompra->prox;
        prevVenda->prox = tempVenda->prox;

        free(tempCompra); // Free memory
        free(tempVenda);  // Free memory
    }
}

void inserirOperacao(int id, Titulo **inicioTitulos)
{
    Titulo *title = *inicioTitulos;
    while (title != NULL)
    {
        if (title->id == id)
            break;

        title = title->prox;
    }

    Acao *novaOperacao;
    novaOperacao = criarOperacao();
    Acao *current = NULL;
    Acao *previous = NULL;
    Acao *temp;

    if (novaOperacao->tipo == 'c')
    {

        if (title->compra == NULL || title->compra->valor <= novaOperacao->valor)
        {
            novaOperacao->prox = title->compra;
            title->compra = novaOperacao;
        }
        else
        {
            /* Locate the node before
    the point of insertion */
            current = title->compra;
            while (current->prox != NULL && current->prox->valor > novaOperacao->valor)
            {
                current = current->prox;
            }
            novaOperacao->prox = current->prox;
            current->prox = novaOperacao;
        }
    }

    else
    {
        if (title->venda == NULL || title->venda->valor >= novaOperacao->valor)
        {
            novaOperacao->prox = title->venda;
            title->venda = novaOperacao;
        }
        else
        {
            /* Locate the node before
    the point of insertion */
            current = title->venda;
            while (current->prox != NULL && current->prox->valor < novaOperacao->valor)
            {
                current = current->prox;
            }
            novaOperacao->prox = current->prox;
            current->prox = novaOperacao;
        }
    }

    realizarOperacoes(id, inicioTitulos);
}

void listarOperacoes(Acao *inicioLista, int id)
{
    Acao *current;

    current = inicioLista;
    if (inicioLista == NULL)
     { printf("---------------------------------------------\n");
        printf("\n\tNenhuma Operacao registrada ainda!\n");
       printf("---------------------------------------------\n");}
    else
    {
        do
        {
            printf("---------------------------------------------\n");
            printf("\t\tR$%.2f - %d - %c\n", current->valor, current->qtd, current->tipo);

            current = current->prox;
        } while (current != NULL);
      printf("---------------------------------------------\n");

    }
}

Acao *criarAcaoArq(int qtd, float valor, char tipo)
{
    Acao *novo = (Acao *)malloc(sizeof(Acao));

    novo->valor = valor;
    novo->tipo = tipo;
    novo->qtd = qtd;
    novo->prox = NULL;
}

void carregarAcao(Titulo **inicioLista)
{
    int id, qtd;
    float valor;
    char tipo;

    FILE *file = fopen("./acoes.txt", "a+");

    if (file == NULL)
    {
        printf("Não foi possível abrir o arquivo.\n");
    }
    else
    {
        while (fscanf(file, "%d %f %d %c", &id, &valor, &qtd, &tipo) != EOF)
        {
            Acao *current;
            Titulo *title = *inicioLista;

            while (title != NULL)
            {
                if (title->id == id)
                    break;

                title = title->prox;
            }

            if (tipo == 'c')
            {
                current = title->compra;

                if (title->compra == NULL)
                {
                    title->compra = criarAcaoArq(qtd, valor, tipo);
                }
                else
                {
                    while (current->prox != NULL)
                    {
                        current = current->prox;
                    }
                    current->prox = criarAcaoArq(qtd, valor, tipo);
                }
            }

            else if (tipo == 'v')
            {
                current = title->venda;

                {
                    if (title->venda == NULL)
                    {
                        title->venda = criarAcaoArq(qtd, valor, tipo);
                    }
                    else
                    {
                        while (current->prox != NULL)
                        {
                            current = current->prox;
                        }
                        current->prox = criarAcaoArq(qtd, valor, tipo);
                    }
<<<<<<< HEAD
=======
              }
            else
                if (tipo == 'v')
                {
                    current = title->venda;

                    {
                        if (title->venda == NULL)
                        {
                            title->venda = criarAcaoArq(qtd, valor, tipo);
                        }
                        else
                        {
                            while (current->prox != NULL)
                            {
                                current = current->prox;
                            }
                            current->prox = criarAcaoArq(qtd, valor, tipo);
                        }
                    }
>>>>>>> 36b84e1d229965d5c5a7966b4307576965cfc138
                }
            }
        }
    }
    fclose(file);
}

void main()
{
    Titulo *inicioTitulos = NULL;
    Titulo *titulo;
    int id = -1;
    int opcao = -1, opcaoSecundaria = -1;

    carregarTitulos(&inicioTitulos);
    carregarAcao(&inicioTitulos);

    while (opcao != 0)
    {
        printf("Menu \n");
<<<<<<< HEAD
        printf("1- Inserir novo Titulo \n2- Listar titulos registrados \n3- Operar Títulos \n4- Listar operacoes\n ->");
=======
      printf("1- Inserir novo Titulo \n2- Listar titulos registrados \n3- Operar Títulos \n4- Listar operacoes \n5- Verificar última cotacao\n ->");
>>>>>>> 36b84e1d229965d5c5a7966b4307576965cfc138
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            system("cls");
            inserirTitulo(&inicioTitulos);

            break;

        case 2:
            system("cls");
            listarTitulos(inicioTitulos);
<<<<<<< HEAD

=======
            
>>>>>>> 36b84e1d229965d5c5a7966b4307576965cfc138
            break;

        case 3:
            system("cls");
            listarTitulos(inicioTitulos);
            printf("Qual titulo deseja operar? \n->");
            scanf("%d", &id);
            getchar();

            inserirOperacao(id, &inicioTitulos);

            break;

        case 4:
            system("cls");
            listarTitulos(inicioTitulos);
            printf("Qual titulo deseja verificar? \n->");
            scanf("%d", &id);
            titulo = getTituloById(id, &inicioTitulos);

            printf("1- Listar Operacoes de Compra \n2- Listar Operacoes de Venda \n3- Listar todas as operacoes \n ->");
            scanf("%d", &opcaoSecundaria);
          
            
            if (opcaoSecundaria == 1)
            {
              printf("---------------------------------------------\n");
              printf("\tO P E R A C O E S");
              printf("\tC O M P R A\n");
              listarOperacoes(titulo->compra, id);}
            else if (opcaoSecundaria == 2)
            {
              printf("---------------------------------------------\n");
            printf("\tO P E R A C O E S");
              printf("\tV E N D A\n");
                listarOperacoes(titulo->venda, id);}
            else if (opcaoSecundaria == 3)
            {
                printf("---------------------------------------------\n");
                printf("\tO P E R A C O E S");
                printf("\tC O M P R A\n");
                listarOperacoes(titulo->compra, id);
              
                printf("---------------------------------------------\n");
                printf("\tO P E R A C O E S");
                printf("\tV E N D A\n");
                listarOperacoes(titulo->venda, id);
            }

            break;

        case 5:
            system("cls");
            listarTitulos(inicioTitulos);
            printf("Qual titulo deseja verificar? \n->");
            scanf("%d", &id);
            titulo = getTituloById(id, &inicioTitulos);

<<<<<<< HEAD
            printf("Ultima cotacao %s: %.2f - %d - %c\n", titulo->sigla, titulo->cotacao.valor, titulo->cotacao.qtd, titulo->cotacao.tipo);

=======
            printf("                 C O T A C A O\n");
            printf("---------------------------------------------\n");
          
            if (titulo->cotacao.valor == 0)
              printf("\tAinda não existe cotação para esse título.\n");
            else
            {
            printf("\tUltima cotacao %s: R$ %.2f - %c\n", titulo->sigla, titulo->cotacao.valor, titulo->cotacao.tipo);}
            printf("---------------------------------------------\n");

          
>>>>>>> 36b84e1d229965d5c5a7966b4307576965cfc138
            break;
        default:
            break;
        }
    }
}