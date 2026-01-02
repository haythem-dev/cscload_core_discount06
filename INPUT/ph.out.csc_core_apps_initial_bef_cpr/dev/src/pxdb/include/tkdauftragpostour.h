#ifndef __PP_KDAUFTRAGPOSTOUR_H_
#define __PP_KDAUFTRAGPOSTOUR_H_

/******************************************************************************/
/* c:\temp\kdauftragpostour ***************************************************/
/* produced by DADE 6.22.0 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of KDAUFTRAGPOSTOUR ******************************************/

#define L_KDAUFTRAGPOSTOUR_KDAUFTRAGNR 11
#define L_KDAUFTRAGPOSTOUR_POSNR 11
#define L_KDAUFTRAGPOSTOUR_DELIVERYBRANCHNO 6
#define L_KDAUFTRAGPOSTOUR_DELIVERYDATE 11
#define L_KDAUFTRAGPOSTOUR_DELIVERYTIME 6
#define L_KDAUFTRAGPOSTOUR_TOURID 6
#define L_KDAUFTRAGPOSTOUR_DEPARTUREDATE 11
#define L_KDAUFTRAGPOSTOUR_DEPARTURETIME 6
#define L_KDAUFTRAGPOSTOUR_DRIVINGDURATION 11
#define L_KDAUFTRAGPOSTOUR_DELIVERYTIMEBUFFER 6
#define L_KDAUFTRAGPOSTOUR_IBTTOURID 6
#define L_KDAUFTRAGPOSTOUR_IBTCUSTOMERNO 11
#define L_KDAUFTRAGPOSTOUR_IBTTYPE 6
#define L_KDAUFTRAGPOSTOUR_DAYIBT 6
#define L_KDAUFTRAGPOSTOUR_IBTTOURDATE 11

/* Length/Count-Define of KDAUFTRAGPOSTOUR ************************************/

#define LS_KDAUFTRAGPOSTOUR_KDAUFTRAGNR 10 + 1
#define LS_KDAUFTRAGPOSTOUR_POSNR 10 + 1
#define LS_KDAUFTRAGPOSTOUR_DELIVERYBRANCHNO 5 + 1
#define LS_KDAUFTRAGPOSTOUR_DELIVERYDATE 10 + 1
#define LS_KDAUFTRAGPOSTOUR_DELIVERYTIME 5 + 1
#define LS_KDAUFTRAGPOSTOUR_TOURID 6 + 1
#define LS_KDAUFTRAGPOSTOUR_DEPARTUREDATE 10 + 1
#define LS_KDAUFTRAGPOSTOUR_DEPARTURETIME 5 + 1
#define LS_KDAUFTRAGPOSTOUR_DRIVINGDURATION 10 + 1
#define LS_KDAUFTRAGPOSTOUR_DELIVERYTIMEBUFFER 5 + 1
#define LS_KDAUFTRAGPOSTOUR_IBTTOURID 6 + 1
#define LS_KDAUFTRAGPOSTOUR_IBTCUSTOMERNO 10 + 1
#define LS_KDAUFTRAGPOSTOUR_IBTTYPE 5 + 1
#define LS_KDAUFTRAGPOSTOUR_DAYIBT 5 + 1
#define LS_KDAUFTRAGPOSTOUR_IBTTOURDATE 10 + 1

#define KDAUFTRAGPOSTOURKDAUFTRAGNR 0
#define KDAUFTRAGPOSTOURPOSNR 1
#define KDAUFTRAGPOSTOURDELIVERYBRANCHNO 2
#define KDAUFTRAGPOSTOURDELIVERYDATE 3
#define KDAUFTRAGPOSTOURDELIVERYTIME 4
#define KDAUFTRAGPOSTOURTOURID 5
#define KDAUFTRAGPOSTOURDEPARTUREDATE 6
#define KDAUFTRAGPOSTOURDEPARTURETIME 7
#define KDAUFTRAGPOSTOURDRIVINGDURATION 8
#define KDAUFTRAGPOSTOURDELIVERYTIMEBUFFER 9
#define KDAUFTRAGPOSTOURIBTTOURID 10
#define KDAUFTRAGPOSTOURIBTCUSTOMERNO 11
#define KDAUFTRAGPOSTOURIBTTYPE 12
#define KDAUFTRAGPOSTOURDAYIBT 13
#define KDAUFTRAGPOSTOURIBTTOURDATE 14

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define KDAUFTRAGPOSTOUR_H
#define KDAUFTRAGPOSTOUR_ANZ ( sizeof(KDAUFTRAGPOSTOUR_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of KDAUFTRAGPOSTOUR **********************************************/

#define KDAUFTRAGPOSTOUR_LISTE \
        KDAUFTRAGPOSTOUR.KDAUFTRAGNR,\
        KDAUFTRAGPOSTOUR.POSNR,\
        KDAUFTRAGPOSTOUR.DELIVERYBRANCHNO,\
        KDAUFTRAGPOSTOUR.DELIVERYDATE,\
        KDAUFTRAGPOSTOUR.DELIVERYTIME,\
        KDAUFTRAGPOSTOUR.TOURID,\
        KDAUFTRAGPOSTOUR.DEPARTUREDATE,\
        KDAUFTRAGPOSTOUR.DEPARTURETIME,\
        KDAUFTRAGPOSTOUR.DRIVINGDURATION,\
        KDAUFTRAGPOSTOUR.DELIVERYTIMEBUFFER,\
        KDAUFTRAGPOSTOUR.IBTTOURID,\
        KDAUFTRAGPOSTOUR.IBTCUSTOMERNO,\
        KDAUFTRAGPOSTOUR.IBTTYPE,\
        KDAUFTRAGPOSTOUR.DAYIBT,\
        KDAUFTRAGPOSTOUR.IBTTOURDATE
#define KDAUFTRAGPOSTOUR_LISTE_390 \
        KDAUFTRAGNR,\
        POSNR,\
        DELIVERYBRANCHNO,\
        DELIVERYDATE,\
        DELIVERYTIME,\
        TOURID,\
        DEPARTUREDATE,\
        DEPARTURETIME,\
        DRIVINGDURATION,\
        DELIVERYTIMEBUFFER,\
        IBTTOURID,\
        IBTCUSTOMERNO,\
        IBTTYPE,\
        DAYIBT,\
        IBTTOURDATE
#define KDAUFTRAGPOSTOUR_PLISTE \
        "KDAUFTRAGPOSTOUR.KDAUFTRAGNR,"\
        "KDAUFTRAGPOSTOUR.POSNR,"\
        "KDAUFTRAGPOSTOUR.DELIVERYBRANCHNO,"\
        "KDAUFTRAGPOSTOUR.DELIVERYDATE,"\
        "KDAUFTRAGPOSTOUR.DELIVERYTIME,"\
        "KDAUFTRAGPOSTOUR.TOURID,"\
        "KDAUFTRAGPOSTOUR.DEPARTUREDATE,"\
        "KDAUFTRAGPOSTOUR.DEPARTURETIME,"\
        "KDAUFTRAGPOSTOUR.DRIVINGDURATION,"\
        "KDAUFTRAGPOSTOUR.DELIVERYTIMEBUFFER,"\
        "KDAUFTRAGPOSTOUR.IBTTOURID,"\
        "KDAUFTRAGPOSTOUR.IBTCUSTOMERNO,"\
        "KDAUFTRAGPOSTOUR.IBTTYPE,"\
        "KDAUFTRAGPOSTOUR.DAYIBT,"\
        "KDAUFTRAGPOSTOUR.IBTTOURDATE"
#define KDAUFTRAGPOSTOUR_PELISTE \
        "KDAUFTRAGNR,"\
        "POSNR,"\
        "DELIVERYBRANCHNO,"\
        "DELIVERYDATE,"\
        "DELIVERYTIME,"\
        "TOURID,"\
        "DEPARTUREDATE,"\
        "DEPARTURETIME,"\
        "DRIVINGDURATION,"\
        "DELIVERYTIMEBUFFER,"\
        "IBTTOURID,"\
        "IBTCUSTOMERNO,"\
        "IBTTYPE,"\
        "DAYIBT,"\
        "IBTTOURDATE"
#define KDAUFTRAGPOSTOUR_UPDLISTE \
        "KDAUFTRAGNR=?,"\
        "POSNR=?,"\
        "DELIVERYBRANCHNO=?,"\
        "DELIVERYDATE=?,"\
        "DELIVERYTIME=?,"\
        "TOURID=?,"\
        "DEPARTUREDATE=?,"\
        "DEPARTURETIME=?,"\
        "DRIVINGDURATION=?,"\
        "DELIVERYTIMEBUFFER=?,"\
        "IBTTOURID=?,"\
        "IBTCUSTOMERNO=?,"\
        "IBTTYPE=?,"\
        "DAYIBT=?,"\
        "IBTTOURDATE=?"
/* SqlMacros-Define of KDAUFTRAGPOSTOUR ***************************************/

#define KDAUFTRAGPOSTOUR_ZEIGER(x) \
        :x->KDAUFTRAGNR,\
        :x->POSNR,\
        :x->DELIVERYBRANCHNO,\
        :x->DELIVERYDATE,\
        :x->DELIVERYTIME,\
        :x->TOURID,\
        :x->DEPARTUREDATE,\
        :x->DEPARTURETIME,\
        :x->DRIVINGDURATION,\
        :x->DELIVERYTIMEBUFFER,\
        :x->IBTTOURID,\
        :x->IBTCUSTOMERNO,\
        :x->IBTTYPE,\
        :x->DAYIBT,\
        :x->IBTTOURDATE
#define KDAUFTRAGPOSTOUR_ZEIGERSEL(x) \
        :x->KDAUFTRAGNR,\
        :x->POSNR,\
        :x->DELIVERYBRANCHNO,\
        :x->DELIVERYDATE,\
        :x->DELIVERYTIME,\
        :x->TOURID,\
        :x->DEPARTUREDATE,\
        :x->DEPARTURETIME,\
        :x->DRIVINGDURATION,\
        :x->DELIVERYTIMEBUFFER,\
        :x->IBTTOURID,\
        :x->IBTCUSTOMERNO,\
        :x->IBTTYPE,\
        :x->DAYIBT,\
        :x->IBTTOURDATE
#define KDAUFTRAGPOSTOUR_UPDATE(x) \
        KDAUFTRAGPOSTOUR.KDAUFTRAGNR=:x->KDAUFTRAGNR,\
        KDAUFTRAGPOSTOUR.POSNR=:x->POSNR,\
        KDAUFTRAGPOSTOUR.DELIVERYBRANCHNO=:x->DELIVERYBRANCHNO,\
        KDAUFTRAGPOSTOUR.DELIVERYDATE=:x->DELIVERYDATE,\
        KDAUFTRAGPOSTOUR.DELIVERYTIME=:x->DELIVERYTIME,\
        KDAUFTRAGPOSTOUR.TOURID=:x->TOURID,\
        KDAUFTRAGPOSTOUR.DEPARTUREDATE=:x->DEPARTUREDATE,\
        KDAUFTRAGPOSTOUR.DEPARTURETIME=:x->DEPARTURETIME,\
        KDAUFTRAGPOSTOUR.DRIVINGDURATION=:x->DRIVINGDURATION,\
        KDAUFTRAGPOSTOUR.DELIVERYTIMEBUFFER=:x->DELIVERYTIMEBUFFER,\
        KDAUFTRAGPOSTOUR.IBTTOURID=:x->IBTTOURID,\
        KDAUFTRAGPOSTOUR.IBTCUSTOMERNO=:x->IBTCUSTOMERNO,\
        KDAUFTRAGPOSTOUR.IBTTYPE=:x->IBTTYPE,\
        KDAUFTRAGPOSTOUR.DAYIBT=:x->DAYIBT,\
        KDAUFTRAGPOSTOUR.IBTTOURDATE=:x->IBTTOURDATE
/* SqlMacros390-Define of KDAUFTRAGPOSTOUR ************************************/

#define KDAUFTRAGPOSTOUR_ZEIGER_390 \
        :KDAUFTRAGNR,\
        :POSNR,\
        :DELIVERYBRANCHNO,\
        :DELIVERYDATE,\
        :DELIVERYTIME,\
        :TOURID,\
        :DEPARTUREDATE,\
        :DEPARTURETIME,\
        :DRIVINGDURATION,\
        :DELIVERYTIMEBUFFER,\
        :IBTTOURID,\
        :IBTCUSTOMERNO,\
        :IBTTYPE,\
        :DAYIBT,\
        :IBTTOURDATE
#define KDAUFTRAGPOSTOUR_UPDATE_390 \
        KDAUFTRAGNR=:KDAUFTRAGNR,\
        POSNR=:POSNR,\
        DELIVERYBRANCHNO=:DELIVERYBRANCHNO,\
        DELIVERYDATE=:DELIVERYDATE,\
        DELIVERYTIME=:DELIVERYTIME,\
        TOURID=:TOURID,\
        DEPARTUREDATE=:DEPARTUREDATE,\
        DEPARTURETIME=:DEPARTURETIME,\
        DRIVINGDURATION=:DRIVINGDURATION,\
        DELIVERYTIMEBUFFER=:DELIVERYTIMEBUFFER,\
        IBTTOURID=:IBTTOURID,\
        IBTCUSTOMERNO=:IBTCUSTOMERNO,\
        IBTTYPE=:IBTTYPE,\
        DAYIBT=:DAYIBT,\
        IBTTOURDATE=:IBTTOURDATE
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of KDAUFTRAGPOSTOUR ****************************************/

#ifndef TRANSCLASS
typedef struct N_KDAUFTRAGPOSTOUR {
    long KDAUFTRAGNR;
    long POSNR;
    short DELIVERYBRANCHNO;
    long DELIVERYDATE;
    short DELIVERYTIME;
    char TOURID[7];
    long DEPARTUREDATE;
    short DEPARTURETIME;
    long DRIVINGDURATION;
    short DELIVERYTIMEBUFFER;
    char IBTTOURID[7];
    long IBTCUSTOMERNO;
    short IBTTYPE;
    short DAYIBT;
    long IBTTOURDATE;
} kdauftragpostourS;
#else /* TRANSCLASS */
typedef struct N_KDAUFTRAGPOSTOUR {
    long KDAUFTRAGNR;
    long POSNR;
    short DELIVERYBRANCHNO;
    long DELIVERYDATE;
    short DELIVERYTIME;
    char TOURID[7];
    long DEPARTUREDATE;
    short DEPARTURETIME;
    long DRIVINGDURATION;
    short DELIVERYTIMEBUFFER;
    char IBTTOURID[7];
    long IBTCUSTOMERNO;
    short IBTTYPE;
    short DAYIBT;
    long IBTTOURDATE;

    bool operator == (const N_KDAUFTRAGPOSTOUR& right) const {
        return (
            KDAUFTRAGNR == right.KDAUFTRAGNR &&
            POSNR == right.POSNR &&
            DELIVERYBRANCHNO == right.DELIVERYBRANCHNO &&
            DELIVERYDATE == right.DELIVERYDATE &&
            DELIVERYTIME == right.DELIVERYTIME &&
            !strcmp(TOURID, right.TOURID) &&
            DEPARTUREDATE == right.DEPARTUREDATE &&
            DEPARTURETIME == right.DEPARTURETIME &&
            DRIVINGDURATION == right.DRIVINGDURATION &&
            DELIVERYTIMEBUFFER == right.DELIVERYTIMEBUFFER &&
            !strcmp(IBTTOURID, right.IBTTOURID) &&
            IBTCUSTOMERNO == right.IBTCUSTOMERNO &&
            IBTTYPE == right.IBTTYPE &&
            DAYIBT == right.DAYIBT &&
            IBTTOURDATE == right.IBTTOURDATE
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        KDAUFTRAGNR = 0;
        POSNR = 0;
        DELIVERYBRANCHNO = 0;
        DELIVERYDATE = 0;
        DELIVERYTIME = 0;
        strcpy(TOURID, " " );
        DEPARTUREDATE = 0;
        DEPARTURETIME = 0;
        DRIVINGDURATION = 0;
        DELIVERYTIMEBUFFER = 0;
        strcpy(IBTTOURID, " " );
        IBTCUSTOMERNO = 0;
        IBTTYPE = 0;
        DAYIBT = 0;
        IBTTOURDATE = 0;
#endif
    }
} kdauftragpostourS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of KDAUFTRAGPOSTOUR **********************************/

struct S_KDAUFTRAGPOSTOUR {
    char KDAUFTRAGNR[11];
    char POSNR[11];
    char DELIVERYBRANCHNO[7];
    char DELIVERYDATE[11];
    char DELIVERYTIME[7];
    char TOURID[6 + 1];
    char DEPARTUREDATE[11];
    char DEPARTURETIME[7];
    char DRIVINGDURATION[11];
    char DELIVERYTIMEBUFFER[7];
    char IBTTOURID[6 + 1];
    char IBTCUSTOMERNO[11];
    char IBTTYPE[7];
    char DAYIBT[7];
    char IBTTOURDATE[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of KDAUFTRAGPOSTOUR *****************/

struct O_KDAUFTRAGPOSTOUR {
    char KDAUFTRAGNR[11];
    char POSNR[11];
    char DELIVERYBRANCHNO[7];
    char DELIVERYDATE[11];
    char DELIVERYTIME[7];
    char TOURID[6];
    char DEPARTUREDATE[11];
    char DEPARTURETIME[7];
    char DRIVINGDURATION[11];
    char DELIVERYTIMEBUFFER[7];
    char IBTTOURID[6];
    char IBTCUSTOMERNO[11];
    char IBTTYPE[7];
    char DAYIBT[7];
    char IBTTOURDATE[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of KDAUFTRAGPOSTOUR ****************************/

struct C_KDAUFTRAGPOSTOUR {
    long KDAUFTRAGNR;
    long POSNR;
    short DELIVERYBRANCHNO;
    long DELIVERYDATE;
    short DELIVERYTIME;
    char TOURID[7];
    long DEPARTUREDATE;
    short DEPARTURETIME;
    long DRIVINGDURATION;
    short DELIVERYTIMEBUFFER;
    char IBTTOURID[7];
    long IBTCUSTOMERNO;
    short IBTTYPE;
    short DAYIBT;
    long IBTTOURDATE;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of KDAUFTRAGPOSTOUR **************************/

struct I_KDAUFTRAGPOSTOUR {
    short KDAUFTRAGNR;
    short POSNR;
    short DELIVERYBRANCHNO;
    short DELIVERYDATE;
    short DELIVERYTIME;
    short TOURID;
    short DEPARTUREDATE;
    short DEPARTURETIME;
    short DRIVINGDURATION;
    short DELIVERYTIMEBUFFER;
    short IBTTOURID;
    short IBTCUSTOMERNO;
    short IBTTYPE;
    short DAYIBT;
    short IBTTOURDATE;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of KDAUFTRAGPOSTOUR ************************************/

#if defined (BUF_DESC)
static struct buf_desc KDAUFTRAGPOSTOUR_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc KDAUFTRAGPOSTOUR_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* description for datatypes of KDAUFTRAGPOSTOUR ******************************/

 #define KDAUFTRAGPOSTOUR_S390 \
         long KDAUFTRAGNR; \
         long POSNR; \
         short DELIVERYBRANCHNO; \
         long DELIVERYDATE; \
         short DELIVERYTIME; \
         char TOURID[7]; \
         long DEPARTUREDATE; \
         short DEPARTURETIME; \
         long DRIVINGDURATION; \
         short DELIVERYTIMEBUFFER; \
         char IBTTOURID[7]; \
         long IBTCUSTOMERNO; \
         short IBTTYPE; \
         short DAYIBT; \
         long IBTTOURDATE; \



/* Copy-Function Struct to single Data KDAUFTRAGPOSTOUR ***********************/

 #define KDAUFTRAGPOSTOUR_S390_COPY_TO_SINGLE(_x_) \
         KDAUFTRAGNR=_x_->KDAUFTRAGNR;\
         POSNR=_x_->POSNR;\
         DELIVERYBRANCHNO=_x_->DELIVERYBRANCHNO;\
         DELIVERYDATE=_x_->DELIVERYDATE;\
         DELIVERYTIME=_x_->DELIVERYTIME;\
          strcpy(TOURID,_x_->TOURID);\
         DEPARTUREDATE=_x_->DEPARTUREDATE;\
         DEPARTURETIME=_x_->DEPARTURETIME;\
         DRIVINGDURATION=_x_->DRIVINGDURATION;\
         DELIVERYTIMEBUFFER=_x_->DELIVERYTIMEBUFFER;\
          strcpy(IBTTOURID,_x_->IBTTOURID);\
         IBTCUSTOMERNO=_x_->IBTCUSTOMERNO;\
         IBTTYPE=_x_->IBTTYPE;\
         DAYIBT=_x_->DAYIBT;\
         IBTTOURDATE=_x_->IBTTOURDATE;\

 #define KDAUFTRAGPOSTOUR_S390_COPY_TO_STRUCT(_x_) \
          _x_->KDAUFTRAGNR=KDAUFTRAGNR;\
          _x_->POSNR=POSNR;\
          _x_->DELIVERYBRANCHNO=DELIVERYBRANCHNO;\
          _x_->DELIVERYDATE=DELIVERYDATE;\
          _x_->DELIVERYTIME=DELIVERYTIME;\
          strcpy(_x_->TOURID,TOURID);\
          _x_->DEPARTUREDATE=DEPARTUREDATE;\
          _x_->DEPARTURETIME=DEPARTURETIME;\
          _x_->DRIVINGDURATION=DRIVINGDURATION;\
          _x_->DELIVERYTIMEBUFFER=DELIVERYTIMEBUFFER;\
          strcpy(_x_->IBTTOURID,IBTTOURID);\
          _x_->IBTCUSTOMERNO=IBTCUSTOMERNO;\
          _x_->IBTTYPE=IBTTYPE;\
          _x_->DAYIBT=DAYIBT;\
          _x_->IBTTOURDATE=IBTTOURDATE;\



/* FunctionNumber-Define of kdauftragpostour **********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of kdauftragpostour ******************************/


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

class CKDAUFTRAGPOSTOUR : public ppDadeVirtual {
public:
    kdauftragpostourS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<kdauftragpostourS> lst; // class list

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
                     vector< kdauftragpostourS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     kdauftragpostourS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< kdauftragpostourS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<kdauftragpostourS>::iterator
                 beginList() { return lst.begin(); }
    vector<kdauftragpostourS>::iterator
                 endList  () { return lst.end  (); }

    long         GetKdauftragnr() const { return s.KDAUFTRAGNR; }
    long         GetPosnr() const { return s.POSNR; }
    short        GetDeliverybranchno() const { return s.DELIVERYBRANCHNO; }
    long         GetDeliverydate() const { return s.DELIVERYDATE; }
    short        GetDeliverytime() const { return s.DELIVERYTIME; }
    const char*  GetTourid(ppString & t) const { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
    long         GetDeparturedate() const { return s.DEPARTUREDATE; }
    short        GetDeparturetime() const { return s.DEPARTURETIME; }
    long         GetDrivingduration() const { return s.DRIVINGDURATION; }
    short        GetDeliverytimebuffer() const { return s.DELIVERYTIMEBUFFER; }
    const char*  GetIbttourid(ppString & t) const { t = s.IBTTOURID; t.erasespace(ppString::END); return t.c_str(); }
    long         GetIbtcustomerno() const { return s.IBTCUSTOMERNO; }
    short        GetIbttype() const { return s.IBTTYPE; }
    short        GetDayibt() const { return s.DAYIBT; }
    long         GetIbttourdate() const { return s.IBTTOURDATE; }

    const kdauftragpostourS &
                 GetStruct() const { return s; }
    void         SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
    void         SetPosnr(long t) { s.POSNR = t; }
    void         SetDeliverybranchno(short t) { s.DELIVERYBRANCHNO = t; }
    void         SetDeliverydate(long t) { s.DELIVERYDATE = t; }
    void         SetDeliverytime(short t) { s.DELIVERYTIME = t; }
    void         SetTourid(const ppString & t) { ppGStrCopy(s.TOURID, t.c_str(), L_KDAUFTRAGPOSTOUR_TOURID); }
    void         SetDeparturedate(long t) { s.DEPARTUREDATE = t; }
    void         SetDeparturetime(short t) { s.DEPARTURETIME = t; }
    void         SetDrivingduration(long t) { s.DRIVINGDURATION = t; }
    void         SetDeliverytimebuffer(short t) { s.DELIVERYTIMEBUFFER = t; }
    void         SetIbttourid(const ppString & t) { ppGStrCopy(s.IBTTOURID, t.c_str(), L_KDAUFTRAGPOSTOUR_IBTTOURID); }
    void         SetIbtcustomerno(long t) { s.IBTCUSTOMERNO = t; }
    void         SetIbttype(short t) { s.IBTTYPE = t; }
    void         SetDayibt(short t) { s.DAYIBT = t; }
    void         SetIbttourdate(long t) { s.IBTTOURDATE = t; }

    void         SetStruct(const kdauftragpostourS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CKDAUFTRAGPOSTOUR() {
        ::buf_default((void *)&s, KDAUFTRAGPOSTOUR_BES, KDAUFTRAGPOSTOUR_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CKDAUFTRAGPOSTOUR() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, KDAUFTRAGPOSTOUR_BES, KDAUFTRAGPOSTOUR_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, KDAUFTRAGPOSTOUR_BES, (int)KDAUFTRAGPOSTOUR_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, KDAUFTRAGPOSTOUR_BES, (int)KDAUFTRAGPOSTOUR_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_KDAUFTRAGPOSTOUR & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.TOURID);
        ppGStripLast(d.IBTTOURID);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, KDAUFTRAGPOSTOUR_BES, (int)KDAUFTRAGPOSTOUR_ANZ, error_msg);
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
/* CreateSqlStatement of KDAUFTRAGPOSTOUR *************************************/

 #define KDAUFTRAGPOSTOUR_CREATE(x) EXEC SQL create table x (\
         KDAUFTRAGNR integer default 0 not null,\
         POSNR integer default 0 not null,\
         DELIVERYBRANCHNO smallint default 0 not null,\
         DELIVERYDATE integer default 0 not null,\
         DELIVERYTIME smallint default 0 not null,\
         TOURID char(6) default " " not null,\
         DEPARTUREDATE integer default 0 not null,\
         DEPARTURETIME smallint default 0 not null,\
         DRIVINGDURATION integer default 0 not null,\
         DELIVERYTIMEBUFFER smallint default 0 not null,\
         IBTTOURID char(6) default " " not null,\
         IBTCUSTOMERNO integer default 0 not null,\
         IBTTYPE smallint default 0 not null,\
         DAYIBT smallint default 0 not null,\
         IBTTOURDATE integer default 0 not null) in ksc extent size 10980 next size 1100 lock mode row;



/* CreateIndexStatement of KDAUFTRAGPOSTOUR ***********************************/

 #define KDAUFTRAGPOSTOUR_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index kdauftragpostouridx on _X_(\
              kdauftragnr,\
              posnr,\
              DeliveryBranchNo ) in ksc;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of KDAUFTRAGPOSTOUR ***********************************/

 #define KDAUFTRAGPOSTOUR_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index kdauftragpostouridx;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
