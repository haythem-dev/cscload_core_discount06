#ifndef __PP_LDAUFTRAGARTKD_H_
#define __PP_LDAUFTRAGARTKD_H_

/******************************************************************************/
/* d:\prj\DF\UNIX\loaddkkaa\ldauftragartkd ************************************/
/* produced by DADE 6.21.4 ****************************************************/
/******************************************************************************/

/* ppunixc */

/* Length-Define of LDAUFTRAGARTKD ********************************************/

#define L_LDAUFTRAGARTKD_IDFNR 11
#define L_LDAUFTRAGARTKD_KDAUFTRAGART 2
#define L_LDAUFTRAGARTKD_VALUTAMONATE 11
#define L_LDAUFTRAGARTKD_SKDAUFTRAGARTNATRA 1
#define L_LDAUFTRAGARTKD_SKDAUFTRAGARTNETTO 1
#define L_LDAUFTRAGARTKD_SKDAUFTRAGARTBANR 1
#define L_LDAUFTRAGARTKD_SKDAUFTRAGARTMONAT 1
#define L_LDAUFTRAGARTKD_SKDAUFTRAGVERBUND 1
#define L_LDAUFTRAGARTKD_SKDAUFTRAGARTVALS 1
#define L_LDAUFTRAGARTKD_VALUTAMONAUTO 6
#define L_LDAUFTRAGARTKD_KZUPD 1
#define L_LDAUFTRAGARTKD_RABATTART 6
#define L_LDAUFTRAGARTKD_KUNDESTAFFELNR 11
#define L_LDAUFTRAGARTKD_VERTRIEBSZENTRUMNR 6
#define L_LDAUFTRAGARTKD_KUNDENNR 11
#define L_LDAUFTRAGARTKD_TM_DATE 11
#define L_LDAUFTRAGARTKD_TM_TIME 11
#define L_LDAUFTRAGARTKD_LOGINID 11
#define L_LDAUFTRAGARTKD_CHANGEID 1
#define L_LDAUFTRAGARTKD_SKDAUFTRAGARTDD 1
#define L_LDAUFTRAGARTKD_ORDERLABELCOUNT 6
#define L_LDAUFTRAGARTKD_SWMSV3 6
#define L_LDAUFTRAGARTKD_SWPARTDEL 6
#define L_LDAUFTRAGARTKD_ORDERIDENTIFICATIO 10

/* Length/Count-Define of LDAUFTRAGARTKD **************************************/

#define LS_LDAUFTRAGARTKD_IDFNR 10 + 1
#define LS_LDAUFTRAGARTKD_KDAUFTRAGART 2 + 1
#define LS_LDAUFTRAGARTKD_VALUTAMONATE 10 + 1
#define LS_LDAUFTRAGARTKD_SKDAUFTRAGARTNATRA 1 + 1
#define LS_LDAUFTRAGARTKD_SKDAUFTRAGARTNETTO 1 + 1
#define LS_LDAUFTRAGARTKD_SKDAUFTRAGARTBANR 1 + 1
#define LS_LDAUFTRAGARTKD_SKDAUFTRAGARTMONAT 1 + 1
#define LS_LDAUFTRAGARTKD_SKDAUFTRAGVERBUND 1 + 1
#define LS_LDAUFTRAGARTKD_SKDAUFTRAGARTVALS 1 + 1
#define LS_LDAUFTRAGARTKD_VALUTAMONAUTO 5 + 1
#define LS_LDAUFTRAGARTKD_KZUPD 1 + 1
#define LS_LDAUFTRAGARTKD_RABATTART 5 + 1
#define LS_LDAUFTRAGARTKD_KUNDESTAFFELNR 10 + 1
#define LS_LDAUFTRAGARTKD_VERTRIEBSZENTRUMNR 5 + 1
#define LS_LDAUFTRAGARTKD_KUNDENNR 10 + 1
#define LS_LDAUFTRAGARTKD_TM_DATE 10 + 1
#define LS_LDAUFTRAGARTKD_TM_TIME 10 + 1
#define LS_LDAUFTRAGARTKD_LOGINID 10 + 1
#define LS_LDAUFTRAGARTKD_CHANGEID 1 + 1
#define LS_LDAUFTRAGARTKD_SKDAUFTRAGARTDD 1 + 1
#define LS_LDAUFTRAGARTKD_ORDERLABELCOUNT 5 + 1
#define LS_LDAUFTRAGARTKD_SWMSV3 5 + 1
#define LS_LDAUFTRAGARTKD_SWPARTDEL 5 + 1
#define LS_LDAUFTRAGARTKD_ORDERIDENTIFICATIO 10 + 1

#define LDAUFTRAGARTKDIDFNR 0
#define LDAUFTRAGARTKDKDAUFTRAGART 1
#define LDAUFTRAGARTKDVALUTAMONATE 2
#define LDAUFTRAGARTKDSKDAUFTRAGARTNATRA 3
#define LDAUFTRAGARTKDSKDAUFTRAGARTNETTO 4
#define LDAUFTRAGARTKDSKDAUFTRAGARTBANR 5
#define LDAUFTRAGARTKDSKDAUFTRAGARTMONAT 6
#define LDAUFTRAGARTKDSKDAUFTRAGVERBUND 7
#define LDAUFTRAGARTKDSKDAUFTRAGARTVALS 8
#define LDAUFTRAGARTKDVALUTAMONAUTO 9
#define LDAUFTRAGARTKDKZUPD 10
#define LDAUFTRAGARTKDRABATTART 11
#define LDAUFTRAGARTKDKUNDESTAFFELNR 12
#define LDAUFTRAGARTKDVERTRIEBSZENTRUMNR 13
#define LDAUFTRAGARTKDKUNDENNR 14
#define LDAUFTRAGARTKDTM_DATE 15
#define LDAUFTRAGARTKDTM_TIME 16
#define LDAUFTRAGARTKDLOGINID 17
#define LDAUFTRAGARTKDCHANGEID 18
#define LDAUFTRAGARTKDSKDAUFTRAGARTDD 19
#define LDAUFTRAGARTKDORDERLABELCOUNT 20
#define LDAUFTRAGARTKDSWMSV3 21
#define LDAUFTRAGARTKDSWPARTDEL 22
#define LDAUFTRAGARTKDORDERIDENTIFICATIO 23

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define LDAUFTRAGARTKD_H
#define LDAUFTRAGARTKD_ANZ ( sizeof(LDAUFTRAGARTKD_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of LDAUFTRAGARTKD ************************************************/

#define LDAUFTRAGARTKD_LISTE \
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
        AUFTRAGARTKD.KZUPD,\
        AUFTRAGARTKD.RABATTART,\
        AUFTRAGARTKD.KUNDESTAFFELNR,\
        AUFTRAGARTKD.VERTRIEBSZENTRUMNR,\
        AUFTRAGARTKD.KUNDENNR,\
        AUFTRAGARTKD.TM_DATE,\
        AUFTRAGARTKD.TM_TIME,\
        AUFTRAGARTKD.LOGINID,\
        AUFTRAGARTKD.CHANGEID,\
        AUFTRAGARTKD.SKDAUFTRAGARTDD,\
        AUFTRAGARTKD.ORDERLABELCOUNT,\
        AUFTRAGARTKD.SWMSV3,\
        AUFTRAGARTKD.SWPARTDEL,\
        AUFTRAGARTKD.ORDERIDENTIFICATIO
#define LDAUFTRAGARTKD_LISTE_390 \
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
        KZUPD,\
        RABATTART,\
        KUNDESTAFFELNR,\
        VERTRIEBSZENTRUMNR,\
        KUNDENNR,\
        TM_DATE,\
        TM_TIME,\
        LOGINID,\
        CHANGEID,\
        SKDAUFTRAGARTDD,\
        ORDERLABELCOUNT,\
        SWMSV3,\
        SWPARTDEL,\
        ORDERIDENTIFICATIO
#define LDAUFTRAGARTKD_PLISTE \
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
        "AUFTRAGARTKD.KZUPD,"\
        "AUFTRAGARTKD.RABATTART,"\
        "AUFTRAGARTKD.KUNDESTAFFELNR,"\
        "AUFTRAGARTKD.VERTRIEBSZENTRUMNR,"\
        "AUFTRAGARTKD.KUNDENNR,"\
        "AUFTRAGARTKD.TM_DATE,"\
        "AUFTRAGARTKD.TM_TIME,"\
        "AUFTRAGARTKD.LOGINID,"\
        "AUFTRAGARTKD.CHANGEID,"\
        "AUFTRAGARTKD.SKDAUFTRAGARTDD,"\
        "AUFTRAGARTKD.ORDERLABELCOUNT,"\
        "AUFTRAGARTKD.SWMSV3,"\
        "AUFTRAGARTKD.SWPARTDEL,"\
        "AUFTRAGARTKD.ORDERIDENTIFICATIO"
#define LDAUFTRAGARTKD_PELISTE \
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
        "KZUPD,"\
        "RABATTART,"\
        "KUNDESTAFFELNR,"\
        "VERTRIEBSZENTRUMNR,"\
        "KUNDENNR,"\
        "TM_DATE,"\
        "TM_TIME,"\
        "LOGINID,"\
        "CHANGEID,"\
        "SKDAUFTRAGARTDD,"\
        "ORDERLABELCOUNT,"\
        "SWMSV3,"\
        "SWPARTDEL,"\
        "ORDERIDENTIFICATIO"
#define LDAUFTRAGARTKD_UPDLISTE \
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
        "KZUPD=?,"\
        "RABATTART=?,"\
        "KUNDESTAFFELNR=?,"\
        "VERTRIEBSZENTRUMNR=?,"\
        "KUNDENNR=?,"\
        "TM_DATE=?,"\
        "TM_TIME=?,"\
        "LOGINID=?,"\
        "CHANGEID=?,"\
        "SKDAUFTRAGARTDD=?,"\
        "ORDERLABELCOUNT=?,"\
        "SWMSV3=?,"\
        "SWPARTDEL=?,"\
        "ORDERIDENTIFICATIO=?"
/* SqlMacros-Define of LDAUFTRAGARTKD *****************************************/

#define LDAUFTRAGARTKD_ZEIGER(x) \
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
        :x->KZUPD,\
        :x->RABATTART,\
        :x->KUNDESTAFFELNR,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->TM_DATE,\
        :x->TM_TIME,\
        :x->LOGINID,\
        :x->CHANGEID,\
        :x->SKDAUFTRAGARTDD,\
        :x->ORDERLABELCOUNT,\
        :x->SWMSV3,\
        :x->SWPARTDEL,\
        :x->ORDERIDENTIFICATIO
#define LDAUFTRAGARTKD_ZEIGERSEL(x) \
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
        :x->KZUPD,\
        :x->RABATTART,\
        :x->KUNDESTAFFELNR,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->TM_DATE,\
        :x->TM_TIME,\
        :x->LOGINID,\
        :x->CHANGEID,\
        :x->SKDAUFTRAGARTDD,\
        :x->ORDERLABELCOUNT,\
        :x->SWMSV3,\
        :x->SWPARTDEL,\
        :x->ORDERIDENTIFICATIO
#define LDAUFTRAGARTKD_UPDATE(x) \
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
        AUFTRAGARTKD.KZUPD=:x->KZUPD,\
        AUFTRAGARTKD.RABATTART=:x->RABATTART,\
        AUFTRAGARTKD.KUNDESTAFFELNR=:x->KUNDESTAFFELNR,\
        AUFTRAGARTKD.VERTRIEBSZENTRUMNR=:x->VERTRIEBSZENTRUMNR,\
        AUFTRAGARTKD.KUNDENNR=:x->KUNDENNR,\
        AUFTRAGARTKD.TM_DATE=:x->TM_DATE,\
        AUFTRAGARTKD.TM_TIME=:x->TM_TIME,\
        AUFTRAGARTKD.LOGINID=:x->LOGINID,\
        AUFTRAGARTKD.CHANGEID=:x->CHANGEID,\
        AUFTRAGARTKD.SKDAUFTRAGARTDD=:x->SKDAUFTRAGARTDD,\
        AUFTRAGARTKD.ORDERLABELCOUNT=:x->ORDERLABELCOUNT,\
        AUFTRAGARTKD.SWMSV3=:x->SWMSV3,\
        AUFTRAGARTKD.SWPARTDEL=:x->SWPARTDEL,\
        AUFTRAGARTKD.ORDERIDENTIFICATIO=:x->ORDERIDENTIFICATIO
/* SqlMacros390-Define of LDAUFTRAGARTKD **************************************/

#define LDAUFTRAGARTKD_ZEIGER_390 \
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
        :KZUPD,\
        :RABATTART,\
        :KUNDESTAFFELNR,\
        :VERTRIEBSZENTRUMNR,\
        :KUNDENNR,\
        :TM_DATE,\
        :TM_TIME,\
        :LOGINID,\
        :CHANGEID,\
        :SKDAUFTRAGARTDD,\
        :ORDERLABELCOUNT,\
        :SWMSV3,\
        :SWPARTDEL,\
        :ORDERIDENTIFICATIO
#define LDAUFTRAGARTKD_UPDATE_390 \
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
        KZUPD=:KZUPD,\
        RABATTART=:RABATTART,\
        KUNDESTAFFELNR=:KUNDESTAFFELNR,\
        VERTRIEBSZENTRUMNR=:VERTRIEBSZENTRUMNR,\
        KUNDENNR=:KUNDENNR,\
        TM_DATE=:TM_DATE,\
        TM_TIME=:TM_TIME,\
        LOGINID=:LOGINID,\
        CHANGEID=:CHANGEID,\
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

/* original struct of LDAUFTRAGARTKD ******************************************/

#ifndef TRANSCLASS
typedef struct N_LDAUFTRAGARTKD {
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
    char KZUPD[2];
    short RABATTART;
    long KUNDESTAFFELNR;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long TM_DATE;
    long TM_TIME;
    long LOGINID;
    char CHANGEID[2];
    char SKDAUFTRAGARTDD[2];
    short ORDERLABELCOUNT;
    short SWMSV3;
    short SWPARTDEL;
    char ORDERIDENTIFICATIO[11];
} ldauftragartkdS;
#else /* TRANSCLASS */
typedef struct N_LDAUFTRAGARTKD {
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
    char KZUPD[2];
    short RABATTART;
    long KUNDESTAFFELNR;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long TM_DATE;
    long TM_TIME;
    long LOGINID;
    char CHANGEID[2];
    char SKDAUFTRAGARTDD[2];
    short ORDERLABELCOUNT;
    short SWMSV3;
    short SWPARTDEL;
    char ORDERIDENTIFICATIO[11];

    bool operator == (const N_LDAUFTRAGARTKD& right) const {
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
            !strcmp(KZUPD, right.KZUPD) &&
            RABATTART == right.RABATTART &&
            KUNDESTAFFELNR == right.KUNDESTAFFELNR &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            TM_DATE == right.TM_DATE &&
            TM_TIME == right.TM_TIME &&
            LOGINID == right.LOGINID &&
            !strcmp(CHANGEID, right.CHANGEID) &&
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
        strcpy(KZUPD, " " );
        RABATTART = 0;
        KUNDESTAFFELNR = 0;
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        TM_DATE = 0;
        TM_TIME = 0;
        LOGINID = 0;
        strcpy(CHANGEID, " " );
        strcpy(SKDAUFTRAGARTDD, " " );
        ORDERLABELCOUNT = 0;
        SWMSV3 = 0;
        SWPARTDEL = 0;
        strcpy(ORDERIDENTIFICATIO, " " );
#endif
    }
} ldauftragartkdS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of LDAUFTRAGARTKD ************************************/

struct S_LDAUFTRAGARTKD {
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
    char KZUPD[1 + 1];
    char RABATTART[7];
    char KUNDESTAFFELNR[11];
    char VERTRIEBSZENTRUMNR[7];
    char KUNDENNR[11];
    char TM_DATE[11];
    char TM_TIME[11];
    char LOGINID[11];
    char CHANGEID[1 + 1];
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

/* Stringbuffer (without strend) Structur of LDAUFTRAGARTKD *******************/

struct O_LDAUFTRAGARTKD {
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
    char KZUPD[1];
    char RABATTART[7];
    char KUNDESTAFFELNR[11];
    char VERTRIEBSZENTRUMNR[7];
    char KUNDENNR[11];
    char TM_DATE[11];
    char TM_TIME[11];
    char LOGINID[11];
    char CHANGEID[1];
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

/* Structur with real chartype of LDAUFTRAGARTKD ******************************/

struct C_LDAUFTRAGARTKD {
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
    char KZUPD;
    short RABATTART;
    long KUNDESTAFFELNR;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long TM_DATE;
    long TM_TIME;
    long LOGINID;
    char CHANGEID;
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

/* Sizetype  Structur (buf_desc) of LDAUFTRAGARTKD ****************************/

struct I_LDAUFTRAGARTKD {
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
    short KZUPD;
    short RABATTART;
    short KUNDESTAFFELNR;
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short TM_DATE;
    short TM_TIME;
    short LOGINID;
    short CHANGEID;
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

/* Structur (buf_desc) of LDAUFTRAGARTKD **************************************/

#if defined (BUF_DESC)
static struct buf_desc LDAUFTRAGARTKD_BES [] = {
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
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 10, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc LDAUFTRAGARTKD_BES [] = {
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
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 10, 0 },
};
#endif

/* description for datatypes of LDAUFTRAGARTKD ********************************/

 #define LDAUFTRAGARTKD_S390 \
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
         char KZUPD; \
         short RABATTART; \
         long KUNDESTAFFELNR; \
         short VERTRIEBSZENTRUMNR; \
         long KUNDENNR; \
         long TM_DATE; \
         long TM_TIME; \
         long LOGINID; \
         char CHANGEID; \
         char SKDAUFTRAGARTDD; \
         short ORDERLABELCOUNT; \
         short SWMSV3; \
         short SWPARTDEL; \
         char ORDERIDENTIFICATIO[11]; \



/* Copy-Function Struct to single Data LDAUFTRAGARTKD *************************/

 #define LDAUFTRAGARTKD_S390_COPY_TO_SINGLE(_x_) \
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
         KZUPD=_x_->KZUPD;\
         RABATTART=_x_->RABATTART;\
         KUNDESTAFFELNR=_x_->KUNDESTAFFELNR;\
         VERTRIEBSZENTRUMNR=_x_->VERTRIEBSZENTRUMNR;\
         KUNDENNR=_x_->KUNDENNR;\
         TM_DATE=_x_->TM_DATE;\
         TM_TIME=_x_->TM_TIME;\
         LOGINID=_x_->LOGINID;\
         CHANGEID=_x_->CHANGEID;\
         SKDAUFTRAGARTDD=_x_->SKDAUFTRAGARTDD;\
         ORDERLABELCOUNT=_x_->ORDERLABELCOUNT;\
         SWMSV3=_x_->SWMSV3;\
         SWPARTDEL=_x_->SWPARTDEL;\
          strcpy(ORDERIDENTIFICATIO,_x_->ORDERIDENTIFICATIO);\

 #define LDAUFTRAGARTKD_S390_COPY_TO_STRUCT(_x_) \
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
          _x_->KZUPD=KZUPD;\
          _x_->RABATTART=RABATTART;\
          _x_->KUNDESTAFFELNR=KUNDESTAFFELNR;\
          _x_->VERTRIEBSZENTRUMNR=VERTRIEBSZENTRUMNR;\
          _x_->KUNDENNR=KUNDENNR;\
          _x_->TM_DATE=TM_DATE;\
          _x_->TM_TIME=TM_TIME;\
          _x_->LOGINID=LOGINID;\
          _x_->CHANGEID=CHANGEID;\
          _x_->SKDAUFTRAGARTDD=SKDAUFTRAGARTDD;\
          _x_->ORDERLABELCOUNT=ORDERLABELCOUNT;\
          _x_->SWMSV3=SWMSV3;\
          _x_->SWPARTDEL=SWPARTDEL;\
          strcpy(_x_->ORDERIDENTIFICATIO,ORDERIDENTIFICATIO);\



/* FunctionNumber-Define of ldauftragartkd ************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of ldauftragartkd ********************************/


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

class CLDAUFTRAGARTKD : public ppDadeVirtual {
public:
    ldauftragartkdS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<ldauftragartkdS> lst; // class list

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
                     vector< ldauftragartkdS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     ldauftragartkdS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< ldauftragartkdS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<ldauftragartkdS>::iterator
                 beginList() { return lst.begin(); }
    vector<ldauftragartkdS>::iterator
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
    char         GetKzupd() const { return s.KZUPD[0]; }
    short        GetRabattart() const { return s.RABATTART; }
    long         GetKundestaffelnr() const { return s.KUNDESTAFFELNR; }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    long         GetTm_date() const { return s.TM_DATE; }
    long         GetTm_time() const { return s.TM_TIME; }
    long         GetLoginid() const { return s.LOGINID; }
    char         GetChangeid() const { return s.CHANGEID[0]; }
    char         GetSkdauftragartdd() const { return s.SKDAUFTRAGARTDD[0]; }
    short        GetOrderlabelcount() const { return s.ORDERLABELCOUNT; }
    short        GetSwmsv3() const { return s.SWMSV3; }
    short        GetSwpartdel() const { return s.SWPARTDEL; }
    const char*  GetOrderidentificatio(ppString & t) const { t = s.ORDERIDENTIFICATIO; t.erasespace(ppString::END); return t.c_str(); }

    const ldauftragartkdS &
                 GetStruct() const { return s; }
    void         SetIdfnr(long t) { s.IDFNR = t; }
    void         SetKdauftragart(const ppString & t) { ppGStrCopy(s.KDAUFTRAGART, t.c_str(), L_LDAUFTRAGARTKD_KDAUFTRAGART); }
    void         SetValutamonate(long t) { s.VALUTAMONATE = t; }
    void         SetSkdauftragartnatra(char t) { s.SKDAUFTRAGARTNATRA[0] = t; s.SKDAUFTRAGARTNATRA[1] = '\0';}
    void         SetSkdauftragartnetto(char t) { s.SKDAUFTRAGARTNETTO[0] = t; s.SKDAUFTRAGARTNETTO[1] = '\0';}
    void         SetSkdauftragartbanr(char t) { s.SKDAUFTRAGARTBANR[0] = t; s.SKDAUFTRAGARTBANR[1] = '\0';}
    void         SetSkdauftragartmonat(char t) { s.SKDAUFTRAGARTMONAT[0] = t; s.SKDAUFTRAGARTMONAT[1] = '\0';}
    void         SetSkdauftragverbund(char t) { s.SKDAUFTRAGVERBUND[0] = t; s.SKDAUFTRAGVERBUND[1] = '\0';}
    void         SetSkdauftragartvals(char t) { s.SKDAUFTRAGARTVALS[0] = t; s.SKDAUFTRAGARTVALS[1] = '\0';}
    void         SetValutamonauto(short t) { s.VALUTAMONAUTO = t; }
    void         SetKzupd(char t) { s.KZUPD[0] = t; s.KZUPD[1] = '\0';}
    void         SetRabattart(short t) { s.RABATTART = t; }
    void         SetKundestaffelnr(long t) { s.KUNDESTAFFELNR = t; }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetTm_date(long t) { s.TM_DATE = t; }
    void         SetTm_time(long t) { s.TM_TIME = t; }
    void         SetLoginid(long t) { s.LOGINID = t; }
    void         SetChangeid(char t) { s.CHANGEID[0] = t; s.CHANGEID[1] = '\0';}
    void         SetSkdauftragartdd(char t) { s.SKDAUFTRAGARTDD[0] = t; s.SKDAUFTRAGARTDD[1] = '\0';}
    void         SetOrderlabelcount(short t) { s.ORDERLABELCOUNT = t; }
    void         SetSwmsv3(short t) { s.SWMSV3 = t; }
    void         SetSwpartdel(short t) { s.SWPARTDEL = t; }
    void         SetOrderidentificatio(const ppString & t) { ppGStrCopy(s.ORDERIDENTIFICATIO, t.c_str(), L_LDAUFTRAGARTKD_ORDERIDENTIFICATIO); }

    void         SetStruct(const ldauftragartkdS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CLDAUFTRAGARTKD() {
        ::buf_default((void *)&s, LDAUFTRAGARTKD_BES, LDAUFTRAGARTKD_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CLDAUFTRAGARTKD() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, LDAUFTRAGARTKD_BES, LDAUFTRAGARTKD_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, LDAUFTRAGARTKD_BES, (int)LDAUFTRAGARTKD_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, LDAUFTRAGARTKD_BES, (int)LDAUFTRAGARTKD_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_LDAUFTRAGARTKD & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.KDAUFTRAGART);
        ppGStripLast(d.ORDERIDENTIFICATIO);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, LDAUFTRAGARTKD_BES, (int)LDAUFTRAGARTKD_ANZ, error_msg);
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
/* CreateSqlStatement of LDAUFTRAGARTKD ***************************************/

 #define LDAUFTRAGARTKD_CREATE(x) EXEC SQL create table x (\
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
         KZUPD char(1) default " " not null,\
         RABATTART smallint default 0 not null,\
         KUNDESTAFFELNR integer default 0 not null,\
         VERTRIEBSZENTRUMNR smallint default 0 not null,\
         KUNDENNR integer default 0 not null,\
         TM_DATE integer default 0 not null,\
         TM_TIME integer default 0 not null,\
         LOGINID integer default 0 not null,\
         CHANGEID char(1) default " " not null,\
         SKDAUFTRAGARTDD char(1) default " " not null,\
         ORDERLABELCOUNT smallint default 0 not null,\
         SWMSV3 smallint default 0 not null,\
         SWPARTDEL smallint default 0 not null,\
         ORDERIDENTIFICATIO char(10) default " " not null) extent size 2116 next size 212 lock mode row;



/* CreateIndexStatement of LDAUFTRAGARTKD *************************************/

 #define LDAUFTRAGARTKD_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create   index auftragartkdx on _X_(\
              idfnr,\
              kdauftragart );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create unique index i_auftragartkd_1 on _X_(\
              VertriebszentrumNr,\
              KundenNr,\
              kdauftragart );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of LDAUFTRAGARTKD *************************************/

 #define LDAUFTRAGARTKD_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index auftragartkdx;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_auftragartkd_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
