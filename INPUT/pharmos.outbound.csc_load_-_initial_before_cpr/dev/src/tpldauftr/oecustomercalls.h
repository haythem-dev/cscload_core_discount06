#ifndef __PP_OECUSTOMERCALLS_H_
#define __PP_OECUSTOMERCALLS_H_

/******************************************************************************/
/* c:\Marathon\orderentry\load\tpldauftr\src\OECustomerCalls ******************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <pplib/bufkon.h>

/* Length-Define of OECUSTOMERCALLS *******************************************/

#define L_OECUSTOMERCALLS_BRANCHNO 6
#define L_OECUSTOMERCALLS_CUSTOMERNO 11
#define L_OECUSTOMERCALLS_CALLDATE 11
#define L_OECUSTOMERCALLS_CALLTIME 11
#define L_OECUSTOMERCALLS_CALLEFFECT 6
#define L_OECUSTOMERCALLS_CSCORDERNO 11

/* Length/Count-Define of OECUSTOMERCALLS *************************************/

#define LS_OECUSTOMERCALLS_BRANCHNO 5 + 1
#define LS_OECUSTOMERCALLS_CUSTOMERNO 10 + 1
#define LS_OECUSTOMERCALLS_CALLDATE 10 + 1
#define LS_OECUSTOMERCALLS_CALLTIME 10 + 1
#define LS_OECUSTOMERCALLS_CALLEFFECT 5 + 1
#define LS_OECUSTOMERCALLS_CSCORDERNO 10 + 1

#define OECUSTOMERCALLSBRANCHNO 0
#define OECUSTOMERCALLSCUSTOMERNO 1
#define OECUSTOMERCALLSCALLDATE 2
#define OECUSTOMERCALLSCALLTIME 3
#define OECUSTOMERCALLSCALLEFFECT 4
#define OECUSTOMERCALLSCSCORDERNO 5

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define OECUSTOMERCALLS_H
#define OECUSTOMERCALLS_ANZ ( sizeof(OECUSTOMERCALLS_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of OECUSTOMERCALLS ***********************************************/

#define OECUSTOMERCALLS_LISTE \
        OECUSTOMERCALLS.BRANCHNO,\
        OECUSTOMERCALLS.CUSTOMERNO,\
        OECUSTOMERCALLS.CALLDATE,\
        OECUSTOMERCALLS.CALLTIME,\
        OECUSTOMERCALLS.CALLEFFECT,\
        OECUSTOMERCALLS.CSCORDERNO
#define OECUSTOMERCALLS_LISTE_390 \
        BRANCHNO,\
        CUSTOMERNO,\
        CALLDATE,\
        CALLTIME,\
        CALLEFFECT,\
        CSCORDERNO
#define OECUSTOMERCALLS_PLISTE \
        "OECUSTOMERCALLS.BRANCHNO,"\
        "OECUSTOMERCALLS.CUSTOMERNO,"\
        "OECUSTOMERCALLS.CALLDATE,"\
        "OECUSTOMERCALLS.CALLTIME,"\
        "OECUSTOMERCALLS.CALLEFFECT,"\
        "OECUSTOMERCALLS.CSCORDERNO"
#define OECUSTOMERCALLS_PELISTE \
        "BRANCHNO,"\
        "CUSTOMERNO,"\
        "CALLDATE,"\
        "CALLTIME,"\
        "CALLEFFECT,"\
        "CSCORDERNO"
#define OECUSTOMERCALLS_UPDLISTE \
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "CALLDATE=?,"\
        "CALLTIME=?,"\
        "CALLEFFECT=?,"\
        "CSCORDERNO=?"
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
#define OECUSTOMERCALLS_UPDATE(x) \
        OECUSTOMERCALLS.BRANCHNO=:x->BRANCHNO,\
        OECUSTOMERCALLS.CUSTOMERNO=:x->CUSTOMERNO,\
        OECUSTOMERCALLS.CALLDATE=:x->CALLDATE,\
        OECUSTOMERCALLS.CALLTIME=:x->CALLTIME,\
        OECUSTOMERCALLS.CALLEFFECT=:x->CALLEFFECT,\
        OECUSTOMERCALLS.CSCORDERNO=:x->CSCORDERNO
/* SqlMacros390-Define of OECUSTOMERCALLS *************************************/

#define OECUSTOMERCALLS_ZEIGER_390 \
        :BRANCHNO,\
        :CUSTOMERNO,\
        :CALLDATE,\
        :CALLTIME,\
        :CALLEFFECT,\
        :CSCORDERNO
#define OECUSTOMERCALLS_UPDATE_390 \
        BRANCHNO=:BRANCHNO,\
        CUSTOMERNO=:CUSTOMERNO,\
        CALLDATE=:CALLDATE,\
        CALLTIME=:CALLTIME,\
        CALLEFFECT=:CALLEFFECT,\
        CSCORDERNO=:CSCORDERNO
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

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

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of OECUSTOMERCALLS ***********************************/

struct S_OECUSTOMERCALLS {
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char CALLDATE[11];
    char CALLTIME[11];
    char CALLEFFECT[7];
    char CSCORDERNO[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of OECUSTOMERCALLS ******************/

struct O_OECUSTOMERCALLS {
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char CALLDATE[11];
    char CALLTIME[11];
    char CALLEFFECT[7];
    char CSCORDERNO[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of OECUSTOMERCALLS *****************************/

struct C_OECUSTOMERCALLS {
    short BRANCHNO;
    long CUSTOMERNO;
    long CALLDATE;
    long CALLTIME;
    short CALLEFFECT;
    long CSCORDERNO;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of OECUSTOMERCALLS ***************************/

struct I_OECUSTOMERCALLS {
    short BRANCHNO;
    short CUSTOMERNO;
    short CALLDATE;
    short CALLTIME;
    short CALLEFFECT;
    short CSCORDERNO;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

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

/* description for datatypes of OECUSTOMERCALLS *******************************/

 #define OECUSTOMERCALLS_S390 \
         short BRANCHNO; \
         long CUSTOMERNO; \
         long CALLDATE; \
         long CALLTIME; \
         short CALLEFFECT; \
         long CSCORDERNO; \



/* Copy-Function Struct to single Data OECUSTOMERCALLS ************************/

 #define OECUSTOMERCALLS_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
         CALLDATE=_x_->CALLDATE;\
         CALLTIME=_x_->CALLTIME;\
         CALLEFFECT=_x_->CALLEFFECT;\
         CSCORDERNO=_x_->CSCORDERNO;\

 #define OECUSTOMERCALLS_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->CALLDATE=CALLDATE;\
          _x_->CALLTIME=CALLTIME;\
          _x_->CALLEFFECT=CALLEFFECT;\
          _x_->CSCORDERNO=CSCORDERNO;\



/* FunctionNumber-Define of OECustomerCalls ***********************************/

#define OECUSTOMERCALLS_INSERT 1715
#define OECUSTOMERCALLS_UPDATE 1716

#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of OECustomerCalls *******************************/

#define Insert 1715
#define Update 1716

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
#endif    // TRANSCLASS
/* CreateSqlStatement of OECUSTOMERCALLS **************************************/

 #define OECUSTOMERCALLS_CREATE(x) EXEC SQL create table x (\
         BRANCHNO smallint default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         CALLDATE integer default 0 not null,\
         CALLTIME integer default 0 not null,\
         CALLEFFECT smallint default 0 not null,\
         CSCORDERNO integer default 0 not null) in ksc extent size 784 next size 80 lock mode row;



/* CreateIndexStatement of OECUSTOMERCALLS ************************************/

 #define OECUSTOMERCALLS_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_oecustomercalls_1 on _X_(\
              BranchNo,\
              CustomerNo,\
              CallDate,\
              CallTime ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of OECUSTOMERCALLS ************************************/

 #define OECUSTOMERCALLS_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_oecustomercalls_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
