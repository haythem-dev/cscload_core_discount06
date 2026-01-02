#ifndef __PP_ORDERTYPERESERVATIONCONFIGCPG_H_
#define __PP_ORDERTYPERESERVATIONCONFIGCPG_H_

/******************************************************************************/
/* c:\prri\Headerfiles\OrderTypeReservationConfigCPG **************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of ORDERTYPERESERVATIONCONFIGCPG *****************************/

#define L_ORDERTYPERESERVATIONCONFIGCPG_ID 11
#define L_ORDERTYPERESERVATIONCONFIGCPG_PHARMACYGROUPID 3
#define L_ORDERTYPERESERVATIONCONFIGCPG_ORDERTYPERESERVATIONCONFIG_ID 11

/* Length/Count-Define of ORDERTYPERESERVATIONCONFIGCPG ***********************/

#define LS_ORDERTYPERESERVATIONCONFIGCPG_ID 10 + 1
#define LS_ORDERTYPERESERVATIONCONFIGCPG_PHARMACYGROUPID 3 + 1
#define LS_ORDERTYPERESERVATIONCONFIGCPG_ORDERTYPERESERVATIONCONFIG_ID 10 + 1

#define ORDERTYPERESERVATIONCONFIGCPGID 0
#define ORDERTYPERESERVATIONCONFIGCPGPHARMACYGROUPID 1
#define ORDERTYPERESERVATIONCONFIGCPGORDERTYPERESERVATIONCONFIG_ID 2

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define ORDERTYPERESERVATIONCONFIGCPG_H
#define ORDERTYPERESERVATIONCONFIGCPG_ANZ ( sizeof(ORDERTYPERESERVATIONCONFIGCPG_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ORDERTYPERESERVATIONCONFIGCPG *********************************/

#define ORDERTYPERESERVATIONCONFIGCPG_LISTE \
        ORDERTYPERESERVATIONCONFIGCPG.ID,\
        ORDERTYPERESERVATIONCONFIGCPG.PHARMACYGROUPID,\
        ORDERTYPERESERVATIONCONFIGCPG.ORDERTYPERESERVATIONCONFIG_ID
#define ORDERTYPERESERVATIONCONFIGCPG_LISTE_390 \
        ID,\
        PHARMACYGROUPID,\
        ORDERTYPERESERVATIONCONFIG_ID
#define ORDERTYPERESERVATIONCONFIGCPG_PLISTE \
        "ORDERTYPERESERVATIONCONFIGCPG.ID,"\
        "ORDERTYPERESERVATIONCONFIGCPG.PHARMACYGROUPID,"\
        "ORDERTYPERESERVATIONCONFIGCPG.ORDERTYPERESERVATIONCONFIG_ID"
#define ORDERTYPERESERVATIONCONFIGCPG_PELISTE \
        "ID,"\
        "PHARMACYGROUPID,"\
        "ORDERTYPERESERVATIONCONFIG_ID"
#define ORDERTYPERESERVATIONCONFIGCPG_UPDLISTE \
        "ID=?,"\
        "PHARMACYGROUPID=?,"\
        "ORDERTYPERESERVATIONCONFIG_ID=?"
/* SqlMacros-Define of ORDERTYPERESERVATIONCONFIGCPG **************************/

#define ORDERTYPERESERVATIONCONFIGCPG_ZEIGER(x) \
        :x->ID,\
        :x->PHARMACYGROUPID,\
        :x->ORDERTYPERESERVATIONCONFIG_ID
#define ORDERTYPERESERVATIONCONFIGCPG_ZEIGERSEL(x) \
        :x->ID,\
        :x->PHARMACYGROUPID,\
        :x->ORDERTYPERESERVATIONCONFIG_ID
#define ORDERTYPERESERVATIONCONFIGCPG_UPDATE(x) \
        ORDERTYPERESERVATIONCONFIGCPG.PHARMACYGROUPID=:x->PHARMACYGROUPID,\
        ORDERTYPERESERVATIONCONFIGCPG.ORDERTYPERESERVATIONCONFIG_ID=:x->ORDERTYPERESERVATIONCONFIG_ID
/* SqlMacros390-Define of ORDERTYPERESERVATIONCONFIGCPG ***********************/

#define ORDERTYPERESERVATIONCONFIGCPG_ZEIGER_390 \
        :ID,\
        :PHARMACYGROUPID,\
        :ORDERTYPERESERVATIONCONFIG_ID
#define ORDERTYPERESERVATIONCONFIGCPG_UPDATE_390 \
        ID=:ID,\
        PHARMACYGROUPID=:PHARMACYGROUPID,\
        ORDERTYPERESERVATIONCONFIG_ID=:ORDERTYPERESERVATIONCONFIG_ID
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of ORDERTYPERESERVATIONCONFIGCPG ***************************/

#ifndef TRANSCLASS
typedef struct N_ORDERTYPERESERVATIONCONFIGCPG {
    long ID;
    char PHARMACYGROUPID[4];
    long ORDERTYPERESERVATIONCONFIG_ID;
} ordertypereservationconfigcpgS;
#else /* TRANSCLASS */
typedef struct N_ORDERTYPERESERVATIONCONFIGCPG {
    long ID;
    char PHARMACYGROUPID[4];
    long ORDERTYPERESERVATIONCONFIG_ID;

    bool operator == (const N_ORDERTYPERESERVATIONCONFIGCPG& right) const {
        return (
            ID == right.ID &&
            !strcmp(PHARMACYGROUPID, right.PHARMACYGROUPID) &&
            ORDERTYPERESERVATIONCONFIG_ID == right.ORDERTYPERESERVATIONCONFIG_ID
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        ID = 0;
        strcpy(PHARMACYGROUPID, " " );
        ORDERTYPERESERVATIONCONFIG_ID = 0;
#endif
    }
} ordertypereservationconfigcpgS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ORDERTYPERESERVATIONCONFIGCPG *********************/

struct S_ORDERTYPERESERVATIONCONFIGCPG {
    char ID[11];
    char PHARMACYGROUPID[3 + 1];
    char ORDERTYPERESERVATIONCONFIG_ID[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ORDERTYPERESERVATIONCONFIGCPG ****/

struct O_ORDERTYPERESERVATIONCONFIGCPG {
    char ID[11];
    char PHARMACYGROUPID[3];
    char ORDERTYPERESERVATIONCONFIG_ID[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ORDERTYPERESERVATIONCONFIGCPG ***************/

struct C_ORDERTYPERESERVATIONCONFIGCPG {
    long ID;
    char PHARMACYGROUPID[4];
    long ORDERTYPERESERVATIONCONFIG_ID;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ORDERTYPERESERVATIONCONFIGCPG *************/

struct I_ORDERTYPERESERVATIONCONFIGCPG {
    short ID;
    short PHARMACYGROUPID;
    short ORDERTYPERESERVATIONCONFIG_ID;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ORDERTYPERESERVATIONCONFIGCPG ***********************/

#if defined (BUF_DESC)
static struct buf_desc ORDERTYPERESERVATIONCONFIGCPG_BES [] = {
   { TYP_L ,  11, 0 },
   { TYP_C, 3, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc ORDERTYPERESERVATIONCONFIGCPG_BES [] = {
   { TYP_L ,  11, 0 },
   { TYP_C, 3, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* description for datatypes of ORDERTYPERESERVATIONCONFIGCPG *****************/

 #define ORDERTYPERESERVATIONCONFIGCPG_S390 \
         long ID; \
         char PHARMACYGROUPID[4]; \
         long ORDERTYPERESERVATIONCONFIG_ID; \



/* Copy-Function Struct to single Data ORDERTYPERESERVATIONCONFIGCPG **********/

 #define ORDERTYPERESERVATIONCONFIGCPG_S390_COPY_TO_SINGLE(_x_) \
         ID=_x_->ID;\
          strcpy(PHARMACYGROUPID,_x_->PHARMACYGROUPID);\
         ORDERTYPERESERVATIONCONFIG_ID=_x_->ORDERTYPERESERVATIONCONFIG_ID;\

 #define ORDERTYPERESERVATIONCONFIGCPG_S390_COPY_TO_STRUCT(_x_) \
          _x_->ID=ID;\
          strcpy(_x_->PHARMACYGROUPID,PHARMACYGROUPID);\
          _x_->ORDERTYPERESERVATIONCONFIG_ID=ORDERTYPERESERVATIONCONFIG_ID;\



/* FunctionNumber-Define of OrderTypeReservationConfigCPG *********************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of OrderTypeReservationConfigCPG *****************/


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

class CORDERTYPERESERVATIONCONFIGCPG : public ppDadeVirtual {
public:
    ordertypereservationconfigcpgS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<ordertypereservationconfigcpgS> lst; // class list

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
                     vector< ordertypereservationconfigcpgS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     ordertypereservationconfigcpgS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< ordertypereservationconfigcpgS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<ordertypereservationconfigcpgS>::iterator
                 beginList() { return lst.begin(); }
    vector<ordertypereservationconfigcpgS>::iterator
                 endList  () { return lst.end  (); }

    long         GetId() const { return s.ID; }
    const char*  GetPharmacygroupid(ppString & t) const { t = s.PHARMACYGROUPID; t.erasespace(ppString::END); return t.c_str(); }
    long         GetOrdertypereservationconfig_id() const { return s.ORDERTYPERESERVATIONCONFIG_ID; }

    const ordertypereservationconfigcpgS &
                 GetStruct() const { return s; }
    void         SetId(long t) { s.ID = t; }
    void         SetPharmacygroupid(const ppString & t) { ppGStrCopy(s.PHARMACYGROUPID, t.c_str(), L_ORDERTYPERESERVATIONCONFIGCPG_PHARMACYGROUPID); }
    void         SetOrdertypereservationconfig_id(long t) { s.ORDERTYPERESERVATIONCONFIG_ID = t; }

    void         SetStruct(const ordertypereservationconfigcpgS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CORDERTYPERESERVATIONCONFIGCPG() {
        ::buf_default((void *)&s, ORDERTYPERESERVATIONCONFIGCPG_BES, ORDERTYPERESERVATIONCONFIGCPG_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CORDERTYPERESERVATIONCONFIGCPG() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, ORDERTYPERESERVATIONCONFIGCPG_BES, ORDERTYPERESERVATIONCONFIGCPG_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, ORDERTYPERESERVATIONCONFIGCPG_BES, (int)ORDERTYPERESERVATIONCONFIGCPG_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, ORDERTYPERESERVATIONCONFIGCPG_BES, (int)ORDERTYPERESERVATIONCONFIGCPG_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_ORDERTYPERESERVATIONCONFIGCPG & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.PHARMACYGROUPID);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, ORDERTYPERESERVATIONCONFIGCPG_BES, (int)ORDERTYPERESERVATIONCONFIGCPG_ANZ, error_msg);
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
/* CreateSqlStatement of ORDERTYPERESERVATIONCONFIGCPG ************************/

 #define ORDERTYPERESERVATIONCONFIGCPG_CREATE(x) EXEC SQL create table x (\
         ID serial not null,\
         PHARMACYGROUPID char(3) default " " not null,\
         ORDERTYPERESERVATIONCONFIG_ID integer default 0 not null) in ksc extent size 80 next size 8 lock mode row;



/* CreateIndexStatement of ORDERTYPERESERVATIONCONFIGCPG **********************/

 #define ORDERTYPERESERVATIONCONFIGCPG_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_ordertypereservationconfigcpg_1 on _X_(\
              id ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index i_ordertypereservationconfigcpg_2 on _X_(\
              OrderTypeReservationConfig_ID ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ORDERTYPERESERVATIONCONFIGCPG **********************/

 #define ORDERTYPERESERVATIONCONFIGCPG_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_ordertypereservationconfigcpg_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_ordertypereservationconfigcpg_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
