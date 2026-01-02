#ifndef __PP_DELIVERYADVICEVATTOTALS_H_
#define __PP_DELIVERYADVICEVATTOTALS_H_

/******************************************************************************/
/* c:\prri\Headerfiles\Deliveryadvicevattotals ********************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of DELIVERYADVICEVATTOTALS ***********************************/

#define L_DELIVERYADVICEVATTOTALS_BRANCHNO 6
#define L_DELIVERYADVICEVATTOTALS_CUSTOMERNO 11
#define L_DELIVERYADVICEVATTOTALS_DELIVERYADVICEDATE 11
#define L_DELIVERYADVICEVATTOTALS_DELIVERYADVICENO 10
#define L_DELIVERYADVICEVATTOTALS_DAVAT 1
#define L_DELIVERYADVICEVATTOTALS_VATPERCENTAGE 5
#define N_DELIVERYADVICEVATTOTALS_VATPERCENTAGE 2
#define L_DELIVERYADVICEVATTOTALS_NETVALUE 11
#define N_DELIVERYADVICEVATTOTALS_NETVALUE 4
#define L_DELIVERYADVICEVATTOTALS_VATVALUE 11
#define N_DELIVERYADVICEVATTOTALS_VATVALUE 4

/* Length/Count-Define of DELIVERYADVICEVATTOTALS *****************************/

#define LS_DELIVERYADVICEVATTOTALS_BRANCHNO 5 + 1
#define LS_DELIVERYADVICEVATTOTALS_CUSTOMERNO 10 + 1
#define LS_DELIVERYADVICEVATTOTALS_DELIVERYADVICEDATE 10 + 1
#define LS_DELIVERYADVICEVATTOTALS_DELIVERYADVICENO 10 + 1
#define LS_DELIVERYADVICEVATTOTALS_DAVAT 1 + 1
#define LS_DELIVERYADVICEVATTOTALS_VATPERCENTAGE 5 + 2
#define LS_DELIVERYADVICEVATTOTALS_NETVALUE 11 + 2
#define LS_DELIVERYADVICEVATTOTALS_VATVALUE 11 + 2

#define DELIVERYADVICEVATTOTALSBRANCHNO 0
#define DELIVERYADVICEVATTOTALSCUSTOMERNO 1
#define DELIVERYADVICEVATTOTALSDELIVERYADVICEDATE 2
#define DELIVERYADVICEVATTOTALSDELIVERYADVICENO 3
#define DELIVERYADVICEVATTOTALSDAVAT 4
#define DELIVERYADVICEVATTOTALSVATPERCENTAGE 5
#define DELIVERYADVICEVATTOTALSNETVALUE 6
#define DELIVERYADVICEVATTOTALSVATVALUE 7

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define DELIVERYADVICEVATTOTALS_H
#define DELIVERYADVICEVATTOTALS_ANZ ( sizeof(DELIVERYADVICEVATTOTALS_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of DELIVERYADVICEVATTOTALS ***************************************/

#define DELIVERYADVICEVATTOTALS_LISTE \
        DADUMMY.BRANCHNO,\
        DADUMMY.CUSTOMERNO,\
        DADUMMY.DELIVERYADVICEDATE,\
        DADUMMY.DELIVERYADVICENO,\
        DADUMMY.DAVAT,\
        DADUMMY.VATPERCENTAGE,\
        DADUMMY.NETVALUE,\
        DADUMMY.VATVALUE
#define DELIVERYADVICEVATTOTALS_LISTE_390 \
        BRANCHNO,\
        CUSTOMERNO,\
        DELIVERYADVICEDATE,\
        DELIVERYADVICENO,\
        DAVAT,\
        VATPERCENTAGE,\
        NETVALUE,\
        VATVALUE
#define DELIVERYADVICEVATTOTALS_PLISTE \
        "DADUMMY.BRANCHNO,"\
        "DADUMMY.CUSTOMERNO,"\
        "DADUMMY.DELIVERYADVICEDATE,"\
        "DADUMMY.DELIVERYADVICENO,"\
        "DADUMMY.DAVAT,"\
        "DADUMMY.VATPERCENTAGE,"\
        "DADUMMY.NETVALUE,"\
        "DADUMMY.VATVALUE"
#define DELIVERYADVICEVATTOTALS_PELISTE \
        "BRANCHNO,"\
        "CUSTOMERNO,"\
        "DELIVERYADVICEDATE,"\
        "DELIVERYADVICENO,"\
        "DAVAT,"\
        "VATPERCENTAGE,"\
        "NETVALUE,"\
        "VATVALUE"
#define DELIVERYADVICEVATTOTALS_UPDLISTE \
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "DELIVERYADVICEDATE=?,"\
        "DELIVERYADVICENO=?,"\
        "DAVAT=?,"\
        "VATPERCENTAGE=?,"\
        "NETVALUE=?,"\
        "VATVALUE=?"
/* SqlMacros-Define of DELIVERYADVICEVATTOTALS ********************************/

#define DELIVERYADVICEVATTOTALS_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->DELIVERYADVICEDATE,\
        :x->DELIVERYADVICENO,\
        :x->DAVAT,\
        :x->VATPERCENTAGE,\
        :x->NETVALUE,\
        :x->VATVALUE
#define DELIVERYADVICEVATTOTALS_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->DELIVERYADVICEDATE,\
        :x->DELIVERYADVICENO,\
        :x->DAVAT,\
        :x->VATPERCENTAGE,\
        :x->NETVALUE,\
        :x->VATVALUE
#define DELIVERYADVICEVATTOTALS_UPDATE(x) \
        DADUMMY.BRANCHNO=:x->BRANCHNO,\
        DADUMMY.CUSTOMERNO=:x->CUSTOMERNO,\
        DADUMMY.DELIVERYADVICEDATE=:x->DELIVERYADVICEDATE,\
        DADUMMY.DELIVERYADVICENO=:x->DELIVERYADVICENO,\
        DADUMMY.DAVAT=:x->DAVAT,\
        DADUMMY.VATPERCENTAGE=:x->VATPERCENTAGE,\
        DADUMMY.NETVALUE=:x->NETVALUE,\
        DADUMMY.VATVALUE=:x->VATVALUE
/* SqlMacros390-Define of DELIVERYADVICEVATTOTALS *****************************/

#define DELIVERYADVICEVATTOTALS_ZEIGER_390 \
        :BRANCHNO,\
        :CUSTOMERNO,\
        :DELIVERYADVICEDATE,\
        :DELIVERYADVICENO,\
        :DAVAT,\
        :VATPERCENTAGE,\
        :NETVALUE,\
        :VATVALUE
#define DELIVERYADVICEVATTOTALS_UPDATE_390 \
        BRANCHNO=:BRANCHNO,\
        CUSTOMERNO=:CUSTOMERNO,\
        DELIVERYADVICEDATE=:DELIVERYADVICEDATE,\
        DELIVERYADVICENO=:DELIVERYADVICENO,\
        DAVAT=:DAVAT,\
        VATPERCENTAGE=:VATPERCENTAGE,\
        NETVALUE=:NETVALUE,\
        VATVALUE=:VATVALUE
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of DELIVERYADVICEVATTOTALS *********************************/

#ifndef TRANSCLASS
typedef struct N_DELIVERYADVICEVATTOTALS {
    short BRANCHNO;
    long CUSTOMERNO;
    long DELIVERYADVICEDATE;
    char DELIVERYADVICENO[11];
    char DAVAT[2];
    double VATPERCENTAGE;
    double NETVALUE;
    double VATVALUE;
} deliveryadvicevattotalsS;
#else /* TRANSCLASS */
typedef struct N_DELIVERYADVICEVATTOTALS {
    short BRANCHNO;
    long CUSTOMERNO;
    long DELIVERYADVICEDATE;
    char DELIVERYADVICENO[11];
    char DAVAT[2];
    double VATPERCENTAGE;
    double NETVALUE;
    double VATVALUE;

    bool operator == (const N_DELIVERYADVICEVATTOTALS& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            CUSTOMERNO == right.CUSTOMERNO &&
            DELIVERYADVICEDATE == right.DELIVERYADVICEDATE &&
            !strcmp(DELIVERYADVICENO, right.DELIVERYADVICENO) &&
            !strcmp(DAVAT, right.DAVAT) &&
            VATPERCENTAGE == right.VATPERCENTAGE &&
            NETVALUE == right.NETVALUE &&
            VATVALUE == right.VATVALUE
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
        strcpy(DAVAT, " " );
        VATPERCENTAGE = 0;
        NETVALUE = 0;
        VATVALUE = 0;
#endif
    }
} deliveryadvicevattotalsS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of DELIVERYADVICEVATTOTALS ***************************/

struct S_DELIVERYADVICEVATTOTALS {
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char DELIVERYADVICEDATE[11];
    char DELIVERYADVICENO[10 + 1];
    char DAVAT[1 + 1];
    char VATPERCENTAGE[5 + 2];
    char NETVALUE[11 + 2];
    char VATVALUE[11 + 2];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of DELIVERYADVICEVATTOTALS **********/

struct O_DELIVERYADVICEVATTOTALS {
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char DELIVERYADVICEDATE[11];
    char DELIVERYADVICENO[10];
    char DAVAT[1];
    char VATPERCENTAGE[5];
    char NETVALUE[11];
    char VATVALUE[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of DELIVERYADVICEVATTOTALS *********************/

struct C_DELIVERYADVICEVATTOTALS {
    short BRANCHNO;
    long CUSTOMERNO;
    long DELIVERYADVICEDATE;
    char DELIVERYADVICENO[11];
    char DAVAT;
    double VATPERCENTAGE;
    double NETVALUE;
    double VATVALUE;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of DELIVERYADVICEVATTOTALS *******************/

struct I_DELIVERYADVICEVATTOTALS {
    short BRANCHNO;
    short CUSTOMERNO;
    short DELIVERYADVICEDATE;
    short DELIVERYADVICENO;
    short DAVAT;
    short VATPERCENTAGE;
    short NETVALUE;
    short VATVALUE;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of DELIVERYADVICEVATTOTALS *****************************/

#if defined (BUF_DESC)
static struct buf_desc DELIVERYADVICEVATTOTALS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 10, 0 },
   { TYP_C, 1, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 11, 4 },
   { TYP_D, 11, 4 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc DELIVERYADVICEVATTOTALS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 10, 0 },
   { TYP_C, 1, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 11, 4 },
   { TYP_D, 11, 4 },
};
#endif

/* description for datatypes of DELIVERYADVICEVATTOTALS ***********************/

 #define DELIVERYADVICEVATTOTALS_S390 \
         short BRANCHNO; \
         long CUSTOMERNO; \
         long DELIVERYADVICEDATE; \
         char DELIVERYADVICENO[11]; \
         char DAVAT; \
         double VATPERCENTAGE; \
         double NETVALUE; \
         double VATVALUE; \



/* Copy-Function Struct to single Data DELIVERYADVICEVATTOTALS ****************/

 #define DELIVERYADVICEVATTOTALS_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
         DELIVERYADVICEDATE=_x_->DELIVERYADVICEDATE;\
          strcpy(DELIVERYADVICENO,_x_->DELIVERYADVICENO);\
         DAVAT=_x_->DAVAT;\
         VATPERCENTAGE=_x_->VATPERCENTAGE;\
         NETVALUE=_x_->NETVALUE;\
         VATVALUE=_x_->VATVALUE;\

 #define DELIVERYADVICEVATTOTALS_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->DELIVERYADVICEDATE=DELIVERYADVICEDATE;\
          strcpy(_x_->DELIVERYADVICENO,DELIVERYADVICENO);\
          _x_->DAVAT=DAVAT;\
          _x_->VATPERCENTAGE=VATPERCENTAGE;\
          _x_->NETVALUE=NETVALUE;\
          _x_->VATVALUE=VATVALUE;\



/* FunctionNumber-Define of Deliveryadvicevattotals ***************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of Deliveryadvicevattotals ***********************/


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

class CDELIVERYADVICEVATTOTALS : public ppDadeVirtual {
public:
    deliveryadvicevattotalsS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<deliveryadvicevattotalsS> lst; // class list

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
                     vector< deliveryadvicevattotalsS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     deliveryadvicevattotalsS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< deliveryadvicevattotalsS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<deliveryadvicevattotalsS>::iterator
                 beginList() { return lst.begin(); }
    vector<deliveryadvicevattotalsS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    long         GetDeliveryadvicedate() const { return s.DELIVERYADVICEDATE; }
    const char*  GetDeliveryadviceno(ppString & t) const { t = s.DELIVERYADVICENO; t.erasespace(ppString::END); return t.c_str(); }
    char         GetDavat() const { return s.DAVAT[0]; }
    double       GetVatpercentage() const { return s.VATPERCENTAGE; }
    double       GetNetvalue() const { return s.NETVALUE; }
    double       GetVatvalue() const { return s.VATVALUE; }

    const deliveryadvicevattotalsS &
                 GetStruct() const { return s; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetDeliveryadvicedate(long t) { s.DELIVERYADVICEDATE = t; }
    void         SetDeliveryadviceno(const ppString & t) { ppGStrCopy(s.DELIVERYADVICENO, t.c_str(), L_DELIVERYADVICEVATTOTALS_DELIVERYADVICENO); }
    void         SetDavat(char t) { s.DAVAT[0] = t; s.DAVAT[1] = '\0';}
    void         SetVatpercentage(double t) { s.VATPERCENTAGE = t; }
    void         SetNetvalue(double t) { s.NETVALUE = t; }
    void         SetVatvalue(double t) { s.VATVALUE = t; }

    void         SetStruct(const deliveryadvicevattotalsS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CDELIVERYADVICEVATTOTALS() {
        ::buf_default((void *)&s, DELIVERYADVICEVATTOTALS_BES, DELIVERYADVICEVATTOTALS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CDELIVERYADVICEVATTOTALS() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, DELIVERYADVICEVATTOTALS_BES, DELIVERYADVICEVATTOTALS_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, DELIVERYADVICEVATTOTALS_BES, (int)DELIVERYADVICEVATTOTALS_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, DELIVERYADVICEVATTOTALS_BES, (int)DELIVERYADVICEVATTOTALS_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_DELIVERYADVICEVATTOTALS & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.DELIVERYADVICENO);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, DELIVERYADVICEVATTOTALS_BES, (int)DELIVERYADVICEVATTOTALS_ANZ, error_msg);
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
/* CreateSqlStatement of DELIVERYADVICEVATTOTALS ******************************/

 #define DELIVERYADVICEVATTOTALS_CREATE(x) EXEC SQL create table x (\
         BRANCHNO smallint default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         DELIVERYADVICEDATE integer default 0 not null,\
         DELIVERYADVICENO varchar(10,0) default " " not null,\
         DAVAT char(1) default " " not null,\
         VATPERCENTAGE decimal(5,2) default 0 not null,\
         NETVALUE decimal(11,4) default 0 not null,\
         VATVALUE decimal(11,4) default 0 not null) extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of DELIVERYADVICEVATTOTALS ****************************/

 #define DELIVERYADVICEVATTOTALS_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
/* DeleteIndexStatement of DELIVERYADVICEVATTOTALS ****************************/

 #define DELIVERYADVICEVATTOTALS_DELETE_INDEX(_X_)\
              _X_ = 0;\


#endif   // GUARD
