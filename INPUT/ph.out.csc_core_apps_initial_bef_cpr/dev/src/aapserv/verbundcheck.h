#ifndef __PP_VERBUNDCHECK_H_
#define __PP_VERBUNDCHECK_H_

/******************************************************************************/
/* c:\git\pharmos.outbound.csc_core_applications\dev\src\aapserv\VerbundCheck */
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of ARTSTOCK **************************************************/

#define L_ARTSTOCK_EXCLUDEDBRANCHES 254
#define L_ARTSTOCK_FILIALNR 6
#define L_ARTSTOCK_ARTIKEL_NR 11
#define L_ARTSTOCK_BESTAND 11

/* Length-Define of CHECKIBTDONE **********************************************/

#define L_CHECKIBTDONE_HERKUNFTFILIALE 6
#define L_CHECKIBTDONE_KDAUFTRAGNR 11
#define L_CHECKIBTDONE_POSNR 11
#define L_CHECKIBTDONE_FILIALNR 6
#define L_CHECKIBTDONE_PROCESSINGSTATUS 6

/* Length-Define of VERBUNDMOEGL **********************************************/

#define L_VERBUNDMOEGL_WEEKDAY 6
#define L_VERBUNDMOEGL_FILIALNR 6
#define L_VERBUNDMOEGL_ARTIKEL_NR 11
#define L_VERBUNDMOEGL_BESTAND 11

/* Length-Define of ARTICLENLEVELIBTTYPE **************************************/

#define L_ARTICLENLEVELIBTTYPE_ARTICLENO 11
#define L_ARTICLENLEVELIBTTYPE_BRANCHNO 6
#define L_ARTICLENLEVELIBTTYPE_ASSORTMENTTYPENAME 20
#define L_ARTICLENLEVELIBTTYPE_IBTTYPENAME 20
#define L_ARTICLENLEVELIBTTYPE_IBTTYPEID 6
#define L_ARTICLENLEVELIBTTYPE_IBTASSORTMENTTYPEID 6

/* SqlDefine of ARTSTOCK ******************************************************/


#define ARTSTOCK_PLISTE \
        "ARTIKELLOKAL.FILIALNR,"\
        "ARTIKELLOKAL.ARTIKEL_NR,"\
        "ARTIKELLOKAL.BESTAND"

/* SqlDefine of CHECKIBTDONE **************************************************/


#define CHECKIBTDONE_PLISTE \
        "KDVERBUNDPOS.HERKUNFTFILIALE,"\
        "KDVERBUNDPOS.KDAUFTRAGNR,"\
        "KDVERBUNDPOS.POSNR,"\
        "KDVERBUNDPOS.FILIALNR,"\
        "KDVERBUNDPOS.PROCESSINGSTATUS"

/* SqlDefine of VERBUNDMOEGL **************************************************/


#define VERBUNDMOEGL_PLISTE \
        "ZEITARTEN.WEEKDAY,"\
        "ARTIKELLOKAL.FILIALNR,"\
        "ARTIKELLOKAL.ARTIKEL_NR,"\
        "ARTIKELLOKAL.BESTAND"

/* SqlDefine of ARTICLENLEVELIBTTYPE ******************************************/


#define ARTICLENLEVELIBTTYPE_PLISTE \
        "IBTBRANCHARTICLECONFIG.ARTICLENO,"\
        "IBTBRANCHARTICLECONFIG.BRANCHNO,"\
        "IBTASSORTMENTTYPE.ASSORTMENTTYPENAME,"\
        "IBTTYPE.IBTTYPENAME,"\
        "IBTBRANCHARTICLECONFIG.IBTTYPEID,"\
        "IBTBRANCHARTICLECONFIG.IBTASSORTMENTTYPEID"

/* SqlDefine of ARTSTOCK ******************************************************/


#define ARTSTOCK_UPDLISTE \
        "FILIALNR=?,"\
        "ARTIKEL_NR=?,"\
        "BESTAND=?"
/* SqlDefine of CHECKIBTDONE **************************************************/


#define CHECKIBTDONE_UPDLISTE \
        "HERKUNFTFILIALE=?,"\
        "KDAUFTRAGNR=?,"\
        "POSNR=?,"\
        "FILIALNR=?,"\
        "PROCESSINGSTATUS=?"
/* SqlDefine of VERBUNDMOEGL **************************************************/


#define VERBUNDMOEGL_UPDLISTE \
        "WEEKDAY=?,"\
        "FILIALNR=?,"\
        "ARTIKEL_NR=?,"\
        "BESTAND=?"
/* SqlDefine of ARTICLENLEVELIBTTYPE ******************************************/


#define ARTICLENLEVELIBTTYPE_UPDLISTE \
        "ARTICLENO=?,"\
        "BRANCHNO=?,"\
        "IBTTYPEID=?,"\
        "IBTASSORTMENTTYPEID=?"
/* SqlMacros-Define of ARTSTOCK ***********************************************/

#define ARTSTOCK_ZEIGER(x) \
        :x->FILIALNR,\
        :x->ARTIKEL_NR,\
        :x->BESTAND
#define ARTSTOCK_ZEIGERSEL(x) \
        :x->FILIALNR,\
        :x->ARTIKEL_NR,\
        :x->BESTAND

/* SqlMacros-Define of CHECKIBTDONE *******************************************/

#define CHECKIBTDONE_ZEIGER(x) \
        :x->HERKUNFTFILIALE,\
        :x->KDAUFTRAGNR,\
        :x->POSNR,\
        :x->FILIALNR,\
        :x->PROCESSINGSTATUS
#define CHECKIBTDONE_ZEIGERSEL(x) \
        :x->HERKUNFTFILIALE,\
        :x->KDAUFTRAGNR,\
        :x->POSNR,\
        :x->FILIALNR,\
        :x->PROCESSINGSTATUS

/* SqlMacros-Define of VERBUNDMOEGL *******************************************/

#define VERBUNDMOEGL_ZEIGER(x) \
        :x->WEEKDAY,\
        :x->FILIALNR,\
        :x->ARTIKEL_NR,\
        :x->BESTAND
#define VERBUNDMOEGL_ZEIGERSEL(x) \
        :x->WEEKDAY,\
        :x->FILIALNR,\
        :x->ARTIKEL_NR,\
        :x->BESTAND

/* SqlMacros-Define of ARTICLENLEVELIBTTYPE ***********************************/

#define ARTICLENLEVELIBTTYPE_ZEIGER(x) \
        :x->ARTICLENO,\
        :x->BRANCHNO,\
        :x->IBTTYPEID,\
        :x->IBTASSORTMENTTYPEID
#define ARTICLENLEVELIBTTYPE_ZEIGERSEL(x) \
        :x->ARTICLENO,\
        :x->BRANCHNO,\
        :x->ASSORTMENTTYPENAME,\
        :x->IBTTYPENAME,\
        :x->IBTTYPEID,\
        :x->IBTASSORTMENTTYPEID

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define ARTSTOCK_H
#define ARTSTOCK_ANZ ( sizeof(ARTSTOCK_BES) / sizeof(struct buf_desc) )
#define CHECKIBTDONE_H
#define CHECKIBTDONE_ANZ ( sizeof(CHECKIBTDONE_BES) / sizeof(struct buf_desc) )
#define VERBUNDMOEGL_H
#define VERBUNDMOEGL_ANZ ( sizeof(VERBUNDMOEGL_BES) / sizeof(struct buf_desc) )
#define ARTICLENLEVELIBTTYPE_H
#define ARTICLENLEVELIBTTYPE_ANZ ( sizeof(ARTICLENLEVELIBTTYPE_BES) / sizeof(struct buf_desc) )
#endif

#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of ARTSTOCK ************************************************/

#ifndef TRANSCLASS
typedef struct N_ARTSTOCK {
    char EXCLUDEDBRANCHES[255];
    short FILIALNR;
    long ARTIKEL_NR;
    long BESTAND;
    long FETCH_REL;
} artstockS;
#else /* TRANSCLASS */
typedef struct N_ARTSTOCK {
    char EXCLUDEDBRANCHES[255];
    short FILIALNR;
    long ARTIKEL_NR;
    long BESTAND;
    long FETCH_REL;
    bool operator == (const N_ARTSTOCK& right) const {
        return (
            !strcmp(EXCLUDEDBRANCHES, right.EXCLUDEDBRANCHES) &&
            FILIALNR == right.FILIALNR &&
            ARTIKEL_NR == right.ARTIKEL_NR &&
            BESTAND == right.BESTAND
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        strcpy(EXCLUDEDBRANCHES, " " );
        FILIALNR = 0;
        ARTIKEL_NR = 0;
        BESTAND = 0;
#endif
    }
} artstockS;
#endif /* TRANSCLASS */

/* original struct of CHECKIBTDONE ********************************************/

#ifndef TRANSCLASS
typedef struct N_CHECKIBTDONE {
    short HERKUNFTFILIALE;
    long KDAUFTRAGNR;
    long POSNR;
    short FILIALNR;
    short PROCESSINGSTATUS;
} checkibtdoneS;
#else /* TRANSCLASS */
typedef struct N_CHECKIBTDONE {
    short HERKUNFTFILIALE;
    long KDAUFTRAGNR;
    long POSNR;
    short FILIALNR;
    short PROCESSINGSTATUS;

    bool operator == (const N_CHECKIBTDONE& right) const {
        return (
            HERKUNFTFILIALE == right.HERKUNFTFILIALE &&
            KDAUFTRAGNR == right.KDAUFTRAGNR &&
            POSNR == right.POSNR &&
            FILIALNR == right.FILIALNR &&
            PROCESSINGSTATUS == right.PROCESSINGSTATUS
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        HERKUNFTFILIALE = 0;
        KDAUFTRAGNR = 0;
        POSNR = 0;
        FILIALNR = 0;
        PROCESSINGSTATUS = 0;
#endif
    }
} checkibtdoneS;
#endif /* TRANSCLASS */

/* original struct of VERBUNDMOEGL ********************************************/

#ifndef TRANSCLASS
typedef struct N_VERBUNDMOEGL {
    short WEEKDAY;
    short FILIALNR;
    long ARTIKEL_NR;
    long BESTAND;
} verbundmoeglS;
#else /* TRANSCLASS */
typedef struct N_VERBUNDMOEGL {
    short WEEKDAY;
    short FILIALNR;
    long ARTIKEL_NR;
    long BESTAND;

    bool operator == (const N_VERBUNDMOEGL& right) const {
        return (
            WEEKDAY == right.WEEKDAY &&
            FILIALNR == right.FILIALNR &&
            ARTIKEL_NR == right.ARTIKEL_NR &&
            BESTAND == right.BESTAND
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        WEEKDAY = 0;
        FILIALNR = 0;
        ARTIKEL_NR = 0;
        BESTAND = 0;
#endif
    }
} verbundmoeglS;
#endif /* TRANSCLASS */

/* original struct of ARTICLENLEVELIBTTYPE ************************************/

#ifndef TRANSCLASS
typedef struct N_ARTICLENLEVELIBTTYPE {
    long ARTICLENO;
    short BRANCHNO;
    char ASSORTMENTTYPENAME[21];
    char IBTTYPENAME[21];
    short IBTTYPEID;
    short IBTASSORTMENTTYPEID;
    long FETCH_REL;
} articlenlevelibttypeS;
#else /* TRANSCLASS */
typedef struct N_ARTICLENLEVELIBTTYPE {
    long ARTICLENO;
    short BRANCHNO;
    char ASSORTMENTTYPENAME[21];
    char IBTTYPENAME[21];
    short IBTTYPEID;
    short IBTASSORTMENTTYPEID;
    long FETCH_REL;
    bool operator == (const N_ARTICLENLEVELIBTTYPE& right) const {
        return (
            ARTICLENO == right.ARTICLENO &&
            BRANCHNO == right.BRANCHNO &&
            !strcmp(ASSORTMENTTYPENAME, right.ASSORTMENTTYPENAME) &&
            !strcmp(IBTTYPENAME, right.IBTTYPENAME) &&
            IBTTYPEID == right.IBTTYPEID &&
            IBTASSORTMENTTYPEID == right.IBTASSORTMENTTYPEID
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        ARTICLENO = 0;
        BRANCHNO = 0;
        strcpy(ASSORTMENTTYPENAME, " " );
        strcpy(IBTTYPENAME, " " );
        IBTTYPEID = 0;
        IBTASSORTMENTTYPEID = 0;
#endif
    }
} articlenlevelibttypeS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ARTSTOCK ************************************/

struct C_ARTSTOCK {
    char EXCLUDEDBRANCHES[255];
    short FILIALNR;
    long ARTIKEL_NR;
    long BESTAND;
    long FETCH_REL;
};
/* Structur with real chartype of CHECKIBTDONE ********************************/

struct C_CHECKIBTDONE {
    short HERKUNFTFILIALE;
    long KDAUFTRAGNR;
    long POSNR;
    short FILIALNR;
    short PROCESSINGSTATUS;
};
/* Structur with real chartype of VERBUNDMOEGL ********************************/

struct C_VERBUNDMOEGL {
    short WEEKDAY;
    short FILIALNR;
    long ARTIKEL_NR;
    long BESTAND;
};
/* Structur with real chartype of ARTICLENLEVELIBTTYPE ************************/

struct C_ARTICLENLEVELIBTTYPE {
    long ARTICLENO;
    short BRANCHNO;
    char ASSORTMENTTYPENAME[21];
    char IBTTYPENAME[21];
    short IBTTYPEID;
    short IBTASSORTMENTTYPEID;
    long FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ARTSTOCK **********************************/

struct I_ARTSTOCK {
    short EXCLUDEDBRANCHES;
    short FILIALNR;
    short ARTIKEL_NR;
    short BESTAND;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of CHECKIBTDONE ******************************/

struct I_CHECKIBTDONE {
    short HERKUNFTFILIALE;
    short KDAUFTRAGNR;
    short POSNR;
    short FILIALNR;
    short PROCESSINGSTATUS;
};
/* Sizetype  Structur (buf_desc) of VERBUNDMOEGL ******************************/

struct I_VERBUNDMOEGL {
    short WEEKDAY;
    short FILIALNR;
    short ARTIKEL_NR;
    short BESTAND;
};
/* Sizetype  Structur (buf_desc) of ARTICLENLEVELIBTTYPE **********************/

struct I_ARTICLENLEVELIBTTYPE {
    short ARTICLENO;
    short BRANCHNO;
    short ASSORTMENTTYPENAME;
    short IBTTYPENAME;
    short IBTTYPEID;
    short IBTASSORTMENTTYPEID;
    short FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ARTSTOCK ********************************************/

#if defined (BUF_DESC)
static struct buf_desc ARTSTOCK_BES [] = {
   { TYP_C, 254, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc ARTSTOCK_BES [] = {
   { TYP_C, 254, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of CHECKIBTDONE ****************************************/

#if defined (BUF_DESC)
static struct buf_desc CHECKIBTDONE_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CHECKIBTDONE_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* Structur (buf_desc) of VERBUNDMOEGL ****************************************/

#if defined (BUF_DESC)
static struct buf_desc VERBUNDMOEGL_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc VERBUNDMOEGL_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of ARTICLENLEVELIBTTYPE ********************************/

#if defined (BUF_DESC)
static struct buf_desc ARTICLENLEVELIBTTYPE_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 20, 0 },
   { TYP_C, 20, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc ARTICLENLEVELIBTTYPE_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 20, 0 },
   { TYP_C, 20, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* FunctionNumber-Define of ArtStock ******************************************/

#define ARTSTOCK_SELLIST 1714

/* FunctionNumber-Define of CheckIBTDone **************************************/

#define CHECKIBTDONE_ISIBTDONE 1640
#define CHECKIBTDONE_SELIBTDONEORDER 1678

/* FunctionNumber-Define of VERBUNDMOEGL **************************************/

#define VERBUNDMOEGL_SELVBBESTANDNEU 1776
#define VERBUNDMOEGL_SELVBBESTANDTM 1775

/* FunctionNumber-Define of articlenlevelibttype ******************************/

#define ARTICLENLEVELIBTTYPE_SELLIST 1696

#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of ArtStock **************************************/

#define SelList 1714

/* Old-FunctionNumber-Define of CheckIBTDone **********************************/

#define IsIBTDone 1640
#define SelIBTDoneOrder 1678

/* Old-FunctionNumber-Define of VERBUNDMOEGL **********************************/

#define SelVbBestandNeu 1776
#define SelVbBestandTM 1775

/* Old-FunctionNumber-Define of articlenlevelibttype **************************/

#define SelList 1696

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

class CARTSTOCK : public ppDadeVirtual {
public:
    artstockS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<artstockS> lst; // class list

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
                     vector< artstockS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     artstockS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< artstockS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<artstockS>::iterator
                 beginList() { return lst.begin(); }
    vector<artstockS>::iterator
                 endList  () { return lst.end  (); }

    const char*  GetExcludedbranches(ppString & t) const { t = s.EXCLUDEDBRANCHES; t.erasespace(ppString::END); return t.c_str(); }
    short        GetFilialnr() const { return s.FILIALNR; }
    long         GetArtikel_nr() const { return s.ARTIKEL_NR; }
    long         GetBestand() const { return s.BESTAND; }

    const artstockS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetExcludedbranches(const ppString & t) { ppGStrCopy(s.EXCLUDEDBRANCHES, t.c_str(), L_ARTSTOCK_EXCLUDEDBRANCHES); }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetArtikel_nr(long t) { s.ARTIKEL_NR = t; }
    void         SetBestand(long t) { s.BESTAND = t; }

    void         SetStruct(const artstockS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1714, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CARTSTOCK() {
        ::buf_default((void *)&s, ARTSTOCK_BES, ARTSTOCK_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CARTSTOCK() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, ARTSTOCK_BES, ARTSTOCK_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, ARTSTOCK_BES, (int)ARTSTOCK_ANZ, error_msg);
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
        if ( fkt_nr == 1714 ) return CursorServerCall(1714, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_ARTSTOCK & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.EXCLUDEDBRANCHES);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, ARTSTOCK_BES, (int)ARTSTOCK_ANZ, error_msg);
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
        CARTSTOCK c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, ARTSTOCK_BES, (int)ARTSTOCK_ANZ, error_msg);
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

class CCHECKIBTDONE : public ppDadeVirtual {
public:
    checkibtdoneS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<checkibtdoneS> lst; // class list

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
                     vector< checkibtdoneS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     checkibtdoneS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< checkibtdoneS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<checkibtdoneS>::iterator
                 beginList() { return lst.begin(); }
    vector<checkibtdoneS>::iterator
                 endList  () { return lst.end  (); }

    short        GetHerkunftfiliale() const { return s.HERKUNFTFILIALE; }
    long         GetKdauftragnr() const { return s.KDAUFTRAGNR; }
    long         GetPosnr() const { return s.POSNR; }
    short        GetFilialnr() const { return s.FILIALNR; }
    short        GetProcessingstatus() const { return s.PROCESSINGSTATUS; }

    const checkibtdoneS &
                 GetStruct() const { return s; }
    void         SetHerkunftfiliale(short t) { s.HERKUNFTFILIALE = t; }
    void         SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
    void         SetPosnr(long t) { s.POSNR = t; }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetProcessingstatus(short t) { s.PROCESSINGSTATUS = t; }

    void         SetStruct(const checkibtdoneS & t) { s = t; }

    int          IsIBTDone(int pos = 0) { int ret = UniqueServerCall(1640, pos); Strip(s); return ret; }
    int          SelIBTDoneOrder(int pos = 0) { int ret = UniqueServerCall(1678, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCHECKIBTDONE() {
        ::buf_default((void *)&s, CHECKIBTDONE_BES, CHECKIBTDONE_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCHECKIBTDONE() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CHECKIBTDONE_BES, CHECKIBTDONE_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1640 ) return UniqueServerCall(1640, pos);
        if ( fkt_nr == 1678 ) return UniqueServerCall(1678, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CHECKIBTDONE & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CHECKIBTDONE_BES, (int)CHECKIBTDONE_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CVERBUNDMOEGL : public ppDadeVirtual {
public:
    verbundmoeglS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<verbundmoeglS> lst; // class list

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
                     vector< verbundmoeglS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     verbundmoeglS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< verbundmoeglS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<verbundmoeglS>::iterator
                 beginList() { return lst.begin(); }
    vector<verbundmoeglS>::iterator
                 endList  () { return lst.end  (); }

    short        GetWeekday() const { return s.WEEKDAY; }
    short        GetFilialnr() const { return s.FILIALNR; }
    long         GetArtikel_nr() const { return s.ARTIKEL_NR; }
    long         GetBestand() const { return s.BESTAND; }

    const verbundmoeglS &
                 GetStruct() const { return s; }
    void         SetWeekday(short t) { s.WEEKDAY = t; }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetArtikel_nr(long t) { s.ARTIKEL_NR = t; }
    void         SetBestand(long t) { s.BESTAND = t; }

    void         SetStruct(const verbundmoeglS & t) { s = t; }

    int          SelVbBestandNeu(int pos = 0) { int ret = UniqueServerCall(1776, pos); Strip(s); return ret; }
    int          SelVbBestandTM(int pos = 0) { int ret = UniqueServerCall(1775, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CVERBUNDMOEGL() {
        ::buf_default((void *)&s, VERBUNDMOEGL_BES, VERBUNDMOEGL_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CVERBUNDMOEGL() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, VERBUNDMOEGL_BES, VERBUNDMOEGL_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1776 ) return UniqueServerCall(1776, pos);
        if ( fkt_nr == 1775 ) return UniqueServerCall(1775, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_VERBUNDMOEGL & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, VERBUNDMOEGL_BES, (int)VERBUNDMOEGL_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CARTICLENLEVELIBTTYPE : public ppDadeVirtual {
public:
    articlenlevelibttypeS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<articlenlevelibttypeS> lst; // class list

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
                     vector< articlenlevelibttypeS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     articlenlevelibttypeS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< articlenlevelibttypeS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<articlenlevelibttypeS>::iterator
                 beginList() { return lst.begin(); }
    vector<articlenlevelibttypeS>::iterator
                 endList  () { return lst.end  (); }

    long         GetArticleno() const { return s.ARTICLENO; }
    short        GetBranchno() const { return s.BRANCHNO; }
    const char*  GetAssortmenttypename(ppString & t) const { t = s.ASSORTMENTTYPENAME; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetIbttypename(ppString & t) const { t = s.IBTTYPENAME; t.erasespace(ppString::END); return t.c_str(); }
    short        GetIbttypeid() const { return s.IBTTYPEID; }
    short        GetIbtassortmenttypeid() const { return s.IBTASSORTMENTTYPEID; }

    const articlenlevelibttypeS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetArticleno(long t) { s.ARTICLENO = t; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetAssortmenttypename(const ppString & t) { ppGStrCopy(s.ASSORTMENTTYPENAME, t.c_str(), L_ARTICLENLEVELIBTTYPE_ASSORTMENTTYPENAME); }
    void         SetIbttypename(const ppString & t) { ppGStrCopy(s.IBTTYPENAME, t.c_str(), L_ARTICLENLEVELIBTTYPE_IBTTYPENAME); }
    void         SetIbttypeid(short t) { s.IBTTYPEID = t; }
    void         SetIbtassortmenttypeid(short t) { s.IBTASSORTMENTTYPEID = t; }

    void         SetStruct(const articlenlevelibttypeS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1696, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CARTICLENLEVELIBTTYPE() {
        ::buf_default((void *)&s, ARTICLENLEVELIBTTYPE_BES, ARTICLENLEVELIBTTYPE_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CARTICLENLEVELIBTTYPE() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, ARTICLENLEVELIBTTYPE_BES, ARTICLENLEVELIBTTYPE_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, ARTICLENLEVELIBTTYPE_BES, (int)ARTICLENLEVELIBTTYPE_ANZ, error_msg);
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
        if ( fkt_nr == 1696 ) return CursorServerCall(1696, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_ARTICLENLEVELIBTTYPE & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.ASSORTMENTTYPENAME);
        ppGStripLast(d.IBTTYPENAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, ARTICLENLEVELIBTTYPE_BES, (int)ARTICLENLEVELIBTTYPE_ANZ, error_msg);
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
        CARTICLENLEVELIBTTYPE c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, ARTICLENLEVELIBTTYPE_BES, (int)ARTICLENLEVELIBTTYPE_ANZ, error_msg);
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
