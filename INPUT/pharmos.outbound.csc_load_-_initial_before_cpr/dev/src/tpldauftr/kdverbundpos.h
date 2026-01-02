#ifndef __PP_KDVERBUNDPOS_H_
#define __PP_KDVERBUNDPOS_H_

/******************************************************************************/
/* d:\prj\DF\UNIX\tpldauftr\kdverbundpos **************************************/
/* produced by DADE 6.22.0 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <pplib/bufkon.h>

/* Length-Define of KDVERBUNDPOS **********************************************/

#define L_KDVERBUNDPOS_HERKUNFTFILIALE 6
#define L_KDVERBUNDPOS_KDAUFTRAGNR 11
#define L_KDVERBUNDPOS_POSNR 11
#define L_KDVERBUNDPOS_ARTIKEL_NR 11
#define L_KDVERBUNDPOS_MENGEABGEBUCHT 11
#define L_KDVERBUNDPOS_FILIALNR 6
#define L_KDVERBUNDPOS_BEMERKUNGEN 240
#define L_KDVERBUNDPOS_KDAUFTRAGBESTELLNR 9
#define L_KDVERBUNDPOS_CODE_TYPE 6
#define L_KDVERBUNDPOS_ARTICLE_CODE 25
#define L_KDVERBUNDPOS_PROCESSINGSTATUS 6
#define L_KDVERBUNDPOS_PREISEKAPOFREE 9
#define N_KDVERBUNDPOS_PREISEKAPOFREE 2
#define L_KDVERBUNDPOS_IBTTYPE 6

/* Length/Count-Define of KDVERBUNDPOS ****************************************/

#define LS_KDVERBUNDPOS_HERKUNFTFILIALE 5 + 1
#define LS_KDVERBUNDPOS_KDAUFTRAGNR 10 + 1
#define LS_KDVERBUNDPOS_POSNR 10 + 1
#define LS_KDVERBUNDPOS_ARTIKEL_NR 10 + 1
#define LS_KDVERBUNDPOS_MENGEABGEBUCHT 10 + 1
#define LS_KDVERBUNDPOS_FILIALNR 5 + 1
#define LS_KDVERBUNDPOS_BEMERKUNGEN 240 + 1
#define LS_KDVERBUNDPOS_KDAUFTRAGBESTELLNR 9 + 1
#define LS_KDVERBUNDPOS_CODE_TYPE 5 + 1
#define LS_KDVERBUNDPOS_ARTICLE_CODE 25 + 1
#define LS_KDVERBUNDPOS_PROCESSINGSTATUS 5 + 1
#define LS_KDVERBUNDPOS_PREISEKAPOFREE 9 + 2
#define LS_KDVERBUNDPOS_IBTTYPE 5 + 1

#define KDVERBUNDPOSHERKUNFTFILIALE 0
#define KDVERBUNDPOSKDAUFTRAGNR 1
#define KDVERBUNDPOSPOSNR 2
#define KDVERBUNDPOSARTIKEL_NR 3
#define KDVERBUNDPOSMENGEABGEBUCHT 4
#define KDVERBUNDPOSFILIALNR 5
#define KDVERBUNDPOSBEMERKUNGEN 6
#define KDVERBUNDPOSKDAUFTRAGBESTELLNR 7
#define KDVERBUNDPOSCODE_TYPE 8
#define KDVERBUNDPOSARTICLE_CODE 9
#define KDVERBUNDPOSPROCESSINGSTATUS 10
#define KDVERBUNDPOSPREISEKAPOFREE 11
#define KDVERBUNDPOSIBTTYPE 12

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define KDVERBUNDPOS_H
#define KDVERBUNDPOS_ANZ ( sizeof(KDVERBUNDPOS_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of KDVERBUNDPOS **************************************************/

#define KDVERBUNDPOS_LISTE \
        KDVERBUNDPOS.HERKUNFTFILIALE,\
        KDVERBUNDPOS.KDAUFTRAGNR,\
        KDVERBUNDPOS.POSNR,\
        KDVERBUNDPOS.ARTIKEL_NR,\
        KDVERBUNDPOS.MENGEABGEBUCHT,\
        KDVERBUNDPOS.FILIALNR,\
        KDVERBUNDPOS.BEMERKUNGEN,\
        KDVERBUNDPOS.KDAUFTRAGBESTELLNR,\
        KDVERBUNDPOS.CODE_TYPE,\
        KDVERBUNDPOS.ARTICLE_CODE,\
        KDVERBUNDPOS.PROCESSINGSTATUS,\
        KDVERBUNDPOS.PREISEKAPOFREE,\
        KDVERBUNDPOS.IBTTYPE
#define KDVERBUNDPOS_LISTE_390 \
        HERKUNFTFILIALE,\
        KDAUFTRAGNR,\
        POSNR,\
        ARTIKEL_NR,\
        MENGEABGEBUCHT,\
        FILIALNR,\
        BEMERKUNGEN,\
        KDAUFTRAGBESTELLNR,\
        CODE_TYPE,\
        ARTICLE_CODE,\
        PROCESSINGSTATUS,\
        PREISEKAPOFREE,\
        IBTTYPE
#define KDVERBUNDPOS_PLISTE \
        "KDVERBUNDPOS.HERKUNFTFILIALE,"\
        "KDVERBUNDPOS.KDAUFTRAGNR,"\
        "KDVERBUNDPOS.POSNR,"\
        "KDVERBUNDPOS.ARTIKEL_NR,"\
        "KDVERBUNDPOS.MENGEABGEBUCHT,"\
        "KDVERBUNDPOS.FILIALNR,"\
        "KDVERBUNDPOS.BEMERKUNGEN,"\
        "KDVERBUNDPOS.KDAUFTRAGBESTELLNR,"\
        "KDVERBUNDPOS.CODE_TYPE,"\
        "KDVERBUNDPOS.ARTICLE_CODE,"\
        "KDVERBUNDPOS.PROCESSINGSTATUS,"\
        "KDVERBUNDPOS.PREISEKAPOFREE,"\
        "KDVERBUNDPOS.IBTTYPE"
#define KDVERBUNDPOS_PELISTE \
        "HERKUNFTFILIALE,"\
        "KDAUFTRAGNR,"\
        "POSNR,"\
        "ARTIKEL_NR,"\
        "MENGEABGEBUCHT,"\
        "FILIALNR,"\
        "BEMERKUNGEN,"\
        "KDAUFTRAGBESTELLNR,"\
        "CODE_TYPE,"\
        "ARTICLE_CODE,"\
        "PROCESSINGSTATUS,"\
        "PREISEKAPOFREE,"\
        "IBTTYPE"
#define KDVERBUNDPOS_UPDLISTE \
        "HERKUNFTFILIALE=?,"\
        "KDAUFTRAGNR=?,"\
        "POSNR=?,"\
        "ARTIKEL_NR=?,"\
        "MENGEABGEBUCHT=?,"\
        "FILIALNR=?,"\
        "BEMERKUNGEN=?,"\
        "KDAUFTRAGBESTELLNR=?,"\
        "CODE_TYPE=?,"\
        "ARTICLE_CODE=?,"\
        "PROCESSINGSTATUS=?,"\
        "PREISEKAPOFREE=?,"\
        "IBTTYPE=?"
/* SqlMacros-Define of KDVERBUNDPOS *******************************************/

#define KDVERBUNDPOS_ZEIGER(x) \
        :x->HERKUNFTFILIALE,\
        :x->KDAUFTRAGNR,\
        :x->POSNR,\
        :x->ARTIKEL_NR,\
        :x->MENGEABGEBUCHT,\
        :x->FILIALNR,\
        :x->BEMERKUNGEN,\
        :x->KDAUFTRAGBESTELLNR,\
        :x->CODE_TYPE,\
        :x->ARTICLE_CODE,\
        :x->PROCESSINGSTATUS,\
        :x->PREISEKAPOFREE,\
        :x->IBTTYPE
#define KDVERBUNDPOS_ZEIGERSEL(x) \
        :x->HERKUNFTFILIALE,\
        :x->KDAUFTRAGNR,\
        :x->POSNR,\
        :x->ARTIKEL_NR,\
        :x->MENGEABGEBUCHT,\
        :x->FILIALNR,\
        :x->BEMERKUNGEN,\
        :x->KDAUFTRAGBESTELLNR,\
        :x->CODE_TYPE,\
        :x->ARTICLE_CODE,\
        :x->PROCESSINGSTATUS,\
        :x->PREISEKAPOFREE,\
        :x->IBTTYPE
#define KDVERBUNDPOS_UPDATE(x) \
        KDVERBUNDPOS.HERKUNFTFILIALE=:x->HERKUNFTFILIALE,\
        KDVERBUNDPOS.KDAUFTRAGNR=:x->KDAUFTRAGNR,\
        KDVERBUNDPOS.POSNR=:x->POSNR,\
        KDVERBUNDPOS.ARTIKEL_NR=:x->ARTIKEL_NR,\
        KDVERBUNDPOS.MENGEABGEBUCHT=:x->MENGEABGEBUCHT,\
        KDVERBUNDPOS.FILIALNR=:x->FILIALNR,\
        KDVERBUNDPOS.BEMERKUNGEN=:x->BEMERKUNGEN,\
        KDVERBUNDPOS.KDAUFTRAGBESTELLNR=:x->KDAUFTRAGBESTELLNR,\
        KDVERBUNDPOS.CODE_TYPE=:x->CODE_TYPE,\
        KDVERBUNDPOS.ARTICLE_CODE=:x->ARTICLE_CODE,\
        KDVERBUNDPOS.PROCESSINGSTATUS=:x->PROCESSINGSTATUS,\
        KDVERBUNDPOS.PREISEKAPOFREE=:x->PREISEKAPOFREE,\
        KDVERBUNDPOS.IBTTYPE=:x->IBTTYPE
/* SqlMacros390-Define of KDVERBUNDPOS ****************************************/

#define KDVERBUNDPOS_ZEIGER_390 \
        :HERKUNFTFILIALE,\
        :KDAUFTRAGNR,\
        :POSNR,\
        :ARTIKEL_NR,\
        :MENGEABGEBUCHT,\
        :FILIALNR,\
        :BEMERKUNGEN,\
        :KDAUFTRAGBESTELLNR,\
        :CODE_TYPE,\
        :ARTICLE_CODE,\
        :PROCESSINGSTATUS,\
        :PREISEKAPOFREE,\
        :IBTTYPE
#define KDVERBUNDPOS_UPDATE_390 \
        HERKUNFTFILIALE=:HERKUNFTFILIALE,\
        KDAUFTRAGNR=:KDAUFTRAGNR,\
        POSNR=:POSNR,\
        ARTIKEL_NR=:ARTIKEL_NR,\
        MENGEABGEBUCHT=:MENGEABGEBUCHT,\
        FILIALNR=:FILIALNR,\
        BEMERKUNGEN=:BEMERKUNGEN,\
        KDAUFTRAGBESTELLNR=:KDAUFTRAGBESTELLNR,\
        CODE_TYPE=:CODE_TYPE,\
        ARTICLE_CODE=:ARTICLE_CODE,\
        PROCESSINGSTATUS=:PROCESSINGSTATUS,\
        PREISEKAPOFREE=:PREISEKAPOFREE,\
        IBTTYPE=:IBTTYPE
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of KDVERBUNDPOS ********************************************/

#ifndef TRANSCLASS
typedef struct N_KDVERBUNDPOS {
    short HERKUNFTFILIALE;
    long KDAUFTRAGNR;
    long POSNR;
    long ARTIKEL_NR;
    long MENGEABGEBUCHT;
    short FILIALNR;
    char BEMERKUNGEN[241];
    char KDAUFTRAGBESTELLNR[10];
    short CODE_TYPE;
    char ARTICLE_CODE[26];
    short PROCESSINGSTATUS;
    double PREISEKAPOFREE;
    short IBTTYPE;
} kdverbundposS;
#else /* TRANSCLASS */
typedef struct N_KDVERBUNDPOS {
    short HERKUNFTFILIALE;
    long KDAUFTRAGNR;
    long POSNR;
    long ARTIKEL_NR;
    long MENGEABGEBUCHT;
    short FILIALNR;
    char BEMERKUNGEN[241];
    char KDAUFTRAGBESTELLNR[10];
    short CODE_TYPE;
    char ARTICLE_CODE[26];
    short PROCESSINGSTATUS;
    double PREISEKAPOFREE;
    short IBTTYPE;

    bool operator == (const N_KDVERBUNDPOS& right) const {
        return (
            HERKUNFTFILIALE == right.HERKUNFTFILIALE &&
            KDAUFTRAGNR == right.KDAUFTRAGNR &&
            POSNR == right.POSNR &&
            ARTIKEL_NR == right.ARTIKEL_NR &&
            MENGEABGEBUCHT == right.MENGEABGEBUCHT &&
            FILIALNR == right.FILIALNR &&
            !strcmp(BEMERKUNGEN, right.BEMERKUNGEN) &&
            !strcmp(KDAUFTRAGBESTELLNR, right.KDAUFTRAGBESTELLNR) &&
            CODE_TYPE == right.CODE_TYPE &&
            !strcmp(ARTICLE_CODE, right.ARTICLE_CODE) &&
            PROCESSINGSTATUS == right.PROCESSINGSTATUS &&
            PREISEKAPOFREE == right.PREISEKAPOFREE &&
            IBTTYPE == right.IBTTYPE
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        HERKUNFTFILIALE = 0;
        KDAUFTRAGNR = 0;
        POSNR = 0;
        ARTIKEL_NR = 0;
        MENGEABGEBUCHT = 0;
        FILIALNR = 0;
        strcpy(BEMERKUNGEN, " " );
        strcpy(KDAUFTRAGBESTELLNR, " " );
        CODE_TYPE = 0;
        strcpy(ARTICLE_CODE, " " );
        PROCESSINGSTATUS = 0;
        PREISEKAPOFREE = 0;
        IBTTYPE = 0;
#endif
    }
} kdverbundposS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of KDVERBUNDPOS **************************************/

struct S_KDVERBUNDPOS {
    char HERKUNFTFILIALE[7];
    char KDAUFTRAGNR[11];
    char POSNR[11];
    char ARTIKEL_NR[11];
    char MENGEABGEBUCHT[11];
    char FILIALNR[7];
    char BEMERKUNGEN[240 + 1];
    char KDAUFTRAGBESTELLNR[9 + 1];
    char CODE_TYPE[7];
    char ARTICLE_CODE[25 + 1];
    char PROCESSINGSTATUS[7];
    char PREISEKAPOFREE[9 + 2];
    char IBTTYPE[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of KDVERBUNDPOS *********************/

struct O_KDVERBUNDPOS {
    char HERKUNFTFILIALE[7];
    char KDAUFTRAGNR[11];
    char POSNR[11];
    char ARTIKEL_NR[11];
    char MENGEABGEBUCHT[11];
    char FILIALNR[7];
    char BEMERKUNGEN[240];
    char KDAUFTRAGBESTELLNR[9];
    char CODE_TYPE[7];
    char ARTICLE_CODE[25];
    char PROCESSINGSTATUS[7];
    char PREISEKAPOFREE[9];
    char IBTTYPE[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of KDVERBUNDPOS ********************************/

struct C_KDVERBUNDPOS {
    short HERKUNFTFILIALE;
    long KDAUFTRAGNR;
    long POSNR;
    long ARTIKEL_NR;
    long MENGEABGEBUCHT;
    short FILIALNR;
    char BEMERKUNGEN[241];
    char KDAUFTRAGBESTELLNR[10];
    short CODE_TYPE;
    char ARTICLE_CODE[26];
    short PROCESSINGSTATUS;
    double PREISEKAPOFREE;
    short IBTTYPE;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of KDVERBUNDPOS ******************************/

struct I_KDVERBUNDPOS {
    short HERKUNFTFILIALE;
    short KDAUFTRAGNR;
    short POSNR;
    short ARTIKEL_NR;
    short MENGEABGEBUCHT;
    short FILIALNR;
    short BEMERKUNGEN;
    short KDAUFTRAGBESTELLNR;
    short CODE_TYPE;
    short ARTICLE_CODE;
    short PROCESSINGSTATUS;
    short PREISEKAPOFREE;
    short IBTTYPE;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of KDVERBUNDPOS ****************************************/

#if defined (BUF_DESC)
static struct buf_desc KDVERBUNDPOS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 240, 0 },
   { TYP_C, 9, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 25, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 9, 2 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc KDVERBUNDPOS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 240, 0 },
   { TYP_C, 9, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 25, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 9, 2 },
   { TYP_S ,  6, 0 },
};
#endif

/* description for datatypes of KDVERBUNDPOS **********************************/

 #define KDVERBUNDPOS_S390 \
         short HERKUNFTFILIALE; \
         long KDAUFTRAGNR; \
         long POSNR; \
         long ARTIKEL_NR; \
         long MENGEABGEBUCHT; \
         short FILIALNR; \
         char BEMERKUNGEN[241]; \
         char KDAUFTRAGBESTELLNR[10]; \
         short CODE_TYPE; \
         char ARTICLE_CODE[26]; \
         short PROCESSINGSTATUS; \
         double PREISEKAPOFREE; \
         short IBTTYPE; \



/* Copy-Function Struct to single Data KDVERBUNDPOS ***************************/

 #define KDVERBUNDPOS_S390_COPY_TO_SINGLE(_x_) \
         HERKUNFTFILIALE=_x_->HERKUNFTFILIALE;\
         KDAUFTRAGNR=_x_->KDAUFTRAGNR;\
         POSNR=_x_->POSNR;\
         ARTIKEL_NR=_x_->ARTIKEL_NR;\
         MENGEABGEBUCHT=_x_->MENGEABGEBUCHT;\
         FILIALNR=_x_->FILIALNR;\
          strcpy(BEMERKUNGEN,_x_->BEMERKUNGEN);\
          strcpy(KDAUFTRAGBESTELLNR,_x_->KDAUFTRAGBESTELLNR);\
         CODE_TYPE=_x_->CODE_TYPE;\
          strcpy(ARTICLE_CODE,_x_->ARTICLE_CODE);\
         PROCESSINGSTATUS=_x_->PROCESSINGSTATUS;\
         PREISEKAPOFREE=_x_->PREISEKAPOFREE;\
         IBTTYPE=_x_->IBTTYPE;\

 #define KDVERBUNDPOS_S390_COPY_TO_STRUCT(_x_) \
          _x_->HERKUNFTFILIALE=HERKUNFTFILIALE;\
          _x_->KDAUFTRAGNR=KDAUFTRAGNR;\
          _x_->POSNR=POSNR;\
          _x_->ARTIKEL_NR=ARTIKEL_NR;\
          _x_->MENGEABGEBUCHT=MENGEABGEBUCHT;\
          _x_->FILIALNR=FILIALNR;\
          strcpy(_x_->BEMERKUNGEN,BEMERKUNGEN);\
          strcpy(_x_->KDAUFTRAGBESTELLNR,KDAUFTRAGBESTELLNR);\
          _x_->CODE_TYPE=CODE_TYPE;\
          strcpy(_x_->ARTICLE_CODE,ARTICLE_CODE);\
          _x_->PROCESSINGSTATUS=PROCESSINGSTATUS;\
          _x_->PREISEKAPOFREE=PREISEKAPOFREE;\
          _x_->IBTTYPE=IBTTYPE;\



/* FunctionNumber-Define of kdverbundpos **************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of kdverbundpos **********************************/


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

class CKDVERBUNDPOS : public ppDadeVirtual {
public:
    kdverbundposS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<kdverbundposS> lst; // class list

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
                     vector< kdverbundposS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     kdverbundposS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< kdverbundposS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<kdverbundposS>::iterator
                 beginList() { return lst.begin(); }
    vector<kdverbundposS>::iterator
                 endList  () { return lst.end  (); }

    short        GetHerkunftfiliale() const { return s.HERKUNFTFILIALE; }
    long         GetKdauftragnr() const { return s.KDAUFTRAGNR; }
    long         GetPosnr() const { return s.POSNR; }
    long         GetArtikel_nr() const { return s.ARTIKEL_NR; }
    long         GetMengeabgebucht() const { return s.MENGEABGEBUCHT; }
    short        GetFilialnr() const { return s.FILIALNR; }
    const char*  GetBemerkungen(ppString & t) const { t = s.BEMERKUNGEN; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetKdauftragbestellnr(ppString & t) const { t = s.KDAUFTRAGBESTELLNR; t.erasespace(ppString::END); return t.c_str(); }
    short        GetCode_type() const { return s.CODE_TYPE; }
    const char*  GetArticle_code(ppString & t) const { t = s.ARTICLE_CODE; t.erasespace(ppString::END); return t.c_str(); }
    short        GetProcessingstatus() const { return s.PROCESSINGSTATUS; }
    double       GetPreisekapofree() const { return s.PREISEKAPOFREE; }
    short        GetIbttype() const { return s.IBTTYPE; }

    const kdverbundposS &
                 GetStruct() const { return s; }
    void         SetHerkunftfiliale(short t) { s.HERKUNFTFILIALE = t; }
    void         SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
    void         SetPosnr(long t) { s.POSNR = t; }
    void         SetArtikel_nr(long t) { s.ARTIKEL_NR = t; }
    void         SetMengeabgebucht(long t) { s.MENGEABGEBUCHT = t; }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetBemerkungen(const ppString & t) { ppGStrCopy(s.BEMERKUNGEN, t.c_str(), L_KDVERBUNDPOS_BEMERKUNGEN); }
    void         SetKdauftragbestellnr(const ppString & t) { ppGStrCopy(s.KDAUFTRAGBESTELLNR, t.c_str(), L_KDVERBUNDPOS_KDAUFTRAGBESTELLNR); }
    void         SetCode_type(short t) { s.CODE_TYPE = t; }
    void         SetArticle_code(const ppString & t) { ppGStrCopy(s.ARTICLE_CODE, t.c_str(), L_KDVERBUNDPOS_ARTICLE_CODE); }
    void         SetProcessingstatus(short t) { s.PROCESSINGSTATUS = t; }
    void         SetPreisekapofree(double t) { s.PREISEKAPOFREE = t; }
    void         SetIbttype(short t) { s.IBTTYPE = t; }

    void         SetStruct(const kdverbundposS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CKDVERBUNDPOS() {
        ::buf_default((void *)&s, KDVERBUNDPOS_BES, KDVERBUNDPOS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CKDVERBUNDPOS() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, KDVERBUNDPOS_BES, KDVERBUNDPOS_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, KDVERBUNDPOS_BES, (int)KDVERBUNDPOS_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, KDVERBUNDPOS_BES, (int)KDVERBUNDPOS_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_KDVERBUNDPOS & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.BEMERKUNGEN);
        ppGStripLast(d.KDAUFTRAGBESTELLNR);
        ppGStripLast(d.ARTICLE_CODE);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, KDVERBUNDPOS_BES, (int)KDVERBUNDPOS_ANZ, error_msg);
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
/* CreateSqlStatement of KDVERBUNDPOS *****************************************/

 #define KDVERBUNDPOS_CREATE(x) EXEC SQL create table x (\
         HERKUNFTFILIALE smallint default 0 not null,\
         KDAUFTRAGNR integer default 0 not null,\
         POSNR integer default 0 not null,\
         ARTIKEL_NR integer default 0 not null,\
         MENGEABGEBUCHT integer default 0 not null,\
         FILIALNR smallint default 0 not null,\
         BEMERKUNGEN varchar(240,0) default " " not null,\
         KDAUFTRAGBESTELLNR char(9) default " " not null,\
         CODE_TYPE smallint default 0 not null,\
         ARTICLE_CODE char(25) default " " not null,\
         PROCESSINGSTATUS smallint default 0 not null,\
         PREISEKAPOFREE decimal(9,2) default 0 not null,\
         IBTTYPE smallint default 0 not null) in KscOrder extent size 224 next size 24 lock mode row;



/* CreateIndexStatement of KDVERBUNDPOS ***************************************/

 #define KDVERBUNDPOS_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_kdverbundpos_1 on _X_(\
              filialnr,\
              herkunftfiliale,\
              kdauftragnr,\
              posnr,\
              ibttype ) in KscOrderIdx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of KDVERBUNDPOS ***************************************/

 #define KDVERBUNDPOS_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_kdverbundpos_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
