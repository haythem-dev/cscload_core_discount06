/* ---------------------------------------------------------------------- *
 *                            DC_FORM.H                                  *
 * ---------------------------------------------------------------------- */

#ifndef LI_FORM_INCLUDED
#define LI_FORM_INCLUDED

#define NO_SIGNS 20000
#define NO_SIGNS_ELEMENT 1000
#define FILENAME "/logindex.csv"

#define FILE_DELIMITER		'¤'

#define POSANZ_UNUSED		54

#define DATPOS 0

int  OpenLiDatei  ( FILE **fd, const char * const datei, char *errmld );
void CloseLiDatei ( FILE *fd );
int  GetLiZeile   ( FILE * fd, char *zeile );
FILE	  *fd_file; /* Handle auf logindex.csv */

#endif
