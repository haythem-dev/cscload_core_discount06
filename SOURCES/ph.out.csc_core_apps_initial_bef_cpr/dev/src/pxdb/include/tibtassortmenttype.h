#ifndef __PP_IBTASSORTMENTTYPE_H_
#define __PP_IBTASSORTMENTTYPE_H_

/******************************************************************************/
/* c:\prri\Headerfiles\ibtassortmenttype **************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of IBTASSORTMENTTYPE *****************************************/

#define L_IBTASSORTMENTTYPE_IBTASSORTMENTTYPEID 6
#define L_IBTASSORTMENTTYPE_ASSORTMENTTYPENAME 20
#define L_IBTASSORTMENTTYPE_IBTCUSTOMERSONLY 6
#define L_IBTASSORTMENTTYPE_IBTPERIODNEEDED 6

/* Length/Count-Define of IBTASSORTMENTTYPE ***********************************/

#define LS_IBTASSORTMENTTYPE_IBTASSORTMENTTYPEID 5 + 1
#define LS_IBTASSORTMENTTYPE_ASSORTMENTTYPENAME 20 + 1
#define LS_IBTASSORTMENTTYPE_IBTCUSTOMERSONLY 5 + 1
#define LS_IBTASSORTMENTTYPE_IBTPERIODNEEDED 5 + 1

#define IBTASSORTMENTTYPEIBTASSORTMENTTYPEID 0
#define IBTASSORTMENTTYPEASSORTMENTTYPENAME 1
#define IBTASSORTMENTTYPEIBTCUSTOMERSONLY 2
#define IBTASSORTMENTTYPEIBTPERIODNEEDED 3

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define IBTASSORTMENTTYPE_H
#define IBTASSORTMENTTYPE_ANZ ( sizeof(IBTASSORTMENTTYPE_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of IBTASSORTMENTTYPE *********************************************/

#define IBTASSORTMENTTYPE_LISTE \
        IBTASSORTMENTTYPE.IBTASSORTMENTTYPEID,\
        IBTASSORTMENTTYPE.ASSORTMENTTYPENAME,\
        IBTASSORTMENTTYPE.IBTCUSTOMERSONLY,\
        IBTASSORTMENTTYPE.IBTPERIODNEEDED
#define IBTASSORTMENTTYPE_LISTE_390 \
        IBTASSORTMENTTYPEID,\
        ASSORTMENTTYPENAME,\
        IBTCUSTOMERSONLY,\
        IBTPERIODNEEDED
#define IBTASSORTMENTTYPE_PLISTE \
        "IBTASSORTMENTTYPE.IBTASSORTMENTTYPEID,"\
        "IBTASSORTMENTTYPE.ASSORTMENTTYPENAME,"\
        "IBTASSORTMENTTYPE.IBTCUSTOMERSONLY,"\
        "IBTASSORTMENTTYPE.IBTPERIODNEEDED"
#define IBTASSORTMENTTYPE_PELISTE \
        "IBTASSORTMENTTYPEID,"\
        "ASSORTMENTTYPENAME,"\
        "IBTCUSTOMERSONLY,"\
        "IBTPERIODNEEDED"
#define IBTASSORTMENTTYPE_UPDLISTE \
        "IBTASSORTMENTTYPEID=?,"\
        "ASSORTMENTTYPENAME=?,"\
        "IBTCUSTOMERSONLY=?,"\
        "IBTPERIODNEEDED=?"
/* SqlMacros-Define of IBTASSORTMENTTYPE **************************************/

#define IBTASSORTMENTTYPE_ZEIGER(x) \
        :x->IBTASSORTMENTTYPEID,\
        :x->ASSORTMENTTYPENAME,\
        :x->IBTCUSTOMERSONLY,\
        :x->IBTPERIODNEEDED
#define IBTASSORTMENTTYPE_ZEIGERSEL(x) \
        :x->IBTASSORTMENTTYPEID,\
        :x->ASSORTMENTTYPENAME,\
        :x->IBTCUSTOMERSONLY,\
        :x->IBTPERIODNEEDED
#define IBTASSORTMENTTYPE_UPDATE(x) \
        IBTASSORTMENTTYPE.IBTASSORTMENTTYPEID=:x->IBTASSORTMENTTYPEID,\
        IBTASSORTMENTTYPE.ASSORTMENTTYPENAME=:x->ASSORTMENTTYPENAME,\
        IBTASSORTMENTTYPE.IBTCUSTOMERSONLY=:x->IBTCUSTOMERSONLY,\
        IBTASSORTMENTTYPE.IBTPERIODNEEDED=:x->IBTPERIODNEEDED
/* SqlMacros390-Define of IBTASSORTMENTTYPE ***********************************/

#define IBTASSORTMENTTYPE_ZEIGER_390 \
        :IBTASSORTMENTTYPEID,\
        :ASSORTMENTTYPENAME,\
        :IBTCUSTOMERSONLY,\
        :IBTPERIODNEEDED
#define IBTASSORTMENTTYPE_UPDATE_390 \
        IBTASSORTMENTTYPEID=:IBTASSORTMENTTYPEID,\
        ASSORTMENTTYPENAME=:ASSORTMENTTYPENAME,\
        IBTCUSTOMERSONLY=:IBTCUSTOMERSONLY,\
        IBTPERIODNEEDED=:IBTPERIODNEEDED
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of IBTASSORTMENTTYPE ***************************************/

#ifndef TRANSCLASS
typedef struct N_IBTASSORTMENTTYPE {
    short IBTASSORTMENTTYPEID;
    char ASSORTMENTTYPENAME[21];
    short IBTCUSTOMERSONLY;
    short IBTPERIODNEEDED;
} ibtassortmenttypeS;
#else /* TRANSCLASS */
typedef struct N_IBTASSORTMENTTYPE {
    short IBTASSORTMENTTYPEID;
    char ASSORTMENTTYPENAME[21];
    short IBTCUSTOMERSONLY;
    short IBTPERIODNEEDED;

    bool operator == (const N_IBTASSORTMENTTYPE& right) const {
        return (
            IBTASSORTMENTTYPEID == right.IBTASSORTMENTTYPEID &&
            !strcmp(ASSORTMENTTYPENAME, right.ASSORTMENTTYPENAME) &&
            IBTCUSTOMERSONLY == right.IBTCUSTOMERSONLY &&
            IBTPERIODNEEDED == right.IBTPERIODNEEDED
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        IBTASSORTMENTTYPEID = 0;
        strcpy(ASSORTMENTTYPENAME, " " );
        IBTCUSTOMERSONLY = 0;
        IBTPERIODNEEDED = 0;
#endif
    }
} ibtassortmenttypeS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of IBTASSORTMENTTYPE *********************************/

struct S_IBTASSORTMENTTYPE {
    char IBTASSORTMENTTYPEID[7];
    char ASSORTMENTTYPENAME[20 + 1];
    char IBTCUSTOMERSONLY[7];
    char IBTPERIODNEEDED[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of IBTASSORTMENTTYPE ****************/

struct O_IBTASSORTMENTTYPE {
    char IBTASSORTMENTTYPEID[7];
    char ASSORTMENTTYPENAME[20];
    char IBTCUSTOMERSONLY[7];
    char IBTPERIODNEEDED[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of IBTASSORTMENTTYPE ***************************/

struct C_IBTASSORTMENTTYPE {
    short IBTASSORTMENTTYPEID;
    char ASSORTMENTTYPENAME[21];
    short IBTCUSTOMERSONLY;
    short IBTPERIODNEEDED;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of IBTASSORTMENTTYPE *************************/

struct I_IBTASSORTMENTTYPE {
    short IBTASSORTMENTTYPEID;
    short ASSORTMENTTYPENAME;
    short IBTCUSTOMERSONLY;
    short IBTPERIODNEEDED;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of IBTASSORTMENTTYPE ***********************************/

#if defined (BUF_DESC)
static struct buf_desc IBTASSORTMENTTYPE_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 20, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc IBTASSORTMENTTYPE_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 20, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* description for datatypes of IBTASSORTMENTTYPE *****************************/

 #define IBTASSORTMENTTYPE_S390 \
         short IBTASSORTMENTTYPEID; \
         char ASSORTMENTTYPENAME[21]; \
         short IBTCUSTOMERSONLY; \
         short IBTPERIODNEEDED; \



/* Copy-Function Struct to single Data IBTASSORTMENTTYPE **********************/

 #define IBTASSORTMENTTYPE_S390_COPY_TO_SINGLE(_x_) \
         IBTASSORTMENTTYPEID=_x_->IBTASSORTMENTTYPEID;\
          strcpy(ASSORTMENTTYPENAME,_x_->ASSORTMENTTYPENAME);\
         IBTCUSTOMERSONLY=_x_->IBTCUSTOMERSONLY;\
         IBTPERIODNEEDED=_x_->IBTPERIODNEEDED;\

 #define IBTASSORTMENTTYPE_S390_COPY_TO_STRUCT(_x_) \
          _x_->IBTASSORTMENTTYPEID=IBTASSORTMENTTYPEID;\
          strcpy(_x_->ASSORTMENTTYPENAME,ASSORTMENTTYPENAME);\
          _x_->IBTCUSTOMERSONLY=IBTCUSTOMERSONLY;\
          _x_->IBTPERIODNEEDED=IBTPERIODNEEDED;\



/* FunctionNumber-Define of ibtassortmenttype *********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of ibtassortmenttype *****************************/


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

class CIBTASSORTMENTTYPE : public ppDadeVirtual {
public:
    ibtassortmenttypeS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<ibtassortmenttypeS> lst; // class list

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
                     vector< ibtassortmenttypeS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     ibtassortmenttypeS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< ibtassortmenttypeS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<ibtassortmenttypeS>::iterator
                 beginList() { return lst.begin(); }
    vector<ibtassortmenttypeS>::iterator
                 endList  () { return lst.end  (); }

    short        GetIbtassortmenttypeid() const { return s.IBTASSORTMENTTYPEID; }
    const char*  GetAssortmenttypename(ppString & t) const { t = s.ASSORTMENTTYPENAME; t.erasespace(ppString::END); return t.c_str(); }
    short        GetIbtcustomersonly() const { return s.IBTCUSTOMERSONLY; }
    short        GetIbtperiodneeded() const { return s.IBTPERIODNEEDED; }

    const ibtassortmenttypeS &
                 GetStruct() const { return s; }
    void         SetIbtassortmenttypeid(short t) { s.IBTASSORTMENTTYPEID = t; }
    void         SetAssortmenttypename(const ppString & t) { ppGStrCopy(s.ASSORTMENTTYPENAME, t.c_str(), L_IBTASSORTMENTTYPE_ASSORTMENTTYPENAME); }
    void         SetIbtcustomersonly(short t) { s.IBTCUSTOMERSONLY = t; }
    void         SetIbtperiodneeded(short t) { s.IBTPERIODNEEDED = t; }

    void         SetStruct(const ibtassortmenttypeS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CIBTASSORTMENTTYPE() {
        ::buf_default((void *)&s, IBTASSORTMENTTYPE_BES, IBTASSORTMENTTYPE_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CIBTASSORTMENTTYPE() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, IBTASSORTMENTTYPE_BES, IBTASSORTMENTTYPE_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, IBTASSORTMENTTYPE_BES, (int)IBTASSORTMENTTYPE_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, IBTASSORTMENTTYPE_BES, (int)IBTASSORTMENTTYPE_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_IBTASSORTMENTTYPE & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.ASSORTMENTTYPENAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, IBTASSORTMENTTYPE_BES, (int)IBTASSORTMENTTYPE_ANZ, error_msg);
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
/* CreateSqlStatement of IBTASSORTMENTTYPE ************************************/

 #define IBTASSORTMENTTYPE_CREATE(x) EXEC SQL create table x (\
         IBTASSORTMENTTYPEID smallint default 0 not null,\
         ASSORTMENTTYPENAME varchar(20,0) default " " not null,\
         IBTCUSTOMERSONLY smallint default 0 not null,\
         IBTPERIODNEEDED smallint default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of IBTASSORTMENTTYPE **********************************/

 #define IBTASSORTMENTTYPE_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index xpkibtassortmenttype on _X_(\
              ibtassortmenttypeid ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of IBTASSORTMENTTYPE **********************************/

 #define IBTASSORTMENTTYPE_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index xpkibtassortmenttype;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
