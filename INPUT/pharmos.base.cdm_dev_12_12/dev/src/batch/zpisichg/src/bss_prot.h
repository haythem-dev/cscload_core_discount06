/* ---------------------------------------------------------------------- *
 *     Include-Datei    : bss_prot.h                                      *
 * ---------------------------------------------------------------------- */

#ifndef BSS_PROT_H_INCLUDED
#define BSS_PROT_H_INCLUDED

#include <zartikel.h>

/* ---- Prototype ----------------------------- */

long bss_OpenProtokol( char *datei, int mit_protokol, char *errmld );
long bss_Protokol( struct ZARTIKEL *art, char *bssig_old, char *errmld );
void bss_CloseProtokol(  );

#endif  /* BSS_PROT_H_INCLUDED */

