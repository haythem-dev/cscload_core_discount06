#ifndef __PP_ORDERREMARKS_H_
#define __PP_ORDERREMARKS_H_

/******************************************************************************/
/* d:\orderremarks ************************************************************/
/* produced by DADE 6.21.4 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of ORDERREMARKS **********************************************/

#define L_ORDERREMARKS_CSCORDERNO 11
#define L_ORDERREMARKS_POSITIONNO 11
#define L_ORDERREMARKS_REMARKTYPE 6
#define L_ORDERREMARKS_TEXTNUMBER 6
#define L_ORDERREMARKS_REMARKTEXT 250

/* Length/Count-Define of ORDERREMARKS ****************************************/

#define LS_ORDERREMARKS_CSCORDERNO 10 + 1
#define LS_ORDERREMARKS_POSITIONNO 10 + 1
#define LS_ORDERREMARKS_REMARKTYPE 5 + 1
#define LS_ORDERREMARKS_TEXTNUMBER 5 + 1
#define LS_ORDERREMARKS_REMARKTEXT 250 + 1

#define ORDERREMARKSCSCORDERNO 0
#define ORDERREMARKSPOSITIONNO 1
#define ORDERREMARKSREMARKTYPE 2
#define ORDERREMARKSTEXTNUMBER 3
#define ORDERREMARKSREMARKTEXT 4

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define ORDERREMARKS_H
#define ORDERREMARKS_ANZ ( sizeof(ORDERREMARKS_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ORDERREMARKS **************************************************/

#define ORDERREMARKS_LISTE \
        ORDERREMARKS.CSCORDERNO,\
        ORDERREMARKS.POSITIONNO,\
        ORDERREMARKS.REMARKTYPE,\
        ORDERREMARKS.TEXTNUMBER,\
        ORDERREMARKS.REMARKTEXT
#define ORDERREMARKS_LISTE_390 \
        CSCORDERNO,\
        POSITIONNO,\
        REMARKTYPE,\
        TEXTNUMBER,\
        REMARKTEXT
#define ORDERREMARKS_PLISTE \
        "ORDERREMARKS.CSCORDERNO,"\
        "ORDERREMARKS.POSITIONNO,"\
        "ORDERREMARKS.REMARKTYPE,"\
        "ORDERREMARKS.TEXTNUMBER,"\
        "ORDERREMARKS.REMARKTEXT"
#define ORDERREMARKS_PELISTE \
        "CSCORDERNO,"\
        "POSITIONNO,"\
        "REMARKTYPE,"\
        "TEXTNUMBER,"\
        "REMARKTEXT"
#define ORDERREMARKS_UPDLISTE \
        "CSCORDERNO=?,"\
        "POSITIONNO=?,"\
        "REMARKTYPE=?,"\
        "TEXTNUMBER=?,"\
        "REMARKTEXT=?"
/* SqlMacros-Define of ORDERREMARKS *******************************************/

#define ORDERREMARKS_ZEIGER(x) \
        :x->CSCORDERNO,\
        :x->POSITIONNO,\
        :x->REMARKTYPE,\
        :x->TEXTNUMBER,\
        :x->REMARKTEXT
#define ORDERREMARKS_ZEIGERSEL(x) \
        :x->CSCORDERNO,\
        :x->POSITIONNO,\
        :x->REMARKTYPE,\
        :x->TEXTNUMBER,\
        :x->REMARKTEXT
#define ORDERREMARKS_UPDATE(x) \
        ORDERREMARKS.CSCORDERNO=:x->CSCORDERNO,\
        ORDERREMARKS.POSITIONNO=:x->POSITIONNO,\
        ORDERREMARKS.REMARKTYPE=:x->REMARKTYPE,\
        ORDERREMARKS.TEXTNUMBER=:x->TEXTNUMBER,\
        ORDERREMARKS.REMARKTEXT=:x->REMARKTEXT
/* SqlMacros390-Define of ORDERREMARKS ****************************************/

#define ORDERREMARKS_ZEIGER_390 \
        :CSCORDERNO,\
        :POSITIONNO,\
        :REMARKTYPE,\
        :TEXTNUMBER,\
        :REMARKTEXT
#define ORDERREMARKS_UPDATE_390 \
        CSCORDERNO=:CSCORDERNO,\
        POSITIONNO=:POSITIONNO,\
        REMARKTYPE=:REMARKTYPE,\
        TEXTNUMBER=:TEXTNUMBER,\
        REMARKTEXT=:REMARKTEXT
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of ORDERREMARKS ********************************************/

#ifndef TRANSCLASS
typedef struct N_ORDERREMARKS {
    long CSCORDERNO;
    long POSITIONNO;
    short REMARKTYPE;
    short TEXTNUMBER;
    char REMARKTEXT[251];
} orderremarksS;
#else /* TRANSCLASS */
typedef struct N_ORDERREMARKS {
    long CSCORDERNO;
    long POSITIONNO;
    short REMARKTYPE;
    short TEXTNUMBER;
    char REMARKTEXT[251];

    bool operator == (const N_ORDERREMARKS& right) const {
        return (
            CSCORDERNO == right.CSCORDERNO &&
            POSITIONNO == right.POSITIONNO &&
            REMARKTYPE == right.REMARKTYPE &&
            TEXTNUMBER == right.TEXTNUMBER &&
            !strcmp(REMARKTEXT, right.REMARKTEXT)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        CSCORDERNO = 0;
        POSITIONNO = 0;
        REMARKTYPE = 0;
        TEXTNUMBER = 0;
        strcpy(REMARKTEXT, " " );
#endif
    }
} orderremarksS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ORDERREMARKS **************************************/

struct S_ORDERREMARKS {
    char CSCORDERNO[11];
    char POSITIONNO[11];
    char REMARKTYPE[7];
    char TEXTNUMBER[7];
    char REMARKTEXT[250 + 1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ORDERREMARKS *********************/

struct O_ORDERREMARKS {
    char CSCORDERNO[11];
    char POSITIONNO[11];
    char REMARKTYPE[7];
    char TEXTNUMBER[7];
    char REMARKTEXT[250];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ORDERREMARKS ********************************/

struct C_ORDERREMARKS {
    long CSCORDERNO;
    long POSITIONNO;
    short REMARKTYPE;
    short TEXTNUMBER;
    char REMARKTEXT[251];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ORDERREMARKS ******************************/

struct I_ORDERREMARKS {
    short CSCORDERNO;
    short POSITIONNO;
    short REMARKTYPE;
    short TEXTNUMBER;
    short REMARKTEXT;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ORDERREMARKS ****************************************/

#if defined (BUF_DESC)
static struct buf_desc ORDERREMARKS_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 250, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc ORDERREMARKS_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 250, 0 },
};
#endif

/* description for datatypes of ORDERREMARKS **********************************/

 #define ORDERREMARKS_S390 \
         long CSCORDERNO; \
         long POSITIONNO; \
         short REMARKTYPE; \
         short TEXTNUMBER; \
         char REMARKTEXT[251]; \



/* Copy-Function Struct to single Data ORDERREMARKS ***************************/

 #define ORDERREMARKS_S390_COPY_TO_SINGLE(_x_) \
         CSCORDERNO=_x_->CSCORDERNO;\
         POSITIONNO=_x_->POSITIONNO;\
         REMARKTYPE=_x_->REMARKTYPE;\
         TEXTNUMBER=_x_->TEXTNUMBER;\
          strcpy(REMARKTEXT,_x_->REMARKTEXT);\

 #define ORDERREMARKS_S390_COPY_TO_STRUCT(_x_) \
          _x_->CSCORDERNO=CSCORDERNO;\
          _x_->POSITIONNO=POSITIONNO;\
          _x_->REMARKTYPE=REMARKTYPE;\
          _x_->TEXTNUMBER=TEXTNUMBER;\
          strcpy(_x_->REMARKTEXT,REMARKTEXT);\



/* FunctionNumber-Define of orderremarks **************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of orderremarks **********************************/


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

class CORDERREMARKS : public ppDadeVirtual {
public:
    orderremarksS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<orderremarksS> lst; // class list

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
                     vector< orderremarksS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     orderremarksS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< orderremarksS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<orderremarksS>::iterator
                 beginList() { return lst.begin(); }
    vector<orderremarksS>::iterator
                 endList  () { return lst.end  (); }

    long         GetCscorderno() const { return s.CSCORDERNO; }
    long         GetPositionno() const { return s.POSITIONNO; }
    short        GetRemarktype() const { return s.REMARKTYPE; }
    short        GetTextnumber() const { return s.TEXTNUMBER; }
    const char*  GetRemarktext(ppString & t) const { t = s.REMARKTEXT; t.erasespace(ppString::END); return t.c_str(); }

    const orderremarksS &
                 GetStruct() const { return s; }
    void         SetCscorderno(long t) { s.CSCORDERNO = t; }
    void         SetPositionno(long t) { s.POSITIONNO = t; }
    void         SetRemarktype(short t) { s.REMARKTYPE = t; }
    void         SetTextnumber(short t) { s.TEXTNUMBER = t; }
    void         SetRemarktext(const ppString & t) { ppGStrCopy(s.REMARKTEXT, t.c_str(), L_ORDERREMARKS_REMARKTEXT); }

    void         SetStruct(const orderremarksS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CORDERREMARKS() {
        ::buf_default((void *)&s, ORDERREMARKS_BES, ORDERREMARKS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CORDERREMARKS() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, ORDERREMARKS_BES, ORDERREMARKS_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, ORDERREMARKS_BES, (int)ORDERREMARKS_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, ORDERREMARKS_BES, (int)ORDERREMARKS_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_ORDERREMARKS & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.REMARKTEXT);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, ORDERREMARKS_BES, (int)ORDERREMARKS_ANZ, error_msg);
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
/* CreateSqlStatement of ORDERREMARKS *****************************************/

 #define ORDERREMARKS_CREATE(x) EXEC SQL create table x (\
         CSCORDERNO integer default 0 not null,\
         POSITIONNO integer default 0 not null,\
         REMARKTYPE smallint default 0 not null,\
         TEXTNUMBER smallint default 0 not null,\
         REMARKTEXT varchar(250,0) default " " not null) in ksc extent size 1176 next size 120 lock mode row;



/* CreateIndexStatement of ORDERREMARKS ***************************************/

 #define ORDERREMARKS_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_orderremarks_1 on _X_(\
              cscorderno,\
              PositionNo,\
              remarktype,\
              textnumber ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ORDERREMARKS ***************************************/

 #define ORDERREMARKS_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_orderremarks_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
