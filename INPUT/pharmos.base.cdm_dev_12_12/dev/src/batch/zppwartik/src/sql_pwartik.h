#ifndef SQL_PWARTIK_INCLUDED
#define SQL_PWARTIK_INCLUDED

#include <zartikel.h>
#include <zartprei.h>
#include <carticlecodes.h>

long sel_ArtNoByCode	( const long code );
long sel_ArtNoByManArt	( char* ArtNoManufacturer );
long sel_NextPseudoArtNo( );

int sel_zartikel	( const int *Fd_ZArtikel, const long art_nr, struct ZARTIKEL *zart, char* errmld);
int upd_zartikel	( const int *Fd_ZArtikel, struct ZARTIKEL *zart, char *errmld);
int ins_zartikel	( const int *Fd_ZArtikel, struct ZARTIKEL *zart, char *errmld);
int del_zartikel	( const int *Fd_ZArtikel, const long art_nr, char * errmld);
int sel_zartpreis	( const int *Fd_ZArtPreis,const long art_nr, struct ZARTPREIS *zpreis, char* errmld);
int ins_zartpreis	( const int *Fd_ZArtPreis,struct ZARTPREIS *zpreis, char *errmld);
int del_preis_artwg_artaustria ( const long art_nr, char *errmld );
int copy_zartpreis  ( const long art_nr_orig, const long art_nr_neu, char *errmld);
int copy_zartwg		( const long art_nr_orig, const long art_nr_neu, char *errmld);
int copy_zartaustria( const long art_nr_orig, const long art_nr_neu, char *errmld);

int ins_carticlecodes( const int *Fd_CArticleCodes, struct CARTICLECODES *codes, char *errmld);

int WriteGrpPflege(long comp_no, char * dezap_sa, long date, char * errmld);
int WritePznPflege(long art_no, char * dezap_sa, long date, char * errmld);
int WriteZAPflege(long art_no, long date, char * errmld);

#define L_ARTIKEL_NR		7

struct ZARTIKEL			m_BufOldZArt;
struct ZARTPREIS		m_BufOldZPreis;

#endif
