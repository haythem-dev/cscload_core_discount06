#ifndef SQL_ZLIART_INCLUDED
#define SQL_ZLIART_INCLUDED

int sel_zartikel	( const long art_nr, long *her_nr, long *awl1, char* name, long *datum_ah, 
						char* preis0, char* gesperrt, char* privat, char* verfall, char* vb_apo, char* vb_inland, char* vb_kanton, char* vb_kuenzle, char* vb_spital, 
						char* phyto, char* homeo, char* anthro, char* tierarznei, char* med, char* impfst, char* chargenartikel, double *herst_proz, char *errmld);
int sel_zartpreis	( const long art_nr, const long datgueltab, /*double *aep, double* gep, double *avp,*/ double *lbp, char *errmld);
int sel_phar		( const long prdno, char *errmld );
int fetch_next		( long *pzn, char *errmld );

int sel_productgrp	( const long prdno, char *errmld );
int fetch_next_productgrp( char* prdgrpcd, char *errmld );

int read_clioart_into_cliartBuf	( struct CLIART * li, char *errmld );
int read_cliproduct_into_cliartBuf( struct CLIART * li, const long prdno, char *errmld );

int sel_cliart		( const int *Fd_Cliart, const long art_nr, const long lidatumnr, struct CLIART *li, char* errmld);
int sel_clioart		( const int *Fd_Clioart, const long art_nr, struct CLIOART *lio, char* errmld);
int sel_clicompany	( const int *Fd_Clicompany, const long prtno, struct CLICOMPANY *licomp, char* errmld);
int sel_cassortmentcode	( const int *Fd_Cassortmentcode, char* code, struct CASSORTMENTCODE *assortcode, char* errmld);
int sel_catccode	( const int *Fd_Catccode, char* code, struct CATCCODE *atccode, char* errmld);
int ins_cliart		( const int *Fd_Cliart, const struct CLIART * const li, char* errmld);
int upd_cliart		( const int *Fd_Cliart, struct CLIART * li, char* errmld);
int ins_clicompany	( const int *Fd_Clicompany, const struct CLICOMPANY * const licomp, char* errmld);
int ins_catccode	( const int *Fd_Catccode, struct CATCCODE * atccode, char* errmld);
int ins_cassortmentcode ( const int *Fd_Cassortmentcode, struct CASSORTMENTCODE * assortcode, char* errmld);
int ins_clioart		( const int *Fd_Clioart, struct CLIOART * lio, char* errmld);
int upd_clioart		( const int *Fd_Clioart, struct CLIOART * lio, char* errmld);
int upd_clicompany	( const int *Fd_Clicompany, struct CLICOMPANY * licomp, char* errmld);

int sel_ean_by_ean	( long *art_nr, char* ean_nr, char *errmld);
int sel_ean_by_pzn	( const long art_nr, char* ean_nr, char *errmld);
long checkGtin14Exists(  long artno, char * gtin );
int sel_ersatz		( const long ersatz_nr, char *errmld);
int sel_warengruppe	( const long art_nr, char* art, char* wgr, char *errmld);

long sel_count_cliohsatz	(const long phar, long* count, char* errmld);
long exists_cliohsatz		(const long phar, const char* hazardnoteid, long* result, char* errmld);
int del_all_cliohsatz		(const int* Fd_Cliohsatz, const long phar, char* errmld);
int ins_cliohsatz			(const int* Fd_Cliohsatz, const struct CLIOHSATZ* cliohasatz, char* errmld);

int del_all_clihsatz		(const int* Fd_Clihsatz, const long phar, const long linr, char* errmld);
int ins_clihsatz			(const int* Fd_Clihsatz, const struct CLIHSATZ* clihasatz, char* errmld);

long exists_hsatz			(const char* hazardnoteid, long* result, char* errmld);

int read_clio_subartdan		(struct SUBARTDAN* subartdan, char *errmld);
int read_clio_subartcomp	(struct SUBARTCOMP* subartcomp, char *errmld);

long exists_cliosatz	(const long phar, long* result, char* errmld);

int sel_cliproduct	( const int *Fd_Cliproduct, const long prdno, struct CLIPRODUCT *liproduct, char* errmld);
int ins_cliproduct	( const int *Fd_Cliproduct, struct CLIPRODUCT * liproduct, char* errmld);
int upd_cliproduct	( const int *Fd_Cliproduct, struct CLIPRODUCT * liproduct, char* errmld);
int sel_cliproductgrp(const int *Fd_Cliproductgrp, const long prdno, const char* prdgrpcd, struct CLIPRODUCTGRP *liproductgrp, char* errmld);
int ins_cliproductgrp(const int *Fd_Cliproductgrp, struct CLIPRODUCTGRP * liproductgrp, char* errmld);
int del_cliproductgrp(const int* Fd_Cliproductgrp, const long prdno, char* errmld);

#endif
