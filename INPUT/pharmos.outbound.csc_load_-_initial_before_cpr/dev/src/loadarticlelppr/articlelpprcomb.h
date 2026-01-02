#ifndef __PP_ARTICLELPPRCOMB_H_
#define __PP_ARTICLELPPRCOMB_H_

/******************************************************************************/
/* c:\Marathon\orderentry\csc_load\trunk\dev\src\loadarticlelppr\articlelpprcomb */
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <pplib/bufkon.h>

/* Length-Define of ARTICLELPPRCOMB *******************************************/

#define L_ARTICLELPPRCOMB_ARTICLENO 11
#define L_ARTICLELPPRCOMB_CODE_LPPR 15
#define L_ARTICLELPPRCOMB_REIMBCALCFLAG 6

/* Length/Count-Define of ARTICLELPPRCOMB *************************************/

#define LS_ARTICLELPPRCOMB_ARTICLENO 10 + 1
#define LS_ARTICLELPPRCOMB_CODE_LPPR 15 + 1
#define LS_ARTICLELPPRCOMB_REIMBCALCFLAG 5 + 1

#define ARTICLELPPRCOMBARTICLENO 0
#define ARTICLELPPRCOMBCODE_LPPR 1
#define ARTICLELPPRCOMBREIMBCALCFLAG 2

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define ARTICLELPPRCOMB_H
#define ARTICLELPPRCOMB_ANZ ( sizeof(ARTICLELPPRCOMB_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ARTICLELPPRCOMB ***********************************************/

#define ARTICLELPPRCOMB_LISTE \
        ARTICLELPPRCOMB.ARTICLENO,\
        ARTICLELPPRCOMB.CODE_LPPR,\
        ARTICLELPPRCOMB.REIMBCALCFLAG
#define ARTICLELPPRCOMB_LISTE_390 \
        ARTICLENO,\
        CODE_LPPR,\
        REIMBCALCFLAG
#define ARTICLELPPRCOMB_PLISTE \
        "ARTICLELPPRCOMB.ARTICLENO,"\
        "ARTICLELPPRCOMB.CODE_LPPR,"\
        "ARTICLELPPRCOMB.REIMBCALCFLAG"
#define ARTICLELPPRCOMB_PELISTE \
        "ARTICLENO,"\
        "CODE_LPPR,"\
        "REIMBCALCFLAG"
#define ARTICLELPPRCOMB_UPDLISTE \
        "ARTICLENO=?,"\
        "CODE_LPPR=?,"\
        "REIMBCALCFLAG=?"
/* SqlMacros-Define of ARTICLELPPRCOMB ****************************************/

#define ARTICLELPPRCOMB_ZEIGER(x) \
        :x->ARTICLENO,\
        :x->CODE_LPPR,\
        :x->REIMBCALCFLAG
#define ARTICLELPPRCOMB_ZEIGERSEL(x) \
        :x->ARTICLENO,\
        :x->CODE_LPPR,\
        :x->REIMBCALCFLAG
#define ARTICLELPPRCOMB_UPDATE(x) \
        ARTICLELPPRCOMB.ARTICLENO=:x->ARTICLENO,\
        ARTICLELPPRCOMB.CODE_LPPR=:x->CODE_LPPR,\
        ARTICLELPPRCOMB.REIMBCALCFLAG=:x->REIMBCALCFLAG
/* SqlMacros390-Define of ARTICLELPPRCOMB *************************************/

#define ARTICLELPPRCOMB_ZEIGER_390 \
        :ARTICLENO,\
        :CODE_LPPR,\
        :REIMBCALCFLAG
#define ARTICLELPPRCOMB_UPDATE_390 \
        ARTICLENO=:ARTICLENO,\
        CODE_LPPR=:CODE_LPPR,\
        REIMBCALCFLAG=:REIMBCALCFLAG
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of ARTICLELPPRCOMB *****************************************/

#ifndef TRANSCLASS
typedef struct N_ARTICLELPPRCOMB {
    long ARTICLENO;
    char CODE_LPPR[16];
    short REIMBCALCFLAG;
} articlelpprcombS;
#else /* TRANSCLASS */
typedef struct N_ARTICLELPPRCOMB {
    long ARTICLENO;
    char CODE_LPPR[16];
    short REIMBCALCFLAG;

    bool operator == (const N_ARTICLELPPRCOMB& right) const {
        return (
            ARTICLENO == right.ARTICLENO &&
            !strcmp(CODE_LPPR, right.CODE_LPPR) &&
            REIMBCALCFLAG == right.REIMBCALCFLAG
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        ARTICLENO = 0;
        strcpy(CODE_LPPR, " " );
        REIMBCALCFLAG = 0;
#endif
    }
} articlelpprcombS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ARTICLELPPRCOMB ***********************************/

struct S_ARTICLELPPRCOMB {
    char ARTICLENO[11];
    char CODE_LPPR[15 + 1];
    char REIMBCALCFLAG[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ARTICLELPPRCOMB ******************/

struct O_ARTICLELPPRCOMB {
    char ARTICLENO[11];
    char CODE_LPPR[15];
    char REIMBCALCFLAG[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ARTICLELPPRCOMB *****************************/

struct C_ARTICLELPPRCOMB {
    long ARTICLENO;
    char CODE_LPPR[16];
    short REIMBCALCFLAG;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ARTICLELPPRCOMB ***************************/

struct I_ARTICLELPPRCOMB {
    short ARTICLENO;
    short CODE_LPPR;
    short REIMBCALCFLAG;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ARTICLELPPRCOMB *************************************/

#if defined (BUF_DESC)
static struct buf_desc ARTICLELPPRCOMB_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 15, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc ARTICLELPPRCOMB_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 15, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* description for datatypes of ARTICLELPPRCOMB *******************************/

 #define ARTICLELPPRCOMB_S390 \
         long ARTICLENO; \
         char CODE_LPPR[16]; \
         short REIMBCALCFLAG; \



/* Copy-Function Struct to single Data ARTICLELPPRCOMB ************************/

 #define ARTICLELPPRCOMB_S390_COPY_TO_SINGLE(_x_) \
         ARTICLENO=_x_->ARTICLENO;\
          strcpy(CODE_LPPR,_x_->CODE_LPPR);\
         REIMBCALCFLAG=_x_->REIMBCALCFLAG;\

 #define ARTICLELPPRCOMB_S390_COPY_TO_STRUCT(_x_) \
          _x_->ARTICLENO=ARTICLENO;\
          strcpy(_x_->CODE_LPPR,CODE_LPPR);\
          _x_->REIMBCALCFLAG=REIMBCALCFLAG;\



/* FunctionNumber-Define of articlelpprcomb ***********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of articlelpprcomb *******************************/


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

class CARTICLELPPRCOMB : public ppDadeVirtual {
public:
    articlelpprcombS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<articlelpprcombS> lst; // class list

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
                     vector< articlelpprcombS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     articlelpprcombS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< articlelpprcombS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<articlelpprcombS>::iterator
                 beginList() { return lst.begin(); }
    vector<articlelpprcombS>::iterator
                 endList  () { return lst.end  (); }

    long         GetArticleno() const { return s.ARTICLENO; }
    const char*  GetCode_lppr(ppString & t) const { t = s.CODE_LPPR; t.erasespace(ppString::END); return t.c_str(); }
    short        GetReimbcalcflag() const { return s.REIMBCALCFLAG; }

    const articlelpprcombS &
                 GetStruct() const { return s; }
    void         SetArticleno(long t) { s.ARTICLENO = t; }
    void         SetCode_lppr(const ppString & t) { ppGStrCopy(s.CODE_LPPR, t.c_str(), L_ARTICLELPPRCOMB_CODE_LPPR); }
    void         SetReimbcalcflag(short t) { s.REIMBCALCFLAG = t; }

    void         SetStruct(const articlelpprcombS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CARTICLELPPRCOMB() {
        ::buf_default((void *)&s, ARTICLELPPRCOMB_BES, ARTICLELPPRCOMB_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CARTICLELPPRCOMB() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, ARTICLELPPRCOMB_BES, ARTICLELPPRCOMB_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, ARTICLELPPRCOMB_BES, (int)ARTICLELPPRCOMB_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, ARTICLELPPRCOMB_BES, (int)ARTICLELPPRCOMB_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_ARTICLELPPRCOMB & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.CODE_LPPR);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, ARTICLELPPRCOMB_BES, (int)ARTICLELPPRCOMB_ANZ, error_msg);
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
/* CreateSqlStatement of ARTICLELPPRCOMB **************************************/

 #define ARTICLELPPRCOMB_CREATE(x) EXEC SQL create table x (\
         ARTICLENO integer default 0 not null,\
         CODE_LPPR char(15) default " " not null,\
         REIMBCALCFLAG smallint default 0 not null) in ksc extent size 2352 next size 236 lock mode row;



/* CreateIndexStatement of ARTICLELPPRCOMB ************************************/

 #define ARTICLELPPRCOMB_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_articlelpprcomb_1 on _X_(\
              ArticleNo,\
              code_lppr ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ARTICLELPPRCOMB ************************************/

 #define ARTICLELPPRCOMB_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_articlelpprcomb_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
