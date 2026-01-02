#ifndef __PP_IBTBRANCHARTICLECONFIG_H_
#define __PP_IBTBRANCHARTICLECONFIG_H_

/******************************************************************************/
/* c:\tmp\ibtbrancharticleconfig **********************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of IBTBRANCHARTICLECONFIG ************************************/

#define L_IBTBRANCHARTICLECONFIG_ARTICLENO 11
#define L_IBTBRANCHARTICLECONFIG_BRANCHNO 6
#define L_IBTBRANCHARTICLECONFIG_IBTTYPEID 6
#define L_IBTBRANCHARTICLECONFIG_IBTASSORTMENTTYPEID 6

/* Length/Count-Define of IBTBRANCHARTICLECONFIG ******************************/

#define LS_IBTBRANCHARTICLECONFIG_ARTICLENO 10 + 1
#define LS_IBTBRANCHARTICLECONFIG_BRANCHNO 5 + 1
#define LS_IBTBRANCHARTICLECONFIG_IBTTYPEID 5 + 1
#define LS_IBTBRANCHARTICLECONFIG_IBTASSORTMENTTYPEID 5 + 1

#define IBTBRANCHARTICLECONFIGARTICLENO 0
#define IBTBRANCHARTICLECONFIGBRANCHNO 1
#define IBTBRANCHARTICLECONFIGIBTTYPEID 2
#define IBTBRANCHARTICLECONFIGIBTASSORTMENTTYPEID 3

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define IBTBRANCHARTICLECONFIG_H
#define IBTBRANCHARTICLECONFIG_ANZ ( sizeof(IBTBRANCHARTICLECONFIG_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of IBTBRANCHARTICLECONFIG ****************************************/

#define IBTBRANCHARTICLECONFIG_LISTE \
        IBTBRANCHARTICLECONFIG.ARTICLENO,\
        IBTBRANCHARTICLECONFIG.BRANCHNO,\
        IBTBRANCHARTICLECONFIG.IBTTYPEID,\
        IBTBRANCHARTICLECONFIG.IBTASSORTMENTTYPEID
#define IBTBRANCHARTICLECONFIG_LISTE_390 \
        ARTICLENO,\
        BRANCHNO,\
        IBTTYPEID,\
        IBTASSORTMENTTYPEID
#define IBTBRANCHARTICLECONFIG_PLISTE \
        "IBTBRANCHARTICLECONFIG.ARTICLENO,"\
        "IBTBRANCHARTICLECONFIG.BRANCHNO,"\
        "IBTBRANCHARTICLECONFIG.IBTTYPEID,"\
        "IBTBRANCHARTICLECONFIG.IBTASSORTMENTTYPEID"
#define IBTBRANCHARTICLECONFIG_PELISTE \
        "ARTICLENO,"\
        "BRANCHNO,"\
        "IBTTYPEID,"\
        "IBTASSORTMENTTYPEID"
#define IBTBRANCHARTICLECONFIG_UPDLISTE \
        "ARTICLENO=?,"\
        "BRANCHNO=?,"\
        "IBTTYPEID=?,"\
        "IBTASSORTMENTTYPEID=?"
/* SqlMacros-Define of IBTBRANCHARTICLECONFIG *********************************/

#define IBTBRANCHARTICLECONFIG_ZEIGER(x) \
        :x->ARTICLENO,\
        :x->BRANCHNO,\
        :x->IBTTYPEID,\
        :x->IBTASSORTMENTTYPEID
#define IBTBRANCHARTICLECONFIG_ZEIGERSEL(x) \
        :x->ARTICLENO,\
        :x->BRANCHNO,\
        :x->IBTTYPEID,\
        :x->IBTASSORTMENTTYPEID
#define IBTBRANCHARTICLECONFIG_UPDATE(x) \
        IBTBRANCHARTICLECONFIG.ARTICLENO=:x->ARTICLENO,\
        IBTBRANCHARTICLECONFIG.BRANCHNO=:x->BRANCHNO,\
        IBTBRANCHARTICLECONFIG.IBTTYPEID=:x->IBTTYPEID,\
        IBTBRANCHARTICLECONFIG.IBTASSORTMENTTYPEID=:x->IBTASSORTMENTTYPEID
/* SqlMacros390-Define of IBTBRANCHARTICLECONFIG ******************************/

#define IBTBRANCHARTICLECONFIG_ZEIGER_390 \
        :ARTICLENO,\
        :BRANCHNO,\
        :IBTTYPEID,\
        :IBTASSORTMENTTYPEID
#define IBTBRANCHARTICLECONFIG_UPDATE_390 \
        ARTICLENO=:ARTICLENO,\
        BRANCHNO=:BRANCHNO,\
        IBTTYPEID=:IBTTYPEID,\
        IBTASSORTMENTTYPEID=:IBTASSORTMENTTYPEID
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of IBTBRANCHARTICLECONFIG **********************************/

#ifndef TRANSCLASS
typedef struct N_IBTBRANCHARTICLECONFIG {
    long ARTICLENO;
    short BRANCHNO;
    short IBTTYPEID;
    short IBTASSORTMENTTYPEID;
} ibtbrancharticleconfigS;
#else /* TRANSCLASS */
typedef struct N_IBTBRANCHARTICLECONFIG {
    long ARTICLENO;
    short BRANCHNO;
    short IBTTYPEID;
    short IBTASSORTMENTTYPEID;

    bool operator == (const N_IBTBRANCHARTICLECONFIG& right) const {
        return (
            ARTICLENO == right.ARTICLENO &&
            BRANCHNO == right.BRANCHNO &&
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
        IBTTYPEID = 0;
        IBTASSORTMENTTYPEID = 0;
#endif
    }
} ibtbrancharticleconfigS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of IBTBRANCHARTICLECONFIG ****************************/

struct S_IBTBRANCHARTICLECONFIG {
    char ARTICLENO[11];
    char BRANCHNO[7];
    char IBTTYPEID[7];
    char IBTASSORTMENTTYPEID[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of IBTBRANCHARTICLECONFIG ***********/

struct O_IBTBRANCHARTICLECONFIG {
    char ARTICLENO[11];
    char BRANCHNO[7];
    char IBTTYPEID[7];
    char IBTASSORTMENTTYPEID[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of IBTBRANCHARTICLECONFIG **********************/

struct C_IBTBRANCHARTICLECONFIG {
    long ARTICLENO;
    short BRANCHNO;
    short IBTTYPEID;
    short IBTASSORTMENTTYPEID;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of IBTBRANCHARTICLECONFIG ********************/

struct I_IBTBRANCHARTICLECONFIG {
    short ARTICLENO;
    short BRANCHNO;
    short IBTTYPEID;
    short IBTASSORTMENTTYPEID;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of IBTBRANCHARTICLECONFIG ******************************/

#if defined (BUF_DESC)
static struct buf_desc IBTBRANCHARTICLECONFIG_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc IBTBRANCHARTICLECONFIG_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* description for datatypes of IBTBRANCHARTICLECONFIG ************************/

 #define IBTBRANCHARTICLECONFIG_S390 \
         long ARTICLENO; \
         short BRANCHNO; \
         short IBTTYPEID; \
         short IBTASSORTMENTTYPEID; \



/* Copy-Function Struct to single Data IBTBRANCHARTICLECONFIG *****************/

 #define IBTBRANCHARTICLECONFIG_S390_COPY_TO_SINGLE(_x_) \
         ARTICLENO=_x_->ARTICLENO;\
         BRANCHNO=_x_->BRANCHNO;\
         IBTTYPEID=_x_->IBTTYPEID;\
         IBTASSORTMENTTYPEID=_x_->IBTASSORTMENTTYPEID;\

 #define IBTBRANCHARTICLECONFIG_S390_COPY_TO_STRUCT(_x_) \
          _x_->ARTICLENO=ARTICLENO;\
          _x_->BRANCHNO=BRANCHNO;\
          _x_->IBTTYPEID=IBTTYPEID;\
          _x_->IBTASSORTMENTTYPEID=IBTASSORTMENTTYPEID;\



/* FunctionNumber-Define of ibtbrancharticleconfig ****************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of ibtbrancharticleconfig ************************/


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

class CIBTBRANCHARTICLECONFIG : public ppDadeVirtual {
public:
    ibtbrancharticleconfigS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<ibtbrancharticleconfigS> lst; // class list

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
                     vector< ibtbrancharticleconfigS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     ibtbrancharticleconfigS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< ibtbrancharticleconfigS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<ibtbrancharticleconfigS>::iterator
                 beginList() { return lst.begin(); }
    vector<ibtbrancharticleconfigS>::iterator
                 endList  () { return lst.end  (); }

    long         GetArticleno() const { return s.ARTICLENO; }
    short        GetBranchno() const { return s.BRANCHNO; }
    short        GetIbttypeid() const { return s.IBTTYPEID; }
    short        GetIbtassortmenttypeid() const { return s.IBTASSORTMENTTYPEID; }

    const ibtbrancharticleconfigS &
                 GetStruct() const { return s; }
    void         SetArticleno(long t) { s.ARTICLENO = t; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetIbttypeid(short t) { s.IBTTYPEID = t; }
    void         SetIbtassortmenttypeid(short t) { s.IBTASSORTMENTTYPEID = t; }

    void         SetStruct(const ibtbrancharticleconfigS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CIBTBRANCHARTICLECONFIG() {
        ::buf_default((void *)&s, IBTBRANCHARTICLECONFIG_BES, IBTBRANCHARTICLECONFIG_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CIBTBRANCHARTICLECONFIG() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, IBTBRANCHARTICLECONFIG_BES, IBTBRANCHARTICLECONFIG_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, IBTBRANCHARTICLECONFIG_BES, (int)IBTBRANCHARTICLECONFIG_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, IBTBRANCHARTICLECONFIG_BES, (int)IBTBRANCHARTICLECONFIG_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_IBTBRANCHARTICLECONFIG & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, IBTBRANCHARTICLECONFIG_BES, (int)IBTBRANCHARTICLECONFIG_ANZ, error_msg);
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
/* CreateSqlStatement of IBTBRANCHARTICLECONFIG *******************************/

 #define IBTBRANCHARTICLECONFIG_CREATE(x) EXEC SQL create table x (\
         ARTICLENO integer default 0 not null,\
         BRANCHNO smallint default 0 not null,\
         IBTTYPEID smallint default 0 not null,\
         IBTASSORTMENTTYPEID smallint default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of IBTBRANCHARTICLECONFIG *****************************/

 #define IBTBRANCHARTICLECONFIG_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
/* DeleteIndexStatement of IBTBRANCHARTICLECONFIG *****************************/

 #define IBTBRANCHARTICLECONFIG_DELETE_INDEX(_X_)\
              _X_ = 0;\


#endif   // GUARD
