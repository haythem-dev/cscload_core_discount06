#ifndef __PP_ORDERTYPEFLAGS_H_
#define __PP_ORDERTYPEFLAGS_H_

/******************************************************************************/
/**/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* Length-Define of ORDERTYPEFLAGS ********************************************/

#define L_ORDERTYPEFLAGS_CSCORDERTYPE 2
#define L_ORDERTYPEFLAGS_ORDERTYPEFLAGTYPE 6
#define L_ORDERTYPEFLAGS_ORDERTYPEFLAG 6

/* Length/Count-Define of ORDERTYPEFLAGS **************************************/

#define LS_ORDERTYPEFLAGS_CSCORDERTYPE 2 + 1
#define LS_ORDERTYPEFLAGS_ORDERTYPEFLAGTYPE 5 + 1
#define LS_ORDERTYPEFLAGS_ORDERTYPEFLAG 5 + 1

#define ORDERTYPEFLAGSCSCORDERTYPE 0
#define ORDERTYPEFLAGSORDERTYPEFLAGTYPE 1
#define ORDERTYPEFLAGSORDERTYPEFLAG 2

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define ORDERTYPEFLAGS_H
#define ORDERTYPEFLAGS_ANZ ( sizeof(ORDERTYPEFLAGS_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ORDERTYPEFLAGS ************************************************/

#define ORDERTYPEFLAGS_LISTE \
        ORDERTYPEFLAGS.CSCORDERTYPE,\
        ORDERTYPEFLAGS.ORDERTYPEFLAGTYPE,\
        ORDERTYPEFLAGS.ORDERTYPEFLAG
#define ORDERTYPEFLAGS_LISTE_390 \
        CSCORDERTYPE,\
        ORDERTYPEFLAGTYPE,\
        ORDERTYPEFLAG
#define ORDERTYPEFLAGS_PLISTE \
        "ORDERTYPEFLAGS.CSCORDERTYPE,"\
        "ORDERTYPEFLAGS.ORDERTYPEFLAGTYPE,"\
        "ORDERTYPEFLAGS.ORDERTYPEFLAG"
#define ORDERTYPEFLAGS_PELISTE \
        "CSCORDERTYPE,"\
        "ORDERTYPEFLAGTYPE,"\
        "ORDERTYPEFLAG"
#define ORDERTYPEFLAGS_UPDLISTE \
        "CSCORDERTYPE=?,"\
        "ORDERTYPEFLAGTYPE=?,"\
        "ORDERTYPEFLAG=?"
/* SqlMacros-Define of ORDERTYPEFLAGS *****************************************/

#define ORDERTYPEFLAGS_ZEIGER(x) \
        :x->CSCORDERTYPE,\
        :x->ORDERTYPEFLAGTYPE,\
        :x->ORDERTYPEFLAG
#define ORDERTYPEFLAGS_ZEIGERSEL(x) \
        :x->CSCORDERTYPE,\
        :x->ORDERTYPEFLAGTYPE,\
        :x->ORDERTYPEFLAG
#define ORDERTYPEFLAGS_UPDATE(x) \
        ORDERTYPEFLAGS.CSCORDERTYPE=:x->CSCORDERTYPE,\
        ORDERTYPEFLAGS.ORDERTYPEFLAGTYPE=:x->ORDERTYPEFLAGTYPE,\
        ORDERTYPEFLAGS.ORDERTYPEFLAG=:x->ORDERTYPEFLAG
/* SqlMacros390-Define of ORDERTYPEFLAGS **************************************/

#define ORDERTYPEFLAGS_ZEIGER_390 \
        :CSCORDERTYPE,\
        :ORDERTYPEFLAGTYPE,\
        :ORDERTYPEFLAG
#define ORDERTYPEFLAGS_UPDATE_390 \
        CSCORDERTYPE=:CSCORDERTYPE,\
        ORDERTYPEFLAGTYPE=:ORDERTYPEFLAGTYPE,\
        ORDERTYPEFLAG=:ORDERTYPEFLAG
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of ORDERTYPEFLAGS ******************************************/

#ifndef TRANSCLASS
typedef struct N_ORDERTYPEFLAGS {
    char CSCORDERTYPE[3];
    short ORDERTYPEFLAGTYPE;
    short ORDERTYPEFLAG;
} ordertypeflagsS;
#else /* TRANSCLASS */
typedef struct N_ORDERTYPEFLAGS {
    char CSCORDERTYPE[3];
    short ORDERTYPEFLAGTYPE;
    short ORDERTYPEFLAG;

    bool operator == (const N_ORDERTYPEFLAGS& right) const {
        return (
            !strcmp(CSCORDERTYPE, right.CSCORDERTYPE) &&
            ORDERTYPEFLAGTYPE == right.ORDERTYPEFLAGTYPE &&
            ORDERTYPEFLAG == right.ORDERTYPEFLAG
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        strcpy(CSCORDERTYPE, " " );
        ORDERTYPEFLAGTYPE = 0;
        ORDERTYPEFLAG = 0;
#endif
    }
} ordertypeflagsS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ORDERTYPEFLAGS ************************************/

struct S_ORDERTYPEFLAGS {
    char CSCORDERTYPE[2 + 1];
    char ORDERTYPEFLAGTYPE[7];
    char ORDERTYPEFLAG[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ORDERTYPEFLAGS *******************/

struct O_ORDERTYPEFLAGS {
    char CSCORDERTYPE[2];
    char ORDERTYPEFLAGTYPE[7];
    char ORDERTYPEFLAG[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ORDERTYPEFLAGS ******************************/

struct C_ORDERTYPEFLAGS {
    char CSCORDERTYPE[3];
    short ORDERTYPEFLAGTYPE;
    short ORDERTYPEFLAG;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ORDERTYPEFLAGS ****************************/

struct I_ORDERTYPEFLAGS {
    short CSCORDERTYPE;
    short ORDERTYPEFLAGTYPE;
    short ORDERTYPEFLAG;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ORDERTYPEFLAGS **************************************/

#if defined (BUF_DESC)
static struct buf_desc ORDERTYPEFLAGS_BES [] = {
   { TYP_C, 2, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc ORDERTYPEFLAGS_BES [] = {
   { TYP_C, 2, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* description for datatypes of ORDERTYPEFLAGS ********************************/

 #define ORDERTYPEFLAGS_S390 \
         char CSCORDERTYPE[3]; \
         short ORDERTYPEFLAGTYPE; \
         short ORDERTYPEFLAG; \



/* Copy-Function Struct to single Data ORDERTYPEFLAGS *************************/

 #define ORDERTYPEFLAGS_S390_COPY_TO_SINGLE(_x_) \
          strcpy(CSCORDERTYPE,_x_->CSCORDERTYPE);\
         ORDERTYPEFLAGTYPE=_x_->ORDERTYPEFLAGTYPE;\
         ORDERTYPEFLAG=_x_->ORDERTYPEFLAG;\

 #define ORDERTYPEFLAGS_S390_COPY_TO_STRUCT(_x_) \
          strcpy(_x_->CSCORDERTYPE,CSCORDERTYPE);\
          _x_->ORDERTYPEFLAGTYPE=ORDERTYPEFLAGTYPE;\
          _x_->ORDERTYPEFLAG=ORDERTYPEFLAG;\



/* FunctionNumber-Define of OrderTypeFlags ************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of OrderTypeFlags ********************************/


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

class CORDERTYPEFLAGS : public ppDadeVirtual {
public:
    ordertypeflagsS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<ordertypeflagsS> lst; // class list

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
                     vector< ordertypeflagsS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     ordertypeflagsS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< ordertypeflagsS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<ordertypeflagsS>::iterator
                 beginList() { return lst.begin(); }
    vector<ordertypeflagsS>::iterator
                 endList  () { return lst.end  (); }

    const char*  GetCscordertype(ppString & t) const { t = s.CSCORDERTYPE; t.erasespace(ppString::END); return t.c_str(); }
    short        GetOrdertypeflagtype() const { return s.ORDERTYPEFLAGTYPE; }
    short        GetOrdertypeflag() const { return s.ORDERTYPEFLAG; }

    const ordertypeflagsS &
                 GetStruct() const { return s; }
    void         SetCscordertype(const ppString & t) { ppGStrCopy(s.CSCORDERTYPE, t.c_str(), L_ORDERTYPEFLAGS_CSCORDERTYPE); }
    void         SetOrdertypeflagtype(short t) { s.ORDERTYPEFLAGTYPE = t; }
    void         SetOrdertypeflag(short t) { s.ORDERTYPEFLAG = t; }

    void         SetStruct(const ordertypeflagsS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CORDERTYPEFLAGS() {
        ::buf_default((void *)&s, ORDERTYPEFLAGS_BES, ORDERTYPEFLAGS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CORDERTYPEFLAGS() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, ORDERTYPEFLAGS_BES, ORDERTYPEFLAGS_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, ORDERTYPEFLAGS_BES, (int)ORDERTYPEFLAGS_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, ORDERTYPEFLAGS_BES, (int)ORDERTYPEFLAGS_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_ORDERTYPEFLAGS & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.CSCORDERTYPE);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, ORDERTYPEFLAGS_BES, (int)ORDERTYPEFLAGS_ANZ, error_msg);
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
/* CreateSqlStatement of ORDERTYPEFLAGS ***************************************/

 #define ORDERTYPEFLAGS_CREATE(x) EXEC SQL create table x (\
         CSCORDERTYPE char(2) default " " not null,\
         ORDERTYPEFLAGTYPE smallint default 0 not null,\
         ORDERTYPEFLAG smallint default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of ORDERTYPEFLAGS *************************************/

 #define ORDERTYPEFLAGS_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index o_ordertypeflags_1 on _X_(\
              cscordertype,\
              ordertypeflagtype ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ORDERTYPEFLAGS *************************************/

 #define ORDERTYPEFLAGS_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index o_ordertypeflags_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
