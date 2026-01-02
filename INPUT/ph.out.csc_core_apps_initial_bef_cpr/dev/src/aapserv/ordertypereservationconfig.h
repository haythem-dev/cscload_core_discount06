#ifndef __PP_ORDERTYPERESERVATIONCONFIG_H_
#define __PP_ORDERTYPERESERVATIONCONFIG_H_

/******************************************************************************/
/* c:\prri\Headerfiles\OrderTypeReservationConfig *****************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of ORDERTYPERESERVATIONCONFIG ********************************/

#define L_ORDERTYPERESERVATIONCONFIG_ID 11
#define L_ORDERTYPERESERVATIONCONFIG_PRIORITY 6
#define L_ORDERTYPERESERVATIONCONFIG_CSCORDERTYPE 2
#define L_ORDERTYPERESERVATIONCONFIG_ORDERTYPERESERVATIONCONFIGNAME 30
#define L_ORDERTYPERESERVATIONCONFIG_CSCRESERVATIONTYPE 11
#define L_ORDERTYPERESERVATIONCONFIG_RESERVEDSTOCKONLY 6
#define L_ORDERTYPERESERVATIONCONFIG_FREESTOCKHASPRIORITY 6

/* Length/Count-Define of ORDERTYPERESERVATIONCONFIG **************************/

#define LS_ORDERTYPERESERVATIONCONFIG_ID 10 + 1
#define LS_ORDERTYPERESERVATIONCONFIG_PRIORITY 5 + 1
#define LS_ORDERTYPERESERVATIONCONFIG_CSCORDERTYPE 2 + 1
#define LS_ORDERTYPERESERVATIONCONFIG_ORDERTYPERESERVATIONCONFIGNAME 30 + 1
#define LS_ORDERTYPERESERVATIONCONFIG_CSCRESERVATIONTYPE 10 + 1
#define LS_ORDERTYPERESERVATIONCONFIG_RESERVEDSTOCKONLY 5 + 1
#define LS_ORDERTYPERESERVATIONCONFIG_FREESTOCKHASPRIORITY 5 + 1

#define ORDERTYPERESERVATIONCONFIGID 0
#define ORDERTYPERESERVATIONCONFIGPRIORITY 1
#define ORDERTYPERESERVATIONCONFIGCSCORDERTYPE 2
#define ORDERTYPERESERVATIONCONFIGORDERTYPERESERVATIONCONFIGNAME 3
#define ORDERTYPERESERVATIONCONFIGCSCRESERVATIONTYPE 4
#define ORDERTYPERESERVATIONCONFIGRESERVEDSTOCKONLY 5
#define ORDERTYPERESERVATIONCONFIGFREESTOCKHASPRIORITY 6

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define ORDERTYPERESERVATIONCONFIG_H
#define ORDERTYPERESERVATIONCONFIG_ANZ ( sizeof(ORDERTYPERESERVATIONCONFIG_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ORDERTYPERESERVATIONCONFIG ************************************/

#define ORDERTYPERESERVATIONCONFIG_LISTE \
        ORDERTYPERESERVATIONCONFIG.ID,\
        ORDERTYPERESERVATIONCONFIG.PRIORITY,\
        ORDERTYPERESERVATIONCONFIG.CSCORDERTYPE,\
        ORDERTYPERESERVATIONCONFIG.ORDERTYPERESERVATIONCONFIGNAME,\
        ORDERTYPERESERVATIONCONFIG.CSCRESERVATIONTYPE,\
        ORDERTYPERESERVATIONCONFIG.RESERVEDSTOCKONLY,\
        ORDERTYPERESERVATIONCONFIG.FREESTOCKHASPRIORITY
#define ORDERTYPERESERVATIONCONFIG_LISTE_390 \
        ID,\
        PRIORITY,\
        CSCORDERTYPE,\
        ORDERTYPERESERVATIONCONFIGNAME,\
        CSCRESERVATIONTYPE,\
        RESERVEDSTOCKONLY,\
        FREESTOCKHASPRIORITY
#define ORDERTYPERESERVATIONCONFIG_PLISTE \
        "ORDERTYPERESERVATIONCONFIG.ID,"\
        "ORDERTYPERESERVATIONCONFIG.PRIORITY,"\
        "ORDERTYPERESERVATIONCONFIG.CSCORDERTYPE,"\
        "ORDERTYPERESERVATIONCONFIG.ORDERTYPERESERVATIONCONFIGNAME,"\
        "ORDERTYPERESERVATIONCONFIG.CSCRESERVATIONTYPE,"\
        "ORDERTYPERESERVATIONCONFIG.RESERVEDSTOCKONLY,"\
        "ORDERTYPERESERVATIONCONFIG.FREESTOCKHASPRIORITY"
#define ORDERTYPERESERVATIONCONFIG_PELISTE \
        "ID,"\
        "PRIORITY,"\
        "CSCORDERTYPE,"\
        "ORDERTYPERESERVATIONCONFIGNAME,"\
        "CSCRESERVATIONTYPE,"\
        "RESERVEDSTOCKONLY,"\
        "FREESTOCKHASPRIORITY"
#define ORDERTYPERESERVATIONCONFIG_UPDLISTE \
        "ID=?,"\
        "PRIORITY=?,"\
        "CSCORDERTYPE=?,"\
        "ORDERTYPERESERVATIONCONFIGNAME=?,"\
        "CSCRESERVATIONTYPE=?,"\
        "RESERVEDSTOCKONLY=?,"\
        "FREESTOCKHASPRIORITY=?"
/* SqlMacros-Define of ORDERTYPERESERVATIONCONFIG *****************************/

#define ORDERTYPERESERVATIONCONFIG_ZEIGER(x) \
        :x->ID,\
        :x->PRIORITY,\
        :x->CSCORDERTYPE,\
        :x->ORDERTYPERESERVATIONCONFIGNAME,\
        :x->CSCRESERVATIONTYPE,\
        :x->RESERVEDSTOCKONLY,\
        :x->FREESTOCKHASPRIORITY
#define ORDERTYPERESERVATIONCONFIG_ZEIGERSEL(x) \
        :x->ID,\
        :x->PRIORITY,\
        :x->CSCORDERTYPE,\
        :x->ORDERTYPERESERVATIONCONFIGNAME,\
        :x->CSCRESERVATIONTYPE,\
        :x->RESERVEDSTOCKONLY,\
        :x->FREESTOCKHASPRIORITY
#define ORDERTYPERESERVATIONCONFIG_UPDATE(x) \
        ORDERTYPERESERVATIONCONFIG.PRIORITY=:x->PRIORITY,\
        ORDERTYPERESERVATIONCONFIG.CSCORDERTYPE=:x->CSCORDERTYPE,\
        ORDERTYPERESERVATIONCONFIG.ORDERTYPERESERVATIONCONFIGNAME=:x->ORDERTYPERESERVATIONCONFIGNAME,\
        ORDERTYPERESERVATIONCONFIG.CSCRESERVATIONTYPE=:x->CSCRESERVATIONTYPE,\
        ORDERTYPERESERVATIONCONFIG.RESERVEDSTOCKONLY=:x->RESERVEDSTOCKONLY,\
        ORDERTYPERESERVATIONCONFIG.FREESTOCKHASPRIORITY=:x->FREESTOCKHASPRIORITY
/* SqlMacros390-Define of ORDERTYPERESERVATIONCONFIG **************************/

#define ORDERTYPERESERVATIONCONFIG_ZEIGER_390 \
        :ID,\
        :PRIORITY,\
        :CSCORDERTYPE,\
        :ORDERTYPERESERVATIONCONFIGNAME,\
        :CSCRESERVATIONTYPE,\
        :RESERVEDSTOCKONLY,\
        :FREESTOCKHASPRIORITY
#define ORDERTYPERESERVATIONCONFIG_UPDATE_390 \
        ID=:ID,\
        PRIORITY=:PRIORITY,\
        CSCORDERTYPE=:CSCORDERTYPE,\
        ORDERTYPERESERVATIONCONFIGNAME=:ORDERTYPERESERVATIONCONFIGNAME,\
        CSCRESERVATIONTYPE=:CSCRESERVATIONTYPE,\
        RESERVEDSTOCKONLY=:RESERVEDSTOCKONLY,\
        FREESTOCKHASPRIORITY=:FREESTOCKHASPRIORITY
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of ORDERTYPERESERVATIONCONFIG ******************************/

#ifndef TRANSCLASS
typedef struct N_ORDERTYPERESERVATIONCONFIG {
    long ID;
    short PRIORITY;
    char CSCORDERTYPE[3];
    char ORDERTYPERESERVATIONCONFIGNAME[31];
    long CSCRESERVATIONTYPE;
    short RESERVEDSTOCKONLY;
    short FREESTOCKHASPRIORITY;
} ordertypereservationconfigS;
#else /* TRANSCLASS */
typedef struct N_ORDERTYPERESERVATIONCONFIG {
    long ID;
    short PRIORITY;
    char CSCORDERTYPE[3];
    char ORDERTYPERESERVATIONCONFIGNAME[31];
    long CSCRESERVATIONTYPE;
    short RESERVEDSTOCKONLY;
    short FREESTOCKHASPRIORITY;

    bool operator == (const N_ORDERTYPERESERVATIONCONFIG& right) const {
        return (
            ID == right.ID &&
            PRIORITY == right.PRIORITY &&
            !strcmp(CSCORDERTYPE, right.CSCORDERTYPE) &&
            !strcmp(ORDERTYPERESERVATIONCONFIGNAME, right.ORDERTYPERESERVATIONCONFIGNAME) &&
            CSCRESERVATIONTYPE == right.CSCRESERVATIONTYPE &&
            RESERVEDSTOCKONLY == right.RESERVEDSTOCKONLY &&
            FREESTOCKHASPRIORITY == right.FREESTOCKHASPRIORITY
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        ID = 0;
        PRIORITY = 0;
        strcpy(CSCORDERTYPE, " " );
        strcpy(ORDERTYPERESERVATIONCONFIGNAME, " " );
        CSCRESERVATIONTYPE = 0;
        RESERVEDSTOCKONLY = 0;
        FREESTOCKHASPRIORITY = 0;
#endif
    }
} ordertypereservationconfigS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ORDERTYPERESERVATIONCONFIG ************************/

struct S_ORDERTYPERESERVATIONCONFIG {
    char ID[11];
    char PRIORITY[7];
    char CSCORDERTYPE[2 + 1];
    char ORDERTYPERESERVATIONCONFIGNAME[30 + 1];
    char CSCRESERVATIONTYPE[11];
    char RESERVEDSTOCKONLY[7];
    char FREESTOCKHASPRIORITY[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ORDERTYPERESERVATIONCONFIG *******/

struct O_ORDERTYPERESERVATIONCONFIG {
    char ID[11];
    char PRIORITY[7];
    char CSCORDERTYPE[2];
    char ORDERTYPERESERVATIONCONFIGNAME[30];
    char CSCRESERVATIONTYPE[11];
    char RESERVEDSTOCKONLY[7];
    char FREESTOCKHASPRIORITY[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ORDERTYPERESERVATIONCONFIG ******************/

struct C_ORDERTYPERESERVATIONCONFIG {
    long ID;
    short PRIORITY;
    char CSCORDERTYPE[3];
    char ORDERTYPERESERVATIONCONFIGNAME[31];
    long CSCRESERVATIONTYPE;
    short RESERVEDSTOCKONLY;
    short FREESTOCKHASPRIORITY;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ORDERTYPERESERVATIONCONFIG ****************/

struct I_ORDERTYPERESERVATIONCONFIG {
    short ID;
    short PRIORITY;
    short CSCORDERTYPE;
    short ORDERTYPERESERVATIONCONFIGNAME;
    short CSCRESERVATIONTYPE;
    short RESERVEDSTOCKONLY;
    short FREESTOCKHASPRIORITY;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ORDERTYPERESERVATIONCONFIG **************************/

#if defined (BUF_DESC)
static struct buf_desc ORDERTYPERESERVATIONCONFIG_BES [] = {
   { TYP_L ,  11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc ORDERTYPERESERVATIONCONFIG_BES [] = {
   { TYP_L ,  11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* description for datatypes of ORDERTYPERESERVATIONCONFIG ********************/

 #define ORDERTYPERESERVATIONCONFIG_S390 \
         long ID; \
         short PRIORITY; \
         char CSCORDERTYPE[3]; \
         char ORDERTYPERESERVATIONCONFIGNAME[31]; \
         long CSCRESERVATIONTYPE; \
         short RESERVEDSTOCKONLY; \
         short FREESTOCKHASPRIORITY; \



/* Copy-Function Struct to single Data ORDERTYPERESERVATIONCONFIG *************/

 #define ORDERTYPERESERVATIONCONFIG_S390_COPY_TO_SINGLE(_x_) \
         ID=_x_->ID;\
         PRIORITY=_x_->PRIORITY;\
          strcpy(CSCORDERTYPE,_x_->CSCORDERTYPE);\
          strcpy(ORDERTYPERESERVATIONCONFIGNAME,_x_->ORDERTYPERESERVATIONCONFIGNAME);\
         CSCRESERVATIONTYPE=_x_->CSCRESERVATIONTYPE;\
         RESERVEDSTOCKONLY=_x_->RESERVEDSTOCKONLY;\
         FREESTOCKHASPRIORITY=_x_->FREESTOCKHASPRIORITY;\

 #define ORDERTYPERESERVATIONCONFIG_S390_COPY_TO_STRUCT(_x_) \
          _x_->ID=ID;\
          _x_->PRIORITY=PRIORITY;\
          strcpy(_x_->CSCORDERTYPE,CSCORDERTYPE);\
          strcpy(_x_->ORDERTYPERESERVATIONCONFIGNAME,ORDERTYPERESERVATIONCONFIGNAME);\
          _x_->CSCRESERVATIONTYPE=CSCRESERVATIONTYPE;\
          _x_->RESERVEDSTOCKONLY=RESERVEDSTOCKONLY;\
          _x_->FREESTOCKHASPRIORITY=FREESTOCKHASPRIORITY;\



/* FunctionNumber-Define of OrderTypeReservationConfig ************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of OrderTypeReservationConfig ********************/


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

class CORDERTYPERESERVATIONCONFIG : public ppDadeVirtual {
public:
    ordertypereservationconfigS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<ordertypereservationconfigS> lst; // class list

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
                     vector< ordertypereservationconfigS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     ordertypereservationconfigS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< ordertypereservationconfigS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<ordertypereservationconfigS>::iterator
                 beginList() { return lst.begin(); }
    vector<ordertypereservationconfigS>::iterator
                 endList  () { return lst.end  (); }

    long         GetId() const { return s.ID; }
    short        GetPriority() const { return s.PRIORITY; }
    const char*  GetCscordertype(ppString & t) const { t = s.CSCORDERTYPE; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetOrdertypereservationconfigname(ppString & t) const { t = s.ORDERTYPERESERVATIONCONFIGNAME; t.erasespace(ppString::END); return t.c_str(); }
    long         GetCscreservationtype() const { return s.CSCRESERVATIONTYPE; }
    short        GetReservedstockonly() const { return s.RESERVEDSTOCKONLY; }
    short        GetFreestockhaspriority() const { return s.FREESTOCKHASPRIORITY; }

    const ordertypereservationconfigS &
                 GetStruct() const { return s; }
    void         SetId(long t) { s.ID = t; }
    void         SetPriority(short t) { s.PRIORITY = t; }
    void         SetCscordertype(const ppString & t) { ppGStrCopy(s.CSCORDERTYPE, t.c_str(), L_ORDERTYPERESERVATIONCONFIG_CSCORDERTYPE); }
    void         SetOrdertypereservationconfigname(const ppString & t) { ppGStrCopy(s.ORDERTYPERESERVATIONCONFIGNAME, t.c_str(), L_ORDERTYPERESERVATIONCONFIG_ORDERTYPERESERVATIONCONFIGNAME); }
    void         SetCscreservationtype(long t) { s.CSCRESERVATIONTYPE = t; }
    void         SetReservedstockonly(short t) { s.RESERVEDSTOCKONLY = t; }
    void         SetFreestockhaspriority(short t) { s.FREESTOCKHASPRIORITY = t; }

    void         SetStruct(const ordertypereservationconfigS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CORDERTYPERESERVATIONCONFIG() {
        ::buf_default((void *)&s, ORDERTYPERESERVATIONCONFIG_BES, ORDERTYPERESERVATIONCONFIG_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CORDERTYPERESERVATIONCONFIG() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, ORDERTYPERESERVATIONCONFIG_BES, ORDERTYPERESERVATIONCONFIG_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, ORDERTYPERESERVATIONCONFIG_BES, (int)ORDERTYPERESERVATIONCONFIG_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, ORDERTYPERESERVATIONCONFIG_BES, (int)ORDERTYPERESERVATIONCONFIG_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_ORDERTYPERESERVATIONCONFIG & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.CSCORDERTYPE);
        ppGStripLast(d.ORDERTYPERESERVATIONCONFIGNAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, ORDERTYPERESERVATIONCONFIG_BES, (int)ORDERTYPERESERVATIONCONFIG_ANZ, error_msg);
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
/* CreateSqlStatement of ORDERTYPERESERVATIONCONFIG ***************************/

 #define ORDERTYPERESERVATIONCONFIG_CREATE(x) EXEC SQL create table x (\
         ID serial not null,\
         PRIORITY smallint default 0 not null,\
         CSCORDERTYPE char(2) default " " not null,\
         ORDERTYPERESERVATIONCONFIGNAME char(30) default " " not null,\
         CSCRESERVATIONTYPE integer default 0 not null,\
         RESERVEDSTOCKONLY smallint default 0 not null,\
         FREESTOCKHASPRIORITY smallint default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of ORDERTYPERESERVATIONCONFIG *************************/

 #define ORDERTYPERESERVATIONCONFIG_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_ordertypereservationconfig_1 on _X_(\
              id ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create unique index i_ordertypereservationconfig_2 on _X_(\
              cscordertype,\
              cscreservationtype,\
              priority ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ORDERTYPERESERVATIONCONFIG *************************/

 #define ORDERTYPERESERVATIONCONFIG_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_ordertypereservationconfig_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_ordertypereservationconfig_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
