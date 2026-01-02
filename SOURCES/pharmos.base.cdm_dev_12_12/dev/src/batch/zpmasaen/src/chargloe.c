/* ---------------------------------------------------------------------- *
 *                         C H A R G L O E . C                            *
 * ---------------------------------------------------------------------- *
 * Projekt:  ZDP                                                          *
 * Gruppe:   Chargen loeschen                                             *
 * ---------------------------------------------------------------------- *
 * Autor  :  Raab                                                         *
 * Anfang :  12.09.2006                                                   *
 * Update :                                                               *
 * ---------------------------------------------------------------------- */

/* --- Include-Dateien einbinden ---------------------------------------- */

#include <stdio.h>                                /* C-Standard-Libraries */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "hdatum/phodate.h"
#include "libscsvoodoo/libscsvoodoo.h"

#include  "wdbups/wpp_prot.h"
#include  "wdbups/wpp_dbas.h"

#include <zchargenrueckruf.h>
#include <cdiscount.h>
#include <zpreiserhoehung.h>
#include <zpznpflege.h>
#include <zgrppflege.h>

#define L_ARTIKEL_NR 7

/* ----------------- Prototype ------------------------ */

void CloseBase( void );
long OpenBase( char *db, char *errmld );

/* ----------------- Usage ------------------------ */

void ChargLoeUsage( char *buf )
{
   strcat( buf, "- zpmasaen 8 mode Database USER Datum\n" );
   strcat( buf, "  mode = 1: Chargen mit Ablaufdaten < heute loeschen\n" );
   strcat( buf, "  mode = 2: Rabatte mit Ablaufdatum <= Datum loeschen\n" );
   strcat( buf, "  mode = 3: Preiserhoeh. mit Datum  <= Datum loeschen\n" );
   strcat( buf, "  mode = 4: CTransferCsc mit entrytime <= Datum (datetime-format!) loeschen\n" );
}

/* ----------------- Loeschen mit Protokoll ------------------ */

static int m_Fd_Zchargenrueckruf = -1;

static int GetBufferDesc_Zchargenrueckruf( char *cErrmld )
{
   char *tabelle = "zchargenrueckruf";
   long s;
   char errmld[100];

   *cErrmld = '\0';

   if ( m_Fd_Zchargenrueckruf >= 0 ) return 0;

   s = OpenBufferDescProj( &m_Fd_Zchargenrueckruf, tabelle, PROJECTION_ZCHARGENRUECKRUF,
                           NULL, NULL, V_PROTO_VERTEIL,
                           errmld );
   if ( s != 0 )
   {
     strcpy( cErrmld, errmld );
     strcat( cErrmld, "\ntable " );
     strcat( cErrmld, tabelle );;
     m_Fd_Zchargenrueckruf = -1;
     return -1;
   }

   return 0;
}

static long Delete_Zchargenrueckruf( long artikel_nr, char *charge, char *cErrmld )
{
   long s;
   char errmld[200];
   char m_PrimekeyCond[80];
   char format[80];
   struct ZCHARGENRUECKRUF zchr;

   if (  GetBufferDesc_Zchargenrueckruf( cErrmld ) != 0 ) return -1;

   zchr.ARTIKEL_NR = artikel_nr;
   strcpy(zchr.CHARGE, charge);
   sprintf( format, "ARTIKEL_NR=%c%d.ld and CHARGE = '%s'", '%', L_ARTIKEL_NR, zchr.CHARGE );
   sprintf( m_PrimekeyCond, format, zchr.ARTIKEL_NR );

   s = FdReadRecord( m_Fd_Zchargenrueckruf, m_PrimekeyCond, &zchr, errmld );
   if ( s == 0 )
   {
     s = FdDelayDeleteRecord( m_Fd_Zchargenrueckruf, &zchr, m_PrimekeyCond, errmld );
     if ( s != 0 )
     {
       strcpy( cErrmld, "FdDeleteZchargenrueckruf\n" );
       strcat( cErrmld, errmld );
     }
   }
   else if ( s == 100 )
     s = 0;
   else
   {
     strcpy( cErrmld, "FdReadZchargenrueckruf\n" );
     strcat( cErrmld, errmld );
   }

   return s;
}

static int m_Fd_Cdiscount = -1;

static int GetBufferDesc_Cdiscount( char *cErrmld )
{
   char *tabelle = "cdiscount";
   long s;
   char errmld[100];

   *cErrmld = '\0';

   if ( m_Fd_Cdiscount >= 0 ) return 0;

   s = OpenBufferDescProj( &m_Fd_Cdiscount, tabelle, PROJECTION_CDISCOUNT,
                           NULL, NULL, V_PROTO_VERTEIL,
                           errmld );
   if ( s != 0 )
   {
     strcpy( cErrmld, errmld );
     strcat( cErrmld, "\ntable " );
     strcat( cErrmld, tabelle );;
     m_Fd_Cdiscount = -1;
     return -1;
   }

   return 0;
}

static long Delete_Cdiscount( long articleno, long discountgrpno, char *pharmacygroupid, 
							  long customerno, long baseqty, long datefrom, long dateto, 
							  short grpdiscounttyp, short discounttype, short discountspec,
						      char *cErrmld )
{
   long s;
   char errmld[200];
   char m_PrimekeyCond[500];
   char format[500];
   struct CDISCOUNT cdi;

   if (  GetBufferDesc_Cdiscount( cErrmld ) != 0 ) return -1;

   cdi.ARTICLENO = articleno;
   cdi.DISCOUNTGRPNO = discountgrpno;
   strcpy(cdi.PHARMACYGROUPID, pharmacygroupid);
   cdi.CUSTOMERNO = customerno;
   cdi.BASEQTY = baseqty;
   cdi.DATEFROM = datefrom;
   cdi.DATETO = dateto;
   cdi.GRPDISCOUNTTYP = grpdiscounttyp;
   cdi.DISCOUNTTYPE = discounttype;
   cdi.DISCOUNTSPEC = discountspec;

   sprintf( format, "ARTICLENO=%c%d.1ld and DISCOUNTGRPNO=%ld and PHARMACYGROUPID = '%s' and CUSTOMERNO=%ld and BASEQTY=%ld and DATEFROM=%ld and DATETO=%ld and GRPDISCOUNTTYP=%d and DISCOUNTTYPE=%d and DISCOUNTSPEC=%d", '%', L_ARTIKEL_NR, cdi.DISCOUNTGRPNO, cdi.PHARMACYGROUPID, cdi.CUSTOMERNO, cdi.BASEQTY, cdi.DATEFROM, cdi.DATETO, cdi.GRPDISCOUNTTYP, cdi.DISCOUNTTYPE, cdi.DISCOUNTSPEC );
   sprintf( m_PrimekeyCond, format, cdi.ARTICLENO );

   s = FdReadRecord( m_Fd_Cdiscount, m_PrimekeyCond, &cdi, errmld );
   if ( s == 0 )
   {
     s = FdDelayDeleteRecord( m_Fd_Cdiscount, &cdi, m_PrimekeyCond, errmld );
     if ( s != 0 )
     {
       strcpy( cErrmld, "FdDeleteCdiscount\n" );
       strcat( cErrmld, errmld );
     }
   }
   else if ( s == 100 )
     s = 0;
   else
   {
     strcpy( cErrmld, "FdReadCdiscount\n" );
     strcat( cErrmld, errmld );
     strcat( cErrmld, "\n" );
     strcat( cErrmld, m_PrimekeyCond );
   }

   return s;
}

static int m_Fd_Zpreiserhoehung = -1;

static int GetBufferDesc_Zpreiserhoehung( char *cErrmld )
{
   char *tabelle = "zpreiserhoehung";
   long s;
   char errmld[100];

   *cErrmld = '\0';

   if ( m_Fd_Zpreiserhoehung >= 0 ) return 0;

   s = OpenBufferDescProj( &m_Fd_Zpreiserhoehung, tabelle, PROJECTION_ZPREISERHOEHUNG,
                           NULL, NULL, V_PROTO_VERTEIL,
                           errmld );
   if ( s != 0 )
   {
     strcpy( cErrmld, errmld );
     strcat( cErrmld, "\ntable " );
     strcat( cErrmld, tabelle );;
     m_Fd_Zpreiserhoehung = -1;
     return -1;
   }

   return 0;
}

static long Delete_Zpreiserhoehung( long artikel_nr, long datumgueltigab, char *cErrmld )
{
   long s;
   char errmld[200];
   char m_PrimekeyCond[80];
   char format[80];
   struct ZPREISERHOEHUNG zpe;

   if (  GetBufferDesc_Zpreiserhoehung( cErrmld ) != 0 ) return -1;

   zpe.ARTIKEL_NR = artikel_nr;
   zpe.DATUMGUELTIGAB = datumgueltigab;
   sprintf( format, "ARTIKEL_NR=%c%d.ld and DATUMGUELTIGAB = %d", '%', L_ARTIKEL_NR, zpe.DATUMGUELTIGAB );
   sprintf( m_PrimekeyCond, format, zpe.ARTIKEL_NR );

   s = FdReadRecord( m_Fd_Zpreiserhoehung, m_PrimekeyCond, &zpe, errmld );
   if ( s == 0 )
   {
     s = FdDelayDeleteRecord( m_Fd_Zpreiserhoehung, &zpe, m_PrimekeyCond, errmld );
     if ( s != 0 )
     {
       strcpy( cErrmld, "FdDeleteZpreiserhoehung\n" );
       strcat( cErrmld, errmld );
     }
   }
   else if ( s == 100 )
     s = 0;
   else
   {
     strcpy( cErrmld, "FdReadZpreiserhoehung\n" );
     strcat( cErrmld, errmld );
   }

   return s;
}

/* -----  Zpznpflege  ------------------------- */

static int  Fd_Zpznpflege = -1;

static struct ZPZNPFLEGE Buf_zpznpflege;

static int GetBufferDesc_Zpznpflege( char * errmld )
{
   char *tabelle = "zpznpflege";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");
   if ( Fd_Zpznpflege >= 0 ) return 0;

   lStatus = OpenBufferDescProj( &Fd_Zpznpflege, tabelle, PROJECTION_ZPZNPFLEGE,
                                 NULL, NULL,
                                 V_OHNE,
                                 errstr );
   if ( lStatus != 0 )
   {
     sprintf( errmld, "%s: %s", tabelle, errstr );
     Fd_Zpznpflege = -1;
     return -1;
   }

   return 0;
}

static long StoreRecord_Zpznpflege( long artikel_nr, long datum, char* cErrmld )
{
   long lStatus;
   char PrimekeyCond[75];

   Buf_zpznpflege.ARTIKEL_NR = artikel_nr;
   Buf_zpznpflege.DATUM      = datum;
   strcpy (Buf_zpznpflege.DEZAP_SA, "28");

   strcpy( cErrmld, "" );

   sprintf( PrimekeyCond, "ARTIKEL_NR=%ld and DATUM=%ld and DEZAP_SA='%s'",
                          Buf_zpznpflege.ARTIKEL_NR,
                          Buf_zpznpflege.DATUM,
						  Buf_zpznpflege.DEZAP_SA);

   lStatus = FdReadRecord( Fd_Zpznpflege, PrimekeyCond,
                           &Buf_zpznpflege, cErrmld );

   if ( !( lStatus == 0 || lStatus == 100 ) ) return -1;

   if ( lStatus == 100 )
   {
      Buf_zpznpflege.ARTIKEL_NR = artikel_nr;
      Buf_zpznpflege.DATUM      = datum;
	  strcpy (Buf_zpznpflege.DEZAP_SA, "28");
      lStatus = FdDelayInsertRecord( Fd_Zpznpflege, &Buf_zpznpflege,
                                     PrimekeyCond, cErrmld);
   }

   return lStatus;
}

/* -----  Zgrppflege  ------------------------- */

static int  Fd_Zgrppflege = -1;

static struct ZGRPPFLEGE Buf_zgrppflege;

static int GetBufferDesc_Zgrppflege( char * errmld )
{
   char *tabelle = "zgrppflege";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");
   if ( Fd_Zgrppflege >= 0 ) return 0;

   lStatus = OpenBufferDescProj( &Fd_Zgrppflege, tabelle, PROJECTION_ZGRPPFLEGE,
                                 NULL, NULL,
                                 V_OHNE,
                                 errstr );
   if ( lStatus != 0 )
   {
     sprintf( errmld, "%s: %s", tabelle, errstr );
     Fd_Zgrppflege = -1;
     return -1;
   }

   return 0;
}

static long StoreRecord_Zgrppflege( long rabattgruppe, long datum, char* cErrmld )
{
   long lStatus;
   char PrimekeyCond[75];

   sprintf (Buf_zgrppflege.KEY_GRUPPE, "%5.5d", rabattgruppe);
   Buf_zgrppflege.DATUM      = datum;
   strcpy (Buf_zgrppflege.DEZAP_SA, "28");

   strcpy( cErrmld, "" );

   sprintf( PrimekeyCond, "KEY_GRUPPE='%s' and DATUM=%ld and DEZAP_SA='%s'",
                          Buf_zgrppflege.KEY_GRUPPE,
                          Buf_zgrppflege.DATUM,
						  Buf_zgrppflege.DEZAP_SA);

   lStatus = FdReadRecord( Fd_Zgrppflege, PrimekeyCond,
                           &Buf_zgrppflege, cErrmld );

   if ( !( lStatus == 0 || lStatus == 100 ) ) return -1;

   if ( lStatus == 100 )
   {
	  sprintf (Buf_zgrppflege.KEY_GRUPPE, "%5.5d", rabattgruppe);
      Buf_zgrppflege.DATUM      = datum;
	  strcpy (Buf_zgrppflege.DEZAP_SA, "28");
      lStatus = FdDelayInsertRecord( Fd_Zgrppflege, &Buf_zgrppflege,
                                     PrimekeyCond, cErrmld);
   }

   return lStatus;
}

/* ----------------- Funktion ------------------------ */

static long Init_Loeschen( char *errmld )
{
   if ( GetBufferDesc_Zpznpflege( errmld ) != 0 ) 
	   return -1;

   if ( GetBufferDesc_Zgrppflege( errmld ) != 0 ) 
	   return -1;

   return 0;
}

static long Execute_Loeschen_Chargen( long artikel_nr, char *charge, char *errmld )
{
   long s;

   s = Delete_Zchargenrueckruf( artikel_nr, charge, errmld );
   
   if ( s == 0 )
      s = FdTransactWithoutWork( errmld );
   
   if ( s != 0 )
   {
      return s;
   }

   return 0;
}

static long Execute_Loeschen_Rabatte( long articleno, long discountgrpno, char *pharmacygroupid, 
									  long customerno, long baseqty, long datefrom, long dateto, 
									  short grpdiscounttyp, short discounttype, short discountspec,
									  char *errmld )
{
   long s;
   long tagesdatum;

   tagesdatum = GetPhoDate();

   s = Delete_Cdiscount( articleno, discountgrpno, pharmacygroupid, customerno, baseqty, datefrom, 
						 dateto, grpdiscounttyp, discounttype, discountspec, errmld );
   
   if ( s == 0 ) 
   {
	  if (articleno == 0)
   	     s = StoreRecord_Zgrppflege( discountgrpno, tagesdatum, errmld );
	  else
   	     s = StoreRecord_Zpznpflege( articleno, tagesdatum, errmld );
   }
  
   if ( s == 0 )
      s = FdTransactWithoutWork( errmld );
/*    s = FdTransact( errmld ); */
   
   if ( s != 0 )
   {
      return s;
   }

   return 0;
}

static long Execute_Loeschen_Preiserhoehungen( long artikel_nr, long datumgueltigab, char *errmld )
{
   long s;

   s = Delete_Zpreiserhoehung( artikel_nr, datumgueltigab, errmld );
   
   if ( s == 0 )
      s = FdTransactWithoutWork( errmld );
   
   if ( s != 0 )
   {
      return s;
   }

   return 0;
}

static void Free_Loeschen( )
{
   if ( Fd_Zpznpflege >= 0 )
      CloseOneBufferDesc( Fd_Zpznpflege );
   Fd_Zpznpflege = -1;

   if ( Fd_Zgrppflege >= 0 )
      CloseOneBufferDesc( Fd_Zgrppflege );
   Fd_Zgrppflege = -1;
}

static long LoescheTransferCsc( char *user, char *loedatum, char *buf )
{
	long lStatus = 0;
	char sql [250];
	
	//sprintf ( sql, "delete from ctransfercsc where entrydatetime < datetime(%s) YEAR TO DAY",
	//				loedatum );
	// auf Wunsch von FN werden jeden Abend alle Einträge wieder gelöscht:
	sprintf ( sql, "delete from ctransfercsc" );	

	lStatus = SqlExecuteImm( sql );
			
	if ( lStatus != 0 )
	{
		strcpy( buf, "ctransfercsc (Delete): " );
		strcat( buf, DynErrmld() );
	}

	return lStatus;
}

static long LoescheAllChargen( char *user, long artikel_nr, char *charge, 
					    long tagesdatum, char *buf )
{
   long s;

   s = SqlBeginWork();
   if ( s != 0 )
   {
     strcpy( buf, DynErrmld() );
     return -1;
   }

   s = Execute_Loeschen_Chargen( artikel_nr, charge, buf );

   if ( s == 0 )
   {
      s = SqlCommitWork();
      if ( s != 0 )
         strcpy( buf, DynErrmld() );
   }
   else
      SqlRollbackWork();

   return s;
}

static long LoescheChargen( char *user, long loedatum, char *buf )
{
   long tagesdatum;
   long artikel_nr;
   char charge[25];
   long s;
   long anz;
   int  fd;
   char z_buf[51];

   tagesdatum = GetPhoDate();

   sprintf( buf, "select ARTIKEL_NR, CHARGE from ZCHARGENRUECKRUF where " \
            //"DATUM_ANLAGE <= %ld", loedatum );
			"DATETO_GI < %ld and DATETO_CUSTRETURNS < %ld", tagesdatum, tagesdatum);

   s = SqlOpenCsWh( &fd, buf );

   if ( s != 0 )
   {
     strcpy( buf, "ZCHARGENRUECKRUF\n" );
     strcat( buf, DynErrmld() );
     return s;
   }

   s = SqlFetch( fd, 1, &artikel_nr, charge, NULL );
   if ( s == 100 )
   {
        //ConvFromPhoDate( z_buf, loedatum, "tt.mm.jjjj" );
        //sprintf( buf, "Keine Chargen mit Anlagedatum <= %s vorhanden",
        ConvFromPhoDate( z_buf, tagesdatum, "tt.mm.jjjj" );
        sprintf( buf, "Keine Chargen mit DATETO_GI && DATETO_CUSTRETURNS < %s vorhanden",
                      z_buf );

		return 0;
   }

   if ( s != 0 )
   {
     strcpy( buf, "ZCHARGENRUECKRUF\n" );
     strcat( buf, DynErrmld() );
     return s;
   }

   s = Init_Loeschen( buf );
   if ( s != 0 )
   {
      Free_Loeschen( );
      SqlCloseCs( fd );
      return s;
   }

   anz = 0;
   while ( s == 0 )
   {
      s = LoescheAllChargen( user, artikel_nr, charge, tagesdatum, buf );

      if ( s == 0 )
      {
         anz++;
         s = SqlFetch( fd, 1, &artikel_nr, charge, NULL );
         if ( s != 0 )
         {
           strcpy( buf, "ZCHARGENRUECKRUF\n" );
           strcat( buf, DynErrmld() );
         }
      }
   }

   Free_Loeschen( );

   SqlCloseCs( fd );

   sprintf( z_buf, "\nEs wurden %ld Chargen geloescht", anz );

   if ( s == 100 )
   {
      s = 0;
      strcpy( buf, "Loeschen erfolgreich" );
   }

   strcat( buf, z_buf );
   return s;
}

static long LoescheAllPreiserhoehungen( char *user, long artikel_nr, long datumgueltigab, 
					    long tagesdatum, char *buf )
{
   long s;

   s = SqlBeginWork();
   if ( s != 0 )
   {
     strcpy( buf, DynErrmld() );
     return -1;
   }

   s = Execute_Loeschen_Preiserhoehungen( artikel_nr, datumgueltigab, buf );

   if ( s == 0 )
   {
      s = SqlCommitWork();
      if ( s != 0 )
         strcpy( buf, DynErrmld() );
   }
   else
      SqlRollbackWork();

   return s;
}

static long LoeschePreiserhoehungen( char *user, long loedatum, char *buf )
{
   long tagesdatum;
   long artikel_nr;
   long datumgueltigab;
   long s;
   long anz;
   int  fd;
   char z_buf[51];

   tagesdatum = GetPhoDate();

   sprintf( buf, "select ARTIKEL_NR, DATUMGUELTIGAB from ZPREISERHOEHUNG where " \
            "DATUMGUELTIGAB <= %ld", loedatum );

   s = SqlOpenCsWh( &fd, buf );

   if ( s != 0 )
   {
     strcpy( buf, "ZPREISERHOEHUNG\n" );
     strcat( buf, DynErrmld() );
     return s;
   }

   s = SqlFetch( fd, 1, &artikel_nr, &datumgueltigab, NULL );
   if ( s == 100 )
   {
        ConvFromPhoDate( z_buf, loedatum, "tt.mm.jjjj" );
        sprintf( buf, "Keine Preiserhoehungen mit Datum <= %s vorhanden",
                      z_buf );

		return 0;
   }

   if ( s != 0 )
   {
     strcpy( buf, "ZPREISERHOEHUNG\n" );
     strcat( buf, DynErrmld() );
     return s;
   }

   s = Init_Loeschen( buf );
   if ( s != 0 )
   {
      Free_Loeschen( );
      SqlCloseCs( fd );
      return s;
   }

   anz = 0;
   while ( s == 0 )
   {
      s = LoescheAllPreiserhoehungen( user, artikel_nr, datumgueltigab, tagesdatum, buf );

      if ( s == 0 )
      {
         anz++;
         s = SqlFetch( fd, 1, &artikel_nr, &datumgueltigab, NULL );
         if ( s != 0 )
         {
           strcpy( buf, "ZPREISERHOEHUNG\n" );
           strcat( buf, DynErrmld() );
         }
      }
   }

   Free_Loeschen( );

   SqlCloseCs( fd );

   sprintf( z_buf, "\nEs wurden %ld Preiserhoehungen geloescht", anz );

   if ( s == 100 )
   {
      s = 0;
      strcpy( buf, "Loeschen erfolgreich" );
   }

   strcat( buf, z_buf );
   return s;
}

static long LoescheAllRabatte( char *user, long articleno, long discountgrpno, char *pharmacygroupid, 
							   long customerno, long baseqty, long datefrom, long dateto, 
							   short grpdiscounttyp, short discounttype, short discountspec,
						       long tagesdatum, char *buf )
{
   long s;

   s = SqlBeginWork();
   if ( s != 0 )
   {
     strcpy( buf, DynErrmld() );
     return -1;
   }

   s = Execute_Loeschen_Rabatte( articleno, discountgrpno, pharmacygroupid, customerno, baseqty, datefrom, dateto, grpdiscounttyp, discounttype, discountspec, buf );

   if ( s == 0 )
   {
      s = SqlCommitWork();
      if ( s != 0 )
         strcpy( buf, DynErrmld() );
   }
   else
      SqlRollbackWork();

   return s;
}

static long LoescheRabatte( char *user, long loedatum, char *buf )
{
   long tagesdatum;
   long articleno;
   long discountgrpno;
   char pharmacygroupid[4];
   long customerno;
   long baseqty;
   long datefrom;
   long dateto;
   short grpdiscounttyp;
   short discounttype;
   short discountspec;

   long s;
   long anz;
   int  fd;
   char z_buf[51];

   tagesdatum = GetPhoDate();

   sprintf( buf, "select ARTICLENO, DISCOUNTGRPNO, PHARMACYGROUPID, CUSTOMERNO, BASEQTY, DATEFROM, " \
				 "DATETO, GRPDISCOUNTTYP, DISCOUNTTYPE, DISCOUNTSPEC from CDISCOUNT where " \
				 "DATETO <= %ld", loedatum );

   s = SqlOpenCsWh( &fd, buf );

   if ( s != 0 )
   {
     strcpy( buf, "CDISCOUNT\n" );
     strcat( buf, DynErrmld() );
     return s;
   }

   s = SqlFetch( fd, 1, &articleno, &discountgrpno, pharmacygroupid, &customerno, &baseqty, &datefrom, &dateto, &grpdiscounttyp, &discounttype, &discountspec, NULL );
   if ( s == 100 )
   {
        ConvFromPhoDate( z_buf, loedatum, "tt.mm.jjjj" );
        sprintf( buf, "Keine Rabatte mit Endedatum <= %s vorhanden",
                      z_buf );

		return 0;
   }

   if ( s != 0 )
   {
     strcpy( buf, "CDISCOUNT\n" );
     strcat( buf, DynErrmld() );
     return s;
   }

   s = Init_Loeschen( buf );
   if ( s != 0 )
   {
      Free_Loeschen( );
      SqlCloseCs( fd );
      return s;
   }

   anz = 0;
   while ( s == 0 )
   {
	   s = LoescheAllRabatte( user, articleno, discountgrpno, pharmacygroupid, customerno, baseqty, datefrom, dateto, grpdiscounttyp, discounttype, discountspec, tagesdatum, buf );

      if ( s == 0 )
      {
         anz++;
	     s = SqlFetch( fd, 1, &articleno, &discountgrpno, pharmacygroupid, &customerno, &baseqty, &datefrom, &dateto, &grpdiscounttyp, &discounttype, &discountspec, NULL );
         if ( s != 0 )
         {
           strcpy( buf, "CDISCOUNT\n" );
           strcat( buf, DynErrmld() );
         }
      }
   }

   Free_Loeschen( );

   SqlCloseCs( fd );

   sprintf( z_buf, "\nEs wurden %ld Rabattpositionen geloescht", anz );

   if ( s == 100 )
   {
      s = 0;
      strcpy( buf, "Loeschen erfolgreich" );
   }

   strcat( buf, z_buf );
   return s;
}

long ChargLoeLoop ( char *mode, char *db, char *user, char *cDatum, char *buf )
{
   long s;
   long loedatum = 0;
   size_t lng;
   char errmld[10];

   if ( !( *mode == '1' || *mode == '2' || *mode == '3' || *mode == '4' ) )
   {
      strcpy( buf, "mode = 1 oder mode = 2 oder mode = 3 oder mode = 4" );
      return -1;
   }

   lng = strlen( cDatum );
   if ( lng == 1 && *cDatum == '0' )
      loedatum = -1;
   else if ( lng != 10 )
      loedatum = -1;
   else if (*mode != '4')
   {
      if ( ConvToPhoDate( cDatum, &loedatum, "tt.mm.jjjj" ) == 0 )
        loedatum = -1;
   }

   if ( loedatum == -1 )
   {
      strcpy( buf, "Datum fehlt oder nicht korrekt" );
      return -1;
   }

   s = OpenBase( db, buf );
   
   if ( s == 0 )
   {
     s = OpenPflege( user, buf );
     
	 if ( s == 0 )
     {
		if ( *mode == '1' )
			s = LoescheChargen( user, loedatum, buf );
		else if ( *mode == '2' )
			s = LoescheRabatte( user, loedatum, buf );
		else if ( *mode == '3' )
			s = LoeschePreiserhoehungen( user, loedatum, buf );
		else if ( *mode == '4' )
			s = LoescheTransferCsc( user, cDatum, buf );

		ClosePflege( errmld );
     }
     
	 CloseBase( );
   }

   return s;
}
