#if !defined(L_TAXTAB_INCLUDED)
#define L_TAXTAB_INCLUDED

#define TAXTAB_IS_VOLLMWST  0
#define TAXTAB_IS_VERMMWST  1
#define TAXTAB_IS_OHNEMWST  2

int  CreateTaxtab( char *cErrmld );
void KaufmRunden( double *wert, int stellen );

int  CalcAek( double grosso, double *aek, long datum, char taxmode  );
int  CalcAvkMwst( double aek, double *avk, int mwst_art, long datum, char taxmode  );

#endif /* !defined(L_TAXTAB_INCLUDED) */

