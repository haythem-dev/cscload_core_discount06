#ifndef __PP_KRITIKKOPF_H_
#define __PP_KRITIKKOPF_H_

/******************************************************************************/
/* c:\Marathon\orderentry\csc_core_applications\src\aapserv\KRITIKKOPF ********/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of KRITIKKOPF ************************************************/

#define L_KRITIKKOPF_IDFNR 11
#define L_KRITIKKOPF_DATUM 11
#define L_KRITIKKOPF_REGIONNR 11
#define L_KRITIKKOPF_ZEIT 11
#define L_KRITIKKOPF_UID 11
#define L_KRITIKKOPF_TITEL 30
#define L_KRITIKKOPF_KRITIKNR 11
#define L_KRITIKKOPF_VERTRIEBSZENTRUMNR 6
#define L_KRITIKKOPF_KUNDENNR 11
#define L_KRITIKKOPF_FILIALNR 6
#define L_KRITIKKOPF_KRITIKLEVEL 6

/* Length/Count-Define of KRITIKKOPF ******************************************/

#define LS_KRITIKKOPF_IDFNR 10 + 1
#define LS_KRITIKKOPF_DATUM 10 + 1
#define LS_KRITIKKOPF_REGIONNR 10 + 1
#define LS_KRITIKKOPF_ZEIT 10 + 1
#define LS_KRITIKKOPF_UID 10 + 1
#define LS_KRITIKKOPF_TITEL 30 + 1
#define LS_KRITIKKOPF_KRITIKNR 10 + 1
#define LS_KRITIKKOPF_VERTRIEBSZENTRUMNR 5 + 1
#define LS_KRITIKKOPF_KUNDENNR 10 + 1
#define LS_KRITIKKOPF_FILIALNR 5 + 1
#define LS_KRITIKKOPF_KRITIKLEVEL 5 + 1

#define KRITIKKOPFIDFNR 0
#define KRITIKKOPFDATUM 1
#define KRITIKKOPFREGIONNR 2
#define KRITIKKOPFZEIT 3
#define KRITIKKOPFUID 4
#define KRITIKKOPFTITEL 5
#define KRITIKKOPFKRITIKNR 6
#define KRITIKKOPFVERTRIEBSZENTRUMNR 7
#define KRITIKKOPFKUNDENNR 8
#define KRITIKKOPFFILIALNR 9
#define KRITIKKOPFKRITIKLEVEL 10

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define KRITIKKOPF_H
#define KRITIKKOPF_ANZ ( sizeof(KRITIKKOPF_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of KRITIKKOPF ****************************************************/

#define KRITIKKOPF_LISTE \
        KDKRITIK.IDFNR,\
        KDKRITIK.DATUM,\
        REGIONARTEN.REGIONNR,\
        KDKRITIK.ZEIT,\
        KDKRITIK.UID,\
        KDKRITIK.TITEL,\
        KDKRITIK.KRITIKNR,\
        KDKRITIK.VERTRIEBSZENTRUMNR,\
        KDKRITIK.KUNDENNR,\
        KDKRITIK.FILIALNR,\
        KDKRITIK.KRITIKLEVEL
#define KRITIKKOPF_LISTE_390 \
        IDFNR,\
        DATUM,\
        REGIONNR,\
        ZEIT,\
        UID,\
        TITEL,\
        KRITIKNR,\
        VERTRIEBSZENTRUMNR,\
        KUNDENNR,\
        FILIALNR,\
        KRITIKLEVEL
#define KRITIKKOPF_PLISTE \
        "KDKRITIK.IDFNR,"\
        "KDKRITIK.DATUM,"\
        "KDKRITIK.ZEIT,"\
        "KDKRITIK.UID,"\
        "KDKRITIK.TITEL,"\
        "KDKRITIK.KRITIKNR,"\
        "KDKRITIK.VERTRIEBSZENTRUMNR,"\
        "KDKRITIK.KUNDENNR,"\
        "KDKRITIK.FILIALNR,"\
        "KDKRITIK.KRITIKLEVEL"
#define KRITIKKOPF_PELISTE \
        "IDFNR,"\
        "DATUM,"\
        "ZEIT,"\
        "UID,"\
        "TITEL,"\
        "KRITIKNR,"\
        "VERTRIEBSZENTRUMNR,"\
        "KUNDENNR,"\
        "FILIALNR,"\
        "KRITIKLEVEL"
#define KRITIKKOPF_UPDLISTE \
        "IDFNR=?,"\
        "DATUM=?,"\
        "ZEIT=?,"\
        "UID=?,"\
        "TITEL=?,"\
        "KRITIKNR=?,"\
        "VERTRIEBSZENTRUMNR=?,"\
        "KUNDENNR=?,"\
        "FILIALNR=?,"\
        "KRITIKLEVEL=?"
/* SqlMacros-Define of KRITIKKOPF *********************************************/

#define KRITIKKOPF_ZEIGER(x) \
        :x->IDFNR,\
        :x->DATUM,\
        :x->ZEIT,\
        :x->UID,\
        :x->TITEL,\
        :x->KRITIKNR,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->FILIALNR,\
        :x->KRITIKLEVEL
#define KRITIKKOPF_ZEIGERSEL(x) \
        :x->IDFNR,\
        :x->DATUM,\
        :x->ZEIT,\
        :x->UID,\
        :x->TITEL,\
        :x->KRITIKNR,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->FILIALNR,\
        :x->KRITIKLEVEL
#define KRITIKKOPF_UPDATE(x) \
        KDKRITIK.IDFNR=:x->IDFNR,\
        KDKRITIK.DATUM=:x->DATUM,\
        KDKRITIK.ZEIT=:x->ZEIT,\
        KDKRITIK.UID=:x->UID,\
        KDKRITIK.TITEL=:x->TITEL,\
        KDKRITIK.KRITIKNR=:x->KRITIKNR,\
        KDKRITIK.VERTRIEBSZENTRUMNR=:x->VERTRIEBSZENTRUMNR,\
        KDKRITIK.KUNDENNR=:x->KUNDENNR,\
        KDKRITIK.FILIALNR=:x->FILIALNR,\
        KDKRITIK.KRITIKLEVEL=:x->KRITIKLEVEL
/* SqlMacros390-Define of KRITIKKOPF ******************************************/

#define KRITIKKOPF_ZEIGER_390 \
        :IDFNR,\
        :DATUM,\
        :REGIONNR,\
        :ZEIT,\
        :UID,\
        :TITEL,\
        :KRITIKNR,\
        :VERTRIEBSZENTRUMNR,\
        :KUNDENNR,\
        :FILIALNR,\
        :KRITIKLEVEL
#define KRITIKKOPF_UPDATE_390 \
        IDFNR=:IDFNR,\
        DATUM=:DATUM,\
        ZEIT=:ZEIT,\
        UID=:UID,\
        TITEL=:TITEL,\
        KRITIKNR=:KRITIKNR,\
        VERTRIEBSZENTRUMNR=:VERTRIEBSZENTRUMNR,\
        KUNDENNR=:KUNDENNR,\
        FILIALNR=:FILIALNR,\
        KRITIKLEVEL=:KRITIKLEVEL
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of KRITIKKOPF **********************************************/

#ifndef TRANSCLASS
typedef struct N_KRITIKKOPF {
    long IDFNR;
    long DATUM;
    long REGIONNR;
    long ZEIT;
    long UID;
    char TITEL[31];
    long KRITIKNR;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    short FILIALNR;
    short KRITIKLEVEL;
    long FETCH_REL;
} kritikkopfS;
#else /* TRANSCLASS */
typedef struct N_KRITIKKOPF {
    long IDFNR;
    long DATUM;
    long REGIONNR;
    long ZEIT;
    long UID;
    char TITEL[31];
    long KRITIKNR;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    short FILIALNR;
    short KRITIKLEVEL;
    long FETCH_REL;
    bool operator == (const N_KRITIKKOPF& right) const {
        return (
            IDFNR == right.IDFNR &&
            DATUM == right.DATUM &&
            REGIONNR == right.REGIONNR &&
            ZEIT == right.ZEIT &&
            UID == right.UID &&
            !strcmp(TITEL, right.TITEL) &&
            KRITIKNR == right.KRITIKNR &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            FILIALNR == right.FILIALNR &&
            KRITIKLEVEL == right.KRITIKLEVEL
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        IDFNR = 0;
        DATUM = 0;
        REGIONNR = 0;
        ZEIT = 0;
        UID = 0;
        strcpy(TITEL, " " );
        KRITIKNR = 0;
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        FILIALNR = 0;
        KRITIKLEVEL = 0;
#endif
    }
} kritikkopfS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of KRITIKKOPF ****************************************/

struct S_KRITIKKOPF {
    char IDFNR[11];
    char DATUM[11];
    char REGIONNR[11];
    char ZEIT[11];
    char UID[11];
    char TITEL[30 + 1];
    char KRITIKNR[11];
    char VERTRIEBSZENTRUMNR[7];
    char KUNDENNR[11];
    char FILIALNR[7];
    char KRITIKLEVEL[7];
    char FETCH_REL[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of KRITIKKOPF ***********************/

struct O_KRITIKKOPF {
    char IDFNR[11];
    char DATUM[11];
    char REGIONNR[11];
    char ZEIT[11];
    char UID[11];
    char TITEL[30];
    char KRITIKNR[11];
    char VERTRIEBSZENTRUMNR[7];
    char KUNDENNR[11];
    char FILIALNR[7];
    char KRITIKLEVEL[7];
    char FETCH_REL[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of KRITIKKOPF **********************************/

struct C_KRITIKKOPF {
    long IDFNR;
    long DATUM;
    long REGIONNR;
    long ZEIT;
    long UID;
    char TITEL[31];
    long KRITIKNR;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    short FILIALNR;
    short KRITIKLEVEL;
    long FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of KRITIKKOPF ********************************/

struct I_KRITIKKOPF {
    short IDFNR;
    short DATUM;
    short REGIONNR;
    short ZEIT;
    short UID;
    short TITEL;
    short KRITIKNR;
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short FILIALNR;
    short KRITIKLEVEL;
    short FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of KRITIKKOPF ******************************************/

#if defined (BUF_DESC)
static struct buf_desc KRITIKKOPF_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc KRITIKKOPF_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* description for datatypes of KRITIKKOPF ************************************/

 #define KRITIKKOPF_S390 \
         long IDFNR; \
         long DATUM; \
         long REGIONNR; \
         long ZEIT; \
         long UID; \
         char TITEL[31]; \
         long KRITIKNR; \
         short VERTRIEBSZENTRUMNR; \
         long KUNDENNR; \
         short FILIALNR; \
         short KRITIKLEVEL; \
         long FETCH_REL;



/* Copy-Function Struct to single Data KRITIKKOPF *****************************/

 #define KRITIKKOPF_S390_COPY_TO_SINGLE(_x_) \
         IDFNR=_x_->IDFNR;\
         DATUM=_x_->DATUM;\
         REGIONNR=_x_->REGIONNR;\
         ZEIT=_x_->ZEIT;\
         UID=_x_->UID;\
          strcpy(TITEL,_x_->TITEL);\
         KRITIKNR=_x_->KRITIKNR;\
         VERTRIEBSZENTRUMNR=_x_->VERTRIEBSZENTRUMNR;\
         KUNDENNR=_x_->KUNDENNR;\
         FILIALNR=_x_->FILIALNR;\
         KRITIKLEVEL=_x_->KRITIKLEVEL;\
          FETCH_REL=_x_->FETCH_REL;\

 #define KRITIKKOPF_S390_COPY_TO_STRUCT(_x_) \
          _x_->IDFNR=IDFNR;\
          _x_->DATUM=DATUM;\
          _x_->REGIONNR=REGIONNR;\
          _x_->ZEIT=ZEIT;\
          _x_->UID=UID;\
          strcpy(_x_->TITEL,TITEL);\
          _x_->KRITIKNR=KRITIKNR;\
          _x_->VERTRIEBSZENTRUMNR=VERTRIEBSZENTRUMNR;\
          _x_->KUNDENNR=KUNDENNR;\
          _x_->FILIALNR=FILIALNR;\
          _x_->KRITIKLEVEL=KRITIKLEVEL;\
          _x_->FETCH_REL=FETCH_REL;\



/* FunctionNumber-Define of KRITIKKOPF ****************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of KRITIKKOPF ************************************/


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

class CKRITIKKOPF : public ppDadeVirtual {
public:
    kritikkopfS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<kritikkopfS> lst; // class list

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
                     vector< kritikkopfS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     kritikkopfS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< kritikkopfS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<kritikkopfS>::iterator
                 beginList() { return lst.begin(); }
    vector<kritikkopfS>::iterator
                 endList  () { return lst.end  (); }

    long         GetIdfnr() const { return s.IDFNR; }
    long         GetDatum() const { return s.DATUM; }
    long         GetRegionnr() const { return s.REGIONNR; }
    long         GetZeit() const { return s.ZEIT; }
    long         GetUid() const { return s.UID; }
    const char*  GetTitel(ppString & t) const { t = s.TITEL; t.erasespace(ppString::END); return t.c_str(); }
    long         GetKritiknr() const { return s.KRITIKNR; }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    short        GetFilialnr() const { return s.FILIALNR; }
    short        GetKritiklevel() const { return s.KRITIKLEVEL; }

    const kritikkopfS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetIdfnr(long t) { s.IDFNR = t; }
    void         SetDatum(long t) { s.DATUM = t; }
    void         SetRegionnr(long t) { s.REGIONNR = t; }
    void         SetZeit(long t) { s.ZEIT = t; }
    void         SetUid(long t) { s.UID = t; }
    void         SetTitel(const ppString & t) { ppGStrCopy(s.TITEL, t.c_str(), L_KRITIKKOPF_TITEL); }
    void         SetKritiknr(long t) { s.KRITIKNR = t; }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetKritiklevel(short t) { s.KRITIKLEVEL = t; }

    void         SetStruct(const kritikkopfS & t) { s = t; }
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
    CKRITIKKOPF() {
        ::buf_default((void *)&s, KRITIKKOPF_BES, KRITIKKOPF_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CKRITIKKOPF() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, KRITIKKOPF_BES, KRITIKKOPF_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, KRITIKKOPF_BES, (int)KRITIKKOPF_ANZ, error_msg);
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
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, KRITIKKOPF_BES, (int)KRITIKKOPF_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, KRITIKKOPF_BES, (int)KRITIKKOPF_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_KRITIKKOPF & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.TITEL);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, KRITIKKOPF_BES, (int)KRITIKKOPF_ANZ, error_msg);
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
        CKRITIKKOPF c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, KRITIKKOPF_BES, (int)KRITIKKOPF_ANZ, error_msg);
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
/* CreateSqlStatement of KRITIKKOPF *******************************************/

 #define KRITIKKOPF_CREATE(x) EXEC SQL create table x (\
         IDFNR integer default 0 not null,\
         DATUM integer default 0 not null,\
         REGIONNR integer default 0 not null,\
         ZEIT integer default 0 not null,\
         UID integer default 0 not null,\
         TITEL char(30) default " " not null,\
         KRITIKNR integer default 0 not null,\
         VERTRIEBSZENTRUMNR smallint default 0 not null,\
         KUNDENNR integer default 0 not null,\
         FILIALNR smallint default 0 not null,\
         KRITIKLEVEL smallint default 0 not null) extent size 784 next size 80 lock mode row;



/* CreateIndexStatement of KRITIKKOPF *****************************************/

 #define KRITIKKOPF_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_kdkritik_1 on _X_(\
              kritiknr );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index i_kdkritik_2 on _X_(\
              idfnr );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index i_kdkritik_3 on _X_(\
              datum );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of KRITIKKOPF *****************************************/

 #define KRITIKKOPF_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_kdkritik_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_kdkritik_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_kdkritik_3;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
