/* ---------------------------------------------------------------------- *
 *                                                                        *
 *     Include-Datei    : feb_prot.h                                      *
 *     letztes Update am: 26.10.1998                                      *
 *                                                                        *
 *     Autor            : Schmitt                                         *
 *                                                                        *
 * ---------------------------------------------------------------------- */

#ifndef FEB_PROT_H_INCLUDED
#define FEB_PROT_H_INCLUDED

#include <zartikel.h>
#include <zartwg.h>

struct  FEB_PROT
{
   long    ARTIKEL_NR;
   long    ARTIKEL_CODE;
   char    ARTIKEL_NAME [L_ZARTIKEL_ARTIKEL_NAME + 1];
   char    EINHEIT      [L_ZARTIKEL_EINHEIT + 1];
   char    DARREICHFORM [L_ZARTIKEL_DARREICHFORM + 1];
   char    WIRKSTOFF_NR [L_ZARTWG_WARENGRUPPE + 1];
   double  AVP;
   double  FEST_NEU;
   double  FEST_ALT;
   int     WEGFALL;
};

/* ---- Prototype ----------------------------- */

long feb_OpenProtokol( char *datei, int mit_protokol, char *mode,
                       char *errmld );
long feb_Protokol( struct FEB_PROT *info, char *errmld );
void feb_CloseProtokol( int ok, long anz_gelesen, char *errmld );

#endif  /* FEB_PROT_H_INCLUDED */

