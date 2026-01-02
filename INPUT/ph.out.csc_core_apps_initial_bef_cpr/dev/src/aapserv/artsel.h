/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/
#ifndef _ARTSEL_H
#define _ARTSEL_H

 #define L_ARTAESEL_ARTIKEL_NR           11
 #define L_ARTAESEL_ARTIKEL_MC           12
 #define L_ARTAESEL_PACKGROESSE          11
 #define L_ARTAESEL_DARREICHFORM         3
 #define L_ARTAESEL_EINHEIT              9
 #define L_ARTAESEL_ARTIKEL_NAME         30
 #define L_ARTAESEL_BESTAND              11
 #define L_ARTAESEL_PREISEKAPO           9
 #define N_ARTAESEL_PREISEKAPO           2
 #define L_ARTAESEL_DATUMVERFALL         11
 #define L_ARTAESEL_FILIALNR             6
 #define L_ARTAESEL_ETARTSCHALTER1       5
 #define L_ARTAESEL_ETARTSCHALTER3       5
 #define L_ARTAESEL_PRISOART             1
 #define L_ARTAESEL_ETARTSCHALTER2       5
 #define L_ARTAESEL_ETARTSCHALTER4       5
 #define L_ARTAESEL_ETARTSCHALTER5       5
 #define L_ARTAESEL_NORMPACKUNG          2
 #define L_ARTAESEL_ETARTKLASSE1         5
 #define L_ARTAESEL_CHARGENARTIKEL       1
 #define L_ARTAESEL_HERSTELLER_CODE      5
 #define L_ARTAESEL_WAFOTYP              1
 #define L_ARTAESEL_NATRASTAFFELNR       11
 #define L_ARTAESEL_TEXT				 240
 #define L_ARTAESEL_TEXTKEY_HOSPITAL     6
 #define L_ARTAESEL_CODEBLOCAGE          1
 #define L_ARTAESEL_PHARMACYGROUPID      3
 #define L_ARTAESEL_POSITIVLISTE         1
 #define L_ARTAESEL_HEALTHFUNDCODE       5
 #define L_ARTAESEL_ARTIKEL_LANGNAME     50
 #define L_ARTAESEL_TAXLEVEL	         6
 #define L_ARTAESEL_PREISEKGROSSO        9
 #define N_ARTAESEL_PREISEKGROSSO        2
 #define L_ARTAESEL_PREISEKGROSSONA      9
 #define N_ARTAESEL_PREISEKGROSSONA      2
 #define L_ARTAESEL_CODE_TYPE			 6
 #define L_ARTAESEL_ARTICLE_CODE		 25
 #define L_ARTAESEL_KZPSYCHOSTOFFE       1
 #define L_ARTAESEL_PRODUSERQUOTA		 6
 #define L_ARTAESEL_ARTIKELAKTIV         1
 #define L_ARTAESEL_ARTIKEL_GESPERRT     1
 #define L_ARTAESEL_IMPORTARTICLE        6
 #define L_ARTAESEL_TFG				     1
 #define L_ARTAESEL_KONTINGENT_PPE	     1
 #define L_ARTAESEL_MEDIZINPRODUKT	     1
 #define L_ARTAESEL_FROZEN			     6
 #define L_ARTAESEL_ABDACODE		     5

 #define L_ARTAESEL_PKEY 28

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define ARTAESEL_ANZ ( sizeof(ARTAESEL_BES) / sizeof(struct buf_desc) )
#endif
 #define G_ARTAESEL sizeof(struct ARTAESEL)


 #define ARTAESEL_H

 #define ARTAESEL_LISTE \
 			ARTIKEL.ARTIKEL_NR, \
 			ARTIKEL.ARTIKEL_MC, \
 			ARTIKEL.PACKGROESSE, \
 			ARTIKEL.DARREICHFORM, \
 			ARTIKEL.EINHEIT, \
 			ARTIKEL.ARTIKEL_NAME, \
 			ARTIKEL.BESTAND, \
 			ARTIKELPREIS.PREISEKAPO, \
 			ARTIKELLAGERORT.DATUMVERFALL, \
 			ARTIKELLAGERORT.FILIALNR, \
 			ARTSELECT.ETARTSCHALTER1, \
 			ARTSELECT.ETARTSCHALTER3, \
 			ARTSELECT.PRISOART, \
 			ARTIKEL.ETARTSCHALTER2, \
 			ARTIKEL.ETARTSCHALTER4, \
 			ARTIKEL.ETARTSCHALTER5, \
 			ARTIKEL.NORMPACKUNG, \
 			ARTIKEL.ETARTKLASSE1, \
			ARTIKEL.CHARGENARTIKEL, \
			ARTIKEL.HERSTELLER_CODE, \
			ARTIKEL.WAFOTYP, \
			ARTIKEL.NATRASTAFFELNR, \
			ARTICLETEXT.TEXT, \
			ARTIKELZENTAL.TEXTKEY_HOSPITAL, \
			ARTIKEL.CODEBLOCAGE, \
			ARTIKEL.PHARMACYGROUPID, \
			ARTIKEL.POSITIVLISTE, \
			ARTIKELZENTAL.HEALTHFUNDCODE,\
			ARTIKELZENTAL.ARTIKEL_LANGNAME,\
			ARTIKELZENTAL.TAXLEVEL,\
			ARTIKELPREIS.PREISEKGROSSO, \
			ARTIKELPREIS.PREISEKGROSSONA, \
			ARTICLECODES.CODE_TYPE, \
			ARTICLECODES.ARTICLE_CODE, \
			ARTIKELZENTAL.KZPSYCHOSTOFFE, \
			ARTIKELZENTAL.PRODUSERQUOTA, \
 			ARTIKEL.ARTIKELAKTIV, \
			ARTIKELZENTAL.ARTIKEL_GESPERRT, \
			ARTIKELZENTAL.IMPORTARTICLE, \
			ARTIKELZENTAL.TFG, \
			ARTIKELZENTAL.KONTINGENT_PPE, \
			ARTIKELZENTAL.MEDIZINPRODUKT, \
			ARTIKELZENTAL.FROZEN, \
			ARTIKELZENTAL.ABDACODE

#define ARTAESEL_PLISTE \
 			"ARTIKEL.ARTIKEL_NR," \
 			"ARTIKEL.ARTIKEL_MC," \
 			"ARTIKEL.PACKGROESSE," \
 			"ARTIKEL.DARREICHFORM," \
 			"ARTIKEL.EINHEIT," \
 			"ARTIKEL.ARTIKEL_NAME," \
 			"ARTIKEL.BESTAND," \
 			"ARTIKELPREIS.PREISEKAPO," \
 			"ARTIKELLAGERORT.DATUMVERFALL," \
 			"ARTIKELLAGERORT.FILIALNR," \
 			"ARTSELECT.ETARTSCHALTER1," \
 			"ARTSELECT.ETARTSCHALTER3," \
 			"ARTSELECT.PRISOART," \
 			"ARTIKEL.ETARTSCHALTER2," \
 			"ARTIKEL.ETARTSCHALTER4," \
 			"ARTIKEL.ETARTSCHALTER5," \
 			"ARTIKEL.NORMPACKUNG," \
 			"ARTIKEL.ETARTKLASSE1," \
			"ARTIKEL.CHARGENARTIKEL," \
			"ARTIKEL.HERSTELLER_CODE," \
			"ARTIKEL.WAFOTYP," \
			"ARTIKEL.NATRASTAFFELNR," \
			"ARTICLETEXT.TEXT," \
			"ARTIKELZENTAL.TEXTKEY_HOSPITAL," \
			"ARTIKEL.CODEBLOCAGE," \
			"ARTIKEL.PHARMACYGROUPID," \
			"ARTIKEL.POSITIVLISTE," \
			"ARTIKELZENTAL.HEALTHFUNDCODE," \
			"ARTIKELZENTAL.ARTIKEL_LANGNAME," \
			"ARTIKELZENTAL.TAXLEVEL," \
			"ARTIKELPREIS.PREISEKGROSSO," \
			"ARTIKELPREIS.PREISEKGROSSONA," \
			"ARTICLECODES.CODE_TYPE," \
			"ARTICLECODES.ARTICLE_CODE," \
			"ARTIKELZENTAL.KZPSYCHOSTOFFE," \
			"ARTIKELZENTAL.PRODUSERQUOTA," \
 			"ARTIKEL.ARTIKELAKTIV," \
			"ARTIKELZENTAL.ARTIKEL_GESPERRT," \
			"ARTIKELZENTAL.IMPORTARTICLE," \
			"ARTIKELZENTAL.TFG," \
			"ARTIKELZENTAL.KONTINGENT_PPE," \
			"ARTIKELZENTAL.MEDIZINPRODUKT," \
			"ARTIKELZENTAL.FROZEN," \
			"ARTIKELZENTAL.ABDACODE "

 #define ARTAESEL_PELISTE \
 			"ARTIKEL_NR," \
 			"ARTIKEL_MC," \
 			"PACKGROESSE," \
 			"DARREICHFORM," \
 			"EINHEIT," \
 			"ARTIKEL_NAME," \
 			"BESTAND," \
 			"PREISEKAPO," \
 			"DATUMVERFALL," \
 			"FILIALNR," \
 			"ETARTSCHALTER1," \
 			"ETARTSCHALTER3," \
 			"PRISOART," \
 			"ETARTSCHALTER2," \
 			"ETARTSCHALTER4," \
 			"ETARTSCHALTER5," \
 			"NORMPACKUNG," \
 			"ETARTKLASSE1," \
			"CHARGENARTIKEL," \
			"HERSTELLER_CODE," \
			"WAFOTYP," \
			"NATRASTAFFELNR," \
			"TEXT," \
			"TEXTKEY_HOSPITAL," \
			"CODEBLOCAGE," \
			"PHARMACYGROUPID," \
			"POSITIVLISTE," \
			"HEALTHFUNDCODE," \
			"ARTIKEL_LANGNAME," \
			"TAXLEVEL," \
			"PREISEKGROSSO," \
			"PREISEKGROSSONA," \
			"CODE_TYPE," \
			"ARTICLE_CODE," \
			"KZPSYCHOSTOFFE," \
			"PRODUSERQUOTA," \
 			"ARTIKELAKTIV," \
			"ARTIKEL_GESPERRT," \
			"IMPORTARTICLE," \
			"TFG," \
			"KONTINGENT_PPE," \
			"MEDIZINPRODUKT," \
			"FROZEN," \
			"ABDACODE "

 #define ARTAESEL_UPDLISTE \
 			"ARTIKEL_NR=?," \
 			"ARTIKEL_MC=?," \
 			"PACKGROESSE=?," \
 			"DARREICHFORM=?," \
 			"EINHEIT=?," \
 			"ARTIKEL_NAME=?," \
 			"BESTAND=?," \
 			"PREISEKAPO=?," \
 			"DATUMVERFALL=?," \
 			"FILIALNR=?," \
 			"ETARTSCHALTER1=?," \
 			"ETARTSCHALTER3=?," \
 			"PRISOART=?," \
 			"ETARTSCHALTER2=?," \
 			"ETARTSCHALTER4=?," \
 			"ETARTSCHALTER5=?," \
 			"NORMPACKUNG=?," \
 			"ETARTKLASSE1=?," \
			"CHARGENARTIKEL=?," \
			"HERSTELLER_CODE=?," \
			"WAFOTYP=?," \
			"NATRASTAFFELNR=?," \
			"TEXT=?," \
			"TEXTKEY_HOSPITAL=?," \
			"CODEBLOCAGE=?," \
			"PHARMACYGROUPID=?," \
			"POSITIVLISTE=?," \
			"HEALTHFUNDCODE=?," \
			"ARTIKEL_LANGNAME=?," \
			"TAXLEVEL=?," \
			"PREISEKGROSSO=?," \
			"PREISEKGROSSONA=?," \
			"CODE_TYPE=?," \
			"ARTICLE_CODE=?," \
			"KZPSYCHOSTOFFE=?," \
			"PRODUSERQUOTA=?," \
 			"ARTIKELAKTIV=?," \
			"ARTIKEL_GESPERRT=?," \
			"IMPORTARTICLE=?," \
			"TFG=?," \
			"KONTINGENT_PPE=?," \
			"MEDIZINPRODUKT=?," \
			"FROZEN=?," \
			"ABDACODE=? "

 #define ARTAESELARTIKEL_NR                    0
 #define ARTAESELARTIKEL_MC                    1
 #define ARTAESELPACKGROESSE                   2
 #define ARTAESELDARREICHFORM                  3
 #define ARTAESELEINHEIT                       4
 #define ARTAESELARTIKEL_NAME                  5
 #define ARTAESELBESTAND                       6
 #define ARTAESELPREISEKAPO                    7
 #define ARTAESELDATUMVERFALL                  8
 #define ARTAESELFILIALNR                      9
 #define ARTAESELETARTSCHALTER1                10
 #define ARTAESELETARTSCHALTER3                11
 #define ARTAESELPRISOART                      12
 #define ARTAESELETARTSCHALTER2                13
 #define ARTAESELETARTSCHALTER4                14
 #define ARTAESELETARTSCHALTER5                15
 #define ARTAESELNORMPACKUNG                   16
 #define ARTAESELETARTKLASSE1                  17
 #define ARTAESELCHARGENARTIKEL                18
 #define ARTAESELHERSTELLER_CODE               19
 #define ARTAESELWAFOTYP                       20
 #define ARTAESELNATRASTAFFELNR                21
 #define ARTAESELTEXT						   22
 #define ARTAESELTEXTKEY_HOSPITAL			   23
 #define ARTAESELCODEBLOCAGE				   24
 #define ARTAESELPHARMACYGROUPID			   25
 #define ARTAESELPOSITIVLISTE				   26
 #define ARTAESELHEALTHFUNDCODE				   27
 #define ARTAESELARTIKEL_LANGNAME			   28
 #define ARTAESELTAXLEVEL					   29
 #define ARTAESELPREISEKGROSSO				   30
 #define ARTAESELPREISEKGROSSONA			   31
 #define ARTAESELCODE_TYPE					   32
 #define ARTAESELARTICLE_CODE				   33
 #define ARTAESELKZPSYCHOSTOFFE				   34
 #define ARTAESELPRODUSERQUOTA				   35
 #define ARTAESELARTIKELAKTIV				   36
 #define ARTAESELARTIKEL_GESPERRT			   37
 #define ARTAESELIMPORTARTICLE				   38
 #define ARTAESELTFG						   39
 #define ARTAESELKONTINGENT_PPE				   40
 #define ARTAESELMEDIZINPRODUKT				   41
 #define ARTAESELFROZEN						   42
 #define ARTAESELABDACODE					   43

 #define ARTAESEL_ZEIGER(xxx) \
 			:xxx->ARTIKEL_NR,\
 			:xxx->ARTIKEL_MC,\
 			:xxx->PACKGROESSE,\
 			:xxx->DARREICHFORM,\
 			:xxx->EINHEIT,\
 			:xxx->ARTIKEL_NAME,\
 			:xxx->BESTAND,\
 			:xxx->PREISEKAPO,\
 			:xxx->DATUMVERFALL,\
 			:xxx->FILIALNR,\
 			:xxx->ETARTSCHALTER1,\
 			:xxx->ETARTSCHALTER3,\
 			:xxx->PRISOART,\
 			:xxx->ETARTSCHALTER2,\
 			:xxx->ETARTSCHALTER4,\
 			:xxx->ETARTSCHALTER5,\
 			:xxx->NORMPACKUNG,\
 			:xxx->ETARTKLASSE1,\
 			:xxx->CHARGENARTIKEL,\
 			:xxx->HERSTELLER_CODE,\
 			:xxx->WAFOTYP,\
 			:xxx->NATRASTAFFELNR,\
 			:xxx->TEXT,\
 			:xxx->TEXTKEY_HOSPITAL,\
 			:xxx->CODEBLOCAGE,\
 			:xxx->PHARMACYGROUPID,\
 			:xxx->POSITIVLISTE,\
 			:xxx->HEALTHFUNDCODE,\
 			:xxx->ARTIKEL_LANGNAME,\
 			:xxx->TAXLEVEL,\
 			:xxx->PREISEKGROSSO,\
 			:xxx->PREISEKGROSSONA,\
 			:xxx->CODE_TYPE,\
 			:xxx->ARTICLE_CODE,\
 			:xxx->KZPSYCHOSTOFFE,\
 			:xxx->PRODUSERQUOTA,\
 			:xxx->ARTIKELAKTIV,\
 			:xxx->ARTIKEL_GESPERRT,\
			:xxx->IMPORTARTICLE,\
			:xxx->TFG,\
			:xxx->KONTINGENT_PPE,\
			:xxx->MEDIZINPRODUKT,\
			:xxx->FROZEN,\
			:xxx->ABDACODE

 #define ARTAESEL_UPDATE(xxx) \
 			ARTIKEL_NR = :xxx->ARTIKEL_NR,\
 			ARTIKEL_MC = :xxx->ARTIKEL_MC,\
 			PACKGROESSE = :xxx->PACKGROESSE,\
 			DARREICHFORM = :xxx->DARREICHFORM,\
 			EINHEIT = :xxx->EINHEIT,\
 			ARTIKEL_NAME = :xxx->ARTIKEL_NAME,\
 			BESTAND = :xxx->BESTAND,\
 			PREISEKAPO = :xxx->PREISEKAPO,\
 			DATUMVERFALL = :xxx->DATUMVERFALL,\
 			FILIALNR = :xxx->FILIALNR,\
 			ETARTSCHALTER1 = :xxx->ETARTSCHALTER1,\
 			ETARTSCHALTER3 = :xxx->ETARTSCHALTER3,\
 			PRISOART = :xxx->PRISOART,\
 			ETARTSCHALTER2 = :xxx->ETARTSCHALTER2,\
 			ETARTSCHALTER4 = :xxx->ETARTSCHALTER4,\
 			ETARTSCHALTER5 = :xxx->ETARTSCHALTER5,\
 			NORMPACKUNG = :xxx->NORMPACKUNG,\
 			ETARTKLASSE1 = :xxx->ETARTKLASSE1,\
 			CHARGENARTIKEL = :xxx->CHARGENARTIKEL,\
 			HERSTELLER_CODE = :xxx->HERSTELLER_CODE,\
 			WAFOTYP = :xxx->WAFOTYP,\
 			NATRASTAFFELNR = :xxx->NATRASTAFFELNR,\
 			TEXT = :xxx->TEXT,\
 			TEXTKEY_HOSPITAL = :xxx->TEXTKEY_HOSPITAL,\
 			CODEBLOCAGE = :xxx->CODEBLOCAGE,\
 			PHARMACYGROUPID = :xxx->PHARMACYGROUPID,\
 			POSITIVLISTE = :xxx->POSITIVLISTE,\
 			HEALTHFUNDCODE = :xxx->HEALTHFUNDCODE,\
 			ARTIKEL_LANGNAME = :xxx->ARTIKEL_LANGNAME,\
 			TAXLEVEL = :xxx->TAXLEVEL,\
 			PREISEKGROSSO = :xxx->PREISEKGROSSO,\
 			PREISEKGROSSONA = :xxx->PREISEKGROSSONA,\
 			CODE_TYPE = :xxx->CODE_TYPE,\
 			ARTICLE_CODE = :xxx->ARTICLE_CODE,\
 			KZPSYCHOSTOFFE = :xxx->KZPSYCHOSTOFFE,\
 			PRODUSERQUOTA = :xxx->PRODUSERQUOTA,\
 			ARTIKELAKTIV = :xxx->ARTIKELAKTIV,\
 			ARTIKEL_GESPERRT = :xxx->ARTIKEL_GESPERRT,\
			IMPORTARTICLE = :xxx->IMPORTARTICLE,\
			TFG = :xxx->TFG,\
			KONTINGENT_PPE = :xxx->KONTINGENT_PPE,\
			MEDIZINPRODUKT = :xxx->MEDIZINPRODUKT,\
			FROZEN = :xxx->FROZEN,\
			ABDACODE = :xxx->ABDACODE


 #define LS_ARTAESEL_ARTIKEL_NR           11
 #define LS_ARTAESEL_ARTIKEL_MC           13
 #define LS_ARTAESEL_PACKGROESSE          11
 #define LS_ARTAESEL_DARREICHFORM         4
 #define LS_ARTAESEL_EINHEIT              10
 #define LS_ARTAESEL_ARTIKEL_NAME         31
 #define LS_ARTAESEL_BESTAND              11
 #define LS_ARTAESEL_PREISEKAPO           11
 #define LS_ARTAESEL_DATUMVERFALL         11
 #define LS_ARTAESEL_FILIALNR             7
 #define LS_ARTAESEL_ETARTSCHALTER1       6
 #define LS_ARTAESEL_ETARTSCHALTER3       6
 #define LS_ARTAESEL_PRISOART             2
 #define LS_ARTAESEL_ETARTSCHALTER2       6
 #define LS_ARTAESEL_ETARTSCHALTER4       6
 #define LS_ARTAESEL_ETARTSCHALTER5       6
 #define LS_ARTAESEL_NORMPACKUNG          3
 #define LS_ARTAESEL_ETARTKLASSE1         6
 #define LS_ARTAESEL_CHARGENARTIKEL       2
 #define LS_ARTAESEL_HERSTELLER_CODE      6
 #define LS_ARTAESEL_WAFOTYP              2
 #define LS_ARTAESEL_NATRASTAFFELNR       11
 #define LS_ARTAESEL_TEXT			      241
 #define LS_ARTAESEL_TEXTKEY_HOSPITAL     7
 #define LS_ARTAESEL_CODEBLOCAGE	      2
 #define LS_ARTAESEL_PHARMACYGROUPID      4
 #define LS_ARTAESEL_POSITIVLISTE	      2
 #define LS_ARTAESEL_HEALTHFUNDCODE	      6
 #define LS_ARTAESEL_ARTIKEL_LANGNAME     51
 #define LS_ARTAESEL_TAXLEVEL             7
 #define LS_ARTAESEL_PREISEKGROSSO        11
 #define LS_ARTAESEL_PREISEKGROSSONA      11
 #define LS_ARTAESEL_CODE_TYPE			  7
 #define LS_ARTAESEL_ARTICLE_CODE		  26
 #define LS_ARTAESEL_KZPSYCHOSTOFFE	      2
 #define LS_ARTAESEL_PRODUSERQUOTA		  7
 #define LS_ARTAESEL_ARTIKELAKTIV	      2
 #define LS_ARTAESEL_ARTIKEL_GESPERRT     2
 #define LS_ARTAESEL_IMPORTARTICLE        7
 #define LS_ARTAESEL_TFG			      2
 #define LS_ARTAESEL_KONTINGENT_PPE	      2
 #define LS_ARTAESEL_MEDIZINPRODUKT	      2
 #define LS_ARTAESEL_FROZEN			      7
 #define LS_ARTAESEL_ABDACODE			  6
 #define LS_ARTAESEL_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct ARTAESEL {
		 long    ARTIKEL_NR;
		 char    ARTIKEL_MC[12 + 1];
		 long    PACKGROESSE;
		 char    DARREICHFORM[3 + 1];
		 char    EINHEIT[9 + 1];
		 char    ARTIKEL_NAME[30 + 1];
		 long    BESTAND;
		 double  PREISEKAPO;
		 long    DATUMVERFALL;
		 short   FILIALNR;
		 long    ETARTSCHALTER1;
		 long    ETARTSCHALTER3;
		 char    PRISOART[1 + 1];
		 long    ETARTSCHALTER2;
		 long    ETARTSCHALTER4;
		 long    ETARTSCHALTER5;
		 char    NORMPACKUNG[2 + 1];
		 long    ETARTKLASSE1;
		 char    CHARGENARTIKEL[1 + 1];
		 char    HERSTELLER_CODE[5 + 1];
		 char    WAFOTYP[1 + 1];
		 long    NATRASTAFFELNR;
		 char    TEXT[240 + 1];
		 short   TEXTKEY_HOSPITAL;
		 char    CODEBLOCAGE[1 + 1];
		 char    PHARMACYGROUPID[3 + 1];
		 char    POSITIVLISTE[1 + 1];
		 char    HEALTHFUNDCODE[5 + 1];
		 char    ARTIKEL_LANGNAME[50 + 1];
		 short   TAXLEVEL;
		 double  PREISEKGROSSO;
		 double  PREISEKGROSSONA;
         short	 CODE_TYPE;
         char	 ARTICLE_CODE[25 + 1];
		 char    KZPSYCHOSTOFFE[1 + 1];
         short	 PRODUSERQUOTA;
		 char    ARTIKELAKTIV[1 + 1];
		 char    ARTIKEL_GESPERRT[1 + 1];
		 short   IMPORTARTICLE;
		 char    TFG[1 + 1];
		 char    KONTINGENT_PPE[1 + 1];
		 char    MEDIZINPRODUKT[1 + 1];
		 short   FROZEN;
		 char    ABDACODE[5 + 1];
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_ARTAESEL {
		 long    ARTIKEL_NR;
		 char    ARTIKEL_MC[12 + 1];
		 long    PACKGROESSE;
		 char    DARREICHFORM[3 + 1];
		 char    EINHEIT[9 + 1];
		 char    ARTIKEL_NAME[30 + 1];
		 long    BESTAND;
		 double  PREISEKAPO;
		 long    DATUMVERFALL;
		 short   FILIALNR;
		 long    ETARTSCHALTER1;
		 long    ETARTSCHALTER3;
		 char    PRISOART;
		 long    ETARTSCHALTER2;
		 long    ETARTSCHALTER4;
		 long    ETARTSCHALTER5;
		 char    NORMPACKUNG[2 + 1];
		 long    ETARTKLASSE1;
		 char    CHARGENARTIKEL;
		 char    HERSTELLER_CODE[5 + 1];
		 char    WAFOTYP;
		 long    NATRASTAFFELNR;
		 char    TEXT[240 + 1];
		 short   TEXTKEY_HOSPITAL;
		 char    CODEBLOCAGE;
		 char    PHARMACYGROUPID[3 + 1];
		 char    POSITIVLISTE;
		 char    HEALTHFUNDCODE[5 + 1];
		 char    ARTIKEL_LANGNAME[50 + 1];
		 short   TAXLEVEL;
		 double  PREISEKGROSSO;
		 double  PREISEKGROSSONA;
         short	 CODE_TYPE;
         char	 ARTICLE_CODE[25 + 1];
		 char    KZPSYCHOSTOFFE;
         short	 PRODUSERQUOTA;
		 char    ARTIKELAKTIV;
		 char    ARTIKEL_GESPERRT;
		 short   IMPORTARTICLE;
		 char    TFG;
		 char    KONTINGENT_PPE;
		 char    MEDIZINPRODUKT;
		 short   FROZEN;
		 char    ABDACODE[5 + 1];
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_ARTAESEL {
		 short  ARTIKEL_NR;
		 short  ARTIKEL_MC;
		 short  PACKGROESSE;
		 short  DARREICHFORM;
		 short  EINHEIT;
		 short  ARTIKEL_NAME;
		 short  BESTAND;
		 short  PREISEKAPO;
		 short  DATUMVERFALL;
		 short  FILIALNR;
		 short  ETARTSCHALTER1;
		 short  ETARTSCHALTER3;
		 short  PRISOART;
		 short  ETARTSCHALTER2;
		 short  ETARTSCHALTER4;
		 short  ETARTSCHALTER5;
		 short  NORMPACKUNG;
		 short  ETARTKLASSE1;
		 short  CHARGENARTIKEL;
		 short  HERSTELLER_CODE;
		 short  WAFOTYP;
		 short  NATRASTAFFELNR;
		 short  TEXT;
		 short  TEXTKEY_HOSPITAL;
		 short  CODEBLOCAGE;
		 short  PHARMACYGROUPID;
		 short  POSITIVLISTE;
		 short  HEALTHFUNDCODE;
		 short  ARTIKEL_LANGNAME;
		 short  TAXLEVEL;
		 short  PREISEKGROSSO;
		 short  PREISEKGROSSONA;
         short	CODE_TYPE;
         short  ARTICLE_CODE;
		 short  KZPSYCHOSTOFFE;
         short	PRODUSERQUOTA;
		 short  ARTIKELAKTIV;
		 short  ARTIKEL_GESPERRT;
		 short  IMPORTARTICLE;
		 short  TFG;
		 short  KONTINGENT_PPE;
		 short  MEDIZINPRODUKT;
		 short  FROZEN;
		 short  ABDACODE;
		 short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_ARTAESEL {
		 char    ARTIKEL_NR[11];
		 char    ARTIKEL_MC[12 + 1];
		 char    PACKGROESSE[11];
		 char    DARREICHFORM[3 + 1];
		 char    EINHEIT[9 + 1];
		 char    ARTIKEL_NAME[30 + 1];
		 char    BESTAND[11];
		 char    PREISEKAPO[9 + 2];
		 char    DATUMVERFALL[11];
		 char    FILIALNR[7];
		 char    ETARTSCHALTER1[5 + 1];
		 char    ETARTSCHALTER3[5 + 1];
		 char    PRISOART[1 + 1];
		 char    ETARTSCHALTER2[5 + 1];
		 char    ETARTSCHALTER4[5 + 1];
		 char    ETARTSCHALTER5[5 + 1];
		 char    NORMPACKUNG[2 + 1];
		 char    ETARTKLASSE1[5 + 1];
		 char    CHARGENARTIKEL[1 + 1];
		 char    HERSTELLER_CODE[5 + 1];
		 char    WAFOTYP[1 + 1];
		 char    NATRASTAFFELNR[11];
		 char    TEXT[240 + 1];
		 char    TEXTKEY_HOSPITAL[7];
		 char    CODEBLOCAGE[1 + 1];
		 char    PHARMACYGROUPID[3 + 1];
		 char    POSITIVLISTE[1 + 1];
		 char    HEALTHFUNDCODE[5 + 1];
		 char    ARTIKEL_LANGNAME[50 + 1];
		 char    TAXLEVEL[7];
		 char    PREISEKGROSSO[9 + 2];
		 char    PREISEKGROSSONA[9 + 2];
         char	 CODE_TYPE[7];
         char	 ARTICLE_CODE[25 + 1];
		 char    KZPSYCHOSTOFFE[1 + 1];
         char	 PRODUSERQUOTA[7];
		 char    ARTIKELAKTIV[1 + 1];
		 char    ARTIKEL_GESPERRT[1 + 1];
		 char    IMPORTARTICLE[7];
		 char    TFG[1 + 1];
		 char    KONTINGENT_PPE[1 + 1];
		 char    MEDIZINPRODUKT[1 + 1];
		 char    FROZEN[7];
		 char    ABDACODE[5 + 1];
		 char    FETCH_REL[11];
       };

 struct O_ARTAESEL {
		 char    ARTIKEL_NR[11];
		 char    ARTIKEL_MC[12];
		 char    PACKGROESSE[11];
		 char    DARREICHFORM[3];
		 char    EINHEIT[9];
		 char    ARTIKEL_NAME[30];
		 char    BESTAND[11];
		 char    PREISEKAPO[9];
		 char    DATUMVERFALL[11];
		 char    FILIALNR[7];
		 char    ETARTSCHALTER1[5];
		 char    ETARTSCHALTER3[5];
		 char    PRISOART[1];
		 char    ETARTSCHALTER2[5];
		 char    ETARTSCHALTER4[5];
		 char    ETARTSCHALTER5[5];
		 char    NORMPACKUNG[2];
		 char    ETARTKLASSE1[5];
		 char    CHARGENARTIKEL[1];
		 char    HERSTELLER_CODE[5];
		 char    WAFOTYP[1];
		 char    NATRASTAFFELNR[11];
		 char    TEXT[240];
		 char    TEXTKEY_HOSPITAL[7];
		 char    CODEBLOCAGE[1];
		 char    PHARMACYGROUPID[3];
		 char    POSITIVLISTE[1];
		 char    HEALTHFUNDCODE[5];
		 char    ARTIKEL_LANGNAME[50];
		 char    TAXLEVEL[7];
		 char    PREISEKGROSSO[9];
		 char    PREISEKGROSSONA[9];
         char	 CODE_TYPE[7];
         char	 ARTICLE_CODE[25];
		 char    KZPSYCHOSTOFFE[1];
         char	 PRODUSERQUOTA[7];
		 char    ARTIKELAKTIV[1];
		 char    ARTIKEL_GESPERRT[1];
		 char    IMPORTARTICLE[7];
		 char    TFG[1];
		 char    KONTINGENT_PPE[1];
		 char    MEDIZINPRODUKT[1];
		 char    FROZEN[7];
		 char    ABDACODE[5];
		 char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc ARTAESEL_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,   12 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_D ,    9 ,   2 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,  240 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   50 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_D ,    9 ,   2 },
	 { TYP_D ,    9 ,   2 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,   25 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTAESEL_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_C,   12 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_C,    3 ,   0 },
	 { TYP_C,    9 ,   0 },
	 { TYP_C,   30 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_D,    9 ,   2 },
	 { TYP_L,   11 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_C,    2 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_C,    5 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_C,  240 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_C,    3 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_C,    5 ,   0 },
	 { TYP_C ,  50 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_D,    9 ,   2 },
	 { TYP_D,    9 ,   2 },
	 { TYP_S,    5 ,   0 },
	 { TYP_C ,  25 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_C,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CARTAESEL
 {
  public:

  ARTAESEL s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, ARTAESEL_BES, ARTAESEL_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,ARTAESEL_BES, ARTAESEL_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,ARTAESEL_BES, ARTAESEL_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CARTAESEL()
  {
   ::buf_default((void *)&s, ARTAESEL_BES, ARTAESEL_ANZ);
  }
 };
#endif

#define ARTAESEL_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 ARTIKEL_NR INTEGER           ,\
		 ARTIKEL_MC CHAR(12)          ,\
		 PACKGROESSE INTEGER           ,\
		 DARREICHFORM CHAR(3)           ,\
		 EINHEIT CHAR(9)           ,\
		 ARTIKEL_NAME CHAR(30)          ,\
		 BESTAND INTEGER           ,\
		 PREISEKAPO DECIMAL(9,2)      ,\
		 DATUMVERFALL INTEGER           ,\
		 FILIALNR SMALLINT          ,\
		 ETARTSCHALTER1 INTEGER,\
		 ETARTSCHALTER3 INTEGER,\
		 PRISOART CHAR(1)           ,\
		 ETARTSCHALTER2 INTEGER,\
		 ETARTSCHALTER4 INTEGER,\
		 ETARTSCHALTER5 INTEGER,\
		 NORMPACKUNG CHAR(2)           ,\
		 ETARTKLASSE1 INTEGER,\
		 CHARGENARTIKEL CHAR(1)           ,\
		 HERSTELLER_CODE CHAR(5)           ,\
		 WAFOTYP CHAR(1)           ,\
		 NATRASTAFFELNR INTEGER           ,\
		 TEXT CHAR(240)           ,\
		 TEXTKEY_HOSPITAL SMALLINT          ,\
		 CODEBLOCAGE CHAR(1)           ,\
		 PHARMACYGROUPID CHAR(3)           ,\
		 POSITIVLISTE CHAR(1)           ,\
		 HEALTHFUNDCODE CHAR(5)           ,\
		 ARTIKEL_LANGNAME CHAR(50)           ,\
		 TAXLEVEL SMALLINT          ,\
		 PREISEKGROSSO DECIMAL(9,2)      ,\
		 PREISEKGROSSONA DECIMAL(9,2)      ,\
		 CODE_TYPE SMALLINT          ,\
		 ARTICLE_CODE CHAR(25)           ,\
		 KZPSYCHOSTOFFE CHAR(1)           ,\
		 PRODUSERQUOTA SMALLINT          ,\
		 ARTIKELAKTIV CHAR(1)           ,\
		 ARTIKEL_GESPERRT CHAR(1)           ,\
		 IMPORTARTICLE SMALLINT           ,\
		 TFG CHAR(1)           ,\
		 KONTINGENT_PPE CHAR(1)           ,\
		 MEDIZINPRODUKT CHAR(1)           ,\
		 FROZEN SMALLINT          ,\
		 ABDACODE CHAR(5)           ,\
		 FETCH_REL INTEGER  ) EXTENT SIZE 66830 LOCK MODE ROW;

#define ARTAESEL_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX I_ARTIKEL_1        on yyy( ARTIKEL_NR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_ARTIKEL_2        on yyy( ARTIKEL_MC );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_ARTIKELLAGEROR_5 on yyy( FILIALNR, LAGERFACHNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_ARTIKELLAGEROR_2 on yyy( FILIALNR, ARTIKEL_NR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE UNIQUE INDEX I_ARTIKELLAGERORT_ on yyy( FILIALNR, ARTIKEL_NR, LAGERBEREICHNR, STATIONNR, LAGERFACHNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define ARTAESEL_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_ARTIKEL_1       ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_ARTIKEL_2       ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_ARTIKELLAGEROR_5;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_ARTIKELLAGEROR_2;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_ARTIKELLAGERORT_;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_ARTALT_ARTIKEL_NR           11
 #define L_ARTALT_ARTIKEL_NR_ALTERN    11


 #define L_ARTALT_PKEY 22

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define ARTALT_ANZ ( sizeof(ARTALT_BES) / sizeof(struct buf_desc) )
#endif
 #define G_ARTALT sizeof(struct ARTALT)


 #define ARTALT_H

 #define ARTALT_LISTE \
 			ARTIKELALTERN.ARTIKEL_NR, \
 			ARTIKELALTERN.ARTIKEL_NR_ALTERN
 #define ARTALT_PLISTE \
 			"ARTIKELALTERN.ARTIKEL_NR," \
 			"ARTIKELALTERN.ARTIKEL_NR_ALTERN " 

 #define ARTALT_PELISTE \
 			"ARTIKEL_NR," \
 			"ARTIKEL_NR_ALTERN " 

 #define ARTALT_UPDLISTE \
 			"ARTIKEL_NR=?," \
 			"ARTIKEL_NR_ALTERN=? " 

 #define ARTALTARTIKEL_NR                    0
 #define ARTALTARTIKEL_NR_ALTERN             1

 #define ARTALT_ZEIGER(xxx) \
 			:xxx->ARTIKEL_NR,\
 			:xxx->ARTIKEL_NR_ALTERN

 #define ARTALT_UPDATE(xxx) \
 			ARTIKEL_NR = :xxx->ARTIKEL_NR,\
 			ARTIKEL_NR_ALTERN = :xxx->ARTIKEL_NR_ALTERN

 #define LS_ARTALT_ARTIKEL_NR           11
 #define LS_ARTALT_ARTIKEL_NR_ALTERN    11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct ARTALT {
		 long    ARTIKEL_NR;
		 long    ARTIKEL_NR_ALTERN;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_ARTALT {
		 long    ARTIKEL_NR;
		 long    ARTIKEL_NR_ALTERN;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_ARTALT {
		 short  ARTIKEL_NR;
		 short  ARTIKEL_NR_ALTERN;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_ARTALT {
		 char    ARTIKEL_NR[11];
		 char    ARTIKEL_NR_ALTERN[11];
       };

 struct O_ARTALT {
		 char    ARTIKEL_NR[11];
		 char    ARTIKEL_NR_ALTERN[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc ARTALT_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTALT_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CARTALT
 {
  public:

  ARTALT s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, ARTALT_BES, ARTALT_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,ARTALT_BES, ARTALT_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,ARTALT_BES, ARTALT_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CARTALT()
  {
   ::buf_default((void *)&s, ARTALT_BES, ARTALT_ANZ);
  }
 };
#endif

#define ARTALT_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 ARTIKEL_NR INTEGER           ,\
		 ARTIKEL_NR_ALTERN INTEGER             ) EXTENT SIZE 1099 LOCK MODE ROW;

#define ARTALT_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX ARTIKELALTERNX     on yyy( ARTIKEL_NR, ARTIKEL_NR_ALTERN );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define ARTALT_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX ARTIKELALTERNX    ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_ARTFOLGE_ARTIKEL_NR           11
 #define L_ARTFOLGE_BESTAND              11


 #define L_ARTFOLGE_PKEY 11

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define ARTFOLGE_ANZ ( sizeof(ARTFOLGE_BES) / sizeof(struct buf_desc) )
#endif
 #define G_ARTFOLGE sizeof(struct ARTFOLGE)


 #define ARTFOLGE_H

 #define ARTFOLGE_LISTE \
 			ARTIKEL.ARTIKEL_NR, \
 			ARTIKEL.BESTAND
 #define ARTFOLGE_PLISTE \
 			"ARTIKEL.ARTIKEL_NR," \
 			"ARTIKEL.BESTAND " 

 #define ARTFOLGE_PELISTE \
 			"ARTIKEL_NR," \
 			"BESTAND " 

 #define ARTFOLGE_UPDLISTE \
 			"ARTIKEL_NR=?," \
 			"BESTAND=? " 

 #define ARTFOLGEARTIKEL_NR                    0
 #define ARTFOLGEBESTAND                       1

 #define ARTFOLGE_ZEIGER(xxx) \
 			:xxx->ARTIKEL_NR,\
 			:xxx->BESTAND

 #define ARTFOLGE_UPDATE(xxx) \
 			ARTIKEL_NR = :xxx->ARTIKEL_NR,\
 			BESTAND = :xxx->BESTAND

 #define LS_ARTFOLGE_ARTIKEL_NR           11
 #define LS_ARTFOLGE_BESTAND              11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct ARTFOLGE {
		 long    ARTIKEL_NR;
		 long    BESTAND;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_ARTFOLGE {
		 long    ARTIKEL_NR;
		 long    BESTAND;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_ARTFOLGE {
		 short  ARTIKEL_NR;
		 short  BESTAND;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_ARTFOLGE {
		 char    ARTIKEL_NR[11];
		 char    BESTAND[11];
       };

 struct O_ARTFOLGE {
		 char    ARTIKEL_NR[11];
		 char    BESTAND[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc ARTFOLGE_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTFOLGE_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CARTFOLGE
 {
  public:

  ARTFOLGE s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, ARTFOLGE_BES, ARTFOLGE_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,ARTFOLGE_BES, ARTFOLGE_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,ARTFOLGE_BES, ARTFOLGE_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CARTFOLGE()
  {
   ::buf_default((void *)&s, ARTFOLGE_BES, ARTFOLGE_ANZ);
  }
 };
#endif

#define ARTFOLGE_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 ARTIKEL_NR INTEGER           ,\
		 BESTAND INTEGER             ) EXTENT SIZE 7658 LOCK MODE ROW;

#define ARTFOLGE_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX I_ARTIKEL_1        on yyy( ARTIKEL_NR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define ARTFOLGE_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_ARTIKEL_1       ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_ARTINF_NATRASTAFFELNR       11
 #define L_ARTINF_ARTIKEL_MC           12
 #define L_ARTINF_PACKGROESSE          11
 #define L_ARTINF_DARREICHFORM         3
 #define L_ARTINF_NORMPACKUNG          2
 #define L_ARTINF_EINHEIT              9
 #define L_ARTINF_ARTIKEL_NAME         30
 #define L_ARTINF_VERKAUFEINHEIT       11
 #define L_ARTINF_CONTAINERGROESSE     11
 #define L_ARTINF_ETARTKLASSE1         5
 #define L_ARTINF_ETARTKLASSE2         5
 #define L_ARTINF_ETARTSCHALTER1       5
 #define L_ARTINF_ETARTSCHALTER2       5
 #define L_ARTINF_ETARTSCHALTER3       5
 #define L_ARTINF_ETARTSCHALTER4       5
 #define L_ARTINF_ETARTSCHALTER5       5
 #define L_ARTINF_HERSTELLER_NR        11
 #define L_ARTINF_WARENGRUPPE          5
 #define L_ARTINF_THERAPIEGRUPPE       5
 #define L_ARTINF_LAENGE               11
 #define L_ARTINF_HOEHE                11
 #define L_ARTINF_BREITE               11
 #define L_ARTINF_GEWICHT              11
 #define L_ARTINF_LAUFZEITMONATE       11
 #define L_ARTINF_BESTAND              11
 #define L_ARTINF_NACHFRAGE            11
 #define L_ARTINF_ZUZAHLUNG            1
 #define L_ARTINF_ARTIKEL_NR           11
 #define L_ARTINF_RABATTFAEHIG         2
 #define L_ARTINF_ARTIKELAKTIV         1
 #define L_ARTINF_VERBUNDARTIKEL       1
 #define L_ARTINF_PRISOART             1
 #define L_ARTINF_HERSTELLER_CODE      5
 #define L_ARTINF_TEXTKEY			   6
 #define L_ARTINF_KONTIGENTMENGE	   6
 #define L_ARTINF_BESTANDRESERVIERT    11
 #define L_ARTINF_STELLER              1
 #define L_ARTINF_POSITIVLISTE         1
 #define L_ARTINF_TAXLEVEL	           6
 #define L_ARTINF_ARTIKEL_LANGNAME     50
 #define L_ARTINF_IMPORTARTICLE        6
 #define L_ARTINF_WAFOTYP              1
 #define L_ARTINF_DATUM_LIEFERBAR_AB   11
 #define L_ARTINF_FILIALNR             6
 #define L_ARTINF_FROZEN	           6


 #define L_ARTINF_PKEY 22

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define ARTINF_ANZ ( sizeof(ARTINF_BES) / sizeof(struct buf_desc) )
#endif
 #define G_ARTINF sizeof(struct ARTINF)


 #define ARTINF_H

 #define ARTINF_LISTE \
 			ARTIKEL.NATRASTAFFELNR, \
 			ARTIKEL.ARTIKEL_MC, \
 			ARTIKEL.PACKGROESSE, \
 			ARTIKEL.DARREICHFORM, \
 			ARTIKEL.NORMPACKUNG, \
 			ARTIKEL.EINHEIT, \
 			ARTIKEL.ARTIKEL_NAME, \
 			ARTIKEL.VERKAUFEINHEIT, \
 			ARTIKEL.CONTAINERGROESSE, \
 			ARTIKEL.ETARTKLASSE1, \
 			ARTIKEL.ETARTKLASSE2, \
 			ARTIKEL.ETARTSCHALTER1, \
 			ARTIKEL.ETARTSCHALTER2, \
 			ARTIKEL.ETARTSCHALTER3, \
 			ARTIKEL.ETARTSCHALTER4, \
 			ARTIKEL.ETARTSCHALTER5, \
 			ARTIKEL.HERSTELLER_NR, \
 			ARTIKEL.WARENGRUPPE, \
 			ARTIKEL.THERAPIEGRUPPE, \
 			ARTIKEL.LAENGE, \
 			ARTIKEL.HOEHE, \
 			ARTIKEL.BREITE, \
 			ARTIKEL.GEWICHT, \
 			ARTIKEL.LAUFZEITMONATE, \
 			ARTIKEL.BESTAND, \
 			ARTIKEL.NACHFRAGE, \
 			ARTIKEL.ZUZAHLUNG, \
 			ARTIKEL.ARTIKEL_NR, \
 			ARTIKEL.RABATTFAEHIG, \
 			ARTIKEL.ARTIKELAKTIV, \
 			ARTIKEL.VERBUNDARTIKEL, \
 			ARTIKEL.PRISOART, \
 			ARTIKEL.HERSTELLER_CODE, \
 			ARTIKEL.TEXTKEY, \
 			ARTIKEL.KONTIGENTMENGE, \
 			ARTIKEL.BESTANDRESERVIERT, \
 			ARTIKEL.STELLER, \
 			ARTIKEL.POSITIVLISTE, \
 			ARTIKEL.TAXLEVEL, \
 			ARTIKEL.ARTIKEL_LANGNAME, \
			ARTIKEL.IMPORTARTICLE, \
			ARTIKEL.WAFOTYP, \
			ARTIKEL.DATUM_LIEFERBAR_AB, \
			ARTIKEL.FILIALNR, \
			ARTIKEL.FROZEN
#define ARTINF_PLISTE \
 			"ARTIKEL.NATRASTAFFELNR," \
 			"ARTIKEL.ARTIKEL_MC," \
 			"ARTIKEL.PACKGROESSE," \
 			"ARTIKEL.DARREICHFORM," \
 			"ARTIKEL.NORMPACKUNG," \
 			"ARTIKEL.EINHEIT," \
 			"ARTIKEL.ARTIKEL_NAME," \
 			"ARTIKEL.VERKAUFEINHEIT," \
 			"ARTIKEL.CONTAINERGROESSE," \
 			"ARTIKEL.ETARTKLASSE1," \
 			"ARTIKEL.ETARTKLASSE2," \
 			"ARTIKEL.ETARTSCHALTER1," \
 			"ARTIKEL.ETARTSCHALTER2," \
 			"ARTIKEL.ETARTSCHALTER3," \
 			"ARTIKEL.ETARTSCHALTER4," \
 			"ARTIKEL.ETARTSCHALTER5," \
 			"ARTIKEL.HERSTELLER_NR," \
 			"ARTIKEL.WARENGRUPPE," \
 			"ARTIKEL.THERAPIEGRUPPE," \
 			"ARTIKEL.LAENGE," \
 			"ARTIKEL.HOEHE," \
 			"ARTIKEL.BREITE," \
 			"ARTIKEL.GEWICHT," \
 			"ARTIKEL.LAUFZEITMONATE," \
 			"ARTIKEL.BESTAND," \
 			"ARTIKEL.NACHFRAGE," \
 			"ARTIKEL.ZUZAHLUNG," \
 			"ARTIKEL.ARTIKEL_NR," \
 			"ARTIKEL.RABATTFAEHIG," \
 			"ARTIKEL.ARTIKELAKTIV," \
 			"ARTIKEL.VERBUNDARTIKEL," \
 			"ARTIKEL.PRISOART," \
 			"ARTIKEL.HERSTELLER_CODE," \
 			"ARTIKEL.TEXTKEY," \
 			"ARTIKEL.KONTIGENTMENGE," \
 			"ARTIKEL.BESTANDRESERVIERT," \
 			"ARTIKEL.STELLER," \
 			"ARTIKEL.POSITIVLISTE," \
 			"ARTIKEL.TAXLEVEL," \
 			"ARTIKEL.ARTIKEL_LANGNAME," \
			"ARTIKEL.IMPORTARTICLE," \
			"ARTIKEL.WAFOTYP," \
			"ARTIKEL.DATUM_LIEFERBAR_AB," \
			"ARTIKEL.FILIALNR," \
			"ARTIKEL.FROZEN "

 #define ARTINF_PELISTE \
 			"NATRASTAFFELNR," \
 			"ARTIKEL_MC," \
 			"PACKGROESSE," \
 			"DARREICHFORM," \
 			"NORMPACKUNG," \
 			"EINHEIT," \
 			"ARTIKEL_NAME," \
 			"VERKAUFEINHEIT," \
 			"CONTAINERGROESSE," \
 			"ETARTKLASSE1," \
 			"ETARTKLASSE2," \
 			"ETARTSCHALTER1," \
 			"ETARTSCHALTER2," \
 			"ETARTSCHALTER3," \
 			"ETARTSCHALTER4," \
 			"ETARTSCHALTER5," \
 			"HERSTELLER_NR," \
 			"WARENGRUPPE," \
 			"THERAPIEGRUPPE," \
 			"LAENGE," \
 			"HOEHE," \
 			"BREITE," \
 			"GEWICHT," \
 			"LAUFZEITMONATE," \
 			"BESTAND," \
 			"NACHFRAGE," \
 			"ZUZAHLUNG," \
 			"ARTIKEL_NR," \
 			"RABATTFAEHIG," \
 			"ARTIKELAKTIV," \
 			"VERBUNDARTIKEL," \
 			"PRISOART," \
 			"HERSTELLER_CODE," \
 			"TEXTKEY," \
 			"KONTIGENTMENGE," \
 			"BESTANDRESERVIERT," \
 			"STELLER," \
 			"POSITIVLISTE," \
 			"TAXLEVEL," \
 			"ARTIKEL_LANGNAME," \
			"IMPORTARTICLE," \
			"WAFOTYP," \
			"DATUM_LIEFERBAR_AB," \
			"FILIALNR," \
			"FROZEN "

 #define ARTINF_UPDLISTE \
 			"NATRASTAFFELNR=?," \
 			"ARTIKEL_MC=?," \
 			"PACKGROESSE=?," \
 			"DARREICHFORM=?," \
 			"NORMPACKUNG=?," \
 			"EINHEIT=?," \
 			"ARTIKEL_NAME=?," \
 			"VERKAUFEINHEIT=?," \
 			"CONTAINERGROESSE=?," \
 			"ETARTKLASSE1=?," \
 			"ETARTKLASSE2=?," \
 			"ETARTSCHALTER1=?," \
 			"ETARTSCHALTER2=?," \
 			"ETARTSCHALTER3=?," \
 			"ETARTSCHALTER4=?," \
 			"ETARTSCHALTER5=?," \
 			"HERSTELLER_NR=?," \
 			"WARENGRUPPE=?," \
 			"THERAPIEGRUPPE=?," \
 			"LAENGE=?," \
 			"HOEHE=?," \
 			"BREITE=?," \
 			"GEWICHT=?," \
 			"LAUFZEITMONATE=?," \
 			"BESTAND=?," \
 			"NACHFRAGE=?," \
 			"ZUZAHLUNG=?," \
 			"ARTIKEL_NR=?," \
 			"RABATTFAEHIG=?," \
 			"ARTIKELAKTIV=?," \
 			"VERBUNDARTIKEL=?," \
 			"PRISOART=?," \
 			"HERSTELLER_CODE=?," \
 			"TEXTKEY=?," \
 			"KONTIGENTMENGE=?," \
 			"BESTANDRESERVIERT=?," \
 			"STELLER=?," \
 			"POSITIVLISTE=?," \
 			"TAXLEVEL=?," \
 			"ARTIKEL_LANGNAME=?," \
			"ARTIKEL.IMPORTARTICLE=?," \
			"IMPORTARTICLE=?," \
			"WAFOTYP=?," \
			"DATUM_LIEFERBAR_AB=?," \
			"FILIALNR=?," \
			"FROZEN=? "

 #define ARTINFNATRASTAFFELNR                0
 #define ARTINFARTIKEL_MC                    1
 #define ARTINFPACKGROESSE                   2
 #define ARTINFDARREICHFORM                  3
 #define ARTINFNORMPACKUNG                   4
 #define ARTINFEINHEIT                       5
 #define ARTINFARTIKEL_NAME                  6
 #define ARTINFVERKAUFEINHEIT                7
 #define ARTINFCONTAINERGROESSE              8
 #define ARTINFETARTKLASSE1                  9
 #define ARTINFETARTKLASSE2                  10
 #define ARTINFETARTSCHALTER1                11
 #define ARTINFETARTSCHALTER2                12
 #define ARTINFETARTSCHALTER3                13
 #define ARTINFETARTSCHALTER4                14
 #define ARTINFETARTSCHALTER5                15
 #define ARTINFHERSTELLER_NR                 16
 #define ARTINFWARENGRUPPE                   17
 #define ARTINFTHERAPIEGRUPPE                18
 #define ARTINFLAENGE                        19
 #define ARTINFHOEHE                         20
 #define ARTINFBREITE                        21
 #define ARTINFGEWICHT                       22
 #define ARTINFLAUFZEITMONATE                23
 #define ARTINFBESTAND                       24
 #define ARTINFNACHFRAGE                     25
 #define ARTINFZUZAHLUNG                     26
 #define ARTINFARTIKEL_NR                    27
 #define ARTINFRABATTFAEHIG                  28
 #define ARTINFARTIKELAKTIV                  29
 #define ARTINFVERBUNDARTIKEL                30
 #define ARTINFPRISOART                      31
 #define ARTINFHERSTELLER_CODE               32
 #define ARTINFTEXTKEY						 33
 #define ARTINFKONTIGENTMENGE				 34
 #define ARTINFBESTANDRESERVIERT			 35
 #define ARTINFSTELLER						 36
 #define ARTINFPOSITIVLISTE					 37
 #define ARTINFTAXLEVEL						 38
 #define ARTINFARTIKEL_LANGNAME				 39
 #define ARTINFARTIKEL_IMPORTARTICLE		 40
 #define ARTINFARTIKEL_WAFOTYP				 41
 #define ARTINFARTIKEL_DATUM_LIEFERBAR_AB	 42
 #define ARTINFARTIKEL_FILIALNR				 43
 #define ARTINFARTIKEL_FROZEN				 44


 #define ARTINF_ZEIGER(xxx) \
 			:xxx->NATRASTAFFELNR,\
 			:xxx->ARTIKEL_MC,\
 			:xxx->PACKGROESSE,\
 			:xxx->DARREICHFORM,\
 			:xxx->NORMPACKUNG,\
 			:xxx->EINHEIT,\
 			:xxx->ARTIKEL_NAME,\
 			:xxx->VERKAUFEINHEIT,\
 			:xxx->CONTAINERGROESSE,\
 			:xxx->ETARTKLASSE1,\
 			:xxx->ETARTKLASSE2,\
 			:xxx->ETARTSCHALTER1,\
 			:xxx->ETARTSCHALTER2,\
 			:xxx->ETARTSCHALTER3,\
 			:xxx->ETARTSCHALTER4,\
 			:xxx->ETARTSCHALTER5,\
 			:xxx->HERSTELLER_NR,\
 			:xxx->WARENGRUPPE,\
 			:xxx->THERAPIEGRUPPE,\
 			:xxx->LAENGE,\
 			:xxx->HOEHE,\
 			:xxx->BREITE,\
 			:xxx->GEWICHT,\
 			:xxx->LAUFZEITMONATE,\
 			:xxx->BESTAND,\
 			:xxx->NACHFRAGE,\
 			:xxx->ZUZAHLUNG,\
 			:xxx->ARTIKEL_NR,\
 			:xxx->RABATTFAEHIG,\
 			:xxx->ARTIKELAKTIV,\
 			:xxx->VERBUNDARTIKEL,\
 			:xxx->PRISOART,\
 			:xxx->HERSTELLER_CODE,\
 			:xxx->TEXTKEY,\
 			:xxx->KONTIGENTMENGE,\
 			:xxx->BESTANDRESERVIERT,\
 			:xxx->STELLER,\
 			:xxx->POSITIVLISTE,\
 			:xxx->TAXLEVEL,\
 			:xxx->ARTIKEL_LANGNAME,\
			:xxx->IMPORTARTICLE,\
			:xxx->WAFOTYP,\
			:xxx->DATUM_LIEFERBAR_AB,\
			:xxx->FILIALNR,\
			:xxx->FROZEN

#define ARTINF_UPDATE(xxx) \
 			NATRASTAFFELNR = :xxx->NATRASTAFFELNR,\
 			ARTIKEL_MC = :xxx->ARTIKEL_MC,\
 			PACKGROESSE = :xxx->PACKGROESSE,\
 			DARREICHFORM = :xxx->DARREICHFORM,\
 			NORMPACKUNG = :xxx->NORMPACKUNG,\
 			EINHEIT = :xxx->EINHEIT,\
 			ARTIKEL_NAME = :xxx->ARTIKEL_NAME,\
 			VERKAUFEINHEIT = :xxx->VERKAUFEINHEIT,\
 			CONTAINERGROESSE = :xxx->CONTAINERGROESSE,\
 			ETARTKLASSE1 = :xxx->ETARTKLASSE1,\
 			ETARTKLASSE2 = :xxx->ETARTKLASSE2,\
 			ETARTSCHALTER1 = :xxx->ETARTSCHALTER1,\
 			ETARTSCHALTER2 = :xxx->ETARTSCHALTER2,\
 			ETARTSCHALTER3 = :xxx->ETARTSCHALTER3,\
 			ETARTSCHALTER4 = :xxx->ETARTSCHALTER4,\
 			ETARTSCHALTER5 = :xxx->ETARTSCHALTER5,\
 			HERSTELLER_NR = :xxx->HERSTELLER_NR,\
 			WARENGRUPPE = :xxx->WARENGRUPPE,\
 			THERAPIEGRUPPE = :xxx->THERAPIEGRUPPE,\
 			LAENGE = :xxx->LAENGE,\
 			HOEHE = :xxx->HOEHE,\
 			BREITE = :xxx->BREITE,\
 			GEWICHT = :xxx->GEWICHT,\
 			LAUFZEITMONATE = :xxx->LAUFZEITMONATE,\
 			BESTAND = :xxx->BESTAND,\
 			NACHFRAGE = :xxx->NACHFRAGE,\
 			ZUZAHLUNG = :xxx->ZUZAHLUNG,\
 			ARTIKEL_NR = :xxx->ARTIKEL_NR,\
 			RABATTFAEHIG = :xxx->RABATTFAEHIG,\
 			ARTIKELAKTIV = :xxx->ARTIKELAKTIV,\
 			VERBUNDARTIKEL = :xxx->VERBUNDARTIKEL,\
 			PRISOART = :xxx->PRISOART,\
 			HERSTELLER_CODE = :xxx->HERSTELLER_CODE,\
 			TEXTKEY = :xxx->TEXTKEY,\
 			KONTIGENTMENGE = :xxx->KONTIGENTMENGE,\
 			BESTANDRESERVIERT = :xxx->BESTANDRESERVIERT,\
 			STELLER = :xxx->STELLER,\
 			POSITIVLISTE = :xxx->POSITIVLISTE,\
 			TAXLEVEL = :xxx->TAXLEVEL,\
 			ARTIKEL_LANGNAME = :xxx->ARTIKEL_LANGNAME,\
			IMPORTARTICLE = :xxx->IMPORTARTICLE,\
			WAFOTYP = :xxx->WAFOTYP,\
			DATUM_LIEFERBAR_AB = :xxx->DATUM_LIEFERBAR_AB,\
			FILIALNR = :xxx->FILIALNR,\
			FROZEN = :xxx->FROZEN

 #define LS_ARTINF_NATRASTAFFELNR       11
 #define LS_ARTINF_ARTIKEL_MC           13
 #define LS_ARTINF_PACKGROESSE          11
 #define LS_ARTINF_DARREICHFORM         4
 #define LS_ARTINF_NORMPACKUNG          3
 #define LS_ARTINF_EINHEIT              10
 #define LS_ARTINF_ARTIKEL_NAME         31
 #define LS_ARTINF_VERKAUFEINHEIT       11
 #define LS_ARTINF_CONTAINERGROESSE     11
 #define LS_ARTINF_ETARTKLASSE1         6
 #define LS_ARTINF_ETARTKLASSE2         6
 #define LS_ARTINF_ETARTSCHALTER1       6
 #define LS_ARTINF_ETARTSCHALTER2       6
 #define LS_ARTINF_ETARTSCHALTER3       6
 #define LS_ARTINF_ETARTSCHALTER4       6
 #define LS_ARTINF_ETARTSCHALTER5       6
 #define LS_ARTINF_HERSTELLER_NR        11
 #define LS_ARTINF_WARENGRUPPE          6
 #define LS_ARTINF_THERAPIEGRUPPE       6
 #define LS_ARTINF_LAENGE               11
 #define LS_ARTINF_HOEHE                11
 #define LS_ARTINF_BREITE               11
 #define LS_ARTINF_GEWICHT              11
 #define LS_ARTINF_LAUFZEITMONATE       11
 #define LS_ARTINF_BESTAND              11
 #define LS_ARTINF_NACHFRAGE            11
 #define LS_ARTINF_ZUZAHLUNG            2
 #define LS_ARTINF_ARTIKEL_NR           11
 #define LS_ARTINF_RABATTFAEHIG         3
 #define LS_ARTINF_ARTIKELAKTIV         2
 #define LS_ARTINF_VERBUNDARTIKEL       2
 #define LS_ARTINF_PRISOART             2
 #define LS_ARTINF_HERSTELLER_CODE      6
 #define LS_ARTINF_TEXTKEY				7
 #define LS_ARTINF_KONTIGENTMENGE		7
 #define LS_ARTINF_BESTANDRESERVIERT    11
 #define LS_ARTINF_STELLER		        2
 #define LS_ARTINF_POSITIVLISTE	        2
 #define LS_ARTINF_TAXLEVEL				7
 #define LS_ARTINF_ARTIKEL_LANGNAME		51
 #define LS_ARTINF_IMPORTARTICLE		7
 #define LS_ARTINF_WAFOTYP		        2
 #define LS_ARTINF_DATUM_LIEFERBAR_AB   11
 #define LS_ARTINF_FILIALNR				7
 #define LS_ARTINF_FROZEN				7
 #define LS_ARTINF_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct ARTINF {
		 long    NATRASTAFFELNR;
		 char    ARTIKEL_MC[12 + 1];
		 long    PACKGROESSE;
		 char    DARREICHFORM[3 + 1];
		 char    NORMPACKUNG[2 + 1];
		 char    EINHEIT[9 + 1];
		 char    ARTIKEL_NAME[30 + 1];
		 long    VERKAUFEINHEIT;
		 long    CONTAINERGROESSE;
		 long    ETARTKLASSE1;
		 long    ETARTKLASSE2;
		 long    ETARTSCHALTER1;
		 long    ETARTSCHALTER2;
		 long    ETARTSCHALTER3;
		 long    ETARTSCHALTER4;
		 long    ETARTSCHALTER5;
		 long    HERSTELLER_NR;
		 char    WARENGRUPPE[5 + 1];
		 char    THERAPIEGRUPPE[5 + 1];
		 long    LAENGE;
		 long    HOEHE;
		 long    BREITE;
		 long    GEWICHT;
		 long    LAUFZEITMONATE;
		 long    BESTAND;
		 long    NACHFRAGE;
		 char    ZUZAHLUNG[1 + 1];
		 long    ARTIKEL_NR;
		 char    RABATTFAEHIG[2 + 1];
		 char    ARTIKELAKTIV[1 + 1];
		 char    VERBUNDARTIKEL[1 + 1];
		 char    PRISOART[1 + 1];
		 char    HERSTELLER_CODE[5 + 1];
		 short   TEXTKEY;
		 short   KONTIGENTMENGE;
		 long    BESTANDRESERVIERT;
		 char    STELLER[1 + 1];
		 char    POSITIVLISTE[1 + 1];
		 short   TAXLEVEL;
		 char    ARTIKEL_LANGNAME[50 + 1];
		 short   IMPORTARTICLE;
		 char    WAFOTYP[1 + 1];
		 long    DATUM_LIEFERBAR_AB;
		 short   FILIALNR;
		 short   FROZEN;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_ARTINF {
		 long    NATRASTAFFELNR;
		 char    ARTIKEL_MC[12 + 1];
		 long    PACKGROESSE;
		 char    DARREICHFORM[3 + 1];
		 char    NORMPACKUNG[2 + 1];
		 char    EINHEIT[9 + 1];
		 char    ARTIKEL_NAME[30 + 1];
		 long    VERKAUFEINHEIT;
		 long    CONTAINERGROESSE;
		 long    ETARTKLASSE1;
		 long    ETARTKLASSE2;
		 long    ETARTSCHALTER1;
		 long    ETARTSCHALTER2;
		 long    ETARTSCHALTER3;
		 long    ETARTSCHALTER4;
		 long    ETARTSCHALTER5;
		 long    HERSTELLER_NR;
		 char    WARENGRUPPE[5 + 1];
		 char    THERAPIEGRUPPE[5 + 1];
		 long    LAENGE;
		 long    HOEHE;
		 long    BREITE;
		 long    GEWICHT;
		 long    LAUFZEITMONATE;
		 long    BESTAND;
		 long    NACHFRAGE;
		 char    ZUZAHLUNG;
		 long    ARTIKEL_NR;
		 char    RABATTFAEHIG[2 + 1];
		 char    ARTIKELAKTIV;
		 char    VERBUNDARTIKEL;
		 char    PRISOART;
		 char    HERSTELLER_CODE[5 + 1];
		 short   TEXTKEY;
		 short   KONTIGENTMENGE;
		 long    BESTANDRESERVIERT;
		 char    STELLER;
		 char    POSITIVLISTE;
		 short   TAXLEVEL;
		 char    ARTIKEL_LANGNAME[50 + 1];
		 short   IMPORTARTICLE;
		 char    WAFOTYP;
		 long    DATUM_LIEFERBAR_AB;
		 short   FILIALNR;
		 short   FROZEN;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_ARTINF {
		 short  NATRASTAFFELNR;
		 short  ARTIKEL_MC;
		 short  PACKGROESSE;
		 short  DARREICHFORM;
		 short  NORMPACKUNG;
		 short  EINHEIT;
		 short  ARTIKEL_NAME;
		 short  VERKAUFEINHEIT;
		 short  CONTAINERGROESSE;
		 short  ETARTKLASSE1;
		 short  ETARTKLASSE2;
		 short  ETARTSCHALTER1;
		 short  ETARTSCHALTER2;
		 short  ETARTSCHALTER3;
		 short  ETARTSCHALTER4;
		 short  ETARTSCHALTER5;
		 short  HERSTELLER_NR;
		 short  WARENGRUPPE;
		 short  THERAPIEGRUPPE;
		 short  LAENGE;
		 short  HOEHE;
		 short  BREITE;
		 short  GEWICHT;
		 short  LAUFZEITMONATE;
		 short  BESTAND;
		 short  NACHFRAGE;
		 short  ZUZAHLUNG;
		 short  ARTIKEL_NR;
		 short  RABATTFAEHIG;
		 short  ARTIKELAKTIV;
		 short  VERBUNDARTIKEL;
		 short  PRISOART;
		 short  HERSTELLER_CODE;
		 short  TEXTKEY;
		 short  KONTIGENTMENGE;
		 short  BESTANDRESERVIERT;
		 short  STELLER;
		 short  POSITIVLISTE;
		 short  TAXLEVEL;
		 short  ARTIKEL_LANGNAME;
		 short  IMPORTARTICLE;
		 short  WAFOTYP;
		 short  DATUM_LIEFERBAR_AB;
		 short  FILIALNR;
		 short  FROZEN;
		 short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_ARTINF {
		 char    NATRASTAFFELNR[11];
		 char    ARTIKEL_MC[12 + 1];
		 char    PACKGROESSE[11];
		 char    DARREICHFORM[3 + 1];
		 char    NORMPACKUNG[2 + 1];
		 char    EINHEIT[9 + 1];
		 char    ARTIKEL_NAME[30 + 1];
		 char    VERKAUFEINHEIT[11];
		 char    CONTAINERGROESSE[11];
		 char    ETARTKLASSE1[5 + 1];
		 char    ETARTKLASSE2[5 + 1];
		 char    ETARTSCHALTER1[5 + 1];
		 char    ETARTSCHALTER2[5 + 1];
		 char    ETARTSCHALTER3[5 + 1];
		 char    ETARTSCHALTER4[5 + 1];
		 char    ETARTSCHALTER5[5 + 1];
		 char    HERSTELLER_NR[11];
		 char    WARENGRUPPE[5 + 1];
		 char    THERAPIEGRUPPE[5 + 1];
		 char    LAENGE[11];
		 char    HOEHE[11];
		 char    BREITE[11];
		 char    GEWICHT[11];
		 char    LAUFZEITMONATE[11];
		 char    BESTAND[11];
		 char    NACHFRAGE[11];
		 char    ZUZAHLUNG[1 + 1];
		 char    ARTIKEL_NR[11];
		 char    RABATTFAEHIG[2 + 1];
		 char    ARTIKELAKTIV[1 + 1];
		 char    VERBUNDARTIKEL[1 + 1];
		 char    PRISOART[1 + 1];
		 char    HERSTELLER_CODE[5 + 1];
		 char    TEXTKEY[6 + 1];
		 char    KONTIGENTMENGE[6 + 1];
		 char    BESTANDRESERVIERT[11];
		 char    STELLER[1 + 1];
		 char    POSITIVLISTE[1 + 1];
		 char    TAXLEVEL[6 + 1];
		 char    ARTIKEL_LANGNAME[50 + 1];
		 char    IMPORTARTICLE[6 + 1];
		 char    WAFOTYP[1 + 1];
		 char    DATUM_LIEFERBAR_AB[11];
		 char    FILIALNR[6 + 1];
		 char    FROZEN[6 + 1];
		 char    FETCH_REL[11];
       };

 struct O_ARTINF {
		 char    NATRASTAFFELNR[11];
		 char    ARTIKEL_MC[12];
		 char    PACKGROESSE[11];
		 char    DARREICHFORM[3];
		 char    NORMPACKUNG[2];
		 char    EINHEIT[9];
		 char    ARTIKEL_NAME[30];
		 char    VERKAUFEINHEIT[11];
		 char    CONTAINERGROESSE[11];
		 char    ETARTKLASSE1[5];
		 char    ETARTKLASSE2[5];
		 char    ETARTSCHALTER1[5];
		 char    ETARTSCHALTER2[5];
		 char    ETARTSCHALTER3[5];
		 char    ETARTSCHALTER4[5];
		 char    ETARTSCHALTER5[5];
		 char    HERSTELLER_NR[11];
		 char    WARENGRUPPE[5];
		 char    THERAPIEGRUPPE[5];
		 char    LAENGE[11];
		 char    HOEHE[11];
		 char    BREITE[11];
		 char    GEWICHT[11];
		 char    LAUFZEITMONATE[11];
		 char    BESTAND[11];
		 char    NACHFRAGE[11];
		 char    ZUZAHLUNG[1];
		 char    ARTIKEL_NR[11];
		 char    RABATTFAEHIG[2];
		 char    ARTIKELAKTIV[1];
		 char    VERBUNDARTIKEL[1];
		 char    PRISOART[1];
		 char    HERSTELLER_CODE[5];
		 char    TEXTKEY[6];
		 char    KONTIGENTMENGE[6];
		 char    BESTANDRESERVIERT[11];
		 char    STELLER[1];
		 char    POSITIVLISTE[1];
		 char    TAXLEVEL[6];
		 char    ARTIKEL_LANGNAME[50];
		 char    IMPORTARTICLE[6];
		 char    WAFOTYP[1];
		 char    DATUM_LIEFERBAR_AB[11];
		 char    FILIALNR[6];
		 char    FROZEN[6];
		 char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc ARTINF_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,   12 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,   50 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTINF_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_C,   12 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_C,    3 ,   0 },
	 { TYP_C,    2 ,   0 },
	 { TYP_C,    9 ,   0 },
	 { TYP_C,   30 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_C,    5 ,   0 },
	 { TYP_C,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_C,    2 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_C,    5 ,   0 },
	 { TYP_S ,   6 ,   0 },
	 { TYP_S ,   6 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_S ,   6 ,   0 },
	 { TYP_C,   50 ,   0 },
	 { TYP_S ,   6 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_S ,   6 ,   0 },
	 { TYP_S ,   6 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CARTINF
 {
  public:

  ARTINF s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, ARTINF_BES, ARTINF_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,ARTINF_BES, ARTINF_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,ARTINF_BES, ARTINF_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CARTINF()
  {
   ::buf_default((void *)&s, ARTINF_BES, ARTINF_ANZ);
  }
 };
#endif

#define ARTINF_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 NATRASTAFFELNR INTEGER           ,\
		 ARTIKEL_MC CHAR(12)          ,\
		 PACKGROESSE INTEGER           ,\
		 DARREICHFORM CHAR(3)           ,\
		 NORMPACKUNG CHAR(2)           ,\
		 EINHEIT CHAR(9)           ,\
		 ARTIKEL_NAME CHAR(30)          ,\
		 VERKAUFEINHEIT INTEGER           ,\
		 CONTAINERGROESSE INTEGER           ,\
		 ETARTKLASSE1 INTEGER,\
		 ETARTKLASSE2 INTEGER,\
		 ETARTSCHALTER1 INTEGER,\
		 ETARTSCHALTER2 INTEGER,\
		 ETARTSCHALTER3 INTEGER,\
		 ETARTSCHALTER4 INTEGER,\
		 ETARTSCHALTER5 INTEGER,\
		 HERSTELLER_NR INTEGER           ,\
		 WARENGRUPPE CHAR(5)           ,\
		 THERAPIEGRUPPE CHAR(5)           ,\
		 LAENGE INTEGER           ,\
		 HOEHE INTEGER           ,\
		 BREITE INTEGER           ,\
		 GEWICHT INTEGER           ,\
		 LAUFZEITMONATE INTEGER           ,\
		 BESTAND INTEGER           ,\
		 NACHFRAGE INTEGER           ,\
		 ZUZAHLUNG CHAR(1)           ,\
		 ARTIKEL_NR INTEGER           ,\
		 RABATTFAEHIG CHAR(2)           ,\
		 ARTIKELAKTIV CHAR(1)           ,\
		 VERBUNDARTIKEL CHAR(1)           ,\
		 PRISOART CHAR(1)           ,\
		 HERSTELLER_CODE CHAR(5)           ,\
		 TEXTKEY SMALLINT           ,\
		 KONTIGENTMENGE SMALLINT           ,\
		 BESTANDRESERVIERT INTEGER           ,\
		 STELLER CHAR(1)           ,\
		 POSITIVLISTE CHAR(1)           ,\
		 TAXLEVEL SMALLINT           ,\
		 ARTIKEL_LANGNAME CHAR(50)          ,\
		 IMPORTARTICLE SMALLINT           ,\
		 WAFOTYP CHAR(1)           ,\
		 DATUM_LIEFERBAR_AB INTEGER           ,\
		 FILIALNR SMALLINT           ,\
		 FROZEN SMALLINT           ,\
		 FETCH_REL INTEGER  ) EXTENT SIZE 74929 LOCK MODE ROW;

#define ARTINF_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX I_ARTIKEL_1        on yyy( ARTIKEL_NR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_ARTIKEL_2        on yyy( ARTIKEL_MC );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE UNIQUE INDEX I_ARTIKEL_1        on yyy( ARTIKEL_NR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define ARTINF_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_ARTIKEL_1       ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_ARTIKEL_2       ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_ARTIKEL_1       ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_ARTINFBESTEL_BESTELL_NR           11
 #define L_ARTINFBESTEL_DATUM_BESTELL        11
 #define L_ARTINFBESTEL_DATUM_WE_SOLL        11
 #define L_ARTINFBESTEL_ARTIKEL_NR           11
 #define L_ARTINFBESTEL_MENGE_BESTELL        11
 #define L_ARTINFBESTEL_BEST_WIRKSAM         1
 #define L_ARTINFBESTEL_STATUS_AKT           1


 #define L_ARTINFBESTEL_PKEY 11

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define ARTINFBESTEL_ANZ ( sizeof(ARTINFBESTEL_BES) / sizeof(struct buf_desc) )
#endif
 #define G_ARTINFBESTEL sizeof(struct ARTINFBESTEL)


 #define ARTINFBESTEL_H

 #define ARTINFBESTEL_LISTE \
 			BESKOPF.BESTELL_NR, \
 			BESKOPF.DATUM_BESTELL, \
 			BESKOPF.DATUM_WE_SOLL, \
 			BESPOSI.ARTIKEL_NR, \
 			BESPOSI.MENGE_BESTELL, \
 			BESPOSI.BEST_WIRKSAM, \
 			BESKOPF.STATUS_AKT
 #define ARTINFBESTEL_PLISTE \
 			"BESKOPF.BESTELL_NR," \
 			"BESKOPF.DATUM_BESTELL," \
 			"BESKOPF.DATUM_WE_SOLL," \
 			"BESPOSI.ARTIKEL_NR," \
 			"BESPOSI.MENGE_BESTELL," \
 			"BESPOSI.BEST_WIRKSAM," \
 			"BESKOPF.STATUS_AKT " 

 #define ARTINFBESTEL_PELISTE \
 			"BESTELL_NR," \
 			"DATUM_BESTELL," \
 			"DATUM_WE_SOLL," \
 			"ARTIKEL_NR," \
 			"MENGE_BESTELL," \
 			"BEST_WIRKSAM," \
 			"STATUS_AKT " 

 #define ARTINFBESTEL_UPDLISTE \
 			"BESTELL_NR=?," \
 			"DATUM_BESTELL=?," \
 			"DATUM_WE_SOLL=?," \
 			"ARTIKEL_NR=?," \
 			"MENGE_BESTELL=?," \
 			"BEST_WIRKSAM=?," \
 			"STATUS_AKT=? " 

 #define ARTINFBESTELBESTELL_NR                    0
 #define ARTINFBESTELDATUM_BESTELL                 1
 #define ARTINFBESTELDATUM_WE_SOLL                 2
 #define ARTINFBESTELARTIKEL_NR                    3
 #define ARTINFBESTELMENGE_BESTELL                 4
 #define ARTINFBESTELBEST_WIRKSAM                  5
 #define ARTINFBESTELSTATUS_AKT                    6

 #define ARTINFBESTEL_ZEIGER(xxx) \
 			:xxx->BESTELL_NR,\
 			:xxx->DATUM_BESTELL,\
 			:xxx->DATUM_WE_SOLL,\
 			:xxx->ARTIKEL_NR,\
 			:xxx->MENGE_BESTELL,\
 			:xxx->BEST_WIRKSAM,\
 			:xxx->STATUS_AKT

 #define ARTINFBESTEL_UPDATE(xxx) \
 			BESTELL_NR = :xxx->BESTELL_NR,\
 			DATUM_BESTELL = :xxx->DATUM_BESTELL,\
 			DATUM_WE_SOLL = :xxx->DATUM_WE_SOLL,\
 			ARTIKEL_NR = :xxx->ARTIKEL_NR,\
 			MENGE_BESTELL = :xxx->MENGE_BESTELL,\
 			BEST_WIRKSAM = :xxx->BEST_WIRKSAM,\
 			STATUS_AKT = :xxx->STATUS_AKT

 #define LS_ARTINFBESTEL_BESTELL_NR           11
 #define LS_ARTINFBESTEL_DATUM_BESTELL        11
 #define LS_ARTINFBESTEL_DATUM_WE_SOLL        11
 #define LS_ARTINFBESTEL_ARTIKEL_NR           11
 #define LS_ARTINFBESTEL_MENGE_BESTELL        11
 #define LS_ARTINFBESTEL_BEST_WIRKSAM         2
 #define LS_ARTINFBESTEL_STATUS_AKT           2
 #define LS_ARTINFBESTEL_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct ARTINFBESTEL {
		 long    BESTELL_NR;
		 long    DATUM_BESTELL;
		 long    DATUM_WE_SOLL;
		 long    ARTIKEL_NR;
		 long    MENGE_BESTELL;
		 char    BEST_WIRKSAM[1 + 1];
		 char    STATUS_AKT[1 + 1];
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_ARTINFBESTEL {
		 long    BESTELL_NR;
		 long    DATUM_BESTELL;
		 long    DATUM_WE_SOLL;
		 long    ARTIKEL_NR;
		 long    MENGE_BESTELL;
		 char    BEST_WIRKSAM;
		 char    STATUS_AKT;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_ARTINFBESTEL {
		 short  BESTELL_NR;
		 short  DATUM_BESTELL;
		 short  DATUM_WE_SOLL;
		 short  ARTIKEL_NR;
		 short  MENGE_BESTELL;
		 short  BEST_WIRKSAM;
		 short  STATUS_AKT;
		 short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_ARTINFBESTEL {
		 char    BESTELL_NR[11];
		 char    DATUM_BESTELL[11];
		 char    DATUM_WE_SOLL[11];
		 char    ARTIKEL_NR[11];
		 char    MENGE_BESTELL[11];
		 char    BEST_WIRKSAM[1 + 1];
		 char    STATUS_AKT[1 + 1];
		 char    FETCH_REL[11];
       };

 struct O_ARTINFBESTEL {
		 char    BESTELL_NR[11];
		 char    DATUM_BESTELL[11];
		 char    DATUM_WE_SOLL[11];
		 char    ARTIKEL_NR[11];
		 char    MENGE_BESTELL[11];
		 char    BEST_WIRKSAM[1];
		 char    STATUS_AKT[1];
		 char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc ARTINFBESTEL_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTINFBESTEL_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CARTINFBESTEL
 {
  public:

  ARTINFBESTEL s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, ARTINFBESTEL_BES, ARTINFBESTEL_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,ARTINFBESTEL_BES, ARTINFBESTEL_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,ARTINFBESTEL_BES, ARTINFBESTEL_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CARTINFBESTEL()
  {
   ::buf_default((void *)&s, ARTINFBESTEL_BES, ARTINFBESTEL_ANZ);
  }
 };
#endif

#define ARTINFBESTEL_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 BESTELL_NR INTEGER           ,\
		 DATUM_BESTELL INTEGER           ,\
		 DATUM_WE_SOLL INTEGER           ,\
		 ARTIKEL_NR INTEGER           ,\
		 MENGE_BESTELL INTEGER           ,\
		 BEST_WIRKSAM CHAR(1)           ,\
		 STATUS_AKT CHAR(1)           ,\
		 FETCH_REL INTEGER  ) EXTENT SIZE 654 LOCK MODE ROW;

#define ARTINFBESTEL_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX I_BESKOPF_1        on yyy( BESTELL_NR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_BESKOPF_2        on yyy( BESTELL_NR, BESLA_NR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_BESKOPF_3        on yyy( BESTELL_NR, BESLA_NR, WE_NR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_BESKOPF_4        on yyy( BESTELL_NR, STATUS_AKT, BESLA_MC );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_BESKOPF_5        on yyy( BESTELL_NR, WE_NR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_BESKOPF_6        on yyy( BESTELL_NR, BESLA_MC );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_BESPOSI_3        on yyy( ARTIKEL_NR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define ARTINFBESTEL_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_BESKOPF_1       ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_BESKOPF_2       ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_BESKOPF_3       ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_BESKOPF_4       ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_BESKOPF_5       ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_BESKOPF_6       ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_BESPOSI_3       ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_ARTINFHERSTE_HERSTELLER_NR        11
 #define L_ARTINFHERSTE_NAME                 22
 #define L_ARTINFHERSTE_PLZ                  7
 #define L_ARTINFHERSTE_ORT                  40
 #define L_ARTINFHERSTE_STRASSE              40
 #define L_ARTINFHERSTE_POST_FACH            8
 #define L_ARTINFHERSTE_PLZ2                 7
 #define L_ARTINFHERSTE_VORWAHL              10
 #define L_ARTINFHERSTE_TELEFON_NR           15
 #define L_ARTINFHERSTE_VORWAHL_TELEFAX      10
 #define L_ARTINFHERSTE_FAX_NR               15
 #define L_ARTINFHERSTE_HOMEPAGE             60


 #define L_ARTINFHERSTE_PKEY 11

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define ARTINFHERSTE_ANZ ( sizeof(ARTINFHERSTE_BES) / sizeof(struct buf_desc) )
#endif
 #define G_ARTINFHERSTE sizeof(struct ARTINFHERSTE)


 #define ARTINFHERSTE_H

 #define ARTINFHERSTE_LISTE \
 			HERSTEL.HERSTELLER_NR, \
 			HERSTEL.NAME, \
 			HERSTEL.PLZ, \
 			HERSTEL.ORT, \
 			HERSTEL.STRASSE, \
 			HERSTEL.POST_FACH, \
 			HERSTEL.PLZ2, \
 			HERSTEL.VORWAHL, \
 			HERSTEL.TELEFON_NR, \
 			HERSTEL.VORWAHL_TELEFAX, \
 			HERSTEL.FAX_NR, \
 			HERSTEL.HOMEPAGE
 #define ARTINFHERSTE_PLISTE \
 			"HERSTEL.HERSTELLER_NR," \
 			"HERSTEL.NAME," \
 			"HERSTEL.PLZ," \
 			"HERSTEL.ORT," \
 			"HERSTEL.STRASSE," \
 			"HERSTEL.POST_FACH," \
 			"HERSTEL.PLZ2," \
 			"HERSTEL.VORWAHL," \
 			"HERSTEL.TELEFON_NR," \
 			"HERSTEL.VORWAHL_TELEFAX," \
 			"HERSTEL.FAX_NR," \
 			"HERSTEL.HOMEPAGE "

 #define ARTINFHERSTE_PELISTE \
 			"HERSTELLER_NR," \
 			"NAME," \
 			"PLZ," \
 			"ORT," \
 			"STRASSE," \
 			"POST_FACH," \
 			"PLZ2," \
 			"VORWAHL," \
 			"TELEFON_NR," \
 			"VORWAHL_TELEFAX," \
 			"FAX_NR," \
 			"HOMEPAGE "

 #define ARTINFHERSTE_UPDLISTE \
 			"HERSTELLER_NR=?," \
 			"NAME=?," \
 			"PLZ=?," \
 			"ORT=?," \
 			"STRASSE=?," \
 			"POST_FACH=?," \
 			"PLZ2=?," \
 			"VORWAHL=?," \
 			"TELEFON_NR=?," \
 			"VORWAHL_TELEFAX=?," \
 			"FAX_NR=?," \
 			"HOMEPAGE=? "

 #define ARTINFHERSTEHERSTELLER_NR                 0
 #define ARTINFHERSTENAME                          1
 #define ARTINFHERSTEPLZ                           2
 #define ARTINFHERSTEORT                           3
 #define ARTINFHERSTESTRASSE                       4
 #define ARTINFHERSTEPOST_FACH                     5
 #define ARTINFHERSTEPLZ2                          6
 #define ARTINFHERSTEVORWAHL                       7
 #define ARTINFHERSTETELEFON_NR                    8
 #define ARTINFHERSTEVORWAHL_TELEFAX               9
 #define ARTINFHERSTEFAX_NR                        10
 #define ARTINFHERSTEHOMEPAGE                      11

 #define ARTINFHERSTE_ZEIGER(xxx) \
 			:xxx->HERSTELLER_NR,\
 			:xxx->NAME,\
 			:xxx->PLZ,\
 			:xxx->ORT,\
 			:xxx->STRASSE,\
 			:xxx->POST_FACH,\
 			:xxx->PLZ2,\
 			:xxx->VORWAHL,\
 			:xxx->TELEFON_NR,\
 			:xxx->VORWAHL_TELEFAX,\
 			:xxx->FAX_NR,\
 			:xxx->HOMEPAGE

 #define ARTINFHERSTE_UPDATE(xxx) \
 			HERSTELLER_NR = :xxx->HERSTELLER_NR,\
 			NAME = :xxx->NAME,\
 			PLZ = :xxx->PLZ,\
 			ORT = :xxx->ORT,\
 			STRASSE = :xxx->STRASSE,\
 			POST_FACH = :xxx->POST_FACH,\
 			PLZ2 = :xxx->PLZ2,\
 			VORWAHL = :xxx->VORWAHL,\
 			TELEFON_NR = :xxx->TELEFON_NR,\
 			VORWAHL_TELEFAX = :xxx->VORWAHL_TELEFAX,\
 			FAX_NR = :xxx->FAX_NR,\
 			HOMEPAGE = :xxx->HOMEPAGE

 #define LS_ARTINFHERSTE_HERSTELLER_NR        11
 #define LS_ARTINFHERSTE_NAME                 23
 #define LS_ARTINFHERSTE_PLZ                  8
 #define LS_ARTINFHERSTE_ORT                  41
 #define LS_ARTINFHERSTE_STRASSE              41
 #define LS_ARTINFHERSTE_POST_FACH            9
 #define LS_ARTINFHERSTE_PLZ2                 8
 #define LS_ARTINFHERSTE_VORWAHL              11
 #define LS_ARTINFHERSTE_TELEFON_NR           16
 #define LS_ARTINFHERSTE_VORWAHL_TELEFAX      11
 #define LS_ARTINFHERSTE_FAX_NR               16
 #define LS_ARTINFHERSTE_HOMEPAGE             61

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct ARTINFHERSTE {
		 long    HERSTELLER_NR;
		 char    NAME[22 + 1];
		 char    PLZ[7 + 1];
		 char    ORT[40 + 1];
		 char    STRASSE[40 + 1];
		 char    POST_FACH[8 + 1];
		 char    PLZ2[7 + 1];
		 char    VORWAHL[10 + 1];
		 char    TELEFON_NR[15 + 1];
		 char    VORWAHL_TELEFAX[10 + 1];
		 char    FAX_NR[15 + 1];
		 char    HOMEPAGE[60 + 1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_ARTINFHERSTE {
		 long    HERSTELLER_NR;
		 char    NAME[22 + 1];
		 char    PLZ[7 + 1];
		 char    ORT[40 + 1];
		 char    STRASSE[40 + 1];
		 char    POST_FACH[8 + 1];
		 char    PLZ2[7 + 1];
		 char    VORWAHL[10 + 1];
		 char    TELEFON_NR[15 + 1];
		 char    VORWAHL_TELEFAX[10 + 1];
		 char    FAX_NR[15 + 1];
		 char    HOMEPAGE[60 + 1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_ARTINFHERSTE {
		 short  HERSTELLER_NR;
		 short  NAME;
		 short  PLZ;
		 short  ORT;
		 short  STRASSE;
		 short  POST_FACH;
		 short  PLZ2;
		 short  VORWAHL;
		 short  TELEFON_NR;
		 short  VORWAHL_TELEFAX;
		 short  FAX_NR;
		 short  HOMEPAGE;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_ARTINFHERSTE {
		 char    HERSTELLER_NR[11];
		 char    NAME[22 + 1];
		 char    PLZ[7 + 1];
		 char    ORT[40 + 1];
		 char    STRASSE[40 + 1];
		 char    POST_FACH[8 + 1];
		 char    PLZ2[7 + 1];
		 char    VORWAHL[10 + 1];
		 char    TELEFON_NR[15 + 1];
		 char    VORWAHL_TELEFAX[10 + 1];
		 char    FAX_NR[15 + 1];
		 char    HOMEPAGE[60 + 1];
       };

 struct O_ARTINFHERSTE {
		 char    HERSTELLER_NR[11];
		 char    NAME[22];
		 char    PLZ[7];
		 char    ORT[40];
		 char    STRASSE[40];
		 char    POST_FACH[8];
		 char    PLZ2[7];
		 char    VORWAHL[10];
		 char    TELEFON_NR[15];
		 char    VORWAHL_TELEFAX[10];
		 char    FAX_NR[15];
		 char    HOMEPAGE[60];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc ARTINFHERSTE_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,   22 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   40 ,   0 },
	 { TYP_C ,   40 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,   60 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTINFHERSTE_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_C,   22 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_C,   40 ,   0 },
	 { TYP_C,   40 ,   0 },
	 { TYP_C,    8 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_C,   10 ,   0 },
	 { TYP_C,   15 ,   0 },
	 { TYP_C,   10 ,   0 },
	 { TYP_C,   15 ,   0 },
	 { TYP_C,   60 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CARTINFHERSTE
 {
  public:

  ARTINFHERSTE s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, ARTINFHERSTE_BES, ARTINFHERSTE_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,ARTINFHERSTE_BES, ARTINFHERSTE_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,ARTINFHERSTE_BES, ARTINFHERSTE_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CARTINFHERSTE()
  {
   ::buf_default((void *)&s, ARTINFHERSTE_BES, ARTINFHERSTE_ANZ);
  }
 };
#endif

#define ARTINFHERSTE_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 HERSTELLER_NR INTEGER           ,\
		 NAME CHAR(22)          ,\
		 PLZ CHAR(7)           ,\
		 ORT CHAR(40)          ,\
		 STRASSE CHAR(40)          ,\
		 POST_FACH CHAR(8)           ,\
		 PLZ2 CHAR(7)           ,\
		 VORWAHL CHAR(10)          ,\
		 TELEFON_NR CHAR(15)          ,\
		 VORWAHL_TELEFAX CHAR(10)          ,\
		 FAX_NR CHAR(15)          ,\
		 HOMEPAGE CHAR(60)            ) EXTENT SIZE 182 LOCK MODE ROW;

#define ARTINFHERSTE_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX I_HERSTEL_1        on yyy( HERSTELLER_NR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define ARTINFHERSTE_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_HERSTEL_1       ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_ARTLAGER_ARTIKEL_NR           11
 #define L_ARTLAGER_LAGERBEREICHNR       6
 #define L_ARTLAGER_STATIONNR            2
 #define L_ARTLAGER_LAGERFACHNR          10
 #define L_ARTLAGER_DATUMVERFALL         11
 #define L_ARTLAGER_FILIALNR             6
 #define L_ARTLAGER_BESTAND              11
 

 #define L_ARTLAGER_PKEY 35

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define ARTLAGER_ANZ ( sizeof(ARTLAGER_BES) / sizeof(struct buf_desc) )
#endif
 #define G_ARTLAGER sizeof(struct ARTLAGER)


 #define ARTLAGER_H

 #define ARTLAGER_LISTE \
 			ARTIKELLAGERORT.ARTIKEL_NR, \
 			ARTIKELLAGERORT.LAGERBEREICHNR, \
 			ARTIKELLAGERORT.STATIONNR, \
 			ARTIKELLAGERORT.LAGERFACHNR, \
 			ARTIKELLAGERORT.DATUMVERFALL, \
 			ARTIKELLAGERORT.FILIALNR, \
 			ARTIKELLAGERORT.BESTAND 
 #define ARTLAGER_PLISTE \
 			"ARTIKELLAGERORT.ARTIKEL_NR," \
 			"ARTIKELLAGERORT.LAGERBEREICHNR," \
 			"ARTIKELLAGERORT.STATIONNR," \
 			"ARTIKELLAGERORT.LAGERFACHNR," \
 			"ARTIKELLAGERORT.DATUMVERFALL," \
 			"ARTIKELLAGERORT.FILIALNR," \
 			"ARTIKELLAGERORT.BESTAND " 

 #define ARTLAGER_PELISTE \
 			"ARTIKEL_NR," \
 			"LAGERBEREICHNR," \
 			"STATIONNR," \
 			"LAGERFACHNR," \
 			"DATUMVERFALL," \
 			"FILIALNR," \
 			"BESTAND " 

 #define ARTLAGER_UPDLISTE \
 			"ARTIKEL_NR=?," \
 			"LAGERBEREICHNR=?," \
 			"STATIONNR=?," \
 			"LAGERFACHNR=?," \
 			"DATUMVERFALL=?," \
 			"FILIALNR=?," \
 			"BESTAND=? " 

 #define ARTLAGERARTIKEL_NR                    0
 #define ARTLAGERLAGERBEREICHNR                1
 #define ARTLAGERSTATIONNR                     2
 #define ARTLAGERLAGERFACHNR                   3
 #define ARTLAGERDATUMVERFALL                  4
 #define ARTLAGERFILIALNR                      5
 #define ARTLAGERBESTAND                       6

 #define ARTLAGER_ZEIGER(xxx) \
 			:xxx->ARTIKEL_NR,\
 			:xxx->LAGERBEREICHNR,\
 			:xxx->STATIONNR,\
 			:xxx->LAGERFACHNR,\
 			:xxx->DATUMVERFALL,\
 			:xxx->FILIALNR,\
 			:xxx->BESTAND

 #define ARTLAGER_UPDATE(xxx) \
 			ARTIKEL_NR = :xxx->ARTIKEL_NR,\
 			LAGERBEREICHNR = :xxx->LAGERBEREICHNR,\
 			STATIONNR = :xxx->STATIONNR,\
 			LAGERFACHNR = :xxx->LAGERFACHNR,\
 			DATUMVERFALL = :xxx->DATUMVERFALL,\
 			FILIALNR = :xxx->FILIALNR,\
 			BESTAND = :xxx->BESTAND

 #define LS_ARTLAGER_ARTIKEL_NR           11
 #define LS_ARTLAGER_LAGERBEREICHNR       7
 #define LS_ARTLAGER_STATIONNR            3
 #define LS_ARTLAGER_LAGERFACHNR          11
 #define LS_ARTLAGER_DATUMVERFALL         11
 #define LS_ARTLAGER_FILIALNR             7
 #define LS_ARTLAGER_BESTAND              11
 #define LS_ARTLAGER_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct ARTLAGER {
		 long    ARTIKEL_NR;
		 short   LAGERBEREICHNR;
		 char    STATIONNR[2 + 1];
		 char    LAGERFACHNR[10 + 1];
		 long    DATUMVERFALL;
		 short   FILIALNR;
		 long    BESTAND;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_ARTLAGER {
		 long    ARTIKEL_NR;
		 short   LAGERBEREICHNR;
		 char    STATIONNR[2 + 1];
		 char    LAGERFACHNR[10 + 1];
		 long    DATUMVERFALL;
		 short   FILIALNR;
		 long    BESTAND;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_ARTLAGER {
		 short  ARTIKEL_NR;
		 short  LAGERBEREICHNR;
		 short  STATIONNR;
		 short  LAGERFACHNR;
		 short  DATUMVERFALL;
		 short  FILIALNR;
		 short  BESTAND;
		 short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_ARTLAGER {
		 char    ARTIKEL_NR[11];
		 char    LAGERBEREICHNR[7];
		 char    STATIONNR[2 + 1];
		 char    LAGERFACHNR[10 + 1];
		 char    DATUMVERFALL[11];
		 char    FILIALNR[7];
		 char    BESTAND[11];
		 char    FETCH_REL[11];
       };

 struct O_ARTLAGER {
		 char    ARTIKEL_NR[11];
		 char    LAGERBEREICHNR[7];
		 char    STATIONNR[2];
		 char    LAGERFACHNR[10];
		 char    DATUMVERFALL[11];
		 char    FILIALNR[7];
		 char    BESTAND[11];
		 char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc ARTLAGER_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTLAGER_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_C,    2 ,   0 },
	 { TYP_C,   10 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CARTLAGER
 {
  public:

  ARTLAGER s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, ARTLAGER_BES, ARTLAGER_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,ARTLAGER_BES, ARTLAGER_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,ARTLAGER_BES, ARTLAGER_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CARTLAGER()
  {
   ::buf_default((void *)&s, ARTLAGER_BES, ARTLAGER_ANZ);
  }
 };
#endif

#define ARTLAGER_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 ARTIKEL_NR INTEGER           ,\
		 LAGERBEREICHNR SMALLINT          ,\
		 STATIONNR CHAR(2)           ,\
		 LAGERFACHNR CHAR(10)          ,\
		 DATUMVERFALL INTEGER           ,\
		 FILIALNR SMALLINT          ,\
		 BESTAND INTEGER           ,\
		 FETCH_REL INTEGER  ) EXTENT SIZE 98495 LOCK MODE ROW;

#define ARTLAGER_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE INDEX I_ARTIKELLAGEROR_4 on yyy( ARTIKEL_NR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_ARTIKELLAGEROR_5 on yyy( FILIALNR, LAGERFACHNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_ARTIKELLAGEROR_2 on yyy( FILIALNR, ARTIKEL_NR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE UNIQUE INDEX I_ARTIKELLAGERORT_ on yyy( FILIALNR, ARTIKEL_NR, LAGERBEREICHNR, STATIONNR, LAGERFACHNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define ARTLAGER_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_ARTIKELLAGEROR_4;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_ARTIKELLAGEROR_5;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_ARTIKELLAGEROR_2;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_ARTIKELLAGERORT_;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define L_ARTPREIS_PREISEKAPO           9
 #define N_ARTPREIS_PREISEKAPO           2
 #define L_ARTPREIS_PREISEKGROSSO        9
 #define N_ARTPREIS_PREISEKGROSSO        2
 #define L_ARTPREIS_PREISEKGROSSONA      9
 #define N_ARTPREIS_PREISEKGROSSONA      2
 #define L_ARTPREIS_PREISVKAPO           9
 #define N_ARTPREIS_PREISVKAPO           2
 #define L_ARTPREIS_RABATTFEST           5
 #define N_ARTPREIS_RABATTFEST           2
 #define L_ARTPREIS_RABATTFESTDM         9
 #define N_ARTPREIS_RABATTFESTDM         2
 #define L_ARTPREIS_PREISFEST            9
 #define N_ARTPREIS_PREISFEST            2
 #define L_ARTPREIS_PREISPROZENT         5
 #define N_ARTPREIS_PREISPROZENT         2
 #define L_ARTPREIS_DATUMGUELTIGAB       11
 #define L_ARTPREIS_ARTIKEL_NR           11
 #define L_ARTPREIS_DATUMGUELTIGBIS      11
 #define L_ARTPREIS_PREISAGP             9
 #define N_ARTPREIS_PREISAGP             2
 #define L_ARTPREIS_PREIS_TYP		     6


 #define L_ARTPREIS_PKEY 22

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define ARTPREIS_ANZ ( sizeof(ARTPREIS_BES) / sizeof(struct buf_desc) )
#endif
 #define G_ARTPREIS sizeof(struct ARTPREIS)


 #define ARTPREIS_H

 #define ARTPREIS_LISTE \
 			ARTIKELPREIS.PREISEKAPO, \
 			ARTIKELPREIS.PREISEKGROSSO, \
 			ARTIKELPREIS.PREISEKGROSSONA, \
 			ARTIKELPREIS.PREISVKAPO, \
 			ARTIKELPREIS.RABATTFEST, \
 			ARTIKELPREIS.RABATTFESTDM, \
 			ARTIKELPREIS.PREISFEST, \
 			ARTIKELPREIS.PREISPROZENT, \
 			ARTIKELPREIS.DATUMGUELTIGAB, \
 			ARTIKELPREIS.ARTIKEL_NR, \
 			ARTIKELPREIS.DATUMGUELTIGBIS, \
 			ARTIKELPREIS.PREISAGP, \
 			ARTIKELPREIS.PREIS_TYP
 #define ARTPREIS_PLISTE \
 			"ARTIKELPREIS.PREISEKAPO," \
 			"ARTIKELPREIS.PREISEKGROSSO," \
 			"ARTIKELPREIS.PREISEKGROSSONA," \
 			"ARTIKELPREIS.PREISVKAPO," \
 			"ARTIKELPREIS.RABATTFEST," \
 			"ARTIKELPREIS.RABATTFESTDM," \
 			"ARTIKELPREIS.PREISFEST," \
 			"ARTIKELPREIS.PREISPROZENT," \
 			"ARTIKELPREIS.DATUMGUELTIGAB," \
 			"ARTIKELPREIS.ARTIKEL_NR," \
 			"ARTIKELPREIS.DATUMGUELTIGBIS," \
 			"ARTIKELPREIS.PREISAGP," \
 			"ARTIKELPREIS.PREIS_TYP "

 #define ARTPREIS_PELISTE \
 			"PREISEKAPO," \
 			"PREISEKGROSSO," \
 			"PREISEKGROSSONA," \
 			"PREISVKAPO," \
 			"RABATTFEST," \
 			"RABATTFESTDM," \
 			"PREISFEST," \
 			"PREISPROZENT," \
 			"DATUMGUELTIGAB," \
 			"ARTIKEL_NR," \
 			"DATUMGUELTIGBIS," \
 			"PREISEKAPO," \
 			"PREIS_TYP "

 #define ARTPREIS_UPDLISTE \
 			"PREISEKAPO=?," \
 			"PREISEKGROSSO=?," \
 			"PREISEKGROSSONA=?," \
 			"PREISVKAPO=?," \
 			"RABATTFEST=?," \
 			"RABATTFESTDM=?," \
 			"PREISFEST=?," \
 			"PREISPROZENT=?," \
 			"DATUMGUELTIGAB=?," \
 			"ARTIKEL_NR=?," \
 			"DATUMGUELTIGBIS=?," \
 			"PREISAGP=?," \
 			"PREIS_TYP=? "

 #define ARTPREISPREISEKAPO                    0
 #define ARTPREISPREISEKGROSSO                 1
 #define ARTPREISPREISEKGROSSONA               2
 #define ARTPREISPREISVKAPO                    3
 #define ARTPREISRABATTFEST                    4
 #define ARTPREISRABATTFESTDM                  5
 #define ARTPREISPREISFEST                     6
 #define ARTPREISPREISPROZENT                  7
 #define ARTPREISDATUMGUELTIGAB                8
 #define ARTPREISARTIKEL_NR                    9
 #define ARTPREISDATUMGUELTIGBIS               10
 #define ARTPREISPREISAGP                      11
 #define ARTPREISPREIS_TYP                     12

 #define ARTPREIS_ZEIGER(xxx) \
 			:xxx->PREISEKAPO,\
 			:xxx->PREISEKGROSSO,\
 			:xxx->PREISEKGROSSONA,\
 			:xxx->PREISVKAPO,\
 			:xxx->RABATTFEST,\
 			:xxx->RABATTFESTDM,\
 			:xxx->PREISFEST,\
 			:xxx->PREISPROZENT,\
 			:xxx->DATUMGUELTIGAB,\
 			:xxx->ARTIKEL_NR,\
 			:xxx->DATUMGUELTIGBIS,\
 			:xxx->PREISAGP,\
 			:xxx->PREIS_TYP

 #define ARTPREIS_UPDATE(xxx) \
 			PREISEKAPO = :xxx->PREISEKAPO,\
 			PREISEKGROSSO = :xxx->PREISEKGROSSO,\
 			PREISEKGROSSONA = :xxx->PREISEKGROSSONA,\
 			PREISVKAPO = :xxx->PREISVKAPO,\
 			RABATTFEST = :xxx->RABATTFEST,\
 			RABATTFESTDM = :xxx->RABATTFESTDM,\
 			PREISFEST = :xxx->PREISFEST,\
 			PREISPROZENT = :xxx->PREISPROZENT,\
 			DATUMGUELTIGAB = :xxx->DATUMGUELTIGAB,\
 			ARTIKEL_NR = :xxx->ARTIKEL_NR,\
 			DATUMGUELTIGBIS = :xxx->DATUMGUELTIGBIS,\
 			PREISAGP = :xxx->PREISAGP,\
 			PREIS_TYP = :xxx->PREIS_TYP

 #define LS_ARTPREIS_PREISEKAPO           11
 #define LS_ARTPREIS_PREISEKGROSSO        11
 #define LS_ARTPREIS_PREISEKGROSSONA      11
 #define LS_ARTPREIS_PREISVKAPO           11
 #define LS_ARTPREIS_RABATTFEST           7
 #define LS_ARTPREIS_RABATTFESTDM         11
 #define LS_ARTPREIS_PREISFEST            11
 #define LS_ARTPREIS_PREISPROZENT         7
 #define LS_ARTPREIS_DATUMGUELTIGAB       11
 #define LS_ARTPREIS_ARTIKEL_NR           11
 #define LS_ARTPREIS_DATUMGUELTIGBIS      11
 #define LS_ARTPREIS_PREISAGP             11
 #define LS_ARTPREIS_PREIS_TYP            7
 #define LS_ARTPREIS_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct ARTPREIS {
		 double  PREISEKAPO;
		 double  PREISEKGROSSO;
		 double  PREISEKGROSSONA;
		 double  PREISVKAPO;
		 double  RABATTFEST;
		 double  RABATTFESTDM;
		 double  PREISFEST;
		 double  PREISPROZENT;
		 long    DATUMGUELTIGAB;
		 long    ARTIKEL_NR;
		 long    DATUMGUELTIGBIS;
		 double  PREISAGP;
		 short   PREIS_TYP;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_ARTPREIS {
		 double  PREISEKAPO;
		 double  PREISEKGROSSO;
		 double  PREISEKGROSSONA;
		 double  PREISVKAPO;
		 double  RABATTFEST;
		 double  RABATTFESTDM;
		 double  PREISFEST;
		 double  PREISPROZENT;
		 long    DATUMGUELTIGAB;
		 long    ARTIKEL_NR;
		 long    DATUMGUELTIGBIS;
		 double  PREISAGP;
		 short   PREIS_TYP;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_ARTPREIS {
		 short  PREISEKAPO;
		 short  PREISEKGROSSO;
		 short  PREISEKGROSSONA;
		 short  PREISVKAPO;
		 short  RABATTFEST;
		 short  RABATTFESTDM;
		 short  PREISFEST;
		 short  PREISPROZENT;
		 short  DATUMGUELTIGAB;
		 short  ARTIKEL_NR;
		 short  DATUMGUELTIGBIS;
		 short  PREISAGP;
		 short  PREIS_TYP;
		 short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_ARTPREIS {
		 char    PREISEKAPO[9 + 2];
		 char    PREISEKGROSSO[9 + 2];
		 char    PREISEKGROSSONA[9 + 2];
		 char    PREISVKAPO[9 + 2];
		 char    RABATTFEST[5 + 2];
		 char    RABATTFESTDM[9 + 2];
		 char    PREISFEST[9 + 2];
		 char    PREISPROZENT[5 + 2];
		 char    DATUMGUELTIGAB[11];
		 char    ARTIKEL_NR[11];
		 char    DATUMGUELTIGBIS[11];
		 char    PREISAGP[9 + 2];
		 char    PREIS_TYP[7];
		 char    FETCH_REL[11];
       };

 struct O_ARTPREIS {
		 char    PREISEKAPO[9];
		 char    PREISEKGROSSO[9];
		 char    PREISEKGROSSONA[9];
		 char    PREISVKAPO[9];
		 char    RABATTFEST[5];
		 char    RABATTFESTDM[9];
		 char    PREISFEST[9];
		 char    PREISPROZENT[5];
		 char    DATUMGUELTIGAB[11];
		 char    ARTIKEL_NR[11];
		 char    DATUMGUELTIGBIS[11];
		 char    PREISAGP[9];
		 char    PREIS_TYP[7];
		 char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc ARTPREIS_BES [] =
 {
	 { TYP_D ,    9 ,   2 },
	 { TYP_D ,    9 ,   2 },
	 { TYP_D ,    9 ,   2 },
	 { TYP_D ,    9 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_D ,    9 ,   2 },
	 { TYP_D ,    9 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_D ,    9 ,   2 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTPREIS_BES [] =
 {
	 { TYP_D,    9 ,   2 },
	 { TYP_D,    9 ,   2 },
	 { TYP_D,    9 ,   2 },
	 { TYP_D,    9 ,   2 },
	 { TYP_D,    5 ,   2 },
	 { TYP_D,    9 ,   2 },
	 { TYP_D,    9 ,   2 },
	 { TYP_D,    5 ,   2 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_D,    9 ,   2 },
	 { TYP_S ,   5 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CARTPREIS
 {
  public:

  ARTPREIS s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, ARTPREIS_BES, ARTPREIS_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,ARTPREIS_BES, ARTPREIS_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,ARTPREIS_BES, ARTPREIS_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CARTPREIS()
  {
   ::buf_default((void *)&s, ARTPREIS_BES, ARTPREIS_ANZ);
  }
 };
#endif

#define ARTPREIS_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 PREISEKAPO DECIMAL(9,2)      ,\
		 PREISEKGROSSO DECIMAL(9,2)      ,\
		 PREISEKGROSSONA DECIMAL(9,2)      ,\
		 PREISVKAPO DECIMAL(9,2)      ,\
		 RABATTFEST DECIMAL(5,2)      ,\
		 RABATTFESTDM DECIMAL(9,2)      ,\
		 PREISFEST DECIMAL(9,2)      ,\
		 PREISPROZENT DECIMAL(5,2)      ,\
		 DATUMGUELTIGAB INTEGER           ,\
		 ARTIKEL_NR INTEGER           ,\
		 DATUMGUELTIGBIS INTEGER           ,\
		 PREISAGP DECIMAL(9,2)      ,\
		 PREIS_TYP SMALLINT          ,\
		 FETCH_REL INTEGER  ) EXTENT SIZE 27248 LOCK MODE ROW;

#define ARTPREIS_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX ARTIKELPREISX      on yyy( ARTIKEL_NR, DATUMGUELTIGAB );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define ARTPREIS_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX ARTIKELPREISX     ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_ARTSEL_ARTIKEL_MC           12
 #define L_ARTSEL_PACKGROESSE          11
 #define L_ARTSEL_DARREICHFORM         3
 #define L_ARTSEL_EINHEIT              9
 #define L_ARTSEL_ARTIKEL_NAME         30
 #define L_ARTSEL_ARTIKEL_NR           11
 #define L_ARTSEL_BESTAND              11
 #define L_ARTSEL_NORMPACKUNG          2
 #define L_ARTSEL_HERSTELLER_CODE      5
 #define L_ARTSEL_HERSTELLER_NR        11
 #define L_ARTSEL_IMPORTARTICLE        6


 #define L_ARTSEL_PKEY 11

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define ARTSEL_ANZ ( sizeof(ARTSEL_BES) / sizeof(struct buf_desc) )
#endif
 #define G_ARTSEL sizeof(struct ARTSEL)


 #define ARTSEL_H

 #define ARTSEL_LISTE \
 			ARTIKEL.ARTIKEL_MC, \
 			ARTIKEL.PACKGROESSE, \
 			ARTIKEL.DARREICHFORM, \
 			ARTIKEL.EINHEIT, \
 			ARTIKEL.ARTIKEL_NAME, \
 			ARTIKEL.ARTIKEL_NR, \
 			ARTIKEL.BESTAND, \
 			ARTIKEL.NORMPACKUNG, \
 			ARTIKEL.HERSTELLER_CODE, \
 			ARTIKEL.HERSTELLER_NR, \
			ARTIKEL.IMPORTARTICLE
#define ARTSEL_PLISTE \
 			"ARTIKEL.ARTIKEL_MC," \
 			"ARTIKEL.PACKGROESSE," \
 			"ARTIKEL.DARREICHFORM," \
 			"ARTIKEL.EINHEIT," \
 			"ARTIKEL.ARTIKEL_NAME," \
 			"ARTIKEL.ARTIKEL_NR," \
 			"ARTIKEL.BESTAND," \
 			"ARTIKEL.NORMPACKUNG," \
 			"ARTIKEL.HERSTELLER_CODE," \
 			"ARTIKEL.HERSTELLER_NR," \
			"ARTIKEL.IMPORTARTICLE "

 #define ARTSEL_PELISTE \
 			"ARTIKEL_MC," \
 			"PACKGROESSE," \
 			"DARREICHFORM," \
 			"EINHEIT," \
 			"ARTIKEL_NAME," \
 			"ARTIKEL_NR," \
 			"BESTAND," \
 			"NORMPACKUNG," \
 			"HERSTELLER_CODE," \
 			"HERSTELLER_NR," \
			"ARTIKEL.IMPORTARTICLE "

 #define ARTSEL_UPDLISTE \
 			"ARTIKEL_MC=?," \
 			"PACKGROESSE=?," \
 			"DARREICHFORM=?," \
 			"EINHEIT=?," \
 			"ARTIKEL_NAME=?," \
 			"ARTIKEL_NR=?," \
 			"BESTAND=?," \
 			"NORMPACKUNG=?," \
 			"HERSTELLER_CODE=?," \
 			"HERSTELLER_NR=?," \
			"IMPORTARTICLE=? "

 #define ARTSELARTIKEL_MC                    0
 #define ARTSELPACKGROESSE                   1
 #define ARTSELDARREICHFORM                  2
 #define ARTSELEINHEIT                       3
 #define ARTSELARTIKEL_NAME                  4
 #define ARTSELARTIKEL_NR                    5
 #define ARTSELBESTAND                       6
 #define ARTSELNORMPACKUNG                   7
 #define ARTSELHERSTELLER_CODE               8
 #define ARTSELHERSTELLER_NR                 9
 #define ARTSELIMPORTARTICLE                 10

 #define ARTSEL_ZEIGER(xxx) \
 			:xxx->ARTIKEL_MC,\
 			:xxx->PACKGROESSE,\
 			:xxx->DARREICHFORM,\
 			:xxx->EINHEIT,\
 			:xxx->ARTIKEL_NAME,\
 			:xxx->ARTIKEL_NR,\
 			:xxx->BESTAND,\
 			:xxx->NORMPACKUNG,\
 			:xxx->HERSTELLER_CODE,\
 			:xxx->HERSTELLER_NR,\
			:xxx->IMPORTARTICLE

 #define ARTSEL_UPDATE(xxx) \
 			ARTIKEL_MC = :xxx->ARTIKEL_MC,\
 			PACKGROESSE = :xxx->PACKGROESSE,\
 			DARREICHFORM = :xxx->DARREICHFORM,\
 			EINHEIT = :xxx->EINHEIT,\
 			ARTIKEL_NAME = :xxx->ARTIKEL_NAME,\
 			ARTIKEL_NR = :xxx->ARTIKEL_NR,\
 			BESTAND = :xxx->BESTAND,\
 			NORMPACKUNG = :xxx->NORMPACKUNG,\
 			HERSTELLER_CODE = :xxx->HERSTELLER_CODE,\
 			HERSTELLER_NR = :xxx->HERSTELLER_NR,\
			IMPORTARTICLE = :xxx->IMPORTARTICLE

 #define LS_ARTSEL_ARTIKEL_MC           13
 #define LS_ARTSEL_PACKGROESSE          11
 #define LS_ARTSEL_DARREICHFORM         4
 #define LS_ARTSEL_EINHEIT              10
 #define LS_ARTSEL_ARTIKEL_NAME         31
 #define LS_ARTSEL_ARTIKEL_NR           11
 #define LS_ARTSEL_BESTAND              11
 #define LS_ARTSEL_NORMPACKUNG          3
 #define LS_ARTSEL_HERSTELLER_CODE      6
 #define LS_ARTSEL_HERSTELLER_NR        11
 #define LS_ARTSEL_IMPORTARTICLE        7
 #define LS_ARTSEL_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct ARTSEL {
		 char    ARTIKEL_MC[12 + 1];
		 long    PACKGROESSE;
		 char    DARREICHFORM[3 + 1];
		 char    EINHEIT[9 + 1];
		 char    ARTIKEL_NAME[30 + 1];
		 long    ARTIKEL_NR;
		 long    BESTAND;
		 char    NORMPACKUNG[2 + 1];
		 char    HERSTELLER_CODE[5 + 1];
		 long    HERSTELLER_NR;
		 short   IMPORTARTICLE;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_ARTSEL {
		 char    ARTIKEL_MC[12 + 1];
		 long    PACKGROESSE;
		 char    DARREICHFORM[3 + 1];
		 char    EINHEIT[9 + 1];
		 char    ARTIKEL_NAME[30 + 1];
		 long    ARTIKEL_NR;
		 long    BESTAND;
		 char    NORMPACKUNG[2 + 1];
		 char    HERSTELLER_CODE[5 + 1];
		 long    HERSTELLER_NR;
		 short   IMPORTARTICLE;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_ARTSEL {
		 short  ARTIKEL_MC;
		 short  PACKGROESSE;
		 short  DARREICHFORM;
		 short  EINHEIT;
		 short  ARTIKEL_NAME;
		 short  ARTIKEL_NR;
		 short  BESTAND;
		 short  NORMPACKUNG;
		 short  HERSTELLER_CODE;
		 short  HERSTELLER_NR;
		 short  IMPORTARTICLE;
		 short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_ARTSEL {
		 char    ARTIKEL_MC[12 + 1];
		 char    PACKGROESSE[11];
		 char    DARREICHFORM[3 + 1];
		 char    EINHEIT[9 + 1];
		 char    ARTIKEL_NAME[30 + 1];
		 char    ARTIKEL_NR[11];
		 char    BESTAND[11];
		 char    NORMPACKUNG[2 + 1];
		 char    HERSTELLER_CODE[5 + 1];
		 char    HERSTELLER_NR[11];
		 char    IMPORTARTICLE[7];
		 char    FETCH_REL[11];
       };

 struct O_ARTSEL {
		 char    ARTIKEL_MC[12];
		 char    PACKGROESSE[11];
		 char    DARREICHFORM[3];
		 char    EINHEIT[9];
		 char    ARTIKEL_NAME[30];
		 char    ARTIKEL_NR[11];
		 char    BESTAND[11];
		 char    NORMPACKUNG[2];
		 char    HERSTELLER_CODE[5];
		 char    HERSTELLER_NR[11];
		 char    IMPORTARTICLE[7];
		 char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc ARTSEL_BES [] =
 {
	 { TYP_C ,   12 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTSEL_BES [] =
 {
	 { TYP_C,   12 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_C,    3 ,   0 },
	 { TYP_C,    9 ,   0 },
	 { TYP_C,   30 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_C,    2 ,   0 },
	 { TYP_C,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CARTSEL
 {
  public:

  ARTSEL s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, ARTSEL_BES, ARTSEL_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,ARTSEL_BES, ARTSEL_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,ARTSEL_BES, ARTSEL_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CARTSEL()
  {
   ::buf_default((void *)&s, ARTSEL_BES, ARTSEL_ANZ);
  }
 };
#endif

#define ARTSEL_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 ARTIKEL_MC CHAR(12)          ,\
		 PACKGROESSE INTEGER           ,\
		 DARREICHFORM CHAR(3)           ,\
		 EINHEIT CHAR(9)           ,\
		 ARTIKEL_NAME CHAR(30)          ,\
		 ARTIKEL_NR INTEGER           ,\
		 BESTAND INTEGER           ,\
		 NORMPACKUNG CHAR(2)           ,\
		 HERSTELLER_CODE CHAR(2)           ,\
		 HERSTELLER_NR INTEGER           ,\
		 IMPORTARTICLE SMALLINT           ,\
		 FETCH_REL INTEGER  ) EXTENT SIZE 38467 LOCK MODE ROW;

#define ARTSEL_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE INDEX I_ARTIKEL_2        on yyy( ARTIKEL_MC );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE UNIQUE INDEX I_ARTIKEL_1        on yyy( ARTIKEL_NR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define ARTSEL_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_ARTIKEL_2       ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_ARTIKEL_1       ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_ARTVERFALL_ARTIKEL_NR           11
 #define L_ARTVERFALL_FILIALNR             6
 #define L_ARTVERFALL_DATUMVERFALL         11


 #define L_ARTVERFALL_PKEY 17

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define ARTVERFALL_ANZ ( sizeof(ARTVERFALL_BES) / sizeof(struct buf_desc) )
#endif
 #define G_ARTVERFALL sizeof(struct ARTVERFALL)


 #define ARTVERFALL_H

 #define ARTVERFALL_LISTE \
 			ARTIKELLAGERORT.ARTIKEL_NR, \
 			ARTIKELLAGERORT.FILIALNR, \
 			ARTIKELLAGERORT.DATUMVERFALL
 #define ARTVERFALL_PLISTE \
 			"ARTIKELLAGERORT.ARTIKEL_NR," \
 			"ARTIKELLAGERORT.FILIALNR," \
 			"ARTIKELLAGERORT.DATUMVERFALL " 

 #define ARTVERFALL_PELISTE \
 			"ARTIKEL_NR," \
 			"FILIALNR," \
 			"DATUMVERFALL " 

 #define ARTVERFALL_UPDLISTE \
 			"ARTIKEL_NR=?," \
 			"FILIALNR=?," \
 			"DATUMVERFALL=? " 

 #define ARTVERFALLARTIKEL_NR                    0
 #define ARTVERFALLFILIALNR                      1
 #define ARTVERFALLDATUMVERFALL                  2

 #define ARTVERFALL_ZEIGER(xxx) \
 			:xxx->ARTIKEL_NR,\
 			:xxx->FILIALNR,\
 			:xxx->DATUMVERFALL

 #define ARTVERFALL_UPDATE(xxx) \
 			ARTIKEL_NR = :xxx->ARTIKEL_NR,\
 			FILIALNR = :xxx->FILIALNR,\
 			DATUMVERFALL = :xxx->DATUMVERFALL

 #define LS_ARTVERFALL_ARTIKEL_NR           11
 #define LS_ARTVERFALL_FILIALNR             7
 #define LS_ARTVERFALL_DATUMVERFALL         11
 #define LS_ARTVERFALL_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct ARTVERFALL {
		 long    ARTIKEL_NR;
		 short   FILIALNR;
		 long    DATUMVERFALL;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_ARTVERFALL {
		 long    ARTIKEL_NR;
		 short   FILIALNR;
		 long    DATUMVERFALL;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_ARTVERFALL {
		 short  ARTIKEL_NR;
		 short  FILIALNR;
		 short  DATUMVERFALL;
		 short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_ARTVERFALL {
		 char    ARTIKEL_NR[11];
		 char    FILIALNR[7];
		 char    DATUMVERFALL[11];
		 char    FETCH_REL[11];
       };

 struct O_ARTVERFALL {
		 char    ARTIKEL_NR[11];
		 char    FILIALNR[7];
		 char    DATUMVERFALL[11];
		 char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc ARTVERFALL_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTVERFALL_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CARTVERFALL
 {
  public:

  ARTVERFALL s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, ARTVERFALL_BES, ARTVERFALL_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,ARTVERFALL_BES, ARTVERFALL_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,ARTVERFALL_BES, ARTVERFALL_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CARTVERFALL()
  {
   ::buf_default((void *)&s, ARTVERFALL_BES, ARTVERFALL_ANZ);
  }
 };
#endif

#define ARTVERFALL_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 ARTIKEL_NR INTEGER           ,\
		 FILIALNR SMALLINT          ,\
		 DATUMVERFALL INTEGER           ,\
		 FETCH_REL INTEGER  ) EXTENT SIZE 60176 LOCK MODE ROW;

#define ARTVERFALL_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE INDEX I_ARTIKELLAGEROR_4 on yyy( ARTIKEL_NR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_ARTIKELLAGEROR_5 on yyy( FILIALNR, LAGERFACHNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_ARTIKELLAGEROR_2 on yyy( FILIALNR, ARTIKEL_NR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE UNIQUE INDEX I_ARTIKELLAGERORT_ on yyy( FILIALNR, ARTIKEL_NR, LAGERBEREICHNR, STATIONNR, LAGERFACHNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define ARTVERFALL_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_ARTIKELLAGEROR_4;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_ARTIKELLAGEROR_5;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_ARTIKELLAGEROR_2;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_ARTIKELLAGERORT_;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_ARTLIEFER_ARTIKEL_NR           11
 #define L_ARTLIEFER_ARTIKEL_NR_BLIEFER   16


 #define L_ARTLIEFER_PKEY 0

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define ARTLIEFER_ANZ ( sizeof(ARTLIEFER_BES) / sizeof(struct buf_desc) )
#endif
 #define G_ARTLIEFER sizeof(struct ARTLIEFER)


 #define ARTLIEFER_H

 #define ARTLIEFER_LISTE \
 			BLIEART.ARTIKEL_NR, \
 			BLIEART.ARTIKEL_NR_BLIEFER
 #define ARTLIEFER_PLISTE \
 			"BLIEART.ARTIKEL_NR," \
 			"BLIEART.ARTIKEL_NR_BLIEFER " 

 #define ARTLIEFER_PELISTE \
 			"ARTIKEL_NR," \
 			"ARTIKEL_NR_BLIEFER " 

 #define ARTLIEFER_UPDLISTE \
 			"ARTIKEL_NR=?," \
 			"ARTIKEL_NR_BLIEFER=? " 

 #define ARTLIEFERARTIKEL_NR                    0
 #define ARTLIEFERARTIKEL_NR_BLIEFER            1

 #define ARTLIEFER_ZEIGER(xxx) \
 			:xxx->ARTIKEL_NR,\
 			:xxx->ARTIKEL_NR_BLIEFER

 #define ARTLIEFER_UPDATE(xxx) \
 			ARTIKEL_NR = :xxx->ARTIKEL_NR,\
 			ARTIKEL_NR_BLIEFER = :xxx->ARTIKEL_NR_BLIEFER

 #define LS_ARTLIEFER_ARTIKEL_NR           11
 #define LS_ARTLIEFER_ARTIKEL_NR_BLIEFER   17

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct ARTLIEFER {
		 long    ARTIKEL_NR;
		 char    ARTIKEL_NR_BLIEFER[16 + 1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_ARTLIEFER {
		 long    ARTIKEL_NR;
		 char    ARTIKEL_NR_BLIEFER[16 + 1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_ARTLIEFER {
		 short  ARTIKEL_NR;
		 short  ARTIKEL_NR_BLIEFER;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_ARTLIEFER {
		 char    ARTIKEL_NR[11];
		 char    ARTIKEL_NR_BLIEFER[16 + 1];
       };

 struct O_ARTLIEFER {
		 char    ARTIKEL_NR[11];
		 char    ARTIKEL_NR_BLIEFER[16];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc ARTLIEFER_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,   16 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTLIEFER_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_C,   16 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CARTLIEFER
 {
  public:

  ARTLIEFER s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, ARTLIEFER_BES, ARTLIEFER_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,ARTLIEFER_BES, ARTLIEFER_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,ARTLIEFER_BES, ARTLIEFER_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CARTLIEFER()
  {
   ::buf_default((void *)&s, ARTLIEFER_BES, ARTLIEFER_ANZ);
  }
 };
#endif

#define ARTLIEFER_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 ARTIKEL_NR INTEGER           ,\
		 ARTIKEL_NR_BLIEFER CHAR(16)            ) EXTENT SIZE 17226 LOCK MODE ROW;

#define ARTLIEFER_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE INDEX I_BLIEART_3        on yyy( ARTIKEL_NR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define ARTLIEFER_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_BLIEART_3       ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#endif

