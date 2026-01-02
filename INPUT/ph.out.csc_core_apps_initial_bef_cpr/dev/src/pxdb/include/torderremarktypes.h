#ifndef __PP_ORDERREMARKTYPES_H_
#define __PP_ORDERREMARKTYPES_H_

/******************************************************************************/
/* d:\orderremarktypes ********************************************************/
/* produced by DADE 6.21.4 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of ORDERREMARKTYPES ******************************************/

#define L_ORDERREMARKTYPES_REMARKTYPE 6
#define L_ORDERREMARKTYPES_LEVEL 6
#define L_ORDERREMARKTYPES_REMARKNAME 50

/* Length/Count-Define of ORDERREMARKTYPES ************************************/

#define LS_ORDERREMARKTYPES_REMARKTYPE 5 + 1
#define LS_ORDERREMARKTYPES_LEVEL 5 + 1
#define LS_ORDERREMARKTYPES_REMARKNAME 50 + 1

#define ORDERREMARKTYPESREMARKTYPE 0
#define ORDERREMARKTYPESLEVEL 1
#define ORDERREMARKTYPESREMARKNAME 2

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define ORDERREMARKTYPES_H
#define ORDERREMARKTYPES_ANZ ( sizeof(ORDERREMARKTYPES_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ORDERREMARKTYPES **********************************************/

#define ORDERREMARKTYPES_LISTE \
        ORDERREMARKTYPES.REMARKTYPE,\
        ORDERREMARKTYPES.LEVEL,\
        ORDERREMARKTYPES.REMARKNAME
#define ORDERREMARKTYPES_LISTE_390 \
        REMARKTYPE,\
        LEVEL,\
        REMARKNAME
#define ORDERREMARKTYPES_PLISTE \
        "ORDERREMARKTYPES.REMARKTYPE,"\
        "ORDERREMARKTYPES.LEVEL,"\
        "ORDERREMARKTYPES.REMARKNAME"
#define ORDERREMARKTYPES_PELISTE \
        "REMARKTYPE,"\
        "LEVEL,"\
        "REMARKNAME"
#define ORDERREMARKTYPES_UPDLISTE \
        "REMARKTYPE=?,"\
        "LEVEL=?,"\
        "REMARKNAME=?"
/* SqlMacros-Define of ORDERREMARKTYPES ***************************************/

#define ORDERREMARKTYPES_ZEIGER(x) \
        :x->REMARKTYPE,\
        :x->LEVEL,\
        :x->REMARKNAME
#define ORDERREMARKTYPES_ZEIGERSEL(x) \
        :x->REMARKTYPE,\
        :x->LEVEL,\
        :x->REMARKNAME
#define ORDERREMARKTYPES_UPDATE(x) \
        ORDERREMARKTYPES.REMARKTYPE=:x->REMARKTYPE,\
        ORDERREMARKTYPES.LEVEL=:x->LEVEL,\
        ORDERREMARKTYPES.REMARKNAME=:x->REMARKNAME
/* SqlMacros390-Define of ORDERREMARKTYPES ************************************/

#define ORDERREMARKTYPES_ZEIGER_390 \
        :REMARKTYPE,\
        :LEVEL,\
        :REMARKNAME
#define ORDERREMARKTYPES_UPDATE_390 \
        REMARKTYPE=:REMARKTYPE,\
        LEVEL=:LEVEL,\
        REMARKNAME=:REMARKNAME
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of ORDERREMARKTYPES ****************************************/

#ifndef TRANSCLASS
typedef struct N_ORDERREMARKTYPES {
    short REMARKTYPE;
    short LEVEL;
    char REMARKNAME[51];
} orderremarktypesS;
#else /* TRANSCLASS */
typedef struct N_ORDERREMARKTYPES {
    short REMARKTYPE;
    short LEVEL;
    char REMARKNAME[51];

    bool operator == (const N_ORDERREMARKTYPES& right) const {
        return (
            REMARKTYPE == right.REMARKTYPE &&
            LEVEL == right.LEVEL &&
            !strcmp(REMARKNAME, right.REMARKNAME)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        REMARKTYPE = 0;
        LEVEL = 0;
        strcpy(REMARKNAME, " " );
#endif
    }
} orderremarktypesS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ORDERREMARKTYPES **********************************/

struct S_ORDERREMARKTYPES {
    char REMARKTYPE[7];
    char LEVEL[7];
    char REMARKNAME[50 + 1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ORDERREMARKTYPES *****************/

struct O_ORDERREMARKTYPES {
    char REMARKTYPE[7];
    char LEVEL[7];
    char REMARKNAME[50];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ORDERREMARKTYPES ****************************/

struct C_ORDERREMARKTYPES {
    short REMARKTYPE;
    short LEVEL;
    char REMARKNAME[51];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ORDERREMARKTYPES **************************/

struct I_ORDERREMARKTYPES {
    short REMARKTYPE;
    short LEVEL;
    short REMARKNAME;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ORDERREMARKTYPES ************************************/

#if defined (BUF_DESC)
static struct buf_desc ORDERREMARKTYPES_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 50, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc ORDERREMARKTYPES_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 50, 0 },
};
#endif

/* description for datatypes of ORDERREMARKTYPES ******************************/

 #define ORDERREMARKTYPES_S390 \
         short REMARKTYPE; \
         short LEVEL; \
         char REMARKNAME[51]; \



/* Copy-Function Struct to single Data ORDERREMARKTYPES ***********************/

 #define ORDERREMARKTYPES_S390_COPY_TO_SINGLE(_x_) \
         REMARKTYPE=_x_->REMARKTYPE;\
         LEVEL=_x_->LEVEL;\
          strcpy(REMARKNAME,_x_->REMARKNAME);\

 #define ORDERREMARKTYPES_S390_COPY_TO_STRUCT(_x_) \
          _x_->REMARKTYPE=REMARKTYPE;\
          _x_->LEVEL=LEVEL;\
          strcpy(_x_->REMARKNAME,REMARKNAME);\



/* FunctionNumber-Define of orderremarktypes **********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of orderremarktypes ******************************/


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

class CORDERREMARKTYPES : public ppDadeVirtual {
public:
    orderremarktypesS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<orderremarktypesS> lst; // class list

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
                     vector< orderremarktypesS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     orderremarktypesS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< orderremarktypesS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<orderremarktypesS>::iterator
                 beginList() { return lst.begin(); }
    vector<orderremarktypesS>::iterator
                 endList  () { return lst.end  (); }

    short        GetRemarktype() const { return s.REMARKTYPE; }
    short        GetLevel() const { return s.LEVEL; }
    const char*  GetRemarkname(ppString & t) const { t = s.REMARKNAME; t.erasespace(ppString::END); return t.c_str(); }

    const orderremarktypesS &
                 GetStruct() const { return s; }
    void         SetRemarktype(short t) { s.REMARKTYPE = t; }
    void         SetLevel(short t) { s.LEVEL = t; }
    void         SetRemarkname(const ppString & t) { ppGStrCopy(s.REMARKNAME, t.c_str(), L_ORDERREMARKTYPES_REMARKNAME); }

    void         SetStruct(const orderremarktypesS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CORDERREMARKTYPES() {
        ::buf_default((void *)&s, ORDERREMARKTYPES_BES, ORDERREMARKTYPES_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CORDERREMARKTYPES() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, ORDERREMARKTYPES_BES, ORDERREMARKTYPES_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, ORDERREMARKTYPES_BES, (int)ORDERREMARKTYPES_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, ORDERREMARKTYPES_BES, (int)ORDERREMARKTYPES_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_ORDERREMARKTYPES & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.REMARKNAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, ORDERREMARKTYPES_BES, (int)ORDERREMARKTYPES_ANZ, error_msg);
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
/* CreateSqlStatement of ORDERREMARKTYPES *************************************/

 #define ORDERREMARKTYPES_CREATE(x) EXEC SQL create table x (\
         REMARKTYPE smallint default 0 not null,\
         LEVEL smallint default 0 not null,\
         REMARKNAME varchar(50,0) default " " not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of ORDERREMARKTYPES ***********************************/

 #define ORDERREMARKTYPES_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_orderremarkts_1 on _X_(\
              remarktype,\
              level ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ORDERREMARKTYPES ***********************************/

 #define ORDERREMARKTYPES_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_orderremarkts_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
