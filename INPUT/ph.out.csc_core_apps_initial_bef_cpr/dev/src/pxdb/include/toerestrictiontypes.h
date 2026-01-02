#ifndef __PP_OERESTRICTIONTYPES_H_
#define __PP_OERESTRICTIONTYPES_H_

/******************************************************************************/
/* v:\OERestrictionTypes ******************************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of OERESTRICTIONTYPES ****************************************/

#define L_OERESTRICTIONTYPES_RESTRICTIONTYPE 6
#define L_OERESTRICTIONTYPES_RESTRICTIONNAME 254

/* Length/Count-Define of OERESTRICTIONTYPES **********************************/

#define LS_OERESTRICTIONTYPES_RESTRICTIONTYPE 5 + 1
#define LS_OERESTRICTIONTYPES_RESTRICTIONNAME 254 + 1

#define OERESTRICTIONTYPESRESTRICTIONTYPE 0
#define OERESTRICTIONTYPESRESTRICTIONNAME 1

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define OERESTRICTIONTYPES_H
#define OERESTRICTIONTYPES_ANZ ( sizeof(OERESTRICTIONTYPES_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of OERESTRICTIONTYPES ********************************************/

#define OERESTRICTIONTYPES_LISTE \
        OERESTRICTIONTYPES.RESTRICTIONTYPE,\
        OERESTRICTIONTYPES.RESTRICTIONNAME
#define OERESTRICTIONTYPES_LISTE_390 \
        RESTRICTIONTYPE,\
        RESTRICTIONNAME
#define OERESTRICTIONTYPES_PLISTE \
        "OERESTRICTIONTYPES.RESTRICTIONTYPE,"\
        "OERESTRICTIONTYPES.RESTRICTIONNAME"
#define OERESTRICTIONTYPES_PELISTE \
        "RESTRICTIONTYPE,"\
        "RESTRICTIONNAME"
#define OERESTRICTIONTYPES_UPDLISTE \
        "RESTRICTIONTYPE=?,"\
        "RESTRICTIONNAME=?"
/* SqlMacros-Define of OERESTRICTIONTYPES *************************************/

#define OERESTRICTIONTYPES_ZEIGER(x) \
        :x->RESTRICTIONTYPE,\
        :x->RESTRICTIONNAME
#define OERESTRICTIONTYPES_ZEIGERSEL(x) \
        :x->RESTRICTIONTYPE,\
        :x->RESTRICTIONNAME
#define OERESTRICTIONTYPES_UPDATE(x) \
        OERESTRICTIONTYPES.RESTRICTIONTYPE=:x->RESTRICTIONTYPE,\
        OERESTRICTIONTYPES.RESTRICTIONNAME=:x->RESTRICTIONNAME
/* SqlMacros390-Define of OERESTRICTIONTYPES **********************************/

#define OERESTRICTIONTYPES_ZEIGER_390 \
        :RESTRICTIONTYPE,\
        :RESTRICTIONNAME
#define OERESTRICTIONTYPES_UPDATE_390 \
        RESTRICTIONTYPE=:RESTRICTIONTYPE,\
        RESTRICTIONNAME=:RESTRICTIONNAME
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of OERESTRICTIONTYPES **************************************/

#ifndef TRANSCLASS
typedef struct N_OERESTRICTIONTYPES {
    short RESTRICTIONTYPE;
    char RESTRICTIONNAME[255];
} oerestrictiontypesS;
#else /* TRANSCLASS */
typedef struct N_OERESTRICTIONTYPES {
    short RESTRICTIONTYPE;
    char RESTRICTIONNAME[255];

    bool operator == (const N_OERESTRICTIONTYPES& right) const {
        return (
            RESTRICTIONTYPE == right.RESTRICTIONTYPE &&
            !strcmp(RESTRICTIONNAME, right.RESTRICTIONNAME)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        RESTRICTIONTYPE = 0;
        strcpy(RESTRICTIONNAME, " " );
#endif
    }
} oerestrictiontypesS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of OERESTRICTIONTYPES ********************************/

struct S_OERESTRICTIONTYPES {
    char RESTRICTIONTYPE[7];
    char RESTRICTIONNAME[254 + 1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of OERESTRICTIONTYPES ***************/

struct O_OERESTRICTIONTYPES {
    char RESTRICTIONTYPE[7];
    char RESTRICTIONNAME[254];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of OERESTRICTIONTYPES **************************/

struct C_OERESTRICTIONTYPES {
    short RESTRICTIONTYPE;
    char RESTRICTIONNAME[255];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of OERESTRICTIONTYPES ************************/

struct I_OERESTRICTIONTYPES {
    short RESTRICTIONTYPE;
    short RESTRICTIONNAME;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of OERESTRICTIONTYPES **********************************/

#if defined (BUF_DESC)
static struct buf_desc OERESTRICTIONTYPES_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 254, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc OERESTRICTIONTYPES_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 254, 0 },
};
#endif

/* description for datatypes of OERESTRICTIONTYPES ****************************/

 #define OERESTRICTIONTYPES_S390 \
         short RESTRICTIONTYPE; \
         char RESTRICTIONNAME[255]; \



/* Copy-Function Struct to single Data OERESTRICTIONTYPES *********************/

 #define OERESTRICTIONTYPES_S390_COPY_TO_SINGLE(_x_) \
         RESTRICTIONTYPE=_x_->RESTRICTIONTYPE;\
          strcpy(RESTRICTIONNAME,_x_->RESTRICTIONNAME);\

 #define OERESTRICTIONTYPES_S390_COPY_TO_STRUCT(_x_) \
          _x_->RESTRICTIONTYPE=RESTRICTIONTYPE;\
          strcpy(_x_->RESTRICTIONNAME,RESTRICTIONNAME);\



/* FunctionNumber-Define of OERestrictionTypes ********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of OERestrictionTypes ****************************/


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

class COERESTRICTIONTYPES : public ppDadeVirtual {
public:
    oerestrictiontypesS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<oerestrictiontypesS> lst; // class list

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
                     vector< oerestrictiontypesS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     oerestrictiontypesS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< oerestrictiontypesS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<oerestrictiontypesS>::iterator
                 beginList() { return lst.begin(); }
    vector<oerestrictiontypesS>::iterator
                 endList  () { return lst.end  (); }

    short        GetRestrictiontype() const { return s.RESTRICTIONTYPE; }
    const char*  GetRestrictionname(ppString & t) const { t = s.RESTRICTIONNAME; t.erasespace(ppString::END); return t.c_str(); }

    const oerestrictiontypesS &
                 GetStruct() const { return s; }
    void         SetRestrictiontype(short t) { s.RESTRICTIONTYPE = t; }
    void         SetRestrictionname(const ppString & t) { ppGStrCopy(s.RESTRICTIONNAME, t.c_str(), L_OERESTRICTIONTYPES_RESTRICTIONNAME); }

    void         SetStruct(const oerestrictiontypesS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    COERESTRICTIONTYPES() {
        ::buf_default((void *)&s, OERESTRICTIONTYPES_BES, OERESTRICTIONTYPES_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~COERESTRICTIONTYPES() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, OERESTRICTIONTYPES_BES, OERESTRICTIONTYPES_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, OERESTRICTIONTYPES_BES, (int)OERESTRICTIONTYPES_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, OERESTRICTIONTYPES_BES, (int)OERESTRICTIONTYPES_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_OERESTRICTIONTYPES & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.RESTRICTIONNAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, OERESTRICTIONTYPES_BES, (int)OERESTRICTIONTYPES_ANZ, error_msg);
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
/* CreateSqlStatement of OERESTRICTIONTYPES ***********************************/

 #define OERESTRICTIONTYPES_CREATE(x) EXEC SQL create table x (\
         RESTRICTIONTYPE smallint default 0 not null,\
         RESTRICTIONNAME varchar(254,0) default " " not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of OERESTRICTIONTYPES *********************************/

 #define OERESTRICTIONTYPES_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_oerestrictiontypes_1 on _X_(\
              RestrictionType ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of OERESTRICTIONTYPES *********************************/

 #define OERESTRICTIONTYPES_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_oerestrictiontypes_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
