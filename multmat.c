#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//aloca uma matriz como um vetor
double** newVetor(int l, int c)
{
    double **M;
    int i;
    M = malloc (l * sizeof (double*)) ;
    M[0] = malloc(l * c * sizeof(double));
    for (i=1; i < l; i++)
        M[i] = M[0] + c * i;
    return M;
}

//aloca cada linha da matriz em uma posição distinta na memória
double** newMatriz(int l, int c)
{
    double **M;
       M = malloc (l * sizeof (double*)) ;
    int i;
    for (i=0; i < l; i++)
        M[i] = malloc (c * sizeof (double)) ;
    return M;
}

void freeMatriz(double **M, int l)
{
    int i;
    for (i = 0; i < l; i++)
        free(M[i]);
    free(M);
}

void freeVetor(double **V)
{
    free(V[0]);
    free(V);
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
    clock_t clk = clock();
    if (seed)
        srand(clk);
    for (i = 0; i < l; i++)
        for (j = 0; j < c; j++)
            M[i][j] = ((double)rand() * 1000.0) / ((double)RAND_MAX);
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
            C[i][j] = 0.0;
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
            C[i][j] = 0.0;
            for (k = 0; k < l2; k++)
                C[i][j] += A[i][k] * Bt[j][k];
        }
    }
    return C;
}

//transpõe uma matriz e retorna a matriz transposta
double** matrizT(double **M,  int l, int c, char *mode)
{
    int i, j;
    double **Mt;
    if (!strcmp(mode, "vt"))
        Mt = newVetor(c,l);
    else
        Mt = newMatriz(c, l);
    for(i = 0; i < c; i++)
        for(j = 0; j < l; j++)
            Mt[i][j] = M[j][i];
    return Mt;
}

//exporta uma matriz para um arquivo txt
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

    if (strcmp(mode,"o") && strcmp(mode,"t") && strcmp(mode,"vo") && strcmp(mode,"vt"))
    {
        printf("Invalid format!\n");
        printf("./multmat.x l1 c1 l2 c2 o|t|vo|vt\n");
        return 0;
    }
    if(c1 != l2)
    {
        printf("Dimensoes das matrizes imcompativeis para multiplicar!\n");
        return 0;
    }

    //Aloca e gera duas matrizes com numeros aleatorios
    double **A, **B, **C, **Bt;
    C = NULL;
    Bt = NULL;
    
    //aloca as matrizes de acordo com o modo
    A = newMatriz(l1,c1);
    if (!strcmp(mode,"vo"))
        B = newVetor(l2, c2);
    else
        B = newMatriz(l2,c2);
        
    //preenche as matrizes (seed = 0 valores repetem; seed = 1 valores aleatórios)
    fillMatriz(A, l1, c1, 1);
    fillMatriz(B, l2, c2, 1);
    
    double tempo = 0.0;
    clock_t inicio, fim;
    clock_t inicioT, fimT;

    if (!strcmp(mode, "o") || !strcmp(mode, "vo"))
    {
        inicio = clock();
        C = multMat(A, B, l1, l2, c1, c2);
        fim = clock();

        tempo = (float)(((fim - inicio) + 0.0) / CLOCKS_PER_SEC);
    }
    else 
    {
        inicioT = clock();
        Bt = matrizT(B, l2, c2, mode);
        fimT = clock();

        inicio = clock();
        C = multMatT(A, Bt, l1, l2, c1, c2);
        fim = clock();

        tempo = (float)(((fim - inicio) + 0.0) / CLOCKS_PER_SEC) + (float)(((fimT - inicioT) + 0.0) / CLOCKS_PER_SEC);
    }

    //printa as matrizes no terminal
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

    //grava as matrizes em um arquivo txt
    else if (argc == 7 && strcmp("txt", argv[6]) == 0)
    {
        exportToTxt(A, l1, c1, "Matriz A", "matriz.txt");
        exportToTxt(B, l2, c2, "Matriz B", "matriz.txt");
        if (Bt != NULL)
            exportToTxt(Bt, c2, l2, "Matriz BT", "matriz.txt");
        exportToTxt(C, l1, c2, "Matriz A*B", "matriz.txt");
    }

    if (argc == 7 && strcmp("out", argv[6]) == 0)
        printf("%f\n", tempo);
    else 
        printf("Tempo de execucao = %f\n", tempo);
    
    //desaloca as matrizes utillizadas
    if (A!=NULL)
        freeMatriz(A,l1);
    if (B!=NULL)
    {    
        if(!strcmp(mode,"vo"))
            freeVetor(B);
        else
            freeMatriz(B,l2);
    }
    if (C!=NULL)
        freeMatriz(C,l1);
    if(Bt != NULL)
    {
        if (!strcmp(mode,"vt"))
            freeVetor(Bt);
        else
            freeMatriz(Bt,c2);
    }
    return 0;
}
