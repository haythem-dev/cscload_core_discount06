#ifndef __PP_ORDERTYPE_H_
#define __PP_ORDERTYPE_H_

/******************************************************************************/
/* c:\Source\Repos\pharmos.outbound.csc_load\dev\src\loadordertypes\OrderType */
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* Length-Define of ORDERTYPE *************************************************/

#define L_ORDERTYPE_CSCORDERTYPE 2
#define L_ORDERTYPE_NAME 30

/* Length/Count-Define of ORDERTYPE *******************************************/

#define LS_ORDERTYPE_CSCORDERTYPE 2 + 1
#define LS_ORDERTYPE_NAME 30 + 1

#define ORDERTYPECSCORDERTYPE 0
#define ORDERTYPENAME 1

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define ORDERTYPE_H
#define ORDERTYPE_ANZ ( sizeof(ORDERTYPE_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ORDERTYPE *****************************************************/

#define ORDERTYPE_LISTE \
        ORDERTYPE.CSCORDERTYPE,\
        ORDERTYPE.NAME
#define ORDERTYPE_LISTE_390 \
        CSCORDERTYPE,\
        NAME
#define ORDERTYPE_PLISTE \
        "ORDERTYPE.CSCORDERTYPE,"\
        "ORDERTYPE.NAME"
#define ORDERTYPE_PELISTE \
        "CSCORDERTYPE,"\
        "NAME"
#define ORDERTYPE_UPDLISTE \
        "CSCORDERTYPE=?,"\
        "NAME=?"
/* SqlMacros-Define of ORDERTYPE **********************************************/

#define ORDERTYPE_ZEIGER(x) \
        :x->CSCORDERTYPE,\
        :x->NAME
#define ORDERTYPE_ZEIGERSEL(x) \
        :x->CSCORDERTYPE,\
        :x->NAME
#define ORDERTYPE_UPDATE(x) \
        ORDERTYPE.CSCORDERTYPE=:x->CSCORDERTYPE,\
        ORDERTYPE.NAME=:x->NAME
/* SqlMacros390-Define of ORDERTYPE *******************************************/

#define ORDERTYPE_ZEIGER_390 \
        :CSCORDERTYPE,\
        :NAME
#define ORDERTYPE_UPDATE_390 \
        CSCORDERTYPE=:CSCORDERTYPE,\
        NAME=:NAME
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of ORDERTYPE ***********************************************/

#ifndef TRANSCLASS
typedef struct N_ORDERTYPE {
    char CSCORDERTYPE[3];
    char NAME[31];
} ordertypeS;
#else /* TRANSCLASS */
typedef struct N_ORDERTYPE {
    char CSCORDERTYPE[3];
    char NAME[31];

    bool operator == (const N_ORDERTYPE& right) const {
        return (
            !strcmp(CSCORDERTYPE, right.CSCORDERTYPE) &&
            !strcmp(NAME, right.NAME)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        strcpy(CSCORDERTYPE, " " );
        strcpy(NAME, " " );
#endif
    }
} ordertypeS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ORDERTYPE *****************************************/

struct S_ORDERTYPE {
    char CSCORDERTYPE[2 + 1];
    char NAME[30 + 1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ORDERTYPE ************************/

struct O_ORDERTYPE {
    char CSCORDERTYPE[2];
    char NAME[30];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ORDERTYPE ***********************************/

struct C_ORDERTYPE {
    char CSCORDERTYPE[3];
    char NAME[31];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ORDERTYPE *********************************/

struct I_ORDERTYPE {
    short CSCORDERTYPE;
    short NAME;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ORDERTYPE *******************************************/

#if defined (BUF_DESC)
static struct buf_desc ORDERTYPE_BES [] = {
   { TYP_C, 2, 0 },
   { TYP_C, 30, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc ORDERTYPE_BES [] = {
   { TYP_C, 2, 0 },
   { TYP_C, 30, 0 },
};
#endif

/* description for datatypes of ORDERTYPE *************************************/

 #define ORDERTYPE_S390 \
         char CSCORDERTYPE[3]; \
         char NAME[31]; \



/* Copy-Function Struct to single Data ORDERTYPE ******************************/

 #define ORDERTYPE_S390_COPY_TO_SINGLE(_x_) \
          strcpy(CSCORDERTYPE,_x_->CSCORDERTYPE);\
          strcpy(NAME,_x_->NAME);\

 #define ORDERTYPE_S390_COPY_TO_STRUCT(_x_) \
          strcpy(_x_->CSCORDERTYPE,CSCORDERTYPE);\
          strcpy(_x_->NAME,NAME);\



/* FunctionNumber-Define of OrderType *****************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of OrderType *************************************/


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

class CORDERTYPE : public ppDadeVirtual {
public:
    ordertypeS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<ordertypeS> lst; // class list

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
                     vector< ordertypeS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     ordertypeS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< ordertypeS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<ordertypeS>::iterator
                 beginList() { return lst.begin(); }
    vector<ordertypeS>::iterator
                 endList  () { return lst.end  (); }

    const char*  GetCscordertype(ppString & t) const { t = s.CSCORDERTYPE; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetName(ppString & t) const { t = s.NAME; t.erasespace(ppString::END); return t.c_str(); }

    const ordertypeS &
                 GetStruct() const { return s; }
    void         SetCscordertype(const ppString & t) { ppGStrCopy(s.CSCORDERTYPE, t.c_str(), L_ORDERTYPE_CSCORDERTYPE); }
    void         SetName(const ppString & t) { ppGStrCopy(s.NAME, t.c_str(), L_ORDERTYPE_NAME); }

    void         SetStruct(const ordertypeS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CORDERTYPE() {
        ::buf_default((void *)&s, ORDERTYPE_BES, ORDERTYPE_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CORDERTYPE() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, ORDERTYPE_BES, ORDERTYPE_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, ORDERTYPE_BES, (int)ORDERTYPE_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, ORDERTYPE_BES, (int)ORDERTYPE_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_ORDERTYPE & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.CSCORDERTYPE);
        ppGStripLast(d.NAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, ORDERTYPE_BES, (int)ORDERTYPE_ANZ, error_msg);
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
/* CreateSqlStatement of ORDERTYPE ********************************************/

 #define ORDERTYPE_CREATE(x) EXEC SQL create table x (\
         CSCORDERTYPE char(2) default " " not null,\
         NAME char(30) default " " not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of ORDERTYPE ******************************************/

 #define ORDERTYPE_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_ordertype_1 on _X_(\
              cscordertype ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ORDERTYPE ******************************************/

 #define ORDERTYPE_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_ordertype_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
