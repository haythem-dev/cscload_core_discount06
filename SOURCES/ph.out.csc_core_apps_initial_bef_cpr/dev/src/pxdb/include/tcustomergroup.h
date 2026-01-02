#ifndef __PP_CUSTOMERGROUP_H_
#define __PP_CUSTOMERGROUP_H_

/******************************************************************************/
/* d:\prj\DF\UNIX\loadcustgroups\customergroup ********************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of CUSTOMERGROUP *********************************************/

#define L_CUSTOMERGROUP_BRANCHNO 6
#define L_CUSTOMERGROUP_CUSTOMERGROUPNO 6
#define L_CUSTOMERGROUP_NAME 30
#define L_CUSTOMERGROUP_SALES_RESTR_PH 16
#define L_CUSTOMERGROUP_BLOCK_FLAG 6
#define L_CUSTOMERGROUP_BASISNATRA_FLAG 6
#define L_CUSTOMERGROUP_UPD_FLAG 1

/* Length/Count-Define of CUSTOMERGROUP ***************************************/

#define LS_CUSTOMERGROUP_BRANCHNO 5 + 1
#define LS_CUSTOMERGROUP_CUSTOMERGROUPNO 5 + 1
#define LS_CUSTOMERGROUP_NAME 30 + 1
#define LS_CUSTOMERGROUP_SALES_RESTR_PH 16 + 1
#define LS_CUSTOMERGROUP_BLOCK_FLAG 5 + 1
#define LS_CUSTOMERGROUP_BASISNATRA_FLAG 5 + 1
#define LS_CUSTOMERGROUP_UPD_FLAG 1 + 1

#define CUSTOMERGROUPBRANCHNO 0
#define CUSTOMERGROUPCUSTOMERGROUPNO 1
#define CUSTOMERGROUPNAME 2
#define CUSTOMERGROUPSALES_RESTR_PH 3
#define CUSTOMERGROUPBLOCK_FLAG 4
#define CUSTOMERGROUPBASISNATRA_FLAG 5
#define CUSTOMERGROUPUPD_FLAG 6

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define CUSTOMERGROUP_H
#define CUSTOMERGROUP_ANZ ( sizeof(CUSTOMERGROUP_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of CUSTOMERGROUP *************************************************/

#define CUSTOMERGROUP_LISTE \
        CUSTOMERGROUP.BRANCHNO,\
        CUSTOMERGROUP.CUSTOMERGROUPNO,\
        CUSTOMERGROUP.NAME,\
        CUSTOMERGROUP.SALES_RESTR_PH,\
        CUSTOMERGROUP.BLOCK_FLAG,\
        CUSTOMERGROUP.BASISNATRA_FLAG,\
        CUSTOMERGROUP.UPD_FLAG
#define CUSTOMERGROUP_LISTE_390 \
        BRANCHNO,\
        CUSTOMERGROUPNO,\
        NAME,\
        SALES_RESTR_PH,\
        BLOCK_FLAG,\
        BASISNATRA_FLAG,\
        UPD_FLAG
#define CUSTOMERGROUP_PLISTE \
        "CUSTOMERGROUP.BRANCHNO,"\
        "CUSTOMERGROUP.CUSTOMERGROUPNO,"\
        "CUSTOMERGROUP.NAME,"\
        "CUSTOMERGROUP.SALES_RESTR_PH,"\
        "CUSTOMERGROUP.BLOCK_FLAG,"\
        "CUSTOMERGROUP.BASISNATRA_FLAG,"\
        "CUSTOMERGROUP.UPD_FLAG"
#define CUSTOMERGROUP_PELISTE \
        "BRANCHNO,"\
        "CUSTOMERGROUPNO,"\
        "NAME,"\
        "SALES_RESTR_PH,"\
        "BLOCK_FLAG,"\
        "BASISNATRA_FLAG,"\
        "UPD_FLAG"
#define CUSTOMERGROUP_UPDLISTE \
        "BRANCHNO=?,"\
        "CUSTOMERGROUPNO=?,"\
        "NAME=?,"\
        "SALES_RESTR_PH=?,"\
        "BLOCK_FLAG=?,"\
        "BASISNATRA_FLAG=?,"\
        "UPD_FLAG=?"
/* SqlMacros-Define of CUSTOMERGROUP ******************************************/

#define CUSTOMERGROUP_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERGROUPNO,\
        :x->NAME,\
        :x->SALES_RESTR_PH,\
        :x->BLOCK_FLAG,\
        :x->BASISNATRA_FLAG,\
        :x->UPD_FLAG
#define CUSTOMERGROUP_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERGROUPNO,\
        :x->NAME,\
        :x->SALES_RESTR_PH,\
        :x->BLOCK_FLAG,\
        :x->BASISNATRA_FLAG,\
        :x->UPD_FLAG
#define CUSTOMERGROUP_UPDATE(x) \
        CUSTOMERGROUP.BRANCHNO=:x->BRANCHNO,\
        CUSTOMERGROUP.CUSTOMERGROUPNO=:x->CUSTOMERGROUPNO,\
        CUSTOMERGROUP.NAME=:x->NAME,\
        CUSTOMERGROUP.SALES_RESTR_PH=:x->SALES_RESTR_PH,\
        CUSTOMERGROUP.BLOCK_FLAG=:x->BLOCK_FLAG,\
        CUSTOMERGROUP.BASISNATRA_FLAG=:x->BASISNATRA_FLAG,\
        CUSTOMERGROUP.UPD_FLAG=:x->UPD_FLAG
/* SqlMacros390-Define of CUSTOMERGROUP ***************************************/

#define CUSTOMERGROUP_ZEIGER_390 \
        :BRANCHNO,\
        :CUSTOMERGROUPNO,\
        :NAME,\
        :SALES_RESTR_PH,\
        :BLOCK_FLAG,\
        :BASISNATRA_FLAG,\
        :UPD_FLAG
#define CUSTOMERGROUP_UPDATE_390 \
        BRANCHNO=:BRANCHNO,\
        CUSTOMERGROUPNO=:CUSTOMERGROUPNO,\
        NAME=:NAME,\
        SALES_RESTR_PH=:SALES_RESTR_PH,\
        BLOCK_FLAG=:BLOCK_FLAG,\
        BASISNATRA_FLAG=:BASISNATRA_FLAG,\
        UPD_FLAG=:UPD_FLAG
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of CUSTOMERGROUP *******************************************/

#ifndef TRANSCLASS
typedef struct N_CUSTOMERGROUP {
    short BRANCHNO;
    short CUSTOMERGROUPNO;
    char NAME[31];
    char SALES_RESTR_PH[17];
    short BLOCK_FLAG;
    short BASISNATRA_FLAG;
    char UPD_FLAG[2];
} customergroupS;
#else /* TRANSCLASS */
typedef struct N_CUSTOMERGROUP {
    short BRANCHNO;
    short CUSTOMERGROUPNO;
    char NAME[31];
    char SALES_RESTR_PH[17];
    short BLOCK_FLAG;
    short BASISNATRA_FLAG;
    char UPD_FLAG[2];

    bool operator == (const N_CUSTOMERGROUP& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            CUSTOMERGROUPNO == right.CUSTOMERGROUPNO &&
            !strcmp(NAME, right.NAME) &&
            !strcmp(SALES_RESTR_PH, right.SALES_RESTR_PH) &&
            BLOCK_FLAG == right.BLOCK_FLAG &&
            BASISNATRA_FLAG == right.BASISNATRA_FLAG &&
            !strcmp(UPD_FLAG, right.UPD_FLAG)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        CUSTOMERGROUPNO = 0;
        strcpy(NAME, " " );
        strcpy(SALES_RESTR_PH, " " );
        BLOCK_FLAG = 0;
        BASISNATRA_FLAG = 0;
        strcpy(UPD_FLAG, " " );
#endif
    }
} customergroupS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of CUSTOMERGROUP *************************************/

struct S_CUSTOMERGROUP {
    char BRANCHNO[7];
    char CUSTOMERGROUPNO[7];
    char NAME[30 + 1];
    char SALES_RESTR_PH[16 + 1];
    char BLOCK_FLAG[7];
    char BASISNATRA_FLAG[7];
    char UPD_FLAG[1 + 1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of CUSTOMERGROUP ********************/

struct O_CUSTOMERGROUP {
    char BRANCHNO[7];
    char CUSTOMERGROUPNO[7];
    char NAME[30];
    char SALES_RESTR_PH[16];
    char BLOCK_FLAG[7];
    char BASISNATRA_FLAG[7];
    char UPD_FLAG[1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of CUSTOMERGROUP *******************************/

struct C_CUSTOMERGROUP {
    short BRANCHNO;
    short CUSTOMERGROUPNO;
    char NAME[31];
    char SALES_RESTR_PH[17];
    short BLOCK_FLAG;
    short BASISNATRA_FLAG;
    char UPD_FLAG;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of CUSTOMERGROUP *****************************/

struct I_CUSTOMERGROUP {
    short BRANCHNO;
    short CUSTOMERGROUPNO;
    short NAME;
    short SALES_RESTR_PH;
    short BLOCK_FLAG;
    short BASISNATRA_FLAG;
    short UPD_FLAG;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CUSTOMERGROUP ***************************************/

#if defined (BUF_DESC)
static struct buf_desc CUSTOMERGROUP_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 16, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CUSTOMERGROUP_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 16, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
};
#endif

/* description for datatypes of CUSTOMERGROUP *********************************/

 #define CUSTOMERGROUP_S390 \
         short BRANCHNO; \
         short CUSTOMERGROUPNO; \
         char NAME[31]; \
         char SALES_RESTR_PH[17]; \
         short BLOCK_FLAG; \
         short BASISNATRA_FLAG; \
         char UPD_FLAG; \



/* Copy-Function Struct to single Data CUSTOMERGROUP **************************/

 #define CUSTOMERGROUP_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         CUSTOMERGROUPNO=_x_->CUSTOMERGROUPNO;\
          strcpy(NAME,_x_->NAME);\
          strcpy(SALES_RESTR_PH,_x_->SALES_RESTR_PH);\
         BLOCK_FLAG=_x_->BLOCK_FLAG;\
         BASISNATRA_FLAG=_x_->BASISNATRA_FLAG;\
         UPD_FLAG=_x_->UPD_FLAG;\

 #define CUSTOMERGROUP_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->CUSTOMERGROUPNO=CUSTOMERGROUPNO;\
          strcpy(_x_->NAME,NAME);\
          strcpy(_x_->SALES_RESTR_PH,SALES_RESTR_PH);\
          _x_->BLOCK_FLAG=BLOCK_FLAG;\
          _x_->BASISNATRA_FLAG=BASISNATRA_FLAG;\
          _x_->UPD_FLAG=UPD_FLAG;\



/* FunctionNumber-Define of customergroup *************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of customergroup *********************************/


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

class CCUSTOMERGROUP : public ppDadeVirtual {
public:
    customergroupS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<customergroupS> lst; // class list

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
                     vector< customergroupS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     customergroupS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< customergroupS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<customergroupS>::iterator
                 beginList() { return lst.begin(); }
    vector<customergroupS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    short        GetCustomergroupno() const { return s.CUSTOMERGROUPNO; }
    const char*  GetName(ppString & t) const { t = s.NAME; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetSales_restr_ph(ppString & t) const { t = s.SALES_RESTR_PH; t.erasespace(ppString::END); return t.c_str(); }
    short        GetBlock_flag() const { return s.BLOCK_FLAG; }
    short        GetBasisnatra_flag() const { return s.BASISNATRA_FLAG; }
    char         GetUpd_flag() const { return s.UPD_FLAG[0]; }

    const customergroupS &
                 GetStruct() const { return s; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustomergroupno(short t) { s.CUSTOMERGROUPNO = t; }
    void         SetName(const ppString & t) { ppGStrCopy(s.NAME, t.c_str(), L_CUSTOMERGROUP_NAME); }
    void         SetSales_restr_ph(const ppString & t) { ppGStrCopy(s.SALES_RESTR_PH, t.c_str(), L_CUSTOMERGROUP_SALES_RESTR_PH); }
    void         SetBlock_flag(short t) { s.BLOCK_FLAG = t; }
    void         SetBasisnatra_flag(short t) { s.BASISNATRA_FLAG = t; }
    void         SetUpd_flag(char t) { s.UPD_FLAG[0] = t; s.UPD_FLAG[1] = '\0';}

    void         SetStruct(const customergroupS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCUSTOMERGROUP() {
        ::buf_default((void *)&s, CUSTOMERGROUP_BES, CUSTOMERGROUP_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCUSTOMERGROUP() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CUSTOMERGROUP_BES, CUSTOMERGROUP_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, CUSTOMERGROUP_BES, (int)CUSTOMERGROUP_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, CUSTOMERGROUP_BES, (int)CUSTOMERGROUP_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_CUSTOMERGROUP & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.NAME);
        ppGStripLast(d.SALES_RESTR_PH);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CUSTOMERGROUP_BES, (int)CUSTOMERGROUP_ANZ, error_msg);
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
/* CreateSqlStatement of CUSTOMERGROUP ****************************************/

 #define CUSTOMERGROUP_CREATE(x) EXEC SQL create table x (\
         BRANCHNO smallint default 0 not null,\
         CUSTOMERGROUPNO smallint default 0 not null,\
         NAME char(30) default " " not null,\
         SALES_RESTR_PH char(16) default " " not null,\
         BLOCK_FLAG smallint default 0 not null,\
         BASISNATRA_FLAG smallint default 0 not null,\
         UPD_FLAG char(1) default " " not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of CUSTOMERGROUP **************************************/

 #define CUSTOMERGROUP_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_customergroup_1 on _X_(\
              BranchNo,\
              customergroupno ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of CUSTOMERGROUP **************************************/

 #define CUSTOMERGROUP_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_customergroup_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
