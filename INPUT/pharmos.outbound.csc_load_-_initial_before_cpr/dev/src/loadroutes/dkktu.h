/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define L_DKKTU_KTUFIL               2
 #define L_DKKTU_KTUIDF               7
 #define L_DKKTU_KTUTOUR              6
 #define L_DKKTU_KTUTFOLGE            3
 #define L_DKKTU_KTUTDAUER            3
 #define L_DKKTU_KTUVBTOUR            1
 #define L_DKKTU_KTUMO                1
 #define L_DKKTU_KTUDI                1
 #define L_DKKTU_KTUMI                1
 #define L_DKKTU_KTUDO                1
 #define L_DKKTU_KTUFR                1
 #define L_DKKTU_KTUSA                1
 #define L_DKKTU_KTUSO                1
 #define L_DKKTU_KTUKIPPZEIT          3
 #define L_DKKTU_KTUAUFZFZ1           3
 #define L_DKKTU_KTUAUFZFZ2           3
 #define L_DKKTU_KTUAUFZFZ3           3
 #define L_DKKTU_AEDAT                7
 #define L_DKKTU_GPTOUR               1
 #define L_DKKTU_KTUVFIL              2
 #define L_DKKTU_KTUNTF               1
 #define L_DKKTU_KTUBAT               1
 #define L_DKKTU_KTUVBTVSA            1
 #define L_DKKTU_KTULOE               1
 #define L_DKKTU_KTUDTOUR             4
 #define L_DKKTU_KTUAART              2
 #define L_DKKTU_NHFIL                2
 #define L_DKKTU_AEPR                 5
 #define L_DKKTU_EPK                  1
 #define L_DKKTU_KK                   1
 #define L_DKKTU_K08                  1
 #define L_DKKTU_K20                  1
 #define L_DKKTU_KARENZ		          3
 #define L_DKKTU_KTUKIPPZEIT2         4
 #define L_DKKTU_KTUTDAUER2           4
 #define L_DKKTU_KTURETTOUR           1
 #define L_DKKTU_PST                  1
 #define L_DKKTU_KTUFILL              24

EXEC SQL BEGIN DECLARE SECTION;
struct O_DKKTU {
		 char    KTUFIL[2];
		 char    KTUIDF[7];
		 char    KTUTOUR[6];
		 char    KTUTFOLGE[3];
		 char    KTUTDAUER[3];
		 char    KTUVBTOUR[1];
		 char    KTUMO[1];
		 char    KTUDI[1];
		 char    KTUMI[1];
		 char    KTUDO[1];
		 char    KTUFR[1];
		 char    KTUSA[1];
		 char    KTUSO[1];
		 char    KTUKIPPZEIT[3];
		 char    KTUAUFZFZ1[3];
		 char    KTUAUFZFZ2[3];
		 char    KTUAUFZFZ3[3];
		 char    KTUAEDAT[7];
		 char    KTUGPTOUR[1];
		 char    KTUVFIL[2];
		 char    KTUNTF[1];
		 char    KTUBAT[1];
		 char    KTUVBTVSA[1];
		 char    KTULOE[1];
		 char    KTUDTOUR[4];
		 char    KTUAART[2];
		 char    KTUNHFIL[2];
		 char    KTUAEPR[5];
		 char    KTUEPK[1];
		 char    KTUKK[1];
		 char    KTUK08[1];
		 char    KTUK20[1];
		 char    KTUKARENZ[3];
		 char    KTUKIPPZEIT2[4];
		 char    KTUTDAUER2[4];
		 char    KTURETTOUR[1];
		 char    KTUPST[1];
		 char    KTUFILL[24];
       };
EXEC SQL END DECLARE SECTION;


