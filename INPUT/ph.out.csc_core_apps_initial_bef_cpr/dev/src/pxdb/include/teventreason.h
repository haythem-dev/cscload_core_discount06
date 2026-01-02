#ifndef __PP_EVENTREASONS_H_
#define __PP_EVENTREASONS_H_

/******************************************************************************/
/* v:\EventReasons ************************************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of EVENTREASONS **********************************************/

#define L_EVENTREASONS_EVENTCODE 6
#define L_EVENTREASONS_EVENTDESCRIPTION 254

/* Length/Count-Define of EVENTREASONS ****************************************/

#define LS_EVENTREASONS_EVENTCODE 5 + 1
#define LS_EVENTREASONS_EVENTDESCRIPTION 254 + 1

#define EVENTREASONSEVENTCODE 0
#define EVENTREASONSEVENTDESCRIPTION 1

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define EVENTREASONS_H
#define EVENTREASONS_ANZ ( sizeof(EVENTREASONS_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of EVENTREASONS **************************************************/

#define EVENTREASONS_LISTE \
        EVENTREASONS.EVENTCODE,\
        EVENTREASONS.EVENTDESCRIPTION
#define EVENTREASONS_LISTE_390 \
        EVENTCODE,\
        EVENTDESCRIPTION
#define EVENTREASONS_PLISTE \
        "EVENTREASONS.EVENTCODE,"\
        "EVENTREASONS.EVENTDESCRIPTION"
#define EVENTREASONS_PELISTE \
        "EVENTCODE,"\
        "EVENTDESCRIPTION"
#define EVENTREASONS_UPDLISTE \
        "EVENTCODE=?,"\
        "EVENTDESCRIPTION=?"
/* SqlMacros-Define of EVENTREASONS *******************************************/

#define EVENTREASONS_ZEIGER(x) \
        :x->EVENTCODE,\
        :x->EVENTDESCRIPTION
#define EVENTREASONS_ZEIGERSEL(x) \
        :x->EVENTCODE,\
        :x->EVENTDESCRIPTION
#define EVENTREASONS_UPDATE(x) \
        EVENTREASONS.EVENTCODE=:x->EVENTCODE,\
        EVENTREASONS.EVENTDESCRIPTION=:x->EVENTDESCRIPTION
/* SqlMacros390-Define of EVENTREASONS ****************************************/

#define EVENTREASONS_ZEIGER_390 \
        :EVENTCODE,\
        :EVENTDESCRIPTION
#define EVENTREASONS_UPDATE_390 \
        EVENTCODE=:EVENTCODE,\
        EVENTDESCRIPTION=:EVENTDESCRIPTION
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of EVENTREASONS ********************************************/

#ifndef TRANSCLASS
typedef struct N_EVENTREASONS {
    short EVENTCODE;
    char EVENTDESCRIPTION[255];
} eventreasonsS;
#else /* TRANSCLASS */
typedef struct N_EVENTREASONS {
    short EVENTCODE;
    char EVENTDESCRIPTION[255];

    bool operator == (const N_EVENTREASONS& right) const {
        return (
            EVENTCODE == right.EVENTCODE &&
            !strcmp(EVENTDESCRIPTION, right.EVENTDESCRIPTION)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        EVENTCODE = 0;
        strcpy(EVENTDESCRIPTION, " " );
#endif
    }
} eventreasonsS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of EVENTREASONS **************************************/

struct S_EVENTREASONS {
    char EVENTCODE[7];
    char EVENTDESCRIPTION[254 + 1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of EVENTREASONS *********************/

struct O_EVENTREASONS {
    char EVENTCODE[7];
    char EVENTDESCRIPTION[254];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of EVENTREASONS ********************************/

struct C_EVENTREASONS {
    short EVENTCODE;
    char EVENTDESCRIPTION[255];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of EVENTREASONS ******************************/

struct I_EVENTREASONS {
    short EVENTCODE;
    short EVENTDESCRIPTION;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of EVENTREASONS ****************************************/

#if defined (BUF_DESC)
static struct buf_desc EVENTREASONS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 254, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc EVENTREASONS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 254, 0 },
};
#endif

/* description for datatypes of EVENTREASONS **********************************/

 #define EVENTREASONS_S390 \
         short EVENTCODE; \
         char EVENTDESCRIPTION[255]; \



/* Copy-Function Struct to single Data EVENTREASONS ***************************/

 #define EVENTREASONS_S390_COPY_TO_SINGLE(_x_) \
         EVENTCODE=_x_->EVENTCODE;\
          strcpy(EVENTDESCRIPTION,_x_->EVENTDESCRIPTION);\

 #define EVENTREASONS_S390_COPY_TO_STRUCT(_x_) \
          _x_->EVENTCODE=EVENTCODE;\
          strcpy(_x_->EVENTDESCRIPTION,EVENTDESCRIPTION);\



/* FunctionNumber-Define of EventReasons **************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of EventReasons **********************************/


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

class CEVENTREASONS : public ppDadeVirtual {
public:
    eventreasonsS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<eventreasonsS> lst; // class list

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
                     vector< eventreasonsS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     eventreasonsS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< eventreasonsS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<eventreasonsS>::iterator
                 beginList() { return lst.begin(); }
    vector<eventreasonsS>::iterator
                 endList  () { return lst.end  (); }

    short        GetEventcode() const { return s.EVENTCODE; }
    const char*  GetEventdescription(ppString & t) const { t = s.EVENTDESCRIPTION; t.erasespace(ppString::END); return t.c_str(); }

    const eventreasonsS &
                 GetStruct() const { return s; }
    void         SetEventcode(short t) { s.EVENTCODE = t; }
    void         SetEventdescription(const ppString & t) { ppGStrCopy(s.EVENTDESCRIPTION, t.c_str(), L_EVENTREASONS_EVENTDESCRIPTION); }

    void         SetStruct(const eventreasonsS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CEVENTREASONS() {
        ::buf_default((void *)&s, EVENTREASONS_BES, EVENTREASONS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CEVENTREASONS() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, EVENTREASONS_BES, EVENTREASONS_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, EVENTREASONS_BES, (int)EVENTREASONS_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, EVENTREASONS_BES, (int)EVENTREASONS_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_EVENTREASONS & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.EVENTDESCRIPTION);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, EVENTREASONS_BES, (int)EVENTREASONS_ANZ, error_msg);
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
/* CreateSqlStatement of EVENTREASONS *****************************************/

 #define EVENTREASONS_CREATE(x) EXEC SQL create table x (\
         EVENTCODE smallint default 0 not null,\
         EVENTDESCRIPTION varchar(254,0) default " " not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of EVENTREASONS ***************************************/

 #define EVENTREASONS_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_eventreaseons_1 on _X_(\
              EventCode ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of EVENTREASONS ***************************************/

 #define EVENTREASONS_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_eventreaseons_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
