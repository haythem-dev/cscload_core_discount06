#ifndef __PP_ORDERTYPEFLAGTYPE_H_
#define __PP_ORDERTYPEFLAGTYPE_H_

/******************************************************************************/
/**/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* Length-Define of ORDERTYPEFLAGTYPE *****************************************/

#define L_ORDERTYPEFLAGTYPE_ORDERTYPEFLAGTYPE 6
#define L_ORDERTYPEFLAGTYPE_DESCRIPTION 254
#define L_ORDERTYPEFLAGTYPE_INDEX_DKAUA 6

/* Length/Count-Define of ORDERTYPEFLAGTYPE ***********************************/

#define LS_ORDERTYPEFLAGTYPE_ORDERTYPEFLAGTYPE 5 + 1
#define LS_ORDERTYPEFLAGTYPE_DESCRIPTION 254 + 1
#define LS_ORDERTYPEFLAGTYPE_INDEX_DKAUA 5 + 1

#define ORDERTYPEFLAGTYPEORDERTYPEFLAGTYPE 0
#define ORDERTYPEFLAGTYPEDESCRIPTION 1
#define ORDERTYPEFLAGTYPEINDEX_DKAUA 2

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define ORDERTYPEFLAGTYPE_H
#define ORDERTYPEFLAGTYPE_ANZ ( sizeof(ORDERTYPEFLAGTYPE_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ORDERTYPEFLAGTYPE *********************************************/

#define ORDERTYPEFLAGTYPE_LISTE \
        ORDERTYPEFLAGTYPE.ORDERTYPEFLAGTYPE,\
        ORDERTYPEFLAGTYPE.DESCRIPTION,\
        ORDERTYPEFLAGTYPE.INDEX_DKAUA
#define ORDERTYPEFLAGTYPE_LISTE_390 \
        ORDERTYPEFLAGTYPE,\
        DESCRIPTION,\
        INDEX_DKAUA
#define ORDERTYPEFLAGTYPE_PLISTE \
        "ORDERTYPEFLAGTYPE.ORDERTYPEFLAGTYPE,"\
        "ORDERTYPEFLAGTYPE.DESCRIPTION,"\
        "ORDERTYPEFLAGTYPE.INDEX_DKAUA"
#define ORDERTYPEFLAGTYPE_PELISTE \
        "ORDERTYPEFLAGTYPE,"\
        "DESCRIPTION,"\
        "INDEX_DKAUA"
#define ORDERTYPEFLAGTYPE_UPDLISTE \
        "ORDERTYPEFLAGTYPE=?,"\
        "DESCRIPTION=?,"\
        "INDEX_DKAUA=?"
/* SqlMacros-Define of ORDERTYPEFLAGTYPE **************************************/

#define ORDERTYPEFLAGTYPE_ZEIGER(x) \
        :x->ORDERTYPEFLAGTYPE,\
        :x->DESCRIPTION,\
        :x->INDEX_DKAUA
#define ORDERTYPEFLAGTYPE_ZEIGERSEL(x) \
        :x->ORDERTYPEFLAGTYPE,\
        :x->DESCRIPTION,\
        :x->INDEX_DKAUA
#define ORDERTYPEFLAGTYPE_UPDATE(x) \
        ORDERTYPEFLAGTYPE.ORDERTYPEFLAGTYPE=:x->ORDERTYPEFLAGTYPE,\
        ORDERTYPEFLAGTYPE.DESCRIPTION=:x->DESCRIPTION,\
        ORDERTYPEFLAGTYPE.INDEX_DKAUA=:x->INDEX_DKAUA
/* SqlMacros390-Define of ORDERTYPEFLAGTYPE ***********************************/

#define ORDERTYPEFLAGTYPE_ZEIGER_390 \
        :ORDERTYPEFLAGTYPE,\
        :DESCRIPTION,\
        :INDEX_DKAUA
#define ORDERTYPEFLAGTYPE_UPDATE_390 \
        ORDERTYPEFLAGTYPE=:ORDERTYPEFLAGTYPE,\
        DESCRIPTION=:DESCRIPTION,\
        INDEX_DKAUA=:INDEX_DKAUA
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of ORDERTYPEFLAGTYPE ***************************************/

#ifndef TRANSCLASS
typedef struct N_ORDERTYPEFLAGTYPE {
    short ORDERTYPEFLAGTYPE;
    char DESCRIPTION[255];
    short INDEX_DKAUA;
} ordertypeflagtypeS;
#else /* TRANSCLASS */
typedef struct N_ORDERTYPEFLAGTYPE {
    short ORDERTYPEFLAGTYPE;
    char DESCRIPTION[255];
    short INDEX_DKAUA;

    bool operator == (const N_ORDERTYPEFLAGTYPE& right) const {
        return (
            ORDERTYPEFLAGTYPE == right.ORDERTYPEFLAGTYPE &&
            !strcmp(DESCRIPTION, right.DESCRIPTION) &&
            INDEX_DKAUA == right.INDEX_DKAUA
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        ORDERTYPEFLAGTYPE = 0;
        strcpy(DESCRIPTION, " " );
        INDEX_DKAUA = 0;
#endif
    }
} ordertypeflagtypeS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ORDERTYPEFLAGTYPE *********************************/

struct S_ORDERTYPEFLAGTYPE {
    char ORDERTYPEFLAGTYPE[7];
    char DESCRIPTION[254 + 1];
    char INDEX_DKAUA[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ORDERTYPEFLAGTYPE ****************/

struct O_ORDERTYPEFLAGTYPE {
    char ORDERTYPEFLAGTYPE[7];
    char DESCRIPTION[254];
    char INDEX_DKAUA[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ORDERTYPEFLAGTYPE ***************************/

struct C_ORDERTYPEFLAGTYPE {
    short ORDERTYPEFLAGTYPE;
    char DESCRIPTION[255];
    short INDEX_DKAUA;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ORDERTYPEFLAGTYPE *************************/

struct I_ORDERTYPEFLAGTYPE {
    short ORDERTYPEFLAGTYPE;
    short DESCRIPTION;
    short INDEX_DKAUA;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ORDERTYPEFLAGTYPE ***********************************/

#if defined (BUF_DESC)
static struct buf_desc ORDERTYPEFLAGTYPE_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 254, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc ORDERTYPEFLAGTYPE_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 254, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* description for datatypes of ORDERTYPEFLAGTYPE *****************************/

 #define ORDERTYPEFLAGTYPE_S390 \
         short ORDERTYPEFLAGTYPE; \
         char DESCRIPTION[255]; \
         short INDEX_DKAUA; \



/* Copy-Function Struct to single Data ORDERTYPEFLAGTYPE **********************/

 #define ORDERTYPEFLAGTYPE_S390_COPY_TO_SINGLE(_x_) \
         ORDERTYPEFLAGTYPE=_x_->ORDERTYPEFLAGTYPE;\
          strcpy(DESCRIPTION,_x_->DESCRIPTION);\
         INDEX_DKAUA=_x_->INDEX_DKAUA;\

 #define ORDERTYPEFLAGTYPE_S390_COPY_TO_STRUCT(_x_) \
          _x_->ORDERTYPEFLAGTYPE=ORDERTYPEFLAGTYPE;\
          strcpy(_x_->DESCRIPTION,DESCRIPTION);\
          _x_->INDEX_DKAUA=INDEX_DKAUA;\



/* FunctionNumber-Define of OrderTypeFlagType *********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of OrderTypeFlagType *****************************/


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

class CORDERTYPEFLAGTYPE : public ppDadeVirtual {
public:
    ordertypeflagtypeS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<ordertypeflagtypeS> lst; // class list

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
                     vector< ordertypeflagtypeS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     ordertypeflagtypeS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< ordertypeflagtypeS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<ordertypeflagtypeS>::iterator
                 beginList() { return lst.begin(); }
    vector<ordertypeflagtypeS>::iterator
                 endList  () { return lst.end  (); }

    short        GetOrdertypeflagtype() const { return s.ORDERTYPEFLAGTYPE; }
    const char*  GetDescription(ppString & t) const { t = s.DESCRIPTION; t.erasespace(ppString::END); return t.c_str(); }
    short        GetIndex_dkaua() const { return s.INDEX_DKAUA; }

    const ordertypeflagtypeS &
                 GetStruct() const { return s; }
    void         SetOrdertypeflagtype(short t) { s.ORDERTYPEFLAGTYPE = t; }
    void         SetDescription(const ppString & t) { ppGStrCopy(s.DESCRIPTION, t.c_str(), L_ORDERTYPEFLAGTYPE_DESCRIPTION); }
    void         SetIndex_dkaua(short t) { s.INDEX_DKAUA = t; }

    void         SetStruct(const ordertypeflagtypeS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CORDERTYPEFLAGTYPE() {
        ::buf_default((void *)&s, ORDERTYPEFLAGTYPE_BES, ORDERTYPEFLAGTYPE_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CORDERTYPEFLAGTYPE() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, ORDERTYPEFLAGTYPE_BES, ORDERTYPEFLAGTYPE_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, ORDERTYPEFLAGTYPE_BES, (int)ORDERTYPEFLAGTYPE_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, ORDERTYPEFLAGTYPE_BES, (int)ORDERTYPEFLAGTYPE_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_ORDERTYPEFLAGTYPE & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.DESCRIPTION);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, ORDERTYPEFLAGTYPE_BES, (int)ORDERTYPEFLAGTYPE_ANZ, error_msg);
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
/* CreateSqlStatement of ORDERTYPEFLAGTYPE ************************************/

 #define ORDERTYPEFLAGTYPE_CREATE(x) EXEC SQL create table x (\
         ORDERTYPEFLAGTYPE smallint default 0 not null,\
         DESCRIPTION varchar(254,0) default " " not null,\
         INDEX_DKAUA smallint default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of ORDERTYPEFLAGTYPE **********************************/

 #define ORDERTYPEFLAGTYPE_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_ordertypeflagtype on _X_(\
              ordertypeflagtype ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ORDERTYPEFLAGTYPE **********************************/

 #define ORDERTYPEFLAGTYPE_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_ordertypeflagtype;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
