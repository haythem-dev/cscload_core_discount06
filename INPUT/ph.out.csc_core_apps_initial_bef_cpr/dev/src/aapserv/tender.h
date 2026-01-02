#ifndef __PP_TENDER_H_
#define __PP_TENDER_H_

/******************************************************************************/
/* c:\git\pharmos.outbound.csc_core_applications\dev\src\aapserv\Tender *******/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of TENDERARTICLE *********************************************/

#define L_TENDERARTICLE_TENDERNO 11
#define L_TENDERARTICLE_ARTICLENO 11
#define L_TENDERARTICLE_CONTRACTQTY 11
#define L_TENDERARTICLE_PREISEKAPO 9
#define N_TENDERARTICLE_PREISEKAPO 2
#define L_TENDERARTICLE_PREISEKGROSSO 9
#define N_TENDERARTICLE_PREISEKGROSSO 2
#define L_TENDERARTICLE_CONTRACTPRICE 9
#define N_TENDERARTICLE_CONTRACTPRICE 2
#define L_TENDERARTICLE_REMAININGLIFE 11
#define L_TENDERARTICLE_PREISEKGROSSONA 9
#define N_TENDERARTICLE_PREISEKGROSSONA 2
#define L_TENDERARTICLE_ADDDISCOUNTPCT 5
#define N_TENDERARTICLE_ADDDISCOUNTPCT 2
#define L_TENDERARTICLE_AEP 9
#define N_TENDERARTICLE_AEP 2
#define L_TENDERARTICLE_TENDERSTATE 1
#define L_TENDERARTICLE_EINHEIT 9
#define L_TENDERARTICLE_ARTIKEL_NAME 30
#define L_TENDERARTICLE_TAXLEVEL 6
#define L_TENDERARTICLE_ARTIKEL_LANGNAME 50

/* Length-Define of TENDERINFO ************************************************/

#define L_TENDERINFO_TENDERNO 11
#define L_TENDERINFO_TENDERTYPE 11
#define L_TENDERINFO_ARTICLENO 11
#define L_TENDERINFO_CONTRACTNO 48
#define L_TENDERINFO_BRANCHNO 6
#define L_TENDERINFO_CUSTOMERNO 11
#define L_TENDERINFO_DATEFROM 11
#define L_TENDERINFO_DATETO 11
#define L_TENDERINFO_EXCEEDANCEPCT 5
#define N_TENDERINFO_EXCEEDANCEPCT 2
#define L_TENDERINFO_PHARMACYCHAINNO 11

/* Length-Define of TENDERSTOCK ***********************************************/

#define L_TENDERSTOCK_TENDERNO 11
#define L_TENDERSTOCK_DELIVERYQTY 11
#define L_TENDERSTOCK_DATUMVERFALL 11
#define L_TENDERSTOCK_RETURNQTY 11
#define L_TENDERSTOCK_FILIALNR 6
#define L_TENDERSTOCK_ARTIKEL_NR 11
#define L_TENDERSTOCK_BESTAND 11

/* SqlDefine of TENDERARTICLE *************************************************/


#define TENDERARTICLE_PLISTE \
        "TENDERPOS.TENDERNO,"\
        "TENDERPOS.ARTICLENO,"\
        "TENDERPOS.CONTRACTQTY,"\
        "ARTIKELPREIS.PREISEKAPO,"\
        "ARTIKELPREIS.PREISEKGROSSO,"\
        "TENDERPOS.CONTRACTPRICE,"\
        "TENDERPOS.REMAININGLIFE,"\
        "ARTIKELPREIS.PREISEKGROSSONA,"\
        "TENDERPOS.ADDDISCOUNTPCT,"\
        "TENDERPOS.AEP,"\
        "TENDERPOS.TENDERSTATE,"\
        "ARTIKELZENTRAL.EINHEIT,"\
        "ARTIKELZENTRAL.ARTIKEL_NAME,"\
        "ARTIKELZENTRAL.TAXLEVEL,"\
        "ARTIKELZENTRAL.ARTIKEL_LANGNAME"

/* SqlDefine of TENDERINFO ****************************************************/


#define TENDERINFO_PLISTE \
        "TENDERHEAD.TENDERNO,"\
        "TENDERHEAD.TENDERTYPE,"\
        "TENDERHEAD.CONTRACTNO,"\
        "TENDERHEAD.BRANCHNO,"\
        "TENDERHEAD.CUSTOMERNO,"\
        "TENDERHEAD.DATEFROM,"\
        "TENDERHEAD.DATETO,"\
        "TENDERHEAD.EXCEEDANCEPCT,"\
        "TENDERHEAD.PHARMACYCHAINNO"

/* SqlDefine of TENDERSTOCK ***************************************************/


#define TENDERSTOCK_PLISTE \
        "TENDERPROGRESS.TENDERNO,"\
        "TENDERPROGRESS.DELIVERYQTY,"\
        "ARTIKELLAGERORT.DATUMVERFALL,"\
        "TENDERPROGRESS.RETURNQTY,"\
        "ARTIKELLOKAL.FILIALNR,"\
        "ARTIKELLOKAL.ARTIKEL_NR,"\
        "ARTIKELLOKAL.BESTAND"

/* SqlDefine of TENDERARTICLE *************************************************/


#define TENDERARTICLE_UPDLISTE \
        "TENDERNO=?,"\
        "ARTICLENO=?,"\
        "CONTRACTQTY=?,"\
        "PREISEKAPO=?,"\
        "PREISEKGROSSO=?,"\
        "CONTRACTPRICE=?,"\
        "REMAININGLIFE=?,"\
        "PREISEKGROSSONA=?,"\
        "ADDDISCOUNTPCT=?,"\
        "AEP=?,"\
        "TENDERSTATE=?,"\
        "EINHEIT=?,"\
        "ARTIKEL_NAME=?,"\
        "TAXLEVEL=?,"\
        "ARTIKEL_LANGNAME=?"
/* SqlDefine of TENDERINFO ****************************************************/


#define TENDERINFO_UPDLISTE \
        "TENDERNO=?,"\
        "TENDERTYPE=?,"\
        "CONTRACTNO=?,"\
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "DATEFROM=?,"\
        "DATETO=?,"\
        "EXCEEDANCEPCT=?,"\
        "PHARMACYCHAINNO=?"
/* SqlDefine of TENDERSTOCK ***************************************************/


#define TENDERSTOCK_UPDLISTE \
        "TENDERNO=?,"\
        "DELIVERYQTY=?,"\
        "DATUMVERFALL=?,"\
        "RETURNQTY=?,"\
        "FILIALNR=?,"\
        "ARTIKEL_NR=?,"\
        "BESTAND=?"
/* SqlMacros-Define of TENDERARTICLE ******************************************/

#define TENDERARTICLE_ZEIGER(x) \
        :x->TENDERNO,\
        :x->ARTICLENO,\
        :x->CONTRACTQTY,\
        :x->PREISEKAPO,\
        :x->PREISEKGROSSO,\
        :x->CONTRACTPRICE,\
        :x->REMAININGLIFE,\
        :x->PREISEKGROSSONA,\
        :x->ADDDISCOUNTPCT,\
        :x->AEP,\
        :x->TENDERSTATE,\
        :x->EINHEIT,\
        :x->ARTIKEL_NAME,\
        :x->TAXLEVEL,\
        :x->ARTIKEL_LANGNAME
#define TENDERARTICLE_ZEIGERSEL(x) \
        :x->TENDERNO,\
        :x->ARTICLENO,\
        :x->CONTRACTQTY,\
        :x->PREISEKAPO,\
        :x->PREISEKGROSSO,\
        :x->CONTRACTPRICE,\
        :x->REMAININGLIFE,\
        :x->PREISEKGROSSONA,\
        :x->ADDDISCOUNTPCT,\
        :x->AEP,\
        :x->TENDERSTATE,\
        :x->EINHEIT,\
        :x->ARTIKEL_NAME,\
        :x->TAXLEVEL,\
        :x->ARTIKEL_LANGNAME

/* SqlMacros-Define of TENDERINFO *********************************************/

#define TENDERINFO_ZEIGER(x) \
        :x->TENDERNO,\
        :x->TENDERTYPE,\
        :x->CONTRACTNO,\
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->DATEFROM,\
        :x->DATETO,\
        :x->EXCEEDANCEPCT,\
        :x->PHARMACYCHAINNO
#define TENDERINFO_ZEIGERSEL(x) \
        :x->TENDERNO,\
        :x->TENDERTYPE,\
        :x->CONTRACTNO,\
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->DATEFROM,\
        :x->DATETO,\
        :x->EXCEEDANCEPCT,\
        :x->PHARMACYCHAINNO

/* SqlMacros-Define of TENDERSTOCK ********************************************/

#define TENDERSTOCK_ZEIGER(x) \
        :x->TENDERNO,\
        :x->DELIVERYQTY,\
        :x->DATUMVERFALL,\
        :x->RETURNQTY,\
        :x->FILIALNR,\
        :x->ARTIKEL_NR,\
        :x->BESTAND
#define TENDERSTOCK_ZEIGERSEL(x) \
        :x->TENDERNO,\
        :x->DELIVERYQTY,\
        :x->DATUMVERFALL,\
        :x->RETURNQTY,\
        :x->FILIALNR,\
        :x->ARTIKEL_NR,\
        :x->BESTAND

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define TENDERARTICLE_H
#define TENDERARTICLE_ANZ ( sizeof(TENDERARTICLE_BES) / sizeof(struct buf_desc) )
#define TENDERINFO_H
#define TENDERINFO_ANZ ( sizeof(TENDERINFO_BES) / sizeof(struct buf_desc) )
#define TENDERSTOCK_H
#define TENDERSTOCK_ANZ ( sizeof(TENDERSTOCK_BES) / sizeof(struct buf_desc) )
#endif

#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of TENDERARTICLE *******************************************/

#ifndef TRANSCLASS
typedef struct N_TENDERARTICLE {
    long TENDERNO;
    long ARTICLENO;
    long CONTRACTQTY;
    double PREISEKAPO;
    double PREISEKGROSSO;
    double CONTRACTPRICE;
    long REMAININGLIFE;
    double PREISEKGROSSONA;
    double ADDDISCOUNTPCT;
    double AEP;
    char TENDERSTATE[2];
    char EINHEIT[10];
    char ARTIKEL_NAME[31];
    short TAXLEVEL;
    char ARTIKEL_LANGNAME[51];
    long FETCH_REL;
} tenderarticleS;
#else /* TRANSCLASS */
typedef struct N_TENDERARTICLE {
    long TENDERNO;
    long ARTICLENO;
    long CONTRACTQTY;
    double PREISEKAPO;
    double PREISEKGROSSO;
    double CONTRACTPRICE;
    long REMAININGLIFE;
    double PREISEKGROSSONA;
    double ADDDISCOUNTPCT;
    double AEP;
    char TENDERSTATE[2];
    char EINHEIT[10];
    char ARTIKEL_NAME[31];
    short TAXLEVEL;
    char ARTIKEL_LANGNAME[51];
    long FETCH_REL;
    bool operator == (const N_TENDERARTICLE& right) const {
        return (
            TENDERNO == right.TENDERNO &&
            ARTICLENO == right.ARTICLENO &&
            CONTRACTQTY == right.CONTRACTQTY &&
            PREISEKAPO == right.PREISEKAPO &&
            PREISEKGROSSO == right.PREISEKGROSSO &&
            CONTRACTPRICE == right.CONTRACTPRICE &&
            REMAININGLIFE == right.REMAININGLIFE &&
            PREISEKGROSSONA == right.PREISEKGROSSONA &&
            ADDDISCOUNTPCT == right.ADDDISCOUNTPCT &&
            AEP == right.AEP &&
            !strcmp(TENDERSTATE, right.TENDERSTATE) &&
            !strcmp(EINHEIT, right.EINHEIT) &&
            !strcmp(ARTIKEL_NAME, right.ARTIKEL_NAME) &&
            TAXLEVEL == right.TAXLEVEL &&
            !strcmp(ARTIKEL_LANGNAME, right.ARTIKEL_LANGNAME)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        TENDERNO = 0;
        ARTICLENO = 0;
        CONTRACTQTY = 0;
        PREISEKAPO = 0;
        PREISEKGROSSO = 0;
        CONTRACTPRICE = 0;
        REMAININGLIFE = 0;
        PREISEKGROSSONA = 0;
        ADDDISCOUNTPCT = 0;
        AEP = 0;
        strcpy(TENDERSTATE, " " );
        strcpy(EINHEIT, " " );
        strcpy(ARTIKEL_NAME, " " );
        TAXLEVEL = 0;
        strcpy(ARTIKEL_LANGNAME, " " );
#endif
    }
} tenderarticleS;
#endif /* TRANSCLASS */

/* original struct of TENDERINFO **********************************************/

#ifndef TRANSCLASS
typedef struct N_TENDERINFO {
    long TENDERNO;
    long TENDERTYPE;
    long ARTICLENO;
    char CONTRACTNO[49];
    short BRANCHNO;
    long CUSTOMERNO;
    long DATEFROM;
    long DATETO;
    double EXCEEDANCEPCT;
    long PHARMACYCHAINNO;
    long FETCH_REL;
} tenderinfoS;
#else /* TRANSCLASS */
typedef struct N_TENDERINFO {
    long TENDERNO;
    long TENDERTYPE;
    long ARTICLENO;
    char CONTRACTNO[49];
    short BRANCHNO;
    long CUSTOMERNO;
    long DATEFROM;
    long DATETO;
    double EXCEEDANCEPCT;
    long PHARMACYCHAINNO;
    long FETCH_REL;
    bool operator == (const N_TENDERINFO& right) const {
        return (
            TENDERNO == right.TENDERNO &&
            TENDERTYPE == right.TENDERTYPE &&
            ARTICLENO == right.ARTICLENO &&
            !strcmp(CONTRACTNO, right.CONTRACTNO) &&
            BRANCHNO == right.BRANCHNO &&
            CUSTOMERNO == right.CUSTOMERNO &&
            DATEFROM == right.DATEFROM &&
            DATETO == right.DATETO &&
            EXCEEDANCEPCT == right.EXCEEDANCEPCT &&
            PHARMACYCHAINNO == right.PHARMACYCHAINNO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        TENDERNO = 0;
        TENDERTYPE = 0;
        ARTICLENO = 0;
        strcpy(CONTRACTNO, " " );
        BRANCHNO = 0;
        CUSTOMERNO = 0;
        DATEFROM = 0;
        DATETO = 0;
        EXCEEDANCEPCT = 0;
        PHARMACYCHAINNO = 0;
#endif
    }
} tenderinfoS;
#endif /* TRANSCLASS */

/* original struct of TENDERSTOCK *********************************************/

#ifndef TRANSCLASS
typedef struct N_TENDERSTOCK {
    long TENDERNO;
    long DELIVERYQTY;
    long DATUMVERFALL;
    long RETURNQTY;
    short FILIALNR;
    long ARTIKEL_NR;
    long BESTAND;
} tenderstockS;
#else /* TRANSCLASS */
typedef struct N_TENDERSTOCK {
    long TENDERNO;
    long DELIVERYQTY;
    long DATUMVERFALL;
    long RETURNQTY;
    short FILIALNR;
    long ARTIKEL_NR;
    long BESTAND;

    bool operator == (const N_TENDERSTOCK& right) const {
        return (
            TENDERNO == right.TENDERNO &&
            DELIVERYQTY == right.DELIVERYQTY &&
            DATUMVERFALL == right.DATUMVERFALL &&
            RETURNQTY == right.RETURNQTY &&
            FILIALNR == right.FILIALNR &&
            ARTIKEL_NR == right.ARTIKEL_NR &&
            BESTAND == right.BESTAND
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        TENDERNO = 0;
        DELIVERYQTY = 0;
        DATUMVERFALL = 0;
        RETURNQTY = 0;
        FILIALNR = 0;
        ARTIKEL_NR = 0;
        BESTAND = 0;
#endif
    }
} tenderstockS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of TENDERARTICLE *******************************/

struct C_TENDERARTICLE {
    long TENDERNO;
    long ARTICLENO;
    long CONTRACTQTY;
    double PREISEKAPO;
    double PREISEKGROSSO;
    double CONTRACTPRICE;
    long REMAININGLIFE;
    double PREISEKGROSSONA;
    double ADDDISCOUNTPCT;
    double AEP;
    char TENDERSTATE;
    char EINHEIT[10];
    char ARTIKEL_NAME[31];
    short TAXLEVEL;
    char ARTIKEL_LANGNAME[51];
    long FETCH_REL;
};
/* Structur with real chartype of TENDERINFO **********************************/

struct C_TENDERINFO {
    long TENDERNO;
    long TENDERTYPE;
    long ARTICLENO;
    char CONTRACTNO[49];
    short BRANCHNO;
    long CUSTOMERNO;
    long DATEFROM;
    long DATETO;
    double EXCEEDANCEPCT;
    long PHARMACYCHAINNO;
    long FETCH_REL;
};
/* Structur with real chartype of TENDERSTOCK *********************************/

struct C_TENDERSTOCK {
    long TENDERNO;
    long DELIVERYQTY;
    long DATUMVERFALL;
    long RETURNQTY;
    short FILIALNR;
    long ARTIKEL_NR;
    long BESTAND;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of TENDERARTICLE *****************************/

struct I_TENDERARTICLE {
    short TENDERNO;
    short ARTICLENO;
    short CONTRACTQTY;
    short PREISEKAPO;
    short PREISEKGROSSO;
    short CONTRACTPRICE;
    short REMAININGLIFE;
    short PREISEKGROSSONA;
    short ADDDISCOUNTPCT;
    short AEP;
    short TENDERSTATE;
    short EINHEIT;
    short ARTIKEL_NAME;
    short TAXLEVEL;
    short ARTIKEL_LANGNAME;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of TENDERINFO ********************************/

struct I_TENDERINFO {
    short TENDERNO;
    short TENDERTYPE;
    short ARTICLENO;
    short CONTRACTNO;
    short BRANCHNO;
    short CUSTOMERNO;
    short DATEFROM;
    short DATETO;
    short EXCEEDANCEPCT;
    short PHARMACYCHAINNO;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of TENDERSTOCK *******************************/

struct I_TENDERSTOCK {
    short TENDERNO;
    short DELIVERYQTY;
    short DATUMVERFALL;
    short RETURNQTY;
    short FILIALNR;
    short ARTIKEL_NR;
    short BESTAND;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of TENDERARTICLE ***************************************/

#if defined (BUF_DESC)
static struct buf_desc TENDERARTICLE_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_D, 5, 2 },
   { TYP_D, 9, 2 },
   { TYP_C, 1, 0 },
   { TYP_C, 9, 0 },
   { TYP_C, 30, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 50, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc TENDERARTICLE_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_D, 5, 2 },
   { TYP_D, 9, 2 },
   { TYP_C, 1, 0 },
   { TYP_C, 9, 0 },
   { TYP_C, 30, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 50, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of TENDERINFO ******************************************/

#if defined (BUF_DESC)
static struct buf_desc TENDERINFO_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 48, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 5, 2 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc TENDERINFO_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 48, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 5, 2 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of TENDERSTOCK *****************************************/

#if defined (BUF_DESC)
static struct buf_desc TENDERSTOCK_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc TENDERSTOCK_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* FunctionNumber-Define of TenderArticle *************************************/

#define TENDERARTICLE_SELART 1494
#define TENDERARTICLE_SELLIST 1490

/* FunctionNumber-Define of TenderInfo ****************************************/

#define TENDERINFO_SELLIST 1489
#define TENDERINFO_SELLISTCHAIN 1632
#define TENDERINFO_SELLISTPOS 1633
#define TENDERINFO_SELLISTSTAAT 1495
#define TENDERINFO_SELTENDER 1493

/* FunctionNumber-Define of TenderStock ***************************************/

#define TENDERSTOCK_SELQTY 1492

#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of TenderArticle *********************************/

#define SelArt 1494
#define SelList 1490

/* Old-FunctionNumber-Define of TenderInfo ************************************/

#define SelList 1489
#define SelListChain 1632
#define SelListPos 1633
#define SelListStaat 1495
#define SelTender 1493

/* Old-FunctionNumber-Define of TenderStock ***********************************/

#define SelQty 1492

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

class CTENDERARTICLE : public ppDadeVirtual {
public:
    tenderarticleS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<tenderarticleS> lst; // class list

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
                     vector< tenderarticleS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     tenderarticleS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< tenderarticleS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<tenderarticleS>::iterator
                 beginList() { return lst.begin(); }
    vector<tenderarticleS>::iterator
                 endList  () { return lst.end  (); }

    long         GetTenderno() const { return s.TENDERNO; }
    long         GetArticleno() const { return s.ARTICLENO; }
    long         GetContractqty() const { return s.CONTRACTQTY; }
    double       GetPreisekapo() const { return s.PREISEKAPO; }
    double       GetPreisekgrosso() const { return s.PREISEKGROSSO; }
    double       GetContractprice() const { return s.CONTRACTPRICE; }
    long         GetRemaininglife() const { return s.REMAININGLIFE; }
    double       GetPreisekgrossona() const { return s.PREISEKGROSSONA; }
    double       GetAdddiscountpct() const { return s.ADDDISCOUNTPCT; }
    double       GetAep() const { return s.AEP; }
    char         GetTenderstate() const { return s.TENDERSTATE[0]; }
    const char*  GetEinheit(ppString & t) const { t = s.EINHEIT; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetArtikel_name(ppString & t) const { t = s.ARTIKEL_NAME; t.erasespace(ppString::END); return t.c_str(); }
    short        GetTaxlevel() const { return s.TAXLEVEL; }
    const char*  GetArtikel_langname(ppString & t) const { t = s.ARTIKEL_LANGNAME; t.erasespace(ppString::END); return t.c_str(); }

    const tenderarticleS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetTenderno(long t) { s.TENDERNO = t; }
    void         SetArticleno(long t) { s.ARTICLENO = t; }
    void         SetContractqty(long t) { s.CONTRACTQTY = t; }
    void         SetPreisekapo(double t) { s.PREISEKAPO = t; }
    void         SetPreisekgrosso(double t) { s.PREISEKGROSSO = t; }
    void         SetContractprice(double t) { s.CONTRACTPRICE = t; }
    void         SetRemaininglife(long t) { s.REMAININGLIFE = t; }
    void         SetPreisekgrossona(double t) { s.PREISEKGROSSONA = t; }
    void         SetAdddiscountpct(double t) { s.ADDDISCOUNTPCT = t; }
    void         SetAep(double t) { s.AEP = t; }
    void         SetTenderstate(char t) { s.TENDERSTATE[0] = t; s.TENDERSTATE[1] = '\0';}
    void         SetEinheit(const ppString & t) { ppGStrCopy(s.EINHEIT, t.c_str(), L_TENDERARTICLE_EINHEIT); }
    void         SetArtikel_name(const ppString & t) { ppGStrCopy(s.ARTIKEL_NAME, t.c_str(), L_TENDERARTICLE_ARTIKEL_NAME); }
    void         SetTaxlevel(short t) { s.TAXLEVEL = t; }
    void         SetArtikel_langname(const ppString & t) { ppGStrCopy(s.ARTIKEL_LANGNAME, t.c_str(), L_TENDERARTICLE_ARTIKEL_LANGNAME); }

    void         SetStruct(const tenderarticleS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelArt(int pos = 0) { int ret = UniqueServerCall(1494, pos); Strip(s); return ret; }
    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1490, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CTENDERARTICLE() {
        ::buf_default((void *)&s, TENDERARTICLE_BES, TENDERARTICLE_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CTENDERARTICLE() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, TENDERARTICLE_BES, TENDERARTICLE_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, TENDERARTICLE_BES, (int)TENDERARTICLE_ANZ, error_msg);
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
        if ( fkt_nr == 1494 ) return UniqueServerCall(1494, pos);
        if ( fkt_nr == 1490 ) return CursorServerCall(1490, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_TENDERARTICLE & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.EINHEIT);
        ppGStripLast(d.ARTIKEL_NAME);
        ppGStripLast(d.ARTIKEL_LANGNAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, TENDERARTICLE_BES, (int)TENDERARTICLE_ANZ, error_msg);
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
        CTENDERARTICLE c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, TENDERARTICLE_BES, (int)TENDERARTICLE_ANZ, error_msg);
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

class CTENDERINFO : public ppDadeVirtual {
public:
    tenderinfoS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<tenderinfoS> lst; // class list

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
                     vector< tenderinfoS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     tenderinfoS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< tenderinfoS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<tenderinfoS>::iterator
                 beginList() { return lst.begin(); }
    vector<tenderinfoS>::iterator
                 endList  () { return lst.end  (); }

    long         GetTenderno() const { return s.TENDERNO; }
    long         GetTendertype() const { return s.TENDERTYPE; }
    long         GetArticleno() const { return s.ARTICLENO; }
    const char*  GetContractno(ppString & t) const { t = s.CONTRACTNO; t.erasespace(ppString::END); return t.c_str(); }
    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    long         GetDatefrom() const { return s.DATEFROM; }
    long         GetDateto() const { return s.DATETO; }
    double       GetExceedancepct() const { return s.EXCEEDANCEPCT; }
    long         GetPharmacychainno() const { return s.PHARMACYCHAINNO; }

    const tenderinfoS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetTenderno(long t) { s.TENDERNO = t; }
    void         SetTendertype(long t) { s.TENDERTYPE = t; }
    void         SetArticleno(long t) { s.ARTICLENO = t; }
    void         SetContractno(const ppString & t) { ppGStrCopy(s.CONTRACTNO, t.c_str(), L_TENDERINFO_CONTRACTNO); }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetDatefrom(long t) { s.DATEFROM = t; }
    void         SetDateto(long t) { s.DATETO = t; }
    void         SetExceedancepct(double t) { s.EXCEEDANCEPCT = t; }
    void         SetPharmacychainno(long t) { s.PHARMACYCHAINNO = t; }

    void         SetStruct(const tenderinfoS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1489, FetchRel, pos); return ret; }
    int          SelListChain(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1632, FetchRel, pos); return ret; }
    int          SelListPos(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1633, FetchRel, pos); return ret; }
    int          SelListStaat(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1495, FetchRel, pos); return ret; }
    int          SelTender(int pos = 0) { int ret = UniqueServerCall(1493, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CTENDERINFO() {
        ::buf_default((void *)&s, TENDERINFO_BES, TENDERINFO_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CTENDERINFO() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, TENDERINFO_BES, TENDERINFO_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, TENDERINFO_BES, (int)TENDERINFO_ANZ, error_msg);
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
        if ( fkt_nr == 1489 ) return CursorServerCall(1489, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1632 ) return CursorServerCall(1632, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1633 ) return CursorServerCall(1633, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1495 ) return CursorServerCall(1495, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1493 ) return UniqueServerCall(1493, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_TENDERINFO & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.CONTRACTNO);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, TENDERINFO_BES, (int)TENDERINFO_ANZ, error_msg);
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
        CTENDERINFO c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, TENDERINFO_BES, (int)TENDERINFO_ANZ, error_msg);
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

class CTENDERSTOCK : public ppDadeVirtual {
public:
    tenderstockS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<tenderstockS> lst; // class list

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
                     vector< tenderstockS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     tenderstockS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< tenderstockS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<tenderstockS>::iterator
                 beginList() { return lst.begin(); }
    vector<tenderstockS>::iterator
                 endList  () { return lst.end  (); }

    long         GetTenderno() const { return s.TENDERNO; }
    long         GetDeliveryqty() const { return s.DELIVERYQTY; }
    long         GetDatumverfall() const { return s.DATUMVERFALL; }
    long         GetReturnqty() const { return s.RETURNQTY; }
    short        GetFilialnr() const { return s.FILIALNR; }
    long         GetArtikel_nr() const { return s.ARTIKEL_NR; }
    long         GetBestand() const { return s.BESTAND; }

    const tenderstockS &
                 GetStruct() const { return s; }
    void         SetTenderno(long t) { s.TENDERNO = t; }
    void         SetDeliveryqty(long t) { s.DELIVERYQTY = t; }
    void         SetDatumverfall(long t) { s.DATUMVERFALL = t; }
    void         SetReturnqty(long t) { s.RETURNQTY = t; }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetArtikel_nr(long t) { s.ARTIKEL_NR = t; }
    void         SetBestand(long t) { s.BESTAND = t; }

    void         SetStruct(const tenderstockS & t) { s = t; }

    int          SelQty(int pos = 0) { int ret = UniqueServerCall(1492, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CTENDERSTOCK() {
        ::buf_default((void *)&s, TENDERSTOCK_BES, TENDERSTOCK_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CTENDERSTOCK() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, TENDERSTOCK_BES, TENDERSTOCK_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1492 ) return UniqueServerCall(1492, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_TENDERSTOCK & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, TENDERSTOCK_BES, (int)TENDERSTOCK_ANZ, error_msg);
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

#endif   // GUARD
