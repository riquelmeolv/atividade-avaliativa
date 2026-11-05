#include <stdio.h>
#define SETORES 4
#define NOTAS 6

void lerAvaliacoes(int hotel[][SETORES]);
void calcularMediaSetor(int hotel[][SETORES], float *medias);
float calcularMediaGeral(float *medias);
void identificarExtremos(float *medias, char nomes[][15]);
void contarAvaliacoesCriticas(int hotel[][SETORES]);
void exibirRelatorio(int hotel[][SETORES], float *medias, char nomes[][15]);

int main()
{
    int hotel[NOTAS][SETORES];
    float medias[SETORES], media_geral;
    char nomes[SETORES][15] = {"Recepcao", "Limpeza", "Restaurante", "Manutencao"};
    int op;

    lerAvaliacoes(hotel);
    calcularMediaSetor(hotel, medias);
    media_geral = calcularMediaGeral(medias);

    printf("\n========= MENU =========");
    printf("\n1 - Calcular a media geral dos setores\n2 - Quantidade de avaliacoes com notas criticas"
           "\n3 - Exibir maior e menor media\n4 - Exibir relatorio\n0 - Sair\n");
    do
    {
        printf("Answer: ");
        if(scanf("%d", &op) != 1)
        {
            printf("Entrada invalida.\n");
            break;
        }

        switch (op)
        {
        case 1:
            media_geral = calcularMediaGeral(medias);
            printf("Media geral: %.2f\n", media_geral);
            break;
        case 2: 
            contarAvaliacoesCriticas(hotel);
            break;
        case 3:
            identificarExtremos(medias, nomes);
            break;
        case 4:
            exibirRelatorio(hotel, medias, nomes);
            break;
        case 0:
            break;
        default:
            printf("Entrada invalida\n");
            break;
        }

    } while (op != 0);
    
    return 0;
}

void lerAvaliacoes(int hotel[][SETORES])
{
    int nota;
    for(int i = 0; i < NOTAS; i++)
    {
        printf("=== Informe as Notas ===\n");
        for(int j = 0; j < SETORES; j++)
        {
            nota = 0;
            do
            {
                printf("Setor %d: ", j + 1);
                if(scanf("%d", &nota) != 1)
                {
                    printf("Entrada invalida.\n");
                    continue;
                }

            } while (nota < 1 || nota > 5);
            hotel[i][j] = nota;
        }
    }
}

void calcularMediaSetor(int hotel[][SETORES], float *medias)
{
    float media, sum;
    for(int i = 0; i < SETORES; i++)
    {
        sum = 0;
        for(int j = 0; j < NOTAS; j++)
        {
            sum += hotel[j][i];
        }

        if(sum != 0)
        {
            media = sum / 6.0;
        }
        else
        {
            media = 0;
        }

        medias[i] = media;
    }
}

float calcularMediaGeral(float *medias)
{
    float sum = 0, media;
    for(int i = 0; i < SETORES; i++)
    {
        sum += medias[i];
    }

    media = sum / SETORES;
    return media;
}

void identificarExtremos(float *medias, char nomes[][15])
{
    float maior, menor;
    maior = medias[0], menor = medias[0];
    for(int i = 0; i < SETORES; i++)
    {
        if(medias[i] > maior)
        {
            maior = medias[i];
        }
        if(medias[i] < menor)
        {
            menor = medias[i];
        }
    }
    
    printf("A maior media: %.2f\n", maior);
    for(int i = 0; i < SETORES; i++)
    {
        if(medias[i] == maior)
        {
            printf("Setor: %s\n", nomes[i]);
        }
    }

    printf("A menor media: %.2f\n", menor);
    for(int i = 0; i < SETORES; i++)
    {
        if(medias[i] == menor)
        {
            printf("Setor: %s\n", nomes[i]);
        }
    }
}

void contarAvaliacoesCriticas(int hotel[][SETORES])
{
    int notaCri_linhas = 0, cont;
    for(int i = 0; i < NOTAS; i++)
    {
        cont = 0;
        for(int j = 0; j < SETORES; j++)
        {
            if(hotel[i][j] == 1 || hotel[i][j] == 2)
            {
                cont++;
            }
        }

        if(cont != 0)
        {
            notaCri_linhas++;
        }
    }

    printf("Avaliacoes com pelo menos uma nota critica: %d\n", notaCri_linhas);
}

void exibirRelatorio(int hotel[][SETORES], float *medias, char nomes[][15])
{
    printf("SETORES | RECEPCAO | LIMPEZA | RESTAURANTE | MANUTENCAO\n");
    for(int i = 0; i < NOTAS; i++)
    {
        printf("NOTAS   |");
        for(int j = 0; j < SETORES; j++)
        {
            printf("     %d    |", hotel[i][j]);
        }
        printf("\n");
    }


    printf("\nMEDIAS  | ");
    for(int i = 0; i < SETORES; i++)
    {
        printf(" %.2f | ", medias[i]);
    }
    printf("\n");

    float media_geral = calcularMediaGeral(medias);
    printf("A media geral: %.2f\n", media_geral);
    identificarExtremos(medias, nomes);
    contarAvaliacoesCriticas(hotel);
}