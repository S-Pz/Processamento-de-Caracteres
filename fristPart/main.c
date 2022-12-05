#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fristPart.h"

// TO RUN  THIS PROGRAM TYPE : ./tp3 -i texto.txt padrao.txt
int main(int agrc, char *argv[]){

    FILE *t;
    
    char a[200];
    char b[200];
    int tam1 = 0;
    int tam2 = 0;
    int aux1;
    int tam = 0;
    char *Texto,*Padrao;
   
    Texto = read_file(argv[2]);
    Padrao = read_file(argv[3]);

    t = fopen(argv[3],"r");

    if(strcmp(argv[1], "2") == 0){
   
        for(int i; i<=strlen(Padrao); i++){
        
            fscanf(t, "%c", &a[i]);
            
            if(a[i] == '\n'){
            
                tam2 = i-1;
                aux1 = tam1;
                tam = (tam2 - tam1);

                for(int j = 0 ; j <= tam; j++){
                
                    b[j] = a[aux1];
                    aux1++;
                }
                printf("\n");
                printf("%s", b);
                shiftAndAprox(Texto, (long)strlen(Texto), b, tam, 0);

                tam1 = tam2 + 2;
            }
        }

        tam2 = strlen(Padrao);
        aux1 = tam1;
        tam = (tam2 - tam1);

        for(int j = 0 ; j <= tam; j++){
        
            b[j] = a[aux1];
            aux1++;
        }
        
        printf("\n");
        printf("%s", b);
        shiftAndAprox(Texto, (long)strlen(Texto), b, tam,0);
        printf("\n");


    }else if(strcmp(argv[1], "1") == 0){
        
        for(int i; i<=strlen(Padrao); i++){
        
            fscanf(t, "%c", &a[i]);

            if(a[i] == '\n'){
            
                tam2 = i-1;
                aux1 = tam1;
                tam = (tam2 - tam1);
            
                for(int j = 0 ; j <= tam; j++){
                
                    b[j] = a[aux1];
                    aux1++;
                }
                
                printf("\n");
                printf("%s ", b);
                
                PD(Texto, b, 0);
                
                tam1 = tam2 + 2;
            }
        }

        tam2 = strlen(Padrao);
        aux1 = tam1;
        tam = (tam2 - tam1);
        
        for(int j = 0 ; j <= tam; j++){
                
            b[j] = a[aux1];
            aux1++;
        }

        printf("\n");
        printf("%s ", b);

        PD(Texto, b, 0);

    }else{
        printf("Digite uma op válida!!");
    }

    printf("\n");

    fclose(t);
    free(Texto);
    free(Padrao);

    return 0;
}

/*
int main(){

    TipoTexto tipo = "Texto exemplo, texto tem palavras, palavras exercem fascínio.";
    TipoPadrao tipoP = "palavras";

    shiftAndAprox(tipo, (long)strlen(tipo), tipoP, (long)strlen(tipoP), 0);

    printf("\nLength %ld ", (long)strlen(tipoP));

    return 0;
}
*/