/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define L_DKKEG_KEGFIL               2
 #define L_DKKEG_KEGIDF               7
 #define L_DKKEG_KEGEGR               4
 #define L_DKKEG_KEGAEDAT             6
 #define L_DKKEG_KEGAKT               1
/* #define L_DKKEG_KEGOMG               1
 #define L_DKKEG_KEGFLEX              1
 #define L_DKKEG_KEGELAC              1	*/
 #define L_DKKEG_KEGFILL              80

EXEC SQL BEGIN DECLARE SECTION;
struct O_DKKEG {
		 char    KEGFIL[2];
		 char    KEGIDF[7];
		 char    KEGEGR[4];
		 char    KEGAEDAT[6];
		 char    KEGAKT[1];
		 char    KEGFILL[80];
       };
EXEC SQL END DECLARE SECTION;


