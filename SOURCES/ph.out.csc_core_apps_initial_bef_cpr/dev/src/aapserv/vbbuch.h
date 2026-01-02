#ifndef __PP_VBBUCH_H_
#define __PP_VBBUCH_H_

/******************************************************************************/
/* d:\prj\AA\UNIX\aapserv\src\VBBUCH ******************************************/
/* produced by DADE 6.21.6 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of VBBUCH ****************************************************/

#define L_VBBUCH_ARTIKEL_NR 11
#define L_VBBUCH_FILIALNR 6
#define L_VBBUCH_DARREICHFORM 3
#define L_VBBUCH_EINHEIT 9
#define L_VBBUCH_BESTAND 11
#define L_VBBUCH_ARTIKEL_NAME 30
#define L_VBBUCH_MENGEBESTELLT 11
#define L_VBBUCH_MENGEBESTAETIGT 11
#define L_VBBUCH_MENGENATRA 11
#define L_VBBUCH_BEMERKUNGEN 240
#define L_VBBUCH_KURZBEZKONDI 6
#define L_VBBUCH_PRODUSERQUOTA 6

/* Length/Count-Define of VBBUCH **********************************************/

#define LS_VBBUCH_ARTIKEL_NR 10 + 1
#define LS_VBBUCH_FILIALNR 5 + 1
#define LS_VBBUCH_DARREICHFORM 3 + 1
#define LS_VBBUCH_EINHEIT 9 + 1
#define LS_VBBUCH_BESTAND 10 + 1
#define LS_VBBUCH_ARTIKEL_NAME 30 + 1
#define LS_VBBUCH_MENGEBESTELLT 10 + 1
#define LS_VBBUCH_MENGEBESTAETIGT 10 + 1
#define LS_VBBUCH_MENGENATRA 10 + 1
#define LS_VBBUCH_BEMERKUNGEN 240 + 1
#define LS_VBBUCH_KURZBEZKONDI 6 + 1
#define LS_VBBUCH_PRODUSERQUOTA 5 + 1

#define VBBUCHARTIKEL_NR 0
#define VBBUCHFILIALNR 1
#define VBBUCHDARREICHFORM 2
#define VBBUCHEINHEIT 3
#define VBBUCHBESTAND 4
#define VBBUCHARTIKEL_NAME 5
#define VBBUCHMENGEBESTELLT 6
#define VBBUCHMENGEBESTAETIGT 7
#define VBBUCHMENGENATRA 8
#define VBBUCHBEMERKUNGEN 9
#define VBBUCHKURZBEZKONDI 10
#define VBBUCHPRODUSERQUOTA 11

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define VBBUCH_H
#define VBBUCH_ANZ ( sizeof(VBBUCH_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of VBBUCH ********************************************************/

#define VBBUCH_LISTE \
        ARTIKEL.ARTIKEL_NR,\
        ARTIKELLAGERORT.FILIALNR,\
        ARTIKEL.DARREICHFORM,\
        ARTIKEL.EINHEIT,\
        ARTIKELLAGERORT.BESTAND,\
        ARTIKEL.ARTIKEL_NAME,\
        KDAUFTRAGPOS.MENGEBESTELLT,\
        KDAUFTRAGPOS.MENGEBESTAETIGT,\
        KDAUFTRAGPOS.MENGENATRA,\
        KDAUFTRAGPOS.BEMERKUNGEN,\
        AADUMMY.KURZBEZKONDI,\
        ARTIKELZENTRAL.PRODUSERQUOTA
#define VBBUCH_LISTE_390 \
        ARTIKEL_NR,\
        FILIALNR,\
        DARREICHFORM,\
        EINHEIT,\
        BESTAND,\
        ARTIKEL_NAME,\
        MENGEBESTELLT,\
        MENGEBESTAETIGT,\
        MENGENATRA,\
        BEMERKUNGEN,\
        KURZBEZKONDI,\
        PRODUSERQUOTA
#define VBBUCH_PLISTE \
        "ARTIKEL.ARTIKEL_NR,"\
        "ARTIKELLAGERORT.FILIALNR,"\
        "ARTIKEL.DARREICHFORM,"\
        "ARTIKEL.EINHEIT,"\
        "ARTIKELLAGERORT.BESTAND,"\
        "ARTIKEL.ARTIKEL_NAME,"\
        "KDAUFTRAGPOS.MENGEBESTELLT,"\
        "KDAUFTRAGPOS.MENGEBESTAETIGT,"\
        "KDAUFTRAGPOS.MENGENATRA,"\
        "KDAUFTRAGPOS.BEMERKUNGEN,"\
        "AADUMMY.KURZBEZKONDI,"\
        "ARTIKELZENTRAL.PRODUSERQUOTA"
#define VBBUCH_PELISTE \
        "ARTIKEL_NR,"\
        "FILIALNR,"\
        "DARREICHFORM,"\
        "EINHEIT,"\
        "BESTAND,"\
        "ARTIKEL_NAME,"\
        "MENGEBESTELLT,"\
        "MENGEBESTAETIGT,"\
        "MENGENATRA,"\
        "BEMERKUNGEN,"\
        "KURZBEZKONDI,"\
        "PRODUSERQUOTA"
#define VBBUCH_UPDLISTE \
        "ARTIKEL_NR=?,"\
        "FILIALNR=?,"\
        "DARREICHFORM=?,"\
        "EINHEIT=?,"\
        "BESTAND=?,"\
        "ARTIKEL_NAME=?,"\
        "MENGEBESTELLT=?,"\
        "MENGEBESTAETIGT=?,"\
        "MENGENATRA=?,"\
        "BEMERKUNGEN=?,"\
        "KURZBEZKONDI=?,"\
        "PRODUSERQUOTA=?"
/* SqlMacros-Define of VBBUCH *************************************************/

#define VBBUCH_ZEIGER(x) \
        :x->ARTIKEL_NR,\
        :x->FILIALNR,\
        :x->DARREICHFORM,\
        :x->EINHEIT,\
        :x->BESTAND,\
        :x->ARTIKEL_NAME,\
        :x->MENGEBESTELLT,\
        :x->MENGEBESTAETIGT,\
        :x->MENGENATRA,\
        :x->BEMERKUNGEN,\
        :x->KURZBEZKONDI,\
        :x->PRODUSERQUOTA
#define VBBUCH_ZEIGERSEL(x) \
        :x->ARTIKEL_NR,\
        :x->FILIALNR,\
        :x->DARREICHFORM,\
        :x->EINHEIT,\
        :x->BESTAND,\
        :x->ARTIKEL_NAME,\
        :x->MENGEBESTELLT,\
        :x->MENGEBESTAETIGT,\
        :x->MENGENATRA,\
        :x->BEMERKUNGEN,\
        :x->KURZBEZKONDI,\
        :x->PRODUSERQUOTA
#define VBBUCH_UPDATE(x) \
        ARTIKEL.ARTIKEL_NR=:x->ARTIKEL_NR,\
        ARTIKELLAGERORT.FILIALNR=:x->FILIALNR,\
        ARTIKEL.DARREICHFORM=:x->DARREICHFORM,\
        ARTIKEL.EINHEIT=:x->EINHEIT,\
        ARTIKELLAGERORT.BESTAND=:x->BESTAND,\
        ARTIKEL.ARTIKEL_NAME=:x->ARTIKEL_NAME,\
        KDAUFTRAGPOS.MENGEBESTELLT=:x->MENGEBESTELLT,\
        KDAUFTRAGPOS.MENGEBESTAETIGT=:x->MENGEBESTAETIGT,\
        KDAUFTRAGPOS.MENGENATRA=:x->MENGENATRA,\
        KDAUFTRAGPOS.BEMERKUNGEN=:x->BEMERKUNGEN,\
        AADUMMY.KURZBEZKONDI=:x->KURZBEZKONDI,\
        ARTIKELZENTRAL.PRODUSERQUOTA=:x->PRODUSERQUOTA
/* SqlMacros390-Define of VBBUCH **********************************************/

#define VBBUCH_ZEIGER_390 \
        :ARTIKEL_NR,\
        :FILIALNR,\
        :DARREICHFORM,\
        :EINHEIT,\
        :BESTAND,\
        :ARTIKEL_NAME,\
        :MENGEBESTELLT,\
        :MENGEBESTAETIGT,\
        :MENGENATRA,\
        :BEMERKUNGEN,\
        :KURZBEZKONDI,\
        :PRODUSERQUOTA
#define VBBUCH_UPDATE_390 \
        ARTIKEL_NR=:ARTIKEL_NR,\
        FILIALNR=:FILIALNR,\
        DARREICHFORM=:DARREICHFORM,\
        EINHEIT=:EINHEIT,\
        BESTAND=:BESTAND,\
        ARTIKEL_NAME=:ARTIKEL_NAME,\
        MENGEBESTELLT=:MENGEBESTELLT,\
        MENGEBESTAETIGT=:MENGEBESTAETIGT,\
        MENGENATRA=:MENGENATRA,\
        BEMERKUNGEN=:BEMERKUNGEN,\
        KURZBEZKONDI=:KURZBEZKONDI,\
        PRODUSERQUOTA=:PRODUSERQUOTA
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of VBBUCH **************************************************/

#ifndef TRANSCLASS
typedef struct N_VBBUCH {
    long ARTIKEL_NR;
    short FILIALNR;
    char DARREICHFORM[4];
    char EINHEIT[10];
    long BESTAND;
    char ARTIKEL_NAME[31];
    long MENGEBESTELLT;
    long MENGEBESTAETIGT;
    long MENGENATRA;
    char BEMERKUNGEN[241];
    char KURZBEZKONDI[7];
    short PRODUSERQUOTA;
    long FETCH_REL;
} vbbuchS;
#else /* TRANSCLASS */
typedef struct N_VBBUCH {
    long ARTIKEL_NR;
    short FILIALNR;
    char DARREICHFORM[4];
    char EINHEIT[10];
    long BESTAND;
    char ARTIKEL_NAME[31];
    long MENGEBESTELLT;
    long MENGEBESTAETIGT;
    long MENGENATRA;
    char BEMERKUNGEN[241];
    char KURZBEZKONDI[7];
    short PRODUSERQUOTA;
    long FETCH_REL;
    bool operator == (const N_VBBUCH& right) const {
        return (
            ARTIKEL_NR == right.ARTIKEL_NR &&
            FILIALNR == right.FILIALNR &&
            !strcmp(DARREICHFORM, right.DARREICHFORM) &&
            !strcmp(EINHEIT, right.EINHEIT) &&
            BESTAND == right.BESTAND &&
            !strcmp(ARTIKEL_NAME, right.ARTIKEL_NAME) &&
            MENGEBESTELLT == right.MENGEBESTELLT &&
            MENGEBESTAETIGT == right.MENGEBESTAETIGT &&
            MENGENATRA == right.MENGENATRA &&
            !strcmp(BEMERKUNGEN, right.BEMERKUNGEN) &&
            !strcmp(KURZBEZKONDI, right.KURZBEZKONDI) &&
            PRODUSERQUOTA == right.PRODUSERQUOTA
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        ARTIKEL_NR = 0;
        FILIALNR = 0;
        strcpy(DARREICHFORM, " " );
        strcpy(EINHEIT, " " );
        BESTAND = 0;
        strcpy(ARTIKEL_NAME, " " );
        MENGEBESTELLT = 0;
        MENGEBESTAETIGT = 0;
        MENGENATRA = 0;
        strcpy(BEMERKUNGEN, " " );
        strcpy(KURZBEZKONDI, " " );
        PRODUSERQUOTA = 0;
#endif
    }
} vbbuchS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of VBBUCH ********************************************/

struct S_VBBUCH {
    char ARTIKEL_NR[11];
    char FILIALNR[7];
    char DARREICHFORM[3 + 1];
    char EINHEIT[9 + 1];
    char BESTAND[11];
    char ARTIKEL_NAME[30 + 1];
    char MENGEBESTELLT[11];
    char MENGEBESTAETIGT[11];
    char MENGENATRA[11];
    char BEMERKUNGEN[240 + 1];
    char KURZBEZKONDI[6 + 1];
    char PRODUSERQUOTA[7];
    char FETCH_REL[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of VBBUCH ***************************/

struct O_VBBUCH {
    char ARTIKEL_NR[11];
    char FILIALNR[7];
    char DARREICHFORM[3];
    char EINHEIT[9];
    char BESTAND[11];
    char ARTIKEL_NAME[30];
    char MENGEBESTELLT[11];
    char MENGEBESTAETIGT[11];
    char MENGENATRA[11];
    char BEMERKUNGEN[240];
    char KURZBEZKONDI[6];
    char PRODUSERQUOTA[7];
    char FETCH_REL[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of VBBUCH **************************************/

struct C_VBBUCH {
    long ARTIKEL_NR;
    short FILIALNR;
    char DARREICHFORM[4];
    char EINHEIT[10];
    long BESTAND;
    char ARTIKEL_NAME[31];
    long MENGEBESTELLT;
    long MENGEBESTAETIGT;
    long MENGENATRA;
    char BEMERKUNGEN[241];
    char KURZBEZKONDI[7];
    short PRODUSERQUOTA;
    long FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of VBBUCH ************************************/

struct I_VBBUCH {
    short ARTIKEL_NR;
    short FILIALNR;
    short DARREICHFORM;
    short EINHEIT;
    short BESTAND;
    short ARTIKEL_NAME;
    short MENGEBESTELLT;
    short MENGEBESTAETIGT;
    short MENGENATRA;
    short BEMERKUNGEN;
    short KURZBEZKONDI;
    short PRODUSERQUOTA;
    short FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of VBBUCH **********************************************/

#if defined (BUF_DESC)
static struct buf_desc VBBUCH_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 3, 0 },
   { TYP_C, 9, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 240, 0 },
   { TYP_C, 6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc VBBUCH_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 3, 0 },
   { TYP_C, 9, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 240, 0 },
   { TYP_C, 6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* description for datatypes of VBBUCH ****************************************/

 #define VBBUCH_S390 \
         long ARTIKEL_NR; \
         short FILIALNR; \
         char DARREICHFORM[4]; \
         char EINHEIT[10]; \
         long BESTAND; \
         char ARTIKEL_NAME[31]; \
         long MENGEBESTELLT; \
         long MENGEBESTAETIGT; \
         long MENGENATRA; \
         char BEMERKUNGEN[241]; \
         char KURZBEZKONDI[7]; \
         short PRODUSERQUOTA; \
         long FETCH_REL;



/* Copy-Function Struct to single Data VBBUCH *********************************/

 #define VBBUCH_S390_COPY_TO_SINGLE(_x_) \
         ARTIKEL_NR=_x_->ARTIKEL_NR;\
         FILIALNR=_x_->FILIALNR;\
          strcpy(DARREICHFORM,_x_->DARREICHFORM);\
          strcpy(EINHEIT,_x_->EINHEIT);\
         BESTAND=_x_->BESTAND;\
          strcpy(ARTIKEL_NAME,_x_->ARTIKEL_NAME);\
         MENGEBESTELLT=_x_->MENGEBESTELLT;\
         MENGEBESTAETIGT=_x_->MENGEBESTAETIGT;\
         MENGENATRA=_x_->MENGENATRA;\
          strcpy(BEMERKUNGEN,_x_->BEMERKUNGEN);\
          strcpy(KURZBEZKONDI,_x_->KURZBEZKONDI);\
         PRODUSERQUOTA=_x_->PRODUSERQUOTA;\
          FETCH_REL=_x_->FETCH_REL;\

 #define VBBUCH_S390_COPY_TO_STRUCT(_x_) \
          _x_->ARTIKEL_NR=ARTIKEL_NR;\
          _x_->FILIALNR=FILIALNR;\
          strcpy(_x_->DARREICHFORM,DARREICHFORM);\
          strcpy(_x_->EINHEIT,EINHEIT);\
          _x_->BESTAND=BESTAND;\
          strcpy(_x_->ARTIKEL_NAME,ARTIKEL_NAME);\
          _x_->MENGEBESTELLT=MENGEBESTELLT;\
          _x_->MENGEBESTAETIGT=MENGEBESTAETIGT;\
          _x_->MENGENATRA=MENGENATRA;\
          strcpy(_x_->BEMERKUNGEN,BEMERKUNGEN);\
          strcpy(_x_->KURZBEZKONDI,KURZBEZKONDI);\
          _x_->PRODUSERQUOTA=PRODUSERQUOTA;\
          _x_->FETCH_REL=FETCH_REL;\



/* FunctionNumber-Define of VBBUCH ********************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of VBBUCH ****************************************/


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

class CVBBUCH : public ppDadeVirtual {
public:
    vbbuchS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<vbbuchS> lst; // class list

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
                     vector< vbbuchS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     vbbuchS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< vbbuchS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<vbbuchS>::iterator
                 beginList() { return lst.begin(); }
    vector<vbbuchS>::iterator
                 endList  () { return lst.end  (); }

    long         GetArtikel_nr() const { return s.ARTIKEL_NR; }
    short        GetFilialnr() const { return s.FILIALNR; }
    const char*  GetDarreichform(ppString & t) const { t = s.DARREICHFORM; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetEinheit(ppString & t) const { t = s.EINHEIT; t.erasespace(ppString::END); return t.c_str(); }
    long         GetBestand() const { return s.BESTAND; }
    const char*  GetArtikel_name(ppString & t) const { t = s.ARTIKEL_NAME; t.erasespace(ppString::END); return t.c_str(); }
    long         GetMengebestellt() const { return s.MENGEBESTELLT; }
    long         GetMengebestaetigt() const { return s.MENGEBESTAETIGT; }
    long         GetMengenatra() const { return s.MENGENATRA; }
    const char*  GetBemerkungen(ppString & t) const { t = s.BEMERKUNGEN; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetKurzbezkondi(ppString & t) const { t = s.KURZBEZKONDI; t.erasespace(ppString::END); return t.c_str(); }
    short        GetProduserquota() const { return s.PRODUSERQUOTA; }

    const vbbuchS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetArtikel_nr(long t) { s.ARTIKEL_NR = t; }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetDarreichform(const ppString & t) { ppGStrCopy(s.DARREICHFORM, t.c_str(), L_VBBUCH_DARREICHFORM); }
    void         SetEinheit(const ppString & t) { ppGStrCopy(s.EINHEIT, t.c_str(), L_VBBUCH_EINHEIT); }
    void         SetBestand(long t) { s.BESTAND = t; }
    void         SetArtikel_name(const ppString & t) { ppGStrCopy(s.ARTIKEL_NAME, t.c_str(), L_VBBUCH_ARTIKEL_NAME); }
    void         SetMengebestellt(long t) { s.MENGEBESTELLT = t; }
    void         SetMengebestaetigt(long t) { s.MENGEBESTAETIGT = t; }
    void         SetMengenatra(long t) { s.MENGENATRA = t; }
    void         SetBemerkungen(const ppString & t) { ppGStrCopy(s.BEMERKUNGEN, t.c_str(), L_VBBUCH_BEMERKUNGEN); }
    void         SetKurzbezkondi(const ppString & t) { ppGStrCopy(s.KURZBEZKONDI, t.c_str(), L_VBBUCH_KURZBEZKONDI); }
    void         SetProduserquota(short t) { s.PRODUSERQUOTA = t; }

    void         SetStruct(const vbbuchS & t) { s = t; }
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
    CVBBUCH() {
        ::buf_default((void *)&s, VBBUCH_BES, VBBUCH_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CVBBUCH() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, VBBUCH_BES, VBBUCH_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, VBBUCH_BES, (int)VBBUCH_ANZ, error_msg);
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
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, VBBUCH_BES, (int)VBBUCH_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, VBBUCH_BES, (int)VBBUCH_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_VBBUCH & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.DARREICHFORM);
        ppGStripLast(d.EINHEIT);
        ppGStripLast(d.ARTIKEL_NAME);
        ppGStripLast(d.BEMERKUNGEN);
        ppGStripLast(d.KURZBEZKONDI);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, VBBUCH_BES, (int)VBBUCH_ANZ, error_msg);
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
        CVBBUCH c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, VBBUCH_BES, (int)VBBUCH_ANZ, error_msg);
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
/* CreateSqlStatement of VBBUCH ***********************************************/

 #define VBBUCH_CREATE(x) EXEC SQL create table x (\
         ARTIKEL_NR integer default 0 not null,\
         FILIALNR smallint default 0 not null,\
         DARREICHFORM char(3) default " " not null,\
         EINHEIT char(9) default " " not null,\
         BESTAND integer default 0 not null,\
         ARTIKEL_NAME char(30) default " " not null,\
         MENGEBESTELLT integer default 0 not null,\
         MENGEBESTAETIGT integer default 0 not null,\
         MENGENATRA integer default 0 not null,\
         BEMERKUNGEN varchar(240,0) default " " not null,\
         KURZBEZKONDI char(6) default " " not null,\
         PRODUSERQUOTA smallint default 0 not null) extent size 2744 next size 276 lock mode row;



/* CreateIndexStatement of VBBUCH *********************************************/

 #define VBBUCH_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_artikel_1 on _X_(\
              artikel_nr );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index i_artikel_2 on _X_(\
              artikel_mc );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of VBBUCH *********************************************/

 #define VBBUCH_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_artikel_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_artikel_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
