/* ---------------------------------------------------------------------- *
 *                            PW_FORM.H                                   *
 * ---------------------------------------------------------------------- */

#ifndef PW_FORM_INCLUDED
#define PW_FORM_INCLUDED

#define NO_SIGNS 170 /* maximum length of  one row in datafile */


#define LENGTH_TIMESTAMP	8
#define LENGTH_ARTICLENO    7

/*for protokol*/
#define PROTNAME "/p"
#define PROTEND ".pwa" 
#define LINES_PER_PAGE	60
#define SPACE		"   "
#define DELIM  ";"

int  OpenPwDatei  ( FILE **fd, const char * const datei, char *errmld );
void ClosePwDatei ( FILE *fd );
int  GetPwZeile   ( FILE * fd, char *zeile );
FILE	  *fd_file; /* Handle auf Datenfile */

int  OpenProtDatei	( FILE **fd, const char * const datei, const long date, const long time, char *errmld );
void CloseProtDatei ( FILE *fd );
int  WriteProtZeile ( FILE * fd );

void WriteProtHead1 ( FILE * fd );
FILE	  *fd_prot; /* Handle auf protokol */

char daydate[10];
char daytime[10];
int linecount;
int pagecount;

/* Feldlängen in Ratiopharm Masterout */
#define L_INTRO			5
#define L_MANUFACTURER	5
#define L_CDATE			8
#define L_CFONC			1
#define L_MATNR			18
#define L_MATTEXT		40
#define L_MATART		4
#define L_EINHEIT_BASIS	3
#define L_SPARTE		2
#define L_STATUS		2
#define L_NORMBEZ		18
#define L_EINHEIT_VERKAUF 3
#define L_LADEGRP		4
#define L_TEMP			2
#define L_BEHAELTER		2
#define L_RAUM			2
#define L_PREIS			15

/* Feldpositionen in Ratiopharm Masterout */
#define P_INTRO			0
#define P_MANUFACTURER	P_INTRO			+ L_INTRO				+ 1
#define P_CDATE			P_MANUFACTURER	+ L_MANUFACTURER		+ 1
#define P_CFONC			P_CDATE			+ L_CDATE				+ 1
#define P_MATNR			P_CFONC			+ L_CFONC				+ 1
#define P_MATTEXT		P_MATNR			+ L_MATNR				+ 1
#define P_MATART		P_MATTEXT		+ L_MATTEXT				+ 1
#define P_EINHEIT_BASIS	P_MATART		+ L_MATART				+ 1
#define P_SPARTE		P_EINHEIT_BASIS	+ L_EINHEIT_BASIS		+ 1
#define P_STATUS		P_SPARTE		+ L_SPARTE				+ 1
#define P_NORMBEZ		P_STATUS		+ L_STATUS				+ 1
#define P_EINHEIT_VERKAUF P_NORMBEZ		+ L_NORMBEZ				+ 1
#define P_LADEGRP		P_EINHEIT_VERKAUF + L_EINHEIT_VERKAUF	+ 1
#define P_TEMP			P_LADEGRP		+ L_LADEGRP				+ 1
#define P_BEHAELTER		P_TEMP			+ L_TEMP				+ 1
#define P_RAUM			P_BEHAELTER		+ L_BEHAELTER			+ 1
#define P_PREIS			P_RAUM			+ L_RAUM				+ 1

#endif
