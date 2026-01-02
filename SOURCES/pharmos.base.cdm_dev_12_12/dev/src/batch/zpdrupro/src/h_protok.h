/* ---------------------------------------------------------------- *
 *                            h_protok.h                            *
 * ---------------------------------------------------------------- */

#include <protokol.h>

#ifndef H_PROTOK_INCLUDED
#define H_PROTOK_INCLUDED

/* --- Aenderungsart ---------------------------------------------------- */

#define AE_AEND        1
#define AE_NEU         2
#define AE_LOESCH      4
#define AE_AEND_NEU    ( AE_AEND + AE_NEU )
#define AE_AEND_LOESCH ( AE_AEND + AE_LOESCH )
#define AE_NEU_LOESCH  ( AE_NEU  + AE_LOESCH )
#define AE_ALLES       ( AE_AEND + AE_NEU + AE_LOESCH )

/* --- Protokoll -------------------------------------------------------- */

struct s_PROTOKOL
{
   long    PROTOKOL_NR         ;
   long    DATUM               ;
   long    UHRZEIT             ;
   char    ANWENDER        [L_PROTOKOL_ANWENDER + 1];
   char    AENDERUNGSART   [L_PROTOKOL_AENDERUNGSART + 1];
   char    RELATION        [L_PROTOKOL_RELATION + 1];
   char    KEY_SELECT      [L_PROTOKOL_KEY_SELECT + 1];
};

#define p_PROTOKOL   "PROTOKOL_NR," \
                     "DATUM," \
                     "UHRZEIT," \
                     "ANWENDER," \
                     "AENDERUNGSART," \
                     "RELATION," \
                     "KEY_SELECT "


#endif   /* H_PROTOK_INCLUDED */

