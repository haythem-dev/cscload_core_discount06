#ifndef __PP_KRITIK_H_
#define __PP_KRITIK_H_

/******************************************************************************/
/* c:\Marathon\orderentry\csc_core_applications\src\aapserv\KRITIK ************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of KRITIK ****************************************************/

#define L_KRITIK_IDFNR 11
#define L_KRITIK_DATUM 11
#define L_KRITIK_REGIONNR 11
#define L_KRITIK_ZEIT 11
#define L_KRITIK_UID 11
#define L_KRITIK_TITEL 30
#define L_KRITIK_KRITIKNR 11
#define L_KRITIK_VERTRIEBSZENTRUMNR 5
#define L_KRITIK_KUNDENNR 11
#define L_KRITIK_FILIALNR 5
#define L_KRITIK_KRITIKLEVEL 5
#define L_KRITIK_NAMEAPO 40
#define L_KRITIK_ORT 30
#define L_KRITIK_USERNAME64 64
#define L_KRITIK_DIVISIONNAME 20
#define L_KRITIK_KRITIKTEXT 2048
#define L_KRITIK_CALLBACKNO 11
#define L_KRITIK_REFERENCE 150
#define L_KRITIK_CALLBACKSTATUSNAME 50

/* Length/Count-Define of KRITIK **********************************************/

#define LS_KRITIK_IDFNR 10 + 1
#define LS_KRITIK_DATUM 10 + 1
#define LS_KRITIK_REGIONNR 10 + 1
#define LS_KRITIK_ZEIT 10 + 1
#define LS_KRITIK_UID 10 + 1
#define LS_KRITIK_TITEL 30 + 1
#define LS_KRITIK_KRITIKNR 10 + 1
#define LS_KRITIK_VERTRIEBSZENTRUMNR 5 + 1
#define LS_KRITIK_KUNDENNR 10 + 1
#define LS_KRITIK_FILIALNR 5 + 1
#define LS_KRITIK_KRITIKLEVEL 5 + 1
#define LS_KRITIK_NAMEAPO 40 + 1
#define LS_KRITIK_ORT 30 + 1
#define LS_KRITIK_USERNAME64 64 + 1
#define LS_KRITIK_DIVISIONNAME 20 + 1
#define LS_KRITIK_KRITIKTEXT 2048 + 1
#define LS_KRITIK_CALLBACKNO 11 + 1
#define LS_KRITIK_REFERENCE 150 + 1
#define LS_KRITIK_CALLBACKSTATUSNAME 50 + 1

#define KRITIKIDFNR 0
#define KRITIKDATUM 1
#define KRITIKREGIONNR 2
#define KRITIKZEIT 3
#define KRITIKUID 4
#define KRITIKTITEL 5
#define KRITIKKRITIKNR 6
#define KRITIKVERTRIEBSZENTRUMNR 7
#define KRITIKKUNDENNR 8
#define KRITIKFILIALNR 9
#define KRITIKKRITIKLEVEL 10
#define KRITIKNAMEAPO 11
#define KRITIKORT 12
#define KRITIKUSERNAME64 13
#define KRITIKDIVISIONNAME 14
#define KRITIKKRITIKTEXT 15
#define KRITIKCALLBACKNO 16
#define KRITIKCALLBACKSTATUSNAME 17

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define KRITIK_H
#define KRITIK_ANZ ( sizeof(KRITIK_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of KRITIK ********************************************************/

#define KRITIK_LISTE \
        KDKRITIK.IDFNR,\
        KDKRITIK.DATUM,\
        REGIONARTEN.REGIONNR,\
        KDKRITIK.ZEIT,\
        KDKRITIK.UID,\
        KDKRITIK.TITEL,\
        KDKRITIK.KRITIKNR,\
        KDKRITIK.VERTRIEBSZENTRUMNR,\
        KDKRITIK.KUNDENNR,\
        KDKRITIK.FILIALNR,\
        KDKRITIK.KRITIKLEVEL,\
        KUNDE.NAMEAPO,\
        KUNDE.ORT,\
        AADUMMY.USERNAME64,\
        CALLBACKDIVISION.DIVISIONNAME,\
        KDKRITIKPOS.KRITIKTEXT,\
        CALLBACKITEMS.CALLBACKNO,\
        CALLBACKITEMS.REFERENCE,\
        CALLBACKSTATUS.CALLBACKSTATUSNAME
#define KRITIK_LISTE_390 \
        IDFNR,\
        DATUM,\
        REGIONNR,\
        ZEIT,\
        UID,\
        TITEL,\
        KRITIKNR,\
        VERTRIEBSZENTRUMNR,\
        KUNDENNR,\
        FILIALNR,\
        KRITIKLEVEL,\
        NAMEAPO,\
        ORT,\
        USERNAME64,\
        DIVISIONNAME,\
        KRITIKTEXT,\
        CALLBACKNO,\
        REFERENCE,\
        CALLBACKSTATUSNAME
#define KRITIK_PLISTE \
        "KDKRITIK.IDFNR,"\
        "KDKRITIK.DATUM,"\
        "KDKRITIK.ZEIT,"\
        "KDKRITIK.UID,"\
        "KDKRITIK.TITEL,"\
        "KDKRITIK.KRITIKNR,"\
        "KDKRITIK.VERTRIEBSZENTRUMNR,"\
        "KDKRITIK.KUNDENNR,"\
        "KDKRITIK.FILIALNR,"\
        "KDKRITIK.KRITIKLEVEL,"\
        "KUNDE.NAMEAPO,"\
        "KUNDE.ORT,"\
        "AADUMMY.USERNAME64,"\
        "CALLBACKDIVISION.DIVISIONNAME,"\
        "KDKRITIKPOS.KRITIKTEXT,"\
        "CALLBACKITEMS.CALLBACKNO,"\
        "CALLBACKITEMS.REFERENCE,"\
        "CALLBACKSTATUS.CALLBACKSTATUSNAME"
#define KRITIK_PELISTE \
        "IDFNR,"\
        "DATUM,"\
        "ZEIT,"\
        "UID,"\
        "TITEL,"\
        "KRITIKNR,"\
        "VERTRIEBSZENTRUMNR,"\
        "KUNDENNR,"\
        "FILIALNR,"\
        "KRITIKLEVEL,"\
        "NAMEAPO,"\
        "ORT,"\
        "USERNAME64,"\
        "DIVISIONNAME,"\
        "KRITIKTEXT,"\
        "CALLBACKNO,"\
        "REFERENCE,"\
        "CALLBACKSTATUSNAME"
#define KRITIK_UPDLISTE \
        "IDFNR=?,"\
        "DATUM=?,"\
        "ZEIT=?,"\
        "UID=?,"\
        "TITEL=?,"\
        "KRITIKNR=?,"\
        "VERTRIEBSZENTRUMNR=?,"\
        "KUNDENNR=?,"\
        "FILIALNR=?,"\
        "KRITIKLEVEL=?,"\
        "NAMEAPO=?,"\
        "ORT=?,"\
        "USERNAME64=?,"\
        "DIVISIONNAME=?,"\
        "KRITIKTEXT=?,"\
        "CALLBACKNO=?,"\
        "REFERENCE=?,"\
        "CALLBACKSTATUSNAME=?"
/* SqlMacros-Define of KRITIK *************************************************/

#define KRITIK_ZEIGER(x) \
        :x->IDFNR,\
        :x->DATUM,\
        :x->ZEIT,\
        :x->UID,\
        :x->TITEL,\
        :x->KRITIKNR,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->FILIALNR,\
        :x->KRITIKLEVEL,\
        :x->NAMEAPO,\
        :x->ORT,\
        :x->USERNAME64,\
        :x->DIVISIONNAME,\
        :x->KRITIKTEXT,\
        :x->CALLBACKNO,\
        :x->REFERENCE,\
        :x->CALLBACKSTATUSNAME
#define KRITIK_ZEIGERSEL(x) \
        :x->IDFNR,\
        :x->DATUM,\
        :x->ZEIT,\
        :x->UID,\
        :x->TITEL,\
        :x->KRITIKNR,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->FILIALNR,\
        :x->KRITIKLEVEL,\
        :x->NAMEAPO,\
        :x->ORT,\
        :x->USERNAME64,\
        :x->DIVISIONNAME,\
        :x->KRITIKTEXT,\
        :x->CALLBACKNO,\
        :x->REFERENCE,\
        :x->CALLBACKSTATUSNAME
#define KRITIK_UPDATE(x) \
        KDKRITIK.IDFNR=:x->IDFNR,\
        KDKRITIK.DATUM=:x->DATUM,\
        KDKRITIK.ZEIT=:x->ZEIT,\
        KDKRITIK.UID=:x->UID,\
        KDKRITIK.TITEL=:x->TITEL,\
        KDKRITIK.KRITIKNR=:x->KRITIKNR,\
        KDKRITIK.VERTRIEBSZENTRUMNR=:x->VERTRIEBSZENTRUMNR,\
        KDKRITIK.KUNDENNR=:x->KUNDENNR,\
        KDKRITIK.FILIALNR=:x->FILIALNR,\
        KDKRITIK.KRITIKLEVEL=:x->KRITIKLEVEL,\
        KUNDE.NAMEAPO=:x->NAMEAPO,\
        KUNDE.ORT=:x->ORT,\
        AADUMMY.USERNAME64=:x->USERNAME64,\
        CALLBACKDIVISION.DIVISIONNAME=:x->DIVISIONNAME,\
        KDKRITIKPOS.KRITIKTEXT=:x->KRITIKTEXT,\
        CALLBACKITEMS.CALLBACKNO=:x->CALLBACKNO,\
        CALLBACKITEMS.REFERENCE=:x->REFERENCE,\
        CALLBACKSTATUS.CALLBACKSTATUSNAME=:x->CALLBACKSTATUSNAME
/* SqlMacros390-Define of KRITIK **********************************************/

#define KRITIK_ZEIGER_390 \
        :IDFNR,\
        :DATUM,\
        :REGIONNR,\
        :ZEIT,\
        :UID,\
        :TITEL,\
        :KRITIKNR,\
        :VERTRIEBSZENTRUMNR,\
        :KUNDENNR,\
        :FILIALNR,\
        :KRITIKLEVEL,\
        :NAMEAPO,\
        :ORT,\
        :USERNAME64,\
        :DIVISIONNAME,\
        :KRITIKTEXT,\
        :CALLBACKNO,\
        :REFERENCE,\
        :CALLBACKSTATUSNAME
#define KRITIK_UPDATE_390 \
        IDFNR=:IDFNR,\
        DATUM=:DATUM,\
        ZEIT=:ZEIT,\
        UID=:UID,\
        TITEL=:TITEL,\
        KRITIKNR=:KRITIKNR,\
        VERTRIEBSZENTRUMNR=:VERTRIEBSZENTRUMNR,\
        KUNDENNR=:KUNDENNR,\
        FILIALNR=:FILIALNR,\
        KRITIKLEVEL=:KRITIKLEVEL,\
        NAMEAPO=:NAMEAPO,\
        ORT=:ORT,\
        USERNAME64=:USERNAME64,\
        DIVISIONNAME=:DIVISIONNAME,\
        KRITIKTEXT=:KRITIKTEXT,\
        CALLBACKNO=:CALLBACKNO,\
        REFERENCE=:REFERENCE,\
        CALLBACKSTATUSNAME=:CALLBACKSTATUSNAME
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of KRITIK **************************************************/

#ifndef TRANSCLASS
typedef struct N_KRITIK {
    long IDFNR;
    long DATUM;
    long REGIONNR;
    long ZEIT;
    long UID;
    char TITEL[LS_KRITIK_TITEL];
    long KRITIKNR;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    short FILIALNR;
    short KRITIKLEVEL;
    char NAMEAPO[LS_KRITIK_NAMEAPO];
    char ORT[LS_KRITIK_ORT];
    char USERNAME64[LS_KRITIK_USERNAME64];
    char DIVISIONNAME[LS_KRITIK_DIVISIONNAME];
    char KRITIKTEXT[LS_KRITIK_KRITIKTEXT];
    long CALLBACKNO;
    char REFERENCE[LS_KRITIK_REFERENCE];
    char CALLBACKSTATUSNAME[LS_KRITIK_CALLBACKSTATUSNAME];
    long FETCH_REL;
} kritikS;
#else /* TRANSCLASS */
typedef struct N_KRITIK {
    long IDFNR;
    long DATUM;
    long REGIONNR;
    long ZEIT;
    long UID;
    char TITEL[LS_KRITIK_TITEL];
    long KRITIKNR;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    short FILIALNR;
    short KRITIKLEVEL;
    char NAMEAPO[LS_KRITIK_NAMEAPO];
    char ORT[LS_KRITIK_ORT];
    char USERNAME64[LS_KRITIK_USERNAME64];
    char DIVISIONNAME[LS_KRITIK_DIVISIONNAME];
    char KRITIKTEXT[LS_KRITIK_KRITIKTEXT];
    long CALLBACKNO;
    char REFERENCE[LS_KRITIK_REFERENCE];
    char CALLBACKSTATUSNAME[LS_KRITIK_CALLBACKSTATUSNAME];
    long FETCH_REL;
    bool operator == (const N_KRITIK& right) const {
        return (
            IDFNR == right.IDFNR &&
            DATUM == right.DATUM &&
            REGIONNR == right.REGIONNR &&
            ZEIT == right.ZEIT &&
            UID == right.UID &&
            !strcmp(TITEL, right.TITEL) &&
            KRITIKNR == right.KRITIKNR &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            FILIALNR == right.FILIALNR &&
            KRITIKLEVEL == right.KRITIKLEVEL &&
            !strcmp(NAMEAPO, right.NAMEAPO) &&
            !strcmp(ORT, right.ORT) &&
            !strcmp(USERNAME64, right.USERNAME64) &&
            !strcmp(DIVISIONNAME, right.DIVISIONNAME) &&
            !strcmp(KRITIKTEXT, right.KRITIKTEXT) &&
            CALLBACKNO == right.CALLBACKNO &&
            !strcmp(REFERENCE, right.REFERENCE) &&
            !strcmp(CALLBACKSTATUSNAME, right.CALLBACKSTATUSNAME)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        IDFNR = 0;
        DATUM = 0;
        REGIONNR = 0;
        ZEIT = 0;
        UID = 0;
        strcpy(TITEL, " " );
        KRITIKNR = 0;
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        FILIALNR = 0;
        KRITIKLEVEL = 0;
        strcpy(NAMEAPO, " " );
        strcpy(ORT, " " );
        strcpy(USERNAME64, " " );
        strcpy(DIVISIONNAME, " ");
        strcpy(KRITIKTEXT, " ");
        FILIALNR = 0;
        strcpy(REFERENCE, "");
        strcpy(CALLBACKSTATUSNAME, " ");
#endif
    }
} kritikS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of KRITIK ********************************************/

struct S_KRITIK {
    char IDFNR[LS_KRITIK_IDFNR];
    char DATUM[LS_KRITIK_DATUM];
    char REGIONNR[LS_KRITIK_REGIONNR];
    char ZEIT[LS_KRITIK_ZEIT];
    char UID[LS_KRITIK_UID];
    char TITEL[LS_KRITIK_TITEL];
    char KRITIKNR[LS_KRITIK_KRITIKNR];
    char VERTRIEBSZENTRUMNR[LS_KRITIK_VERTRIEBSZENTRUMNR];
    char KUNDENNR[LS_KRITIK_KUNDENNR];
    char FILIALNR[LS_KRITIK_FILIALNR];
    char KRITIKLEVEL[LS_KRITIK_KRITIKLEVEL];
    char NAMEAPO[LS_KRITIK_NAMEAPO];
    char ORT[LS_KRITIK_ORT];
    char USERNAME64[LS_KRITIK_USERNAME64];
    char DIVISIONNAME[LS_KRITIK_DIVISIONNAME];
    char KRITIKTEXT[LS_KRITIK_KRITIKTEXT];
    char CALLBACKNO[LS_KRITIK_CALLBACKNO];
    char REFERENCE[LS_KRITIK_REFERENCE];
    char CALLBACKSTATUSNAME[LS_KRITIK_CALLBACKSTATUSNAME];
    char FETCH_REL[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of KRITIK ***************************/

struct O_KRITIK {
    char IDFNR[LS_KRITIK_IDFNR];
    char DATUM[LS_KRITIK_DATUM];
    char REGIONNR[LS_KRITIK_REGIONNR];
    char ZEIT[LS_KRITIK_ZEIT];
    char UID[LS_KRITIK_UID];
    char TITEL[LS_KRITIK_TITEL];
    char KRITIKNR[LS_KRITIK_KRITIKNR];
    char VERTRIEBSZENTRUMNR[LS_KRITIK_VERTRIEBSZENTRUMNR];
    char KUNDENNR[LS_KRITIK_KUNDENNR];
    char FILIALNR[LS_KRITIK_FILIALNR];
    char KRITIKLEVEL[LS_KRITIK_KRITIKLEVEL];
    char NAMEAPO[LS_KRITIK_NAMEAPO];
    char ORT[LS_KRITIK_ORT];
    char USERNAME64[LS_KRITIK_USERNAME64];
    char DIVISIONNAME[LS_KRITIK_DIVISIONNAME];
    char KRITIKTEXT[LS_KRITIK_KRITIKTEXT];
    char CALLBACKNO[LS_KRITIK_CALLBACKNO];
    char REFERENCE[LS_KRITIK_REFERENCE];
    char CALLBACKSTATUSNAME[LS_KRITIK_CALLBACKSTATUSNAME];
    char FETCH_REL[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of KRITIK **************************************/

struct C_KRITIK {
    long IDFNR;
    long DATUM;
    long REGIONNR;
    long ZEIT;
    long UID;
    char TITEL[LS_KRITIK_TITEL];
    long KRITIKNR;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    short FILIALNR;
    short KRITIKLEVEL;
    char NAMEAPO[LS_KRITIK_NAMEAPO];
    char ORT[LS_KRITIK_ORT];
    char USERNAME64[LS_KRITIK_USERNAME64];
    char DIVISIONNAME[LS_KRITIK_DIVISIONNAME];
    char KRITIKTEXT[LS_KRITIK_KRITIKTEXT];
    long CALLBACKNO;
    char REFERENCE[LS_KRITIK_REFERENCE];
    char CALLBACKSTATUSNAME[LS_KRITIK_CALLBACKSTATUSNAME];
    long FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of KRITIK ************************************/

struct I_KRITIK {
    short IDFNR;
    short DATUM;
    short REGIONNR;
    short ZEIT;
    short UID;
    short TITEL;
    short KRITIKNR;
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short FILIALNR;
    short KRITIKLEVEL;
    short NAMEAPO;
    short ORT;
    short USERNAME64;
    short DIVISIONNAME;
    short KRITIKTEXT;
    short CALLBACKNO;
    short REFERENCE;
    short CALLBACKSTATUSNAME;
    short FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of KRITIK **********************************************/

#if defined (BUF_DESC)
static struct buf_desc KRITIK_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 40, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 64, 0 },
   { TYP_C, 20, 0 },
   { TYP_C, 2048, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 150, 0 },
   { TYP_C, 50, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc KRITIK_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 40, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 64, 0 },
   { TYP_C, 20, 0 },
   { TYP_C, 2048, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 150, 0 },
   { TYP_C, 50, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* description for datatypes of KRITIK ****************************************/

 #define KRITIK_S390 \
         long IDFNR; \
         long DATUM; \
         long REGIONNR; \
         long ZEIT; \
         long UID; \
         char TITEL[31]; \
         long KRITIKNR; \
         short VERTRIEBSZENTRUMNR; \
         long KUNDENNR; \
         short FILIALNR; \
         short KRITIKLEVEL; \
         char NAMEAPO[41]; \
         char ORT[31]; \
         char USERNAME64[65]; \
         char DIVISIONNAME[21]; \
         char KRITIKTEXT[2049]; \
         long CALLBACKNO; \
         char REFERENCE[151]; \
         char CALLBACKSTATUSNAME[51]; \
         long FETCH_REL;



/* Copy-Function Struct to single Data KRITIK *********************************/

 #define KRITIK_S390_COPY_TO_SINGLE(_x_) \
         IDFNR=_x_->IDFNR;\
         DATUM=_x_->DATUM;\
         REGIONNR=_x_->REGIONNR;\
         ZEIT=_x_->ZEIT;\
         UID=_x_->UID;\
         strcpy(TITEL,_x_->TITEL);\
         KRITIKNR=_x_->KRITIKNR;\
         VERTRIEBSZENTRUMNR=_x_->VERTRIEBSZENTRUMNR;\
         KUNDENNR=_x_->KUNDENNR;\
         FILIALNR=_x_->FILIALNR;\
         KRITIKLEVEL=_x_->KRITIKLEVEL;\
         strcpy(NAMEAPO,_x_->NAMEAPO);\
         strcpy(ORT,_x_->ORT);\
         strcpy(USERNAME64,_x_->USERNAME64);\
         strcpy(DIVISIONNAME, _x_->DIVISIONNAME);\
         strcpy(KRITIKTEXT, _x_->KRITIKTEXT);\
         CALLBACKNO = _x_->CALLBACKNO;\
         strcpy(REFERENCE, _x_->REFERENCE);\
         strcpy(CALLBACKSTATUSNAME, _x_->CALLBACKSTATUSNAME);\
         FETCH_REL=_x_->FETCH_REL;\

 #define KRITIK_S390_COPY_TO_STRUCT(_x_) \
          _x_->IDFNR=IDFNR;\
          _x_->DATUM=DATUM;\
          _x_->REGIONNR=REGIONNR;\
          _x_->ZEIT=ZEIT;\
          _x_->UID=UID;\
          strcpy(_x_->TITEL,TITEL);\
          _x_->KRITIKNR=KRITIKNR;\
          _x_->VERTRIEBSZENTRUMNR=VERTRIEBSZENTRUMNR;\
          _x_->KUNDENNR=KUNDENNR;\
          _x_->FILIALNR=FILIALNR;\
          _x_->KRITIKLEVEL=KRITIKLEVEL;\
          strcpy(_x_->NAMEAPO,NAMEAPO);\
          strcpy(_x_->ORT,ORT);\
          strcpy(_x_->USERNAME64,USERNAME64);\
          strcpy(_x_->DIVISIONNAME,DIVISIONNAME);\
          strcpy(_x_->KRITIKTEXT,KRITIKTEXT);\
          _x_->CALLBACKNO=CALLBACKNO;\
          strcpy(_x_->REFERENCE,REFERENCE);\
          strcpy(_x_->CALLBACKSTATUSNAME,CALLBACKSTATUSNAME);\
          _x_->FETCH_REL=FETCH_REL;\



/* FunctionNumber-Define of KRITIK ********************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of KRITIK ****************************************/


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

class CKRITIK : public ppDadeVirtual {
public:
    kritikS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<kritikS> lst; // class list

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
                     vector< kritikS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     kritikS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< kritikS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<kritikS>::iterator
                 beginList() { return lst.begin(); }
    vector<kritikS>::iterator
                 endList  () { return lst.end  (); }

    long         GetIdfnr() const { return s.IDFNR; }
    long         GetDatum() const { return s.DATUM; }
    long         GetRegionnr() const { return s.REGIONNR; }
    long         GetZeit() const { return s.ZEIT; }
    long         GetUid() const { return s.UID; }
    const char*  GetTitel(ppString & t) const { t = s.TITEL; t.erasespace(ppString::END); return t.c_str(); }
    long         GetKritiknr() const { return s.KRITIKNR; }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    short        GetFilialnr() const { return s.FILIALNR; }
    short        GetKritiklevel() const { return s.KRITIKLEVEL; }
    const char*  GetNameapo(ppString & t) const { t = s.NAMEAPO; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetOrt(ppString & t) const { t = s.ORT; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetUsername64(ppString & t) const { t = s.USERNAME64; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetDivisionName(ppString& t) const { t = s.DIVISIONNAME; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetKritiktext(ppString& t) const { t = s.KRITIKTEXT; t.erasespace(ppString::END); return t.c_str(); }
    long         GetCallbackNo() const { return s.CALLBACKNO; }
    const char* GetReference(ppString& t) const { t = s.REFERENCE; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetCallbackStatusName(ppString& t) const { t = s.CALLBACKSTATUSNAME; t.erasespace(ppString::END); return t.c_str(); }

    const kritikS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetIdfnr(long t) { s.IDFNR = t; }
    void         SetDatum(long t) { s.DATUM = t; }
    void         SetRegionnr(long t) { s.REGIONNR = t; }
    void         SetZeit(long t) { s.ZEIT = t; }
    void         SetUid(long t) { s.UID = t; }
    void         SetTitel(const ppString & t) { ppGStrCopy(s.TITEL, t.c_str(), L_KRITIK_TITEL); }
    void         SetKritiknr(long t) { s.KRITIKNR = t; }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetKritiklevel(short t) { s.KRITIKLEVEL = t; }
    void         SetNameapo(const ppString & t) { ppGStrCopy(s.NAMEAPO, t.c_str(), L_KRITIK_NAMEAPO); }
    void         SetOrt(const ppString & t) { ppGStrCopy(s.ORT, t.c_str(), L_KRITIK_ORT); }
    void         SetUsername64(const ppString & t) { ppGStrCopy(s.USERNAME64, t.c_str(), L_KRITIK_USERNAME64); }
    void         SetDivisionName(const ppString& t) { ppGStrCopy(s.DIVISIONNAME, t.c_str(), L_KRITIK_DIVISIONNAME); }
    void         SetKritiktext(const ppString& t) { ppGStrCopy(s.KRITIKTEXT, t.c_str(), L_KRITIK_KRITIKTEXT); }
    void         SetCallbackNo(long t) { s.CALLBACKNO = t; }
    void         SetReference(const ppString& t) { ppGStrCopy(s.REFERENCE, t.c_str(), L_KRITIK_REFERENCE); }
    void         SetCallbackStatusName(const ppString& t) { ppGStrCopy(s.CALLBACKSTATUSNAME, t.c_str(), L_KRITIK_CALLBACKSTATUSNAME); }

    void         SetStruct(const kritikS & t) { s = t; }
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
    CKRITIK() {
        ::buf_default((void *)&s, KRITIK_BES, KRITIK_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CKRITIK() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, KRITIK_BES, KRITIK_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, KRITIK_BES, (int)KRITIK_ANZ, error_msg);
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
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, KRITIK_BES, (int)KRITIK_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, KRITIK_BES, (int)KRITIK_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_KRITIK & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.TITEL);
        ppGStripLast(d.NAMEAPO);
        ppGStripLast(d.ORT);
        ppGStripLast(d.USERNAME64);
        ppGStripLast(d.DIVISIONNAME);
        ppGStripLast(d.KRITIKTEXT);
        ppGStripLast(d.CALLBACKSTATUSNAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, KRITIK_BES, (int)KRITIK_ANZ, error_msg);
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
        CKRITIK c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, KRITIK_BES, (int)KRITIK_ANZ, error_msg);
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
/* CreateSqlStatement of KRITIK ***********************************************/

 #define KRITIK_CREATE(x) EXEC SQL create table x (\
         IDFNR integer default 0 not null,\
         DATUM integer default 0 not null,\
         REGIONNR integer default 0 not null,\
         ZEIT integer default 0 not null,\
         UID integer default 0 not null,\
         TITEL char(30) default " " not null,\
         KRITIKNR integer default 0 not null,\
         VERTRIEBSZENTRUMNR smallint default 0 not null,\
         KUNDENNR integer default 0 not null,\
         FILIALNR smallint default 0 not null,\
         KRITIKLEVEL smallint default 0 not null,\
         NAMEAPO char(40) default " " not null,\
         ORT char(30) default " " not null,\
         USERNAME64 varchar(64,0) default " " not null,\
         DIVISIONNAME char(20) default " " not null, \
         KRITIKTEXT char(2048) default " " not null, \
         CALLBACKNO integer default 0 not null, \
         CALLBACKSTATUSNAME char(50) default " " not null) extent size 784 next size 80 lock mode row;



/* CreateIndexStatement of KRITIK *********************************************/

 #define KRITIK_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_kdkritik_1 on _X_(\
              kritiknr );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index i_kdkritik_2 on _X_(\
              idfnr );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index i_kdkritik_3 on _X_(\
              datum );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of KRITIK *********************************************/

 #define KRITIK_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_kdkritik_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_kdkritik_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_kdkritik_3;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
