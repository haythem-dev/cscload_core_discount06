#ifndef __PP_POTENTIALCUSTOMERTOURS_H_
#define __PP_POTENTIALCUSTOMERTOURS_H_

/******************************************************************************/
/* c:\Marathon\orderentry\load\loadroutes\src\PotentialCustomerTours **********/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <pplib/bufkon.h>

/* Length-Define of POTENTIALCUSTOMERTOURS ************************************/

#define L_POTENTIALCUSTOMERTOURS_BRANCHNO 6
#define L_POTENTIALCUSTOMERTOURS_CUSTOMERNO 11
#define L_POTENTIALCUSTOMERTOURS_TOURID 6
#define L_POTENTIALCUSTOMERTOURS_UPDATESIGN 1

/* Length/Count-Define of POTENTIALCUSTOMERTOURS ******************************/

#define LS_POTENTIALCUSTOMERTOURS_BRANCHNO 5 + 1
#define LS_POTENTIALCUSTOMERTOURS_CUSTOMERNO 10 + 1
#define LS_POTENTIALCUSTOMERTOURS_TOURID 6 + 1
#define LS_POTENTIALCUSTOMERTOURS_UPDATESIGN 1 + 1

#define POTENTIALCUSTOMERTOURSBRANCHNO 0
#define POTENTIALCUSTOMERTOURSCUSTOMERNO 1
#define POTENTIALCUSTOMERTOURSTOURID 2
#define POTENTIALCUSTOMERTOURSUPDATESIGN 3

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define POTENTIALCUSTOMERTOURS_H
#define POTENTIALCUSTOMERTOURS_ANZ ( sizeof(POTENTIALCUSTOMERTOURS_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of POTENTIALCUSTOMERTOURS ****************************************/

#define POTENTIALCUSTOMERTOURS_LISTE \
        POTENTIALCUSTOMERTOURS.BRANCHNO,\
        POTENTIALCUSTOMERTOURS.CUSTOMERNO,\
        POTENTIALCUSTOMERTOURS.TOURID,\
        POTENTIALCUSTOMERTOURS.UPDATESIGN
#define POTENTIALCUSTOMERTOURS_LISTE_390 \
        BRANCHNO,\
        CUSTOMERNO,\
        TOURID,\
        UPDATESIGN
#define POTENTIALCUSTOMERTOURS_PLISTE \
        "POTENTIALCUSTOMERTOURS.BRANCHNO,"\
        "POTENTIALCUSTOMERTOURS.CUSTOMERNO,"\
        "POTENTIALCUSTOMERTOURS.TOURID,"\
        "POTENTIALCUSTOMERTOURS.UPDATESIGN"
#define POTENTIALCUSTOMERTOURS_PELISTE \
        "BRANCHNO,"\
        "CUSTOMERNO,"\
        "TOURID,"\
        "UPDATESIGN"
#define POTENTIALCUSTOMERTOURS_UPDLISTE \
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "TOURID=?,"\
        "UPDATESIGN=?"
/* SqlMacros-Define of POTENTIALCUSTOMERTOURS *********************************/

#define POTENTIALCUSTOMERTOURS_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->TOURID,\
        :x->UPDATESIGN
#define POTENTIALCUSTOMERTOURS_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->TOURID,\
        :x->UPDATESIGN
#define POTENTIALCUSTOMERTOURS_UPDATE(x) \
        POTENTIALCUSTOMERTOURS.BRANCHNO=:x->BRANCHNO,\
        POTENTIALCUSTOMERTOURS.CUSTOMERNO=:x->CUSTOMERNO,\
        POTENTIALCUSTOMERTOURS.TOURID=:x->TOURID,\
        POTENTIALCUSTOMERTOURS.UPDATESIGN=:x->UPDATESIGN
/* SqlMacros390-Define of POTENTIALCUSTOMERTOURS ******************************/

#define POTENTIALCUSTOMERTOURS_ZEIGER_390 \
        :BRANCHNO,\
        :CUSTOMERNO,\
        :TOURID,\
        :UPDATESIGN
#define POTENTIALCUSTOMERTOURS_UPDATE_390 \
        BRANCHNO=:BRANCHNO,\
        CUSTOMERNO=:CUSTOMERNO,\
        TOURID=:TOURID,\
        UPDATESIGN=:UPDATESIGN
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of POTENTIALCUSTOMERTOURS **********************************/

#ifndef TRANSCLASS
typedef struct N_POTENTIALCUSTOMERTOURS {
    short BRANCHNO;
    long CUSTOMERNO;
    char TOURID[7];
    char UPDATESIGN[2];
} potentialcustomertoursS;
#else /* TRANSCLASS */
typedef struct N_POTENTIALCUSTOMERTOURS {
    short BRANCHNO;
    long CUSTOMERNO;
    char TOURID[7];
    char UPDATESIGN[2];

    bool operator == (const N_POTENTIALCUSTOMERTOURS& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            CUSTOMERNO == right.CUSTOMERNO &&
            !strcmp(TOURID, right.TOURID) &&
            !strcmp(UPDATESIGN, right.UPDATESIGN)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        CUSTOMERNO = 0;
        strcpy(TOURID, " " );
        strcpy(UPDATESIGN, " " );
#endif
    }
} potentialcustomertoursS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of POTENTIALCUSTOMERTOURS ****************************/

struct S_POTENTIALCUSTOMERTOURS {
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char TOURID[6 + 1];
    char UPDATESIGN[1 + 1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of POTENTIALCUSTOMERTOURS ***********/

struct O_POTENTIALCUSTOMERTOURS {
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char TOURID[6];
    char UPDATESIGN[1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of POTENTIALCUSTOMERTOURS **********************/

struct C_POTENTIALCUSTOMERTOURS {
    short BRANCHNO;
    long CUSTOMERNO;
    char TOURID[7];
    char UPDATESIGN;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of POTENTIALCUSTOMERTOURS ********************/

struct I_POTENTIALCUSTOMERTOURS {
    short BRANCHNO;
    short CUSTOMERNO;
    short TOURID;
    short UPDATESIGN;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of POTENTIALCUSTOMERTOURS ******************************/

#if defined (BUF_DESC)
static struct buf_desc POTENTIALCUSTOMERTOURS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 1, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc POTENTIALCUSTOMERTOURS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 1, 0 },
};
#endif

/* description for datatypes of POTENTIALCUSTOMERTOURS ************************/

 #define POTENTIALCUSTOMERTOURS_S390 \
         short BRANCHNO; \
         long CUSTOMERNO; \
         char TOURID[7]; \
         char UPDATESIGN; \



/* Copy-Function Struct to single Data POTENTIALCUSTOMERTOURS *****************/

 #define POTENTIALCUSTOMERTOURS_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
          strcpy(TOURID,_x_->TOURID);\
         UPDATESIGN=_x_->UPDATESIGN;\

 #define POTENTIALCUSTOMERTOURS_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          strcpy(_x_->TOURID,TOURID);\
          _x_->UPDATESIGN=UPDATESIGN;\



/* FunctionNumber-Define of PotentialCustomerTours ****************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of PotentialCustomerTours ************************/


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

class CPOTENTIALCUSTOMERTOURS : public ppDadeVirtual {
public:
    potentialcustomertoursS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<potentialcustomertoursS> lst; // class list

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
                     vector< potentialcustomertoursS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     potentialcustomertoursS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< potentialcustomertoursS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<potentialcustomertoursS>::iterator
                 beginList() { return lst.begin(); }
    vector<potentialcustomertoursS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    const char*  GetTourid(ppString & t) const { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
    char         GetUpdatesign() const { return s.UPDATESIGN[0]; }

    const potentialcustomertoursS &
                 GetStruct() const { return s; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetTourid(const ppString & t) { ppGStrCopy(s.TOURID, t.c_str(), L_POTENTIALCUSTOMERTOURS_TOURID); }
    void         SetUpdatesign(char t) { s.UPDATESIGN[0] = t; s.UPDATESIGN[1] = '\0';}

    void         SetStruct(const potentialcustomertoursS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CPOTENTIALCUSTOMERTOURS() {
        ::buf_default((void *)&s, POTENTIALCUSTOMERTOURS_BES, POTENTIALCUSTOMERTOURS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CPOTENTIALCUSTOMERTOURS() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, POTENTIALCUSTOMERTOURS_BES, POTENTIALCUSTOMERTOURS_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, POTENTIALCUSTOMERTOURS_BES, (int)POTENTIALCUSTOMERTOURS_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, POTENTIALCUSTOMERTOURS_BES, (int)POTENTIALCUSTOMERTOURS_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_POTENTIALCUSTOMERTOURS & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.TOURID);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, POTENTIALCUSTOMERTOURS_BES, (int)POTENTIALCUSTOMERTOURS_ANZ, error_msg);
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
/* CreateSqlStatement of POTENTIALCUSTOMERTOURS *******************************/

 #define POTENTIALCUSTOMERTOURS_CREATE(x) EXEC SQL create table x (\
         BRANCHNO smallint default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         TOURID char(6) default " " not null,\
         UPDATESIGN char(1) default " " not null) in ksc extent size 3920 next size 392 lock mode row;



/* CreateIndexStatement of POTENTIALCUSTOMERTOURS *****************************/

 #define POTENTIALCUSTOMERTOURS_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_potcusttours_1 on _X_(\
              BranchNo,\
              CustomerNo,\
              tourid ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of POTENTIALCUSTOMERTOURS *****************************/

 #define POTENTIALCUSTOMERTOURS_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_potcusttours_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
