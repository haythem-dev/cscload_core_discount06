/* ---------------------------------------------------------------------- *
 *                         g_iherst.c                                     *
 * ---------------------------------------------------------------------- *
 * Aufgabe        : Liest die (neuer) IFA                                 *
 * ---------------------------------------------------------------------- *
 * Autor          : Schmitt                                               *
 * erstellt am    : 04.02.00                                              *
 * letztes Update :                                                       *
 * ---------------------------------------------------------------------- */

/* --------- Includes -------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include <libscsvoodoo.h>

#include <zifaher.h>
#include <herstel.h>

#include "ifa_satz.h"
#include "ifa_info.h"
#include "ifa_stat.h"


#define TEST_MODE 0
#define FILL_MODE 1

/* -------- Kennung fuer Festbetrag --------------- */

static char *SatzartPhx = "PHERSTEL";

static struct ZIFAHER zher;

static long ifadatumnr;
static long satznr;

static char wertConv [ 110 ];
static char NB_PLAUSI[ POSANZ_ZIFAHER + 1 ];

/* --- Prototype  ------------------------------------------------------- */

void CloseBase( void );
long OpenBase ( char *db, char *errmld );

long UpdateHerstel( char *db, long ifadatum, char *mode, char *errmld );

/* ---------- Test IFA auf "Keine Angabe" ---------------------------- */

#define NOVALUE_PL '9'

static void InitNoValue(  )
{
   int pos;
   for ( pos = 0; pos < POSANZ_ZIFAHER; pos++ )
      NB_PLAUSI[ pos ] = '0';
}

static void TestNoValue( char *wert, int pos )
{
   if ( *wert == '\0' )
      NB_PLAUSI[ pos ] = NOVALUE_PL;
}

static int IsNoValue( int pos )
{
   return NB_PLAUSI[ pos ] == NOVALUE_PL;
}

static int IsAnyNoValue( )
{
   int pos;
   for ( pos = 0; pos < POSANZ_ZIFAHER; pos++ )
   {
      if ( NB_PLAUSI[ pos ] == NOVALUE_PL ) return 1;
   }
   return 0;
}

/* ---------------------------------------------------------------------- *
 * Funktion         : Zifa-Satz einfuegen                                 *
 * ---------------------------------------------------------------------- */

static int fd_zifaher;

static long PrepareZifaher( char *errmld )
{
    long status;
    status = SqlPrepareInsert ( &fd_zifaher, "zifaher", "*" );
    if ( status != 0 )
    {
      strcpy( errmld, "zifaher: " );
      strcat( errmld, DynErrmld() );
      fd_zifaher = -1;
     }
    return status;
}

static long InsertZifaher( char *errmld )
{
    long status;
    status = SqlExecutePrepare( fd_zifaher, &zher, NULL );
    if ( status != 0 )
    {
      strcpy( errmld, "zifaher: " );
      strcat( errmld, DynErrmld() );
    }
    return status;
}

/* ---------------------------------------------------------------------- *
 * Funktion         : Hersteller lesen                                    *
 * ---------------------------------------------------------------------- */

static int fd_herstel;

static char* Proj_Herstel = "HERSTELLER_NR,"   \
                            "SORTIERNAME,"     \
                            "NAME,"            \
                            "LANGNAME1,"       \
                            "LANGNAME2,"       \
                            "LANGNAME3,"       \
                            "LANDESKUERZEL,"   \
                            "PLZ,"             \
                            "ORT,"             \
                            "STRASSE,"         \
                            "HAUSNR_VON,"      \
                            "HAUSNR_VON_ZUS,"  \
                            "HAUSNR_BIS,"      \
                            "HAUSNR_BIS_ZUS,"  \
                            "PLZ2,"            \
                            "POSTFACHORT,"     \
                            "POST_FACH,"       \
                            "PLZ_GROSSKUNDE,"  \
                            "VORWAHL,"         \
                            "TELEFON_NR,"      \
                            "VORWAHL2,"         \
                            "TELEFON_NR2,"      \
                            "VORWAHL_TELEFAX," \
                            "FAX_NR,"			\
							"VORWAHL_TELEFAX2," \
                            "FAX_NR2,"			\
							"EMAIL1,"			\
							"EMAIL2,"			\
							"HOMEPAGE,"			\
							"REGNR_VERPACKG ";


struct S_Herstel
{
   long    HERSTELLER_NR;
   char    SORTIERNAME        [L_HERSTEL_SORTIERNAME     + 1];
   char    NAME               [L_HERSTEL_NAME            + 1];
   char    LANGNAME1          [L_HERSTEL_LANGNAME1       + 1];
   char    LANGNAME2          [L_HERSTEL_LANGNAME2       + 1];
   char    LANGNAME3          [L_HERSTEL_LANGNAME3       + 1];
   char    LANDESKUERZEL      [L_HERSTEL_LANDESKUERZEL   + 1];
   char    PLZ                [L_HERSTEL_PLZ             + 1];
   char    ORT                [L_HERSTEL_ORT             + 1];
   char    STRASSE            [L_HERSTEL_STRASSE         + 1];
   char    HAUSNR_VON         [L_HERSTEL_HAUSNR_VON      + 1];
   char    HAUSNR_VON_ZUS     [L_HERSTEL_HAUSNR_VON_ZUS  + 1];
   char    HAUSNR_BIS         [L_HERSTEL_HAUSNR_BIS      + 1];
   char    HAUSNR_BIS_ZUS     [L_HERSTEL_HAUSNR_BIS_ZUS  + 1];
   char    PLZ2               [L_HERSTEL_PLZ2            + 1];
   char    POSTFACHORT        [L_HERSTEL_POSTFACHORT     + 1];
   char    POST_FACH          [L_HERSTEL_POST_FACH       + 1];
   char    PLZ_GROSSKUNDE     [L_HERSTEL_PLZ_GROSSKUNDE  + 1];
   char    VORWAHL            [L_HERSTEL_VORWAHL         + 1];
   char    TELEFON_NR         [L_HERSTEL_TELEFON_NR      + 1];
   char    VORWAHL2           [L_HERSTEL_VORWAHL2        + 1];
   char    TELEFON_NR2        [L_HERSTEL_TELEFON_NR2     + 1];
   char    VORWAHL_TELEFAX    [L_HERSTEL_VORWAHL_TELEFAX + 1];
   char    FAX_NR             [L_HERSTEL_FAX_NR          + 1];
   char    VORWAHL_TELEFAX2   [L_HERSTEL_VORWAHL_TELEFAX2+ 1];
   char    FAX_NR2            [L_HERSTEL_FAX_NR2         + 1];
   char    EMAIL1             [L_HERSTEL_EMAIL1          + 1];
   char    EMAIL2             [L_HERSTEL_EMAIL2          + 1];
   char    HOMEPAGE           [L_HERSTEL_HOMEPAGE        + 1];
   char    REGNR_VERPACKG     [L_HERSTEL_REGNR_VERPACKG  + 1];
};

static struct S_Herstel s_Herstel;

static long DeclareHerstel( char *errmld )
{
    char sql[500];
    long status;

    sprintf( sql,
             "select %s from HERSTEL where HERSTELLER_NR=?", Proj_Herstel );
    status = SqlDeclareCs( &fd_herstel, sql, "HERSTEL.HERSTELLER_NR", NULL );
    if ( status != 0 )
    {
      strcpy( errmld, "herstel: " );
      strcat( errmld, DynErrmld() );
      fd_herstel = -1;
     }
    return status;
}

static long ReadHerstel( long hersteller_nr, char *errmld )
{
    long status;
    status = SqlReadDeclCs( fd_herstel, &s_Herstel, NULL,
                            &hersteller_nr, NULL );
    if ( !( status == 0 || status == 100 ))
    {

      strcpy( errmld, "herstel: " );
      strcat( errmld, DynErrmld() );
    }
    return status;
}

/* ----------------- FDs ------------------------------- */

static void Init_All_FDs()
{
    fd_herstel = -1;
    fd_zifaher = -1;
}

static void Close_All_FDs()
{
    if ( fd_herstel != -1 ) SqlCloseCs     ( fd_herstel );
    if ( fd_zifaher != -1 ) SqlFreePrepare ( fd_zifaher );

    Init_All_FDs();
}

static int Open_All_FDs( char *errmld )
{
    long status;

    Init_All_FDs();

    /* Zifaher einfuegen */
    status = PrepareZifaher( errmld );
    if ( status != 0 ) return 1;

    /* Hersteller lesen */
    status =  DeclareHerstel( errmld );
    if ( status != 0 ) return 1;

    return 0;
}

/* ---------------------------------------------------------------------- *
 * Funktion         : Test, ob IFA bereits geladen                        *
 * ---------------------------------------------------------------------- */

static long test_ifanr(  long ifadatum, char *errmld )
  {
    char sql[100];
    long status;
    long nr;

    sprintf( sql, "select H_IFANR from ZIFAHER where H_IFANR=%ld",
                  ifadatum );

    status = SqlRead( sql, &nr, NULL );
    if ( status == 100 ) return 0;

    if ( status == 0 )
       strcpy( errmld, "IFA-Hersteller-Datei bereits eingelesen" );
    else
    {
       strcpy( errmld, "zifaher: " );
       strcat( errmld, DynErrmld() );
    }
    return -1;
}


/* ---------------------------------------------------------------------- *
 * Funktion         : I f a B e a r b e i t e                             *
 * ---------------------------------------------------------------------- */

/* --- neu am 19.06.99 ------ */

static void str_lcpy( char *s1, char *s2, int lng1 )
{
   int lng2;
   lng2 = strlen( s2 );
   if ( lng2 < lng1 )
   {
      while ( lng2-- > 0 ) 
	  { 
		  if (*s2 == '\'')
		  {
			  *s1++ = ' ';
			  s2++;
		  }
		  else
          	  *s1++ = *s2++; 

		  lng1--; 
	  }

      while ( lng1-- > 0 ) 
		  *s1++ = ' ';
   }
   else
   {
      while ( lng1-- > 0 ) 
	  {
		  if (*s2 == '\'')
		  {
			  *s1++ = ' ';
			  s2++;
		  }
		  else
          	  *s1++ = *s2++; 
	  }
   }

   *s1 = '\0';
}

static void ze_lcpy( char *s1, char ze, int lng )
{
    while ( lng-- > 0 ) *s1++ = ze;
    *s1 = '\0';
}

static void set_blank( char *str, int lng )
{
  int i;
  i = 0;
  while( i < lng && str[i] == '0' ) i++;
  if ( i == lng )
    memset( str, ' ', lng );
}

static void set_lead_blank( char *str, int lng )
{
  int i;
  int k;
  i = 0;
  while( i < lng && ( str[i] == '0' || str[i] == ' ' ) ) i++;
  k = 0;
  while ( i < lng )
     str[k++] = str[i++];
  while ( k < lng )
     str[k++] = ' ';
}

/* ---- 089/57095-126 ---- */

static void gen_tele( char *vorwahl, char *nummer, char *gesamt )
{
  int l_ges;
  int l_vor;
  int l_num;
  int i;
  int j;
  l_ges = strlen( gesamt );        /* 24 */
  l_vor = L_ZIFAHER_H_VORWAHL;     /* 10 */
  l_num = L_ZIFAHER_H_TELEFON_NR;  /* 15  */
  ze_lcpy( vorwahl, ' ', l_vor );
  ze_lcpy( nummer,  ' ', l_num );
  i = 0;
  
  /* Hr. Peetz am 23.05.:
  Bisher wurden Vorwahl und Nummer mit  „/“ getrennt.
	Jetzt hat man sich an eine ISO-Norm orientiert und trennt
	Vorwahl und Nummer mit einem Blank. */
  while ( i < l_ges && gesamt[i] != ' ' ) i++;
  if ( gesamt[i] == ' ' )
  {
     if ( i <= l_vor )
       memcpy( vorwahl, gesamt, i );
      j = l_ges - i - 1;
      if ( j > l_num ) j = l_num;
      memcpy( nummer, &gesamt[i+1], j );
  }
  else
  {
      i = l_num;
      if ( i > l_ges ) i = l_ges;
      if ( i > 0 )
         memcpy( nummer, gesamt, i );
  }
}

static void gen_plz( char *plz, char *wert )
{
  int lng;
  int ifa_lng;
  char ifa_plz[50];  /* gross genug */
  strcpy( ifa_plz, wert );
  ifa_lng = strlen( ifa_plz);  /* 10 */
/*  set_lead_blank( ifa_plz, ifa_lng ); */
  set_blank( ifa_plz, ifa_lng );             /* blank nur wenn alles null */
  memset( plz, ' ', L_ZIFAHER_H_PLZ );
  lng = L_ZIFAHER_H_PLZ;
  if ( lng >= ifa_lng ) lng = ifa_lng;
/*
  memcpy( &plz[L_ZIFAHER_H_PLZ - lng], ifa_plz, lng );
*/
  memcpy( plz, ifa_plz, lng );   /* von vorne !!!!!!!!!!!!!!! */
  plz[L_ZIFAHER_H_PLZ] = '\0';
}

static void gen_postfach( char *pf, char *wert )
{
  int lng;
  int ifa_lng;
  char ifa_pf[50];  /* gross genug */
  strcpy( ifa_pf, wert );
  ifa_lng = strlen( ifa_pf );  /* 10 */
  set_lead_blank( ifa_pf, ifa_lng );
  memset( pf, ' ', L_ZIFAHER_H_POST_FACH );
  lng = L_ZIFAHER_H_POST_FACH;
  if ( lng >= ifa_lng ) lng = ifa_lng;
/*
  memcpy( &pf[L_ZIFAHER_H_POST_FACH - lng], ifa_pf, lng );
*/
  memcpy( pf, ifa_pf, lng );   /* von vorne !!!!!!!!!!!!!!!!! */
  pf[L_ZIFAHER_H_POST_FACH] = '\0';
}

static void Upper (unsigned char *s)
{
	int i;
	for (i = 0; i < (int) strlen( (char *) s); i++)
	{
		/* ä/ö/ü/ß nicht möglich -> muss vorher umgewandelt werden */
		if ((s[i] >= 97 && s[i] <= 122))
		{
			s[i]-=32;
		}
	}
}

static int GetUmlaut ( int Sign, char * Conv )
{
	if ( Sign == 196 || Sign == 142 )
		strcpy ( Conv, "AE" );
	else if ( Sign == 214 || Sign == 153 )
		strcpy ( Conv, "OE" );
	else if ( Sign == 220 || Sign == 154 )
		strcpy ( Conv, "UE" );
	else if ( Sign == 228 || Sign == 132 )
		strcpy ( Conv, "ae" );
	else if ( Sign == 246 || Sign == 148 )
		strcpy ( Conv, "oe" );
	else if ( Sign == 252 || Sign == 129 )
		strcpy ( Conv, "ue" );
	else if ( Sign == 223 || Sign == 225 )
		strcpy ( Conv, "ss" );
	else if ( Sign == 39 )
	{
		strcpy ( Conv, " " );
		return 1;
	}
	else
		return 0;

	return 2;
}

static void ConvertUmlaute ( unsigned char *strOrig, char *strConv )
{
	char temp[3];
	int ret;

	int iOrig;
	int iConv = 0;
	
	for ( iOrig = 0; iOrig < (int) strlen ((char *) strOrig); iOrig++ )
	{
		memset ( temp, '\0', 3 );
		
		ret = GetUmlaut ( strOrig[iOrig], temp );

		if ( ret == 2 )
		{		
			strConv[iConv] = temp [0];
			iConv++;
			strConv[iConv] = temp [1];
		}
		else if ( ret == 1 )
		{
			strConv[iConv] = temp [0];
		}
		else
		{
			strConv[iConv] = strOrig[iOrig];
		}
		iConv++;
	}
	strConv[iConv] = '\0';
}

static char *GetWert( sSatzArt *pSart, char* feld, char *errmld )
{
   char *wert;
   strcpy ( wertConv, "" ); // Wert zurücksetzen
   wert = GetWertFromSatzArtViaFeldName( pSart, feld );
   
   if ( wert == NULL )
   {
      sprintf( errmld, "kein Wert fuer Feld %s", feld );
   }
   else
   {
	  /* für diese 3 Felder keinen Upper machen, Wunsch von Hr. Peetz */
	  if (strcmp(feld, "B00EMAIL") != 0 && 
	      strcmp(feld, "B00EMAIL2") != 0 && 
	      strcmp(feld, "B00HOMEPAG") != 0)
	  {
		  ConvertUmlaute(wert, wertConv);   
		  Upper(wertConv);
		  return wertConv;
	  }
   }

   return wert;
}

static void IfaFillFromHerstel( struct ZIFAHER *h, struct S_Herstel *her )
{

/*
   if ( IsNoValue( P_ZIFAHER_H_SATZART ) )

   if ( IsNoValue( P_ZIFAHER_H_HERSTELLER_NR ) )
*/

   if ( IsNoValue( P_ZIFAHER_H_STAND ) )
      h->H_STAND = h->H_IFANR;                  /* !!!!!!!!!!!!!! */

   if ( IsNoValue( P_ZIFAHER_H_SORTIERNAME ) )
      strcpy( h->H_SORTIERNAME, her->SORTIERNAME );

   if ( IsNoValue( P_ZIFAHER_H_NAME ) )
      strcpy( h->H_NAME, her->LANGNAME1 );

   if ( IsNoValue( P_ZIFAHER_H_NAME2 ) )
      strcpy( h->H_NAME2, her->LANGNAME2 );

   if ( IsNoValue( P_ZIFAHER_H_NAME3 ) )
      strcpy( h->H_NAME3, her->LANGNAME3 );

   if ( IsNoValue( P_ZIFAHER_H_LANDESKUERZEL ) )
      strcpy( h->H_LANDESKUERZEL, her->LANDESKUERZEL );

   if ( IsNoValue( P_ZIFAHER_H_PLZ ) )
      strcpy( h->H_PLZ, her->PLZ );

   if ( IsNoValue( P_ZIFAHER_H_ORT ) )
      strcpy( h->H_ORT, her->ORT );

   if ( IsNoValue( P_ZIFAHER_H_STRASSE ) )
      strcpy( h->H_STRASSE, her->STRASSE );

   if ( IsNoValue( P_ZIFAHER_H_HAUSNR_VON ) )
      strcpy( h->H_HAUSNR_VON, her->HAUSNR_VON );

   if ( IsNoValue( P_ZIFAHER_H_HAUSNR_VON_ZUS ) )
      strcpy( h->H_HAUSNR_VON_ZUS, her->HAUSNR_VON_ZUS );

   if ( IsNoValue( P_ZIFAHER_H_HAUSNR_BIS ) )
      strcpy( h->H_HAUSNR_BIS, her->HAUSNR_BIS );

   if ( IsNoValue( P_ZIFAHER_H_HAUSNR_BIS_ZUS ) )
      strcpy( h->H_HAUSNR_BIS_ZUS, her->HAUSNR_BIS_ZUS );

   if ( IsNoValue( P_ZIFAHER_H_PLZ2 ) )
      strcpy( h->H_PLZ2, her->PLZ2 );

   if ( IsNoValue( P_ZIFAHER_H_POSTFACHORT ) )
      strcpy( h->H_POSTFACHORT, her->POSTFACHORT );

   if ( IsNoValue( P_ZIFAHER_H_POST_FACH ) )
      strcpy( h->H_POST_FACH, her->POST_FACH );

   if ( IsNoValue( P_ZIFAHER_H_PLZ_GROSSKUNDE ) )
      strcpy( h->H_PLZ_GROSSKUNDE, her->PLZ_GROSSKUNDE );

   if ( IsNoValue( P_ZIFAHER_H_VORWAHL ) )
      strcpy( h->H_VORWAHL, her->VORWAHL );

   if ( IsNoValue( P_ZIFAHER_H_TELEFON_NR  ) )
      strcpy( h->H_TELEFON_NR, her->TELEFON_NR );

   if ( IsNoValue( P_ZIFAHER_H_VORWAHL2 ) )
      strcpy( h->H_VORWAHL2, her->VORWAHL2 );

   if ( IsNoValue( P_ZIFAHER_H_TELEFON_NR2  ) )
      strcpy( h->H_TELEFON_NR2, her->TELEFON_NR2 );

   if ( IsNoValue( P_ZIFAHER_H_VORWAHL_TELEFAX ) )
      strcpy( h->H_VORWAHL_TELEFAX, her->VORWAHL_TELEFAX );

   if ( IsNoValue( P_ZIFAHER_H_FAX_NR ) )
      strcpy( h->H_FAX_NR, her->FAX_NR );

   if ( IsNoValue( P_ZIFAHER_H_VORWAHL_TELEFAX2 ) )
      strcpy( h->H_VORWAHL_TELEFAX2, her->VORWAHL_TELEFAX2 );

   if ( IsNoValue( P_ZIFAHER_H_FAX_NR2 ) )
      strcpy( h->H_FAX_NR2, her->FAX_NR2 );

   if ( IsNoValue( P_ZIFAHER_H_EMAIL ) )
      strcpy( h->H_EMAIL, her->EMAIL1 );

   if ( IsNoValue( P_ZIFAHER_H_EMAIL2 ) )
      strcpy( h->H_EMAIL2, her->EMAIL2 );

   if ( IsNoValue( P_ZIFAHER_H_HOMEPAGE ) )
      strcpy( h->H_HOMEPAGE, her->HOMEPAGE );

   if ( IsNoValue( P_ZIFAHER_H_REGNR_VERPACKG ) )
      strcpy( h->H_REGNR_VERPACKG, her->REGNR_VERPACKG );
}

static int IfaFill( struct ZIFAHER *h, sSatzArt *pSart, char *errmld )
{
   char *wert;
 
   InitNoValue(  );

   strcpy( h->H_SATZART, "000" );

   if ( ( wert = GetWert( pSart, "B00SSATZ", errmld ) ) == NULL ) return 1;
   TestNoValue( wert, P_ZIFAHER_H_SATZART );
   if ( *wert == '2' )
      strcpy( h->H_SATZART, "003" );   /* Loeschung */

   if ( ( wert = GetWert( pSart, "B00LKZ", errmld ) ) == NULL ) return 1;
/* TestNoValue( wert, P_ZIFAHER_H_SATZART );  */
   if ( *wert == 'X' )
      strcpy( h->H_SATZART, "003" );   /* Loeschung */

   if ( ( wert = GetWert( pSart, "B00GDAT", errmld ) ) == NULL ) return 1;
   TestNoValue( wert, P_ZIFAHER_H_STAND );
   h->H_STAND = atol( wert );  /* jjjjmmtt */

   if ( ( wert = GetWert( pSart, "B00ADRNR", errmld ) ) == NULL ) return 1;
   TestNoValue( wert, P_ZIFAHER_H_HERSTELLER_NR );
   h->H_HERSTELLER_NR = atol( wert );

   if ( ( wert = GetWert( pSart, "B00SNAME", errmld ) ) == NULL ) return 1;
   TestNoValue( wert, P_ZIFAHER_H_SORTIERNAME );
   str_lcpy( h->H_SORTIERNAME, wert, L_ZIFAHER_H_SORTIERNAME );

   if ( ( wert = GetWert( pSart, "B00NAME1", errmld ) ) == NULL ) return 1;
   TestNoValue( wert, P_ZIFAHER_H_NAME );
   str_lcpy( h->H_NAME, wert, L_ZIFAHER_H_NAME );

   if ( ( wert = GetWert( pSart, "B00NAME2", errmld ) ) == NULL ) return 1;
   TestNoValue( wert, P_ZIFAHER_H_NAME2 );
   str_lcpy( h->H_NAME2, wert, L_ZIFAHER_H_NAME2 );

   if ( ( wert = GetWert( pSart, "B00NAME3", errmld ) ) == NULL ) return 1;
   TestNoValue( wert, P_ZIFAHER_H_NAME3 );
   str_lcpy( h->H_NAME3, wert, L_ZIFAHER_H_NAME3 );

   if ( ( wert = GetWert( pSart, "B00LAND", errmld ) ) == NULL ) return 1;
   TestNoValue( wert, P_ZIFAHER_H_LANDESKUERZEL );
   str_lcpy( h->H_LANDESKUERZEL , wert, L_ZIFAHER_H_LANDESKUERZEL );

   if ( ( wert = GetWert( pSart, "B00PLZZU1", errmld ) ) == NULL ) return 1;
   TestNoValue( wert, P_ZIFAHER_H_PLZ );
   gen_plz ( h->H_PLZ, wert );

   if ( ( wert = GetWert( pSart, "B00ORTZU", errmld ) ) == NULL ) return 1;
   TestNoValue( wert, P_ZIFAHER_H_ORT );
   str_lcpy( h->H_ORT, wert, L_ZIFAHER_H_ORT );

   if ( ( wert = GetWert( pSart, "B00STR", errmld ) ) == NULL ) return 1;
   TestNoValue( wert, P_ZIFAHER_H_STRASSE );
   str_lcpy( h->H_STRASSE, wert, L_ZIFAHER_H_STRASSE  );

   if ( ( wert = GetWert( pSart, "B00HNRV", errmld ) ) == NULL ) return 1;
   TestNoValue( wert, P_ZIFAHER_H_HAUSNR_VON );
   str_lcpy( h->H_HAUSNR_VON, wert, L_ZIFAHER_H_HAUSNR_VON );
   set_lead_blank( h->H_HAUSNR_VON, L_ZIFAHER_H_HAUSNR_VON );

   if ( ( wert = GetWert( pSart, "B00HNRVZ", errmld ) ) == NULL )  return 1;
   TestNoValue( wert, P_ZIFAHER_H_HAUSNR_VON_ZUS );
   str_lcpy( h->H_HAUSNR_VON_ZUS, wert, L_ZIFAHER_H_HAUSNR_VON_ZUS);
   set_lead_blank( h->H_HAUSNR_VON_ZUS, L_ZIFAHER_H_HAUSNR_VON_ZUS );

   if ( ( wert = GetWert( pSart, "B00HNRB", errmld ) ) == NULL ) return 1;
   TestNoValue( wert, P_ZIFAHER_H_HAUSNR_BIS );
   str_lcpy( h->H_HAUSNR_BIS, wert, L_ZIFAHER_H_HAUSNR_BIS );
   set_lead_blank( h->H_HAUSNR_BIS, L_ZIFAHER_H_HAUSNR_BIS );

   if ( ( wert = GetWert( pSart, "B00HNRBZ", errmld ) ) == NULL ) return 1;
   TestNoValue( wert, P_ZIFAHER_H_HAUSNR_BIS_ZUS );
   str_lcpy( h->H_HAUSNR_BIS_ZUS, wert, L_ZIFAHER_H_HAUSNR_BIS_ZUS );
   set_lead_blank( h->H_HAUSNR_BIS_ZUS, L_ZIFAHER_H_HAUSNR_BIS_ZUS );

   if ( ( wert = GetWert( pSart, "B00PLZPF1", errmld ) ) == NULL ) return 1;
   TestNoValue( wert, P_ZIFAHER_H_PLZ2 );
   gen_plz ( h->H_PLZ2, wert );

   if ( ( wert = GetWert( pSart, "B00ORTPF", errmld ) ) == NULL ) return 1;
   TestNoValue( wert, P_ZIFAHER_H_POSTFACHORT );
   str_lcpy( h->H_POSTFACHORT, wert, L_ZIFAHER_H_POSTFACHORT );

   if ( ( wert = GetWert( pSart, "B00PF1", errmld ) ) == NULL ) return 1;
   TestNoValue( wert, P_ZIFAHER_H_POST_FACH );
   gen_postfach( h->H_POST_FACH, wert );

   if ( ( wert = GetWert( pSart, "B00PLZGK1", errmld ) ) == NULL ) return 1;
   TestNoValue( wert, P_ZIFAHER_H_PLZ_GROSSKUNDE );
   gen_plz ( h->H_PLZ_GROSSKUNDE, wert );

   if ( ( wert = GetWert( pSart, "B00TEL1", errmld ) ) == NULL ) return 1;
   TestNoValue( wert, P_ZIFAHER_H_VORWAHL );
   TestNoValue( wert, P_ZIFAHER_H_TELEFON_NR );
   gen_tele( h->H_VORWAHL, h->H_TELEFON_NR, wert );

   if ( ( wert = GetWert( pSart, "B00TEL2", errmld ) ) == NULL ) return 1;
   TestNoValue( wert, P_ZIFAHER_H_VORWAHL2 );
   TestNoValue( wert, P_ZIFAHER_H_TELEFON_NR2 );
   gen_tele( h->H_VORWAHL2, h->H_TELEFON_NR2, wert );

   if ( ( wert = GetWert( pSart,  "B00FAX1", errmld ) ) == NULL ) return 1;
   TestNoValue( wert, P_ZIFAHER_H_VORWAHL_TELEFAX );
   TestNoValue( wert, P_ZIFAHER_H_FAX_NR );
   gen_tele( h->H_VORWAHL_TELEFAX, h->H_FAX_NR, wert );

   if ( ( wert = GetWert( pSart,  "B00FAX2", errmld ) ) == NULL ) return 1;
   TestNoValue( wert, P_ZIFAHER_H_VORWAHL_TELEFAX2 );
   TestNoValue( wert, P_ZIFAHER_H_FAX_NR2 );
   gen_tele( h->H_VORWAHL_TELEFAX2, h->H_FAX_NR2, wert );

   if ( ( wert = GetWert( pSart, "B00HERSTER", errmld ) ) == NULL ) return 1;
   TestNoValue( wert, P_ZIFAHER_H_HE_ERL );
   str_lcpy( h->H_HE_ERL, wert, L_ZIFAHER_H_HE_ERL );

   if ( ( wert = GetWert( pSart, "B00GHERLAU", errmld ) ) == NULL ) return 1;
   TestNoValue( wert, P_ZIFAHER_H_GH_ERL );
   str_lcpy( h->H_GH_ERL, wert, L_ZIFAHER_H_GH_ERL );

   if ( ( wert = GetWert( pSart, "B00EMAIL", errmld ) ) == NULL ) return 1;
   TestNoValue( wert, P_ZIFAHER_H_EMAIL );
   str_lcpy( h->H_EMAIL, wert, L_ZIFAHER_H_EMAIL  );

   if ( ( wert = GetWert( pSart, "B00EMAIL2", errmld ) ) == NULL ) return 1;
   TestNoValue( wert, P_ZIFAHER_H_EMAIL2 );
   str_lcpy( h->H_EMAIL2, wert, L_ZIFAHER_H_EMAIL2  );

   if ( ( wert = GetWert( pSart, "B00HOMEPAG", errmld ) ) == NULL ) return 1;
   TestNoValue( wert, P_ZIFAHER_H_HOMEPAGE );
   str_lcpy( h->H_HOMEPAGE, wert, L_ZIFAHER_H_HOMEPAGE  );

   if ( ( wert = GetWert( pSart, "B00REGNR9", errmld ) ) == NULL ) return 1;
   TestNoValue( wert, P_ZIFAHER_H_REGNR_VERPACKG );
   str_lcpy( h->H_REGNR_VERPACKG, wert, L_ZIFAHER_H_REGNR_VERPACKG  );
   
   return 0;
}


static int  FillHerstelSatz( sSatzArt *pSart, int mode, char *errmld )
{
   int  s;

   s = IfaFill( &zher, pSart, errmld );
   if ( s != 0 ) return 1;

   /* --------------------------- */

   satznr++;

   strcpy( zher.H_IFASTATUS, "0" );
   zher.H_IFANR  = ifadatumnr;
   zher.H_SATZNR = satznr;

   if ( mode == FILL_MODE )
   {
      long status;

      /* herstel lesen */
      status = ReadHerstel( zher.H_HERSTELLER_NR, errmld );
      if ( !( status == 0 || status == 100 )) return 1;

    /*  status  B00SSATZ      H_AENDERUNG   */
    /*     0    '0' '1'  '3'     '1'        */
    /*   100    '0' '1'  '3'     '0' wenn !IsNoValue */
    /*                           '2' wenn  IsNoValue */

      if ( status == 0 )
      {
         /* ok !!!!!! */
         strcpy( zher.H_AENDERUNG, "1"  );    /* Aenderung */
         IfaFillFromHerstel( &zher, &s_Herstel );
      }
      else                /* Neuanlage */
      {
        if ( IsAnyNoValue( ) )
           strcpy( zher.H_AENDERUNG, "2" );     /* Fehler bei Neuanlage */
        else
           strcpy( zher.H_AENDERUNG, "0" );     /* Neuanlage */
      }
      status = InsertZifaher( errmld );

      if ( status != 0 ) s = 1;
   }
   else
   {
#ifdef MSDOS
      printf( "%8.0ld %5.0ld %5.0ld %s\n",
              zher.H_IFANR, zher.H_SATZNR, zher.H_HERSTELLER_NR, zher.H_SORTIERNAME  );
#endif
   }

   return s;
}

static long GenHerstelNeu( char *datei, char *satzart, int mode,
                           char *idd_file, char *errmld )
{
   sSatzDesc sD;

   sD.satzart = satzart;
   sD.mode = mode;
   sD.Fill = &FillHerstelSatz;
   return GenIfaSatz( datei, &sD, idd_file, errmld );
}

static void ExtractPfad( char *str )
{
  int i;
  int found;
  found = 0;
  i = strlen( str ) - 1;

  while ( i >= 0 && !found )
  {
     found = str[i] == ':' || str[i] == '\\' || str[i] == '/';
     if ( !found ) i--;
  }
  str[i+1] = '\0';
}


static long GenAll( char *datei[], char *pfad, char *satzart, int mode,
                    char *idd_file, char *errmld  )
{
   int  i;
   long s;

   satznr = 0;   /* !!!!!! globale Variable */

   i = 0;
   s = 0;
   while ( s == 0 && datei[i] != NULL )
   {
      ExtractPfad( pfad );
      strcat( pfad, datei[i] );
      s = GenHerstelNeu( pfad, satzart, mode, idd_file, errmld );
      i++;
   }
   return s;
}

#define ANZ_DATEI 10

static long GenHerstel( char *db, char* ili_file, char *idd_file, char *satzart,
                        char *errmld )
{
   long s;
   int i;
   long datum;
   char *datei[ANZ_DATEI];

   s = IfaLieferung( ili_file, satzart, datei, ANZ_DATEI, &datum, idd_file,
                     errmld );

   ifadatumnr = datum;   /* !!!!!! globale Variable */

   if ( s == 0 )
   {
      s = GenAll( datei, ili_file, satzart, TEST_MODE, idd_file, errmld );
      if ( s == 0 )
      {
        s = 1;
        if ( OpenBase( db, errmld ) == 0 )
        {
          if ( test_ifanr( ifadatumnr, errmld ) == 0 )
          {
             if ( Open_All_FDs( errmld ) == 0 )
               s = GenAll( datei, ili_file, satzart, FILL_MODE, idd_file, errmld );
             Close_All_FDs( );
          }
          CloseBase( );
        }
      }
   }

   for ( i = 0; i < ANZ_DATEI; i++ )
     if ( datei[i] != NULL )
       free( datei[i] );

   return s;
}


#define FILE_LEN 20

long GenIfaHerNeu( char *db, char* ili_direc, char *idd_direc, char *errmld )
{
    char satzart[31];
    char meld[200];
    char *idd_file;
    char *ili_file;
    long status;

    idd_file = malloc( strlen( idd_direc ) + FILE_LEN + 1 );
    if ( idd_file == NULL )
    {
       strcpy( errmld, "malloc-Fehler GenIfaHerNeu" );
       return 1;
    }

    ili_file = malloc( strlen( ili_direc ) + FILE_LEN + 1 );
    if ( ili_file == NULL )
    {
       free( idd_file );
       strcpy( errmld, "malloc-Fehler GenIfaHerNeu" );
       return 1;
    }

    strcpy( idd_file, idd_direc );
    strcat( idd_file, "/defprod.ifa" );
    if ( IfaSatzName( idd_file, SatzartPhx, satzart, errmld ) != 0 )
    {
       free( ili_file );
       free( idd_file );
       return 1;
    }

    strcpy( idd_file, idd_direc );
    strcat( idd_file, "/definifa.idd" );
    strcpy( ili_file, ili_direc );
    strcat( ili_file, "/liefer.ili" );
    if ( GenHerstel( db, ili_file, idd_file, satzart, errmld ) != 0 )
    {
       free( ili_file );
       free( idd_file );
       return 1;
    }

    free( ili_file );
    free( idd_file );
    sprintf( errmld, "%ld IFA-Hersteller erfolgreich geladen", satznr );

    /* als bearbeitet kennzeichnen */
    if ( WriteIfaStatus( SatzartPhx, ili_direc, meld  ) != 0 )
    {
       strcat( errmld, "\nStatus 'bearbeitet' wurde nicht gesetzt" );
    }

    status = 0;
    {
       /* Neuaufnahmen in Hersteller integrieren */
       status = UpdateHerstel( db, ifadatumnr, "2", meld );
       if ( status == 0 )
	   {
		   // strcat( errmld, "\nNeuaufnahmen in die Hersteller-Tabelle eingefuegt" );
		   strcat( errmld, "\n" );
           strcat( errmld, meld );
	   }
       else
       {
          if ( status == 100 )
             status = 0;
          else
             strcat( errmld, "\nFehler bei Einfuegen der Neuaufnahmen:" );

          strcat( errmld, "\n" );
          strcat( errmld, meld );
       }
    }
    return status;
}


