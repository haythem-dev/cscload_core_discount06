#ifndef __PP_PUSUPPLIER_H_
#define __PP_PUSUPPLIER_H_

/******************************************************************************/
/* c:\prri\Headerfiles\pusupplier *********************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
//#include <bufkon.h>

/* Length-Define of PUSUPPLIER ************************************************/

#define L_PUSUPPLIER_BESLA_NR 11
#define L_PUSUPPLIER_LANT_NR 11
#define L_PUSUPPLIER_BESLA_MC 15
#define L_PUSUPPLIER_BESLA_NAME 30
#define L_PUSUPPLIER_ANREDE 6
#define L_PUSUPPLIER_ANREDE_2 6
#define L_PUSUPPLIER_TITEL 30
#define L_PUSUPPLIER_VORNAME 30
#define L_PUSUPPLIER_NAME 30
#define L_PUSUPPLIER_STRASSE 30
#define L_PUSUPPLIER_PLZ_STRASSE 7
#define L_PUSUPPLIER_POSTFACH 10
#define L_PUSUPPLIER_ORT 30
#define L_PUSUPPLIER_ABTEILUNG 30
#define L_PUSUPPLIER_MAILNR_1 8
#define L_PUSUPPLIER_MAILNR_2 8
#define L_PUSUPPLIER_VORWAHL 10
#define L_PUSUPPLIER_TELEFON 15
#define L_PUSUPPLIER_TELEFAX 15
#define L_PUSUPPLIER_SONDERBESTELL 1
#define L_PUSUPPLIER_PHOENIX_OHNE 1
#define L_PUSUPPLIER_AUSTAUSCH_GESPERRT 1
#define L_PUSUPPLIER_PREIS_BASIS 1
#define L_PUSUPPLIER_VERZ_TAGE 11
#define L_PUSUPPLIER_MAX_ZEILEN 11
#define L_PUSUPPLIER_DATUM_ANLAGE 11
#define L_PUSUPPLIER_SONDERLIEFERANT 1
#define L_PUSUPPLIER_DATUM_AENDER 11
#define L_PUSUPPLIER_DATUM_LOESCH 11
#define L_PUSUPPLIER_BEARBEITER 8
#define L_PUSUPPLIER_LANDESKUERZEL 3
#define L_PUSUPPLIER_VORWAHL_FAX 10
#define L_PUSUPPLIER_BEMERKUNGEN 240
#define L_PUSUPPLIER_BESTELLADRESSEPPE 1
#define L_PUSUPPLIER_MANDATSLAGER 1
#define L_PUSUPPLIER_FILIALNRMANDAT_LAG 6
#define L_PUSUPPLIER_ZWISCHENLIEFER 1
#define L_PUSUPPLIER_LIEFERSPEZIAL 1
#define L_PUSUPPLIER_BGA_NR 11
#define L_PUSUPPLIER_LIEFER_BESLA_NR 11
#define L_PUSUPPLIER_EAN1 13
#define L_PUSUPPLIER_EAN2 13
#define L_PUSUPPLIER_SIREN_CODE 9
#define L_PUSUPPLIER_SIRET_CODE 5
#define L_PUSUPPLIER_BESTELL_VARIANTE 6
#define L_PUSUPPLIER_E_MAIL 120
#define L_PUSUPPLIER_ANZEIGE_NBG 1
#define L_PUSUPPLIER_PUPRODUCTGROUPID 6

/* Length/Count-Define of PUSUPPLIER ******************************************/

#define LS_PUSUPPLIER_BESLA_NR 10 + 1
#define LS_PUSUPPLIER_LANT_NR 10 + 1
#define LS_PUSUPPLIER_BESLA_MC 15 + 1
#define LS_PUSUPPLIER_BESLA_NAME 30 + 1
#define LS_PUSUPPLIER_ANREDE 6 + 1
#define LS_PUSUPPLIER_ANREDE_2 6 + 1
#define LS_PUSUPPLIER_TITEL 30 + 1
#define LS_PUSUPPLIER_VORNAME 30 + 1
#define LS_PUSUPPLIER_NAME 30 + 1
#define LS_PUSUPPLIER_STRASSE 30 + 1
#define LS_PUSUPPLIER_PLZ_STRASSE 7 + 1
#define LS_PUSUPPLIER_POSTFACH 10 + 1
#define LS_PUSUPPLIER_ORT 30 + 1
#define LS_PUSUPPLIER_ABTEILUNG 30 + 1
#define LS_PUSUPPLIER_MAILNR_1 8 + 1
#define LS_PUSUPPLIER_MAILNR_2 8 + 1
#define LS_PUSUPPLIER_VORWAHL 10 + 1
#define LS_PUSUPPLIER_TELEFON 15 + 1
#define LS_PUSUPPLIER_TELEFAX 15 + 1
#define LS_PUSUPPLIER_SONDERBESTELL 1 + 1
#define LS_PUSUPPLIER_PHOENIX_OHNE 1 + 1
#define LS_PUSUPPLIER_AUSTAUSCH_GESPERRT 1 + 1
#define LS_PUSUPPLIER_PREIS_BASIS 1 + 1
#define LS_PUSUPPLIER_VERZ_TAGE 10 + 1
#define LS_PUSUPPLIER_MAX_ZEILEN 10 + 1
#define LS_PUSUPPLIER_DATUM_ANLAGE 10 + 1
#define LS_PUSUPPLIER_SONDERLIEFERANT 1 + 1
#define LS_PUSUPPLIER_DATUM_AENDER 10 + 1
#define LS_PUSUPPLIER_DATUM_LOESCH 10 + 1
#define LS_PUSUPPLIER_BEARBEITER 8 + 1
#define LS_PUSUPPLIER_LANDESKUERZEL 3 + 1
#define LS_PUSUPPLIER_VORWAHL_FAX 10 + 1
#define LS_PUSUPPLIER_BEMERKUNGEN 240 + 1
#define LS_PUSUPPLIER_BESTELLADRESSEPPE 1 + 1
#define LS_PUSUPPLIER_MANDATSLAGER 1 + 1
#define LS_PUSUPPLIER_FILIALNRMANDAT_LAG 5 + 1
#define LS_PUSUPPLIER_ZWISCHENLIEFER 1 + 1
#define LS_PUSUPPLIER_LIEFERSPEZIAL 1 + 1
#define LS_PUSUPPLIER_BGA_NR 10 + 1
#define LS_PUSUPPLIER_LIEFER_BESLA_NR 10 + 1
#define LS_PUSUPPLIER_EAN1 13 + 1
#define LS_PUSUPPLIER_EAN2 13 + 1
#define LS_PUSUPPLIER_SIREN_CODE 9 + 1
#define LS_PUSUPPLIER_SIRET_CODE 5 + 1
#define LS_PUSUPPLIER_BESTELL_VARIANTE 5 + 1
#define LS_PUSUPPLIER_E_MAIL 120 + 1
#define LS_PUSUPPLIER_ANZEIGE_NBG 1 + 1
#define LS_PUSUPPLIER_PUPRODUCTGROUPID 5 + 1

#define PUSUPPLIERBESLA_NR 0
#define PUSUPPLIERLANT_NR 1
#define PUSUPPLIERBESLA_MC 2
#define PUSUPPLIERBESLA_NAME 3
#define PUSUPPLIERANREDE 4
#define PUSUPPLIERANREDE_2 5
#define PUSUPPLIERTITEL 6
#define PUSUPPLIERVORNAME 7
#define PUSUPPLIERNAME 8
#define PUSUPPLIERSTRASSE 9
#define PUSUPPLIERPLZ_STRASSE 10
#define PUSUPPLIERPOSTFACH 11
#define PUSUPPLIERORT 12
#define PUSUPPLIERABTEILUNG 13
#define PUSUPPLIERMAILNR_1 14
#define PUSUPPLIERMAILNR_2 15
#define PUSUPPLIERVORWAHL 16
#define PUSUPPLIERTELEFON 17
#define PUSUPPLIERTELEFAX 18
#define PUSUPPLIERSONDERBESTELL 19
#define PUSUPPLIERPHOENIX_OHNE 20
#define PUSUPPLIERAUSTAUSCH_GESPERRT 21
#define PUSUPPLIERPREIS_BASIS 22
#define PUSUPPLIERVERZ_TAGE 23
#define PUSUPPLIERMAX_ZEILEN 24
#define PUSUPPLIERDATUM_ANLAGE 25
#define PUSUPPLIERSONDERLIEFERANT 26
#define PUSUPPLIERDATUM_AENDER 27
#define PUSUPPLIERDATUM_LOESCH 28
#define PUSUPPLIERBEARBEITER 29
#define PUSUPPLIERLANDESKUERZEL 30
#define PUSUPPLIERVORWAHL_FAX 31
#define PUSUPPLIERBEMERKUNGEN 32
#define PUSUPPLIERBESTELLADRESSEPPE 33
#define PUSUPPLIERMANDATSLAGER 34
#define PUSUPPLIERFILIALNRMANDAT_LAG 35
#define PUSUPPLIERZWISCHENLIEFER 36
#define PUSUPPLIERLIEFERSPEZIAL 37
#define PUSUPPLIERBGA_NR 38
#define PUSUPPLIERLIEFER_BESLA_NR 39
#define PUSUPPLIEREAN1 40
#define PUSUPPLIEREAN2 41
#define PUSUPPLIERSIREN_CODE 42
#define PUSUPPLIERSIRET_CODE 43
#define PUSUPPLIERBESTELL_VARIANTE 44
#define PUSUPPLIERE_MAIL 45
#define PUSUPPLIERANZEIGE_NBG 46
#define PUSUPPLIERPUPRODUCTGROUPID 47

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define PUSUPPLIER_H
#define PUSUPPLIER_ANZ ( sizeof(PUSUPPLIER_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of PUSUPPLIER ****************************************************/

#define PUSUPPLIER_LISTE \
        PUSUPPLIER.BESLA_NR,\
        PUSUPPLIER.LANT_NR,\
        PUSUPPLIER.BESLA_MC,\
        PUSUPPLIER.BESLA_NAME,\
        PUSUPPLIER.ANREDE,\
        PUSUPPLIER.ANREDE_2,\
        PUSUPPLIER.TITEL,\
        PUSUPPLIER.VORNAME,\
        PUSUPPLIER.NAME,\
        PUSUPPLIER.STRASSE,\
        PUSUPPLIER.PLZ_STRASSE,\
        PUSUPPLIER.POSTFACH,\
        PUSUPPLIER.ORT,\
        PUSUPPLIER.ABTEILUNG,\
        PUSUPPLIER.MAILNR_1,\
        PUSUPPLIER.MAILNR_2,\
        PUSUPPLIER.VORWAHL,\
        PUSUPPLIER.TELEFON,\
        PUSUPPLIER.TELEFAX,\
        PUSUPPLIER.SONDERBESTELL,\
        PUSUPPLIER.PHOENIX_OHNE,\
        PUSUPPLIER.AUSTAUSCH_GESPERRT,\
        PUSUPPLIER.PREIS_BASIS,\
        PUSUPPLIER.VERZ_TAGE,\
        PUSUPPLIER.MAX_ZEILEN,\
        PUSUPPLIER.DATUM_ANLAGE,\
        PUSUPPLIER.SONDERLIEFERANT,\
        PUSUPPLIER.DATUM_AENDER,\
        PUSUPPLIER.DATUM_LOESCH,\
        PUSUPPLIER.BEARBEITER,\
        PUSUPPLIER.LANDESKUERZEL,\
        PUSUPPLIER.VORWAHL_FAX,\
        PUSUPPLIER.BEMERKUNGEN,\
        PUSUPPLIER.BESTELLADRESSEPPE,\
        PUSUPPLIER.MANDATSLAGER,\
        PUSUPPLIER.FILIALNRMANDAT_LAG,\
        PUSUPPLIER.ZWISCHENLIEFER,\
        PUSUPPLIER.LIEFERSPEZIAL,\
        PUSUPPLIER.BGA_NR,\
        PUSUPPLIER.LIEFER_BESLA_NR,\
        PUSUPPLIER.EAN1,\
        PUSUPPLIER.EAN2,\
        PUSUPPLIER.SIREN_CODE,\
        PUSUPPLIER.SIRET_CODE,\
        PUSUPPLIER.BESTELL_VARIANTE,\
        PUSUPPLIER.E_MAIL,\
        PUSUPPLIER.ANZEIGE_NBG,\
        PUSUPPLIER.PUPRODUCTGROUPID
#define PUSUPPLIER_LISTE_390 \
        BESLA_NR,\
        LANT_NR,\
        BESLA_MC,\
        BESLA_NAME,\
        ANREDE,\
        ANREDE_2,\
        TITEL,\
        VORNAME,\
        NAME,\
        STRASSE,\
        PLZ_STRASSE,\
        POSTFACH,\
        ORT,\
        ABTEILUNG,\
        MAILNR_1,\
        MAILNR_2,\
        VORWAHL,\
        TELEFON,\
        TELEFAX,\
        SONDERBESTELL,\
        PHOENIX_OHNE,\
        AUSTAUSCH_GESPERRT,\
        PREIS_BASIS,\
        VERZ_TAGE,\
        MAX_ZEILEN,\
        DATUM_ANLAGE,\
        SONDERLIEFERANT,\
        DATUM_AENDER,\
        DATUM_LOESCH,\
        BEARBEITER,\
        LANDESKUERZEL,\
        VORWAHL_FAX,\
        BEMERKUNGEN,\
        BESTELLADRESSEPPE,\
        MANDATSLAGER,\
        FILIALNRMANDAT_LAG,\
        ZWISCHENLIEFER,\
        LIEFERSPEZIAL,\
        BGA_NR,\
        LIEFER_BESLA_NR,\
        EAN1,\
        EAN2,\
        SIREN_CODE,\
        SIRET_CODE,\
        BESTELL_VARIANTE,\
        E_MAIL,\
        ANZEIGE_NBG,\
        PUPRODUCTGROUPID
#define PUSUPPLIER_PLISTE \
        "PUSUPPLIER.BESLA_NR,"\
        "PUSUPPLIER.LANT_NR,"\
        "PUSUPPLIER.BESLA_MC,"\
        "PUSUPPLIER.BESLA_NAME,"\
        "PUSUPPLIER.ANREDE,"\
        "PUSUPPLIER.ANREDE_2,"\
        "PUSUPPLIER.TITEL,"\
        "PUSUPPLIER.VORNAME,"\
        "PUSUPPLIER.NAME,"\
        "PUSUPPLIER.STRASSE,"\
        "PUSUPPLIER.PLZ_STRASSE,"\
        "PUSUPPLIER.POSTFACH,"\
        "PUSUPPLIER.ORT,"\
        "PUSUPPLIER.ABTEILUNG,"\
        "PUSUPPLIER.MAILNR_1,"\
        "PUSUPPLIER.MAILNR_2,"\
        "PUSUPPLIER.VORWAHL,"\
        "PUSUPPLIER.TELEFON,"\
        "PUSUPPLIER.TELEFAX,"\
        "PUSUPPLIER.SONDERBESTELL,"\
        "PUSUPPLIER.PHOENIX_OHNE,"\
        "PUSUPPLIER.AUSTAUSCH_GESPERRT,"\
        "PUSUPPLIER.PREIS_BASIS,"\
        "PUSUPPLIER.VERZ_TAGE,"\
        "PUSUPPLIER.MAX_ZEILEN,"\
        "PUSUPPLIER.DATUM_ANLAGE,"\
        "PUSUPPLIER.SONDERLIEFERANT,"\
        "PUSUPPLIER.DATUM_AENDER,"\
        "PUSUPPLIER.DATUM_LOESCH,"\
        "PUSUPPLIER.BEARBEITER,"\
        "PUSUPPLIER.LANDESKUERZEL,"\
        "PUSUPPLIER.VORWAHL_FAX,"\
        "PUSUPPLIER.BEMERKUNGEN,"\
        "PUSUPPLIER.BESTELLADRESSEPPE,"\
        "PUSUPPLIER.MANDATSLAGER,"\
        "PUSUPPLIER.FILIALNRMANDAT_LAG,"\
        "PUSUPPLIER.ZWISCHENLIEFER,"\
        "PUSUPPLIER.LIEFERSPEZIAL,"\
        "PUSUPPLIER.BGA_NR,"\
        "PUSUPPLIER.LIEFER_BESLA_NR,"\
        "PUSUPPLIER.EAN1,"\
        "PUSUPPLIER.EAN2,"\
        "PUSUPPLIER.SIREN_CODE,"\
        "PUSUPPLIER.SIRET_CODE,"\
        "PUSUPPLIER.BESTELL_VARIANTE,"\
        "PUSUPPLIER.E_MAIL,"\
        "PUSUPPLIER.ANZEIGE_NBG,"\
        "PUSUPPLIER.PUPRODUCTGROUPID"
#define PUSUPPLIER_PELISTE \
        "BESLA_NR,"\
        "LANT_NR,"\
        "BESLA_MC,"\
        "BESLA_NAME,"\
        "ANREDE,"\
        "ANREDE_2,"\
        "TITEL,"\
        "VORNAME,"\
        "NAME,"\
        "STRASSE,"\
        "PLZ_STRASSE,"\
        "POSTFACH,"\
        "ORT,"\
        "ABTEILUNG,"\
        "MAILNR_1,"\
        "MAILNR_2,"\
        "VORWAHL,"\
        "TELEFON,"\
        "TELEFAX,"\
        "SONDERBESTELL,"\
        "PHOENIX_OHNE,"\
        "AUSTAUSCH_GESPERRT,"\
        "PREIS_BASIS,"\
        "VERZ_TAGE,"\
        "MAX_ZEILEN,"\
        "DATUM_ANLAGE,"\
        "SONDERLIEFERANT,"\
        "DATUM_AENDER,"\
        "DATUM_LOESCH,"\
        "BEARBEITER,"\
        "LANDESKUERZEL,"\
        "VORWAHL_FAX,"\
        "BEMERKUNGEN,"\
        "BESTELLADRESSEPPE,"\
        "MANDATSLAGER,"\
        "FILIALNRMANDAT_LAG,"\
        "ZWISCHENLIEFER,"\
        "LIEFERSPEZIAL,"\
        "BGA_NR,"\
        "LIEFER_BESLA_NR,"\
        "EAN1,"\
        "EAN2,"\
        "SIREN_CODE,"\
        "SIRET_CODE,"\
        "BESTELL_VARIANTE,"\
        "E_MAIL,"\
        "ANZEIGE_NBG,"\
        "PUPRODUCTGROUPID"
#define PUSUPPLIER_UPDLISTE \
        "BESLA_NR=?,"\
        "LANT_NR=?,"\
        "BESLA_MC=?,"\
        "BESLA_NAME=?,"\
        "ANREDE=?,"\
        "ANREDE_2=?,"\
        "TITEL=?,"\
        "VORNAME=?,"\
        "NAME=?,"\
        "STRASSE=?,"\
        "PLZ_STRASSE=?,"\
        "POSTFACH=?,"\
        "ORT=?,"\
        "ABTEILUNG=?,"\
        "MAILNR_1=?,"\
        "MAILNR_2=?,"\
        "VORWAHL=?,"\
        "TELEFON=?,"\
        "TELEFAX=?,"\
        "SONDERBESTELL=?,"\
        "PHOENIX_OHNE=?,"\
        "AUSTAUSCH_GESPERRT=?,"\
        "PREIS_BASIS=?,"\
        "VERZ_TAGE=?,"\
        "MAX_ZEILEN=?,"\
        "DATUM_ANLAGE=?,"\
        "SONDERLIEFERANT=?,"\
        "DATUM_AENDER=?,"\
        "DATUM_LOESCH=?,"\
        "BEARBEITER=?,"\
        "LANDESKUERZEL=?,"\
        "VORWAHL_FAX=?,"\
        "BEMERKUNGEN=?,"\
        "BESTELLADRESSEPPE=?,"\
        "MANDATSLAGER=?,"\
        "FILIALNRMANDAT_LAG=?,"\
        "ZWISCHENLIEFER=?,"\
        "LIEFERSPEZIAL=?,"\
        "BGA_NR=?,"\
        "LIEFER_BESLA_NR=?,"\
        "EAN1=?,"\
        "EAN2=?,"\
        "SIREN_CODE=?,"\
        "SIRET_CODE=?,"\
        "BESTELL_VARIANTE=?,"\
        "E_MAIL=?,"\
        "ANZEIGE_NBG=?,"\
        "PUPRODUCTGROUPID=?"
/* SqlMacros-Define of PUSUPPLIER *********************************************/

#define PUSUPPLIER_ZEIGER(x) \
        :x->BESLA_NR,\
        :x->LANT_NR,\
        :x->BESLA_MC,\
        :x->BESLA_NAME,\
        :x->ANREDE,\
        :x->ANREDE_2,\
        :x->TITEL,\
        :x->VORNAME,\
        :x->NAME,\
        :x->STRASSE,\
        :x->PLZ_STRASSE,\
        :x->POSTFACH,\
        :x->ORT,\
        :x->ABTEILUNG,\
        :x->MAILNR_1,\
        :x->MAILNR_2,\
        :x->VORWAHL,\
        :x->TELEFON,\
        :x->TELEFAX,\
        :x->SONDERBESTELL,\
        :x->PHOENIX_OHNE,\
        :x->AUSTAUSCH_GESPERRT,\
        :x->PREIS_BASIS,\
        :x->VERZ_TAGE,\
        :x->MAX_ZEILEN,\
        :x->DATUM_ANLAGE,\
        :x->SONDERLIEFERANT,\
        :x->DATUM_AENDER,\
        :x->DATUM_LOESCH,\
        :x->BEARBEITER,\
        :x->LANDESKUERZEL,\
        :x->VORWAHL_FAX,\
        :x->BEMERKUNGEN,\
        :x->BESTELLADRESSEPPE,\
        :x->MANDATSLAGER,\
        :x->FILIALNRMANDAT_LAG,\
        :x->ZWISCHENLIEFER,\
        :x->LIEFERSPEZIAL,\
        :x->BGA_NR,\
        :x->LIEFER_BESLA_NR,\
        :x->EAN1,\
        :x->EAN2,\
        :x->SIREN_CODE,\
        :x->SIRET_CODE,\
        :x->BESTELL_VARIANTE,\
        :x->E_MAIL,\
        :x->ANZEIGE_NBG,\
        :x->PUPRODUCTGROUPID
#define PUSUPPLIER_ZEIGERSEL(x) \
        :x->BESLA_NR,\
        :x->LANT_NR,\
        :x->BESLA_MC,\
        :x->BESLA_NAME,\
        :x->ANREDE,\
        :x->ANREDE_2,\
        :x->TITEL,\
        :x->VORNAME,\
        :x->NAME,\
        :x->STRASSE,\
        :x->PLZ_STRASSE,\
        :x->POSTFACH,\
        :x->ORT,\
        :x->ABTEILUNG,\
        :x->MAILNR_1,\
        :x->MAILNR_2,\
        :x->VORWAHL,\
        :x->TELEFON,\
        :x->TELEFAX,\
        :x->SONDERBESTELL,\
        :x->PHOENIX_OHNE,\
        :x->AUSTAUSCH_GESPERRT,\
        :x->PREIS_BASIS,\
        :x->VERZ_TAGE,\
        :x->MAX_ZEILEN,\
        :x->DATUM_ANLAGE,\
        :x->SONDERLIEFERANT,\
        :x->DATUM_AENDER,\
        :x->DATUM_LOESCH,\
        :x->BEARBEITER,\
        :x->LANDESKUERZEL,\
        :x->VORWAHL_FAX,\
        :x->BEMERKUNGEN,\
        :x->BESTELLADRESSEPPE,\
        :x->MANDATSLAGER,\
        :x->FILIALNRMANDAT_LAG,\
        :x->ZWISCHENLIEFER,\
        :x->LIEFERSPEZIAL,\
        :x->BGA_NR,\
        :x->LIEFER_BESLA_NR,\
        :x->EAN1,\
        :x->EAN2,\
        :x->SIREN_CODE,\
        :x->SIRET_CODE,\
        :x->BESTELL_VARIANTE,\
        :x->E_MAIL,\
        :x->ANZEIGE_NBG,\
        :x->PUPRODUCTGROUPID
#define PUSUPPLIER_UPDATE(x) \
        BLIEFER.BESLA_NR=:x->BESLA_NR,\
        BLIEFER.LANT_NR=:x->LANT_NR,\
        BLIEFER.BESLA_MC=:x->BESLA_MC,\
        BLIEFER.BESLA_NAME=:x->BESLA_NAME,\
        BLIEFER.ANREDE=:x->ANREDE,\
        BLIEFER.ANREDE_2=:x->ANREDE_2,\
        BLIEFER.TITEL=:x->TITEL,\
        BLIEFER.VORNAME=:x->VORNAME,\
        BLIEFER.NAME=:x->NAME,\
        BLIEFER.STRASSE=:x->STRASSE,\
        BLIEFER.PLZ_STRASSE=:x->PLZ_STRASSE,\
        BLIEFER.POSTFACH=:x->POSTFACH,\
        BLIEFER.ORT=:x->ORT,\
        BLIEFER.ABTEILUNG=:x->ABTEILUNG,\
        BLIEFER.MAILNR_1=:x->MAILNR_1,\
        BLIEFER.MAILNR_2=:x->MAILNR_2,\
        BLIEFER.VORWAHL=:x->VORWAHL,\
        BLIEFER.TELEFON=:x->TELEFON,\
        BLIEFER.TELEFAX=:x->TELEFAX,\
        BLIEFER.SONDERBESTELL=:x->SONDERBESTELL,\
        BLIEFER.PHOENIX_OHNE=:x->PHOENIX_OHNE,\
        BLIEFER.AUSTAUSCH_GESPERRT=:x->AUSTAUSCH_GESPERRT,\
        BLIEFER.PREIS_BASIS=:x->PREIS_BASIS,\
        BLIEFER.VERZ_TAGE=:x->VERZ_TAGE,\
        BLIEFER.MAX_ZEILEN=:x->MAX_ZEILEN,\
        BLIEFER.DATUM_ANLAGE=:x->DATUM_ANLAGE,\
        BLIEFER.SONDERLIEFERANT=:x->SONDERLIEFERANT,\
        BLIEFER.DATUM_AENDER=:x->DATUM_AENDER,\
        BLIEFER.DATUM_LOESCH=:x->DATUM_LOESCH,\
        BLIEFER.BEARBEITER=:x->BEARBEITER,\
        BLIEFER.LANDESKUERZEL=:x->LANDESKUERZEL,\
        BLIEFER.VORWAHL_FAX=:x->VORWAHL_FAX,\
        BLIEFER.BEMERKUNGEN=:x->BEMERKUNGEN,\
        BLIEFER.BESTELLADRESSEPPE=:x->BESTELLADRESSEPPE,\
        BLIEFER.MANDATSLAGER=:x->MANDATSLAGER,\
        BLIEFER.FILIALNRMANDAT_LAG=:x->FILIALNRMANDAT_LAG,\
        BLIEFER.ZWISCHENLIEFER=:x->ZWISCHENLIEFER,\
        BLIEFER.LIEFERSPEZIAL=:x->LIEFERSPEZIAL,\
        BLIEFER.BGA_NR=:x->BGA_NR,\
        BLIEFER.LIEFER_BESLA_NR=:x->LIEFER_BESLA_NR,\
        BLIEFER.EAN1=:x->EAN1,\
        BLIEFER.EAN2=:x->EAN2,\
        BLIEFER.SIREN_CODE=:x->SIREN_CODE,\
        BLIEFER.SIRET_CODE=:x->SIRET_CODE,\
        BLIEFER.BESTELL_VARIANTE=:x->BESTELL_VARIANTE,\
        BLIEFER.E_MAIL=:x->E_MAIL,\
        BLIEFER.ANZEIGE_NBG=:x->ANZEIGE_NBG,\
        BLIEFER.PUPRODUCTGROUPID=:x->PUPRODUCTGROUPID
/* SqlMacros390-Define of PUSUPPLIER ******************************************/

#define PUSUPPLIER_ZEIGER_390 \
        :BESLA_NR,\
        :LANT_NR,\
        :BESLA_MC,\
        :BESLA_NAME,\
        :ANREDE,\
        :ANREDE_2,\
        :TITEL,\
        :VORNAME,\
        :NAME,\
        :STRASSE,\
        :PLZ_STRASSE,\
        :POSTFACH,\
        :ORT,\
        :ABTEILUNG,\
        :MAILNR_1,\
        :MAILNR_2,\
        :VORWAHL,\
        :TELEFON,\
        :TELEFAX,\
        :SONDERBESTELL,\
        :PHOENIX_OHNE,\
        :AUSTAUSCH_GESPERRT,\
        :PREIS_BASIS,\
        :VERZ_TAGE,\
        :MAX_ZEILEN,\
        :DATUM_ANLAGE,\
        :SONDERLIEFERANT,\
        :DATUM_AENDER,\
        :DATUM_LOESCH,\
        :BEARBEITER,\
        :LANDESKUERZEL,\
        :VORWAHL_FAX,\
        :BEMERKUNGEN,\
        :BESTELLADRESSEPPE,\
        :MANDATSLAGER,\
        :FILIALNRMANDAT_LAG,\
        :ZWISCHENLIEFER,\
        :LIEFERSPEZIAL,\
        :BGA_NR,\
        :LIEFER_BESLA_NR,\
        :EAN1,\
        :EAN2,\
        :SIREN_CODE,\
        :SIRET_CODE,\
        :BESTELL_VARIANTE,\
        :E_MAIL,\
        :ANZEIGE_NBG,\
        :PUPRODUCTGROUPID
#define PUSUPPLIER_UPDATE_390 \
        BESLA_NR=:BESLA_NR,\
        LANT_NR=:LANT_NR,\
        BESLA_MC=:BESLA_MC,\
        BESLA_NAME=:BESLA_NAME,\
        ANREDE=:ANREDE,\
        ANREDE_2=:ANREDE_2,\
        TITEL=:TITEL,\
        VORNAME=:VORNAME,\
        NAME=:NAME,\
        STRASSE=:STRASSE,\
        PLZ_STRASSE=:PLZ_STRASSE,\
        POSTFACH=:POSTFACH,\
        ORT=:ORT,\
        ABTEILUNG=:ABTEILUNG,\
        MAILNR_1=:MAILNR_1,\
        MAILNR_2=:MAILNR_2,\
        VORWAHL=:VORWAHL,\
        TELEFON=:TELEFON,\
        TELEFAX=:TELEFAX,\
        SONDERBESTELL=:SONDERBESTELL,\
        PHOENIX_OHNE=:PHOENIX_OHNE,\
        AUSTAUSCH_GESPERRT=:AUSTAUSCH_GESPERRT,\
        PREIS_BASIS=:PREIS_BASIS,\
        VERZ_TAGE=:VERZ_TAGE,\
        MAX_ZEILEN=:MAX_ZEILEN,\
        DATUM_ANLAGE=:DATUM_ANLAGE,\
        SONDERLIEFERANT=:SONDERLIEFERANT,\
        DATUM_AENDER=:DATUM_AENDER,\
        DATUM_LOESCH=:DATUM_LOESCH,\
        BEARBEITER=:BEARBEITER,\
        LANDESKUERZEL=:LANDESKUERZEL,\
        VORWAHL_FAX=:VORWAHL_FAX,\
        BEMERKUNGEN=:BEMERKUNGEN,\
        BESTELLADRESSEPPE=:BESTELLADRESSEPPE,\
        MANDATSLAGER=:MANDATSLAGER,\
        FILIALNRMANDAT_LAG=:FILIALNRMANDAT_LAG,\
        ZWISCHENLIEFER=:ZWISCHENLIEFER,\
        LIEFERSPEZIAL=:LIEFERSPEZIAL,\
        BGA_NR=:BGA_NR,\
        LIEFER_BESLA_NR=:LIEFER_BESLA_NR,\
        EAN1=:EAN1,\
        EAN2=:EAN2,\
        SIREN_CODE=:SIREN_CODE,\
        SIRET_CODE=:SIRET_CODE,\
        BESTELL_VARIANTE=:BESTELL_VARIANTE,\
        E_MAIL=:E_MAIL,\
        ANZEIGE_NBG=:ANZEIGE_NBG,\
        PUPRODUCTGROUPID=:PUPRODUCTGROUPID
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of PUSUPPLIER **********************************************/

#ifndef TRANSCLASS
typedef struct N_PUSUPPLIER {
    long BESLA_NR;
    long LANT_NR;
    char BESLA_MC[16];
    char BESLA_NAME[31];
    char ANREDE[7];
    char ANREDE_2[7];
    char TITEL[31];
    char VORNAME[31];
    char NAME[31];
    char STRASSE[31];
    char PLZ_STRASSE[8];
    char POSTFACH[11];
    char ORT[31];
    char ABTEILUNG[31];
    char MAILNR_1[9];
    char MAILNR_2[9];
    char VORWAHL[11];
    char TELEFON[16];
    char TELEFAX[16];
    char SONDERBESTELL[2];
    char PHOENIX_OHNE[2];
    char AUSTAUSCH_GESPERRT[2];
    char PREIS_BASIS[2];
    long VERZ_TAGE;
    long MAX_ZEILEN;
    long DATUM_ANLAGE;
    char SONDERLIEFERANT[2];
    long DATUM_AENDER;
    long DATUM_LOESCH;
    char BEARBEITER[9];
    char LANDESKUERZEL[4];
    char VORWAHL_FAX[11];
    char BEMERKUNGEN[241];
    char BESTELLADRESSEPPE[2];
    char MANDATSLAGER[2];
    short FILIALNRMANDAT_LAG;
    char ZWISCHENLIEFER[2];
    char LIEFERSPEZIAL[2];
    long BGA_NR;
    long LIEFER_BESLA_NR;
    char EAN1[14];
    char EAN2[14];
    char SIREN_CODE[10];
    char SIRET_CODE[6];
    short BESTELL_VARIANTE;
    char E_MAIL[121];
    char ANZEIGE_NBG[2];
    short PUPRODUCTGROUPID;
} pusupplierS;
#else /* TRANSCLASS */
typedef struct N_PUSUPPLIER {
    long BESLA_NR;
    long LANT_NR;
    char BESLA_MC[16];
    char BESLA_NAME[31];
    char ANREDE[7];
    char ANREDE_2[7];
    char TITEL[31];
    char VORNAME[31];
    char NAME[31];
    char STRASSE[31];
    char PLZ_STRASSE[8];
    char POSTFACH[11];
    char ORT[31];
    char ABTEILUNG[31];
    char MAILNR_1[9];
    char MAILNR_2[9];
    char VORWAHL[11];
    char TELEFON[16];
    char TELEFAX[16];
    char SONDERBESTELL[2];
    char PHOENIX_OHNE[2];
    char AUSTAUSCH_GESPERRT[2];
    char PREIS_BASIS[2];
    long VERZ_TAGE;
    long MAX_ZEILEN;
    long DATUM_ANLAGE;
    char SONDERLIEFERANT[2];
    long DATUM_AENDER;
    long DATUM_LOESCH;
    char BEARBEITER[9];
    char LANDESKUERZEL[4];
    char VORWAHL_FAX[11];
    char BEMERKUNGEN[241];
    char BESTELLADRESSEPPE[2];
    char MANDATSLAGER[2];
    short FILIALNRMANDAT_LAG;
    char ZWISCHENLIEFER[2];
    char LIEFERSPEZIAL[2];
    long BGA_NR;
    long LIEFER_BESLA_NR;
    char EAN1[14];
    char EAN2[14];
    char SIREN_CODE[10];
    char SIRET_CODE[6];
    short BESTELL_VARIANTE;
    char E_MAIL[121];
    char ANZEIGE_NBG[2];
    short PUPRODUCTGROUPID;

    bool operator == (const N_PUSUPPLIER& right) const {
        return (
            BESLA_NR == right.BESLA_NR &&
            LANT_NR == right.LANT_NR &&
            !strcmp(BESLA_MC, right.BESLA_MC) &&
            !strcmp(BESLA_NAME, right.BESLA_NAME) &&
            !strcmp(ANREDE, right.ANREDE) &&
            !strcmp(ANREDE_2, right.ANREDE_2) &&
            !strcmp(TITEL, right.TITEL) &&
            !strcmp(VORNAME, right.VORNAME) &&
            !strcmp(NAME, right.NAME) &&
            !strcmp(STRASSE, right.STRASSE) &&
            !strcmp(PLZ_STRASSE, right.PLZ_STRASSE) &&
            !strcmp(POSTFACH, right.POSTFACH) &&
            !strcmp(ORT, right.ORT) &&
            !strcmp(ABTEILUNG, right.ABTEILUNG) &&
            !strcmp(MAILNR_1, right.MAILNR_1) &&
            !strcmp(MAILNR_2, right.MAILNR_2) &&
            !strcmp(VORWAHL, right.VORWAHL) &&
            !strcmp(TELEFON, right.TELEFON) &&
            !strcmp(TELEFAX, right.TELEFAX) &&
            !strcmp(SONDERBESTELL, right.SONDERBESTELL) &&
            !strcmp(PHOENIX_OHNE, right.PHOENIX_OHNE) &&
            !strcmp(AUSTAUSCH_GESPERRT, right.AUSTAUSCH_GESPERRT) &&
            !strcmp(PREIS_BASIS, right.PREIS_BASIS) &&
            VERZ_TAGE == right.VERZ_TAGE &&
            MAX_ZEILEN == right.MAX_ZEILEN &&
            DATUM_ANLAGE == right.DATUM_ANLAGE &&
            !strcmp(SONDERLIEFERANT, right.SONDERLIEFERANT) &&
            DATUM_AENDER == right.DATUM_AENDER &&
            DATUM_LOESCH == right.DATUM_LOESCH &&
            !strcmp(BEARBEITER, right.BEARBEITER) &&
            !strcmp(LANDESKUERZEL, right.LANDESKUERZEL) &&
            !strcmp(VORWAHL_FAX, right.VORWAHL_FAX) &&
            !strcmp(BEMERKUNGEN, right.BEMERKUNGEN) &&
            !strcmp(BESTELLADRESSEPPE, right.BESTELLADRESSEPPE) &&
            !strcmp(MANDATSLAGER, right.MANDATSLAGER) &&
            FILIALNRMANDAT_LAG == right.FILIALNRMANDAT_LAG &&
            !strcmp(ZWISCHENLIEFER, right.ZWISCHENLIEFER) &&
            !strcmp(LIEFERSPEZIAL, right.LIEFERSPEZIAL) &&
            BGA_NR == right.BGA_NR &&
            LIEFER_BESLA_NR == right.LIEFER_BESLA_NR &&
            !strcmp(EAN1, right.EAN1) &&
            !strcmp(EAN2, right.EAN2) &&
            !strcmp(SIREN_CODE, right.SIREN_CODE) &&
            !strcmp(SIRET_CODE, right.SIRET_CODE) &&
            BESTELL_VARIANTE == right.BESTELL_VARIANTE &&
            !strcmp(E_MAIL, right.E_MAIL) &&
            !strcmp(ANZEIGE_NBG, right.ANZEIGE_NBG) &&
            PUPRODUCTGROUPID == right.PUPRODUCTGROUPID
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BESLA_NR = 0;
        LANT_NR = 0;
        strcpy(BESLA_MC, " " );
        strcpy(BESLA_NAME, " " );
        strcpy(ANREDE, " " );
        strcpy(ANREDE_2, " " );
        strcpy(TITEL, " " );
        strcpy(VORNAME, " " );
        strcpy(NAME, " " );
        strcpy(STRASSE, " " );
        strcpy(PLZ_STRASSE, " " );
        strcpy(POSTFACH, " " );
        strcpy(ORT, " " );
        strcpy(ABTEILUNG, " " );
        strcpy(MAILNR_1, " " );
        strcpy(MAILNR_2, " " );
        strcpy(VORWAHL, " " );
        strcpy(TELEFON, " " );
        strcpy(TELEFAX, " " );
        strcpy(SONDERBESTELL, " " );
        strcpy(PHOENIX_OHNE, " " );
        strcpy(AUSTAUSCH_GESPERRT, " " );
        strcpy(PREIS_BASIS, " " );
        VERZ_TAGE = 0;
        MAX_ZEILEN = 0;
        DATUM_ANLAGE = 0;
        strcpy(SONDERLIEFERANT, " " );
        DATUM_AENDER = 0;
        DATUM_LOESCH = 0;
        strcpy(BEARBEITER, " " );
        strcpy(LANDESKUERZEL, " " );
        strcpy(VORWAHL_FAX, " " );
        strcpy(BEMERKUNGEN, " " );
        strcpy(BESTELLADRESSEPPE, " " );
        strcpy(MANDATSLAGER, " " );
        FILIALNRMANDAT_LAG = 0;
        strcpy(ZWISCHENLIEFER, " " );
        strcpy(LIEFERSPEZIAL, " " );
        BGA_NR = 0;
        LIEFER_BESLA_NR = 0;
        strcpy(EAN1, " " );
        strcpy(EAN2, " " );
        strcpy(SIREN_CODE, " " );
        strcpy(SIRET_CODE, " " );
        BESTELL_VARIANTE = 0;
        strcpy(E_MAIL, " " );
        strcpy(ANZEIGE_NBG, " " );
        PUPRODUCTGROUPID = 0;
#endif
    }
} pusupplierS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of PUSUPPLIER ****************************************/

struct S_PUSUPPLIER {
    char BESLA_NR[11];
    char LANT_NR[11];
    char BESLA_MC[15 + 1];
    char BESLA_NAME[30 + 1];
    char ANREDE[6 + 1];
    char ANREDE_2[6 + 1];
    char TITEL[30 + 1];
    char VORNAME[30 + 1];
    char NAME[30 + 1];
    char STRASSE[30 + 1];
    char PLZ_STRASSE[7 + 1];
    char POSTFACH[10 + 1];
    char ORT[30 + 1];
    char ABTEILUNG[30 + 1];
    char MAILNR_1[8 + 1];
    char MAILNR_2[8 + 1];
    char VORWAHL[10 + 1];
    char TELEFON[15 + 1];
    char TELEFAX[15 + 1];
    char SONDERBESTELL[1 + 1];
    char PHOENIX_OHNE[1 + 1];
    char AUSTAUSCH_GESPERRT[1 + 1];
    char PREIS_BASIS[1 + 1];
    char VERZ_TAGE[11];
    char MAX_ZEILEN[11];
    char DATUM_ANLAGE[11];
    char SONDERLIEFERANT[1 + 1];
    char DATUM_AENDER[11];
    char DATUM_LOESCH[11];
    char BEARBEITER[8 + 1];
    char LANDESKUERZEL[3 + 1];
    char VORWAHL_FAX[10 + 1];
    char BEMERKUNGEN[240 + 1];
    char BESTELLADRESSEPPE[1 + 1];
    char MANDATSLAGER[1 + 1];
    char FILIALNRMANDAT_LAG[7];
    char ZWISCHENLIEFER[1 + 1];
    char LIEFERSPEZIAL[1 + 1];
    char BGA_NR[11];
    char LIEFER_BESLA_NR[11];
    char EAN1[13 + 1];
    char EAN2[13 + 1];
    char SIREN_CODE[9 + 1];
    char SIRET_CODE[5 + 1];
    char BESTELL_VARIANTE[7];
    char E_MAIL[120 + 1];
    char ANZEIGE_NBG[1 + 1];
    char PUPRODUCTGROUPID[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of PUSUPPLIER ***********************/

struct O_PUSUPPLIER {
    char BESLA_NR[11];
    char LANT_NR[11];
    char BESLA_MC[15];
    char BESLA_NAME[30];
    char ANREDE[6];
    char ANREDE_2[6];
    char TITEL[30];
    char VORNAME[30];
    char NAME[30];
    char STRASSE[30];
    char PLZ_STRASSE[7];
    char POSTFACH[10];
    char ORT[30];
    char ABTEILUNG[30];
    char MAILNR_1[8];
    char MAILNR_2[8];
    char VORWAHL[10];
    char TELEFON[15];
    char TELEFAX[15];
    char SONDERBESTELL[1];
    char PHOENIX_OHNE[1];
    char AUSTAUSCH_GESPERRT[1];
    char PREIS_BASIS[1];
    char VERZ_TAGE[11];
    char MAX_ZEILEN[11];
    char DATUM_ANLAGE[11];
    char SONDERLIEFERANT[1];
    char DATUM_AENDER[11];
    char DATUM_LOESCH[11];
    char BEARBEITER[8];
    char LANDESKUERZEL[3];
    char VORWAHL_FAX[10];
    char BEMERKUNGEN[240];
    char BESTELLADRESSEPPE[1];
    char MANDATSLAGER[1];
    char FILIALNRMANDAT_LAG[7];
    char ZWISCHENLIEFER[1];
    char LIEFERSPEZIAL[1];
    char BGA_NR[11];
    char LIEFER_BESLA_NR[11];
    char EAN1[13];
    char EAN2[13];
    char SIREN_CODE[9];
    char SIRET_CODE[5];
    char BESTELL_VARIANTE[7];
    char E_MAIL[120];
    char ANZEIGE_NBG[1];
    char PUPRODUCTGROUPID[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of PUSUPPLIER **********************************/

struct C_PUSUPPLIER {
    long BESLA_NR;
    long LANT_NR;
    char BESLA_MC[16];
    char BESLA_NAME[31];
    char ANREDE[7];
    char ANREDE_2[7];
    char TITEL[31];
    char VORNAME[31];
    char NAME[31];
    char STRASSE[31];
    char PLZ_STRASSE[8];
    char POSTFACH[11];
    char ORT[31];
    char ABTEILUNG[31];
    char MAILNR_1[9];
    char MAILNR_2[9];
    char VORWAHL[11];
    char TELEFON[16];
    char TELEFAX[16];
    char SONDERBESTELL;
    char PHOENIX_OHNE;
    char AUSTAUSCH_GESPERRT;
    char PREIS_BASIS;
    long VERZ_TAGE;
    long MAX_ZEILEN;
    long DATUM_ANLAGE;
    char SONDERLIEFERANT;
    long DATUM_AENDER;
    long DATUM_LOESCH;
    char BEARBEITER[9];
    char LANDESKUERZEL[4];
    char VORWAHL_FAX[11];
    char BEMERKUNGEN[241];
    char BESTELLADRESSEPPE;
    char MANDATSLAGER;
    short FILIALNRMANDAT_LAG;
    char ZWISCHENLIEFER;
    char LIEFERSPEZIAL;
    long BGA_NR;
    long LIEFER_BESLA_NR;
    char EAN1[14];
    char EAN2[14];
    char SIREN_CODE[10];
    char SIRET_CODE[6];
    short BESTELL_VARIANTE;
    char E_MAIL[121];
    char ANZEIGE_NBG;
    short PUPRODUCTGROUPID;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of PUSUPPLIER ********************************/

struct I_PUSUPPLIER {
    short BESLA_NR;
    short LANT_NR;
    short BESLA_MC;
    short BESLA_NAME;
    short ANREDE;
    short ANREDE_2;
    short TITEL;
    short VORNAME;
    short NAME;
    short STRASSE;
    short PLZ_STRASSE;
    short POSTFACH;
    short ORT;
    short ABTEILUNG;
    short MAILNR_1;
    short MAILNR_2;
    short VORWAHL;
    short TELEFON;
    short TELEFAX;
    short SONDERBESTELL;
    short PHOENIX_OHNE;
    short AUSTAUSCH_GESPERRT;
    short PREIS_BASIS;
    short VERZ_TAGE;
    short MAX_ZEILEN;
    short DATUM_ANLAGE;
    short SONDERLIEFERANT;
    short DATUM_AENDER;
    short DATUM_LOESCH;
    short BEARBEITER;
    short LANDESKUERZEL;
    short VORWAHL_FAX;
    short BEMERKUNGEN;
    short BESTELLADRESSEPPE;
    short MANDATSLAGER;
    short FILIALNRMANDAT_LAG;
    short ZWISCHENLIEFER;
    short LIEFERSPEZIAL;
    short BGA_NR;
    short LIEFER_BESLA_NR;
    short EAN1;
    short EAN2;
    short SIREN_CODE;
    short SIRET_CODE;
    short BESTELL_VARIANTE;
    short E_MAIL;
    short ANZEIGE_NBG;
    short PUPRODUCTGROUPID;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of PUSUPPLIER ******************************************/

#if defined (BUF_DESC)
static struct buf_desc PUSUPPLIER_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 15, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 7, 0 },
   { TYP_C, 10, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 8, 0 },
   { TYP_C, 8, 0 },
   { TYP_C, 10, 0 },
   { TYP_C, 15, 0 },
   { TYP_C, 15, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 8, 0 },
   { TYP_C, 3, 0 },
   { TYP_C, 10, 0 },
   { TYP_C, 240, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 13, 0 },
   { TYP_C, 13, 0 },
   { TYP_C, 9, 0 },
   { TYP_C, 5, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 120, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc PUSUPPLIER_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 15, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 7, 0 },
   { TYP_C, 10, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 8, 0 },
   { TYP_C, 8, 0 },
   { TYP_C, 10, 0 },
   { TYP_C, 15, 0 },
   { TYP_C, 15, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 8, 0 },
   { TYP_C, 3, 0 },
   { TYP_C, 10, 0 },
   { TYP_C, 240, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 13, 0 },
   { TYP_C, 13, 0 },
   { TYP_C, 9, 0 },
   { TYP_C, 5, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 120, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* description for datatypes of PUSUPPLIER ************************************/

 #define PUSUPPLIER_S390 \
         long BESLA_NR; \
         long LANT_NR; \
         char BESLA_MC[16]; \
         char BESLA_NAME[31]; \
         char ANREDE[7]; \
         char ANREDE_2[7]; \
         char TITEL[31]; \
         char VORNAME[31]; \
         char NAME[31]; \
         char STRASSE[31]; \
         char PLZ_STRASSE[8]; \
         char POSTFACH[11]; \
         char ORT[31]; \
         char ABTEILUNG[31]; \
         char MAILNR_1[9]; \
         char MAILNR_2[9]; \
         char VORWAHL[11]; \
         char TELEFON[16]; \
         char TELEFAX[16]; \
         char SONDERBESTELL; \
         char PHOENIX_OHNE; \
         char AUSTAUSCH_GESPERRT; \
         char PREIS_BASIS; \
         long VERZ_TAGE; \
         long MAX_ZEILEN; \
         long DATUM_ANLAGE; \
         char SONDERLIEFERANT; \
         long DATUM_AENDER; \
         long DATUM_LOESCH; \
         char BEARBEITER[9]; \
         char LANDESKUERZEL[4]; \
         char VORWAHL_FAX[11]; \
         char BEMERKUNGEN[241]; \
         char BESTELLADRESSEPPE; \
         char MANDATSLAGER; \
         short FILIALNRMANDAT_LAG; \
         char ZWISCHENLIEFER; \
         char LIEFERSPEZIAL; \
         long BGA_NR; \
         long LIEFER_BESLA_NR; \
         char EAN1[14]; \
         char EAN2[14]; \
         char SIREN_CODE[10]; \
         char SIRET_CODE[6]; \
         short BESTELL_VARIANTE; \
         char E_MAIL[121]; \
         char ANZEIGE_NBG; \
         short PUPRODUCTGROUPID; \



/* Copy-Function Struct to single Data PUSUPPLIER *****************************/

 #define PUSUPPLIER_S390_COPY_TO_SINGLE(_x_) \
         BESLA_NR=_x_->BESLA_NR;\
         LANT_NR=_x_->LANT_NR;\
          strcpy(BESLA_MC,_x_->BESLA_MC);\
          strcpy(BESLA_NAME,_x_->BESLA_NAME);\
          strcpy(ANREDE,_x_->ANREDE);\
          strcpy(ANREDE_2,_x_->ANREDE_2);\
          strcpy(TITEL,_x_->TITEL);\
          strcpy(VORNAME,_x_->VORNAME);\
          strcpy(NAME,_x_->NAME);\
          strcpy(STRASSE,_x_->STRASSE);\
          strcpy(PLZ_STRASSE,_x_->PLZ_STRASSE);\
          strcpy(POSTFACH,_x_->POSTFACH);\
          strcpy(ORT,_x_->ORT);\
          strcpy(ABTEILUNG,_x_->ABTEILUNG);\
          strcpy(MAILNR_1,_x_->MAILNR_1);\
          strcpy(MAILNR_2,_x_->MAILNR_2);\
          strcpy(VORWAHL,_x_->VORWAHL);\
          strcpy(TELEFON,_x_->TELEFON);\
          strcpy(TELEFAX,_x_->TELEFAX);\
         SONDERBESTELL=_x_->SONDERBESTELL;\
         PHOENIX_OHNE=_x_->PHOENIX_OHNE;\
         AUSTAUSCH_GESPERRT=_x_->AUSTAUSCH_GESPERRT;\
         PREIS_BASIS=_x_->PREIS_BASIS;\
         VERZ_TAGE=_x_->VERZ_TAGE;\
         MAX_ZEILEN=_x_->MAX_ZEILEN;\
         DATUM_ANLAGE=_x_->DATUM_ANLAGE;\
         SONDERLIEFERANT=_x_->SONDERLIEFERANT;\
         DATUM_AENDER=_x_->DATUM_AENDER;\
         DATUM_LOESCH=_x_->DATUM_LOESCH;\
          strcpy(BEARBEITER,_x_->BEARBEITER);\
          strcpy(LANDESKUERZEL,_x_->LANDESKUERZEL);\
          strcpy(VORWAHL_FAX,_x_->VORWAHL_FAX);\
          strcpy(BEMERKUNGEN,_x_->BEMERKUNGEN);\
         BESTELLADRESSEPPE=_x_->BESTELLADRESSEPPE;\
         MANDATSLAGER=_x_->MANDATSLAGER;\
         FILIALNRMANDAT_LAG=_x_->FILIALNRMANDAT_LAG;\
         ZWISCHENLIEFER=_x_->ZWISCHENLIEFER;\
         LIEFERSPEZIAL=_x_->LIEFERSPEZIAL;\
         BGA_NR=_x_->BGA_NR;\
         LIEFER_BESLA_NR=_x_->LIEFER_BESLA_NR;\
          strcpy(EAN1,_x_->EAN1);\
          strcpy(EAN2,_x_->EAN2);\
          strcpy(SIREN_CODE,_x_->SIREN_CODE);\
          strcpy(SIRET_CODE,_x_->SIRET_CODE);\
         BESTELL_VARIANTE=_x_->BESTELL_VARIANTE;\
          strcpy(E_MAIL,_x_->E_MAIL);\
         ANZEIGE_NBG=_x_->ANZEIGE_NBG;\
         PUPRODUCTGROUPID=_x_->PUPRODUCTGROUPID;\

 #define PUSUPPLIER_S390_COPY_TO_STRUCT(_x_) \
          _x_->BESLA_NR=BESLA_NR;\
          _x_->LANT_NR=LANT_NR;\
          strcpy(_x_->BESLA_MC,BESLA_MC);\
          strcpy(_x_->BESLA_NAME,BESLA_NAME);\
          strcpy(_x_->ANREDE,ANREDE);\
          strcpy(_x_->ANREDE_2,ANREDE_2);\
          strcpy(_x_->TITEL,TITEL);\
          strcpy(_x_->VORNAME,VORNAME);\
          strcpy(_x_->NAME,NAME);\
          strcpy(_x_->STRASSE,STRASSE);\
          strcpy(_x_->PLZ_STRASSE,PLZ_STRASSE);\
          strcpy(_x_->POSTFACH,POSTFACH);\
          strcpy(_x_->ORT,ORT);\
          strcpy(_x_->ABTEILUNG,ABTEILUNG);\
          strcpy(_x_->MAILNR_1,MAILNR_1);\
          strcpy(_x_->MAILNR_2,MAILNR_2);\
          strcpy(_x_->VORWAHL,VORWAHL);\
          strcpy(_x_->TELEFON,TELEFON);\
          strcpy(_x_->TELEFAX,TELEFAX);\
          _x_->SONDERBESTELL=SONDERBESTELL;\
          _x_->PHOENIX_OHNE=PHOENIX_OHNE;\
          _x_->AUSTAUSCH_GESPERRT=AUSTAUSCH_GESPERRT;\
          _x_->PREIS_BASIS=PREIS_BASIS;\
          _x_->VERZ_TAGE=VERZ_TAGE;\
          _x_->MAX_ZEILEN=MAX_ZEILEN;\
          _x_->DATUM_ANLAGE=DATUM_ANLAGE;\
          _x_->SONDERLIEFERANT=SONDERLIEFERANT;\
          _x_->DATUM_AENDER=DATUM_AENDER;\
          _x_->DATUM_LOESCH=DATUM_LOESCH;\
          strcpy(_x_->BEARBEITER,BEARBEITER);\
          strcpy(_x_->LANDESKUERZEL,LANDESKUERZEL);\
          strcpy(_x_->VORWAHL_FAX,VORWAHL_FAX);\
          strcpy(_x_->BEMERKUNGEN,BEMERKUNGEN);\
          _x_->BESTELLADRESSEPPE=BESTELLADRESSEPPE;\
          _x_->MANDATSLAGER=MANDATSLAGER;\
          _x_->FILIALNRMANDAT_LAG=FILIALNRMANDAT_LAG;\
          _x_->ZWISCHENLIEFER=ZWISCHENLIEFER;\
          _x_->LIEFERSPEZIAL=LIEFERSPEZIAL;\
          _x_->BGA_NR=BGA_NR;\
          _x_->LIEFER_BESLA_NR=LIEFER_BESLA_NR;\
          strcpy(_x_->EAN1,EAN1);\
          strcpy(_x_->EAN2,EAN2);\
          strcpy(_x_->SIREN_CODE,SIREN_CODE);\
          strcpy(_x_->SIRET_CODE,SIRET_CODE);\
          _x_->BESTELL_VARIANTE=BESTELL_VARIANTE;\
          strcpy(_x_->E_MAIL,E_MAIL);\
          _x_->ANZEIGE_NBG=ANZEIGE_NBG;\
          _x_->PUPRODUCTGROUPID=PUPRODUCTGROUPID;\



/* FunctionNumber-Define of pusupplier ****************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of pusupplier ************************************/


#endif

/* C++ Class ******************************************************************/

#ifdef TRANSCLASS

#include<vector>
using namespace std;

/* ppunixc */
#include <sockclient.h>
#include <ppstring.h>
#include <ppgeneric.h>

/* must be implemented */
void FehlerBehandlung(int rc, const char * const error_msg);

#ifndef __VIRTUAL_DADE_CLASS__
#define __VIRTUAL_DADE_CLASS__

class ppDadeVirtual {
public:
    virtual    ~ppDadeVirtual() {};
    virtual int SelList      (int FetchRel = 1, int pos = 0) = 0;
    virtual int SelListHist  (int FetchRel = 1, int pos = 0) = 0;
    virtual int SelListFuture(int FetchRel = 1, int pos = 0) = 0;
    virtual int Load         (int pos = 0                  ) = 0;
    virtual int Delete       (int pos = 0                  ) = 0;
    virtual int Save         (int pos = 0                  ) = 0;
};
#endif

class CPUSUPPLIER : public ppDadeVirtual {
public:
    pusupplierS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<pusupplierS> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< pusupplierS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     pusupplierS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< pusupplierS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<pusupplierS>::iterator
                 beginList() { return lst.begin(); }
    vector<pusupplierS>::iterator
                 endList  () { return lst.end  (); }

    long         GetBesla_nr() const { return s.BESLA_NR; }
    long         GetLant_nr() const { return s.LANT_NR; }
    const char*  GetBesla_mc(ppString & t) const { t = s.BESLA_MC; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetBesla_name(ppString & t) const { t = s.BESLA_NAME; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetAnrede(ppString & t) const { t = s.ANREDE; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetAnrede_2(ppString & t) const { t = s.ANREDE_2; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetTitel(ppString & t) const { t = s.TITEL; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetVorname(ppString & t) const { t = s.VORNAME; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetName(ppString & t) const { t = s.NAME; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetStrasse(ppString & t) const { t = s.STRASSE; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetPlz_strasse(ppString & t) const { t = s.PLZ_STRASSE; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetPostfach(ppString & t) const { t = s.POSTFACH; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetOrt(ppString & t) const { t = s.ORT; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetAbteilung(ppString & t) const { t = s.ABTEILUNG; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetMailnr_1(ppString & t) const { t = s.MAILNR_1; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetMailnr_2(ppString & t) const { t = s.MAILNR_2; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetVorwahl(ppString & t) const { t = s.VORWAHL; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetTelefon(ppString & t) const { t = s.TELEFON; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetTelefax(ppString & t) const { t = s.TELEFAX; t.erasespace(ppString::END); return t.c_str(); }
    char         GetSonderbestell() const { return s.SONDERBESTELL[0]; }
    char         GetPhoenix_ohne() const { return s.PHOENIX_OHNE[0]; }
    char         GetAustausch_gesperrt() const { return s.AUSTAUSCH_GESPERRT[0]; }
    char         GetPreis_basis() const { return s.PREIS_BASIS[0]; }
    long         GetVerz_tage() const { return s.VERZ_TAGE; }
    long         GetMax_zeilen() const { return s.MAX_ZEILEN; }
    long         GetDatum_anlage() const { return s.DATUM_ANLAGE; }
    char         GetSonderlieferant() const { return s.SONDERLIEFERANT[0]; }
    long         GetDatum_aender() const { return s.DATUM_AENDER; }
    long         GetDatum_loesch() const { return s.DATUM_LOESCH; }
    const char*  GetBearbeiter(ppString & t) const { t = s.BEARBEITER; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetLandeskuerzel(ppString & t) const { t = s.LANDESKUERZEL; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetVorwahl_fax(ppString & t) const { t = s.VORWAHL_FAX; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetBemerkungen(ppString & t) const { t = s.BEMERKUNGEN; t.erasespace(ppString::END); return t.c_str(); }
    char         GetBestelladresseppe() const { return s.BESTELLADRESSEPPE[0]; }
    char         GetMandatslager() const { return s.MANDATSLAGER[0]; }
    short        GetFilialnrmandat_lag() const { return s.FILIALNRMANDAT_LAG; }
    char         GetZwischenliefer() const { return s.ZWISCHENLIEFER[0]; }
    char         GetLieferspezial() const { return s.LIEFERSPEZIAL[0]; }
    long         GetBga_nr() const { return s.BGA_NR; }
    long         GetLiefer_besla_nr() const { return s.LIEFER_BESLA_NR; }
    const char*  GetEan1(ppString & t) const { t = s.EAN1; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetEan2(ppString & t) const { t = s.EAN2; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetSiren_code(ppString & t) const { t = s.SIREN_CODE; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetSiret_code(ppString & t) const { t = s.SIRET_CODE; t.erasespace(ppString::END); return t.c_str(); }
    short        GetBestell_variante() const { return s.BESTELL_VARIANTE; }
    const char*  GetE_mail(ppString & t) const { t = s.E_MAIL; t.erasespace(ppString::END); return t.c_str(); }
    char         GetAnzeige_nbg() const { return s.ANZEIGE_NBG[0]; }
    short        GetPuproductgroupid() const { return s.PUPRODUCTGROUPID; }

    const pusupplierS &
                 GetStruct() const { return s; }
    void         SetBesla_nr(long t) { s.BESLA_NR = t; }
    void         SetLant_nr(long t) { s.LANT_NR = t; }
    void         SetBesla_mc(const ppString & t) { ppGStrCopy(s.BESLA_MC, t.c_str(), L_PUSUPPLIER_BESLA_MC); }
    void         SetBesla_name(const ppString & t) { ppGStrCopy(s.BESLA_NAME, t.c_str(), L_PUSUPPLIER_BESLA_NAME); }
    void         SetAnrede(const ppString & t) { ppGStrCopy(s.ANREDE, t.c_str(), L_PUSUPPLIER_ANREDE); }
    void         SetAnrede_2(const ppString & t) { ppGStrCopy(s.ANREDE_2, t.c_str(), L_PUSUPPLIER_ANREDE_2); }
    void         SetTitel(const ppString & t) { ppGStrCopy(s.TITEL, t.c_str(), L_PUSUPPLIER_TITEL); }
    void         SetVorname(const ppString & t) { ppGStrCopy(s.VORNAME, t.c_str(), L_PUSUPPLIER_VORNAME); }
    void         SetName(const ppString & t) { ppGStrCopy(s.NAME, t.c_str(), L_PUSUPPLIER_NAME); }
    void         SetStrasse(const ppString & t) { ppGStrCopy(s.STRASSE, t.c_str(), L_PUSUPPLIER_STRASSE); }
    void         SetPlz_strasse(const ppString & t) { ppGStrCopy(s.PLZ_STRASSE, t.c_str(), L_PUSUPPLIER_PLZ_STRASSE); }
    void         SetPostfach(const ppString & t) { ppGStrCopy(s.POSTFACH, t.c_str(), L_PUSUPPLIER_POSTFACH); }
    void         SetOrt(const ppString & t) { ppGStrCopy(s.ORT, t.c_str(), L_PUSUPPLIER_ORT); }
    void         SetAbteilung(const ppString & t) { ppGStrCopy(s.ABTEILUNG, t.c_str(), L_PUSUPPLIER_ABTEILUNG); }
    void         SetMailnr_1(const ppString & t) { ppGStrCopy(s.MAILNR_1, t.c_str(), L_PUSUPPLIER_MAILNR_1); }
    void         SetMailnr_2(const ppString & t) { ppGStrCopy(s.MAILNR_2, t.c_str(), L_PUSUPPLIER_MAILNR_2); }
    void         SetVorwahl(const ppString & t) { ppGStrCopy(s.VORWAHL, t.c_str(), L_PUSUPPLIER_VORWAHL); }
    void         SetTelefon(const ppString & t) { ppGStrCopy(s.TELEFON, t.c_str(), L_PUSUPPLIER_TELEFON); }
    void         SetTelefax(const ppString & t) { ppGStrCopy(s.TELEFAX, t.c_str(), L_PUSUPPLIER_TELEFAX); }
    void         SetSonderbestell(char t) { s.SONDERBESTELL[0] = t; s.SONDERBESTELL[1] = '\0';}
    void         SetPhoenix_ohne(char t) { s.PHOENIX_OHNE[0] = t; s.PHOENIX_OHNE[1] = '\0';}
    void         SetAustausch_gesperrt(char t) { s.AUSTAUSCH_GESPERRT[0] = t; s.AUSTAUSCH_GESPERRT[1] = '\0';}
    void         SetPreis_basis(char t) { s.PREIS_BASIS[0] = t; s.PREIS_BASIS[1] = '\0';}
    void         SetVerz_tage(long t) { s.VERZ_TAGE = t; }
    void         SetMax_zeilen(long t) { s.MAX_ZEILEN = t; }
    void         SetDatum_anlage(long t) { s.DATUM_ANLAGE = t; }
    void         SetSonderlieferant(char t) { s.SONDERLIEFERANT[0] = t; s.SONDERLIEFERANT[1] = '\0';}
    void         SetDatum_aender(long t) { s.DATUM_AENDER = t; }
    void         SetDatum_loesch(long t) { s.DATUM_LOESCH = t; }
    void         SetBearbeiter(const ppString & t) { ppGStrCopy(s.BEARBEITER, t.c_str(), L_PUSUPPLIER_BEARBEITER); }
    void         SetLandeskuerzel(const ppString & t) { ppGStrCopy(s.LANDESKUERZEL, t.c_str(), L_PUSUPPLIER_LANDESKUERZEL); }
    void         SetVorwahl_fax(const ppString & t) { ppGStrCopy(s.VORWAHL_FAX, t.c_str(), L_PUSUPPLIER_VORWAHL_FAX); }
    void         SetBemerkungen(const ppString & t) { ppGStrCopy(s.BEMERKUNGEN, t.c_str(), L_PUSUPPLIER_BEMERKUNGEN); }
    void         SetBestelladresseppe(char t) { s.BESTELLADRESSEPPE[0] = t; s.BESTELLADRESSEPPE[1] = '\0';}
    void         SetMandatslager(char t) { s.MANDATSLAGER[0] = t; s.MANDATSLAGER[1] = '\0';}
    void         SetFilialnrmandat_lag(short t) { s.FILIALNRMANDAT_LAG = t; }
    void         SetZwischenliefer(char t) { s.ZWISCHENLIEFER[0] = t; s.ZWISCHENLIEFER[1] = '\0';}
    void         SetLieferspezial(char t) { s.LIEFERSPEZIAL[0] = t; s.LIEFERSPEZIAL[1] = '\0';}
    void         SetBga_nr(long t) { s.BGA_NR = t; }
    void         SetLiefer_besla_nr(long t) { s.LIEFER_BESLA_NR = t; }
    void         SetEan1(const ppString & t) { ppGStrCopy(s.EAN1, t.c_str(), L_PUSUPPLIER_EAN1); }
    void         SetEan2(const ppString & t) { ppGStrCopy(s.EAN2, t.c_str(), L_PUSUPPLIER_EAN2); }
    void         SetSiren_code(const ppString & t) { ppGStrCopy(s.SIREN_CODE, t.c_str(), L_PUSUPPLIER_SIREN_CODE); }
    void         SetSiret_code(const ppString & t) { ppGStrCopy(s.SIRET_CODE, t.c_str(), L_PUSUPPLIER_SIRET_CODE); }
    void         SetBestell_variante(short t) { s.BESTELL_VARIANTE = t; }
    void         SetE_mail(const ppString & t) { ppGStrCopy(s.E_MAIL, t.c_str(), L_PUSUPPLIER_E_MAIL); }
    void         SetAnzeige_nbg(char t) { s.ANZEIGE_NBG[0] = t; s.ANZEIGE_NBG[1] = '\0';}
    void         SetPuproductgroupid(short t) { s.PUPRODUCTGROUPID = t; }

    void         SetStruct(const pusupplierS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CPUSUPPLIER() {
        ::buf_default((void *)&s, PUSUPPLIER_BES, PUSUPPLIER_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CPUSUPPLIER() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, PUSUPPLIER_BES, PUSUPPLIER_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, PUSUPPLIER_BES, (int)PUSUPPLIER_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, PUSUPPLIER_BES, (int)PUSUPPLIER_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_PUSUPPLIER & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.BESLA_MC);
        ppGStripLast(d.BESLA_NAME);
        ppGStripLast(d.ANREDE);
        ppGStripLast(d.ANREDE_2);
        ppGStripLast(d.TITEL);
        ppGStripLast(d.VORNAME);
        ppGStripLast(d.NAME);
        ppGStripLast(d.STRASSE);
        ppGStripLast(d.PLZ_STRASSE);
        ppGStripLast(d.POSTFACH);
        ppGStripLast(d.ORT);
        ppGStripLast(d.ABTEILUNG);
        ppGStripLast(d.MAILNR_1);
        ppGStripLast(d.MAILNR_2);
        ppGStripLast(d.VORWAHL);
        ppGStripLast(d.TELEFON);
        ppGStripLast(d.TELEFAX);
        ppGStripLast(d.BEARBEITER);
        ppGStripLast(d.LANDESKUERZEL);
        ppGStripLast(d.VORWAHL_FAX);
        ppGStripLast(d.BEMERKUNGEN);
        ppGStripLast(d.EAN1);
        ppGStripLast(d.EAN2);
        ppGStripLast(d.SIREN_CODE);
        ppGStripLast(d.SIRET_CODE);
        ppGStripLast(d.E_MAIL);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, PUSUPPLIER_BES, (int)PUSUPPLIER_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};
#endif    // TRANSCLASS
/* CreateSqlStatement of PUSUPPLIER *******************************************/

 #define PUSUPPLIER_CREATE(x) EXEC SQL create table x (\
         BESLA_NR integer default 0 not null,\
         LANT_NR integer default 0 not null,\
         BESLA_MC char(15) default " " not null,\
         BESLA_NAME char(30) default " " not null,\
         ANREDE char(6) default " " not null,\
         ANREDE_2 char(6) default " " not null,\
         TITEL char(30) default " " not null,\
         VORNAME char(30) default " " not null,\
         NAME char(30) default " " not null,\
         STRASSE char(30) default " " not null,\
         PLZ_STRASSE char(7) default " " not null,\
         POSTFACH char(10) default " " not null,\
         ORT char(30) default " " not null,\
         ABTEILUNG char(30) default " " not null,\
         MAILNR_1 char(8) default " " not null,\
         MAILNR_2 char(8) default " " not null,\
         VORWAHL char(10) default " " not null,\
         TELEFON char(15) default " " not null,\
         TELEFAX char(15) default " " not null,\
         SONDERBESTELL char(1) default " " not null,\
         PHOENIX_OHNE char(1) default " " not null,\
         AUSTAUSCH_GESPERRT char(1) default " " not null,\
         PREIS_BASIS char(1) default " " not null,\
         VERZ_TAGE integer default 0 not null,\
         MAX_ZEILEN integer default 0 not null,\
         DATUM_ANLAGE integer default 0 not null,\
         SONDERLIEFERANT char(1) default " " not null,\
         DATUM_AENDER integer default 0 not null,\
         DATUM_LOESCH integer default 0 not null,\
         BEARBEITER char(8) default " " not null,\
         LANDESKUERZEL char(3) default " " not null,\
         VORWAHL_FAX char(10) default " " not null,\
         BEMERKUNGEN varchar(240,0) default " " not null,\
         BESTELLADRESSEPPE char(1) default " " not null,\
         MANDATSLAGER char(1) default " " not null,\
         FILIALNRMANDAT_LAG smallint default 0 not null,\
         ZWISCHENLIEFER char(1) default " " not null,\
         LIEFERSPEZIAL char(1) default " " not null,\
         BGA_NR integer default 0 not null,\
         LIEFER_BESLA_NR integer default 0 not null,\
         EAN1 char(13) default " " not null,\
         EAN2 char(13) default " " not null,\
         SIREN_CODE char(9) default " " not null,\
         SIRET_CODE char(5) default " " not null,\
         BESTELL_VARIANTE smallint default 0 not null,\
         E_MAIL char(120) default " " not null,\
         ANZEIGE_NBG char(1) default " " not null,\
         PUPRODUCTGROUPID smallint default 0 not null) extent size 96 next size 12 lock mode row;



/* CreateIndexStatement of PUSUPPLIER *****************************************/

 #define PUSUPPLIER_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_pusupplier_1 on _X_(\
              besla_nr );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index i_pusupplier_2 on _X_(\
              besla_mc );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index i_pusupplier_3 on _X_(\
              lant_nr );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of PUSUPPLIER *****************************************/

 #define PUSUPPLIER_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_pusupplier_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_pusupplier_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_pusupplier_3;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
