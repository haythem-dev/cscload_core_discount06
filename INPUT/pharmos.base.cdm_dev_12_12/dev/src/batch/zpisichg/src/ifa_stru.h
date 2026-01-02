/* ---------------------------------------------------------------------- *
 *                         Ifa_Stru.h                                     *
 * ---------------------------------------------------------------------- */

#ifndef IFA_STRU_INCLUDED
#define IFA_STRU_INCLUDED

/*
DEFK "SATZART;FDTSBEZ;FDTTXT;FDTDATZEIT;"
DFEL "SATZART;DFELFBEZ;DFELFTXT;DFELFTYP;DFELFLANG;DFELFKAW;DFELSLS;DFELSSLF;"
DSAT "SATZART;DSATSBEZ;DSATSTXT;DSATSANZ;DSATSBEZ;DSATSBEZ;"
DEFE "SATZART;FDTSBEZ;FDTTXT;FDTDATZEIT;FDTNUM;"
*/

/* ------ Ifa-Satzart DFEL ------------- */

struct Dfel
{
   char *dfelfbez;
   char *dfelftext;
   char *dfelftyp;
   int   dfelityp;
   long  dfelflang;
   char *dfelfkaw;
   char *dfelssls;
   char *dfelsslf;
};

typedef struct Dfel   sDfel;
typedef struct Dfel*  pDfel;


/* ------ Ifa-Satzart DSAT ------------- */

struct Dsat
{
   char     *dsatsbez;
   char     *dsatstext;
   int      dsatfanz;
   char     **dsatfbez;
};

typedef struct Dsat   sDsat;
typedef struct Dsat*  pDsat;

/* ------ eigene Satzbeschreibung Satzart ------------- */

struct SatzFeld
{
   char *dsatfbez;
   int   dfelityp;
   long  dfelflang;
   char *pWert;
};

typedef struct SatzFeld sSatzFeld;


struct SatzArt
{
   char *SatzName;
   int  FeldAnzahl;
   sSatzFeld *pFeld;
};

typedef struct SatzArt sSatzArt;

/* ---------------------------------------------------- */

int  BuildSatzArt( char *satzart, sSatzArt *pSart, char *Pfad, char *errmld );
void DeleteSatzArt( sSatzArt *pSart );

int  GetFeldAnzahlFromSatzArt( sSatzArt *pSart );
void InsertWertIntoSatzArt( sSatzArt *pSart, int FbezIndex, char *wert );
void RemoveWertFromSatzArt( sSatzArt *pSart, int FbezIndex );
void RemoveAllWerteFromSatzArt( sSatzArt *pSart );
char *GetWertFromSatzArtViaIndex( sSatzArt *pSart, int FbezIndex );
char *GetWertFromSatzArtViaFeldName( sSatzArt *pSart, char *FeldName );

char *GetFbezFromSatzArtViaIndex( sSatzArt *pSart, int FbezIndex );

#endif
