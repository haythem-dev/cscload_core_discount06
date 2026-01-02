#ifndef __PP_ORDERDATA_H_
#define __PP_ORDERDATA_H_

/******************************************************************************/
/* D:\var\tmp\2\orderdata *****************************************************/
/* produced by DADE 6.21.0 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <pplib/bufkon.h>

/* Length-Define of ORDERDATA *************************************************/

#define L_ORDERDATA_BRANCHNO 6
#define L_ORDERDATA_CUSTOMERNO 11
#define L_ORDERDATA_ORDERQTY 11
#define L_ORDERDATA_ARTICLENO 11
#define L_ORDERDATA_KINDOFORDER 2
#define L_ORDERDATA_SHIPMENTTYPE 1
#define L_ORDERDATA_BOOKINGTYPE 1
#define L_ORDERDATA_DEVICENAME 8
#define L_ORDERDATA_USERNAME 8
#define L_ORDERDATA_UID 11
#define L_ORDERDATA_ADDITION 2
#define L_ORDERDATA_ORDERSEQUENZNO 6
#define L_ORDERDATA_CLOSETYPE 1
#define L_ORDERDATA_POSITIONINFO 2
#define L_ORDERDATA_REMARKS 30

/* Length/Count-Define of ORDERDATA *******************************************/

#define LS_ORDERDATA_BRANCHNO 5 + 1
#define LS_ORDERDATA_CUSTOMERNO 10 + 1
#define LS_ORDERDATA_ORDERQTY 10 + 1
#define LS_ORDERDATA_ARTICLENO 10 + 1
#define LS_ORDERDATA_KINDOFORDER 2 + 1
#define LS_ORDERDATA_SHIPMENTTYPE 1 + 1
#define LS_ORDERDATA_BOOKINGTYPE 1 + 1
#define LS_ORDERDATA_DEVICENAME 8 + 1
#define LS_ORDERDATA_USERNAME 8 + 1
#define LS_ORDERDATA_UID 10 + 1
#define LS_ORDERDATA_ADDITION 2 + 1
#define LS_ORDERDATA_ORDERSEQUENZNO 5 + 1
#define LS_ORDERDATA_CLOSETYPE 1 + 1
#define LS_ORDERDATA_POSITIONINFO 2 + 1
#define LS_ORDERDATA_REMARKS 30 + 1

#define ORDERDATABRANCHNO 0
#define ORDERDATACUSTOMERNO 1
#define ORDERDATAORDERQTY 2
#define ORDERDATAARTICLENO 3
#define ORDERDATAKINDOFORDER 4
#define ORDERDATASHIPMENTTYPE 5
#define ORDERDATABOOKINGTYPE 6
#define ORDERDATADEVICENAME 7
#define ORDERDATAUSERNAME 8
#define ORDERDATAUID 9
#define ORDERDATAADDITION 10
#define ORDERDATAORDERSEQUENZNO 11
#define ORDERDATACLOSETYPE 12
#define ORDERDATAPOSITIONINFO 13
#define ORDERDATAREMARKS 14

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define ORDERDATA_H
#define ORDERDATA_ANZ ( sizeof(ORDERDATA_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ORDERDATA *****************************************************/

#define ORDERDATA_LISTE \
        KSCDUMMY.BRANCHNO,\
        KSCDUMMY.CUSTOMERNO,\
        KSCDUMMY.ORDERQTY,\
        KSCDUMMY.ARTICLENO,\
        KSCDUMMY.KINDOFORDER,\
        KSCDUMMY.SHIPMENTTYPE,\
        KSCDUMMY.BOOKINGTYPE,\
        KSCDUMMY.DEVICENAME,\
        KSCDUMMY.USERNAME,\
        KSCDUMMY.UID,\
        KSCDUMMY.ADDITION,\
        KSCDUMMY.ORDERSEQUENZNO,\
        KSCDUMMY.CLOSETYPE,\
        KSCDUMMY.POSITIONINFO,\
        KSCDUMMY.REMARKS
#define ORDERDATA_LISTE_390 \
        BRANCHNO,\
        CUSTOMERNO,\
        ORDERQTY,\
        ARTICLENO,\
        KINDOFORDER,\
        SHIPMENTTYPE,\
        BOOKINGTYPE,\
        DEVICENAME,\
        USERNAME,\
        UID,\
        ADDITION,\
        ORDERSEQUENZNO,\
        CLOSETYPE,\
        POSITIONINFO,\
        REMARKS
#define ORDERDATA_PLISTE \
        "KSCDUMMY.BRANCHNO,"\
        "KSCDUMMY.CUSTOMERNO,"\
        "KSCDUMMY.ORDERQTY,"\
        "KSCDUMMY.ARTICLENO,"\
        "KSCDUMMY.KINDOFORDER,"\
        "KSCDUMMY.SHIPMENTTYPE,"\
        "KSCDUMMY.BOOKINGTYPE,"\
        "KSCDUMMY.DEVICENAME,"\
        "KSCDUMMY.USERNAME,"\
        "KSCDUMMY.UID,"\
        "KSCDUMMY.ADDITION,"\
        "KSCDUMMY.ORDERSEQUENZNO,"\
        "KSCDUMMY.CLOSETYPE,"\
        "KSCDUMMY.POSITIONINFO,"\
        "KSCDUMMY.REMARKS"
#define ORDERDATA_PELISTE \
        "BRANCHNO,"\
        "CUSTOMERNO,"\
        "ORDERQTY,"\
        "ARTICLENO,"\
        "KINDOFORDER,"\
        "SHIPMENTTYPE,"\
        "BOOKINGTYPE,"\
        "DEVICENAME,"\
        "USERNAME,"\
        "UID,"\
        "ADDITION,"\
        "ORDERSEQUENZNO,"\
        "CLOSETYPE,"\
        "POSITIONINFO,"\
        "REMARKS"
#define ORDERDATA_UPDLISTE \
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "ORDERQTY=?,"\
        "ARTICLENO=?,"\
        "KINDOFORDER=?,"\
        "SHIPMENTTYPE=?,"\
        "BOOKINGTYPE=?,"\
        "DEVICENAME=?,"\
        "USERNAME=?,"\
        "UID=?,"\
        "ADDITION=?,"\
        "ORDERSEQUENZNO=?,"\
        "CLOSETYPE=?,"\
        "POSITIONINFO=?,"\
        "REMARKS=?"
/* SqlMacros-Define of ORDERDATA **********************************************/

#define ORDERDATA_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->ORDERQTY,\
        :x->ARTICLENO,\
        :x->KINDOFORDER,\
        :x->SHIPMENTTYPE,\
        :x->BOOKINGTYPE,\
        :x->DEVICENAME,\
        :x->USERNAME,\
        :x->UID,\
        :x->ADDITION,\
        :x->ORDERSEQUENZNO,\
        :x->CLOSETYPE,\
        :x->POSITIONINFO,\
        :x->REMARKS
#define ORDERDATA_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->ORDERQTY,\
        :x->ARTICLENO,\
        :x->KINDOFORDER,\
        :x->SHIPMENTTYPE,\
        :x->BOOKINGTYPE,\
        :x->DEVICENAME,\
        :x->USERNAME,\
        :x->UID,\
        :x->ADDITION,\
        :x->ORDERSEQUENZNO,\
        :x->CLOSETYPE,\
        :x->POSITIONINFO,\
        :x->REMARKS
#define ORDERDATA_UPDATE(x) \
        KSCDUMMY.BRANCHNO=:x->BRANCHNO,\
        KSCDUMMY.CUSTOMERNO=:x->CUSTOMERNO,\
        KSCDUMMY.ORDERQTY=:x->ORDERQTY,\
        KSCDUMMY.ARTICLENO=:x->ARTICLENO,\
        KSCDUMMY.KINDOFORDER=:x->KINDOFORDER,\
        KSCDUMMY.SHIPMENTTYPE=:x->SHIPMENTTYPE,\
        KSCDUMMY.BOOKINGTYPE=:x->BOOKINGTYPE,\
        KSCDUMMY.DEVICENAME=:x->DEVICENAME,\
        KSCDUMMY.USERNAME=:x->USERNAME,\
        KSCDUMMY.UID=:x->UID,\
        KSCDUMMY.ADDITION=:x->ADDITION,\
        KSCDUMMY.ORDERSEQUENZNO=:x->ORDERSEQUENZNO,\
        KSCDUMMY.CLOSETYPE=:x->CLOSETYPE,\
        KSCDUMMY.POSITIONINFO=:x->POSITIONINFO,\
        KSCDUMMY.REMARKS=:x->REMARKS
/* SqlMacros390-Define of ORDERDATA *******************************************/

#define ORDERDATA_ZEIGER_390 \
        :BRANCHNO,\
        :CUSTOMERNO,\
        :ORDERQTY,\
        :ARTICLENO,\
        :KINDOFORDER,\
        :SHIPMENTTYPE,\
        :BOOKINGTYPE,\
        :DEVICENAME,\
        :USERNAME,\
        :UID,\
        :ADDITION,\
        :ORDERSEQUENZNO,\
        :CLOSETYPE,\
        :POSITIONINFO,\
        :REMARKS
#define ORDERDATA_UPDATE_390 \
        BRANCHNO=:BRANCHNO,\
        CUSTOMERNO=:CUSTOMERNO,\
        ORDERQTY=:ORDERQTY,\
        ARTICLENO=:ARTICLENO,\
        KINDOFORDER=:KINDOFORDER,\
        SHIPMENTTYPE=:SHIPMENTTYPE,\
        BOOKINGTYPE=:BOOKINGTYPE,\
        DEVICENAME=:DEVICENAME,\
        USERNAME=:USERNAME,\
        UID=:UID,\
        ADDITION=:ADDITION,\
        ORDERSEQUENZNO=:ORDERSEQUENZNO,\
        CLOSETYPE=:CLOSETYPE,\
        POSITIONINFO=:POSITIONINFO,\
        REMARKS=:REMARKS
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of ORDERDATA ***********************************************/

#ifndef TRANSCLASS
typedef struct N_ORDERDATA {
    short BRANCHNO;
    long CUSTOMERNO;
    long ORDERQTY;
    long ARTICLENO;
    char KINDOFORDER[3];
    char SHIPMENTTYPE[2];
    char BOOKINGTYPE[2];
    char DEVICENAME[9];
    char USERNAME[9];
    long UID;
    char ADDITION[3];
    short ORDERSEQUENZNO;
    char CLOSETYPE[2];
    char POSITIONINFO[3];
    char REMARKS[31];
} orderdataS;
#else /* TRANSCLASS */
typedef struct N_ORDERDATA {
    short BRANCHNO;
    long CUSTOMERNO;
    long ORDERQTY;
    long ARTICLENO;
    char KINDOFORDER[3];
    char SHIPMENTTYPE[2];
    char BOOKINGTYPE[2];
    char DEVICENAME[9];
    char USERNAME[9];
    long UID;
    char ADDITION[3];
    short ORDERSEQUENZNO;
    char CLOSETYPE[2];
    char POSITIONINFO[3];
    char REMARKS[31];

    bool operator == (const N_ORDERDATA& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            CUSTOMERNO == right.CUSTOMERNO &&
            ORDERQTY == right.ORDERQTY &&
            ARTICLENO == right.ARTICLENO &&
            !strcmp(KINDOFORDER, right.KINDOFORDER) &&
            !strcmp(SHIPMENTTYPE, right.SHIPMENTTYPE) &&
            !strcmp(BOOKINGTYPE, right.BOOKINGTYPE) &&
            !strcmp(DEVICENAME, right.DEVICENAME) &&
            !strcmp(USERNAME, right.USERNAME) &&
            UID == right.UID &&
            !strcmp(ADDITION, right.ADDITION) &&
            ORDERSEQUENZNO == right.ORDERSEQUENZNO &&
            !strcmp(CLOSETYPE, right.CLOSETYPE) &&
            !strcmp(POSITIONINFO, right.POSITIONINFO) &&
            !strcmp(REMARKS, right.REMARKS)
        );
    }
    void clear() {
#ifdef _WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        CUSTOMERNO = 0;
        ORDERQTY = 0;
        ARTICLENO = 0;
        strcpy(KINDOFORDER, " " );
        strcpy(SHIPMENTTYPE, " " );
        strcpy(BOOKINGTYPE, " " );
        strcpy(DEVICENAME, " " );
        strcpy(USERNAME, " " );
        UID = 0;
        strcpy(ADDITION, " " );
        ORDERSEQUENZNO = 0;
        strcpy(CLOSETYPE, " " );
        strcpy(POSITIONINFO, " " );
        strcpy(REMARKS, " " );
#endif
    }
} orderdataS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ORDERDATA *****************************************/

struct S_ORDERDATA {
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char ORDERQTY[11];
    char ARTICLENO[11];
    char KINDOFORDER[2 + 1];
    char SHIPMENTTYPE[1 + 1];
    char BOOKINGTYPE[1 + 1];
    char DEVICENAME[8 + 1];
    char USERNAME[8 + 1];
    char UID[11];
    char ADDITION[2 + 1];
    char ORDERSEQUENZNO[7];
    char CLOSETYPE[1 + 1];
    char POSITIONINFO[2 + 1];
    char REMARKS[30 + 1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ORDERDATA ************************/

struct O_ORDERDATA {
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char ORDERQTY[11];
    char ARTICLENO[11];
    char KINDOFORDER[2];
    char SHIPMENTTYPE[1];
    char BOOKINGTYPE[1];
    char DEVICENAME[8];
    char USERNAME[8];
    char UID[11];
    char ADDITION[2];
    char ORDERSEQUENZNO[7];
    char CLOSETYPE[1];
    char POSITIONINFO[2];
    char REMARKS[30];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ORDERDATA ***********************************/

struct C_ORDERDATA {
    short BRANCHNO;
    long CUSTOMERNO;
    long ORDERQTY;
    long ARTICLENO;
    char KINDOFORDER[3];
    char SHIPMENTTYPE;
    char BOOKINGTYPE;
    char DEVICENAME[9];
    char USERNAME[9];
    long UID;
    char ADDITION[3];
    short ORDERSEQUENZNO;
    char CLOSETYPE;
    char POSITIONINFO[3];
    char REMARKS[31];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ORDERDATA *********************************/

struct I_ORDERDATA {
    short BRANCHNO;
    short CUSTOMERNO;
    short ORDERQTY;
    short ARTICLENO;
    short KINDOFORDER;
    short SHIPMENTTYPE;
    short BOOKINGTYPE;
    short DEVICENAME;
    short USERNAME;
    short UID;
    short ADDITION;
    short ORDERSEQUENZNO;
    short CLOSETYPE;
    short POSITIONINFO;
    short REMARKS;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ORDERDATA *******************************************/

#if defined (BUF_DESC)
static struct buf_desc ORDERDATA_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 8, 0 },
   { TYP_C, 8, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 2, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 30, 0 },
};
/* avoid unused warning */
void * pUnusedORDERDATA = ORDERDATA_BES;
#elif defined (C_BUF_DESC)
static struct buf_desc ORDERDATA_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 8, 0 },
   { TYP_C, 8, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 2, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 30, 0 },
};
/* avoid unused warning */
void * pUnusedORDERDATA = ORDERDATA_BES;
#endif

/* description for datatypes of ORDERDATA *************************************/

 #define ORDERDATA_S390 \
         short BRANCHNO; \
         long CUSTOMERNO; \
         long ORDERQTY; \
         long ARTICLENO; \
         char KINDOFORDER[3]; \
         char SHIPMENTTYPE; \
         char BOOKINGTYPE; \
         char DEVICENAME[9]; \
         char USERNAME[9]; \
         long UID; \
         char ADDITION[3]; \
         short ORDERSEQUENZNO; \
         char CLOSETYPE; \
         char POSITIONINFO[3]; \
         char REMARKS[31]; \



/* Copy-Function Struct to single Data ORDERDATA ******************************/

 #define ORDERDATA_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
         ORDERQTY=_x_->ORDERQTY;\
         ARTICLENO=_x_->ARTICLENO;\
          strcpy(KINDOFORDER,_x_->KINDOFORDER);\
         SHIPMENTTYPE=_x_->SHIPMENTTYPE;\
         BOOKINGTYPE=_x_->BOOKINGTYPE;\
          strcpy(DEVICENAME,_x_->DEVICENAME);\
          strcpy(USERNAME,_x_->USERNAME);\
         UID=_x_->UID;\
          strcpy(ADDITION,_x_->ADDITION);\
         ORDERSEQUENZNO=_x_->ORDERSEQUENZNO;\
         CLOSETYPE=_x_->CLOSETYPE;\
          strcpy(POSITIONINFO,_x_->POSITIONINFO);\
          strcpy(REMARKS,_x_->REMARKS);\

 #define ORDERDATA_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->ORDERQTY=ORDERQTY;\
          _x_->ARTICLENO=ARTICLENO;\
          strcpy(_x_->KINDOFORDER,KINDOFORDER);\
          _x_->SHIPMENTTYPE=SHIPMENTTYPE;\
          _x_->BOOKINGTYPE=BOOKINGTYPE;\
          strcpy(_x_->DEVICENAME,DEVICENAME);\
          strcpy(_x_->USERNAME,USERNAME);\
          _x_->UID=UID;\
          strcpy(_x_->ADDITION,ADDITION);\
          _x_->ORDERSEQUENZNO=ORDERSEQUENZNO;\
          _x_->CLOSETYPE=CLOSETYPE;\
          strcpy(_x_->POSITIONINFO,POSITIONINFO);\
          strcpy(_x_->REMARKS,REMARKS);\



/* FunctionNumber-Define of orderdata *****************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of orderdata *************************************/


#endif

/* C++ Class ******************************************************************/

#ifdef TRANSCLASS

#include<vector>
using namespace std;

/* ppunixc */
#include <pplib/sockclient.h>
#include <pplib/ppstring.h>
#include <pplib/ppgeneric.h>

/* must be implemented */
void FehlerBehandlung(int rc, char *error_msg);

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

class CORDERDATA : public ppDadeVirtual {
public:
    orderdataS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<orderdataS> lst; // class list

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
                     vector< orderdataS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     orderdataS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< orderdataS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<orderdataS>::iterator
                 beginList() { return lst.begin(); }
    vector<orderdataS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    long         GetOrderqty() const { return s.ORDERQTY; }
    long         GetArticleno() const { return s.ARTICLENO; }
    const char*  GetKindoforder(ppString & t) const { t = s.KINDOFORDER; t.erasespace(ppString::END); return t.c_str(); }
    char         GetShipmenttype() const { return s.SHIPMENTTYPE[0]; }
    char         GetBookingtype() const { return s.BOOKINGTYPE[0]; }
    const char*  GetDevicename(ppString & t) const { t = s.DEVICENAME; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetUsername(ppString & t) const { t = s.USERNAME; t.erasespace(ppString::END); return t.c_str(); }
    long         GetUid() const { return s.UID; }
    const char*  GetAddition(ppString & t) const { t = s.ADDITION; t.erasespace(ppString::END); return t.c_str(); }
    short        GetOrdersequenzno() const { return s.ORDERSEQUENZNO; }
    char         GetClosetype() const { return s.CLOSETYPE[0]; }
    const char*  GetPositioninfo(ppString & t) const { t = s.POSITIONINFO; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetRemarks(ppString & t) const { t = s.REMARKS; t.erasespace(ppString::END); return t.c_str(); }

    const orderdataS &
                 GetStruct() const { return s; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetOrderqty(long t) { s.ORDERQTY = t; }
    void         SetArticleno(long t) { s.ARTICLENO = t; }
    void         SetKindoforder(const ppString & t) { ppGStrCopy(s.KINDOFORDER, t.c_str(), L_ORDERDATA_KINDOFORDER); }
    void         SetShipmenttype(char t) { s.SHIPMENTTYPE[0] = t; s.SHIPMENTTYPE[1] = '\0';}
    void         SetBookingtype(char t) { s.BOOKINGTYPE[0] = t; s.BOOKINGTYPE[1] = '\0';}
    void         SetDevicename(const ppString & t) { ppGStrCopy(s.DEVICENAME, t.c_str(), L_ORDERDATA_DEVICENAME); }
    void         SetUsername(const ppString & t) { ppGStrCopy(s.USERNAME, t.c_str(), L_ORDERDATA_USERNAME); }
    void         SetUid(long t) { s.UID = t; }
    void         SetAddition(const ppString & t) { ppGStrCopy(s.ADDITION, t.c_str(), L_ORDERDATA_ADDITION); }
    void         SetOrdersequenzno(short t) { s.ORDERSEQUENZNO = t; }
    void         SetClosetype(char t) { s.CLOSETYPE[0] = t; s.CLOSETYPE[1] = '\0';}
    void         SetPositioninfo(const ppString & t) { ppGStrCopy(s.POSITIONINFO, t.c_str(), L_ORDERDATA_POSITIONINFO); }
    void         SetRemarks(const ppString & t) { ppGStrCopy(s.REMARKS, t.c_str(), L_ORDERDATA_REMARKS); }

    void         SetStruct(const orderdataS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CORDERDATA() {
        ::buf_default((void *)&s, ORDERDATA_BES, ORDERDATA_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CORDERDATA() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, ORDERDATA_BES, ORDERDATA_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef _WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, ORDERDATA_BES, ORDERDATA_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, ORDERDATA_BES, ORDERDATA_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_ORDERDATA & d) {
        d = d;
    #ifdef _WIN32
        ppGStripLast(d.KINDOFORDER);
        ppGStripLast(d.DEVICENAME);
        ppGStripLast(d.USERNAME);
        ppGStripLast(d.ADDITION);
        ppGStripLast(d.POSITIONINFO);
        ppGStripLast(d.REMARKS);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, ORDERDATA_BES, ORDERDATA_ANZ, error_msg);
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
/* CreateSqlStatement of ORDERDATA ********************************************/

 #define ORDERDATA_CREATE(x) EXEC SQL create table x (\
         BRANCHNO smallint default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         ORDERQTY integer default 0 not null,\
         ARTICLENO integer default 0 not null,\
         KINDOFORDER char(2) default " " not null,\
         SHIPMENTTYPE char(1) default " " not null,\
         BOOKINGTYPE char(1) default " " not null,\
         DEVICENAME char(8) default " " not null,\
         USERNAME char(8) default " " not null,\
         UID integer default 0 not null,\
         ADDITION char(2) default " " not null,\
         ORDERSEQUENZNO smallint default 0 not null,\
         CLOSETYPE char(1) default " " not null,\
         POSITIONINFO char(2) default " " not null,\
         REMARKS char(30) default " " not null) extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of ORDERDATA ******************************************/

 #define ORDERDATA_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
/* DeleteIndexStatement of ORDERDATA ******************************************/

 #define ORDERDATA_DELETE_INDEX(_X_)\
              _X_ = 0;\


#endif   // GUARD
