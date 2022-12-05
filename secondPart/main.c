#include <stdlib.h>
#include <string.h>

#include "partTwo.h"

int main(int argc, char *argv[]){

    FILE *ArqTxt = NULL, *ArqAlf = NULL; 
    FILE *ArqComprimdo = NULL;
    TipoPalavra NomeArqTxt, NomeArqAlf, NomeArqComp, Opcao;
    TipoPalavra aux;

    memset(Opcao, 0, sizeof(Opcao));

    while(Opcao[0] != 't'){
        
        printf("***********************************************\n");
        printf("*                  Opções                     *\n");
        printf("* (c) Compressão                              *\n");
        printf("* (d) Descompressão                           *\n");
        printf("* (p) Pesquisa no texto comprimido            *\n");
        printf("* (t) Termina                                 *\n");
        printf("***********************************************\n");
        printf("*Opcao:");

        fgets(Opcao, MAXALFABETO + 1, stdin);

        stpcpy (NomeArqAlf, "alfabeto.txt");
        ArqAlf = fopen(NomeArqAlf, "r");

        if(Opcao[0] == 'c'){

            printf("Arquivo texto a ser comprimido: ");
            fgets(NomeArqTxt, MAXALFABETO + 1, stdin);
            NomeArqTxt[strlen(NomeArqTxt)-1] = '\0';
            
            fflush(stdin);
            
            printf("Arquivo comprimido a ser gerado: ");
            fgets(NomeArqComp, MAXALFABETO + 1, stdin);
            NomeArqComp[strlen(NomeArqComp)-1] = '\0';

            ArqTxt = fopen(NomeArqTxt, "r");
            ArqComprimdo = fopen(NomeArqComp, "w+b");

            Compressao(ArqTxt, ArqAlf, ArqComprimdo);

            fclose(ArqTxt);
            ArqTxt = NULL;
            fclose(ArqComprimdo);
            ArqComprimdo = NULL;

        }else if(Opcao[0] == 'd'){

            printf("Arquivo texto a ser descomprimido: ");
            fgets(NomeArqComp, MAXALFABETO + 1, stdin);
            NomeArqComp[strlen(NomeArqComp)-1] = '\0';

            printf("Arquivo de texto a ser gerado: ");
            fgets(NomeArqTxt, MAXALFABETO + 1, stdin);
            NomeArqTxt[strlen(NomeArqTxt)-1] = '\0';

            ArqTxt = fopen(NomeArqTxt, "w");
            ArqComprimdo = fopen(NomeArqComp, "r+b");

            Descompressao(ArqComprimdo, ArqTxt, ArqAlf);

            fclose(ArqTxt);
            ArqTxt = NULL;
            fclose(ArqComprimdo);
            ArqComprimdo = NULL;

        }else if(Opcao[0] == 'p'){

            printf("Arquivo comprimido para ser pesquisado: ");
            fgets(aux, MAXALFABETO + 1, stdin);
            aux[strlen(aux)-1] = '\0';

            strcpy(NomeArqComp, aux);
            ArqComprimdo = fopen(NomeArqComp, "r+b");

            Busca(ArqComprimdo, ArqAlf);

            fclose(ArqComprimdo);
            ArqComprimdo = NULL;
        }
    }
}