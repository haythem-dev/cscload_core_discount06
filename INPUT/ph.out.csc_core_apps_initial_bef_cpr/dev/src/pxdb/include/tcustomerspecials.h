#ifndef __PP_CUSTOMERSPECIALS_H_
#define __PP_CUSTOMERSPECIALS_H_

/******************************************************************************/
/* c:\prri\Headerfiles\customerspecials ***************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of CUSTOMERSPECIALS ******************************************/

#define L_CUSTOMERSPECIALS_BRANCHNO 6
#define L_CUSTOMERSPECIALS_CUSTOMERNO 11
#define L_CUSTOMERSPECIALS_UW_IDF 11
#define L_CUSTOMERSPECIALS_UW_TOUR 6
#define L_CUSTOMERSPECIALS_WEEKDAY 6
#define L_CUSTOMERSPECIALS_ACTIV 1

/* Length/Count-Define of CUSTOMERSPECIALS ************************************/

#define LS_CUSTOMERSPECIALS_BRANCHNO 5 + 1
#define LS_CUSTOMERSPECIALS_CUSTOMERNO 10 + 1
#define LS_CUSTOMERSPECIALS_UW_IDF 10 + 1
#define LS_CUSTOMERSPECIALS_UW_TOUR 6 + 1
#define LS_CUSTOMERSPECIALS_WEEKDAY 5 + 1
#define LS_CUSTOMERSPECIALS_ACTIV 1 + 1

#define CUSTOMERSPECIALSBRANCHNO 0
#define CUSTOMERSPECIALSCUSTOMERNO 1
#define CUSTOMERSPECIALSUW_IDF 2
#define CUSTOMERSPECIALSUW_TOUR 3
#define CUSTOMERSPECIALSWEEKDAY 4
#define CUSTOMERSPECIALSACTIV 5

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define CUSTOMERSPECIALS_H
#define CUSTOMERSPECIALS_ANZ ( sizeof(CUSTOMERSPECIALS_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of CUSTOMERSPECIALS **********************************************/

#define CUSTOMERSPECIALS_LISTE \
        CUSTOMERSPECIALS.BRANCHNO,\
        CUSTOMERSPECIALS.CUSTOMERNO,\
        CUSTOMERSPECIALS.UW_IDF,\
        CUSTOMERSPECIALS.UW_TOUR,\
        CUSTOMERSPECIALS.WEEKDAY,\
        CUSTOMERSPECIALS.ACTIV
#define CUSTOMERSPECIALS_LISTE_390 \
        BRANCHNO,\
        CUSTOMERNO,\
        UW_IDF,\
        UW_TOUR,\
        WEEKDAY,\
        ACTIV
#define CUSTOMERSPECIALS_PLISTE \
        "CUSTOMERSPECIALS.BRANCHNO,"\
        "CUSTOMERSPECIALS.CUSTOMERNO,"\
        "CUSTOMERSPECIALS.UW_IDF,"\
        "CUSTOMERSPECIALS.UW_TOUR,"\
        "CUSTOMERSPECIALS.WEEKDAY,"\
        "CUSTOMERSPECIALS.ACTIV"
#define CUSTOMERSPECIALS_PELISTE \
        "BRANCHNO,"\
        "CUSTOMERNO,"\
        "UW_IDF,"\
        "UW_TOUR,"\
        "WEEKDAY,"\
        "ACTIV"
#define CUSTOMERSPECIALS_UPDLISTE \
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "UW_IDF=?,"\
        "UW_TOUR=?,"\
        "WEEKDAY=?,"\
        "ACTIV=?"
/* SqlMacros-Define of CUSTOMERSPECIALS ***************************************/

#define CUSTOMERSPECIALS_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->UW_IDF,\
        :x->UW_TOUR,\
        :x->WEEKDAY,\
        :x->ACTIV
#define CUSTOMERSPECIALS_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->UW_IDF,\
        :x->UW_TOUR,\
        :x->WEEKDAY,\
        :x->ACTIV
#define CUSTOMERSPECIALS_UPDATE(x) \
        CUSTOMERSPECIALS.BRANCHNO=:x->BRANCHNO,\
        CUSTOMERSPECIALS.CUSTOMERNO=:x->CUSTOMERNO,\
        CUSTOMERSPECIALS.UW_IDF=:x->UW_IDF,\
        CUSTOMERSPECIALS.UW_TOUR=:x->UW_TOUR,\
        CUSTOMERSPECIALS.WEEKDAY=:x->WEEKDAY,\
        CUSTOMERSPECIALS.ACTIV=:x->ACTIV
/* SqlMacros390-Define of CUSTOMERSPECIALS ************************************/

#define CUSTOMERSPECIALS_ZEIGER_390 \
        :BRANCHNO,\
        :CUSTOMERNO,\
        :UW_IDF,\
        :UW_TOUR,\
        :WEEKDAY,\
        :ACTIV
#define CUSTOMERSPECIALS_UPDATE_390 \
        BRANCHNO=:BRANCHNO,\
        CUSTOMERNO=:CUSTOMERNO,\
        UW_IDF=:UW_IDF,\
        UW_TOUR=:UW_TOUR,\
        WEEKDAY=:WEEKDAY,\
        ACTIV=:ACTIV
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of CUSTOMERSPECIALS ****************************************/

#ifndef TRANSCLASS
typedef struct N_CUSTOMERSPECIALS {
    short BRANCHNO;
    long CUSTOMERNO;
    long UW_IDF;
    char UW_TOUR[7];
    short WEEKDAY;
    char ACTIV[2];
} customerspecialsS;
#else /* TRANSCLASS */
typedef struct N_CUSTOMERSPECIALS {
    short BRANCHNO;
    long CUSTOMERNO;
    long UW_IDF;
    char UW_TOUR[7];
    short WEEKDAY;
    char ACTIV[2];

    bool operator == (const N_CUSTOMERSPECIALS& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            CUSTOMERNO == right.CUSTOMERNO &&
            UW_IDF == right.UW_IDF &&
            !strcmp(UW_TOUR, right.UW_TOUR) &&
            WEEKDAY == right.WEEKDAY &&
            !strcmp(ACTIV, right.ACTIV)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        CUSTOMERNO = 0;
        UW_IDF = 0;
        strcpy(UW_TOUR, " " );
        WEEKDAY = 0;
        strcpy(ACTIV, " " );
#endif
    }
} customerspecialsS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of CUSTOMERSPECIALS **********************************/

struct S_CUSTOMERSPECIALS {
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char UW_IDF[11];
    char UW_TOUR[6 + 1];
    char WEEKDAY[7];
    char ACTIV[1 + 1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of CUSTOMERSPECIALS *****************/

struct O_CUSTOMERSPECIALS {
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char UW_IDF[11];
    char UW_TOUR[6];
    char WEEKDAY[7];
    char ACTIV[1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of CUSTOMERSPECIALS ****************************/

struct C_CUSTOMERSPECIALS {
    short BRANCHNO;
    long CUSTOMERNO;
    long UW_IDF;
    char UW_TOUR[7];
    short WEEKDAY;
    char ACTIV;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of CUSTOMERSPECIALS **************************/

struct I_CUSTOMERSPECIALS {
    short BRANCHNO;
    short CUSTOMERNO;
    short UW_IDF;
    short UW_TOUR;
    short WEEKDAY;
    short ACTIV;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CUSTOMERSPECIALS ************************************/

#if defined (BUF_DESC)
static struct buf_desc CUSTOMERSPECIALS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CUSTOMERSPECIALS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
};
#endif

/* description for datatypes of CUSTOMERSPECIALS ******************************/

 #define CUSTOMERSPECIALS_S390 \
         short BRANCHNO; \
         long CUSTOMERNO; \
         long UW_IDF; \
         char UW_TOUR[7]; \
         short WEEKDAY; \
         char ACTIV; \



/* Copy-Function Struct to single Data CUSTOMERSPECIALS ***********************/

 #define CUSTOMERSPECIALS_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
         UW_IDF=_x_->UW_IDF;\
          strcpy(UW_TOUR,_x_->UW_TOUR);\
         WEEKDAY=_x_->WEEKDAY;\
         ACTIV=_x_->ACTIV;\

 #define CUSTOMERSPECIALS_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->UW_IDF=UW_IDF;\
          strcpy(_x_->UW_TOUR,UW_TOUR);\
          _x_->WEEKDAY=WEEKDAY;\
          _x_->ACTIV=ACTIV;\



/* FunctionNumber-Define of customerspecials **********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of customerspecials ******************************/


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

class CCUSTOMERSPECIALS : public ppDadeVirtual {
public:
    customerspecialsS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<customerspecialsS> lst; // class list

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
                     vector< customerspecialsS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     customerspecialsS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< customerspecialsS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<customerspecialsS>::iterator
                 beginList() { return lst.begin(); }
    vector<customerspecialsS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    long         GetUw_idf() const { return s.UW_IDF; }
    const char*  GetUw_tour(ppString & t) const { t = s.UW_TOUR; t.erasespace(ppString::END); return t.c_str(); }
    short        GetWeekday() const { return s.WEEKDAY; }
    char         GetActiv() const { return s.ACTIV[0]; }

    const customerspecialsS &
                 GetStruct() const { return s; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetUw_idf(long t) { s.UW_IDF = t; }
    void         SetUw_tour(const ppString & t) { ppGStrCopy(s.UW_TOUR, t.c_str(), L_CUSTOMERSPECIALS_UW_TOUR); }
    void         SetWeekday(short t) { s.WEEKDAY = t; }
    void         SetActiv(char t) { s.ACTIV[0] = t; s.ACTIV[1] = '\0';}

    void         SetStruct(const customerspecialsS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCUSTOMERSPECIALS() {
        ::buf_default((void *)&s, CUSTOMERSPECIALS_BES, CUSTOMERSPECIALS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCUSTOMERSPECIALS() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CUSTOMERSPECIALS_BES, CUSTOMERSPECIALS_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, CUSTOMERSPECIALS_BES, (int)CUSTOMERSPECIALS_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, CUSTOMERSPECIALS_BES, (int)CUSTOMERSPECIALS_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_CUSTOMERSPECIALS & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.UW_TOUR);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CUSTOMERSPECIALS_BES, (int)CUSTOMERSPECIALS_ANZ, error_msg);
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
/* CreateSqlStatement of CUSTOMERSPECIALS *************************************/

 #define CUSTOMERSPECIALS_CREATE(x) EXEC SQL create table x (\
         BRANCHNO smallint default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         UW_IDF integer default 0 not null,\
         UW_TOUR char(6) default " " not null,\
         WEEKDAY smallint default 0 not null,\
         ACTIV char(1) default " " not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of CUSTOMERSPECIALS ***********************************/

 #define CUSTOMERSPECIALS_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_customerspez_1 on _X_(\
              BranchNo,\
              CustomerNo,\
              weekday ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of CUSTOMERSPECIALS ***********************************/

 #define CUSTOMERSPECIALS_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_customerspez_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
