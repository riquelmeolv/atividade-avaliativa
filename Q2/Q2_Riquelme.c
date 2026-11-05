#include <stdio.h>
#define ANDARES 5
#define QUARTOS 8

/*
TESTES MANUAIS:
1. Hotel vazio: cada andar tem 0 ocupados e 8 livres; total 0/40;
   taxa 0.00%;
2. Ocupacao (apos implementar ocuparQuarto): ocupar (1,1), (5,8)
   e (5,7). Esperado: 3 ocupados, 37 livres.
   Repetir (5,8) deve avisar que ja esta ocupado, sem mudar os totais.
3. Entradas invalidas: em execucoes separadas, consultar andares 0 e 6,
   quartos 0 e 9.
   Esperado: mensagem de erro, sem acessar a matriz.
*/

void inicializarMatriz(int hotel[][QUARTOS]);
void exibirOcupacao(int hotel[][QUARTOS]);
int contarOcupadosAndar(int hotel[][QUARTOS], int indiceAndar);
void exibirResumo(int hotel[][QUARTOS]);
float calcularTaxaOcupacao(int hotel[][QUARTOS]);
void consultarQuarto(int hotel[][QUARTOS]);
void ocuparQuarto(int hotel[][QUARTOS]);

int main(void)
{
    int hotel[ANDARES][QUARTOS];
    inicializarMatriz(hotel);

    int op;
    float percentual;
    do
    {
        printf("\n======= MENU =======\n");
        printf("1 - Exibir ocupação\n2 - Ocupar quarto\n3 - Exibir resumo\n"
           "4 - Mostrar taxa de ocupação\n5 - Consultar quarto\n0 - Encerrar laço\n");
        printf("Resposta: ");
        /* scanf retorna 1 quando consegue ler um numero inteiro. */
        if(scanf("%d", &op) != 1)
        {
            printf("Entrada invalida. Tente novamente.\n");
        }

        if(op < 0 || op > 5)
        {
            printf("Opção inválida\n");
            continue;
        }
        switch (op)
            {
            case 1:
                exibirOcupacao(hotel);
                break;
            case 2:
                ocuparQuarto(hotel);
                break;
            case 3:
                exibirResumo(hotel);
                break;
            case 4:
                percentual = calcularTaxaOcupacao(hotel);
                printf("Taxa geral: %.2f%%\n", percentual);
                break;
            case 5:
                consultarQuarto(hotel);
                break;
            case 0:
                op = 0;
                break;
            default:
                printf("Opção inválida\n");
                break;
            }
    } while (op != 0);
    
    return 0;
}

/*
QUARTOS informa ao C o tamanho de cada linha da matriz.
Assim, hotel[i][j] pode localizar a linha i e a coluna j.
Alterar um elemento aqui tambem altera a matriz usada na main.
*/
void inicializarMatriz(int hotel[][QUARTOS])
{
    for(int i = 0; i < ANDARES; i++)
    {
        for(int j = 0; j < QUARTOS; j++)
        {
            hotel[i][j] = 0;
        }
    }
}

void exibirOcupacao(int hotel[][QUARTOS])
{
    printf("\nOcupacao: 0 = livre | 1 = ocupado\n");
    printf("Quartos | ");
    for(int j = 0; j < QUARTOS; j++)
    {
        printf("%d | ", j + 1);
    }
    printf("\n");

    for(int i = 0; i < ANDARES; i++)
    {
        printf("Andar %d | ", i + 1);
        for(int j = 0; j < QUARTOS; j++)
        {
            printf("%d | ", hotel[i][j]);
        }
        printf("\n");
    }
}


int contarOcupadosAndar(int hotel[][QUARTOS], int indiceAndar)
{
    int ocupados = 0;
    if(indiceAndar < 0 || indiceAndar >= ANDARES)
    {
        return -1; /* -1 indica indice invalido;*/
    }

    for(int j = 0; j < QUARTOS; j++)
    {
        ocupados += hotel[indiceAndar][j];
    }
    return ocupados;
}

void exibirResumo(int hotel[][QUARTOS])
{
    int totalOcupados = 0;
    int ocupados = 0, maior = 0, andarMaior = 0;
    for(int i = 0; i < ANDARES; i++)
    {
        ocupados = contarOcupadosAndar(hotel, i);
        totalOcupados += ocupados;
        if(i == 0)
        {
            maior = ocupados;
            andarMaior = i;
        }
        else
        {
            if(ocupados > maior)
            {
                maior = ocupados;
                andarMaior = i;
            }
        }

        printf("Andar %d | Livres %d | Ocupados %d |\n",
               i + 1, QUARTOS - ocupados, ocupados);
    }

    printf("Total de ocupados: %d\n", totalOcupados);
    printf("Total livres: %d\n", ANDARES * QUARTOS - totalOcupados);
    /* Todos os andares tem 8 quartos: comparar totais equivale a taxas.
       Em empate, o uso de > mantem o primeiro andar encontrado. */
    printf("Andar com maior ocupacao: %d | Taxa: %.2f%%\n",
           andarMaior + 1, 100.0f * maior / QUARTOS);
}

float calcularTaxaOcupacao(int hotel[][QUARTOS])
{
    int totalOcupados = 0;
    for(int i = 0; i < ANDARES; i++)
    {
        totalOcupados += contarOcupadosAndar(hotel, i);
    }

    /* 100.0f garante divisao real: 3 quartos em 40 resultam em 7.50%. */
    return 100.0f * totalOcupados / (ANDARES * QUARTOS);
}

void consultarQuarto(int hotel[][QUARTOS])
{
    int andar, quarto;

    printf("Informe o andar: ");
    if(scanf("%d", &andar) != 1)
    {
        printf("Entrada invalida: informe um numero inteiro.\n");
    }

    if(andar < 1 || andar > ANDARES)
    {
        printf("Andar invalido.\n");
        return;
    }

    printf("Informe o quarto: ");
    if(scanf("%d", &quarto) != 1)
    {
        printf("Entrada invalida: informe um numero inteiro.\n");
    }

    if(quarto < 1 || quarto > QUARTOS)
    {
        printf("Quarto invalido.\n");
        return;
    }

    if(hotel[andar - 1][quarto - 1] == 1)
    {
        printf("Quarto ocupado.\n");
    }
    else
    {
        printf("Quarto livre.\n");
    }

}

void ocuparQuarto(int hotel[][QUARTOS])
{
   
    int andar, quarto;

    printf("Informe o andar: ");
    if(scanf("%d", &andar) != 1)
    {
        printf("Entrada invalida: informe um numero inteiro.\n");
    }
    if(andar < 1 || andar > ANDARES)
    {
        printf("Andar invalido.\n");
        return;
    }

    printf("Informe o quarto: ");
    if(scanf("%d", &quarto) != 1)
    {
        printf("Entrada invalida: informe um numero inteiro.\n");
        
    }
    if(quarto < 1 || quarto > QUARTOS)
    {
        printf("Quarto invalido.\n");
        return;
    }
    
    
    if(hotel[andar - 1][quarto - 1] == 1)
    {
        printf("Quarto ocupado.\n");
    }
    else
    {
        hotel[andar - 1][quarto - 1] = 1;
        printf("Ocupação confirmada.\n");
    }
}

