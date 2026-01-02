#ifndef __PP_NRECHNER_H_
#define __PP_NRECHNER_H_

/******************************************************************************/
/* c:\tmp\nRechner ************************************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of NRECHNER **************************************************/

#define L_NRECHNER_FILIALNR 6
#define L_NRECHNER_RECHNER_NAME 7
#define L_NRECHNER_STANDORT 15
#define L_NRECHNER_PFLEGE 1
#define L_NRECHNER_DATENBANK_NAME 35
#define L_NRECHNER_SZENTRAL 1
#define L_NRECHNER_WAREHOUSE_DATENBANKNAME 35
#define L_NRECHNER_INBOUND_DATENBANKNAME 35

/* Length/Count-Define of NRECHNER ********************************************/

#define LS_NRECHNER_FILIALNR 5 + 1
#define LS_NRECHNER_RECHNER_NAME 7 + 1
#define LS_NRECHNER_STANDORT 15 + 1
#define LS_NRECHNER_PFLEGE 1 + 1
#define LS_NRECHNER_DATENBANK_NAME 35 + 1
#define LS_NRECHNER_SZENTRAL 1 + 1
#define LS_NRECHNER_WAREHOUSE_DATENBANKNAME 35 + 1
#define LS_NRECHNER_INBOUND_DATENBANKNAME 35 + 1

#define NRECHNERFILIALNR 0
#define NRECHNERRECHNER_NAME 1
#define NRECHNERSTANDORT 2
#define NRECHNERPFLEGE 3
#define NRECHNERDATENBANK_NAME 4
#define NRECHNERSZENTRAL 5
#define NRECHNERWAREHOUSE_DATENBANKNAME 6
#define NRECHNERINBOUND_DATENBANKNAME 7

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define NRECHNER_H
#define NRECHNER_ANZ ( sizeof(NRECHNER_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of NRECHNER ******************************************************/

#define NRECHNER_LISTE \
        RECHNER.FILIALNR,\
        RECHNER.RECHNER_NAME,\
        RECHNER.STANDORT,\
        RECHNER.PFLEGE,\
        RECHNER.DATENBANK_NAME,\
        RECHNER.SZENTRAL,\
        RECHNER.WAREHOUSE_DATENBANKNAME,\
        RECHNER.INBOUND_DATENBANKNAME
#define NRECHNER_LISTE_390 \
        FILIALNR,\
        RECHNER_NAME,\
        STANDORT,\
        PFLEGE,\
        DATENBANK_NAME,\
        SZENTRAL,\
        WAREHOUSE_DATENBANKNAME,\
        INBOUND_DATENBANKNAME
#define NRECHNER_PLISTE \
        "RECHNER.FILIALNR,"\
        "RECHNER.RECHNER_NAME,"\
        "RECHNER.STANDORT,"\
        "RECHNER.PFLEGE,"\
        "RECHNER.DATENBANK_NAME,"\
        "RECHNER.SZENTRAL,"\
        "RECHNER.WAREHOUSE_DATENBANKNAME,"\
        "RECHNER.INBOUND_DATENBANKNAME"
#define NRECHNER_PELISTE \
        "FILIALNR,"\
        "RECHNER_NAME,"\
        "STANDORT,"\
        "PFLEGE,"\
        "DATENBANK_NAME,"\
        "SZENTRAL,"\
        "WAREHOUSE_DATENBANKNAME,"\
        "INBOUND_DATENBANKNAME"
#define NRECHNER_UPDLISTE \
        "FILIALNR=?,"\
        "RECHNER_NAME=?,"\
        "STANDORT=?,"\
        "PFLEGE=?,"\
        "DATENBANK_NAME=?,"\
        "SZENTRAL=?,"\
        "WAREHOUSE_DATENBANKNAME=?,"\
        "INBOUND_DATENBANKNAME=?"
/* SqlMacros-Define of NRECHNER ***********************************************/

#define NRECHNER_ZEIGER(x) \
        :x->FILIALNR,\
        :x->RECHNER_NAME,\
        :x->STANDORT,\
        :x->PFLEGE,\
        :x->DATENBANK_NAME,\
        :x->SZENTRAL,\
        :x->WAREHOUSE_DATENBANKNAME,\
        :x->INBOUND_DATENBANKNAME
#define NRECHNER_ZEIGERSEL(x) \
        :x->FILIALNR,\
        :x->RECHNER_NAME,\
        :x->STANDORT,\
        :x->PFLEGE,\
        :x->DATENBANK_NAME,\
        :x->SZENTRAL,\
        :x->WAREHOUSE_DATENBANKNAME,\
        :x->INBOUND_DATENBANKNAME
#define NRECHNER_UPDATE(x) \
        RECHNER.FILIALNR=:x->FILIALNR,\
        RECHNER.RECHNER_NAME=:x->RECHNER_NAME,\
        RECHNER.STANDORT=:x->STANDORT,\
        RECHNER.PFLEGE=:x->PFLEGE,\
        RECHNER.DATENBANK_NAME=:x->DATENBANK_NAME,\
        RECHNER.SZENTRAL=:x->SZENTRAL,\
        RECHNER.WAREHOUSE_DATENBANKNAME=:x->WAREHOUSE_DATENBANKNAME,\
        RECHNER.INBOUND_DATENBANKNAME=:x->INBOUND_DATENBANKNAME
/* SqlMacros390-Define of NRECHNER ********************************************/

#define NRECHNER_ZEIGER_390 \
        :FILIALNR,\
        :RECHNER_NAME,\
        :STANDORT,\
        :PFLEGE,\
        :DATENBANK_NAME,\
        :SZENTRAL,\
        :WAREHOUSE_DATENBANKNAME,\
        :INBOUND_DATENBANKNAME
#define NRECHNER_UPDATE_390 \
        FILIALNR=:FILIALNR,\
        RECHNER_NAME=:RECHNER_NAME,\
        STANDORT=:STANDORT,\
        PFLEGE=:PFLEGE,\
        DATENBANK_NAME=:DATENBANK_NAME,\
        SZENTRAL=:SZENTRAL,\
        WAREHOUSE_DATENBANKNAME=:WAREHOUSE_DATENBANKNAME,\
        INBOUND_DATENBANKNAME=:INBOUND_DATENBANKNAME
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of NRECHNER ************************************************/

#ifndef TRANSCLASS
typedef struct N_NRECHNER {
    short FILIALNR;
    char RECHNER_NAME[8];
    char STANDORT[16];
    char PFLEGE[2];
    char DATENBANK_NAME[36];
    char SZENTRAL[2];
    char WAREHOUSE_DATENBANKNAME[36];
    char INBOUND_DATENBANKNAME[36];
} nrechnerS;
#else /* TRANSCLASS */
typedef struct N_NRECHNER {
    short FILIALNR;
    char RECHNER_NAME[8];
    char STANDORT[16];
    char PFLEGE[2];
    char DATENBANK_NAME[36];
    char SZENTRAL[2];
    char WAREHOUSE_DATENBANKNAME[36];
    char INBOUND_DATENBANKNAME[36];

    bool operator == (const N_NRECHNER& right) const {
        return (
            FILIALNR == right.FILIALNR &&
            !strcmp(RECHNER_NAME, right.RECHNER_NAME) &&
            !strcmp(STANDORT, right.STANDORT) &&
            !strcmp(PFLEGE, right.PFLEGE) &&
            !strcmp(DATENBANK_NAME, right.DATENBANK_NAME) &&
            !strcmp(SZENTRAL, right.SZENTRAL) &&
            !strcmp(WAREHOUSE_DATENBANKNAME, right.WAREHOUSE_DATENBANKNAME) &&
            !strcmp(INBOUND_DATENBANKNAME, right.INBOUND_DATENBANKNAME)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        FILIALNR = 0;
        strcpy(RECHNER_NAME, " " );
        strcpy(STANDORT, " " );
        strcpy(PFLEGE, " " );
        strcpy(DATENBANK_NAME, " " );
        strcpy(SZENTRAL, " " );
        strcpy(WAREHOUSE_DATENBANKNAME, " " );
        strcpy(INBOUND_DATENBANKNAME, " " );
#endif
    }
} nrechnerS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of NRECHNER ******************************************/

struct S_NRECHNER {
    char FILIALNR[7];
    char RECHNER_NAME[7 + 1];
    char STANDORT[15 + 1];
    char PFLEGE[1 + 1];
    char DATENBANK_NAME[35 + 1];
    char SZENTRAL[1 + 1];
    char WAREHOUSE_DATENBANKNAME[35 + 1];
    char INBOUND_DATENBANKNAME[35 + 1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of NRECHNER *************************/

struct O_NRECHNER {
    char FILIALNR[7];
    char RECHNER_NAME[7];
    char STANDORT[15];
    char PFLEGE[1];
    char DATENBANK_NAME[35];
    char SZENTRAL[1];
    char WAREHOUSE_DATENBANKNAME[35];
    char INBOUND_DATENBANKNAME[35];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of NRECHNER ************************************/

struct C_NRECHNER {
    short FILIALNR;
    char RECHNER_NAME[8];
    char STANDORT[16];
    char PFLEGE;
    char DATENBANK_NAME[36];
    char SZENTRAL;
    char WAREHOUSE_DATENBANKNAME[36];
    char INBOUND_DATENBANKNAME[36];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of NRECHNER **********************************/

struct I_NRECHNER {
    short FILIALNR;
    short RECHNER_NAME;
    short STANDORT;
    short PFLEGE;
    short DATENBANK_NAME;
    short SZENTRAL;
    short WAREHOUSE_DATENBANKNAME;
    short INBOUND_DATENBANKNAME;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of NRECHNER ********************************************/

#if defined (BUF_DESC)
static struct buf_desc NRECHNER_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 7, 0 },
   { TYP_C, 15, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 35, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 35, 0 },
   { TYP_C, 35, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc NRECHNER_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 7, 0 },
   { TYP_C, 15, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 35, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 35, 0 },
   { TYP_C, 35, 0 },
};
#endif

/* description for datatypes of NRECHNER **************************************/

 #define NRECHNER_S390 \
         short FILIALNR; \
         char RECHNER_NAME[8]; \
         char STANDORT[16]; \
         char PFLEGE; \
         char DATENBANK_NAME[36]; \
         char SZENTRAL; \
         char WAREHOUSE_DATENBANKNAME[36]; \
         char INBOUND_DATENBANKNAME[36]; \



/* Copy-Function Struct to single Data NRECHNER *******************************/

 #define NRECHNER_S390_COPY_TO_SINGLE(_x_) \
         FILIALNR=_x_->FILIALNR;\
          strcpy(RECHNER_NAME,_x_->RECHNER_NAME);\
          strcpy(STANDORT,_x_->STANDORT);\
         PFLEGE=_x_->PFLEGE;\
          strcpy(DATENBANK_NAME,_x_->DATENBANK_NAME);\
         SZENTRAL=_x_->SZENTRAL;\
          strcpy(WAREHOUSE_DATENBANKNAME,_x_->WAREHOUSE_DATENBANKNAME);\
          strcpy(INBOUND_DATENBANKNAME,_x_->INBOUND_DATENBANKNAME);\

 #define NRECHNER_S390_COPY_TO_STRUCT(_x_) \
          _x_->FILIALNR=FILIALNR;\
          strcpy(_x_->RECHNER_NAME,RECHNER_NAME);\
          strcpy(_x_->STANDORT,STANDORT);\
          _x_->PFLEGE=PFLEGE;\
          strcpy(_x_->DATENBANK_NAME,DATENBANK_NAME);\
          _x_->SZENTRAL=SZENTRAL;\
          strcpy(_x_->WAREHOUSE_DATENBANKNAME,WAREHOUSE_DATENBANKNAME);\
          strcpy(_x_->INBOUND_DATENBANKNAME,INBOUND_DATENBANKNAME);\



/* FunctionNumber-Define of nRechner ******************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of nRechner **************************************/


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

class CNRECHNER : public ppDadeVirtual {
public:
    nrechnerS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<nrechnerS> lst; // class list

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
                     vector< nrechnerS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     nrechnerS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< nrechnerS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<nrechnerS>::iterator
                 beginList() { return lst.begin(); }
    vector<nrechnerS>::iterator
                 endList  () { return lst.end  (); }

    short        GetFilialnr() const { return s.FILIALNR; }
    const char*  GetRechner_name(ppString & t) const { t = s.RECHNER_NAME; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetStandort(ppString & t) const { t = s.STANDORT; t.erasespace(ppString::END); return t.c_str(); }
    char         GetPflege() const { return s.PFLEGE[0]; }
    const char*  GetDatenbank_name(ppString & t) const { t = s.DATENBANK_NAME; t.erasespace(ppString::END); return t.c_str(); }
    char         GetSzentral() const { return s.SZENTRAL[0]; }
    const char*  GetWarehouse_datenbankname(ppString & t) const { t = s.WAREHOUSE_DATENBANKNAME; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetInbound_datenbankname(ppString & t) const { t = s.INBOUND_DATENBANKNAME; t.erasespace(ppString::END); return t.c_str(); }

    const nrechnerS &
                 GetStruct() const { return s; }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetRechner_name(const ppString & t) { ppGStrCopy(s.RECHNER_NAME, t.c_str(), L_NRECHNER_RECHNER_NAME); }
    void         SetStandort(const ppString & t) { ppGStrCopy(s.STANDORT, t.c_str(), L_NRECHNER_STANDORT); }
    void         SetPflege(char t) { s.PFLEGE[0] = t; s.PFLEGE[1] = '\0';}
    void         SetDatenbank_name(const ppString & t) { ppGStrCopy(s.DATENBANK_NAME, t.c_str(), L_NRECHNER_DATENBANK_NAME); }
    void         SetSzentral(char t) { s.SZENTRAL[0] = t; s.SZENTRAL[1] = '\0';}
    void         SetWarehouse_datenbankname(const ppString & t) { ppGStrCopy(s.WAREHOUSE_DATENBANKNAME, t.c_str(), L_NRECHNER_WAREHOUSE_DATENBANKNAME); }
    void         SetInbound_datenbankname(const ppString & t) { ppGStrCopy(s.INBOUND_DATENBANKNAME, t.c_str(), L_NRECHNER_INBOUND_DATENBANKNAME); }

    void         SetStruct(const nrechnerS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CNRECHNER() {
        ::buf_default((void *)&s, NRECHNER_BES, NRECHNER_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CNRECHNER() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, NRECHNER_BES, NRECHNER_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, NRECHNER_BES, (int)NRECHNER_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, NRECHNER_BES, (int)NRECHNER_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_NRECHNER & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.RECHNER_NAME);
        ppGStripLast(d.STANDORT);
        ppGStripLast(d.DATENBANK_NAME);
        ppGStripLast(d.WAREHOUSE_DATENBANKNAME);
        ppGStripLast(d.INBOUND_DATENBANKNAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, NRECHNER_BES, (int)NRECHNER_ANZ, error_msg);
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
/* CreateSqlStatement of NRECHNER *********************************************/

 #define NRECHNER_CREATE(x) EXEC SQL create table x (\
         FILIALNR smallint default 0 not null,\
         RECHNER_NAME char(7) default " " not null,\
         STANDORT char(15) default " " not null,\
         PFLEGE char(1) default " " not null,\
         DATENBANK_NAME char(35) default " " not null,\
         SZENTRAL char(1) default " " not null,\
         WAREHOUSE_DATENBANKNAME char(35) default " " not null,\
         INBOUND_DATENBANKNAME char(35) default " " not null) extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of NRECHNER *******************************************/

 #define NRECHNER_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_rechner_1 on _X_(\
              filialnr );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create unique index i_rechner_2 on _X_(\
              rechner_name );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of NRECHNER *******************************************/

 #define NRECHNER_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_rechner_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_rechner_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
