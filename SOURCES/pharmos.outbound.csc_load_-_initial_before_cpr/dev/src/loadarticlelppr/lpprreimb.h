#ifndef __PP_LPPRREIMB_H_
#define __PP_LPPRREIMB_H_

/******************************************************************************/
/* c:\Marathon\orderentry\csc_load\trunk\dev\src\loadarticlelppr\lpprreimb ****/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <pplib/bufkon.h>

/* Length-Define of LPPRREIMB *************************************************/

#define L_LPPRREIMB_CODE_LPPR 15
#define L_LPPRREIMB_DATEFROM 11
#define L_LPPRREIMB_REIMBURSEMENT_VAL 9
#define N_LPPRREIMB_REIMBURSEMENT_VAL 2
#define L_LPPRREIMB_LPPR_DESC 400

/* Length/Count-Define of LPPRREIMB *******************************************/

#define LS_LPPRREIMB_CODE_LPPR 15 + 1
#define LS_LPPRREIMB_DATEFROM 10 + 1
#define LS_LPPRREIMB_REIMBURSEMENT_VAL 9 + 2
#define LS_LPPRREIMB_LPPR_DESC 400 + 1

#define LPPRREIMBCODE_LPPR 0
#define LPPRREIMBDATEFROM 1
#define LPPRREIMBREIMBURSEMENT_VAL 2
#define LPPRREIMBLPPR_DESC 3

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define LPPRREIMB_H
#define LPPRREIMB_ANZ ( sizeof(LPPRREIMB_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of LPPRREIMB *****************************************************/

#define LPPRREIMB_LISTE \
        LPPRREIMB.CODE_LPPR,\
        LPPRREIMB.DATEFROM,\
        LPPRREIMB.REIMBURSEMENT_VAL,\
        LPPRREIMB.LPPR_DESC
#define LPPRREIMB_LISTE_390 \
        CODE_LPPR,\
        DATEFROM,\
        REIMBURSEMENT_VAL,\
        LPPR_DESC
#define LPPRREIMB_PLISTE \
        "LPPRREIMB.CODE_LPPR,"\
        "LPPRREIMB.DATEFROM,"\
        "LPPRREIMB.REIMBURSEMENT_VAL,"\
        "LPPRREIMB.LPPR_DESC"
#define LPPRREIMB_PELISTE \
        "CODE_LPPR,"\
        "DATEFROM,"\
        "REIMBURSEMENT_VAL,"\
        "LPPR_DESC"
#define LPPRREIMB_UPDLISTE \
        "CODE_LPPR=?,"\
        "DATEFROM=?,"\
        "REIMBURSEMENT_VAL=?,"\
        "LPPR_DESC=?"
/* SqlMacros-Define of LPPRREIMB **********************************************/

#define LPPRREIMB_ZEIGER(x) \
        :x->CODE_LPPR,\
        :x->DATEFROM,\
        :x->REIMBURSEMENT_VAL,\
        :x->LPPR_DESC
#define LPPRREIMB_ZEIGERSEL(x) \
        :x->CODE_LPPR,\
        :x->DATEFROM,\
        :x->REIMBURSEMENT_VAL,\
        :x->LPPR_DESC
#define LPPRREIMB_UPDATE(x) \
        LPPRREIMB.CODE_LPPR=:x->CODE_LPPR,\
        LPPRREIMB.DATEFROM=:x->DATEFROM,\
        LPPRREIMB.REIMBURSEMENT_VAL=:x->REIMBURSEMENT_VAL,\
        LPPRREIMB.LPPR_DESC=:x->LPPR_DESC
/* SqlMacros390-Define of LPPRREIMB *******************************************/

#define LPPRREIMB_ZEIGER_390 \
        :CODE_LPPR,\
        :DATEFROM,\
        :REIMBURSEMENT_VAL,\
        :LPPR_DESC
#define LPPRREIMB_UPDATE_390 \
        CODE_LPPR=:CODE_LPPR,\
        DATEFROM=:DATEFROM,\
        REIMBURSEMENT_VAL=:REIMBURSEMENT_VAL,\
        LPPR_DESC=:LPPR_DESC
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of LPPRREIMB ***********************************************/

#ifndef TRANSCLASS
typedef struct N_LPPRREIMB {
    char CODE_LPPR[16];
    long DATEFROM;
    double REIMBURSEMENT_VAL;
    char LPPR_DESC[401];
} lpprreimbS;
#else /* TRANSCLASS */
typedef struct N_LPPRREIMB {
    char CODE_LPPR[16];
    long DATEFROM;
    double REIMBURSEMENT_VAL;
    char LPPR_DESC[401];

    bool operator == (const N_LPPRREIMB& right) const {
        return (
            !strcmp(CODE_LPPR, right.CODE_LPPR) &&
            DATEFROM == right.DATEFROM &&
            REIMBURSEMENT_VAL == right.REIMBURSEMENT_VAL &&
            !strcmp(LPPR_DESC, right.LPPR_DESC)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        strcpy(CODE_LPPR, " " );
        DATEFROM = 0;
        REIMBURSEMENT_VAL = 0;
        strcpy(LPPR_DESC, " " );
#endif
    }
} lpprreimbS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of LPPRREIMB *****************************************/

struct S_LPPRREIMB {
    char CODE_LPPR[15 + 1];
    char DATEFROM[11];
    char REIMBURSEMENT_VAL[9 + 2];
    char LPPR_DESC[400 + 1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of LPPRREIMB ************************/

struct O_LPPRREIMB {
    char CODE_LPPR[15];
    char DATEFROM[11];
    char REIMBURSEMENT_VAL[9];
    char LPPR_DESC[400];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of LPPRREIMB ***********************************/

struct C_LPPRREIMB {
    char CODE_LPPR[16];
    long DATEFROM;
    double REIMBURSEMENT_VAL;
    char LPPR_DESC[401];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of LPPRREIMB *********************************/

struct I_LPPRREIMB {
    short CODE_LPPR;
    short DATEFROM;
    short REIMBURSEMENT_VAL;
    short LPPR_DESC;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of LPPRREIMB *******************************************/

#if defined (BUF_DESC)
static struct buf_desc LPPRREIMB_BES [] = {
   { TYP_C, 15, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_C, 400, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc LPPRREIMB_BES [] = {
   { TYP_C, 15, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_C, 400, 0 },
};
#endif

/* description for datatypes of LPPRREIMB *************************************/

 #define LPPRREIMB_S390 \
         char CODE_LPPR[16]; \
         long DATEFROM; \
         double REIMBURSEMENT_VAL; \
         char LPPR_DESC[401]; \



/* Copy-Function Struct to single Data LPPRREIMB ******************************/

 #define LPPRREIMB_S390_COPY_TO_SINGLE(_x_) \
          strcpy(CODE_LPPR,_x_->CODE_LPPR);\
         DATEFROM=_x_->DATEFROM;\
         REIMBURSEMENT_VAL=_x_->REIMBURSEMENT_VAL;\
          strcpy(LPPR_DESC,_x_->LPPR_DESC);\

 #define LPPRREIMB_S390_COPY_TO_STRUCT(_x_) \
          strcpy(_x_->CODE_LPPR,CODE_LPPR);\
          _x_->DATEFROM=DATEFROM;\
          _x_->REIMBURSEMENT_VAL=REIMBURSEMENT_VAL;\
          strcpy(_x_->LPPR_DESC,LPPR_DESC);\



/* FunctionNumber-Define of lpprreimb *****************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of lpprreimb *************************************/


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

class CLPPRREIMB : public ppDadeVirtual {
public:
    lpprreimbS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<lpprreimbS> lst; // class list

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
                     vector< lpprreimbS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     lpprreimbS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< lpprreimbS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<lpprreimbS>::iterator
                 beginList() { return lst.begin(); }
    vector<lpprreimbS>::iterator
                 endList  () { return lst.end  (); }

    const char*  GetCode_lppr(ppString & t) const { t = s.CODE_LPPR; t.erasespace(ppString::END); return t.c_str(); }
    long         GetDatefrom() const { return s.DATEFROM; }
    double       GetReimbursement_val() const { return s.REIMBURSEMENT_VAL; }
    const char*  GetLppr_desc(ppString & t) const { t = s.LPPR_DESC; t.erasespace(ppString::END); return t.c_str(); }

    const lpprreimbS &
                 GetStruct() const { return s; }
    void         SetCode_lppr(const ppString & t) { ppGStrCopy(s.CODE_LPPR, t.c_str(), L_LPPRREIMB_CODE_LPPR); }
    void         SetDatefrom(long t) { s.DATEFROM = t; }
    void         SetReimbursement_val(double t) { s.REIMBURSEMENT_VAL = t; }
    void         SetLppr_desc(const ppString & t) { ppGStrCopy(s.LPPR_DESC, t.c_str(), L_LPPRREIMB_LPPR_DESC); }

    void         SetStruct(const lpprreimbS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CLPPRREIMB() {
        ::buf_default((void *)&s, LPPRREIMB_BES, LPPRREIMB_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CLPPRREIMB() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, LPPRREIMB_BES, LPPRREIMB_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, LPPRREIMB_BES, (int)LPPRREIMB_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, LPPRREIMB_BES, (int)LPPRREIMB_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_LPPRREIMB & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.CODE_LPPR);
        ppGStripLast(d.LPPR_DESC);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, LPPRREIMB_BES, (int)LPPRREIMB_ANZ, error_msg);
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
/* CreateSqlStatement of LPPRREIMB ********************************************/

 #define LPPRREIMB_CREATE(x) EXEC SQL create table x (\
         CODE_LPPR char(15) default " " not null,\
         DATEFROM integer default 0 not null,\
         REIMBURSEMENT_VAL decimal(9,2) default 0 not null,\
         LPPR_DESC char(400) default " " not null) in ksc extent size 40 next size 8 lock mode row;



/* CreateIndexStatement of LPPRREIMB ******************************************/

 #define LPPRREIMB_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_lpprreimb_1 on _X_(\
              code_lppr ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of LPPRREIMB ******************************************/

 #define LPPRREIMB_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_lpprreimb_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
