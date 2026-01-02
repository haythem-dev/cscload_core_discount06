#ifndef __PP_ARTICLEINQUIRYBULK_H_
#define __PP_ARTICLEINQUIRYBULK_H_

/******************************************************************************/
/* c:\marathon\dade\ArticleInquiryBulk ****************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* Length-Define of ARTICLEINQUIRYBULK ****************************************/

#define L_ARTICLEINQUIRYBULK_BRANCHNO 6
#define L_ARTICLEINQUIRYBULK_CUSTOMERNO 11
#define L_ARTICLEINQUIRYBULK_INFOBLOCK 4001

/* Length/Count-Define of ARTICLEINQUIRYBULK **********************************/

#define LS_ARTICLEINQUIRYBULK_BRANCHNO 5 + 1
#define LS_ARTICLEINQUIRYBULK_CUSTOMERNO 10 + 1
#define LS_ARTICLEINQUIRYBULK_INFOBLOCK 4001 + 1

#define ARTICLEINQUIRYBULKBRANCHNO 0
#define ARTICLEINQUIRYBULKCUSTOMERNO 1
#define ARTICLEINQUIRYBULKINFOBLOCK 2

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define ARTICLEINQUIRYBULK_H
#define ARTICLEINQUIRYBULK_ANZ ( sizeof(ARTICLEINQUIRYBULK_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ARTICLEINQUIRYBULK ********************************************/

#define ARTICLEINQUIRYBULK_LISTE \
        KSCDUMMY.BRANCHNO,\
        KSCDUMMY.CUSTOMERNO,\
        KSCDUMMY.INFOBLOCK
#define ARTICLEINQUIRYBULK_LISTE_390 \
        BRANCHNO,\
        CUSTOMERNO,\
        INFOBLOCK
#define ARTICLEINQUIRYBULK_PLISTE \
        "KSCDUMMY.BRANCHNO,"\
        "KSCDUMMY.CUSTOMERNO,"\
        "KSCDUMMY.INFOBLOCK"
#define ARTICLEINQUIRYBULK_PELISTE \
        "BRANCHNO,"\
        "CUSTOMERNO,"\
        "INFOBLOCK"
#define ARTICLEINQUIRYBULK_UPDLISTE \
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "INFOBLOCK=?"
/* SqlMacros-Define of ARTICLEINQUIRYBULK *************************************/

#define ARTICLEINQUIRYBULK_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->INFOBLOCK
#define ARTICLEINQUIRYBULK_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->INFOBLOCK
#define ARTICLEINQUIRYBULK_UPDATE(x) \
        KSCDUMMY.BRANCHNO=:x->BRANCHNO,\
        KSCDUMMY.CUSTOMERNO=:x->CUSTOMERNO,\
        KSCDUMMY.INFOBLOCK=:x->INFOBLOCK
/* SqlMacros390-Define of ARTICLEINQUIRYBULK **********************************/

#define ARTICLEINQUIRYBULK_ZEIGER_390 \
        :BRANCHNO,\
        :CUSTOMERNO,\
        :INFOBLOCK
#define ARTICLEINQUIRYBULK_UPDATE_390 \
        BRANCHNO=:BRANCHNO,\
        CUSTOMERNO=:CUSTOMERNO,\
        INFOBLOCK=:INFOBLOCK
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of ARTICLEINQUIRYBULK **************************************/

#ifndef TRANSCLASS
typedef struct N_ARTICLEINQUIRYBULK {
    short BRANCHNO;
    long CUSTOMERNO;
    char INFOBLOCK[4002];
} articleinquirybulkS;
#else /* TRANSCLASS */
typedef struct N_ARTICLEINQUIRYBULK {
    short BRANCHNO;
    long CUSTOMERNO;
    char INFOBLOCK[4002];

    bool operator == (const N_ARTICLEINQUIRYBULK& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            CUSTOMERNO == right.CUSTOMERNO &&
            !strcmp(INFOBLOCK, right.INFOBLOCK)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        CUSTOMERNO = 0;
        strcpy(INFOBLOCK, " " );
#endif
    }
} articleinquirybulkS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ARTICLEINQUIRYBULK ********************************/

struct S_ARTICLEINQUIRYBULK {
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char INFOBLOCK[4001 + 1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ARTICLEINQUIRYBULK ***************/

struct O_ARTICLEINQUIRYBULK {
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char INFOBLOCK[4001];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ARTICLEINQUIRYBULK **************************/

struct C_ARTICLEINQUIRYBULK {
    short BRANCHNO;
    long CUSTOMERNO;
    char INFOBLOCK[4002];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ARTICLEINQUIRYBULK ************************/

struct I_ARTICLEINQUIRYBULK {
    short BRANCHNO;
    short CUSTOMERNO;
    short INFOBLOCK;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ARTICLEINQUIRYBULK **********************************/

#if defined (BUF_DESC)
static struct buf_desc ARTICLEINQUIRYBULK_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 4001, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc ARTICLEINQUIRYBULK_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 4001, 0 },
};
#endif

/* description for datatypes of ARTICLEINQUIRYBULK ****************************/

 #define ARTICLEINQUIRYBULK_S390 \
         short BRANCHNO; \
         long CUSTOMERNO; \
         char INFOBLOCK[4002]; \



/* Copy-Function Struct to single Data ARTICLEINQUIRYBULK *********************/

 #define ARTICLEINQUIRYBULK_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
          strcpy(INFOBLOCK,_x_->INFOBLOCK);\

 #define ARTICLEINQUIRYBULK_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          strcpy(_x_->INFOBLOCK,INFOBLOCK);\



/* FunctionNumber-Define of ArticleInquiryBulk ********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of ArticleInquiryBulk ****************************/


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

class CARTICLEINQUIRYBULK : public ppDadeVirtual {
public:
    articleinquirybulkS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<articleinquirybulkS> lst; // class list

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
                     vector< articleinquirybulkS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     articleinquirybulkS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< articleinquirybulkS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<articleinquirybulkS>::iterator
                 beginList() { return lst.begin(); }
    vector<articleinquirybulkS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    const char*  GetInfoblock(ppString & t) const { t = s.INFOBLOCK; t.erasespace(ppString::END); return t.c_str(); }

    const articleinquirybulkS &
                 GetStruct() const { return s; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetInfoblock(const ppString & t) { ppGStrCopy(s.INFOBLOCK, t.c_str(), L_ARTICLEINQUIRYBULK_INFOBLOCK); }

    void         SetStruct(const articleinquirybulkS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CARTICLEINQUIRYBULK() {
        ::buf_default((void *)&s, ARTICLEINQUIRYBULK_BES, ARTICLEINQUIRYBULK_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CARTICLEINQUIRYBULK() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, ARTICLEINQUIRYBULK_BES, ARTICLEINQUIRYBULK_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, ARTICLEINQUIRYBULK_BES, (int)ARTICLEINQUIRYBULK_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, ARTICLEINQUIRYBULK_BES, (int)ARTICLEINQUIRYBULK_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_ARTICLEINQUIRYBULK & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.INFOBLOCK);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, ARTICLEINQUIRYBULK_BES, (int)ARTICLEINQUIRYBULK_ANZ, error_msg);
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
/* CreateSqlStatement of ARTICLEINQUIRYBULK ***********************************/

 #define ARTICLEINQUIRYBULK_CREATE(x) EXEC SQL create table x (\
         BRANCHNO smallint default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         INFOBLOCK char(4001) default " " not null) extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of ARTICLEINQUIRYBULK *********************************/

 #define ARTICLEINQUIRYBULK_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
/* DeleteIndexStatement of ARTICLEINQUIRYBULK *********************************/

 #define ARTICLEINQUIRYBULK_DELETE_INDEX(_X_)\
              _X_ = 0;\


#endif   // GUARD
