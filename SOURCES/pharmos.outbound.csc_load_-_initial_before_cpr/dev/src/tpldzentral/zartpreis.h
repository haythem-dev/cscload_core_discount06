#ifndef __PP_ZARTPREIS_H_
#define __PP_ZARTPREIS_H_

/******************************************************************************/
/* c:\prri\Headerfiles\zartpreis **********************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <pplib/bufkon.h>

/* Length-Define of ZARTPREIS *************************************************/

#define L_ZARTPREIS_ARTIKEL_NR 11
#define L_ZARTPREIS_DATUMGUELTIGAB 11
#define L_ZARTPREIS_GROSSO 9
#define N_ZARTPREIS_GROSSO 2
#define L_ZARTPREIS_AEP 9
#define N_ZARTPREIS_AEP 2
#define L_ZARTPREIS_AVP 9
#define N_ZARTPREIS_AVP 2
#define L_ZARTPREIS_KE_MWST 1
#define L_ZARTPREIS_HERST_PROZENT 5
#define N_ZARTPREIS_HERST_PROZENT 2
#define L_ZARTPREIS_EAVP 9
#define N_ZARTPREIS_EAVP 2
#define L_ZARTPREIS_MAXAVP 9
#define N_ZARTPREIS_MAXAVP 2
#define L_ZARTPREIS_PREIS_TYP 6
#define L_ZARTPREIS_AGP 9
#define N_ZARTPREIS_AGP 2

/* Length/Count-Define of ZARTPREIS *******************************************/

#define LS_ZARTPREIS_ARTIKEL_NR 10 + 1
#define LS_ZARTPREIS_DATUMGUELTIGAB 10 + 1
#define LS_ZARTPREIS_GROSSO 9 + 2
#define LS_ZARTPREIS_AEP 9 + 2
#define LS_ZARTPREIS_AVP 9 + 2
#define LS_ZARTPREIS_KE_MWST 1 + 1
#define LS_ZARTPREIS_HERST_PROZENT 5 + 2
#define LS_ZARTPREIS_EAVP 9 + 2
#define LS_ZARTPREIS_MAXAVP 9 + 2
#define LS_ZARTPREIS_PREIS_TYP 5 + 1
#define LS_ZARTPREIS_AGP 9 + 2

#define ZARTPREISARTIKEL_NR 0
#define ZARTPREISDATUMGUELTIGAB 1
#define ZARTPREISGROSSO 2
#define ZARTPREISAEP 3
#define ZARTPREISAVP 4
#define ZARTPREISKE_MWST 5
#define ZARTPREISHERST_PROZENT 6
#define ZARTPREISEAVP 7
#define ZARTPREISMAXAVP 8
#define ZARTPREISPREIS_TYP 9
#define ZARTPREISAGP 10

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define ZARTPREIS_H
#define ZARTPREIS_ANZ ( sizeof(ZARTPREIS_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ZARTPREIS *****************************************************/

#define ZARTPREIS_LISTE \
        ZARTPREIS.ARTIKEL_NR,\
        ZARTPREIS.DATUMGUELTIGAB,\
        ZARTPREIS.GROSSO,\
        ZARTPREIS.AEP,\
        ZARTPREIS.AVP,\
        ZARTPREIS.KE_MWST,\
        ZARTPREIS.HERST_PROZENT,\
        ZARTPREIS.EAVP,\
        ZARTPREIS.MAXAVP,\
        ZARTPREIS.PREIS_TYP,\
        ZARTPREIS.AGP
#define ZARTPREIS_LISTE_390 \
        ARTIKEL_NR,\
        DATUMGUELTIGAB,\
        GROSSO,\
        AEP,\
        AVP,\
        KE_MWST,\
        HERST_PROZENT,\
        EAVP,\
        MAXAVP,\
        PREIS_TYP,\
        AGP
#define ZARTPREIS_PLISTE \
        "ZARTPREIS.ARTIKEL_NR,"\
        "ZARTPREIS.DATUMGUELTIGAB,"\
        "ZARTPREIS.GROSSO,"\
        "ZARTPREIS.AEP,"\
        "ZARTPREIS.AVP,"\
        "ZARTPREIS.KE_MWST,"\
        "ZARTPREIS.HERST_PROZENT,"\
        "ZARTPREIS.EAVP,"\
        "ZARTPREIS.MAXAVP,"\
        "ZARTPREIS.PREIS_TYP,"\
        "ZARTPREIS.AGP"
#define ZARTPREIS_PELISTE \
        "ARTIKEL_NR,"\
        "DATUMGUELTIGAB,"\
        "GROSSO,"\
        "AEP,"\
        "AVP,"\
        "KE_MWST,"\
        "HERST_PROZENT,"\
        "EAVP,"\
        "MAXAVP,"\
        "PREIS_TYP,"\
        "AGP"
#define ZARTPREIS_UPDLISTE \
        "ARTIKEL_NR=?,"\
        "DATUMGUELTIGAB=?,"\
        "GROSSO=?,"\
        "AEP=?,"\
        "AVP=?,"\
        "KE_MWST=?,"\
        "HERST_PROZENT=?,"\
        "EAVP=?,"\
        "MAXAVP=?,"\
        "PREIS_TYP=?,"\
        "AGP=?"
/* SqlMacros-Define of ZARTPREIS **********************************************/

#define ZARTPREIS_ZEIGER(x) \
        :x->ARTIKEL_NR,\
        :x->DATUMGUELTIGAB,\
        :x->GROSSO,\
        :x->AEP,\
        :x->AVP,\
        :x->KE_MWST,\
        :x->HERST_PROZENT,\
        :x->EAVP,\
        :x->MAXAVP,\
        :x->PREIS_TYP,\
        :x->AGP
#define ZARTPREIS_ZEIGERSEL(x) \
        :x->ARTIKEL_NR,\
        :x->DATUMGUELTIGAB,\
        :x->GROSSO,\
        :x->AEP,\
        :x->AVP,\
        :x->KE_MWST,\
        :x->HERST_PROZENT,\
        :x->EAVP,\
        :x->MAXAVP,\
        :x->PREIS_TYP,\
        :x->AGP
#define ZARTPREIS_UPDATE(x) \
        ZARTPREIS.ARTIKEL_NR=:x->ARTIKEL_NR,\
        ZARTPREIS.DATUMGUELTIGAB=:x->DATUMGUELTIGAB,\
        ZARTPREIS.GROSSO=:x->GROSSO,\
        ZARTPREIS.AEP=:x->AEP,\
        ZARTPREIS.AVP=:x->AVP,\
        ZARTPREIS.KE_MWST=:x->KE_MWST,\
        ZARTPREIS.HERST_PROZENT=:x->HERST_PROZENT,\
        ZARTPREIS.EAVP=:x->EAVP,\
        ZARTPREIS.MAXAVP=:x->MAXAVP,\
        ZARTPREIS.PREIS_TYP=:x->PREIS_TYP,\
        ZARTPREIS.AGP=:x->AGP
/* SqlMacros390-Define of ZARTPREIS *******************************************/

#define ZARTPREIS_ZEIGER_390 \
        :ARTIKEL_NR,\
        :DATUMGUELTIGAB,\
        :GROSSO,\
        :AEP,\
        :AVP,\
        :KE_MWST,\
        :HERST_PROZENT,\
        :EAVP,\
        :MAXAVP,\
        :PREIS_TYP,\
        :AGP
#define ZARTPREIS_UPDATE_390 \
        ARTIKEL_NR=:ARTIKEL_NR,\
        DATUMGUELTIGAB=:DATUMGUELTIGAB,\
        GROSSO=:GROSSO,\
        AEP=:AEP,\
        AVP=:AVP,\
        KE_MWST=:KE_MWST,\
        HERST_PROZENT=:HERST_PROZENT,\
        EAVP=:EAVP,\
        MAXAVP=:MAXAVP,\
        PREIS_TYP=:PREIS_TYP,\
        AGP=:AGP
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of ZARTPREIS ***********************************************/

#ifndef TRANSCLASS
typedef struct N_ZARTPREIS {
    long ARTIKEL_NR;
    long DATUMGUELTIGAB;
    double GROSSO;
    double AEP;
    double AVP;
    char KE_MWST[2];
    double HERST_PROZENT;
    double EAVP;
    double MAXAVP;
    short PREIS_TYP;
    double AGP;
} zartpreisS;
#else /* TRANSCLASS */
typedef struct N_ZARTPREIS {
    long ARTIKEL_NR;
    long DATUMGUELTIGAB;
    double GROSSO;
    double AEP;
    double AVP;
    char KE_MWST[2];
    double HERST_PROZENT;
    double EAVP;
    double MAXAVP;
    short PREIS_TYP;
    double AGP;

    bool operator == (const N_ZARTPREIS& right) const {
        return (
            ARTIKEL_NR == right.ARTIKEL_NR &&
            DATUMGUELTIGAB == right.DATUMGUELTIGAB &&
            GROSSO == right.GROSSO &&
            AEP == right.AEP &&
            AVP == right.AVP &&
            !strcmp(KE_MWST, right.KE_MWST) &&
            HERST_PROZENT == right.HERST_PROZENT &&
            EAVP == right.EAVP &&
            MAXAVP == right.MAXAVP &&
            PREIS_TYP == right.PREIS_TYP &&
            AGP == right.AGP
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        ARTIKEL_NR = 0;
        DATUMGUELTIGAB = 0;
        GROSSO = 0;
        AEP = 0;
        AVP = 0;
        strcpy(KE_MWST, " " );
        HERST_PROZENT = 0;
        EAVP = 0;
        MAXAVP = 0;
        PREIS_TYP = 0;
        AGP = 0;
#endif
    }
} zartpreisS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ZARTPREIS *****************************************/

struct S_ZARTPREIS {
    char ARTIKEL_NR[11];
    char DATUMGUELTIGAB[11];
    char GROSSO[9 + 2];
    char AEP[9 + 2];
    char AVP[9 + 2];
    char KE_MWST[1 + 1];
    char HERST_PROZENT[5 + 2];
    char EAVP[9 + 2];
    char MAXAVP[9 + 2];
    char PREIS_TYP[7];
    char AGP[9 + 2];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ZARTPREIS ************************/

struct O_ZARTPREIS {
    char ARTIKEL_NR[11];
    char DATUMGUELTIGAB[11];
    char GROSSO[9];
    char AEP[9];
    char AVP[9];
    char KE_MWST[1];
    char HERST_PROZENT[5];
    char EAVP[9];
    char MAXAVP[9];
    char PREIS_TYP[7];
    char AGP[9];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ZARTPREIS ***********************************/

struct C_ZARTPREIS {
    long ARTIKEL_NR;
    long DATUMGUELTIGAB;
    double GROSSO;
    double AEP;
    double AVP;
    char KE_MWST;
    double HERST_PROZENT;
    double EAVP;
    double MAXAVP;
    short PREIS_TYP;
    double AGP;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ZARTPREIS *********************************/

struct I_ZARTPREIS {
    short ARTIKEL_NR;
    short DATUMGUELTIGAB;
    short GROSSO;
    short AEP;
    short AVP;
    short KE_MWST;
    short HERST_PROZENT;
    short EAVP;
    short MAXAVP;
    short PREIS_TYP;
    short AGP;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ZARTPREIS *******************************************/

#if defined (BUF_DESC)
static struct buf_desc ZARTPREIS_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_C, 1, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_S ,  6, 0 },
   { TYP_D, 9, 2 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc ZARTPREIS_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_C, 1, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_S ,  6, 0 },
   { TYP_D, 9, 2 },
};
#endif

/* description for datatypes of ZARTPREIS *************************************/

 #define ZARTPREIS_S390 \
         long ARTIKEL_NR; \
         long DATUMGUELTIGAB; \
         double GROSSO; \
         double AEP; \
         double AVP; \
         char KE_MWST; \
         double HERST_PROZENT; \
         double EAVP; \
         double MAXAVP; \
         short PREIS_TYP; \
         double AGP; \



/* Copy-Function Struct to single Data ZARTPREIS ******************************/

 #define ZARTPREIS_S390_COPY_TO_SINGLE(_x_) \
         ARTIKEL_NR=_x_->ARTIKEL_NR;\
         DATUMGUELTIGAB=_x_->DATUMGUELTIGAB;\
         GROSSO=_x_->GROSSO;\
         AEP=_x_->AEP;\
         AVP=_x_->AVP;\
         KE_MWST=_x_->KE_MWST;\
         HERST_PROZENT=_x_->HERST_PROZENT;\
         EAVP=_x_->EAVP;\
         MAXAVP=_x_->MAXAVP;\
         PREIS_TYP=_x_->PREIS_TYP;\
         AGP=_x_->AGP;\

 #define ZARTPREIS_S390_COPY_TO_STRUCT(_x_) \
          _x_->ARTIKEL_NR=ARTIKEL_NR;\
          _x_->DATUMGUELTIGAB=DATUMGUELTIGAB;\
          _x_->GROSSO=GROSSO;\
          _x_->AEP=AEP;\
          _x_->AVP=AVP;\
          _x_->KE_MWST=KE_MWST;\
          _x_->HERST_PROZENT=HERST_PROZENT;\
          _x_->EAVP=EAVP;\
          _x_->MAXAVP=MAXAVP;\
          _x_->PREIS_TYP=PREIS_TYP;\
          _x_->AGP=AGP;\



/* FunctionNumber-Define of zartpreis *****************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of zartpreis *************************************/


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

class CZARTPREIS : public ppDadeVirtual {
public:
    zartpreisS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<zartpreisS> lst; // class list

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
                     vector< zartpreisS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     zartpreisS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< zartpreisS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<zartpreisS>::iterator
                 beginList() { return lst.begin(); }
    vector<zartpreisS>::iterator
                 endList  () { return lst.end  (); }

    long         GetArtikel_nr() const { return s.ARTIKEL_NR; }
    long         GetDatumgueltigab() const { return s.DATUMGUELTIGAB; }
    double       GetGrosso() const { return s.GROSSO; }
    double       GetAep() const { return s.AEP; }
    double       GetAvp() const { return s.AVP; }
    char         GetKe_mwst() const { return s.KE_MWST[0]; }
    double       GetHerst_prozent() const { return s.HERST_PROZENT; }
    double       GetEavp() const { return s.EAVP; }
    double       GetMaxavp() const { return s.MAXAVP; }
    short        GetPreis_typ() const { return s.PREIS_TYP; }
    double       GetAgp() const { return s.AGP; }

    const zartpreisS &
                 GetStruct() const { return s; }
    void         SetArtikel_nr(long t) { s.ARTIKEL_NR = t; }
    void         SetDatumgueltigab(long t) { s.DATUMGUELTIGAB = t; }
    void         SetGrosso(double t) { s.GROSSO = t; }
    void         SetAep(double t) { s.AEP = t; }
    void         SetAvp(double t) { s.AVP = t; }
    void         SetKe_mwst(char t) { s.KE_MWST[0] = t; s.KE_MWST[1] = '\0';}
    void         SetHerst_prozent(double t) { s.HERST_PROZENT = t; }
    void         SetEavp(double t) { s.EAVP = t; }
    void         SetMaxavp(double t) { s.MAXAVP = t; }
    void         SetPreis_typ(short t) { s.PREIS_TYP = t; }
    void         SetAgp(double t) { s.AGP = t; }

    void         SetStruct(const zartpreisS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CZARTPREIS() {
        ::buf_default((void *)&s, ZARTPREIS_BES, ZARTPREIS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CZARTPREIS() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, ZARTPREIS_BES, ZARTPREIS_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, ZARTPREIS_BES, (int)ZARTPREIS_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, ZARTPREIS_BES, (int)ZARTPREIS_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_ZARTPREIS & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, ZARTPREIS_BES, (int)ZARTPREIS_ANZ, error_msg);
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
/* CreateSqlStatement of ZARTPREIS ********************************************/

 #define ZARTPREIS_CREATE(x) EXEC SQL create table x (\
         ARTIKEL_NR integer default 0 not null,\
         DATUMGUELTIGAB integer default 0 not null,\
         GROSSO decimal(9,2) default 0 not null,\
         AEP decimal(9,2) default 0 not null,\
         AVP decimal(9,2) default 0 not null,\
         KE_MWST char(1) default " " not null,\
         HERST_PROZENT decimal(5,2) default 0 not null,\
         EAVP decimal(9,2) default 0 not null,\
         MAXAVP decimal(9,2) default 0 not null,\
         PREIS_TYP smallint default 0 not null,\
         AGP decimal(9,2) default 0 not null) in phosix extent size 784 next size 80 lock mode row;



/* CreateIndexStatement of ZARTPREIS ******************************************/

 #define ZARTPREIS_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_zartpreis_1 on _X_(\
              artikel_nr,\
              preis_typ,\
              datumgueltigab ) in phosix1;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ZARTPREIS ******************************************/

 #define ZARTPREIS_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_zartpreis_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
