#ifndef __PP_ORDERS_H_
#define __PP_ORDERS_H_

/******************************************************************************/
/* c:\git\pharmos.outbound.csc_core_applications\dev\src\aapserv\Orders *******/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of CHECKDFREASON *********************************************/

#define L_CHECKDFREASON_KDAUFTRAGNR 11
#define L_CHECKDFREASON_EVENTDESCRIPTION 254
#define L_CHECKDFREASON_EVENTCODE 6

/* Length-Define of CHECKKLRELEASED *******************************************/

#define L_CHECKKLRELEASED_KDAUFTRAGNR 11
#define L_CHECKKLRELEASED_ISRELEASED 6

/* Length-Define of CHECKORDERNODD ********************************************/

#define L_CHECKORDERNODD_CSCORDERNO 11

/* Length-Define of CHECKORDERZEROD *******************************************/

#define L_CHECKORDERZEROD_KDAUFTRAGNR 11
#define L_CHECKORDERZEROD_ORDVALFTAXFS 11
#define N_CHECKORDERZEROD_ORDVALFTAXFS 2

/* Length-Define of CHECKORDERZERODOLD ****************************************/

#define L_CHECKORDERZERODOLD_DATUM 11
#define L_CHECKORDERZERODOLD_KDAUFTRAGNR 11
#define L_CHECKORDERZERODOLD_ORDVALFTAXFS 11
#define N_CHECKORDERZERODOLD_ORDVALFTAXFS 2

/* Length-Define of CHECKORDERLABEL *******************************************/

#define L_CHECKORDERLABEL_KDAUFTRAGNR 11
#define L_CHECKORDERLABEL_ORDERLABELTYP 6

/* Length-Define of DRIVER ****************************************************/

#define L_DRIVER_DATUM 11
#define L_DRIVER_KDAUFTRAGNR 11
#define L_DRIVER_INVOICENUMBER 15
#define L_DRIVER_DRIVERNAME 30
#define L_DRIVER_DRIVERID 11

/* Length-Define of INVOICENOS ************************************************/

#define L_INVOICENOS_CSCORDERNO 11
#define L_INVOICENOS_REMARKTEXT 250

/* Length-Define of INVOICENOSOLD *********************************************/

#define L_INVOICENOSOLD_DATUM 11
#define L_INVOICENOSOLD_CSCORDERNO 11
#define L_INVOICENOSOLD_REMARKTEXT 250

/* Length-Define of ORDERPERIOD ***********************************************/

#define L_ORDERPERIOD_CUSTOMERNO 11
#define L_ORDERPERIOD_TOURID 6
#define L_ORDERPERIOD_DATUMKOMMI 11
#define L_ORDERPERIOD_CONSTIME 11
#define L_ORDERPERIOD_ID 11
#define L_ORDERPERIOD_BRANCHNO 6
#define L_ORDERPERIOD_WEEKDAY 6
#define L_ORDERPERIOD_FROMTIME 11
#define L_ORDERPERIOD_TOTIME 11
#define L_ORDERPERIOD_ORDER_PERIOD_ID 11
#define L_ORDERPERIOD_MAINTIME 11
#define L_ORDERPERIOD_TOURINAKTIV 1
#define L_ORDERPERIOD_KIPPZEIT 6
#define L_ORDERPERIOD_ANZ_ERFASST 11
#define L_ORDERPERIOD_ANZ_FAKTUR 11

/* Length-Define of ORIGINTYPESETTINGSPF **************************************/

#define L_ORIGINTYPESETTINGSPF_ORIGINTYPE 6
#define L_ORIGINTYPESETTINGSPF_SETTINGACTIVATED 6
#define L_ORIGINTYPESETTINGSPF_ORIGINDEVICE 20
#define L_ORIGINTYPESETTINGSPF_BRANCHNO 6
#define L_ORIGINTYPESETTINGSPF_ISORDERCONSOLIDATION 6
#define L_ORIGINTYPESETTINGSPF_ENDOFORDERCONS 11
#define L_ORIGINTYPESETTINGSPF_ORDERCONSDURATION 11

/* Length-Define of REMARKTYPES ***********************************************/

#define L_REMARKTYPES_REMARKTYPE 6
#define L_REMARKTYPES_REMARKNAME 50

/* Length-Define of SPECIALNUMBERS ********************************************/

#define L_SPECIALNUMBERS_CSCORDERNO 11
#define L_SPECIALNUMBERS_RELATIONNOTYPE 6
#define L_SPECIALNUMBERS_RELATIONNO 11

/* Length-Define of SPECIALNUMBERSOLD *****************************************/

#define L_SPECIALNUMBERSOLD_DATE 11
#define L_SPECIALNUMBERSOLD_CSCORDERNO 11
#define L_SPECIALNUMBERSOLD_RELATIONNOTYPE 6
#define L_SPECIALNUMBERSOLD_RELATIONNO 11

/* SqlDefine of CHECKDFREASON *************************************************/


#define CHECKDFREASON_PLISTE \
        "KDAUFTRAGEREIGNIS.KDAUFTRAGNR,"\
        "EVENTREASONS.EVENTDESCRIPTION,"\
        "KDAUFTRAGEREIGNIS.EVENTCODE"

/* SqlDefine of CHECKKLRELEASED ***********************************************/


#define CHECKKLRELEASED_PLISTE \
        "KDAUFTRAGDEBTREL.KDAUFTRAGNR,"\
        "KDAUFTRAGDEBTREL.ISRELEASED"

/* SqlDefine of CHECKORDERNODD ************************************************/


#define CHECKORDERNODD_PLISTE \
        "CSCORDERFLAGS.CSCORDERNO"

/* SqlDefine of CHECKORDERZEROD ***********************************************/


#define CHECKORDERZEROD_PLISTE \
        "KDAUFTRAGWERTE.KDAUFTRAGNR,"\
        "KDAUFTRAGWERTE.ORDVALFTAXFS"

/* SqlDefine of CHECKORDERZERODOLD ********************************************/


#define CHECKORDERZERODOLD_PLISTE \
        "AKDAUFTRAGWERTE.DATUM,"\
        "AKDAUFTRAGWERTE.KDAUFTRAGNR,"\
        "AKDAUFTRAGWERTE.ORDVALFTAXFS"

/* SqlDefine of CHECKORDERLABEL ***********************************************/


#define CHECKORDERLABEL_PLISTE \
        "KDAUFTRAG.KDAUFTRAGNR"

/* SqlDefine of DRIVER ********************************************************/


#define DRIVER_PLISTE \
        "CSTPAYMENTLIST.INVOICENUMBER,"\
        "DRIVERLIST.DRIVERNAME,"\
        "CSTPAYMENTLIST.DRIVERID"

/* SqlDefine of INVOICENOS ****************************************************/


#define INVOICENOS_PLISTE \
        "ORDERREMARKS.CSCORDERNO,"\
        "ORDERREMARKS.REMARKTEXT"

/* SqlDefine of INVOICENOSOLD *************************************************/


#define INVOICENOSOLD_PLISTE \
        "AORDERREMARKS.DATUM,"\
        "AORDERREMARKS.CSCORDERNO,"\
        "AORDERREMARKS.REMARKTEXT"

/* SqlDefine of ORDERPERIOD ***************************************************/


#define ORDERPERIOD_PLISTE \
        "ORDERPERIOD.CUSTOMERNO,"\
        "ORDERPERIOD.TOURID,"\
        "TOURCONSTIME.DATUMKOMMI,"\
        "TOURCONSTIME.CONSTIME,"\
        "ORDERPERIOD.ID,"\
        "ORDERPERIOD.BRANCHNO,"\
        "ORDERPERIOD.WEEKDAY,"\
        "ORDERPERIODTIME.FROMTIME,"\
        "ORDERPERIODTIME.TOTIME,"\
        "ORDERPERIODTIME.ORDER_PERIOD_ID,"\
        "ORDERPERIODTIME.MAINTIME,"\
        "TOURPLANTAG.TOURINAKTIV,"\
        "TOUR.KIPPZEIT,"\
        "AADUMMY.ANZ_ERFASST,"\
        "AADUMMY.ANZ_FAKTUR"

/* SqlDefine of ORIGINTYPESETTINGSPF ******************************************/


#define ORIGINTYPESETTINGSPF_PLISTE \
        "ORIGINTYPESETTINGS.ORIGINTYPE,"\
        "ORIGINTYPESETTINGS.SETTINGACTIVATED,"\
        "OEORIGINTYPES.ORIGINDEVICE,"\
        "ORIGINTYPESETTINGS.BRANCHNO,"\
        "ORIGINTYPESETTINGS.ISORDERCONSOLIDATION,"\
        "ORIGINTYPESETTINGS.ENDOFORDERCONS,"\
        "ORIGINTYPESETTINGS.ORDERCONSDURATION"

/* SqlDefine of REMARKTYPES ***************************************************/


#define REMARKTYPES_PLISTE \
        "ORDERREMARKTYPES.REMARKTYPE,"\
        "ORDERREMARKTYPES.REMARKNAME"

/* SqlDefine of SPECIALNUMBERS ************************************************/


#define SPECIALNUMBERS_PLISTE \
        "ORDERRELATIONNO.CSCORDERNO,"\
        "ORDERRELATIONNO.RELATIONNOTYPE,"\
        "ORDERRELATIONNO.RELATIONNO"

/* SqlDefine of SPECIALNUMBERSOLD *********************************************/


#define SPECIALNUMBERSOLD_PLISTE \
        "AORDERRELATIONNO.DATE,"\
        "AORDERRELATIONNO.CSCORDERNO,"\
        "AORDERRELATIONNO.RELATIONNOTYPE,"\
        "AORDERRELATIONNO.RELATIONNO"

/* SqlDefine of CHECKDFREASON *************************************************/


#define CHECKDFREASON_UPDLISTE \
        "KDAUFTRAGNR=?,"\
        "EVENTDESCRIPTION=?,"\
        "EVENTCODE=?"
/* SqlDefine of CHECKKLRELEASED ***********************************************/


#define CHECKKLRELEASED_UPDLISTE \
        "KDAUFTRAGNR=?,"\
        "ISRELEASED=?"
/* SqlDefine of CHECKORDERNODD ************************************************/


#define CHECKORDERNODD_UPDLISTE \
        "CSCORDERNO=?"
/* SqlDefine of CHECKORDERZEROD ***********************************************/


#define CHECKORDERZEROD_UPDLISTE \
        "KDAUFTRAGNR=?,"\
        "ORDVALFTAXFS=?"
/* SqlDefine of CHECKORDERZERODOLD ********************************************/


#define CHECKORDERZERODOLD_UPDLISTE \
        "DATUM=?,"\
        "KDAUFTRAGNR=?,"\
        "ORDVALFTAXFS=?"
/* SqlDefine of CHECKORDERLABEL ***********************************************/


#define CHECKORDERLABEL_UPDLISTE \
        "KDAUFTRAGNR=?"
/* SqlDefine of DRIVER ********************************************************/


#define DRIVER_UPDLISTE \
        "INVOICENUMBER=?,"\
        "DRIVERNAME=?,"\
        "DRIVERID=?"
/* SqlDefine of INVOICENOS ****************************************************/


#define INVOICENOS_UPDLISTE \
        "CSCORDERNO=?,"\
        "REMARKTEXT=?"
/* SqlDefine of INVOICENOSOLD *************************************************/


#define INVOICENOSOLD_UPDLISTE \
        "DATUM=?,"\
        "CSCORDERNO=?,"\
        "REMARKTEXT=?"
/* SqlDefine of ORDERPERIOD ***************************************************/


#define ORDERPERIOD_UPDLISTE \
        "CUSTOMERNO=?,"\
        "TOURID=?,"\
        "DATUMKOMMI=?,"\
        "CONSTIME=?,"\
        "ID=?,"\
        "BRANCHNO=?,"\
        "WEEKDAY=?,"\
        "FROMTIME=?,"\
        "TOTIME=?,"\
        "ORDER_PERIOD_ID=?,"\
        "MAINTIME=?,"\
        "TOURINAKTIV=?,"\
        "KIPPZEIT=?,"\
        "ANZ_ERFASST=?,"\
        "ANZ_FAKTUR=?"
/* SqlDefine of ORIGINTYPESETTINGSPF ******************************************/


#define ORIGINTYPESETTINGSPF_UPDLISTE \
        "ORIGINTYPE=?,"\
        "SETTINGACTIVATED=?,"\
        "BRANCHNO=?,"\
        "ISORDERCONSOLIDATION=?,"\
        "ENDOFORDERCONS=?,"\
        "ORDERCONSDURATION=?"
/* SqlDefine of REMARKTYPES ***************************************************/


#define REMARKTYPES_UPDLISTE \
        "REMARKTYPE=?,"\
        "REMARKNAME=?"
/* SqlDefine of SPECIALNUMBERS ************************************************/


#define SPECIALNUMBERS_UPDLISTE \
        "CSCORDERNO=?,"\
        "RELATIONNOTYPE=?,"\
        "RELATIONNO=?"
/* SqlDefine of SPECIALNUMBERSOLD *********************************************/


#define SPECIALNUMBERSOLD_UPDLISTE \
        "DATE=?,"\
        "CSCORDERNO=?,"\
        "RELATIONNOTYPE=?,"\
        "RELATIONNO=?"
/* SqlMacros-Define of CHECKDFREASON ******************************************/

#define CHECKDFREASON_ZEIGER(x) \
        :x->KDAUFTRAGNR,\
        :x->EVENTDESCRIPTION,\
        :x->EVENTCODE
#define CHECKDFREASON_ZEIGERSEL(x) \
        :x->KDAUFTRAGNR,\
        :x->EVENTDESCRIPTION,\
        :x->EVENTCODE

/* SqlMacros-Define of CHECKKLRELEASED ****************************************/

#define CHECKKLRELEASED_ZEIGER(x) \
        :x->KDAUFTRAGNR,\
        :x->ISRELEASED
#define CHECKKLRELEASED_ZEIGERSEL(x) \
        :x->KDAUFTRAGNR,\
        :x->ISRELEASED

/* SqlMacros-Define of CHECKORDERNODD *****************************************/

#define CHECKORDERNODD_ZEIGER(x) \
        :x->CSCORDERNO
#define CHECKORDERNODD_ZEIGERSEL(x) \
        :x->CSCORDERNO

/* SqlMacros-Define of CHECKORDERZEROD ****************************************/

#define CHECKORDERZEROD_ZEIGER(x) \
        :x->KDAUFTRAGNR,\
        :x->ORDVALFTAXFS
#define CHECKORDERZEROD_ZEIGERSEL(x) \
        :x->KDAUFTRAGNR,\
        :x->ORDVALFTAXFS

/* SqlMacros-Define of CHECKORDERZERODOLD *************************************/

#define CHECKORDERZERODOLD_ZEIGER(x) \
        :x->DATUM,\
        :x->KDAUFTRAGNR,\
        :x->ORDVALFTAXFS
#define CHECKORDERZERODOLD_ZEIGERSEL(x) \
        :x->DATUM,\
        :x->KDAUFTRAGNR,\
        :x->ORDVALFTAXFS

/* SqlMacros-Define of CHECKORDERLABEL ****************************************/

#define CHECKORDERLABEL_ZEIGER(x) \
        :x->KDAUFTRAGNR
#define CHECKORDERLABEL_ZEIGERSEL(x) \
        :x->KDAUFTRAGNR

/* SqlMacros-Define of DRIVER *************************************************/

#define DRIVER_ZEIGER(x) \
        :x->INVOICENUMBER,\
        :x->DRIVERNAME,\
        :x->DRIVERID
#define DRIVER_ZEIGERSEL(x) \
        :x->INVOICENUMBER,\
        :x->DRIVERNAME,\
        :x->DRIVERID

/* SqlMacros-Define of INVOICENOS *********************************************/

#define INVOICENOS_ZEIGER(x) \
        :x->CSCORDERNO,\
        :x->REMARKTEXT
#define INVOICENOS_ZEIGERSEL(x) \
        :x->CSCORDERNO,\
        :x->REMARKTEXT

/* SqlMacros-Define of INVOICENOSOLD ******************************************/

#define INVOICENOSOLD_ZEIGER(x) \
        :x->DATUM,\
        :x->CSCORDERNO,\
        :x->REMARKTEXT
#define INVOICENOSOLD_ZEIGERSEL(x) \
        :x->DATUM,\
        :x->CSCORDERNO,\
        :x->REMARKTEXT

/* SqlMacros-Define of ORDERPERIOD ********************************************/

#define ORDERPERIOD_ZEIGER(x) \
        :x->CUSTOMERNO,\
        :x->TOURID,\
        :x->DATUMKOMMI,\
        :x->CONSTIME,\
        :x->ID,\
        :x->BRANCHNO,\
        :x->WEEKDAY,\
        :x->FROMTIME,\
        :x->TOTIME,\
        :x->ORDER_PERIOD_ID,\
        :x->MAINTIME,\
        :x->TOURINAKTIV,\
        :x->KIPPZEIT,\
        :x->ANZ_ERFASST,\
        :x->ANZ_FAKTUR
#define ORDERPERIOD_ZEIGERSEL(x) \
        :x->CUSTOMERNO,\
        :x->TOURID,\
        :x->DATUMKOMMI,\
        :x->CONSTIME,\
        :x->ID,\
        :x->BRANCHNO,\
        :x->WEEKDAY,\
        :x->FROMTIME,\
        :x->TOTIME,\
        :x->ORDER_PERIOD_ID,\
        :x->MAINTIME,\
        :x->TOURINAKTIV,\
        :x->KIPPZEIT,\
        :x->ANZ_ERFASST,\
        :x->ANZ_FAKTUR

/* SqlMacros-Define of ORIGINTYPESETTINGSPF ***********************************/

#define ORIGINTYPESETTINGSPF_ZEIGER(x) \
        :x->ORIGINTYPE,\
        :x->SETTINGACTIVATED,\
        :x->BRANCHNO,\
        :x->ISORDERCONSOLIDATION,\
        :x->ENDOFORDERCONS,\
        :x->ORDERCONSDURATION
#define ORIGINTYPESETTINGSPF_ZEIGERSEL(x) \
        :x->ORIGINTYPE,\
        :x->SETTINGACTIVATED,\
        :x->ORIGINDEVICE,\
        :x->BRANCHNO,\
        :x->ISORDERCONSOLIDATION,\
        :x->ENDOFORDERCONS,\
        :x->ORDERCONSDURATION

/* SqlMacros-Define of REMARKTYPES ********************************************/

#define REMARKTYPES_ZEIGER(x) \
        :x->REMARKTYPE,\
        :x->REMARKNAME
#define REMARKTYPES_ZEIGERSEL(x) \
        :x->REMARKTYPE,\
        :x->REMARKNAME

/* SqlMacros-Define of SPECIALNUMBERS *****************************************/

#define SPECIALNUMBERS_ZEIGER(x) \
        :x->CSCORDERNO,\
        :x->RELATIONNOTYPE,\
        :x->RELATIONNO
#define SPECIALNUMBERS_ZEIGERSEL(x) \
        :x->CSCORDERNO,\
        :x->RELATIONNOTYPE,\
        :x->RELATIONNO

/* SqlMacros-Define of SPECIALNUMBERSOLD **************************************/

#define SPECIALNUMBERSOLD_ZEIGER(x) \
        :x->DATE,\
        :x->CSCORDERNO,\
        :x->RELATIONNOTYPE,\
        :x->RELATIONNO
#define SPECIALNUMBERSOLD_ZEIGERSEL(x) \
        :x->DATE,\
        :x->CSCORDERNO,\
        :x->RELATIONNOTYPE,\
        :x->RELATIONNO

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define CHECKDFREASON_H
#define CHECKDFREASON_ANZ ( sizeof(CHECKDFREASON_BES) / sizeof(struct buf_desc) )
#define CHECKKLRELEASED_H
#define CHECKKLRELEASED_ANZ ( sizeof(CHECKKLRELEASED_BES) / sizeof(struct buf_desc) )
#define CHECKORDERNODD_H
#define CHECKORDERNODD_ANZ ( sizeof(CHECKORDERNODD_BES) / sizeof(struct buf_desc) )
#define CHECKORDERZEROD_H
#define CHECKORDERZEROD_ANZ ( sizeof(CHECKORDERZEROD_BES) / sizeof(struct buf_desc) )
#define CHECKORDERZERODOLD_H
#define CHECKORDERZERODOLD_ANZ ( sizeof(CHECKORDERZERODOLD_BES) / sizeof(struct buf_desc) )
#define CHECKORDERLABEL_H
#define CHECKORDERLABEL_ANZ ( sizeof(CHECKORDERLABEL_BES) / sizeof(struct buf_desc) )
#define DRIVER_H
#define DRIVER_ANZ ( sizeof(DRIVER_BES) / sizeof(struct buf_desc) )
#define INVOICENOS_H
#define INVOICENOS_ANZ ( sizeof(INVOICENOS_BES) / sizeof(struct buf_desc) )
#define INVOICENOSOLD_H
#define INVOICENOSOLD_ANZ ( sizeof(INVOICENOSOLD_BES) / sizeof(struct buf_desc) )
#define ORDERPERIOD_H
#define ORDERPERIOD_ANZ ( sizeof(ORDERPERIOD_BES) / sizeof(struct buf_desc) )
#define ORIGINTYPESETTINGSPF_H
#define ORIGINTYPESETTINGSPF_ANZ ( sizeof(ORIGINTYPESETTINGSPF_BES) / sizeof(struct buf_desc) )
#define REMARKTYPES_H
#define REMARKTYPES_ANZ ( sizeof(REMARKTYPES_BES) / sizeof(struct buf_desc) )
#define SPECIALNUMBERS_H
#define SPECIALNUMBERS_ANZ ( sizeof(SPECIALNUMBERS_BES) / sizeof(struct buf_desc) )
#define SPECIALNUMBERSOLD_H
#define SPECIALNUMBERSOLD_ANZ ( sizeof(SPECIALNUMBERSOLD_BES) / sizeof(struct buf_desc) )
#endif

#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of CHECKDFREASON *******************************************/

#ifndef TRANSCLASS
typedef struct N_CHECKDFREASON {
    long KDAUFTRAGNR;
    char EVENTDESCRIPTION[255];
    short EVENTCODE;
} checkdfreasonS;
#else /* TRANSCLASS */
typedef struct N_CHECKDFREASON {
    long KDAUFTRAGNR;
    char EVENTDESCRIPTION[255];
    short EVENTCODE;

    bool operator == (const N_CHECKDFREASON& right) const {
        return (
            KDAUFTRAGNR == right.KDAUFTRAGNR &&
            !strcmp(EVENTDESCRIPTION, right.EVENTDESCRIPTION) &&
            EVENTCODE == right.EVENTCODE
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        KDAUFTRAGNR = 0;
        strcpy(EVENTDESCRIPTION, " " );
        EVENTCODE = 0;
#endif
    }
} checkdfreasonS;
#endif /* TRANSCLASS */

/* original struct of CHECKKLRELEASED *****************************************/

#ifndef TRANSCLASS
typedef struct N_CHECKKLRELEASED {
    long KDAUFTRAGNR;
    short ISRELEASED;
} checkklreleasedS;
#else /* TRANSCLASS */
typedef struct N_CHECKKLRELEASED {
    long KDAUFTRAGNR;
    short ISRELEASED;

    bool operator == (const N_CHECKKLRELEASED& right) const {
        return (
            KDAUFTRAGNR == right.KDAUFTRAGNR &&
            ISRELEASED == right.ISRELEASED
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        KDAUFTRAGNR = 0;
        ISRELEASED = 0;
#endif
    }
} checkklreleasedS;
#endif /* TRANSCLASS */

/* original struct of CHECKORDERNODD ******************************************/

#ifndef TRANSCLASS
typedef struct N_CHECKORDERNODD {
    long CSCORDERNO;
} checkordernoddS;
#else /* TRANSCLASS */
typedef struct N_CHECKORDERNODD {
    long CSCORDERNO;

    bool operator == (const N_CHECKORDERNODD& right) const {
        return (
            CSCORDERNO == right.CSCORDERNO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        CSCORDERNO = 0;
#endif
    }
} checkordernoddS;
#endif /* TRANSCLASS */

/* original struct of CHECKORDERZEROD *****************************************/

#ifndef TRANSCLASS
typedef struct N_CHECKORDERZEROD {
    long KDAUFTRAGNR;
    double ORDVALFTAXFS;
} checkorderzerodS;
#else /* TRANSCLASS */
typedef struct N_CHECKORDERZEROD {
    long KDAUFTRAGNR;
    double ORDVALFTAXFS;

    bool operator == (const N_CHECKORDERZEROD& right) const {
        return (
            KDAUFTRAGNR == right.KDAUFTRAGNR &&
            ORDVALFTAXFS == right.ORDVALFTAXFS
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        KDAUFTRAGNR = 0;
        ORDVALFTAXFS = 0;
#endif
    }
} checkorderzerodS;
#endif /* TRANSCLASS */

/* original struct of CHECKORDERZERODOLD **************************************/

#ifndef TRANSCLASS
typedef struct N_CHECKORDERZERODOLD {
    long DATUM;
    long KDAUFTRAGNR;
    double ORDVALFTAXFS;
} checkorderzerodoldS;
#else /* TRANSCLASS */
typedef struct N_CHECKORDERZERODOLD {
    long DATUM;
    long KDAUFTRAGNR;
    double ORDVALFTAXFS;

    bool operator == (const N_CHECKORDERZERODOLD& right) const {
        return (
            DATUM == right.DATUM &&
            KDAUFTRAGNR == right.KDAUFTRAGNR &&
            ORDVALFTAXFS == right.ORDVALFTAXFS
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        DATUM = 0;
        KDAUFTRAGNR = 0;
        ORDVALFTAXFS = 0;
#endif
    }
} checkorderzerodoldS;
#endif /* TRANSCLASS */

/* original struct of CHECKORDERLABEL *****************************************/

#ifndef TRANSCLASS
typedef struct N_CHECKORDERLABEL {
    long KDAUFTRAGNR;
    short ORDERLABELTYP;
} checkorderlabelS;
#else /* TRANSCLASS */
typedef struct N_CHECKORDERLABEL {
    long KDAUFTRAGNR;
    short ORDERLABELTYP;

    bool operator == (const N_CHECKORDERLABEL& right) const {
        return (
            KDAUFTRAGNR == right.KDAUFTRAGNR &&
            ORDERLABELTYP == right.ORDERLABELTYP
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        KDAUFTRAGNR = 0;
        ORDERLABELTYP = 0;
#endif
    }
} checkorderlabelS;
#endif /* TRANSCLASS */

/* original struct of DRIVER **************************************************/

#ifndef TRANSCLASS
typedef struct N_DRIVER {
    long DATUM;
    long KDAUFTRAGNR;
    char INVOICENUMBER[16];
    char DRIVERNAME[31];
    long DRIVERID;
} driverS;
#else /* TRANSCLASS */
typedef struct N_DRIVER {
    long DATUM;
    long KDAUFTRAGNR;
    char INVOICENUMBER[16];
    char DRIVERNAME[31];
    long DRIVERID;

    bool operator == (const N_DRIVER& right) const {
        return (
            DATUM == right.DATUM &&
            KDAUFTRAGNR == right.KDAUFTRAGNR &&
            !strcmp(INVOICENUMBER, right.INVOICENUMBER) &&
            !strcmp(DRIVERNAME, right.DRIVERNAME) &&
            DRIVERID == right.DRIVERID
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        DATUM = 0;
        KDAUFTRAGNR = 0;
        strcpy(INVOICENUMBER, " " );
        strcpy(DRIVERNAME, " " );
        DRIVERID = 0;
#endif
    }
} driverS;
#endif /* TRANSCLASS */

/* original struct of INVOICENOS **********************************************/

#ifndef TRANSCLASS
typedef struct N_INVOICENOS {
    long CSCORDERNO;
    char REMARKTEXT[251];
    long FETCH_REL;
} invoicenosS;
#else /* TRANSCLASS */
typedef struct N_INVOICENOS {
    long CSCORDERNO;
    char REMARKTEXT[251];
    long FETCH_REL;
    bool operator == (const N_INVOICENOS& right) const {
        return (
            CSCORDERNO == right.CSCORDERNO &&
            !strcmp(REMARKTEXT, right.REMARKTEXT)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        CSCORDERNO = 0;
        strcpy(REMARKTEXT, " " );
#endif
    }
} invoicenosS;
#endif /* TRANSCLASS */

/* original struct of INVOICENOSOLD *******************************************/

#ifndef TRANSCLASS
typedef struct N_INVOICENOSOLD {
    long DATUM;
    long CSCORDERNO;
    char REMARKTEXT[251];
    long FETCH_REL;
} invoicenosoldS;
#else /* TRANSCLASS */
typedef struct N_INVOICENOSOLD {
    long DATUM;
    long CSCORDERNO;
    char REMARKTEXT[251];
    long FETCH_REL;
    bool operator == (const N_INVOICENOSOLD& right) const {
        return (
            DATUM == right.DATUM &&
            CSCORDERNO == right.CSCORDERNO &&
            !strcmp(REMARKTEXT, right.REMARKTEXT)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        DATUM = 0;
        CSCORDERNO = 0;
        strcpy(REMARKTEXT, " " );
#endif
    }
} invoicenosoldS;
#endif /* TRANSCLASS */

/* original struct of ORDERPERIOD *********************************************/

#ifndef TRANSCLASS
typedef struct N_ORDERPERIOD {
    long CUSTOMERNO;
    char TOURID[7];
    long DATUMKOMMI;
    long CONSTIME;
    long ID;
    short BRANCHNO;
    short WEEKDAY;
    long FROMTIME;
    long TOTIME;
    long ORDER_PERIOD_ID;
    long MAINTIME;
    char TOURINAKTIV[2];
    short KIPPZEIT;
    long ANZ_ERFASST;
    long ANZ_FAKTUR;
    long FETCH_REL;
} orderperiodS;
#else /* TRANSCLASS */
typedef struct N_ORDERPERIOD {
    long CUSTOMERNO;
    char TOURID[7];
    long DATUMKOMMI;
    long CONSTIME;
    long ID;
    short BRANCHNO;
    short WEEKDAY;
    long FROMTIME;
    long TOTIME;
    long ORDER_PERIOD_ID;
    long MAINTIME;
    char TOURINAKTIV[2];
    short KIPPZEIT;
    long ANZ_ERFASST;
    long ANZ_FAKTUR;
    long FETCH_REL;
    bool operator == (const N_ORDERPERIOD& right) const {
        return (
            CUSTOMERNO == right.CUSTOMERNO &&
            !strcmp(TOURID, right.TOURID) &&
            DATUMKOMMI == right.DATUMKOMMI &&
            CONSTIME == right.CONSTIME &&
            ID == right.ID &&
            BRANCHNO == right.BRANCHNO &&
            WEEKDAY == right.WEEKDAY &&
            FROMTIME == right.FROMTIME &&
            TOTIME == right.TOTIME &&
            ORDER_PERIOD_ID == right.ORDER_PERIOD_ID &&
            MAINTIME == right.MAINTIME &&
            !strcmp(TOURINAKTIV, right.TOURINAKTIV) &&
            KIPPZEIT == right.KIPPZEIT &&
            ANZ_ERFASST == right.ANZ_ERFASST &&
            ANZ_FAKTUR == right.ANZ_FAKTUR
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        CUSTOMERNO = 0;
        strcpy(TOURID, " " );
        DATUMKOMMI = 0;
        CONSTIME = 0;
        ID = 0;
        BRANCHNO = 0;
        WEEKDAY = 0;
        FROMTIME = 0;
        TOTIME = 0;
        ORDER_PERIOD_ID = 0;
        MAINTIME = 0;
        strcpy(TOURINAKTIV, " " );
        KIPPZEIT = 0;
        ANZ_ERFASST = 0;
        ANZ_FAKTUR = 0;
#endif
    }
} orderperiodS;
#endif /* TRANSCLASS */

/* original struct of ORIGINTYPESETTINGSPF ************************************/

#ifndef TRANSCLASS
typedef struct N_ORIGINTYPESETTINGSPF {
    short ORIGINTYPE;
    short SETTINGACTIVATED;
    char ORIGINDEVICE[21];
    short BRANCHNO;
    short ISORDERCONSOLIDATION;
    long ENDOFORDERCONS;
    long ORDERCONSDURATION;
    long FETCH_REL;
} origintypesettingspfS;
#else /* TRANSCLASS */
typedef struct N_ORIGINTYPESETTINGSPF {
    short ORIGINTYPE;
    short SETTINGACTIVATED;
    char ORIGINDEVICE[21];
    short BRANCHNO;
    short ISORDERCONSOLIDATION;
    long ENDOFORDERCONS;
    long ORDERCONSDURATION;
    long FETCH_REL;
    bool operator == (const N_ORIGINTYPESETTINGSPF& right) const {
        return (
            ORIGINTYPE == right.ORIGINTYPE &&
            SETTINGACTIVATED == right.SETTINGACTIVATED &&
            !strcmp(ORIGINDEVICE, right.ORIGINDEVICE) &&
            BRANCHNO == right.BRANCHNO &&
            ISORDERCONSOLIDATION == right.ISORDERCONSOLIDATION &&
            ENDOFORDERCONS == right.ENDOFORDERCONS &&
            ORDERCONSDURATION == right.ORDERCONSDURATION
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        ORIGINTYPE = 0;
        SETTINGACTIVATED = 0;
        strcpy(ORIGINDEVICE, " " );
        BRANCHNO = 0;
        ISORDERCONSOLIDATION = 0;
        ENDOFORDERCONS = 0;
        ORDERCONSDURATION = 0;
#endif
    }
} origintypesettingspfS;
#endif /* TRANSCLASS */

/* original struct of REMARKTYPES *********************************************/

#ifndef TRANSCLASS
typedef struct N_REMARKTYPES {
    short REMARKTYPE;
    char REMARKNAME[51];
    long FETCH_REL;
} remarktypesS;
#else /* TRANSCLASS */
typedef struct N_REMARKTYPES {
    short REMARKTYPE;
    char REMARKNAME[51];
    long FETCH_REL;
    bool operator == (const N_REMARKTYPES& right) const {
        return (
            REMARKTYPE == right.REMARKTYPE &&
            !strcmp(REMARKNAME, right.REMARKNAME)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        REMARKTYPE = 0;
        strcpy(REMARKNAME, " " );
#endif
    }
} remarktypesS;
#endif /* TRANSCLASS */

/* original struct of SPECIALNUMBERS ******************************************/

#ifndef TRANSCLASS
typedef struct N_SPECIALNUMBERS {
    long CSCORDERNO;
    short RELATIONNOTYPE;
    long RELATIONNO;
} specialnumbersS;
#else /* TRANSCLASS */
typedef struct N_SPECIALNUMBERS {
    long CSCORDERNO;
    short RELATIONNOTYPE;
    long RELATIONNO;

    bool operator == (const N_SPECIALNUMBERS& right) const {
        return (
            CSCORDERNO == right.CSCORDERNO &&
            RELATIONNOTYPE == right.RELATIONNOTYPE &&
            RELATIONNO == right.RELATIONNO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        CSCORDERNO = 0;
        RELATIONNOTYPE = 0;
        RELATIONNO = 0;
#endif
    }
} specialnumbersS;
#endif /* TRANSCLASS */

/* original struct of SPECIALNUMBERSOLD ***************************************/

#ifndef TRANSCLASS
typedef struct N_SPECIALNUMBERSOLD {
    long DATE;
    long CSCORDERNO;
    short RELATIONNOTYPE;
    long RELATIONNO;
} specialnumbersoldS;
#else /* TRANSCLASS */
typedef struct N_SPECIALNUMBERSOLD {
    long DATE;
    long CSCORDERNO;
    short RELATIONNOTYPE;
    long RELATIONNO;

    bool operator == (const N_SPECIALNUMBERSOLD& right) const {
        return (
            DATE == right.DATE &&
            CSCORDERNO == right.CSCORDERNO &&
            RELATIONNOTYPE == right.RELATIONNOTYPE &&
            RELATIONNO == right.RELATIONNO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        DATE = 0;
        CSCORDERNO = 0;
        RELATIONNOTYPE = 0;
        RELATIONNO = 0;
#endif
    }
} specialnumbersoldS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of CHECKDFREASON *******************************/

struct C_CHECKDFREASON {
    long KDAUFTRAGNR;
    char EVENTDESCRIPTION[255];
    short EVENTCODE;
};
/* Structur with real chartype of CHECKKLRELEASED *****************************/

struct C_CHECKKLRELEASED {
    long KDAUFTRAGNR;
    short ISRELEASED;
};
/* Structur with real chartype of CHECKORDERNODD ******************************/

struct C_CHECKORDERNODD {
    long CSCORDERNO;
};
/* Structur with real chartype of CHECKORDERZEROD *****************************/

struct C_CHECKORDERZEROD {
    long KDAUFTRAGNR;
    double ORDVALFTAXFS;
};
/* Structur with real chartype of CHECKORDERZERODOLD **************************/

struct C_CHECKORDERZERODOLD {
    long DATUM;
    long KDAUFTRAGNR;
    double ORDVALFTAXFS;
};
/* Structur with real chartype of CHECKORDERLABEL *****************************/

struct C_CHECKORDERLABEL {
    long KDAUFTRAGNR;
    short ORDERLABELTYP;
};
/* Structur with real chartype of DRIVER **************************************/

struct C_DRIVER {
    long DATUM;
    long KDAUFTRAGNR;
    char INVOICENUMBER[16];
    char DRIVERNAME[31];
    long DRIVERID;
};
/* Structur with real chartype of INVOICENOS **********************************/

struct C_INVOICENOS {
    long CSCORDERNO;
    char REMARKTEXT[251];
    long FETCH_REL;
};
/* Structur with real chartype of INVOICENOSOLD *******************************/

struct C_INVOICENOSOLD {
    long DATUM;
    long CSCORDERNO;
    char REMARKTEXT[251];
    long FETCH_REL;
};
/* Structur with real chartype of ORDERPERIOD *********************************/

struct C_ORDERPERIOD {
    long CUSTOMERNO;
    char TOURID[7];
    long DATUMKOMMI;
    long CONSTIME;
    long ID;
    short BRANCHNO;
    short WEEKDAY;
    long FROMTIME;
    long TOTIME;
    long ORDER_PERIOD_ID;
    long MAINTIME;
    char TOURINAKTIV;
    short KIPPZEIT;
    long ANZ_ERFASST;
    long ANZ_FAKTUR;
    long FETCH_REL;
};
/* Structur with real chartype of ORIGINTYPESETTINGSPF ************************/

struct C_ORIGINTYPESETTINGSPF {
    short ORIGINTYPE;
    short SETTINGACTIVATED;
    char ORIGINDEVICE[21];
    short BRANCHNO;
    short ISORDERCONSOLIDATION;
    long ENDOFORDERCONS;
    long ORDERCONSDURATION;
    long FETCH_REL;
};
/* Structur with real chartype of REMARKTYPES *********************************/

struct C_REMARKTYPES {
    short REMARKTYPE;
    char REMARKNAME[51];
    long FETCH_REL;
};
/* Structur with real chartype of SPECIALNUMBERS ******************************/

struct C_SPECIALNUMBERS {
    long CSCORDERNO;
    short RELATIONNOTYPE;
    long RELATIONNO;
};
/* Structur with real chartype of SPECIALNUMBERSOLD ***************************/

struct C_SPECIALNUMBERSOLD {
    long DATE;
    long CSCORDERNO;
    short RELATIONNOTYPE;
    long RELATIONNO;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of CHECKDFREASON *****************************/

struct I_CHECKDFREASON {
    short KDAUFTRAGNR;
    short EVENTDESCRIPTION;
    short EVENTCODE;
};
/* Sizetype  Structur (buf_desc) of CHECKKLRELEASED ***************************/

struct I_CHECKKLRELEASED {
    short KDAUFTRAGNR;
    short ISRELEASED;
};
/* Sizetype  Structur (buf_desc) of CHECKORDERNODD ****************************/

struct I_CHECKORDERNODD {
    short CSCORDERNO;
};
/* Sizetype  Structur (buf_desc) of CHECKORDERZEROD ***************************/

struct I_CHECKORDERZEROD {
    short KDAUFTRAGNR;
    short ORDVALFTAXFS;
};
/* Sizetype  Structur (buf_desc) of CHECKORDERZERODOLD ************************/

struct I_CHECKORDERZERODOLD {
    short DATUM;
    short KDAUFTRAGNR;
    short ORDVALFTAXFS;
};
/* Sizetype  Structur (buf_desc) of CHECKORDERLABEL ***************************/

struct I_CHECKORDERLABEL {
    short KDAUFTRAGNR;
    short ORDERLABELTYP;
};
/* Sizetype  Structur (buf_desc) of DRIVER ************************************/

struct I_DRIVER {
    short DATUM;
    short KDAUFTRAGNR;
    short INVOICENUMBER;
    short DRIVERNAME;
    short DRIVERID;
};
/* Sizetype  Structur (buf_desc) of INVOICENOS ********************************/

struct I_INVOICENOS {
    short CSCORDERNO;
    short REMARKTEXT;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of INVOICENOSOLD *****************************/

struct I_INVOICENOSOLD {
    short DATUM;
    short CSCORDERNO;
    short REMARKTEXT;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of ORDERPERIOD *******************************/

struct I_ORDERPERIOD {
    short CUSTOMERNO;
    short TOURID;
    short DATUMKOMMI;
    short CONSTIME;
    short ID;
    short BRANCHNO;
    short WEEKDAY;
    short FROMTIME;
    short TOTIME;
    short ORDER_PERIOD_ID;
    short MAINTIME;
    short TOURINAKTIV;
    short KIPPZEIT;
    short ANZ_ERFASST;
    short ANZ_FAKTUR;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of ORIGINTYPESETTINGSPF **********************/

struct I_ORIGINTYPESETTINGSPF {
    short ORIGINTYPE;
    short SETTINGACTIVATED;
    short ORIGINDEVICE;
    short BRANCHNO;
    short ISORDERCONSOLIDATION;
    short ENDOFORDERCONS;
    short ORDERCONSDURATION;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of REMARKTYPES *******************************/

struct I_REMARKTYPES {
    short REMARKTYPE;
    short REMARKNAME;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of SPECIALNUMBERS ****************************/

struct I_SPECIALNUMBERS {
    short CSCORDERNO;
    short RELATIONNOTYPE;
    short RELATIONNO;
};
/* Sizetype  Structur (buf_desc) of SPECIALNUMBERSOLD *************************/

struct I_SPECIALNUMBERSOLD {
    short DATE;
    short CSCORDERNO;
    short RELATIONNOTYPE;
    short RELATIONNO;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CHECKDFREASON ***************************************/

#if defined (BUF_DESC)
static struct buf_desc CHECKDFREASON_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 254, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CHECKDFREASON_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 254, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* Structur (buf_desc) of CHECKKLRELEASED *************************************/

#if defined (BUF_DESC)
static struct buf_desc CHECKKLRELEASED_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CHECKKLRELEASED_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* Structur (buf_desc) of CHECKORDERNODD **************************************/

#if defined (BUF_DESC)
static struct buf_desc CHECKORDERNODD_BES [] = {
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CHECKORDERNODD_BES [] = {
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of CHECKORDERZEROD *************************************/

#if defined (BUF_DESC)
static struct buf_desc CHECKORDERZEROD_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_D, 11, 2 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CHECKORDERZEROD_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_D, 11, 2 },
};
#endif

/* Structur (buf_desc) of CHECKORDERZERODOLD **********************************/

#if defined (BUF_DESC)
static struct buf_desc CHECKORDERZERODOLD_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 11, 2 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CHECKORDERZERODOLD_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 11, 2 },
};
#endif

/* Structur (buf_desc) of CHECKORDERLABEL *************************************/

#if defined (BUF_DESC)
static struct buf_desc CHECKORDERLABEL_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CHECKORDERLABEL_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* Structur (buf_desc) of DRIVER **********************************************/

#if defined (BUF_DESC)
static struct buf_desc DRIVER_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 15, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc DRIVER_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 15, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of INVOICENOS ******************************************/

#if defined (BUF_DESC)
static struct buf_desc INVOICENOS_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 250, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc INVOICENOS_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 250, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of INVOICENOSOLD ***************************************/

#if defined (BUF_DESC)
static struct buf_desc INVOICENOSOLD_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 250, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc INVOICENOSOLD_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 250, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of ORDERPERIOD *****************************************/

#if defined (BUF_DESC)
static struct buf_desc ORDERPERIOD_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L ,  11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc ORDERPERIOD_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L ,  11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of ORIGINTYPESETTINGSPF ********************************/

#if defined (BUF_DESC)
static struct buf_desc ORIGINTYPESETTINGSPF_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 20, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc ORIGINTYPESETTINGSPF_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 20, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of REMARKTYPES *****************************************/

#if defined (BUF_DESC)
static struct buf_desc REMARKTYPES_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 50, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc REMARKTYPES_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 50, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of SPECIALNUMBERS **************************************/

#if defined (BUF_DESC)
static struct buf_desc SPECIALNUMBERS_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc SPECIALNUMBERS_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of SPECIALNUMBERSOLD ***********************************/

#if defined (BUF_DESC)
static struct buf_desc SPECIALNUMBERSOLD_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc SPECIALNUMBERSOLD_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* FunctionNumber-Define of CheckDFReason *************************************/

#define CHECKDFREASON_SELEVENT 1676

/* FunctionNumber-Define of CheckKLReleased ***********************************/

#define CHECKKLRELEASED_SELRELEASED 1755

/* FunctionNumber-Define of CheckOrderNoDD ************************************/

#define CHECKORDERNODD_CHECKNODD 1753

/* FunctionNumber-Define of CheckOrderZerod ***********************************/

#define CHECKORDERZEROD_SELAUFWERT 1593

/* FunctionNumber-Define of CheckOrderZerodOld ********************************/

#define CHECKORDERZERODOLD_SELAUFWERT 1594

/* FunctionNumber-Define of CheckOrderlabel ***********************************/

#define CHECKORDERLABEL_SELLABELTYPE 1613

/* FunctionNumber-Define of Driver ********************************************/

#define DRIVER_SELACT 1553
#define DRIVER_SELOLD 1554

/* FunctionNumber-Define of InvoiceNos ****************************************/

#define INVOICENOS_SELLIST 1730

/* FunctionNumber-Define of InvoiceNosOld *************************************/

#define INVOICENOSOLD_SELLIST 1731

/* FunctionNumber-Define of OrderPeriod ***************************************/

#define ORDERPERIOD_CHECKOPOVERLAP 1620
#define ORDERPERIOD_DELOPOPTFORDAY 1627
#define ORDERPERIOD_DELETEOPANDOPT 1617
#define ORDERPERIOD_DELETEOPFORDAY 1631
#define ORDERPERIOD_DELETEOPT 1636
#define ORDERPERIOD_DELETEOPTFORDAY 1630
#define ORDERPERIOD_INSERTOPANDOPT 1611
#define ORDERPERIOD_INSERTOPT 1624
#define ORDERPERIOD_SELCONSTIME 1609
#define ORDERPERIOD_SELHIGHKIPPTIME 1612
#define ORDERPERIOD_SELOPCHILDCOUNT 1637
#define ORDERPERIOD_SELOPWEEKDAYS 1623
#define ORDERPERIOD_SELTIMESLASTTOUR 1635
#define ORDERPERIOD_SELTOURDATA 1607
#define ORDERPERIOD_SELTOURFORIDF 1621
#define ORDERPERIOD_SELWEEKDAYS4TOUR 1622
#define ORDERPERIOD_UPDATETIME 1610
#define ORDERPERIOD_UPDATETIMESINGLE 1634

/* FunctionNumber-Define of OriginTypeSettingsPf ******************************/

#define ORIGINTYPESETTINGSPF_DELETE 1674
#define ORIGINTYPESETTINGSPF_INSERT 1673
#define ORIGINTYPESETTINGSPF_SELLIST 1671
#define ORIGINTYPESETTINGSPF_SELLISTNOTDEFINED 1675
#define ORIGINTYPESETTINGSPF_UPDATE 1672

/* FunctionNumber-Define of RemarkTypes ***************************************/

#define REMARKTYPES_SELLIST 1777

/* FunctionNumber-Define of SpecialNumbers ************************************/

#define SPECIALNUMBERS_SELNUMBER 1736

/* FunctionNumber-Define of SpecialNumbersOld *********************************/

#define SPECIALNUMBERSOLD_SELNUMBER 1754

#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of CheckDFReason *********************************/

#define SelEvent 1676

/* Old-FunctionNumber-Define of CheckKLReleased *******************************/

#define SelReleased 1755

/* Old-FunctionNumber-Define of CheckOrderNoDD ********************************/

#define CheckNoDD 1753

/* Old-FunctionNumber-Define of CheckOrderZerod *******************************/

#define SelAufwert 1593

/* Old-FunctionNumber-Define of CheckOrderZerodOld ****************************/

#define SelAufwert 1594

/* Old-FunctionNumber-Define of CheckOrderlabel *******************************/

#define SelLabelType 1613

/* Old-FunctionNumber-Define of Driver ****************************************/

#define SelAct 1553
#define SelOld 1554

/* Old-FunctionNumber-Define of InvoiceNos ************************************/

#define SelList 1730

/* Old-FunctionNumber-Define of InvoiceNosOld *********************************/

#define SelList 1731

/* Old-FunctionNumber-Define of OrderPeriod ***********************************/

#define CheckOPOverLap 1620
#define DelOPOPTForDay 1627
#define DeleteOPAndOPT 1617
#define DeleteOPForDay 1631
#define DeleteOPT 1636
#define DeleteOPTForDay 1630
#define InsertOPAndOPT 1611
#define InsertOPT 1624
#define SelConsTime 1609
#define SelHighKippTime 1612
#define SelOPChildCount 1637
#define SelOPWeekdays 1623
#define SelTimesLastTour 1635
#define SelTourData 1607
#define SelTourForIDF 1621
#define SelWeekdays4Tour 1622
#define UpdateTime 1610
#define UpdateTimeSingle 1634

/* Old-FunctionNumber-Define of OriginTypeSettingsPf **************************/

#define Delete 1674
#define Insert 1673
#define SelList 1671
#define SelListNotDefined 1675
#define Update 1672

/* Old-FunctionNumber-Define of RemarkTypes ***********************************/

#define SelList 1777

/* Old-FunctionNumber-Define of SpecialNumbers ********************************/

#define SelNumber 1736

/* Old-FunctionNumber-Define of SpecialNumbersOld *****************************/

#define SelNumber 1754

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

class CCHECKDFREASON : public ppDadeVirtual {
public:
    checkdfreasonS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<checkdfreasonS> lst; // class list

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
                     vector< checkdfreasonS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     checkdfreasonS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< checkdfreasonS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<checkdfreasonS>::iterator
                 beginList() { return lst.begin(); }
    vector<checkdfreasonS>::iterator
                 endList  () { return lst.end  (); }

    long         GetKdauftragnr() const { return s.KDAUFTRAGNR; }
    const char*  GetEventdescription(ppString & t) const { t = s.EVENTDESCRIPTION; t.erasespace(ppString::END); return t.c_str(); }
    short        GetEventcode() const { return s.EVENTCODE; }

    const checkdfreasonS &
                 GetStruct() const { return s; }
    void         SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
    void         SetEventdescription(const ppString & t) { ppGStrCopy(s.EVENTDESCRIPTION, t.c_str(), L_CHECKDFREASON_EVENTDESCRIPTION); }
    void         SetEventcode(short t) { s.EVENTCODE = t; }

    void         SetStruct(const checkdfreasonS & t) { s = t; }

    int          SelEvent(int pos = 0) { int ret = UniqueServerCall(1676, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCHECKDFREASON() {
        ::buf_default((void *)&s, CHECKDFREASON_BES, CHECKDFREASON_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCHECKDFREASON() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CHECKDFREASON_BES, CHECKDFREASON_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1676 ) return UniqueServerCall(1676, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CHECKDFREASON & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.EVENTDESCRIPTION);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CHECKDFREASON_BES, (int)CHECKDFREASON_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CCHECKKLRELEASED : public ppDadeVirtual {
public:
    checkklreleasedS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<checkklreleasedS> lst; // class list

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
                     vector< checkklreleasedS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     checkklreleasedS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< checkklreleasedS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<checkklreleasedS>::iterator
                 beginList() { return lst.begin(); }
    vector<checkklreleasedS>::iterator
                 endList  () { return lst.end  (); }

    long         GetKdauftragnr() const { return s.KDAUFTRAGNR; }
    short        GetIsreleased() const { return s.ISRELEASED; }

    const checkklreleasedS &
                 GetStruct() const { return s; }
    void         SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
    void         SetIsreleased(short t) { s.ISRELEASED = t; }

    void         SetStruct(const checkklreleasedS & t) { s = t; }

    int          SelReleased(int pos = 0) { int ret = UniqueServerCall(1755, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCHECKKLRELEASED() {
        ::buf_default((void *)&s, CHECKKLRELEASED_BES, CHECKKLRELEASED_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCHECKKLRELEASED() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CHECKKLRELEASED_BES, CHECKKLRELEASED_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1755 ) return UniqueServerCall(1755, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CHECKKLRELEASED & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CHECKKLRELEASED_BES, (int)CHECKKLRELEASED_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CCHECKORDERNODD : public ppDadeVirtual {
public:
    checkordernoddS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<checkordernoddS> lst; // class list

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
                     vector< checkordernoddS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     checkordernoddS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< checkordernoddS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<checkordernoddS>::iterator
                 beginList() { return lst.begin(); }
    vector<checkordernoddS>::iterator
                 endList  () { return lst.end  (); }

    long         GetCscorderno() const { return s.CSCORDERNO; }

    const checkordernoddS &
                 GetStruct() const { return s; }
    void         SetCscorderno(long t) { s.CSCORDERNO = t; }

    void         SetStruct(const checkordernoddS & t) { s = t; }

    int          CheckNoDD(int pos = 0) { int ret = UniqueServerCall(1753, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCHECKORDERNODD() {
        ::buf_default((void *)&s, CHECKORDERNODD_BES, CHECKORDERNODD_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCHECKORDERNODD() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CHECKORDERNODD_BES, CHECKORDERNODD_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1753 ) return UniqueServerCall(1753, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CHECKORDERNODD & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CHECKORDERNODD_BES, (int)CHECKORDERNODD_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CCHECKORDERZEROD : public ppDadeVirtual {
public:
    checkorderzerodS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<checkorderzerodS> lst; // class list

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
                     vector< checkorderzerodS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     checkorderzerodS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< checkorderzerodS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<checkorderzerodS>::iterator
                 beginList() { return lst.begin(); }
    vector<checkorderzerodS>::iterator
                 endList  () { return lst.end  (); }

    long         GetKdauftragnr() const { return s.KDAUFTRAGNR; }
    double       GetOrdvalftaxfs() const { return s.ORDVALFTAXFS; }

    const checkorderzerodS &
                 GetStruct() const { return s; }
    void         SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
    void         SetOrdvalftaxfs(double t) { s.ORDVALFTAXFS = t; }

    void         SetStruct(const checkorderzerodS & t) { s = t; }

    int          SelAufwert(int pos = 0) { int ret = UniqueServerCall(1593, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCHECKORDERZEROD() {
        ::buf_default((void *)&s, CHECKORDERZEROD_BES, CHECKORDERZEROD_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCHECKORDERZEROD() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CHECKORDERZEROD_BES, CHECKORDERZEROD_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1593 ) return UniqueServerCall(1593, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CHECKORDERZEROD & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CHECKORDERZEROD_BES, (int)CHECKORDERZEROD_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CCHECKORDERZERODOLD : public ppDadeVirtual {
public:
    checkorderzerodoldS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<checkorderzerodoldS> lst; // class list

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
                     vector< checkorderzerodoldS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     checkorderzerodoldS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< checkorderzerodoldS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<checkorderzerodoldS>::iterator
                 beginList() { return lst.begin(); }
    vector<checkorderzerodoldS>::iterator
                 endList  () { return lst.end  (); }

    long         GetDatum() const { return s.DATUM; }
    long         GetKdauftragnr() const { return s.KDAUFTRAGNR; }
    double       GetOrdvalftaxfs() const { return s.ORDVALFTAXFS; }

    const checkorderzerodoldS &
                 GetStruct() const { return s; }
    void         SetDatum(long t) { s.DATUM = t; }
    void         SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
    void         SetOrdvalftaxfs(double t) { s.ORDVALFTAXFS = t; }

    void         SetStruct(const checkorderzerodoldS & t) { s = t; }

    int          SelAufwert(int pos = 0) { int ret = UniqueServerCall(1594, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCHECKORDERZERODOLD() {
        ::buf_default((void *)&s, CHECKORDERZERODOLD_BES, CHECKORDERZERODOLD_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCHECKORDERZERODOLD() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CHECKORDERZERODOLD_BES, CHECKORDERZERODOLD_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1594 ) return UniqueServerCall(1594, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CHECKORDERZERODOLD & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CHECKORDERZERODOLD_BES, (int)CHECKORDERZERODOLD_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CCHECKORDERLABEL : public ppDadeVirtual {
public:
    checkorderlabelS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<checkorderlabelS> lst; // class list

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
                     vector< checkorderlabelS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     checkorderlabelS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< checkorderlabelS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<checkorderlabelS>::iterator
                 beginList() { return lst.begin(); }
    vector<checkorderlabelS>::iterator
                 endList  () { return lst.end  (); }

    long         GetKdauftragnr() const { return s.KDAUFTRAGNR; }
    short        GetOrderlabeltyp() const { return s.ORDERLABELTYP; }

    const checkorderlabelS &
                 GetStruct() const { return s; }
    void         SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
    void         SetOrderlabeltyp(short t) { s.ORDERLABELTYP = t; }

    void         SetStruct(const checkorderlabelS & t) { s = t; }

    int          SelLabelType(int pos = 0) { int ret = UniqueServerCall(1613, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCHECKORDERLABEL() {
        ::buf_default((void *)&s, CHECKORDERLABEL_BES, CHECKORDERLABEL_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCHECKORDERLABEL() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CHECKORDERLABEL_BES, CHECKORDERLABEL_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1613 ) return UniqueServerCall(1613, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CHECKORDERLABEL & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CHECKORDERLABEL_BES, (int)CHECKORDERLABEL_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CDRIVER : public ppDadeVirtual {
public:
    driverS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<driverS> lst; // class list

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
                     vector< driverS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     driverS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< driverS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<driverS>::iterator
                 beginList() { return lst.begin(); }
    vector<driverS>::iterator
                 endList  () { return lst.end  (); }

    long         GetDatum() const { return s.DATUM; }
    long         GetKdauftragnr() const { return s.KDAUFTRAGNR; }
    const char*  GetInvoicenumber(ppString & t) const { t = s.INVOICENUMBER; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetDrivername(ppString & t) const { t = s.DRIVERNAME; t.erasespace(ppString::END); return t.c_str(); }
    long         GetDriverid() const { return s.DRIVERID; }

    const driverS &
                 GetStruct() const { return s; }
    void         SetDatum(long t) { s.DATUM = t; }
    void         SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
    void         SetInvoicenumber(const ppString & t) { ppGStrCopy(s.INVOICENUMBER, t.c_str(), L_DRIVER_INVOICENUMBER); }
    void         SetDrivername(const ppString & t) { ppGStrCopy(s.DRIVERNAME, t.c_str(), L_DRIVER_DRIVERNAME); }
    void         SetDriverid(long t) { s.DRIVERID = t; }

    void         SetStruct(const driverS & t) { s = t; }

    int          SelAct(int pos = 0) { int ret = UniqueServerCall(1553, pos); Strip(s); return ret; }
    int          SelOld(int pos = 0) { int ret = UniqueServerCall(1554, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CDRIVER() {
        ::buf_default((void *)&s, DRIVER_BES, DRIVER_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CDRIVER() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, DRIVER_BES, DRIVER_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1553 ) return UniqueServerCall(1553, pos);
        if ( fkt_nr == 1554 ) return UniqueServerCall(1554, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_DRIVER & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.INVOICENUMBER);
        ppGStripLast(d.DRIVERNAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, DRIVER_BES, (int)DRIVER_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CINVOICENOS : public ppDadeVirtual {
public:
    invoicenosS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<invoicenosS> lst; // class list

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
                     vector< invoicenosS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     invoicenosS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< invoicenosS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<invoicenosS>::iterator
                 beginList() { return lst.begin(); }
    vector<invoicenosS>::iterator
                 endList  () { return lst.end  (); }

    long         GetCscorderno() const { return s.CSCORDERNO; }
    const char*  GetRemarktext(ppString & t) const { t = s.REMARKTEXT; t.erasespace(ppString::END); return t.c_str(); }

    const invoicenosS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetCscorderno(long t) { s.CSCORDERNO = t; }
    void         SetRemarktext(const ppString & t) { ppGStrCopy(s.REMARKTEXT, t.c_str(), L_INVOICENOS_REMARKTEXT); }

    void         SetStruct(const invoicenosS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1730, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CINVOICENOS() {
        ::buf_default((void *)&s, INVOICENOS_BES, INVOICENOS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CINVOICENOS() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, INVOICENOS_BES, INVOICENOS_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, INVOICENOS_BES, (int)INVOICENOS_ANZ, error_msg);
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
        if ( fkt_nr == 1730 ) return CursorServerCall(1730, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_INVOICENOS & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.REMARKTEXT);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, INVOICENOS_BES, (int)INVOICENOS_ANZ, error_msg);
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
        CINVOICENOS c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, INVOICENOS_BES, (int)INVOICENOS_ANZ, error_msg);
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

class CINVOICENOSOLD : public ppDadeVirtual {
public:
    invoicenosoldS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<invoicenosoldS> lst; // class list

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
                     vector< invoicenosoldS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     invoicenosoldS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< invoicenosoldS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<invoicenosoldS>::iterator
                 beginList() { return lst.begin(); }
    vector<invoicenosoldS>::iterator
                 endList  () { return lst.end  (); }

    long         GetDatum() const { return s.DATUM; }
    long         GetCscorderno() const { return s.CSCORDERNO; }
    const char*  GetRemarktext(ppString & t) const { t = s.REMARKTEXT; t.erasespace(ppString::END); return t.c_str(); }

    const invoicenosoldS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetDatum(long t) { s.DATUM = t; }
    void         SetCscorderno(long t) { s.CSCORDERNO = t; }
    void         SetRemarktext(const ppString & t) { ppGStrCopy(s.REMARKTEXT, t.c_str(), L_INVOICENOSOLD_REMARKTEXT); }

    void         SetStruct(const invoicenosoldS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1731, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CINVOICENOSOLD() {
        ::buf_default((void *)&s, INVOICENOSOLD_BES, INVOICENOSOLD_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CINVOICENOSOLD() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, INVOICENOSOLD_BES, INVOICENOSOLD_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, INVOICENOSOLD_BES, (int)INVOICENOSOLD_ANZ, error_msg);
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
        if ( fkt_nr == 1731 ) return CursorServerCall(1731, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_INVOICENOSOLD & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.REMARKTEXT);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, INVOICENOSOLD_BES, (int)INVOICENOSOLD_ANZ, error_msg);
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
        CINVOICENOSOLD c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, INVOICENOSOLD_BES, (int)INVOICENOSOLD_ANZ, error_msg);
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

class CORDERPERIOD : public ppDadeVirtual {
public:
    orderperiodS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<orderperiodS> lst; // class list

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
                     vector< orderperiodS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     orderperiodS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< orderperiodS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<orderperiodS>::iterator
                 beginList() { return lst.begin(); }
    vector<orderperiodS>::iterator
                 endList  () { return lst.end  (); }

    long         GetCustomerno() const { return s.CUSTOMERNO; }
    const char*  GetTourid(ppString & t) const { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
    long         GetDatumkommi() const { return s.DATUMKOMMI; }
    long         GetConstime() const { return s.CONSTIME; }
    long         GetId() const { return s.ID; }
    short        GetBranchno() const { return s.BRANCHNO; }
    short        GetWeekday() const { return s.WEEKDAY; }
    long         GetFromtime() const { return s.FROMTIME; }
    long         GetTotime() const { return s.TOTIME; }
    long         GetOrder_period_id() const { return s.ORDER_PERIOD_ID; }
    long         GetMaintime() const { return s.MAINTIME; }
    char         GetTourinaktiv() const { return s.TOURINAKTIV[0]; }
    short        GetKippzeit() const { return s.KIPPZEIT; }
    long         GetAnz_erfasst() const { return s.ANZ_ERFASST; }
    long         GetAnz_faktur() const { return s.ANZ_FAKTUR; }

    const orderperiodS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetTourid(const ppString & t) { ppGStrCopy(s.TOURID, t.c_str(), L_ORDERPERIOD_TOURID); }
    void         SetDatumkommi(long t) { s.DATUMKOMMI = t; }
    void         SetConstime(long t) { s.CONSTIME = t; }
    void         SetId(long t) { s.ID = t; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetWeekday(short t) { s.WEEKDAY = t; }
    void         SetFromtime(long t) { s.FROMTIME = t; }
    void         SetTotime(long t) { s.TOTIME = t; }
    void         SetOrder_period_id(long t) { s.ORDER_PERIOD_ID = t; }
    void         SetMaintime(long t) { s.MAINTIME = t; }
    void         SetTourinaktiv(char t) { s.TOURINAKTIV[0] = t; s.TOURINAKTIV[1] = '\0';}
    void         SetKippzeit(short t) { s.KIPPZEIT = t; }
    void         SetAnz_erfasst(long t) { s.ANZ_ERFASST = t; }
    void         SetAnz_faktur(long t) { s.ANZ_FAKTUR = t; }

    void         SetStruct(const orderperiodS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          CheckOPOverLap(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1620, FetchRel, pos); return ret; }
    int          DelOPOPTForDay(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1627, FetchRel, pos); return ret; }
    int          DeleteOPAndOPT(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1617, FetchRel, pos); return ret; }
    int          DeleteOPForDay(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1631, FetchRel, pos); return ret; }
    int          DeleteOPT(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1636, FetchRel, pos); return ret; }
    int          DeleteOPTForDay(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1630, FetchRel, pos); return ret; }
    int          InsertOPAndOPT(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1611, FetchRel, pos); return ret; }
    int          InsertOPT(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1624, FetchRel, pos); return ret; }
    int          SelConsTime(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1609, FetchRel, pos); return ret; }
    int          SelHighKippTime(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1612, FetchRel, pos); return ret; }
    int          SelOPChildCount(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1637, FetchRel, pos); return ret; }
    int          SelOPWeekdays(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1623, FetchRel, pos); return ret; }
    int          SelTimesLastTour(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1635, FetchRel, pos); return ret; }
    int          SelTourData(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1607, FetchRel, pos); return ret; }
    int          SelTourForIDF(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1621, FetchRel, pos); return ret; }
    int          SelWeekdays4Tour(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1622, FetchRel, pos); return ret; }
    int          UpdateTime(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1610, FetchRel, pos); return ret; }
    int          UpdateTimeSingle(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1634, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CORDERPERIOD() {
        ::buf_default((void *)&s, ORDERPERIOD_BES, ORDERPERIOD_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CORDERPERIOD() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, ORDERPERIOD_BES, ORDERPERIOD_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, ORDERPERIOD_BES, (int)ORDERPERIOD_ANZ, error_msg);
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
        if ( fkt_nr == 1620 ) return CursorServerCall(1620, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1627 ) return CursorServerCall(1627, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1617 ) return CursorServerCall(1617, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1631 ) return CursorServerCall(1631, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1636 ) return CursorServerCall(1636, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1630 ) return CursorServerCall(1630, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1611 ) return CursorServerCall(1611, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1624 ) return CursorServerCall(1624, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1609 ) return CursorServerCall(1609, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1612 ) return CursorServerCall(1612, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1637 ) return CursorServerCall(1637, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1623 ) return CursorServerCall(1623, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1635 ) return CursorServerCall(1635, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1607 ) return CursorServerCall(1607, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1621 ) return CursorServerCall(1621, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1622 ) return CursorServerCall(1622, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1610 ) return CursorServerCall(1610, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1634 ) return CursorServerCall(1634, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_ORDERPERIOD & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.TOURID);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, ORDERPERIOD_BES, (int)ORDERPERIOD_ANZ, error_msg);
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
        CORDERPERIOD c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, ORDERPERIOD_BES, (int)ORDERPERIOD_ANZ, error_msg);
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

class CORIGINTYPESETTINGSPF : public ppDadeVirtual {
public:
    origintypesettingspfS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<origintypesettingspfS> lst; // class list

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
                     vector< origintypesettingspfS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     origintypesettingspfS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< origintypesettingspfS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<origintypesettingspfS>::iterator
                 beginList() { return lst.begin(); }
    vector<origintypesettingspfS>::iterator
                 endList  () { return lst.end  (); }

    short        GetOrigintype() const { return s.ORIGINTYPE; }
    short        GetSettingactivated() const { return s.SETTINGACTIVATED; }
    const char*  GetOrigindevice(ppString & t) const { t = s.ORIGINDEVICE; t.erasespace(ppString::END); return t.c_str(); }
    short        GetBranchno() const { return s.BRANCHNO; }
    short        GetIsorderconsolidation() const { return s.ISORDERCONSOLIDATION; }
    long         GetEndofordercons() const { return s.ENDOFORDERCONS; }
    long         GetOrderconsduration() const { return s.ORDERCONSDURATION; }

    const origintypesettingspfS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetOrigintype(short t) { s.ORIGINTYPE = t; }
    void         SetSettingactivated(short t) { s.SETTINGACTIVATED = t; }
    void         SetOrigindevice(const ppString & t) { ppGStrCopy(s.ORIGINDEVICE, t.c_str(), L_ORIGINTYPESETTINGSPF_ORIGINDEVICE); }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetIsorderconsolidation(short t) { s.ISORDERCONSOLIDATION = t; }
    void         SetEndofordercons(long t) { s.ENDOFORDERCONS = t; }
    void         SetOrderconsduration(long t) { s.ORDERCONSDURATION = t; }

    void         SetStruct(const origintypesettingspfS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          Delete(int pos = 0) { return UniqueServerCall(1674, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1673, pos); Strip(s); return ret; }
    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1671, FetchRel, pos); return ret; }
    int          SelListNotDefined(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1675, FetchRel, pos); return ret; }
    int          Update(int pos = 0) { int ret = UniqueServerCall(1672, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CORIGINTYPESETTINGSPF() {
        ::buf_default((void *)&s, ORIGINTYPESETTINGSPF_BES, ORIGINTYPESETTINGSPF_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CORIGINTYPESETTINGSPF() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, ORIGINTYPESETTINGSPF_BES, ORIGINTYPESETTINGSPF_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, ORIGINTYPESETTINGSPF_BES, (int)ORIGINTYPESETTINGSPF_ANZ, error_msg);
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
        if ( fkt_nr == 1674 ) return UniqueServerCall(1674, pos);
        if ( fkt_nr == 1673 ) return UniqueServerCall(1673, pos);
        if ( fkt_nr == 1671 ) return CursorServerCall(1671, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1675 ) return CursorServerCall(1675, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1672 ) return UniqueServerCall(1672, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_ORIGINTYPESETTINGSPF & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.ORIGINDEVICE);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, ORIGINTYPESETTINGSPF_BES, (int)ORIGINTYPESETTINGSPF_ANZ, error_msg);
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
        CORIGINTYPESETTINGSPF c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, ORIGINTYPESETTINGSPF_BES, (int)ORIGINTYPESETTINGSPF_ANZ, error_msg);
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

class CREMARKTYPES : public ppDadeVirtual {
public:
    remarktypesS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<remarktypesS> lst; // class list

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
                     vector< remarktypesS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     remarktypesS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< remarktypesS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<remarktypesS>::iterator
                 beginList() { return lst.begin(); }
    vector<remarktypesS>::iterator
                 endList  () { return lst.end  (); }

    short        GetRemarktype() const { return s.REMARKTYPE; }
    const char*  GetRemarkname(ppString & t) const { t = s.REMARKNAME; t.erasespace(ppString::END); return t.c_str(); }

    const remarktypesS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetRemarktype(short t) { s.REMARKTYPE = t; }
    void         SetRemarkname(const ppString & t) { ppGStrCopy(s.REMARKNAME, t.c_str(), L_REMARKTYPES_REMARKNAME); }

    void         SetStruct(const remarktypesS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1777, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CREMARKTYPES() {
        ::buf_default((void *)&s, REMARKTYPES_BES, REMARKTYPES_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CREMARKTYPES() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, REMARKTYPES_BES, REMARKTYPES_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, REMARKTYPES_BES, (int)REMARKTYPES_ANZ, error_msg);
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
        if ( fkt_nr == 1777 ) return CursorServerCall(1777, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_REMARKTYPES & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.REMARKNAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, REMARKTYPES_BES, (int)REMARKTYPES_ANZ, error_msg);
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
        CREMARKTYPES c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, REMARKTYPES_BES, (int)REMARKTYPES_ANZ, error_msg);
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

class CSPECIALNUMBERS : public ppDadeVirtual {
public:
    specialnumbersS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<specialnumbersS> lst; // class list

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
                     vector< specialnumbersS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     specialnumbersS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< specialnumbersS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<specialnumbersS>::iterator
                 beginList() { return lst.begin(); }
    vector<specialnumbersS>::iterator
                 endList  () { return lst.end  (); }

    long         GetCscorderno() const { return s.CSCORDERNO; }
    short        GetRelationnotype() const { return s.RELATIONNOTYPE; }
    long         GetRelationno() const { return s.RELATIONNO; }

    const specialnumbersS &
                 GetStruct() const { return s; }
    void         SetCscorderno(long t) { s.CSCORDERNO = t; }
    void         SetRelationnotype(short t) { s.RELATIONNOTYPE = t; }
    void         SetRelationno(long t) { s.RELATIONNO = t; }

    void         SetStruct(const specialnumbersS & t) { s = t; }

    int          SelNumber(int pos = 0) { int ret = UniqueServerCall(1736, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CSPECIALNUMBERS() {
        ::buf_default((void *)&s, SPECIALNUMBERS_BES, SPECIALNUMBERS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CSPECIALNUMBERS() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, SPECIALNUMBERS_BES, SPECIALNUMBERS_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1736 ) return UniqueServerCall(1736, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_SPECIALNUMBERS & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, SPECIALNUMBERS_BES, (int)SPECIALNUMBERS_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CSPECIALNUMBERSOLD : public ppDadeVirtual {
public:
    specialnumbersoldS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<specialnumbersoldS> lst; // class list

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
                     vector< specialnumbersoldS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     specialnumbersoldS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< specialnumbersoldS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<specialnumbersoldS>::iterator
                 beginList() { return lst.begin(); }
    vector<specialnumbersoldS>::iterator
                 endList  () { return lst.end  (); }

    long         GetDate() const { return s.DATE; }
    long         GetCscorderno() const { return s.CSCORDERNO; }
    short        GetRelationnotype() const { return s.RELATIONNOTYPE; }
    long         GetRelationno() const { return s.RELATIONNO; }

    const specialnumbersoldS &
                 GetStruct() const { return s; }
    void         SetDate(long t) { s.DATE = t; }
    void         SetCscorderno(long t) { s.CSCORDERNO = t; }
    void         SetRelationnotype(short t) { s.RELATIONNOTYPE = t; }
    void         SetRelationno(long t) { s.RELATIONNO = t; }

    void         SetStruct(const specialnumbersoldS & t) { s = t; }

    int          SelNumber(int pos = 0) { int ret = UniqueServerCall(1754, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CSPECIALNUMBERSOLD() {
        ::buf_default((void *)&s, SPECIALNUMBERSOLD_BES, SPECIALNUMBERSOLD_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CSPECIALNUMBERSOLD() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, SPECIALNUMBERSOLD_BES, SPECIALNUMBERSOLD_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1754 ) return UniqueServerCall(1754, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_SPECIALNUMBERSOLD & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, SPECIALNUMBERSOLD_BES, (int)SPECIALNUMBERSOLD_ANZ, error_msg);
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
