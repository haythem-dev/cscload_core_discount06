/* ---------------------------------------------------------------------- *
 *                            CHECK_PLAUSI.H                                  *
 * ---------------------------------------------------------------------- */

#ifndef CHECK_PLAUSI_INCLUDED
#define CHECK_PLAUSI_INCLUDED


int CheckPruefziffer ( long pzn );
void SetNZwing ( struct ZDCART *dc, char *errmld);
void SetZwing ( struct ZDCART *dc, char *errmld);
void CalcKZs ( struct ZDCART *dc, long grenzeHochpreis, char * skontof, char *errmld );
int CheckPrices ( struct ZDCART *dc, double* aep, double *gep, double *avp, 
				 double * herst_prozent, char adgep, char adaep, char *errmld );
int PricesPlausi( struct ZDCART *dc );


#endif
