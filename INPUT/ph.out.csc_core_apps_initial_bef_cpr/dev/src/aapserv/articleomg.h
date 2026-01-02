#ifndef __PP_ARTICLEOMG_H_
#define __PP_ARTICLEOMG_H_

/******************************************************************************/
/* c:\Marathon\orderentry\csc_core_applications\src\aapserv\ArticleOMG ********/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of ARTICLEOMG ************************************************/

#define L_ARTICLEOMG_ARTICLENO 11
#define L_ARTICLEOMG_CONTRACTQTY 11
#define L_ARTICLEOMG_BRANCHNO 6
#define L_ARTICLEOMG_CUSTOMERNO 11
#define L_ARTICLEOMG_ADDDISCOUNTPCT 5
#define N_ARTICLEOMG_ADDDISCOUNTPCT 2
#define L_ARTICLEOMG_DATEFROM 11
#define L_ARTICLEOMG_DATETO 11
#define L_ARTICLEOMG_PHARMACYGROUPID 3
#define L_ARTICLEOMG_RESTQTY 11
#define L_ARTICLEOMG_DISCOUNTCALCFROM 6
#define L_ARTICLEOMG_DISCOUNTAPPLYTO 6

/* Length/Count-Define of ARTICLEOMG ******************************************/

#define LS_ARTICLEOMG_ARTICLENO 10 + 1
#define LS_ARTICLEOMG_CONTRACTQTY 10 + 1
#define LS_ARTICLEOMG_BRANCHNO 5 + 1
#define LS_ARTICLEOMG_CUSTOMERNO 10 + 1
#define LS_ARTICLEOMG_ADDDISCOUNTPCT 5 + 2
#define LS_ARTICLEOMG_DATEFROM 10 + 1
#define LS_ARTICLEOMG_DATETO 10 + 1
#define LS_ARTICLEOMG_PHARMACYGROUPID 3 + 1
#define LS_ARTICLEOMG_RESTQTY 10 + 1
#define LS_ARTICLEOMG_DISCOUNTCALCFROM 5 + 1
#define LS_ARTICLEOMG_DISCOUNTAPPLYTO 5 + 1

#define ARTICLEOMGARTICLENO 0
#define ARTICLEOMGCONTRACTQTY 1
#define ARTICLEOMGBRANCHNO 2
#define ARTICLEOMGCUSTOMERNO 3
#define ARTICLEOMGADDDISCOUNTPCT 4
#define ARTICLEOMGDATEFROM 5
#define ARTICLEOMGDATETO 6
#define ARTICLEOMGPHARMACYGROUPID 7
#define ARTICLEOMGRESTQTY 8
#define ARTICLEOMGDISCOUNTCALCFROM 9
#define ARTICLEOMGDISCOUNTAPPLYTO 10

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define ARTICLEOMG_H
#define ARTICLEOMG_ANZ ( sizeof(ARTICLEOMG_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ARTICLEOMG ****************************************************/

#define ARTICLEOMG_LISTE \
        TENDERPOS.ARTICLENO,\
        TENDERPOS.CONTRACTQTY,\
        TENDERHEAD.BRANCHNO,\
        TENDERHEAD.CUSTOMERNO,\
        TENDERPOS.ADDDISCOUNTPCT,\
        TENDERHEAD.DATEFROM,\
        TENDERHEAD.DATETO,\
        TENDERHEAD.PHARMACYGROUPID,\
        AADUMMY.RESTQTY,\
        TENDERPOS.DISCOUNTCALCFROM,\
        TENDERPOS.DISCOUNTAPPLYTO
#define ARTICLEOMG_LISTE_390 \
        ARTICLENO,\
        CONTRACTQTY,\
        BRANCHNO,\
        CUSTOMERNO,\
        ADDDISCOUNTPCT,\
        DATEFROM,\
        DATETO,\
        PHARMACYGROUPID,\
        RESTQTY,\
        DISCOUNTCALCFROM,\
        DISCOUNTAPPLYTO
#define ARTICLEOMG_PLISTE \
        "TENDERPOS.ARTICLENO,"\
        "TENDERPOS.CONTRACTQTY,"\
        "TENDERHEAD.BRANCHNO,"\
        "TENDERHEAD.CUSTOMERNO,"\
        "TENDERPOS.ADDDISCOUNTPCT,"\
        "TENDERHEAD.DATEFROM,"\
        "TENDERHEAD.DATETO,"\
        "TENDERHEAD.PHARMACYGROUPID,"\
        "AADUMMY.RESTQTY,"\
        "TENDERPOS.DISCOUNTCALCFROM,"\
        "TENDERPOS.DISCOUNTAPPLYTO"
#define ARTICLEOMG_PELISTE \
        "ARTICLENO,"\
        "CONTRACTQTY,"\
        "BRANCHNO,"\
        "CUSTOMERNO,"\
        "ADDDISCOUNTPCT,"\
        "DATEFROM,"\
        "DATETO,"\
        "PHARMACYGROUPID,"\
        "RESTQTY,"\
        "DISCOUNTCALCFROM,"\
        "DISCOUNTAPPLYTO"
#define ARTICLEOMG_UPDLISTE \
        "ARTICLENO=?,"\
        "CONTRACTQTY=?,"\
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "ADDDISCOUNTPCT=?,"\
        "DATEFROM=?,"\
        "DATETO=?,"\
        "PHARMACYGROUPID=?,"\
        "RESTQTY=?"\
        "DISCOUNTCALCFROM=?"\
        "DISCOUNTAPPLYTO=?"
/* SqlMacros-Define of ARTICLEOMG *********************************************/

#define ARTICLEOMG_ZEIGER(x) \
        :x->ARTICLENO,\
        :x->CONTRACTQTY,\
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->ADDDISCOUNTPCT,\
        :x->DATEFROM,\
        :x->DATETO,\
        :x->PHARMACYGROUPID,\
        :x->RESTQTY,\
        :x->DISCOUNTCALCFROM,\
        :x->DISCOUNTAPPLYTO
#define ARTICLEOMG_ZEIGERSEL(x) \
        :x->ARTICLENO,\
        :x->CONTRACTQTY,\
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->ADDDISCOUNTPCT,\
        :x->DATEFROM,\
        :x->DATETO,\
        :x->PHARMACYGROUPID,\
        :x->RESTQTY,\
        :x->DISCOUNTCALCFROM,\
        :x->DISCOUNTAPPLYTO
#define ARTICLEOMG_UPDATE(x) \
        TENDERPOS.ARTICLENO=:x->ARTICLENO,\
        TENDERPOS.CONTRACTQTY=:x->CONTRACTQTY,\
        TENDERHEAD.BRANCHNO=:x->BRANCHNO,\
        TENDERHEAD.CUSTOMERNO=:x->CUSTOMERNO,\
        TENDERPOS.ADDDISCOUNTPCT=:x->ADDDISCOUNTPCT,\
        TENDERHEAD.DATEFROM=:x->DATEFROM,\
        TENDERHEAD.DATETO=:x->DATETO,\
        TENDERHEAD.PHARMACYGROUPID=:x->PHARMACYGROUPID,\
        AADUMMY.RESTQTY=:x->RESTQTY,\
     	TENDERPOS.DISCOUNTCALCFROM=:x->DISCOUNTCALCFROM,\
        TENDERPOS.DISCOUNTAPPLYTO=:x->DISCOUNTAPPLYTO
/* SqlMacros390-Define of ARTICLEOMG ******************************************/

#define ARTICLEOMG_ZEIGER_390 \
        :ARTICLENO,\
        :CONTRACTQTY,\
        :BRANCHNO,\
        :CUSTOMERNO,\
        :ADDDISCOUNTPCT,\
        :DATEFROM,\
        :DATETO,\
        :PHARMACYGROUPID,\
        :RESTQTY,\
     	:DISCOUNTCALCFROM,\
        :DISCOUNTAPPLYTO
#define ARTICLEOMG_UPDATE_390 \
        ARTICLENO=:ARTICLENO,\
        CONTRACTQTY=:CONTRACTQTY,\
        BRANCHNO=:BRANCHNO,\
        CUSTOMERNO=:CUSTOMERNO,\
        ADDDISCOUNTPCT=:ADDDISCOUNTPCT,\
        DATEFROM=:DATEFROM,\
        DATETO=:DATETO,\
        PHARMACYGROUPID=:PHARMACYGROUPID,\
        RESTQTY=:RESTQTY,\
        DISCOUNTCALCFROM=:DISCOUNTCALCFROM,\
        DISCOUNTAPPLYTO=:DISCOUNTAPPLYTO
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of ARTICLEOMG **********************************************/

#ifndef TRANSCLASS
typedef struct N_ARTICLEOMG {
    long ARTICLENO;
    long CONTRACTQTY;
    short BRANCHNO;
    long CUSTOMERNO;
    double ADDDISCOUNTPCT;
    long DATEFROM;
    long DATETO;
    char PHARMACYGROUPID[4];
    long RESTQTY;
    short DISCOUNTCALCFROM;
    short DISCOUNTAPPLYTO;
} articleomgS;
#else /* TRANSCLASS */
typedef struct N_ARTICLEOMG {
    long ARTICLENO;
    long CONTRACTQTY;
    short BRANCHNO;
    long CUSTOMERNO;
    double ADDDISCOUNTPCT;
    long DATEFROM;
    long DATETO;
    char PHARMACYGROUPID[4];
    long RESTQTY;
    short DISCOUNTCALCFROM;
    short DISCOUNTAPPLYTO;

    bool operator == (const N_ARTICLEOMG& right) const {
        return (
            ARTICLENO == right.ARTICLENO &&
            CONTRACTQTY == right.CONTRACTQTY &&
            BRANCHNO == right.BRANCHNO &&
            CUSTOMERNO == right.CUSTOMERNO &&
            ADDDISCOUNTPCT == right.ADDDISCOUNTPCT &&
            DATEFROM == right.DATEFROM &&
            DATETO == right.DATETO &&
            !strcmp(PHARMACYGROUPID, right.PHARMACYGROUPID) &&
            RESTQTY == right.RESTQTY &&
            DISCOUNTCALCFROM == right.DISCOUNTCALCFROM &&
            DISCOUNTAPPLYTO == right.DISCOUNTAPPLYTO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        ARTICLENO = 0;
        CONTRACTQTY = 0;
        BRANCHNO = 0;
        CUSTOMERNO = 0;
        ADDDISCOUNTPCT = 0;
        DATEFROM = 0;
        DATETO = 0;
        strcpy(PHARMACYGROUPID, " " );
        RESTQTY = 0;
        DISCOUNTCALCFROM = 0;
        DISCOUNTAPPLYTO = 1;
#endif
    }
} articleomgS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ARTICLEOMG ****************************************/

struct S_ARTICLEOMG {
    char ARTICLENO[11];
    char CONTRACTQTY[11];
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char ADDDISCOUNTPCT[5 + 2];
    char DATEFROM[11];
    char DATETO[11];
    char PHARMACYGROUPID[3 + 1];
    char RESTQTY[11];
    char DISCOUNTCALCFROM[7];
    char DISCOUNTAPPLYTO[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ARTICLEOMG ***********************/

struct O_ARTICLEOMG {
    char ARTICLENO[11];
    char CONTRACTQTY[11];
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char ADDDISCOUNTPCT[5];
    char DATEFROM[11];
    char DATETO[11];
    char PHARMACYGROUPID[3];
    char RESTQTY[11];
    char DISCOUNTCALCFROM[7];
    char DISCOUNTAPPLYTO[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ARTICLEOMG **********************************/

struct C_ARTICLEOMG {
    long ARTICLENO;
    long CONTRACTQTY;
    short BRANCHNO;
    long CUSTOMERNO;
    double ADDDISCOUNTPCT;
    long DATEFROM;
    long DATETO;
    char PHARMACYGROUPID[4];
    long RESTQTY;
    short DISCOUNTCALCFROM;
    short DISCOUNTAPPLYTO;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ARTICLEOMG ********************************/

struct I_ARTICLEOMG {
    short ARTICLENO;
    short CONTRACTQTY;
    short BRANCHNO;
    short CUSTOMERNO;
    short ADDDISCOUNTPCT;
    short DATEFROM;
    short DATETO;
    short PHARMACYGROUPID;
    short RESTQTY;
    short DISCOUNTCALCFROM;
    short DISCOUNTAPPLYTO;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ARTICLEOMG ******************************************/

#if defined (BUF_DESC)
static struct buf_desc ARTICLEOMG_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 5, 2 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 3, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc ARTICLEOMG_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 5, 2 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 3, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* description for datatypes of ARTICLEOMG ************************************/

 #define ARTICLEOMG_S390 \
         long ARTICLENO; \
         long CONTRACTQTY; \
         short BRANCHNO; \
         long CUSTOMERNO; \
         double ADDDISCOUNTPCT; \
         long DATEFROM; \
         long DATETO; \
         char PHARMACYGROUPID[4]; \
         long RESTQTY; \
         short DISCOUNTCALCFROM; \
         short DISCOUNTAPPLYTO; \



/* Copy-Function Struct to single Data ARTICLEOMG *****************************/

 #define ARTICLEOMG_S390_COPY_TO_SINGLE(_x_) \
         ARTICLENO=_x_->ARTICLENO;\
         CONTRACTQTY=_x_->CONTRACTQTY;\
         BRANCHNO=_x_->BRANCHNO;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
         ADDDISCOUNTPCT=_x_->ADDDISCOUNTPCT;\
         DATEFROM=_x_->DATEFROM;\
         DATETO=_x_->DATETO;\
          strcpy(PHARMACYGROUPID,_x_->PHARMACYGROUPID);\
         RESTQTY=_x_->RESTQTY;\
         DISCOUNTCALCFROM=_x_->DISCOUNTCALCFROM;\
         DISCOUNTAPPLYTO=_x_->DISCOUNTAPPLYTO;\

 #define ARTICLEOMG_S390_COPY_TO_STRUCT(_x_) \
          _x_->ARTICLENO=ARTICLENO;\
          _x_->CONTRACTQTY=CONTRACTQTY;\
          _x_->BRANCHNO=BRANCHNO;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->ADDDISCOUNTPCT=ADDDISCOUNTPCT;\
          _x_->DATEFROM=DATEFROM;\
          _x_->DATETO=DATETO;\
          strcpy(_x_->PHARMACYGROUPID,PHARMACYGROUPID);\
          _x_->RESTQTY=RESTQTY;\
          _x_->DISCOUNTCALCFROM=DISCOUNTCALCFROM;\
          _x_->DISCOUNTAPPLYTO=DISCOUNTAPPLYTO;\



/* FunctionNumber-Define of ArticleOMG ****************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of ArticleOMG ************************************/


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

class CARTICLEOMG : public ppDadeVirtual {
public:
    articleomgS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<articleomgS> lst; // class list

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
                     vector< articleomgS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     articleomgS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< articleomgS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<articleomgS>::iterator
                 beginList() { return lst.begin(); }
    vector<articleomgS>::iterator
                 endList  () { return lst.end  (); }

    long         GetArticleno() const { return s.ARTICLENO; }
    long         GetContractqty() const { return s.CONTRACTQTY; }
    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    double       GetAdddiscountpct() const { return s.ADDDISCOUNTPCT; }
    long         GetDatefrom() const { return s.DATEFROM; }
    long         GetDateto() const { return s.DATETO; }
    const char*  GetPharmacygroupid(ppString & t) const { t = s.PHARMACYGROUPID; t.erasespace(ppString::END); return t.c_str(); }
    long         GetRestqty() const { return s.RESTQTY; }
    short        GetDiscountcalcfrom() const { return s.DISCOUNTCALCFROM; }
    short        GetDiscountapplyto() const { return s.DISCOUNTAPPLYTO; }

    const articleomgS &
                 GetStruct() const { return s; }
    void         SetArticleno(long t) { s.ARTICLENO = t; }
    void         SetContractqty(long t) { s.CONTRACTQTY = t; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetAdddiscountpct(double t) { s.ADDDISCOUNTPCT = t; }
    void         SetDatefrom(long t) { s.DATEFROM = t; }
    void         SetDateto(long t) { s.DATETO = t; }
    void         SetPharmacygroupid(const ppString & t) { ppGStrCopy(s.PHARMACYGROUPID, t.c_str(), L_ARTICLEOMG_PHARMACYGROUPID); }
    void         SetRestqty(long t) { s.RESTQTY = t; }
    void         SetDiscountcalcfrom(short t) { s.DISCOUNTCALCFROM = t; }
    void         SetDiscountapplyto(short t) { s.DISCOUNTAPPLYTO = t; }

    void         SetStruct(const articleomgS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CARTICLEOMG() {
        ::buf_default((void *)&s, ARTICLEOMG_BES, ARTICLEOMG_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CARTICLEOMG() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, ARTICLEOMG_BES, ARTICLEOMG_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, ARTICLEOMG_BES, (int)ARTICLEOMG_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, ARTICLEOMG_BES, (int)ARTICLEOMG_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_ARTICLEOMG & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.PHARMACYGROUPID);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, ARTICLEOMG_BES, (int)ARTICLEOMG_ANZ, error_msg);
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
/* CreateSqlStatement of ARTICLEOMG *******************************************/

 #define ARTICLEOMG_CREATE(x) EXEC SQL create table x (\
         ARTICLENO integer default 0 not null,\
         CONTRACTQTY integer default 0 not null,\
         BRANCHNO smallint default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         ADDDISCOUNTPCT decimal(5,2) default 0 not null,\
         DATEFROM integer default 0 not null,\
         DATETO integer default 0 not null,\
         PHARMACYGROUPID char(3) default " " not null,\
         RESTQTY integer default 0 not null,\
         DISCOUNTCALCFROM smallint default 0 not null,\
         DISCOUNTAPPLYTO smallint default 1 not null) extent size 784 next size 80 lock mode row;



/* CreateIndexStatement of ARTICLEOMG *****************************************/

 #define ARTICLEOMG_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_tenderpos_1 on _X_(\
              TenderNo,\
              ArticleNo );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ARTICLEOMG *****************************************/

 #define ARTICLEOMG_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_tenderpos_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
