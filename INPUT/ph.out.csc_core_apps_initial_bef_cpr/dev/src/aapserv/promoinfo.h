#ifndef __PP_PROMOINFO_H_
#define __PP_PROMOINFO_H_

/******************************************************************************/
/* c:\git\pharmos.outbound.csc_core_applications\dev\src\aapserv\PromoInfo ****/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of CHECKPROMOSCALE *******************************************/

#define L_CHECKPROMOSCALE_BASEPROMOTION 11
#define L_CHECKPROMOSCALE_PROMOTION_NO 6

/* Length-Define of PROMOQUOTAANZ *********************************************/

#define L_PROMOQUOTAANZ_BRANCHNO 6
#define L_PROMOQUOTAANZ_PROMOTION_NO 6
#define L_PROMOQUOTAANZ_NAME 30
#define L_PROMOQUOTAANZ_BRANCHQUOTAQTY 11
#define L_PROMOQUOTAANZ_CUSTOMERQUOTAQTY 11
#define L_PROMOQUOTAANZ_SOLDQTYBRANCH 11
#define L_PROMOQUOTAANZ_ARTICLENO 11
#define L_PROMOQUOTAANZ_CUSTOMERMINQTY 11

/* Length-Define of PROMOQUOTACHECK *******************************************/

#define L_PROMOQUOTACHECK_BRANCHNO 6
#define L_PROMOQUOTACHECK_PROMOTION_NO 6
#define L_PROMOQUOTACHECK_BRANCHQUOTAQTY 11
#define L_PROMOQUOTACHECK_CUSTOMERQUOTAQTY 11
#define L_PROMOQUOTACHECK_SOLDQTYCST 11
#define L_PROMOQUOTACHECK_SOLDQTYBRANCH 11
#define L_PROMOQUOTACHECK_CUSTOMERNO 11
#define L_PROMOQUOTACHECK_ARTICLENO 11
#define L_PROMOQUOTACHECK_CUSTOMERMINQTY 11

/* Length-Define of PROMOQUOTACSTANZ ******************************************/

#define L_PROMOQUOTACSTANZ_BRANCHNO 6
#define L_PROMOQUOTACSTANZ_PROMOTION_NO 6
#define L_PROMOQUOTACSTANZ_NAME 30
#define L_PROMOQUOTACSTANZ_CUSTOMERQUOTAQTY 11
#define L_PROMOQUOTACSTANZ_SOLDQTYCST 11
#define L_PROMOQUOTACSTANZ_CUSTOMERNO 11
#define L_PROMOQUOTACSTANZ_ARTICLENO 11
#define L_PROMOQUOTACSTANZ_NAMEAPO 40
#define L_PROMOQUOTACSTANZ_ORT 30

/* SqlDefine of CHECKPROMOSCALE ***********************************************/


#define CHECKPROMOSCALE_PLISTE \
        "PROMOTIONSCALE.BASEPROMOTION,"\
        "PROMOTIONSCALE.PROMOTION_NO"

/* SqlDefine of PROMOQUOTAANZ *************************************************/


#define PROMOQUOTAANZ_PLISTE \
        "PROMOTIONQUOTA.BRANCHNO,"\
        "PROMOTIONQUOTA.PROMOTION_NO,"\
        "PROMOTIONS.NAME,"\
        "PROMOTIONQUOTA.BRANCHQUOTAQTY,"\
        "PROMOTIONQUOTA.CUSTOMERQUOTAQTY,"\
        "PROMOTIONQUOTA.SOLDQTYBRANCH,"\
        "PROMOTIONQUOTA.ARTICLENO,"\
        "PROMOTIONQUOTA.CUSTOMERMINQTY"

/* SqlDefine of PROMOQUOTACHECK ***********************************************/


#define PROMOQUOTACHECK_PLISTE \
        "PROMOTIONQUOTA.BRANCHNO,"\
        "PROMOTIONQUOTA.PROMOTION_NO,"\
        "PROMOTIONQUOTA.BRANCHQUOTAQTY,"\
        "PROMOTIONQUOTA.CUSTOMERQUOTAQTY,"\
        "PROMOTIONQUOTACST.SOLDQTYCST,"\
        "PROMOTIONQUOTA.SOLDQTYBRANCH,"\
        "PROMOTIONQUOTACST.CUSTOMERNO,"\
        "PROMOTIONQUOTA.ARTICLENO,"\
        "PROMOTIONQUOTA.CUSTOMERMINQTY"

/* SqlDefine of PROMOQUOTACSTANZ **********************************************/


#define PROMOQUOTACSTANZ_PLISTE \
        "PROMOTIONQUOTACST.BRANCHNO,"\
        "PROMOTIONQUOTACST.PROMOTION_NO,"\
        "PROMOTIONS.NAME,"\
        "PROMOTIONQUOTACST.CUSTOMERQUOTAQTY,"\
        "PROMOTIONQUOTACST.SOLDQTYCST,"\
        "PROMOTIONQUOTACST.CUSTOMERNO,"\
        "PROMOTIONQUOTACST.ARTICLENO,"\
        "KUNDE.NAMEAPO,"\
        "KUNDE.ORT"

/* SqlDefine of CHECKPROMOSCALE ***********************************************/


#define CHECKPROMOSCALE_UPDLISTE \
        "BASEPROMOTION=?,"\
        "PROMOTION_NO=?"
/* SqlDefine of PROMOQUOTAANZ *************************************************/


#define PROMOQUOTAANZ_UPDLISTE \
        "BRANCHNO=?,"\
        "PROMOTION_NO=?,"\
        "NAME=?,"\
        "BRANCHQUOTAQTY=?,"\
        "CUSTOMERQUOTAQTY=?,"\
        "SOLDQTYBRANCH=?,"\
        "ARTICLENO=?,"\
        "CUSTOMERMINQTY=?"
/* SqlDefine of PROMOQUOTACHECK ***********************************************/


#define PROMOQUOTACHECK_UPDLISTE \
        "BRANCHNO=?,"\
        "PROMOTION_NO=?,"\
        "BRANCHQUOTAQTY=?,"\
        "CUSTOMERQUOTAQTY=?,"\
        "SOLDQTYCST=?,"\
        "SOLDQTYBRANCH=?,"\
        "CUSTOMERNO=?,"\
        "ARTICLENO=?,"\
        "CUSTOMERMINQTY=?"
/* SqlDefine of PROMOQUOTACSTANZ **********************************************/


#define PROMOQUOTACSTANZ_UPDLISTE \
        "BRANCHNO=?,"\
        "PROMOTION_NO=?,"\
        "NAME=?,"\
        "CUSTOMERQUOTAQTY=?,"\
        "SOLDQTYCST=?,"\
        "CUSTOMERNO=?,"\
        "ARTICLENO=?,"\
        "NAMEAPO=?,"\
        "ORT=?"
/* SqlMacros-Define of CHECKPROMOSCALE ****************************************/

#define CHECKPROMOSCALE_ZEIGER(x) \
        :x->BASEPROMOTION,\
        :x->PROMOTION_NO
#define CHECKPROMOSCALE_ZEIGERSEL(x) \
        :x->BASEPROMOTION,\
        :x->PROMOTION_NO

/* SqlMacros-Define of PROMOQUOTAANZ ******************************************/

#define PROMOQUOTAANZ_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->PROMOTION_NO,\
        :x->NAME,\
        :x->BRANCHQUOTAQTY,\
        :x->CUSTOMERQUOTAQTY,\
        :x->SOLDQTYBRANCH,\
        :x->ARTICLENO,\
        :x->CUSTOMERMINQTY
#define PROMOQUOTAANZ_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->PROMOTION_NO,\
        :x->NAME,\
        :x->BRANCHQUOTAQTY,\
        :x->CUSTOMERQUOTAQTY,\
        :x->SOLDQTYBRANCH,\
        :x->ARTICLENO,\
        :x->CUSTOMERMINQTY

/* SqlMacros-Define of PROMOQUOTACHECK ****************************************/

#define PROMOQUOTACHECK_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->PROMOTION_NO,\
        :x->BRANCHQUOTAQTY,\
        :x->CUSTOMERQUOTAQTY,\
        :x->SOLDQTYCST,\
        :x->SOLDQTYBRANCH,\
        :x->CUSTOMERNO,\
        :x->ARTICLENO,\
        :x->CUSTOMERMINQTY
#define PROMOQUOTACHECK_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->PROMOTION_NO,\
        :x->BRANCHQUOTAQTY,\
        :x->CUSTOMERQUOTAQTY,\
        :x->SOLDQTYCST,\
        :x->SOLDQTYBRANCH,\
        :x->CUSTOMERNO,\
        :x->ARTICLENO,\
        :x->CUSTOMERMINQTY

/* SqlMacros-Define of PROMOQUOTACSTANZ ***************************************/

#define PROMOQUOTACSTANZ_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->PROMOTION_NO,\
        :x->NAME,\
        :x->CUSTOMERQUOTAQTY,\
        :x->SOLDQTYCST,\
        :x->CUSTOMERNO,\
        :x->ARTICLENO,\
        :x->NAMEAPO,\
        :x->ORT
#define PROMOQUOTACSTANZ_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->PROMOTION_NO,\
        :x->NAME,\
        :x->CUSTOMERQUOTAQTY,\
        :x->SOLDQTYCST,\
        :x->CUSTOMERNO,\
        :x->ARTICLENO,\
        :x->NAMEAPO,\
        :x->ORT

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define CHECKPROMOSCALE_H
#define CHECKPROMOSCALE_ANZ ( sizeof(CHECKPROMOSCALE_BES) / sizeof(struct buf_desc) )
#define PROMOQUOTAANZ_H
#define PROMOQUOTAANZ_ANZ ( sizeof(PROMOQUOTAANZ_BES) / sizeof(struct buf_desc) )
#define PROMOQUOTACHECK_H
#define PROMOQUOTACHECK_ANZ ( sizeof(PROMOQUOTACHECK_BES) / sizeof(struct buf_desc) )
#define PROMOQUOTACSTANZ_H
#define PROMOQUOTACSTANZ_ANZ ( sizeof(PROMOQUOTACSTANZ_BES) / sizeof(struct buf_desc) )
#endif

#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of CHECKPROMOSCALE *****************************************/

#ifndef TRANSCLASS
typedef struct N_CHECKPROMOSCALE {
    long BASEPROMOTION;
    short PROMOTION_NO;
} checkpromoscaleS;
#else /* TRANSCLASS */
typedef struct N_CHECKPROMOSCALE {
    long BASEPROMOTION;
    short PROMOTION_NO;

    bool operator == (const N_CHECKPROMOSCALE& right) const {
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
} checkpromoscaleS;
#endif /* TRANSCLASS */

/* original struct of PROMOQUOTAANZ *******************************************/

#ifndef TRANSCLASS
typedef struct N_PROMOQUOTAANZ {
    short BRANCHNO;
    short PROMOTION_NO;
    char NAME[31];
    long BRANCHQUOTAQTY;
    long CUSTOMERQUOTAQTY;
    long SOLDQTYBRANCH;
    long ARTICLENO;
    long CUSTOMERMINQTY;
    long FETCH_REL;
} promoquotaanzS;
#else /* TRANSCLASS */
typedef struct N_PROMOQUOTAANZ {
    short BRANCHNO;
    short PROMOTION_NO;
    char NAME[31];
    long BRANCHQUOTAQTY;
    long CUSTOMERQUOTAQTY;
    long SOLDQTYBRANCH;
    long ARTICLENO;
    long CUSTOMERMINQTY;
    long FETCH_REL;
    bool operator == (const N_PROMOQUOTAANZ& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            PROMOTION_NO == right.PROMOTION_NO &&
            !strcmp(NAME, right.NAME) &&
            BRANCHQUOTAQTY == right.BRANCHQUOTAQTY &&
            CUSTOMERQUOTAQTY == right.CUSTOMERQUOTAQTY &&
            SOLDQTYBRANCH == right.SOLDQTYBRANCH &&
            ARTICLENO == right.ARTICLENO &&
            CUSTOMERMINQTY == right.CUSTOMERMINQTY
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        PROMOTION_NO = 0;
        strcpy(NAME, " " );
        BRANCHQUOTAQTY = 0;
        CUSTOMERQUOTAQTY = 0;
        SOLDQTYBRANCH = 0;
        ARTICLENO = 0;
        CUSTOMERMINQTY = 0;
#endif
    }
} promoquotaanzS;
#endif /* TRANSCLASS */

/* original struct of PROMOQUOTACHECK *****************************************/

#ifndef TRANSCLASS
typedef struct N_PROMOQUOTACHECK {
    short BRANCHNO;
    short PROMOTION_NO;
    long BRANCHQUOTAQTY;
    long CUSTOMERQUOTAQTY;
    long SOLDQTYCST;
    long SOLDQTYBRANCH;
    long CUSTOMERNO;
    long ARTICLENO;
    long CUSTOMERMINQTY;
} promoquotacheckS;
#else /* TRANSCLASS */
typedef struct N_PROMOQUOTACHECK {
    short BRANCHNO;
    short PROMOTION_NO;
    long BRANCHQUOTAQTY;
    long CUSTOMERQUOTAQTY;
    long SOLDQTYCST;
    long SOLDQTYBRANCH;
    long CUSTOMERNO;
    long ARTICLENO;
    long CUSTOMERMINQTY;

    bool operator == (const N_PROMOQUOTACHECK& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            PROMOTION_NO == right.PROMOTION_NO &&
            BRANCHQUOTAQTY == right.BRANCHQUOTAQTY &&
            CUSTOMERQUOTAQTY == right.CUSTOMERQUOTAQTY &&
            SOLDQTYCST == right.SOLDQTYCST &&
            SOLDQTYBRANCH == right.SOLDQTYBRANCH &&
            CUSTOMERNO == right.CUSTOMERNO &&
            ARTICLENO == right.ARTICLENO &&
            CUSTOMERMINQTY == right.CUSTOMERMINQTY
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        PROMOTION_NO = 0;
        BRANCHQUOTAQTY = 0;
        CUSTOMERQUOTAQTY = 0;
        SOLDQTYCST = 0;
        SOLDQTYBRANCH = 0;
        CUSTOMERNO = 0;
        ARTICLENO = 0;
        CUSTOMERMINQTY = 0;
#endif
    }
} promoquotacheckS;
#endif /* TRANSCLASS */

/* original struct of PROMOQUOTACSTANZ ****************************************/

#ifndef TRANSCLASS
typedef struct N_PROMOQUOTACSTANZ {
    short BRANCHNO;
    short PROMOTION_NO;
    char NAME[31];
    long CUSTOMERQUOTAQTY;
    long SOLDQTYCST;
    long CUSTOMERNO;
    long ARTICLENO;
    char NAMEAPO[41];
    char ORT[31];
    long FETCH_REL;
} promoquotacstanzS;
#else /* TRANSCLASS */
typedef struct N_PROMOQUOTACSTANZ {
    short BRANCHNO;
    short PROMOTION_NO;
    char NAME[31];
    long CUSTOMERQUOTAQTY;
    long SOLDQTYCST;
    long CUSTOMERNO;
    long ARTICLENO;
    char NAMEAPO[41];
    char ORT[31];
    long FETCH_REL;
    bool operator == (const N_PROMOQUOTACSTANZ& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            PROMOTION_NO == right.PROMOTION_NO &&
            !strcmp(NAME, right.NAME) &&
            CUSTOMERQUOTAQTY == right.CUSTOMERQUOTAQTY &&
            SOLDQTYCST == right.SOLDQTYCST &&
            CUSTOMERNO == right.CUSTOMERNO &&
            ARTICLENO == right.ARTICLENO &&
            !strcmp(NAMEAPO, right.NAMEAPO) &&
            !strcmp(ORT, right.ORT)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        PROMOTION_NO = 0;
        strcpy(NAME, " " );
        CUSTOMERQUOTAQTY = 0;
        SOLDQTYCST = 0;
        CUSTOMERNO = 0;
        ARTICLENO = 0;
        strcpy(NAMEAPO, " " );
        strcpy(ORT, " " );
#endif
    }
} promoquotacstanzS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of CHECKPROMOSCALE *****************************/

struct C_CHECKPROMOSCALE {
    long BASEPROMOTION;
    short PROMOTION_NO;
};
/* Structur with real chartype of PROMOQUOTAANZ *******************************/

struct C_PROMOQUOTAANZ {
    short BRANCHNO;
    short PROMOTION_NO;
    char NAME[31];
    long BRANCHQUOTAQTY;
    long CUSTOMERQUOTAQTY;
    long SOLDQTYBRANCH;
    long ARTICLENO;
    long CUSTOMERMINQTY;
    long FETCH_REL;
};
/* Structur with real chartype of PROMOQUOTACHECK *****************************/

struct C_PROMOQUOTACHECK {
    short BRANCHNO;
    short PROMOTION_NO;
    long BRANCHQUOTAQTY;
    long CUSTOMERQUOTAQTY;
    long SOLDQTYCST;
    long SOLDQTYBRANCH;
    long CUSTOMERNO;
    long ARTICLENO;
    long CUSTOMERMINQTY;
};
/* Structur with real chartype of PROMOQUOTACSTANZ ****************************/

struct C_PROMOQUOTACSTANZ {
    short BRANCHNO;
    short PROMOTION_NO;
    char NAME[31];
    long CUSTOMERQUOTAQTY;
    long SOLDQTYCST;
    long CUSTOMERNO;
    long ARTICLENO;
    char NAMEAPO[41];
    char ORT[31];
    long FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of CHECKPROMOSCALE ***************************/

struct I_CHECKPROMOSCALE {
    short BASEPROMOTION;
    short PROMOTION_NO;
};
/* Sizetype  Structur (buf_desc) of PROMOQUOTAANZ *****************************/

struct I_PROMOQUOTAANZ {
    short BRANCHNO;
    short PROMOTION_NO;
    short NAME;
    short BRANCHQUOTAQTY;
    short CUSTOMERQUOTAQTY;
    short SOLDQTYBRANCH;
    short ARTICLENO;
    short CUSTOMERMINQTY;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of PROMOQUOTACHECK ***************************/

struct I_PROMOQUOTACHECK {
    short BRANCHNO;
    short PROMOTION_NO;
    short BRANCHQUOTAQTY;
    short CUSTOMERQUOTAQTY;
    short SOLDQTYCST;
    short SOLDQTYBRANCH;
    short CUSTOMERNO;
    short ARTICLENO;
    short CUSTOMERMINQTY;
};
/* Sizetype  Structur (buf_desc) of PROMOQUOTACSTANZ **************************/

struct I_PROMOQUOTACSTANZ {
    short BRANCHNO;
    short PROMOTION_NO;
    short NAME;
    short CUSTOMERQUOTAQTY;
    short SOLDQTYCST;
    short CUSTOMERNO;
    short ARTICLENO;
    short NAMEAPO;
    short ORT;
    short FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CHECKPROMOSCALE *************************************/

#if defined (BUF_DESC)
static struct buf_desc CHECKPROMOSCALE_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CHECKPROMOSCALE_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* Structur (buf_desc) of PROMOQUOTAANZ ***************************************/

#if defined (BUF_DESC)
static struct buf_desc PROMOQUOTAANZ_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc PROMOQUOTAANZ_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of PROMOQUOTACHECK *************************************/

#if defined (BUF_DESC)
static struct buf_desc PROMOQUOTACHECK_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc PROMOQUOTACHECK_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of PROMOQUOTACSTANZ ************************************/

#if defined (BUF_DESC)
static struct buf_desc PROMOQUOTACSTANZ_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 40, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc PROMOQUOTACSTANZ_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 40, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* FunctionNumber-Define of CheckPromoScale ***********************************/

#define CHECKPROMOSCALE_PROMOSCALEEXIST 1641

/* FunctionNumber-Define of PromoQuotaAnz *************************************/

#define PROMOQUOTAANZ_SELLIST 1559
#define PROMOQUOTAANZ_SELQUOTA 1563
#define PROMOQUOTAANZ_SELQUOTAPZN 1576

/* FunctionNumber-Define of PromoQuotaCheck ***********************************/

#define PROMOQUOTACHECK_SELQUOTA 1589

/* FunctionNumber-Define of PromoQuotaCstAnz **********************************/

#define PROMOQUOTACSTANZ_SELLIST 1562
#define PROMOQUOTACSTANZ_SELLISTCST 1560
#define PROMOQUOTACSTANZ_SELLISTPROMO 1561
#define PROMOQUOTACSTANZ_SELQUOTA 1564

#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of CheckPromoScale *******************************/

#define PromoScaleExist 1641

/* Old-FunctionNumber-Define of PromoQuotaAnz *********************************/

#define SelList 1559
#define SelQuota 1563
#define SelQuotaPzn 1576

/* Old-FunctionNumber-Define of PromoQuotaCheck *******************************/

#define SelQuota 1589

/* Old-FunctionNumber-Define of PromoQuotaCstAnz ******************************/

#define SelList 1562
#define SelListCst 1560
#define SelListPromo 1561
#define SelQuota 1564

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

class CCHECKPROMOSCALE : public ppDadeVirtual {
public:
    checkpromoscaleS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<checkpromoscaleS> lst; // class list

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
                     vector< checkpromoscaleS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     checkpromoscaleS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< checkpromoscaleS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<checkpromoscaleS>::iterator
                 beginList() { return lst.begin(); }
    vector<checkpromoscaleS>::iterator
                 endList  () { return lst.end  (); }

    long         GetBasepromotion() const { return s.BASEPROMOTION; }
    short        GetPromotion_no() const { return s.PROMOTION_NO; }

    const checkpromoscaleS &
                 GetStruct() const { return s; }
    void         SetBasepromotion(long t) { s.BASEPROMOTION = t; }
    void         SetPromotion_no(short t) { s.PROMOTION_NO = t; }

    void         SetStruct(const checkpromoscaleS & t) { s = t; }

    int          PromoScaleExist(int pos = 0) { int ret = UniqueServerCall(1641, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCHECKPROMOSCALE() {
        ::buf_default((void *)&s, CHECKPROMOSCALE_BES, CHECKPROMOSCALE_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCHECKPROMOSCALE() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CHECKPROMOSCALE_BES, CHECKPROMOSCALE_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1641 ) return UniqueServerCall(1641, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CHECKPROMOSCALE & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CHECKPROMOSCALE_BES, (int)CHECKPROMOSCALE_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CPROMOQUOTAANZ : public ppDadeVirtual {
public:
    promoquotaanzS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<promoquotaanzS> lst; // class list

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
                     vector< promoquotaanzS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     promoquotaanzS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< promoquotaanzS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<promoquotaanzS>::iterator
                 beginList() { return lst.begin(); }
    vector<promoquotaanzS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    short        GetPromotion_no() const { return s.PROMOTION_NO; }
    const char*  GetName(ppString & t) const { t = s.NAME; t.erasespace(ppString::END); return t.c_str(); }
    long         GetBranchquotaqty() const { return s.BRANCHQUOTAQTY; }
    long         GetCustomerquotaqty() const { return s.CUSTOMERQUOTAQTY; }
    long         GetSoldqtybranch() const { return s.SOLDQTYBRANCH; }
    long         GetArticleno() const { return s.ARTICLENO; }
    long         GetCustomerminqty() const { return s.CUSTOMERMINQTY; }

    const promoquotaanzS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetPromotion_no(short t) { s.PROMOTION_NO = t; }
    void         SetName(const ppString & t) { ppGStrCopy(s.NAME, t.c_str(), L_PROMOQUOTAANZ_NAME); }
    void         SetBranchquotaqty(long t) { s.BRANCHQUOTAQTY = t; }
    void         SetCustomerquotaqty(long t) { s.CUSTOMERQUOTAQTY = t; }
    void         SetSoldqtybranch(long t) { s.SOLDQTYBRANCH = t; }
    void         SetArticleno(long t) { s.ARTICLENO = t; }
    void         SetCustomerminqty(long t) { s.CUSTOMERMINQTY = t; }

    void         SetStruct(const promoquotaanzS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1559, FetchRel, pos); return ret; }
    int          SelQuota(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1563, FetchRel, pos); return ret; }
    int          SelQuotaPzn(int pos = 0) { int ret = UniqueServerCall(1576, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CPROMOQUOTAANZ() {
        ::buf_default((void *)&s, PROMOQUOTAANZ_BES, PROMOQUOTAANZ_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CPROMOQUOTAANZ() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, PROMOQUOTAANZ_BES, PROMOQUOTAANZ_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, PROMOQUOTAANZ_BES, (int)PROMOQUOTAANZ_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1559 ) return CursorServerCall(1559, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1563 ) return CursorServerCall(1563, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1576 ) return UniqueServerCall(1576, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_PROMOQUOTAANZ & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.NAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, PROMOQUOTAANZ_BES, (int)PROMOQUOTAANZ_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CPROMOQUOTAANZ c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, PROMOQUOTAANZ_BES, (int)PROMOQUOTAANZ_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CPROMOQUOTACHECK : public ppDadeVirtual {
public:
    promoquotacheckS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<promoquotacheckS> lst; // class list

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
                     vector< promoquotacheckS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     promoquotacheckS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< promoquotacheckS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<promoquotacheckS>::iterator
                 beginList() { return lst.begin(); }
    vector<promoquotacheckS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    short        GetPromotion_no() const { return s.PROMOTION_NO; }
    long         GetBranchquotaqty() const { return s.BRANCHQUOTAQTY; }
    long         GetCustomerquotaqty() const { return s.CUSTOMERQUOTAQTY; }
    long         GetSoldqtycst() const { return s.SOLDQTYCST; }
    long         GetSoldqtybranch() const { return s.SOLDQTYBRANCH; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    long         GetArticleno() const { return s.ARTICLENO; }
    long         GetCustomerminqty() const { return s.CUSTOMERMINQTY; }

    const promoquotacheckS &
                 GetStruct() const { return s; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetPromotion_no(short t) { s.PROMOTION_NO = t; }
    void         SetBranchquotaqty(long t) { s.BRANCHQUOTAQTY = t; }
    void         SetCustomerquotaqty(long t) { s.CUSTOMERQUOTAQTY = t; }
    void         SetSoldqtycst(long t) { s.SOLDQTYCST = t; }
    void         SetSoldqtybranch(long t) { s.SOLDQTYBRANCH = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetArticleno(long t) { s.ARTICLENO = t; }
    void         SetCustomerminqty(long t) { s.CUSTOMERMINQTY = t; }

    void         SetStruct(const promoquotacheckS & t) { s = t; }

    int          SelQuota(int pos = 0) { int ret = UniqueServerCall(1589, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CPROMOQUOTACHECK() {
        ::buf_default((void *)&s, PROMOQUOTACHECK_BES, PROMOQUOTACHECK_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CPROMOQUOTACHECK() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, PROMOQUOTACHECK_BES, PROMOQUOTACHECK_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1589 ) return UniqueServerCall(1589, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_PROMOQUOTACHECK & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, PROMOQUOTACHECK_BES, (int)PROMOQUOTACHECK_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CPROMOQUOTACSTANZ : public ppDadeVirtual {
public:
    promoquotacstanzS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<promoquotacstanzS> lst; // class list

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
                     vector< promoquotacstanzS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     promoquotacstanzS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< promoquotacstanzS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<promoquotacstanzS>::iterator
                 beginList() { return lst.begin(); }
    vector<promoquotacstanzS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    short        GetPromotion_no() const { return s.PROMOTION_NO; }
    const char*  GetName(ppString & t) const { t = s.NAME; t.erasespace(ppString::END); return t.c_str(); }
    long         GetCustomerquotaqty() const { return s.CUSTOMERQUOTAQTY; }
    long         GetSoldqtycst() const { return s.SOLDQTYCST; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    long         GetArticleno() const { return s.ARTICLENO; }
    const char*  GetNameapo(ppString & t) const { t = s.NAMEAPO; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetOrt(ppString & t) const { t = s.ORT; t.erasespace(ppString::END); return t.c_str(); }

    const promoquotacstanzS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetPromotion_no(short t) { s.PROMOTION_NO = t; }
    void         SetName(const ppString & t) { ppGStrCopy(s.NAME, t.c_str(), L_PROMOQUOTACSTANZ_NAME); }
    void         SetCustomerquotaqty(long t) { s.CUSTOMERQUOTAQTY = t; }
    void         SetSoldqtycst(long t) { s.SOLDQTYCST = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetArticleno(long t) { s.ARTICLENO = t; }
    void         SetNameapo(const ppString & t) { ppGStrCopy(s.NAMEAPO, t.c_str(), L_PROMOQUOTACSTANZ_NAMEAPO); }
    void         SetOrt(const ppString & t) { ppGStrCopy(s.ORT, t.c_str(), L_PROMOQUOTACSTANZ_ORT); }

    void         SetStruct(const promoquotacstanzS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1562, FetchRel, pos); return ret; }
    int          SelListCst(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1560, FetchRel, pos); return ret; }
    int          SelListPromo(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1561, FetchRel, pos); return ret; }
    int          SelQuota(int pos = 0) { int ret = UniqueServerCall(1564, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CPROMOQUOTACSTANZ() {
        ::buf_default((void *)&s, PROMOQUOTACSTANZ_BES, PROMOQUOTACSTANZ_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CPROMOQUOTACSTANZ() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, PROMOQUOTACSTANZ_BES, PROMOQUOTACSTANZ_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, PROMOQUOTACSTANZ_BES, (int)PROMOQUOTACSTANZ_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1562 ) return CursorServerCall(1562, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1560 ) return CursorServerCall(1560, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1561 ) return CursorServerCall(1561, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1564 ) return UniqueServerCall(1564, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_PROMOQUOTACSTANZ & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.NAME);
        ppGStripLast(d.NAMEAPO);
        ppGStripLast(d.ORT);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, PROMOQUOTACSTANZ_BES, (int)PROMOQUOTACSTANZ_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CPROMOQUOTACSTANZ c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, PROMOQUOTACSTANZ_BES, (int)PROMOQUOTACSTANZ_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};
#endif    // TRANSCLASS

#endif   // GUARD
