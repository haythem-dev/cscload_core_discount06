#ifndef __PP_CSCORDERIMPORTCSVCOLUMNS_H_
#define __PP_CSCORDERIMPORTCSVCOLUMNS_H_

/******************************************************************************/
/**/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of CSCORDERIMPORTCSVCOLUMNS **********************************/

#define L_CSCORDERIMPORTCSVCOLUMNS_COLUMNNO 6
#define L_CSCORDERIMPORTCSVCOLUMNS_FIELDNAMEID 11
#define L_CSCORDERIMPORTCSVCOLUMNS_CSCORDERIMPORTFORMATID 11
#define L_CSCORDERIMPORTCSVCOLUMNS_GROUPING 6

/* Length/Count-Define of CSCORDERIMPORTCSVCOLUMNS ****************************/

#define LS_CSCORDERIMPORTCSVCOLUMNS_COLUMNNO 5 + 1
#define LS_CSCORDERIMPORTCSVCOLUMNS_FIELDNAMEID 10 + 1
#define LS_CSCORDERIMPORTCSVCOLUMNS_CSCORDERIMPORTFORMATID 10 + 1
#define LS_CSCORDERIMPORTCSVCOLUMNS_GROUPING 5 + 1

#define CSCORDERIMPORTCSVCOLUMNSCOLUMNNO 0
#define CSCORDERIMPORTCSVCOLUMNSFIELDNAMEID 1
#define CSCORDERIMPORTCSVCOLUMNSCSCORDERIMPORTFORMATID 2
#define CSCORDERIMPORTCSVCOLUMNSGROUPING 3

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define CSCORDERIMPORTCSVCOLUMNS_H
#define CSCORDERIMPORTCSVCOLUMNS_ANZ ( sizeof(CSCORDERIMPORTCSVCOLUMNS_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of CSCORDERIMPORTCSVCOLUMNS **************************************/

#define CSCORDERIMPORTCSVCOLUMNS_LISTE \
        CSCORDERIMPORTCSVCOLUMNS.COLUMNNO,\
        CSCORDERIMPORTCSVCOLUMNS.FIELDNAMEID,\
        CSCORDERIMPORTCSVCOLUMNS.CSCORDERIMPORTFORMATID,\
        CSCORDERIMPORTCSVCOLUMNS.GROUPING
#define CSCORDERIMPORTCSVCOLUMNS_LISTE_390 \
        COLUMNNO,\
        FIELDNAMEID,\
        CSCORDERIMPORTFORMATID,\
        GROUPING
#define CSCORDERIMPORTCSVCOLUMNS_PLISTE \
        "CSCORDERIMPORTCSVCOLUMNS.COLUMNNO,"\
        "CSCORDERIMPORTCSVCOLUMNS.FIELDNAMEID,"\
        "CSCORDERIMPORTCSVCOLUMNS.CSCORDERIMPORTFORMATID,"\
        "CSCORDERIMPORTCSVCOLUMNS.GROUPING"
#define CSCORDERIMPORTCSVCOLUMNS_PELISTE \
        "COLUMNNO,"\
        "FIELDNAMEID,"\
        "CSCORDERIMPORTFORMATID,"\
        "GROUPING"
#define CSCORDERIMPORTCSVCOLUMNS_UPDLISTE \
        "COLUMNNO=?,"\
        "FIELDNAMEID=?,"\
        "CSCORDERIMPORTFORMATID=?,"\
        "GROUPING=?"
/* SqlMacros-Define of CSCORDERIMPORTCSVCOLUMNS *******************************/

#define CSCORDERIMPORTCSVCOLUMNS_ZEIGER(x) \
        :x->COLUMNNO,\
        :x->FIELDNAMEID,\
        :x->CSCORDERIMPORTFORMATID,\
        :x->GROUPING
#define CSCORDERIMPORTCSVCOLUMNS_ZEIGERSEL(x) \
        :x->COLUMNNO,\
        :x->FIELDNAMEID,\
        :x->CSCORDERIMPORTFORMATID,\
        :x->GROUPING
#define CSCORDERIMPORTCSVCOLUMNS_UPDATE(x) \
        CSCORDERIMPORTCSVCOLUMNS.COLUMNNO=:x->COLUMNNO,\
        CSCORDERIMPORTCSVCOLUMNS.FIELDNAMEID=:x->FIELDNAMEID,\
        CSCORDERIMPORTCSVCOLUMNS.CSCORDERIMPORTFORMATID=:x->CSCORDERIMPORTFORMATID,\
        CSCORDERIMPORTCSVCOLUMNS.GROUPING=:x->GROUPING
/* SqlMacros390-Define of CSCORDERIMPORTCSVCOLUMNS ****************************/

#define CSCORDERIMPORTCSVCOLUMNS_ZEIGER_390 \
        :COLUMNNO,\
        :FIELDNAMEID,\
        :CSCORDERIMPORTFORMATID,\
        :GROUPING
#define CSCORDERIMPORTCSVCOLUMNS_UPDATE_390 \
        COLUMNNO=:COLUMNNO,\
        FIELDNAMEID=:FIELDNAMEID,\
        CSCORDERIMPORTFORMATID=:CSCORDERIMPORTFORMATID,\
        GROUPING=:GROUPING
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of CSCORDERIMPORTCSVCOLUMNS ********************************/

#ifndef TRANSCLASS
typedef struct N_CSCORDERIMPORTCSVCOLUMNS {
    short COLUMNNO;
    long FIELDNAMEID;
    long CSCORDERIMPORTFORMATID;
    short GROUPING;
} cscorderimportcsvcolumnsS;
#else /* TRANSCLASS */
typedef struct N_CSCORDERIMPORTCSVCOLUMNS {
    short COLUMNNO;
    long FIELDNAMEID;
    long CSCORDERIMPORTFORMATID;
    short GROUPING;

    bool operator == (const N_CSCORDERIMPORTCSVCOLUMNS& right) const {
        return (
            COLUMNNO == right.COLUMNNO &&
            FIELDNAMEID == right.FIELDNAMEID &&
            CSCORDERIMPORTFORMATID == right.CSCORDERIMPORTFORMATID &&
            GROUPING == right.GROUPING
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        COLUMNNO = 0;
        FIELDNAMEID = 0;
        CSCORDERIMPORTFORMATID = 0;
        GROUPING = 0;
#endif
    }
} cscorderimportcsvcolumnsS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of CSCORDERIMPORTCSVCOLUMNS **************************/

struct S_CSCORDERIMPORTCSVCOLUMNS {
    char COLUMNNO[7];
    char FIELDNAMEID[11];
    char CSCORDERIMPORTFORMATID[11];
    char GROUPING[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of CSCORDERIMPORTCSVCOLUMNS *********/

struct O_CSCORDERIMPORTCSVCOLUMNS {
    char COLUMNNO[7];
    char FIELDNAMEID[11];
    char CSCORDERIMPORTFORMATID[11];
    char GROUPING[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of CSCORDERIMPORTCSVCOLUMNS ********************/

struct C_CSCORDERIMPORTCSVCOLUMNS {
    short COLUMNNO;
    long FIELDNAMEID;
    long CSCORDERIMPORTFORMATID;
    short GROUPING;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of CSCORDERIMPORTCSVCOLUMNS ******************/

struct I_CSCORDERIMPORTCSVCOLUMNS {
    short COLUMNNO;
    short FIELDNAMEID;
    short CSCORDERIMPORTFORMATID;
    short GROUPING;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CSCORDERIMPORTCSVCOLUMNS ****************************/

#if defined (BUF_DESC)
static struct buf_desc CSCORDERIMPORTCSVCOLUMNS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CSCORDERIMPORTCSVCOLUMNS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* description for datatypes of CSCORDERIMPORTCSVCOLUMNS **********************/

 #define CSCORDERIMPORTCSVCOLUMNS_S390 \
         short COLUMNNO; \
         long FIELDNAMEID; \
         long CSCORDERIMPORTFORMATID; \
         short GROUPING; \



/* Copy-Function Struct to single Data CSCORDERIMPORTCSVCOLUMNS ***************/

 #define CSCORDERIMPORTCSVCOLUMNS_S390_COPY_TO_SINGLE(_x_) \
         COLUMNNO=_x_->COLUMNNO;\
         FIELDNAMEID=_x_->FIELDNAMEID;\
         CSCORDERIMPORTFORMATID=_x_->CSCORDERIMPORTFORMATID;\
         GROUPING=_x_->GROUPING;\

 #define CSCORDERIMPORTCSVCOLUMNS_S390_COPY_TO_STRUCT(_x_) \
          _x_->COLUMNNO=COLUMNNO;\
          _x_->FIELDNAMEID=FIELDNAMEID;\
          _x_->CSCORDERIMPORTFORMATID=CSCORDERIMPORTFORMATID;\
          _x_->GROUPING=GROUPING;\



/* FunctionNumber-Define of CSCOrderImportCSVColumns **************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of CSCOrderImportCSVColumns **********************/


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

class CCSCORDERIMPORTCSVCOLUMNS : public ppDadeVirtual {
public:
    cscorderimportcsvcolumnsS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<cscorderimportcsvcolumnsS> lst; // class list

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
                     vector< cscorderimportcsvcolumnsS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     cscorderimportcsvcolumnsS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< cscorderimportcsvcolumnsS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<cscorderimportcsvcolumnsS>::iterator
                 beginList() { return lst.begin(); }
    vector<cscorderimportcsvcolumnsS>::iterator
                 endList  () { return lst.end  (); }

    short        GetColumnno() const { return s.COLUMNNO; }
    long         GetFieldnameid() const { return s.FIELDNAMEID; }
    long         GetCscorderimportformatid() const { return s.CSCORDERIMPORTFORMATID; }
    short        GetGrouping() const { return s.GROUPING; }

    const cscorderimportcsvcolumnsS &
                 GetStruct() const { return s; }
    void         SetColumnno(short t) { s.COLUMNNO = t; }
    void         SetFieldnameid(long t) { s.FIELDNAMEID = t; }
    void         SetCscorderimportformatid(long t) { s.CSCORDERIMPORTFORMATID = t; }
    void         SetGrouping(short t) { s.GROUPING = t; }

    void         SetStruct(const cscorderimportcsvcolumnsS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCSCORDERIMPORTCSVCOLUMNS() {
        ::buf_default((void *)&s, CSCORDERIMPORTCSVCOLUMNS_BES, CSCORDERIMPORTCSVCOLUMNS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCSCORDERIMPORTCSVCOLUMNS() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CSCORDERIMPORTCSVCOLUMNS_BES, CSCORDERIMPORTCSVCOLUMNS_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, CSCORDERIMPORTCSVCOLUMNS_BES, (int)CSCORDERIMPORTCSVCOLUMNS_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, CSCORDERIMPORTCSVCOLUMNS_BES, (int)CSCORDERIMPORTCSVCOLUMNS_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_CSCORDERIMPORTCSVCOLUMNS & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CSCORDERIMPORTCSVCOLUMNS_BES, (int)CSCORDERIMPORTCSVCOLUMNS_ANZ, error_msg);
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
/* CreateSqlStatement of CSCORDERIMPORTCSVCOLUMNS *****************************/

 #define CSCORDERIMPORTCSVCOLUMNS_CREATE(x) EXEC SQL create table x (\
         COLUMNNO smallint default 0 not null,\
         FIELDNAMEID integer default 0 not null,\
         CSCORDERIMPORTFORMATID integer default 0 not null,\
         GROUPING smallint default 0 not null) in ksc extent size 16 next size 8 lock mode row;



/* CreateIndexStatement of CSCORDERIMPORTCSVCOLUMNS ***************************/

 #define CSCORDERIMPORTCSVCOLUMNS_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_csvcolumnes_1 on _X_(\
              CSCOrderImportFormatID,\
              ColumnNo ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of CSCORDERIMPORTCSVCOLUMNS ***************************/

 #define CSCORDERIMPORTCSVCOLUMNS_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_csvcolumnes_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
