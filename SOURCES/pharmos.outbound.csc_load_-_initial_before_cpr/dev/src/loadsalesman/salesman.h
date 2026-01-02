#ifndef __PP_SALESMAN_H_
#define __PP_SALESMAN_H_

/******************************************************************************/
/* c:\Marathon\orderentry\load\loadsalesman\src\SalesMan **********************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <pplib/bufkon.h>

/* Length-Define of SALESMAN **************************************************/

#define L_SALESMAN_BRANCHNO 6
#define L_SALESMAN_SALESMANNO 6
#define L_SALESMAN_SALESMANNAME 30
#define L_SALESMAN_SALESMANSTREET 30
#define L_SALESMAN_SALESMANCITY 30
#define L_SALESMAN_POSTCODE 5
#define L_SALESMAN_SACTIVE 6
#define L_SALESMAN_SPREWHOLE 6
#define L_SALESMAN_EMAILADRESS 50

/* Length/Count-Define of SALESMAN ********************************************/

#define LS_SALESMAN_BRANCHNO 5 + 1
#define LS_SALESMAN_SALESMANNO 5 + 1
#define LS_SALESMAN_SALESMANNAME 30 + 1
#define LS_SALESMAN_SALESMANSTREET 30 + 1
#define LS_SALESMAN_SALESMANCITY 30 + 1
#define LS_SALESMAN_POSTCODE 5 + 1
#define LS_SALESMAN_SACTIVE 5 + 1
#define LS_SALESMAN_SPREWHOLE 5 + 1
#define LS_SALESMAN_EMAILADRESS 50 + 1

#define SALESMANBRANCHNO 0
#define SALESMANSALESMANNO 1
#define SALESMANSALESMANNAME 2
#define SALESMANSALESMANSTREET 3
#define SALESMANSALESMANCITY 4
#define SALESMANPOSTCODE 5
#define SALESMANSACTIVE 6
#define SALESMANSPREWHOLE 7
#define SALESMANEMAILADRESS 8

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define SALESMAN_H
#define SALESMAN_ANZ ( sizeof(SALESMAN_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of SALESMAN ******************************************************/

#define SALESMAN_LISTE \
        SALESMAN.BRANCHNO,\
        SALESMAN.SALESMANNO,\
        SALESMAN.SALESMANNAME,\
        SALESMAN.SALESMANSTREET,\
        SALESMAN.SALESMANCITY,\
        SALESMAN.POSTCODE,\
        SALESMAN.SACTIVE,\
        SALESMAN.SPREWHOLE,\
        SALESMAN.EMAILADRESS
#define SALESMAN_LISTE_390 \
        BRANCHNO,\
        SALESMANNO,\
        SALESMANNAME,\
        SALESMANSTREET,\
        SALESMANCITY,\
        POSTCODE,\
        SACTIVE,\
        SPREWHOLE,\
        EMAILADRESS
#define SALESMAN_PLISTE \
        "SALESMAN.BRANCHNO,"\
        "SALESMAN.SALESMANNO,"\
        "SALESMAN.SALESMANNAME,"\
        "SALESMAN.SALESMANSTREET,"\
        "SALESMAN.SALESMANCITY,"\
        "SALESMAN.POSTCODE,"\
        "SALESMAN.SACTIVE,"\
        "SALESMAN.SPREWHOLE,"\
        "SALESMAN.EMAILADRESS"
#define SALESMAN_PELISTE \
        "BRANCHNO,"\
        "SALESMANNO,"\
        "SALESMANNAME,"\
        "SALESMANSTREET,"\
        "SALESMANCITY,"\
        "POSTCODE,"\
        "SACTIVE,"\
        "SPREWHOLE,"\
        "EMAILADRESS"
#define SALESMAN_UPDLISTE \
        "BRANCHNO=?,"\
        "SALESMANNO=?,"\
        "SALESMANNAME=?,"\
        "SALESMANSTREET=?,"\
        "SALESMANCITY=?,"\
        "POSTCODE=?,"\
        "SACTIVE=?,"\
        "SPREWHOLE=?,"\
        "EMAILADRESS=?"
/* SqlMacros-Define of SALESMAN ***********************************************/

#define SALESMAN_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->SALESMANNO,\
        :x->SALESMANNAME,\
        :x->SALESMANSTREET,\
        :x->SALESMANCITY,\
        :x->POSTCODE,\
        :x->SACTIVE,\
        :x->SPREWHOLE,\
        :x->EMAILADRESS
#define SALESMAN_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->SALESMANNO,\
        :x->SALESMANNAME,\
        :x->SALESMANSTREET,\
        :x->SALESMANCITY,\
        :x->POSTCODE,\
        :x->SACTIVE,\
        :x->SPREWHOLE,\
        :x->EMAILADRESS
#define SALESMAN_UPDATE(x) \
        SALESMAN.BRANCHNO=:x->BRANCHNO,\
        SALESMAN.SALESMANNO=:x->SALESMANNO,\
        SALESMAN.SALESMANNAME=:x->SALESMANNAME,\
        SALESMAN.SALESMANSTREET=:x->SALESMANSTREET,\
        SALESMAN.SALESMANCITY=:x->SALESMANCITY,\
        SALESMAN.POSTCODE=:x->POSTCODE,\
        SALESMAN.SACTIVE=:x->SACTIVE,\
        SALESMAN.SPREWHOLE=:x->SPREWHOLE,\
        SALESMAN.EMAILADRESS=:x->EMAILADRESS
/* SqlMacros390-Define of SALESMAN ********************************************/

#define SALESMAN_ZEIGER_390 \
        :BRANCHNO,\
        :SALESMANNO,\
        :SALESMANNAME,\
        :SALESMANSTREET,\
        :SALESMANCITY,\
        :POSTCODE,\
        :SACTIVE,\
        :SPREWHOLE,\
        :EMAILADRESS
#define SALESMAN_UPDATE_390 \
        BRANCHNO=:BRANCHNO,\
        SALESMANNO=:SALESMANNO,\
        SALESMANNAME=:SALESMANNAME,\
        SALESMANSTREET=:SALESMANSTREET,\
        SALESMANCITY=:SALESMANCITY,\
        POSTCODE=:POSTCODE,\
        SACTIVE=:SACTIVE,\
        SPREWHOLE=:SPREWHOLE,\
        EMAILADRESS=:EMAILADRESS
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of SALESMAN ************************************************/

#ifndef TRANSCLASS
typedef struct N_SALESMAN {
    short BRANCHNO;
    short SALESMANNO;
    char SALESMANNAME[31];
    char SALESMANSTREET[31];
    char SALESMANCITY[31];
    char POSTCODE[6];
    short SACTIVE;
    short SPREWHOLE;
    char EMAILADRESS[51];
} salesmanS;
#else /* TRANSCLASS */
typedef struct N_SALESMAN {
    short BRANCHNO;
    short SALESMANNO;
    char SALESMANNAME[31];
    char SALESMANSTREET[31];
    char SALESMANCITY[31];
    char POSTCODE[6];
    short SACTIVE;
    short SPREWHOLE;
    char EMAILADRESS[51];

    bool operator == (const N_SALESMAN& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            SALESMANNO == right.SALESMANNO &&
            !strcmp(SALESMANNAME, right.SALESMANNAME) &&
            !strcmp(SALESMANSTREET, right.SALESMANSTREET) &&
            !strcmp(SALESMANCITY, right.SALESMANCITY) &&
            !strcmp(POSTCODE, right.POSTCODE) &&
            SACTIVE == right.SACTIVE &&
            SPREWHOLE == right.SPREWHOLE &&
            !strcmp(EMAILADRESS, right.EMAILADRESS)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        SALESMANNO = 0;
        strcpy(SALESMANNAME, " " );
        strcpy(SALESMANSTREET, " " );
        strcpy(SALESMANCITY, " " );
        strcpy(POSTCODE, " " );
        SACTIVE = 0;
        SPREWHOLE = 0;
        strcpy(EMAILADRESS, " " );
#endif
    }
} salesmanS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of SALESMAN ******************************************/

struct S_SALESMAN {
    char BRANCHNO[7];
    char SALESMANNO[7];
    char SALESMANNAME[30 + 1];
    char SALESMANSTREET[30 + 1];
    char SALESMANCITY[30 + 1];
    char POSTCODE[5 + 1];
    char SACTIVE[7];
    char SPREWHOLE[7];
    char EMAILADRESS[50 + 1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of SALESMAN *************************/

struct O_SALESMAN {
    char BRANCHNO[7];
    char SALESMANNO[7];
    char SALESMANNAME[30];
    char SALESMANSTREET[30];
    char SALESMANCITY[30];
    char POSTCODE[5];
    char SACTIVE[7];
    char SPREWHOLE[7];
    char EMAILADRESS[50];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of SALESMAN ************************************/

struct C_SALESMAN {
    short BRANCHNO;
    short SALESMANNO;
    char SALESMANNAME[31];
    char SALESMANSTREET[31];
    char SALESMANCITY[31];
    char POSTCODE[6];
    short SACTIVE;
    short SPREWHOLE;
    char EMAILADRESS[51];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of SALESMAN **********************************/

struct I_SALESMAN {
    short BRANCHNO;
    short SALESMANNO;
    short SALESMANNAME;
    short SALESMANSTREET;
    short SALESMANCITY;
    short POSTCODE;
    short SACTIVE;
    short SPREWHOLE;
    short EMAILADRESS;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of SALESMAN ********************************************/

#if defined (BUF_DESC)
static struct buf_desc SALESMAN_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 5, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 50, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc SALESMAN_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 5, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 50, 0 },
};
#endif

/* description for datatypes of SALESMAN **************************************/

 #define SALESMAN_S390 \
         short BRANCHNO; \
         short SALESMANNO; \
         char SALESMANNAME[31]; \
         char SALESMANSTREET[31]; \
         char SALESMANCITY[31]; \
         char POSTCODE[6]; \
         short SACTIVE; \
         short SPREWHOLE; \
         char EMAILADRESS[51]; \



/* Copy-Function Struct to single Data SALESMAN *******************************/

 #define SALESMAN_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         SALESMANNO=_x_->SALESMANNO;\
          strcpy(SALESMANNAME,_x_->SALESMANNAME);\
          strcpy(SALESMANSTREET,_x_->SALESMANSTREET);\
          strcpy(SALESMANCITY,_x_->SALESMANCITY);\
          strcpy(POSTCODE,_x_->POSTCODE);\
         SACTIVE=_x_->SACTIVE;\
         SPREWHOLE=_x_->SPREWHOLE;\
          strcpy(EMAILADRESS,_x_->EMAILADRESS);\

 #define SALESMAN_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->SALESMANNO=SALESMANNO;\
          strcpy(_x_->SALESMANNAME,SALESMANNAME);\
          strcpy(_x_->SALESMANSTREET,SALESMANSTREET);\
          strcpy(_x_->SALESMANCITY,SALESMANCITY);\
          strcpy(_x_->POSTCODE,POSTCODE);\
          _x_->SACTIVE=SACTIVE;\
          _x_->SPREWHOLE=SPREWHOLE;\
          strcpy(_x_->EMAILADRESS,EMAILADRESS);\



/* FunctionNumber-Define of SalesMan ******************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of SalesMan **************************************/


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

class CSALESMAN : public ppDadeVirtual {
public:
    salesmanS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<salesmanS> lst; // class list

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
                     vector< salesmanS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     salesmanS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< salesmanS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<salesmanS>::iterator
                 beginList() { return lst.begin(); }
    vector<salesmanS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    short        GetSalesmanno() const { return s.SALESMANNO; }
    const char*  GetSalesmanname(ppString & t) const { t = s.SALESMANNAME; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetSalesmanstreet(ppString & t) const { t = s.SALESMANSTREET; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetSalesmancity(ppString & t) const { t = s.SALESMANCITY; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetPostcode(ppString & t) const { t = s.POSTCODE; t.erasespace(ppString::END); return t.c_str(); }
    short        GetSactive() const { return s.SACTIVE; }
    short        GetSprewhole() const { return s.SPREWHOLE; }
    const char*  GetEmailadress(ppString & t) const { t = s.EMAILADRESS; t.erasespace(ppString::END); return t.c_str(); }

    const salesmanS &
                 GetStruct() const { return s; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetSalesmanno(short t) { s.SALESMANNO = t; }
    void         SetSalesmanname(const ppString & t) { ppGStrCopy(s.SALESMANNAME, t.c_str(), L_SALESMAN_SALESMANNAME); }
    void         SetSalesmanstreet(const ppString & t) { ppGStrCopy(s.SALESMANSTREET, t.c_str(), L_SALESMAN_SALESMANSTREET); }
    void         SetSalesmancity(const ppString & t) { ppGStrCopy(s.SALESMANCITY, t.c_str(), L_SALESMAN_SALESMANCITY); }
    void         SetPostcode(const ppString & t) { ppGStrCopy(s.POSTCODE, t.c_str(), L_SALESMAN_POSTCODE); }
    void         SetSactive(short t) { s.SACTIVE = t; }
    void         SetSprewhole(short t) { s.SPREWHOLE = t; }
    void         SetEmailadress(const ppString & t) { ppGStrCopy(s.EMAILADRESS, t.c_str(), L_SALESMAN_EMAILADRESS); }

    void         SetStruct(const salesmanS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CSALESMAN() {
        ::buf_default((void *)&s, SALESMAN_BES, SALESMAN_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CSALESMAN() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, SALESMAN_BES, SALESMAN_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, SALESMAN_BES, (int)SALESMAN_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, SALESMAN_BES, (int)SALESMAN_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_SALESMAN & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.SALESMANNAME);
        ppGStripLast(d.SALESMANSTREET);
        ppGStripLast(d.SALESMANCITY);
        ppGStripLast(d.POSTCODE);
        ppGStripLast(d.EMAILADRESS);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, SALESMAN_BES, (int)SALESMAN_ANZ, error_msg);
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
/* CreateSqlStatement of SALESMAN *********************************************/

 #define SALESMAN_CREATE(x) EXEC SQL create table x (\
         BRANCHNO smallint default 0 not null,\
         SALESMANNO smallint default 0 not null,\
         SALESMANNAME char(30) default " " not null,\
         SALESMANSTREET char(30) default " " not null,\
         SALESMANCITY char(30) default " " not null,\
         POSTCODE char(5) default " " not null,\
         SACTIVE smallint default 0 not null,\
         SPREWHOLE smallint default 0 not null,\
         EMAILADRESS char(50) default " " not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of SALESMAN *******************************************/

 #define SALESMAN_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_salesman_1 on _X_(\
              BranchNo,\
              SalesManNo ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of SALESMAN *******************************************/

 #define SALESMAN_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_salesman_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
