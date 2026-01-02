/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define L_DKVTR_VTRFIL               2
 #define L_DKVTR_VTRNUM               3
 #define L_DKVTR_VTRNAME              30
 #define L_DKVTR_VTRSTR               30
 #define L_DKVTR_VTRORT               30
 #define L_DKVTR_VTRPLZ               5
 #define L_DKVTR_VTRKZA               1
 #define L_DKVTR_VTRPWFAK             1
 #define L_DKVTR_VTREMAIL             50
 #define L_DKVTR_VTRFILL              104

EXEC SQL BEGIN DECLARE SECTION;
struct O_DKVTR {
		 char    VTRFIL[2];
		 char    VTRNUM[3];
		 char    VTRNAME[30];
		 char    VTRSTR[30];
		 char    VTRORT[30];
		 char    VTRPLZ[5];
		 char    VTRKZA[1];
		 char    VTRPWFAK[1];
		 char    VTREMAIL[50];
		 char    VTRFILL[104];
       };
EXEC SQL END DECLARE SECTION;


