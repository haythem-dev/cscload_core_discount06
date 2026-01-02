#ifndef __PP_CALLPLANUNDERTAKE_H_
#define __PP_CALLPLANUNDERTAKE_H_

/******************************************************************************/
/**/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of MCALLPLANUNDERTAKE ****************************************/

#define L_MCALLPLANUNDERTAKE_VERTRIEBSZENTRUMNR 6
#define L_MCALLPLANUNDERTAKE_KUNDENNR 11
#define L_MCALLPLANUNDERTAKE_DATUM 11
#define L_MCALLPLANUNDERTAKE_URRUFZEIT 11
#define L_MCALLPLANUNDERTAKE_RUFZEIT 11
#define L_MCALLPLANUNDERTAKE_UMKSTATUS 6
#define L_MCALLPLANUNDERTAKE_ANRUFSTATUS 6
#define L_MCALLPLANUNDERTAKE_ANRUFZAEHLER 6
#define L_MCALLPLANUNDERTAKE_TAGNR 1
#define L_MCALLPLANUNDERTAKE_TOURID 6
#define L_MCALLPLANUNDERTAKE_STOURDEFINITIV 1
#define L_MCALLPLANUNDERTAKE_RUFPROTOKOLL 1
#define L_MCALLPLANUNDERTAKE_RUFSTEUERUNG 6
#define L_MCALLPLANUNDERTAKE_POOLNR 6
#define L_MCALLPLANUNDERTAKE_MODEMPOOLNR 6
#define L_MCALLPLANUNDERTAKE_RUFEINSTELLUNG 1
#define L_MCALLPLANUNDERTAKE_ANRUFTYP 1
#define L_MCALLPLANUNDERTAKE_SKDANRUFGENERELL 1

/* Length-Define of MHOLIDAY **************************************************/

#define L_MHOLIDAY_FILIALNR 6
#define L_MHOLIDAY_MODUS 6
#define L_MHOLIDAY_TAG 6
#define L_MHOLIDAY_VON_JAHR 6
#define L_MHOLIDAY_BIS_JAHR 6
#define L_MHOLIDAY_TAGNAME 20
#define L_MHOLIDAY_ANTEIL 16
#define N_MHOLIDAY_ANTEIL 6

/* SqlDefine of MCALLPLANUNDERTAKE ********************************************/


#define MCALLPLANUNDERTAKE_PLISTE \
        "KUNDEANRUFPLANTAG.VERTRIEBSZENTRUMNR,"\
        "KUNDEANRUFPLANTAG.KUNDENNR,"\
        "KUNDEANRUFPLANTAG.DATUM,"\
        "KUNDEANRUFPLANTAG.URRUFZEIT,"\
        "KUNDEANRUFPLANTAG.RUFZEIT,"\
        "KUNDEANRUFPLANTAG.UMKSTATUS,"\
        "KUNDEANRUFPLANTAG.ANRUFSTATUS,"\
        "KUNDEANRUFPLANTAG.ANRUFZAEHLER,"\
        "KUNDEANRUFPLANTAG.TAGNR,"\
        "KUNDEANRUFPLANTAG.TOURID,"\
        "KUNDEANRUFPLANTAG.STOURDEFINITIV,"\
        "KUNDEANRUFPLANTAG.RUFPROTOKOLL,"\
        "KUNDEANRUFPLANTAG.RUFSTEUERUNG,"\
        "KUNDEANRUFPLANTAG.POOLNR,"\
        "KUNDEANRUFPLANTAG.MODEMPOOLNR,"\
        "KUNDEANRUFPLANTAG.RUFEINSTELLUNG,"\
        "KUNDEANRUFPLANTAG.ANRUFTYP,"\
        "KUNDEANRUFPLANTAG.SKDANRUFGENERELL"

/* SqlDefine of MHOLIDAY ******************************************************/


#define MHOLIDAY_PLISTE \
        "FEIERTAG.FILIALNR,"\
        "FEIERTAG.MODUS,"\
        "FEIERTAG.TAG,"\
        "FEIERTAG.VON_JAHR,"\
        "FEIERTAG.BIS_JAHR,"\
        "FEIERTAG.TAGNAME,"\
        "FEIERTAG.ANTEIL"

/* SqlDefine of MCALLPLANUNDERTAKE ********************************************/


#define MCALLPLANUNDERTAKE_UPDLISTE \
        "VERTRIEBSZENTRUMNR=?,"\
        "KUNDENNR=?,"\
        "DATUM=?,"\
        "URRUFZEIT=?,"\
        "RUFZEIT=?,"\
        "UMKSTATUS=?,"\
        "ANRUFSTATUS=?,"\
        "ANRUFZAEHLER=?,"\
        "TAGNR=?,"\
        "TOURID=?,"\
        "STOURDEFINITIV=?,"\
        "RUFPROTOKOLL=?,"\
        "RUFSTEUERUNG=?,"\
        "POOLNR=?,"\
        "MODEMPOOLNR=?,"\
        "RUFEINSTELLUNG=?,"\
        "ANRUFTYP=?,"\
        "SKDANRUFGENERELL=?"
/* SqlDefine of MHOLIDAY ******************************************************/


#define MHOLIDAY_UPDLISTE \
        "FILIALNR=?,"\
        "MODUS=?,"\
        "TAG=?,"\
        "VON_JAHR=?,"\
        "BIS_JAHR=?,"\
        "TAGNAME=?,"\
        "ANTEIL=?"
/* SqlMacros-Define of MCALLPLANUNDERTAKE *************************************/

#define MCALLPLANUNDERTAKE_ZEIGER(x) \
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->DATUM,\
        :x->URRUFZEIT,\
        :x->RUFZEIT,\
        :x->UMKSTATUS,\
        :x->ANRUFSTATUS,\
        :x->ANRUFZAEHLER,\
        :x->TAGNR,\
        :x->TOURID,\
        :x->STOURDEFINITIV,\
        :x->RUFPROTOKOLL,\
        :x->RUFSTEUERUNG,\
        :x->POOLNR,\
        :x->MODEMPOOLNR,\
        :x->RUFEINSTELLUNG,\
        :x->ANRUFTYP,\
        :x->SKDANRUFGENERELL
#define MCALLPLANUNDERTAKE_ZEIGERSEL(x) \
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->DATUM,\
        :x->URRUFZEIT,\
        :x->RUFZEIT,\
        :x->UMKSTATUS,\
        :x->ANRUFSTATUS,\
        :x->ANRUFZAEHLER,\
        :x->TAGNR,\
        :x->TOURID,\
        :x->STOURDEFINITIV,\
        :x->RUFPROTOKOLL,\
        :x->RUFSTEUERUNG,\
        :x->POOLNR,\
        :x->MODEMPOOLNR,\
        :x->RUFEINSTELLUNG,\
        :x->ANRUFTYP,\
        :x->SKDANRUFGENERELL

/* SqlMacros-Define of MHOLIDAY ***********************************************/

#define MHOLIDAY_ZEIGER(x) \
        :x->FILIALNR,\
        :x->MODUS,\
        :x->TAG,\
        :x->VON_JAHR,\
        :x->BIS_JAHR,\
        :x->TAGNAME,\
        :x->ANTEIL
#define MHOLIDAY_ZEIGERSEL(x) \
        :x->FILIALNR,\
        :x->MODUS,\
        :x->TAG,\
        :x->VON_JAHR,\
        :x->BIS_JAHR,\
        :x->TAGNAME,\
        :x->ANTEIL

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define MCALLPLANUNDERTAKE_H
#define MCALLPLANUNDERTAKE_ANZ ( sizeof(MCALLPLANUNDERTAKE_BES) / sizeof(struct buf_desc) )
#define MHOLIDAY_H
#define MHOLIDAY_ANZ ( sizeof(MHOLIDAY_BES) / sizeof(struct buf_desc) )
#endif

#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of MCALLPLANUNDERTAKE **************************************/

#ifndef TRANSCLASS
typedef struct N_MCALLPLANUNDERTAKE {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long DATUM;
    long URRUFZEIT;
    long RUFZEIT;
    short UMKSTATUS;
    short ANRUFSTATUS;
    short ANRUFZAEHLER;
    char TAGNR[2];
    char TOURID[7];
    char STOURDEFINITIV[2];
    char RUFPROTOKOLL[2];
    short RUFSTEUERUNG;
    short POOLNR;
    short MODEMPOOLNR;
    char RUFEINSTELLUNG[2];
    char ANRUFTYP[2];
    char SKDANRUFGENERELL[2];
    long FETCH_REL;
} mcallplanundertakeS;
#else /* TRANSCLASS */
typedef struct N_MCALLPLANUNDERTAKE {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long DATUM;
    long URRUFZEIT;
    long RUFZEIT;
    short UMKSTATUS;
    short ANRUFSTATUS;
    short ANRUFZAEHLER;
    char TAGNR[2];
    char TOURID[7];
    char STOURDEFINITIV[2];
    char RUFPROTOKOLL[2];
    short RUFSTEUERUNG;
    short POOLNR;
    short MODEMPOOLNR;
    char RUFEINSTELLUNG[2];
    char ANRUFTYP[2];
    char SKDANRUFGENERELL[2];
    long FETCH_REL;
    bool operator == (const N_MCALLPLANUNDERTAKE& right) const {
        return (
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            DATUM == right.DATUM &&
            URRUFZEIT == right.URRUFZEIT &&
            RUFZEIT == right.RUFZEIT &&
            UMKSTATUS == right.UMKSTATUS &&
            ANRUFSTATUS == right.ANRUFSTATUS &&
            ANRUFZAEHLER == right.ANRUFZAEHLER &&
            !strcmp(TAGNR, right.TAGNR) &&
            !strcmp(TOURID, right.TOURID) &&
            !strcmp(STOURDEFINITIV, right.STOURDEFINITIV) &&
            !strcmp(RUFPROTOKOLL, right.RUFPROTOKOLL) &&
            RUFSTEUERUNG == right.RUFSTEUERUNG &&
            POOLNR == right.POOLNR &&
            MODEMPOOLNR == right.MODEMPOOLNR &&
            !strcmp(RUFEINSTELLUNG, right.RUFEINSTELLUNG) &&
            !strcmp(ANRUFTYP, right.ANRUFTYP) &&
            !strcmp(SKDANRUFGENERELL, right.SKDANRUFGENERELL)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        DATUM = 0;
        URRUFZEIT = 0;
        RUFZEIT = 0;
        UMKSTATUS = 0;
        ANRUFSTATUS = 0;
        ANRUFZAEHLER = 0;
        strcpy(TAGNR, " " );
        strcpy(TOURID, " " );
        strcpy(STOURDEFINITIV, " " );
        strcpy(RUFPROTOKOLL, " " );
        RUFSTEUERUNG = 0;
        POOLNR = 0;
        MODEMPOOLNR = 0;
        strcpy(RUFEINSTELLUNG, " " );
        strcpy(ANRUFTYP, " " );
        strcpy(SKDANRUFGENERELL, " " );
#endif
    }
} mcallplanundertakeS;
#endif /* TRANSCLASS */

/* original struct of MHOLIDAY ************************************************/

#ifndef TRANSCLASS
typedef struct N_MHOLIDAY {
    short FILIALNR;
    short MODUS;
    short TAG;
    short VON_JAHR;
    short BIS_JAHR;
    char TAGNAME[21];
    double ANTEIL;
    long FETCH_REL;
} mholidayS;
#else /* TRANSCLASS */
typedef struct N_MHOLIDAY {
    short FILIALNR;
    short MODUS;
    short TAG;
    short VON_JAHR;
    short BIS_JAHR;
    char TAGNAME[21];
    double ANTEIL;
    long FETCH_REL;
    bool operator == (const N_MHOLIDAY& right) const {
        return (
            FILIALNR == right.FILIALNR &&
            MODUS == right.MODUS &&
            TAG == right.TAG &&
            VON_JAHR == right.VON_JAHR &&
            BIS_JAHR == right.BIS_JAHR &&
            !strcmp(TAGNAME, right.TAGNAME) &&
            ANTEIL == right.ANTEIL
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        FILIALNR = 0;
        MODUS = 0;
        TAG = 0;
        VON_JAHR = 0;
        BIS_JAHR = 0;
        strcpy(TAGNAME, " " );
        ANTEIL = 0;
#endif
    }
} mholidayS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of MCALLPLANUNDERTAKE **************************/

struct C_MCALLPLANUNDERTAKE {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long DATUM;
    long URRUFZEIT;
    long RUFZEIT;
    short UMKSTATUS;
    short ANRUFSTATUS;
    short ANRUFZAEHLER;
    char TAGNR;
    char TOURID[7];
    char STOURDEFINITIV;
    char RUFPROTOKOLL;
    short RUFSTEUERUNG;
    short POOLNR;
    short MODEMPOOLNR;
    char RUFEINSTELLUNG;
    char ANRUFTYP;
    char SKDANRUFGENERELL;
    long FETCH_REL;
};
/* Structur with real chartype of MHOLIDAY ************************************/

struct C_MHOLIDAY {
    short FILIALNR;
    short MODUS;
    short TAG;
    short VON_JAHR;
    short BIS_JAHR;
    char TAGNAME[21];
    double ANTEIL;
    long FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of MCALLPLANUNDERTAKE ************************/

struct I_MCALLPLANUNDERTAKE {
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short DATUM;
    short URRUFZEIT;
    short RUFZEIT;
    short UMKSTATUS;
    short ANRUFSTATUS;
    short ANRUFZAEHLER;
    short TAGNR;
    short TOURID;
    short STOURDEFINITIV;
    short RUFPROTOKOLL;
    short RUFSTEUERUNG;
    short POOLNR;
    short MODEMPOOLNR;
    short RUFEINSTELLUNG;
    short ANRUFTYP;
    short SKDANRUFGENERELL;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of MHOLIDAY **********************************/

struct I_MHOLIDAY {
    short FILIALNR;
    short MODUS;
    short TAG;
    short VON_JAHR;
    short BIS_JAHR;
    short TAGNAME;
    short ANTEIL;
    short FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of MCALLPLANUNDERTAKE **********************************/

#if defined (BUF_DESC)
static struct buf_desc MCALLPLANUNDERTAKE_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MCALLPLANUNDERTAKE_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of MHOLIDAY ********************************************/

#if defined (BUF_DESC)
static struct buf_desc MHOLIDAY_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 20, 0 },
   { TYP_D, 16, 6 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MHOLIDAY_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 20, 0 },
   { TYP_D, 16, 6 },
   { TYP_L , 11, 0 },
};
#endif

/* FunctionNumber-Define of MCallPlanUndertake ********************************/

#define MCALLPLANUNDERTAKE_AINCLUDEDUMMY 1773
#define MCALLPLANUNDERTAKE_CHECKAVAILABLEENTRIES 1107
#define MCALLPLANUNDERTAKE_CHECKAVAILABLEENTRIESPHON 1201
#define MCALLPLANUNDERTAKE_DELALL 1106
#define MCALLPLANUNDERTAKE_DELALLOLDER 1222
#define MCALLPLANUNDERTAKE_DELALLPHON 1219
#define MCALLPLANUNDERTAKE_DELALLPHONOLDER 1223
#define MCALLPLANUNDERTAKE_DELCALLPLANLOADOLDER 1231
#define MCALLPLANUNDERTAKE_DELEVENTS 1167
#define MCALLPLANUNDERTAKE_DELEVENTSOLDER 1226
#define MCALLPLANUNDERTAKE_DELEVENTSPHON 1218
#define MCALLPLANUNDERTAKE_DELEVENTSPHONOLDER 1227
#define MCALLPLANUNDERTAKE_INSERT 1105
#define MCALLPLANUNDERTAKE_SELCOUNTAVAILABLE 1108
#define MCALLPLANUNDERTAKE_SELCOUNTAVAILABLEPHON 1202
#define MCALLPLANUNDERTAKE_UNDERTAKECALLPLAN 1104
#define MCALLPLANUNDERTAKE_UNDERTAKECALLPLANPHON 1211

/* FunctionNumber-Define of MHoliday ******************************************/

#define MHOLIDAY_ENDBROWSE 1236
#define MHOLIDAY_ISHOLIDAY 1237
#define MHOLIDAY_SELCOUNT 1233
#define MHOLIDAY_SELHOLIDAY 1232
#define MHOLIDAY_STARTBROWSE 1234
#define MHOLIDAY_INLINE_GETBUFFER 1235

#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of MCallPlanUndertake ****************************/

#define AIncludeDummy 1773
#define CheckAvailableEntries 1107
#define CheckAvailableEntriesPhon 1201
#define DelAll 1106
#define DelAllOlder 1222
#define DelAllPhon 1219
#define DelAllPhonOlder 1223
#define DelCallPlanLoadOlder 1231
#define DelEvents 1167
#define DelEventsOlder 1226
#define DelEventsPhon 1218
#define DelEventsPhonOlder 1227
#define Insert 1105
#define SelCountAvailable 1108
#define SelCountAvailablePhon 1202
#define UndertakeCallplan 1104
#define UndertakeCallplanPhon 1211

/* Old-FunctionNumber-Define of MHoliday **************************************/

#define EndBrowse 1236
#define IsHoliday 1237
#define SelCount 1233
#define SelHoliday 1232
#define StartBrowse 1234
#define inline_GetBuffer 1235

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

class CMCALLPLANUNDERTAKE : public ppDadeVirtual {
public:
    mcallplanundertakeS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<mcallplanundertakeS> lst; // class list

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
                     vector< mcallplanundertakeS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     mcallplanundertakeS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< mcallplanundertakeS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<mcallplanundertakeS>::iterator
                 beginList() { return lst.begin(); }
    vector<mcallplanundertakeS>::iterator
                 endList  () { return lst.end  (); }

    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    long         GetDatum() const { return s.DATUM; }
    long         GetUrrufzeit() const { return s.URRUFZEIT; }
    long         GetRufzeit() const { return s.RUFZEIT; }
    short        GetUmkstatus() const { return s.UMKSTATUS; }
    short        GetAnrufstatus() const { return s.ANRUFSTATUS; }
    short        GetAnrufzaehler() const { return s.ANRUFZAEHLER; }
    char         GetTagnr() const { return s.TAGNR[0]; }
    const char*  GetTourid(ppString & t) const { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
    char         GetStourdefinitiv() const { return s.STOURDEFINITIV[0]; }
    char         GetRufprotokoll() const { return s.RUFPROTOKOLL[0]; }
    short        GetRufsteuerung() const { return s.RUFSTEUERUNG; }
    short        GetPoolnr() const { return s.POOLNR; }
    short        GetModempoolnr() const { return s.MODEMPOOLNR; }
    char         GetRufeinstellung() const { return s.RUFEINSTELLUNG[0]; }
    char         GetAnruftyp() const { return s.ANRUFTYP[0]; }
    char         GetSkdanrufgenerell() const { return s.SKDANRUFGENERELL[0]; }

    const mcallplanundertakeS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetDatum(long t) { s.DATUM = t; }
    void         SetUrrufzeit(long t) { s.URRUFZEIT = t; }
    void         SetRufzeit(long t) { s.RUFZEIT = t; }
    void         SetUmkstatus(short t) { s.UMKSTATUS = t; }
    void         SetAnrufstatus(short t) { s.ANRUFSTATUS = t; }
    void         SetAnrufzaehler(short t) { s.ANRUFZAEHLER = t; }
    void         SetTagnr(char t) { s.TAGNR[0] = t; s.TAGNR[1] = '\0';}
    void         SetTourid(const ppString & t) { ppGStrCopy(s.TOURID, t.c_str(), L_MCALLPLANUNDERTAKE_TOURID); }
    void         SetStourdefinitiv(char t) { s.STOURDEFINITIV[0] = t; s.STOURDEFINITIV[1] = '\0';}
    void         SetRufprotokoll(char t) { s.RUFPROTOKOLL[0] = t; s.RUFPROTOKOLL[1] = '\0';}
    void         SetRufsteuerung(short t) { s.RUFSTEUERUNG = t; }
    void         SetPoolnr(short t) { s.POOLNR = t; }
    void         SetModempoolnr(short t) { s.MODEMPOOLNR = t; }
    void         SetRufeinstellung(char t) { s.RUFEINSTELLUNG[0] = t; s.RUFEINSTELLUNG[1] = '\0';}
    void         SetAnruftyp(char t) { s.ANRUFTYP[0] = t; s.ANRUFTYP[1] = '\0';}
    void         SetSkdanrufgenerell(char t) { s.SKDANRUFGENERELL[0] = t; s.SKDANRUFGENERELL[1] = '\0';}

    void         SetStruct(const mcallplanundertakeS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          AIncludeDummy(int pos = 0) { int ret = UniqueServerCall(1773, pos); Strip(s); return ret; }
    int          CheckAvailableEntries(int pos = 0) { int ret = UniqueServerCall(1107, pos); Strip(s); return ret; }
    int          CheckAvailableEntriesPhon(int pos = 0) { int ret = UniqueServerCall(1201, pos); Strip(s); return ret; }
    int          DelAll(int pos = 0) { return UniqueServerCall(1106, pos); }
    int          DelAllOlder(int pos = 0) { return UniqueServerCall(1222, pos); }
    int          DelAllPhon(int pos = 0) { int ret = UniqueServerCall(1219, pos); Strip(s); return ret; }
    int          DelAllPhonOlder(int pos = 0) { int ret = UniqueServerCall(1223, pos); Strip(s); return ret; }
    int          DelCallPlanLoadOlder(int pos = 0) { int ret = UniqueServerCall(1231, pos); Strip(s); return ret; }
    int          DelEvents(int pos = 0) { int ret = UniqueServerCall(1167, pos); Strip(s); return ret; }
    int          DelEventsOlder(int pos = 0) { int ret = UniqueServerCall(1226, pos); Strip(s); return ret; }
    int          DelEventsPhon(int pos = 0) { int ret = UniqueServerCall(1218, pos); Strip(s); return ret; }
    int          DelEventsPhonOlder(int pos = 0) { int ret = UniqueServerCall(1227, pos); Strip(s); return ret; }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1105, pos); Strip(s); return ret; }
    int          SelCountAvailable(int pos = 0) { int ret = UniqueServerCall(1108, pos); Strip(s); return ret; }
    int          SelCountAvailablePhon(int pos = 0) { int ret = UniqueServerCall(1202, pos); Strip(s); return ret; }
    int          UndertakeCallplan(int pos = 0) { int ret = UniqueServerCall(1104, pos); Strip(s); return ret; }
    int          UndertakeCallplanPhon(int pos = 0) { int ret = UniqueServerCall(1211, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMCALLPLANUNDERTAKE() {
        ::buf_default((void *)&s, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMCALLPLANUNDERTAKE() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MCALLPLANUNDERTAKE_BES, (int)MCALLPLANUNDERTAKE_ANZ, error_msg);
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
        if ( fkt_nr == 1773 ) return UniqueServerCall(1773, pos);
        if ( fkt_nr == 1107 ) return UniqueServerCall(1107, pos);
        if ( fkt_nr == 1201 ) return UniqueServerCall(1201, pos);
        if ( fkt_nr == 1106 ) return UniqueServerCall(1106, pos);
        if ( fkt_nr == 1222 ) return UniqueServerCall(1222, pos);
        if ( fkt_nr == 1219 ) return UniqueServerCall(1219, pos);
        if ( fkt_nr == 1223 ) return UniqueServerCall(1223, pos);
        if ( fkt_nr == 1231 ) return UniqueServerCall(1231, pos);
        if ( fkt_nr == 1167 ) return UniqueServerCall(1167, pos);
        if ( fkt_nr == 1226 ) return UniqueServerCall(1226, pos);
        if ( fkt_nr == 1218 ) return UniqueServerCall(1218, pos);
        if ( fkt_nr == 1227 ) return UniqueServerCall(1227, pos);
        if ( fkt_nr == 1105 ) return UniqueServerCall(1105, pos);
        if ( fkt_nr == 1108 ) return UniqueServerCall(1108, pos);
        if ( fkt_nr == 1202 ) return UniqueServerCall(1202, pos);
        if ( fkt_nr == 1104 ) return UniqueServerCall(1104, pos);
        if ( fkt_nr == 1211 ) return UniqueServerCall(1211, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MCALLPLANUNDERTAKE & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.TOURID);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MCALLPLANUNDERTAKE_BES, (int)MCALLPLANUNDERTAKE_ANZ, error_msg);
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
        CMCALLPLANUNDERTAKE c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MCALLPLANUNDERTAKE_BES, (int)MCALLPLANUNDERTAKE_ANZ, error_msg);
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

class CMHOLIDAY : public ppDadeVirtual {
public:
    mholidayS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<mholidayS> lst; // class list

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
                     vector< mholidayS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     mholidayS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< mholidayS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<mholidayS>::iterator
                 beginList() { return lst.begin(); }
    vector<mholidayS>::iterator
                 endList  () { return lst.end  (); }

    short        GetFilialnr() const { return s.FILIALNR; }
    short        GetModus() const { return s.MODUS; }
    short        GetTag() const { return s.TAG; }
    short        GetVon_jahr() const { return s.VON_JAHR; }
    short        GetBis_jahr() const { return s.BIS_JAHR; }
    const char*  GetTagname(ppString & t) const { t = s.TAGNAME; t.erasespace(ppString::END); return t.c_str(); }
    double       GetAnteil() const { return s.ANTEIL; }

    const mholidayS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetModus(short t) { s.MODUS = t; }
    void         SetTag(short t) { s.TAG = t; }
    void         SetVon_jahr(short t) { s.VON_JAHR = t; }
    void         SetBis_jahr(short t) { s.BIS_JAHR = t; }
    void         SetTagname(const ppString & t) { ppGStrCopy(s.TAGNAME, t.c_str(), L_MHOLIDAY_TAGNAME); }
    void         SetAnteil(double t) { s.ANTEIL = t; }

    void         SetStruct(const mholidayS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          EndBrowse(int pos = 0) { int ret = UniqueServerCall(1236, pos); Strip(s); return ret; }
    int          IsHoliday(int pos = 0) { int ret = UniqueServerCall(1237, pos); Strip(s); return ret; }
    int          SelCount(int pos = 0) { int ret = UniqueServerCall(1233, pos); Strip(s); return ret; }
    int          SelHoliday(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1232, FetchRel, pos); return ret; }
    int          StartBrowse(int pos = 0) { int ret = UniqueServerCall(1234, pos); Strip(s); return ret; }
    int          inline_GetBuffer(int pos = 0) { int ret = UniqueServerCall(1235, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMHOLIDAY() {
        ::buf_default((void *)&s, MHOLIDAY_BES, MHOLIDAY_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMHOLIDAY() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MHOLIDAY_BES, MHOLIDAY_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MHOLIDAY_BES, (int)MHOLIDAY_ANZ, error_msg);
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
        if ( fkt_nr == 1236 ) return UniqueServerCall(1236, pos);
        if ( fkt_nr == 1237 ) return UniqueServerCall(1237, pos);
        if ( fkt_nr == 1233 ) return UniqueServerCall(1233, pos);
        if ( fkt_nr == 1232 ) return CursorServerCall(1232, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1234 ) return UniqueServerCall(1234, pos);
        if ( fkt_nr == 1235 ) return UniqueServerCall(1235, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MHOLIDAY & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.TAGNAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MHOLIDAY_BES, (int)MHOLIDAY_ANZ, error_msg);
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
        CMHOLIDAY c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MHOLIDAY_BES, (int)MHOLIDAY_ANZ, error_msg);
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
