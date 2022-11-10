#include<stdio.h>
#include<stdlib.h>


#include"shiftAnd_Aprox.h"


char *read_file(char *file){

    FILE *arq;

    arq = fopen (*file, "r");

    if (*file == NULL){
        return NULL;
    }

    fseek(*file, 0, SEEK_END);
    int size = ftell(*file);
    fseek(*file, 0, SEEK_SET);

    char *string = malloc(sizeof(char)*(size+1));

    char c;
    int i=0;

    while ((c = fgetc(*file)) != EOF){

        string[i] = c;
        i++;
    }

    string[i] = "\0";

    fclose(*file);

    return string;
}



void shiftAndAprox(TipoTexto T, long n, TipoPadrao P,long m, long k){

    long Masc[MAXCHAR], i, j, Ri, Rant, Rnovo;
    long R[NUMMAXERROS + 1];

    for(i=0; i<MAXCHAR; i++){
        Masc[i] = 0;
    }
    for(i=1; i<=m; i++){
        Masc[P[i-1] + 127] |= 1 << (m-i);
    }

    R[0] = 0;
    Ri = 1 << (m-1);
    
    for(j=1; j<=k; j++){
        R[j] = (1 << (m-j)) | R[j-1];
    }
    for(i=0; i<n; i++){

        Rant = R[0];
        Rnovo = ((((unsigned long)Rant) >> 1) | Ri) & Masc[T[i] + 127];
        R[0]=Rnovo;

        for(j=1; j<=k; j++){

            Rnovo = ((((unsigned long)R[j]) >> 1 ) & Masc[T[i] + 127]) | Rant | (((unsigned long)(Rant | Rnovo)) >> 1);
            Rant = R[j];
            R[j] = Rnovo |Ri;
        }
        if((Rnovo & 1) != 0){
            printf("Casamento na posição %12ld\n" , i+1);
        }
    }
}


