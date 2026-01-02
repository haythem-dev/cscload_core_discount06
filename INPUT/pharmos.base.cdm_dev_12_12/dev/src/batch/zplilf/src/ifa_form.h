/* ---------------------------------------------------------------------- *
 *                            IFA_FORM.H                                  *
 * ---------------------------------------------------------------------- */

#ifndef IFA_FORM_INCLUDED
#define IFA_FORM_INCLUDED

int  OpenIfaDatei  ( int *fd, char *datei, char *errmld );
int  RewindIfaDatei( int fd, char *datei, char *errmld );
void CloseIfaDatei ( int fd );
int  GetIfaZeile   ( int fd, char *zeile );

#endif
