#ifndef __PP_ARTIKELLOKAL_H_
#define __PP_ARTIKELLOKAL_H_

/******************************************************************************/
/* v:\nordat\artikellokal *****************************************************/
/******************************************************************************/

/* Length-Define of ARTIKELLOKAL **********************************************/

  #define L_ARTIKELLOKAL_FILIALNR 6
  #define L_ARTIKELLOKAL_ARTIKEL_NR 11
  #define L_ARTIKELLOKAL_BESTAND 11
  #define L_ARTIKELLOKAL_NACHFRAGE 11
  #define L_ARTIKELLOKAL_ZUZAHLUNG 1
  #define L_ARTIKELLOKAL_RABATTFAEHIG 2
  #define L_ARTIKELLOKAL_NATRASTAFFELNR 11
  #define L_ARTIKELLOKAL_PRISOART 1
  #define L_ARTIKELLOKAL_ARTIKELAKTIV 1
  #define L_ARTIKELLOKAL_LAGERBEREICHNR 6
  #define L_ARTIKELLOKAL_STATIONNR 2
  #define L_ARTIKELLOKAL_LAGERFACHNR 10
  #define L_ARTIKELLOKAL_VERBUNDARTIKEL 1
  #define L_ARTIKELLOKAL_ETARTSCHALTER1 5
  #define L_ARTIKELLOKAL_ETARTSCHALTER2 5
  #define L_ARTIKELLOKAL_ETARTSCHALTER3 5
  #define L_ARTIKELLOKAL_ETARTSCHALTER4 5
  #define L_ARTIKELLOKAL_ETARTSCHALTER5 5
  #define L_ARTIKELLOKAL_VERKAUFEINHEIT 11
  #define L_ARTIKELLOKAL_CONTAINERGROESSE 11
  #define L_ARTIKELLOKAL_KONTIGENTMENGE 6
  #define L_ARTIKELLOKAL_CHARGENARTIKEL 1
  #define L_ARTIKELLOKAL_TEXTKEY 6
  #define L_ARTIKELLOKAL_BESTANDRESERVIERT 11
  #define L_ARTIKELLOKAL_WAFOTYP 1
  #define L_ARTIKELLOKAL_KZRANGE 1
  #define L_ARTIKELLOKAL_MORECONDITIONS 1
  #define L_ARTIKELLOKAL_BESTANDTAGESANFANG 11
  #define L_ARTIKELLOKAL_CODEBLOCAGE 1
  #define L_ARTIKELLOKAL_BLOCKEDFORRETURNS 6

/* Length/Count-Define of ARTIKELLOKAL ****************************************/

  #define LS_ARTIKELLOKAL_FILIALNR 5 + 1
  #define LS_ARTIKELLOKAL_ARTIKEL_NR 10 + 1
  #define LS_ARTIKELLOKAL_BESTAND 10 + 1
  #define LS_ARTIKELLOKAL_NACHFRAGE 10 + 1
  #define LS_ARTIKELLOKAL_ZUZAHLUNG 1 + 1
  #define LS_ARTIKELLOKAL_RABATTFAEHIG 2 + 1
  #define LS_ARTIKELLOKAL_NATRASTAFFELNR 10 + 1
  #define LS_ARTIKELLOKAL_PRISOART 1 + 1
  #define LS_ARTIKELLOKAL_ARTIKELAKTIV 1 + 1
  #define LS_ARTIKELLOKAL_LAGERBEREICHNR 5 + 1
  #define LS_ARTIKELLOKAL_STATIONNR 2 + 1
  #define LS_ARTIKELLOKAL_LAGERFACHNR 10 + 1
  #define LS_ARTIKELLOKAL_VERBUNDARTIKEL 1 + 1
  #define LS_ARTIKELLOKAL_ETARTSCHALTER1 5 + 1
  #define LS_ARTIKELLOKAL_ETARTSCHALTER2 5 + 1
  #define LS_ARTIKELLOKAL_ETARTSCHALTER3 5 + 1
  #define LS_ARTIKELLOKAL_ETARTSCHALTER4 5 + 1
  #define LS_ARTIKELLOKAL_ETARTSCHALTER5 5 + 1
  #define LS_ARTIKELLOKAL_VERKAUFEINHEIT 10 + 1
  #define LS_ARTIKELLOKAL_CONTAINERGROESSE 10 + 1
  #define LS_ARTIKELLOKAL_KONTIGENTMENGE 5 + 1
  #define LS_ARTIKELLOKAL_CHARGENARTIKEL 1 + 1
  #define LS_ARTIKELLOKAL_TEXTKEY 5 + 1
  #define LS_ARTIKELLOKAL_BESTANDRESERVIERT 10 + 1
  #define LS_ARTIKELLOKAL_WAFOTYP 1 + 1
  #define LS_ARTIKELLOKAL_KZRANGE 1 + 1
  #define LS_ARTIKELLOKAL_MORECONDITIONS 1 + 1
  #define LS_ARTIKELLOKAL_BESTANDTAGESANFANG 10 + 1
  #define LS_ARTIKELLOKAL_CODEBLOCAGE 1 + 1
  #define LS_ARTIKELLOKAL_BLOCKEDFORRETURNS 5 + 1

  #define ARTIKELLOKALFILIALNR 0
  #define ARTIKELLOKALARTIKEL_NR 1
  #define ARTIKELLOKALBESTAND 2
  #define ARTIKELLOKALNACHFRAGE 3
  #define ARTIKELLOKALZUZAHLUNG 4
  #define ARTIKELLOKALRABATTFAEHIG 5
  #define ARTIKELLOKALNATRASTAFFELNR 6
  #define ARTIKELLOKALPRISOART 7
  #define ARTIKELLOKALARTIKELAKTIV 8
  #define ARTIKELLOKALLAGERBEREICHNR 9
  #define ARTIKELLOKALSTATIONNR 10
  #define ARTIKELLOKALLAGERFACHNR 11
  #define ARTIKELLOKALVERBUNDARTIKEL 12
  #define ARTIKELLOKALETARTSCHALTER1 13
  #define ARTIKELLOKALETARTSCHALTER2 14
  #define ARTIKELLOKALETARTSCHALTER3 15
  #define ARTIKELLOKALETARTSCHALTER4 16
  #define ARTIKELLOKALETARTSCHALTER5 17
  #define ARTIKELLOKALVERKAUFEINHEIT 18
  #define ARTIKELLOKALCONTAINERGROESSE 19
  #define ARTIKELLOKALKONTIGENTMENGE 20
  #define ARTIKELLOKALCHARGENARTIKEL 21
  #define ARTIKELLOKALTEXTKEY 22
  #define ARTIKELLOKALBESTANDRESERVIERT 23
  #define ARTIKELLOKALWAFOTYP 24
  #define ARTIKELLOKALKZRANGE 25
  #define ARTIKELLOKALMORECONDITIONS 26
  #define ARTIKELLOKALBESTANDTAGESANFANG 27
  #define ARTIKELLOKALCODEBLOCAGE 28
  #define ARTIKELLOKALBLOCKEDFORRETURNS 29

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define ARTIKELLOKAL_H
 #define ARTIKELLOKAL_ANZ ( sizeof(ARTIKELLOKAL_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ARTIKELLOKAL **************************************************/

 #define ARTIKELLOKAL_LISTE \
         ARTIKELLOKAL.FILIALNR,\
         ARTIKELLOKAL.ARTIKEL_NR,\
         ARTIKELLOKAL.BESTAND,\
         ARTIKELLOKAL.NACHFRAGE,\
         ARTIKELLOKAL.ZUZAHLUNG,\
         ARTIKELLOKAL.RABATTFAEHIG,\
         ARTIKELLOKAL.NATRASTAFFELNR,\
         ARTIKELLOKAL.PRISOART,\
         ARTIKELLOKAL.ARTIKELAKTIV,\
         ARTIKELLOKAL.LAGERBEREICHNR,\
         ARTIKELLOKAL.STATIONNR,\
         ARTIKELLOKAL.LAGERFACHNR,\
         ARTIKELLOKAL.VERBUNDARTIKEL,\
         ARTIKELLOKAL.ETARTSCHALTER1,\
         ARTIKELLOKAL.ETARTSCHALTER2,\
         ARTIKELLOKAL.ETARTSCHALTER3,\
         ARTIKELLOKAL.ETARTSCHALTER4,\
         ARTIKELLOKAL.ETARTSCHALTER5,\
         ARTIKELLOKAL.VERKAUFEINHEIT,\
         ARTIKELLOKAL.CONTAINERGROESSE,\
         ARTIKELLOKAL.KONTIGENTMENGE,\
         ARTIKELLOKAL.CHARGENARTIKEL,\
         ARTIKELLOKAL.TEXTKEY,\
         ARTIKELLOKAL.BESTANDRESERVIERT,\
         ARTIKELLOKAL.WAFOTYP,\
         ARTIKELLOKAL.KZRANGE,\
         ARTIKELLOKAL.MORECONDITIONS,\
         ARTIKELLOKAL.BESTANDTAGESANFANG,\
         ARTIKELLOKAL.CODEBLOCAGE,\
		 ARTIKELLOKAL.BLOCKEDFORRETURNS

 #define ARTIKELLOKAL_LISTE_390 \
         FILIALNR,\
         ARTIKEL_NR,\
         BESTAND,\
         NACHFRAGE,\
         ZUZAHLUNG,\
         RABATTFAEHIG,\
         NATRASTAFFELNR,\
         PRISOART,\
         ARTIKELAKTIV,\
         LAGERBEREICHNR,\
         STATIONNR,\
         LAGERFACHNR,\
         VERBUNDARTIKEL,\
         ETARTSCHALTER1,\
         ETARTSCHALTER2,\
         ETARTSCHALTER3,\
         ETARTSCHALTER4,\
         ETARTSCHALTER5,\
         VERKAUFEINHEIT,\
         CONTAINERGROESSE,\
         KONTIGENTMENGE,\
         CHARGENARTIKEL,\
         TEXTKEY,\
         BESTANDRESERVIERT,\
         WAFOTYP,\
         KZRANGE,\
         MORECONDITIONS,\
         BESTANDTAGESANFANG,\
		 CODEBLOCAGE,\
		 BLOCKEDFORRETURNS

 #define ARTIKELLOKAL_PLISTE \
         "ARTIKELLOKAL.FILIALNR,"\
         "ARTIKELLOKAL.ARTIKEL_NR,"\
         "ARTIKELLOKAL.BESTAND,"\
         "ARTIKELLOKAL.NACHFRAGE,"\
         "ARTIKELLOKAL.ZUZAHLUNG,"\
         "ARTIKELLOKAL.RABATTFAEHIG,"\
         "ARTIKELLOKAL.NATRASTAFFELNR,"\
         "ARTIKELLOKAL.PRISOART,"\
         "ARTIKELLOKAL.ARTIKELAKTIV,"\
         "ARTIKELLOKAL.LAGERBEREICHNR,"\
         "ARTIKELLOKAL.STATIONNR,"\
         "ARTIKELLOKAL.LAGERFACHNR,"\
         "ARTIKELLOKAL.VERBUNDARTIKEL,"\
         "ARTIKELLOKAL.ETARTSCHALTER1,"\
         "ARTIKELLOKAL.ETARTSCHALTER2,"\
         "ARTIKELLOKAL.ETARTSCHALTER3,"\
         "ARTIKELLOKAL.ETARTSCHALTER4,"\
         "ARTIKELLOKAL.ETARTSCHALTER5,"\
         "ARTIKELLOKAL.VERKAUFEINHEIT,"\
         "ARTIKELLOKAL.CONTAINERGROESSE,"\
         "ARTIKELLOKAL.KONTIGENTMENGE,"\
         "ARTIKELLOKAL.CHARGENARTIKEL,"\
         "ARTIKELLOKAL.TEXTKEY,"\
         "ARTIKELLOKAL.BESTANDRESERVIERT,"\
         "ARTIKELLOKAL.WAFOTYP,"\
         "ARTIKELLOKAL.KZRANGE,"\
         "ARTIKELLOKAL.MORECONDITIONS,"\
         "ARTIKELLOKAL.BESTANDTAGESANFANG,"\
         "ARTIKELLOKAL.CODEBLOCAGE,"\
		 "ARTIKELLOKAL.BLOCKEDFORRETURNS"

 #define ARTIKELLOKAL_PELISTE \
         "FILIALNR,"\
         "ARTIKEL_NR,"\
         "BESTAND,"\
         "NACHFRAGE,"\
         "ZUZAHLUNG,"\
         "RABATTFAEHIG,"\
         "NATRASTAFFELNR,"\
         "PRISOART,"\
         "ARTIKELAKTIV,"\
         "LAGERBEREICHNR,"\
         "STATIONNR,"\
         "LAGERFACHNR,"\
         "VERBUNDARTIKEL,"\
         "ETARTSCHALTER1,"\
         "ETARTSCHALTER2,"\
         "ETARTSCHALTER3,"\
         "ETARTSCHALTER4,"\
         "ETARTSCHALTER5,"\
         "VERKAUFEINHEIT,"\
         "CONTAINERGROESSE,"\
         "KONTIGENTMENGE,"\
         "CHARGENARTIKEL,"\
         "TEXTKEY,"\
         "BESTANDRESERVIERT,"\
         "WAFOTYP,"\
         "KZRANGE,"\
         "MORECONDITIONS,"\
         "BESTANDTAGESANFANG,"\
         "CODEBLOCAGE,"\
		 "BLOCKEDFORRETURNS"

 #define ARTIKELLOKAL_UPDLISTE \
         "FILIALNR=?,"\
         "ARTIKEL_NR=?,"\
         "BESTAND=?,"\
         "NACHFRAGE=?,"\
         "ZUZAHLUNG=?,"\
         "RABATTFAEHIG=?,"\
         "NATRASTAFFELNR=?,"\
         "PRISOART=?,"\
         "ARTIKELAKTIV=?,"\
         "LAGERBEREICHNR=?,"\
         "STATIONNR=?,"\
         "LAGERFACHNR=?,"\
         "VERBUNDARTIKEL=?,"\
         "ETARTSCHALTER1=?,"\
         "ETARTSCHALTER2=?,"\
         "ETARTSCHALTER3=?,"\
         "ETARTSCHALTER4=?,"\
         "ETARTSCHALTER5=?,"\
         "VERKAUFEINHEIT=?,"\
         "CONTAINERGROESSE=?,"\
         "KONTIGENTMENGE=?,"\
         "CHARGENARTIKEL=?,"\
         "TEXTKEY=?,"\
         "BESTANDRESERVIERT=?,"\
         "WAFOTYP=?,"\
         "KZRANGE=?,"\
         "MORECONDITIONS=?,"\
         "BESTANDTAGESANFANG=?,"\
         "CODEBLOCAGE=?,"\
		 "BLOCKEDFORRETURNS=?"

/* SqlMacros-Define of ARTIKELLOKAL *******************************************/

 #define ARTIKELLOKAL_ZEIGER(x) \
         :x->FILIALNR,\
         :x->ARTIKEL_NR,\
         :x->BESTAND,\
         :x->NACHFRAGE,\
         :x->ZUZAHLUNG,\
         :x->RABATTFAEHIG,\
         :x->NATRASTAFFELNR,\
         :x->PRISOART,\
         :x->ARTIKELAKTIV,\
         :x->LAGERBEREICHNR,\
         :x->STATIONNR,\
         :x->LAGERFACHNR,\
         :x->VERBUNDARTIKEL,\
         :x->ETARTSCHALTER1,\
         :x->ETARTSCHALTER2,\
         :x->ETARTSCHALTER3,\
         :x->ETARTSCHALTER4,\
         :x->ETARTSCHALTER5,\
         :x->VERKAUFEINHEIT,\
         :x->CONTAINERGROESSE,\
         :x->KONTIGENTMENGE,\
         :x->CHARGENARTIKEL,\
         :x->TEXTKEY,\
         :x->BESTANDRESERVIERT,\
         :x->WAFOTYP,\
         :x->KZRANGE,\
         :x->MORECONDITIONS,\
         :x->BESTANDTAGESANFANG,\
         :x->CODEBLOCAGE,\
		 :x->BLOCKEDFORRETURNS

 #define ARTIKELLOKAL_ZEIGERSEL(x) \
         :x->FILIALNR,\
         :x->ARTIKEL_NR,\
         :x->BESTAND,\
         :x->NACHFRAGE,\
         :x->ZUZAHLUNG,\
         :x->RABATTFAEHIG,\
         :x->NATRASTAFFELNR,\
         :x->PRISOART,\
         :x->ARTIKELAKTIV,\
         :x->LAGERBEREICHNR,\
         :x->STATIONNR,\
         :x->LAGERFACHNR,\
         :x->VERBUNDARTIKEL,\
         :x->ETARTSCHALTER1,\
         :x->ETARTSCHALTER2,\
         :x->ETARTSCHALTER3,\
         :x->ETARTSCHALTER4,\
         :x->ETARTSCHALTER5,\
         :x->VERKAUFEINHEIT,\
         :x->CONTAINERGROESSE,\
         :x->KONTIGENTMENGE,\
         :x->CHARGENARTIKEL,\
         :x->TEXTKEY,\
         :x->BESTANDRESERVIERT,\
         :x->WAFOTYP,\
         :x->KZRANGE,\
         :x->MORECONDITIONS,\
         :x->BESTANDTAGESANFANG,\
         :x->CODEBLOCAGE,\
		 :x->BLOCKEDFORRETURNS

 #define ARTIKELLOKAL_UPDATE(x) \
         ARTIKELLOKAL.FILIALNR=:x->FILIALNR,\
         ARTIKELLOKAL.ARTIKEL_NR=:x->ARTIKEL_NR,\
         ARTIKELLOKAL.BESTAND=:x->BESTAND,\
         ARTIKELLOKAL.NACHFRAGE=:x->NACHFRAGE,\
         ARTIKELLOKAL.ZUZAHLUNG=:x->ZUZAHLUNG,\
         ARTIKELLOKAL.RABATTFAEHIG=:x->RABATTFAEHIG,\
         ARTIKELLOKAL.NATRASTAFFELNR=:x->NATRASTAFFELNR,\
         ARTIKELLOKAL.PRISOART=:x->PRISOART,\
         ARTIKELLOKAL.ARTIKELAKTIV=:x->ARTIKELAKTIV,\
         ARTIKELLOKAL.LAGERBEREICHNR=:x->LAGERBEREICHNR,\
         ARTIKELLOKAL.STATIONNR=:x->STATIONNR,\
         ARTIKELLOKAL.LAGERFACHNR=:x->LAGERFACHNR,\
         ARTIKELLOKAL.VERBUNDARTIKEL=:x->VERBUNDARTIKEL,\
         ARTIKELLOKAL.ETARTSCHALTER1=:x->ETARTSCHALTER1,\
         ARTIKELLOKAL.ETARTSCHALTER2=:x->ETARTSCHALTER2,\
         ARTIKELLOKAL.ETARTSCHALTER3=:x->ETARTSCHALTER3,\
         ARTIKELLOKAL.ETARTSCHALTER4=:x->ETARTSCHALTER4,\
         ARTIKELLOKAL.ETARTSCHALTER5=:x->ETARTSCHALTER5,\
         ARTIKELLOKAL.VERKAUFEINHEIT=:x->VERKAUFEINHEIT,\
         ARTIKELLOKAL.CONTAINERGROESSE=:x->CONTAINERGROESSE,\
         ARTIKELLOKAL.KONTIGENTMENGE=:x->KONTIGENTMENGE,\
         ARTIKELLOKAL.CHARGENARTIKEL=:x->CHARGENARTIKEL,\
         ARTIKELLOKAL.TEXTKEY=:x->TEXTKEY,\
         ARTIKELLOKAL.BESTANDRESERVIERT=:x->BESTANDRESERVIERT,\
         ARTIKELLOKAL.WAFOTYP=:x->WAFOTYP,\
         ARTIKELLOKAL.KZRANGE=:x->KZRANGE,\
         ARTIKELLOKAL.MORECONDITIONS=:x->MORECONDITIONS,\
         ARTIKELLOKAL.BESTANDTAGESANFANG=:x->BESTANDTAGESANFANG,\
         ARTIKELLOKAL.CODEBLOCAGE=:x->CODEBLOCAGE,\
		 ARTIKELLOKAL.BLOCKEDFORRETURNS=:x->BLOCKEDFORRETURNS

/* SqlMacros390-Define of ARTIKELLOKAL ****************************************/

 #define ARTIKELLOKAL_ZEIGER_390 \
         :FILIALNR,\
         :ARTIKEL_NR,\
         :BESTAND,\
         :NACHFRAGE,\
         :ZUZAHLUNG,\
         :RABATTFAEHIG,\
         :NATRASTAFFELNR,\
         :PRISOART,\
         :ARTIKELAKTIV,\
         :LAGERBEREICHNR,\
         :STATIONNR,\
         :LAGERFACHNR,\
         :VERBUNDARTIKEL,\
         :ETARTSCHALTER1,\
         :ETARTSCHALTER2,\
         :ETARTSCHALTER3,\
         :ETARTSCHALTER4,\
         :ETARTSCHALTER5,\
         :VERKAUFEINHEIT,\
         :CONTAINERGROESSE,\
         :KONTIGENTMENGE,\
         :CHARGENARTIKEL,\
         :TEXTKEY,\
         :BESTANDRESERVIERT,\
         :WAFOTYP,\
         :KZRANGE,\
         :MORECONDITIONS,\
         :BESTANDTAGESANFANG,\
         :CODEBLOCAGE,\
		 :BLOCKEDFORRETURNS

 #define ARTIKELLOKAL_UPDATE_390 \
         FILIALNR=:FILIALNR,\
         ARTIKEL_NR=:ARTIKEL_NR,\
         BESTAND=:BESTAND,\
         NACHFRAGE=:NACHFRAGE,\
         ZUZAHLUNG=:ZUZAHLUNG,\
         RABATTFAEHIG=:RABATTFAEHIG,\
         NATRASTAFFELNR=:NATRASTAFFELNR,\
         PRISOART=:PRISOART,\
         ARTIKELAKTIV=:ARTIKELAKTIV,\
         LAGERBEREICHNR=:LAGERBEREICHNR,\
         STATIONNR=:STATIONNR,\
         LAGERFACHNR=:LAGERFACHNR,\
         VERBUNDARTIKEL=:VERBUNDARTIKEL,\
         ETARTSCHALTER1=:ETARTSCHALTER1,\
         ETARTSCHALTER2=:ETARTSCHALTER2,\
         ETARTSCHALTER3=:ETARTSCHALTER3,\
         ETARTSCHALTER4=:ETARTSCHALTER4,\
         ETARTSCHALTER5=:ETARTSCHALTER5,\
         VERKAUFEINHEIT=:VERKAUFEINHEIT,\
         CONTAINERGROESSE=:CONTAINERGROESSE,\
         KONTIGENTMENGE=:KONTIGENTMENGE,\
         CHARGENARTIKEL=:CHARGENARTIKEL,\
         TEXTKEY=:TEXTKEY,\
         BESTANDRESERVIERT=:BESTANDRESERVIERT,\
         WAFOTYP=:WAFOTYP,\
         KZRANGE=:KZRANGE,\
         MORECONDITIONS=:MORECONDITIONS,\
         BESTANDTAGESANFANG=:BESTANDTAGESANFANG,\
         CODEBLOCAGE=:CODEBLOCAGE,\
		 BLOCKEDFORRETURNS=:BLOCKEDFORRETURNS

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of ARTIKELLOKAL *******************************************/

 #ifndef TRANSCLASS
 typedef struct N_ARTIKELLOKAL {
         short FILIALNR;
         long ARTIKEL_NR;
         long BESTAND;
         long NACHFRAGE;
         char ZUZAHLUNG[2];
         char RABATTFAEHIG[3];
         long NATRASTAFFELNR;
         char PRISOART[2];
         char ARTIKELAKTIV[2];
         short LAGERBEREICHNR;
         char STATIONNR[3];
         char LAGERFACHNR[11];
         char VERBUNDARTIKEL[2];
         long ETARTSCHALTER1;
         long ETARTSCHALTER2;
         long ETARTSCHALTER3;
         long ETARTSCHALTER4;
         long ETARTSCHALTER5;
         long VERKAUFEINHEIT;
         long CONTAINERGROESSE;
         short KONTIGENTMENGE;
         char CHARGENARTIKEL[2];
         short TEXTKEY;
         long BESTANDRESERVIERT;
         char WAFOTYP[2];
         char KZRANGE[2];
         char MORECONDITIONS[2];
         long BESTANDTAGESANFANG;
         char CODEBLOCAGE[2];
		 short BLOCKEDFORRETURNS;
        } artikellokalS;
 #else /*TRANSCLASS*/
 typedef struct N_ARTIKELLOKAL {
         short FILIALNR;
         long ARTIKEL_NR;
         long BESTAND;
         long NACHFRAGE;
         char ZUZAHLUNG[2];
         char RABATTFAEHIG[3];
         long NATRASTAFFELNR;
         char PRISOART[2];
         char ARTIKELAKTIV[2];
         short LAGERBEREICHNR;
         char STATIONNR[3];
         char LAGERFACHNR[11];
         char VERBUNDARTIKEL[2];
         long ETARTSCHALTER1;
         long ETARTSCHALTER2;
         long ETARTSCHALTER3;
         long ETARTSCHALTER4;
         long ETARTSCHALTER5;
         long VERKAUFEINHEIT;
         long CONTAINERGROESSE;
         short KONTIGENTMENGE;
         char CHARGENARTIKEL[2];
         short TEXTKEY;
         long BESTANDRESERVIERT;
         char WAFOTYP[2];
         char KZRANGE[2];
         char MORECONDITIONS[2];
         long BESTANDTAGESANFANG;
         char CODEBLOCAGE[2];
		 short BLOCKEDFORRETURNS;

                        bool operator==(const N_ARTIKELLOKAL& right) const {
                        return(
                                FILIALNR == right.FILIALNR &&
                                ARTIKEL_NR == right.ARTIKEL_NR &&
                                BESTAND == right.BESTAND &&
                                NACHFRAGE == right.NACHFRAGE &&
                                !strcmp(ZUZAHLUNG, right.ZUZAHLUNG) &&
                                !strcmp(RABATTFAEHIG, right.RABATTFAEHIG) &&
                                NATRASTAFFELNR == right.NATRASTAFFELNR &&
                                !strcmp(PRISOART, right.PRISOART) &&
                                !strcmp(ARTIKELAKTIV, right.ARTIKELAKTIV) &&
                                LAGERBEREICHNR == right.LAGERBEREICHNR &&
                                !strcmp(STATIONNR, right.STATIONNR) &&
                                !strcmp(LAGERFACHNR, right.LAGERFACHNR) &&
                                !strcmp(VERBUNDARTIKEL, right.VERBUNDARTIKEL) &&
                                ETARTSCHALTER1 == right.ETARTSCHALTER1 &&
                                ETARTSCHALTER2 == right.ETARTSCHALTER2 &&
                                ETARTSCHALTER3 == right.ETARTSCHALTER3 &&
                                ETARTSCHALTER4 == right.ETARTSCHALTER4 &&
                                ETARTSCHALTER5 == right.ETARTSCHALTER5 &&
                                VERKAUFEINHEIT == right.VERKAUFEINHEIT &&
                                CONTAINERGROESSE == right.CONTAINERGROESSE &&
                                KONTIGENTMENGE == right.KONTIGENTMENGE &&
                                !strcmp(CHARGENARTIKEL, right.CHARGENARTIKEL) &&
                                TEXTKEY == right.TEXTKEY &&
                                BESTANDRESERVIERT == right.BESTANDRESERVIERT &&
                                !strcmp(WAFOTYP, right.WAFOTYP) &&
                                !strcmp(KZRANGE, right.KZRANGE) &&
                                !strcmp(MORECONDITIONS, right.MORECONDITIONS) &&
                                BESTANDTAGESANFANG == right.BESTANDTAGESANFANG &&
                                !strcmp(CODEBLOCAGE, right.CODEBLOCAGE)
								BLOCKEDFORRETURNS == right.BLOCKEDFORRETURNS
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                FILIALNR = 0;
                                ARTIKEL_NR = 0;
                                BESTAND = 0;
                                NACHFRAGE = 0;
                                strcpy(ZUZAHLUNG, " " );
                                strcpy(RABATTFAEHIG, " " );
                                NATRASTAFFELNR = 0;
                                strcpy(PRISOART, " " );
                                strcpy(ARTIKELAKTIV, " " );
                                LAGERBEREICHNR = 0;
                                strcpy(STATIONNR, " " );
                                strcpy(LAGERFACHNR, " " );
                                strcpy(VERBUNDARTIKEL, " " );
                                ETARTSCHALTER1 = 0;
                                ETARTSCHALTER2 = 0;
                                ETARTSCHALTER3 = 0;
                                ETARTSCHALTER4 = 0;
                                ETARTSCHALTER5 = 0;
                                VERKAUFEINHEIT = 0;
                                CONTAINERGROESSE = 0;
                                KONTIGENTMENGE = 0;
                                strcpy(CHARGENARTIKEL, " " );
                                TEXTKEY = 0;
                                BESTANDRESERVIERT = 0;
                                strcpy(WAFOTYP, " " );
                                strcpy(KZRANGE, " " );
                                strcpy(MORECONDITIONS, " " );
                                BESTANDTAGESANFANG = 0;
                                strcpy(CODEBLOCAGE, " " );
								BLOCKEDFORRETURNS = 0;
#endif
                        }
         } artikellokalS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ARTIKELLOKAL **************************************/

 struct S_ARTIKELLOKAL {
         char FILIALNR[7];
         char ARTIKEL_NR[11];
         char BESTAND[11];
         char NACHFRAGE[11];
         char ZUZAHLUNG[1 + 1];
         char RABATTFAEHIG[2 + 1];
         char NATRASTAFFELNR[11];
         char PRISOART[1 + 1];
         char ARTIKELAKTIV[1 + 1];
         char LAGERBEREICHNR[7];
         char STATIONNR[2 + 1];
         char LAGERFACHNR[10 + 1];
         char VERBUNDARTIKEL[1 + 1];
         char ETARTSCHALTER1[5 + 1];
         char ETARTSCHALTER2[5 + 1];
         char ETARTSCHALTER3[5 + 1];
         char ETARTSCHALTER4[5 + 1];
         char ETARTSCHALTER5[5 + 1];
         char VERKAUFEINHEIT[11];
         char CONTAINERGROESSE[11];
         char KONTIGENTMENGE[7];
         char CHARGENARTIKEL[1 + 1];
         char TEXTKEY[7];
         char BESTANDRESERVIERT[11];
         char WAFOTYP[1 + 1];
         char KZRANGE[1 + 1];
         char MORECONDITIONS[1 + 1];
         char BESTANDTAGESANFANG[11];
         char CODEBLOCAGE[1 + 1];
		 char BLOCKEDFORRETURNS[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ARTIKELLOKAL *********************/

 struct O_ARTIKELLOKAL {
         char FILIALNR[7];
         char ARTIKEL_NR[11];
         char BESTAND[11];
         char NACHFRAGE[11];
         char ZUZAHLUNG[1];
         char RABATTFAEHIG[2];
         char NATRASTAFFELNR[11];
         char PRISOART[1];
         char ARTIKELAKTIV[1];
         char LAGERBEREICHNR[7];
         char STATIONNR[2];
         char LAGERFACHNR[10];
         char VERBUNDARTIKEL[1];
         char ETARTSCHALTER1[5];
         char ETARTSCHALTER2[5];
         char ETARTSCHALTER3[5];
         char ETARTSCHALTER4[5];
         char ETARTSCHALTER5[5];
         char VERKAUFEINHEIT[11];
         char CONTAINERGROESSE[11];
         char KONTIGENTMENGE[7];
         char CHARGENARTIKEL[1];
         char TEXTKEY[7];
         char BESTANDRESERVIERT[11];
         char WAFOTYP[1];
         char KZRANGE[1];
         char MORECONDITIONS[1];
         char BESTANDTAGESANFANG[11];
         char CODEBLOCAGE[1];
		 char BLOCKEDFORRETURNS[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ARTIKELLOKAL ********************************/

 struct C_ARTIKELLOKAL {
         short FILIALNR;
         long ARTIKEL_NR;
         long BESTAND;
         long NACHFRAGE;
         char ZUZAHLUNG;
         char RABATTFAEHIG[3];
         long NATRASTAFFELNR;
         char PRISOART;
         char ARTIKELAKTIV;
         short LAGERBEREICHNR;
         char STATIONNR[3];
         char LAGERFACHNR[11];
         char VERBUNDARTIKEL;
         long ETARTSCHALTER1;
         long ETARTSCHALTER2;
         long ETARTSCHALTER3;
         long ETARTSCHALTER4;
         long ETARTSCHALTER5;
         long VERKAUFEINHEIT;
         long CONTAINERGROESSE;
         short KONTIGENTMENGE;
         char CHARGENARTIKEL;
         short TEXTKEY;
         long BESTANDRESERVIERT;
         char WAFOTYP;
         char KZRANGE;
         char MORECONDITIONS;
         long BESTANDTAGESANFANG;
         char CODEBLOCAGE;
		 short BLOCKEDFORRETURNS;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ARTIKELLOKAL ******************************/

 struct I_ARTIKELLOKAL {
         short FILIALNR;
         short ARTIKEL_NR;
         short BESTAND;
         short NACHFRAGE;
         short ZUZAHLUNG;
         short RABATTFAEHIG;
         short NATRASTAFFELNR;
         short PRISOART;
         short ARTIKELAKTIV;
         short LAGERBEREICHNR;
         short STATIONNR;
         short LAGERFACHNR;
         short VERBUNDARTIKEL;
         short ETARTSCHALTER1;
         short ETARTSCHALTER2;
         short ETARTSCHALTER3;
         short ETARTSCHALTER4;
         short ETARTSCHALTER5;
         short VERKAUFEINHEIT;
         short CONTAINERGROESSE;
         short KONTIGENTMENGE;
         short CHARGENARTIKEL;
         short TEXTKEY;
         short BESTANDRESERVIERT;
         short WAFOTYP;
         short KZRANGE;
         short MORECONDITIONS;
         short BESTANDTAGESANFANG;
         short CODEBLOCAGE;
		 short BLOCKEDFORRETURNS;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ARTIKELLOKAL ****************************************/

#if defined (BUF_DESC)
 static struct buf_desc ARTIKELLOKAL_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 2, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 10, 0 },
   { TYP_C, 1, 0 },
   { TYP_L ,  11, 0 },
   { TYP_L ,  11, 0 },
   { TYP_L ,  11, 0 },
   { TYP_L ,  11, 0 },
   { TYP_L ,  11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTIKELLOKAL_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 2, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 10, 0 },
   { TYP_C, 1, 0 },
   { TYP_L ,  11, 0 },
   { TYP_L ,  11, 0 },
   { TYP_L ,  11, 0 },
   { TYP_L ,  11, 0 },
   { TYP_L ,  11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
 };
#endif

/* description for datatypes of ARTIKELLOKAL **********************************/

 #define ARTIKELLOKAL_S390 \
         short FILIALNR; \
         long ARTIKEL_NR; \
         long BESTAND; \
         long NACHFRAGE; \
         char ZUZAHLUNG; \
         char RABATTFAEHIG[3]; \
         long NATRASTAFFELNR; \
         char PRISOART; \
         char ARTIKELAKTIV; \
         short LAGERBEREICHNR; \
         char STATIONNR[3]; \
         char LAGERFACHNR[11]; \
         char VERBUNDARTIKEL; \
         long ETARTSCHALTER1; \
         long ETARTSCHALTER2; \
         long ETARTSCHALTER3; \
         long ETARTSCHALTER4; \
         long ETARTSCHALTER5; \
         long VERKAUFEINHEIT; \
         long CONTAINERGROESSE; \
         short KONTIGENTMENGE; \
         char CHARGENARTIKEL; \
         short TEXTKEY; \
         long BESTANDRESERVIERT; \
         char WAFOTYP; \
         char KZRANGE; \
         char MORECONDITIONS; \
         long BESTANDTAGESANFANG; \
         char CODEBLOCAGE; \
		 short BLOCKEDFORRETURNS; \

/* Copy-Function Struct to single Data ARTIKELLOKAL ***************************/

 #define ARTIKELLOKAL_S390_COPY_TO_SINGLE(_x_) \
         FILIALNR=_x_->FILIALNR;\
         ARTIKEL_NR=_x_->ARTIKEL_NR;\
         BESTAND=_x_->BESTAND;\
         NACHFRAGE=_x_->NACHFRAGE;\
         ZUZAHLUNG=_x_->ZUZAHLUNG;\
          strcpy(RABATTFAEHIG,_x_->RABATTFAEHIG);\
         NATRASTAFFELNR=_x_->NATRASTAFFELNR;\
         PRISOART=_x_->PRISOART;\
         ARTIKELAKTIV=_x_->ARTIKELAKTIV;\
         LAGERBEREICHNR=_x_->LAGERBEREICHNR;\
          strcpy(STATIONNR,_x_->STATIONNR);\
          strcpy(LAGERFACHNR,_x_->LAGERFACHNR);\
         VERBUNDARTIKEL=_x_->VERBUNDARTIKEL;\
         ETARTSCHALTER1=_x_->ETARTSCHALTER1;\
         ETARTSCHALTER2=_x_->ETARTSCHALTER2;\
         ETARTSCHALTER3=_x_->ETARTSCHALTER3;\
         ETARTSCHALTER4=_x_->ETARTSCHALTER4;\
         ETARTSCHALTER5=_x_->ETARTSCHALTER5;\
         VERKAUFEINHEIT=_x_->VERKAUFEINHEIT;\
         CONTAINERGROESSE=_x_->CONTAINERGROESSE;\
         KONTIGENTMENGE=_x_->KONTIGENTMENGE;\
         CHARGENARTIKEL=_x_->CHARGENARTIKEL;\
         TEXTKEY=_x_->TEXTKEY;\
         BESTANDRESERVIERT=_x_->BESTANDRESERVIERT;\
         WAFOTYP=_x_->WAFOTYP;\
         KZRANGE=_x_->KZRANGE;\
         MORECONDITIONS=_x_->MORECONDITIONS;\
         BESTANDTAGESANFANG=_x_->BESTANDTAGESANFANG;\
         CODEBLOCAGE=_x_->CODEBLOCAGE;\
		BLOCKEDFORRETURNS=_x_->BLOCKEDFORRETURNS;\

 #define ARTIKELLOKAL_S390_COPY_TO_STRUCT(_x_) \
          _x_->FILIALNR=FILIALNR;\
          _x_->ARTIKEL_NR=ARTIKEL_NR;\
          _x_->BESTAND=BESTAND;\
          _x_->NACHFRAGE=NACHFRAGE;\
          _x_->ZUZAHLUNG=ZUZAHLUNG;\
          strcpy(_x_->RABATTFAEHIG,RABATTFAEHIG);\
          _x_->NATRASTAFFELNR=NATRASTAFFELNR;\
          _x_->PRISOART=PRISOART;\
          _x_->ARTIKELAKTIV=ARTIKELAKTIV;\
          _x_->LAGERBEREICHNR=LAGERBEREICHNR;\
          strcpy(_x_->STATIONNR,STATIONNR);\
          strcpy(_x_->LAGERFACHNR,LAGERFACHNR);\
          _x_->VERBUNDARTIKEL=VERBUNDARTIKEL;\
          _x_->ETARTSCHALTER1=ETARTSCHALTER1;\
          _x_->ETARTSCHALTER2=ETARTSCHALTER2;\
          _x_->ETARTSCHALTER3=ETARTSCHALTER3;\
          _x_->ETARTSCHALTER4=ETARTSCHALTER4;\
          _x_->ETARTSCHALTER5=ETARTSCHALTER5;\
          _x_->VERKAUFEINHEIT=VERKAUFEINHEIT;\
          _x_->CONTAINERGROESSE=CONTAINERGROESSE;\
          _x_->KONTIGENTMENGE=KONTIGENTMENGE;\
          _x_->CHARGENARTIKEL=CHARGENARTIKEL;\
          _x_->TEXTKEY=TEXTKEY;\
          _x_->BESTANDRESERVIERT=BESTANDRESERVIERT;\
          _x_->WAFOTYP=WAFOTYP;\
          _x_->KZRANGE=KZRANGE;\
          _x_->MORECONDITIONS=MORECONDITIONS;\
          _x_->BESTANDTAGESANFANG=BESTANDTAGESANFANG;\
          _x_->CODEBLOCAGE=CODEBLOCAGE;\
		  _x_->BLOCKEDFORRETURNS=BLOCKEDFORRETURNS;\



/* FunctionNumber-Define of artikellokal **************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of artikellokal **********************************/


#endif

/* C++ Class ******************************************************************/

#ifdef TRANSCLASS
#include<vector>
using namespace std;

#ifndef __VIRTUAL_DADE_CLASS__
#define __VIRTUAL_DADE_CLASS__

class ppDadeVirtual
{
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

class CARTIKELLOKAL : public ppDadeVirtual
{
        //data members
        public:
                artikellokalS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<artikellokalS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<artikellokalS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<artikellokalS>; Strip(s); artikellokalS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<artikellokalS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<artikellokalS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<artikellokalS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                short           GetFilialnr() const     { return s.FILIALNR; }
                long            GetArtikel_nr() const   { return s.ARTIKEL_NR; }
                long            GetBestand() const      { return s.BESTAND; }
                long            GetNachfrage() const    { return s.NACHFRAGE; }
                char            GetZuzahlung() const    { return s.ZUZAHLUNG[0]; }
                const char*     GetRabattfaehig(ppString& t) const      { t = s.RABATTFAEHIG; t.erasespace(ppString::END); return t.c_str(); }
                long            GetNatrastaffelnr() const       { return s.NATRASTAFFELNR; }
                char            GetPrisoart() const     { return s.PRISOART[0]; }
                char            GetArtikelaktiv() const { return s.ARTIKELAKTIV[0]; }
                short           GetLagerbereichnr() const       { return s.LAGERBEREICHNR; }
                const char*     GetStationnr(ppString& t) const         { t = s.STATIONNR; t.erasespace(ppString::END); return t.c_str(); }
                const char*     GetLagerfachnr(ppString& t) const       { t = s.LAGERFACHNR; t.erasespace(ppString::END); return t.c_str(); }
                char            GetVerbundartikel() const       { return s.VERBUNDARTIKEL[0]; }
                long            GetEtartschalter1() const       { return s.ETARTSCHALTER1; }
                long            GetEtartschalter2() const       { return s.ETARTSCHALTER2; }
                long            GetEtartschalter3() const       { return s.ETARTSCHALTER3; }
                long            GetEtartschalter4() const       { return s.ETARTSCHALTER4; }
                long            GetEtartschalter5() const       { return s.ETARTSCHALTER5; }
                long            GetVerkaufeinheit() const       { return s.VERKAUFEINHEIT; }
                long            GetContainergroesse() const     { return s.CONTAINERGROESSE; }
                short           GetKontigentmenge() const       { return s.KONTIGENTMENGE; }
                char            GetChargenartikel() const       { return s.CHARGENARTIKEL[0]; }
                short           GetTextkey() const      { return s.TEXTKEY; }
                long            GetBestandreserviert() const    { return s.BESTANDRESERVIERT; }
                char            GetWafotyp() const      { return s.WAFOTYP[0]; }
                char            GetKzrange() const      { return s.KZRANGE[0]; }
                char            GetMoreconditions() const       { return s.MORECONDITIONS[0]; }
                long            GetBestandtagesanfang() const   { return s.BESTANDTAGESANFANG; }
                char            GetCodeblocage() const  { return s.CODEBLOCAGE[0]; }
				short			GetBlockedforreturns() const { return s.BLOCKEDFORRETURNS; }
                const artikellokalS& GetStruct() const { return s; }
                void            SetFilialnr(short t) { s.FILIALNR = t; }
                void            SetArtikel_nr(long t) { s.ARTIKEL_NR = t; }
                void            SetBestand(long t) { s.BESTAND = t; }
                void            SetNachfrage(long t) { s.NACHFRAGE = t; }
                void            SetZuzahlung(char t) { s.ZUZAHLUNG[0] = t; s.ZUZAHLUNG[1] = '\0';}
                void            SetRabattfaehig(const ppString& t) { ppGStrCopy(s.RABATTFAEHIG,t.c_str() ,L_ARTIKELLOKAL_RABATTFAEHIG); }
                void            SetNatrastaffelnr(long t) { s.NATRASTAFFELNR = t; }
                void            SetPrisoart(char t) { s.PRISOART[0] = t; s.PRISOART[1] = '\0';}
                void            SetArtikelaktiv(char t) { s.ARTIKELAKTIV[0] = t; s.ARTIKELAKTIV[1] = '\0';}
                void            SetLagerbereichnr(short t) { s.LAGERBEREICHNR = t; }
                void            SetStationnr(const ppString& t) { ppGStrCopy(s.STATIONNR,t.c_str() ,L_ARTIKELLOKAL_STATIONNR); }
                void            SetLagerfachnr(const ppString& t) { ppGStrCopy(s.LAGERFACHNR,t.c_str() ,L_ARTIKELLOKAL_LAGERFACHNR); }
                void            SetVerbundartikel(char t) { s.VERBUNDARTIKEL[0] = t; s.VERBUNDARTIKEL[1] = '\0';}
                void            SetEtartschalter1(long t) { s.ETARTSCHALTER1 = t; }
                void            SetEtartschalter2(long t) { s.ETARTSCHALTER2 = t; }
                void            SetEtartschalter3(long t) { s.ETARTSCHALTER3 = t; }
                void            SetEtartschalter4(long t) { s.ETARTSCHALTER4 = t; }
                void            SetEtartschalter5(long t) { s.ETARTSCHALTER5 = t; }
                void            SetVerkaufeinheit(long t) { s.VERKAUFEINHEIT = t; }
                void            SetContainergroesse(long t) { s.CONTAINERGROESSE = t; }
                void            SetKontigentmenge(short t) { s.KONTIGENTMENGE = t; }
                void            SetChargenartikel(char t) { s.CHARGENARTIKEL[0] = t; s.CHARGENARTIKEL[1] = '\0';}
                void            SetTextkey(short t) { s.TEXTKEY = t; }
                void            SetBestandreserviert(long t) { s.BESTANDRESERVIERT = t; }
                void            SetWafotyp(char t) { s.WAFOTYP[0] = t; s.WAFOTYP[1] = '\0';}
                void            SetKzrange(char t) { s.KZRANGE[0] = t; s.KZRANGE[1] = '\0';}
                void            SetMoreconditions(char t) { s.MORECONDITIONS[0] = t; s.MORECONDITIONS[1] = '\0';}
                void            SetBestandtagesanfang(long t) { s.BESTANDTAGESANFANG = t; }
                void            SetCodeblocage(char t) { s.CODEBLOCAGE[0] = t; s.CODEBLOCAGE[1] = '\0';}
				void			SetBlockedforreturns(short t) { s.BLOCKEDFORRETURNS = t; }
                void            SetStruct(const artikellokalS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CARTIKELLOKAL()  //constructor
                {
                        ::buf_default((void *)&s, ARTIKELLOKAL_BES, ARTIKELLOKAL_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CARTIKELLOKAL()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, ARTIKELLOKAL_BES, ARTIKELLOKAL_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, ARTIKELLOKAL_BES, ARTIKELLOKAL_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, ARTIKELLOKAL_BES, ARTIKELLOKAL_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_ARTIKELLOKAL& d)
                {
#ifdef WIN32
                        ppGStripLast(d.RABATTFAEHIG);
                        ppGStripLast(d.STATIONNR);
                        ppGStripLast(d.LAGERFACHNR);
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, ARTIKELLOKAL_BES, ARTIKELLOKAL_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of ARTIKELLOKAL *****************************************/

 #define ARTIKELLOKAL_CREATE(x) exec sql create table x (\
         FILIALNR smallint default 0 not null,\
         ARTIKEL_NR integer default 0 not null,\
         BESTAND integer default 0 not null,\
         NACHFRAGE integer default 0 not null,\
         ZUZAHLUNG char(1) default " " not null,\
         RABATTFAEHIG char(2) default " " not null,\
         NATRASTAFFELNR integer default 0 not null,\
         PRISOART char(1) default " " not null,\
         ARTIKELAKTIV char(1) default " " not null,\
         LAGERBEREICHNR smallint default 0 not null,\
         STATIONNR char(2) default " " not null,\
         LAGERFACHNR char(10) default " " not null,\
         VERBUNDARTIKEL char(1) default " " not null,\
         ETARTSCHALTER1 integer default 0 not null,\
         ETARTSCHALTER2 integer default 0 not null,\
         ETARTSCHALTER3 integer default 0 not null,\
         ETARTSCHALTER4 integer default 0 not null,\
         ETARTSCHALTER5 integer default 0 not null,\
         VERKAUFEINHEIT integer default 0 not null,\
         CONTAINERGROESSE integer default 0 not null,\
         KONTIGENTMENGE smallint default 0 not null,\
         CHARGENARTIKEL char(1) default " " not null,\
         TEXTKEY smallint default 0 not null,\
         BESTANDRESERVIERT integer default 0 not null,\
         WAFOTYP char(1) default " " not null,\
         KZRANGE char(1) default " " not null,\
         MORECONDITIONS char(1) default " " not null,\
         BESTANDTAGESANFANG integer default 0 not null,\
         CODEBLOCAGE char(1) default " " not null,\
		 BLOCKEDFORRETURNS smallint default 0 not null) in zp extent size 16472 next size 1648 lock mode row;


/* CreateIndexStatement of ARTIKELLOKAL ***************************************/

 #define ARTIKELLOKAL_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_artikellokal_1 on _X_(\
              filialnr,\
              artikel_nr ) in zpidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         exec sql create   index i_artikellokal_2 on _X_(\
              artikel_nr ) in zpidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ARTIKELLOKAL ***************************************/

 #define ARTIKELLOKAL_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_artikellokal_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         exec sql drop index i_artikellokal_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif
