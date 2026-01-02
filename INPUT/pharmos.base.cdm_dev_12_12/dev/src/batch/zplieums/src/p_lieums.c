/* ---------------------------------------------------------------------- *
 *                      P _ L I E U M S . C                               *
 * ---------------------------------------------------------------------- *
 * Projekt:  ZDP                                                          *
 * Gruppe:   Lieferanten tauschen                                         *
 * ---------------------------------------------------------------------- *
 * Autor  :  Schmitt                                                      *
 * Anfang :  26.07.1999                                                   *
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

#include <wpp_dbas.h>
#include <wpp_prot.h>

#include <liefer.h>
#include <bliefer.h>
#include <herlief.h>
#include <pflege.h>
#ifdef SAP_R3
#include <zliefsapr3.h>
#endif

#define L_LANT_NR 5
#define L_BESLA_NR 5
#define L_HERSTELLER_NR 5

/* ----------------- Prototype ------------------------ */

void CloseBase( void );
long OpenBase( char *db, char *errmld );

/* ----------------- Usage ------------------------ */

void LieUmsUsage( char *buf )
{
   strcat( buf, "- zplieums 1 Database User LantAlt LantNeu [LantAlt LantNeu]...\n" );
   strcat( buf, "  Lieferant LantAlt->LantNeu umsetzen\n" );
}


/* ----- Anzahl ----------------- */

static int anz_liefer;
static int anz_bliefer;
static int anz_herlief;
static int anz_zliefsapr3;

/* ------ Modus 26.08.2011 ----------------- */

static int isCdcAlone;		/* = 1 Zentrale Pflegedatenbank alleine*/
						    /* = 0 Zentrale Pflegedatenbank zusammen mit zu pflegenden Datenbanken*/

static void InitAnz( )
{
   char wert[300];	/*	26.08.2011 */

  if ( UnxGetenv( "CDC_ALONE", wert ) == 0 )	/*	26.08.2011 */ /* central data care alone */
	isCdcAlone = 1;	
  else
    isCdcAlone = 0;	

   anz_liefer  = 0;
   anz_bliefer = 0;
   anz_herlief = 0;
   anz_zliefsapr3 = 0;


}

static void ReportAnz( char *meld, char *buf )
{
  sprintf( buf, "%s\n" \
                "liefer:     %d\n" \
                "bliefer:    %d\n" \
                "herlief:    %d\n" \
                "zliefsapr3: %d",
                meld,
                anz_liefer,
                anz_bliefer,
                anz_herlief, 
                anz_zliefsapr3 );
}


/* ----- Pflege  ------------------------- */

static int Fd_Pflege = -1;

static int GetBufferDesc_Pflege( char * errmld )
{
   char *tabelle = "pflege";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");
   if ( Fd_Pflege >= 0 ) return 0;

   if ( isCdcAlone == 0 )									/*	26.08.2011 */
		lStatus = OpenBufferDesc( &Fd_Pflege, tabelle,
			                      NULL, NULL,
				                  V_PROTO_VERTEIL,			/* Schreiben, Protokoll und Verteil */
					              errstr );
   else
		lStatus = OpenBufferDesc( &Fd_Pflege, tabelle,		/* so wie früher: nur Protokoll und verteil */
			                      NULL, NULL,
				                  V_ONLY_PROTO_VERTEIL,
					              errstr );
   if ( lStatus != 0 )
   {
     sprintf( errmld, "%s: %s", tabelle, errstr );
     Fd_Pflege = -1;
     return -1;
   }
   return 0;
}

static long Insert_Pflege( long lantnr_alt, long lantnr_neu, char *user,
                           char *cErrmld )
{
   long s;
   char PrimekeyCond[30];
   char errmld[100];
   struct PFLEGE  Buf_Pflege;

   if (  GetBufferDesc_Pflege( cErrmld ) != 0 ) return -1;

   Buf_Pflege.PFLEGE_NR = 0;
   Buf_Pflege.DATUM     = GetPhoDate();
   Buf_Pflege.UHRZEIT   = GetPhoTime();
   strcpy( Buf_Pflege.ANWENDER, user );
   strcpy( Buf_Pflege.STATUS, "0" );
   strcpy( Buf_Pflege.FEHLERTEXT, " " );
   Buf_Pflege.FUNKTION = 2;       /* Tausch LANT_NR */
   sprintf( Buf_Pflege.INFO, "%ld %ld", lantnr_alt, lantnr_neu );

   strcpy ( PrimekeyCond, "PFLEGE_NR=0" );

   s = FdWithoutWorkInsertRecord( Fd_Pflege, &Buf_Pflege,
                                  PrimekeyCond, errmld  );
   if ( s != 0 )
   {
       strcpy( cErrmld, "FdInsert pflege\n" );
       strcat( cErrmld, errmld );
   }
   return s;
}

/* ----------------- Liefer Umsetzen ------------------ */

static int m_Fd_Liefer = -1;

int GetBufferDesc_Liefer( char *cErrmld )
{
   char *tabelle = "liefer";
   long s;
   char errmld[100];

   *cErrmld = '\0';

   if ( m_Fd_Liefer >= 0 ) return 0;

   /* s = OpenBufferDesc( &m_Fd_Liefer, tabelle,
                       NULL, NULL, V_PROTO_VERTEIL, errmld ); */

   /* direkter Aufruf von OpenBufferDescProj, um select * beim Read zu vermeiden */
   s = OpenBufferDescProj( &m_Fd_Liefer, tabelle, PROJECTION_LIEFER,
                       NULL, NULL, V_PROTO_VERTEIL, errmld );

   if ( s != 0 )
   {
     strcpy( cErrmld, errmld );
     strcat( cErrmld, "\ntable " );
     strcat( cErrmld, tabelle );
     m_Fd_Liefer = -1;
     return -1;
   }
   return 0;
}

static long LieferUms( char *user, long lantnr_alt, long lantnr_neu,
                       char *cErrmld )
{
   long s;
   int  lng;
   char errmld[200];
   char format[30];
   char PrimekeyCondNeu[30];
   char PrimekeyCondAlt[30];
   struct LIEFER liealt;
   struct LIEFER lieneu;

   if (  GetBufferDesc_Liefer( cErrmld ) != 0 ) return -1;

   sprintf( format, "LANT_NR=%c%d.ld", '%', L_LANT_NR );

   sprintf( PrimekeyCondNeu, format, lantnr_neu );
   lieneu.LANT_NR = lantnr_neu;

   s = FdReadRecord( m_Fd_Liefer, PrimekeyCondNeu, &lieneu, errmld );
   if ( s == 0 )
   {
     sprintf( cErrmld, "LantNr-Neu = %ld bereits vorhanden", lantnr_neu );
     return -1;
   }
   if ( s != 100 )
   {
     sprintf( cErrmld, "LantNr-Neu: %s", DynErrmld() );
     return s;
   }

   sprintf( PrimekeyCondAlt, format, lantnr_alt );
   liealt.LANT_NR = lantnr_alt;

   s = FdReadRecord( m_Fd_Liefer, PrimekeyCondAlt, &liealt, errmld );
   if ( s == 100 )
   {
     sprintf( cErrmld, "LantNr-Alt = %ld nicht vorhanden", lantnr_alt );
     return -1;
   }
   if ( s != 0 )
   {
     sprintf( cErrmld, "LantNr-Alt: %s", DynErrmld() );
     return s;
   }

   lieneu = liealt;
   lieneu.LANT_NR = lantnr_neu;
   memset( lieneu.BEARBEITER, ' ', 8 );
   lieneu.BEARBEITER[8] = '\0';
   lng =  strlen( user );
   if ( lng > 8 ) lng = 8;
   memcpy( lieneu.BEARBEITER, user, lng );
/*
   lieneu.DATUM_ANLAGE = GetPhoDate();
   lieneu.DATUM_AENDER = 0;
*/
   lieneu.DATUM_AENDER = GetPhoDate();

   s = FdWithoutWorkDeleteRecord( m_Fd_Liefer, &liealt, PrimekeyCondAlt,
                                  errmld );
   if ( s != 0 )
   {
       strcpy( cErrmld, "FdDelete liefer\n" );
       strcat( cErrmld, errmld );
       return s;
   }
   s = FdWithoutWorkInsertRecord( m_Fd_Liefer, &lieneu, PrimekeyCondNeu,
                                  errmld );
   if ( s != 0 )
   {
       strcpy( cErrmld, "FdInsert liefer\n" );
       strcat( cErrmld, errmld );
       return s;
   }

   anz_liefer++;

   return s;
}

/* ----------------- Bliefer Umsetzen ------------------ */

static int m_Fd_Bliefer = -1;

int GetBufferDesc_Bliefer( char *cErrmld )
{
   char *tabelle = "bliefer";
   long s;
   char errmld[100];

   *cErrmld = '\0';

   if ( m_Fd_Bliefer >= 0 ) return 0;

/*   s = OpenBufferDesc( &m_Fd_Bliefer, tabelle,
                       NULL, NULL, V_PROTO_VERTEIL, errmld ); */

   /* direkter Aufruf von OpenBufferDescProj, um select * beim Read zu vermeiden */
   s = OpenBufferDescProj( &m_Fd_Bliefer, tabelle, PROJECTION_BLIEFER,
                       NULL, NULL, V_PROTO_VERTEIL, errmld );

   if ( s != 0 )
   {
     strcpy( cErrmld, errmld );
     strcat( cErrmld, "\ntable " );
     strcat( cErrmld, tabelle );
     m_Fd_Bliefer = -1;
     return -1;
   }
   return 0;
}

static long BlieferUms( char *user, long lantnr_alt, long lantnr_neu,
                        char *cErrmld )
{
   long s;
   int  fd;
   char errmld[200];
   char format[30];
   char sql[1000];
   char PrimekeyCond[30];
   struct BLIEFER bliealt;
   struct BLIEFER blieneu;

   if (  GetBufferDesc_Bliefer( cErrmld ) != 0 ) return -1;

   sprintf( format, "BESLA_NR=%c%d.ld", '%', L_BESLA_NR );

   sprintf( sql, "select %s from BLIEFER where LANT_NR=%ld",
                 PROJECTION_BLIEFER, lantnr_alt );

   s = SqlOpenCsWh( &fd, sql );

   if ( s != 0 )
   {
     strcpy( cErrmld, "bliefer\n" );
     strcat( cErrmld, DynErrmld() );
     return s;
   }

   while ( s == 0 )
   {
      s = SqlFetch( fd, 1, &bliealt, NULL );
      if ( s == 0 )
      {
        blieneu = bliealt;
        blieneu.LANT_NR = lantnr_neu;
        sprintf( PrimekeyCond, format, blieneu.BESLA_NR );
        s = FdWithoutWorkUpdateRecord( m_Fd_Bliefer,
                                       &blieneu, &bliealt,
                                       PrimekeyCond, errmld );
        if ( s == 0 )
          anz_bliefer++;
        else
        {
          strcpy( cErrmld, "FdUpdate bliefer\n" );
          strcat( cErrmld, errmld );
        }
      }
      else if ( s != 100 )
      {
        strcpy( cErrmld, "Fetch bliefer\n" );
        strcat( cErrmld, DynErrmld() );
      }
   }

   if ( s == 100 )
      return 0;
   else
      return s;
}


/* ----------------- Herlief Umsetzen ------------------ */

static int m_Fd_Herlief = -1;

int GetBufferDesc_Herlief( char *cErrmld )
{
   char *tabelle = "herlief";
   long s;
   char errmld[100];

   *cErrmld = '\0';

   if ( m_Fd_Herlief >= 0 ) return 0;

   /* s = OpenBufferDesc( &m_Fd_Herlief, tabelle,
                       NULL, NULL, V_PROTO_VERTEIL, errmld ); */

   /* direkter Aufruf von OpenBufferDescProj, um select * beim Read zu vermeiden */
   s = OpenBufferDescProj( &m_Fd_Herlief, tabelle, PROJECTION_HERLIEF,
                       NULL, NULL, V_PROTO_VERTEIL, errmld );

   if ( s != 0 )
   {
     strcpy( cErrmld, errmld );
     strcat( cErrmld, "\ntable " );
     strcat( cErrmld, tabelle );
     m_Fd_Herlief = -1;
     return -1;
   }
   return 0;
}

static long HerliefUms( char *user, long lantnr_alt, long lantnr_neu,
                        char *cErrmld )
{
   long s;
   int  fd;
   char errmld[200];
   char format[60];
   char sql[100];
   char PrimekeyCond[60];
   struct HERLIEF hlalt;
   struct HERLIEF hlneu;

   if (  GetBufferDesc_Herlief( cErrmld ) != 0 ) return -1;

   sprintf( format, "LANT_NR=%c%d.1ld and HERSTELLER_NR=%c%d.1ld",
                    '%', L_LANT_NR,
                    '%', L_HERSTELLER_NR );

   sprintf( sql, "select %s from HERLIEF where LANT_NR=%ld",
                 PROJECTION_HERLIEF, lantnr_alt );

   s = SqlOpenCsWh( &fd, sql );

   if ( s != 0 )
   {
     strcpy( cErrmld, "Herlief\n" );
     strcat( cErrmld, DynErrmld() );
     return s;
   }

   while ( s == 0 )
   {
      s = SqlFetch( fd, 1, &hlalt, NULL );
      if ( s == 0 )
      {
         sprintf( PrimekeyCond, format, hlalt.LANT_NR, hlalt.HERSTELLER_NR );
         s = FdWithoutWorkDeleteRecord( m_Fd_Herlief, &hlalt, PrimekeyCond,
                                        errmld );
         if ( s != 0 )
         {
            strcpy( cErrmld, "FdDelete herlief\n" );
            strcat( cErrmld, errmld );
         }
         else
         {
            sprintf( PrimekeyCond, format, lantnr_neu, hlalt.HERSTELLER_NR );
            s = FdReadRecord( m_Fd_Herlief, PrimekeyCond, &hlneu, errmld );
            if ( s == 100 )
            {
               hlneu = hlalt;
               hlneu.LANT_NR = lantnr_neu;
               if ( hlneu.HERSTELLER_NR != 0 )
               {
                  s = FdWithoutWorkInsertRecord( m_Fd_Herlief, &hlneu,
                                                 PrimekeyCond, errmld );
                  if ( s != 0 )
                  {
                    strcpy( cErrmld, "FdInsert herlief\n" );
                    strcat( cErrmld, errmld );
                  }
               }
               else     /* Hersteller-Nr 0 wird nicht umkopiert */
                  s = 0;
            }
            else if ( s != 0 )
            {
              strcpy( cErrmld, "FdRead herlief\n" );
              strcat( cErrmld, errmld );
            }
         }
         if ( s == 0 )
           anz_herlief++;
      }
      else if ( s != 100 )
      {
        strcpy( cErrmld, "Fetch herlief\n" );
        strcat( cErrmld, DynErrmld() );
      }
   }

   if ( s == 100 )
      return 0;
   else
      return s;
}

/* ----------------- Zliefsapr3 umsetzen ------------------ */

#ifdef SAP_R3

static int m_Fd_Zliefsapr3 = -1;

int GetBufferDesc_Zliefsapr3( char *cErrmld )
{
   char *tabelle = "zliefsapr3";
   long s;
   char errmld[100];

   *cErrmld = '\0';

   if ( m_Fd_Zliefsapr3 >= 0 ) return 0;

   /* s = OpenBufferDesc( &m_Fd_Zliefsapr3, tabelle,
                       NULL, NULL, V_PROTO_VERTEIL, errmld ); */

   /* direkter Aufruf von OpenBufferDescProj, um select * beim Read zu vermeiden */
   s = OpenBufferDescProj( &m_Fd_Zliefsapr3, tabelle, PROJECTION_ZLIEFSAPR3,
                       NULL, NULL, V_PROTO_VERTEIL, errmld );

   if ( s != 0 )
   {
     strcpy( cErrmld, errmld );
     strcat( cErrmld, "\ntable " );
     strcat( cErrmld, tabelle );
     m_Fd_Zliefsapr3 = -1;
     return -1;
   }
   return 0;
}

static long ZLiefsapr3Ums( char *user, long lantnr_alt, long lantnr_neu,
                        char *cErrmld )
{
   long s;
   int  fd;
   char errmld[200];
   char format[60];
   char sql[200];
   char PrimekeyCond[60];
   struct ZLIEFSAPR3 zls3alt;
   struct ZLIEFSAPR3 zls3neu;

   if (  GetBufferDesc_Zliefsapr3( cErrmld ) != 0 ) return -1;

   sprintf( format, "LANT_NR=%c%d.1ld and DELCREDERE_ART = %cc",
                    '%', L_LANT_NR, '%' );

   sprintf( sql, "select %s from ZLIEFSAPR3 where LANT_NR=%ld",
                 PROJECTION_ZLIEFSAPR3, lantnr_alt );

   s = SqlOpenCsWh( &fd, sql );

   if ( s != 0 )
   {
     strcpy( cErrmld, "Zliefsapr3\n" );
     strcat( cErrmld, DynErrmld() );
     return s;
   }

   while ( s == 0 )
   {
      s = SqlFetch( fd, 1, &zls3alt, NULL );
      if ( s == 0 )
      {
         sprintf( PrimekeyCond, format, zls3alt.LANT_NR, zls3alt.DELCREDERE_ART[0]);
         s = FdWithoutWorkDeleteRecord( m_Fd_Zliefsapr3, &zls3alt, PrimekeyCond,
                                        errmld );
         if ( s != 0 )
         {
            strcpy( cErrmld, "FdDelete zliefsapr3\n" );
            strcat( cErrmld, errmld );
         }
         else
         {
            sprintf( PrimekeyCond, format, lantnr_neu, zls3alt.DELCREDERE_ART[0] );
            s = FdReadRecord( m_Fd_Zliefsapr3, PrimekeyCond, &zls3neu, errmld );
            if ( s == 100 )
            {
				zls3neu = zls3alt;
				zls3neu.LANT_NR = lantnr_neu;
				s = FdWithoutWorkInsertRecord( m_Fd_Zliefsapr3, &zls3neu,
												PrimekeyCond, errmld );
				if ( s != 0 )
				{
					strcpy( cErrmld, "FdInsert zliefsapr3\n" );
					strcat( cErrmld, errmld );
				}
			}
            else if ( s != 0 )
            {
              strcpy( cErrmld, "FdRead zliefsapr3\n" );
              strcat( cErrmld, errmld );
            }
         }

         if ( s == 0 )
           anz_zliefsapr3++;

      }
      else if ( s != 100 )
      {
        strcpy( cErrmld, "Fetch zliefsapr3\n" );
        strcat( cErrmld, DynErrmld() );
      }
   }

   if ( s == 100 )
      return 0;
   else
      return s;
}
#endif

/* ----------------- Alles Umsetzen ------------------ */

static long Umsetzen( char *user, long LantAlt, long LantNeu,
                      char *errmld )
{
   long s;
   s = SqlBeginWork();
   if ( s != 0 )
   {
     strcpy( errmld, DynErrmld() );
     return -1;
   }

   s = LieferUms( user, LantAlt, LantNeu, errmld );

   if ( s == 0 )
      s = BlieferUms( user, LantAlt, LantNeu, errmld );

   if ( s == 0 )
      s = HerliefUms( user, LantAlt, LantNeu, errmld );

#ifdef SAP_R3
   if ( s == 0 )
      s = ZLiefsapr3Ums( user, LantAlt, LantNeu, errmld );
#endif

   if ( s == 0 )
      s = Insert_Pflege( LantAlt, LantNeu, user, errmld );

   if ( s == 0 )
   {
      s = SqlCommitWork();
      if ( s != 0 )
         strcpy( errmld, DynErrmld() );
   }
   else
      SqlRollbackWork();

   return s;
}


/* ----------------- Loop Umsetzen ------------------ */

long LieUmsLoop ( char *db, char *user, int anz, char* LantNr[], char *buf  )
{
   long s;
   int  i;
   char errmld[50];

   s = OpenBase( db, buf );
   if ( s == 0 )
   {
     s = OpenPflege( user, buf );
     if ( s == 0 )
     {
        InitAnz( );
        i = 0;
        while ( s == 0 && i < anz )
        {
           s = Umsetzen( user, atol(LantNr[2*i]), atol(LantNr[2*i+1]),
                         buf );
           if ( s == 0 ) i++;
        }
        if ( s == 0 )
           ReportAnz( "Umsetzen erfolgreich", buf );
        ClosePflege( errmld );
     }
     CloseBase( );
   }
   return s;
}

