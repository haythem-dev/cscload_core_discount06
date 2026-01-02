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

#include <zifaart.h>
#include <zartikel.h>
#include <zartprei.h>

/* ---------------------------------------------------------------------- */

struct  ZIFAART_PROT
{
   long    IFANR;
   long    A00PZN;
   long    A00PZN8;
   char    A00PBEZ   [L_ZIFAART_A00PBEZ   + 1];
   char    A00PGMENG [L_ZIFAART_A00PGMENG + 1];
   char    A00PGEINH [L_ZIFAART_A00PGEINH + 1];
   char    A00DARFO  [L_ZIFAART_A00DARFO  + 1];
   long    A00ANBNR;
   char    A00ARTNR  [L_ZIFAART_A00ARTNR  + 1];
   double  A01GEPDM;
   double  A01AEPDM;
   double  A01AVPDM;
   char    A05TMAX   [L_ZIFAART_A05TMAX   + 1];
   char    A01AMPV   [L_ZIFAART_A01AMPV   + 1];
   char    A01MWST   [L_ZIFAART_A01MWST   + 1];
   char    A02NEM    [L_ZIFAART_A02NEM  + 1];
   char    A02AM     [L_ZIFAART_A02AM  + 1];
   char    A02BTM    [L_ZIFAART_A02BTM    + 1];
   char    A03VWGGH  [L_ZIFAART_A03VWGGH  + 1];
   long    A06PZNNF;
   long    A06PZNNF8;
   long    DATUMGUELTIGAB;
   char    NB_PLAUSI [L_ZIFAART_NB_PLAUSI + 1];
};

#define ZIFAART_PROT_PROJ \
          "IFANR,"        \
          "A00PZN,"       \
          "A00PZN8,"       \
          "A00PBEZ,"      \
          "A00PGMENG,"    \
		  "A00PGEINH,"    \
          "A00DARFO,"     \
          "A00ANBNR,"     \
          "A00ARTNR,"     \
          "A01GEPDM,"     \
          "A01AEPDM,"     \
          "A01AVPDM,"     \
          "A05TMAX,"      \
          "A01AMPV,"      \
          "A01MWST,"      \
          "A02NEM,"     \
          "A02AM,"     \
          "A02BTM,"       \
          "A03VWGGH,"     \
          "A06PZNNF,"     \
          "A06PZNNF8,"     \
          "DATUMGUELTIGAB,"  \
		  "NB_PLAUSI "

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

