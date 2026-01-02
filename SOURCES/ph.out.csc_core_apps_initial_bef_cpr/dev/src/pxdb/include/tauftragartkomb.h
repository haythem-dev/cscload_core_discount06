#ifndef __PP_AUFTRAGARTKOMB_H_
#define __PP_AUFTRAGARTKOMB_H_

/******************************************************************************/
/* c:\temp\auftragartkomb *****************************************************/
/* produced by DADE 6.22.0 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of AUFTRAGARTKOMB ********************************************/

#define L_AUFTRAGARTKOMB_KDAUFTRAGART 2
#define L_AUFTRAGARTKOMB_BUCHART 1
#define L_AUFTRAGARTKOMB_KOART 1
#define L_AUFTRAGARTKOMB_KZSTANDARD 1
#define L_AUFTRAGARTKOMB_TOURID 6
#define L_AUFTRAGARTKOMB_VERTRIEBSZENTRUMNR 6
#define L_AUFTRAGARTKOMB_CALCEXPRESSDELIVERYCHARGE 6

/* Length/Count-Define of AUFTRAGARTKOMB **************************************/

#define LS_AUFTRAGARTKOMB_KDAUFTRAGART 2 + 1
#define LS_AUFTRAGARTKOMB_BUCHART 1 + 1
#define LS_AUFTRAGARTKOMB_KOART 1 + 1
#define LS_AUFTRAGARTKOMB_KZSTANDARD 1 + 1
#define LS_AUFTRAGARTKOMB_TOURID 6 + 1
#define LS_AUFTRAGARTKOMB_VERTRIEBSZENTRUMNR 5 + 1
#define LS_AUFTRAGARTKOMB_CALCEXPRESSDELIVERYCHARGE 5 + 1

#define AUFTRAGARTKOMBKDAUFTRAGART 0
#define AUFTRAGARTKOMBBUCHART 1
#define AUFTRAGARTKOMBKOART 2
#define AUFTRAGARTKOMBKZSTANDARD 3
#define AUFTRAGARTKOMBTOURID 4
#define AUFTRAGARTKOMBVERTRIEBSZENTRUMNR 5
#define AUFTRAGARTKOMBCALCEXPRESSDELIVERYCHARGE 6

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define AUFTRAGARTKOMB_H
#define AUFTRAGARTKOMB_ANZ ( sizeof(AUFTRAGARTKOMB_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of AUFTRAGARTKOMB ************************************************/

#define AUFTRAGARTKOMB_LISTE \
        AUFTRAGARTKOMB.KDAUFTRAGART,\
        AUFTRAGARTKOMB.BUCHART,\
        AUFTRAGARTKOMB.KOART,\
        AUFTRAGARTKOMB.KZSTANDARD,\
        AUFTRAGARTKOMB.TOURID,\
        AUFTRAGARTKOMB.VERTRIEBSZENTRUMNR,\
        AUFTRAGARTKOMB.CALCEXPRESSDELIVERYCHARGE
#define AUFTRAGARTKOMB_LISTE_390 \
        KDAUFTRAGART,\
        BUCHART,\
        KOART,\
        KZSTANDARD,\
        TOURID,\
        VERTRIEBSZENTRUMNR,\
        CALCEXPRESSDELIVERYCHARGE
#define AUFTRAGARTKOMB_PLISTE \
        "AUFTRAGARTKOMB.KDAUFTRAGART,"\
        "AUFTRAGARTKOMB.BUCHART,"\
        "AUFTRAGARTKOMB.KOART,"\
        "AUFTRAGARTKOMB.KZSTANDARD,"\
        "AUFTRAGARTKOMB.TOURID,"\
        "AUFTRAGARTKOMB.VERTRIEBSZENTRUMNR,"\
        "AUFTRAGARTKOMB.CALCEXPRESSDELIVERYCHARGE"
#define AUFTRAGARTKOMB_PELISTE \
        "KDAUFTRAGART,"\
        "BUCHART,"\
        "KOART,"\
        "KZSTANDARD,"\
        "TOURID,"\
        "VERTRIEBSZENTRUMNR,"\
        "CALCEXPRESSDELIVERYCHARGE"
#define AUFTRAGARTKOMB_UPDLISTE \
        "KDAUFTRAGART=?,"\
        "BUCHART=?,"\
        "KOART=?,"\
        "KZSTANDARD=?,"\
        "TOURID=?,"\
        "VERTRIEBSZENTRUMNR=?,"\
        "CALCEXPRESSDELIVERYCHARGE=?"
/* SqlMacros-Define of AUFTRAGARTKOMB *****************************************/

#define AUFTRAGARTKOMB_ZEIGER(x) \
        :x->KDAUFTRAGART,\
        :x->BUCHART,\
        :x->KOART,\
        :x->KZSTANDARD,\
        :x->TOURID,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->CALCEXPRESSDELIVERYCHARGE
#define AUFTRAGARTKOMB_ZEIGERSEL(x) \
        :x->KDAUFTRAGART,\
        :x->BUCHART,\
        :x->KOART,\
        :x->KZSTANDARD,\
        :x->TOURID,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->CALCEXPRESSDELIVERYCHARGE
#define AUFTRAGARTKOMB_UPDATE(x) \
        AUFTRAGARTKOMB.KDAUFTRAGART=:x->KDAUFTRAGART,\
        AUFTRAGARTKOMB.BUCHART=:x->BUCHART,\
        AUFTRAGARTKOMB.KOART=:x->KOART,\
        AUFTRAGARTKOMB.KZSTANDARD=:x->KZSTANDARD,\
        AUFTRAGARTKOMB.TOURID=:x->TOURID,\
        AUFTRAGARTKOMB.VERTRIEBSZENTRUMNR=:x->VERTRIEBSZENTRUMNR,\
        AUFTRAGARTKOMB.CALCEXPRESSDELIVERYCHARGE=:x->CALCEXPRESSDELIVERYCHARGE
/* SqlMacros390-Define of AUFTRAGARTKOMB **************************************/

#define AUFTRAGARTKOMB_ZEIGER_390 \
        :KDAUFTRAGART,\
        :BUCHART,\
        :KOART,\
        :KZSTANDARD,\
        :TOURID,\
        :VERTRIEBSZENTRUMNR,\
        :CALCEXPRESSDELIVERYCHARGE
#define AUFTRAGARTKOMB_UPDATE_390 \
        KDAUFTRAGART=:KDAUFTRAGART,\
        BUCHART=:BUCHART,\
        KOART=:KOART,\
        KZSTANDARD=:KZSTANDARD,\
        TOURID=:TOURID,\
        VERTRIEBSZENTRUMNR=:VERTRIEBSZENTRUMNR,\
        CALCEXPRESSDELIVERYCHARGE=:CALCEXPRESSDELIVERYCHARGE
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of AUFTRAGARTKOMB ******************************************/

#ifndef TRANSCLASS
typedef struct N_AUFTRAGARTKOMB {
    char KDAUFTRAGART[3];
    char BUCHART[2];
    char KOART[2];
    char KZSTANDARD[2];
    char TOURID[7];
    short VERTRIEBSZENTRUMNR;
    short CALCEXPRESSDELIVERYCHARGE;
} auftragartkombS;
#else /* TRANSCLASS */
typedef struct N_AUFTRAGARTKOMB {
    char KDAUFTRAGART[3];
    char BUCHART[2];
    char KOART[2];
    char KZSTANDARD[2];
    char TOURID[7];
    short VERTRIEBSZENTRUMNR;
    short CALCEXPRESSDELIVERYCHARGE;

    bool operator == (const N_AUFTRAGARTKOMB& right) const {
        return (
            !strcmp(KDAUFTRAGART, right.KDAUFTRAGART) &&
            !strcmp(BUCHART, right.BUCHART) &&
            !strcmp(KOART, right.KOART) &&
            !strcmp(KZSTANDARD, right.KZSTANDARD) &&
            !strcmp(TOURID, right.TOURID) &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            CALCEXPRESSDELIVERYCHARGE == right.CALCEXPRESSDELIVERYCHARGE
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        strcpy(KDAUFTRAGART, " " );
        strcpy(BUCHART, " " );
        strcpy(KOART, " " );
        strcpy(KZSTANDARD, " " );
        strcpy(TOURID, " " );
        VERTRIEBSZENTRUMNR = 0;
        CALCEXPRESSDELIVERYCHARGE = 0;
#endif
    }
} auftragartkombS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of AUFTRAGARTKOMB ************************************/

struct S_AUFTRAGARTKOMB {
    char KDAUFTRAGART[2 + 1];
    char BUCHART[1 + 1];
    char KOART[1 + 1];
    char KZSTANDARD[1 + 1];
    char TOURID[6 + 1];
    char VERTRIEBSZENTRUMNR[7];
    char CALCEXPRESSDELIVERYCHARGE[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of AUFTRAGARTKOMB *******************/

struct O_AUFTRAGARTKOMB {
    char KDAUFTRAGART[2];
    char BUCHART[1];
    char KOART[1];
    char KZSTANDARD[1];
    char TOURID[6];
    char VERTRIEBSZENTRUMNR[7];
    char CALCEXPRESSDELIVERYCHARGE[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of AUFTRAGARTKOMB ******************************/

struct C_AUFTRAGARTKOMB {
    char KDAUFTRAGART[3];
    char BUCHART;
    char KOART;
    char KZSTANDARD;
    char TOURID[7];
    short VERTRIEBSZENTRUMNR;
    short CALCEXPRESSDELIVERYCHARGE;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of AUFTRAGARTKOMB ****************************/

struct I_AUFTRAGARTKOMB {
    short KDAUFTRAGART;
    short BUCHART;
    short KOART;
    short KZSTANDARD;
    short TOURID;
    short VERTRIEBSZENTRUMNR;
    short CALCEXPRESSDELIVERYCHARGE;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of AUFTRAGARTKOMB **************************************/

#if defined (BUF_DESC)
static struct buf_desc AUFTRAGARTKOMB_BES [] = {
   { TYP_C, 2, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc AUFTRAGARTKOMB_BES [] = {
   { TYP_C, 2, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* description for datatypes of AUFTRAGARTKOMB ********************************/

 #define AUFTRAGARTKOMB_S390 \
         char KDAUFTRAGART[3]; \
         char BUCHART; \
         char KOART; \
         char KZSTANDARD; \
         char TOURID[7]; \
         short VERTRIEBSZENTRUMNR; \
         short CALCEXPRESSDELIVERYCHARGE; \



/* Copy-Function Struct to single Data AUFTRAGARTKOMB *************************/

 #define AUFTRAGARTKOMB_S390_COPY_TO_SINGLE(_x_) \
          strcpy(KDAUFTRAGART,_x_->KDAUFTRAGART);\
         BUCHART=_x_->BUCHART;\
         KOART=_x_->KOART;\
         KZSTANDARD=_x_->KZSTANDARD;\
          strcpy(TOURID,_x_->TOURID);\
         VERTRIEBSZENTRUMNR=_x_->VERTRIEBSZENTRUMNR;\
         CALCEXPRESSDELIVERYCHARGE=_x_->CALCEXPRESSDELIVERYCHARGE;\

 #define AUFTRAGARTKOMB_S390_COPY_TO_STRUCT(_x_) \
          strcpy(_x_->KDAUFTRAGART,KDAUFTRAGART);\
          _x_->BUCHART=BUCHART;\
          _x_->KOART=KOART;\
          _x_->KZSTANDARD=KZSTANDARD;\
          strcpy(_x_->TOURID,TOURID);\
          _x_->VERTRIEBSZENTRUMNR=VERTRIEBSZENTRUMNR;\
          _x_->CALCEXPRESSDELIVERYCHARGE=CALCEXPRESSDELIVERYCHARGE;\



/* FunctionNumber-Define of auftragartkomb ************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of auftragartkomb ********************************/


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

class CAUFTRAGARTKOMB : public ppDadeVirtual {
public:
    auftragartkombS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<auftragartkombS> lst; // class list

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
                     vector< auftragartkombS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     auftragartkombS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< auftragartkombS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<auftragartkombS>::iterator
                 beginList() { return lst.begin(); }
    vector<auftragartkombS>::iterator
                 endList  () { return lst.end  (); }

    const char*  GetKdauftragart(ppString & t) const { t = s.KDAUFTRAGART; t.erasespace(ppString::END); return t.c_str(); }
    char         GetBuchart() const { return s.BUCHART[0]; }
    char         GetKoart() const { return s.KOART[0]; }
    char         GetKzstandard() const { return s.KZSTANDARD[0]; }
    const char*  GetTourid(ppString & t) const { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    short        GetCalcexpressdeliverycharge() const { return s.CALCEXPRESSDELIVERYCHARGE; }

    const auftragartkombS &
                 GetStruct() const { return s; }
    void         SetKdauftragart(const ppString & t) { ppGStrCopy(s.KDAUFTRAGART, t.c_str(), L_AUFTRAGARTKOMB_KDAUFTRAGART); }
    void         SetBuchart(char t) { s.BUCHART[0] = t; s.BUCHART[1] = '\0';}
    void         SetKoart(char t) { s.KOART[0] = t; s.KOART[1] = '\0';}
    void         SetKzstandard(char t) { s.KZSTANDARD[0] = t; s.KZSTANDARD[1] = '\0';}
    void         SetTourid(const ppString & t) { ppGStrCopy(s.TOURID, t.c_str(), L_AUFTRAGARTKOMB_TOURID); }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetCalcexpressdeliverycharge(short t) { s.CALCEXPRESSDELIVERYCHARGE = t; }

    void         SetStruct(const auftragartkombS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CAUFTRAGARTKOMB() {
        ::buf_default((void *)&s, AUFTRAGARTKOMB_BES, AUFTRAGARTKOMB_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CAUFTRAGARTKOMB() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, AUFTRAGARTKOMB_BES, AUFTRAGARTKOMB_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, AUFTRAGARTKOMB_BES, (int)AUFTRAGARTKOMB_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, AUFTRAGARTKOMB_BES, (int)AUFTRAGARTKOMB_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_AUFTRAGARTKOMB & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.KDAUFTRAGART);
        ppGStripLast(d.TOURID);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, AUFTRAGARTKOMB_BES, (int)AUFTRAGARTKOMB_ANZ, error_msg);
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
/* CreateSqlStatement of AUFTRAGARTKOMB ***************************************/

 #define AUFTRAGARTKOMB_CREATE(x) EXEC SQL create table x (\
         KDAUFTRAGART char(2) default " " not null,\
         BUCHART char(1) default " " not null,\
         KOART char(1) default " " not null,\
         KZSTANDARD char(1) default " " not null,\
         TOURID char(6) default " " not null,\
         VERTRIEBSZENTRUMNR smallint default 0 not null,\
         CALCEXPRESSDELIVERYCHARGE smallint default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of AUFTRAGARTKOMB *************************************/

 #define AUFTRAGARTKOMB_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_auftragartkomb_1 on _X_(\
              kdauftragart,\
              buchart,\
              koart,\
              VertriebszentrumNr ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of AUFTRAGARTKOMB *************************************/

 #define AUFTRAGARTKOMB_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_auftragartkomb_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
