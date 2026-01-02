#ifndef __PP_CREMAMAIL_H_
#define __PP_CREMAMAIL_H_

/******************************************************************************/
/* c:\marathon\CremaMail ******************************************************/
/* produced by DADE 6.22.3 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of CREMAMAIL *************************************************/

#define L_CREMAMAIL_PARTNERNO 11
#define L_CREMAMAIL_ID 11
#define L_CREMAMAIL_SERVER 50
#define L_CREMAMAIL_EMAILTYPE 6
#define L_CREMAMAIL_SMTPID 11
#define L_CREMAMAIL_SMTPUSERGROUPID 11
#define L_CREMAMAIL_TYPEDATAID 11
#define L_CREMAMAIL_TYPE 6
#define L_CREMAMAIL_THRESHOLDAMOUNT 11
#define N_CREMAMAIL_THRESHOLDAMOUNT 2
#define L_CREMAMAIL_DLPERCENTAGE 5
#define N_CREMAMAIL_DLPERCENTAGE 2
#define L_CREMAMAIL_LEVELTYPE 6
#define L_CREMAMAIL_LIMIT 13
#define N_CREMAMAIL_LIMIT 2
#define L_CREMAMAIL_REASONTYPE 6
#define L_CREMAMAIL_TYPEID 11
#define L_CREMAMAIL_IDFNR 11
#define L_CREMAMAIL_SENDGVLMAIL 6
#define L_CREMAMAIL_PORT 11
#define L_CREMAMAIL_SENTFROMADDRESS 50
#define L_CREMAMAIL_APPROVALPERSONSNEEDED 6
#define L_CREMAMAIL_KDAUFTRAGNR 11
#define L_CREMAMAIL_SENTTOADDRESS 50
#define L_CREMAMAIL_GUID 36
#define L_CREMAMAIL_URL 254
#define L_CREMAMAIL_WASSEND 1
#define L_CREMAMAIL_SENDDATE 11
#define L_CREMAMAIL_CREMATYPEID 11
#define L_CREMAMAIL_BRANCHNO 6
#define L_CREMAMAIL_SENDTIME 11
#define L_CREMAMAIL_WERTAUFTRAG 11
#define N_CREMAMAIL_WERTAUFTRAG 2

/* Length/Count-Define of CREMAMAIL *******************************************/

#define LS_CREMAMAIL_PARTNERNO 10 + 1
#define LS_CREMAMAIL_ID 10 + 1
#define LS_CREMAMAIL_SERVER 50 + 1
#define LS_CREMAMAIL_EMAILTYPE 5 + 1
#define LS_CREMAMAIL_SMTPID 10 + 1
#define LS_CREMAMAIL_SMTPUSERGROUPID 10 + 1
#define LS_CREMAMAIL_TYPEDATAID 10 + 1
#define LS_CREMAMAIL_TYPE 5 + 1
#define LS_CREMAMAIL_THRESHOLDAMOUNT 11 + 2
#define LS_CREMAMAIL_DLPERCENTAGE 5 + 2
#define LS_CREMAMAIL_LEVELTYPE 5 + 1
#define LS_CREMAMAIL_LIMIT 13 + 2
#define LS_CREMAMAIL_REASONTYPE 5 + 1
#define LS_CREMAMAIL_TYPEID 10 + 1
#define LS_CREMAMAIL_IDFNR 10 + 1
#define LS_CREMAMAIL_SENDGVLMAIL 5 + 1
#define LS_CREMAMAIL_PORT 10 + 1
#define LS_CREMAMAIL_SENTFROMADDRESS 50 + 1
#define LS_CREMAMAIL_APPROVALPERSONSNEEDED 5 + 1
#define LS_CREMAMAIL_KDAUFTRAGNR 10 + 1
#define LS_CREMAMAIL_SENTTOADDRESS 50 + 1
#define LS_CREMAMAIL_GUID 36 + 1
#define LS_CREMAMAIL_URL 254 + 1
#define LS_CREMAMAIL_WASSEND 1 + 1
#define LS_CREMAMAIL_SENDDATE 10 + 1
#define LS_CREMAMAIL_CREMATYPEID 10 + 1
#define LS_CREMAMAIL_BRANCHNO 5 + 1
#define LS_CREMAMAIL_SENDTIME 10 + 1
#define LS_CREMAMAIL_WERTAUFTRAG 11 + 2

#define CREMAMAILPARTNERNO 0
#define CREMAMAILID 1
#define CREMAMAILSERVER 2
#define CREMAMAILEMAILTYPE 3
#define CREMAMAILSMTPID 4
#define CREMAMAILSMTPUSERGROUPID 5
#define CREMAMAILTYPEDATAID 6
#define CREMAMAILTYPE 7
#define CREMAMAILTHRESHOLDAMOUNT 8
#define CREMAMAILDLPERCENTAGE 9
#define CREMAMAILLEVELTYPE 10
#define CREMAMAILLIMIT 11
#define CREMAMAILREASONTYPE 12
#define CREMAMAILTYPEID 13
#define CREMAMAILIDFNR 14
#define CREMAMAILSENDGVLMAIL 15
#define CREMAMAILPORT 16
#define CREMAMAILSENTFROMADDRESS 17
#define CREMAMAILAPPROVALPERSONSNEEDED 18
#define CREMAMAILKDAUFTRAGNR 19
#define CREMAMAILSENTTOADDRESS 20
#define CREMAMAILGUID 21
#define CREMAMAILURL 22
#define CREMAMAILWASSEND 23
#define CREMAMAILSENDDATE 24
#define CREMAMAILCREMATYPEID 25
#define CREMAMAILBRANCHNO 26
#define CREMAMAILSENDTIME 27
#define CREMAMAILWERTAUFTRAG 28

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define CREMAMAIL_H
#define CREMAMAIL_ANZ ( sizeof(CREMAMAIL_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of CREMAMAIL *****************************************************/

#define CREMAMAIL_LISTE \
        DEBTLIMIT.PARTNERNO,\
        SMTPUSERGROUPS.ID,\
        SMTP.SERVER,\
        SMTPEMAILTYPE.EMAILTYPE,\
        SMTPUSERGROUPS.SMTPID,\
        DEBTMAILSEND.SMTPUSERGROUPID,\
        CREMAMAILREASON.TYPEDATAID,\
        CREMATYPE.TYPE,\
        AMOUNTFORMAIL.THRESHOLDAMOUNT,\
        DEBTLEVELFORMAIL.DLPERCENTAGE,\
        DEBTLEVELFORMAIL.LEVELTYPE,\
        DEBTLIMIT.LIMIT,\
        CREMAMAILREASON.REASONTYPE,\
        CREMATYPE.TYPEID,\
        KDAUFTRAG.IDFNR,\
        SMTPGVLMAIL.SENDGVLMAIL,\
        SMTP.PORT,\
        SMTPUSERGROUPS.SENTFROMADDRESS,\
        DEBTLEVELFORMAIL.APPROVALPERSONSNEEDED,\
        DEBTMAILSEND.KDAUFTRAGNR,\
        SMTPSENDTOEMAILADDRESSES.SENTTOADDRESS,\
        DEBTMAILSEND.GUID,\
        SMTPUSERGROUPS.URL,\
        DEBTMAILSEND.WASSEND,\
        DEBTMAILSEND.SENDDATE,\
        SMTPUSERGROUPS.CREMATYPEID,\
        DEBTMAILSEND.BRANCHNO,\
        DEBTMAILSEND.SENDTIME,\
        KDAUFTRAG.WERTAUFTRAG
#define CREMAMAIL_LISTE_390 \
        PARTNERNO,\
        ID,\
        SERVER,\
        EMAILTYPE,\
        SMTPID,\
        SMTPUSERGROUPID,\
        TYPEDATAID,\
        TYPE,\
        THRESHOLDAMOUNT,\
        DLPERCENTAGE,\
        LEVELTYPE,\
        LIMIT,\
        REASONTYPE,\
        TYPEID,\
        IDFNR,\
        SENDGVLMAIL,\
        PORT,\
        SENTFROMADDRESS,\
        APPROVALPERSONSNEEDED,\
        KDAUFTRAGNR,\
        SENTTOADDRESS,\
        GUID,\
        URL,\
        WASSEND,\
        SENDDATE,\
        CREMATYPEID,\
        BRANCHNO,\
        SENDTIME,\
        WERTAUFTRAG
#define CREMAMAIL_PLISTE \
        "DEBTLIMIT.PARTNERNO,"\
        "SMTPUSERGROUPS.ID,"\
        "SMTP.SERVER,"\
        "SMTPEMAILTYPE.EMAILTYPE,"\
        "SMTPUSERGROUPS.SMTPID,"\
        "DEBTMAILSEND.SMTPUSERGROUPID,"\
        "CREMAMAILREASON.TYPEDATAID,"\
        "CREMATYPE.TYPE,"\
        "AMOUNTFORMAIL.THRESHOLDAMOUNT,"\
        "DEBTLEVELFORMAIL.DLPERCENTAGE,"\
        "DEBTLEVELFORMAIL.LEVELTYPE,"\
        "DEBTLIMIT.LIMIT,"\
        "CREMAMAILREASON.REASONTYPE,"\
        "CREMATYPE.TYPEID,"\
        "KDAUFTRAG.IDFNR,"\
        "SMTPGVLMAIL.SENDGVLMAIL,"\
        "SMTP.PORT,"\
        "SMTPUSERGROUPS.SENTFROMADDRESS,"\
        "DEBTLEVELFORMAIL.APPROVALPERSONSNEEDED,"\
        "DEBTMAILSEND.KDAUFTRAGNR,"\
        "SMTPSENDTOEMAILADDRESSES.SENTTOADDRESS,"\
        "DEBTMAILSEND.GUID,"\
        "SMTPUSERGROUPS.URL,"\
        "DEBTMAILSEND.WASSEND,"\
        "DEBTMAILSEND.SENDDATE,"\
        "SMTPUSERGROUPS.CREMATYPEID,"\
        "DEBTMAILSEND.BRANCHNO,"\
        "DEBTMAILSEND.SENDTIME,"\
        "KDAUFTRAG.WERTAUFTRAG"
#define CREMAMAIL_PELISTE \
        "PARTNERNO,"\
        "ID,"\
        "SERVER,"\
        "EMAILTYPE,"\
        "SMTPID,"\
        "SMTPUSERGROUPID,"\
        "TYPEDATAID,"\
        "TYPE,"\
        "THRESHOLDAMOUNT,"\
        "DLPERCENTAGE,"\
        "LEVELTYPE,"\
        "LIMIT,"\
        "REASONTYPE,"\
        "TYPEID,"\
        "IDFNR,"\
        "SENDGVLMAIL,"\
        "PORT,"\
        "SENTFROMADDRESS,"\
        "APPROVALPERSONSNEEDED,"\
        "KDAUFTRAGNR,"\
        "SENTTOADDRESS,"\
        "GUID,"\
        "URL,"\
        "WASSEND,"\
        "SENDDATE,"\
        "CREMATYPEID,"\
        "BRANCHNO,"\
        "SENDTIME,"\
        "WERTAUFTRAG"
#define CREMAMAIL_UPDLISTE \
        "PARTNERNO=?,"\
        "ID=?,"\
        "SERVER=?,"\
        "EMAILTYPE=?,"\
        "SMTPID=?,"\
        "SMTPUSERGROUPID=?,"\
        "TYPEDATAID=?,"\
        "TYPE=?,"\
        "THRESHOLDAMOUNT=?,"\
        "DLPERCENTAGE=?,"\
        "LEVELTYPE=?,"\
        "LIMIT=?,"\
        "REASONTYPE=?,"\
        "TYPEID=?,"\
        "IDFNR=?,"\
        "SENDGVLMAIL=?,"\
        "PORT=?,"\
        "SENTFROMADDRESS=?,"\
        "APPROVALPERSONSNEEDED=?,"\
        "KDAUFTRAGNR=?,"\
        "SENTTOADDRESS=?,"\
        "GUID=?,"\
        "URL=?,"\
        "WASSEND=?,"\
        "SENDDATE=?,"\
        "CREMATYPEID=?,"\
        "BRANCHNO=?,"\
        "SENDTIME=?,"\
        "WERTAUFTRAG=?"
/* SqlMacros-Define of CREMAMAIL **********************************************/

#define CREMAMAIL_ZEIGER(x) \
        :x->PARTNERNO,\
        :x->ID,\
        :x->SERVER,\
        :x->EMAILTYPE,\
        :x->SMTPID,\
        :x->SMTPUSERGROUPID,\
        :x->TYPEDATAID,\
        :x->TYPE,\
        :x->THRESHOLDAMOUNT,\
        :x->DLPERCENTAGE,\
        :x->LEVELTYPE,\
        :x->LIMIT,\
        :x->REASONTYPE,\
        :x->TYPEID,\
        :x->IDFNR,\
        :x->SENDGVLMAIL,\
        :x->PORT,\
        :x->SENTFROMADDRESS,\
        :x->APPROVALPERSONSNEEDED,\
        :x->KDAUFTRAGNR,\
        :x->SENTTOADDRESS,\
        :x->GUID,\
        :x->URL,\
        :x->WASSEND,\
        :x->SENDDATE,\
        :x->CREMATYPEID,\
        :x->BRANCHNO,\
        :x->SENDTIME,\
        :x->WERTAUFTRAG
#define CREMAMAIL_ZEIGERSEL(x) \
        :x->PARTNERNO,\
        :x->ID,\
        :x->SERVER,\
        :x->EMAILTYPE,\
        :x->SMTPID,\
        :x->SMTPUSERGROUPID,\
        :x->TYPEDATAID,\
        :x->TYPE,\
        :x->THRESHOLDAMOUNT,\
        :x->DLPERCENTAGE,\
        :x->LEVELTYPE,\
        :x->LIMIT,\
        :x->REASONTYPE,\
        :x->TYPEID,\
        :x->IDFNR,\
        :x->SENDGVLMAIL,\
        :x->PORT,\
        :x->SENTFROMADDRESS,\
        :x->APPROVALPERSONSNEEDED,\
        :x->KDAUFTRAGNR,\
        :x->SENTTOADDRESS,\
        :x->GUID,\
        :x->URL,\
        :x->WASSEND,\
        :x->SENDDATE,\
        :x->CREMATYPEID,\
        :x->BRANCHNO,\
        :x->SENDTIME,\
        :x->WERTAUFTRAG
#define CREMAMAIL_UPDATE(x) \
        DEBTLIMIT.PARTNERNO=:x->PARTNERNO,\
        SMTP.SERVER=:x->SERVER,\
        SMTPEMAILTYPE.EMAILTYPE=:x->EMAILTYPE,\
        SMTPUSERGROUPS.SMTPID=:x->SMTPID,\
        DEBTMAILSEND.SMTPUSERGROUPID=:x->SMTPUSERGROUPID,\
        CREMAMAILREASON.TYPEDATAID=:x->TYPEDATAID,\
        CREMATYPE.TYPE=:x->TYPE,\
        AMOUNTFORMAIL.THRESHOLDAMOUNT=:x->THRESHOLDAMOUNT,\
        DEBTLEVELFORMAIL.DLPERCENTAGE=:x->DLPERCENTAGE,\
        DEBTLEVELFORMAIL.LEVELTYPE=:x->LEVELTYPE,\
        DEBTLIMIT.LIMIT=:x->LIMIT,\
        CREMAMAILREASON.REASONTYPE=:x->REASONTYPE,\
        CREMATYPE.TYPEID=:x->TYPEID,\
        KDAUFTRAG.IDFNR=:x->IDFNR,\
        SMTPGVLMAIL.SENDGVLMAIL=:x->SENDGVLMAIL,\
        SMTP.PORT=:x->PORT,\
        SMTPUSERGROUPS.SENTFROMADDRESS=:x->SENTFROMADDRESS,\
        DEBTLEVELFORMAIL.APPROVALPERSONSNEEDED=:x->APPROVALPERSONSNEEDED,\
        DEBTMAILSEND.KDAUFTRAGNR=:x->KDAUFTRAGNR,\
        SMTPSENDTOEMAILADDRESSES.SENTTOADDRESS=:x->SENTTOADDRESS,\
        DEBTMAILSEND.GUID=:x->GUID,\
        SMTPUSERGROUPS.URL=:x->URL,\
        DEBTMAILSEND.WASSEND=:x->WASSEND,\
        DEBTMAILSEND.SENDDATE=:x->SENDDATE,\
        SMTPUSERGROUPS.CREMATYPEID=:x->CREMATYPEID,\
        DEBTMAILSEND.BRANCHNO=:x->BRANCHNO,\
        DEBTMAILSEND.SENDTIME=:x->SENDTIME,\
        KDAUFTRAG.WERTAUFTRAG=:x->WERTAUFTRAG
/* SqlMacros390-Define of CREMAMAIL *******************************************/

#define CREMAMAIL_ZEIGER_390 \
        :PARTNERNO,\
        :ID,\
        :SERVER,\
        :EMAILTYPE,\
        :SMTPID,\
        :SMTPUSERGROUPID,\
        :TYPEDATAID,\
        :TYPE,\
        :THRESHOLDAMOUNT,\
        :DLPERCENTAGE,\
        :LEVELTYPE,\
        :LIMIT,\
        :REASONTYPE,\
        :TYPEID,\
        :IDFNR,\
        :SENDGVLMAIL,\
        :PORT,\
        :SENTFROMADDRESS,\
        :APPROVALPERSONSNEEDED,\
        :KDAUFTRAGNR,\
        :SENTTOADDRESS,\
        :GUID,\
        :URL,\
        :WASSEND,\
        :SENDDATE,\
        :CREMATYPEID,\
        :BRANCHNO,\
        :SENDTIME,\
        :WERTAUFTRAG
#define CREMAMAIL_UPDATE_390 \
        PARTNERNO=:PARTNERNO,\
        ID=:ID,\
        SERVER=:SERVER,\
        EMAILTYPE=:EMAILTYPE,\
        SMTPID=:SMTPID,\
        SMTPUSERGROUPID=:SMTPUSERGROUPID,\
        TYPEDATAID=:TYPEDATAID,\
        TYPE=:TYPE,\
        THRESHOLDAMOUNT=:THRESHOLDAMOUNT,\
        DLPERCENTAGE=:DLPERCENTAGE,\
        LEVELTYPE=:LEVELTYPE,\
        LIMIT=:LIMIT,\
        REASONTYPE=:REASONTYPE,\
        TYPEID=:TYPEID,\
        IDFNR=:IDFNR,\
        SENDGVLMAIL=:SENDGVLMAIL,\
        PORT=:PORT,\
        SENTFROMADDRESS=:SENTFROMADDRESS,\
        APPROVALPERSONSNEEDED=:APPROVALPERSONSNEEDED,\
        KDAUFTRAGNR=:KDAUFTRAGNR,\
        SENTTOADDRESS=:SENTTOADDRESS,\
        GUID=:GUID,\
        URL=:URL,\
        WASSEND=:WASSEND,\
        SENDDATE=:SENDDATE,\
        CREMATYPEID=:CREMATYPEID,\
        BRANCHNO=:BRANCHNO,\
        SENDTIME=:SENDTIME,\
        WERTAUFTRAG=:WERTAUFTRAG
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of CREMAMAIL ***********************************************/

#ifndef TRANSCLASS
typedef struct N_CREMAMAIL {
    long PARTNERNO;
    long ID;
    char SERVER[51];
    short EMAILTYPE;
    long SMTPID;
    long SMTPUSERGROUPID;
    long TYPEDATAID;
    short TYPE;
    double THRESHOLDAMOUNT;
    double DLPERCENTAGE;
    short LEVELTYPE;
    double LIMIT;
    short REASONTYPE;
    long TYPEID;
    long IDFNR;
    short SENDGVLMAIL;
    long PORT;
    char SENTFROMADDRESS[51];
    short APPROVALPERSONSNEEDED;
    long KDAUFTRAGNR;
    char SENTTOADDRESS[51];
    char GUID[37];
    char URL[255];
    char WASSEND[2];
    long SENDDATE;
    long CREMATYPEID;
    short BRANCHNO;
    long SENDTIME;
    double WERTAUFTRAG;
} cremamailS;
#else /* TRANSCLASS */
typedef struct N_CREMAMAIL {
    long PARTNERNO;
    long ID;
    char SERVER[51];
    short EMAILTYPE;
    long SMTPID;
    long SMTPUSERGROUPID;
    long TYPEDATAID;
    short TYPE;
    double THRESHOLDAMOUNT;
    double DLPERCENTAGE;
    short LEVELTYPE;
    double LIMIT;
    short REASONTYPE;
    long TYPEID;
    long IDFNR;
    short SENDGVLMAIL;
    long PORT;
    char SENTFROMADDRESS[51];
    short APPROVALPERSONSNEEDED;
    long KDAUFTRAGNR;
    char SENTTOADDRESS[51];
    char GUID[37];
    char URL[255];
    char WASSEND[2];
    long SENDDATE;
    long CREMATYPEID;
    short BRANCHNO;
    long SENDTIME;
    double WERTAUFTRAG;

    bool operator == (const N_CREMAMAIL& right) const {
        return (
            PARTNERNO == right.PARTNERNO &&
            ID == right.ID &&
            !strcmp(SERVER, right.SERVER) &&
            EMAILTYPE == right.EMAILTYPE &&
            SMTPID == right.SMTPID &&
            SMTPUSERGROUPID == right.SMTPUSERGROUPID &&
            TYPEDATAID == right.TYPEDATAID &&
            TYPE == right.TYPE &&
            THRESHOLDAMOUNT == right.THRESHOLDAMOUNT &&
            DLPERCENTAGE == right.DLPERCENTAGE &&
            LEVELTYPE == right.LEVELTYPE &&
            LIMIT == right.LIMIT &&
            REASONTYPE == right.REASONTYPE &&
            TYPEID == right.TYPEID &&
            IDFNR == right.IDFNR &&
            SENDGVLMAIL == right.SENDGVLMAIL &&
            PORT == right.PORT &&
            !strcmp(SENTFROMADDRESS, right.SENTFROMADDRESS) &&
            APPROVALPERSONSNEEDED == right.APPROVALPERSONSNEEDED &&
            KDAUFTRAGNR == right.KDAUFTRAGNR &&
            !strcmp(SENTTOADDRESS, right.SENTTOADDRESS) &&
            !strcmp(GUID, right.GUID) &&
            !strcmp(URL, right.URL) &&
            !strcmp(WASSEND, right.WASSEND) &&
            SENDDATE == right.SENDDATE &&
            CREMATYPEID == right.CREMATYPEID &&
            BRANCHNO == right.BRANCHNO &&
            SENDTIME == right.SENDTIME &&
            WERTAUFTRAG == right.WERTAUFTRAG
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        PARTNERNO = 0;
        ID = 0;
        strcpy(SERVER, " " );
        EMAILTYPE = 0;
        SMTPID = 0;
        SMTPUSERGROUPID = 0;
        TYPEDATAID = 0;
        TYPE = 0;
        THRESHOLDAMOUNT = 0;
        DLPERCENTAGE = 0;
        LEVELTYPE = 0;
        LIMIT = 0;
        REASONTYPE = 0;
        TYPEID = 0;
        IDFNR = 0;
        SENDGVLMAIL = 0;
        PORT = 0;
        strcpy(SENTFROMADDRESS, " " );
        APPROVALPERSONSNEEDED = 0;
        KDAUFTRAGNR = 0;
        strcpy(SENTTOADDRESS, " " );
        strcpy(GUID, " " );
        strcpy(URL, " " );
        strcpy(WASSEND, " " );
        SENDDATE = 0;
        CREMATYPEID = 0;
        BRANCHNO = 0;
        SENDTIME = 0;
        WERTAUFTRAG = 0;
#endif
    }
} cremamailS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of CREMAMAIL *****************************************/

struct S_CREMAMAIL {
    char PARTNERNO[11];
    char ID[11];
    char SERVER[50 + 1];
    char EMAILTYPE[7];
    char SMTPID[11];
    char SMTPUSERGROUPID[11];
    char TYPEDATAID[11];
    char TYPE[7];
    char THRESHOLDAMOUNT[11 + 2];
    char DLPERCENTAGE[5 + 2];
    char LEVELTYPE[7];
    char LIMIT[13 + 2];
    char REASONTYPE[7];
    char TYPEID[11];
    char IDFNR[11];
    char SENDGVLMAIL[7];
    char PORT[11];
    char SENTFROMADDRESS[50 + 1];
    char APPROVALPERSONSNEEDED[7];
    char KDAUFTRAGNR[11];
    char SENTTOADDRESS[50 + 1];
    char GUID[36 + 1];
    char URL[254 + 1];
    char WASSEND[1 + 1];
    char SENDDATE[11];
    char CREMATYPEID[11];
    char BRANCHNO[7];
    char SENDTIME[11];
    char WERTAUFTRAG[11 + 2];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of CREMAMAIL ************************/

struct O_CREMAMAIL {
    char PARTNERNO[11];
    char ID[11];
    char SERVER[50];
    char EMAILTYPE[7];
    char SMTPID[11];
    char SMTPUSERGROUPID[11];
    char TYPEDATAID[11];
    char TYPE[7];
    char THRESHOLDAMOUNT[11];
    char DLPERCENTAGE[5];
    char LEVELTYPE[7];
    char LIMIT[13];
    char REASONTYPE[7];
    char TYPEID[11];
    char IDFNR[11];
    char SENDGVLMAIL[7];
    char PORT[11];
    char SENTFROMADDRESS[50];
    char APPROVALPERSONSNEEDED[7];
    char KDAUFTRAGNR[11];
    char SENTTOADDRESS[50];
    char GUID[36];
    char URL[254];
    char WASSEND[1];
    char SENDDATE[11];
    char CREMATYPEID[11];
    char BRANCHNO[7];
    char SENDTIME[11];
    char WERTAUFTRAG[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of CREMAMAIL ***********************************/

struct C_CREMAMAIL {
    long PARTNERNO;
    long ID;
    char SERVER[51];
    short EMAILTYPE;
    long SMTPID;
    long SMTPUSERGROUPID;
    long TYPEDATAID;
    short TYPE;
    double THRESHOLDAMOUNT;
    double DLPERCENTAGE;
    short LEVELTYPE;
    double LIMIT;
    short REASONTYPE;
    long TYPEID;
    long IDFNR;
    short SENDGVLMAIL;
    long PORT;
    char SENTFROMADDRESS[51];
    short APPROVALPERSONSNEEDED;
    long KDAUFTRAGNR;
    char SENTTOADDRESS[51];
    char GUID[37];
    char URL[255];
    char WASSEND;
    long SENDDATE;
    long CREMATYPEID;
    short BRANCHNO;
    long SENDTIME;
    double WERTAUFTRAG;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of CREMAMAIL *********************************/

struct I_CREMAMAIL {
    short PARTNERNO;
    short ID;
    short SERVER;
    short EMAILTYPE;
    short SMTPID;
    short SMTPUSERGROUPID;
    short TYPEDATAID;
    short TYPE;
    short THRESHOLDAMOUNT;
    short DLPERCENTAGE;
    short LEVELTYPE;
    short LIMIT;
    short REASONTYPE;
    short TYPEID;
    short IDFNR;
    short SENDGVLMAIL;
    short PORT;
    short SENTFROMADDRESS;
    short APPROVALPERSONSNEEDED;
    short KDAUFTRAGNR;
    short SENTTOADDRESS;
    short GUID;
    short URL;
    short WASSEND;
    short SENDDATE;
    short CREMATYPEID;
    short BRANCHNO;
    short SENDTIME;
    short WERTAUFTRAG;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CREMAMAIL *******************************************/

#if defined (BUF_DESC)
static struct buf_desc CREMAMAIL_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L ,  11, 0 },
   { TYP_C, 50, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 11, 2 },
   { TYP_D, 5, 2 },
   { TYP_S ,  6, 0 },
   { TYP_D, 13, 2 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 50, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 50, 0 },
   { TYP_C, 36, 0 },
   { TYP_C, 254, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 11, 2 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CREMAMAIL_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L ,  11, 0 },
   { TYP_C, 50, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 11, 2 },
   { TYP_D, 5, 2 },
   { TYP_S ,  6, 0 },
   { TYP_D, 13, 2 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 50, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 50, 0 },
   { TYP_C, 36, 0 },
   { TYP_C, 254, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 11, 2 },
};
#endif

/* description for datatypes of CREMAMAIL *************************************/

 #define CREMAMAIL_S390 \
         long PARTNERNO; \
         long ID; \
         char SERVER[51]; \
         short EMAILTYPE; \
         long SMTPID; \
         long SMTPUSERGROUPID; \
         long TYPEDATAID; \
         short TYPE; \
         double THRESHOLDAMOUNT; \
         double DLPERCENTAGE; \
         short LEVELTYPE; \
         double LIMIT; \
         short REASONTYPE; \
         long TYPEID; \
         long IDFNR; \
         short SENDGVLMAIL; \
         long PORT; \
         char SENTFROMADDRESS[51]; \
         short APPROVALPERSONSNEEDED; \
         long KDAUFTRAGNR; \
         char SENTTOADDRESS[51]; \
         char GUID[37]; \
         char URL[255]; \
         char WASSEND; \
         long SENDDATE; \
         long CREMATYPEID; \
         short BRANCHNO; \
         long SENDTIME; \
         double WERTAUFTRAG; \



/* Copy-Function Struct to single Data CREMAMAIL ******************************/

 #define CREMAMAIL_S390_COPY_TO_SINGLE(_x_) \
         PARTNERNO=_x_->PARTNERNO;\
         ID=_x_->ID;\
          strcpy(SERVER,_x_->SERVER);\
         EMAILTYPE=_x_->EMAILTYPE;\
         SMTPID=_x_->SMTPID;\
         SMTPUSERGROUPID=_x_->SMTPUSERGROUPID;\
         TYPEDATAID=_x_->TYPEDATAID;\
         TYPE=_x_->TYPE;\
         THRESHOLDAMOUNT=_x_->THRESHOLDAMOUNT;\
         DLPERCENTAGE=_x_->DLPERCENTAGE;\
         LEVELTYPE=_x_->LEVELTYPE;\
         LIMIT=_x_->LIMIT;\
         REASONTYPE=_x_->REASONTYPE;\
         TYPEID=_x_->TYPEID;\
         IDFNR=_x_->IDFNR;\
         SENDGVLMAIL=_x_->SENDGVLMAIL;\
         PORT=_x_->PORT;\
          strcpy(SENTFROMADDRESS,_x_->SENTFROMADDRESS);\
         APPROVALPERSONSNEEDED=_x_->APPROVALPERSONSNEEDED;\
         KDAUFTRAGNR=_x_->KDAUFTRAGNR;\
          strcpy(SENTTOADDRESS,_x_->SENTTOADDRESS);\
          strcpy(GUID,_x_->GUID);\
          strcpy(URL,_x_->URL);\
         WASSEND=_x_->WASSEND;\
         SENDDATE=_x_->SENDDATE;\
         CREMATYPEID=_x_->CREMATYPEID;\
         BRANCHNO=_x_->BRANCHNO;\
         SENDTIME=_x_->SENDTIME;\
         WERTAUFTRAG=_x_->WERTAUFTRAG;\

 #define CREMAMAIL_S390_COPY_TO_STRUCT(_x_) \
          _x_->PARTNERNO=PARTNERNO;\
          _x_->ID=ID;\
          strcpy(_x_->SERVER,SERVER);\
          _x_->EMAILTYPE=EMAILTYPE;\
          _x_->SMTPID=SMTPID;\
          _x_->SMTPUSERGROUPID=SMTPUSERGROUPID;\
          _x_->TYPEDATAID=TYPEDATAID;\
          _x_->TYPE=TYPE;\
          _x_->THRESHOLDAMOUNT=THRESHOLDAMOUNT;\
          _x_->DLPERCENTAGE=DLPERCENTAGE;\
          _x_->LEVELTYPE=LEVELTYPE;\
          _x_->LIMIT=LIMIT;\
          _x_->REASONTYPE=REASONTYPE;\
          _x_->TYPEID=TYPEID;\
          _x_->IDFNR=IDFNR;\
          _x_->SENDGVLMAIL=SENDGVLMAIL;\
          _x_->PORT=PORT;\
          strcpy(_x_->SENTFROMADDRESS,SENTFROMADDRESS);\
          _x_->APPROVALPERSONSNEEDED=APPROVALPERSONSNEEDED;\
          _x_->KDAUFTRAGNR=KDAUFTRAGNR;\
          strcpy(_x_->SENTTOADDRESS,SENTTOADDRESS);\
          strcpy(_x_->GUID,GUID);\
          strcpy(_x_->URL,URL);\
          _x_->WASSEND=WASSEND;\
          _x_->SENDDATE=SENDDATE;\
          _x_->CREMATYPEID=CREMATYPEID;\
          _x_->BRANCHNO=BRANCHNO;\
          _x_->SENDTIME=SENDTIME;\
          _x_->WERTAUFTRAG=WERTAUFTRAG;\



/* FunctionNumber-Define of CremaMail *****************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of CremaMail *************************************/


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

class CCREMAMAIL : public ppDadeVirtual {
public:
    cremamailS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<cremamailS> lst; // class list

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
                     vector< cremamailS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     cremamailS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< cremamailS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<cremamailS>::iterator
                 beginList() { return lst.begin(); }
    vector<cremamailS>::iterator
                 endList  () { return lst.end  (); }

    long         GetPartnerno() const { return s.PARTNERNO; }
    long         GetId() const { return s.ID; }
    const char*  GetServer(ppString & t) const { t = s.SERVER; t.erasespace(ppString::END); return t.c_str(); }
    short        GetEmailtype() const { return s.EMAILTYPE; }
    long         GetSmtpid() const { return s.SMTPID; }
    long         GetSmtpusergroupid() const { return s.SMTPUSERGROUPID; }
    long         GetTypedataid() const { return s.TYPEDATAID; }
    short        GetType() const { return s.TYPE; }
    double       GetThresholdamount() const { return s.THRESHOLDAMOUNT; }
    double       GetDlpercentage() const { return s.DLPERCENTAGE; }
    short        GetLeveltype() const { return s.LEVELTYPE; }
    double       GetLimit() const { return s.LIMIT; }
    short        GetReasontype() const { return s.REASONTYPE; }
    long         GetTypeid() const { return s.TYPEID; }
    long         GetIdfnr() const { return s.IDFNR; }
    short        GetSendgvlmail() const { return s.SENDGVLMAIL; }
    long         GetPort() const { return s.PORT; }
    const char*  GetSentfromaddress(ppString & t) const { t = s.SENTFROMADDRESS; t.erasespace(ppString::END); return t.c_str(); }
    short        GetApprovalpersonsneeded() const { return s.APPROVALPERSONSNEEDED; }
    long         GetKdauftragnr() const { return s.KDAUFTRAGNR; }
    const char*  GetSenttoaddress(ppString & t) const { t = s.SENTTOADDRESS; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetGuid(ppString & t) const { t = s.GUID; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetUrl(ppString & t) const { t = s.URL; t.erasespace(ppString::END); return t.c_str(); }
    char         GetWassend() const { return s.WASSEND[0]; }
    long         GetSenddate() const { return s.SENDDATE; }
    long         GetCrematypeid() const { return s.CREMATYPEID; }
    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetSendtime() const { return s.SENDTIME; }
    double       GetWertauftrag() const { return s.WERTAUFTRAG; }

    const cremamailS &
                 GetStruct() const { return s; }
    void         SetPartnerno(long t) { s.PARTNERNO = t; }
    void         SetId(long t) { s.ID = t; }
    void         SetServer(const ppString & t) { ppGStrCopy(s.SERVER, t.c_str(), L_CREMAMAIL_SERVER); }
    void         SetEmailtype(short t) { s.EMAILTYPE = t; }
    void         SetSmtpid(long t) { s.SMTPID = t; }
    void         SetSmtpusergroupid(long t) { s.SMTPUSERGROUPID = t; }
    void         SetTypedataid(long t) { s.TYPEDATAID = t; }
    void         SetType(short t) { s.TYPE = t; }
    void         SetThresholdamount(double t) { s.THRESHOLDAMOUNT = t; }
    void         SetDlpercentage(double t) { s.DLPERCENTAGE = t; }
    void         SetLeveltype(short t) { s.LEVELTYPE = t; }
    void         SetLimit(double t) { s.LIMIT = t; }
    void         SetReasontype(short t) { s.REASONTYPE = t; }
    void         SetTypeid(long t) { s.TYPEID = t; }
    void         SetIdfnr(long t) { s.IDFNR = t; }
    void         SetSendgvlmail(short t) { s.SENDGVLMAIL = t; }
    void         SetPort(long t) { s.PORT = t; }
    void         SetSentfromaddress(const ppString & t) { ppGStrCopy(s.SENTFROMADDRESS, t.c_str(), L_CREMAMAIL_SENTFROMADDRESS); }
    void         SetApprovalpersonsneeded(short t) { s.APPROVALPERSONSNEEDED = t; }
    void         SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
    void         SetSenttoaddress(const ppString & t) { ppGStrCopy(s.SENTTOADDRESS, t.c_str(), L_CREMAMAIL_SENTTOADDRESS); }
    void         SetGuid(const ppString & t) { ppGStrCopy(s.GUID, t.c_str(), L_CREMAMAIL_GUID); }
    void         SetUrl(const ppString & t) { ppGStrCopy(s.URL, t.c_str(), L_CREMAMAIL_URL); }
    void         SetWassend(char t) { s.WASSEND[0] = t; s.WASSEND[1] = '\0';}
    void         SetSenddate(long t) { s.SENDDATE = t; }
    void         SetCrematypeid(long t) { s.CREMATYPEID = t; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetSendtime(long t) { s.SENDTIME = t; }
    void         SetWertauftrag(double t) { s.WERTAUFTRAG = t; }

    void         SetStruct(const cremamailS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCREMAMAIL() {
        ::buf_default((void *)&s, CREMAMAIL_BES, CREMAMAIL_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCREMAMAIL() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CREMAMAIL_BES, CREMAMAIL_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, CREMAMAIL_BES, (int)CREMAMAIL_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, CREMAMAIL_BES, (int)CREMAMAIL_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_CREMAMAIL & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.SERVER);
        ppGStripLast(d.SENTFROMADDRESS);
        ppGStripLast(d.SENTTOADDRESS);
        ppGStripLast(d.GUID);
        ppGStripLast(d.URL);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CREMAMAIL_BES, (int)CREMAMAIL_ANZ, error_msg);
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
/* CreateSqlStatement of CREMAMAIL ********************************************/

 #define CREMAMAIL_CREATE(x) EXEC SQL create table x (\
         PARTNERNO integer default 0 not null,\
         ID serial not null,\
         SERVER varchar(50,0) default " " not null,\
         EMAILTYPE smallint default 0 not null,\
         SMTPID integer default 0 not null,\
         SMTPUSERGROUPID integer default 0 not null,\
         TYPEDATAID integer default 0 not null,\
         TYPE smallint default 0 not null,\
         THRESHOLDAMOUNT decimal(11,2) default 0 not null,\
         DLPERCENTAGE decimal(5,2) default 0 not null,\
         LEVELTYPE smallint default 0 not null,\
         LIMIT decimal(13,2) default 0 not null,\
         REASONTYPE smallint default 0 not null,\
         TYPEID integer default 0 not null,\
         IDFNR integer default 0 not null,\
         SENDGVLMAIL smallint default 0 not null,\
         PORT integer default 0 not null,\
         SENTFROMADDRESS varchar(50,0) default " " not null,\
         APPROVALPERSONSNEEDED smallint default 0 not null,\
         KDAUFTRAGNR integer default 0 not null,\
         SENTTOADDRESS varchar(50,0) default " " not null,\
         GUID varchar(36,0) default " " not null,\
         URL varchar(254,0) default " " not null,\
         WASSEND char(1) default " " not null,\
         SENDDATE integer default 0 not null,\
         CREMATYPEID integer default 0 not null,\
         BRANCHNO smallint default 0 not null,\
         SENDTIME integer default 0 not null,\
         WERTAUFTRAG decimal(11,2) default 0 not null) extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of CREMAMAIL ******************************************/

 #define CREMAMAIL_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_debtlimit_1 on _X_(\
              partnerno,\
              LimitType );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of CREMAMAIL ******************************************/

 #define CREMAMAIL_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_debtlimit_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
