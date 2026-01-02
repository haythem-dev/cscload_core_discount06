#ifndef __PP_RANGES_H_
#define __PP_RANGES_H_

/******************************************************************************/
/* c:\git\pharmos.outbound.csc_core_applications\dev\src\aapserv\Ranges *******/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of DISCOUNTGROUP *********************************************/

#define L_DISCOUNTGROUP_BRANCHNO 6
#define L_DISCOUNTGROUP_DISCOUNTGRPNO 11
#define L_DISCOUNTGROUP_DESCRIPTION 40

/* Length-Define of RANGEMEMBERS **********************************************/

#define L_RANGEMEMBERS_BRANCHNO 6
#define L_RANGEMEMBERS_DISCOUNTGRPNO 11
#define L_RANGEMEMBERS_PREISEKAPO 9
#define N_RANGEMEMBERS_PREISEKAPO 2
#define L_RANGEMEMBERS_MANUFACTURERNO 11
#define L_RANGEMEMBERS_ARTIKEL_NR 11
#define L_RANGEMEMBERS_BESTAND 11
#define L_RANGEMEMBERS_EINHEIT 9
#define L_RANGEMEMBERS_ARTIKEL_NAME 30

/* SqlDefine of DISCOUNTGROUP *************************************************/


#define DISCOUNTGROUP_PLISTE \
        "DISCOUNTGRP.BRANCHNO,"\
        "DISCOUNTGRP.DISCOUNTGRPNO,"\
        "DISCOUNTGRP.DESCRIPTION"

/* SqlDefine of RANGEMEMBERS **************************************************/


#define RANGEMEMBERS_PLISTE \
        "DISCOUNTGRPMEM.BRANCHNO,"\
        "DISCOUNTGRPMEM.DISCOUNTGRPNO,"\
        "ARTIKELPREIS.PREISEKAPO,"\
        "DISCOUNTGRPMEM.MANUFACTURERNO,"\
        "ARTIKELZENTRAL.ARTIKEL_NR,"\
        "ARTIKELLOKAL.BESTAND,"\
        "ARTIKELZENTRAL.EINHEIT,"\
        "ARTIKELZENTRAL.ARTIKEL_NAME"

/* SqlDefine of DISCOUNTGROUP *************************************************/


#define DISCOUNTGROUP_UPDLISTE \
        "BRANCHNO=?,"\
        "DISCOUNTGRPNO=?,"\
        "DESCRIPTION=?"
/* SqlDefine of RANGEMEMBERS **************************************************/


#define RANGEMEMBERS_UPDLISTE \
        "BRANCHNO=?,"\
        "DISCOUNTGRPNO=?,"\
        "PREISEKAPO=?,"\
        "MANUFACTURERNO=?,"\
        "ARTIKEL_NR=?,"\
        "BESTAND=?,"\
        "EINHEIT=?,"\
        "ARTIKEL_NAME=?"
/* SqlMacros-Define of DISCOUNTGROUP ******************************************/

#define DISCOUNTGROUP_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->DISCOUNTGRPNO,\
        :x->DESCRIPTION
#define DISCOUNTGROUP_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->DISCOUNTGRPNO,\
        :x->DESCRIPTION

/* SqlMacros-Define of RANGEMEMBERS *******************************************/

#define RANGEMEMBERS_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->DISCOUNTGRPNO,\
        :x->PREISEKAPO,\
        :x->MANUFACTURERNO,\
        :x->ARTIKEL_NR,\
        :x->BESTAND,\
        :x->EINHEIT,\
        :x->ARTIKEL_NAME
#define RANGEMEMBERS_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->DISCOUNTGRPNO,\
        :x->PREISEKAPO,\
        :x->MANUFACTURERNO,\
        :x->ARTIKEL_NR,\
        :x->BESTAND,\
        :x->EINHEIT,\
        :x->ARTIKEL_NAME

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define DISCOUNTGROUP_H
#define DISCOUNTGROUP_ANZ ( sizeof(DISCOUNTGROUP_BES) / sizeof(struct buf_desc) )
#define RANGEMEMBERS_H
#define RANGEMEMBERS_ANZ ( sizeof(RANGEMEMBERS_BES) / sizeof(struct buf_desc) )
#endif

#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of DISCOUNTGROUP *******************************************/

#ifndef TRANSCLASS
typedef struct N_DISCOUNTGROUP {
    short BRANCHNO;
    long DISCOUNTGRPNO;
    char DESCRIPTION[41];
} discountgroupS;
#else /* TRANSCLASS */
typedef struct N_DISCOUNTGROUP {
    short BRANCHNO;
    long DISCOUNTGRPNO;
    char DESCRIPTION[41];

    bool operator == (const N_DISCOUNTGROUP& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            DISCOUNTGRPNO == right.DISCOUNTGRPNO &&
            !strcmp(DESCRIPTION, right.DESCRIPTION)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        DISCOUNTGRPNO = 0;
        strcpy(DESCRIPTION, " " );
#endif
    }
} discountgroupS;
#endif /* TRANSCLASS */

/* original struct of RANGEMEMBERS ********************************************/

#ifndef TRANSCLASS
typedef struct N_RANGEMEMBERS {
    short BRANCHNO;
    long DISCOUNTGRPNO;
    double PREISEKAPO;
    long MANUFACTURERNO;
    long ARTIKEL_NR;
    long BESTAND;
    char EINHEIT[10];
    char ARTIKEL_NAME[31];
    long FETCH_REL;
} rangemembersS;
#else /* TRANSCLASS */
typedef struct N_RANGEMEMBERS {
    short BRANCHNO;
    long DISCOUNTGRPNO;
    double PREISEKAPO;
    long MANUFACTURERNO;
    long ARTIKEL_NR;
    long BESTAND;
    char EINHEIT[10];
    char ARTIKEL_NAME[31];
    long FETCH_REL;
    bool operator == (const N_RANGEMEMBERS& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            DISCOUNTGRPNO == right.DISCOUNTGRPNO &&
            PREISEKAPO == right.PREISEKAPO &&
            MANUFACTURERNO == right.MANUFACTURERNO &&
            ARTIKEL_NR == right.ARTIKEL_NR &&
            BESTAND == right.BESTAND &&
            !strcmp(EINHEIT, right.EINHEIT) &&
            !strcmp(ARTIKEL_NAME, right.ARTIKEL_NAME)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        DISCOUNTGRPNO = 0;
        PREISEKAPO = 0;
        MANUFACTURERNO = 0;
        ARTIKEL_NR = 0;
        BESTAND = 0;
        strcpy(EINHEIT, " " );
        strcpy(ARTIKEL_NAME, " " );
#endif
    }
} rangemembersS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of DISCOUNTGROUP *******************************/

struct C_DISCOUNTGROUP {
    short BRANCHNO;
    long DISCOUNTGRPNO;
    char DESCRIPTION[41];
};
/* Structur with real chartype of RANGEMEMBERS ********************************/

struct C_RANGEMEMBERS {
    short BRANCHNO;
    long DISCOUNTGRPNO;
    double PREISEKAPO;
    long MANUFACTURERNO;
    long ARTIKEL_NR;
    long BESTAND;
    char EINHEIT[10];
    char ARTIKEL_NAME[31];
    long FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of DISCOUNTGROUP *****************************/

struct I_DISCOUNTGROUP {
    short BRANCHNO;
    short DISCOUNTGRPNO;
    short DESCRIPTION;
};
/* Sizetype  Structur (buf_desc) of RANGEMEMBERS ******************************/

struct I_RANGEMEMBERS {
    short BRANCHNO;
    short DISCOUNTGRPNO;
    short PREISEKAPO;
    short MANUFACTURERNO;
    short ARTIKEL_NR;
    short BESTAND;
    short EINHEIT;
    short ARTIKEL_NAME;
    short FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of DISCOUNTGROUP ***************************************/

#if defined (BUF_DESC)
static struct buf_desc DISCOUNTGROUP_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 40, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc DISCOUNTGROUP_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 40, 0 },
};
#endif

/* Structur (buf_desc) of RANGEMEMBERS ****************************************/

#if defined (BUF_DESC)
static struct buf_desc RANGEMEMBERS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 9, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc RANGEMEMBERS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 9, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* FunctionNumber-Define of DiscountGroup *************************************/

#define DISCOUNTGROUP_SELGROUP 1596

/* FunctionNumber-Define of RangeMembers **************************************/

#define RANGEMEMBERS_SELARTICLE 1597
#define RANGEMEMBERS_SELMANU 1598

#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of DiscountGroup *********************************/

#define Selgroup 1596

/* Old-FunctionNumber-Define of RangeMembers **********************************/

#define SelArticle 1597
#define SelManu 1598

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

class CDISCOUNTGROUP : public ppDadeVirtual {
public:
    discountgroupS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<discountgroupS> lst; // class list

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
                     vector< discountgroupS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     discountgroupS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< discountgroupS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<discountgroupS>::iterator
                 beginList() { return lst.begin(); }
    vector<discountgroupS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetDiscountgrpno() const { return s.DISCOUNTGRPNO; }
    const char*  GetDescription(ppString & t) const { t = s.DESCRIPTION; t.erasespace(ppString::END); return t.c_str(); }

    const discountgroupS &
                 GetStruct() const { return s; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetDiscountgrpno(long t) { s.DISCOUNTGRPNO = t; }
    void         SetDescription(const ppString & t) { ppGStrCopy(s.DESCRIPTION, t.c_str(), L_DISCOUNTGROUP_DESCRIPTION); }

    void         SetStruct(const discountgroupS & t) { s = t; }

    int          Selgroup(int pos = 0) { int ret = UniqueServerCall(1596, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CDISCOUNTGROUP() {
        ::buf_default((void *)&s, DISCOUNTGROUP_BES, DISCOUNTGROUP_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CDISCOUNTGROUP() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, DISCOUNTGROUP_BES, DISCOUNTGROUP_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1596 ) return UniqueServerCall(1596, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_DISCOUNTGROUP & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.DESCRIPTION);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, DISCOUNTGROUP_BES, (int)DISCOUNTGROUP_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CRANGEMEMBERS : public ppDadeVirtual {
public:
    rangemembersS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<rangemembersS> lst; // class list

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
                     vector< rangemembersS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     rangemembersS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< rangemembersS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<rangemembersS>::iterator
                 beginList() { return lst.begin(); }
    vector<rangemembersS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetDiscountgrpno() const { return s.DISCOUNTGRPNO; }
    double       GetPreisekapo() const { return s.PREISEKAPO; }
    long         GetManufacturerno() const { return s.MANUFACTURERNO; }
    long         GetArtikel_nr() const { return s.ARTIKEL_NR; }
    long         GetBestand() const { return s.BESTAND; }
    const char*  GetEinheit(ppString & t) const { t = s.EINHEIT; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetArtikel_name(ppString & t) const { t = s.ARTIKEL_NAME; t.erasespace(ppString::END); return t.c_str(); }

    const rangemembersS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetDiscountgrpno(long t) { s.DISCOUNTGRPNO = t; }
    void         SetPreisekapo(double t) { s.PREISEKAPO = t; }
    void         SetManufacturerno(long t) { s.MANUFACTURERNO = t; }
    void         SetArtikel_nr(long t) { s.ARTIKEL_NR = t; }
    void         SetBestand(long t) { s.BESTAND = t; }
    void         SetEinheit(const ppString & t) { ppGStrCopy(s.EINHEIT, t.c_str(), L_RANGEMEMBERS_EINHEIT); }
    void         SetArtikel_name(const ppString & t) { ppGStrCopy(s.ARTIKEL_NAME, t.c_str(), L_RANGEMEMBERS_ARTIKEL_NAME); }

    void         SetStruct(const rangemembersS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelArticle(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1597, FetchRel, pos); return ret; }
    int          SelManu(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1598, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CRANGEMEMBERS() {
        ::buf_default((void *)&s, RANGEMEMBERS_BES, RANGEMEMBERS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CRANGEMEMBERS() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, RANGEMEMBERS_BES, RANGEMEMBERS_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, RANGEMEMBERS_BES, (int)RANGEMEMBERS_ANZ, error_msg);
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
        if ( fkt_nr == 1597 ) return CursorServerCall(1597, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1598 ) return CursorServerCall(1598, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_RANGEMEMBERS & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.EINHEIT);
        ppGStripLast(d.ARTIKEL_NAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, RANGEMEMBERS_BES, (int)RANGEMEMBERS_ANZ, error_msg);
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
        CRANGEMEMBERS c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, RANGEMEMBERS_BES, (int)RANGEMEMBERS_ANZ, error_msg);
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
