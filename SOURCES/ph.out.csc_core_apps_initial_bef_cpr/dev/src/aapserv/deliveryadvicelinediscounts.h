#ifndef __PP_DELIVERYADVICELINEDISCOUNTS_H_
#define __PP_DELIVERYADVICELINEDISCOUNTS_H_

/******************************************************************************/
/**/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of DELIVERYADVICELINEDISCOUNTS *******************************/

#define L_DELIVERYADVICELINEDISCOUNTS_BRANCHNO 6
#define L_DELIVERYADVICELINEDISCOUNTS_CUSTOMERNO 11
#define L_DELIVERYADVICELINEDISCOUNTS_DELIVERYADVICEDATE 11
#define L_DELIVERYADVICELINEDISCOUNTS_DELIVERYADVICENO 10
#define L_DELIVERYADVICELINEDISCOUNTS_DELIVERYADVICEPOSNO 11
#define L_DELIVERYADVICELINEDISCOUNTS_DISCOUNTMODE 6
#define L_DELIVERYADVICELINEDISCOUNTS_DISCOUNT 11
#define N_DELIVERYADVICELINEDISCOUNTS_DISCOUNT 2
#define L_DELIVERYADVICELINEDISCOUNTS_DAORIGIN 1
#define L_DELIVERYADVICELINEDISCOUNTS_DELETEREASON 6
#define L_DELIVERYADVICELINEDISCOUNTS_DADISCOUNTVALUE 11
#define N_DELIVERYADVICELINEDISCOUNTS_DADISCOUNTVALUE 2
#define L_DELIVERYADVICELINEDISCOUNTS_DISCOUNTTYPE 6
#define L_DELIVERYADVICELINEDISCOUNTS_HIERARCHY 6
#define L_DELIVERYADVICELINEDISCOUNTS_CALCULATIONBASIS 6
#define L_DELIVERYADVICELINEDISCOUNTS_DISCOUNTMODENAME 30

/* Length/Count-Define of DELIVERYADVICELINEDISCOUNTS *************************/

#define LS_DELIVERYADVICELINEDISCOUNTS_BRANCHNO 5 + 1
#define LS_DELIVERYADVICELINEDISCOUNTS_CUSTOMERNO 10 + 1
#define LS_DELIVERYADVICELINEDISCOUNTS_DELIVERYADVICEDATE 10 + 1
#define LS_DELIVERYADVICELINEDISCOUNTS_DELIVERYADVICENO 10 + 1
#define LS_DELIVERYADVICELINEDISCOUNTS_DELIVERYADVICEPOSNO 10 + 1
#define LS_DELIVERYADVICELINEDISCOUNTS_DISCOUNTMODE 5 + 1
#define LS_DELIVERYADVICELINEDISCOUNTS_DISCOUNT 11 + 2
#define LS_DELIVERYADVICELINEDISCOUNTS_DAORIGIN 1 + 1
#define LS_DELIVERYADVICELINEDISCOUNTS_DELETEREASON 5 + 1
#define LS_DELIVERYADVICELINEDISCOUNTS_DADISCOUNTVALUE 11 + 2
#define LS_DELIVERYADVICELINEDISCOUNTS_DISCOUNTTYPE 5 + 1
#define LS_DELIVERYADVICELINEDISCOUNTS_HIERARCHY 5 + 1
#define LS_DELIVERYADVICELINEDISCOUNTS_CALCULATIONBASIS 5 + 1
#define LS_DELIVERYADVICELINEDISCOUNTS_DISCOUNTMODENAME 30 + 1

#define DELIVERYADVICELINEDISCOUNTSBRANCHNO 0
#define DELIVERYADVICELINEDISCOUNTSCUSTOMERNO 1
#define DELIVERYADVICELINEDISCOUNTSDELIVERYADVICEDATE 2
#define DELIVERYADVICELINEDISCOUNTSDELIVERYADVICENO 3
#define DELIVERYADVICELINEDISCOUNTSDELIVERYADVICEPOSNO 4
#define DELIVERYADVICELINEDISCOUNTSDISCOUNTMODE 5
#define DELIVERYADVICELINEDISCOUNTSDISCOUNT 6
#define DELIVERYADVICELINEDISCOUNTSDAORIGIN 7
#define DELIVERYADVICELINEDISCOUNTSDELETEREASON 8
#define DELIVERYADVICELINEDISCOUNTSDADISCOUNTVALUE 9
#define DELIVERYADVICELINEDISCOUNTSDISCOUNTTYPE 10
#define DELIVERYADVICELINEDISCOUNTSHIERARCHY 11
#define DELIVERYADVICELINEDISCOUNTSCALCULATIONBASIS 12
#define DELIVERYADVICELINEDISCOUNTSDISCOUNTMODENAME 13

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define DELIVERYADVICELINEDISCOUNTS_H
#define DELIVERYADVICELINEDISCOUNTS_ANZ ( sizeof(DELIVERYADVICELINEDISCOUNTS_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of DELIVERYADVICELINEDISCOUNTS ***********************************/

#define DELIVERYADVICELINEDISCOUNTS_LISTE \
        DADUMMY.BRANCHNO,\
        DADUMMY.CUSTOMERNO,\
        DADUMMY.DELIVERYADVICEDATE,\
        DADUMMY.DELIVERYADVICENO,\
        DADUMMY.DELIVERYADVICEPOSNO,\
        DADUMMY.DISCOUNTMODE,\
        DADUMMY.DISCOUNT,\
        DADUMMY.DAORIGIN,\
        DADUMMY.DELETEREASON,\
        DADUMMY.DADISCOUNTVALUE,\
        DADUMMY.DISCOUNTTYPE,\
        DADUMMY.HIERARCHY,\
        DADUMMY.CALCULATIONBASIS,\
        DADUMMY.DISCOUNTMODENAME
#define DELIVERYADVICELINEDISCOUNTS_LISTE_390 \
        BRANCHNO,\
        CUSTOMERNO,\
        DELIVERYADVICEDATE,\
        DELIVERYADVICENO,\
        DELIVERYADVICEPOSNO,\
        DISCOUNTMODE,\
        DISCOUNT,\
        DAORIGIN,\
        DELETEREASON,\
        DADISCOUNTVALUE,\
        DISCOUNTTYPE,\
        HIERARCHY,\
        CALCULATIONBASIS,\
        DISCOUNTMODENAME
#define DELIVERYADVICELINEDISCOUNTS_PLISTE \
        "DADUMMY.BRANCHNO,"\
        "DADUMMY.CUSTOMERNO,"\
        "DADUMMY.DELIVERYADVICEDATE,"\
        "DADUMMY.DELIVERYADVICENO,"\
        "DADUMMY.DELIVERYADVICEPOSNO,"\
        "DADUMMY.DISCOUNTMODE,"\
        "DADUMMY.DISCOUNT,"\
        "DADUMMY.DAORIGIN,"\
        "DADUMMY.DELETEREASON,"\
        "DADUMMY.DADISCOUNTVALUE,"\
        "DADUMMY.DISCOUNTTYPE,"\
        "DADUMMY.HIERARCHY,"\
        "DADUMMY.CALCULATIONBASIS,"\
        "DADUMMY.DISCOUNTMODENAME"
#define DELIVERYADVICELINEDISCOUNTS_PELISTE \
        "BRANCHNO,"\
        "CUSTOMERNO,"\
        "DELIVERYADVICEDATE,"\
        "DELIVERYADVICENO,"\
        "DELIVERYADVICEPOSNO,"\
        "DISCOUNTMODE,"\
        "DISCOUNT,"\
        "DAORIGIN,"\
        "DELETEREASON,"\
        "DADISCOUNTVALUE,"\
        "DISCOUNTTYPE,"\
        "HIERARCHY,"\
        "CALCULATIONBASIS,"\
        "DISCOUNTMODENAME"
#define DELIVERYADVICELINEDISCOUNTS_UPDLISTE \
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "DELIVERYADVICEDATE=?,"\
        "DELIVERYADVICENO=?,"\
        "DELIVERYADVICEPOSNO=?,"\
        "DISCOUNTMODE=?,"\
        "DISCOUNT=?,"\
        "DAORIGIN=?,"\
        "DELETEREASON=?,"\
        "DADISCOUNTVALUE=?,"\
        "DISCOUNTTYPE=?,"\
        "HIERARCHY=?,"\
        "CALCULATIONBASIS=?,"\
        "DISCOUNTMODENAME=?"
/* SqlMacros-Define of DELIVERYADVICELINEDISCOUNTS ****************************/

#define DELIVERYADVICELINEDISCOUNTS_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->DELIVERYADVICEDATE,\
        :x->DELIVERYADVICENO,\
        :x->DELIVERYADVICEPOSNO,\
        :x->DISCOUNTMODE,\
        :x->DISCOUNT,\
        :x->DAORIGIN,\
        :x->DELETEREASON,\
        :x->DADISCOUNTVALUE,\
        :x->DISCOUNTTYPE,\
        :x->HIERARCHY,\
        :x->CALCULATIONBASIS,\
        :x->DISCOUNTMODENAME
#define DELIVERYADVICELINEDISCOUNTS_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->DELIVERYADVICEDATE,\
        :x->DELIVERYADVICENO,\
        :x->DELIVERYADVICEPOSNO,\
        :x->DISCOUNTMODE,\
        :x->DISCOUNT,\
        :x->DAORIGIN,\
        :x->DELETEREASON,\
        :x->DADISCOUNTVALUE,\
        :x->DISCOUNTTYPE,\
        :x->HIERARCHY,\
        :x->CALCULATIONBASIS,\
        :x->DISCOUNTMODENAME
#define DELIVERYADVICELINEDISCOUNTS_UPDATE(x) \
        DADUMMY.BRANCHNO=:x->BRANCHNO,\
        DADUMMY.CUSTOMERNO=:x->CUSTOMERNO,\
        DADUMMY.DELIVERYADVICEDATE=:x->DELIVERYADVICEDATE,\
        DADUMMY.DELIVERYADVICENO=:x->DELIVERYADVICENO,\
        DADUMMY.DELIVERYADVICEPOSNO=:x->DELIVERYADVICEPOSNO,\
        DADUMMY.DISCOUNTMODE=:x->DISCOUNTMODE,\
        DADUMMY.DISCOUNT=:x->DISCOUNT,\
        DADUMMY.DAORIGIN=:x->DAORIGIN,\
        DADUMMY.DELETEREASON=:x->DELETEREASON,\
        DADUMMY.DADISCOUNTVALUE=:x->DADISCOUNTVALUE,\
        DADUMMY.DISCOUNTTYPE=:x->DISCOUNTTYPE,\
        DADUMMY.HIERARCHY=:x->HIERARCHY,\
        DADUMMY.CALCULATIONBASIS=:x->CALCULATIONBASIS,\
        DADUMMY.DISCOUNTMODENAME=:x->DISCOUNTMODENAME
/* SqlMacros390-Define of DELIVERYADVICELINEDISCOUNTS *************************/

#define DELIVERYADVICELINEDISCOUNTS_ZEIGER_390 \
        :BRANCHNO,\
        :CUSTOMERNO,\
        :DELIVERYADVICEDATE,\
        :DELIVERYADVICENO,\
        :DELIVERYADVICEPOSNO,\
        :DISCOUNTMODE,\
        :DISCOUNT,\
        :DAORIGIN,\
        :DELETEREASON,\
        :DADISCOUNTVALUE,\
        :DISCOUNTTYPE,\
        :HIERARCHY,\
        :CALCULATIONBASIS,\
        :DISCOUNTMODENAME
#define DELIVERYADVICELINEDISCOUNTS_UPDATE_390 \
        BRANCHNO=:BRANCHNO,\
        CUSTOMERNO=:CUSTOMERNO,\
        DELIVERYADVICEDATE=:DELIVERYADVICEDATE,\
        DELIVERYADVICENO=:DELIVERYADVICENO,\
        DELIVERYADVICEPOSNO=:DELIVERYADVICEPOSNO,\
        DISCOUNTMODE=:DISCOUNTMODE,\
        DISCOUNT=:DISCOUNT,\
        DAORIGIN=:DAORIGIN,\
        DELETEREASON=:DELETEREASON,\
        DADISCOUNTVALUE=:DADISCOUNTVALUE,\
        DISCOUNTTYPE=:DISCOUNTTYPE,\
        HIERARCHY=:HIERARCHY,\
        CALCULATIONBASIS=:CALCULATIONBASIS,\
        DISCOUNTMODENAME=:DISCOUNTMODENAME
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of DELIVERYADVICELINEDISCOUNTS *****************************/

#ifndef TRANSCLASS
typedef struct N_DELIVERYADVICELINEDISCOUNTS {
    short BRANCHNO;
    long CUSTOMERNO;
    long DELIVERYADVICEDATE;
    char DELIVERYADVICENO[11];
    long DELIVERYADVICEPOSNO;
    short DISCOUNTMODE;
    double DISCOUNT;
    char DAORIGIN[2];
    short DELETEREASON;
    double DADISCOUNTVALUE;
    short DISCOUNTTYPE;
    short HIERARCHY;
    short CALCULATIONBASIS;
    char DISCOUNTMODENAME[31];
} deliveryadvicelinediscountsS;
#else /* TRANSCLASS */
typedef struct N_DELIVERYADVICELINEDISCOUNTS {
    short BRANCHNO;
    long CUSTOMERNO;
    long DELIVERYADVICEDATE;
    char DELIVERYADVICENO[11];
    long DELIVERYADVICEPOSNO;
    short DISCOUNTMODE;
    double DISCOUNT;
    char DAORIGIN[2];
    short DELETEREASON;
    double DADISCOUNTVALUE;
    short DISCOUNTTYPE;
    short HIERARCHY;
    short CALCULATIONBASIS;
    char DISCOUNTMODENAME[31];

    bool operator == (const N_DELIVERYADVICELINEDISCOUNTS& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            CUSTOMERNO == right.CUSTOMERNO &&
            DELIVERYADVICEDATE == right.DELIVERYADVICEDATE &&
            !strcmp(DELIVERYADVICENO, right.DELIVERYADVICENO) &&
            DELIVERYADVICEPOSNO == right.DELIVERYADVICEPOSNO &&
            DISCOUNTMODE == right.DISCOUNTMODE &&
            DISCOUNT == right.DISCOUNT &&
            !strcmp(DAORIGIN, right.DAORIGIN) &&
            DELETEREASON == right.DELETEREASON &&
            DADISCOUNTVALUE == right.DADISCOUNTVALUE &&
            DISCOUNTTYPE == right.DISCOUNTTYPE &&
            HIERARCHY == right.HIERARCHY &&
            CALCULATIONBASIS == right.CALCULATIONBASIS &&
            !strcmp(DISCOUNTMODENAME, right.DISCOUNTMODENAME)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        CUSTOMERNO = 0;
        DELIVERYADVICEDATE = 0;
        strcpy(DELIVERYADVICENO, " " );
        DELIVERYADVICEPOSNO = 0;
        DISCOUNTMODE = 0;
        DISCOUNT = 0;
        strcpy(DAORIGIN, " " );
        DELETEREASON = 0;
        DADISCOUNTVALUE = 0;
        DISCOUNTTYPE = 0;
        HIERARCHY = 0;
        CALCULATIONBASIS = 0;
        strcpy(DISCOUNTMODENAME, " " );
#endif
    }
} deliveryadvicelinediscountsS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of DELIVERYADVICELINEDISCOUNTS ***********************/

struct S_DELIVERYADVICELINEDISCOUNTS {
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char DELIVERYADVICEDATE[11];
    char DELIVERYADVICENO[10 + 1];
    char DELIVERYADVICEPOSNO[11];
    char DISCOUNTMODE[7];
    char DISCOUNT[11 + 2];
    char DAORIGIN[1 + 1];
    char DELETEREASON[7];
    char DADISCOUNTVALUE[11 + 2];
    char DISCOUNTTYPE[7];
    char HIERARCHY[7];
    char CALCULATIONBASIS[7];
    char DISCOUNTMODENAME[30 + 1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of DELIVERYADVICELINEDISCOUNTS ******/

struct O_DELIVERYADVICELINEDISCOUNTS {
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char DELIVERYADVICEDATE[11];
    char DELIVERYADVICENO[10];
    char DELIVERYADVICEPOSNO[11];
    char DISCOUNTMODE[7];
    char DISCOUNT[11];
    char DAORIGIN[1];
    char DELETEREASON[7];
    char DADISCOUNTVALUE[11];
    char DISCOUNTTYPE[7];
    char HIERARCHY[7];
    char CALCULATIONBASIS[7];
    char DISCOUNTMODENAME[30];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of DELIVERYADVICELINEDISCOUNTS *****************/

struct C_DELIVERYADVICELINEDISCOUNTS {
    short BRANCHNO;
    long CUSTOMERNO;
    long DELIVERYADVICEDATE;
    char DELIVERYADVICENO[11];
    long DELIVERYADVICEPOSNO;
    short DISCOUNTMODE;
    double DISCOUNT;
    char DAORIGIN;
    short DELETEREASON;
    double DADISCOUNTVALUE;
    short DISCOUNTTYPE;
    short HIERARCHY;
    short CALCULATIONBASIS;
    char DISCOUNTMODENAME[31];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of DELIVERYADVICELINEDISCOUNTS ***************/

struct I_DELIVERYADVICELINEDISCOUNTS {
    short BRANCHNO;
    short CUSTOMERNO;
    short DELIVERYADVICEDATE;
    short DELIVERYADVICENO;
    short DELIVERYADVICEPOSNO;
    short DISCOUNTMODE;
    short DISCOUNT;
    short DAORIGIN;
    short DELETEREASON;
    short DADISCOUNTVALUE;
    short DISCOUNTTYPE;
    short HIERARCHY;
    short CALCULATIONBASIS;
    short DISCOUNTMODENAME;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of DELIVERYADVICELINEDISCOUNTS *************************/

#if defined (BUF_DESC)
static struct buf_desc DELIVERYADVICELINEDISCOUNTS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 10, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 11, 2 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 11, 2 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc DELIVERYADVICELINEDISCOUNTS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 10, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 11, 2 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 11, 2 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
};
#endif

/* description for datatypes of DELIVERYADVICELINEDISCOUNTS *******************/

 #define DELIVERYADVICELINEDISCOUNTS_S390 \
         short BRANCHNO; \
         long CUSTOMERNO; \
         long DELIVERYADVICEDATE; \
         char DELIVERYADVICENO[11]; \
         long DELIVERYADVICEPOSNO; \
         short DISCOUNTMODE; \
         double DISCOUNT; \
         char DAORIGIN; \
         short DELETEREASON; \
         double DADISCOUNTVALUE; \
         short DISCOUNTTYPE; \
         short HIERARCHY; \
         short CALCULATIONBASIS; \
         char DISCOUNTMODENAME[31]; \



/* Copy-Function Struct to single Data DELIVERYADVICELINEDISCOUNTS ************/

 #define DELIVERYADVICELINEDISCOUNTS_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
         DELIVERYADVICEDATE=_x_->DELIVERYADVICEDATE;\
          strcpy(DELIVERYADVICENO,_x_->DELIVERYADVICENO);\
         DELIVERYADVICEPOSNO=_x_->DELIVERYADVICEPOSNO;\
         DISCOUNTMODE=_x_->DISCOUNTMODE;\
         DISCOUNT=_x_->DISCOUNT;\
         DAORIGIN=_x_->DAORIGIN;\
         DELETEREASON=_x_->DELETEREASON;\
         DADISCOUNTVALUE=_x_->DADISCOUNTVALUE;\
         DISCOUNTTYPE=_x_->DISCOUNTTYPE;\
         HIERARCHY=_x_->HIERARCHY;\
         CALCULATIONBASIS=_x_->CALCULATIONBASIS;\
          strcpy(DISCOUNTMODENAME,_x_->DISCOUNTMODENAME);\

 #define DELIVERYADVICELINEDISCOUNTS_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->DELIVERYADVICEDATE=DELIVERYADVICEDATE;\
          strcpy(_x_->DELIVERYADVICENO,DELIVERYADVICENO);\
          _x_->DELIVERYADVICEPOSNO=DELIVERYADVICEPOSNO;\
          _x_->DISCOUNTMODE=DISCOUNTMODE;\
          _x_->DISCOUNT=DISCOUNT;\
          _x_->DAORIGIN=DAORIGIN;\
          _x_->DELETEREASON=DELETEREASON;\
          _x_->DADISCOUNTVALUE=DADISCOUNTVALUE;\
          _x_->DISCOUNTTYPE=DISCOUNTTYPE;\
          _x_->HIERARCHY=HIERARCHY;\
          _x_->CALCULATIONBASIS=CALCULATIONBASIS;\
          strcpy(_x_->DISCOUNTMODENAME,DISCOUNTMODENAME);\



/* FunctionNumber-Define of Deliveryadvicelinediscounts ***********************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of Deliveryadvicelinediscounts *******************/


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

class CDELIVERYADVICELINEDISCOUNTS : public ppDadeVirtual {
public:
    deliveryadvicelinediscountsS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<deliveryadvicelinediscountsS> lst; // class list

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
                     vector< deliveryadvicelinediscountsS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     deliveryadvicelinediscountsS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< deliveryadvicelinediscountsS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<deliveryadvicelinediscountsS>::iterator
                 beginList() { return lst.begin(); }
    vector<deliveryadvicelinediscountsS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    long         GetDeliveryadvicedate() const { return s.DELIVERYADVICEDATE; }
    const char*  GetDeliveryadviceno(ppString & t) const { t = s.DELIVERYADVICENO; t.erasespace(ppString::END); return t.c_str(); }
    long         GetDeliveryadviceposno() const { return s.DELIVERYADVICEPOSNO; }
    short        GetDiscountmode() const { return s.DISCOUNTMODE; }
    double       GetDiscount() const { return s.DISCOUNT; }
    char         GetDaorigin() const { return s.DAORIGIN[0]; }
    short        GetDeletereason() const { return s.DELETEREASON; }
    double       GetDadiscountvalue() const { return s.DADISCOUNTVALUE; }
    short        GetDiscounttype() const { return s.DISCOUNTTYPE; }
    short        GetHierarchy() const { return s.HIERARCHY; }
    short        GetCalculationbasis() const { return s.CALCULATIONBASIS; }
    const char*  GetDiscountmodename(ppString & t) const { t = s.DISCOUNTMODENAME; t.erasespace(ppString::END); return t.c_str(); }

    const deliveryadvicelinediscountsS &
                 GetStruct() const { return s; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetDeliveryadvicedate(long t) { s.DELIVERYADVICEDATE = t; }
    void         SetDeliveryadviceno(const ppString & t) { ppGStrCopy(s.DELIVERYADVICENO, t.c_str(), L_DELIVERYADVICELINEDISCOUNTS_DELIVERYADVICENO); }
    void         SetDeliveryadviceposno(long t) { s.DELIVERYADVICEPOSNO = t; }
    void         SetDiscountmode(short t) { s.DISCOUNTMODE = t; }
    void         SetDiscount(double t) { s.DISCOUNT = t; }
    void         SetDaorigin(char t) { s.DAORIGIN[0] = t; s.DAORIGIN[1] = '\0';}
    void         SetDeletereason(short t) { s.DELETEREASON = t; }
    void         SetDadiscountvalue(double t) { s.DADISCOUNTVALUE = t; }
    void         SetDiscounttype(short t) { s.DISCOUNTTYPE = t; }
    void         SetHierarchy(short t) { s.HIERARCHY = t; }
    void         SetCalculationbasis(short t) { s.CALCULATIONBASIS = t; }
    void         SetDiscountmodename(const ppString & t) { ppGStrCopy(s.DISCOUNTMODENAME, t.c_str(), L_DELIVERYADVICELINEDISCOUNTS_DISCOUNTMODENAME); }

    void         SetStruct(const deliveryadvicelinediscountsS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CDELIVERYADVICELINEDISCOUNTS() {
        ::buf_default((void *)&s, DELIVERYADVICELINEDISCOUNTS_BES, DELIVERYADVICELINEDISCOUNTS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CDELIVERYADVICELINEDISCOUNTS() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, DELIVERYADVICELINEDISCOUNTS_BES, DELIVERYADVICELINEDISCOUNTS_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, DELIVERYADVICELINEDISCOUNTS_BES, (int)DELIVERYADVICELINEDISCOUNTS_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, DELIVERYADVICELINEDISCOUNTS_BES, (int)DELIVERYADVICELINEDISCOUNTS_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_DELIVERYADVICELINEDISCOUNTS & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.DELIVERYADVICENO);
        ppGStripLast(d.DISCOUNTMODENAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, DELIVERYADVICELINEDISCOUNTS_BES, (int)DELIVERYADVICELINEDISCOUNTS_ANZ, error_msg);
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
/* CreateSqlStatement of DELIVERYADVICELINEDISCOUNTS **************************/

 #define DELIVERYADVICELINEDISCOUNTS_CREATE(x) EXEC SQL create table x (\
         BRANCHNO smallint default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         DELIVERYADVICEDATE integer default 0 not null,\
         DELIVERYADVICENO varchar(10,0) default " " not null,\
         DELIVERYADVICEPOSNO integer default 0 not null,\
         DISCOUNTMODE smallint default 0 not null,\
         DISCOUNT decimal(11,2) default 0 not null,\
         DAORIGIN char(1) default " " not null,\
         DELETEREASON smallint default 0 not null,\
         DADISCOUNTVALUE decimal(11,2) default 0 not null,\
         DISCOUNTTYPE smallint default 0 not null,\
         HIERARCHY smallint default 0 not null,\
         CALCULATIONBASIS smallint default 0 not null,\
         DISCOUNTMODENAME varchar(30,0) default " " not null) extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of DELIVERYADVICELINEDISCOUNTS ************************/

 #define DELIVERYADVICELINEDISCOUNTS_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
/* DeleteIndexStatement of DELIVERYADVICELINEDISCOUNTS ************************/

 #define DELIVERYADVICELINEDISCOUNTS_DELETE_INDEX(_X_)\
              _X_ = 0;\


#endif   // GUARD
