
/* ---------------------------------------------------------------------- *
 *                           N _ U M L I S T . C                          *
 * ---------------------------------------------------------------------- *
 * Projekt:  Einkauf                                                      *
 * Gruppe:   Sortiments-Pflege                                            *
 * Modul:    Sortiment tauschen                                           *
 * ---------------------------------------------------------------------- *
 * Autor  :  Schmitt                                                      *
 * Anfang :  18.10.1994                                                   *
 * Update :  18.10.1994                                                   *
 * ---------------------------------------------------------------------- */

/* --- Include-Dateien einbinden ---------------------------------------- */

#include <stdio.h>                                /* C-Standard-Libraries */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <libscsvoodoo/libscsvoodoo.h>

#include <eklibs/hconfkt/hconfkt.h>

#include "n_basic.h"

#define LNG_ZAHL     5
#define L_BESLA_NR   5
#define L_ARTIKEL_NR 7
#define L_ANWENDER   8
#define LNG_AEN     11



static long Umlisten( long besla_vorh, long besla_neu,
                      int uebernehmen, int loeschen, int filueb,
                      long artikel_nr,
                      long *anz_aen, long *anz_vor, long *last_artnr,
                      char *errmld, char *db )
{
   long s;
   int  bereits_vorhanden;

   s = StartTransaction( errmld );
   if ( s != 0 ) return s;

   bereits_vorhanden = 0;

   s = Lese_Bliesort( besla_neu, artikel_nr, errmld );
   if ( s == 100 )
      s = Insert_Bliesort( besla_neu, artikel_nr, errmld );
   else if ( s == 0 )
      bereits_vorhanden = 1;

   /* wenn mit loeschen */
   if ( s == 0 && loeschen == 1 )
   {
      /* Bliesort loeschen */
      s = Lese_Bliesort( besla_vorh, artikel_nr, errmld );
      if ( s == 0 )
          s = Delete_Bliesort( besla_vorh, artikel_nr, errmld );
      else if ( s == 100 )
          s = 0;
   }

   /* wenn mit Artikel-Nr Bliefer uebernehmen */
   if ( s == 0 && uebernehmen  == 1 )
   {
      char nr_bliefer_vorh[50];
      char nr_bliefer_neu [50];
      s = Lese_Artnrbl( besla_vorh, artikel_nr, nr_bliefer_vorh, errmld );
      if ( s == 0 )
      {
         s = Lese_Artnrbl( besla_neu, artikel_nr, nr_bliefer_neu, errmld );
         if ( s == 100 )
         {
            s = Insert_Artnrbl( besla_neu, artikel_nr, nr_bliefer_vorh, errmld );
         }
         else if ( s == 0 )
         {
           /* nix machen */
           /* oder updaten ????? */
         }
      }
      else if ( s == 100 )
        s = 0;
   }


   /* wenn mit loeschen oder mit in filiale uebernehmen */
   /* Satz in Pflege einfuegen ???? */
   if ( s == 0 && ( loeschen == 1 || filueb == 1 ) )
        s = Insert_Pflege( besla_neu, artikel_nr, errmld );

#ifdef MIT_NEM
   /* wenn mit in filiale uebernehmen */
   /* NEM-Kennzeichen in Artikel ???? */
	 if ( s == 0 && filueb == 1 && (strcmp (db, "zpps1de") == 0 || strcmp (db, "ide21") == 0))
		 s = StoreRecord_Zartikel( artikel_nr, besla_neu, errmld  );
#endif

   if ( s == 0 )
      s = CommitTransaction( errmld );
   else
      CancelTransaction( );

   if ( s == 0 )
   {
     *last_artnr = artikel_nr;
/*   i++;   */
     (*anz_aen)++;
     if ( bereits_vorhanden )
        (*anz_vor)++;
   }
   return s;
}

/* ---------------------------------------------------------------------- *
 *      Einzel-Umlisten                                                   *
 * ---------------------------------------------------------------------- */

static int Do_UmlistenEinzel( char *user, long besla_vorh, long besla_neu,
                              int uebernehmen, int loeschen, int filueb,
                              int  list_anz, long art_list[],
                              long *anz_aen, long *anz_vor, long *last_artnr,
                              char *errmld, char *db )
{
    int i;
    long a_aen;
    long a_vor;
    long s;

#ifdef TEST
    printf( "user: %s\nvon : %ld\nnach: %ld\nueb : %d\nloe : %d\nfil: %d\nanz : %ld\n",
            user, besla_vorh, besla_neu,
            uebernehmen, loeschen, filueb, list_anz );
    for ( i = 0; i < list_anz; i++ )
      printf( "%ld\n", art_list[i] );
#endif

    *anz_aen = 0;
    *anz_vor = 0;
    *last_artnr = 0;

    if ( OnFirst( user, errmld )  != 0 ) return -1;
    if ( OpenForUmlisten( errmld )!= 0 ) return -1;

    a_aen = 0;
    a_vor = 0;

    i = 0;
    s = 0;

    while ( i < list_anz && s == 0 )
    {
      s = Umlisten( besla_vorh, besla_neu,
                    uebernehmen, loeschen, filueb,
                    art_list[i],
                    &a_aen, &a_vor, last_artnr, errmld, db );
      if ( s == 0 )
        i++;
    }

    *anz_aen = a_aen;
    *anz_vor = a_vor;

    if ( s == 0 ) strcpy( errmld, "" );
    if ( s == 0 && *anz_aen == 0 ) return 1;
    if ( s == 0 ) return 0;
    return -1;
}

/* ---------------------------------------------------------------------- *
 *      Gesamt-Umlisten                                                   *
 * ---------------------------------------------------------------------- */

static int fd_gesamt = -2;

static long Gesamt_Declare( char *errmld )
{
    static long s;
    static char smeld[80];
    if ( fd_gesamt == -2 )
    {
        char *sql;
        sql =  "select bliesort.artikel_nr from bliesort,zartikel " \
               "where bliesort.artikel_nr=zartikel.artikel_nr and " \
               "besla_nr=? and ekoriginalhs != '1'";

		/* ekoriginalhs 01.082003 */

        s = SqlDeclareCsWh( &fd_gesamt, sql, "bliesort.besla_nr", NULL );
        if ( s != 0 ) strcpy( smeld, DynErrmld() );
    }
    if ( s != 0 )
    {
        fd_gesamt = -1;
        strcpy( errmld, smeld );
    }
    return s;
}

static int Do_UmlistenGesamt( char *user, long besla_vorh, long besla_neu,
                              int uebernehmen, int loeschen, int filueb,
                              long *anz_aen, long *anz_vor, long *last_artnr,
                              char *errmld, char *db )
{
    long artikel_nr;
    long a_aen;
    long a_vor;
    long s;

#ifdef TEST
    printf( "user: %s\nvon : %ld\nnach: %ld\nueb : %d\nloe : %d\nfil: %d\n",
            user, besla_vorh, besla_neu,
            uebernehmen, loeschen, filueb );
#endif

    *anz_aen = 0;
    *anz_vor = 0;
    *last_artnr = 0;

    if ( OnFirst( user,  errmld ) != 0 ) return -1;
    if ( OpenForUmlisten( errmld )!= 0 ) return -1;
    if ( Gesamt_Declare( errmld ) != 0 ) return -1;

    a_aen = 0;
    a_vor = 0;

    s = SqlOpenDeclCs( fd_gesamt, &besla_vorh, NULL );
    if ( s != 0 )
    {
       strcpy( errmld, DynErrmld() );
       return -1;
    }

    while ( s == 0 )
    {
       s = SqlFetch( fd_gesamt, 1, &artikel_nr, NULL );
       if ( s == 0 )
       {
          s = Umlisten( besla_vorh, besla_neu,
                        uebernehmen, loeschen, filueb,
                        artikel_nr,
                        &a_aen, &a_vor, last_artnr, errmld, db );

       }
    }

    if ( s == 100 ) s = 0;

    *anz_aen = a_aen;
    *anz_vor = a_vor;

    if ( s == 0 ) strcpy( errmld, "" );
    if ( s == 0 && *anz_aen == 0 ) return 1;
    if ( s == 0 ) return 0;
    return -1;
}


static void Do_UmlistenFreeAll( void )
{
    OnLast( );
}


/* ---------------------------------------------------------------------- *
 *      Umwandel-Funktionen                                               *
 * ---------------------------------------------------------------------- */

static void anz_cpy ( char *str1, char *str2, int lng )
  {
    memcpy( str1, str2, lng );
    str1[lng] = '\0';
   }

static int Unload_Gesamt( char *user, long *besla_vorh, long *besla_neu,
                          int *uebernehmen, int *loeschen, int *filueb,
                          char *str, char *errmld )
{
#ifdef TEST
    printf( "%d %d\n%s\n", strlen(str), L_ANWENDER + 2*L_BESLA_NR + 3, str );
#endif

    if ( strlen( str ) != L_ANWENDER + 2*L_BESLA_NR + 3 )
    {
       strcpy( errmld, "Uebergabe-Parameter falsch" );
       return -1;
    }

    anz_cpy( user, str, L_ANWENDER );          str += L_ANWENDER;
    *besla_vorh  = s_atol ( str, L_BESLA_NR ); str += L_BESLA_NR;
    *besla_neu   = s_atol ( str, L_BESLA_NR ); str += L_BESLA_NR;
    *uebernehmen = s_atoi ( str, 1 );          str += 1;
    *loeschen    = s_atoi ( str, 1 );          str += 1;
    *filueb      = s_atoi ( str, 1 );          str += 1;
    return 0;
}

static int  Unload_Einzel( char *user, long *besla_vorh, long *besla_neu,
                           int *uebernehmen, int *loeschen, int *filueb,
                           int *list_anz, long **art_list,
                           char *str, char *errmld )
{
    int  i;
    long *list;
    int  lng;

    lng =  L_ANWENDER + 2*L_BESLA_NR + 3 + LNG_ZAHL;

#ifdef TEST
    printf( "%d %d\n%s\n", strlen(str), lng, str );
#endif

    if ( (int) strlen( str ) < lng )
    {
       strcpy( errmld, "Uebergabe-Parameter-1 falsch" );
       return -1;
    }

    anz_cpy( user, str, L_ANWENDER );          str += L_ANWENDER;
    *besla_vorh  = s_atol ( str, L_BESLA_NR ); str += L_BESLA_NR;
    *besla_neu   = s_atol ( str, L_BESLA_NR ); str += L_BESLA_NR;
    *uebernehmen = s_atoi ( str, 1 );          str += 1;
    *loeschen    = s_atoi ( str, 1 );          str += 1;
    *filueb      = s_atoi ( str, 1 );          str += 1;
    *list_anz    = s_atoi( str, LNG_ZAHL );    str += LNG_ZAHL;

    lng = (*list_anz) * L_ARTIKEL_NR;

#ifdef TEST
    printf( "%d %d\n%s\n", strlen(str), lng, str );
#endif

    if ( (int) strlen( str ) != lng )
    {
       strcpy( errmld, "Uebergabe-Parameter-2 falsch" );
       return -1;
    }

    list = ( long * ) malloc( *list_anz * sizeof( long ) );
    if ( list != NULL )
      {
        for ( i = 0; i < *list_anz; i++ )
           {
             list[i] = s_atol( str, L_ARTIKEL_NR );
             str += L_ARTIKEL_NR;
            }
       }
    *art_list = list;
    return 0;
}


/* ---------------------------------------------------------------------- *
 *      Gesamt-Umlisten                                                   *
 * ---------------------------------------------------------------------- */

int Serv_UmlistenGesamt( char *ustr, char *rstr, int *ulng, char *db )
{
    char user[L_ANWENDER + 1];
    long anz_aen;
    long anz_vor;
    long last_artnr;
    long besla_vorh;
    long besla_neu;
    int  uebernehmen;
    int  loeschen;
    int  filueb;
    char errmld[80];
    int  s;

    s = -1;
    anz_aen = 0;
    anz_vor = 0;
    last_artnr = 0;

    s = Unload_Gesamt( user, &besla_vorh, &besla_neu,
                       &uebernehmen, &loeschen, &filueb, ustr, errmld );
    if ( s == 0 )
       s = Do_UmlistenGesamt( user, besla_vorh, besla_neu,
                              uebernehmen, loeschen, filueb,
                              &anz_aen, &anz_vor, &last_artnr, errmld, db );

    strcpy    ( rstr, "" );
    s_longcatl( rstr, anz_aen, LNG_AEN, '0' );
    s_longcatl( rstr, anz_vor, LNG_AEN, '0' );
    s_longcatl( rstr, last_artnr, L_ARTIKEL_NR, '0' );
    strcat    ( rstr, errmld );

    *ulng = strlen( rstr );

    return s;
}


/* ---------------------------------------------------------------------- *
 *      Einzel-Umlisten                                                   *
 * ---------------------------------------------------------------------- */

int Serv_UmlistenEinzel( char *ustr, char *rstr, int *ulng, char *db )
{
    char user[L_ANWENDER + 1];
    long besla_neu;
    long besla_vorh;
    int  uebernehmen;
    int  loeschen;
    int  filueb;
    int  list_anz;
    long *art_list;
    long anz_aen;
    long anz_vor;
    long last_artnr;
    char errmld[80];
    int  s;

    s = -1;
    anz_aen = 0;
    anz_vor = 0;
    last_artnr = 0;

    s = Unload_Einzel( user, &besla_vorh, &besla_neu,
                       &uebernehmen, &loeschen, &filueb,
                       &list_anz, &art_list, ustr, errmld );

    if ( s == 0 )
    {
      if ( art_list != NULL )
      {
        s = Do_UmlistenEinzel( user, besla_vorh, besla_neu,
                               uebernehmen, loeschen, filueb,
                               list_anz, art_list,
                               &anz_aen, &anz_vor, &last_artnr, errmld, db );
        free( art_list );
      }
      else
      {
        s = -1;
        anz_aen = 0;
        anz_vor = 0;
        last_artnr = 0;
        strcpy( errmld, "Alloc-Fehler bei Alloc art_list" );
      }
    }

    strcpy    ( rstr, "" );
    s_longcatl( rstr, anz_aen, LNG_AEN, '0' );
    s_longcatl( rstr, anz_vor, LNG_AEN, '0' );
    s_longcatl( rstr, last_artnr, L_ARTIKEL_NR, '0' );
    strcat    ( rstr, errmld );

    *ulng = strlen( rstr );

    return s;
}

/* ---------------------------------------------------------------------- *
 *      Freigeben                                                         *
 * ---------------------------------------------------------------------- */

void Serv_UmlistenFreeAll( void )
{
    Do_UmlistenFreeAll(  );
    if ( fd_gesamt >= 0 )
    {
       SqlCloseCs( fd_gesamt );
       fd_gesamt = -2;
    }
}

