#ifndef __PP_CSCRESERVATIONTYPES_H_
#define __PP_CSCRESERVATIONTYPES_H_

/******************************************************************************/
/* c:\prri\Headerfiles\CSCReservationTypes ************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of CSCRESERVATIONTYPES ***************************************/

#define L_CSCRESERVATIONTYPES_ID 11
#define L_CSCRESERVATIONTYPES_CSCRESERVATIONTYPENAME 30
#define L_CSCRESERVATIONTYPES_CSCRESERVATIONTYPE 11
#define L_CSCRESERVATIONTYPES_WITHPHARMACYGROUP 6

/* Length/Count-Define of CSCRESERVATIONTYPES *********************************/

#define LS_CSCRESERVATIONTYPES_ID 10 + 1
#define LS_CSCRESERVATIONTYPES_CSCRESERVATIONTYPENAME 30 + 1
#define LS_CSCRESERVATIONTYPES_CSCRESERVATIONTYPE 10 + 1
#define LS_CSCRESERVATIONTYPES_WITHPHARMACYGROUP 5 + 1

#define CSCRESERVATIONTYPESID 0
#define CSCRESERVATIONTYPESCSCRESERVATIONTYPENAME 1
#define CSCRESERVATIONTYPESCSCRESERVATIONTYPE 2
#define CSCRESERVATIONTYPESWITHPHARMACYGROUP 3

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define CSCRESERVATIONTYPES_H
#define CSCRESERVATIONTYPES_ANZ ( sizeof(CSCRESERVATIONTYPES_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of CSCRESERVATIONTYPES *******************************************/

#define CSCRESERVATIONTYPES_LISTE \
        CSCRESERVATIONTYPES.ID,\
        CSCRESERVATIONTYPES.CSCRESERVATIONTYPENAME,\
        CSCRESERVATIONTYPES.CSCRESERVATIONTYPE,\
        CSCRESERVATIONTYPES.WITHPHARMACYGROUP
#define CSCRESERVATIONTYPES_LISTE_390 \
        ID,\
        CSCRESERVATIONTYPENAME,\
        CSCRESERVATIONTYPE,\
        WITHPHARMACYGROUP
#define CSCRESERVATIONTYPES_PLISTE \
        "CSCRESERVATIONTYPES.ID,"\
        "CSCRESERVATIONTYPES.CSCRESERVATIONTYPENAME,"\
        "CSCRESERVATIONTYPES.CSCRESERVATIONTYPE,"\
        "CSCRESERVATIONTYPES.WITHPHARMACYGROUP"
#define CSCRESERVATIONTYPES_PELISTE \
        "ID,"\
        "CSCRESERVATIONTYPENAME,"\
        "CSCRESERVATIONTYPE,"\
        "WITHPHARMACYGROUP"
#define CSCRESERVATIONTYPES_UPDLISTE \
        "ID=?,"\
        "CSCRESERVATIONTYPENAME=?,"\
        "CSCRESERVATIONTYPE=?,"\
        "WITHPHARMACYGROUP=?"
/* SqlMacros-Define of CSCRESERVATIONTYPES ************************************/

#define CSCRESERVATIONTYPES_ZEIGER(x) \
        :x->ID,\
        :x->CSCRESERVATIONTYPENAME,\
        :x->CSCRESERVATIONTYPE,\
        :x->WITHPHARMACYGROUP
#define CSCRESERVATIONTYPES_ZEIGERSEL(x) \
        :x->ID,\
        :x->CSCRESERVATIONTYPENAME,\
        :x->CSCRESERVATIONTYPE,\
        :x->WITHPHARMACYGROUP
#define CSCRESERVATIONTYPES_UPDATE(x) \
        CSCRESERVATIONTYPES.CSCRESERVATIONTYPENAME=:x->CSCRESERVATIONTYPENAME,\
        CSCRESERVATIONTYPES.CSCRESERVATIONTYPE=:x->CSCRESERVATIONTYPE,\
        CSCRESERVATIONTYPES.WITHPHARMACYGROUP=:x->WITHPHARMACYGROUP
/* SqlMacros390-Define of CSCRESERVATIONTYPES *********************************/

#define CSCRESERVATIONTYPES_ZEIGER_390 \
        :ID,\
        :CSCRESERVATIONTYPENAME,\
        :CSCRESERVATIONTYPE,\
        :WITHPHARMACYGROUP
#define CSCRESERVATIONTYPES_UPDATE_390 \
        ID=:ID,\
        CSCRESERVATIONTYPENAME=:CSCRESERVATIONTYPENAME,\
        CSCRESERVATIONTYPE=:CSCRESERVATIONTYPE,\
        WITHPHARMACYGROUP=:WITHPHARMACYGROUP
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of CSCRESERVATIONTYPES *************************************/

#ifndef TRANSCLASS
typedef struct N_CSCRESERVATIONTYPES {
    long ID;
    char CSCRESERVATIONTYPENAME[31];
    long CSCRESERVATIONTYPE;
    short WITHPHARMACYGROUP;
} cscreservationtypesS;
#else /* TRANSCLASS */
typedef struct N_CSCRESERVATIONTYPES {
    long ID;
    char CSCRESERVATIONTYPENAME[31];
    long CSCRESERVATIONTYPE;
    short WITHPHARMACYGROUP;

    bool operator == (const N_CSCRESERVATIONTYPES& right) const {
        return (
            ID == right.ID &&
            !strcmp(CSCRESERVATIONTYPENAME, right.CSCRESERVATIONTYPENAME) &&
            CSCRESERVATIONTYPE == right.CSCRESERVATIONTYPE &&
            WITHPHARMACYGROUP == right.WITHPHARMACYGROUP
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        ID = 0;
        strcpy(CSCRESERVATIONTYPENAME, " " );
        CSCRESERVATIONTYPE = 0;
        WITHPHARMACYGROUP = 0;
#endif
    }
} cscreservationtypesS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of CSCRESERVATIONTYPES *******************************/

struct S_CSCRESERVATIONTYPES {
    char ID[11];
    char CSCRESERVATIONTYPENAME[30 + 1];
    char CSCRESERVATIONTYPE[11];
    char WITHPHARMACYGROUP[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of CSCRESERVATIONTYPES **************/

struct O_CSCRESERVATIONTYPES {
    char ID[11];
    char CSCRESERVATIONTYPENAME[30];
    char CSCRESERVATIONTYPE[11];
    char WITHPHARMACYGROUP[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of CSCRESERVATIONTYPES *************************/

struct C_CSCRESERVATIONTYPES {
    long ID;
    char CSCRESERVATIONTYPENAME[31];
    long CSCRESERVATIONTYPE;
    short WITHPHARMACYGROUP;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of CSCRESERVATIONTYPES ***********************/

struct I_CSCRESERVATIONTYPES {
    short ID;
    short CSCRESERVATIONTYPENAME;
    short CSCRESERVATIONTYPE;
    short WITHPHARMACYGROUP;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CSCRESERVATIONTYPES *********************************/

#if defined (BUF_DESC)
static struct buf_desc CSCRESERVATIONTYPES_BES [] = {
   { TYP_L ,  11, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CSCRESERVATIONTYPES_BES [] = {
   { TYP_L ,  11, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* description for datatypes of CSCRESERVATIONTYPES ***************************/

 #define CSCRESERVATIONTYPES_S390 \
         long ID; \
         char CSCRESERVATIONTYPENAME[31]; \
         long CSCRESERVATIONTYPE; \
         short WITHPHARMACYGROUP; \



/* Copy-Function Struct to single Data CSCRESERVATIONTYPES ********************/

 #define CSCRESERVATIONTYPES_S390_COPY_TO_SINGLE(_x_) \
         ID=_x_->ID;\
          strcpy(CSCRESERVATIONTYPENAME,_x_->CSCRESERVATIONTYPENAME);\
         CSCRESERVATIONTYPE=_x_->CSCRESERVATIONTYPE;\
         WITHPHARMACYGROUP=_x_->WITHPHARMACYGROUP;\

 #define CSCRESERVATIONTYPES_S390_COPY_TO_STRUCT(_x_) \
          _x_->ID=ID;\
          strcpy(_x_->CSCRESERVATIONTYPENAME,CSCRESERVATIONTYPENAME);\
          _x_->CSCRESERVATIONTYPE=CSCRESERVATIONTYPE;\
          _x_->WITHPHARMACYGROUP=WITHPHARMACYGROUP;\



/* FunctionNumber-Define of CSCReservationTypes *******************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of CSCReservationTypes ***************************/


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

class CCSCRESERVATIONTYPES : public ppDadeVirtual {
public:
    cscreservationtypesS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<cscreservationtypesS> lst; // class list

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
                     vector< cscreservationtypesS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     cscreservationtypesS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< cscreservationtypesS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<cscreservationtypesS>::iterator
                 beginList() { return lst.begin(); }
    vector<cscreservationtypesS>::iterator
                 endList  () { return lst.end  (); }

    long         GetId() const { return s.ID; }
    const char*  GetCscreservationtypename(ppString & t) const { t = s.CSCRESERVATIONTYPENAME; t.erasespace(ppString::END); return t.c_str(); }
    long         GetCscreservationtype() const { return s.CSCRESERVATIONTYPE; }
    short        GetWithpharmacygroup() const { return s.WITHPHARMACYGROUP; }

    const cscreservationtypesS &
                 GetStruct() const { return s; }
    void         SetId(long t) { s.ID = t; }
    void         SetCscreservationtypename(const ppString & t) { ppGStrCopy(s.CSCRESERVATIONTYPENAME, t.c_str(), L_CSCRESERVATIONTYPES_CSCRESERVATIONTYPENAME); }
    void         SetCscreservationtype(long t) { s.CSCRESERVATIONTYPE = t; }
    void         SetWithpharmacygroup(short t) { s.WITHPHARMACYGROUP = t; }

    void         SetStruct(const cscreservationtypesS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCSCRESERVATIONTYPES() {
        ::buf_default((void *)&s, CSCRESERVATIONTYPES_BES, CSCRESERVATIONTYPES_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCSCRESERVATIONTYPES() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CSCRESERVATIONTYPES_BES, CSCRESERVATIONTYPES_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, CSCRESERVATIONTYPES_BES, (int)CSCRESERVATIONTYPES_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, CSCRESERVATIONTYPES_BES, (int)CSCRESERVATIONTYPES_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_CSCRESERVATIONTYPES & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.CSCRESERVATIONTYPENAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CSCRESERVATIONTYPES_BES, (int)CSCRESERVATIONTYPES_ANZ, error_msg);
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
/* CreateSqlStatement of CSCRESERVATIONTYPES **********************************/

 #define CSCRESERVATIONTYPES_CREATE(x) EXEC SQL create table x (\
         ID serial not null,\
         CSCRESERVATIONTYPENAME char(30) default " " not null,\
         CSCRESERVATIONTYPE integer default 0 not null,\
         WITHPHARMACYGROUP smallint default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of CSCRESERVATIONTYPES ********************************/

 #define CSCRESERVATIONTYPES_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_cscreservationtypes_1 on _X_(\
              id ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create unique index i_cscreservationtypes_2 on _X_(\
              cscreservationtype ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of CSCRESERVATIONTYPES ********************************/

 #define CSCRESERVATIONTYPES_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_cscreservationtypes_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_cscreservationtypes_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
