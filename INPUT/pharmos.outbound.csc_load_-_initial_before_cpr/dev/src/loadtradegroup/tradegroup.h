#ifndef __PP_TRADEGROUP_H_
#define __PP_TRADEGROUP_H_

/******************************************************************************/
/* c:\prri\Headerfiles\tradegroup *********************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of TRADEGROUP ************************************************/

#define L_TRADEGROUP_ARTIKEL_NR 11
#define L_TRADEGROUP_ART 1
#define L_TRADEGROUP_WARENGRUPPE 5

/* Length/Count-Define of TRADEGROUP ******************************************/

#define LS_TRADEGROUP_ARTIKEL_NR 10 + 1
#define LS_TRADEGROUP_ART 1 + 1
#define LS_TRADEGROUP_WARENGRUPPE 5 + 1

#define TRADEGROUPARTIKEL_NR 0
#define TRADEGROUPART 1
#define TRADEGROUPWARENGRUPPE 2

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define TRADEGROUP_H
#define TRADEGROUP_ANZ ( sizeof(TRADEGROUP_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of TRADEGROUP ****************************************************/

#define TRADEGROUP_LISTE \
        ZARTWG.ARTIKEL_NR,\
        ZARTWG.ART,\
        ZARTWG.WARENGRUPPE
#define TRADEGROUP_LISTE_390 \
        ARTIKEL_NR,\
        ART,\
        WARENGRUPPE
#define TRADEGROUP_PLISTE \
        "ZARTWG.ARTIKEL_NR,"\
        "ZARTWG.ART,"\
        "ZARTWG.WARENGRUPPE"
#define TRADEGROUP_PELISTE \
        "ARTIKEL_NR,"\
        "ART,"\
        "WARENGRUPPE"
#define TRADEGROUP_UPDLISTE \
        "ARTIKEL_NR=?,"\
        "ART=?,"\
        "WARENGRUPPE=?"
/* SqlMacros-Define of TRADEGROUP *********************************************/

#define TRADEGROUP_ZEIGER(x) \
        :x->ARTIKEL_NR,\
        :x->ART,\
        :x->WARENGRUPPE
#define TRADEGROUP_ZEIGERSEL(x) \
        :x->ARTIKEL_NR,\
        :x->ART,\
        :x->WARENGRUPPE
#define TRADEGROUP_UPDATE(x) \
        ZARTWG.ARTIKEL_NR=:x->ARTIKEL_NR,\
        ZARTWG.ART=:x->ART,\
        ZARTWG.WARENGRUPPE=:x->WARENGRUPPE
/* SqlMacros390-Define of TRADEGROUP ******************************************/

#define TRADEGROUP_ZEIGER_390 \
        :ARTIKEL_NR,\
        :ART,\
        :WARENGRUPPE
#define TRADEGROUP_UPDATE_390 \
        ARTIKEL_NR=:ARTIKEL_NR,\
        ART=:ART,\
        WARENGRUPPE=:WARENGRUPPE
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of TRADEGROUP **********************************************/

#ifndef TRANSCLASS
typedef struct N_TRADEGROUP {
    long ARTIKEL_NR;
    char ART[2];
    char WARENGRUPPE[6];
} tradegroupS;
#else /* TRANSCLASS */
typedef struct N_TRADEGROUP {
    long ARTIKEL_NR;
    char ART[2];
    char WARENGRUPPE[6];

    bool operator == (const N_TRADEGROUP& right) const {
        return (
            ARTIKEL_NR == right.ARTIKEL_NR &&
            !strcmp(ART, right.ART) &&
            !strcmp(WARENGRUPPE, right.WARENGRUPPE)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        ARTIKEL_NR = 0;
        strcpy(ART, " " );
        strcpy(WARENGRUPPE, " " );
#endif
    }
} tradegroupS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of TRADEGROUP ****************************************/

struct S_TRADEGROUP {
    char ARTIKEL_NR[11];
    char ART[1 + 1];
    char WARENGRUPPE[5 + 1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of TRADEGROUP ***********************/

struct O_TRADEGROUP {
    char ARTIKEL_NR[11];
    char ART[1];
    char WARENGRUPPE[5];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of TRADEGROUP **********************************/

struct C_TRADEGROUP {
    long ARTIKEL_NR;
    char ART;
    char WARENGRUPPE[6];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of TRADEGROUP ********************************/

struct I_TRADEGROUP {
    short ARTIKEL_NR;
    short ART;
    short WARENGRUPPE;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of TRADEGROUP ******************************************/

#if defined (BUF_DESC)
static struct buf_desc TRADEGROUP_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 5, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc TRADEGROUP_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 5, 0 },
};
#endif

/* description for datatypes of TRADEGROUP ************************************/

 #define TRADEGROUP_S390 \
         long ARTIKEL_NR; \
         char ART; \
         char WARENGRUPPE[6]; \



/* Copy-Function Struct to single Data TRADEGROUP *****************************/

 #define TRADEGROUP_S390_COPY_TO_SINGLE(_x_) \
         ARTIKEL_NR=_x_->ARTIKEL_NR;\
         ART=_x_->ART;\
          strcpy(WARENGRUPPE,_x_->WARENGRUPPE);\

 #define TRADEGROUP_S390_COPY_TO_STRUCT(_x_) \
          _x_->ARTIKEL_NR=ARTIKEL_NR;\
          _x_->ART=ART;\
          strcpy(_x_->WARENGRUPPE,WARENGRUPPE);\



/* FunctionNumber-Define of tradegroup ****************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of tradegroup ************************************/


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

class CTRADEGROUP : public ppDadeVirtual {
public:
    tradegroupS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<tradegroupS> lst; // class list

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
                     vector< tradegroupS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     tradegroupS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< tradegroupS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<tradegroupS>::iterator
                 beginList() { return lst.begin(); }
    vector<tradegroupS>::iterator
                 endList  () { return lst.end  (); }

    long         GetArtikel_nr() const { return s.ARTIKEL_NR; }
    char         GetArt() const { return s.ART[0]; }
    const char*  GetWarengruppe(ppString & t) const { t = s.WARENGRUPPE; t.erasespace(ppString::END); return t.c_str(); }

    const tradegroupS &
                 GetStruct() const { return s; }
    void         SetArtikel_nr(long t) { s.ARTIKEL_NR = t; }
    void         SetArt(char t) { s.ART[0] = t; s.ART[1] = '\0';}
    void         SetWarengruppe(const ppString & t) { ppGStrCopy(s.WARENGRUPPE, t.c_str(), L_TRADEGROUP_WARENGRUPPE); }

    void         SetStruct(const tradegroupS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CTRADEGROUP() {
        ::buf_default((void *)&s, TRADEGROUP_BES, TRADEGROUP_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CTRADEGROUP() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, TRADEGROUP_BES, TRADEGROUP_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, TRADEGROUP_BES, (int)TRADEGROUP_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, TRADEGROUP_BES, (int)TRADEGROUP_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_TRADEGROUP & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.WARENGRUPPE);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, TRADEGROUP_BES, (int)TRADEGROUP_ANZ, error_msg);
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
/* CreateSqlStatement of TRADEGROUP *******************************************/

 #define TRADEGROUP_CREATE(x) EXEC SQL create table x (\
         ARTIKEL_NR integer default 0 not null,\
         ART char(1) default " " not null,\
         WARENGRUPPE char(5) default " " not null) extent size 7844 next size 788 lock mode row;



/* CreateIndexStatement of TRADEGROUP *****************************************/

 #define TRADEGROUP_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_zartwg_1 on _X_(\
              artikel_nr,\
              art );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index i_zartwg_3 on _X_(\
              art,\
              warengruppe );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of TRADEGROUP *****************************************/

 #define TRADEGROUP_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_zartwg_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_zartwg_3;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
