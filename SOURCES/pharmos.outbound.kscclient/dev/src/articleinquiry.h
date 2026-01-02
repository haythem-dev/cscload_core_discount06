#ifndef __PP_ARTICLEINQUIRY_H_
#define __PP_ARTICLEINQUIRY_H_

/******************************************************************************/
/* d:\var\tmp\2\ArticleInquiry ************************************************/
/* produced by DADE 6.21.0 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <pplib/bufkon.h>

/* Length-Define of ARTICLEINQUIRY ********************************************/

#define L_ARTICLEINQUIRY_INFOBLOCK 4001

/* Length/Count-Define of ARTICLEINQUIRY **************************************/

#define LS_ARTICLEINQUIRY_INFOBLOCK 4001 + 1

#define ARTICLEINQUIRYINFOBLOCK 0

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define ARTICLEINQUIRY_H
#define ARTICLEINQUIRY_ANZ ( sizeof(ARTICLEINQUIRY_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ARTICLEINQUIRY ************************************************/

#define ARTICLEINQUIRY_LISTE \
        KSCDUMMY.INFOBLOCK
#define ARTICLEINQUIRY_LISTE_390 \
        INFOBLOCK
#define ARTICLEINQUIRY_PLISTE \
        "KSCDUMMY.INFOBLOCK"
#define ARTICLEINQUIRY_PELISTE \
        "INFOBLOCK"
#define ARTICLEINQUIRY_UPDLISTE \
        "INFOBLOCK=?"
/* SqlMacros-Define of ARTICLEINQUIRY *****************************************/

#define ARTICLEINQUIRY_ZEIGER(x) \
        :x->INFOBLOCK
#define ARTICLEINQUIRY_ZEIGERSEL(x) \
        :x->INFOBLOCK
#define ARTICLEINQUIRY_UPDATE(x) \
        KSCDUMMY.INFOBLOCK=:x->INFOBLOCK
/* SqlMacros390-Define of ARTICLEINQUIRY **************************************/

#define ARTICLEINQUIRY_ZEIGER_390 \
        :INFOBLOCK
#define ARTICLEINQUIRY_UPDATE_390 \
        INFOBLOCK=:INFOBLOCK
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of ARTICLEINQUIRY ******************************************/

#ifndef TRANSCLASS
typedef struct N_ARTICLEINQUIRY {
    char INFOBLOCK[4002];
} articleinquiryS;
#else /* TRANSCLASS */
typedef struct N_ARTICLEINQUIRY {
    char INFOBLOCK[4002];

    bool operator == (const N_ARTICLEINQUIRY& right) const {
        return (
            !strcmp(INFOBLOCK, right.INFOBLOCK)
        );
    }
    void clear() {
#ifdef _WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        strcpy(INFOBLOCK, " " );
#endif
    }
} articleinquiryS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ARTICLEINQUIRY ************************************/

struct S_ARTICLEINQUIRY {
    char INFOBLOCK[4001 + 1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ARTICLEINQUIRY *******************/

struct O_ARTICLEINQUIRY {
    char INFOBLOCK[4001];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ARTICLEINQUIRY ******************************/

struct C_ARTICLEINQUIRY {
    char INFOBLOCK[4002];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ARTICLEINQUIRY ****************************/

struct I_ARTICLEINQUIRY {
    short INFOBLOCK;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ARTICLEINQUIRY **************************************/

#if defined (BUF_DESC)
static struct buf_desc ARTICLEINQUIRY_BES [] = {
   { TYP_C, 4001, 0 },
};
/* avoid unused warning */
void * pUnusedARTICLEINQUIRY = ARTICLEINQUIRY_BES;
#elif defined (C_BUF_DESC)
static struct buf_desc ARTICLEINQUIRY_BES [] = {
   { TYP_C, 4001, 0 },
};
/* avoid unused warning */
void * pUnusedARTICLEINQUIRY = ARTICLEINQUIRY_BES;
#endif

/* description for datatypes of ARTICLEINQUIRY ********************************/

 #define ARTICLEINQUIRY_S390 \
         char INFOBLOCK[4002]; \



/* Copy-Function Struct to single Data ARTICLEINQUIRY *************************/

 #define ARTICLEINQUIRY_S390_COPY_TO_SINGLE(_x_) \
          strcpy(INFOBLOCK,_x_->INFOBLOCK);\

 #define ARTICLEINQUIRY_S390_COPY_TO_STRUCT(_x_) \
          strcpy(_x_->INFOBLOCK,INFOBLOCK);\



/* FunctionNumber-Define of ArticleInquiry ************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of ArticleInquiry ********************************/


#endif

/* C++ Class ******************************************************************/

#ifdef TRANSCLASS

#include<vector>
using namespace std;

/* ppunixc */
#include <pplib/sockclient.h>
#include <pplib/ppstring.h>
#include <pplib/ppgeneric.h>

/* must be implemented */
void FehlerBehandlung(int rc, char *error_msg);

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

class CARTICLEINQUIRY : public ppDadeVirtual {
public:
    articleinquiryS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<articleinquiryS> lst; // class list

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
                     vector< articleinquiryS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     articleinquiryS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< articleinquiryS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<articleinquiryS>::iterator
                 beginList() { return lst.begin(); }
    vector<articleinquiryS>::iterator
                 endList  () { return lst.end  (); }

    const char*  GetInfoblock(ppString & t) const { t = s.INFOBLOCK; t.erasespace(ppString::END); return t.c_str(); }

    const articleinquiryS &
                 GetStruct() const { return s; }
    void         SetInfoblock(const ppString & t) { ppGStrCopy(s.INFOBLOCK, t.c_str(), L_ARTICLEINQUIRY_INFOBLOCK); }

    void         SetStruct(const articleinquiryS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CARTICLEINQUIRY() {
        ::buf_default((void *)&s, ARTICLEINQUIRY_BES, ARTICLEINQUIRY_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CARTICLEINQUIRY() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, ARTICLEINQUIRY_BES, ARTICLEINQUIRY_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef _WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, ARTICLEINQUIRY_BES, ARTICLEINQUIRY_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, ARTICLEINQUIRY_BES, ARTICLEINQUIRY_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_ARTICLEINQUIRY & d) {
        d = d;
    #ifdef _WIN32
        ppGStripLast(d.INFOBLOCK);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, ARTICLEINQUIRY_BES, ARTICLEINQUIRY_ANZ, error_msg);
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
/* CreateSqlStatement of ARTICLEINQUIRY ***************************************/

 #define ARTICLEINQUIRY_CREATE(x) EXEC SQL create table x (\
         INFOBLOCK char(4001) default " " not null) extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of ARTICLEINQUIRY *************************************/

 #define ARTICLEINQUIRY_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
/* DeleteIndexStatement of ARTICLEINQUIRY *************************************/

 #define ARTICLEINQUIRY_DELETE_INDEX(_X_)\
              _X_ = 0;\


#endif   // GUARD
