#ifndef __PP_TOURDELAY_H_
#define __PP_TOURDELAY_H_

/******************************************************************************/
/* c:\prri\Headerfiles\TourDelay **********************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of TOURDELAY *************************************************/

#define L_TOURDELAY_KDAUFTRAGNR 11
#define L_TOURDELAY_DATUMKOMMI 11
#define L_TOURDELAY_TOURID 6
#define L_TOURDELAY_VERTRIEBSZENTRUMNR 6
#define L_TOURDELAY_KUNDENNR 11
#define L_TOURDELAY_DELAYTEXT 100

/* Length/Count-Define of TOURDELAY *******************************************/

#define LS_TOURDELAY_KDAUFTRAGNR 10 + 1
#define LS_TOURDELAY_DATUMKOMMI 10 + 1
#define LS_TOURDELAY_TOURID 6 + 1
#define LS_TOURDELAY_VERTRIEBSZENTRUMNR 5 + 1
#define LS_TOURDELAY_KUNDENNR 10 + 1
#define LS_TOURDELAY_DELAYTEXT 100 + 1

#define TOURDELAYKDAUFTRAGNR 0
#define TOURDELAYDATUMKOMMI 1
#define TOURDELAYTOURID 2
#define TOURDELAYVERTRIEBSZENTRUMNR 3
#define TOURDELAYKUNDENNR 4
#define TOURDELAYDELAYTEXT 5

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define TOURDELAY_H
#define TOURDELAY_ANZ ( sizeof(TOURDELAY_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of TOURDELAY *****************************************************/

#define TOURDELAY_LISTE \
        KDAUFTRAG.KDAUFTRAGNR,\
        TOURPLANTAG.DATUMKOMMI,\
        TOURPLANTAG.TOURID,\
        TOURPLANTAG.VERTRIEBSZENTRUMNR,\
        TOURPLANTAG.KUNDENNR,\
        AADUMMY.DELAYTEXT
#define TOURDELAY_LISTE_390 \
        KDAUFTRAGNR,\
        DATUMKOMMI,\
        TOURID,\
        VERTRIEBSZENTRUMNR,\
        KUNDENNR,\
        DELAYTEXT
#define TOURDELAY_PLISTE \
        "KDAUFTRAG.KDAUFTRAGNR,"\
        "TOURPLANTAG.DATUMKOMMI,"\
        "TOURPLANTAG.TOURID,"\
        "TOURPLANTAG.VERTRIEBSZENTRUMNR,"\
        "TOURPLANTAG.KUNDENNR,"\
        "AADUMMY.DELAYTEXT"
#define TOURDELAY_PELISTE \
        "KDAUFTRAGNR,"\
        "DATUMKOMMI,"\
        "TOURID,"\
        "VERTRIEBSZENTRUMNR,"\
        "KUNDENNR,"\
        "DELAYTEXT"
#define TOURDELAY_UPDLISTE \
        "KDAUFTRAGNR=?,"\
        "DATUMKOMMI=?,"\
        "TOURID=?,"\
        "VERTRIEBSZENTRUMNR=?,"\
        "KUNDENNR=?,"\
        "DELAYTEXT=?"
/* SqlMacros-Define of TOURDELAY **********************************************/

#define TOURDELAY_ZEIGER(x) \
        :x->KDAUFTRAGNR,\
        :x->DATUMKOMMI,\
        :x->TOURID,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->DELAYTEXT
#define TOURDELAY_ZEIGERSEL(x) \
        :x->KDAUFTRAGNR,\
        :x->DATUMKOMMI,\
        :x->TOURID,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->DELAYTEXT
#define TOURDELAY_UPDATE(x) \
        KDAUFTRAG.KDAUFTRAGNR=:x->KDAUFTRAGNR,\
        TOURPLANTAG.DATUMKOMMI=:x->DATUMKOMMI,\
        TOURPLANTAG.TOURID=:x->TOURID,\
        TOURPLANTAG.VERTRIEBSZENTRUMNR=:x->VERTRIEBSZENTRUMNR,\
        TOURPLANTAG.KUNDENNR=:x->KUNDENNR,\
        AADUMMY.DELAYTEXT=:x->DELAYTEXT
/* SqlMacros390-Define of TOURDELAY *******************************************/

#define TOURDELAY_ZEIGER_390 \
        :KDAUFTRAGNR,\
        :DATUMKOMMI,\
        :TOURID,\
        :VERTRIEBSZENTRUMNR,\
        :KUNDENNR,\
        :DELAYTEXT
#define TOURDELAY_UPDATE_390 \
        KDAUFTRAGNR=:KDAUFTRAGNR,\
        DATUMKOMMI=:DATUMKOMMI,\
        TOURID=:TOURID,\
        VERTRIEBSZENTRUMNR=:VERTRIEBSZENTRUMNR,\
        KUNDENNR=:KUNDENNR,\
        DELAYTEXT=:DELAYTEXT
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of TOURDELAY ***********************************************/

#ifndef TRANSCLASS
typedef struct N_TOURDELAY {
    long KDAUFTRAGNR;
    long DATUMKOMMI;
    char TOURID[7];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char DELAYTEXT[101];
} tourdelayS;
#else /* TRANSCLASS */
typedef struct N_TOURDELAY {
    long KDAUFTRAGNR;
    long DATUMKOMMI;
    char TOURID[7];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char DELAYTEXT[101];

    bool operator == (const N_TOURDELAY& right) const {
        return (
            KDAUFTRAGNR == right.KDAUFTRAGNR &&
            DATUMKOMMI == right.DATUMKOMMI &&
            !strcmp(TOURID, right.TOURID) &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            !strcmp(DELAYTEXT, right.DELAYTEXT)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        KDAUFTRAGNR = 0;
        DATUMKOMMI = 0;
        strcpy(TOURID, " " );
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        strcpy(DELAYTEXT, " " );
#endif
    }
} tourdelayS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of TOURDELAY *****************************************/

struct S_TOURDELAY {
    char KDAUFTRAGNR[11];
    char DATUMKOMMI[11];
    char TOURID[6 + 1];
    char VERTRIEBSZENTRUMNR[7];
    char KUNDENNR[11];
    char DELAYTEXT[100 + 1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of TOURDELAY ************************/

struct O_TOURDELAY {
    char KDAUFTRAGNR[11];
    char DATUMKOMMI[11];
    char TOURID[6];
    char VERTRIEBSZENTRUMNR[7];
    char KUNDENNR[11];
    char DELAYTEXT[100];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of TOURDELAY ***********************************/

struct C_TOURDELAY {
    long KDAUFTRAGNR;
    long DATUMKOMMI;
    char TOURID[7];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char DELAYTEXT[101];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of TOURDELAY *********************************/

struct I_TOURDELAY {
    short KDAUFTRAGNR;
    short DATUMKOMMI;
    short TOURID;
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short DELAYTEXT;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of TOURDELAY *******************************************/

#if defined (BUF_DESC)
static struct buf_desc TOURDELAY_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 100, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc TOURDELAY_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 100, 0 },
};
#endif

/* description for datatypes of TOURDELAY *************************************/

 #define TOURDELAY_S390 \
         long KDAUFTRAGNR; \
         long DATUMKOMMI; \
         char TOURID[7]; \
         short VERTRIEBSZENTRUMNR; \
         long KUNDENNR; \
         char DELAYTEXT[101]; \



/* Copy-Function Struct to single Data TOURDELAY ******************************/

 #define TOURDELAY_S390_COPY_TO_SINGLE(_x_) \
         KDAUFTRAGNR=_x_->KDAUFTRAGNR;\
         DATUMKOMMI=_x_->DATUMKOMMI;\
          strcpy(TOURID,_x_->TOURID);\
         VERTRIEBSZENTRUMNR=_x_->VERTRIEBSZENTRUMNR;\
         KUNDENNR=_x_->KUNDENNR;\
          strcpy(DELAYTEXT,_x_->DELAYTEXT);\

 #define TOURDELAY_S390_COPY_TO_STRUCT(_x_) \
          _x_->KDAUFTRAGNR=KDAUFTRAGNR;\
          _x_->DATUMKOMMI=DATUMKOMMI;\
          strcpy(_x_->TOURID,TOURID);\
          _x_->VERTRIEBSZENTRUMNR=VERTRIEBSZENTRUMNR;\
          _x_->KUNDENNR=KUNDENNR;\
          strcpy(_x_->DELAYTEXT,DELAYTEXT);\



/* FunctionNumber-Define of TourDelay *****************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of TourDelay *************************************/


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

class CTOURDELAY : public ppDadeVirtual {
public:
    tourdelayS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<tourdelayS> lst; // class list

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
                     vector< tourdelayS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     tourdelayS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< tourdelayS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<tourdelayS>::iterator
                 beginList() { return lst.begin(); }
    vector<tourdelayS>::iterator
                 endList  () { return lst.end  (); }

    long         GetKdauftragnr() const { return s.KDAUFTRAGNR; }
    long         GetDatumkommi() const { return s.DATUMKOMMI; }
    const char*  GetTourid(ppString & t) const { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    const char*  GetDelaytext(ppString & t) const { t = s.DELAYTEXT; t.erasespace(ppString::END); return t.c_str(); }

    const tourdelayS &
                 GetStruct() const { return s; }
    void         SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
    void         SetDatumkommi(long t) { s.DATUMKOMMI = t; }
    void         SetTourid(const ppString & t) { ppGStrCopy(s.TOURID, t.c_str(), L_TOURDELAY_TOURID); }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetDelaytext(const ppString & t) { ppGStrCopy(s.DELAYTEXT, t.c_str(), L_TOURDELAY_DELAYTEXT); }

    void         SetStruct(const tourdelayS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CTOURDELAY() {
        ::buf_default((void *)&s, TOURDELAY_BES, TOURDELAY_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CTOURDELAY() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, TOURDELAY_BES, TOURDELAY_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, TOURDELAY_BES, (int)TOURDELAY_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, TOURDELAY_BES, (int)TOURDELAY_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_TOURDELAY & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.TOURID);
        ppGStripLast(d.DELAYTEXT);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, TOURDELAY_BES, (int)TOURDELAY_ANZ, error_msg);
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
/* CreateSqlStatement of TOURDELAY ********************************************/

 #define TOURDELAY_CREATE(x) EXEC SQL create table x (\
         KDAUFTRAGNR integer default 0 not null,\
         DATUMKOMMI integer default 0 not null,\
         TOURID char(6) default " " not null,\
         VERTRIEBSZENTRUMNR smallint default 0 not null,\
         KUNDENNR integer default 0 not null,\
         DELAYTEXT char(100) default " " not null) extent size 940 next size 96 lock mode row;



/* CreateIndexStatement of TOURDELAY ******************************************/

 #define TOURDELAY_CREATE_INDEX(_X_,_Y_)\
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
         EXEC SQL create   index i_kdauftrag_311 on _X_(\
              rechnungnr );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index kdauftragtourx on _X_(\
              tourid );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create unique index kdauftragx on _X_(\
              kdauftragnr );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of TOURDELAY ******************************************/

 #define TOURDELAY_DELETE_INDEX(_X_)\
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
         EXEC SQL drop index i_kdauftrag_311;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index kdauftragtourx;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index kdauftragx;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
