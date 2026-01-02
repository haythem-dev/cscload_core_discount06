#ifndef __PP_PROMOTIONSCALE_H_
#define __PP_PROMOTIONSCALE_H_

/******************************************************************************/
/* w:\PromotionScale **********************************************************/
/* produced by DADE 6.21.6 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of PROMOTIONSCALE ********************************************/

#define L_PROMOTIONSCALE_BASEPROMOTION 11
#define L_PROMOTIONSCALE_PROMOTION_NO 6

/* Length/Count-Define of PROMOTIONSCALE **************************************/

#define LS_PROMOTIONSCALE_BASEPROMOTION 10 + 1
#define LS_PROMOTIONSCALE_PROMOTION_NO 5 + 1

#define PROMOTIONSCALEBASEPROMOTION 0
#define PROMOTIONSCALEPROMOTION_NO 1

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define PROMOTIONSCALE_H
#define PROMOTIONSCALE_ANZ ( sizeof(PROMOTIONSCALE_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of PROMOTIONSCALE ************************************************/

#define PROMOTIONSCALE_LISTE \
        PROMOTIONSCALE.BASEPROMOTION,\
        PROMOTIONSCALE.PROMOTION_NO
#define PROMOTIONSCALE_LISTE_390 \
        BASEPROMOTION,\
        PROMOTION_NO
#define PROMOTIONSCALE_PLISTE \
        "PROMOTIONSCALE.BASEPROMOTION,"\
        "PROMOTIONSCALE.PROMOTION_NO"
#define PROMOTIONSCALE_PELISTE \
        "BASEPROMOTION,"\
        "PROMOTION_NO"
#define PROMOTIONSCALE_UPDLISTE \
        "BASEPROMOTION=?,"\
        "PROMOTION_NO=?"
/* SqlMacros-Define of PROMOTIONSCALE *****************************************/

#define PROMOTIONSCALE_ZEIGER(x) \
        :x->BASEPROMOTION,\
        :x->PROMOTION_NO
#define PROMOTIONSCALE_ZEIGERSEL(x) \
        :x->BASEPROMOTION,\
        :x->PROMOTION_NO
#define PROMOTIONSCALE_UPDATE(x) \
        PROMOTIONSCALE.BASEPROMOTION=:x->BASEPROMOTION,\
        PROMOTIONSCALE.PROMOTION_NO=:x->PROMOTION_NO
/* SqlMacros390-Define of PROMOTIONSCALE **************************************/

#define PROMOTIONSCALE_ZEIGER_390 \
        :BASEPROMOTION,\
        :PROMOTION_NO
#define PROMOTIONSCALE_UPDATE_390 \
        BASEPROMOTION=:BASEPROMOTION,\
        PROMOTION_NO=:PROMOTION_NO
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of PROMOTIONSCALE ******************************************/

#ifndef TRANSCLASS
typedef struct N_PROMOTIONSCALE {
    long BASEPROMOTION;
    short PROMOTION_NO;
} promotionscaleS;
#else /* TRANSCLASS */
typedef struct N_PROMOTIONSCALE {
    long BASEPROMOTION;
    short PROMOTION_NO;

    bool operator == (const N_PROMOTIONSCALE& right) const {
        return (
            BASEPROMOTION == right.BASEPROMOTION &&
            PROMOTION_NO == right.PROMOTION_NO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BASEPROMOTION = 0;
        PROMOTION_NO = 0;
#endif
    }
} promotionscaleS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of PROMOTIONSCALE ************************************/

struct S_PROMOTIONSCALE {
    char BASEPROMOTION[11];
    char PROMOTION_NO[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of PROMOTIONSCALE *******************/

struct O_PROMOTIONSCALE {
    char BASEPROMOTION[11];
    char PROMOTION_NO[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of PROMOTIONSCALE ******************************/

struct C_PROMOTIONSCALE {
    long BASEPROMOTION;
    short PROMOTION_NO;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of PROMOTIONSCALE ****************************/

struct I_PROMOTIONSCALE {
    short BASEPROMOTION;
    short PROMOTION_NO;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of PROMOTIONSCALE **************************************/

#if defined (BUF_DESC)
static struct buf_desc PROMOTIONSCALE_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc PROMOTIONSCALE_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* description for datatypes of PROMOTIONSCALE ********************************/

 #define PROMOTIONSCALE_S390 \
         long BASEPROMOTION; \
         short PROMOTION_NO; \



/* Copy-Function Struct to single Data PROMOTIONSCALE *************************/

 #define PROMOTIONSCALE_S390_COPY_TO_SINGLE(_x_) \
         BASEPROMOTION=_x_->BASEPROMOTION;\
         PROMOTION_NO=_x_->PROMOTION_NO;\

 #define PROMOTIONSCALE_S390_COPY_TO_STRUCT(_x_) \
          _x_->BASEPROMOTION=BASEPROMOTION;\
          _x_->PROMOTION_NO=PROMOTION_NO;\



/* FunctionNumber-Define of PromotionScale ************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of PromotionScale ********************************/


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

class CPROMOTIONSCALE : public ppDadeVirtual {
public:
    promotionscaleS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<promotionscaleS> lst; // class list

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
                     vector< promotionscaleS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     promotionscaleS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< promotionscaleS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<promotionscaleS>::iterator
                 beginList() { return lst.begin(); }
    vector<promotionscaleS>::iterator
                 endList  () { return lst.end  (); }

    long         GetBasepromotion() const { return s.BASEPROMOTION; }
    short        GetPromotion_no() const { return s.PROMOTION_NO; }

    const promotionscaleS &
                 GetStruct() const { return s; }
    void         SetBasepromotion(long t) { s.BASEPROMOTION = t; }
    void         SetPromotion_no(short t) { s.PROMOTION_NO = t; }

    void         SetStruct(const promotionscaleS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CPROMOTIONSCALE() {
        ::buf_default((void *)&s, PROMOTIONSCALE_BES, PROMOTIONSCALE_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CPROMOTIONSCALE() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, PROMOTIONSCALE_BES, PROMOTIONSCALE_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, PROMOTIONSCALE_BES, (int)PROMOTIONSCALE_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, PROMOTIONSCALE_BES, (int)PROMOTIONSCALE_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_PROMOTIONSCALE & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, PROMOTIONSCALE_BES, (int)PROMOTIONSCALE_ANZ, error_msg);
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
/* CreateSqlStatement of PROMOTIONSCALE ***************************************/

 #define PROMOTIONSCALE_CREATE(x) EXEC SQL create table x (\
         BASEPROMOTION integer default 0 not null,\
         PROMOTION_NO smallint default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of PROMOTIONSCALE *************************************/

 #define PROMOTIONSCALE_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_promoscale_1 on _X_(\
              BasePromotion,\
              promotion_no ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of PROMOTIONSCALE *************************************/

 #define PROMOTIONSCALE_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_promoscale_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
