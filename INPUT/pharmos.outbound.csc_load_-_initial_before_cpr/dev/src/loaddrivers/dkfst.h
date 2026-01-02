/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define L_DKFST_FSTFIL               2
 #define L_DKFST_FSTFNR               4
 #define L_DKFST_FSTFNAME            30

EXEC SQL BEGIN DECLARE SECTION;
struct O_DKFST {
         char    FSTFIL               [2];
         char    FSTFNR               [4];
         char    FSTFNAME             [30];
       };
EXEC SQL END DECLARE SECTION;


