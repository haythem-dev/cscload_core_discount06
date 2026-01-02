#ifndef __PP_KUNDENOTDIENSTPLAN_H_
#define __PP_KUNDENOTDIENSTPLAN_H_

/******************************************************************************/
/* c:\temp\kundenotdienstplan *************************************************/
/* produced by DADE 6.22.0 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of KUNDENOTDIENSTPLAN ****************************************/

#define L_KUNDENOTDIENSTPLAN_VERTRIEBSZENTRUMNR 6
#define L_KUNDENOTDIENSTPLAN_KUNDENNR 11
#define L_KUNDENOTDIENSTPLAN_DATUM 11
#define L_KUNDENOTDIENSTPLAN_UHRZEITVON 11
#define L_KUNDENOTDIENSTPLAN_UHRZEITBIS 11
#define L_KUNDENOTDIENSTPLAN_BEMERKUNGEN 240
#define L_KUNDENOTDIENSTPLAN_ISBTM 6
#define L_KUNDENOTDIENSTPLAN_ISKK 6
#define L_KUNDENOTDIENSTPLAN_ISK08 6
#define L_KUNDENOTDIENSTPLAN_ISK20 6

/* Length/Count-Define of KUNDENOTDIENSTPLAN **********************************/

#define LS_KUNDENOTDIENSTPLAN_VERTRIEBSZENTRUMNR 5 + 1
#define LS_KUNDENOTDIENSTPLAN_KUNDENNR 10 + 1
#define LS_KUNDENOTDIENSTPLAN_DATUM 10 + 1
#define LS_KUNDENOTDIENSTPLAN_UHRZEITVON 10 + 1
#define LS_KUNDENOTDIENSTPLAN_UHRZEITBIS 10 + 1
#define LS_KUNDENOTDIENSTPLAN_BEMERKUNGEN 240 + 1
#define LS_KUNDENOTDIENSTPLAN_ISBTM 5 + 1
#define LS_KUNDENOTDIENSTPLAN_ISKK 5 + 1
#define LS_KUNDENOTDIENSTPLAN_ISK08 5 + 1
#define LS_KUNDENOTDIENSTPLAN_ISK20 5 + 1

#define KUNDENOTDIENSTPLANVERTRIEBSZENTRUMNR 0
#define KUNDENOTDIENSTPLANKUNDENNR 1
#define KUNDENOTDIENSTPLANDATUM 2
#define KUNDENOTDIENSTPLANUHRZEITVON 3
#define KUNDENOTDIENSTPLANUHRZEITBIS 4
#define KUNDENOTDIENSTPLANBEMERKUNGEN 5
#define KUNDENOTDIENSTPLANISBTM 6
#define KUNDENOTDIENSTPLANISKK 7
#define KUNDENOTDIENSTPLANISK08 8
#define KUNDENOTDIENSTPLANISK20 9

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define KUNDENOTDIENSTPLAN_H
#define KUNDENOTDIENSTPLAN_ANZ ( sizeof(KUNDENOTDIENSTPLAN_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of KUNDENOTDIENSTPLAN ********************************************/

#define KUNDENOTDIENSTPLAN_LISTE \
        KUNDENOTDIENSTPLAN.VERTRIEBSZENTRUMNR,\
        KUNDENOTDIENSTPLAN.KUNDENNR,\
        KUNDENOTDIENSTPLAN.DATUM,\
        KUNDENOTDIENSTPLAN.UHRZEITVON,\
        KUNDENOTDIENSTPLAN.UHRZEITBIS,\
        KUNDENOTDIENSTPLAN.BEMERKUNGEN,\
        KUNDENOTDIENSTPLAN.ISBTM,\
        KUNDENOTDIENSTPLAN.ISKK,\
        KUNDENOTDIENSTPLAN.ISK08,\
        KUNDENOTDIENSTPLAN.ISK20
#define KUNDENOTDIENSTPLAN_LISTE_390 \
        VERTRIEBSZENTRUMNR,\
        KUNDENNR,\
        DATUM,\
        UHRZEITVON,\
        UHRZEITBIS,\
        BEMERKUNGEN,\
        ISBTM,\
        ISKK,\
        ISK08,\
        ISK20
#define KUNDENOTDIENSTPLAN_PLISTE \
        "KUNDENOTDIENSTPLAN.VERTRIEBSZENTRUMNR,"\
        "KUNDENOTDIENSTPLAN.KUNDENNR,"\
        "KUNDENOTDIENSTPLAN.DATUM,"\
        "KUNDENOTDIENSTPLAN.UHRZEITVON,"\
        "KUNDENOTDIENSTPLAN.UHRZEITBIS,"\
        "KUNDENOTDIENSTPLAN.BEMERKUNGEN,"\
        "KUNDENOTDIENSTPLAN.ISBTM,"\
        "KUNDENOTDIENSTPLAN.ISKK,"\
        "KUNDENOTDIENSTPLAN.ISK08,"\
        "KUNDENOTDIENSTPLAN.ISK20"
#define KUNDENOTDIENSTPLAN_PELISTE \
        "VERTRIEBSZENTRUMNR,"\
        "KUNDENNR,"\
        "DATUM,"\
        "UHRZEITVON,"\
        "UHRZEITBIS,"\
        "BEMERKUNGEN,"\
        "ISBTM,"\
        "ISKK,"\
        "ISK08,"\
        "ISK20"
#define KUNDENOTDIENSTPLAN_UPDLISTE \
        "VERTRIEBSZENTRUMNR=?,"\
        "KUNDENNR=?,"\
        "DATUM=?,"\
        "UHRZEITVON=?,"\
        "UHRZEITBIS=?,"\
        "BEMERKUNGEN=?,"\
        "ISBTM=?,"\
        "ISKK=?,"\
        "ISK08=?,"\
        "ISK20=?"
/* SqlMacros-Define of KUNDENOTDIENSTPLAN *************************************/

#define KUNDENOTDIENSTPLAN_ZEIGER(x) \
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->DATUM,\
        :x->UHRZEITVON,\
        :x->UHRZEITBIS,\
        :x->BEMERKUNGEN,\
        :x->ISBTM,\
        :x->ISKK,\
        :x->ISK08,\
        :x->ISK20
#define KUNDENOTDIENSTPLAN_ZEIGERSEL(x) \
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->DATUM,\
        :x->UHRZEITVON,\
        :x->UHRZEITBIS,\
        :x->BEMERKUNGEN,\
        :x->ISBTM,\
        :x->ISKK,\
        :x->ISK08,\
        :x->ISK20
#define KUNDENOTDIENSTPLAN_UPDATE(x) \
        KUNDENOTDIENSTPLAN.VERTRIEBSZENTRUMNR=:x->VERTRIEBSZENTRUMNR,\
        KUNDENOTDIENSTPLAN.KUNDENNR=:x->KUNDENNR,\
        KUNDENOTDIENSTPLAN.DATUM=:x->DATUM,\
        KUNDENOTDIENSTPLAN.UHRZEITVON=:x->UHRZEITVON,\
        KUNDENOTDIENSTPLAN.UHRZEITBIS=:x->UHRZEITBIS,\
        KUNDENOTDIENSTPLAN.BEMERKUNGEN=:x->BEMERKUNGEN,\
        KUNDENOTDIENSTPLAN.ISBTM=:x->ISBTM,\
        KUNDENOTDIENSTPLAN.ISKK=:x->ISKK,\
        KUNDENOTDIENSTPLAN.ISK08=:x->ISK08,\
        KUNDENOTDIENSTPLAN.ISK20=:x->ISK20
/* SqlMacros390-Define of KUNDENOTDIENSTPLAN **********************************/

#define KUNDENOTDIENSTPLAN_ZEIGER_390 \
        :VERTRIEBSZENTRUMNR,\
        :KUNDENNR,\
        :DATUM,\
        :UHRZEITVON,\
        :UHRZEITBIS,\
        :BEMERKUNGEN,\
        :ISBTM,\
        :ISKK,\
        :ISK08,\
        :ISK20
#define KUNDENOTDIENSTPLAN_UPDATE_390 \
        VERTRIEBSZENTRUMNR=:VERTRIEBSZENTRUMNR,\
        KUNDENNR=:KUNDENNR,\
        DATUM=:DATUM,\
        UHRZEITVON=:UHRZEITVON,\
        UHRZEITBIS=:UHRZEITBIS,\
        BEMERKUNGEN=:BEMERKUNGEN,\
        ISBTM=:ISBTM,\
        ISKK=:ISKK,\
        ISK08=:ISK08,\
        ISK20=:ISK20
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of KUNDENOTDIENSTPLAN **************************************/

#ifndef TRANSCLASS
typedef struct N_KUNDENOTDIENSTPLAN {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long DATUM;
    long UHRZEITVON;
    long UHRZEITBIS;
    char BEMERKUNGEN[241];
    short ISBTM;
    short ISKK;
    short ISK08;
    short ISK20;
} kundenotdienstplanS;
#else /* TRANSCLASS */
typedef struct N_KUNDENOTDIENSTPLAN {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long DATUM;
    long UHRZEITVON;
    long UHRZEITBIS;
    char BEMERKUNGEN[241];
    short ISBTM;
    short ISKK;
    short ISK08;
    short ISK20;

    bool operator == (const N_KUNDENOTDIENSTPLAN& right) const {
        return (
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            DATUM == right.DATUM &&
            UHRZEITVON == right.UHRZEITVON &&
            UHRZEITBIS == right.UHRZEITBIS &&
            !strcmp(BEMERKUNGEN, right.BEMERKUNGEN) &&
            ISBTM == right.ISBTM &&
            ISKK == right.ISKK &&
            ISK08 == right.ISK08 &&
            ISK20 == right.ISK20
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        DATUM = 0;
        UHRZEITVON = 0;
        UHRZEITBIS = 0;
        strcpy(BEMERKUNGEN, " " );
        ISBTM = 0;
        ISKK = 0;
        ISK08 = 0;
        ISK20 = 0;
#endif
    }
} kundenotdienstplanS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of KUNDENOTDIENSTPLAN ********************************/

struct S_KUNDENOTDIENSTPLAN {
    char VERTRIEBSZENTRUMNR[7];
    char KUNDENNR[11];
    char DATUM[11];
    char UHRZEITVON[11];
    char UHRZEITBIS[11];
    char BEMERKUNGEN[240 + 1];
    char ISBTM[7];
    char ISKK[7];
    char ISK08[7];
    char ISK20[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of KUNDENOTDIENSTPLAN ***************/

struct O_KUNDENOTDIENSTPLAN {
    char VERTRIEBSZENTRUMNR[7];
    char KUNDENNR[11];
    char DATUM[11];
    char UHRZEITVON[11];
    char UHRZEITBIS[11];
    char BEMERKUNGEN[240];
    char ISBTM[7];
    char ISKK[7];
    char ISK08[7];
    char ISK20[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of KUNDENOTDIENSTPLAN **************************/

struct C_KUNDENOTDIENSTPLAN {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long DATUM;
    long UHRZEITVON;
    long UHRZEITBIS;
    char BEMERKUNGEN[241];
    short ISBTM;
    short ISKK;
    short ISK08;
    short ISK20;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of KUNDENOTDIENSTPLAN ************************/

struct I_KUNDENOTDIENSTPLAN {
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short DATUM;
    short UHRZEITVON;
    short UHRZEITBIS;
    short BEMERKUNGEN;
    short ISBTM;
    short ISKK;
    short ISK08;
    short ISK20;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of KUNDENOTDIENSTPLAN **********************************/

#if defined (BUF_DESC)
static struct buf_desc KUNDENOTDIENSTPLAN_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 240, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc KUNDENOTDIENSTPLAN_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 240, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* description for datatypes of KUNDENOTDIENSTPLAN ****************************/

 #define KUNDENOTDIENSTPLAN_S390 \
         short VERTRIEBSZENTRUMNR; \
         long KUNDENNR; \
         long DATUM; \
         long UHRZEITVON; \
         long UHRZEITBIS; \
         char BEMERKUNGEN[241]; \
         short ISBTM; \
         short ISKK; \
         short ISK08; \
         short ISK20; \



/* Copy-Function Struct to single Data KUNDENOTDIENSTPLAN *********************/

 #define KUNDENOTDIENSTPLAN_S390_COPY_TO_SINGLE(_x_) \
         VERTRIEBSZENTRUMNR=_x_->VERTRIEBSZENTRUMNR;\
         KUNDENNR=_x_->KUNDENNR;\
         DATUM=_x_->DATUM;\
         UHRZEITVON=_x_->UHRZEITVON;\
         UHRZEITBIS=_x_->UHRZEITBIS;\
          strcpy(BEMERKUNGEN,_x_->BEMERKUNGEN);\
         ISBTM=_x_->ISBTM;\
         ISKK=_x_->ISKK;\
         ISK08=_x_->ISK08;\
         ISK20=_x_->ISK20;\

 #define KUNDENOTDIENSTPLAN_S390_COPY_TO_STRUCT(_x_) \
          _x_->VERTRIEBSZENTRUMNR=VERTRIEBSZENTRUMNR;\
          _x_->KUNDENNR=KUNDENNR;\
          _x_->DATUM=DATUM;\
          _x_->UHRZEITVON=UHRZEITVON;\
          _x_->UHRZEITBIS=UHRZEITBIS;\
          strcpy(_x_->BEMERKUNGEN,BEMERKUNGEN);\
          _x_->ISBTM=ISBTM;\
          _x_->ISKK=ISKK;\
          _x_->ISK08=ISK08;\
          _x_->ISK20=ISK20;\



/* FunctionNumber-Define of kundenotdienstplan ********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of kundenotdienstplan ****************************/


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

class CKUNDENOTDIENSTPLAN : public ppDadeVirtual {
public:
    kundenotdienstplanS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<kundenotdienstplanS> lst; // class list

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
                     vector< kundenotdienstplanS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     kundenotdienstplanS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< kundenotdienstplanS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<kundenotdienstplanS>::iterator
                 beginList() { return lst.begin(); }
    vector<kundenotdienstplanS>::iterator
                 endList  () { return lst.end  (); }

    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    long         GetDatum() const { return s.DATUM; }
    long         GetUhrzeitvon() const { return s.UHRZEITVON; }
    long         GetUhrzeitbis() const { return s.UHRZEITBIS; }
    const char*  GetBemerkungen(ppString & t) const { t = s.BEMERKUNGEN; t.erasespace(ppString::END); return t.c_str(); }
    short        GetIsbtm() const { return s.ISBTM; }
    short        GetIskk() const { return s.ISKK; }
    short        GetIsk08() const { return s.ISK08; }
    short        GetIsk20() const { return s.ISK20; }

    const kundenotdienstplanS &
                 GetStruct() const { return s; }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetDatum(long t) { s.DATUM = t; }
    void         SetUhrzeitvon(long t) { s.UHRZEITVON = t; }
    void         SetUhrzeitbis(long t) { s.UHRZEITBIS = t; }
    void         SetBemerkungen(const ppString & t) { ppGStrCopy(s.BEMERKUNGEN, t.c_str(), L_KUNDENOTDIENSTPLAN_BEMERKUNGEN); }
    void         SetIsbtm(short t) { s.ISBTM = t; }
    void         SetIskk(short t) { s.ISKK = t; }
    void         SetIsk08(short t) { s.ISK08 = t; }
    void         SetIsk20(short t) { s.ISK20 = t; }

    void         SetStruct(const kundenotdienstplanS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CKUNDENOTDIENSTPLAN() {
        ::buf_default((void *)&s, KUNDENOTDIENSTPLAN_BES, KUNDENOTDIENSTPLAN_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CKUNDENOTDIENSTPLAN() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, KUNDENOTDIENSTPLAN_BES, KUNDENOTDIENSTPLAN_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, KUNDENOTDIENSTPLAN_BES, (int)KUNDENOTDIENSTPLAN_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, KUNDENOTDIENSTPLAN_BES, (int)KUNDENOTDIENSTPLAN_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_KUNDENOTDIENSTPLAN & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.BEMERKUNGEN);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, KUNDENOTDIENSTPLAN_BES, (int)KUNDENOTDIENSTPLAN_ANZ, error_msg);
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
/* CreateSqlStatement of KUNDENOTDIENSTPLAN ***********************************/

 #define KUNDENOTDIENSTPLAN_CREATE(x) EXEC SQL create table x (\
         VERTRIEBSZENTRUMNR smallint default 0 not null,\
         KUNDENNR integer default 0 not null,\
         DATUM integer default 0 not null,\
         UHRZEITVON integer default 0 not null,\
         UHRZEITBIS integer default 0 not null,\
         BEMERKUNGEN varchar(240,0) default " " not null,\
         ISBTM smallint default 0 not null,\
         ISKK smallint default 0 not null,\
         ISK08 smallint default 0 not null,\
         ISK20 smallint default 0 not null) in KscCustomer extent size 3372 next size 340 lock mode row;



/* CreateIndexStatement of KUNDENOTDIENSTPLAN *********************************/

 #define KUNDENOTDIENSTPLAN_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_KundeNotdienstP1 on _X_(\
              VertriebszentrumNr,\
              KundenNr,\
              datum ) in KscCustomerIdx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of KUNDENOTDIENSTPLAN *********************************/

 #define KUNDENOTDIENSTPLAN_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_KundeNotdienstP1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
