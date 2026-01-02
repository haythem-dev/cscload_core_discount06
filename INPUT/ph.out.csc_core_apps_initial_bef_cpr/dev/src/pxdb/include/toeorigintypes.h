#ifndef __PP_OEORIGINTYPES_H_
#define __PP_OEORIGINTYPES_H_

/******************************************************************************/
/* v:\OEOriginTypes ***********************************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of OEORIGINTYPES *********************************************/

#define L_OEORIGINTYPES_ORIGINTYPE 6
#define L_OEORIGINTYPES_ORIGINDEVICE 20

/* Length/Count-Define of OEORIGINTYPES ***************************************/

#define LS_OEORIGINTYPES_ORIGINTYPE 5 + 1
#define LS_OEORIGINTYPES_ORIGINDEVICE 20 + 1

#define OEORIGINTYPESORIGINTYPE 0
#define OEORIGINTYPESORIGINDEVICE 1

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define OEORIGINTYPES_H
#define OEORIGINTYPES_ANZ ( sizeof(OEORIGINTYPES_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of OEORIGINTYPES *************************************************/

#define OEORIGINTYPES_LISTE \
        OEORIGINTYPES.ORIGINTYPE,\
        OEORIGINTYPES.ORIGINDEVICE
#define OEORIGINTYPES_LISTE_390 \
        ORIGINTYPE,\
        ORIGINDEVICE
#define OEORIGINTYPES_PLISTE \
        "OEORIGINTYPES.ORIGINTYPE,"\
        "OEORIGINTYPES.ORIGINDEVICE"
#define OEORIGINTYPES_PELISTE \
        "ORIGINTYPE,"\
        "ORIGINDEVICE"
#define OEORIGINTYPES_UPDLISTE \
        "ORIGINTYPE=?,"\
        "ORIGINDEVICE=?"
/* SqlMacros-Define of OEORIGINTYPES ******************************************/

#define OEORIGINTYPES_ZEIGER(x) \
        :x->ORIGINTYPE,\
        :x->ORIGINDEVICE
#define OEORIGINTYPES_ZEIGERSEL(x) \
        :x->ORIGINTYPE,\
        :x->ORIGINDEVICE
#define OEORIGINTYPES_UPDATE(x) \
        OEORIGINTYPES.ORIGINTYPE=:x->ORIGINTYPE,\
        OEORIGINTYPES.ORIGINDEVICE=:x->ORIGINDEVICE
/* SqlMacros390-Define of OEORIGINTYPES ***************************************/

#define OEORIGINTYPES_ZEIGER_390 \
        :ORIGINTYPE,\
        :ORIGINDEVICE
#define OEORIGINTYPES_UPDATE_390 \
        ORIGINTYPE=:ORIGINTYPE,\
        ORIGINDEVICE=:ORIGINDEVICE
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of OEORIGINTYPES *******************************************/

#ifndef TRANSCLASS
typedef struct N_OEORIGINTYPES {
    short ORIGINTYPE;
    char ORIGINDEVICE[21];
} oeorigintypesS;
#else /* TRANSCLASS */
typedef struct N_OEORIGINTYPES {
    short ORIGINTYPE;
    char ORIGINDEVICE[21];

    bool operator == (const N_OEORIGINTYPES& right) const {
        return (
            ORIGINTYPE == right.ORIGINTYPE &&
            !strcmp(ORIGINDEVICE, right.ORIGINDEVICE)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        ORIGINTYPE = 0;
        strcpy(ORIGINDEVICE, " " );
#endif
    }
} oeorigintypesS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of OEORIGINTYPES *************************************/

struct S_OEORIGINTYPES {
    char ORIGINTYPE[7];
    char ORIGINDEVICE[20 + 1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of OEORIGINTYPES ********************/

struct O_OEORIGINTYPES {
    char ORIGINTYPE[7];
    char ORIGINDEVICE[20];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of OEORIGINTYPES *******************************/

struct C_OEORIGINTYPES {
    short ORIGINTYPE;
    char ORIGINDEVICE[21];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of OEORIGINTYPES *****************************/

struct I_OEORIGINTYPES {
    short ORIGINTYPE;
    short ORIGINDEVICE;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of OEORIGINTYPES ***************************************/

#if defined (BUF_DESC)
static struct buf_desc OEORIGINTYPES_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 20, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc OEORIGINTYPES_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 20, 0 },
};
#endif

/* description for datatypes of OEORIGINTYPES *********************************/

 #define OEORIGINTYPES_S390 \
         short ORIGINTYPE; \
         char ORIGINDEVICE[21]; \



/* Copy-Function Struct to single Data OEORIGINTYPES **************************/

 #define OEORIGINTYPES_S390_COPY_TO_SINGLE(_x_) \
         ORIGINTYPE=_x_->ORIGINTYPE;\
          strcpy(ORIGINDEVICE,_x_->ORIGINDEVICE);\

 #define OEORIGINTYPES_S390_COPY_TO_STRUCT(_x_) \
          _x_->ORIGINTYPE=ORIGINTYPE;\
          strcpy(_x_->ORIGINDEVICE,ORIGINDEVICE);\



/* FunctionNumber-Define of OEOriginTypes *************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of OEOriginTypes *********************************/


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

class COEORIGINTYPES : public ppDadeVirtual {
public:
    oeorigintypesS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<oeorigintypesS> lst; // class list

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
                     vector< oeorigintypesS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     oeorigintypesS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< oeorigintypesS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<oeorigintypesS>::iterator
                 beginList() { return lst.begin(); }
    vector<oeorigintypesS>::iterator
                 endList  () { return lst.end  (); }

    short        GetOrigintype() const { return s.ORIGINTYPE; }
    const char*  GetOrigindevice(ppString & t) const { t = s.ORIGINDEVICE; t.erasespace(ppString::END); return t.c_str(); }

    const oeorigintypesS &
                 GetStruct() const { return s; }
    void         SetOrigintype(short t) { s.ORIGINTYPE = t; }
    void         SetOrigindevice(const ppString & t) { ppGStrCopy(s.ORIGINDEVICE, t.c_str(), L_OEORIGINTYPES_ORIGINDEVICE); }

    void         SetStruct(const oeorigintypesS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    COEORIGINTYPES() {
        ::buf_default((void *)&s, OEORIGINTYPES_BES, OEORIGINTYPES_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~COEORIGINTYPES() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, OEORIGINTYPES_BES, OEORIGINTYPES_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, OEORIGINTYPES_BES, (int)OEORIGINTYPES_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, OEORIGINTYPES_BES, (int)OEORIGINTYPES_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_OEORIGINTYPES & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.ORIGINDEVICE);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, OEORIGINTYPES_BES, (int)OEORIGINTYPES_ANZ, error_msg);
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
/* CreateSqlStatement of OEORIGINTYPES ****************************************/

 #define OEORIGINTYPES_CREATE(x) EXEC SQL create table x (\
         ORIGINTYPE smallint default 0 not null,\
         ORIGINDEVICE char(20) default " " not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of OEORIGINTYPES **************************************/

 #define OEORIGINTYPES_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_oeorigintypes_1 on _X_(\
              OriginType ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of OEORIGINTYPES **************************************/

 #define OEORIGINTYPES_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_oeorigintypes_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
