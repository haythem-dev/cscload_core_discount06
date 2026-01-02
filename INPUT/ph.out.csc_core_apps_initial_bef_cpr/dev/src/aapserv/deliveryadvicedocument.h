#ifndef __PP_DELIVERYADVICEDOCUMENT_H_
#define __PP_DELIVERYADVICEDOCUMENT_H_

/******************************************************************************/
/**/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of DELIVERYADVICEDOCUMENT ************************************/

#define L_DELIVERYADVICEDOCUMENT_BRANCHNO 6
#define L_DELIVERYADVICEDOCUMENT_CUSTOMERNO 11
#define L_DELIVERYADVICEDOCUMENT_DELIVERYADVICEDATE 11
#define L_DELIVERYADVICEDOCUMENT_DELIVERYADVICENO 10
#define L_DELIVERYADVICEDOCUMENT_DOCUMENTLINK 254
#define L_DELIVERYADVICEDOCUMENT_DOCUMENTTYPE 6

/* Length/Count-Define of DELIVERYADVICEDOCUMENT ******************************/

#define LS_DELIVERYADVICEDOCUMENT_BRANCHNO 5 + 1
#define LS_DELIVERYADVICEDOCUMENT_CUSTOMERNO 10 + 1
#define LS_DELIVERYADVICEDOCUMENT_DELIVERYADVICEDATE 10 + 1
#define LS_DELIVERYADVICEDOCUMENT_DELIVERYADVICENO 10 + 1
#define LS_DELIVERYADVICEDOCUMENT_DOCUMENTLINK 254 + 1
#define LS_DELIVERYADVICEDOCUMENT_DOCUMENTTYPE 5 + 1

#define DELIVERYADVICEDOCUMENTBRANCHNO 0
#define DELIVERYADVICEDOCUMENTCUSTOMERNO 1
#define DELIVERYADVICEDOCUMENTDELIVERYADVICEDATE 2
#define DELIVERYADVICEDOCUMENTDELIVERYADVICENO 3
#define DELIVERYADVICEDOCUMENTDOCUMENTLINK 4
#define DELIVERYADVICEDOCUMENTDOCUMENTTYPE 5

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define DELIVERYADVICEDOCUMENT_H
#define DELIVERYADVICEDOCUMENT_ANZ ( sizeof(DELIVERYADVICEDOCUMENT_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of DELIVERYADVICEDOCUMENT ****************************************/

#define DELIVERYADVICEDOCUMENT_LISTE \
        DADUMMY.BRANCHNO,\
        DADUMMY.CUSTOMERNO,\
        DADUMMY.DELIVERYADVICEDATE,\
        DADUMMY.DELIVERYADVICENO,\
        DADUMMY.DOCUMENTLINK,\
        DADUMMY.DOCUMENTTYPE
#define DELIVERYADVICEDOCUMENT_LISTE_390 \
        BRANCHNO,\
        CUSTOMERNO,\
        DELIVERYADVICEDATE,\
        DELIVERYADVICENO,\
        DOCUMENTLINK,\
        DOCUMENTTYPE
#define DELIVERYADVICEDOCUMENT_PLISTE \
        "DADUMMY.BRANCHNO,"\
        "DADUMMY.CUSTOMERNO,"\
        "DADUMMY.DELIVERYADVICEDATE,"\
        "DADUMMY.DELIVERYADVICENO,"\
        "DADUMMY.DOCUMENTLINK,"\
        "DADUMMY.DOCUMENTTYPE"
#define DELIVERYADVICEDOCUMENT_PELISTE \
        "BRANCHNO,"\
        "CUSTOMERNO,"\
        "DELIVERYADVICEDATE,"\
        "DELIVERYADVICENO,"\
        "DOCUMENTLINK,"\
        "DOCUMENTTYPE"
#define DELIVERYADVICEDOCUMENT_UPDLISTE \
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "DELIVERYADVICEDATE=?,"\
        "DELIVERYADVICENO=?,"\
        "DOCUMENTLINK=?,"\
        "DOCUMENTTYPE=?"
/* SqlMacros-Define of DELIVERYADVICEDOCUMENT *********************************/

#define DELIVERYADVICEDOCUMENT_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->DELIVERYADVICEDATE,\
        :x->DELIVERYADVICENO,\
        :x->DOCUMENTLINK,\
        :x->DOCUMENTTYPE
#define DELIVERYADVICEDOCUMENT_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->DELIVERYADVICEDATE,\
        :x->DELIVERYADVICENO,\
        :x->DOCUMENTLINK,\
        :x->DOCUMENTTYPE
#define DELIVERYADVICEDOCUMENT_UPDATE(x) \
        DADUMMY.BRANCHNO=:x->BRANCHNO,\
        DADUMMY.CUSTOMERNO=:x->CUSTOMERNO,\
        DADUMMY.DELIVERYADVICEDATE=:x->DELIVERYADVICEDATE,\
        DADUMMY.DELIVERYADVICENO=:x->DELIVERYADVICENO,\
        DADUMMY.DOCUMENTLINK=:x->DOCUMENTLINK,\
        DADUMMY.DOCUMENTTYPE=:x->DOCUMENTTYPE
/* SqlMacros390-Define of DELIVERYADVICEDOCUMENT ******************************/

#define DELIVERYADVICEDOCUMENT_ZEIGER_390 \
        :BRANCHNO,\
        :CUSTOMERNO,\
        :DELIVERYADVICEDATE,\
        :DELIVERYADVICENO,\
        :DOCUMENTLINK,\
        :DOCUMENTTYPE
#define DELIVERYADVICEDOCUMENT_UPDATE_390 \
        BRANCHNO=:BRANCHNO,\
        CUSTOMERNO=:CUSTOMERNO,\
        DELIVERYADVICEDATE=:DELIVERYADVICEDATE,\
        DELIVERYADVICENO=:DELIVERYADVICENO,\
        DOCUMENTLINK=:DOCUMENTLINK,\
        DOCUMENTTYPE=:DOCUMENTTYPE
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of DELIVERYADVICEDOCUMENT **********************************/

#ifndef TRANSCLASS
typedef struct N_DELIVERYADVICEDOCUMENT {
    short BRANCHNO;
    long CUSTOMERNO;
    long DELIVERYADVICEDATE;
    char DELIVERYADVICENO[11];
    char DOCUMENTLINK[255];
    short DOCUMENTTYPE;
} deliveryadvicedocumentS;
#else /* TRANSCLASS */
typedef struct N_DELIVERYADVICEDOCUMENT {
    short BRANCHNO;
    long CUSTOMERNO;
    long DELIVERYADVICEDATE;
    char DELIVERYADVICENO[11];
    char DOCUMENTLINK[255];
    short DOCUMENTTYPE;

    bool operator == (const N_DELIVERYADVICEDOCUMENT& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            CUSTOMERNO == right.CUSTOMERNO &&
            DELIVERYADVICEDATE == right.DELIVERYADVICEDATE &&
            !strcmp(DELIVERYADVICENO, right.DELIVERYADVICENO) &&
            !strcmp(DOCUMENTLINK, right.DOCUMENTLINK) &&
            DOCUMENTTYPE == right.DOCUMENTTYPE
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
        strcpy(DOCUMENTLINK, " " );
        DOCUMENTTYPE = 0;
#endif
    }
} deliveryadvicedocumentS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of DELIVERYADVICEDOCUMENT ****************************/

struct S_DELIVERYADVICEDOCUMENT {
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char DELIVERYADVICEDATE[11];
    char DELIVERYADVICENO[10 + 1];
    char DOCUMENTLINK[254 + 1];
    char DOCUMENTTYPE[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of DELIVERYADVICEDOCUMENT ***********/

struct O_DELIVERYADVICEDOCUMENT {
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char DELIVERYADVICEDATE[11];
    char DELIVERYADVICENO[10];
    char DOCUMENTLINK[254];
    char DOCUMENTTYPE[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of DELIVERYADVICEDOCUMENT **********************/

struct C_DELIVERYADVICEDOCUMENT {
    short BRANCHNO;
    long CUSTOMERNO;
    long DELIVERYADVICEDATE;
    char DELIVERYADVICENO[11];
    char DOCUMENTLINK[255];
    short DOCUMENTTYPE;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of DELIVERYADVICEDOCUMENT ********************/

struct I_DELIVERYADVICEDOCUMENT {
    short BRANCHNO;
    short CUSTOMERNO;
    short DELIVERYADVICEDATE;
    short DELIVERYADVICENO;
    short DOCUMENTLINK;
    short DOCUMENTTYPE;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of DELIVERYADVICEDOCUMENT ******************************/

#if defined (BUF_DESC)
static struct buf_desc DELIVERYADVICEDOCUMENT_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 10, 0 },
   { TYP_C, 254, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc DELIVERYADVICEDOCUMENT_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 10, 0 },
   { TYP_C, 254, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* description for datatypes of DELIVERYADVICEDOCUMENT ************************/

 #define DELIVERYADVICEDOCUMENT_S390 \
         short BRANCHNO; \
         long CUSTOMERNO; \
         long DELIVERYADVICEDATE; \
         char DELIVERYADVICENO[11]; \
         char DOCUMENTLINK[255]; \
         short DOCUMENTTYPE; \



/* Copy-Function Struct to single Data DELIVERYADVICEDOCUMENT *****************/

 #define DELIVERYADVICEDOCUMENT_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
         DELIVERYADVICEDATE=_x_->DELIVERYADVICEDATE;\
          strcpy(DELIVERYADVICENO,_x_->DELIVERYADVICENO);\
          strcpy(DOCUMENTLINK,_x_->DOCUMENTLINK);\
         DOCUMENTTYPE=_x_->DOCUMENTTYPE;\

 #define DELIVERYADVICEDOCUMENT_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->DELIVERYADVICEDATE=DELIVERYADVICEDATE;\
          strcpy(_x_->DELIVERYADVICENO,DELIVERYADVICENO);\
          strcpy(_x_->DOCUMENTLINK,DOCUMENTLINK);\
          _x_->DOCUMENTTYPE=DOCUMENTTYPE;\



/* FunctionNumber-Define of Deliveryadvicedocument ****************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of Deliveryadvicedocument ************************/


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

class CDELIVERYADVICEDOCUMENT : public ppDadeVirtual {
public:
    deliveryadvicedocumentS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<deliveryadvicedocumentS> lst; // class list

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
                     vector< deliveryadvicedocumentS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     deliveryadvicedocumentS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< deliveryadvicedocumentS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<deliveryadvicedocumentS>::iterator
                 beginList() { return lst.begin(); }
    vector<deliveryadvicedocumentS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    long         GetDeliveryadvicedate() const { return s.DELIVERYADVICEDATE; }
    const char*  GetDeliveryadviceno(ppString & t) const { t = s.DELIVERYADVICENO; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetDocumentlink(ppString & t) const { t = s.DOCUMENTLINK; t.erasespace(ppString::END); return t.c_str(); }
    short        GetDocumenttype() const { return s.DOCUMENTTYPE; }

    const deliveryadvicedocumentS &
                 GetStruct() const { return s; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetDeliveryadvicedate(long t) { s.DELIVERYADVICEDATE = t; }
    void         SetDeliveryadviceno(const ppString & t) { ppGStrCopy(s.DELIVERYADVICENO, t.c_str(), L_DELIVERYADVICEDOCUMENT_DELIVERYADVICENO); }
    void         SetDocumentlink(const ppString & t) { ppGStrCopy(s.DOCUMENTLINK, t.c_str(), L_DELIVERYADVICEDOCUMENT_DOCUMENTLINK); }
    void         SetDocumenttype(short t) { s.DOCUMENTTYPE = t; }

    void         SetStruct(const deliveryadvicedocumentS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CDELIVERYADVICEDOCUMENT() {
        ::buf_default((void *)&s, DELIVERYADVICEDOCUMENT_BES, DELIVERYADVICEDOCUMENT_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CDELIVERYADVICEDOCUMENT() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, DELIVERYADVICEDOCUMENT_BES, DELIVERYADVICEDOCUMENT_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, DELIVERYADVICEDOCUMENT_BES, (int)DELIVERYADVICEDOCUMENT_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, DELIVERYADVICEDOCUMENT_BES, (int)DELIVERYADVICEDOCUMENT_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_DELIVERYADVICEDOCUMENT & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.DELIVERYADVICENO);
        ppGStripLast(d.DOCUMENTLINK);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, DELIVERYADVICEDOCUMENT_BES, (int)DELIVERYADVICEDOCUMENT_ANZ, error_msg);
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
/* CreateSqlStatement of DELIVERYADVICEDOCUMENT *******************************/

 #define DELIVERYADVICEDOCUMENT_CREATE(x) EXEC SQL create table x (\
         BRANCHNO smallint default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         DELIVERYADVICEDATE integer default 0 not null,\
         DELIVERYADVICENO varchar(10,0) default " " not null,\
         DOCUMENTLINK varchar(254,0) default " " not null,\
         DOCUMENTTYPE smallint default 0 not null) extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of DELIVERYADVICEDOCUMENT *****************************/

 #define DELIVERYADVICEDOCUMENT_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
/* DeleteIndexStatement of DELIVERYADVICEDOCUMENT *****************************/

 #define DELIVERYADVICEDOCUMENT_DELETE_INDEX(_X_)\
              _X_ = 0;\


#endif   // GUARD
