#ifndef __PP_DELIVERYADVICELINEDETAILS_H_
#define __PP_DELIVERYADVICELINEDETAILS_H_

/******************************************************************************/
/* c:\prri\Headerfiles\Deliveryadvicelinedetails ******************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of DELIVERYADVICELINEDETAILS *********************************/

#define L_DELIVERYADVICELINEDETAILS_BRANCHNO 6
#define L_DELIVERYADVICELINEDETAILS_CUSTOMERNO 11
#define L_DELIVERYADVICELINEDETAILS_DELIVERYADVICEDATE 11
#define L_DELIVERYADVICELINEDETAILS_PHARMOSORDERNO 11
#define L_DELIVERYADVICELINEDETAILS_PHARMOSORDERPOSNO 11
#define L_DELIVERYADVICELINEDETAILS_QTY_DELIVERY 11
#define L_DELIVERYADVICELINEDETAILS_BATCH 25
#define L_DELIVERYADVICELINEDETAILS_EXPIRYDATE 11
#define L_DELIVERYADVICELINEDETAILS_PACKAGEID 11
#define L_DELIVERYADVICELINEDETAILS_TRACKINGID 25
#define L_DELIVERYADVICELINEDETAILS_QTY_LACK 11
#define L_DELIVERYADVICELINEDETAILS_DELIVERYPOSNO 11

/* Length/Count-Define of DELIVERYADVICELINEDETAILS ***************************/

#define LS_DELIVERYADVICELINEDETAILS_BRANCHNO 5 + 1
#define LS_DELIVERYADVICELINEDETAILS_CUSTOMERNO 10 + 1
#define LS_DELIVERYADVICELINEDETAILS_DELIVERYADVICEDATE 10 + 1
#define LS_DELIVERYADVICELINEDETAILS_PHARMOSORDERNO 10 + 1
#define LS_DELIVERYADVICELINEDETAILS_PHARMOSORDERPOSNO 10 + 1
#define LS_DELIVERYADVICELINEDETAILS_QTY_DELIVERY 10 + 1
#define LS_DELIVERYADVICELINEDETAILS_BATCH 25 + 1
#define LS_DELIVERYADVICELINEDETAILS_EXPIRYDATE 10 + 1
#define LS_DELIVERYADVICELINEDETAILS_PACKAGEID 10 + 1
#define LS_DELIVERYADVICELINEDETAILS_TRACKINGID 25 + 1
#define LS_DELIVERYADVICELINEDETAILS_QTY_LACK 10 + 1
#define LS_DELIVERYADVICELINEDETAILS_DELIVERYPOSNO 10 + 1

#define DELIVERYADVICELINEDETAILSBRANCHNO 0
#define DELIVERYADVICELINEDETAILSCUSTOMERNO 1
#define DELIVERYADVICELINEDETAILSDELIVERYADVICEDATE 2
#define DELIVERYADVICELINEDETAILSPHARMOSORDERNO 3
#define DELIVERYADVICELINEDETAILSPHARMOSORDERPOSNO 4
#define DELIVERYADVICELINEDETAILSQTY_DELIVERY 5
#define DELIVERYADVICELINEDETAILSBATCH 6
#define DELIVERYADVICELINEDETAILSEXPIRYDATE 7
#define DELIVERYADVICELINEDETAILSPACKAGEID 8
#define DELIVERYADVICELINEDETAILSTRACKINGID 9
#define DELIVERYADVICELINEDETAILSQTY_LACK 10
#define DELIVERYADVICELINEDETAILSDELIVERYPOSNO 11

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define DELIVERYADVICELINEDETAILS_H
#define DELIVERYADVICELINEDETAILS_ANZ ( sizeof(DELIVERYADVICELINEDETAILS_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of DELIVERYADVICELINEDETAILS *************************************/

#define DELIVERYADVICELINEDETAILS_LISTE \
        DADUMMY.BRANCHNO,\
        DADUMMY.CUSTOMERNO,\
        DADUMMY.DELIVERYADVICEDATE,\
        DADUMMY.PHARMOSORDERNO,\
        DADUMMY.PHARMOSORDERPOSNO,\
        DADUMMY.QTY_DELIVERY,\
        DADUMMY.BATCH,\
        DADUMMY.EXPIRYDATE,\
        DADUMMY.PACKAGEID,\
        DADUMMY.TRACKINGID,\
        DADUMMY.QTY_LACK,\
        DADUMMY.DELIVERYPOSNO
#define DELIVERYADVICELINEDETAILS_LISTE_390 \
        BRANCHNO,\
        CUSTOMERNO,\
        DELIVERYADVICEDATE,\
        PHARMOSORDERNO,\
        PHARMOSORDERPOSNO,\
        QTY_DELIVERY,\
        BATCH,\
        EXPIRYDATE,\
        PACKAGEID,\
        TRACKINGID,\
        QTY_LACK,\
        DELIVERYPOSNO
#define DELIVERYADVICELINEDETAILS_PLISTE \
        "DADUMMY.BRANCHNO,"\
        "DADUMMY.CUSTOMERNO,"\
        "DADUMMY.DELIVERYADVICEDATE,"\
        "DADUMMY.PHARMOSORDERNO,"\
        "DADUMMY.PHARMOSORDERPOSNO,"\
        "DADUMMY.QTY_DELIVERY,"\
        "DADUMMY.BATCH,"\
        "DADUMMY.EXPIRYDATE,"\
        "DADUMMY.PACKAGEID,"\
        "DADUMMY.TRACKINGID,"\
        "DADUMMY.QTY_LACK,"\
        "DADUMMY.DELIVERYPOSNO"
#define DELIVERYADVICELINEDETAILS_PELISTE \
        "BRANCHNO,"\
        "CUSTOMERNO,"\
        "DELIVERYADVICEDATE,"\
        "PHARMOSORDERNO,"\
        "PHARMOSORDERPOSNO,"\
        "QTY_DELIVERY,"\
        "BATCH,"\
        "EXPIRYDATE,"\
        "PACKAGEID,"\
        "TRACKINGID,"\
        "QTY_LACK,"\
        "DELIVERYPOSNO"
#define DELIVERYADVICELINEDETAILS_UPDLISTE \
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "DELIVERYADVICEDATE=?,"\
        "PHARMOSORDERNO=?,"\
        "PHARMOSORDERPOSNO=?,"\
        "QTY_DELIVERY=?,"\
        "BATCH=?,"\
        "EXPIRYDATE=?,"\
        "PACKAGEID=?,"\
        "TRACKINGID=?,"\
        "QTY_LACK=?,"\
        "DELIVERYPOSNO=?"
/* SqlMacros-Define of DELIVERYADVICELINEDETAILS ******************************/

#define DELIVERYADVICELINEDETAILS_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->DELIVERYADVICEDATE,\
        :x->PHARMOSORDERNO,\
        :x->PHARMOSORDERPOSNO,\
        :x->QTY_DELIVERY,\
        :x->BATCH,\
        :x->EXPIRYDATE,\
        :x->PACKAGEID,\
        :x->TRACKINGID,\
        :x->QTY_LACK,\
        :x->DELIVERYPOSNO
#define DELIVERYADVICELINEDETAILS_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->DELIVERYADVICEDATE,\
        :x->PHARMOSORDERNO,\
        :x->PHARMOSORDERPOSNO,\
        :x->QTY_DELIVERY,\
        :x->BATCH,\
        :x->EXPIRYDATE,\
        :x->PACKAGEID,\
        :x->TRACKINGID,\
        :x->QTY_LACK,\
        :x->DELIVERYPOSNO
#define DELIVERYADVICELINEDETAILS_UPDATE(x) \
        DADUMMY.BRANCHNO=:x->BRANCHNO,\
        DADUMMY.CUSTOMERNO=:x->CUSTOMERNO,\
        DADUMMY.DELIVERYADVICEDATE=:x->DELIVERYADVICEDATE,\
        DADUMMY.PHARMOSORDERNO=:x->PHARMOSORDERNO,\
        DADUMMY.PHARMOSORDERPOSNO=:x->PHARMOSORDERPOSNO,\
        DADUMMY.QTY_DELIVERY=:x->QTY_DELIVERY,\
        DADUMMY.BATCH=:x->BATCH,\
        DADUMMY.EXPIRYDATE=:x->EXPIRYDATE,\
        DADUMMY.PACKAGEID=:x->PACKAGEID,\
        DADUMMY.TRACKINGID=:x->TRACKINGID,\
        DADUMMY.QTY_LACK=:x->QTY_LACK,\
        DADUMMY.DELIVERYPOSNO=:x->DELIVERYPOSNO
/* SqlMacros390-Define of DELIVERYADVICELINEDETAILS ***************************/

#define DELIVERYADVICELINEDETAILS_ZEIGER_390 \
        :BRANCHNO,\
        :CUSTOMERNO,\
        :DELIVERYADVICEDATE,\
        :PHARMOSORDERNO,\
        :PHARMOSORDERPOSNO,\
        :QTY_DELIVERY,\
        :BATCH,\
        :EXPIRYDATE,\
        :PACKAGEID,\
        :TRACKINGID,\
        :QTY_LACK,\
        :DELIVERYPOSNO
#define DELIVERYADVICELINEDETAILS_UPDATE_390 \
        BRANCHNO=:BRANCHNO,\
        CUSTOMERNO=:CUSTOMERNO,\
        DELIVERYADVICEDATE=:DELIVERYADVICEDATE,\
        PHARMOSORDERNO=:PHARMOSORDERNO,\
        PHARMOSORDERPOSNO=:PHARMOSORDERPOSNO,\
        QTY_DELIVERY=:QTY_DELIVERY,\
        BATCH=:BATCH,\
        EXPIRYDATE=:EXPIRYDATE,\
        PACKAGEID=:PACKAGEID,\
        TRACKINGID=:TRACKINGID,\
        QTY_LACK=:QTY_LACK,\
        DELIVERYPOSNO=:DELIVERYPOSNO
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of DELIVERYADVICELINEDETAILS *******************************/

#ifndef TRANSCLASS
typedef struct N_DELIVERYADVICELINEDETAILS {
    short BRANCHNO;
    long CUSTOMERNO;
    long DELIVERYADVICEDATE;
    long PHARMOSORDERNO;
    long PHARMOSORDERPOSNO;
    long QTY_DELIVERY;
    char BATCH[26];
    long EXPIRYDATE;
    long PACKAGEID;
    char TRACKINGID[26];
    long QTY_LACK;
    long DELIVERYPOSNO;
} deliveryadvicelinedetailsS;
#else /* TRANSCLASS */
typedef struct N_DELIVERYADVICELINEDETAILS {
    short BRANCHNO;
    long CUSTOMERNO;
    long DELIVERYADVICEDATE;
    long PHARMOSORDERNO;
    long PHARMOSORDERPOSNO;
    long QTY_DELIVERY;
    char BATCH[26];
    long EXPIRYDATE;
    long PACKAGEID;
    char TRACKINGID[26];
    long QTY_LACK;
    long DELIVERYPOSNO;

    bool operator == (const N_DELIVERYADVICELINEDETAILS& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            CUSTOMERNO == right.CUSTOMERNO &&
            DELIVERYADVICEDATE == right.DELIVERYADVICEDATE &&
            PHARMOSORDERNO == right.PHARMOSORDERNO &&
            PHARMOSORDERPOSNO == right.PHARMOSORDERPOSNO &&
            QTY_DELIVERY == right.QTY_DELIVERY &&
            !strcmp(BATCH, right.BATCH) &&
            EXPIRYDATE == right.EXPIRYDATE &&
            PACKAGEID == right.PACKAGEID &&
            !strcmp(TRACKINGID, right.TRACKINGID) &&
            QTY_LACK == right.QTY_LACK &&
            DELIVERYPOSNO == right.DELIVERYPOSNO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        CUSTOMERNO = 0;
        DELIVERYADVICEDATE = 0;
        PHARMOSORDERNO = 0;
        PHARMOSORDERPOSNO = 0;
        QTY_DELIVERY = 0;
        strcpy(BATCH, " " );
        EXPIRYDATE = 0;
        PACKAGEID = 0;
        strcpy(TRACKINGID, " " );
        QTY_LACK = 0;
        DELIVERYPOSNO = 0;
#endif
    }
} deliveryadvicelinedetailsS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of DELIVERYADVICELINEDETAILS *************************/

struct S_DELIVERYADVICELINEDETAILS {
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char DELIVERYADVICEDATE[11];
    char PHARMOSORDERNO[11];
    char PHARMOSORDERPOSNO[11];
    char QTY_DELIVERY[11];
    char BATCH[25 + 1];
    char EXPIRYDATE[11];
    char PACKAGEID[11];
    char TRACKINGID[25 + 1];
    char QTY_LACK[11];
    char DELIVERYPOSNO[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of DELIVERYADVICELINEDETAILS ********/

struct O_DELIVERYADVICELINEDETAILS {
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char DELIVERYADVICEDATE[11];
    char PHARMOSORDERNO[11];
    char PHARMOSORDERPOSNO[11];
    char QTY_DELIVERY[11];
    char BATCH[25];
    char EXPIRYDATE[11];
    char PACKAGEID[11];
    char TRACKINGID[25];
    char QTY_LACK[11];
    char DELIVERYPOSNO[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of DELIVERYADVICELINEDETAILS *******************/

struct C_DELIVERYADVICELINEDETAILS {
    short BRANCHNO;
    long CUSTOMERNO;
    long DELIVERYADVICEDATE;
    long PHARMOSORDERNO;
    long PHARMOSORDERPOSNO;
    long QTY_DELIVERY;
    char BATCH[26];
    long EXPIRYDATE;
    long PACKAGEID;
    char TRACKINGID[26];
    long QTY_LACK;
    long DELIVERYPOSNO;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of DELIVERYADVICELINEDETAILS *****************/

struct I_DELIVERYADVICELINEDETAILS {
    short BRANCHNO;
    short CUSTOMERNO;
    short DELIVERYADVICEDATE;
    short PHARMOSORDERNO;
    short PHARMOSORDERPOSNO;
    short QTY_DELIVERY;
    short BATCH;
    short EXPIRYDATE;
    short PACKAGEID;
    short TRACKINGID;
    short QTY_LACK;
    short DELIVERYPOSNO;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of DELIVERYADVICELINEDETAILS ***************************/

#if defined (BUF_DESC)
static struct buf_desc DELIVERYADVICELINEDETAILS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 25, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 25, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc DELIVERYADVICELINEDETAILS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 25, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 25, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* description for datatypes of DELIVERYADVICELINEDETAILS *********************/

 #define DELIVERYADVICELINEDETAILS_S390 \
         short BRANCHNO; \
         long CUSTOMERNO; \
         long DELIVERYADVICEDATE; \
         long PHARMOSORDERNO; \
         long PHARMOSORDERPOSNO; \
         long QTY_DELIVERY; \
         char BATCH[26]; \
         long EXPIRYDATE; \
         long PACKAGEID; \
         char TRACKINGID[26]; \
         long QTY_LACK; \
         long DELIVERYPOSNO; \



/* Copy-Function Struct to single Data DELIVERYADVICELINEDETAILS **************/

 #define DELIVERYADVICELINEDETAILS_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
         DELIVERYADVICEDATE=_x_->DELIVERYADVICEDATE;\
         PHARMOSORDERNO=_x_->PHARMOSORDERNO;\
         PHARMOSORDERPOSNO=_x_->PHARMOSORDERPOSNO;\
         QTY_DELIVERY=_x_->QTY_DELIVERY;\
          strcpy(BATCH,_x_->BATCH);\
         EXPIRYDATE=_x_->EXPIRYDATE;\
         PACKAGEID=_x_->PACKAGEID;\
          strcpy(TRACKINGID,_x_->TRACKINGID);\
         QTY_LACK=_x_->QTY_LACK;\
         DELIVERYPOSNO=_x_->DELIVERYPOSNO;\

 #define DELIVERYADVICELINEDETAILS_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->DELIVERYADVICEDATE=DELIVERYADVICEDATE;\
          _x_->PHARMOSORDERNO=PHARMOSORDERNO;\
          _x_->PHARMOSORDERPOSNO=PHARMOSORDERPOSNO;\
          _x_->QTY_DELIVERY=QTY_DELIVERY;\
          strcpy(_x_->BATCH,BATCH);\
          _x_->EXPIRYDATE=EXPIRYDATE;\
          _x_->PACKAGEID=PACKAGEID;\
          strcpy(_x_->TRACKINGID,TRACKINGID);\
          _x_->QTY_LACK=QTY_LACK;\
          _x_->DELIVERYPOSNO=DELIVERYPOSNO;\



/* FunctionNumber-Define of Deliveryadvicelinedetails *************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of Deliveryadvicelinedetails *********************/


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

class CDELIVERYADVICELINEDETAILS : public ppDadeVirtual {
public:
    deliveryadvicelinedetailsS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<deliveryadvicelinedetailsS> lst; // class list

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
                     vector< deliveryadvicelinedetailsS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     deliveryadvicelinedetailsS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< deliveryadvicelinedetailsS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<deliveryadvicelinedetailsS>::iterator
                 beginList() { return lst.begin(); }
    vector<deliveryadvicelinedetailsS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    long         GetDeliveryadvicedate() const { return s.DELIVERYADVICEDATE; }
    long         GetPharmosorderno() const { return s.PHARMOSORDERNO; }
    long         GetPharmosorderposno() const { return s.PHARMOSORDERPOSNO; }
    long         GetQty_delivery() const { return s.QTY_DELIVERY; }
    const char*  GetBatch(ppString & t) const { t = s.BATCH; t.erasespace(ppString::END); return t.c_str(); }
    long         GetExpirydate() const { return s.EXPIRYDATE; }
    long         GetPackageid() const { return s.PACKAGEID; }
    const char*  GetTrackingid(ppString & t) const { t = s.TRACKINGID; t.erasespace(ppString::END); return t.c_str(); }
    long         GetQty_lack() const { return s.QTY_LACK; }
    long         GetDeliveryposno() const { return s.DELIVERYPOSNO; }

    const deliveryadvicelinedetailsS &
                 GetStruct() const { return s; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetDeliveryadvicedate(long t) { s.DELIVERYADVICEDATE = t; }
    void         SetPharmosorderno(long t) { s.PHARMOSORDERNO = t; }
    void         SetPharmosorderposno(long t) { s.PHARMOSORDERPOSNO = t; }
    void         SetQty_delivery(long t) { s.QTY_DELIVERY = t; }
    void         SetBatch(const ppString & t) { ppGStrCopy(s.BATCH, t.c_str(), L_DELIVERYADVICELINEDETAILS_BATCH); }
    void         SetExpirydate(long t) { s.EXPIRYDATE = t; }
    void         SetPackageid(long t) { s.PACKAGEID = t; }
    void         SetTrackingid(const ppString & t) { ppGStrCopy(s.TRACKINGID, t.c_str(), L_DELIVERYADVICELINEDETAILS_TRACKINGID); }
    void         SetQty_lack(long t) { s.QTY_LACK = t; }
    void         SetDeliveryposno(long t) { s.DELIVERYPOSNO = t; }

    void         SetStruct(const deliveryadvicelinedetailsS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CDELIVERYADVICELINEDETAILS() {
        ::buf_default((void *)&s, DELIVERYADVICELINEDETAILS_BES, DELIVERYADVICELINEDETAILS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CDELIVERYADVICELINEDETAILS() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, DELIVERYADVICELINEDETAILS_BES, DELIVERYADVICELINEDETAILS_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, DELIVERYADVICELINEDETAILS_BES, (int)DELIVERYADVICELINEDETAILS_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, DELIVERYADVICELINEDETAILS_BES, (int)DELIVERYADVICELINEDETAILS_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_DELIVERYADVICELINEDETAILS & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.BATCH);
        ppGStripLast(d.TRACKINGID);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, DELIVERYADVICELINEDETAILS_BES, (int)DELIVERYADVICELINEDETAILS_ANZ, error_msg);
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
/* CreateSqlStatement of DELIVERYADVICELINEDETAILS ****************************/

 #define DELIVERYADVICELINEDETAILS_CREATE(x) EXEC SQL create table x (\
         BRANCHNO smallint default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         DELIVERYADVICEDATE integer default 0 not null,\
         PHARMOSORDERNO integer default 0 not null,\
         PHARMOSORDERPOSNO integer default 0 not null,\
         QTY_DELIVERY integer default 0 not null,\
         BATCH varchar(25,0) default " " not null,\
         EXPIRYDATE integer default 0 not null,\
         PACKAGEID integer default 0 not null,\
         TRACKINGID varchar(25,0) default " " not null,\
         QTY_LACK integer default 0 not null,\
         DELIVERYPOSNO integer default 0 not null) extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of DELIVERYADVICELINEDETAILS **************************/

 #define DELIVERYADVICELINEDETAILS_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
/* DeleteIndexStatement of DELIVERYADVICELINEDETAILS **************************/

 #define DELIVERYADVICELINEDETAILS_DELETE_INDEX(_X_)\
              _X_ = 0;\


#endif   // GUARD
