/* ---------------------------------------------------------------------- *
 *                          asciidat.h      Headerfile                    *
 * ---------------------------------------------------------------------- *
 *   Aufgabe        : Enthaelt Funktionen zum Bearbeiten von              *
 *                    ASCII-Dateien                                       *
 * ---------------------------------------------------------------------- *
 *   Autor          : Schmitt                                             *
 *   entwickelt am  : 15.12.1993                                          *
 *   letztes Update : 15.12.1993                                          *
 * ---------------------------------------------------------------------- */

/* --- Vom Benutzer zu definierende File-Funktionen -------- */

typedef int (*ASC_OPENFKT)   ( char *datei, char *mode );
typedef int (*ASC_READFKT)   ( int fd, char *puffer, int lng );
typedef int (*ASC_WRITEFKT)  ( int fd, char *puffer, int lng );
typedef int (*ASC_REWINDFKT) ( int fd );
typedef int (*ASC_CLOSEFKT)  ( int fd );

typedef struct  /* Struk mit den verschiedenen Funktions-Pointern  */
  {
    ASC_OPENFKT   open;
    ASC_READFKT   read;
    ASC_WRITEFKT  write;
    ASC_REWINDFKT rewind;
    ASC_CLOSEFKT  close;
  } ASC_FKT;


/* --- Vordefinierte File-Funktionen -------- */

extern ASC_FKT AscNormFkt;
extern ASC_FKT AscUnixFkt;
extern ASC_FKT AscUnixPipeFkt;

/* neu 25.09.95 */
extern ASC_FKT AscUnxFkt;
extern ASC_FKT AscUnxPipeFkt;

/* --- Prototyping ----------------------------------------- */

#define RDA_OK      0
#define RDA_NOFILE  1
#define RDA_ALLOC1  2
#define RDA_ALLOC2  3
#define RDA_NOPEN   4
#define RDA_EOF     5

#ifdef __STDC__
int AscOpen    ( char *datei, char *mode, int *datfd, int buflng, ASC_FKT *af);
int AscOpenRd  ( char *datei, int *datfd, int buflng, ASC_FKT *af );
int AscOpenCr  ( char *datei, int *datfd, ASC_FKT *af );
int AscClose   ( int datfd );
int AscRewind  ( int datfd );
int AscRead    ( char *zeile, int  datfd );
int AscWriteLng( char *zeile, int lng, int datfd );

char *DatGetenv( char *datei, char *name );

#else
int AscOpen    (  );
int AscOpenRd  (  );
int AscOpenCr  (  );
int AscClose   (  );
int AscRewind  (  );
int AscRead    (  );
int AscWriteLng(  );

char *DatGetenv( datei, name );

#endif

