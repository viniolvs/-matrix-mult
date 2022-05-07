#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef double Data;

typedef struct Matriz
{
    Data **M;
    int lin,col;
}Matriz;

//aloca uma matriz
void newMatriz(Matriz *mat, int l, int c)
{
    mat->M = malloc (l * sizeof (Data*)) ;
    int i;
    for (i=0; i < l; i++)
        mat->M[i] = malloc (c * sizeof (Data)) ;
    
    mat->lin = l; mat->col = c;
}

void printMatriz(Matriz mat)
{
    int i, j;
    for (i = 0; i < mat.lin; i++)
    {
        printf("| ");
        for(j = 0; j < mat.col; j++ )
            printf("%14.5lf ", mat.M[i][j]);
        printf("|\n");
    }
    printf("\n");
}

//preenche a matriz com valores aleatórios
void fillMatriz(Matriz *mat, int seed)
{
    int i,j;
    if (seed)
        srand(time(NULL));
    for (i = 0; i < mat->lin; i++)
        for (j = 0; j < mat->col; j++)
            mat->M[i][j] = ((double)rand() * 1000) / (double)RAND_MAX;
}

//Multiplica duas matrizes
void multMat(Matriz A, Matriz B, Matriz *C)
{
    int i,j,k;
    for (i = 0; i < A.lin; i++)
        for (j = 0; j < B.col; j++)
            for (k = 0; k < A.col; k++)
                C->M[i][j] += A.M[i][k] * B.M[k][j];
}

//Multiplica duas matrizes com B transposta
void multMatT(Matriz A, Matriz Bt, Matriz *C)
{
    int i, j, k;
    for (i = 0; i < A.lin; i++)
        for (j = 0; j < Bt.col; j++)
            for (k = 0; k < A.col; k++)
                C->M[i][j] += A.M[i][k] * Bt.M[j][k];
}

//transpõe uma matriz
void matrizT(Matriz A, Matriz *At)
{
    int i, j;
    for(i = 0; i < At->lin; i++)
        for(j = 0; j < At->col; j++)
            At->M[i][j] = A.M[j][i];

}

void exportToCsv(Matriz mat, char *nomeMatriz, char *filename)
{
    FILE *file;
    file = fopen(filename,"a");

    int i,j;
    char buffer[100];

    fputs(nomeMatriz, file);
    fputc('\n', file);

    for(i = 0; i < mat.lin; i++)
    {
        for (j = 0; j < mat.col; j++)
        {
            sprintf(buffer, "%lf", mat.M[i][j]);
            fputs(buffer, file);
            fputc(',',file);
        }
        fputc('\n', file);
    }
    fputc('\n',file);

    fclose(file);
}

void exportToTxt(Matriz mat, char *nomeMatriz, char *filename)
{
    FILE *file;
    file = fopen(filename,"a");

    int i,j;
    char buffer[100];

    fputs(nomeMatriz, file);
    fputc('\n', file);

    for(i = 0; i < mat.lin; i++)
    {
        for (j = 0; j < mat.col; j++)
        {
            sprintf(buffer, "%lf", mat.M[i][j]);
            fputs(buffer, file);
            fputc(' ',file);
        }
        fputc('\n', file);
    }
    fputc('\n',file);

    fclose(file);
}

int main(int argc, char *argv[])
{
    if (argc < 6 || argc > 7)
    {
        printf("Invalid format!\n");
        printf("./multmat.x l1 c1 l2 c2 o|t\n");
        return 0;
    }

    int l1,c1;
    int l2,c2;
    char *mode;
    l1 = atoi(argv[1]);
    c1 = atoi(argv[2]);
    l2 = atoi(argv[3]);
    c2 = atoi(argv[4]);
    mode = argv[5];

    if ((strcmp(mode,"o") != 0) && (strcmp(mode,"t") != 0))
    {
        printf("Invalid format!\n");
        printf("./multmat.x l1 c1 l2 c2 o|t\n");
        return 0;
    }
    if(c1 != l2)
    {
        printf("Dimensoes das matrizes imcompativeis para multiplicar!\n");
        return 0;
    }

    //Aloca e gera duas matrizes com numeros aleatorios
    Matriz A, B, C, Bt;
    Bt.M = NULL;
    newMatriz(&A, l1, c1);
    newMatriz(&B, l2, c2);
    fillMatriz(&A, 1);
    fillMatriz(&B, 1);
    //Aloca a matriz para o resultado
    newMatriz(&C, A.lin, B.col);

    float tempo = 0.0;

    clock_t inicio, fim;
    clock_t inicioT, fimT;

    if (strcmp(mode,"o") == 0)
    {
        inicio = clock();
        multMat(A, B, &C);
        fim = clock();

        tempo = (float)(((fim - inicio) + 0.0) / CLOCKS_PER_SEC);
    }
    else 
    {
        newMatriz(&Bt, B.col, B.lin);

        inicioT = clock();
        matrizT(B, &Bt);
        fimT = clock();

        inicio = clock();
        multMatT(A, Bt, &C);
        fim = clock();

        tempo = (float)(((fim - inicio) + 0.0) / CLOCKS_PER_SEC) + (float)(((fimT - inicioT) + 0.0) / CLOCKS_PER_SEC);
    }

    if (argc == 7 && strcmp("p", argv[6]) == 0)
    {
        printf("Matriz M1: \n");
        printMatriz(A);
        printf("Matriz M2: \n");
        printMatriz(B);
        if (Bt.M != NULL)
        {
            printf("Matriz M2 transposta: \n");
            printMatriz(Bt);
        }
        printf("Produto de M1 M2: \n");
        printMatriz(C);
    }

    //grava as matrizes em um arquivo csv
    else if (argc == 7 && strcmp("csv", argv[6]) == 0)
    {
        exportToCsv(A, "Matriz M1", "matriz.csv");
        exportToCsv(B, "Matriz M2", "matriz.csv");
        if (Bt.M != NULL)
            exportToCsv(Bt, "Matriz M2T", "matriz.csv");
        exportToCsv(C, "Matriz M1*M2", "matriz.csv");
    }
    
    else if (argc == 7 && strcmp("txt", argv[6]) == 0)
    {
        exportToTxt(A, "Matriz M1", "matriz.txt");
        exportToTxt(B, "Matriz M2", "matriz.txt");
        if (Bt.M != NULL)
            exportToTxt(Bt, "Matriz M2T", "matriz.txt");
        exportToTxt(C, "Matriz M1*M2", "matriz.txt");
    }

    
    printf("Tempo de execucao = %f\n", tempo);

    return 0;
}
