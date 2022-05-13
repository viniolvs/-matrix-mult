#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//aloca uma matriz como um vetorzao
double** newVetor(int l, int c)
{
    double **M;
    int i, j;
    M = malloc (l * sizeof (double*)) ;
    M[0] = malloc(l * c * sizeof(double));
    
    for (i=1; i < l; i++)
        M[i] = M[0] + i + c;

    return M;
}

double** newMatriz(int l, int c)
{
    double **M;
       M = malloc (l * sizeof (double*)) ;
    int i;
    for (i=0; i < l; i++)
        M[i] = malloc (c * sizeof (double)) ;
    return M;
}

void printMatriz(double **M, int l, int c)
{
    int i, j;
    for (i = 0; i < l; i++)
    {
        printf("| ");
        for(j = 0; j < c; j++ )
            printf("%14.5lf ", M[i][j]);
        printf("|\n");
    }
    printf("\n");
}

//preenche a matriz com valores aleatórios
void fillMatriz(double **M,int l, int c, int seed)
{
    int i,j;
    if (seed)
        srand(time(NULL));
    for (i = 0; i < l; i++)
        for (j = 0; j < c; j++)
            M[i][j] = ((double)rand() * 1000) / (double)RAND_MAX;
}

//Multiplica duas matrizes
double** multMat(double **A, double **B, int l1, int l2, int c1, int c2)
{
    int i,j,k;
    double **C;
    C = newMatriz(l1, c2);
    for (i = 0; i < l1; i++)
    {
        for (j = 0; j < c2; j++)
        {
            C[i][j] = 0;
            for (k = 0; k < l2; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    }
    return C;
}

//Multiplica duas matrizes com B transposta
double** multMatT(double **A, double **Bt, int l1, int l2, int c1, int c2)
{
    int i,j,k;
    double **C;
    C = newMatriz(l1, c2);
    for (i = 0; i < l1; i++)
    {
        for (j = 0; j < c2; j++)
        {
            C[i][j] = 0;
            for (k = 0; k < l2; k++)
                C[i][j] += A[i][k] * Bt[j][k];
        }
    }
    return C;
}

//transpõe uma matriz
double** matrizT(double **M,  int l, int c)
{
    int i, j;
    double **Mt;
    Mt = newMatriz(c, l);
    for(i = 0; i < l; i++)
        for(j = 0; j < c; j++)
            Mt[i][j] = M[j][i];
    return Mt;
}

void exportToCsv(double **M, int l, int c, char *nomeMatriz, char *filename)
{
    FILE *file;
    file = fopen(filename,"a");

    int i,j;
    char buffer[100];

    fputs(nomeMatriz, file);
    fputc('\n', file);

    for(i = 0; i < l; i++)
    {
        for (j = 0; j < c; j++)
        {
            sprintf(buffer, "%lf", M[i][j]);
            fputs(buffer, file);
            fputc(',',file);
        }
        fputc('\n', file);
    }
    fputc('\n',file);

    fclose(file);
}

void exportToTxt(double **M, int l, int c, char *nomeMatriz, char *filename)
{
    FILE *file;
    file = fopen(filename,"a");

    int i,j;
    char buffer[100];

    fputs(nomeMatriz, file);
    fputc('\n', file);

    for(i = 0; i < l; i++)
    {
        for (j = 0; j < c; j++)
        {
            sprintf(buffer, "%lf", M[i][j]);
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
    double **A, **B, **C, **Bt;
    Bt = NULL;
    C = NULL;
    A = newMatriz(l1, c1);
    B = newVetor(l2, c2);
    fillMatriz(A, l1, c1, 1);
    fillMatriz(B, l2, c2, 1);
    

    float tempo = 0.0;

    clock_t inicio, fim;
    clock_t inicioT, fimT;

    if (strcmp(mode,"o") == 0)
    {
        inicio = clock();
        C = multMat(A, B, l1, l2, c1, c2);
        fim = clock();

        tempo = (float)(((fim - inicio) + 0.0) / CLOCKS_PER_SEC);
    }
    else 
    {
        inicioT = clock();
        Bt = matrizT(B, l2, c2);
        fimT = clock();

        inicio = clock();
        C = multMatT(A, B, l1, l2, c1, c2);
        fim = clock();

        tempo = (float)(((fim - inicio) + 0.0) / CLOCKS_PER_SEC) + (float)(((fimT - inicioT) + 0.0) / CLOCKS_PER_SEC);
    }

    if (argc == 7 && strcmp("p", argv[6]) == 0)
    {
        printf("Matriz M1: \n");
        printMatriz(A, l1, c1);
        printf("Matriz M2: \n");
        printMatriz(B, l2, c2);
        if (Bt != NULL)
        {
            printf("Matriz M2 transposta: \n");
            printMatriz(Bt, c2, l2);
        }
        printf("Produto de M1 M2: \n");
        printMatriz(C, l1, c2);
    }

    //grava as matrizes em um arquivo csv
    else if (argc == 7 && strcmp("csv", argv[6]) == 0)
    {
        exportToCsv(A, l1, c1, "Matriz M1", "matriz.csv");
        exportToCsv(B, l2, c2, "Matriz M2", "matriz.csv");
        if (Bt != NULL)
            exportToCsv(Bt, c2, l2, "Matriz M2T", "matriz.csv");
        exportToCsv(C, l1, c2, "Matriz M1*M2", "matriz.csv");
    }
    
    else if (argc == 7 && strcmp("txt", argv[6]) == 0)
    {
        exportToTxt(A, l1, c1, "Matriz M1", "matriz.txt");
        exportToTxt(B, l2, c2, "Matriz M2", "matriz.txt");
        if (Bt != NULL)
            exportToTxt(Bt, c2, l2, "Matriz M2T", "matriz.txt");
        exportToTxt(C, l1, c2, "Matriz M1*M2", "matriz.csv");
    }

    if (argc == 7 && strcmp("out", argv[6]) == 0)
        printf("%f\n", tempo);
    else 
        printf("Tempo de execucao = %f\n", tempo);
    
    free(A[0]);
    free(A);
    free(B[0]);
    free(B);
    free(C[0]);
    free(C);
    if (Bt!=NULL)
    {
        free(Bt[0]);
        free(Bt);
    }

    return 0;
}
