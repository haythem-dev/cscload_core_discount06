#ifndef __PP_TENDERPOS_H_
#define __PP_TENDERPOS_H_

/******************************************************************************/
/* u:\TenderPos ***************************************************************/
/* produced by DADE 6.21.6 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of TENDERPOS *************************************************/

#define L_TENDERPOS_TENDERNO 11
#define L_TENDERPOS_ARTICLENO 11
#define L_TENDERPOS_CONTRACTQTY 11
#define L_TENDERPOS_CONTRACTPRICE 9
#define N_TENDERPOS_CONTRACTPRICE 2
#define L_TENDERPOS_REMAININGLIFE 11
#define L_TENDERPOS_ADDDISCOUNTPCT 5
#define N_TENDERPOS_ADDDISCOUNTPCT 2
#define L_TENDERPOS_AEP 9
#define N_TENDERPOS_AEP 2
#define L_TENDERPOS_TENDERSTATE 1
#define L_TENDERPOS_CHANGEDATE 11
#define L_TENDERPOS_NAMEOFUSER 30
#define L_TENDERPOS_PRICEDIFF 9
#define N_TENDERPOS_PRICEDIFF 2

/* Length/Count-Define of TENDERPOS *******************************************/

#define LS_TENDERPOS_TENDERNO 10 + 1
#define LS_TENDERPOS_ARTICLENO 10 + 1
#define LS_TENDERPOS_CONTRACTQTY 10 + 1
#define LS_TENDERPOS_CONTRACTPRICE 9 + 2
#define LS_TENDERPOS_REMAININGLIFE 10 + 1
#define LS_TENDERPOS_ADDDISCOUNTPCT 5 + 2
#define LS_TENDERPOS_AEP 9 + 2
#define LS_TENDERPOS_TENDERSTATE 1 + 1
#define LS_TENDERPOS_CHANGEDATE 10 + 1
#define LS_TENDERPOS_NAMEOFUSER 30 + 1
#define LS_TENDERPOS_PRICEDIFF 9 + 2

#define TENDERPOSTENDERNO 0
#define TENDERPOSARTICLENO 1
#define TENDERPOSCONTRACTQTY 2
#define TENDERPOSCONTRACTPRICE 3
#define TENDERPOSREMAININGLIFE 4
#define TENDERPOSADDDISCOUNTPCT 5
#define TENDERPOSAEP 6
#define TENDERPOSTENDERSTATE 7
#define TENDERPOSCHANGEDATE 8
#define TENDERPOSNAMEOFUSER 9
#define TENDERPOSPRICEDIFF 10

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define TENDERPOS_H
#define TENDERPOS_ANZ ( sizeof(TENDERPOS_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of TENDERPOS *****************************************************/

#define TENDERPOS_LISTE \
        TENDERPOS.TENDERNO,\
        TENDERPOS.ARTICLENO,\
        TENDERPOS.CONTRACTQTY,\
        TENDERPOS.CONTRACTPRICE,\
        TENDERPOS.REMAININGLIFE,\
        TENDERPOS.ADDDISCOUNTPCT,\
        TENDERPOS.AEP,\
        TENDERPOS.TENDERSTATE,\
        TENDERPOS.CHANGEDATE,\
        TENDERPOS.NAMEOFUSER,\
        TENDERPOS.PRICEDIFF
#define TENDERPOS_LISTE_390 \
        TENDERNO,\
        ARTICLENO,\
        CONTRACTQTY,\
        CONTRACTPRICE,\
        REMAININGLIFE,\
        ADDDISCOUNTPCT,\
        AEP,\
        TENDERSTATE,\
        CHANGEDATE,\
        NAMEOFUSER,\
        PRICEDIFF
#define TENDERPOS_PLISTE \
        "TENDERPOS.TENDERNO,"\
        "TENDERPOS.ARTICLENO,"\
        "TENDERPOS.CONTRACTQTY,"\
        "TENDERPOS.CONTRACTPRICE,"\
        "TENDERPOS.REMAININGLIFE,"\
        "TENDERPOS.ADDDISCOUNTPCT,"\
        "TENDERPOS.AEP,"\
        "TENDERPOS.TENDERSTATE,"\
        "TENDERPOS.CHANGEDATE,"\
        "TENDERPOS.NAMEOFUSER,"\
        "TENDERPOS.PRICEDIFF"
#define TENDERPOS_PELISTE \
        "TENDERNO,"\
        "ARTICLENO,"\
        "CONTRACTQTY,"\
        "CONTRACTPRICE,"\
        "REMAININGLIFE,"\
        "ADDDISCOUNTPCT,"\
        "AEP,"\
        "TENDERSTATE,"\
        "CHANGEDATE,"\
        "NAMEOFUSER,"\
        "PRICEDIFF"
#define TENDERPOS_UPDLISTE \
        "TENDERNO=?,"\
        "ARTICLENO=?,"\
        "CONTRACTQTY=?,"\
        "CONTRACTPRICE=?,"\
        "REMAININGLIFE=?,"\
        "ADDDISCOUNTPCT=?,"\
        "AEP=?,"\
        "TENDERSTATE=?,"\
        "CHANGEDATE=?,"\
        "NAMEOFUSER=?,"\
        "PRICEDIFF=?"
/* SqlMacros-Define of TENDERPOS **********************************************/

#define TENDERPOS_ZEIGER(x) \
        :x->TENDERNO,\
        :x->ARTICLENO,\
        :x->CONTRACTQTY,\
        :x->CONTRACTPRICE,\
        :x->REMAININGLIFE,\
        :x->ADDDISCOUNTPCT,\
        :x->AEP,\
        :x->TENDERSTATE,\
        :x->CHANGEDATE,\
        :x->NAMEOFUSER,\
        :x->PRICEDIFF
#define TENDERPOS_ZEIGERSEL(x) \
        :x->TENDERNO,\
        :x->ARTICLENO,\
        :x->CONTRACTQTY,\
        :x->CONTRACTPRICE,\
        :x->REMAININGLIFE,\
        :x->ADDDISCOUNTPCT,\
        :x->AEP,\
        :x->TENDERSTATE,\
        :x->CHANGEDATE,\
        :x->NAMEOFUSER,\
        :x->PRICEDIFF
#define TENDERPOS_UPDATE(x) \
        TENDERPOS.TENDERNO=:x->TENDERNO,\
        TENDERPOS.ARTICLENO=:x->ARTICLENO,\
        TENDERPOS.CONTRACTQTY=:x->CONTRACTQTY,\
        TENDERPOS.CONTRACTPRICE=:x->CONTRACTPRICE,\
        TENDERPOS.REMAININGLIFE=:x->REMAININGLIFE,\
        TENDERPOS.ADDDISCOUNTPCT=:x->ADDDISCOUNTPCT,\
        TENDERPOS.AEP=:x->AEP,\
        TENDERPOS.TENDERSTATE=:x->TENDERSTATE,\
        TENDERPOS.CHANGEDATE=:x->CHANGEDATE,\
        TENDERPOS.NAMEOFUSER=:x->NAMEOFUSER,\
        TENDERPOS.PRICEDIFF=:x->PRICEDIFF
/* SqlMacros390-Define of TENDERPOS *******************************************/

#define TENDERPOS_ZEIGER_390 \
        :TENDERNO,\
        :ARTICLENO,\
        :CONTRACTQTY,\
        :CONTRACTPRICE,\
        :REMAININGLIFE,\
        :ADDDISCOUNTPCT,\
        :AEP,\
        :TENDERSTATE,\
        :CHANGEDATE,\
        :NAMEOFUSER,\
        :PRICEDIFF
#define TENDERPOS_UPDATE_390 \
        TENDERNO=:TENDERNO,\
        ARTICLENO=:ARTICLENO,\
        CONTRACTQTY=:CONTRACTQTY,\
        CONTRACTPRICE=:CONTRACTPRICE,\
        REMAININGLIFE=:REMAININGLIFE,\
        ADDDISCOUNTPCT=:ADDDISCOUNTPCT,\
        AEP=:AEP,\
        TENDERSTATE=:TENDERSTATE,\
        CHANGEDATE=:CHANGEDATE,\
        NAMEOFUSER=:NAMEOFUSER,\
        PRICEDIFF=:PRICEDIFF
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of TENDERPOS ***********************************************/

#ifndef TRANSCLASS
typedef struct N_TENDERPOS {
    long TENDERNO;
    long ARTICLENO;
    long CONTRACTQTY;
    double CONTRACTPRICE;
    long REMAININGLIFE;
    double ADDDISCOUNTPCT;
    double AEP;
    char TENDERSTATE[2];
    long CHANGEDATE;
    char NAMEOFUSER[31];
    double PRICEDIFF;
} tenderposS;
#else /* TRANSCLASS */
typedef struct N_TENDERPOS {
    long TENDERNO;
    long ARTICLENO;
    long CONTRACTQTY;
    double CONTRACTPRICE;
    long REMAININGLIFE;
    double ADDDISCOUNTPCT;
    double AEP;
    char TENDERSTATE[2];
    long CHANGEDATE;
    char NAMEOFUSER[31];
    double PRICEDIFF;

    bool operator == (const N_TENDERPOS& right) const {
        return (
            TENDERNO == right.TENDERNO &&
            ARTICLENO == right.ARTICLENO &&
            CONTRACTQTY == right.CONTRACTQTY &&
            CONTRACTPRICE == right.CONTRACTPRICE &&
            REMAININGLIFE == right.REMAININGLIFE &&
            ADDDISCOUNTPCT == right.ADDDISCOUNTPCT &&
            AEP == right.AEP &&
            !strcmp(TENDERSTATE, right.TENDERSTATE) &&
            CHANGEDATE == right.CHANGEDATE &&
            !strcmp(NAMEOFUSER, right.NAMEOFUSER) &&
            PRICEDIFF == right.PRICEDIFF
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        TENDERNO = 0;
        ARTICLENO = 0;
        CONTRACTQTY = 0;
        CONTRACTPRICE = 0;
        REMAININGLIFE = 0;
        ADDDISCOUNTPCT = 0;
        AEP = 0;
        strcpy(TENDERSTATE, " " );
        CHANGEDATE = 0;
        strcpy(NAMEOFUSER, " " );
        PRICEDIFF = 0;
#endif
    }
} tenderposS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of TENDERPOS *****************************************/

struct S_TENDERPOS {
    char TENDERNO[11];
    char ARTICLENO[11];
    char CONTRACTQTY[11];
    char CONTRACTPRICE[9 + 2];
    char REMAININGLIFE[11];
    char ADDDISCOUNTPCT[5 + 2];
    char AEP[9 + 2];
    char TENDERSTATE[1 + 1];
    char CHANGEDATE[11];
    char NAMEOFUSER[30 + 1];
    char PRICEDIFF[9 + 2];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of TENDERPOS ************************/

struct O_TENDERPOS {
    char TENDERNO[11];
    char ARTICLENO[11];
    char CONTRACTQTY[11];
    char CONTRACTPRICE[9];
    char REMAININGLIFE[11];
    char ADDDISCOUNTPCT[5];
    char AEP[9];
    char TENDERSTATE[1];
    char CHANGEDATE[11];
    char NAMEOFUSER[30];
    char PRICEDIFF[9];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of TENDERPOS ***********************************/

struct C_TENDERPOS {
    long TENDERNO;
    long ARTICLENO;
    long CONTRACTQTY;
    double CONTRACTPRICE;
    long REMAININGLIFE;
    double ADDDISCOUNTPCT;
    double AEP;
    char TENDERSTATE;
    long CHANGEDATE;
    char NAMEOFUSER[31];
    double PRICEDIFF;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of TENDERPOS *********************************/

struct I_TENDERPOS {
    short TENDERNO;
    short ARTICLENO;
    short CONTRACTQTY;
    short CONTRACTPRICE;
    short REMAININGLIFE;
    short ADDDISCOUNTPCT;
    short AEP;
    short TENDERSTATE;
    short CHANGEDATE;
    short NAMEOFUSER;
    short PRICEDIFF;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of TENDERPOS *******************************************/

#if defined (BUF_DESC)
static struct buf_desc TENDERPOS_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_L , 11, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 9, 2 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_D, 9, 2 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc TENDERPOS_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_L , 11, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 9, 2 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_D, 9, 2 },
};
#endif

/* description for datatypes of TENDERPOS *************************************/

 #define TENDERPOS_S390 \
         long TENDERNO; \
         long ARTICLENO; \
         long CONTRACTQTY; \
         double CONTRACTPRICE; \
         long REMAININGLIFE; \
         double ADDDISCOUNTPCT; \
         double AEP; \
         char TENDERSTATE; \
         long CHANGEDATE; \
         char NAMEOFUSER[31]; \
         double PRICEDIFF; \



/* Copy-Function Struct to single Data TENDERPOS ******************************/

 #define TENDERPOS_S390_COPY_TO_SINGLE(_x_) \
         TENDERNO=_x_->TENDERNO;\
         ARTICLENO=_x_->ARTICLENO;\
         CONTRACTQTY=_x_->CONTRACTQTY;\
         CONTRACTPRICE=_x_->CONTRACTPRICE;\
         REMAININGLIFE=_x_->REMAININGLIFE;\
         ADDDISCOUNTPCT=_x_->ADDDISCOUNTPCT;\
         AEP=_x_->AEP;\
         TENDERSTATE=_x_->TENDERSTATE;\
         CHANGEDATE=_x_->CHANGEDATE;\
          strcpy(NAMEOFUSER,_x_->NAMEOFUSER);\
         PRICEDIFF=_x_->PRICEDIFF;\

 #define TENDERPOS_S390_COPY_TO_STRUCT(_x_) \
          _x_->TENDERNO=TENDERNO;\
          _x_->ARTICLENO=ARTICLENO;\
          _x_->CONTRACTQTY=CONTRACTQTY;\
          _x_->CONTRACTPRICE=CONTRACTPRICE;\
          _x_->REMAININGLIFE=REMAININGLIFE;\
          _x_->ADDDISCOUNTPCT=ADDDISCOUNTPCT;\
          _x_->AEP=AEP;\
          _x_->TENDERSTATE=TENDERSTATE;\
          _x_->CHANGEDATE=CHANGEDATE;\
          strcpy(_x_->NAMEOFUSER,NAMEOFUSER);\
          _x_->PRICEDIFF=PRICEDIFF;\



/* FunctionNumber-Define of TenderPos *****************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of TenderPos *************************************/


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

class CTENDERPOS : public ppDadeVirtual {
public:
    tenderposS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<tenderposS> lst; // class list

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
                     vector< tenderposS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     tenderposS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< tenderposS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<tenderposS>::iterator
                 beginList() { return lst.begin(); }
    vector<tenderposS>::iterator
                 endList  () { return lst.end  (); }

    long         GetTenderno() const { return s.TENDERNO; }
    long         GetArticleno() const { return s.ARTICLENO; }
    long         GetContractqty() const { return s.CONTRACTQTY; }
    double       GetContractprice() const { return s.CONTRACTPRICE; }
    long         GetRemaininglife() const { return s.REMAININGLIFE; }
    double       GetAdddiscountpct() const { return s.ADDDISCOUNTPCT; }
    double       GetAep() const { return s.AEP; }
    char         GetTenderstate() const { return s.TENDERSTATE[0]; }
    long         GetChangedate() const { return s.CHANGEDATE; }
    const char*  GetNameofuser(ppString & t) const { t = s.NAMEOFUSER; t.erasespace(ppString::END); return t.c_str(); }
    double       GetPricediff() const { return s.PRICEDIFF; }

    const tenderposS &
                 GetStruct() const { return s; }
    void         SetTenderno(long t) { s.TENDERNO = t; }
    void         SetArticleno(long t) { s.ARTICLENO = t; }
    void         SetContractqty(long t) { s.CONTRACTQTY = t; }
    void         SetContractprice(double t) { s.CONTRACTPRICE = t; }
    void         SetRemaininglife(long t) { s.REMAININGLIFE = t; }
    void         SetAdddiscountpct(double t) { s.ADDDISCOUNTPCT = t; }
    void         SetAep(double t) { s.AEP = t; }
    void         SetTenderstate(char t) { s.TENDERSTATE[0] = t; s.TENDERSTATE[1] = '\0';}
    void         SetChangedate(long t) { s.CHANGEDATE = t; }
    void         SetNameofuser(const ppString & t) { ppGStrCopy(s.NAMEOFUSER, t.c_str(), L_TENDERPOS_NAMEOFUSER); }
    void         SetPricediff(double t) { s.PRICEDIFF = t; }

    void         SetStruct(const tenderposS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CTENDERPOS() {
        ::buf_default((void *)&s, TENDERPOS_BES, TENDERPOS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CTENDERPOS() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, TENDERPOS_BES, TENDERPOS_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, TENDERPOS_BES, (int)TENDERPOS_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, TENDERPOS_BES, (int)TENDERPOS_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_TENDERPOS & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.NAMEOFUSER);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, TENDERPOS_BES, (int)TENDERPOS_ANZ, error_msg);
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
/* CreateSqlStatement of TENDERPOS ********************************************/

 #define TENDERPOS_CREATE(x) EXEC SQL create table x (\
         TENDERNO integer default 0 not null,\
         ARTICLENO integer default 0 not null,\
         CONTRACTQTY integer default 0 not null,\
         CONTRACTPRICE decimal(9,2) default 0 not null,\
         REMAININGLIFE integer default 0 not null,\
         ADDDISCOUNTPCT decimal(5,2) default 0 not null,\
         AEP decimal(9,2) default 0 not null,\
         TENDERSTATE char(1) default " " not null,\
         CHANGEDATE integer default 0 not null,\
         NAMEOFUSER varchar(30,0) default " " not null,\
         PRICEDIFF decimal(9,2) default 0 not null) in ksc extent size 784 next size 80 lock mode row;



/* CreateIndexStatement of TENDERPOS ******************************************/

 #define TENDERPOS_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_tenderpos_1 on _X_(\
              TenderNo,\
              ArticleNo ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of TENDERPOS ******************************************/

 #define TENDERPOS_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_tenderpos_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
