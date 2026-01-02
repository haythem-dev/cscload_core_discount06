#ifndef __PP_CUSTOMERBUSINESSHOURS_H_
#define __PP_CUSTOMERBUSINESSHOURS_H_

/******************************************************************************/
/* c:\temp\customerbusinesshours **********************************************/
/* produced by DADE 6.22.0 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of CUSTOMERBUSINESSHOURS *************************************/

#define L_CUSTOMERBUSINESSHOURS_WEEKDAY 6
#define L_CUSTOMERBUSINESSHOURS_BRANCHNO 6
#define L_CUSTOMERBUSINESSHOURS_CUSTOMERNO 11
#define L_CUSTOMERBUSINESSHOURS_BUSINESSHOURSSTART 11
#define L_CUSTOMERBUSINESSHOURS_BUSINESSHOURSEND 11

/* Length/Count-Define of CUSTOMERBUSINESSHOURS *******************************/

#define LS_CUSTOMERBUSINESSHOURS_WEEKDAY 5 + 1
#define LS_CUSTOMERBUSINESSHOURS_BRANCHNO 5 + 1
#define LS_CUSTOMERBUSINESSHOURS_CUSTOMERNO 10 + 1
#define LS_CUSTOMERBUSINESSHOURS_BUSINESSHOURSSTART 10 + 1
#define LS_CUSTOMERBUSINESSHOURS_BUSINESSHOURSEND 10 + 1

#define CUSTOMERBUSINESSHOURSWEEKDAY 0
#define CUSTOMERBUSINESSHOURSBRANCHNO 1
#define CUSTOMERBUSINESSHOURSCUSTOMERNO 2
#define CUSTOMERBUSINESSHOURSBUSINESSHOURSSTART 3
#define CUSTOMERBUSINESSHOURSBUSINESSHOURSEND 4

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define CUSTOMERBUSINESSHOURS_H
#define CUSTOMERBUSINESSHOURS_ANZ ( sizeof(CUSTOMERBUSINESSHOURS_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of CUSTOMERBUSINESSHOURS *****************************************/

#define CUSTOMERBUSINESSHOURS_LISTE \
        CUSTOMERBUSINESSHOURS.WEEKDAY,\
        CUSTOMERBUSINESSHOURS.BRANCHNO,\
        CUSTOMERBUSINESSHOURS.CUSTOMERNO,\
        CUSTOMERBUSINESSHOURS.BUSINESSHOURSSTART,\
        CUSTOMERBUSINESSHOURS.BUSINESSHOURSEND
#define CUSTOMERBUSINESSHOURS_LISTE_390 \
        WEEKDAY,\
        BRANCHNO,\
        CUSTOMERNO,\
        BUSINESSHOURSSTART,\
        BUSINESSHOURSEND
#define CUSTOMERBUSINESSHOURS_PLISTE \
        "CUSTOMERBUSINESSHOURS.WEEKDAY,"\
        "CUSTOMERBUSINESSHOURS.BRANCHNO,"\
        "CUSTOMERBUSINESSHOURS.CUSTOMERNO,"\
        "CUSTOMERBUSINESSHOURS.BUSINESSHOURSSTART,"\
        "CUSTOMERBUSINESSHOURS.BUSINESSHOURSEND"
#define CUSTOMERBUSINESSHOURS_PELISTE \
        "WEEKDAY,"\
        "BRANCHNO,"\
        "CUSTOMERNO,"\
        "BUSINESSHOURSSTART,"\
        "BUSINESSHOURSEND"
#define CUSTOMERBUSINESSHOURS_UPDLISTE \
        "WEEKDAY=?,"\
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "BUSINESSHOURSSTART=?,"\
        "BUSINESSHOURSEND=?"
/* SqlMacros-Define of CUSTOMERBUSINESSHOURS **********************************/

#define CUSTOMERBUSINESSHOURS_ZEIGER(x) \
        :x->WEEKDAY,\
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->BUSINESSHOURSSTART,\
        :x->BUSINESSHOURSEND
#define CUSTOMERBUSINESSHOURS_ZEIGERSEL(x) \
        :x->WEEKDAY,\
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->BUSINESSHOURSSTART,\
        :x->BUSINESSHOURSEND
#define CUSTOMERBUSINESSHOURS_UPDATE(x) \
        CUSTOMERBUSINESSHOURS.WEEKDAY=:x->WEEKDAY,\
        CUSTOMERBUSINESSHOURS.BRANCHNO=:x->BRANCHNO,\
        CUSTOMERBUSINESSHOURS.CUSTOMERNO=:x->CUSTOMERNO,\
        CUSTOMERBUSINESSHOURS.BUSINESSHOURSSTART=:x->BUSINESSHOURSSTART,\
        CUSTOMERBUSINESSHOURS.BUSINESSHOURSEND=:x->BUSINESSHOURSEND
/* SqlMacros390-Define of CUSTOMERBUSINESSHOURS *******************************/

#define CUSTOMERBUSINESSHOURS_ZEIGER_390 \
        :WEEKDAY,\
        :BRANCHNO,\
        :CUSTOMERNO,\
        :BUSINESSHOURSSTART,\
        :BUSINESSHOURSEND
#define CUSTOMERBUSINESSHOURS_UPDATE_390 \
        WEEKDAY=:WEEKDAY,\
        BRANCHNO=:BRANCHNO,\
        CUSTOMERNO=:CUSTOMERNO,\
        BUSINESSHOURSSTART=:BUSINESSHOURSSTART,\
        BUSINESSHOURSEND=:BUSINESSHOURSEND
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of CUSTOMERBUSINESSHOURS ***********************************/

#ifndef TRANSCLASS
typedef struct N_CUSTOMERBUSINESSHOURS {
    short WEEKDAY;
    short BRANCHNO;
    long CUSTOMERNO;
    long BUSINESSHOURSSTART;
    long BUSINESSHOURSEND;
} customerbusinesshoursS;
#else /* TRANSCLASS */
typedef struct N_CUSTOMERBUSINESSHOURS {
    short WEEKDAY;
    short BRANCHNO;
    long CUSTOMERNO;
    long BUSINESSHOURSSTART;
    long BUSINESSHOURSEND;

    bool operator == (const N_CUSTOMERBUSINESSHOURS& right) const {
        return (
            WEEKDAY == right.WEEKDAY &&
            BRANCHNO == right.BRANCHNO &&
            CUSTOMERNO == right.CUSTOMERNO &&
            BUSINESSHOURSSTART == right.BUSINESSHOURSSTART &&
            BUSINESSHOURSEND == right.BUSINESSHOURSEND
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        WEEKDAY = 0;
        BRANCHNO = 0;
        CUSTOMERNO = 0;
        BUSINESSHOURSSTART = 0;
        BUSINESSHOURSEND = 0;
#endif
    }
} customerbusinesshoursS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of CUSTOMERBUSINESSHOURS *****************************/

struct S_CUSTOMERBUSINESSHOURS {
    char WEEKDAY[7];
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char BUSINESSHOURSSTART[11];
    char BUSINESSHOURSEND[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of CUSTOMERBUSINESSHOURS ************/

struct O_CUSTOMERBUSINESSHOURS {
    char WEEKDAY[7];
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char BUSINESSHOURSSTART[11];
    char BUSINESSHOURSEND[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of CUSTOMERBUSINESSHOURS ***********************/

struct C_CUSTOMERBUSINESSHOURS {
    short WEEKDAY;
    short BRANCHNO;
    long CUSTOMERNO;
    long BUSINESSHOURSSTART;
    long BUSINESSHOURSEND;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of CUSTOMERBUSINESSHOURS *********************/

struct I_CUSTOMERBUSINESSHOURS {
    short WEEKDAY;
    short BRANCHNO;
    short CUSTOMERNO;
    short BUSINESSHOURSSTART;
    short BUSINESSHOURSEND;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CUSTOMERBUSINESSHOURS *******************************/

#if defined (BUF_DESC)
static struct buf_desc CUSTOMERBUSINESSHOURS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CUSTOMERBUSINESSHOURS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* description for datatypes of CUSTOMERBUSINESSHOURS *************************/

 #define CUSTOMERBUSINESSHOURS_S390 \
         short WEEKDAY; \
         short BRANCHNO; \
         long CUSTOMERNO; \
         long BUSINESSHOURSSTART; \
         long BUSINESSHOURSEND; \



/* Copy-Function Struct to single Data CUSTOMERBUSINESSHOURS ******************/

 #define CUSTOMERBUSINESSHOURS_S390_COPY_TO_SINGLE(_x_) \
         WEEKDAY=_x_->WEEKDAY;\
         BRANCHNO=_x_->BRANCHNO;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
         BUSINESSHOURSSTART=_x_->BUSINESSHOURSSTART;\
         BUSINESSHOURSEND=_x_->BUSINESSHOURSEND;\

 #define CUSTOMERBUSINESSHOURS_S390_COPY_TO_STRUCT(_x_) \
          _x_->WEEKDAY=WEEKDAY;\
          _x_->BRANCHNO=BRANCHNO;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->BUSINESSHOURSSTART=BUSINESSHOURSSTART;\
          _x_->BUSINESSHOURSEND=BUSINESSHOURSEND;\



/* FunctionNumber-Define of customerbusinesshours *****************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of customerbusinesshours *************************/


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

class CCUSTOMERBUSINESSHOURS : public ppDadeVirtual {
public:
    customerbusinesshoursS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<customerbusinesshoursS> lst; // class list

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
                     vector< customerbusinesshoursS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     customerbusinesshoursS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< customerbusinesshoursS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<customerbusinesshoursS>::iterator
                 beginList() { return lst.begin(); }
    vector<customerbusinesshoursS>::iterator
                 endList  () { return lst.end  (); }

    short        GetWeekday() const { return s.WEEKDAY; }
    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    long         GetBusinesshoursstart() const { return s.BUSINESSHOURSSTART; }
    long         GetBusinesshoursend() const { return s.BUSINESSHOURSEND; }

    const customerbusinesshoursS &
                 GetStruct() const { return s; }
    void         SetWeekday(short t) { s.WEEKDAY = t; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetBusinesshoursstart(long t) { s.BUSINESSHOURSSTART = t; }
    void         SetBusinesshoursend(long t) { s.BUSINESSHOURSEND = t; }

    void         SetStruct(const customerbusinesshoursS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCUSTOMERBUSINESSHOURS() {
        ::buf_default((void *)&s, CUSTOMERBUSINESSHOURS_BES, CUSTOMERBUSINESSHOURS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCUSTOMERBUSINESSHOURS() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CUSTOMERBUSINESSHOURS_BES, CUSTOMERBUSINESSHOURS_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, CUSTOMERBUSINESSHOURS_BES, (int)CUSTOMERBUSINESSHOURS_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, CUSTOMERBUSINESSHOURS_BES, (int)CUSTOMERBUSINESSHOURS_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_CUSTOMERBUSINESSHOURS & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CUSTOMERBUSINESSHOURS_BES, (int)CUSTOMERBUSINESSHOURS_ANZ, error_msg);
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
/* CreateSqlStatement of CUSTOMERBUSINESSHOURS ********************************/

 #define CUSTOMERBUSINESSHOURS_CREATE(x) EXEC SQL create table x (\
         WEEKDAY smallint default 0 not null,\
         BRANCHNO smallint default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         BUSINESSHOURSSTART integer default 0 not null,\
         BUSINESSHOURSEND integer default 0 not null) in KscCustomer extent size 2744 next size 276 lock mode row;



/* CreateIndexStatement of CUSTOMERBUSINESSHOURS ******************************/

 #define CUSTOMERBUSINESSHOURS_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
/* DeleteIndexStatement of CUSTOMERBUSINESSHOURS ******************************/

 #define CUSTOMERBUSINESSHOURS_DELETE_INDEX(_X_)\
              _X_ = 0;\


#endif   // GUARD
