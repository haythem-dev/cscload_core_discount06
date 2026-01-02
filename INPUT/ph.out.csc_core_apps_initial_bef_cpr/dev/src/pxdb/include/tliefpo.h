#ifndef __PP_NACHLIEFERPOS_H_
#define __PP_NACHLIEFERPOS_H_

/******************************************************************************/
/* c:\prri\Headerfiles\nachlieferpos ******************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of NACHLIEFERPOS *********************************************/

#define L_NACHLIEFERPOS_KDAUFTRAGNR 11
#define L_NACHLIEFERPOS_POSNR 11
#define L_NACHLIEFERPOS_DATUM 11
#define L_NACHLIEFERPOS_POSTYP 6
#define L_NACHLIEFERPOS_IDFNR 11
#define L_NACHLIEFERPOS_ARTIKEL_NR 11
#define L_NACHLIEFERPOS_MENGE 11
#define L_NACHLIEFERPOS_FILIALNR1 6
#define L_NACHLIEFERPOS_FILIALNR2 6
#define L_NACHLIEFERPOS_FILIALNR3 6
#define L_NACHLIEFERPOS_STATUS 11
#define L_NACHLIEFERPOS_URSPRUNGAUFTRAGNR 11
#define L_NACHLIEFERPOS_URSPRUNGPOSNR 11
#define L_NACHLIEFERPOS_KUNDENNR 11
#define L_NACHLIEFERPOS_VERTRIEBSZENTRUMNR 6
#define L_NACHLIEFERPOS_ERFASST 11
#define L_NACHLIEFERPOS_KDAUFTRAGART 2
#define L_NACHLIEFERPOS_POSART 2
#define L_NACHLIEFERPOS_PREISEKAPONETTO 9
#define N_NACHLIEFERPOS_PREISEKAPONETTO 2
#define L_NACHLIEFERPOS_BATCHAUFTRAGNR 11
#define L_NACHLIEFERPOS_BATCHPOSNR 11
#define L_NACHLIEFERPOS_MENGENATRA 11
#define L_NACHLIEFERPOS_BEMERKUNGEN 240
#define L_NACHLIEFERPOS_PREISEKAPO 9
#define N_NACHLIEFERPOS_PREISEKAPO 2
#define L_NACHLIEFERPOS_PREISVKAPO 9
#define N_NACHLIEFERPOS_PREISVKAPO 2
#define L_NACHLIEFERPOS_PREISAGP 9
#define N_NACHLIEFERPOS_PREISAGP 2
#define L_NACHLIEFERPOS_DATUMVALUTA 11
#define L_NACHLIEFERPOS_KOART 1
#define L_NACHLIEFERPOS_BUCHART 1
#define L_NACHLIEFERPOS_CODE_TYPE 6
#define L_NACHLIEFERPOS_ARTICLE_CODE 25
#define L_NACHLIEFERPOS_DISCOUNTVALUEPCT 5
#define N_NACHLIEFERPOS_DISCOUNTVALUEPCT 2
#define L_NACHLIEFERPOS_MENGEBESTELLT 11
#define L_NACHLIEFERPOS_PREIS_TYP 6

/* Length/Count-Define of NACHLIEFERPOS ***************************************/

#define LS_NACHLIEFERPOS_KDAUFTRAGNR 10 + 1
#define LS_NACHLIEFERPOS_POSNR 10 + 1
#define LS_NACHLIEFERPOS_DATUM 10 + 1
#define LS_NACHLIEFERPOS_POSTYP 5 + 1
#define LS_NACHLIEFERPOS_IDFNR 10 + 1
#define LS_NACHLIEFERPOS_ARTIKEL_NR 10 + 1
#define LS_NACHLIEFERPOS_MENGE 10 + 1
#define LS_NACHLIEFERPOS_FILIALNR1 5 + 1
#define LS_NACHLIEFERPOS_FILIALNR2 5 + 1
#define LS_NACHLIEFERPOS_FILIALNR3 5 + 1
#define LS_NACHLIEFERPOS_STATUS 10 + 1
#define LS_NACHLIEFERPOS_URSPRUNGAUFTRAGNR 10 + 1
#define LS_NACHLIEFERPOS_URSPRUNGPOSNR 10 + 1
#define LS_NACHLIEFERPOS_KUNDENNR 10 + 1
#define LS_NACHLIEFERPOS_VERTRIEBSZENTRUMNR 5 + 1
#define LS_NACHLIEFERPOS_ERFASST 10 + 1
#define LS_NACHLIEFERPOS_KDAUFTRAGART 2 + 1
#define LS_NACHLIEFERPOS_POSART 2 + 1
#define LS_NACHLIEFERPOS_PREISEKAPONETTO 9 + 2
#define LS_NACHLIEFERPOS_BATCHAUFTRAGNR 10 + 1
#define LS_NACHLIEFERPOS_BATCHPOSNR 10 + 1
#define LS_NACHLIEFERPOS_MENGENATRA 10 + 1
#define LS_NACHLIEFERPOS_BEMERKUNGEN 240 + 1
#define LS_NACHLIEFERPOS_PREISEKAPO 9 + 2
#define LS_NACHLIEFERPOS_PREISVKAPO 9 + 2
#define LS_NACHLIEFERPOS_PREISAGP 9 + 2
#define LS_NACHLIEFERPOS_DATUMVALUTA 10 + 1
#define LS_NACHLIEFERPOS_KOART 1 + 1
#define LS_NACHLIEFERPOS_BUCHART 1 + 1
#define LS_NACHLIEFERPOS_CODE_TYPE 5 + 1
#define LS_NACHLIEFERPOS_ARTICLE_CODE 25 + 1
#define LS_NACHLIEFERPOS_DISCOUNTVALUEPCT 5 + 2
#define LS_NACHLIEFERPOS_MENGEBESTELLT 10 + 1
#define LS_NACHLIEFERPOS_PREIS_TYP 5 + 1

#define NACHLIEFERPOSKDAUFTRAGNR 0
#define NACHLIEFERPOSPOSNR 1
#define NACHLIEFERPOSDATUM 2
#define NACHLIEFERPOSPOSTYP 3
#define NACHLIEFERPOSIDFNR 4
#define NACHLIEFERPOSARTIKEL_NR 5
#define NACHLIEFERPOSMENGE 6
#define NACHLIEFERPOSFILIALNR1 7
#define NACHLIEFERPOSFILIALNR2 8
#define NACHLIEFERPOSFILIALNR3 9
#define NACHLIEFERPOSSTATUS 10
#define NACHLIEFERPOSURSPRUNGAUFTRAGNR 11
#define NACHLIEFERPOSURSPRUNGPOSNR 12
#define NACHLIEFERPOSKUNDENNR 13
#define NACHLIEFERPOSVERTRIEBSZENTRUMNR 14
#define NACHLIEFERPOSERFASST 15
#define NACHLIEFERPOSKDAUFTRAGART 16
#define NACHLIEFERPOSPOSART 17
#define NACHLIEFERPOSPREISEKAPONETTO 18
#define NACHLIEFERPOSBATCHAUFTRAGNR 19
#define NACHLIEFERPOSBATCHPOSNR 20
#define NACHLIEFERPOSMENGENATRA 21
#define NACHLIEFERPOSBEMERKUNGEN 22
#define NACHLIEFERPOSPREISEKAPO 23
#define NACHLIEFERPOSPREISVKAPO 24
#define NACHLIEFERPOSPREISAGP 25
#define NACHLIEFERPOSDATUMVALUTA 26
#define NACHLIEFERPOSKOART 27
#define NACHLIEFERPOSBUCHART 28
#define NACHLIEFERPOSCODE_TYPE 29
#define NACHLIEFERPOSARTICLE_CODE 30
#define NACHLIEFERPOSDISCOUNTVALUEPCT 31
#define NACHLIEFERPOSMENGEBESTELLT 32
#define NACHLIEFERPOSPREIS_TYP 33

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define NACHLIEFERPOS_H
#define NACHLIEFERPOS_ANZ ( sizeof(NACHLIEFERPOS_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of NACHLIEFERPOS *************************************************/

#define NACHLIEFERPOS_LISTE \
        NACHLIEFERPOS.KDAUFTRAGNR,\
        NACHLIEFERPOS.POSNR,\
        NACHLIEFERPOS.DATUM,\
        NACHLIEFERPOS.POSTYP,\
        NACHLIEFERPOS.IDFNR,\
        NACHLIEFERPOS.ARTIKEL_NR,\
        NACHLIEFERPOS.MENGE,\
        NACHLIEFERPOS.FILIALNR1,\
        NACHLIEFERPOS.FILIALNR2,\
        NACHLIEFERPOS.FILIALNR3,\
        NACHLIEFERPOS.STATUS,\
        NACHLIEFERPOS.URSPRUNGAUFTRAGNR,\
        NACHLIEFERPOS.URSPRUNGPOSNR,\
        NACHLIEFERPOS.KUNDENNR,\
        NACHLIEFERPOS.VERTRIEBSZENTRUMNR,\
        NACHLIEFERPOS.ERFASST,\
        NACHLIEFERPOS.KDAUFTRAGART,\
        NACHLIEFERPOS.POSART,\
        NACHLIEFERPOS.PREISEKAPONETTO,\
        NACHLIEFERPOS.BATCHAUFTRAGNR,\
        NACHLIEFERPOS.BATCHPOSNR,\
        NACHLIEFERPOS.MENGENATRA,\
        NACHLIEFERPOS.BEMERKUNGEN,\
        NACHLIEFERPOS.PREISEKAPO,\
        NACHLIEFERPOS.PREISVKAPO,\
        NACHLIEFERPOS.PREISAGP,\
        NACHLIEFERPOS.DATUMVALUTA,\
        NACHLIEFERPOS.KOART,\
        NACHLIEFERPOS.BUCHART,\
        NACHLIEFERPOS.CODE_TYPE,\
        NACHLIEFERPOS.ARTICLE_CODE,\
        NACHLIEFERPOS.DISCOUNTVALUEPCT,\
        NACHLIEFERPOS.MENGEBESTELLT,\
        NACHLIEFERPOS.PREIS_TYP
#define NACHLIEFERPOS_LISTE_390 \
        KDAUFTRAGNR,\
        POSNR,\
        DATUM,\
        POSTYP,\
        IDFNR,\
        ARTIKEL_NR,\
        MENGE,\
        FILIALNR1,\
        FILIALNR2,\
        FILIALNR3,\
        STATUS,\
        URSPRUNGAUFTRAGNR,\
        URSPRUNGPOSNR,\
        KUNDENNR,\
        VERTRIEBSZENTRUMNR,\
        ERFASST,\
        KDAUFTRAGART,\
        POSART,\
        PREISEKAPONETTO,\
        BATCHAUFTRAGNR,\
        BATCHPOSNR,\
        MENGENATRA,\
        BEMERKUNGEN,\
        PREISEKAPO,\
        PREISVKAPO,\
        PREISAGP,\
        DATUMVALUTA,\
        KOART,\
        BUCHART,\
        CODE_TYPE,\
        ARTICLE_CODE,\
        DISCOUNTVALUEPCT,\
        MENGEBESTELLT,\
        PREIS_TYP
#define NACHLIEFERPOS_PLISTE \
        "NACHLIEFERPOS.KDAUFTRAGNR,"\
        "NACHLIEFERPOS.POSNR,"\
        "NACHLIEFERPOS.DATUM,"\
        "NACHLIEFERPOS.POSTYP,"\
        "NACHLIEFERPOS.IDFNR,"\
        "NACHLIEFERPOS.ARTIKEL_NR,"\
        "NACHLIEFERPOS.MENGE,"\
        "NACHLIEFERPOS.FILIALNR1,"\
        "NACHLIEFERPOS.FILIALNR2,"\
        "NACHLIEFERPOS.FILIALNR3,"\
        "NACHLIEFERPOS.STATUS,"\
        "NACHLIEFERPOS.URSPRUNGAUFTRAGNR,"\
        "NACHLIEFERPOS.URSPRUNGPOSNR,"\
        "NACHLIEFERPOS.KUNDENNR,"\
        "NACHLIEFERPOS.VERTRIEBSZENTRUMNR,"\
        "NACHLIEFERPOS.ERFASST,"\
        "NACHLIEFERPOS.KDAUFTRAGART,"\
        "NACHLIEFERPOS.POSART,"\
        "NACHLIEFERPOS.PREISEKAPONETTO,"\
        "NACHLIEFERPOS.BATCHAUFTRAGNR,"\
        "NACHLIEFERPOS.BATCHPOSNR,"\
        "NACHLIEFERPOS.MENGENATRA,"\
        "NACHLIEFERPOS.BEMERKUNGEN,"\
        "NACHLIEFERPOS.PREISEKAPO,"\
        "NACHLIEFERPOS.PREISVKAPO,"\
        "NACHLIEFERPOS.PREISAGP,"\
        "NACHLIEFERPOS.DATUMVALUTA,"\
        "NACHLIEFERPOS.KOART,"\
        "NACHLIEFERPOS.BUCHART,"\
        "NACHLIEFERPOS.CODE_TYPE,"\
        "NACHLIEFERPOS.ARTICLE_CODE,"\
        "NACHLIEFERPOS.DISCOUNTVALUEPCT,"\
        "NACHLIEFERPOS.MENGEBESTELLT,"\
        "NACHLIEFERPOS.PREIS_TYP"
#define NACHLIEFERPOS_PELISTE \
        "KDAUFTRAGNR,"\
        "POSNR,"\
        "DATUM,"\
        "POSTYP,"\
        "IDFNR,"\
        "ARTIKEL_NR,"\
        "MENGE,"\
        "FILIALNR1,"\
        "FILIALNR2,"\
        "FILIALNR3,"\
        "STATUS,"\
        "URSPRUNGAUFTRAGNR,"\
        "URSPRUNGPOSNR,"\
        "KUNDENNR,"\
        "VERTRIEBSZENTRUMNR,"\
        "ERFASST,"\
        "KDAUFTRAGART,"\
        "POSART,"\
        "PREISEKAPONETTO,"\
        "BATCHAUFTRAGNR,"\
        "BATCHPOSNR,"\
        "MENGENATRA,"\
        "BEMERKUNGEN,"\
        "PREISEKAPO,"\
        "PREISVKAPO,"\
        "PREISAGP,"\
        "DATUMVALUTA,"\
        "KOART,"\
        "BUCHART,"\
        "CODE_TYPE,"\
        "ARTICLE_CODE,"\
        "DISCOUNTVALUEPCT,"\
        "MENGEBESTELLT,"\
        "PREIS_TYP"
#define NACHLIEFERPOS_UPDLISTE \
        "KDAUFTRAGNR=?,"\
        "POSNR=?,"\
        "DATUM=?,"\
        "POSTYP=?,"\
        "IDFNR=?,"\
        "ARTIKEL_NR=?,"\
        "MENGE=?,"\
        "FILIALNR1=?,"\
        "FILIALNR2=?,"\
        "FILIALNR3=?,"\
        "STATUS=?,"\
        "URSPRUNGAUFTRAGNR=?,"\
        "URSPRUNGPOSNR=?,"\
        "KUNDENNR=?,"\
        "VERTRIEBSZENTRUMNR=?,"\
        "ERFASST=?,"\
        "KDAUFTRAGART=?,"\
        "POSART=?,"\
        "PREISEKAPONETTO=?,"\
        "BATCHAUFTRAGNR=?,"\
        "BATCHPOSNR=?,"\
        "MENGENATRA=?,"\
        "BEMERKUNGEN=?,"\
        "PREISEKAPO=?,"\
        "PREISVKAPO=?,"\
        "PREISAGP=?,"\
        "DATUMVALUTA=?,"\
        "KOART=?,"\
        "BUCHART=?,"\
        "CODE_TYPE=?,"\
        "ARTICLE_CODE=?,"\
        "DISCOUNTVALUEPCT=?,"\
        "MENGEBESTELLT=?,"\
        "PREIS_TYP=?"
/* SqlMacros-Define of NACHLIEFERPOS ******************************************/

#define NACHLIEFERPOS_ZEIGER(x) \
        :x->KDAUFTRAGNR,\
        :x->POSNR,\
        :x->DATUM,\
        :x->POSTYP,\
        :x->IDFNR,\
        :x->ARTIKEL_NR,\
        :x->MENGE,\
        :x->FILIALNR1,\
        :x->FILIALNR2,\
        :x->FILIALNR3,\
        :x->STATUS,\
        :x->URSPRUNGAUFTRAGNR,\
        :x->URSPRUNGPOSNR,\
        :x->KUNDENNR,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->ERFASST,\
        :x->KDAUFTRAGART,\
        :x->POSART,\
        :x->PREISEKAPONETTO,\
        :x->BATCHAUFTRAGNR,\
        :x->BATCHPOSNR,\
        :x->MENGENATRA,\
        :x->BEMERKUNGEN,\
        :x->PREISEKAPO,\
        :x->PREISVKAPO,\
        :x->PREISAGP,\
        :x->DATUMVALUTA,\
        :x->KOART,\
        :x->BUCHART,\
        :x->CODE_TYPE,\
        :x->ARTICLE_CODE,\
        :x->DISCOUNTVALUEPCT,\
        :x->MENGEBESTELLT,\
        :x->PREIS_TYP
#define NACHLIEFERPOS_ZEIGERSEL(x) \
        :x->KDAUFTRAGNR,\
        :x->POSNR,\
        :x->DATUM,\
        :x->POSTYP,\
        :x->IDFNR,\
        :x->ARTIKEL_NR,\
        :x->MENGE,\
        :x->FILIALNR1,\
        :x->FILIALNR2,\
        :x->FILIALNR3,\
        :x->STATUS,\
        :x->URSPRUNGAUFTRAGNR,\
        :x->URSPRUNGPOSNR,\
        :x->KUNDENNR,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->ERFASST,\
        :x->KDAUFTRAGART,\
        :x->POSART,\
        :x->PREISEKAPONETTO,\
        :x->BATCHAUFTRAGNR,\
        :x->BATCHPOSNR,\
        :x->MENGENATRA,\
        :x->BEMERKUNGEN,\
        :x->PREISEKAPO,\
        :x->PREISVKAPO,\
        :x->PREISAGP,\
        :x->DATUMVALUTA,\
        :x->KOART,\
        :x->BUCHART,\
        :x->CODE_TYPE,\
        :x->ARTICLE_CODE,\
        :x->DISCOUNTVALUEPCT,\
        :x->MENGEBESTELLT,\
        :x->PREIS_TYP
#define NACHLIEFERPOS_UPDATE(x) \
        NACHLIEFERPOS.KDAUFTRAGNR=:x->KDAUFTRAGNR,\
        NACHLIEFERPOS.POSNR=:x->POSNR,\
        NACHLIEFERPOS.DATUM=:x->DATUM,\
        NACHLIEFERPOS.POSTYP=:x->POSTYP,\
        NACHLIEFERPOS.IDFNR=:x->IDFNR,\
        NACHLIEFERPOS.ARTIKEL_NR=:x->ARTIKEL_NR,\
        NACHLIEFERPOS.MENGE=:x->MENGE,\
        NACHLIEFERPOS.FILIALNR1=:x->FILIALNR1,\
        NACHLIEFERPOS.FILIALNR2=:x->FILIALNR2,\
        NACHLIEFERPOS.FILIALNR3=:x->FILIALNR3,\
        NACHLIEFERPOS.STATUS=:x->STATUS,\
        NACHLIEFERPOS.URSPRUNGAUFTRAGNR=:x->URSPRUNGAUFTRAGNR,\
        NACHLIEFERPOS.URSPRUNGPOSNR=:x->URSPRUNGPOSNR,\
        NACHLIEFERPOS.KUNDENNR=:x->KUNDENNR,\
        NACHLIEFERPOS.VERTRIEBSZENTRUMNR=:x->VERTRIEBSZENTRUMNR,\
        NACHLIEFERPOS.ERFASST=:x->ERFASST,\
        NACHLIEFERPOS.KDAUFTRAGART=:x->KDAUFTRAGART,\
        NACHLIEFERPOS.POSART=:x->POSART,\
        NACHLIEFERPOS.PREISEKAPONETTO=:x->PREISEKAPONETTO,\
        NACHLIEFERPOS.BATCHAUFTRAGNR=:x->BATCHAUFTRAGNR,\
        NACHLIEFERPOS.BATCHPOSNR=:x->BATCHPOSNR,\
        NACHLIEFERPOS.MENGENATRA=:x->MENGENATRA,\
        NACHLIEFERPOS.BEMERKUNGEN=:x->BEMERKUNGEN,\
        NACHLIEFERPOS.PREISEKAPO=:x->PREISEKAPO,\
        NACHLIEFERPOS.PREISVKAPO=:x->PREISVKAPO,\
        NACHLIEFERPOS.PREISAGP=:x->PREISAGP,\
        NACHLIEFERPOS.DATUMVALUTA=:x->DATUMVALUTA,\
        NACHLIEFERPOS.KOART=:x->KOART,\
        NACHLIEFERPOS.BUCHART=:x->BUCHART,\
        NACHLIEFERPOS.CODE_TYPE=:x->CODE_TYPE,\
        NACHLIEFERPOS.ARTICLE_CODE=:x->ARTICLE_CODE,\
        NACHLIEFERPOS.DISCOUNTVALUEPCT=:x->DISCOUNTVALUEPCT,\
        NACHLIEFERPOS.MENGEBESTELLT=:x->MENGEBESTELLT,\
        NACHLIEFERPOS.PREIS_TYP=:x->PREIS_TYP
/* SqlMacros390-Define of NACHLIEFERPOS ***************************************/

#define NACHLIEFERPOS_ZEIGER_390 \
        :KDAUFTRAGNR,\
        :POSNR,\
        :DATUM,\
        :POSTYP,\
        :IDFNR,\
        :ARTIKEL_NR,\
        :MENGE,\
        :FILIALNR1,\
        :FILIALNR2,\
        :FILIALNR3,\
        :STATUS,\
        :URSPRUNGAUFTRAGNR,\
        :URSPRUNGPOSNR,\
        :KUNDENNR,\
        :VERTRIEBSZENTRUMNR,\
        :ERFASST,\
        :KDAUFTRAGART,\
        :POSART,\
        :PREISEKAPONETTO,\
        :BATCHAUFTRAGNR,\
        :BATCHPOSNR,\
        :MENGENATRA,\
        :BEMERKUNGEN,\
        :PREISEKAPO,\
        :PREISVKAPO,\
        :PREISAGP,\
        :DATUMVALUTA,\
        :KOART,\
        :BUCHART,\
        :CODE_TYPE,\
        :ARTICLE_CODE,\
        :DISCOUNTVALUEPCT,\
        :MENGEBESTELLT,\
        :PREIS_TYP
#define NACHLIEFERPOS_UPDATE_390 \
        KDAUFTRAGNR=:KDAUFTRAGNR,\
        POSNR=:POSNR,\
        DATUM=:DATUM,\
        POSTYP=:POSTYP,\
        IDFNR=:IDFNR,\
        ARTIKEL_NR=:ARTIKEL_NR,\
        MENGE=:MENGE,\
        FILIALNR1=:FILIALNR1,\
        FILIALNR2=:FILIALNR2,\
        FILIALNR3=:FILIALNR3,\
        STATUS=:STATUS,\
        URSPRUNGAUFTRAGNR=:URSPRUNGAUFTRAGNR,\
        URSPRUNGPOSNR=:URSPRUNGPOSNR,\
        KUNDENNR=:KUNDENNR,\
        VERTRIEBSZENTRUMNR=:VERTRIEBSZENTRUMNR,\
        ERFASST=:ERFASST,\
        KDAUFTRAGART=:KDAUFTRAGART,\
        POSART=:POSART,\
        PREISEKAPONETTO=:PREISEKAPONETTO,\
        BATCHAUFTRAGNR=:BATCHAUFTRAGNR,\
        BATCHPOSNR=:BATCHPOSNR,\
        MENGENATRA=:MENGENATRA,\
        BEMERKUNGEN=:BEMERKUNGEN,\
        PREISEKAPO=:PREISEKAPO,\
        PREISVKAPO=:PREISVKAPO,\
        PREISAGP=:PREISAGP,\
        DATUMVALUTA=:DATUMVALUTA,\
        KOART=:KOART,\
        BUCHART=:BUCHART,\
        CODE_TYPE=:CODE_TYPE,\
        ARTICLE_CODE=:ARTICLE_CODE,\
        DISCOUNTVALUEPCT=:DISCOUNTVALUEPCT,\
        MENGEBESTELLT=:MENGEBESTELLT,\
        PREIS_TYP=:PREIS_TYP
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of NACHLIEFERPOS *******************************************/

#ifndef TRANSCLASS
typedef struct N_NACHLIEFERPOS {
    long KDAUFTRAGNR;
    long POSNR;
    long DATUM;
    short POSTYP;
    long IDFNR;
    long ARTIKEL_NR;
    long MENGE;
    short FILIALNR1;
    short FILIALNR2;
    short FILIALNR3;
    long STATUS;
    long URSPRUNGAUFTRAGNR;
    long URSPRUNGPOSNR;
    long KUNDENNR;
    short VERTRIEBSZENTRUMNR;
    long ERFASST;
    char KDAUFTRAGART[3];
    char POSART[3];
    double PREISEKAPONETTO;
    long BATCHAUFTRAGNR;
    long BATCHPOSNR;
    long MENGENATRA;
    char BEMERKUNGEN[241];
    double PREISEKAPO;
    double PREISVKAPO;
    double PREISAGP;
    long DATUMVALUTA;
    char KOART[2];
    char BUCHART[2];
    short CODE_TYPE;
    char ARTICLE_CODE[26];
    double DISCOUNTVALUEPCT;
    long MENGEBESTELLT;
    short PREIS_TYP;
} nachlieferposS;
#else /* TRANSCLASS */
typedef struct N_NACHLIEFERPOS {
    long KDAUFTRAGNR;
    long POSNR;
    long DATUM;
    short POSTYP;
    long IDFNR;
    long ARTIKEL_NR;
    long MENGE;
    short FILIALNR1;
    short FILIALNR2;
    short FILIALNR3;
    long STATUS;
    long URSPRUNGAUFTRAGNR;
    long URSPRUNGPOSNR;
    long KUNDENNR;
    short VERTRIEBSZENTRUMNR;
    long ERFASST;
    char KDAUFTRAGART[3];
    char POSART[3];
    double PREISEKAPONETTO;
    long BATCHAUFTRAGNR;
    long BATCHPOSNR;
    long MENGENATRA;
    char BEMERKUNGEN[241];
    double PREISEKAPO;
    double PREISVKAPO;
    double PREISAGP;
    long DATUMVALUTA;
    char KOART[2];
    char BUCHART[2];
    short CODE_TYPE;
    char ARTICLE_CODE[26];
    double DISCOUNTVALUEPCT;
    long MENGEBESTELLT;
    short PREIS_TYP;

    bool operator == (const N_NACHLIEFERPOS& right) const {
        return (
            KDAUFTRAGNR == right.KDAUFTRAGNR &&
            POSNR == right.POSNR &&
            DATUM == right.DATUM &&
            POSTYP == right.POSTYP &&
            IDFNR == right.IDFNR &&
            ARTIKEL_NR == right.ARTIKEL_NR &&
            MENGE == right.MENGE &&
            FILIALNR1 == right.FILIALNR1 &&
            FILIALNR2 == right.FILIALNR2 &&
            FILIALNR3 == right.FILIALNR3 &&
            STATUS == right.STATUS &&
            URSPRUNGAUFTRAGNR == right.URSPRUNGAUFTRAGNR &&
            URSPRUNGPOSNR == right.URSPRUNGPOSNR &&
            KUNDENNR == right.KUNDENNR &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            ERFASST == right.ERFASST &&
            !strcmp(KDAUFTRAGART, right.KDAUFTRAGART) &&
            !strcmp(POSART, right.POSART) &&
            PREISEKAPONETTO == right.PREISEKAPONETTO &&
            BATCHAUFTRAGNR == right.BATCHAUFTRAGNR &&
            BATCHPOSNR == right.BATCHPOSNR &&
            MENGENATRA == right.MENGENATRA &&
            !strcmp(BEMERKUNGEN, right.BEMERKUNGEN) &&
            PREISEKAPO == right.PREISEKAPO &&
            PREISVKAPO == right.PREISVKAPO &&
            PREISAGP == right.PREISAGP &&
            DATUMVALUTA == right.DATUMVALUTA &&
            !strcmp(KOART, right.KOART) &&
            !strcmp(BUCHART, right.BUCHART) &&
            CODE_TYPE == right.CODE_TYPE &&
            !strcmp(ARTICLE_CODE, right.ARTICLE_CODE) &&
            DISCOUNTVALUEPCT == right.DISCOUNTVALUEPCT &&
            MENGEBESTELLT == right.MENGEBESTELLT &&
            PREIS_TYP == right.PREIS_TYP
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        KDAUFTRAGNR = 0;
        POSNR = 0;
        DATUM = 0;
        POSTYP = 0;
        IDFNR = 0;
        ARTIKEL_NR = 0;
        MENGE = 0;
        FILIALNR1 = 0;
        FILIALNR2 = 0;
        FILIALNR3 = 0;
        STATUS = 0;
        URSPRUNGAUFTRAGNR = 0;
        URSPRUNGPOSNR = 0;
        KUNDENNR = 0;
        VERTRIEBSZENTRUMNR = 0;
        ERFASST = 0;
        strcpy(KDAUFTRAGART, " " );
        strcpy(POSART, " " );
        PREISEKAPONETTO = 0;
        BATCHAUFTRAGNR = 0;
        BATCHPOSNR = 0;
        MENGENATRA = 0;
        strcpy(BEMERKUNGEN, " " );
        PREISEKAPO = 0;
        PREISVKAPO = 0;
        PREISAGP = 0;
        DATUMVALUTA = 0;
        strcpy(KOART, " " );
        strcpy(BUCHART, " " );
        CODE_TYPE = 0;
        strcpy(ARTICLE_CODE, " " );
        DISCOUNTVALUEPCT = 0;
        MENGEBESTELLT = 0;
        PREIS_TYP = 0;
#endif
    }
} nachlieferposS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of NACHLIEFERPOS *************************************/

struct S_NACHLIEFERPOS {
    char KDAUFTRAGNR[11];
    char POSNR[11];
    char DATUM[11];
    char POSTYP[7];
    char IDFNR[11];
    char ARTIKEL_NR[11];
    char MENGE[11];
    char FILIALNR1[7];
    char FILIALNR2[7];
    char FILIALNR3[7];
    char STATUS[11];
    char URSPRUNGAUFTRAGNR[11];
    char URSPRUNGPOSNR[11];
    char KUNDENNR[11];
    char VERTRIEBSZENTRUMNR[7];
    char ERFASST[11];
    char KDAUFTRAGART[2 + 1];
    char POSART[2 + 1];
    char PREISEKAPONETTO[9 + 2];
    char BATCHAUFTRAGNR[11];
    char BATCHPOSNR[11];
    char MENGENATRA[11];
    char BEMERKUNGEN[240 + 1];
    char PREISEKAPO[9 + 2];
    char PREISVKAPO[9 + 2];
    char PREISAGP[9 + 2];
    char DATUMVALUTA[11];
    char KOART[1 + 1];
    char BUCHART[1 + 1];
    char CODE_TYPE[7];
    char ARTICLE_CODE[25 + 1];
    char DISCOUNTVALUEPCT[5 + 2];
    char MENGEBESTELLT[11];
    char PREIS_TYP[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of NACHLIEFERPOS ********************/

struct O_NACHLIEFERPOS {
    char KDAUFTRAGNR[11];
    char POSNR[11];
    char DATUM[11];
    char POSTYP[7];
    char IDFNR[11];
    char ARTIKEL_NR[11];
    char MENGE[11];
    char FILIALNR1[7];
    char FILIALNR2[7];
    char FILIALNR3[7];
    char STATUS[11];
    char URSPRUNGAUFTRAGNR[11];
    char URSPRUNGPOSNR[11];
    char KUNDENNR[11];
    char VERTRIEBSZENTRUMNR[7];
    char ERFASST[11];
    char KDAUFTRAGART[2];
    char POSART[2];
    char PREISEKAPONETTO[9];
    char BATCHAUFTRAGNR[11];
    char BATCHPOSNR[11];
    char MENGENATRA[11];
    char BEMERKUNGEN[240];
    char PREISEKAPO[9];
    char PREISVKAPO[9];
    char PREISAGP[9];
    char DATUMVALUTA[11];
    char KOART[1];
    char BUCHART[1];
    char CODE_TYPE[7];
    char ARTICLE_CODE[25];
    char DISCOUNTVALUEPCT[5];
    char MENGEBESTELLT[11];
    char PREIS_TYP[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of NACHLIEFERPOS *******************************/

struct C_NACHLIEFERPOS {
    long KDAUFTRAGNR;
    long POSNR;
    long DATUM;
    short POSTYP;
    long IDFNR;
    long ARTIKEL_NR;
    long MENGE;
    short FILIALNR1;
    short FILIALNR2;
    short FILIALNR3;
    long STATUS;
    long URSPRUNGAUFTRAGNR;
    long URSPRUNGPOSNR;
    long KUNDENNR;
    short VERTRIEBSZENTRUMNR;
    long ERFASST;
    char KDAUFTRAGART[3];
    char POSART[3];
    double PREISEKAPONETTO;
    long BATCHAUFTRAGNR;
    long BATCHPOSNR;
    long MENGENATRA;
    char BEMERKUNGEN[241];
    double PREISEKAPO;
    double PREISVKAPO;
    double PREISAGP;
    long DATUMVALUTA;
    char KOART;
    char BUCHART;
    short CODE_TYPE;
    char ARTICLE_CODE[26];
    double DISCOUNTVALUEPCT;
    long MENGEBESTELLT;
    short PREIS_TYP;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of NACHLIEFERPOS *****************************/

struct I_NACHLIEFERPOS {
    short KDAUFTRAGNR;
    short POSNR;
    short DATUM;
    short POSTYP;
    short IDFNR;
    short ARTIKEL_NR;
    short MENGE;
    short FILIALNR1;
    short FILIALNR2;
    short FILIALNR3;
    short STATUS;
    short URSPRUNGAUFTRAGNR;
    short URSPRUNGPOSNR;
    short KUNDENNR;
    short VERTRIEBSZENTRUMNR;
    short ERFASST;
    short KDAUFTRAGART;
    short POSART;
    short PREISEKAPONETTO;
    short BATCHAUFTRAGNR;
    short BATCHPOSNR;
    short MENGENATRA;
    short BEMERKUNGEN;
    short PREISEKAPO;
    short PREISVKAPO;
    short PREISAGP;
    short DATUMVALUTA;
    short KOART;
    short BUCHART;
    short CODE_TYPE;
    short ARTICLE_CODE;
    short DISCOUNTVALUEPCT;
    short MENGEBESTELLT;
    short PREIS_TYP;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of NACHLIEFERPOS ***************************************/

#if defined (BUF_DESC)
static struct buf_desc NACHLIEFERPOS_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 2, 0 },
   { TYP_D, 9, 2 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 240, 0 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 25, 0 },
   { TYP_D, 5, 2 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc NACHLIEFERPOS_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 2, 0 },
   { TYP_D, 9, 2 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 240, 0 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 25, 0 },
   { TYP_D, 5, 2 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* description for datatypes of NACHLIEFERPOS *********************************/

 #define NACHLIEFERPOS_S390 \
         long KDAUFTRAGNR; \
         long POSNR; \
         long DATUM; \
         short POSTYP; \
         long IDFNR; \
         long ARTIKEL_NR; \
         long MENGE; \
         short FILIALNR1; \
         short FILIALNR2; \
         short FILIALNR3; \
         long STATUS; \
         long URSPRUNGAUFTRAGNR; \
         long URSPRUNGPOSNR; \
         long KUNDENNR; \
         short VERTRIEBSZENTRUMNR; \
         long ERFASST; \
         char KDAUFTRAGART[3]; \
         char POSART[3]; \
         double PREISEKAPONETTO; \
         long BATCHAUFTRAGNR; \
         long BATCHPOSNR; \
         long MENGENATRA; \
         char BEMERKUNGEN[241]; \
         double PREISEKAPO; \
         double PREISVKAPO; \
         double PREISAGP; \
         long DATUMVALUTA; \
         char KOART; \
         char BUCHART; \
         short CODE_TYPE; \
         char ARTICLE_CODE[26]; \
         double DISCOUNTVALUEPCT; \
         long MENGEBESTELLT; \
         short PREIS_TYP; \



/* Copy-Function Struct to single Data NACHLIEFERPOS **************************/

 #define NACHLIEFERPOS_S390_COPY_TO_SINGLE(_x_) \
         KDAUFTRAGNR=_x_->KDAUFTRAGNR;\
         POSNR=_x_->POSNR;\
         DATUM=_x_->DATUM;\
         POSTYP=_x_->POSTYP;\
         IDFNR=_x_->IDFNR;\
         ARTIKEL_NR=_x_->ARTIKEL_NR;\
         MENGE=_x_->MENGE;\
         FILIALNR1=_x_->FILIALNR1;\
         FILIALNR2=_x_->FILIALNR2;\
         FILIALNR3=_x_->FILIALNR3;\
         STATUS=_x_->STATUS;\
         URSPRUNGAUFTRAGNR=_x_->URSPRUNGAUFTRAGNR;\
         URSPRUNGPOSNR=_x_->URSPRUNGPOSNR;\
         KUNDENNR=_x_->KUNDENNR;\
         VERTRIEBSZENTRUMNR=_x_->VERTRIEBSZENTRUMNR;\
         ERFASST=_x_->ERFASST;\
          strcpy(KDAUFTRAGART,_x_->KDAUFTRAGART);\
          strcpy(POSART,_x_->POSART);\
         PREISEKAPONETTO=_x_->PREISEKAPONETTO;\
         BATCHAUFTRAGNR=_x_->BATCHAUFTRAGNR;\
         BATCHPOSNR=_x_->BATCHPOSNR;\
         MENGENATRA=_x_->MENGENATRA;\
          strcpy(BEMERKUNGEN,_x_->BEMERKUNGEN);\
         PREISEKAPO=_x_->PREISEKAPO;\
         PREISVKAPO=_x_->PREISVKAPO;\
         PREISAGP=_x_->PREISAGP;\
         DATUMVALUTA=_x_->DATUMVALUTA;\
         KOART=_x_->KOART;\
         BUCHART=_x_->BUCHART;\
         CODE_TYPE=_x_->CODE_TYPE;\
          strcpy(ARTICLE_CODE,_x_->ARTICLE_CODE);\
         DISCOUNTVALUEPCT=_x_->DISCOUNTVALUEPCT;\
         MENGEBESTELLT=_x_->MENGEBESTELLT;\
         PREIS_TYP=_x_->PREIS_TYP;\

 #define NACHLIEFERPOS_S390_COPY_TO_STRUCT(_x_) \
          _x_->KDAUFTRAGNR=KDAUFTRAGNR;\
          _x_->POSNR=POSNR;\
          _x_->DATUM=DATUM;\
          _x_->POSTYP=POSTYP;\
          _x_->IDFNR=IDFNR;\
          _x_->ARTIKEL_NR=ARTIKEL_NR;\
          _x_->MENGE=MENGE;\
          _x_->FILIALNR1=FILIALNR1;\
          _x_->FILIALNR2=FILIALNR2;\
          _x_->FILIALNR3=FILIALNR3;\
          _x_->STATUS=STATUS;\
          _x_->URSPRUNGAUFTRAGNR=URSPRUNGAUFTRAGNR;\
          _x_->URSPRUNGPOSNR=URSPRUNGPOSNR;\
          _x_->KUNDENNR=KUNDENNR;\
          _x_->VERTRIEBSZENTRUMNR=VERTRIEBSZENTRUMNR;\
          _x_->ERFASST=ERFASST;\
          strcpy(_x_->KDAUFTRAGART,KDAUFTRAGART);\
          strcpy(_x_->POSART,POSART);\
          _x_->PREISEKAPONETTO=PREISEKAPONETTO;\
          _x_->BATCHAUFTRAGNR=BATCHAUFTRAGNR;\
          _x_->BATCHPOSNR=BATCHPOSNR;\
          _x_->MENGENATRA=MENGENATRA;\
          strcpy(_x_->BEMERKUNGEN,BEMERKUNGEN);\
          _x_->PREISEKAPO=PREISEKAPO;\
          _x_->PREISVKAPO=PREISVKAPO;\
          _x_->PREISAGP=PREISAGP;\
          _x_->DATUMVALUTA=DATUMVALUTA;\
          _x_->KOART=KOART;\
          _x_->BUCHART=BUCHART;\
          _x_->CODE_TYPE=CODE_TYPE;\
          strcpy(_x_->ARTICLE_CODE,ARTICLE_CODE);\
          _x_->DISCOUNTVALUEPCT=DISCOUNTVALUEPCT;\
          _x_->MENGEBESTELLT=MENGEBESTELLT;\
          _x_->PREIS_TYP=PREIS_TYP;\



/* FunctionNumber-Define of nachlieferpos *************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of nachlieferpos *********************************/


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

class CNACHLIEFERPOS : public ppDadeVirtual {
public:
    nachlieferposS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<nachlieferposS> lst; // class list

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
                     vector< nachlieferposS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     nachlieferposS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< nachlieferposS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<nachlieferposS>::iterator
                 beginList() { return lst.begin(); }
    vector<nachlieferposS>::iterator
                 endList  () { return lst.end  (); }

    long         GetKdauftragnr() const { return s.KDAUFTRAGNR; }
    long         GetPosnr() const { return s.POSNR; }
    long         GetDatum() const { return s.DATUM; }
    short        GetPostyp() const { return s.POSTYP; }
    long         GetIdfnr() const { return s.IDFNR; }
    long         GetArtikel_nr() const { return s.ARTIKEL_NR; }
    long         GetMenge() const { return s.MENGE; }
    short        GetFilialnr1() const { return s.FILIALNR1; }
    short        GetFilialnr2() const { return s.FILIALNR2; }
    short        GetFilialnr3() const { return s.FILIALNR3; }
    long         GetStatus() const { return s.STATUS; }
    long         GetUrsprungauftragnr() const { return s.URSPRUNGAUFTRAGNR; }
    long         GetUrsprungposnr() const { return s.URSPRUNGPOSNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetErfasst() const { return s.ERFASST; }
    const char*  GetKdauftragart(ppString & t) const { t = s.KDAUFTRAGART; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetPosart(ppString & t) const { t = s.POSART; t.erasespace(ppString::END); return t.c_str(); }
    double       GetPreisekaponetto() const { return s.PREISEKAPONETTO; }
    long         GetBatchauftragnr() const { return s.BATCHAUFTRAGNR; }
    long         GetBatchposnr() const { return s.BATCHPOSNR; }
    long         GetMengenatra() const { return s.MENGENATRA; }
    const char*  GetBemerkungen(ppString & t) const { t = s.BEMERKUNGEN; t.erasespace(ppString::END); return t.c_str(); }
    double       GetPreisekapo() const { return s.PREISEKAPO; }
    double       GetPreisvkapo() const { return s.PREISVKAPO; }
    double       GetPreisagp() const { return s.PREISAGP; }
    long         GetDatumvaluta() const { return s.DATUMVALUTA; }
    char         GetKoart() const { return s.KOART[0]; }
    char         GetBuchart() const { return s.BUCHART[0]; }
    short        GetCode_type() const { return s.CODE_TYPE; }
    const char*  GetArticle_code(ppString & t) const { t = s.ARTICLE_CODE; t.erasespace(ppString::END); return t.c_str(); }
    double       GetDiscountvaluepct() const { return s.DISCOUNTVALUEPCT; }
    long         GetMengebestellt() const { return s.MENGEBESTELLT; }
    short        GetPreis_typ() const { return s.PREIS_TYP; }

    const nachlieferposS &
                 GetStruct() const { return s; }
    void         SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
    void         SetPosnr(long t) { s.POSNR = t; }
    void         SetDatum(long t) { s.DATUM = t; }
    void         SetPostyp(short t) { s.POSTYP = t; }
    void         SetIdfnr(long t) { s.IDFNR = t; }
    void         SetArtikel_nr(long t) { s.ARTIKEL_NR = t; }
    void         SetMenge(long t) { s.MENGE = t; }
    void         SetFilialnr1(short t) { s.FILIALNR1 = t; }
    void         SetFilialnr2(short t) { s.FILIALNR2 = t; }
    void         SetFilialnr3(short t) { s.FILIALNR3 = t; }
    void         SetStatus(long t) { s.STATUS = t; }
    void         SetUrsprungauftragnr(long t) { s.URSPRUNGAUFTRAGNR = t; }
    void         SetUrsprungposnr(long t) { s.URSPRUNGPOSNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetErfasst(long t) { s.ERFASST = t; }
    void         SetKdauftragart(const ppString & t) { ppGStrCopy(s.KDAUFTRAGART, t.c_str(), L_NACHLIEFERPOS_KDAUFTRAGART); }
    void         SetPosart(const ppString & t) { ppGStrCopy(s.POSART, t.c_str(), L_NACHLIEFERPOS_POSART); }
    void         SetPreisekaponetto(double t) { s.PREISEKAPONETTO = t; }
    void         SetBatchauftragnr(long t) { s.BATCHAUFTRAGNR = t; }
    void         SetBatchposnr(long t) { s.BATCHPOSNR = t; }
    void         SetMengenatra(long t) { s.MENGENATRA = t; }
    void         SetBemerkungen(const ppString & t) { ppGStrCopy(s.BEMERKUNGEN, t.c_str(), L_NACHLIEFERPOS_BEMERKUNGEN); }
    void         SetPreisekapo(double t) { s.PREISEKAPO = t; }
    void         SetPreisvkapo(double t) { s.PREISVKAPO = t; }
    void         SetPreisagp(double t) { s.PREISAGP = t; }
    void         SetDatumvaluta(long t) { s.DATUMVALUTA = t; }
    void         SetKoart(char t) { s.KOART[0] = t; s.KOART[1] = '\0';}
    void         SetBuchart(char t) { s.BUCHART[0] = t; s.BUCHART[1] = '\0';}
    void         SetCode_type(short t) { s.CODE_TYPE = t; }
    void         SetArticle_code(const ppString & t) { ppGStrCopy(s.ARTICLE_CODE, t.c_str(), L_NACHLIEFERPOS_ARTICLE_CODE); }
    void         SetDiscountvaluepct(double t) { s.DISCOUNTVALUEPCT = t; }
    void         SetMengebestellt(long t) { s.MENGEBESTELLT = t; }
    void         SetPreis_typ(short t) { s.PREIS_TYP = t; }

    void         SetStruct(const nachlieferposS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CNACHLIEFERPOS() {
        ::buf_default((void *)&s, NACHLIEFERPOS_BES, NACHLIEFERPOS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CNACHLIEFERPOS() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, NACHLIEFERPOS_BES, NACHLIEFERPOS_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, NACHLIEFERPOS_BES, (int)NACHLIEFERPOS_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, NACHLIEFERPOS_BES, (int)NACHLIEFERPOS_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_NACHLIEFERPOS & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.KDAUFTRAGART);
        ppGStripLast(d.POSART);
        ppGStripLast(d.BEMERKUNGEN);
        ppGStripLast(d.ARTICLE_CODE);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, NACHLIEFERPOS_BES, (int)NACHLIEFERPOS_ANZ, error_msg);
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
/* CreateSqlStatement of NACHLIEFERPOS ****************************************/

 #define NACHLIEFERPOS_CREATE(x) EXEC SQL create table x (\
         KDAUFTRAGNR integer default 0 not null,\
         POSNR integer default 0 not null,\
         DATUM integer default 0 not null,\
         POSTYP smallint default 0 not null,\
         IDFNR integer default 0 not null,\
         ARTIKEL_NR integer default 0 not null,\
         MENGE integer default 0 not null,\
         FILIALNR1 smallint default 0 not null,\
         FILIALNR2 smallint default 0 not null,\
         FILIALNR3 smallint default 0 not null,\
         STATUS integer default 0 not null,\
         URSPRUNGAUFTRAGNR integer default 0 not null,\
         URSPRUNGPOSNR integer default 0 not null,\
         KUNDENNR integer default 0 not null,\
         VERTRIEBSZENTRUMNR smallint default 0 not null,\
         ERFASST integer default 0 not null,\
         KDAUFTRAGART char(2) default " " not null,\
         POSART char(2) default " " not null,\
         PREISEKAPONETTO decimal(9,2) default 0 not null,\
         BATCHAUFTRAGNR integer default 0 not null,\
         BATCHPOSNR integer default 0 not null,\
         MENGENATRA integer default 0 not null,\
         BEMERKUNGEN varchar(240,0) default " " not null,\
         PREISEKAPO decimal(9,2) default 0 not null,\
         PREISVKAPO decimal(9,2) default 0 not null,\
         PREISAGP decimal(9,2) default 0 not null,\
         DATUMVALUTA integer default 0 not null,\
         KOART char(1) default " " not null,\
         BUCHART char(1) default " " not null,\
         CODE_TYPE smallint default 0 not null,\
         ARTICLE_CODE char(25) default " " not null,\
         DISCOUNTVALUEPCT decimal(5,2) default 0 not null,\
         MENGEBESTELLT integer default 0 not null,\
         PREIS_TYP smallint default 0 not null) in KscOrder extent size 10432 next size 1044 lock mode row;



/* CreateIndexStatement of NACHLIEFERPOS **************************************/

 #define NACHLIEFERPOS_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_nachlieferpos_3 on _X_(\
              kdauftragnr,\
              posnr,\
              datum,\
              postyp ) in KscOrderIdx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index i_nachlieferpos_4 on _X_(\
              VertriebszentrumNr,\
              KundenNr ) in KscOrderIdx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index i_nachlieferpos_5 on _X_(\
              VertriebszentrumNr,\
              artikel_nr ) in KscOrderIdx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index i_verbundlieferp_2 on _X_(\
              idfnr ) in KscOrderIdx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of NACHLIEFERPOS **************************************/

 #define NACHLIEFERPOS_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_nachlieferpos_3;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_nachlieferpos_4;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_nachlieferpos_5;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_verbundlieferp_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
