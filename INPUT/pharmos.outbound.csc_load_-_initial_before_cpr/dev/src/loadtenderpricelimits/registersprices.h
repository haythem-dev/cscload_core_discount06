#ifndef __PP_REGISTERSPRICES_H_
#define __PP_REGISTERSPRICES_H_

/******************************************************************************/
/* c:\prri\Headerfiles\registersprices ****************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of REGISTERSPRICES *******************************************/

#define L_REGISTERSPRICES_MINISTRYPRODUCTCODE 25
#define L_REGISTERSPRICES_DATEVALIDFROM 11
#define L_REGISTERSPRICES_MAXWHOLESALEPRICE 9
#define N_REGISTERSPRICES_MAXWHOLESALEPRICE 2
#define L_REGISTERSPRICES_REFERENCEPRICE 9
#define N_REGISTERSPRICES_REFERENCEPRICE 2

/* Length/Count-Define of REGISTERSPRICES *************************************/

#define LS_REGISTERSPRICES_MINISTRYPRODUCTCODE 25 + 1
#define LS_REGISTERSPRICES_DATEVALIDFROM 10 + 1
#define LS_REGISTERSPRICES_MAXWHOLESALEPRICE 9 + 2
#define LS_REGISTERSPRICES_REFERENCEPRICE 9 + 2

#define REGISTERSPRICESMINISTRYPRODUCTCODE 0
#define REGISTERSPRICESDATEVALIDFROM 1
#define REGISTERSPRICESMAXWHOLESALEPRICE 2
#define REGISTERSPRICESREFERENCEPRICE 3

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define REGISTERSPRICES_H
#define REGISTERSPRICES_ANZ ( sizeof(REGISTERSPRICES_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of REGISTERSPRICES ***********************************************/

#define REGISTERSPRICES_LISTE \
        REGISTERSPRICES.MINISTRYPRODUCTCODE,\
        REGISTERSPRICES.DATEVALIDFROM,\
        REGISTERSPRICES.MAXWHOLESALEPRICE,\
        REGISTERSPRICES.REFERENCEPRICE
#define REGISTERSPRICES_LISTE_390 \
        MINISTRYPRODUCTCODE,\
        DATEVALIDFROM,\
        MAXWHOLESALEPRICE,\
        REFERENCEPRICE
#define REGISTERSPRICES_PLISTE \
        "REGISTERSPRICES.MINISTRYPRODUCTCODE,"\
        "REGISTERSPRICES.DATEVALIDFROM,"\
        "REGISTERSPRICES.MAXWHOLESALEPRICE,"\
        "REGISTERSPRICES.REFERENCEPRICE"
#define REGISTERSPRICES_PELISTE \
        "MINISTRYPRODUCTCODE,"\
        "DATEVALIDFROM,"\
        "MAXWHOLESALEPRICE,"\
        "REFERENCEPRICE"
#define REGISTERSPRICES_UPDLISTE \
        "MINISTRYPRODUCTCODE=?,"\
        "DATEVALIDFROM=?,"\
        "MAXWHOLESALEPRICE=?,"\
        "REFERENCEPRICE=?"
/* SqlMacros-Define of REGISTERSPRICES ****************************************/

#define REGISTERSPRICES_ZEIGER(x) \
        :x->MINISTRYPRODUCTCODE,\
        :x->DATEVALIDFROM,\
        :x->MAXWHOLESALEPRICE,\
        :x->REFERENCEPRICE
#define REGISTERSPRICES_ZEIGERSEL(x) \
        :x->MINISTRYPRODUCTCODE,\
        :x->DATEVALIDFROM,\
        :x->MAXWHOLESALEPRICE,\
        :x->REFERENCEPRICE
#define REGISTERSPRICES_UPDATE(x) \
        REGISTERSPRICES.MINISTRYPRODUCTCODE=:x->MINISTRYPRODUCTCODE,\
        REGISTERSPRICES.DATEVALIDFROM=:x->DATEVALIDFROM,\
        REGISTERSPRICES.MAXWHOLESALEPRICE=:x->MAXWHOLESALEPRICE,\
        REGISTERSPRICES.REFERENCEPRICE=:x->REFERENCEPRICE
/* SqlMacros390-Define of REGISTERSPRICES *************************************/

#define REGISTERSPRICES_ZEIGER_390 \
        :MINISTRYPRODUCTCODE,\
        :DATEVALIDFROM,\
        :MAXWHOLESALEPRICE,\
        :REFERENCEPRICE
#define REGISTERSPRICES_UPDATE_390 \
        MINISTRYPRODUCTCODE=:MINISTRYPRODUCTCODE,\
        DATEVALIDFROM=:DATEVALIDFROM,\
        MAXWHOLESALEPRICE=:MAXWHOLESALEPRICE,\
        REFERENCEPRICE=:REFERENCEPRICE
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of REGISTERSPRICES *****************************************/

#ifndef TRANSCLASS
typedef struct N_REGISTERSPRICES {
    char MINISTRYPRODUCTCODE[26];
    long DATEVALIDFROM;
    double MAXWHOLESALEPRICE;
    double REFERENCEPRICE;
} registerspricesS;
#else /* TRANSCLASS */
typedef struct N_REGISTERSPRICES {
    char MINISTRYPRODUCTCODE[26];
    long DATEVALIDFROM;
    double MAXWHOLESALEPRICE;
    double REFERENCEPRICE;

    bool operator == (const N_REGISTERSPRICES& right) const {
        return (
            !strcmp(MINISTRYPRODUCTCODE, right.MINISTRYPRODUCTCODE) &&
            DATEVALIDFROM == right.DATEVALIDFROM &&
            MAXWHOLESALEPRICE == right.MAXWHOLESALEPRICE &&
            REFERENCEPRICE == right.REFERENCEPRICE
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        strcpy(MINISTRYPRODUCTCODE, " " );
        DATEVALIDFROM = 0;
        MAXWHOLESALEPRICE = 0;
        REFERENCEPRICE = 0;
#endif
    }
} registerspricesS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of REGISTERSPRICES ***********************************/

struct S_REGISTERSPRICES {
    char MINISTRYPRODUCTCODE[25 + 1];
    char DATEVALIDFROM[11];
    char MAXWHOLESALEPRICE[9 + 2];
    char REFERENCEPRICE[9 + 2];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of REGISTERSPRICES ******************/

struct O_REGISTERSPRICES {
    char MINISTRYPRODUCTCODE[25];
    char DATEVALIDFROM[11];
    char MAXWHOLESALEPRICE[9];
    char REFERENCEPRICE[9];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of REGISTERSPRICES *****************************/

struct C_REGISTERSPRICES {
    char MINISTRYPRODUCTCODE[26];
    long DATEVALIDFROM;
    double MAXWHOLESALEPRICE;
    double REFERENCEPRICE;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of REGISTERSPRICES ***************************/

struct I_REGISTERSPRICES {
    short MINISTRYPRODUCTCODE;
    short DATEVALIDFROM;
    short MAXWHOLESALEPRICE;
    short REFERENCEPRICE;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of REGISTERSPRICES *************************************/

#if defined (BUF_DESC)
static struct buf_desc REGISTERSPRICES_BES [] = {
   { TYP_C, 25, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc REGISTERSPRICES_BES [] = {
   { TYP_C, 25, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
};
#endif

/* description for datatypes of REGISTERSPRICES *******************************/

 #define REGISTERSPRICES_S390 \
         char MINISTRYPRODUCTCODE[26]; \
         long DATEVALIDFROM; \
         double MAXWHOLESALEPRICE; \
         double REFERENCEPRICE; \



/* Copy-Function Struct to single Data REGISTERSPRICES ************************/

 #define REGISTERSPRICES_S390_COPY_TO_SINGLE(_x_) \
          strcpy(MINISTRYPRODUCTCODE,_x_->MINISTRYPRODUCTCODE);\
         DATEVALIDFROM=_x_->DATEVALIDFROM;\
         MAXWHOLESALEPRICE=_x_->MAXWHOLESALEPRICE;\
         REFERENCEPRICE=_x_->REFERENCEPRICE;\

 #define REGISTERSPRICES_S390_COPY_TO_STRUCT(_x_) \
          strcpy(_x_->MINISTRYPRODUCTCODE,MINISTRYPRODUCTCODE);\
          _x_->DATEVALIDFROM=DATEVALIDFROM;\
          _x_->MAXWHOLESALEPRICE=MAXWHOLESALEPRICE;\
          _x_->REFERENCEPRICE=REFERENCEPRICE;\



/* FunctionNumber-Define of registersprices ***********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of registersprices *******************************/


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

class CREGISTERSPRICES : public ppDadeVirtual {
public:
    registerspricesS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<registerspricesS> lst; // class list

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
                     vector< registerspricesS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     registerspricesS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< registerspricesS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<registerspricesS>::iterator
                 beginList() { return lst.begin(); }
    vector<registerspricesS>::iterator
                 endList  () { return lst.end  (); }

    const char*  GetMinistryproductcode(ppString & t) const { t = s.MINISTRYPRODUCTCODE; t.erasespace(ppString::END); return t.c_str(); }
    long         GetDatevalidfrom() const { return s.DATEVALIDFROM; }
    double       GetMaxwholesaleprice() const { return s.MAXWHOLESALEPRICE; }
    double       GetReferenceprice() const { return s.REFERENCEPRICE; }

    const registerspricesS &
                 GetStruct() const { return s; }
    void         SetMinistryproductcode(const ppString & t) { ppGStrCopy(s.MINISTRYPRODUCTCODE, t.c_str(), L_REGISTERSPRICES_MINISTRYPRODUCTCODE); }
    void         SetDatevalidfrom(long t) { s.DATEVALIDFROM = t; }
    void         SetMaxwholesaleprice(double t) { s.MAXWHOLESALEPRICE = t; }
    void         SetReferenceprice(double t) { s.REFERENCEPRICE = t; }

    void         SetStruct(const registerspricesS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CREGISTERSPRICES() {
        ::buf_default((void *)&s, REGISTERSPRICES_BES, REGISTERSPRICES_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CREGISTERSPRICES() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, REGISTERSPRICES_BES, REGISTERSPRICES_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, REGISTERSPRICES_BES, (int)REGISTERSPRICES_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, REGISTERSPRICES_BES, (int)REGISTERSPRICES_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_REGISTERSPRICES & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.MINISTRYPRODUCTCODE);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, REGISTERSPRICES_BES, (int)REGISTERSPRICES_ANZ, error_msg);
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
/* CreateSqlStatement of REGISTERSPRICES **************************************/

 #define REGISTERSPRICES_CREATE(x) EXEC SQL create table x (\
         MINISTRYPRODUCTCODE varchar(25,0) default " " not null,\
         DATEVALIDFROM integer default 0 not null,\
         MAXWHOLESALEPRICE decimal(9,2) default 0 not null,\
         REFERENCEPRICE decimal(9,2) default 0 not null) in ksc extent size 40 next size 8 lock mode row;



/* CreateIndexStatement of REGISTERSPRICES ************************************/

 #define REGISTERSPRICES_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_registersprice_1 on _X_(\
              MinistryProductCode,\
              datevalidfrom ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of REGISTERSPRICES ************************************/

 #define REGISTERSPRICES_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_registersprice_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
