#ifndef __PP_SEPORDERARTGRP_H_
#define __PP_SEPORDERARTGRP_H_

/******************************************************************************/
/* w:\seporderartgrp **********************************************************/
/* produced by DADE 6.21.6 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of SEPORDERARTGRP ********************************************/

#define L_SEPORDERARTGRP_BRANCHNO 6
#define L_SEPORDERARTGRP_ARTGRP 6
#define L_SEPORDERARTGRP_KDAUFTRAGART 2
#define L_SEPORDERARTGRP_KOART 1
#define L_SEPORDERARTGRP_BUCHART 1
#define L_SEPORDERARTGRP_DEFERORDER 1
#define L_SEPORDERARTGRP_MANUFACTURERNO 11

/* Length/Count-Define of SEPORDERARTGRP **************************************/

#define LS_SEPORDERARTGRP_BRANCHNO 5 + 1
#define LS_SEPORDERARTGRP_ARTGRP 5 + 1
#define LS_SEPORDERARTGRP_KDAUFTRAGART 2 + 1
#define LS_SEPORDERARTGRP_KOART 1 + 1
#define LS_SEPORDERARTGRP_BUCHART 1 + 1
#define LS_SEPORDERARTGRP_DEFERORDER 1 + 1
#define LS_SEPORDERARTGRP_MANUFACTURERNO 10 + 1

#define SEPORDERARTGRPBRANCHNO 0
#define SEPORDERARTGRPARTGRP 1
#define SEPORDERARTGRPKDAUFTRAGART 2
#define SEPORDERARTGRPKOART 3
#define SEPORDERARTGRPBUCHART 4
#define SEPORDERARTGRPDEFERORDER 5
#define SEPORDERARTGRPMANUFACTURERNO 6

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define SEPORDERARTGRP_H
#define SEPORDERARTGRP_ANZ ( sizeof(SEPORDERARTGRP_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of SEPORDERARTGRP ************************************************/

#define SEPORDERARTGRP_LISTE \
        SEPORDERARTGRP.BRANCHNO,\
        SEPORDERARTGRP.ARTGRP,\
        SEPORDERARTGRP.KDAUFTRAGART,\
        SEPORDERARTGRP.KOART,\
        SEPORDERARTGRP.BUCHART,\
        SEPORDERARTGRP.DEFERORDER,\
        SEPORDERARTGRP.MANUFACTURERNO
#define SEPORDERARTGRP_LISTE_390 \
        BRANCHNO,\
        ARTGRP,\
        KDAUFTRAGART,\
        KOART,\
        BUCHART,\
        DEFERORDER,\
        MANUFACTURERNO
#define SEPORDERARTGRP_PLISTE \
        "SEPORDERARTGRP.BRANCHNO,"\
        "SEPORDERARTGRP.ARTGRP,"\
        "SEPORDERARTGRP.KDAUFTRAGART,"\
        "SEPORDERARTGRP.KOART,"\
        "SEPORDERARTGRP.BUCHART,"\
        "SEPORDERARTGRP.DEFERORDER,"\
        "SEPORDERARTGRP.MANUFACTURERNO"
#define SEPORDERARTGRP_PELISTE \
        "BRANCHNO,"\
        "ARTGRP,"\
        "KDAUFTRAGART,"\
        "KOART,"\
        "BUCHART,"\
        "DEFERORDER,"\
        "MANUFACTURERNO"
#define SEPORDERARTGRP_UPDLISTE \
        "BRANCHNO=?,"\
        "ARTGRP=?,"\
        "KDAUFTRAGART=?,"\
        "KOART=?,"\
        "BUCHART=?,"\
        "DEFERORDER=?,"\
        "MANUFACTURERNO=?"
/* SqlMacros-Define of SEPORDERARTGRP *****************************************/

#define SEPORDERARTGRP_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->ARTGRP,\
        :x->KDAUFTRAGART,\
        :x->KOART,\
        :x->BUCHART,\
        :x->DEFERORDER,\
        :x->MANUFACTURERNO
#define SEPORDERARTGRP_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->ARTGRP,\
        :x->KDAUFTRAGART,\
        :x->KOART,\
        :x->BUCHART,\
        :x->DEFERORDER,\
        :x->MANUFACTURERNO
#define SEPORDERARTGRP_UPDATE(x) \
        SEPORDERARTGRP.BRANCHNO=:x->BRANCHNO,\
        SEPORDERARTGRP.ARTGRP=:x->ARTGRP,\
        SEPORDERARTGRP.KDAUFTRAGART=:x->KDAUFTRAGART,\
        SEPORDERARTGRP.KOART=:x->KOART,\
        SEPORDERARTGRP.BUCHART=:x->BUCHART,\
        SEPORDERARTGRP.DEFERORDER=:x->DEFERORDER,\
        SEPORDERARTGRP.MANUFACTURERNO=:x->MANUFACTURERNO
/* SqlMacros390-Define of SEPORDERARTGRP **************************************/

#define SEPORDERARTGRP_ZEIGER_390 \
        :BRANCHNO,\
        :ARTGRP,\
        :KDAUFTRAGART,\
        :KOART,\
        :BUCHART,\
        :DEFERORDER,\
        :MANUFACTURERNO
#define SEPORDERARTGRP_UPDATE_390 \
        BRANCHNO=:BRANCHNO,\
        ARTGRP=:ARTGRP,\
        KDAUFTRAGART=:KDAUFTRAGART,\
        KOART=:KOART,\
        BUCHART=:BUCHART,\
        DEFERORDER=:DEFERORDER,\
        MANUFACTURERNO=:MANUFACTURERNO
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of SEPORDERARTGRP ******************************************/

#ifndef TRANSCLASS
typedef struct N_SEPORDERARTGRP {
    short BRANCHNO;
    short ARTGRP;
    char KDAUFTRAGART[3];
    char KOART[2];
    char BUCHART[2];
    char DEFERORDER[2];
    long MANUFACTURERNO;
} seporderartgrpS;
#else /* TRANSCLASS */
typedef struct N_SEPORDERARTGRP {
    short BRANCHNO;
    short ARTGRP;
    char KDAUFTRAGART[3];
    char KOART[2];
    char BUCHART[2];
    char DEFERORDER[2];
    long MANUFACTURERNO;

    bool operator == (const N_SEPORDERARTGRP& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            ARTGRP == right.ARTGRP &&
            !strcmp(KDAUFTRAGART, right.KDAUFTRAGART) &&
            !strcmp(KOART, right.KOART) &&
            !strcmp(BUCHART, right.BUCHART) &&
            !strcmp(DEFERORDER, right.DEFERORDER) &&
            MANUFACTURERNO == right.MANUFACTURERNO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        ARTGRP = 0;
        strcpy(KDAUFTRAGART, " " );
        strcpy(KOART, " " );
        strcpy(BUCHART, " " );
        strcpy(DEFERORDER, " " );
        MANUFACTURERNO = 0;
#endif
    }
} seporderartgrpS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of SEPORDERARTGRP ************************************/

struct S_SEPORDERARTGRP {
    char BRANCHNO[7];
    char ARTGRP[7];
    char KDAUFTRAGART[2 + 1];
    char KOART[1 + 1];
    char BUCHART[1 + 1];
    char DEFERORDER[1 + 1];
    char MANUFACTURERNO[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of SEPORDERARTGRP *******************/

struct O_SEPORDERARTGRP {
    char BRANCHNO[7];
    char ARTGRP[7];
    char KDAUFTRAGART[2];
    char KOART[1];
    char BUCHART[1];
    char DEFERORDER[1];
    char MANUFACTURERNO[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of SEPORDERARTGRP ******************************/

struct C_SEPORDERARTGRP {
    short BRANCHNO;
    short ARTGRP;
    char KDAUFTRAGART[3];
    char KOART;
    char BUCHART;
    char DEFERORDER;
    long MANUFACTURERNO;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of SEPORDERARTGRP ****************************/

struct I_SEPORDERARTGRP {
    short BRANCHNO;
    short ARTGRP;
    short KDAUFTRAGART;
    short KOART;
    short BUCHART;
    short DEFERORDER;
    short MANUFACTURERNO;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of SEPORDERARTGRP **************************************/

#if defined (BUF_DESC)
static struct buf_desc SEPORDERARTGRP_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc SEPORDERARTGRP_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* description for datatypes of SEPORDERARTGRP ********************************/

 #define SEPORDERARTGRP_S390 \
         short BRANCHNO; \
         short ARTGRP; \
         char KDAUFTRAGART[3]; \
         char KOART; \
         char BUCHART; \
         char DEFERORDER; \
         long MANUFACTURERNO; \



/* Copy-Function Struct to single Data SEPORDERARTGRP *************************/

 #define SEPORDERARTGRP_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         ARTGRP=_x_->ARTGRP;\
          strcpy(KDAUFTRAGART,_x_->KDAUFTRAGART);\
         KOART=_x_->KOART;\
         BUCHART=_x_->BUCHART;\
         DEFERORDER=_x_->DEFERORDER;\
         MANUFACTURERNO=_x_->MANUFACTURERNO;\

 #define SEPORDERARTGRP_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->ARTGRP=ARTGRP;\
          strcpy(_x_->KDAUFTRAGART,KDAUFTRAGART);\
          _x_->KOART=KOART;\
          _x_->BUCHART=BUCHART;\
          _x_->DEFERORDER=DEFERORDER;\
          _x_->MANUFACTURERNO=MANUFACTURERNO;\



/* FunctionNumber-Define of seporderartgrp ************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of seporderartgrp ********************************/


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

class CSEPORDERARTGRP : public ppDadeVirtual {
public:
    seporderartgrpS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<seporderartgrpS> lst; // class list

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
                     vector< seporderartgrpS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     seporderartgrpS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< seporderartgrpS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<seporderartgrpS>::iterator
                 beginList() { return lst.begin(); }
    vector<seporderartgrpS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    short        GetArtgrp() const { return s.ARTGRP; }
    const char*  GetKdauftragart(ppString & t) const { t = s.KDAUFTRAGART; t.erasespace(ppString::END); return t.c_str(); }
    char         GetKoart() const { return s.KOART[0]; }
    char         GetBuchart() const { return s.BUCHART[0]; }
    char         GetDeferorder() const { return s.DEFERORDER[0]; }
    long         GetManufacturerno() const { return s.MANUFACTURERNO; }

    const seporderartgrpS &
                 GetStruct() const { return s; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetArtgrp(short t) { s.ARTGRP = t; }
    void         SetKdauftragart(const ppString & t) { ppGStrCopy(s.KDAUFTRAGART, t.c_str(), L_SEPORDERARTGRP_KDAUFTRAGART); }
    void         SetKoart(char t) { s.KOART[0] = t; s.KOART[1] = '\0';}
    void         SetBuchart(char t) { s.BUCHART[0] = t; s.BUCHART[1] = '\0';}
    void         SetDeferorder(char t) { s.DEFERORDER[0] = t; s.DEFERORDER[1] = '\0';}
    void         SetManufacturerno(long t) { s.MANUFACTURERNO = t; }

    void         SetStruct(const seporderartgrpS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CSEPORDERARTGRP() {
        ::buf_default((void *)&s, SEPORDERARTGRP_BES, SEPORDERARTGRP_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CSEPORDERARTGRP() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, SEPORDERARTGRP_BES, SEPORDERARTGRP_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, SEPORDERARTGRP_BES, (int)SEPORDERARTGRP_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, SEPORDERARTGRP_BES, (int)SEPORDERARTGRP_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_SEPORDERARTGRP & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.KDAUFTRAGART);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, SEPORDERARTGRP_BES, (int)SEPORDERARTGRP_ANZ, error_msg);
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
/* CreateSqlStatement of SEPORDERARTGRP ***************************************/

 #define SEPORDERARTGRP_CREATE(x) EXEC SQL create table x (\
         BRANCHNO smallint default 0 not null,\
         ARTGRP smallint default 0 not null,\
         KDAUFTRAGART char(2) default " " not null,\
         KOART char(1) default " " not null,\
         BUCHART char(1) default " " not null,\
         DEFERORDER char(1) default " " not null,\
         MANUFACTURERNO integer default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of SEPORDERARTGRP *************************************/

 #define SEPORDERARTGRP_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_sepordartgrp_1 on _X_(\
              BranchNo,\
              ArtGrp,\
              manufacturerno ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of SEPORDERARTGRP *************************************/

 #define SEPORDERARTGRP_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_sepordartgrp_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
