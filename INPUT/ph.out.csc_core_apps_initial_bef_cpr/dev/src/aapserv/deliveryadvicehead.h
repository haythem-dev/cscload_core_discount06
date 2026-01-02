#ifndef __PP_DELIVERYADVICEHEAD_H_
#define __PP_DELIVERYADVICEHEAD_H_

/******************************************************************************/
/* c:\prri\Headerfiles\Deliveryadvicehead *************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of DELIVERYADVICEHEAD ****************************************/

#define L_DELIVERYADVICEHEAD_BRANCHNO 6
#define L_DELIVERYADVICEHEAD_CUSTOMERNO 11
#define L_DELIVERYADVICEHEAD_DELIVERYADVICEDATE 11
#define L_DELIVERYADVICEHEAD_DELIVERYADVICENO 10
#define L_DELIVERYADVICEHEAD_PHARMOSORDERNO 11
#define L_DELIVERYADVICEHEAD_CSCORDERNO 11
#define L_DELIVERYADVICEHEAD_COMPLETED 1
#define L_DELIVERYADVICEHEAD_SPECIALDOCUMENTTYPE 1
#define L_DELIVERYADVICEHEAD_TOURID 6
#define L_DELIVERYADVICEHEAD_DUEDATE 11
#define L_DELIVERYADVICEHEAD_KDAUFTRAGART 2
#define L_DELIVERYADVICEHEAD_PICKINGTYPE 1
#define L_DELIVERYADVICEHEAD_BOOKINGTYPE 1
#define L_DELIVERYADVICEHEAD_REQUESTED 6
#define L_DELIVERYADVICEHEAD_CONFIRMED 6
#define L_DELIVERYADVICEHEAD_ORDERLABEL 40
#define L_DELIVERYADVICEHEAD_CANCELLED 6
#define L_DELIVERYADVICEHEAD_DEPOSITVALUE 11
#define N_DELIVERYADVICEHEAD_DEPOSITVALUE 4
#define L_DELIVERYADVICEHEAD_LOGISTICSERVICECOST 11
#define N_DELIVERYADVICEHEAD_LOGISTICSERVICECOST 4
#define L_DELIVERYADVICEHEAD_BATCHCORRECTIONADVICE 6
#define L_DELIVERYADVICEHEAD_CSCUSER 11
#define L_DELIVERYADVICEHEAD_MATURITYDAYS 6
#define L_DELIVERYADVICEHEAD_TIMEOFINVOICECREATION 11
#define L_DELIVERYADVICEHEAD_LINEFEE 5
#define N_DELIVERYADVICEHEAD_LINEFEE 2
#define L_DELIVERYADVICEHEAD_PACKAGEFEE 5
#define N_DELIVERYADVICEHEAD_PACKAGEFEE 2
#define L_DELIVERYADVICEHEAD_CONTRACTID 30

/* Length/Count-Define of DELIVERYADVICEHEAD **********************************/

#define LS_DELIVERYADVICEHEAD_BRANCHNO 5 + 1
#define LS_DELIVERYADVICEHEAD_CUSTOMERNO 10 + 1
#define LS_DELIVERYADVICEHEAD_DELIVERYADVICEDATE 10 + 1
#define LS_DELIVERYADVICEHEAD_DELIVERYADVICENO 10 + 1
#define LS_DELIVERYADVICEHEAD_PHARMOSORDERNO 10 + 1
#define LS_DELIVERYADVICEHEAD_CSCORDERNO 10 + 1
#define LS_DELIVERYADVICEHEAD_COMPLETED 1 + 1
#define LS_DELIVERYADVICEHEAD_SPECIALDOCUMENTTYPE 1 + 1
#define LS_DELIVERYADVICEHEAD_TOURID 6 + 1
#define LS_DELIVERYADVICEHEAD_DUEDATE 10 + 1
#define LS_DELIVERYADVICEHEAD_KDAUFTRAGART 2 + 1
#define LS_DELIVERYADVICEHEAD_PICKINGTYPE 1 + 1
#define LS_DELIVERYADVICEHEAD_BOOKINGTYPE 1 + 1
#define LS_DELIVERYADVICEHEAD_REQUESTED 5 + 1
#define LS_DELIVERYADVICEHEAD_CONFIRMED 5 + 1
#define LS_DELIVERYADVICEHEAD_ORDERLABEL 40 + 1
#define LS_DELIVERYADVICEHEAD_CANCELLED 5 + 1
#define LS_DELIVERYADVICEHEAD_DEPOSITVALUE 11 + 2
#define LS_DELIVERYADVICEHEAD_LOGISTICSERVICECOST 11 + 2
#define LS_DELIVERYADVICEHEAD_BATCHCORRECTIONADVICE 5 + 1
#define LS_DELIVERYADVICEHEAD_CSCUSER 10 + 1
#define LS_DELIVERYADVICEHEAD_MATURITYDAYS 5 + 1
#define LS_DELIVERYADVICEHEAD_TIMEOFINVOICECREATION 10 + 1
#define LS_DELIVERYADVICEHEAD_LINEFEE 5 + 2
#define LS_DELIVERYADVICEHEAD_PACKAGEFEE 5 + 2
#define LS_DELIVERYADVICEHEAD_CONTRACTID 30 + 1

#define DELIVERYADVICEHEADBRANCHNO 0
#define DELIVERYADVICEHEADCUSTOMERNO 1
#define DELIVERYADVICEHEADDELIVERYADVICEDATE 2
#define DELIVERYADVICEHEADDELIVERYADVICENO 3
#define DELIVERYADVICEHEADPHARMOSORDERNO 4
#define DELIVERYADVICEHEADCSCORDERNO 5
#define DELIVERYADVICEHEADCOMPLETED 6
#define DELIVERYADVICEHEADSPECIALDOCUMENTTYPE 7
#define DELIVERYADVICEHEADTOURID 8
#define DELIVERYADVICEHEADDUEDATE 9
#define DELIVERYADVICEHEADKDAUFTRAGART 10
#define DELIVERYADVICEHEADPICKINGTYPE 11
#define DELIVERYADVICEHEADBOOKINGTYPE 12
#define DELIVERYADVICEHEADREQUESTED 13
#define DELIVERYADVICEHEADCONFIRMED 14
#define DELIVERYADVICEHEADORDERLABEL 15
#define DELIVERYADVICEHEADCANCELLED 16
#define DELIVERYADVICEHEADDEPOSITVALUE 17
#define DELIVERYADVICEHEADLOGISTICSERVICECOST 18
#define DELIVERYADVICEHEADBATCHCORRECTIONADVICE 19
#define DELIVERYADVICEHEADCSCUSER 20
#define DELIVERYADVICEHEADMATURITYDAYS 21
#define DELIVERYADVICEHEADTIMEOFINVOICECREATION 22
#define DELIVERYADVICEHEADLINEFEE 23
#define DELIVERYADVICEHEADPACKAGEFEE 24
#define DELIVERYADVICEHEADCONTRACTID 25

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define DELIVERYADVICEHEAD_H
#define DELIVERYADVICEHEAD_ANZ ( sizeof(DELIVERYADVICEHEAD_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of DELIVERYADVICEHEAD ********************************************/

#define DELIVERYADVICEHEAD_LISTE \
        DADUMMY.BRANCHNO,\
        DADUMMY.CUSTOMERNO,\
        DADUMMY.DELIVERYADVICEDATE,\
        DADUMMY.DELIVERYADVICENO,\
        DADUMMY.PHARMOSORDERNO,\
        DADUMMY.CSCORDERNO,\
        DADUMMY.COMPLETED,\
        DADUMMY.SPECIALDOCUMENTTYPE,\
        DADUMMY.TOURID,\
        DADUMMY.DUEDATE,\
        DADUMMY.KDAUFTRAGART,\
        DADUMMY.PICKINGTYPE,\
        DADUMMY.BOOKINGTYPE,\
        DADUMMY.REQUESTED,\
        DADUMMY.CONFIRMED,\
        DADUMMY.ORDERLABEL,\
        DADUMMY.CANCELLED,\
        DADUMMY.DEPOSITVALUE,\
        DADUMMY.LOGISTICSERVICECOST,\
        DADUMMY.BATCHCORRECTIONADVICE,\
        DADUMMY.CSCUSER,\
        DADUMMY.MATURITYDAYS,\
        DADUMMY.TIMEOFINVOICECREATION,\
        DADUMMY.LINEFEE,\
        DADUMMY.PACKAGEFEE,\
        DADUMMY.CONTRACTID
#define DELIVERYADVICEHEAD_LISTE_390 \
        BRANCHNO,\
        CUSTOMERNO,\
        DELIVERYADVICEDATE,\
        DELIVERYADVICENO,\
        PHARMOSORDERNO,\
        CSCORDERNO,\
        COMPLETED,\
        SPECIALDOCUMENTTYPE,\
        TOURID,\
        DUEDATE,\
        KDAUFTRAGART,\
        PICKINGTYPE,\
        BOOKINGTYPE,\
        REQUESTED,\
        CONFIRMED,\
        ORDERLABEL,\
        CANCELLED,\
        DEPOSITVALUE,\
        LOGISTICSERVICECOST,\
        BATCHCORRECTIONADVICE,\
        CSCUSER,\
        MATURITYDAYS,\
        TIMEOFINVOICECREATION,\
        LINEFEE,\
        PACKAGEFEE,\
        CONTRACTID
#define DELIVERYADVICEHEAD_PLISTE \
        "DADUMMY.BRANCHNO,"\
        "DADUMMY.CUSTOMERNO,"\
        "DADUMMY.DELIVERYADVICEDATE,"\
        "DADUMMY.DELIVERYADVICENO,"\
        "DADUMMY.PHARMOSORDERNO,"\
        "DADUMMY.CSCORDERNO,"\
        "DADUMMY.COMPLETED,"\
        "DADUMMY.SPECIALDOCUMENTTYPE,"\
        "DADUMMY.TOURID,"\
        "DADUMMY.DUEDATE,"\
        "DADUMMY.KDAUFTRAGART,"\
        "DADUMMY.PICKINGTYPE,"\
        "DADUMMY.BOOKINGTYPE,"\
        "DADUMMY.REQUESTED,"\
        "DADUMMY.CONFIRMED,"\
        "DADUMMY.ORDERLABEL,"\
        "DADUMMY.CANCELLED,"\
        "DADUMMY.DEPOSITVALUE,"\
        "DADUMMY.LOGISTICSERVICECOST,"\
        "DADUMMY.BATCHCORRECTIONADVICE,"\
        "DADUMMY.CSCUSER,"\
        "DADUMMY.MATURITYDAYS,"\
        "DADUMMY.TIMEOFINVOICECREATION,"\
        "DADUMMY.LINEFEE,"\
        "DADUMMY.PACKAGEFEE,"\
        "DADUMMY.CONTRACTID"
#define DELIVERYADVICEHEAD_PELISTE \
        "BRANCHNO,"\
        "CUSTOMERNO,"\
        "DELIVERYADVICEDATE,"\
        "DELIVERYADVICENO,"\
        "PHARMOSORDERNO,"\
        "CSCORDERNO,"\
        "COMPLETED,"\
        "SPECIALDOCUMENTTYPE,"\
        "TOURID,"\
        "DUEDATE,"\
        "KDAUFTRAGART,"\
        "PICKINGTYPE,"\
        "BOOKINGTYPE,"\
        "REQUESTED,"\
        "CONFIRMED,"\
        "ORDERLABEL,"\
        "CANCELLED,"\
        "DEPOSITVALUE,"\
        "LOGISTICSERVICECOST,"\
        "BATCHCORRECTIONADVICE,"\
        "CSCUSER,"\
        "MATURITYDAYS,"\
        "TIMEOFINVOICECREATION,"\
        "LINEFEE,"\
        "PACKAGEFEE,"\
        "CONTRACTID"
#define DELIVERYADVICEHEAD_UPDLISTE \
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "DELIVERYADVICEDATE=?,"\
        "DELIVERYADVICENO=?,"\
        "PHARMOSORDERNO=?,"\
        "CSCORDERNO=?,"\
        "COMPLETED=?,"\
        "SPECIALDOCUMENTTYPE=?,"\
        "TOURID=?,"\
        "DUEDATE=?,"\
        "KDAUFTRAGART=?,"\
        "PICKINGTYPE=?,"\
        "BOOKINGTYPE=?,"\
        "REQUESTED=?,"\
        "CONFIRMED=?,"\
        "ORDERLABEL=?,"\
        "CANCELLED=?,"\
        "DEPOSITVALUE=?,"\
        "LOGISTICSERVICECOST=?,"\
        "BATCHCORRECTIONADVICE=?,"\
        "CSCUSER=?,"\
        "MATURITYDAYS=?,"\
        "TIMEOFINVOICECREATION=?,"\
        "LINEFEE=?,"\
        "PACKAGEFEE=?,"\
        "CONTRACTID=?"
/* SqlMacros-Define of DELIVERYADVICEHEAD *************************************/

#define DELIVERYADVICEHEAD_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->DELIVERYADVICEDATE,\
        :x->DELIVERYADVICENO,\
        :x->PHARMOSORDERNO,\
        :x->CSCORDERNO,\
        :x->COMPLETED,\
        :x->SPECIALDOCUMENTTYPE,\
        :x->TOURID,\
        :x->DUEDATE,\
        :x->KDAUFTRAGART,\
        :x->PICKINGTYPE,\
        :x->BOOKINGTYPE,\
        :x->REQUESTED,\
        :x->CONFIRMED,\
        :x->ORDERLABEL,\
        :x->CANCELLED,\
        :x->DEPOSITVALUE,\
        :x->LOGISTICSERVICECOST,\
        :x->BATCHCORRECTIONADVICE,\
        :x->CSCUSER,\
        :x->MATURITYDAYS,\
        :x->TIMEOFINVOICECREATION,\
        :x->LINEFEE,\
        :x->PACKAGEFEE,\
        :x->CONTRACTID
#define DELIVERYADVICEHEAD_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->DELIVERYADVICEDATE,\
        :x->DELIVERYADVICENO,\
        :x->PHARMOSORDERNO,\
        :x->CSCORDERNO,\
        :x->COMPLETED,\
        :x->SPECIALDOCUMENTTYPE,\
        :x->TOURID,\
        :x->DUEDATE,\
        :x->KDAUFTRAGART,\
        :x->PICKINGTYPE,\
        :x->BOOKINGTYPE,\
        :x->REQUESTED,\
        :x->CONFIRMED,\
        :x->ORDERLABEL,\
        :x->CANCELLED,\
        :x->DEPOSITVALUE,\
        :x->LOGISTICSERVICECOST,\
        :x->BATCHCORRECTIONADVICE,\
        :x->CSCUSER,\
        :x->MATURITYDAYS,\
        :x->TIMEOFINVOICECREATION,\
        :x->LINEFEE,\
        :x->PACKAGEFEE,\
        :x->CONTRACTID
#define DELIVERYADVICEHEAD_UPDATE(x) \
        DADUMMY.BRANCHNO=:x->BRANCHNO,\
        DADUMMY.CUSTOMERNO=:x->CUSTOMERNO,\
        DADUMMY.DELIVERYADVICEDATE=:x->DELIVERYADVICEDATE,\
        DADUMMY.DELIVERYADVICENO=:x->DELIVERYADVICENO,\
        DADUMMY.PHARMOSORDERNO=:x->PHARMOSORDERNO,\
        DADUMMY.CSCORDERNO=:x->CSCORDERNO,\
        DADUMMY.COMPLETED=:x->COMPLETED,\
        DADUMMY.SPECIALDOCUMENTTYPE=:x->SPECIALDOCUMENTTYPE,\
        DADUMMY.TOURID=:x->TOURID,\
        DADUMMY.DUEDATE=:x->DUEDATE,\
        DADUMMY.KDAUFTRAGART=:x->KDAUFTRAGART,\
        DADUMMY.PICKINGTYPE=:x->PICKINGTYPE,\
        DADUMMY.BOOKINGTYPE=:x->BOOKINGTYPE,\
        DADUMMY.REQUESTED=:x->REQUESTED,\
        DADUMMY.CONFIRMED=:x->CONFIRMED,\
        DADUMMY.ORDERLABEL=:x->ORDERLABEL,\
        DADUMMY.CANCELLED=:x->CANCELLED,\
        DADUMMY.DEPOSITVALUE=:x->DEPOSITVALUE,\
        DADUMMY.LOGISTICSERVICECOST=:x->LOGISTICSERVICECOST,\
        DADUMMY.BATCHCORRECTIONADVICE=:x->BATCHCORRECTIONADVICE,\
        DADUMMY.CSCUSER=:x->CSCUSER,\
        DADUMMY.MATURITYDAYS=:x->MATURITYDAYS,\
        DADUMMY.TIMEOFINVOICECREATION=:x->TIMEOFINVOICECREATION,\
        DADUMMY.LINEFEE=:x->LINEFEE,\
        DADUMMY.PACKAGEFEE=:x->PACKAGEFEE,\
        DADUMMY.CONTRACTID=:x->CONTRACTID
/* SqlMacros390-Define of DELIVERYADVICEHEAD **********************************/

#define DELIVERYADVICEHEAD_ZEIGER_390 \
        :BRANCHNO,\
        :CUSTOMERNO,\
        :DELIVERYADVICEDATE,\
        :DELIVERYADVICENO,\
        :PHARMOSORDERNO,\
        :CSCORDERNO,\
        :COMPLETED,\
        :SPECIALDOCUMENTTYPE,\
        :TOURID,\
        :DUEDATE,\
        :KDAUFTRAGART,\
        :PICKINGTYPE,\
        :BOOKINGTYPE,\
        :REQUESTED,\
        :CONFIRMED,\
        :ORDERLABEL,\
        :CANCELLED,\
        :DEPOSITVALUE,\
        :LOGISTICSERVICECOST,\
        :BATCHCORRECTIONADVICE,\
        :CSCUSER,\
        :MATURITYDAYS,\
        :TIMEOFINVOICECREATION,\
        :LINEFEE,\
        :PACKAGEFEE,\
        :CONTRACTID
#define DELIVERYADVICEHEAD_UPDATE_390 \
        BRANCHNO=:BRANCHNO,\
        CUSTOMERNO=:CUSTOMERNO,\
        DELIVERYADVICEDATE=:DELIVERYADVICEDATE,\
        DELIVERYADVICENO=:DELIVERYADVICENO,\
        PHARMOSORDERNO=:PHARMOSORDERNO,\
        CSCORDERNO=:CSCORDERNO,\
        COMPLETED=:COMPLETED,\
        SPECIALDOCUMENTTYPE=:SPECIALDOCUMENTTYPE,\
        TOURID=:TOURID,\
        DUEDATE=:DUEDATE,\
        KDAUFTRAGART=:KDAUFTRAGART,\
        PICKINGTYPE=:PICKINGTYPE,\
        BOOKINGTYPE=:BOOKINGTYPE,\
        REQUESTED=:REQUESTED,\
        CONFIRMED=:CONFIRMED,\
        ORDERLABEL=:ORDERLABEL,\
        CANCELLED=:CANCELLED,\
        DEPOSITVALUE=:DEPOSITVALUE,\
        LOGISTICSERVICECOST=:LOGISTICSERVICECOST,\
        BATCHCORRECTIONADVICE=:BATCHCORRECTIONADVICE,\
        CSCUSER=:CSCUSER,\
        MATURITYDAYS=:MATURITYDAYS,\
        TIMEOFINVOICECREATION=:TIMEOFINVOICECREATION,\
        LINEFEE=:LINEFEE,\
        PACKAGEFEE=:PACKAGEFEE,\
        CONTRACTID=:CONTRACTID
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of DELIVERYADVICEHEAD **************************************/

#ifndef TRANSCLASS
typedef struct N_DELIVERYADVICEHEAD {
    short BRANCHNO;
    long CUSTOMERNO;
    long DELIVERYADVICEDATE;
    char DELIVERYADVICENO[11];
    long PHARMOSORDERNO;
    long CSCORDERNO;
    char COMPLETED[2];
    char SPECIALDOCUMENTTYPE[2];
    char TOURID[7];
    long DUEDATE;
    char KDAUFTRAGART[3];
    char PICKINGTYPE[2];
    char BOOKINGTYPE[2];
    short REQUESTED;
    short CONFIRMED;
    char ORDERLABEL[41];
    short CANCELLED;
    double DEPOSITVALUE;
    double LOGISTICSERVICECOST;
    short BATCHCORRECTIONADVICE;
    long CSCUSER;
    short MATURITYDAYS;
    long TIMEOFINVOICECREATION;
    double LINEFEE;
    double PACKAGEFEE;
    char CONTRACTID[31];
} deliveryadviceheadS;
#else /* TRANSCLASS */
typedef struct N_DELIVERYADVICEHEAD {
    short BRANCHNO;
    long CUSTOMERNO;
    long DELIVERYADVICEDATE;
    char DELIVERYADVICENO[11];
    long PHARMOSORDERNO;
    long CSCORDERNO;
    char COMPLETED[2];
    char SPECIALDOCUMENTTYPE[2];
    char TOURID[7];
    long DUEDATE;
    char KDAUFTRAGART[3];
    char PICKINGTYPE[2];
    char BOOKINGTYPE[2];
    short REQUESTED;
    short CONFIRMED;
    char ORDERLABEL[41];
    short CANCELLED;
    double DEPOSITVALUE;
    double LOGISTICSERVICECOST;
    short BATCHCORRECTIONADVICE;
    long CSCUSER;
    short MATURITYDAYS;
    long TIMEOFINVOICECREATION;
    double LINEFEE;
    double PACKAGEFEE;
    char CONTRACTID[31];

    bool operator == (const N_DELIVERYADVICEHEAD& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            CUSTOMERNO == right.CUSTOMERNO &&
            DELIVERYADVICEDATE == right.DELIVERYADVICEDATE &&
            !strcmp(DELIVERYADVICENO, right.DELIVERYADVICENO) &&
            PHARMOSORDERNO == right.PHARMOSORDERNO &&
            CSCORDERNO == right.CSCORDERNO &&
            !strcmp(COMPLETED, right.COMPLETED) &&
            !strcmp(SPECIALDOCUMENTTYPE, right.SPECIALDOCUMENTTYPE) &&
            !strcmp(TOURID, right.TOURID) &&
            DUEDATE == right.DUEDATE &&
            !strcmp(KDAUFTRAGART, right.KDAUFTRAGART) &&
            !strcmp(PICKINGTYPE, right.PICKINGTYPE) &&
            !strcmp(BOOKINGTYPE, right.BOOKINGTYPE) &&
            REQUESTED == right.REQUESTED &&
            CONFIRMED == right.CONFIRMED &&
            !strcmp(ORDERLABEL, right.ORDERLABEL) &&
            CANCELLED == right.CANCELLED &&
            DEPOSITVALUE == right.DEPOSITVALUE &&
            LOGISTICSERVICECOST == right.LOGISTICSERVICECOST &&
            BATCHCORRECTIONADVICE == right.BATCHCORRECTIONADVICE &&
            CSCUSER == right.CSCUSER &&
            MATURITYDAYS == right.MATURITYDAYS &&
            TIMEOFINVOICECREATION == right.TIMEOFINVOICECREATION &&
            LINEFEE == right.LINEFEE &&
            PACKAGEFEE == right.PACKAGEFEE &&
            !strcmp(CONTRACTID, right.CONTRACTID)
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
        PHARMOSORDERNO = 0;
        CSCORDERNO = 0;
        strcpy(COMPLETED, " " );
        strcpy(SPECIALDOCUMENTTYPE, " " );
        strcpy(TOURID, " " );
        DUEDATE = 0;
        strcpy(KDAUFTRAGART, " " );
        strcpy(PICKINGTYPE, " " );
        strcpy(BOOKINGTYPE, " " );
        REQUESTED = 0;
        CONFIRMED = 0;
        strcpy(ORDERLABEL, " " );
        CANCELLED = 0;
        DEPOSITVALUE = 0;
        LOGISTICSERVICECOST = 0;
        BATCHCORRECTIONADVICE = 0;
        CSCUSER = 0;
        MATURITYDAYS = 0;
        TIMEOFINVOICECREATION = 0;
        LINEFEE = 0;
        PACKAGEFEE = 0;
        strcpy(CONTRACTID, " " );
#endif
    }
} deliveryadviceheadS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of DELIVERYADVICEHEAD ********************************/

struct S_DELIVERYADVICEHEAD {
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char DELIVERYADVICEDATE[11];
    char DELIVERYADVICENO[10 + 1];
    char PHARMOSORDERNO[11];
    char CSCORDERNO[11];
    char COMPLETED[1 + 1];
    char SPECIALDOCUMENTTYPE[1 + 1];
    char TOURID[6 + 1];
    char DUEDATE[11];
    char KDAUFTRAGART[2 + 1];
    char PICKINGTYPE[1 + 1];
    char BOOKINGTYPE[1 + 1];
    char REQUESTED[7];
    char CONFIRMED[7];
    char ORDERLABEL[40 + 1];
    char CANCELLED[7];
    char DEPOSITVALUE[11 + 2];
    char LOGISTICSERVICECOST[11 + 2];
    char BATCHCORRECTIONADVICE[7];
    char CSCUSER[11];
    char MATURITYDAYS[7];
    char TIMEOFINVOICECREATION[11];
    char LINEFEE[5 + 2];
    char PACKAGEFEE[5 + 2];
    char CONTRACTID[30 + 1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of DELIVERYADVICEHEAD ***************/

struct O_DELIVERYADVICEHEAD {
    char BRANCHNO[7];
    char CUSTOMERNO[11];
    char DELIVERYADVICEDATE[11];
    char DELIVERYADVICENO[10];
    char PHARMOSORDERNO[11];
    char CSCORDERNO[11];
    char COMPLETED[1];
    char SPECIALDOCUMENTTYPE[1];
    char TOURID[6];
    char DUEDATE[11];
    char KDAUFTRAGART[2];
    char PICKINGTYPE[1];
    char BOOKINGTYPE[1];
    char REQUESTED[7];
    char CONFIRMED[7];
    char ORDERLABEL[40];
    char CANCELLED[7];
    char DEPOSITVALUE[11];
    char LOGISTICSERVICECOST[11];
    char BATCHCORRECTIONADVICE[7];
    char CSCUSER[11];
    char MATURITYDAYS[7];
    char TIMEOFINVOICECREATION[11];
    char LINEFEE[5];
    char PACKAGEFEE[5];
    char CONTRACTID[30];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of DELIVERYADVICEHEAD **************************/

struct C_DELIVERYADVICEHEAD {
    short BRANCHNO;
    long CUSTOMERNO;
    long DELIVERYADVICEDATE;
    char DELIVERYADVICENO[11];
    long PHARMOSORDERNO;
    long CSCORDERNO;
    char COMPLETED;
    char SPECIALDOCUMENTTYPE;
    char TOURID[7];
    long DUEDATE;
    char KDAUFTRAGART[3];
    char PICKINGTYPE;
    char BOOKINGTYPE;
    short REQUESTED;
    short CONFIRMED;
    char ORDERLABEL[41];
    short CANCELLED;
    double DEPOSITVALUE;
    double LOGISTICSERVICECOST;
    short BATCHCORRECTIONADVICE;
    long CSCUSER;
    short MATURITYDAYS;
    long TIMEOFINVOICECREATION;
    double LINEFEE;
    double PACKAGEFEE;
    char CONTRACTID[31];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of DELIVERYADVICEHEAD ************************/

struct I_DELIVERYADVICEHEAD {
    short BRANCHNO;
    short CUSTOMERNO;
    short DELIVERYADVICEDATE;
    short DELIVERYADVICENO;
    short PHARMOSORDERNO;
    short CSCORDERNO;
    short COMPLETED;
    short SPECIALDOCUMENTTYPE;
    short TOURID;
    short DUEDATE;
    short KDAUFTRAGART;
    short PICKINGTYPE;
    short BOOKINGTYPE;
    short REQUESTED;
    short CONFIRMED;
    short ORDERLABEL;
    short CANCELLED;
    short DEPOSITVALUE;
    short LOGISTICSERVICECOST;
    short BATCHCORRECTIONADVICE;
    short CSCUSER;
    short MATURITYDAYS;
    short TIMEOFINVOICECREATION;
    short LINEFEE;
    short PACKAGEFEE;
    short CONTRACTID;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of DELIVERYADVICEHEAD **********************************/

#if defined (BUF_DESC)
static struct buf_desc DELIVERYADVICEHEAD_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 10, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 40, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 11, 4 },
   { TYP_D, 11, 4 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 5, 2 },
   { TYP_C, 30, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc DELIVERYADVICEHEAD_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 10, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 40, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 11, 4 },
   { TYP_D, 11, 4 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 5, 2 },
   { TYP_C, 30, 0 },
};
#endif

/* description for datatypes of DELIVERYADVICEHEAD ****************************/

 #define DELIVERYADVICEHEAD_S390 \
         short BRANCHNO; \
         long CUSTOMERNO; \
         long DELIVERYADVICEDATE; \
         char DELIVERYADVICENO[11]; \
         long PHARMOSORDERNO; \
         long CSCORDERNO; \
         char COMPLETED; \
         char SPECIALDOCUMENTTYPE; \
         char TOURID[7]; \
         long DUEDATE; \
         char KDAUFTRAGART[3]; \
         char PICKINGTYPE; \
         char BOOKINGTYPE; \
         short REQUESTED; \
         short CONFIRMED; \
         char ORDERLABEL[41]; \
         short CANCELLED; \
         double DEPOSITVALUE; \
         double LOGISTICSERVICECOST; \
         short BATCHCORRECTIONADVICE; \
         long CSCUSER; \
         short MATURITYDAYS; \
         long TIMEOFINVOICECREATION; \
         double LINEFEE; \
         double PACKAGEFEE; \
         char CONTRACTID[31]; \



/* Copy-Function Struct to single Data DELIVERYADVICEHEAD *********************/

 #define DELIVERYADVICEHEAD_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
         DELIVERYADVICEDATE=_x_->DELIVERYADVICEDATE;\
          strcpy(DELIVERYADVICENO,_x_->DELIVERYADVICENO);\
         PHARMOSORDERNO=_x_->PHARMOSORDERNO;\
         CSCORDERNO=_x_->CSCORDERNO;\
         COMPLETED=_x_->COMPLETED;\
         SPECIALDOCUMENTTYPE=_x_->SPECIALDOCUMENTTYPE;\
          strcpy(TOURID,_x_->TOURID);\
         DUEDATE=_x_->DUEDATE;\
          strcpy(KDAUFTRAGART,_x_->KDAUFTRAGART);\
         PICKINGTYPE=_x_->PICKINGTYPE;\
         BOOKINGTYPE=_x_->BOOKINGTYPE;\
         REQUESTED=_x_->REQUESTED;\
         CONFIRMED=_x_->CONFIRMED;\
          strcpy(ORDERLABEL,_x_->ORDERLABEL);\
         CANCELLED=_x_->CANCELLED;\
         DEPOSITVALUE=_x_->DEPOSITVALUE;\
         LOGISTICSERVICECOST=_x_->LOGISTICSERVICECOST;\
         BATCHCORRECTIONADVICE=_x_->BATCHCORRECTIONADVICE;\
         CSCUSER=_x_->CSCUSER;\
         MATURITYDAYS=_x_->MATURITYDAYS;\
         TIMEOFINVOICECREATION=_x_->TIMEOFINVOICECREATION;\
         LINEFEE=_x_->LINEFEE;\
         PACKAGEFEE=_x_->PACKAGEFEE;\
          strcpy(CONTRACTID,_x_->CONTRACTID);\

 #define DELIVERYADVICEHEAD_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->DELIVERYADVICEDATE=DELIVERYADVICEDATE;\
          strcpy(_x_->DELIVERYADVICENO,DELIVERYADVICENO);\
          _x_->PHARMOSORDERNO=PHARMOSORDERNO;\
          _x_->CSCORDERNO=CSCORDERNO;\
          _x_->COMPLETED=COMPLETED;\
          _x_->SPECIALDOCUMENTTYPE=SPECIALDOCUMENTTYPE;\
          strcpy(_x_->TOURID,TOURID);\
          _x_->DUEDATE=DUEDATE;\
          strcpy(_x_->KDAUFTRAGART,KDAUFTRAGART);\
          _x_->PICKINGTYPE=PICKINGTYPE;\
          _x_->BOOKINGTYPE=BOOKINGTYPE;\
          _x_->REQUESTED=REQUESTED;\
          _x_->CONFIRMED=CONFIRMED;\
          strcpy(_x_->ORDERLABEL,ORDERLABEL);\
          _x_->CANCELLED=CANCELLED;\
          _x_->DEPOSITVALUE=DEPOSITVALUE;\
          _x_->LOGISTICSERVICECOST=LOGISTICSERVICECOST;\
          _x_->BATCHCORRECTIONADVICE=BATCHCORRECTIONADVICE;\
          _x_->CSCUSER=CSCUSER;\
          _x_->MATURITYDAYS=MATURITYDAYS;\
          _x_->TIMEOFINVOICECREATION=TIMEOFINVOICECREATION;\
          _x_->LINEFEE=LINEFEE;\
          _x_->PACKAGEFEE=PACKAGEFEE;\
          strcpy(_x_->CONTRACTID,CONTRACTID);\



/* FunctionNumber-Define of Deliveryadvicehead ********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of Deliveryadvicehead ****************************/


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

class CDELIVERYADVICEHEAD : public ppDadeVirtual {
public:
    deliveryadviceheadS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<deliveryadviceheadS> lst; // class list

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
                     vector< deliveryadviceheadS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     deliveryadviceheadS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< deliveryadviceheadS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<deliveryadviceheadS>::iterator
                 beginList() { return lst.begin(); }
    vector<deliveryadviceheadS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    long         GetDeliveryadvicedate() const { return s.DELIVERYADVICEDATE; }
    const char*  GetDeliveryadviceno(ppString & t) const { t = s.DELIVERYADVICENO; t.erasespace(ppString::END); return t.c_str(); }
    long         GetPharmosorderno() const { return s.PHARMOSORDERNO; }
    long         GetCscorderno() const { return s.CSCORDERNO; }
    char         GetCompleted() const { return s.COMPLETED[0]; }
    char         GetSpecialdocumenttype() const { return s.SPECIALDOCUMENTTYPE[0]; }
    const char*  GetTourid(ppString & t) const { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
    long         GetDuedate() const { return s.DUEDATE; }
    const char*  GetKdauftragart(ppString & t) const { t = s.KDAUFTRAGART; t.erasespace(ppString::END); return t.c_str(); }
    char         GetPickingtype() const { return s.PICKINGTYPE[0]; }
    char         GetBookingtype() const { return s.BOOKINGTYPE[0]; }
    short        GetRequested() const { return s.REQUESTED; }
    short        GetConfirmed() const { return s.CONFIRMED; }
    const char*  GetOrderlabel(ppString & t) const { t = s.ORDERLABEL; t.erasespace(ppString::END); return t.c_str(); }
    short        GetCancelled() const { return s.CANCELLED; }
    double       GetDepositvalue() const { return s.DEPOSITVALUE; }
    double       GetLogisticservicecost() const { return s.LOGISTICSERVICECOST; }
    short        GetBatchcorrectionadvice() const { return s.BATCHCORRECTIONADVICE; }
    long         GetCscuser() const { return s.CSCUSER; }
    short        GetMaturitydays() const { return s.MATURITYDAYS; }
    long         GetTimeofinvoicecreation() const { return s.TIMEOFINVOICECREATION; }
    double       GetLinefee() const { return s.LINEFEE; }
    double       GetPackagefee() const { return s.PACKAGEFEE; }
    const char*  GetContractid(ppString & t) const { t = s.CONTRACTID; t.erasespace(ppString::END); return t.c_str(); }

    const deliveryadviceheadS &
                 GetStruct() const { return s; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetDeliveryadvicedate(long t) { s.DELIVERYADVICEDATE = t; }
    void         SetDeliveryadviceno(const ppString & t) { ppGStrCopy(s.DELIVERYADVICENO, t.c_str(), L_DELIVERYADVICEHEAD_DELIVERYADVICENO); }
    void         SetPharmosorderno(long t) { s.PHARMOSORDERNO = t; }
    void         SetCscorderno(long t) { s.CSCORDERNO = t; }
    void         SetCompleted(char t) { s.COMPLETED[0] = t; s.COMPLETED[1] = '\0';}
    void         SetSpecialdocumenttype(char t) { s.SPECIALDOCUMENTTYPE[0] = t; s.SPECIALDOCUMENTTYPE[1] = '\0';}
    void         SetTourid(const ppString & t) { ppGStrCopy(s.TOURID, t.c_str(), L_DELIVERYADVICEHEAD_TOURID); }
    void         SetDuedate(long t) { s.DUEDATE = t; }
    void         SetKdauftragart(const ppString & t) { ppGStrCopy(s.KDAUFTRAGART, t.c_str(), L_DELIVERYADVICEHEAD_KDAUFTRAGART); }
    void         SetPickingtype(char t) { s.PICKINGTYPE[0] = t; s.PICKINGTYPE[1] = '\0';}
    void         SetBookingtype(char t) { s.BOOKINGTYPE[0] = t; s.BOOKINGTYPE[1] = '\0';}
    void         SetRequested(short t) { s.REQUESTED = t; }
    void         SetConfirmed(short t) { s.CONFIRMED = t; }
    void         SetOrderlabel(const ppString & t) { ppGStrCopy(s.ORDERLABEL, t.c_str(), L_DELIVERYADVICEHEAD_ORDERLABEL); }
    void         SetCancelled(short t) { s.CANCELLED = t; }
    void         SetDepositvalue(double t) { s.DEPOSITVALUE = t; }
    void         SetLogisticservicecost(double t) { s.LOGISTICSERVICECOST = t; }
    void         SetBatchcorrectionadvice(short t) { s.BATCHCORRECTIONADVICE = t; }
    void         SetCscuser(long t) { s.CSCUSER = t; }
    void         SetMaturitydays(short t) { s.MATURITYDAYS = t; }
    void         SetTimeofinvoicecreation(long t) { s.TIMEOFINVOICECREATION = t; }
    void         SetLinefee(double t) { s.LINEFEE = t; }
    void         SetPackagefee(double t) { s.PACKAGEFEE = t; }
    void         SetContractid(const ppString & t) { ppGStrCopy(s.CONTRACTID, t.c_str(), L_DELIVERYADVICEHEAD_CONTRACTID); }

    void         SetStruct(const deliveryadviceheadS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CDELIVERYADVICEHEAD() {
        ::buf_default((void *)&s, DELIVERYADVICEHEAD_BES, DELIVERYADVICEHEAD_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CDELIVERYADVICEHEAD() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, DELIVERYADVICEHEAD_BES, DELIVERYADVICEHEAD_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, DELIVERYADVICEHEAD_BES, (int)DELIVERYADVICEHEAD_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, DELIVERYADVICEHEAD_BES, (int)DELIVERYADVICEHEAD_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_DELIVERYADVICEHEAD & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.DELIVERYADVICENO);
        ppGStripLast(d.TOURID);
        ppGStripLast(d.KDAUFTRAGART);
        ppGStripLast(d.ORDERLABEL);
        ppGStripLast(d.CONTRACTID);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, DELIVERYADVICEHEAD_BES, (int)DELIVERYADVICEHEAD_ANZ, error_msg);
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
/* CreateSqlStatement of DELIVERYADVICEHEAD ***********************************/

 #define DELIVERYADVICEHEAD_CREATE(x) EXEC SQL create table x (\
         BRANCHNO smallint default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         DELIVERYADVICEDATE integer default 0 not null,\
         DELIVERYADVICENO varchar(10,0) default " " not null,\
         PHARMOSORDERNO integer default 0 not null,\
         CSCORDERNO integer default 0 not null,\
         COMPLETED char(1) default " " not null,\
         SPECIALDOCUMENTTYPE char(1) default " " not null,\
         TOURID char(6) default " " not null,\
         DUEDATE integer default 0 not null,\
         KDAUFTRAGART char(2) default " " not null,\
         PICKINGTYPE char(1) default " " not null,\
         BOOKINGTYPE char(1) default " " not null,\
         REQUESTED smallint default 0 not null,\
         CONFIRMED smallint default 0 not null,\
         ORDERLABEL varchar(40,0) default " " not null,\
         CANCELLED smallint default 0 not null,\
         DEPOSITVALUE decimal(11,4) default 0 not null,\
         LOGISTICSERVICECOST decimal(11,4) default 0 not null,\
         BATCHCORRECTIONADVICE smallint default 0 not null,\
         CSCUSER integer default 0 not null,\
         MATURITYDAYS smallint default 0 not null,\
         TIMEOFINVOICECREATION integer default 0 not null,\
         LINEFEE decimal(5,2) default 0 not null,\
         PACKAGEFEE decimal(5,2) default 0 not null,\
         CONTRACTID varchar(30,0) default " " not null) extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of DELIVERYADVICEHEAD *********************************/

 #define DELIVERYADVICEHEAD_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
/* DeleteIndexStatement of DELIVERYADVICEHEAD *********************************/

 #define DELIVERYADVICEHEAD_DELETE_INDEX(_X_)\
              _X_ = 0;\


#endif   // GUARD
