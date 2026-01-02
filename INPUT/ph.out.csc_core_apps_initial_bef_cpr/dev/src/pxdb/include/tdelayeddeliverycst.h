#ifndef __PP_DELAYEDDELIVERYCST_H_
#define __PP_DELAYEDDELIVERYCST_H_

/******************************************************************************/
/* c:\prri\Headerfiles\delayeddeliverycst *************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of DELAYEDDELIVERYCST ****************************************/

#define L_DELAYEDDELIVERYCST_BRANCHNO 6
#define L_DELAYEDDELIVERYCST_CUSTOMERNO 11
#define L_DELAYEDDELIVERYCST_WEEKDAY 6
#define L_DELAYEDDELIVERYCST_TIME 11
#define L_DELAYEDDELIVERYCST_TOURID 6
#define L_DELAYEDDELIVERYCST_ACTIV 1
#define L_DELAYEDDELIVERYCST_DELAYEDWEEKDAY 6
#define L_DELAYEDDELIVERYCST_NARCOTIC 1
#define L_DELAYEDDELIVERYCST_COLDCHAIN 1
#define L_DELAYEDDELIVERYCST_COOL08 1
#define L_DELAYEDDELIVERYCST_COOL20 1
#define L_DELAYEDDELIVERYCST_DATEFROM 11
#define L_DELAYEDDELIVERYCST_DATETO 11

/* Length/Count-Define of DELAYEDDELIVERYCST **********************************/

#define LS_DELAYEDDELIVERYCST_BRANCHNO 5 + 1
#define LS_DELAYEDDELIVERYCST_CUSTOMERNO 10 + 1
#define LS_DELAYEDDELIVERYCST_WEEKDAY 5 + 1
#define LS_DELAYEDDELIVERYCST_TIME 10 + 1
#define LS_DELAYEDDELIVERYCST_TOURID 6 + 1
#define LS_DELAYEDDELIVERYCST_ACTIV 1 + 1
#define LS_DELAYEDDELIVERYCST_DELAYEDWEEKDAY 5 + 1
#define LS_DELAYEDDELIVERYCST_NARCOTIC 1 + 1
#define LS_DELAYEDDELIVERYCST_COLDCHAIN 1 + 1
#define LS_DELAYEDDELIVERYCST_COOL08 1 + 1
#define LS_DELAYEDDELIVERYCST_COOL20 1 + 1
#define LS_DELAYEDDELIVERYCST_DATEFROM 10 + 1
#define LS_DELAYEDDELIVERYCST_DATETO 10 + 1

#define DELAYEDDELIVERYCSTBRANCHNO 0
#define DELAYEDDELIVERYCSTCUSTOMERNO 1
#define DELAYEDDELIVERYCSTWEEKDAY 2
#define DELAYEDDELIVERYCSTTIME 3
#define DELAYEDDELIVERYCSTTOURID 4
#define DELAYEDDELIVERYCSTACTIV 5
#define DELAYEDDELIVERYCSTDELAYEDWEEKDAY 6
#define DELAYEDDELIVERYCSTNARCOTIC 7
#define DELAYEDDELIVERYCSTCOLDCHAIN 8
#define DELAYEDDELIVERYCSTCOOL08 9
#define DELAYEDDELIVERYCSTCOOL20 10
#define DELAYEDDELIVERYCSTDATEFROM 11
#define DELAYEDDELIVERYCSTDATETO 12

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define DELAYEDDELIVERYCST_H
#define DELAYEDDELIVERYCST_ANZ ( sizeof(DELAYEDDELIVERYCST_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of DELAYEDDELIVERYCST ********************************************/

#define DELAYEDDELIVERYCST_LISTE \
        DELAYEDDELIVERYCST.BRANCHNO,\
        DELAYEDDELIVERYCST.CUSTOMERNO,\
        DELAYEDDELIVERYCST.WEEKDAY,\
        DELAYEDDELIVERYCST.TIME,\
        DELAYEDDELIVERYCST.TOURID,\
        DELAYEDDELIVERYCST.ACTIV,\
        DELAYEDDELIVERYCST.DELAYEDWEEKDAY,\
        DELAYEDDELIVERYCST.NARCOTIC,\
        DELAYEDDELIVERYCST.COLDCHAIN,\
        DELAYEDDELIVERYCST.COOL08,\
        DELAYEDDELIVERYCST.COOL20,\
        DELAYEDDELIVERYCST.DATEFROM,\
        DELAYEDDELIVERYCST.DATETO
#define DELAYEDDELIVERYCST_LISTE_390 \
        BRANCHNO,\
        CUSTOMERNO,\
        WEEKDAY,\
        TIME,\
        TOURID,\
        ACTIV,\
        DELAYEDWEEKDAY,\
        NARCOTIC,\
        COLDCHAIN,\
        COOL08,\
        COOL20,\
        DATEFROM,\
        DATETO
#define DELAYEDDELIVERYCST_PLISTE \
        "DELAYEDDELIVERYCST.BRANCHNO,"\
        "DELAYEDDELIVERYCST.CUSTOMERNO,"\
        "DELAYEDDELIVERYCST.WEEKDAY,"\
        "DELAYEDDELIVERYCST.TIME,"\
        "DELAYEDDELIVERYCST.TOURID,"\
        "DELAYEDDELIVERYCST.ACTIV,"\
        "DELAYEDDELIVERYCST.DELAYEDWEEKDAY,"\
        "DELAYEDDELIVERYCST.NARCOTIC,"\
        "DELAYEDDELIVERYCST.COLDCHAIN,"\
        "DELAYEDDELIVERYCST.COOL08,"\
        "DELAYEDDELIVERYCST.COOL20,"\
        "DELAYEDDELIVERYCST.DATEFROM,"\
        "DELAYEDDELIVERYCST.DATETO"
#define DELAYEDDELIVERYCST_PELISTE \
        "BRANCHNO,"\
        "CUSTOMERNO,"\
        "WEEKDAY,"\
        "TIME,"\
        "TOURID,"\
        "ACTIV,"\
        "DELAYEDWEEKDAY,"\
        "NARCOTIC,"\
        "COLDCHAIN,"\
        "COOL08,"\
        "COOL20,"\
        "DATEFROM,"\
        "DATETO"
#define DELAYEDDELIVERYCST_UPDLISTE \
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "WEEKDAY=?,"\
        "TIME=?,"\
        "TOURID=?,"\
        "ACTIV=?,"\
        "DELAYEDWEEKDAY=?,"\
        "NARCOTIC=?,"\
        "COLDCHAIN=?,"\
        "COOL08=?,"\
        "COOL20=?,"\
        "DATEFROM=?,"\
        "DATETO=?"
/* SqlMacros-Define of DELAYEDDELIVERYCST *************************************/

#define DELAYEDDELIVERYCST_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->WEEKDAY,\
        :x->TIME,\
        :x->TOURID,\
        :x->ACTIV,\
        :x->DELAYEDWEEKDAY,\
        :x->NARCOTIC,\
        :x->COLDCHAIN,\
        :x->COOL08,\
        :x->COOL20,\
        :x->DATEFROM,\
        :x->DATETO
#define DELAYEDDELIVERYCST_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->WEEKDAY,\
        :x->TIME,\
        :x->TOURID,\
        :x->ACTIV,\
        :x->DELAYEDWEEKDAY,\
        :x->NARCOTIC,\
        :x->COLDCHAIN,\
        :x->COOL08,\
        :x->COOL20,\
        :x->DATEFROM,\
        :x->DATETO
#define DELAYEDDELIVERYCST_UPDATE(x) \
        DELAYEDDELIVERYCST.BRANCHNO=:x->BRANCHNO,\
        DELAYEDDELIVERYCST.CUSTOMERNO=:x->CUSTOMERNO,\
        DELAYEDDELIVERYCST.WEEKDAY=:x->WEEKDAY,\
        DELAYEDDELIVERYCST.TIME=:x->TIME,\
        DELAYEDDELIVERYCST.TOURID=:x->TOURID,\
        DELAYEDDELIVERYCST.ACTIV=:x->ACTIV,\
        DELAYEDDELIVERYCST.DELAYEDWEEKDAY=:x->DELAYEDWEEKDAY,\
        DELAYEDDELIVERYCST.NARCOTIC=:x->NARCOTIC,\
        DELAYEDDELIVERYCST.COLDCHAIN=:x->COLDCHAIN,\
        DELAYEDDELIVERYCST.COOL08=:x->COOL08,\
        DELAYEDDELIVERYCST.COOL20=:x->COOL20,\
        DELAYEDDELIVERYCST.DATEFROM=:x->DATEFROM,\
        DELAYEDDELIVERYCST.DATETO=:x->DATETO
/* SqlMacros390-Define of DELAYEDDELIVERYCST **********************************/

#define DELAYEDDELIVERYCST_ZEIGER_390 \
        :BRANCHNO,\
        :CUSTOMERNO,\
        :WEEKDAY,\
        :TIME,\
        :TOURID,\
        :ACTIV,\
        :DELAYEDWEEKDAY,\
        :NARCOTIC,\
        :COLDCHAIN,\
        :COOL08,\
        :COOL20,\
        :DATEFROM,\
        :DATETO
#define DELAYEDDELIVERYCST_UPDATE_390 \
        BRANCHNO=:BRANCHNO,\
        CUSTOMERNO=:CUSTOMERNO,\
        WEEKDAY=:WEEKDAY,\
        TIME=:TIME,\
        TOURID=:TOURID,\
        ACTIV=:ACTIV,\
        DELAYEDWEEKDAY=:DELAYEDWEEKDAY,\
        NARCOTIC=:NARCOTIC,\
        COLDCHAIN=:COLDCHAIN,\
        COOL08=:COOL08,\
        COOL20=:COOL20,\
        DATEFROM=:DATEFROM,\
        DATETO=:DATETO
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of DELAYEDDELIVERYCST **************************************/

#ifndef TRANSCLASS
typedef struct N_DELAYEDDELIVERYCST {
    short BRANCHNO;
    long CUSTOMERNO;
    short WEEKDAY;
    long TIME;
    char TOURID[7];
    char ACTIV[2];
    short DELAYEDWEEKDAY;
    char NARCOTIC[2];
    char COLDCHAIN[2];
    char COOL08[2];
    char COOL20[2];
    long DATEFROM;
    long DATETO;
} delayeddeliverycstS;
#else /* TRANSCLASS */
typedef struct N_DELAYEDDELIVERYCST {
    short BRANCHNO;
    long CUSTOMERNO;
    short WEEKDAY;
    long TIME;
    char TOURID[7];
    char ACTIV[2];
    short DELAYEDWEEKDAY;
    char NARCOTIC[2];
    char COLDCHAIN[2];
    char COOL08[2];
    char COOL20[2];
    long DATEFROM;
    long DATETO;

    bool operator == (const N_DELAYEDDELIVERYCST& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            CUSTOMERNO == right.CUSTOMERNO &&
            WEEKDAY == right.WEEKDAY &&
            TIME == right.TIME &&
            !strcmp(TOURID, right.TOURID) &&
            !strcmp(ACTIV, right.ACTIV) &&
            DELAYEDWEEKDAY == right.DELAYEDWEEKDAY &&
            !strcmp(NARCOTIC, right.NARCOTIC) &&
            !strcmp(COLDCHAIN, right.COLDCHAIN) &&
            !strcmp(COOL08, right.COOL08) &&
            !strcmp(COOL20, right.COOL20) &&
            DATEFROM == right.DATEFROM &&
            DATETO == right.DATETO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        CUSTOMERNO = 0;
        WEEKDAY = 0;
        TIME = 0;
        strcpy(TOURID, " " );
        strcpy(ACTIV, " " );
        DELAYEDWEEKDAY = 0;
        strcpy(NARCOTIC, " " );
        strcpy(COLDCHAIN, " " );
        strcpy(COOL08, " " );
        strcpy(COOL20, " " );
        DATEFROM = 0;
        DATETO = 0;
#endif
    }
} delayeddeliverycstS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of DELAYEDDELIVERYCST ********************************/

struct S_DELAYEDDELIVERYCST {
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char WEEKDAY[7];
    char TIME[11];
    char TOURID[6 + 1];
    char ACTIV[1 + 1];
    char DELAYEDWEEKDAY[7];
    char NARCOTIC[1 + 1];
    char COLDCHAIN[1 + 1];
    char COOL08[1 + 1];
    char COOL20[1 + 1];
    char DATEFROM[11];
    char DATETO[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of DELAYEDDELIVERYCST ***************/

struct O_DELAYEDDELIVERYCST {
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char WEEKDAY[7];
    char TIME[11];
    char TOURID[6];
    char ACTIV[1];
    char DELAYEDWEEKDAY[7];
    char NARCOTIC[1];
    char COLDCHAIN[1];
    char COOL08[1];
    char COOL20[1];
    char DATEFROM[11];
    char DATETO[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of DELAYEDDELIVERYCST **************************/

struct C_DELAYEDDELIVERYCST {
    short BRANCHNO;
    long CUSTOMERNO;
    short WEEKDAY;
    long TIME;
    char TOURID[7];
    char ACTIV;
    short DELAYEDWEEKDAY;
    char NARCOTIC;
    char COLDCHAIN;
    char COOL08;
    char COOL20;
    long DATEFROM;
    long DATETO;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of DELAYEDDELIVERYCST ************************/

struct I_DELAYEDDELIVERYCST {
    short BRANCHNO;
    short CUSTOMERNO;
    short WEEKDAY;
    short TIME;
    short TOURID;
    short ACTIV;
    short DELAYEDWEEKDAY;
    short NARCOTIC;
    short COLDCHAIN;
    short COOL08;
    short COOL20;
    short DATEFROM;
    short DATETO;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of DELAYEDDELIVERYCST **********************************/

#if defined (BUF_DESC)
static struct buf_desc DELAYEDDELIVERYCST_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc DELAYEDDELIVERYCST_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* description for datatypes of DELAYEDDELIVERYCST ****************************/

 #define DELAYEDDELIVERYCST_S390 \
         short BRANCHNO; \
         long CUSTOMERNO; \
         short WEEKDAY; \
         long TIME; \
         char TOURID[7]; \
         char ACTIV; \
         short DELAYEDWEEKDAY; \
         char NARCOTIC; \
         char COLDCHAIN; \
         char COOL08; \
         char COOL20; \
         long DATEFROM; \
         long DATETO; \



/* Copy-Function Struct to single Data DELAYEDDELIVERYCST *********************/

 #define DELAYEDDELIVERYCST_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
         WEEKDAY=_x_->WEEKDAY;\
         TIME=_x_->TIME;\
          strcpy(TOURID,_x_->TOURID);\
         ACTIV=_x_->ACTIV;\
         DELAYEDWEEKDAY=_x_->DELAYEDWEEKDAY;\
         NARCOTIC=_x_->NARCOTIC;\
         COLDCHAIN=_x_->COLDCHAIN;\
         COOL08=_x_->COOL08;\
         COOL20=_x_->COOL20;\
         DATEFROM=_x_->DATEFROM;\
         DATETO=_x_->DATETO;\

 #define DELAYEDDELIVERYCST_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->WEEKDAY=WEEKDAY;\
          _x_->TIME=TIME;\
          strcpy(_x_->TOURID,TOURID);\
          _x_->ACTIV=ACTIV;\
          _x_->DELAYEDWEEKDAY=DELAYEDWEEKDAY;\
          _x_->NARCOTIC=NARCOTIC;\
          _x_->COLDCHAIN=COLDCHAIN;\
          _x_->COOL08=COOL08;\
          _x_->COOL20=COOL20;\
          _x_->DATEFROM=DATEFROM;\
          _x_->DATETO=DATETO;\



/* FunctionNumber-Define of delayeddeliverycst ********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of delayeddeliverycst ****************************/


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

class CDELAYEDDELIVERYCST : public ppDadeVirtual {
public:
    delayeddeliverycstS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<delayeddeliverycstS> lst; // class list

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
                     vector< delayeddeliverycstS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     delayeddeliverycstS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< delayeddeliverycstS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<delayeddeliverycstS>::iterator
                 beginList() { return lst.begin(); }
    vector<delayeddeliverycstS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    short        GetWeekday() const { return s.WEEKDAY; }
    long         GetTime() const { return s.TIME; }
    const char*  GetTourid(ppString & t) const { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
    char         GetActiv() const { return s.ACTIV[0]; }
    short        GetDelayedweekday() const { return s.DELAYEDWEEKDAY; }
    char         GetNarcotic() const { return s.NARCOTIC[0]; }
    char         GetColdchain() const { return s.COLDCHAIN[0]; }
    char         GetCool08() const { return s.COOL08[0]; }
    char         GetCool20() const { return s.COOL20[0]; }
    long         GetDatefrom() const { return s.DATEFROM; }
    long         GetDateto() const { return s.DATETO; }

    const delayeddeliverycstS &
                 GetStruct() const { return s; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetWeekday(short t) { s.WEEKDAY = t; }
    void         SetTime(long t) { s.TIME = t; }
    void         SetTourid(const ppString & t) { ppGStrCopy(s.TOURID, t.c_str(), L_DELAYEDDELIVERYCST_TOURID); }
    void         SetActiv(char t) { s.ACTIV[0] = t; s.ACTIV[1] = '\0';}
    void         SetDelayedweekday(short t) { s.DELAYEDWEEKDAY = t; }
    void         SetNarcotic(char t) { s.NARCOTIC[0] = t; s.NARCOTIC[1] = '\0';}
    void         SetColdchain(char t) { s.COLDCHAIN[0] = t; s.COLDCHAIN[1] = '\0';}
    void         SetCool08(char t) { s.COOL08[0] = t; s.COOL08[1] = '\0';}
    void         SetCool20(char t) { s.COOL20[0] = t; s.COOL20[1] = '\0';}
    void         SetDatefrom(long t) { s.DATEFROM = t; }
    void         SetDateto(long t) { s.DATETO = t; }

    void         SetStruct(const delayeddeliverycstS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CDELAYEDDELIVERYCST() {
        ::buf_default((void *)&s, DELAYEDDELIVERYCST_BES, DELAYEDDELIVERYCST_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CDELAYEDDELIVERYCST() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, DELAYEDDELIVERYCST_BES, DELAYEDDELIVERYCST_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, DELAYEDDELIVERYCST_BES, (int)DELAYEDDELIVERYCST_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, DELAYEDDELIVERYCST_BES, (int)DELAYEDDELIVERYCST_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_DELAYEDDELIVERYCST & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.TOURID);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, DELAYEDDELIVERYCST_BES, (int)DELAYEDDELIVERYCST_ANZ, error_msg);
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
/* CreateSqlStatement of DELAYEDDELIVERYCST ***********************************/

 #define DELAYEDDELIVERYCST_CREATE(x) EXEC SQL create table x (\
         BRANCHNO smallint default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         WEEKDAY smallint default 0 not null,\
         TIME integer default 0 not null,\
         TOURID char(6) default " " not null,\
         ACTIV char(1) default " " not null,\
         DELAYEDWEEKDAY smallint default 0 not null,\
         NARCOTIC char(1) default " " not null,\
         COLDCHAIN char(1) default " " not null,\
         COOL08 char(1) default " " not null,\
         COOL20 char(1) default " " not null,\
         DATEFROM integer default 0 not null,\
         DATETO integer default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of DELAYEDDELIVERYCST *********************************/

 #define DELAYEDDELIVERYCST_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_delayedcst_1 on _X_(\
              BranchNo,\
              CustomerNo,\
              weekday,\
              DateFrom ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of DELAYEDDELIVERYCST *********************************/

 #define DELAYEDDELIVERYCST_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_delayedcst_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
