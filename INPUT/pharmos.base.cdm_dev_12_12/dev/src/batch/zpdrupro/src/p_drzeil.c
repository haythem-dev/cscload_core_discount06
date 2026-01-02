
/* ---------------------------------------------------------------------- *
 *                            P _ D R Z E I L . C                         *
 * ---------------------------------------------------------------------- *
 * Projekt:  HajoSoft                                                     *
 * Aufgabe:  isql - Sql-Anweisungen  ( Einzel-Select )                    *
 * ---------------------------------------------------------------------- *
 * Autor  :  Schmitt                                                      *
 * Anfang :  01.12.1993                                                   *
 * Update :  02.12.1993                                                   *
 * ---------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <hconfkt.h>
#include <libscsvoodoo.h>
#include <tabsqld.h>
#include <phodate.h>
#include <phozeit.h>

#define ANZ_VORSPANN    4

#define MAX_KEYBREITE  24
#define MAX_COLBREITE  18
#define MAX_FELDBREITE 30    /* 30 */

static char rel_header[50];

static char cmpind[500];
static char vorspann[ANZ_VORSPANN + 1][MAX_KEYBREITE + 50];
static int  anz_vorspann;

static char *dat_uhr_anw = "DATUM    UHRZEIT  ANWENDER ";

/* ---------------------------------------------------------------------- */

#define MAX_LINE 60

static  int  line = 0;
static  long page = 0;

int  OpenPrintFile ( char *errmld );
void WritePrintFile( char *buf, char *abschluss );

static void WriteZeile( char *buf )
{
   WritePrintFile( buf, "\n" );
   line++;
}

static void WriteLeerZeile( )
{
   WritePrintFile( "", "\n" );
   line++;
}

static void WriteVorschub()
{
   WritePrintFile( "", "\f" );
/* line = 0; */
}

void PosNextPage()
{
   line = 0;
}


void StoreHeaderTablename( char *bezeichnung )
{
   strcpy( rel_header, bezeichnung );
}

/* ---------------------------------------------------------------------- */

static void pos_row( char *str, int pos )
{
  int lng;
  lng = strlen( str );
  if ( lng < pos )
  {
    memset( &str[lng], ' ', pos - lng );
    str[pos] = '\0';
  }
}

static void print_ueber( char *str )
{
  int i;
  char str1[50];
  char buf[100];
  long zeit;
  ConvFromPhoDate( str1, GetPhoDate(), "tt.mm.jjjj" );
  zeit = GetPhoTime( );

   sprintf( buf,
            "DATUM: %s   UHRZEIT: %.2ld:%.2ld:%.2ld   SEITE: %ld",
            str1,
            zeit/10000,
            (zeit/100)%100,
            zeit%100,
            ++page );

   strcpy ( str, "ZPDRUPRO" );
   pos_row( str, MAX_KEYBREITE + 1 );
/* strcat ( str, "HISTORIE RELATION \"" ); */
   strcat ( str, "HISTORIE " );
   strcpy ( str1, rel_header );
   for ( i = 0; i < (int) strlen(str1); i++ )
     str1[i] = (char) toupper( str1[i] );
   strcat ( str, str1  );
/* strcat ( str, "\"" ); */
   pos_row( str, MAX_KEYBREITE + 1 + MAX_COLBREITE + 1 + strlen( dat_uhr_anw ));
   strcat ( str, buf );
}

static void print_header( char *str )
{
  int pos;
  strcpy( str, "SCHLUESSELBEGRIFF" );
  pos = MAX_KEYBREITE + 1;
  pos_row( str, pos );
  strcat( str, dat_uhr_anw );
  pos = strlen( str );
  strcat( str, "FELDBEZEICHNUNG" );
  pos += MAX_COLBREITE + 1;
  pos_row( str, pos );
  strcat( str, "INHALT NEU" );
  pos += MAX_FELDBREITE + 1;
  pos_row( str, pos );
  strcat( str, "INHALT ALT" );
}

/* ---------------------------------------------------------------------- *
 *  Uhrzeit                                                               *
 * ---------------------------------------------------------------------- */

static void Uhrzeit_Aus( long zeit, char *str )
{
    s_longcatl( str, zeit/10000, 2, '0' );
    strcat( str, ":" );
    s_longcatl( str, (zeit%10000)/100, 2, '0');
    strcat( str, ":" );
    s_longcatl( str, zeit%100, 2, '0' );
}

/* ---------------------------------------------------------------------- *
 *  1 Zeile ausgeben                                                      *
 * ---------------------------------------------------------------------- */

static void out_dbl( char *zeile, double d )
  {
    int i;
    int j;
    char str[30];

    sprintf( str, "%.9f", d );

    j = 0;
    while ( str[j] && str[j] != '.' ) j++;
    if ( str[j] )
      {
        i = strlen( str ) - 1;
        while ( i >= j && str[i] == '0' ) i--;
        if ( i == j ) str[++i] = '0';
        str[++i] = '\0';
       }
    sprintf( zeile, "%s", str );
   }

static void out_dec( char *zeile, double d, int stellen, int nk )
  {
    char format[30];

    /* Format-String generieren */
    strcpy    ( format,"% " );
    s_longcat ( format, stellen );
    strcat    ( format,"." );
    s_longcat ( format, nk );
    strcat    ( format,"f" );

    sprintf( zeile, format, d );

   }

static void out_dec_left( char *zeile, double d, int stellen, int nk )
  {
    char buf[50];
    char *str;

    out_dec( buf, d, stellen, nk );
    str = buf;
    while ( *str && *str == ' ' ) str++;

    strcpy( zeile, str );

   }

void remove_blank( char *str )
{
   int lng;
   lng = strlen( str ) - 1;
   while ( str[lng] && str[lng] == ' ' ) lng--;
   lng++;
   str[lng] = '\0';
}

static int pos_cat( char *str1, char *str2, int pos2, int max_lng )
{
   int lng1;
   int lng2;
   lng2 = strlen( &str2[pos2] );
   if ( lng2 <= max_lng )
   {
     strcat( str1, &str2[pos2] );
     return -1;
   }
   lng1 = strlen( str1 );
   memcpy( &str1[lng1], &str2[pos2], max_lng );
   str1[lng1 + max_lng] = '\0';
   return pos2 + max_lng;
}


static int print_zeile( char *buf, struct sqlcol_struct *sq, char *zeile )
{
    switch ( sq->coltype )
    {
       case DT_CHAR:
       case DT_VCHAR:
       case DT_NCHAR:
       case DT_NVCHAR:
         sprintf( zeile, "%s", &buf[sq->colpos] );
         break;
       case DT_LONG:
       case DT_SERIAL:
         sprintf( zeile, "%ld",  *( long * )  &buf[sq->colpos] );
         break;
       case DT_DATE:
         Ifx_datestr( *( long * ) &buf[sq->colpos], zeile );
         break;
       case DT_SHORT:
         sprintf( zeile, "%d",   *( short * ) &buf[sq->colpos] );
         break;
       case DT_FLOAT:
         sprintf( zeile, "%f",   *( float *) &buf[sq->colpos] );
         break;
       case DT_DOUBLE:
         out_dbl( zeile, *( double *) &buf[sq->colpos] );
         break;
       case DT_DECIMAL:
       case DT_MONEY:
         out_dec_left( zeile, *( double *) &buf[sq->colpos],
                       sq->colsize, sq->colnachk );
         break;
    }
    return 1;
}

static void print_colname( char *colname, char *druckzeile )
{
   int lng;
   char str[MAX_COLBREITE + 1];
   memset( str, ' ', MAX_COLBREITE );
   lng = strlen( colname );
   if ( lng > MAX_COLBREITE )
     lng = MAX_COLBREITE;
   memcpy( str, colname, lng );
   str[MAX_COLBREITE] = '\0';
   while ( lng-- )  str[lng] = (char) toupper( str[lng] );
   strcat( druckzeile, str );
}

static void druck_colname( struct sqltab_struct *tab_desc, int i,
                           char *buf_before, char *buf_after,
                           char *druckzeile )
{
   struct sqlcol_struct *sq;
   char *colname;

   sq = tab_desc->sqc[i];
   colname =  sq->colname;
   if ( strcmp ( tab_desc->tabname, "zartwg" ) == 0 )
   {
     if ( strcmp( sq->colname, "warengruppe" ) == 0 )
     {
        char *buf;
        char art[10];
        if ( buf_before != NULL )
          buf = buf_before;
        else
          buf = buf_after;
        print_zeile( buf, tab_desc->sqc[1], art ); /* 1 = ART */
        switch ( *art )
        {
          case '1':
            colname = "IMS-Warengruppe";
            break;
          case '2':
            colname = "PHOSIX-Warengruppe";
            break;
          case '3':
            colname = "Therapie-Gruppe";
            break;
          case '4':
            colname = "Abda-Code";
            break;
          case '5':
            colname = "Saison-Warengruppe";
            break;
		  case '7':
			colname = "Artikeltext";
			break;
        }
     }
   }
   else if ( strcmp ( tab_desc->tabname, "zartsekbez" ) == 0 )
   {
     if ( strcmp( sq->colname, "artikel_name" ) == 0 )
        colname = "sekundaer-name";
     else if ( strcmp( sq->colname, "bemerkungen" ) == 0 )
        colname = "sekundaer-bemerk";
   }

   print_colname( colname, druckzeile );

}

static int VglSpez( struct sqltab_struct *tab_desc, int i )
{
   if ( strcmp ( tab_desc->tabname, "zartwg" ) == 0 )
   {
      return i == 2;           /* nur das Feld WARENGRUPPE */
   }
   else if ( strcmp ( tab_desc->tabname, "zartpreis" ) == 0 )
   {
      return i != 0;           /* nicht die ARTIKEL_NR */
   }
   else if ( strcmp ( tab_desc->tabname, "ean" ) == 0 )
   {
      return i == 1;           /* nur das Feld EAN */
   }
   else if ( strcmp ( tab_desc->tabname, "zartsekbez" ) == 0 )
   {
      return i >= 2 && i <= 4;   /* nicht Artikel_mc, Artikel_nr */
   }

   return 1;
}

static long Print_Buffer( struct sqltab_struct *tab_desc, int NoVglSpez,
                          int diffsqld,
                          char *buf_before, char *buf_after, char *cmpind,
                          char *errmld )
{
   int  i;
   int  ind_vorspann;
   int  first_pos;
   int  second_pos;
   int  pos_1;
   int  pos_2;
   char druckzeile[300];
   char zeile_1[300];
   char zeile_2[300];

   ind_vorspann =  0;

   for ( i = 0; i < tab_desc->sqld - diffsqld; i++ )
   {
      if ( ( cmpind == NULL || cmpind[i] != COL_EQ ) &&
           ( NoVglSpez || VglSpez(tab_desc, i)      )    )
      {
         if ( line == 0 )
         {
            if ( page > 0 )
               WriteVorschub();

            print_ueber( druckzeile );
            WriteZeile( druckzeile );
            WriteLeerZeile( );
            print_header( druckzeile );
            WriteZeile( druckzeile );
            WriteLeerZeile( );
            ind_vorspann = 0;
         }

         strcpy( druckzeile, vorspann[ind_vorspann] );

         if ( ind_vorspann < anz_vorspann )
            ind_vorspann++;

     /*  print_colname( tab_desc->sqc[i], druckzeile );  */
         druck_colname( tab_desc, i, buf_before, buf_after, druckzeile );
         strcat( druckzeile, " " );
         first_pos  = strlen( druckzeile );
         second_pos = first_pos + MAX_FELDBREITE + 1;

         if ( buf_before != NULL )
         {
           print_zeile( buf_before, tab_desc->sqc[i], zeile_1 );
           remove_blank( zeile_1 );
           pos_1 = 0;
         }
         else
         {
           *zeile_1 = '\0';
           pos_1 = -1;
         }
         if ( buf_after  != NULL )
         {
           print_zeile( buf_after , tab_desc->sqc[i], zeile_2 );
           remove_blank( zeile_2 );
           pos_2 = 0;
         }
         else
         {
           *zeile_2 = '\0';
           pos_2 = -1;
         }

         while ( pos_1 != -1 || pos_2 != -1 )
         {
            /* zuerst der neue Inhalt */
            if ( pos_2 != -1 )
            {
               pos_row( druckzeile, first_pos );
               pos_2 = pos_cat( druckzeile, zeile_2, pos_2, MAX_FELDBREITE );
            }

            /* dann der alte Inhalt */
            if ( pos_1 != -1 )
            {
               pos_row( druckzeile, second_pos );
               pos_1 = pos_cat( druckzeile, zeile_1, pos_1, MAX_FELDBREITE );
            }

            WriteZeile( druckzeile );
            *druckzeile = '\0';

            if ( line >= MAX_LINE )
              line = 0;
            else
            {
              if ( pos_1 != -1 || pos_2 != -1 )
                if ( ind_vorspann < anz_vorspann )
                   strcpy( druckzeile, vorspann[ind_vorspann++] );
            }
         }
      }
   }

   if ( ind_vorspann > 0 )   /* wenn schon was gedruckt */
   {
      while ( ind_vorspann < anz_vorspann )
      {
        WriteZeile( vorspann[ind_vorspann++] );
      }
   }

   return 0;
}

/* ---------------------------------------------------------------------- *
 *  SEL-Menue                                                             *
 * ---------------------------------------------------------------------- */

static long Ausgabe( int aen_modus,
                     struct sqltab_struct *tab_desc, int NoVglSpez,
                     int diffsqld,
                     char *buf_before, char *buf_after, char *errmld )
{
   long s;

   if ( aen_modus == 1 ) /* Update nur Differenzen */
   {
     SqlCmpTabBuf( cmpind, NULL, buf_before, buf_after, tab_desc );
     s = Print_Buffer ( tab_desc, NoVglSpez, diffsqld,
                        buf_before, buf_after, cmpind, errmld );
   }
   else
   {
     s = Print_Buffer ( tab_desc, NoVglSpez, diffsqld,
                        buf_before, buf_after, NULL, errmld );
   }

   return s;
}

/* ---------------------------------------------------------------------- *
 *  SEL-Statements                                                        *
 * ---------------------------------------------------------------------- */

static char *skip_and( char *str )
{
  int i;
  char and_str[6];
  while ( *str && *str == ' ' ) str++;
  str--;
  memcpy( and_str, str, 5 );
  for ( i = 0; i < 5; i++ )
    and_str[i] = (char) toupper( and_str[i] );
  if ( memcmp( and_str, " AND ", 5 ) == 0 )
  {
     *str = '\0';
     str += 5;
  }
  else
     str++;
  while ( *str && *str == ' ' ) str++;
  return str;
}

static char *next_key( char *str )
{
   while ( *str && *str != '=' ) str++;
   if ( *str  )
   {
     str++;
     while ( *str && *str == ' ' ) str++;
     if ( *str == '\'' )
     {
       str++;
       while ( *str && *str != '\'' ) str++;
       if ( *str ) str++;
     }
     else if ( *str )
     {
       while ( *str && *str != ' ' ) str++;
     }
     if ( *str )
        str = skip_and( str );
   }
   return str;
}


static void handle_char_key( char *str )
{
   char *str1;
   char *str2;
   while ( *str && *str != '=' ) str++;
   if ( *str == '\0' ) return;
   str++;
   while ( *str && *str == ' ' ) str++;
   if ( *str == '\0' || *str != '\'' ) return;
   str++;
   str1 = str;
   while ( *str && *str != '\'' ) str++;
   if ( *str == '\0' ) return;
   str2 = str - 1;
   /* letzte blanks im String entfernen */
   while( str2 >= str1 && *str2 == ' ' ) str2--;
   str2++;
   *str2 = '\'';
   str2++;
   *str2 = '\0';
}

static int get_keysel( char *str, char *key[], int maxlng, int maxanz )
{
   int i;
   i = strlen( str ) - 1;
   while ( i >= 0 && str[i] == ' ' ) i--;
   str[++i] = '\0';
   while ( *str && *str == ' ' ) str++;
   key[0] = str;
   handle_char_key( key[0] );
   if ( (int) strlen(str)<= maxlng )
     return 1;

   i = 1;
   do
   {
      key[i] = next_key( key[i - 1] );
      if ( key[i][0] != '\0' )
      {
         handle_char_key( key[i] );
         i++;
      }
	  else
	  {
		  break;
	  }
   }  while ( i < maxanz && key[i-1][0] != '\0' );
   return i;
}

static int copy_vorspann( int ind, char *key_str, int maxlng, int maxanz )
{
   int lng;
   lng = strlen( key_str );

   /* wegen leerem Vorspann bei ean, zartwg wenn ueber zartikel */
   if ( lng == 0 )
   {
      strcpy( vorspann[ind++], key_str );
      return ind;
   }

   while ( lng > maxlng && ind < maxanz )
   {
      memcpy( vorspann[ind], key_str, maxlng );
      vorspann[ind][maxlng] = '\0';
      ind++;
      lng -= maxlng;
      key_str += maxlng;
   }
   if ( lng > 0 && ind < maxanz )
   {
      strcpy( vorspann[ind++], key_str );
   }
   return ind;
}

long Zeige_Info( char *tabelle, char *art, int aen_modus, int NoVglSpez,
                 int diffsqld,
                 long datum, long uhrzeit, char *key_select, char *user,
                 void *tab_desc, char *buf_before, char *buf_after,
                 char *errmld )
{
   int  anz;
   int  ind;
   int  pos;
   int  i;
   long s;
   char *key_str[ANZ_VORSPANN];

   anz = get_keysel( key_select, key_str, MAX_KEYBREITE, ANZ_VORSPANN );

   ind = 0;
   i   = 0;
   while ( ind < ANZ_VORSPANN && i < anz )
     ind = copy_vorspann( ind, key_str[i++], MAX_KEYBREITE, ANZ_VORSPANN );
   anz_vorspann = ind;

/*
   printf( "anz=%d anz_vorspann=%d\n", anz, anz_vorspann );
   for ( anz = 0; anz < anz_vorspann; anz++ )
     printf( "%s\n", key_str[anz] );
*/

/* strcpy( vorspann[0], key_str[0] );*/
   pos = MAX_KEYBREITE + 1;
   pos_row( vorspann[0], pos );
   pos = strlen( vorspann[0] );
   ConvFromPhoDate( &vorspann[0][pos], datum, "tt.mm.jj" );
   strcat( vorspann[0], " " );
   Uhrzeit_Aus( uhrzeit, vorspann[0] );
   strcat( vorspann[0], " " );
   strcat( vorspann[0], user );
   strcat( vorspann[0], " " );

   anz = 1;
   while ( anz < anz_vorspann )
   {
/*   strcpy ( vorspann[anz], key_str[anz] );  */
     pos_row( vorspann[anz], MAX_KEYBREITE + 1 + strlen( dat_uhr_anw ) );
     anz++;
   }
   /* leerer Vorspann */
   strcpy ( vorspann[anz], " " );
   pos_row( vorspann[anz], MAX_KEYBREITE + 1 + strlen( dat_uhr_anw ) );

   s = OpenPrintFile( errmld );

   if ( s == 0 )
      s = Ausgabe( aen_modus, tab_desc, NoVglSpez, diffsqld,
                   buf_before, buf_after, errmld );

   return s;
}
