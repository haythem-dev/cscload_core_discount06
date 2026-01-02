#ifndef __PP_DELIVERYADVICEREMARK_H_
#define __PP_DELIVERYADVICEREMARK_H_

/******************************************************************************/
/* c:\prri\Headerfiles\Deliveryadviceremark ***********************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of DELIVERYADVICEREMARK **************************************/

#define L_DELIVERYADVICEREMARK_BRANCHNO 6
#define L_DELIVERYADVICEREMARK_CUSTOMERNO 11
#define L_DELIVERYADVICEREMARK_DELIVERYADVICEDATE 11
#define L_DELIVERYADVICEREMARK_CSCORDERNO 11
#define L_DELIVERYADVICEREMARK_REMARKTYPE 6
#define L_DELIVERYADVICEREMARK_SERIALNO 6
#define L_DELIVERYADVICEREMARK_REMARKTEXT 250
#define L_DELIVERYADVICEREMARK_CSCORDERPOSNO 11

/* Length/Count-Define of DELIVERYADVICEREMARK ********************************/

#define LS_DELIVERYADVICEREMARK_BRANCHNO 5 + 1
#define LS_DELIVERYADVICEREMARK_CUSTOMERNO 10 + 1
#define LS_DELIVERYADVICEREMARK_DELIVERYADVICEDATE 10 + 1
#define LS_DELIVERYADVICEREMARK_CSCORDERNO 10 + 1
#define LS_DELIVERYADVICEREMARK_REMARKTYPE 5 + 1
#define LS_DELIVERYADVICEREMARK_SERIALNO 5 + 1
#define LS_DELIVERYADVICEREMARK_REMARKTEXT 250 + 1
#define LS_DELIVERYADVICEREMARK_CSCORDERPOSNO 10 + 1

#define DELIVERYADVICEREMARKBRANCHNO 0
#define DELIVERYADVICEREMARKCUSTOMERNO 1
#define DELIVERYADVICEREMARKDELIVERYADVICEDATE 2
#define DELIVERYADVICEREMARKCSCORDERNO 3
#define DELIVERYADVICEREMARKREMARKTYPE 4
#define DELIVERYADVICEREMARKSERIALNO 5
#define DELIVERYADVICEREMARKREMARKTEXT 6
#define DELIVERYADVICEREMARKCSCORDERPOSNO 7

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define DELIVERYADVICEREMARK_H
#define DELIVERYADVICEREMARK_ANZ ( sizeof(DELIVERYADVICEREMARK_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of DELIVERYADVICEREMARK ******************************************/

#define DELIVERYADVICEREMARK_LISTE \
        DADUMMY.BRANCHNO,\
        DADUMMY.CUSTOMERNO,\
        DADUMMY.DELIVERYADVICEDATE,\
        DADUMMY.CSCORDERNO,\
        DADUMMY.REMARKTYPE,\
        DADUMMY.SERIALNO,\
        DADUMMY.REMARKTEXT,\
        DADUMMY.CSCORDERPOSNO
#define DELIVERYADVICEREMARK_LISTE_390 \
        BRANCHNO,\
        CUSTOMERNO,\
        DELIVERYADVICEDATE,\
        CSCORDERNO,\
        REMARKTYPE,\
        SERIALNO,\
        REMARKTEXT,\
        CSCORDERPOSNO
#define DELIVERYADVICEREMARK_PLISTE \
        "DADUMMY.BRANCHNO,"\
        "DADUMMY.CUSTOMERNO,"\
        "DADUMMY.DELIVERYADVICEDATE,"\
        "DADUMMY.CSCORDERNO,"\
        "DADUMMY.REMARKTYPE,"\
        "DADUMMY.SERIALNO,"\
        "DADUMMY.REMARKTEXT,"\
        "DADUMMY.CSCORDERPOSNO"
#define DELIVERYADVICEREMARK_PELISTE \
        "BRANCHNO,"\
        "CUSTOMERNO,"\
        "DELIVERYADVICEDATE,"\
        "CSCORDERNO,"\
        "REMARKTYPE,"\
        "SERIALNO,"\
        "REMARKTEXT,"\
        "CSCORDERPOSNO"
#define DELIVERYADVICEREMARK_UPDLISTE \
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "DELIVERYADVICEDATE=?,"\
        "CSCORDERNO=?,"\
        "REMARKTYPE=?,"\
        "SERIALNO=?,"\
        "REMARKTEXT=?,"\
        "CSCORDERPOSNO=?"
/* SqlMacros-Define of DELIVERYADVICEREMARK ***********************************/

#define DELIVERYADVICEREMARK_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->DELIVERYADVICEDATE,\
        :x->CSCORDERNO,\
        :x->REMARKTYPE,\
        :x->SERIALNO,\
        :x->REMARKTEXT,\
        :x->CSCORDERPOSNO
#define DELIVERYADVICEREMARK_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->DELIVERYADVICEDATE,\
        :x->CSCORDERNO,\
        :x->REMARKTYPE,\
        :x->SERIALNO,\
        :x->REMARKTEXT,\
        :x->CSCORDERPOSNO
#define DELIVERYADVICEREMARK_UPDATE(x) \
        DADUMMY.BRANCHNO=:x->BRANCHNO,\
        DADUMMY.CUSTOMERNO=:x->CUSTOMERNO,\
        DADUMMY.DELIVERYADVICEDATE=:x->DELIVERYADVICEDATE,\
        DADUMMY.CSCORDERNO=:x->CSCORDERNO,\
        DADUMMY.REMARKTYPE=:x->REMARKTYPE,\
        DADUMMY.SERIALNO=:x->SERIALNO,\
        DADUMMY.REMARKTEXT=:x->REMARKTEXT,\
        DADUMMY.CSCORDERPOSNO=:x->CSCORDERPOSNO
/* SqlMacros390-Define of DELIVERYADVICEREMARK ********************************/

#define DELIVERYADVICEREMARK_ZEIGER_390 \
        :BRANCHNO,\
        :CUSTOMERNO,\
        :DELIVERYADVICEDATE,\
        :CSCORDERNO,\
        :REMARKTYPE,\
        :SERIALNO,\
        :REMARKTEXT,\
        :CSCORDERPOSNO
#define DELIVERYADVICEREMARK_UPDATE_390 \
        BRANCHNO=:BRANCHNO,\
        CUSTOMERNO=:CUSTOMERNO,\
        DELIVERYADVICEDATE=:DELIVERYADVICEDATE,\
        CSCORDERNO=:CSCORDERNO,\
        REMARKTYPE=:REMARKTYPE,\
        SERIALNO=:SERIALNO,\
        REMARKTEXT=:REMARKTEXT,\
        CSCORDERPOSNO=:CSCORDERPOSNO
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of DELIVERYADVICEREMARK ************************************/

#ifndef TRANSCLASS
typedef struct N_DELIVERYADVICEREMARK {
    short BRANCHNO;
    long CUSTOMERNO;
    long DELIVERYADVICEDATE;
    long CSCORDERNO;
    short REMARKTYPE;
    short SERIALNO;
    char REMARKTEXT[251];
    long CSCORDERPOSNO;
} deliveryadviceremarkS;
#else /* TRANSCLASS */
typedef struct N_DELIVERYADVICEREMARK {
    short BRANCHNO;
    long CUSTOMERNO;
    long DELIVERYADVICEDATE;
    long CSCORDERNO;
    short REMARKTYPE;
    short SERIALNO;
    char REMARKTEXT[251];
    long CSCORDERPOSNO;

    bool operator == (const N_DELIVERYADVICEREMARK& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            CUSTOMERNO == right.CUSTOMERNO &&
            DELIVERYADVICEDATE == right.DELIVERYADVICEDATE &&
            CSCORDERNO == right.CSCORDERNO &&
            REMARKTYPE == right.REMARKTYPE &&
            SERIALNO == right.SERIALNO &&
            !strcmp(REMARKTEXT, right.REMARKTEXT) &&
            CSCORDERPOSNO == right.CSCORDERPOSNO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        CUSTOMERNO = 0;
        DELIVERYADVICEDATE = 0;
        CSCORDERNO = 0;
        REMARKTYPE = 0;
        SERIALNO = 0;
        strcpy(REMARKTEXT, " " );
        CSCORDERPOSNO = 0;
#endif
    }
} deliveryadviceremarkS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of DELIVERYADVICEREMARK ******************************/

struct S_DELIVERYADVICEREMARK {
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char DELIVERYADVICEDATE[11];
    char CSCORDERNO[11];
    char REMARKTYPE[7];
    char SERIALNO[7];
    char REMARKTEXT[250 + 1];
    char CSCORDERPOSNO[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of DELIVERYADVICEREMARK *************/

struct O_DELIVERYADVICEREMARK {
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char DELIVERYADVICEDATE[11];
    char CSCORDERNO[11];
    char REMARKTYPE[7];
    char SERIALNO[7];
    char REMARKTEXT[250];
    char CSCORDERPOSNO[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of DELIVERYADVICEREMARK ************************/

struct C_DELIVERYADVICEREMARK {
    short BRANCHNO;
    long CUSTOMERNO;
    long DELIVERYADVICEDATE;
    long CSCORDERNO;
    short REMARKTYPE;
    short SERIALNO;
    char REMARKTEXT[251];
    long CSCORDERPOSNO;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of DELIVERYADVICEREMARK **********************/

struct I_DELIVERYADVICEREMARK {
    short BRANCHNO;
    short CUSTOMERNO;
    short DELIVERYADVICEDATE;
    short CSCORDERNO;
    short REMARKTYPE;
    short SERIALNO;
    short REMARKTEXT;
    short CSCORDERPOSNO;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of DELIVERYADVICEREMARK ********************************/

#if defined (BUF_DESC)
static struct buf_desc DELIVERYADVICEREMARK_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 250, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc DELIVERYADVICEREMARK_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 250, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* description for datatypes of DELIVERYADVICEREMARK **************************/

 #define DELIVERYADVICEREMARK_S390 \
         short BRANCHNO; \
         long CUSTOMERNO; \
         long DELIVERYADVICEDATE; \
         long CSCORDERNO; \
         short REMARKTYPE; \
         short SERIALNO; \
         char REMARKTEXT[251]; \
         long CSCORDERPOSNO; \



/* Copy-Function Struct to single Data DELIVERYADVICEREMARK *******************/

 #define DELIVERYADVICEREMARK_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
         DELIVERYADVICEDATE=_x_->DELIVERYADVICEDATE;\
         CSCORDERNO=_x_->CSCORDERNO;\
         REMARKTYPE=_x_->REMARKTYPE;\
         SERIALNO=_x_->SERIALNO;\
          strcpy(REMARKTEXT,_x_->REMARKTEXT);\
         CSCORDERPOSNO=_x_->CSCORDERPOSNO;\

 #define DELIVERYADVICEREMARK_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->DELIVERYADVICEDATE=DELIVERYADVICEDATE;\
          _x_->CSCORDERNO=CSCORDERNO;\
          _x_->REMARKTYPE=REMARKTYPE;\
          _x_->SERIALNO=SERIALNO;\
          strcpy(_x_->REMARKTEXT,REMARKTEXT);\
          _x_->CSCORDERPOSNO=CSCORDERPOSNO;\



/* FunctionNumber-Define of Deliveryadviceremark ******************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of Deliveryadviceremark **************************/


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

class CDELIVERYADVICEREMARK : public ppDadeVirtual {
public:
    deliveryadviceremarkS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<deliveryadviceremarkS> lst; // class list

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
                     vector< deliveryadviceremarkS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     deliveryadviceremarkS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< deliveryadviceremarkS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<deliveryadviceremarkS>::iterator
                 beginList() { return lst.begin(); }
    vector<deliveryadviceremarkS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    long         GetDeliveryadvicedate() const { return s.DELIVERYADVICEDATE; }
    long         GetCscorderno() const { return s.CSCORDERNO; }
    short        GetRemarktype() const { return s.REMARKTYPE; }
    short        GetSerialno() const { return s.SERIALNO; }
    const char*  GetRemarktext(ppString & t) const { t = s.REMARKTEXT; t.erasespace(ppString::END); return t.c_str(); }
    long         GetCscorderposno() const { return s.CSCORDERPOSNO; }

    const deliveryadviceremarkS &
                 GetStruct() const { return s; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetDeliveryadvicedate(long t) { s.DELIVERYADVICEDATE = t; }
    void         SetCscorderno(long t) { s.CSCORDERNO = t; }
    void         SetRemarktype(short t) { s.REMARKTYPE = t; }
    void         SetSerialno(short t) { s.SERIALNO = t; }
    void         SetRemarktext(const ppString & t) { ppGStrCopy(s.REMARKTEXT, t.c_str(), L_DELIVERYADVICEREMARK_REMARKTEXT); }
    void         SetCscorderposno(long t) { s.CSCORDERPOSNO = t; }

    void         SetStruct(const deliveryadviceremarkS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CDELIVERYADVICEREMARK() {
        ::buf_default((void *)&s, DELIVERYADVICEREMARK_BES, DELIVERYADVICEREMARK_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CDELIVERYADVICEREMARK() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, DELIVERYADVICEREMARK_BES, DELIVERYADVICEREMARK_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, DELIVERYADVICEREMARK_BES, (int)DELIVERYADVICEREMARK_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, DELIVERYADVICEREMARK_BES, (int)DELIVERYADVICEREMARK_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_DELIVERYADVICEREMARK & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.REMARKTEXT);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, DELIVERYADVICEREMARK_BES, (int)DELIVERYADVICEREMARK_ANZ, error_msg);
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
/* CreateSqlStatement of DELIVERYADVICEREMARK *********************************/

 #define DELIVERYADVICEREMARK_CREATE(x) EXEC SQL create table x (\
         BRANCHNO smallint default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         DELIVERYADVICEDATE integer default 0 not null,\
         CSCORDERNO integer default 0 not null,\
         REMARKTYPE smallint default 0 not null,\
         SERIALNO smallint default 0 not null,\
         REMARKTEXT varchar(250,0) default " " not null,\
         CSCORDERPOSNO integer default 0 not null) extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of DELIVERYADVICEREMARK *******************************/

 #define DELIVERYADVICEREMARK_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
/* DeleteIndexStatement of DELIVERYADVICEREMARK *******************************/

 #define DELIVERYADVICEREMARK_DELETE_INDEX(_X_)\
              _X_ = 0;\


#endif   // GUARD
