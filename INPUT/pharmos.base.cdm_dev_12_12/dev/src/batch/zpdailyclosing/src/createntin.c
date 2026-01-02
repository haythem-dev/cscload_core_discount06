/* ---------------------------------------------------------------------- *
 *                         createNTIN.c                                   *
 * ---------------------------------------------------------------------- *
 * Projekt:  ZDP                                                          *
 * Gruppe:   NTIN´s erzeugen	                                          *
 * ---------------------------------------------------------------------- *
 * Autor  :  Hörath                                                       *
 * ---------------------------------------------------------------------- */

/* --- Include-Dateien einbinden ---------------------------------------- */

#include <stdio.h>                                /* C-Standard-Libraries */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <phodate.h>
#include <libscsvoodoo.h>

#include <wpp_prot.h>
#include <wpp_dbas.h>

#include <carticlecodes.h>
#include <zpznpflege.h>

/* ----------------- Prototype ------------------------ */

void CloseBase( void );
long OpenBase( char *db, char *errmld );

/* ----------------- Usage ------------------------ */

void CreateNtinUsage( char *buf )
{
   strcat( buf, "- zpdailyclosing 3 Database USER\n" );
   strcat( buf, "  NTIN erzeugen für alle aktiven Artikel.\n" );
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

   if ( Fd_Zpznpflege >= 0 ) 
	   return 0;

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

static long StoreRecord_Zpznpflege( char* dezap_sa, long artikel_nr, long datum, char* cErrmld )
{
   long lStatus;
   char PrimekeyCond[100];

   Buf_zpznpflege.ARTIKEL_NR = artikel_nr;
   Buf_zpznpflege.DATUM      = datum;
   strcpy (Buf_zpznpflege.DEZAP_SA, dezap_sa);

   strcpy( cErrmld, "" );

   sprintf( PrimekeyCond, "ARTIKEL_NR=%7ld and DATUM=%ld and DEZAP_SA = '%s'",
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
	  strcpy (Buf_zpznpflege.DEZAP_SA, dezap_sa);
      lStatus = FdDelayInsertRecord( Fd_Zpznpflege, &Buf_zpznpflege,
                                     PrimekeyCond, cErrmld);
   }

   return lStatus;
}

/* ----- CArticleCodes ------------------------- */

static int  Fd_CArticleCodes = -1;

static struct CARTICLECODES Buf_CArticleCodes;

static int GetBufferDesc_CArticleCodes( char * errmld )
{
    char *tabelle = "carticlecodes";
    long lStatus;
    char errstr[80];

    strcpy( errmld, "");

    if ( Fd_CArticleCodes >= 0 )
		return 0;

    lStatus = OpenBufferDescProj( &Fd_CArticleCodes, tabelle, PROJECTION_CARTICLECODES,
                                  NULL, NULL, V_PROTO_VERTEIL, errstr );
                                
    if ( lStatus != 0 )
    {
      sprintf( errmld, "%s: %s", tabelle, errstr );
      Fd_CArticleCodes = -1;
      return -1;
    }

    return 0;
}

static long StoreRecord_CArticleCodes( long artikel_nr, long datum, char* ntin, char* cErrmld )
{
   long lStatus;
   char PrimekeyCond[100];

   Buf_CArticleCodes.ARTICLENO = artikel_nr;
   Buf_CArticleCodes.CODE_TYPE = 22;
   Buf_CArticleCodes.SERIAL_NUMBER = 1;
   Buf_CArticleCodes.PREFERRED_FLAG = 0;
   Buf_CArticleCodes.DATE_CHANGED = datum;
   strcpy(Buf_CArticleCodes.ARTICLE_CODE, ntin);

   strcpy( cErrmld, "" );

   sprintf( PrimekeyCond, "ARTICLENO=%7ld AND CODE_TYPE=%d AND SERIAL_NUMBER=%d", Buf_CArticleCodes.ARTICLENO, Buf_CArticleCodes.CODE_TYPE, Buf_CArticleCodes.SERIAL_NUMBER);
 
   lStatus = FdDelayInsertRecord(Fd_CArticleCodes, &Buf_CArticleCodes, PrimekeyCond, cErrmld);
   
   return lStatus;
}


static long InitAll( char *errmld )
{
   if ( GetBufferDesc_CArticleCodes( errmld ) != 0 ) return -1;
   if ( GetBufferDesc_Zpznpflege( errmld ) != 0 ) return -1;
   return 0;
}


static void FreeAll()
{
   if ( Fd_CArticleCodes >= 0 )
      CloseOneBufferDesc( Fd_CArticleCodes );
   Fd_CArticleCodes = -1;

   if ( Fd_Zpznpflege >= 0 )
      CloseOneBufferDesc( Fd_Zpznpflege );
   Fd_Zpznpflege = -1;
}

static long DoIt( char *user, long artikel_nr, char* ntin, short prefix, long tagesdatum,
                  char *errmld )
{
   long s;
   char code[L_CARTICLECODES_ARTICLE_CODE + 1] = {0};
   int checkdigit;

   // Zusammensetzen Prefix, Ntin, Prüfziffer ...
   sprintf(code, "%d%s", prefix, ntin);

   checkdigit =	 1 * (code[0] - '0');
   checkdigit += 3 * (code[1] - '0');
   checkdigit += 1 * (code[2] - '0');
   checkdigit += 3 * (code[3] - '0');
   checkdigit += 1 * (code[4] - '0');
   checkdigit += 3 * (code[5] - '0');
   checkdigit += 1 * (code[6] - '0');
   checkdigit += 3 * (code[7] - '0');
   checkdigit += 1 * (code[8] - '0');
   checkdigit += 3 * (code[9] - '0');
   checkdigit += 1 * (code[10] - '0');
   checkdigit += 3 * (code[11] - '0');

   checkdigit = checkdigit % 10;
   checkdigit = 10 - checkdigit;

   if (checkdigit == 10)
	   checkdigit = 0;

   code[12] = (checkdigit + '0');
   code[13] = '\0';
   
   s = StoreRecord_CArticleCodes( artikel_nr, tagesdatum, code, errmld );
  
   if ( s == 0 )  
      s = StoreRecord_Zpznpflege( "34", artikel_nr, tagesdatum, errmld );
  
   if ( s == 0 || s == 99 )
      s = FdTransact( errmld );

   return s;
}

static long CreateNtin(  char *db, char *user, char *buf )
{
   long tagesdatum;

   long artikel_nr;
   char ntin[L_CARTICLECODES_ARTICLE_CODE + 1];
   long s;
   long anz;
   int  fd;
   char z_buf[51];
   short referenceCodeType;
   short prefix;
   char sql[100] = {0};

   tagesdatum = GetPhoDate();

   if ( strcmp( db, "ich21" ) == 0 || strcmp( db, "ich21pre" ) == 0 )
   {
       referenceCodeType = 11;
	   prefix = 7680;
   }
   else if ( strcmp( db, "iat21" ) == 0 || strcmp( db, "iat21pre" ) == 0 )
   {
       referenceCodeType = 11;
	   prefix = 6120;
	   strcpy(sql, " and articleno < 9000000 ");
   }
   else if ( strcmp( db, "ide21" ) == 0 )
   {
       referenceCodeType = 16;
	   prefix = 4150;
   }
   else
   {
	   strcpy( buf, "Funktion für dieses Land aktuell nicht implementiert!" );
       return 1;
   }

   sprintf( buf,
				"select ARTICLENO, lpad(trim(ARTICLE_CODE), 8, '0') from CARTICLECODES where " \
				"articleno not in (select articleno from carticlecodes where code_type = 22) and " \
				"articleno in (select artikel_nr from zartikel where datum_ah = 0 and artikel_gesperrt = '0' and artikel_geloescht = '0') " \
				// "and articleno = 112 "
				"and code_type = %d %s ", referenceCodeType, sql );
   
   s = SqlOpenCsWh( &fd, buf );

   if ( s != 0 )
   {
     strcpy( buf, "CARTICLECODES\n" );
     strcat( buf, DynErrmld() );
     return s;
   }

   s = SqlFetch( fd, 1, &artikel_nr, ntin, NULL );
   if ( s == 100 )
   {
     strcpy( buf, "Keine Artikel ohne NTIN vorhanden" );
     return 0;
   }

   if ( s != 0 )
   {
     strcpy( buf, "CARTICLECODES\n" );
     strcat( buf, DynErrmld() );
     return s;
   }

   s = InitAll( buf );
   if ( s != 0 )
   {
      FreeAll( );
      SqlCloseCs( fd );
      return s;
   }

   anz = 0;
   while ( s == 0 )
   {
		s = DoIt( user, artikel_nr, ntin, prefix, tagesdatum, buf );

		if ( s == 0 )
		{
			anz++;
		}
	
		if ( s == 0 )
		{
			s = SqlFetch( fd, 1, &artikel_nr, ntin, NULL );
			if ( s != 0 )
			{
				strcpy( buf, "CARTICLECODES\n" );
				strcat( buf, DynErrmld() );
			}
		}
   }

   FreeAll( );

   SqlCloseCs( fd );

   sprintf( z_buf, "\nEs wurden %ld NTINs angelegt", anz );

   if ( s == 100 )
   {
      s = 0;
      strcpy( buf, "Aktion erfolgreich" );
   }

   strcat( buf, z_buf );
   return s;
}

long CreateNtinLoop ( char *db, char *user, char *buf )
{
   long s;
   char errmld[10];

   
   s = OpenBase( db, buf );
   if ( s == 0 )
   {
     s = OpenPflege( user, buf );
     if ( s == 0 )
     {
        s = CreateNtin( db, user, buf );
        ClosePflege( errmld );
     }
     CloseBase( );
   }

   return s;
}
