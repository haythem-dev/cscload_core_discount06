#ifndef __PP_STATISTICS_H_
#define __PP_STATISTICS_H_

/******************************************************************************/
/* c:\git\pharmos.outbound.csc_core_applications\dev\src\aapserv\Statistics ***/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of ARTIKELKONTOANZ *******************************************/

#define L_ARTIKELKONTOANZ_ZEIT_BIS 11
#define L_ARTIKELKONTOANZ_LFDNR 11
#define L_ARTIKELKONTOANZ_FILIALNR 6
#define L_ARTIKELKONTOANZ_ARTIKEL_NR 11
#define L_ARTIKELKONTOANZ_BEWEGUNGSART 1
#define L_ARTIKELKONTOANZ_MENGE 11
#define L_ARTIKELKONTOANZ_BELEGNR 11
#define L_ARTIKELKONTOANZ_UID 11
#define L_ARTIKELKONTOANZ_IDFNR 11
#define L_ARTIKELKONTOANZ_MENGENEU 11
#define L_ARTIKELKONTOANZ_ZEITUNIX 11
#define L_ARTIKELKONTOANZ_BEWEGUNGSCHLUESSEL 11
#define L_ARTIKELKONTOANZ_STOCKRESERVED 11
#define L_ARTIKELKONTOANZ_MOVETYPE 6

/* Length-Define of AUFWERTHERST **********************************************/

#define L_AUFWERTHERST_KDAUFTRAGNR 11
#define L_AUFWERTHERST_PREISEKAPO 9
#define N_AUFWERTHERST_PREISEKAPO 2
#define L_AUFWERTHERST_HERSTELLER_CODE 5

/* Length-Define of FEIERTAG **************************************************/

#define L_FEIERTAG_MODUS_ALT 6
#define L_FEIERTAG_TAG_ALT 6
#define L_FEIERTAG_FILIALNR 6
#define L_FEIERTAG_MODUS 6
#define L_FEIERTAG_TAG 6
#define L_FEIERTAG_VON_JAHR 6
#define L_FEIERTAG_BIS_JAHR 6
#define L_FEIERTAG_TAGNAME 20

/* Length-Define of LAGERREVISIONANZ ******************************************/

#define L_LAGERREVISIONANZ_FILIALNR 6
#define L_LAGERREVISIONANZ_ARTIKEL_NR 11
#define L_LAGERREVISIONANZ_DATUM 11
#define L_LAGERREVISIONANZ_UHRZEIT 11
#define L_LAGERREVISIONANZ_BESTANDKSC 11
#define L_LAGERREVISIONANZ_BESTANDVSE 11

/* Length-Define of OECUSTOMERCALLS *******************************************/

#define L_OECUSTOMERCALLS_BRANCHNO 6
#define L_OECUSTOMERCALLS_CUSTOMERNO 11
#define L_OECUSTOMERCALLS_CALLDATE 11
#define L_OECUSTOMERCALLS_CALLTIME 11
#define L_OECUSTOMERCALLS_CALLEFFECT 6
#define L_OECUSTOMERCALLS_CSCORDERNO 11

/* Length-Define of OFFENAUFTRAG **********************************************/

#define L_OFFENAUFTRAG_KDAUFTRAGNR 11
#define L_OFFENAUFTRAG_FILIALNR 6
#define L_OFFENAUFTRAG_MENGEBESTELLT 11
#define L_OFFENAUFTRAG_KDAUFTRAGART 2
#define L_OFFENAUFTRAG_MENGENATRA 11
#define L_OFFENAUFTRAG_DATUMAUSLIEFERUNG 11
#define L_OFFENAUFTRAG_ARTIKEL_NR 11
#define L_OFFENAUFTRAG_BESTAND 11
#define L_OFFENAUFTRAG_DARREICHFORM 3
#define L_OFFENAUFTRAG_EINHEIT 9
#define L_OFFENAUFTRAG_ARTIKEL_NAME 30
#define L_OFFENAUFTRAG_HERSTELLER_NR 11

/* Length-Define of RUFSTAT ***************************************************/

#define L_RUFSTAT_DATUM 11
#define L_RUFSTAT_ZEIT_VON 11
#define L_RUFSTAT_ZEIT_BIS 11
#define L_RUFSTAT_ANZ_PLAN 6
#define L_RUFSTAT_ANZ_POSTPONE1 6
#define L_RUFSTAT_ANZ_POSTPONE2 6
#define L_RUFSTAT_ANZ_POSTPONE3 6
#define L_RUFSTAT_ANZ_POSTPONE_MORE 6
#define L_RUFSTAT_ANZ_POSTPONE_TOTAL 6

/* Length-Define of TOURZEIT **************************************************/

#define L_TOURZEIT_IDFNR 11
#define L_TOURZEIT_TOURID 6
#define L_TOURZEIT_VERTRIEBSZENTRUMNR 6

/* SqlDefine of ARTIKELKONTOANZ ***********************************************/


#define ARTIKELKONTOANZ_PLISTE \
        "ARTIKELKONTO.LFDNR,"\
        "ARTIKELKONTO.FILIALNR,"\
        "ARTIKELKONTO.ARTIKEL_NR,"\
        "ARTIKELKONTO.BEWEGUNGSART,"\
        "ARTIKELKONTO.MENGE,"\
        "ARTIKELKONTO.BELEGNR,"\
        "ARTIKELKONTO.UID,"\
        "ARTIKELKONTO.IDFNR,"\
        "ARTIKELKONTO.MENGENEU,"\
        "ARTIKELKONTO.ZEITUNIX,"\
        "ARTIKELKONTO.BEWEGUNGSCHLUESSEL,"\
        "ARTIKELKONTO.STOCKRESERVED,"\
        "ARTIKELKONTO.MOVETYPE"

/* SqlDefine of AUFWERTHERST **************************************************/


#define AUFWERTHERST_PLISTE \
        "KDAUFTRAGPOS.KDAUFTRAGNR,"\
        "KDAUFTRAGPOS.PREISEKAPO,"\
        "ARTIKELZENTRAL.HERSTELLER_CODE"

/* SqlDefine of FEIERTAG ******************************************************/


#define FEIERTAG_PLISTE \
        "FEIERTAG.FILIALNR,"\
        "FEIERTAG.MODUS,"\
        "FEIERTAG.TAG,"\
        "FEIERTAG.VON_JAHR,"\
        "FEIERTAG.BIS_JAHR,"\
        "FEIERTAG.TAGNAME"

/* SqlDefine of LAGERREVISIONANZ **********************************************/


#define LAGERREVISIONANZ_PLISTE \
        "LAGERREVISION.FILIALNR,"\
        "LAGERREVISION.ARTIKEL_NR,"\
        "LAGERREVISION.DATUM,"\
        "LAGERREVISION.UHRZEIT,"\
        "LAGERREVISION.BESTANDKSC,"\
        "LAGERREVISION.BESTANDVSE"

/* SqlDefine of OECUSTOMERCALLS ***********************************************/


#define OECUSTOMERCALLS_PLISTE \
        "OECUSTOMERCALLS.BRANCHNO,"\
        "OECUSTOMERCALLS.CUSTOMERNO,"\
        "OECUSTOMERCALLS.CALLDATE,"\
        "OECUSTOMERCALLS.CALLTIME,"\
        "OECUSTOMERCALLS.CALLEFFECT,"\
        "OECUSTOMERCALLS.CSCORDERNO"

/* SqlDefine of OFFENAUFTRAG **************************************************/


#define OFFENAUFTRAG_PLISTE \
        "KDAUFTRAG.KDAUFTRAGNR,"\
        "KDAUFTRAG.FILIALNR,"\
        "KDAUFTRAGPOS.MENGEBESTELLT,"\
        "KDAUFTRAG.KDAUFTRAGART,"\
        "KDAUFTRAGPOS.MENGENATRA,"\
        "KDAUFTRAG.DATUMAUSLIEFERUNG,"\
        "ARTIKELZENTRAL.ARTIKEL_NR,"\
        "ARTIKELLOKAL.BESTAND,"\
        "ARTIKELZENTRAL.DARREICHFORM,"\
        "ARTIKELZENTRAL.EINHEIT,"\
        "ARTIKELZENTRAL.ARTIKEL_NAME,"\
        "ARTIKELZENTRAL.HERSTELLER_NR"

/* SqlDefine of RUFSTAT *******************************************************/


#define RUFSTAT_PLISTE \
        "AADUMMY.DATUM,"\
        "AADUMMY.ZEIT_VON,"\
        "AADUMMY.ZEIT_BIS,"\
        "AADUMMY.ANZ_PLAN,"\
        "AADUMMY.ANZ_POSTPONE1,"\
        "AADUMMY.ANZ_POSTPONE2,"\
        "AADUMMY.ANZ_POSTPONE3,"\
        "AADUMMY.ANZ_POSTPONE_MORE,"\
        "AADUMMY.ANZ_POSTPONE_TOTAL"

/* SqlDefine of TOURZEIT ******************************************************/


#define TOURZEIT_PLISTE \
        "TOURPLANTAG.IDFNR,"\
        "TOURPLANTAG.TOURID,"\
        "TOURPLANTAG.VERTRIEBSZENTRUMNR"

/* SqlDefine of ARTIKELKONTOANZ ***********************************************/


#define ARTIKELKONTOANZ_UPDLISTE \
        "LFDNR=?,"\
        "FILIALNR=?,"\
        "ARTIKEL_NR=?,"\
        "BEWEGUNGSART=?,"\
        "MENGE=?,"\
        "BELEGNR=?,"\
        "UID=?,"\
        "IDFNR=?,"\
        "MENGENEU=?,"\
        "ZEITUNIX=?,"\
        "BEWEGUNGSCHLUESSEL=?,"\
        "STOCKRESERVED=?,"\
        "MOVETYPE=?"
/* SqlDefine of AUFWERTHERST **************************************************/


#define AUFWERTHERST_UPDLISTE \
        "KDAUFTRAGNR=?,"\
        "PREISEKAPO=?,"\
        "HERSTELLER_CODE=?"
/* SqlDefine of FEIERTAG ******************************************************/


#define FEIERTAG_UPDLISTE \
        "FILIALNR=?,"\
        "MODUS=?,"\
        "TAG=?,"\
        "VON_JAHR=?,"\
        "BIS_JAHR=?,"\
        "TAGNAME=?"
/* SqlDefine of LAGERREVISIONANZ **********************************************/


#define LAGERREVISIONANZ_UPDLISTE \
        "FILIALNR=?,"\
        "ARTIKEL_NR=?,"\
        "DATUM=?,"\
        "UHRZEIT=?,"\
        "BESTANDKSC=?,"\
        "BESTANDVSE=?"
/* SqlDefine of OECUSTOMERCALLS ***********************************************/


#define OECUSTOMERCALLS_UPDLISTE \
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "CALLDATE=?,"\
        "CALLTIME=?,"\
        "CALLEFFECT=?,"\
        "CSCORDERNO=?"
/* SqlDefine of OFFENAUFTRAG **************************************************/


#define OFFENAUFTRAG_UPDLISTE \
        "KDAUFTRAGNR=?,"\
        "FILIALNR=?,"\
        "MENGEBESTELLT=?,"\
        "KDAUFTRAGART=?,"\
        "MENGENATRA=?,"\
        "DATUMAUSLIEFERUNG=?,"\
        "ARTIKEL_NR=?,"\
        "BESTAND=?,"\
        "DARREICHFORM=?,"\
        "EINHEIT=?,"\
        "ARTIKEL_NAME=?,"\
        "HERSTELLER_NR=?"
/* SqlDefine of RUFSTAT *******************************************************/


#define RUFSTAT_UPDLISTE \
        "DATUM=?,"\
        "ZEIT_VON=?,"\
        "ZEIT_BIS=?,"\
        "ANZ_PLAN=?,"\
        "ANZ_POSTPONE1=?,"\
        "ANZ_POSTPONE2=?,"\
        "ANZ_POSTPONE3=?,"\
        "ANZ_POSTPONE_MORE=?,"\
        "ANZ_POSTPONE_TOTAL=?"
/* SqlDefine of TOURZEIT ******************************************************/


#define TOURZEIT_UPDLISTE \
        "IDFNR=?,"\
        "TOURID=?,"\
        "VERTRIEBSZENTRUMNR=?"
/* SqlMacros-Define of ARTIKELKONTOANZ ****************************************/

#define ARTIKELKONTOANZ_ZEIGER(x) \
        :x->LFDNR,\
        :x->FILIALNR,\
        :x->ARTIKEL_NR,\
        :x->BEWEGUNGSART,\
        :x->MENGE,\
        :x->BELEGNR,\
        :x->UID,\
        :x->IDFNR,\
        :x->MENGENEU,\
        :x->ZEITUNIX,\
        :x->BEWEGUNGSCHLUESSEL,\
        :x->STOCKRESERVED,\
        :x->MOVETYPE
#define ARTIKELKONTOANZ_ZEIGERSEL(x) \
        :x->LFDNR,\
        :x->FILIALNR,\
        :x->ARTIKEL_NR,\
        :x->BEWEGUNGSART,\
        :x->MENGE,\
        :x->BELEGNR,\
        :x->UID,\
        :x->IDFNR,\
        :x->MENGENEU,\
        :x->ZEITUNIX,\
        :x->BEWEGUNGSCHLUESSEL,\
        :x->STOCKRESERVED,\
        :x->MOVETYPE

/* SqlMacros-Define of AUFWERTHERST *******************************************/

#define AUFWERTHERST_ZEIGER(x) \
        :x->KDAUFTRAGNR,\
        :x->PREISEKAPO,\
        :x->HERSTELLER_CODE
#define AUFWERTHERST_ZEIGERSEL(x) \
        :x->KDAUFTRAGNR,\
        :x->PREISEKAPO,\
        :x->HERSTELLER_CODE

/* SqlMacros-Define of FEIERTAG ***********************************************/

#define FEIERTAG_ZEIGER(x) \
        :x->FILIALNR,\
        :x->MODUS,\
        :x->TAG,\
        :x->VON_JAHR,\
        :x->BIS_JAHR,\
        :x->TAGNAME
#define FEIERTAG_ZEIGERSEL(x) \
        :x->FILIALNR,\
        :x->MODUS,\
        :x->TAG,\
        :x->VON_JAHR,\
        :x->BIS_JAHR,\
        :x->TAGNAME

/* SqlMacros-Define of LAGERREVISIONANZ ***************************************/

#define LAGERREVISIONANZ_ZEIGER(x) \
        :x->FILIALNR,\
        :x->ARTIKEL_NR,\
        :x->DATUM,\
        :x->UHRZEIT,\
        :x->BESTANDKSC,\
        :x->BESTANDVSE
#define LAGERREVISIONANZ_ZEIGERSEL(x) \
        :x->FILIALNR,\
        :x->ARTIKEL_NR,\
        :x->DATUM,\
        :x->UHRZEIT,\
        :x->BESTANDKSC,\
        :x->BESTANDVSE

/* SqlMacros-Define of OECUSTOMERCALLS ****************************************/

#define OECUSTOMERCALLS_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->CALLDATE,\
        :x->CALLTIME,\
        :x->CALLEFFECT,\
        :x->CSCORDERNO
#define OECUSTOMERCALLS_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->CALLDATE,\
        :x->CALLTIME,\
        :x->CALLEFFECT,\
        :x->CSCORDERNO

/* SqlMacros-Define of OFFENAUFTRAG *******************************************/

#define OFFENAUFTRAG_ZEIGER(x) \
        :x->KDAUFTRAGNR,\
        :x->FILIALNR,\
        :x->MENGEBESTELLT,\
        :x->KDAUFTRAGART,\
        :x->MENGENATRA,\
        :x->DATUMAUSLIEFERUNG,\
        :x->ARTIKEL_NR,\
        :x->BESTAND,\
        :x->DARREICHFORM,\
        :x->EINHEIT,\
        :x->ARTIKEL_NAME,\
        :x->HERSTELLER_NR
#define OFFENAUFTRAG_ZEIGERSEL(x) \
        :x->KDAUFTRAGNR,\
        :x->FILIALNR,\
        :x->MENGEBESTELLT,\
        :x->KDAUFTRAGART,\
        :x->MENGENATRA,\
        :x->DATUMAUSLIEFERUNG,\
        :x->ARTIKEL_NR,\
        :x->BESTAND,\
        :x->DARREICHFORM,\
        :x->EINHEIT,\
        :x->ARTIKEL_NAME,\
        :x->HERSTELLER_NR

/* SqlMacros-Define of RUFSTAT ************************************************/

#define RUFSTAT_ZEIGER(x) \
        :x->DATUM,\
        :x->ZEIT_VON,\
        :x->ZEIT_BIS,\
        :x->ANZ_PLAN,\
        :x->ANZ_POSTPONE1,\
        :x->ANZ_POSTPONE2,\
        :x->ANZ_POSTPONE3,\
        :x->ANZ_POSTPONE_MORE,\
        :x->ANZ_POSTPONE_TOTAL
#define RUFSTAT_ZEIGERSEL(x) \
        :x->DATUM,\
        :x->ZEIT_VON,\
        :x->ZEIT_BIS,\
        :x->ANZ_PLAN,\
        :x->ANZ_POSTPONE1,\
        :x->ANZ_POSTPONE2,\
        :x->ANZ_POSTPONE3,\
        :x->ANZ_POSTPONE_MORE,\
        :x->ANZ_POSTPONE_TOTAL

/* SqlMacros-Define of TOURZEIT ***********************************************/

#define TOURZEIT_ZEIGER(x) \
        :x->IDFNR,\
        :x->TOURID,\
        :x->VERTRIEBSZENTRUMNR
#define TOURZEIT_ZEIGERSEL(x) \
        :x->IDFNR,\
        :x->TOURID,\
        :x->VERTRIEBSZENTRUMNR

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define ARTIKELKONTOANZ_H
#define ARTIKELKONTOANZ_ANZ ( sizeof(ARTIKELKONTOANZ_BES) / sizeof(struct buf_desc) )
#define AUFWERTHERST_H
#define AUFWERTHERST_ANZ ( sizeof(AUFWERTHERST_BES) / sizeof(struct buf_desc) )
#define FEIERTAG_H
#define FEIERTAG_ANZ ( sizeof(FEIERTAG_BES) / sizeof(struct buf_desc) )
#define LAGERREVISIONANZ_H
#define LAGERREVISIONANZ_ANZ ( sizeof(LAGERREVISIONANZ_BES) / sizeof(struct buf_desc) )
#define OECUSTOMERCALLS_H
#define OECUSTOMERCALLS_ANZ ( sizeof(OECUSTOMERCALLS_BES) / sizeof(struct buf_desc) )
#define OFFENAUFTRAG_H
#define OFFENAUFTRAG_ANZ ( sizeof(OFFENAUFTRAG_BES) / sizeof(struct buf_desc) )
#define RUFSTAT_H
#define RUFSTAT_ANZ ( sizeof(RUFSTAT_BES) / sizeof(struct buf_desc) )
#define TOURZEIT_H
#define TOURZEIT_ANZ ( sizeof(TOURZEIT_BES) / sizeof(struct buf_desc) )
#endif

#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of ARTIKELKONTOANZ *****************************************/

#ifndef TRANSCLASS
typedef struct N_ARTIKELKONTOANZ {
    long ZEIT_BIS;
    long LFDNR;
    short FILIALNR;
    long ARTIKEL_NR;
    char BEWEGUNGSART[2];
    long MENGE;
    long BELEGNR;
    long UID;
    long IDFNR;
    long MENGENEU;
    long ZEITUNIX;
    long BEWEGUNGSCHLUESSEL;
    long STOCKRESERVED;
    short MOVETYPE;
    long FETCH_REL;
} artikelkontoanzS;
#else /* TRANSCLASS */
typedef struct N_ARTIKELKONTOANZ {
    long ZEIT_BIS;
    long LFDNR;
    short FILIALNR;
    long ARTIKEL_NR;
    char BEWEGUNGSART[2];
    long MENGE;
    long BELEGNR;
    long UID;
    long IDFNR;
    long MENGENEU;
    long ZEITUNIX;
    long BEWEGUNGSCHLUESSEL;
    long STOCKRESERVED;
    short MOVETYPE;
    long FETCH_REL;
    bool operator == (const N_ARTIKELKONTOANZ& right) const {
        return (
            ZEIT_BIS == right.ZEIT_BIS &&
            LFDNR == right.LFDNR &&
            FILIALNR == right.FILIALNR &&
            ARTIKEL_NR == right.ARTIKEL_NR &&
            !strcmp(BEWEGUNGSART, right.BEWEGUNGSART) &&
            MENGE == right.MENGE &&
            BELEGNR == right.BELEGNR &&
            UID == right.UID &&
            IDFNR == right.IDFNR &&
            MENGENEU == right.MENGENEU &&
            ZEITUNIX == right.ZEITUNIX &&
            BEWEGUNGSCHLUESSEL == right.BEWEGUNGSCHLUESSEL &&
            STOCKRESERVED == right.STOCKRESERVED &&
            MOVETYPE == right.MOVETYPE
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        ZEIT_BIS = 0;
        LFDNR = 0;
        FILIALNR = 0;
        ARTIKEL_NR = 0;
        strcpy(BEWEGUNGSART, " " );
        MENGE = 0;
        BELEGNR = 0;
        UID = 0;
        IDFNR = 0;
        MENGENEU = 0;
        ZEITUNIX = 0;
        BEWEGUNGSCHLUESSEL = 0;
        STOCKRESERVED = 0;
        MOVETYPE = 0;
#endif
    }
} artikelkontoanzS;
#endif /* TRANSCLASS */

/* original struct of AUFWERTHERST ********************************************/

#ifndef TRANSCLASS
typedef struct N_AUFWERTHERST {
    long KDAUFTRAGNR;
    double PREISEKAPO;
    char HERSTELLER_CODE[6];
    long FETCH_REL;
} aufwertherstS;
#else /* TRANSCLASS */
typedef struct N_AUFWERTHERST {
    long KDAUFTRAGNR;
    double PREISEKAPO;
    char HERSTELLER_CODE[6];
    long FETCH_REL;
    bool operator == (const N_AUFWERTHERST& right) const {
        return (
            KDAUFTRAGNR == right.KDAUFTRAGNR &&
            PREISEKAPO == right.PREISEKAPO &&
            !strcmp(HERSTELLER_CODE, right.HERSTELLER_CODE)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        KDAUFTRAGNR = 0;
        PREISEKAPO = 0;
        strcpy(HERSTELLER_CODE, " " );
#endif
    }
} aufwertherstS;
#endif /* TRANSCLASS */

/* original struct of FEIERTAG ************************************************/

#ifndef TRANSCLASS
typedef struct N_FEIERTAG {
    short MODUS_ALT;
    short TAG_ALT;
    short FILIALNR;
    short MODUS;
    short TAG;
    short VON_JAHR;
    short BIS_JAHR;
    char TAGNAME[21];
    long FETCH_REL;
} feiertagS;
#else /* TRANSCLASS */
typedef struct N_FEIERTAG {
    short MODUS_ALT;
    short TAG_ALT;
    short FILIALNR;
    short MODUS;
    short TAG;
    short VON_JAHR;
    short BIS_JAHR;
    char TAGNAME[21];
    long FETCH_REL;
    bool operator == (const N_FEIERTAG& right) const {
        return (
            MODUS_ALT == right.MODUS_ALT &&
            TAG_ALT == right.TAG_ALT &&
            FILIALNR == right.FILIALNR &&
            MODUS == right.MODUS &&
            TAG == right.TAG &&
            VON_JAHR == right.VON_JAHR &&
            BIS_JAHR == right.BIS_JAHR &&
            !strcmp(TAGNAME, right.TAGNAME)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        MODUS_ALT = 0;
        TAG_ALT = 0;
        FILIALNR = 0;
        MODUS = 0;
        TAG = 0;
        VON_JAHR = 0;
        BIS_JAHR = 0;
        strcpy(TAGNAME, " " );
#endif
    }
} feiertagS;
#endif /* TRANSCLASS */

/* original struct of LAGERREVISIONANZ ****************************************/

#ifndef TRANSCLASS
typedef struct N_LAGERREVISIONANZ {
    short FILIALNR;
    long ARTIKEL_NR;
    long DATUM;
    long UHRZEIT;
    long BESTANDKSC;
    long BESTANDVSE;
    long FETCH_REL;
} lagerrevisionanzS;
#else /* TRANSCLASS */
typedef struct N_LAGERREVISIONANZ {
    short FILIALNR;
    long ARTIKEL_NR;
    long DATUM;
    long UHRZEIT;
    long BESTANDKSC;
    long BESTANDVSE;
    long FETCH_REL;
    bool operator == (const N_LAGERREVISIONANZ& right) const {
        return (
            FILIALNR == right.FILIALNR &&
            ARTIKEL_NR == right.ARTIKEL_NR &&
            DATUM == right.DATUM &&
            UHRZEIT == right.UHRZEIT &&
            BESTANDKSC == right.BESTANDKSC &&
            BESTANDVSE == right.BESTANDVSE
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        FILIALNR = 0;
        ARTIKEL_NR = 0;
        DATUM = 0;
        UHRZEIT = 0;
        BESTANDKSC = 0;
        BESTANDVSE = 0;
#endif
    }
} lagerrevisionanzS;
#endif /* TRANSCLASS */

/* original struct of OECUSTOMERCALLS *****************************************/

#ifndef TRANSCLASS
typedef struct N_OECUSTOMERCALLS {
    short BRANCHNO;
    long CUSTOMERNO;
    long CALLDATE;
    long CALLTIME;
    short CALLEFFECT;
    long CSCORDERNO;
} oecustomercallsS;
#else /* TRANSCLASS */
typedef struct N_OECUSTOMERCALLS {
    short BRANCHNO;
    long CUSTOMERNO;
    long CALLDATE;
    long CALLTIME;
    short CALLEFFECT;
    long CSCORDERNO;

    bool operator == (const N_OECUSTOMERCALLS& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            CUSTOMERNO == right.CUSTOMERNO &&
            CALLDATE == right.CALLDATE &&
            CALLTIME == right.CALLTIME &&
            CALLEFFECT == right.CALLEFFECT &&
            CSCORDERNO == right.CSCORDERNO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        CUSTOMERNO = 0;
        CALLDATE = 0;
        CALLTIME = 0;
        CALLEFFECT = 0;
        CSCORDERNO = 0;
#endif
    }
} oecustomercallsS;
#endif /* TRANSCLASS */

/* original struct of OFFENAUFTRAG ********************************************/

#ifndef TRANSCLASS
typedef struct N_OFFENAUFTRAG {
    long KDAUFTRAGNR;
    short FILIALNR;
    long MENGEBESTELLT;
    char KDAUFTRAGART[3];
    long MENGENATRA;
    long DATUMAUSLIEFERUNG;
    long ARTIKEL_NR;
    long BESTAND;
    char DARREICHFORM[4];
    char EINHEIT[10];
    char ARTIKEL_NAME[31];
    long HERSTELLER_NR;
    long FETCH_REL;
} offenauftragS;
#else /* TRANSCLASS */
typedef struct N_OFFENAUFTRAG {
    long KDAUFTRAGNR;
    short FILIALNR;
    long MENGEBESTELLT;
    char KDAUFTRAGART[3];
    long MENGENATRA;
    long DATUMAUSLIEFERUNG;
    long ARTIKEL_NR;
    long BESTAND;
    char DARREICHFORM[4];
    char EINHEIT[10];
    char ARTIKEL_NAME[31];
    long HERSTELLER_NR;
    long FETCH_REL;
    bool operator == (const N_OFFENAUFTRAG& right) const {
        return (
            KDAUFTRAGNR == right.KDAUFTRAGNR &&
            FILIALNR == right.FILIALNR &&
            MENGEBESTELLT == right.MENGEBESTELLT &&
            !strcmp(KDAUFTRAGART, right.KDAUFTRAGART) &&
            MENGENATRA == right.MENGENATRA &&
            DATUMAUSLIEFERUNG == right.DATUMAUSLIEFERUNG &&
            ARTIKEL_NR == right.ARTIKEL_NR &&
            BESTAND == right.BESTAND &&
            !strcmp(DARREICHFORM, right.DARREICHFORM) &&
            !strcmp(EINHEIT, right.EINHEIT) &&
            !strcmp(ARTIKEL_NAME, right.ARTIKEL_NAME) &&
            HERSTELLER_NR == right.HERSTELLER_NR
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        KDAUFTRAGNR = 0;
        FILIALNR = 0;
        MENGEBESTELLT = 0;
        strcpy(KDAUFTRAGART, " " );
        MENGENATRA = 0;
        DATUMAUSLIEFERUNG = 0;
        ARTIKEL_NR = 0;
        BESTAND = 0;
        strcpy(DARREICHFORM, " " );
        strcpy(EINHEIT, " " );
        strcpy(ARTIKEL_NAME, " " );
        HERSTELLER_NR = 0;
#endif
    }
} offenauftragS;
#endif /* TRANSCLASS */

/* original struct of RUFSTAT *************************************************/

#ifndef TRANSCLASS
typedef struct N_RUFSTAT {
    long DATUM;
    long ZEIT_VON;
    long ZEIT_BIS;
    short ANZ_PLAN;
    short ANZ_POSTPONE1;
    short ANZ_POSTPONE2;
    short ANZ_POSTPONE3;
    short ANZ_POSTPONE_MORE;
    short ANZ_POSTPONE_TOTAL;
    long FETCH_REL;
} rufstatS;
#else /* TRANSCLASS */
typedef struct N_RUFSTAT {
    long DATUM;
    long ZEIT_VON;
    long ZEIT_BIS;
    short ANZ_PLAN;
    short ANZ_POSTPONE1;
    short ANZ_POSTPONE2;
    short ANZ_POSTPONE3;
    short ANZ_POSTPONE_MORE;
    short ANZ_POSTPONE_TOTAL;
    long FETCH_REL;
    bool operator == (const N_RUFSTAT& right) const {
        return (
            DATUM == right.DATUM &&
            ZEIT_VON == right.ZEIT_VON &&
            ZEIT_BIS == right.ZEIT_BIS &&
            ANZ_PLAN == right.ANZ_PLAN &&
            ANZ_POSTPONE1 == right.ANZ_POSTPONE1 &&
            ANZ_POSTPONE2 == right.ANZ_POSTPONE2 &&
            ANZ_POSTPONE3 == right.ANZ_POSTPONE3 &&
            ANZ_POSTPONE_MORE == right.ANZ_POSTPONE_MORE &&
            ANZ_POSTPONE_TOTAL == right.ANZ_POSTPONE_TOTAL
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        DATUM = 0;
        ZEIT_VON = 0;
        ZEIT_BIS = 0;
        ANZ_PLAN = 0;
        ANZ_POSTPONE1 = 0;
        ANZ_POSTPONE2 = 0;
        ANZ_POSTPONE3 = 0;
        ANZ_POSTPONE_MORE = 0;
        ANZ_POSTPONE_TOTAL = 0;
#endif
    }
} rufstatS;
#endif /* TRANSCLASS */

/* original struct of TOURZEIT ************************************************/

#ifndef TRANSCLASS
typedef struct N_TOURZEIT {
    long IDFNR;
    char TOURID[7];
    short VERTRIEBSZENTRUMNR;
} tourzeitS;
#else /* TRANSCLASS */
typedef struct N_TOURZEIT {
    long IDFNR;
    char TOURID[7];
    short VERTRIEBSZENTRUMNR;

    bool operator == (const N_TOURZEIT& right) const {
        return (
            IDFNR == right.IDFNR &&
            !strcmp(TOURID, right.TOURID) &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        IDFNR = 0;
        strcpy(TOURID, " " );
        VERTRIEBSZENTRUMNR = 0;
#endif
    }
} tourzeitS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ARTIKELKONTOANZ *****************************/

struct C_ARTIKELKONTOANZ {
    long ZEIT_BIS;
    long LFDNR;
    short FILIALNR;
    long ARTIKEL_NR;
    char BEWEGUNGSART;
    long MENGE;
    long BELEGNR;
    long UID;
    long IDFNR;
    long MENGENEU;
    long ZEITUNIX;
    long BEWEGUNGSCHLUESSEL;
    long STOCKRESERVED;
    short MOVETYPE;
    long FETCH_REL;
};
/* Structur with real chartype of AUFWERTHERST ********************************/

struct C_AUFWERTHERST {
    long KDAUFTRAGNR;
    double PREISEKAPO;
    char HERSTELLER_CODE[6];
    long FETCH_REL;
};
/* Structur with real chartype of FEIERTAG ************************************/

struct C_FEIERTAG {
    short MODUS_ALT;
    short TAG_ALT;
    short FILIALNR;
    short MODUS;
    short TAG;
    short VON_JAHR;
    short BIS_JAHR;
    char TAGNAME[21];
    long FETCH_REL;
};
/* Structur with real chartype of LAGERREVISIONANZ ****************************/

struct C_LAGERREVISIONANZ {
    short FILIALNR;
    long ARTIKEL_NR;
    long DATUM;
    long UHRZEIT;
    long BESTANDKSC;
    long BESTANDVSE;
    long FETCH_REL;
};
/* Structur with real chartype of OECUSTOMERCALLS *****************************/

struct C_OECUSTOMERCALLS {
    short BRANCHNO;
    long CUSTOMERNO;
    long CALLDATE;
    long CALLTIME;
    short CALLEFFECT;
    long CSCORDERNO;
};
/* Structur with real chartype of OFFENAUFTRAG ********************************/

struct C_OFFENAUFTRAG {
    long KDAUFTRAGNR;
    short FILIALNR;
    long MENGEBESTELLT;
    char KDAUFTRAGART[3];
    long MENGENATRA;
    long DATUMAUSLIEFERUNG;
    long ARTIKEL_NR;
    long BESTAND;
    char DARREICHFORM[4];
    char EINHEIT[10];
    char ARTIKEL_NAME[31];
    long HERSTELLER_NR;
    long FETCH_REL;
};
/* Structur with real chartype of RUFSTAT *************************************/

struct C_RUFSTAT {
    long DATUM;
    long ZEIT_VON;
    long ZEIT_BIS;
    short ANZ_PLAN;
    short ANZ_POSTPONE1;
    short ANZ_POSTPONE2;
    short ANZ_POSTPONE3;
    short ANZ_POSTPONE_MORE;
    short ANZ_POSTPONE_TOTAL;
    long FETCH_REL;
};
/* Structur with real chartype of TOURZEIT ************************************/

struct C_TOURZEIT {
    long IDFNR;
    char TOURID[7];
    short VERTRIEBSZENTRUMNR;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ARTIKELKONTOANZ ***************************/

struct I_ARTIKELKONTOANZ {
    short ZEIT_BIS;
    short LFDNR;
    short FILIALNR;
    short ARTIKEL_NR;
    short BEWEGUNGSART;
    short MENGE;
    short BELEGNR;
    short UID;
    short IDFNR;
    short MENGENEU;
    short ZEITUNIX;
    short BEWEGUNGSCHLUESSEL;
    short STOCKRESERVED;
    short MOVETYPE;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of AUFWERTHERST ******************************/

struct I_AUFWERTHERST {
    short KDAUFTRAGNR;
    short PREISEKAPO;
    short HERSTELLER_CODE;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of FEIERTAG **********************************/

struct I_FEIERTAG {
    short MODUS_ALT;
    short TAG_ALT;
    short FILIALNR;
    short MODUS;
    short TAG;
    short VON_JAHR;
    short BIS_JAHR;
    short TAGNAME;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of LAGERREVISIONANZ **************************/

struct I_LAGERREVISIONANZ {
    short FILIALNR;
    short ARTIKEL_NR;
    short DATUM;
    short UHRZEIT;
    short BESTANDKSC;
    short BESTANDVSE;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of OECUSTOMERCALLS ***************************/

struct I_OECUSTOMERCALLS {
    short BRANCHNO;
    short CUSTOMERNO;
    short CALLDATE;
    short CALLTIME;
    short CALLEFFECT;
    short CSCORDERNO;
};
/* Sizetype  Structur (buf_desc) of OFFENAUFTRAG ******************************/

struct I_OFFENAUFTRAG {
    short KDAUFTRAGNR;
    short FILIALNR;
    short MENGEBESTELLT;
    short KDAUFTRAGART;
    short MENGENATRA;
    short DATUMAUSLIEFERUNG;
    short ARTIKEL_NR;
    short BESTAND;
    short DARREICHFORM;
    short EINHEIT;
    short ARTIKEL_NAME;
    short HERSTELLER_NR;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of RUFSTAT ***********************************/

struct I_RUFSTAT {
    short DATUM;
    short ZEIT_VON;
    short ZEIT_BIS;
    short ANZ_PLAN;
    short ANZ_POSTPONE1;
    short ANZ_POSTPONE2;
    short ANZ_POSTPONE3;
    short ANZ_POSTPONE_MORE;
    short ANZ_POSTPONE_TOTAL;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of TOURZEIT **********************************/

struct I_TOURZEIT {
    short IDFNR;
    short TOURID;
    short VERTRIEBSZENTRUMNR;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ARTIKELKONTOANZ *************************************/

#if defined (BUF_DESC)
static struct buf_desc ARTIKELKONTOANZ_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L ,  11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc ARTIKELKONTOANZ_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L ,  11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of AUFWERTHERST ****************************************/

#if defined (BUF_DESC)
static struct buf_desc AUFWERTHERST_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_C, 5, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc AUFWERTHERST_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_C, 5, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of FEIERTAG ********************************************/

#if defined (BUF_DESC)
static struct buf_desc FEIERTAG_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 20, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc FEIERTAG_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 20, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of LAGERREVISIONANZ ************************************/

#if defined (BUF_DESC)
static struct buf_desc LAGERREVISIONANZ_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc LAGERREVISIONANZ_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of OECUSTOMERCALLS *************************************/

#if defined (BUF_DESC)
static struct buf_desc OECUSTOMERCALLS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc OECUSTOMERCALLS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of OFFENAUFTRAG ****************************************/

#if defined (BUF_DESC)
static struct buf_desc OFFENAUFTRAG_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 2, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 3, 0 },
   { TYP_C, 9, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc OFFENAUFTRAG_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 2, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 3, 0 },
   { TYP_C, 9, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of RUFSTAT *********************************************/

#if defined (BUF_DESC)
static struct buf_desc RUFSTAT_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc RUFSTAT_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of TOURZEIT ********************************************/

#if defined (BUF_DESC)
static struct buf_desc TOURZEIT_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc TOURZEIT_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* FunctionNumber-Define of ArtikelKontoAnz ***********************************/

#define ARTIKELKONTOANZ_SELLIST 1296

/* FunctionNumber-Define of Aufwertherst **************************************/

#define AUFWERTHERST_SELLIST 1341

/* FunctionNumber-Define of Feiertag ******************************************/

#define FEIERTAG_DELETE 1271
#define FEIERTAG_INSERT 1270
#define FEIERTAG_SELALL 1268
#define FEIERTAG_UPDATE 1269

/* FunctionNumber-Define of LagerRevisionAnz **********************************/

#define LAGERREVISIONANZ_SELLIST 1295

/* FunctionNumber-Define of OECustomerCalls ***********************************/

#define OECUSTOMERCALLS_INSERT 1715
#define OECUSTOMERCALLS_UPDATE 1716

/* FunctionNumber-Define of OffenAuftrag **************************************/

#define OFFENAUFTRAG_SELLIST 1405

/* FunctionNumber-Define of RUFSTAT *******************************************/

#define RUFSTAT_SEL_TAGSTAT 1207

/* FunctionNumber-Define of TourZeit ******************************************/

#define TOURZEIT_SELNEXTTOUR 1215

#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of ArtikelKontoAnz *******************************/

#define SelList 1296

/* Old-FunctionNumber-Define of Aufwertherst **********************************/

#define SelList 1341

/* Old-FunctionNumber-Define of Feiertag **************************************/

#define Delete 1271
#define Insert 1270
#define SelAll 1268
#define Update 1269

/* Old-FunctionNumber-Define of LagerRevisionAnz ******************************/

#define SelList 1295

/* Old-FunctionNumber-Define of OECustomerCalls *******************************/

#define Insert 1715
#define Update 1716

/* Old-FunctionNumber-Define of OffenAuftrag **********************************/

#define SelList 1405

/* Old-FunctionNumber-Define of RUFSTAT ***************************************/

#define Sel_Tagstat 1207

/* Old-FunctionNumber-Define of TourZeit **************************************/

#define SelNextTour 1215

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

class CARTIKELKONTOANZ : public ppDadeVirtual {
public:
    artikelkontoanzS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<artikelkontoanzS> lst; // class list

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
                     vector< artikelkontoanzS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     artikelkontoanzS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< artikelkontoanzS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<artikelkontoanzS>::iterator
                 beginList() { return lst.begin(); }
    vector<artikelkontoanzS>::iterator
                 endList  () { return lst.end  (); }

    long         GetZeit_bis() const { return s.ZEIT_BIS; }
    long         GetLfdnr() const { return s.LFDNR; }
    short        GetFilialnr() const { return s.FILIALNR; }
    long         GetArtikel_nr() const { return s.ARTIKEL_NR; }
    char         GetBewegungsart() const { return s.BEWEGUNGSART[0]; }
    long         GetMenge() const { return s.MENGE; }
    long         GetBelegnr() const { return s.BELEGNR; }
    long         GetUid() const { return s.UID; }
    long         GetIdfnr() const { return s.IDFNR; }
    long         GetMengeneu() const { return s.MENGENEU; }
    long         GetZeitunix() const { return s.ZEITUNIX; }
    long         GetBewegungschluessel() const { return s.BEWEGUNGSCHLUESSEL; }
    long         GetStockreserved() const { return s.STOCKRESERVED; }
    short        GetMovetype() const { return s.MOVETYPE; }

    const artikelkontoanzS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetZeit_bis(long t) { s.ZEIT_BIS = t; }
    void         SetLfdnr(long t) { s.LFDNR = t; }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetArtikel_nr(long t) { s.ARTIKEL_NR = t; }
    void         SetBewegungsart(char t) { s.BEWEGUNGSART[0] = t; s.BEWEGUNGSART[1] = '\0';}
    void         SetMenge(long t) { s.MENGE = t; }
    void         SetBelegnr(long t) { s.BELEGNR = t; }
    void         SetUid(long t) { s.UID = t; }
    void         SetIdfnr(long t) { s.IDFNR = t; }
    void         SetMengeneu(long t) { s.MENGENEU = t; }
    void         SetZeitunix(long t) { s.ZEITUNIX = t; }
    void         SetBewegungschluessel(long t) { s.BEWEGUNGSCHLUESSEL = t; }
    void         SetStockreserved(long t) { s.STOCKRESERVED = t; }
    void         SetMovetype(short t) { s.MOVETYPE = t; }

    void         SetStruct(const artikelkontoanzS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1296, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CARTIKELKONTOANZ() {
        ::buf_default((void *)&s, ARTIKELKONTOANZ_BES, ARTIKELKONTOANZ_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CARTIKELKONTOANZ() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, ARTIKELKONTOANZ_BES, ARTIKELKONTOANZ_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, ARTIKELKONTOANZ_BES, (int)ARTIKELKONTOANZ_ANZ, error_msg);
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
        if ( fkt_nr == 1296 ) return CursorServerCall(1296, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_ARTIKELKONTOANZ & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, ARTIKELKONTOANZ_BES, (int)ARTIKELKONTOANZ_ANZ, error_msg);
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
        CARTIKELKONTOANZ c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, ARTIKELKONTOANZ_BES, (int)ARTIKELKONTOANZ_ANZ, error_msg);
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

class CAUFWERTHERST : public ppDadeVirtual {
public:
    aufwertherstS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<aufwertherstS> lst; // class list

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
                     vector< aufwertherstS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     aufwertherstS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< aufwertherstS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<aufwertherstS>::iterator
                 beginList() { return lst.begin(); }
    vector<aufwertherstS>::iterator
                 endList  () { return lst.end  (); }

    long         GetKdauftragnr() const { return s.KDAUFTRAGNR; }
    double       GetPreisekapo() const { return s.PREISEKAPO; }
    const char*  GetHersteller_code(ppString & t) const { t = s.HERSTELLER_CODE; t.erasespace(ppString::END); return t.c_str(); }

    const aufwertherstS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
    void         SetPreisekapo(double t) { s.PREISEKAPO = t; }
    void         SetHersteller_code(const ppString & t) { ppGStrCopy(s.HERSTELLER_CODE, t.c_str(), L_AUFWERTHERST_HERSTELLER_CODE); }

    void         SetStruct(const aufwertherstS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1341, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CAUFWERTHERST() {
        ::buf_default((void *)&s, AUFWERTHERST_BES, AUFWERTHERST_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CAUFWERTHERST() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, AUFWERTHERST_BES, AUFWERTHERST_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, AUFWERTHERST_BES, (int)AUFWERTHERST_ANZ, error_msg);
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
        if ( fkt_nr == 1341 ) return CursorServerCall(1341, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_AUFWERTHERST & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.HERSTELLER_CODE);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, AUFWERTHERST_BES, (int)AUFWERTHERST_ANZ, error_msg);
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
        CAUFWERTHERST c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, AUFWERTHERST_BES, (int)AUFWERTHERST_ANZ, error_msg);
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

class CFEIERTAG : public ppDadeVirtual {
public:
    feiertagS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<feiertagS> lst; // class list

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
                     vector< feiertagS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     feiertagS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< feiertagS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<feiertagS>::iterator
                 beginList() { return lst.begin(); }
    vector<feiertagS>::iterator
                 endList  () { return lst.end  (); }

    short        GetModus_alt() const { return s.MODUS_ALT; }
    short        GetTag_alt() const { return s.TAG_ALT; }
    short        GetFilialnr() const { return s.FILIALNR; }
    short        GetModus() const { return s.MODUS; }
    short        GetTag() const { return s.TAG; }
    short        GetVon_jahr() const { return s.VON_JAHR; }
    short        GetBis_jahr() const { return s.BIS_JAHR; }
    const char*  GetTagname(ppString & t) const { t = s.TAGNAME; t.erasespace(ppString::END); return t.c_str(); }

    const feiertagS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetModus_alt(short t) { s.MODUS_ALT = t; }
    void         SetTag_alt(short t) { s.TAG_ALT = t; }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetModus(short t) { s.MODUS = t; }
    void         SetTag(short t) { s.TAG = t; }
    void         SetVon_jahr(short t) { s.VON_JAHR = t; }
    void         SetBis_jahr(short t) { s.BIS_JAHR = t; }
    void         SetTagname(const ppString & t) { ppGStrCopy(s.TAGNAME, t.c_str(), L_FEIERTAG_TAGNAME); }

    void         SetStruct(const feiertagS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          Delete(int pos = 0) { return UniqueServerCall(1271, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1270, pos); Strip(s); return ret; }
    int          SelAll(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1268, FetchRel, pos); return ret; }
    int          Update(int pos = 0) { int ret = UniqueServerCall(1269, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CFEIERTAG() {
        ::buf_default((void *)&s, FEIERTAG_BES, FEIERTAG_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CFEIERTAG() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, FEIERTAG_BES, FEIERTAG_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, FEIERTAG_BES, (int)FEIERTAG_ANZ, error_msg);
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
        if ( fkt_nr == 1271 ) return UniqueServerCall(1271, pos);
        if ( fkt_nr == 1270 ) return UniqueServerCall(1270, pos);
        if ( fkt_nr == 1268 ) return CursorServerCall(1268, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1269 ) return UniqueServerCall(1269, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_FEIERTAG & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.TAGNAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, FEIERTAG_BES, (int)FEIERTAG_ANZ, error_msg);
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
        CFEIERTAG c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, FEIERTAG_BES, (int)FEIERTAG_ANZ, error_msg);
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

class CLAGERREVISIONANZ : public ppDadeVirtual {
public:
    lagerrevisionanzS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<lagerrevisionanzS> lst; // class list

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
                     vector< lagerrevisionanzS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     lagerrevisionanzS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< lagerrevisionanzS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<lagerrevisionanzS>::iterator
                 beginList() { return lst.begin(); }
    vector<lagerrevisionanzS>::iterator
                 endList  () { return lst.end  (); }

    short        GetFilialnr() const { return s.FILIALNR; }
    long         GetArtikel_nr() const { return s.ARTIKEL_NR; }
    long         GetDatum() const { return s.DATUM; }
    long         GetUhrzeit() const { return s.UHRZEIT; }
    long         GetBestandksc() const { return s.BESTANDKSC; }
    long         GetBestandvse() const { return s.BESTANDVSE; }

    const lagerrevisionanzS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetArtikel_nr(long t) { s.ARTIKEL_NR = t; }
    void         SetDatum(long t) { s.DATUM = t; }
    void         SetUhrzeit(long t) { s.UHRZEIT = t; }
    void         SetBestandksc(long t) { s.BESTANDKSC = t; }
    void         SetBestandvse(long t) { s.BESTANDVSE = t; }

    void         SetStruct(const lagerrevisionanzS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1295, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CLAGERREVISIONANZ() {
        ::buf_default((void *)&s, LAGERREVISIONANZ_BES, LAGERREVISIONANZ_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CLAGERREVISIONANZ() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, LAGERREVISIONANZ_BES, LAGERREVISIONANZ_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, LAGERREVISIONANZ_BES, (int)LAGERREVISIONANZ_ANZ, error_msg);
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
        if ( fkt_nr == 1295 ) return CursorServerCall(1295, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_LAGERREVISIONANZ & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, LAGERREVISIONANZ_BES, (int)LAGERREVISIONANZ_ANZ, error_msg);
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
        CLAGERREVISIONANZ c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, LAGERREVISIONANZ_BES, (int)LAGERREVISIONANZ_ANZ, error_msg);
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

class COECUSTOMERCALLS : public ppDadeVirtual {
public:
    oecustomercallsS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<oecustomercallsS> lst; // class list

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
                     vector< oecustomercallsS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     oecustomercallsS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< oecustomercallsS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<oecustomercallsS>::iterator
                 beginList() { return lst.begin(); }
    vector<oecustomercallsS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    long         GetCalldate() const { return s.CALLDATE; }
    long         GetCalltime() const { return s.CALLTIME; }
    short        GetCalleffect() const { return s.CALLEFFECT; }
    long         GetCscorderno() const { return s.CSCORDERNO; }

    const oecustomercallsS &
                 GetStruct() const { return s; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetCalldate(long t) { s.CALLDATE = t; }
    void         SetCalltime(long t) { s.CALLTIME = t; }
    void         SetCalleffect(short t) { s.CALLEFFECT = t; }
    void         SetCscorderno(long t) { s.CSCORDERNO = t; }

    void         SetStruct(const oecustomercallsS & t) { s = t; }

    int          Insert(int pos = 0) { int ret = UniqueServerCall(1715, pos); Strip(s); return ret; }
    int          Update(int pos = 0) { int ret = UniqueServerCall(1716, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    COECUSTOMERCALLS() {
        ::buf_default((void *)&s, OECUSTOMERCALLS_BES, OECUSTOMERCALLS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~COECUSTOMERCALLS() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, OECUSTOMERCALLS_BES, OECUSTOMERCALLS_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1715 ) return UniqueServerCall(1715, pos);
        if ( fkt_nr == 1716 ) return UniqueServerCall(1716, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_OECUSTOMERCALLS & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, OECUSTOMERCALLS_BES, (int)OECUSTOMERCALLS_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class COFFENAUFTRAG : public ppDadeVirtual {
public:
    offenauftragS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<offenauftragS> lst; // class list

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
                     vector< offenauftragS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     offenauftragS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< offenauftragS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<offenauftragS>::iterator
                 beginList() { return lst.begin(); }
    vector<offenauftragS>::iterator
                 endList  () { return lst.end  (); }

    long         GetKdauftragnr() const { return s.KDAUFTRAGNR; }
    short        GetFilialnr() const { return s.FILIALNR; }
    long         GetMengebestellt() const { return s.MENGEBESTELLT; }
    const char*  GetKdauftragart(ppString & t) const { t = s.KDAUFTRAGART; t.erasespace(ppString::END); return t.c_str(); }
    long         GetMengenatra() const { return s.MENGENATRA; }
    long         GetDatumauslieferung() const { return s.DATUMAUSLIEFERUNG; }
    long         GetArtikel_nr() const { return s.ARTIKEL_NR; }
    long         GetBestand() const { return s.BESTAND; }
    const char*  GetDarreichform(ppString & t) const { t = s.DARREICHFORM; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetEinheit(ppString & t) const { t = s.EINHEIT; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetArtikel_name(ppString & t) const { t = s.ARTIKEL_NAME; t.erasespace(ppString::END); return t.c_str(); }
    long         GetHersteller_nr() const { return s.HERSTELLER_NR; }

    const offenauftragS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetMengebestellt(long t) { s.MENGEBESTELLT = t; }
    void         SetKdauftragart(const ppString & t) { ppGStrCopy(s.KDAUFTRAGART, t.c_str(), L_OFFENAUFTRAG_KDAUFTRAGART); }
    void         SetMengenatra(long t) { s.MENGENATRA = t; }
    void         SetDatumauslieferung(long t) { s.DATUMAUSLIEFERUNG = t; }
    void         SetArtikel_nr(long t) { s.ARTIKEL_NR = t; }
    void         SetBestand(long t) { s.BESTAND = t; }
    void         SetDarreichform(const ppString & t) { ppGStrCopy(s.DARREICHFORM, t.c_str(), L_OFFENAUFTRAG_DARREICHFORM); }
    void         SetEinheit(const ppString & t) { ppGStrCopy(s.EINHEIT, t.c_str(), L_OFFENAUFTRAG_EINHEIT); }
    void         SetArtikel_name(const ppString & t) { ppGStrCopy(s.ARTIKEL_NAME, t.c_str(), L_OFFENAUFTRAG_ARTIKEL_NAME); }
    void         SetHersteller_nr(long t) { s.HERSTELLER_NR = t; }

    void         SetStruct(const offenauftragS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1405, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    COFFENAUFTRAG() {
        ::buf_default((void *)&s, OFFENAUFTRAG_BES, OFFENAUFTRAG_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~COFFENAUFTRAG() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, OFFENAUFTRAG_BES, OFFENAUFTRAG_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, OFFENAUFTRAG_BES, (int)OFFENAUFTRAG_ANZ, error_msg);
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
        if ( fkt_nr == 1405 ) return CursorServerCall(1405, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_OFFENAUFTRAG & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.KDAUFTRAGART);
        ppGStripLast(d.DARREICHFORM);
        ppGStripLast(d.EINHEIT);
        ppGStripLast(d.ARTIKEL_NAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, OFFENAUFTRAG_BES, (int)OFFENAUFTRAG_ANZ, error_msg);
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
        COFFENAUFTRAG c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, OFFENAUFTRAG_BES, (int)OFFENAUFTRAG_ANZ, error_msg);
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

class CRUFSTAT : public ppDadeVirtual {
public:
    rufstatS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<rufstatS> lst; // class list

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
                     vector< rufstatS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     rufstatS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< rufstatS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<rufstatS>::iterator
                 beginList() { return lst.begin(); }
    vector<rufstatS>::iterator
                 endList  () { return lst.end  (); }

    long         GetDatum() const { return s.DATUM; }
    long         GetZeit_von() const { return s.ZEIT_VON; }
    long         GetZeit_bis() const { return s.ZEIT_BIS; }
    short        GetAnz_plan() const { return s.ANZ_PLAN; }
    short        GetAnz_postpone1() const { return s.ANZ_POSTPONE1; }
    short        GetAnz_postpone2() const { return s.ANZ_POSTPONE2; }
    short        GetAnz_postpone3() const { return s.ANZ_POSTPONE3; }
    short        GetAnz_postpone_more() const { return s.ANZ_POSTPONE_MORE; }
    short        GetAnz_postpone_total() const { return s.ANZ_POSTPONE_TOTAL; }

    const rufstatS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetDatum(long t) { s.DATUM = t; }
    void         SetZeit_von(long t) { s.ZEIT_VON = t; }
    void         SetZeit_bis(long t) { s.ZEIT_BIS = t; }
    void         SetAnz_plan(short t) { s.ANZ_PLAN = t; }
    void         SetAnz_postpone1(short t) { s.ANZ_POSTPONE1 = t; }
    void         SetAnz_postpone2(short t) { s.ANZ_POSTPONE2 = t; }
    void         SetAnz_postpone3(short t) { s.ANZ_POSTPONE3 = t; }
    void         SetAnz_postpone_more(short t) { s.ANZ_POSTPONE_MORE = t; }
    void         SetAnz_postpone_total(short t) { s.ANZ_POSTPONE_TOTAL = t; }

    void         SetStruct(const rufstatS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          Sel_Tagstat(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1207, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CRUFSTAT() {
        ::buf_default((void *)&s, RUFSTAT_BES, RUFSTAT_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CRUFSTAT() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, RUFSTAT_BES, RUFSTAT_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, RUFSTAT_BES, (int)RUFSTAT_ANZ, error_msg);
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
        if ( fkt_nr == 1207 ) return CursorServerCall(1207, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_RUFSTAT & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, RUFSTAT_BES, (int)RUFSTAT_ANZ, error_msg);
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
        CRUFSTAT c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, RUFSTAT_BES, (int)RUFSTAT_ANZ, error_msg);
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

class CTOURZEIT : public ppDadeVirtual {
public:
    tourzeitS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<tourzeitS> lst; // class list

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
                     vector< tourzeitS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     tourzeitS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< tourzeitS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<tourzeitS>::iterator
                 beginList() { return lst.begin(); }
    vector<tourzeitS>::iterator
                 endList  () { return lst.end  (); }

    long         GetIdfnr() const { return s.IDFNR; }
    const char*  GetTourid(ppString & t) const { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }

    const tourzeitS &
                 GetStruct() const { return s; }
    void         SetIdfnr(long t) { s.IDFNR = t; }
    void         SetTourid(const ppString & t) { ppGStrCopy(s.TOURID, t.c_str(), L_TOURZEIT_TOURID); }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }

    void         SetStruct(const tourzeitS & t) { s = t; }

    int          SelNextTour(int pos = 0) { int ret = UniqueServerCall(1215, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CTOURZEIT() {
        ::buf_default((void *)&s, TOURZEIT_BES, TOURZEIT_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CTOURZEIT() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, TOURZEIT_BES, TOURZEIT_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1215 ) return UniqueServerCall(1215, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_TOURZEIT & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.TOURID);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, TOURZEIT_BES, (int)TOURZEIT_ANZ, error_msg);
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

#endif   // GUARD
