
/* ---------------------------------------------------------------------- *
 *                          p_prinfo.c                                    *
 * ---------------------------------------------------------------------- *
 * Projekt:  SQL-Server                                                   *
 * Gruppe:                                                                *
 * Modul:    Pflege-Daemon                                                *
 * ---------------------------------------------------------------------- *
 * Autor  :  Schmitt                                                      *
 * Anfang :  04.08.1993                                                   *
 * Update :  06.11.1995                                                   *
 * ---------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <hconfkt.h>
#include <libscsvoodoo.h>
#include <tabsqld.h>
#include <wpp_prot.h>
#include <phodate.h>
#include <protokol.h>
#include <protinfo.h>

/* --------- Satz im Load-Format --------------------------------- */

static char before_delim;
static char after_delim;

static char before_info[2000];
static char after_info[2000];

static char before_buf[3000];
static char after_buf[3000];

#define ANZ_TABS 20

static struct sqltab_struct *tabs[ANZ_TABS];

static int anz_tabs = 0;

static int t_nr;

/* --------- FD Protinfo ----------------------------------------- */

static int fd_protinfo = -1;

/* -------------------------------------------------------------- *
 *       PROTINFO lesen                                           *
 * -------------------------------------------------------------- */

static long DeclCsWh_Protinfo( char *errmld )
  {
    long s;
    char *sql;

    if ( fd_protinfo != -1 ) return 0;

    sql = "select protokol_nr,image,teil,info from protinfo " \
          "where protokol_nr=? and image=? " \
          "order by protokol_nr,image,teil";
    s = SqlDeclareCsWh ( &fd_protinfo, sql, "protinfo.protokol_nr",
                                            "protinfo.image",
                                            NULL );
    if ( s  != 0 )
      {
        fd_protinfo = -1;
        strcpy( errmld, DynErrmld() );
       }
    return s;
   }

long CloseCs_Protinfo( char *errmld )
  {
    long s;
    if ( fd_protinfo == -1 ) return 0;
    s = SqlCloseCs( fd_protinfo );
    if ( s != 0 && errmld != NULL )
      {
       strcpy( errmld, "CloseCs_Protinfo : " );
       strcat( errmld, DynErrmld() );
      }
    fd_protinfo = -1;
    return s;
   }

static long Lese_Protinfo( long u_protokol_nr, char *u_image, char *info,
                           char *delim, char *errmld )
  {
    long s;
    int  lng;
    long protokol_nr;
    char image[2]   ;
    char teil[2]    ;

    s = DeclCsWh_Protinfo( errmld );
    if ( s != 0 ) return s;

    lng = 0;
    s = SqlReadDeclCs ( fd_protinfo,
                        &protokol_nr, image, teil, info, NULL,
                        &u_protokol_nr, u_image, NULL );

    if ( s == 100 )
      {
/*
        printf("\nPROTINFO: Kein Satz vorhanden\n") ;
        return 0;
*/
        strcpy( errmld, "Kein PROTINFO-Satz vorhanden: " ) ;
        strcat( errmld, DynErrmld() ) ;
        return s;
       }

    if ( s != 0 )
      {
        strcpy( errmld, "Lese_Protinfo: " ) ;
        strcat( errmld, DynErrmld() ) ;
        return s;
       }

    while ( s == 0 )
      {
        lng += L_PROTINFO_INFO;
        s = SqlFetch ( fd_protinfo, 1,
                       &protokol_nr, image, teil, &info[lng], NULL );
      }

    if ( s != 100 )
      {
        strcpy( errmld, "Lese_Protinfo: " ) ;
        strcat( errmld, DynErrmld() ) ;
        return s;
       }

    lng--;
    while ( info[lng] == ' ' ) lng--;
    *delim = info[lng++];
    info[lng] = '\0';
/*
    printf( "%s\n", info );
*/
    return 0;
   }

/* -------------------------------------------------------------- *
 *       Tabellenbeschreibung                                     *
 * -------------------------------------------------------------- */

static long Install_Tabs( char *tabelle, int *tab_nr, char *errmld )
  {
    long s;
    struct sqltab_struct *tab_desc;
    int i;
    i = 0;
/*
    while ( i < anz_tabs &&  strcmp( tabs[i]->tabname, tabelle ) != 0 ) i++;
*/
    while ( i < anz_tabs &&  strcmp( SqlTabName(tabs[i]), tabelle ) != 0 ) i++;
    *tab_nr = i;

    if ( i < anz_tabs ) return 0;

    /* Ueberlauf -> letzte Tabelle streichen */
    if ( i == ANZ_TABS )
      {
         i--;
         anz_tabs--;
         SqlFreeTabDesc ( tabs[i] );
         *tab_nr = i;
        }


    s = SqlGetTabDesc( tabelle, ( void ** ) &tab_desc, DESC_COLNAMES, errmld );
    if ( s == 0 )
      {
        tabs[i] = tab_desc;
        anz_tabs++;
       }
    return s;
   }


void Free_Tabs( void )
  {
    int i;
    for ( i = 0; i < anz_tabs; i++ )
      SqlFreeTabDesc ( tabs[i] );
   }


static long KonvSatz ( char *relation, char *info, char delim, char *tab_buf,
                       int *diffsqld, char *errmld )
  {
    long s;
    int  i;
    int  tab_nr;
    char tabelle[ L_PROTOKOL_RELATION + 1 ];

    while ( *relation && *relation == ' ' ) relation++;
    i = 0;
    while ( *relation && *relation != ' ' ) tabelle[i++] = *relation++;
    tabelle[i] = '\0';

    s = Install_Tabs( tabelle, &tab_nr, errmld );
    if ( s != 0 ) return s;

    *diffsqld = SqlLoadTabBuf( info, delim, tab_buf, tabs[tab_nr], errmld );
    t_nr = tab_nr;   /* !!!!!!!! */
    return 0;
   }

long Lese_Info( char *tabelle, long protokol_nr, char *aen_art,
                int *diffsqld, char *errmld )
{
    long s;
    char image[2];
    image[1] = '\0';
    switch ( *aen_art )
    {
       case P_INSERT:
         image[0] = AFTER_IMAGE;
         s = Lese_Protinfo( protokol_nr, image, after_info,
                            &after_delim, errmld );
         if ( s == 0 )
           s = KonvSatz( tabelle, after_info, after_delim, after_buf,
                         diffsqld, errmld );
/*
         if ( s == 0 )
            printf( "%s\n", after_info );
*/
         break;
       case P_UPDATE:
         image[0] = BEFORE_IMAGE;
         s = Lese_Protinfo( protokol_nr, image, before_info,
                            &before_delim, errmld );
         if ( s == 0 )
         {
             int diffsqld1;
             s = KonvSatz( tabelle, before_info, before_delim, before_buf,
                           &diffsqld1, errmld );
             if ( s == 0 )
             {
                image[0] = AFTER_IMAGE;
                s = Lese_Protinfo( protokol_nr, image, after_info,
                                   &after_delim, errmld );
                if ( s == 0 )
                {
                  s = KonvSatz( tabelle, after_info, after_delim, after_buf,
                                diffsqld, errmld );
                  if ( *diffsqld != diffsqld1 )
                  {
                     s = -1;
                     strcpy( errmld, "SqlLoadBuf: Konsistenz-Error" );
                  }
                }
             }
         }
         break;
       case P_DELETE:
         image[0] = BEFORE_IMAGE;
         s = Lese_Protinfo( protokol_nr, image, before_info,
                            &before_delim, errmld );
         if ( s == 0 )
           s = KonvSatz( tabelle, before_info, before_delim, before_buf,
                         diffsqld, errmld );
         break;
    }
    return s;
}


long Zeige_Info( char *tabelle, char *art, int aen_modus, int NoVglSpez,
                 int diffsqld,
                 long datum, long uhrzeit, char *key_select, char *user,
                 void *tab_desc, char *buf_before, char *buf_after,
                 char *errmld );

long Show_Info( char *tabelle, char *aen_art, int NoVglSpez, int diffsqld,
                long datum, long uhrzeit,
                char *key_select, char *user, char *errmld )
  {
    char *buf_before;
    char *buf_after;
    char *art;
    int  aen_modus;
    switch ( *aen_art )
     {
       case P_INSERT:
         aen_modus = 0;
         art = "Neuaufnahme";
         buf_before = NULL;
         buf_after  = after_buf;
         break;
       case P_UPDATE:
         aen_modus = 1;
         art = "Žnderung";
         buf_before = before_buf;
         buf_after  = after_buf;
         break;
       case P_DELETE:
         aen_modus = 3;
         art = "L”schung";
         buf_before = before_buf;
         buf_after  = NULL;
         break;
      }
    return Zeige_Info( tabelle, art, aen_modus, NoVglSpez, diffsqld,
                       datum, uhrzeit, key_select, user,
                       tabs[t_nr], buf_before, buf_after, errmld );
   }




long Show_Info_Preis( char *tabelle, char *aen_art, int diffsqld,
                      long datum, long uhrzeit,
                      char *key_select, char *user, char *errmld,
                      void *preis_buf )
  {
    char *buf_before;
    char *buf_after;
    char *art;
    int  aen_modus;
    if ( *aen_art == P_INSERT )
    {
       if ( preis_buf == NULL )
       {
         aen_modus = 0;
         art = "Neuaufnahme";
       }
       else
       {
          aen_modus = 1;
          art = "Aenderung";
       }
       buf_before = preis_buf;
       buf_after  = after_buf;
       return Zeige_Info( tabelle, art, aen_modus, 1, diffsqld,
                          datum, uhrzeit, key_select, user,
                          tabs[t_nr], buf_before, buf_after, errmld );
    }
    else
       return Show_Info( tabelle, aen_art, 0, diffsqld,
                         datum, uhrzeit, key_select,
                         user, errmld );
}
