#ifndef __PP_RETURNPERIOD_H_
#define __PP_RETURNPERIOD_H_

/******************************************************************************/
/**/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* Length-Define of RETURNPERIOD **********************************************/

#define L_RETURNPERIOD_ARTICLETYPEID 6
#define L_RETURNPERIOD_PERIODOFVALIDRETURN 6

/* Length/Count-Define of RETURNPERIOD ****************************************/

#define LS_RETURNPERIOD_ARTICLETYPEID 5 + 1
#define LS_RETURNPERIOD_PERIODOFVALIDRETURN 5 + 1

#define RETURNPERIODARTICLETYPEID 0
#define RETURNPERIODPERIODOFVALIDRETURN 1

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define RETURNPERIOD_H
#define RETURNPERIOD_ANZ ( sizeof(RETURNPERIOD_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of RETURNPERIOD **************************************************/

#define RETURNPERIOD_LISTE \
        RETURNPERIOD.ARTICLETYPEID,\
        RETURNPERIOD.PERIODOFVALIDRETURN
#define RETURNPERIOD_LISTE_390 \
        ARTICLETYPEID,\
        PERIODOFVALIDRETURN
#define RETURNPERIOD_PLISTE \
        "RETURNPERIOD.ARTICLETYPEID,"\
        "RETURNPERIOD.PERIODOFVALIDRETURN"
#define RETURNPERIOD_PELISTE \
        "ARTICLETYPEID,"\
        "PERIODOFVALIDRETURN"
#define RETURNPERIOD_UPDLISTE \
        "ARTICLETYPEID=?,"\
        "PERIODOFVALIDRETURN=?"
/* SqlMacros-Define of RETURNPERIOD *******************************************/

#define RETURNPERIOD_ZEIGER(x) \
        :x->ARTICLETYPEID,\
        :x->PERIODOFVALIDRETURN
#define RETURNPERIOD_ZEIGERSEL(x) \
        :x->ARTICLETYPEID,\
        :x->PERIODOFVALIDRETURN
#define RETURNPERIOD_UPDATE(x) \
        RETURNPERIOD.ARTICLETYPEID=:x->ARTICLETYPEID,\
        RETURNPERIOD.PERIODOFVALIDRETURN=:x->PERIODOFVALIDRETURN
/* SqlMacros390-Define of RETURNPERIOD ****************************************/

#define RETURNPERIOD_ZEIGER_390 \
        :ARTICLETYPEID,\
        :PERIODOFVALIDRETURN
#define RETURNPERIOD_UPDATE_390 \
        ARTICLETYPEID=:ARTICLETYPEID,\
        PERIODOFVALIDRETURN=:PERIODOFVALIDRETURN
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of RETURNPERIOD ********************************************/

#ifndef TRANSCLASS
typedef struct N_RETURNPERIOD {
    short ARTICLETYPEID;
    short PERIODOFVALIDRETURN;
} returnperiodS;
#else /* TRANSCLASS */
typedef struct N_RETURNPERIOD {
    short ARTICLETYPEID;
    short PERIODOFVALIDRETURN;

    bool operator == (const N_RETURNPERIOD& right) const {
        return (
            ARTICLETYPEID == right.ARTICLETYPEID &&
            PERIODOFVALIDRETURN == right.PERIODOFVALIDRETURN
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        ARTICLETYPEID = 0;
        PERIODOFVALIDRETURN = 0;
#endif
    }
} returnperiodS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of RETURNPERIOD **************************************/

struct S_RETURNPERIOD {
    char ARTICLETYPEID[7];
    char PERIODOFVALIDRETURN[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of RETURNPERIOD *********************/

struct O_RETURNPERIOD {
    char ARTICLETYPEID[7];
    char PERIODOFVALIDRETURN[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of RETURNPERIOD ********************************/

struct C_RETURNPERIOD {
    short ARTICLETYPEID;
    short PERIODOFVALIDRETURN;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of RETURNPERIOD ******************************/

struct I_RETURNPERIOD {
    short ARTICLETYPEID;
    short PERIODOFVALIDRETURN;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of RETURNPERIOD ****************************************/

#if defined (BUF_DESC)
static struct buf_desc RETURNPERIOD_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc RETURNPERIOD_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* description for datatypes of RETURNPERIOD **********************************/

 #define RETURNPERIOD_S390 \
         short ARTICLETYPEID; \
         short PERIODOFVALIDRETURN; \



/* Copy-Function Struct to single Data RETURNPERIOD ***************************/

 #define RETURNPERIOD_S390_COPY_TO_SINGLE(_x_) \
         ARTICLETYPEID=_x_->ARTICLETYPEID;\
         PERIODOFVALIDRETURN=_x_->PERIODOFVALIDRETURN;\

 #define RETURNPERIOD_S390_COPY_TO_STRUCT(_x_) \
          _x_->ARTICLETYPEID=ARTICLETYPEID;\
          _x_->PERIODOFVALIDRETURN=PERIODOFVALIDRETURN;\



/* FunctionNumber-Define of ReturnPeriod **************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of ReturnPeriod **********************************/


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

class CRETURNPERIOD : public ppDadeVirtual {
public:
    returnperiodS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<returnperiodS> lst; // class list

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
                     vector< returnperiodS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     returnperiodS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< returnperiodS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<returnperiodS>::iterator
                 beginList() { return lst.begin(); }
    vector<returnperiodS>::iterator
                 endList  () { return lst.end  (); }

    short        GetArticletypeid() const { return s.ARTICLETYPEID; }
    short        GetPeriodofvalidreturn() const { return s.PERIODOFVALIDRETURN; }

    const returnperiodS &
                 GetStruct() const { return s; }
    void         SetArticletypeid(short t) { s.ARTICLETYPEID = t; }
    void         SetPeriodofvalidreturn(short t) { s.PERIODOFVALIDRETURN = t; }

    void         SetStruct(const returnperiodS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CRETURNPERIOD() {
        ::buf_default((void *)&s, RETURNPERIOD_BES, RETURNPERIOD_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CRETURNPERIOD() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, RETURNPERIOD_BES, RETURNPERIOD_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, RETURNPERIOD_BES, (int)RETURNPERIOD_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, RETURNPERIOD_BES, (int)RETURNPERIOD_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_RETURNPERIOD & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, RETURNPERIOD_BES, (int)RETURNPERIOD_ANZ, error_msg);
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
/* CreateSqlStatement of RETURNPERIOD *****************************************/

 #define RETURNPERIOD_CREATE(x) EXEC SQL create table x (\
         ARTICLETYPEID smallint default 0 not null,\
         PERIODOFVALIDRETURN smallint default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of RETURNPERIOD ***************************************/

 #define RETURNPERIOD_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_returnperiod_1 on _X_(\
              articletypeid ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of RETURNPERIOD ***************************************/

 #define RETURNPERIOD_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_returnperiod_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
