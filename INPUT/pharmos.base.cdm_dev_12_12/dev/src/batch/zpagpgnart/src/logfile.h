/* ---------------------------------------------------------------------- *
 *                          logfile.h                                     *
 * ---------------------------------------------------------------------- */

#define S_DEBUG		1
#define S_HINWEIS   0
#define S_FEHLER   -1
#define S_WARNUNG  -2

int  wrap_logging(int status, char *Anwendung, char *text);

int  write_logfile(int status, char *Anwendung, char *text);
int  write_logdatei(int status, char *Anwendung, char *text, char *datei);

void displ_logfile(int status, char *text);
