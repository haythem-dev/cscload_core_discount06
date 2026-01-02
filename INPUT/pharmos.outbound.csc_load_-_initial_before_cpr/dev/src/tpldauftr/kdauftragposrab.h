#ifndef __PP_KDAUFTRAGPOSRAB_H_
#define __PP_KDAUFTRAGPOSRAB_H_

/******************************************************************************/
/* c:\prri\headerfiles\kdauftragposrab ****************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of KDAUFTRAGPOSRAB *******************************************/

#define L_KDAUFTRAGPOSRAB_KDAUFTRAGNR 11
#define L_KDAUFTRAGPOSRAB_POSNR 11
#define L_KDAUFTRAGPOSRAB_DISCOUNTTYPE 6
#define L_KDAUFTRAGPOSRAB_DISCOUNTVALUEPCT 5
#define N_KDAUFTRAGPOSRAB_DISCOUNTVALUEPCT 2
#define L_KDAUFTRAGPOSRAB_PHARMACYGROUPID 3
#define L_KDAUFTRAGPOSRAB_PAYMENTTARGETNO 6
#define L_KDAUFTRAGPOSRAB_DISCOUNTVALPCTMAN 5
#define N_KDAUFTRAGPOSRAB_DISCOUNTVALPCTMAN 2
#define L_KDAUFTRAGPOSRAB_SURCHARGEPCT 5
#define N_KDAUFTRAGPOSRAB_SURCHARGEPCT 2
#define L_KDAUFTRAGPOSRAB_DISCOUNTCATEGORY 6
#define L_KDAUFTRAGPOSRAB_INTERNALDISCOUNTFLAG 6
#define L_KDAUFTRAGPOSRAB_REFUNDVALUEPCT 5
#define N_KDAUFTRAGPOSRAB_REFUNDVALUEPCT 2
#define L_KDAUFTRAGPOSRAB_FIXEDPRICE 9
#define N_KDAUFTRAGPOSRAB_FIXEDPRICE 2
#define L_KDAUFTRAGPOSRAB_DISCOUNTCALCFROM 6
#define L_KDAUFTRAGPOSRAB_DISCOUNTAPPLYTO 6

/* Length/Count-Define of KDAUFTRAGPOSRAB *************************************/

#define LS_KDAUFTRAGPOSRAB_KDAUFTRAGNR 10 + 1
#define LS_KDAUFTRAGPOSRAB_POSNR 10 + 1
#define LS_KDAUFTRAGPOSRAB_DISCOUNTTYPE 5 + 1
#define LS_KDAUFTRAGPOSRAB_DISCOUNTVALUEPCT 5 + 2
#define LS_KDAUFTRAGPOSRAB_PHARMACYGROUPID 3 + 1
#define LS_KDAUFTRAGPOSRAB_PAYMENTTARGETNO 5 + 1
#define LS_KDAUFTRAGPOSRAB_DISCOUNTVALPCTMAN 5 + 2
#define LS_KDAUFTRAGPOSRAB_SURCHARGEPCT 5 + 2
#define LS_KDAUFTRAGPOSRAB_DISCOUNTCATEGORY 5 + 1
#define LS_KDAUFTRAGPOSRAB_INTERNALDISCOUNTFLAG 5 + 1
#define LS_KDAUFTRAGPOSRAB_REFUNDVALUEPCT 5 + 2
#define LS_KDAUFTRAGPOSRAB_FIXEDPRICE 9 + 2
#define LS_KDAUFTRAGPOSRAB_DISCOUNTCALCFROM 5 + 1
#define LS_KDAUFTRAGPOSRAB_DISCOUNTAPPLYTO 5 + 1

#define KDAUFTRAGPOSRABKDAUFTRAGNR 0
#define KDAUFTRAGPOSRABPOSNR 1
#define KDAUFTRAGPOSRABDISCOUNTTYPE 2
#define KDAUFTRAGPOSRABDISCOUNTVALUEPCT 3
#define KDAUFTRAGPOSRABPHARMACYGROUPID 4
#define KDAUFTRAGPOSRABPAYMENTTARGETNO 5
#define KDAUFTRAGPOSRABDISCOUNTVALPCTMAN 6
#define KDAUFTRAGPOSRABSURCHARGEPCT 7
#define KDAUFTRAGPOSRABDISCOUNTCATEGORY 8
#define KDAUFTRAGPOSRABINTERNALDISCOUNTFLAG 9
#define KDAUFTRAGPOSRABREFUNDVALUEPCT 10
#define KDAUFTRAGPOSRABFIXEDPRICE 11
#define KDAUFTRAGPOSRABDISCOUNTCALCFROM 12
#define KDAUFTRAGPOSRABDISCOUNTAPPLYTO 13

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define KDAUFTRAGPOSRAB_H
#define KDAUFTRAGPOSRAB_ANZ ( sizeof(KDAUFTRAGPOSRAB_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of KDAUFTRAGPOSRAB ***********************************************/

#define KDAUFTRAGPOSRAB_LISTE \
        KDAUFTRAGPOSRAB.KDAUFTRAGNR,\
        KDAUFTRAGPOSRAB.POSNR,\
        KDAUFTRAGPOSRAB.DISCOUNTTYPE,\
        KDAUFTRAGPOSRAB.DISCOUNTVALUEPCT,\
        KDAUFTRAGPOSRAB.PHARMACYGROUPID,\
        KDAUFTRAGPOSRAB.PAYMENTTARGETNO,\
        KDAUFTRAGPOSRAB.DISCOUNTVALPCTMAN,\
        KDAUFTRAGPOSRAB.SURCHARGEPCT,\
        KDAUFTRAGPOSRAB.DISCOUNTCATEGORY,\
        KDAUFTRAGPOSRAB.INTERNALDISCOUNTFLAG,\
        KDAUFTRAGPOSRAB.REFUNDVALUEPCT,\
        KDAUFTRAGPOSRAB.FIXEDPRICE,\
        KDAUFTRAGPOSRAB.DISCOUNTCALCFROM,\
        KDAUFTRAGPOSRAB.DISCOUNTAPPLYTO
#define KDAUFTRAGPOSRAB_LISTE_390 \
        KDAUFTRAGNR,\
        POSNR,\
        DISCOUNTTYPE,\
        DISCOUNTVALUEPCT,\
        PHARMACYGROUPID,\
        PAYMENTTARGETNO,\
        DISCOUNTVALPCTMAN,\
        SURCHARGEPCT,\
        DISCOUNTCATEGORY,\
        INTERNALDISCOUNTFLAG,\
        REFUNDVALUEPCT,\
        FIXEDPRICE,\
        DISCOUNTCALCFROM,\
        DISCOUNTAPPLYTO
#define KDAUFTRAGPOSRAB_PLISTE \
        "KDAUFTRAGPOSRAB.KDAUFTRAGNR,"\
        "KDAUFTRAGPOSRAB.POSNR,"\
        "KDAUFTRAGPOSRAB.DISCOUNTTYPE,"\
        "KDAUFTRAGPOSRAB.DISCOUNTVALUEPCT,"\
        "KDAUFTRAGPOSRAB.PHARMACYGROUPID,"\
        "KDAUFTRAGPOSRAB.PAYMENTTARGETNO,"\
        "KDAUFTRAGPOSRAB.DISCOUNTVALPCTMAN,"\
        "KDAUFTRAGPOSRAB.SURCHARGEPCT,"\
        "KDAUFTRAGPOSRAB.DISCOUNTCATEGORY,"\
        "KDAUFTRAGPOSRAB.INTERNALDISCOUNTFLAG,"\
        "KDAUFTRAGPOSRAB.REFUNDVALUEPCT,"\
        "KDAUFTRAGPOSRAB.FIXEDPRICE,"\
        "KDAUFTRAGPOSRAB.DISCOUNTCALCFROM,"\
        "KDAUFTRAGPOSRAB.DISCOUNTAPPLYTO"
#define KDAUFTRAGPOSRAB_PELISTE \
        "KDAUFTRAGNR,"\
        "POSNR,"\
        "DISCOUNTTYPE,"\
        "DISCOUNTVALUEPCT,"\
        "PHARMACYGROUPID,"\
        "PAYMENTTARGETNO,"\
        "DISCOUNTVALPCTMAN,"\
        "SURCHARGEPCT,"\
        "DISCOUNTCATEGORY,"\
        "INTERNALDISCOUNTFLAG,"\
        "REFUNDVALUEPCT,"\
        "FIXEDPRICE,"\
        "DISCOUNTCALCFROM,"\
        "DISCOUNTAPPLYTO"
#define KDAUFTRAGPOSRAB_UPDLISTE \
        "KDAUFTRAGNR=?,"\
        "POSNR=?,"\
        "DISCOUNTTYPE=?,"\
        "DISCOUNTVALUEPCT=?,"\
        "PHARMACYGROUPID=?,"\
        "PAYMENTTARGETNO=?,"\
        "DISCOUNTVALPCTMAN=?,"\
        "SURCHARGEPCT=?,"\
        "DISCOUNTCATEGORY=?,"\
        "INTERNALDISCOUNTFLAG=?,"\
        "REFUNDVALUEPCT=?,"\
        "FIXEDPRICE=?,"\
        "DISCOUNTCALCFROM=?,"\
        "DISCOUNTAPPLYTO=?"
/* SqlMacros-Define of KDAUFTRAGPOSRAB ****************************************/

#define KDAUFTRAGPOSRAB_ZEIGER(x) \
        :x->KDAUFTRAGNR,\
        :x->POSNR,\
        :x->DISCOUNTTYPE,\
        :x->DISCOUNTVALUEPCT,\
        :x->PHARMACYGROUPID,\
        :x->PAYMENTTARGETNO,\
        :x->DISCOUNTVALPCTMAN,\
        :x->SURCHARGEPCT,\
        :x->DISCOUNTCATEGORY,\
        :x->INTERNALDISCOUNTFLAG,\
        :x->REFUNDVALUEPCT,\
        :x->FIXEDPRICE,\
        :x->DISCOUNTCALCFROM,\
        :x->DISCOUNTAPPLYTO
#define KDAUFTRAGPOSRAB_ZEIGERSEL(x) \
        :x->KDAUFTRAGNR,\
        :x->POSNR,\
        :x->DISCOUNTTYPE,\
        :x->DISCOUNTVALUEPCT,\
        :x->PHARMACYGROUPID,\
        :x->PAYMENTTARGETNO,\
        :x->DISCOUNTVALPCTMAN,\
        :x->SURCHARGEPCT,\
        :x->DISCOUNTCATEGORY,\
        :x->INTERNALDISCOUNTFLAG,\
        :x->REFUNDVALUEPCT,\
        :x->FIXEDPRICE,\
        :x->DISCOUNTCALCFROM,\
        :x->DISCOUNTAPPLYTO
#define KDAUFTRAGPOSRAB_UPDATE(x) \
        KDAUFTRAGPOSRAB.KDAUFTRAGNR=:x->KDAUFTRAGNR,\
        KDAUFTRAGPOSRAB.POSNR=:x->POSNR,\
        KDAUFTRAGPOSRAB.DISCOUNTTYPE=:x->DISCOUNTTYPE,\
        KDAUFTRAGPOSRAB.DISCOUNTVALUEPCT=:x->DISCOUNTVALUEPCT,\
        KDAUFTRAGPOSRAB.PHARMACYGROUPID=:x->PHARMACYGROUPID,\
        KDAUFTRAGPOSRAB.PAYMENTTARGETNO=:x->PAYMENTTARGETNO,\
        KDAUFTRAGPOSRAB.DISCOUNTVALPCTMAN=:x->DISCOUNTVALPCTMAN,\
        KDAUFTRAGPOSRAB.SURCHARGEPCT=:x->SURCHARGEPCT,\
        KDAUFTRAGPOSRAB.DISCOUNTCATEGORY=:x->DISCOUNTCATEGORY,\
        KDAUFTRAGPOSRAB.INTERNALDISCOUNTFLAG=:x->INTERNALDISCOUNTFLAG,\
        KDAUFTRAGPOSRAB.REFUNDVALUEPCT=:x->REFUNDVALUEPCT,\
        KDAUFTRAGPOSRAB.FIXEDPRICE=:x->FIXEDPRICE,\
        KDAUFTRAGPOSRAB.DISCOUNTCALCFROM=:x->DISCOUNTCALCFROM,\
        KDAUFTRAGPOSRAB.DISCOUNTAPPLYTO=:x->DISCOUNTAPPLYTO
/* SqlMacros390-Define of KDAUFTRAGPOSRAB *************************************/

#define KDAUFTRAGPOSRAB_ZEIGER_390 \
        :KDAUFTRAGNR,\
        :POSNR,\
        :DISCOUNTTYPE,\
        :DISCOUNTVALUEPCT,\
        :PHARMACYGROUPID,\
        :PAYMENTTARGETNO,\
        :DISCOUNTVALPCTMAN,\
        :SURCHARGEPCT,\
        :DISCOUNTCATEGORY,\
        :INTERNALDISCOUNTFLAG,\
        :REFUNDVALUEPCT,\
        :FIXEDPRICE,\
        :DISCOUNTCALCFROM,\
        :DISCOUNTAPPLYTO
#define KDAUFTRAGPOSRAB_UPDATE_390 \
        KDAUFTRAGNR=:KDAUFTRAGNR,\
        POSNR=:POSNR,\
        DISCOUNTTYPE=:DISCOUNTTYPE,\
        DISCOUNTVALUEPCT=:DISCOUNTVALUEPCT,\
        PHARMACYGROUPID=:PHARMACYGROUPID,\
        PAYMENTTARGETNO=:PAYMENTTARGETNO,\
        DISCOUNTVALPCTMAN=:DISCOUNTVALPCTMAN,\
        SURCHARGEPCT=:SURCHARGEPCT,\
        DISCOUNTCATEGORY=:DISCOUNTCATEGORY,\
        INTERNALDISCOUNTFLAG=:INTERNALDISCOUNTFLAG,\
        REFUNDVALUEPCT=:REFUNDVALUEPCT,\
        FIXEDPRICE=:FIXEDPRICE,\
        DISCOUNTCALCFROM=:DISCOUNTCALCFROM,\
        DISCOUNTAPPLYTO=:DISCOUNTAPPLYTO
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of KDAUFTRAGPOSRAB *****************************************/

#ifndef TRANSCLASS
typedef struct N_KDAUFTRAGPOSRAB {
    long KDAUFTRAGNR;
    long POSNR;
    short DISCOUNTTYPE;
    double DISCOUNTVALUEPCT;
    char PHARMACYGROUPID[4];
    short PAYMENTTARGETNO;
    double DISCOUNTVALPCTMAN;
    double SURCHARGEPCT;
    short DISCOUNTCATEGORY;
    short INTERNALDISCOUNTFLAG;
    double REFUNDVALUEPCT;
    double FIXEDPRICE;
    short DISCOUNTCALCFROM;
    short DISCOUNTAPPLYTO;
} kdauftragposrabS;
#else /* TRANSCLASS */
typedef struct N_KDAUFTRAGPOSRAB {
    long KDAUFTRAGNR;
    long POSNR;
    short DISCOUNTTYPE;
    double DISCOUNTVALUEPCT;
    char PHARMACYGROUPID[4];
    short PAYMENTTARGETNO;
    double DISCOUNTVALPCTMAN;
    double SURCHARGEPCT;
    short DISCOUNTCATEGORY;
    short INTERNALDISCOUNTFLAG;
    double REFUNDVALUEPCT;
    double FIXEDPRICE;
    short DISCOUNTCALCFROM;
    short DISCOUNTAPPLYTO;

    bool operator == (const N_KDAUFTRAGPOSRAB& right) const {
        return (
            KDAUFTRAGNR == right.KDAUFTRAGNR &&
            POSNR == right.POSNR &&
            DISCOUNTTYPE == right.DISCOUNTTYPE &&
            DISCOUNTVALUEPCT == right.DISCOUNTVALUEPCT &&
            !strcmp(PHARMACYGROUPID, right.PHARMACYGROUPID) &&
            PAYMENTTARGETNO == right.PAYMENTTARGETNO &&
            DISCOUNTVALPCTMAN == right.DISCOUNTVALPCTMAN &&
            SURCHARGEPCT == right.SURCHARGEPCT &&
            DISCOUNTCATEGORY == right.DISCOUNTCATEGORY &&
            INTERNALDISCOUNTFLAG == right.INTERNALDISCOUNTFLAG &&
            REFUNDVALUEPCT == right.REFUNDVALUEPCT &&
            FIXEDPRICE == right.FIXEDPRICE &&
            DISCOUNTCALCFROM == right.DISCOUNTCALCFROM &&
            DISCOUNTAPPLYTO == right.DISCOUNTAPPLYTO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        KDAUFTRAGNR = 0;
        POSNR = 0;
        DISCOUNTTYPE = 0;
        DISCOUNTVALUEPCT = 0;
        strcpy(PHARMACYGROUPID, " " );
        PAYMENTTARGETNO = 0;
        DISCOUNTVALPCTMAN = 0;
        SURCHARGEPCT = 0;
        DISCOUNTCATEGORY = 0;
        INTERNALDISCOUNTFLAG = 0;
        REFUNDVALUEPCT = 0;
        FIXEDPRICE = 0;
        DISCOUNTCALCFROM = 0;
        DISCOUNTAPPLYTO = 1;
#endif
    }
} kdauftragposrabS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of KDAUFTRAGPOSRAB ***********************************/

struct S_KDAUFTRAGPOSRAB {
    char KDAUFTRAGNR[11];
    char POSNR[11];
    char DISCOUNTTYPE[7];
    char DISCOUNTVALUEPCT[5 + 2];
    char PHARMACYGROUPID[3 + 1];
    char PAYMENTTARGETNO[7];
    char DISCOUNTVALPCTMAN[5 + 2];
    char SURCHARGEPCT[5 + 2];
    char DISCOUNTCATEGORY[7];
    char INTERNALDISCOUNTFLAG[7];
    char REFUNDVALUEPCT[5 + 2];
    char FIXEDPRICE[9 + 2];
    char DISCOUNTCALCFROM[7];
    char DISCOUNTAPPLYTO[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of KDAUFTRAGPOSRAB ******************/

struct O_KDAUFTRAGPOSRAB {
    char KDAUFTRAGNR[11];
    char POSNR[11];
    char DISCOUNTTYPE[7];
    char DISCOUNTVALUEPCT[5];
    char PHARMACYGROUPID[3];
    char PAYMENTTARGETNO[7];
    char DISCOUNTVALPCTMAN[5];
    char SURCHARGEPCT[5];
    char DISCOUNTCATEGORY[7];
    char INTERNALDISCOUNTFLAG[7];
    char REFUNDVALUEPCT[5];
    char FIXEDPRICE[9];
    char DISCOUNTCALCFROM[7];
    char DISCOUNTAPPLYTO[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of KDAUFTRAGPOSRAB *****************************/

struct C_KDAUFTRAGPOSRAB {
    long KDAUFTRAGNR;
    long POSNR;
    short DISCOUNTTYPE;
    double DISCOUNTVALUEPCT;
    char PHARMACYGROUPID[4];
    short PAYMENTTARGETNO;
    double DISCOUNTVALPCTMAN;
    double SURCHARGEPCT;
    short DISCOUNTCATEGORY;
    short INTERNALDISCOUNTFLAG;
    double REFUNDVALUEPCT;
    double FIXEDPRICE;
    short DISCOUNTCALCFROM;
    short DISCOUNTAPPLYTO;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of KDAUFTRAGPOSRAB ***************************/

struct I_KDAUFTRAGPOSRAB {
    short KDAUFTRAGNR;
    short POSNR;
    short DISCOUNTTYPE;
    short DISCOUNTVALUEPCT;
    short PHARMACYGROUPID;
    short PAYMENTTARGETNO;
    short DISCOUNTVALPCTMAN;
    short SURCHARGEPCT;
    short DISCOUNTCATEGORY;
    short INTERNALDISCOUNTFLAG;
    short REFUNDVALUEPCT;
    short FIXEDPRICE;
    short DISCOUNTCALCFROM;
    short DISCOUNTAPPLYTO;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of KDAUFTRAGPOSRAB *************************************/

#if defined (BUF_DESC)
static struct buf_desc KDAUFTRAGPOSRAB_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_C, 3, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 5, 2 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 9, 2 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc KDAUFTRAGPOSRAB_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_C, 3, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 5, 2 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 9, 2 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* description for datatypes of KDAUFTRAGPOSRAB *******************************/

 #define KDAUFTRAGPOSRAB_S390 \
         long KDAUFTRAGNR; \
         long POSNR; \
         short DISCOUNTTYPE; \
         double DISCOUNTVALUEPCT; \
         char PHARMACYGROUPID[4]; \
         short PAYMENTTARGETNO; \
         double DISCOUNTVALPCTMAN; \
         double SURCHARGEPCT; \
         short DISCOUNTCATEGORY; \
         short INTERNALDISCOUNTFLAG; \
         double REFUNDVALUEPCT; \
         double FIXEDPRICE; \
         short DISCOUNTCALCFROM; \
         short DISCOUNTAPPLYTO; \



/* Copy-Function Struct to single Data KDAUFTRAGPOSRAB ************************/

 #define KDAUFTRAGPOSRAB_S390_COPY_TO_SINGLE(_x_) \
         KDAUFTRAGNR=_x_->KDAUFTRAGNR;\
         POSNR=_x_->POSNR;\
         DISCOUNTTYPE=_x_->DISCOUNTTYPE;\
         DISCOUNTVALUEPCT=_x_->DISCOUNTVALUEPCT;\
          strcpy(PHARMACYGROUPID,_x_->PHARMACYGROUPID);\
         PAYMENTTARGETNO=_x_->PAYMENTTARGETNO;\
         DISCOUNTVALPCTMAN=_x_->DISCOUNTVALPCTMAN;\
         SURCHARGEPCT=_x_->SURCHARGEPCT;\
         DISCOUNTCATEGORY=_x_->DISCOUNTCATEGORY;\
         INTERNALDISCOUNTFLAG=_x_->INTERNALDISCOUNTFLAG;\
         REFUNDVALUEPCT=_x_->REFUNDVALUEPCT;\
         FIXEDPRICE=_x_->FIXEDPRICE;\
         DISCOUNTCALCFROM=_x_->DISCOUNTCALCFROM;\
         DISCOUNTAPPLYTO=_x_->DISCOUNTAPPLYTO;\

 #define KDAUFTRAGPOSRAB_S390_COPY_TO_STRUCT(_x_) \
          _x_->KDAUFTRAGNR=KDAUFTRAGNR;\
          _x_->POSNR=POSNR;\
          _x_->DISCOUNTTYPE=DISCOUNTTYPE;\
          _x_->DISCOUNTVALUEPCT=DISCOUNTVALUEPCT;\
          strcpy(_x_->PHARMACYGROUPID,PHARMACYGROUPID);\
          _x_->PAYMENTTARGETNO=PAYMENTTARGETNO;\
          _x_->DISCOUNTVALPCTMAN=DISCOUNTVALPCTMAN;\
          _x_->SURCHARGEPCT=SURCHARGEPCT;\
          _x_->DISCOUNTCATEGORY=DISCOUNTCATEGORY;\
          _x_->INTERNALDISCOUNTFLAG=INTERNALDISCOUNTFLAG;\
          _x_->REFUNDVALUEPCT=REFUNDVALUEPCT;\
          _x_->FIXEDPRICE=FIXEDPRICE;\
          _x_->DISCOUNTCALCFROM=DISCOUNTCALCFROM;\
          _x_->DISCOUNTAPPLYTO=DISCOUNTAPPLYTO;\



/* FunctionNumber-Define of kdauftragposrab ***********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of kdauftragposrab *******************************/


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

class CKDAUFTRAGPOSRAB : public ppDadeVirtual {
public:
    kdauftragposrabS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<kdauftragposrabS> lst; // class list

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
                     vector< kdauftragposrabS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     kdauftragposrabS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< kdauftragposrabS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<kdauftragposrabS>::iterator
                 beginList() { return lst.begin(); }
    vector<kdauftragposrabS>::iterator
                 endList  () { return lst.end  (); }

    long         GetKdauftragnr() const { return s.KDAUFTRAGNR; }
    long         GetPosnr() const { return s.POSNR; }
    short        GetDiscounttype() const { return s.DISCOUNTTYPE; }
    double       GetDiscountvaluepct() const { return s.DISCOUNTVALUEPCT; }
    const char*  GetPharmacygroupid(ppString & t) const { t = s.PHARMACYGROUPID; t.erasespace(ppString::END); return t.c_str(); }
    short        GetPaymenttargetno() const { return s.PAYMENTTARGETNO; }
    double       GetDiscountvalpctman() const { return s.DISCOUNTVALPCTMAN; }
    double       GetSurchargepct() const { return s.SURCHARGEPCT; }
    short        GetDiscountcategory() const { return s.DISCOUNTCATEGORY; }
    short        GetInternaldiscountflag() const { return s.INTERNALDISCOUNTFLAG; }
    double       GetRefundvaluepct() const { return s.REFUNDVALUEPCT; }
    double       GetFixedprice() const { return s.FIXEDPRICE; }
    short        GetDiscountcalcfrom() const { return s.DISCOUNTCALCFROM; }
    short        GetDiscountapplyto() const { return s.DISCOUNTAPPLYTO; }

    const kdauftragposrabS &
                 GetStruct() const { return s; }
    void         SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
    void         SetPosnr(long t) { s.POSNR = t; }
    void         SetDiscounttype(short t) { s.DISCOUNTTYPE = t; }
    void         SetDiscountvaluepct(double t) { s.DISCOUNTVALUEPCT = t; }
    void         SetPharmacygroupid(const ppString & t) { ppGStrCopy(s.PHARMACYGROUPID, t.c_str(), L_KDAUFTRAGPOSRAB_PHARMACYGROUPID); }
    void         SetPaymenttargetno(short t) { s.PAYMENTTARGETNO = t; }
    void         SetDiscountvalpctman(double t) { s.DISCOUNTVALPCTMAN = t; }
    void         SetSurchargepct(double t) { s.SURCHARGEPCT = t; }
    void         SetDiscountcategory(short t) { s.DISCOUNTCATEGORY = t; }
    void         SetInternaldiscountflag(short t) { s.INTERNALDISCOUNTFLAG = t; }
    void         SetRefundvaluepct(double t) { s.REFUNDVALUEPCT = t; }
    void         SetFixedprice(double t) { s.FIXEDPRICE = t; }
    void         SetDiscountcalcfrom(short t) { s.DISCOUNTCALCFROM = t; }
    void         SetDiscountapplyto(short t) { s.DISCOUNTAPPLYTO = t; }

    void         SetStruct(const kdauftragposrabS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CKDAUFTRAGPOSRAB() {
        ::buf_default((void *)&s, KDAUFTRAGPOSRAB_BES, KDAUFTRAGPOSRAB_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CKDAUFTRAGPOSRAB() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, KDAUFTRAGPOSRAB_BES, KDAUFTRAGPOSRAB_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, KDAUFTRAGPOSRAB_BES, (int)KDAUFTRAGPOSRAB_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, KDAUFTRAGPOSRAB_BES, (int)KDAUFTRAGPOSRAB_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_KDAUFTRAGPOSRAB & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.PHARMACYGROUPID);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, KDAUFTRAGPOSRAB_BES, (int)KDAUFTRAGPOSRAB_ANZ, error_msg);
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
/* CreateSqlStatement of KDAUFTRAGPOSRAB **************************************/

 #define KDAUFTRAGPOSRAB_CREATE(x) EXEC SQL create table x (\
         KDAUFTRAGNR integer default 0 not null,\
         POSNR integer default 0 not null,\
         DISCOUNTTYPE smallint default 0 not null,\
         DISCOUNTVALUEPCT decimal(5,2) default 0 not null,\
         PHARMACYGROUPID char(3) default " " not null,\
         PAYMENTTARGETNO smallint default 0 not null,\
         DISCOUNTVALPCTMAN decimal(5,2) default 0 not null,\
         SURCHARGEPCT decimal(5,2) default 0 not null,\
         DISCOUNTCATEGORY smallint default 0 not null,\
         INTERNALDISCOUNTFLAG smallint default 0 not null,\
         REFUNDVALUEPCT decimal(5,2) default 0 not null,\
         FIXEDPRICE decimal(9,2) default 0 not null,\
         DISCOUNTCALCFROM smallint default 0 not null,\
         DISCOUNTAPPLYTO smallint default 1 not null) in ksc extent size 784 next size 80 lock mode row;



/* CreateIndexStatement of KDAUFTRAGPOSRAB ************************************/

 #define KDAUFTRAGPOSRAB_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_kdaufposrab_1 on _X_(\
              kdauftragnr,\
              posnr,\
              DiscountType,\
              paymenttargetno ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of KDAUFTRAGPOSRAB ************************************/

 #define KDAUFTRAGPOSRAB_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_kdaufposrab_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
