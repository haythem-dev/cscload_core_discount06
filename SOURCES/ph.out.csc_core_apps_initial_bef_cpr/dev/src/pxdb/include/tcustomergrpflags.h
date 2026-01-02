#ifndef __PP_CUSTOMERGRPFLAGS_H_
#define __PP_CUSTOMERGRPFLAGS_H_

/******************************************************************************/
/* d:\prj\DF\UNIX\loadcustgroups\customergrpflags *****************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of CUSTOMERGRPFLAGS ******************************************/

#define L_CUSTOMERGRPFLAGS_BRANCHNO 6
#define L_CUSTOMERGRPFLAGS_CUSTOMERGROUPNO 6
#define L_CUSTOMERGRPFLAGS_CUSTGRPFLAGTYPE 6
#define L_CUSTOMERGRPFLAGS_CUSTOMERGRPFLAG 6
#define L_CUSTOMERGRPFLAGS_UPD_FLAG 1

/* Length/Count-Define of CUSTOMERGRPFLAGS ************************************/

#define LS_CUSTOMERGRPFLAGS_BRANCHNO 5 + 1
#define LS_CUSTOMERGRPFLAGS_CUSTOMERGROUPNO 5 + 1
#define LS_CUSTOMERGRPFLAGS_CUSTGRPFLAGTYPE 5 + 1
#define LS_CUSTOMERGRPFLAGS_CUSTOMERGRPFLAG 5 + 1
#define LS_CUSTOMERGRPFLAGS_UPD_FLAG 1 + 1

#define CUSTOMERGRPFLAGSBRANCHNO 0
#define CUSTOMERGRPFLAGSCUSTOMERGROUPNO 1
#define CUSTOMERGRPFLAGSCUSTGRPFLAGTYPE 2
#define CUSTOMERGRPFLAGSCUSTOMERGRPFLAG 3
#define CUSTOMERGRPFLAGSUPD_FLAG 4

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define CUSTOMERGRPFLAGS_H
#define CUSTOMERGRPFLAGS_ANZ ( sizeof(CUSTOMERGRPFLAGS_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of CUSTOMERGRPFLAGS **********************************************/

#define CUSTOMERGRPFLAGS_LISTE \
        CUSTOMERGRPFLAGS.BRANCHNO,\
        CUSTOMERGRPFLAGS.CUSTOMERGROUPNO,\
        CUSTOMERGRPFLAGS.CUSTGRPFLAGTYPE,\
        CUSTOMERGRPFLAGS.CUSTOMERGRPFLAG,\
        CUSTOMERGRPFLAGS.UPD_FLAG
#define CUSTOMERGRPFLAGS_LISTE_390 \
        BRANCHNO,\
        CUSTOMERGROUPNO,\
        CUSTGRPFLAGTYPE,\
        CUSTOMERGRPFLAG,\
        UPD_FLAG
#define CUSTOMERGRPFLAGS_PLISTE \
        "CUSTOMERGRPFLAGS.BRANCHNO,"\
        "CUSTOMERGRPFLAGS.CUSTOMERGROUPNO,"\
        "CUSTOMERGRPFLAGS.CUSTGRPFLAGTYPE,"\
        "CUSTOMERGRPFLAGS.CUSTOMERGRPFLAG,"\
        "CUSTOMERGRPFLAGS.UPD_FLAG"
#define CUSTOMERGRPFLAGS_PELISTE \
        "BRANCHNO,"\
        "CUSTOMERGROUPNO,"\
        "CUSTGRPFLAGTYPE,"\
        "CUSTOMERGRPFLAG,"\
        "UPD_FLAG"
#define CUSTOMERGRPFLAGS_UPDLISTE \
        "BRANCHNO=?,"\
        "CUSTOMERGROUPNO=?,"\
        "CUSTGRPFLAGTYPE=?,"\
        "CUSTOMERGRPFLAG=?,"\
        "UPD_FLAG=?"
/* SqlMacros-Define of CUSTOMERGRPFLAGS ***************************************/

#define CUSTOMERGRPFLAGS_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERGROUPNO,\
        :x->CUSTGRPFLAGTYPE,\
        :x->CUSTOMERGRPFLAG,\
        :x->UPD_FLAG
#define CUSTOMERGRPFLAGS_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERGROUPNO,\
        :x->CUSTGRPFLAGTYPE,\
        :x->CUSTOMERGRPFLAG,\
        :x->UPD_FLAG
#define CUSTOMERGRPFLAGS_UPDATE(x) \
        CUSTOMERGRPFLAGS.BRANCHNO=:x->BRANCHNO,\
        CUSTOMERGRPFLAGS.CUSTOMERGROUPNO=:x->CUSTOMERGROUPNO,\
        CUSTOMERGRPFLAGS.CUSTGRPFLAGTYPE=:x->CUSTGRPFLAGTYPE,\
        CUSTOMERGRPFLAGS.CUSTOMERGRPFLAG=:x->CUSTOMERGRPFLAG,\
        CUSTOMERGRPFLAGS.UPD_FLAG=:x->UPD_FLAG
/* SqlMacros390-Define of CUSTOMERGRPFLAGS ************************************/

#define CUSTOMERGRPFLAGS_ZEIGER_390 \
        :BRANCHNO,\
        :CUSTOMERGROUPNO,\
        :CUSTGRPFLAGTYPE,\
        :CUSTOMERGRPFLAG,\
        :UPD_FLAG
#define CUSTOMERGRPFLAGS_UPDATE_390 \
        BRANCHNO=:BRANCHNO,\
        CUSTOMERGROUPNO=:CUSTOMERGROUPNO,\
        CUSTGRPFLAGTYPE=:CUSTGRPFLAGTYPE,\
        CUSTOMERGRPFLAG=:CUSTOMERGRPFLAG,\
        UPD_FLAG=:UPD_FLAG
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of CUSTOMERGRPFLAGS ****************************************/

#ifndef TRANSCLASS
typedef struct N_CUSTOMERGRPFLAGS {
    short BRANCHNO;
    short CUSTOMERGROUPNO;
    short CUSTGRPFLAGTYPE;
    short CUSTOMERGRPFLAG;
    char UPD_FLAG[2];
} customergrpflagsS;
#else /* TRANSCLASS */
typedef struct N_CUSTOMERGRPFLAGS {
    short BRANCHNO;
    short CUSTOMERGROUPNO;
    short CUSTGRPFLAGTYPE;
    short CUSTOMERGRPFLAG;
    char UPD_FLAG[2];

    bool operator == (const N_CUSTOMERGRPFLAGS& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            CUSTOMERGROUPNO == right.CUSTOMERGROUPNO &&
            CUSTGRPFLAGTYPE == right.CUSTGRPFLAGTYPE &&
            CUSTOMERGRPFLAG == right.CUSTOMERGRPFLAG &&
            !strcmp(UPD_FLAG, right.UPD_FLAG)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        CUSTOMERGROUPNO = 0;
        CUSTGRPFLAGTYPE = 0;
        CUSTOMERGRPFLAG = 0;
        strcpy(UPD_FLAG, " " );
#endif
    }
} customergrpflagsS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of CUSTOMERGRPFLAGS **********************************/

struct S_CUSTOMERGRPFLAGS {
    char BRANCHNO[7];
    char CUSTOMERGROUPNO[7];
    char CUSTGRPFLAGTYPE[7];
    char CUSTOMERGRPFLAG[7];
    char UPD_FLAG[1 + 1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of CUSTOMERGRPFLAGS *****************/

struct O_CUSTOMERGRPFLAGS {
    char BRANCHNO[7];
    char CUSTOMERGROUPNO[7];
    char CUSTGRPFLAGTYPE[7];
    char CUSTOMERGRPFLAG[7];
    char UPD_FLAG[1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of CUSTOMERGRPFLAGS ****************************/

struct C_CUSTOMERGRPFLAGS {
    short BRANCHNO;
    short CUSTOMERGROUPNO;
    short CUSTGRPFLAGTYPE;
    short CUSTOMERGRPFLAG;
    char UPD_FLAG;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of CUSTOMERGRPFLAGS **************************/

struct I_CUSTOMERGRPFLAGS {
    short BRANCHNO;
    short CUSTOMERGROUPNO;
    short CUSTGRPFLAGTYPE;
    short CUSTOMERGRPFLAG;
    short UPD_FLAG;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CUSTOMERGRPFLAGS ************************************/

#if defined (BUF_DESC)
static struct buf_desc CUSTOMERGRPFLAGS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CUSTOMERGRPFLAGS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
};
#endif

/* description for datatypes of CUSTOMERGRPFLAGS ******************************/

 #define CUSTOMERGRPFLAGS_S390 \
         short BRANCHNO; \
         short CUSTOMERGROUPNO; \
         short CUSTGRPFLAGTYPE; \
         short CUSTOMERGRPFLAG; \
         char UPD_FLAG; \



/* Copy-Function Struct to single Data CUSTOMERGRPFLAGS ***********************/

 #define CUSTOMERGRPFLAGS_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         CUSTOMERGROUPNO=_x_->CUSTOMERGROUPNO;\
         CUSTGRPFLAGTYPE=_x_->CUSTGRPFLAGTYPE;\
         CUSTOMERGRPFLAG=_x_->CUSTOMERGRPFLAG;\
         UPD_FLAG=_x_->UPD_FLAG;\

 #define CUSTOMERGRPFLAGS_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->CUSTOMERGROUPNO=CUSTOMERGROUPNO;\
          _x_->CUSTGRPFLAGTYPE=CUSTGRPFLAGTYPE;\
          _x_->CUSTOMERGRPFLAG=CUSTOMERGRPFLAG;\
          _x_->UPD_FLAG=UPD_FLAG;\



/* FunctionNumber-Define of customergrpflags **********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of customergrpflags ******************************/


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

class CCUSTOMERGRPFLAGS : public ppDadeVirtual {
public:
    customergrpflagsS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<customergrpflagsS> lst; // class list

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
                     vector< customergrpflagsS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     customergrpflagsS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< customergrpflagsS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<customergrpflagsS>::iterator
                 beginList() { return lst.begin(); }
    vector<customergrpflagsS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    short        GetCustomergroupno() const { return s.CUSTOMERGROUPNO; }
    short        GetCustgrpflagtype() const { return s.CUSTGRPFLAGTYPE; }
    short        GetCustomergrpflag() const { return s.CUSTOMERGRPFLAG; }
    char         GetUpd_flag() const { return s.UPD_FLAG[0]; }

    const customergrpflagsS &
                 GetStruct() const { return s; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustomergroupno(short t) { s.CUSTOMERGROUPNO = t; }
    void         SetCustgrpflagtype(short t) { s.CUSTGRPFLAGTYPE = t; }
    void         SetCustomergrpflag(short t) { s.CUSTOMERGRPFLAG = t; }
    void         SetUpd_flag(char t) { s.UPD_FLAG[0] = t; s.UPD_FLAG[1] = '\0';}

    void         SetStruct(const customergrpflagsS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCUSTOMERGRPFLAGS() {
        ::buf_default((void *)&s, CUSTOMERGRPFLAGS_BES, CUSTOMERGRPFLAGS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCUSTOMERGRPFLAGS() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CUSTOMERGRPFLAGS_BES, CUSTOMERGRPFLAGS_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, CUSTOMERGRPFLAGS_BES, (int)CUSTOMERGRPFLAGS_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, CUSTOMERGRPFLAGS_BES, (int)CUSTOMERGRPFLAGS_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_CUSTOMERGRPFLAGS & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CUSTOMERGRPFLAGS_BES, (int)CUSTOMERGRPFLAGS_ANZ, error_msg);
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
/* CreateSqlStatement of CUSTOMERGRPFLAGS *************************************/

 #define CUSTOMERGRPFLAGS_CREATE(x) EXEC SQL create table x (\
         BRANCHNO smallint default 0 not null,\
         CUSTOMERGROUPNO smallint default 0 not null,\
         CUSTGRPFLAGTYPE smallint default 0 not null,\
         CUSTOMERGRPFLAG smallint default 0 not null,\
         UPD_FLAG char(1) default " " not null) in ksc extent size 16 next size 8 lock mode row;



/* CreateIndexStatement of CUSTOMERGRPFLAGS ***********************************/

 #define CUSTOMERGRPFLAGS_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_customergrpflag_1 on _X_(\
              BranchNo,\
              customergroupno,\
              custgrpflagtype ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of CUSTOMERGRPFLAGS ***********************************/

 #define CUSTOMERGRPFLAGS_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_customergrpflag_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
