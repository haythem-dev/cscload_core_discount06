#ifndef __PP_ALTFIL_H_
#define __PP_ALTFIL_H_

/******************************************************************************/
/* d:\prj\AA\WIN32\altfil *****************************************************/
/* produced by DADE 6.21.4 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of ALTFIL ****************************************************/

#define L_ALTFIL_FILIALNR 6
#define L_ALTFIL_REIHENFOLGENR 11
#define L_ALTFIL_VERBUNDFILIALNR 6
#define L_ALTFIL_FILIALTYP 6
#define L_ALTFIL_KDNR 11
#define L_ALTFIL_TAGTOURBGANR 11
#define L_ALTFIL_VBTOURZEIT 11
#define L_ALTFIL_VBTAGTOURZEIT 11
#define L_ALTFIL_VBTYP 6
#define L_ALTFIL_IBTDELIVERYTIME 6

/* Length/Count-Define of ALTFIL **********************************************/

#define LS_ALTFIL_FILIALNR 5 + 1
#define LS_ALTFIL_REIHENFOLGENR 10 + 1
#define LS_ALTFIL_VERBUNDFILIALNR 5 + 1
#define LS_ALTFIL_FILIALTYP 5 + 1
#define LS_ALTFIL_KDNR 10 + 1
#define LS_ALTFIL_TAGTOURBGANR 10 + 1
#define LS_ALTFIL_VBTOURZEIT 10 + 1
#define LS_ALTFIL_VBTAGTOURZEIT 10 + 1
#define LS_ALTFIL_VBTYP 5 + 1
#define LS_ALTFIL_IBTDELIVERYTIME 5 + 1

#define ALTFILFILIALNR 0
#define ALTFILREIHENFOLGENR 1
#define ALTFILVERBUNDFILIALNR 2
#define ALTFILFILIALTYP 3
#define ALTFILKDNR 4
#define ALTFILTAGTOURBGANR 5
#define ALTFILVBTOURZEIT 6
#define ALTFILVBTAGTOURZEIT 7
#define ALTFILVBTYP 8
#define ALTFILIBTDELIVERYTIME 9

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define ALTFIL_H
#define ALTFIL_ANZ ( sizeof(ALTFIL_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ALTFIL ********************************************************/

#define ALTFIL_LISTE \
        ALTERNATIVFILIALE.FILIALNR,\
        ALTERNATIVFILIALE.REIHENFOLGENR,\
        ALTERNATIVFILIALE.VERBUNDFILIALNR,\
        ALTERNATIVFILIALE.FILIALTYP,\
        ALTERNATIVFILIALE.KDNR,\
        ALTERNATIVFILIALE.TAGTOURBGANR,\
        ALTERNATIVFILIALE.VBTOURZEIT,\
        ALTERNATIVFILIALE.VBTAGTOURZEIT,\
        ALTERNATIVFILIALE.VBTYP,\
        ALTERNATIVFILIALE.IBTDELIVERYTIME
#define ALTFIL_LISTE_390 \
        FILIALNR,\
        REIHENFOLGENR,\
        VERBUNDFILIALNR,\
        FILIALTYP,\
        KDNR,\
        TAGTOURBGANR,\
        VBTOURZEIT,\
        VBTAGTOURZEIT,\
        VBTYP,\
        IBTDELIVERYTIME
#define ALTFIL_PLISTE \
        "ALTERNATIVFILIALE.FILIALNR,"\
        "ALTERNATIVFILIALE.REIHENFOLGENR,"\
        "ALTERNATIVFILIALE.VERBUNDFILIALNR,"\
        "ALTERNATIVFILIALE.FILIALTYP,"\
        "ALTERNATIVFILIALE.KDNR,"\
        "ALTERNATIVFILIALE.TAGTOURBGANR,"\
        "ALTERNATIVFILIALE.VBTOURZEIT,"\
        "ALTERNATIVFILIALE.VBTAGTOURZEIT,"\
        "ALTERNATIVFILIALE.VBTYP,"\
        "ALTERNATIVFILIALE.IBTDELIVERYTIME"
#define ALTFIL_PELISTE \
        "FILIALNR,"\
        "REIHENFOLGENR,"\
        "VERBUNDFILIALNR,"\
        "FILIALTYP,"\
        "KDNR,"\
        "TAGTOURBGANR,"\
        "VBTOURZEIT,"\
        "VBTAGTOURZEIT,"\
        "VBTYP,"\
        "IBTDELIVERYTIME"
#define ALTFIL_UPDLISTE \
        "FILIALNR=?,"\
        "REIHENFOLGENR=?,"\
        "VERBUNDFILIALNR=?,"\
        "FILIALTYP=?,"\
        "KDNR=?,"\
        "TAGTOURBGANR=?,"\
        "VBTOURZEIT=?,"\
        "VBTAGTOURZEIT=?,"\
        "VBTYP=?,"\
        "IBTDELIVERYTIME=?"
/* SqlMacros-Define of ALTFIL *************************************************/

#define ALTFIL_ZEIGER(x) \
        :x->FILIALNR,\
        :x->REIHENFOLGENR,\
        :x->VERBUNDFILIALNR,\
        :x->FILIALTYP,\
        :x->KDNR,\
        :x->TAGTOURBGANR,\
        :x->VBTOURZEIT,\
        :x->VBTAGTOURZEIT,\
        :x->VBTYP,\
        :x->IBTDELIVERYTIME
#define ALTFIL_ZEIGERSEL(x) \
        :x->FILIALNR,\
        :x->REIHENFOLGENR,\
        :x->VERBUNDFILIALNR,\
        :x->FILIALTYP,\
        :x->KDNR,\
        :x->TAGTOURBGANR,\
        :x->VBTOURZEIT,\
        :x->VBTAGTOURZEIT,\
        :x->VBTYP,\
        :x->IBTDELIVERYTIME
#define ALTFIL_UPDATE(x) \
        ALTERNATIVFILIALE.FILIALNR=:x->FILIALNR,\
        ALTERNATIVFILIALE.REIHENFOLGENR=:x->REIHENFOLGENR,\
        ALTERNATIVFILIALE.VERBUNDFILIALNR=:x->VERBUNDFILIALNR,\
        ALTERNATIVFILIALE.FILIALTYP=:x->FILIALTYP,\
        ALTERNATIVFILIALE.KDNR=:x->KDNR,\
        ALTERNATIVFILIALE.TAGTOURBGANR=:x->TAGTOURBGANR,\
        ALTERNATIVFILIALE.VBTOURZEIT=:x->VBTOURZEIT,\
        ALTERNATIVFILIALE.VBTAGTOURZEIT=:x->VBTAGTOURZEIT,\
        ALTERNATIVFILIALE.VBTYP=:x->VBTYP,\
        ALTERNATIVFILIALE.IBTDELIVERYTIME=:x->IBTDELIVERYTIME
/* SqlMacros390-Define of ALTFIL **********************************************/

#define ALTFIL_ZEIGER_390 \
        :FILIALNR,\
        :REIHENFOLGENR,\
        :VERBUNDFILIALNR,\
        :FILIALTYP,\
        :KDNR,\
        :TAGTOURBGANR,\
        :VBTOURZEIT,\
        :VBTAGTOURZEIT,\
        :VBTYP,\
        :IBTDELIVERYTIME
#define ALTFIL_UPDATE_390 \
        FILIALNR=:FILIALNR,\
        REIHENFOLGENR=:REIHENFOLGENR,\
        VERBUNDFILIALNR=:VERBUNDFILIALNR,\
        FILIALTYP=:FILIALTYP,\
        KDNR=:KDNR,\
        TAGTOURBGANR=:TAGTOURBGANR,\
        VBTOURZEIT=:VBTOURZEIT,\
        VBTAGTOURZEIT=:VBTAGTOURZEIT,\
        VBTYP=:VBTYP,\
        IBTDELIVERYTIME=:IBTDELIVERYTIME
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of ALTFIL **************************************************/

#ifndef TRANSCLASS
typedef struct N_ALTFIL {
    short FILIALNR;
    long REIHENFOLGENR;
    short VERBUNDFILIALNR;
    short FILIALTYP;
    long KDNR;
    long TAGTOURBGANR;
    long VBTOURZEIT;
    long VBTAGTOURZEIT;
    short VBTYP;
    short IBTDELIVERYTIME;
    long FETCH_REL;
} altfilS;
#else /* TRANSCLASS */
typedef struct N_ALTFIL {
    short FILIALNR;
    long REIHENFOLGENR;
    short VERBUNDFILIALNR;
    short FILIALTYP;
    long KDNR;
    long TAGTOURBGANR;
    long VBTOURZEIT;
    long VBTAGTOURZEIT;
    short VBTYP;
    short IBTDELIVERYTIME;
    long FETCH_REL;
    bool operator == (const N_ALTFIL& right) const {
        return (
            FILIALNR == right.FILIALNR &&
            REIHENFOLGENR == right.REIHENFOLGENR &&
            VERBUNDFILIALNR == right.VERBUNDFILIALNR &&
            FILIALTYP == right.FILIALTYP &&
            KDNR == right.KDNR &&
            TAGTOURBGANR == right.TAGTOURBGANR &&
            VBTOURZEIT == right.VBTOURZEIT &&
            VBTAGTOURZEIT == right.VBTAGTOURZEIT &&
            VBTYP == right.VBTYP &&
            IBTDELIVERYTIME == right.IBTDELIVERYTIME
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        FILIALNR = 0;
        REIHENFOLGENR = 0;
        VERBUNDFILIALNR = 0;
        FILIALTYP = 0;
        KDNR = 0;
        TAGTOURBGANR = 0;
        VBTOURZEIT = 0;
        VBTAGTOURZEIT = 0;
        VBTYP = 0;
        IBTDELIVERYTIME = 0;
#endif
    }
} altfilS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ALTFIL ********************************************/

struct S_ALTFIL {
    char FILIALNR[7];
    char REIHENFOLGENR[11];
    char VERBUNDFILIALNR[7];
    char FILIALTYP[7];
    char KDNR[11];
    char TAGTOURBGANR[11];
    char VBTOURZEIT[11];
    char VBTAGTOURZEIT[11];
    char VBTYP[7];
    char IBTDELIVERYTIME[7];
    char FETCH_REL[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ALTFIL ***************************/

struct O_ALTFIL {
    char FILIALNR[7];
    char REIHENFOLGENR[11];
    char VERBUNDFILIALNR[7];
    char FILIALTYP[7];
    char KDNR[11];
    char TAGTOURBGANR[11];
    char VBTOURZEIT[11];
    char VBTAGTOURZEIT[11];
    char VBTYP[7];
    char IBTDELIVERYTIME[7];
    char FETCH_REL[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ALTFIL **************************************/

struct C_ALTFIL {
    short FILIALNR;
    long REIHENFOLGENR;
    short VERBUNDFILIALNR;
    short FILIALTYP;
    long KDNR;
    long TAGTOURBGANR;
    long VBTOURZEIT;
    long VBTAGTOURZEIT;
    short VBTYP;
    short IBTDELIVERYTIME;
    long FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ALTFIL ************************************/

struct I_ALTFIL {
    short FILIALNR;
    short REIHENFOLGENR;
    short VERBUNDFILIALNR;
    short FILIALTYP;
    short KDNR;
    short TAGTOURBGANR;
    short VBTOURZEIT;
    short VBTAGTOURZEIT;
    short VBTYP;
    short IBTDELIVERYTIME;
    short FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ALTFIL **********************************************/

#if defined (BUF_DESC)
static struct buf_desc ALTFIL_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc ALTFIL_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* description for datatypes of ALTFIL ****************************************/

 #define ALTFIL_S390 \
         short FILIALNR; \
         long REIHENFOLGENR; \
         short VERBUNDFILIALNR; \
         short FILIALTYP; \
         long KDNR; \
         long TAGTOURBGANR; \
         long VBTOURZEIT; \
         long VBTAGTOURZEIT; \
         short VBTYP; \
         short IBTDELIVERYTIME; \
         long FETCH_REL;



/* Copy-Function Struct to single Data ALTFIL *********************************/

 #define ALTFIL_S390_COPY_TO_SINGLE(_x_) \
         FILIALNR=_x_->FILIALNR;\
         REIHENFOLGENR=_x_->REIHENFOLGENR;\
         VERBUNDFILIALNR=_x_->VERBUNDFILIALNR;\
         FILIALTYP=_x_->FILIALTYP;\
         KDNR=_x_->KDNR;\
         TAGTOURBGANR=_x_->TAGTOURBGANR;\
         VBTOURZEIT=_x_->VBTOURZEIT;\
         VBTAGTOURZEIT=_x_->VBTAGTOURZEIT;\
         VBTYP=_x_->VBTYP;\
         IBTDELIVERYTIME=_x_->IBTDELIVERYTIME;\
          FETCH_REL=_x_->FETCH_REL;\

 #define ALTFIL_S390_COPY_TO_STRUCT(_x_) \
          _x_->FILIALNR=FILIALNR;\
          _x_->REIHENFOLGENR=REIHENFOLGENR;\
          _x_->VERBUNDFILIALNR=VERBUNDFILIALNR;\
          _x_->FILIALTYP=FILIALTYP;\
          _x_->KDNR=KDNR;\
          _x_->TAGTOURBGANR=TAGTOURBGANR;\
          _x_->VBTOURZEIT=VBTOURZEIT;\
          _x_->VBTAGTOURZEIT=VBTAGTOURZEIT;\
          _x_->VBTYP=VBTYP;\
          _x_->IBTDELIVERYTIME=IBTDELIVERYTIME;\
          _x_->FETCH_REL=FETCH_REL;\



/* FunctionNumber-Define of altfil ********************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of altfil ****************************************/


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

class CALTFIL : public ppDadeVirtual {
public:
    altfilS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<altfilS> lst; // class list

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
                     vector< altfilS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     altfilS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< altfilS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<altfilS>::iterator
                 beginList() { return lst.begin(); }
    vector<altfilS>::iterator
                 endList  () { return lst.end  (); }

    short        GetFilialnr() const { return s.FILIALNR; }
    long         GetReihenfolgenr() const { return s.REIHENFOLGENR; }
    short        GetVerbundfilialnr() const { return s.VERBUNDFILIALNR; }
    short        GetFilialtyp() const { return s.FILIALTYP; }
    long         GetKdnr() const { return s.KDNR; }
    long         GetTagtourbganr() const { return s.TAGTOURBGANR; }
    long         GetVbtourzeit() const { return s.VBTOURZEIT; }
    long         GetVbtagtourzeit() const { return s.VBTAGTOURZEIT; }
    short        GetVbtyp() const { return s.VBTYP; }
    short        GetIbtdeliverytime() const { return s.IBTDELIVERYTIME; }

    const altfilS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetReihenfolgenr(long t) { s.REIHENFOLGENR = t; }
    void         SetVerbundfilialnr(short t) { s.VERBUNDFILIALNR = t; }
    void         SetFilialtyp(short t) { s.FILIALTYP = t; }
    void         SetKdnr(long t) { s.KDNR = t; }
    void         SetTagtourbganr(long t) { s.TAGTOURBGANR = t; }
    void         SetVbtourzeit(long t) { s.VBTOURZEIT = t; }
    void         SetVbtagtourzeit(long t) { s.VBTAGTOURZEIT = t; }
    void         SetVbtyp(short t) { s.VBTYP = t; }
    void         SetIbtdeliverytime(short t) { s.IBTDELIVERYTIME = t; }

    void         SetStruct(const altfilS & t) { s = t; }
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
    CALTFIL() {
        ::buf_default((void *)&s, ALTFIL_BES, ALTFIL_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CALTFIL() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, ALTFIL_BES, ALTFIL_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, ALTFIL_BES, (int)ALTFIL_ANZ, error_msg);
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
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, ALTFIL_BES, (int)ALTFIL_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, ALTFIL_BES, (int)ALTFIL_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_ALTFIL & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, ALTFIL_BES, (int)ALTFIL_ANZ, error_msg);
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
        CALTFIL c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, ALTFIL_BES, (int)ALTFIL_ANZ, error_msg);
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
/* CreateSqlStatement of ALTFIL ***********************************************/

 #define ALTFIL_CREATE(x) EXEC SQL create table x (\
         FILIALNR smallint default 0 not null,\
         REIHENFOLGENR integer default 0 not null,\
         VERBUNDFILIALNR smallint default 0 not null,\
         FILIALTYP smallint default 0 not null,\
         KDNR integer default 0 not null,\
         TAGTOURBGANR integer default 0 not null,\
         VBTOURZEIT integer default 0 not null,\
         VBTAGTOURZEIT integer default 0 not null,\
         VBTYP smallint default 0 not null,\
         IBTDELIVERYTIME smallint default 0 not null) extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of ALTFIL *********************************************/

 #define ALTFIL_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_alternativfili_1 on _X_(\
              filialnr,\
              reihenfolgenr );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index ialternativfilial2 on _X_(\
              verbundfilialnr );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ALTFIL *********************************************/

 #define ALTFIL_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_alternativfili_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index ialternativfilial2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
