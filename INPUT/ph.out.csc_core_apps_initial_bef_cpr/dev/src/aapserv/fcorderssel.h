#ifndef __PP_FCORDERSSEL_H_
#define __PP_FCORDERSSEL_H_

/******************************************************************************/
/* c:\Marathon\orderentry\csc_core_applications\src\aapserv\FCOrdersSel *******/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of FCORDERSSEL ***********************************************/

#define L_FCORDERSSEL_KDAUFTRAGNR 11
#define L_FCORDERSSEL_DATUM 11
#define L_FCORDERSSEL_NAMEAPO 40
#define L_FCORDERSSEL_KDAUFTRAGART 2
#define L_FCORDERSSEL_VERTRIEBSZENTRUMNR 6
#define L_FCORDERSSEL_KUNDENNR 11

/* Length/Count-Define of FCORDERSSEL *****************************************/

#define LS_FCORDERSSEL_KDAUFTRAGNR 10 + 1
#define LS_FCORDERSSEL_DATUM 10 + 1
#define LS_FCORDERSSEL_NAMEAPO 40 + 1
#define LS_FCORDERSSEL_KDAUFTRAGART 2 + 1
#define LS_FCORDERSSEL_VERTRIEBSZENTRUMNR 5 + 1
#define LS_FCORDERSSEL_KUNDENNR 10 + 1

#define FCORDERSSELKDAUFTRAGNR 0
#define FCORDERSSELDATUM 1
#define FCORDERSSELNAMEAPO 2
#define FCORDERSSELKDAUFTRAGART 3
#define FCORDERSSELVERTRIEBSZENTRUMNR 4
#define FCORDERSSELKUNDENNR 5

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define FCORDERSSEL_H
#define FCORDERSSEL_ANZ ( sizeof(FCORDERSSEL_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of FCORDERSSEL ***************************************************/

#define FCORDERSSEL_LISTE \
        KDAUFTRAG.KDAUFTRAGNR,\
        KDAUFTRAGEREIGNIS.DATUM,\
        KUNDE.NAMEAPO,\
        KDAUFTRAG.KDAUFTRAGART,\
        KUNDE.VERTRIEBSZENTRUMNR,\
        KUNDE.KUNDENNR
#define FCORDERSSEL_LISTE_390 \
        KDAUFTRAGNR,\
        DATUM,\
        NAMEAPO,\
        KDAUFTRAGART,\
        VERTRIEBSZENTRUMNR,\
        KUNDENNR
#define FCORDERSSEL_PLISTE \
        "KDAUFTRAG.KDAUFTRAGNR,"\
        "KDAUFTRAGEREIGNIS.DATUM,"\
        "KUNDE.NAMEAPO,"\
        "KDAUFTRAG.KDAUFTRAGART,"\
        "KUNDE.VERTRIEBSZENTRUMNR,"\
        "KUNDE.KUNDENNR"
#define FCORDERSSEL_PELISTE \
        "KDAUFTRAGNR,"\
        "DATUM,"\
        "NAMEAPO,"\
        "KDAUFTRAGART,"\
        "VERTRIEBSZENTRUMNR,"\
        "KUNDENNR"
#define FCORDERSSEL_UPDLISTE \
        "KDAUFTRAGNR=?,"\
        "DATUM=?,"\
        "NAMEAPO=?,"\
        "KDAUFTRAGART=?,"\
        "VERTRIEBSZENTRUMNR=?,"\
        "KUNDENNR=?"
/* SqlMacros-Define of FCORDERSSEL ********************************************/

#define FCORDERSSEL_ZEIGER(x) \
        :x->KDAUFTRAGNR,\
        :x->DATUM,\
        :x->NAMEAPO,\
        :x->KDAUFTRAGART,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR
#define FCORDERSSEL_ZEIGERSEL(x) \
        :x->KDAUFTRAGNR,\
        :x->DATUM,\
        :x->NAMEAPO,\
        :x->KDAUFTRAGART,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR
#define FCORDERSSEL_UPDATE(x) \
        KDAUFTRAG.KDAUFTRAGNR=:x->KDAUFTRAGNR,\
        KDAUFTRAGEREIGNIS.DATUM=:x->DATUM,\
        KUNDE.NAMEAPO=:x->NAMEAPO,\
        KDAUFTRAG.KDAUFTRAGART=:x->KDAUFTRAGART,\
        KUNDE.VERTRIEBSZENTRUMNR=:x->VERTRIEBSZENTRUMNR,\
        KUNDE.KUNDENNR=:x->KUNDENNR
/* SqlMacros390-Define of FCORDERSSEL *****************************************/

#define FCORDERSSEL_ZEIGER_390 \
        :KDAUFTRAGNR,\
        :DATUM,\
        :NAMEAPO,\
        :KDAUFTRAGART,\
        :VERTRIEBSZENTRUMNR,\
        :KUNDENNR
#define FCORDERSSEL_UPDATE_390 \
        KDAUFTRAGNR=:KDAUFTRAGNR,\
        DATUM=:DATUM,\
        NAMEAPO=:NAMEAPO,\
        KDAUFTRAGART=:KDAUFTRAGART,\
        VERTRIEBSZENTRUMNR=:VERTRIEBSZENTRUMNR,\
        KUNDENNR=:KUNDENNR
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of FCORDERSSEL *********************************************/

#ifndef TRANSCLASS
typedef struct N_FCORDERSSEL {
    long KDAUFTRAGNR;
    long DATUM;
    char NAMEAPO[41];
    char KDAUFTRAGART[3];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long FETCH_REL;
} fcordersselS;
#else /* TRANSCLASS */
typedef struct N_FCORDERSSEL {
    long KDAUFTRAGNR;
    long DATUM;
    char NAMEAPO[41];
    char KDAUFTRAGART[3];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long FETCH_REL;
    bool operator == (const N_FCORDERSSEL& right) const {
        return (
            KDAUFTRAGNR == right.KDAUFTRAGNR &&
            DATUM == right.DATUM &&
            !strcmp(NAMEAPO, right.NAMEAPO) &&
            !strcmp(KDAUFTRAGART, right.KDAUFTRAGART) &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        KDAUFTRAGNR = 0;
        DATUM = 0;
        strcpy(NAMEAPO, " " );
        strcpy(KDAUFTRAGART, " " );
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
#endif
    }
} fcordersselS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of FCORDERSSEL ***************************************/

struct S_FCORDERSSEL {
    char KDAUFTRAGNR[11];
    char DATUM[11];
    char NAMEAPO[40 + 1];
    char KDAUFTRAGART[2 + 1];
    char VERTRIEBSZENTRUMNR[7];
    char KUNDENNR[11];
    char FETCH_REL[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of FCORDERSSEL **********************/

struct O_FCORDERSSEL {
    char KDAUFTRAGNR[11];
    char DATUM[11];
    char NAMEAPO[40];
    char KDAUFTRAGART[2];
    char VERTRIEBSZENTRUMNR[7];
    char KUNDENNR[11];
    char FETCH_REL[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of FCORDERSSEL *********************************/

struct C_FCORDERSSEL {
    long KDAUFTRAGNR;
    long DATUM;
    char NAMEAPO[41];
    char KDAUFTRAGART[3];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of FCORDERSSEL *******************************/

struct I_FCORDERSSEL {
    short KDAUFTRAGNR;
    short DATUM;
    short NAMEAPO;
    short KDAUFTRAGART;
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of FCORDERSSEL *****************************************/

#if defined (BUF_DESC)
static struct buf_desc FCORDERSSEL_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 40, 0 },
   { TYP_C, 2, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc FCORDERSSEL_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 40, 0 },
   { TYP_C, 2, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* description for datatypes of FCORDERSSEL ***********************************/

 #define FCORDERSSEL_S390 \
         long KDAUFTRAGNR; \
         long DATUM; \
         char NAMEAPO[41]; \
         char KDAUFTRAGART[3]; \
         short VERTRIEBSZENTRUMNR; \
         long KUNDENNR; \
         long FETCH_REL;



/* Copy-Function Struct to single Data FCORDERSSEL ****************************/

 #define FCORDERSSEL_S390_COPY_TO_SINGLE(_x_) \
         KDAUFTRAGNR=_x_->KDAUFTRAGNR;\
         DATUM=_x_->DATUM;\
          strcpy(NAMEAPO,_x_->NAMEAPO);\
          strcpy(KDAUFTRAGART,_x_->KDAUFTRAGART);\
         VERTRIEBSZENTRUMNR=_x_->VERTRIEBSZENTRUMNR;\
         KUNDENNR=_x_->KUNDENNR;\
          FETCH_REL=_x_->FETCH_REL;\

 #define FCORDERSSEL_S390_COPY_TO_STRUCT(_x_) \
          _x_->KDAUFTRAGNR=KDAUFTRAGNR;\
          _x_->DATUM=DATUM;\
          strcpy(_x_->NAMEAPO,NAMEAPO);\
          strcpy(_x_->KDAUFTRAGART,KDAUFTRAGART);\
          _x_->VERTRIEBSZENTRUMNR=VERTRIEBSZENTRUMNR;\
          _x_->KUNDENNR=KUNDENNR;\
          _x_->FETCH_REL=FETCH_REL;\



/* FunctionNumber-Define of FCOrdersSel ***************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of FCOrdersSel ***********************************/


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

class CFCORDERSSEL : public ppDadeVirtual {
public:
    fcordersselS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<fcordersselS> lst; // class list

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
                     vector< fcordersselS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     fcordersselS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< fcordersselS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<fcordersselS>::iterator
                 beginList() { return lst.begin(); }
    vector<fcordersselS>::iterator
                 endList  () { return lst.end  (); }

    long         GetKdauftragnr() const { return s.KDAUFTRAGNR; }
    long         GetDatum() const { return s.DATUM; }
    const char*  GetNameapo(ppString & t) const { t = s.NAMEAPO; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetKdauftragart(ppString & t) const { t = s.KDAUFTRAGART; t.erasespace(ppString::END); return t.c_str(); }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }

    const fcordersselS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
    void         SetDatum(long t) { s.DATUM = t; }
    void         SetNameapo(const ppString & t) { ppGStrCopy(s.NAMEAPO, t.c_str(), L_FCORDERSSEL_NAMEAPO); }
    void         SetKdauftragart(const ppString & t) { ppGStrCopy(s.KDAUFTRAGART, t.c_str(), L_FCORDERSSEL_KDAUFTRAGART); }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }

    void         SetStruct(const fcordersselS & t) { s = t; }
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
    CFCORDERSSEL() {
        ::buf_default((void *)&s, FCORDERSSEL_BES, FCORDERSSEL_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CFCORDERSSEL() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, FCORDERSSEL_BES, FCORDERSSEL_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, FCORDERSSEL_BES, (int)FCORDERSSEL_ANZ, error_msg);
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
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, FCORDERSSEL_BES, (int)FCORDERSSEL_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, FCORDERSSEL_BES, (int)FCORDERSSEL_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_FCORDERSSEL & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.NAMEAPO);
        ppGStripLast(d.KDAUFTRAGART);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, FCORDERSSEL_BES, (int)FCORDERSSEL_ANZ, error_msg);
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
        CFCORDERSSEL c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, FCORDERSSEL_BES, (int)FCORDERSSEL_ANZ, error_msg);
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
/* CreateSqlStatement of FCORDERSSEL ******************************************/

 #define FCORDERSSEL_CREATE(x) EXEC SQL create table x (\
         KDAUFTRAGNR integer default 0 not null,\
         DATUM integer default 0 not null,\
         NAMEAPO char(40) default " " not null,\
         KDAUFTRAGART char(2) default " " not null,\
         VERTRIEBSZENTRUMNR smallint default 0 not null,\
         KUNDENNR integer default 0 not null) extent size 940 next size 96 lock mode row;



/* CreateIndexStatement of FCORDERSSEL ****************************************/

 #define FCORDERSSEL_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create   index i_kdauftrag_303 on _X_(\
              kdauftragstat );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index i_kdauftrag_304 on _X_(\
              idfnr );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index i_kdauftrag_305 on _X_(\
              geraetname );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index i_kdauftrag_306 on _X_(\
              filialnr );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index i_kdauftrag_307 on _X_(\
              VertriebszentrumNr,\
              KundenNr );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index i_kdauftrag_308 on _X_(\
              KdauftragNrFiliale );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index i_kdauftrag_309 on _X_(\
              datumauslieferung );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index i_kdauftrag_310 on _X_(\
              InvoiceNumber );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index kdauftragtourx on _X_(\
              tourid );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create unique index kdauftragx on _X_(\
              kdauftragnr );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of FCORDERSSEL ****************************************/

 #define FCORDERSSEL_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_kdauftrag_303;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_kdauftrag_304;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_kdauftrag_305;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_kdauftrag_306;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_kdauftrag_307;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_kdauftrag_308;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_kdauftrag_309;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_kdauftrag_310;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index kdauftragtourx;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index kdauftragx;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
