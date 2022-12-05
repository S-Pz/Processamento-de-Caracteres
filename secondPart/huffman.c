#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <math.h>
#include "stdio.h"

#include "partTwo.h"

// /*E28*/
// #define VAZIO "!!!!!!!!!!"
// #define RETIRADO "**********"
// #define M 7
// #define N 11

// /*H1*/
// #define MAXTAMTEXTO 1000
// #define MAXTAMPADRAO 10
// #define MAXCHAR 256
// #define NUMMAXERROS 10

// /*H33*/
// #define BASENUM 128
// #define MAXALFABETO 255
// #define MAXTAMVETORESDO 10
// #define TRUE 1
// #define FALSE 0

// typedef short TipoAlfabeto[MAXALFABETO + 1];
// typedef struct TipoBaseOffset {
//     int Base, Offset;
// }TipoBaseOffset;

// typedef TipoBaseOffset *TipoVetoresBO;
// typedef char TipoPalavra[256];
// typedef TipoPalavra *TipoVetorPalavra;

// /*E28*/
// typedef unsigned int TipoApontador;
// typedef char TipoChave[N];
// typedef unsigned TipoPesos[N];
// typedef struct TipoItem{
//     /*Outros Componentes*/
//     int Freq, Ordem;
//     TipoChave Chave;
// }TipoItem;

// typedef unsigned int TipoIndice;
// typedef TipoItem TipoDicionario[M];

// /*H1*/
// typedef char TipoTexto[MAXTAMTEXTO];
// typedef char TipoPadrao[MAXTAMPADRAO];

void Particao(TipoIndice Esq, TipoIndice Dir, TipoIndice *i, TipoIndice *j, TipoItem *A){
    
    TipoItem x, w;

    *i = Esq;
    *j = Dir;
    
    x = A[(*i + *j)/2];

    do{
        while (x.Chave > A[*i].Chave){
            (*i)++;
        }
        while(x.Chave < A[*j].Chave){
            (*j)--;
        }
        if(*i <= *j){
            w = A[*i];
            A[*i] = A[*j];
            A[*j] = w;

            (*i)++;
            (*j)--;
        }
    }while(*i <= *j);
}
void Ordena(TipoIndice Esq, TipoIndice Dir, TipoItem *A){

    TipoIndice i, j;
    Particao (Esq, Dir, &i, &j, A);

    if(Esq < j) Ordena(Esq, j, A);
    if(i < Dir) Ordena(i, Dir, A);
}
void QuickSort(TipoItem *A, TipoIndice n){
    Ordena(1, n, A);
}

void GeraPesos(TipoPesos p){

    int i;
    struct timeval semente;
    /*Utilizar o tempo como semente para a função srand()*/
    gettimeofday(&semente, NULL);
    srand((int)(semente.tv_sec + 1000000*semente.tv_usec));

    for(i=0; i<N; i++){
        p[i] = 1+(int)(10000.0*rand())/(RAND_MAX + 1.0);
    }
}
TipoIndice h(TipoChave Chave, TipoPesos p){ 

    int i;
    unsigned int Soma = 0;
    int comp = strlen(Chave);

    for ( i=0; i < comp; i++){
        Soma += (unsigned int)Chave[i]*p[i];
    }
    return (Soma %M);
}

void Inicializa (TipoDicionario T){

    int i;
    for (i=0; i<M; i++){
        memcpy(T[i].Chave, VAZIO, N);
    }
}

TipoApontador Pesquisa(TipoChave Ch, TipoPesos p, TipoDicionario T){

    unsigned int i = 0;
    unsigned int Inicial;

    Inicial = h(Ch, p);

    while(strcmp(T[(Inicial + i) % M].Chave, VAZIO) !=0 && strcmp(T[(Inicial + i) % M].Chave, Ch) != 0 && i<M ){
        i++;
    }
    if(strcmp(T[(Inicial + i) % M].Chave, Ch) == 0){
        return ((Inicial + i) % M);
    }else{
        return M;
    }
}

void Insere(TipoItem x, TipoPesos p, TipoDicionario T){

    unsigned int i = 0;
    unsigned int Inicial;

    if(Pesquisa(x.Chave, p, T) < M){
        printf("Elemento já está presente\n");
        return;
    }
    Inicial = h(x.Chave, p);

    while (strcmp(T[(Inicial + i) %M].Chave, VAZIO) !=0 && strcmp(T[(Inicial + i) %M].Chave, RETIRADO) != 0 && i<M){
        i++;
    }

    if(i<M){
        strcpy(T[(Inicial + i)%M].Chave, x.Chave);
        /*Copiar os demais campos de x, se existirem*/
    }else{
        printf("Tabela cheia\n");
    }
}

int LeNumInt(FILE *ArqComprimido){
    
    int Num;
    fread(&Num, sizeof(int), 1, ArqComprimido);

    return Num;
}

void GravaNumInt(FILE *ArqComprimido, int Num){
    fwrite(&Num, sizeof(int), 1, ArqComprimido);
}
void DefineAlfabeto(TipoAlfabeto Alfabeto, FILE *ArqAlf){

    /*Os Símbolos devem estar juntos em uma linha no arquivo*/
    char Simbolos[MAXALFABETO + 1];
    int i;

    char *Temp;

    for(i =0;i <= MAXALFABETO; i++){
        Alfabeto[i] = FALSE;
        fgets(Simbolos, MAXALFABETO + 1, ArqAlf);
        Temp = strchr(Simbolos, '\n');
    }

    if(Temp!=NULL){
        *Temp =0;
    }
    
    for(i =0; i <= strlen(Simbolos)- 1; i++){
        Alfabeto[Simbolos[i] + 127] = TRUE;
    }

    Alfabeto[0] = FALSE; /*caractere de codigo zero: separador*/
}
char *Trim(char *str){ 

    int i = 0, j, len;
    char *strtmp = malloc(sizeof(char) * strlen(str) + 1);
    
    strcpy(strtmp, str);
    len = strlen(strtmp);
    
    while((i < len) && ((strtmp[i] == ' ') || (strtmp[i] == '\t') || (strtmp[i] == '\r') || (strtmp[i] == ',') || (strtmp[i] == '.'))) i++;
    j = len - 1;
    while((j >= 0) && ((strtmp[j] == ' ') || (strtmp[j] == '\t') || (strtmp[i] == '\r') || (strtmp[i] == ',') || (strtmp[i] == '.'))) j--;
  
    if (j >= 0) str[j + 1] = '\0';
    if (i <= j) memmove(strtmp, strtmp + i, strlen(strtmp + i)+1); 
    else strcpy(strtmp, "");
    
    return strtmp;
}

int Decodifica(TipoVetoresBO VetoresBaseOffset, FILE *ArqComprimido, int MaxCompCod){
    
    int c = 1;
    int Codigo = 0;
    int CodigoTmp = 0;
    int LogBase2 = (int)round(log(BASENUM)) / log(2.0);
    
    fread(&Codigo, sizeof(unsigned char), 1, ArqComprimido);

    if(LogBase2 == 7){
        Codigo -= 128;
    }
    while((c + 1 <= MaxCompCod) && ((Codigo << LogBase2)>= VetoresBaseOffset[c+1].Base)){
        fread(&CodigoTmp, sizeof(unsigned char), 1, ArqComprimido);
        Codigo = (Codigo << LogBase2) | CodigoTmp;
        c++;
    }
    return (Codigo - VetoresBaseOffset[c].Base + VetoresBaseOffset[c].Offset);
}

int LeVetores(FILE * ArqComprimido, TipoBaseOffset *VetoresBaseOffset){
    int MaxCompCod, i;
    MaxCompCod = LeNumInt(ArqComprimido);
    for(i = 1; i<= MaxCompCod; i++){
        VetoresBaseOffset[i].Base = LeNumInt(ArqComprimido);
        VetoresBaseOffset[i].Offset = LeNumInt(ArqComprimido);
    }
    return MaxCompCod;
}

int LeVocabulario (FILE *ArqComprimdo, TipoVetorPalavra Vocabulario){

    int NumNodosFolhas, i;
    TipoPalavra Palavra;

    char Ch;

    NumNodosFolhas = LeNumInt(ArqComprimdo);
    for(i = 1; i<= NumNodosFolhas; i++){
        *Palavra = '\0';

        do{
            fread(&Ch, sizeof(unsigned char), 1, ArqComprimdo);
            if(Ch !=(char)0) /*Palavras estao separadas pelo caracter 0*/

            sprintf(Palavra + strlen(Palavra), "%c", Ch);
        }while(Ch != (char)0);
        strcpy(Vocabulario[i], Palavra);
    }
    return NumNodosFolhas;
}

int Codifica(TipoVetoresBO VetoresBaseOffset, int Ordem, int *c, int MaxCompCod){

    *c = 1;

    while (Ordem >= VetoresBaseOffset[*c+1].Offset && *c + 1 <= MaxCompCod){
        (*c)++;
    }

    return (Ordem - VetoresBaseOffset[*c].Offset + VetoresBaseOffset[*c].Base);
}

void CalculaCompCodigo(TipoDicionario A, int n){
    
    int u=0; /*Nodos internos usados*/
    int h=0; /*Altura da arvore*/
    int NoInt; /*Número de nodos internos*/
    int Prox, Raiz, Folha;
    int Disp = 1;
    int x, Resto;

    if(n > BASENUM - 1){
        Resto = 1 +((n - BASENUM) % (BASENUM - 1));
        if(Resto < 2){
            Resto = BASENUM;
        }
    }else{
        Resto = n-1;
    }
    NoInt = 1 + ((n-Resto) / (BASENUM - 1));
   
    for(x = n-1; x >= (n-Resto)+1; x--){
        A[n].Freq += A[x].Freq;
    }

    /*Primeira Fase*/
    Raiz = n;
    Folha = n - Resto;
    
    for(Prox = n-1; Prox >=(n-NoInt) + 1; Prox --){
        /*Procura Posição*/

        if((Folha < 1) || ((Raiz > Prox) && (A[Raiz].Freq <= A[Folha].Freq))){

            A[Prox].Freq = A[Raiz].Freq;
            A[Raiz].Freq = Prox;
            Raiz --;
        }else{/*No - Folha*/
            A[Prox].Freq = A[Folha].Freq;
            Folha--;
        }
        /*Atualiza Frequencias*/
        for(x = 1; x <= BASENUM - 1; x++){
            if((Folha < 1) || ((Raiz > Prox) && (A[Raiz].Freq <= A[Folha].Freq))){
                /*No interno*/
                A[Prox].Freq += A[Raiz].Freq;
                A[Raiz].Freq = Prox;
                Raiz --;
            }else{/*No-Folha*/
                A[Prox].Freq += A[Folha].Freq;
                Folha --;
            }
        }
    }
    /*Segunda Fase*/
    A[Raiz].Freq = 0;

    for(Prox = Raiz + 1 ; Prox <= n; Prox ++){
        A[Prox].Freq = A[A[Prox].Freq].Freq + 1;
    }
    /*Terceira Fase*/
    Prox = 1;
    while (Disp > 0){
        while(Raiz <= n && A[Raiz].Freq == h){
            u ++;
            Raiz ++;
        }
        while (Disp > u){
            A[Prox].Freq = h;
            Prox++;
            Disp--;

            if(Prox > n){
                u = 0;
                break;
            }
        }
        Disp = BASENUM * u;
        h++;
        u = 0;
    }
}

int ConstroiVetores(TipoVetoresBO VetoresBaseOffset, TipoDicionario Vocabulario, int n, FILE *ArqComprimido){

    int Wcs[MAXTAMVETORESDO + 1];
    int i, MaxCompCod;
    MaxCompCod = Vocabulario[n].Freq;
    
    for(i = 1; i <= MaxCompCod; i++){
        Wcs[i] = 0;
        VetoresBaseOffset[i].Offset = 0;
    }
    for(i = 1; i <= n; i++){
        Wcs[Vocabulario[i].Freq]++;
        VetoresBaseOffset[Vocabulario[i].Freq].Offset = i - Wcs[Vocabulario[i].Freq] + 1;
    }
    VetoresBaseOffset[1].Base = 0;

    for(i = 2; i <= MaxCompCod; i++){
        VetoresBaseOffset[i].Base = BASENUM * (VetoresBaseOffset[i-1].Base + Wcs[i-1]);

        if(VetoresBaseOffset[i].Offset == 0 ){
            VetoresBaseOffset[i].Offset = VetoresBaseOffset[i-1].Offset;
        }
        
    }
    /*Salvando as tableas em disco*/
    GravaNumInt(ArqComprimido, MaxCompCod);

    for(i = 1; i <= MaxCompCod; i++){
        GravaNumInt(ArqComprimido, VetoresBaseOffset[i].Base);
        GravaNumInt(ArqComprimido, VetoresBaseOffset[i].Offset);
    }
    return MaxCompCod;
}

void ExtraiProximaPalavra(TipoPalavra Result, int * TipoIndice, char *Linha, FILE *ArqTxt, TipoAlfabeto Alfabeto){
 
    short FimPalavra = FALSE, Aux = FALSE;
    Result[0] = '\0';
    
    if(*TipoIndice > strlen(Linha)){
        if(fgets(Linha, MAXALFABETO + 1, ArqTxt)){
            /*Coloca um delimitador em linha*/
            sprintf(Linha + strlen(Linha), "%c", (char)0);
            *TipoIndice = 1;

        }else{
            sprintf(Linha, "%c", (char)0);
            FimPalavra = TRUE;
        }
    }
    while (*TipoIndice <= strlen(Linha) && !FimPalavra){
        if(Alfabeto[Linha[*TipoIndice - 1] + 127]){
            sprintf(Result + strlen(Result), "%c", Linha [*TipoIndice - 1]);
            Aux = TRUE;
        }else{
            if(Aux){
                if(Linha[*TipoIndice - 1] != (char)0){
                    (*TipoIndice)--;
                }else{
                    sprintf(Result + strlen(Result), "%c", Linha[*TipoIndice - 1]);
                }
                FimPalavra = TRUE;
            }
            (*TipoIndice)++;
        }
    }
}

void Escreve(FILE *ArqComprimido, int *Codigo, int *c){

    unsigned char Saida[MAXTAMVETORESDO + 1];
    int i = 1, cTmp;
    int LogBase2 = (int)round(log(BASENUM) / log(2.0));
    int Mask = (int) pow(2, LogBase2) -1;

    cTmp = *c;

    Saida[i] = ((unsigned)(*Codigo)) >> ((*c-1) * LogBase2);
    if(LogBase2 == 7){
        Saida[i]= Saida[i] | 0x80;
    }
    i++;
    (*c)--;

    while(*c >0){
        Saida[i] = (((unsigned)(*Codigo)) >> ((*c-1)*LogBase2)) & Mask;
        i++;
        (*c)--;
    }
    for(i = 1; i<= cTmp; i++){
        fwrite(&Saida[i], sizeof(unsigned char), 1, ArqComprimido);
    }
}

TipoIndice OrdenaPorFrequencia(TipoDicionario Vocabulario){

    TipoIndice i;
    TipoIndice n = 1;
    TipoItem Item;
    
    Item = Vocabulario[1];

    for(i=0; i<=M-1; i++){
        if(strcmp(Vocabulario[i].Chave,VAZIO)){
            if(i!=1){
                Vocabulario[n] = Vocabulario[i];
                n++;
            }
        }
    }
    if(strcmp(Item.Chave,VAZIO)){
        Vocabulario[n]= Item;
    }else{
        n--;
    }
    QuickSort(Vocabulario, n);
    return n;
    
}
void PrimeiraEtapa(FILE *ArqTxt, TipoAlfabeto Alfabeto, int *TipoIndice, TipoPalavra Palavra, char *Linha,
                    TipoDicionario Vocabulario, TipoPesos p){

    TipoItem Elemento;
    int i;
    char *PalavraTrim = NULL;

    do{
        ExtraiProximaPalavra(Palavra, TipoIndice, Linha, ArqTxt, Alfabeto);
        memcpy(Elemento.Chave, Palavra, sizeof(TipoChave));

        Elemento.Freq = 1;

        if(*Palavra != '\0'){
            i = Pesquisa(Elemento.Chave, p, Vocabulario);
            if(i < M){
                Vocabulario[i].Freq++;

            }else{
                Insere(Elemento, p, Vocabulario);
            }
            do{
                ExtraiProximaPalavra(Palavra, TipoIndice, Linha, ArqTxt, Alfabeto);
                memcpy(Elemento.Chave, Palavra, sizeof(TipoChave));

                if(PalavraTrim != NULL){
                    free(PalavraTrim);
                }
                PalavraTrim = Trim(Palavra);
                
                if(strcmp(PalavraTrim, "") && (*PalavraTrim) != (char)0){
                    i = Pesquisa(Elemento.Chave, p, Vocabulario);

                    if(i < M){
                        Vocabulario[i].Freq++;
                    }else{
                        Insere(Elemento, p , Vocabulario);
                    }
                }
            }while (strcmp(Palavra, ""));
            if(PalavraTrim != NULL){
                free(PalavraTrim);
            }
        }
    }while (Palavra[0] != '\0');
}

int SegundaEtapa(TipoDicionario Vocabulario, TipoVetoresBO VetoresBaseOffset, TipoPesos p, FILE *ArqComprimido){

    int Result, i, j, NumNodosFolhas, PosArq;
    TipoItem Elemento;
    char Ch;

    TipoPalavra Palavra;
    NumNodosFolhas = OrdenaPorFrequencia(Vocabulario);
    CalculaCompCodigo(Vocabulario,NumNodosFolhas);
    Result = ConstroiVetores(VetoresBaseOffset, Vocabulario, NumNodosFolhas, ArqComprimido);

    /*Grava Vocabulario*/

    GravaNumInt(ArqComprimido, NumNodosFolhas);
    PosArq = ftell(ArqComprimido);

    for(i = 1; i<= NumNodosFolhas; i++){

        j = strlen(Vocabulario[i].Chave);
        fwrite(Vocabulario[i].Chave, sizeof(char), j + 1, ArqComprimido);
    }
    /*Le e reconstroi a condição de hash no vetor que contém o vabulário*/

    fseek(ArqComprimido, PosArq, SEEK_SET);
    Inicializa(Vocabulario);

    for( i = 1; i <= NumNodosFolhas; i++){
        *Palavra = '\0';

        do{
            fread(&Ch, sizeof(char), 1, ArqComprimido);
            if(Ch != (char)0){
                sprintf(Palavra + strlen(Palavra), "%c", Ch);
            }
        }while(Ch != (char)0);
        memcpy(Elemento.Chave, Palavra, sizeof(TipoChave));
        Elemento.Ordem = i;
        j = Pesquisa(Elemento.Chave, p, Vocabulario);

        if(j >= M){
            Insere(Elemento, p, Vocabulario);
        }
    }
    return Result;
}

void TerceiraEtapa(FILE *ArqTxt, TipoAlfabeto Alfabeto, int *TipoIndice, TipoPalavra Palavra, char *Linha,
                    TipoDicionario Vocabulario, TipoPesos p, TipoVetoresBO VetoresBaseOffset, FILE *ArqComprimido,
                    int MaxCompCod){

                        TipoApontador Pos;
                        TipoChave Chave;
                        
                        char *PalavraTrim = NULL;
                        int Codigo, c;

                        do{
                            ExtraiProximaPalavra(Palavra, TipoIndice, Linha, ArqTxt, Alfabeto);
                            memcpy(Chave, Palavra, sizeof(TipoChave));

                            if(*Palavra != '\0'){
                                Pos = Pesquisa(Chave, p, Vocabulario);
                                Codigo = Codifica(VetoresBaseOffset, Vocabulario[Pos].Ordem, &c, MaxCompCod);
                                Escreve(ArqComprimido, &Codigo, &c);
                            
                                do{
                                    ExtraiProximaPalavra(Palavra, TipoIndice, Linha, ArqTxt, Alfabeto);
                                    /*O primeiro espaço depois da palavra não é codificado*/

                                    PalavraTrim = Trim(Palavra);
                                    if(strcmp(PalavraTrim, "") && (*PalavraTrim) != (char)0){
                                        memcpy(Chave, Palavra, sizeof(TipoChave));
                                        Pos= Pesquisa(Chave, p, Vocabulario);
                                        Codigo = Codifica(VetoresBaseOffset, Vocabulario[Pos].Ordem, &c, MaxCompCod);

                                        Escreve(ArqComprimido, &Codigo, &c);
                                    }
                                    if(strcmp(PalavraTrim, "")){
                                        free(PalavraTrim);
                                    }

                                }while(strcmp(Palavra, ""));
                            }
                        }while(*Palavra != '\0');
                    }

void BMH(TipoTexto T, long n, TipoPadrao P, long m){

    long i, j, k, d[MAXCHAR + 1];
    int a,b;
   
    for(j=0; j <= MAXCHAR; j++){
        d[j] = m;
    }
    for(j=1; j < m; j++){
        a= P[j-1];
        d[a] = m - j;
    }
    i = m;

    while(i <= m){
        k = i;
        j = m;

        while(T[k-1] == P[j-1] && j > 0){
            k--;
            j--;
        }
        if(j == 0){
            printf("Casamento na posição: %3ld\n", k + 1);
        }
        b = T[i-1];
        i+= d[b];
    }
}

// H.23 CODIGO PARA FAZER COMPRESSÃO
void Compressao(FILE *ArqTxt, FILE *ArqAlf, FILE *ArqComprimido){ 

    TipoAlfabeto Alfabeto;
    TipoPalavra Palavra, Linha; 

    int Ind = 1, MaxCompCod; 

    TipoPesos p;
    
    TipoDicionario Vocabulario = (TipoDicionario)calloc(M+1, sizeof(TipoItem));
    TipoVetoresBO VetoresBaseOffset = (TipoVetoresBO)calloc(MAXTAMVETORESDO+1, sizeof(TipoBaseOffset));

    fprintf(stderr , "Definindo alfabeto \n");
    DefineAlfabeto(Alfabeto, ArqAlf); /* Lê alfabeto definido em arquivo */
    *Linha = '\0';
    fprintf(stderr, "Inicializando Voc. \n"); 
    Inicializa(Vocabulario);
    fprintf(stderr, "Gerando Pesos \n"); 
    GeraPesos(p);

    fprintf(stderr , "Primeira etapa \n"); 
    PrimeiraEtapa(ArqTxt, Alfabeto, &Ind, Palavra, Linha, Vocabulario, p);
    fprintf(stderr, "Segunda etapa \n" );
    MaxCompCod = SegundaEtapa(Vocabulario, VetoresBaseOffset , p , ArqComprimido);
    fseek (ArqTxt, 0 , SEEK_SET); /* Move o cursor para o início do arquivo */
    Ind = 1;
    *Linha = '\0';

    fprintf(stderr , "Terceira etapa \n");
    TerceiraEtapa(ArqTxt, Alfabeto, &Ind, Palavra, Linha, Vocabulario, p, VetoresBaseOffset, ArqComprimido , MaxCompCod);
    
    free(Vocabulario);
    free(VetoresBaseOffset);
} 
// H.29 CODIGO PARA FAZER DESCOMPRESSÃO
void Descompressao(FILE *ArqComprimido , FILE *ArqTxt, FILE *ArqAlf){

    TipoAlfabeto Alfabeto;
    int Ind, MaxCompCod ;

    TipoVetorPalavra Vocabulario = (TipoVetorPalavra)calloc(256, sizeof(TipoPalavra));
    TipoVetoresBO VetoresBaseOffset = (TipoVetoresBO)calloc(MAXTAMVETORESDO+1,sizeof(TipoBaseOffset));
    TipoPalavra PalavraAnt;

    DefineAlfabeto(Alfabeto, ArqAlf); /* Lê o alfabeto definido no arquivo */
    MaxCompCod = LeVetores(ArqComprimido , VetoresBaseOffset);
    LeVocabulario(ArqComprimido, Vocabulario);

    Ind = Decodifica(VetoresBaseOffset, ArqComprimido, MaxCompCod);
    fputs(Vocabulario[Ind], ArqTxt);

    while (!feof(ArqComprimido)){ 
        Ind = Decodifica(VetoresBaseOffset, ArqComprimido, MaxCompCod);

        if (Ind > 0){ 

            if (Alfabeto[Vocabulario[Ind][0]+127] && PalavraAnt[0] != '\n')
            putc(' ', ArqTxt);
            strcpy(PalavraAnt, Vocabulario[Ind]);
            fputs(Vocabulario[Ind], ArqTxt);
        }
    }
    
    free(VetoresBaseOffset);
    free(Vocabulario);
}
// H.31 FUNÇÃO PARA REALIZAR BUSCA NO ARQUIVO COMPRIMIDO
void Busca(FILE *ArqComprimido , FILE *ArqAlf){ 

    TipoAlfabeto Alfabeto;
    int Ind, Codigo, MaxCompCod;

    TipoVetorPalavra Vocabulario = (TipoVetorPalavra)calloc(M+1,sizeof(TipoPalavra));
    TipoVetoresBO VetoresBaseOffset = (TipoVetoresBO)calloc(MAXTAMVETORESDO+1,sizeof(TipoBaseOffset));

    TipoPalavra p; 
    int c, Ord, NumNodosFolhas;
    TipoTexto T;
    TipoPadrao Padrao;

    memset(T, 0, sizeof(T));
    memset(Padrao, 0, sizeof(Padrao));

    int n = 1;
    DefineAlfabeto(Alfabeto, ArqAlf); /*Le o alfabeto definido em arquivo */

    MaxCompCod = LeVetores(ArqComprimido, VetoresBaseOffset);
    NumNodosFolhas = LeVocabulario(ArqComprimido, Vocabulario);

    while (fread(&T[n], sizeof(char), 1, ArqComprimido)){
        n++;
    }
    while (1){

        printf("Padrao (digite s para terminar): ");
        fgets(p , MAXALFABETO + 1, stdin);
        p[strlen(p)-1] = '\0';

        if (strcmp(p, "s") == 0){
            break;
        }
        
        for (Ind = 1; Ind <= NumNodosFolhas; Ind++){
            if(!strcmp(Vocabulario[Ind],p)) {
                Ord = Ind; 
                break; 
            }
        }

        if (Ind == NumNodosFolhas+1){ 
            printf("Padrao: %s não encontrado /n ", p ); 
            continue; 
        }
        Codigo = Codifica(VetoresBaseOffset , Ord , &c , MaxCompCod);

        Atribui(Padrao, Codigo, c);
        BMH(T, n, Padrao, c);
    }

    free(Vocabulario);
    free(VetoresBaseOffset);
}

void Atribui(TipoPadrao P, int Codigo, int c){
    
    int i = 1;
    P[i] = (char)((Codigo >> ((c - 1) * 7)) | 0x80);
    i++;
    c--;

    while(c>0){
        P[i] = (char)((Codigo >> ((c - 1) * 7)) & 127);
        i++;
        c--;
    }
}

// int main(int argc, char *argv[]){

//     FILE *ArqTxt = NULL, *ArqAlf = NULL; FILE *ArqComprimdo = NULL;
//     TipoPalavra NomeArqTxt, NomeArqAlf, NomeArqComp, Opcao;

//     memset(Opcao, 0, sizeof(Opcao));

//     while(Opcao[0] != 't'){
//         printf("***********************************************\n");
//         printf("*                  Opções                     *\n");
//         printf("* (c) Compressão                              *\n");
//         printf("* (d) Descompressão                           *\n");
//         printf("* (p) Pesquisa no texto comprimido            *\n");
//         printf("* (t) Termina                                 *\n");
//         printf("***********************************************\n");
//         printf("*Opcao:");

//         fgets(Opcao, MAXALFABETO + 1, stdin);

//         stpcpy (NomeArqAlf, "alfabeto.txt");
//         ArqAlf = fopen(NomeArqAlf, "r");

//         if(Opcao[0] == 'c'){

//             printf("Arquivo texto a ser comprimido: ");
//             fgets(NomeArqTxt, MAXALFABETO + 1, stdin);
//             NomeArqTxt[strlen(NomeArqTxt)-1] = '\0';

//             printf("Arquivo comprimido a ser gerado: ");
//             fgets(NomeArqComp, MAXALFABETO + 1, stdin);
//             NomeArqComp[strlen(NomeArqComp)-1] = '\0';

//             ArqTxt = fopen(NomeArqTxt, "r");
//             ArqComprimdo = fopen(NomeArqComp, "w+b");

//             Compressao(ArqTxt, ArqAlf, ArqComprimdo);

//             fclose(ArqTxt);
//             ArqTxt = NULL;
//             fclose(ArqComprimdo);
//             ArqComprimdo = NULL;

//         }else if(Opcao[0] == 'd'){

//             printf("Arquivo texto a ser descomprimido: ");
//             fgets(NomeArqComp, MAXALFABETO + 1, stdin);
//             NomeArqComp[strlen(NomeArqComp)-1] = '\0';

//             printf("Arquivo de texto a ser gerado: ");
//             fgets(NomeArqTxt, MAXALFABETO + 1, stdin);
//             NomeArqTxt[strlen(NomeArqTxt)-1] = '\0';

//             ArqTxt = fopen(NomeArqTxt, "w");
//             ArqComprimdo = fopen(NomeArqComp, "r+b");

//             Descompressao(ArqComprimdo, ArqTxt, ArqAlf);

//             fclose(ArqTxt);
//             ArqTxt = NULL;
//             fclose(ArqComprimdo);
//             ArqComprimdo = NULL;

//         }else if(Opcao[0] == 'p'){

//             printf("Arquivo comprimido para ser pesquisado: ");
//             fgets(NomeArqComp, MAXALFABETO + 1, stdin);
//             NomeArqComp[strlen(NomeArqComp)-1] = '\0';

//             strcpy(NomeArqComp, NomeArqComp);
//             ArqComprimdo = fopen(NomeArqComp, "r+b");

//             Busca(ArqComprimdo, ArqAlf);

//             fclose(ArqComprimdo);
//             ArqComprimdo = NULL;
//         }
       
//     }
   
// }