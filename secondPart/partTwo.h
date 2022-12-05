#ifndef _PART_TWO
#define _PART_TWO

#include <stdio.h>

/*E28*/
#define VAZIO "!!!!!!!!!!"
#define RETIRADO "**********"
#define M 60000
#define N 50

/*H1*/
#define MAXTAMTEXTO 1000
#define MAXTAMPADRAO 10
#define MAXCHAR 256
#define NUMMAXERROS 10

/*H33*/
#define BASENUM 128
#define MAXALFABETO 255
#define MAXTAMVETORESDO 10
#define TRUE 1
#define FALSE 0

typedef short TipoAlfabeto[MAXALFABETO + 1];
typedef struct TipoBaseOffset {
    int Base, Offset;
}TipoBaseOffset;

typedef TipoBaseOffset *TipoVetoresBO;
typedef char TipoPalavra[256];
typedef TipoPalavra *TipoVetorPalavra;

/*E28*/
typedef unsigned int TipoApontador;
typedef char TipoChave[N];
typedef unsigned TipoPesos[N];
typedef struct TipoItem{
    /*Outros Componentes*/
    int Freq, Ordem;
    TipoChave Chave;
}TipoItem;

typedef unsigned int TipoIndice;
typedef TipoItem *TipoDicionario;

/*H1*/
typedef char TipoTexto[MAXTAMTEXTO];
typedef char TipoPadrao[MAXTAMPADRAO];

void Particao(TipoIndice Esq, TipoIndice Dir, TipoIndice *i, TipoIndice *j, TipoItem *A);
void Ordena(TipoIndice Esq, TipoIndice Dir, TipoItem *A);
void QuickSort(TipoItem *A, TipoIndice n);
void GeraPesos(TipoPesos p);
TipoIndice h(TipoChave Chave, TipoPesos p);
void Incializa (TipoDicionario T);
TipoApontador Pesquisa(TipoChave Ch, TipoPesos p, TipoDicionario T);
void Insere(TipoItem x, TipoPesos p, TipoDicionario T);
char *Trim(char *str);

void BMH(TipoTexto T, long n, TipoPadrao P, long m);
void CalculaCompCodigo(TipoDicionario A, int n);
int Codifica(TipoVetoresBO VetoresBaseOffset, int Ordem, int *c, int MaxCompCod);
int Decodifica(TipoVetoresBO VetoresBaseOffset, FILE *ArqComprimido, int MaxCompCod);
int ConstroiVetores(TipoVetoresBO VetoresBaseOffset,TipoDicionario Vocabulario, int n, FILE *ArqComprimido);
int LeNumInt(FILE *ArqComprimido);
void GravaNumInt(FILE *ArqComprimido, int Num);
void DefineAlfabeto(TipoAlfabeto Alfabeto, FILE *ArqAlf);
void ExtraiProximaPalavra(TipoPalavra Result, int * TipoIndice, char *Linha, FILE *ArqTxt, TipoAlfabeto Alfabeto);
void Compressao(FILE *ArqTxt, FILE *ArqAlf, FILE *ArqComprimido);
void PrimeiraEtapa(FILE*ArqTxt,TipoAlfabeto Alfabeto, int *TipoIndice,TipoPalavra Palavra, char *linha,
                    TipoDicionario Vocabulario, TipoPesos p);
int SegundaEtapa(TipoDicionario Vocabulario, TipoVetoresBO VetoresBaseOffset, TipoPesos p,FILE *ArqComprimido);
TipoIndice OrdenaPorFrequencia(TipoDicionario Vocabulario);
void TerceiraEtapa(FILE *ArqTxt, TipoAlfabeto Alfabeto, int *TipoIndice, TipoPalavra Palavra, char *Linha,
                    TipoDicionario Vocabulario, TipoPesos p, TipoVetoresBO VetoresBaseOffset, FILE *ArqComprimido,
                    int MaxCompCod);
void Escreve(FILE *ArqComprimido, int *Codigo, int *c);
void Descompressao(FILE *ArqComprimido , FILE *ArqTxt, FILE *ArqAlf );
int LeVetores(FILE * ArqComprimido, TipoBaseOffset *VetoresBaseOffset);
int LeVocabulario (FILE *ArqComprimdo, TipoVetorPalavra Vocabulario);
void Busca(FILE *ArqComprimido , FILE *ArqAlf);
void Atribui(TipoPadrao P, int Codigo, int c);

#endif