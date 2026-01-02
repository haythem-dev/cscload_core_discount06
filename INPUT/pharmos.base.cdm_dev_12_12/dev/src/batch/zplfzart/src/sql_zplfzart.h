#ifndef SQL_ZPLFZART_INCLUDED
#define SQL_ZPLFZART_INCLUDED

#include <voodoo_table_header/zartikel.h>
#include <voodoo_table_header/ean.h>
#include <voodoo_table_header/chealthinsurance.h>
#include <voodoo_table_header/chealthinsurancearticles.h>
#include <voodoo_table_header/chealthinsurancegroups.h>
#include <voodoo_table_header/carticlecodes.h>

int sel_zartikel	( const int *Fd_ZArtikel, const long art_nr, struct ZARTIKEL *zart, char* errmld);
int upd_zartikel	( const int *Fd_ZArtikel, struct ZARTIKEL *zart, char *errmld);

int sel_ean			( const int *Fd_Ean, const char* ean, const long art_nr, struct EAN *ean_struct, char* errmld );
int ins_ean			( const int *Fd_Ean, struct EAN *ean_struct, char *errmld);

int sel_chealthinsurance	( const int *Fd_CHealthInsurance, const long hiid, struct CHEALTHINSURANCE *chi, char* errmld);
int upd_chealthinsurance	( const int *Fd_CHealthInsurance, struct CHEALTHINSURANCE *chi, char *errmld);
int ins_chealthinsurance	( const int *Fd_CHealthInsurance, struct CHEALTHINSURANCE *chi, char *errmld);
int del_chealthinsurance	( const int *Fd_CHealthInsurance, struct CHEALTHINSURANCE *chi, char *errmld);

int sel_chealthinsurancearticle	( const int *Fd_CHealthInsuranceArticles, const long higroup, const long articleno, struct CHEALTHINSURANCEARTICLES *chia, char* errmld);
int ins_chealthinsurancearticle	( const int *Fd_CHealthInsuranceArticles, struct CHEALTHINSURANCEARTICLES *chia, char *errmld);
int del_chealthinsurancearticle	( const int *Fd_CHealthInsuranceArticles, struct CHEALTHINSURANCEARTICLES *chia, char *errmld);

int sel_chealthinsurancegroups	( const int *Fd_CHealthInsuranceGroups, const long higroup, const long hiid, struct CHEALTHINSURANCEGROUPS *chig, char* errmld);
int ins_chealthinsurancegroups	( const int *Fd_CHealthInsuranceGroups, struct CHEALTHINSURANCEGROUPS *chig, char *errmld);
int del_chealthinsurancegroups	( const int *Fd_CHealthInsuranceGroups, struct CHEALTHINSURANCEGROUPS *chig, char *errmld);

int sel_carticlecodes	( const int *Fd_Atc, const long artnr, struct CARTICLECODES *codes, char* errmld);
int upd_carticlecodes	( const int *Fd_Atc, struct CARTICLECODES *codes, char *errmld);
int ins_carticlecodes	( const int *Fd_Atc, struct CARTICLECODES *codes, char *errmld);
int del_carticlecodes	( const int *Fd_Atc, struct CARTICLECODES *codes, char *errmld);

long sel_ArtNoByCode	( const long code );
int  isNarcoticStillUnset ( char* atcCode, const long artNr );

struct CHEALTHINSURANCE			m_BufOldCHi;
struct CHEALTHINSURANCE*		getOldBufCHi ();

struct ZARTIKEL			m_BufOldZArt;
struct ZARTIKEL*		getOldBufZArt ();

struct CARTICLECODES			m_BufOldCodes;
struct CARTICLECODES*			getOldBufCodes ();

#endif
