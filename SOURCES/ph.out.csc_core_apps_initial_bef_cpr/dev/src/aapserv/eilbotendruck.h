#ifndef __PP_EILBOTENDRUCK_H_
#define __PP_EILBOTENDRUCK_H_

/******************************************************************************/
/* c:\git\pharmos.outbound.csc_core_applications\dev\src\aapserv\Eilbotendruck */
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of EILBOTENDRUCK *********************************************/

#define L_EILBOTENDRUCK_USERNAME 8
#define L_EILBOTENDRUCK_IDFNR 11
#define L_EILBOTENDRUCK_TOURID 6
#define L_EILBOTENDRUCK_BEMERKUNGEN 240
#define L_EILBOTENDRUCK_FILIALNR 6
#define L_EILBOTENDRUCK_VERTRIEBSZENTRUMNR 6

/* Length-Define of EXTRATOURREASONS ******************************************/

#define L_EXTRATOURREASONS_EXTRATOURREASON 40
#define L_EXTRATOURREASONS_CSCORDERTYPE 2

/* SqlDefine of EILBOTENDRUCK *************************************************/


#define EILBOTENDRUCK_PLISTE \
        "PASSWD.USERNAME,"\
        "KDAUFTRAG.IDFNR,"\
        "KDAUFTRAG.TOURID,"\
        "KDAUFTRAG.BEMERKUNGEN,"\
        "KUNDELAGERINFO.FILIALNR,"\
        "KUNDELAGERINFO.VERTRIEBSZENTRUMNR"

/* SqlDefine of EXTRATOURREASONS **********************************************/


#define EXTRATOURREASONS_PLISTE \
        "EXTRATOURREASONS.EXTRATOURREASON,"\
        "EXTRATOURREASONS.CSCORDERTYPE"

/* SqlDefine of EILBOTENDRUCK *************************************************/


#define EILBOTENDRUCK_UPDLISTE \
        "USERNAME=?,"\
        "IDFNR=?,"\
        "TOURID=?,"\
        "BEMERKUNGEN=?,"\
        "FILIALNR=?,"\
        "VERTRIEBSZENTRUMNR=?"
/* SqlDefine of EXTRATOURREASONS **********************************************/


#define EXTRATOURREASONS_UPDLISTE \
        "EXTRATOURREASON=?,"\
        "CSCORDERTYPE=?"
/* SqlMacros-Define of EILBOTENDRUCK ******************************************/

#define EILBOTENDRUCK_ZEIGER(x) \
        :x->USERNAME,\
        :x->IDFNR,\
        :x->TOURID,\
        :x->BEMERKUNGEN,\
        :x->FILIALNR,\
        :x->VERTRIEBSZENTRUMNR
#define EILBOTENDRUCK_ZEIGERSEL(x) \
        :x->USERNAME,\
        :x->IDFNR,\
        :x->TOURID,\
        :x->BEMERKUNGEN,\
        :x->FILIALNR,\
        :x->VERTRIEBSZENTRUMNR

/* SqlMacros-Define of EXTRATOURREASONS ***************************************/

#define EXTRATOURREASONS_ZEIGER(x) \
        :x->EXTRATOURREASON,\
        :x->CSCORDERTYPE
#define EXTRATOURREASONS_ZEIGERSEL(x) \
        :x->EXTRATOURREASON,\
        :x->CSCORDERTYPE

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define EILBOTENDRUCK_H
#define EILBOTENDRUCK_ANZ ( sizeof(EILBOTENDRUCK_BES) / sizeof(struct buf_desc) )
#define EXTRATOURREASONS_H
#define EXTRATOURREASONS_ANZ ( sizeof(EXTRATOURREASONS_BES) / sizeof(struct buf_desc) )
#endif

#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of EILBOTENDRUCK *******************************************/

#ifndef TRANSCLASS
typedef struct N_EILBOTENDRUCK {
    char USERNAME[9];
    long IDFNR;
    char TOURID[7];
    char BEMERKUNGEN[241];
    short FILIALNR;
    short VERTRIEBSZENTRUMNR;
} eilbotendruckS;
#else /* TRANSCLASS */
typedef struct N_EILBOTENDRUCK {
    char USERNAME[9];
    long IDFNR;
    char TOURID[7];
    char BEMERKUNGEN[241];
    short FILIALNR;
    short VERTRIEBSZENTRUMNR;

    bool operator == (const N_EILBOTENDRUCK& right) const {
        return (
            !strcmp(USERNAME, right.USERNAME) &&
            IDFNR == right.IDFNR &&
            !strcmp(TOURID, right.TOURID) &&
            !strcmp(BEMERKUNGEN, right.BEMERKUNGEN) &&
            FILIALNR == right.FILIALNR &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        strcpy(USERNAME, " " );
        IDFNR = 0;
        strcpy(TOURID, " " );
        strcpy(BEMERKUNGEN, " " );
        FILIALNR = 0;
        VERTRIEBSZENTRUMNR = 0;
#endif
    }
} eilbotendruckS;
#endif /* TRANSCLASS */

/* original struct of EXTRATOURREASONS ****************************************/

#ifndef TRANSCLASS
typedef struct N_EXTRATOURREASONS {
    char EXTRATOURREASON[41];
    char CSCORDERTYPE[3];
    long FETCH_REL;
} extratourreasonsS;
#else /* TRANSCLASS */
typedef struct N_EXTRATOURREASONS {
    char EXTRATOURREASON[41];
    char CSCORDERTYPE[3];
    long FETCH_REL;
    bool operator == (const N_EXTRATOURREASONS& right) const {
        return (
            !strcmp(EXTRATOURREASON, right.EXTRATOURREASON) &&
            !strcmp(CSCORDERTYPE, right.CSCORDERTYPE)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        strcpy(EXTRATOURREASON, " " );
        strcpy(CSCORDERTYPE, " " );
#endif
    }
} extratourreasonsS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of EILBOTENDRUCK *******************************/

struct C_EILBOTENDRUCK {
    char USERNAME[9];
    long IDFNR;
    char TOURID[7];
    char BEMERKUNGEN[241];
    short FILIALNR;
    short VERTRIEBSZENTRUMNR;
};
/* Structur with real chartype of EXTRATOURREASONS ****************************/

struct C_EXTRATOURREASONS {
    char EXTRATOURREASON[41];
    char CSCORDERTYPE[3];
    long FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of EILBOTENDRUCK *****************************/

struct I_EILBOTENDRUCK {
    short USERNAME;
    short IDFNR;
    short TOURID;
    short BEMERKUNGEN;
    short FILIALNR;
    short VERTRIEBSZENTRUMNR;
};
/* Sizetype  Structur (buf_desc) of EXTRATOURREASONS **************************/

struct I_EXTRATOURREASONS {
    short EXTRATOURREASON;
    short CSCORDERTYPE;
    short FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of EILBOTENDRUCK ***************************************/

#if defined (BUF_DESC)
static struct buf_desc EILBOTENDRUCK_BES [] = {
   { TYP_C, 8, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 240, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc EILBOTENDRUCK_BES [] = {
   { TYP_C, 8, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 240, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* Structur (buf_desc) of EXTRATOURREASONS ************************************/

#if defined (BUF_DESC)
static struct buf_desc EXTRATOURREASONS_BES [] = {
   { TYP_C, 40, 0 },
   { TYP_C, 2, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc EXTRATOURREASONS_BES [] = {
   { TYP_C, 40, 0 },
   { TYP_C, 2, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* FunctionNumber-Define of EilBotenDruck *************************************/

#define EILBOTENDRUCK_DRUCKEIL 1095

/* FunctionNumber-Define of ExtraTourReasons **********************************/

#define EXTRATOURREASONS_DELETE 1750
#define EXTRATOURREASONS_INSERT 1749
#define EXTRATOURREASONS_SELLIST 1748
#define EXTRATOURREASONS_SELLISTALL 1751

#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of EilBotenDruck *********************************/

#define druckeil 1095

/* Old-FunctionNumber-Define of ExtraTourReasons ******************************/

#define Delete 1750
#define Insert 1749
#define SelList 1748
#define SelListAll 1751

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

class CEILBOTENDRUCK : public ppDadeVirtual {
public:
    eilbotendruckS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<eilbotendruckS> lst; // class list

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
                     vector< eilbotendruckS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     eilbotendruckS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< eilbotendruckS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<eilbotendruckS>::iterator
                 beginList() { return lst.begin(); }
    vector<eilbotendruckS>::iterator
                 endList  () { return lst.end  (); }

    const char*  GetUsername(ppString & t) const { t = s.USERNAME; t.erasespace(ppString::END); return t.c_str(); }
    long         GetIdfnr() const { return s.IDFNR; }
    const char*  GetTourid(ppString & t) const { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetBemerkungen(ppString & t) const { t = s.BEMERKUNGEN; t.erasespace(ppString::END); return t.c_str(); }
    short        GetFilialnr() const { return s.FILIALNR; }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }

    const eilbotendruckS &
                 GetStruct() const { return s; }
    void         SetUsername(const ppString & t) { ppGStrCopy(s.USERNAME, t.c_str(), L_EILBOTENDRUCK_USERNAME); }
    void         SetIdfnr(long t) { s.IDFNR = t; }
    void         SetTourid(const ppString & t) { ppGStrCopy(s.TOURID, t.c_str(), L_EILBOTENDRUCK_TOURID); }
    void         SetBemerkungen(const ppString & t) { ppGStrCopy(s.BEMERKUNGEN, t.c_str(), L_EILBOTENDRUCK_BEMERKUNGEN); }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }

    void         SetStruct(const eilbotendruckS & t) { s = t; }

    int          druckeil(int pos = 0) { int ret = UniqueServerCall(1095, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CEILBOTENDRUCK() {
        ::buf_default((void *)&s, EILBOTENDRUCK_BES, EILBOTENDRUCK_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CEILBOTENDRUCK() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, EILBOTENDRUCK_BES, EILBOTENDRUCK_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1095 ) return UniqueServerCall(1095, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_EILBOTENDRUCK & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.USERNAME);
        ppGStripLast(d.TOURID);
        ppGStripLast(d.BEMERKUNGEN);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, EILBOTENDRUCK_BES, (int)EILBOTENDRUCK_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CEXTRATOURREASONS : public ppDadeVirtual {
public:
    extratourreasonsS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<extratourreasonsS> lst; // class list

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
                     vector< extratourreasonsS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     extratourreasonsS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< extratourreasonsS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<extratourreasonsS>::iterator
                 beginList() { return lst.begin(); }
    vector<extratourreasonsS>::iterator
                 endList  () { return lst.end  (); }

    const char*  GetExtratourreason(ppString & t) const { t = s.EXTRATOURREASON; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetCscordertype(ppString & t) const { t = s.CSCORDERTYPE; t.erasespace(ppString::END); return t.c_str(); }

    const extratourreasonsS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetExtratourreason(const ppString & t) { ppGStrCopy(s.EXTRATOURREASON, t.c_str(), L_EXTRATOURREASONS_EXTRATOURREASON); }
    void         SetCscordertype(const ppString & t) { ppGStrCopy(s.CSCORDERTYPE, t.c_str(), L_EXTRATOURREASONS_CSCORDERTYPE); }

    void         SetStruct(const extratourreasonsS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          Delete(int pos = 0) { return UniqueServerCall(1750, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1749, pos); Strip(s); return ret; }
    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1748, FetchRel, pos); return ret; }
    int          SelListAll(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1751, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CEXTRATOURREASONS() {
        ::buf_default((void *)&s, EXTRATOURREASONS_BES, EXTRATOURREASONS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CEXTRATOURREASONS() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, EXTRATOURREASONS_BES, EXTRATOURREASONS_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, EXTRATOURREASONS_BES, (int)EXTRATOURREASONS_ANZ, error_msg);
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
        if ( fkt_nr == 1750 ) return UniqueServerCall(1750, pos);
        if ( fkt_nr == 1749 ) return UniqueServerCall(1749, pos);
        if ( fkt_nr == 1748 ) return CursorServerCall(1748, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1751 ) return CursorServerCall(1751, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_EXTRATOURREASONS & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.EXTRATOURREASON);
        ppGStripLast(d.CSCORDERTYPE);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, EXTRATOURREASONS_BES, (int)EXTRATOURREASONS_ANZ, error_msg);
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
        CEXTRATOURREASONS c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, EXTRATOURREASONS_BES, (int)EXTRATOURREASONS_ANZ, error_msg);
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
