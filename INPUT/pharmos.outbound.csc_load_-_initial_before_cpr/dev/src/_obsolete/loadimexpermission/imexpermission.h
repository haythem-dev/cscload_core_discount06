#ifndef __PP_IMEXPERMISSION_H_
#define __PP_IMEXPERMISSION_H_

/******************************************************************************/
/* c:\Marathon\orderentry\load\loadimexpermission\src\ImexPermission **********/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <pplib/bufkon.h>

/* Length-Define of IMEXPERMISSION ********************************************/

#define L_IMEXPERMISSION_COUNTRY_IFACODE 3
#define L_IMEXPERMISSION_IMEX_MODE 6
#define L_IMEXPERMISSION_ARTICLENO 11

/* Length/Count-Define of IMEXPERMISSION **************************************/

#define LS_IMEXPERMISSION_COUNTRY_IFACODE 3 + 1
#define LS_IMEXPERMISSION_IMEX_MODE 5 + 1
#define LS_IMEXPERMISSION_ARTICLENO 10 + 1

#define IMEXPERMISSIONCOUNTRY_IFACODE 0
#define IMEXPERMISSIONIMEX_MODE 1
#define IMEXPERMISSIONARTICLENO 2

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define IMEXPERMISSION_H
#define IMEXPERMISSION_ANZ ( sizeof(IMEXPERMISSION_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of IMEXPERMISSION ************************************************/

#define IMEXPERMISSION_LISTE \
        IMEXPERMISSION.COUNTRY_IFACODE,\
        IMEXPERMISSION.IMEX_MODE,\
        IMEXPERMISSION.ARTICLENO
#define IMEXPERMISSION_LISTE_390 \
        COUNTRY_IFACODE,\
        IMEX_MODE,\
        ARTICLENO
#define IMEXPERMISSION_PLISTE \
        "IMEXPERMISSION.COUNTRY_IFACODE,"\
        "IMEXPERMISSION.IMEX_MODE,"\
        "IMEXPERMISSION.ARTICLENO"
#define IMEXPERMISSION_PELISTE \
        "COUNTRY_IFACODE,"\
        "IMEX_MODE,"\
        "ARTICLENO"
#define IMEXPERMISSION_UPDLISTE \
        "COUNTRY_IFACODE=?,"\
        "IMEX_MODE=?,"\
        "ARTICLENO=?"
/* SqlMacros-Define of IMEXPERMISSION *****************************************/

#define IMEXPERMISSION_ZEIGER(x) \
        :x->COUNTRY_IFACODE,\
        :x->IMEX_MODE,\
        :x->ARTICLENO
#define IMEXPERMISSION_ZEIGERSEL(x) \
        :x->COUNTRY_IFACODE,\
        :x->IMEX_MODE,\
        :x->ARTICLENO
#define IMEXPERMISSION_UPDATE(x) \
        IMEXPERMISSION.COUNTRY_IFACODE=:x->COUNTRY_IFACODE,\
        IMEXPERMISSION.IMEX_MODE=:x->IMEX_MODE,\
        IMEXPERMISSION.ARTICLENO=:x->ARTICLENO
/* SqlMacros390-Define of IMEXPERMISSION **************************************/

#define IMEXPERMISSION_ZEIGER_390 \
        :COUNTRY_IFACODE,\
        :IMEX_MODE,\
        :ARTICLENO
#define IMEXPERMISSION_UPDATE_390 \
        COUNTRY_IFACODE=:COUNTRY_IFACODE,\
        IMEX_MODE=:IMEX_MODE,\
        ARTICLENO=:ARTICLENO
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of IMEXPERMISSION ******************************************/

#ifndef TRANSCLASS
typedef struct N_IMEXPERMISSION {
    char COUNTRY_IFACODE[4];
    short IMEX_MODE;
    long ARTICLENO;
} imexpermissionS;
#else /* TRANSCLASS */
typedef struct N_IMEXPERMISSION {
    char COUNTRY_IFACODE[4];
    short IMEX_MODE;
    long ARTICLENO;

    bool operator == (const N_IMEXPERMISSION& right) const {
        return (
            !strcmp(COUNTRY_IFACODE, right.COUNTRY_IFACODE) &&
            IMEX_MODE == right.IMEX_MODE &&
            ARTICLENO == right.ARTICLENO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        strcpy(COUNTRY_IFACODE, " " );
        IMEX_MODE = 0;
        ARTICLENO = 0;
#endif
    }
} imexpermissionS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of IMEXPERMISSION ************************************/

struct S_IMEXPERMISSION {
    char COUNTRY_IFACODE[3 + 1];
    char IMEX_MODE[7];
    char ARTICLENO[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of IMEXPERMISSION *******************/

struct O_IMEXPERMISSION {
    char COUNTRY_IFACODE[3];
    char IMEX_MODE[7];
    char ARTICLENO[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of IMEXPERMISSION ******************************/

struct C_IMEXPERMISSION {
    char COUNTRY_IFACODE[4];
    short IMEX_MODE;
    long ARTICLENO;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of IMEXPERMISSION ****************************/

struct I_IMEXPERMISSION {
    short COUNTRY_IFACODE;
    short IMEX_MODE;
    short ARTICLENO;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of IMEXPERMISSION **************************************/

#if defined (BUF_DESC)
static struct buf_desc IMEXPERMISSION_BES [] = {
   { TYP_C, 3, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc IMEXPERMISSION_BES [] = {
   { TYP_C, 3, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* description for datatypes of IMEXPERMISSION ********************************/

 #define IMEXPERMISSION_S390 \
         char COUNTRY_IFACODE[4]; \
         short IMEX_MODE; \
         long ARTICLENO; \



/* Copy-Function Struct to single Data IMEXPERMISSION *************************/

 #define IMEXPERMISSION_S390_COPY_TO_SINGLE(_x_) \
          strcpy(COUNTRY_IFACODE,_x_->COUNTRY_IFACODE);\
         IMEX_MODE=_x_->IMEX_MODE;\
         ARTICLENO=_x_->ARTICLENO;\

 #define IMEXPERMISSION_S390_COPY_TO_STRUCT(_x_) \
          strcpy(_x_->COUNTRY_IFACODE,COUNTRY_IFACODE);\
          _x_->IMEX_MODE=IMEX_MODE;\
          _x_->ARTICLENO=ARTICLENO;\



/* FunctionNumber-Define of ImexPermission ************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of ImexPermission ********************************/


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

class CIMEXPERMISSION : public ppDadeVirtual {
public:
    imexpermissionS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<imexpermissionS> lst; // class list

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
                     vector< imexpermissionS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     imexpermissionS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< imexpermissionS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<imexpermissionS>::iterator
                 beginList() { return lst.begin(); }
    vector<imexpermissionS>::iterator
                 endList  () { return lst.end  (); }

    const char*  GetCountry_ifacode(ppString & t) const { t = s.COUNTRY_IFACODE; t.erasespace(ppString::END); return t.c_str(); }
    short        GetImex_mode() const { return s.IMEX_MODE; }
    long         GetArticleno() const { return s.ARTICLENO; }

    const imexpermissionS &
                 GetStruct() const { return s; }
    void         SetCountry_ifacode(const ppString & t) { ppGStrCopy(s.COUNTRY_IFACODE, t.c_str(), L_IMEXPERMISSION_COUNTRY_IFACODE); }
    void         SetImex_mode(short t) { s.IMEX_MODE = t; }
    void         SetArticleno(long t) { s.ARTICLENO = t; }

    void         SetStruct(const imexpermissionS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CIMEXPERMISSION() {
        ::buf_default((void *)&s, IMEXPERMISSION_BES, IMEXPERMISSION_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CIMEXPERMISSION() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, IMEXPERMISSION_BES, IMEXPERMISSION_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, IMEXPERMISSION_BES, (int)IMEXPERMISSION_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, IMEXPERMISSION_BES, (int)IMEXPERMISSION_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_IMEXPERMISSION & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.COUNTRY_IFACODE);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, IMEXPERMISSION_BES, (int)IMEXPERMISSION_ANZ, error_msg);
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
/* CreateSqlStatement of IMEXPERMISSION ***************************************/

 #define IMEXPERMISSION_CREATE(x) EXEC SQL create table x (\
         COUNTRY_IFACODE char(3) default " " not null,\
         IMEX_MODE smallint default 0 not null,\
         ARTICLENO integer default 0 not null) in phosix extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of IMEXPERMISSION *************************************/

 #define IMEXPERMISSION_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_imexpermission_1 on _X_(\
              country_ifacode,\
              imex_mode,\
              ArticleNo ) in phosix1;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of IMEXPERMISSION *************************************/

 #define IMEXPERMISSION_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_imexpermission_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
