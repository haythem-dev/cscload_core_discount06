#if !defined(L_TAXTAB_INCLUDED)
#define L_TAXTAB_INCLUDED

#define TAXTAB_IS_VOLLMWST  0
#define TAXTAB_IS_VERMMWST  1
#define TAXTAB_IS_OHNEMWST  2

int  CreateTaxtab( char *cErrmld );

int  CalcAvk( double aek, double *avk, double mwstproz, long datum, char taxmode  );
int  CalcAek( double grosso, double *aek, long datum, char taxmode  );

#endif /* !defined(L_TAXTAB_INCLUDED) */

