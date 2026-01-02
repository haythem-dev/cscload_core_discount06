#ifndef __PP_CSCORDERFLAGS_H_
#define __PP_CSCORDERFLAGS_H_

/******************************************************************************/
/* c:\Source\Repos\pharmos.outbound.csc_load\dev\src\tpldauftr\cscorderflags **/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <pplib/bufkon.h>

/* Length-Define of CSCORDERFLAGS *********************************************/

#define L_CSCORDERFLAGS_CSCORDERNO 11
#define L_CSCORDERFLAGS_NODELAYEDDELIVERY 6
#define L_CSCORDERFLAGS_WAITFORIBTPICKING 6

/* Length/Count-Define of CSCORDERFLAGS ***************************************/

#define LS_CSCORDERFLAGS_CSCORDERNO 10 + 1
#define LS_CSCORDERFLAGS_NODELAYEDDELIVERY 5 + 1
#define LS_CSCORDERFLAGS_WAITFORIBTPICKING 5 + 1

#define CSCORDERFLAGSCSCORDERNO 0
#define CSCORDERFLAGSNODELAYEDDELIVERY 1
#define CSCORDERFLAGSWAITFORIBTPICKING 2

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define CSCORDERFLAGS_H
#define CSCORDERFLAGS_ANZ ( sizeof(CSCORDERFLAGS_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of CSCORDERFLAGS *************************************************/

#define CSCORDERFLAGS_LISTE \
        CSCORDERFLAGS.CSCORDERNO,\
        CSCORDERFLAGS.NODELAYEDDELIVERY,\
        CSCORDERFLAGS.WAITFORIBTPICKING
#define CSCORDERFLAGS_LISTE_390 \
        CSCORDERNO,\
        NODELAYEDDELIVERY,\
        WAITFORIBTPICKING
#define CSCORDERFLAGS_PLISTE \
        "CSCORDERFLAGS.CSCORDERNO,"\
        "CSCORDERFLAGS.NODELAYEDDELIVERY,"\
        "CSCORDERFLAGS.WAITFORIBTPICKING"
#define CSCORDERFLAGS_PELISTE \
        "CSCORDERNO,"\
        "NODELAYEDDELIVERY,"\
        "WAITFORIBTPICKING"
#define CSCORDERFLAGS_UPDLISTE \
        "CSCORDERNO=?,"\
        "NODELAYEDDELIVERY=?,"\
        "WAITFORIBTPICKING=?"
/* SqlMacros-Define of CSCORDERFLAGS ******************************************/

#define CSCORDERFLAGS_ZEIGER(x) \
        :x->CSCORDERNO,\
        :x->NODELAYEDDELIVERY,\
        :x->WAITFORIBTPICKING
#define CSCORDERFLAGS_ZEIGERSEL(x) \
        :x->CSCORDERNO,\
        :x->NODELAYEDDELIVERY,\
        :x->WAITFORIBTPICKING
#define CSCORDERFLAGS_UPDATE(x) \
        CSCORDERFLAGS.CSCORDERNO=:x->CSCORDERNO,\
        CSCORDERFLAGS.NODELAYEDDELIVERY=:x->NODELAYEDDELIVERY,\
        CSCORDERFLAGS.WAITFORIBTPICKING=:x->WAITFORIBTPICKING
/* SqlMacros390-Define of CSCORDERFLAGS ***************************************/

#define CSCORDERFLAGS_ZEIGER_390 \
        :CSCORDERNO,\
        :NODELAYEDDELIVERY,\
        :WAITFORIBTPICKING
#define CSCORDERFLAGS_UPDATE_390 \
        CSCORDERNO=:CSCORDERNO,\
        NODELAYEDDELIVERY=:NODELAYEDDELIVERY,\
        WAITFORIBTPICKING=:WAITFORIBTPICKING
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of CSCORDERFLAGS *******************************************/

#ifndef TRANSCLASS
typedef struct N_CSCORDERFLAGS {
    long CSCORDERNO;
    short NODELAYEDDELIVERY;
    short WAITFORIBTPICKING;
} cscorderflagsS;
#else /* TRANSCLASS */
typedef struct N_CSCORDERFLAGS {
    long CSCORDERNO;
    short NODELAYEDDELIVERY;
    short WAITFORIBTPICKING;

    bool operator == (const N_CSCORDERFLAGS& right) const {
        return (
            CSCORDERNO == right.CSCORDERNO &&
            NODELAYEDDELIVERY == right.NODELAYEDDELIVERY &&
            WAITFORIBTPICKING == right.WAITFORIBTPICKING
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        CSCORDERNO = 0;
        NODELAYEDDELIVERY = 0;
        WAITFORIBTPICKING = 0;
#endif
    }
} cscorderflagsS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of CSCORDERFLAGS *************************************/

struct S_CSCORDERFLAGS {
    char CSCORDERNO[11];
    char NODELAYEDDELIVERY[7];
    char WAITFORIBTPICKING[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of CSCORDERFLAGS ********************/

struct O_CSCORDERFLAGS {
    char CSCORDERNO[11];
    char NODELAYEDDELIVERY[7];
    char WAITFORIBTPICKING[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of CSCORDERFLAGS *******************************/

struct C_CSCORDERFLAGS {
    long CSCORDERNO;
    short NODELAYEDDELIVERY;
    short WAITFORIBTPICKING;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of CSCORDERFLAGS *****************************/

struct I_CSCORDERFLAGS {
    short CSCORDERNO;
    short NODELAYEDDELIVERY;
    short WAITFORIBTPICKING;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CSCORDERFLAGS ***************************************/

#if defined (BUF_DESC)
static struct buf_desc CSCORDERFLAGS_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CSCORDERFLAGS_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* description for datatypes of CSCORDERFLAGS *********************************/

 #define CSCORDERFLAGS_S390 \
         long CSCORDERNO; \
         short NODELAYEDDELIVERY; \
         short WAITFORIBTPICKING; \



/* Copy-Function Struct to single Data CSCORDERFLAGS **************************/

 #define CSCORDERFLAGS_S390_COPY_TO_SINGLE(_x_) \
         CSCORDERNO=_x_->CSCORDERNO;\
         NODELAYEDDELIVERY=_x_->NODELAYEDDELIVERY;\
         WAITFORIBTPICKING=_x_->WAITFORIBTPICKING;\

 #define CSCORDERFLAGS_S390_COPY_TO_STRUCT(_x_) \
          _x_->CSCORDERNO=CSCORDERNO;\
          _x_->NODELAYEDDELIVERY=NODELAYEDDELIVERY;\
          _x_->WAITFORIBTPICKING=WAITFORIBTPICKING;\



/* FunctionNumber-Define of cscorderflags *************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of cscorderflags *********************************/


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

class CCSCORDERFLAGS : public ppDadeVirtual {
public:
    cscorderflagsS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<cscorderflagsS> lst; // class list

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
                     vector< cscorderflagsS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     cscorderflagsS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< cscorderflagsS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<cscorderflagsS>::iterator
                 beginList() { return lst.begin(); }
    vector<cscorderflagsS>::iterator
                 endList  () { return lst.end  (); }

    long         GetCscorderno() const { return s.CSCORDERNO; }
    short        GetNodelayeddelivery() const { return s.NODELAYEDDELIVERY; }
    short        GetWaitforibtpicking() const { return s.WAITFORIBTPICKING; }

    const cscorderflagsS &
                 GetStruct() const { return s; }
    void         SetCscorderno(long t) { s.CSCORDERNO = t; }
    void         SetNodelayeddelivery(short t) { s.NODELAYEDDELIVERY = t; }
    void         SetWaitforibtpicking(short t) { s.WAITFORIBTPICKING = t; }

    void         SetStruct(const cscorderflagsS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCSCORDERFLAGS() {
        ::buf_default((void *)&s, CSCORDERFLAGS_BES, CSCORDERFLAGS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCSCORDERFLAGS() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CSCORDERFLAGS_BES, CSCORDERFLAGS_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, CSCORDERFLAGS_BES, (int)CSCORDERFLAGS_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, CSCORDERFLAGS_BES, (int)CSCORDERFLAGS_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_CSCORDERFLAGS & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CSCORDERFLAGS_BES, (int)CSCORDERFLAGS_ANZ, error_msg);
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
/* CreateSqlStatement of CSCORDERFLAGS ****************************************/

 #define CSCORDERFLAGS_CREATE(x) EXEC SQL create table x (\
         CSCORDERNO integer default 0 not null,\
         NODELAYEDDELIVERY smallint default 0 not null,\
         WAITFORIBTPICKING smallint default 0 not null) in phosix extent size 940 next size 96 lock mode row;



/* CreateIndexStatement of CSCORDERFLAGS **************************************/

 #define CSCORDERFLAGS_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index cscorderflagsx on _X_(\
              cscorderno ) in phosix1;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of CSCORDERFLAGS **************************************/

 #define CSCORDERFLAGS_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index cscorderflagsx;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
