#ifndef __PP_NHIFPRICES_H_
#define __PP_NHIFPRICES_H_

/******************************************************************************/
/* c:\prri\headerfiles\nhifprices *********************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of NHIFPRICES ************************************************/

#define L_NHIFPRICES_HEALTHFUNDCODEHOSPITAL 25
#define L_NHIFPRICES_DATEVALIDFROM 11
#define L_NHIFPRICES_NHIFPRICE 9
#define N_NHIFPRICES_NHIFPRICE 2

/* Length/Count-Define of NHIFPRICES ******************************************/

#define LS_NHIFPRICES_HEALTHFUNDCODEHOSPITAL 25 + 1
#define LS_NHIFPRICES_DATEVALIDFROM 10 + 1
#define LS_NHIFPRICES_NHIFPRICE 9 + 2

#define NHIFPRICESHEALTHFUNDCODEHOSPITAL 0
#define NHIFPRICESDATEVALIDFROM 1
#define NHIFPRICESNHIFPRICE 2

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define NHIFPRICES_H
#define NHIFPRICES_ANZ ( sizeof(NHIFPRICES_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of NHIFPRICES ****************************************************/

#define NHIFPRICES_LISTE \
        NHIFPRICES.HEALTHFUNDCODEHOSPITAL,\
        NHIFPRICES.DATEVALIDFROM,\
        NHIFPRICES.NHIFPRICE
#define NHIFPRICES_LISTE_390 \
        HEALTHFUNDCODEHOSPITAL,\
        DATEVALIDFROM,\
        NHIFPRICE
#define NHIFPRICES_PLISTE \
        "NHIFPRICES.HEALTHFUNDCODEHOSPITAL,"\
        "NHIFPRICES.DATEVALIDFROM,"\
        "NHIFPRICES.NHIFPRICE"
#define NHIFPRICES_PELISTE \
        "HEALTHFUNDCODEHOSPITAL,"\
        "DATEVALIDFROM,"\
        "NHIFPRICE"
#define NHIFPRICES_UPDLISTE \
        "HEALTHFUNDCODEHOSPITAL=?,"\
        "DATEVALIDFROM=?,"\
        "NHIFPRICE=?"
/* SqlMacros-Define of NHIFPRICES *********************************************/

#define NHIFPRICES_ZEIGER(x) \
        :x->HEALTHFUNDCODEHOSPITAL,\
        :x->DATEVALIDFROM,\
        :x->NHIFPRICE
#define NHIFPRICES_ZEIGERSEL(x) \
        :x->HEALTHFUNDCODEHOSPITAL,\
        :x->DATEVALIDFROM,\
        :x->NHIFPRICE
#define NHIFPRICES_UPDATE(x) \
        NHIFPRICES.HEALTHFUNDCODEHOSPITAL=:x->HEALTHFUNDCODEHOSPITAL,\
        NHIFPRICES.DATEVALIDFROM=:x->DATEVALIDFROM,\
        NHIFPRICES.NHIFPRICE=:x->NHIFPRICE
/* SqlMacros390-Define of NHIFPRICES ******************************************/

#define NHIFPRICES_ZEIGER_390 \
        :HEALTHFUNDCODEHOSPITAL,\
        :DATEVALIDFROM,\
        :NHIFPRICE
#define NHIFPRICES_UPDATE_390 \
        HEALTHFUNDCODEHOSPITAL=:HEALTHFUNDCODEHOSPITAL,\
        DATEVALIDFROM=:DATEVALIDFROM,\
        NHIFPRICE=:NHIFPRICE
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of NHIFPRICES **********************************************/

#ifndef TRANSCLASS
typedef struct N_NHIFPRICES {
    char HEALTHFUNDCODEHOSPITAL[26];
    long DATEVALIDFROM;
    double NHIFPRICE;
} nhifpricesS;
#else /* TRANSCLASS */
typedef struct N_NHIFPRICES {
    char HEALTHFUNDCODEHOSPITAL[26];
    long DATEVALIDFROM;
    double NHIFPRICE;

    bool operator == (const N_NHIFPRICES& right) const {
        return (
            !strcmp(HEALTHFUNDCODEHOSPITAL, right.HEALTHFUNDCODEHOSPITAL) &&
            DATEVALIDFROM == right.DATEVALIDFROM &&
            NHIFPRICE == right.NHIFPRICE
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        strcpy(HEALTHFUNDCODEHOSPITAL, " " );
        DATEVALIDFROM = 0;
        NHIFPRICE = 0;
#endif
    }
} nhifpricesS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of NHIFPRICES ****************************************/

struct S_NHIFPRICES {
    char HEALTHFUNDCODEHOSPITAL[25 + 1];
    char DATEVALIDFROM[11];
    char NHIFPRICE[9 + 2];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of NHIFPRICES ***********************/

struct O_NHIFPRICES {
    char HEALTHFUNDCODEHOSPITAL[25];
    char DATEVALIDFROM[11];
    char NHIFPRICE[9];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of NHIFPRICES **********************************/

struct C_NHIFPRICES {
    char HEALTHFUNDCODEHOSPITAL[26];
    long DATEVALIDFROM;
    double NHIFPRICE;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of NHIFPRICES ********************************/

struct I_NHIFPRICES {
    short HEALTHFUNDCODEHOSPITAL;
    short DATEVALIDFROM;
    short NHIFPRICE;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of NHIFPRICES ******************************************/

#if defined (BUF_DESC)
static struct buf_desc NHIFPRICES_BES [] = {
   { TYP_C, 25, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc NHIFPRICES_BES [] = {
   { TYP_C, 25, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
};
#endif

/* description for datatypes of NHIFPRICES ************************************/

 #define NHIFPRICES_S390 \
         char HEALTHFUNDCODEHOSPITAL[26]; \
         long DATEVALIDFROM; \
         double NHIFPRICE; \



/* Copy-Function Struct to single Data NHIFPRICES *****************************/

 #define NHIFPRICES_S390_COPY_TO_SINGLE(_x_) \
          strcpy(HEALTHFUNDCODEHOSPITAL,_x_->HEALTHFUNDCODEHOSPITAL);\
         DATEVALIDFROM=_x_->DATEVALIDFROM;\
         NHIFPRICE=_x_->NHIFPRICE;\

 #define NHIFPRICES_S390_COPY_TO_STRUCT(_x_) \
          strcpy(_x_->HEALTHFUNDCODEHOSPITAL,HEALTHFUNDCODEHOSPITAL);\
          _x_->DATEVALIDFROM=DATEVALIDFROM;\
          _x_->NHIFPRICE=NHIFPRICE;\



/* FunctionNumber-Define of nhifprices ****************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of nhifprices ************************************/


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

class CNHIFPRICES : public ppDadeVirtual {
public:
    nhifpricesS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<nhifpricesS> lst; // class list

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
                     vector< nhifpricesS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     nhifpricesS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< nhifpricesS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<nhifpricesS>::iterator
                 beginList() { return lst.begin(); }
    vector<nhifpricesS>::iterator
                 endList  () { return lst.end  (); }

    const char*  GetHealthfundcodehospital(ppString & t) const { t = s.HEALTHFUNDCODEHOSPITAL; t.erasespace(ppString::END); return t.c_str(); }
    long         GetDatevalidfrom() const { return s.DATEVALIDFROM; }
    double       GetNhifprice() const { return s.NHIFPRICE; }

    const nhifpricesS &
                 GetStruct() const { return s; }
    void         SetHealthfundcodehospital(const ppString & t) { ppGStrCopy(s.HEALTHFUNDCODEHOSPITAL, t.c_str(), L_NHIFPRICES_HEALTHFUNDCODEHOSPITAL); }
    void         SetDatevalidfrom(long t) { s.DATEVALIDFROM = t; }
    void         SetNhifprice(double t) { s.NHIFPRICE = t; }

    void         SetStruct(const nhifpricesS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CNHIFPRICES() {
        ::buf_default((void *)&s, NHIFPRICES_BES, NHIFPRICES_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CNHIFPRICES() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, NHIFPRICES_BES, NHIFPRICES_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, NHIFPRICES_BES, (int)NHIFPRICES_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, NHIFPRICES_BES, (int)NHIFPRICES_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_NHIFPRICES & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.HEALTHFUNDCODEHOSPITAL);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, NHIFPRICES_BES, (int)NHIFPRICES_ANZ, error_msg);
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
/* CreateSqlStatement of NHIFPRICES *******************************************/

 #define NHIFPRICES_CREATE(x) EXEC SQL create table x (\
         HEALTHFUNDCODEHOSPITAL varchar(25,0) default " " not null,\
         DATEVALIDFROM integer default 0 not null,\
         NHIFPRICE decimal(9,2) default 0 not null) in ksc extent size 40 next size 8 lock mode row;



/* CreateIndexStatement of NHIFPRICES *****************************************/

 #define NHIFPRICES_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_nhifprice_1 on _X_(\
              HealthFundCodeHospital,\
              datevalidfrom ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of NHIFPRICES *****************************************/

 #define NHIFPRICES_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_nhifprice_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
