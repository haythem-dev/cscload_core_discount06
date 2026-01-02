#ifndef __PP_FILIALPARTNER_H_
#define __PP_FILIALPARTNER_H_

/******************************************************************************/
/* c:\git\pharmos.outbound.csc_core_applications\dev\src\aapserv\filialpartner */
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of BACKROUT **************************************************/

#define L_BACKROUT_BRANCHNO 6
#define L_BACKROUT_DEPARTEMENT 20
#define L_BACKROUT_PHONENO 20

/* Length-Define of BRANCHINFO ************************************************/

#define L_BRANCHINFO_BRANCHNO 6
#define L_BRANCHINFO_INFORMATION 2000
#define L_BRANCHINFO_BRANCHINFOTYPE 6

/* Length-Define of BRANCHNAMES ***********************************************/

#define L_BRANCHNAMES_FILIALNR 6
#define L_BRANCHNAMES_RECHNER_NAME 7
#define L_BRANCHNAMES_STANDORT 15
#define L_BRANCHNAMES_DATENBANK_NAME 35

/* Length-Define of IBTBRANCHESADMIN ******************************************/

#define L_IBTBRANCHESADMIN_BRANCHNO 6
#define L_IBTBRANCHESADMIN_PRIORITY 6
#define L_IBTBRANCHESADMIN_IBTBRANCHNO 6
#define L_IBTBRANCHESADMIN_IBTTYPE 6
#define L_IBTBRANCHESADMIN_DAYIBT 6
#define L_IBTBRANCHESADMIN_IBTCUSTOMERNO 11
#define L_IBTBRANCHESADMIN_ACTIVE_FLAG 6
#define L_IBTBRANCHESADMIN_NLEVELIBTTYPEID 6
#define L_IBTBRANCHESADMIN_NLEVELIBTASSORTMENTTYPEID 6
#define L_IBTBRANCHESADMIN_BGANR_EK 11

/* Length-Define of NLEVELIBTBRANCHES *****************************************/

#define L_NLEVELIBTBRANCHES_BRANCHNO 6
#define L_NLEVELIBTBRANCHES_IBTBRANCHNO 6
#define L_NLEVELIBTBRANCHES_IBTTYPE 6
#define L_NLEVELIBTBRANCHES_ZEITBEGIN 11
#define L_NLEVELIBTBRANCHES_ZEITENDE 11
#define L_NLEVELIBTBRANCHES_NLEVELIBTTYPEID 6
#define L_NLEVELIBTBRANCHES_WEEKDAY 6

/* Length-Define of REGIONBRANCHES ********************************************/

#define L_REGIONBRANCHES_REGIONNR 11
#define L_REGIONBRANCHES_REGIONTEILNR 11
#define L_REGIONBRANCHES_STANDORT_LANG 15

/* Length-Define of REGIONS ***************************************************/

#define L_REGIONS_REGIONNO 6
#define L_REGIONS_REGIONNAME 254
#define L_REGIONS_REGIONBRANCHNO 6

/* Length-Define of VBFILIALEN ************************************************/

#define L_VBFILIALEN_FILIALNR 6
#define L_VBFILIALEN_VERBUNDFILIALNR 6
#define L_VBFILIALEN_TAGESTYP 6
#define L_VBFILIALEN_ZEITBEGIN 11
#define L_VBFILIALEN_ZEITENDE 11
#define L_VBFILIALEN_WEEKDAY 6
#define L_VBFILIALEN_VBTYP 6

/* Length-Define of VERBUNDIDF ************************************************/

#define L_VERBUNDIDF_FILIALNR 6
#define L_VERBUNDIDF_BGANR_EK 11

/* Length-Define of ZIELFILIALEN **********************************************/

#define L_ZIELFILIALEN_FILIALNR 6
#define L_ZIELFILIALEN_RECHNER_NAME 7
#define L_ZIELFILIALEN_NAME 30

/* Length-Define of FILIALPARTNER *********************************************/

#define L_FILIALPARTNER_FILIALNR 6
#define L_FILIALPARTNER_NAME 30
#define L_FILIALPARTNER_BGANR 11
#define L_FILIALPARTNER_SUPPORT_FROM 11
#define L_FILIALPARTNER_SUPPORT_UNTIL 11
#define L_FILIALPARTNER_RECHNER_NAME 7

/* Length-Define of FILIALZEITEN **********************************************/

#define L_FILIALZEITEN_FILIALNR 6
#define L_FILIALZEITEN_CLOSED_FROM 11
#define L_FILIALZEITEN_CLOSED_UNTIL 11

/* SqlDefine of BACKROUT ******************************************************/


#define BACKROUT_PLISTE \
        "BACKROUTING.BRANCHNO,"\
        "BACKROUTING.DEPARTEMENT,"\
        "BACKROUTING.PHONENO"

/* SqlDefine of BRANCHINFO ****************************************************/


#define BRANCHINFO_PLISTE \
        "BRANCHINFO.BRANCHNO,"\
        "BRANCHINFO.INFORMATION,"\
        "BRANCHINFO.BRANCHINFOTYPE"

/* SqlDefine of BRANCHNAMES ***************************************************/


#define BRANCHNAMES_PLISTE \
        "RECHNER.FILIALNR,"\
        "RECHNER.RECHNER_NAME,"\
        "RECHNER.STANDORT,"\
        "RECHNER.DATENBANK_NAME"

/* SqlDefine of IBTBRANCHESADMIN **********************************************/


#define IBTBRANCHESADMIN_PLISTE \
        "IBTBRANCHES.BRANCHNO,"\
        "IBTBRANCHES.PRIORITY,"\
        "IBTBRANCHES.IBTBRANCHNO,"\
        "IBTBRANCHES.IBTTYPE,"\
        "IBTBRANCHES.DAYIBT,"\
        "IBTBRANCHES.IBTCUSTOMERNO,"\
        "IBTBRANCHES.ACTIVE_FLAG,"\
        "IBTBRANCHES.NLEVELIBTTYPEID,"\
        "IBTBRANCHES.NLEVELIBTASSORTMENTTYPEID,"\
        "FILIALE.BGANR_EK"

/* SqlDefine of NLEVELIBTBRANCHES *********************************************/


#define NLEVELIBTBRANCHES_PLISTE \
        "IBTBRANCHES.BRANCHNO,"\
        "IBTBRANCHES.IBTBRANCHNO,"\
        "IBTBRANCHES.IBTTYPE,"\
        "ZEITARTEN.ZEITBEGIN,"\
        "ZEITARTEN.ZEITENDE,"\
        "IBTBRANCHES.NLEVELIBTTYPEID,"\
        "ZEITARTEN.WEEKDAY"

/* SqlDefine of REGIONBRANCHES ************************************************/


#define REGIONBRANCHES_PLISTE \
        "REGIONARTEN.REGIONNR,"\
        "REGIONARTEN.REGIONTEILNR,"\
        "FILIALE.STANDORT_LANG"

/* SqlDefine of REGIONS *******************************************************/


#define REGIONS_PLISTE \
        "REGIONS.REGIONNO,"\
        "REGIONS.REGIONNAME,"\
        "REGIONS.REGIONBRANCHNO"

/* SqlDefine of VBFILIALEN ****************************************************/


#define VBFILIALEN_PLISTE \
        "ALTERNATIVFILIALE.FILIALNR,"\
        "ALTERNATIVFILIALE.VERBUNDFILIALNR,"\
        "ZEITARTEN.TAGESTYP,"\
        "ZEITARTEN.ZEITBEGIN,"\
        "ZEITARTEN.ZEITENDE,"\
        "ZEITARTEN.WEEKDAY,"\
        "ALTERNATIVFILIALE.VBTYP"

/* SqlDefine of VERBUNDIDF ****************************************************/


#define VERBUNDIDF_PLISTE \
        "FILIALE.FILIALNR,"\
        "FILIALE.BGANR_EK"

/* SqlDefine of ZIELFILIALEN **************************************************/


#define ZIELFILIALEN_PLISTE \
        "FILIALE.FILIALNR,"\
        "RECHNER.RECHNER_NAME,"\
        "FILIALE.NAME"

/* SqlDefine of FILIALPARTNER *************************************************/


#define FILIALPARTNER_PLISTE \
        "FILIALPARTNER.FILIALNR,"\
        "FILIALPARTNER.NAME,"\
        "FILIALPARTNER.BGANR,"\
        "FILIALPARTNER.SUPPORT_FROM,"\
        "FILIALPARTNER.SUPPORT_UNTIL,"\
        "FILIALPARTNER.RECHNER_NAME"

/* SqlDefine of FILIALZEITEN **************************************************/


#define FILIALZEITEN_PLISTE \
        "FILIALE.FILIALNR,"\
        "FILIALE.CLOSED_FROM,"\
        "FILIALE.CLOSED_UNTIL"

/* SqlDefine of BACKROUT ******************************************************/


#define BACKROUT_UPDLISTE \
        "BRANCHNO=?,"\
        "DEPARTEMENT=?,"\
        "PHONENO=?"
/* SqlDefine of BRANCHINFO ****************************************************/


#define BRANCHINFO_UPDLISTE \
        "BRANCHNO=?,"\
        "INFORMATION=?,"\
        "BRANCHINFOTYPE=?"
/* SqlDefine of BRANCHNAMES ***************************************************/


#define BRANCHNAMES_UPDLISTE \
        "FILIALNR=?,"\
        "RECHNER_NAME=?,"\
        "STANDORT=?,"\
        "DATENBANK_NAME=?"
/* SqlDefine of IBTBRANCHESADMIN **********************************************/


#define IBTBRANCHESADMIN_UPDLISTE \
        "BRANCHNO=?,"\
        "PRIORITY=?,"\
        "IBTBRANCHNO=?,"\
        "IBTTYPE=?,"\
        "DAYIBT=?,"\
        "IBTCUSTOMERNO=?,"\
        "ACTIVE_FLAG=?,"\
        "NLEVELIBTTYPEID=?,"\
        "NLEVELIBTASSORTMENTTYPEID=?"
/* SqlDefine of NLEVELIBTBRANCHES *********************************************/


#define NLEVELIBTBRANCHES_UPDLISTE \
        "BRANCHNO=?,"\
        "IBTBRANCHNO=?,"\
        "IBTTYPE=?,"\
        "ZEITBEGIN=?,"\
        "ZEITENDE=?,"\
        "NLEVELIBTTYPEID=?,"\
        "WEEKDAY=?"
/* SqlDefine of REGIONBRANCHES ************************************************/


#define REGIONBRANCHES_UPDLISTE \
        "REGIONNR=?,"\
        "REGIONTEILNR=?,"\
        "STANDORT_LANG=?"
/* SqlDefine of REGIONS *******************************************************/


#define REGIONS_UPDLISTE \
        "REGIONNO=?,"\
        "REGIONNAME=?,"\
        "REGIONBRANCHNO=?"
/* SqlDefine of VBFILIALEN ****************************************************/


#define VBFILIALEN_UPDLISTE \
        "FILIALNR=?,"\
        "VERBUNDFILIALNR=?,"\
        "TAGESTYP=?,"\
        "ZEITBEGIN=?,"\
        "ZEITENDE=?,"\
        "WEEKDAY=?,"\
        "VBTYP=?"
/* SqlDefine of VERBUNDIDF ****************************************************/


#define VERBUNDIDF_UPDLISTE \
        "FILIALNR=?,"\
        "BGANR_EK=?"
/* SqlDefine of ZIELFILIALEN **************************************************/


#define ZIELFILIALEN_UPDLISTE \
        "FILIALNR=?,"\
        "RECHNER_NAME=?,"\
        "NAME=?"
/* SqlDefine of FILIALPARTNER *************************************************/


#define FILIALPARTNER_UPDLISTE \
        "FILIALNR=?,"\
        "NAME=?,"\
        "BGANR=?,"\
        "SUPPORT_FROM=?,"\
        "SUPPORT_UNTIL=?,"\
        "RECHNER_NAME=?"
/* SqlDefine of FILIALZEITEN **************************************************/


#define FILIALZEITEN_UPDLISTE \
        "FILIALNR=?,"\
        "CLOSED_FROM=?,"\
        "CLOSED_UNTIL=?"
/* SqlMacros-Define of BACKROUT ***********************************************/

#define BACKROUT_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->DEPARTEMENT,\
        :x->PHONENO
#define BACKROUT_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->DEPARTEMENT,\
        :x->PHONENO

/* SqlMacros-Define of BRANCHINFO *********************************************/

#define BRANCHINFO_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->INFORMATION,\
        :x->BRANCHINFOTYPE
#define BRANCHINFO_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->INFORMATION,\
        :x->BRANCHINFOTYPE

/* SqlMacros-Define of BRANCHNAMES ********************************************/

#define BRANCHNAMES_ZEIGER(x) \
        :x->FILIALNR,\
        :x->RECHNER_NAME,\
        :x->STANDORT,\
        :x->DATENBANK_NAME
#define BRANCHNAMES_ZEIGERSEL(x) \
        :x->FILIALNR,\
        :x->RECHNER_NAME,\
        :x->STANDORT,\
        :x->DATENBANK_NAME

/* SqlMacros-Define of IBTBRANCHESADMIN ***************************************/

#define IBTBRANCHESADMIN_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->PRIORITY,\
        :x->IBTBRANCHNO,\
        :x->IBTTYPE,\
        :x->DAYIBT,\
        :x->IBTCUSTOMERNO,\
        :x->ACTIVE_FLAG,\
        :x->NLEVELIBTTYPEID,\
        :x->NLEVELIBTASSORTMENTTYPEID
#define IBTBRANCHESADMIN_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->PRIORITY,\
        :x->IBTBRANCHNO,\
        :x->IBTTYPE,\
        :x->DAYIBT,\
        :x->IBTCUSTOMERNO,\
        :x->ACTIVE_FLAG,\
        :x->NLEVELIBTTYPEID,\
        :x->NLEVELIBTASSORTMENTTYPEID,\
        :x->BGANR_EK

/* SqlMacros-Define of NLEVELIBTBRANCHES **************************************/

#define NLEVELIBTBRANCHES_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->IBTBRANCHNO,\
        :x->IBTTYPE,\
        :x->ZEITBEGIN,\
        :x->ZEITENDE,\
        :x->NLEVELIBTTYPEID,\
        :x->WEEKDAY
#define NLEVELIBTBRANCHES_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->IBTBRANCHNO,\
        :x->IBTTYPE,\
        :x->ZEITBEGIN,\
        :x->ZEITENDE,\
        :x->NLEVELIBTTYPEID,\
        :x->WEEKDAY

/* SqlMacros-Define of REGIONBRANCHES *****************************************/

#define REGIONBRANCHES_ZEIGER(x) \
        :x->REGIONNR,\
        :x->REGIONTEILNR,\
        :x->STANDORT_LANG
#define REGIONBRANCHES_ZEIGERSEL(x) \
        :x->REGIONNR,\
        :x->REGIONTEILNR,\
        :x->STANDORT_LANG

/* SqlMacros-Define of REGIONS ************************************************/

#define REGIONS_ZEIGER(x) \
        :x->REGIONNO,\
        :x->REGIONNAME,\
        :x->REGIONBRANCHNO
#define REGIONS_ZEIGERSEL(x) \
        :x->REGIONNO,\
        :x->REGIONNAME,\
        :x->REGIONBRANCHNO

/* SqlMacros-Define of VBFILIALEN *********************************************/

#define VBFILIALEN_ZEIGER(x) \
        :x->FILIALNR,\
        :x->VERBUNDFILIALNR,\
        :x->TAGESTYP,\
        :x->ZEITBEGIN,\
        :x->ZEITENDE,\
        :x->WEEKDAY,\
        :x->VBTYP
#define VBFILIALEN_ZEIGERSEL(x) \
        :x->FILIALNR,\
        :x->VERBUNDFILIALNR,\
        :x->TAGESTYP,\
        :x->ZEITBEGIN,\
        :x->ZEITENDE,\
        :x->WEEKDAY,\
        :x->VBTYP

/* SqlMacros-Define of VERBUNDIDF *********************************************/

#define VERBUNDIDF_ZEIGER(x) \
        :x->FILIALNR,\
        :x->BGANR_EK
#define VERBUNDIDF_ZEIGERSEL(x) \
        :x->FILIALNR,\
        :x->BGANR_EK

/* SqlMacros-Define of ZIELFILIALEN *******************************************/

#define ZIELFILIALEN_ZEIGER(x) \
        :x->FILIALNR,\
        :x->RECHNER_NAME,\
        :x->NAME
#define ZIELFILIALEN_ZEIGERSEL(x) \
        :x->FILIALNR,\
        :x->RECHNER_NAME,\
        :x->NAME

/* SqlMacros-Define of FILIALPARTNER ******************************************/

#define FILIALPARTNER_ZEIGER(x) \
        :x->FILIALNR,\
        :x->NAME,\
        :x->BGANR,\
        :x->SUPPORT_FROM,\
        :x->SUPPORT_UNTIL,\
        :x->RECHNER_NAME
#define FILIALPARTNER_ZEIGERSEL(x) \
        :x->FILIALNR,\
        :x->NAME,\
        :x->BGANR,\
        :x->SUPPORT_FROM,\
        :x->SUPPORT_UNTIL,\
        :x->RECHNER_NAME

/* SqlMacros-Define of FILIALZEITEN *******************************************/

#define FILIALZEITEN_ZEIGER(x) \
        :x->FILIALNR,\
        :x->CLOSED_FROM,\
        :x->CLOSED_UNTIL
#define FILIALZEITEN_ZEIGERSEL(x) \
        :x->FILIALNR,\
        :x->CLOSED_FROM,\
        :x->CLOSED_UNTIL

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define BACKROUT_H
#define BACKROUT_ANZ ( sizeof(BACKROUT_BES) / sizeof(struct buf_desc) )
#define BRANCHINFO_H
#define BRANCHINFO_ANZ ( sizeof(BRANCHINFO_BES) / sizeof(struct buf_desc) )
#define BRANCHNAMES_H
#define BRANCHNAMES_ANZ ( sizeof(BRANCHNAMES_BES) / sizeof(struct buf_desc) )
#define IBTBRANCHESADMIN_H
#define IBTBRANCHESADMIN_ANZ ( sizeof(IBTBRANCHESADMIN_BES) / sizeof(struct buf_desc) )
#define NLEVELIBTBRANCHES_H
#define NLEVELIBTBRANCHES_ANZ ( sizeof(NLEVELIBTBRANCHES_BES) / sizeof(struct buf_desc) )
#define REGIONBRANCHES_H
#define REGIONBRANCHES_ANZ ( sizeof(REGIONBRANCHES_BES) / sizeof(struct buf_desc) )
#define REGIONS_H
#define REGIONS_ANZ ( sizeof(REGIONS_BES) / sizeof(struct buf_desc) )
#define VBFILIALEN_H
#define VBFILIALEN_ANZ ( sizeof(VBFILIALEN_BES) / sizeof(struct buf_desc) )
#define VERBUNDIDF_H
#define VERBUNDIDF_ANZ ( sizeof(VERBUNDIDF_BES) / sizeof(struct buf_desc) )
#define ZIELFILIALEN_H
#define ZIELFILIALEN_ANZ ( sizeof(ZIELFILIALEN_BES) / sizeof(struct buf_desc) )
#define FILIALPARTNER_H
#define FILIALPARTNER_ANZ ( sizeof(FILIALPARTNER_BES) / sizeof(struct buf_desc) )
#define FILIALZEITEN_H
#define FILIALZEITEN_ANZ ( sizeof(FILIALZEITEN_BES) / sizeof(struct buf_desc) )
#endif

#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of BACKROUT ************************************************/

#ifndef TRANSCLASS
typedef struct N_BACKROUT {
    short BRANCHNO;
    char DEPARTEMENT[21];
    char PHONENO[21];
    long FETCH_REL;
} backroutS;
#else /* TRANSCLASS */
typedef struct N_BACKROUT {
    short BRANCHNO;
    char DEPARTEMENT[21];
    char PHONENO[21];
    long FETCH_REL;
    bool operator == (const N_BACKROUT& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            !strcmp(DEPARTEMENT, right.DEPARTEMENT) &&
            !strcmp(PHONENO, right.PHONENO)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        strcpy(DEPARTEMENT, " " );
        strcpy(PHONENO, " " );
#endif
    }
} backroutS;
#endif /* TRANSCLASS */

/* original struct of BRANCHINFO **********************************************/

#ifndef TRANSCLASS
typedef struct N_BRANCHINFO {
    short BRANCHNO;
    char INFORMATION[2001];
    short BRANCHINFOTYPE;
} branchinfoS;
#else /* TRANSCLASS */
typedef struct N_BRANCHINFO {
    short BRANCHNO;
    char INFORMATION[2001];
    short BRANCHINFOTYPE;

    bool operator == (const N_BRANCHINFO& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            !strcmp(INFORMATION, right.INFORMATION) &&
            BRANCHINFOTYPE == right.BRANCHINFOTYPE
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        strcpy(INFORMATION, " " );
        BRANCHINFOTYPE = 0;
#endif
    }
} branchinfoS;
#endif /* TRANSCLASS */

/* original struct of BRANCHNAMES *********************************************/

#ifndef TRANSCLASS
typedef struct N_BRANCHNAMES {
    short FILIALNR;
    char RECHNER_NAME[8];
    char STANDORT[16];
    char DATENBANK_NAME[36];
    long FETCH_REL;
} branchnamesS;
#else /* TRANSCLASS */
typedef struct N_BRANCHNAMES {
    short FILIALNR;
    char RECHNER_NAME[8];
    char STANDORT[16];
    char DATENBANK_NAME[36];
    long FETCH_REL;
    bool operator == (const N_BRANCHNAMES& right) const {
        return (
            FILIALNR == right.FILIALNR &&
            !strcmp(RECHNER_NAME, right.RECHNER_NAME) &&
            !strcmp(STANDORT, right.STANDORT) &&
            !strcmp(DATENBANK_NAME, right.DATENBANK_NAME)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        FILIALNR = 0;
        strcpy(RECHNER_NAME, " " );
        strcpy(STANDORT, " " );
        strcpy(DATENBANK_NAME, " " );
#endif
    }
} branchnamesS;
#endif /* TRANSCLASS */

/* original struct of IBTBRANCHESADMIN ****************************************/

#ifndef TRANSCLASS
typedef struct N_IBTBRANCHESADMIN {
    short BRANCHNO;
    short PRIORITY;
    short IBTBRANCHNO;
    short IBTTYPE;
    short DAYIBT;
    long IBTCUSTOMERNO;
    short ACTIVE_FLAG;
    short NLEVELIBTTYPEID;
    short NLEVELIBTASSORTMENTTYPEID;
    long BGANR_EK;
    long FETCH_REL;
} ibtbranchesadminS;
#else /* TRANSCLASS */
typedef struct N_IBTBRANCHESADMIN {
    short BRANCHNO;
    short PRIORITY;
    short IBTBRANCHNO;
    short IBTTYPE;
    short DAYIBT;
    long IBTCUSTOMERNO;
    short ACTIVE_FLAG;
    short NLEVELIBTTYPEID;
    short NLEVELIBTASSORTMENTTYPEID;
    long BGANR_EK;
    long FETCH_REL;
    bool operator == (const N_IBTBRANCHESADMIN& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            PRIORITY == right.PRIORITY &&
            IBTBRANCHNO == right.IBTBRANCHNO &&
            IBTTYPE == right.IBTTYPE &&
            DAYIBT == right.DAYIBT &&
            IBTCUSTOMERNO == right.IBTCUSTOMERNO &&
            ACTIVE_FLAG == right.ACTIVE_FLAG &&
            NLEVELIBTTYPEID == right.NLEVELIBTTYPEID &&
            NLEVELIBTASSORTMENTTYPEID == right.NLEVELIBTASSORTMENTTYPEID &&
            BGANR_EK == right.BGANR_EK
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        PRIORITY = 0;
        IBTBRANCHNO = 0;
        IBTTYPE = 0;
        DAYIBT = 0;
        IBTCUSTOMERNO = 0;
        ACTIVE_FLAG = 0;
        NLEVELIBTTYPEID = 0;
        NLEVELIBTASSORTMENTTYPEID = 0;
        BGANR_EK = 0;
#endif
    }
} ibtbranchesadminS;
#endif /* TRANSCLASS */

/* original struct of NLEVELIBTBRANCHES ***************************************/

#ifndef TRANSCLASS
typedef struct N_NLEVELIBTBRANCHES {
    short BRANCHNO;
    short IBTBRANCHNO;
    short IBTTYPE;
    long ZEITBEGIN;
    long ZEITENDE;
    short NLEVELIBTTYPEID;
    short WEEKDAY;
    long FETCH_REL;
} nlevelibtbranchesS;
#else /* TRANSCLASS */
typedef struct N_NLEVELIBTBRANCHES {
    short BRANCHNO;
    short IBTBRANCHNO;
    short IBTTYPE;
    long ZEITBEGIN;
    long ZEITENDE;
    short NLEVELIBTTYPEID;
    short WEEKDAY;
    long FETCH_REL;
    bool operator == (const N_NLEVELIBTBRANCHES& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            IBTBRANCHNO == right.IBTBRANCHNO &&
            IBTTYPE == right.IBTTYPE &&
            ZEITBEGIN == right.ZEITBEGIN &&
            ZEITENDE == right.ZEITENDE &&
            NLEVELIBTTYPEID == right.NLEVELIBTTYPEID &&
            WEEKDAY == right.WEEKDAY
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        IBTBRANCHNO = 0;
        IBTTYPE = 0;
        ZEITBEGIN = 0;
        ZEITENDE = 0;
        NLEVELIBTTYPEID = 0;
        WEEKDAY = 0;
#endif
    }
} nlevelibtbranchesS;
#endif /* TRANSCLASS */

/* original struct of REGIONBRANCHES ******************************************/

#ifndef TRANSCLASS
typedef struct N_REGIONBRANCHES {
    long REGIONNR;
    long REGIONTEILNR;
    char STANDORT_LANG[16];
    long FETCH_REL;
} regionbranchesS;
#else /* TRANSCLASS */
typedef struct N_REGIONBRANCHES {
    long REGIONNR;
    long REGIONTEILNR;
    char STANDORT_LANG[16];
    long FETCH_REL;
    bool operator == (const N_REGIONBRANCHES& right) const {
        return (
            REGIONNR == right.REGIONNR &&
            REGIONTEILNR == right.REGIONTEILNR &&
            !strcmp(STANDORT_LANG, right.STANDORT_LANG)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        REGIONNR = 0;
        REGIONTEILNR = 0;
        strcpy(STANDORT_LANG, " " );
#endif
    }
} regionbranchesS;
#endif /* TRANSCLASS */

/* original struct of REGIONS *************************************************/

#ifndef TRANSCLASS
typedef struct N_REGIONS {
    short REGIONNO;
    char REGIONNAME[255];
    short REGIONBRANCHNO;
} regionsS;
#else /* TRANSCLASS */
typedef struct N_REGIONS {
    short REGIONNO;
    char REGIONNAME[255];
    short REGIONBRANCHNO;

    bool operator == (const N_REGIONS& right) const {
        return (
            REGIONNO == right.REGIONNO &&
            !strcmp(REGIONNAME, right.REGIONNAME) &&
            REGIONBRANCHNO == right.REGIONBRANCHNO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        REGIONNO = 0;
        strcpy(REGIONNAME, " " );
        REGIONBRANCHNO = 0;
#endif
    }
} regionsS;
#endif /* TRANSCLASS */

/* original struct of VBFILIALEN **********************************************/

#ifndef TRANSCLASS
typedef struct N_VBFILIALEN {
    short FILIALNR;
    short VERBUNDFILIALNR;
    char TAGESTYP[7];
    long ZEITBEGIN;
    long ZEITENDE;
    short WEEKDAY;
    short VBTYP;
    long FETCH_REL;
} vbfilialenS;
#else /* TRANSCLASS */
typedef struct N_VBFILIALEN {
    short FILIALNR;
    short VERBUNDFILIALNR;
    char TAGESTYP[7];
    long ZEITBEGIN;
    long ZEITENDE;
    short WEEKDAY;
    short VBTYP;
    long FETCH_REL;
    bool operator == (const N_VBFILIALEN& right) const {
        return (
            FILIALNR == right.FILIALNR &&
            VERBUNDFILIALNR == right.VERBUNDFILIALNR &&
            !strcmp(TAGESTYP, right.TAGESTYP) &&
            ZEITBEGIN == right.ZEITBEGIN &&
            ZEITENDE == right.ZEITENDE &&
            WEEKDAY == right.WEEKDAY &&
            VBTYP == right.VBTYP
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        FILIALNR = 0;
        VERBUNDFILIALNR = 0;
        strcpy(TAGESTYP, " " );
        ZEITBEGIN = 0;
        ZEITENDE = 0;
        WEEKDAY = 0;
        VBTYP = 0;
#endif
    }
} vbfilialenS;
#endif /* TRANSCLASS */

/* original struct of VERBUNDIDF **********************************************/

#ifndef TRANSCLASS
typedef struct N_VERBUNDIDF {
    short FILIALNR;
    long BGANR_EK;
} verbundidfS;
#else /* TRANSCLASS */
typedef struct N_VERBUNDIDF {
    short FILIALNR;
    long BGANR_EK;

    bool operator == (const N_VERBUNDIDF& right) const {
        return (
            FILIALNR == right.FILIALNR &&
            BGANR_EK == right.BGANR_EK
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        FILIALNR = 0;
        BGANR_EK = 0;
#endif
    }
} verbundidfS;
#endif /* TRANSCLASS */

/* original struct of ZIELFILIALEN ********************************************/

#ifndef TRANSCLASS
typedef struct N_ZIELFILIALEN {
    short FILIALNR;
    char RECHNER_NAME[8];
    char NAME[31];
    long FETCH_REL;
} zielfilialenS;
#else /* TRANSCLASS */
typedef struct N_ZIELFILIALEN {
    short FILIALNR;
    char RECHNER_NAME[8];
    char NAME[31];
    long FETCH_REL;
    bool operator == (const N_ZIELFILIALEN& right) const {
        return (
            FILIALNR == right.FILIALNR &&
            !strcmp(RECHNER_NAME, right.RECHNER_NAME) &&
            !strcmp(NAME, right.NAME)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        FILIALNR = 0;
        strcpy(RECHNER_NAME, " " );
        strcpy(NAME, " " );
#endif
    }
} zielfilialenS;
#endif /* TRANSCLASS */

/* original struct of FILIALPARTNER *******************************************/

#ifndef TRANSCLASS
typedef struct N_FILIALPARTNER {
    short FILIALNR;
    char NAME[31];
    long BGANR;
    long SUPPORT_FROM;
    long SUPPORT_UNTIL;
    char RECHNER_NAME[8];
    long FETCH_REL;
} filialpartnerS;
#else /* TRANSCLASS */
typedef struct N_FILIALPARTNER {
    short FILIALNR;
    char NAME[31];
    long BGANR;
    long SUPPORT_FROM;
    long SUPPORT_UNTIL;
    char RECHNER_NAME[8];
    long FETCH_REL;
    bool operator == (const N_FILIALPARTNER& right) const {
        return (
            FILIALNR == right.FILIALNR &&
            !strcmp(NAME, right.NAME) &&
            BGANR == right.BGANR &&
            SUPPORT_FROM == right.SUPPORT_FROM &&
            SUPPORT_UNTIL == right.SUPPORT_UNTIL &&
            !strcmp(RECHNER_NAME, right.RECHNER_NAME)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        FILIALNR = 0;
        strcpy(NAME, " " );
        BGANR = 0;
        SUPPORT_FROM = 0;
        SUPPORT_UNTIL = 0;
        strcpy(RECHNER_NAME, " " );
#endif
    }
} filialpartnerS;
#endif /* TRANSCLASS */

/* original struct of FILIALZEITEN ********************************************/

#ifndef TRANSCLASS
typedef struct N_FILIALZEITEN {
    short FILIALNR;
    long CLOSED_FROM;
    long CLOSED_UNTIL;
    long FETCH_REL;
} filialzeitenS;
#else /* TRANSCLASS */
typedef struct N_FILIALZEITEN {
    short FILIALNR;
    long CLOSED_FROM;
    long CLOSED_UNTIL;
    long FETCH_REL;
    bool operator == (const N_FILIALZEITEN& right) const {
        return (
            FILIALNR == right.FILIALNR &&
            CLOSED_FROM == right.CLOSED_FROM &&
            CLOSED_UNTIL == right.CLOSED_UNTIL
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        FILIALNR = 0;
        CLOSED_FROM = 0;
        CLOSED_UNTIL = 0;
#endif
    }
} filialzeitenS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of BACKROUT ************************************/

struct C_BACKROUT {
    short BRANCHNO;
    char DEPARTEMENT[21];
    char PHONENO[21];
    long FETCH_REL;
};
/* Structur with real chartype of BRANCHINFO **********************************/

struct C_BRANCHINFO {
    short BRANCHNO;
    char INFORMATION[2001];
    short BRANCHINFOTYPE;
};
/* Structur with real chartype of BRANCHNAMES *********************************/

struct C_BRANCHNAMES {
    short FILIALNR;
    char RECHNER_NAME[8];
    char STANDORT[16];
    char DATENBANK_NAME[36];
    long FETCH_REL;
};
/* Structur with real chartype of IBTBRANCHESADMIN ****************************/

struct C_IBTBRANCHESADMIN {
    short BRANCHNO;
    short PRIORITY;
    short IBTBRANCHNO;
    short IBTTYPE;
    short DAYIBT;
    long IBTCUSTOMERNO;
    short ACTIVE_FLAG;
    short NLEVELIBTTYPEID;
    short NLEVELIBTASSORTMENTTYPEID;
    long BGANR_EK;
    long FETCH_REL;
};
/* Structur with real chartype of NLEVELIBTBRANCHES ***************************/

struct C_NLEVELIBTBRANCHES {
    short BRANCHNO;
    short IBTBRANCHNO;
    short IBTTYPE;
    long ZEITBEGIN;
    long ZEITENDE;
    short NLEVELIBTTYPEID;
    short WEEKDAY;
    long FETCH_REL;
};
/* Structur with real chartype of REGIONBRANCHES ******************************/

struct C_REGIONBRANCHES {
    long REGIONNR;
    long REGIONTEILNR;
    char STANDORT_LANG[16];
    long FETCH_REL;
};
/* Structur with real chartype of REGIONS *************************************/

struct C_REGIONS {
    short REGIONNO;
    char REGIONNAME[255];
    short REGIONBRANCHNO;
};
/* Structur with real chartype of VBFILIALEN **********************************/

struct C_VBFILIALEN {
    short FILIALNR;
    short VERBUNDFILIALNR;
    char TAGESTYP[7];
    long ZEITBEGIN;
    long ZEITENDE;
    short WEEKDAY;
    short VBTYP;
    long FETCH_REL;
};
/* Structur with real chartype of VERBUNDIDF **********************************/

struct C_VERBUNDIDF {
    short FILIALNR;
    long BGANR_EK;
};
/* Structur with real chartype of ZIELFILIALEN ********************************/

struct C_ZIELFILIALEN {
    short FILIALNR;
    char RECHNER_NAME[8];
    char NAME[31];
    long FETCH_REL;
};
/* Structur with real chartype of FILIALPARTNER *******************************/

struct C_FILIALPARTNER {
    short FILIALNR;
    char NAME[31];
    long BGANR;
    long SUPPORT_FROM;
    long SUPPORT_UNTIL;
    char RECHNER_NAME[8];
    long FETCH_REL;
};
/* Structur with real chartype of FILIALZEITEN ********************************/

struct C_FILIALZEITEN {
    short FILIALNR;
    long CLOSED_FROM;
    long CLOSED_UNTIL;
    long FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of BACKROUT **********************************/

struct I_BACKROUT {
    short BRANCHNO;
    short DEPARTEMENT;
    short PHONENO;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of BRANCHINFO ********************************/

struct I_BRANCHINFO {
    short BRANCHNO;
    short INFORMATION;
    short BRANCHINFOTYPE;
};
/* Sizetype  Structur (buf_desc) of BRANCHNAMES *******************************/

struct I_BRANCHNAMES {
    short FILIALNR;
    short RECHNER_NAME;
    short STANDORT;
    short DATENBANK_NAME;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of IBTBRANCHESADMIN **************************/

struct I_IBTBRANCHESADMIN {
    short BRANCHNO;
    short PRIORITY;
    short IBTBRANCHNO;
    short IBTTYPE;
    short DAYIBT;
    short IBTCUSTOMERNO;
    short ACTIVE_FLAG;
    short NLEVELIBTTYPEID;
    short NLEVELIBTASSORTMENTTYPEID;
    short BGANR_EK;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of NLEVELIBTBRANCHES *************************/

struct I_NLEVELIBTBRANCHES {
    short BRANCHNO;
    short IBTBRANCHNO;
    short IBTTYPE;
    short ZEITBEGIN;
    short ZEITENDE;
    short NLEVELIBTTYPEID;
    short WEEKDAY;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of REGIONBRANCHES ****************************/

struct I_REGIONBRANCHES {
    short REGIONNR;
    short REGIONTEILNR;
    short STANDORT_LANG;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of REGIONS ***********************************/

struct I_REGIONS {
    short REGIONNO;
    short REGIONNAME;
    short REGIONBRANCHNO;
};
/* Sizetype  Structur (buf_desc) of VBFILIALEN ********************************/

struct I_VBFILIALEN {
    short FILIALNR;
    short VERBUNDFILIALNR;
    short TAGESTYP;
    short ZEITBEGIN;
    short ZEITENDE;
    short WEEKDAY;
    short VBTYP;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of VERBUNDIDF ********************************/

struct I_VERBUNDIDF {
    short FILIALNR;
    short BGANR_EK;
};
/* Sizetype  Structur (buf_desc) of ZIELFILIALEN ******************************/

struct I_ZIELFILIALEN {
    short FILIALNR;
    short RECHNER_NAME;
    short NAME;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of FILIALPARTNER *****************************/

struct I_FILIALPARTNER {
    short FILIALNR;
    short NAME;
    short BGANR;
    short SUPPORT_FROM;
    short SUPPORT_UNTIL;
    short RECHNER_NAME;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of FILIALZEITEN ******************************/

struct I_FILIALZEITEN {
    short FILIALNR;
    short CLOSED_FROM;
    short CLOSED_UNTIL;
    short FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of BACKROUT ********************************************/

#if defined (BUF_DESC)
static struct buf_desc BACKROUT_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 20, 0 },
   { TYP_C, 20, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc BACKROUT_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 20, 0 },
   { TYP_C, 20, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of BRANCHINFO ******************************************/

#if defined (BUF_DESC)
static struct buf_desc BRANCHINFO_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 2000, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc BRANCHINFO_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 2000, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* Structur (buf_desc) of BRANCHNAMES *****************************************/

#if defined (BUF_DESC)
static struct buf_desc BRANCHNAMES_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 7, 0 },
   { TYP_C, 15, 0 },
   { TYP_C, 35, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc BRANCHNAMES_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 7, 0 },
   { TYP_C, 15, 0 },
   { TYP_C, 35, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of IBTBRANCHESADMIN ************************************/

#if defined (BUF_DESC)
static struct buf_desc IBTBRANCHESADMIN_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc IBTBRANCHESADMIN_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of NLEVELIBTBRANCHES ***********************************/

#if defined (BUF_DESC)
static struct buf_desc NLEVELIBTBRANCHES_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc NLEVELIBTBRANCHES_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of REGIONBRANCHES **************************************/

#if defined (BUF_DESC)
static struct buf_desc REGIONBRANCHES_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 15, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc REGIONBRANCHES_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 15, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of REGIONS *********************************************/

#if defined (BUF_DESC)
static struct buf_desc REGIONS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 254, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc REGIONS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 254, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* Structur (buf_desc) of VBFILIALEN ******************************************/

#if defined (BUF_DESC)
static struct buf_desc VBFILIALEN_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc VBFILIALEN_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of VERBUNDIDF ******************************************/

#if defined (BUF_DESC)
static struct buf_desc VERBUNDIDF_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc VERBUNDIDF_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of ZIELFILIALEN ****************************************/

#if defined (BUF_DESC)
static struct buf_desc ZIELFILIALEN_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 7, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc ZIELFILIALEN_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 7, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of FILIALPARTNER ***************************************/

#if defined (BUF_DESC)
static struct buf_desc FILIALPARTNER_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 7, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc FILIALPARTNER_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 7, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of FILIALZEITEN ****************************************/

#if defined (BUF_DESC)
static struct buf_desc FILIALZEITEN_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc FILIALZEITEN_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* FunctionNumber-Define of BackRout ******************************************/

#define BACKROUT_DELETE 1350
#define BACKROUT_INSERT 1349
#define BACKROUT_SELLIST 1348

/* FunctionNumber-Define of BranchInfo ****************************************/

#define BRANCHINFO_INSERT 1380
#define BRANCHINFO_SELINFO 1381
#define BRANCHINFO_UPDATE 1382

/* FunctionNumber-Define of BranchNames ***************************************/

#define BRANCHNAMES_SELLIST 1718

/* FunctionNumber-Define of IbtBranchesAdmin **********************************/

#define IBTBRANCHESADMIN_DELETE 1683
#define IBTBRANCHESADMIN_INSERT 1682
#define IBTBRANCHESADMIN_SELLIST 1680
#define IBTBRANCHESADMIN_UPDATE 1681

/* FunctionNumber-Define of NLevelIBTBranches *********************************/

#define NLEVELIBTBRANCHES_SELIBTBRANCHES 1711

/* FunctionNumber-Define of RegionBranches ************************************/

#define REGIONBRANCHES_SELLIST 1739

/* FunctionNumber-Define of Regions *******************************************/

#define REGIONS_SELREGION 1679

/* FunctionNumber-Define of VBFILIALEN ****************************************/

#define VBFILIALEN_SELVBFILIALEN 1042

/* FunctionNumber-Define of VerbundIdf ****************************************/

#define VERBUNDIDF_SELVBIDF 1558

/* FunctionNumber-Define of ZielFilialen **************************************/

#define ZIELFILIALEN_SELLIST 1450

/* FunctionNumber-Define of filialpartner *************************************/

#define FILIALPARTNER_DELETE 1014
#define FILIALPARTNER_INSERT 1016
#define FILIALPARTNER_SEL 1013
#define FILIALPARTNER_SELSUPPORTTIME 1022
#define FILIALPARTNER_UPDATE 1015

/* FunctionNumber-Define of filialzeiten **************************************/

#define FILIALZEITEN_SELZEITEN 1019
#define FILIALZEITEN_UPDATEZEITEN 1021

#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of BackRout **************************************/

#define Delete 1350
#define Insert 1349
#define SelList 1348

/* Old-FunctionNumber-Define of BranchInfo ************************************/

#define Insert 1380
#define SelInfo 1381
#define Update 1382

/* Old-FunctionNumber-Define of BranchNames ***********************************/

#define SelList 1718

/* Old-FunctionNumber-Define of IbtBranchesAdmin ******************************/

#define Delete 1683
#define Insert 1682
#define SelList 1680
#define Update 1681

/* Old-FunctionNumber-Define of NLevelIBTBranches *****************************/

#define SelIBTBranches 1711

/* Old-FunctionNumber-Define of RegionBranches ********************************/

#define SelList 1739

/* Old-FunctionNumber-Define of Regions ***************************************/

#define SelRegion 1679

/* Old-FunctionNumber-Define of VBFILIALEN ************************************/

#define SelVbFilialen 1042

/* Old-FunctionNumber-Define of VerbundIdf ************************************/

#define SelVBIdf 1558

/* Old-FunctionNumber-Define of ZielFilialen **********************************/

#define SelList 1450

/* Old-FunctionNumber-Define of filialpartner *********************************/

#define Delete 1014
#define Insert 1016
#define Sel 1013
#define SelSupportTime 1022
#define Update 1015

/* Old-FunctionNumber-Define of filialzeiten **********************************/

#define SelZeiten 1019
#define UpdateZeiten 1021

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

class CBACKROUT : public ppDadeVirtual {
public:
    backroutS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<backroutS> lst; // class list

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
                     vector< backroutS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     backroutS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< backroutS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<backroutS>::iterator
                 beginList() { return lst.begin(); }
    vector<backroutS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    const char*  GetDepartement(ppString & t) const { t = s.DEPARTEMENT; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetPhoneno(ppString & t) const { t = s.PHONENO; t.erasespace(ppString::END); return t.c_str(); }

    const backroutS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetDepartement(const ppString & t) { ppGStrCopy(s.DEPARTEMENT, t.c_str(), L_BACKROUT_DEPARTEMENT); }
    void         SetPhoneno(const ppString & t) { ppGStrCopy(s.PHONENO, t.c_str(), L_BACKROUT_PHONENO); }

    void         SetStruct(const backroutS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          Delete(int pos = 0) { return UniqueServerCall(1350, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1349, pos); Strip(s); return ret; }
    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1348, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CBACKROUT() {
        ::buf_default((void *)&s, BACKROUT_BES, BACKROUT_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CBACKROUT() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, BACKROUT_BES, BACKROUT_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, BACKROUT_BES, (int)BACKROUT_ANZ, error_msg);
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
        if ( fkt_nr == 1350 ) return UniqueServerCall(1350, pos);
        if ( fkt_nr == 1349 ) return UniqueServerCall(1349, pos);
        if ( fkt_nr == 1348 ) return CursorServerCall(1348, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_BACKROUT & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.DEPARTEMENT);
        ppGStripLast(d.PHONENO);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, BACKROUT_BES, (int)BACKROUT_ANZ, error_msg);
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
        CBACKROUT c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, BACKROUT_BES, (int)BACKROUT_ANZ, error_msg);
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

class CBRANCHINFO : public ppDadeVirtual {
public:
    branchinfoS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<branchinfoS> lst; // class list

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
                     vector< branchinfoS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     branchinfoS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< branchinfoS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<branchinfoS>::iterator
                 beginList() { return lst.begin(); }
    vector<branchinfoS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    const char*  GetInformation(ppString & t) const { t = s.INFORMATION; t.erasespace(ppString::END); return t.c_str(); }
    short        GetBranchinfotype() const { return s.BRANCHINFOTYPE; }

    const branchinfoS &
                 GetStruct() const { return s; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetInformation(const ppString & t) { ppGStrCopy(s.INFORMATION, t.c_str(), L_BRANCHINFO_INFORMATION); }
    void         SetBranchinfotype(short t) { s.BRANCHINFOTYPE = t; }

    void         SetStruct(const branchinfoS & t) { s = t; }

    int          Insert(int pos = 0) { int ret = UniqueServerCall(1380, pos); Strip(s); return ret; }
    int          SelInfo(int pos = 0) { int ret = UniqueServerCall(1381, pos); Strip(s); return ret; }
    int          Update(int pos = 0) { int ret = UniqueServerCall(1382, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CBRANCHINFO() {
        ::buf_default((void *)&s, BRANCHINFO_BES, BRANCHINFO_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CBRANCHINFO() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, BRANCHINFO_BES, BRANCHINFO_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1380 ) return UniqueServerCall(1380, pos);
        if ( fkt_nr == 1381 ) return UniqueServerCall(1381, pos);
        if ( fkt_nr == 1382 ) return UniqueServerCall(1382, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_BRANCHINFO & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.INFORMATION);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, BRANCHINFO_BES, (int)BRANCHINFO_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CBRANCHNAMES : public ppDadeVirtual {
public:
    branchnamesS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<branchnamesS> lst; // class list

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
                     vector< branchnamesS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     branchnamesS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< branchnamesS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<branchnamesS>::iterator
                 beginList() { return lst.begin(); }
    vector<branchnamesS>::iterator
                 endList  () { return lst.end  (); }

    short        GetFilialnr() const { return s.FILIALNR; }
    const char*  GetRechner_name(ppString & t) const { t = s.RECHNER_NAME; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetStandort(ppString & t) const { t = s.STANDORT; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetDatenbank_name(ppString & t) const { t = s.DATENBANK_NAME; t.erasespace(ppString::END); return t.c_str(); }

    const branchnamesS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetRechner_name(const ppString & t) { ppGStrCopy(s.RECHNER_NAME, t.c_str(), L_BRANCHNAMES_RECHNER_NAME); }
    void         SetStandort(const ppString & t) { ppGStrCopy(s.STANDORT, t.c_str(), L_BRANCHNAMES_STANDORT); }
    void         SetDatenbank_name(const ppString & t) { ppGStrCopy(s.DATENBANK_NAME, t.c_str(), L_BRANCHNAMES_DATENBANK_NAME); }

    void         SetStruct(const branchnamesS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1718, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CBRANCHNAMES() {
        ::buf_default((void *)&s, BRANCHNAMES_BES, BRANCHNAMES_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CBRANCHNAMES() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, BRANCHNAMES_BES, BRANCHNAMES_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, BRANCHNAMES_BES, (int)BRANCHNAMES_ANZ, error_msg);
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
        if ( fkt_nr == 1718 ) return CursorServerCall(1718, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_BRANCHNAMES & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.RECHNER_NAME);
        ppGStripLast(d.STANDORT);
        ppGStripLast(d.DATENBANK_NAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, BRANCHNAMES_BES, (int)BRANCHNAMES_ANZ, error_msg);
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
        CBRANCHNAMES c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, BRANCHNAMES_BES, (int)BRANCHNAMES_ANZ, error_msg);
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

class CIBTBRANCHESADMIN : public ppDadeVirtual {
public:
    ibtbranchesadminS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<ibtbranchesadminS> lst; // class list

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
                     vector< ibtbranchesadminS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     ibtbranchesadminS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< ibtbranchesadminS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<ibtbranchesadminS>::iterator
                 beginList() { return lst.begin(); }
    vector<ibtbranchesadminS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    short        GetPriority() const { return s.PRIORITY; }
    short        GetIbtbranchno() const { return s.IBTBRANCHNO; }
    short        GetIbttype() const { return s.IBTTYPE; }
    short        GetDayibt() const { return s.DAYIBT; }
    long         GetIbtcustomerno() const { return s.IBTCUSTOMERNO; }
    short        GetActive_flag() const { return s.ACTIVE_FLAG; }
    short        GetNlevelibttypeid() const { return s.NLEVELIBTTYPEID; }
    short        GetNlevelibtassortmenttypeid() const { return s.NLEVELIBTASSORTMENTTYPEID; }
    long         GetBganr_ek() const { return s.BGANR_EK; }

    const ibtbranchesadminS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetPriority(short t) { s.PRIORITY = t; }
    void         SetIbtbranchno(short t) { s.IBTBRANCHNO = t; }
    void         SetIbttype(short t) { s.IBTTYPE = t; }
    void         SetDayibt(short t) { s.DAYIBT = t; }
    void         SetIbtcustomerno(long t) { s.IBTCUSTOMERNO = t; }
    void         SetActive_flag(short t) { s.ACTIVE_FLAG = t; }
    void         SetNlevelibttypeid(short t) { s.NLEVELIBTTYPEID = t; }
    void         SetNlevelibtassortmenttypeid(short t) { s.NLEVELIBTASSORTMENTTYPEID = t; }
    void         SetBganr_ek(long t) { s.BGANR_EK = t; }

    void         SetStruct(const ibtbranchesadminS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          Delete(int pos = 0) { return UniqueServerCall(1683, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1682, pos); Strip(s); return ret; }
    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1680, FetchRel, pos); return ret; }
    int          Update(int pos = 0) { int ret = UniqueServerCall(1681, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CIBTBRANCHESADMIN() {
        ::buf_default((void *)&s, IBTBRANCHESADMIN_BES, IBTBRANCHESADMIN_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CIBTBRANCHESADMIN() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, IBTBRANCHESADMIN_BES, IBTBRANCHESADMIN_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, IBTBRANCHESADMIN_BES, (int)IBTBRANCHESADMIN_ANZ, error_msg);
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
        if ( fkt_nr == 1683 ) return UniqueServerCall(1683, pos);
        if ( fkt_nr == 1682 ) return UniqueServerCall(1682, pos);
        if ( fkt_nr == 1680 ) return CursorServerCall(1680, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1681 ) return UniqueServerCall(1681, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_IBTBRANCHESADMIN & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, IBTBRANCHESADMIN_BES, (int)IBTBRANCHESADMIN_ANZ, error_msg);
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
        CIBTBRANCHESADMIN c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, IBTBRANCHESADMIN_BES, (int)IBTBRANCHESADMIN_ANZ, error_msg);
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

class CNLEVELIBTBRANCHES : public ppDadeVirtual {
public:
    nlevelibtbranchesS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<nlevelibtbranchesS> lst; // class list

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
                     vector< nlevelibtbranchesS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     nlevelibtbranchesS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< nlevelibtbranchesS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<nlevelibtbranchesS>::iterator
                 beginList() { return lst.begin(); }
    vector<nlevelibtbranchesS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    short        GetIbtbranchno() const { return s.IBTBRANCHNO; }
    short        GetIbttype() const { return s.IBTTYPE; }
    long         GetZeitbegin() const { return s.ZEITBEGIN; }
    long         GetZeitende() const { return s.ZEITENDE; }
    short        GetNlevelibttypeid() const { return s.NLEVELIBTTYPEID; }
    short        GetWeekday() const { return s.WEEKDAY; }

    const nlevelibtbranchesS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetIbtbranchno(short t) { s.IBTBRANCHNO = t; }
    void         SetIbttype(short t) { s.IBTTYPE = t; }
    void         SetZeitbegin(long t) { s.ZEITBEGIN = t; }
    void         SetZeitende(long t) { s.ZEITENDE = t; }
    void         SetNlevelibttypeid(short t) { s.NLEVELIBTTYPEID = t; }
    void         SetWeekday(short t) { s.WEEKDAY = t; }

    void         SetStruct(const nlevelibtbranchesS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelIBTBranches(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1711, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CNLEVELIBTBRANCHES() {
        ::buf_default((void *)&s, NLEVELIBTBRANCHES_BES, NLEVELIBTBRANCHES_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CNLEVELIBTBRANCHES() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, NLEVELIBTBRANCHES_BES, NLEVELIBTBRANCHES_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, NLEVELIBTBRANCHES_BES, (int)NLEVELIBTBRANCHES_ANZ, error_msg);
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
        if ( fkt_nr == 1711 ) return CursorServerCall(1711, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_NLEVELIBTBRANCHES & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, NLEVELIBTBRANCHES_BES, (int)NLEVELIBTBRANCHES_ANZ, error_msg);
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
        CNLEVELIBTBRANCHES c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, NLEVELIBTBRANCHES_BES, (int)NLEVELIBTBRANCHES_ANZ, error_msg);
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

class CREGIONBRANCHES : public ppDadeVirtual {
public:
    regionbranchesS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<regionbranchesS> lst; // class list

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
                     vector< regionbranchesS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     regionbranchesS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< regionbranchesS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<regionbranchesS>::iterator
                 beginList() { return lst.begin(); }
    vector<regionbranchesS>::iterator
                 endList  () { return lst.end  (); }

    long         GetRegionnr() const { return s.REGIONNR; }
    long         GetRegionteilnr() const { return s.REGIONTEILNR; }
    const char*  GetStandort_lang(ppString & t) const { t = s.STANDORT_LANG; t.erasespace(ppString::END); return t.c_str(); }

    const regionbranchesS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetRegionnr(long t) { s.REGIONNR = t; }
    void         SetRegionteilnr(long t) { s.REGIONTEILNR = t; }
    void         SetStandort_lang(const ppString & t) { ppGStrCopy(s.STANDORT_LANG, t.c_str(), L_REGIONBRANCHES_STANDORT_LANG); }

    void         SetStruct(const regionbranchesS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1739, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CREGIONBRANCHES() {
        ::buf_default((void *)&s, REGIONBRANCHES_BES, REGIONBRANCHES_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CREGIONBRANCHES() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, REGIONBRANCHES_BES, REGIONBRANCHES_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, REGIONBRANCHES_BES, (int)REGIONBRANCHES_ANZ, error_msg);
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
        if ( fkt_nr == 1739 ) return CursorServerCall(1739, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_REGIONBRANCHES & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.STANDORT_LANG);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, REGIONBRANCHES_BES, (int)REGIONBRANCHES_ANZ, error_msg);
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
        CREGIONBRANCHES c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, REGIONBRANCHES_BES, (int)REGIONBRANCHES_ANZ, error_msg);
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

class CREGIONS : public ppDadeVirtual {
public:
    regionsS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<regionsS> lst; // class list

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
                     vector< regionsS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     regionsS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< regionsS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<regionsS>::iterator
                 beginList() { return lst.begin(); }
    vector<regionsS>::iterator
                 endList  () { return lst.end  (); }

    short        GetRegionno() const { return s.REGIONNO; }
    const char*  GetRegionname(ppString & t) const { t = s.REGIONNAME; t.erasespace(ppString::END); return t.c_str(); }
    short        GetRegionbranchno() const { return s.REGIONBRANCHNO; }

    const regionsS &
                 GetStruct() const { return s; }
    void         SetRegionno(short t) { s.REGIONNO = t; }
    void         SetRegionname(const ppString & t) { ppGStrCopy(s.REGIONNAME, t.c_str(), L_REGIONS_REGIONNAME); }
    void         SetRegionbranchno(short t) { s.REGIONBRANCHNO = t; }

    void         SetStruct(const regionsS & t) { s = t; }

    int          SelRegion(int pos = 0) { int ret = UniqueServerCall(1679, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CREGIONS() {
        ::buf_default((void *)&s, REGIONS_BES, REGIONS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CREGIONS() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, REGIONS_BES, REGIONS_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1679 ) return UniqueServerCall(1679, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_REGIONS & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.REGIONNAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, REGIONS_BES, (int)REGIONS_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CVBFILIALEN : public ppDadeVirtual {
public:
    vbfilialenS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<vbfilialenS> lst; // class list

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
                     vector< vbfilialenS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     vbfilialenS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< vbfilialenS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<vbfilialenS>::iterator
                 beginList() { return lst.begin(); }
    vector<vbfilialenS>::iterator
                 endList  () { return lst.end  (); }

    short        GetFilialnr() const { return s.FILIALNR; }
    short        GetVerbundfilialnr() const { return s.VERBUNDFILIALNR; }
    const char*  GetTagestyp(ppString & t) const { t = s.TAGESTYP; t.erasespace(ppString::END); return t.c_str(); }
    long         GetZeitbegin() const { return s.ZEITBEGIN; }
    long         GetZeitende() const { return s.ZEITENDE; }
    short        GetWeekday() const { return s.WEEKDAY; }
    short        GetVbtyp() const { return s.VBTYP; }

    const vbfilialenS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetVerbundfilialnr(short t) { s.VERBUNDFILIALNR = t; }
    void         SetTagestyp(const ppString & t) { ppGStrCopy(s.TAGESTYP, t.c_str(), L_VBFILIALEN_TAGESTYP); }
    void         SetZeitbegin(long t) { s.ZEITBEGIN = t; }
    void         SetZeitende(long t) { s.ZEITENDE = t; }
    void         SetWeekday(short t) { s.WEEKDAY = t; }
    void         SetVbtyp(short t) { s.VBTYP = t; }

    void         SetStruct(const vbfilialenS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelVbFilialen(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1042, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CVBFILIALEN() {
        ::buf_default((void *)&s, VBFILIALEN_BES, VBFILIALEN_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CVBFILIALEN() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, VBFILIALEN_BES, VBFILIALEN_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, VBFILIALEN_BES, (int)VBFILIALEN_ANZ, error_msg);
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
        if ( fkt_nr == 1042 ) return CursorServerCall(1042, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_VBFILIALEN & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.TAGESTYP);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, VBFILIALEN_BES, (int)VBFILIALEN_ANZ, error_msg);
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
        CVBFILIALEN c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, VBFILIALEN_BES, (int)VBFILIALEN_ANZ, error_msg);
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

class CVERBUNDIDF : public ppDadeVirtual {
public:
    verbundidfS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<verbundidfS> lst; // class list

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
                     vector< verbundidfS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     verbundidfS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< verbundidfS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<verbundidfS>::iterator
                 beginList() { return lst.begin(); }
    vector<verbundidfS>::iterator
                 endList  () { return lst.end  (); }

    short        GetFilialnr() const { return s.FILIALNR; }
    long         GetBganr_ek() const { return s.BGANR_EK; }

    const verbundidfS &
                 GetStruct() const { return s; }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetBganr_ek(long t) { s.BGANR_EK = t; }

    void         SetStruct(const verbundidfS & t) { s = t; }

    int          SelVBIdf(int pos = 0) { int ret = UniqueServerCall(1558, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CVERBUNDIDF() {
        ::buf_default((void *)&s, VERBUNDIDF_BES, VERBUNDIDF_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CVERBUNDIDF() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, VERBUNDIDF_BES, VERBUNDIDF_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1558 ) return UniqueServerCall(1558, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_VERBUNDIDF & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, VERBUNDIDF_BES, (int)VERBUNDIDF_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CZIELFILIALEN : public ppDadeVirtual {
public:
    zielfilialenS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<zielfilialenS> lst; // class list

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
                     vector< zielfilialenS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     zielfilialenS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< zielfilialenS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<zielfilialenS>::iterator
                 beginList() { return lst.begin(); }
    vector<zielfilialenS>::iterator
                 endList  () { return lst.end  (); }

    short        GetFilialnr() const { return s.FILIALNR; }
    const char*  GetRechner_name(ppString & t) const { t = s.RECHNER_NAME; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetName(ppString & t) const { t = s.NAME; t.erasespace(ppString::END); return t.c_str(); }

    const zielfilialenS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetRechner_name(const ppString & t) { ppGStrCopy(s.RECHNER_NAME, t.c_str(), L_ZIELFILIALEN_RECHNER_NAME); }
    void         SetName(const ppString & t) { ppGStrCopy(s.NAME, t.c_str(), L_ZIELFILIALEN_NAME); }

    void         SetStruct(const zielfilialenS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1450, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CZIELFILIALEN() {
        ::buf_default((void *)&s, ZIELFILIALEN_BES, ZIELFILIALEN_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CZIELFILIALEN() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, ZIELFILIALEN_BES, ZIELFILIALEN_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, ZIELFILIALEN_BES, (int)ZIELFILIALEN_ANZ, error_msg);
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
        if ( fkt_nr == 1450 ) return CursorServerCall(1450, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_ZIELFILIALEN & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.RECHNER_NAME);
        ppGStripLast(d.NAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, ZIELFILIALEN_BES, (int)ZIELFILIALEN_ANZ, error_msg);
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
        CZIELFILIALEN c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, ZIELFILIALEN_BES, (int)ZIELFILIALEN_ANZ, error_msg);
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

class CFILIALPARTNER : public ppDadeVirtual {
public:
    filialpartnerS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<filialpartnerS> lst; // class list

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
                     vector< filialpartnerS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     filialpartnerS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< filialpartnerS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<filialpartnerS>::iterator
                 beginList() { return lst.begin(); }
    vector<filialpartnerS>::iterator
                 endList  () { return lst.end  (); }

    short        GetFilialnr() const { return s.FILIALNR; }
    const char*  GetName(ppString & t) const { t = s.NAME; t.erasespace(ppString::END); return t.c_str(); }
    long         GetBganr() const { return s.BGANR; }
    long         GetSupport_from() const { return s.SUPPORT_FROM; }
    long         GetSupport_until() const { return s.SUPPORT_UNTIL; }
    const char*  GetRechner_name(ppString & t) const { t = s.RECHNER_NAME; t.erasespace(ppString::END); return t.c_str(); }

    const filialpartnerS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetName(const ppString & t) { ppGStrCopy(s.NAME, t.c_str(), L_FILIALPARTNER_NAME); }
    void         SetBganr(long t) { s.BGANR = t; }
    void         SetSupport_from(long t) { s.SUPPORT_FROM = t; }
    void         SetSupport_until(long t) { s.SUPPORT_UNTIL = t; }
    void         SetRechner_name(const ppString & t) { ppGStrCopy(s.RECHNER_NAME, t.c_str(), L_FILIALPARTNER_RECHNER_NAME); }

    void         SetStruct(const filialpartnerS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          Delete(int pos = 0) { return UniqueServerCall(1014, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1016, pos); Strip(s); return ret; }
    int          Sel(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1013, FetchRel, pos); return ret; }
    int          SelSupportTime(int pos = 0) { int ret = UniqueServerCall(1022, pos); Strip(s); return ret; }
    int          Update(int pos = 0) { int ret = UniqueServerCall(1015, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CFILIALPARTNER() {
        ::buf_default((void *)&s, FILIALPARTNER_BES, FILIALPARTNER_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CFILIALPARTNER() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, FILIALPARTNER_BES, FILIALPARTNER_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, FILIALPARTNER_BES, (int)FILIALPARTNER_ANZ, error_msg);
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
        if ( fkt_nr == 1014 ) return UniqueServerCall(1014, pos);
        if ( fkt_nr == 1016 ) return UniqueServerCall(1016, pos);
        if ( fkt_nr == 1013 ) return CursorServerCall(1013, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1022 ) return UniqueServerCall(1022, pos);
        if ( fkt_nr == 1015 ) return UniqueServerCall(1015, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_FILIALPARTNER & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.NAME);
        ppGStripLast(d.RECHNER_NAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, FILIALPARTNER_BES, (int)FILIALPARTNER_ANZ, error_msg);
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
        CFILIALPARTNER c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, FILIALPARTNER_BES, (int)FILIALPARTNER_ANZ, error_msg);
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

class CFILIALZEITEN : public ppDadeVirtual {
public:
    filialzeitenS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<filialzeitenS> lst; // class list

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
                     vector< filialzeitenS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     filialzeitenS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< filialzeitenS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<filialzeitenS>::iterator
                 beginList() { return lst.begin(); }
    vector<filialzeitenS>::iterator
                 endList  () { return lst.end  (); }

    short        GetFilialnr() const { return s.FILIALNR; }
    long         GetClosed_from() const { return s.CLOSED_FROM; }
    long         GetClosed_until() const { return s.CLOSED_UNTIL; }

    const filialzeitenS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetClosed_from(long t) { s.CLOSED_FROM = t; }
    void         SetClosed_until(long t) { s.CLOSED_UNTIL = t; }

    void         SetStruct(const filialzeitenS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelZeiten(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1019, FetchRel, pos); return ret; }
    int          UpdateZeiten(int pos = 0) { int ret = UniqueServerCall(1021, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CFILIALZEITEN() {
        ::buf_default((void *)&s, FILIALZEITEN_BES, FILIALZEITEN_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CFILIALZEITEN() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, FILIALZEITEN_BES, FILIALZEITEN_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, FILIALZEITEN_BES, (int)FILIALZEITEN_ANZ, error_msg);
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
        if ( fkt_nr == 1019 ) return CursorServerCall(1019, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1021 ) return UniqueServerCall(1021, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_FILIALZEITEN & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, FILIALZEITEN_BES, (int)FILIALZEITEN_ANZ, error_msg);
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
        CFILIALZEITEN c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, FILIALZEITEN_BES, (int)FILIALZEITEN_ANZ, error_msg);
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
