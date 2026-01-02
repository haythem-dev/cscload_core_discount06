/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_ARTIKELLOKAL_FILIALNR             6
 #define L_ARTIKELLOKAL_ARTIKEL_NR           11
 #define L_ARTIKELLOKAL_BESTAND              11
 #define L_ARTIKELLOKAL_NACHFRAGE            11
 #define L_ARTIKELLOKAL_ZUZAHLUNG            1
 #define L_ARTIKELLOKAL_RABATTFAEHIG         2
 #define L_ARTIKELLOKAL_NATRASTAFFELNR       11
 #define L_ARTIKELLOKAL_PRISOART             1
 #define L_ARTIKELLOKAL_ARTIKELAKTIV         1
 #define L_ARTIKELLOKAL_LAGERBEREICHNR       6
 #define L_ARTIKELLOKAL_STATIONNR            2
 #define L_ARTIKELLOKAL_LAGERFACHNR          10
 #define L_ARTIKELLOKAL_VERBUNDARTIKEL       1
 #define L_ARTIKELLOKAL_ETARTSCHALTER1       11
 #define L_ARTIKELLOKAL_ETARTSCHALTER2       11
 #define L_ARTIKELLOKAL_ETARTSCHALTER3       11
 #define L_ARTIKELLOKAL_ETARTSCHALTER4       11
 #define L_ARTIKELLOKAL_ETARTSCHALTER5       11
 #define L_ARTIKELLOKAL_VERKAUFEINHEIT       11
 #define L_ARTIKELLOKAL_CONTAINERGROESSE     11
 #define L_ARTIKELLOKAL_KONTIGENTMENGE       6
 #define L_ARTIKELLOKAL_CHARGENARTIKEL       1
 #define L_ARTIKELLOKAL_TEXTKEY              6
 #define L_ARTIKELLOKAL_BESTANDRESERVIERT    11
 #define L_ARTIKELLOKAL_WAFOTYP              1
 #define L_ARTIKELLOKAL_KZRANGE              1
 #define L_ARTIKELLOKAL_MORECONDITIONS        1
 #define L_ARTIKELLOKAL_BESTANDTAGESANFANG   11
 #define L_ARTIKELLOKAL_CODEBLOCAGE          1
 #define L_ARTIKELLOKAL_BLOCKEDFORRETURNS    6


 #define L_ARTIKELLOKAL_PKEY 0

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define ARTIKELLOKAL_ANZ ( sizeof(ARTIKELLOKAL_BES) / sizeof(struct buf_desc) )
#endif
 #define G_ARTIKELLOKAL sizeof(struct ARTIKELLOKAL)


 #define ARTIKELLOKAL_H

 #define ARTIKELLOKAL_LISTE \
 			ARTIKELLOKAL.FILIALNR, \
 			ARTIKELLOKAL.ARTIKEL_NR, \
 			ARTIKELLOKAL.BESTAND, \
 			ARTIKELLOKAL.NACHFRAGE, \
 			ARTIKELLOKAL.ZUZAHLUNG, \
 			ARTIKELLOKAL.RABATTFAEHIG, \
 			ARTIKELLOKAL.NATRASTAFFELNR, \
 			ARTIKELLOKAL.PRISOART, \
 			ARTIKELLOKAL.ARTIKELAKTIV, \
 			ARTIKELLOKAL.LAGERBEREICHNR, \
 			ARTIKELLOKAL.STATIONNR, \
 			ARTIKELLOKAL.LAGERFACHNR, \
 			ARTIKELLOKAL.VERBUNDARTIKEL, \
 			ARTIKELLOKAL.ETARTSCHALTER1, \
 			ARTIKELLOKAL.ETARTSCHALTER2, \
 			ARTIKELLOKAL.ETARTSCHALTER3, \
 			ARTIKELLOKAL.ETARTSCHALTER4, \
 			ARTIKELLOKAL.ETARTSCHALTER5, \
 			ARTIKELLOKAL.VERKAUFEINHEIT, \
 			ARTIKELLOKAL.CONTAINERGROESSE, \
 			ARTIKELLOKAL.KONTIGENTMENGE, \
 			ARTIKELLOKAL.CHARGENARTIKEL, \
			ARTIKELLOKAL.TEXTKEY, \
			ARTIKELLOKAL.BESTANDRESERVIERT, \
			ARTIKELLOKAL.WAFOTYP, \
			ARTIKELLOKAL.KZRANGE, \
			ARTIKELLOKAL.MORECONDITIONS, \
			ARTIKELLOKAL.BESTANDTAGESANFANG, \
			ARTIKELLOKAL.CODEBLOCAGE, \
			ARTIKELLOKAL.BLOCKEDFORRETURNS

#define ARTIKELLOKAL_PLISTE \
 			"ARTIKELLOKAL.FILIALNR," \
 			"ARTIKELLOKAL.ARTIKEL_NR," \
 			"ARTIKELLOKAL.BESTAND," \
 			"ARTIKELLOKAL.NACHFRAGE," \
 			"ARTIKELLOKAL.ZUZAHLUNG," \
 			"ARTIKELLOKAL.RABATTFAEHIG," \
 			"ARTIKELLOKAL.NATRASTAFFELNR," \
 			"ARTIKELLOKAL.PRISOART," \
 			"ARTIKELLOKAL.ARTIKELAKTIV," \
 			"ARTIKELLOKAL.LAGERBEREICHNR," \
 			"ARTIKELLOKAL.STATIONNR," \
 			"ARTIKELLOKAL.LAGERFACHNR," \
 			"ARTIKELLOKAL.VERBUNDARTIKEL," \
 			"ARTIKELLOKAL.ETARTSCHALTER1," \
 			"ARTIKELLOKAL.ETARTSCHALTER2," \
 			"ARTIKELLOKAL.ETARTSCHALTER3," \
 			"ARTIKELLOKAL.ETARTSCHALTER4," \
 			"ARTIKELLOKAL.ETARTSCHALTER5," \
 			"ARTIKELLOKAL.VERKAUFEINHEIT," \
 			"ARTIKELLOKAL.CONTAINERGROESSE," \
 			"ARTIKELLOKAL.KONTIGENTMENGE," \
 			"ARTIKELLOKAL.CHARGENARTIKEL," \
			"ARTIKELLOKAL.TEXTKEY," \
			"ARTIKELLOKAL.BESTANDRESERVIERT," \
			"ARTIKELLOKAL.WAFOTYP," \
			"ARTIKELLOKAL.KZRANGE," \
			"ARTIKELLOKAL.MORECONDITIONS," \
			"ARTIKELLOKAL.BESTANDTAGESANFANG," \
			"ARTIKELLOKAL.CODEBLOCAGE," \
			"ARTIKELLOKAL.BLOCKEDFORRETURNS "

 #define ARTIKELLOKAL_PELISTE_ALL \
 			"FILIALNR," \
 			"ARTIKEL_NR," \
 			"BESTAND," \
 			"NACHFRAGE," \
 			"ZUZAHLUNG," \
 			"RABATTFAEHIG," \
 			"NATRASTAFFELNR," \
 			"PRISOART," \
 			"ARTIKELAKTIV," \
 			"LAGERBEREICHNR," \
 			"STATIONNR," \
 			"LAGERFACHNR," \
 			"VERBUNDARTIKEL," \
 			"ETARTSCHALTER1," \
 			"ETARTSCHALTER2," \
 			"ETARTSCHALTER3," \
 			"ETARTSCHALTER4," \
 			"ETARTSCHALTER5," \
 			"VERKAUFEINHEIT," \
 			"CONTAINERGROESSE," \
 			"KONTIGENTMENGE," \
 			"CHARGENARTIKEL," \
			"TEXTKEY," \
			"BESTANDRESERVIERT," \
			"WAFOTYP," \
			"KZRANGE," \
			"MORECONDITIONS," \
			"BESTANDTAGESANFANG," \
			"CODEBLOCAGE," \
			"BLOCKEDFORRETURNS "

#define ARTIKELLOKAL_PELISTE \
 			"FILIALNR," \
 			"ARTIKEL_NR," \
 			"BESTAND," \
 			"NACHFRAGE," \
 			"ZUZAHLUNG," \
 			"RABATTFAEHIG," \
 			"NATRASTAFFELNR," \
 			"PRISOART," \
 			"ARTIKELAKTIV," \
 			"LAGERBEREICHNR," \
 			"STATIONNR," \
 			"LAGERFACHNR," \
 			"VERBUNDARTIKEL," \
 			"ETARTSCHALTER1," \
 			"ETARTSCHALTER2," \
 			"ETARTSCHALTER3," \
 			"ETARTSCHALTER4," \
 			"ETARTSCHALTER5," \
 			"VERKAUFEINHEIT," \
 			"CONTAINERGROESSE," \
 			"KONTIGENTMENGE," \
 			"CHARGENARTIKEL," \
			"TEXTKEY," \
			"BESTANDRESERVIERT," \
			"KZRANGE," \
			"MORECONDITIONS," \
			"BESTANDTAGESANFANG," \
			"CODEBLOCAGE," \
			"BLOCKEDFORRETURNS "

#define ARTIKELLOKAL_UPDLISTE_ALL \
 			"FILIALNR=?," \
 			"ARTIKEL_NR=?," \
 			"BESTAND=?," \
 			"NACHFRAGE=?," \
 			"ZUZAHLUNG=?," \
 			"RABATTFAEHIG=?," \
 			"NATRASTAFFELNR=?," \
 			"PRISOART=?," \
 			"ARTIKELAKTIV=?," \
 			"LAGERBEREICHNR=?," \
 			"STATIONNR=?," \
 			"LAGERFACHNR=?," \
 			"VERBUNDARTIKEL=?," \
 			"ETARTSCHALTER1=?," \
 			"ETARTSCHALTER2=?," \
 			"ETARTSCHALTER3=?," \
 			"ETARTSCHALTER4=?," \
 			"ETARTSCHALTER5=?," \
 			"VERKAUFEINHEIT=?," \
 			"CONTAINERGROESSE=?," \
 			"KONTIGENTMENGE=?," \
 			"CHARGENARTIKEL=?," \
			"TEXTKEY=?," \
			"BESTANDRESERVIERT=?," \
			"WAFOTYP=?," \
			"KZRANGE=?," \
			"MORECONDITIONS=?," \
			"BESTANDTAGESANFANG=?," \
			"CODEBLOCAGE=?," \
			"BLOCKEDFORRETURNS=? "

#define ARTIKELLOKAL_UPDLISTE \
 			"FILIALNR=?," \
 			"ARTIKEL_NR=?," \
 			"BESTAND=?," \
 			"NACHFRAGE=?," \
 			"ZUZAHLUNG=?," \
 			"RABATTFAEHIG=?," \
 			"NATRASTAFFELNR=?," \
 			"PRISOART=?," \
 			"ARTIKELAKTIV=?," \
 			"LAGERBEREICHNR=?," \
 			"STATIONNR=?," \
 			"LAGERFACHNR=?," \
 			"VERBUNDARTIKEL=?," \
 			"ETARTSCHALTER1=?," \
 			"ETARTSCHALTER2=?," \
 			"ETARTSCHALTER3=?," \
 			"ETARTSCHALTER4=?," \
 			"ETARTSCHALTER5=?," \
 			"VERKAUFEINHEIT=?," \
 			"CONTAINERGROESSE=?," \
 			"KONTIGENTMENGE=?," \
 			"CHARGENARTIKEL=?," \
			"TEXTKEY=?," \
			"BESTANDRESERVIERT=?," \
			"KZRANGE=?," \
			"MORECONDITIONS=?," \
			"BESTANDTAGESANFANG=?," \
			"CODEBLOCAGE=?," \
			"BLOCKEDFORRETURNS=? "

 #define ARTIKELLOKALFILIALNR                      0
 #define ARTIKELLOKALARTIKEL_NR                    1
 #define ARTIKELLOKALBESTAND                       2
 #define ARTIKELLOKALNACHFRAGE                     3
 #define ARTIKELLOKALZUZAHLUNG                     4
 #define ARTIKELLOKALRABATTFAEHIG                  5
 #define ARTIKELLOKALNATRASTAFFELNR                6
 #define ARTIKELLOKALPRISOART                      7
 #define ARTIKELLOKALARTIKELAKTIV                  8
 #define ARTIKELLOKALLAGERBEREICHNR                9
 #define ARTIKELLOKALSTATIONNR                     10
 #define ARTIKELLOKALLAGERFACHNR                   11
 #define ARTIKELLOKALVERBUNDARTIKEL                12
 #define ARTIKELLOKALETARTSCHALTER1                13
 #define ARTIKELLOKALETARTSCHALTER2                14
 #define ARTIKELLOKALETARTSCHALTER3                15
 #define ARTIKELLOKALETARTSCHALTER4                16
 #define ARTIKELLOKALETARTSCHALTER5                17
 #define ARTIKELLOKALVERKAUFEINHEIT                18
 #define ARTIKELLOKALCONTAINERGROESSE              19
 #define ARTIKELLOKALKONTIGENTMENGE                20
 #define ARTIKELLOKALCHARGENARTIKEL                21
 #define ARTIKELLOKALTEXTKEY                       22
 #define ARTIKELLOKALBESTANDRESERVIERT             23
 #define ARTIKELLOKALWAFOTYP                       24
 #define ARTIKELLOKALKZRANGE                       25
 #define ARTIKELLOKALMORECONDITIONS                26
 #define ARTIKELLOKALBESTANDTAGESANFANG            27
 #define ARTIKELLOKALCODEBLOCAGE                   28
 #define ARTIKELLOKALBLOCKEDFORRETURNS             29

 #define ARTIKELLOKAL_ZEIGER(xxx) \
 			:xxx->FILIALNR,\
 			:xxx->ARTIKEL_NR,\
 			:xxx->BESTAND,\
 			:xxx->NACHFRAGE,\
 			:xxx->ZUZAHLUNG,\
 			:xxx->RABATTFAEHIG,\
 			:xxx->NATRASTAFFELNR,\
 			:xxx->PRISOART,\
 			:xxx->ARTIKELAKTIV,\
 			:xxx->LAGERBEREICHNR,\
 			:xxx->STATIONNR,\
 			:xxx->LAGERFACHNR,\
 			:xxx->VERBUNDARTIKEL,\
 			:xxx->ETARTSCHALTER1,\
 			:xxx->ETARTSCHALTER2,\
 			:xxx->ETARTSCHALTER3,\
 			:xxx->ETARTSCHALTER4,\
 			:xxx->ETARTSCHALTER5,\
 			:xxx->VERKAUFEINHEIT,\
 			:xxx->CONTAINERGROESSE,\
 			:xxx->KONTIGENTMENGE,\
 			:xxx->CHARGENARTIKEL,\
			:xxx->TEXTKEY,\
			:xxx->BESTANDRESERVIERT,\
			:xxx->WAFOTYP,\
			:xxx->KZRANGE,\
			:xxx->MORECONDITIONS,\
			:xxx->BESTANDTAGESANFANG,\
			:xxx->CODEBLOCAGE,\
			:xxx->BLOCKEDFORRETURNS
#define ARTIKELLOKAL_UPDATE(xxx) \
 			FILIALNR = :xxx->FILIALNR,\
 			ARTIKEL_NR = :xxx->ARTIKEL_NR,\
 			BESTAND = :xxx->BESTAND,\
 			NACHFRAGE = :xxx->NACHFRAGE,\
 			ZUZAHLUNG = :xxx->ZUZAHLUNG,\
 			RABATTFAEHIG = :xxx->RABATTFAEHIG,\
 			NATRASTAFFELNR = :xxx->NATRASTAFFELNR,\
 			PRISOART = :xxx->PRISOART,\
 			ARTIKELAKTIV = :xxx->ARTIKELAKTIV,\
 			LAGERBEREICHNR = :xxx->LAGERBEREICHNR,\
 			STATIONNR = :xxx->STATIONNR,\
 			LAGERFACHNR = :xxx->LAGERFACHNR,\
 			VERBUNDARTIKEL = :xxx->VERBUNDARTIKEL,\
 			ETARTSCHALTER1 = :xxx->ETARTSCHALTER1,\
 			ETARTSCHALTER2 = :xxx->ETARTSCHALTER2,\
 			ETARTSCHALTER3 = :xxx->ETARTSCHALTER3,\
 			ETARTSCHALTER4 = :xxx->ETARTSCHALTER4,\
 			ETARTSCHALTER5 = :xxx->ETARTSCHALTER5,\
 			VERKAUFEINHEIT = :xxx->VERKAUFEINHEIT,\
 			CONTAINERGROESSE = :xxx->CONTAINERGROESSE,\
 			KONTIGENTMENGE = :xxx->KONTIGENTMENGE,\
 			CHARGENARTIKEL = :xxx->CHARGENARTIKEL,\
			TEXTKEY = :xxx->TEXTKEY,\
			BESTANDRESERVIERT = :xxx->BESTANDRESERVIERT,\
			WAFOTYP = :xxx->WAFOTYP,\
			KZRANGE = :xxx->KZRANGE,\
			MORECONDITIONS = :xxx->MORECONDITIONS,\
			BESTANDTAGESANFANG = :xxx->BESTANDTAGESANFANG,\
			CODEBLOCAGE = :xxx->CODEBLOCAGE,\ 
			BLOCKEDFORRETURNS = :xxx->BLOCKEDFORRETURNS

 #define LS_ARTIKELLOKAL_FILIALNR             7
 #define LS_ARTIKELLOKAL_ARTIKEL_NR           11
 #define LS_ARTIKELLOKAL_BESTAND              11
 #define LS_ARTIKELLOKAL_NACHFRAGE            11
 #define LS_ARTIKELLOKAL_ZUZAHLUNG            2
 #define LS_ARTIKELLOKAL_RABATTFAEHIG         3
 #define LS_ARTIKELLOKAL_NATRASTAFFELNR       11
 #define LS_ARTIKELLOKAL_PRISOART             2
 #define LS_ARTIKELLOKAL_ARTIKELAKTIV         2
 #define LS_ARTIKELLOKAL_LAGERBEREICHNR       7
 #define LS_ARTIKELLOKAL_STATIONNR            3
 #define LS_ARTIKELLOKAL_LAGERFACHNR          11
 #define LS_ARTIKELLOKAL_VERBUNDARTIKEL       2
 #define LS_ARTIKELLOKAL_ETARTSCHALTER1       11
 #define LS_ARTIKELLOKAL_ETARTSCHALTER2       11
 #define LS_ARTIKELLOKAL_ETARTSCHALTER3       11
 #define LS_ARTIKELLOKAL_ETARTSCHALTER4       11
 #define LS_ARTIKELLOKAL_ETARTSCHALTER5       11
 #define LS_ARTIKELLOKAL_VERKAUFEINHEIT       11
 #define LS_ARTIKELLOKAL_CONTAINERGROESSE     11
 #define LS_ARTIKELLOKAL_KONTIGENTMENGE       7
 #define LS_ARTIKELLOKAL_CHARGENARTIKEL       2
 #define LS_ARTIKELLOKAL_TEXTKEY              7
 #define LS_ARTIKELLOKAL_BESTANDRESERVIERT    11
 #define LS_ARTIKELLOKAL_WAFOTYP              2
 #define LS_ARTIKELLOKAL_KZRANGE              2
 #define LS_ARTIKELLOKAL_MORECONDITIONS        2
 #define LS_ARTIKELLOKAL_BESTANDTAGESANFANG   11
 #define LS_ARTIKELLOKAL_CODEBLOCAGE          2
 #define LS_ARTIKELLOKAL_BLOCKEDFORRETURNS    7

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct ARTIKELLOKAL {
		 short   FILIALNR;
		 long    ARTIKEL_NR;
		 long    BESTAND;
		 long    NACHFRAGE;
		 char    ZUZAHLUNG[1 + 1];
		 char    RABATTFAEHIG[2 + 1];
		 long    NATRASTAFFELNR;
		 char    PRISOART[1 + 1];
		 char    ARTIKELAKTIV[1 + 1];
		 short   LAGERBEREICHNR;
		 char    STATIONNR[2 + 1];
		 char    LAGERFACHNR[10 + 1];
		 char    VERBUNDARTIKEL[1 + 1];
		 long    ETARTSCHALTER1;
		 long    ETARTSCHALTER2;
		 long    ETARTSCHALTER3;
		 long    ETARTSCHALTER4;
		 long    ETARTSCHALTER5;
		 long    VERKAUFEINHEIT;
		 long    CONTAINERGROESSE;
		 short   KONTIGENTMENGE;
		 char    CHARGENARTIKEL[1 + 1];
		 short   TEXTKEY;
		 long    BESTANDRESERVIERT;
		 char    WAFOTYP[1 + 1];
		 char    KZRANGE[1 + 1];
		 char    MORECONDITIONS[1 + 1];
		 long    BESTANDTAGESANFANG;
		 char    CODEBLOCAGE[1 + 1];
		 short   BLOCKEDFORRETURNS;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_ARTIKELLOKAL {
		 short   FILIALNR;
		 long    ARTIKEL_NR;
		 long    BESTAND;
		 long    NACHFRAGE;
		 char    ZUZAHLUNG;
		 char    RABATTFAEHIG[2 + 1];
		 long    NATRASTAFFELNR;
		 char    PRISOART;
		 char    ARTIKELAKTIV;
		 short   LAGERBEREICHNR;
		 char    STATIONNR[2 + 1];
		 char    LAGERFACHNR[10 + 1];
		 char    VERBUNDARTIKEL;
		 long    ETARTSCHALTER1;
		 long    ETARTSCHALTER2;
		 long    ETARTSCHALTER3;
		 long    ETARTSCHALTER4;
		 long    ETARTSCHALTER5;
		 long    VERKAUFEINHEIT;
		 long    CONTAINERGROESSE;
		 short   KONTIGENTMENGE;
		 char    CHARGENARTIKEL;
		 short   TEXTKEY;
		 long    BESTANDRESERVIERT;
		 char    WAFOTYP;
		 char    KZRANGE;
		 char    MORECONDITIONS;
		 long    BESTANDTAGESANFANG;
		 char    CODEBLOCAGE;
		 short   BLOCKEDFORRETURNS;
 };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_ARTIKELLOKAL {
		 short  FILIALNR;
		 short  ARTIKEL_NR;
		 short  BESTAND;
		 short  NACHFRAGE;
		 short  ZUZAHLUNG;
		 short  RABATTFAEHIG;
		 short  NATRASTAFFELNR;
		 short  PRISOART;
		 short  ARTIKELAKTIV;
		 short  LAGERBEREICHNR;
		 short  STATIONNR;
		 short  LAGERFACHNR;
		 short  VERBUNDARTIKEL;
		 short  ETARTSCHALTER1;
		 short  ETARTSCHALTER2;
		 short  ETARTSCHALTER3;
		 short  ETARTSCHALTER4;
		 short  ETARTSCHALTER5;
		 short  VERKAUFEINHEIT;
		 short  CONTAINERGROESSE;
		 short  KONTIGENTMENGE;
		 short  CHARGENARTIKEL;
		 short  TEXTKEY;
		 short  BESTANDRESERVIERT;
		 short  WAFOTYP;
		 short  KZRANGE;
		 short  MORECONDITIONS;
		 short  BESTANDTAGESANFANG;
		 short  CODEBLOCAGE;
		 short  BLOCKEDFORRETURNS;
 };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_ARTIKELLOKAL {
		 char    FILIALNR[7];
		 char    ARTIKEL_NR[11];
		 char    BESTAND[11];
		 char    NACHFRAGE[11];
		 char    ZUZAHLUNG[1 + 1];
		 char    RABATTFAEHIG[2 + 1];
		 char    NATRASTAFFELNR[11];
		 char    PRISOART[1 + 1];
		 char    ARTIKELAKTIV[1 + 1];
		 char    LAGERBEREICHNR[7];
		 char    STATIONNR[2 + 1];
		 char    LAGERFACHNR[10 + 1];
		 char    VERBUNDARTIKEL[1 + 1];
		 char    ETARTSCHALTER1[11];
		 char    ETARTSCHALTER2[11];
		 char    ETARTSCHALTER3[11];
		 char    ETARTSCHALTER4[11];
		 char    ETARTSCHALTER5[11];
		 char    VERKAUFEINHEIT[11];
		 char    CONTAINERGROESSE[11];
		 char    KONTIGENTMENGE[7];
		 char    CHARGENARTIKEL[1 + 1];
		 char    TEXTKEY[7];
		 char    BESTANDRESERVIERT[11];
		 char    WAFOTYP[1 + 1];
		 char    KZRANGE[1 + 1];
		 char    MORECONDITIONS[1 + 1];
		 char    BESTANDTAGESANFANG[11];
		 char    CODEBLOCAGE[1 + 1];
		 char    BLOCKEDFORRETURNS[7];
 };

 struct O_ARTIKELLOKAL {
		 char    FILIALNR[7];
		 char    ARTIKEL_NR[11];
		 char    BESTAND[11];
		 char    NACHFRAGE[11];
		 char    ZUZAHLUNG[1];
		 char    RABATTFAEHIG[2];
		 char    NATRASTAFFELNR[11];
		 char    PRISOART[1];
		 char    ARTIKELAKTIV[1];
		 char    LAGERBEREICHNR[7];
		 char    STATIONNR[2];
		 char    LAGERFACHNR[10];
		 char    VERBUNDARTIKEL[1];
		 char    ETARTSCHALTER1[11];
		 char    ETARTSCHALTER2[11];
		 char    ETARTSCHALTER3[11];
		 char    ETARTSCHALTER4[11];
		 char    ETARTSCHALTER5[11];
		 char    VERKAUFEINHEIT[11];
		 char    CONTAINERGROESSE[11];
		 char    KONTIGENTMENGE[7];
		 char    CHARGENARTIKEL[1];
		 char    TEXTKEY[7];
		 char    BESTANDRESERVIERT[11];
		 char    WAFOTYP[1];
		 char    KZRANGE[1];
		 char    MORECONDITIONS[1];
		 char    BESTANDTAGESANFANG[11];
		 char    CODEBLOCAGE[1];
		 char    BLOCKEDFORRETURNS[7];
 };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc ARTIKELLOKAL_BES [] =
 {
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_S ,    6 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTIKELLOKAL_BES [] =
 {
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_C,    2 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_C,    2 ,   0 },
	 { TYP_C,   10 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_S,    5 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CARTIKELLOKAL
 {
  public:

  ARTIKELLOKAL s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, ARTIKELLOKAL_BES, ARTIKELLOKAL_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,ARTIKELLOKAL_BES, ARTIKELLOKAL_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,ARTIKELLOKAL_BES, ARTIKELLOKAL_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CARTIKELLOKAL()
  {
   ::buf_default((void *)&s, ARTIKELLOKAL_BES, ARTIKELLOKAL_ANZ);
  }
 };
#endif

#define ARTIKELLOKAL_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 FILIALNR           SMALLINT        default 0 NOT NULL,\
		 ARTIKEL_NR         INTEGER         default 0 NOT NULL,\
		 BESTAND            INTEGER         default 0 NOT NULL,\
		 NACHFRAGE          INTEGER         default 0 NOT NULL,\
		 ZUZAHLUNG          CHAR(1)         default " " NOT NULL,\
		 RABATTFAEHIG       CHAR(2)         default " " NOT NULL,\
		 NATRASTAFFELNR     INTEGER         default 0 NOT NULL,\
		 PRISOART           CHAR(1)         default " " NOT NULL,\
		 ARTIKELAKTIV       CHAR(1)         default " " NOT NULL,\
		 LAGERBEREICHNR     SMALLINT        default 0 NOT NULL,\
		 STATIONNR          CHAR(2)         default " " NOT NULL,\
		 LAGERFACHNR        CHAR(10)        default " " NOT NULL,\
		 VERBUNDARTIKEL     CHAR(1)         default " " NOT NULL,\
		 ETARTSCHALTER1     INTEGER         default 0 NOT NULL,\
		 ETARTSCHALTER2     INTEGER         default 0 NOT NULL,\
		 ETARTSCHALTER3     INTEGER         default 0 NOT NULL,\
		 ETARTSCHALTER4     INTEGER         default 0 NOT NULL,\
		 ETARTSCHALTER5     INTEGER         default 0 NOT NULL,\
		 VERKAUFEINHEIT     INTEGER         default 0 NOT NULL,\
		 CONTAINERGROESSE   INTEGER         default 0 NOT NULL,\
		 KONTIGENTMENGE     SMALLINT        default 0 NOT NULL,\
		 CHARGENARTIKEL     CHAR(1)         default 0 NOT NULL,\
		 TEXTKEY            SMALLINT        default 0 NOT NULL,\
		 BESTANDRESERVIERT  INTEGER         default 0 NOT NULL,\
		 WAFOTYP            CHAR(1)         default 0 NOT NULL,\
		 KZRANGE            CHAR(1)         default 0 NOT NULL,\
		 MORECONDITIONS      CHAR(1)         default 0 NOT NULL,\
		 BESTANDTAGESANFANG INTEGER         default 0 NOT NULL,\
		 CODEBLOCAGE            CHAR(1)         default 0 NOT NULL,\
		 BLOCKEDFORRETURNS		SMALLINT         default 0 NOT NULL  ) EXTENT SIZE 9 LOCK MODE ROW;

#define ARTIKELLOKAL_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX I_ARTIKELLOKAL_1   on yyy(  );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define ARTIKELLOKAL_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_ARTIKELLOKAL_1  ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

