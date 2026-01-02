/* ---------------------------------------------------------------------- *
 *                         R E S T L O E . C                              *
 * ---------------------------------------------------------------------- *
 * Projekt:  PHOSIX + REGIOEK                                           *
 * Gruppe:   Artikel loeschen                                             *
 * ---------------------------------------------------------------------- *
 * Autor  :  Schmitt                                                      *
 * Anfang :  10.10.1998                                                   *
 * Update :                                                               *
 * ---------------------------------------------------------------------- */

/* --- Include-Dateien einbinden ---------------------------------------- */

#include <stdio.h>                                /* C-Standard-Libraries */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "hdatum/phodate.h"
#include "libscsvoodoo/libscsvoodoo.h"

/* ----------------- Prototype ------------------------ */

void CloseBase( void );
int  IsStandartEngine( );
long OpenBase( char *db, char *errmld );

/* ----------------- Usage ------------------------ */

void RestArtLoeUsage( char *buf )
{
   strcat( buf, "- zpmasaen 6 DBase-Zdp DBase-Rek [PZN]\n" );
   strcat( buf, "  loescht Saetze aus PZN-abhaengigen Relationen\n" );
   strcat( buf, "  deren PZN in DBase-Zdp:ZARTLOESCH stehen\n" );
   strcat( buf, "  1. ohne PZN: alle Artikel aus ZARTLOESCH\n" );
   strcat( buf, "  2. mit  PZN: Artikel mit PZN wenn in ZARTLOESCH\n" );
}

struct LOESCH_RELATION
{
	int  fd;
	char *rel;
};

int fd_carticlecodes = -1;

struct LOESCH_RELATION regioek[] =
{
	{ -1, "articlecondition" },
	{ -1, "artikelabverkauf" },
	{ -1, "artikelf" },
	{ -1, "artlnr" },
	{ -1, "artprog" },
	{ -1, "defekte" },
	{ -1, "defektw" },
	{ -1, "kettart" }, 
	{ -1, "nachfw" },
	{ -1, "pseudoart" },                               
	{ -1, "regioartinfo" },                                                                                                                            
	{ -1, "stammhausstation" },              
	{ -1, "stammlagerartikel" },
	{ -1, "wafo" },
	{ -1, "vzartinfo" },

	// Thomas Arnold
	{ -1, "defektw_cmi" },
	{ -1, "nachfw_cmi" },
	{ -1, "zaneuheit" },
};

#define ANZ_REGIOEK ( sizeof( regioek ) / sizeof( struct LOESCH_RELATION ) )


/* --- SET ISOLATION-Fehler bei SE -------------------------------------- */

#define SQL_TABLENOTFOUND_ERROR   (-206)

static long Init_Loeschen_Db( char *db, int anz, struct LOESCH_RELATION *loerel, char *errmld )
{
	long s;
	int  i;
	char sql[200];
	char desc[70];

	s = 0;

	i = 0;
	while ( i < anz && s == 0 )
	{
/*		if ( IsStandartEngine( ) )
		{
			sprintf( desc, "%s.artikel_nr", loerel[i].rel );
			sprintf( sql, "delete from %s where artikel_nr=?",
				      	  loerel[i].rel );
		}
		else */
		{
			sprintf( desc, "%s:%s.artikel_nr", db, loerel[i].rel );
			sprintf( sql, "delete from %s:%s where artikel_nr=?",
						  db,
						  loerel[i].rel );
		}

		s = SqlPrepareStmnt( &loerel[i].fd,
							 sql,
							 desc,
							 NULL );

		if ( s == SQL_TABLENOTFOUND_ERROR )
		{
			s = 0;
			loerel[i].fd = -2;
		}

		if ( s == 0 )
			i++;
	}

	if ( s != 0 )
		sprintf( errmld, "%s:%s\n%s", db, loerel[i].rel, DynErrmld() );
	else
	{
		//Init carticlecodes --> leider hier "articleno"
		sprintf( desc, "%s:carticlecodes.articleno", db );
		sprintf( sql, "delete from %s:carticlecodes where articleno=?",
						  db );
		s = SqlPrepareStmnt( &fd_carticlecodes,
							 sql,
							 desc,
							 NULL );

		if ( s == SQL_TABLENOTFOUND_ERROR )
		{
			s = 0;
			fd_carticlecodes = -2;
		}
	
		if ( s != 0 )
			sprintf( errmld, "%s:carticlecodes\n%s", db, DynErrmld() );
	}

	return s;
}

static long Init_Loeschen( char *db1, char *db2, char *errmld )
{
	long s;

	/* nur ein Löschaufruf mit der Regio-Ek-Datenbank */
	s = Init_Loeschen_Db( db2, ANZ_REGIOEK, regioek, errmld );

/*	s = Init_Loeschen_Db( db1, ANZ_PHOSIX, phosix, errmld );
	if ( !IsStandartEngine( ) )
	{
		if ( s == 0 )
			s = Init_Loeschen_Db( db2, ANZ_REGIOEK, regioek, errmld );
	} */

	return s;
}


static long Execute_Loeschen_E( char *db, int anz, struct LOESCH_RELATION *loerel, 
							    long artikel_nr, char *errmld )
{
 
	long s;
	int  i;

	s = 0;
	i = 0;
    while ( i < anz && s == 0 )
    {
        if ( -2 == loerel[i].fd )
        {
            i++;
            continue;
        }

		s = SqlExecutePrepare( loerel[i].fd, &artikel_nr, NULL );

		if ( s == 0 )
			i++;
	}	
	
	if ( s != 0 )
		sprintf( errmld, "%s:%s\n%s", db, loerel[i].rel, DynErrmld() );
	else
	{
		//carticlecodes
		s = SqlExecutePrepare( fd_carticlecodes, &artikel_nr, NULL );

		if ( s != 0 )
			sprintf( errmld, "%s:carticlecodes\n%s", db, DynErrmld() );
	}

	return s;
}

static long Execute_Loeschen( char *db1, char *db2, long artikel_nr, char *errmld )
{
	long s;

	/* nur ein Löschaufruf mit der Regio-Ek-Datenbank */
	s = Execute_Loeschen_E( db2, ANZ_REGIOEK, regioek, artikel_nr, errmld );

/*	s = Execute_Loeschen_E( db1, ANZ_PHOSIX, phosix, artikel_nr, errmld );

	if ( !IsStandartEngine( ) )
	{
		if ( s == 0 )
			s = Execute_Loeschen_E( db2, ANZ_REGIOEK, regioek, artikel_nr, errmld );
	} */

	return s;
}

static void Free_Loeschen_E( int anz, struct LOESCH_RELATION *loerel )
{
	int i;
	for ( i = 0; i < anz; i++ )
	{
		if ( loerel[i].fd >= 0 )
			SqlFreePrepare( loerel[i].fd );
		loerel[i].fd = -1;
	}

	if ( fd_carticlecodes >= 0 )
		SqlFreePrepare( fd_carticlecodes );
	fd_carticlecodes = -1;
}
	
static void Free_Loeschen( )
{
	/* nur ein Löschaufruf mit der Regio-Ek-Datenbank */

	Free_Loeschen_E( ANZ_REGIOEK, regioek );

/*	Free_Loeschen_E( ANZ_PHOSIX,  phosix );
	if ( !IsStandartEngine( ) )
		Free_Loeschen_E( ANZ_REGIOEK, regioek ); */
}


static int fd_zart = -1;

static long Declare_Zartikel( char *errmld )
{
	long s;
	s = SqlDeclareCsWh ( &fd_zart, 
					     "select artikel_nr from zartikel where artikel_nr=?",
					     "zartikel.artikel_nr",
					     NULL );
	if ( s != 0 )
		sprintf( errmld, "zartikel:\n%s", DynErrmld() );

	return s;
}

static long Read_Zartikel( long artikel_nr, char *errmld )
{
	long s;

	s = SqlReadDeclCs( fd_zart, &artikel_nr, NULL, &artikel_nr, NULL );
	if (!( s == 0 || s == 100 ) )
		sprintf( errmld, "zartikel:\n%s", DynErrmld() );

	return s;
}

static void Close_Zartikel( )
{
	if ( fd_zart >= 0 )
		SqlCloseCs ( fd_zart );
	fd_zart = -1;
}

static long LoescheAll( char *db1, char *db2, long artikel_nr, long tagesdatum, int fd_zartloe, char *buf )
{
   long s;;

   s = Execute_Loeschen( db1, db2, artikel_nr, buf );
   if ( s == 0 )
   {
	  s = SqlExecutePrepare( fd_zartloe, &artikel_nr, &tagesdatum, NULL );
	  if ( s != 0 )
	  {
			strcpy( buf, "ZARTLOESCH\n" );
            strcat( buf, DynErrmld() );
	  }
   }

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

static long LoescheArtikel_E( char *db1, char *db2, char *buf )
{
	long upddatum;
	long tagesdatum;
	long datum_restloesch;
	long artikel_nr;
	long s;
	long anz;
	int  fd;
	int  fd_zartloe;
	char sql[30];
	char z_buf[51];

	tagesdatum = GetPhoDate();


	s = Declare_Zartikel( buf );
	if ( s != 0 )
		return s;

	/* With hold oeffnen */
	s = SqlOpenCsWh( &fd, buf );
	if ( s != 0 )
	{
		strcpy( buf, "ZARTLOESCH\n" );
		strcat( buf, DynErrmld() );
		Close_Zartikel( );
		return s;
	}

	s = Init_Loeschen( db1, db2, buf );
	if ( s != 0 )
	{
		Free_Loeschen( );
		SqlCloseCs( fd );
		Close_Zartikel( );
		return s;
	}

	sprintf( sql, "where current of %s", SqlGetCursor( fd ) );
   	s = SqlPrepareUpdate ( &fd_zartloe, "zartloesch", "artikel_nr, datum_restloesch", sql );
 
	if ( s != 0 )
	{
		strcpy( buf, "ZARTLOESCH\n" );
        strcat( buf, DynErrmld() );
		Free_Loeschen( );
		SqlCloseCs( fd );
		Close_Zartikel( );
		return s;
	}

	anz = 0;
	while ( s == 0 )
	{
		s = SqlBeginWork();
		if ( s != 0 )
			strcpy( buf, DynErrmld() );

		if ( s == 0 )
			s = SqlFetch( fd, 1, &artikel_nr, &datum_restloesch, NULL );

		if ( s == 0 )
		{
			s = Read_Zartikel( artikel_nr, buf );

		    if ( s == 100 )
			{
				s = 0;
			}

			if ( s == 0 )
			{
				upddatum = tagesdatum;
				s = LoescheAll( db1, db2, artikel_nr, upddatum, fd_zartloe, buf );
			}
		}
		else
		{
			if ( s != 100 )
			{
				strcpy( buf, "ZARTLOESCH\n" );
				strcat( buf, DynErrmld() );
			}
		}

		if ( s == 0 )
			anz++;
	}

	SqlFreePrepare( fd_zartloe );
	Free_Loeschen( );
	SqlCloseCs( fd );
	Close_Zartikel( );

	sprintf( z_buf, "\nEs wurden %ld Artikel geloescht", anz );

	if ( s == 100 )
	{
		s = 0;
		if ( anz == 0 )
			strcpy( buf, "Keine zu loeschenden Artikel vorhanden" );
		else
			strcpy( buf, "Loeschen erfolgreich" );
	}
	strcat( buf, z_buf );
	return s;
}

static long LoescheEinzelArtikel( char *db1, char *db2, long artikel_nr, char *buf )
{
	sprintf( buf,
			 "select artikel_nr, datum_restloesch from zartloesch " \
			 "where datum_restloesch = 0 and artikel_nr=%ld for update",
             artikel_nr );
	return LoescheArtikel_E( db1, db2, buf );
}

static long LoescheArtikel( char *db1, char *db2, char *buf )
{
	sprintf( buf,
			 "select artikel_nr, datum_restloesch from zartloesch " \
			 "where datum_restloesch = 0 for update" );
	return LoescheArtikel_E( db1, db2, buf );
}

long RestArtLoeLoop ( char *db1, char *db2, char *cArtNr, char *buf )
{
   long s;
   long artikel_nr;
 
   if ( cArtNr != NULL )
   {
       int i;
       i = 0;
       while ( isdigit(cArtNr[i]) ) i++;
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

	s = OpenBase( db1, buf );
	if ( s == 0 )
	{
		if ( cArtNr == NULL )
			s = LoescheArtikel( db1, db2, buf );
        else
			s = LoescheEinzelArtikel( db1, db2, artikel_nr, buf );
		CloseBase();
	}
   return s;
}

