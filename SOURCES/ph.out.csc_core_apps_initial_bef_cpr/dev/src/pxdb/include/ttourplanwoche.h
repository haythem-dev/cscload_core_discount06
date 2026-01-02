#ifndef __PP_TOURPLANWOCHE_H_
#define __PP_TOURPLANWOCHE_H_

/******************************************************************************/
/* c:\temp\tourplanwoche ******************************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of TOURPLANWOCHE *********************************************/

#define L_TOURPLANWOCHE_TOURID 6
#define L_TOURPLANWOCHE_TAGESTYP 6
#define L_TOURPLANWOCHE_KZUPD 1
#define L_TOURPLANWOCHE_FILIALNR 6
#define L_TOURPLANWOCHE_WEEKDAY 6
#define L_TOURPLANWOCHE_LAGRECHTOUR 11
#define L_TOURPLANWOCHE_KARENZZEIT 6

/* Length/Count-Define of TOURPLANWOCHE ***************************************/

#define LS_TOURPLANWOCHE_TOURID 6 + 1
#define LS_TOURPLANWOCHE_TAGESTYP 6 + 1
#define LS_TOURPLANWOCHE_KZUPD 1 + 1
#define LS_TOURPLANWOCHE_FILIALNR 5 + 1
#define LS_TOURPLANWOCHE_WEEKDAY 5 + 1
#define LS_TOURPLANWOCHE_LAGRECHTOUR 10 + 1
#define LS_TOURPLANWOCHE_KARENZZEIT 5 + 1

#define TOURPLANWOCHETOURID 0
#define TOURPLANWOCHETAGESTYP 1
#define TOURPLANWOCHEKZUPD 2
#define TOURPLANWOCHEFILIALNR 3
#define TOURPLANWOCHEWEEKDAY 4
#define TOURPLANWOCHELAGRECHTOUR 5
#define TOURPLANWOCHEKARENZZEIT 6

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define TOURPLANWOCHE_H
#define TOURPLANWOCHE_ANZ ( sizeof(TOURPLANWOCHE_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of TOURPLANWOCHE *************************************************/

#define TOURPLANWOCHE_LISTE \
        TOURPLANWOCHE.TOURID,\
        TOURPLANWOCHE.TAGESTYP,\
        TOURPLANWOCHE.KZUPD,\
        TOURPLANWOCHE.FILIALNR,\
        TOURPLANWOCHE.WEEKDAY,\
        TOURPLANWOCHE.LAGRECHTOUR,\
        TOURPLANWOCHE.KARENZZEIT
#define TOURPLANWOCHE_LISTE_390 \
        TOURID,\
        TAGESTYP,\
        KZUPD,\
        FILIALNR,\
        WEEKDAY,\
        LAGRECHTOUR,\
        KARENZZEIT
#define TOURPLANWOCHE_PLISTE \
        "TOURPLANWOCHE.TOURID,"\
        "TOURPLANWOCHE.TAGESTYP,"\
        "TOURPLANWOCHE.KZUPD,"\
        "TOURPLANWOCHE.FILIALNR,"\
        "TOURPLANWOCHE.WEEKDAY,"\
        "TOURPLANWOCHE.LAGRECHTOUR,"\
        "TOURPLANWOCHE.KARENZZEIT"
#define TOURPLANWOCHE_PELISTE \
        "TOURID,"\
        "TAGESTYP,"\
        "KZUPD,"\
        "FILIALNR,"\
        "WEEKDAY,"\
        "LAGRECHTOUR,"\
        "KARENZZEIT"
#define TOURPLANWOCHE_UPDLISTE \
        "TOURID=?,"\
        "TAGESTYP=?,"\
        "KZUPD=?,"\
        "FILIALNR=?,"\
        "WEEKDAY=?,"\
        "LAGRECHTOUR=?,"\
        "KARENZZEIT=?"
/* SqlMacros-Define of TOURPLANWOCHE ******************************************/

#define TOURPLANWOCHE_ZEIGER(x) \
        :x->TOURID,\
        :x->TAGESTYP,\
        :x->KZUPD,\
        :x->FILIALNR,\
        :x->WEEKDAY,\
        :x->LAGRECHTOUR,\
        :x->KARENZZEIT
#define TOURPLANWOCHE_ZEIGERSEL(x) \
        :x->TOURID,\
        :x->TAGESTYP,\
        :x->KZUPD,\
        :x->FILIALNR,\
        :x->WEEKDAY,\
        :x->LAGRECHTOUR,\
        :x->KARENZZEIT
#define TOURPLANWOCHE_UPDATE(x) \
        TOURPLANWOCHE.TOURID=:x->TOURID,\
        TOURPLANWOCHE.TAGESTYP=:x->TAGESTYP,\
        TOURPLANWOCHE.KZUPD=:x->KZUPD,\
        TOURPLANWOCHE.FILIALNR=:x->FILIALNR,\
        TOURPLANWOCHE.WEEKDAY=:x->WEEKDAY,\
        TOURPLANWOCHE.LAGRECHTOUR=:x->LAGRECHTOUR,\
        TOURPLANWOCHE.KARENZZEIT=:x->KARENZZEIT
/* SqlMacros390-Define of TOURPLANWOCHE ***************************************/

#define TOURPLANWOCHE_ZEIGER_390 \
        :TOURID,\
        :TAGESTYP,\
        :KZUPD,\
        :FILIALNR,\
        :WEEKDAY,\
        :LAGRECHTOUR,\
        :KARENZZEIT
#define TOURPLANWOCHE_UPDATE_390 \
        TOURID=:TOURID,\
        TAGESTYP=:TAGESTYP,\
        KZUPD=:KZUPD,\
        FILIALNR=:FILIALNR,\
        WEEKDAY=:WEEKDAY,\
        LAGRECHTOUR=:LAGRECHTOUR,\
        KARENZZEIT=:KARENZZEIT
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of TOURPLANWOCHE *******************************************/

#ifndef TRANSCLASS
typedef struct N_TOURPLANWOCHE {
    char TOURID[7];
    char TAGESTYP[7];
    char KZUPD[2];
    short FILIALNR;
    short WEEKDAY;
    long LAGRECHTOUR;
    short KARENZZEIT;
} tourplanwocheS;
#else /* TRANSCLASS */
typedef struct N_TOURPLANWOCHE {
    char TOURID[7];
    char TAGESTYP[7];
    char KZUPD[2];
    short FILIALNR;
    short WEEKDAY;
    long LAGRECHTOUR;
    short KARENZZEIT;

    bool operator == (const N_TOURPLANWOCHE& right) const {
        return (
            !strcmp(TOURID, right.TOURID) &&
            !strcmp(TAGESTYP, right.TAGESTYP) &&
            !strcmp(KZUPD, right.KZUPD) &&
            FILIALNR == right.FILIALNR &&
            WEEKDAY == right.WEEKDAY &&
            LAGRECHTOUR == right.LAGRECHTOUR &&
            KARENZZEIT == right.KARENZZEIT
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        strcpy(TOURID, " " );
        strcpy(TAGESTYP, " " );
        strcpy(KZUPD, " " );
        FILIALNR = 0;
        WEEKDAY = 0;
        LAGRECHTOUR = 0;
        KARENZZEIT = 0;
#endif
    }
} tourplanwocheS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of TOURPLANWOCHE *************************************/

struct S_TOURPLANWOCHE {
    char TOURID[6 + 1];
    char TAGESTYP[6 + 1];
    char KZUPD[1 + 1];
    char FILIALNR[7];
    char WEEKDAY[7];
    char LAGRECHTOUR[11];
    char KARENZZEIT[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of TOURPLANWOCHE ********************/

struct O_TOURPLANWOCHE {
    char TOURID[6];
    char TAGESTYP[6];
    char KZUPD[1];
    char FILIALNR[7];
    char WEEKDAY[7];
    char LAGRECHTOUR[11];
    char KARENZZEIT[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of TOURPLANWOCHE *******************************/

struct C_TOURPLANWOCHE {
    char TOURID[7];
    char TAGESTYP[7];
    char KZUPD;
    short FILIALNR;
    short WEEKDAY;
    long LAGRECHTOUR;
    short KARENZZEIT;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of TOURPLANWOCHE *****************************/

struct I_TOURPLANWOCHE {
    short TOURID;
    short TAGESTYP;
    short KZUPD;
    short FILIALNR;
    short WEEKDAY;
    short LAGRECHTOUR;
    short KARENZZEIT;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of TOURPLANWOCHE ***************************************/

#if defined (BUF_DESC)
static struct buf_desc TOURPLANWOCHE_BES [] = {
   { TYP_C, 6, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc TOURPLANWOCHE_BES [] = {
   { TYP_C, 6, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* description for datatypes of TOURPLANWOCHE *********************************/

 #define TOURPLANWOCHE_S390 \
         char TOURID[7]; \
         char TAGESTYP[7]; \
         char KZUPD; \
         short FILIALNR; \
         short WEEKDAY; \
         long LAGRECHTOUR; \
         short KARENZZEIT; \



/* Copy-Function Struct to single Data TOURPLANWOCHE **************************/

 #define TOURPLANWOCHE_S390_COPY_TO_SINGLE(_x_) \
          strcpy(TOURID,_x_->TOURID);\
          strcpy(TAGESTYP,_x_->TAGESTYP);\
         KZUPD=_x_->KZUPD;\
         FILIALNR=_x_->FILIALNR;\
         WEEKDAY=_x_->WEEKDAY;\
         LAGRECHTOUR=_x_->LAGRECHTOUR;\
         KARENZZEIT=_x_->KARENZZEIT;\

 #define TOURPLANWOCHE_S390_COPY_TO_STRUCT(_x_) \
          strcpy(_x_->TOURID,TOURID);\
          strcpy(_x_->TAGESTYP,TAGESTYP);\
          _x_->KZUPD=KZUPD;\
          _x_->FILIALNR=FILIALNR;\
          _x_->WEEKDAY=WEEKDAY;\
          _x_->LAGRECHTOUR=LAGRECHTOUR;\
          _x_->KARENZZEIT=KARENZZEIT;\



/* FunctionNumber-Define of tourplanwoche *************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of tourplanwoche *********************************/


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

class CTOURPLANWOCHE : public ppDadeVirtual {
public:
    tourplanwocheS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<tourplanwocheS> lst; // class list

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
                     vector< tourplanwocheS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     tourplanwocheS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< tourplanwocheS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<tourplanwocheS>::iterator
                 beginList() { return lst.begin(); }
    vector<tourplanwocheS>::iterator
                 endList  () { return lst.end  (); }

    const char*  GetTourid(ppString & t) const { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetTagestyp(ppString & t) const { t = s.TAGESTYP; t.erasespace(ppString::END); return t.c_str(); }
    char         GetKzupd() const { return s.KZUPD[0]; }
    short        GetFilialnr() const { return s.FILIALNR; }
    short        GetWeekday() const { return s.WEEKDAY; }
    long         GetLagrechtour() const { return s.LAGRECHTOUR; }
    short        GetKarenzzeit() const { return s.KARENZZEIT; }

    const tourplanwocheS &
                 GetStruct() const { return s; }
    void         SetTourid(const ppString & t) { ppGStrCopy(s.TOURID, t.c_str(), L_TOURPLANWOCHE_TOURID); }
    void         SetTagestyp(const ppString & t) { ppGStrCopy(s.TAGESTYP, t.c_str(), L_TOURPLANWOCHE_TAGESTYP); }
    void         SetKzupd(char t) { s.KZUPD[0] = t; s.KZUPD[1] = '\0';}
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetWeekday(short t) { s.WEEKDAY = t; }
    void         SetLagrechtour(long t) { s.LAGRECHTOUR = t; }
    void         SetKarenzzeit(short t) { s.KARENZZEIT = t; }

    void         SetStruct(const tourplanwocheS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CTOURPLANWOCHE() {
        ::buf_default((void *)&s, TOURPLANWOCHE_BES, TOURPLANWOCHE_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CTOURPLANWOCHE() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, TOURPLANWOCHE_BES, TOURPLANWOCHE_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, TOURPLANWOCHE_BES, (int)TOURPLANWOCHE_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, TOURPLANWOCHE_BES, (int)TOURPLANWOCHE_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_TOURPLANWOCHE & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.TOURID);
        ppGStripLast(d.TAGESTYP);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, TOURPLANWOCHE_BES, (int)TOURPLANWOCHE_ANZ, error_msg);
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
/* CreateSqlStatement of TOURPLANWOCHE ****************************************/

 #define TOURPLANWOCHE_CREATE(x) EXEC SQL create table x (\
         TOURID char(6) default " " not null,\
         TAGESTYP char(6) default " " not null,\
         KZUPD char(1) default " " not null,\
         FILIALNR smallint default 0 not null,\
         WEEKDAY smallint default 0 not null,\
         LAGRECHTOUR integer default 0 not null,\
         KARENZZEIT smallint default 0 not null) in ksc extent size 284 next size 32 lock mode row;



/* CreateIndexStatement of TOURPLANWOCHE **************************************/

 #define TOURPLANWOCHE_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_tourplanwoche_1 on _X_(\
              filialnr,\
              tourid,\
              weekday ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of TOURPLANWOCHE **************************************/

 #define TOURPLANWOCHE_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_tourplanwoche_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
