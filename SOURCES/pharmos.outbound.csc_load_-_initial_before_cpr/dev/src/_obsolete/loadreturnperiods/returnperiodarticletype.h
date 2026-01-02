#ifndef __PP_RETURNPERIODARTICLETYPE_H_
#define __PP_RETURNPERIODARTICLETYPE_H_

/******************************************************************************/
/**/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* Length-Define of RETURNPERIODARTICLETYPE ***********************************/

#define L_RETURNPERIODARTICLETYPE_ARTICLETYPEID 6
#define L_RETURNPERIODARTICLETYPE_NAME 30

/* Length/Count-Define of RETURNPERIODARTICLETYPE *****************************/

#define LS_RETURNPERIODARTICLETYPE_ARTICLETYPEID 5 + 1
#define LS_RETURNPERIODARTICLETYPE_NAME 30 + 1

#define RETURNPERIODARTICLETYPEARTICLETYPEID 0
#define RETURNPERIODARTICLETYPENAME 1

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define RETURNPERIODARTICLETYPE_H
#define RETURNPERIODARTICLETYPE_ANZ ( sizeof(RETURNPERIODARTICLETYPE_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of RETURNPERIODARTICLETYPE ***************************************/

#define RETURNPERIODARTICLETYPE_LISTE \
        RETURNPERIODARTICLETYPE.ARTICLETYPEID,\
        RETURNPERIODARTICLETYPE.NAME
#define RETURNPERIODARTICLETYPE_LISTE_390 \
        ARTICLETYPEID,\
        NAME
#define RETURNPERIODARTICLETYPE_PLISTE \
        "RETURNPERIODARTICLETYPE.ARTICLETYPEID,"\
        "RETURNPERIODARTICLETYPE.NAME"
#define RETURNPERIODARTICLETYPE_PELISTE \
        "ARTICLETYPEID,"\
        "NAME"
#define RETURNPERIODARTICLETYPE_UPDLISTE \
        "ARTICLETYPEID=?,"\
        "NAME=?"
/* SqlMacros-Define of RETURNPERIODARTICLETYPE ********************************/

#define RETURNPERIODARTICLETYPE_ZEIGER(x) \
        :x->ARTICLETYPEID,\
        :x->NAME
#define RETURNPERIODARTICLETYPE_ZEIGERSEL(x) \
        :x->ARTICLETYPEID,\
        :x->NAME
#define RETURNPERIODARTICLETYPE_UPDATE(x) \
        RETURNPERIODARTICLETYPE.ARTICLETYPEID=:x->ARTICLETYPEID,\
        RETURNPERIODARTICLETYPE.NAME=:x->NAME
/* SqlMacros390-Define of RETURNPERIODARTICLETYPE *****************************/

#define RETURNPERIODARTICLETYPE_ZEIGER_390 \
        :ARTICLETYPEID,\
        :NAME
#define RETURNPERIODARTICLETYPE_UPDATE_390 \
        ARTICLETYPEID=:ARTICLETYPEID,\
        NAME=:NAME
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of RETURNPERIODARTICLETYPE *********************************/

#ifndef TRANSCLASS
typedef struct N_RETURNPERIODARTICLETYPE {
    short ARTICLETYPEID;
    char NAME[31];
} returnperiodarticletypeS;
#else /* TRANSCLASS */
typedef struct N_RETURNPERIODARTICLETYPE {
    short ARTICLETYPEID;
    char NAME[31];

    bool operator == (const N_RETURNPERIODARTICLETYPE& right) const {
        return (
            ARTICLETYPEID == right.ARTICLETYPEID &&
            !strcmp(NAME, right.NAME)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        ARTICLETYPEID = 0;
        strcpy(NAME, " " );
#endif
    }
} returnperiodarticletypeS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of RETURNPERIODARTICLETYPE ***************************/

struct S_RETURNPERIODARTICLETYPE {
    char ARTICLETYPEID[7];
    char NAME[30 + 1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of RETURNPERIODARTICLETYPE **********/

struct O_RETURNPERIODARTICLETYPE {
    char ARTICLETYPEID[7];
    char NAME[30];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of RETURNPERIODARTICLETYPE *********************/

struct C_RETURNPERIODARTICLETYPE {
    short ARTICLETYPEID;
    char NAME[31];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of RETURNPERIODARTICLETYPE *******************/

struct I_RETURNPERIODARTICLETYPE {
    short ARTICLETYPEID;
    short NAME;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of RETURNPERIODARTICLETYPE *****************************/

#if defined (BUF_DESC)
static struct buf_desc RETURNPERIODARTICLETYPE_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc RETURNPERIODARTICLETYPE_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
};
#endif

/* description for datatypes of RETURNPERIODARTICLETYPE ***********************/

 #define RETURNPERIODARTICLETYPE_S390 \
         short ARTICLETYPEID; \
         char NAME[31]; \



/* Copy-Function Struct to single Data RETURNPERIODARTICLETYPE ****************/

 #define RETURNPERIODARTICLETYPE_S390_COPY_TO_SINGLE(_x_) \
         ARTICLETYPEID=_x_->ARTICLETYPEID;\
          strcpy(NAME,_x_->NAME);\

 #define RETURNPERIODARTICLETYPE_S390_COPY_TO_STRUCT(_x_) \
          _x_->ARTICLETYPEID=ARTICLETYPEID;\
          strcpy(_x_->NAME,NAME);\



/* FunctionNumber-Define of ReturnPeriodArticleType ***************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of ReturnPeriodArticleType ***********************/


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

class CRETURNPERIODARTICLETYPE : public ppDadeVirtual {
public:
    returnperiodarticletypeS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<returnperiodarticletypeS> lst; // class list

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
                     vector< returnperiodarticletypeS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     returnperiodarticletypeS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< returnperiodarticletypeS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<returnperiodarticletypeS>::iterator
                 beginList() { return lst.begin(); }
    vector<returnperiodarticletypeS>::iterator
                 endList  () { return lst.end  (); }

    short        GetArticletypeid() const { return s.ARTICLETYPEID; }
    const char*  GetName(ppString & t) const { t = s.NAME; t.erasespace(ppString::END); return t.c_str(); }

    const returnperiodarticletypeS &
                 GetStruct() const { return s; }
    void         SetArticletypeid(short t) { s.ARTICLETYPEID = t; }
    void         SetName(const ppString & t) { ppGStrCopy(s.NAME, t.c_str(), L_RETURNPERIODARTICLETYPE_NAME); }

    void         SetStruct(const returnperiodarticletypeS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CRETURNPERIODARTICLETYPE() {
        ::buf_default((void *)&s, RETURNPERIODARTICLETYPE_BES, RETURNPERIODARTICLETYPE_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CRETURNPERIODARTICLETYPE() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, RETURNPERIODARTICLETYPE_BES, RETURNPERIODARTICLETYPE_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, RETURNPERIODARTICLETYPE_BES, (int)RETURNPERIODARTICLETYPE_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, RETURNPERIODARTICLETYPE_BES, (int)RETURNPERIODARTICLETYPE_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_RETURNPERIODARTICLETYPE & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.NAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, RETURNPERIODARTICLETYPE_BES, (int)RETURNPERIODARTICLETYPE_ANZ, error_msg);
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
/* CreateSqlStatement of RETURNPERIODARTICLETYPE ******************************/

 #define RETURNPERIODARTICLETYPE_CREATE(x) EXEC SQL create table x (\
         ARTICLETYPEID smallint default 0 not null,\
         NAME char(30) default " " not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of RETURNPERIODARTICLETYPE ****************************/

 #define RETURNPERIODARTICLETYPE_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_returnperiodarticletype_1 on _X_(\
              articletypeid ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of RETURNPERIODARTICLETYPE ****************************/

 #define RETURNPERIODARTICLETYPE_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_returnperiodarticletype_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
