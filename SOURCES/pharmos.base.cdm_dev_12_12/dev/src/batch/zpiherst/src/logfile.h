/* ---------------------------------------------------------------------- *
 *                          logfile.h                                     *
 * ---------------------------------------------------------------------- */

#define S_HINWEIS   0
#define S_FEHLER   -1
#define S_WARNUNG  -2

int  write_logfile ( int status, short filial_nr, char *Anwendung, char *Str );
int  write_logdatei( int status, short filial_nr, char *Str, char *datei );

void displ_logfile ( int status, short filial_nr, char *Str );

