#ifndef __PP_DELIVERYADVICELINEIBTLINK_H_
#define __PP_DELIVERYADVICELINEIBTLINK_H_

/******************************************************************************/
/* c:\prri\Headerfiles\deliveryadvicelineibtlink ******************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of DELIVERYADVICELINEIBTLINK *********************************/

#define L_DELIVERYADVICELINEIBTLINK_BRANCHNO 6
#define L_DELIVERYADVICELINEIBTLINK_CUSTOMERNO 11
#define L_DELIVERYADVICELINEIBTLINK_DELIVERYADVICEDATE 11
#define L_DELIVERYADVICELINEIBTLINK_DELIVERYADVICENO 10
#define L_DELIVERYADVICELINEIBTLINK_CSCORDERNO 11
#define L_DELIVERYADVICELINEIBTLINK_DELIVERYADVICEPOSNO 11
#define L_DELIVERYADVICELINEIBTLINK_CSCORDERPOSNO 11
#define L_DELIVERYADVICELINEIBTLINK_IBTBRANCHNO 6
#define L_DELIVERYADVICELINEIBTLINK_IBTCUSTOMERNO 11
#define L_DELIVERYADVICELINEIBTLINK_IBTDELIVERYADVICEDATE 11
#define L_DELIVERYADVICELINEIBTLINK_IBTDELIVERYADVICENO 10
#define L_DELIVERYADVICELINEIBTLINK_IBTDELIVERYADVICEPOSNO 11
#define L_DELIVERYADVICELINEIBTLINK_IBTCSCORDERNO 11
#define L_DELIVERYADVICELINEIBTLINK_IBTCSCORDERPOSNO 11

/* Length/Count-Define of DELIVERYADVICELINEIBTLINK ***************************/

#define LS_DELIVERYADVICELINEIBTLINK_BRANCHNO 5 + 1
#define LS_DELIVERYADVICELINEIBTLINK_CUSTOMERNO 10 + 1
#define LS_DELIVERYADVICELINEIBTLINK_DELIVERYADVICEDATE 10 + 1
#define LS_DELIVERYADVICELINEIBTLINK_DELIVERYADVICENO 10 + 1
#define LS_DELIVERYADVICELINEIBTLINK_CSCORDERNO 10 + 1
#define LS_DELIVERYADVICELINEIBTLINK_DELIVERYADVICEPOSNO 10 + 1
#define LS_DELIVERYADVICELINEIBTLINK_CSCORDERPOSNO 10 + 1
#define LS_DELIVERYADVICELINEIBTLINK_IBTBRANCHNO 5 + 1
#define LS_DELIVERYADVICELINEIBTLINK_IBTCUSTOMERNO 10 + 1
#define LS_DELIVERYADVICELINEIBTLINK_IBTDELIVERYADVICEDATE 10 + 1
#define LS_DELIVERYADVICELINEIBTLINK_IBTDELIVERYADVICENO 10 + 1
#define LS_DELIVERYADVICELINEIBTLINK_IBTDELIVERYADVICEPOSNO 10 + 1
#define LS_DELIVERYADVICELINEIBTLINK_IBTCSCORDERNO 10 + 1
#define LS_DELIVERYADVICELINEIBTLINK_IBTCSCORDERPOSNO 10 + 1

#define DELIVERYADVICELINEIBTLINKBRANCHNO 0
#define DELIVERYADVICELINEIBTLINKCUSTOMERNO 1
#define DELIVERYADVICELINEIBTLINKDELIVERYADVICEDATE 2
#define DELIVERYADVICELINEIBTLINKDELIVERYADVICENO 3
#define DELIVERYADVICELINEIBTLINKCSCORDERNO 4
#define DELIVERYADVICELINEIBTLINKDELIVERYADVICEPOSNO 5
#define DELIVERYADVICELINEIBTLINKCSCORDERPOSNO 6
#define DELIVERYADVICELINEIBTLINKIBTBRANCHNO 7
#define DELIVERYADVICELINEIBTLINKIBTCUSTOMERNO 8
#define DELIVERYADVICELINEIBTLINKIBTDELIVERYADVICEDATE 9
#define DELIVERYADVICELINEIBTLINKIBTDELIVERYADVICENO 10
#define DELIVERYADVICELINEIBTLINKIBTDELIVERYADVICEPOSNO 11
#define DELIVERYADVICELINEIBTLINKIBTCSCORDERNO 12
#define DELIVERYADVICELINEIBTLINKIBTCSCORDERPOSNO 13

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define DELIVERYADVICELINEIBTLINK_H
#define DELIVERYADVICELINEIBTLINK_ANZ ( sizeof(DELIVERYADVICELINEIBTLINK_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of DELIVERYADVICELINEIBTLINK *************************************/

#define DELIVERYADVICELINEIBTLINK_LISTE \
        DADUMMY.BRANCHNO,\
        DADUMMY.CUSTOMERNO,\
        DADUMMY.DELIVERYADVICEDATE,\
        DADUMMY.DELIVERYADVICENO,\
        DADUMMY.CSCORDERNO,\
        DADUMMY.DELIVERYADVICEPOSNO,\
        DADUMMY.CSCORDERPOSNO,\
        DADUMMY.IBTBRANCHNO,\
        DADUMMY.IBTCUSTOMERNO,\
        DADUMMY.IBTDELIVERYADVICEDATE,\
        DADUMMY.IBTDELIVERYADVICENO,\
        DADUMMY.IBTDELIVERYADVICEPOSNO,\
        DADUMMY.IBTCSCORDERNO,\
        DADUMMY.IBTCSCORDERPOSNO
#define DELIVERYADVICELINEIBTLINK_LISTE_390 \
        BRANCHNO,\
        CUSTOMERNO,\
        DELIVERYADVICEDATE,\
        DELIVERYADVICENO,\
        CSCORDERNO,\
        DELIVERYADVICEPOSNO,\
        CSCORDERPOSNO,\
        IBTBRANCHNO,\
        IBTCUSTOMERNO,\
        IBTDELIVERYADVICEDATE,\
        IBTDELIVERYADVICENO,\
        IBTDELIVERYADVICEPOSNO,\
        IBTCSCORDERNO,\
        IBTCSCORDERPOSNO
#define DELIVERYADVICELINEIBTLINK_PLISTE \
        "DADUMMY.BRANCHNO,"\
        "DADUMMY.CUSTOMERNO,"\
        "DADUMMY.DELIVERYADVICEDATE,"\
        "DADUMMY.DELIVERYADVICENO,"\
        "DADUMMY.CSCORDERNO,"\
        "DADUMMY.DELIVERYADVICEPOSNO,"\
        "DADUMMY.CSCORDERPOSNO,"\
        "DADUMMY.IBTBRANCHNO,"\
        "DADUMMY.IBTCUSTOMERNO,"\
        "DADUMMY.IBTDELIVERYADVICEDATE,"\
        "DADUMMY.IBTDELIVERYADVICENO,"\
        "DADUMMY.IBTDELIVERYADVICEPOSNO,"\
        "DADUMMY.IBTCSCORDERNO,"\
        "DADUMMY.IBTCSCORDERPOSNO"
#define DELIVERYADVICELINEIBTLINK_PELISTE \
        "BRANCHNO,"\
        "CUSTOMERNO,"\
        "DELIVERYADVICEDATE,"\
        "DELIVERYADVICENO,"\
        "CSCORDERNO,"\
        "DELIVERYADVICEPOSNO,"\
        "CSCORDERPOSNO,"\
        "IBTBRANCHNO,"\
        "IBTCUSTOMERNO,"\
        "IBTDELIVERYADVICEDATE,"\
        "IBTDELIVERYADVICENO,"\
        "IBTDELIVERYADVICEPOSNO,"\
        "IBTCSCORDERNO,"\
        "IBTCSCORDERPOSNO"
#define DELIVERYADVICELINEIBTLINK_UPDLISTE \
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "DELIVERYADVICEDATE=?,"\
        "DELIVERYADVICENO=?,"\
        "CSCORDERNO=?,"\
        "DELIVERYADVICEPOSNO=?,"\
        "CSCORDERPOSNO=?,"\
        "IBTBRANCHNO=?,"\
        "IBTCUSTOMERNO=?,"\
        "IBTDELIVERYADVICEDATE=?,"\
        "IBTDELIVERYADVICENO=?,"\
        "IBTDELIVERYADVICEPOSNO=?,"\
        "IBTCSCORDERNO=?,"\
        "IBTCSCORDERPOSNO=?"
/* SqlMacros-Define of DELIVERYADVICELINEIBTLINK ******************************/

#define DELIVERYADVICELINEIBTLINK_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->DELIVERYADVICEDATE,\
        :x->DELIVERYADVICENO,\
        :x->CSCORDERNO,\
        :x->DELIVERYADVICEPOSNO,\
        :x->CSCORDERPOSNO,\
        :x->IBTBRANCHNO,\
        :x->IBTCUSTOMERNO,\
        :x->IBTDELIVERYADVICEDATE,\
        :x->IBTDELIVERYADVICENO,\
        :x->IBTDELIVERYADVICEPOSNO,\
        :x->IBTCSCORDERNO,\
        :x->IBTCSCORDERPOSNO
#define DELIVERYADVICELINEIBTLINK_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->DELIVERYADVICEDATE,\
        :x->DELIVERYADVICENO,\
        :x->CSCORDERNO,\
        :x->DELIVERYADVICEPOSNO,\
        :x->CSCORDERPOSNO,\
        :x->IBTBRANCHNO,\
        :x->IBTCUSTOMERNO,\
        :x->IBTDELIVERYADVICEDATE,\
        :x->IBTDELIVERYADVICENO,\
        :x->IBTDELIVERYADVICEPOSNO,\
        :x->IBTCSCORDERNO,\
        :x->IBTCSCORDERPOSNO
#define DELIVERYADVICELINEIBTLINK_UPDATE(x) \
        DADUMMY.BRANCHNO=:x->BRANCHNO,\
        DADUMMY.CUSTOMERNO=:x->CUSTOMERNO,\
        DADUMMY.DELIVERYADVICEDATE=:x->DELIVERYADVICEDATE,\
        DADUMMY.DELIVERYADVICENO=:x->DELIVERYADVICENO,\
        DADUMMY.CSCORDERNO=:x->CSCORDERNO,\
        DADUMMY.DELIVERYADVICEPOSNO=:x->DELIVERYADVICEPOSNO,\
        DADUMMY.CSCORDERPOSNO=:x->CSCORDERPOSNO,\
        DADUMMY.IBTBRANCHNO=:x->IBTBRANCHNO,\
        DADUMMY.IBTCUSTOMERNO=:x->IBTCUSTOMERNO,\
        DADUMMY.IBTDELIVERYADVICEDATE=:x->IBTDELIVERYADVICEDATE,\
        DADUMMY.IBTDELIVERYADVICENO=:x->IBTDELIVERYADVICENO,\
        DADUMMY.IBTDELIVERYADVICEPOSNO=:x->IBTDELIVERYADVICEPOSNO,\
        DADUMMY.IBTCSCORDERNO=:x->IBTCSCORDERNO,\
        DADUMMY.IBTCSCORDERPOSNO=:x->IBTCSCORDERPOSNO
/* SqlMacros390-Define of DELIVERYADVICELINEIBTLINK ***************************/

#define DELIVERYADVICELINEIBTLINK_ZEIGER_390 \
        :BRANCHNO,\
        :CUSTOMERNO,\
        :DELIVERYADVICEDATE,\
        :DELIVERYADVICENO,\
        :CSCORDERNO,\
        :DELIVERYADVICEPOSNO,\
        :CSCORDERPOSNO,\
        :IBTBRANCHNO,\
        :IBTCUSTOMERNO,\
        :IBTDELIVERYADVICEDATE,\
        :IBTDELIVERYADVICENO,\
        :IBTDELIVERYADVICEPOSNO,\
        :IBTCSCORDERNO,\
        :IBTCSCORDERPOSNO
#define DELIVERYADVICELINEIBTLINK_UPDATE_390 \
        BRANCHNO=:BRANCHNO,\
        CUSTOMERNO=:CUSTOMERNO,\
        DELIVERYADVICEDATE=:DELIVERYADVICEDATE,\
        DELIVERYADVICENO=:DELIVERYADVICENO,\
        CSCORDERNO=:CSCORDERNO,\
        DELIVERYADVICEPOSNO=:DELIVERYADVICEPOSNO,\
        CSCORDERPOSNO=:CSCORDERPOSNO,\
        IBTBRANCHNO=:IBTBRANCHNO,\
        IBTCUSTOMERNO=:IBTCUSTOMERNO,\
        IBTDELIVERYADVICEDATE=:IBTDELIVERYADVICEDATE,\
        IBTDELIVERYADVICENO=:IBTDELIVERYADVICENO,\
        IBTDELIVERYADVICEPOSNO=:IBTDELIVERYADVICEPOSNO,\
        IBTCSCORDERNO=:IBTCSCORDERNO,\
        IBTCSCORDERPOSNO=:IBTCSCORDERPOSNO
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of DELIVERYADVICELINEIBTLINK *******************************/

#ifndef TRANSCLASS
typedef struct N_DELIVERYADVICELINEIBTLINK {
    short BRANCHNO;
    long CUSTOMERNO;
    long DELIVERYADVICEDATE;
    char DELIVERYADVICENO[11];
    long CSCORDERNO;
    long DELIVERYADVICEPOSNO;
    long CSCORDERPOSNO;
    short IBTBRANCHNO;
    long IBTCUSTOMERNO;
    long IBTDELIVERYADVICEDATE;
    char IBTDELIVERYADVICENO[11];
    long IBTDELIVERYADVICEPOSNO;
    long IBTCSCORDERNO;
    long IBTCSCORDERPOSNO;
} deliveryadvicelineibtlinkS;
#else /* TRANSCLASS */
typedef struct N_DELIVERYADVICELINEIBTLINK {
    short BRANCHNO;
    long CUSTOMERNO;
    long DELIVERYADVICEDATE;
    char DELIVERYADVICENO[11];
    long CSCORDERNO;
    long DELIVERYADVICEPOSNO;
    long CSCORDERPOSNO;
    short IBTBRANCHNO;
    long IBTCUSTOMERNO;
    long IBTDELIVERYADVICEDATE;
    char IBTDELIVERYADVICENO[11];
    long IBTDELIVERYADVICEPOSNO;
    long IBTCSCORDERNO;
    long IBTCSCORDERPOSNO;

    bool operator == (const N_DELIVERYADVICELINEIBTLINK& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            CUSTOMERNO == right.CUSTOMERNO &&
            DELIVERYADVICEDATE == right.DELIVERYADVICEDATE &&
            !strcmp(DELIVERYADVICENO, right.DELIVERYADVICENO) &&
            CSCORDERNO == right.CSCORDERNO &&
            DELIVERYADVICEPOSNO == right.DELIVERYADVICEPOSNO &&
            CSCORDERPOSNO == right.CSCORDERPOSNO &&
            IBTBRANCHNO == right.IBTBRANCHNO &&
            IBTCUSTOMERNO == right.IBTCUSTOMERNO &&
            IBTDELIVERYADVICEDATE == right.IBTDELIVERYADVICEDATE &&
            !strcmp(IBTDELIVERYADVICENO, right.IBTDELIVERYADVICENO) &&
            IBTDELIVERYADVICEPOSNO == right.IBTDELIVERYADVICEPOSNO &&
            IBTCSCORDERNO == right.IBTCSCORDERNO &&
            IBTCSCORDERPOSNO == right.IBTCSCORDERPOSNO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        CUSTOMERNO = 0;
        DELIVERYADVICEDATE = 0;
        strcpy(DELIVERYADVICENO, " " );
        CSCORDERNO = 0;
        DELIVERYADVICEPOSNO = 0;
        CSCORDERPOSNO = 0;
        IBTBRANCHNO = 0;
        IBTCUSTOMERNO = 0;
        IBTDELIVERYADVICEDATE = 0;
        strcpy(IBTDELIVERYADVICENO, " " );
        IBTDELIVERYADVICEPOSNO = 0;
        IBTCSCORDERNO = 0;
        IBTCSCORDERPOSNO = 0;
#endif
    }
} deliveryadvicelineibtlinkS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of DELIVERYADVICELINEIBTLINK *************************/

struct S_DELIVERYADVICELINEIBTLINK {
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char DELIVERYADVICEDATE[11];
    char DELIVERYADVICENO[10 + 1];
    char CSCORDERNO[11];
    char DELIVERYADVICEPOSNO[11];
    char CSCORDERPOSNO[11];
    char IBTBRANCHNO[7];
    char IBTCUSTOMERNO[11];
    char IBTDELIVERYADVICEDATE[11];
    char IBTDELIVERYADVICENO[10 + 1];
    char IBTDELIVERYADVICEPOSNO[11];
    char IBTCSCORDERNO[11];
    char IBTCSCORDERPOSNO[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of DELIVERYADVICELINEIBTLINK ********/

struct O_DELIVERYADVICELINEIBTLINK {
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char DELIVERYADVICEDATE[11];
    char DELIVERYADVICENO[10];
    char CSCORDERNO[11];
    char DELIVERYADVICEPOSNO[11];
    char CSCORDERPOSNO[11];
    char IBTBRANCHNO[7];
    char IBTCUSTOMERNO[11];
    char IBTDELIVERYADVICEDATE[11];
    char IBTDELIVERYADVICENO[10];
    char IBTDELIVERYADVICEPOSNO[11];
    char IBTCSCORDERNO[11];
    char IBTCSCORDERPOSNO[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of DELIVERYADVICELINEIBTLINK *******************/

struct C_DELIVERYADVICELINEIBTLINK {
    short BRANCHNO;
    long CUSTOMERNO;
    long DELIVERYADVICEDATE;
    char DELIVERYADVICENO[11];
    long CSCORDERNO;
    long DELIVERYADVICEPOSNO;
    long CSCORDERPOSNO;
    short IBTBRANCHNO;
    long IBTCUSTOMERNO;
    long IBTDELIVERYADVICEDATE;
    char IBTDELIVERYADVICENO[11];
    long IBTDELIVERYADVICEPOSNO;
    long IBTCSCORDERNO;
    long IBTCSCORDERPOSNO;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of DELIVERYADVICELINEIBTLINK *****************/

struct I_DELIVERYADVICELINEIBTLINK {
    short BRANCHNO;
    short CUSTOMERNO;
    short DELIVERYADVICEDATE;
    short DELIVERYADVICENO;
    short CSCORDERNO;
    short DELIVERYADVICEPOSNO;
    short CSCORDERPOSNO;
    short IBTBRANCHNO;
    short IBTCUSTOMERNO;
    short IBTDELIVERYADVICEDATE;
    short IBTDELIVERYADVICENO;
    short IBTDELIVERYADVICEPOSNO;
    short IBTCSCORDERNO;
    short IBTCSCORDERPOSNO;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of DELIVERYADVICELINEIBTLINK ***************************/

#if defined (BUF_DESC)
static struct buf_desc DELIVERYADVICELINEIBTLINK_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 10, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 10, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc DELIVERYADVICELINEIBTLINK_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 10, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 10, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* description for datatypes of DELIVERYADVICELINEIBTLINK *********************/

 #define DELIVERYADVICELINEIBTLINK_S390 \
         short BRANCHNO; \
         long CUSTOMERNO; \
         long DELIVERYADVICEDATE; \
         char DELIVERYADVICENO[11]; \
         long CSCORDERNO; \
         long DELIVERYADVICEPOSNO; \
         long CSCORDERPOSNO; \
         short IBTBRANCHNO; \
         long IBTCUSTOMERNO; \
         long IBTDELIVERYADVICEDATE; \
         char IBTDELIVERYADVICENO[11]; \
         long IBTDELIVERYADVICEPOSNO; \
         long IBTCSCORDERNO; \
         long IBTCSCORDERPOSNO; \



/* Copy-Function Struct to single Data DELIVERYADVICELINEIBTLINK **************/

 #define DELIVERYADVICELINEIBTLINK_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
         DELIVERYADVICEDATE=_x_->DELIVERYADVICEDATE;\
          strcpy(DELIVERYADVICENO,_x_->DELIVERYADVICENO);\
         CSCORDERNO=_x_->CSCORDERNO;\
         DELIVERYADVICEPOSNO=_x_->DELIVERYADVICEPOSNO;\
         CSCORDERPOSNO=_x_->CSCORDERPOSNO;\
         IBTBRANCHNO=_x_->IBTBRANCHNO;\
         IBTCUSTOMERNO=_x_->IBTCUSTOMERNO;\
         IBTDELIVERYADVICEDATE=_x_->IBTDELIVERYADVICEDATE;\
          strcpy(IBTDELIVERYADVICENO,_x_->IBTDELIVERYADVICENO);\
         IBTDELIVERYADVICEPOSNO=_x_->IBTDELIVERYADVICEPOSNO;\
         IBTCSCORDERNO=_x_->IBTCSCORDERNO;\
         IBTCSCORDERPOSNO=_x_->IBTCSCORDERPOSNO;\

 #define DELIVERYADVICELINEIBTLINK_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->DELIVERYADVICEDATE=DELIVERYADVICEDATE;\
          strcpy(_x_->DELIVERYADVICENO,DELIVERYADVICENO);\
          _x_->CSCORDERNO=CSCORDERNO;\
          _x_->DELIVERYADVICEPOSNO=DELIVERYADVICEPOSNO;\
          _x_->CSCORDERPOSNO=CSCORDERPOSNO;\
          _x_->IBTBRANCHNO=IBTBRANCHNO;\
          _x_->IBTCUSTOMERNO=IBTCUSTOMERNO;\
          _x_->IBTDELIVERYADVICEDATE=IBTDELIVERYADVICEDATE;\
          strcpy(_x_->IBTDELIVERYADVICENO,IBTDELIVERYADVICENO);\
          _x_->IBTDELIVERYADVICEPOSNO=IBTDELIVERYADVICEPOSNO;\
          _x_->IBTCSCORDERNO=IBTCSCORDERNO;\
          _x_->IBTCSCORDERPOSNO=IBTCSCORDERPOSNO;\



/* FunctionNumber-Define of deliveryadvicelineibtlink *************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of deliveryadvicelineibtlink *********************/


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

class CDELIVERYADVICELINEIBTLINK : public ppDadeVirtual {
public:
    deliveryadvicelineibtlinkS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<deliveryadvicelineibtlinkS> lst; // class list

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
                     vector< deliveryadvicelineibtlinkS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     deliveryadvicelineibtlinkS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< deliveryadvicelineibtlinkS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<deliveryadvicelineibtlinkS>::iterator
                 beginList() { return lst.begin(); }
    vector<deliveryadvicelineibtlinkS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    long         GetDeliveryadvicedate() const { return s.DELIVERYADVICEDATE; }
    const char*  GetDeliveryadviceno(ppString & t) const { t = s.DELIVERYADVICENO; t.erasespace(ppString::END); return t.c_str(); }
    long         GetCscorderno() const { return s.CSCORDERNO; }
    long         GetDeliveryadviceposno() const { return s.DELIVERYADVICEPOSNO; }
    long         GetCscorderposno() const { return s.CSCORDERPOSNO; }
    short        GetIbtbranchno() const { return s.IBTBRANCHNO; }
    long         GetIbtcustomerno() const { return s.IBTCUSTOMERNO; }
    long         GetIbtdeliveryadvicedate() const { return s.IBTDELIVERYADVICEDATE; }
    const char*  GetIbtdeliveryadviceno(ppString & t) const { t = s.IBTDELIVERYADVICENO; t.erasespace(ppString::END); return t.c_str(); }
    long         GetIbtdeliveryadviceposno() const { return s.IBTDELIVERYADVICEPOSNO; }
    long         GetIbtcscorderno() const { return s.IBTCSCORDERNO; }
    long         GetIbtcscorderposno() const { return s.IBTCSCORDERPOSNO; }

    const deliveryadvicelineibtlinkS &
                 GetStruct() const { return s; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetDeliveryadvicedate(long t) { s.DELIVERYADVICEDATE = t; }
    void         SetDeliveryadviceno(const ppString & t) { ppGStrCopy(s.DELIVERYADVICENO, t.c_str(), L_DELIVERYADVICELINEIBTLINK_DELIVERYADVICENO); }
    void         SetCscorderno(long t) { s.CSCORDERNO = t; }
    void         SetDeliveryadviceposno(long t) { s.DELIVERYADVICEPOSNO = t; }
    void         SetCscorderposno(long t) { s.CSCORDERPOSNO = t; }
    void         SetIbtbranchno(short t) { s.IBTBRANCHNO = t; }
    void         SetIbtcustomerno(long t) { s.IBTCUSTOMERNO = t; }
    void         SetIbtdeliveryadvicedate(long t) { s.IBTDELIVERYADVICEDATE = t; }
    void         SetIbtdeliveryadviceno(const ppString & t) { ppGStrCopy(s.IBTDELIVERYADVICENO, t.c_str(), L_DELIVERYADVICELINEIBTLINK_IBTDELIVERYADVICENO); }
    void         SetIbtdeliveryadviceposno(long t) { s.IBTDELIVERYADVICEPOSNO = t; }
    void         SetIbtcscorderno(long t) { s.IBTCSCORDERNO = t; }
    void         SetIbtcscorderposno(long t) { s.IBTCSCORDERPOSNO = t; }

    void         SetStruct(const deliveryadvicelineibtlinkS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CDELIVERYADVICELINEIBTLINK() {
        ::buf_default((void *)&s, DELIVERYADVICELINEIBTLINK_BES, DELIVERYADVICELINEIBTLINK_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CDELIVERYADVICELINEIBTLINK() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, DELIVERYADVICELINEIBTLINK_BES, DELIVERYADVICELINEIBTLINK_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, DELIVERYADVICELINEIBTLINK_BES, (int)DELIVERYADVICELINEIBTLINK_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, DELIVERYADVICELINEIBTLINK_BES, (int)DELIVERYADVICELINEIBTLINK_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_DELIVERYADVICELINEIBTLINK & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.DELIVERYADVICENO);
        ppGStripLast(d.IBTDELIVERYADVICENO);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, DELIVERYADVICELINEIBTLINK_BES, (int)DELIVERYADVICELINEIBTLINK_ANZ, error_msg);
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
/* CreateSqlStatement of DELIVERYADVICELINEIBTLINK ****************************/

 #define DELIVERYADVICELINEIBTLINK_CREATE(x) EXEC SQL create table x (\
         BRANCHNO smallint default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         DELIVERYADVICEDATE integer default 0 not null,\
         DELIVERYADVICENO varchar(10,0) default " " not null,\
         CSCORDERNO integer default 0 not null,\
         DELIVERYADVICEPOSNO integer default 0 not null,\
         CSCORDERPOSNO integer default 0 not null,\
         IBTBRANCHNO smallint default 0 not null,\
         IBTCUSTOMERNO integer default 0 not null,\
         IBTDELIVERYADVICEDATE integer default 0 not null,\
         IBTDELIVERYADVICENO varchar(10,0) default " " not null,\
         IBTDELIVERYADVICEPOSNO integer default 0 not null,\
         IBTCSCORDERNO integer default 0 not null,\
         IBTCSCORDERPOSNO integer default 0 not null) extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of DELIVERYADVICELINEIBTLINK **************************/

 #define DELIVERYADVICELINEIBTLINK_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
/* DeleteIndexStatement of DELIVERYADVICELINEIBTLINK **************************/

 #define DELIVERYADVICELINEIBTLINK_DELETE_INDEX(_X_)\
              _X_ = 0;\


#endif   // GUARD
