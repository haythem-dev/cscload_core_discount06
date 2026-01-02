#ifndef __PP_SUPPLINFO_H_
#define __PP_SUPPLINFO_H_

/******************************************************************************/
/* d:\prj\AA\UNIX\aapserv\src\SupplInfo ***************************************/
/* produced by DADE 6.21.6 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of SUPPLINFO *************************************************/

#define L_SUPPLINFO_ARTICLENO 11
#define L_SUPPLINFO_AVAILABILITYINFO 254
#define L_SUPPLINFO_PROGLIEFERDATUM 11
#define L_SUPPLINFO_LIEFERDATUM 11

/* Length/Count-Define of SUPPLINFO *******************************************/

#define LS_SUPPLINFO_ARTICLENO 10 + 1
#define LS_SUPPLINFO_AVAILABILITYINFO 254 + 1
#define LS_SUPPLINFO_PROGLIEFERDATUM 10 + 1
#define LS_SUPPLINFO_LIEFERDATUM 10 + 1

#define SUPPLINFOARTICLENO 0
#define SUPPLINFOAVAILABILITYINFO 1
#define SUPPLINFOPROGLIEFERDATUM 2
#define SUPPLINFOLIEFERDATUM 3

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define SUPPLINFO_H
#define SUPPLINFO_ANZ ( sizeof(SUPPLINFO_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of SUPPLINFO *****************************************************/

#define SUPPLINFO_LISTE \
        SUPPLDELIVERYINFO.ARTICLENO,\
        SUPPLDELIVERYINFO.AVAILABILITYINFO,\
        AADUMMY.PROGLIEFERDATUM,\
        AADUMMY.LIEFERDATUM
#define SUPPLINFO_LISTE_390 \
        ARTICLENO,\
        AVAILABILITYINFO,\
        PROGLIEFERDATUM,\
        LIEFERDATUM
#define SUPPLINFO_PLISTE \
        "SUPPLDELIVERYINFO.ARTICLENO,"\
        "SUPPLDELIVERYINFO.AVAILABILITYINFO"
#define SUPPLINFO_PELISTE \
        "ARTICLENO,"\
        "AVAILABILITYINFO"
#define SUPPLINFO_UPDLISTE \
        "ARTICLENO=?,"\
        "AVAILABILITYINFO=?"
/* SqlMacros-Define of SUPPLINFO **********************************************/

#define SUPPLINFO_ZEIGER(x) \
        :x->ARTICLENO,\
        :x->AVAILABILITYINFO
#define SUPPLINFO_ZEIGERSEL(x) \
        :x->ARTICLENO,\
        :x->AVAILABILITYINFO
#define SUPPLINFO_UPDATE(x) \
        SUPPLDELIVERYINFO.ARTICLENO=:x->ARTICLENO,\
        SUPPLDELIVERYINFO.AVAILABILITYINFO=:x->AVAILABILITYINFO
/* SqlMacros390-Define of SUPPLINFO *******************************************/

#define SUPPLINFO_ZEIGER_390 \
        :ARTICLENO,\
        :AVAILABILITYINFO,\
        :PROGLIEFERDATUM,\
        :LIEFERDATUM
#define SUPPLINFO_UPDATE_390 \
        ARTICLENO=:ARTICLENO,\
        AVAILABILITYINFO=:AVAILABILITYINFO
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of SUPPLINFO ***********************************************/

#ifndef TRANSCLASS
typedef struct N_SUPPLINFO {
    long ARTICLENO;
    char AVAILABILITYINFO[255];
    long PROGLIEFERDATUM;
    long LIEFERDATUM;
    long FETCH_REL;
} supplinfoS;
#else /* TRANSCLASS */
typedef struct N_SUPPLINFO {
    long ARTICLENO;
    char AVAILABILITYINFO[255];
    long PROGLIEFERDATUM;
    long LIEFERDATUM;
    long FETCH_REL;
    bool operator == (const N_SUPPLINFO& right) const {
        return (
            ARTICLENO == right.ARTICLENO &&
            !strcmp(AVAILABILITYINFO, right.AVAILABILITYINFO) &&
            PROGLIEFERDATUM == right.PROGLIEFERDATUM &&
            LIEFERDATUM == right.LIEFERDATUM
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        ARTICLENO = 0;
        strcpy(AVAILABILITYINFO, " " );
        PROGLIEFERDATUM = 0;
        LIEFERDATUM = 0;
#endif
    }
} supplinfoS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of SUPPLINFO *****************************************/

struct S_SUPPLINFO {
    char ARTICLENO[11];
    char AVAILABILITYINFO[254 + 1];
    char PROGLIEFERDATUM[11];
    char LIEFERDATUM[11];
    char FETCH_REL[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of SUPPLINFO ************************/

struct O_SUPPLINFO {
    char ARTICLENO[11];
    char AVAILABILITYINFO[254];
    char PROGLIEFERDATUM[11];
    char LIEFERDATUM[11];
    char FETCH_REL[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of SUPPLINFO ***********************************/

struct C_SUPPLINFO {
    long ARTICLENO;
    char AVAILABILITYINFO[255];
    long PROGLIEFERDATUM;
    long LIEFERDATUM;
    long FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of SUPPLINFO *********************************/

struct I_SUPPLINFO {
    short ARTICLENO;
    short AVAILABILITYINFO;
    short PROGLIEFERDATUM;
    short LIEFERDATUM;
    short FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of SUPPLINFO *******************************************/

#if defined (BUF_DESC)
static struct buf_desc SUPPLINFO_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 254, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc SUPPLINFO_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 254, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* description for datatypes of SUPPLINFO *************************************/

 #define SUPPLINFO_S390 \
         long ARTICLENO; \
         char AVAILABILITYINFO[255]; \
         long PROGLIEFERDATUM; \
         long LIEFERDATUM; \
         long FETCH_REL;



/* Copy-Function Struct to single Data SUPPLINFO ******************************/

 #define SUPPLINFO_S390_COPY_TO_SINGLE(_x_) \
         ARTICLENO=_x_->ARTICLENO;\
          strcpy(AVAILABILITYINFO,_x_->AVAILABILITYINFO);\
         PROGLIEFERDATUM=_x_->PROGLIEFERDATUM;\
         LIEFERDATUM=_x_->LIEFERDATUM;\
          FETCH_REL=_x_->FETCH_REL;\

 #define SUPPLINFO_S390_COPY_TO_STRUCT(_x_) \
          _x_->ARTICLENO=ARTICLENO;\
          strcpy(_x_->AVAILABILITYINFO,AVAILABILITYINFO);\
          _x_->PROGLIEFERDATUM=PROGLIEFERDATUM;\
          _x_->LIEFERDATUM=LIEFERDATUM;\
          _x_->FETCH_REL=FETCH_REL;\



/* FunctionNumber-Define of SupplInfo *****************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of SupplInfo *************************************/


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

class CSUPPLINFO : public ppDadeVirtual {
public:
    supplinfoS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<supplinfoS> lst; // class list

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
                     vector< supplinfoS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     supplinfoS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< supplinfoS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<supplinfoS>::iterator
                 beginList() { return lst.begin(); }
    vector<supplinfoS>::iterator
                 endList  () { return lst.end  (); }

    long         GetArticleno() const { return s.ARTICLENO; }
    const char*  GetAvailabilityinfo(ppString & t) const { t = s.AVAILABILITYINFO; t.erasespace(ppString::END); return t.c_str(); }
    long         GetProglieferdatum() const { return s.PROGLIEFERDATUM; }
    long         GetLieferdatum() const { return s.LIEFERDATUM; }

    const supplinfoS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetArticleno(long t) { s.ARTICLENO = t; }
    void         SetAvailabilityinfo(const ppString & t) { ppGStrCopy(s.AVAILABILITYINFO, t.c_str(), L_SUPPLINFO_AVAILABILITYINFO); }
    void         SetProglieferdatum(long t) { s.PROGLIEFERDATUM = t; }
    void         SetLieferdatum(long t) { s.LIEFERDATUM = t; }

    void         SetStruct(const supplinfoS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CSUPPLINFO() {
        ::buf_default((void *)&s, SUPPLINFO_BES, SUPPLINFO_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CSUPPLINFO() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, SUPPLINFO_BES, SUPPLINFO_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, SUPPLINFO_BES, (int)SUPPLINFO_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, SUPPLINFO_BES, (int)SUPPLINFO_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, SUPPLINFO_BES, (int)SUPPLINFO_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_SUPPLINFO & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.AVAILABILITYINFO);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, SUPPLINFO_BES, (int)SUPPLINFO_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CSUPPLINFO c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, SUPPLINFO_BES, (int)SUPPLINFO_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};
#endif    // TRANSCLASS
/* CreateSqlStatement of SUPPLINFO ********************************************/

 #define SUPPLINFO_CREATE(x) EXEC SQL create table x (\
         ARTICLENO integer default 0 not null,\
         AVAILABILITYINFO varchar(254,0) default " " not null,\
         PROGLIEFERDATUM integer default 0 not null,\
         LIEFERDATUM integer default 0 not null) extent size 236 next size 24 lock mode row;



/* CreateIndexStatement of SUPPLINFO ******************************************/

 #define SUPPLINFO_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_suppdelinfo_1 on _X_(\
              id );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index i_suppdelinfo_2 on _X_(\
              ArticleNo );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index i_suppdelinfo_3 on _X_(\
              SDIChangeDate );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of SUPPLINFO ******************************************/

 #define SUPPLINFO_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_suppdelinfo_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_suppdelinfo_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_suppdelinfo_3;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
