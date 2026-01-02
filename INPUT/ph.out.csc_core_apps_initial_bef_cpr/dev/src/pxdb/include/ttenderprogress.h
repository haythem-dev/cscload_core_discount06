#ifndef __PP_TENDERPROGRESS_H_
#define __PP_TENDERPROGRESS_H_

/******************************************************************************/
/* c:\prri\Headerfiles\TenderProgress *****************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of TENDERPROGRESS ********************************************/

#define L_TENDERPROGRESS_TENDERNO 11
#define L_TENDERPROGRESS_ARTICLENO 11
#define L_TENDERPROGRESS_KDAUFTRAGNR 11
#define L_TENDERPROGRESS_ORDERDATE 11
#define L_TENDERPROGRESS_DELIVERYQTY 11
#define L_TENDERPROGRESS_CHARGEDPRICE 9
#define N_TENDERPROGRESS_CHARGEDPRICE 2
#define L_TENDERPROGRESS_POSNR 11
#define L_TENDERPROGRESS_RETURNQTY 11
#define L_TENDERPROGRESS_ORDERTIME 11
#define L_TENDERPROGRESS_CUSTOMERNO 11
#define L_TENDERPROGRESS_AEP 9
#define N_TENDERPROGRESS_AEP 2
#define L_TENDERPROGRESS_BOOKINGTENDERNO 11
#define L_TENDERPROGRESS_INVOICENO 11
#define L_TENDERPROGRESS_INVOICEDATE 11
#define L_TENDERPROGRESS_KDAUFTRAGART 2
#define L_TENDERPROGRESS_GEP 9
#define N_TENDERPROGRESS_GEP 2
#define L_TENDERPROGRESS_INVOICETIME 11
#define L_TENDERPROGRESS_BRANCHNO 6
#define L_TENDERPROGRESS_DISCOUNTPCT 5
#define N_TENDERPROGRESS_DISCOUNTPCT 2
#define L_TENDERPROGRESS_CHANGEDATE 11

/* Length/Count-Define of TENDERPROGRESS **************************************/

#define LS_TENDERPROGRESS_TENDERNO 10 + 1
#define LS_TENDERPROGRESS_ARTICLENO 10 + 1
#define LS_TENDERPROGRESS_KDAUFTRAGNR 10 + 1
#define LS_TENDERPROGRESS_ORDERDATE 10 + 1
#define LS_TENDERPROGRESS_DELIVERYQTY 10 + 1
#define LS_TENDERPROGRESS_CHARGEDPRICE 9 + 2
#define LS_TENDERPROGRESS_POSNR 10 + 1
#define LS_TENDERPROGRESS_RETURNQTY 10 + 1
#define LS_TENDERPROGRESS_ORDERTIME 10 + 1
#define LS_TENDERPROGRESS_CUSTOMERNO 10 + 1
#define LS_TENDERPROGRESS_AEP 9 + 2
#define LS_TENDERPROGRESS_BOOKINGTENDERNO 10 + 1
#define LS_TENDERPROGRESS_INVOICENO 10 + 1
#define LS_TENDERPROGRESS_INVOICEDATE 10 + 1
#define LS_TENDERPROGRESS_KDAUFTRAGART 2 + 1
#define LS_TENDERPROGRESS_GEP 9 + 2
#define LS_TENDERPROGRESS_INVOICETIME 10 + 1
#define LS_TENDERPROGRESS_BRANCHNO 5 + 1
#define LS_TENDERPROGRESS_DISCOUNTPCT 5 + 2
#define LS_TENDERPROGRESS_CHANGEDATE 10 + 1

#define TENDERPROGRESSTENDERNO 0
#define TENDERPROGRESSARTICLENO 1
#define TENDERPROGRESSKDAUFTRAGNR 2
#define TENDERPROGRESSORDERDATE 3
#define TENDERPROGRESSDELIVERYQTY 4
#define TENDERPROGRESSCHARGEDPRICE 5
#define TENDERPROGRESSPOSNR 6
#define TENDERPROGRESSRETURNQTY 7
#define TENDERPROGRESSORDERTIME 8
#define TENDERPROGRESSCUSTOMERNO 9
#define TENDERPROGRESSAEP 10
#define TENDERPROGRESSBOOKINGTENDERNO 11
#define TENDERPROGRESSINVOICENO 12
#define TENDERPROGRESSINVOICEDATE 13
#define TENDERPROGRESSKDAUFTRAGART 14
#define TENDERPROGRESSGEP 15
#define TENDERPROGRESSINVOICETIME 16
#define TENDERPROGRESSBRANCHNO 17
#define TENDERPROGRESSDISCOUNTPCT 18
#define TENDERPROGRESSCHANGEDATE 19

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define TENDERPROGRESS_H
#define TENDERPROGRESS_ANZ ( sizeof(TENDERPROGRESS_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of TENDERPROGRESS ************************************************/

#define TENDERPROGRESS_LISTE \
        TENDERPROGRESS.TENDERNO,\
        TENDERPROGRESS.ARTICLENO,\
        TENDERPROGRESS.KDAUFTRAGNR,\
        TENDERPROGRESS.ORDERDATE,\
        TENDERPROGRESS.DELIVERYQTY,\
        TENDERPROGRESS.CHARGEDPRICE,\
        TENDERPROGRESS.POSNR,\
        TENDERPROGRESS.RETURNQTY,\
        TENDERPROGRESS.ORDERTIME,\
        TENDERPROGRESS.CUSTOMERNO,\
        TENDERPROGRESS.AEP,\
        TENDERPROGRESS.BOOKINGTENDERNO,\
        TENDERPROGRESS.INVOICENO,\
        TENDERPROGRESS.INVOICEDATE,\
        TENDERPROGRESS.KDAUFTRAGART,\
        TENDERPROGRESS.GEP,\
        TENDERPROGRESS.INVOICETIME,\
        TENDERPROGRESS.BRANCHNO,\
        TENDERPROGRESS.DISCOUNTPCT,\
        TENDERPROGRESS.CHANGEDATE
#define TENDERPROGRESS_LISTE_390 \
        TENDERNO,\
        ARTICLENO,\
        KDAUFTRAGNR,\
        ORDERDATE,\
        DELIVERYQTY,\
        CHARGEDPRICE,\
        POSNR,\
        RETURNQTY,\
        ORDERTIME,\
        CUSTOMERNO,\
        AEP,\
        BOOKINGTENDERNO,\
        INVOICENO,\
        INVOICEDATE,\
        KDAUFTRAGART,\
        GEP,\
        INVOICETIME,\
        BRANCHNO,\
        DISCOUNTPCT,\
        CHANGEDATE
#define TENDERPROGRESS_PLISTE \
        "TENDERPROGRESS.TENDERNO,"\
        "TENDERPROGRESS.ARTICLENO,"\
        "TENDERPROGRESS.KDAUFTRAGNR,"\
        "TENDERPROGRESS.ORDERDATE,"\
        "TENDERPROGRESS.DELIVERYQTY,"\
        "TENDERPROGRESS.CHARGEDPRICE,"\
        "TENDERPROGRESS.POSNR,"\
        "TENDERPROGRESS.RETURNQTY,"\
        "TENDERPROGRESS.ORDERTIME,"\
        "TENDERPROGRESS.CUSTOMERNO,"\
        "TENDERPROGRESS.AEP,"\
        "TENDERPROGRESS.BOOKINGTENDERNO,"\
        "TENDERPROGRESS.INVOICENO,"\
        "TENDERPROGRESS.INVOICEDATE,"\
        "TENDERPROGRESS.KDAUFTRAGART,"\
        "TENDERPROGRESS.GEP,"\
        "TENDERPROGRESS.INVOICETIME,"\
        "TENDERPROGRESS.BRANCHNO,"\
        "TENDERPROGRESS.DISCOUNTPCT,"\
        "TENDERPROGRESS.CHANGEDATE"
#define TENDERPROGRESS_PELISTE \
        "TENDERNO,"\
        "ARTICLENO,"\
        "KDAUFTRAGNR,"\
        "ORDERDATE,"\
        "DELIVERYQTY,"\
        "CHARGEDPRICE,"\
        "POSNR,"\
        "RETURNQTY,"\
        "ORDERTIME,"\
        "CUSTOMERNO,"\
        "AEP,"\
        "BOOKINGTENDERNO,"\
        "INVOICENO,"\
        "INVOICEDATE,"\
        "KDAUFTRAGART,"\
        "GEP,"\
        "INVOICETIME,"\
        "BRANCHNO,"\
        "DISCOUNTPCT,"\
        "CHANGEDATE"
#define TENDERPROGRESS_UPDLISTE \
        "TENDERNO=?,"\
        "ARTICLENO=?,"\
        "KDAUFTRAGNR=?,"\
        "ORDERDATE=?,"\
        "DELIVERYQTY=?,"\
        "CHARGEDPRICE=?,"\
        "POSNR=?,"\
        "RETURNQTY=?,"\
        "ORDERTIME=?,"\
        "CUSTOMERNO=?,"\
        "AEP=?,"\
        "BOOKINGTENDERNO=?,"\
        "INVOICENO=?,"\
        "INVOICEDATE=?,"\
        "KDAUFTRAGART=?,"\
        "GEP=?,"\
        "INVOICETIME=?,"\
        "BRANCHNO=?,"\
        "DISCOUNTPCT=?,"\
        "CHANGEDATE=?"
/* SqlMacros-Define of TENDERPROGRESS *****************************************/

#define TENDERPROGRESS_ZEIGER(x) \
        :x->TENDERNO,\
        :x->ARTICLENO,\
        :x->KDAUFTRAGNR,\
        :x->ORDERDATE,\
        :x->DELIVERYQTY,\
        :x->CHARGEDPRICE,\
        :x->POSNR,\
        :x->RETURNQTY,\
        :x->ORDERTIME,\
        :x->CUSTOMERNO,\
        :x->AEP,\
        :x->BOOKINGTENDERNO,\
        :x->INVOICENO,\
        :x->INVOICEDATE,\
        :x->KDAUFTRAGART,\
        :x->GEP,\
        :x->INVOICETIME,\
        :x->BRANCHNO,\
        :x->DISCOUNTPCT,\
        :x->CHANGEDATE
#define TENDERPROGRESS_ZEIGERSEL(x) \
        :x->TENDERNO,\
        :x->ARTICLENO,\
        :x->KDAUFTRAGNR,\
        :x->ORDERDATE,\
        :x->DELIVERYQTY,\
        :x->CHARGEDPRICE,\
        :x->POSNR,\
        :x->RETURNQTY,\
        :x->ORDERTIME,\
        :x->CUSTOMERNO,\
        :x->AEP,\
        :x->BOOKINGTENDERNO,\
        :x->INVOICENO,\
        :x->INVOICEDATE,\
        :x->KDAUFTRAGART,\
        :x->GEP,\
        :x->INVOICETIME,\
        :x->BRANCHNO,\
        :x->DISCOUNTPCT,\
        :x->CHANGEDATE
#define TENDERPROGRESS_UPDATE(x) \
        TENDERPROGRESS.TENDERNO=:x->TENDERNO,\
        TENDERPROGRESS.ARTICLENO=:x->ARTICLENO,\
        TENDERPROGRESS.KDAUFTRAGNR=:x->KDAUFTRAGNR,\
        TENDERPROGRESS.ORDERDATE=:x->ORDERDATE,\
        TENDERPROGRESS.DELIVERYQTY=:x->DELIVERYQTY,\
        TENDERPROGRESS.CHARGEDPRICE=:x->CHARGEDPRICE,\
        TENDERPROGRESS.POSNR=:x->POSNR,\
        TENDERPROGRESS.RETURNQTY=:x->RETURNQTY,\
        TENDERPROGRESS.ORDERTIME=:x->ORDERTIME,\
        TENDERPROGRESS.CUSTOMERNO=:x->CUSTOMERNO,\
        TENDERPROGRESS.AEP=:x->AEP,\
        TENDERPROGRESS.BOOKINGTENDERNO=:x->BOOKINGTENDERNO,\
        TENDERPROGRESS.INVOICENO=:x->INVOICENO,\
        TENDERPROGRESS.INVOICEDATE=:x->INVOICEDATE,\
        TENDERPROGRESS.KDAUFTRAGART=:x->KDAUFTRAGART,\
        TENDERPROGRESS.GEP=:x->GEP,\
        TENDERPROGRESS.INVOICETIME=:x->INVOICETIME,\
        TENDERPROGRESS.BRANCHNO=:x->BRANCHNO,\
        TENDERPROGRESS.DISCOUNTPCT=:x->DISCOUNTPCT,\
        TENDERPROGRESS.CHANGEDATE=:x->CHANGEDATE
/* SqlMacros390-Define of TENDERPROGRESS **************************************/

#define TENDERPROGRESS_ZEIGER_390 \
        :TENDERNO,\
        :ARTICLENO,\
        :KDAUFTRAGNR,\
        :ORDERDATE,\
        :DELIVERYQTY,\
        :CHARGEDPRICE,\
        :POSNR,\
        :RETURNQTY,\
        :ORDERTIME,\
        :CUSTOMERNO,\
        :AEP,\
        :BOOKINGTENDERNO,\
        :INVOICENO,\
        :INVOICEDATE,\
        :KDAUFTRAGART,\
        :GEP,\
        :INVOICETIME,\
        :BRANCHNO,\
        :DISCOUNTPCT,\
        :CHANGEDATE
#define TENDERPROGRESS_UPDATE_390 \
        TENDERNO=:TENDERNO,\
        ARTICLENO=:ARTICLENO,\
        KDAUFTRAGNR=:KDAUFTRAGNR,\
        ORDERDATE=:ORDERDATE,\
        DELIVERYQTY=:DELIVERYQTY,\
        CHARGEDPRICE=:CHARGEDPRICE,\
        POSNR=:POSNR,\
        RETURNQTY=:RETURNQTY,\
        ORDERTIME=:ORDERTIME,\
        CUSTOMERNO=:CUSTOMERNO,\
        AEP=:AEP,\
        BOOKINGTENDERNO=:BOOKINGTENDERNO,\
        INVOICENO=:INVOICENO,\
        INVOICEDATE=:INVOICEDATE,\
        KDAUFTRAGART=:KDAUFTRAGART,\
        GEP=:GEP,\
        INVOICETIME=:INVOICETIME,\
        BRANCHNO=:BRANCHNO,\
        DISCOUNTPCT=:DISCOUNTPCT,\
        CHANGEDATE=:CHANGEDATE
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of TENDERPROGRESS ******************************************/

#ifndef TRANSCLASS
typedef struct N_TENDERPROGRESS {
    long TENDERNO;
    long ARTICLENO;
    long KDAUFTRAGNR;
    long ORDERDATE;
    long DELIVERYQTY;
    double CHARGEDPRICE;
    long POSNR;
    long RETURNQTY;
    long ORDERTIME;
    long CUSTOMERNO;
    double AEP;
    long BOOKINGTENDERNO;
    long INVOICENO;
    long INVOICEDATE;
    char KDAUFTRAGART[3];
    double GEP;
    long INVOICETIME;
    short BRANCHNO;
    double DISCOUNTPCT;
    long CHANGEDATE;
} tenderprogressS;
#else /* TRANSCLASS */
typedef struct N_TENDERPROGRESS {
    long TENDERNO;
    long ARTICLENO;
    long KDAUFTRAGNR;
    long ORDERDATE;
    long DELIVERYQTY;
    double CHARGEDPRICE;
    long POSNR;
    long RETURNQTY;
    long ORDERTIME;
    long CUSTOMERNO;
    double AEP;
    long BOOKINGTENDERNO;
    long INVOICENO;
    long INVOICEDATE;
    char KDAUFTRAGART[3];
    double GEP;
    long INVOICETIME;
    short BRANCHNO;
    double DISCOUNTPCT;
    long CHANGEDATE;

    bool operator == (const N_TENDERPROGRESS& right) const {
        return (
            TENDERNO == right.TENDERNO &&
            ARTICLENO == right.ARTICLENO &&
            KDAUFTRAGNR == right.KDAUFTRAGNR &&
            ORDERDATE == right.ORDERDATE &&
            DELIVERYQTY == right.DELIVERYQTY &&
            CHARGEDPRICE == right.CHARGEDPRICE &&
            POSNR == right.POSNR &&
            RETURNQTY == right.RETURNQTY &&
            ORDERTIME == right.ORDERTIME &&
            CUSTOMERNO == right.CUSTOMERNO &&
            AEP == right.AEP &&
            BOOKINGTENDERNO == right.BOOKINGTENDERNO &&
            INVOICENO == right.INVOICENO &&
            INVOICEDATE == right.INVOICEDATE &&
            !strcmp(KDAUFTRAGART, right.KDAUFTRAGART) &&
            GEP == right.GEP &&
            INVOICETIME == right.INVOICETIME &&
            BRANCHNO == right.BRANCHNO &&
            DISCOUNTPCT == right.DISCOUNTPCT &&
            CHANGEDATE == right.CHANGEDATE
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        TENDERNO = 0;
        ARTICLENO = 0;
        KDAUFTRAGNR = 0;
        ORDERDATE = 0;
        DELIVERYQTY = 0;
        CHARGEDPRICE = 0;
        POSNR = 0;
        RETURNQTY = 0;
        ORDERTIME = 0;
        CUSTOMERNO = 0;
        AEP = 0;
        BOOKINGTENDERNO = 0;
        INVOICENO = 0;
        INVOICEDATE = 0;
        strcpy(KDAUFTRAGART, " " );
        GEP = 0;
        INVOICETIME = 0;
        BRANCHNO = 0;
        DISCOUNTPCT = 0;
        CHANGEDATE = 0;
#endif
    }
} tenderprogressS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of TENDERPROGRESS ************************************/

struct S_TENDERPROGRESS {
    char TENDERNO[11];
    char ARTICLENO[11];
    char KDAUFTRAGNR[11];
    char ORDERDATE[11];
    char DELIVERYQTY[11];
    char CHARGEDPRICE[9 + 2];
    char POSNR[11];
    char RETURNQTY[11];
    char ORDERTIME[11];
    char CUSTOMERNO[11];
    char AEP[9 + 2];
    char BOOKINGTENDERNO[11];
    char INVOICENO[11];
    char INVOICEDATE[11];
    char KDAUFTRAGART[2 + 1];
    char GEP[9 + 2];
    char INVOICETIME[11];
    char BRANCHNO[7];
    char DISCOUNTPCT[5 + 2];
    char CHANGEDATE[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of TENDERPROGRESS *******************/

struct O_TENDERPROGRESS {
    char TENDERNO[11];
    char ARTICLENO[11];
    char KDAUFTRAGNR[11];
    char ORDERDATE[11];
    char DELIVERYQTY[11];
    char CHARGEDPRICE[9];
    char POSNR[11];
    char RETURNQTY[11];
    char ORDERTIME[11];
    char CUSTOMERNO[11];
    char AEP[9];
    char BOOKINGTENDERNO[11];
    char INVOICENO[11];
    char INVOICEDATE[11];
    char KDAUFTRAGART[2];
    char GEP[9];
    char INVOICETIME[11];
    char BRANCHNO[7];
    char DISCOUNTPCT[5];
    char CHANGEDATE[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of TENDERPROGRESS ******************************/

struct C_TENDERPROGRESS {
    long TENDERNO;
    long ARTICLENO;
    long KDAUFTRAGNR;
    long ORDERDATE;
    long DELIVERYQTY;
    double CHARGEDPRICE;
    long POSNR;
    long RETURNQTY;
    long ORDERTIME;
    long CUSTOMERNO;
    double AEP;
    long BOOKINGTENDERNO;
    long INVOICENO;
    long INVOICEDATE;
    char KDAUFTRAGART[3];
    double GEP;
    long INVOICETIME;
    short BRANCHNO;
    double DISCOUNTPCT;
    long CHANGEDATE;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of TENDERPROGRESS ****************************/

struct I_TENDERPROGRESS {
    short TENDERNO;
    short ARTICLENO;
    short KDAUFTRAGNR;
    short ORDERDATE;
    short DELIVERYQTY;
    short CHARGEDPRICE;
    short POSNR;
    short RETURNQTY;
    short ORDERTIME;
    short CUSTOMERNO;
    short AEP;
    short BOOKINGTENDERNO;
    short INVOICENO;
    short INVOICEDATE;
    short KDAUFTRAGART;
    short GEP;
    short INVOICETIME;
    short BRANCHNO;
    short DISCOUNTPCT;
    short CHANGEDATE;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of TENDERPROGRESS **************************************/

#if defined (BUF_DESC)
static struct buf_desc TENDERPROGRESS_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 2, 0 },
   { TYP_D, 9, 2 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc TENDERPROGRESS_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 2, 0 },
   { TYP_D, 9, 2 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_L , 11, 0 },
};
#endif

/* description for datatypes of TENDERPROGRESS ********************************/

 #define TENDERPROGRESS_S390 \
         long TENDERNO; \
         long ARTICLENO; \
         long KDAUFTRAGNR; \
         long ORDERDATE; \
         long DELIVERYQTY; \
         double CHARGEDPRICE; \
         long POSNR; \
         long RETURNQTY; \
         long ORDERTIME; \
         long CUSTOMERNO; \
         double AEP; \
         long BOOKINGTENDERNO; \
         long INVOICENO; \
         long INVOICEDATE; \
         char KDAUFTRAGART[3]; \
         double GEP; \
         long INVOICETIME; \
         short BRANCHNO; \
         double DISCOUNTPCT; \
         long CHANGEDATE; \



/* Copy-Function Struct to single Data TENDERPROGRESS *************************/

 #define TENDERPROGRESS_S390_COPY_TO_SINGLE(_x_) \
         TENDERNO=_x_->TENDERNO;\
         ARTICLENO=_x_->ARTICLENO;\
         KDAUFTRAGNR=_x_->KDAUFTRAGNR;\
         ORDERDATE=_x_->ORDERDATE;\
         DELIVERYQTY=_x_->DELIVERYQTY;\
         CHARGEDPRICE=_x_->CHARGEDPRICE;\
         POSNR=_x_->POSNR;\
         RETURNQTY=_x_->RETURNQTY;\
         ORDERTIME=_x_->ORDERTIME;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
         AEP=_x_->AEP;\
         BOOKINGTENDERNO=_x_->BOOKINGTENDERNO;\
         INVOICENO=_x_->INVOICENO;\
         INVOICEDATE=_x_->INVOICEDATE;\
          strcpy(KDAUFTRAGART,_x_->KDAUFTRAGART);\
         GEP=_x_->GEP;\
         INVOICETIME=_x_->INVOICETIME;\
         BRANCHNO=_x_->BRANCHNO;\
         DISCOUNTPCT=_x_->DISCOUNTPCT;\
         CHANGEDATE=_x_->CHANGEDATE;\

 #define TENDERPROGRESS_S390_COPY_TO_STRUCT(_x_) \
          _x_->TENDERNO=TENDERNO;\
          _x_->ARTICLENO=ARTICLENO;\
          _x_->KDAUFTRAGNR=KDAUFTRAGNR;\
          _x_->ORDERDATE=ORDERDATE;\
          _x_->DELIVERYQTY=DELIVERYQTY;\
          _x_->CHARGEDPRICE=CHARGEDPRICE;\
          _x_->POSNR=POSNR;\
          _x_->RETURNQTY=RETURNQTY;\
          _x_->ORDERTIME=ORDERTIME;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->AEP=AEP;\
          _x_->BOOKINGTENDERNO=BOOKINGTENDERNO;\
          _x_->INVOICENO=INVOICENO;\
          _x_->INVOICEDATE=INVOICEDATE;\
          strcpy(_x_->KDAUFTRAGART,KDAUFTRAGART);\
          _x_->GEP=GEP;\
          _x_->INVOICETIME=INVOICETIME;\
          _x_->BRANCHNO=BRANCHNO;\
          _x_->DISCOUNTPCT=DISCOUNTPCT;\
          _x_->CHANGEDATE=CHANGEDATE;\



/* FunctionNumber-Define of TenderProgress ************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of TenderProgress ********************************/


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

class CTENDERPROGRESS : public ppDadeVirtual {
public:
    tenderprogressS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<tenderprogressS> lst; // class list

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
                     vector< tenderprogressS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     tenderprogressS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< tenderprogressS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<tenderprogressS>::iterator
                 beginList() { return lst.begin(); }
    vector<tenderprogressS>::iterator
                 endList  () { return lst.end  (); }

    long         GetTenderno() const { return s.TENDERNO; }
    long         GetArticleno() const { return s.ARTICLENO; }
    long         GetKdauftragnr() const { return s.KDAUFTRAGNR; }
    long         GetOrderdate() const { return s.ORDERDATE; }
    long         GetDeliveryqty() const { return s.DELIVERYQTY; }
    double       GetChargedprice() const { return s.CHARGEDPRICE; }
    long         GetPosnr() const { return s.POSNR; }
    long         GetReturnqty() const { return s.RETURNQTY; }
    long         GetOrdertime() const { return s.ORDERTIME; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    double       GetAep() const { return s.AEP; }
    long         GetBookingtenderno() const { return s.BOOKINGTENDERNO; }
    long         GetInvoiceno() const { return s.INVOICENO; }
    long         GetInvoicedate() const { return s.INVOICEDATE; }
    const char*  GetKdauftragart(ppString & t) const { t = s.KDAUFTRAGART; t.erasespace(ppString::END); return t.c_str(); }
    double       GetGep() const { return s.GEP; }
    long         GetInvoicetime() const { return s.INVOICETIME; }
    short        GetBranchno() const { return s.BRANCHNO; }
    double       GetDiscountpct() const { return s.DISCOUNTPCT; }
    long         GetChangedate() const { return s.CHANGEDATE; }

    const tenderprogressS &
                 GetStruct() const { return s; }
    void         SetTenderno(long t) { s.TENDERNO = t; }
    void         SetArticleno(long t) { s.ARTICLENO = t; }
    void         SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
    void         SetOrderdate(long t) { s.ORDERDATE = t; }
    void         SetDeliveryqty(long t) { s.DELIVERYQTY = t; }
    void         SetChargedprice(double t) { s.CHARGEDPRICE = t; }
    void         SetPosnr(long t) { s.POSNR = t; }
    void         SetReturnqty(long t) { s.RETURNQTY = t; }
    void         SetOrdertime(long t) { s.ORDERTIME = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetAep(double t) { s.AEP = t; }
    void         SetBookingtenderno(long t) { s.BOOKINGTENDERNO = t; }
    void         SetInvoiceno(long t) { s.INVOICENO = t; }
    void         SetInvoicedate(long t) { s.INVOICEDATE = t; }
    void         SetKdauftragart(const ppString & t) { ppGStrCopy(s.KDAUFTRAGART, t.c_str(), L_TENDERPROGRESS_KDAUFTRAGART); }
    void         SetGep(double t) { s.GEP = t; }
    void         SetInvoicetime(long t) { s.INVOICETIME = t; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetDiscountpct(double t) { s.DISCOUNTPCT = t; }
    void         SetChangedate(long t) { s.CHANGEDATE = t; }

    void         SetStruct(const tenderprogressS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CTENDERPROGRESS() {
        ::buf_default((void *)&s, TENDERPROGRESS_BES, TENDERPROGRESS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CTENDERPROGRESS() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, TENDERPROGRESS_BES, TENDERPROGRESS_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, TENDERPROGRESS_BES, (int)TENDERPROGRESS_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, TENDERPROGRESS_BES, (int)TENDERPROGRESS_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_TENDERPROGRESS & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.KDAUFTRAGART);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, TENDERPROGRESS_BES, (int)TENDERPROGRESS_ANZ, error_msg);
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
/* CreateSqlStatement of TENDERPROGRESS ***************************************/

 #define TENDERPROGRESS_CREATE(x) EXEC SQL create table x (\
         TENDERNO integer default 0 not null,\
         ARTICLENO integer default 0 not null,\
         KDAUFTRAGNR integer default 0 not null,\
         ORDERDATE integer default 0 not null,\
         DELIVERYQTY integer default 0 not null,\
         CHARGEDPRICE decimal(9,2) default 0 not null,\
         POSNR integer default 0 not null,\
         RETURNQTY integer default 0 not null,\
         ORDERTIME integer default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         AEP decimal(9,2) default 0 not null,\
         BOOKINGTENDERNO integer default 0 not null,\
         INVOICENO integer default 0 not null,\
         INVOICEDATE integer default 0 not null,\
         KDAUFTRAGART char(2) default " " not null,\
         GEP decimal(9,2) default 0 not null,\
         INVOICETIME integer default 0 not null,\
         BRANCHNO smallint default 0 not null,\
         DISCOUNTPCT decimal(5,2) default 0 not null,\
         CHANGEDATE integer default 0 not null) in ksc extent size 548 next size 56 lock mode row;



/* CreateIndexStatement of TENDERPROGRESS *************************************/

 #define TENDERPROGRESS_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_tenderprogress_1 on _X_(\
              TenderNo,\
              kdauftragnr,\
              posnr,\
              OrderDate,\
              ArticleNo ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index i_tenderprogress_2 on _X_(\
              TenderNo,\
              ArticleNo,\
              kdauftragnr,\
              OrderDate ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of TENDERPROGRESS *************************************/

 #define TENDERPROGRESS_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_tenderprogress_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_tenderprogress_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
