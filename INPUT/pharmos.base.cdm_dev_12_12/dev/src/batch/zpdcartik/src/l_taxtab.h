#if !defined(LSTAXTAB_H_INCLUDED)
#define LSTAXTAB_H_INCLUDED


#define TAXTAB_IS_VOLLMWST  0 //in datacare.txt = 2
#define	TAXTAB_IS_VERMMWST  1 //identical to datacare.txt
#define TAXTAB_IS_3RD		2 //in datacare.txt = 3
#define TAXTAB_IS_KMWST		3 //in datacare.txt = 0

	int CreateTaxtabAustria( long * grenzeHochpreis, char* cErrmld );
	void KaufmRunden( double *wert, int stellen );

	int CalcAekAustria( double grosso, double *aek, long datum, char taxmode );
	int CalcAvkAustriaMwst( double aek, double *avk, int mwst_art, long datum, char taxmode, char btm );
	
#endif
