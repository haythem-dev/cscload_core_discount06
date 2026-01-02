/* ---------------------------------------------------------------------- *
 *                           u_iherst.c                                   *
 * ---------------------------------------------------------------------- *
 * Projekt:  Einkauf                                                      *
 * Gruppe:   Generiert die Hersteller aus zifaher                         *
 * ---------------------------------------------------------------------- *
 * Autor  :  Schmitt                                                      *
 * Anfang :  28.06.1998                                                   *
 * Update :                                                               *
 * ---------------------------------------------------------------------- */

/* --- Include-Dateien einbinden ---------------------------------------- */

#include <stdio.h>                                /* C-Standard-Libraries */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <libscsvoodoo.h>
#include <phodate.h>

#include <herstel.h>
#include <zifaher.h>
#include <zgrppflege.h>

#define L_HERSTELLER_NR 5

/* --- Prototype  ------------------------------------------------------- */

void CloseBase( void );
long OpenBase ( char *db, char *errmld );

/* -------  Spezielle includes ----------------------------------------- */

#include <tabsqld.h>

#include <wpp_prot.h>
#include <wpp_dbas.h>

/* --------  user -------------- */

static char *user = "IFA     ";

/* ---------- Primekeycondition fuer alles ----------- */

static char PrimekeyCond[100];

/* ----- Herstel ------------------------- */

static char CmpIndikator_Herstel[POSANZ_HERSTEL + 1];
static int  Fd_Herstel = -1;
static long lStatus_Herstel;

static int anz_neuaufnahmen;

static struct HERSTEL Buf_herstel;
static struct HERSTEL BufOld_herstel;

/* ----- zgrppflege ------------------------- */
static long   m_tagesdatum;
static int    m_Fd_Zgrppflege = -1;
static long   m_lStatus_Zgrppflege;
static struct ZGRPPFLEGE m_ZgrppflegeBuf;


void FillCmpIndikator_Herstel ( )
{
   memset( CmpIndikator_Herstel, '1', POSANZ_HERSTEL );
   CmpIndikator_Herstel[POSANZ_HERSTEL] = '\0';
   CmpIndikator_Herstel[P_HERSTEL_DATUM_ANLAGE]  = '0';
   CmpIndikator_Herstel[P_HERSTEL_DATUM_AENDER]  = '0';

}

/*----------------------------------------------------------------*/
void SetTagesdatum( )
{
	m_tagesdatum = PhoToday();
}

/*----------------------------------------------------------------*/
int GetBufferDesc_Zgrppflege( char * errmld )
{
	char *tabelle = "zgrppflege";
	long lStatus;
	char errstr[100];

	strcpy( errmld, "");

	if ( m_Fd_Zgrppflege >= 0 ) 
		return 0;

	lStatus = OpenBufferDesc( &m_Fd_Zgrppflege, tabelle,
                                NULL, NULL, V_OHNE, errstr );
	if ( lStatus != 0 )
	{
		sprintf( errmld, "%s: %s", tabelle, errstr );
		m_Fd_Zgrppflege = -1;
		return -1;
	}
	return 0;
}

/*----------------------------------------------------------------*/
int GetBufferDesc_Herstel( char * errmld )
{
   char *tabelle = "herstel";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");
   if ( Fd_Herstel >= 0 ) return 0;

   FillCmpIndikator_Herstel ( );
   lStatus = OpenBufferDescProj( &Fd_Herstel, tabelle, PROJECTION_HERSTEL,
                                 CmpIndikator_Herstel, NULL,
                                 V_PROTO_VERTEIL,
                                 errstr );
   if ( lStatus != 0 )
   {
     sprintf( errmld, "%s: %s", tabelle, errstr );
     Fd_Herstel = -1;
     return -1;
   }
   return 0;
}

/*----------------------------------------------------------------*/
int InitRecord_Herstel( )
{
   long nr;
   long tagesdatum;

   tagesdatum = PhoToday();
   nr = Buf_herstel.HERSTELLER_NR;

   FdInitTabBuf( Fd_Herstel, &Buf_herstel );

   Buf_herstel.HERSTELLER_NR = nr;
   Buf_herstel.DATUM_ANLAGE = tagesdatum;

   strcpy( Buf_herstel.PPE_KENNZ, "0" );
   strcpy( Buf_herstel.HERSTELL_VERGUETET, "0" );
   strcpy( Buf_herstel.ZENTRALPPELIST, "0" );
   strcpy( Buf_herstel.EKORIGINALHS, "0" );
   strcpy( Buf_herstel.BESTELL_NUR_OZEK, "0" );
   strcpy( Buf_herstel.REZEPTPFL, "0" );
   strcpy( Buf_herstel.APOTHEKENPFL, "0" );
   strcpy( Buf_herstel.NETTOARTIKEL, "0" );
   return 0;
}

/*----------------------------------------------------------------*/
void SetPrimekeyCondition_Herstel ( )
{
   char format[30];
   sprintf( format, "HERSTELLER_NR=%c%d.ld", '%', L_HERSTELLER_NR );
   sprintf( PrimekeyCond, format, Buf_herstel.HERSTELLER_NR );
/*
   sprintf( PrimekeyCond, "HERSTELLER_NR=%ld", Buf_herstel.HERSTELLER_NR );
*/
}

/*----------------------------------------------------------------*/
long ReadRecord_Herstel( long hersteller_nr, char *cErrmld )
{
   long lStatus;
   char errstr[200];

   Buf_herstel.HERSTELLER_NR = hersteller_nr;

   SetPrimekeyCondition_Herstel ( );
   lStatus = FdReadRecord( Fd_Herstel, PrimekeyCond,
                           &Buf_herstel, errstr );

   if ( lStatus == 0 )
   {
      BufOld_herstel = Buf_herstel;  /* gelesenen Satz sichern */
      strcpy( cErrmld, "" );
   }
   else if ( lStatus == 100 )
   {
      if ( InitRecord_Herstel( ) == 0 )
      {
        BufOld_herstel = Buf_herstel;  /* initial. sichern */
      }
      else
        lStatus = -1;
   }
   else
      strcpy ( cErrmld, errstr );
   lStatus_Herstel = lStatus;
   return lStatus;
}

/*----------------------------------------------------------------*/
long StoreRecord_Zgrppflege( long datum, char* cErrmld )
{
	long lStatus;

	char PrimekeyCond_Zgrppflege[100];
	char errmld[200];

	sprintf (m_ZgrppflegeBuf.KEY_GRUPPE, "%5.5d", Buf_herstel.HERSTELLER_NR);
	m_ZgrppflegeBuf.DATUM = datum;

	sprintf( PrimekeyCond_Zgrppflege, "KEY_GRUPPE='%s' and DATUM=%ld and DEZAP_SA = '20'",
									m_ZgrppflegeBuf.KEY_GRUPPE, m_ZgrppflegeBuf.DATUM );

    lStatus = FdReadRecord( m_Fd_Zgrppflege, PrimekeyCond_Zgrppflege,
				  			  &m_ZgrppflegeBuf, errmld );

	if ( lStatus == 100 )
	{
		sprintf (m_ZgrppflegeBuf.KEY_GRUPPE, "%5.5ld", Buf_herstel.HERSTELLER_NR);
		m_ZgrppflegeBuf.DATUM		= datum;
		strcpy (m_ZgrppflegeBuf.DEZAP_SA, "20");

		
		lStatus = FdDelayInsertRecord( m_Fd_Zgrppflege, &m_ZgrppflegeBuf, 
										 PrimekeyCond_Zgrppflege, errmld );
	}

   if ( lStatus != 0 )
      strcpy( cErrmld, errmld );
   else
      strcpy( cErrmld, "" );

	return lStatus;
}

/*----------------------------------------------------------------*/
long StoreRecord_Herstel( char* cErrmld )
{
   long lStatus;
   char errmld[200];

   SetPrimekeyCondition_Herstel ( );
   if ( lStatus_Herstel == 100 )
      lStatus = FdDelayInsertRecord( Fd_Herstel, &Buf_herstel,
                                     PrimekeyCond, errmld);
   else if ( lStatus_Herstel == 0 )
      lStatus = FdDelayUpdateRecord( Fd_Herstel, &Buf_herstel,
                                     &BufOld_herstel,
                                     PrimekeyCond, errmld );
   else
   {
     lStatus = lStatus_Herstel;
     strcpy( cErrmld, "Interner Fehler" );
   }
   if ( lStatus != 0 )
      strcpy( cErrmld, errmld );
   else
      strcpy( cErrmld, "" );
   return lStatus;
}

/* ---------------------------------------------------------------------- *
 * Funktion         Zifaher lesen                                         *
 * ---------------------------------------------------------------------- */

#define S_ZIFA ZIFAHER

static char *zifa_proj = "*";

static int fd_zifa_sel = -1;
static int fd_zifa_upd = -1;

static long Zifa_Select( long ifanr, char *mode, char *errmld )
{
    long s;
    char sql[500];

    if ( *mode == '0' )       /* Neuaufnahmen */
      sprintf( sql,
               "select %s from ZIFAHER where H_IFANR=%ld and " \
               "H_IFASTATUS='0' and H_AENDERUNG='0'",
               zifa_proj,
               ifanr );
    else if ( *mode == '1' )  /* Aenderungen */
      sprintf( sql,
               "select %s from ZIFAHER where H_IFANR=%ld and " \
               "H_IFASTATUS='0' and H_AENDERUNG='1'",
               zifa_proj,
               ifanr );
    else if ( *mode == '2' )  /* Neuaufnahmen + Loeschungen */
      sprintf( sql,
               "select %s from ZIFAHER where H_IFANR=%ld and " \
               "H_IFASTATUS='0' and " \
               "(H_AENDERUNG='0' or H_SATZART='003')",
               zifa_proj,
               ifanr );



/*  printf("%s\n", sql );  */

    s = SqlOpenCsWh( &fd_zifa_sel, sql );
    if ( s != 0 )
    {
      fd_zifa_sel = -1;
      sprintf( errmld, "ZIFAHER: %s", DynErrmld() );
    }
    return s;
}

static long Zifa_Fetch( struct S_ZIFA *ifa, char *errmld )
{
    long s;
    s = SqlFetch( fd_zifa_sel, 1, ifa, NULL );
    if ( s != 0 )
      sprintf( errmld, "ZIFAHER: %s", DynErrmld() );
    return s;
}

static long Zifa_CloseCs( char *errmld )
{
    long s;
    if ( fd_zifa_sel == -1 ) return 0;
    s = SqlCloseCs( fd_zifa_sel );
    if ( s != 0 && errmld != NULL )
       sprintf( errmld, "ZIFAHER: %s", DynErrmld() );
    fd_zifa_sel = -1;
    return s;
}

static long Zifa_PrepUpdate( char *errmld )
{
    long s;
    s = SqlPrepareStmnt ( &fd_zifa_upd,
                          "update ZIFAHER set H_IFASTATUS='1' where " \
                          "H_IFANR=? and H_SATZNR=?",
                          "ZIFAHER.H_IFANR", "ZIFAHER.H_SATZNR", NULL );
    if ( s != 0 )
    {
      fd_zifa_upd = -1;
      sprintf( errmld, "ZIFAHER PrepUpdate: %s", DynErrmld() );
    }
    return s;
}

static long Zifa_ExecuteUpdate( struct S_ZIFA *ifa, char *errmld )
{
    long s;
    long ifanr;
    long satznr;
    ifanr  = ifa->H_IFANR;
    satznr = ifa->H_SATZNR;
    s = SqlExecutePrepare( fd_zifa_upd, &ifanr, &satznr, NULL );
    if ( s != 0 )
      sprintf( errmld, "ZIFAHER ExecUpdate: %s", DynErrmld() );
    return s;
}

static long Zifa_FreeUpdate( char *errmld )
{
    long s;
    if ( fd_zifa_upd == -1 )  return 0;
    s = SqlFreePrepare( fd_zifa_upd );
    if ( s != 0 && errmld != NULL )
        sprintf( errmld, "ZIFAHER FreeUpdate: %s", DynErrmld() );
    fd_zifa_upd = -1;
    return s;
}

/* -------------------------------------------------------------- *
 *        Aenderungsschleife                                      *
 * -------------------------------------------------------------- */


static long StartWork( char *errmld )
  {
    long s;
    s = SqlBeginWork( );
    if ( s != 0 )
      {
        strcpy( errmld, "IFA-Hersteller generieren: " );
        strcat( errmld, DynErrmld() );
       }
    return s;
   }

/*----------------------------------------------------------------*/
static long EndWork( long status, char *errmld )
  {
    long s;
    if ( status == 0 )
      {
        s = SqlCommitWork( );
        if ( s != 0 )
          {
            strcpy( errmld, "IFA-Hersteller generieren: " );
            strcat( errmld, DynErrmld() );
           }
        return s;
       }
     else
      {
        s = SqlRollbackWork( );
        return status;
       }
   }

/*----------------------------------------------------------------*/
static long Open_All( char *cErrmld )
{
    if ( GetBufferDesc_Herstel ( cErrmld ) != 0 ) 
		return -1;

	if ( GetBufferDesc_Zgrppflege( cErrmld ) != 0 ) 
		return -1;

	SetTagesdatum();

    return 0;
}

static void Close_All(  )
{
/* dummy !!!!!!!!!!!!!! */
}

/* -------------Blanks am Ende eines Strings eliminieren---------- */
int Trim (char *s)
{
	int i;
		
	for (i = strlen(s)-1; i >= 0; i--)
	{
		if (s[i] != ' ')
		{
			break;
		}
	}

	s[i+1] = '\0';
	
	return i;
}

/* ----- Alles Updaten -------------- */
void IfaToHersteller( struct HERSTEL *Buf, struct ZIFAHER *IfaBuf )
{
   int len;
   char * pos;
   char * pos2;
   char tmp [100];

   anz_neuaufnahmen++;

   strcpy( Buf->SORTIERNAME, IfaBuf->H_SORTIERNAME );
   
   /* IFA-Name (80 Stellen) auf herstel.name und herstel.zusatz_name aufteilen */
   strncpy( tmp, IfaBuf->H_NAME, L_ZIFAHER_H_NAME );
   Trim (tmp);
   len = strlen (tmp);

   if (len <= L_HERSTEL_NAME)
      strncpy( Buf->NAME, IfaBuf->H_NAME, L_HERSTEL_NAME );
   else
   {
      strncpy( tmp, IfaBuf->H_NAME,	L_HERSTEL_NAME );

	  /* strrchr: Suche nach dem letzten Blank */
	  pos = strrchr( tmp, ' ' );
	   
	  if (pos == NULL)
	  {
         strncpy( Buf->NAME, IfaBuf->H_NAME, L_HERSTEL_NAME );
		 pos = &IfaBuf->H_NAME[ L_HERSTEL_NAME + 1 ];
	  }   
	  else
	  {
		 strncpy( Buf->NAME, IfaBuf->H_NAME, pos - tmp );
		 pos = &IfaBuf->H_NAME[ pos - tmp + 1 ];
	  }

      Trim (pos);
      len = strlen (pos);

      if (len <= L_HERSTEL_ZUSATZ_NAME)
         strncpy( Buf->ZUSATZ_NAME, pos, L_HERSTEL_ZUSATZ_NAME );
      else
	  {
         strncpy( tmp, pos, L_HERSTEL_ZUSATZ_NAME );

	     pos2 = strrchr( tmp, ' ' );

         if (pos2 == NULL)
	        strncpy( Buf->ZUSATZ_NAME, pos, L_HERSTEL_ZUSATZ_NAME );
	     else
	        strncpy( Buf->ZUSATZ_NAME, pos, pos2 - tmp);
	  }
   }

   strcpy( Buf->LANGNAME1       , IfaBuf->H_NAME );
   strcpy( Buf->LANGNAME2       , IfaBuf->H_NAME2 );
   strcpy( Buf->LANGNAME3       , IfaBuf->H_NAME3 );
   strcpy( Buf->LANDESKUERZEL   , IfaBuf->H_LANDESKUERZEL );
   strcpy( Buf->PLZ             , IfaBuf->H_PLZ );
   strcpy( Buf->ORT             , IfaBuf->H_ORT );
   strcpy( Buf->STRASSE         , IfaBuf->H_STRASSE );
   strcpy( Buf->HAUSNR_VON      , IfaBuf->H_HAUSNR_VON );
   strcpy( Buf->HAUSNR_VON_ZUS  , IfaBuf->H_HAUSNR_VON_ZUS );
   strcpy( Buf->HAUSNR_BIS      , IfaBuf->H_HAUSNR_BIS );
   strcpy( Buf->HAUSNR_BIS_ZUS  , IfaBuf->H_HAUSNR_BIS_ZUS );
   strcpy( Buf->PLZ2            , IfaBuf->H_PLZ2 );
   strcpy( Buf->POSTFACHORT     , IfaBuf->H_POSTFACHORT );
   strcpy( Buf->POST_FACH       , IfaBuf->H_POST_FACH );
   strcpy( Buf->PLZ_GROSSKUNDE  , IfaBuf->H_PLZ_GROSSKUNDE );
   strcpy( Buf->VORWAHL         , IfaBuf->H_VORWAHL );
   strcpy( Buf->TELEFON_NR      , IfaBuf->H_TELEFON_NR );
   strcpy( Buf->VORWAHL2        , IfaBuf->H_VORWAHL2 );
   strcpy( Buf->TELEFON_NR2     , IfaBuf->H_TELEFON_NR2 );
   strcpy( Buf->VORWAHL_TELEFAX , IfaBuf->H_VORWAHL_TELEFAX );
   strcpy( Buf->FAX_NR          , IfaBuf->H_FAX_NR );
   strcpy( Buf->VORWAHL_TELEFAX2, IfaBuf->H_VORWAHL_TELEFAX2 );
   strcpy( Buf->FAX_NR2         , IfaBuf->H_FAX_NR2 );
   strcpy( Buf->EMAIL1          , IfaBuf->H_EMAIL );
   strcpy( Buf->EMAIL2          , IfaBuf->H_EMAIL2 );
   strcpy( Buf->HOMEPAGE        , IfaBuf->H_HOMEPAGE );
   strcpy( Buf->REGNR_VERPACKG  , IfaBuf->H_REGNR_VERPACKG );
}

/*----------------------------------------------------------------*/
static long Do_All( struct S_ZIFA *ifa, char *errmld )
{
    long s;
    int  ifa_loeschung;

    /* Hersteller */
    s = ReadRecord_Herstel( ifa->H_HERSTELLER_NR, errmld );
    if ( !( s == 0 || s == 100 ) ) return s;

    /* ---- IFA-Loeschung ---- */
    ifa_loeschung = strcmp( ifa->H_SATZART, "003" ) == 0;

    if ( ifa_loeschung  )
    {
      if ( s == 100 ) return 0;  /* nicht mehr neu aufnehmen */

      /* nur Loeschdatum eintragen */
      Buf_herstel.DATUM_IFALOESCH = ifa->H_STAND;
      Buf_herstel.DATUM_IFAAENDER = ifa->H_STAND;
    }
    else
    {
      IfaToHersteller( &Buf_herstel, ifa );
      Buf_herstel.DATUM_IFAAENDER = ifa->H_STAND;
      if ( s == 100 )
         strcpy( Buf_herstel.BEARBEITER, user );

    }

    s = StoreRecord_Herstel( errmld );
    if ( s != 0 ) 
		return s;

    /* Ausfuehren */
    s = FdTransactWithoutWork( errmld );

    if ( s != 0 )
    {
      return s;
    }

	// Ausgabe zgrppflege für Verteilung mittels tpulzentpfl 
	s = StoreRecord_Zgrppflege( m_tagesdatum, errmld ) ;
	if (s != 0)
	{
		return s;
	}

	  /* Ausfuehren */
    s = FdTransactWithoutWork( errmld );

    if ( s != 0 )
    {
      return s;
    }

    return 0;
}


static long Transfer_Loop( long ifanr, char *errmld )
{
    long s;
    long s1;
    long anz_ueb;
	struct S_ZIFA ifa;

    s = Zifa_Fetch( &ifa, errmld );
    if ( s == 100 )
       strcpy( errmld, "Keine IFA-Hersteller-Saetze zum Uebertragen vorhanden" );
    if ( s != 0 ) return s;

	anz_ueb = 0;
	anz_neuaufnahmen = 0;
    s1 = 0;
	while ( s == 0 && s1 == 0 )
    {
      s1 = StartWork( errmld );
	  if ( s1 == 0 )
      {
        s1 = Do_All( &ifa, errmld );
		
        if ( s1 == 0 )
		{
           s1 = Zifa_ExecuteUpdate( &ifa, errmld );  /* Ifasatz updaten */
		}
        s1 = EndWork( s1, errmld );

        if ( s1 == 0 )
        {
          anz_ueb++;
          s = Zifa_Fetch( &ifa, errmld );
		}
      }
    }

    if ( s1 != 0 )  
		return s1;

    if ( s == 100 )
    {
      sprintf( errmld,
               //"%ld IFA-Hersteller-Saetze wurden uebertragen\n",
			   // anz_ueb
			   "%ld Neuaufnahmen in die Hersteller-Tabelle eingefuegt\n",
			   anz_neuaufnahmen
                );
      return 0;
    }
    return s;
}

static long Select_Loop( long ifanr, char *mode, char *errmld )
{
    long s;
    s = Zifa_Select( ifanr, mode, errmld );
    if ( s == 0 )
    {
       s = Zifa_PrepUpdate( errmld );
       if ( s == 0 )
       {
         s = Open_All( errmld );
         if ( s == 0 )
         {
            s = Transfer_Loop( ifanr, errmld );
            Close_All();
         }
         Zifa_FreeUpdate( NULL );
       }
       Zifa_CloseCs( NULL );
    }
    return s;
}


long UpdateHerstel( char *db, long ifadatum, char *mode, char *errmld )
{
   long status;

   if ( !( strcmp( mode, "0" ) == 0 || strcmp( mode, "1" ) == 0 ||
           strcmp( mode, "2" ) == 0 ) )
   {
     strcpy( errmld, "mode = 0: Neuaufnahmen\n" \
                     "mode = 1: Aenderungen\n"  \
                     "mode = 2: Neuaufnahmen + Loeschungen" );
     return 1;
   }

   status = OpenBase( db, errmld );
   if ( status == 0 )
   {
       status = OpenPflege( user, errmld );
       if ( status == 0 )
       {
          status = Select_Loop( ifadatum, mode, errmld );
          ClosePflege( errmld );
       }
      CloseBase( );
   }

    if ( status == 100 )
       return 100;

    if ( status != 0 )
      return 1;

    // strcpy( errmld, "Einfuegen erfolgreich" );
    return 0;
}


