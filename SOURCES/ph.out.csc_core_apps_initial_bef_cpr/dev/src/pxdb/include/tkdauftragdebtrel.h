#ifndef __PP_KDAUFTRAGDEBTREL_H_
#define __PP_KDAUFTRAGDEBTREL_H_

/******************************************************************************/
/* c:\tmp\kdauftragdebtrel ****************************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of KDAUFTRAGDEBTREL ******************************************/

#define L_KDAUFTRAGDEBTREL_KDAUFTRAGNR 11
#define L_KDAUFTRAGDEBTREL_RELREASON 240
#define L_KDAUFTRAGDEBTREL_RELCOMMENT 240
#define L_KDAUFTRAGDEBTREL_RELUSER 30
#define L_KDAUFTRAGDEBTREL_ISRELEASED 6
#define L_KDAUFTRAGDEBTREL_RELCOUNTER 11
#define L_KDAUFTRAGDEBTREL_APPROVALCOUNTER 6
#define L_KDAUFTRAGDEBTREL_CANCELCOUNTER 6
#define L_KDAUFTRAGDEBTREL_DEBTLIMIT 13
#define N_KDAUFTRAGDEBTREL_DEBTLIMIT 2
#define L_KDAUFTRAGDEBTREL_USEDDEBTLIMIT 13
#define N_KDAUFTRAGDEBTREL_USEDDEBTLIMIT 2
#define L_KDAUFTRAGDEBTREL_ORDERVALUE 16
#define N_KDAUFTRAGDEBTREL_ORDERVALUE 2

/* Length/Count-Define of KDAUFTRAGDEBTREL ************************************/

#define LS_KDAUFTRAGDEBTREL_KDAUFTRAGNR 10 + 1
#define LS_KDAUFTRAGDEBTREL_RELREASON 240 + 1
#define LS_KDAUFTRAGDEBTREL_RELCOMMENT 240 + 1
#define LS_KDAUFTRAGDEBTREL_RELUSER 30 + 1
#define LS_KDAUFTRAGDEBTREL_ISRELEASED 5 + 1
#define LS_KDAUFTRAGDEBTREL_RELCOUNTER 10 + 1
#define LS_KDAUFTRAGDEBTREL_APPROVALCOUNTER 5 + 1
#define LS_KDAUFTRAGDEBTREL_CANCELCOUNTER 5 + 1
#define LS_KDAUFTRAGDEBTREL_DEBTLIMIT 13 + 2
#define LS_KDAUFTRAGDEBTREL_USEDDEBTLIMIT 13 + 2
#define LS_KDAUFTRAGDEBTREL_ORDERVALUE 16 + 2

#define KDAUFTRAGDEBTRELKDAUFTRAGNR 0
#define KDAUFTRAGDEBTRELRELREASON 1
#define KDAUFTRAGDEBTRELRELCOMMENT 2
#define KDAUFTRAGDEBTRELRELUSER 3
#define KDAUFTRAGDEBTRELISRELEASED 4
#define KDAUFTRAGDEBTRELRELCOUNTER 5
#define KDAUFTRAGDEBTRELAPPROVALCOUNTER 6
#define KDAUFTRAGDEBTRELCANCELCOUNTER 7
#define KDAUFTRAGDEBTRELDEBTLIMIT 8
#define KDAUFTRAGDEBTRELUSEDDEBTLIMIT 9
#define KDAUFTRAGDEBTRELORDERVALUE 10

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define KDAUFTRAGDEBTREL_H
#define KDAUFTRAGDEBTREL_ANZ ( sizeof(KDAUFTRAGDEBTREL_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of KDAUFTRAGDEBTREL **********************************************/

#define KDAUFTRAGDEBTREL_LISTE \
        KDAUFTRAGDEBTREL.KDAUFTRAGNR,\
        KDAUFTRAGDEBTREL.RELREASON,\
        KDAUFTRAGDEBTREL.RELCOMMENT,\
        KDAUFTRAGDEBTREL.RELUSER,\
        KDAUFTRAGDEBTREL.ISRELEASED,\
        KDAUFTRAGDEBTREL.RELCOUNTER,\
        KDAUFTRAGDEBTREL.APPROVALCOUNTER,\
        KDAUFTRAGDEBTREL.CANCELCOUNTER,\
        KDAUFTRAGDEBTREL.DEBTLIMIT,\
        KDAUFTRAGDEBTREL.USEDDEBTLIMIT,\
        KDAUFTRAGDEBTREL.ORDERVALUE
#define KDAUFTRAGDEBTREL_LISTE_390 \
        KDAUFTRAGNR,\
        RELREASON,\
        RELCOMMENT,\
        RELUSER,\
        ISRELEASED,\
        RELCOUNTER,\
        APPROVALCOUNTER,\
        CANCELCOUNTER,\
        DEBTLIMIT,\
        USEDDEBTLIMIT,\
        ORDERVALUE
#define KDAUFTRAGDEBTREL_PLISTE \
        "KDAUFTRAGDEBTREL.KDAUFTRAGNR,"\
        "KDAUFTRAGDEBTREL.RELREASON,"\
        "KDAUFTRAGDEBTREL.RELCOMMENT,"\
        "KDAUFTRAGDEBTREL.RELUSER,"\
        "KDAUFTRAGDEBTREL.ISRELEASED,"\
        "KDAUFTRAGDEBTREL.RELCOUNTER,"\
        "KDAUFTRAGDEBTREL.APPROVALCOUNTER,"\
        "KDAUFTRAGDEBTREL.CANCELCOUNTER,"\
        "KDAUFTRAGDEBTREL.DEBTLIMIT,"\
        "KDAUFTRAGDEBTREL.USEDDEBTLIMIT,"\
        "KDAUFTRAGDEBTREL.ORDERVALUE"
#define KDAUFTRAGDEBTREL_PELISTE \
        "KDAUFTRAGNR,"\
        "RELREASON,"\
        "RELCOMMENT,"\
        "RELUSER,"\
        "ISRELEASED,"\
        "RELCOUNTER,"\
        "APPROVALCOUNTER,"\
        "CANCELCOUNTER,"\
        "DEBTLIMIT,"\
        "USEDDEBTLIMIT,"\
        "ORDERVALUE"
#define KDAUFTRAGDEBTREL_UPDLISTE \
        "KDAUFTRAGNR=?,"\
        "RELREASON=?,"\
        "RELCOMMENT=?,"\
        "RELUSER=?,"\
        "ISRELEASED=?,"\
        "RELCOUNTER=?,"\
        "APPROVALCOUNTER=?,"\
        "CANCELCOUNTER=?,"\
        "DEBTLIMIT=?,"\
        "USEDDEBTLIMIT=?,"\
        "ORDERVALUE=?"
/* SqlMacros-Define of KDAUFTRAGDEBTREL ***************************************/

#define KDAUFTRAGDEBTREL_ZEIGER(x) \
        :x->KDAUFTRAGNR,\
        :x->RELREASON,\
        :x->RELCOMMENT,\
        :x->RELUSER,\
        :x->ISRELEASED,\
        :x->RELCOUNTER,\
        :x->APPROVALCOUNTER,\
        :x->CANCELCOUNTER,\
        :x->DEBTLIMIT,\
        :x->USEDDEBTLIMIT,\
        :x->ORDERVALUE
#define KDAUFTRAGDEBTREL_ZEIGERSEL(x) \
        :x->KDAUFTRAGNR,\
        :x->RELREASON,\
        :x->RELCOMMENT,\
        :x->RELUSER,\
        :x->ISRELEASED,\
        :x->RELCOUNTER,\
        :x->APPROVALCOUNTER,\
        :x->CANCELCOUNTER,\
        :x->DEBTLIMIT,\
        :x->USEDDEBTLIMIT,\
        :x->ORDERVALUE
#define KDAUFTRAGDEBTREL_UPDATE(x) \
        KDAUFTRAGDEBTREL.KDAUFTRAGNR=:x->KDAUFTRAGNR,\
        KDAUFTRAGDEBTREL.RELREASON=:x->RELREASON,\
        KDAUFTRAGDEBTREL.RELCOMMENT=:x->RELCOMMENT,\
        KDAUFTRAGDEBTREL.RELUSER=:x->RELUSER,\
        KDAUFTRAGDEBTREL.ISRELEASED=:x->ISRELEASED,\
        KDAUFTRAGDEBTREL.RELCOUNTER=:x->RELCOUNTER,\
        KDAUFTRAGDEBTREL.APPROVALCOUNTER=:x->APPROVALCOUNTER,\
        KDAUFTRAGDEBTREL.CANCELCOUNTER=:x->CANCELCOUNTER,\
        KDAUFTRAGDEBTREL.DEBTLIMIT=:x->DEBTLIMIT,\
        KDAUFTRAGDEBTREL.USEDDEBTLIMIT=:x->USEDDEBTLIMIT,\
        KDAUFTRAGDEBTREL.ORDERVALUE=:x->ORDERVALUE
/* SqlMacros390-Define of KDAUFTRAGDEBTREL ************************************/

#define KDAUFTRAGDEBTREL_ZEIGER_390 \
        :KDAUFTRAGNR,\
        :RELREASON,\
        :RELCOMMENT,\
        :RELUSER,\
        :ISRELEASED,\
        :RELCOUNTER,\
        :APPROVALCOUNTER,\
        :CANCELCOUNTER,\
        :DEBTLIMIT,\
        :USEDDEBTLIMIT,\
        :ORDERVALUE
#define KDAUFTRAGDEBTREL_UPDATE_390 \
        KDAUFTRAGNR=:KDAUFTRAGNR,\
        RELREASON=:RELREASON,\
        RELCOMMENT=:RELCOMMENT,\
        RELUSER=:RELUSER,\
        ISRELEASED=:ISRELEASED,\
        RELCOUNTER=:RELCOUNTER,\
        APPROVALCOUNTER=:APPROVALCOUNTER,\
        CANCELCOUNTER=:CANCELCOUNTER,\
        DEBTLIMIT=:DEBTLIMIT,\
        USEDDEBTLIMIT=:USEDDEBTLIMIT,\
        ORDERVALUE=:ORDERVALUE
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of KDAUFTRAGDEBTREL ****************************************/

#ifndef TRANSCLASS
typedef struct N_KDAUFTRAGDEBTREL {
    long KDAUFTRAGNR;
    char RELREASON[241];
    char RELCOMMENT[241];
    char RELUSER[31];
    short ISRELEASED;
    long RELCOUNTER;
    short APPROVALCOUNTER;
    short CANCELCOUNTER;
    double DEBTLIMIT;
    double USEDDEBTLIMIT;
    double ORDERVALUE;
} kdauftragdebtrelS;
#else /* TRANSCLASS */
typedef struct N_KDAUFTRAGDEBTREL {
    long KDAUFTRAGNR;
    char RELREASON[241];
    char RELCOMMENT[241];
    char RELUSER[31];
    short ISRELEASED;
    long RELCOUNTER;
    short APPROVALCOUNTER;
    short CANCELCOUNTER;
    double DEBTLIMIT;
    double USEDDEBTLIMIT;
    double ORDERVALUE;

    bool operator == (const N_KDAUFTRAGDEBTREL& right) const {
        return (
            KDAUFTRAGNR == right.KDAUFTRAGNR &&
            !strcmp(RELREASON, right.RELREASON) &&
            !strcmp(RELCOMMENT, right.RELCOMMENT) &&
            !strcmp(RELUSER, right.RELUSER) &&
            ISRELEASED == right.ISRELEASED &&
            RELCOUNTER == right.RELCOUNTER &&
            APPROVALCOUNTER == right.APPROVALCOUNTER &&
            CANCELCOUNTER == right.CANCELCOUNTER &&
            DEBTLIMIT == right.DEBTLIMIT &&
            USEDDEBTLIMIT == right.USEDDEBTLIMIT &&
            ORDERVALUE == right.ORDERVALUE
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        KDAUFTRAGNR = 0;
        strcpy(RELREASON, " " );
        strcpy(RELCOMMENT, " " );
        strcpy(RELUSER, " " );
        ISRELEASED = 0;
        RELCOUNTER = 0;
        APPROVALCOUNTER = 0;
        CANCELCOUNTER = 0;
        DEBTLIMIT = 0;
        USEDDEBTLIMIT = 0;
        ORDERVALUE = 0;
#endif
    }
} kdauftragdebtrelS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of KDAUFTRAGDEBTREL **********************************/

struct S_KDAUFTRAGDEBTREL {
    char KDAUFTRAGNR[11];
    char RELREASON[240 + 1];
    char RELCOMMENT[240 + 1];
    char RELUSER[30 + 1];
    char ISRELEASED[7];
    char RELCOUNTER[11];
    char APPROVALCOUNTER[7];
    char CANCELCOUNTER[7];
    char DEBTLIMIT[13 + 2];
    char USEDDEBTLIMIT[13 + 2];
    char ORDERVALUE[16 + 2];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of KDAUFTRAGDEBTREL *****************/

struct O_KDAUFTRAGDEBTREL {
    char KDAUFTRAGNR[11];
    char RELREASON[240];
    char RELCOMMENT[240];
    char RELUSER[30];
    char ISRELEASED[7];
    char RELCOUNTER[11];
    char APPROVALCOUNTER[7];
    char CANCELCOUNTER[7];
    char DEBTLIMIT[13];
    char USEDDEBTLIMIT[13];
    char ORDERVALUE[16];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of KDAUFTRAGDEBTREL ****************************/

struct C_KDAUFTRAGDEBTREL {
    long KDAUFTRAGNR;
    char RELREASON[241];
    char RELCOMMENT[241];
    char RELUSER[31];
    short ISRELEASED;
    long RELCOUNTER;
    short APPROVALCOUNTER;
    short CANCELCOUNTER;
    double DEBTLIMIT;
    double USEDDEBTLIMIT;
    double ORDERVALUE;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of KDAUFTRAGDEBTREL **************************/

struct I_KDAUFTRAGDEBTREL {
    short KDAUFTRAGNR;
    short RELREASON;
    short RELCOMMENT;
    short RELUSER;
    short ISRELEASED;
    short RELCOUNTER;
    short APPROVALCOUNTER;
    short CANCELCOUNTER;
    short DEBTLIMIT;
    short USEDDEBTLIMIT;
    short ORDERVALUE;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of KDAUFTRAGDEBTREL ************************************/

#if defined (BUF_DESC)
static struct buf_desc KDAUFTRAGDEBTREL_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 240, 0 },
   { TYP_C, 240, 0 },
   { TYP_C, 30, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 13, 2 },
   { TYP_D, 13, 2 },
   { TYP_D, 16, 2 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc KDAUFTRAGDEBTREL_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 240, 0 },
   { TYP_C, 240, 0 },
   { TYP_C, 30, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 13, 2 },
   { TYP_D, 13, 2 },
   { TYP_D, 16, 2 },
};
#endif

/* description for datatypes of KDAUFTRAGDEBTREL ******************************/

 #define KDAUFTRAGDEBTREL_S390 \
         long KDAUFTRAGNR; \
         char RELREASON[241]; \
         char RELCOMMENT[241]; \
         char RELUSER[31]; \
         short ISRELEASED; \
         long RELCOUNTER; \
         short APPROVALCOUNTER; \
         short CANCELCOUNTER; \
         double DEBTLIMIT; \
         double USEDDEBTLIMIT; \
         double ORDERVALUE; \



/* Copy-Function Struct to single Data KDAUFTRAGDEBTREL ***********************/

 #define KDAUFTRAGDEBTREL_S390_COPY_TO_SINGLE(_x_) \
         KDAUFTRAGNR=_x_->KDAUFTRAGNR;\
          strcpy(RELREASON,_x_->RELREASON);\
          strcpy(RELCOMMENT,_x_->RELCOMMENT);\
          strcpy(RELUSER,_x_->RELUSER);\
         ISRELEASED=_x_->ISRELEASED;\
         RELCOUNTER=_x_->RELCOUNTER;\
         APPROVALCOUNTER=_x_->APPROVALCOUNTER;\
         CANCELCOUNTER=_x_->CANCELCOUNTER;\
         DEBTLIMIT=_x_->DEBTLIMIT;\
         USEDDEBTLIMIT=_x_->USEDDEBTLIMIT;\
         ORDERVALUE=_x_->ORDERVALUE;\

 #define KDAUFTRAGDEBTREL_S390_COPY_TO_STRUCT(_x_) \
          _x_->KDAUFTRAGNR=KDAUFTRAGNR;\
          strcpy(_x_->RELREASON,RELREASON);\
          strcpy(_x_->RELCOMMENT,RELCOMMENT);\
          strcpy(_x_->RELUSER,RELUSER);\
          _x_->ISRELEASED=ISRELEASED;\
          _x_->RELCOUNTER=RELCOUNTER;\
          _x_->APPROVALCOUNTER=APPROVALCOUNTER;\
          _x_->CANCELCOUNTER=CANCELCOUNTER;\
          _x_->DEBTLIMIT=DEBTLIMIT;\
          _x_->USEDDEBTLIMIT=USEDDEBTLIMIT;\
          _x_->ORDERVALUE=ORDERVALUE;\



/* FunctionNumber-Define of kdauftragdebtrel **********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of kdauftragdebtrel ******************************/


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

class CKDAUFTRAGDEBTREL : public ppDadeVirtual {
public:
    kdauftragdebtrelS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<kdauftragdebtrelS> lst; // class list

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
                     vector< kdauftragdebtrelS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     kdauftragdebtrelS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< kdauftragdebtrelS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<kdauftragdebtrelS>::iterator
                 beginList() { return lst.begin(); }
    vector<kdauftragdebtrelS>::iterator
                 endList  () { return lst.end  (); }

    long         GetKdauftragnr() const { return s.KDAUFTRAGNR; }
    const char*  GetRelreason(ppString & t) const { t = s.RELREASON; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetRelcomment(ppString & t) const { t = s.RELCOMMENT; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetReluser(ppString & t) const { t = s.RELUSER; t.erasespace(ppString::END); return t.c_str(); }
    short        GetIsreleased() const { return s.ISRELEASED; }
    long         GetRelcounter() const { return s.RELCOUNTER; }
    short        GetApprovalcounter() const { return s.APPROVALCOUNTER; }
    short        GetCancelcounter() const { return s.CANCELCOUNTER; }
    double       GetDebtlimit() const { return s.DEBTLIMIT; }
    double       GetUseddebtlimit() const { return s.USEDDEBTLIMIT; }
    double       GetOrdervalue() const { return s.ORDERVALUE; }

    const kdauftragdebtrelS &
                 GetStruct() const { return s; }
    void         SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
    void         SetRelreason(const ppString & t) { ppGStrCopy(s.RELREASON, t.c_str(), L_KDAUFTRAGDEBTREL_RELREASON); }
    void         SetRelcomment(const ppString & t) { ppGStrCopy(s.RELCOMMENT, t.c_str(), L_KDAUFTRAGDEBTREL_RELCOMMENT); }
    void         SetReluser(const ppString & t) { ppGStrCopy(s.RELUSER, t.c_str(), L_KDAUFTRAGDEBTREL_RELUSER); }
    void         SetIsreleased(short t) { s.ISRELEASED = t; }
    void         SetRelcounter(long t) { s.RELCOUNTER = t; }
    void         SetApprovalcounter(short t) { s.APPROVALCOUNTER = t; }
    void         SetCancelcounter(short t) { s.CANCELCOUNTER = t; }
    void         SetDebtlimit(double t) { s.DEBTLIMIT = t; }
    void         SetUseddebtlimit(double t) { s.USEDDEBTLIMIT = t; }
    void         SetOrdervalue(double t) { s.ORDERVALUE = t; }

    void         SetStruct(const kdauftragdebtrelS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CKDAUFTRAGDEBTREL() {
        ::buf_default((void *)&s, KDAUFTRAGDEBTREL_BES, KDAUFTRAGDEBTREL_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CKDAUFTRAGDEBTREL() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, KDAUFTRAGDEBTREL_BES, KDAUFTRAGDEBTREL_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, KDAUFTRAGDEBTREL_BES, (int)KDAUFTRAGDEBTREL_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, KDAUFTRAGDEBTREL_BES, (int)KDAUFTRAGDEBTREL_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_KDAUFTRAGDEBTREL & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.RELREASON);
        ppGStripLast(d.RELCOMMENT);
        ppGStripLast(d.RELUSER);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, KDAUFTRAGDEBTREL_BES, (int)KDAUFTRAGDEBTREL_ANZ, error_msg);
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
/* CreateSqlStatement of KDAUFTRAGDEBTREL *************************************/

 #define KDAUFTRAGDEBTREL_CREATE(x) EXEC SQL create table x (\
         KDAUFTRAGNR integer default 0 not null,\
         RELREASON char(240) default " " not null,\
         RELCOMMENT char(240) default " " not null,\
         RELUSER char(30) default " " not null,\
         ISRELEASED smallint default 0 not null,\
         RELCOUNTER integer default 0 not null,\
         APPROVALCOUNTER smallint default 0 not null,\
         CANCELCOUNTER smallint default 0 not null,\
         DEBTLIMIT decimal(13,2) default 0 not null,\
         USEDDEBTLIMIT decimal(13,2) default 0 not null,\
         ORDERVALUE decimal(16,2) default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of KDAUFTRAGDEBTREL ***********************************/

 #define KDAUFTRAGDEBTREL_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_kdauftrdebtrel_1 on _X_(\
              kdauftragnr,\
              relCounter ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of KDAUFTRAGDEBTREL ***********************************/

 #define KDAUFTRAGDEBTREL_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_kdauftrdebtrel_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
