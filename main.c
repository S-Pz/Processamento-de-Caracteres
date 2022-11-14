#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"shiftAnd_Aprox.h"
/*
int main(int argc, char const *argv[]){
    
    // Implementar a questão de selecionar o dinâmico ou o shift-and aprox

    FILE *textFile, *defFile;

    printf("Argc: %d", argc);

    for(int i=0; i<argc;i++){
        
        printf("%s %d\n",argv[i],i);
        printf("\n");
    }

    textFile = fopen(argv[2],"r"); // Open text file.
    defFile = fopen(argv[3],"r"); // Opend defeault file, with contains the relation to find in the text.

    for(int i=0 ; i<10 ; i++){
        int num;

        fscanf(textFile,"%d",&num);
        printf("%d",num);
    }

    printf("\n\n");

    for(int i=0 ; i<16 ; i++){
        char num[16];

        fscanf(defFile,"%c",&num[i]);
        printf("%s\n",num);
    }

    fclose(textFile);
    fclose(defFile);
    return 0;
}
*/

// TO RUN  THIS PROGRAM TYPE IN TERMINAL : ./tp3 -i texto.txt padrao.txt
int main(int agrc, char *argv[]){

    FILE *t;
    char a[200];
    char b[200];
    int tam1 = 0;
    int tam2 = 0;
    int aux1;
    int tam = 0;
    char *Text,*Def;
    long o;

    Text = read_file(argv[2]);
    Def = read_file(argv[3]);

    t = fopen(argv[3],"r");

    for(int i; i<=strlen(Def); i++){
        
        fscanf(t,"%c",&a[i]);

        if(a[i] == '\n'){
            
            tam2 = i-1;
            aux1 = tam1;
            tam = (tam2 - tam1);

            for(int j = 0 ; j <= tam; j++){
               
               b[j] = a[aux1];
               aux1++;
               //printf("%c", b[j]);
            }
            //shiftAndAprox(Text, (long)strlen(Text), b, tam,0);
            o = PD(Text, b, 0);
            printf("quantidade de casamentos: %ld \n", o);
            //printf("\n");
            tam1 = tam2 + 2;
        }
    }
    tam2 = strlen(Def);
    aux1 = tam1;
    tam = (tam2 - tam1);

    for(int j = 0 ; j <= tam; j++){
        
        b[j] = a[aux1];
        aux1++;
        //printf("%c", b[j]);
    }

    //shiftAndAprox(Text, (long)strlen(Text), b, tam,0);
    o = PD(Text, b, 0);
    printf("quantidade de casamentos: %ld \n", o);

    //printf("\n");

    fclose(t);
    free(Text);
    free(Def);

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