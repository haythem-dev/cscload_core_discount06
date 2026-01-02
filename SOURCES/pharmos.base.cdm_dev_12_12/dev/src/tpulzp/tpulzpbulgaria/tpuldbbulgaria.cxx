
/******************************************************************************/
/*     Hauptmodul: tpulzpbulgaria                                             */
/*         Source: tpuldbbulgaria.cxx                                         */
/*          Autor: R. Raab                                                    */
/*       Erstellt: 01042.1998                                                 */
/*        Sprache: C/Esql-C                                                   */
/*        Erzeugt: basierend auf tpulzentpfl                                  */
/*        Aufgabe: sätze aus DB lesen                                         */
/*                                                                            */
/******************************************************************************/

/*** INCLUDE ******************************************************************/


 #ifndef ESQL_C
 #define ESQL_C 
 #endif

 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include <memory.h>

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

 #include <voodoo_table_header/zartwg.h>
 #include <voodoo_table_header/zartsekb.h>
 #include <voodoo_table_header/zartprei.h>
 #include <voodoo_table_header/zartikel.h>
 #include <voodoo_table_header/zapflege.h>
 #include <voodoo_table_header/zartbulgaria.h>
 #include <voodoo_table_header/artve.h>
 #include <voodoo_table_header/ean.h>
 #include <voodoo_table_header/carticlelang.h>
 #include <voodoo_table_header/zdkwir.h>
 #include <voodoo_table_header/cregisters.h>

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

 #include "tpulzpbulgaria.h"
 #include "cdb.h"
 #include "logfile.h"

 #include "tpuldbbulgaria.h"

 exec sql include sqlca;


/*** MACRO *********************************************************************/

 #define VERIFY(x) { int rc; if ( (rc = x) !=0 ) { \
                     return (rterror)(rc == SQLNOTFOUND ? eof:db_error);} }
 
/*** DECLARATION ***************************************************************/

/* hajo: warum dieser Schwachsinn ???????? */

/*   static int verify( char *spFun, int iError, char *spText );  */
 
/*** VERIFY ********************************************************************/

 static int verify( char *spFun, char *spText )
 {
   if ( sqlca.sqlcode < 0 )
      WriteLog( spFun, sqlca.sqlcode, "%s", spText );
   return sqlca.sqlcode;
 }

/*** START-BROWSE ******************************************************/

 rterror startBrowse( const long lDateCurrent, const long lDateUntil, const long lDateDelete, const char *spDatabase )
 {
   exec sql begin declare section;
   char szBuf[4096];
   long lDateOfTheDay;
   long lDateTo;
   long lDateSince;
   exec sql end declare section;
   char *fun = "startBrowse";

   lDateOfTheDay = lDateCurrent;
   lDateTo = lDateUntil;
   lDateSince    = lDateDelete;
   
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_ZARTIKEL );
   strcat( szBuf, " from zartikel where artikel_nr in " );
   strcat( szBuf, "(select distinct artikel_nr from zapflege " );
   strcat( szBuf, "where datum >= ? " );
   strcat( szBuf, "and datum <= ? )" ); 

   exec sql prepare pre_zartikel from :szBuf;
   VERIFY( verify( fun, "prepare pre_zartikel" ) );
	
   /* prepare for zartsekbez */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_ZARTSEKBEZ );
   strcat( szBuf, " from zartsekbez where artikel_nr = ? " );
   strcat( szBuf, "and pharmos_sekbez = \"1\" " );
   
   exec sql prepare pre_zartsekbez from :szBuf;
   VERIFY( verify( fun, "prepare pre_zartsekbez" ) );
	
    /* prepare for artve */
	strcpy( szBuf, "select " );
	strcat( szBuf, PROJECTION_ARTVE );
	strcat( szBuf, " from artve where artikel_nr = ? " );
		
	exec sql prepare pre_artve from :szBuf;
	VERIFY( verify( fun, "prepare pre_artve" ) );

    /* prepare for ean */
	strcpy( szBuf, "select " );
	strcat( szBuf, PROJECTION_EAN );
	strcat( szBuf, " from ean where artikel_nr = ? " );
		
	exec sql prepare pre_ean from :szBuf;
	VERIFY( verify( fun, "prepare pre_ean" ) );

    /* prepare for zdkwir */
	strcpy( szBuf, "select " );
	strcat( szBuf, PROJECTION_ZDKWIR );
	strcat( szBuf, " from zdkwir where wir_bereich = ? " );
		
	exec sql prepare pre_zdkwir from :szBuf;
	VERIFY( verify( fun, "prepare pre_zdkwir" ) );

    /* prepare for cregisters */
	strcpy( szBuf, "select " );
	strcat( szBuf, PROJECTION_CREGISTERS );
	strcat( szBuf, " from cregisters, carticlecodes where carticlecodes.articleno = ? and carticlecodes.code_type = 23 and carticlecodes.article_code = cregisters.ministryproductcode " );
		
	exec sql prepare pre_cregisters from :szBuf;
	VERIFY( verify( fun, "prepare pre_cregisters" ) );

	/* prepare for zartwg */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_ZARTWG );
   strcat( szBuf, " from zartwg where artikel_nr = ? and art in ('2', '4', 'B') order by art" );
   
   exec sql prepare pre_zartwg from :szBuf;
   VERIFY( verify( fun, "prepare pre_zartwg" ) );

    /* prepare for zartbulgaria (nur in Bulgarien) */
	strcpy( szBuf, "select " );
	strcat( szBuf, PROJECTION_ZARTBULGARIA );
	strcat( szBuf, " from zartbulgaria where articleno = ? " );
		
	exec sql prepare pre_zartbulgaria from :szBuf;
	VERIFY( verify( fun, "prepare pre_zartbulgaria" ) );
   
   /* prepare for carticlelang */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_CARTICLELANG );
   strcat( szBuf, " from carticlelang where articleno = ? " );
   strcat( szBuf, "and langid = \"EN\" " );
   
   exec sql prepare pre_carticlelang from :szBuf;
   VERIFY( verify( fun, "prepare pre_carticlelang" ) );
	
   /* declare for zartikel with open */
   exec sql declare cu_zartikel cursor for pre_zartikel;
   exec sql open cu_zartikel using :lDateOfTheDay, :lDateTo;
   VERIFY( verify( fun, "open cu_zartikel" ) );

   /* declare for zartsekbez */
   exec sql declare cu_zartsekbez cursor for pre_zartsekbez;
   
   /* declare for artve */
   exec sql declare cu_artve cursor for pre_artve;
   
   /* declare for ean */
   exec sql declare cu_ean cursor for pre_ean;
   
   /* declare for zdkwir */
   exec sql declare cu_zdkwir cursor for pre_zdkwir;
   
   /* declare for cregisters */
   exec sql declare cu_cregisters cursor for pre_cregisters;
   
   /* declare for zartwg */
   exec sql declare cu_zartwg cursor for pre_zartwg;

   /* declare for carticlelang */
   exec sql declare cu_carticlelang cursor for pre_carticlelang;
   
  return no_error;
 }

/*** END-BROWSE ********************************************************/

 rterror endBrowse( const bool bCloseAll  )
 {
   char *fun = "endBrowse";

   exec sql close cu_zartikel;
   VERIFY( verify( fun, "close cu_zartikel" ) );
   if ( bCloseAll )
   {
      exec sql close cu_zartpreis;
      VERIFY( verify( fun, "close cu_zartpreis" ) );
      exec sql close cu_zartsekbez;
      VERIFY( verify( fun, "close cu_zartsekbez" ) );
      exec sql close cu_artve;
      VERIFY( verify( fun, "close cu_artve" ) );
      exec sql close cu_ean;
      VERIFY( verify( fun, "close cu_ean" ) );
      exec sql close cu_zdkwir;
      VERIFY( verify( fun, "close cu_zdkwir" ) );
      exec sql close cu_cregisters;
      VERIFY( verify( fun, "close cu_cregisters" ) );
      exec sql close cu_zartwg;
      VERIFY( verify( fun, "close cu_zartwg" ) );
      exec sql close cu_carticlelang;
      VERIFY( verify( fun, "close cu_carticlelang" ) );
   }

   return no_error;
 }

/*** START-BROWSE-ZARTPREIS ******************************************************/

 rterror startBrowseZartpreis ( const long artikel_nr )
 {
   exec sql begin declare section;
   char szBuf[4096];
   long lartikel_nr;
   exec sql end declare section;
   char *fun = "startBrowseZartpreis";

   lartikel_nr = artikel_nr;

   /* prepare for zartpreis */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_ZARTPREIS );
   strcat( szBuf, " from zartpreis " );
   strcat( szBuf, "where artikel_nr = ? " );
   strcat( szBuf, "order by datumgueltigab desc " );

   exec sql prepare pre_zartpreis from :szBuf;
   VERIFY( verify( fun, "prepare pre_zartpreis" ) );
	
   /* declare for pre_zartpreis with open */
   exec sql declare cu_zartpreis cursor for pre_zartpreis;
   exec sql open cu_zartpreis using :lartikel_nr;
   VERIFY( verify( fun, "open cu_zartpreis" ) );

  return no_error;
 }

/*** END-BROWSE-ZARTPREIS ********************************************************/

 rterror endBrowseZartpreis( )
 {
   char *fun = "endBrowse";

   exec sql close cu_zartpreis;
   VERIFY( verify( fun, "close cu_zartpreis" ) );

   return no_error;
 }

/*** GET-NEXT-ARTICLE **********************************************************/
 
 rterror GetNextArticle( dezapzartikelSTR *article )
 {
   exec sql begin declare section;
   dezapzartikelSTR *d;
   exec sql end declare section;
   char *fun = "GetNextArticle";

   d = article;	 
   memset( (char *)d, ' ', sizeof( dezapzartikelSTR ) );
   
   exec sql fetch cu_zartikel into :*d;
   VERIFY( verify( fun, "fetch cu_zartikel" ) );

   return no_error;
 }

/*** GET-PRICE-OF-ARTICLE (only the first) *************************************/
 
 rterror GetPriceOfArticle( dezapzartpreisSTR *price )
 {
   exec sql begin declare section;
   dezapzartpreisSTR *d;
   exec sql end declare section;
   char *fun = "GetPriceOfArticle";

   d = price;	 

   exec sql open cu_zartpreis using :d->ARTIKEL_NR, :d->DATUMGUELTIGAB;
   memset( (char *)d, ' ', sizeof( dezapzartpreisSTR ) ); 
   exec sql fetch cu_zartpreis into :*d;
   VERIFY( verify( fun, "fetch cu_zartpreis" ) ); 

   return no_error;
 }

/*** GET-SECONDARY-OF-ARTICLE (only the first) *********************************/
 
 rterror GetSecondaryOfArticle( dezapzartsekbezSTR *secondary )
 {
   exec sql begin declare section;
   dezapzartsekbezSTR *d;
   exec sql end declare section;
   char *fun = "GetSecondaryOfArticle";

   d = secondary;	 
   exec sql open cu_zartsekbez using :d->ARTIKEL_NR;
   memset( (char *)d, ' ', sizeof( dezapzartsekbezSTR ) );
   exec sql fetch cu_zartsekbez into :*d;
   VERIFY( verify( fun, "fetch cu_zartsekbez" ) );

   return no_error;
 }

/*** GET-VE-OF-ARTICLE *********************************/
 
 rterror GetVeOfArticle( dezapartveSTR *artve )
 {
   exec sql begin declare section;
   dezapartveSTR *d;
   exec sql end declare section;
   char *fun = "GetVeOfArticle";

   d = artve;	 
   exec sql open cu_artve using :d->ARTIKEL_NR;
   memset( (char *)d, ' ', sizeof( dezapartveSTR ) );
   exec sql fetch cu_artve into :*d;
   VERIFY( verify( fun, "fetch cu_artve" ) );

   return no_error;
 }

/*** GET-EAN-OF-ARTICLE *********************************/
 
 rterror GetEanOfArticle( dezapeanSTR *ean )
 {
   exec sql begin declare section;
   dezapeanSTR *d;
   exec sql end declare section;
   char *fun = "GetEanOfArticle";

   d = ean;	 
   exec sql open cu_ean using :d->ARTIKEL_NR;
   memset( (char *)d, ' ', sizeof( dezapeanSTR ) );
   exec sql fetch cu_ean into :*d;
   VERIFY( verify( fun, "fetch cu_ean" ) );

   return no_error;
 }

/*** INIT-GOODS-GROUP-OF-ARTICLE ***********************************************/

 rterror InitGoodsgroupOfArticle( dezapzartwgSTR *goodsgroup )
 {
   exec sql begin declare section;
   dezapzartwgSTR *d;
   exec sql end declare section;
   char *fun = "InitGoodsgroupOfArticle";

   d = goodsgroup;	 
   exec sql open cu_zartwg using :d->ARTIKEL_NR;
   VERIFY( verify( fun, "init cu_zartwg" ) );

   return no_error;
 }

/*** GET-GOODS-GROUP-OF-ARTICLE ************************************************/

 rterror GetGoodsgroupOfArticle( dezapzartwgSTR *goodsgroup )
 {
   exec sql begin declare section;
   dezapzartwgSTR *d;
   exec sql end declare section;
   char *fun = "GetGoodsgroupOfArticle";

   d = goodsgroup;	 
   memset( (char *)d, ' ', sizeof( dezapzartwgSTR ) );
   exec sql fetch cu_zartwg into :*d;
   VERIFY( verify( fun, "fetch cu_zartwg" ) );

   return no_error;
 }															

/*** GET-BULGARIAN-FIELDS ***********************************************/

 rterror GetBulgarianFields(  dezapzartbulgariaSTR *bulgaria )
 {
   exec sql begin declare section;
   dezapzartbulgariaSTR *d;		
   long lArticleNo;
   exec sql end declare section;
   char *fun = "GetBulgarianFields";

   d = bulgaria;	 
   lArticleNo = d->ARTICLENO; 
   memset( (char *)d, ' ', sizeof( dezapzartbulgariaSTR ) );
   exec sql execute pre_zartbulgaria into :*d using :lArticleNo; 
   VERIFY( verify( fun, "fetch cu_zartbulgaria" ) );

   return no_error;
 }

/*** GET-SECOND-NAME-OF-ARTICLE *********************************/
 
 rterror GetSecondNameOfArticle( dezapcarticlelangSTR *secondname )
 {
   exec sql begin declare section;
   dezapcarticlelangSTR *d;
   exec sql end declare section;
   char *fun = "GetSecondNameOfArticle";

   d = secondname;	 
   exec sql open cu_carticlelang using :d->ARTICLENO;
   memset( (char *)d, ' ', sizeof( dezapcarticlelangSTR ) );
   exec sql fetch cu_carticlelang into :*d;
   VERIFY( verify( fun, "fetch cu_carticlelang" ) );

   return no_error;
 }

/*** GET-NEXT-ZARTPREIS **********************************************************/
 
 rterror GetNextZartpreis( dezapzartpreisSTR *zartpreis )
 {
   exec sql begin declare section;
   dezapzartpreisSTR *d;
   exec sql end declare section;
   char *fun = "GetNextZartpreis";

   d = zartpreis;	 
   memset( (char *)d, ' ', sizeof( dezapzartpreisSTR ) );
   
   exec sql fetch cu_zartpreis into :*d;

   VERIFY( verify( fun, "fetch cu_zartpreis" ) );

   return no_error;
 }

 /*** GET-SUBSTANCE-NAME *********************************/
 
 rterror GetSubstanceName( dezapzdkwirSTR *zdkwir )
 {
   exec sql begin declare section;
   dezapzdkwirSTR *d;
   exec sql end declare section;
   char *fun = "GetSubstanceName";

   d = zdkwir;	 
   exec sql open cu_zdkwir using :d->WIR_BEREICH;
   memset( (char *)d, ' ', sizeof( dezapzdkwirSTR ) );
   exec sql fetch cu_zdkwir into :*d;
   VERIFY( verify( fun, "fetch cu_zdkwir" ) );

   return no_error;
 }

 /*** GET-INN *********************************/
 
 rterror GetINN( dezapcregistersSTR *cregisters, dezapartveSTR *artve )
 {
   exec sql begin declare section;
   dezapcregistersSTR *d;
   dezapartveSTR *v;
   exec sql end declare section;
   char *fun = "GetINN";

   d = cregisters;	 
   v = artve;
   exec sql open cu_cregisters using :v->ARTIKEL_NR;
   memset( (char *)d, ' ', sizeof( dezapcregistersSTR ) );
   exec sql fetch cu_cregisters into :*d;
   VERIFY( verify( fun, "fetch cu_cregisters" ) );

   return no_error;
 }
