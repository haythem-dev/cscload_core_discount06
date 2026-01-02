#ifndef SQL_ZDCART_INCLUDED
#define SQL_ZDCART_INCLUDED

int sel_herstellnr	( const long art_nr, long * her_nr, char *errmld );
int sel_warengrp	( const long art_nr, char* warengrp, char *errmld);
int sel_zdkwgr		( const char* warengrp, char * sktof, char *errmld);
int sel_zdcoart		( const int *Fd_Zdcoart, const long art_nr, struct ZDCOART *dco, char* errmld);
int ins_zdcart		( const struct ZDCART * const dc, char* errmld);
int del_zdcart		( const long dcnr, const long satznr, char * errmld);
int ins_zdcoart		( const int *Fd_Zdcoart, struct ZDCOART * dc, char* errmld);
int upd_zdcoart		( const int *Fd_Zdcoart, struct ZDCOART * dc, char* errmld);
int del_zdcoart		( const int *Fd_Zdcoart, const long art_nr, char *errmld);
int sel_zartikel	( const long art_nr, long * datum_ah, char * sondergr, char * skontof, char *errmld);
int sel_zartpreis	( const long art_nr, const long datgueltab, double *aep, 
					 double* gep, double *avp, double *herst_prozent, char *errmld);
int sel_ccomgroupprop(const char * const wrgrp, char *taxkz, char *adgep, char *adaep, char *adavp, char *adbez);

#endif
