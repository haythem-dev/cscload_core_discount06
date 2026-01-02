#ifndef __PP_KDAUFTRAGEREIGNIS_H_
#define __PP_KDAUFTRAGEREIGNIS_H_

/******************************************************************************/
/* v:\kdauftragereignis *******************************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of KDAUFTRAGEREIGNIS *****************************************/

#define L_KDAUFTRAGEREIGNIS_KDAUFTRAGNR 11
#define L_KDAUFTRAGEREIGNIS_DATUM 11
#define L_KDAUFTRAGEREIGNIS_ZEIT 11
#define L_KDAUFTRAGEREIGNIS_EREIGNISART 6
#define L_KDAUFTRAGEREIGNIS_PERSONALNR 11
#define L_KDAUFTRAGEREIGNIS_GERAETNAME 8
#define L_KDAUFTRAGEREIGNIS_FILIALNR 6
#define L_KDAUFTRAGEREIGNIS_EVENTCODE 6

/* Length/Count-Define of KDAUFTRAGEREIGNIS ***********************************/

#define LS_KDAUFTRAGEREIGNIS_KDAUFTRAGNR 10 + 1
#define LS_KDAUFTRAGEREIGNIS_DATUM 10 + 1
#define LS_KDAUFTRAGEREIGNIS_ZEIT 10 + 1
#define LS_KDAUFTRAGEREIGNIS_EREIGNISART 5 + 1
#define LS_KDAUFTRAGEREIGNIS_PERSONALNR 10 + 1
#define LS_KDAUFTRAGEREIGNIS_GERAETNAME 8 + 1
#define LS_KDAUFTRAGEREIGNIS_FILIALNR 5 + 1
#define LS_KDAUFTRAGEREIGNIS_EVENTCODE 5 + 1

#define KDAUFTRAGEREIGNISKDAUFTRAGNR 0
#define KDAUFTRAGEREIGNISDATUM 1
#define KDAUFTRAGEREIGNISZEIT 2
#define KDAUFTRAGEREIGNISEREIGNISART 3
#define KDAUFTRAGEREIGNISPERSONALNR 4
#define KDAUFTRAGEREIGNISGERAETNAME 5
#define KDAUFTRAGEREIGNISFILIALNR 6
#define KDAUFTRAGEREIGNISEVENTCODE 7

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define KDAUFTRAGEREIGNIS_H
#define KDAUFTRAGEREIGNIS_ANZ ( sizeof(KDAUFTRAGEREIGNIS_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of KDAUFTRAGEREIGNIS *********************************************/

#define KDAUFTRAGEREIGNIS_LISTE \
        KDAUFTRAGEREIGNIS.KDAUFTRAGNR,\
        KDAUFTRAGEREIGNIS.DATUM,\
        KDAUFTRAGEREIGNIS.ZEIT,\
        KDAUFTRAGEREIGNIS.EREIGNISART,\
        KDAUFTRAGEREIGNIS.PERSONALNR,\
        KDAUFTRAGEREIGNIS.GERAETNAME,\
        KDAUFTRAGEREIGNIS.FILIALNR,\
        KDAUFTRAGEREIGNIS.EVENTCODE
#define KDAUFTRAGEREIGNIS_LISTE_390 \
        KDAUFTRAGNR,\
        DATUM,\
        ZEIT,\
        EREIGNISART,\
        PERSONALNR,\
        GERAETNAME,\
        FILIALNR,\
        EVENTCODE
#define KDAUFTRAGEREIGNIS_PLISTE \
        "KDAUFTRAGEREIGNIS.KDAUFTRAGNR,"\
        "KDAUFTRAGEREIGNIS.DATUM,"\
        "KDAUFTRAGEREIGNIS.ZEIT,"\
        "KDAUFTRAGEREIGNIS.EREIGNISART,"\
        "KDAUFTRAGEREIGNIS.PERSONALNR,"\
        "KDAUFTRAGEREIGNIS.GERAETNAME,"\
        "KDAUFTRAGEREIGNIS.FILIALNR,"\
        "KDAUFTRAGEREIGNIS.EVENTCODE"
#define KDAUFTRAGEREIGNIS_PELISTE \
        "KDAUFTRAGNR,"\
        "DATUM,"\
        "ZEIT,"\
        "EREIGNISART,"\
        "PERSONALNR,"\
        "GERAETNAME,"\
        "FILIALNR,"\
        "EVENTCODE"
#define KDAUFTRAGEREIGNIS_UPDLISTE \
        "KDAUFTRAGNR=?,"\
        "DATUM=?,"\
        "ZEIT=?,"\
        "EREIGNISART=?,"\
        "PERSONALNR=?,"\
        "GERAETNAME=?,"\
        "FILIALNR=?,"\
        "EVENTCODE=?"
/* SqlMacros-Define of KDAUFTRAGEREIGNIS **************************************/

#define KDAUFTRAGEREIGNIS_ZEIGER(x) \
        :x->KDAUFTRAGNR,\
        :x->DATUM,\
        :x->ZEIT,\
        :x->EREIGNISART,\
        :x->PERSONALNR,\
        :x->GERAETNAME,\
        :x->FILIALNR,\
        :x->EVENTCODE
#define KDAUFTRAGEREIGNIS_ZEIGERSEL(x) \
        :x->KDAUFTRAGNR,\
        :x->DATUM,\
        :x->ZEIT,\
        :x->EREIGNISART,\
        :x->PERSONALNR,\
        :x->GERAETNAME,\
        :x->FILIALNR,\
        :x->EVENTCODE
#define KDAUFTRAGEREIGNIS_UPDATE(x) \
        KDAUFTRAGEREIGNIS.KDAUFTRAGNR=:x->KDAUFTRAGNR,\
        KDAUFTRAGEREIGNIS.DATUM=:x->DATUM,\
        KDAUFTRAGEREIGNIS.ZEIT=:x->ZEIT,\
        KDAUFTRAGEREIGNIS.EREIGNISART=:x->EREIGNISART,\
        KDAUFTRAGEREIGNIS.PERSONALNR=:x->PERSONALNR,\
        KDAUFTRAGEREIGNIS.GERAETNAME=:x->GERAETNAME,\
        KDAUFTRAGEREIGNIS.FILIALNR=:x->FILIALNR,\
        KDAUFTRAGEREIGNIS.EVENTCODE=:x->EVENTCODE
/* SqlMacros390-Define of KDAUFTRAGEREIGNIS ***********************************/

#define KDAUFTRAGEREIGNIS_ZEIGER_390 \
        :KDAUFTRAGNR,\
        :DATUM,\
        :ZEIT,\
        :EREIGNISART,\
        :PERSONALNR,\
        :GERAETNAME,\
        :FILIALNR,\
        :EVENTCODE
#define KDAUFTRAGEREIGNIS_UPDATE_390 \
        KDAUFTRAGNR=:KDAUFTRAGNR,\
        DATUM=:DATUM,\
        ZEIT=:ZEIT,\
        EREIGNISART=:EREIGNISART,\
        PERSONALNR=:PERSONALNR,\
        GERAETNAME=:GERAETNAME,\
        FILIALNR=:FILIALNR,\
        EVENTCODE=:EVENTCODE
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of KDAUFTRAGEREIGNIS ***************************************/

#ifndef TRANSCLASS
typedef struct N_KDAUFTRAGEREIGNIS {
    long KDAUFTRAGNR;
    long DATUM;
    long ZEIT;
    short EREIGNISART;
    long PERSONALNR;
    char GERAETNAME[9];
    short FILIALNR;
    short EVENTCODE;
} kdauftragereignisS;
#else /* TRANSCLASS */
typedef struct N_KDAUFTRAGEREIGNIS {
    long KDAUFTRAGNR;
    long DATUM;
    long ZEIT;
    short EREIGNISART;
    long PERSONALNR;
    char GERAETNAME[9];
    short FILIALNR;
    short EVENTCODE;

    bool operator == (const N_KDAUFTRAGEREIGNIS& right) const {
        return (
            KDAUFTRAGNR == right.KDAUFTRAGNR &&
            DATUM == right.DATUM &&
            ZEIT == right.ZEIT &&
            EREIGNISART == right.EREIGNISART &&
            PERSONALNR == right.PERSONALNR &&
            !strcmp(GERAETNAME, right.GERAETNAME) &&
            FILIALNR == right.FILIALNR &&
            EVENTCODE == right.EVENTCODE
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        KDAUFTRAGNR = 0;
        DATUM = 0;
        ZEIT = 0;
        EREIGNISART = 0;
        PERSONALNR = 0;
        strcpy(GERAETNAME, " " );
        FILIALNR = 0;
        EVENTCODE = 0;
#endif
    }
} kdauftragereignisS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of KDAUFTRAGEREIGNIS *********************************/

struct S_KDAUFTRAGEREIGNIS {
    char KDAUFTRAGNR[11];
    char DATUM[11];
    char ZEIT[11];
    char EREIGNISART[7];
    char PERSONALNR[11];
    char GERAETNAME[8 + 1];
    char FILIALNR[7];
    char EVENTCODE[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of KDAUFTRAGEREIGNIS ****************/

struct O_KDAUFTRAGEREIGNIS {
    char KDAUFTRAGNR[11];
    char DATUM[11];
    char ZEIT[11];
    char EREIGNISART[7];
    char PERSONALNR[11];
    char GERAETNAME[8];
    char FILIALNR[7];
    char EVENTCODE[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of KDAUFTRAGEREIGNIS ***************************/

struct C_KDAUFTRAGEREIGNIS {
    long KDAUFTRAGNR;
    long DATUM;
    long ZEIT;
    short EREIGNISART;
    long PERSONALNR;
    char GERAETNAME[9];
    short FILIALNR;
    short EVENTCODE;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of KDAUFTRAGEREIGNIS *************************/

struct I_KDAUFTRAGEREIGNIS {
    short KDAUFTRAGNR;
    short DATUM;
    short ZEIT;
    short EREIGNISART;
    short PERSONALNR;
    short GERAETNAME;
    short FILIALNR;
    short EVENTCODE;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of KDAUFTRAGEREIGNIS ***********************************/

#if defined (BUF_DESC)
static struct buf_desc KDAUFTRAGEREIGNIS_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 8, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc KDAUFTRAGEREIGNIS_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 8, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* description for datatypes of KDAUFTRAGEREIGNIS *****************************/

 #define KDAUFTRAGEREIGNIS_S390 \
         long KDAUFTRAGNR; \
         long DATUM; \
         long ZEIT; \
         short EREIGNISART; \
         long PERSONALNR; \
         char GERAETNAME[9]; \
         short FILIALNR; \
         short EVENTCODE; \



/* Copy-Function Struct to single Data KDAUFTRAGEREIGNIS **********************/

 #define KDAUFTRAGEREIGNIS_S390_COPY_TO_SINGLE(_x_) \
         KDAUFTRAGNR=_x_->KDAUFTRAGNR;\
         DATUM=_x_->DATUM;\
         ZEIT=_x_->ZEIT;\
         EREIGNISART=_x_->EREIGNISART;\
         PERSONALNR=_x_->PERSONALNR;\
          strcpy(GERAETNAME,_x_->GERAETNAME);\
         FILIALNR=_x_->FILIALNR;\
         EVENTCODE=_x_->EVENTCODE;\

 #define KDAUFTRAGEREIGNIS_S390_COPY_TO_STRUCT(_x_) \
          _x_->KDAUFTRAGNR=KDAUFTRAGNR;\
          _x_->DATUM=DATUM;\
          _x_->ZEIT=ZEIT;\
          _x_->EREIGNISART=EREIGNISART;\
          _x_->PERSONALNR=PERSONALNR;\
          strcpy(_x_->GERAETNAME,GERAETNAME);\
          _x_->FILIALNR=FILIALNR;\
          _x_->EVENTCODE=EVENTCODE;\



/* FunctionNumber-Define of kdauftragereignis *********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of kdauftragereignis *****************************/


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

class CKDAUFTRAGEREIGNIS : public ppDadeVirtual {
public:
    kdauftragereignisS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<kdauftragereignisS> lst; // class list

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
                     vector< kdauftragereignisS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     kdauftragereignisS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< kdauftragereignisS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<kdauftragereignisS>::iterator
                 beginList() { return lst.begin(); }
    vector<kdauftragereignisS>::iterator
                 endList  () { return lst.end  (); }

    long         GetKdauftragnr() const { return s.KDAUFTRAGNR; }
    long         GetDatum() const { return s.DATUM; }
    long         GetZeit() const { return s.ZEIT; }
    short        GetEreignisart() const { return s.EREIGNISART; }
    long         GetPersonalnr() const { return s.PERSONALNR; }
    const char*  GetGeraetname(ppString & t) const { t = s.GERAETNAME; t.erasespace(ppString::END); return t.c_str(); }
    short        GetFilialnr() const { return s.FILIALNR; }
    short        GetEventcode() const { return s.EVENTCODE; }

    const kdauftragereignisS &
                 GetStruct() const { return s; }
    void         SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
    void         SetDatum(long t) { s.DATUM = t; }
    void         SetZeit(long t) { s.ZEIT = t; }
    void         SetEreignisart(short t) { s.EREIGNISART = t; }
    void         SetPersonalnr(long t) { s.PERSONALNR = t; }
    void         SetGeraetname(const ppString & t) { ppGStrCopy(s.GERAETNAME, t.c_str(), L_KDAUFTRAGEREIGNIS_GERAETNAME); }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetEventcode(short t) { s.EVENTCODE = t; }

    void         SetStruct(const kdauftragereignisS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CKDAUFTRAGEREIGNIS() {
        ::buf_default((void *)&s, KDAUFTRAGEREIGNIS_BES, KDAUFTRAGEREIGNIS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CKDAUFTRAGEREIGNIS() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, KDAUFTRAGEREIGNIS_BES, KDAUFTRAGEREIGNIS_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, KDAUFTRAGEREIGNIS_BES, (int)KDAUFTRAGEREIGNIS_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, KDAUFTRAGEREIGNIS_BES, (int)KDAUFTRAGEREIGNIS_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_KDAUFTRAGEREIGNIS & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.GERAETNAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, KDAUFTRAGEREIGNIS_BES, (int)KDAUFTRAGEREIGNIS_ANZ, error_msg);
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
/* CreateSqlStatement of KDAUFTRAGEREIGNIS ************************************/

 #define KDAUFTRAGEREIGNIS_CREATE(x) EXEC SQL create table x (\
         KDAUFTRAGNR integer default 0 not null,\
         DATUM integer default 0 not null,\
         ZEIT integer default 0 not null,\
         EREIGNISART smallint default 0 not null,\
         PERSONALNR integer default 0 not null,\
         GERAETNAME char(8) default " " not null,\
         FILIALNR smallint default 0 not null,\
         EVENTCODE smallint default 0 not null) in KscOrder extent size 5100 next size 512 lock mode row;



/* CreateIndexStatement of KDAUFTRAGEREIGNIS **********************************/

 #define KDAUFTRAGEREIGNIS_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_kdauftragereig_1 on _X_(\
              kdauftragnr,\
              datum,\
              zeit,\
              ereignisart ) in KscOrderIdx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index i_kdauftragereig_2 on _X_(\
              kdauftragnr,\
              ereignisart ) in KscOrderIdx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of KDAUFTRAGEREIGNIS **********************************/

 #define KDAUFTRAGEREIGNIS_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_kdauftragereig_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_kdauftragereig_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
