#ifndef __PP_KDAUFTRAGPOSEREIGNIS_H_
#define __PP_KDAUFTRAGPOSEREIGNIS_H_

/******************************************************************************/
/* y:\kdauftragposereignis ****************************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of KDAUFTRAGPOSEREIGNIS **************************************/

#define L_KDAUFTRAGPOSEREIGNIS_DATUM 11
#define L_KDAUFTRAGPOSEREIGNIS_KDAUFTRAGNR 11
#define L_KDAUFTRAGPOSEREIGNIS_SENDID 11
#define L_KDAUFTRAGPOSEREIGNIS_POSEREIGNISART 6
#define L_KDAUFTRAGPOSEREIGNIS_POSNR 11
#define L_KDAUFTRAGPOSEREIGNIS_UHRZEIT 11

/* Length/Count-Define of KDAUFTRAGPOSEREIGNIS ********************************/

#define LS_KDAUFTRAGPOSEREIGNIS_DATUM 10 + 1
#define LS_KDAUFTRAGPOSEREIGNIS_KDAUFTRAGNR 10 + 1
#define LS_KDAUFTRAGPOSEREIGNIS_SENDID 10 + 1
#define LS_KDAUFTRAGPOSEREIGNIS_POSEREIGNISART 5 + 1
#define LS_KDAUFTRAGPOSEREIGNIS_POSNR 10 + 1
#define LS_KDAUFTRAGPOSEREIGNIS_UHRZEIT 10 + 1

#define KDAUFTRAGPOSEREIGNISDATUM 0
#define KDAUFTRAGPOSEREIGNISKDAUFTRAGNR 1
#define KDAUFTRAGPOSEREIGNISSENDID 2
#define KDAUFTRAGPOSEREIGNISPOSEREIGNISART 3
#define KDAUFTRAGPOSEREIGNISPOSNR 4
#define KDAUFTRAGPOSEREIGNISUHRZEIT 5

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define KDAUFTRAGPOSEREIGNIS_H
#define KDAUFTRAGPOSEREIGNIS_ANZ ( sizeof(KDAUFTRAGPOSEREIGNIS_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of KDAUFTRAGPOSEREIGNIS ******************************************/

#define KDAUFTRAGPOSEREIGNIS_LISTE \
        KDAUFTRAGPOSEREIGNIS.DATUM,\
        KDAUFTRAGPOSEREIGNIS.KDAUFTRAGNR,\
        KDAUFTRAGPOSEREIGNIS.SENDID,\
        KDAUFTRAGPOSEREIGNIS.POSEREIGNISART,\
        KDAUFTRAGPOSEREIGNIS.POSNR,\
        KDAUFTRAGPOSEREIGNIS.UHRZEIT
#define KDAUFTRAGPOSEREIGNIS_LISTE_390 \
        DATUM,\
        KDAUFTRAGNR,\
        SENDID,\
        POSEREIGNISART,\
        POSNR,\
        UHRZEIT
#define KDAUFTRAGPOSEREIGNIS_PLISTE \
        "KDAUFTRAGPOSEREIGNIS.DATUM,"\
        "KDAUFTRAGPOSEREIGNIS.KDAUFTRAGNR,"\
        "KDAUFTRAGPOSEREIGNIS.SENDID,"\
        "KDAUFTRAGPOSEREIGNIS.POSEREIGNISART,"\
        "KDAUFTRAGPOSEREIGNIS.POSNR,"\
        "KDAUFTRAGPOSEREIGNIS.UHRZEIT"
#define KDAUFTRAGPOSEREIGNIS_PELISTE \
        "DATUM,"\
        "KDAUFTRAGNR,"\
        "SENDID,"\
        "POSEREIGNISART,"\
        "POSNR,"\
        "UHRZEIT"
#define KDAUFTRAGPOSEREIGNIS_UPDLISTE \
        "DATUM=?,"\
        "KDAUFTRAGNR=?,"\
        "SENDID=?,"\
        "POSEREIGNISART=?,"\
        "POSNR=?,"\
        "UHRZEIT=?"
/* SqlMacros-Define of KDAUFTRAGPOSEREIGNIS ***********************************/

#define KDAUFTRAGPOSEREIGNIS_ZEIGER(x) \
        :x->DATUM,\
        :x->KDAUFTRAGNR,\
        :x->SENDID,\
        :x->POSEREIGNISART,\
        :x->POSNR,\
        :x->UHRZEIT
#define KDAUFTRAGPOSEREIGNIS_ZEIGERSEL(x) \
        :x->DATUM,\
        :x->KDAUFTRAGNR,\
        :x->SENDID,\
        :x->POSEREIGNISART,\
        :x->POSNR,\
        :x->UHRZEIT
#define KDAUFTRAGPOSEREIGNIS_UPDATE(x) \
        KDAUFTRAGPOSEREIGNIS.DATUM=:x->DATUM,\
        KDAUFTRAGPOSEREIGNIS.KDAUFTRAGNR=:x->KDAUFTRAGNR,\
        KDAUFTRAGPOSEREIGNIS.SENDID=:x->SENDID,\
        KDAUFTRAGPOSEREIGNIS.POSEREIGNISART=:x->POSEREIGNISART,\
        KDAUFTRAGPOSEREIGNIS.POSNR=:x->POSNR,\
        KDAUFTRAGPOSEREIGNIS.UHRZEIT=:x->UHRZEIT
/* SqlMacros390-Define of KDAUFTRAGPOSEREIGNIS ********************************/

#define KDAUFTRAGPOSEREIGNIS_ZEIGER_390 \
        :DATUM,\
        :KDAUFTRAGNR,\
        :SENDID,\
        :POSEREIGNISART,\
        :POSNR,\
        :UHRZEIT
#define KDAUFTRAGPOSEREIGNIS_UPDATE_390 \
        DATUM=:DATUM,\
        KDAUFTRAGNR=:KDAUFTRAGNR,\
        SENDID=:SENDID,\
        POSEREIGNISART=:POSEREIGNISART,\
        POSNR=:POSNR,\
        UHRZEIT=:UHRZEIT
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of KDAUFTRAGPOSEREIGNIS ************************************/

#ifndef TRANSCLASS
typedef struct N_KDAUFTRAGPOSEREIGNIS {
    long DATUM;
    long KDAUFTRAGNR;
    long SENDID;
    short POSEREIGNISART;
    long POSNR;
    long UHRZEIT;
} kdauftragposereignisS;
#else /* TRANSCLASS */
typedef struct N_KDAUFTRAGPOSEREIGNIS {
    long DATUM;
    long KDAUFTRAGNR;
    long SENDID;
    short POSEREIGNISART;
    long POSNR;
    long UHRZEIT;

    bool operator == (const N_KDAUFTRAGPOSEREIGNIS& right) const {
        return (
            DATUM == right.DATUM &&
            KDAUFTRAGNR == right.KDAUFTRAGNR &&
            SENDID == right.SENDID &&
            POSEREIGNISART == right.POSEREIGNISART &&
            POSNR == right.POSNR &&
            UHRZEIT == right.UHRZEIT
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        DATUM = 0;
        KDAUFTRAGNR = 0;
        SENDID = 0;
        POSEREIGNISART = 0;
        POSNR = 0;
        UHRZEIT = 0;
#endif
    }
} kdauftragposereignisS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of KDAUFTRAGPOSEREIGNIS ******************************/

struct S_KDAUFTRAGPOSEREIGNIS {
    char DATUM[11];
    char KDAUFTRAGNR[11];
    char SENDID[11];
    char POSEREIGNISART[7];
    char POSNR[11];
    char UHRZEIT[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of KDAUFTRAGPOSEREIGNIS *************/

struct O_KDAUFTRAGPOSEREIGNIS {
    char DATUM[11];
    char KDAUFTRAGNR[11];
    char SENDID[11];
    char POSEREIGNISART[7];
    char POSNR[11];
    char UHRZEIT[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of KDAUFTRAGPOSEREIGNIS ************************/

struct C_KDAUFTRAGPOSEREIGNIS {
    long DATUM;
    long KDAUFTRAGNR;
    long SENDID;
    short POSEREIGNISART;
    long POSNR;
    long UHRZEIT;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of KDAUFTRAGPOSEREIGNIS **********************/

struct I_KDAUFTRAGPOSEREIGNIS {
    short DATUM;
    short KDAUFTRAGNR;
    short SENDID;
    short POSEREIGNISART;
    short POSNR;
    short UHRZEIT;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of KDAUFTRAGPOSEREIGNIS ********************************/

#if defined (BUF_DESC)
static struct buf_desc KDAUFTRAGPOSEREIGNIS_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc KDAUFTRAGPOSEREIGNIS_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* description for datatypes of KDAUFTRAGPOSEREIGNIS **************************/

 #define KDAUFTRAGPOSEREIGNIS_S390 \
         long DATUM; \
         long KDAUFTRAGNR; \
         long SENDID; \
         short POSEREIGNISART; \
         long POSNR; \
         long UHRZEIT; \



/* Copy-Function Struct to single Data KDAUFTRAGPOSEREIGNIS *******************/

 #define KDAUFTRAGPOSEREIGNIS_S390_COPY_TO_SINGLE(_x_) \
         DATUM=_x_->DATUM;\
         KDAUFTRAGNR=_x_->KDAUFTRAGNR;\
         SENDID=_x_->SENDID;\
         POSEREIGNISART=_x_->POSEREIGNISART;\
         POSNR=_x_->POSNR;\
         UHRZEIT=_x_->UHRZEIT;\

 #define KDAUFTRAGPOSEREIGNIS_S390_COPY_TO_STRUCT(_x_) \
          _x_->DATUM=DATUM;\
          _x_->KDAUFTRAGNR=KDAUFTRAGNR;\
          _x_->SENDID=SENDID;\
          _x_->POSEREIGNISART=POSEREIGNISART;\
          _x_->POSNR=POSNR;\
          _x_->UHRZEIT=UHRZEIT;\



/* FunctionNumber-Define of kdauftragposereignis ******************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of kdauftragposereignis **************************/


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

class CKDAUFTRAGPOSEREIGNIS : public ppDadeVirtual {
public:
    kdauftragposereignisS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<kdauftragposereignisS> lst; // class list

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
                     vector< kdauftragposereignisS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     kdauftragposereignisS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< kdauftragposereignisS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<kdauftragposereignisS>::iterator
                 beginList() { return lst.begin(); }
    vector<kdauftragposereignisS>::iterator
                 endList  () { return lst.end  (); }

    long         GetDatum() const { return s.DATUM; }
    long         GetKdauftragnr() const { return s.KDAUFTRAGNR; }
    long         GetSendid() const { return s.SENDID; }
    short        GetPosereignisart() const { return s.POSEREIGNISART; }
    long         GetPosnr() const { return s.POSNR; }
    long         GetUhrzeit() const { return s.UHRZEIT; }

    const kdauftragposereignisS &
                 GetStruct() const { return s; }
    void         SetDatum(long t) { s.DATUM = t; }
    void         SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
    void         SetSendid(long t) { s.SENDID = t; }
    void         SetPosereignisart(short t) { s.POSEREIGNISART = t; }
    void         SetPosnr(long t) { s.POSNR = t; }
    void         SetUhrzeit(long t) { s.UHRZEIT = t; }

    void         SetStruct(const kdauftragposereignisS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CKDAUFTRAGPOSEREIGNIS() {
        ::buf_default((void *)&s, KDAUFTRAGPOSEREIGNIS_BES, KDAUFTRAGPOSEREIGNIS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CKDAUFTRAGPOSEREIGNIS() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, KDAUFTRAGPOSEREIGNIS_BES, KDAUFTRAGPOSEREIGNIS_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, KDAUFTRAGPOSEREIGNIS_BES, (int)KDAUFTRAGPOSEREIGNIS_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, KDAUFTRAGPOSEREIGNIS_BES, (int)KDAUFTRAGPOSEREIGNIS_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_KDAUFTRAGPOSEREIGNIS & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, KDAUFTRAGPOSEREIGNIS_BES, (int)KDAUFTRAGPOSEREIGNIS_ANZ, error_msg);
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
/* CreateSqlStatement of KDAUFTRAGPOSEREIGNIS *********************************/

 #define KDAUFTRAGPOSEREIGNIS_CREATE(x) EXEC SQL create table x (\
         DATUM integer default 0 not null,\
         KDAUFTRAGNR integer default 0 not null,\
         SENDID integer default 0 not null,\
         POSEREIGNISART smallint default 0 not null,\
         POSNR integer default 0 not null,\
         UHRZEIT integer default 0 not null) in ksc extent size 21960 next size 2196 lock mode row;



/* CreateIndexStatement of KDAUFTRAGPOSEREIGNIS *******************************/

 #define KDAUFTRAGPOSEREIGNIS_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_kdauftragposereignis_1 on _X_(\
              datum,\
              kdauftragnr,\
              PosEreignisArt,\
              posnr,\
              uhrzeit ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of KDAUFTRAGPOSEREIGNIS *******************************/

 #define KDAUFTRAGPOSEREIGNIS_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_kdauftragposereignis_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
