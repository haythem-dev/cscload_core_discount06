#ifndef __PP_TENDERHEAD_H_
#define __PP_TENDERHEAD_H_

/******************************************************************************/
/* c:\prri\Headerfiles\TenderHead *********************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of TENDERHEAD ************************************************/

#define L_TENDERHEAD_TENDERNO 11
#define L_TENDERHEAD_TENDERTYPE 11
#define L_TENDERHEAD_CONTRACTNO 48
#define L_TENDERHEAD_BRANCHNO 6
#define L_TENDERHEAD_CUSTOMERNO 11
#define L_TENDERHEAD_ACCBRANCHNO 6
#define L_TENDERHEAD_ACCCUSTOMERNO 11
#define L_TENDERHEAD_DATEFROM 11
#define L_TENDERHEAD_DATETO 11
#define L_TENDERHEAD_EXCEEDANCEPCT 5
#define N_TENDERHEAD_EXCEEDANCEPCT 2
#define L_TENDERHEAD_TENDERSTATE 1
#define L_TENDERHEAD_CHANGEDATE 11
#define L_TENDERHEAD_NAMEOFUSER 30
#define L_TENDERHEAD_PHARMACYCHAINNO 11

/* Length/Count-Define of TENDERHEAD ******************************************/

#define LS_TENDERHEAD_TENDERNO 10 + 1
#define LS_TENDERHEAD_TENDERTYPE 10 + 1
#define LS_TENDERHEAD_CONTRACTNO 48 + 1
#define LS_TENDERHEAD_BRANCHNO 5 + 1
#define LS_TENDERHEAD_CUSTOMERNO 10 + 1
#define LS_TENDERHEAD_ACCBRANCHNO 5 + 1
#define LS_TENDERHEAD_ACCCUSTOMERNO 10 + 1
#define LS_TENDERHEAD_DATEFROM 10 + 1
#define LS_TENDERHEAD_DATETO 10 + 1
#define LS_TENDERHEAD_EXCEEDANCEPCT 5 + 2
#define LS_TENDERHEAD_TENDERSTATE 1 + 1
#define LS_TENDERHEAD_CHANGEDATE 10 + 1
#define LS_TENDERHEAD_NAMEOFUSER 30 + 1
#define LS_TENDERHEAD_PHARMACYCHAINNO 10 + 1

#define TENDERHEADTENDERNO 0
#define TENDERHEADTENDERTYPE 1
#define TENDERHEADCONTRACTNO 2
#define TENDERHEADBRANCHNO 3
#define TENDERHEADCUSTOMERNO 4
#define TENDERHEADACCBRANCHNO 5
#define TENDERHEADACCCUSTOMERNO 6
#define TENDERHEADDATEFROM 7
#define TENDERHEADDATETO 8
#define TENDERHEADEXCEEDANCEPCT 9
#define TENDERHEADTENDERSTATE 10
#define TENDERHEADCHANGEDATE 11
#define TENDERHEADNAMEOFUSER 12
#define TENDERHEADPHARMACYCHAINNO 13

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define TENDERHEAD_H
#define TENDERHEAD_ANZ ( sizeof(TENDERHEAD_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of TENDERHEAD ****************************************************/

#define TENDERHEAD_LISTE \
        TENDERHEAD.TENDERNO,\
        TENDERHEAD.TENDERTYPE,\
        TENDERHEAD.CONTRACTNO,\
        TENDERHEAD.BRANCHNO,\
        TENDERHEAD.CUSTOMERNO,\
        TENDERHEAD.ACCBRANCHNO,\
        TENDERHEAD.ACCCUSTOMERNO,\
        TENDERHEAD.DATEFROM,\
        TENDERHEAD.DATETO,\
        TENDERHEAD.EXCEEDANCEPCT,\
        TENDERHEAD.TENDERSTATE,\
        TENDERHEAD.CHANGEDATE,\
        TENDERHEAD.NAMEOFUSER,\
        TENDERHEAD.PHARMACYCHAINNO
#define TENDERHEAD_LISTE_390 \
        TENDERNO,\
        TENDERTYPE,\
        CONTRACTNO,\
        BRANCHNO,\
        CUSTOMERNO,\
        ACCBRANCHNO,\
        ACCCUSTOMERNO,\
        DATEFROM,\
        DATETO,\
        EXCEEDANCEPCT,\
        TENDERSTATE,\
        CHANGEDATE,\
        NAMEOFUSER,\
        PHARMACYCHAINNO
#define TENDERHEAD_PLISTE \
        "TENDERHEAD.TENDERNO,"\
        "TENDERHEAD.TENDERTYPE,"\
        "TENDERHEAD.CONTRACTNO,"\
        "TENDERHEAD.BRANCHNO,"\
        "TENDERHEAD.CUSTOMERNO,"\
        "TENDERHEAD.ACCBRANCHNO,"\
        "TENDERHEAD.ACCCUSTOMERNO,"\
        "TENDERHEAD.DATEFROM,"\
        "TENDERHEAD.DATETO,"\
        "TENDERHEAD.EXCEEDANCEPCT,"\
        "TENDERHEAD.TENDERSTATE,"\
        "TENDERHEAD.CHANGEDATE,"\
        "TENDERHEAD.NAMEOFUSER,"\
        "TENDERHEAD.PHARMACYCHAINNO"
#define TENDERHEAD_PELISTE \
        "TENDERNO,"\
        "TENDERTYPE,"\
        "CONTRACTNO,"\
        "BRANCHNO,"\
        "CUSTOMERNO,"\
        "ACCBRANCHNO,"\
        "ACCCUSTOMERNO,"\
        "DATEFROM,"\
        "DATETO,"\
        "EXCEEDANCEPCT,"\
        "TENDERSTATE,"\
        "CHANGEDATE,"\
        "NAMEOFUSER,"\
        "PHARMACYCHAINNO"
#define TENDERHEAD_UPDLISTE \
        "TENDERNO=?,"\
        "TENDERTYPE=?,"\
        "CONTRACTNO=?,"\
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "ACCBRANCHNO=?,"\
        "ACCCUSTOMERNO=?,"\
        "DATEFROM=?,"\
        "DATETO=?,"\
        "EXCEEDANCEPCT=?,"\
        "TENDERSTATE=?,"\
        "CHANGEDATE=?,"\
        "NAMEOFUSER=?,"\
        "PHARMACYCHAINNO=?"
/* SqlMacros-Define of TENDERHEAD *********************************************/

#define TENDERHEAD_ZEIGER(x) \
        :x->TENDERNO,\
        :x->TENDERTYPE,\
        :x->CONTRACTNO,\
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->ACCBRANCHNO,\
        :x->ACCCUSTOMERNO,\
        :x->DATEFROM,\
        :x->DATETO,\
        :x->EXCEEDANCEPCT,\
        :x->TENDERSTATE,\
        :x->CHANGEDATE,\
        :x->NAMEOFUSER,\
        :x->PHARMACYCHAINNO
#define TENDERHEAD_ZEIGERSEL(x) \
        :x->TENDERNO,\
        :x->TENDERTYPE,\
        :x->CONTRACTNO,\
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->ACCBRANCHNO,\
        :x->ACCCUSTOMERNO,\
        :x->DATEFROM,\
        :x->DATETO,\
        :x->EXCEEDANCEPCT,\
        :x->TENDERSTATE,\
        :x->CHANGEDATE,\
        :x->NAMEOFUSER,\
        :x->PHARMACYCHAINNO
#define TENDERHEAD_UPDATE(x) \
        TENDERHEAD.TENDERNO=:x->TENDERNO,\
        TENDERHEAD.TENDERTYPE=:x->TENDERTYPE,\
        TENDERHEAD.CONTRACTNO=:x->CONTRACTNO,\
        TENDERHEAD.BRANCHNO=:x->BRANCHNO,\
        TENDERHEAD.CUSTOMERNO=:x->CUSTOMERNO,\
        TENDERHEAD.ACCBRANCHNO=:x->ACCBRANCHNO,\
        TENDERHEAD.ACCCUSTOMERNO=:x->ACCCUSTOMERNO,\
        TENDERHEAD.DATEFROM=:x->DATEFROM,\
        TENDERHEAD.DATETO=:x->DATETO,\
        TENDERHEAD.EXCEEDANCEPCT=:x->EXCEEDANCEPCT,\
        TENDERHEAD.TENDERSTATE=:x->TENDERSTATE,\
        TENDERHEAD.CHANGEDATE=:x->CHANGEDATE,\
        TENDERHEAD.NAMEOFUSER=:x->NAMEOFUSER,\
        TENDERHEAD.PHARMACYCHAINNO=:x->PHARMACYCHAINNO
/* SqlMacros390-Define of TENDERHEAD ******************************************/

#define TENDERHEAD_ZEIGER_390 \
        :TENDERNO,\
        :TENDERTYPE,\
        :CONTRACTNO,\
        :BRANCHNO,\
        :CUSTOMERNO,\
        :ACCBRANCHNO,\
        :ACCCUSTOMERNO,\
        :DATEFROM,\
        :DATETO,\
        :EXCEEDANCEPCT,\
        :TENDERSTATE,\
        :CHANGEDATE,\
        :NAMEOFUSER,\
        :PHARMACYCHAINNO
#define TENDERHEAD_UPDATE_390 \
        TENDERNO=:TENDERNO,\
        TENDERTYPE=:TENDERTYPE,\
        CONTRACTNO=:CONTRACTNO,\
        BRANCHNO=:BRANCHNO,\
        CUSTOMERNO=:CUSTOMERNO,\
        ACCBRANCHNO=:ACCBRANCHNO,\
        ACCCUSTOMERNO=:ACCCUSTOMERNO,\
        DATEFROM=:DATEFROM,\
        DATETO=:DATETO,\
        EXCEEDANCEPCT=:EXCEEDANCEPCT,\
        TENDERSTATE=:TENDERSTATE,\
        CHANGEDATE=:CHANGEDATE,\
        NAMEOFUSER=:NAMEOFUSER,\
        PHARMACYCHAINNO=:PHARMACYCHAINNO
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of TENDERHEAD **********************************************/

#ifndef TRANSCLASS
typedef struct N_TENDERHEAD {
    long TENDERNO;
    long TENDERTYPE;
    char CONTRACTNO[49];
    short BRANCHNO;
    long CUSTOMERNO;
    short ACCBRANCHNO;
    long ACCCUSTOMERNO;
    long DATEFROM;
    long DATETO;
    double EXCEEDANCEPCT;
    char TENDERSTATE[2];
    long CHANGEDATE;
    char NAMEOFUSER[31];
    long PHARMACYCHAINNO;
} tenderheadS;
#else /* TRANSCLASS */
typedef struct N_TENDERHEAD {
    long TENDERNO;
    long TENDERTYPE;
    char CONTRACTNO[49];
    short BRANCHNO;
    long CUSTOMERNO;
    short ACCBRANCHNO;
    long ACCCUSTOMERNO;
    long DATEFROM;
    long DATETO;
    double EXCEEDANCEPCT;
    char TENDERSTATE[2];
    long CHANGEDATE;
    char NAMEOFUSER[31];
    long PHARMACYCHAINNO;

    bool operator == (const N_TENDERHEAD& right) const {
        return (
            TENDERNO == right.TENDERNO &&
            TENDERTYPE == right.TENDERTYPE &&
            !strcmp(CONTRACTNO, right.CONTRACTNO) &&
            BRANCHNO == right.BRANCHNO &&
            CUSTOMERNO == right.CUSTOMERNO &&
            ACCBRANCHNO == right.ACCBRANCHNO &&
            ACCCUSTOMERNO == right.ACCCUSTOMERNO &&
            DATEFROM == right.DATEFROM &&
            DATETO == right.DATETO &&
            EXCEEDANCEPCT == right.EXCEEDANCEPCT &&
            !strcmp(TENDERSTATE, right.TENDERSTATE) &&
            CHANGEDATE == right.CHANGEDATE &&
            !strcmp(NAMEOFUSER, right.NAMEOFUSER) &&
            PHARMACYCHAINNO == right.PHARMACYCHAINNO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        TENDERNO = 0;
        TENDERTYPE = 0;
        strcpy(CONTRACTNO, " " );
        BRANCHNO = 0;
        CUSTOMERNO = 0;
        ACCBRANCHNO = 0;
        ACCCUSTOMERNO = 0;
        DATEFROM = 0;
        DATETO = 0;
        EXCEEDANCEPCT = 0;
        strcpy(TENDERSTATE, " " );
        CHANGEDATE = 0;
        strcpy(NAMEOFUSER, " " );
        PHARMACYCHAINNO = 0;
#endif
    }
} tenderheadS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of TENDERHEAD ****************************************/

struct S_TENDERHEAD {
    char TENDERNO[11];
    char TENDERTYPE[11];
    char CONTRACTNO[48 + 1];
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char ACCBRANCHNO[7];
    char ACCCUSTOMERNO[11];
    char DATEFROM[11];
    char DATETO[11];
    char EXCEEDANCEPCT[5 + 2];
    char TENDERSTATE[1 + 1];
    char CHANGEDATE[11];
    char NAMEOFUSER[30 + 1];
    char PHARMACYCHAINNO[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of TENDERHEAD ***********************/

struct O_TENDERHEAD {
    char TENDERNO[11];
    char TENDERTYPE[11];
    char CONTRACTNO[48];
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char ACCBRANCHNO[7];
    char ACCCUSTOMERNO[11];
    char DATEFROM[11];
    char DATETO[11];
    char EXCEEDANCEPCT[5];
    char TENDERSTATE[1];
    char CHANGEDATE[11];
    char NAMEOFUSER[30];
    char PHARMACYCHAINNO[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of TENDERHEAD **********************************/

struct C_TENDERHEAD {
    long TENDERNO;
    long TENDERTYPE;
    char CONTRACTNO[49];
    short BRANCHNO;
    long CUSTOMERNO;
    short ACCBRANCHNO;
    long ACCCUSTOMERNO;
    long DATEFROM;
    long DATETO;
    double EXCEEDANCEPCT;
    char TENDERSTATE;
    long CHANGEDATE;
    char NAMEOFUSER[31];
    long PHARMACYCHAINNO;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of TENDERHEAD ********************************/

struct I_TENDERHEAD {
    short TENDERNO;
    short TENDERTYPE;
    short CONTRACTNO;
    short BRANCHNO;
    short CUSTOMERNO;
    short ACCBRANCHNO;
    short ACCCUSTOMERNO;
    short DATEFROM;
    short DATETO;
    short EXCEEDANCEPCT;
    short TENDERSTATE;
    short CHANGEDATE;
    short NAMEOFUSER;
    short PHARMACYCHAINNO;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of TENDERHEAD ******************************************/

#if defined (BUF_DESC)
static struct buf_desc TENDERHEAD_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 48, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 5, 2 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc TENDERHEAD_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 48, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 5, 2 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* description for datatypes of TENDERHEAD ************************************/

 #define TENDERHEAD_S390 \
         long TENDERNO; \
         long TENDERTYPE; \
         char CONTRACTNO[49]; \
         short BRANCHNO; \
         long CUSTOMERNO; \
         short ACCBRANCHNO; \
         long ACCCUSTOMERNO; \
         long DATEFROM; \
         long DATETO; \
         double EXCEEDANCEPCT; \
         char TENDERSTATE; \
         long CHANGEDATE; \
         char NAMEOFUSER[31]; \
         long PHARMACYCHAINNO; \



/* Copy-Function Struct to single Data TENDERHEAD *****************************/

 #define TENDERHEAD_S390_COPY_TO_SINGLE(_x_) \
         TENDERNO=_x_->TENDERNO;\
         TENDERTYPE=_x_->TENDERTYPE;\
          strcpy(CONTRACTNO,_x_->CONTRACTNO);\
         BRANCHNO=_x_->BRANCHNO;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
         ACCBRANCHNO=_x_->ACCBRANCHNO;\
         ACCCUSTOMERNO=_x_->ACCCUSTOMERNO;\
         DATEFROM=_x_->DATEFROM;\
         DATETO=_x_->DATETO;\
         EXCEEDANCEPCT=_x_->EXCEEDANCEPCT;\
         TENDERSTATE=_x_->TENDERSTATE;\
         CHANGEDATE=_x_->CHANGEDATE;\
          strcpy(NAMEOFUSER,_x_->NAMEOFUSER);\
         PHARMACYCHAINNO=_x_->PHARMACYCHAINNO;\

 #define TENDERHEAD_S390_COPY_TO_STRUCT(_x_) \
          _x_->TENDERNO=TENDERNO;\
          _x_->TENDERTYPE=TENDERTYPE;\
          strcpy(_x_->CONTRACTNO,CONTRACTNO);\
          _x_->BRANCHNO=BRANCHNO;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->ACCBRANCHNO=ACCBRANCHNO;\
          _x_->ACCCUSTOMERNO=ACCCUSTOMERNO;\
          _x_->DATEFROM=DATEFROM;\
          _x_->DATETO=DATETO;\
          _x_->EXCEEDANCEPCT=EXCEEDANCEPCT;\
          _x_->TENDERSTATE=TENDERSTATE;\
          _x_->CHANGEDATE=CHANGEDATE;\
          strcpy(_x_->NAMEOFUSER,NAMEOFUSER);\
          _x_->PHARMACYCHAINNO=PHARMACYCHAINNO;\



/* FunctionNumber-Define of TenderHead ****************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of TenderHead ************************************/


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

class CTENDERHEAD : public ppDadeVirtual {
public:
    tenderheadS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<tenderheadS> lst; // class list

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
                     vector< tenderheadS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     tenderheadS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< tenderheadS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<tenderheadS>::iterator
                 beginList() { return lst.begin(); }
    vector<tenderheadS>::iterator
                 endList  () { return lst.end  (); }

    long         GetTenderno() const { return s.TENDERNO; }
    long         GetTendertype() const { return s.TENDERTYPE; }
    const char*  GetContractno(ppString & t) const { t = s.CONTRACTNO; t.erasespace(ppString::END); return t.c_str(); }
    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    short        GetAccbranchno() const { return s.ACCBRANCHNO; }
    long         GetAcccustomerno() const { return s.ACCCUSTOMERNO; }
    long         GetDatefrom() const { return s.DATEFROM; }
    long         GetDateto() const { return s.DATETO; }
    double       GetExceedancepct() const { return s.EXCEEDANCEPCT; }
    char         GetTenderstate() const { return s.TENDERSTATE[0]; }
    long         GetChangedate() const { return s.CHANGEDATE; }
    const char*  GetNameofuser(ppString & t) const { t = s.NAMEOFUSER; t.erasespace(ppString::END); return t.c_str(); }
    long         GetPharmacychainno() const { return s.PHARMACYCHAINNO; }

    const tenderheadS &
                 GetStruct() const { return s; }
    void         SetTenderno(long t) { s.TENDERNO = t; }
    void         SetTendertype(long t) { s.TENDERTYPE = t; }
    void         SetContractno(const ppString & t) { ppGStrCopy(s.CONTRACTNO, t.c_str(), L_TENDERHEAD_CONTRACTNO); }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetAccbranchno(short t) { s.ACCBRANCHNO = t; }
    void         SetAcccustomerno(long t) { s.ACCCUSTOMERNO = t; }
    void         SetDatefrom(long t) { s.DATEFROM = t; }
    void         SetDateto(long t) { s.DATETO = t; }
    void         SetExceedancepct(double t) { s.EXCEEDANCEPCT = t; }
    void         SetTenderstate(char t) { s.TENDERSTATE[0] = t; s.TENDERSTATE[1] = '\0';}
    void         SetChangedate(long t) { s.CHANGEDATE = t; }
    void         SetNameofuser(const ppString & t) { ppGStrCopy(s.NAMEOFUSER, t.c_str(), L_TENDERHEAD_NAMEOFUSER); }
    void         SetPharmacychainno(long t) { s.PHARMACYCHAINNO = t; }

    void         SetStruct(const tenderheadS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CTENDERHEAD() {
        ::buf_default((void *)&s, TENDERHEAD_BES, TENDERHEAD_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CTENDERHEAD() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, TENDERHEAD_BES, TENDERHEAD_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, TENDERHEAD_BES, (int)TENDERHEAD_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, TENDERHEAD_BES, (int)TENDERHEAD_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_TENDERHEAD & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.CONTRACTNO);
        ppGStripLast(d.NAMEOFUSER);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, TENDERHEAD_BES, (int)TENDERHEAD_ANZ, error_msg);
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
/* CreateSqlStatement of TENDERHEAD *******************************************/

 #define TENDERHEAD_CREATE(x) EXEC SQL create table x (\
         TENDERNO integer default 0 not null,\
         TENDERTYPE integer default 0 not null,\
         CONTRACTNO varchar(48,0) default " " not null,\
         BRANCHNO smallint default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         ACCBRANCHNO smallint default 0 not null,\
         ACCCUSTOMERNO integer default 0 not null,\
         DATEFROM integer default 0 not null,\
         DATETO integer default 0 not null,\
         EXCEEDANCEPCT decimal(5,2) default 0 not null,\
         TENDERSTATE char(1) default " " not null,\
         CHANGEDATE integer default 0 not null,\
         NAMEOFUSER varchar(30,0) default " " not null,\
         PHARMACYCHAINNO integer default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of TENDERHEAD *****************************************/

 #define TENDERHEAD_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_tenderhead_1 on _X_(\
              TenderNo ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index i_tenderhead_2 on _X_(\
              BranchNo,\
              CustomerNo ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of TENDERHEAD *****************************************/

 #define TENDERHEAD_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_tenderhead_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_tenderhead_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
