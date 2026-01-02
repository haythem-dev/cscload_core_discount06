/* ---------------------------------------------------------------------- *
 *                                                                        *
 *     Include-Datei    : art_prot.h                                      *
 *     letztes Update am: 04.10.2000                                      *
 *                                                                        *
 *     Autor            : Schmitt                                         *
 *                                                                        *
 * ---------------------------------------------------------------------- */

#ifndef ART_PROT_H_INCLUDED
#define ART_PROT_H_INCLUDED

#include <voodoo_table_header/zdcart.h>
#include <voodoo_table_header/zartikel.h>
#include <voodoo_table_header/zartprei.h>

/* ---------------------------------------------------------------------- */

struct  ZDCART_PROT
{
   long    DCNR;
   long    DC_ARTIKEL_NR;
   char    DC_ARTIKELTEXT	[L_ZDCART_DC_ARTIKELTEXT   + 1];
   char    DC_EINH_MENGE	[L_ZDCART_DC_EINH_MENGE  + 1];
   char    DC_EINH_EINHEIT	[L_ZDCART_DC_EINH_EINHEIT + 1];
   char    DC_DARREICHFORM  [L_ZDCART_DC_DARREICHFORM + 1];
   double  DC_GEP;
   double  DC_AEP;
   double  DC_AVP;
   char    DC_MWST_GH  [L_ZDCART_DC_MWST_GH   + 1];
   char	   DC_TAXKZ[L_ZDCART_DC_TAXKZ + 1 ];
   char    DC_CODE_LIEFERANT[L_ZDCART_DC_CODE_LIEFERANT + 1];
   char	   DC_CODE_HERSTELLER[L_ZDCART_DC_CODE_HERSTELLER + 1];
   long	   HERSTELLER_NR;
   long    DC_DATUMGUELTIGAB;
   char    NB_DC_PLAUSI [L_ZDCART_NB_DC_PLAUSI + 1];
};

#define ZDCART_PROT_PROJ \
          "DCNR,"        \
          "DC_ARTIKEL_NR,"       \
          "DC_ARTIKELTEXT,"      \
          "DC_EINH_MENGE,"    \
		  "DC_EINH_EINHEIT,"    \
          "DC_DARREICHFORM,"     \
          "DC_GEP,"     \
          "DC_AEP,"     \
          "DC_AVP,"     \
          "DC_MWST_GH,"      \
		  "DC_TAXKZ," \
		  "DC_CODE_LIEFERANT," \
		  "DC_CODE_HERSTELLER, " \
		  "HERSTELLER_NR,"	\
          "DC_DATUMGUELTIGAB,"  \
		  "NB_DC_PLAUSI "

/* ---------------------------------------------------------------------- */

struct ZARTIKEL_PROT
{
   char    ARTIKEL_NAME [L_ZARTIKEL_ARTIKEL_NAME + 1];
   char    EINHEIT      [L_ZARTIKEL_EINHEIT      + 1];
   char    DARREICHFORM [L_ZARTIKEL_DARREICHFORM + 1];

};

#define ZARTIKEL_PROT_PROJ \
          "ARTIKEL_NAME,"  \
          "EINHEIT,"       \
          "DARREICHFORM "

/* ---------------------------------------------------------------------- */

struct ZARTPREIS_PROT
{
   double  GROSSO;
   double  AEP   ;
   double  AVP   ;
};

#define ZARTPREIS_PROT_PROJ \
          "GROSSO,"         \
          "AEP,"            \
          "AVP "

/* ---- Prototype ----------------------------- */

#endif  /* ART_PROT_H_INCLUDED */

