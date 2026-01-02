#ifndef __PP_PARAMETER_CHANGE_LOG_DEFS_H_
#define __PP_PARAMETER_CHANGE_LOG_DEFS_H_

/******************************************************************************/
/* c:\prri\Headerfiles\parameter_change_log_defs ******************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of PARAMETER_CHANGE_LOG_DEFS *********************************/

#define L_PARAMETER_CHANGE_LOG_DEFS_TABLE_NAME 30
#define L_PARAMETER_CHANGE_LOG_DEFS_FIELD_NAME 40
#define L_PARAMETER_CHANGE_LOG_DEFS_PARAMETER_NAME 30
#define L_PARAMETER_CHANGE_LOG_DEFS_PARAMETER_TABLE 30
#define L_PARAMETER_CHANGE_LOG_DEFS_FIELD_TYPE 10

/* Length/Count-Define of PARAMETER_CHANGE_LOG_DEFS ***************************/

#define LS_PARAMETER_CHANGE_LOG_DEFS_TABLE_NAME 30 + 1
#define LS_PARAMETER_CHANGE_LOG_DEFS_FIELD_NAME 40 + 1
#define LS_PARAMETER_CHANGE_LOG_DEFS_PARAMETER_NAME 30 + 1
#define LS_PARAMETER_CHANGE_LOG_DEFS_PARAMETER_TABLE 30 + 1
#define LS_PARAMETER_CHANGE_LOG_DEFS_FIELD_TYPE 10 + 1

#define PARAMETER_CHANGE_LOG_DEFSTABLE_NAME 0
#define PARAMETER_CHANGE_LOG_DEFSFIELD_NAME 1
#define PARAMETER_CHANGE_LOG_DEFSPARAMETER_NAME 2
#define PARAMETER_CHANGE_LOG_DEFSPARAMETER_TABLE 3
#define PARAMETER_CHANGE_LOG_DEFSFIELD_TYPE 4

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define PARAMETER_CHANGE_LOG_DEFS_H
#define PARAMETER_CHANGE_LOG_DEFS_ANZ ( sizeof(PARAMETER_CHANGE_LOG_DEFS_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of PARAMETER_CHANGE_LOG_DEFS *************************************/

#define PARAMETER_CHANGE_LOG_DEFS_LISTE \
        PARAMETER_CHANGE_LOG_DEFINITION.TABLE_NAME,\
        PARAMETER_CHANGE_LOG_DEFINITION.FIELD_NAME,\
        PARAMETER_CHANGE_LOG_DEFINITION.PARAMETER_NAME,\
        PARAMETER_CHANGE_LOG_DEFINITION.PARAMETER_TABLE,\
        PARAMETER_CHANGE_LOG_DEFINITION.FIELD_TYPE
#define PARAMETER_CHANGE_LOG_DEFS_LISTE_390 \
        TABLE_NAME,\
        FIELD_NAME,\
        PARAMETER_NAME,\
        PARAMETER_TABLE,\
        FIELD_TYPE
#define PARAMETER_CHANGE_LOG_DEFS_PLISTE \
        "PARAMETER_CHANGE_LOG_DEFINITION.TABLE_NAME,"\
        "PARAMETER_CHANGE_LOG_DEFINITION.FIELD_NAME,"\
        "PARAMETER_CHANGE_LOG_DEFINITION.PARAMETER_NAME,"\
        "PARAMETER_CHANGE_LOG_DEFINITION.PARAMETER_TABLE,"\
        "PARAMETER_CHANGE_LOG_DEFINITION.FIELD_TYPE"
#define PARAMETER_CHANGE_LOG_DEFS_PELISTE \
        "TABLE_NAME,"\
        "FIELD_NAME,"\
        "PARAMETER_NAME,"\
        "PARAMETER_TABLE,"\
        "FIELD_TYPE"
#define PARAMETER_CHANGE_LOG_DEFS_UPDLISTE \
        "TABLE_NAME=?,"\
        "FIELD_NAME=?,"\
        "PARAMETER_NAME=?,"\
        "PARAMETER_TABLE=?,"\
        "FIELD_TYPE=?"
/* SqlMacros-Define of PARAMETER_CHANGE_LOG_DEFS ******************************/

#define PARAMETER_CHANGE_LOG_DEFS_ZEIGER(x) \
        :x->TABLE_NAME,\
        :x->FIELD_NAME,\
        :x->PARAMETER_NAME,\
        :x->PARAMETER_TABLE,\
        :x->FIELD_TYPE
#define PARAMETER_CHANGE_LOG_DEFS_ZEIGERSEL(x) \
        :x->TABLE_NAME,\
        :x->FIELD_NAME,\
        :x->PARAMETER_NAME,\
        :x->PARAMETER_TABLE,\
        :x->FIELD_TYPE
#define PARAMETER_CHANGE_LOG_DEFS_UPDATE(x) \
        PARAMETER_CHANGE_LOG_DEFINITION.TABLE_NAME=:x->TABLE_NAME,\
        PARAMETER_CHANGE_LOG_DEFINITION.FIELD_NAME=:x->FIELD_NAME,\
        PARAMETER_CHANGE_LOG_DEFINITION.PARAMETER_NAME=:x->PARAMETER_NAME,\
        PARAMETER_CHANGE_LOG_DEFINITION.PARAMETER_TABLE=:x->PARAMETER_TABLE,\
        PARAMETER_CHANGE_LOG_DEFINITION.FIELD_TYPE=:x->FIELD_TYPE
/* SqlMacros390-Define of PARAMETER_CHANGE_LOG_DEFS ***************************/

#define PARAMETER_CHANGE_LOG_DEFS_ZEIGER_390 \
        :TABLE_NAME,\
        :FIELD_NAME,\
        :PARAMETER_NAME,\
        :PARAMETER_TABLE,\
        :FIELD_TYPE
#define PARAMETER_CHANGE_LOG_DEFS_UPDATE_390 \
        TABLE_NAME=:TABLE_NAME,\
        FIELD_NAME=:FIELD_NAME,\
        PARAMETER_NAME=:PARAMETER_NAME,\
        PARAMETER_TABLE=:PARAMETER_TABLE,\
        FIELD_TYPE=:FIELD_TYPE
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of PARAMETER_CHANGE_LOG_DEFS *******************************/

#ifndef TRANSCLASS
typedef struct N_PARAMETER_CHANGE_LOG_DEFS {
    char TABLE_NAME[31];
    char FIELD_NAME[41];
    char PARAMETER_NAME[31];
    char PARAMETER_TABLE[31];
    char FIELD_TYPE[11];
    long FETCH_REL;
} parameter_change_log_defsS;
#else /* TRANSCLASS */
typedef struct N_PARAMETER_CHANGE_LOG_DEFS {
    char TABLE_NAME[31];
    char FIELD_NAME[41];
    char PARAMETER_NAME[31];
    char PARAMETER_TABLE[31];
    char FIELD_TYPE[11];
    long FETCH_REL;
    bool operator == (const N_PARAMETER_CHANGE_LOG_DEFS& right) const {
        return (
            !strcmp(TABLE_NAME, right.TABLE_NAME) &&
            !strcmp(FIELD_NAME, right.FIELD_NAME) &&
            !strcmp(PARAMETER_NAME, right.PARAMETER_NAME) &&
            !strcmp(PARAMETER_TABLE, right.PARAMETER_TABLE) &&
            !strcmp(FIELD_TYPE, right.FIELD_TYPE)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        strcpy(TABLE_NAME, " " );
        strcpy(FIELD_NAME, " " );
        strcpy(PARAMETER_NAME, " " );
        strcpy(PARAMETER_TABLE, " " );
        strcpy(FIELD_TYPE, " " );
#endif
    }
} parameter_change_log_defsS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of PARAMETER_CHANGE_LOG_DEFS *************************/

struct S_PARAMETER_CHANGE_LOG_DEFS {
    char TABLE_NAME[30 + 1];
    char FIELD_NAME[40 + 1];
    char PARAMETER_NAME[30 + 1];
    char PARAMETER_TABLE[30 + 1];
    char FIELD_TYPE[10 + 1];
    char FETCH_REL[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of PARAMETER_CHANGE_LOG_DEFS ********/

struct O_PARAMETER_CHANGE_LOG_DEFS {
    char TABLE_NAME[30];
    char FIELD_NAME[40];
    char PARAMETER_NAME[30];
    char PARAMETER_TABLE[30];
    char FIELD_TYPE[10];
    char FETCH_REL[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of PARAMETER_CHANGE_LOG_DEFS *******************/

struct C_PARAMETER_CHANGE_LOG_DEFS {
    char TABLE_NAME[31];
    char FIELD_NAME[41];
    char PARAMETER_NAME[31];
    char PARAMETER_TABLE[31];
    char FIELD_TYPE[11];
    long FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of PARAMETER_CHANGE_LOG_DEFS *****************/

struct I_PARAMETER_CHANGE_LOG_DEFS {
    short TABLE_NAME;
    short FIELD_NAME;
    short PARAMETER_NAME;
    short PARAMETER_TABLE;
    short FIELD_TYPE;
    short FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of PARAMETER_CHANGE_LOG_DEFS ***************************/

#if defined (BUF_DESC)
static struct buf_desc PARAMETER_CHANGE_LOG_DEFS_BES [] = {
   { TYP_C, 30, 0 },
   { TYP_C, 40, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 10, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc PARAMETER_CHANGE_LOG_DEFS_BES [] = {
   { TYP_C, 30, 0 },
   { TYP_C, 40, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 10, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* description for datatypes of PARAMETER_CHANGE_LOG_DEFS *********************/

 #define PARAMETER_CHANGE_LOG_DEFS_S390 \
         char TABLE_NAME[31]; \
         char FIELD_NAME[41]; \
         char PARAMETER_NAME[31]; \
         char PARAMETER_TABLE[31]; \
         char FIELD_TYPE[11]; \
         long FETCH_REL;



/* Copy-Function Struct to single Data PARAMETER_CHANGE_LOG_DEFS **************/

 #define PARAMETER_CHANGE_LOG_DEFS_S390_COPY_TO_SINGLE(_x_) \
          strcpy(TABLE_NAME,_x_->TABLE_NAME);\
          strcpy(FIELD_NAME,_x_->FIELD_NAME);\
          strcpy(PARAMETER_NAME,_x_->PARAMETER_NAME);\
          strcpy(PARAMETER_TABLE,_x_->PARAMETER_TABLE);\
          strcpy(FIELD_TYPE,_x_->FIELD_TYPE);\
          FETCH_REL=_x_->FETCH_REL;\

 #define PARAMETER_CHANGE_LOG_DEFS_S390_COPY_TO_STRUCT(_x_) \
          strcpy(_x_->TABLE_NAME,TABLE_NAME);\
          strcpy(_x_->FIELD_NAME,FIELD_NAME);\
          strcpy(_x_->PARAMETER_NAME,PARAMETER_NAME);\
          strcpy(_x_->PARAMETER_TABLE,PARAMETER_TABLE);\
          strcpy(_x_->FIELD_TYPE,FIELD_TYPE);\
          _x_->FETCH_REL=FETCH_REL;\



/* FunctionNumber-Define of parameter_change_log_defs *************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of parameter_change_log_defs *********************/


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

class CPARAMETER_CHANGE_LOG_DEFS : public ppDadeVirtual {
public:
    parameter_change_log_defsS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<parameter_change_log_defsS> lst; // class list

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
                     vector< parameter_change_log_defsS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     parameter_change_log_defsS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< parameter_change_log_defsS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<parameter_change_log_defsS>::iterator
                 beginList() { return lst.begin(); }
    vector<parameter_change_log_defsS>::iterator
                 endList  () { return lst.end  (); }

    const char*  GetTable_name(ppString & t) const { t = s.TABLE_NAME; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetField_name(ppString & t) const { t = s.FIELD_NAME; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetParameter_name(ppString & t) const { t = s.PARAMETER_NAME; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetParameter_table(ppString & t) const { t = s.PARAMETER_TABLE; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetField_type(ppString & t) const { t = s.FIELD_TYPE; t.erasespace(ppString::END); return t.c_str(); }

    const parameter_change_log_defsS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetTable_name(const ppString & t) { ppGStrCopy(s.TABLE_NAME, t.c_str(), L_PARAMETER_CHANGE_LOG_DEFS_TABLE_NAME); }
    void         SetField_name(const ppString & t) { ppGStrCopy(s.FIELD_NAME, t.c_str(), L_PARAMETER_CHANGE_LOG_DEFS_FIELD_NAME); }
    void         SetParameter_name(const ppString & t) { ppGStrCopy(s.PARAMETER_NAME, t.c_str(), L_PARAMETER_CHANGE_LOG_DEFS_PARAMETER_NAME); }
    void         SetParameter_table(const ppString & t) { ppGStrCopy(s.PARAMETER_TABLE, t.c_str(), L_PARAMETER_CHANGE_LOG_DEFS_PARAMETER_TABLE); }
    void         SetField_type(const ppString & t) { ppGStrCopy(s.FIELD_TYPE, t.c_str(), L_PARAMETER_CHANGE_LOG_DEFS_FIELD_TYPE); }

    void         SetStruct(const parameter_change_log_defsS & t) { s = t; }
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
    CPARAMETER_CHANGE_LOG_DEFS() {
        ::buf_default((void *)&s, PARAMETER_CHANGE_LOG_DEFS_BES, PARAMETER_CHANGE_LOG_DEFS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CPARAMETER_CHANGE_LOG_DEFS() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, PARAMETER_CHANGE_LOG_DEFS_BES, PARAMETER_CHANGE_LOG_DEFS_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, PARAMETER_CHANGE_LOG_DEFS_BES, (int)PARAMETER_CHANGE_LOG_DEFS_ANZ, error_msg);
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
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, PARAMETER_CHANGE_LOG_DEFS_BES, (int)PARAMETER_CHANGE_LOG_DEFS_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, PARAMETER_CHANGE_LOG_DEFS_BES, (int)PARAMETER_CHANGE_LOG_DEFS_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_PARAMETER_CHANGE_LOG_DEFS & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.TABLE_NAME);
        ppGStripLast(d.FIELD_NAME);
        ppGStripLast(d.PARAMETER_NAME);
        ppGStripLast(d.PARAMETER_TABLE);
        ppGStripLast(d.FIELD_TYPE);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, PARAMETER_CHANGE_LOG_DEFS_BES, (int)PARAMETER_CHANGE_LOG_DEFS_ANZ, error_msg);
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
        CPARAMETER_CHANGE_LOG_DEFS c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, PARAMETER_CHANGE_LOG_DEFS_BES, (int)PARAMETER_CHANGE_LOG_DEFS_ANZ, error_msg);
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
/* CreateSqlStatement of PARAMETER_CHANGE_LOG_DEFS ****************************/

 #define PARAMETER_CHANGE_LOG_DEFS_CREATE(x) EXEC SQL create table x (\
         TABLE_NAME varchar(30,0) default " " not null,\
         FIELD_NAME varchar(40,0) default " " not null,\
         PARAMETER_NAME char(30) default " " not null,\
         PARAMETER_TABLE char(30) default " " not null,\
         FIELD_TYPE varchar(10,0) default " " not null) extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of PARAMETER_CHANGE_LOG_DEFS **************************/

 #define PARAMETER_CHANGE_LOG_DEFS_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_paraloggingdefinition_1 on _X_(\
              table_name,\
              field_name );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of PARAMETER_CHANGE_LOG_DEFS **************************/

 #define PARAMETER_CHANGE_LOG_DEFS_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_paraloggingdefinition_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
