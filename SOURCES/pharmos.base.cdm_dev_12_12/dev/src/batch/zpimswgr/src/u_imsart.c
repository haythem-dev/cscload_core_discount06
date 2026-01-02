/* ---------------------------------------------------------------------- *
 *                           U _ I M S A R T . C                          *
 * ---------------------------------------------------------------------- *
 * Projekt:  Einkauf                                                      *
 * Gruppe:   Generiert die Zuordnung in zartwg                            *
 * ---------------------------------------------------------------------- *
 * Autor  :  Schmitt                                                      *
 * Anfang :  28.06.1998                                                   *
 * Update :                                                               *
 * ---------------------------------------------------------------------- */

/* #define TEST */

/* --- Include-Dateien einbinden ---------------------------------------- */

#include <stdio.h>                                /* C-Standard-Libraries */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <libscsvoodoo.h>
#include <phodate.h>

#include <zartwg.h>
#include <zapflege.h>
#include <artkatg.h>

#ifdef MIT_BSSICHG		/* 24.01.2003 */
#include "u_bssg.h"		/* 23.21.2002 BSSICHG */
#endif

#define L_ARTIKEL_NR 7

/* -------  Spezielle includes ----------------------------------------- */

#include "pflegevers.h"

/* ---------- schreiben mit Protokoll ----------- */

void s_longcatl( char *str, long l, int lng, char ze )
{
   int i;
   char buf[50];
   char format[11];

   sprintf( format, "%s%d%s", "%.", lng, "ld" );

   sprintf( buf, format, l );

   if ( ze != '0' )
   {
      i = 0;
      while ( i < lng - 1 && buf[i] == '0' )
         buf[i++] = ze;
   }
   strcat( str, buf);
}

static char PrimekeyCond[100];

static int  Fd_Zartwg = -1;
static int  Fd_Zartwg_9 = -1;
static long lStatus_Zartwg;
static long lStatus_Zartwg_9;

static struct ZARTWG  Buf_Zartwg;
static struct ZARTWG  BufOld_Zartwg;
static struct ZARTWG  Buf_Zartwg_9;
static struct ZARTWG  BufOld_Zartwg_9;


static int GetBufferDesc_Zartwg( char * errmld )
{
   char *tabelle = "zartwg";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");
   if ( Fd_Zartwg >= 0 ) return 0;

#ifdef WP_ALTE_VERSION
   lStatus = OpenBufferDesc( &Fd_Zartwg, tabelle,
                              NULL, NULL,
                              V_PROTO_VERTEIL,
                              errstr );
#else
   lStatus = OpenBufferDescProj( &Fd_Zartwg, tabelle, PROJECTION_ZARTWG,
                                 NULL, NULL,
                                 V_PROTO_VERTEIL,
                                 errstr );
#endif

   if ( lStatus != 0 )
   {
     sprintf( errmld, "%s: %s", tabelle, errstr );
     Fd_Zartwg = -1;
     return -1;
   }
   return 0;
}

static int GetBufferDesc_Zartwg_9( char * errmld )
{
   char *tabelle = "zartwg";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");
   if ( Fd_Zartwg_9 >= 0 ) return 0;

   lStatus = OpenBufferDescProj( &Fd_Zartwg_9, tabelle, PROJECTION_ZARTWG,
                                 NULL, NULL,
                                 V_PROTO_VERTEIL,
                                 errstr );

   if ( lStatus != 0 )
   {
     sprintf( errmld, "%s: %s", tabelle, errstr );
     Fd_Zartwg_9 = -1;
     return -1;
   }

   return 0;
}

static void SetPrimekeyCondition_Zartwg ( char art )
{
   /* ART = '1' -> IMS-WGR */
   /* ART = '9' -> Rabattgruppe */

   char format[50];

   sprintf( format, "ARTIKEL_NR=%c%d.ld and ART='%c'", '%', L_ARTIKEL_NR, art );
   sprintf( PrimekeyCond, format, Buf_Zartwg.ARTIKEL_NR );
}

static void InitRecord_Zartwg( )
{
	Buf_Zartwg.ARTIKEL_NR = 0;
	Buf_Zartwg.ART[0] = '1';    
	memset( Buf_Zartwg.WARENGRUPPE, ' ', L_ZARTWG_WARENGRUPPE );
	Buf_Zartwg.WARENGRUPPE[L_ZARTWG_WARENGRUPPE] = '\0';
}

static void InitRecord_Zartwg_9( )
{
	Buf_Zartwg_9.ARTIKEL_NR = 0;
	Buf_Zartwg_9.ART[0] = '9';    
	memset( Buf_Zartwg_9.WARENGRUPPE, ' ', L_ZARTWG_WARENGRUPPE );
	Buf_Zartwg_9.WARENGRUPPE[L_ZARTWG_WARENGRUPPE] = '\0';
}

static long DeclReadZartwg( int *fd, char *errmld )
{
   long s;
   char sql[100];

   sprintf( sql, "select %s from ZARTWG where ARTIKEL_NR=? and ART='1'",
	             PROJECTION_ZARTWG );
   s = SqlDeclareCsWh( fd,
                       sql,
                       "ZARTWG.ARTIKEL_NR",
                       NULL  );

   if ( s != 0 )
     sprintf( errmld, "DeclReadZartwg: %s", DynErrmld() );

   return s;
}

static long DeclReadZartwg_9( int *fd, char *errmld )
{
   long s;
   char sql[100];

   sprintf( sql, "select %s from ZARTWG where ARTIKEL_NR=? and ART='9'",
	             PROJECTION_ZARTWG );
   s = SqlDeclareCsWh( fd,
                       sql,
                       "ZARTWG.ARTIKEL_NR",
                       NULL  );

   if ( s != 0 )
     sprintf( errmld, "DeclReadZartwg_9: %s", DynErrmld() );

   return s;
}

static long ReadZartwg( int fd, long artikel_nr, char *cErrmld )
{
   long lStatus;

   lStatus = SqlReadDeclCs( fd, &Buf_Zartwg, NULL, &artikel_nr, NULL );
   if ( lStatus == 0 )
   {
      BufOld_Zartwg = Buf_Zartwg;  /* gelesenen Satz sichern */
      strcpy( cErrmld, "" );
   }
   else if ( lStatus == 100 )
   {
     InitRecord_Zartwg( );
     BufOld_Zartwg = Buf_Zartwg;       /* initialisierten Satz sichern */
   }
   else
     sprintf( cErrmld, "ReadZartwg: %s", DynErrmld() );

   lStatus_Zartwg = lStatus;
   return lStatus;
}

static long ReadZartwg_9( int fd, long artikel_nr, char *cErrmld )
{
   long lStatus;

   lStatus = SqlReadDeclCs( fd, &Buf_Zartwg_9, NULL, &artikel_nr, NULL );
   if ( lStatus == 0 )
   {
	    BufOld_Zartwg_9 = Buf_Zartwg_9;  /* gelesenen Satz sichern */
		strcpy( cErrmld, "" );
   }
   else if ( lStatus == 100 )
   {
		InitRecord_Zartwg_9( );
		BufOld_Zartwg_9 = Buf_Zartwg_9;       /* initialisierten Satz sichern */
   }
   else
		sprintf( cErrmld, "ReadZartwg_9: %s", DynErrmld() );

   lStatus_Zartwg_9 = lStatus;

   return lStatus;
}

static long StoreRecord_Zartwg( char* cErrmld )
{
   long lStatus;
   char errmld[200];

   SetPrimekeyCondition_Zartwg ( '1' );

   if ( lStatus_Zartwg == 100 )
      lStatus = FdDelayInsertRecord( Fd_Zartwg, &Buf_Zartwg,
                                     PrimekeyCond, errmld);
   else if ( lStatus_Zartwg == 0 )
      lStatus = FdDelayUpdateRecord( Fd_Zartwg, &Buf_Zartwg,
                                     &BufOld_Zartwg,
                                     PrimekeyCond, errmld );
   else
   {
     lStatus = lStatus_Zartwg;
     strcpy( cErrmld, "Interner Fehler" );
   }

   if ( lStatus != 0 )
      strcpy( cErrmld, errmld );
   else
      strcpy( cErrmld, "" );

   return lStatus;
}

static long StoreRecord_Zartwg_9( int *upd_rabgrp, char* cErrmld )
{
   long lStatus;
   char errmld[200];

   SetPrimekeyCondition_Zartwg ( '9' );

   if ( lStatus_Zartwg_9 == 100 )
   {
      lStatus = FdDelayInsertRecord( Fd_Zartwg_9, &Buf_Zartwg_9,
                                     PrimekeyCond, errmld);
	  (*upd_rabgrp) = 3;
   }
   else if ( lStatus_Zartwg_9 == 0 )
   {
      lStatus = FdDelayUpdateRecord( Fd_Zartwg_9, &Buf_Zartwg_9,
                                     &BufOld_Zartwg_9,
                                     PrimekeyCond, errmld );
   	  (*upd_rabgrp) = 2;
   }
   else
   {
     lStatus = lStatus_Zartwg_9;
     strcpy( cErrmld, "Interner Fehler" );
   }

   if ( lStatus != 0 )
      strcpy( cErrmld, errmld );
   else
      strcpy( cErrmld, "" );

   return lStatus;
}

static long DeleteRecord_Zartwg( char *cErrmld )
{
   long lStatus;
   char errmld[200];

   if ( GetBufferDesc_Zartwg( cErrmld ) != 0 ) return -1;

   SetPrimekeyCondition_Zartwg ( '1' );

   lStatus = FdDelayDeleteRecord( Fd_Zartwg, &Buf_Zartwg, PrimekeyCond, errmld );

   if ( lStatus != 0 )
      strcpy( cErrmld, errmld );
   else
      strcpy( cErrmld, "" );

   return lStatus;
}

static long DeleteRecord_Zartwg_9( char *cErrmld )
{
   long lStatus;
   char errmld[200];

   if ( GetBufferDesc_Zartwg_9( cErrmld ) != 0 ) return -1;

   SetPrimekeyCondition_Zartwg ( '9' );

   lStatus = FdDelayDeleteRecord( Fd_Zartwg_9, &Buf_Zartwg_9, PrimekeyCond, errmld );

   if ( lStatus != 0 )
      strcpy( cErrmld, errmld );
   else
      strcpy( cErrmld, "" );

   return lStatus;
}

static long Loesche_Rabattgruppe( long artikel_nr, int *loe_rabgrp, char *errmld )
{
	int fd_read;
    long lStatus;
	long rc;

    if ( GetBufferDesc_Zartwg_9(  errmld ) != 0 )
    {
        return -1;
    }

    if ( DeclReadZartwg_9( &fd_read, errmld ) != 0 )
    {
		return -1;
    }

    ReadZartwg_9( fd_read, artikel_nr, errmld );
    if ( lStatus_Zartwg_9 == 100 )  
	{
		rc = 0;
	}
	else if ( lStatus_Zartwg_9 != 0 ) 
    {
		strcpy( errmld, DynErrmld() );
		rc = lStatus_Zartwg_9;
    }
	else
	{
		lStatus = DeleteRecord_Zartwg_9( errmld );
		(*loe_rabgrp) = 1;
		rc = lStatus;
	}

	SqlCloseCs( fd_read );
	return rc;
}

static long Schreibe_Rabattgruppe( long artikel_nr, char *rabgrp, int *upd_rabgrp, char *errmld )
{
	int fd_read;
    long lStatus;
	long rc;

    if ( GetBufferDesc_Zartwg_9(  errmld ) != 0 )
    {
        return -1;
    }

    if ( DeclReadZartwg_9( &fd_read, errmld ) != 0 )
    {
		return -1;
    }

    ReadZartwg_9( fd_read, artikel_nr, errmld );

	/* wenn Artikel Rabattgruppe hat: entweder Neuanlage oder Update zartwg mit art = 9 */
	if (atoi(rabgrp) > 0)
	{
		Buf_Zartwg_9.ARTIKEL_NR = artikel_nr;
		*Buf_Zartwg_9.WARENGRUPPE = '\0';
        strcpy (Buf_Zartwg_9.WARENGRUPPE, rabgrp);

		lStatus = StoreRecord_Zartwg_9 ( upd_rabgrp, errmld );
		rc = lStatus;
	}
	else
	{
		if ( lStatus_Zartwg_9 == 100 )  
		{
			rc = 0;
		}
		else if ( lStatus_Zartwg_9 != 0 ) 
		{
			strcpy( errmld, DynErrmld() );
			rc = lStatus_Zartwg_9;
		}
		else
		{
			lStatus = DeleteRecord_Zartwg_9( errmld );
			(*upd_rabgrp) = 1;
			rc = lStatus;
		}
	}
			
	SqlCloseCs( fd_read );
	return rc;
}

/* ////////////////////////////////////////////////////////////////// */
/* ZAPFLEGE  */

static int m_Fd_Zapflege = -1;

static long m_lStatus_Zapflege;
static struct ZAPFLEGE m_ZapflegeBuf;

static int GetBufferDesc_Zapflege( char *errmld )
{
   char *tabelle = "zapflege";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");
   if ( m_Fd_Zapflege >= 0 ) return 0;

#ifdef WP_ALTE_VERSION
   lStatus = OpenBufferDesc( &m_Fd_Zapflege, tabelle,
                             NULL, NULL,
                             V_OHNE,
                             errstr );
#else
   lStatus = OpenBufferDescProj( &m_Fd_Zapflege, tabelle, PROJECTION_ZAPFLEGE,
                                 NULL, NULL,
                                 V_OHNE,
                                 errstr );
#endif

   if ( lStatus != 0 )
   {
     sprintf( errmld, "%s: %s", tabelle, errstr );
     m_Fd_Zapflege = -1;
     return -1;
   }
   return 0;
}

long StoreRecord_Zapflege( long artikel_nr, char *cErrmld )
{
    static long datum = -1;

    long lStatus;

    char PrimekeyCond_Zapflege[100];
    char errmld[200];

    if ( datum == -1 )
       datum = PhoToday();

    m_ZapflegeBuf.ARTIKEL_NR = artikel_nr;
    m_ZapflegeBuf.DATUM = datum;

    sprintf( PrimekeyCond_Zapflege, "ARTIKEL_NR=%7ld and DATUM=%ld",
                                    m_ZapflegeBuf.ARTIKEL_NR,
                                    m_ZapflegeBuf.DATUM       );

    lStatus = FdReadRecord( m_Fd_Zapflege, PrimekeyCond_Zapflege,
                            &m_ZapflegeBuf, errmld );

    if ( lStatus == 100 )
    {
       m_ZapflegeBuf.ARTIKEL_NR = artikel_nr;
       m_ZapflegeBuf.DATUM = datum;
       lStatus = FdDelayInsertRecord( m_Fd_Zapflege, &m_ZapflegeBuf,
                                      PrimekeyCond_Zapflege, errmld );
    }

   if ( lStatus != 0 )
      strcpy( cErrmld, errmld );
   else
      strcpy( cErrmld, "" );
   return lStatus;
}

/* ////////////////////////////////////////////////////////////////// */
/* ARTKATG  */

static int m_Fd_Artkatg = -1;

static long m_lStatus_Artkatg;
static struct ARTKATG m_ArtkatgBuf;

static int GetBufferDesc_Artkatg( char *errmld )
{
   char *tabelle = "artkatg";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");
   if ( m_Fd_Artkatg >= 0 ) return 0;

   lStatus = OpenBufferDescProj( &m_Fd_Artkatg, tabelle, PROJECTION_ARTKATG,
                                 NULL, NULL,
                                 V_OHNE,
                                 errstr );

   if ( lStatus != 0 )
   {
     sprintf( errmld, "%s: %s", tabelle, errstr );
     m_Fd_Artkatg = -1;
     return -1;
   }

   return 0;
}

static int Read_Artkatg( int imswgr, char *rabgrp, char *cErrmld )
{
	char sql[100];
    long status;

	m_ArtkatgBuf.WARENGRUPPE[0] = '\0';
	s_longcatl( m_ArtkatgBuf.WARENGRUPPE, imswgr, L_ARTKATG_WARENGRUPPE, '0' );

	sprintf( sql, "select RABATTGRUPPE from ARTKATG where WARENGRUPPE = %s", m_ArtkatgBuf.WARENGRUPPE );

    status = SqlRead( sql, rabgrp, NULL );

	if (status != 0)
	{
		strcpy(rabgrp, "");

		if (status == 100)
		{
			status = 0;
		}
	}

	return status;
}

/* ---------- Eintraege aus Zartwg loeschen ----------- */

static long DeclReadTemp( int *fd, char *temp_name, char *errmld )
{
   long s;
   char sql[100];
   char art[50];
   sprintf( sql, "select ARTIKEL_NR from %s where ARTIKEL_NR=?",
                  temp_name );

   sprintf( art, "%s.ARTIKEL_NR", temp_name );

   s = SqlDeclareCsWh( fd, sql, art, NULL  );
   if ( s != 0 )
     sprintf( errmld, "DeclReadTemp: %s", DynErrmld() );
   return s;
}

static long ReadTemp( int fd, long artikel_nr, char *errmld )
{
   long s;
   long art_nr;
   s = SqlReadDeclCs( fd, &art_nr, NULL, &artikel_nr, NULL );
   if ( s != 0 )
     sprintf( errmld, "ReadTemp: %s", DynErrmld() );
   return s;
}

static long Loesche_Zartwg( long artikel_nr, int *loe_rabgrp, char *errmld )
{
   long lStatus;

   lStatus = DeleteRecord_Zartwg( errmld );
   if ( lStatus != 0 ) return lStatus;

   lStatus = Loesche_Rabattgruppe( artikel_nr, loe_rabgrp, errmld );
   if ( lStatus != 0 ) return lStatus;
   
   lStatus = StoreRecord_Zapflege( artikel_nr, errmld );
   if ( lStatus != 0 ) return lStatus;
   
   if ( FdTransact( errmld ) != 0 )
   {
      return -1;
   }

   return 0;
}


long Loesche_From_Zartwg( char *temp_name, char *errmld,
                          long *anz_loe, long *anz_loe_9 )
{
   int fd_sel;
   int fd_read;
   long s;
   char sql[100];
   int loe_rabgrp = 0;

/* *anz_loe = 0;
   *anz_loe_9 = 0; */

   if (  GetBufferDesc_Zapflege( errmld ) != 0 )
   {
      return -1;
   }

   if (  GetBufferDesc_Zartwg(  errmld ) != 0 )
   {
      return -1;
   }

   if ( DeclReadTemp( &fd_read, temp_name, errmld ) != 0 )
   {
      return -1;
   }

#ifdef TEST
   printf( "Anfang von Loeschen\n" );
#endif

   sprintf( sql, "select %s from ZARTWG where ART='1'", PROJECTION_ZARTWG );

   lStatus_Zartwg = SqlOpenCsWh( &fd_sel, sql );
   if ( lStatus_Zartwg != 0 )
   {
      strcpy( errmld, DynErrmld() );
      return lStatus_Zartwg;
   }

   s = 0;
   while ( lStatus_Zartwg == 0 && s == 0 )
   {
     lStatus_Zartwg =  SqlFetch( fd_sel, 1, &Buf_Zartwg, NULL );

     if ( lStatus_Zartwg == 0 )
     {
       s = ReadTemp( fd_read, Buf_Zartwg.ARTIKEL_NR, errmld );
       if ( s == 100 )
       {
		 s = 0;

#ifdef MIT_BSSICHG		/* 24.01.2003 */
		 /* 23.21.2002 BSSICHG */
		 if ( TestBSSichG( Buf_Zartwg.WARENGRUPPE ) )
			 s = SetBSSichG( Buf_Zartwg.ARTIKEL_NR, "", errmld );  /* hier wgr = "" */
		 /* */
#endif

		 if ( s == 0 )
			s = Loesche_Zartwg( Buf_Zartwg.ARTIKEL_NR, &loe_rabgrp, errmld );

         if ( s == 0 )
		 {
			(*anz_loe)++;

			if (loe_rabgrp == 1)
			{
				(*anz_loe_9)++;
			}
		 }

#ifdef TEST
         printf( "del: %.7ld %s\n",
                 Buf_Zartwg.ARTIKEL_NR, Buf_Zartwg.WARENGRUPPE );
#endif
       }
       else if ( s != 0 )
       {
          strcpy( errmld, DynErrmld() );
       }
     }
     else if ( lStatus_Zartwg != 100 )
     {
       strcpy( errmld, DynErrmld() );
     }
   }

   SqlCloseCs( fd_sel );
   SqlCloseCs( fd_read );

#ifdef TEST
   printf( "Ende von Loeschen\n" );
#endif

   if ( s != 0 )
      return s;
   if ( lStatus_Zartwg == 100 )
      lStatus_Zartwg = 0;

   return lStatus_Zartwg;
}

/* ---------- Eintraege in Zartwg einfuegen/updaten ----------- */


static long Schreibe_Zartwg( long artikel_nr, char *rabgrp, int *upd_rabgrp, char *errmld )
{
   long lStatus;

   lStatus = StoreRecord_Zartwg( errmld );
   if ( lStatus != 0 ) return lStatus;

   lStatus = Schreibe_Rabattgruppe( artikel_nr, rabgrp, upd_rabgrp, errmld );
   if ( lStatus != 0 ) return lStatus;
   
   lStatus = StoreRecord_Zapflege( artikel_nr, errmld );
   if ( lStatus != 0 ) return lStatus;

   if ( FdTransact( errmld ) != 0 )
   {
      return -1;
   }

   return 0;
}

long Insert_From_ImsTemp( char *temp_name, char *errmld,
                          long *anz_ins, long *anz_upd,
						  long *anz_ins_9, long *anz_upd_9, long *anz_loe_9 )
{
   int fd_sel;
   int fd_read;
   long s;
   char sql[200];
   long artikel_nr;
   long imswgr_nr;
   int upd_rabgrp;
   char rabgrp[4];

/* *anz_ins = 0;
   *anz_upd = 0; */

   if (  GetBufferDesc_Zapflege( errmld ) != 0 )
   {
      return -1;
   }

   if ( GetBufferDesc_Zartwg( errmld ) != 0 )
   {
      return -1;
   }

   if ( GetBufferDesc_Artkatg( errmld ) != 0 )
   {
      return -1;
   }

   if ( DeclReadZartwg( &fd_read, errmld ) != 0 )
   {
     return -1;
   }

#ifdef TEST
   printf( "Anfang von Inserten\n" );
#endif

/*
   sprintf( sql, "select artikel_nr,imswgr_nr from %s order by ARTIKEL_NR",
                 temp_name );
*/
   sprintf( sql, "select artikel_nr,imswgr_nr from %s", temp_name );
   s = SqlOpenCsWh( &fd_sel, sql );
   if ( s != 0 )
   {
      strcpy( errmld, DynErrmld() );
      return s;
   }

   lStatus_Zartwg = 0;
   while ( lStatus_Zartwg == 0 && s == 0 )
   {
     s  =  SqlFetch( fd_sel, 1, &artikel_nr, &imswgr_nr, NULL );

     if ( s == 0 )
     {
	   Read_Artkatg(imswgr_nr, rabgrp, errmld);

       ReadZartwg( fd_read, artikel_nr, errmld );
       if ( lStatus_Zartwg == 0 || lStatus_Zartwg == 100 )  /* !!!!!! anders*/
       {
          Buf_Zartwg.ARTIKEL_NR = artikel_nr;
          *Buf_Zartwg.WARENGRUPPE = '\0';
          s_longcatl( Buf_Zartwg.WARENGRUPPE, imswgr_nr,
                      L_ZARTWG_WARENGRUPPE, '0' );

          /* schreiben nur wenn WGR ungleich oder nicht vorhanden */
          if ( lStatus_Zartwg == 100 ||
               strcmp(Buf_Zartwg.WARENGRUPPE, BufOld_Zartwg.WARENGRUPPE) != 0 )
          {
             long lStat;
			 lStat = 0;

#ifdef MIT_BSSICHG		/* 24.01.2003 */
			 /* 23.21.2002 BSSICHG */
			 if ( TestBSSichG( Buf_Zartwg.WARENGRUPPE ) )
				 lStat = SetBSSichG( Buf_Zartwg.ARTIKEL_NR, Buf_Zartwg.WARENGRUPPE, errmld );
			 /* */
#endif

			 if ( lStat == 0 )
			 {
				upd_rabgrp = 0;
                lStat = Schreibe_Zartwg( artikel_nr, rabgrp, &upd_rabgrp, errmld );
			 }

             if ( lStat == 0 )
             {
                if ( lStatus_Zartwg == 100 )
                   (*anz_ins)++;
                else
                   (*anz_upd)++;

				if (upd_rabgrp == 1)
				{
					(*anz_loe_9)++;
				}
				else if (upd_rabgrp == 2)
				{
					(*anz_upd_9)++;
				}
				else if (upd_rabgrp == 3)
				{
					(*anz_ins_9)++;
				}
             }
             lStatus_Zartwg = lStat;
#ifdef TEST
              printf( "ins: %.7ld %s\n",
                      Buf_Zartwg.ARTIKEL_NR, Buf_Zartwg.WARENGRUPPE );
#endif
          }
       }

     }
     else if ( s != 100 )
     {
       strcpy( errmld, DynErrmld() );
     }
   }

   SqlCloseCs( fd_read );
   SqlCloseCs( fd_sel );

#ifdef TEST
   printf( "Ende von Inserten\n" );
#endif

   if ( lStatus_Zartwg != 0 )
     return lStatus_Zartwg;
   if ( s == 100 ) s = 0;
   return s;
}
