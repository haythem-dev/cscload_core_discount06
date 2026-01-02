#ifndef __PP_CUSTGRPFLAGTYPES_H_
#define __PP_CUSTGRPFLAGTYPES_H_

/******************************************************************************/
/* d:\prj\DF\UNIX\loadcustgroups\custgrpflagtypes *****************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of CUSTGRPFLAGTYPES ******************************************/

#define L_CUSTGRPFLAGTYPES_BRANCHNO 6
#define L_CUSTGRPFLAGTYPES_CUSTGRPFLAGTYPE 6
#define L_CUSTGRPFLAGTYPES_DESCRIPTION 254
#define L_CUSTGRPFLAGTYPES_INDEX_DKKGR 6
#define L_CUSTGRPFLAGTYPES_UPD_FLAG 1

/* Length/Count-Define of CUSTGRPFLAGTYPES ************************************/

#define LS_CUSTGRPFLAGTYPES_BRANCHNO 5 + 1
#define LS_CUSTGRPFLAGTYPES_CUSTGRPFLAGTYPE 5 + 1
#define LS_CUSTGRPFLAGTYPES_DESCRIPTION 254 + 1
#define LS_CUSTGRPFLAGTYPES_INDEX_DKKGR 5 + 1
#define LS_CUSTGRPFLAGTYPES_UPD_FLAG 1 + 1

#define CUSTGRPFLAGTYPESBRANCHNO 0
#define CUSTGRPFLAGTYPESCUSTGRPFLAGTYPE 1
#define CUSTGRPFLAGTYPESDESCRIPTION 2
#define CUSTGRPFLAGTYPESINDEX_DKKGR 3
#define CUSTGRPFLAGTYPESUPD_FLAG 4

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define CUSTGRPFLAGTYPES_H
#define CUSTGRPFLAGTYPES_ANZ ( sizeof(CUSTGRPFLAGTYPES_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of CUSTGRPFLAGTYPES **********************************************/

#define CUSTGRPFLAGTYPES_LISTE \
        CUSTGRPFLAGTYPES.BRANCHNO,\
        CUSTGRPFLAGTYPES.CUSTGRPFLAGTYPE,\
        CUSTGRPFLAGTYPES.DESCRIPTION,\
        CUSTGRPFLAGTYPES.INDEX_DKKGR,\
        CUSTGRPFLAGTYPES.UPD_FLAG
#define CUSTGRPFLAGTYPES_LISTE_390 \
        BRANCHNO,\
        CUSTGRPFLAGTYPE,\
        DESCRIPTION,\
        INDEX_DKKGR,\
        UPD_FLAG
#define CUSTGRPFLAGTYPES_PLISTE \
        "CUSTGRPFLAGTYPES.BRANCHNO,"\
        "CUSTGRPFLAGTYPES.CUSTGRPFLAGTYPE,"\
        "CUSTGRPFLAGTYPES.DESCRIPTION,"\
        "CUSTGRPFLAGTYPES.INDEX_DKKGR,"\
        "CUSTGRPFLAGTYPES.UPD_FLAG"
#define CUSTGRPFLAGTYPES_PELISTE \
        "BRANCHNO,"\
        "CUSTGRPFLAGTYPE,"\
        "DESCRIPTION,"\
        "INDEX_DKKGR,"\
        "UPD_FLAG"
#define CUSTGRPFLAGTYPES_UPDLISTE \
        "BRANCHNO=?,"\
        "CUSTGRPFLAGTYPE=?,"\
        "DESCRIPTION=?,"\
        "INDEX_DKKGR=?,"\
        "UPD_FLAG=?"
/* SqlMacros-Define of CUSTGRPFLAGTYPES ***************************************/

#define CUSTGRPFLAGTYPES_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->CUSTGRPFLAGTYPE,\
        :x->DESCRIPTION,\
        :x->INDEX_DKKGR,\
        :x->UPD_FLAG
#define CUSTGRPFLAGTYPES_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->CUSTGRPFLAGTYPE,\
        :x->DESCRIPTION,\
        :x->INDEX_DKKGR,\
        :x->UPD_FLAG
#define CUSTGRPFLAGTYPES_UPDATE(x) \
        CUSTGRPFLAGTYPES.BRANCHNO=:x->BRANCHNO,\
        CUSTGRPFLAGTYPES.CUSTGRPFLAGTYPE=:x->CUSTGRPFLAGTYPE,\
        CUSTGRPFLAGTYPES.DESCRIPTION=:x->DESCRIPTION,\
        CUSTGRPFLAGTYPES.INDEX_DKKGR=:x->INDEX_DKKGR,\
        CUSTGRPFLAGTYPES.UPD_FLAG=:x->UPD_FLAG
/* SqlMacros390-Define of CUSTGRPFLAGTYPES ************************************/

#define CUSTGRPFLAGTYPES_ZEIGER_390 \
        :BRANCHNO,\
        :CUSTGRPFLAGTYPE,\
        :DESCRIPTION,\
        :INDEX_DKKGR,\
        :UPD_FLAG
#define CUSTGRPFLAGTYPES_UPDATE_390 \
        BRANCHNO=:BRANCHNO,\
        CUSTGRPFLAGTYPE=:CUSTGRPFLAGTYPE,\
        DESCRIPTION=:DESCRIPTION,\
        INDEX_DKKGR=:INDEX_DKKGR,\
        UPD_FLAG=:UPD_FLAG
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of CUSTGRPFLAGTYPES ****************************************/

#ifndef TRANSCLASS
typedef struct N_CUSTGRPFLAGTYPES {
    short BRANCHNO;
    short CUSTGRPFLAGTYPE;
    char DESCRIPTION[255];
    short INDEX_DKKGR;
    char UPD_FLAG[2];
} custgrpflagtypesS;
#else /* TRANSCLASS */
typedef struct N_CUSTGRPFLAGTYPES {
    short BRANCHNO;
    short CUSTGRPFLAGTYPE;
    char DESCRIPTION[255];
    short INDEX_DKKGR;
    char UPD_FLAG[2];

    bool operator == (const N_CUSTGRPFLAGTYPES& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            CUSTGRPFLAGTYPE == right.CUSTGRPFLAGTYPE &&
            !strcmp(DESCRIPTION, right.DESCRIPTION) &&
            INDEX_DKKGR == right.INDEX_DKKGR &&
            !strcmp(UPD_FLAG, right.UPD_FLAG)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        CUSTGRPFLAGTYPE = 0;
        strcpy(DESCRIPTION, " " );
        INDEX_DKKGR = 0;
        strcpy(UPD_FLAG, " " );
#endif
    }
} custgrpflagtypesS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of CUSTGRPFLAGTYPES **********************************/

struct S_CUSTGRPFLAGTYPES {
    char BRANCHNO[7];
    char CUSTGRPFLAGTYPE[7];
    char DESCRIPTION[254 + 1];
    char INDEX_DKKGR[7];
    char UPD_FLAG[1 + 1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of CUSTGRPFLAGTYPES *****************/

struct O_CUSTGRPFLAGTYPES {
    char BRANCHNO[7];
    char CUSTGRPFLAGTYPE[7];
    char DESCRIPTION[254];
    char INDEX_DKKGR[7];
    char UPD_FLAG[1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of CUSTGRPFLAGTYPES ****************************/

struct C_CUSTGRPFLAGTYPES {
    short BRANCHNO;
    short CUSTGRPFLAGTYPE;
    char DESCRIPTION[255];
    short INDEX_DKKGR;
    char UPD_FLAG;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of CUSTGRPFLAGTYPES **************************/

struct I_CUSTGRPFLAGTYPES {
    short BRANCHNO;
    short CUSTGRPFLAGTYPE;
    short DESCRIPTION;
    short INDEX_DKKGR;
    short UPD_FLAG;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CUSTGRPFLAGTYPES ************************************/

#if defined (BUF_DESC)
static struct buf_desc CUSTGRPFLAGTYPES_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 254, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CUSTGRPFLAGTYPES_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 254, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
};
#endif

/* description for datatypes of CUSTGRPFLAGTYPES ******************************/

 #define CUSTGRPFLAGTYPES_S390 \
         short BRANCHNO; \
         short CUSTGRPFLAGTYPE; \
         char DESCRIPTION[255]; \
         short INDEX_DKKGR; \
         char UPD_FLAG; \



/* Copy-Function Struct to single Data CUSTGRPFLAGTYPES ***********************/

 #define CUSTGRPFLAGTYPES_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         CUSTGRPFLAGTYPE=_x_->CUSTGRPFLAGTYPE;\
          strcpy(DESCRIPTION,_x_->DESCRIPTION);\
         INDEX_DKKGR=_x_->INDEX_DKKGR;\
         UPD_FLAG=_x_->UPD_FLAG;\

 #define CUSTGRPFLAGTYPES_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->CUSTGRPFLAGTYPE=CUSTGRPFLAGTYPE;\
          strcpy(_x_->DESCRIPTION,DESCRIPTION);\
          _x_->INDEX_DKKGR=INDEX_DKKGR;\
          _x_->UPD_FLAG=UPD_FLAG;\



/* FunctionNumber-Define of custgrpflagtypes **********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of custgrpflagtypes ******************************/


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

class CCUSTGRPFLAGTYPES : public ppDadeVirtual {
public:
    custgrpflagtypesS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<custgrpflagtypesS> lst; // class list

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
                     vector< custgrpflagtypesS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     custgrpflagtypesS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< custgrpflagtypesS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<custgrpflagtypesS>::iterator
                 beginList() { return lst.begin(); }
    vector<custgrpflagtypesS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    short        GetCustgrpflagtype() const { return s.CUSTGRPFLAGTYPE; }
    const char*  GetDescription(ppString & t) const { t = s.DESCRIPTION; t.erasespace(ppString::END); return t.c_str(); }
    short        GetIndex_dkkgr() const { return s.INDEX_DKKGR; }
    char         GetUpd_flag() const { return s.UPD_FLAG[0]; }

    const custgrpflagtypesS &
                 GetStruct() const { return s; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustgrpflagtype(short t) { s.CUSTGRPFLAGTYPE = t; }
    void         SetDescription(const ppString & t) { ppGStrCopy(s.DESCRIPTION, t.c_str(), L_CUSTGRPFLAGTYPES_DESCRIPTION); }
    void         SetIndex_dkkgr(short t) { s.INDEX_DKKGR = t; }
    void         SetUpd_flag(char t) { s.UPD_FLAG[0] = t; s.UPD_FLAG[1] = '\0';}

    void         SetStruct(const custgrpflagtypesS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCUSTGRPFLAGTYPES() {
        ::buf_default((void *)&s, CUSTGRPFLAGTYPES_BES, CUSTGRPFLAGTYPES_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCUSTGRPFLAGTYPES() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CUSTGRPFLAGTYPES_BES, CUSTGRPFLAGTYPES_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, CUSTGRPFLAGTYPES_BES, (int)CUSTGRPFLAGTYPES_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, CUSTGRPFLAGTYPES_BES, (int)CUSTGRPFLAGTYPES_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_CUSTGRPFLAGTYPES & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.DESCRIPTION);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CUSTGRPFLAGTYPES_BES, (int)CUSTGRPFLAGTYPES_ANZ, error_msg);
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
/* CreateSqlStatement of CUSTGRPFLAGTYPES *************************************/

 #define CUSTGRPFLAGTYPES_CREATE(x) EXEC SQL create table x (\
         BRANCHNO smallint default 0 not null,\
         CUSTGRPFLAGTYPE smallint default 0 not null,\
         DESCRIPTION varchar(254,0) default " " not null,\
         INDEX_DKKGR smallint default 0 not null,\
         UPD_FLAG char(1) default " " not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of CUSTGRPFLAGTYPES ***********************************/

 #define CUSTGRPFLAGTYPES_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_custgrpflagtypes_1 on _X_(\
              BranchNo,\
              custgrpflagtype ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of CUSTGRPFLAGTYPES ***********************************/

 #define CUSTGRPFLAGTYPES_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_custgrpflagtypes_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
