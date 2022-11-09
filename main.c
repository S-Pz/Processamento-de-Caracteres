#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"shiftAnd_Aprox.h"
/*
int main(int argc, char const *argv[]){

    FILE *textFile, *defFile;

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

    for(int i=0 ; i<10 ; i++){
        int num;

        fscanf(defFile,"%d",&num);
        printf("%d",num);
        printf("\n");
    }

    fclose(textFile);
    fclose(defFile);
    return 0;
}
*/
int main(){

    TipoTexto tipo = "Texto exemplo, texto tem palavras, palavras exercem fascínio.";
    TipoPadrao tipoP = "palavras";

    shiftAndAprox(tipo, (long)strlen(tipo), tipoP, (long)strlen(tipoP), 0);

    printf("\nLength %ld ", (long)strlen(tipoP));

    return 0;
}