#ifndef __PP_KDAUFTRAGPARTNERFUNCTION_H_
#define __PP_KDAUFTRAGPARTNERFUNCTION_H_

/******************************************************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <pplib/bufkon.h>

/* Length-Define of KDAUFTRAGPARTNERFUNCTION **********************************/

#define L_KDAUFTRAGPARTNERFUNCTION_KDAUFTRAGNR 11
#define L_KDAUFTRAGPARTNERFUNCTION_PARTNERFUNCTION 2
#define L_KDAUFTRAGPARTNERFUNCTION_SAPKUNNR 10

/* Length/Count-Define of KDAUFTRAGPARTNERFUNCTION ****************************/

#define LS_KDAUFTRAGPARTNERFUNCTION_KDAUFTRAGNR 10 + 1
#define LS_KDAUFTRAGPARTNERFUNCTION_PARTNERFUNCTION 2 + 1
#define LS_KDAUFTRAGPARTNERFUNCTION_SAPKUNNR 10 + 1

#define KDAUFTRAGPARTNERFUNCTIONKDAUFTRAGNR 0
#define KDAUFTRAGPARTNERFUNCTIONPARTNERFUNCTION 1
#define KDAUFTRAGPARTNERFUNCTIONSAPKUNNR 2

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define KDAUFTRAGPARTNERFUNCTION_H
#define KDAUFTRAGPARTNERFUNCTION_ANZ ( sizeof(KDAUFTRAGPARTNERFUNCTION_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of KDAUFTRAGPARTNERFUNCTION **************************************/

#define KDAUFTRAGPARTNERFUNCTION_LISTE \
        KDAUFTRAGPARTNERFUNCTION.KDAUFTRAGNR,\
        KDAUFTRAGPARTNERFUNCTION.PARTNERFUNCTION,\
        KDAUFTRAGPARTNERFUNCTION.SAPKUNNR
#define KDAUFTRAGPARTNERFUNCTION_LISTE_390 \
        KDAUFTRAGNR,\
        PARTNERFUNCTION,\
        SAPKUNNR
#define KDAUFTRAGPARTNERFUNCTION_PLISTE \
        "KDAUFTRAGPARTNERFUNCTION.KDAUFTRAGNR,"\
        "KDAUFTRAGPARTNERFUNCTION.PARTNERFUNCTION,"\
        "KDAUFTRAGPARTNERFUNCTION.SAPKUNNR"
#define KDAUFTRAGPARTNERFUNCTION_PELISTE \
        "KDAUFTRAGNR,"\
        "PARTNERFUNCTION,"\
        "SAPKUNNR"
#define KDAUFTRAGPARTNERFUNCTION_UPDLISTE \
        "KDAUFTRAGNR=?,"\
        "PARTNERFUNCTION=?,"\
        "SAPKUNNR=?"
/* SqlMacros-Define of KDAUFTRAGPARTNERFUNCTION *******************************/

#define KDAUFTRAGPARTNERFUNCTION_ZEIGER(x) \
        :x->KDAUFTRAGNR,\
        :x->PARTNERFUNCTION,\
        :x->SAPKUNNR
#define KDAUFTRAGPARTNERFUNCTION_ZEIGERSEL(x) \
        :x->KDAUFTRAGNR,\
        :x->PARTNERFUNCTION,\
        :x->SAPKUNNR
#define KDAUFTRAGPARTNERFUNCTION_UPDATE(x) \
        KDAUFTRAGPARTNERFUNCTION.KDAUFTRAGNR=:x->KDAUFTRAGNR,\
        KDAUFTRAGPARTNERFUNCTION.PARTNERFUNCTION=:x->PARTNERFUNCTION,\
        KDAUFTRAGPARTNERFUNCTION.SAPKUNNR=:x->SAPKUNNR
/* SqlMacros390-Define of KDAUFTRAGPARTNERFUNCTION ****************************/

#define KDAUFTRAGPARTNERFUNCTION_ZEIGER_390 \
        :KDAUFTRAGNR,\
        :PARTNERFUNCTION,\
        :SAPKUNNR
#define KDAUFTRAGPARTNERFUNCTION_UPDATE_390 \
        KDAUFTRAGNR=:KDAUFTRAGNR,\
        PARTNERFUNCTION=:PARTNERFUNCTION,\
        SAPKUNNR=:SAPKUNNR
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of KDAUFTRAGPARTNERFUNCTION ********************************/

#ifndef TRANSCLASS
typedef struct N_KDAUFTRAGPARTNERFUNCTION {
    long KDAUFTRAGNR;
    char PARTNERFUNCTION[3];
    char SAPKUNNR[11];
} kdauftragpartnerfunctionS;
#else /* TRANSCLASS */
typedef struct N_KDAUFTRAGPARTNERFUNCTION {
    long KDAUFTRAGNR;
    char PARTNERFUNCTION[3];
    char SAPKUNNR[11];

    bool operator == (const N_KDAUFTRAGPARTNERFUNCTION& right) const {
        return (
            KDAUFTRAGNR == right.KDAUFTRAGNR &&
            !strcmp(PARTNERFUNCTION, right.PARTNERFUNCTION) &&
            !strcmp(SAPKUNNR, right.SAPKUNNR)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        KDAUFTRAGNR = 0;
        strcpy(PARTNERFUNCTION, " " );
        strcpy(SAPKUNNR, " " );
#endif
    }
} kdauftragpartnerfunctionS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of KDAUFTRAGPARTNERFUNCTION **************************/

struct S_KDAUFTRAGPARTNERFUNCTION {
    char KDAUFTRAGNR[11];
    char PARTNERFUNCTION[2 + 1];
    char SAPKUNNR[10 + 1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of KDAUFTRAGPARTNERFUNCTION *********/

struct O_KDAUFTRAGPARTNERFUNCTION {
    char KDAUFTRAGNR[11];
    char PARTNERFUNCTION[2];
    char SAPKUNNR[10];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of KDAUFTRAGPARTNERFUNCTION ********************/

struct C_KDAUFTRAGPARTNERFUNCTION {
    long KDAUFTRAGNR;
    char PARTNERFUNCTION[3];
    char SAPKUNNR[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of KDAUFTRAGPARTNERFUNCTION ******************/

struct I_KDAUFTRAGPARTNERFUNCTION {
    short KDAUFTRAGNR;
    short PARTNERFUNCTION;
    short SAPKUNNR;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of KDAUFTRAGPARTNERFUNCTION ****************************/

#if defined (BUF_DESC)
static struct buf_desc KDAUFTRAGPARTNERFUNCTION_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 10, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc KDAUFTRAGPARTNERFUNCTION_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 10, 0 },
};
#endif

/* description for datatypes of KDAUFTRAGPARTNERFUNCTION **********************/

 #define KDAUFTRAGPARTNERFUNCTION_S390 \
         long KDAUFTRAGNR; \
         char PARTNERFUNCTION[3]; \
         char SAPKUNNR[11]; \



/* Copy-Function Struct to single Data KDAUFTRAGPARTNERFUNCTION ***************/

 #define KDAUFTRAGPARTNERFUNCTION_S390_COPY_TO_SINGLE(_x_) \
         KDAUFTRAGNR=_x_->KDAUFTRAGNR;\
          strcpy(PARTNERFUNCTION,_x_->PARTNERFUNCTION);\
          strcpy(SAPKUNNR,_x_->SAPKUNNR);\

 #define KDAUFTRAGPARTNERFUNCTION_S390_COPY_TO_STRUCT(_x_) \
          _x_->KDAUFTRAGNR=KDAUFTRAGNR;\
          strcpy(_x_->PARTNERFUNCTION,PARTNERFUNCTION);\
          strcpy(_x_->SAPKUNNR,SAPKUNNR);\



/* FunctionNumber-Define of kdauftragpartnerfunction **************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of kdauftragpartnerfunction **********************/


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

class CKDAUFTRAGPARTNERFUNCTION : public ppDadeVirtual {
public:
    kdauftragpartnerfunctionS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<kdauftragpartnerfunctionS> lst; // class list

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
                     vector< kdauftragpartnerfunctionS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     kdauftragpartnerfunctionS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< kdauftragpartnerfunctionS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<kdauftragpartnerfunctionS>::iterator
                 beginList() { return lst.begin(); }
    vector<kdauftragpartnerfunctionS>::iterator
                 endList  () { return lst.end  (); }

    long         GetKdauftragnr() const { return s.KDAUFTRAGNR; }
    const char*  GetPartnerfunction(ppString & t) const { t = s.PARTNERFUNCTION; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetSapkunnr(ppString & t) const { t = s.SAPKUNNR; t.erasespace(ppString::END); return t.c_str(); }

    const kdauftragpartnerfunctionS &
                 GetStruct() const { return s; }
    void         SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
    void         SetPartnerfunction(const ppString & t) { ppGStrCopy(s.PARTNERFUNCTION, t.c_str(), L_KDAUFTRAGPARTNERFUNCTION_PARTNERFUNCTION); }
    void         SetSapkunnr(const ppString & t) { ppGStrCopy(s.SAPKUNNR, t.c_str(), L_KDAUFTRAGPARTNERFUNCTION_SAPKUNNR); }

    void         SetStruct(const kdauftragpartnerfunctionS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CKDAUFTRAGPARTNERFUNCTION() {
        ::buf_default((void *)&s, KDAUFTRAGPARTNERFUNCTION_BES, KDAUFTRAGPARTNERFUNCTION_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CKDAUFTRAGPARTNERFUNCTION() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, KDAUFTRAGPARTNERFUNCTION_BES, KDAUFTRAGPARTNERFUNCTION_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, KDAUFTRAGPARTNERFUNCTION_BES, (int)KDAUFTRAGPARTNERFUNCTION_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, KDAUFTRAGPARTNERFUNCTION_BES, (int)KDAUFTRAGPARTNERFUNCTION_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_KDAUFTRAGPARTNERFUNCTION & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.PARTNERFUNCTION);
        ppGStripLast(d.SAPKUNNR);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, KDAUFTRAGPARTNERFUNCTION_BES, (int)KDAUFTRAGPARTNERFUNCTION_ANZ, error_msg);
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
/* CreateSqlStatement of KDAUFTRAGPARTNERFUNCTION *****************************/

 #define KDAUFTRAGPARTNERFUNCTION_CREATE(x) EXEC SQL create table x (\
         KDAUFTRAGNR integer default 0 not null,\
         PARTNERFUNCTION char(2) default " " not null,\
         SAPKUNNR char(10) default " " not null) in phosix extent size 784 next size 80 lock mode row;



/* CreateIndexStatement of KDAUFTRAGPARTNERFUNCTION ***************************/

 #define KDAUFTRAGPARTNERFUNCTION_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_kdauftragpartnerfunction_1 on _X_(\
              kdauftragnr,\
              partnerfunction ) in phosix;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of KDAUFTRAGPARTNERFUNCTION ***************************/

 #define KDAUFTRAGPARTNERFUNCTION_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_kdauftragpartnerfunction_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
