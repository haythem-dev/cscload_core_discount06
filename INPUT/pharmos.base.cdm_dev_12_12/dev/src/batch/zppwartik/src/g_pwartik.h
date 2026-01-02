#ifndef G_PWARTIK_INCLUDED
#define G_PWARTIK_INCLUDED

long GenPwArtik( char *db, char *ili_direc, char *errmld );

long tages_datum;

int  Fd_ZArtikel;
int  Fd_ZArtPreis;
int  Fd_CArticleCodes;

struct RATIOPHARM  {
	   long    HERSTELLER_NR      ;
       long    DATUM		      ;
	   char    CHANGE_FLAG        [2];
       char    ARTIKEL_NR_HERST   [19]; //16
       char    ARTIKEL_LANGNAME   [41]; //51
       char    EINHEIT_2          [4];
       char    SPARTE	          [3];
       char    STATUS	          [3];
       char    ARTICLE_CODE		  [19]; //26
	   char    EINHEIT_1          [4];
	   char    KUEHL	          [3];
	   double  PREIS			  ;       
};

int Trim (char *s);

#endif
