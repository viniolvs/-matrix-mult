#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//lê um arquivo de saída da execução e calcula a média

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("%d\n",argc);
        printf("Entrada inválida!\n");
        printf("./media.x <nome_arquivo>\n");
        return 0;
    }

    char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    char c = '0';
    short offset = strlen("Tempo de execucao = ");
    char number[30];
    char buffer[offset+1];
    int i , j;
    double n, sum = 0.0;

    for(i = 0; i < 10; i++)
    {
        fread(buffer, 1, offset, file);
        buffer[offset] = '\0';
        for(j = 0, c = '0'; c != '\n';)
        {
            c = fgetc(file);
            number[j++] = c;
        }
        sscanf(number, "%lf", &n);
        sum += n;
    }
    fclose(file);
    double media = sum / 10.0;
    printf("Media %s = %.5lf\n", filename, media);
    return 0;
}
