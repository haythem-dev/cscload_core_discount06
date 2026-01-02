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

#include <voodoo_table_header/cliart.h>
#include <voodoo_table_header/zartikel.h>
#include <voodoo_table_header/zartprei.h>

/* ---------------------------------------------------------------------- */

struct  CLIART_PROT
{
   long    LINR;
   long    PHAR;
   char    DSCRD	[L_CLIART_DSCRD   + 1];
   double  QTY;
   char    QTYUD	[L_CLIART_QTYUD + 1];
   short   NOPCS;
   char    PCKTYPD  [L_CLIART_PCKTYPD + 1];
   double  PRICE_PEXF;
   double  PRICE_PPUB;
   long    COMPNO;
   long	   HERSTELLER_NR;
   long    VDAT;
   char    NB_LI_PLAUSI [L_CLIART_NB_LI_PLAUSI + 1];
};

#define CLIART_PROT_PROJ \
          "LINR,"        \
          "PHAR,"       \
          "DSCRD,"      \
          "QTY,"    \
		  "QTYUD,"    \
		  "NOPCS,"    \
          "PCKTYPD,"     \
          "PRICE_PEXF,"     \
          "PRICE_PPUB,"     \
          "COMPNO,"     \
          "HERSTELLER_NR,"	\
          "VDAT,"  \
		  "NB_LI_PLAUSI "

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
   double  AVP   ;
};

#define ZARTPREIS_PROT_PROJ \
          "GROSSO,"         \
          "AVP "

/* ---- Prototype ----------------------------- */

#endif  /* ART_PROT_H_INCLUDED */

