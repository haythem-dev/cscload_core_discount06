#ifndef SQL_IMPARTIK_INCLUDED
#define SQL_IMPARTIK_INCLUDED

#include <zartikel.h>
#include <zartprei.h>
#include <carticlecodes.h>
#include <herstel.h>
#include <cimexmanufacturermapping.h>
#include <herlief.h>
#include <ean.h>
#include <cimportarticleparam.h>
#include <zartwg.h>
#include <zartaustria.h>
#include <bliesort.h>

#define L_ARTIKEL_NR		7
#define L_HERSTELLER_NR		5

int WriteGrpPflege(long comp_no, char * dezap_sa, long date, char * errmld);
int WritePznPflege(long art_no, char * dezap_sa, long date, char * errmld);
int WriteZAPflege(long art_no, long date, char * errmld);

long StartTransaction ( char *errmld );
long CommitTransaction( char *errmld );
void CancelTransaction( void );

int sel_importParam	( const int *Fd_Cimportarticleparam, char * exportCountry, struct CIMPORTARTICLEPARAM *importParam, char* errmld);

struct HERSTEL_IMPORTDATA  {
       long    HERSTELLER_NR        ;
       char    NAME                 [L_HERSTEL_NAME + 1];
       char    SORTIERNAME          [L_HERSTEL_SORTIERNAME + 1];
       char    PLZ                  [L_HERSTEL_PLZ + 1];
       char    ORT                  [L_HERSTEL_ORT + 1];
       char    STRASSE              [L_HERSTEL_STRASSE + 1];
       char    HAUSNR_VON           [L_HERSTEL_HAUSNR_VON + 1];
       char    LANDESKUERZEL        [L_HERSTEL_LANDESKUERZEL + 1];
       char    VORWAHL              [L_HERSTEL_VORWAHL + 1];
       char    TELEFON_NR           [L_HERSTEL_TELEFON_NR + 1];
       char    VORWAHL_TELEFAX      [L_HERSTEL_VORWAHL_TELEFAX + 1];
       char    FAX_NR               [L_HERSTEL_FAX_NR + 1];
};

struct HERSTEL		m_BufHerstelOld;
static int fd_sel_export_manuf;
int sel_herstel	( const int *Fd_Herstel, const long hnr, struct HERSTEL *herst, char* errmld);
int upd_herstel	( const int *Fd_Herstel, struct HERSTEL *herst, char *errmld);
int ins_herstel	( const int *Fd_Herstel, struct HERSTEL *herst, char *errmld);
int openCs_export_manuf( char *dbexp, const long datefrom, char * exportCountry, char* errmld);
int fetchNext_export_manuf( struct HERSTEL_IMPORTDATA * impdata, char* errmld );
long sel_HnrByExportManufacturer( long manufacturerNo, char * exportCountry, char* errmld );
long sel_NextInternalHnr( char *errmld );

int ins_cimexmanufmapping	( const int *Fd_Cimexmanufacturermapping, struct CIMEXMANUFACTURERMAPPING *manufMap, char *errmld);
int ins_herlief	( const int *Fd_Herlief, struct HERLIEF *herlief, char *errmld);



struct ARTICLE_IMPORTDATA  {
		long	ARTIKEL_NR;
		short	EXPORTPERMISSIONFLAG;
		char    ARTIKEL_MC                    [L_ZARTIKEL_ARTIKEL_MC + 1];
		char    ARTIKEL_NAME                  [L_ZARTIKEL_ARTIKEL_NAME + 1];
		long    LAENGE                        ;
		long    BREITE                        ;
		long    HOEHE                         ;
		long    GEWICHT                       ;
		char    KUEHLARTIKEL                  [L_ZARTIKEL_KUEHLARTIKEL + 1];
		char    DARREICHFORM                  [L_ZARTIKEL_DARREICHFORM + 1];
		char    EINHEIT                       [L_ZARTIKEL_EINHEIT + 1];
		char    ARZNEIMITTEL                  [L_ZARTIKEL_ARZNEIMITTEL + 1];
		char    TIERARZNEI	                  [L_ZARTIKEL_TIERARZNEI + 1];
		char    REZEPTPFL	                  [L_ZARTIKEL_REZEPTPFL + 1];
		char    APOTHEKENPFL                  [L_ZARTIKEL_APOTHEKENPFL + 1];
		char    CHARGENARTIKEL                [L_ZARTIKEL_CHARGENARTIKEL + 1];
		short   BIOSIEGEL                     ;
		long    HERSTELLER_NR_EXP             ;
		char    NAME                 [L_HERSTEL_NAME + 1];
		char    SORTIERNAME          [L_HERSTEL_SORTIERNAME + 1];
		char    PLZ                  [L_HERSTEL_PLZ + 1];
		char    ORT                  [L_HERSTEL_ORT + 1];
		char    STRASSE              [L_HERSTEL_STRASSE + 1];
		char    HAUSNR_VON           [L_HERSTEL_HAUSNR_VON + 1];
		char    LANDESKUERZEL        [L_HERSTEL_LANDESKUERZEL + 1];
		char    VORWAHL              [L_HERSTEL_VORWAHL + 1];
		char    TELEFON_NR           [L_HERSTEL_TELEFON_NR + 1];
		char    VORWAHL_TELEFAX      [L_HERSTEL_VORWAHL_TELEFAX + 1];
		char    FAX_NR               [L_HERSTEL_FAX_NR + 1];
		long    HERSTELLER_NR_IMP             ;
		char	EAN_NR				 [L_EAN_EAN_NR + 1];
		char	ATC_CODE			 [L_CARTICLECODES_ARTICLE_CODE + 1];
		char	NTIN_CODE			 [L_CARTICLECODES_ARTICLE_CODE + 1];
		char	PZN8				 [L_CARTICLECODES_ARTICLE_CODE + 1];
		};

struct ZARTIKEL			m_BufOldZArt;
static int fd_sel_export_article;
long sel_ArtNoByManArt	( char* ArtNoManufacturer, char* errmld );
int sel_zartikel	( const int *Fd_ZArtikel, const long art_nr, struct ZARTIKEL *zart, char* errmld);
int upd_zartikel	( const int *Fd_ZArtikel, struct ZARTIKEL *zart, char *errmld);
int ins_zartikel	( const int *Fd_ZArtikel, struct ZARTIKEL *zart, char *errmld);
int openCs_export_article( char *dbexp, char * importCountry, char * exportCountry, char* errmld );
int fetchNext_export_article( struct ARTICLE_IMPORTDATA * impdata, char* errmld );
long sel_NextInternalPzn( char *errmld );


struct CARTICLECODES	m_BufOldCodes;
int ins_carticlecodes( const int *Fd_CArticleCodes, struct CARTICLECODES *codes, char *errmld);
int upd_carticlecodes( const int *Fd_CArticleCodes, struct CARTICLECODES *codes, char *errmld);
int sel_atccode		 ( const int *Fd_CArticleCodes, const long art_nr, struct CARTICLECODES *codes, char* errmld);
int del_atccode		 ( const int *Fd_CArticleCodes, const long art_nr, char* errmld);
int sel_ntincode	 ( const int *Fd_CArticleCodes, const long art_nr, struct CARTICLECODES *codes, char* errmld);
int del_ntincode	 ( const int *Fd_CArticleCodes, const long art_nr, char* errmld);

struct EAN	m_BufOldEan;
int ins_ean( const int *Fd_Ean, struct EAN *ean, char *errmld);
int upd_ean( const int *Fd_Ean, struct EAN *ean, char *errmld);
int sel_ean( const int *Fd_Ean, const long art_nr, struct EAN *ean, char* errmld);
int del_ean( const int *Fd_Ean, const long art_nr, char* errmld);

int ins_zartwg		( const int *Fd_ZArtWg, struct ZARTWG *wg, char *errmld);
int ins_zartaustria	( const int *Fd_ZArtAustria, struct ZARTAUSTRIA *zaustria, char *errmld);
int ins_bliesort	( const int *Fd_Bliesort, struct BLIESORT *bliesort, char *errmld);

int markOutdatedArticlesAsDeleted (short month, const char *bearbeiter, char *errmld);
int markExportArticleAsImportProcessed (char *dbexp, char * importCountry, long artNo, char* errmld);


struct PRICE_IMPORTDATA  {
		long	ARTIKEL_NR;
		long    DATUMGUELTIGAB     ;
		double  GROSSO             ;
		double  AEP                ;
		double  AVP                ;
};

static int fd_sel_export_price;
int openCs_export_price( char *dbexp, const long art_nr, char* errmld );
int closeCs_export_price( );
int fetchNext_export_price( struct PRICE_IMPORTDATA * impdata, char* errmld );
int sel_zartpreis	( const int *Fd_ZArtPreis,const long art_nr, const long datefrom, struct ZARTPREIS *zpreis, char* errmld);
int save_zartpreis	( const int *Fd_ZArtPreis,struct ZARTPREIS *zpreis, char *errmld);
struct ZARTPREIS		m_BufOldZPreis;


#endif
