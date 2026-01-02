#ifndef __PP_PARAMETERCHANGELOG_H_
#define __PP_PARAMETERCHANGELOG_H_

/******************************************************************************/
/* c:\prri\Headerfiles\parameterchangelog *************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of PARAMETERCHANGELOG ****************************************/

#define L_PARAMETERCHANGELOG_BRANCHNO 6
#define L_PARAMETERCHANGELOG_USER_ID 11
#define L_PARAMETERCHANGELOG_USER_BRANCHNO 6
#define L_PARAMETERCHANGELOG_DATE_CHANGE 11
#define L_PARAMETERCHANGELOG_TIME_CHANGE 11
#define L_PARAMETERCHANGELOG_PARAMETER_NAME 30
#define L_PARAMETERCHANGELOG_PARAMETER_TABLE 30
#define L_PARAMETERCHANGELOG_KEYOFCHANGE 100
#define L_PARAMETERCHANGELOG_OLD_VALUE 50
#define L_PARAMETERCHANGELOG_NEW_VALUE 50

/* Length/Count-Define of PARAMETERCHANGELOG **********************************/

#define LS_PARAMETERCHANGELOG_BRANCHNO 5 + 1
#define LS_PARAMETERCHANGELOG_USER_ID 10 + 1
#define LS_PARAMETERCHANGELOG_USER_BRANCHNO 5 + 1
#define LS_PARAMETERCHANGELOG_DATE_CHANGE 10 + 1
#define LS_PARAMETERCHANGELOG_TIME_CHANGE 10 + 1
#define LS_PARAMETERCHANGELOG_PARAMETER_NAME 30 + 1
#define LS_PARAMETERCHANGELOG_PARAMETER_TABLE 30 + 1
#define LS_PARAMETERCHANGELOG_KEYOFCHANGE 100 + 1
#define LS_PARAMETERCHANGELOG_OLD_VALUE 50 + 1
#define LS_PARAMETERCHANGELOG_NEW_VALUE 50 + 1

#define PARAMETERCHANGELOGBRANCHNO 0
#define PARAMETERCHANGELOGUSER_ID 1
#define PARAMETERCHANGELOGUSER_BRANCHNO 2
#define PARAMETERCHANGELOGDATE_CHANGE 3
#define PARAMETERCHANGELOGTIME_CHANGE 4
#define PARAMETERCHANGELOGPARAMETER_NAME 5
#define PARAMETERCHANGELOGPARAMETER_TABLE 6
#define PARAMETERCHANGELOGKEYOFCHANGE 7
#define PARAMETERCHANGELOGOLD_VALUE 8
#define PARAMETERCHANGELOGNEW_VALUE 9

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define PARAMETERCHANGELOG_H
#define PARAMETERCHANGELOG_ANZ ( sizeof(PARAMETERCHANGELOG_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of PARAMETERCHANGELOG ********************************************/

#define PARAMETERCHANGELOG_LISTE \
        PARAMETER_CHANGE_LOGGING.BRANCHNO,\
        PARAMETER_CHANGE_LOGGING.USER_ID,\
        PARAMETER_CHANGE_LOGGING.USER_BRANCHNO,\
        PARAMETER_CHANGE_LOGGING.DATE_CHANGE,\
        PARAMETER_CHANGE_LOGGING.TIME_CHANGE,\
        PARAMETER_CHANGE_LOGGING.PARAMETER_NAME,\
        PARAMETER_CHANGE_LOGGING.PARAMETER_TABLE,\
        PARAMETER_CHANGE_LOGGING.KEYOFCHANGE,\
        PARAMETER_CHANGE_LOGGING.OLD_VALUE,\
        PARAMETER_CHANGE_LOGGING.NEW_VALUE
#define PARAMETERCHANGELOG_LISTE_390 \
        BRANCHNO,\
        USER_ID,\
        USER_BRANCHNO,\
        DATE_CHANGE,\
        TIME_CHANGE,\
        PARAMETER_NAME,\
        PARAMETER_TABLE,\
        KEYOFCHANGE,\
        OLD_VALUE,\
        NEW_VALUE
#define PARAMETERCHANGELOG_PLISTE \
        "PARAMETER_CHANGE_LOGGING.BRANCHNO,"\
        "PARAMETER_CHANGE_LOGGING.USER_ID,"\
        "PARAMETER_CHANGE_LOGGING.USER_BRANCHNO,"\
        "PARAMETER_CHANGE_LOGGING.DATE_CHANGE,"\
        "PARAMETER_CHANGE_LOGGING.TIME_CHANGE,"\
        "PARAMETER_CHANGE_LOGGING.PARAMETER_NAME,"\
        "PARAMETER_CHANGE_LOGGING.PARAMETER_TABLE,"\
        "PARAMETER_CHANGE_LOGGING.KEYOFCHANGE,"\
        "PARAMETER_CHANGE_LOGGING.OLD_VALUE,"\
        "PARAMETER_CHANGE_LOGGING.NEW_VALUE"
#define PARAMETERCHANGELOG_PELISTE \
        "BRANCHNO,"\
        "USER_ID,"\
        "USER_BRANCHNO,"\
        "DATE_CHANGE,"\
        "TIME_CHANGE,"\
        "PARAMETER_NAME,"\
        "PARAMETER_TABLE,"\
        "KEYOFCHANGE,"\
        "OLD_VALUE,"\
        "NEW_VALUE"
#define PARAMETERCHANGELOG_UPDLISTE \
        "BRANCHNO=?,"\
        "USER_ID=?,"\
        "USER_BRANCHNO=?,"\
        "DATE_CHANGE=?,"\
        "TIME_CHANGE=?,"\
        "PARAMETER_NAME=?,"\
        "PARAMETER_TABLE=?,"\
        "KEYOFCHANGE=?,"\
        "OLD_VALUE=?,"\
        "NEW_VALUE=?"
/* SqlMacros-Define of PARAMETERCHANGELOG *************************************/

#define PARAMETERCHANGELOG_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->USER_ID,\
        :x->USER_BRANCHNO,\
        :x->DATE_CHANGE,\
        :x->TIME_CHANGE,\
        :x->PARAMETER_NAME,\
        :x->PARAMETER_TABLE,\
        :x->KEYOFCHANGE,\
        :x->OLD_VALUE,\
        :x->NEW_VALUE
#define PARAMETERCHANGELOG_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->USER_ID,\
        :x->USER_BRANCHNO,\
        :x->DATE_CHANGE,\
        :x->TIME_CHANGE,\
        :x->PARAMETER_NAME,\
        :x->PARAMETER_TABLE,\
        :x->KEYOFCHANGE,\
        :x->OLD_VALUE,\
        :x->NEW_VALUE
#define PARAMETERCHANGELOG_UPDATE(x) \
        PARAMETER_CHANGE_LOGGING.BRANCHNO=:x->BRANCHNO,\
        PARAMETER_CHANGE_LOGGING.USER_ID=:x->USER_ID,\
        PARAMETER_CHANGE_LOGGING.USER_BRANCHNO=:x->USER_BRANCHNO,\
        PARAMETER_CHANGE_LOGGING.DATE_CHANGE=:x->DATE_CHANGE,\
        PARAMETER_CHANGE_LOGGING.TIME_CHANGE=:x->TIME_CHANGE,\
        PARAMETER_CHANGE_LOGGING.PARAMETER_NAME=:x->PARAMETER_NAME,\
        PARAMETER_CHANGE_LOGGING.PARAMETER_TABLE=:x->PARAMETER_TABLE,\
        PARAMETER_CHANGE_LOGGING.KEYOFCHANGE=:x->KEYOFCHANGE,\
        PARAMETER_CHANGE_LOGGING.OLD_VALUE=:x->OLD_VALUE,\
        PARAMETER_CHANGE_LOGGING.NEW_VALUE=:x->NEW_VALUE
/* SqlMacros390-Define of PARAMETERCHANGELOG **********************************/

#define PARAMETERCHANGELOG_ZEIGER_390 \
        :BRANCHNO,\
        :USER_ID,\
        :USER_BRANCHNO,\
        :DATE_CHANGE,\
        :TIME_CHANGE,\
        :PARAMETER_NAME,\
        :PARAMETER_TABLE,\
        :KEYOFCHANGE,\
        :OLD_VALUE,\
        :NEW_VALUE
#define PARAMETERCHANGELOG_UPDATE_390 \
        BRANCHNO=:BRANCHNO,\
        USER_ID=:USER_ID,\
        USER_BRANCHNO=:USER_BRANCHNO,\
        DATE_CHANGE=:DATE_CHANGE,\
        TIME_CHANGE=:TIME_CHANGE,\
        PARAMETER_NAME=:PARAMETER_NAME,\
        PARAMETER_TABLE=:PARAMETER_TABLE,\
        KEYOFCHANGE=:KEYOFCHANGE,\
        OLD_VALUE=:OLD_VALUE,\
        NEW_VALUE=:NEW_VALUE
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of PARAMETERCHANGELOG **************************************/

#ifndef TRANSCLASS
typedef struct N_PARAMETERCHANGELOG {
    short BRANCHNO;
    long USER_ID;
    short USER_BRANCHNO;
    long DATE_CHANGE;
    long TIME_CHANGE;
    char PARAMETER_NAME[31];
    char PARAMETER_TABLE[31];
    char KEYOFCHANGE[101];
    char OLD_VALUE[51];
    char NEW_VALUE[51];
} parameterchangelogS;
#else /* TRANSCLASS */
typedef struct N_PARAMETERCHANGELOG {
    short BRANCHNO;
    long USER_ID;
    short USER_BRANCHNO;
    long DATE_CHANGE;
    long TIME_CHANGE;
    char PARAMETER_NAME[31];
    char PARAMETER_TABLE[31];
    char KEYOFCHANGE[101];
    char OLD_VALUE[51];
    char NEW_VALUE[51];

    bool operator == (const N_PARAMETERCHANGELOG& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            USER_ID == right.USER_ID &&
            USER_BRANCHNO == right.USER_BRANCHNO &&
            DATE_CHANGE == right.DATE_CHANGE &&
            TIME_CHANGE == right.TIME_CHANGE &&
            !strcmp(PARAMETER_NAME, right.PARAMETER_NAME) &&
            !strcmp(PARAMETER_TABLE, right.PARAMETER_TABLE) &&
            !strcmp(KEYOFCHANGE, right.KEYOFCHANGE) &&
            !strcmp(OLD_VALUE, right.OLD_VALUE) &&
            !strcmp(NEW_VALUE, right.NEW_VALUE)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        USER_ID = 0;
        USER_BRANCHNO = 0;
        DATE_CHANGE = 0;
        TIME_CHANGE = 0;
        strcpy(PARAMETER_NAME, " " );
        strcpy(PARAMETER_TABLE, " " );
        strcpy(KEYOFCHANGE, " " );
        strcpy(OLD_VALUE, " " );
        strcpy(NEW_VALUE, " " );
#endif
    }
} parameterchangelogS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of PARAMETERCHANGELOG ********************************/

struct S_PARAMETERCHANGELOG {
    char BRANCHNO[7];
    char USER_ID[11];
    char USER_BRANCHNO[7];
    char DATE_CHANGE[11];
    char TIME_CHANGE[11];
    char PARAMETER_NAME[30 + 1];
    char PARAMETER_TABLE[30 + 1];
    char KEYOFCHANGE[100 + 1];
    char OLD_VALUE[50 + 1];
    char NEW_VALUE[50 + 1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of PARAMETERCHANGELOG ***************/

struct O_PARAMETERCHANGELOG {
    char BRANCHNO[7];
    char USER_ID[11];
    char USER_BRANCHNO[7];
    char DATE_CHANGE[11];
    char TIME_CHANGE[11];
    char PARAMETER_NAME[30];
    char PARAMETER_TABLE[30];
    char KEYOFCHANGE[100];
    char OLD_VALUE[50];
    char NEW_VALUE[50];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of PARAMETERCHANGELOG **************************/

struct C_PARAMETERCHANGELOG {
    short BRANCHNO;
    long USER_ID;
    short USER_BRANCHNO;
    long DATE_CHANGE;
    long TIME_CHANGE;
    char PARAMETER_NAME[31];
    char PARAMETER_TABLE[31];
    char KEYOFCHANGE[101];
    char OLD_VALUE[51];
    char NEW_VALUE[51];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of PARAMETERCHANGELOG ************************/

struct I_PARAMETERCHANGELOG {
    short BRANCHNO;
    short USER_ID;
    short USER_BRANCHNO;
    short DATE_CHANGE;
    short TIME_CHANGE;
    short PARAMETER_NAME;
    short PARAMETER_TABLE;
    short KEYOFCHANGE;
    short OLD_VALUE;
    short NEW_VALUE;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of PARAMETERCHANGELOG **********************************/

#if defined (BUF_DESC)
static struct buf_desc PARAMETERCHANGELOG_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 100, 0 },
   { TYP_C, 50, 0 },
   { TYP_C, 50, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc PARAMETERCHANGELOG_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 100, 0 },
   { TYP_C, 50, 0 },
   { TYP_C, 50, 0 },
};
#endif

/* description for datatypes of PARAMETERCHANGELOG ****************************/

 #define PARAMETERCHANGELOG_S390 \
         short BRANCHNO; \
         long USER_ID; \
         short USER_BRANCHNO; \
         long DATE_CHANGE; \
         long TIME_CHANGE; \
         char PARAMETER_NAME[31]; \
         char PARAMETER_TABLE[31]; \
         char KEYOFCHANGE[101]; \
         char OLD_VALUE[51]; \
         char NEW_VALUE[51]; \



/* Copy-Function Struct to single Data PARAMETERCHANGELOG *********************/

 #define PARAMETERCHANGELOG_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         USER_ID=_x_->USER_ID;\
         USER_BRANCHNO=_x_->USER_BRANCHNO;\
         DATE_CHANGE=_x_->DATE_CHANGE;\
         TIME_CHANGE=_x_->TIME_CHANGE;\
          strcpy(PARAMETER_NAME,_x_->PARAMETER_NAME);\
          strcpy(PARAMETER_TABLE,_x_->PARAMETER_TABLE);\
          strcpy(KEYOFCHANGE,_x_->KEYOFCHANGE);\
          strcpy(OLD_VALUE,_x_->OLD_VALUE);\
          strcpy(NEW_VALUE,_x_->NEW_VALUE);\

 #define PARAMETERCHANGELOG_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->USER_ID=USER_ID;\
          _x_->USER_BRANCHNO=USER_BRANCHNO;\
          _x_->DATE_CHANGE=DATE_CHANGE;\
          _x_->TIME_CHANGE=TIME_CHANGE;\
          strcpy(_x_->PARAMETER_NAME,PARAMETER_NAME);\
          strcpy(_x_->PARAMETER_TABLE,PARAMETER_TABLE);\
          strcpy(_x_->KEYOFCHANGE,KEYOFCHANGE);\
          strcpy(_x_->OLD_VALUE,OLD_VALUE);\
          strcpy(_x_->NEW_VALUE,NEW_VALUE);\



/* FunctionNumber-Define of parameterchangelog ********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of parameterchangelog ****************************/


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

class CPARAMETERCHANGELOG : public ppDadeVirtual {
public:
    parameterchangelogS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<parameterchangelogS> lst; // class list

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
                     vector< parameterchangelogS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     parameterchangelogS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< parameterchangelogS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<parameterchangelogS>::iterator
                 beginList() { return lst.begin(); }
    vector<parameterchangelogS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetUser_id() const { return s.USER_ID; }
    short        GetUser_branchno() const { return s.USER_BRANCHNO; }
    long         GetDate_change() const { return s.DATE_CHANGE; }
    long         GetTime_change() const { return s.TIME_CHANGE; }
    const char*  GetParameter_name(ppString & t) const { t = s.PARAMETER_NAME; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetParameter_table(ppString & t) const { t = s.PARAMETER_TABLE; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetKeyofchange(ppString & t) const { t = s.KEYOFCHANGE; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetOld_value(ppString & t) const { t = s.OLD_VALUE; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetNew_value(ppString & t) const { t = s.NEW_VALUE; t.erasespace(ppString::END); return t.c_str(); }

    const parameterchangelogS &
                 GetStruct() const { return s; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetUser_id(long t) { s.USER_ID = t; }
    void         SetUser_branchno(short t) { s.USER_BRANCHNO = t; }
    void         SetDate_change(long t) { s.DATE_CHANGE = t; }
    void         SetTime_change(long t) { s.TIME_CHANGE = t; }
    void         SetParameter_name(const ppString & t) { ppGStrCopy(s.PARAMETER_NAME, t.c_str(), L_PARAMETERCHANGELOG_PARAMETER_NAME); }
    void         SetParameter_table(const ppString & t) { ppGStrCopy(s.PARAMETER_TABLE, t.c_str(), L_PARAMETERCHANGELOG_PARAMETER_TABLE); }
    void         SetKeyofchange(const ppString & t) { ppGStrCopy(s.KEYOFCHANGE, t.c_str(), L_PARAMETERCHANGELOG_KEYOFCHANGE); }
    void         SetOld_value(const ppString & t) { ppGStrCopy(s.OLD_VALUE, t.c_str(), L_PARAMETERCHANGELOG_OLD_VALUE); }
    void         SetNew_value(const ppString & t) { ppGStrCopy(s.NEW_VALUE, t.c_str(), L_PARAMETERCHANGELOG_NEW_VALUE); }

    void         SetStruct(const parameterchangelogS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CPARAMETERCHANGELOG() {
        ::buf_default((void *)&s, PARAMETERCHANGELOG_BES, PARAMETERCHANGELOG_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CPARAMETERCHANGELOG() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, PARAMETERCHANGELOG_BES, PARAMETERCHANGELOG_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, PARAMETERCHANGELOG_BES, (int)PARAMETERCHANGELOG_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, PARAMETERCHANGELOG_BES, (int)PARAMETERCHANGELOG_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_PARAMETERCHANGELOG & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.PARAMETER_NAME);
        ppGStripLast(d.PARAMETER_TABLE);
        ppGStripLast(d.KEYOFCHANGE);
        ppGStripLast(d.OLD_VALUE);
        ppGStripLast(d.NEW_VALUE);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, PARAMETERCHANGELOG_BES, (int)PARAMETERCHANGELOG_ANZ, error_msg);
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
/* CreateSqlStatement of PARAMETERCHANGELOG ***********************************/

 #define PARAMETERCHANGELOG_CREATE(x) EXEC SQL create table x (\
         BRANCHNO smallint default 0 not null,\
         USER_ID integer default 0 not null,\
         USER_BRANCHNO smallint default 0 not null,\
         DATE_CHANGE integer default 0 not null,\
         TIME_CHANGE integer default 0 not null,\
         PARAMETER_NAME char(30) default " " not null,\
         PARAMETER_TABLE char(30) default " " not null,\
         KEYOFCHANGE varchar(100,0) default " " not null,\
         OLD_VALUE varchar(50,0) default " " not null,\
         NEW_VALUE varchar(50,0) default " " not null) extent size 7844 next size 788 lock mode row;



/* CreateIndexStatement of PARAMETERCHANGELOG *********************************/

 #define PARAMETERCHANGELOG_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_paralogging_1 on _X_(\
              BranchNo,\
              date_change,\
              time_change,\
              parameter_table,\
              parameter_name );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index i_paralogging_2 on _X_(\
              user_branchno,\
              user_id );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of PARAMETERCHANGELOG *********************************/

 #define PARAMETERCHANGELOG_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_paralogging_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_paralogging_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
