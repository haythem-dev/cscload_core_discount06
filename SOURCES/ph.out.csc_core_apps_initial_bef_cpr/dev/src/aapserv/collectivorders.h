#ifndef __PP_COLLECTIVORDERS_H_
#define __PP_COLLECTIVORDERS_H_

/******************************************************************************/
/* c:\git\pharmos.outbound.csc_core_applications\dev\src\aapserv\CollectivOrders */
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of COLLORDERGRP **********************************************/

#define L_COLLORDERGRP_COLLORDERGRPID 11
#define L_COLLORDERGRP_COLLORDERGRPNAME 30
#define L_COLLORDERGRP_BRANCHNO 6

/* Length-Define of COLLORDERGRPMEM *******************************************/

#define L_COLLORDERGRPMEM_BRANCHNO 6
#define L_COLLORDERGRPMEM_IDFNR 11
#define L_COLLORDERGRPMEM_MATCHCODE 12
#define L_COLLORDERGRPMEM_CUSTOMERNO 11
#define L_COLLORDERGRPMEM_COLLORDERGRPID 11
#define L_COLLORDERGRPMEM_NAMEAPO 40
#define L_COLLORDERGRPMEM_NAMEINHABER 30
#define L_COLLORDERGRPMEM_STRASSE 30
#define L_COLLORDERGRPMEM_ORT 30
#define L_COLLORDERGRPMEM_KZKDKLASSE 3
#define L_COLLORDERGRPMEM_SKDKUNDEAEGESPERRT 1

/* SqlDefine of COLLORDERGRP **************************************************/


#define COLLORDERGRP_PLISTE \
        "COLLORDERGRP.COLLORDERGRPID,"\
        "COLLORDERGRP.COLLORDERGRPNAME,"\
        "COLLORDERGRP.BRANCHNO"

/* SqlDefine of COLLORDERGRPMEM ***********************************************/


#define COLLORDERGRPMEM_PLISTE \
        "COLLORDERGRPMEM.BRANCHNO,"\
        "KUNDE.IDFNR,"\
        "KUNDE.MATCHCODE,"\
        "COLLORDERGRPMEM.CUSTOMERNO,"\
        "COLLORDERGRPMEM.COLLORDERGRPID,"\
        "KUNDE.NAMEAPO,"\
        "KUNDE.NAMEINHABER,"\
        "KUNDE.STRASSE,"\
        "KUNDE.ORT,"\
        "KUNDE.KZKDKLASSE,"\
        "KUNDESCHALTER.SKDKUNDEAEGESPERRT"

/* SqlDefine of COLLORDERGRP **************************************************/


#define COLLORDERGRP_UPDLISTE \
        "COLLORDERGRPID=?,"\
        "COLLORDERGRPNAME=?,"\
        "BRANCHNO=?"
/* SqlDefine of COLLORDERGRPMEM ***********************************************/


#define COLLORDERGRPMEM_UPDLISTE \
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "COLLORDERGRPID=?"
/* SqlMacros-Define of COLLORDERGRP *******************************************/

#define COLLORDERGRP_ZEIGER(x) \
        :x->COLLORDERGRPID,\
        :x->COLLORDERGRPNAME,\
        :x->BRANCHNO
#define COLLORDERGRP_ZEIGERSEL(x) \
        :x->COLLORDERGRPID,\
        :x->COLLORDERGRPNAME,\
        :x->BRANCHNO

/* SqlMacros-Define of COLLORDERGRPMEM ****************************************/

#define COLLORDERGRPMEM_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->COLLORDERGRPID
#define COLLORDERGRPMEM_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->IDFNR,\
        :x->MATCHCODE,\
        :x->CUSTOMERNO,\
        :x->COLLORDERGRPID,\
        :x->NAMEAPO,\
        :x->NAMEINHABER,\
        :x->STRASSE,\
        :x->ORT,\
        :x->KZKDKLASSE,\
        :x->SKDKUNDEAEGESPERRT

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define COLLORDERGRP_H
#define COLLORDERGRP_ANZ ( sizeof(COLLORDERGRP_BES) / sizeof(struct buf_desc) )
#define COLLORDERGRPMEM_H
#define COLLORDERGRPMEM_ANZ ( sizeof(COLLORDERGRPMEM_BES) / sizeof(struct buf_desc) )
#endif

#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of COLLORDERGRP ********************************************/

#ifndef TRANSCLASS
typedef struct N_COLLORDERGRP {
    long COLLORDERGRPID;
    char COLLORDERGRPNAME[31];
    short BRANCHNO;
    long FETCH_REL;
} collordergrpS;
#else /* TRANSCLASS */
typedef struct N_COLLORDERGRP {
    long COLLORDERGRPID;
    char COLLORDERGRPNAME[31];
    short BRANCHNO;
    long FETCH_REL;
    bool operator == (const N_COLLORDERGRP& right) const {
        return (
            COLLORDERGRPID == right.COLLORDERGRPID &&
            !strcmp(COLLORDERGRPNAME, right.COLLORDERGRPNAME) &&
            BRANCHNO == right.BRANCHNO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        COLLORDERGRPID = 0;
        strcpy(COLLORDERGRPNAME, " " );
        BRANCHNO = 0;
#endif
    }
} collordergrpS;
#endif /* TRANSCLASS */

/* original struct of COLLORDERGRPMEM *****************************************/

#ifndef TRANSCLASS
typedef struct N_COLLORDERGRPMEM {
    short BRANCHNO;
    long IDFNR;
    char MATCHCODE[13];
    long CUSTOMERNO;
    long COLLORDERGRPID;
    char NAMEAPO[41];
    char NAMEINHABER[31];
    char STRASSE[31];
    char ORT[31];
    char KZKDKLASSE[4];
    char SKDKUNDEAEGESPERRT[2];
    long FETCH_REL;
} collordergrpmemS;
#else /* TRANSCLASS */
typedef struct N_COLLORDERGRPMEM {
    short BRANCHNO;
    long IDFNR;
    char MATCHCODE[13];
    long CUSTOMERNO;
    long COLLORDERGRPID;
    char NAMEAPO[41];
    char NAMEINHABER[31];
    char STRASSE[31];
    char ORT[31];
    char KZKDKLASSE[4];
    char SKDKUNDEAEGESPERRT[2];
    long FETCH_REL;
    bool operator == (const N_COLLORDERGRPMEM& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            IDFNR == right.IDFNR &&
            !strcmp(MATCHCODE, right.MATCHCODE) &&
            CUSTOMERNO == right.CUSTOMERNO &&
            COLLORDERGRPID == right.COLLORDERGRPID &&
            !strcmp(NAMEAPO, right.NAMEAPO) &&
            !strcmp(NAMEINHABER, right.NAMEINHABER) &&
            !strcmp(STRASSE, right.STRASSE) &&
            !strcmp(ORT, right.ORT) &&
            !strcmp(KZKDKLASSE, right.KZKDKLASSE) &&
            !strcmp(SKDKUNDEAEGESPERRT, right.SKDKUNDEAEGESPERRT)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        IDFNR = 0;
        strcpy(MATCHCODE, " " );
        CUSTOMERNO = 0;
        COLLORDERGRPID = 0;
        strcpy(NAMEAPO, " " );
        strcpy(NAMEINHABER, " " );
        strcpy(STRASSE, " " );
        strcpy(ORT, " " );
        strcpy(KZKDKLASSE, " " );
        strcpy(SKDKUNDEAEGESPERRT, " " );
#endif
    }
} collordergrpmemS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of COLLORDERGRP ********************************/

struct C_COLLORDERGRP {
    long COLLORDERGRPID;
    char COLLORDERGRPNAME[31];
    short BRANCHNO;
    long FETCH_REL;
};
/* Structur with real chartype of COLLORDERGRPMEM *****************************/

struct C_COLLORDERGRPMEM {
    short BRANCHNO;
    long IDFNR;
    char MATCHCODE[13];
    long CUSTOMERNO;
    long COLLORDERGRPID;
    char NAMEAPO[41];
    char NAMEINHABER[31];
    char STRASSE[31];
    char ORT[31];
    char KZKDKLASSE[4];
    char SKDKUNDEAEGESPERRT;
    long FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of COLLORDERGRP ******************************/

struct I_COLLORDERGRP {
    short COLLORDERGRPID;
    short COLLORDERGRPNAME;
    short BRANCHNO;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of COLLORDERGRPMEM ***************************/

struct I_COLLORDERGRPMEM {
    short BRANCHNO;
    short IDFNR;
    short MATCHCODE;
    short CUSTOMERNO;
    short COLLORDERGRPID;
    short NAMEAPO;
    short NAMEINHABER;
    short STRASSE;
    short ORT;
    short KZKDKLASSE;
    short SKDKUNDEAEGESPERRT;
    short FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of COLLORDERGRP ****************************************/

#if defined (BUF_DESC)
static struct buf_desc COLLORDERGRP_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc COLLORDERGRP_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of COLLORDERGRPMEM *************************************/

#if defined (BUF_DESC)
static struct buf_desc COLLORDERGRPMEM_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 12, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 40, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 3, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc COLLORDERGRPMEM_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 12, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 40, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 3, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* FunctionNumber-Define of CollOrderGrp **************************************/

#define COLLORDERGRP_DELETE 1435
#define COLLORDERGRP_INSERT 1432
#define COLLORDERGRP_SELLIST 1433
#define COLLORDERGRP_UPDATE 1434

/* FunctionNumber-Define of CollOrderGrpMem ***********************************/

#define COLLORDERGRPMEM_DELETE 1437
#define COLLORDERGRPMEM_INSERT 1436
#define COLLORDERGRPMEM_SELLIST 1438

#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of CollOrderGrp **********************************/

#define Delete 1435
#define Insert 1432
#define SelList 1433
#define Update 1434

/* Old-FunctionNumber-Define of CollOrderGrpMem *******************************/

#define Delete 1437
#define Insert 1436
#define SelList 1438

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

class CCOLLORDERGRP : public ppDadeVirtual {
public:
    collordergrpS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<collordergrpS> lst; // class list

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
                     vector< collordergrpS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     collordergrpS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< collordergrpS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<collordergrpS>::iterator
                 beginList() { return lst.begin(); }
    vector<collordergrpS>::iterator
                 endList  () { return lst.end  (); }

    long         GetCollordergrpid() const { return s.COLLORDERGRPID; }
    const char*  GetCollordergrpname(ppString & t) const { t = s.COLLORDERGRPNAME; t.erasespace(ppString::END); return t.c_str(); }
    short        GetBranchno() const { return s.BRANCHNO; }

    const collordergrpS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetCollordergrpid(long t) { s.COLLORDERGRPID = t; }
    void         SetCollordergrpname(const ppString & t) { ppGStrCopy(s.COLLORDERGRPNAME, t.c_str(), L_COLLORDERGRP_COLLORDERGRPNAME); }
    void         SetBranchno(short t) { s.BRANCHNO = t; }

    void         SetStruct(const collordergrpS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          Delete(int pos = 0) { return UniqueServerCall(1435, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1432, pos); Strip(s); return ret; }
    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1433, FetchRel, pos); return ret; }
    int          Update(int pos = 0) { int ret = UniqueServerCall(1434, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCOLLORDERGRP() {
        ::buf_default((void *)&s, COLLORDERGRP_BES, COLLORDERGRP_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCOLLORDERGRP() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, COLLORDERGRP_BES, COLLORDERGRP_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, COLLORDERGRP_BES, (int)COLLORDERGRP_ANZ, error_msg);
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
        if ( fkt_nr == 1435 ) return UniqueServerCall(1435, pos);
        if ( fkt_nr == 1432 ) return UniqueServerCall(1432, pos);
        if ( fkt_nr == 1433 ) return CursorServerCall(1433, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1434 ) return UniqueServerCall(1434, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_COLLORDERGRP & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.COLLORDERGRPNAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, COLLORDERGRP_BES, (int)COLLORDERGRP_ANZ, error_msg);
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
        CCOLLORDERGRP c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, COLLORDERGRP_BES, (int)COLLORDERGRP_ANZ, error_msg);
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

class CCOLLORDERGRPMEM : public ppDadeVirtual {
public:
    collordergrpmemS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<collordergrpmemS> lst; // class list

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
                     vector< collordergrpmemS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     collordergrpmemS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< collordergrpmemS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<collordergrpmemS>::iterator
                 beginList() { return lst.begin(); }
    vector<collordergrpmemS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetIdfnr() const { return s.IDFNR; }
    const char*  GetMatchcode(ppString & t) const { t = s.MATCHCODE; t.erasespace(ppString::END); return t.c_str(); }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    long         GetCollordergrpid() const { return s.COLLORDERGRPID; }
    const char*  GetNameapo(ppString & t) const { t = s.NAMEAPO; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetNameinhaber(ppString & t) const { t = s.NAMEINHABER; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetStrasse(ppString & t) const { t = s.STRASSE; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetOrt(ppString & t) const { t = s.ORT; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetKzkdklasse(ppString & t) const { t = s.KZKDKLASSE; t.erasespace(ppString::END); return t.c_str(); }
    char         GetSkdkundeaegesperrt() const { return s.SKDKUNDEAEGESPERRT[0]; }

    const collordergrpmemS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetIdfnr(long t) { s.IDFNR = t; }
    void         SetMatchcode(const ppString & t) { ppGStrCopy(s.MATCHCODE, t.c_str(), L_COLLORDERGRPMEM_MATCHCODE); }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetCollordergrpid(long t) { s.COLLORDERGRPID = t; }
    void         SetNameapo(const ppString & t) { ppGStrCopy(s.NAMEAPO, t.c_str(), L_COLLORDERGRPMEM_NAMEAPO); }
    void         SetNameinhaber(const ppString & t) { ppGStrCopy(s.NAMEINHABER, t.c_str(), L_COLLORDERGRPMEM_NAMEINHABER); }
    void         SetStrasse(const ppString & t) { ppGStrCopy(s.STRASSE, t.c_str(), L_COLLORDERGRPMEM_STRASSE); }
    void         SetOrt(const ppString & t) { ppGStrCopy(s.ORT, t.c_str(), L_COLLORDERGRPMEM_ORT); }
    void         SetKzkdklasse(const ppString & t) { ppGStrCopy(s.KZKDKLASSE, t.c_str(), L_COLLORDERGRPMEM_KZKDKLASSE); }
    void         SetSkdkundeaegesperrt(char t) { s.SKDKUNDEAEGESPERRT[0] = t; s.SKDKUNDEAEGESPERRT[1] = '\0';}

    void         SetStruct(const collordergrpmemS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          Delete(int pos = 0) { return UniqueServerCall(1437, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1436, pos); Strip(s); return ret; }
    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1438, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCOLLORDERGRPMEM() {
        ::buf_default((void *)&s, COLLORDERGRPMEM_BES, COLLORDERGRPMEM_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCOLLORDERGRPMEM() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, COLLORDERGRPMEM_BES, COLLORDERGRPMEM_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, COLLORDERGRPMEM_BES, (int)COLLORDERGRPMEM_ANZ, error_msg);
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
        if ( fkt_nr == 1437 ) return UniqueServerCall(1437, pos);
        if ( fkt_nr == 1436 ) return UniqueServerCall(1436, pos);
        if ( fkt_nr == 1438 ) return CursorServerCall(1438, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_COLLORDERGRPMEM & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.MATCHCODE);
        ppGStripLast(d.NAMEAPO);
        ppGStripLast(d.NAMEINHABER);
        ppGStripLast(d.STRASSE);
        ppGStripLast(d.ORT);
        ppGStripLast(d.KZKDKLASSE);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, COLLORDERGRPMEM_BES, (int)COLLORDERGRPMEM_ANZ, error_msg);
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
        CCOLLORDERGRPMEM c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, COLLORDERGRPMEM_BES, (int)COLLORDERGRPMEM_ANZ, error_msg);
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
