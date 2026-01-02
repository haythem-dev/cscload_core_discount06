#ifndef __PP_VARTIKELLOKAL_H_
#define __PP_VARTIKELLOKAL_H_

/******************************************************************************/
/* c:\temp\vartikellokal ******************************************************/
/* produced by DADE 6.22.0 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of VARTIKELLOKAL *********************************************/

#define L_VARTIKELLOKAL_FILIALNR 6
#define L_VARTIKELLOKAL_ARTIKEL_NR 11
#define L_VARTIKELLOKAL_BESTAND 11
#define L_VARTIKELLOKAL_ARTIKELAKTIV 1
#define L_VARTIKELLOKAL_VERBUNDARTIKEL 1
#define L_VARTIKELLOKAL_NLEVELIBTTYPEID 6
#define L_VARTIKELLOKAL_IBTQTYAVAILABILITYPERCENTAGE 6

/* Length/Count-Define of VARTIKELLOKAL ***************************************/

#define LS_VARTIKELLOKAL_FILIALNR 5 + 1
#define LS_VARTIKELLOKAL_ARTIKEL_NR 10 + 1
#define LS_VARTIKELLOKAL_BESTAND 10 + 1
#define LS_VARTIKELLOKAL_ARTIKELAKTIV 1 + 1
#define LS_VARTIKELLOKAL_VERBUNDARTIKEL 1 + 1
#define LS_VARTIKELLOKAL_NLEVELIBTTYPEID 5 + 1
#define LS_VARTIKELLOKAL_IBTQTYAVAILABILITYPERCENTAGE 5 + 1

#define VARTIKELLOKALFILIALNR 0
#define VARTIKELLOKALARTIKEL_NR 1
#define VARTIKELLOKALBESTAND 2
#define VARTIKELLOKALARTIKELAKTIV 3
#define VARTIKELLOKALVERBUNDARTIKEL 4
#define VARTIKELLOKALNLEVELIBTTYPEID 5
#define VARTIKELLOKALIBTQTYAVAILABILITYPERCENTAGE 6

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define VARTIKELLOKAL_H
#define VARTIKELLOKAL_ANZ ( sizeof(VARTIKELLOKAL_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of VARTIKELLOKAL *************************************************/

#define VARTIKELLOKAL_LISTE \
        VARTIKELLOKAL.FILIALNR,\
        VARTIKELLOKAL.ARTIKEL_NR,\
        VARTIKELLOKAL.BESTAND,\
        VARTIKELLOKAL.ARTIKELAKTIV,\
        VARTIKELLOKAL.VERBUNDARTIKEL,\
        IBTBRANCHES.NLEVELIBTTYPEID,\
        PARAAUFTRAGBEARB.IBTQTYAVAILABILITYPERCENTAGE
#define VARTIKELLOKAL_LISTE_390 \
        FILIALNR,\
        ARTIKEL_NR,\
        BESTAND,\
        ARTIKELAKTIV,\
        VERBUNDARTIKEL,\
        NLEVELIBTTYPEID,\
        IBTQTYAVAILABILITYPERCENTAGE
#define VARTIKELLOKAL_PLISTE \
        "VARTIKELLOKAL.FILIALNR,"\
        "VARTIKELLOKAL.ARTIKEL_NR,"\
        "VARTIKELLOKAL.BESTAND,"\
        "VARTIKELLOKAL.ARTIKELAKTIV,"\
        "VARTIKELLOKAL.VERBUNDARTIKEL,"\
        "IBTBRANCHES.NLEVELIBTTYPEID,"\
        "PARAAUFTRAGBEARB.IBTQTYAVAILABILITYPERCENTAGE"
#define VARTIKELLOKAL_PELISTE \
        "FILIALNR,"\
        "ARTIKEL_NR,"\
        "BESTAND,"\
        "ARTIKELAKTIV,"\
        "VERBUNDARTIKEL,"\
        "NLEVELIBTTYPEID,"\
        "IBTQTYAVAILABILITYPERCENTAGE"
#define VARTIKELLOKAL_UPDLISTE \
        "FILIALNR=?,"\
        "ARTIKEL_NR=?,"\
        "BESTAND=?,"\
        "ARTIKELAKTIV=?,"\
        "VERBUNDARTIKEL=?,"\
        "NLEVELIBTTYPEID=?,"\
        "IBTQTYAVAILABILITYPERCENTAGE=?"
/* SqlMacros-Define of VARTIKELLOKAL ******************************************/

#define VARTIKELLOKAL_ZEIGER(x) \
        :x->FILIALNR,\
        :x->ARTIKEL_NR,\
        :x->BESTAND,\
        :x->ARTIKELAKTIV,\
        :x->VERBUNDARTIKEL,\
        :x->NLEVELIBTTYPEID,\
        :x->IBTQTYAVAILABILITYPERCENTAGE
#define VARTIKELLOKAL_ZEIGERSEL(x) \
        :x->FILIALNR,\
        :x->ARTIKEL_NR,\
        :x->BESTAND,\
        :x->ARTIKELAKTIV,\
        :x->VERBUNDARTIKEL,\
        :x->NLEVELIBTTYPEID,\
        :x->IBTQTYAVAILABILITYPERCENTAGE
#define VARTIKELLOKAL_UPDATE(x) \
        VARTIKELLOKAL.FILIALNR=:x->FILIALNR,\
        VARTIKELLOKAL.ARTIKEL_NR=:x->ARTIKEL_NR,\
        VARTIKELLOKAL.BESTAND=:x->BESTAND,\
        VARTIKELLOKAL.ARTIKELAKTIV=:x->ARTIKELAKTIV,\
        VARTIKELLOKAL.VERBUNDARTIKEL=:x->VERBUNDARTIKEL,\
        IBTBRANCHES.NLEVELIBTTYPEID=:x->NLEVELIBTTYPEID,\
        PARAAUFTRAGBEARB.IBTQTYAVAILABILITYPERCENTAGE=:x->IBTQTYAVAILABILITYPERCENTAGE
/* SqlMacros390-Define of VARTIKELLOKAL ***************************************/

#define VARTIKELLOKAL_ZEIGER_390 \
        :FILIALNR,\
        :ARTIKEL_NR,\
        :BESTAND,\
        :ARTIKELAKTIV,\
        :VERBUNDARTIKEL,\
        :NLEVELIBTTYPEID,\
        :IBTQTYAVAILABILITYPERCENTAGE
#define VARTIKELLOKAL_UPDATE_390 \
        FILIALNR=:FILIALNR,\
        ARTIKEL_NR=:ARTIKEL_NR,\
        BESTAND=:BESTAND,\
        ARTIKELAKTIV=:ARTIKELAKTIV,\
        VERBUNDARTIKEL=:VERBUNDARTIKEL,\
        NLEVELIBTTYPEID=:NLEVELIBTTYPEID,\
        IBTQTYAVAILABILITYPERCENTAGE=:IBTQTYAVAILABILITYPERCENTAGE
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of VARTIKELLOKAL *******************************************/

#ifndef TRANSCLASS
typedef struct N_VARTIKELLOKAL {
    short FILIALNR;
    long ARTIKEL_NR;
    long BESTAND;
    char ARTIKELAKTIV[2];
    char VERBUNDARTIKEL[2];
    short NLEVELIBTTYPEID;
    short IBTQTYAVAILABILITYPERCENTAGE;
} vartikellokalS;
#else /* TRANSCLASS */
typedef struct N_VARTIKELLOKAL {
    short FILIALNR;
    long ARTIKEL_NR;
    long BESTAND;
    char ARTIKELAKTIV[2];
    char VERBUNDARTIKEL[2];
    short NLEVELIBTTYPEID;
    short IBTQTYAVAILABILITYPERCENTAGE;

    bool operator == (const N_VARTIKELLOKAL& right) const {
        return (
            FILIALNR == right.FILIALNR &&
            ARTIKEL_NR == right.ARTIKEL_NR &&
            BESTAND == right.BESTAND &&
            !strcmp(ARTIKELAKTIV, right.ARTIKELAKTIV) &&
            !strcmp(VERBUNDARTIKEL, right.VERBUNDARTIKEL) &&
            NLEVELIBTTYPEID == right.NLEVELIBTTYPEID &&
            IBTQTYAVAILABILITYPERCENTAGE == right.IBTQTYAVAILABILITYPERCENTAGE
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        FILIALNR = 0;
        ARTIKEL_NR = 0;
        BESTAND = 0;
        strcpy(ARTIKELAKTIV, " " );
        strcpy(VERBUNDARTIKEL, " " );
        NLEVELIBTTYPEID = 0;
        IBTQTYAVAILABILITYPERCENTAGE = 0;
#endif
    }
} vartikellokalS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of VARTIKELLOKAL *************************************/

struct S_VARTIKELLOKAL {
    char FILIALNR[7];
    char ARTIKEL_NR[11];
    char BESTAND[11];
    char ARTIKELAKTIV[1 + 1];
    char VERBUNDARTIKEL[1 + 1];
    char NLEVELIBTTYPEID[7];
    char IBTQTYAVAILABILITYPERCENTAGE[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of VARTIKELLOKAL ********************/

struct O_VARTIKELLOKAL {
    char FILIALNR[7];
    char ARTIKEL_NR[11];
    char BESTAND[11];
    char ARTIKELAKTIV[1];
    char VERBUNDARTIKEL[1];
    char NLEVELIBTTYPEID[7];
    char IBTQTYAVAILABILITYPERCENTAGE[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of VARTIKELLOKAL *******************************/

struct C_VARTIKELLOKAL {
    short FILIALNR;
    long ARTIKEL_NR;
    long BESTAND;
    char ARTIKELAKTIV;
    char VERBUNDARTIKEL;
    short NLEVELIBTTYPEID;
    short IBTQTYAVAILABILITYPERCENTAGE;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of VARTIKELLOKAL *****************************/

struct I_VARTIKELLOKAL {
    short FILIALNR;
    short ARTIKEL_NR;
    short BESTAND;
    short ARTIKELAKTIV;
    short VERBUNDARTIKEL;
    short NLEVELIBTTYPEID;
    short IBTQTYAVAILABILITYPERCENTAGE;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of VARTIKELLOKAL ***************************************/

#if defined (BUF_DESC)
static struct buf_desc VARTIKELLOKAL_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc VARTIKELLOKAL_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* description for datatypes of VARTIKELLOKAL *********************************/

 #define VARTIKELLOKAL_S390 \
         short FILIALNR; \
         long ARTIKEL_NR; \
         long BESTAND; \
         char ARTIKELAKTIV; \
         char VERBUNDARTIKEL; \
         short NLEVELIBTTYPEID; \
         short IBTQTYAVAILABILITYPERCENTAGE; \



/* Copy-Function Struct to single Data VARTIKELLOKAL **************************/

 #define VARTIKELLOKAL_S390_COPY_TO_SINGLE(_x_) \
         FILIALNR=_x_->FILIALNR;\
         ARTIKEL_NR=_x_->ARTIKEL_NR;\
         BESTAND=_x_->BESTAND;\
         ARTIKELAKTIV=_x_->ARTIKELAKTIV;\
         VERBUNDARTIKEL=_x_->VERBUNDARTIKEL;\
         NLEVELIBTTYPEID=_x_->NLEVELIBTTYPEID;\
         IBTQTYAVAILABILITYPERCENTAGE=_x_->IBTQTYAVAILABILITYPERCENTAGE;\

 #define VARTIKELLOKAL_S390_COPY_TO_STRUCT(_x_) \
          _x_->FILIALNR=FILIALNR;\
          _x_->ARTIKEL_NR=ARTIKEL_NR;\
          _x_->BESTAND=BESTAND;\
          _x_->ARTIKELAKTIV=ARTIKELAKTIV;\
          _x_->VERBUNDARTIKEL=VERBUNDARTIKEL;\
          _x_->NLEVELIBTTYPEID=NLEVELIBTTYPEID;\
          _x_->IBTQTYAVAILABILITYPERCENTAGE=IBTQTYAVAILABILITYPERCENTAGE;\



/* FunctionNumber-Define of vartikellokal *************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of vartikellokal *********************************/


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

class CVARTIKELLOKAL : public ppDadeVirtual {
public:
    vartikellokalS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<vartikellokalS> lst; // class list

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
                     vector< vartikellokalS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     vartikellokalS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< vartikellokalS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<vartikellokalS>::iterator
                 beginList() { return lst.begin(); }
    vector<vartikellokalS>::iterator
                 endList  () { return lst.end  (); }

    short        GetFilialnr() const { return s.FILIALNR; }
    long         GetArtikel_nr() const { return s.ARTIKEL_NR; }
    long         GetBestand() const { return s.BESTAND; }
    char         GetArtikelaktiv() const { return s.ARTIKELAKTIV[0]; }
    char         GetVerbundartikel() const { return s.VERBUNDARTIKEL[0]; }
    short        GetNlevelibttypeid() const { return s.NLEVELIBTTYPEID; }
    short        GetIbtqtyavailabilitypercentage() const { return s.IBTQTYAVAILABILITYPERCENTAGE; }

    const vartikellokalS &
                 GetStruct() const { return s; }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetArtikel_nr(long t) { s.ARTIKEL_NR = t; }
    void         SetBestand(long t) { s.BESTAND = t; }
    void         SetArtikelaktiv(char t) { s.ARTIKELAKTIV[0] = t; s.ARTIKELAKTIV[1] = '\0';}
    void         SetVerbundartikel(char t) { s.VERBUNDARTIKEL[0] = t; s.VERBUNDARTIKEL[1] = '\0';}
    void         SetNlevelibttypeid(short t) { s.NLEVELIBTTYPEID = t; }
    void         SetIbtqtyavailabilitypercentage(short t) { s.IBTQTYAVAILABILITYPERCENTAGE = t; }

    void         SetStruct(const vartikellokalS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CVARTIKELLOKAL() {
        ::buf_default((void *)&s, VARTIKELLOKAL_BES, VARTIKELLOKAL_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CVARTIKELLOKAL() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, VARTIKELLOKAL_BES, VARTIKELLOKAL_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, VARTIKELLOKAL_BES, (int)VARTIKELLOKAL_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, VARTIKELLOKAL_BES, (int)VARTIKELLOKAL_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_VARTIKELLOKAL & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, VARTIKELLOKAL_BES, (int)VARTIKELLOKAL_ANZ, error_msg);
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
/* CreateSqlStatement of VARTIKELLOKAL ****************************************/

 #define VARTIKELLOKAL_CREATE(x) EXEC SQL create table x (\
         FILIALNR smallint default 0 not null,\
         ARTIKEL_NR integer default 0 not null,\
         BESTAND integer default 0 not null,\
         ARTIKELAKTIV char(1) default " " not null,\
         VERBUNDARTIKEL char(1) default " " not null,\
         NLEVELIBTTYPEID smallint default 0 not null,\
         IBTQTYAVAILABILITYPERCENTAGE smallint default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of VARTIKELLOKAL **************************************/

 #define VARTIKELLOKAL_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
/* DeleteIndexStatement of VARTIKELLOKAL **************************************/

 #define VARTIKELLOKAL_DELETE_INDEX(_X_)\
              _X_ = 0;\


#endif   // GUARD
