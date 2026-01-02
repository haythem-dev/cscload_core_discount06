/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define L_DKTMD_TMDFIL               2
 #define L_DKTMD_TMDIDF               7
 #define L_DKTMD_TMDSTOP              6
 #define L_DKTMD_TMDTTOUR             4
 #define L_DKTMD_TMDNTOUR             4
 #define L_DKTMD_TMDTOUR              4
 #define L_DKTMD_TMDSCODE             3
 #define L_DKTMD_TMDPRUEFSUMME        7
 #define L_DKTMD_TMDANDAT             6
 #define L_DKTMD_TMDSENDDAT           6
 #define L_DKTMD_TMDLDAT              6
 #define L_DKTMD_TMDTTYPE             1
 #define L_DKTMD_TMDSTNAFB            1
 #define L_DKTMD_TMDFILL              43

EXEC SQL BEGIN DECLARE SECTION;
struct O_DKTMD {
         char    TMDFIL               [2];
         char    TMDIDF               [7];
         char    TMDSTOP              [6];
         char    TMDTTOUR             [4];
         char    TMDNTOUR             [4];
         char    TMDTOUR              [4];
         char    TMDSCODE             [3];
         char    TMDPRUEFSUMME        [7];
         char    TMDANDAT             [6];
         char    TMDSENDDAT           [6];
         char    TMDLDAT              [6];
         char    TMDTTYPE             [1];
         char    TMDSTNAFB            [1];
         char    TMDFILL              [43];
       };
EXEC SQL END DECLARE SECTION;


