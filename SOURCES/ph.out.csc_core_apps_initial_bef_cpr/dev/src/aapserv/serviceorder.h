#ifndef __PP_SERVICEORDER_H_
#define __PP_SERVICEORDER_H_

/******************************************************************************/
/* c:\git\pharmos.outbound.csc_core_applications\dev\src\aapserv\ServiceOrder */
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of SERVICEMEMBER *********************************************/

#define L_SERVICEMEMBER_SERVICE_NO 6
#define L_SERVICEMEMBER_NAME 30
#define L_SERVICEMEMBER_SERVICETYPENO 6

/* Length-Define of SERVICEORDER **********************************************/

#define L_SERVICEORDER_SERVICETYPENO 6
#define L_SERVICEORDER_NAME 30
#define L_SERVICEORDER_ORDER_TYPE 2

/* SqlDefine of SERVICEMEMBER *************************************************/


#define SERVICEMEMBER_PLISTE \
        "SERVICES.SERVICE_NO,"\
        "SERVICES.NAME,"\
        "SERVICES.SERVICETYPENO"

/* SqlDefine of SERVICEORDER **************************************************/


#define SERVICEORDER_PLISTE \
        "SERVICETYPES.SERVICETYPENO,"\
        "SERVICETYPES.NAME,"\
        "SERVICETYPES.ORDER_TYPE"

/* SqlDefine of SERVICEMEMBER *************************************************/


#define SERVICEMEMBER_UPDLISTE \
        "SERVICE_NO=?,"\
        "NAME=?,"\
        "SERVICETYPENO=?"
/* SqlDefine of SERVICEORDER **************************************************/


#define SERVICEORDER_UPDLISTE \
        "SERVICETYPENO=?,"\
        "NAME=?,"\
        "ORDER_TYPE=?"
/* SqlMacros-Define of SERVICEMEMBER ******************************************/

#define SERVICEMEMBER_ZEIGER(x) \
        :x->SERVICE_NO,\
        :x->NAME,\
        :x->SERVICETYPENO
#define SERVICEMEMBER_ZEIGERSEL(x) \
        :x->SERVICE_NO,\
        :x->NAME,\
        :x->SERVICETYPENO

/* SqlMacros-Define of SERVICEORDER *******************************************/

#define SERVICEORDER_ZEIGER(x) \
        :x->SERVICETYPENO,\
        :x->NAME,\
        :x->ORDER_TYPE
#define SERVICEORDER_ZEIGERSEL(x) \
        :x->SERVICETYPENO,\
        :x->NAME,\
        :x->ORDER_TYPE

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define SERVICEMEMBER_H
#define SERVICEMEMBER_ANZ ( sizeof(SERVICEMEMBER_BES) / sizeof(struct buf_desc) )
#define SERVICEORDER_H
#define SERVICEORDER_ANZ ( sizeof(SERVICEORDER_BES) / sizeof(struct buf_desc) )
#endif

#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of SERVICEMEMBER *******************************************/

#ifndef TRANSCLASS
typedef struct N_SERVICEMEMBER {
    short SERVICE_NO;
    char NAME[31];
    short SERVICETYPENO;
    long FETCH_REL;
} servicememberS;
#else /* TRANSCLASS */
typedef struct N_SERVICEMEMBER {
    short SERVICE_NO;
    char NAME[31];
    short SERVICETYPENO;
    long FETCH_REL;
    bool operator == (const N_SERVICEMEMBER& right) const {
        return (
            SERVICE_NO == right.SERVICE_NO &&
            !strcmp(NAME, right.NAME) &&
            SERVICETYPENO == right.SERVICETYPENO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        SERVICE_NO = 0;
        strcpy(NAME, " " );
        SERVICETYPENO = 0;
#endif
    }
} servicememberS;
#endif /* TRANSCLASS */

/* original struct of SERVICEORDER ********************************************/

#ifndef TRANSCLASS
typedef struct N_SERVICEORDER {
    short SERVICETYPENO;
    char NAME[31];
    char ORDER_TYPE[3];
} serviceorderS;
#else /* TRANSCLASS */
typedef struct N_SERVICEORDER {
    short SERVICETYPENO;
    char NAME[31];
    char ORDER_TYPE[3];

    bool operator == (const N_SERVICEORDER& right) const {
        return (
            SERVICETYPENO == right.SERVICETYPENO &&
            !strcmp(NAME, right.NAME) &&
            !strcmp(ORDER_TYPE, right.ORDER_TYPE)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        SERVICETYPENO = 0;
        strcpy(NAME, " " );
        strcpy(ORDER_TYPE, " " );
#endif
    }
} serviceorderS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of SERVICEMEMBER *******************************/

struct C_SERVICEMEMBER {
    short SERVICE_NO;
    char NAME[31];
    short SERVICETYPENO;
    long FETCH_REL;
};
/* Structur with real chartype of SERVICEORDER ********************************/

struct C_SERVICEORDER {
    short SERVICETYPENO;
    char NAME[31];
    char ORDER_TYPE[3];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of SERVICEMEMBER *****************************/

struct I_SERVICEMEMBER {
    short SERVICE_NO;
    short NAME;
    short SERVICETYPENO;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of SERVICEORDER ******************************/

struct I_SERVICEORDER {
    short SERVICETYPENO;
    short NAME;
    short ORDER_TYPE;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of SERVICEMEMBER ***************************************/

#if defined (BUF_DESC)
static struct buf_desc SERVICEMEMBER_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc SERVICEMEMBER_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of SERVICEORDER ****************************************/

#if defined (BUF_DESC)
static struct buf_desc SERVICEORDER_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 2, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc SERVICEORDER_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 2, 0 },
};
#endif

/* FunctionNumber-Define of ServiceMember *************************************/

#define SERVICEMEMBER_SELLIST 1524

/* FunctionNumber-Define of ServiceOrder **************************************/

#define SERVICEORDER_SELTYPE 1523

#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of ServiceMember *********************************/

#define SelList 1524

/* Old-FunctionNumber-Define of ServiceOrder **********************************/

#define SelType 1523

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

class CSERVICEMEMBER : public ppDadeVirtual {
public:
    servicememberS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<servicememberS> lst; // class list

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
                     vector< servicememberS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     servicememberS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< servicememberS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<servicememberS>::iterator
                 beginList() { return lst.begin(); }
    vector<servicememberS>::iterator
                 endList  () { return lst.end  (); }

    short        GetService_no() const { return s.SERVICE_NO; }
    const char*  GetName(ppString & t) const { t = s.NAME; t.erasespace(ppString::END); return t.c_str(); }
    short        GetServicetypeno() const { return s.SERVICETYPENO; }

    const servicememberS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetService_no(short t) { s.SERVICE_NO = t; }
    void         SetName(const ppString & t) { ppGStrCopy(s.NAME, t.c_str(), L_SERVICEMEMBER_NAME); }
    void         SetServicetypeno(short t) { s.SERVICETYPENO = t; }

    void         SetStruct(const servicememberS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1524, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CSERVICEMEMBER() {
        ::buf_default((void *)&s, SERVICEMEMBER_BES, SERVICEMEMBER_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CSERVICEMEMBER() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, SERVICEMEMBER_BES, SERVICEMEMBER_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, SERVICEMEMBER_BES, (int)SERVICEMEMBER_ANZ, error_msg);
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
        if ( fkt_nr == 1524 ) return CursorServerCall(1524, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_SERVICEMEMBER & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.NAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, SERVICEMEMBER_BES, (int)SERVICEMEMBER_ANZ, error_msg);
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
        CSERVICEMEMBER c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, SERVICEMEMBER_BES, (int)SERVICEMEMBER_ANZ, error_msg);
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

class CSERVICEORDER : public ppDadeVirtual {
public:
    serviceorderS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<serviceorderS> lst; // class list

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
                     vector< serviceorderS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     serviceorderS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< serviceorderS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<serviceorderS>::iterator
                 beginList() { return lst.begin(); }
    vector<serviceorderS>::iterator
                 endList  () { return lst.end  (); }

    short        GetServicetypeno() const { return s.SERVICETYPENO; }
    const char*  GetName(ppString & t) const { t = s.NAME; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetOrder_type(ppString & t) const { t = s.ORDER_TYPE; t.erasespace(ppString::END); return t.c_str(); }

    const serviceorderS &
                 GetStruct() const { return s; }
    void         SetServicetypeno(short t) { s.SERVICETYPENO = t; }
    void         SetName(const ppString & t) { ppGStrCopy(s.NAME, t.c_str(), L_SERVICEORDER_NAME); }
    void         SetOrder_type(const ppString & t) { ppGStrCopy(s.ORDER_TYPE, t.c_str(), L_SERVICEORDER_ORDER_TYPE); }

    void         SetStruct(const serviceorderS & t) { s = t; }

    int          SelType(int pos = 0) { int ret = UniqueServerCall(1523, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CSERVICEORDER() {
        ::buf_default((void *)&s, SERVICEORDER_BES, SERVICEORDER_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CSERVICEORDER() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, SERVICEORDER_BES, SERVICEORDER_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1523 ) return UniqueServerCall(1523, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_SERVICEORDER & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.NAME);
        ppGStripLast(d.ORDER_TYPE);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, SERVICEORDER_BES, (int)SERVICEORDER_ANZ, error_msg);
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
