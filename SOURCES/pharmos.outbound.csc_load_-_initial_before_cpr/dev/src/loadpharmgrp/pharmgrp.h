#ifndef __PP_PHARMGRP_H_
#define __PP_PHARMGRP_H_

/******************************************************************************/
/* c:\Marathon\orderentry\csc_load\dev\src\loadpharmgrp\PharmGrp **************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <pplib/bufkon.h>

/* Length-Define of PHARMGRP **************************************************/

#define L_PHARMGRP_PHARMACYGROUPID 3
#define L_PHARMGRP_GROUP_NAME 30
#define L_PHARMGRP_GROUP_TYPE 1
#define L_PHARMGRP_PERCENT 5
#define N_PHARMGRP_PERCENT 2
#define L_PHARMGRP_CONTRIBUTION 3
#define N_PHARMGRP_CONTRIBUTION 2
#define L_PHARMGRP_CUSTOMERNO 11
#define L_PHARMGRP_OMG_OWN_CONT 1
#define L_PHARMGRP_PRICE_BASIS_PURCH 1
#define L_PHARMGRP_RECLAIM_OMG_DISC 1
#define L_PHARMGRP_SPECIALGROUP 6
#define L_PHARMGRP_SPECIALGROUPREFNO 11
#define L_PHARMGRP_GROUPING_VIS 6

/* Length/Count-Define of PHARMGRP ********************************************/

#define LS_PHARMGRP_PHARMACYGROUPID 3 + 1
#define LS_PHARMGRP_GROUP_NAME 30 + 1
#define LS_PHARMGRP_GROUP_TYPE 1 + 1
#define LS_PHARMGRP_PERCENT 5 + 2
#define LS_PHARMGRP_CONTRIBUTION 3 + 2
#define LS_PHARMGRP_CUSTOMERNO 10 + 1
#define LS_PHARMGRP_OMG_OWN_CONT 1 + 1
#define LS_PHARMGRP_PRICE_BASIS_PURCH 1 + 1
#define LS_PHARMGRP_RECLAIM_OMG_DISC 1 + 1
#define LS_PHARMGRP_SPECIALGROUP 5 + 1
#define LS_PHARMGRP_SPECIALGROUPREFNO 10 + 1
#define LS_PHARMGRP_GROUPING_VIS 5 + 1

#define PHARMGRPPHARMACYGROUPID 0
#define PHARMGRPGROUP_NAME 1
#define PHARMGRPGROUP_TYPE 2
#define PHARMGRPPERCENT 3
#define PHARMGRPCONTRIBUTION 4
#define PHARMGRPCUSTOMERNO 5
#define PHARMGRPOMG_OWN_CONT 6
#define PHARMGRPPRICE_BASIS_PURCH 7
#define PHARMGRPRECLAIM_OMG_DISC 8
#define PHARMGRPSPECIALGROUP 9
#define PHARMGRPSPECIALGROUPREFNO 10
#define PHARMGRPGROUPING_VIS 11

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define PHARMGRP_H
#define PHARMGRP_ANZ ( sizeof(PHARMGRP_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of PHARMGRP ******************************************************/

#define PHARMGRP_LISTE \
        PHARMACYGROUPS.PHARMACYGROUPID,\
        PHARMACYGROUPS.GROUP_NAME,\
        PHARMACYGROUPS.GROUP_TYPE,\
        PHARMACYGROUPS.PERCENT,\
        PHARMACYGROUPS.CONTRIBUTION,\
        PHARMACYGROUPS.CUSTOMERNO,\
        PHARMACYGROUPS.OMG_OWN_CONT,\
        PHARMACYGROUPS.PRICE_BASIS_PURCH,\
        PHARMACYGROUPS.RECLAIM_OMG_DISC,\
        PHARMACYGROUPS.SPECIALGROUP,\
        PHARMACYGROUPS.SPECIALGROUPREFNO,\
        PHARMACYGROUPS.GROUPING_VIS
#define PHARMGRP_LISTE_390 \
        PHARMACYGROUPID,\
        GROUP_NAME,\
        GROUP_TYPE,\
        PERCENT,\
        CONTRIBUTION,\
        CUSTOMERNO,\
        OMG_OWN_CONT,\
        PRICE_BASIS_PURCH,\
        RECLAIM_OMG_DISC,\
        SPECIALGROUP,\
        SPECIALGROUPREFNO,\
        GROUPING_VIS
#define PHARMGRP_PLISTE \
        "PHARMACYGROUPS.PHARMACYGROUPID,"\
        "PHARMACYGROUPS.GROUP_NAME,"\
        "PHARMACYGROUPS.GROUP_TYPE,"\
        "PHARMACYGROUPS.PERCENT,"\
        "PHARMACYGROUPS.CONTRIBUTION,"\
        "PHARMACYGROUPS.CUSTOMERNO,"\
        "PHARMACYGROUPS.OMG_OWN_CONT,"\
        "PHARMACYGROUPS.PRICE_BASIS_PURCH,"\
        "PHARMACYGROUPS.RECLAIM_OMG_DISC,"\
        "PHARMACYGROUPS.SPECIALGROUP,"\
        "PHARMACYGROUPS.SPECIALGROUPREFNO,"\
        "PHARMACYGROUPS.GROUPING_VIS"
#define PHARMGRP_PELISTE \
        "PHARMACYGROUPID,"\
        "GROUP_NAME,"\
        "GROUP_TYPE,"\
        "PERCENT,"\
        "CONTRIBUTION,"\
        "CUSTOMERNO,"\
        "OMG_OWN_CONT,"\
        "PRICE_BASIS_PURCH,"\
        "RECLAIM_OMG_DISC,"\
        "SPECIALGROUP,"\
        "SPECIALGROUPREFNO,"\
        "GROUPING_VIS"
#define PHARMGRP_UPDLISTE \
        "PHARMACYGROUPID=?,"\
        "GROUP_NAME=?,"\
        "GROUP_TYPE=?,"\
        "PERCENT=?,"\
        "CONTRIBUTION=?,"\
        "CUSTOMERNO=?,"\
        "OMG_OWN_CONT=?,"\
        "PRICE_BASIS_PURCH=?,"\
        "RECLAIM_OMG_DISC=?,"\
        "SPECIALGROUP=?,"\
        "SPECIALGROUPREFNO=?,"\
        "GROUPING_VIS=?"
/* SqlMacros-Define of PHARMGRP ***********************************************/

#define PHARMGRP_ZEIGER(x) \
        :x->PHARMACYGROUPID,\
        :x->GROUP_NAME,\
        :x->GROUP_TYPE,\
        :x->PERCENT,\
        :x->CONTRIBUTION,\
        :x->CUSTOMERNO,\
        :x->OMG_OWN_CONT,\
        :x->PRICE_BASIS_PURCH,\
        :x->RECLAIM_OMG_DISC,\
        :x->SPECIALGROUP,\
        :x->SPECIALGROUPREFNO,\
        :x->GROUPING_VIS
#define PHARMGRP_ZEIGERSEL(x) \
        :x->PHARMACYGROUPID,\
        :x->GROUP_NAME,\
        :x->GROUP_TYPE,\
        :x->PERCENT,\
        :x->CONTRIBUTION,\
        :x->CUSTOMERNO,\
        :x->OMG_OWN_CONT,\
        :x->PRICE_BASIS_PURCH,\
        :x->RECLAIM_OMG_DISC,\
        :x->SPECIALGROUP,\
        :x->SPECIALGROUPREFNO,\
        :x->GROUPING_VIS
#define PHARMGRP_UPDATE(x) \
        PHARMACYGROUPS.PHARMACYGROUPID=:x->PHARMACYGROUPID,\
        PHARMACYGROUPS.GROUP_NAME=:x->GROUP_NAME,\
        PHARMACYGROUPS.GROUP_TYPE=:x->GROUP_TYPE,\
        PHARMACYGROUPS.PERCENT=:x->PERCENT,\
        PHARMACYGROUPS.CONTRIBUTION=:x->CONTRIBUTION,\
        PHARMACYGROUPS.CUSTOMERNO=:x->CUSTOMERNO,\
        PHARMACYGROUPS.OMG_OWN_CONT=:x->OMG_OWN_CONT,\
        PHARMACYGROUPS.PRICE_BASIS_PURCH=:x->PRICE_BASIS_PURCH,\
        PHARMACYGROUPS.RECLAIM_OMG_DISC=:x->RECLAIM_OMG_DISC,\
        PHARMACYGROUPS.SPECIALGROUP=:x->SPECIALGROUP,\
        PHARMACYGROUPS.SPECIALGROUPREFNO=:x->SPECIALGROUPREFNO,\
        PHARMACYGROUPS.GROUPING_VIS=:x->GROUPING_VIS
/* SqlMacros390-Define of PHARMGRP ********************************************/

#define PHARMGRP_ZEIGER_390 \
        :PHARMACYGROUPID,\
        :GROUP_NAME,\
        :GROUP_TYPE,\
        :PERCENT,\
        :CONTRIBUTION,\
        :CUSTOMERNO,\
        :OMG_OWN_CONT,\
        :PRICE_BASIS_PURCH,\
        :RECLAIM_OMG_DISC,\
        :SPECIALGROUP,\
        :SPECIALGROUPREFNO,\
        :GROUPING_VIS
#define PHARMGRP_UPDATE_390 \
        PHARMACYGROUPID=:PHARMACYGROUPID,\
        GROUP_NAME=:GROUP_NAME,\
        GROUP_TYPE=:GROUP_TYPE,\
        PERCENT=:PERCENT,\
        CONTRIBUTION=:CONTRIBUTION,\
        CUSTOMERNO=:CUSTOMERNO,\
        OMG_OWN_CONT=:OMG_OWN_CONT,\
        PRICE_BASIS_PURCH=:PRICE_BASIS_PURCH,\
        RECLAIM_OMG_DISC=:RECLAIM_OMG_DISC,\
        SPECIALGROUP=:SPECIALGROUP,\
        SPECIALGROUPREFNO=:SPECIALGROUPREFNO,\
        GROUPING_VIS=:GROUPING_VIS
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of PHARMGRP ************************************************/

#ifndef TRANSCLASS
typedef struct N_PHARMGRP {
    char PHARMACYGROUPID[4];
    char GROUP_NAME[31];
    char GROUP_TYPE[2];
    double PERCENT;
    double CONTRIBUTION;
    long CUSTOMERNO;
    char OMG_OWN_CONT[2];
    char PRICE_BASIS_PURCH[2];
    char RECLAIM_OMG_DISC[2];
    short SPECIALGROUP;
    long SPECIALGROUPREFNO;
    short GROUPING_VIS;
} pharmgrpS;
#else /* TRANSCLASS */
typedef struct N_PHARMGRP {
    char PHARMACYGROUPID[4];
    char GROUP_NAME[31];
    char GROUP_TYPE[2];
    double PERCENT;
    double CONTRIBUTION;
    long CUSTOMERNO;
    char OMG_OWN_CONT[2];
    char PRICE_BASIS_PURCH[2];
    char RECLAIM_OMG_DISC[2];
    short SPECIALGROUP;
    long SPECIALGROUPREFNO;
    short GROUPING_VIS;

    bool operator == (const N_PHARMGRP& right) const {
        return (
            !strcmp(PHARMACYGROUPID, right.PHARMACYGROUPID) &&
            !strcmp(GROUP_NAME, right.GROUP_NAME) &&
            !strcmp(GROUP_TYPE, right.GROUP_TYPE) &&
            PERCENT == right.PERCENT &&
            CONTRIBUTION == right.CONTRIBUTION &&
            CUSTOMERNO == right.CUSTOMERNO &&
            !strcmp(OMG_OWN_CONT, right.OMG_OWN_CONT) &&
            !strcmp(PRICE_BASIS_PURCH, right.PRICE_BASIS_PURCH) &&
            !strcmp(RECLAIM_OMG_DISC, right.RECLAIM_OMG_DISC) &&
            SPECIALGROUP == right.SPECIALGROUP &&
            SPECIALGROUPREFNO == right.SPECIALGROUPREFNO &&
            GROUPING_VIS == right.GROUPING_VIS
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        strcpy(PHARMACYGROUPID, " " );
        strcpy(GROUP_NAME, " " );
        strcpy(GROUP_TYPE, " " );
        PERCENT = 0;
        CONTRIBUTION = 0;
        CUSTOMERNO = 0;
        strcpy(OMG_OWN_CONT, " " );
        strcpy(PRICE_BASIS_PURCH, " " );
        strcpy(RECLAIM_OMG_DISC, " " );
        SPECIALGROUP = 0;
        SPECIALGROUPREFNO = 0;
        GROUPING_VIS = 0;
#endif
    }
} pharmgrpS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of PHARMGRP ******************************************/

struct S_PHARMGRP {
    char PHARMACYGROUPID[3 + 1];
    char GROUP_NAME[30 + 1];
    char GROUP_TYPE[1 + 1];
    char PERCENT[5 + 2];
    char CONTRIBUTION[3 + 2];
    char CUSTOMERNO[11];
    char OMG_OWN_CONT[1 + 1];
    char PRICE_BASIS_PURCH[1 + 1];
    char RECLAIM_OMG_DISC[1 + 1];
    char SPECIALGROUP[7];
    char SPECIALGROUPREFNO[11];
    char GROUPING_VIS[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of PHARMGRP *************************/

struct O_PHARMGRP {
    char PHARMACYGROUPID[3];
    char GROUP_NAME[30];
    char GROUP_TYPE[1];
    char PERCENT[5];
    char CONTRIBUTION[3];
    char CUSTOMERNO[11];
    char OMG_OWN_CONT[1];
    char PRICE_BASIS_PURCH[1];
    char RECLAIM_OMG_DISC[1];
    char SPECIALGROUP[7];
    char SPECIALGROUPREFNO[11];
    char GROUPING_VIS[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of PHARMGRP ************************************/

struct C_PHARMGRP {
    char PHARMACYGROUPID[4];
    char GROUP_NAME[31];
    char GROUP_TYPE;
    double PERCENT;
    double CONTRIBUTION;
    long CUSTOMERNO;
    char OMG_OWN_CONT;
    char PRICE_BASIS_PURCH;
    char RECLAIM_OMG_DISC;
    short SPECIALGROUP;
    long SPECIALGROUPREFNO;
    short GROUPING_VIS;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of PHARMGRP **********************************/

struct I_PHARMGRP {
    short PHARMACYGROUPID;
    short GROUP_NAME;
    short GROUP_TYPE;
    short PERCENT;
    short CONTRIBUTION;
    short CUSTOMERNO;
    short OMG_OWN_CONT;
    short PRICE_BASIS_PURCH;
    short RECLAIM_OMG_DISC;
    short SPECIALGROUP;
    short SPECIALGROUPREFNO;
    short GROUPING_VIS;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of PHARMGRP ********************************************/

#if defined (BUF_DESC)
static struct buf_desc PHARMGRP_BES [] = {
   { TYP_C, 3, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 1, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 3, 2 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc PHARMGRP_BES [] = {
   { TYP_C, 3, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 1, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 3, 2 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* description for datatypes of PHARMGRP **************************************/

 #define PHARMGRP_S390 \
         char PHARMACYGROUPID[4]; \
         char GROUP_NAME[31]; \
         char GROUP_TYPE; \
         double PERCENT; \
         double CONTRIBUTION; \
         long CUSTOMERNO; \
         char OMG_OWN_CONT; \
         char PRICE_BASIS_PURCH; \
         char RECLAIM_OMG_DISC; \
         short SPECIALGROUP; \
         long SPECIALGROUPREFNO; \
         short GROUPING_VIS; \



/* Copy-Function Struct to single Data PHARMGRP *******************************/

 #define PHARMGRP_S390_COPY_TO_SINGLE(_x_) \
          strcpy(PHARMACYGROUPID,_x_->PHARMACYGROUPID);\
          strcpy(GROUP_NAME,_x_->GROUP_NAME);\
         GROUP_TYPE=_x_->GROUP_TYPE;\
         PERCENT=_x_->PERCENT;\
         CONTRIBUTION=_x_->CONTRIBUTION;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
         OMG_OWN_CONT=_x_->OMG_OWN_CONT;\
         PRICE_BASIS_PURCH=_x_->PRICE_BASIS_PURCH;\
         RECLAIM_OMG_DISC=_x_->RECLAIM_OMG_DISC;\
         SPECIALGROUP=_x_->SPECIALGROUP;\
         SPECIALGROUPREFNO=_x_->SPECIALGROUPREFNO;\
         GROUPING_VIS=_x_->GROUPING_VIS;\

 #define PHARMGRP_S390_COPY_TO_STRUCT(_x_) \
          strcpy(_x_->PHARMACYGROUPID,PHARMACYGROUPID);\
          strcpy(_x_->GROUP_NAME,GROUP_NAME);\
          _x_->GROUP_TYPE=GROUP_TYPE;\
          _x_->PERCENT=PERCENT;\
          _x_->CONTRIBUTION=CONTRIBUTION;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->OMG_OWN_CONT=OMG_OWN_CONT;\
          _x_->PRICE_BASIS_PURCH=PRICE_BASIS_PURCH;\
          _x_->RECLAIM_OMG_DISC=RECLAIM_OMG_DISC;\
          _x_->SPECIALGROUP=SPECIALGROUP;\
          _x_->SPECIALGROUPREFNO=SPECIALGROUPREFNO;\
          _x_->GROUPING_VIS=GROUPING_VIS;\



/* FunctionNumber-Define of PharmGrp ******************************************/

#define PHARMGRP_SEL 1442

#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of PharmGrp **************************************/

#define Sel 1442

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

class CPHARMGRP : public ppDadeVirtual {
public:
    pharmgrpS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<pharmgrpS> lst; // class list

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
                     vector< pharmgrpS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     pharmgrpS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< pharmgrpS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<pharmgrpS>::iterator
                 beginList() { return lst.begin(); }
    vector<pharmgrpS>::iterator
                 endList  () { return lst.end  (); }

    const char*  GetPharmacygroupid(ppString & t) const { t = s.PHARMACYGROUPID; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetGroup_name(ppString & t) const { t = s.GROUP_NAME; t.erasespace(ppString::END); return t.c_str(); }
    char         GetGroup_type() const { return s.GROUP_TYPE[0]; }
    double       GetPercent() const { return s.PERCENT; }
    double       GetContribution() const { return s.CONTRIBUTION; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    char         GetOmg_own_cont() const { return s.OMG_OWN_CONT[0]; }
    char         GetPrice_basis_purch() const { return s.PRICE_BASIS_PURCH[0]; }
    char         GetReclaim_omg_disc() const { return s.RECLAIM_OMG_DISC[0]; }
    short        GetSpecialgroup() const { return s.SPECIALGROUP; }
    long         GetSpecialgrouprefno() const { return s.SPECIALGROUPREFNO; }
    short        GetGrouping_vis() const { return s.GROUPING_VIS; }

    const pharmgrpS &
                 GetStruct() const { return s; }
    void         SetPharmacygroupid(const ppString & t) { ppGStrCopy(s.PHARMACYGROUPID, t.c_str(), L_PHARMGRP_PHARMACYGROUPID); }
    void         SetGroup_name(const ppString & t) { ppGStrCopy(s.GROUP_NAME, t.c_str(), L_PHARMGRP_GROUP_NAME); }
    void         SetGroup_type(char t) { s.GROUP_TYPE[0] = t; s.GROUP_TYPE[1] = '\0';}
    void         SetPercent(double t) { s.PERCENT = t; }
    void         SetContribution(double t) { s.CONTRIBUTION = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetOmg_own_cont(char t) { s.OMG_OWN_CONT[0] = t; s.OMG_OWN_CONT[1] = '\0';}
    void         SetPrice_basis_purch(char t) { s.PRICE_BASIS_PURCH[0] = t; s.PRICE_BASIS_PURCH[1] = '\0';}
    void         SetReclaim_omg_disc(char t) { s.RECLAIM_OMG_DISC[0] = t; s.RECLAIM_OMG_DISC[1] = '\0';}
    void         SetSpecialgroup(short t) { s.SPECIALGROUP = t; }
    void         SetSpecialgrouprefno(long t) { s.SPECIALGROUPREFNO = t; }
    void         SetGrouping_vis(short t) { s.GROUPING_VIS = t; }

    void         SetStruct(const pharmgrpS & t) { s = t; }

    int          Sel(int pos = 0) { int ret = UniqueServerCall(1442, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CPHARMGRP() {
        ::buf_default((void *)&s, PHARMGRP_BES, PHARMGRP_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CPHARMGRP() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, PHARMGRP_BES, PHARMGRP_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1442 ) return UniqueServerCall(1442, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_PHARMGRP & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.PHARMACYGROUPID);
        ppGStripLast(d.GROUP_NAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, PHARMGRP_BES, (int)PHARMGRP_ANZ, error_msg);
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
/* CreateSqlStatement of PHARMGRP *********************************************/

 #define PHARMGRP_CREATE(x) EXEC SQL create table x (\
         PHARMACYGROUPID char(3) default " " not null,\
         GROUP_NAME char(30) default " " not null,\
         GROUP_TYPE char(1) default " " not null,\
         PERCENT decimal(5,2) default 0 not null,\
         CONTRIBUTION decimal(3,2) default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         OMG_OWN_CONT char(1) default " " not null,\
         PRICE_BASIS_PURCH char(1) default " " not null,\
         RECLAIM_OMG_DISC char(1) default " " not null,\
         SPECIALGROUP smallint default 0 not null,\
         SPECIALGROUPREFNO integer default 0 not null,\
         GROUPING_VIS smallint default 0 not null) extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of PHARMGRP *******************************************/

 #define PHARMGRP_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_pharmgrp_1 on _X_(\
              PharmacyGroupId );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of PHARMGRP *******************************************/

 #define PHARMGRP_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_pharmgrp_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
