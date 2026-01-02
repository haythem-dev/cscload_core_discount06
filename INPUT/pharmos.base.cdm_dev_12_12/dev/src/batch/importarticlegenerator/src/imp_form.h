/* ---------------------------------------------------------------------- *
 *                            PW_FORM.H                                   *
 * ---------------------------------------------------------------------- */

#ifndef IMP_FORM_INCLUDED
#define IMP_FORM_INCLUDED

#define LENGTH_TIMESTAMP	8
#define LENGTH_ARTICLENO    7

/*for protokol*/
#define PROTNAME "/importarticlegenerator"
#define PROTEND ".log" 
#define LINES_PER_PAGE	100
#define SPACE		"   "
#define DELIM  ";"

int  OpenProtDatei	( FILE **fd, const char * const datei, const long date, const long time, char *errmld );
void CloseProtDatei ( FILE *fd );
int  WriteProtZeile ( FILE * fd, const char * const msg  );

void WriteProtHead1 ( FILE * fd );
FILE	  *fd_prot; /* Handle auf protokol */

char daydate[10];
char daytime[10];
int linecount;
int pagecount;

#endif
