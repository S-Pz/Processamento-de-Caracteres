#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"shiftAnd_Aprox.h"

char *read_file(char *file){

    FILE *arq;

    arq = fopen (file, "r");

    if (arq == NULL){
        return NULL;
    }

    //Go to end of file and get size to alloc memory to string down below
    fseek(arq, 0, SEEK_END);
    int size = ftell(arq); // obtain size of file
    fseek(arq, 0, SEEK_SET);

    //Alloc string witch size founded in file 
    char *string = malloc(sizeof(char)*(size+1));

    char c;
    int i=0;

    // Obtain the characters in file and put them in the string
    while ((c = fgetc(arq)) != EOF){

        string[i] = c;
        i++;
    }

    //Put the special character in final of string 
    string[i] = '\0';

    //Close file and return
    fclose(arq);
    return string;
}

void shiftAndAprox(char *T, long n, char *P, long m, long k){
    
    long Masc[MAXCHAR], i, j, Ri, Rant, Rnovo;
    long R[NUMMAXERROS + 1];
    
    for(i=0; i<MAXCHAR; i++){
        Masc[i] = 0;
    }
    for(i = 0; i<=m; i++){
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
            printf("%12ld" , i+1);
        }
    }
}

long PD(char *T, char *P, long k){

    long i , pos, o;
    long n, m;
    long lact ,nC,pC;
    long *C;

    n = strlen(T); // tamanho do texto  
    m = strlen(P); // tamanho da palavra
    
    C = (long*)malloc(sizeof(long)*(m+1));

    for(i=0;i<=m; i++){
        C[i] = i ;
    }
    o = 0;  // numero de ocorrencias
    lact = k + 1; // erros

    for(pos=1;pos<=n;pos++){   // procurando
        pC = 0;
        nC = 0;
    
        for(i=1;i<=lact; i++){
            
            if (P[ i-1] ==T[pos-1]){
                nC = pC;
            }else{
                if (pC < nC){
                    nC = pC;
                } 
                if (C[i] < nC){
                    nC = C[i] ;
                } 
                nC++;
            }
            pC = C[ i ] ;
            C[ i ] = nC;
        }
        
        while(C[lact] > k){
            lact--;
        }
        if (lact == m){
            o++; 
            printf("%ld \n" , pos - m);
            
        }else{
            lact++;
            
        }
    }
    free (C);
    return o;
}

