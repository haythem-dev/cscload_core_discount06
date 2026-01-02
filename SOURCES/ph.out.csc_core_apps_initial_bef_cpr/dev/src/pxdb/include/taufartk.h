#ifndef __PP_AUFTRAGARTKD_H_
#define __PP_AUFTRAGARTKD_H_

/******************************************************************************/
/* u:\auftragartkd ************************************************************/
/* produced by DADE 6.21.4 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of AUFTRAGARTKD **********************************************/

#define L_AUFTRAGARTKD_IDFNR 11
#define L_AUFTRAGARTKD_KDAUFTRAGART 2
#define L_AUFTRAGARTKD_VALUTAMONATE 11
#define L_AUFTRAGARTKD_SKDAUFTRAGARTNATRA 1
#define L_AUFTRAGARTKD_SKDAUFTRAGARTNETTO 1
#define L_AUFTRAGARTKD_SKDAUFTRAGARTBANR 1
#define L_AUFTRAGARTKD_SKDAUFTRAGARTMONAT 1
#define L_AUFTRAGARTKD_SKDAUFTRAGVERBUND 1
#define L_AUFTRAGARTKD_SKDAUFTRAGARTVALS 1
#define L_AUFTRAGARTKD_VALUTAMONAUTO 6
#define L_AUFTRAGARTKD_VERTRIEBSZENTRUMNR 6
#define L_AUFTRAGARTKD_KUNDENNR 11
#define L_AUFTRAGARTKD_SKDAUFTRAGARTDD 1
#define L_AUFTRAGARTKD_ORDERLABELCOUNT 6
#define L_AUFTRAGARTKD_SWMSV3 6
#define L_AUFTRAGARTKD_SWPARTDEL 6
#define L_AUFTRAGARTKD_ORDERIDENTIFICATIO 10

/* Length/Count-Define of AUFTRAGARTKD ****************************************/

#define LS_AUFTRAGARTKD_IDFNR 10 + 1
#define LS_AUFTRAGARTKD_KDAUFTRAGART 2 + 1
#define LS_AUFTRAGARTKD_VALUTAMONATE 10 + 1
#define LS_AUFTRAGARTKD_SKDAUFTRAGARTNATRA 1 + 1
#define LS_AUFTRAGARTKD_SKDAUFTRAGARTNETTO 1 + 1
#define LS_AUFTRAGARTKD_SKDAUFTRAGARTBANR 1 + 1
#define LS_AUFTRAGARTKD_SKDAUFTRAGARTMONAT 1 + 1
#define LS_AUFTRAGARTKD_SKDAUFTRAGVERBUND 1 + 1
#define LS_AUFTRAGARTKD_SKDAUFTRAGARTVALS 1 + 1
#define LS_AUFTRAGARTKD_VALUTAMONAUTO 5 + 1
#define LS_AUFTRAGARTKD_VERTRIEBSZENTRUMNR 5 + 1
#define LS_AUFTRAGARTKD_KUNDENNR 10 + 1
#define LS_AUFTRAGARTKD_SKDAUFTRAGARTDD 1 + 1
#define LS_AUFTRAGARTKD_ORDERLABELCOUNT 5 + 1
#define LS_AUFTRAGARTKD_SWMSV3 5 + 1
#define LS_AUFTRAGARTKD_SWPARTDEL 5 + 1
#define LS_AUFTRAGARTKD_ORDERIDENTIFICATIO 10 + 1

#define AUFTRAGARTKDIDFNR 0
#define AUFTRAGARTKDKDAUFTRAGART 1
#define AUFTRAGARTKDVALUTAMONATE 2
#define AUFTRAGARTKDSKDAUFTRAGARTNATRA 3
#define AUFTRAGARTKDSKDAUFTRAGARTNETTO 4
#define AUFTRAGARTKDSKDAUFTRAGARTBANR 5
#define AUFTRAGARTKDSKDAUFTRAGARTMONAT 6
#define AUFTRAGARTKDSKDAUFTRAGVERBUND 7
#define AUFTRAGARTKDSKDAUFTRAGARTVALS 8
#define AUFTRAGARTKDVALUTAMONAUTO 9
#define AUFTRAGARTKDVERTRIEBSZENTRUMNR 10
#define AUFTRAGARTKDKUNDENNR 11
#define AUFTRAGARTKDSKDAUFTRAGARTDD 12
#define AUFTRAGARTKDORDERLABELCOUNT 13
#define AUFTRAGARTKDSWMSV3 14
#define AUFTRAGARTKDSWPARTDEL 15
#define AUFTRAGARTKDORDERIDENTIFICATIO 16

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define AUFTRAGARTKD_H
#define AUFTRAGARTKD_ANZ ( sizeof(AUFTRAGARTKD_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of AUFTRAGARTKD **************************************************/

#define AUFTRAGARTKD_LISTE \
        AUFTRAGARTKD.IDFNR,\
        AUFTRAGARTKD.KDAUFTRAGART,\
        AUFTRAGARTKD.VALUTAMONATE,\
        AUFTRAGARTKD.SKDAUFTRAGARTNATRA,\
        AUFTRAGARTKD.SKDAUFTRAGARTNETTO,\
        AUFTRAGARTKD.SKDAUFTRAGARTBANR,\
        AUFTRAGARTKD.SKDAUFTRAGARTMONAT,\
        AUFTRAGARTKD.SKDAUFTRAGVERBUND,\
        AUFTRAGARTKD.SKDAUFTRAGARTVALS,\
        AUFTRAGARTKD.VALUTAMONAUTO,\
        AUFTRAGARTKD.VERTRIEBSZENTRUMNR,\
        AUFTRAGARTKD.KUNDENNR,\
        AUFTRAGARTKD.SKDAUFTRAGARTDD,\
        AUFTRAGARTKD.ORDERLABELCOUNT,\
        AUFTRAGARTKD.SWMSV3,\
        AUFTRAGARTKD.SWPARTDEL,\
        AUFTRAGARTKD.ORDERIDENTIFICATIO
#define AUFTRAGARTKD_LISTE_390 \
        IDFNR,\
        KDAUFTRAGART,\
        VALUTAMONATE,\
        SKDAUFTRAGARTNATRA,\
        SKDAUFTRAGARTNETTO,\
        SKDAUFTRAGARTBANR,\
        SKDAUFTRAGARTMONAT,\
        SKDAUFTRAGVERBUND,\
        SKDAUFTRAGARTVALS,\
        VALUTAMONAUTO,\
        VERTRIEBSZENTRUMNR,\
        KUNDENNR,\
        SKDAUFTRAGARTDD,\
        ORDERLABELCOUNT,\
        SWMSV3,\
        SWPARTDEL,\
        ORDERIDENTIFICATIO
#define AUFTRAGARTKD_PLISTE \
        "AUFTRAGARTKD.IDFNR,"\
        "AUFTRAGARTKD.KDAUFTRAGART,"\
        "AUFTRAGARTKD.VALUTAMONATE,"\
        "AUFTRAGARTKD.SKDAUFTRAGARTNATRA,"\
        "AUFTRAGARTKD.SKDAUFTRAGARTNETTO,"\
        "AUFTRAGARTKD.SKDAUFTRAGARTBANR,"\
        "AUFTRAGARTKD.SKDAUFTRAGARTMONAT,"\
        "AUFTRAGARTKD.SKDAUFTRAGVERBUND,"\
        "AUFTRAGARTKD.SKDAUFTRAGARTVALS,"\
        "AUFTRAGARTKD.VALUTAMONAUTO,"\
        "AUFTRAGARTKD.VERTRIEBSZENTRUMNR,"\
        "AUFTRAGARTKD.KUNDENNR,"\
        "AUFTRAGARTKD.SKDAUFTRAGARTDD,"\
        "AUFTRAGARTKD.ORDERLABELCOUNT,"\
        "AUFTRAGARTKD.SWMSV3,"\
        "AUFTRAGARTKD.SWPARTDEL,"\
        "AUFTRAGARTKD.ORDERIDENTIFICATIO"
#define AUFTRAGARTKD_PELISTE \
        "IDFNR,"\
        "KDAUFTRAGART,"\
        "VALUTAMONATE,"\
        "SKDAUFTRAGARTNATRA,"\
        "SKDAUFTRAGARTNETTO,"\
        "SKDAUFTRAGARTBANR,"\
        "SKDAUFTRAGARTMONAT,"\
        "SKDAUFTRAGVERBUND,"\
        "SKDAUFTRAGARTVALS,"\
        "VALUTAMONAUTO,"\
        "VERTRIEBSZENTRUMNR,"\
        "KUNDENNR,"\
        "SKDAUFTRAGARTDD,"\
        "ORDERLABELCOUNT,"\
        "SWMSV3,"\
        "SWPARTDEL,"\
        "ORDERIDENTIFICATIO"
#define AUFTRAGARTKD_UPDLISTE \
        "IDFNR=?,"\
        "KDAUFTRAGART=?,"\
        "VALUTAMONATE=?,"\
        "SKDAUFTRAGARTNATRA=?,"\
        "SKDAUFTRAGARTNETTO=?,"\
        "SKDAUFTRAGARTBANR=?,"\
        "SKDAUFTRAGARTMONAT=?,"\
        "SKDAUFTRAGVERBUND=?,"\
        "SKDAUFTRAGARTVALS=?,"\
        "VALUTAMONAUTO=?,"\
        "VERTRIEBSZENTRUMNR=?,"\
        "KUNDENNR=?,"\
        "SKDAUFTRAGARTDD=?,"\
        "ORDERLABELCOUNT=?,"\
        "SWMSV3=?,"\
        "SWPARTDEL=?,"\
        "ORDERIDENTIFICATIO=?"
/* SqlMacros-Define of AUFTRAGARTKD *******************************************/

#define AUFTRAGARTKD_ZEIGER(x) \
        :x->IDFNR,\
        :x->KDAUFTRAGART,\
        :x->VALUTAMONATE,\
        :x->SKDAUFTRAGARTNATRA,\
        :x->SKDAUFTRAGARTNETTO,\
        :x->SKDAUFTRAGARTBANR,\
        :x->SKDAUFTRAGARTMONAT,\
        :x->SKDAUFTRAGVERBUND,\
        :x->SKDAUFTRAGARTVALS,\
        :x->VALUTAMONAUTO,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->SKDAUFTRAGARTDD,\
        :x->ORDERLABELCOUNT,\
        :x->SWMSV3,\
        :x->SWPARTDEL,\
        :x->ORDERIDENTIFICATIO
#define AUFTRAGARTKD_ZEIGERSEL(x) \
        :x->IDFNR,\
        :x->KDAUFTRAGART,\
        :x->VALUTAMONATE,\
        :x->SKDAUFTRAGARTNATRA,\
        :x->SKDAUFTRAGARTNETTO,\
        :x->SKDAUFTRAGARTBANR,\
        :x->SKDAUFTRAGARTMONAT,\
        :x->SKDAUFTRAGVERBUND,\
        :x->SKDAUFTRAGARTVALS,\
        :x->VALUTAMONAUTO,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->SKDAUFTRAGARTDD,\
        :x->ORDERLABELCOUNT,\
        :x->SWMSV3,\
        :x->SWPARTDEL,\
        :x->ORDERIDENTIFICATIO
#define AUFTRAGARTKD_UPDATE(x) \
        AUFTRAGARTKD.IDFNR=:x->IDFNR,\
        AUFTRAGARTKD.KDAUFTRAGART=:x->KDAUFTRAGART,\
        AUFTRAGARTKD.VALUTAMONATE=:x->VALUTAMONATE,\
        AUFTRAGARTKD.SKDAUFTRAGARTNATRA=:x->SKDAUFTRAGARTNATRA,\
        AUFTRAGARTKD.SKDAUFTRAGARTNETTO=:x->SKDAUFTRAGARTNETTO,\
        AUFTRAGARTKD.SKDAUFTRAGARTBANR=:x->SKDAUFTRAGARTBANR,\
        AUFTRAGARTKD.SKDAUFTRAGARTMONAT=:x->SKDAUFTRAGARTMONAT,\
        AUFTRAGARTKD.SKDAUFTRAGVERBUND=:x->SKDAUFTRAGVERBUND,\
        AUFTRAGARTKD.SKDAUFTRAGARTVALS=:x->SKDAUFTRAGARTVALS,\
        AUFTRAGARTKD.VALUTAMONAUTO=:x->VALUTAMONAUTO,\
        AUFTRAGARTKD.VERTRIEBSZENTRUMNR=:x->VERTRIEBSZENTRUMNR,\
        AUFTRAGARTKD.KUNDENNR=:x->KUNDENNR,\
        AUFTRAGARTKD.SKDAUFTRAGARTDD=:x->SKDAUFTRAGARTDD,\
        AUFTRAGARTKD.ORDERLABELCOUNT=:x->ORDERLABELCOUNT,\
        AUFTRAGARTKD.SWMSV3=:x->SWMSV3,\
        AUFTRAGARTKD.SWPARTDEL=:x->SWPARTDEL,\
        AUFTRAGARTKD.ORDERIDENTIFICATIO=:x->ORDERIDENTIFICATIO
/* SqlMacros390-Define of AUFTRAGARTKD ****************************************/

#define AUFTRAGARTKD_ZEIGER_390 \
        :IDFNR,\
        :KDAUFTRAGART,\
        :VALUTAMONATE,\
        :SKDAUFTRAGARTNATRA,\
        :SKDAUFTRAGARTNETTO,\
        :SKDAUFTRAGARTBANR,\
        :SKDAUFTRAGARTMONAT,\
        :SKDAUFTRAGVERBUND,\
        :SKDAUFTRAGARTVALS,\
        :VALUTAMONAUTO,\
        :VERTRIEBSZENTRUMNR,\
        :KUNDENNR,\
        :SKDAUFTRAGARTDD,\
        :ORDERLABELCOUNT,\
        :SWMSV3,\
        :SWPARTDEL,\
        :ORDERIDENTIFICATIO
#define AUFTRAGARTKD_UPDATE_390 \
        IDFNR=:IDFNR,\
        KDAUFTRAGART=:KDAUFTRAGART,\
        VALUTAMONATE=:VALUTAMONATE,\
        SKDAUFTRAGARTNATRA=:SKDAUFTRAGARTNATRA,\
        SKDAUFTRAGARTNETTO=:SKDAUFTRAGARTNETTO,\
        SKDAUFTRAGARTBANR=:SKDAUFTRAGARTBANR,\
        SKDAUFTRAGARTMONAT=:SKDAUFTRAGARTMONAT,\
        SKDAUFTRAGVERBUND=:SKDAUFTRAGVERBUND,\
        SKDAUFTRAGARTVALS=:SKDAUFTRAGARTVALS,\
        VALUTAMONAUTO=:VALUTAMONAUTO,\
        VERTRIEBSZENTRUMNR=:VERTRIEBSZENTRUMNR,\
        KUNDENNR=:KUNDENNR,\
        SKDAUFTRAGARTDD=:SKDAUFTRAGARTDD,\
        ORDERLABELCOUNT=:ORDERLABELCOUNT,\
        SWMSV3=:SWMSV3,\
        SWPARTDEL=:SWPARTDEL,\
        ORDERIDENTIFICATIO=:ORDERIDENTIFICATIO
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of AUFTRAGARTKD ********************************************/

#ifndef TRANSCLASS
typedef struct N_AUFTRAGARTKD {
    long IDFNR;
    char KDAUFTRAGART[3];
    long VALUTAMONATE;
    char SKDAUFTRAGARTNATRA[2];
    char SKDAUFTRAGARTNETTO[2];
    char SKDAUFTRAGARTBANR[2];
    char SKDAUFTRAGARTMONAT[2];
    char SKDAUFTRAGVERBUND[2];
    char SKDAUFTRAGARTVALS[2];
    short VALUTAMONAUTO;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char SKDAUFTRAGARTDD[2];
    short ORDERLABELCOUNT;
    short SWMSV3;
    short SWPARTDEL;
    char ORDERIDENTIFICATIO[11];
} auftragartkdS;
#else /* TRANSCLASS */
typedef struct N_AUFTRAGARTKD {
    long IDFNR;
    char KDAUFTRAGART[3];
    long VALUTAMONATE;
    char SKDAUFTRAGARTNATRA[2];
    char SKDAUFTRAGARTNETTO[2];
    char SKDAUFTRAGARTBANR[2];
    char SKDAUFTRAGARTMONAT[2];
    char SKDAUFTRAGVERBUND[2];
    char SKDAUFTRAGARTVALS[2];
    short VALUTAMONAUTO;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char SKDAUFTRAGARTDD[2];
    short ORDERLABELCOUNT;
    short SWMSV3;
    short SWPARTDEL;
    char ORDERIDENTIFICATIO[11];

    bool operator == (const N_AUFTRAGARTKD& right) const {
        return (
            IDFNR == right.IDFNR &&
            !strcmp(KDAUFTRAGART, right.KDAUFTRAGART) &&
            VALUTAMONATE == right.VALUTAMONATE &&
            !strcmp(SKDAUFTRAGARTNATRA, right.SKDAUFTRAGARTNATRA) &&
            !strcmp(SKDAUFTRAGARTNETTO, right.SKDAUFTRAGARTNETTO) &&
            !strcmp(SKDAUFTRAGARTBANR, right.SKDAUFTRAGARTBANR) &&
            !strcmp(SKDAUFTRAGARTMONAT, right.SKDAUFTRAGARTMONAT) &&
            !strcmp(SKDAUFTRAGVERBUND, right.SKDAUFTRAGVERBUND) &&
            !strcmp(SKDAUFTRAGARTVALS, right.SKDAUFTRAGARTVALS) &&
            VALUTAMONAUTO == right.VALUTAMONAUTO &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            !strcmp(SKDAUFTRAGARTDD, right.SKDAUFTRAGARTDD) &&
            ORDERLABELCOUNT == right.ORDERLABELCOUNT &&
            SWMSV3 == right.SWMSV3 &&
            SWPARTDEL == right.SWPARTDEL &&
            !strcmp(ORDERIDENTIFICATIO, right.ORDERIDENTIFICATIO)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        IDFNR = 0;
        strcpy(KDAUFTRAGART, " " );
        VALUTAMONATE = 0;
        strcpy(SKDAUFTRAGARTNATRA, " " );
        strcpy(SKDAUFTRAGARTNETTO, " " );
        strcpy(SKDAUFTRAGARTBANR, " " );
        strcpy(SKDAUFTRAGARTMONAT, " " );
        strcpy(SKDAUFTRAGVERBUND, " " );
        strcpy(SKDAUFTRAGARTVALS, " " );
        VALUTAMONAUTO = 0;
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        strcpy(SKDAUFTRAGARTDD, " " );
        ORDERLABELCOUNT = 0;
        SWMSV3 = 0;
        SWPARTDEL = 0;
        strcpy(ORDERIDENTIFICATIO, " " );
#endif
    }
} auftragartkdS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of AUFTRAGARTKD **************************************/

struct S_AUFTRAGARTKD {
    char IDFNR[11];
    char KDAUFTRAGART[2 + 1];
    char VALUTAMONATE[11];
    char SKDAUFTRAGARTNATRA[1 + 1];
    char SKDAUFTRAGARTNETTO[1 + 1];
    char SKDAUFTRAGARTBANR[1 + 1];
    char SKDAUFTRAGARTMONAT[1 + 1];
    char SKDAUFTRAGVERBUND[1 + 1];
    char SKDAUFTRAGARTVALS[1 + 1];
    char VALUTAMONAUTO[7];
    char VERTRIEBSZENTRUMNR[7];
    char KUNDENNR[11];
    char SKDAUFTRAGARTDD[1 + 1];
    char ORDERLABELCOUNT[7];
    char SWMSV3[7];
    char SWPARTDEL[7];
    char ORDERIDENTIFICATIO[10 + 1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of AUFTRAGARTKD *********************/

struct O_AUFTRAGARTKD {
    char IDFNR[11];
    char KDAUFTRAGART[2];
    char VALUTAMONATE[11];
    char SKDAUFTRAGARTNATRA[1];
    char SKDAUFTRAGARTNETTO[1];
    char SKDAUFTRAGARTBANR[1];
    char SKDAUFTRAGARTMONAT[1];
    char SKDAUFTRAGVERBUND[1];
    char SKDAUFTRAGARTVALS[1];
    char VALUTAMONAUTO[7];
    char VERTRIEBSZENTRUMNR[7];
    char KUNDENNR[11];
    char SKDAUFTRAGARTDD[1];
    char ORDERLABELCOUNT[7];
    char SWMSV3[7];
    char SWPARTDEL[7];
    char ORDERIDENTIFICATIO[10];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of AUFTRAGARTKD ********************************/

struct C_AUFTRAGARTKD {
    long IDFNR;
    char KDAUFTRAGART[3];
    long VALUTAMONATE;
    char SKDAUFTRAGARTNATRA;
    char SKDAUFTRAGARTNETTO;
    char SKDAUFTRAGARTBANR;
    char SKDAUFTRAGARTMONAT;
    char SKDAUFTRAGVERBUND;
    char SKDAUFTRAGARTVALS;
    short VALUTAMONAUTO;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char SKDAUFTRAGARTDD;
    short ORDERLABELCOUNT;
    short SWMSV3;
    short SWPARTDEL;
    char ORDERIDENTIFICATIO[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of AUFTRAGARTKD ******************************/

struct I_AUFTRAGARTKD {
    short IDFNR;
    short KDAUFTRAGART;
    short VALUTAMONATE;
    short SKDAUFTRAGARTNATRA;
    short SKDAUFTRAGARTNETTO;
    short SKDAUFTRAGARTBANR;
    short SKDAUFTRAGARTMONAT;
    short SKDAUFTRAGVERBUND;
    short SKDAUFTRAGARTVALS;
    short VALUTAMONAUTO;
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short SKDAUFTRAGARTDD;
    short ORDERLABELCOUNT;
    short SWMSV3;
    short SWPARTDEL;
    short ORDERIDENTIFICATIO;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of AUFTRAGARTKD ****************************************/

#if defined (BUF_DESC)
static struct buf_desc AUFTRAGARTKD_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 2, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 10, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc AUFTRAGARTKD_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 2, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 10, 0 },
};
#endif

/* description for datatypes of AUFTRAGARTKD **********************************/

 #define AUFTRAGARTKD_S390 \
         long IDFNR; \
         char KDAUFTRAGART[3]; \
         long VALUTAMONATE; \
         char SKDAUFTRAGARTNATRA; \
         char SKDAUFTRAGARTNETTO; \
         char SKDAUFTRAGARTBANR; \
         char SKDAUFTRAGARTMONAT; \
         char SKDAUFTRAGVERBUND; \
         char SKDAUFTRAGARTVALS; \
         short VALUTAMONAUTO; \
         short VERTRIEBSZENTRUMNR; \
         long KUNDENNR; \
         char SKDAUFTRAGARTDD; \
         short ORDERLABELCOUNT; \
         short SWMSV3; \
         short SWPARTDEL; \
         char ORDERIDENTIFICATIO[11]; \



/* Copy-Function Struct to single Data AUFTRAGARTKD ***************************/

 #define AUFTRAGARTKD_S390_COPY_TO_SINGLE(_x_) \
         IDFNR=_x_->IDFNR;\
          strcpy(KDAUFTRAGART,_x_->KDAUFTRAGART);\
         VALUTAMONATE=_x_->VALUTAMONATE;\
         SKDAUFTRAGARTNATRA=_x_->SKDAUFTRAGARTNATRA;\
         SKDAUFTRAGARTNETTO=_x_->SKDAUFTRAGARTNETTO;\
         SKDAUFTRAGARTBANR=_x_->SKDAUFTRAGARTBANR;\
         SKDAUFTRAGARTMONAT=_x_->SKDAUFTRAGARTMONAT;\
         SKDAUFTRAGVERBUND=_x_->SKDAUFTRAGVERBUND;\
         SKDAUFTRAGARTVALS=_x_->SKDAUFTRAGARTVALS;\
         VALUTAMONAUTO=_x_->VALUTAMONAUTO;\
         VERTRIEBSZENTRUMNR=_x_->VERTRIEBSZENTRUMNR;\
         KUNDENNR=_x_->KUNDENNR;\
         SKDAUFTRAGARTDD=_x_->SKDAUFTRAGARTDD;\
         ORDERLABELCOUNT=_x_->ORDERLABELCOUNT;\
         SWMSV3=_x_->SWMSV3;\
         SWPARTDEL=_x_->SWPARTDEL;\
          strcpy(ORDERIDENTIFICATIO,_x_->ORDERIDENTIFICATIO);\

 #define AUFTRAGARTKD_S390_COPY_TO_STRUCT(_x_) \
          _x_->IDFNR=IDFNR;\
          strcpy(_x_->KDAUFTRAGART,KDAUFTRAGART);\
          _x_->VALUTAMONATE=VALUTAMONATE;\
          _x_->SKDAUFTRAGARTNATRA=SKDAUFTRAGARTNATRA;\
          _x_->SKDAUFTRAGARTNETTO=SKDAUFTRAGARTNETTO;\
          _x_->SKDAUFTRAGARTBANR=SKDAUFTRAGARTBANR;\
          _x_->SKDAUFTRAGARTMONAT=SKDAUFTRAGARTMONAT;\
          _x_->SKDAUFTRAGVERBUND=SKDAUFTRAGVERBUND;\
          _x_->SKDAUFTRAGARTVALS=SKDAUFTRAGARTVALS;\
          _x_->VALUTAMONAUTO=VALUTAMONAUTO;\
          _x_->VERTRIEBSZENTRUMNR=VERTRIEBSZENTRUMNR;\
          _x_->KUNDENNR=KUNDENNR;\
          _x_->SKDAUFTRAGARTDD=SKDAUFTRAGARTDD;\
          _x_->ORDERLABELCOUNT=ORDERLABELCOUNT;\
          _x_->SWMSV3=SWMSV3;\
          _x_->SWPARTDEL=SWPARTDEL;\
          strcpy(_x_->ORDERIDENTIFICATIO,ORDERIDENTIFICATIO);\



/* FunctionNumber-Define of auftragartkd **************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of auftragartkd **********************************/


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

class CAUFTRAGARTKD : public ppDadeVirtual {
public:
    auftragartkdS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<auftragartkdS> lst; // class list

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
                     vector< auftragartkdS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     auftragartkdS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< auftragartkdS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<auftragartkdS>::iterator
                 beginList() { return lst.begin(); }
    vector<auftragartkdS>::iterator
                 endList  () { return lst.end  (); }

    long         GetIdfnr() const { return s.IDFNR; }
    const char*  GetKdauftragart(ppString & t) const { t = s.KDAUFTRAGART; t.erasespace(ppString::END); return t.c_str(); }
    long         GetValutamonate() const { return s.VALUTAMONATE; }
    char         GetSkdauftragartnatra() const { return s.SKDAUFTRAGARTNATRA[0]; }
    char         GetSkdauftragartnetto() const { return s.SKDAUFTRAGARTNETTO[0]; }
    char         GetSkdauftragartbanr() const { return s.SKDAUFTRAGARTBANR[0]; }
    char         GetSkdauftragartmonat() const { return s.SKDAUFTRAGARTMONAT[0]; }
    char         GetSkdauftragverbund() const { return s.SKDAUFTRAGVERBUND[0]; }
    char         GetSkdauftragartvals() const { return s.SKDAUFTRAGARTVALS[0]; }
    short        GetValutamonauto() const { return s.VALUTAMONAUTO; }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    char         GetSkdauftragartdd() const { return s.SKDAUFTRAGARTDD[0]; }
    short        GetOrderlabelcount() const { return s.ORDERLABELCOUNT; }
    short        GetSwmsv3() const { return s.SWMSV3; }
    short        GetSwpartdel() const { return s.SWPARTDEL; }
    const char*  GetOrderidentificatio(ppString & t) const { t = s.ORDERIDENTIFICATIO; t.erasespace(ppString::END); return t.c_str(); }

    const auftragartkdS &
                 GetStruct() const { return s; }
    void         SetIdfnr(long t) { s.IDFNR = t; }
    void         SetKdauftragart(const ppString & t) { ppGStrCopy(s.KDAUFTRAGART, t.c_str(), L_AUFTRAGARTKD_KDAUFTRAGART); }
    void         SetValutamonate(long t) { s.VALUTAMONATE = t; }
    void         SetSkdauftragartnatra(char t) { s.SKDAUFTRAGARTNATRA[0] = t; s.SKDAUFTRAGARTNATRA[1] = '\0';}
    void         SetSkdauftragartnetto(char t) { s.SKDAUFTRAGARTNETTO[0] = t; s.SKDAUFTRAGARTNETTO[1] = '\0';}
    void         SetSkdauftragartbanr(char t) { s.SKDAUFTRAGARTBANR[0] = t; s.SKDAUFTRAGARTBANR[1] = '\0';}
    void         SetSkdauftragartmonat(char t) { s.SKDAUFTRAGARTMONAT[0] = t; s.SKDAUFTRAGARTMONAT[1] = '\0';}
    void         SetSkdauftragverbund(char t) { s.SKDAUFTRAGVERBUND[0] = t; s.SKDAUFTRAGVERBUND[1] = '\0';}
    void         SetSkdauftragartvals(char t) { s.SKDAUFTRAGARTVALS[0] = t; s.SKDAUFTRAGARTVALS[1] = '\0';}
    void         SetValutamonauto(short t) { s.VALUTAMONAUTO = t; }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetSkdauftragartdd(char t) { s.SKDAUFTRAGARTDD[0] = t; s.SKDAUFTRAGARTDD[1] = '\0';}
    void         SetOrderlabelcount(short t) { s.ORDERLABELCOUNT = t; }
    void         SetSwmsv3(short t) { s.SWMSV3 = t; }
    void         SetSwpartdel(short t) { s.SWPARTDEL = t; }
    void         SetOrderidentificatio(const ppString & t) { ppGStrCopy(s.ORDERIDENTIFICATIO, t.c_str(), L_AUFTRAGARTKD_ORDERIDENTIFICATIO); }

    void         SetStruct(const auftragartkdS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CAUFTRAGARTKD() {
        ::buf_default((void *)&s, AUFTRAGARTKD_BES, AUFTRAGARTKD_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CAUFTRAGARTKD() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, AUFTRAGARTKD_BES, AUFTRAGARTKD_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, AUFTRAGARTKD_BES, (int)AUFTRAGARTKD_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, AUFTRAGARTKD_BES, (int)AUFTRAGARTKD_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_AUFTRAGARTKD & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.KDAUFTRAGART);
        ppGStripLast(d.ORDERIDENTIFICATIO);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, AUFTRAGARTKD_BES, (int)AUFTRAGARTKD_ANZ, error_msg);
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
/* CreateSqlStatement of AUFTRAGARTKD *****************************************/

 #define AUFTRAGARTKD_CREATE(x) EXEC SQL create table x (\
         IDFNR integer default 0 not null,\
         KDAUFTRAGART char(2) default " " not null,\
         VALUTAMONATE integer default 0 not null,\
         SKDAUFTRAGARTNATRA char(1) default " " not null,\
         SKDAUFTRAGARTNETTO char(1) default " " not null,\
         SKDAUFTRAGARTBANR char(1) default " " not null,\
         SKDAUFTRAGARTMONAT char(1) default " " not null,\
         SKDAUFTRAGVERBUND char(1) default " " not null,\
         SKDAUFTRAGARTVALS char(1) default " " not null,\
         VALUTAMONAUTO smallint default 0 not null,\
         VERTRIEBSZENTRUMNR smallint default 0 not null,\
         KUNDENNR integer default 0 not null,\
         SKDAUFTRAGARTDD char(1) default " " not null,\
         ORDERLABELCOUNT smallint default 0 not null,\
         SWMSV3 smallint default 0 not null,\
         SWPARTDEL smallint default 0 not null,\
         ORDERIDENTIFICATIO char(10) default " " not null) in KscCustomer extent size 2116 next size 212 lock mode row;



/* CreateIndexStatement of AUFTRAGARTKD ***************************************/

 #define AUFTRAGARTKD_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create   index auftragartkdx on _X_(\
              idfnr,\
              kdauftragart ) in KscCustomerIdx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create unique index i_auftragartkd_1 on _X_(\
              VertriebszentrumNr,\
              KundenNr,\
              kdauftragart ) in KscCustomerIdx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of AUFTRAGARTKD ***************************************/

 #define AUFTRAGARTKD_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index auftragartkdx;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_auftragartkd_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
