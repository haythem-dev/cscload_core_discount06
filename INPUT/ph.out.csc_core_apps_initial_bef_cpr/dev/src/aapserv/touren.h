#ifndef __PP_TOUREN_H_
#define __PP_TOUREN_H_

/******************************************************************************/
/* c:\git\pharmos.outbound.csc_core_applications\dev\src\aapserv\Touren *******/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of SONDERTOUREN **********************************************/

#define L_SONDERTOUREN_TOURID 6
#define L_SONDERTOUREN_KDAUFTRAGART 2
#define L_SONDERTOUREN_FILIALNR 6

/* Length-Define of TOURPLANPFLEGE ********************************************/

#define L_TOURPLANPFLEGE_DATUMKOMMI 11
#define L_TOURPLANPFLEGE_TERMID 4
#define L_TOURPLANPFLEGE_TOURID 6
#define L_TOURPLANPFLEGE_VERTRIEBSZENTRUMNR 6
#define L_TOURPLANPFLEGE_KUNDENNR 11
#define L_TOURPLANPFLEGE_KZAUTOZUORD 1
#define L_TOURPLANPFLEGE_ISBTM 6
#define L_TOURPLANPFLEGE_ISKK 6
#define L_TOURPLANPFLEGE_ISK08 6
#define L_TOURPLANPFLEGE_ISK20 6

/* Length-Define of TOURSPERRE ************************************************/

#define L_TOURSPERRE_DATUMKOMMI 11
#define L_TOURSPERRE_TOURID 6
#define L_TOURSPERRE_BEZEICHNUNG 30
#define L_TOURSPERRE_FILIALNR 6
#define L_TOURSPERRE_TOURINAKTIV 1
#define L_TOURSPERRE_ERSATZFILIALNR 6

/* SqlDefine of SONDERTOUREN **************************************************/


#define SONDERTOUREN_PLISTE \
        "SONDERTOUREN.TOURID,"\
        "SONDERTOUREN.KDAUFTRAGART,"\
        "SONDERTOUREN.FILIALNR"

/* SqlDefine of TOURPLANPFLEGE ************************************************/


#define TOURPLANPFLEGE_PLISTE \
        "TOURPLANTAG.DATUMKOMMI,"\
        "TOURPLANTAG.TOURID,"\
        "TOURPLANTAG.VERTRIEBSZENTRUMNR,"\
        "TOURPLANTAG.KUNDENNR,"\
        "TOURPLANTAG.KZAUTOZUORD,"\
        "TOURPLANTAG.ISBTM,"\
        "TOURPLANTAG.ISKK,"\
        "TOURPLANTAG.ISK08,"\
        "TOURPLANTAG.ISK20"

/* SqlDefine of TOURSPERRE ****************************************************/


#define TOURSPERRE_PLISTE \
        "TOUR.DATUMKOMMI,"\
        "TOUR.TOURID,"\
        "TOUR.BEZEICHNUNG,"\
        "TOUR.FILIALNR,"\
        "TOUR.TOURINAKTIV,"\
        "TOUR.ERSATZFILIALNR"

/* SqlDefine of SONDERTOUREN **************************************************/


#define SONDERTOUREN_UPDLISTE \
        "TOURID=?,"\
        "KDAUFTRAGART=?,"\
        "FILIALNR=?"
/* SqlDefine of TOURPLANPFLEGE ************************************************/


#define TOURPLANPFLEGE_UPDLISTE \
        "KZAUTOZUORD=?,"\
        "ISBTM=?,"\
        "ISKK=?,"\
        "ISK08=?,"\
        "ISK20=?"
/* SqlDefine of TOURSPERRE ****************************************************/


#define TOURSPERRE_UPDLISTE \
        "DATUMKOMMI=?,"\
        "TOURID=?,"\
        "BEZEICHNUNG=?,"\
        "FILIALNR=?,"\
        "TOURINAKTIV=?,"\
        "ERSATZFILIALNR=?"
/* SqlMacros-Define of SONDERTOUREN *******************************************/

#define SONDERTOUREN_ZEIGER(x) \
        :x->TOURID,\
        :x->KDAUFTRAGART,\
        :x->FILIALNR
#define SONDERTOUREN_ZEIGERSEL(x) \
        :x->TOURID,\
        :x->KDAUFTRAGART,\
        :x->FILIALNR

/* SqlMacros-Define of TOURPLANPFLEGE *****************************************/

#define TOURPLANPFLEGE_ZEIGER(x) \
        :x->KZAUTOZUORD,\
        :x->ISBTM,\
        :x->ISKK,\
        :x->ISK08,\
        :x->ISK20
#define TOURPLANPFLEGE_ZEIGERSEL(x) \
        :x->DATUMKOMMI,\
        :x->TOURID,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->KZAUTOZUORD,\
        :x->ISBTM,\
        :x->ISKK,\
        :x->ISK08,\
        :x->ISK20

/* SqlMacros-Define of TOURSPERRE *********************************************/

#define TOURSPERRE_ZEIGER(x) \
        :x->DATUMKOMMI,\
        :x->TOURID,\
        :x->BEZEICHNUNG,\
        :x->FILIALNR,\
        :x->TOURINAKTIV,\
        :x->ERSATZFILIALNR
#define TOURSPERRE_ZEIGERSEL(x) \
        :x->DATUMKOMMI,\
        :x->TOURID,\
        :x->BEZEICHNUNG,\
        :x->FILIALNR,\
        :x->TOURINAKTIV,\
        :x->ERSATZFILIALNR

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define SONDERTOUREN_H
#define SONDERTOUREN_ANZ ( sizeof(SONDERTOUREN_BES) / sizeof(struct buf_desc) )
#define TOURPLANPFLEGE_H
#define TOURPLANPFLEGE_ANZ ( sizeof(TOURPLANPFLEGE_BES) / sizeof(struct buf_desc) )
#define TOURSPERRE_H
#define TOURSPERRE_ANZ ( sizeof(TOURSPERRE_BES) / sizeof(struct buf_desc) )
#endif

#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of SONDERTOUREN ********************************************/

#ifndef TRANSCLASS
typedef struct N_SONDERTOUREN {
    char TOURID[7];
    char KDAUFTRAGART[3];
    short FILIALNR;
    long FETCH_REL;
} sondertourenS;
#else /* TRANSCLASS */
typedef struct N_SONDERTOUREN {
    char TOURID[7];
    char KDAUFTRAGART[3];
    short FILIALNR;
    long FETCH_REL;
    bool operator == (const N_SONDERTOUREN& right) const {
        return (
            !strcmp(TOURID, right.TOURID) &&
            !strcmp(KDAUFTRAGART, right.KDAUFTRAGART) &&
            FILIALNR == right.FILIALNR
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        strcpy(TOURID, " " );
        strcpy(KDAUFTRAGART, " " );
        FILIALNR = 0;
#endif
    }
} sondertourenS;
#endif /* TRANSCLASS */

/* original struct of TOURPLANPFLEGE ******************************************/

#ifndef TRANSCLASS
typedef struct N_TOURPLANPFLEGE {
    long DATUMKOMMI;
    char TERMID[5];
    char TOURID[7];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char KZAUTOZUORD[2];
    short ISBTM;
    short ISKK;
    short ISK08;
    short ISK20;
    long FETCH_REL;
} tourplanpflegeS;
#else /* TRANSCLASS */
typedef struct N_TOURPLANPFLEGE {
    long DATUMKOMMI;
    char TERMID[5];
    char TOURID[7];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char KZAUTOZUORD[2];
    short ISBTM;
    short ISKK;
    short ISK08;
    short ISK20;
    long FETCH_REL;
    bool operator == (const N_TOURPLANPFLEGE& right) const {
        return (
            DATUMKOMMI == right.DATUMKOMMI &&
            !strcmp(TERMID, right.TERMID) &&
            !strcmp(TOURID, right.TOURID) &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            !strcmp(KZAUTOZUORD, right.KZAUTOZUORD) &&
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
        DATUMKOMMI = 0;
        strcpy(TERMID, " " );
        strcpy(TOURID, " " );
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        strcpy(KZAUTOZUORD, " " );
        ISBTM = 0;
        ISKK = 0;
        ISK08 = 0;
        ISK20 = 0;
#endif
    }
} tourplanpflegeS;
#endif /* TRANSCLASS */

/* original struct of TOURSPERRE **********************************************/

#ifndef TRANSCLASS
typedef struct N_TOURSPERRE {
    long DATUMKOMMI;
    char TOURID[7];
    char BEZEICHNUNG[31];
    short FILIALNR;
    char TOURINAKTIV[2];
    short ERSATZFILIALNR;
    long FETCH_REL;
} toursperreS;
#else /* TRANSCLASS */
typedef struct N_TOURSPERRE {
    long DATUMKOMMI;
    char TOURID[7];
    char BEZEICHNUNG[31];
    short FILIALNR;
    char TOURINAKTIV[2];
    short ERSATZFILIALNR;
    long FETCH_REL;
    bool operator == (const N_TOURSPERRE& right) const {
        return (
            DATUMKOMMI == right.DATUMKOMMI &&
            !strcmp(TOURID, right.TOURID) &&
            !strcmp(BEZEICHNUNG, right.BEZEICHNUNG) &&
            FILIALNR == right.FILIALNR &&
            !strcmp(TOURINAKTIV, right.TOURINAKTIV) &&
            ERSATZFILIALNR == right.ERSATZFILIALNR
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        DATUMKOMMI = 0;
        strcpy(TOURID, " " );
        strcpy(BEZEICHNUNG, " " );
        FILIALNR = 0;
        strcpy(TOURINAKTIV, " " );
        ERSATZFILIALNR = 0;
#endif
    }
} toursperreS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of SONDERTOUREN ********************************/

struct C_SONDERTOUREN {
    char TOURID[7];
    char KDAUFTRAGART[3];
    short FILIALNR;
    long FETCH_REL;
};
/* Structur with real chartype of TOURPLANPFLEGE ******************************/

struct C_TOURPLANPFLEGE {
    long DATUMKOMMI;
    char TERMID[5];
    char TOURID[7];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char KZAUTOZUORD;
    short ISBTM;
    short ISKK;
    short ISK08;
    short ISK20;
    long FETCH_REL;
};
/* Structur with real chartype of TOURSPERRE **********************************/

struct C_TOURSPERRE {
    long DATUMKOMMI;
    char TOURID[7];
    char BEZEICHNUNG[31];
    short FILIALNR;
    char TOURINAKTIV;
    short ERSATZFILIALNR;
    long FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of SONDERTOUREN ******************************/

struct I_SONDERTOUREN {
    short TOURID;
    short KDAUFTRAGART;
    short FILIALNR;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of TOURPLANPFLEGE ****************************/

struct I_TOURPLANPFLEGE {
    short DATUMKOMMI;
    short TERMID;
    short TOURID;
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short KZAUTOZUORD;
    short ISBTM;
    short ISKK;
    short ISK08;
    short ISK20;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of TOURSPERRE ********************************/

struct I_TOURSPERRE {
    short DATUMKOMMI;
    short TOURID;
    short BEZEICHNUNG;
    short FILIALNR;
    short TOURINAKTIV;
    short ERSATZFILIALNR;
    short FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of SONDERTOUREN ****************************************/

#if defined (BUF_DESC)
static struct buf_desc SONDERTOUREN_BES [] = {
   { TYP_C, 6, 0 },
   { TYP_C, 2, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc SONDERTOUREN_BES [] = {
   { TYP_C, 6, 0 },
   { TYP_C, 2, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of TOURPLANPFLEGE **************************************/

#if defined (BUF_DESC)
static struct buf_desc TOURPLANPFLEGE_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 4, 0 },
   { TYP_C, 6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc TOURPLANPFLEGE_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 4, 0 },
   { TYP_C, 6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of TOURSPERRE ******************************************/

#if defined (BUF_DESC)
static struct buf_desc TOURSPERRE_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 30, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc TOURSPERRE_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 30, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* FunctionNumber-Define of SonderTouren **************************************/

#define SONDERTOUREN_DELETE 1311
#define SONDERTOUREN_INSERT 1310
#define SONDERTOUREN_SELLIST 1308
#define SONDERTOUREN_UPDATE 1309

/* FunctionNumber-Define of TourPlanPflege ************************************/

#define TOURPLANPFLEGE_SELLIST 1728
#define TOURPLANPFLEGE_SELTOUR 1752
#define TOURPLANPFLEGE_UPDATE 1729

/* FunctionNumber-Define of TourSperre ****************************************/

#define TOURSPERRE_SELLIST 1362
#define TOURSPERRE_UPDATE 1363

#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of SonderTouren **********************************/

#define Delete 1311
#define Insert 1310
#define SelList 1308
#define Update 1309

/* Old-FunctionNumber-Define of TourPlanPflege ********************************/

#define SelList 1728
#define SelTour 1752
#define Update 1729

/* Old-FunctionNumber-Define of TourSperre ************************************/

#define SelList 1362
#define Update 1363

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

class CSONDERTOUREN : public ppDadeVirtual {
public:
    sondertourenS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<sondertourenS> lst; // class list

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
                     vector< sondertourenS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     sondertourenS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< sondertourenS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<sondertourenS>::iterator
                 beginList() { return lst.begin(); }
    vector<sondertourenS>::iterator
                 endList  () { return lst.end  (); }

    const char*  GetTourid(ppString & t) const { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetKdauftragart(ppString & t) const { t = s.KDAUFTRAGART; t.erasespace(ppString::END); return t.c_str(); }
    short        GetFilialnr() const { return s.FILIALNR; }

    const sondertourenS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetTourid(const ppString & t) { ppGStrCopy(s.TOURID, t.c_str(), L_SONDERTOUREN_TOURID); }
    void         SetKdauftragart(const ppString & t) { ppGStrCopy(s.KDAUFTRAGART, t.c_str(), L_SONDERTOUREN_KDAUFTRAGART); }
    void         SetFilialnr(short t) { s.FILIALNR = t; }

    void         SetStruct(const sondertourenS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          Delete(int pos = 0) { return UniqueServerCall(1311, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1310, pos); Strip(s); return ret; }
    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1308, FetchRel, pos); return ret; }
    int          Update(int pos = 0) { int ret = UniqueServerCall(1309, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CSONDERTOUREN() {
        ::buf_default((void *)&s, SONDERTOUREN_BES, SONDERTOUREN_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CSONDERTOUREN() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, SONDERTOUREN_BES, SONDERTOUREN_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, SONDERTOUREN_BES, (int)SONDERTOUREN_ANZ, error_msg);
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
        if ( fkt_nr == 1311 ) return UniqueServerCall(1311, pos);
        if ( fkt_nr == 1310 ) return UniqueServerCall(1310, pos);
        if ( fkt_nr == 1308 ) return CursorServerCall(1308, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1309 ) return UniqueServerCall(1309, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_SONDERTOUREN & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.TOURID);
        ppGStripLast(d.KDAUFTRAGART);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, SONDERTOUREN_BES, (int)SONDERTOUREN_ANZ, error_msg);
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
        CSONDERTOUREN c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, SONDERTOUREN_BES, (int)SONDERTOUREN_ANZ, error_msg);
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

class CTOURPLANPFLEGE : public ppDadeVirtual {
public:
    tourplanpflegeS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<tourplanpflegeS> lst; // class list

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
                     vector< tourplanpflegeS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     tourplanpflegeS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< tourplanpflegeS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<tourplanpflegeS>::iterator
                 beginList() { return lst.begin(); }
    vector<tourplanpflegeS>::iterator
                 endList  () { return lst.end  (); }

    long         GetDatumkommi() const { return s.DATUMKOMMI; }
    const char*  GetTermid(ppString & t) const { t = s.TERMID; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetTourid(ppString & t) const { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    char         GetKzautozuord() const { return s.KZAUTOZUORD[0]; }
    short        GetIsbtm() const { return s.ISBTM; }
    short        GetIskk() const { return s.ISKK; }
    short        GetIsk08() const { return s.ISK08; }
    short        GetIsk20() const { return s.ISK20; }

    const tourplanpflegeS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetDatumkommi(long t) { s.DATUMKOMMI = t; }
    void         SetTermid(const ppString & t) { ppGStrCopy(s.TERMID, t.c_str(), L_TOURPLANPFLEGE_TERMID); }
    void         SetTourid(const ppString & t) { ppGStrCopy(s.TOURID, t.c_str(), L_TOURPLANPFLEGE_TOURID); }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetKzautozuord(char t) { s.KZAUTOZUORD[0] = t; s.KZAUTOZUORD[1] = '\0';}
    void         SetIsbtm(short t) { s.ISBTM = t; }
    void         SetIskk(short t) { s.ISKK = t; }
    void         SetIsk08(short t) { s.ISK08 = t; }
    void         SetIsk20(short t) { s.ISK20 = t; }

    void         SetStruct(const tourplanpflegeS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1728, FetchRel, pos); return ret; }
    int          SelTour(int pos = 0) { int ret = UniqueServerCall(1752, pos); Strip(s); return ret; }
    int          Update(int pos = 0) { int ret = UniqueServerCall(1729, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CTOURPLANPFLEGE() {
        ::buf_default((void *)&s, TOURPLANPFLEGE_BES, TOURPLANPFLEGE_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CTOURPLANPFLEGE() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, TOURPLANPFLEGE_BES, TOURPLANPFLEGE_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, TOURPLANPFLEGE_BES, (int)TOURPLANPFLEGE_ANZ, error_msg);
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
        if ( fkt_nr == 1728 ) return CursorServerCall(1728, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1752 ) return UniqueServerCall(1752, pos);
        if ( fkt_nr == 1729 ) return UniqueServerCall(1729, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_TOURPLANPFLEGE & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.TERMID);
        ppGStripLast(d.TOURID);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, TOURPLANPFLEGE_BES, (int)TOURPLANPFLEGE_ANZ, error_msg);
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
        CTOURPLANPFLEGE c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, TOURPLANPFLEGE_BES, (int)TOURPLANPFLEGE_ANZ, error_msg);
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

class CTOURSPERRE : public ppDadeVirtual {
public:
    toursperreS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<toursperreS> lst; // class list

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
                     vector< toursperreS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     toursperreS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< toursperreS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<toursperreS>::iterator
                 beginList() { return lst.begin(); }
    vector<toursperreS>::iterator
                 endList  () { return lst.end  (); }

    long         GetDatumkommi() const { return s.DATUMKOMMI; }
    const char*  GetTourid(ppString & t) const { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetBezeichnung(ppString & t) const { t = s.BEZEICHNUNG; t.erasespace(ppString::END); return t.c_str(); }
    short        GetFilialnr() const { return s.FILIALNR; }
    char         GetTourinaktiv() const { return s.TOURINAKTIV[0]; }
    short        GetErsatzfilialnr() const { return s.ERSATZFILIALNR; }

    const toursperreS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetDatumkommi(long t) { s.DATUMKOMMI = t; }
    void         SetTourid(const ppString & t) { ppGStrCopy(s.TOURID, t.c_str(), L_TOURSPERRE_TOURID); }
    void         SetBezeichnung(const ppString & t) { ppGStrCopy(s.BEZEICHNUNG, t.c_str(), L_TOURSPERRE_BEZEICHNUNG); }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetTourinaktiv(char t) { s.TOURINAKTIV[0] = t; s.TOURINAKTIV[1] = '\0';}
    void         SetErsatzfilialnr(short t) { s.ERSATZFILIALNR = t; }

    void         SetStruct(const toursperreS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1362, FetchRel, pos); return ret; }
    int          Update(int pos = 0) { int ret = UniqueServerCall(1363, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CTOURSPERRE() {
        ::buf_default((void *)&s, TOURSPERRE_BES, TOURSPERRE_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CTOURSPERRE() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, TOURSPERRE_BES, TOURSPERRE_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, TOURSPERRE_BES, (int)TOURSPERRE_ANZ, error_msg);
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
        if ( fkt_nr == 1362 ) return CursorServerCall(1362, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1363 ) return UniqueServerCall(1363, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_TOURSPERRE & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.TOURID);
        ppGStripLast(d.BEZEICHNUNG);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, TOURSPERRE_BES, (int)TOURSPERRE_ANZ, error_msg);
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
        CTOURSPERRE c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, TOURSPERRE_BES, (int)TOURSPERRE_ANZ, error_msg);
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

#endif   // GUARD
