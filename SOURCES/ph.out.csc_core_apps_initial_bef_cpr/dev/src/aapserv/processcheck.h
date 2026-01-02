#ifndef __PP_PROCESSCHECK_H_
#define __PP_PROCESSCHECK_H_

/******************************************************************************/
/* c:\git\pharmos.outbound.csc_core_applications\dev\src\aapserv\ProcessCheck */
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of MCHECKPROCESS *********************************************/

#define L_MCHECKPROCESS_PROGRAMMNAME 15
#define L_MCHECKPROCESS_PROGRAMMPARTNER 15
#define L_MCHECKPROCESS_PID 11

/* Length-Define of MUMKPROCESSES *********************************************/

#define L_MUMKPROCESSES_UMKFILIALNR 6
#define L_MUMKPROCESSES_UMKANZAHL 6
#define L_MUMKPROCESSES_UMKRETURNSTATUS 40

/* SqlDefine of MCHECKPROCESS *************************************************/


#define MCHECKPROCESS_PLISTE \
        "AKTIVEPROZESSE.PROGRAMMNAME,"\
        "AKTIVEPROZESSE.PROGRAMMPARTNER,"\
        "AKTIVEPROZESSE.PID"

/* SqlDefine of MUMKPROCESSES *************************************************/


#define MUMKPROCESSES_PLISTE \
        "AADUMMY.UMKFILIALNR,"\
        "AADUMMY.UMKANZAHL,"\
        "AADUMMY.UMKRETURNSTATUS"

/* SqlDefine of MCHECKPROCESS *************************************************/


#define MCHECKPROCESS_UPDLISTE \
        "PROGRAMMNAME=?,"\
        "PROGRAMMPARTNER=?,"\
        "PID=?"
/* SqlDefine of MUMKPROCESSES *************************************************/


#define MUMKPROCESSES_UPDLISTE \
        "UMKFILIALNR=?,"\
        "UMKANZAHL=?,"\
        "UMKRETURNSTATUS=?"
/* SqlMacros-Define of MCHECKPROCESS ******************************************/

#define MCHECKPROCESS_ZEIGER(x) \
        :x->PROGRAMMNAME,\
        :x->PROGRAMMPARTNER,\
        :x->PID
#define MCHECKPROCESS_ZEIGERSEL(x) \
        :x->PROGRAMMNAME,\
        :x->PROGRAMMPARTNER,\
        :x->PID

/* SqlMacros-Define of MUMKPROCESSES ******************************************/

#define MUMKPROCESSES_ZEIGER(x) \
        :x->UMKFILIALNR,\
        :x->UMKANZAHL,\
        :x->UMKRETURNSTATUS
#define MUMKPROCESSES_ZEIGERSEL(x) \
        :x->UMKFILIALNR,\
        :x->UMKANZAHL,\
        :x->UMKRETURNSTATUS

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define MCHECKPROCESS_H
#define MCHECKPROCESS_ANZ ( sizeof(MCHECKPROCESS_BES) / sizeof(struct buf_desc) )
#define MUMKPROCESSES_H
#define MUMKPROCESSES_ANZ ( sizeof(MUMKPROCESSES_BES) / sizeof(struct buf_desc) )
#endif

#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of MCHECKPROCESS *******************************************/

#ifndef TRANSCLASS
typedef struct N_MCHECKPROCESS {
    char PROGRAMMNAME[16];
    char PROGRAMMPARTNER[16];
    long PID;
} mcheckprocessS;
#else /* TRANSCLASS */
typedef struct N_MCHECKPROCESS {
    char PROGRAMMNAME[16];
    char PROGRAMMPARTNER[16];
    long PID;

    bool operator == (const N_MCHECKPROCESS& right) const {
        return (
            !strcmp(PROGRAMMNAME, right.PROGRAMMNAME) &&
            !strcmp(PROGRAMMPARTNER, right.PROGRAMMPARTNER) &&
            PID == right.PID
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        strcpy(PROGRAMMNAME, " " );
        strcpy(PROGRAMMPARTNER, " " );
        PID = 0;
#endif
    }
} mcheckprocessS;
#endif /* TRANSCLASS */

/* original struct of MUMKPROCESSES *******************************************/

#ifndef TRANSCLASS
typedef struct N_MUMKPROCESSES {
    short UMKFILIALNR;
    short UMKANZAHL;
    char UMKRETURNSTATUS[41];
    long FETCH_REL;
} mumkprocessesS;
#else /* TRANSCLASS */
typedef struct N_MUMKPROCESSES {
    short UMKFILIALNR;
    short UMKANZAHL;
    char UMKRETURNSTATUS[41];
    long FETCH_REL;
    bool operator == (const N_MUMKPROCESSES& right) const {
        return (
            UMKFILIALNR == right.UMKFILIALNR &&
            UMKANZAHL == right.UMKANZAHL &&
            !strcmp(UMKRETURNSTATUS, right.UMKRETURNSTATUS)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        UMKFILIALNR = 0;
        UMKANZAHL = 0;
        strcpy(UMKRETURNSTATUS, " " );
#endif
    }
} mumkprocessesS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of MCHECKPROCESS *******************************/

struct C_MCHECKPROCESS {
    char PROGRAMMNAME[16];
    char PROGRAMMPARTNER[16];
    long PID;
};
/* Structur with real chartype of MUMKPROCESSES *******************************/

struct C_MUMKPROCESSES {
    short UMKFILIALNR;
    short UMKANZAHL;
    char UMKRETURNSTATUS[41];
    long FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of MCHECKPROCESS *****************************/

struct I_MCHECKPROCESS {
    short PROGRAMMNAME;
    short PROGRAMMPARTNER;
    short PID;
};
/* Sizetype  Structur (buf_desc) of MUMKPROCESSES *****************************/

struct I_MUMKPROCESSES {
    short UMKFILIALNR;
    short UMKANZAHL;
    short UMKRETURNSTATUS;
    short FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of MCHECKPROCESS ***************************************/

#if defined (BUF_DESC)
static struct buf_desc MCHECKPROCESS_BES [] = {
   { TYP_C, 15, 0 },
   { TYP_C, 15, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MCHECKPROCESS_BES [] = {
   { TYP_C, 15, 0 },
   { TYP_C, 15, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of MUMKPROCESSES ***************************************/

#if defined (BUF_DESC)
static struct buf_desc MUMKPROCESSES_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 40, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MUMKPROCESSES_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 40, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* FunctionNumber-Define of MCheckProcess *************************************/

#define MCHECKPROCESS_DELPROCESS 1124
#define MCHECKPROCESS_INSERT 1122
#define MCHECKPROCESS_SELPROCESS 1121
#define MCHECKPROCESS_UPDPROCESS 1123

/* FunctionNumber-Define of MUmkProcesses *************************************/

#define MUMKPROCESSES_SELLIST 1303
#define MUMKPROCESSES_STARTCALLPLAN 1304
#define MUMKPROCESSES_STARTUMKALL 1299
#define MUMKPROCESSES_STARTUMKUNIQUE 1306
#define MUMKPROCESSES_STOPCALLPLAN 1305
#define MUMKPROCESSES_STOPUMKALL 1300
#define MUMKPROCESSES_STOPUMKUNIQUE 1307

#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of MCheckProcess *********************************/

#define DelProcess 1124
#define Insert 1122
#define SelProcess 1121
#define UpdProcess 1123

/* Old-FunctionNumber-Define of MUmkProcesses *********************************/

#define SelList 1303
#define StartCallplan 1304
#define StartUmkAll 1299
#define StartUmkUnique 1306
#define StopCallplan 1305
#define StopUmkAll 1300
#define StopUmkUnique 1307

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

class CMCHECKPROCESS : public ppDadeVirtual {
public:
    mcheckprocessS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<mcheckprocessS> lst; // class list

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
                     vector< mcheckprocessS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     mcheckprocessS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< mcheckprocessS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<mcheckprocessS>::iterator
                 beginList() { return lst.begin(); }
    vector<mcheckprocessS>::iterator
                 endList  () { return lst.end  (); }

    const char*  GetProgrammname(ppString & t) const { t = s.PROGRAMMNAME; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetProgrammpartner(ppString & t) const { t = s.PROGRAMMPARTNER; t.erasespace(ppString::END); return t.c_str(); }
    long         GetPid() const { return s.PID; }

    const mcheckprocessS &
                 GetStruct() const { return s; }
    void         SetProgrammname(const ppString & t) { ppGStrCopy(s.PROGRAMMNAME, t.c_str(), L_MCHECKPROCESS_PROGRAMMNAME); }
    void         SetProgrammpartner(const ppString & t) { ppGStrCopy(s.PROGRAMMPARTNER, t.c_str(), L_MCHECKPROCESS_PROGRAMMPARTNER); }
    void         SetPid(long t) { s.PID = t; }

    void         SetStruct(const mcheckprocessS & t) { s = t; }

    int          DelProcess(int pos = 0) { return UniqueServerCall(1124, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1122, pos); Strip(s); return ret; }
    int          SelProcess(int pos = 0) { int ret = UniqueServerCall(1121, pos); Strip(s); return ret; }
    int          UpdProcess(int pos = 0) { int ret = UniqueServerCall(1123, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMCHECKPROCESS() {
        ::buf_default((void *)&s, MCHECKPROCESS_BES, MCHECKPROCESS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMCHECKPROCESS() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MCHECKPROCESS_BES, MCHECKPROCESS_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1124 ) return UniqueServerCall(1124, pos);
        if ( fkt_nr == 1122 ) return UniqueServerCall(1122, pos);
        if ( fkt_nr == 1121 ) return UniqueServerCall(1121, pos);
        if ( fkt_nr == 1123 ) return UniqueServerCall(1123, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MCHECKPROCESS & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.PROGRAMMNAME);
        ppGStripLast(d.PROGRAMMPARTNER);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MCHECKPROCESS_BES, (int)MCHECKPROCESS_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CMUMKPROCESSES : public ppDadeVirtual {
public:
    mumkprocessesS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<mumkprocessesS> lst; // class list

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
                     vector< mumkprocessesS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     mumkprocessesS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< mumkprocessesS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<mumkprocessesS>::iterator
                 beginList() { return lst.begin(); }
    vector<mumkprocessesS>::iterator
                 endList  () { return lst.end  (); }

    short        GetUmkfilialnr() const { return s.UMKFILIALNR; }
    short        GetUmkanzahl() const { return s.UMKANZAHL; }
    const char*  GetUmkreturnstatus(ppString & t) const { t = s.UMKRETURNSTATUS; t.erasespace(ppString::END); return t.c_str(); }

    const mumkprocessesS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetUmkfilialnr(short t) { s.UMKFILIALNR = t; }
    void         SetUmkanzahl(short t) { s.UMKANZAHL = t; }
    void         SetUmkreturnstatus(const ppString & t) { ppGStrCopy(s.UMKRETURNSTATUS, t.c_str(), L_MUMKPROCESSES_UMKRETURNSTATUS); }

    void         SetStruct(const mumkprocessesS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1303, FetchRel, pos); return ret; }
    int          StartCallplan(int pos = 0) { int ret = UniqueServerCall(1304, pos); Strip(s); return ret; }
    int          StartUmkAll(int pos = 0) { int ret = UniqueServerCall(1299, pos); Strip(s); return ret; }
    int          StartUmkUnique(int pos = 0) { int ret = UniqueServerCall(1306, pos); Strip(s); return ret; }
    int          StopCallplan(int pos = 0) { int ret = UniqueServerCall(1305, pos); Strip(s); return ret; }
    int          StopUmkAll(int pos = 0) { int ret = UniqueServerCall(1300, pos); Strip(s); return ret; }
    int          StopUmkUnique(int pos = 0) { int ret = UniqueServerCall(1307, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMUMKPROCESSES() {
        ::buf_default((void *)&s, MUMKPROCESSES_BES, MUMKPROCESSES_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMUMKPROCESSES() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MUMKPROCESSES_BES, MUMKPROCESSES_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MUMKPROCESSES_BES, (int)MUMKPROCESSES_ANZ, error_msg);
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
        if ( fkt_nr == 1303 ) return CursorServerCall(1303, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1304 ) return UniqueServerCall(1304, pos);
        if ( fkt_nr == 1299 ) return UniqueServerCall(1299, pos);
        if ( fkt_nr == 1306 ) return UniqueServerCall(1306, pos);
        if ( fkt_nr == 1305 ) return UniqueServerCall(1305, pos);
        if ( fkt_nr == 1300 ) return UniqueServerCall(1300, pos);
        if ( fkt_nr == 1307 ) return UniqueServerCall(1307, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MUMKPROCESSES & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.UMKRETURNSTATUS);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MUMKPROCESSES_BES, (int)MUMKPROCESSES_ANZ, error_msg);
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
        CMUMKPROCESSES c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MUMKPROCESSES_BES, (int)MUMKPROCESSES_ANZ, error_msg);
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
