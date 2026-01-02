#ifndef __PP_ARTICLEQUOTA_H_
#define __PP_ARTICLEQUOTA_H_

/******************************************************************************/
/* v:\articlequota ************************************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of ARTICLEQUOTA **********************************************/

#define L_ARTICLEQUOTA_BRANCHNO 6
#define L_ARTICLEQUOTA_CUSTOMERNO 11
#define L_ARTICLEQUOTA_ARTICLENO 11
#define L_ARTICLEQUOTA_QUOTA 11
#define L_ARTICLEQUOTA_KUMQTY 11
#define L_ARTICLEQUOTA_VALIDITY 1
#define L_ARTICLEQUOTA_SDAFUEQUOTA 1
#define L_ARTICLEQUOTA_DATEFROM 11
#define L_ARTICLEQUOTA_DATETO 11
#define L_ARTICLEQUOTA_PHARMACYGROUPID 3

/* Length/Count-Define of ARTICLEQUOTA ****************************************/

#define LS_ARTICLEQUOTA_BRANCHNO 5 + 1
#define LS_ARTICLEQUOTA_CUSTOMERNO 10 + 1
#define LS_ARTICLEQUOTA_ARTICLENO 10 + 1
#define LS_ARTICLEQUOTA_QUOTA 10 + 1
#define LS_ARTICLEQUOTA_KUMQTY 10 + 1
#define LS_ARTICLEQUOTA_VALIDITY 1 + 1
#define LS_ARTICLEQUOTA_SDAFUEQUOTA 1 + 1
#define LS_ARTICLEQUOTA_DATEFROM 10 + 1
#define LS_ARTICLEQUOTA_DATETO 10 + 1
#define LS_ARTICLEQUOTA_PHARMACYGROUPID 3 + 1

#define ARTICLEQUOTABRANCHNO 0
#define ARTICLEQUOTACUSTOMERNO 1
#define ARTICLEQUOTAARTICLENO 2
#define ARTICLEQUOTAQUOTA 3
#define ARTICLEQUOTAKUMQTY 4
#define ARTICLEQUOTAVALIDITY 5
#define ARTICLEQUOTASDAFUEQUOTA 6
#define ARTICLEQUOTADATEFROM 7
#define ARTICLEQUOTADATETO 8
#define ARTICLEQUOTAPHARMACYGROUPID 9

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define ARTICLEQUOTA_H
#define ARTICLEQUOTA_ANZ ( sizeof(ARTICLEQUOTA_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ARTICLEQUOTA **************************************************/

#define ARTICLEQUOTA_LISTE \
        ARTICLEQUOTA.BRANCHNO,\
        ARTICLEQUOTA.CUSTOMERNO,\
        ARTICLEQUOTA.ARTICLENO,\
        ARTICLEQUOTA.QUOTA,\
        ARTICLEQUOTA.KUMQTY,\
        ARTICLEQUOTA.VALIDITY,\
        ARTICLEQUOTA.SDAFUEQUOTA,\
        ARTICLEQUOTA.DATEFROM,\
        ARTICLEQUOTA.DATETO,\
        ARTICLEQUOTA.PHARMACYGROUPID
#define ARTICLEQUOTA_LISTE_390 \
        BRANCHNO,\
        CUSTOMERNO,\
        ARTICLENO,\
        QUOTA,\
        KUMQTY,\
        VALIDITY,\
        SDAFUEQUOTA,\
        DATEFROM,\
        DATETO,\
        PHARMACYGROUPID
#define ARTICLEQUOTA_PLISTE \
        "ARTICLEQUOTA.BRANCHNO,"\
        "ARTICLEQUOTA.CUSTOMERNO,"\
        "ARTICLEQUOTA.ARTICLENO,"\
        "ARTICLEQUOTA.QUOTA,"\
        "ARTICLEQUOTA.KUMQTY,"\
        "ARTICLEQUOTA.VALIDITY,"\
        "ARTICLEQUOTA.SDAFUEQUOTA,"\
        "ARTICLEQUOTA.DATEFROM,"\
        "ARTICLEQUOTA.DATETO,"\
        "ARTICLEQUOTA.PHARMACYGROUPID"
#define ARTICLEQUOTA_PELISTE \
        "BRANCHNO,"\
        "CUSTOMERNO,"\
        "ARTICLENO,"\
        "QUOTA,"\
        "KUMQTY,"\
        "VALIDITY,"\
        "SDAFUEQUOTA,"\
        "DATEFROM,"\
        "DATETO,"\
        "PHARMACYGROUPID"
#define ARTICLEQUOTA_UPDLISTE \
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "ARTICLENO=?,"\
        "QUOTA=?,"\
        "KUMQTY=?,"\
        "VALIDITY=?,"\
        "SDAFUEQUOTA=?,"\
        "DATEFROM=?,"\
        "DATETO=?,"\
        "PHARMACYGROUPID=?"
/* SqlMacros-Define of ARTICLEQUOTA *******************************************/

#define ARTICLEQUOTA_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->ARTICLENO,\
        :x->QUOTA,\
        :x->KUMQTY,\
        :x->VALIDITY,\
        :x->SDAFUEQUOTA,\
        :x->DATEFROM,\
        :x->DATETO,\
        :x->PHARMACYGROUPID
#define ARTICLEQUOTA_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->ARTICLENO,\
        :x->QUOTA,\
        :x->KUMQTY,\
        :x->VALIDITY,\
        :x->SDAFUEQUOTA,\
        :x->DATEFROM,\
        :x->DATETO,\
        :x->PHARMACYGROUPID
#define ARTICLEQUOTA_UPDATE(x) \
        ARTICLEQUOTA.BRANCHNO=:x->BRANCHNO,\
        ARTICLEQUOTA.CUSTOMERNO=:x->CUSTOMERNO,\
        ARTICLEQUOTA.ARTICLENO=:x->ARTICLENO,\
        ARTICLEQUOTA.QUOTA=:x->QUOTA,\
        ARTICLEQUOTA.KUMQTY=:x->KUMQTY,\
        ARTICLEQUOTA.VALIDITY=:x->VALIDITY,\
        ARTICLEQUOTA.SDAFUEQUOTA=:x->SDAFUEQUOTA,\
        ARTICLEQUOTA.DATEFROM=:x->DATEFROM,\
        ARTICLEQUOTA.DATETO=:x->DATETO,\
        ARTICLEQUOTA.PHARMACYGROUPID=:x->PHARMACYGROUPID
/* SqlMacros390-Define of ARTICLEQUOTA ****************************************/

#define ARTICLEQUOTA_ZEIGER_390 \
        :BRANCHNO,\
        :CUSTOMERNO,\
        :ARTICLENO,\
        :QUOTA,\
        :KUMQTY,\
        :VALIDITY,\
        :SDAFUEQUOTA,\
        :DATEFROM,\
        :DATETO,\
        :PHARMACYGROUPID
#define ARTICLEQUOTA_UPDATE_390 \
        BRANCHNO=:BRANCHNO,\
        CUSTOMERNO=:CUSTOMERNO,\
        ARTICLENO=:ARTICLENO,\
        QUOTA=:QUOTA,\
        KUMQTY=:KUMQTY,\
        VALIDITY=:VALIDITY,\
        SDAFUEQUOTA=:SDAFUEQUOTA,\
        DATEFROM=:DATEFROM,\
        DATETO=:DATETO,\
        PHARMACYGROUPID=:PHARMACYGROUPID
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of ARTICLEQUOTA ********************************************/

#ifndef TRANSCLASS
typedef struct N_ARTICLEQUOTA {
    short BRANCHNO;
    long CUSTOMERNO;
    long ARTICLENO;
    long QUOTA;
    long KUMQTY;
    char VALIDITY[2];
    char SDAFUEQUOTA[2];
    long DATEFROM;
    long DATETO;
    char PHARMACYGROUPID[4];
} articlequotaS;
#else /* TRANSCLASS */
typedef struct N_ARTICLEQUOTA {
    short BRANCHNO;
    long CUSTOMERNO;
    long ARTICLENO;
    long QUOTA;
    long KUMQTY;
    char VALIDITY[2];
    char SDAFUEQUOTA[2];
    long DATEFROM;
    long DATETO;
    char PHARMACYGROUPID[4];

    bool operator == (const N_ARTICLEQUOTA& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            CUSTOMERNO == right.CUSTOMERNO &&
            ARTICLENO == right.ARTICLENO &&
            QUOTA == right.QUOTA &&
            KUMQTY == right.KUMQTY &&
            !strcmp(VALIDITY, right.VALIDITY) &&
            !strcmp(SDAFUEQUOTA, right.SDAFUEQUOTA) &&
            DATEFROM == right.DATEFROM &&
            DATETO == right.DATETO &&
            !strcmp(PHARMACYGROUPID, right.PHARMACYGROUPID)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        CUSTOMERNO = 0;
        ARTICLENO = 0;
        QUOTA = 0;
        KUMQTY = 0;
        strcpy(VALIDITY, " " );
        strcpy(SDAFUEQUOTA, " " );
        DATEFROM = 0;
        DATETO = 0;
        strcpy(PHARMACYGROUPID, " " );
#endif
    }
} articlequotaS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ARTICLEQUOTA **************************************/

struct S_ARTICLEQUOTA {
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char ARTICLENO[11];
    char QUOTA[11];
    char KUMQTY[11];
    char VALIDITY[1 + 1];
    char SDAFUEQUOTA[1 + 1];
    char DATEFROM[11];
    char DATETO[11];
    char PHARMACYGROUPID[3 + 1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ARTICLEQUOTA *********************/

struct O_ARTICLEQUOTA {
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char ARTICLENO[11];
    char QUOTA[11];
    char KUMQTY[11];
    char VALIDITY[1];
    char SDAFUEQUOTA[1];
    char DATEFROM[11];
    char DATETO[11];
    char PHARMACYGROUPID[3];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ARTICLEQUOTA ********************************/

struct C_ARTICLEQUOTA {
    short BRANCHNO;
    long CUSTOMERNO;
    long ARTICLENO;
    long QUOTA;
    long KUMQTY;
    char VALIDITY;
    char SDAFUEQUOTA;
    long DATEFROM;
    long DATETO;
    char PHARMACYGROUPID[4];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ARTICLEQUOTA ******************************/

struct I_ARTICLEQUOTA {
    short BRANCHNO;
    short CUSTOMERNO;
    short ARTICLENO;
    short QUOTA;
    short KUMQTY;
    short VALIDITY;
    short SDAFUEQUOTA;
    short DATEFROM;
    short DATETO;
    short PHARMACYGROUPID;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ARTICLEQUOTA ****************************************/

#if defined (BUF_DESC)
static struct buf_desc ARTICLEQUOTA_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 3, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc ARTICLEQUOTA_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 3, 0 },
};
#endif

/* description for datatypes of ARTICLEQUOTA **********************************/

 #define ARTICLEQUOTA_S390 \
         short BRANCHNO; \
         long CUSTOMERNO; \
         long ARTICLENO; \
         long QUOTA; \
         long KUMQTY; \
         char VALIDITY; \
         char SDAFUEQUOTA; \
         long DATEFROM; \
         long DATETO; \
         char PHARMACYGROUPID[4]; \



/* Copy-Function Struct to single Data ARTICLEQUOTA ***************************/

 #define ARTICLEQUOTA_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
         ARTICLENO=_x_->ARTICLENO;\
         QUOTA=_x_->QUOTA;\
         KUMQTY=_x_->KUMQTY;\
         VALIDITY=_x_->VALIDITY;\
         SDAFUEQUOTA=_x_->SDAFUEQUOTA;\
         DATEFROM=_x_->DATEFROM;\
         DATETO=_x_->DATETO;\
          strcpy(PHARMACYGROUPID,_x_->PHARMACYGROUPID);\

 #define ARTICLEQUOTA_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->ARTICLENO=ARTICLENO;\
          _x_->QUOTA=QUOTA;\
          _x_->KUMQTY=KUMQTY;\
          _x_->VALIDITY=VALIDITY;\
          _x_->SDAFUEQUOTA=SDAFUEQUOTA;\
          _x_->DATEFROM=DATEFROM;\
          _x_->DATETO=DATETO;\
          strcpy(_x_->PHARMACYGROUPID,PHARMACYGROUPID);\



/* FunctionNumber-Define of articlequota **************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of articlequota **********************************/


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

class CARTICLEQUOTA : public ppDadeVirtual {
public:
    articlequotaS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<articlequotaS> lst; // class list

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
                     vector< articlequotaS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     articlequotaS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< articlequotaS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<articlequotaS>::iterator
                 beginList() { return lst.begin(); }
    vector<articlequotaS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    long         GetArticleno() const { return s.ARTICLENO; }
    long         GetQuota() const { return s.QUOTA; }
    long         GetKumqty() const { return s.KUMQTY; }
    char         GetValidity() const { return s.VALIDITY[0]; }
    char         GetSdafuequota() const { return s.SDAFUEQUOTA[0]; }
    long         GetDatefrom() const { return s.DATEFROM; }
    long         GetDateto() const { return s.DATETO; }
    const char*  GetPharmacygroupid(ppString & t) const { t = s.PHARMACYGROUPID; t.erasespace(ppString::END); return t.c_str(); }

    const articlequotaS &
                 GetStruct() const { return s; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetArticleno(long t) { s.ARTICLENO = t; }
    void         SetQuota(long t) { s.QUOTA = t; }
    void         SetKumqty(long t) { s.KUMQTY = t; }
    void         SetValidity(char t) { s.VALIDITY[0] = t; s.VALIDITY[1] = '\0';}
    void         SetSdafuequota(char t) { s.SDAFUEQUOTA[0] = t; s.SDAFUEQUOTA[1] = '\0';}
    void         SetDatefrom(long t) { s.DATEFROM = t; }
    void         SetDateto(long t) { s.DATETO = t; }
    void         SetPharmacygroupid(const ppString & t) { ppGStrCopy(s.PHARMACYGROUPID, t.c_str(), L_ARTICLEQUOTA_PHARMACYGROUPID); }

    void         SetStruct(const articlequotaS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CARTICLEQUOTA() {
        ::buf_default((void *)&s, ARTICLEQUOTA_BES, ARTICLEQUOTA_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CARTICLEQUOTA() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, ARTICLEQUOTA_BES, ARTICLEQUOTA_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, ARTICLEQUOTA_BES, (int)ARTICLEQUOTA_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, ARTICLEQUOTA_BES, (int)ARTICLEQUOTA_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_ARTICLEQUOTA & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.PHARMACYGROUPID);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, ARTICLEQUOTA_BES, (int)ARTICLEQUOTA_ANZ, error_msg);
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
/* CreateSqlStatement of ARTICLEQUOTA *****************************************/

 #define ARTICLEQUOTA_CREATE(x) EXEC SQL create table x (\
         BRANCHNO smallint default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         ARTICLENO integer default 0 not null,\
         QUOTA integer default 0 not null,\
         KUMQTY integer default 0 not null,\
         VALIDITY char(1) default " " not null,\
         SDAFUEQUOTA char(1) default " " not null,\
         DATEFROM integer default 0 not null,\
         DATETO integer default 0 not null,\
         PHARMACYGROUPID char(3) default " " not null) in ksc extent size 1568 next size 160 lock mode row;



/* CreateIndexStatement of ARTICLEQUOTA ***************************************/

 #define ARTICLEQUOTA_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_Artquota_1 on _X_(\
              BranchNo,\
              CustomerNo,\
              ArticleNo,\
              PharmacyGroupId,\
              Validity ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index i_Artquota_2 on _X_(\
              BranchNo,\
              ArticleNo,\
              PharmacyGroupId ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ARTICLEQUOTA ***************************************/

 #define ARTICLEQUOTA_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_Artquota_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_Artquota_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
