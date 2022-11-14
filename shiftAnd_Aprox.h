#ifndef _SHIFT_AND_APROX
#define _SHIFT_AND_APROX

#define MAXTAMTEXTO 1000
#define MAXTAMPADRAO 10
#define MAXCHAR 256
#define NUMMAXERROS 100

typedef char TipoTexto[MAXTAMTEXTO];
typedef char TipoPadrao[MAXTAMPADRAO];

void shiftAndAprox(char *, long, char *, long, long);
long PD(char *, char *, long);

char *read_file(char *);

#endif