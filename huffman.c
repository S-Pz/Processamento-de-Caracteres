#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int ConstroiVetores(TipoVetoresBO VetoresBaseOffset,TipoDicionario Vocabulario, int n, FILE *ArqComprimido){
    int Wcs[MAXTAMVETORESDO + 1];
    int i, MaxCompCod;
    MaxCompCod = Vocabulario[n].Freq;
    
    for(i = 1; i<=n; i++){
        Wcs[i] = 0;
        VetoresBaseOffset[i].Offset = 0;
    }
    for(i = 1; i <= n; i++){
        Wcs[Vocabulario[i].Freq]++;
        VetoresBaseOffset[Vocabulario[i].Freq].Offset = i - Wcs[Vocabulario[i].Freq] + 1;
    }
    VetoresBaseOffset[1].Base = 0;

    for(i = 2; i<= MaxCompCod; i++){
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
    return MaxCompCod
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
    while (*TipoIndice <= strlen(Linha && !FimPalavra)){
        if(Alfabeto[Linha[*TipoIndice - 1] + 127]){
            sprintf(Result + strlen(Result), "%c", Linha [*TipoIndice - 1]);
            Aux = TRUE;
        }else{
            if(Aux){
                if(Linha[*TipoIndice - 1] != (char)0){
                    (*TipoIndice)--;
                }else{
                    sprintf(Result + strlen(Result, "%c", Linha[*TipoIndice - 1]));
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
    int LogBase2 = (int)round(log(BASENUM))/log(2.0);
    int Mask = (int)pow(2, LogBase2)-1;
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
void PrimeiraEtapa(FILE*ArqTxt,TipoAlfabeto Alfabeto, int *TipoIndice,TipoPalavra Palavra, char *linha,
                    TipoDicionario Vocabulario, TipoPesos p){

    TipoItem Elemento;
    int i;
    char *PalavraTrim = NULL;

    do{
        ExtraiProximaPalavra(Palavra, TipoIndice, Linha, ArqTxt, Alfabeto);
        memcpy(Elemento.Chave, Palavra, sizeof(TipoChave));

        Elemento.Freq = 1;

        if(*Palavra != '\0'){
            i = Pesquisa(Elemento.chave, p, Vocabulario);
            if(i < M){
                Vocabulario[i].Freq++;

            }else{
                Insere(&Elemento.Chave, p, Vocabulario);
            }
            do{
                ExtraiProximaPalavra(Palavra, TipoIndice, Linha, ArqTxt, Alfabeto);
                memcpy(Elemento.chave, Palavra, sizeof(TipoChave));

                if(PalavraTrim != NULL){
                    free(PalavraTrim);
                }
                PalavraTrim = Trim(Palavra);
                
                if(strcmp(PalavraTrim, "") && (*PalavraTrim) != (char)0){
                    i = Pesquisa(Elemento.chave, p, Vocabulario);

                    if(i < M){
                        Vocabulario[i].Freq++;
                    }else{
                        Insere(&Elemento, p , Vocabulario);
                    }
                }
            }while (strcmp(Palavra, ""));
            if(PalavraTrim != NULL){
                free(PalavraTrim);
            }
        }
    }while (Palavra[0] != '\0');
}

int SegundaEtapa(TipoDicionario Vocabulario, TipoVetoresBO VetoresBaseOffset, TipoPeso p,FILE *ArqComprimido){

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

    for( i = 1; i < NumNodosFolhas; i++){
        *Palavra = '\0';

        do{
            fread(&Ch, sizeof(char), 1, ArqComprimido);
            if(Ch != (char)0){
                sprintf(Palavra + strlen(Palavra), sizeof(TipoChave));
            }
        }while(Ch != (char)0);
        memccpy(Elemento.Chave, Palavra, sizeof(TipoChave));
        Elemento.Ordem = i;
        j = Pesquisa(Elemento.Chave, p, Vocabulario);

        if(j >= M){
            Insere(&Elemento, p, Vocabulario);
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
                                    if(stcmp(PalavraTrim, "") && (*PalavraTrim) != (char)0){
                                        memcpy(Chave, Palavra, sizeof(TipoChave));
                                        Codigo = Codifica(VetoresBaseOffsetm, Vocabulario[Pos].Ordem, &c, MaxCompCod);

                                        Escreve(ArqComprimido, &Codigo, &c);
                                    }
                                    if(stcmp(PalavraTrim, "")){
                                        free(PalavraTrim)
                                    }

                                }while(stcmp(Palavra, ""));
                            }
                        }while(*Palavra != '\0');
                    }