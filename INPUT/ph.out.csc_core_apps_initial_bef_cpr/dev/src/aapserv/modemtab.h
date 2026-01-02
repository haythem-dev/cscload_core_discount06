#ifndef __PP_MODEMTAB_H_
#define __PP_MODEMTAB_H_

/******************************************************************************/
/**/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of MODEMTAB **************************************************/

#define L_MODEMTAB_FILIALNR 6
#define L_MODEMTAB_GERAETEID 4

/* SqlDefine of MODEMTAB ******************************************************/


#define MODEMTAB_PLISTE \
        "MODEMTAB.FILIALNR,"\
        "MODEMTAB.GERAETEID"

/* SqlDefine of MODEMTAB ******************************************************/


#define MODEMTAB_UPDLISTE \
        "FILIALNR=?,"\
        "GERAETEID=?"
/* SqlMacros-Define of MODEMTAB ***********************************************/

#define MODEMTAB_ZEIGER(x) \
        :x->FILIALNR,\
        :x->GERAETEID
#define MODEMTAB_ZEIGERSEL(x) \
        :x->FILIALNR,\
        :x->GERAETEID

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define MODEMTAB_H
#define MODEMTAB_ANZ ( sizeof(MODEMTAB_BES) / sizeof(struct buf_desc) )
#endif

#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of MODEMTAB ************************************************/

#ifndef TRANSCLASS
typedef struct N_MODEMTAB {
    short FILIALNR;
    char GERAETEID[5];
    long FETCH_REL;
} modemtabS;
#else /* TRANSCLASS */
typedef struct N_MODEMTAB {
    short FILIALNR;
    char GERAETEID[5];
    long FETCH_REL;
    bool operator == (const N_MODEMTAB& right) const {
        return (
            FILIALNR == right.FILIALNR &&
            !strcmp(GERAETEID, right.GERAETEID)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        FILIALNR = 0;
        strcpy(GERAETEID, " " );
#endif
    }
} modemtabS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of MODEMTAB ************************************/

struct C_MODEMTAB {
    short FILIALNR;
    char GERAETEID[5];
    long FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of MODEMTAB **********************************/

struct I_MODEMTAB {
    short FILIALNR;
    short GERAETEID;
    short FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of MODEMTAB ********************************************/

#if defined (BUF_DESC)
static struct buf_desc MODEMTAB_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 4, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MODEMTAB_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 4, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* FunctionNumber-Define of ModemTab ******************************************/

#define MODEMTAB_DELETEMODEM 1025
#define MODEMTAB_INSERT 1027
#define MODEMTAB_SELALL 1023

#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of ModemTab **************************************/

#define DeleteModem 1025
#define Insert 1027
#define SelAll 1023

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

class CMODEMTAB : public ppDadeVirtual {
public:
    modemtabS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<modemtabS> lst; // class list

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
                     vector< modemtabS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     modemtabS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< modemtabS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<modemtabS>::iterator
                 beginList() { return lst.begin(); }
    vector<modemtabS>::iterator
                 endList  () { return lst.end  (); }

    short        GetFilialnr() const { return s.FILIALNR; }
    const char*  GetGeraeteid(ppString & t) const { t = s.GERAETEID; t.erasespace(ppString::END); return t.c_str(); }

    const modemtabS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetGeraeteid(const ppString & t) { ppGStrCopy(s.GERAETEID, t.c_str(), L_MODEMTAB_GERAETEID); }

    void         SetStruct(const modemtabS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          DeleteModem(int pos = 0) { return UniqueServerCall(1025, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1027, pos); Strip(s); return ret; }
    int          SelAll(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1023, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMODEMTAB() {
        ::buf_default((void *)&s, MODEMTAB_BES, MODEMTAB_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMODEMTAB() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MODEMTAB_BES, MODEMTAB_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MODEMTAB_BES, (int)MODEMTAB_ANZ, error_msg);
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
        if ( fkt_nr == 1025 ) return UniqueServerCall(1025, pos);
        if ( fkt_nr == 1027 ) return UniqueServerCall(1027, pos);
        if ( fkt_nr == 1023 ) return CursorServerCall(1023, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MODEMTAB & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.GERAETEID);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MODEMTAB_BES, (int)MODEMTAB_ANZ, error_msg);
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
        CMODEMTAB c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MODEMTAB_BES, (int)MODEMTAB_ANZ, error_msg);
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
