#ifndef __PP_KRITIKPOS_H_
#define __PP_KRITIKPOS_H_

/******************************************************************************/
/* c:\tmp\q2\KRITIKPOS ********************************************************/
/* produced by DADE 6.22.3 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of KRITIKPOS *************************************************/

#define L_KRITIKPOS_KRITIKNR 11
#define L_KRITIKPOS_POSNR 11
#define L_KRITIKPOS_KZPOSART 1
#define L_KRITIKPOS_UID 11
#define L_KRITIKPOS_DATUM 11
#define L_KRITIKPOS_ZEIT 11
#define L_KRITIKPOS_FILIALNR 6
#define L_KRITIKPOS_KRITIKTEXT 2048
#define L_KRITIKPOS_USERNAME64 64

/* Length/Count-Define of KRITIKPOS *******************************************/

#define LS_KRITIKPOS_KRITIKNR 10 + 1
#define LS_KRITIKPOS_POSNR 10 + 1
#define LS_KRITIKPOS_KZPOSART 1 + 1
#define LS_KRITIKPOS_UID 10 + 1
#define LS_KRITIKPOS_DATUM 10 + 1
#define LS_KRITIKPOS_ZEIT 10 + 1
#define LS_KRITIKPOS_FILIALNR 5 + 1
#define LS_KRITIKPOS_KRITIKTEXT 2048 + 1
#define LS_KRITIKPOS_USERNAME64 64 + 1

#define KRITIKPOSKRITIKNR 0
#define KRITIKPOSPOSNR 1
#define KRITIKPOSKZPOSART 2
#define KRITIKPOSUID 3
#define KRITIKPOSDATUM 4
#define KRITIKPOSZEIT 5
#define KRITIKPOSFILIALNR 6
#define KRITIKPOSKRITIKTEXT 7
#define KRITIKPOSUSERNAME64 8

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define KRITIKPOS_H
#define KRITIKPOS_ANZ ( sizeof(KRITIKPOS_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of KRITIKPOS *****************************************************/

#define KRITIKPOS_LISTE \
        KDKRITIKPOS.KRITIKNR,\
        KDKRITIKPOS.POSNR,\
        KDKRITIKPOS.KZPOSART,\
        KDKRITIKPOS.UID,\
        KDKRITIKPOS.DATUM,\
        KDKRITIKPOS.ZEIT,\
        KDKRITIKPOS.FILIALNR,\
        KDKRITIKPOS.KRITIKTEXT,\
        AADUMMY.USERNAME64
#define KRITIKPOS_LISTE_390 \
        KRITIKNR,\
        POSNR,\
        KZPOSART,\
        UID,\
        DATUM,\
        ZEIT,\
        FILIALNR,\
        KRITIKTEXT,\
        USERNAME64
#define KRITIKPOS_PLISTE \
        "KDKRITIKPOS.KRITIKNR,"\
        "KDKRITIKPOS.POSNR,"\
        "KDKRITIKPOS.KZPOSART,"\
        "KDKRITIKPOS.UID,"\
        "KDKRITIKPOS.DATUM,"\
        "KDKRITIKPOS.ZEIT,"\
        "KDKRITIKPOS.FILIALNR,"\
        "KDKRITIKPOS.KRITIKTEXT,"\
        "AADUMMY.USERNAME64"
#define KRITIKPOS_PELISTE \
        "KRITIKNR,"\
        "POSNR,"\
        "KZPOSART,"\
        "UID,"\
        "DATUM,"\
        "ZEIT,"\
        "FILIALNR,"\
        "KRITIKTEXT,"\
        "USERNAME64"
#define KRITIKPOS_UPDLISTE \
        "KRITIKNR=?,"\
        "POSNR=?,"\
        "KZPOSART=?,"\
        "UID=?,"\
        "DATUM=?,"\
        "ZEIT=?,"\
        "FILIALNR=?,"\
        "KRITIKTEXT=?,"\
        "USERNAME64=?"
/* SqlMacros-Define of KRITIKPOS **********************************************/

#define KRITIKPOS_ZEIGER(x) \
        :x->KRITIKNR,\
        :x->POSNR,\
        :x->KZPOSART,\
        :x->UID,\
        :x->DATUM,\
        :x->ZEIT,\
        :x->FILIALNR,\
        :x->KRITIKTEXT,\
        :x->USERNAME64
#define KRITIKPOS_ZEIGERSEL(x) \
        :x->KRITIKNR,\
        :x->POSNR,\
        :x->KZPOSART,\
        :x->UID,\
        :x->DATUM,\
        :x->ZEIT,\
        :x->FILIALNR,\
        :x->KRITIKTEXT,\
        :x->USERNAME64
#define KRITIKPOS_UPDATE(x) \
        KDKRITIKPOS.KRITIKNR=:x->KRITIKNR,\
        KDKRITIKPOS.POSNR=:x->POSNR,\
        KDKRITIKPOS.KZPOSART=:x->KZPOSART,\
        KDKRITIKPOS.UID=:x->UID,\
        KDKRITIKPOS.DATUM=:x->DATUM,\
        KDKRITIKPOS.ZEIT=:x->ZEIT,\
        KDKRITIKPOS.FILIALNR=:x->FILIALNR,\
        KDKRITIKPOS.KRITIKTEXT=:x->KRITIKTEXT,\
        AADUMMY.USERNAME64=:x->USERNAME64
/* SqlMacros390-Define of KRITIKPOS *******************************************/

#define KRITIKPOS_ZEIGER_390 \
        :KRITIKNR,\
        :POSNR,\
        :KZPOSART,\
        :UID,\
        :DATUM,\
        :ZEIT,\
        :FILIALNR,\
        :KRITIKTEXT,\
        :USERNAME64
#define KRITIKPOS_UPDATE_390 \
        KRITIKNR=:KRITIKNR,\
        POSNR=:POSNR,\
        KZPOSART=:KZPOSART,\
        UID=:UID,\
        DATUM=:DATUM,\
        ZEIT=:ZEIT,\
        FILIALNR=:FILIALNR,\
        KRITIKTEXT=:KRITIKTEXT,\
        USERNAME64=:USERNAME64
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of KRITIKPOS ***********************************************/

#ifndef TRANSCLASS
typedef struct N_KRITIKPOS {
    long KRITIKNR;
    long POSNR;
    char KZPOSART[2];
    long UID;
    long DATUM;
    long ZEIT;
    short FILIALNR;
    char KRITIKTEXT[2049];
    char USERNAME64[65];
    long FETCH_REL;
} kritikposS;
#else /* TRANSCLASS */
typedef struct N_KRITIKPOS {
    long KRITIKNR;
    long POSNR;
    char KZPOSART[2];
    long UID;
    long DATUM;
    long ZEIT;
    short FILIALNR;
    char KRITIKTEXT[2049];
    char USERNAME64[65];
    long FETCH_REL;
    bool operator == (const N_KRITIKPOS& right) const {
        return (
            KRITIKNR == right.KRITIKNR &&
            POSNR == right.POSNR &&
            !strcmp(KZPOSART, right.KZPOSART) &&
            UID == right.UID &&
            DATUM == right.DATUM &&
            ZEIT == right.ZEIT &&
            FILIALNR == right.FILIALNR &&
            !strcmp(KRITIKTEXT, right.KRITIKTEXT) &&
            !strcmp(USERNAME64, right.USERNAME64)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        KRITIKNR = 0;
        POSNR = 0;
        strcpy(KZPOSART, " " );
        UID = 0;
        DATUM = 0;
        ZEIT = 0;
        FILIALNR = 0;
        strcpy(KRITIKTEXT, " " );
        strcpy(USERNAME64, " " );
#endif
    }
} kritikposS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of KRITIKPOS *****************************************/

struct S_KRITIKPOS {
    char KRITIKNR[11];
    char POSNR[11];
    char KZPOSART[1 + 1];
    char UID[11];
    char DATUM[11];
    char ZEIT[11];
    char FILIALNR[7];
    char KRITIKTEXT[2048 + 1];
    char USERNAME64[64 + 1];
    char FETCH_REL[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of KRITIKPOS ************************/

struct O_KRITIKPOS {
    char KRITIKNR[11];
    char POSNR[11];
    char KZPOSART[1];
    char UID[11];
    char DATUM[11];
    char ZEIT[11];
    char FILIALNR[7];
    char KRITIKTEXT[2048];
    char USERNAME64[64];
    char FETCH_REL[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of KRITIKPOS ***********************************/

struct C_KRITIKPOS {
    long KRITIKNR;
    long POSNR;
    char KZPOSART;
    long UID;
    long DATUM;
    long ZEIT;
    short FILIALNR;
    char KRITIKTEXT[2049];
    char USERNAME64[65];
    long FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of KRITIKPOS *********************************/

struct I_KRITIKPOS {
    short KRITIKNR;
    short POSNR;
    short KZPOSART;
    short UID;
    short DATUM;
    short ZEIT;
    short FILIALNR;
    short KRITIKTEXT;
    short USERNAME64;
    short FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of KRITIKPOS *******************************************/

#if defined (BUF_DESC)
static struct buf_desc KRITIKPOS_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 2048, 0 },
   { TYP_C, 64, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc KRITIKPOS_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 2048, 0 },
   { TYP_C, 64, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* description for datatypes of KRITIKPOS *************************************/

 #define KRITIKPOS_S390 \
         long KRITIKNR; \
         long POSNR; \
         char KZPOSART; \
         long UID; \
         long DATUM; \
         long ZEIT; \
         short FILIALNR; \
         char KRITIKTEXT[2049]; \
         char USERNAME64[65]; \
         long FETCH_REL;



/* Copy-Function Struct to single Data KRITIKPOS ******************************/

 #define KRITIKPOS_S390_COPY_TO_SINGLE(_x_) \
         KRITIKNR=_x_->KRITIKNR;\
         POSNR=_x_->POSNR;\
         KZPOSART=_x_->KZPOSART;\
         UID=_x_->UID;\
         DATUM=_x_->DATUM;\
         ZEIT=_x_->ZEIT;\
         FILIALNR=_x_->FILIALNR;\
          strcpy(KRITIKTEXT,_x_->KRITIKTEXT);\
          strcpy(USERNAME64,_x_->USERNAME64);\
          FETCH_REL=_x_->FETCH_REL;\

 #define KRITIKPOS_S390_COPY_TO_STRUCT(_x_) \
          _x_->KRITIKNR=KRITIKNR;\
          _x_->POSNR=POSNR;\
          _x_->KZPOSART=KZPOSART;\
          _x_->UID=UID;\
          _x_->DATUM=DATUM;\
          _x_->ZEIT=ZEIT;\
          _x_->FILIALNR=FILIALNR;\
          strcpy(_x_->KRITIKTEXT,KRITIKTEXT);\
          strcpy(_x_->USERNAME64,USERNAME64);\
          _x_->FETCH_REL=FETCH_REL;\



/* FunctionNumber-Define of KRITIKPOS *****************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of KRITIKPOS *************************************/


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

class CKRITIKPOS : public ppDadeVirtual {
public:
    kritikposS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<kritikposS> lst; // class list

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
                     vector< kritikposS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     kritikposS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< kritikposS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<kritikposS>::iterator
                 beginList() { return lst.begin(); }
    vector<kritikposS>::iterator
                 endList  () { return lst.end  (); }

    long         GetKritiknr() const { return s.KRITIKNR; }
    long         GetPosnr() const { return s.POSNR; }
    char         GetKzposart() const { return s.KZPOSART[0]; }
    long         GetUid() const { return s.UID; }
    long         GetDatum() const { return s.DATUM; }
    long         GetZeit() const { return s.ZEIT; }
    short        GetFilialnr() const { return s.FILIALNR; }
    const char*  GetKritiktext(ppString & t) const { t = s.KRITIKTEXT; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetUsername64(ppString & t) const { t = s.USERNAME64; t.erasespace(ppString::END); return t.c_str(); }

    const kritikposS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetKritiknr(long t) { s.KRITIKNR = t; }
    void         SetPosnr(long t) { s.POSNR = t; }
    void         SetKzposart(char t) { s.KZPOSART[0] = t; s.KZPOSART[1] = '\0';}
    void         SetUid(long t) { s.UID = t; }
    void         SetDatum(long t) { s.DATUM = t; }
    void         SetZeit(long t) { s.ZEIT = t; }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetKritiktext(const ppString & t) { ppGStrCopy(s.KRITIKTEXT, t.c_str(), L_KRITIKPOS_KRITIKTEXT); }
    void         SetUsername64(const ppString & t) { ppGStrCopy(s.USERNAME64, t.c_str(), L_KRITIKPOS_USERNAME64); }

    void         SetStruct(const kritikposS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CKRITIKPOS() {
        ::buf_default((void *)&s, KRITIKPOS_BES, KRITIKPOS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CKRITIKPOS() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, KRITIKPOS_BES, KRITIKPOS_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, KRITIKPOS_BES, (int)KRITIKPOS_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, KRITIKPOS_BES, (int)KRITIKPOS_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, KRITIKPOS_BES, (int)KRITIKPOS_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_KRITIKPOS & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.KRITIKTEXT);
        ppGStripLast(d.USERNAME64);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, KRITIKPOS_BES, (int)KRITIKPOS_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CKRITIKPOS c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, KRITIKPOS_BES, (int)KRITIKPOS_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};
#endif    // TRANSCLASS
/* CreateSqlStatement of KRITIKPOS ********************************************/

 #define KRITIKPOS_CREATE(x) EXEC SQL create table x (\
         KRITIKNR integer default 0 not null,\
         POSNR integer default 0 not null,\
         KZPOSART char(1) default " " not null,\
         UID integer default 0 not null,\
         DATUM integer default 0 not null,\
         ZEIT integer default 0 not null,\
         FILIALNR smallint default 0 not null,\
         KRITIKTEXT lvarchar(2048,0) default " " not null,\
         USERNAME64 varchar(64,0) default " " not null) extent size 1568 next size 160 lock mode row;



/* CreateIndexStatement of KRITIKPOS ******************************************/

 #define KRITIKPOS_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_kdkritikpos_1 on _X_(\
              kritiknr,\
              kzposart,\
              posnr );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of KRITIKPOS ******************************************/

 #define KRITIKPOS_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_kdkritikpos_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
