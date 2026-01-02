#ifndef __PP_KDVERBUNDPOSRAB_H_
#define __PP_KDVERBUNDPOSRAB_H_

/******************************************************************************/
/* c:\prri\headerfiles\kdverbundposrab ****************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <pplib/bufkon.h>

/* Length-Define of KDVERBUNDPOSRAB *******************************************/

#define L_KDVERBUNDPOSRAB_HERKUNFTFILIALE 6
#define L_KDVERBUNDPOSRAB_FILIALNR 6
#define L_KDVERBUNDPOSRAB_KDAUFTRAGNR 11
#define L_KDVERBUNDPOSRAB_POSNR 11
#define L_KDVERBUNDPOSRAB_DISCOUNTTYPE 6
#define L_KDVERBUNDPOSRAB_DISCOUNTVALUEPCT 5
#define N_KDVERBUNDPOSRAB_DISCOUNTVALUEPCT 2
#define L_KDVERBUNDPOSRAB_PHARMACYGROUPID 3
#define L_KDVERBUNDPOSRAB_PAYMENTTARGETNO 6
#define L_KDVERBUNDPOSRAB_DISCOUNTVALPCTMAN 5
#define N_KDVERBUNDPOSRAB_DISCOUNTVALPCTMAN 2
#define L_KDVERBUNDPOSRAB_FIXEDPRICE 9
#define N_KDVERBUNDPOSRAB_FIXEDPRICE 2

/* Length/Count-Define of KDVERBUNDPOSRAB *************************************/

#define LS_KDVERBUNDPOSRAB_HERKUNFTFILIALE 5 + 1
#define LS_KDVERBUNDPOSRAB_FILIALNR 5 + 1
#define LS_KDVERBUNDPOSRAB_KDAUFTRAGNR 10 + 1
#define LS_KDVERBUNDPOSRAB_POSNR 10 + 1
#define LS_KDVERBUNDPOSRAB_DISCOUNTTYPE 5 + 1
#define LS_KDVERBUNDPOSRAB_DISCOUNTVALUEPCT 5 + 2
#define LS_KDVERBUNDPOSRAB_PHARMACYGROUPID 3 + 1
#define LS_KDVERBUNDPOSRAB_PAYMENTTARGETNO 5 + 1
#define LS_KDVERBUNDPOSRAB_DISCOUNTVALPCTMAN 5 + 2
#define LS_KDVERBUNDPOSRAB_FIXEDPRICE 9 + 2

#define KDVERBUNDPOSRABHERKUNFTFILIALE 0
#define KDVERBUNDPOSRABFILIALNR 1
#define KDVERBUNDPOSRABKDAUFTRAGNR 2
#define KDVERBUNDPOSRABPOSNR 3
#define KDVERBUNDPOSRABDISCOUNTTYPE 4
#define KDVERBUNDPOSRABDISCOUNTVALUEPCT 5
#define KDVERBUNDPOSRABPHARMACYGROUPID 6
#define KDVERBUNDPOSRABPAYMENTTARGETNO 7
#define KDVERBUNDPOSRABDISCOUNTVALPCTMAN 8
#define KDVERBUNDPOSRABFIXEDPRICE 9

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define KDVERBUNDPOSRAB_H
#define KDVERBUNDPOSRAB_ANZ ( sizeof(KDVERBUNDPOSRAB_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of KDVERBUNDPOSRAB ***********************************************/

#define KDVERBUNDPOSRAB_LISTE \
        KDVERBUNDPOSRAB.HERKUNFTFILIALE,\
        KDVERBUNDPOSRAB.FILIALNR,\
        KDVERBUNDPOSRAB.KDAUFTRAGNR,\
        KDVERBUNDPOSRAB.POSNR,\
        KDVERBUNDPOSRAB.DISCOUNTTYPE,\
        KDVERBUNDPOSRAB.DISCOUNTVALUEPCT,\
        KDVERBUNDPOSRAB.PHARMACYGROUPID,\
        KDVERBUNDPOSRAB.PAYMENTTARGETNO,\
        KDVERBUNDPOSRAB.DISCOUNTVALPCTMAN,\
        KDVERBUNDPOSRAB.FIXEDPRICE
#define KDVERBUNDPOSRAB_LISTE_390 \
        HERKUNFTFILIALE,\
        FILIALNR,\
        KDAUFTRAGNR,\
        POSNR,\
        DISCOUNTTYPE,\
        DISCOUNTVALUEPCT,\
        PHARMACYGROUPID,\
        PAYMENTTARGETNO,\
        DISCOUNTVALPCTMAN,\
        FIXEDPRICE
#define KDVERBUNDPOSRAB_PLISTE \
        "KDVERBUNDPOSRAB.HERKUNFTFILIALE,"\
        "KDVERBUNDPOSRAB.FILIALNR,"\
        "KDVERBUNDPOSRAB.KDAUFTRAGNR,"\
        "KDVERBUNDPOSRAB.POSNR,"\
        "KDVERBUNDPOSRAB.DISCOUNTTYPE,"\
        "KDVERBUNDPOSRAB.DISCOUNTVALUEPCT,"\
        "KDVERBUNDPOSRAB.PHARMACYGROUPID,"\
        "KDVERBUNDPOSRAB.PAYMENTTARGETNO,"\
        "KDVERBUNDPOSRAB.DISCOUNTVALPCTMAN,"\
        "KDVERBUNDPOSRAB.FIXEDPRICE"
#define KDVERBUNDPOSRAB_PELISTE \
        "HERKUNFTFILIALE,"\
        "FILIALNR,"\
        "KDAUFTRAGNR,"\
        "POSNR,"\
        "DISCOUNTTYPE,"\
        "DISCOUNTVALUEPCT,"\
        "PHARMACYGROUPID,"\
        "PAYMENTTARGETNO,"\
        "DISCOUNTVALPCTMAN,"\
        "FIXEDPRICE"
#define KDVERBUNDPOSRAB_UPDLISTE \
        "HERKUNFTFILIALE=?,"\
        "FILIALNR=?,"\
        "KDAUFTRAGNR=?,"\
        "POSNR=?,"\
        "DISCOUNTTYPE=?,"\
        "DISCOUNTVALUEPCT=?,"\
        "PHARMACYGROUPID=?,"\
        "PAYMENTTARGETNO=?,"\
        "DISCOUNTVALPCTMAN=?,"\
        "FIXEDPRICE=?"
/* SqlMacros-Define of KDVERBUNDPOSRAB ****************************************/

#define KDVERBUNDPOSRAB_ZEIGER(x) \
        :x->HERKUNFTFILIALE,\
        :x->FILIALNR,\
        :x->KDAUFTRAGNR,\
        :x->POSNR,\
        :x->DISCOUNTTYPE,\
        :x->DISCOUNTVALUEPCT,\
        :x->PHARMACYGROUPID,\
        :x->PAYMENTTARGETNO,\
        :x->DISCOUNTVALPCTMAN,\
        :x->FIXEDPRICE
#define KDVERBUNDPOSRAB_ZEIGERSEL(x) \
        :x->HERKUNFTFILIALE,\
        :x->FILIALNR,\
        :x->KDAUFTRAGNR,\
        :x->POSNR,\
        :x->DISCOUNTTYPE,\
        :x->DISCOUNTVALUEPCT,\
        :x->PHARMACYGROUPID,\
        :x->PAYMENTTARGETNO,\
        :x->DISCOUNTVALPCTMAN,\
        :x->FIXEDPRICE
#define KDVERBUNDPOSRAB_UPDATE(x) \
        KDVERBUNDPOSRAB.HERKUNFTFILIALE=:x->HERKUNFTFILIALE,\
        KDVERBUNDPOSRAB.FILIALNR=:x->FILIALNR,\
        KDVERBUNDPOSRAB.KDAUFTRAGNR=:x->KDAUFTRAGNR,\
        KDVERBUNDPOSRAB.POSNR=:x->POSNR,\
        KDVERBUNDPOSRAB.DISCOUNTTYPE=:x->DISCOUNTTYPE,\
        KDVERBUNDPOSRAB.DISCOUNTVALUEPCT=:x->DISCOUNTVALUEPCT,\
        KDVERBUNDPOSRAB.PHARMACYGROUPID=:x->PHARMACYGROUPID,\
        KDVERBUNDPOSRAB.PAYMENTTARGETNO=:x->PAYMENTTARGETNO,\
        KDVERBUNDPOSRAB.DISCOUNTVALPCTMAN=:x->DISCOUNTVALPCTMAN,\
        KDVERBUNDPOSRAB.FIXEDPRICE=:x->FIXEDPRICE
/* SqlMacros390-Define of KDVERBUNDPOSRAB *************************************/

#define KDVERBUNDPOSRAB_ZEIGER_390 \
        :HERKUNFTFILIALE,\
        :FILIALNR,\
        :KDAUFTRAGNR,\
        :POSNR,\
        :DISCOUNTTYPE,\
        :DISCOUNTVALUEPCT,\
        :PHARMACYGROUPID,\
        :PAYMENTTARGETNO,\
        :DISCOUNTVALPCTMAN,\
        :FIXEDPRICE
#define KDVERBUNDPOSRAB_UPDATE_390 \
        HERKUNFTFILIALE=:HERKUNFTFILIALE,\
        FILIALNR=:FILIALNR,\
        KDAUFTRAGNR=:KDAUFTRAGNR,\
        POSNR=:POSNR,\
        DISCOUNTTYPE=:DISCOUNTTYPE,\
        DISCOUNTVALUEPCT=:DISCOUNTVALUEPCT,\
        PHARMACYGROUPID=:PHARMACYGROUPID,\
        PAYMENTTARGETNO=:PAYMENTTARGETNO,\
        DISCOUNTVALPCTMAN=:DISCOUNTVALPCTMAN,\
        FIXEDPRICE=:FIXEDPRICE
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of KDVERBUNDPOSRAB *****************************************/

#ifndef TRANSCLASS
typedef struct N_KDVERBUNDPOSRAB {
    short HERKUNFTFILIALE;
    short FILIALNR;
    long KDAUFTRAGNR;
    long POSNR;
    short DISCOUNTTYPE;
    double DISCOUNTVALUEPCT;
    char PHARMACYGROUPID[4];
    short PAYMENTTARGETNO;
    double DISCOUNTVALPCTMAN;
    double FIXEDPRICE;
} kdverbundposrabS;
#else /* TRANSCLASS */
typedef struct N_KDVERBUNDPOSRAB {
    short HERKUNFTFILIALE;
    short FILIALNR;
    long KDAUFTRAGNR;
    long POSNR;
    short DISCOUNTTYPE;
    double DISCOUNTVALUEPCT;
    char PHARMACYGROUPID[4];
    short PAYMENTTARGETNO;
    double DISCOUNTVALPCTMAN;
    double FIXEDPRICE;

    bool operator == (const N_KDVERBUNDPOSRAB& right) const {
        return (
            HERKUNFTFILIALE == right.HERKUNFTFILIALE &&
            FILIALNR == right.FILIALNR &&
            KDAUFTRAGNR == right.KDAUFTRAGNR &&
            POSNR == right.POSNR &&
            DISCOUNTTYPE == right.DISCOUNTTYPE &&
            DISCOUNTVALUEPCT == right.DISCOUNTVALUEPCT &&
            !strcmp(PHARMACYGROUPID, right.PHARMACYGROUPID) &&
            PAYMENTTARGETNO == right.PAYMENTTARGETNO &&
            DISCOUNTVALPCTMAN == right.DISCOUNTVALPCTMAN &&
            FIXEDPRICE == right.FIXEDPRICE
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        HERKUNFTFILIALE = 0;
        FILIALNR = 0;
        KDAUFTRAGNR = 0;
        POSNR = 0;
        DISCOUNTTYPE = 0;
        DISCOUNTVALUEPCT = 0;
        strcpy(PHARMACYGROUPID, " " );
        PAYMENTTARGETNO = 0;
        DISCOUNTVALPCTMAN = 0;
        FIXEDPRICE = 0;
#endif
    }
} kdverbundposrabS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of KDVERBUNDPOSRAB ***********************************/

struct S_KDVERBUNDPOSRAB {
    char HERKUNFTFILIALE[7];
    char FILIALNR[7];
    char KDAUFTRAGNR[11];
    char POSNR[11];
    char DISCOUNTTYPE[7];
    char DISCOUNTVALUEPCT[5 + 2];
    char PHARMACYGROUPID[3 + 1];
    char PAYMENTTARGETNO[7];
    char DISCOUNTVALPCTMAN[5 + 2];
    char FIXEDPRICE[9 + 2];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of KDVERBUNDPOSRAB ******************/

struct O_KDVERBUNDPOSRAB {
    char HERKUNFTFILIALE[7];
    char FILIALNR[7];
    char KDAUFTRAGNR[11];
    char POSNR[11];
    char DISCOUNTTYPE[7];
    char DISCOUNTVALUEPCT[5];
    char PHARMACYGROUPID[3];
    char PAYMENTTARGETNO[7];
    char DISCOUNTVALPCTMAN[5];
    char FIXEDPRICE[9];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of KDVERBUNDPOSRAB *****************************/

struct C_KDVERBUNDPOSRAB {
    short HERKUNFTFILIALE;
    short FILIALNR;
    long KDAUFTRAGNR;
    long POSNR;
    short DISCOUNTTYPE;
    double DISCOUNTVALUEPCT;
    char PHARMACYGROUPID[4];
    short PAYMENTTARGETNO;
    double DISCOUNTVALPCTMAN;
    double FIXEDPRICE;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of KDVERBUNDPOSRAB ***************************/

struct I_KDVERBUNDPOSRAB {
    short HERKUNFTFILIALE;
    short FILIALNR;
    short KDAUFTRAGNR;
    short POSNR;
    short DISCOUNTTYPE;
    short DISCOUNTVALUEPCT;
    short PHARMACYGROUPID;
    short PAYMENTTARGETNO;
    short DISCOUNTVALPCTMAN;
    short FIXEDPRICE;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of KDVERBUNDPOSRAB *************************************/

#if defined (BUF_DESC)
static struct buf_desc KDVERBUNDPOSRAB_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_C, 3, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 9, 2 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc KDVERBUNDPOSRAB_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_C, 3, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 9, 2 },
};
#endif

/* description for datatypes of KDVERBUNDPOSRAB *******************************/

 #define KDVERBUNDPOSRAB_S390 \
         short HERKUNFTFILIALE; \
         short FILIALNR; \
         long KDAUFTRAGNR; \
         long POSNR; \
         short DISCOUNTTYPE; \
         double DISCOUNTVALUEPCT; \
         char PHARMACYGROUPID[4]; \
         short PAYMENTTARGETNO; \
         double DISCOUNTVALPCTMAN; \
         double FIXEDPRICE; \



/* Copy-Function Struct to single Data KDVERBUNDPOSRAB ************************/

 #define KDVERBUNDPOSRAB_S390_COPY_TO_SINGLE(_x_) \
         HERKUNFTFILIALE=_x_->HERKUNFTFILIALE;\
         FILIALNR=_x_->FILIALNR;\
         KDAUFTRAGNR=_x_->KDAUFTRAGNR;\
         POSNR=_x_->POSNR;\
         DISCOUNTTYPE=_x_->DISCOUNTTYPE;\
         DISCOUNTVALUEPCT=_x_->DISCOUNTVALUEPCT;\
          strcpy(PHARMACYGROUPID,_x_->PHARMACYGROUPID);\
         PAYMENTTARGETNO=_x_->PAYMENTTARGETNO;\
         DISCOUNTVALPCTMAN=_x_->DISCOUNTVALPCTMAN;\
         FIXEDPRICE=_x_->FIXEDPRICE;\

 #define KDVERBUNDPOSRAB_S390_COPY_TO_STRUCT(_x_) \
          _x_->HERKUNFTFILIALE=HERKUNFTFILIALE;\
          _x_->FILIALNR=FILIALNR;\
          _x_->KDAUFTRAGNR=KDAUFTRAGNR;\
          _x_->POSNR=POSNR;\
          _x_->DISCOUNTTYPE=DISCOUNTTYPE;\
          _x_->DISCOUNTVALUEPCT=DISCOUNTVALUEPCT;\
          strcpy(_x_->PHARMACYGROUPID,PHARMACYGROUPID);\
          _x_->PAYMENTTARGETNO=PAYMENTTARGETNO;\
          _x_->DISCOUNTVALPCTMAN=DISCOUNTVALPCTMAN;\
          _x_->FIXEDPRICE=FIXEDPRICE;\



/* FunctionNumber-Define of kdverbundposrab ***********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of kdverbundposrab *******************************/


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

class CKDVERBUNDPOSRAB : public ppDadeVirtual {
public:
    kdverbundposrabS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<kdverbundposrabS> lst; // class list

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
                     vector< kdverbundposrabS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     kdverbundposrabS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< kdverbundposrabS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<kdverbundposrabS>::iterator
                 beginList() { return lst.begin(); }
    vector<kdverbundposrabS>::iterator
                 endList  () { return lst.end  (); }

    short        GetHerkunftfiliale() const { return s.HERKUNFTFILIALE; }
    short        GetFilialnr() const { return s.FILIALNR; }
    long         GetKdauftragnr() const { return s.KDAUFTRAGNR; }
    long         GetPosnr() const { return s.POSNR; }
    short        GetDiscounttype() const { return s.DISCOUNTTYPE; }
    double       GetDiscountvaluepct() const { return s.DISCOUNTVALUEPCT; }
    const char*  GetPharmacygroupid(ppString & t) const { t = s.PHARMACYGROUPID; t.erasespace(ppString::END); return t.c_str(); }
    short        GetPaymenttargetno() const { return s.PAYMENTTARGETNO; }
    double       GetDiscountvalpctman() const { return s.DISCOUNTVALPCTMAN; }
    double       GetFixedprice() const { return s.FIXEDPRICE; }

    const kdverbundposrabS &
                 GetStruct() const { return s; }
    void         SetHerkunftfiliale(short t) { s.HERKUNFTFILIALE = t; }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
    void         SetPosnr(long t) { s.POSNR = t; }
    void         SetDiscounttype(short t) { s.DISCOUNTTYPE = t; }
    void         SetDiscountvaluepct(double t) { s.DISCOUNTVALUEPCT = t; }
    void         SetPharmacygroupid(const ppString & t) { ppGStrCopy(s.PHARMACYGROUPID, t.c_str(), L_KDVERBUNDPOSRAB_PHARMACYGROUPID); }
    void         SetPaymenttargetno(short t) { s.PAYMENTTARGETNO = t; }
    void         SetDiscountvalpctman(double t) { s.DISCOUNTVALPCTMAN = t; }
    void         SetFixedprice(double t) { s.FIXEDPRICE = t; }

    void         SetStruct(const kdverbundposrabS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CKDVERBUNDPOSRAB() {
        ::buf_default((void *)&s, KDVERBUNDPOSRAB_BES, KDVERBUNDPOSRAB_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CKDVERBUNDPOSRAB() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, KDVERBUNDPOSRAB_BES, KDVERBUNDPOSRAB_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, KDVERBUNDPOSRAB_BES, (int)KDVERBUNDPOSRAB_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, KDVERBUNDPOSRAB_BES, (int)KDVERBUNDPOSRAB_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_KDVERBUNDPOSRAB & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.PHARMACYGROUPID);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, KDVERBUNDPOSRAB_BES, (int)KDVERBUNDPOSRAB_ANZ, error_msg);
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
/* CreateSqlStatement of KDVERBUNDPOSRAB **************************************/

 #define KDVERBUNDPOSRAB_CREATE(x) EXEC SQL create table x (\
         HERKUNFTFILIALE smallint default 0 not null,\
         FILIALNR smallint default 0 not null,\
         KDAUFTRAGNR integer default 0 not null,\
         POSNR integer default 0 not null,\
         DISCOUNTTYPE smallint default 0 not null,\
         DISCOUNTVALUEPCT decimal(5,2) default 0 not null,\
         PHARMACYGROUPID char(3) default " " not null,\
         PAYMENTTARGETNO smallint default 0 not null,\
         DISCOUNTVALPCTMAN decimal(5,2) default 0 not null,\
         FIXEDPRICE decimal(9,2) default 0 not null) in ksc extent size 224 next size 24 lock mode row;



/* CreateIndexStatement of KDVERBUNDPOSRAB ************************************/

 #define KDVERBUNDPOSRAB_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_kdverbposrab_1 on _X_(\
              filialnr,\
              herkunftfiliale,\
              kdauftragnr,\
              posnr,\
              DiscountType,\
              paymenttargetno ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of KDVERBUNDPOSRAB ************************************/

 #define KDVERBUNDPOSRAB_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_kdverbposrab_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
