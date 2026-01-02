#ifndef __PP_TOUR_H_
#define __PP_TOUR_H_

/******************************************************************************/
/* c:\temp\tour ***************************************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of TOUR ******************************************************/

#define L_TOUR_DATUMKOMMI 11
#define L_TOUR_TOURID 6
#define L_TOUR_ZEITKOENDE 11
#define L_TOUR_DATUMVERSAND 11
#define L_TOUR_ZEITVERSAND 11
#define L_TOUR_BAHNHOFVERSAND 6
#define L_TOUR_TOURSTAT 1
#define L_TOUR_LAGRECHTOUR 11
#define L_TOUR_FILIALNR 6
#define L_TOUR_KDAUFTRAGART 2
#define L_TOUR_TOURINAKTIV 1
#define L_TOUR_ERSATZFILIALNR 6
#define L_TOUR_KIPPZEIT 6
#define L_TOUR_CHECKTIMETOTOUR 6
#define L_TOUR_SCHECKORDER 6
#define L_TOUR_KARENZZEIT 6

/* Length/Count-Define of TOUR ************************************************/

#define LS_TOUR_DATUMKOMMI 10 + 1
#define LS_TOUR_TOURID 6 + 1
#define LS_TOUR_ZEITKOENDE 10 + 1
#define LS_TOUR_DATUMVERSAND 10 + 1
#define LS_TOUR_ZEITVERSAND 10 + 1
#define LS_TOUR_BAHNHOFVERSAND 5 + 1
#define LS_TOUR_TOURSTAT 1 + 1
#define LS_TOUR_LAGRECHTOUR 10 + 1
#define LS_TOUR_FILIALNR 5 + 1
#define LS_TOUR_KDAUFTRAGART 2 + 1
#define LS_TOUR_TOURINAKTIV 1 + 1
#define LS_TOUR_ERSATZFILIALNR 5 + 1
#define LS_TOUR_KIPPZEIT 5 + 1
#define LS_TOUR_CHECKTIMETOTOUR 5 + 1
#define LS_TOUR_SCHECKORDER 5 + 1
#define LS_TOUR_KARENZZEIT 5 + 1

#define TOURDATUMKOMMI 0
#define TOURTOURID 1
#define TOURZEITKOENDE 2
#define TOURDATUMVERSAND 3
#define TOURZEITVERSAND 4
#define TOURBAHNHOFVERSAND 5
#define TOURTOURSTAT 6
#define TOURLAGRECHTOUR 7
#define TOURFILIALNR 8
#define TOURKDAUFTRAGART 9
#define TOURTOURINAKTIV 10
#define TOURERSATZFILIALNR 11
#define TOURKIPPZEIT 12
#define TOURCHECKTIMETOTOUR 13
#define TOURSCHECKORDER 14
#define TOURKARENZZEIT 15

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define TOUR_H
#define TOUR_ANZ ( sizeof(TOUR_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of TOUR **********************************************************/

#define TOUR_LISTE \
        TOUR.DATUMKOMMI,\
        TOUR.TOURID,\
        TOUR.ZEITKOENDE,\
        TOUR.DATUMVERSAND,\
        TOUR.ZEITVERSAND,\
        TOUR.BAHNHOFVERSAND,\
        TOUR.TOURSTAT,\
        TOUR.LAGRECHTOUR,\
        TOUR.FILIALNR,\
        TOUR.KDAUFTRAGART,\
        TOUR.TOURINAKTIV,\
        TOUR.ERSATZFILIALNR,\
        TOUR.KIPPZEIT,\
        TOUR.CHECKTIMETOTOUR,\
        TOUR.SCHECKORDER,\
        TOUR.KARENZZEIT
#define TOUR_LISTE_390 \
        DATUMKOMMI,\
        TOURID,\
        ZEITKOENDE,\
        DATUMVERSAND,\
        ZEITVERSAND,\
        BAHNHOFVERSAND,\
        TOURSTAT,\
        LAGRECHTOUR,\
        FILIALNR,\
        KDAUFTRAGART,\
        TOURINAKTIV,\
        ERSATZFILIALNR,\
        KIPPZEIT,\
        CHECKTIMETOTOUR,\
        SCHECKORDER,\
        KARENZZEIT
#define TOUR_PLISTE \
        "TOUR.DATUMKOMMI,"\
        "TOUR.TOURID,"\
        "TOUR.ZEITKOENDE,"\
        "TOUR.DATUMVERSAND,"\
        "TOUR.ZEITVERSAND,"\
        "TOUR.BAHNHOFVERSAND,"\
        "TOUR.TOURSTAT,"\
        "TOUR.LAGRECHTOUR,"\
        "TOUR.FILIALNR,"\
        "TOUR.KDAUFTRAGART,"\
        "TOUR.TOURINAKTIV,"\
        "TOUR.ERSATZFILIALNR,"\
        "TOUR.KIPPZEIT,"\
        "TOUR.CHECKTIMETOTOUR,"\
        "TOUR.SCHECKORDER,"\
        "TOUR.KARENZZEIT"
#define TOUR_PELISTE \
        "DATUMKOMMI,"\
        "TOURID,"\
        "ZEITKOENDE,"\
        "DATUMVERSAND,"\
        "ZEITVERSAND,"\
        "BAHNHOFVERSAND,"\
        "TOURSTAT,"\
        "LAGRECHTOUR,"\
        "FILIALNR,"\
        "KDAUFTRAGART,"\
        "TOURINAKTIV,"\
        "ERSATZFILIALNR,"\
        "KIPPZEIT,"\
        "CHECKTIMETOTOUR,"\
        "SCHECKORDER,"\
        "KARENZZEIT"
#define TOUR_UPDLISTE \
        "DATUMKOMMI=?,"\
        "TOURID=?,"\
        "ZEITKOENDE=?,"\
        "DATUMVERSAND=?,"\
        "ZEITVERSAND=?,"\
        "BAHNHOFVERSAND=?,"\
        "TOURSTAT=?,"\
        "LAGRECHTOUR=?,"\
        "FILIALNR=?,"\
        "KDAUFTRAGART=?,"\
        "TOURINAKTIV=?,"\
        "ERSATZFILIALNR=?,"\
        "KIPPZEIT=?,"\
        "CHECKTIMETOTOUR=?,"\
        "SCHECKORDER=?,"\
        "KARENZZEIT=?"
/* SqlMacros-Define of TOUR ***************************************************/

#define TOUR_ZEIGER(x) \
        :x->DATUMKOMMI,\
        :x->TOURID,\
        :x->ZEITKOENDE,\
        :x->DATUMVERSAND,\
        :x->ZEITVERSAND,\
        :x->BAHNHOFVERSAND,\
        :x->TOURSTAT,\
        :x->LAGRECHTOUR,\
        :x->FILIALNR,\
        :x->KDAUFTRAGART,\
        :x->TOURINAKTIV,\
        :x->ERSATZFILIALNR,\
        :x->KIPPZEIT,\
        :x->CHECKTIMETOTOUR,\
        :x->SCHECKORDER,\
        :x->KARENZZEIT
#define TOUR_ZEIGERSEL(x) \
        :x->DATUMKOMMI,\
        :x->TOURID,\
        :x->ZEITKOENDE,\
        :x->DATUMVERSAND,\
        :x->ZEITVERSAND,\
        :x->BAHNHOFVERSAND,\
        :x->TOURSTAT,\
        :x->LAGRECHTOUR,\
        :x->FILIALNR,\
        :x->KDAUFTRAGART,\
        :x->TOURINAKTIV,\
        :x->ERSATZFILIALNR,\
        :x->KIPPZEIT,\
        :x->CHECKTIMETOTOUR,\
        :x->SCHECKORDER,\
        :x->KARENZZEIT
#define TOUR_UPDATE(x) \
        TOUR.DATUMKOMMI=:x->DATUMKOMMI,\
        TOUR.TOURID=:x->TOURID,\
        TOUR.ZEITKOENDE=:x->ZEITKOENDE,\
        TOUR.DATUMVERSAND=:x->DATUMVERSAND,\
        TOUR.ZEITVERSAND=:x->ZEITVERSAND,\
        TOUR.BAHNHOFVERSAND=:x->BAHNHOFVERSAND,\
        TOUR.TOURSTAT=:x->TOURSTAT,\
        TOUR.LAGRECHTOUR=:x->LAGRECHTOUR,\
        TOUR.FILIALNR=:x->FILIALNR,\
        TOUR.KDAUFTRAGART=:x->KDAUFTRAGART,\
        TOUR.TOURINAKTIV=:x->TOURINAKTIV,\
        TOUR.ERSATZFILIALNR=:x->ERSATZFILIALNR,\
        TOUR.KIPPZEIT=:x->KIPPZEIT,\
        TOUR.CHECKTIMETOTOUR=:x->CHECKTIMETOTOUR,\
        TOUR.SCHECKORDER=:x->SCHECKORDER,\
        TOUR.KARENZZEIT=:x->KARENZZEIT
/* SqlMacros390-Define of TOUR ************************************************/

#define TOUR_ZEIGER_390 \
        :DATUMKOMMI,\
        :TOURID,\
        :ZEITKOENDE,\
        :DATUMVERSAND,\
        :ZEITVERSAND,\
        :BAHNHOFVERSAND,\
        :TOURSTAT,\
        :LAGRECHTOUR,\
        :FILIALNR,\
        :KDAUFTRAGART,\
        :TOURINAKTIV,\
        :ERSATZFILIALNR,\
        :KIPPZEIT,\
        :CHECKTIMETOTOUR,\
        :SCHECKORDER,\
        :KARENZZEIT
#define TOUR_UPDATE_390 \
        DATUMKOMMI=:DATUMKOMMI,\
        TOURID=:TOURID,\
        ZEITKOENDE=:ZEITKOENDE,\
        DATUMVERSAND=:DATUMVERSAND,\
        ZEITVERSAND=:ZEITVERSAND,\
        BAHNHOFVERSAND=:BAHNHOFVERSAND,\
        TOURSTAT=:TOURSTAT,\
        LAGRECHTOUR=:LAGRECHTOUR,\
        FILIALNR=:FILIALNR,\
        KDAUFTRAGART=:KDAUFTRAGART,\
        TOURINAKTIV=:TOURINAKTIV,\
        ERSATZFILIALNR=:ERSATZFILIALNR,\
        KIPPZEIT=:KIPPZEIT,\
        CHECKTIMETOTOUR=:CHECKTIMETOTOUR,\
        SCHECKORDER=:SCHECKORDER,\
        KARENZZEIT=:KARENZZEIT
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of TOUR ****************************************************/

#ifndef TRANSCLASS
typedef struct N_TOUR {
    long DATUMKOMMI;
    char TOURID[7];
    long ZEITKOENDE;
    long DATUMVERSAND;
    long ZEITVERSAND;
    short BAHNHOFVERSAND;
    char TOURSTAT[2];
    long LAGRECHTOUR;
    short FILIALNR;
    char KDAUFTRAGART[3];
    char TOURINAKTIV[2];
    short ERSATZFILIALNR;
    short KIPPZEIT;
    short CHECKTIMETOTOUR;
    short SCHECKORDER;
    short KARENZZEIT;
} tourS;
#else /* TRANSCLASS */
typedef struct N_TOUR {
    long DATUMKOMMI;
    char TOURID[7];
    long ZEITKOENDE;
    long DATUMVERSAND;
    long ZEITVERSAND;
    short BAHNHOFVERSAND;
    char TOURSTAT[2];
    long LAGRECHTOUR;
    short FILIALNR;
    char KDAUFTRAGART[3];
    char TOURINAKTIV[2];
    short ERSATZFILIALNR;
    short KIPPZEIT;
    short CHECKTIMETOTOUR;
    short SCHECKORDER;
    short KARENZZEIT;

    bool operator == (const N_TOUR& right) const {
        return (
            DATUMKOMMI == right.DATUMKOMMI &&
            !strcmp(TOURID, right.TOURID) &&
            ZEITKOENDE == right.ZEITKOENDE &&
            DATUMVERSAND == right.DATUMVERSAND &&
            ZEITVERSAND == right.ZEITVERSAND &&
            BAHNHOFVERSAND == right.BAHNHOFVERSAND &&
            !strcmp(TOURSTAT, right.TOURSTAT) &&
            LAGRECHTOUR == right.LAGRECHTOUR &&
            FILIALNR == right.FILIALNR &&
            !strcmp(KDAUFTRAGART, right.KDAUFTRAGART) &&
            !strcmp(TOURINAKTIV, right.TOURINAKTIV) &&
            ERSATZFILIALNR == right.ERSATZFILIALNR &&
            KIPPZEIT == right.KIPPZEIT &&
            CHECKTIMETOTOUR == right.CHECKTIMETOTOUR &&
            SCHECKORDER == right.SCHECKORDER &&
            KARENZZEIT == right.KARENZZEIT
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        DATUMKOMMI = 0;
        strcpy(TOURID, " " );
        ZEITKOENDE = 0;
        DATUMVERSAND = 0;
        ZEITVERSAND = 0;
        BAHNHOFVERSAND = 0;
        strcpy(TOURSTAT, " " );
        LAGRECHTOUR = 0;
        FILIALNR = 0;
        strcpy(KDAUFTRAGART, " " );
        strcpy(TOURINAKTIV, " " );
        ERSATZFILIALNR = 0;
        KIPPZEIT = 0;
        CHECKTIMETOTOUR = 0;
        SCHECKORDER = 0;
        KARENZZEIT = 0;
#endif
    }
} tourS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of TOUR **********************************************/

struct S_TOUR {
    char DATUMKOMMI[11];
    char TOURID[6 + 1];
    char ZEITKOENDE[11];
    char DATUMVERSAND[11];
    char ZEITVERSAND[11];
    char BAHNHOFVERSAND[7];
    char TOURSTAT[1 + 1];
    char LAGRECHTOUR[11];
    char FILIALNR[7];
    char KDAUFTRAGART[2 + 1];
    char TOURINAKTIV[1 + 1];
    char ERSATZFILIALNR[7];
    char KIPPZEIT[7];
    char CHECKTIMETOTOUR[7];
    char SCHECKORDER[7];
    char KARENZZEIT[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of TOUR *****************************/

struct O_TOUR {
    char DATUMKOMMI[11];
    char TOURID[6];
    char ZEITKOENDE[11];
    char DATUMVERSAND[11];
    char ZEITVERSAND[11];
    char BAHNHOFVERSAND[7];
    char TOURSTAT[1];
    char LAGRECHTOUR[11];
    char FILIALNR[7];
    char KDAUFTRAGART[2];
    char TOURINAKTIV[1];
    char ERSATZFILIALNR[7];
    char KIPPZEIT[7];
    char CHECKTIMETOTOUR[7];
    char SCHECKORDER[7];
    char KARENZZEIT[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of TOUR ****************************************/

struct C_TOUR {
    long DATUMKOMMI;
    char TOURID[7];
    long ZEITKOENDE;
    long DATUMVERSAND;
    long ZEITVERSAND;
    short BAHNHOFVERSAND;
    char TOURSTAT;
    long LAGRECHTOUR;
    short FILIALNR;
    char KDAUFTRAGART[3];
    char TOURINAKTIV;
    short ERSATZFILIALNR;
    short KIPPZEIT;
    short CHECKTIMETOTOUR;
    short SCHECKORDER;
    short KARENZZEIT;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of TOUR **************************************/

struct I_TOUR {
    short DATUMKOMMI;
    short TOURID;
    short ZEITKOENDE;
    short DATUMVERSAND;
    short ZEITVERSAND;
    short BAHNHOFVERSAND;
    short TOURSTAT;
    short LAGRECHTOUR;
    short FILIALNR;
    short KDAUFTRAGART;
    short TOURINAKTIV;
    short ERSATZFILIALNR;
    short KIPPZEIT;
    short CHECKTIMETOTOUR;
    short SCHECKORDER;
    short KARENZZEIT;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of TOUR ************************************************/

#if defined (BUF_DESC)
static struct buf_desc TOUR_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc TOUR_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* description for datatypes of TOUR ******************************************/

 #define TOUR_S390 \
         long DATUMKOMMI; \
         char TOURID[7]; \
         long ZEITKOENDE; \
         long DATUMVERSAND; \
         long ZEITVERSAND; \
         short BAHNHOFVERSAND; \
         char TOURSTAT; \
         long LAGRECHTOUR; \
         short FILIALNR; \
         char KDAUFTRAGART[3]; \
         char TOURINAKTIV; \
         short ERSATZFILIALNR; \
         short KIPPZEIT; \
         short CHECKTIMETOTOUR; \
         short SCHECKORDER; \
         short KARENZZEIT; \



/* Copy-Function Struct to single Data TOUR ***********************************/

 #define TOUR_S390_COPY_TO_SINGLE(_x_) \
         DATUMKOMMI=_x_->DATUMKOMMI;\
          strcpy(TOURID,_x_->TOURID);\
         ZEITKOENDE=_x_->ZEITKOENDE;\
         DATUMVERSAND=_x_->DATUMVERSAND;\
         ZEITVERSAND=_x_->ZEITVERSAND;\
         BAHNHOFVERSAND=_x_->BAHNHOFVERSAND;\
         TOURSTAT=_x_->TOURSTAT;\
         LAGRECHTOUR=_x_->LAGRECHTOUR;\
         FILIALNR=_x_->FILIALNR;\
          strcpy(KDAUFTRAGART,_x_->KDAUFTRAGART);\
         TOURINAKTIV=_x_->TOURINAKTIV;\
         ERSATZFILIALNR=_x_->ERSATZFILIALNR;\
         KIPPZEIT=_x_->KIPPZEIT;\
         CHECKTIMETOTOUR=_x_->CHECKTIMETOTOUR;\
         SCHECKORDER=_x_->SCHECKORDER;\
         KARENZZEIT=_x_->KARENZZEIT;\

 #define TOUR_S390_COPY_TO_STRUCT(_x_) \
          _x_->DATUMKOMMI=DATUMKOMMI;\
          strcpy(_x_->TOURID,TOURID);\
          _x_->ZEITKOENDE=ZEITKOENDE;\
          _x_->DATUMVERSAND=DATUMVERSAND;\
          _x_->ZEITVERSAND=ZEITVERSAND;\
          _x_->BAHNHOFVERSAND=BAHNHOFVERSAND;\
          _x_->TOURSTAT=TOURSTAT;\
          _x_->LAGRECHTOUR=LAGRECHTOUR;\
          _x_->FILIALNR=FILIALNR;\
          strcpy(_x_->KDAUFTRAGART,KDAUFTRAGART);\
          _x_->TOURINAKTIV=TOURINAKTIV;\
          _x_->ERSATZFILIALNR=ERSATZFILIALNR;\
          _x_->KIPPZEIT=KIPPZEIT;\
          _x_->CHECKTIMETOTOUR=CHECKTIMETOTOUR;\
          _x_->SCHECKORDER=SCHECKORDER;\
          _x_->KARENZZEIT=KARENZZEIT;\



/* FunctionNumber-Define of tour **********************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of tour ******************************************/


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

class CTOUR : public ppDadeVirtual {
public:
    tourS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<tourS> lst; // class list

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
                     vector< tourS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     tourS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< tourS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<tourS>::iterator
                 beginList() { return lst.begin(); }
    vector<tourS>::iterator
                 endList  () { return lst.end  (); }

    long         GetDatumkommi() const { return s.DATUMKOMMI; }
    const char*  GetTourid(ppString & t) const { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
    long         GetZeitkoende() const { return s.ZEITKOENDE; }
    long         GetDatumversand() const { return s.DATUMVERSAND; }
    long         GetZeitversand() const { return s.ZEITVERSAND; }
    short        GetBahnhofversand() const { return s.BAHNHOFVERSAND; }
    char         GetTourstat() const { return s.TOURSTAT[0]; }
    long         GetLagrechtour() const { return s.LAGRECHTOUR; }
    short        GetFilialnr() const { return s.FILIALNR; }
    const char*  GetKdauftragart(ppString & t) const { t = s.KDAUFTRAGART; t.erasespace(ppString::END); return t.c_str(); }
    char         GetTourinaktiv() const { return s.TOURINAKTIV[0]; }
    short        GetErsatzfilialnr() const { return s.ERSATZFILIALNR; }
    short        GetKippzeit() const { return s.KIPPZEIT; }
    short        GetChecktimetotour() const { return s.CHECKTIMETOTOUR; }
    short        GetScheckorder() const { return s.SCHECKORDER; }
    short        GetKarenzzeit() const { return s.KARENZZEIT; }

    const tourS &
                 GetStruct() const { return s; }
    void         SetDatumkommi(long t) { s.DATUMKOMMI = t; }
    void         SetTourid(const ppString & t) { ppGStrCopy(s.TOURID, t.c_str(), L_TOUR_TOURID); }
    void         SetZeitkoende(long t) { s.ZEITKOENDE = t; }
    void         SetDatumversand(long t) { s.DATUMVERSAND = t; }
    void         SetZeitversand(long t) { s.ZEITVERSAND = t; }
    void         SetBahnhofversand(short t) { s.BAHNHOFVERSAND = t; }
    void         SetTourstat(char t) { s.TOURSTAT[0] = t; s.TOURSTAT[1] = '\0';}
    void         SetLagrechtour(long t) { s.LAGRECHTOUR = t; }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetKdauftragart(const ppString & t) { ppGStrCopy(s.KDAUFTRAGART, t.c_str(), L_TOUR_KDAUFTRAGART); }
    void         SetTourinaktiv(char t) { s.TOURINAKTIV[0] = t; s.TOURINAKTIV[1] = '\0';}
    void         SetErsatzfilialnr(short t) { s.ERSATZFILIALNR = t; }
    void         SetKippzeit(short t) { s.KIPPZEIT = t; }
    void         SetChecktimetotour(short t) { s.CHECKTIMETOTOUR = t; }
    void         SetScheckorder(short t) { s.SCHECKORDER = t; }
    void         SetKarenzzeit(short t) { s.KARENZZEIT = t; }

    void         SetStruct(const tourS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CTOUR() {
        ::buf_default((void *)&s, TOUR_BES, TOUR_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CTOUR() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, TOUR_BES, TOUR_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, TOUR_BES, (int)TOUR_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, TOUR_BES, (int)TOUR_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_TOUR & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.TOURID);
        ppGStripLast(d.KDAUFTRAGART);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, TOUR_BES, (int)TOUR_ANZ, error_msg);
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
/* CreateSqlStatement of TOUR *************************************************/

 #define TOUR_CREATE(x) EXEC SQL create table x (\
         DATUMKOMMI integer default 0 not null,\
         TOURID char(6) default " " not null,\
         ZEITKOENDE integer default 0 not null,\
         DATUMVERSAND integer default 0 not null,\
         ZEITVERSAND integer default 0 not null,\
         BAHNHOFVERSAND smallint default 0 not null,\
         TOURSTAT char(1) default " " not null,\
         LAGRECHTOUR integer default 0 not null,\
         FILIALNR smallint default 0 not null,\
         KDAUFTRAGART char(2) default " " not null,\
         TOURINAKTIV char(1) default " " not null,\
         ERSATZFILIALNR smallint default 0 not null,\
         KIPPZEIT smallint default 0 not null,\
         CHECKTIMETOTOUR smallint default 0 not null,\
         SCHECKORDER smallint default 0 not null,\
         KARENZZEIT smallint default 0 not null) in ksc extent size 56 next size 8 lock mode row;



/* CreateIndexStatement of TOUR ***********************************************/

 #define TOUR_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index tourx on _X_(\
              datumkommi,\
              filialnr,\
              tourid ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of TOUR ***********************************************/

 #define TOUR_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index tourx;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
