#ifndef __PP_TOTEINFO_H_
#define __PP_TOTEINFO_H_

/******************************************************************************/
/* c:\tmp\TOTEINFO ************************************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of TOTEINFO **************************************************/

#define L_TOTEINFO_ID 11
#define L_TOTEINFO_DATAINFOTYPE 5
#define L_TOTEINFO_TOTENO 11
#define L_TOTEINFO_ORDERNOIBT 11
#define L_TOTEINFO_BRANCHNOIBT 6
#define L_TOTEINFO_PICKINGSTARTDATETIME 11
#define L_TOTEINFO_TOURID 6
#define L_TOTEINFO_BRANCHNO 6

/* Length/Count-Define of TOTEINFO ********************************************/

#define LS_TOTEINFO_ID 10 + 1
#define LS_TOTEINFO_DATAINFOTYPE 5 + 1
#define LS_TOTEINFO_TOTENO 10 + 1
#define LS_TOTEINFO_ORDERNOIBT 10 + 1
#define LS_TOTEINFO_BRANCHNOIBT 5 + 1
#define LS_TOTEINFO_PICKINGSTARTDATETIME 10 + 1
#define LS_TOTEINFO_TOURID 6 + 1
#define LS_TOTEINFO_BRANCHNO 5 + 1

#define TOTEINFOID 0
#define TOTEINFODATAINFOTYPE 1
#define TOTEINFOTOTENO 2
#define TOTEINFOORDERNOIBT 3
#define TOTEINFOBRANCHNOIBT 4
#define TOTEINFOPICKINGSTARTDATETIME 5
#define TOTEINFOTOURID 6
#define TOTEINFOBRANCHNO 7

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define TOTEINFO_H
#define TOTEINFO_ANZ ( sizeof(TOTEINFO_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of TOTEINFO ******************************************************/

#define TOTEINFO_LISTE \
        TOTEINFO.ID,\
        TOTEINFO.DATAINFOTYPE,\
        TOTEINFO.TOTENO,\
        TOTEINFO.ORDERNOIBT,\
        TOTEINFO.BRANCHNOIBT,\
        TOTEINFO.PICKINGSTARTDATETIME,\
        TOTEINFO.TOURID,\
        TOTEINFO.BRANCHNO
#define TOTEINFO_LISTE_390 \
        ID,\
        DATAINFOTYPE,\
        TOTENO,\
        ORDERNOIBT,\
        BRANCHNOIBT,\
        PICKINGSTARTDATETIME,\
        TOURID,\
        BRANCHNO
#define TOTEINFO_PLISTE \
        "TOTEINFO.ID,"\
        "TOTEINFO.DATAINFOTYPE,"\
        "TOTEINFO.TOTENO,"\
        "TOTEINFO.ORDERNOIBT,"\
        "TOTEINFO.BRANCHNOIBT,"\
        "TOTEINFO.PICKINGSTARTDATETIME,"\
        "TOTEINFO.TOURID,"\
        "TOTEINFO.BRANCHNO"
#define TOTEINFO_PELISTE \
        "ID,"\
        "DATAINFOTYPE,"\
        "TOTENO,"\
        "ORDERNOIBT,"\
        "BRANCHNOIBT,"\
        "PICKINGSTARTDATETIME,"\
        "TOURID,"\
        "BRANCHNO"
#define TOTEINFO_UPDLISTE \
        "ID=?,"\
        "DATAINFOTYPE=?,"\
        "TOTENO=?,"\
        "ORDERNOIBT=?,"\
        "BRANCHNOIBT=?,"\
        "PICKINGSTARTDATETIME=?,"\
        "TOURID=?,"\
        "BRANCHNO=?"
/* SqlMacros-Define of TOTEINFO ***********************************************/

#define TOTEINFO_ZEIGER(x) \
        :x->ID,\
        :x->DATAINFOTYPE,\
        :x->TOTENO,\
        :x->ORDERNOIBT,\
        :x->BRANCHNOIBT,\
        :x->PICKINGSTARTDATETIME,\
        :x->TOURID,\
        :x->BRANCHNO
#define TOTEINFO_ZEIGERSEL(x) \
        :x->ID,\
        :x->DATAINFOTYPE,\
        :x->TOTENO,\
        :x->ORDERNOIBT,\
        :x->BRANCHNOIBT,\
        :x->PICKINGSTARTDATETIME,\
        :x->TOURID,\
        :x->BRANCHNO
#define TOTEINFO_UPDATE(x) \
        TOTEINFO.DATAINFOTYPE=:x->DATAINFOTYPE,\
        TOTEINFO.TOTENO=:x->TOTENO,\
        TOTEINFO.ORDERNOIBT=:x->ORDERNOIBT,\
        TOTEINFO.BRANCHNOIBT=:x->BRANCHNOIBT,\
        TOTEINFO.PICKINGSTARTDATETIME=:x->PICKINGSTARTDATETIME,\
        TOTEINFO.TOURID=:x->TOURID,\
        TOTEINFO.BRANCHNO=:x->BRANCHNO
/* SqlMacros390-Define of TOTEINFO ********************************************/

#define TOTEINFO_ZEIGER_390 \
        :ID,\
        :DATAINFOTYPE,\
        :TOTENO,\
        :ORDERNOIBT,\
        :BRANCHNOIBT,\
        :PICKINGSTARTDATETIME,\
        :TOURID,\
        :BRANCHNO
#define TOTEINFO_UPDATE_390 \
        ID=:ID,\
        DATAINFOTYPE=:DATAINFOTYPE,\
        TOTENO=:TOTENO,\
        ORDERNOIBT=:ORDERNOIBT,\
        BRANCHNOIBT=:BRANCHNOIBT,\
        PICKINGSTARTDATETIME=:PICKINGSTARTDATETIME,\
        TOURID=:TOURID,\
        BRANCHNO=:BRANCHNO
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of TOTEINFO ************************************************/

#ifndef TRANSCLASS
typedef struct N_TOTEINFO {
    long ID;
    char DATAINFOTYPE[6];
    long TOTENO;
    long ORDERNOIBT;
    short BRANCHNOIBT;
    long PICKINGSTARTDATETIME;
    char TOURID[7];
    short BRANCHNO;
} toteinfoS;
#else /* TRANSCLASS */
typedef struct N_TOTEINFO {
    long ID;
    char DATAINFOTYPE[6];
    long TOTENO;
    long ORDERNOIBT;
    short BRANCHNOIBT;
    long PICKINGSTARTDATETIME;
    char TOURID[7];
    short BRANCHNO;

    bool operator == (const N_TOTEINFO& right) const {
        return (
            ID == right.ID &&
            !strcmp(DATAINFOTYPE, right.DATAINFOTYPE) &&
            TOTENO == right.TOTENO &&
            ORDERNOIBT == right.ORDERNOIBT &&
            BRANCHNOIBT == right.BRANCHNOIBT &&
            PICKINGSTARTDATETIME == right.PICKINGSTARTDATETIME &&
            !strcmp(TOURID, right.TOURID) &&
            BRANCHNO == right.BRANCHNO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        ID = 0;
        strcpy(DATAINFOTYPE, " " );
        TOTENO = 0;
        ORDERNOIBT = 0;
        BRANCHNOIBT = 0;
        PICKINGSTARTDATETIME = 0;
        strcpy(TOURID, " " );
        BRANCHNO = 0;
#endif
    }
} toteinfoS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of TOTEINFO ******************************************/

struct S_TOTEINFO {
    char ID[11];
    char DATAINFOTYPE[5 + 1];
    char TOTENO[11];
    char ORDERNOIBT[11];
    char BRANCHNOIBT[7];
    char PICKINGSTARTDATETIME[11];
    char TOURID[6 + 1];
    char BRANCHNO[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of TOTEINFO *************************/

struct O_TOTEINFO {
    char ID[11];
    char DATAINFOTYPE[5];
    char TOTENO[11];
    char ORDERNOIBT[11];
    char BRANCHNOIBT[7];
    char PICKINGSTARTDATETIME[11];
    char TOURID[6];
    char BRANCHNO[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of TOTEINFO ************************************/

struct C_TOTEINFO {
    long ID;
    char DATAINFOTYPE[6];
    long TOTENO;
    long ORDERNOIBT;
    short BRANCHNOIBT;
    long PICKINGSTARTDATETIME;
    char TOURID[7];
    short BRANCHNO;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of TOTEINFO **********************************/

struct I_TOTEINFO {
    short ID;
    short DATAINFOTYPE;
    short TOTENO;
    short ORDERNOIBT;
    short BRANCHNOIBT;
    short PICKINGSTARTDATETIME;
    short TOURID;
    short BRANCHNO;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of TOTEINFO ********************************************/

#if defined (BUF_DESC)
static struct buf_desc TOTEINFO_BES [] = {
   { TYP_L ,  11, 0 },
   { TYP_C, 5, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc TOTEINFO_BES [] = {
   { TYP_L ,  11, 0 },
   { TYP_C, 5, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* description for datatypes of TOTEINFO **************************************/

 #define TOTEINFO_S390 \
         long ID; \
         char DATAINFOTYPE[6]; \
         long TOTENO; \
         long ORDERNOIBT; \
         short BRANCHNOIBT; \
         long PICKINGSTARTDATETIME; \
         char TOURID[7]; \
         short BRANCHNO; \



/* Copy-Function Struct to single Data TOTEINFO *******************************/

 #define TOTEINFO_S390_COPY_TO_SINGLE(_x_) \
         ID=_x_->ID;\
          strcpy(DATAINFOTYPE,_x_->DATAINFOTYPE);\
         TOTENO=_x_->TOTENO;\
         ORDERNOIBT=_x_->ORDERNOIBT;\
         BRANCHNOIBT=_x_->BRANCHNOIBT;\
         PICKINGSTARTDATETIME=_x_->PICKINGSTARTDATETIME;\
          strcpy(TOURID,_x_->TOURID);\
         BRANCHNO=_x_->BRANCHNO;\

 #define TOTEINFO_S390_COPY_TO_STRUCT(_x_) \
          _x_->ID=ID;\
          strcpy(_x_->DATAINFOTYPE,DATAINFOTYPE);\
          _x_->TOTENO=TOTENO;\
          _x_->ORDERNOIBT=ORDERNOIBT;\
          _x_->BRANCHNOIBT=BRANCHNOIBT;\
          _x_->PICKINGSTARTDATETIME=PICKINGSTARTDATETIME;\
          strcpy(_x_->TOURID,TOURID);\
          _x_->BRANCHNO=BRANCHNO;\



/* FunctionNumber-Define of TOTEINFO ******************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of TOTEINFO **************************************/


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

class CTOTEINFO : public ppDadeVirtual {
public:
    toteinfoS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<toteinfoS> lst; // class list

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
                     vector< toteinfoS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     toteinfoS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< toteinfoS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<toteinfoS>::iterator
                 beginList() { return lst.begin(); }
    vector<toteinfoS>::iterator
                 endList  () { return lst.end  (); }

    long         GetId() const { return s.ID; }
    const char*  GetDatainfotype(ppString & t) const { t = s.DATAINFOTYPE; t.erasespace(ppString::END); return t.c_str(); }
    long         GetToteno() const { return s.TOTENO; }
    long         GetOrdernoibt() const { return s.ORDERNOIBT; }
    short        GetBranchnoibt() const { return s.BRANCHNOIBT; }
    long         GetPickingstartdatetime() const { return s.PICKINGSTARTDATETIME; }
    const char*  GetTourid(ppString & t) const { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
    short        GetBranchno() const { return s.BRANCHNO; }

    const toteinfoS &
                 GetStruct() const { return s; }
    void         SetId(long t) { s.ID = t; }
    void         SetDatainfotype(const ppString & t) { ppGStrCopy(s.DATAINFOTYPE, t.c_str(), L_TOTEINFO_DATAINFOTYPE); }
    void         SetToteno(long t) { s.TOTENO = t; }
    void         SetOrdernoibt(long t) { s.ORDERNOIBT = t; }
    void         SetBranchnoibt(short t) { s.BRANCHNOIBT = t; }
    void         SetPickingstartdatetime(long t) { s.PICKINGSTARTDATETIME = t; }
    void         SetTourid(const ppString & t) { ppGStrCopy(s.TOURID, t.c_str(), L_TOTEINFO_TOURID); }
    void         SetBranchno(short t) { s.BRANCHNO = t; }

    void         SetStruct(const toteinfoS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CTOTEINFO() {
        ::buf_default((void *)&s, TOTEINFO_BES, TOTEINFO_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CTOTEINFO() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, TOTEINFO_BES, TOTEINFO_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, TOTEINFO_BES, (int)TOTEINFO_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, TOTEINFO_BES, (int)TOTEINFO_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_TOTEINFO & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.DATAINFOTYPE);
        ppGStripLast(d.TOURID);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, TOTEINFO_BES, (int)TOTEINFO_ANZ, error_msg);
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
/* CreateSqlStatement of TOTEINFO *********************************************/

 #define TOTEINFO_CREATE(x) EXEC SQL create table x (\
         ID serial not null,\
         DATAINFOTYPE varchar(5,0) default " " not null,\
         TOTENO integer default 0 not null,\
         ORDERNOIBT integer default 0 not null,\
         BRANCHNOIBT smallint default 0 not null,\
         PICKINGSTARTDATETIME integer default 0 not null,\
         TOURID char(6) default " " not null,\
         BRANCHNO smallint default 0 not null) in ksc extent size 392 next size 40 lock mode row;



/* CreateIndexStatement of TOTEINFO *******************************************/

 #define TOTEINFO_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index pk_toteinfo on _X_(\
              id ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create unique index uid_toteinfo on _X_(\
              DataInfoType,\
              BranchNoIBT,\
              OrderNoIBT,\
              ToteNo,\
              BranchNo ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of TOTEINFO *******************************************/

 #define TOTEINFO_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index pk_toteinfo;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index uid_toteinfo;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
