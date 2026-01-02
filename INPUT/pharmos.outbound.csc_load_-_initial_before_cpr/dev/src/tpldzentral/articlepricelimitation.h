#ifndef __PP_ARTICLEPRICELIMITATION_H_
#define __PP_ARTICLEPRICELIMITATION_H_

/******************************************************************************/
/* c:\prri\Headerfiles\articlepricelimitation *********************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of ARTICLEPRICELIMITATION ************************************/

#define L_ARTICLEPRICELIMITATION_ARTICLENO 11
#define L_ARTICLEPRICELIMITATION_MAXWHOLESALEPRICE 9
#define N_ARTICLEPRICELIMITATION_MAXWHOLESALEPRICE 2
#define L_ARTICLEPRICELIMITATION_REFERENCEPRICE 9
#define N_ARTICLEPRICELIMITATION_REFERENCEPRICE 2
#define L_ARTICLEPRICELIMITATION_NHIFPRICE 9
#define N_ARTICLEPRICELIMITATION_NHIFPRICE 2

/* Length/Count-Define of ARTICLEPRICELIMITATION ******************************/

#define LS_ARTICLEPRICELIMITATION_ARTICLENO 10 + 1
#define LS_ARTICLEPRICELIMITATION_MAXWHOLESALEPRICE 9 + 2
#define LS_ARTICLEPRICELIMITATION_REFERENCEPRICE 9 + 2
#define LS_ARTICLEPRICELIMITATION_NHIFPRICE 9 + 2

#define ARTICLEPRICELIMITATIONARTICLENO 0
#define ARTICLEPRICELIMITATIONMAXWHOLESALEPRICE 1
#define ARTICLEPRICELIMITATIONREFERENCEPRICE 2
#define ARTICLEPRICELIMITATIONNHIFPRICE 3

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define ARTICLEPRICELIMITATION_H
#define ARTICLEPRICELIMITATION_ANZ ( sizeof(ARTICLEPRICELIMITATION_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ARTICLEPRICELIMITATION ****************************************/

#define ARTICLEPRICELIMITATION_LISTE \
        ARTICLEPRICELIMITATION.ARTICLENO,\
        ARTICLEPRICELIMITATION.MAXWHOLESALEPRICE,\
        ARTICLEPRICELIMITATION.REFERENCEPRICE,\
        ARTICLEPRICELIMITATION.NHIFPRICE
#define ARTICLEPRICELIMITATION_LISTE_390 \
        ARTICLENO,\
        MAXWHOLESALEPRICE,\
        REFERENCEPRICE,\
        NHIFPRICE
#define ARTICLEPRICELIMITATION_PLISTE \
        "ARTICLEPRICELIMITATION.ARTICLENO,"\
        "ARTICLEPRICELIMITATION.MAXWHOLESALEPRICE,"\
        "ARTICLEPRICELIMITATION.REFERENCEPRICE,"\
        "ARTICLEPRICELIMITATION.NHIFPRICE"
#define ARTICLEPRICELIMITATION_PELISTE \
        "ARTICLENO,"\
        "MAXWHOLESALEPRICE,"\
        "REFERENCEPRICE,"\
        "NHIFPRICE"
#define ARTICLEPRICELIMITATION_UPDLISTE \
        "ARTICLENO=?,"\
        "MAXWHOLESALEPRICE=?,"\
        "REFERENCEPRICE=?,"\
        "NHIFPRICE=?"
/* SqlMacros-Define of ARTICLEPRICELIMITATION *********************************/

#define ARTICLEPRICELIMITATION_ZEIGER(x) \
        :x->ARTICLENO,\
        :x->MAXWHOLESALEPRICE,\
        :x->REFERENCEPRICE,\
        :x->NHIFPRICE
#define ARTICLEPRICELIMITATION_ZEIGERSEL(x) \
        :x->ARTICLENO,\
        :x->MAXWHOLESALEPRICE,\
        :x->REFERENCEPRICE,\
        :x->NHIFPRICE
#define ARTICLEPRICELIMITATION_UPDATE(x) \
        ARTICLEPRICELIMITATION.ARTICLENO=:x->ARTICLENO,\
        ARTICLEPRICELIMITATION.MAXWHOLESALEPRICE=:x->MAXWHOLESALEPRICE,\
        ARTICLEPRICELIMITATION.REFERENCEPRICE=:x->REFERENCEPRICE,\
        ARTICLEPRICELIMITATION.NHIFPRICE=:x->NHIFPRICE
/* SqlMacros390-Define of ARTICLEPRICELIMITATION ******************************/

#define ARTICLEPRICELIMITATION_ZEIGER_390 \
        :ARTICLENO,\
        :MAXWHOLESALEPRICE,\
        :REFERENCEPRICE,\
        :NHIFPRICE
#define ARTICLEPRICELIMITATION_UPDATE_390 \
        ARTICLENO=:ARTICLENO,\
        MAXWHOLESALEPRICE=:MAXWHOLESALEPRICE,\
        REFERENCEPRICE=:REFERENCEPRICE,\
        NHIFPRICE=:NHIFPRICE
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of ARTICLEPRICELIMITATION **********************************/

#ifndef TRANSCLASS
typedef struct N_ARTICLEPRICELIMITATION {
    long ARTICLENO;
    double MAXWHOLESALEPRICE;
    double REFERENCEPRICE;
    double NHIFPRICE;
} articlepricelimitationS;
#else /* TRANSCLASS */
typedef struct N_ARTICLEPRICELIMITATION {
    long ARTICLENO;
    double MAXWHOLESALEPRICE;
    double REFERENCEPRICE;
    double NHIFPRICE;

    bool operator == (const N_ARTICLEPRICELIMITATION& right) const {
        return (
            ARTICLENO == right.ARTICLENO &&
            MAXWHOLESALEPRICE == right.MAXWHOLESALEPRICE &&
            REFERENCEPRICE == right.REFERENCEPRICE &&
            NHIFPRICE == right.NHIFPRICE
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        ARTICLENO = 0;
        MAXWHOLESALEPRICE = 0;
        REFERENCEPRICE = 0;
        NHIFPRICE = 0;
#endif
    }
} articlepricelimitationS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ARTICLEPRICELIMITATION ****************************/

struct S_ARTICLEPRICELIMITATION {
    char ARTICLENO[11];
    char MAXWHOLESALEPRICE[9 + 2];
    char REFERENCEPRICE[9 + 2];
    char NHIFPRICE[9 + 2];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ARTICLEPRICELIMITATION ***********/

struct O_ARTICLEPRICELIMITATION {
    char ARTICLENO[11];
    char MAXWHOLESALEPRICE[9];
    char REFERENCEPRICE[9];
    char NHIFPRICE[9];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ARTICLEPRICELIMITATION **********************/

struct C_ARTICLEPRICELIMITATION {
    long ARTICLENO;
    double MAXWHOLESALEPRICE;
    double REFERENCEPRICE;
    double NHIFPRICE;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ARTICLEPRICELIMITATION ********************/

struct I_ARTICLEPRICELIMITATION {
    short ARTICLENO;
    short MAXWHOLESALEPRICE;
    short REFERENCEPRICE;
    short NHIFPRICE;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ARTICLEPRICELIMITATION ******************************/

#if defined (BUF_DESC)
static struct buf_desc ARTICLEPRICELIMITATION_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc ARTICLEPRICELIMITATION_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
};
#endif

/* description for datatypes of ARTICLEPRICELIMITATION ************************/

 #define ARTICLEPRICELIMITATION_S390 \
         long ARTICLENO; \
         double MAXWHOLESALEPRICE; \
         double REFERENCEPRICE; \
         double NHIFPRICE; \



/* Copy-Function Struct to single Data ARTICLEPRICELIMITATION *****************/

 #define ARTICLEPRICELIMITATION_S390_COPY_TO_SINGLE(_x_) \
         ARTICLENO=_x_->ARTICLENO;\
         MAXWHOLESALEPRICE=_x_->MAXWHOLESALEPRICE;\
         REFERENCEPRICE=_x_->REFERENCEPRICE;\
         NHIFPRICE=_x_->NHIFPRICE;\

 #define ARTICLEPRICELIMITATION_S390_COPY_TO_STRUCT(_x_) \
          _x_->ARTICLENO=ARTICLENO;\
          _x_->MAXWHOLESALEPRICE=MAXWHOLESALEPRICE;\
          _x_->REFERENCEPRICE=REFERENCEPRICE;\
          _x_->NHIFPRICE=NHIFPRICE;\



/* FunctionNumber-Define of articlepricelimitation ****************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of articlepricelimitation ************************/


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

class CARTICLEPRICELIMITATION : public ppDadeVirtual {
public:
    articlepricelimitationS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<articlepricelimitationS> lst; // class list

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
                     vector< articlepricelimitationS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     articlepricelimitationS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< articlepricelimitationS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<articlepricelimitationS>::iterator
                 beginList() { return lst.begin(); }
    vector<articlepricelimitationS>::iterator
                 endList  () { return lst.end  (); }

    long         GetArticleno() const { return s.ARTICLENO; }
    double       GetMaxwholesaleprice() const { return s.MAXWHOLESALEPRICE; }
    double       GetReferenceprice() const { return s.REFERENCEPRICE; }
    double       GetNhifprice() const { return s.NHIFPRICE; }

    const articlepricelimitationS &
                 GetStruct() const { return s; }
    void         SetArticleno(long t) { s.ARTICLENO = t; }
    void         SetMaxwholesaleprice(double t) { s.MAXWHOLESALEPRICE = t; }
    void         SetReferenceprice(double t) { s.REFERENCEPRICE = t; }
    void         SetNhifprice(double t) { s.NHIFPRICE = t; }

    void         SetStruct(const articlepricelimitationS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CARTICLEPRICELIMITATION() {
        ::buf_default((void *)&s, ARTICLEPRICELIMITATION_BES, ARTICLEPRICELIMITATION_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CARTICLEPRICELIMITATION() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, ARTICLEPRICELIMITATION_BES, ARTICLEPRICELIMITATION_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, ARTICLEPRICELIMITATION_BES, (int)ARTICLEPRICELIMITATION_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, ARTICLEPRICELIMITATION_BES, (int)ARTICLEPRICELIMITATION_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_ARTICLEPRICELIMITATION & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, ARTICLEPRICELIMITATION_BES, (int)ARTICLEPRICELIMITATION_ANZ, error_msg);
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
/* CreateSqlStatement of ARTICLEPRICELIMITATION *******************************/

 #define ARTICLEPRICELIMITATION_CREATE(x) EXEC SQL create table x (\
         ARTICLENO integer default 0 not null,\
         MAXWHOLESALEPRICE decimal(9,2) default 0 not null,\
         REFERENCEPRICE decimal(9,2) default 0 not null,\
         NHIFPRICE decimal(9,2) default 0 not null) in ksc extent size 392 next size 40 lock mode row;



/* CreateIndexStatement of ARTICLEPRICELIMITATION *****************************/

 #define ARTICLEPRICELIMITATION_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_artpricelimit_1 on _X_(\
              ArticleNo ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ARTICLEPRICELIMITATION *****************************/

 #define ARTICLEPRICELIMITATION_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_artpricelimit_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
