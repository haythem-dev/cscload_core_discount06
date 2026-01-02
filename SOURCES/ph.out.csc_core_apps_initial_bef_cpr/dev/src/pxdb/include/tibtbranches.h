#ifndef __PP_IBTBRANCHES_H_
#define __PP_IBTBRANCHES_H_

/******************************************************************************/
/* c:\temp\ibtbranches ********************************************************/
/* produced by DADE 6.22.0 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of IBTBRANCHES ***********************************************/

#define L_IBTBRANCHES_ARTICLENO 11
#define L_IBTBRANCHES_BRANCHNO 6
#define L_IBTBRANCHES_PRIORITY 6
#define L_IBTBRANCHES_IBTBRANCHNO 6
#define L_IBTBRANCHES_IBTTYPE 6
#define L_IBTBRANCHES_DAYIBT 6
#define L_IBTBRANCHES_IBTCUSTOMERNO 11
#define L_IBTBRANCHES_ACTIVE_FLAG 6
#define L_IBTBRANCHES_NLEVELIBTTYPEID 6
#define L_IBTBRANCHES_NLEVELIBTASSORTMENTTYPEID 6

/* Length/Count-Define of IBTBRANCHES *****************************************/

#define LS_IBTBRANCHES_ARTICLENO 10 + 1
#define LS_IBTBRANCHES_BRANCHNO 5 + 1
#define LS_IBTBRANCHES_PRIORITY 5 + 1
#define LS_IBTBRANCHES_IBTBRANCHNO 5 + 1
#define LS_IBTBRANCHES_IBTTYPE 5 + 1
#define LS_IBTBRANCHES_DAYIBT 5 + 1
#define LS_IBTBRANCHES_IBTCUSTOMERNO 10 + 1
#define LS_IBTBRANCHES_ACTIVE_FLAG 5 + 1
#define LS_IBTBRANCHES_NLEVELIBTTYPEID 5 + 1
#define LS_IBTBRANCHES_NLEVELIBTASSORTMENTTYPEID 5 + 1

#define IBTBRANCHESARTICLENO 0
#define IBTBRANCHESBRANCHNO 1
#define IBTBRANCHESPRIORITY 2
#define IBTBRANCHESIBTBRANCHNO 3
#define IBTBRANCHESIBTTYPE 4
#define IBTBRANCHESDAYIBT 5
#define IBTBRANCHESIBTCUSTOMERNO 6
#define IBTBRANCHESACTIVE_FLAG 7
#define IBTBRANCHESNLEVELIBTTYPEID 8
#define IBTBRANCHESNLEVELIBTASSORTMENTTYPEID 9

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define IBTBRANCHES_H
#define IBTBRANCHES_ANZ ( sizeof(IBTBRANCHES_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of IBTBRANCHES ***************************************************/

#define IBTBRANCHES_LISTE \
        ARTICLECODES.ARTICLENO,\
        IBTBRANCHES.BRANCHNO,\
        IBTBRANCHES.PRIORITY,\
        IBTBRANCHES.IBTBRANCHNO,\
        IBTBRANCHES.IBTTYPE,\
        IBTBRANCHES.DAYIBT,\
        IBTBRANCHES.IBTCUSTOMERNO,\
        IBTBRANCHES.ACTIVE_FLAG,\
        IBTBRANCHES.NLEVELIBTTYPEID,\
        IBTBRANCHES.NLEVELIBTASSORTMENTTYPEID
#define IBTBRANCHES_LISTE_390 \
        ARTICLENO,\
        BRANCHNO,\
        PRIORITY,\
        IBTBRANCHNO,\
        IBTTYPE,\
        DAYIBT,\
        IBTCUSTOMERNO,\
        ACTIVE_FLAG,\
        NLEVELIBTTYPEID,\
        NLEVELIBTASSORTMENTTYPEID
#define IBTBRANCHES_PLISTE \
        "ARTICLECODES.ARTICLENO,"\
        "IBTBRANCHES.BRANCHNO,"\
        "IBTBRANCHES.PRIORITY,"\
        "IBTBRANCHES.IBTBRANCHNO,"\
        "IBTBRANCHES.IBTTYPE,"\
        "IBTBRANCHES.DAYIBT,"\
        "IBTBRANCHES.IBTCUSTOMERNO,"\
        "IBTBRANCHES.ACTIVE_FLAG,"\
        "IBTBRANCHES.NLEVELIBTTYPEID,"\
        "IBTBRANCHES.NLEVELIBTASSORTMENTTYPEID"
#define IBTBRANCHES_PELISTE \
        "ARTICLENO,"\
        "BRANCHNO,"\
        "PRIORITY,"\
        "IBTBRANCHNO,"\
        "IBTTYPE,"\
        "DAYIBT,"\
        "IBTCUSTOMERNO,"\
        "ACTIVE_FLAG,"\
        "NLEVELIBTTYPEID,"\
        "NLEVELIBTASSORTMENTTYPEID"
#define IBTBRANCHES_UPDLISTE \
        "ARTICLENO=?,"\
        "BRANCHNO=?,"\
        "PRIORITY=?,"\
        "IBTBRANCHNO=?,"\
        "IBTTYPE=?,"\
        "DAYIBT=?,"\
        "IBTCUSTOMERNO=?,"\
        "ACTIVE_FLAG=?,"\
        "NLEVELIBTTYPEID=?,"\
        "NLEVELIBTASSORTMENTTYPEID=?"
/* SqlMacros-Define of IBTBRANCHES ********************************************/

#define IBTBRANCHES_ZEIGER(x) \
        :x->ARTICLENO,\
        :x->BRANCHNO,\
        :x->PRIORITY,\
        :x->IBTBRANCHNO,\
        :x->IBTTYPE,\
        :x->DAYIBT,\
        :x->IBTCUSTOMERNO,\
        :x->ACTIVE_FLAG,\
        :x->NLEVELIBTTYPEID,\
        :x->NLEVELIBTASSORTMENTTYPEID
#define IBTBRANCHES_ZEIGERSEL(x) \
        :x->ARTICLENO,\
        :x->BRANCHNO,\
        :x->PRIORITY,\
        :x->IBTBRANCHNO,\
        :x->IBTTYPE,\
        :x->DAYIBT,\
        :x->IBTCUSTOMERNO,\
        :x->ACTIVE_FLAG,\
        :x->NLEVELIBTTYPEID,\
        :x->NLEVELIBTASSORTMENTTYPEID
#define IBTBRANCHES_UPDATE(x) \
        ARTICLECODES.ARTICLENO=:x->ARTICLENO,\
        IBTBRANCHES.BRANCHNO=:x->BRANCHNO,\
        IBTBRANCHES.PRIORITY=:x->PRIORITY,\
        IBTBRANCHES.IBTBRANCHNO=:x->IBTBRANCHNO,\
        IBTBRANCHES.IBTTYPE=:x->IBTTYPE,\
        IBTBRANCHES.DAYIBT=:x->DAYIBT,\
        IBTBRANCHES.IBTCUSTOMERNO=:x->IBTCUSTOMERNO,\
        IBTBRANCHES.ACTIVE_FLAG=:x->ACTIVE_FLAG,\
        IBTBRANCHES.NLEVELIBTTYPEID=:x->NLEVELIBTTYPEID,\
        IBTBRANCHES.NLEVELIBTASSORTMENTTYPEID=:x->NLEVELIBTASSORTMENTTYPEID
/* SqlMacros390-Define of IBTBRANCHES *****************************************/

#define IBTBRANCHES_ZEIGER_390 \
        :ARTICLENO,\
        :BRANCHNO,\
        :PRIORITY,\
        :IBTBRANCHNO,\
        :IBTTYPE,\
        :DAYIBT,\
        :IBTCUSTOMERNO,\
        :ACTIVE_FLAG,\
        :NLEVELIBTTYPEID,\
        :NLEVELIBTASSORTMENTTYPEID
#define IBTBRANCHES_UPDATE_390 \
        ARTICLENO=:ARTICLENO,\
        BRANCHNO=:BRANCHNO,\
        PRIORITY=:PRIORITY,\
        IBTBRANCHNO=:IBTBRANCHNO,\
        IBTTYPE=:IBTTYPE,\
        DAYIBT=:DAYIBT,\
        IBTCUSTOMERNO=:IBTCUSTOMERNO,\
        ACTIVE_FLAG=:ACTIVE_FLAG,\
        NLEVELIBTTYPEID=:NLEVELIBTTYPEID,\
        NLEVELIBTASSORTMENTTYPEID=:NLEVELIBTASSORTMENTTYPEID
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of IBTBRANCHES *********************************************/

#ifndef TRANSCLASS
typedef struct N_IBTBRANCHES {
    long ARTICLENO;
    short BRANCHNO;
    short PRIORITY;
    short IBTBRANCHNO;
    short IBTTYPE;
    short DAYIBT;
    long IBTCUSTOMERNO;
    short ACTIVE_FLAG;
    short NLEVELIBTTYPEID;
    short NLEVELIBTASSORTMENTTYPEID;
} ibtbranchesS;
#else /* TRANSCLASS */
typedef struct N_IBTBRANCHES {
    long ARTICLENO;
    short BRANCHNO;
    short PRIORITY;
    short IBTBRANCHNO;
    short IBTTYPE;
    short DAYIBT;
    long IBTCUSTOMERNO;
    short ACTIVE_FLAG;
    short NLEVELIBTTYPEID;
    short NLEVELIBTASSORTMENTTYPEID;

    bool operator == (const N_IBTBRANCHES& right) const {
        return (
            ARTICLENO == right.ARTICLENO &&
            BRANCHNO == right.BRANCHNO &&
            PRIORITY == right.PRIORITY &&
            IBTBRANCHNO == right.IBTBRANCHNO &&
            IBTTYPE == right.IBTTYPE &&
            DAYIBT == right.DAYIBT &&
            IBTCUSTOMERNO == right.IBTCUSTOMERNO &&
            ACTIVE_FLAG == right.ACTIVE_FLAG &&
            NLEVELIBTTYPEID == right.NLEVELIBTTYPEID &&
            NLEVELIBTASSORTMENTTYPEID == right.NLEVELIBTASSORTMENTTYPEID
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        ARTICLENO = 0;
        BRANCHNO = 0;
        PRIORITY = 0;
        IBTBRANCHNO = 0;
        IBTTYPE = 0;
        DAYIBT = 0;
        IBTCUSTOMERNO = 0;
        ACTIVE_FLAG = 0;
        NLEVELIBTTYPEID = 0;
        NLEVELIBTASSORTMENTTYPEID = 0;
#endif
    }
} ibtbranchesS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of IBTBRANCHES ***************************************/

struct S_IBTBRANCHES {
    char ARTICLENO[11];
    char BRANCHNO[7];
    char PRIORITY[7];
    char IBTBRANCHNO[7];
    char IBTTYPE[7];
    char DAYIBT[7];
    char IBTCUSTOMERNO[11];
    char ACTIVE_FLAG[7];
    char NLEVELIBTTYPEID[7];
    char NLEVELIBTASSORTMENTTYPEID[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of IBTBRANCHES **********************/

struct O_IBTBRANCHES {
    char ARTICLENO[11];
    char BRANCHNO[7];
    char PRIORITY[7];
    char IBTBRANCHNO[7];
    char IBTTYPE[7];
    char DAYIBT[7];
    char IBTCUSTOMERNO[11];
    char ACTIVE_FLAG[7];
    char NLEVELIBTTYPEID[7];
    char NLEVELIBTASSORTMENTTYPEID[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of IBTBRANCHES *********************************/

struct C_IBTBRANCHES {
    long ARTICLENO;
    short BRANCHNO;
    short PRIORITY;
    short IBTBRANCHNO;
    short IBTTYPE;
    short DAYIBT;
    long IBTCUSTOMERNO;
    short ACTIVE_FLAG;
    short NLEVELIBTTYPEID;
    short NLEVELIBTASSORTMENTTYPEID;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of IBTBRANCHES *******************************/

struct I_IBTBRANCHES {
    short ARTICLENO;
    short BRANCHNO;
    short PRIORITY;
    short IBTBRANCHNO;
    short IBTTYPE;
    short DAYIBT;
    short IBTCUSTOMERNO;
    short ACTIVE_FLAG;
    short NLEVELIBTTYPEID;
    short NLEVELIBTASSORTMENTTYPEID;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of IBTBRANCHES *****************************************/

#if defined (BUF_DESC)
static struct buf_desc IBTBRANCHES_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc IBTBRANCHES_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* description for datatypes of IBTBRANCHES ***********************************/

 #define IBTBRANCHES_S390 \
         long ARTICLENO; \
         short BRANCHNO; \
         short PRIORITY; \
         short IBTBRANCHNO; \
         short IBTTYPE; \
         short DAYIBT; \
         long IBTCUSTOMERNO; \
         short ACTIVE_FLAG; \
         short NLEVELIBTTYPEID; \
         short NLEVELIBTASSORTMENTTYPEID; \



/* Copy-Function Struct to single Data IBTBRANCHES ****************************/

 #define IBTBRANCHES_S390_COPY_TO_SINGLE(_x_) \
         ARTICLENO=_x_->ARTICLENO;\
         BRANCHNO=_x_->BRANCHNO;\
         PRIORITY=_x_->PRIORITY;\
         IBTBRANCHNO=_x_->IBTBRANCHNO;\
         IBTTYPE=_x_->IBTTYPE;\
         DAYIBT=_x_->DAYIBT;\
         IBTCUSTOMERNO=_x_->IBTCUSTOMERNO;\
         ACTIVE_FLAG=_x_->ACTIVE_FLAG;\
         NLEVELIBTTYPEID=_x_->NLEVELIBTTYPEID;\
         NLEVELIBTASSORTMENTTYPEID=_x_->NLEVELIBTASSORTMENTTYPEID;\

 #define IBTBRANCHES_S390_COPY_TO_STRUCT(_x_) \
          _x_->ARTICLENO=ARTICLENO;\
          _x_->BRANCHNO=BRANCHNO;\
          _x_->PRIORITY=PRIORITY;\
          _x_->IBTBRANCHNO=IBTBRANCHNO;\
          _x_->IBTTYPE=IBTTYPE;\
          _x_->DAYIBT=DAYIBT;\
          _x_->IBTCUSTOMERNO=IBTCUSTOMERNO;\
          _x_->ACTIVE_FLAG=ACTIVE_FLAG;\
          _x_->NLEVELIBTTYPEID=NLEVELIBTTYPEID;\
          _x_->NLEVELIBTASSORTMENTTYPEID=NLEVELIBTASSORTMENTTYPEID;\



/* FunctionNumber-Define of ibtbranches ***************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of ibtbranches ***********************************/


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

class CIBTBRANCHES : public ppDadeVirtual {
public:
    ibtbranchesS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<ibtbranchesS> lst; // class list

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
                     vector< ibtbranchesS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     ibtbranchesS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< ibtbranchesS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<ibtbranchesS>::iterator
                 beginList() { return lst.begin(); }
    vector<ibtbranchesS>::iterator
                 endList  () { return lst.end  (); }

    long         GetArticleno() const { return s.ARTICLENO; }
    short        GetBranchno() const { return s.BRANCHNO; }
    short        GetPriority() const { return s.PRIORITY; }
    short        GetIbtbranchno() const { return s.IBTBRANCHNO; }
    short        GetIbttype() const { return s.IBTTYPE; }
    short        GetDayibt() const { return s.DAYIBT; }
    long         GetIbtcustomerno() const { return s.IBTCUSTOMERNO; }
    short        GetActive_flag() const { return s.ACTIVE_FLAG; }
    short        GetNlevelibttypeid() const { return s.NLEVELIBTTYPEID; }
    short        GetNlevelibtassortmenttypeid() const { return s.NLEVELIBTASSORTMENTTYPEID; }

    const ibtbranchesS &
                 GetStruct() const { return s; }
    void         SetArticleno(long t) { s.ARTICLENO = t; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetPriority(short t) { s.PRIORITY = t; }
    void         SetIbtbranchno(short t) { s.IBTBRANCHNO = t; }
    void         SetIbttype(short t) { s.IBTTYPE = t; }
    void         SetDayibt(short t) { s.DAYIBT = t; }
    void         SetIbtcustomerno(long t) { s.IBTCUSTOMERNO = t; }
    void         SetActive_flag(short t) { s.ACTIVE_FLAG = t; }
    void         SetNlevelibttypeid(short t) { s.NLEVELIBTTYPEID = t; }
    void         SetNlevelibtassortmenttypeid(short t) { s.NLEVELIBTASSORTMENTTYPEID = t; }

    void         SetStruct(const ibtbranchesS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CIBTBRANCHES() {
        ::buf_default((void *)&s, IBTBRANCHES_BES, IBTBRANCHES_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CIBTBRANCHES() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, IBTBRANCHES_BES, IBTBRANCHES_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, IBTBRANCHES_BES, (int)IBTBRANCHES_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, IBTBRANCHES_BES, (int)IBTBRANCHES_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_IBTBRANCHES & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, IBTBRANCHES_BES, (int)IBTBRANCHES_ANZ, error_msg);
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
/* CreateSqlStatement of IBTBRANCHES ******************************************/

 #define IBTBRANCHES_CREATE(x) EXEC SQL create table x (\
         ARTICLENO integer default 0 not null,\
         BRANCHNO smallint default 0 not null,\
         PRIORITY smallint default 0 not null,\
         IBTBRANCHNO smallint default 0 not null,\
         IBTTYPE smallint default 0 not null,\
         DAYIBT smallint default 0 not null,\
         IBTCUSTOMERNO integer default 0 not null,\
         ACTIVE_FLAG smallint default 0 not null,\
         NLEVELIBTTYPEID smallint default 0 not null,\
         NLEVELIBTASSORTMENTTYPEID smallint default 0 not null) in ksc extent size 7844 next size 788 lock mode row;



/* CreateIndexStatement of IBTBRANCHES ****************************************/

 #define IBTBRANCHES_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_artcodes_1 on _X_(\
              article_code ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index i_artcodes_2 on _X_(\
              ArticleNo,\
              preferred_flag ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of IBTBRANCHES ****************************************/

 #define IBTBRANCHES_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_artcodes_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_artcodes_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
