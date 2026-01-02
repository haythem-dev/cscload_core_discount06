#ifndef __PP_KDAUFTRAGPOSCHARGE_H_
#define __PP_KDAUFTRAGPOSCHARGE_H_

/******************************************************************************/
/* c:\tmp\kdauftragposcharge **************************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of KDAUFTRAGPOSCHARGE ****************************************/

#define L_KDAUFTRAGPOSCHARGE_KDAUFTRAGNR 11
#define L_KDAUFTRAGPOSCHARGE_POSNR 11
#define L_KDAUFTRAGPOSCHARGE_CHARGENNR 25
#define L_KDAUFTRAGPOSCHARGE_QUANTITYORDERED 11
#define L_KDAUFTRAGPOSCHARGE_FIXBATCH 6

/* Length/Count-Define of KDAUFTRAGPOSCHARGE **********************************/

#define LS_KDAUFTRAGPOSCHARGE_KDAUFTRAGNR 10 + 1
#define LS_KDAUFTRAGPOSCHARGE_POSNR 10 + 1
#define LS_KDAUFTRAGPOSCHARGE_CHARGENNR 25 + 1
#define LS_KDAUFTRAGPOSCHARGE_QUANTITYORDERED 10 + 1
#define LS_KDAUFTRAGPOSCHARGE_FIXBATCH 5 + 1

#define KDAUFTRAGPOSCHARGEKDAUFTRAGNR 0
#define KDAUFTRAGPOSCHARGEPOSNR 1
#define KDAUFTRAGPOSCHARGECHARGENNR 2
#define KDAUFTRAGPOSCHARGEQUANTITYORDERED 3
#define KDAUFTRAGPOSCHARGEFIXBATCH 4

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define KDAUFTRAGPOSCHARGE_H
#define KDAUFTRAGPOSCHARGE_ANZ ( sizeof(KDAUFTRAGPOSCHARGE_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of KDAUFTRAGPOSCHARGE ********************************************/

#define KDAUFTRAGPOSCHARGE_LISTE \
        KDAUFTRAGPOSCHARGE.KDAUFTRAGNR,\
        KDAUFTRAGPOSCHARGE.POSNR,\
        KDAUFTRAGPOSCHARGE.CHARGENNR,\
        KDAUFTRAGPOSCHARGE.QUANTITYORDERED,\
        KDAUFTRAGPOSCHARGE.FIXBATCH
#define KDAUFTRAGPOSCHARGE_LISTE_390 \
        KDAUFTRAGNR,\
        POSNR,\
        CHARGENNR,\
        QUANTITYORDERED,\
        FIXBATCH
#define KDAUFTRAGPOSCHARGE_PLISTE \
        "KDAUFTRAGPOSCHARGE.KDAUFTRAGNR,"\
        "KDAUFTRAGPOSCHARGE.POSNR,"\
        "KDAUFTRAGPOSCHARGE.CHARGENNR,"\
        "KDAUFTRAGPOSCHARGE.QUANTITYORDERED,"\
        "KDAUFTRAGPOSCHARGE.FIXBATCH"
#define KDAUFTRAGPOSCHARGE_PELISTE \
        "KDAUFTRAGNR,"\
        "POSNR,"\
        "CHARGENNR,"\
        "QUANTITYORDERED,"\
        "FIXBATCH"
#define KDAUFTRAGPOSCHARGE_UPDLISTE \
        "KDAUFTRAGNR=?,"\
        "POSNR=?,"\
        "CHARGENNR=?,"\
        "QUANTITYORDERED=?,"\
        "FIXBATCH=?"
/* SqlMacros-Define of KDAUFTRAGPOSCHARGE *************************************/

#define KDAUFTRAGPOSCHARGE_ZEIGER(x) \
        :x->KDAUFTRAGNR,\
        :x->POSNR,\
        :x->CHARGENNR,\
        :x->QUANTITYORDERED,\
        :x->FIXBATCH
#define KDAUFTRAGPOSCHARGE_ZEIGERSEL(x) \
        :x->KDAUFTRAGNR,\
        :x->POSNR,\
        :x->CHARGENNR,\
        :x->QUANTITYORDERED,\
        :x->FIXBATCH
#define KDAUFTRAGPOSCHARGE_UPDATE(x) \
        KDAUFTRAGPOSCHARGE.KDAUFTRAGNR=:x->KDAUFTRAGNR,\
        KDAUFTRAGPOSCHARGE.POSNR=:x->POSNR,\
        KDAUFTRAGPOSCHARGE.CHARGENNR=:x->CHARGENNR,\
        KDAUFTRAGPOSCHARGE.QUANTITYORDERED=:x->QUANTITYORDERED,\
        KDAUFTRAGPOSCHARGE.FIXBATCH=:x->FIXBATCH
/* SqlMacros390-Define of KDAUFTRAGPOSCHARGE **********************************/

#define KDAUFTRAGPOSCHARGE_ZEIGER_390 \
        :KDAUFTRAGNR,\
        :POSNR,\
        :CHARGENNR,\
        :QUANTITYORDERED,\
        :FIXBATCH
#define KDAUFTRAGPOSCHARGE_UPDATE_390 \
        KDAUFTRAGNR=:KDAUFTRAGNR,\
        POSNR=:POSNR,\
        CHARGENNR=:CHARGENNR,\
        QUANTITYORDERED=:QUANTITYORDERED,\
        FIXBATCH=:FIXBATCH
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of KDAUFTRAGPOSCHARGE **************************************/

#ifndef TRANSCLASS
typedef struct N_KDAUFTRAGPOSCHARGE {
    long KDAUFTRAGNR;
    long POSNR;
    char CHARGENNR[26];
    long QUANTITYORDERED;
    short FIXBATCH;
} kdauftragposchargeS;
#else /* TRANSCLASS */
typedef struct N_KDAUFTRAGPOSCHARGE {
    long KDAUFTRAGNR;
    long POSNR;
    char CHARGENNR[26];
    long QUANTITYORDERED;
    short FIXBATCH;

    bool operator == (const N_KDAUFTRAGPOSCHARGE& right) const {
        return (
            KDAUFTRAGNR == right.KDAUFTRAGNR &&
            POSNR == right.POSNR &&
            !strcmp(CHARGENNR, right.CHARGENNR) &&
            QUANTITYORDERED == right.QUANTITYORDERED &&
            FIXBATCH == right.FIXBATCH
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        KDAUFTRAGNR = 0;
        POSNR = 0;
        strcpy(CHARGENNR, " " );
        QUANTITYORDERED = 0;
        FIXBATCH = 0;
#endif
    }
} kdauftragposchargeS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of KDAUFTRAGPOSCHARGE ********************************/

struct S_KDAUFTRAGPOSCHARGE {
    char KDAUFTRAGNR[11];
    char POSNR[11];
    char CHARGENNR[25 + 1];
    char QUANTITYORDERED[11];
    char FIXBATCH[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of KDAUFTRAGPOSCHARGE ***************/

struct O_KDAUFTRAGPOSCHARGE {
    char KDAUFTRAGNR[11];
    char POSNR[11];
    char CHARGENNR[25];
    char QUANTITYORDERED[11];
    char FIXBATCH[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of KDAUFTRAGPOSCHARGE **************************/

struct C_KDAUFTRAGPOSCHARGE {
    long KDAUFTRAGNR;
    long POSNR;
    char CHARGENNR[26];
    long QUANTITYORDERED;
    short FIXBATCH;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of KDAUFTRAGPOSCHARGE ************************/

struct I_KDAUFTRAGPOSCHARGE {
    short KDAUFTRAGNR;
    short POSNR;
    short CHARGENNR;
    short QUANTITYORDERED;
    short FIXBATCH;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of KDAUFTRAGPOSCHARGE **********************************/

#if defined (BUF_DESC)
static struct buf_desc KDAUFTRAGPOSCHARGE_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 25, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc KDAUFTRAGPOSCHARGE_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 25, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* description for datatypes of KDAUFTRAGPOSCHARGE ****************************/

 #define KDAUFTRAGPOSCHARGE_S390 \
         long KDAUFTRAGNR; \
         long POSNR; \
         char CHARGENNR[26]; \
         long QUANTITYORDERED; \
         short FIXBATCH; \



/* Copy-Function Struct to single Data KDAUFTRAGPOSCHARGE *********************/

 #define KDAUFTRAGPOSCHARGE_S390_COPY_TO_SINGLE(_x_) \
         KDAUFTRAGNR=_x_->KDAUFTRAGNR;\
         POSNR=_x_->POSNR;\
          strcpy(CHARGENNR,_x_->CHARGENNR);\
         QUANTITYORDERED=_x_->QUANTITYORDERED;\
         FIXBATCH=_x_->FIXBATCH;\

 #define KDAUFTRAGPOSCHARGE_S390_COPY_TO_STRUCT(_x_) \
          _x_->KDAUFTRAGNR=KDAUFTRAGNR;\
          _x_->POSNR=POSNR;\
          strcpy(_x_->CHARGENNR,CHARGENNR);\
          _x_->QUANTITYORDERED=QUANTITYORDERED;\
          _x_->FIXBATCH=FIXBATCH;\



/* FunctionNumber-Define of kdauftragposcharge ********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of kdauftragposcharge ****************************/


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

class CKDAUFTRAGPOSCHARGE : public ppDadeVirtual {
public:
    kdauftragposchargeS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<kdauftragposchargeS> lst; // class list

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
                     vector< kdauftragposchargeS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     kdauftragposchargeS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< kdauftragposchargeS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<kdauftragposchargeS>::iterator
                 beginList() { return lst.begin(); }
    vector<kdauftragposchargeS>::iterator
                 endList  () { return lst.end  (); }

    long         GetKdauftragnr() const { return s.KDAUFTRAGNR; }
    long         GetPosnr() const { return s.POSNR; }
    const char*  GetChargennr(ppString & t) const { t = s.CHARGENNR; t.erasespace(ppString::END); return t.c_str(); }
    long         GetQuantityordered() const { return s.QUANTITYORDERED; }
    short        GetFixbatch() const { return s.FIXBATCH; }

    const kdauftragposchargeS &
                 GetStruct() const { return s; }
    void         SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
    void         SetPosnr(long t) { s.POSNR = t; }
    void         SetChargennr(const ppString & t) { ppGStrCopy(s.CHARGENNR, t.c_str(), L_KDAUFTRAGPOSCHARGE_CHARGENNR); }
    void         SetQuantityordered(long t) { s.QUANTITYORDERED = t; }
    void         SetFixbatch(short t) { s.FIXBATCH = t; }

    void         SetStruct(const kdauftragposchargeS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CKDAUFTRAGPOSCHARGE() {
        ::buf_default((void *)&s, KDAUFTRAGPOSCHARGE_BES, KDAUFTRAGPOSCHARGE_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CKDAUFTRAGPOSCHARGE() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, KDAUFTRAGPOSCHARGE_BES, KDAUFTRAGPOSCHARGE_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, KDAUFTRAGPOSCHARGE_BES, (int)KDAUFTRAGPOSCHARGE_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, KDAUFTRAGPOSCHARGE_BES, (int)KDAUFTRAGPOSCHARGE_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_KDAUFTRAGPOSCHARGE & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.CHARGENNR);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, KDAUFTRAGPOSCHARGE_BES, (int)KDAUFTRAGPOSCHARGE_ANZ, error_msg);
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
/* CreateSqlStatement of KDAUFTRAGPOSCHARGE ***********************************/

 #define KDAUFTRAGPOSCHARGE_CREATE(x) EXEC SQL create table x (\
         KDAUFTRAGNR integer default 0 not null,\
         POSNR integer default 0 not null,\
         CHARGENNR char(25) default " " not null,\
         QUANTITYORDERED integer default 0 not null,\
         FIXBATCH smallint default 0 not null) in ksc extent size 784 next size 80 lock mode row;



/* CreateIndexStatement of KDAUFTRAGPOSCHARGE *********************************/

 #define KDAUFTRAGPOSCHARGE_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_kdposcharge_1 on _X_(\
              kdauftragnr,\
              posnr ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of KDAUFTRAGPOSCHARGE *********************************/

 #define KDAUFTRAGPOSCHARGE_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_kdposcharge_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
