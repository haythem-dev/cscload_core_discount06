/******************************************************************************/
/*     Hauptmodul: tpldauftr.cpp                                              */
/*         Source: tpldauftr.cpp                                              */
/*          Autor: A. Schmidt-Rehschuh                                        */
/*       Erstellt: 13.05.1996                                                 */
/*        Sprache: C                                                          */
/*        Erzeugt: manuell                                                    */
/*        Aufgabe: loeschen der Kundenauftragrelationen bei Tagesabschluss    */
/*         Aufruf: tpldauftr -ta                                              */
/*                                                                            */
/******************************************************************************/

/*** VERSION ******************************************************************/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "tpldauftr"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

/******************************************************************************************/
/* Versionierung: */
/******************************************************************************************/

/*** INCLUDE ******************************************************************/

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <unistd.h>
 #include <signal.h>
 #include <time.h>
 #include <sys/time.h>
 
 #include <sys/stat.h>
 #include <libtpld/hsystfkt.h>
 #include <dirent.h>                                     
 #include <errno.h>

 #include "pplib/allg.h"
 #include "libtpld/qtime.h"
 #include "dispoartikel.h"
 #include "kdauftrag.h"
 #include "kdauftragdebtrel.h"
 #include "kdauftragzusatz.h"
 #include "kdauftragdiscacc.h"
 #include "kdauftragpos.h"
 #include "kdauftragposrab.h"
 #include "kdauftragposcharge.h"
 #include "kdauftragposchange.h"
 #include "kdauftragbem.h"
 #include "kdauftragereignis.h"
 #include "kdauftragrechart.h"
 #include "kdauftrposrechart.h"
 #include "kdauftragpospromo.h"
 #include "kdauftragposrefund.h"
 #include "akoeinheit.h"
 #include "kdverbund.h"
 #include "kdverbundpos.h"
 #include "kdauftragwerte.h"
 #include "orderrelationno.h"
 #include "kdauftragprolink.h"
 #include "kdverbundposrab.h"
 #include "kdauftragposxml.h"
 #include "kdauftragposereignis.h"
 #include "kdauftragpostour.h"
 #include "kdauftragpartnerfunction.h"
 #include "orderremarks.h"
 #include "orderpositiondiscount.h"
 #include "oecustomercalls.h"
 #include "cscorderflags.h"
 #include "cscorderibtpickingdata.h"
 #include "cscorderpossplittinfo.h"

/*** DEFINE *******************************************************************/

 #include "libtpld/define.h"
 #define MAX_TRANSAKTION     300
 #define WARNING		     -2
 #define MIN_COUNT_OF_DAY     30
 typedef struct timeval timeval_t; 
 #define DATABASE "phosix"

/*** MACROS *******************************************************************/

 #define ERROR_MSG( x )      if ( SQLCODE < 0 ) { PrintMsg( fun, x, FEHLER ); \
				 return ERROR; }
 #define ERROR_MLD( x )      if ( SQLCODE < 0 ) { PrintMsg( fun, x, FEHLER ); }
 #define NOT_FOUND           SQLCODE == SQLNOTFOUND

/*** GLOBALE ******************************************************************/

 int isDE = NO;
 int debug_enabled = NO;
 int i24 = NO;
 int HausNr = 0;
	exec sql begin declare section;
	char str[2048];
	long lDatumEreignis;
	long lDatumAktuell;
	long lZeitEreignis;
	long datedelphone;
	int iFilialNr = 0;
	char folderpath[255] = {0};
	exec sql end declare section;

/*** STRUCTUR *****************************************************************/

 struct ZAEHLER {
    int DelKdauftrag;
    int DelKdauftragDebtrel;
    int DelKdauftragZusatz;
    int DelKdauftragPos;
    int DelKdauftragEreignis;
    int DelKdauftragBem;
    int DelKdauftragRechart;
    int DelKdauftragDiscacc;
    int DelDispoArtikel;    
    int DelKoauftrag;
    int DelKoeinheit;
    int DelFkwarteschlange;
    int UpdNummer;
	int DelKdTourDruck;
    int DelNachlieferPos;
    int DelKdverbund;
	int DelKdverbundPos;
	int DelKdvbPosWithoutHeader;
	int DelCostomerorderno;
	int DelKdauftraginfo;
	int DelKdauftragposrab;
	int DelKdauftragposcharge;
	int DelKdauftragposrechart;
    int DelKdauftragposPromo;
	int DelKdauftragposrefund;
	int DelKdauftragposxml;
	int DelKdauftragposereignis;
	int DelKdauftragpostour;
	int DelKdauftragpartnerfunction;
	int DelStockentry;
	int Reaktiviert;
	int DelAcststockreserve;
    int DelKdauftragWerte;
	int DelKdauftragposchange;
	int DelKdauftragProlink;
	int DelKdverbundPosRab;
	int DelOrderRemarks;
	int DelOrderPositionDiscount;
	int DelNewIBT;
	int DelOrderRelationNo;
	int DelPhoneHistory;
	int DelCscOrderFlags;
	int DelToteInfo;
	int DelCscOrderPosSplittInfo;
	int DelCscOrderIBTPickingData;
	int DelDocumentPrintInfo;
	int DelPositionDiscountProcessed;
 };
 
 typedef struct NUMMER {
    short HerkunftFiliale; 
    short FilialNr; 
    int   KdNr;
    int   Datum;
    } Nummer;

/*** DECLARATION **************************************************************/

 int main( int, char ** );
 static int  HoleHausNr( char*,const int *,int * );
 static int  DeleteOld( const int iNumberOfDay );
 static int  DeleteOldCSV( const int iNumberOfDay );
 static int  GetCSVImportFolder();
 static char*  trimwhitespace(char *str);
 static int  DeleteKdTourDruck( struct ZAEHLER * );
 static int  DeleteFkwarteschlange( struct ZAEHLER * );
 static int  StartKdauftrag( void );
 static int  DeleteKdauftrag( Nummer *, struct ZAEHLER * );
 static int  DeleteKdauftragDebtrel( Nummer *, struct ZAEHLER * );
 static int  DeleteKdauftragRechart( Nummer *, struct ZAEHLER * );
 static int  DeleteKdauftragDiscacc( Nummer *, struct ZAEHLER * );
 static int  DeleteKdauftragZusatz( Nummer *, struct ZAEHLER * );
 static int  DeleteKdauftragProlink( Nummer *, struct ZAEHLER * );
 static int  DeleteKdauftragPos( Nummer *, struct ZAEHLER * );
 static int  DeleteKdauftragPosRab( Nummer *, struct ZAEHLER * );
 static int  DeleteKdauftragPosCharge( Nummer *, struct ZAEHLER * );
 static int  DeleteKdauftragPosChange( Nummer *, struct ZAEHLER * );
 static int  DeleteKdauftragPosRechart( Nummer *, struct ZAEHLER * );
 static int  DeleteKdauftragPosPromo( Nummer *, struct ZAEHLER * );
 static int  DeleteKdauftragPosRefund( Nummer *, struct ZAEHLER * );
 static int  DeleteKdauftragPosXml( Nummer *, struct ZAEHLER * );
 static int  DeleteKdauftragPosEreignis( Nummer *, struct ZAEHLER * );
 static int  DeleteKdauftragPosTour( Nummer *, struct ZAEHLER * );
 static int  DeleteKdauftragPartnerFunction( Nummer *, struct ZAEHLER * );
 static int  DeleteKdauftragEreignis( int, struct ZAEHLER * );
 static int  DeleteKdauftragBem( Nummer *, struct ZAEHLER * );
 static int  DeleteKdauftragWerte( Nummer *, struct ZAEHLER * );
 static int  DeleteOrderRelationNo( Nummer *, struct ZAEHLER * );
 static int  DeleteDispoArtikel( Nummer *, struct ZAEHLER * );
 static int  DeleteNachlieferpos( const long lDate, struct ZAEHLER *  );
 static int  DeleteKoauftrag( struct ZAEHLER * );
 static int  DeleteKoeinheitAll( struct ZAEHLER * );
 static int  DeleteKoeinheit( Nummer *, struct ZAEHLER * );
 static int  DeleteOrderRemarks( Nummer *, struct ZAEHLER * );
 static int  DeleteCscOrderFlags( Nummer *, struct ZAEHLER * );
 static int  DeleteCscOrderPosSplittInfo(Nummer *, struct ZAEHLER *);
 static int  DeleteCscOrderIBTPickingData(Nummer *, struct ZAEHLER *);
 static int  DeleteOrderPositionDiscount( Nummer *, struct ZAEHLER * );
 static int  UpdateNummer( struct ZAEHLER * );
 static int  PruefeAuftrag( const short );
 static int  PruefeFaktur( const short );
 static int  PruefeVBAuftrag( const short );
 static int  PrepareAll( const short );
 static int  Commit( char * );
 static void PrintMsg( char *, char *, char );
 static int  DeleteAkdauftrag( long, struct ZAEHLER * );
 static int  DeleteAkdauftragDebtrel( long, long, struct ZAEHLER * );
 static int  DeleteAkdauftragRechart( long, long, struct ZAEHLER * );
 static int  DeleteAkdauftragDiscacc( long, long, struct ZAEHLER * );
 static int  DeleteAkdauftragZusatz( long, struct ZAEHLER * );
 static int  DeleteAkdauftragProlink( long, long, struct ZAEHLER * );
 static int  DeleteAkdauftragPos( long, long, struct ZAEHLER * );
 static int  DeleteAkdauftragPosRab( long, long, struct ZAEHLER * );
 static int  DeleteAkdauftragPosCharge( long, long, struct ZAEHLER * );
 static int  DeleteAkdauftragPosChange( long, long, struct ZAEHLER * );
 static int  DeleteAkdauftragPosRechart( long, long, struct ZAEHLER * );
 static int  DeleteAkdauftragPosPromo( long, long, struct ZAEHLER * );
 static int  DeleteAkdauftragPosRefund( long, long, struct ZAEHLER * );
 static int  DeleteAkdauftragPosXml( long, long, struct ZAEHLER * );
 static int  DeleteAkdauftragPosEreignis( long, long, struct ZAEHLER * );
 static int  DeleteAkdauftragPosTour( long, long, struct ZAEHLER * );
 static int  DeleteAkdauftragPartnerFunction( long, long, struct ZAEHLER * );
 static int  DeleteAkdauftragBem( long, long, struct ZAEHLER * );
 static int  DeleteAkdauftragEreignis( long, long, struct ZAEHLER * );
 static int  DeleteAkdauftragWerte( long, long, struct ZAEHLER * );
 static int  DeleteAOrderRelationNo( long, long, struct ZAEHLER * );
 static int  DeleteAdispoArtikel( long, long, struct ZAEHLER * );
 static int  DeleteAorderRemarks( long, long, struct ZAEHLER *z );
 static int  DeleteAcscOrderFlags( long, long, struct ZAEHLER *z );
 static int  DeleteAcscOrderPosSplittInfo(long, long, struct ZAEHLER *z);
 static int  DeleteAcscOrderIBTOickingData(long, long, struct ZAEHLER *z);
 static int  DeleteAorderPositionDiscount( long, long, struct ZAEHLER *z );
 static int  DeleteAnewIBT( long, long, struct ZAEHLER *z );
 static int  DeleteAkoeinheit( long date, struct ZAEHLER *z );
 static int  DeleteAkdverbund( long date, struct ZAEHLER *z );
 static int  DeleteAkdverbundPos( long, short, long date, struct ZAEHLER *z );
 static int  DeleteAkdverbundPosRab( long, short, long date, struct ZAEHLER *z );
 static int  DeleteStockentry( long date, struct ZAEHLER * );
 static int  DeleteAcststockreserve( long date, struct ZAEHLER * );
 static int  StartKdverbund();
 static int  StartKdverbund3();
 static int  DeleteKdverbund( Nummer *num, struct ZAEHLER *z );
 static int  DeleteKdverbund3( Nummer *num, struct ZAEHLER *z );
 static int  DeleteKdverbundPos( Nummer *num, struct ZAEHLER *z );
 static int  DeleteKdverbundPosRab( Nummer *num, struct ZAEHLER *z );
 static int  DeleteKdvbPosWithoutHeader( struct ZAEHLER *z );
 static int  DeleteKdauftraginfo( Nummer *, struct ZAEHLER * );
 static int  DeleteDailyFiles( struct ZAEHLER * );
 static int  DeletePhoneHistory( struct ZAEHLER * );
 static int  DeleteToteInfo( long date, struct ZAEHLER * );
 static int  DeleteDocumentPrintInfo(long date, struct ZAEHLER *);
 static int  CheckIBTPickingDone(int kdauftragnr);
 static int  DeleteOrderPositionDiscountProcessed(Nummer *num, struct ZAEHLER *z);
 /*** Korrektur kzrestored bei verzögerter Auslieferung ************************/

 static int  UpdateKzrestored( const short );

 /*** Verzögerte Auslieferung **************************************************/

 static int  PrepareReaktiviereAuftrag( );
 static int  PrepareIncreaseNummer( );
 static int  PrepareReaktiviereKdauftrag( );
 static int  PrepareReaktiviereKdauftragPos( );
 static int  PrepareReaktiviereKdauftragPosRab( );
 static int  PrepareReaktiviereKdauftragPosCharge( );
 static int  PrepareReaktiviereKdauftragBem( );
 static int  PrepareReaktiviereKdauftragEreignis( );
 static int  PrepareReaktiviereKdispoArtikel( ); 
 static int  ReaktiviereAuftrag( struct ZAEHLER *z );
 static int  IncreaseNummer( long *KdauftragNr );
 static int  ReaktiviereKdauftrag( kdauftragS *d );
 static int  ReaktiviereKdauftragPos( long lDatum, long KdauftragNr, long KdauftragNrNeu );
 static int  ReaktiviereKdauftragPosRab( long lDatum, long KdauftragNr, long KdauftragNrNeu );
 static int  ReaktiviereKdauftragPosCharge( long lDatum, long KdauftragNr, long KdauftragNrNeu );
 static int  ReaktiviereKdauftragBem( long lDatum, long KdauftragNr, long KdauftragNrNeu );
 static int  ReaktiviereKdauftragEreignis( kdauftragS *d );
 static int  ReaktiviereKdispoArtikel( long lDatum, long KdauftragNr, long KdauftragNrNeu ); 

/*** MAIN *********************************************************************/

int main( int argc, char **argv )
{
  struct ZAEHLER z = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };	        /* initialize */
  Nummer num;
  char error_msg[512];
  int skip;
  int i;
  int rc;
  int iNumberOfDay = MIN_COUNT_OF_DAY; /* minimum an tagen die behalten werden */
  char *schalter;
  char *spDatabase = NULL;
  char *fun = "Main";
  
  skip = NO;
  for ( i = 1; i < argc; i++ )
  {
      if ( skip )
         {
         skip = NO;
         continue;
         }
      schalter = argv[i];
      if ( !strcmp( schalter, "-dg" ) )
         debug_enabled = YES;
      else if ( !strcmp( schalter, "-del" ) )
      {   
		 if ( atoi( argv[i + 1] ) == -1 )
		  	iNumberOfDay = 1;
		 else if ( ( iNumberOfDay = atoi( argv[i + 1] ) ) < MIN_COUNT_OF_DAY )
		    iNumberOfDay = MIN_COUNT_OF_DAY; /* RZ:Arden und Brix sicher!!! */
		 skip = YES;
	  }
      else if ( !strcmp( schalter, "-db" ) )
      {   
		spDatabase = argv[i+1];
	    skip = YES;
	  }
      else if ( !strcmp( schalter, "-fil" ) )
      {   
		iFilialNr = atoi(argv[i+1]);
	    skip = YES;
	  }
      else if ( !strcmp( schalter, "-h24" ) )
      {   
         i24 = YES;
	  }
		else if ( !strcmp( schalter, "-version" ) )
		{
			printVersion(versioninfo);
			return 0;
		}
      else
      {
         skip = ERROR;
         break;
      }
   }                                            
   
   if ( argc == 1 || skip == ERROR )
      {
      printf( "  usage: %s\n\t"
              " { -dg /*Debugging*/ }\n\t"
              " [ -del <NumberOfDays> ]\n\t",
              argv[0] );
      return 2;
      }

  if ( HoleHausNr( spDatabase, &iFilialNr, &HausNr ) < 0 )
     return 1;
  if(	iFilialNr == 5
	 ||	iFilialNr == 6
	 ||	iFilialNr == 8
	 ||	iFilialNr == 9
	 ||	iFilialNr == 21
	 ||	iFilialNr == 31
	 ||	iFilialNr == 33
	 ||	iFilialNr == 40
	 ||	iFilialNr == 44
	 ||	iFilialNr == 46
	 ||	iFilialNr == 51
	 ||	iFilialNr == 52
	 ||	iFilialNr == 54
	 ||	iFilialNr == 56
	 ||	iFilialNr == 57
	 ||	iFilialNr == 58
	 ||	iFilialNr == 59
	 ||	iFilialNr == 70
	 ||	iFilialNr == 78
	 ||	iFilialNr == 81
	 ||	iFilialNr == 82 )
	 isDE = YES;

	sprintf( error_msg, "gestartet mit Tagen:%d fuer DB: %s", iNumberOfDay, spDatabase );
  PrintMsg( fun, error_msg, HINWEIS );
  
	if(i24 == NO)
	{
		if ( PruefeFaktur(iFilialNr) != OK )
		{
			fprintf( stderr, "ES WURDEN NICHT ALLE AUFTRAEGE FAKTURIERT!\n" );
			PrintMsg( fun, "es wurden nicht alle Auftraege fakturiert!", FEHLER );
			/* return;  Nach Aussage von Herrn Sendlbeck muss geloescht trotzdem  */
			/* geloescht werden ! */
		}
	}

	UpdateKzrestored(iFilialNr);
  
	if(i24 == NO)
	{
		if ( !PruefeAuftrag(iFilialNr) )
		{
			fprintf( stderr, "ES WURDEN NICHT ALLE AUFTRAEGE ABGESCHLOSSEN!\n" );
			PrintMsg( fun, "es wurden nicht alle Auftraege abgeschlossen!", FEHLER );
		}
	}

	if(i24 == NO)
	{
		if ( !PruefeVBAuftrag(iFilialNr) )
		{
			fprintf( stderr, "ES WURDEN NICHT ALLE VBAUFTRAEGE ABGESCHLOSSEN/VERARBEITET!\n" );
			PrintMsg( fun, "es wurden nicht alle VBAuftraege abgeschlossen/verarbeitet!", FEHLER );
		}
	}
  
	if ( PrepareAll(iFilialNr) != OK )
		return 1;
  
	DeleteOld( iNumberOfDay );      /* a... Tabellen loeschen ab Datum */
	DeleteOldCSV( iNumberOfDay );      /* delete the .csv and.log files from server//data// */
	DeleteKdTourDruck( &z );		  /* only delete this table, not interested in more */
	DeleteKoauftrag( &z );
	DeleteFkwarteschlange( &z );

	for( !StartKdauftrag(); ; )
	{
		if((rc = DeleteKdauftrag(&num, &z)) == WARNING) continue;
		else if (rc == SQLNOTFOUND) break;
		else if (rc == ERROR) break;
		DeleteKdauftragDebtrel( &num, &z );
		DeleteKdauftragRechart( &num, &z );
		DeleteKdauftragDiscacc( &num, &z );
/*		DeleteKdauftragZusatz( &num, &z );
*/
		DeleteKdauftragProlink( &num, &z );
		DeleteKdauftragPos( &num, &z );
		DeleteKdauftragPosRab( &num, &z );
		DeleteKdauftragPosCharge( &num, &z );
		DeleteKdauftragPosChange( &num, &z );
		DeleteKdauftragPosRechart( &num, &z );
		DeleteKdauftragPosPromo( &num, &z );
		DeleteKdauftragPosRefund( &num, &z );
		DeleteKdauftragPosXml( &num, &z );
		DeleteKdauftragPosEreignis( &num, &z );
		DeleteKdauftragPosTour( &num, &z );
		DeleteKdauftragPartnerFunction( &num, &z );
		DeleteKdauftragBem( &num, &z );
		DeleteKdauftragWerte( &num, &z );
		DeleteOrderRelationNo( &num, &z );
		DeleteDispoArtikel( &num, &z );
		DeleteKoeinheit( &num, &z );
		DeleteKdauftraginfo( &num, &z );
		DeleteOrderRemarks( &num, &z );
		DeleteOrderPositionDiscount( &num, &z );
		DeleteCscOrderFlags( &num, &z );
		DeleteCscOrderPosSplittInfo(&num, &z);
		DeleteCscOrderIBTPickingData(&num, &z);
		DeleteOrderPositionDiscountProcessed(&num, &z);
	}
	if(rc == ERROR) return ERROR;


	/* besondere Behandlung für vb-position (auch vbstatus == 0 */
	for( StartKdverbund(); ( rc = DeleteKdverbund( &num, &z ) ) == OK; )
	{
		DeleteKdverbundPos( &num, &z );
		DeleteKdverbundPosRab( &num, &z );
	}

	/* besondere Behandlung kdverbund vbstatus 3 */
	for( StartKdverbund3(); ( rc = DeleteKdverbund3( &num, &z ) ) == OK; )
	{
		DeleteKdverbundPos( &num, &z );
		DeleteKdverbundPosRab( &num, &z );
	}


	if(rc == ERROR) return ERROR;
  
	/*	DeleteKdvbPosWithoutHeader( &z );	*/

	DeleteKoeinheitAll(&z);  /* to be sure all items are deleted */

	if ( rc != SQLNOTFOUND )
	{
		PrintMsg( fun, "Mit Fehler abgebrochen!", FEHLER );
		return 1;
	}

	DeleteDailyFiles( &z );
	DeletePhoneHistory( &z );
	
/*	if(i24 == NO)
	{
		UpdateNummer( &z );
	}
*/

	sprintf( error_msg, "Kdtourdruck geloescht: %d", z.DelKdTourDruck );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "Fkwarteschl geloescht: %d", z.DelFkwarteschlange );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "AuftragPos  geloescht: %d", z.DelKdauftragPos );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "AuftragPosRab  geloescht: %d", z.DelKdauftragposrab );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "AuftragPosCharge  geloescht: %d", z.DelKdauftragposcharge );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "AuftragPosChange  geloescht: %d", z.DelKdauftragposchange );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "AuftragPosRechart  geloescht: %d", z.DelKdauftragposrechart );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "AuftragPosPromo  geloescht: %d", z.DelKdauftragposPromo );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "AuftragPosRefund  geloescht: %d", z.DelKdauftragposrefund );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "AuftragPosXml  geloescht: %d", z.DelKdauftragposxml );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "AuftragPosEreignis  geloescht: %d", z.DelKdauftragposereignis );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "AuftragPosTour  geloescht: %d", z.DelKdauftragpostour );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "AuftragPartnerFunction  geloescht: %d", z.DelKdauftragpartnerfunction );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "Auftrag     geloescht: %d", z.DelKdauftrag );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "AuftragDebtrel     geloescht: %d", z.DelKdauftragDebtrel );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "AuftragZus  geloescht: %d", z.DelKdauftragZusatz );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "AuftragProlink  geloescht: %d", z.DelKdauftragProlink );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "AuftragErgs geloescht: %d", z.DelKdauftragEreignis );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "AuftragBem  geloescht: %d", z.DelKdauftragBem );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "AuftragWerte  geloescht: %d", z.DelKdauftragWerte );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "AuftragRechart  geloescht: %d", z.DelKdauftragRechart );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "AuftragDiscacc  geloescht: %d", z.DelKdauftragDiscacc );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "AuftragDisp geloescht: %d", z.DelDispoArtikel );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "KoAuftrag   geloescht: %d", z.DelKoauftrag );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "Koeinheit   geloescht: %d", z.DelKoeinheit );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "Verbund     geloescht: %d", z.DelKdverbund );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "Verbundpos  geloescht: %d", z.DelKdverbundPos );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "Verbundposrab  geloescht: %d", z.DelKdverbundPosRab );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "Verbundpos ohne Header geloescht: %d", z.DelKdvbPosWithoutHeader );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "Costomerorderno geloescht: %d", z.DelCostomerorderno );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "Kdauftraginfo geloescht: %d", z.DelKdauftraginfo );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "Orderremarks geloescht: %d", z.DelOrderRemarks );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "OrderPositionDiscount geloescht: %d", z.DelOrderPositionDiscount );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "OrderRelationNo geloescht: %d", z.DelOrderRelationNo );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "CscOrderFlags geloescht: %d", z.DelCscOrderFlags );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf(error_msg, "CscOrderPosSplittInfo geloescht: %d", z.DelCscOrderPosSplittInfo);
	PrintMsg(fun, error_msg, HINWEIS);
	sprintf(error_msg, "CscOrderIBTPickingData geloescht: %d", z.DelCscOrderIBTPickingData);
	PrintMsg(fun, error_msg, HINWEIS);

	sprintf( error_msg, "Nummer      geaendert: %d", z.UpdNummer );
	PrintMsg( fun, error_msg, HINWEIS );
	sprintf( error_msg, "Aufträge reaktiviert: %d", z.Reaktiviert );
	PrintMsg( fun, error_msg, HINWEIS );
	PrintMsg( fun, "beendet", HINWEIS );
	return OK;
}

/***** PRUEFE-FAKTUR ********************************************************/

static int PruefeFaktur( const short iFilialNr )
{
	exec sql begin declare section;
	int Count;
	const short iDBFilialNr = iFilialNr;
	exec sql end declare section;
	
	char *fun = "PruefeFaktur";

	exec sql select count(*) into :Count from fkwarteschlange where
	kdauftragnr in ( select kdauftragnr from kdauftrag where vertriebszentrumnr = :iDBFilialNr);
	ERROR_MSG( "count fkwarteschlange" )

	return Count;
}

/***** PRUEFE-AUFTRAG *******************************************************/

static int PruefeAuftrag( const short iFilialNr )
{
	exec sql begin declare section;
	long lKdAuftragnr;
	const short iDBFilialNr = iFilialNr;
	exec sql end declare section;
	int iReturn = 1;

	char *fun = "PruefeAuftrag";

	exec sql declare CPruefeAuftrag Cursor for 
		select kdauftragnr from kdauftrag
		where kdauftragstat[1,4] != "0000"
		and vertriebszentrumnr = :iDBFilialNr
		and datumauslieferung <= :lDatumAktuell;
	exec sql open CPruefeAuftrag;				
	ERROR_MSG( "open CPruefeAuftrag" )
	while( sqlca.sqlcode == 0 )
	{
		exec sql fetch CPruefeAuftrag into :lKdAuftragnr;
		if ( sqlca.sqlcode == 0 )
		{
			char error_msg[81];
			iReturn = 0;
			sprintf( error_msg, "AuftragNr:%ld wurde nicht abgeschlossen!",lKdAuftragnr );
			PrintMsg( fun, error_msg, FEHLER );	 
		}
	}

	exec sql close  CPruefeAuftrag;
	return iReturn;
}

/***** PRUEFE-VBAUFTRAG *****************************************************/

static int PruefeVBAuftrag( const short iFilialNr )
{
	exec sql begin declare section;
	short sFilialNr;
	short sVbStatus;
	long  lKdAuftragnr;
	const short iDBFilialNr = iFilialNr;
	exec sql end declare section;
	int iReturn = 1;

	char *fun = "PruefeVBAuftrag";

	exec sql declare CPruefeVBAuftrag Cursor for 
		select herkunftfiliale, kdauftragnr, vbstatus from kdverbund
		where vbstatus in ( 0, 3 ) and
			filialnr = :iDBFilialNr;
	exec sql open CPruefeVBAuftrag;				
	ERROR_MSG( "open CPruefeVBAuftrag" )
	while( sqlca.sqlcode == 0 )
	{
		exec sql fetch CPruefeVBAuftrag into :sFilialNr, :lKdAuftragnr, :sVbStatus;
		if ( sqlca.sqlcode == 0 )
		{
			char error_msg[81];
			iReturn = 0;
			sprintf( error_msg, "VBAuftragNr:%ld(Fil:%d/%d) wurde nicht abgeschlossen!",
				lKdAuftragnr, sFilialNr, sVbStatus );
			PrintMsg( fun, error_msg, FEHLER );	 
		}
	}

	exec sql close  CPruefeVBAuftrag;
	return iReturn;
}

   
/***** PREPARE-ALL **********************************************************/

static int PrepareAll( const short iFilialNr )
{
	char szFiliale[10];  
	char *fun = "PrepareAll";

	sprintf( szFiliale, "%d", iFilialNr );

	strcpy( str, "select " );
	strcat( str, KDAUFTRAG_PLISTE );
	strcat( str, " from kdauftrag where vertriebszentrumnr= " );
	strcat( str, szFiliale );
	if(i24 == YES)
	{
		strcat( str, " and (kdauftragstat[9] == '1' " );
		strcat( str, " or kdauftragstat[10] == '1') " );
	}
	strcat( str, " for update " );

	exec sql prepare Skdauftrag from :str;
	ERROR_MSG( "prepare Skdauftrag" );
	exec sql declare Ckdauftrag cursor with hold for Skdauftrag;
	exec sql free Skdauftrag;

	strcpy( str, "select " );
	strcat( str, KDVERBUND_PLISTE );
	strcat( str, " from kdverbund where filialnr=");
	strcat( str, szFiliale );
	if(i24 == YES)
	{
//		strcat( str, " and vbstatus in ( 0, 4, 5, 9 ) " );	/* auch vbstatus = 0, da bei verzögerten Aufträgen am nächsten Tag ein neuer kdverbund geschrieben wird */
		strcat( str, " and vbstatus in ( 4, 5, 9 ) " );	/* auch vbstatus = 0, da bei verzögerten Aufträgen am nächsten Tag ein neuer kdverbund geschrieben wird */
	}
	strcat( str, " for update " );

	exec sql prepare Skdverbund from :str;
	ERROR_MSG( "prepare Skdverbund" );
	exec sql declare Ckdverbund cursor with hold for Skdverbund;
	exec sql free Skdverbund;

	strcpy( str, "select " );
	strcat( str, KDVERBUND_PLISTE );
	strcat( str, " from kdverbund where filialnr=");
	strcat( str, szFiliale );
	strcat( str, " and vbstatus = 3 " );
	strcat( str, " for update " );

	exec sql prepare Skdverbund3 from :str;
	ERROR_MSG( "prepare Skdverbund3" );
	exec sql declare Ckdverbund3 cursor with hold for Skdverbund3;
	exec sql free Skdverbund3;

	strcpy( str, "select 1" );
	strcat( str, " from kdverbundpos");
	strcat( str, " where filialnr = ?");
	strcat( str, " and herkunftfiliale = ?" );
	strcat( str, " and kdauftragnr = ?" );
	strcat( str, " and ibttype = ?" );
	strcat( str, " and processingstatus != 2" );
   
	exec sql prepare Svbposdone from :str;
	ERROR_MSG( "prepare Svbposdone" );
	exec sql declare Cvbposdone cursor with hold for Svbposdone;
	exec sql free Svbposdone;
	
	strcpy( str, "select datum, kdauftragnr " );
	strcat( str, "from akdauftrag " );
	strcat( str, "where datum < ? " );
	strcat( str, "and vertriebszentrumnr= " );
	strcat( str, szFiliale );
	strcat( str, " for update " );

	exec sql prepare SAkdauftrag from :str;
	ERROR_MSG( "prepare SAkdauftrag" );
	exec sql declare CAkdauftrag cursor with hold for SAkdauftrag;
	exec sql free SAkdauftrag;
	
	strcpy( str, "select date " );
	strcat( str, "from stockentry " );
	strcat( str, "where date < ? " );
	strcat( str, "and branchno= " );
	strcat( str, szFiliale );
	strcat( str, " for update " );

	exec sql prepare SStockentry from :str;
	ERROR_MSG( "prepare SStockentry" );
	exec sql declare CStockentry cursor with hold for SStockentry;
	exec sql free SStockentry;
	
	strcpy( str, "select date " );
	strcat( str, "from acststockreserved " );
	strcat( str, "where date < ? " );
	strcat( str, "and branchno= " );
	strcat( str, szFiliale );
	strcat( str, " for update " );

	exec sql prepare SAcststock from :str;
	ERROR_MSG( "prepare SAcststock" );
	exec sql declare CAcststock cursor with hold for SAcststock;
	exec sql free SAcststock;
	
if (isDE == YES)
{
	strcpy( str, "select pickingstartdatetime " );
	strcat( str, "from toteinfo " );
	strcat( str, "where pickingstartdatetime < ? " );
	strcat( str, "and branchnoibt= " );
	strcat( str, szFiliale );
	strcat( str, " for update " );

	exec sql prepare SToteinfo from :str;
	ERROR_MSG( "prepare SToteinfo" );
	exec sql declare CToteinfo cursor with hold for SToteinfo;
	exec sql free SToteinfo;
}
	
	strcpy(str, "select documentdate ");
	strcat(str, "from documentprintinfo ");
	strcat(str, "where documentdate < ? ");
	strcat(str, "and branchno= ");
	strcat(str, szFiliale);
	strcat(str, " for update ");

	exec sql prepare SDocumentprintinfo from :str;
	ERROR_MSG("prepare SDocumentprintinfo");
	exec sql declare CDocumentprintinfo cursor with hold for SDocumentprintinfo;
	exec sql free SDocumentprintinfo;

/* kdauftragzusatz ist für KSC nicht relevant */
/*	strcpy( str, "select " );
	strcat( str, KDAUFTRAGZUSATZ_PLISTE );
	strcat( str, " from kdauftragzusatz " );
	strcat( str, "where kdauftragnr = ? " );
	strcat( str, "for update " );

	exec sql prepare Skdauftragzus from :str;
	ERROR_MSG( "prepare Skdauftragzus" );
	exec sql declare Ckdauftragzus cursor with hold for Skdauftragzus;
	exec sql free Skdauftragzus;
	
	strcpy( str, "select * " );
	strcat( str, "from akdauftragzusatz " );
	strcat( str, "where datum < ? " );
	strcat( str, "and kdauftragnr > 0 for update " );

	exec sql prepare SAkdauftragzus from :str;
	ERROR_MSG( "prepare SAkdauftragzus" );
	exec sql declare CAkdauftragzus cursor with hold for SAkdauftragzus;
	exec sql free SAkdauftrag;
*/	
	strcpy( str, "select " );
	strcat( str, KDAUFTRAGEREIGNIS_PLISTE );
	strcat( str, " from kdauftragereignis where " );
	strcat( str, "kdauftragnr = ? "  );
	strcat( str, "for update " );

	exec sql prepare Skdauftragerg from :str;
	ERROR_MSG( "prepare Skdauftragerg" );
	exec sql declare Ckdauftragerg cursor with hold for Skdauftragerg;
	exec sql free Skdauftragerg;

	strcpy( str, "select " );
	strcat( str, KDAUFTRAGPOS_PLISTE  );
	strcat( str, " from kdauftragpos where " );
	strcat( str, "kdauftragnr = ? " );
	strcat( str, "and posnr > 0 " );
	strcat( str, "for update " );

	exec sql prepare Skdauftragpos from :str;
	ERROR_MSG( "prepare Skdauftragpos" );
	exec sql declare Ckdauftragpos cursor with hold for Skdauftragpos;
	exec sql free Skdauftragpos;
	
	strcpy( str, "select " );
	strcat( str, KDAUFTRAGPOSRAB_PLISTE  );
	strcat( str, " from kdauftragposrab where " );
	strcat( str, "kdauftragnr = ? " );
	strcat( str, "and posnr > 0 " );
	strcat( str, "for update " );

	exec sql prepare Skdauftragposrab from :str;
	ERROR_MSG( "prepare Skdauftragposrab" );
	exec sql declare Ckdauftragposrab cursor with hold for Skdauftragposrab;
	exec sql free Skdauftragposrab;
	
	strcpy( str, "select " );
	strcat( str, KDAUFTRAGPOSCHARGE_PLISTE  );
	strcat( str, " from kdauftragposcharge where " );
	strcat( str, "kdauftragnr = ? " );
	strcat( str, "and posnr > 0 " );
	strcat( str, "for update " );

	exec sql prepare Skdauftragposcharge from :str;
	ERROR_MSG( "prepare Skdauftragposcharge" );
	exec sql declare Ckdauftragposcharge cursor with hold for Skdauftragposcharge;
	exec sql free Skdauftragposcharge;
	
	strcpy( str, "select " );
	strcat( str, KDAUFTRAGPOSCHANGE_PLISTE  );
	strcat( str, " from kdauftragposchange where " );
	strcat( str, "kdauftragnr = ? " );
	strcat( str, "and posnr > 0 " );
	strcat( str, "for update " );

	exec sql prepare Skdauftragposchange from :str;
	ERROR_MSG( "prepare Skdauftragposchange" );
	exec sql declare Ckdauftragposchange cursor with hold for Skdauftragposchange;
	exec sql free Skdauftragposchange;
	
	strcpy( str, "select " );
	strcat( str, KDAUFTRPOSRECHART_PLISTE  );
	strcat( str, " from kdauftrposrechart where " );
	strcat( str, "kdauftragnr = ? " );
	strcat( str, "and posnr > 0 " );
	strcat( str, "for update " );

	exec sql prepare Skdauftragposrechart from :str;
	ERROR_MSG( "prepare Skdauftragposrechart" );
	exec sql declare Ckdauftragposrechart cursor with hold for Skdauftragposrechart;
	exec sql free Skdauftragposrechart;
	
	strcpy( str, "select " );
	strcat( str, KDAUFTRAGPOSPROMO_PLISTE  );
	strcat( str, " from kdauftragpospromo where " );
	strcat( str, "kdauftragnr = ? " );
	strcat( str, "and posnr > 0 " );
	strcat( str, "for update " );

	exec sql prepare Skdauftragpospromo from :str;
	ERROR_MSG( "prepare Skdauftragpospromo" );
	exec sql declare Ckdauftragpospromo cursor with hold for Skdauftragpospromo;
	exec sql free Skdauftragpospromo;
	
	strcpy( str, "select " );
	strcat( str, KDAUFTRAGPOSREFUND_PLISTE  );
	strcat( str, " from kdauftragposrefund where " );
	strcat( str, "kdauftragnr = ? " );
	strcat( str, "for update " );

	exec sql prepare Skdauftragposrefund from :str;
	ERROR_MSG( "prepare Skdauftragposrefund" );
	exec sql declare Ckdauftragposrefund cursor with hold for Skdauftragposrefund;
	exec sql free Skdauftragposrefund;
	
	strcpy( str, "select " );
	strcat( str, KDAUFTRAGPOSXML_PLISTE  );
	strcat( str, " from kdauftragposxml where " );
	strcat( str, "kdauftragnr = ? " );
	strcat( str, "for update " );

	exec sql prepare Skdauftragposxml from :str;
	ERROR_MSG( "prepare Skdauftragposxml" );
	exec sql declare Ckdauftragposxml cursor with hold for Skdauftragposxml;
	exec sql free Skdauftragposxml;
	
	strcpy( str, "select " );
	strcat( str, KDAUFTRAGPOSEREIGNIS_PLISTE  );
	strcat( str, " from kdauftragposereignis where " );
	strcat( str, "kdauftragnr = ? " );
	strcat( str, "for update " );

	exec sql prepare Skdauftragposereignis from :str;
	ERROR_MSG( "prepare Skdauftragposereignis" );
	exec sql declare Ckdauftragposereignis cursor with hold for Skdauftragposereignis;
	exec sql free Skdauftragposereignis;
	
	strcpy( str, "select " );
	strcat( str, KDAUFTRAGPOSTOUR_PLISTE  );
	strcat( str, " from kdauftragpostour where " );
	strcat( str, "kdauftragnr = ? " );
	strcat( str, "for update " );

	exec sql prepare Skdauftragpostour from :str;
	ERROR_MSG( "prepare Skdauftragpostour" );
	exec sql declare Ckdauftragpostour cursor with hold for Skdauftragpostour;
	exec sql free Skdauftragpostour;

	strcpy( str, "select " );
	strcat( str, KDAUFTRAGPARTNERFUNCTION_PLISTE );
	strcat( str, " from kdauftragpartnerfunction where " );
	strcat( str, "kdauftragnr = ? " );
	strcat( str, "for update " );

	exec sql prepare Skdauftragpartnerfunction from :str;
	ERROR_MSG( "prepare Skdauftragpartnerfunction" );
	exec sql declare Ckdauftragpartnerfunction cursor with hold for Skdauftragpartnerfunction;
	exec sql free Skdauftragpartnerfunction;
	
	strcpy( str, "select " );
	strcat( str, KDAUFTRAGWERTE_PLISTE  );
	strcat( str, " from kdauftragwerte where " );
	strcat( str, "kdauftragnr = ? " );
	strcat( str, "for update " );

	exec sql prepare Skdauftragwerte from :str;
	ERROR_MSG( "prepare Skdauftragwerte" );
	exec sql declare Ckdauftragwerte cursor with hold for Skdauftragwerte;
	exec sql free Skdauftragwerte;
	
	strcpy( str, "select " );
	strcat( str, ORDERRELATIONNO_PLISTE  );
	strcat( str, " from orderrelationno where " );
	strcat( str, "cscorderno = ? " );
	strcat( str, "for update " );

	exec sql prepare Sorderrelationno from :str;
	ERROR_MSG( "prepare Sorderrelationno" );
	exec sql declare Corderrelationno cursor with hold for Sorderrelationno;
	exec sql free Sorderrelationno;

	strcpy( str, "select " );
	strcat( str, KDAUFTRAGPROLINK_PLISTE  );
	strcat( str, " from kdauftragprolink where " );
	strcat( str, "kdauftragnr = ? " );
	strcat( str, "for update " );

	exec sql prepare Skdauftragprolink from :str;
	ERROR_MSG( "prepare Skdauftragprolink" );
	exec sql declare Ckdauftragprolink cursor with hold for Skdauftragprolink;
	exec sql free Skdauftragprolink;

	strcpy( str, "select " );
	strcat( str, KDAUFTRAGRECHART_PLISTE  );
	strcat( str, " from kdauftragrechart where " );
	strcat( str, "kdauftragnr = ? " );
	strcat( str, "for update " );

	exec sql prepare Skdauftragrechart from :str;
	ERROR_MSG( "prepare Skdauftragrechart" );
	exec sql declare Ckdauftragrechart cursor with hold for Skdauftragrechart;
	exec sql free Skdauftragrechart;

	strcpy( str, "select " );
	strcat( str, KDAUFTRAGDEBTREL_PLISTE  );
	strcat( str, " from kdauftragdebtrel where " );
	strcat( str, "kdauftragnr = ? " );
	strcat( str, "for update " );

	exec sql prepare Skdauftragdebtrel from :str;
	ERROR_MSG( "prepare Skdauftragdebtrel" );
	exec sql declare Ckdauftragdebtrel cursor with hold for Skdauftragdebtrel;
	exec sql free Skdauftragdebtrel;

	strcpy( str, "select " );
	strcat( str, KDAUFTRAGDISCACC_PLISTE  );
	strcat( str, " from kdauftragdiscacc where " );
	strcat( str, "kdauftragnr = ? " );
	strcat( str, "for update " );

	exec sql prepare Skdauftragdiscacc from :str;
	ERROR_MSG( "prepare Skdauftragdiscacc" );
	exec sql declare Ckdauftragdiscacc cursor with hold for Skdauftragdiscacc;
	exec sql free Skdauftragdiscacc;
	
	strcpy( str, "select " );
	strcat( str, KDVERBUNDPOS_PLISTE  );
	strcat( str, " from kdverbundpos where " );
	strcat( str, "herkunftfiliale = ? " );
	strcat( str, "and kdauftragnr = ? " );
	strcat( str, "and filialnr = ? " );
	strcat( str, "and posnr > 0 " );
	strcat( str, "for update " );

	exec sql prepare Skdverbundpos from :str;
	ERROR_MSG( "prepare Skdverbundpos" );
	exec sql declare Ckdverbundpos cursor with hold for Skdverbundpos;
	exec sql free Skdverbundpos;

	strcpy( str, "select " );
	strcat( str, KDVERBUNDPOSRAB_PLISTE  );
	strcat( str, " from kdverbundposrab where " );
	strcat( str, "herkunftfiliale = ? " );
	strcat( str, "and kdauftragnr = ? " );
	strcat( str, "and filialnr = ? " );
	strcat( str, "and posnr > 0 " );
	strcat( str, "for update " );

	exec sql prepare Skdverbundposrab from :str;
	ERROR_MSG( "prepare Skdverbundposrab" );
	exec sql declare Ckdverbundposrab cursor with hold for Skdverbundposrab;
	exec sql free Skdverbundposrab;

	strcpy( str, "select " );
	strcat( str, KDAUFTRAGBEM_PLISTE );
	strcat( str, " from kdauftragbem " );
	strcat( str, "where kdauftragnr = ? " );
	strcat( str, "for update " );

	exec sql prepare Skdauftragbem from :str;
	ERROR_MSG( "prepare Skdauftragbem" );
	exec sql declare Ckdauftragbem cursor with hold for Skdauftragbem;
	exec sql free Skdauftragbem;

	strcpy( str, "select " );
	strcat( str, ORDERREMARKS_PLISTE );
	strcat( str, " from orderremarks " );
	strcat( str, "where cscorderno = ? " );
	strcat( str, "for update " );

	exec sql prepare Sorderremarks from :str;
	ERROR_MSG( "prepare Sorderremarks" );
	exec sql declare Corderremarks cursor with hold for Sorderremarks;
	exec sql free Sorderremarks;

	strcpy( str, "select " );
	strcat( str, CSCORDERFLAGS_PLISTE );
	strcat( str, " from cscorderflags " );
	strcat( str, "where cscorderno = ? " );
	strcat( str, "for update " );

	exec sql prepare Scscorderflags from :str;
	ERROR_MSG( "prepare Scscorderflags" );
	exec sql declare Ccscorderflags cursor with hold for Scscorderflags;
	exec sql free Scscorderflags;

	strcpy(str, "select ");
	strcat(str, CSCORDERPOSSPLITTINFO_PLISTE);
	strcat(str, " from cscorderpossplittinfo ");
	strcat(str, "where cscorderno = ? ");
	strcat(str, "for update ");

	exec sql prepare Scscorderpossplittinfo from : str;
	ERROR_MSG("prepare Scscorderpossplittinfo");
	exec sql declare Ccscorderpossplittinfo cursor with hold for Scscorderpossplittinfo;
	exec sql free Scscorderpossplittinfo;

	strcpy(str, "select ");
	strcat(str, CSCORDERIBTPICKINGDATA_PLISTE);
	strcat(str, " from cscorderibtpickingdata ");
	strcat(str, "where cscorderno = ? ");
	strcat(str, "for update ");

	exec sql prepare Scscorderibtpickingdata from : str;
	ERROR_MSG("prepare Scscorderibtpickingdata");
	exec sql declare Ccscorderibtpickingdata cursor with hold for Scscorderibtpickingdata;
	exec sql free Scscorderibtpickingdata;

	strcpy( str, "select " );
	strcat( str, ORDERPOSITIONDISCOUNT_PLISTE );
	strcat( str, " from orderpositiondiscount " );
	strcat( str, "where orderno = ? " );
	strcat( str, "for update " );

	exec sql prepare Sorderpositiondiscount from :str;
	ERROR_MSG( "prepare Sorderpositiondiscount" );
	exec sql declare Corderpositiondiscount cursor with hold for Sorderpositiondiscount;
	exec sql free Sorderpositiondiscount;

	strcpy( str, "select " );
	strcat( str, "1 " );
	strcat( str, "from orderpositiondiscountprocessed " );
	strcat( str, "where orderno = ? " );
	strcat( str, "for update " );

	exec sql prepare Spositiondiscountprocessed from :str;
	ERROR_MSG( "prepare Spositiondiscountprocessed" );
	exec sql declare Cpositiondiscountprocessed cursor with hold for Spositiondiscountprocessed;
	exec sql free Spositiondiscountprocessed;

	strcpy( str, "select " );
	strcat( str, DISPOARTIKEL_PLISTE );
	strcat( str, " from dispoartikel where " );
	strcat( str, "kdauftragnr = ? " );
	strcat( str, "and posnr > 0 " );
	strcat( str, "for update " );

	exec sql prepare Sdispoartikel from :str;
	ERROR_MSG( "prepare Sdispoartikel" );
	exec sql declare Cdispoartikel cursor with hold for Sdispoartikel;
	exec sql free Sdispoartikel;

	strcpy( str, "select 0, AUFTRAGNRKO,KDAUFTRAGNR,KOBEHAELTNR " );
	strcat( str, "from koeinheit where " );
	strcat( str, "kdauftragnr = ? " );
	strcat( str, "for update " );

	exec sql prepare Skoeinheit from :str;
	ERROR_MSG( "prepare Skoeinheit" );
	exec sql declare Ckoeinheit cursor with hold for Skoeinheit;
	exec sql free Skoeinheit;
	
	/* sonderbehandlung: wie a-tabellen */
	strcpy( str, "select * from nachlieferpos where " );
	strcat( str, "datum < ? and " );
	strcat( str, "(postyp in (1,2,4) " );
	strcat( str, "or (postyp in (3,5) " );
	strcat( str, "and status = 2) ) " );
	strcat( str, "and vertriebszentrumnr=" );
	strcat( str, szFiliale );
	strcat( str, " for update " );

	exec sql prepare Snachlieferpos from :str;
	ERROR_MSG( "prepare Snachlieferpos" );
	exec sql declare Cnachlieferpos cursor with hold for Snachlieferpos;
	exec sql free Snachlieferpos;
	
	strcpy( str, "select * " );
	strcat( str, "from akoeinheit where " );
	strcat( str, "datum < ? and " );
	strcat( str, "auftragnrko > 0 for update " );

	exec sql prepare SAkoeinheit from :str;
	ERROR_MSG( "prepare SAkoeineheit" );
	exec sql declare CAkoeinheit cursor with hold for SAkoeinheit;
	exec sql free SAkoeinheit;

	strcpy( str, "select datum,herkunftfiliale,kdauftragnr " );
	strcat( str, "from akdverbund where " );
	strcat( str, "datum < ? and " );
	strcat( str, "kdauftragnr > 0 for update " );

	exec sql prepare SAkdverbund from :str;
	ERROR_MSG( "prepare SAkdverbund" );
	exec sql declare CAkdverbund cursor with hold for SAkdverbund;
	exec sql free SAkdverbund;

	strcpy( str, "select * from koauftrag for update" );
	exec sql prepare Skoauftrag from :str;
	 ERROR_MSG( "prepare Skoauftrag" );
	exec sql declare Ckoauftrag cursor with hold for Skoauftrag;
	exec sql free Skoauftrag;

/* 
	strcpy( str, "select * from koeinheit for update" );
	exec sql prepare Skoeinheit from :str;
	ERROR_MSG( "prepare Skoeinheit" );
	exec sql declare Ckoeinheit cursor with hold for Skoeinheit;
*/ 
	strcpy( str, "select * from nummer for update" );
	exec sql prepare Snummer from :str;
	ERROR_MSG( "prepare Snummer" );
	exec sql declare Cnummer cursor with hold for Snummer;
	exec sql free Snummer;

	/* Delete */
	strcpy( str, "delete from kdtourdruck where current of Ckdtourdruck" );
	exec sql prepare Dkdtourdruck from :str;
	ERROR_MSG( "prepare Dkdtourdruck" );

	strcpy( str, "delete from fkwarteschlange where current of Cfkwarteschlange" );
	exec sql prepare Dfkwarteschlange from :str;
	ERROR_MSG( "prepare Dfkwarteschlange" );
	
	strcpy( str, "delete from kdauftrag where current of Ckdauftrag" );
	exec sql prepare Dkdauftrag from :str;
	ERROR_MSG( "prepare Dkdauftrag" );
	
/*	strcpy( str, "delete from kdauftragzusatz where current of Ckdauftragzus" );
	exec sql prepare Dkdauftragzus from :str;
	ERROR_MSG( "prepare Dkdauftragzus" );
*/	
	strcpy( str, "delete from kdverbund where current of Ckdverbund" );
	exec sql prepare Dkdverbund from :str;
	ERROR_MSG( "prepare Dkdverbund" );
	
	strcpy( str, "delete from kdverbund where current of Ckdverbund3" );
	exec sql prepare Dkdverbund3 from :str;
	ERROR_MSG( "prepare Dkdverbund3" );
	
/*	strcpy( str, "delete from akdauftragzusatz where current of CAkdauftragzus" );
	exec sql prepare DAkdauftragzus from :str;
	ERROR_MSG( "prepare DAkdauftragzusatz" );
*/	
	strcpy( str, "delete from akdauftrag where current of CAkdauftrag" );
	exec sql prepare DAkdauftrag from :str;
	ERROR_MSG( "prepare DAkdauftrag" );
	
	strcpy( str, "delete from kdauftragpos where current of Ckdauftragpos" );
	exec sql prepare Dkdauftragpos from :str;
	ERROR_MSG( "prepare Dkdauftragpos" );
	
	strcpy( str, "delete from kdauftragposcharge where current of Ckdauftragposcharge" );
	exec sql prepare Dkdauftragposcharge from :str;
	ERROR_MSG( "prepare Dkdauftragposcharge" );
	
	strcpy( str, "delete from kdauftragposrab where current of Ckdauftragposrab" );
	exec sql prepare Dkdauftragposrab from :str;
	ERROR_MSG( "prepare Dkdauftragposrab" );
	
	strcpy( str, "delete from kdauftragposchange where current of Ckdauftragposchange" );
	exec sql prepare Dkdauftragposchange from :str;
	ERROR_MSG( "prepare Dkdauftragposchange" );
	
	strcpy( str, "delete from kdauftrposrechart where current of Ckdauftragposrechart" );
	exec sql prepare Dkdauftragposrechart from :str;
	ERROR_MSG( "prepare Dkdauftragposrechart" );
	
	strcpy( str, "delete from kdauftragpospromo where current of Ckdauftragpospromo" );
	exec sql prepare Dkdauftragpospromo from :str;
	ERROR_MSG( "prepare Dkdauftragpospromo" );
	
	strcpy( str, "delete from kdauftragposrefund where current of Ckdauftragposrefund" );
	exec sql prepare Dkdauftragposrefund from :str;
	ERROR_MSG( "prepare Dkdauftragposrefund" );
	
	strcpy( str, "delete from kdauftragposxml where current of Ckdauftragposxml" );
	exec sql prepare Dkdauftragposxml from :str;
	ERROR_MSG( "prepare Dkdauftragposxml" );
	
	strcpy( str, "delete from kdauftragposereignis where current of Ckdauftragposereignis" );
	exec sql prepare Dkdauftragposereignis from :str;
	ERROR_MSG( "prepare Dkdauftragposereignis" );
	
	strcpy( str, "delete from kdauftragpostour where current of Ckdauftragpostour" );
	exec sql prepare Dkdauftragpostour from :str;
	ERROR_MSG( "prepare Dkdauftragpostour" );

	strcpy(str, "delete from kdauftragpartnerfunction where current of Ckdauftragpartnerfunction");
	exec sql prepare Dkdauftragpartnerfunction from :str;
	ERROR_MSG("prepare Dkdauftragpartnerfunction");

	strcpy( str, "delete from kdauftragwerte where current of Ckdauftragwerte" );
	exec sql prepare Dkdauftragwerte from :str;
	ERROR_MSG( "prepare Dkdauftragwerte" );
	
	strcpy( str, "delete from orderrelationno where current of Corderrelationno" );
	exec sql prepare Dorderrelationno from :str;
	ERROR_MSG( "prepare Dorderrelationno" );
	
	strcpy( str, "delete from kdauftragprolink where current of Ckdauftragprolink" );
	exec sql prepare Dkdauftragprolink from :str;
	ERROR_MSG( "prepare Dkdauftragprolink" );
	
	strcpy( str, "delete from kdauftragrechart where current of Ckdauftragrechart" );
	exec sql prepare Dkdauftragrechart from :str;
	ERROR_MSG( "prepare Dkdauftragrechart" );
	
	strcpy( str, "delete from kdauftragdebtrel where current of Ckdauftragdebtrel" );
	exec sql prepare Dkdauftragdebtrel from :str;
	ERROR_MSG( "prepare Dkdauftragdebtrel" );
	
	strcpy( str, "delete from orderremarks where current of Corderremarks" );
	exec sql prepare Dorderremarks from :str;
	ERROR_MSG( "prepare Dorderremarks" );
	
	strcpy( str, "delete from cscorderflags where current of Ccscorderflags" );
	exec sql prepare Dcscorderflags from :str;
	ERROR_MSG( "prepare Dcscorderflags" );

	strcpy(str, "delete from cscorderpossplittinfo where current of Ccscorderpossplittinfo");
	exec sql prepare Dcscorderpossplittinfo from : str;
	ERROR_MSG("prepare Dcscorderpossplittinfo");

	strcpy(str, "delete from cscorderibtpickingdata where current of Ccscorderibtpickingdata");
	exec sql prepare Dcscorderibtpickingdata from : str;
	ERROR_MSG("prepare Dcscorderibtpickingdata");

	strcpy( str, "delete from orderpositiondiscount where current of Corderpositiondiscount" );
	exec sql prepare Dorderpositiondiscount from :str;
	ERROR_MSG( "prepare Dorderpositiondiscount" );
	
	strcpy( str, "delete from orderpositiondiscountprocessed where current of Cpositiondiscountprocessed" );
	exec sql prepare Dpositiondiscountprocessed from :str;
	ERROR_MSG( "prepare Dpositiondiscountprocessed" );
	
	strcpy( str, "delete from kdauftragdiscacc where current of Ckdauftragdiscacc" );
	exec sql prepare Dkdauftragdiscacc from :str;
	ERROR_MSG( "prepare Dkdauftragdiscacc" );
	
	strcpy( str, "delete from kdverbundpos where current of Ckdverbundpos" );
	exec sql prepare Dkdverbundpos from :str;
	ERROR_MSG( "prepare Dkdverbundpos" );
	
	strcpy( str, "delete from kdverbundposrab where current of Ckdverbundposrab" );
	exec sql prepare Dkdverbundposrab from :str;
	ERROR_MSG( "prepare Dkdverbundposrab" );

	strcpy( str, "delete from akdauftragpos where datum=? and kdauftragnr =? " );
	exec sql prepare DAkdauftragpos from :str;
	ERROR_MSG( "prepare DAkdauftragpos" );

	strcpy( str, "delete from akdauftragposrab where datum=? and kdauftragnr =? " );
	exec sql prepare DAkdauftragposrab from :str;
	ERROR_MSG( "prepare DAkdauftragposrab" );

	strcpy( str, "delete from akdauftragpospromo where datum=? and kdauftragnr =? " );
	exec sql prepare DAkdauftragpospromo from :str;
	ERROR_MSG( "prepare DAkdauftragpospromo" );

	strcpy( str, "delete from akdauftrposrechart where datum=? and kdauftragnr =? " );
	exec sql prepare DAkdauftragposrechart from :str;
	ERROR_MSG( "prepare DAkdauftragposrechart" );

	strcpy( str, "delete from akdauftragposrefun where datum=? and kdauftragnr =? " );
	exec sql prepare DAkdauftragposrefund from :str;
	ERROR_MSG( "prepare DAkdauftragposrefund" );

	strcpy( str, "delete from akdauftragposxml where datum=? and kdauftragnr =? " );
	exec sql prepare DAkdauftragposxml from :str;
	ERROR_MSG( "prepare DAkdauftragposxml" );

	strcpy( str, "delete from akdauftragposereignis where datum_rechnung=? and kdauftragnr =? " );
	exec sql prepare DAkdauftragposereignis from :str;
	ERROR_MSG( "prepare DAkdauftragposereignis" );

	strcpy( str, "delete from akdauftragpostour where datum=? and kdauftragnr =? " );
	exec sql prepare DAkdauftragpostour from :str;
	ERROR_MSG( "prepare DAkdauftragpostour" );

	strcpy(str, "delete from akdauftragpartnerfunction where datum=? and kdauftragnr =? ");
	exec sql prepare DAkdauftragpartnerfunction from :str;
	ERROR_MSG("prepare DAkdauftragpartnerfunction");

	strcpy( str, "delete from akdauftragposcharg where date=? and kdauftragnr =? " );
	exec sql prepare DAkdauftragposcharge from :str;
	ERROR_MSG( "prepare DAkdauftragposcharge" );

	strcpy( str, "delete from akdauftragposchang where datum=? and kdauftragnr =? " );
	exec sql prepare DAkdauftragposchange from :str;
	ERROR_MSG( "prepare DAkdauftragposchange" );

	strcpy( str, "delete from akdauftragwerte where datum=? and kdauftragnr =? " );
	exec sql prepare DAkdauftragwerte from :str;
	ERROR_MSG( "prepare DAkdauftragwerte" );

	strcpy( str, "delete from aorderrelationno where date=? and cscorderno =? " );
	exec sql prepare DAorderrelationno from :str;
	ERROR_MSG( "prepare DAorderrelationno" );

	strcpy( str, "delete from akdauftragprolink where datum=? and kdauftragnr =? " );
	exec sql prepare DAkdauftragprolink from :str;
	ERROR_MSG( "prepare DAkdauftragprolink" );

	strcpy( str, "delete from akdauftragrechart where datum=? and kdauftragnr =? " );
	exec sql prepare DAkdauftragrechart from :str;
	ERROR_MSG( "prepare DAkdauftragrechart" );

	strcpy( str, "delete from akdauftragdebtrel where datum=? and kdauftragnr =? " );
	exec sql prepare DAkdauftragdebtrel from :str;
	ERROR_MSG( "prepare DAkdauftragdebtrel" );

	strcpy( str, "delete from akdauftragdiscacc where datum=? and kdauftragnr =? " );
	exec sql prepare DAkdauftragdiscacc from :str;
	ERROR_MSG( "prepare DAkdauftragdiscacc" );

	strcpy( str, "delete from kdauftragereignis where current of Ckdauftragerg" );
	exec sql prepare Dkdauftragerg from :str;
	ERROR_MSG( "prepare Dkdauftragerg" );
	
	strcpy( str, "delete from akdauftragereignis where datum_rechnung=? and kdauftragnr=?" );
	exec sql prepare DAkdauftragerg from :str;
	ERROR_MSG( "prepare DAkdauftragerg" );
	
	strcpy( str, "delete from kdauftragbem where current of Ckdauftragbem" );
	exec sql prepare Dkdauftragbem from :str;
	ERROR_MSG( "prepare Dkdauftragbem" );
	
	strcpy( str, "delete from akdauftragbem where datum=? and kdauftragnr=?" );
	exec sql prepare DAkdauftragbem from :str;
	ERROR_MSG( "prepare DAkdauftragbem" );
	
	strcpy( str, "delete from aorderremarks where datum=? and cscorderno=?" );
	exec sql prepare DAorderremarks from :str;
	ERROR_MSG( "prepare DAorderremarks" );
	
	strcpy( str, "delete from acscorderpossplittinfo where datum=? and cscorderno=?" );
	exec sql prepare DAcscorderpossplittinfo from :str;
	ERROR_MSG( "prepare DAcscorderpossplittinfo" );

	strcpy(str, "delete from acscorderibtpickingdata where archivedate=? and cscorderno=?");
	exec sql prepare DAcscorderibtpickingdata from : str;
	ERROR_MSG("prepare DAcscorderibtpickingdata");

	strcpy(str, "delete from acscorderflags where datum=? and cscorderno=?");
	exec sql prepare DAcscorderflags from : str;
	ERROR_MSG("prepare DAcscorderflags");

	strcpy( str, "delete from aorderpositiondiscount where orderdate=? and orderno=?" );
	exec sql prepare DAorderpositiondiscount from :str;
	ERROR_MSG( "prepare DAorderpositiondiscount" );
	
	strcpy( str, "delete from dispoartikel where current of Cdispoartikel" );
	exec sql prepare Ddispoartikel from :str;
	ERROR_MSG( "prepare Ddispoartikel" );
	
	strcpy( str, "delete from adispoartikel where datum=? and kdauftragnr=?" );
	exec sql prepare DAdispoartikel from :str;
	ERROR_MSG( "prepare DAdispoartikel" );
	
	strcpy( str, "delete from akoeinheit where current of CAkoeinheit" );
	exec sql prepare DAkoeinheit from :str;
	ERROR_MSG( "prepare DAkoeinheit" );

	strcpy( str, "delete from akdverbund where current of CAkdverbund" );
	exec sql prepare DAkdverbund from :str;
	ERROR_MSG( "prepare DAkdverbund" );

	strcpy( str, "delete from akdverbundpos where datum=? and herkunftfiliale=? and kdauftragnr=?" );
	exec sql prepare DAkdverbundpos from :str;
	ERROR_MSG( "prepare DAkdverbundpos" );

	strcpy( str, "delete from akdverbundposrab where datum=? and herkunftfiliale=? and kdauftragnr=?" );
	exec sql prepare DAkdverbundposrab from :str;
	ERROR_MSG( "prepare DAkdverbundposrab" );

	strcpy( str, "delete from koauftrag where current of Ckoauftrag" );
	exec sql prepare Dkoauftrag from :str;
	ERROR_MSG( "prepare Dkoauftrag" );
	
	strcpy( str, "delete from koeinheit where current of Ckoeinheit" );
	exec sql prepare Dkoeinheit from :str;
	ERROR_MSG( "prepare Dkoeinheit" );
	
	strcpy( str, "delete from nachlieferpos where current of Cnachlieferpos" );
	exec sql prepare Dnachlieferpos from :str;
	ERROR_MSG( "prepare Dnachlieferpos" );
	
	strcpy( str, "delete from stockentry where current of CStockentry" );
	exec sql prepare DStockentry from :str;
	ERROR_MSG( "prepare DStockentry" );

	strcpy( str, "delete from acststockreserved where current of CAcststock" );
	exec sql prepare DAcststock from :str;
	ERROR_MSG( "prepare DAcststock" );

if (isDE == YES)
{
	strcpy( str, "delete from toteinfo where current of CToteinfo" );
	exec sql prepare DToteinfo from :str;
	ERROR_MSG( "prepare DToteinfo" );
}

	strcpy(str, "delete from documentprintinfo where current of CDocumentprintinfo");
	exec sql prepare DDocumentprintinfo from :str;
	ERROR_MSG("prepare DDocumentprintinfo");

	/* Select */
	strcpy( str, "select * from fkwarteschlange where kdauftragnr in (" );
	strcat( str, "select kdauftragnr from kdauftrag where vertriebszentrumnr=");
	strcat( str, szFiliale );
	strcat(str, ") for update" );
	exec sql prepare Sfkwarteschlange from :str;
	ERROR_MSG( "prepare Sfkwarteschlange" );
	exec sql declare Cfkwarteschlange cursor with hold for Sfkwarteschlange;
	
	strcpy( str, "select * from kdtourdruck for update" );
	exec sql prepare Skdtourdruck from :str;
	ERROR_MSG( "prepare Skdtourdruck" );
	exec sql declare Ckdtourdruck cursor with hold for Skdtourdruck;
	
	strcpy( str, "update nummer set nummerwert = nummermindest where current of Cnummer" );
	exec sql prepare Unummer from :str;
	ERROR_MSG( "prepare Unummer" );
	
	/* Verbundpositionen ohne Header */  
	strcpy( str, "select " );
	strcat( str, KDVERBUNDPOS_PLISTE  );
	strcat( str, " from kdverbundpos " );
	strcat( str, " where filialnr=");
	strcat( str, szFiliale );
	strcat( str, "for update " );

	exec sql prepare Skdvbpos from :str;
	ERROR_MSG( "prepare Skdvbpos" );
	exec sql declare Ckdvbpos cursor with hold for Skdvbpos;
	exec sql free Skdvbpos;
	
	strcpy( str, "delete from kdverbundpos where current of Ckdvbpos" );
	exec sql prepare Dkdvbpos from :str;
	ERROR_MSG( "prepare Dkdvbpos" );

	/* Täglich in der Schweiz erstellte Relationen */  
	strcpy( str, "select * " );
	strcat( str, "from customerorderno " );
	strcat( str, "for update " );

	exec sql prepare SCustomerno from :str;
	ERROR_MSG( "prepare SCustomerno" );
	exec sql declare CCustomerno cursor with hold for SCustomerno;
	
	strcpy( str, "delete from customerorderno where current of CCustomerno" );
	exec sql prepare DCustomerno from :str;
	ERROR_MSG( "prepare DCustomerno" );

	strcpy( str, "select 1 " );
	strcat( str, "from oecustomercalls " );
	strcat( str, "where calldate < ? " );
	strcat( str, "and branchno = ? " );
	strcat( str, "for update " );

	exec sql prepare SOECustomerCalls from :str;
	ERROR_MSG( "prepare SOECustomerCalls" );
	exec sql declare COECustomerCalls cursor with hold for SOECustomerCalls;
	
	strcpy( str, "delete from oecustomercalls where current of COECustomerCalls" );
	exec sql prepare DOECustomerCalls from :str;
	ERROR_MSG( "prepare DOECustomerCalls" );

	strcpy( str, "select * " );
	strcat( str, "from kdauftraginfo where " );
	strcat( str, "kdauftragnr = ? " );
	strcat( str, "for update " );

	exec sql prepare SKdinfo from :str;
	ERROR_MSG( "prepare SKdinfo" );
	exec sql declare CKdinfo cursor with hold for SKdinfo;
	
	strcpy( str, "delete from kdauftraginfo where current of CKdinfo" );
	exec sql prepare DKdinfo from :str;
	ERROR_MSG( "prepare DKdinfo" );


	/* echten Eintrag aus Ereignissen (noch alter vorhanden) */  
	strcpy( str, "select datum " );
	strcat( str, "from kdauftragereignis where " );
	strcat( str, "kdauftragnr = ? " );
	strcat( str, "and EREIGNISART in (9,11,109) " );
	strcat( str, "order by datum desc " );

	exec sql prepare SDatum from :str;
	ERROR_MSG( "prepare SDatum" );
	exec sql declare CDatum cursor with hold for SDatum;

	strcpy( str, "select min(datum) " );
	strcat( str, "from akdauftragereignis where " );
	strcat( str, "datum_rechnung = ? " );
	strcat( str, "and kdauftragnr = ? " );
	strcat( str, "and EREIGNISART = 1 " );

	exec sql prepare SDatumVon from :str;
	ERROR_MSG( "prepare SDatumVon" );

	strcpy( str, "select datum " );
	strcat( str, "from akdauftragereignis where " );
	strcat( str, "datum_rechnung = ? " );
	strcat( str, "and kdauftragnr = ? " );
	strcat( str, "and EREIGNISART in (9,11,109) " );

	exec sql prepare SDatumBis from :str;
	ERROR_MSG( "prepare SDatumBis" );

	strcpy( str, "select ibtrequestid " );
	strcat( str, "from ibtrequest where " );
	strcat( str, "cscorderno = ? " );
	strcat( str, "and TO_CHAR(creationdatetime, '%Y%m%d') between ? and ? " );
	strcat( str, "for update " );

	exec sql prepare Sibtrequest from :str;
	ERROR_MSG( "prepare Sibtrequest" );
	exec sql declare Cibtrequest cursor with hold for Sibtrequest;
	exec sql free Sibtrequest;
	
	strcpy( str, "delete from ibtrequest where current of Cibtrequest" );
	exec sql prepare Dibtrequest from :str;
	ERROR_MSG( "prepare Dibtrequest" );
	
	strcpy( str, "delete from ibtdiscountrequest where ibtrequestid = ?" );
	exec sql prepare Dibtdiscountrequest from :str;
	ERROR_MSG( "prepare Dibtdiscountrequest" );
	
	strcpy( str, "delete from ibtremarkrequest where ibtrequestid = ?" );
	exec sql prepare Dibtremarkrequest from :str;
	ERROR_MSG( "prepare Dibtremarkrequest" );
	
	strcpy( str, "delete from ibtresponse where ibtrequestid = ?" );
	exec sql prepare Dibtresponse from :str;
	ERROR_MSG( "prepare Dibtresponse" );

	return OK;
}

/***** DELETE-FKWARTESCHLANGE **********************************************/

static int DeleteKdTourDruck( struct ZAEHLER *z )
{
  char *fun = "DeleteKdTourDruck";
  int i = 0;
  
  exec sql open Ckdtourdruck;
  ERROR_MSG( "open Ckdtourdruck" )

  for( ;; )
     {
     if ( i == 0 )
	    Commit( fun );

     exec sql fetch Ckdtourdruck;
     ERROR_MSG( "fetch Ckdtourdruck" )
     if ( NOT_FOUND )
	    {
	    exec sql commit work;
	    break;
	    }
     else if ( i >= MAX_TRANSAKTION )
        {
	    i = 0;
		}
     exec sql execute Dkdtourdruck;
     ERROR_MSG( "execute Dkdtourdruck" );
     z->DelKdTourDruck++;
     }

  exec sql close Ckdtourdruck;
  return OK;
}	

/***** DELETE-FKWARTESCHLANGE **********************************************/

static int DeleteFkwarteschlange( struct ZAEHLER *z )
{
  char *fun = "DeleteFkwarteschlange";
  int i = 0;

  exec sql open Cfkwarteschlange;
  ERROR_MSG( "open Cfkwarteschlange" )

  for( ;; )
     {
     if ( i == 0 )
	Commit( fun );

     exec sql fetch Cfkwarteschlange;
     ERROR_MSG( "fetch Cfkwarteschlange" )
     if ( NOT_FOUND )
	{
	exec sql commit work;
	break;
	}
     else if ( i >= MAX_TRANSAKTION )
       i = 0;

      exec sql execute Dfkwarteschlange;
      ERROR_MSG( "execute Dfkwarteschlange" );
      z->DelFkwarteschlange++;
      }

  exec sql close Cfkwarteschlange;
  return OK;
}

/***** START-KDAUFTRAG ******************************************************/

static int StartKdauftrag( void )
{
  char *fun = "StartKdauftrag";

  exec sql open Ckdauftrag;
  ERROR_MSG( "open Ckdauftrag" )

  return OK;
}

/***** START-KDVERBUND ******************************************************/

static int StartKdverbund( void )
{
  char *fun = "StartKdverbund";

  exec sql open Ckdverbund;
  ERROR_MSG( "open Ckdverbund" )

  return OK;
}

/***** START-KDVERBUND vbstatus 3  ******************************************************/

static int StartKdverbund3( void )
{
  char *fun = "StartKdverbund3";

  exec sql open Ckdverbund3;
  ERROR_MSG( "open Ckdverbund3" )

  return OK;
}

/***** DELETE-KDAUFTRAG *****************************************************/

static int DeleteKdauftrag( Nummer *num, struct ZAEHLER *z )
{
  exec sql begin declare section;
  kdauftragS d;
  int Datum;
  exec sql end declare section;

  char *fun = "DeleteKdauftrag";

  Commit( fun );
  exec sql fetch Ckdauftrag into :d;
  ERROR_MSG( "fetch Ckdauftrag" )
  if ( NOT_FOUND )
  {
     exec sql commit work;
     return SQLNOTFOUND;
  }

  if (CheckIBTPickingDone(d.KDAUFTRAGNR) == ERROR) return WARNING;

  if ( ( Datum = DeleteKdauftragEreignis( d.KDAUFTRAGNR, z ) ) == ERROR )
     return ERROR;

  num->KdNr  = d.KDAUFTRAGNR;
  num->Datum = Datum;

  exec sql insert into akdauftrag (DATUM,KDAUFTRAG_LISTE_390) values ( :Datum, :d );
/*  ERROR_MLD( "insert akdauftrag" )*/
	if(SQLCODE == -239)
	{
		sprintf(str,"insert akdauftrag bei Aufnr.: %d",d.KDAUFTRAGNR);
		ERROR_MSG( str ) /* wegen zentr*/
	}
	else
	{
		ERROR_MSG( "insert akdauftrag" ) /* wegen zentr*/
	}


  exec sql execute Dkdauftrag;
  ERROR_MSG( "execute Dkdauftrag" );
  z->DelKdauftrag++;

  return OK;
}

/***** DELETE-KDVERBUND *****************************************************/

static int DeleteKdverbund( Nummer *num, struct ZAEHLER *z )
{
  exec sql begin declare section;
  kdverbundS d;
  exec sql end declare section;

  char *fun = "DeleteKdverbund";

  Commit( fun );
  exec sql fetch Ckdverbund into :d;
  ERROR_MSG( "fetch Ckdverbund" )
  if ( NOT_FOUND )
  {
     exec sql commit work;
     return SQLNOTFOUND;
  }

  num->FilialNr = d.FILIALNR;
  num->HerkunftFiliale = d.HERKUNFTFILIALE;
  num->KdNr  = d.KDAUFTRAGNR;
  num->Datum  = d.DATUM;

  /*akdverbund ist gleicher aufbau wie kdverbund*/
  exec sql insert into akdverbund (KDVERBUND_LISTE_390) values ( :d );
  ERROR_MLD( "insert akdverbund" )

  exec sql execute Dkdverbund;
  ERROR_MSG( "execute Dkdverbund" );
  z->DelKdverbund++;
  return OK;
}

/***** DELETE-KDVERBUND vbstatus 3*****************************************************/

static int DeleteKdverbund3( Nummer *num, struct ZAEHLER *z )
{
	exec sql begin declare section;
	kdverbundS d;
	exec sql end declare section;
	
	char *fun = "DeleteKdverbund3";
	
	Commit( fun );
	
	for(;;)
	{
		exec sql fetch Ckdverbund3 into :d;
		ERROR_MSG( "fetch Ckdverbund3" )
		if ( NOT_FOUND )
		{
			exec sql commit work;
			return SQLNOTFOUND;
		}
	
		exec sql open Cvbposdone using :d.FILIALNR,:d.HERKUNFTFILIALE,:d.KDAUFTRAGNR,:d.IBTTYPE;
		ERROR_MSG( "open Cvbposdone" ) 
		exec sql fetch Cvbposdone;
		ERROR_MSG( "fetch Cvbposdone" )

		if ( NOT_FOUND )
		{
			exec sql close Cvbposdone;
			break;
		}
		else
		{
			exec sql close Cvbposdone;
			continue;
		}
	}
		
	num->FilialNr = d.FILIALNR;
	num->HerkunftFiliale = d.HERKUNFTFILIALE;
	num->KdNr  = d.KDAUFTRAGNR;
	num->Datum  = d.DATUM;
	
	/*akdverbund ist gleicher aufbau wie kdverbund*/
	exec sql insert into akdverbund (KDVERBUND_LISTE_390) values ( :d );
	ERROR_MLD( "insert akdverbund" )
	
	exec sql execute Dkdverbund3;
	ERROR_MSG( "execute Dkdverbund3" );
	z->DelKdverbund++;
	return OK;
}

/***** DELETE-KDVERBUND-POS *************************************************/

static int DeleteKdverbundPos( Nummer *num, struct ZAEHLER *z )
{
  exec sql begin declare section;
  kdverbundposS d;
  int Datum;							
  exec sql end declare section;
  char *fun = "DeleteKdverbundPos";

  d.HERKUNFTFILIALE = num->HerkunftFiliale;
  d.FILIALNR = num->FilialNr;
  d.KDAUFTRAGNR = num->KdNr;
  Datum = num->Datum;
  exec sql open Ckdverbundpos using :d.HERKUNFTFILIALE, :d.KDAUFTRAGNR , :d.FILIALNR;
  ERROR_MSG( "open Ckdverbundpos" )

  for( ;; )
  {
     exec sql fetch Ckdverbundpos into :d;
     ERROR_MSG( "fetch Ckdverbundpos" )
     if ( NOT_FOUND )
     	break;

     exec sql insert into akdverbundpos (DATUM,KDVERBUNDPOS_LISTE_390) values ( :Datum, :d );
     ERROR_MLD( "insert akdverbundpos" )
    
     exec sql execute Dkdverbundpos;
     ERROR_MSG( "execute Dkdverbundpos" );
     z->DelKdverbundPos++;
     }

  return OK;
}

/***** DELETE-KDVERBUND-POS-RAB *************************************************/

static int DeleteKdverbundPosRab( Nummer *num, struct ZAEHLER *z )
{
  exec sql begin declare section;
  kdverbundposrabS d;
  int Datum;							
  exec sql end declare section;
  char *fun = "DeleteKdverbundPosRab";

  d.HERKUNFTFILIALE = num->HerkunftFiliale;
  d.FILIALNR = num->FilialNr;
  d.KDAUFTRAGNR = num->KdNr;
  Datum = num->Datum;
  exec sql open Ckdverbundposrab using :d.HERKUNFTFILIALE, :d.KDAUFTRAGNR , :d.FILIALNR;
  ERROR_MSG( "open Ckdverbundposrab" )

  for( ;; )
  {
     exec sql fetch Ckdverbundposrab into :d;
     ERROR_MSG( "fetch Ckdverbundposrab" )
     if ( NOT_FOUND )
     	break;

     exec sql insert into akdverbundposrab (DATUM,KDVERBUNDPOSRAB_LISTE_390) values ( :Datum, :d );
     ERROR_MLD( "insert akdverbundposrab" )
    
     exec sql execute Dkdverbundposrab;
     ERROR_MSG( "execute Dkdverbundposrab" );
     z->DelKdverbundPosRab++;
     }

  return OK;
}

/***** DELETE-KDVERBUND-POS-OHNE-HEADER *******************************************/

static int DeleteKdvbPosWithoutHeader( struct ZAEHLER *z )
{
  char error_msg[512];
  exec sql begin declare section;
  kdverbundposS d;
  exec sql end declare section;
  char *fun = "DeleteKdvbPosWithoutHeader";

  exec sql begin work;
  ERROR_MSG( "begin work" );

  exec sql open Ckdvbpos;
  ERROR_MSG( "open Ckdvbpos" )

  for( ;; )
  {
     exec sql fetch Ckdvbpos into :d;
     ERROR_MSG( "fetch Ckdvbpos" )
     if ( NOT_FOUND )
     	break;

	 sprintf( error_msg, " Fili/AufNr/PosNr/PZN/Menge: %d/%ld/%ld/%ld/%ld",
			d.HERKUNFTFILIALE,
			d.KDAUFTRAGNR,
			d.POSNR,
			d.ARTIKEL_NR,
			d.MENGEABGEBUCHT
			 );
     PrintMsg( fun, error_msg, FEHLER );

     exec sql execute Dkdvbpos;
     ERROR_MSG( "execute Dkdvbpos" );
     z->DelKdvbPosWithoutHeader++;
  }

  exec sql commit work;
  ERROR_MSG( "commit work" )
  return OK;
}

/***** DELETE-KDAUFTRAG-ZUSATZ **********************************************/

static int DeleteKdauftragZusatz( Nummer *num, struct ZAEHLER *z )
{
  exec sql begin declare section;
  /* struct KDAUFTRAGZUSATZ d; */
  kdauftragzusatzS d;
  int Datum;
  exec sql end declare section;
  
  char *fun = "DeleteKdauftragZusatz";

  d.KDAUFTRAGNR = num->KdNr;
  Datum = num->Datum;
  exec sql open Ckdauftragzus using :d.KDAUFTRAGNR;
  ERROR_MSG( "open Ckdauftragzus" )

  for( ;; )
     {
     exec sql fetch Ckdauftragzus into :d;
     ERROR_MSG( "fetch Ckdauftragzus" )
     if ( NOT_FOUND )
	    break;

     exec sql insert into akdauftragzusatz values ( :Datum, :d );
     ERROR_MLD( "insert akdauftragzusatz" )
    
     exec sql execute Dkdauftragzus;
     ERROR_MSG( "execute Dkdauftragzus" );
     z->DelKdauftragZusatz++;
     }

  return OK;
}

/***** DELETE-KDAUFTRAG-PROLINK **********************************************/

static int DeleteKdauftragProlink( Nummer *num, struct ZAEHLER *z )
{
  exec sql begin declare section;
  kdauftragprolinkS d;
  int Datum;
  exec sql end declare section;
  
  char *fun = "DeleteKdauftragProlink";

  d.KDAUFTRAGNR = num->KdNr;
  Datum = num->Datum;
  exec sql open Ckdauftragprolink using :d.KDAUFTRAGNR;
  ERROR_MSG( "open Ckdauftragprolink" )

  for( ;; )
     {
     exec sql fetch Ckdauftragprolink into :d;
     ERROR_MSG( "fetch Ckdauftragprolink" )
     if ( NOT_FOUND )
	    break;

     exec sql insert into akdauftragprolink values ( :Datum, :d );
     ERROR_MLD( "insert akdauftragprolink" )
    
     exec sql execute Dkdauftragprolink;
     ERROR_MSG( "execute Dkdauftragprolink" );
     z->DelKdauftragProlink++;
     }

  return OK;
}

/***** DELETE-KDAUFTRAG-POS *************************************************/

static int DeleteKdauftragPos( Nummer *num, struct ZAEHLER *z )
{
  exec sql begin declare section;
  kdauftragposS d;
  int Datum;
  exec sql end declare section;
  char *fun = "DeleteKdauftragPos";

  d.KDAUFTRAGNR = num->KdNr;
  Datum = num->Datum;
  exec sql open Ckdauftragpos using :d.KDAUFTRAGNR;
  ERROR_MSG( "open Ckdauftragpos" )

  for( ;; )
     {
     exec sql fetch Ckdauftragpos into :d;
     ERROR_MSG( "fetch Ckdauftragpos" )
     if ( NOT_FOUND )
		break;

#undef HINWEIS 
     exec sql insert into akdauftragpos (DATUM,KDAUFTRAGPOS_LISTE_390) values ( :Datum, :d );
     ERROR_MLD( "insert akdauftragpos" )
    
     exec sql execute Dkdauftragpos;
     ERROR_MSG( "execute Dkdauftragpos" );
     z->DelKdauftragPos++;
     }
#define HINWEIS              'H'
  return OK;
}

/***** DELETE-KDAUFTRAG-POSRAB *************************************************/

static int DeleteKdauftragPosRab( Nummer *num, struct ZAEHLER *z )
{
  exec sql begin declare section;
  kdauftragposrabS d;
  int Datum;
  exec sql end declare section;
  char *fun = "DeleteKdauftragPosRab";

  d.KDAUFTRAGNR = num->KdNr;
  Datum = num->Datum;
  exec sql open Ckdauftragposrab using :d.KDAUFTRAGNR;
  ERROR_MSG( "open Ckdauftragposrab" )

  for( ;; )
     {
     exec sql fetch Ckdauftragposrab into :d;
     ERROR_MSG( "fetch Ckdauftragposrab" )
     if ( NOT_FOUND )
	break;

     exec sql insert into akdauftragposrab (DATUM,KDAUFTRAGPOSRAB_LISTE_390) values ( :Datum, :d );
     ERROR_MLD( "insert akdauftragposrab" )
    
     exec sql execute Dkdauftragposrab;
     ERROR_MSG( "execute Dkdauftragposrab" );
     z->DelKdauftragposrab++;
     }

  return OK;
}

/***** DELETE-ORDERREMARKS *************************************************/

static int DeleteOrderRemarks( Nummer *num, struct ZAEHLER *z )
{
  exec sql begin declare section;
  orderremarksS d;
  int Datum;
  exec sql end declare section;
  char *fun = "DeleteOrderRemarks";

  d.CSCORDERNO = num->KdNr;
  Datum = num->Datum;
  exec sql open Corderremarks using :d.CSCORDERNO;
  ERROR_MSG( "open Corderremarks" )

  for( ;; )
     {
     exec sql fetch Corderremarks into :d;
     ERROR_MSG( "fetch Corderremarks" )
     if ( NOT_FOUND )
	break;

     exec sql insert into aorderremarks (DATUM,ORDERREMARKS_LISTE_390) values ( :Datum, :d );
     ERROR_MLD( "insert aorderremarks" )
    
     exec sql execute Dorderremarks;
     ERROR_MSG( "execute Dorderremarks" );
     z->DelOrderRemarks++;
     }

  return OK;
}

/***** DELETE-CSCORDERFLAGS *************************************************/

static int DeleteCscOrderFlags( Nummer *num, struct ZAEHLER *z )
{
  exec sql begin declare section;
  cscorderflagsS d;
  int Datum;
  exec sql end declare section;
  char *fun = "DeleteCscOrderFlags";

  d.CSCORDERNO = num->KdNr;
  Datum = num->Datum;
  exec sql open Ccscorderflags using :d.CSCORDERNO;
  ERROR_MSG( "open Ccscorderflags" )

  for( ;; )
     {
     exec sql fetch Ccscorderflags into :d;
     ERROR_MSG( "fetch Ccscorderflags" )
     if ( NOT_FOUND )
	break;

     exec sql insert into acscorderflags (DATUM,CSCORDERFLAGS_LISTE_390) values ( :Datum, :d );
     ERROR_MLD( "insert acscorderflags" )
    
     exec sql execute Dcscorderflags;
     ERROR_MSG( "execute Dcscorderflags" );
     z->DelCscOrderFlags++;
     }

  return OK;
}

/***** DELETE-CSCORDERIBTPICKINGDATA *************************************************/

static int DeleteCscOrderIBTPickingData(Nummer *num, struct ZAEHLER *z)
{
	exec sql begin declare section;
	cscorderibtpickingdataS d;
	int Datum;
	exec sql end declare section;
	char *fun = "DeleteCscOrderIBTPickingData";

	d.CSCORDERNO = num->KdNr;
	Datum = num->Datum;
	exec sql open Ccscorderibtpickingdata using :d.CSCORDERNO;
	ERROR_MSG("open Ccscorderibtpickingdata")

		for (;; )
		{
			exec sql fetch Ccscorderibtpickingdata into :d;
			ERROR_MSG("fetch Ccscorderibtpickingdata")
				if (NOT_FOUND)
					break;

			exec sql insert into acscorderibtpickingdata(ARCHIVEDATE, CSCORDERIBTPICKINGDATA_LISTE_390) values(:Datum, :d);
			ERROR_MLD("insert acscorderibtpickingdata")

			exec sql execute Dcscorderibtpickingdata;
			ERROR_MSG("execute Dcscorderibtpickingdata");
			z->DelCscOrderIBTPickingData++;
		}

	return OK;
}

/***** DELETE-CSCORDERPOSSPLITTINFO *************************************************/

static int DeleteCscOrderPosSplittInfo(Nummer *num, struct ZAEHLER *z)
{
	exec sql begin declare section;
	cscorderpossplittinfoS d;
	int Datum;
	exec sql end declare section;
	char *fun = "DeleteCscOrderPosSplittInfo";

	d.CSCORDERNO = num->KdNr;
	Datum = num->Datum;
	exec sql open Ccscorderpossplittinfo using :d.CSCORDERNO;
	ERROR_MSG("open Ccscorderpossplittinfo")

		for (;; )
		{
			exec sql fetch Ccscorderpossplittinfo into :d;
			ERROR_MSG("fetch Ccscorderpossplittinfo")
				if (NOT_FOUND)
					break;

			exec sql insert into acscorderpossplittinfo(DATUM, CSCORDERPOSSPLITTINFO_LISTE_390) values(:Datum, :d);
			ERROR_MLD("insert acscorderpossplittinfo")

			exec sql execute Dcscorderpossplittinfo;
			ERROR_MSG("execute Dcscorderpossplittinfo");
			z->DelCscOrderPosSplittInfo++;
		}

	return OK;
}

/***** DELETE-ORDERPOSITIONDISCOUNT *************************************************/

static int DeleteOrderPositionDiscount( Nummer *num, struct ZAEHLER *z )
{
  exec sql begin declare section;
  orderpositiondiscountS d;
  int Datum;
  exec sql end declare section;
  char *fun = "DeleteOrderPositionDiscount";

  d.orderno = num->KdNr;
  Datum = num->Datum;
  exec sql open Corderpositiondiscount using :d.orderno;
  ERROR_MSG( "open Corderpositiondiscount" )

  for( ;; )
     {
     exec sql fetch Corderpositiondiscount into :d;
     ERROR_MSG( "fetch Corderpositiondiscount" )
     if ( NOT_FOUND )
	break;

     exec sql insert into aorderpositiondiscount (orderdate,ORDERPOSITIONDISCOUNT_LISTE_390) values ( :Datum, :d );
     ERROR_MLD( "insert aorderpositiondiscount" )
    
     exec sql execute Dorderpositiondiscount;
     ERROR_MSG( "execute Dorderpositiondiscount" );
     z->DelOrderPositionDiscount++;
     }

  return OK;
}

/***** DELETE-ORDERPOSITIONDISCONTPROCESSED *************************************************/

static int DeleteOrderPositionDiscountProcessed( Nummer *num, struct ZAEHLER *z )
{
  exec sql begin declare section;
  int d;
  int orderno;
  exec sql end declare section;
  char *fun = "DeleteOrderPositionDiscountProcessed";

  orderno = num->KdNr;
  exec sql open Cpositiondiscountprocessed using :orderno;
  ERROR_MSG( "open Cpositiondiscountprocessed" )

  for( ;; )
  {
     exec sql fetch Cpositiondiscountprocessed into :d;
     ERROR_MSG( "fetch Cpositiondiscountprocessed" )
     if ( NOT_FOUND )
	 break;
    
     exec sql execute Dpositiondiscountprocessed;
     ERROR_MSG( "execute Dpositiondiscountprocessed" );
     z->DelPositionDiscountProcessed++;
  }

  return OK;
}

/***** DELETE-KDAUFTRAG-POSCHARGE *************************************************/

static int DeleteKdauftragPosCharge( Nummer *num, struct ZAEHLER *z )
{
  exec sql begin declare section;
  kdauftragposchargeS d;
  int Datum;
  exec sql end declare section;
  char *fun = "DeleteKdauftragPosCharge";

  d.KDAUFTRAGNR = num->KdNr;
  Datum = num->Datum;
  exec sql open Ckdauftragposcharge using :d.KDAUFTRAGNR;
  ERROR_MSG( "open Ckdauftragposcharge" )

  for( ;; )
     {
     exec sql fetch Ckdauftragposcharge into :d;
     ERROR_MSG( "fetch Ckdauftragposcharge" )
     if ( NOT_FOUND )
	break;

     exec sql insert into akdauftragposcharg (DATE,KDAUFTRAGPOSCHARGE_LISTE_390) values ( :Datum, :d );
     ERROR_MLD( "insert akdauftragposcharg" )
    
     exec sql execute Dkdauftragposcharge;
     ERROR_MSG( "execute Dkdauftragposcharge" );
     z->DelKdauftragposcharge++;
     }

  return OK;
}

/***** DELETE-KDAUFTRAG-POSCHANGE *************************************************/

static int DeleteKdauftragPosChange( Nummer *num, struct ZAEHLER *z )
{
  exec sql begin declare section;
  kdauftragposchangeS d;
  int Datum;
  exec sql end declare section;
  char *fun = "DeleteKdauftragPosChange";

  d.KDAUFTRAGNR = num->KdNr;
  Datum = num->Datum;
  exec sql open Ckdauftragposchange using :d.KDAUFTRAGNR;
  ERROR_MSG( "open Ckdauftragposchange" )

  for( ;; )
     {
     exec sql fetch Ckdauftragposchange into :d;
     ERROR_MSG( "fetch Ckdauftragposchange" )
     if ( NOT_FOUND )
	break;

     exec sql insert into akdauftragposchang (DATUM,KDAUFTRAGPOSCHANGE_LISTE_390) values ( :Datum, :d );
     ERROR_MLD( "insert akdauftragposchang" )
    
     exec sql execute Dkdauftragposchange;
     ERROR_MSG( "execute Dkdauftragposchange" );
     z->DelKdauftragposchange++;
     }

  return OK;
}

/***** DELETE-KDAUFTRAG-POSRECHART *************************************************/

static int DeleteKdauftragPosRechart( Nummer *num, struct ZAEHLER *z )
{
  exec sql begin declare section;
  kdauftrposrechartS d;
  int Datum;
  exec sql end declare section;
  char *fun = "DeleteKdauftragPosRechart";

  d.KDAUFTRAGNR = num->KdNr;
  Datum = num->Datum;
  exec sql open Ckdauftragposrechart using :d.KDAUFTRAGNR;
  ERROR_MSG( "open Ckdauftragposrechart" )

  for( ;; )
     {
     exec sql fetch Ckdauftragposrechart into :d;
     ERROR_MSG( "fetch Ckdauftragposrechart" )
     if ( NOT_FOUND )
	break;

     exec sql insert into akdauftrposrechart (DATUM,KDAUFTRPOSRECHART_LISTE_390) values ( :Datum, :d );
     ERROR_MLD( "insert akdauftragposrechart" )
    
     exec sql execute Dkdauftragposrechart;
     ERROR_MSG( "execute Dkdauftragposrechart" );
     z->DelKdauftragposrechart++;
     }

  return OK;
}

/***** DELETE-KDAUFTRAG-POSPROMO *************************************************/

static int DeleteKdauftragPosPromo( Nummer *num, struct ZAEHLER *z )
{
  exec sql begin declare section;
  kdauftragpospromoS d;
  int Datum;
  exec sql end declare section;
  char *fun = "DeleteKdauftragPosPromo";

  d.KDAUFTRAGNR = num->KdNr;
  Datum = num->Datum;
  exec sql open Ckdauftragpospromo using :d.KDAUFTRAGNR;
  ERROR_MSG( "open Ckdauftragpospromo" )

  for( ;; )
     {
     exec sql fetch Ckdauftragpospromo into :d;
     ERROR_MSG( "fetch Ckdauftragpospromo" )
     if ( NOT_FOUND )
	break;

     exec sql insert into akdauftragpospromo (DATUM,KDAUFTRAGPOSPROMO_LISTE_390) values ( :Datum, :d );
     ERROR_MLD( "insert akdauftragpospromo" )
    
     exec sql execute Dkdauftragpospromo;
     ERROR_MSG( "execute Dkdauftragpospromo" );
     z->DelKdauftragposPromo++;
     }

  return OK;
}

/***** DELETE-KDAUFTRAG-POSREFUND *************************************************/

static int DeleteKdauftragPosRefund( Nummer *num, struct ZAEHLER *z )
{
  exec sql begin declare section;
  kdauftragposrefundS d;
  int Datum;
  exec sql end declare section;
  char *fun = "DeleteKdauftragPosRefund";

  d.KDAUFTRAGNR = num->KdNr;
  Datum = num->Datum;
  exec sql open Ckdauftragposrefund using :d.KDAUFTRAGNR;
  ERROR_MSG( "open Ckdauftragposrefund" )

  for( ;; )
     {
     exec sql fetch Ckdauftragposrefund into :d;
     ERROR_MSG( "fetch Ckdauftragposrefund" )
     if ( NOT_FOUND )
	break;

     exec sql insert into akdauftragposrefun (DATUM,KDAUFTRAGPOSREFUND_LISTE_390) values ( :Datum, :d );
     ERROR_MLD( "insert akdauftragposrefun" )
    
     exec sql execute Dkdauftragposrefund;
     ERROR_MSG( "execute Dkdauftragposrefund" );
     z->DelKdauftragposrefund++;
     }

  return OK;
}

/***** DELETE-KDAUFTRAG-POSXML *************************************************/

static int DeleteKdauftragPosXml( Nummer *num, struct ZAEHLER *z )
{
  exec sql begin declare section;
  kdauftragposxmlS d;
  int Datum;
  exec sql end declare section;
  char *fun = "DeleteKdauftragPosXml";

  d.KDAUFTRAGNR = num->KdNr;
  Datum = num->Datum;
  exec sql open Ckdauftragposxml using :d.KDAUFTRAGNR;
  ERROR_MSG( "open Ckdauftragposxml" )

  for( ;; )
     {
     exec sql fetch Ckdauftragposxml into :d;
     ERROR_MSG( "fetch Ckdauftragposxml" )
     if ( NOT_FOUND )
	break;

     exec sql insert into akdauftragposxml (DATUM,KDAUFTRAGPOSXML_LISTE_390) values ( :Datum, :d );
     ERROR_MLD( "insert akdauftragposxml" )
    
     exec sql execute Dkdauftragposxml;
     ERROR_MSG( "execute Dkdauftragposxml" );
     z->DelKdauftragposxml++;
     }

  return OK;
}

/***** DELETE-KDAUFTRAG-POSEREIGNIS *************************************************/

static int DeleteKdauftragPosEreignis( Nummer *num, struct ZAEHLER *z )
{
  exec sql begin declare section;
  kdauftragposereignisS d;
  int Datum;
  exec sql end declare section;
  char *fun = "DeleteKdauftragPosEreignis";

  d.KDAUFTRAGNR = num->KdNr;
  Datum = num->Datum;
  exec sql open Ckdauftragposereignis using :d.KDAUFTRAGNR;
  ERROR_MSG( "open Ckdauftragposereignis" )

  for( ;; )
     {
     exec sql fetch Ckdauftragposereignis into :d;
     ERROR_MSG( "fetch Ckdauftragposereignis" )
     if ( NOT_FOUND )
	break;

     exec sql insert into akdauftragposereignis (DATUM_RECHNUNG, KDAUFTRAGPOSEREIGNIS_LISTE_390) values ( :Datum, :d );
     ERROR_MLD( "insert akdauftragposereignis" )
    
     exec sql execute Dkdauftragposereignis;
     ERROR_MSG( "execute Dkdauftragposereignis" );
     z->DelKdauftragposereignis++;
     }

  return OK;
}

/***** DELETE-KDAUFTRAG-POSTOUR *************************************************/

static int DeleteKdauftragPosTour( Nummer *num, struct ZAEHLER *z )
{
  exec sql begin declare section;
  kdauftragpostourS d;
  int Datum;
  exec sql end declare section;
  char *fun = "DeleteKdauftragPosTour";

  d.KDAUFTRAGNR = num->KdNr;
  Datum = num->Datum;
  exec sql open Ckdauftragpostour using :d.KDAUFTRAGNR;
  ERROR_MSG( "open Ckdauftragpostour" )

  for( ;; )
     {
     exec sql fetch Ckdauftragpostour into :d;
     ERROR_MSG( "fetch Ckdauftragpostour" )
     if ( NOT_FOUND )
	break;

     exec sql insert into akdauftragpostour (DATUM, KDAUFTRAGPOSTOUR_LISTE_390) values ( :Datum, :d );
     ERROR_MLD( "insert akdauftragpostour" )
    
     exec sql execute Dkdauftragpostour;
     ERROR_MSG( "execute Dkdauftragpostour" );
     z->DelKdauftragpostour++;
     }

  return OK;
}

/***** DELETE-KDAUFTRAG-PARTNER-FUNCTION *************************************************/

static int DeleteKdauftragPartnerFunction( Nummer* num, struct ZAEHLER* z )
{
	exec sql begin declare section;
	kdauftragpartnerfunctionS d;
	int Datum;
	exec sql end declare section;
	char* fun = "DeleteKdauftragPartnerFunction";

	d.KDAUFTRAGNR = num->KdNr;
	Datum = num->Datum;
	exec sql open Ckdauftragpartnerfunction using :d.KDAUFTRAGNR;
	ERROR_MSG("open Ckdauftragpartnerfunction")

	for (;; )
	{
		exec sql fetch Ckdauftragpartnerfunction into :d;
		ERROR_MSG("fetch Ckdauftragpartnerfunction")
		if (NOT_FOUND)
			break;

		exec sql insert into akdauftragpartnerfunction(DATUM, KDAUFTRAGPARTNERFUNCTION_LISTE_390) values( :Datum, :d );
		ERROR_MLD("insert akdauftragpartnerfunction")

		exec sql execute Dkdauftragpartnerfunction;
		ERROR_MSG("execute Dkdauftragpartnerfunction");
		z->DelKdauftragpartnerfunction++;
	}

	return OK;
}

/***** DELETE-KDAUFTRAG-WERTE *************************************************/

static int DeleteKdauftragWerte( Nummer *num, struct ZAEHLER *z )
{
  exec sql begin declare section;
  kdauftragwerteS d;
  int Datum;
  exec sql end declare section;
  char *fun = "DeleteKdauftragWerte";

  d.KDAUFTRAGNR = num->KdNr;
  Datum = num->Datum;
  exec sql open Ckdauftragwerte using :d.KDAUFTRAGNR;
  ERROR_MSG( "open Ckdauftragwerte" )

  for( ;; )
     {
     exec sql fetch Ckdauftragwerte into :d;
     ERROR_MSG( "fetch Ckdauftragwerte" )
     if ( NOT_FOUND )
	break;

     exec sql insert into akdauftragwerte (DATUM,KDAUFTRAGWERTE_LISTE_390) values ( :Datum, :d );
     ERROR_MLD( "insert akdauftragwerte" )
    
     exec sql execute Dkdauftragwerte;
     ERROR_MSG( "execute Dkdauftragwerte" );
     z->DelKdauftragWerte++;
     }

  return OK;
}

/***** DELETE-ORDER-RELATION-NOs *************************************************/

static int DeleteOrderRelationNo( Nummer *num, struct ZAEHLER *z )
{
  exec sql begin declare section;
  orderrelationnoS d;
  int Datum;
  exec sql end declare section;
  char *fun = "DeleteOrderRelationNo";

  d.CSCORDERNO = num->KdNr;
  Datum = num->Datum;
  exec sql open Corderrelationno using :d.CSCORDERNO;
  ERROR_MSG( "open Corderrelationno" )

  for( ;; )
     {
     exec sql fetch Corderrelationno into :d;
     ERROR_MSG( "fetch Corderrelationno" )
     if ( NOT_FOUND )
	break;

     exec sql insert into aorderrelationno (DATE,ORDERRELATIONNO_LISTE_390) values ( :Datum, :d );
     ERROR_MLD( "insert aorderrelationno" )
    
     exec sql execute Dorderrelationno;
     ERROR_MSG( "execute Dorderrelationno" );
     z->DelOrderRelationNo++;
     }

  return OK;
}

/***** DELETE-KDAUFTRAG-RECHART *************************************************/

static int DeleteKdauftragRechart( Nummer *num, struct ZAEHLER *z )
{
  exec sql begin declare section;
  kdauftragrechartS d;
  int Datum;
  exec sql end declare section;
  char *fun = "DeleteKdauftragRechart";

  d.KDAUFTRAGNR = num->KdNr;
  Datum = num->Datum;
  exec sql open Ckdauftragrechart using :d.KDAUFTRAGNR;
  ERROR_MSG( "open Ckdauftragrechart" )

  for( ;; )
     {
     exec sql fetch Ckdauftragrechart into :d;
     ERROR_MSG( "fetch Ckdauftragrechart" )
     if ( NOT_FOUND )
	break;

     exec sql insert into akdauftragrechart (DATUM,KDAUFTRAGRECHART_LISTE_390) values ( :Datum, :d );
     ERROR_MLD( "insert akdauftragrechart" )
    
     exec sql execute Dkdauftragrechart;
     ERROR_MSG( "execute Dkdauftragrechart" );
     z->DelKdauftragRechart++;
     }

  return OK;
}

/***** DELETE-KDAUFTRAG-DEBTREL *************************************************/

static int DeleteKdauftragDebtrel( Nummer *num, struct ZAEHLER *z )
{
  exec sql begin declare section;
  kdauftragdebtrelS d;
  int Datum;
  exec sql end declare section;
  char *fun = "DeleteKdauftragDebtrel";

  d.KDAUFTRAGNR = num->KdNr;
  Datum = num->Datum;
  exec sql open Ckdauftragdebtrel using :d.KDAUFTRAGNR;
  ERROR_MSG( "open Ckdauftragdebtrel" )

  for( ;; )
     {
     exec sql fetch Ckdauftragdebtrel into :d;
     ERROR_MSG( "fetch Ckdauftragdebtrel" )
     if ( NOT_FOUND )
	break;

     exec sql insert into akdauftragdebtrel (DATUM,KDAUFTRAGDEBTREL_LISTE_390) values ( :Datum, :d );
     ERROR_MLD( "insert akdauftragdebtrel" )
    
     exec sql execute Dkdauftragdebtrel;
     ERROR_MSG( "execute Dkdauftragdebtrel" );
     z->DelKdauftragDebtrel++;
     }

  return OK;
}

/***** DELETE-KDAUFTRAG-DISCACC *************************************************/

static int DeleteKdauftragDiscacc( Nummer *num, struct ZAEHLER *z )
{
  exec sql begin declare section;
  kdauftragdiscaccS d;
  int Datum;
  exec sql end declare section;
  char *fun = "DeleteKdauftragDiscacc";

  d.KDAUFTRAGNR = num->KdNr;
  Datum = num->Datum;
  exec sql open Ckdauftragdiscacc using :d.KDAUFTRAGNR;
  ERROR_MSG( "open Ckdauftragdiscacc" )

  for( ;; )
     {
     exec sql fetch Ckdauftragdiscacc into :d;
     ERROR_MSG( "fetch Ckdauftragdiscacc" )
     if ( NOT_FOUND )
	break;

     exec sql insert into akdauftragdiscacc (DATUM,KDAUFTRAGDISCACC_LISTE_390) values ( :Datum, :d );
     ERROR_MLD( "insert akdauftragdiscacc" )
    
     exec sql execute Dkdauftragdiscacc;
     ERROR_MSG( "execute Dkdauftragdiscacc" );
     z->DelKdauftragDiscacc++;
     }

  return OK;
}

/***** DELETEKDAUFTRAGEREIGNIS **********************************************/

static int DeleteKdauftragEreignis( int KdNr, struct ZAEHLER *z )
{
  exec sql begin declare section;
  kdauftragereignisS d;
  int Datum = 0;
  exec sql end declare section;

  char *fun = "DeleteKdauftragEreignis";

  d.KDAUFTRAGNR = KdNr;

	exec sql open CDatum using :d.KDAUFTRAGNR;
	ERROR_MSG( "open CDatum" )
	exec sql fetch CDatum into :Datum;
	ERROR_MSG( "fetch CDatum" )
	if ( NOT_FOUND )	/* darf eigentlich nicht sein */
	{
		Datum = AllgGetDate();
	}

  exec sql open Ckdauftragerg using :d.KDAUFTRAGNR;
  ERROR_MSG( "open Ckdauftragerg" )

  for(;; )
     {
     exec sql fetch Ckdauftragerg into :d;
     ERROR_MSG( "fetch Ckdauftragerg" )
     if ( NOT_FOUND )
	break;
    
/*     if ( d.EREIGNISART == 11 || d.EREIGNISART == 9 )
	Datum = d.DATUM;	*/

	 exec sql insert into akdauftragereignis ( DATUM_RECHNUNG,KDAUFTRAGEREIGNIS_LISTE_390 ) values ( :Datum, :d );
     ERROR_MLD( "insert akdauftragereignis" );

     exec sql execute Dkdauftragerg;
     ERROR_MSG( "execute Dkdauftragerg" );
     z->DelKdauftragEreignis++;
     }

  return Datum;
}

/***** DELETEKDAUFTRAGBEM ***************************************************/

static int DeleteKdauftragBem( Nummer *num, struct ZAEHLER *z )
{
  exec sql begin declare section;
  kdauftragbemS d;
  int Datum;
  exec sql end declare section;

  char *fun = "DeleteKdauftragBem";

  d.KDAUFTRAGNR = num->KdNr;
  Datum = num->Datum;
  exec sql open Ckdauftragbem using :d.KDAUFTRAGNR;
  ERROR_MSG( "open Ckdauftragbem" )

  for( ;; )
     {
     exec sql fetch Ckdauftragbem into :d;
     ERROR_MSG( "fetch Ckdauftragbem" )
     if ( NOT_FOUND )
	break;
    
     exec sql insert into akdauftragbem (DATUM,KDAUFTRAGBEM_LISTE_390) values( :Datum, :d );
     ERROR_MLD( "insert into akdauftragbem" )

     exec sql execute Dkdauftragbem;
     ERROR_MSG( "execute Dkdauftragbem" );
     z->DelKdauftragBem++;
     }

  return OK;
}

/***** DELETE-DISPO-ARTIKEL *************************************************/

static int DeleteDispoArtikel( Nummer *num, struct ZAEHLER *z )
{
  exec sql begin declare section;
  dispoartikelS d;
  int Datum;
  exec sql end declare section;

  char *fun = "DeleteDispoArtikel";

  d.KDAUFTRAGNR = num->KdNr;
  Datum = num->Datum;
  exec sql open Cdispoartikel using :d.KDAUFTRAGNR;
  ERROR_MSG( "open Cdispoartikel" )

  for( ;; )
     {
     exec sql fetch Cdispoartikel into :d;
     ERROR_MSG( "fetch Cdispoartikel" )
     if ( NOT_FOUND )
	break;
    
     exec sql insert into adispoartikel (DATUM,DISPOARTIKEL_LISTE_390) values ( :Datum, :d );
     ERROR_MLD( "insert into adispoartikel" );

     exec sql execute Ddispoartikel;
     ERROR_MSG( "execute Ddispoartikel" );
     z->DelDispoArtikel++;
     }

  return OK;
}

/***** DELETE-KOEINHEIT *****************************************************/

static int DeleteKoeinheit( Nummer *num, struct ZAEHLER *z )
{
  exec sql begin declare section;
  akoeinheitS d;
  exec sql end declare section;

  char *fun = "DeleteKoeinheit";

  d.KDAUFTRAGNR = num->KdNr;	  
  exec sql open Ckoeinheit using :d.KDAUFTRAGNR;
  ERROR_MSG( "open Ckoeinheit" )

  for( ;; )
  {
     exec sql fetch Ckoeinheit into :d;
     ERROR_MSG( "fetch Ckoeinheit" )
     if ( NOT_FOUND )
      	break;
    
     d.DATUM = num->Datum;
     exec sql insert into akoeinheit values ( :d );
     ERROR_MLD( "insert into akoeinheit" );

     exec sql execute Dkoeinheit;
     ERROR_MSG( "execute Dkoeinheit" );
     z->DelKoeinheit++;
     }

  return OK;
}

/***** DELETE-NACHLIEFERPOS *************************************************/

static int DeleteNachlieferpos(const long lDate, struct ZAEHLER *z )
{
  exec sql begin declare section;
  const long Datum = lDate;
  exec sql end declare section;
  int i = 0;

  char *fun = "DeleteDispoArtikel";

  exec sql open Cnachlieferpos using :Datum;
  ERROR_MSG( "open Cnachlieferpos" )

  exec sql begin work;
  for( ;; )
  {
	 if ( (++i % 500) == 0 )
        Commit( fun );
     exec sql fetch Cnachlieferpos;
     ERROR_MSG( "fetch Cnachlieferpos" )
     if ( NOT_FOUND )
      	break;
    
     exec sql execute Dnachlieferpos;
     ERROR_MSG( "execute Dnachlieferpos" );
     z->DelNachlieferPos++;
     }

  exec sql commit work;
  return OK;
}

/***** UPDATE-NUMMER ********************************************************/

static int UpdateNummer( struct ZAEHLER *z )
{
  exec sql begin declare section;
  long lCountAuftrag;
  exec sql end declare section;

  char *fun = "UpdateNummer";
	int rc;
  int i = 0;
 
  exec sql select count(*) into :lCountAuftrag from kdauftrag;
  ERROR_MSG( "select count(*)" )

/* Nur der letzte Löschlauf darf ds Nummernobjekt auf 0 setzten! */
  if ( lCountAuftrag > 0 )
     return OK;
 
  exec sql open Cnummer;
  ERROR_MSG( "open Cnummer" )

  for( ;; )
    {
    if ( i == 0 )
       Commit( fun );
       
    exec sql fetch Cnummer;
    ERROR_MSG( "fetch Cnummer" )
    if ( NOT_FOUND ) 
       {
      exec sql commit work;
      break;
       }
    else if ( i >= MAX_TRANSAKTION )
      i = 0;
    
     exec sql execute Unummer;
    ERROR_MSG( "execute Unummer" );
     z->UpdNummer++;
     }

	if ((rc = ReaktiviereAuftrag( z )) != OK) return rc;

  return OK;
}

/***** HOLE-HAUSNR **********************************************************/

int HoleHausNr( char* spDB, const int *iFilialNr, int *HausNr )
{
  exec sql begin declare section;
  int filialnr;
  char* spDatabase = spDB;
  exec sql end declare section;
  
  char *fun = "HoleHausNr";
  
  if ( spDB == NULL )
  { 
	  exec sql database DATABASE;
  }
  else
  {
	  exec sql database :spDatabase;
  }
  ERROR_MSG( "Fehler oeffnen DB" )

  exec sql set lock mode to wait 20;
  ERROR_MSG( "Set LockMode to Wait" )

  exec sql set isolation to dirty read;
  ERROR_MSG( "Set Isolation to Dirty Read" )
 
  *HausNr = *iFilialNr; 
  
  return SQLCODE;
}

/***** DELETE-KOAUFTRAG *****************************************************/

static int DeleteKoauftrag( struct ZAEHLER *z )
{
  char *fun = "DeleteKoauftrag";
  int i = 0;

  exec sql open Ckoauftrag;
  ERROR_MSG( "open Ckoauftrag" )

  for( ;; )
  {
    if ( i == 0 )
      Commit( fun );

    exec sql fetch Ckoauftrag;
    ERROR_MSG( "fetch Ckoauftrag" )
    if ( NOT_FOUND ) 
    {
      exec sql commit work;
      break;
    }
    else if ( i >= MAX_TRANSAKTION )
      i = 0;
    
    exec sql execute Dkoauftrag;
    ERROR_MSG( "execute Dkoauftrag" );
    z->DelKoauftrag++;
  }

  return OK;
}

/***** DELETE-KOEINHEIT *****************************************************/

static int DeleteKoeinheitAll( struct ZAEHLER *z )
{
  char *fun = "DeleteKoeinheitAll";

  Commit( fun );

  exec sql delete from koeinheit;
  ERROR_MSG( "delete koeinheit" )
  z->DelKoeinheit += sqlca.sqlerrd[2];
  return OK;
}

/***** PRINT-MSG ************************************************************/

 void PrintMsg( char *fun, char *error_msg, char mld )
 {
	 static int fst = 1;
   FILE *fp;
   struct tm *localtime();
   struct tm *zeit;
   long hour1;
   pid_t pid;
   long time();
   char logFile[L_TEXT];
  
   pid = getpid();
   hour1 = time( &hour1 );
   zeit  = localtime( &hour1 );

   sprintf( logFile, "%s/tpldauftr.log", (char *)getenv( "LOG_PATH" ) );
   if ( ( fp = fopen( logFile, "a" ) ) == (FILE *)0 )
      return;

   fprintf( fp, "%c %.2d %02d.%02d.%02d %02d:%02d:%02d "
               "pid=%05ld %.8s %s %s->%d/%d\n",
            mld,
            HausNr,
            zeit->tm_mday,
            zeit->tm_mon + 1,
            (zeit->tm_year+1900)%100,
            zeit->tm_hour,
            zeit->tm_min,
            zeit->tm_sec,
            pid,
            "tpldauftr",
            fun,
            error_msg,
         SQLCODE,
         SQLISAM );

   fclose(fp);
}

/***** COMMIT ***************************************************************/

static int Commit( char *fun )
{
  exec sql commit work;
  exec sql begin work;
  ERROR_MSG( "begin work" );
  return OK;
}

/***** DELETE-OLD ***********************************************************/

static int DeleteOld( const int iNumberOfDay )
{
  struct ZAEHLER z = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };	        /* initialize */
  timeval_t timev_s;
  timeStr   *time_d;
  long lDate;
  char *fun = "DeleteOld";

  DEBUG_SECTION
	  PrintMsg(fun, "wurde aufgerufen", HINWEIS);
  END_DEBUG_SECTION

	gettimeofday( &timev_s , NULL );
  timev_s.tv_sec = timev_s.tv_sec - ( 24 * 60 * 60 * iNumberOfDay );
                                        /*7776000 == 90 Tage in Sec         */
  time_d = (timeStr *)TimeOfDay( timev_s.tv_sec );
  sprintf( str, "%04d%02d%02d", time_d->year, time_d->mon, time_d->day );
  
  lDate = atol( str );
  DEBUG_SECTION
	  PrintMsg(fun, str, HINWEIS);
  END_DEBUG_SECTION

/*  DeleteAkdauftragZusatz( lDate, &z );
*/	DeleteAkdauftrag( lDate, &z );

  DeleteAkoeinheit( lDate, &z );
  DeleteNachlieferpos( lDate, &z );
  DeleteAkdverbund( lDate, &z );
  DeleteStockentry( lDate, &z );
  DeleteAcststockreserve( lDate, &z );

if (isDE == YES)
{
  DeleteToteInfo( lDate, &z );
}

  DeleteDocumentPrintInfo(lDate, &z);

  sprintf( str, "Aelter %02d.%02d.%04d(Kopf/Debtrel/Rechart/Discacc/Zus/Pos/Rab/Charge/PosRechart/PosPromo/Refund/Xml/PosEreignis/PosTour/Bem/Erg/Dis/Nal/Vb/Vbp/StE/Res/Werte/Change/Prolink/VBPosRab/OrderRemarks/OrderPositionDiscount/NewIBT(OrderRelationNo)/CscOrderFlags/ToteInfo/CscOrderPosSplittInfo/CscOrderIBTPickingData/DocumentPrintInfo:%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d",
			time_d->day,
			time_d->mon,
			time_d->year,
			z.DelKdauftrag,
			z.DelKdauftragDebtrel,
			z.DelKdauftragRechart,
			z.DelKdauftragDiscacc,
			z.DelKdauftragZusatz,
			z.DelKdauftragPos,
			z.DelKdauftragposrab,
			z.DelKdauftragposcharge,
			z.DelKdauftragposrechart,
			z.DelKdauftragposPromo,
			z.DelKdauftragposrefund,
			z.DelKdauftragposxml,
			z.DelKdauftragposereignis,
			z.DelKdauftragpostour,
			z.DelKdauftragpartnerfunction,
			z.DelKdauftragBem,
			z.DelKdauftragEreignis,
			z.DelDispoArtikel,
			z.DelNachlieferPos,
			z.DelKdverbund,
			z.DelKdverbundPos,
			z.DelStockentry,
			z.DelAcststockreserve,
			z.DelKdauftragWerte,
			z.DelKdauftragposchange,
			z.DelKdauftragProlink,
			z.DelKdverbundPosRab,
			z.DelOrderRemarks,
			z.DelOrderPositionDiscount,
			z.DelNewIBT,
			z.DelOrderRelationNo,
			z.DelCscOrderFlags,
			z.DelToteInfo,
			z.DelCscOrderPosSplittInfo,
			z.DelCscOrderIBTPickingData,
			z.DelDocumentPrintInfo);

  PrintMsg( fun, str, HINWEIS );
  return OK;
}  

static int GetCSVImportFolder()
{
	
	char *fun = "GetCSVImportFolder";
	char *error_msg;

	exec sql select auspraegung INTO :folderpath FROM parameter WHERE programmname = 'KSC' and zweck = 'CSVIMPORTSERVER';
	ERROR_MSG( "from parameter" );
	if (NOT_FOUND) return ERROR;

	return OK;
}

static char *trimwhitespace(char *str)
{
	char *end;

    // Trim leading space
	while(isspace((unsigned char)*str)) str++;

	if(*str == 0)  // All spaces?
	return str;

	// Trim trailing space
	end = str + strlen(str) - 1;
	while(end > str && isspace((unsigned char)*end)) end--;

	// Write new null terminator character
	end[1] = '\0';
	return str;

}

/***** DELETE-OLD CSV***********************************************************/
static int DeleteOldCSV( const int iNumberOfDay )
{
	char *fun = "DeleteOldCSV";
	char meld[81];
    int rc;
    char szCommand[512];
    char ausgabe[101];

    timeval_t timev_s;
    timeStr   *time_DueDate,*time_FileDate;
    long lDueDate;
    long lFileDate;

	DEBUG_SECTION
		PrintMsg(fun, "wurde aufgerufen", HINWEIS);
	END_DEBUG_SECTION

	if( GetCSVImportFolder() != OK )
	{
       return ERROR;
	}
	DEBUG_SECTION
		PrintMsg(fun, "Importfolder gelesen", HINWEIS);
	END_DEBUG_SECTION

    gettimeofday( &timev_s , NULL );
    timev_s.tv_sec = timev_s.tv_sec - ( 24 * 60 * 60 * iNumberOfDay ); /*7776000 == 90 Tage in Sec         */
                                
    time_DueDate = (timeStr *)TimeOfDay( timev_s.tv_sec );
    sprintf( str, "%04d%02d%02d", time_DueDate->year, time_DueDate->mon, time_DueDate->day );
    lDueDate = atol( str );

	DEBUG_SECTION
		PrintMsg(fun, str, HINWEIS);
	END_DEBUG_SECTION

   
    DIR *dirp;
    static struct dirent *direntp;
    char *fpath;
    fpath = trimwhitespace(folderpath);

	DEBUG_SECTION
		PrintMsg(fun, fpath, HINWEIS);
	END_DEBUG_SECTION

    if((dirp = opendir( fpath ) ) == NULL)
    {
        sprintf( ausgabe," opendir fehler; rc = %d",errno);
        PrintMsg( meld, ausgabe, FEHLER );
        return 1;
    }
    
    while ((direntp = readdir(dirp)) != NULL)
    {
        char file_name[2048];
        struct stat attr;
        struct tm * time_;

		DEBUG_SECTION
			PrintMsg(fun, direntp->d_name, HINWEIS);
		END_DEBUG_SECTION

		if (strncmp(direntp->d_name, "CSV",3))
		{
			continue;
		}
		sprintf(file_name, "%s%s", folderpath, direntp->d_name);

        stat(file_name, &attr);

        time_FileDate = (timeStr *)TimeOfDay(attr.st_mtime);
        sprintf(str, "%04d%02d%02d", time_FileDate->year, time_FileDate->mon, time_FileDate->day);
        lFileDate = atol(str);

		DEBUG_SECTION
			PrintMsg(fun, file_name, HINWEIS);
		END_DEBUG_SECTION

        if (lDueDate >= lFileDate)
        {
//			sprintf(szCommand, "rm -f %s", file_name);
//			if ((rc = h_system(szCommand)) < 0)
			if ((rc = remove(file_name)) < 0)
            {
                sprintf(ausgabe, " Loeschen der Datei %s nicht moeglich; rc = %d", file_name, rc);
                PrintMsg(meld, ausgabe, FEHLER);
            }

			DEBUG_SECTION
				PrintMsg(fun, "geloescht", HINWEIS);
			END_DEBUG_SECTION
		}
	}
    
   return OK;

}

/***** DELETE-AKDAUFTRAG ****************************************************/

static int DeleteAkdauftrag( long date, struct ZAEHLER *z )
  {
  exec sql begin declare section;
  long datum;
  long KdauftragNr;
  exec sql end declare section;

  int i = 0;
  char *fun = "DeleteAkdauftrag";

  datum = date;
  exec sql open CAkdauftrag using :datum;
  ERROR_MSG( "open CAkdauftrag" )

  
  exec sql begin work;
  for( ;; )
     {
     i++;
	 if ( i % 5 == 0 )
        Commit( fun );
     
	 exec sql fetch CAkdauftrag into :datum, :KdauftragNr;
     ERROR_MSG( "fetch CAkdauftrag" )
     if ( NOT_FOUND )
    	break;

	 DeleteAnewIBT( datum, KdauftragNr, z );
     DeleteAkdauftragPos( datum, KdauftragNr, z );
     DeleteAkdauftragPosRab( datum, KdauftragNr, z );
     DeleteAkdauftragPosCharge( datum, KdauftragNr, z );
     DeleteAkdauftragPosChange( datum, KdauftragNr, z );
     DeleteAkdauftragPosRechart( datum, KdauftragNr, z );
     DeleteAkdauftragPosPromo( datum, KdauftragNr, z );
	 DeleteAkdauftragPosRefund( datum, KdauftragNr, z );
	 DeleteAkdauftragPosXml( datum, KdauftragNr, z );
	 DeleteAkdauftragPosEreignis( datum, KdauftragNr, z );
	 DeleteAkdauftragPosTour( datum, KdauftragNr, z );
	 DeleteAkdauftragPartnerFunction( datum, KdauftragNr, z );
     DeleteAkdauftragBem( datum, KdauftragNr, z );
     DeleteAkdauftragEreignis( datum, KdauftragNr, z );
     DeleteAdispoArtikel( datum, KdauftragNr, z ); 
     DeleteAkdauftragWerte( datum, KdauftragNr, z );
     DeleteAOrderRelationNo( datum, KdauftragNr, z );
     DeleteAkdauftragProlink( datum, KdauftragNr, z );
	 DeleteAkdauftragRechart( datum, KdauftragNr, z );
	 DeleteAkdauftragDebtrel( datum, KdauftragNr, z );
	 DeleteAkdauftragDiscacc( datum, KdauftragNr, z );
	 DeleteAorderRemarks( datum, KdauftragNr, z );
	 DeleteAorderPositionDiscount( datum, KdauftragNr, z );
	 DeleteAcscOrderFlags( datum, KdauftragNr, z );
    
     exec sql execute DAkdauftrag;
     ERROR_MSG( "execute DAkdauftrag" );
     z->DelKdauftrag++;
     }
  exec sql commit work;

  return OK;
}

/***** DELETE-AKDAUFTRAG-ZUSATZ *********************************************/

static int DeleteAkdauftragZusatz( long date, struct ZAEHLER *z )
  {
  exec sql begin declare section;
  long datum;
  exec sql end declare section;

  int i = 0;
  char *fun = "DeleteAkdauftragZusatz";

  datum = date;
  exec sql open CAkdauftragzus using :datum;
  ERROR_MSG( "open CAkdauftragzus" )

  
  exec sql begin work;
  for( ;; )
     {
     i++;
	 if ( i % 500 == 0 )
        Commit( fun );
     
	 exec sql fetch CAkdauftragzus;
     ERROR_MSG( "fetch CAkdauftragzus" )
     if ( NOT_FOUND )
    	break;
    
     exec sql execute DAkdauftragzus;
     ERROR_MSG( "execute DAkdauftragzus" );
     z->DelKdauftragZusatz++;
     }
  exec sql commit work;

  return OK;
}

/***** DELETE-AKDAUFTRAGPOS ****************************************************/

static int DeleteAkdauftragPos( long date, long kdnr, struct ZAEHLER *z )
  {
  exec sql begin declare section;
  long datum;
  long kdauftragnr;
  exec sql end declare section;

  char *fun = "DeleteAkdauftragPos";

  datum = date;
  kdauftragnr = kdnr;

  exec sql execute DAkdauftragpos using :datum, :kdauftragnr;
  ERROR_MSG( "execute DAkdauftragpos" );
  z->DelKdauftragPos+= sqlca.sqlerrd[2];
  return OK;
}

/***** DELETE-AKDAUFTRAGPOSRAB ****************************************************/

static int DeleteAkdauftragPosRab( long date, long kdnr, struct ZAEHLER *z )
  {
  exec sql begin declare section;
  long datum;
  long kdauftragnr;
  exec sql end declare section;

  char *fun = "DeleteAkdauftragPosRab";

  datum = date;
  kdauftragnr = kdnr;

  exec sql execute DAkdauftragposrab using :datum, :kdauftragnr;
  ERROR_MSG( "execute DAkdauftragposrab" );
  z->DelKdauftragposrab+= sqlca.sqlerrd[2];
  return OK;
}

/***** DELETE-AKDAUFTRAGPOSCHARGE ****************************************************/

static int DeleteAkdauftragPosCharge( long date, long kdnr, struct ZAEHLER *z )
  {
  exec sql begin declare section;
  long datum;
  long kdauftragnr;
  exec sql end declare section;

  char *fun = "DeleteAkdauftragPosCharge";

  datum = date;
  kdauftragnr = kdnr;

  exec sql execute DAkdauftragposcharge using :datum, :kdauftragnr;
  ERROR_MSG( "execute DAkdauftragposcharge" );
  z->DelKdauftragposcharge += sqlca.sqlerrd[2];
  return OK;
}

/***** DELETE-AKDAUFTRAGPOSCHANGE ****************************************************/

static int DeleteAkdauftragPosChange( long date, long kdnr, struct ZAEHLER *z )
  {
  exec sql begin declare section;
  long datum;
  long kdauftragnr;
  exec sql end declare section;

  char *fun = "DeleteAkdauftragPosChange";

  datum = date;
  kdauftragnr = kdnr;

  exec sql execute DAkdauftragposchange using :datum, :kdauftragnr;
  ERROR_MSG( "execute DAkdauftragposchange" );
  z->DelKdauftragposchange += sqlca.sqlerrd[2];
  return OK;
}

/***** DELETE-AKDAUFTRAGPOSRECHART ****************************************************/

static int DeleteAkdauftragPosRechart( long date, long kdnr, struct ZAEHLER *z )
  {
  exec sql begin declare section;
  long datum;
  long kdauftragnr;
  exec sql end declare section;

  char *fun = "DeleteAkdauftragPosRechart";

  datum = date;
  kdauftragnr = kdnr;

  exec sql execute DAkdauftragposrechart using :datum, :kdauftragnr;
  ERROR_MSG( "execute DAkdauftragposrechart" );
  z->DelKdauftragposrechart += sqlca.sqlerrd[2];
  return OK;
}

/***** DELETE-AKDAUFTRAGPOSPROMO ****************************************************/

static int DeleteAkdauftragPosPromo( long date, long kdnr, struct ZAEHLER *z )
  {
  exec sql begin declare section;
  long datum;
  long kdauftragnr;
  exec sql end declare section;

  char *fun = "DeleteAkdauftragPosPromo";

  datum = date;
  kdauftragnr = kdnr;

  exec sql execute DAkdauftragpospromo using :datum, :kdauftragnr;
  ERROR_MSG( "execute DAkdauftragpospromo" );
  z->DelKdauftragposPromo += sqlca.sqlerrd[2];
  return OK;
}

/***** DELETE-AKDAUFTRAGPOSREFUND ****************************************************/

static int DeleteAkdauftragPosRefund( long date, long kdnr, struct ZAEHLER *z )
  {
  exec sql begin declare section;
  long datum;
  long kdauftragnr;
  exec sql end declare section;

  char *fun = "DeleteAkdauftragPosRefund";

  datum = date;
  kdauftragnr = kdnr;

  exec sql execute DAkdauftragposrefund using :datum, :kdauftragnr;
  ERROR_MSG( "execute DAkdauftragposrefund" );
  z->DelKdauftragposrefund += sqlca.sqlerrd[2];
  return OK;
}

/***** DELETE-AKDAUFTRAGPOSXML ****************************************************/

static int DeleteAkdauftragPosXml( long date, long kdnr, struct ZAEHLER *z )
  {
  exec sql begin declare section;
  long datum;
  long kdauftragnr;
  exec sql end declare section;

  char *fun = "DeleteAkdauftragPosXml";

  datum = date;
  kdauftragnr = kdnr;

  exec sql execute DAkdauftragposxml using :datum, :kdauftragnr;
  ERROR_MSG( "execute DAkdauftragposxml" );
  z->DelKdauftragposxml += sqlca.sqlerrd[2];
  return OK;
}

/***** DELETE-AKDAUFTRAGPOSEREIGNIS ****************************************************/

static int DeleteAkdauftragPosEreignis( long date, long kdnr, struct ZAEHLER *z )
  {
  exec sql begin declare section;
  long datum;
  long kdauftragnr;
  exec sql end declare section;

  char *fun = "DeleteAkdauftragPosEreignis";

  datum = date;
  kdauftragnr = kdnr;

  exec sql execute DAkdauftragposereignis using :datum, :kdauftragnr;
  ERROR_MSG( "execute DAkdauftragposereignis" );
  z->DelKdauftragposereignis += sqlca.sqlerrd[2];
  return OK;
}

/***** DELETE-AKDAUFTRAGPOSTOUR ****************************************************/

static int DeleteAkdauftragPosTour( long date, long kdnr, struct ZAEHLER *z )
  {
  exec sql begin declare section;
  long datum;
  long kdauftragnr;
  exec sql end declare section;

  char *fun = "DeleteAkdauftragPosTour";

  datum = date;
  kdauftragnr = kdnr;

  exec sql execute DAkdauftragpostour using :datum, :kdauftragnr;
  ERROR_MSG( "execute DAkdauftragpostour" );
  z->DelKdauftragpostour += sqlca.sqlerrd[2];
  return OK;
}

/***** DELETE-AKDAUFTRAGPARTNERFUNCTION ****************************************************/

static int DeleteAkdauftragPartnerFunction( long date, long kdnr, struct ZAEHLER* z )
{
	exec sql begin declare section;
	long datum;
	long kdauftragnr;
	exec sql end declare section;

	char* fun = "DeleteAkdauftragPartnerFunction";

	datum = date;
	kdauftragnr = kdnr;

	exec sql execute DAkdauftragpartnerfunction using :datum, :kdauftragnr;
	ERROR_MSG( "execute DAkdauftragpartnerfunction" );
	z->DelKdauftragpartnerfunction += sqlca.sqlerrd[2];
	return OK;
}

/***** DELETE-AKDAUFTRAGWERTE ****************************************************/

static int DeleteAkdauftragWerte( long date, long kdnr, struct ZAEHLER *z )
  {
  exec sql begin declare section;
  long datum;
  long kdauftragnr;
  exec sql end declare section;

  char *fun = "DeleteAkdauftragWerte";

  datum = date;
  kdauftragnr = kdnr;

  exec sql execute DAkdauftragwerte using :datum, :kdauftragnr;
  ERROR_MSG( "execute DAkdauftragwerte" );
  z->DelKdauftragWerte+= sqlca.sqlerrd[2];
  return OK;
}

/***** DELETE-AORDERRELATIONNOs ****************************************************/

static int DeleteAOrderRelationNo( long date, long kdnr, struct ZAEHLER *z )
  {
  exec sql begin declare section;
  long datum;
  long kdauftragnr;
  exec sql end declare section;

  char *fun = "DeleteAOrderRelationNo";

  datum = date;
  kdauftragnr = kdnr;

  exec sql execute DAOrderRelationNo using :datum, :kdauftragnr;
  ERROR_MSG( "execute DAOrderRelationNo" );
  z->DelOrderRelationNo+= sqlca.sqlerrd[2];
  return OK;
}

/***** DELETE-AKDAUFTRAGRECHART ****************************************************/

static int DeleteAkdauftragRechart( long date, long kdnr, struct ZAEHLER *z )
  {
  exec sql begin declare section;
  long datum;
  long kdauftragnr;
  exec sql end declare section;

  char *fun = "DeleteAkdauftragRechart";

  datum = date;
  kdauftragnr = kdnr;

  exec sql execute DAkdauftragrechart using :datum, :kdauftragnr;
  ERROR_MSG( "execute DAkdauftragrechart" );
  z->DelKdauftragRechart += sqlca.sqlerrd[2];
  return OK;
}

/***** DELETE-AKDAUFTRAGDEBTREL ****************************************************/

static int DeleteAkdauftragDebtrel( long date, long kdnr, struct ZAEHLER *z )
  {
  exec sql begin declare section;
  long datum;
  long kdauftragnr;
  exec sql end declare section;

  char *fun = "DeleteAkdauftragDebtrel";

  datum = date;
  kdauftragnr = kdnr;

  exec sql execute DAkdauftragdebtrel using :datum, :kdauftragnr;
  ERROR_MSG( "execute DAkdauftragdebtrel" );
  z->DelKdauftragDebtrel += sqlca.sqlerrd[2];
  return OK;
}

/***** DELETE-AKDAUFTRAGPROLINK ****************************************************/

static int DeleteAkdauftragProlink( long date, long kdnr, struct ZAEHLER *z )
  {
  exec sql begin declare section;
  long datum;
  long kdauftragnr;
  exec sql end declare section;

  char *fun = "DeleteAkdauftragProlink";

  datum = date;
  kdauftragnr = kdnr;

  exec sql execute DAkdauftragprolink using :datum, :kdauftragnr;
  ERROR_MSG( "execute DAkdauftragprolink" );
  z->DelKdauftragProlink += sqlca.sqlerrd[2];
  return OK;
}

/***** DELETE-AKDAUFTRAGDISCACCT ****************************************************/

static int DeleteAkdauftragDiscacc( long date, long kdnr, struct ZAEHLER *z )
  {
  exec sql begin declare section;
  long datum;
  long kdauftragnr;
  exec sql end declare section;

  char *fun = "DeleteAkdauftragDiscacc";

  datum = date;
  kdauftragnr = kdnr;

  exec sql execute DAkdauftragdiscacc using :datum, :kdauftragnr;
  ERROR_MSG( "execute DAkdauftragdiscacc" );
  z->DelKdauftragDiscacc += sqlca.sqlerrd[2];
  return OK;
}

/***** DELETE-AKDAUFTRAGBEM ****************************************************/

static int DeleteAkdauftragBem( long date, long kdnr, struct ZAEHLER *z )
  {
  exec sql begin declare section;
  long datum;
  long kdauftragnr = kdnr;
  exec sql end declare section;

  char *fun = "DeleteAkdauftragBem";

  datum = date;
  exec sql execute DAkdauftragbem using :datum, :kdauftragnr;
  ERROR_MSG( "execute DAkdauftragbem" );
  z->DelKdauftragBem+= sqlca.sqlerrd[2];
  return OK;
}

/***** DELETE-AKDAUFTRAG-EREIGNIS **********************************************/

static int DeleteAkdauftragEreignis( long date, long kdnr, struct ZAEHLER *z )
{
  exec sql begin declare section;
  long datum;
  long kdauftragnr=kdnr;
  exec sql end declare section;

  char *fun = "DeleteAkdauftragEreignis";

  datum = date;
  exec sql execute DAkdauftragerg using :datum, :kdauftragnr;
  ERROR_MSG( "execute DAkdauftragerg" );
  z->DelKdauftragEreignis+= sqlca.sqlerrd[2];
  return OK;
}

/***** DELETE-AORDERREMARKS **********************************************/

static int DeleteAorderRemarks( long date, long kdnr, struct ZAEHLER *z )
{
  exec sql begin declare section;
  long datum;
  long kdauftragnr=kdnr;
  exec sql end declare section;

  char *fun = "DeleteAorderRemarks";

  datum = date;
  exec sql execute DAorderRemarks using :datum, :kdauftragnr;
  ERROR_MSG( "execute DAorderRemarks" );
  z->DelOrderRemarks+= sqlca.sqlerrd[2];
  return OK;
}

/***** DELETE-ACSCORDERFLAGS **********************************************/

static int DeleteAcscOrderFlags( long date, long kdnr, struct ZAEHLER *z )
{
  exec sql begin declare section;
  long datum;
  long kdauftragnr=kdnr;
  exec sql end declare section;

  char *fun = "DeleteAcscOrderFlags";

  datum = date;
  exec sql execute DAcscOrderFlags using :datum, :kdauftragnr;
  ERROR_MSG( "execute DAcscOrderFlags" );
  z->DelCscOrderFlags+= sqlca.sqlerrd[2];
  return OK;
}

/***** DELETE-ACSCORDERPOSSPLITTINFO **********************************************/

static int DeleteAcscOrderPosSplittInfo(long date, long kdnr, struct ZAEHLER *z)
{
	exec sql begin declare section;
	long datum;
	long kdauftragnr = kdnr;
	exec sql end declare section;

	char *fun = "DeleteAcscOrderPosSplittInfo";

	datum = date;
	exec sql execute DAcscOrderPosSplittInfo using :datum, : kdauftragnr;
	ERROR_MSG("execute DAcscOrderPosSplittInfo");
	z->DelCscOrderPosSplittInfo += sqlca.sqlerrd[2];
	return OK;
}

/***** DELETE-ACSCORDERIBTPICKINGDATA **********************************************/

static int DeleteAcscOrderIBTPickingData(long date, long kdnr, struct ZAEHLER *z)
{
	exec sql begin declare section;
	long datum;
	long kdauftragnr = kdnr;
	exec sql end declare section;

	char *fun = "DeleteAcscOrderIBTPickingData";

	datum = date;
	exec sql execute DAcscOrderIBTPickingData using :datum, : kdauftragnr;
	ERROR_MSG("execute DAcscOrderIBTPickingData");
	z->DelCscOrderIBTPickingData += sqlca.sqlerrd[2];
	return OK;
}

/***** DELETE-AORDERPOSITIONDISCOUNT **********************************************/

static int DeleteAorderPositionDiscount( long date, long kdnr, struct ZAEHLER *z )
{
  exec sql begin declare section;
  long datum;
  long kdauftragnr=kdnr;
  exec sql end declare section;

  char *fun = "DeleteAorderPositionDiscount";

  datum = date;
  exec sql execute DAorderPositionDiscount using :datum, :kdauftragnr;
  ERROR_MSG( "execute DAorderPositionDiscount" );
  z->DelOrderPositionDiscount+= sqlca.sqlerrd[2];
  return OK;
}

/***** DELETE-NEW-DISCOUNT-TABLES **********************************************/

static int DeleteAnewIBT( long date, long kdnr, struct ZAEHLER *z )
{
	exec sql begin declare section;
	long datum;
	long datumVon;
	long datumBis=date;
	long requestID;
	long kdauftragnr=kdnr;
	exec sql end declare section;
	
	char *fun = "DeleteAnewIBT";
	
	datum = date;
	
	exec sql execute SDatumVon into :datumVon using :datum, :kdauftragnr;
	ERROR_MSG( "execute SDatumVon" );
/*	DatumBis ist das datum
	exec sql execute SDatumBis into :datumBis using :datum, :kdauftragnr; 
	ERROR_MSG( "execute SDatumBis" );
	*/
	exec sql open Cibtrequest using :kdauftragnr, :datumVon, :datumBis;
	ERROR_MSG( "open Cibtrequest" );
	for(;;)
	{
		exec sql fetch Cibtrequest into :requestID;
		ERROR_MSG( "fetch Cibtrequest" );
		if( NOT_FOUND ) break;

		exec sql execute Dibtrequest;
		ERROR_MSG( "execute Dibtrequest" );
		exec sql execute Dibtdiscountrequest using :requestID;
		ERROR_MSG( "execute Dibtdiscountrequest" );
		exec sql execute Dibtremarkrequest using :requestID;
		ERROR_MSG( "execute Dibtremarkrequest" );
		exec sql execute Dibtresponse using :requestID;
		ERROR_MSG( "execute Dibtresponse" );

		z->DelNewIBT++;
	}
	return OK;
}

/***** DELETE-ADISPO-ARTIKEL ************************************************/

static int DeleteAdispoArtikel( long date, long kdnr, struct ZAEHLER *z )
  {
  exec sql begin declare section;
  long datum;
  long kdauftragnr = kdnr;
  exec sql end declare section;

  char *fun = "DeleteAdispoArtikel";

  datum = date;
  exec sql execute DAdispoartikel using :datum, :kdauftragnr;
  ERROR_MSG( "execute DAdispoartikel" );
  z->DelDispoArtikel+= sqlca.sqlerrd[2];

  return OK;
}

/***** DELETE-AKOEINHEIT ****************************************************/

static int DeleteAkoeinheit( long date, struct ZAEHLER *z )
{
  exec sql begin declare section;
  long datum;
  exec sql end declare section;

  int i = 0;
  char *fun = "DeleteAkoeinheit";

  datum = date;
  DEBUG_PRINT( fun, "Datum ab:", (int) date, (int)datum )
  exec sql open CAkoeinheit using :datum;
  ERROR_MSG( "open CAkoeinheit" )
  
  exec sql begin work;
  for( ;; )
     {
     i++;
	 if ( i % 500 == 0 )
        Commit( fun );
     
	 exec sql fetch CAkoeinheit;
     ERROR_MSG( "fetch CAkoeinheit" )
     if ( NOT_FOUND )
    	break;
    
     exec sql execute DAkoeinheit;
     ERROR_MSG( "execute DAkoeinheit" );
     z->DelKoeinheit++;
     }
  exec sql commit work;
  return OK;
}

/***** DELETE-AKDVERBUND ****************************************************/

static int DeleteAkdverbund( long date, struct ZAEHLER *z )
{
  exec sql begin declare section;
  long datum;
  short herkunftfiliale;
  long kdauftragnr; 
  exec sql end declare section;

  int i = 0;
  char *fun = "DeleteAkdverbund";

  datum = date;
  DEBUG_PRINT( fun, "Datum ab:", (int) date, (int)datum )
  exec sql open CAkdverbund using :datum;
  ERROR_MSG( "open CAkdverbund" )
  
  exec sql begin work;
  for( ;; )
  {
	 if ( (++i % 100) == 0 )
        Commit( fun );
     
	 exec sql fetch CAkdverbund into :datum, :herkunftfiliale, :kdauftragnr;
     ERROR_MSG( "fetch CAkdverbund" )
     if ( NOT_FOUND )
    	break;
    
     DeleteAkdverbundPos( datum,herkunftfiliale,kdauftragnr, z ); 
     DeleteAkdverbundPosRab( datum,herkunftfiliale,kdauftragnr, z ); 
	 exec sql execute DAkdverbund;
     ERROR_MSG( "execute DAkdverbund" );
     z->DelKdverbund++;
     }
  exec sql commit work;
  return OK;
}

/***** DELETE-AKDVERBUNDPOS *************************************************/

static int DeleteAkdverbundPos( long date, short filiale, long kdnr, struct ZAEHLER *z )
{
  exec sql begin declare section;
  long datum = date;
  short herkunftfiliale = filiale;
  long kdauftragnr = kdnr;
  exec sql end declare section;

  char *fun = "DeleteAkdverbundPos";

  exec sql execute DAkdverbundpos using :datum, :herkunftfiliale, :kdauftragnr;
  ERROR_MSG( "execute DAkdverbundpos" );
  z->DelKdverbundPos+=sqlca.sqlerrd[2];
  return OK;
}

/***** DELETE-AKDVERBUNDPOSRAB *************************************************/

static int DeleteAkdverbundPosRab( long date, short filiale, long kdnr, struct ZAEHLER *z )
{
  exec sql begin declare section;
  long datum = date;
  short herkunftfiliale = filiale;
  long kdauftragnr = kdnr;
  exec sql end declare section;

  char *fun = "DeleteAkdverbundPosRab";

  exec sql execute DAkdverbundposrab using :datum, :herkunftfiliale, :kdauftragnr;
  ERROR_MSG( "execute DAkdverbundposrab" );
  z->DelKdverbundPosRab+=sqlca.sqlerrd[2];
  return OK;
}

/***** DELETE-STOCKENTRY *************************************************/

static int DeleteStockentry( long date, struct ZAEHLER *z )
{
  exec sql begin declare section;
  long datum = date;
  exec sql end declare section;

  int i = 0;
  char *fun = "DeleteStockentry";

  datum = date;
  exec sql open CStockentry using :datum;
  ERROR_MSG( "open CStockentry" )

  
  exec sql begin work;
  for( ;; )
     {
     i++;
	 if ( i % 500 == 0 )
        Commit( fun );
     
	 exec sql fetch CStockentry;
     ERROR_MSG( "fetch CStockentry" )
     if ( NOT_FOUND )
    	break;
    
     exec sql execute DStockentry;
     ERROR_MSG( "execute DStockentry" );
     z->DelStockentry++;
     }
  exec sql commit work;
  return OK;
}

/***** DELETE-CSTSTOCKRESERVE *************************************************/

static int DeleteAcststockreserve( long date, struct ZAEHLER *z )
{
  exec sql begin declare section;
  long datum = date;
  exec sql end declare section;

  int i = 0;
  char *fun = "DeleteAcststockreserve";

  datum = date;
  exec sql open CAcststock using :datum;
  ERROR_MSG( "open CAcststock" )

  
  exec sql begin work;
  for( ;; )
     {
     i++;
	 if ( i % 500 == 0 )
        Commit( fun );
     
	 exec sql fetch CAcststock;
     ERROR_MSG( "fetch CAcststock" )
     if ( NOT_FOUND )
    	break;
    
     exec sql execute DAcststock;
     ERROR_MSG( "execute DAcststock" );
     z->DelAcststockreserve++;
     }
  exec sql commit work;
  return OK;
}

static int DeleteDailyFiles( struct ZAEHLER *z )
{

  char *fun = "DeleteDailyFiles";
  int i = 0;
  
  /* customerorderno */

  exec sql open CCustomerno;
  ERROR_MSG( "open CCustomerno" )

  for( ;; )
     {
     if ( i == 0 )
	    Commit( fun );

	 i++;
     exec sql fetch CCustomerno;
     ERROR_MSG( "fetch CCustomerno" )
     if ( NOT_FOUND )
	    {
	    exec sql commit work;
	    break;
	    }
     else if ( i >= MAX_TRANSAKTION )
        {
	    i = 0;
		}
     exec sql execute DCustomerno;
     ERROR_MSG( "execute DCustomerno" );
     z->DelCostomerorderno++;
     }

	exec sql close CCustomerno;

  return OK;
}

static int DeletePhoneHistory( struct ZAEHLER *z )
{
  timeval_t timev_s;
  timeStr   *time_d;

  gettimeofday( &timev_s , NULL );
  timev_s.tv_sec = timev_s.tv_sec - ( 24 * 60 * 60 * 7 );	/* 7 Tage	*/

  time_d = (timeStr *)TimeOfDay( timev_s.tv_sec );
  sprintf( str, "%04d%02d%02d", time_d->year, time_d->mon, time_d->day );
  
  datedelphone = atol( str );

  char *fun = "DeletePhoneHistory";
  int i = 0;
  
  /* oecustomercalls */

  exec sql open COECustomerCalls using :datedelphone,:iFilialNr;
  ERROR_MSG( "open COECustomerCalls" )

  for( ;; )
     {
     if ( i == 0 )
	    Commit( fun );

	 i++;
     exec sql fetch COECustomerCalls;
     ERROR_MSG( "fetch COECustomerCalls" )
     if ( NOT_FOUND )
	    {
	    exec sql commit work;
	    break;
	    }
     else if ( i >= MAX_TRANSAKTION )
        {
	    i = 0;
		}
     exec sql execute DOECustomerCalls;
     ERROR_MSG( "execute DOECustomerCalls" );
     z->DelPhoneHistory++;
     }

	exec sql close COECustomerCalls;

  return OK;
}


/***** DELETE-TOTEINFO *************************************************/

static int DeleteToteInfo( long date, struct ZAEHLER *z )
{
  exec sql begin declare section;
  long datum = date;
  exec sql end declare section;

  int i = 0;
  char *fun = "DeleteToteInfo";

  datum = date;
  exec sql open CToteinfo using :datum;
  ERROR_MSG( "open CToteinfo" )

  
  exec sql begin work;
  for( ;; )
     {
     i++;
	 if ( i % 500 == 0 )
        Commit( fun );
     
	 exec sql fetch CToteinfo;
     ERROR_MSG( "fetch CToteinfo" )
     if ( NOT_FOUND )
    	break;
    
     exec sql execute DToteinfo;
     ERROR_MSG( "execute DToteinfo" );
     z->DelToteInfo++;
     }
  exec sql commit work;
  return OK;
}

/***** DELETE-DOCUMENTPRINTINFO *************************************************/

static int DeleteDocumentPrintInfo(long date, struct ZAEHLER *z)
{
	exec sql begin declare section;
	long datum = date;
	exec sql end declare section;

	int i = 0;
	char *fun = "DeleteDocumentPrintInfo";

	datum = date;
	exec sql open CDocumentprintinfo using :datum;
	ERROR_MSG("open CDocumentprintinfo")


		exec sql begin work;
	for (;; )
	{
		i++;
		if (i % 500 == 0)
			Commit(fun);

		exec sql fetch CDocumentprintinfo;
		ERROR_MSG("fetch CDocumentprintinfo")
			if (NOT_FOUND)
				break;

		exec sql execute DDocumentprintinfo;
		ERROR_MSG("execute DDocumentprintinfo");
		z->DelDocumentPrintInfo++;
	}
	exec sql commit work;
	return OK;
}

static int DeleteKdauftraginfo( Nummer *num, struct ZAEHLER *z )
{
  exec sql begin declare section;
  long kdauftragnr;
  exec sql end declare section;

  char *fun = "DeleteKdauftraginfo";
  
  kdauftragnr = num->KdNr;

  /* kdauftraginfo */

  exec sql open CKdinfo using :kdauftragnr;
  ERROR_MSG( "open CKdinfo" )

  for( ;; )
     {
     exec sql fetch CKdinfo;
     ERROR_MSG( "fetch CKdinfo" )
     if ( NOT_FOUND )
		break;
     exec sql execute DKdinfo;
     ERROR_MSG( "execute DKdinfo" );
     z->DelKdauftraginfo++;
     }

  return OK;
}

/***** REAKTIVIERE-AKDAUFTRAG ****************************************************/

static int ReaktiviereAuftrag( struct ZAEHLER *z )
{
	exec sql begin declare section;
	long datum;
	long KdauftragNrAlt;
	long KdauftragNrNeu;
	kdauftragS d;
	exec sql end declare section;

	int rc;
	int i = 0;
	char *fun = "ReaktiviereAuftrag";

	if ((rc = PrepareReaktiviereAuftrag( )) != OK) return rc;
	if ((rc = PrepareIncreaseNummer( )) != OK) return rc;
	if ((rc = PrepareReaktiviereKdauftrag( )) != OK) return rc;
	if ((rc = PrepareReaktiviereKdauftragPos( )) != OK) return rc;
	if ((rc = PrepareReaktiviereKdauftragPosRab( )) != OK) return rc;
	if ((rc = PrepareReaktiviereKdauftragPosCharge( )) != OK) return rc;
	if ((rc = PrepareReaktiviereKdauftragBem( )) != OK) return rc;
	if ((rc = PrepareReaktiviereKdauftragEreignis( )) != OK) return rc;
	if ((rc = PrepareReaktiviereKdispoArtikel( )) != OK) return rc;
	exec sql open CDDakdauftrag;
	ERROR_MSG( "open CDDakdauftrag" )

	exec sql begin work;
	for( ;; )
	{
		i++;
		if ( i % 5 == 0 )
		Commit( fun );

		exec sql fetch CDDakdauftrag into :datum,:d;
		ERROR_MSG( "fetch CDDakdauftrag" )
		if ( NOT_FOUND )
			break;

		if(d.DATUMORG == 0) d.DATUMORG = datum;
		if(d.KDAUFTRAGNRORG == 0) d.KDAUFTRAGNRORG = d.KDAUFTRAGNR;
		KdauftragNrAlt = d.KDAUFTRAGNR;

		if ((rc = IncreaseNummer( &KdauftragNrNeu )) != OK) return rc;
		d.KDAUFTRAGNR = KdauftragNrNeu;

		if ((rc = ReaktiviereKdauftrag( &d )) != OK) return rc;
		if ((rc = ReaktiviereKdauftragPos( datum, KdauftragNrAlt, KdauftragNrNeu )) != OK) return rc;
		if ((rc = ReaktiviereKdauftragPosRab( datum, KdauftragNrAlt, KdauftragNrNeu )) != OK) return rc;
		if ((rc = ReaktiviereKdauftragPosCharge( datum, KdauftragNrAlt, KdauftragNrNeu )) != OK) return rc;
		if ((rc = ReaktiviereKdauftragBem( datum, KdauftragNrAlt, KdauftragNrNeu )) != OK) return rc;
		if ((rc = ReaktiviereKdauftragEreignis( &d )) != OK) return rc;
		if ((rc = ReaktiviereKdispoArtikel( datum, KdauftragNrAlt, KdauftragNrNeu )) != OK) return rc;

		exec sql execute UDDakdauftrag using :d.KDAUFTRAGNRORG, :d.DATUMORG;
		ERROR_MSG( "execute UDDakdauftrag" );
		z->Reaktiviert++;
	}
	exec sql commit work;

	return OK;
}

/***** REAKTIVIERE-KDAUFTRAG ****************************************************/

static int ReaktiviereKdauftrag( kdauftragS *d )
{
	exec sql begin declare section;
	kdauftragS *a;
	exec sql end declare section;

	int i = 0;
	char *fun = "ReaktiviereKdauftrag";

	a = d;
	exec sql execute IDDkdauftrag using KDAUFTRAG_ZEIGER(a);
	ERROR_MSG( "execute IDDkdauftrag" );

	return OK;
}

/***** INCREASE-NUMMER **********************************************/

static int IncreaseNummer( long *KdauftragNr )
{
	exec sql begin declare section;
	long aufnr;
	long wert;
	exec sql end declare section;

	char *fun = "PrepareIncreaseNummer";

	exec sql open CSelNummer;
	ERROR_MSG( "open CSelNummer" )
	exec sql fetch CSelNummer into :aufnr,:wert;
	ERROR_MSG( "fetch CSelNummer" )
	aufnr += wert;
	exec sql execute UpdNummer using :aufnr;
	ERROR_MSG( "execute UpdNummer" );
	*KdauftragNr = aufnr;
  
	return OK;
}

/***** REAKTIVIERE-KDAUFTRAGPOS ****************************************************/

static int ReaktiviereKdauftragPos( long lDatum, long KdauftragNr, long KdauftragNrNeu )
{
	exec sql begin declare section;
	kdauftragposS a;
	kdauftragposS *b;
	long datum;
	long aufnr;
	exec sql end declare section;

	b = &a;
	int i = 0;
	char *fun = "ReaktiviereKdauftragPos";

	datum = lDatum;
	aufnr = KdauftragNr;

	exec sql open CDDakdauftragpos using :datum, :aufnr;
	ERROR_MSG( "open CDDakdauftragpos" )
	for(;;)
	{
		exec sql fetch CDDakdauftragpos into :a;
		ERROR_MSG( "fetch CDDakdauftragpos" )
		if ( NOT_FOUND )
			break;
		a.KDAUFTRAGNR = KdauftragNrNeu;

#undef HINWEIS 
		exec sql execute IDDkdauftragpos using KDAUFTRAGPOS_ZEIGER(b);
		ERROR_MSG( "execute IDDkdauftragpos" );
	}
 #define HINWEIS              'H'
	return OK;
}

/***** REAKTIVIERE-KDAUFTRAGPOSRAB ****************************************************/

static int ReaktiviereKdauftragPosRab( long lDatum, long KdauftragNr, long KdauftragNrNeu )
{
	exec sql begin declare section;
	kdauftragposrabS a;
	kdauftragposrabS *b;
	long datum;
	long aufnr;
	exec sql end declare section;

	b = &a;
	int i = 0;
	char *fun = "ReaktiviereKdauftragPosRab";

	datum = lDatum;
	aufnr = KdauftragNr;

	exec sql open CDDakdauftragposrab using :datum, :aufnr;
	ERROR_MSG( "open CDDakdauftragposrab" )
	for(;;)
	{
		exec sql fetch CDDakdauftragposrab into :a;
		ERROR_MSG( "fetch CDDakdauftragposrab" )
		if ( NOT_FOUND )
			break;
		a.KDAUFTRAGNR = KdauftragNrNeu;

#undef HINWEIS 
		exec sql execute IDDkdauftragposrab using KDAUFTRAGPOSRAB_ZEIGER(b);
		ERROR_MSG( "execute IDDkdauftragposrab" );
	}
 #define HINWEIS              'H'
	return OK;
}

/***** REAKTIVIERE-KDAUFTRAGPOSCHARGE ****************************************************/

static int ReaktiviereKdauftragPosCharge( long lDatum, long KdauftragNr, long KdauftragNrNeu )
{
	exec sql begin declare section;
	kdauftragposchargeS a;
	kdauftragposchargeS *b;
	long datum;
	long aufnr;
	exec sql end declare section;

	b = &a;
	int i = 0;
	char *fun = "ReaktiviereKdauftragPosCharge";

	datum = lDatum;
	aufnr = KdauftragNr;

	exec sql open CDDakdauftragposcharge using :datum, :aufnr;
	ERROR_MSG( "open CDDakdauftragposcharge" )
	for(;;)
	{
		exec sql fetch CDDakdauftragposcharge into :a;
		ERROR_MSG( "fetch CDDakdauftragposcharge" )
		if ( NOT_FOUND )
			break;
		a.KDAUFTRAGNR = KdauftragNrNeu;

#undef HINWEIS 
		exec sql execute IDDkdauftragposcharge using KDAUFTRAGPOSCHARGE_ZEIGER(b);
		ERROR_MSG( "execute IDDkdauftragposcharge" );
	}
 #define HINWEIS              'H'
	return OK;
}

/***** REAKTIVIERE-KDAUFTRAGBEM ****************************************************/

static int ReaktiviereKdauftragBem( long lDatum, long KdauftragNr, long KdauftragNrNeu )
{
	exec sql begin declare section;
	kdauftragbemS a;
	kdauftragbemS *b;
	long datum;
	long aufnr;
	exec sql end declare section;

	int i = 0;
	char *fun = "ReaktiviereKdauftragBem";

	b = &a;
	datum = lDatum;
	aufnr = KdauftragNr;

	exec sql open CDDakdauftragbem using :datum, :aufnr;
	ERROR_MSG( "open CDDakdauftragbem" )
	for(;;)
	{
		exec sql fetch CDDakdauftragbem into :a;
		ERROR_MSG( "fetch CDDakdauftragbem" )
		if ( NOT_FOUND )
			break;
		a.KDAUFTRAGNR = KdauftragNrNeu;

		exec sql execute IDDkdauftragbem using KDAUFTRAGBEM_ZEIGER(b);
		ERROR_MSG( "execute IDDkdauftragbem" );
	}

	return OK;
}

/***** REAKTIVIERE-DISPOARTIKEL ****************************************************/

static int ReaktiviereKdispoArtikel( long lDatum, long KdauftragNr, long KdauftragNrNeu )
{
	exec sql begin declare section;
	dispoartikelS a;
	dispoartikelS *b;
	long datum;
	long aufnr;
	exec sql end declare section;

	int i = 0;
	char *fun = "ReaktiviereKdispoArtikel";

	b = &a;
	datum = lDatum;
	aufnr = KdauftragNr;

	exec sql open CDDadispoartikel using :datum, :aufnr;
	ERROR_MSG( "open CDDadispoartikel" )
	for(;;)
	{
		exec sql fetch CDDadispoartikel into :a;
		ERROR_MSG( "fetch CDDadispoartikel" )
		if ( NOT_FOUND )
			break;
		a.KDAUFTRAGNR = KdauftragNrNeu;

		exec sql execute IDDdispoartikel using DISPOARTIKEL_ZEIGER(b);
		ERROR_MSG( "execute IDDdispoartikel" );
	}

	return OK;
}

/***** REAKTIVIERE-KDAUFTRAGEREIGNIS ****************************************************/

static int ReaktiviereKdauftragEreignis( kdauftragS *d )
{
	exec sql begin declare section;
	kdauftragS *b;
	exec sql end declare section;

	int i = 0;
	char *fun = "ReaktiviereKdauftragEreignis";

	b = d;
	exec sql execute IDDkdauftragereig using
		:b->KDAUFTRAGNR,
		:lDatumEreignis,
		:lZeitEreignis,
		'12',
		'0',
		'0000',
		:b->FILIALNR;
	ERROR_MSG( "execute IDDkdauftragereig" );

	return OK;
}
   
/***** PREPARE-REAKTIVIERE-AUFTRAG **********************************************/

static int PrepareReaktiviereAuftrag( )
{
	char *fun = "PrepareReaktiviereAuftrag";

	strcpy( str, "select " );
	strcat( str, " datum," );
	strcat( str, KDAUFTRAG_PELISTE );
	strcat( str, " from akdauftrag" );
	strcat( str, " where datumauslieferung > '0'" );
	strcat( str, " and kdauftragstat[5] != '1'" );	/* Erfasst */
	strcat( str, " and kdauftragstat[10] != '1'" );	/* Storniert */
	strcat( str, " and kzrestored != '1'" );
	strcat( str, " for update " );

	exec sql prepare SDDakdauftrag from :str;
	ERROR_MSG( "prepare SDDakdauftrag" );
	exec sql declare CDDakdauftrag cursor with hold for SDDakdauftrag;
	exec sql free SDDakdauftrag;

	strcpy( str, "update akdauftrag" );
	strcat( str, " set kzrestored = '1'" );
	strcat( str, ",kdauftragnrorg = ?" );
	strcat( str, ",datumorg = ?" );
	strcat( str, " where current of CDDakdauftrag" );
	exec sql prepare UDDakdauftrag from :str;
	ERROR_MSG( "prepare UDDakdauftrag" );

	return OK;
}
   
/***** PREPARE-INCREASE-NUMMER **********************************************/

static int PrepareIncreaseNummer( )
{
	char *fun = "PrepareIncreaseNummer";

	strcpy( str, "select nummerwert,nummerinkrement " );
	strcat( str, "from nummer " );
	strcat( str, "where " );
	strcat( str, "nummertyp = '1' " );
	strcat( str, "for update" );
	exec sql prepare SelNummer from :str;
	ERROR_MSG( "prepare SelNummer" );
	exec sql declare CSelNummer cursor with hold for SelNummer;
	exec sql free SelNummer;

	strcpy( str, "update nummer " );
	strcat( str, "set nummerwert = ? " );
	strcat( str, "where current of CSelNummer" );
	exec sql prepare UpdNummer from :str;
	ERROR_MSG( "prepare UpdNummer" );
  
	return OK;
}

/***** PREPARE-REAKTIVIERE-KDAUFTRAG *********************************************/

static int PrepareReaktiviereKdauftrag( )
{
	char *fun = "PrepareReaktiviereKdauftrag";

	strcpy( str, "insert into kdauftrag (" );
	strcat( str, KDAUFTRAG_PELISTE );
	strcat( str, ") values (" );
	strcat( str, "?,?,?,?,?,?,?,?,?,?," );
	strcat( str, "?,?,?,?,?,?,?,?,?,?," );
	strcat( str, "?,?,?,?,?,?,?,?,?,?," );
	strcat( str, "?,?,?,?,?,?,?,?,?,?," );
	strcat( str, "?,?,?,?,?,?,?,?,?,?," );
	strcat( str, "?,?,?,?,?,?,?,?,?,?," );
	strcat( str, "?,?,?,?,?,?,?,?,?,?," );
	strcat( str, "?,?,?,?,?,? " );
	strcat( str, ")" );

	exec sql prepare IDDkdauftrag from :str;
	ERROR_MSG( "prepare IDDkdauftrag" );

	return OK;
}

/***** PREPARE-REAKTIVIERE-KDAUFTRAGPOS *********************************************/

static int PrepareReaktiviereKdauftragPos( )
{
	char *fun = "PrepareReaktiviereKdauftragPos";
	strcpy( str, "select " );
	strcat( str, KDAUFTRAGPOS_PELISTE );
	strcat( str, " from akdauftragpos" );
	strcat( str, " where datum = ?" );
	strcat( str, " and kdauftragnr = ?" );

	exec sql prepare SDDakdauftragpos from :str;
	ERROR_MSG( "prepare SDDakdauftragpos" );
	exec sql declare CDDakdauftragpos cursor with hold for SDDakdauftragpos;
	exec sql free SDDakdauftragpos;

	strcpy( str, "insert into kdauftragpos (" );
	strcat( str, KDAUFTRAGPOS_PELISTE );
	strcat( str, ") values (" );
	strcat( str, "?,?,?,?,?,?,?,?,?,?," );
	strcat( str, "?,?,?,?,?,?,?,?,?,?," );
	strcat( str, "?,?,?,?,?,?,?,?,?,?," );
	strcat( str, "?,?,?,?,?,?,?,?,?,?," );
	strcat( str, "?,?,?,?,?,?,?,?,?,?," );
	strcat( str, "?,?,?,?,?,?,?,? " );
	strcat( str, ")" );

	exec sql prepare IDDkdauftragpos from :str;
	ERROR_MSG( "prepare IDDkdauftragpos" );

	return OK;
}

/***** PREPARE-REAKTIVIERE-KDAUFTRAGPOSRAB *********************************************/

static int PrepareReaktiviereKdauftragPosRab( )
{
	char *fun = "PrepareReaktiviereKdauftragPosRab";
	strcpy( str, "select " );
	strcat( str, KDAUFTRAGPOSRAB_PELISTE );
	strcat( str, " from akdauftragposrab" );
	strcat( str, " where datum = ?" );
	strcat( str, " and kdauftragnr = ?" );

	exec sql prepare SDDakdauftragposrab from :str;
	ERROR_MSG( "prepare SDDakdauftragposrab" );
	exec sql declare CDDakdauftragposrab cursor with hold for SDDakdauftragposrab;
	exec sql free SDDakdauftragposrab;

	strcpy( str, "insert into kdauftragposrab (" );
	strcat( str, KDAUFTRAGPOSRAB_PELISTE );
	strcat( str, ") values (" );
	strcat( str, "?,?,?,?,? " );
	strcat( str, ")" );

	exec sql prepare IDDkdauftragposrab from :str;
	ERROR_MSG( "prepare IDDkdauftragposrab" );

	return OK;
}

/***** PREPARE-REAKTIVIERE-KDAUFTRAGPOSCHARGE *********************************************/

static int PrepareReaktiviereKdauftragPosCharge( )
{
	char *fun = "PrepareReaktiviereKdauftragPosCharge";
	strcpy( str, "select " );
	strcat( str, KDAUFTRAGPOSCHARGE_PELISTE );
	strcat( str, " from akdauftragposcharg" );
	strcat( str, " where date = ?" );
	strcat( str, " and kdauftragnr = ?" );

	exec sql prepare SDDakdauftragposcharge from :str;
	ERROR_MSG( "prepare SDDakdauftragposcharge" );
	exec sql declare CDDakdauftragposcharge cursor with hold for SDDakdauftragposcharge;
	exec sql free SDDakdauftragposcharge;

	strcpy( str, "insert into kdauftragposcharge (" );
	strcat( str, KDAUFTRAGPOSCHARGE_PELISTE );
	strcat( str, ") values (" );
	strcat( str, "?,?,?,? " );
	strcat( str, ")" );

	exec sql prepare IDDkdauftragposcharge from :str;
	ERROR_MSG( "prepare IDDkdauftragposcharge" );

	return OK;
}

/***** PREPARE-REAKTIVIERE-KDAUFTRAGBEM *********************************************/

static int PrepareReaktiviereKdauftragBem( )
{
	char *fun = "PrepareReaktiviereKdauftragBem";

	strcpy( str, "select " );
	strcat( str, KDAUFTRAGBEM_PELISTE );
	strcat( str, " from akdauftragbem" );
	strcat( str, " where datum = ?" );
	strcat( str, " and kdauftragnr = ?" );

	exec sql prepare SDDakdauftragbem from :str;
	ERROR_MSG( "prepare SDDakdauftragbem" );
	exec sql declare CDDakdauftragbem cursor with hold for SDDakdauftragbem;
	exec sql free SDDakdauftragbem;

	strcpy( str, "insert into kdauftragbem (" );
	strcat( str, KDAUFTRAGBEM_PELISTE );
	strcat( str, ") values (" );
	strcat( str, "?,?,?,? " );
	strcat( str, ")" );

	exec sql prepare IDDkdauftragbem from :str;
	ERROR_MSG( "prepare IDDkdauftragbem" );

	return OK;
}

/***** PREPARE-REAKTIVIERE-DISPOARTIKEL *********************************************/

static int PrepareReaktiviereKdispoArtikel( )
{
	char *fun = "PrepareReaktiviereKdispoArtikel";

	strcpy( str, "select " );
	strcat( str, DISPOARTIKEL_PELISTE );
	strcat( str, " from adispoartikel" );
	strcat( str, " where datum = ?" );
	strcat( str, " and kdauftragnr = ?" );

	exec sql prepare SDDadispoartikel from :str;
	ERROR_MSG( "prepare SDDadispoartikel" );
	exec sql declare CDDadispoartikel cursor with hold for SDDadispoartikel;
	exec sql free SDDadispoartikel;

	strcpy( str, "insert into dispoartikel (" );
	strcat( str, DISPOARTIKEL_PELISTE );
	strcat( str, ") values (" );
	strcat( str, "?,?,?,?,?,?,?,?,?,?," );
	strcat( str, "?,?,?,?,?,?,?,?,?,?," );
	strcat( str, "? " );
	strcat( str, ")" );

	exec sql prepare IDDdispoartikel from :str;
	ERROR_MSG( "prepare IDDdispoartikel" );

	return OK;
}

/***** PREPARE-REAKTIVIERE-KDAUFTRAGEREIGNIS *********************************************/

static int PrepareReaktiviereKdauftragEreignis( )
{
	char *fun = "PrepareReaktiviereKdauftragEreignis";

	strcpy( str, "insert into kdauftragereignis (" );
	strcat( str, KDAUFTRAGEREIGNIS_PELISTE );
	strcat( str, ") values (" );
	strcat( str, "?,?,?,?,?,?,? " );
	strcat( str, ")" );

	exec sql prepare IDDkdauftragereig from :str;
	ERROR_MSG( "prepare IDDkdauftragereig" );

	return OK;
}
   
/*** Korrektur kzrestored bei verzögerter Auslieferung ************************/

static int UpdateKzrestored( const short iFilialNr )
{
	exec sql begin declare section;
	const short iDBFilialNr = iFilialNr;
	exec sql end declare section;

	char *fun = "UpdateKzrestored";

	strcpy( str, "select " );
	strcat( str, " kzrestored " );
	strcat( str, " from kdauftrag" );
	strcat( str, " where datumauslieferung > '0'" );
	strcat( str, " and kdauftragstat[5] != '1'" );	/* Erfasst */
	strcat( str, " and kdauftragstat[10] != '1'" );	/* Storniert */
	strcat( str, " and kzrestored = '1'" );
	strcat( str, " and vertriebszentrumnr = ?" );
	strcat( str, " for update " );

	exec sql prepare Srestored from :str;
	ERROR_MSG( "prepare Srestored" );
	exec sql declare Crestored cursor with hold for Srestored;
	exec sql free Srestored;

	strcpy( str, "update kdauftrag" );
	strcat( str, " set kzrestored = '0'" );
	strcat( str, " where current of Crestored" );
	exec sql prepare Urestored from :str;
	ERROR_MSG( "prepare Urestored" );

	exec sql open Crestored using :iDBFilialNr;
	ERROR_MSG( "open Crestored" );
	exec sql begin work;
	for(;;)
	{
		exec sql fetch Crestored;
		ERROR_MSG( "fetch Crestored" )
		if ( NOT_FOUND )
		break;
		exec sql execute Urestored;
		ERROR_MSG( "execute Urestored" );
	}
	exec sql commit work;

	return OK;
}

static int CheckIBTPickingDone(int kdauftragnr)
{
	exec sql begin declare section;
	int iAuftragnr;
	exec sql end declare section;
	iAuftragnr = kdauftragnr;

	exec sql select first 1 * from cscorderflags where cscorderno = :iAuftragnr and waitforibtpicking = 1;
	if (NOT_FOUND) return OK;
	else return ERROR;
}