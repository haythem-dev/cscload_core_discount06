#ifndef __PP_ORDERRELATIONNOTYPES_H_
#define __PP_ORDERRELATIONNOTYPES_H_

/******************************************************************************/
/* c:\temp\OrderRelationNoTypes ***********************************************/
/* produced by DADE 6.22.0 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of ORDERRELATIONNOTYPES **************************************/

#define L_ORDERRELATIONNOTYPES_RELATIONNOTYPE 6
#define L_ORDERRELATIONNOTYPES_RELATIONDESCRIPTION 254

/* Length/Count-Define of ORDERRELATIONNOTYPES ********************************/

#define LS_ORDERRELATIONNOTYPES_RELATIONNOTYPE 5 + 1
#define LS_ORDERRELATIONNOTYPES_RELATIONDESCRIPTION 254 + 1

#define ORDERRELATIONNOTYPESRELATIONNOTYPE 0
#define ORDERRELATIONNOTYPESRELATIONDESCRIPTION 1

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define ORDERRELATIONNOTYPES_H
#define ORDERRELATIONNOTYPES_ANZ ( sizeof(ORDERRELATIONNOTYPES_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ORDERRELATIONNOTYPES ******************************************/

#define ORDERRELATIONNOTYPES_LISTE \
        ORDERRELATIONNOTYPES.RELATIONNOTYPE,\
        ORDERRELATIONNOTYPES.RELATIONDESCRIPTION
#define ORDERRELATIONNOTYPES_LISTE_390 \
        RELATIONNOTYPE,\
        RELATIONDESCRIPTION
#define ORDERRELATIONNOTYPES_PLISTE \
        "ORDERRELATIONNOTYPES.RELATIONNOTYPE,"\
        "ORDERRELATIONNOTYPES.RELATIONDESCRIPTION"
#define ORDERRELATIONNOTYPES_PELISTE \
        "RELATIONNOTYPE,"\
        "RELATIONDESCRIPTION"
#define ORDERRELATIONNOTYPES_UPDLISTE \
        "RELATIONNOTYPE=?,"\
        "RELATIONDESCRIPTION=?"
/* SqlMacros-Define of ORDERRELATIONNOTYPES ***********************************/

#define ORDERRELATIONNOTYPES_ZEIGER(x) \
        :x->RELATIONNOTYPE,\
        :x->RELATIONDESCRIPTION
#define ORDERRELATIONNOTYPES_ZEIGERSEL(x) \
        :x->RELATIONNOTYPE,\
        :x->RELATIONDESCRIPTION
#define ORDERRELATIONNOTYPES_UPDATE(x) \
        ORDERRELATIONNOTYPES.RELATIONNOTYPE=:x->RELATIONNOTYPE,\
        ORDERRELATIONNOTYPES.RELATIONDESCRIPTION=:x->RELATIONDESCRIPTION
/* SqlMacros390-Define of ORDERRELATIONNOTYPES ********************************/

#define ORDERRELATIONNOTYPES_ZEIGER_390 \
        :RELATIONNOTYPE,\
        :RELATIONDESCRIPTION
#define ORDERRELATIONNOTYPES_UPDATE_390 \
        RELATIONNOTYPE=:RELATIONNOTYPE,\
        RELATIONDESCRIPTION=:RELATIONDESCRIPTION
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of ORDERRELATIONNOTYPES ************************************/

#ifndef TRANSCLASS
typedef struct N_ORDERRELATIONNOTYPES {
    short RELATIONNOTYPE;
    char RELATIONDESCRIPTION[255];
} orderrelationnotypesS;
#else /* TRANSCLASS */
typedef struct N_ORDERRELATIONNOTYPES {
    short RELATIONNOTYPE;
    char RELATIONDESCRIPTION[255];

    bool operator == (const N_ORDERRELATIONNOTYPES& right) const {
        return (
            RELATIONNOTYPE == right.RELATIONNOTYPE &&
            !strcmp(RELATIONDESCRIPTION, right.RELATIONDESCRIPTION)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        RELATIONNOTYPE = 0;
        strcpy(RELATIONDESCRIPTION, " " );
#endif
    }
} orderrelationnotypesS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ORDERRELATIONNOTYPES ******************************/

struct S_ORDERRELATIONNOTYPES {
    char RELATIONNOTYPE[7];
    char RELATIONDESCRIPTION[254 + 1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ORDERRELATIONNOTYPES *************/

struct O_ORDERRELATIONNOTYPES {
    char RELATIONNOTYPE[7];
    char RELATIONDESCRIPTION[254];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ORDERRELATIONNOTYPES ************************/

struct C_ORDERRELATIONNOTYPES {
    short RELATIONNOTYPE;
    char RELATIONDESCRIPTION[255];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ORDERRELATIONNOTYPES **********************/

struct I_ORDERRELATIONNOTYPES {
    short RELATIONNOTYPE;
    short RELATIONDESCRIPTION;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ORDERRELATIONNOTYPES ********************************/

#if defined (BUF_DESC)
static struct buf_desc ORDERRELATIONNOTYPES_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 254, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc ORDERRELATIONNOTYPES_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 254, 0 },
};
#endif

/* description for datatypes of ORDERRELATIONNOTYPES **************************/

 #define ORDERRELATIONNOTYPES_S390 \
         short RELATIONNOTYPE; \
         char RELATIONDESCRIPTION[255]; \



/* Copy-Function Struct to single Data ORDERRELATIONNOTYPES *******************/

 #define ORDERRELATIONNOTYPES_S390_COPY_TO_SINGLE(_x_) \
         RELATIONNOTYPE=_x_->RELATIONNOTYPE;\
          strcpy(RELATIONDESCRIPTION,_x_->RELATIONDESCRIPTION);\

 #define ORDERRELATIONNOTYPES_S390_COPY_TO_STRUCT(_x_) \
          _x_->RELATIONNOTYPE=RELATIONNOTYPE;\
          strcpy(_x_->RELATIONDESCRIPTION,RELATIONDESCRIPTION);\



/* FunctionNumber-Define of OrderRelationNoTypes ******************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of OrderRelationNoTypes **************************/


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

class CORDERRELATIONNOTYPES : public ppDadeVirtual {
public:
    orderrelationnotypesS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<orderrelationnotypesS> lst; // class list

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
                     vector< orderrelationnotypesS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     orderrelationnotypesS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< orderrelationnotypesS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<orderrelationnotypesS>::iterator
                 beginList() { return lst.begin(); }
    vector<orderrelationnotypesS>::iterator
                 endList  () { return lst.end  (); }

    short        GetRelationnotype() const { return s.RELATIONNOTYPE; }
    const char*  GetRelationdescription(ppString & t) const { t = s.RELATIONDESCRIPTION; t.erasespace(ppString::END); return t.c_str(); }

    const orderrelationnotypesS &
                 GetStruct() const { return s; }
    void         SetRelationnotype(short t) { s.RELATIONNOTYPE = t; }
    void         SetRelationdescription(const ppString & t) { ppGStrCopy(s.RELATIONDESCRIPTION, t.c_str(), L_ORDERRELATIONNOTYPES_RELATIONDESCRIPTION); }

    void         SetStruct(const orderrelationnotypesS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CORDERRELATIONNOTYPES() {
        ::buf_default((void *)&s, ORDERRELATIONNOTYPES_BES, ORDERRELATIONNOTYPES_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CORDERRELATIONNOTYPES() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, ORDERRELATIONNOTYPES_BES, ORDERRELATIONNOTYPES_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, ORDERRELATIONNOTYPES_BES, (int)ORDERRELATIONNOTYPES_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, ORDERRELATIONNOTYPES_BES, (int)ORDERRELATIONNOTYPES_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_ORDERRELATIONNOTYPES & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.RELATIONDESCRIPTION);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, ORDERRELATIONNOTYPES_BES, (int)ORDERRELATIONNOTYPES_ANZ, error_msg);
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
/* CreateSqlStatement of ORDERRELATIONNOTYPES *********************************/

 #define ORDERRELATIONNOTYPES_CREATE(x) EXEC SQL create table x (\
         RELATIONNOTYPE smallint default 0 not null,\
         RELATIONDESCRIPTION varchar(254,0) default " " not null) in ics extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of ORDERRELATIONNOTYPES *******************************/

 #define ORDERRELATIONNOTYPES_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_orderrelationnotypes_1 on _X_(\
              RelationNoType ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ORDERRELATIONNOTYPES *******************************/

 #define ORDERRELATIONNOTYPES_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_orderrelationnotypes_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
