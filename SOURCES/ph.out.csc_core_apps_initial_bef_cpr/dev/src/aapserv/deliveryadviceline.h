#ifndef __PP_DELIVERYADVICELINE_H_
#define __PP_DELIVERYADVICELINE_H_

/******************************************************************************/
/* c:\prri\Headerfiles\Deliveryadviceline *************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of DELIVERYADVICELINE ****************************************/

#define L_DELIVERYADVICELINE_BRANCHNO 6
#define L_DELIVERYADVICELINE_CUSTOMERNO 11
#define L_DELIVERYADVICELINE_DELIVERYADVICEDATE 11
#define L_DELIVERYADVICELINE_DELIVERYADVICENO 10
#define L_DELIVERYADVICELINE_DAVAT 1
#define L_DELIVERYADVICELINE_VATPERCENTAGE 5
#define N_DELIVERYADVICELINE_VATPERCENTAGE 2
#define L_DELIVERYADVICELINE_DELIVERYADVICEPOSNO 11
#define L_DELIVERYADVICELINE_PHARMOSORDERPOSNO 11
#define L_DELIVERYADVICELINE_CSCORDERPOSNO 11
#define L_DELIVERYADVICELINE_ARTICLENO 11
#define L_DELIVERYADVICELINE_ARTICLE_CODE 25
#define L_DELIVERYADVICELINE_QTY_ORDERED 11
#define L_DELIVERYADVICELINE_QTY_CONFIRMED 11
#define L_DELIVERYADVICELINE_QTY_REBATEINKIND 11
#define L_DELIVERYADVICELINE_QTY_INVOICED 11
#define L_DELIVERYADVICELINE_LINEREFERENCE 40
#define L_DELIVERYADVICELINE_DAINVOICEDPRICE 11
#define N_DELIVERYADVICELINE_DAINVOICEDPRICE 4
#define L_DELIVERYADVICELINE_MINLOGISTICSERVICECOSTVALUE 11
#define N_DELIVERYADVICELINE_MINLOGISTICSERVICECOSTVALUE 4
#define L_DELIVERYADVICELINE_LINETYPE 6
#define L_DELIVERYADVICELINE_DAARTICLENAME 50
#define L_DELIVERYADVICELINE_ARTICLEUNIT 9
#define L_DELIVERYADVICELINE_PHARMACEUTICALFORM 3
#define L_DELIVERYADVICELINE_DABASEPRICE 11
#define N_DELIVERYADVICELINE_DABASEPRICE 4
#define L_DELIVERYADVICELINE_LOGISTICSERVICECOST 11
#define N_DELIVERYADVICELINE_LOGISTICSERVICECOST 4

/* Length/Count-Define of DELIVERYADVICELINE **********************************/

#define LS_DELIVERYADVICELINE_BRANCHNO 5 + 1
#define LS_DELIVERYADVICELINE_CUSTOMERNO 10 + 1
#define LS_DELIVERYADVICELINE_DELIVERYADVICEDATE 10 + 1
#define LS_DELIVERYADVICELINE_DELIVERYADVICENO 10 + 1
#define LS_DELIVERYADVICELINE_DAVAT 1 + 1
#define LS_DELIVERYADVICELINE_VATPERCENTAGE 5 + 2
#define LS_DELIVERYADVICELINE_DELIVERYADVICEPOSNO 10 + 1
#define LS_DELIVERYADVICELINE_PHARMOSORDERPOSNO 10 + 1
#define LS_DELIVERYADVICELINE_CSCORDERPOSNO 10 + 1
#define LS_DELIVERYADVICELINE_ARTICLENO 10 + 1
#define LS_DELIVERYADVICELINE_ARTICLE_CODE 25 + 1
#define LS_DELIVERYADVICELINE_QTY_ORDERED 10 + 1
#define LS_DELIVERYADVICELINE_QTY_CONFIRMED 10 + 1
#define LS_DELIVERYADVICELINE_QTY_REBATEINKIND 10 + 1
#define LS_DELIVERYADVICELINE_QTY_INVOICED 10 + 1
#define LS_DELIVERYADVICELINE_LINEREFERENCE 40 + 1
#define LS_DELIVERYADVICELINE_DAINVOICEDPRICE 11 + 2
#define LS_DELIVERYADVICELINE_MINLOGISTICSERVICECOSTVALUE 11 + 2
#define LS_DELIVERYADVICELINE_LINETYPE 5 + 1
#define LS_DELIVERYADVICELINE_DAARTICLENAME 50 + 1
#define LS_DELIVERYADVICELINE_ARTICLEUNIT 9 + 1
#define LS_DELIVERYADVICELINE_PHARMACEUTICALFORM 3 + 1
#define LS_DELIVERYADVICELINE_DABASEPRICE 11 + 2
#define LS_DELIVERYADVICELINE_LOGISTICSERVICECOST 11 + 2

#define DELIVERYADVICELINEBRANCHNO 0
#define DELIVERYADVICELINECUSTOMERNO 1
#define DELIVERYADVICELINEDELIVERYADVICEDATE 2
#define DELIVERYADVICELINEDELIVERYADVICENO 3
#define DELIVERYADVICELINEDAVAT 4
#define DELIVERYADVICELINEVATPERCENTAGE 5
#define DELIVERYADVICELINEDELIVERYADVICEPOSNO 6
#define DELIVERYADVICELINEPHARMOSORDERPOSNO 7
#define DELIVERYADVICELINECSCORDERPOSNO 8
#define DELIVERYADVICELINEARTICLENO 9
#define DELIVERYADVICELINEARTICLE_CODE 10
#define DELIVERYADVICELINEQTY_ORDERED 11
#define DELIVERYADVICELINEQTY_CONFIRMED 12
#define DELIVERYADVICELINEQTY_REBATEINKIND 13
#define DELIVERYADVICELINEQTY_INVOICED 14
#define DELIVERYADVICELINELINEREFERENCE 15
#define DELIVERYADVICELINEDAINVOICEDPRICE 16
#define DELIVERYADVICELINEMINLOGISTICSERVICECOSTVALUE 17
#define DELIVERYADVICELINELINETYPE 18
#define DELIVERYADVICELINEDAARTICLENAME 19
#define DELIVERYADVICELINEARTICLEUNIT 20
#define DELIVERYADVICELINEPHARMACEUTICALFORM 21
#define DELIVERYADVICELINEDABASEPRICE 22
#define DELIVERYADVICELINELOGISTICSERVICECOST 23

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define DELIVERYADVICELINE_H
#define DELIVERYADVICELINE_ANZ ( sizeof(DELIVERYADVICELINE_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of DELIVERYADVICELINE ********************************************/

#define DELIVERYADVICELINE_LISTE \
        DADUMMY.BRANCHNO,\
        DADUMMY.CUSTOMERNO,\
        DADUMMY.DELIVERYADVICEDATE,\
        DADUMMY.DELIVERYADVICENO,\
        DADUMMY.DAVAT,\
        DADUMMY.VATPERCENTAGE,\
        DADUMMY.DELIVERYADVICEPOSNO,\
        DADUMMY.PHARMOSORDERPOSNO,\
        DADUMMY.CSCORDERPOSNO,\
        DADUMMY.ARTICLENO,\
        DADUMMY.ARTICLE_CODE,\
        DADUMMY.QTY_ORDERED,\
        DADUMMY.QTY_CONFIRMED,\
        DADUMMY.QTY_REBATEINKIND,\
        DADUMMY.QTY_INVOICED,\
        DADUMMY.LINEREFERENCE,\
        DADUMMY.DAINVOICEDPRICE,\
        DADUMMY.MINLOGISTICSERVICECOSTVALUE,\
        DADUMMY.LINETYPE,\
        DADUMMY.DAARTICLENAME,\
        DADUMMY.ARTICLEUNIT,\
        DADUMMY.PHARMACEUTICALFORM,\
        DADUMMY.DABASEPRICE,\
        DADUMMY.LOGISTICSERVICECOST
#define DELIVERYADVICELINE_LISTE_390 \
        BRANCHNO,\
        CUSTOMERNO,\
        DELIVERYADVICEDATE,\
        DELIVERYADVICENO,\
        DAVAT,\
        VATPERCENTAGE,\
        DELIVERYADVICEPOSNO,\
        PHARMOSORDERPOSNO,\
        CSCORDERPOSNO,\
        ARTICLENO,\
        ARTICLE_CODE,\
        QTY_ORDERED,\
        QTY_CONFIRMED,\
        QTY_REBATEINKIND,\
        QTY_INVOICED,\
        LINEREFERENCE,\
        DAINVOICEDPRICE,\
        MINLOGISTICSERVICECOSTVALUE,\
        LINETYPE,\
        DAARTICLENAME,\
        ARTICLEUNIT,\
        PHARMACEUTICALFORM,\
        DABASEPRICE,\
        LOGISTICSERVICECOST
#define DELIVERYADVICELINE_PLISTE \
        "DADUMMY.BRANCHNO,"\
        "DADUMMY.CUSTOMERNO,"\
        "DADUMMY.DELIVERYADVICEDATE,"\
        "DADUMMY.DELIVERYADVICENO,"\
        "DADUMMY.DAVAT,"\
        "DADUMMY.VATPERCENTAGE,"\
        "DADUMMY.DELIVERYADVICEPOSNO,"\
        "DADUMMY.PHARMOSORDERPOSNO,"\
        "DADUMMY.CSCORDERPOSNO,"\
        "DADUMMY.ARTICLENO,"\
        "DADUMMY.ARTICLE_CODE,"\
        "DADUMMY.QTY_ORDERED,"\
        "DADUMMY.QTY_CONFIRMED,"\
        "DADUMMY.QTY_REBATEINKIND,"\
        "DADUMMY.QTY_INVOICED,"\
        "DADUMMY.LINEREFERENCE,"\
        "DADUMMY.DAINVOICEDPRICE,"\
        "DADUMMY.MINLOGISTICSERVICECOSTVALUE,"\
        "DADUMMY.LINETYPE,"\
        "DADUMMY.DAARTICLENAME,"\
        "DADUMMY.ARTICLEUNIT,"\
        "DADUMMY.PHARMACEUTICALFORM,"\
        "DADUMMY.DABASEPRICE,"\
        "DADUMMY.LOGISTICSERVICECOST"
#define DELIVERYADVICELINE_PELISTE \
        "BRANCHNO,"\
        "CUSTOMERNO,"\
        "DELIVERYADVICEDATE,"\
        "DELIVERYADVICENO,"\
        "DAVAT,"\
        "VATPERCENTAGE,"\
        "DELIVERYADVICEPOSNO,"\
        "PHARMOSORDERPOSNO,"\
        "CSCORDERPOSNO,"\
        "ARTICLENO,"\
        "ARTICLE_CODE,"\
        "QTY_ORDERED,"\
        "QTY_CONFIRMED,"\
        "QTY_REBATEINKIND,"\
        "QTY_INVOICED,"\
        "LINEREFERENCE,"\
        "DAINVOICEDPRICE,"\
        "MINLOGISTICSERVICECOSTVALUE,"\
        "LINETYPE,"\
        "DAARTICLENAME,"\
        "ARTICLEUNIT,"\
        "PHARMACEUTICALFORM,"\
        "DABASEPRICE,"\
        "LOGISTICSERVICECOST"
#define DELIVERYADVICELINE_UPDLISTE \
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "DELIVERYADVICEDATE=?,"\
        "DELIVERYADVICENO=?,"\
        "DAVAT=?,"\
        "VATPERCENTAGE=?,"\
        "DELIVERYADVICEPOSNO=?,"\
        "PHARMOSORDERPOSNO=?,"\
        "CSCORDERPOSNO=?,"\
        "ARTICLENO=?,"\
        "ARTICLE_CODE=?,"\
        "QTY_ORDERED=?,"\
        "QTY_CONFIRMED=?,"\
        "QTY_REBATEINKIND=?,"\
        "QTY_INVOICED=?,"\
        "LINEREFERENCE=?,"\
        "DAINVOICEDPRICE=?,"\
        "MINLOGISTICSERVICECOSTVALUE=?,"\
        "LINETYPE=?,"\
        "DAARTICLENAME=?,"\
        "ARTICLEUNIT=?,"\
        "PHARMACEUTICALFORM=?,"\
        "DABASEPRICE=?,"\
        "LOGISTICSERVICECOST=?"
/* SqlMacros-Define of DELIVERYADVICELINE *************************************/

#define DELIVERYADVICELINE_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->DELIVERYADVICEDATE,\
        :x->DELIVERYADVICENO,\
        :x->DAVAT,\
        :x->VATPERCENTAGE,\
        :x->DELIVERYADVICEPOSNO,\
        :x->PHARMOSORDERPOSNO,\
        :x->CSCORDERPOSNO,\
        :x->ARTICLENO,\
        :x->ARTICLE_CODE,\
        :x->QTY_ORDERED,\
        :x->QTY_CONFIRMED,\
        :x->QTY_REBATEINKIND,\
        :x->QTY_INVOICED,\
        :x->LINEREFERENCE,\
        :x->DAINVOICEDPRICE,\
        :x->MINLOGISTICSERVICECOSTVALUE,\
        :x->LINETYPE,\
        :x->DAARTICLENAME,\
        :x->ARTICLEUNIT,\
        :x->PHARMACEUTICALFORM,\
        :x->DABASEPRICE,\
        :x->LOGISTICSERVICECOST
#define DELIVERYADVICELINE_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->DELIVERYADVICEDATE,\
        :x->DELIVERYADVICENO,\
        :x->DAVAT,\
        :x->VATPERCENTAGE,\
        :x->DELIVERYADVICEPOSNO,\
        :x->PHARMOSORDERPOSNO,\
        :x->CSCORDERPOSNO,\
        :x->ARTICLENO,\
        :x->ARTICLE_CODE,\
        :x->QTY_ORDERED,\
        :x->QTY_CONFIRMED,\
        :x->QTY_REBATEINKIND,\
        :x->QTY_INVOICED,\
        :x->LINEREFERENCE,\
        :x->DAINVOICEDPRICE,\
        :x->MINLOGISTICSERVICECOSTVALUE,\
        :x->LINETYPE,\
        :x->DAARTICLENAME,\
        :x->ARTICLEUNIT,\
        :x->PHARMACEUTICALFORM,\
        :x->DABASEPRICE,\
        :x->LOGISTICSERVICECOST
#define DELIVERYADVICELINE_UPDATE(x) \
        DADUMMY.BRANCHNO=:x->BRANCHNO,\
        DADUMMY.CUSTOMERNO=:x->CUSTOMERNO,\
        DADUMMY.DELIVERYADVICEDATE=:x->DELIVERYADVICEDATE,\
        DADUMMY.DELIVERYADVICENO=:x->DELIVERYADVICENO,\
        DADUMMY.DAVAT=:x->DAVAT,\
        DADUMMY.VATPERCENTAGE=:x->VATPERCENTAGE,\
        DADUMMY.DELIVERYADVICEPOSNO=:x->DELIVERYADVICEPOSNO,\
        DADUMMY.PHARMOSORDERPOSNO=:x->PHARMOSORDERPOSNO,\
        DADUMMY.CSCORDERPOSNO=:x->CSCORDERPOSNO,\
        DADUMMY.ARTICLENO=:x->ARTICLENO,\
        DADUMMY.ARTICLE_CODE=:x->ARTICLE_CODE,\
        DADUMMY.QTY_ORDERED=:x->QTY_ORDERED,\
        DADUMMY.QTY_CONFIRMED=:x->QTY_CONFIRMED,\
        DADUMMY.QTY_REBATEINKIND=:x->QTY_REBATEINKIND,\
        DADUMMY.QTY_INVOICED=:x->QTY_INVOICED,\
        DADUMMY.LINEREFERENCE=:x->LINEREFERENCE,\
        DADUMMY.DAINVOICEDPRICE=:x->DAINVOICEDPRICE,\
        DADUMMY.MINLOGISTICSERVICECOSTVALUE=:x->MINLOGISTICSERVICECOSTVALUE,\
        DADUMMY.LINETYPE=:x->LINETYPE,\
        DADUMMY.DAARTICLENAME=:x->DAARTICLENAME,\
        DADUMMY.ARTICLEUNIT=:x->ARTICLEUNIT,\
        DADUMMY.PHARMACEUTICALFORM=:x->PHARMACEUTICALFORM,\
        DADUMMY.DABASEPRICE=:x->DABASEPRICE,\
        DADUMMY.LOGISTICSERVICECOST=:x->LOGISTICSERVICECOST
/* SqlMacros390-Define of DELIVERYADVICELINE **********************************/

#define DELIVERYADVICELINE_ZEIGER_390 \
        :BRANCHNO,\
        :CUSTOMERNO,\
        :DELIVERYADVICEDATE,\
        :DELIVERYADVICENO,\
        :DAVAT,\
        :VATPERCENTAGE,\
        :DELIVERYADVICEPOSNO,\
        :PHARMOSORDERPOSNO,\
        :CSCORDERPOSNO,\
        :ARTICLENO,\
        :ARTICLE_CODE,\
        :QTY_ORDERED,\
        :QTY_CONFIRMED,\
        :QTY_REBATEINKIND,\
        :QTY_INVOICED,\
        :LINEREFERENCE,\
        :DAINVOICEDPRICE,\
        :MINLOGISTICSERVICECOSTVALUE,\
        :LINETYPE,\
        :DAARTICLENAME,\
        :ARTICLEUNIT,\
        :PHARMACEUTICALFORM,\
        :DABASEPRICE,\
        :LOGISTICSERVICECOST
#define DELIVERYADVICELINE_UPDATE_390 \
        BRANCHNO=:BRANCHNO,\
        CUSTOMERNO=:CUSTOMERNO,\
        DELIVERYADVICEDATE=:DELIVERYADVICEDATE,\
        DELIVERYADVICENO=:DELIVERYADVICENO,\
        DAVAT=:DAVAT,\
        VATPERCENTAGE=:VATPERCENTAGE,\
        DELIVERYADVICEPOSNO=:DELIVERYADVICEPOSNO,\
        PHARMOSORDERPOSNO=:PHARMOSORDERPOSNO,\
        CSCORDERPOSNO=:CSCORDERPOSNO,\
        ARTICLENO=:ARTICLENO,\
        ARTICLE_CODE=:ARTICLE_CODE,\
        QTY_ORDERED=:QTY_ORDERED,\
        QTY_CONFIRMED=:QTY_CONFIRMED,\
        QTY_REBATEINKIND=:QTY_REBATEINKIND,\
        QTY_INVOICED=:QTY_INVOICED,\
        LINEREFERENCE=:LINEREFERENCE,\
        DAINVOICEDPRICE=:DAINVOICEDPRICE,\
        MINLOGISTICSERVICECOSTVALUE=:MINLOGISTICSERVICECOSTVALUE,\
        LINETYPE=:LINETYPE,\
        DAARTICLENAME=:DAARTICLENAME,\
        ARTICLEUNIT=:ARTICLEUNIT,\
        PHARMACEUTICALFORM=:PHARMACEUTICALFORM,\
        DABASEPRICE=:DABASEPRICE,\
        LOGISTICSERVICECOST=:LOGISTICSERVICECOST
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of DELIVERYADVICELINE **************************************/

#ifndef TRANSCLASS
typedef struct N_DELIVERYADVICELINE {
    short BRANCHNO;
    long CUSTOMERNO;
    long DELIVERYADVICEDATE;
    char DELIVERYADVICENO[11];
    char DAVAT[2];
    double VATPERCENTAGE;
    long DELIVERYADVICEPOSNO;
    long PHARMOSORDERPOSNO;
    long CSCORDERPOSNO;
    long ARTICLENO;
    char ARTICLE_CODE[26];
    long QTY_ORDERED;
    long QTY_CONFIRMED;
    long QTY_REBATEINKIND;
    long QTY_INVOICED;
    char LINEREFERENCE[41];
    double DAINVOICEDPRICE;
    double MINLOGISTICSERVICECOSTVALUE;
    short LINETYPE;
    char DAARTICLENAME[51];
    char ARTICLEUNIT[10];
    char PHARMACEUTICALFORM[4];
    double DABASEPRICE;
    double LOGISTICSERVICECOST;
} deliveryadvicelineS;
#else /* TRANSCLASS */
typedef struct N_DELIVERYADVICELINE {
    short BRANCHNO;
    long CUSTOMERNO;
    long DELIVERYADVICEDATE;
    char DELIVERYADVICENO[11];
    char DAVAT[2];
    double VATPERCENTAGE;
    long DELIVERYADVICEPOSNO;
    long PHARMOSORDERPOSNO;
    long CSCORDERPOSNO;
    long ARTICLENO;
    char ARTICLE_CODE[26];
    long QTY_ORDERED;
    long QTY_CONFIRMED;
    long QTY_REBATEINKIND;
    long QTY_INVOICED;
    char LINEREFERENCE[41];
    double DAINVOICEDPRICE;
    double MINLOGISTICSERVICECOSTVALUE;
    short LINETYPE;
    char DAARTICLENAME[51];
    char ARTICLEUNIT[10];
    char PHARMACEUTICALFORM[4];
    double DABASEPRICE;
    double LOGISTICSERVICECOST;

    bool operator == (const N_DELIVERYADVICELINE& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            CUSTOMERNO == right.CUSTOMERNO &&
            DELIVERYADVICEDATE == right.DELIVERYADVICEDATE &&
            !strcmp(DELIVERYADVICENO, right.DELIVERYADVICENO) &&
            !strcmp(DAVAT, right.DAVAT) &&
            VATPERCENTAGE == right.VATPERCENTAGE &&
            DELIVERYADVICEPOSNO == right.DELIVERYADVICEPOSNO &&
            PHARMOSORDERPOSNO == right.PHARMOSORDERPOSNO &&
            CSCORDERPOSNO == right.CSCORDERPOSNO &&
            ARTICLENO == right.ARTICLENO &&
            !strcmp(ARTICLE_CODE, right.ARTICLE_CODE) &&
            QTY_ORDERED == right.QTY_ORDERED &&
            QTY_CONFIRMED == right.QTY_CONFIRMED &&
            QTY_REBATEINKIND == right.QTY_REBATEINKIND &&
            QTY_INVOICED == right.QTY_INVOICED &&
            !strcmp(LINEREFERENCE, right.LINEREFERENCE) &&
            DAINVOICEDPRICE == right.DAINVOICEDPRICE &&
            MINLOGISTICSERVICECOSTVALUE == right.MINLOGISTICSERVICECOSTVALUE &&
            LINETYPE == right.LINETYPE &&
            !strcmp(DAARTICLENAME, right.DAARTICLENAME) &&
            !strcmp(ARTICLEUNIT, right.ARTICLEUNIT) &&
            !strcmp(PHARMACEUTICALFORM, right.PHARMACEUTICALFORM) &&
            DABASEPRICE == right.DABASEPRICE &&
            LOGISTICSERVICECOST == right.LOGISTICSERVICECOST
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        CUSTOMERNO = 0;
        DELIVERYADVICEDATE = 0;
        strcpy(DELIVERYADVICENO, " " );
        strcpy(DAVAT, " " );
        VATPERCENTAGE = 0;
        DELIVERYADVICEPOSNO = 0;
        PHARMOSORDERPOSNO = 0;
        CSCORDERPOSNO = 0;
        ARTICLENO = 0;
        strcpy(ARTICLE_CODE, " " );
        QTY_ORDERED = 0;
        QTY_CONFIRMED = 0;
        QTY_REBATEINKIND = 0;
        QTY_INVOICED = 0;
        strcpy(LINEREFERENCE, " " );
        DAINVOICEDPRICE = 0;
        MINLOGISTICSERVICECOSTVALUE = 0;
        LINETYPE = 0;
        strcpy(DAARTICLENAME, " " );
        strcpy(ARTICLEUNIT, " " );
        strcpy(PHARMACEUTICALFORM, " " );
        DABASEPRICE = 0;
        LOGISTICSERVICECOST = 0;
#endif
    }
} deliveryadvicelineS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of DELIVERYADVICELINE ********************************/

struct S_DELIVERYADVICELINE {
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char DELIVERYADVICEDATE[11];
    char DELIVERYADVICENO[10 + 1];
    char DAVAT[1 + 1];
    char VATPERCENTAGE[5 + 2];
    char DELIVERYADVICEPOSNO[11];
    char PHARMOSORDERPOSNO[11];
    char CSCORDERPOSNO[11];
    char ARTICLENO[11];
    char ARTICLE_CODE[25 + 1];
    char QTY_ORDERED[11];
    char QTY_CONFIRMED[11];
    char QTY_REBATEINKIND[11];
    char QTY_INVOICED[11];
    char LINEREFERENCE[40 + 1];
    char DAINVOICEDPRICE[11 + 2];
    char MINLOGISTICSERVICECOSTVALUE[11 + 2];
    char LINETYPE[7];
    char DAARTICLENAME[50 + 1];
    char ARTICLEUNIT[9 + 1];
    char PHARMACEUTICALFORM[3 + 1];
    char DABASEPRICE[11 + 2];
    char LOGISTICSERVICECOST[11 + 2];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of DELIVERYADVICELINE ***************/

struct O_DELIVERYADVICELINE {
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char DELIVERYADVICEDATE[11];
    char DELIVERYADVICENO[10];
    char DAVAT[1];
    char VATPERCENTAGE[5];
    char DELIVERYADVICEPOSNO[11];
    char PHARMOSORDERPOSNO[11];
    char CSCORDERPOSNO[11];
    char ARTICLENO[11];
    char ARTICLE_CODE[25];
    char QTY_ORDERED[11];
    char QTY_CONFIRMED[11];
    char QTY_REBATEINKIND[11];
    char QTY_INVOICED[11];
    char LINEREFERENCE[40];
    char DAINVOICEDPRICE[11];
    char MINLOGISTICSERVICECOSTVALUE[11];
    char LINETYPE[7];
    char DAARTICLENAME[50];
    char ARTICLEUNIT[9];
    char PHARMACEUTICALFORM[3];
    char DABASEPRICE[11];
    char LOGISTICSERVICECOST[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of DELIVERYADVICELINE **************************/

struct C_DELIVERYADVICELINE {
    short BRANCHNO;
    long CUSTOMERNO;
    long DELIVERYADVICEDATE;
    char DELIVERYADVICENO[11];
    char DAVAT;
    double VATPERCENTAGE;
    long DELIVERYADVICEPOSNO;
    long PHARMOSORDERPOSNO;
    long CSCORDERPOSNO;
    long ARTICLENO;
    char ARTICLE_CODE[26];
    long QTY_ORDERED;
    long QTY_CONFIRMED;
    long QTY_REBATEINKIND;
    long QTY_INVOICED;
    char LINEREFERENCE[41];
    double DAINVOICEDPRICE;
    double MINLOGISTICSERVICECOSTVALUE;
    short LINETYPE;
    char DAARTICLENAME[51];
    char ARTICLEUNIT[10];
    char PHARMACEUTICALFORM[4];
    double DABASEPRICE;
    double LOGISTICSERVICECOST;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of DELIVERYADVICELINE ************************/

struct I_DELIVERYADVICELINE {
    short BRANCHNO;
    short CUSTOMERNO;
    short DELIVERYADVICEDATE;
    short DELIVERYADVICENO;
    short DAVAT;
    short VATPERCENTAGE;
    short DELIVERYADVICEPOSNO;
    short PHARMOSORDERPOSNO;
    short CSCORDERPOSNO;
    short ARTICLENO;
    short ARTICLE_CODE;
    short QTY_ORDERED;
    short QTY_CONFIRMED;
    short QTY_REBATEINKIND;
    short QTY_INVOICED;
    short LINEREFERENCE;
    short DAINVOICEDPRICE;
    short MINLOGISTICSERVICECOSTVALUE;
    short LINETYPE;
    short DAARTICLENAME;
    short ARTICLEUNIT;
    short PHARMACEUTICALFORM;
    short DABASEPRICE;
    short LOGISTICSERVICECOST;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of DELIVERYADVICELINE **********************************/

#if defined (BUF_DESC)
static struct buf_desc DELIVERYADVICELINE_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 10, 0 },
   { TYP_C, 1, 0 },
   { TYP_D, 5, 2 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 25, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 40, 0 },
   { TYP_D, 11, 4 },
   { TYP_D, 11, 4 },
   { TYP_S ,  6, 0 },
   { TYP_C, 50, 0 },
   { TYP_C, 9, 0 },
   { TYP_C, 3, 0 },
   { TYP_D, 11, 4 },
   { TYP_D, 11, 4 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc DELIVERYADVICELINE_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 10, 0 },
   { TYP_C, 1, 0 },
   { TYP_D, 5, 2 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 25, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 40, 0 },
   { TYP_D, 11, 4 },
   { TYP_D, 11, 4 },
   { TYP_S ,  6, 0 },
   { TYP_C, 50, 0 },
   { TYP_C, 9, 0 },
   { TYP_C, 3, 0 },
   { TYP_D, 11, 4 },
   { TYP_D, 11, 4 },
};
#endif

/* description for datatypes of DELIVERYADVICELINE ****************************/

 #define DELIVERYADVICELINE_S390 \
         short BRANCHNO; \
         long CUSTOMERNO; \
         long DELIVERYADVICEDATE; \
         char DELIVERYADVICENO[11]; \
         char DAVAT; \
         double VATPERCENTAGE; \
         long DELIVERYADVICEPOSNO; \
         long PHARMOSORDERPOSNO; \
         long CSCORDERPOSNO; \
         long ARTICLENO; \
         char ARTICLE_CODE[26]; \
         long QTY_ORDERED; \
         long QTY_CONFIRMED; \
         long QTY_REBATEINKIND; \
         long QTY_INVOICED; \
         char LINEREFERENCE[41]; \
         double DAINVOICEDPRICE; \
         double MINLOGISTICSERVICECOSTVALUE; \
         short LINETYPE; \
         char DAARTICLENAME[51]; \
         char ARTICLEUNIT[10]; \
         char PHARMACEUTICALFORM[4]; \
         double DABASEPRICE; \
         double LOGISTICSERVICECOST; \



/* Copy-Function Struct to single Data DELIVERYADVICELINE *********************/

 #define DELIVERYADVICELINE_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
         DELIVERYADVICEDATE=_x_->DELIVERYADVICEDATE;\
          strcpy(DELIVERYADVICENO,_x_->DELIVERYADVICENO);\
         DAVAT=_x_->DAVAT;\
         VATPERCENTAGE=_x_->VATPERCENTAGE;\
         DELIVERYADVICEPOSNO=_x_->DELIVERYADVICEPOSNO;\
         PHARMOSORDERPOSNO=_x_->PHARMOSORDERPOSNO;\
         CSCORDERPOSNO=_x_->CSCORDERPOSNO;\
         ARTICLENO=_x_->ARTICLENO;\
          strcpy(ARTICLE_CODE,_x_->ARTICLE_CODE);\
         QTY_ORDERED=_x_->QTY_ORDERED;\
         QTY_CONFIRMED=_x_->QTY_CONFIRMED;\
         QTY_REBATEINKIND=_x_->QTY_REBATEINKIND;\
         QTY_INVOICED=_x_->QTY_INVOICED;\
          strcpy(LINEREFERENCE,_x_->LINEREFERENCE);\
         DAINVOICEDPRICE=_x_->DAINVOICEDPRICE;\
         MINLOGISTICSERVICECOSTVALUE=_x_->MINLOGISTICSERVICECOSTVALUE;\
         LINETYPE=_x_->LINETYPE;\
          strcpy(DAARTICLENAME,_x_->DAARTICLENAME);\
          strcpy(ARTICLEUNIT,_x_->ARTICLEUNIT);\
          strcpy(PHARMACEUTICALFORM,_x_->PHARMACEUTICALFORM);\
         DABASEPRICE=_x_->DABASEPRICE;\
         LOGISTICSERVICECOST=_x_->LOGISTICSERVICECOST;\

 #define DELIVERYADVICELINE_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->DELIVERYADVICEDATE=DELIVERYADVICEDATE;\
          strcpy(_x_->DELIVERYADVICENO,DELIVERYADVICENO);\
          _x_->DAVAT=DAVAT;\
          _x_->VATPERCENTAGE=VATPERCENTAGE;\
          _x_->DELIVERYADVICEPOSNO=DELIVERYADVICEPOSNO;\
          _x_->PHARMOSORDERPOSNO=PHARMOSORDERPOSNO;\
          _x_->CSCORDERPOSNO=CSCORDERPOSNO;\
          _x_->ARTICLENO=ARTICLENO;\
          strcpy(_x_->ARTICLE_CODE,ARTICLE_CODE);\
          _x_->QTY_ORDERED=QTY_ORDERED;\
          _x_->QTY_CONFIRMED=QTY_CONFIRMED;\
          _x_->QTY_REBATEINKIND=QTY_REBATEINKIND;\
          _x_->QTY_INVOICED=QTY_INVOICED;\
          strcpy(_x_->LINEREFERENCE,LINEREFERENCE);\
          _x_->DAINVOICEDPRICE=DAINVOICEDPRICE;\
          _x_->MINLOGISTICSERVICECOSTVALUE=MINLOGISTICSERVICECOSTVALUE;\
          _x_->LINETYPE=LINETYPE;\
          strcpy(_x_->DAARTICLENAME,DAARTICLENAME);\
          strcpy(_x_->ARTICLEUNIT,ARTICLEUNIT);\
          strcpy(_x_->PHARMACEUTICALFORM,PHARMACEUTICALFORM);\
          _x_->DABASEPRICE=DABASEPRICE;\
          _x_->LOGISTICSERVICECOST=LOGISTICSERVICECOST;\



/* FunctionNumber-Define of Deliveryadviceline ********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of Deliveryadviceline ****************************/


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

class CDELIVERYADVICELINE : public ppDadeVirtual {
public:
    deliveryadvicelineS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<deliveryadvicelineS> lst; // class list

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
                     vector< deliveryadvicelineS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     deliveryadvicelineS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< deliveryadvicelineS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<deliveryadvicelineS>::iterator
                 beginList() { return lst.begin(); }
    vector<deliveryadvicelineS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    long         GetDeliveryadvicedate() const { return s.DELIVERYADVICEDATE; }
    const char*  GetDeliveryadviceno(ppString & t) const { t = s.DELIVERYADVICENO; t.erasespace(ppString::END); return t.c_str(); }
    char         GetDavat() const { return s.DAVAT[0]; }
    double       GetVatpercentage() const { return s.VATPERCENTAGE; }
    long         GetDeliveryadviceposno() const { return s.DELIVERYADVICEPOSNO; }
    long         GetPharmosorderposno() const { return s.PHARMOSORDERPOSNO; }
    long         GetCscorderposno() const { return s.CSCORDERPOSNO; }
    long         GetArticleno() const { return s.ARTICLENO; }
    const char*  GetArticle_code(ppString & t) const { t = s.ARTICLE_CODE; t.erasespace(ppString::END); return t.c_str(); }
    long         GetQty_ordered() const { return s.QTY_ORDERED; }
    long         GetQty_confirmed() const { return s.QTY_CONFIRMED; }
    long         GetQty_rebateinkind() const { return s.QTY_REBATEINKIND; }
    long         GetQty_invoiced() const { return s.QTY_INVOICED; }
    const char*  GetLinereference(ppString & t) const { t = s.LINEREFERENCE; t.erasespace(ppString::END); return t.c_str(); }
    double       GetDainvoicedprice() const { return s.DAINVOICEDPRICE; }
    double       GetMinlogisticservicecostvalue() const { return s.MINLOGISTICSERVICECOSTVALUE; }
    short        GetLinetype() const { return s.LINETYPE; }
    const char*  GetDaarticlename(ppString & t) const { t = s.DAARTICLENAME; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetArticleunit(ppString & t) const { t = s.ARTICLEUNIT; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetPharmaceuticalform(ppString & t) const { t = s.PHARMACEUTICALFORM; t.erasespace(ppString::END); return t.c_str(); }
    double       GetDabaseprice() const { return s.DABASEPRICE; }
    double       GetLogisticservicecost() const { return s.LOGISTICSERVICECOST; }

    const deliveryadvicelineS &
                 GetStruct() const { return s; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetDeliveryadvicedate(long t) { s.DELIVERYADVICEDATE = t; }
    void         SetDeliveryadviceno(const ppString & t) { ppGStrCopy(s.DELIVERYADVICENO, t.c_str(), L_DELIVERYADVICELINE_DELIVERYADVICENO); }
    void         SetDavat(char t) { s.DAVAT[0] = t; s.DAVAT[1] = '\0';}
    void         SetVatpercentage(double t) { s.VATPERCENTAGE = t; }
    void         SetDeliveryadviceposno(long t) { s.DELIVERYADVICEPOSNO = t; }
    void         SetPharmosorderposno(long t) { s.PHARMOSORDERPOSNO = t; }
    void         SetCscorderposno(long t) { s.CSCORDERPOSNO = t; }
    void         SetArticleno(long t) { s.ARTICLENO = t; }
    void         SetArticle_code(const ppString & t) { ppGStrCopy(s.ARTICLE_CODE, t.c_str(), L_DELIVERYADVICELINE_ARTICLE_CODE); }
    void         SetQty_ordered(long t) { s.QTY_ORDERED = t; }
    void         SetQty_confirmed(long t) { s.QTY_CONFIRMED = t; }
    void         SetQty_rebateinkind(long t) { s.QTY_REBATEINKIND = t; }
    void         SetQty_invoiced(long t) { s.QTY_INVOICED = t; }
    void         SetLinereference(const ppString & t) { ppGStrCopy(s.LINEREFERENCE, t.c_str(), L_DELIVERYADVICELINE_LINEREFERENCE); }
    void         SetDainvoicedprice(double t) { s.DAINVOICEDPRICE = t; }
    void         SetMinlogisticservicecostvalue(double t) { s.MINLOGISTICSERVICECOSTVALUE = t; }
    void         SetLinetype(short t) { s.LINETYPE = t; }
    void         SetDaarticlename(const ppString & t) { ppGStrCopy(s.DAARTICLENAME, t.c_str(), L_DELIVERYADVICELINE_DAARTICLENAME); }
    void         SetArticleunit(const ppString & t) { ppGStrCopy(s.ARTICLEUNIT, t.c_str(), L_DELIVERYADVICELINE_ARTICLEUNIT); }
    void         SetPharmaceuticalform(const ppString & t) { ppGStrCopy(s.PHARMACEUTICALFORM, t.c_str(), L_DELIVERYADVICELINE_PHARMACEUTICALFORM); }
    void         SetDabaseprice(double t) { s.DABASEPRICE = t; }
    void         SetLogisticservicecost(double t) { s.LOGISTICSERVICECOST = t; }

    void         SetStruct(const deliveryadvicelineS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CDELIVERYADVICELINE() {
        ::buf_default((void *)&s, DELIVERYADVICELINE_BES, DELIVERYADVICELINE_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CDELIVERYADVICELINE() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, DELIVERYADVICELINE_BES, DELIVERYADVICELINE_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, DELIVERYADVICELINE_BES, (int)DELIVERYADVICELINE_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, DELIVERYADVICELINE_BES, (int)DELIVERYADVICELINE_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_DELIVERYADVICELINE & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.DELIVERYADVICENO);
        ppGStripLast(d.ARTICLE_CODE);
        ppGStripLast(d.LINEREFERENCE);
        ppGStripLast(d.DAARTICLENAME);
        ppGStripLast(d.ARTICLEUNIT);
        ppGStripLast(d.PHARMACEUTICALFORM);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, DELIVERYADVICELINE_BES, (int)DELIVERYADVICELINE_ANZ, error_msg);
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
/* CreateSqlStatement of DELIVERYADVICELINE ***********************************/

 #define DELIVERYADVICELINE_CREATE(x) EXEC SQL create table x (\
         BRANCHNO smallint default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         DELIVERYADVICEDATE integer default 0 not null,\
         DELIVERYADVICENO varchar(10,0) default " " not null,\
         DAVAT char(1) default " " not null,\
         VATPERCENTAGE decimal(5,2) default 0 not null,\
         DELIVERYADVICEPOSNO integer default 0 not null,\
         PHARMOSORDERPOSNO integer default 0 not null,\
         CSCORDERPOSNO integer default 0 not null,\
         ARTICLENO integer default 0 not null,\
         ARTICLE_CODE char(25) default " " not null,\
         QTY_ORDERED integer default 0 not null,\
         QTY_CONFIRMED integer default 0 not null,\
         QTY_REBATEINKIND integer default 0 not null,\
         QTY_INVOICED integer default 0 not null,\
         LINEREFERENCE varchar(40,0) default " " not null,\
         DAINVOICEDPRICE decimal(11,4) default 0 not null,\
         MINLOGISTICSERVICECOSTVALUE decimal(11,4) default 0 not null,\
         LINETYPE smallint default 0 not null,\
         DAARTICLENAME varchar(50,0) default " " not null,\
         ARTICLEUNIT char(9) default " " not null,\
         PHARMACEUTICALFORM varchar(3,0) default " " not null,\
         DABASEPRICE decimal(11,4) default 0 not null,\
         LOGISTICSERVICECOST decimal(11,4) default 0 not null) extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of DELIVERYADVICELINE *********************************/

 #define DELIVERYADVICELINE_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
/* DeleteIndexStatement of DELIVERYADVICELINE *********************************/

 #define DELIVERYADVICELINE_DELETE_INDEX(_X_)\
              _X_ = 0;\


#endif   // GUARD
