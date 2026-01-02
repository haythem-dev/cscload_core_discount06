#ifndef __PP_RANGELIST_H_
#define __PP_RANGELIST_H_

/******************************************************************************/
/* c:RangeList ****************************************************************/
/* produced by DADE 6.22.1 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of RANGELIST *************************************************/

#define L_RANGELIST_ARTICLENO 11
#define L_RANGELIST_DISCOUNTGRPNO 11
#define L_RANGELIST_BASEQTY 11
#define L_RANGELIST_DISCOUNTQTY 6
#define L_RANGELIST_DISCOUNTVALUEPCT 5
#define N_RANGELIST_DISCOUNTVALUEPCT 2
#define L_RANGELIST_DISCOUNTARTICLE 11
#define L_RANGELIST_BASE_VALUE 10
#define N_RANGELIST_BASE_VALUE 2
#define L_RANGELIST_ANZAHL 11
#define L_RANGELIST_ORDVALNET 11
#define N_RANGELIST_ORDVALNET 2

/* Length/Count-Define of RANGELIST *******************************************/

#define LS_RANGELIST_ARTICLENO 10 + 1
#define LS_RANGELIST_DISCOUNTGRPNO 10 + 1
#define LS_RANGELIST_BASEQTY 10 + 1
#define LS_RANGELIST_DISCOUNTQTY 5 + 1
#define LS_RANGELIST_DISCOUNTVALUEPCT 5 + 2
#define LS_RANGELIST_DISCOUNTARTICLE 10 + 1
#define LS_RANGELIST_BASE_VALUE 10 + 2
#define LS_RANGELIST_ANZAHL 10 + 1
#define LS_RANGELIST_ORDVALNET 11 + 2

#define RANGELISTARTICLENO 0
#define RANGELISTDISCOUNTGRPNO 1
#define RANGELISTBASEQTY 2
#define RANGELISTDISCOUNTQTY 3
#define RANGELISTDISCOUNTVALUEPCT 4
#define RANGELISTDISCOUNTARTICLE 5
#define RANGELISTBASE_VALUE 6
#define RANGELISTANZAHL 7
#define RANGELISTORDVALNET 8

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define RANGELIST_H
#define RANGELIST_ANZ ( sizeof(RANGELIST_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of RANGELIST *****************************************************/

#define RANGELIST_LISTE \
        DISCOUNT.ARTICLENO,\
        DISCOUNT.DISCOUNTGRPNO,\
        DISCOUNT.BASEQTY,\
        DISCOUNT.DISCOUNTQTY,\
        DISCOUNT.DISCOUNTVALUEPCT,\
        DISCOUNT.DISCOUNTARTICLE,\
        DISCOUNT.BASE_VALUE,\
        AADUMMY.ANZAHL,\
        AADUMMY.ORDVALNET
#define RANGELIST_LISTE_390 \
        ARTICLENO,\
        DISCOUNTGRPNO,\
        BASEQTY,\
        DISCOUNTQTY,\
        DISCOUNTVALUEPCT,\
        DISCOUNTARTICLE,\
        BASE_VALUE,\
        ANZAHL,\
        ORDVALNET
#define RANGELIST_PLISTE \
        "DISCOUNT.ARTICLENO,"\
        "DISCOUNT.DISCOUNTGRPNO,"\
        "DISCOUNT.BASEQTY,"\
        "DISCOUNT.DISCOUNTQTY,"\
        "DISCOUNT.DISCOUNTVALUEPCT,"\
        "DISCOUNT.DISCOUNTARTICLE,"\
        "DISCOUNT.BASE_VALUE,"\
        "AADUMMY.ANZAHL,"\
        "AADUMMY.ORDVALNET"
#define RANGELIST_PELISTE \
        "ARTICLENO,"\
        "DISCOUNTGRPNO,"\
        "BASEQTY,"\
        "DISCOUNTQTY,"\
        "DISCOUNTVALUEPCT,"\
        "DISCOUNTARTICLE,"\
        "BASE_VALUE,"\
        "ANZAHL,"\
        "ORDVALNET"
#define RANGELIST_UPDLISTE \
        "ARTICLENO=?,"\
        "DISCOUNTGRPNO=?,"\
        "BASEQTY=?,"\
        "DISCOUNTQTY=?,"\
        "DISCOUNTVALUEPCT=?,"\
        "DISCOUNTARTICLE=?,"\
        "BASE_VALUE=?,"\
        "ANZAHL=?,"\
        "ORDVALNET=?"
/* SqlMacros-Define of RANGELIST **********************************************/

#define RANGELIST_ZEIGER(x) \
        :x->ARTICLENO,\
        :x->DISCOUNTGRPNO,\
        :x->BASEQTY,\
        :x->DISCOUNTQTY,\
        :x->DISCOUNTVALUEPCT,\
        :x->DISCOUNTARTICLE,\
        :x->BASE_VALUE,\
        :x->ANZAHL,\
        :x->ORDVALNET
#define RANGELIST_ZEIGERSEL(x) \
        :x->ARTICLENO,\
        :x->DISCOUNTGRPNO,\
        :x->BASEQTY,\
        :x->DISCOUNTQTY,\
        :x->DISCOUNTVALUEPCT,\
        :x->DISCOUNTARTICLE,\
        :x->BASE_VALUE,\
        :x->ANZAHL,\
        :x->ORDVALNET
#define RANGELIST_UPDATE(x) \
        DISCOUNT.ARTICLENO=:x->ARTICLENO,\
        DISCOUNT.DISCOUNTGRPNO=:x->DISCOUNTGRPNO,\
        DISCOUNT.BASEQTY=:x->BASEQTY,\
        DISCOUNT.DISCOUNTQTY=:x->DISCOUNTQTY,\
        DISCOUNT.DISCOUNTVALUEPCT=:x->DISCOUNTVALUEPCT,\
        DISCOUNT.DISCOUNTARTICLE=:x->DISCOUNTARTICLE,\
        DISCOUNT.BASE_VALUE=:x->BASE_VALUE,\
        AADUMMY.ANZAHL=:x->ANZAHL,\
        AADUMMY.ORDVALNET=:x->ORDVALNET
/* SqlMacros390-Define of RANGELIST *******************************************/

#define RANGELIST_ZEIGER_390 \
        :ARTICLENO,\
        :DISCOUNTGRPNO,\
        :BASEQTY,\
        :DISCOUNTQTY,\
        :DISCOUNTVALUEPCT,\
        :DISCOUNTARTICLE,\
        :BASE_VALUE,\
        :ANZAHL,\
        :ORDVALNET
#define RANGELIST_UPDATE_390 \
        ARTICLENO=:ARTICLENO,\
        DISCOUNTGRPNO=:DISCOUNTGRPNO,\
        BASEQTY=:BASEQTY,\
        DISCOUNTQTY=:DISCOUNTQTY,\
        DISCOUNTVALUEPCT=:DISCOUNTVALUEPCT,\
        DISCOUNTARTICLE=:DISCOUNTARTICLE,\
        BASE_VALUE=:BASE_VALUE,\
        ANZAHL=:ANZAHL,\
        ORDVALNET=:ORDVALNET
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of RANGELIST ***********************************************/

#ifndef TRANSCLASS
typedef struct N_RANGELIST {
    long ARTICLENO;
    long DISCOUNTGRPNO;
    long BASEQTY;
    short DISCOUNTQTY;
    double DISCOUNTVALUEPCT;
    long DISCOUNTARTICLE;
    double BASE_VALUE;
    long ANZAHL;
    double ORDVALNET;
} rangelistS;
#else /* TRANSCLASS */
typedef struct N_RANGELIST {
    long ARTICLENO;
    long DISCOUNTGRPNO;
    long BASEQTY;
    short DISCOUNTQTY;
    double DISCOUNTVALUEPCT;
    long DISCOUNTARTICLE;
    double BASE_VALUE;
    long ANZAHL;
    double ORDVALNET;

    bool operator == (const N_RANGELIST& right) const {
        return (
            ARTICLENO == right.ARTICLENO &&
            DISCOUNTGRPNO == right.DISCOUNTGRPNO &&
            BASEQTY == right.BASEQTY &&
            DISCOUNTQTY == right.DISCOUNTQTY &&
            DISCOUNTVALUEPCT == right.DISCOUNTVALUEPCT &&
            DISCOUNTARTICLE == right.DISCOUNTARTICLE &&
            BASE_VALUE == right.BASE_VALUE &&
            ANZAHL == right.ANZAHL &&
            ORDVALNET == right.ORDVALNET
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        ARTICLENO = 0;
        DISCOUNTGRPNO = 0;
        BASEQTY = 0;
        DISCOUNTQTY = 0;
        DISCOUNTVALUEPCT = 0;
        DISCOUNTARTICLE = 0;
        BASE_VALUE = 0;
        ANZAHL = 0;
        ORDVALNET = 0;
#endif
    }
} rangelistS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of RANGELIST *****************************************/

struct S_RANGELIST {
    char ARTICLENO[11];
    char DISCOUNTGRPNO[11];
    char BASEQTY[11];
    char DISCOUNTQTY[7];
    char DISCOUNTVALUEPCT[5 + 2];
    char DISCOUNTARTICLE[11];
    char BASE_VALUE[10 + 2];
    char ANZAHL[11];
    char ORDVALNET[11 + 2];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of RANGELIST ************************/

struct O_RANGELIST {
    char ARTICLENO[11];
    char DISCOUNTGRPNO[11];
    char BASEQTY[11];
    char DISCOUNTQTY[7];
    char DISCOUNTVALUEPCT[5];
    char DISCOUNTARTICLE[11];
    char BASE_VALUE[10];
    char ANZAHL[11];
    char ORDVALNET[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of RANGELIST ***********************************/

struct C_RANGELIST {
    long ARTICLENO;
    long DISCOUNTGRPNO;
    long BASEQTY;
    short DISCOUNTQTY;
    double DISCOUNTVALUEPCT;
    long DISCOUNTARTICLE;
    double BASE_VALUE;
    long ANZAHL;
    double ORDVALNET;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of RANGELIST *********************************/

struct I_RANGELIST {
    short ARTICLENO;
    short DISCOUNTGRPNO;
    short BASEQTY;
    short DISCOUNTQTY;
    short DISCOUNTVALUEPCT;
    short DISCOUNTARTICLE;
    short BASE_VALUE;
    short ANZAHL;
    short ORDVALNET;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of RANGELIST *******************************************/

#if defined (BUF_DESC)
static struct buf_desc RANGELIST_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_L , 11, 0 },
   { TYP_D, 10, 2 },
   { TYP_L , 11, 0 },
   { TYP_D, 11, 2 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc RANGELIST_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_L , 11, 0 },
   { TYP_D, 10, 2 },
   { TYP_L , 11, 0 },
   { TYP_D, 11, 2 },
};
#endif

/* description for datatypes of RANGELIST *************************************/

 #define RANGELIST_S390 \
         long ARTICLENO; \
         long DISCOUNTGRPNO; \
         long BASEQTY; \
         short DISCOUNTQTY; \
         double DISCOUNTVALUEPCT; \
         long DISCOUNTARTICLE; \
         double BASE_VALUE; \
         long ANZAHL; \
         double ORDVALNET; \



/* Copy-Function Struct to single Data RANGELIST ******************************/

 #define RANGELIST_S390_COPY_TO_SINGLE(_x_) \
         ARTICLENO=_x_->ARTICLENO;\
         DISCOUNTGRPNO=_x_->DISCOUNTGRPNO;\
         BASEQTY=_x_->BASEQTY;\
         DISCOUNTQTY=_x_->DISCOUNTQTY;\
         DISCOUNTVALUEPCT=_x_->DISCOUNTVALUEPCT;\
         DISCOUNTARTICLE=_x_->DISCOUNTARTICLE;\
         BASE_VALUE=_x_->BASE_VALUE;\
         ANZAHL=_x_->ANZAHL;\
         ORDVALNET=_x_->ORDVALNET;\

 #define RANGELIST_S390_COPY_TO_STRUCT(_x_) \
          _x_->ARTICLENO=ARTICLENO;\
          _x_->DISCOUNTGRPNO=DISCOUNTGRPNO;\
          _x_->BASEQTY=BASEQTY;\
          _x_->DISCOUNTQTY=DISCOUNTQTY;\
          _x_->DISCOUNTVALUEPCT=DISCOUNTVALUEPCT;\
          _x_->DISCOUNTARTICLE=DISCOUNTARTICLE;\
          _x_->BASE_VALUE=BASE_VALUE;\
          _x_->ANZAHL=ANZAHL;\
          _x_->ORDVALNET=ORDVALNET;\



/* FunctionNumber-Define of RangeList *****************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of RangeList *************************************/


#endif

/* C++ Class ******************************************************************/

#ifdef TRANSCLASS

#include <vector>
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

class CRANGELIST : public ppDadeVirtual {
public:
    rangelistS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<rangelistS> lst; // class list

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
                     vector< rangelistS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     rangelistS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< rangelistS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<rangelistS>::iterator
                 beginList() { return lst.begin(); }
    vector<rangelistS>::iterator
                 endList  () { return lst.end  (); }

    long         GetArticleno() const { return s.ARTICLENO; }
    long         GetDiscountgrpno() const { return s.DISCOUNTGRPNO; }
    long         GetBaseqty() const { return s.BASEQTY; }
    short        GetDiscountqty() const { return s.DISCOUNTQTY; }
    double       GetDiscountvaluepct() const { return s.DISCOUNTVALUEPCT; }
    long         GetDiscountarticle() const { return s.DISCOUNTARTICLE; }
    double       GetBase_value() const { return s.BASE_VALUE; }
    long         GetAnzahl() const { return s.ANZAHL; }
    double       GetOrdvalnet() const { return s.ORDVALNET; }

    const rangelistS &
                 GetStruct() const { return s; }
    void         SetArticleno(long t) { s.ARTICLENO = t; }
    void         SetDiscountgrpno(long t) { s.DISCOUNTGRPNO = t; }
    void         SetBaseqty(long t) { s.BASEQTY = t; }
    void         SetDiscountqty(short t) { s.DISCOUNTQTY = t; }
    void         SetDiscountvaluepct(double t) { s.DISCOUNTVALUEPCT = t; }
    void         SetDiscountarticle(long t) { s.DISCOUNTARTICLE = t; }
    void         SetBase_value(double t) { s.BASE_VALUE = t; }
    void         SetAnzahl(long t) { s.ANZAHL = t; }
    void         SetOrdvalnet(double t) { s.ORDVALNET = t; }

    void         SetStruct(const rangelistS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CRANGELIST() {
        ::buf_default((void *)&s, RANGELIST_BES, RANGELIST_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CRANGELIST() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, RANGELIST_BES, RANGELIST_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, RANGELIST_BES, (int)RANGELIST_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, RANGELIST_BES, (int)RANGELIST_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_RANGELIST & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, RANGELIST_BES, (int)RANGELIST_ANZ, error_msg);
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
/* CreateSqlStatement of RANGELIST ********************************************/

 #define RANGELIST_CREATE(x) EXEC SQL create table x (\
         ARTICLENO integer default 0 not null,\
         DISCOUNTGRPNO integer default 0 not null,\
         BASEQTY integer default 0 not null,\
         DISCOUNTQTY smallint default 0 not null,\
         DISCOUNTVALUEPCT decimal(5,2) default 0 not null,\
         DISCOUNTARTICLE integer default 0 not null,\
         BASE_VALUE decimal(10,2) default 0 not null,\
         ANZAHL integer default 0 not null,\
         ORDVALNET decimal(11,2) default 0 not null) extent size 80 next size 8 lock mode row;



/* CreateIndexStatement of RANGELIST ******************************************/

 #define RANGELIST_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create   index i_discount_1 on _X_(\
              BranchNo,\
              ArticleNo,\
              DiscountType,\
              PharmacyGroupId );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index i_discount_2 on _X_(\
              BranchNo,\
              DiscountGrpNo,\
              PharmacyGroupId );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index i_discount_3 on _X_(\
              BranchNo,\
              ArticleNo,\
              CustomerNo );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index i_discount_4 on _X_(\
              BranchNo,\
              CustomerNo,\
              PharmacyGroupId,\
              ArticleNo,\
              manufacturerno,\
              DiscountGrpNo );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index i_discount_5 on _X_(\
              BranchNo,\
              manufacturerno );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of RANGELIST ******************************************/

 #define RANGELIST_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_discount_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_discount_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_discount_3;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_discount_4;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_discount_5;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
