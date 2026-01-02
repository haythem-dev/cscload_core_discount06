/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define L_DKKET_KETFIL               2
 #define L_DKKET_KETKNR               5
 #define L_DKKET_KETNAME              50
 #define L_DKKET_KETAEDAT             7
 #define L_DKKET_KETKLIM1             9
 #define L_DKKET_KETLISTE5            1
 #define L_DKKET_KETFILL              25

EXEC SQL BEGIN DECLARE SECTION;
struct O_DKKET {
         char    KETFIL               [2];
         char    KETKNR               [5];
         char    KETNAME              [50];
         char    KETAEDAT             [7];
         char    KETKLIM1             [9];
         char    KETLISTE5            [1];
         char    KETFILL              [25];
       };
EXEC SQL END DECLARE SECTION;


