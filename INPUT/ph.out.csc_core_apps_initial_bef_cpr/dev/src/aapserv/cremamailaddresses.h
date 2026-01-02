#ifndef __PP_CREMAMAILADDRESSES_H_
#define __PP_CREMAMAILADDRESSES_H_

/******************************************************************************/
/**/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of CREMAEMAILADDRESSES ***************************************/

#define L_CREMAEMAILADDRESSES_ID 11
#define L_CREMAEMAILADDRESSES_EMAILTYPE 6
#define L_CREMAEMAILADDRESSES_SENDGVLMAIL 6
#define L_CREMAEMAILADDRESSES_SMTPUSERGROUPID 11
#define L_CREMAEMAILADDRESSES_SENTTOADDRESS 50
#define L_CREMAEMAILADDRESSES_SMTPEMAILTYPEID 11

/* Length-Define of CREMAEMAILREASONS *****************************************/

#define L_CREMAEMAILREASONS_ID 11
#define L_CREMAEMAILREASONS_THRESHOLDAMOUNT 11
#define N_CREMAEMAILREASONS_THRESHOLDAMOUNT 2
#define L_CREMAEMAILREASONS_TYPE 6
#define L_CREMAEMAILREASONS_DLPERCENTAGE 5
#define N_CREMAEMAILREASONS_DLPERCENTAGE 2
#define L_CREMAEMAILREASONS_BRANCHNO 6

/* SqlDefine of CREMAEMAILADDRESSES *******************************************/


#define CREMAEMAILADDRESSES_PLISTE \
        "SMTPSENDTOEMAILADDRESSES.ID,"\
        "SMTPEMAILTYPE.EMAILTYPE,"\
        "SMTPGVLMAIL.SENDGVLMAIL,"\
        "SMTPEMAILTYPE.SMTPUSERGROUPID,"\
        "SMTPSENDTOEMAILADDRESSES.SENTTOADDRESS,"\
        "SMTPSENDTOEMAILADDRESSES.SMTPEMAILTYPEID"

/* SqlDefine of CREMAEMAILREASONS *********************************************/


#define CREMAEMAILREASONS_PLISTE \
        "SMTPUSERGROUPS.ID,"\
        "AMOUNTFORMAIL.THRESHOLDAMOUNT,"\
        "CREMATYPE.TYPE,"\
        "DEBTLEVELFORMAIL.DLPERCENTAGE,"\
        "SMTPUSERGROUPS.BRANCHNO"

/* SqlDefine of CREMAEMAILADDRESSES *******************************************/


#define CREMAEMAILADDRESSES_UPDLISTE \
        "ID=?,"\
        "EMAILTYPE=?,"\
        "SENDGVLMAIL=?,"\
        "SENTTOADDRESS=?,"\
        "SMTPEMAILTYPEID=?"
/* SqlDefine of CREMAEMAILREASONS *********************************************/


#define CREMAEMAILREASONS_UPDLISTE \
        "ID=?,"\
        "THRESHOLDAMOUNT=?,"\
        "TYPE=?,"\
        "DLPERCENTAGE=?,"\
        "BRANCHNO=?"
/* SqlMacros-Define of CREMAEMAILADDRESSES ************************************/

#define CREMAEMAILADDRESSES_ZEIGER(x) \
        :x->ID,\
        :x->EMAILTYPE,\
        :x->SENDGVLMAIL,\
        :x->SENTTOADDRESS,\
        :x->SMTPEMAILTYPEID
#define CREMAEMAILADDRESSES_ZEIGERSEL(x) \
        :x->ID,\
        :x->EMAILTYPE,\
        :x->SENDGVLMAIL,\
        :x->SMTPUSERGROUPID,\
        :x->SENTTOADDRESS,\
        :x->SMTPEMAILTYPEID

/* SqlMacros-Define of CREMAEMAILREASONS **************************************/

#define CREMAEMAILREASONS_ZEIGER(x) \
        :x->ID,\
        :x->THRESHOLDAMOUNT,\
        :x->TYPE,\
        :x->DLPERCENTAGE,\
        :x->BRANCHNO
#define CREMAEMAILREASONS_ZEIGERSEL(x) \
        :x->ID,\
        :x->THRESHOLDAMOUNT,\
        :x->TYPE,\
        :x->DLPERCENTAGE,\
        :x->BRANCHNO

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define CREMAEMAILADDRESSES_H
#define CREMAEMAILADDRESSES_ANZ ( sizeof(CREMAEMAILADDRESSES_BES) / sizeof(struct buf_desc) )
#define CREMAEMAILREASONS_H
#define CREMAEMAILREASONS_ANZ ( sizeof(CREMAEMAILREASONS_BES) / sizeof(struct buf_desc) )
#endif

#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of CREMAEMAILADDRESSES *************************************/

#ifndef TRANSCLASS
typedef struct N_CREMAEMAILADDRESSES {
    long ID;
    short EMAILTYPE;
    short SENDGVLMAIL;
    long SMTPUSERGROUPID;
    char SENTTOADDRESS[51];
    long SMTPEMAILTYPEID;
    long FETCH_REL;
} cremaemailaddressesS;
#else /* TRANSCLASS */
typedef struct N_CREMAEMAILADDRESSES {
    long ID;
    short EMAILTYPE;
    short SENDGVLMAIL;
    long SMTPUSERGROUPID;
    char SENTTOADDRESS[51];
    long SMTPEMAILTYPEID;
    long FETCH_REL;
    bool operator == (const N_CREMAEMAILADDRESSES& right) const {
        return (
            ID == right.ID &&
            EMAILTYPE == right.EMAILTYPE &&
            SENDGVLMAIL == right.SENDGVLMAIL &&
            SMTPUSERGROUPID == right.SMTPUSERGROUPID &&
            !strcmp(SENTTOADDRESS, right.SENTTOADDRESS) &&
            SMTPEMAILTYPEID == right.SMTPEMAILTYPEID
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        ID = 0;
        EMAILTYPE = 0;
        SENDGVLMAIL = 0;
        SMTPUSERGROUPID = 0;
        strcpy(SENTTOADDRESS, " " );
        SMTPEMAILTYPEID = 0;
#endif
    }
} cremaemailaddressesS;
#endif /* TRANSCLASS */

/* original struct of CREMAEMAILREASONS ***************************************/

#ifndef TRANSCLASS
typedef struct N_CREMAEMAILREASONS {
    long ID;
    double THRESHOLDAMOUNT;
    short TYPE;
    double DLPERCENTAGE;
    short BRANCHNO;
    long FETCH_REL;
} cremaemailreasonsS;
#else /* TRANSCLASS */
typedef struct N_CREMAEMAILREASONS {
    long ID;
    double THRESHOLDAMOUNT;
    short TYPE;
    double DLPERCENTAGE;
    short BRANCHNO;
    long FETCH_REL;
    bool operator == (const N_CREMAEMAILREASONS& right) const {
        return (
            ID == right.ID &&
            THRESHOLDAMOUNT == right.THRESHOLDAMOUNT &&
            TYPE == right.TYPE &&
            DLPERCENTAGE == right.DLPERCENTAGE &&
            BRANCHNO == right.BRANCHNO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        ID = 0;
        THRESHOLDAMOUNT = 0;
        TYPE = 0;
        DLPERCENTAGE = 0;
        BRANCHNO = 0;
#endif
    }
} cremaemailreasonsS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of CREMAEMAILADDRESSES *************************/

struct C_CREMAEMAILADDRESSES {
    long ID;
    short EMAILTYPE;
    short SENDGVLMAIL;
    long SMTPUSERGROUPID;
    char SENTTOADDRESS[51];
    long SMTPEMAILTYPEID;
    long FETCH_REL;
};
/* Structur with real chartype of CREMAEMAILREASONS ***************************/

struct C_CREMAEMAILREASONS {
    long ID;
    double THRESHOLDAMOUNT;
    short TYPE;
    double DLPERCENTAGE;
    short BRANCHNO;
    long FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of CREMAEMAILADDRESSES ***********************/

struct I_CREMAEMAILADDRESSES {
    short ID;
    short EMAILTYPE;
    short SENDGVLMAIL;
    short SMTPUSERGROUPID;
    short SENTTOADDRESS;
    short SMTPEMAILTYPEID;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of CREMAEMAILREASONS *************************/

struct I_CREMAEMAILREASONS {
    short ID;
    short THRESHOLDAMOUNT;
    short TYPE;
    short DLPERCENTAGE;
    short BRANCHNO;
    short FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CREMAEMAILADDRESSES *********************************/

#if defined (BUF_DESC)
static struct buf_desc CREMAEMAILADDRESSES_BES [] = {
   { TYP_L ,  11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 50, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CREMAEMAILADDRESSES_BES [] = {
   { TYP_L ,  11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 50, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of CREMAEMAILREASONS ***********************************/

#if defined (BUF_DESC)
static struct buf_desc CREMAEMAILREASONS_BES [] = {
   { TYP_L ,  11, 0 },
   { TYP_D, 11, 2 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CREMAEMAILREASONS_BES [] = {
   { TYP_L ,  11, 0 },
   { TYP_D, 11, 2 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* FunctionNumber-Define of CremaEmailAddresses *******************************/

#define CREMAEMAILADDRESSES_DELETEADDRESS 1703
#define CREMAEMAILADDRESSES_INSERTADDRESS 1701
#define CREMAEMAILADDRESSES_INSERTGVL 1710
#define CREMAEMAILADDRESSES_INSERTTYPE 1709
#define CREMAEMAILADDRESSES_SELEMAILADDRESSES 1699
#define CREMAEMAILADDRESSES_SELEMAILTYPE 1704
#define CREMAEMAILADDRESSES_UPDATE 1695
#define CREMAEMAILADDRESSES_UPDATEEMAILADDRESS 1708
#define CREMAEMAILADDRESSES_UPDATEGVL 1707

/* FunctionNumber-Define of CremaEmailReasons *********************************/

#define CREMAEMAILREASONS_SELEMAILREASONS 1690

#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of CremaEmailAddresses ***************************/

#define DeleteAddress 1703
#define InsertAddress 1701
#define InsertGVL 1710
#define InsertType 1709
#define SelEmailAddresses 1699
#define SelEmailType 1704
#define Update 1695
#define UpdateEmailAddress 1708
#define UpdateGVL 1707

/* Old-FunctionNumber-Define of CremaEmailReasons *****************************/

#define SelEmailReasons 1690

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

class CCREMAEMAILADDRESSES : public ppDadeVirtual {
public:
    cremaemailaddressesS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<cremaemailaddressesS> lst; // class list

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
                     vector< cremaemailaddressesS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     cremaemailaddressesS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< cremaemailaddressesS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<cremaemailaddressesS>::iterator
                 beginList() { return lst.begin(); }
    vector<cremaemailaddressesS>::iterator
                 endList  () { return lst.end  (); }

    long         GetId() const { return s.ID; }
    short        GetEmailtype() const { return s.EMAILTYPE; }
    short        GetSendgvlmail() const { return s.SENDGVLMAIL; }
    long         GetSmtpusergroupid() const { return s.SMTPUSERGROUPID; }
    const char*  GetSenttoaddress(ppString & t) const { t = s.SENTTOADDRESS; t.erasespace(ppString::END); return t.c_str(); }
    long         GetSmtpemailtypeid() const { return s.SMTPEMAILTYPEID; }

    const cremaemailaddressesS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetId(long t) { s.ID = t; }
    void         SetEmailtype(short t) { s.EMAILTYPE = t; }
    void         SetSendgvlmail(short t) { s.SENDGVLMAIL = t; }
    void         SetSmtpusergroupid(long t) { s.SMTPUSERGROUPID = t; }
    void         SetSenttoaddress(const ppString & t) { ppGStrCopy(s.SENTTOADDRESS, t.c_str(), L_CREMAEMAILADDRESSES_SENTTOADDRESS); }
    void         SetSmtpemailtypeid(long t) { s.SMTPEMAILTYPEID = t; }

    void         SetStruct(const cremaemailaddressesS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          DeleteAddress(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1703, FetchRel, pos); return ret; }
    int          InsertAddress(int pos = 0) { int ret = UniqueServerCall(1701, pos); Strip(s); return ret; }
    int          InsertGVL(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1710, FetchRel, pos); return ret; }
    int          InsertType(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1709, FetchRel, pos); return ret; }
    int          SelEmailAddresses(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1699, FetchRel, pos); return ret; }
    int          SelEmailType(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1704, FetchRel, pos); return ret; }
    int          Update(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1695, FetchRel, pos); return ret; }
    int          UpdateEmailAddress(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1708, FetchRel, pos); return ret; }
    int          UpdateGVL(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1707, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCREMAEMAILADDRESSES() {
        ::buf_default((void *)&s, CREMAEMAILADDRESSES_BES, CREMAEMAILADDRESSES_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCREMAEMAILADDRESSES() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CREMAEMAILADDRESSES_BES, CREMAEMAILADDRESSES_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CREMAEMAILADDRESSES_BES, (int)CREMAEMAILADDRESSES_ANZ, error_msg);
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
        if ( fkt_nr == 1703 ) return CursorServerCall(1703, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1701 ) return UniqueServerCall(1701, pos);
        if ( fkt_nr == 1710 ) return CursorServerCall(1710, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1709 ) return CursorServerCall(1709, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1699 ) return CursorServerCall(1699, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1704 ) return CursorServerCall(1704, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1695 ) return CursorServerCall(1695, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1708 ) return CursorServerCall(1708, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1707 ) return CursorServerCall(1707, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CREMAEMAILADDRESSES & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.SENTTOADDRESS);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CREMAEMAILADDRESSES_BES, (int)CREMAEMAILADDRESSES_ANZ, error_msg);
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
        CCREMAEMAILADDRESSES c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CREMAEMAILADDRESSES_BES, (int)CREMAEMAILADDRESSES_ANZ, error_msg);
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

class CCREMAEMAILREASONS : public ppDadeVirtual {
public:
    cremaemailreasonsS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<cremaemailreasonsS> lst; // class list

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
                     vector< cremaemailreasonsS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     cremaemailreasonsS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< cremaemailreasonsS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<cremaemailreasonsS>::iterator
                 beginList() { return lst.begin(); }
    vector<cremaemailreasonsS>::iterator
                 endList  () { return lst.end  (); }

    long         GetId() const { return s.ID; }
    double       GetThresholdamount() const { return s.THRESHOLDAMOUNT; }
    short        GetType() const { return s.TYPE; }
    double       GetDlpercentage() const { return s.DLPERCENTAGE; }
    short        GetBranchno() const { return s.BRANCHNO; }

    const cremaemailreasonsS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetId(long t) { s.ID = t; }
    void         SetThresholdamount(double t) { s.THRESHOLDAMOUNT = t; }
    void         SetType(short t) { s.TYPE = t; }
    void         SetDlpercentage(double t) { s.DLPERCENTAGE = t; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }

    void         SetStruct(const cremaemailreasonsS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelEmailReasons(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1690, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCREMAEMAILREASONS() {
        ::buf_default((void *)&s, CREMAEMAILREASONS_BES, CREMAEMAILREASONS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCREMAEMAILREASONS() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CREMAEMAILREASONS_BES, CREMAEMAILREASONS_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CREMAEMAILREASONS_BES, (int)CREMAEMAILREASONS_ANZ, error_msg);
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
        if ( fkt_nr == 1690 ) return CursorServerCall(1690, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CREMAEMAILREASONS & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CREMAEMAILREASONS_BES, (int)CREMAEMAILREASONS_ANZ, error_msg);
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
        CCREMAEMAILREASONS c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CREMAEMAILREASONS_BES, (int)CREMAEMAILREASONS_ANZ, error_msg);
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
