#ifndef __PP_PARAMETER_CHANGE_LOGGING_H_
#define __PP_PARAMETER_CHANGE_LOGGING_H_

/******************************************************************************/
/**/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of PARAMETER_CHANGE_LOGGING **********************************/

#define L_PARAMETER_CHANGE_LOGGING_BRANCHNO 6
#define L_PARAMETER_CHANGE_LOGGING_USER_ID 11
#define L_PARAMETER_CHANGE_LOGGING_USERNAME 8
#define L_PARAMETER_CHANGE_LOGGING_USER_BRANCHNO 6
#define L_PARAMETER_CHANGE_LOGGING_DATE_CHANGE 11
#define L_PARAMETER_CHANGE_LOGGING_TIME_CHANGE 11
#define L_PARAMETER_CHANGE_LOGGING_PARAMETER_NAME 30
#define L_PARAMETER_CHANGE_LOGGING_PARAMETER_TABLE 30
#define L_PARAMETER_CHANGE_LOGGING_KEYOFCHANGE 100
#define L_PARAMETER_CHANGE_LOGGING_OLD_VALUE 50
#define L_PARAMETER_CHANGE_LOGGING_NEW_VALUE 50
#define L_PARAMETER_CHANGE_LOGGING_DATE_CHANGE_TO 11
#define L_PARAMETER_CHANGE_LOGGING_TIME_CHANGE_TO 11

/* Length/Count-Define of PARAMETER_CHANGE_LOGGING ****************************/

#define LS_PARAMETER_CHANGE_LOGGING_BRANCHNO 5 + 1
#define LS_PARAMETER_CHANGE_LOGGING_USER_ID 10 + 1
#define LS_PARAMETER_CHANGE_LOGGING_USERNAME 8 + 1
#define LS_PARAMETER_CHANGE_LOGGING_USER_BRANCHNO 5 + 1
#define LS_PARAMETER_CHANGE_LOGGING_DATE_CHANGE 10 + 1
#define LS_PARAMETER_CHANGE_LOGGING_TIME_CHANGE 10 + 1
#define LS_PARAMETER_CHANGE_LOGGING_PARAMETER_NAME 30 + 1
#define LS_PARAMETER_CHANGE_LOGGING_PARAMETER_TABLE 30 + 1
#define LS_PARAMETER_CHANGE_LOGGING_KEYOFCHANGE 100 + 1
#define LS_PARAMETER_CHANGE_LOGGING_OLD_VALUE 50 + 1
#define LS_PARAMETER_CHANGE_LOGGING_NEW_VALUE 50 + 1
#define LS_PARAMETER_CHANGE_LOGGING_DATE_CHANGE_TO 10 + 1
#define LS_PARAMETER_CHANGE_LOGGING_TIME_CHANGE_TO 10 + 1

#define PARAMETER_CHANGE_LOGGINGBRANCHNO 0
#define PARAMETER_CHANGE_LOGGINGUSER_ID 1
#define PARAMETER_CHANGE_LOGGINGUSERNAME 2
#define PARAMETER_CHANGE_LOGGINGUSER_BRANCHNO 3
#define PARAMETER_CHANGE_LOGGINGDATE_CHANGE 4
#define PARAMETER_CHANGE_LOGGINGTIME_CHANGE 5
#define PARAMETER_CHANGE_LOGGINGPARAMETER_NAME 6
#define PARAMETER_CHANGE_LOGGINGPARAMETER_TABLE 7
#define PARAMETER_CHANGE_LOGGINGKEYOFCHANGE 8
#define PARAMETER_CHANGE_LOGGINGOLD_VALUE 9
#define PARAMETER_CHANGE_LOGGINGNEW_VALUE 10
#define PARAMETER_CHANGE_LOGGINGDATE_CHANGE_TO 11
#define PARAMETER_CHANGE_LOGGINGTIME_CHANGE_TO 12

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define PARAMETER_CHANGE_LOGGING_H
#define PARAMETER_CHANGE_LOGGING_ANZ ( sizeof(PARAMETER_CHANGE_LOGGING_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of PARAMETER_CHANGE_LOGGING **************************************/

#define PARAMETER_CHANGE_LOGGING_LISTE \
        PARAMETER_CHANGE_LOGGING.BRANCHNO,\
        PARAMETER_CHANGE_LOGGING.USER_ID,\
        PASSWD.USERNAME,\
        PARAMETER_CHANGE_LOGGING.USER_BRANCHNO,\
        PARAMETER_CHANGE_LOGGING.DATE_CHANGE,\
        PARAMETER_CHANGE_LOGGING.TIME_CHANGE,\
        PARAMETER_CHANGE_LOGGING.PARAMETER_NAME,\
        PARAMETER_CHANGE_LOGGING.PARAMETER_TABLE,\
        PARAMETER_CHANGE_LOGGING.KEYOFCHANGE,\
        PARAMETER_CHANGE_LOGGING.OLD_VALUE,\
        PARAMETER_CHANGE_LOGGING.NEW_VALUE,\
        AADUMMY.DATE_CHANGE_TO,\
        AADUMMY.TIME_CHANGE_TO
#define PARAMETER_CHANGE_LOGGING_LISTE_390 \
        BRANCHNO,\
        USER_ID,\
        USERNAME,\
        USER_BRANCHNO,\
        DATE_CHANGE,\
        TIME_CHANGE,\
        PARAMETER_NAME,\
        PARAMETER_TABLE,\
        KEYOFCHANGE,\
        OLD_VALUE,\
        NEW_VALUE,\
        DATE_CHANGE_TO,\
        TIME_CHANGE_TO
#define PARAMETER_CHANGE_LOGGING_PLISTE \
        "PARAMETER_CHANGE_LOGGING.BRANCHNO,"\
        "PARAMETER_CHANGE_LOGGING.USER_ID,"\
        "PASSWD.USERNAME,"\
        "PARAMETER_CHANGE_LOGGING.USER_BRANCHNO,"\
        "PARAMETER_CHANGE_LOGGING.DATE_CHANGE,"\
        "PARAMETER_CHANGE_LOGGING.TIME_CHANGE,"\
        "PARAMETER_CHANGE_LOGGING.PARAMETER_NAME,"\
        "PARAMETER_CHANGE_LOGGING.PARAMETER_TABLE,"\
        "PARAMETER_CHANGE_LOGGING.KEYOFCHANGE,"\
        "PARAMETER_CHANGE_LOGGING.OLD_VALUE,"\
        "PARAMETER_CHANGE_LOGGING.NEW_VALUE,"\
        "AADUMMY.DATE_CHANGE_TO,"\
        "AADUMMY.TIME_CHANGE_TO"
#define PARAMETER_CHANGE_LOGGING_PELISTE \
        "BRANCHNO,"\
        "USER_ID,"\
        "USERNAME,"\
        "USER_BRANCHNO,"\
        "DATE_CHANGE,"\
        "TIME_CHANGE,"\
        "PARAMETER_NAME,"\
        "PARAMETER_TABLE,"\
        "KEYOFCHANGE,"\
        "OLD_VALUE,"\
        "NEW_VALUE,"\
        "DATE_CHANGE_TO,"\
        "TIME_CHANGE_TO"
#define PARAMETER_CHANGE_LOGGING_UPDLISTE \
        "BRANCHNO=?,"\
        "USER_ID=?,"\
        "USERNAME=?,"\
        "USER_BRANCHNO=?,"\
        "DATE_CHANGE=?,"\
        "TIME_CHANGE=?,"\
        "PARAMETER_NAME=?,"\
        "PARAMETER_TABLE=?,"\
        "KEYOFCHANGE=?,"\
        "OLD_VALUE=?,"\
        "NEW_VALUE=?,"\
        "DATE_CHANGE_TO=?,"\
        "TIME_CHANGE_TO=?"
/* SqlMacros-Define of PARAMETER_CHANGE_LOGGING *******************************/

#define PARAMETER_CHANGE_LOGGING_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->USER_ID,\
        :x->USERNAME,\
        :x->USER_BRANCHNO,\
        :x->DATE_CHANGE,\
        :x->TIME_CHANGE,\
        :x->PARAMETER_NAME,\
        :x->PARAMETER_TABLE,\
        :x->KEYOFCHANGE,\
        :x->OLD_VALUE,\
        :x->NEW_VALUE,\
        :x->DATE_CHANGE_TO,\
        :x->TIME_CHANGE_TO
#define PARAMETER_CHANGE_LOGGING_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->USER_ID,\
        :x->USERNAME,\
        :x->USER_BRANCHNO,\
        :x->DATE_CHANGE,\
        :x->TIME_CHANGE,\
        :x->PARAMETER_NAME,\
        :x->PARAMETER_TABLE,\
        :x->KEYOFCHANGE,\
        :x->OLD_VALUE,\
        :x->NEW_VALUE,\
        :x->DATE_CHANGE_TO,\
        :x->TIME_CHANGE_TO
#define PARAMETER_CHANGE_LOGGING_UPDATE(x) \
        PARAMETER_CHANGE_LOGGING.BRANCHNO=:x->BRANCHNO,\
        PARAMETER_CHANGE_LOGGING.USER_ID=:x->USER_ID,\
        PASSWD.USERNAME=:x->USERNAME,\
        PARAMETER_CHANGE_LOGGING.USER_BRANCHNO=:x->USER_BRANCHNO,\
        PARAMETER_CHANGE_LOGGING.DATE_CHANGE=:x->DATE_CHANGE,\
        PARAMETER_CHANGE_LOGGING.TIME_CHANGE=:x->TIME_CHANGE,\
        PARAMETER_CHANGE_LOGGING.PARAMETER_NAME=:x->PARAMETER_NAME,\
        PARAMETER_CHANGE_LOGGING.PARAMETER_TABLE=:x->PARAMETER_TABLE,\
        PARAMETER_CHANGE_LOGGING.KEYOFCHANGE=:x->KEYOFCHANGE,\
        PARAMETER_CHANGE_LOGGING.OLD_VALUE=:x->OLD_VALUE,\
        PARAMETER_CHANGE_LOGGING.NEW_VALUE=:x->NEW_VALUE,\
        AADUMMY.DATE_CHANGE_TO=:x->DATE_CHANGE_TO,\
        AADUMMY.TIME_CHANGE_TO=:x->TIME_CHANGE_TO
/* SqlMacros390-Define of PARAMETER_CHANGE_LOGGING ****************************/

#define PARAMETER_CHANGE_LOGGING_ZEIGER_390 \
        :BRANCHNO,\
        :USER_ID,\
        :USERNAME,\
        :USER_BRANCHNO,\
        :DATE_CHANGE,\
        :TIME_CHANGE,\
        :PARAMETER_NAME,\
        :PARAMETER_TABLE,\
        :KEYOFCHANGE,\
        :OLD_VALUE,\
        :NEW_VALUE,\
        :DATE_CHANGE_TO,\
        :TIME_CHANGE_TO
#define PARAMETER_CHANGE_LOGGING_UPDATE_390 \
        BRANCHNO=:BRANCHNO,\
        USER_ID=:USER_ID,\
        USERNAME=:USERNAME,\
        USER_BRANCHNO=:USER_BRANCHNO,\
        DATE_CHANGE=:DATE_CHANGE,\
        TIME_CHANGE=:TIME_CHANGE,\
        PARAMETER_NAME=:PARAMETER_NAME,\
        PARAMETER_TABLE=:PARAMETER_TABLE,\
        KEYOFCHANGE=:KEYOFCHANGE,\
        OLD_VALUE=:OLD_VALUE,\
        NEW_VALUE=:NEW_VALUE,\
        DATE_CHANGE_TO=:DATE_CHANGE_TO,\
        TIME_CHANGE_TO=:TIME_CHANGE_TO
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of PARAMETER_CHANGE_LOGGING ********************************/

#ifndef TRANSCLASS
typedef struct N_PARAMETER_CHANGE_LOGGING {
    short BRANCHNO;
    long USER_ID;
    char USERNAME[9];
    short USER_BRANCHNO;
    long DATE_CHANGE;
    long TIME_CHANGE;
    char PARAMETER_NAME[31];
    char PARAMETER_TABLE[31];
    char KEYOFCHANGE[101];
    char OLD_VALUE[51];
    char NEW_VALUE[51];
    long DATE_CHANGE_TO;
    long TIME_CHANGE_TO;
    long FETCH_REL;
} parameter_change_loggingS;
#else /* TRANSCLASS */
typedef struct N_PARAMETER_CHANGE_LOGGING {
    short BRANCHNO;
    long USER_ID;
    char USERNAME[9];
    short USER_BRANCHNO;
    long DATE_CHANGE;
    long TIME_CHANGE;
    char PARAMETER_NAME[31];
    char PARAMETER_TABLE[31];
    char KEYOFCHANGE[101];
    char OLD_VALUE[51];
    char NEW_VALUE[51];
    long DATE_CHANGE_TO;
    long TIME_CHANGE_TO;
    long FETCH_REL;
    bool operator == (const N_PARAMETER_CHANGE_LOGGING& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            USER_ID == right.USER_ID &&
            !strcmp(USERNAME, right.USERNAME) &&
            USER_BRANCHNO == right.USER_BRANCHNO &&
            DATE_CHANGE == right.DATE_CHANGE &&
            TIME_CHANGE == right.TIME_CHANGE &&
            !strcmp(PARAMETER_NAME, right.PARAMETER_NAME) &&
            !strcmp(PARAMETER_TABLE, right.PARAMETER_TABLE) &&
            !strcmp(KEYOFCHANGE, right.KEYOFCHANGE) &&
            !strcmp(OLD_VALUE, right.OLD_VALUE) &&
            !strcmp(NEW_VALUE, right.NEW_VALUE) &&
            DATE_CHANGE_TO == right.DATE_CHANGE_TO &&
            TIME_CHANGE_TO == right.TIME_CHANGE_TO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        USER_ID = 0;
        strcpy(USERNAME, " " );
        USER_BRANCHNO = 0;
        DATE_CHANGE = 0;
        TIME_CHANGE = 0;
        strcpy(PARAMETER_NAME, " " );
        strcpy(PARAMETER_TABLE, " " );
        strcpy(KEYOFCHANGE, " " );
        strcpy(OLD_VALUE, " " );
        strcpy(NEW_VALUE, " " );
        DATE_CHANGE_TO = 0;
        TIME_CHANGE_TO = 0;
#endif
    }
} parameter_change_loggingS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of PARAMETER_CHANGE_LOGGING **************************/

struct S_PARAMETER_CHANGE_LOGGING {
    char BRANCHNO[7];
    char USER_ID[11];
    char USERNAME[8 + 1];
    char USER_BRANCHNO[7];
    char DATE_CHANGE[11];
    char TIME_CHANGE[11];
    char PARAMETER_NAME[30 + 1];
    char PARAMETER_TABLE[30 + 1];
    char KEYOFCHANGE[100 + 1];
    char OLD_VALUE[50 + 1];
    char NEW_VALUE[50 + 1];
    char DATE_CHANGE_TO[11];
    char TIME_CHANGE_TO[11];
    char FETCH_REL[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of PARAMETER_CHANGE_LOGGING *********/

struct O_PARAMETER_CHANGE_LOGGING {
    char BRANCHNO[7];
    char USER_ID[11];
    char USERNAME[8];
    char USER_BRANCHNO[7];
    char DATE_CHANGE[11];
    char TIME_CHANGE[11];
    char PARAMETER_NAME[30];
    char PARAMETER_TABLE[30];
    char KEYOFCHANGE[100];
    char OLD_VALUE[50];
    char NEW_VALUE[50];
    char DATE_CHANGE_TO[11];
    char TIME_CHANGE_TO[11];
    char FETCH_REL[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of PARAMETER_CHANGE_LOGGING ********************/

struct C_PARAMETER_CHANGE_LOGGING {
    short BRANCHNO;
    long USER_ID;
    char USERNAME[9];
    short USER_BRANCHNO;
    long DATE_CHANGE;
    long TIME_CHANGE;
    char PARAMETER_NAME[31];
    char PARAMETER_TABLE[31];
    char KEYOFCHANGE[101];
    char OLD_VALUE[51];
    char NEW_VALUE[51];
    long DATE_CHANGE_TO;
    long TIME_CHANGE_TO;
    long FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of PARAMETER_CHANGE_LOGGING ******************/

struct I_PARAMETER_CHANGE_LOGGING {
    short BRANCHNO;
    short USER_ID;
    short USERNAME;
    short USER_BRANCHNO;
    short DATE_CHANGE;
    short TIME_CHANGE;
    short PARAMETER_NAME;
    short PARAMETER_TABLE;
    short KEYOFCHANGE;
    short OLD_VALUE;
    short NEW_VALUE;
    short DATE_CHANGE_TO;
    short TIME_CHANGE_TO;
    short FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of PARAMETER_CHANGE_LOGGING ****************************/

#if defined (BUF_DESC)
static struct buf_desc PARAMETER_CHANGE_LOGGING_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 8, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 100, 0 },
   { TYP_C, 50, 0 },
   { TYP_C, 50, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc PARAMETER_CHANGE_LOGGING_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 8, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 100, 0 },
   { TYP_C, 50, 0 },
   { TYP_C, 50, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* description for datatypes of PARAMETER_CHANGE_LOGGING **********************/

 #define PARAMETER_CHANGE_LOGGING_S390 \
         short BRANCHNO; \
         long USER_ID; \
         char USERNAME[9]; \
         short USER_BRANCHNO; \
         long DATE_CHANGE; \
         long TIME_CHANGE; \
         char PARAMETER_NAME[31]; \
         char PARAMETER_TABLE[31]; \
         char KEYOFCHANGE[101]; \
         char OLD_VALUE[51]; \
         char NEW_VALUE[51]; \
         long DATE_CHANGE_TO; \
         long TIME_CHANGE_TO; \
         long FETCH_REL;



/* Copy-Function Struct to single Data PARAMETER_CHANGE_LOGGING ***************/

 #define PARAMETER_CHANGE_LOGGING_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         USER_ID=_x_->USER_ID;\
          strcpy(USERNAME,_x_->USERNAME);\
         USER_BRANCHNO=_x_->USER_BRANCHNO;\
         DATE_CHANGE=_x_->DATE_CHANGE;\
         TIME_CHANGE=_x_->TIME_CHANGE;\
          strcpy(PARAMETER_NAME,_x_->PARAMETER_NAME);\
          strcpy(PARAMETER_TABLE,_x_->PARAMETER_TABLE);\
          strcpy(KEYOFCHANGE,_x_->KEYOFCHANGE);\
          strcpy(OLD_VALUE,_x_->OLD_VALUE);\
          strcpy(NEW_VALUE,_x_->NEW_VALUE);\
         DATE_CHANGE_TO=_x_->DATE_CHANGE_TO;\
         TIME_CHANGE_TO=_x_->TIME_CHANGE_TO;\
          FETCH_REL=_x_->FETCH_REL;\

 #define PARAMETER_CHANGE_LOGGING_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->USER_ID=USER_ID;\
          strcpy(_x_->USERNAME,USERNAME);\
          _x_->USER_BRANCHNO=USER_BRANCHNO;\
          _x_->DATE_CHANGE=DATE_CHANGE;\
          _x_->TIME_CHANGE=TIME_CHANGE;\
          strcpy(_x_->PARAMETER_NAME,PARAMETER_NAME);\
          strcpy(_x_->PARAMETER_TABLE,PARAMETER_TABLE);\
          strcpy(_x_->KEYOFCHANGE,KEYOFCHANGE);\
          strcpy(_x_->OLD_VALUE,OLD_VALUE);\
          strcpy(_x_->NEW_VALUE,NEW_VALUE);\
          _x_->DATE_CHANGE_TO=DATE_CHANGE_TO;\
          _x_->TIME_CHANGE_TO=TIME_CHANGE_TO;\
          _x_->FETCH_REL=FETCH_REL;\



/* FunctionNumber-Define of parameter_change_logging **************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of parameter_change_logging **********************/


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

class CPARAMETER_CHANGE_LOGGING : public ppDadeVirtual {
public:
    parameter_change_loggingS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<parameter_change_loggingS> lst; // class list

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
                     vector< parameter_change_loggingS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     parameter_change_loggingS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< parameter_change_loggingS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<parameter_change_loggingS>::iterator
                 beginList() { return lst.begin(); }
    vector<parameter_change_loggingS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetUser_id() const { return s.USER_ID; }
    const char*  GetUsername(ppString & t) const { t = s.USERNAME; t.erasespace(ppString::END); return t.c_str(); }
    short        GetUser_branchno() const { return s.USER_BRANCHNO; }
    long         GetDate_change() const { return s.DATE_CHANGE; }
    long         GetTime_change() const { return s.TIME_CHANGE; }
    const char*  GetParameter_name(ppString & t) const { t = s.PARAMETER_NAME; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetParameter_table(ppString & t) const { t = s.PARAMETER_TABLE; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetKeyofchange(ppString & t) const { t = s.KEYOFCHANGE; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetOld_value(ppString & t) const { t = s.OLD_VALUE; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetNew_value(ppString & t) const { t = s.NEW_VALUE; t.erasespace(ppString::END); return t.c_str(); }
    long         GetDate_change_to() const { return s.DATE_CHANGE_TO; }
    long         GetTime_change_to() const { return s.TIME_CHANGE_TO; }

    const parameter_change_loggingS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetUser_id(long t) { s.USER_ID = t; }
    void         SetUsername(const ppString & t) { ppGStrCopy(s.USERNAME, t.c_str(), L_PARAMETER_CHANGE_LOGGING_USERNAME); }
    void         SetUser_branchno(short t) { s.USER_BRANCHNO = t; }
    void         SetDate_change(long t) { s.DATE_CHANGE = t; }
    void         SetTime_change(long t) { s.TIME_CHANGE = t; }
    void         SetParameter_name(const ppString & t) { ppGStrCopy(s.PARAMETER_NAME, t.c_str(), L_PARAMETER_CHANGE_LOGGING_PARAMETER_NAME); }
    void         SetParameter_table(const ppString & t) { ppGStrCopy(s.PARAMETER_TABLE, t.c_str(), L_PARAMETER_CHANGE_LOGGING_PARAMETER_TABLE); }
    void         SetKeyofchange(const ppString & t) { ppGStrCopy(s.KEYOFCHANGE, t.c_str(), L_PARAMETER_CHANGE_LOGGING_KEYOFCHANGE); }
    void         SetOld_value(const ppString & t) { ppGStrCopy(s.OLD_VALUE, t.c_str(), L_PARAMETER_CHANGE_LOGGING_OLD_VALUE); }
    void         SetNew_value(const ppString & t) { ppGStrCopy(s.NEW_VALUE, t.c_str(), L_PARAMETER_CHANGE_LOGGING_NEW_VALUE); }
    void         SetDate_change_to(long t) { s.DATE_CHANGE_TO = t; }
    void         SetTime_change_to(long t) { s.TIME_CHANGE_TO = t; }

    void         SetStruct(const parameter_change_loggingS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CPARAMETER_CHANGE_LOGGING() {
        ::buf_default((void *)&s, PARAMETER_CHANGE_LOGGING_BES, PARAMETER_CHANGE_LOGGING_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CPARAMETER_CHANGE_LOGGING() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, PARAMETER_CHANGE_LOGGING_BES, PARAMETER_CHANGE_LOGGING_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, PARAMETER_CHANGE_LOGGING_BES, (int)PARAMETER_CHANGE_LOGGING_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, PARAMETER_CHANGE_LOGGING_BES, (int)PARAMETER_CHANGE_LOGGING_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, PARAMETER_CHANGE_LOGGING_BES, (int)PARAMETER_CHANGE_LOGGING_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_PARAMETER_CHANGE_LOGGING & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.USERNAME);
        ppGStripLast(d.PARAMETER_NAME);
        ppGStripLast(d.PARAMETER_TABLE);
        ppGStripLast(d.KEYOFCHANGE);
        ppGStripLast(d.OLD_VALUE);
        ppGStripLast(d.NEW_VALUE);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, PARAMETER_CHANGE_LOGGING_BES, (int)PARAMETER_CHANGE_LOGGING_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CPARAMETER_CHANGE_LOGGING c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, PARAMETER_CHANGE_LOGGING_BES, (int)PARAMETER_CHANGE_LOGGING_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};
#endif    // TRANSCLASS
/* CreateSqlStatement of PARAMETER_CHANGE_LOGGING *****************************/

 #define PARAMETER_CHANGE_LOGGING_CREATE(x) EXEC SQL create table x (\
         BRANCHNO smallint default 0 not null,\
         USER_ID integer default 0 not null,\
         USERNAME char(8) default " " not null,\
         USER_BRANCHNO smallint default 0 not null,\
         DATE_CHANGE integer default 0 not null,\
         TIME_CHANGE integer default 0 not null,\
         PARAMETER_NAME char(30) default " " not null,\
         PARAMETER_TABLE char(30) default " " not null,\
         KEYOFCHANGE varchar(100,0) default " " not null,\
         OLD_VALUE varchar(50,0) default " " not null,\
         NEW_VALUE varchar(50,0) default " " not null,\
         DATE_CHANGE_TO integer default 0 not null,\
         TIME_CHANGE_TO integer default 0 not null) in ksc extent size 7844 next size 788 lock mode row;



/* CreateIndexStatement of PARAMETER_CHANGE_LOGGING ***************************/

 #define PARAMETER_CHANGE_LOGGING_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_paralogging_1 on _X_(\
              BranchNo,\
              date_change,\
              time_change,\
              parameter_table,\
              parameter_name ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index i_paralogging_2 on _X_(\
              user_branchno,\
              user_id ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of PARAMETER_CHANGE_LOGGING ***************************/

 #define PARAMETER_CHANGE_LOGGING_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_paralogging_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_paralogging_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
