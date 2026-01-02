#ifndef __PP_ORDERENTRYRESTRICTIONS_H_
#define __PP_ORDERENTRYRESTRICTIONS_H_

/******************************************************************************/
/* v:\OrderentryRestrictions **************************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of ORDERENTRYRESTRICTIONS ************************************/

#define L_ORDERENTRYRESTRICTIONS_BRANCHNO 6
#define L_ORDERENTRYRESTRICTIONS_RESTRICTIONTYPE 6
#define L_ORDERENTRYRESTRICTIONS_RESTRICTIONVALUE 6
#define L_ORDERENTRYRESTRICTIONS_ORIGINTYPE 6

/* Length/Count-Define of ORDERENTRYRESTRICTIONS ******************************/

#define LS_ORDERENTRYRESTRICTIONS_BRANCHNO 5 + 1
#define LS_ORDERENTRYRESTRICTIONS_RESTRICTIONTYPE 5 + 1
#define LS_ORDERENTRYRESTRICTIONS_RESTRICTIONVALUE 5 + 1
#define LS_ORDERENTRYRESTRICTIONS_ORIGINTYPE 5 + 1

#define ORDERENTRYRESTRICTIONSBRANCHNO 0
#define ORDERENTRYRESTRICTIONSRESTRICTIONTYPE 1
#define ORDERENTRYRESTRICTIONSRESTRICTIONVALUE 2
#define ORDERENTRYRESTRICTIONSORIGINTYPE 3

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define ORDERENTRYRESTRICTIONS_H
#define ORDERENTRYRESTRICTIONS_ANZ ( sizeof(ORDERENTRYRESTRICTIONS_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ORDERENTRYRESTRICTIONS ****************************************/

#define ORDERENTRYRESTRICTIONS_LISTE \
        ORDERENTRYRESTRICTIONS.BRANCHNO,\
        ORDERENTRYRESTRICTIONS.RESTRICTIONTYPE,\
        ORDERENTRYRESTRICTIONS.RESTRICTIONVALUE,\
        ORDERENTRYRESTRICTIONS.ORIGINTYPE
#define ORDERENTRYRESTRICTIONS_LISTE_390 \
        BRANCHNO,\
        RESTRICTIONTYPE,\
        RESTRICTIONVALUE,\
        ORIGINTYPE
#define ORDERENTRYRESTRICTIONS_PLISTE \
        "ORDERENTRYRESTRICTIONS.BRANCHNO,"\
        "ORDERENTRYRESTRICTIONS.RESTRICTIONTYPE,"\
        "ORDERENTRYRESTRICTIONS.RESTRICTIONVALUE,"\
        "ORDERENTRYRESTRICTIONS.ORIGINTYPE"
#define ORDERENTRYRESTRICTIONS_PELISTE \
        "BRANCHNO,"\
        "RESTRICTIONTYPE,"\
        "RESTRICTIONVALUE,"\
        "ORIGINTYPE"
#define ORDERENTRYRESTRICTIONS_UPDLISTE \
        "BRANCHNO=?,"\
        "RESTRICTIONTYPE=?,"\
        "RESTRICTIONVALUE=?,"\
        "ORIGINTYPE=?"
/* SqlMacros-Define of ORDERENTRYRESTRICTIONS *********************************/

#define ORDERENTRYRESTRICTIONS_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->RESTRICTIONTYPE,\
        :x->RESTRICTIONVALUE,\
        :x->ORIGINTYPE
#define ORDERENTRYRESTRICTIONS_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->RESTRICTIONTYPE,\
        :x->RESTRICTIONVALUE,\
        :x->ORIGINTYPE
#define ORDERENTRYRESTRICTIONS_UPDATE(x) \
        ORDERENTRYRESTRICTIONS.BRANCHNO=:x->BRANCHNO,\
        ORDERENTRYRESTRICTIONS.RESTRICTIONTYPE=:x->RESTRICTIONTYPE,\
        ORDERENTRYRESTRICTIONS.RESTRICTIONVALUE=:x->RESTRICTIONVALUE,\
        ORDERENTRYRESTRICTIONS.ORIGINTYPE=:x->ORIGINTYPE
/* SqlMacros390-Define of ORDERENTRYRESTRICTIONS ******************************/

#define ORDERENTRYRESTRICTIONS_ZEIGER_390 \
        :BRANCHNO,\
        :RESTRICTIONTYPE,\
        :RESTRICTIONVALUE,\
        :ORIGINTYPE
#define ORDERENTRYRESTRICTIONS_UPDATE_390 \
        BRANCHNO=:BRANCHNO,\
        RESTRICTIONTYPE=:RESTRICTIONTYPE,\
        RESTRICTIONVALUE=:RESTRICTIONVALUE,\
        ORIGINTYPE=:ORIGINTYPE
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of ORDERENTRYRESTRICTIONS **********************************/

#ifndef TRANSCLASS
typedef struct N_ORDERENTRYRESTRICTIONS {
    short BRANCHNO;
    short RESTRICTIONTYPE;
    short RESTRICTIONVALUE;
    short ORIGINTYPE;
} orderentryrestrictionsS;
#else /* TRANSCLASS */
typedef struct N_ORDERENTRYRESTRICTIONS {
    short BRANCHNO;
    short RESTRICTIONTYPE;
    short RESTRICTIONVALUE;
    short ORIGINTYPE;

    bool operator == (const N_ORDERENTRYRESTRICTIONS& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            RESTRICTIONTYPE == right.RESTRICTIONTYPE &&
            RESTRICTIONVALUE == right.RESTRICTIONVALUE &&
            ORIGINTYPE == right.ORIGINTYPE
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        RESTRICTIONTYPE = 0;
        RESTRICTIONVALUE = 0;
        ORIGINTYPE = 0;
#endif
    }
} orderentryrestrictionsS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ORDERENTRYRESTRICTIONS ****************************/

struct S_ORDERENTRYRESTRICTIONS {
    char BRANCHNO[7];
    char RESTRICTIONTYPE[7];
    char RESTRICTIONVALUE[7];
    char ORIGINTYPE[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ORDERENTRYRESTRICTIONS ***********/

struct O_ORDERENTRYRESTRICTIONS {
    char BRANCHNO[7];
    char RESTRICTIONTYPE[7];
    char RESTRICTIONVALUE[7];
    char ORIGINTYPE[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ORDERENTRYRESTRICTIONS **********************/

struct C_ORDERENTRYRESTRICTIONS {
    short BRANCHNO;
    short RESTRICTIONTYPE;
    short RESTRICTIONVALUE;
    short ORIGINTYPE;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ORDERENTRYRESTRICTIONS ********************/

struct I_ORDERENTRYRESTRICTIONS {
    short BRANCHNO;
    short RESTRICTIONTYPE;
    short RESTRICTIONVALUE;
    short ORIGINTYPE;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ORDERENTRYRESTRICTIONS ******************************/

#if defined (BUF_DESC)
static struct buf_desc ORDERENTRYRESTRICTIONS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc ORDERENTRYRESTRICTIONS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* description for datatypes of ORDERENTRYRESTRICTIONS ************************/

 #define ORDERENTRYRESTRICTIONS_S390 \
         short BRANCHNO; \
         short RESTRICTIONTYPE; \
         short RESTRICTIONVALUE; \
         short ORIGINTYPE; \



/* Copy-Function Struct to single Data ORDERENTRYRESTRICTIONS *****************/

 #define ORDERENTRYRESTRICTIONS_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         RESTRICTIONTYPE=_x_->RESTRICTIONTYPE;\
         RESTRICTIONVALUE=_x_->RESTRICTIONVALUE;\
         ORIGINTYPE=_x_->ORIGINTYPE;\

 #define ORDERENTRYRESTRICTIONS_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->RESTRICTIONTYPE=RESTRICTIONTYPE;\
          _x_->RESTRICTIONVALUE=RESTRICTIONVALUE;\
          _x_->ORIGINTYPE=ORIGINTYPE;\



/* FunctionNumber-Define of OrderentryRestrictions ****************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of OrderentryRestrictions ************************/


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

class CORDERENTRYRESTRICTIONS : public ppDadeVirtual {
public:
    orderentryrestrictionsS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<orderentryrestrictionsS> lst; // class list

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
                     vector< orderentryrestrictionsS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     orderentryrestrictionsS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< orderentryrestrictionsS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<orderentryrestrictionsS>::iterator
                 beginList() { return lst.begin(); }
    vector<orderentryrestrictionsS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    short        GetRestrictiontype() const { return s.RESTRICTIONTYPE; }
    short        GetRestrictionvalue() const { return s.RESTRICTIONVALUE; }
    short        GetOrigintype() const { return s.ORIGINTYPE; }

    const orderentryrestrictionsS &
                 GetStruct() const { return s; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetRestrictiontype(short t) { s.RESTRICTIONTYPE = t; }
    void         SetRestrictionvalue(short t) { s.RESTRICTIONVALUE = t; }
    void         SetOrigintype(short t) { s.ORIGINTYPE = t; }

    void         SetStruct(const orderentryrestrictionsS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CORDERENTRYRESTRICTIONS() {
        ::buf_default((void *)&s, ORDERENTRYRESTRICTIONS_BES, ORDERENTRYRESTRICTIONS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CORDERENTRYRESTRICTIONS() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, ORDERENTRYRESTRICTIONS_BES, ORDERENTRYRESTRICTIONS_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, ORDERENTRYRESTRICTIONS_BES, (int)ORDERENTRYRESTRICTIONS_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, ORDERENTRYRESTRICTIONS_BES, (int)ORDERENTRYRESTRICTIONS_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_ORDERENTRYRESTRICTIONS & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, ORDERENTRYRESTRICTIONS_BES, (int)ORDERENTRYRESTRICTIONS_ANZ, error_msg);
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
/* CreateSqlStatement of ORDERENTRYRESTRICTIONS *******************************/

 #define ORDERENTRYRESTRICTIONS_CREATE(x) EXEC SQL create table x (\
         BRANCHNO smallint default 0 not null,\
         RESTRICTIONTYPE smallint default 0 not null,\
         RESTRICTIONVALUE smallint default 0 not null,\
         ORIGINTYPE smallint default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of ORDERENTRYRESTRICTIONS *****************************/

 #define ORDERENTRYRESTRICTIONS_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
/* DeleteIndexStatement of ORDERENTRYRESTRICTIONS *****************************/

 #define ORDERENTRYRESTRICTIONS_DELETE_INDEX(_X_)\
              _X_ = 0;\


#endif   // GUARD
