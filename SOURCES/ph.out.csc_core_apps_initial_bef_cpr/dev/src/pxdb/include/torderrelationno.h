#ifndef __PP_ORDERRELATIONNO_H_
#define __PP_ORDERRELATIONNO_H_

/******************************************************************************/
/* c:\temp\OrderRelationNo ****************************************************/
/* produced by DADE 6.22.0 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of ORDERRELATIONNO *******************************************/

#define L_ORDERRELATIONNO_CSCORDERNO 11
#define L_ORDERRELATIONNO_RELATIONNOTYPE 6
#define L_ORDERRELATIONNO_RELATIONNO 11

/* Length/Count-Define of ORDERRELATIONNO *************************************/

#define LS_ORDERRELATIONNO_CSCORDERNO 10 + 1
#define LS_ORDERRELATIONNO_RELATIONNOTYPE 5 + 1
#define LS_ORDERRELATIONNO_RELATIONNO 10 + 1

#define ORDERRELATIONNOCSCORDERNO 0
#define ORDERRELATIONNORELATIONNOTYPE 1
#define ORDERRELATIONNORELATIONNO 2

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define ORDERRELATIONNO_H
#define ORDERRELATIONNO_ANZ ( sizeof(ORDERRELATIONNO_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ORDERRELATIONNO ***********************************************/

#define ORDERRELATIONNO_LISTE \
        ORDERRELATIONNO.CSCORDERNO,\
        ORDERRELATIONNO.RELATIONNOTYPE,\
        ORDERRELATIONNO.RELATIONNO
#define ORDERRELATIONNO_LISTE_390 \
        CSCORDERNO,\
        RELATIONNOTYPE,\
        RELATIONNO
#define ORDERRELATIONNO_PLISTE \
        "ORDERRELATIONNO.CSCORDERNO,"\
        "ORDERRELATIONNO.RELATIONNOTYPE,"\
        "ORDERRELATIONNO.RELATIONNO"
#define ORDERRELATIONNO_PELISTE \
        "CSCORDERNO,"\
        "RELATIONNOTYPE,"\
        "RELATIONNO"
#define ORDERRELATIONNO_UPDLISTE \
        "CSCORDERNO=?,"\
        "RELATIONNOTYPE=?,"\
        "RELATIONNO=?"
/* SqlMacros-Define of ORDERRELATIONNO ****************************************/

#define ORDERRELATIONNO_ZEIGER(x) \
        :x->CSCORDERNO,\
        :x->RELATIONNOTYPE,\
        :x->RELATIONNO
#define ORDERRELATIONNO_ZEIGERSEL(x) \
        :x->CSCORDERNO,\
        :x->RELATIONNOTYPE,\
        :x->RELATIONNO
#define ORDERRELATIONNO_UPDATE(x) \
        ORDERRELATIONNO.CSCORDERNO=:x->CSCORDERNO,\
        ORDERRELATIONNO.RELATIONNOTYPE=:x->RELATIONNOTYPE,\
        ORDERRELATIONNO.RELATIONNO=:x->RELATIONNO
/* SqlMacros390-Define of ORDERRELATIONNO *************************************/

#define ORDERRELATIONNO_ZEIGER_390 \
        :CSCORDERNO,\
        :RELATIONNOTYPE,\
        :RELATIONNO
#define ORDERRELATIONNO_UPDATE_390 \
        CSCORDERNO=:CSCORDERNO,\
        RELATIONNOTYPE=:RELATIONNOTYPE,\
        RELATIONNO=:RELATIONNO
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of ORDERRELATIONNO *****************************************/

#ifndef TRANSCLASS
typedef struct N_ORDERRELATIONNO {
    long CSCORDERNO;
    short RELATIONNOTYPE;
    long RELATIONNO;
} orderrelationnoS;
#else /* TRANSCLASS */
typedef struct N_ORDERRELATIONNO {
    long CSCORDERNO;
    short RELATIONNOTYPE;
    long RELATIONNO;

    bool operator == (const N_ORDERRELATIONNO& right) const {
        return (
            CSCORDERNO == right.CSCORDERNO &&
            RELATIONNOTYPE == right.RELATIONNOTYPE &&
            RELATIONNO == right.RELATIONNO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        CSCORDERNO = 0;
        RELATIONNOTYPE = 0;
        RELATIONNO = 0;
#endif
    }
} orderrelationnoS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ORDERRELATIONNO ***********************************/

struct S_ORDERRELATIONNO {
    char CSCORDERNO[11];
    char RELATIONNOTYPE[7];
    char RELATIONNO[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ORDERRELATIONNO ******************/

struct O_ORDERRELATIONNO {
    char CSCORDERNO[11];
    char RELATIONNOTYPE[7];
    char RELATIONNO[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ORDERRELATIONNO *****************************/

struct C_ORDERRELATIONNO {
    long CSCORDERNO;
    short RELATIONNOTYPE;
    long RELATIONNO;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ORDERRELATIONNO ***************************/

struct I_ORDERRELATIONNO {
    short CSCORDERNO;
    short RELATIONNOTYPE;
    short RELATIONNO;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ORDERRELATIONNO *************************************/

#if defined (BUF_DESC)
static struct buf_desc ORDERRELATIONNO_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc ORDERRELATIONNO_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* description for datatypes of ORDERRELATIONNO *******************************/

 #define ORDERRELATIONNO_S390 \
         long CSCORDERNO; \
         short RELATIONNOTYPE; \
         long RELATIONNO; \



/* Copy-Function Struct to single Data ORDERRELATIONNO ************************/

 #define ORDERRELATIONNO_S390_COPY_TO_SINGLE(_x_) \
         CSCORDERNO=_x_->CSCORDERNO;\
         RELATIONNOTYPE=_x_->RELATIONNOTYPE;\
         RELATIONNO=_x_->RELATIONNO;\

 #define ORDERRELATIONNO_S390_COPY_TO_STRUCT(_x_) \
          _x_->CSCORDERNO=CSCORDERNO;\
          _x_->RELATIONNOTYPE=RELATIONNOTYPE;\
          _x_->RELATIONNO=RELATIONNO;\



/* FunctionNumber-Define of OrderRelationNo ***********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of OrderRelationNo *******************************/


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

class CORDERRELATIONNO : public ppDadeVirtual {
public:
    orderrelationnoS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<orderrelationnoS> lst; // class list

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
                     vector< orderrelationnoS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     orderrelationnoS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< orderrelationnoS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<orderrelationnoS>::iterator
                 beginList() { return lst.begin(); }
    vector<orderrelationnoS>::iterator
                 endList  () { return lst.end  (); }

    long         GetCscorderno() const { return s.CSCORDERNO; }
    short        GetRelationnotype() const { return s.RELATIONNOTYPE; }
    long         GetRelationno() const { return s.RELATIONNO; }

    const orderrelationnoS &
                 GetStruct() const { return s; }
    void         SetCscorderno(long t) { s.CSCORDERNO = t; }
    void         SetRelationnotype(short t) { s.RELATIONNOTYPE = t; }
    void         SetRelationno(long t) { s.RELATIONNO = t; }

    void         SetStruct(const orderrelationnoS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CORDERRELATIONNO() {
        ::buf_default((void *)&s, ORDERRELATIONNO_BES, ORDERRELATIONNO_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CORDERRELATIONNO() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, ORDERRELATIONNO_BES, ORDERRELATIONNO_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, ORDERRELATIONNO_BES, (int)ORDERRELATIONNO_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, ORDERRELATIONNO_BES, (int)ORDERRELATIONNO_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_ORDERRELATIONNO & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, ORDERRELATIONNO_BES, (int)ORDERRELATIONNO_ANZ, error_msg);
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
/* CreateSqlStatement of ORDERRELATIONNO **************************************/

 #define ORDERRELATIONNO_CREATE(x) EXEC SQL create table x (\
         CSCORDERNO integer default 0 not null,\
         RELATIONNOTYPE smallint default 0 not null,\
         RELATIONNO integer default 0 not null) in ksc extent size 940 next size 96 lock mode row;



/* CreateIndexStatement of ORDERRELATIONNO ************************************/

 #define ORDERRELATIONNO_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_orderrelationno_1 on _X_(\
              cscorderno,\
              RelationNoType ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ORDERRELATIONNO ************************************/

 #define ORDERRELATIONNO_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_orderrelationno_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
