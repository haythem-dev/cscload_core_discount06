#ifndef __PP_ORDERVALUES_H_
#define __PP_ORDERVALUES_H_

/******************************************************************************/
/* c:\temp\dade_ae\OrderValues ************************************************/
/* produced by DADE 6.22.1 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of ORDERVALUES ***********************************************/

#define L_ORDERVALUES_TAXLEVEL 6
#define L_ORDERVALUES_SALESTAXRATE 5
#define N_ORDERVALUES_SALESTAXRATE 2
#define L_ORDERVALUES_ORDVALNET 11
#define N_ORDERVALUES_ORDVALNET 2
#define L_ORDERVALUES_ORDVALTAX 11
#define N_ORDERVALUES_ORDVALTAX 2

/* Length/Count-Define of ORDERVALUES *****************************************/

#define LS_ORDERVALUES_TAXLEVEL 5 + 1
#define LS_ORDERVALUES_SALESTAXRATE 5 + 2
#define LS_ORDERVALUES_ORDVALNET 11 + 2
#define LS_ORDERVALUES_ORDVALTAX 11 + 2

#define ORDERVALUESTAXLEVEL 0
#define ORDERVALUESSALESTAXRATE 1
#define ORDERVALUESORDVALNET 2
#define ORDERVALUESORDVALTAX 3

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define ORDERVALUES_H
#define ORDERVALUES_ANZ ( sizeof(ORDERVALUES_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ORDERVALUES ***************************************************/

#define ORDERVALUES_LISTE \
        TAXRATES.TAXLEVEL,\
        TAXRATES.SALESTAXRATE,\
        AADUMMY.ORDVALNET,\
        AADUMMY.ORDVALTAX
#define ORDERVALUES_LISTE_390 \
        TAXLEVEL,\
        SALESTAXRATE,\
        ORDVALNET,\
        ORDVALTAX
#define ORDERVALUES_PLISTE \
        "TAXRATES.TAXLEVEL,"\
        "TAXRATES.SALESTAXRATE,"\
        "AADUMMY.ORDVALNET,"\
        "AADUMMY.ORDVALTAX"
#define ORDERVALUES_PELISTE \
        "TAXLEVEL,"\
        "SALESTAXRATE,"\
        "ORDVALNET,"\
        "ORDVALTAX"
#define ORDERVALUES_UPDLISTE \
        "TAXLEVEL=?,"\
        "SALESTAXRATE=?,"\
        "ORDVALNET=?,"\
        "ORDVALTAX=?"
/* SqlMacros-Define of ORDERVALUES ********************************************/

#define ORDERVALUES_ZEIGER(x) \
        :x->TAXLEVEL,\
        :x->SALESTAXRATE,\
        :x->ORDVALNET,\
        :x->ORDVALTAX
#define ORDERVALUES_ZEIGERSEL(x) \
        :x->TAXLEVEL,\
        :x->SALESTAXRATE,\
        :x->ORDVALNET,\
        :x->ORDVALTAX
#define ORDERVALUES_UPDATE(x) \
        TAXRATES.TAXLEVEL=:x->TAXLEVEL,\
        TAXRATES.SALESTAXRATE=:x->SALESTAXRATE,\
        AADUMMY.ORDVALNET=:x->ORDVALNET,\
        AADUMMY.ORDVALTAX=:x->ORDVALTAX
/* SqlMacros390-Define of ORDERVALUES *****************************************/

#define ORDERVALUES_ZEIGER_390 \
        :TAXLEVEL,\
        :SALESTAXRATE,\
        :ORDVALNET,\
        :ORDVALTAX
#define ORDERVALUES_UPDATE_390 \
        TAXLEVEL=:TAXLEVEL,\
        SALESTAXRATE=:SALESTAXRATE,\
        ORDVALNET=:ORDVALNET,\
        ORDVALTAX=:ORDVALTAX
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of ORDERVALUES *********************************************/

#ifndef TRANSCLASS
typedef struct N_ORDERVALUES {
    short TAXLEVEL;
    double SALESTAXRATE;
    double ORDVALNET;
    double ORDVALTAX;
} ordervaluesS;
#else /* TRANSCLASS */
typedef struct N_ORDERVALUES {
    short TAXLEVEL;
    double SALESTAXRATE;
    double ORDVALNET;
    double ORDVALTAX;

    bool operator == (const N_ORDERVALUES& right) const {
        return (
            TAXLEVEL == right.TAXLEVEL &&
            SALESTAXRATE == right.SALESTAXRATE &&
            ORDVALNET == right.ORDVALNET &&
            ORDVALTAX == right.ORDVALTAX
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        TAXLEVEL = 0;
        SALESTAXRATE = 0;
        ORDVALNET = 0;
        ORDVALTAX = 0;
#endif
    }
} ordervaluesS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ORDERVALUES ***************************************/

struct S_ORDERVALUES {
    char TAXLEVEL[7];
    char SALESTAXRATE[5 + 2];
    char ORDVALNET[11 + 2];
    char ORDVALTAX[11 + 2];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ORDERVALUES **********************/

struct O_ORDERVALUES {
    char TAXLEVEL[7];
    char SALESTAXRATE[5];
    char ORDVALNET[11];
    char ORDVALTAX[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ORDERVALUES *********************************/

struct C_ORDERVALUES {
    short TAXLEVEL;
    double SALESTAXRATE;
    double ORDVALNET;
    double ORDVALTAX;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ORDERVALUES *******************************/

struct I_ORDERVALUES {
    short TAXLEVEL;
    short SALESTAXRATE;
    short ORDVALNET;
    short ORDVALTAX;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ORDERVALUES *****************************************/

#if defined (BUF_DESC)
static struct buf_desc ORDERVALUES_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc ORDERVALUES_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
};
#endif

/* description for datatypes of ORDERVALUES ***********************************/

 #define ORDERVALUES_S390 \
         short TAXLEVEL; \
         double SALESTAXRATE; \
         double ORDVALNET; \
         double ORDVALTAX; \



/* Copy-Function Struct to single Data ORDERVALUES ****************************/

 #define ORDERVALUES_S390_COPY_TO_SINGLE(_x_) \
         TAXLEVEL=_x_->TAXLEVEL;\
         SALESTAXRATE=_x_->SALESTAXRATE;\
         ORDVALNET=_x_->ORDVALNET;\
         ORDVALTAX=_x_->ORDVALTAX;\

 #define ORDERVALUES_S390_COPY_TO_STRUCT(_x_) \
          _x_->TAXLEVEL=TAXLEVEL;\
          _x_->SALESTAXRATE=SALESTAXRATE;\
          _x_->ORDVALNET=ORDVALNET;\
          _x_->ORDVALTAX=ORDVALTAX;\



/* FunctionNumber-Define of OrderValues ***************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of OrderValues ***********************************/


#endif

/* C++ Class ******************************************************************/

#ifdef TRANSCLASS

#include <vector>
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

class CORDERVALUES : public ppDadeVirtual {
public:
    ordervaluesS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<ordervaluesS> lst; // class list

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
                     vector< ordervaluesS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     ordervaluesS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< ordervaluesS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<ordervaluesS>::iterator
                 beginList() { return lst.begin(); }
    vector<ordervaluesS>::iterator
                 endList  () { return lst.end  (); }

    short        GetTaxlevel() const { return s.TAXLEVEL; }
    double       GetSalestaxrate() const { return s.SALESTAXRATE; }
    double       GetOrdvalnet() const { return s.ORDVALNET; }
    double       GetOrdvaltax() const { return s.ORDVALTAX; }

    const ordervaluesS &
                 GetStruct() const { return s; }
    void         SetTaxlevel(short t) { s.TAXLEVEL = t; }
    void         SetSalestaxrate(double t) { s.SALESTAXRATE = t; }
    void         SetOrdvalnet(double t) { s.ORDVALNET = t; }
    void         SetOrdvaltax(double t) { s.ORDVALTAX = t; }

    void         SetStruct(const ordervaluesS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CORDERVALUES() {
        ::buf_default((void *)&s, ORDERVALUES_BES, ORDERVALUES_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CORDERVALUES() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, ORDERVALUES_BES, ORDERVALUES_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, ORDERVALUES_BES, (int)ORDERVALUES_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, ORDERVALUES_BES, (int)ORDERVALUES_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_ORDERVALUES & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, ORDERVALUES_BES, (int)ORDERVALUES_ANZ, error_msg);
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
/* CreateSqlStatement of ORDERVALUES ******************************************/

 #define ORDERVALUES_CREATE(x) EXEC SQL create table x (\
         TAXLEVEL smallint default 0 not null,\
         SALESTAXRATE decimal(5,2) default 0 not null,\
         ORDVALNET decimal(11,2) default 0 not null,\
         ORDVALTAX decimal(11,2) default 0 not null) extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of ORDERVALUES ****************************************/

 #define ORDERVALUES_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_taxrates_1 on _X_(\
              TaxLevel );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ORDERVALUES ****************************************/

 #define ORDERVALUES_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_taxrates_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
