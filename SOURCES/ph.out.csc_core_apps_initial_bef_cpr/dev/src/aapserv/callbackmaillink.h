#ifndef __PP_CALLBACKMAILLINK_H_
#define __PP_CALLBACKMAILLINK_H_

/******************************************************************************/
/* C:\Marathon\csc_core_applications\trunk\dev\src\aapserv\CallbackMailLink ***/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of CALLBACKMAILLINK ******************************************/

#define L_CALLBACKMAILLINK_BRANCHNO 6
#define L_CALLBACKMAILLINK_ENABLED 6
#define L_CALLBACKMAILLINK_WEBSITEBASEURL 254

/* Length/Count-Define of CALLBACKMAILLINK ************************************/

#define LS_CALLBACKMAILLINK_BRANCHNO 5 + 1
#define LS_CALLBACKMAILLINK_ENABLED 5 + 1
#define LS_CALLBACKMAILLINK_WEBSITEBASEURL 254 + 1

#define CALLBACKMAILLINKBRANCHNO 0
#define CALLBACKMAILLINKENABLED 1
#define CALLBACKMAILLINKWEBSITEBASEURL 2

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define CALLBACKMAILLINK_H
#define CALLBACKMAILLINK_ANZ ( sizeof(CALLBACKMAILLINK_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of CALLBACKMAILLINK **********************************************/

#define CALLBACKMAILLINK_LISTE \
        CALLBACKDIVISION.BRANCHNO,\
        AADUMMY.ENABLED,\
        AADUMMY.WEBSITEBASEURL
#define CALLBACKMAILLINK_LISTE_390 \
        BRANCHNO,\
        ENABLED,\
        WEBSITEBASEURL
#define CALLBACKMAILLINK_PLISTE \
        "CALLBACKDIVISION.BRANCHNO,"\
        "AADUMMY.ENABLED,"\
        "AADUMMY.WEBSITEBASEURL"
#define CALLBACKMAILLINK_PELISTE \
        "BRANCHNO,"\
        "ENABLED,"\
        "WEBSITEBASEURL"
#define CALLBACKMAILLINK_UPDLISTE \
        "BRANCHNO=?,"\
        "ENABLED=?,"\
        "WEBSITEBASEURL=?"
/* SqlMacros-Define of CALLBACKMAILLINK ***************************************/

#define CALLBACKMAILLINK_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->ENABLED,\
        :x->WEBSITEBASEURL
#define CALLBACKMAILLINK_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->ENABLED,\
        :x->WEBSITEBASEURL
#define CALLBACKMAILLINK_UPDATE(x) \
        CALLBACKDIVISION.BRANCHNO=:x->BRANCHNO,\
        AADUMMY.ENABLED=:x->ENABLED,\
        AADUMMY.WEBSITEBASEURL=:x->WEBSITEBASEURL
/* SqlMacros390-Define of CALLBACKMAILLINK ************************************/

#define CALLBACKMAILLINK_ZEIGER_390 \
        :BRANCHNO,\
        :ENABLED,\
        :WEBSITEBASEURL
#define CALLBACKMAILLINK_UPDATE_390 \
        BRANCHNO=:BRANCHNO,\
        ENABLED=:ENABLED,\
        WEBSITEBASEURL=:WEBSITEBASEURL
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of CALLBACKMAILLINK ****************************************/

#ifndef TRANSCLASS
typedef struct N_CALLBACKMAILLINK {
    short BRANCHNO;
    short ENABLED;
    char WEBSITEBASEURL[255];
} callbackmaillinkS;
#else /* TRANSCLASS */
typedef struct N_CALLBACKMAILLINK {
    short BRANCHNO;
    short ENABLED;
    char WEBSITEBASEURL[255];

    bool operator == (const N_CALLBACKMAILLINK& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            ENABLED == right.ENABLED &&
            !strcmp(WEBSITEBASEURL, right.WEBSITEBASEURL)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        ENABLED = 0;
        strcpy(WEBSITEBASEURL, " " );
#endif
    }
} callbackmaillinkS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of CALLBACKMAILLINK **********************************/

struct S_CALLBACKMAILLINK {
    char BRANCHNO[7];
    char ENABLED[7];
    char WEBSITEBASEURL[254 + 1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of CALLBACKMAILLINK *****************/

struct O_CALLBACKMAILLINK {
    char BRANCHNO[7];
    char ENABLED[7];
    char WEBSITEBASEURL[254];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of CALLBACKMAILLINK ****************************/

struct C_CALLBACKMAILLINK {
    short BRANCHNO;
    short ENABLED;
    char WEBSITEBASEURL[255];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of CALLBACKMAILLINK **************************/

struct I_CALLBACKMAILLINK {
    short BRANCHNO;
    short ENABLED;
    short WEBSITEBASEURL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CALLBACKMAILLINK ************************************/

#if defined (BUF_DESC)
static struct buf_desc CALLBACKMAILLINK_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 254, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CALLBACKMAILLINK_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 254, 0 },
};
#endif

/* description for datatypes of CALLBACKMAILLINK ******************************/

 #define CALLBACKMAILLINK_S390 \
         short BRANCHNO; \
         short ENABLED; \
         char WEBSITEBASEURL[255]; \



/* Copy-Function Struct to single Data CALLBACKMAILLINK ***********************/

 #define CALLBACKMAILLINK_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         ENABLED=_x_->ENABLED;\
          strcpy(WEBSITEBASEURL,_x_->WEBSITEBASEURL);\

 #define CALLBACKMAILLINK_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->ENABLED=ENABLED;\
          strcpy(_x_->WEBSITEBASEURL,WEBSITEBASEURL);\



/* FunctionNumber-Define of CallbackMailLink **********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of CallbackMailLink ******************************/


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

class CCALLBACKMAILLINK : public ppDadeVirtual {
public:
    callbackmaillinkS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<callbackmaillinkS> lst; // class list

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
                     vector< callbackmaillinkS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     callbackmaillinkS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< callbackmaillinkS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<callbackmaillinkS>::iterator
                 beginList() { return lst.begin(); }
    vector<callbackmaillinkS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    short        GetEnabled() const { return s.ENABLED; }
    const char*  GetWebsitebaseurl(ppString & t) const { t = s.WEBSITEBASEURL; t.erasespace(ppString::END); return t.c_str(); }

    const callbackmaillinkS &
                 GetStruct() const { return s; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetEnabled(short t) { s.ENABLED = t; }
    void         SetWebsitebaseurl(const ppString & t) { ppGStrCopy(s.WEBSITEBASEURL, t.c_str(), L_CALLBACKMAILLINK_WEBSITEBASEURL); }

    void         SetStruct(const callbackmaillinkS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCALLBACKMAILLINK() {
        ::buf_default((void *)&s, CALLBACKMAILLINK_BES, CALLBACKMAILLINK_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCALLBACKMAILLINK() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CALLBACKMAILLINK_BES, CALLBACKMAILLINK_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, CALLBACKMAILLINK_BES, (int)CALLBACKMAILLINK_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, CALLBACKMAILLINK_BES, (int)CALLBACKMAILLINK_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_CALLBACKMAILLINK & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.WEBSITEBASEURL);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CALLBACKMAILLINK_BES, (int)CALLBACKMAILLINK_ANZ, error_msg);
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
/* CreateSqlStatement of CALLBACKMAILLINK *************************************/

 #define CALLBACKMAILLINK_CREATE(x) EXEC SQL create table x (\
         BRANCHNO smallint default 0 not null,\
         ENABLED smallint default 0 not null,\
         WEBSITEBASEURL varchar(254,0) default " " not null) extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of CALLBACKMAILLINK ***********************************/

 #define CALLBACKMAILLINK_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_callbackdivision_1 on _X_(\
              BranchNo,\
              CallbackDivisionNo );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of CALLBACKMAILLINK ***********************************/

 #define CALLBACKMAILLINK_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_callbackdivision_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
