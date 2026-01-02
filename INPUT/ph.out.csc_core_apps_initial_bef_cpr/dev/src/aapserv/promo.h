#ifndef __PP_PROMO_H_
#define __PP_PROMO_H_

/******************************************************************************/
/* c:\git\pharmos.outbound.csc_core_applications\dev\src\aapserv\Promo ********/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of PRODUCTPROMO **********************************************/

#define L_PRODUCTPROMO_BRANCHNO 6
#define L_PRODUCTPROMO_PROMOTION_NO 6
#define L_PRODUCTPROMO_ARTICLENO 11
#define L_PRODUCTPROMO_NAME 30
#define L_PRODUCTPROMO_PREISEKAPO 9
#define N_PRODUCTPROMO_PREISEKAPO 2
#define L_PRODUCTPROMO_CUSTOMERNO 11
#define L_PRODUCTPROMO_ADDONSTDDISCOK 1
#define L_PRODUCTPROMO_DISCOUNTVALUEPCT 5
#define N_PRODUCTPROMO_DISCOUNTVALUEPCT 2
#define L_PRODUCTPROMO_MAXQTY 11
#define L_PRODUCTPROMO_BESTAND 11
#define L_PRODUCTPROMO_ARTIKELAKTIV 1
#define L_PRODUCTPROMO_TAXLEVEL 6
#define L_PRODUCTPROMO_ARTIKEL_LANGNAME 50

/* Length-Define of PROMOHERST ************************************************/

#define L_PROMOHERST_PREISEKAPO 9
#define N_PROMOHERST_PREISEKAPO 2
#define L_PROMOHERST_DATUMVERFALL 11
#define L_PROMOHERST_DATEFROM 11
#define L_PROMOHERST_PREIS_TYP 6
#define L_PROMOHERST_PROMOTION_NO 6
#define L_PROMOHERST_FILIALNR 6
#define L_PROMOHERST_ARTIKEL_NR 11
#define L_PROMOHERST_BESTAND 11
#define L_PROMOHERST_ARTIKELAKTIV 1
#define L_PROMOHERST_HERSTELLER_NR 11
#define L_PROMOHERST_TAXLEVEL 6
#define L_PROMOHERST_HEALTHFUNDCODE 5
#define L_PROMOHERST_ARTIKEL_LANGNAME 50

/* Length-Define of PROMOMANUFACT *********************************************/

#define L_PROMOMANUFACT_BRANCHNO 6
#define L_PROMOMANUFACT_DATEFROM 11
#define L_PROMOMANUFACT_DATETO 11
#define L_PROMOMANUFACT_MANUFACTURERNO 11
#define L_PROMOMANUFACT_PROMOTION_NO 6

/* Length-Define of PROMOMEMBERS **********************************************/

#define L_PROMOMEMBERS_BRANCHNO 6
#define L_PROMOMEMBERS_DISCOUNTGRPNO 11
#define L_PROMOMEMBERS_DATUMVERFALL 11
#define L_PROMOMEMBERS_BASEQTY 11
#define L_PROMOMEMBERS_DISCOUNTQTY 6
#define L_PROMOMEMBERS_DISCOUNTVALUEPCT 5
#define N_PROMOMEMBERS_DISCOUNTVALUEPCT 2
#define L_PROMOMEMBERS_NO_MULTIPLE_QTY 1
#define L_PROMOMEMBERS_MAXQTY 11
#define L_PROMOMEMBERS_ARTIKEL_NR 11
#define L_PROMOMEMBERS_ARTIKEL_LANGNAME 50

/* Length-Define of PROMOTIONEN ***********************************************/

#define L_PROMOTIONEN_BRANCHNO 6
#define L_PROMOTIONEN_NAME 30
#define L_PROMOTIONEN_DISCOUNTGRPNO 11
#define L_PROMOTIONEN_PHARMACYGROUPID 3
#define L_PROMOTIONEN_CUSTOMERNO 11
#define L_PROMOTIONEN_ADDONSTDDISCOK 1
#define L_PROMOTIONEN_DATEFROM 11
#define L_PROMOTIONEN_DATETO 11
#define L_PROMOTIONEN_BASEQTY 11
#define L_PROMOTIONEN_DISCOUNTSPEC 6
#define L_PROMOTIONEN_DISCOUNTQTY 6
#define L_PROMOTIONEN_DISCOUNTVALUEPCT 5
#define N_PROMOTIONEN_DISCOUNTVALUEPCT 2
#define L_PROMOTIONEN_DISCOUNTARTICLE 11
#define L_PROMOTIONEN_BASE_VALUE 10
#define N_PROMOTIONEN_BASE_VALUE 2
#define L_PROMOTIONEN_MANUFACTURERNO 11
#define L_PROMOTIONEN_GROSSPROFITPCT 5
#define N_PROMOTIONEN_GROSSPROFITPCT 2
#define L_PROMOTIONEN_ADDONDISCOUNTOK 1
#define L_PROMOTIONEN_PROMOTION_NO 6

/* Length-Define of STOTINKEN *************************************************/

#define L_STOTINKEN_PREISEKAPO 9
#define N_STOTINKEN_PREISEKAPO 2
#define L_STOTINKEN_FILIALNR 6
#define L_STOTINKEN_ARTIKEL_NR 11
#define L_STOTINKEN_BESTAND 11
#define L_STOTINKEN_TAXLEVEL 6
#define L_STOTINKEN_ARTIKEL_LANGNAME 50

/* SqlDefine of PRODUCTPROMO **************************************************/


#define PRODUCTPROMO_PLISTE \
        "DISCOUNT.BRANCHNO,"\
        "PROMOTIONS.PROMOTION_NO,"\
        "DISCOUNT.ARTICLENO,"\
        "PROMOTIONS.NAME,"\
        "ARTIKELPREIS.PREISEKAPO,"\
        "DISCOUNT.CUSTOMERNO,"\
        "PROMOTIONS.ADDONSTDDISCOK,"\
        "DISCOUNT.DISCOUNTVALUEPCT,"\
        "DISCOUNT.MAXQTY,"\
        "ARTIKELLOKAL.BESTAND,"\
        "ARTIKELLOKAL.ARTIKELAKTIV,"\
        "ARTIKELZENTRAL.TAXLEVEL,"\
        "ARTIKELZENTRAL.ARTIKEL_LANGNAME"

/* SqlDefine of PROMOHERST ****************************************************/


#define PROMOHERST_PLISTE \
        "ARTIKELPREIS.PREISEKAPO,"\
        "ARTIKELLAGERORT.DATUMVERFALL,"\
        "ARTIKELPREIS.PREIS_TYP,"\
        "ARTIKELLOKAL.FILIALNR,"\
        "ARTIKELZENTRAL.ARTIKEL_NR,"\
        "ARTIKELLOKAL.BESTAND,"\
        "ARTIKELLOKAL.ARTIKELAKTIV,"\
        "ARTIKELZENTRAL.HERSTELLER_NR,"\
        "ARTIKELZENTRAL.TAXLEVEL,"\
        "ARTIKELZENTRAL.HEALTHFUNDCODE,"\
        "ARTIKELZENTRAL.ARTIKEL_LANGNAME"

/* SqlDefine of PROMOMANUFACT *************************************************/


#define PROMOMANUFACT_PLISTE \
        "DISCOUNT.BRANCHNO,"\
        "DISCOUNT.DATEFROM,"\
        "DISCOUNT.DATETO,"\
        "DISCOUNT.MANUFACTURERNO,"\
        "DISCOUNT.PROMOTION_NO"

/* SqlDefine of PROMOMEMBERS **************************************************/


#define PROMOMEMBERS_PLISTE \
        "DISCOUNTGRPMEM.BRANCHNO,"\
        "DISCOUNTGRPMEM.DISCOUNTGRPNO,"\
        "ARTIKELLAGERORT.DATUMVERFALL,"\
        "DISCOUNT.BASEQTY,"\
        "DISCOUNT.DISCOUNTQTY,"\
        "DISCOUNT.DISCOUNTVALUEPCT,"\
        "DISCOUNT.NO_MULTIPLE_QTY,"\
        "DISCOUNT.MAXQTY,"\
        "ARTIKELZENTRAL.ARTIKEL_NR,"\
        "ARTIKELZENTRAL.ARTIKEL_LANGNAME"

/* SqlDefine of PROMOTIONEN ***************************************************/


#define PROMOTIONEN_PLISTE \
        "DISCOUNT.BRANCHNO,"\
        "PROMOTIONS.NAME,"\
        "DISCOUNT.DISCOUNTGRPNO,"\
        "DISCOUNT.PHARMACYGROUPID,"\
        "DISCOUNT.CUSTOMERNO,"\
        "PROMOTIONS.ADDONSTDDISCOK,"\
        "DISCOUNT.DATEFROM,"\
        "DISCOUNT.DATETO,"\
        "DISCOUNT.BASEQTY,"\
        "DISCOUNT.DISCOUNTSPEC,"\
        "DISCOUNT.DISCOUNTQTY,"\
        "DISCOUNT.DISCOUNTVALUEPCT,"\
        "DISCOUNT.DISCOUNTARTICLE,"\
        "DISCOUNT.BASE_VALUE,"\
        "DISCOUNT.MANUFACTURERNO,"\
        "DISCOUNT.GROSSPROFITPCT,"\
        "DISCOUNT.ADDONDISCOUNTOK,"\
        "DISCOUNT.PROMOTION_NO"

/* SqlDefine of STOTINKEN *****************************************************/


#define STOTINKEN_PLISTE \
        "ARTIKELPREIS.PREISEKAPO,"\
        "ARTIKELLOKAL.FILIALNR,"\
        "ARTIKELZENTRAL.ARTIKEL_NR,"\
        "ARTIKELLOKAL.BESTAND,"\
        "ARTIKELZENTRAL.TAXLEVEL,"\
        "ARTIKELZENTRAL.ARTIKEL_LANGNAME"

/* SqlDefine of PRODUCTPROMO **************************************************/


#define PRODUCTPROMO_UPDLISTE \
        "BRANCHNO=?,"\
        "PROMOTION_NO=?,"\
        "ARTICLENO=?,"\
        "NAME=?,"\
        "PREISEKAPO=?,"\
        "CUSTOMERNO=?,"\
        "ADDONSTDDISCOK=?,"\
        "DISCOUNTVALUEPCT=?,"\
        "MAXQTY=?,"\
        "BESTAND=?,"\
        "ARTIKELAKTIV=?,"\
        "TAXLEVEL=?,"\
        "ARTIKEL_LANGNAME=?"
/* SqlDefine of PROMOHERST ****************************************************/


#define PROMOHERST_UPDLISTE \
        "PREISEKAPO=?,"\
        "DATUMVERFALL=?,"\
        "PREIS_TYP=?,"\
        "FILIALNR=?,"\
        "ARTIKEL_NR=?,"\
        "BESTAND=?,"\
        "ARTIKELAKTIV=?,"\
        "HERSTELLER_NR=?,"\
        "TAXLEVEL=?,"\
        "HEALTHFUNDCODE=?,"\
        "ARTIKEL_LANGNAME=?"
/* SqlDefine of PROMOMANUFACT *************************************************/


#define PROMOMANUFACT_UPDLISTE \
        "BRANCHNO=?,"\
        "DATEFROM=?,"\
        "DATETO=?,"\
        "MANUFACTURERNO=?,"\
        "PROMOTION_NO=?"
/* SqlDefine of PROMOMEMBERS **************************************************/


#define PROMOMEMBERS_UPDLISTE \
        "BRANCHNO=?,"\
        "DISCOUNTGRPNO=?,"\
        "DATUMVERFALL=?,"\
        "BASEQTY=?,"\
        "DISCOUNTQTY=?,"\
        "DISCOUNTVALUEPCT=?,"\
        "NO_MULTIPLE_QTY=?,"\
        "MAXQTY=?,"\
        "ARTIKEL_NR=?,"\
        "ARTIKEL_LANGNAME=?"
/* SqlDefine of PROMOTIONEN ***************************************************/


#define PROMOTIONEN_UPDLISTE \
        "BRANCHNO=?,"\
        "NAME=?,"\
        "DISCOUNTGRPNO=?,"\
        "PHARMACYGROUPID=?,"\
        "CUSTOMERNO=?,"\
        "ADDONSTDDISCOK=?,"\
        "DATEFROM=?,"\
        "DATETO=?,"\
        "BASEQTY=?,"\
        "DISCOUNTSPEC=?,"\
        "DISCOUNTQTY=?,"\
        "DISCOUNTVALUEPCT=?,"\
        "DISCOUNTARTICLE=?,"\
        "BASE_VALUE=?,"\
        "MANUFACTURERNO=?,"\
        "GROSSPROFITPCT=?,"\
        "ADDONDISCOUNTOK=?,"\
        "PROMOTION_NO=?"
/* SqlDefine of STOTINKEN *****************************************************/


#define STOTINKEN_UPDLISTE \
        "PREISEKAPO=?,"\
        "FILIALNR=?,"\
        "ARTIKEL_NR=?,"\
        "BESTAND=?,"\
        "TAXLEVEL=?,"\
        "ARTIKEL_LANGNAME=?"
/* SqlMacros-Define of PRODUCTPROMO *******************************************/

#define PRODUCTPROMO_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->PROMOTION_NO,\
        :x->ARTICLENO,\
        :x->NAME,\
        :x->PREISEKAPO,\
        :x->CUSTOMERNO,\
        :x->ADDONSTDDISCOK,\
        :x->DISCOUNTVALUEPCT,\
        :x->MAXQTY,\
        :x->BESTAND,\
        :x->ARTIKELAKTIV,\
        :x->TAXLEVEL,\
        :x->ARTIKEL_LANGNAME
#define PRODUCTPROMO_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->PROMOTION_NO,\
        :x->ARTICLENO,\
        :x->NAME,\
        :x->PREISEKAPO,\
        :x->CUSTOMERNO,\
        :x->ADDONSTDDISCOK,\
        :x->DISCOUNTVALUEPCT,\
        :x->MAXQTY,\
        :x->BESTAND,\
        :x->ARTIKELAKTIV,\
        :x->TAXLEVEL,\
        :x->ARTIKEL_LANGNAME

/* SqlMacros-Define of PROMOHERST *********************************************/

#define PROMOHERST_ZEIGER(x) \
        :x->PREISEKAPO,\
        :x->DATUMVERFALL,\
        :x->PREIS_TYP,\
        :x->FILIALNR,\
        :x->ARTIKEL_NR,\
        :x->BESTAND,\
        :x->ARTIKELAKTIV,\
        :x->HERSTELLER_NR,\
        :x->TAXLEVEL,\
        :x->HEALTHFUNDCODE,\
        :x->ARTIKEL_LANGNAME
#define PROMOHERST_ZEIGERSEL(x) \
        :x->PREISEKAPO,\
        :x->DATUMVERFALL,\
        :x->PREIS_TYP,\
        :x->FILIALNR,\
        :x->ARTIKEL_NR,\
        :x->BESTAND,\
        :x->ARTIKELAKTIV,\
        :x->HERSTELLER_NR,\
        :x->TAXLEVEL,\
        :x->HEALTHFUNDCODE,\
        :x->ARTIKEL_LANGNAME

/* SqlMacros-Define of PROMOMANUFACT ******************************************/

#define PROMOMANUFACT_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->DATEFROM,\
        :x->DATETO,\
        :x->MANUFACTURERNO,\
        :x->PROMOTION_NO
#define PROMOMANUFACT_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->DATEFROM,\
        :x->DATETO,\
        :x->MANUFACTURERNO,\
        :x->PROMOTION_NO

/* SqlMacros-Define of PROMOMEMBERS *******************************************/

#define PROMOMEMBERS_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->DISCOUNTGRPNO,\
        :x->DATUMVERFALL,\
        :x->BASEQTY,\
        :x->DISCOUNTQTY,\
        :x->DISCOUNTVALUEPCT,\
        :x->NO_MULTIPLE_QTY,\
        :x->MAXQTY,\
        :x->ARTIKEL_NR,\
        :x->ARTIKEL_LANGNAME
#define PROMOMEMBERS_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->DISCOUNTGRPNO,\
        :x->DATUMVERFALL,\
        :x->BASEQTY,\
        :x->DISCOUNTQTY,\
        :x->DISCOUNTVALUEPCT,\
        :x->NO_MULTIPLE_QTY,\
        :x->MAXQTY,\
        :x->ARTIKEL_NR,\
        :x->ARTIKEL_LANGNAME

/* SqlMacros-Define of PROMOTIONEN ********************************************/

#define PROMOTIONEN_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->NAME,\
        :x->DISCOUNTGRPNO,\
        :x->PHARMACYGROUPID,\
        :x->CUSTOMERNO,\
        :x->ADDONSTDDISCOK,\
        :x->DATEFROM,\
        :x->DATETO,\
        :x->BASEQTY,\
        :x->DISCOUNTSPEC,\
        :x->DISCOUNTQTY,\
        :x->DISCOUNTVALUEPCT,\
        :x->DISCOUNTARTICLE,\
        :x->BASE_VALUE,\
        :x->MANUFACTURERNO,\
        :x->GROSSPROFITPCT,\
        :x->ADDONDISCOUNTOK,\
        :x->PROMOTION_NO
#define PROMOTIONEN_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->NAME,\
        :x->DISCOUNTGRPNO,\
        :x->PHARMACYGROUPID,\
        :x->CUSTOMERNO,\
        :x->ADDONSTDDISCOK,\
        :x->DATEFROM,\
        :x->DATETO,\
        :x->BASEQTY,\
        :x->DISCOUNTSPEC,\
        :x->DISCOUNTQTY,\
        :x->DISCOUNTVALUEPCT,\
        :x->DISCOUNTARTICLE,\
        :x->BASE_VALUE,\
        :x->MANUFACTURERNO,\
        :x->GROSSPROFITPCT,\
        :x->ADDONDISCOUNTOK,\
        :x->PROMOTION_NO

/* SqlMacros-Define of STOTINKEN **********************************************/

#define STOTINKEN_ZEIGER(x) \
        :x->PREISEKAPO,\
        :x->FILIALNR,\
        :x->ARTIKEL_NR,\
        :x->BESTAND,\
        :x->TAXLEVEL,\
        :x->ARTIKEL_LANGNAME
#define STOTINKEN_ZEIGERSEL(x) \
        :x->PREISEKAPO,\
        :x->FILIALNR,\
        :x->ARTIKEL_NR,\
        :x->BESTAND,\
        :x->TAXLEVEL,\
        :x->ARTIKEL_LANGNAME

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define PRODUCTPROMO_H
#define PRODUCTPROMO_ANZ ( sizeof(PRODUCTPROMO_BES) / sizeof(struct buf_desc) )
#define PROMOHERST_H
#define PROMOHERST_ANZ ( sizeof(PROMOHERST_BES) / sizeof(struct buf_desc) )
#define PROMOMANUFACT_H
#define PROMOMANUFACT_ANZ ( sizeof(PROMOMANUFACT_BES) / sizeof(struct buf_desc) )
#define PROMOMEMBERS_H
#define PROMOMEMBERS_ANZ ( sizeof(PROMOMEMBERS_BES) / sizeof(struct buf_desc) )
#define PROMOTIONEN_H
#define PROMOTIONEN_ANZ ( sizeof(PROMOTIONEN_BES) / sizeof(struct buf_desc) )
#define STOTINKEN_H
#define STOTINKEN_ANZ ( sizeof(STOTINKEN_BES) / sizeof(struct buf_desc) )
#endif

#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of PRODUCTPROMO ********************************************/

#ifndef TRANSCLASS
typedef struct N_PRODUCTPROMO {
    short BRANCHNO;
    short PROMOTION_NO;
    long ARTICLENO;
    char NAME[31];
    double PREISEKAPO;
    long CUSTOMERNO;
    char ADDONSTDDISCOK[2];
    double DISCOUNTVALUEPCT;
    long MAXQTY;
    long BESTAND;
    char ARTIKELAKTIV[2];
    short TAXLEVEL;
    char ARTIKEL_LANGNAME[51];
    long FETCH_REL;
} productpromoS;
#else /* TRANSCLASS */
typedef struct N_PRODUCTPROMO {
    short BRANCHNO;
    short PROMOTION_NO;
    long ARTICLENO;
    char NAME[31];
    double PREISEKAPO;
    long CUSTOMERNO;
    char ADDONSTDDISCOK[2];
    double DISCOUNTVALUEPCT;
    long MAXQTY;
    long BESTAND;
    char ARTIKELAKTIV[2];
    short TAXLEVEL;
    char ARTIKEL_LANGNAME[51];
    long FETCH_REL;
    bool operator == (const N_PRODUCTPROMO& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            PROMOTION_NO == right.PROMOTION_NO &&
            ARTICLENO == right.ARTICLENO &&
            !strcmp(NAME, right.NAME) &&
            PREISEKAPO == right.PREISEKAPO &&
            CUSTOMERNO == right.CUSTOMERNO &&
            !strcmp(ADDONSTDDISCOK, right.ADDONSTDDISCOK) &&
            DISCOUNTVALUEPCT == right.DISCOUNTVALUEPCT &&
            MAXQTY == right.MAXQTY &&
            BESTAND == right.BESTAND &&
            !strcmp(ARTIKELAKTIV, right.ARTIKELAKTIV) &&
            TAXLEVEL == right.TAXLEVEL &&
            !strcmp(ARTIKEL_LANGNAME, right.ARTIKEL_LANGNAME)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        PROMOTION_NO = 0;
        ARTICLENO = 0;
        strcpy(NAME, " " );
        PREISEKAPO = 0;
        CUSTOMERNO = 0;
        strcpy(ADDONSTDDISCOK, " " );
        DISCOUNTVALUEPCT = 0;
        MAXQTY = 0;
        BESTAND = 0;
        strcpy(ARTIKELAKTIV, " " );
        TAXLEVEL = 0;
        strcpy(ARTIKEL_LANGNAME, " " );
#endif
    }
} productpromoS;
#endif /* TRANSCLASS */

/* original struct of PROMOHERST **********************************************/

#ifndef TRANSCLASS
typedef struct N_PROMOHERST {
    double PREISEKAPO;
    long DATUMVERFALL;
    long DATEFROM;
    short PREIS_TYP;
    short PROMOTION_NO;
    short FILIALNR;
    long ARTIKEL_NR;
    long BESTAND;
    char ARTIKELAKTIV[2];
    long HERSTELLER_NR;
    short TAXLEVEL;
    char HEALTHFUNDCODE[6];
    char ARTIKEL_LANGNAME[51];
    long FETCH_REL;
} promoherstS;
#else /* TRANSCLASS */
typedef struct N_PROMOHERST {
    double PREISEKAPO;
    long DATUMVERFALL;
    long DATEFROM;
    short PREIS_TYP;
    short PROMOTION_NO;
    short FILIALNR;
    long ARTIKEL_NR;
    long BESTAND;
    char ARTIKELAKTIV[2];
    long HERSTELLER_NR;
    short TAXLEVEL;
    char HEALTHFUNDCODE[6];
    char ARTIKEL_LANGNAME[51];
    long FETCH_REL;
    bool operator == (const N_PROMOHERST& right) const {
        return (
            PREISEKAPO == right.PREISEKAPO &&
            DATUMVERFALL == right.DATUMVERFALL &&
            DATEFROM == right.DATEFROM &&
            PREIS_TYP == right.PREIS_TYP &&
            PROMOTION_NO == right.PROMOTION_NO &&
            FILIALNR == right.FILIALNR &&
            ARTIKEL_NR == right.ARTIKEL_NR &&
            BESTAND == right.BESTAND &&
            !strcmp(ARTIKELAKTIV, right.ARTIKELAKTIV) &&
            HERSTELLER_NR == right.HERSTELLER_NR &&
            TAXLEVEL == right.TAXLEVEL &&
            !strcmp(HEALTHFUNDCODE, right.HEALTHFUNDCODE) &&
            !strcmp(ARTIKEL_LANGNAME, right.ARTIKEL_LANGNAME)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        PREISEKAPO = 0;
        DATUMVERFALL = 0;
        DATEFROM = 0;
        PREIS_TYP = 0;
        PROMOTION_NO = 0;
        FILIALNR = 0;
        ARTIKEL_NR = 0;
        BESTAND = 0;
        strcpy(ARTIKELAKTIV, " " );
        HERSTELLER_NR = 0;
        TAXLEVEL = 0;
        strcpy(HEALTHFUNDCODE, " " );
        strcpy(ARTIKEL_LANGNAME, " " );
#endif
    }
} promoherstS;
#endif /* TRANSCLASS */

/* original struct of PROMOMANUFACT *******************************************/

#ifndef TRANSCLASS
typedef struct N_PROMOMANUFACT {
    short BRANCHNO;
    long DATEFROM;
    long DATETO;
    long MANUFACTURERNO;
    short PROMOTION_NO;
    long FETCH_REL;
} promomanufactS;
#else /* TRANSCLASS */
typedef struct N_PROMOMANUFACT {
    short BRANCHNO;
    long DATEFROM;
    long DATETO;
    long MANUFACTURERNO;
    short PROMOTION_NO;
    long FETCH_REL;
    bool operator == (const N_PROMOMANUFACT& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            DATEFROM == right.DATEFROM &&
            DATETO == right.DATETO &&
            MANUFACTURERNO == right.MANUFACTURERNO &&
            PROMOTION_NO == right.PROMOTION_NO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        DATEFROM = 0;
        DATETO = 0;
        MANUFACTURERNO = 0;
        PROMOTION_NO = 0;
#endif
    }
} promomanufactS;
#endif /* TRANSCLASS */

/* original struct of PROMOMEMBERS ********************************************/

#ifndef TRANSCLASS
typedef struct N_PROMOMEMBERS {
    short BRANCHNO;
    long DISCOUNTGRPNO;
    long DATUMVERFALL;
    long BASEQTY;
    short DISCOUNTQTY;
    double DISCOUNTVALUEPCT;
    char NO_MULTIPLE_QTY[2];
    long MAXQTY;
    long ARTIKEL_NR;
    char ARTIKEL_LANGNAME[51];
    long FETCH_REL;
} promomembersS;
#else /* TRANSCLASS */
typedef struct N_PROMOMEMBERS {
    short BRANCHNO;
    long DISCOUNTGRPNO;
    long DATUMVERFALL;
    long BASEQTY;
    short DISCOUNTQTY;
    double DISCOUNTVALUEPCT;
    char NO_MULTIPLE_QTY[2];
    long MAXQTY;
    long ARTIKEL_NR;
    char ARTIKEL_LANGNAME[51];
    long FETCH_REL;
    bool operator == (const N_PROMOMEMBERS& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            DISCOUNTGRPNO == right.DISCOUNTGRPNO &&
            DATUMVERFALL == right.DATUMVERFALL &&
            BASEQTY == right.BASEQTY &&
            DISCOUNTQTY == right.DISCOUNTQTY &&
            DISCOUNTVALUEPCT == right.DISCOUNTVALUEPCT &&
            !strcmp(NO_MULTIPLE_QTY, right.NO_MULTIPLE_QTY) &&
            MAXQTY == right.MAXQTY &&
            ARTIKEL_NR == right.ARTIKEL_NR &&
            !strcmp(ARTIKEL_LANGNAME, right.ARTIKEL_LANGNAME)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        DISCOUNTGRPNO = 0;
        DATUMVERFALL = 0;
        BASEQTY = 0;
        DISCOUNTQTY = 0;
        DISCOUNTVALUEPCT = 0;
        strcpy(NO_MULTIPLE_QTY, " " );
        MAXQTY = 0;
        ARTIKEL_NR = 0;
        strcpy(ARTIKEL_LANGNAME, " " );
#endif
    }
} promomembersS;
#endif /* TRANSCLASS */

/* original struct of PROMOTIONEN *********************************************/

#ifndef TRANSCLASS
typedef struct N_PROMOTIONEN {
    short BRANCHNO;
    char NAME[31];
    long DISCOUNTGRPNO;
    char PHARMACYGROUPID[4];
    long CUSTOMERNO;
    char ADDONSTDDISCOK[2];
    long DATEFROM;
    long DATETO;
    long BASEQTY;
    short DISCOUNTSPEC;
    short DISCOUNTQTY;
    double DISCOUNTVALUEPCT;
    long DISCOUNTARTICLE;
    double BASE_VALUE;
    long MANUFACTURERNO;
    double GROSSPROFITPCT;
    char ADDONDISCOUNTOK[2];
    short PROMOTION_NO;
    long FETCH_REL;
} promotionenS;
#else /* TRANSCLASS */
typedef struct N_PROMOTIONEN {
    short BRANCHNO;
    char NAME[31];
    long DISCOUNTGRPNO;
    char PHARMACYGROUPID[4];
    long CUSTOMERNO;
    char ADDONSTDDISCOK[2];
    long DATEFROM;
    long DATETO;
    long BASEQTY;
    short DISCOUNTSPEC;
    short DISCOUNTQTY;
    double DISCOUNTVALUEPCT;
    long DISCOUNTARTICLE;
    double BASE_VALUE;
    long MANUFACTURERNO;
    double GROSSPROFITPCT;
    char ADDONDISCOUNTOK[2];
    short PROMOTION_NO;
    long FETCH_REL;
    bool operator == (const N_PROMOTIONEN& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            !strcmp(NAME, right.NAME) &&
            DISCOUNTGRPNO == right.DISCOUNTGRPNO &&
            !strcmp(PHARMACYGROUPID, right.PHARMACYGROUPID) &&
            CUSTOMERNO == right.CUSTOMERNO &&
            !strcmp(ADDONSTDDISCOK, right.ADDONSTDDISCOK) &&
            DATEFROM == right.DATEFROM &&
            DATETO == right.DATETO &&
            BASEQTY == right.BASEQTY &&
            DISCOUNTSPEC == right.DISCOUNTSPEC &&
            DISCOUNTQTY == right.DISCOUNTQTY &&
            DISCOUNTVALUEPCT == right.DISCOUNTVALUEPCT &&
            DISCOUNTARTICLE == right.DISCOUNTARTICLE &&
            BASE_VALUE == right.BASE_VALUE &&
            MANUFACTURERNO == right.MANUFACTURERNO &&
            GROSSPROFITPCT == right.GROSSPROFITPCT &&
            !strcmp(ADDONDISCOUNTOK, right.ADDONDISCOUNTOK) &&
            PROMOTION_NO == right.PROMOTION_NO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        strcpy(NAME, " " );
        DISCOUNTGRPNO = 0;
        strcpy(PHARMACYGROUPID, " " );
        CUSTOMERNO = 0;
        strcpy(ADDONSTDDISCOK, " " );
        DATEFROM = 0;
        DATETO = 0;
        BASEQTY = 0;
        DISCOUNTSPEC = 0;
        DISCOUNTQTY = 0;
        DISCOUNTVALUEPCT = 0;
        DISCOUNTARTICLE = 0;
        BASE_VALUE = 0;
        MANUFACTURERNO = 0;
        GROSSPROFITPCT = 0;
        strcpy(ADDONDISCOUNTOK, " " );
        PROMOTION_NO = 0;
#endif
    }
} promotionenS;
#endif /* TRANSCLASS */

/* original struct of STOTINKEN ***********************************************/

#ifndef TRANSCLASS
typedef struct N_STOTINKEN {
    double PREISEKAPO;
    short FILIALNR;
    long ARTIKEL_NR;
    long BESTAND;
    short TAXLEVEL;
    char ARTIKEL_LANGNAME[51];
    long FETCH_REL;
} stotinkenS;
#else /* TRANSCLASS */
typedef struct N_STOTINKEN {
    double PREISEKAPO;
    short FILIALNR;
    long ARTIKEL_NR;
    long BESTAND;
    short TAXLEVEL;
    char ARTIKEL_LANGNAME[51];
    long FETCH_REL;
    bool operator == (const N_STOTINKEN& right) const {
        return (
            PREISEKAPO == right.PREISEKAPO &&
            FILIALNR == right.FILIALNR &&
            ARTIKEL_NR == right.ARTIKEL_NR &&
            BESTAND == right.BESTAND &&
            TAXLEVEL == right.TAXLEVEL &&
            !strcmp(ARTIKEL_LANGNAME, right.ARTIKEL_LANGNAME)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        PREISEKAPO = 0;
        FILIALNR = 0;
        ARTIKEL_NR = 0;
        BESTAND = 0;
        TAXLEVEL = 0;
        strcpy(ARTIKEL_LANGNAME, " " );
#endif
    }
} stotinkenS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of PRODUCTPROMO ********************************/

struct C_PRODUCTPROMO {
    short BRANCHNO;
    short PROMOTION_NO;
    long ARTICLENO;
    char NAME[31];
    double PREISEKAPO;
    long CUSTOMERNO;
    char ADDONSTDDISCOK;
    double DISCOUNTVALUEPCT;
    long MAXQTY;
    long BESTAND;
    char ARTIKELAKTIV;
    short TAXLEVEL;
    char ARTIKEL_LANGNAME[51];
    long FETCH_REL;
};
/* Structur with real chartype of PROMOHERST **********************************/

struct C_PROMOHERST {
    double PREISEKAPO;
    long DATUMVERFALL;
    long DATEFROM;
    short PREIS_TYP;
    short PROMOTION_NO;
    short FILIALNR;
    long ARTIKEL_NR;
    long BESTAND;
    char ARTIKELAKTIV;
    long HERSTELLER_NR;
    short TAXLEVEL;
    char HEALTHFUNDCODE[6];
    char ARTIKEL_LANGNAME[51];
    long FETCH_REL;
};
/* Structur with real chartype of PROMOMANUFACT *******************************/

struct C_PROMOMANUFACT {
    short BRANCHNO;
    long DATEFROM;
    long DATETO;
    long MANUFACTURERNO;
    short PROMOTION_NO;
    long FETCH_REL;
};
/* Structur with real chartype of PROMOMEMBERS ********************************/

struct C_PROMOMEMBERS {
    short BRANCHNO;
    long DISCOUNTGRPNO;
    long DATUMVERFALL;
    long BASEQTY;
    short DISCOUNTQTY;
    double DISCOUNTVALUEPCT;
    char NO_MULTIPLE_QTY;
    long MAXQTY;
    long ARTIKEL_NR;
    char ARTIKEL_LANGNAME[51];
    long FETCH_REL;
};
/* Structur with real chartype of PROMOTIONEN *********************************/

struct C_PROMOTIONEN {
    short BRANCHNO;
    char NAME[31];
    long DISCOUNTGRPNO;
    char PHARMACYGROUPID[4];
    long CUSTOMERNO;
    char ADDONSTDDISCOK;
    long DATEFROM;
    long DATETO;
    long BASEQTY;
    short DISCOUNTSPEC;
    short DISCOUNTQTY;
    double DISCOUNTVALUEPCT;
    long DISCOUNTARTICLE;
    double BASE_VALUE;
    long MANUFACTURERNO;
    double GROSSPROFITPCT;
    char ADDONDISCOUNTOK;
    short PROMOTION_NO;
    long FETCH_REL;
};
/* Structur with real chartype of STOTINKEN ***********************************/

struct C_STOTINKEN {
    double PREISEKAPO;
    short FILIALNR;
    long ARTIKEL_NR;
    long BESTAND;
    short TAXLEVEL;
    char ARTIKEL_LANGNAME[51];
    long FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of PRODUCTPROMO ******************************/

struct I_PRODUCTPROMO {
    short BRANCHNO;
    short PROMOTION_NO;
    short ARTICLENO;
    short NAME;
    short PREISEKAPO;
    short CUSTOMERNO;
    short ADDONSTDDISCOK;
    short DISCOUNTVALUEPCT;
    short MAXQTY;
    short BESTAND;
    short ARTIKELAKTIV;
    short TAXLEVEL;
    short ARTIKEL_LANGNAME;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of PROMOHERST ********************************/

struct I_PROMOHERST {
    short PREISEKAPO;
    short DATUMVERFALL;
    short DATEFROM;
    short PREIS_TYP;
    short PROMOTION_NO;
    short FILIALNR;
    short ARTIKEL_NR;
    short BESTAND;
    short ARTIKELAKTIV;
    short HERSTELLER_NR;
    short TAXLEVEL;
    short HEALTHFUNDCODE;
    short ARTIKEL_LANGNAME;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of PROMOMANUFACT *****************************/

struct I_PROMOMANUFACT {
    short BRANCHNO;
    short DATEFROM;
    short DATETO;
    short MANUFACTURERNO;
    short PROMOTION_NO;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of PROMOMEMBERS ******************************/

struct I_PROMOMEMBERS {
    short BRANCHNO;
    short DISCOUNTGRPNO;
    short DATUMVERFALL;
    short BASEQTY;
    short DISCOUNTQTY;
    short DISCOUNTVALUEPCT;
    short NO_MULTIPLE_QTY;
    short MAXQTY;
    short ARTIKEL_NR;
    short ARTIKEL_LANGNAME;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of PROMOTIONEN *******************************/

struct I_PROMOTIONEN {
    short BRANCHNO;
    short NAME;
    short DISCOUNTGRPNO;
    short PHARMACYGROUPID;
    short CUSTOMERNO;
    short ADDONSTDDISCOK;
    short DATEFROM;
    short DATETO;
    short BASEQTY;
    short DISCOUNTSPEC;
    short DISCOUNTQTY;
    short DISCOUNTVALUEPCT;
    short DISCOUNTARTICLE;
    short BASE_VALUE;
    short MANUFACTURERNO;
    short GROSSPROFITPCT;
    short ADDONDISCOUNTOK;
    short PROMOTION_NO;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of STOTINKEN *********************************/

struct I_STOTINKEN {
    short PREISEKAPO;
    short FILIALNR;
    short ARTIKEL_NR;
    short BESTAND;
    short TAXLEVEL;
    short ARTIKEL_LANGNAME;
    short FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of PRODUCTPROMO ****************************************/

#if defined (BUF_DESC)
static struct buf_desc PRODUCTPROMO_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_D, 9, 2 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_D, 5, 2 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 50, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc PRODUCTPROMO_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_D, 9, 2 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_D, 5, 2 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 50, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of PROMOHERST ******************************************/

#if defined (BUF_DESC)
static struct buf_desc PROMOHERST_BES [] = {
   { TYP_D, 9, 2 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 5, 0 },
   { TYP_C, 50, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc PROMOHERST_BES [] = {
   { TYP_D, 9, 2 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 5, 0 },
   { TYP_C, 50, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of PROMOMANUFACT ***************************************/

#if defined (BUF_DESC)
static struct buf_desc PROMOMANUFACT_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc PROMOMANUFACT_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of PROMOMEMBERS ****************************************/

#if defined (BUF_DESC)
static struct buf_desc PROMOMEMBERS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 50, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc PROMOMEMBERS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 50, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of PROMOTIONEN *****************************************/

#if defined (BUF_DESC)
static struct buf_desc PROMOTIONEN_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 3, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_L , 11, 0 },
   { TYP_D, 10, 2 },
   { TYP_L , 11, 0 },
   { TYP_D, 5, 2 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc PROMOTIONEN_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 3, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_L , 11, 0 },
   { TYP_D, 10, 2 },
   { TYP_L , 11, 0 },
   { TYP_D, 5, 2 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of STOTINKEN *******************************************/

#if defined (BUF_DESC)
static struct buf_desc STOTINKEN_BES [] = {
   { TYP_D, 9, 2 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 50, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc STOTINKEN_BES [] = {
   { TYP_D, 9, 2 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 50, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* FunctionNumber-Define of ProductPromo **************************************/

#define PRODUCTPROMO_SELLIST 1537

/* FunctionNumber-Define of PromoHerst ****************************************/

#define PROMOHERST_SELLIST 1536

/* FunctionNumber-Define of PromoManufact *************************************/

#define PROMOMANUFACT_SELMANUNO 1539

/* FunctionNumber-Define of PromoMembers **************************************/

#define PROMOMEMBERS_SELLIST 1529

/* FunctionNumber-Define of Promotionen ***************************************/

#define PROMOTIONEN_SELLIST 1528
#define PROMOTIONEN_SELLISTMANU 1534
#define PROMOTIONEN_SELPROMONO 1532
#define PROMOTIONEN_SELPROMONOMANU 1535

/* FunctionNumber-Define of Stotinken *****************************************/

#define STOTINKEN_SELLIST 1538

#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of ProductPromo **********************************/

#define SelList 1537

/* Old-FunctionNumber-Define of PromoHerst ************************************/

#define SelList 1536

/* Old-FunctionNumber-Define of PromoManufact *********************************/

#define SelManuNo 1539

/* Old-FunctionNumber-Define of PromoMembers **********************************/

#define SelList 1529

/* Old-FunctionNumber-Define of Promotionen ***********************************/

#define SelList 1528
#define SelListManu 1534
#define SelPromoNo 1532
#define SelPromoNoManu 1535

/* Old-FunctionNumber-Define of Stotinken *************************************/

#define SelList 1538

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

class CPRODUCTPROMO : public ppDadeVirtual {
public:
    productpromoS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<productpromoS> lst; // class list

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
                     vector< productpromoS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     productpromoS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< productpromoS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<productpromoS>::iterator
                 beginList() { return lst.begin(); }
    vector<productpromoS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    short        GetPromotion_no() const { return s.PROMOTION_NO; }
    long         GetArticleno() const { return s.ARTICLENO; }
    const char*  GetName(ppString & t) const { t = s.NAME; t.erasespace(ppString::END); return t.c_str(); }
    double       GetPreisekapo() const { return s.PREISEKAPO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    char         GetAddonstddiscok() const { return s.ADDONSTDDISCOK[0]; }
    double       GetDiscountvaluepct() const { return s.DISCOUNTVALUEPCT; }
    long         GetMaxqty() const { return s.MAXQTY; }
    long         GetBestand() const { return s.BESTAND; }
    char         GetArtikelaktiv() const { return s.ARTIKELAKTIV[0]; }
    short        GetTaxlevel() const { return s.TAXLEVEL; }
    const char*  GetArtikel_langname(ppString & t) const { t = s.ARTIKEL_LANGNAME; t.erasespace(ppString::END); return t.c_str(); }

    const productpromoS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetPromotion_no(short t) { s.PROMOTION_NO = t; }
    void         SetArticleno(long t) { s.ARTICLENO = t; }
    void         SetName(const ppString & t) { ppGStrCopy(s.NAME, t.c_str(), L_PRODUCTPROMO_NAME); }
    void         SetPreisekapo(double t) { s.PREISEKAPO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetAddonstddiscok(char t) { s.ADDONSTDDISCOK[0] = t; s.ADDONSTDDISCOK[1] = '\0';}
    void         SetDiscountvaluepct(double t) { s.DISCOUNTVALUEPCT = t; }
    void         SetMaxqty(long t) { s.MAXQTY = t; }
    void         SetBestand(long t) { s.BESTAND = t; }
    void         SetArtikelaktiv(char t) { s.ARTIKELAKTIV[0] = t; s.ARTIKELAKTIV[1] = '\0';}
    void         SetTaxlevel(short t) { s.TAXLEVEL = t; }
    void         SetArtikel_langname(const ppString & t) { ppGStrCopy(s.ARTIKEL_LANGNAME, t.c_str(), L_PRODUCTPROMO_ARTIKEL_LANGNAME); }

    void         SetStruct(const productpromoS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1537, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CPRODUCTPROMO() {
        ::buf_default((void *)&s, PRODUCTPROMO_BES, PRODUCTPROMO_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CPRODUCTPROMO() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, PRODUCTPROMO_BES, PRODUCTPROMO_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, PRODUCTPROMO_BES, (int)PRODUCTPROMO_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1537 ) return CursorServerCall(1537, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_PRODUCTPROMO & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.NAME);
        ppGStripLast(d.ARTIKEL_LANGNAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, PRODUCTPROMO_BES, (int)PRODUCTPROMO_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CPRODUCTPROMO c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, PRODUCTPROMO_BES, (int)PRODUCTPROMO_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CPROMOHERST : public ppDadeVirtual {
public:
    promoherstS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<promoherstS> lst; // class list

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
                     vector< promoherstS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     promoherstS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< promoherstS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<promoherstS>::iterator
                 beginList() { return lst.begin(); }
    vector<promoherstS>::iterator
                 endList  () { return lst.end  (); }

    double       GetPreisekapo() const { return s.PREISEKAPO; }
    long         GetDatumverfall() const { return s.DATUMVERFALL; }
    long         GetDatefrom() const { return s.DATEFROM; }
    short        GetPreis_typ() const { return s.PREIS_TYP; }
    short        GetPromotion_no() const { return s.PROMOTION_NO; }
    short        GetFilialnr() const { return s.FILIALNR; }
    long         GetArtikel_nr() const { return s.ARTIKEL_NR; }
    long         GetBestand() const { return s.BESTAND; }
    char         GetArtikelaktiv() const { return s.ARTIKELAKTIV[0]; }
    long         GetHersteller_nr() const { return s.HERSTELLER_NR; }
    short        GetTaxlevel() const { return s.TAXLEVEL; }
    const char*  GetHealthfundcode(ppString & t) const { t = s.HEALTHFUNDCODE; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetArtikel_langname(ppString & t) const { t = s.ARTIKEL_LANGNAME; t.erasespace(ppString::END); return t.c_str(); }

    const promoherstS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetPreisekapo(double t) { s.PREISEKAPO = t; }
    void         SetDatumverfall(long t) { s.DATUMVERFALL = t; }
    void         SetDatefrom(long t) { s.DATEFROM = t; }
    void         SetPreis_typ(short t) { s.PREIS_TYP = t; }
    void         SetPromotion_no(short t) { s.PROMOTION_NO = t; }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetArtikel_nr(long t) { s.ARTIKEL_NR = t; }
    void         SetBestand(long t) { s.BESTAND = t; }
    void         SetArtikelaktiv(char t) { s.ARTIKELAKTIV[0] = t; s.ARTIKELAKTIV[1] = '\0';}
    void         SetHersteller_nr(long t) { s.HERSTELLER_NR = t; }
    void         SetTaxlevel(short t) { s.TAXLEVEL = t; }
    void         SetHealthfundcode(const ppString & t) { ppGStrCopy(s.HEALTHFUNDCODE, t.c_str(), L_PROMOHERST_HEALTHFUNDCODE); }
    void         SetArtikel_langname(const ppString & t) { ppGStrCopy(s.ARTIKEL_LANGNAME, t.c_str(), L_PROMOHERST_ARTIKEL_LANGNAME); }

    void         SetStruct(const promoherstS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1536, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CPROMOHERST() {
        ::buf_default((void *)&s, PROMOHERST_BES, PROMOHERST_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CPROMOHERST() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, PROMOHERST_BES, PROMOHERST_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, PROMOHERST_BES, (int)PROMOHERST_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1536 ) return CursorServerCall(1536, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_PROMOHERST & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.HEALTHFUNDCODE);
        ppGStripLast(d.ARTIKEL_LANGNAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, PROMOHERST_BES, (int)PROMOHERST_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CPROMOHERST c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, PROMOHERST_BES, (int)PROMOHERST_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CPROMOMANUFACT : public ppDadeVirtual {
public:
    promomanufactS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<promomanufactS> lst; // class list

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
                     vector< promomanufactS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     promomanufactS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< promomanufactS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<promomanufactS>::iterator
                 beginList() { return lst.begin(); }
    vector<promomanufactS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetDatefrom() const { return s.DATEFROM; }
    long         GetDateto() const { return s.DATETO; }
    long         GetManufacturerno() const { return s.MANUFACTURERNO; }
    short        GetPromotion_no() const { return s.PROMOTION_NO; }

    const promomanufactS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetDatefrom(long t) { s.DATEFROM = t; }
    void         SetDateto(long t) { s.DATETO = t; }
    void         SetManufacturerno(long t) { s.MANUFACTURERNO = t; }
    void         SetPromotion_no(short t) { s.PROMOTION_NO = t; }

    void         SetStruct(const promomanufactS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelManuNo(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1539, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CPROMOMANUFACT() {
        ::buf_default((void *)&s, PROMOMANUFACT_BES, PROMOMANUFACT_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CPROMOMANUFACT() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, PROMOMANUFACT_BES, PROMOMANUFACT_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, PROMOMANUFACT_BES, (int)PROMOMANUFACT_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1539 ) return CursorServerCall(1539, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_PROMOMANUFACT & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, PROMOMANUFACT_BES, (int)PROMOMANUFACT_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CPROMOMANUFACT c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, PROMOMANUFACT_BES, (int)PROMOMANUFACT_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CPROMOMEMBERS : public ppDadeVirtual {
public:
    promomembersS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<promomembersS> lst; // class list

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
                     vector< promomembersS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     promomembersS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< promomembersS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<promomembersS>::iterator
                 beginList() { return lst.begin(); }
    vector<promomembersS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetDiscountgrpno() const { return s.DISCOUNTGRPNO; }
    long         GetDatumverfall() const { return s.DATUMVERFALL; }
    long         GetBaseqty() const { return s.BASEQTY; }
    short        GetDiscountqty() const { return s.DISCOUNTQTY; }
    double       GetDiscountvaluepct() const { return s.DISCOUNTVALUEPCT; }
    char         GetNo_multiple_qty() const { return s.NO_MULTIPLE_QTY[0]; }
    long         GetMaxqty() const { return s.MAXQTY; }
    long         GetArtikel_nr() const { return s.ARTIKEL_NR; }
    const char*  GetArtikel_langname(ppString & t) const { t = s.ARTIKEL_LANGNAME; t.erasespace(ppString::END); return t.c_str(); }

    const promomembersS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetDiscountgrpno(long t) { s.DISCOUNTGRPNO = t; }
    void         SetDatumverfall(long t) { s.DATUMVERFALL = t; }
    void         SetBaseqty(long t) { s.BASEQTY = t; }
    void         SetDiscountqty(short t) { s.DISCOUNTQTY = t; }
    void         SetDiscountvaluepct(double t) { s.DISCOUNTVALUEPCT = t; }
    void         SetNo_multiple_qty(char t) { s.NO_MULTIPLE_QTY[0] = t; s.NO_MULTIPLE_QTY[1] = '\0';}
    void         SetMaxqty(long t) { s.MAXQTY = t; }
    void         SetArtikel_nr(long t) { s.ARTIKEL_NR = t; }
    void         SetArtikel_langname(const ppString & t) { ppGStrCopy(s.ARTIKEL_LANGNAME, t.c_str(), L_PROMOMEMBERS_ARTIKEL_LANGNAME); }

    void         SetStruct(const promomembersS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1529, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CPROMOMEMBERS() {
        ::buf_default((void *)&s, PROMOMEMBERS_BES, PROMOMEMBERS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CPROMOMEMBERS() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, PROMOMEMBERS_BES, PROMOMEMBERS_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, PROMOMEMBERS_BES, (int)PROMOMEMBERS_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1529 ) return CursorServerCall(1529, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_PROMOMEMBERS & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.ARTIKEL_LANGNAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, PROMOMEMBERS_BES, (int)PROMOMEMBERS_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CPROMOMEMBERS c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, PROMOMEMBERS_BES, (int)PROMOMEMBERS_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CPROMOTIONEN : public ppDadeVirtual {
public:
    promotionenS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<promotionenS> lst; // class list

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
                     vector< promotionenS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     promotionenS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< promotionenS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<promotionenS>::iterator
                 beginList() { return lst.begin(); }
    vector<promotionenS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    const char*  GetName(ppString & t) const { t = s.NAME; t.erasespace(ppString::END); return t.c_str(); }
    long         GetDiscountgrpno() const { return s.DISCOUNTGRPNO; }
    const char*  GetPharmacygroupid(ppString & t) const { t = s.PHARMACYGROUPID; t.erasespace(ppString::END); return t.c_str(); }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    char         GetAddonstddiscok() const { return s.ADDONSTDDISCOK[0]; }
    long         GetDatefrom() const { return s.DATEFROM; }
    long         GetDateto() const { return s.DATETO; }
    long         GetBaseqty() const { return s.BASEQTY; }
    short        GetDiscountspec() const { return s.DISCOUNTSPEC; }
    short        GetDiscountqty() const { return s.DISCOUNTQTY; }
    double       GetDiscountvaluepct() const { return s.DISCOUNTVALUEPCT; }
    long         GetDiscountarticle() const { return s.DISCOUNTARTICLE; }
    double       GetBase_value() const { return s.BASE_VALUE; }
    long         GetManufacturerno() const { return s.MANUFACTURERNO; }
    double       GetGrossprofitpct() const { return s.GROSSPROFITPCT; }
    char         GetAddondiscountok() const { return s.ADDONDISCOUNTOK[0]; }
    short        GetPromotion_no() const { return s.PROMOTION_NO; }

    const promotionenS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetName(const ppString & t) { ppGStrCopy(s.NAME, t.c_str(), L_PROMOTIONEN_NAME); }
    void         SetDiscountgrpno(long t) { s.DISCOUNTGRPNO = t; }
    void         SetPharmacygroupid(const ppString & t) { ppGStrCopy(s.PHARMACYGROUPID, t.c_str(), L_PROMOTIONEN_PHARMACYGROUPID); }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetAddonstddiscok(char t) { s.ADDONSTDDISCOK[0] = t; s.ADDONSTDDISCOK[1] = '\0';}
    void         SetDatefrom(long t) { s.DATEFROM = t; }
    void         SetDateto(long t) { s.DATETO = t; }
    void         SetBaseqty(long t) { s.BASEQTY = t; }
    void         SetDiscountspec(short t) { s.DISCOUNTSPEC = t; }
    void         SetDiscountqty(short t) { s.DISCOUNTQTY = t; }
    void         SetDiscountvaluepct(double t) { s.DISCOUNTVALUEPCT = t; }
    void         SetDiscountarticle(long t) { s.DISCOUNTARTICLE = t; }
    void         SetBase_value(double t) { s.BASE_VALUE = t; }
    void         SetManufacturerno(long t) { s.MANUFACTURERNO = t; }
    void         SetGrossprofitpct(double t) { s.GROSSPROFITPCT = t; }
    void         SetAddondiscountok(char t) { s.ADDONDISCOUNTOK[0] = t; s.ADDONDISCOUNTOK[1] = '\0';}
    void         SetPromotion_no(short t) { s.PROMOTION_NO = t; }

    void         SetStruct(const promotionenS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1528, FetchRel, pos); return ret; }
    int          SelListManu(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1534, FetchRel, pos); return ret; }
    int          SelPromoNo(int pos = 0) { int ret = UniqueServerCall(1532, pos); Strip(s); return ret; }
    int          SelPromoNoManu(int pos = 0) { int ret = UniqueServerCall(1535, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CPROMOTIONEN() {
        ::buf_default((void *)&s, PROMOTIONEN_BES, PROMOTIONEN_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CPROMOTIONEN() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, PROMOTIONEN_BES, PROMOTIONEN_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, PROMOTIONEN_BES, (int)PROMOTIONEN_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1528 ) return CursorServerCall(1528, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1534 ) return CursorServerCall(1534, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1532 ) return UniqueServerCall(1532, pos);
        if ( fkt_nr == 1535 ) return UniqueServerCall(1535, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_PROMOTIONEN & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.NAME);
        ppGStripLast(d.PHARMACYGROUPID);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, PROMOTIONEN_BES, (int)PROMOTIONEN_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CPROMOTIONEN c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, PROMOTIONEN_BES, (int)PROMOTIONEN_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CSTOTINKEN : public ppDadeVirtual {
public:
    stotinkenS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<stotinkenS> lst; // class list

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
                     vector< stotinkenS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     stotinkenS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< stotinkenS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<stotinkenS>::iterator
                 beginList() { return lst.begin(); }
    vector<stotinkenS>::iterator
                 endList  () { return lst.end  (); }

    double       GetPreisekapo() const { return s.PREISEKAPO; }
    short        GetFilialnr() const { return s.FILIALNR; }
    long         GetArtikel_nr() const { return s.ARTIKEL_NR; }
    long         GetBestand() const { return s.BESTAND; }
    short        GetTaxlevel() const { return s.TAXLEVEL; }
    const char*  GetArtikel_langname(ppString & t) const { t = s.ARTIKEL_LANGNAME; t.erasespace(ppString::END); return t.c_str(); }

    const stotinkenS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetPreisekapo(double t) { s.PREISEKAPO = t; }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetArtikel_nr(long t) { s.ARTIKEL_NR = t; }
    void         SetBestand(long t) { s.BESTAND = t; }
    void         SetTaxlevel(short t) { s.TAXLEVEL = t; }
    void         SetArtikel_langname(const ppString & t) { ppGStrCopy(s.ARTIKEL_LANGNAME, t.c_str(), L_STOTINKEN_ARTIKEL_LANGNAME); }

    void         SetStruct(const stotinkenS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1538, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CSTOTINKEN() {
        ::buf_default((void *)&s, STOTINKEN_BES, STOTINKEN_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CSTOTINKEN() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, STOTINKEN_BES, STOTINKEN_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, STOTINKEN_BES, (int)STOTINKEN_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1538 ) return CursorServerCall(1538, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_STOTINKEN & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.ARTIKEL_LANGNAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, STOTINKEN_BES, (int)STOTINKEN_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CSTOTINKEN c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, STOTINKEN_BES, (int)STOTINKEN_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};
#endif    // TRANSCLASS

#endif   // GUARD
