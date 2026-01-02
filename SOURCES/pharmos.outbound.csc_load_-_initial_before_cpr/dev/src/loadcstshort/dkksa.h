/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_DKKSA_KSAFIL               2
 #define L_DKKSA_KSAIDF               7
 #define L_DKKSA_KSAAART              2
 #define L_DKKSA_KSASAART             3
 #define L_DKKSA_KSAZBED              4
 #define L_DKKSA_KSAVALUTA            3
 #define L_DKKSA_KSAMAWERT            5
 #define L_DKKSA_KSAMWANNE            5
 #define L_DKKSA_KSAABSCHL            6

EXEC SQL BEGIN DECLARE SECTION;
struct O_DKKSA {
		 char    KSAFIL[2];
		 char    KSAIDF[7];
		 char    KSAAART[2];
		 char    KSASAART[3];
		 char    KSAZBED[4];
		 char    KSAVALUTA[3];
		 char    KSAMAWERT[5];
		 char    KSAMWANNE[5];
		 char    KSAABSCHL[6];
       };
EXEC SQL END DECLARE SECTION;


