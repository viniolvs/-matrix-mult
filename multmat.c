#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int Data;

typedef struct Matriz
{
    Data **M;
    int lin,col;
}Matriz;

//aloca uma matriz
void newMatriz(Matriz *mat, int l, int c)
{
    mat->M = malloc (l * sizeof (int*)) ;
    int i;
    for (i=0; i < l; i++)
        mat->M[i] = malloc (c * sizeof (int)) ;
    
    mat->lin = l; mat->col = c;
}

void printMatriz(Matriz mat)
{
    int i, j;
    for (i = 0; i < mat.lin; i++)
    {
        printf("| ");
        for(j = 0; j < mat.col; j++ )
            printf("%6.d ", mat.M[i][j]);
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
            mat->M[i][j] = (rand()%1000);
}

//Multiplica duas matrizes
void multMat(Matriz A, Matriz B, Matriz *C)
{
    int i,j,k;
    newMatriz(C, A.lin, B.col);
    for (i = 0; i < A.lin; i++)
        for (j = 0; j < B.col; j++)
            for (k = 0; k < A.col; k++)
                C->M[i][j] += A.M[i][k] * B.M[k][j];
}

//Multiplica duas matrizes com B transposta
void multMatT(Matriz A, Matriz Bt, Matriz *C)
{
    newMatriz(C, A.lin, Bt.col);
    int i, j, k;
    for (i = 0; i < A.lin; i++)
        for (j = 0; j < Bt.col; j++)
            for (k = 0; k < A.col; k++)
                C->M[i][j] += A.M[i][k] * Bt.M[i][k];
}

//transpõe uma matriz
void matrizT(Matriz A, Matriz *At)
{
    newMatriz(At, A.col, A.lin);
    int i, j;
    for(i = 0; i < At->lin; i++)
        for(j = 0; j < At->col; j++)
            At->M[i][j] = A.M[j][i];

}

int main(int argc, char const *argv[])
{
    Matriz A, B, C, Bt, D;
    newMatriz(&A, 3, 3);
    fillMatriz(&A, 0);
    printMatriz(A);

    newMatriz(&B, 3, 3);
    fillMatriz(&B, 0);
    printMatriz(B);

    matrizT(B, &Bt);
    printMatriz(Bt);

    printf("Multiplicaçao normal: \n");
    multMat(A, B, &D);
    printMatriz(D);

    printf("Multiplicaçao transposta: \n");
    multMatT(A,Bt,&C);
    printMatriz(C);
    
    return 0;
}
