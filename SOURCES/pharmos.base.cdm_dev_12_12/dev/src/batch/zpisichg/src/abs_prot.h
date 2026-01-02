/* ---------------------------------------------------------------------- *
 *     Include-Datei    : abs_prot.h                                      *
 * ---------------------------------------------------------------------- */

#ifndef ABS_PROT_H_INCLUDED
#define ABS_PROT_H_INCLUDED

/* ---- Prototype ----------------------------- */

long Abs_OpenProtokol( char *datei, int mit_protokol, char *errmld );
long Abs_Protokol( char *buf, char *errmld );
void Abs_CloseProtokol(  );

#endif  /* ABS_PROT_H_INCLUDED */
