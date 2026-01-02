#ifndef __PP_MSV3_H_
#define __PP_MSV3_H_

/******************************************************************************/
/* c:\git\pharmos.outbound.csc_core_applications\dev\src\aapserv\MSV3 *********/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of MSV3CSTINFO ***********************************************/

#define L_MSV3CSTINFO_BRANCHNO 6
#define L_MSV3CSTINFO_CUSTOMERNO 11
#define L_MSV3CSTINFO_MSV3INFODESCRIPTION 254
#define L_MSV3CSTINFO_MSV3CSTINFOVALUE 254

/* Length-Define of MSV3EINSTELLUNGEN *****************************************/

#define L_MSV3EINSTELLUNGEN_SKDAUFTRAGZUSAMMEN 1
#define L_MSV3EINSTELLUNGEN_SKDAUFTRAGZURUECK 1
#define L_MSV3EINSTELLUNGEN_VERTRIEBSZENTRUMNR 6
#define L_MSV3EINSTELLUNGEN_KUNDENNR 11
#define L_MSV3EINSTELLUNGEN_XMLINFOLEVEL 1
#define L_MSV3EINSTELLUNGEN_SKDNOCLOSEDEFVB 1
#define L_MSV3EINSTELLUNGEN_SKDNOSUB 1

/* Length-Define of MSV3INFO **************************************************/

#define L_MSV3INFO_KDAUFTRAGART 2
#define L_MSV3INFO_VERTRIEBSZENTRUMNR 6
#define L_MSV3INFO_KUNDENNR 11
#define L_MSV3INFO_MSV3VEREINBART 6
#define L_MSV3INFO_FREIEKENNUNGEN 6

/* Length-Define of MSV3ORDERINFO *********************************************/

#define L_MSV3ORDERINFO_KDAUFTRAGNR 11
#define L_MSV3ORDERINFO_ORIGINDEVICE 20
#define L_MSV3ORDERINFO_SENDID 11
#define L_MSV3ORDERINFO_DATUM 11
#define L_MSV3ORDERINFO_TOURID 6
#define L_MSV3ORDERINFO_WEEKDAY 6
#define L_MSV3ORDERINFO_TOTIME 11
#define L_MSV3ORDERINFO_MAINTIME 11
#define L_MSV3ORDERINFO_ANZPOS 11
#define L_MSV3ORDERINFO_ZEIT_VON 11
#define L_MSV3ORDERINFO_VERTRIEBSZENTRUMNR 6
#define L_MSV3ORDERINFO_KUNDENNR 11
#define L_MSV3ORDERINFO_ORDERLABEL 40
#define L_MSV3ORDERINFO_BFTOUR 6
#define L_MSV3ORDERINFO_POSTRANSFERED 11

/* Length-Define of MSV3TOURINFO **********************************************/

#define L_MSV3TOURINFO_CUSTOMERNO 11
#define L_MSV3TOURINFO_TOURID 6
#define L_MSV3TOURINFO_BRANCHNO 6
#define L_MSV3TOURINFO_WEEKDAY 6
#define L_MSV3TOURINFO_TOTIME 11
#define L_MSV3TOURINFO_ISTVERBUNDTOUR 1
#define L_MSV3TOURINFO_MAINTIME 11
#define L_MSV3TOURINFO_ISBTM 6
#define L_MSV3TOURINFO_ISKK 6
#define L_MSV3TOURINFO_ISK08 6
#define L_MSV3TOURINFO_ISK20 6
#define L_MSV3TOURINFO_RETURNSTOUR 6

/* SqlDefine of MSV3CSTINFO ***************************************************/


#define MSV3CSTINFO_PLISTE \
        "MSV3CSTINFO.BRANCHNO,"\
        "MSV3CSTINFO.CUSTOMERNO,"\
        "MSV3CSTINFOTYPE.MSV3INFODESCRIPTION,"\
        "MSV3CSTINFO.MSV3CSTINFOVALUE"

/* SqlDefine of MSV3EINSTELLUNGEN *********************************************/


#define MSV3EINSTELLUNGEN_PLISTE \
        "KUNDESCHALTER.SKDAUFTRAGZUSAMMEN,"\
        "KUNDESCHALTER.SKDAUFTRAGZURUECK,"\
        "KUNDE.VERTRIEBSZENTRUMNR,"\
        "KUNDE.KUNDENNR,"\
        "KUNDE.XMLINFOLEVEL,"\
        "KUNDESCHALTER.SKDNOCLOSEDEFVB,"\
        "KUNDESCHALTER.SKDNOSUB"

/* SqlDefine of MSV3INFO ******************************************************/


#define MSV3INFO_PLISTE \
        "KDAUFTRAGART.KDAUFTRAGART,"\
        "KUNDESCHALTER.VERTRIEBSZENTRUMNR,"\
        "KUNDESCHALTER.KUNDENNR,"\
        "AADUMMY.MSV3VEREINBART,"\
        "AADUMMY.FREIEKENNUNGEN"

/* SqlDefine of MSV3ORDERINFO *************************************************/


#define MSV3ORDERINFO_PLISTE \
        "KDAUFTRAG.KDAUFTRAGNR,"\
        "OEORIGINTYPES.ORIGINDEVICE,"\
        "KDAUFTRAGPOSEREIGNIS.SENDID,"\
        "AADUMMY.DATUM,"\
        "KDAUFTRAG.TOURID,"\
        "ORDERPERIOD.WEEKDAY,"\
        "ORDERPERIODTIME.TOTIME,"\
        "ORDERPERIODTIME.MAINTIME,"\
        "KDAUFTRAG.ANZPOS,"\
        "AADUMMY.ZEIT_VON,"\
        "KDAUFTRAG.VERTRIEBSZENTRUMNR,"\
        "KDAUFTRAG.KUNDENNR,"\
        "KDAUFTRAG.ORDERLABEL,"\
        "AADUMMY.BFTOUR,"\
        "AADUMMY.POSTRANSFERED"

/* SqlDefine of MSV3TOURINFO **************************************************/


#define MSV3TOURINFO_PLISTE \
        "ORDERPERIOD.CUSTOMERNO,"\
        "ORDERPERIOD.TOURID,"\
        "ORDERPERIOD.BRANCHNO,"\
        "ORDERPERIOD.WEEKDAY,"\
        "ORDERPERIODTIME.TOTIME,"\
        "TOURPLANTAG.ISTVERBUNDTOUR,"\
        "ORDERPERIODTIME.MAINTIME,"\
        "TOURPLANTAG.ISBTM,"\
        "TOURPLANTAG.ISKK,"\
        "TOURPLANTAG.ISK08,"\
        "TOURPLANTAG.ISK20,"\
        "TOURPLANTAG.RETURNSTOUR"

/* SqlDefine of MSV3CSTINFO ***************************************************/


#define MSV3CSTINFO_UPDLISTE \
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "MSV3INFODESCRIPTION=?,"\
        "MSV3CSTINFOVALUE=?"
/* SqlDefine of MSV3EINSTELLUNGEN *********************************************/


#define MSV3EINSTELLUNGEN_UPDLISTE \
        "SKDAUFTRAGZUSAMMEN=?,"\
        "SKDAUFTRAGZURUECK=?,"\
        "VERTRIEBSZENTRUMNR=?,"\
        "KUNDENNR=?,"\
        "XMLINFOLEVEL=?,"\
        "SKDNOCLOSEDEFVB=?,"\
        "SKDNOSUB=?"
/* SqlDefine of MSV3INFO ******************************************************/


#define MSV3INFO_UPDLISTE \
        "KDAUFTRAGART=?,"\
        "VERTRIEBSZENTRUMNR=?,"\
        "KUNDENNR=?,"\
        "MSV3VEREINBART=?,"\
        "FREIEKENNUNGEN=?"
/* SqlDefine of MSV3ORDERINFO *************************************************/


#define MSV3ORDERINFO_UPDLISTE \
        "KDAUFTRAGNR=?,"\
        "ORIGINDEVICE=?,"\
        "SENDID=?,"\
        "DATUM=?,"\
        "TOURID=?,"\
        "WEEKDAY=?,"\
        "TOTIME=?,"\
        "MAINTIME=?,"\
        "ANZPOS=?,"\
        "ZEIT_VON=?,"\
        "VERTRIEBSZENTRUMNR=?,"\
        "KUNDENNR=?,"\
        "ORDERLABEL=?,"\
        "BFTOUR=?,"\
        "POSTRANSFERED=?"
/* SqlDefine of MSV3TOURINFO **************************************************/


#define MSV3TOURINFO_UPDLISTE \
        "CUSTOMERNO=?,"\
        "TOURID=?,"\
        "BRANCHNO=?,"\
        "WEEKDAY=?,"\
        "TOTIME=?,"\
        "ISTVERBUNDTOUR=?,"\
        "MAINTIME=?,"\
        "ISBTM=?,"\
        "ISKK=?,"\
        "ISK08=?,"\
        "ISK20=?,"\
        "RETURNSTOUR=?"
/* SqlMacros-Define of MSV3CSTINFO ********************************************/

#define MSV3CSTINFO_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->MSV3INFODESCRIPTION,\
        :x->MSV3CSTINFOVALUE
#define MSV3CSTINFO_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->MSV3INFODESCRIPTION,\
        :x->MSV3CSTINFOVALUE

/* SqlMacros-Define of MSV3EINSTELLUNGEN **************************************/

#define MSV3EINSTELLUNGEN_ZEIGER(x) \
        :x->SKDAUFTRAGZUSAMMEN,\
        :x->SKDAUFTRAGZURUECK,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->XMLINFOLEVEL,\
        :x->SKDNOCLOSEDEFVB,\
        :x->SKDNOSUB
#define MSV3EINSTELLUNGEN_ZEIGERSEL(x) \
        :x->SKDAUFTRAGZUSAMMEN,\
        :x->SKDAUFTRAGZURUECK,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->XMLINFOLEVEL,\
        :x->SKDNOCLOSEDEFVB,\
        :x->SKDNOSUB

/* SqlMacros-Define of MSV3INFO ***********************************************/

#define MSV3INFO_ZEIGER(x) \
        :x->KDAUFTRAGART,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->MSV3VEREINBART,\
        :x->FREIEKENNUNGEN
#define MSV3INFO_ZEIGERSEL(x) \
        :x->KDAUFTRAGART,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->MSV3VEREINBART,\
        :x->FREIEKENNUNGEN

/* SqlMacros-Define of MSV3ORDERINFO ******************************************/

#define MSV3ORDERINFO_ZEIGER(x) \
        :x->KDAUFTRAGNR,\
        :x->ORIGINDEVICE,\
        :x->SENDID,\
        :x->DATUM,\
        :x->TOURID,\
        :x->WEEKDAY,\
        :x->TOTIME,\
        :x->MAINTIME,\
        :x->ANZPOS,\
        :x->ZEIT_VON,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->ORDERLABEL,\
        :x->BFTOUR,\
        :x->POSTRANSFERED
#define MSV3ORDERINFO_ZEIGERSEL(x) \
        :x->KDAUFTRAGNR,\
        :x->ORIGINDEVICE,\
        :x->SENDID,\
        :x->DATUM,\
        :x->TOURID,\
        :x->WEEKDAY,\
        :x->TOTIME,\
        :x->MAINTIME,\
        :x->ANZPOS,\
        :x->ZEIT_VON,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->ORDERLABEL,\
        :x->BFTOUR,\
        :x->POSTRANSFERED

/* SqlMacros-Define of MSV3TOURINFO *******************************************/

#define MSV3TOURINFO_ZEIGER(x) \
        :x->CUSTOMERNO,\
        :x->TOURID,\
        :x->BRANCHNO,\
        :x->WEEKDAY,\
        :x->TOTIME,\
        :x->ISTVERBUNDTOUR,\
        :x->MAINTIME,\
        :x->ISBTM,\
        :x->ISKK,\
        :x->ISK08,\
        :x->ISK20,\
        :x->RETURNSTOUR
#define MSV3TOURINFO_ZEIGERSEL(x) \
        :x->CUSTOMERNO,\
        :x->TOURID,\
        :x->BRANCHNO,\
        :x->WEEKDAY,\
        :x->TOTIME,\
        :x->ISTVERBUNDTOUR,\
        :x->MAINTIME,\
        :x->ISBTM,\
        :x->ISKK,\
        :x->ISK08,\
        :x->ISK20,\
        :x->RETURNSTOUR

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define MSV3CSTINFO_H
#define MSV3CSTINFO_ANZ ( sizeof(MSV3CSTINFO_BES) / sizeof(struct buf_desc) )
#define MSV3EINSTELLUNGEN_H
#define MSV3EINSTELLUNGEN_ANZ ( sizeof(MSV3EINSTELLUNGEN_BES) / sizeof(struct buf_desc) )
#define MSV3INFO_H
#define MSV3INFO_ANZ ( sizeof(MSV3INFO_BES) / sizeof(struct buf_desc) )
#define MSV3ORDERINFO_H
#define MSV3ORDERINFO_ANZ ( sizeof(MSV3ORDERINFO_BES) / sizeof(struct buf_desc) )
#define MSV3TOURINFO_H
#define MSV3TOURINFO_ANZ ( sizeof(MSV3TOURINFO_BES) / sizeof(struct buf_desc) )
#endif

#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of MSV3CSTINFO *********************************************/

#ifndef TRANSCLASS
typedef struct N_MSV3CSTINFO {
    short BRANCHNO;
    long CUSTOMERNO;
    char MSV3INFODESCRIPTION[255];
    char MSV3CSTINFOVALUE[255];
    long FETCH_REL;
} msv3cstinfoS;
#else /* TRANSCLASS */
typedef struct N_MSV3CSTINFO {
    short BRANCHNO;
    long CUSTOMERNO;
    char MSV3INFODESCRIPTION[255];
    char MSV3CSTINFOVALUE[255];
    long FETCH_REL;
    bool operator == (const N_MSV3CSTINFO& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            CUSTOMERNO == right.CUSTOMERNO &&
            !strcmp(MSV3INFODESCRIPTION, right.MSV3INFODESCRIPTION) &&
            !strcmp(MSV3CSTINFOVALUE, right.MSV3CSTINFOVALUE)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        CUSTOMERNO = 0;
        strcpy(MSV3INFODESCRIPTION, " " );
        strcpy(MSV3CSTINFOVALUE, " " );
#endif
    }
} msv3cstinfoS;
#endif /* TRANSCLASS */

/* original struct of MSV3EINSTELLUNGEN ***************************************/

#ifndef TRANSCLASS
typedef struct N_MSV3EINSTELLUNGEN {
    char SKDAUFTRAGZUSAMMEN[2];
    char SKDAUFTRAGZURUECK[2];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char XMLINFOLEVEL[2];
    char SKDNOCLOSEDEFVB[2];
    char SKDNOSUB[2];
} msv3einstellungenS;
#else /* TRANSCLASS */
typedef struct N_MSV3EINSTELLUNGEN {
    char SKDAUFTRAGZUSAMMEN[2];
    char SKDAUFTRAGZURUECK[2];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char XMLINFOLEVEL[2];
    char SKDNOCLOSEDEFVB[2];
    char SKDNOSUB[2];

    bool operator == (const N_MSV3EINSTELLUNGEN& right) const {
        return (
            !strcmp(SKDAUFTRAGZUSAMMEN, right.SKDAUFTRAGZUSAMMEN) &&
            !strcmp(SKDAUFTRAGZURUECK, right.SKDAUFTRAGZURUECK) &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            !strcmp(XMLINFOLEVEL, right.XMLINFOLEVEL) &&
            !strcmp(SKDNOCLOSEDEFVB, right.SKDNOCLOSEDEFVB) &&
            !strcmp(SKDNOSUB, right.SKDNOSUB)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        strcpy(SKDAUFTRAGZUSAMMEN, " " );
        strcpy(SKDAUFTRAGZURUECK, " " );
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        strcpy(XMLINFOLEVEL, " " );
        strcpy(SKDNOCLOSEDEFVB, " " );
        strcpy(SKDNOSUB, " " );
#endif
    }
} msv3einstellungenS;
#endif /* TRANSCLASS */

/* original struct of MSV3INFO ************************************************/

#ifndef TRANSCLASS
typedef struct N_MSV3INFO {
    char KDAUFTRAGART[3];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    short MSV3VEREINBART;
    short FREIEKENNUNGEN;
    long FETCH_REL;
} msv3infoS;
#else /* TRANSCLASS */
typedef struct N_MSV3INFO {
    char KDAUFTRAGART[3];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    short MSV3VEREINBART;
    short FREIEKENNUNGEN;
    long FETCH_REL;
    bool operator == (const N_MSV3INFO& right) const {
        return (
            !strcmp(KDAUFTRAGART, right.KDAUFTRAGART) &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            MSV3VEREINBART == right.MSV3VEREINBART &&
            FREIEKENNUNGEN == right.FREIEKENNUNGEN
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        strcpy(KDAUFTRAGART, " " );
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        MSV3VEREINBART = 0;
        FREIEKENNUNGEN = 0;
#endif
    }
} msv3infoS;
#endif /* TRANSCLASS */

/* original struct of MSV3ORDERINFO *******************************************/

#ifndef TRANSCLASS
typedef struct N_MSV3ORDERINFO {
    long KDAUFTRAGNR;
    char ORIGINDEVICE[21];
    long SENDID;
    long DATUM;
    char TOURID[7];
    short WEEKDAY;
    long TOTIME;
    long MAINTIME;
    long ANZPOS;
    long ZEIT_VON;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char ORDERLABEL[41];
    char BFTOUR[7];
    long POSTRANSFERED;
    long FETCH_REL;
} msv3orderinfoS;
#else /* TRANSCLASS */
typedef struct N_MSV3ORDERINFO {
    long KDAUFTRAGNR;
    char ORIGINDEVICE[21];
    long SENDID;
    long DATUM;
    char TOURID[7];
    short WEEKDAY;
    long TOTIME;
    long MAINTIME;
    long ANZPOS;
    long ZEIT_VON;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char ORDERLABEL[41];
    char BFTOUR[7];
    long POSTRANSFERED;
    long FETCH_REL;
    bool operator == (const N_MSV3ORDERINFO& right) const {
        return (
            KDAUFTRAGNR == right.KDAUFTRAGNR &&
            !strcmp(ORIGINDEVICE, right.ORIGINDEVICE) &&
            SENDID == right.SENDID &&
            DATUM == right.DATUM &&
            !strcmp(TOURID, right.TOURID) &&
            WEEKDAY == right.WEEKDAY &&
            TOTIME == right.TOTIME &&
            MAINTIME == right.MAINTIME &&
            ANZPOS == right.ANZPOS &&
            ZEIT_VON == right.ZEIT_VON &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            !strcmp(ORDERLABEL, right.ORDERLABEL) &&
            !strcmp(BFTOUR, right.BFTOUR) &&
            POSTRANSFERED == right.POSTRANSFERED
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        KDAUFTRAGNR = 0;
        strcpy(ORIGINDEVICE, " " );
        SENDID = 0;
        DATUM = 0;
        strcpy(TOURID, " " );
        WEEKDAY = 0;
        TOTIME = 0;
        MAINTIME = 0;
        ANZPOS = 0;
        ZEIT_VON = 0;
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        strcpy(ORDERLABEL, " " );
        strcpy(BFTOUR, " " );
        POSTRANSFERED = 0;
#endif
    }
} msv3orderinfoS;
#endif /* TRANSCLASS */

/* original struct of MSV3TOURINFO ********************************************/

#ifndef TRANSCLASS
typedef struct N_MSV3TOURINFO {
    long CUSTOMERNO;
    char TOURID[7];
    short BRANCHNO;
    short WEEKDAY;
    long TOTIME;
    char ISTVERBUNDTOUR[2];
    long MAINTIME;
    short ISBTM;
    short ISKK;
    short ISK08;
    short ISK20;
    short RETURNSTOUR;
    long FETCH_REL;
} msv3tourinfoS;
#else /* TRANSCLASS */
typedef struct N_MSV3TOURINFO {
    long CUSTOMERNO;
    char TOURID[7];
    short BRANCHNO;
    short WEEKDAY;
    long TOTIME;
    char ISTVERBUNDTOUR[2];
    long MAINTIME;
    short ISBTM;
    short ISKK;
    short ISK08;
    short ISK20;
    short RETURNSTOUR;
    long FETCH_REL;
    bool operator == (const N_MSV3TOURINFO& right) const {
        return (
            CUSTOMERNO == right.CUSTOMERNO &&
            !strcmp(TOURID, right.TOURID) &&
            BRANCHNO == right.BRANCHNO &&
            WEEKDAY == right.WEEKDAY &&
            TOTIME == right.TOTIME &&
            !strcmp(ISTVERBUNDTOUR, right.ISTVERBUNDTOUR) &&
            MAINTIME == right.MAINTIME &&
            ISBTM == right.ISBTM &&
            ISKK == right.ISKK &&
            ISK08 == right.ISK08 &&
            ISK20 == right.ISK20 &&
            RETURNSTOUR == right.RETURNSTOUR
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        CUSTOMERNO = 0;
        strcpy(TOURID, " " );
        BRANCHNO = 0;
        WEEKDAY = 0;
        TOTIME = 0;
        strcpy(ISTVERBUNDTOUR, " " );
        MAINTIME = 0;
        ISBTM = 0;
        ISKK = 0;
        ISK08 = 0;
        ISK20 = 0;
        RETURNSTOUR = 0;
#endif
    }
} msv3tourinfoS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of MSV3CSTINFO *********************************/

struct C_MSV3CSTINFO {
    short BRANCHNO;
    long CUSTOMERNO;
    char MSV3INFODESCRIPTION[255];
    char MSV3CSTINFOVALUE[255];
    long FETCH_REL;
};
/* Structur with real chartype of MSV3EINSTELLUNGEN ***************************/

struct C_MSV3EINSTELLUNGEN {
    char SKDAUFTRAGZUSAMMEN;
    char SKDAUFTRAGZURUECK;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char XMLINFOLEVEL;
    char SKDNOCLOSEDEFVB;
    char SKDNOSUB;
};
/* Structur with real chartype of MSV3INFO ************************************/

struct C_MSV3INFO {
    char KDAUFTRAGART[3];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    short MSV3VEREINBART;
    short FREIEKENNUNGEN;
    long FETCH_REL;
};
/* Structur with real chartype of MSV3ORDERINFO *******************************/

struct C_MSV3ORDERINFO {
    long KDAUFTRAGNR;
    char ORIGINDEVICE[21];
    long SENDID;
    long DATUM;
    char TOURID[7];
    short WEEKDAY;
    long TOTIME;
    long MAINTIME;
    long ANZPOS;
    long ZEIT_VON;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char ORDERLABEL[41];
    char BFTOUR[7];
    long POSTRANSFERED;
    long FETCH_REL;
};
/* Structur with real chartype of MSV3TOURINFO ********************************/

struct C_MSV3TOURINFO {
    long CUSTOMERNO;
    char TOURID[7];
    short BRANCHNO;
    short WEEKDAY;
    long TOTIME;
    char ISTVERBUNDTOUR;
    long MAINTIME;
    short ISBTM;
    short ISKK;
    short ISK08;
    short ISK20;
    short RETURNSTOUR;
    long FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of MSV3CSTINFO *******************************/

struct I_MSV3CSTINFO {
    short BRANCHNO;
    short CUSTOMERNO;
    short MSV3INFODESCRIPTION;
    short MSV3CSTINFOVALUE;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of MSV3EINSTELLUNGEN *************************/

struct I_MSV3EINSTELLUNGEN {
    short SKDAUFTRAGZUSAMMEN;
    short SKDAUFTRAGZURUECK;
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short XMLINFOLEVEL;
    short SKDNOCLOSEDEFVB;
    short SKDNOSUB;
};
/* Sizetype  Structur (buf_desc) of MSV3INFO **********************************/

struct I_MSV3INFO {
    short KDAUFTRAGART;
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short MSV3VEREINBART;
    short FREIEKENNUNGEN;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of MSV3ORDERINFO *****************************/

struct I_MSV3ORDERINFO {
    short KDAUFTRAGNR;
    short ORIGINDEVICE;
    short SENDID;
    short DATUM;
    short TOURID;
    short WEEKDAY;
    short TOTIME;
    short MAINTIME;
    short ANZPOS;
    short ZEIT_VON;
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short ORDERLABEL;
    short BFTOUR;
    short POSTRANSFERED;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of MSV3TOURINFO ******************************/

struct I_MSV3TOURINFO {
    short CUSTOMERNO;
    short TOURID;
    short BRANCHNO;
    short WEEKDAY;
    short TOTIME;
    short ISTVERBUNDTOUR;
    short MAINTIME;
    short ISBTM;
    short ISKK;
    short ISK08;
    short ISK20;
    short RETURNSTOUR;
    short FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of MSV3CSTINFO *****************************************/

#if defined (BUF_DESC)
static struct buf_desc MSV3CSTINFO_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 254, 0 },
   { TYP_C, 254, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MSV3CSTINFO_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 254, 0 },
   { TYP_C, 254, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of MSV3EINSTELLUNGEN ***********************************/

#if defined (BUF_DESC)
static struct buf_desc MSV3EINSTELLUNGEN_BES [] = {
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MSV3EINSTELLUNGEN_BES [] = {
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
};
#endif

/* Structur (buf_desc) of MSV3INFO ********************************************/

#if defined (BUF_DESC)
static struct buf_desc MSV3INFO_BES [] = {
   { TYP_C, 2, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MSV3INFO_BES [] = {
   { TYP_C, 2, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of MSV3ORDERINFO ***************************************/

#if defined (BUF_DESC)
static struct buf_desc MSV3ORDERINFO_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 20, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 40, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MSV3ORDERINFO_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 20, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 40, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of MSV3TOURINFO ****************************************/

#if defined (BUF_DESC)
static struct buf_desc MSV3TOURINFO_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MSV3TOURINFO_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* FunctionNumber-Define of MSV3CstInfo ***************************************/

#define MSV3CSTINFO_SELCSTINFO 1744

/* FunctionNumber-Define of MSV3Einstellungen *********************************/

#define MSV3EINSTELLUNGEN_SELADJUSTMENTS 1742

/* FunctionNumber-Define of MSV3Info ******************************************/

#define MSV3INFO_SELMSV3 1740

/* FunctionNumber-Define of MSV3OrderInfo *************************************/

#define MSV3ORDERINFO_SELMSV3ORDERS 1741

/* FunctionNumber-Define of MSV3TourInfo **************************************/

#define MSV3TOURINFO_SELBFTODAY 1743

#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of MSV3CstInfo ***********************************/

#define SelCstInfo 1744

/* Old-FunctionNumber-Define of MSV3Einstellungen *****************************/

#define SelAdjustments 1742

/* Old-FunctionNumber-Define of MSV3Info **************************************/

#define SelMSV3 1740

/* Old-FunctionNumber-Define of MSV3OrderInfo *********************************/

#define SelMSV3Orders 1741

/* Old-FunctionNumber-Define of MSV3TourInfo **********************************/

#define SelBFToday 1743

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

class CMSV3CSTINFO : public ppDadeVirtual {
public:
    msv3cstinfoS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<msv3cstinfoS> lst; // class list

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
                     vector< msv3cstinfoS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     msv3cstinfoS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< msv3cstinfoS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<msv3cstinfoS>::iterator
                 beginList() { return lst.begin(); }
    vector<msv3cstinfoS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    const char*  GetMsv3infodescription(ppString & t) const { t = s.MSV3INFODESCRIPTION; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetMsv3cstinfovalue(ppString & t) const { t = s.MSV3CSTINFOVALUE; t.erasespace(ppString::END); return t.c_str(); }

    const msv3cstinfoS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetMsv3infodescription(const ppString & t) { ppGStrCopy(s.MSV3INFODESCRIPTION, t.c_str(), L_MSV3CSTINFO_MSV3INFODESCRIPTION); }
    void         SetMsv3cstinfovalue(const ppString & t) { ppGStrCopy(s.MSV3CSTINFOVALUE, t.c_str(), L_MSV3CSTINFO_MSV3CSTINFOVALUE); }

    void         SetStruct(const msv3cstinfoS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelCstInfo(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1744, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMSV3CSTINFO() {
        ::buf_default((void *)&s, MSV3CSTINFO_BES, MSV3CSTINFO_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMSV3CSTINFO() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MSV3CSTINFO_BES, MSV3CSTINFO_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MSV3CSTINFO_BES, (int)MSV3CSTINFO_ANZ, error_msg);
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
        if ( fkt_nr == 1744 ) return CursorServerCall(1744, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MSV3CSTINFO & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.MSV3INFODESCRIPTION);
        ppGStripLast(d.MSV3CSTINFOVALUE);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MSV3CSTINFO_BES, (int)MSV3CSTINFO_ANZ, error_msg);
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
        CMSV3CSTINFO c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MSV3CSTINFO_BES, (int)MSV3CSTINFO_ANZ, error_msg);
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

class CMSV3EINSTELLUNGEN : public ppDadeVirtual {
public:
    msv3einstellungenS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<msv3einstellungenS> lst; // class list

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
                     vector< msv3einstellungenS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     msv3einstellungenS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< msv3einstellungenS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<msv3einstellungenS>::iterator
                 beginList() { return lst.begin(); }
    vector<msv3einstellungenS>::iterator
                 endList  () { return lst.end  (); }

    char         GetSkdauftragzusammen() const { return s.SKDAUFTRAGZUSAMMEN[0]; }
    char         GetSkdauftragzurueck() const { return s.SKDAUFTRAGZURUECK[0]; }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    char         GetXmlinfolevel() const { return s.XMLINFOLEVEL[0]; }
    char         GetSkdnoclosedefvb() const { return s.SKDNOCLOSEDEFVB[0]; }
    char         GetSkdnosub() const { return s.SKDNOSUB[0]; }

    const msv3einstellungenS &
                 GetStruct() const { return s; }
    void         SetSkdauftragzusammen(char t) { s.SKDAUFTRAGZUSAMMEN[0] = t; s.SKDAUFTRAGZUSAMMEN[1] = '\0';}
    void         SetSkdauftragzurueck(char t) { s.SKDAUFTRAGZURUECK[0] = t; s.SKDAUFTRAGZURUECK[1] = '\0';}
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetXmlinfolevel(char t) { s.XMLINFOLEVEL[0] = t; s.XMLINFOLEVEL[1] = '\0';}
    void         SetSkdnoclosedefvb(char t) { s.SKDNOCLOSEDEFVB[0] = t; s.SKDNOCLOSEDEFVB[1] = '\0';}
    void         SetSkdnosub(char t) { s.SKDNOSUB[0] = t; s.SKDNOSUB[1] = '\0';}

    void         SetStruct(const msv3einstellungenS & t) { s = t; }

    int          SelAdjustments(int pos = 0) { int ret = UniqueServerCall(1742, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMSV3EINSTELLUNGEN() {
        ::buf_default((void *)&s, MSV3EINSTELLUNGEN_BES, MSV3EINSTELLUNGEN_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMSV3EINSTELLUNGEN() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MSV3EINSTELLUNGEN_BES, MSV3EINSTELLUNGEN_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1742 ) return UniqueServerCall(1742, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MSV3EINSTELLUNGEN & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MSV3EINSTELLUNGEN_BES, (int)MSV3EINSTELLUNGEN_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CMSV3INFO : public ppDadeVirtual {
public:
    msv3infoS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<msv3infoS> lst; // class list

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
                     vector< msv3infoS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     msv3infoS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< msv3infoS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<msv3infoS>::iterator
                 beginList() { return lst.begin(); }
    vector<msv3infoS>::iterator
                 endList  () { return lst.end  (); }

    const char*  GetKdauftragart(ppString & t) const { t = s.KDAUFTRAGART; t.erasespace(ppString::END); return t.c_str(); }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    short        GetMsv3vereinbart() const { return s.MSV3VEREINBART; }
    short        GetFreiekennungen() const { return s.FREIEKENNUNGEN; }

    const msv3infoS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetKdauftragart(const ppString & t) { ppGStrCopy(s.KDAUFTRAGART, t.c_str(), L_MSV3INFO_KDAUFTRAGART); }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetMsv3vereinbart(short t) { s.MSV3VEREINBART = t; }
    void         SetFreiekennungen(short t) { s.FREIEKENNUNGEN = t; }

    void         SetStruct(const msv3infoS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelMSV3(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1740, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMSV3INFO() {
        ::buf_default((void *)&s, MSV3INFO_BES, MSV3INFO_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMSV3INFO() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MSV3INFO_BES, MSV3INFO_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MSV3INFO_BES, (int)MSV3INFO_ANZ, error_msg);
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
        if ( fkt_nr == 1740 ) return CursorServerCall(1740, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MSV3INFO & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.KDAUFTRAGART);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MSV3INFO_BES, (int)MSV3INFO_ANZ, error_msg);
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
        CMSV3INFO c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MSV3INFO_BES, (int)MSV3INFO_ANZ, error_msg);
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

class CMSV3ORDERINFO : public ppDadeVirtual {
public:
    msv3orderinfoS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<msv3orderinfoS> lst; // class list

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
                     vector< msv3orderinfoS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     msv3orderinfoS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< msv3orderinfoS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<msv3orderinfoS>::iterator
                 beginList() { return lst.begin(); }
    vector<msv3orderinfoS>::iterator
                 endList  () { return lst.end  (); }

    long         GetKdauftragnr() const { return s.KDAUFTRAGNR; }
    const char*  GetOrigindevice(ppString & t) const { t = s.ORIGINDEVICE; t.erasespace(ppString::END); return t.c_str(); }
    long         GetSendid() const { return s.SENDID; }
    long         GetDatum() const { return s.DATUM; }
    const char*  GetTourid(ppString & t) const { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
    short        GetWeekday() const { return s.WEEKDAY; }
    long         GetTotime() const { return s.TOTIME; }
    long         GetMaintime() const { return s.MAINTIME; }
    long         GetAnzpos() const { return s.ANZPOS; }
    long         GetZeit_von() const { return s.ZEIT_VON; }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    const char*  GetOrderlabel(ppString & t) const { t = s.ORDERLABEL; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetBftour(ppString & t) const { t = s.BFTOUR; t.erasespace(ppString::END); return t.c_str(); }
    long         GetPostransfered() const { return s.POSTRANSFERED; }

    const msv3orderinfoS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
    void         SetOrigindevice(const ppString & t) { ppGStrCopy(s.ORIGINDEVICE, t.c_str(), L_MSV3ORDERINFO_ORIGINDEVICE); }
    void         SetSendid(long t) { s.SENDID = t; }
    void         SetDatum(long t) { s.DATUM = t; }
    void         SetTourid(const ppString & t) { ppGStrCopy(s.TOURID, t.c_str(), L_MSV3ORDERINFO_TOURID); }
    void         SetWeekday(short t) { s.WEEKDAY = t; }
    void         SetTotime(long t) { s.TOTIME = t; }
    void         SetMaintime(long t) { s.MAINTIME = t; }
    void         SetAnzpos(long t) { s.ANZPOS = t; }
    void         SetZeit_von(long t) { s.ZEIT_VON = t; }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetOrderlabel(const ppString & t) { ppGStrCopy(s.ORDERLABEL, t.c_str(), L_MSV3ORDERINFO_ORDERLABEL); }
    void         SetBftour(const ppString & t) { ppGStrCopy(s.BFTOUR, t.c_str(), L_MSV3ORDERINFO_BFTOUR); }
    void         SetPostransfered(long t) { s.POSTRANSFERED = t; }

    void         SetStruct(const msv3orderinfoS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelMSV3Orders(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1741, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMSV3ORDERINFO() {
        ::buf_default((void *)&s, MSV3ORDERINFO_BES, MSV3ORDERINFO_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMSV3ORDERINFO() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MSV3ORDERINFO_BES, MSV3ORDERINFO_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MSV3ORDERINFO_BES, (int)MSV3ORDERINFO_ANZ, error_msg);
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
        if ( fkt_nr == 1741 ) return CursorServerCall(1741, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MSV3ORDERINFO & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.ORIGINDEVICE);
        ppGStripLast(d.TOURID);
        ppGStripLast(d.ORDERLABEL);
        ppGStripLast(d.BFTOUR);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MSV3ORDERINFO_BES, (int)MSV3ORDERINFO_ANZ, error_msg);
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
        CMSV3ORDERINFO c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MSV3ORDERINFO_BES, (int)MSV3ORDERINFO_ANZ, error_msg);
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

class CMSV3TOURINFO : public ppDadeVirtual {
public:
    msv3tourinfoS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<msv3tourinfoS> lst; // class list

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
                     vector< msv3tourinfoS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     msv3tourinfoS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< msv3tourinfoS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<msv3tourinfoS>::iterator
                 beginList() { return lst.begin(); }
    vector<msv3tourinfoS>::iterator
                 endList  () { return lst.end  (); }

    long         GetCustomerno() const { return s.CUSTOMERNO; }
    const char*  GetTourid(ppString & t) const { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
    short        GetBranchno() const { return s.BRANCHNO; }
    short        GetWeekday() const { return s.WEEKDAY; }
    long         GetTotime() const { return s.TOTIME; }
    char         GetIstverbundtour() const { return s.ISTVERBUNDTOUR[0]; }
    long         GetMaintime() const { return s.MAINTIME; }
    short        GetIsbtm() const { return s.ISBTM; }
    short        GetIskk() const { return s.ISKK; }
    short        GetIsk08() const { return s.ISK08; }
    short        GetIsk20() const { return s.ISK20; }
    short        GetReturnstour() const { return s.RETURNSTOUR; }

    const msv3tourinfoS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetTourid(const ppString & t) { ppGStrCopy(s.TOURID, t.c_str(), L_MSV3TOURINFO_TOURID); }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetWeekday(short t) { s.WEEKDAY = t; }
    void         SetTotime(long t) { s.TOTIME = t; }
    void         SetIstverbundtour(char t) { s.ISTVERBUNDTOUR[0] = t; s.ISTVERBUNDTOUR[1] = '\0';}
    void         SetMaintime(long t) { s.MAINTIME = t; }
    void         SetIsbtm(short t) { s.ISBTM = t; }
    void         SetIskk(short t) { s.ISKK = t; }
    void         SetIsk08(short t) { s.ISK08 = t; }
    void         SetIsk20(short t) { s.ISK20 = t; }
    void         SetReturnstour(short t) { s.RETURNSTOUR = t; }

    void         SetStruct(const msv3tourinfoS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelBFToday(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1743, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMSV3TOURINFO() {
        ::buf_default((void *)&s, MSV3TOURINFO_BES, MSV3TOURINFO_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMSV3TOURINFO() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MSV3TOURINFO_BES, MSV3TOURINFO_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MSV3TOURINFO_BES, (int)MSV3TOURINFO_ANZ, error_msg);
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
        if ( fkt_nr == 1743 ) return CursorServerCall(1743, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MSV3TOURINFO & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.TOURID);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MSV3TOURINFO_BES, (int)MSV3TOURINFO_ANZ, error_msg);
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
        CMSV3TOURINFO c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MSV3TOURINFO_BES, (int)MSV3TOURINFO_ANZ, error_msg);
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
