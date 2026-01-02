/* ---------------------------------------------------------------------- *
 *                        C A L C U L A T E . C                           *
 * ---------------------------------------------------------------------- *
 * Projekt:  ZDP                                                          *
 * Gruppe:   Preisumrechnung wg Mwst-Aenderung                            *
 * ---------------------------------------------------------------------- *
 * Autor  :  Hoerath                                                      *
 * Anfang :  01.12.2006                                                   *
 * Update :                                                               *
 * ---------------------------------------------------------------------- */

/* --- Include-Dateien einbinden ---------------------------------------- */

#include <stdio.h>                                /* C-Standard-Libraries */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <phodate.h>
#include <phozeit.h>
#include <libscsvoodoo.h>

#include <wpp_prot.h>
#include <wpp_dbas.h>
#include <math.h>

#include <zartprei.h>
#include <zartikel.h>
#include <zartfrance.h>
#include <cartrefundfrance.h>
#include <cppediscounts.h>

#include "l_taxtab.h"

/* ----------------- definitions ------------------------ */
#define	MODE_AVPS				0
#define	MODE_FESTPR				1
#define	MODE_AVP_WITHOUT_TAX	2
#define	MODE_AMNOG				3
#define	MODE_AVP_TAX			4
#define	MODE_GROSSO_LBP			5
#define	MODE_REFUND_FRANCE		6
#define	MODE_IMPORT				7

#define MWST_VOLL	"0"
#define MWST_VERM	"1"
#define MWST_OHNE	"2"

#define ART_IS_TAXPFL_1	"1"
#define ART_IS_TAXPFL_2	"2"
#define ART_IS_TAXPFL_3	"3"

#define MAX_CPPEDISCOUNTS 16

typedef enum { PPT_UPDATE, PPT_EXPIRATION, PPT_DELETION } PPE_PROCESSING_TYPE;

/* ----------------- Prototype ------------------------ */

void CloseBase( void );
long OpenBase( char *db, char *errmld );

void Runden_Modf( double *wert, int stellen );
short CheckDate ( char *cDate );

/* ----------------- Funktion ------------------------ */

static char *	user				= "zpcalcpr";

static int		fd_zartikel			= -1;
static int		fd_zartpreis		= -1;

static int		fd_zartfrance		= -1;
static int		fd_cartrefundfrance	= -1;

static double	mwst_alt			= 0.0;
static double	mwst_neu			= 0.0;

static double	ppe_disc			= 0.0;
static long		ppe_date			= 0;

static double	gep_increase_pct	= 0.0;
static double	aep_increase_pct	= 0.0;

static long		checkdatum			= -1;
static long		datgueltab			= -1;
static long		datgueltbis			= -1;
static long		datum_fb1			= -1;
static long		anz_calculated		= 0;
static long		anz_deleted			= 0;

static char 	ke_mwst[2]			= "  ";
static char 	tax_kz [2]			= "  ";

static int		mode				= -1; // 0 -> avp´s ; 1 -> festpreise

static struct	ZARTPREIS			BufPreis;
static struct	ZARTPREIS			BufPreisOld;
static struct	ZARTIKEL			BufArtikel;
static struct	ZARTIKEL			BufArtikelOld;
static struct	ZARTFRANCE			BufZartfrance;
static struct	ZARTFRANCE			BufZartfranceOld;
static struct	CARTREFUNDFRANCE	BufCartrefundfrance;
// Array für CPPEDISCOUNTS-Eintraege
static struct   CPPEDISCOUNTS       BufCppediscountsList[MAX_CPPEDISCOUNTS];
static struct   CPPEDISCOUNTS       BufCppediscounts;

/* ---------------------------------------- */
static void Init( )
{
	fd_zartpreis		= -1;
	fd_zartikel			= -1;
}

/* ---------------------------------------- */
static void InitRefund( )
{
	fd_zartfrance		= -1;
	fd_cartrefundfrance	= -1;
}

/* ---------------------------------------- */
static void Free( )
{
    if ( fd_zartpreis >= 0 )
        CloseOneBufferDesc( fd_zartpreis );
    fd_zartpreis = -1;

	if ( fd_zartikel >= 0 )
        CloseOneBufferDesc( fd_zartikel );
    fd_zartikel = -1;
}

/* ---------------------------------------- */
static void FreeRefund( )
{
    if ( fd_zartfrance >= 0 )
        CloseOneBufferDesc( fd_zartfrance );
    fd_zartfrance = -1;

	if ( fd_cartrefundfrance >= 0 )
        CloseOneBufferDesc( fd_cartrefundfrance );
    fd_cartrefundfrance = -1;
}

/* ---------------------------------------- */
int GetBufferDesc_Zartpreis( char *cErrmld )
{
   char *tabelle = "zartpreis";
   long s;
   char errmld[100];

   *cErrmld = '\0';
   if ( fd_zartpreis >= 0 ) 
	   return 0;
   
   s = OpenBufferDesc	( &fd_zartpreis, tabelle,
                           NULL, NULL, V_PROTO_VERTEIL, errmld );
   if ( s != 0 )
   {
     strcpy( cErrmld, errmld );
     strcat( cErrmld, "\ntable " );
     strcat( cErrmld, tabelle );
     fd_zartpreis = -1;
     return -1;
   }
   return 0;
}

/* ---------------------------------------- */
int GetBufferDesc_Zartikel( char *cErrmld )
{
   char *tabelle = "zartikel";
   long s;
   char errmld[100];

   *cErrmld = '\0';
   if ( fd_zartikel >= 0 ) 
	   return 0;
   
   s = OpenBufferDesc	( &fd_zartikel, tabelle,
                           NULL, NULL, V_PROTO_VERTEIL, errmld );
   if ( s != 0 )
   {
     strcpy( cErrmld, errmld );
     strcat( cErrmld, "\ntable " );
     strcat( cErrmld, tabelle );
     fd_zartikel = -1;
     return -1;
   }
   return 0;
}

/* ---------------------------------------- */
int GetBufferDesc_Zartfrance( char *cErrmld )
{
   char *tabelle = "zartfrance";
   long s;
   char errmld[100];

   *cErrmld = '\0';
   if ( fd_zartfrance >= 0 ) 
	   return 0;
   
   s = OpenBufferDesc	( &fd_zartfrance, tabelle,
                           NULL, NULL, V_PROTO_VERTEIL, errmld );
   if ( s != 0 )
   {
     strcpy( cErrmld, errmld );
     strcat( cErrmld, "\ntable " );
     strcat( cErrmld, tabelle );
     fd_zartfrance = -1;
     return -1;
   }

   return 0;
}

/* ---------------------------------------- */
int GetBufferDesc_Cartrefundfrance( char *cErrmld )
{
   char *tabelle = "cartrefundfrance";
   long s;
   char errmld[100];

   *cErrmld = '\0';
   if ( fd_cartrefundfrance >= 0 ) 
	   return 0;
   
   s = OpenBufferDesc	( &fd_cartrefundfrance, tabelle,
                           NULL, NULL, V_PROTO_VERTEIL, errmld );
   if ( s != 0 )
   {
     strcpy( cErrmld, errmld );
     strcat( cErrmld, "\ntable " );
     strcat( cErrmld, tabelle );
     fd_cartrefundfrance = -1;
     return -1;
   }

   return 0;
}

/* ---------------------------------------- */
static long ReadRecord_ZartPreis( long artikel_nr, long datumgueltigab, char *buf )
{
	long lStatus;
	
	char PrimeKeyCond[100];
	
	sprintf( PrimeKeyCond, "ARTIKEL_NR = %ld and DATUMGUELTIGAB = %ld",
				artikel_nr, datumgueltigab );

	lStatus = FdReadRecord( fd_zartpreis, PrimeKeyCond,
							  &BufPreisOld, buf );
	
	return lStatus;
}

/* ---------------------------------------- */
static long ReadRecord_ZartPreisCurrent( long artikel_nr, char *buf )
{
	long lStatus;
	
	char PrimeKeyCond[100];

	if ( mode == MODE_GROSSO_LBP )
	{
		sprintf( PrimeKeyCond, "ARTIKEL_NR = %7ld and DATUMGUELTIGAB <= %ld ORDER BY DATUMGUELTIGAB desc",
				artikel_nr, datgueltbis );
	}
	else
	{
		sprintf( PrimeKeyCond, "ARTIKEL_NR = %7ld and DATUMGUELTIGAB <= %ld ORDER BY DATUMGUELTIGAB desc",
				artikel_nr, datgueltab );
	}

	FdInitTabBuf( fd_zartpreis, &BufPreis );

	lStatus = FdReadRecord( fd_zartpreis, PrimeKeyCond,
							  &BufPreis, buf );
	
	if ( lStatus == 0 )
	{
		BufPreisOld = BufPreis;
	}
	
	return lStatus;
}

/* ---------------------------------------- 
static long ReadRecord_ZartPreisFuture( long artikel_nr, char *buf )
{
	long lStatus;
	
	char PrimeKeyCond[100];
	
	sprintf( PrimeKeyCond, "ARTIKEL_NR = %7ld and DATUMGUELTIGAB > %ld ORDER BY DATUMGUELTIGAB asc",
				artikel_nr, BufPreis.DATUMGUELTIGAB );

	FdInitTabBuf( fd_zartpreis, &BufPreis );

	lStatus = FdReadRecord( fd_zartpreis, PrimeKeyCond,
							  &BufPreis, buf );
	
	if ( lStatus == 0 )
	{
		BufPreisOld = BufPreis;
	}
	
	return lStatus;
}
*/

/* ------------------------------------------------------------------- */
int WriteZAPflege(long art_no, long date, char * errmld)
{
	int status = 0;
	char sql[500];
	long dummy;

	sprintf( sql, 
		"select datum from zapflege where artikel_nr = %ld "
		"and datum = %ld",
		art_no, date );
	
    status = SqlRead( sql, &dummy, NULL );

	if ( status == 100 ) 
	{
		sprintf( sql, 
			"insert into zapflege ( artikel_nr, datum ) "
			"values ( %ld, %ld )",
			art_no, date );

		status = SqlExecuteImm( sql );
	}
	
	if ( status != 0 )
	{
		strcpy( errmld, "zapflege (Insert einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}
	
	return status;
}

/* ---------------------------------------- */
static long Insert_ZartPreis( char *buf )
{
	long lStatus;
	
	char PrimeKeyCond[100];
	
	sprintf( PrimeKeyCond, "ARTIKEL_NR = %7ld and DATUMGUELTIGAB = %ld",
				BufPreis.ARTIKEL_NR, BufPreis.DATUMGUELTIGAB );

	lStatus = FdWithoutWorkInsertRecord( fd_zartpreis, &BufPreis, PrimeKeyCond, buf );
	
	if ( lStatus == 0 )
	{
		lStatus = WriteZAPflege(BufPreis.ARTIKEL_NR, BufPreis.DATUMGUELTIGAB, buf);
	}

	return lStatus;
}

/* ---------------------------------------- */
static long StoreRecord_ZartPreis( char *buf )
{
	long lStatus;
	
	char PrimeKeyCond[100];
	
	sprintf( PrimeKeyCond, "ARTIKEL_NR = %7ld and DATUMGUELTIGAB = %ld",
				BufPreis.ARTIKEL_NR, BufPreis.DATUMGUELTIGAB );

	lStatus = ReadRecord_ZartPreis(BufPreis.ARTIKEL_NR, BufPreis.DATUMGUELTIGAB, buf);

	if ( lStatus == 0 )
	{
		lStatus = FdDelayUpdateRecord( fd_zartpreis, &BufPreis, &BufPreisOld, 
										 PrimeKeyCond, buf);
	}
	else if ( lStatus == 100 )
	{
		lStatus = FdDelayInsertRecord( fd_zartpreis, &BufPreis, PrimeKeyCond, buf);
	}

	if ( lStatus == 0 && (mode == MODE_AVP_WITHOUT_TAX || mode == MODE_AMNOG || mode == MODE_AVP_TAX || mode == MODE_GROSSO_LBP || mode == MODE_IMPORT ) )
	{
		lStatus = WriteZAPflege(BufPreis.ARTIKEL_NR, BufPreis.DATUMGUELTIGAB, buf);
	}

	return lStatus;
}

/* ---------------------------------------- */
static int ComputeGrosso(double disc_value, long disc_datefrom, PPE_PROCESSING_TYPE processingType, struct ZARTPREIS* zartpreis)
{
	double tempPrice = 0.0;

	/* CPR-210586: 
	   on update of discount set LIEFERBASISPREIS to GROSSO if LIEFERBASISPREIS is 0,
	   on deletion or expiration of discount set LIEFERBASISPREIS to 0 */
	if (processingType == PPT_UPDATE)
	{
		if (zartpreis->LIEFERBASISPREIS == 0.0 && zartpreis->GROSSO != 0.0)
		{
			zartpreis->LIEFERBASISPREIS = zartpreis->GROSSO;
		}
	}
	else      // deletion or expiration
	{
		if (zartpreis->LIEFERBASISPREIS != 0.0)
		{
			zartpreis->GROSSO = zartpreis->LIEFERBASISPREIS;
			zartpreis->LIEFERBASISPREIS = 0.0;
		}
	}

	if (zartpreis->LIEFERBASISPREIS != 0.0)
	{
		if (disc_value != 0.0)
		{
			tempPrice = zartpreis->LIEFERBASISPREIS - (zartpreis->LIEFERBASISPREIS * disc_value / 100);
			Runden_Modf(&tempPrice, 2);
			zartpreis->GROSSO = tempPrice;
		}
		else
		{
			zartpreis->GROSSO = zartpreis->LIEFERBASISPREIS;
		}
	}

	if (zartpreis->DATUMGUELTIGAB < disc_datefrom)
	{
		zartpreis->DATUMGUELTIGAB = disc_datefrom;
	}

	zartpreis->HERST_PROZENT = disc_value;

	// update of price will only by done, if GROSSO <= AVP
	if (zartpreis->GROSSO <= zartpreis->AVP || zartpreis->AVP == 0)
	{
		return 1;
	}

	return 0;
}

/* ---------------------------------------- */
static int UpdateFutureZartpreis(long artikel_nr, long datefrom, double discount, PPE_PROCESSING_TYPE processingType, char *buf)
{
	long s;
	int fd_sel_zartpreis = -1;

	sprintf(buf,
		"select %s "
		"from ZARTPREIS "
		"where ARTIKEL_NR = %ld "
		"and DATUMGUELTIGAB > %ld "
		"order by DATUMGUELTIGAB",
		PROJECTION_ZARTPREIS,
		artikel_nr,
		datefrom
	);
	s = SqlOpenCsWh(&fd_sel_zartpreis, buf);

	if (s != 0 && s != 100)
	{
		strcpy(buf, "ZARTPREIS\n");
		strcat(buf, DynErrmld());
		return s;
	}

	while (s == 0)
	{
		s = SqlFetch(fd_sel_zartpreis, 1, &BufPreis, NULL);
		if (s == 0)
		{
			if ( ComputeGrosso( discount, BufPreis.DATUMGUELTIGAB, processingType, &BufPreis ) )
			{
				s = StoreRecord_ZartPreis(buf);
			}
		}
	}

	SqlCloseCs(fd_sel_zartpreis);

	if (s != 0 && s != 100)
	{
		strcpy(buf, "ZARTPREIS\n");
		strcat(buf, DynErrmld());

		return s;
	}

	if (s == 100)
		s = 0;

	return s;
}

/* ---------------------------------------- */
static long StoreRecord_Zartikel( char *buf )
{
	long lStatus;
	
	char PrimeKeyCond[100];
	
	sprintf( PrimeKeyCond, "ARTIKEL_NR=%7ld",
				BufArtikel.ARTIKEL_NR );

	lStatus = FdDelayUpdateRecord( fd_zartikel, &BufArtikel, &BufArtikelOld, 
										 PrimeKeyCond, buf);

	return lStatus;
}

/* ---------------------------------------- */
static int ReadMwst( char *buf )
{
	long s;

	if ( strcmp (ke_mwst, MWST_VERM ) == 0 )	// vermindert
	{
		sprintf( buf,
				"select MWST_2, MWST_2_ALT from FILIALE");
	}
	else if ( strcmp (ke_mwst, MWST_OHNE ) == 0 )	// ohne
	{
		sprintf( buf,
				"select MWST_3, MWST_3_ALT from FILIALE");
	}
	else					// voll
	{
		sprintf( buf,
				"select MWST_1, MWST_1_ALT from FILIALE");
	}
	
	s = SqlRead( buf, &mwst_neu, &mwst_alt, NULL ); 
	
	if ( s != 0 )
		strcpy( buf, DynErrmld());
		
	return s;
}

/* ---------------------------------------- */
static int ReadPpePct( char *buf )
{
	long s;

	sprintf( buf, "SELECT ppetotaldiscpct, datefrom FROM cppeartdischist WHERE articleno = %ld and datefrom > %ld ORDER BY datefrom ASC", BufArtikel.ARTIKEL_NR, datgueltab);
	
	s = SqlRead( buf, &ppe_disc, &ppe_date, NULL ); 
	
	if ( s != 0 )
		strcpy( buf, DynErrmld());
		
	return s;
}

/* ---------------------------------------- */
/* liest alle CPPEDISCOUNTS Eintraege des Artikels im Selektionsintervall 
   Paramenter cppediscounts ist ein Array von CPPEDISCOUNTS Strukturen */
static int ReadCppediscounts(long artikel_nr, long datefrom, long dateto, struct CPPEDISCOUNTS* cppediscounts, char *buf )
{
	long s;
	int fd_sel_cppediscounts = -1;
	int i = 0;

#ifdef _DEBUG
//	printf("--> ReadCppediscounts()\n");
#endif // 

	/* Endemarker im cppediscounts-Array setzen */
	cppediscounts[0].ARTICLENO = 0;

	/* zur Logik der Selektion s. Kommentar in CalcAll()
	   Hinweis: wenn die Selektionskriterien hier geaendert werden,
	   muessen sie auch in CalcAll() und CalcSingle() entsprechend
	   angepasst werden */
	/* ACHTUNG: LASTCHANGEDATE darf nicht mit selektiert werden, 
	            fuehrt sonst unter Unix zu Sqlcode -402 beim Fetch */
	sprintf(buf,
		"select ARTICLENO, DATEFROM, DATETO, CHANGECODEID, PPETOTALDISCPCT "
		"from CPPEDISCOUNTS "
		"where ARTICLENO = %ld "
		"  and ((CHANGECODEID = 0 "
		"        and (   (DATEFROM > %ld and DATEFROM <= %ld) "
		"             or (DATETO >= %ld and DATETO < %ld) "
		"            ) "
		"       ) "
		"       or CHANGECODEID = 1 "
		"      ) "
		"order by CHANGECODEID desc, DATEFROM desc",
		artikel_nr,
		datefrom, 
		dateto,
		datefrom,
		dateto
	);
	s = SqlOpenCsWh(&fd_sel_cppediscounts, buf);

#ifdef _DEBUG
//	printf("ReadCppediscounts(): SqlOpenCsWh() returns %ld\n", s);
#endif // 

	if (s != 0)
	{
		strcpy(buf, "CPPEDISCOUNTS\n");
		strcat(buf, DynErrmld());
		return s;
	}

	do
	{
		s = SqlFetch(fd_sel_cppediscounts, 1, &cppediscounts[i].ARTICLENO,
                                   			  &cppediscounts[i].DATEFROM,
			                                  &cppediscounts[i].DATETO,
			                                  &cppediscounts[i].CHANGECODEID,
			                                  &cppediscounts[i].PPETOTALDISCPCT,
			                                  NULL);
#ifdef _DEBUG
//		printf("ReadCppediscounts(): SqlFetch() returns %ld\n", s);
#endif // 

		if (s == 0)
		{
			/* wir koennen max. MAX_CPPEDISCOUNTS - 1 cppediscounts-Saetze in unser Array
			   aufnehmen, weil wir ein Array-Element fuer den Ende-Marker brauchen, d.h.
			   wenn wir MAX_CPPEDISCOUNTS - 1 als Index erreicht haben, haben wir mind.
		       ein Element zu viel */
			i++;
			if (i >= MAX_CPPEDISCOUNTS - 1)
			{
				strcpy(buf, "Zu viele cppediscounts-Saetze fuer Artikel im angegebenen Zeitraum gefunden. ");
				SqlCloseCs(fd_sel_cppediscounts);
				return -1;
			}
		}
	} while (s == 0);

	if (s != 0 && s != 100)
	{
		strcpy(buf, "CPPEDISCOUNTS\n");
		strcat(buf, DynErrmld());
		SqlCloseCs(fd_sel_cppediscounts);
		return s;
	}

	SqlCloseCs(fd_sel_cppediscounts);

	/* dass kein cppediscounts-Satz gefunden wird, kann nicht vorkommen, da wir
   	   von vornherein nur Artikel verarbeiten, fuer die mindestens ein cppediscounts-
	   Satz im Zeitintervall existiert
	   --> trotzdem abfangen, schadet ja nicht */
	if (s == 100)
	{
		if (i == 0)
		{
			strcpy(buf, "Keine cppediscounts-Saetze fuer den Artikel im angegebenen Zeitraum vorhanden. ");
		}
		else
		{
			/* Endemarker im cppediscounts-Array setzen */
			cppediscounts[i + 1].ARTICLENO = 0;
			s = 0;
		}
	}

#ifdef _DEBUG
//	printf("--> ReadCppediscounts(), s = %ld\n", s);
#endif // 

	return s;
}

/* ---------------------------------------- */
static int GetCppediscounts(long artikel_nr, long datumab, long datumbis, struct CPPEDISCOUNTS* cppediscounts, PPE_PROCESSING_TYPE* pProcessingType, char *buf)
{
	long s = 0;
	int index_result = -1;
	int i = 0;
	int max_datumbis = 0;
	int index_max_datumbis = -1;

	/* lies alle CPPEDISCOUNTS Einträge des Artikels im relevanten Datumsbereich
	   normalerweise finden wir hier genau einen Eintrag, ein einigen wenigen 
	   seltenen Konstellationen mehr als einen */
	s = ReadCppediscounts(artikel_nr, datumab, datumbis, BufCppediscountsList, buf);
	if (s != 0)
	{
		return s;
	}

	/* haben wir einen Lösch-Eintrag gefunden? 
	   falls einen solchen gibt, erhalten wir ihn als ersten Eintrag, das wird
	   durch das ORDER BY des SELECTs sichergestellt */
	if (BufCppediscountsList[0].CHANGECODEID == 1)
	{
		/* dann geben wir diesen als Ergebnis zurueck */
		/* im Löschfall sind die Datumswerte im Eintrag nicht relevant, ein
		   Lösch-Eintag kann auch nicht sinnvoll mit anderen Einträgen 
		   kombiniert werden; falls es solche gibt, ignorieren wir sie */
		index_result = 0;
		*pProcessingType = PPT_DELETION;
	}
	else
	{
		/* es liegen nur CPPEDISCOUNTS-Einträge für Änderungen oder Auslaufen
		   vor (CHANGECODEID = 0)
		   wir müssen nur den mit den größten Gültigkeitsdatum im Selektions-
		   Zeitraum betrachten, alle anderen sind nicht mehr relevant; falls
		   ein Änderungseintrag relevant ist, erhalten wir ihn als erstes (das
		   wird durch ORDER BY im SELECT sichergestellt)
		   Wir gehen die evtl. vorhandenen Auslauf-Einträge (= DATETO liegt im 
		   Selektions-Zeitraum) durch und ermitteln den mit dem größten DATETO-
		   Wert - wenn dieser Wert nach dem DATEFROM-Wert des Änderungseintrags
		   liegt, ist der Auslauf-Eintrag relevant und verarbeiten diesen,
		   andernfalls verarbeiten wir den Änderungs-Eintrag */
		i = 0;
		do {
			if (BufCppediscountsList[i].DATETO >= datumab
				&& BufCppediscountsList[i].DATETO < datumbis
				&& BufCppediscountsList[i].DATETO > max_datumbis)
			{
				max_datumbis = BufCppediscountsList[i].DATETO;
				index_max_datumbis = i;
			}
			i++;
		} while (BufCppediscountsList[i].ARTICLENO != 0);

		/* wenn der erste CPPEDISCOUNTS-Eintrag in der Liste KEIN Auslauf-Eintrag 
		   (also ein Aenderungs-Eintrag) ist und sein DATEFROM-Wert groesser 
		   als das ermittelte maximale Auslaufdatum ist, dann verarbeiten 
		   wir den Aenderungs-Eintrag */
		if (   (! (BufCppediscountsList[0].DATETO >= datumab && BufCppediscountsList[0].DATETO < datumbis))
			&& BufCppediscountsList[0].DATEFROM > max_datumbis)
		{
			index_result = 0;
			*pProcessingType = PPT_UPDATE;
		}
		else
		{
			/* ansonsten "gewinnt" der Auslauf-Eintrag mit dem groessten 
			   DATETO-Wert und wir verarbeiten diesen */
			index_result = index_max_datumbis;
			*pProcessingType = PPT_EXPIRATION;
		}
	}

	*cppediscounts = BufCppediscountsList[index_result];

	return s;
}

/* ---------------------------------------- */
static int UpdateExpirationCppediscounts(long artikel_nr, long datumab, long datumbis, char *buf)
{
	/* setze in allen CPPEDISCOUNTS-Einträgen des Artikels, deren Ablaufdatum 
	   im Selektionsintervall liegt, die CHANGECODEID auf -2, um die Verarbeitung 
	   des Ablaufs zu quittieren */
	sprintf(buf,
		"update cppediscounts "
		"set changecodeid = -2, lastchangedate = current "
		"where articleno = %ld "
		"and changecodeid = 0 "
		"and dateto >= %ld "
		"and dateto < %ld",
		artikel_nr,
		datumab,
		datumbis
	);

	return SqlExecuteImm(buf);
}

/* ---------------------------------------- */
static int UpdateDeletionCppediscounts(long artikel_nr, char *buf)
{
	/* setze in allen CPPEDISCOUNTS-Lösch-Einträgen des Artikels (mit CHANGECODEID = 1)
	   die CHANGECODEID auf -1, um die Verarbeitung der Löschung zu quittieren;
	   die Datumswerte werden dabei nicht ausgewertet, bei Löschungen enthalten 
	   diese die unveränderten Werte des gelöschten Eintrags und können nicht 
	   zur Selektion herangezogen werden */
	sprintf(buf,
		"update cppediscounts "
		"set changecodeid = -1, lastchangedate = current "
		"where articleno = %ld "
		"and changecodeid = 1",
		artikel_nr
	);

	return SqlExecuteImm(buf);
}

/* ---------------------------------------- */
static int ReadImportParam( char *buf )
{
	long s;

	strcpy( buf, "SELECT grosso_increasepct, aep_increasepct FROM cimportarticleparam WHERE country_ifacode = 'D'"); // parameter would be fine!
	
	s = SqlRead( buf, &gep_increase_pct, &aep_increase_pct, NULL ); 
	
	if ( s != 0 )
		strcpy( buf, DynErrmld());
		
	return s;
}

/* ---------------------------------------- */
static long CalcAndStore( char *buf )
{
	long s = 0;
	double tempPrice = 0.0;
	
	if ( mode == MODE_AVPS ) // AVP´s
	{
		// die zwei folgenden if´s sind eigentlich überflüssig, da bereits vorher Vorauswahl getroffen wurde!
		if ( strcmp(BufPreis.KE_MWST, ke_mwst ) == 0 )
		{
			if ( strcmp ( BufArtikel.TAXPFL, ART_IS_TAXPFL_1 ) == 0 || 
				 strcmp ( BufArtikel.TAXPFL, ART_IS_TAXPFL_2 ) == 0 )
			{
				//Tax-Artikel
				CalcAvk( BufPreis.AEP, &BufPreis.AVP, mwst_neu, datgueltab, BufArtikel.TAXPFL[0] );
				
			/* else - keine Berechnung von Nicht-Tax-Artikeln !!!
			{
				//  Nichttax-Artikel
				tempPrice = BufPreis.AVP / ((mwst_alt + 100) / 100 );	// : 1,16
				Runden_Modf( &tempPrice, 2 );
				BufPreis.AVP = tempPrice * ((mwst_neu + 100) / 100 );	// * 1,19	
				Runden_Modf( &tempPrice, 2 );
			}*/

				BufPreis.DATUMGUELTIGAB = datgueltab;
				
				s = StoreRecord_ZartPreis ( buf );
				++anz_calculated;
			}
		}
	}
	else if ( mode == MODE_FESTPR ) // Festpreise
	{
		// folgendes if eigentlich überflüssig, da bereits vorher Vorauswahl getroffen wurde!
		if ( strcmp(BufPreis.KE_MWST, ke_mwst ) == 0 )
		{
			tempPrice = BufArtikel.FESTBETRAG1 / ((mwst_alt + 100) / 100 );	// : 1,16
			Runden_Modf( &tempPrice, 2 );
			BufArtikel.FESTBETRAG1 = tempPrice * ((mwst_neu + 100) / 100 );	// * 1,19	
			Runden_Modf( &BufArtikel.FESTBETRAG1, 2 );

			BufArtikel.DATUM_FESTBETRAG1 = datum_fb1;

			s = StoreRecord_Zartikel( buf );
			++anz_calculated;
		}
	}
	else if ( mode == MODE_AVP_WITHOUT_TAX ) // AVP´s ohne Taxen
	{
		// folgendes if eigentlich überflüssig, da bereits vorher Vorauswahl getroffen wurde!
		if ( strcmp(BufPreis.KE_MWST, ke_mwst ) == 0 )
		{
			if ( BufPreis.HERST_PROZENT > 0.0 )
			{
				tempPrice = BufPreis.AEP + (BufPreis.HERST_PROZENT * BufPreis.AEP / 100.0);
				BufPreis.AVP = tempPrice + (tempPrice * mwst_neu / 100.0);
				Runden_Modf( &BufPreis.AVP, 2 );
			}
			else
			{
				tempPrice = BufPreis.AVP / ((mwst_alt + 100) / 100 );	// : 1,22
				//Runden_Modf( &tempPrice, 2 );
				BufPreis.AVP = tempPrice * ((mwst_neu + 100) / 100 );	// * 1,23
				Runden_Modf( &BufPreis.AVP, 2 );
			}

			BufPreis.DATUMGUELTIGAB = datgueltab;
			
			s = StoreRecord_ZartPreis ( buf );
			++anz_calculated;
		}
	}
	else if ( mode == MODE_AMNOG ) // Amnog
	{
		// folgendes if eigentlich überflüssig, da bereits vorher Vorauswahl getroffen wurde!
		if ( strcmp(BufArtikel.TAXPFL, tax_kz ) == 0 )
		{
			// Neuberechnung AEP nach AMNOG
			CalcAek( BufPreis.GROSSO, &BufPreis.AEP, datgueltab, BufArtikel.TAXPFL[0] );

			// Berechnung AVP aus neuem AEP
			CalcAvk( BufPreis.AEP, &BufPreis.AVP, mwst_neu, datgueltab, BufArtikel.TAXPFL[0] );

			BufPreis.DATUMGUELTIGAB = datgueltab;
			
			s = StoreRecord_ZartPreis ( buf );
			++anz_calculated;
		}
	}
	else if ( mode == MODE_AVP_TAX ) // Tax-Umstellung D 2013
	{
		// folgendes if eigentlich überflüssig, da bereits vorher Vorauswahl getroffen wurde!
		if ( strcmp(BufArtikel.TAXPFL, tax_kz ) == 0 )
		{
			// Berechnung AVP aus neuem AEP
			CalcAvk( BufPreis.AEP, &BufPreis.AVP, mwst_neu, datgueltab, BufArtikel.TAXPFL[0] );

			BufPreis.DATUMGUELTIGAB = datgueltab;
			
			s = StoreRecord_ZartPreis ( buf );
			++anz_calculated;
		}
	}
	else if ( mode == MODE_GROSSO_LBP ) // Grosso aus LBP (CH)
	{
		PPE_PROCESSING_TYPE processingType;
		double	disc_value = 0.0;
		long	disc_datefrom = 0;

		/* ermittle den CPPEDISCOUNTS-Eintrag, der den spaetestens ab datgueltbis gueltigen Rabatt definiert */
		s = GetCppediscounts( BufArtikel.ARTIKEL_NR, datgueltab, datgueltbis, &BufCppediscounts, &processingType, buf );

		if (s == 0)
		{
			/* Rabattwert nur uebernehmen, wenn wirklich eine Rabattänderung (CHANGECODEID = 0) 
			   vorliegt; bei einer Löschung oder einem Ablauf setzen wir den Rabatt auf 0 */
			if ( processingType == PPT_UPDATE )
			{
				disc_value = BufCppediscounts.PPETOTALDISCPCT;
				disc_datefrom = BufCppediscounts.DATEFROM;
			}
			else if (processingType == PPT_EXPIRATION)
			{
				disc_value = 0.0;
				/* der Rabatt laeuft an DATETO ab, d.h. der neue Rabatt von 0
				   gilt ab dem darauf folgenden Tag */
				disc_datefrom = AddDayToPhoDate(BufCppediscounts.DATETO, 1);
			}
			else
			{
				disc_value = 0.0;
				/* bei einer Loeschung ist DATETO das Datum, bis zu dem der Rabatt 
				   urspruenglich galt, es ist NICHT das Datum, zu dem die Loeschung 
				   greift
				   --> Annahme: der neue Rabatt von 0 gilt ab dem naechsten Arbeitstag */
				disc_datefrom = datgueltbis;
			}
	        
			// SR-17017244: Lt. Fr. Fretz herst_prozent sofort (nicht erst bei erreichen des Gültigkeitsdatums aus PPE) setzen
			// if (ppe_date <= datgueltbis)
			{
				BufArtikel.HERST_PROZENT = disc_value;
				s = StoreRecord_Zartikel( buf );
			}

			if (s == 0)
			{
				// Preis nur updaten, wenn wir auch tatsaechlich einen gefunden haben
				if (BufPreis.ARTIKEL_NR > 0)
				{
					if ( ComputeGrosso(disc_value, disc_datefrom, processingType, &BufPreis) )
					{
						s = StoreRecord_ZartPreis(buf);
						++anz_calculated;
					}
				}

				/* wir muessen auch alle zukünftigen ZARTPREIS-Eintraege mit dem aktuellen
				   Rabatt aktualisieren */
				s = UpdateFutureZartpreis(BufArtikel.ARTIKEL_NR, disc_datefrom, disc_value, processingType, buf);

				if (processingType == PPT_DELETION)
				{
					/* vearbeiteten CPPEDISCOUNTS-Eintrag quittieren */
					s = UpdateDeletionCppediscounts(BufArtikel.ARTIKEL_NR, buf);
				}
				else
				{
					/* alle CPPEDISCOUNTS-Eintraege fuer auslaufende Rabatte im 
					   Selektionsintevall quittieren 
					   (das kann (theoretisch) mehr als einer sein, die wir alle 
					   quittieren muessen, auch wenn wir nur den mit hoechsten 
					   DATETO-Datum wirklich verarbeiten; und es kann auch (wieder 
					   theoretisch) bei Verarbeitung eines Updates noch zusaetzlich 
					   Einträge für auslaufende Rabatte im Selektionsintervall geben,
					   auch diese muessen quittiert werden */
					s = UpdateExpirationCppediscounts( BufArtikel.ARTIKEL_NR, datgueltab, datgueltbis, buf );
				}
			}
		}
	}
		
	return s;
}

/* ---------------------------------------- */
static long Calculate( long artikel_nr, char *buf )
{
	long s;
		
	s = GetBufferDesc_Zartpreis	( buf );
	if ( s != 0 )
		return s;
	
	s = GetBufferDesc_Zartikel	( buf );
	if ( s != 0 )
		return s;

	s = ReadRecord_ZartPreisCurrent ( artikel_nr, buf );
	
	/* bei GROSSO-Berechnung muessen wir CalcAndStore() auch aufrufen, 
	   wenn wir keinen aktuellen Preis finden, da wir evtl. vorhandene
	   zukuenftige Preise updaten muessen */
	if ( s == 0 
		 || (s = 100 && mode == MODE_GROSSO_LBP) )
		s = CalcAndStore ( buf );
	else if ( s == 100 )
		s = 0; 	// kein alter / aktueller Preissatz vorhanden
			
	return s;
}

/* ---------------------------------------- */
static long CalcArticle( long artikel_nr, char *buf )
{
   long s;

   s = Calculate( artikel_nr, buf );
   
   if ( s == 0 )
	   s = FdTransactWithoutWork( buf );

   return s;
}

/* ---------------------------------------- */
static long CalcRefundArticle( long artikel_nr, char *buf )
{
	long s;
	char PrimeKeyCond[100];
	char sql [500];
	
	s = GetBufferDesc_Zartfrance ( buf );
	if ( s != 0 )
		return s;
	
	s = GetBufferDesc_Cartrefundfrance ( buf );
	if ( s != 0 )
		return s;

	sprintf( PrimeKeyCond, "ARTICLENO=%7ld", BufZartfrance.ARTICLENO );

	/* nicht mehr nötig, wird über zpdailyclosing abgewickelt:
	if ( BufCartrefundfrance.REIMBURSEMENT_TYPE[0] == '9' )
	{
		if (BufZartfrance.REIMBURSEMENT_PERC > 0 && BufZartfrance.REIMBURSEMENT_TYPE[0] == '3' )
		{
		// hier für bestimmten Typ 9 ( = aus zputil bei Änderung AVP gesetzt) nicht die Werte aus cartrefundfrance übernehmen, 
		// sondern wenn zartfrance.REIMBURSEMENT_TYPE=3 mit aktuellem zartfrance.REIMBURSEMENT_PERC * neuen AVP den neuen zartfrance.reimbursement_val berechnen
			double avp = 0.0;
			double pct = 0.0;
		
			sprintf( sql, "select avp, reimbursement_pct from ZARTPREIS, creimbursement_pct where ARTIKEL_NR=%ld and DATUMGUELTIGAB=%ld and REIMBURSEMENT_PCT_ID=%lf "
						, BufZartfrance.ARTICLENO, BufCartrefundfrance.DATEFROM, BufZartfrance.REIMBURSEMENT_PERC);

			s = SqlRead(sql, &avp, &pct, NULL);

			if (s == 0)
			{
				BufZartfrance.REIMBURSEMENT_VAL = avp * pct / 100;

				s = FdDelayUpdateRecord( fd_zartfrance, &BufZartfrance, &BufZartfranceOld, PrimeKeyCond, buf);
			}

			if (s == 0)
				++anz_calculated;
		}
	}
	else */
	{
		BufZartfrance.REIMBURSEMENT_PERC		= BufCartrefundfrance.REIMBURSEMENT_PERC;
		BufZartfrance.REIMBURSEMENT_TYPE[0]		= BufCartrefundfrance.REIMBURSEMENT_TYPE[0];
		BufZartfrance.TFR_BASE_PRICE			= BufCartrefundfrance.TFR_BASE_PRICE;
		//strncpy (BufZartfrance.CODE_LPPR, BufCartrefundfrance.CODE_LPPR, L_ZARTFRANCE_CODE_LPPR);

		if (BufZartfrance.REIMBURSEMENT_TYPE[0] == '2')
		{
			// bei LPPR- Erstattung den Erstattungswert bei Übernahme cartrefundfrance -> zartfrance nochmal neu berechnen, da sich die Werte der Berechnungsgrundlage geändert haben könnten:
			double val = 0.0;
			sprintf( sql, "select sum(reimbursement_val) from clppr2article a, outer clpprreimb r where articleno = %ld "
				" and a.code_lppr = r.code_lppr and reimbcalcflag = 1 "
				" and a.datefrom <= %ld "
				" and  r.datefrom  = (select max(datefrom) from clpprreimb where code_lppr = a.code_lppr and datefrom <= %ld)", BufZartfrance.ARTICLENO, datgueltab, datgueltab);

			s = SqlRead(sql, &val, NULL);

			if (s == 0)
				BufZartfrance.REIMBURSEMENT_VAL	= val;
		}
		else
			BufZartfrance.REIMBURSEMENT_VAL	= BufCartrefundfrance.REIMBURSEMENT_VAL;
		
		
		s = FdDelayUpdateRecord( fd_zartfrance, &BufZartfrance, &BufZartfranceOld, PrimeKeyCond, buf);

		if (s == 0)
			++anz_calculated;
	}

	if (s == 0)
	{
		s = FdDelayDeleteRecord( fd_cartrefundfrance, &BufCartrefundfrance, PrimeKeyCond, buf);

		if ( s == 0 )
		{
			++anz_deleted;

			s = FdTransactWithoutWork( buf );
		}
	}

	return s;
}

/* ---------------------------------------- */
static long CalcAll( char *buf )
{
   long s;
   char z_buf[151];
   int fd_sel_zartikel = -1;

#ifdef _DEBUG
   printf("--> CalcAll()\n");
#endif // 

   if ( mode == MODE_AVPS )
   {
		sprintf( buf,
            "select %s from ZARTIKEL, ZARTPREIS where ZARTIKEL.ARTIKEL_NR = ZARTPREIS.ARTIKEL_NR "
			"and ZARTPREIS.KE_MWST = '%s' and ZARTPREIS.DATUMGUELTIGAB = "
			"(select max(DATUMGUELTIGAB) from ZARTPREIS where ARTIKEL_NR = ZARTIKEL.ARTIKEL_NR and "
			"DATUMGUELTIGAB <= %ld) and TAXPFL != '0'",	// Nicht-Tax-Artikel werden nicht berechnet!
			JOIN_PROJECTION_ZARTIKEL,
			ke_mwst,
			datgueltab
			);
   }
   else if ( mode == MODE_FESTPR )
   {
		sprintf( buf,
            "select %s from ZARTIKEL, ZARTPREIS where ZARTIKEL.ARTIKEL_NR = ZARTPREIS.ARTIKEL_NR "
			"and ZARTPREIS.KE_MWST = '%s' and ZARTPREIS.DATUMGUELTIGAB = "
			"(select max(DATUMGUELTIGAB) from ZARTPREIS where ARTIKEL_NR = ZARTIKEL.ARTIKEL_NR and "
			"DATUMGUELTIGAB <= %ld) and FESTBETRAG1 != 0.0",
			JOIN_PROJECTION_ZARTIKEL,
			ke_mwst,
			datgueltab
			);	  
   }
   else if ( mode == MODE_AVP_WITHOUT_TAX )
   {
	 	 sprintf( buf,
            "select %s from ZARTIKEL, ZARTPREIS where ZARTIKEL.ARTIKEL_NR = ZARTPREIS.ARTIKEL_NR "
			"and ZARTPREIS.KE_MWST = '%s' and ZARTPREIS.DATUMGUELTIGAB = "
			"(select max(DATUMGUELTIGAB) from ZARTPREIS where ARTIKEL_NR = ZARTIKEL.ARTIKEL_NR and "
			"DATUMGUELTIGAB <= %ld) and ZARTPREIS.AVP > 0.0 ",	// Artikel ohne AVP werden nicht berechnet!
			JOIN_PROJECTION_ZARTIKEL,
			ke_mwst,
			datgueltab
			);
   }
   else if ( mode == MODE_AMNOG )
   {
		// nur Artikel, die nicht von IFA geliefert werden (zifaart)
		// außerdem nur die Artikel selektieren, die grosso > 0 && grosso != aep haben

	   sprintf( buf,
			"select %s from ZARTIKEL, ZARTPREIS where ZARTIKEL.ARTIKEL_NR = ZARTPREIS.ARTIKEL_NR "
			"and ZARTIKEL.TAXPFL = '%s' and ZARTPREIS.DATUMGUELTIGAB = "
			"(select max(DATUMGUELTIGAB) from ZARTPREIS where ARTIKEL_NR = ZARTIKEL.ARTIKEL_NR and "
			"DATUMGUELTIGAB <= %ld) "
			"and zartpreis.grosso > 0 and zartpreis.grosso != zartpreis.aep and zartikel.artikel_nr not in ("
			"select a00pzn from zifaart)",	
			JOIN_PROJECTION_ZARTIKEL,
			tax_kz,
			datgueltab
			);
   }
   else if ( mode == MODE_AVP_TAX )
   {
		// nur Tax- Artikel, die nicht von IFA geliefert werden (zartikel.datum_ifaloesch)
		
	   sprintf( buf,
			"select %s from ZARTIKEL, ZARTPREIS where ZARTIKEL.ARTIKEL_NR = ZARTPREIS.ARTIKEL_NR "
			"and ZARTIKEL.TAXPFL = '%s' and ZARTPREIS.DATUMGUELTIGAB = "
			"(select max(DATUMGUELTIGAB) from ZARTPREIS where ARTIKEL_NR = ZARTIKEL.ARTIKEL_NR and "
			"DATUMGUELTIGAB <= %ld) "
			"and zartikel.datum_ifaloesch > 0 ",	
			JOIN_PROJECTION_ZARTIKEL,
			tax_kz,
			datgueltab
			);
   }
   else if ( mode == MODE_GROSSO_LBP )
   {
	   /* zcalcprice wird mit 2 Datumsparametern aufgerufen; fuer die GROSSO_LBP Berechnung haben 
	      diese folgende Bedeutung:
		     datgueltab:  Heute, d.h. der Tag, an dem die Berechnung stattfindet
			              die GROSSO-Berechnung erfolgt am Ende des Tages, d.h. 
						  der heutige Tag ist abgeschlossen
			 datgueltbis: der naechste Arbeitstag; normalerweise ein Tag spaeter 
			              als datgueltab, aber im Falle von Wochenenden und/oder 
						  Feiertagen auch mehr als ein Tag spaeter
	      Fuer die GROSSO-Berechnung muessen wir ermitteln, welche neuen bzw. geaenderten Rabatte 
		  ab dem naechsten Arbeitstag gelten; diese werden fuer uns von PPE in die Tabelle 
		  CPPEDISCOUNTS geschrieben, jeweils mit dem Datum, ab dem (DATEFROM) bzw. bis zu dem
		  (DATETO) sie gueltig sind; für die Verarbeitung selektieren wir alle CPPEDISCOUNTS
		  Eintraege, die innerhalb des vorgegebenen Datumsintervalls gueltig werden 
		  (datgueltbis >= DATEFROM > datgueltab; DATEFROM muss groesser als datgueltab sein,
		  gleich datgueltab waere irrelevant, da "heute" bereits abgeschlossen ist; ein 
		  Rabatt mit DATEFROM = datgueltab muss im gestrigen Verarbeitungslauf verarbeitet
		  worden sein) oder die innerhalb des Datumsintervalls ablaufen 
		  (datgueltbis > DATETO >= datgueltab; hier ist die Selektionslogik etwas anders,
		  ein Rabatt mit DATETO = datgueltab galt heute noch, erst ab morgen ist er ab-
		  gelaufen, d.h. er muss im heutigen Lauf beruecksichtigt werden; entsprechend
		  darf ein Rabatt mit DATETO = datgueltbis im heutigen Lauf NICHT vearbeitet 
		  werden, da her an datgueltbis noch gilt - er darf erst im morgigen Lauf
		  beruecksichtigt werden)
		  Wir selektieren hier erstmal alle Artikel, zu denen es im vorgegebenen Zeit-
		  intervall einen zu verarbeitenden Rabatt gibt, iterieren ueber alle gefundenen
		  Artikel und selektieren dann spaeter in CalcAndStore() den/die relevanten 
		  CPPEDISCOUNTS-Eintrag/-Eintraege zu jedem Artikel */
	   sprintf( buf,
		   "select %s "
		   "from zartikel a "
		   "where exists ("
		   "select articleno from cppediscounts "
		   "where articleno = a.artikel_nr "
		   "and ((changecodeid = 0 "
		   "      and (    (datefrom > %ld and datefrom <= %ld) "
		   "            or (dateto >= %ld and dateto < %ld) "
		   "          ) "
		   "     ) "
		   "     or changecodeid = 1)"
		   ")",
		   PROJECTION_ZARTIKEL,
		   datgueltab,
		   datgueltbis,
		   datgueltab,
		   datgueltbis
	   );
   }

   s = SqlOpenCsWh( &fd_sel_zartikel, buf );

   if ( s != 0 )
   {
     strcpy( buf, "ZARTIKEL\n" );
     strcat( buf, DynErrmld() );
     return s;
   }

   s = SqlFetch( fd_sel_zartikel, 1, &BufArtikel, NULL );
   
   if ( s != 0 )
   {
		strcpy( buf, "ZARTIKEL\n" );
		strcat( buf, DynErrmld() );
		SqlCloseCs( fd_sel_zartikel );

		if (s == 100) //nix zum Umrechnen vorhanden!
			s = 0;

		return s;
   }
   
   BufArtikelOld = BufArtikel;

   if ( mode != MODE_GROSSO_LBP )
   {
		s = ReadMwst ( buf );
		
		if ( s != 0 )
			return s;
   }
     
   Init( );

//--- start transaction
   s = SqlBeginWork();
   if ( s != 0 )
   {
		strcpy( buf, DynErrmld() );
		return -1;
   }
   
   while ( s == 0 )
   {
	    s = CalcArticle( BufArtikel.ARTIKEL_NR, buf );

		if ( s == 0 )
		{
			s = SqlFetch( fd_sel_zartikel, 1, &BufArtikel, NULL );
	         
			if ( s != 0 )
			{
				strcpy( buf, "ZARTIKEL\n" );
				strcat( buf, DynErrmld() );
			}
			else
				BufArtikelOld = BufArtikel;
		}
   }

   Free( );

   SqlCloseCs( fd_sel_zartikel );

   if ( s == 100 )
      s = 0;
   
//--- end transaction
   if ( s == 0 )
   {
      s = SqlCommitWork();
      
	  if ( s != 0 )
         strcpy( buf, DynErrmld() );
   }
   else
      SqlRollbackWork();


   if ( s == 0 )
   {
		strcpy( buf, "Umrechnung erfolgreich. " );
   	
		if ( mode == MODE_AVPS || mode == MODE_AVP_WITHOUT_TAX || mode == MODE_AVP_TAX )
			sprintf( z_buf, "\nEs wurden die AVP´s von %ld Artikeln umgerechnet.", anz_calculated );
		else if ( mode == MODE_FESTPR )
			sprintf( z_buf, "\nEs wurden die Festpreise von %ld Artikeln umgerechnet.", anz_calculated );
		else if ( mode == MODE_AMNOG )
			sprintf( z_buf, "\nEs wurden die Preise von %ld Artikeln nach AMNOG umgerechnet.", anz_calculated );
		else if ( mode == MODE_GROSSO_LBP )
			sprintf( z_buf, "\nEs wurde der Grosso von %ld Artikeln aus LBP neu errechnet.", anz_calculated );
   }

#ifdef _DEBUG
   printf("<-- CalcAll()\n");
#endif // 

   strcat( buf, z_buf );
   return s;
}

/* ---------------------------------------- */
static long CalcRefundSingle( long artikel_nr, long datefrom, long dateto, char *buf )
{
	long s;

	sprintf( buf,
			"select %s from CARTREFUNDFRANCE "
			"where ARTICLENO = %ld and DATEFROM >= %ld and DATEFROM <= %ld",
			PROJECTION_CARTREFUNDFRANCE,
			artikel_nr, datefrom, dateto
			);

	s = SqlRead( buf, &BufCartrefundfrance, NULL ); 
   
	if ( s == 100 )
	{
		strcpy( buf, "kein Eintrag mit entsprechendem Datum in cartrefundfrance vorhanden" );
		return 0;
	}

	if ( s != 0 )
	{
		strcpy( buf, "CARTREFUNDFRANCE\n" );
		strcat( buf, DynErrmld() );
		return s;
	}

	sprintf( buf,
			"select %s from ZARTFRANCE "
			"where ARTICLENO = %ld",
			PROJECTION_ZARTFRANCE,
			artikel_nr
			);

	s = SqlRead( buf, &BufZartfrance, NULL ); 
   
	if ( s == 100 )
	{
		strcpy( buf, "kein Eintrag in zartfrance vorhanden" );
		return 0;
	}

	if ( s != 0 )
	{
		strcpy( buf, "ZARTFRANCE\n" );
		strcat( buf, DynErrmld() );
		return s;
	}
	else
		BufZartfranceOld = BufZartfrance; 

	InitRefund( );

	//--- start transaction
	s = SqlBeginWork();
	if ( s != 0 )
	{
		strcpy( buf, DynErrmld() );
		return -1;
	}
   
	s = CalcRefundArticle( artikel_nr, buf );

	FreeRefund( );

	//--- end transaction
	if ( s == 0 )
	{
		s = SqlCommitWork();
      
		if ( s != 0 )
			strcpy( buf, DynErrmld() );
	}
	else
		SqlRollbackWork();

	if ( s == 0 )
		strcpy( buf, "Übertragung des uebergebenen Artikels erfolgreich." );
 
	return s;
}

/* ---------------------------------------- */
static long CalcRefundAll( long datefrom, long dateto, char *buf )
{
	long s;
	long artikel_nr;
	char z_buf[151];
	int fd_sel_zapflege = -1;

	sprintf( buf,
			"select DISTINCT ARTIKEL_NR from ZAPFLEGE "
			"where DATUM >= %ld and DATUM <= %ld",
			datefrom, dateto
			);
   	s = SqlOpenCsWh( &fd_sel_zapflege, buf );

	if ( s != 0 )
	{
		strcpy( buf, "ZAPFLEGE\n" );
		strcat( buf, DynErrmld() );
		return s;
	}

	s = SqlFetch( fd_sel_zapflege, 1, &artikel_nr, NULL );
   
	/* gar kein zapflege-Satz ist zwar unwahrscheinlich, aber kein Fehler */
	if ( s == 100 )
	{
		strcpy( buf, "keine zapflege-Saetze im angegebenen Zeitraum vorhanden. " );
		return 0;
	}

	if ( s != 0 )
	{
		strcpy( buf, "ZAPFLEGE\n" );
		strcat( buf, DynErrmld() );
		SqlCloseCs( fd_sel_zapflege );

		return s;
	}

	while ( s == 0 )
	{
		s = CalcRefundSingle( artikel_nr, datefrom, dateto, buf );

		if ( s == 0 )
		{
			s = SqlFetch( fd_sel_zapflege, 1, &artikel_nr, NULL );
			
			if ( s != 0 )
			{
				strcpy( buf, "ZAPFLEGE\n" );
				strcat( buf, DynErrmld() );
			}
		}
	}

	SqlCloseCs( fd_sel_zapflege );

	if ( s == 100 )
		s = 0;
   
	if ( s == 0 )
	{
		strcpy( buf, "Umrechnung erfolgreich. " );

		sprintf( z_buf, "\nEs wurden die Werte von %ld Artikeln in zartfrance uebertragen und \n%ld Saetze aus cartrefundfrance geloescht.", anz_calculated, anz_deleted );
   }

   strcat( buf, z_buf );
   return s;
}

/* ---------------------------------------- */
static long CalcSingle( long artikel_nr, char *buf )
{
   long s;

   if ( mode == MODE_AVPS )
   {
		sprintf( buf,
            "select %s from ZARTIKEL, ZARTPREIS where ZARTIKEL.ARTIKEL_NR = ZARTPREIS.ARTIKEL_NR "
			"and ZARTPREIS.KE_MWST = '%s' and ZARTPREIS.DATUMGUELTIGAB = "
			"(select max(DATUMGUELTIGAB) from ZARTPREIS where ARTIKEL_NR = ZARTIKEL.ARTIKEL_NR and "
			"DATUMGUELTIGAB <= %ld) and TAXPFL != '0' and ZARTIKEL.ARTIKEL_NR = %ld",	// Nicht-Tax-Artikel werden nicht berechnet!
			JOIN_PROJECTION_ZARTIKEL,
			ke_mwst,
			datgueltab,
			artikel_nr
			);
   }
   else if ( mode == MODE_FESTPR )
   {
		sprintf( buf,
            "select %s from ZARTIKEL, ZARTPREIS where ZARTIKEL.ARTIKEL_NR = ZARTPREIS.ARTIKEL_NR "
			"and ZARTPREIS.KE_MWST = '%s' and ZARTPREIS.DATUMGUELTIGAB = "
			"(select max(DATUMGUELTIGAB) from ZARTPREIS where ARTIKEL_NR = ZARTIKEL.ARTIKEL_NR and "
			"DATUMGUELTIGAB <= %ld) and FESTBETRAG1 != 0.0 and ZARTIKEL.ARTIKEL_NR = %ld",
			JOIN_PROJECTION_ZARTIKEL,
			ke_mwst,
			datgueltab,
			artikel_nr
			);	  
   }
   else if ( mode == MODE_AVP_WITHOUT_TAX )
   {
	   	sprintf( buf,
            "select %s from ZARTIKEL, ZARTPREIS where ZARTIKEL.ARTIKEL_NR = ZARTPREIS.ARTIKEL_NR "
			"and ZARTPREIS.KE_MWST = '%s' and ZARTPREIS.DATUMGUELTIGAB = "
			"(select max(DATUMGUELTIGAB) from ZARTPREIS where ARTIKEL_NR = ZARTIKEL.ARTIKEL_NR and "
			"DATUMGUELTIGAB <= %ld) and ZARTPREIS.AVP > 0.0 and ZARTIKEL.ARTIKEL_NR = %ld",	// Artikel ohne AVP werden nicht berechnet!
			JOIN_PROJECTION_ZARTIKEL,
			ke_mwst,
			datgueltab,
			artikel_nr
			);
   }
   else if ( mode == MODE_AMNOG )
   {
	   	sprintf( buf,
			"select %s from ZARTIKEL, ZARTPREIS where ZARTIKEL.ARTIKEL_NR = ZARTPREIS.ARTIKEL_NR "
			"and ZARTIKEL.TAXPFL = '%s' and ZARTPREIS.DATUMGUELTIGAB = "
			"(select max(DATUMGUELTIGAB) from ZARTPREIS where ARTIKEL_NR = ZARTIKEL.ARTIKEL_NR and "
			"DATUMGUELTIGAB <= %ld) and ZARTIKEL.ARTIKEL_NR = %ld "
			"and zartpreis.grosso > 0 and zartpreis.grosso != zartpreis.aep and zartikel.artikel_nr not in ("
			"select a00pzn from zifaart)",	
			JOIN_PROJECTION_ZARTIKEL,
			tax_kz,
			datgueltab,
			artikel_nr
			);
   }
   else if ( mode == MODE_AVP_TAX )
   {
		// nur Tax- Artikel, die nicht von IFA geliefert werden (zartikel.datum_ifaloesch)
		
	   sprintf( buf,
			"select %s from ZARTIKEL, ZARTPREIS where ZARTIKEL.ARTIKEL_NR = ZARTPREIS.ARTIKEL_NR "
			"and ZARTIKEL.TAXPFL = '%s' and ZARTPREIS.DATUMGUELTIGAB = "
			"(select max(DATUMGUELTIGAB) from ZARTPREIS where ARTIKEL_NR = ZARTIKEL.ARTIKEL_NR and "
			"DATUMGUELTIGAB <= %ld)  and ZARTIKEL.ARTIKEL_NR = %ld "
			"and zartikel.datum_ifaloesch > 0 ",	
			JOIN_PROJECTION_ZARTIKEL,
			tax_kz,
			datgueltab,
			artikel_nr
			);
   }
   else if ( mode == MODE_GROSSO_LBP )
   {
	     /* zur Selektionslogik s. Kommentar in CalcAll() */
		 sprintf(buf,
			 "select %s "
			 "from zartikel a "
			 "where artikel_nr = %ld "
			 "and exists ("
			 "select articleno from cppediscounts "
			 "where articleno = a.artikel_nr "
			 "and ((changecodeid = 0 "
			 "      and (    (datefrom > %ld and datefrom <= %ld) "
			 "            or (dateto >= %ld and dateto < %ld) "
		     "          ) "
		     "     ) "
			 "     or changecodeid = 1)"
			 ")",
			 PROJECTION_ZARTIKEL,
			 artikel_nr,
			 datgueltab,
			 datgueltbis,
			 datgueltab,
			 datgueltbis
	   );
   }

   s = SqlRead( buf, &BufArtikel, NULL ); 
   
   if ( s == 100 )
   {
		strcpy( buf, "Artikel nicht vorhanden / hat keinen Festbetrag / ist nicht taxplichtig / hat nicht das angegebene Mwst- oder Tax-KZ!" );
		return 0;
   }

   if ( s != 0 )
   {
		strcpy( buf, "ZARTIKEL\n" );
		strcat( buf, DynErrmld() );
		return s;
   }
   else
	   BufArtikelOld = BufArtikel;

   if ( mode != MODE_GROSSO_LBP )
   {
		s = ReadMwst ( buf );

		if ( s != 0 )
			return s;
   }

   Init( );

//--- start transaction
   s = SqlBeginWork();
   if ( s != 0 )
   {
		strcpy( buf, DynErrmld() );
		return -1;
   }
   
   s = CalcArticle( artikel_nr, buf );

   Free( );

//--- end transaction
   if ( s == 0 )
   {
      s = SqlCommitWork();
      
	  if ( s != 0 )
         strcpy( buf, DynErrmld() );
   }
   else
      SqlRollbackWork();

   if ( s == 0 )
   {
		if ( mode == MODE_AVPS || mode == MODE_AVP_WITHOUT_TAX || mode == MODE_AVP_TAX )
			strcpy( buf, "AVP des uebergebenen Artikels wurde umgerechnet." );
		else if ( mode == MODE_FESTPR )
			strcpy( buf, "Festbetrag des uebergebenen Artikels wurde umgerechnet." );
		else if ( mode == MODE_AMNOG )
			strcpy( buf, "Preise des uebergebenen Artikels wurden nach AMNOG umgerechnet." );
		else if ( mode == MODE_GROSSO_LBP )
			strcpy( buf, "Grosso des uebergebenen Artikels wurden aus LBP neu errechnet." );
   }
 
   return s;
}

/* ---------------------------------------- */
static long CalcImportArticle( long artikel_nr, char *dbexport, char *buf )
{
	long s;
	int fd_sel_export_preise = -1;
	short currentPriceNeeded = 1;
	
	s = GetBufferDesc_Zartpreis ( buf );
	if ( s != 0 )
		return s;
	
	sprintf( buf,
			"select %s from %s:zartpreis as zartpreis,  %s:carticlecodes c "
			"where zartpreis.artikel_nr = c.articleno and c.code_type = 16 and c.article_code = '%s' "
			"order by zartpreis.datumgueltigab desc ",	
			JOIN_PROJECTION_ZARTPREIS,
			dbexport, dbexport,  
			BufArtikel.ARTIKEL_NR_HERST
			);
   
   s = SqlOpenCsWh( &fd_sel_export_preise, buf );

   if ( s != 0 )
   {
     strcpy( buf, "ZARTPREIS- EXPORT: open Cs\n" );
     strcat( buf, DynErrmld() );
     return s;
   }

   while ( s == 0 )
   {
		s = SqlFetch( fd_sel_export_preise, 1, &BufPreis, NULL );
	         
		if ( s == 100 || currentPriceNeeded == 0)
		{
			s = 0;
			break;
		}

		if ( s != 0 )
		{
			strcpy( buf, "ZARTPREIS- EXPORT: fetch\n" );
			strcat( buf, DynErrmld() );
			SqlCloseCs( fd_sel_export_preise );
			return s;
		}

		if (BufPreis.DATUMGUELTIGAB >= datgueltab || currentPriceNeeded > 0) // keine Preise aus der Vergangenheit übernehmen
		{
			BufPreis.AEP = BufPreis.AEP * (100 + aep_increase_pct) / 100;
			BufPreis.GROSSO = BufPreis.GROSSO * (100 + gep_increase_pct) / 100;
			BufPreis.ARTIKEL_NR = artikel_nr;
			//BufPreis.AVP wird 1:1 übernommen
			BufPreis.PREIS_TYP = 0;
			BufPreis.HERST_PROZENT = 0;
	
			// Arzneimittel / rezeptpfl. = 10% (verm=1), Tierarznei = 13% (2), Rest = 20% (voll=0)
			if (BufArtikel.ARZNEIMITTEL[0] == '1' || BufArtikel.REZEPTPFL[0] == '1')
				strcpy(BufPreis.KE_MWST, "1");
			else if (BufArtikel.TIERARZNEI[0] == '1')
				strcpy(BufPreis.KE_MWST, "2");
			else
				strcpy(BufPreis.KE_MWST, "0");

			if (BufPreis.DATUMGUELTIGAB <= datgueltab)
			{
				BufPreis.DATUMGUELTIGAB = datgueltab;
				currentPriceNeeded = 0;
			}			

			s = Insert_ZartPreis(buf);
		}
   }

   s = SqlCloseCs( fd_sel_export_preise );

   if ( s == 0 )
   {
		++anz_calculated;
	}
	
	return s;
}

/* ---------------------------------------- */
static long CalcImportSingle( long artikel_nr, char *dbexport, char *buf )
{
  long s;

  sprintf( buf,
			"select %s from ZARTIKEL "
			"where ARTIKEL_NR = %ld and ARTIKEL_GESPERRT != '1' and artikel_nr in (select artikel_nr from zartaustria where deutschlandbesorger = 1)",
			PROJECTION_ZARTIKEL,
			artikel_nr
			);

	s = SqlRead( buf, &BufArtikel, NULL ); 
   
	if ( s == 100 )
	{
		sprintf( buf, "PZN <%ld> ist kein aktiver D-Besorger-Artikel!", artikel_nr );
		return 0;
	}

	if ( s != 0 )
	{
		strcpy( buf, "ZARTIKEL\n" );
		strcat( buf, DynErrmld() );
		return s;
	}

	//--- start transaction
	s = SqlBeginWork();
	if ( s != 0 )
	{
		strcpy( buf, DynErrmld() );
		return -1;
	}
   
	sprintf( buf, 
			"delete from zartpreis where artikel_nr = %ld and datumgueltigab >= %ld",
			artikel_nr, datgueltab );

	s = SqlExecuteImm( buf );
	
	if ( s != 0 )
	{
		strcpy( buf, "zartpreis (Delete Zukunft): " );
		strcat( buf, DynErrmld() );
		SqlRollbackWork();
		return s;
	}

	s = CalcImportArticle( artikel_nr, dbexport, buf );

	//--- end transaction
	if ( s == 0 )
	{
		s = SqlCommitWork();
      
		if ( s != 0 )
			strcpy( buf, DynErrmld() );
	}
	else
		SqlRollbackWork();

	if ( s == 0 )
		strcpy( buf, "Berechnung der Importpreise des uebergebenen Artikels erfolgreich." );
 
	return s;
}

/* ---------------------------------------- */
static long CalcImportAll( char *dbexport, char *buf )
{
	long s;
	long artikel_nr;
	char z_buf[151];
	int fd_sel_zartaustria = -1;

	strcpy( buf,
			"select a.ARTIKEL_NR from ZARTAUSTRIA a where a.DEUTSCHLANDBESORGER = 1 ");
   	s = SqlOpenCsWh( &fd_sel_zartaustria, buf );

	if ( s != 0 )
	{
		strcpy( buf, "ZARTAUSTRIA\n" );
		strcat( buf, DynErrmld() );
		return s;
	}

	s = SqlFetch( fd_sel_zartaustria, 1, &artikel_nr, NULL );
   
	/* gar kein zartaustria-Satz ist zwar unwahrscheinlich, aber kein Fehler */
	if ( s == 100 )
	{
		strcpy( buf, "keine Deutschlandbesorger- Artikel in zartaustria vorhanden." );
		return 0;
	}

	if ( s != 0 )
	{
		strcpy( buf, "ZARTAUSTRIA\n" );
		strcat( buf, DynErrmld() );
		SqlCloseCs( fd_sel_zartaustria );

		return s;
	}

	while ( s == 0 )
	{
		s = CalcImportSingle( artikel_nr, dbexport, buf );

		if ( s == 0 )
		{
			s = SqlFetch( fd_sel_zartaustria, 1, &artikel_nr, NULL );
			
			if ( s != 0 )
			{
				strcpy( buf, "ZARTAUSTRIA\n" );
				strcat( buf, DynErrmld() );
			}
		}
	}

	SqlCloseCs( fd_sel_zartaustria );

	if ( s == 100 )
		s = 0;
   
	if ( s == 0 )
	{
		strcpy( buf, "Umrechnung erfolgreich. " );

		sprintf( z_buf, "\nEs wurden die Importpreise von %ld Artikeln neu berechnet.", anz_calculated );
   }

   strcat( buf, z_buf );
   return s;
}

/* ---------------------------------------- */
long CalcLoop ( char *db, char *cMwstKz, char *cArtNr, long datefrom, long dateto, char *buf )
{
	long s;
	size_t  lng;
   	long artikel_nr;
	char errmld[10];

	//---- PZN -----
	if ( cArtNr != NULL )
	{
		int i = 0;
       
		while ( isdigit(cArtNr[i]) )
			++i;
       
		if ( cArtNr[i] != '\0' )
		{
			strcpy( buf, "PZN nicht numerisch" );
			return 1;
		}
		artikel_nr = atol( cArtNr );
		if ( artikel_nr <= 0 )
		{
			strcpy( buf, "PZN falsch" );
			return 1;
		}
	}

	//---- KE_MWST oder TAX-KZ -----
	lng = strlen( cMwstKz );
	
	// keine Mwst-Kz-Prüfung für LBP-Berechnung, Erstattungs-Übertragung, Importpreise
	if (mode != MODE_GROSSO_LBP && mode != MODE_REFUND_FRANCE && mode != MODE_IMPORT)
	{
		if (mode == MODE_AMNOG || mode == MODE_AVP_TAX)
		{
			if ( lng == 1 )
			{
				if ( strcmp ( cMwstKz, ART_IS_TAXPFL_2 ) == 0 || strcmp ( cMwstKz, ART_IS_TAXPFL_3 ) == 0 ) // Umrechnung AMNOG für TaxKz=2/3 (RX)
					strcpy ( tax_kz, cMwstKz );
				else
				{
					strcpy( buf, "Tax-Kennzeichen nicht korrekt." );
					return -1;
				}
			}
			else
			{
				strcpy( buf, "Tax-Kennzeichen nicht korrekt." );
				return -1;
			}
		}
		else
		{
			if ( lng == 1 )
			{
				if ( strcmp (cMwstKz, MWST_VOLL) == 0 || strcmp (cMwstKz, MWST_VERM) == 0 || strcmp (cMwstKz, MWST_OHNE) == 0) //voll oder vermindert oder ke_mwst = 2(für HR)
					strcpy ( ke_mwst, cMwstKz );
				else
				{
					strcpy( buf, "Mwst-Kennzeichen nicht korrekt." );
					return -1;
				}
			}
			else 
			{
				strcpy( buf, "Mwst-Kennzeichen nicht korrekt." );
				return -1;
			}
		}
	}
	
	s = OpenBase( db, buf );

	if ( s == 0 )
	{
		s = OpenPflege( user, buf );

		if ( s == 0 )
		{
			/* Taxtabelle lesen (nicht für LBP-Berechnung, prozentuale Umrechnung, Erstattungs-Übertragung, Importpreise) */
			if ( mode != MODE_GROSSO_LBP && 
				 mode != MODE_AVP_WITHOUT_TAX &&
				 mode != MODE_IMPORT &&
				 mode != MODE_REFUND_FRANCE)
			{
				if ( CreateTaxtab( buf ) != 0 )
					return -1;
			}	

			// eigene Funktionen für Erstattungs-Übertragung, da komplett andere Verarbeitung
			if (mode == MODE_REFUND_FRANCE)
			{
				if ( cArtNr == NULL )
					s = CalcRefundAll( datefrom, dateto, buf ); 
				else
					s = CalcRefundSingle( artikel_nr, datefrom, dateto, buf );
			}
			else if (mode == MODE_IMPORT)
			{
				s = ReadImportParam(buf);

				if (s == 0)
				{
					Init( );

					if ( cArtNr == NULL )
						s = CalcImportAll( cMwstKz, buf ); 
					else
						s = CalcImportSingle( artikel_nr, cMwstKz, buf );

					Free();
				}
			}
			else
			{
				if ( cArtNr == NULL )
					s = CalcAll( buf );
				else
					s = CalcSingle( artikel_nr, buf );
			}

			ClosePflege( errmld );
		}
     
		CloseBase( );
	}

	return s;
}

/* ---------------------------------------- */
long CalcAvpLoop ( char *db, char *cMwstKz, char *cDatumGueltAb, char *cArtNr, char *buf )
{
	mode = MODE_AVPS;
	
	if ( CheckDate( cDatumGueltAb ) == -1 )
	{
		strcpy( buf, "Datum nicht korrekt." );
		return -1;
	}
	else
		datgueltab = checkdatum;

	return CalcLoop( db, cMwstKz, cArtNr, 0, 0, buf );
}

/* ---------------------------------------- */
long CalcAvpWithoutTaxLoop ( char *db, char *cMwstKz, char *cDatumGueltAb, char *cArtNr, char *buf )
{
	if ( CheckDate( cDatumGueltAb ) == -1 )
	{
		strcpy( buf, "Datum nicht korrekt." );
		return -1;
	}
	else
		datgueltab = checkdatum;

	mode = MODE_AVP_WITHOUT_TAX;

	return CalcLoop( db, cMwstKz, cArtNr, 0, 0, buf );
}

/* ---------------------------------------- */
long CalcFpLoop ( char *db, char *cMwstKz, char *cDatumFB1, char *cArtNr, char *buf )
{
	//---- DATUMGUELTIGAB -----
	datgueltab = GetPhoDate();

	//---- DATUM_FESTBETRAG1 -----
	if ( CheckDate( cDatumFB1 ) == -1 )
	{
		strcpy( buf, "Datum nicht korrekt." );
		return -1;
	}
	else
		datum_fb1 = checkdatum;

	mode = MODE_FESTPR;	// Festpreise

	return CalcLoop( db, cMwstKz, cArtNr, 0, 0, buf );
}

/* ---------------------------------------- */
long CalcAmnogLoop ( char *db, char *cTaxKz, char *cDatumGueltAb, char *cArtNr, char *buf )
{
	if ( CheckDate( cDatumGueltAb ) == -1 )
	{
		strcpy( buf, "Datum nicht korrekt." );
		return -1;
	}
	else
		datgueltab = checkdatum;

	mode = MODE_AMNOG;
	
	return CalcLoop( db, cTaxKz /* 2 oder 3 */, cArtNr, 0, 0, buf );
}

/* ---------------------------------------- */
long CalcAvpTaxLoop ( char *db, char *cTaxKz, char *cDatumGueltAb, char *cArtNr, char *buf )
{
	if ( CheckDate( cDatumGueltAb ) == -1 )
	{
		strcpy( buf, "Datum nicht korrekt." );
		return -1;
	}
	else
		datgueltab = checkdatum;

	mode = MODE_AVP_TAX;
	
	return CalcLoop( db, cTaxKz /* 2 */, cArtNr, 0, 0, buf );
}

/* ---------------------------------------- */
long CalcGrossoFromLbpLoop ( char *db, char *cDateCurrent, char *cDateTo, char *cArtNr, char *buf )
{
	if ( CheckDate( cDateCurrent ) == -1 )
	{
		strcpy( buf, "Von-Datum nicht korrekt." );
		return -1;
	}
	else
		datgueltab = checkdatum;

	if ( CheckDate( cDateTo ) == -1 )
	{
		strcpy( buf, "Bis-Datum nicht korrekt." );
		return -1;
	}
	else
		datgueltbis = checkdatum;

	mode = MODE_GROSSO_LBP;

	return CalcLoop( db, "", cArtNr, 0, 0, buf );
}

/* ---------------------------------------- */
long TransferNewRefundValuesLoop ( char *db, char *cDateFrom, char *cDateTo, char *cArtNr, char *buf )
{
	if ( CheckDate( cDateFrom ) == -1 )
	{
		strcpy( buf, "Von-Datum nicht korrekt." );
		return -1;
	}
	else
		datgueltab = checkdatum;

	if ( CheckDate( cDateTo ) == -1 )
	{
		strcpy( buf, "Bis-Datum nicht korrekt." );
		return -1;
	}
	else
		datgueltbis = checkdatum;

	mode = MODE_REFUND_FRANCE;

	return CalcLoop( db, "", cArtNr, datgueltab, datgueltbis, buf );
}

/* ---------------------------------------- */
long CalcImportLoop ( char *db, char *dbexport, char *cDatumGueltAb, char *cArtNr, char *buf )
{
	mode = MODE_IMPORT;
	
	if ( CheckDate( cDatumGueltAb ) == -1 )
	{
		strcpy( buf, "Datum nicht korrekt." );
		return -1;
	}
	else
		datgueltab = checkdatum;

	return CalcLoop( db, dbexport, cArtNr, 0, 0, buf );
}

/* ---------------------------------------- */
short CheckDate ( char *cDate )
{
	size_t lng;

	lng = strlen( cDate );

	if ( lng != 10 )
		return -1;
	else if ( ConvToPhoDate( cDate, &checkdatum, "tt.mm.jjjj" ) == 0 )
		return -1;
	else
		return 0;
}
