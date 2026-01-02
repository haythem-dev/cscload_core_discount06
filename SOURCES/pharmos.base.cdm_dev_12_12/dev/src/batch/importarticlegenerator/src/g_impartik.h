#ifndef G_IMPARTIK_INCLUDED
#define G_IMPARTIK_INCLUDED

long GenImport( char *dbimp, char *dbexp, char *countryimp, char *countryexp, char *datefrom, char *errmld );

static int  Fd_ZArtikel;
static int  Fd_ZArtPreis;
static int  Fd_CArticleCodes;
static int  Fd_Herstel;
static int  Fd_Cimexmanufacturermapping;
static int  Fd_Cimportarticleparam;
static int  Fd_Herlief;
static int	 Fd_Ean;
static int	 Fd_ZArtAustria;
static int	 Fd_ZArtWg;
static int	 Fd_Bliesort;

int Trim (char *s);

#endif
