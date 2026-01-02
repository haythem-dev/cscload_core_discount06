/* ---------------------------------------------------------------------- *
 *                            GAL_FORM.H                                  *
 * ---------------------------------------------------------------------- */

#ifndef UTIL_FORM_INCLUDED
#define UTIL_FORM_INCLUDED

/* --------  file -------------- */
#define FILE_DELIMITER		"|"

#define MAX_BUF 2048

int  OpenUtilDatei  ( FILE **fd, const char * const datei, char *errmld );
void CloseUtilDatei ( FILE *fd );
int  GetUtilZeile   ( FILE * fd, char *zeile );

FILE	  *fd_file; /* Handle auf Util-File */

int  OpenProtDatei	( FILE **fd, const char * const datei, char *errmld );
void CloseProtDatei ( FILE *fd );
int  WriteProtZeile ( FILE *fd );
FILE	  *fd_prot; /* Handle auf protokol */

/* --------  user -------------- */
static const char* const user = "util   ";

#endif
