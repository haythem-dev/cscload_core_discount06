#ifndef __PP_DELIVERYADVICELINERETURN_H_
#define __PP_DELIVERYADVICELINERETURN_H_

/******************************************************************************/
/* c:\prri\Headerfiles\Deliveryadvicelinereturn *******************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of DELIVERYADVICELINERETURN **********************************/

#define L_DELIVERYADVICELINERETURN_BRANCHNO 6
#define L_DELIVERYADVICELINERETURN_CUSTOMERNO 11
#define L_DELIVERYADVICELINERETURN_DELIVERYADVICEDATE 11
#define L_DELIVERYADVICELINERETURN_DELIVERYADVICENO 10
#define L_DELIVERYADVICELINERETURN_DELIVERYADVICEPOSNO 11
#define L_DELIVERYADVICELINERETURN_BLOCKEDFORRETURNS 6
#define L_DELIVERYADVICELINERETURN_QTY_RETURNED 11
#define L_DELIVERYADVICELINERETURN_QTY_RETURNED_REBATEINKIND 11
#define L_DELIVERYADVICELINERETURN_QTY_RETURN_REJECTED 11

/* Length/Count-Define of DELIVERYADVICELINERETURN ****************************/

#define LS_DELIVERYADVICELINERETURN_BRANCHNO 5 + 1
#define LS_DELIVERYADVICELINERETURN_CUSTOMERNO 10 + 1
#define LS_DELIVERYADVICELINERETURN_DELIVERYADVICEDATE 10 + 1
#define LS_DELIVERYADVICELINERETURN_DELIVERYADVICENO 10 + 1
#define LS_DELIVERYADVICELINERETURN_DELIVERYADVICEPOSNO 10 + 1
#define LS_DELIVERYADVICELINERETURN_BLOCKEDFORRETURNS 5 + 1
#define LS_DELIVERYADVICELINERETURN_QTY_RETURNED 10 + 1
#define LS_DELIVERYADVICELINERETURN_QTY_RETURNED_REBATEINKIND 10 + 1
#define LS_DELIVERYADVICELINERETURN_QTY_RETURN_REJECTED 10 + 1

#define DELIVERYADVICELINERETURNBRANCHNO 0
#define DELIVERYADVICELINERETURNCUSTOMERNO 1
#define DELIVERYADVICELINERETURNDELIVERYADVICEDATE 2
#define DELIVERYADVICELINERETURNDELIVERYADVICENO 3
#define DELIVERYADVICELINERETURNDELIVERYADVICEPOSNO 4
#define DELIVERYADVICELINERETURNBLOCKEDFORRETURNS 5
#define DELIVERYADVICELINERETURNQTY_RETURNED 6
#define DELIVERYADVICELINERETURNQTY_RETURNED_REBATEINKIND 7
#define DELIVERYADVICELINERETURNQTY_RETURN_REJECTED 8

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define DELIVERYADVICELINERETURN_H
#define DELIVERYADVICELINERETURN_ANZ ( sizeof(DELIVERYADVICELINERETURN_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of DELIVERYADVICELINERETURN **************************************/

#define DELIVERYADVICELINERETURN_LISTE \
        DADUMMY.BRANCHNO,\
        DADUMMY.CUSTOMERNO,\
        DADUMMY.DELIVERYADVICEDATE,\
        DADUMMY.DELIVERYADVICENO,\
        DADUMMY.DELIVERYADVICEPOSNO,\
        DADUMMY.BLOCKEDFORRETURNS,\
        DADUMMY.QTY_RETURNED,\
        DADUMMY.QTY_RETURNED_REBATEINKIND,\
        DADUMMY.QTY_RETURN_REJECTED
#define DELIVERYADVICELINERETURN_LISTE_390 \
        BRANCHNO,\
        CUSTOMERNO,\
        DELIVERYADVICEDATE,\
        DELIVERYADVICENO,\
        DELIVERYADVICEPOSNO,\
        BLOCKEDFORRETURNS,\
        QTY_RETURNED,\
        QTY_RETURNED_REBATEINKIND,\
        QTY_RETURN_REJECTED
#define DELIVERYADVICELINERETURN_PLISTE \
        "DADUMMY.BRANCHNO,"\
        "DADUMMY.CUSTOMERNO,"\
        "DADUMMY.DELIVERYADVICEDATE,"\
        "DADUMMY.DELIVERYADVICENO,"\
        "DADUMMY.DELIVERYADVICEPOSNO,"\
        "DADUMMY.BLOCKEDFORRETURNS,"\
        "DADUMMY.QTY_RETURNED,"\
        "DADUMMY.QTY_RETURNED_REBATEINKIND,"\
        "DADUMMY.QTY_RETURN_REJECTED"
#define DELIVERYADVICELINERETURN_PELISTE \
        "BRANCHNO,"\
        "CUSTOMERNO,"\
        "DELIVERYADVICEDATE,"\
        "DELIVERYADVICENO,"\
        "DELIVERYADVICEPOSNO,"\
        "BLOCKEDFORRETURNS,"\
        "QTY_RETURNED,"\
        "QTY_RETURNED_REBATEINKIND,"\
        "QTY_RETURN_REJECTED"
#define DELIVERYADVICELINERETURN_UPDLISTE \
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "DELIVERYADVICEDATE=?,"\
        "DELIVERYADVICENO=?,"\
        "DELIVERYADVICEPOSNO=?,"\
        "BLOCKEDFORRETURNS=?,"\
        "QTY_RETURNED=?,"\
        "QTY_RETURNED_REBATEINKIND=?,"\
        "QTY_RETURN_REJECTED=?"
/* SqlMacros-Define of DELIVERYADVICELINERETURN *******************************/

#define DELIVERYADVICELINERETURN_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->DELIVERYADVICEDATE,\
        :x->DELIVERYADVICENO,\
        :x->DELIVERYADVICEPOSNO,\
        :x->BLOCKEDFORRETURNS,\
        :x->QTY_RETURNED,\
        :x->QTY_RETURNED_REBATEINKIND,\
        :x->QTY_RETURN_REJECTED
#define DELIVERYADVICELINERETURN_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->DELIVERYADVICEDATE,\
        :x->DELIVERYADVICENO,\
        :x->DELIVERYADVICEPOSNO,\
        :x->BLOCKEDFORRETURNS,\
        :x->QTY_RETURNED,\
        :x->QTY_RETURNED_REBATEINKIND,\
        :x->QTY_RETURN_REJECTED
#define DELIVERYADVICELINERETURN_UPDATE(x) \
        DADUMMY.BRANCHNO=:x->BRANCHNO,\
        DADUMMY.CUSTOMERNO=:x->CUSTOMERNO,\
        DADUMMY.DELIVERYADVICEDATE=:x->DELIVERYADVICEDATE,\
        DADUMMY.DELIVERYADVICENO=:x->DELIVERYADVICENO,\
        DADUMMY.DELIVERYADVICEPOSNO=:x->DELIVERYADVICEPOSNO,\
        DADUMMY.BLOCKEDFORRETURNS=:x->BLOCKEDFORRETURNS,\
        DADUMMY.QTY_RETURNED=:x->QTY_RETURNED,\
        DADUMMY.QTY_RETURNED_REBATEINKIND=:x->QTY_RETURNED_REBATEINKIND,\
        DADUMMY.QTY_RETURN_REJECTED=:x->QTY_RETURN_REJECTED
/* SqlMacros390-Define of DELIVERYADVICELINERETURN ****************************/

#define DELIVERYADVICELINERETURN_ZEIGER_390 \
        :BRANCHNO,\
        :CUSTOMERNO,\
        :DELIVERYADVICEDATE,\
        :DELIVERYADVICENO,\
        :DELIVERYADVICEPOSNO,\
        :BLOCKEDFORRETURNS,\
        :QTY_RETURNED,\
        :QTY_RETURNED_REBATEINKIND,\
        :QTY_RETURN_REJECTED
#define DELIVERYADVICELINERETURN_UPDATE_390 \
        BRANCHNO=:BRANCHNO,\
        CUSTOMERNO=:CUSTOMERNO,\
        DELIVERYADVICEDATE=:DELIVERYADVICEDATE,\
        DELIVERYADVICENO=:DELIVERYADVICENO,\
        DELIVERYADVICEPOSNO=:DELIVERYADVICEPOSNO,\
        BLOCKEDFORRETURNS=:BLOCKEDFORRETURNS,\
        QTY_RETURNED=:QTY_RETURNED,\
        QTY_RETURNED_REBATEINKIND=:QTY_RETURNED_REBATEINKIND,\
        QTY_RETURN_REJECTED=:QTY_RETURN_REJECTED
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of DELIVERYADVICELINERETURN ********************************/

#ifndef TRANSCLASS
typedef struct N_DELIVERYADVICELINERETURN {
    short BRANCHNO;
    long CUSTOMERNO;
    long DELIVERYADVICEDATE;
    char DELIVERYADVICENO[11];
    long DELIVERYADVICEPOSNO;
    short BLOCKEDFORRETURNS;
    long QTY_RETURNED;
    long QTY_RETURNED_REBATEINKIND;
    long QTY_RETURN_REJECTED;
} deliveryadvicelinereturnS;
#else /* TRANSCLASS */
typedef struct N_DELIVERYADVICELINERETURN {
    short BRANCHNO;
    long CUSTOMERNO;
    long DELIVERYADVICEDATE;
    char DELIVERYADVICENO[11];
    long DELIVERYADVICEPOSNO;
    short BLOCKEDFORRETURNS;
    long QTY_RETURNED;
    long QTY_RETURNED_REBATEINKIND;
    long QTY_RETURN_REJECTED;

    bool operator == (const N_DELIVERYADVICELINERETURN& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            CUSTOMERNO == right.CUSTOMERNO &&
            DELIVERYADVICEDATE == right.DELIVERYADVICEDATE &&
            !strcmp(DELIVERYADVICENO, right.DELIVERYADVICENO) &&
            DELIVERYADVICEPOSNO == right.DELIVERYADVICEPOSNO &&
            BLOCKEDFORRETURNS == right.BLOCKEDFORRETURNS &&
            QTY_RETURNED == right.QTY_RETURNED &&
            QTY_RETURNED_REBATEINKIND == right.QTY_RETURNED_REBATEINKIND &&
            QTY_RETURN_REJECTED == right.QTY_RETURN_REJECTED
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        CUSTOMERNO = 0;
        DELIVERYADVICEDATE = 0;
        strcpy(DELIVERYADVICENO, " " );
        DELIVERYADVICEPOSNO = 0;
        BLOCKEDFORRETURNS = 0;
        QTY_RETURNED = 0;
        QTY_RETURNED_REBATEINKIND = 0;
        QTY_RETURN_REJECTED = 0;
#endif
    }
} deliveryadvicelinereturnS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of DELIVERYADVICELINERETURN **************************/

struct S_DELIVERYADVICELINERETURN {
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char DELIVERYADVICEDATE[11];
    char DELIVERYADVICENO[10 + 1];
    char DELIVERYADVICEPOSNO[11];
    char BLOCKEDFORRETURNS[7];
    char QTY_RETURNED[11];
    char QTY_RETURNED_REBATEINKIND[11];
    char QTY_RETURN_REJECTED[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of DELIVERYADVICELINERETURN *********/

struct O_DELIVERYADVICELINERETURN {
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char DELIVERYADVICEDATE[11];
    char DELIVERYADVICENO[10];
    char DELIVERYADVICEPOSNO[11];
    char BLOCKEDFORRETURNS[7];
    char QTY_RETURNED[11];
    char QTY_RETURNED_REBATEINKIND[11];
    char QTY_RETURN_REJECTED[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of DELIVERYADVICELINERETURN ********************/

struct C_DELIVERYADVICELINERETURN {
    short BRANCHNO;
    long CUSTOMERNO;
    long DELIVERYADVICEDATE;
    char DELIVERYADVICENO[11];
    long DELIVERYADVICEPOSNO;
    short BLOCKEDFORRETURNS;
    long QTY_RETURNED;
    long QTY_RETURNED_REBATEINKIND;
    long QTY_RETURN_REJECTED;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of DELIVERYADVICELINERETURN ******************/

struct I_DELIVERYADVICELINERETURN {
    short BRANCHNO;
    short CUSTOMERNO;
    short DELIVERYADVICEDATE;
    short DELIVERYADVICENO;
    short DELIVERYADVICEPOSNO;
    short BLOCKEDFORRETURNS;
    short QTY_RETURNED;
    short QTY_RETURNED_REBATEINKIND;
    short QTY_RETURN_REJECTED;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of DELIVERYADVICELINERETURN ****************************/

#if defined (BUF_DESC)
static struct buf_desc DELIVERYADVICELINERETURN_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 10, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc DELIVERYADVICELINERETURN_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 10, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* description for datatypes of DELIVERYADVICELINERETURN **********************/

 #define DELIVERYADVICELINERETURN_S390 \
         short BRANCHNO; \
         long CUSTOMERNO; \
         long DELIVERYADVICEDATE; \
         char DELIVERYADVICENO[11]; \
         long DELIVERYADVICEPOSNO; \
         short BLOCKEDFORRETURNS; \
         long QTY_RETURNED; \
         long QTY_RETURNED_REBATEINKIND; \
         long QTY_RETURN_REJECTED; \



/* Copy-Function Struct to single Data DELIVERYADVICELINERETURN ***************/

 #define DELIVERYADVICELINERETURN_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
         DELIVERYADVICEDATE=_x_->DELIVERYADVICEDATE;\
          strcpy(DELIVERYADVICENO,_x_->DELIVERYADVICENO);\
         DELIVERYADVICEPOSNO=_x_->DELIVERYADVICEPOSNO;\
         BLOCKEDFORRETURNS=_x_->BLOCKEDFORRETURNS;\
         QTY_RETURNED=_x_->QTY_RETURNED;\
         QTY_RETURNED_REBATEINKIND=_x_->QTY_RETURNED_REBATEINKIND;\
         QTY_RETURN_REJECTED=_x_->QTY_RETURN_REJECTED;\

 #define DELIVERYADVICELINERETURN_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->DELIVERYADVICEDATE=DELIVERYADVICEDATE;\
          strcpy(_x_->DELIVERYADVICENO,DELIVERYADVICENO);\
          _x_->DELIVERYADVICEPOSNO=DELIVERYADVICEPOSNO;\
          _x_->BLOCKEDFORRETURNS=BLOCKEDFORRETURNS;\
          _x_->QTY_RETURNED=QTY_RETURNED;\
          _x_->QTY_RETURNED_REBATEINKIND=QTY_RETURNED_REBATEINKIND;\
          _x_->QTY_RETURN_REJECTED=QTY_RETURN_REJECTED;\



/* FunctionNumber-Define of Deliveryadvicelinereturn **************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of Deliveryadvicelinereturn **********************/


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

class CDELIVERYADVICELINERETURN : public ppDadeVirtual {
public:
    deliveryadvicelinereturnS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<deliveryadvicelinereturnS> lst; // class list

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
                     vector< deliveryadvicelinereturnS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     deliveryadvicelinereturnS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< deliveryadvicelinereturnS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<deliveryadvicelinereturnS>::iterator
                 beginList() { return lst.begin(); }
    vector<deliveryadvicelinereturnS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    long         GetDeliveryadvicedate() const { return s.DELIVERYADVICEDATE; }
    const char*  GetDeliveryadviceno(ppString & t) const { t = s.DELIVERYADVICENO; t.erasespace(ppString::END); return t.c_str(); }
    long         GetDeliveryadviceposno() const { return s.DELIVERYADVICEPOSNO; }
    short        GetBlockedforreturns() const { return s.BLOCKEDFORRETURNS; }
    long         GetQty_returned() const { return s.QTY_RETURNED; }
    long         GetQty_returned_rebateinkind() const { return s.QTY_RETURNED_REBATEINKIND; }
    long         GetQty_return_rejected() const { return s.QTY_RETURN_REJECTED; }

    const deliveryadvicelinereturnS &
                 GetStruct() const { return s; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetDeliveryadvicedate(long t) { s.DELIVERYADVICEDATE = t; }
    void         SetDeliveryadviceno(const ppString & t) { ppGStrCopy(s.DELIVERYADVICENO, t.c_str(), L_DELIVERYADVICELINERETURN_DELIVERYADVICENO); }
    void         SetDeliveryadviceposno(long t) { s.DELIVERYADVICEPOSNO = t; }
    void         SetBlockedforreturns(short t) { s.BLOCKEDFORRETURNS = t; }
    void         SetQty_returned(long t) { s.QTY_RETURNED = t; }
    void         SetQty_returned_rebateinkind(long t) { s.QTY_RETURNED_REBATEINKIND = t; }
    void         SetQty_return_rejected(long t) { s.QTY_RETURN_REJECTED = t; }

    void         SetStruct(const deliveryadvicelinereturnS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CDELIVERYADVICELINERETURN() {
        ::buf_default((void *)&s, DELIVERYADVICELINERETURN_BES, DELIVERYADVICELINERETURN_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CDELIVERYADVICELINERETURN() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, DELIVERYADVICELINERETURN_BES, DELIVERYADVICELINERETURN_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, DELIVERYADVICELINERETURN_BES, (int)DELIVERYADVICELINERETURN_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, DELIVERYADVICELINERETURN_BES, (int)DELIVERYADVICELINERETURN_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_DELIVERYADVICELINERETURN & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.DELIVERYADVICENO);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, DELIVERYADVICELINERETURN_BES, (int)DELIVERYADVICELINERETURN_ANZ, error_msg);
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
/* CreateSqlStatement of DELIVERYADVICELINERETURN *****************************/

 #define DELIVERYADVICELINERETURN_CREATE(x) EXEC SQL create table x (\
         BRANCHNO smallint default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         DELIVERYADVICEDATE integer default 0 not null,\
         DELIVERYADVICENO varchar(10,0) default " " not null,\
         DELIVERYADVICEPOSNO integer default 0 not null,\
         BLOCKEDFORRETURNS smallint default 0 not null,\
         QTY_RETURNED integer default 0 not null,\
         QTY_RETURNED_REBATEINKIND integer default 0 not null,\
         QTY_RETURN_REJECTED integer default 0 not null) extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of DELIVERYADVICELINERETURN ***************************/

 #define DELIVERYADVICELINERETURN_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
/* DeleteIndexStatement of DELIVERYADVICELINERETURN ***************************/

 #define DELIVERYADVICELINERETURN_DELETE_INDEX(_X_)\
              _X_ = 0;\


#endif   // GUARD
