#ifndef __PP_NARCGROUP_H_
#define __PP_NARCGROUP_H_

/******************************************************************************/
/* c:\prri\Headerfiles\narcgroup **********************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of NARCGROUP *************************************************/

#define L_NARCGROUP_BTM_GRUPPE 5
#define L_NARCGROUP_BTM_BEZ 30
#define L_NARCGROUP_BTM_GEHALT 9
#define N_NARCGROUP_BTM_GEHALT 4
#define L_NARCGROUP_BTM_EINHEIT 9

/* Length/Count-Define of NARCGROUP *******************************************/

#define LS_NARCGROUP_BTM_GRUPPE 5 + 1
#define LS_NARCGROUP_BTM_BEZ 30 + 1
#define LS_NARCGROUP_BTM_GEHALT 9 + 2
#define LS_NARCGROUP_BTM_EINHEIT 9 + 1

#define NARCGROUPBTM_GRUPPE 0
#define NARCGROUPBTM_BEZ 1
#define NARCGROUPBTM_GEHALT 2
#define NARCGROUPBTM_EINHEIT 3

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define NARCGROUP_H
#define NARCGROUP_ANZ ( sizeof(NARCGROUP_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of NARCGROUP *****************************************************/

#define NARCGROUP_LISTE \
        ZDKBTM.BTM_GRUPPE,\
        ZDKBTM.BTM_BEZ,\
        ZDKBTM.BTM_GEHALT,\
        ZDKBTM.BTM_EINHEIT
#define NARCGROUP_LISTE_390 \
        BTM_GRUPPE,\
        BTM_BEZ,\
        BTM_GEHALT,\
        BTM_EINHEIT
#define NARCGROUP_PLISTE \
        "ZDKBTM.BTM_GRUPPE,"\
        "ZDKBTM.BTM_BEZ,"\
        "ZDKBTM.BTM_GEHALT,"\
        "ZDKBTM.BTM_EINHEIT"
#define NARCGROUP_PELISTE \
        "BTM_GRUPPE,"\
        "BTM_BEZ,"\
        "BTM_GEHALT,"\
        "BTM_EINHEIT"
#define NARCGROUP_UPDLISTE \
        "BTM_GRUPPE=?,"\
        "BTM_BEZ=?,"\
        "BTM_GEHALT=?,"\
        "BTM_EINHEIT=?"
/* SqlMacros-Define of NARCGROUP **********************************************/

#define NARCGROUP_ZEIGER(x) \
        :x->BTM_GRUPPE,\
        :x->BTM_BEZ,\
        :x->BTM_GEHALT,\
        :x->BTM_EINHEIT
#define NARCGROUP_ZEIGERSEL(x) \
        :x->BTM_GRUPPE,\
        :x->BTM_BEZ,\
        :x->BTM_GEHALT,\
        :x->BTM_EINHEIT
#define NARCGROUP_UPDATE(x) \
        ZDKBTM.BTM_GRUPPE=:x->BTM_GRUPPE,\
        ZDKBTM.BTM_BEZ=:x->BTM_BEZ,\
        ZDKBTM.BTM_GEHALT=:x->BTM_GEHALT,\
        ZDKBTM.BTM_EINHEIT=:x->BTM_EINHEIT
/* SqlMacros390-Define of NARCGROUP *******************************************/

#define NARCGROUP_ZEIGER_390 \
        :BTM_GRUPPE,\
        :BTM_BEZ,\
        :BTM_GEHALT,\
        :BTM_EINHEIT
#define NARCGROUP_UPDATE_390 \
        BTM_GRUPPE=:BTM_GRUPPE,\
        BTM_BEZ=:BTM_BEZ,\
        BTM_GEHALT=:BTM_GEHALT,\
        BTM_EINHEIT=:BTM_EINHEIT
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of NARCGROUP ***********************************************/

#ifndef TRANSCLASS
typedef struct N_NARCGROUP {
    char BTM_GRUPPE[6];
    char BTM_BEZ[31];
    double BTM_GEHALT;
    char BTM_EINHEIT[10];
} narcgroupS;
#else /* TRANSCLASS */
typedef struct N_NARCGROUP {
    char BTM_GRUPPE[6];
    char BTM_BEZ[31];
    double BTM_GEHALT;
    char BTM_EINHEIT[10];

    bool operator == (const N_NARCGROUP& right) const {
        return (
            !strcmp(BTM_GRUPPE, right.BTM_GRUPPE) &&
            !strcmp(BTM_BEZ, right.BTM_BEZ) &&
            BTM_GEHALT == right.BTM_GEHALT &&
            !strcmp(BTM_EINHEIT, right.BTM_EINHEIT)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        strcpy(BTM_GRUPPE, " " );
        strcpy(BTM_BEZ, " " );
        BTM_GEHALT = 0;
        strcpy(BTM_EINHEIT, " " );
#endif
    }
} narcgroupS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of NARCGROUP *****************************************/

struct S_NARCGROUP {
    char BTM_GRUPPE[5 + 1];
    char BTM_BEZ[30 + 1];
    char BTM_GEHALT[9 + 2];
    char BTM_EINHEIT[9 + 1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of NARCGROUP ************************/

struct O_NARCGROUP {
    char BTM_GRUPPE[5];
    char BTM_BEZ[30];
    char BTM_GEHALT[9];
    char BTM_EINHEIT[9];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of NARCGROUP ***********************************/

struct C_NARCGROUP {
    char BTM_GRUPPE[6];
    char BTM_BEZ[31];
    double BTM_GEHALT;
    char BTM_EINHEIT[10];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of NARCGROUP *********************************/

struct I_NARCGROUP {
    short BTM_GRUPPE;
    short BTM_BEZ;
    short BTM_GEHALT;
    short BTM_EINHEIT;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of NARCGROUP *******************************************/

#if defined (BUF_DESC)
static struct buf_desc NARCGROUP_BES [] = {
   { TYP_C, 5, 0 },
   { TYP_C, 30, 0 },
   { TYP_D, 9, 4 },
   { TYP_C, 9, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc NARCGROUP_BES [] = {
   { TYP_C, 5, 0 },
   { TYP_C, 30, 0 },
   { TYP_D, 9, 4 },
   { TYP_C, 9, 0 },
};
#endif

/* description for datatypes of NARCGROUP *************************************/

 #define NARCGROUP_S390 \
         char BTM_GRUPPE[6]; \
         char BTM_BEZ[31]; \
         double BTM_GEHALT; \
         char BTM_EINHEIT[10]; \



/* Copy-Function Struct to single Data NARCGROUP ******************************/

 #define NARCGROUP_S390_COPY_TO_SINGLE(_x_) \
          strcpy(BTM_GRUPPE,_x_->BTM_GRUPPE);\
          strcpy(BTM_BEZ,_x_->BTM_BEZ);\
         BTM_GEHALT=_x_->BTM_GEHALT;\
          strcpy(BTM_EINHEIT,_x_->BTM_EINHEIT);\

 #define NARCGROUP_S390_COPY_TO_STRUCT(_x_) \
          strcpy(_x_->BTM_GRUPPE,BTM_GRUPPE);\
          strcpy(_x_->BTM_BEZ,BTM_BEZ);\
          _x_->BTM_GEHALT=BTM_GEHALT;\
          strcpy(_x_->BTM_EINHEIT,BTM_EINHEIT);\



/* FunctionNumber-Define of narcgroup *****************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of narcgroup *************************************/


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

class CNARCGROUP : public ppDadeVirtual {
public:
    narcgroupS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<narcgroupS> lst; // class list

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
                     vector< narcgroupS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     narcgroupS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< narcgroupS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<narcgroupS>::iterator
                 beginList() { return lst.begin(); }
    vector<narcgroupS>::iterator
                 endList  () { return lst.end  (); }

    const char*  GetBtm_gruppe(ppString & t) const { t = s.BTM_GRUPPE; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetBtm_bez(ppString & t) const { t = s.BTM_BEZ; t.erasespace(ppString::END); return t.c_str(); }
    double       GetBtm_gehalt() const { return s.BTM_GEHALT; }
    const char*  GetBtm_einheit(ppString & t) const { t = s.BTM_EINHEIT; t.erasespace(ppString::END); return t.c_str(); }

    const narcgroupS &
                 GetStruct() const { return s; }
    void         SetBtm_gruppe(const ppString & t) { ppGStrCopy(s.BTM_GRUPPE, t.c_str(), L_NARCGROUP_BTM_GRUPPE); }
    void         SetBtm_bez(const ppString & t) { ppGStrCopy(s.BTM_BEZ, t.c_str(), L_NARCGROUP_BTM_BEZ); }
    void         SetBtm_gehalt(double t) { s.BTM_GEHALT = t; }
    void         SetBtm_einheit(const ppString & t) { ppGStrCopy(s.BTM_EINHEIT, t.c_str(), L_NARCGROUP_BTM_EINHEIT); }

    void         SetStruct(const narcgroupS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CNARCGROUP() {
        ::buf_default((void *)&s, NARCGROUP_BES, NARCGROUP_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CNARCGROUP() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, NARCGROUP_BES, NARCGROUP_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, NARCGROUP_BES, (int)NARCGROUP_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, NARCGROUP_BES, (int)NARCGROUP_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_NARCGROUP & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.BTM_GRUPPE);
        ppGStripLast(d.BTM_BEZ);
        ppGStripLast(d.BTM_EINHEIT);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, NARCGROUP_BES, (int)NARCGROUP_ANZ, error_msg);
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
/* CreateSqlStatement of NARCGROUP ********************************************/

 #define NARCGROUP_CREATE(x) EXEC SQL create table x (\
         BTM_GRUPPE char(5) default " " not null,\
         BTM_BEZ char(30) default " " not null,\
         BTM_GEHALT decimal(9,4) default 0 not null,\
         BTM_EINHEIT char(9) default " " not null) extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of NARCGROUP ******************************************/

 #define NARCGROUP_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_zdkbtm_1 on _X_(\
              btm_gruppe );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of NARCGROUP ******************************************/

 #define NARCGROUP_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_zdkbtm_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
