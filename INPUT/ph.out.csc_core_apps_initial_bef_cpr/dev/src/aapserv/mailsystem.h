#ifndef __PP_MAILSYSTEM_H_
#define __PP_MAILSYSTEM_H_

/******************************************************************************/
/* c:\git\pharmos.outbound.csc_core_applications\dev\src\aapserv\mailsystem ***/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of MAILDEFINEDUSER *******************************************/

#define L_MAILDEFINEDUSER_FILIALNR 6
#define L_MAILDEFINEDUSER_USERNAME 8
#define L_MAILDEFINEDUSER_UID 11
#define L_MAILDEFINEDUSER_GROUPNO 11

/* Length-Define of USERINFORMATION *******************************************/

#define L_USERINFORMATION_DATE 11
#define L_USERINFORMATION_VALIDTIMEFROM 11
#define L_USERINFORMATION_VALIDTIMETO 11
#define L_USERINFORMATION_INFOMESSAGE 254
#define L_USERINFORMATION_VALIDBRANCHNO 6
#define L_USERINFORMATION_USERBRANCHNO 6
#define L_USERINFORMATION_UID_ANLAGE 11
#define L_USERINFORMATION_PRIORITY 6

/* Length-Define of MAILGROUP *************************************************/

#define L_MAILGROUP_GROUPNO 11
#define L_MAILGROUP_GROUPNAME 30

/* Length-Define of MAILITEMS *************************************************/

#define L_MAILITEMS_FILIALNR 6
#define L_MAILITEMS_UID 11
#define L_MAILITEMS_NEWSNO 11

/* Length-Define of MAILMESSAGE ***********************************************/

#define L_MAILMESSAGE_NEWSNO 11
#define L_MAILMESSAGE_MESSAGE 254
#define L_MAILMESSAGE_TM_DATE 11
#define L_MAILMESSAGE_TM_TIME 11
#define L_MAILMESSAGE_UID 11
#define L_MAILMESSAGE_FILIALNR 6
#define L_MAILMESSAGE_PRIORITY 6

/* Length-Define of MAILUSERS *************************************************/

#define L_MAILUSERS_GROUPNO 11
#define L_MAILUSERS_UID 11
#define L_MAILUSERS_FILIALNR 6

/* SqlDefine of MAILDEFINEDUSER ***********************************************/


#define MAILDEFINEDUSER_PLISTE \
        "PASSWD.FILIALNR,"\
        "PASSWD.USERNAME,"\
        "PASSWD.UID,"\
        "MAILUSERS.GROUPNO"

/* SqlDefine of USERINFORMATION ***********************************************/


#define USERINFORMATION_PLISTE \
        "USERINFORMATION.DATE,"\
        "USERINFORMATION.VALIDTIMEFROM,"\
        "USERINFORMATION.VALIDTIMETO,"\
        "USERINFORMATION.INFOMESSAGE,"\
        "USERINFORMATION.VALIDBRANCHNO,"\
        "USERINFORMATION.USERBRANCHNO,"\
        "USERINFORMATION.UID_ANLAGE,"\
        "USERINFORMATION.PRIORITY"

/* SqlDefine of MAILGROUP *****************************************************/


#define MAILGROUP_PLISTE \
        "MAILGROUP.GROUPNO,"\
        "MAILGROUP.GROUPNAME"

/* SqlDefine of MAILITEMS *****************************************************/


#define MAILITEMS_PLISTE \
        "MAILITEMS.FILIALNR,"\
        "MAILITEMS.UID,"\
        "MAILITEMS.NEWSNO"

/* SqlDefine of MAILMESSAGE ***************************************************/


#define MAILMESSAGE_PLISTE \
        "MAILMESSAGE.NEWSNO,"\
        "MAILMESSAGE.MESSAGE,"\
        "MAILMESSAGE.TM_DATE,"\
        "MAILMESSAGE.TM_TIME,"\
        "MAILMESSAGE.UID,"\
        "MAILMESSAGE.FILIALNR,"\
        "MAILMESSAGE.PRIORITY"

/* SqlDefine of MAILUSERS *****************************************************/


#define MAILUSERS_PLISTE \
        "MAILUSERS.GROUPNO,"\
        "MAILUSERS.UID,"\
        "MAILUSERS.FILIALNR"

/* SqlDefine of MAILDEFINEDUSER ***********************************************/


#define MAILDEFINEDUSER_UPDLISTE \
        "FILIALNR=?,"\
        "USERNAME=?,"\
        "UID=?,"\
        "GROUPNO=?"
/* SqlDefine of USERINFORMATION ***********************************************/


#define USERINFORMATION_UPDLISTE \
        "DATE=?,"\
        "VALIDTIMEFROM=?,"\
        "VALIDTIMETO=?,"\
        "INFOMESSAGE=?,"\
        "VALIDBRANCHNO=?,"\
        "USERBRANCHNO=?,"\
        "UID_ANLAGE=?,"\
        "PRIORITY=?"
/* SqlDefine of MAILGROUP *****************************************************/


#define MAILGROUP_UPDLISTE \
        "GROUPNO=?,"\
        "GROUPNAME=?"
/* SqlDefine of MAILITEMS *****************************************************/


#define MAILITEMS_UPDLISTE \
        "FILIALNR=?,"\
        "UID=?,"\
        "NEWSNO=?"
/* SqlDefine of MAILMESSAGE ***************************************************/


#define MAILMESSAGE_UPDLISTE \
        "NEWSNO=?,"\
        "MESSAGE=?,"\
        "TM_DATE=?,"\
        "TM_TIME=?,"\
        "UID=?,"\
        "FILIALNR=?,"\
        "PRIORITY=?"
/* SqlDefine of MAILUSERS *****************************************************/


#define MAILUSERS_UPDLISTE \
        "GROUPNO=?,"\
        "UID=?,"\
        "FILIALNR=?"
/* SqlMacros-Define of MAILDEFINEDUSER ****************************************/

#define MAILDEFINEDUSER_ZEIGER(x) \
        :x->FILIALNR,\
        :x->USERNAME,\
        :x->UID,\
        :x->GROUPNO
#define MAILDEFINEDUSER_ZEIGERSEL(x) \
        :x->FILIALNR,\
        :x->USERNAME,\
        :x->UID,\
        :x->GROUPNO

/* SqlMacros-Define of USERINFORMATION ****************************************/

#define USERINFORMATION_ZEIGER(x) \
        :x->DATE,\
        :x->VALIDTIMEFROM,\
        :x->VALIDTIMETO,\
        :x->INFOMESSAGE,\
        :x->VALIDBRANCHNO,\
        :x->USERBRANCHNO,\
        :x->UID_ANLAGE,\
        :x->PRIORITY
#define USERINFORMATION_ZEIGERSEL(x) \
        :x->DATE,\
        :x->VALIDTIMEFROM,\
        :x->VALIDTIMETO,\
        :x->INFOMESSAGE,\
        :x->VALIDBRANCHNO,\
        :x->USERBRANCHNO,\
        :x->UID_ANLAGE,\
        :x->PRIORITY

/* SqlMacros-Define of MAILGROUP **********************************************/

#define MAILGROUP_ZEIGER(x) \
        :x->GROUPNO,\
        :x->GROUPNAME
#define MAILGROUP_ZEIGERSEL(x) \
        :x->GROUPNO,\
        :x->GROUPNAME

/* SqlMacros-Define of MAILITEMS **********************************************/

#define MAILITEMS_ZEIGER(x) \
        :x->FILIALNR,\
        :x->UID,\
        :x->NEWSNO
#define MAILITEMS_ZEIGERSEL(x) \
        :x->FILIALNR,\
        :x->UID,\
        :x->NEWSNO

/* SqlMacros-Define of MAILMESSAGE ********************************************/

#define MAILMESSAGE_ZEIGER(x) \
        :x->NEWSNO,\
        :x->MESSAGE,\
        :x->TM_DATE,\
        :x->TM_TIME,\
        :x->UID,\
        :x->FILIALNR,\
        :x->PRIORITY
#define MAILMESSAGE_ZEIGERSEL(x) \
        :x->NEWSNO,\
        :x->MESSAGE,\
        :x->TM_DATE,\
        :x->TM_TIME,\
        :x->UID,\
        :x->FILIALNR,\
        :x->PRIORITY

/* SqlMacros-Define of MAILUSERS **********************************************/

#define MAILUSERS_ZEIGER(x) \
        :x->GROUPNO,\
        :x->UID,\
        :x->FILIALNR
#define MAILUSERS_ZEIGERSEL(x) \
        :x->GROUPNO,\
        :x->UID,\
        :x->FILIALNR

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define MAILDEFINEDUSER_H
#define MAILDEFINEDUSER_ANZ ( sizeof(MAILDEFINEDUSER_BES) / sizeof(struct buf_desc) )
#define USERINFORMATION_H
#define USERINFORMATION_ANZ ( sizeof(USERINFORMATION_BES) / sizeof(struct buf_desc) )
#define MAILGROUP_H
#define MAILGROUP_ANZ ( sizeof(MAILGROUP_BES) / sizeof(struct buf_desc) )
#define MAILITEMS_H
#define MAILITEMS_ANZ ( sizeof(MAILITEMS_BES) / sizeof(struct buf_desc) )
#define MAILMESSAGE_H
#define MAILMESSAGE_ANZ ( sizeof(MAILMESSAGE_BES) / sizeof(struct buf_desc) )
#define MAILUSERS_H
#define MAILUSERS_ANZ ( sizeof(MAILUSERS_BES) / sizeof(struct buf_desc) )
#endif

#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of MAILDEFINEDUSER *****************************************/

#ifndef TRANSCLASS
typedef struct N_MAILDEFINEDUSER {
    short FILIALNR;
    char USERNAME[9];
    long UID;
    long GROUPNO;
    long FETCH_REL;
} maildefineduserS;
#else /* TRANSCLASS */
typedef struct N_MAILDEFINEDUSER {
    short FILIALNR;
    char USERNAME[9];
    long UID;
    long GROUPNO;
    long FETCH_REL;
    bool operator == (const N_MAILDEFINEDUSER& right) const {
        return (
            FILIALNR == right.FILIALNR &&
            !strcmp(USERNAME, right.USERNAME) &&
            UID == right.UID &&
            GROUPNO == right.GROUPNO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        FILIALNR = 0;
        strcpy(USERNAME, " " );
        UID = 0;
        GROUPNO = 0;
#endif
    }
} maildefineduserS;
#endif /* TRANSCLASS */

/* original struct of USERINFORMATION *****************************************/

#ifndef TRANSCLASS
typedef struct N_USERINFORMATION {
    long DATE;
    long VALIDTIMEFROM;
    long VALIDTIMETO;
    char INFOMESSAGE[255];
    short VALIDBRANCHNO;
    short USERBRANCHNO;
    long UID_ANLAGE;
    short PRIORITY;
    long FETCH_REL;
} userinformationS;
#else /* TRANSCLASS */
typedef struct N_USERINFORMATION {
    long DATE;
    long VALIDTIMEFROM;
    long VALIDTIMETO;
    char INFOMESSAGE[255];
    short VALIDBRANCHNO;
    short USERBRANCHNO;
    long UID_ANLAGE;
    short PRIORITY;
    long FETCH_REL;
    bool operator == (const N_USERINFORMATION& right) const {
        return (
            DATE == right.DATE &&
            VALIDTIMEFROM == right.VALIDTIMEFROM &&
            VALIDTIMETO == right.VALIDTIMETO &&
            !strcmp(INFOMESSAGE, right.INFOMESSAGE) &&
            VALIDBRANCHNO == right.VALIDBRANCHNO &&
            USERBRANCHNO == right.USERBRANCHNO &&
            UID_ANLAGE == right.UID_ANLAGE &&
            PRIORITY == right.PRIORITY
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        DATE = 0;
        VALIDTIMEFROM = 0;
        VALIDTIMETO = 0;
        strcpy(INFOMESSAGE, " " );
        VALIDBRANCHNO = 0;
        USERBRANCHNO = 0;
        UID_ANLAGE = 0;
        PRIORITY = 0;
#endif
    }
} userinformationS;
#endif /* TRANSCLASS */

/* original struct of MAILGROUP ***********************************************/

#ifndef TRANSCLASS
typedef struct N_MAILGROUP {
    long GROUPNO;
    char GROUPNAME[31];
    long FETCH_REL;
} mailgroupS;
#else /* TRANSCLASS */
typedef struct N_MAILGROUP {
    long GROUPNO;
    char GROUPNAME[31];
    long FETCH_REL;
    bool operator == (const N_MAILGROUP& right) const {
        return (
            GROUPNO == right.GROUPNO &&
            !strcmp(GROUPNAME, right.GROUPNAME)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        GROUPNO = 0;
        strcpy(GROUPNAME, " " );
#endif
    }
} mailgroupS;
#endif /* TRANSCLASS */

/* original struct of MAILITEMS ***********************************************/

#ifndef TRANSCLASS
typedef struct N_MAILITEMS {
    short FILIALNR;
    long UID;
    long NEWSNO;
    long FETCH_REL;
} mailitemsS;
#else /* TRANSCLASS */
typedef struct N_MAILITEMS {
    short FILIALNR;
    long UID;
    long NEWSNO;
    long FETCH_REL;
    bool operator == (const N_MAILITEMS& right) const {
        return (
            FILIALNR == right.FILIALNR &&
            UID == right.UID &&
            NEWSNO == right.NEWSNO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        FILIALNR = 0;
        UID = 0;
        NEWSNO = 0;
#endif
    }
} mailitemsS;
#endif /* TRANSCLASS */

/* original struct of MAILMESSAGE *********************************************/

#ifndef TRANSCLASS
typedef struct N_MAILMESSAGE {
    long NEWSNO;
    char MESSAGE[255];
    long TM_DATE;
    long TM_TIME;
    long UID;
    short FILIALNR;
    short PRIORITY;
    long FETCH_REL;
} mailmessageS;
#else /* TRANSCLASS */
typedef struct N_MAILMESSAGE {
    long NEWSNO;
    char MESSAGE[255];
    long TM_DATE;
    long TM_TIME;
    long UID;
    short FILIALNR;
    short PRIORITY;
    long FETCH_REL;
    bool operator == (const N_MAILMESSAGE& right) const {
        return (
            NEWSNO == right.NEWSNO &&
            !strcmp(MESSAGE, right.MESSAGE) &&
            TM_DATE == right.TM_DATE &&
            TM_TIME == right.TM_TIME &&
            UID == right.UID &&
            FILIALNR == right.FILIALNR &&
            PRIORITY == right.PRIORITY
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        NEWSNO = 0;
        strcpy(MESSAGE, " " );
        TM_DATE = 0;
        TM_TIME = 0;
        UID = 0;
        FILIALNR = 0;
        PRIORITY = 0;
#endif
    }
} mailmessageS;
#endif /* TRANSCLASS */

/* original struct of MAILUSERS ***********************************************/

#ifndef TRANSCLASS
typedef struct N_MAILUSERS {
    long GROUPNO;
    long UID;
    short FILIALNR;
    long FETCH_REL;
} mailusersS;
#else /* TRANSCLASS */
typedef struct N_MAILUSERS {
    long GROUPNO;
    long UID;
    short FILIALNR;
    long FETCH_REL;
    bool operator == (const N_MAILUSERS& right) const {
        return (
            GROUPNO == right.GROUPNO &&
            UID == right.UID &&
            FILIALNR == right.FILIALNR
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        GROUPNO = 0;
        UID = 0;
        FILIALNR = 0;
#endif
    }
} mailusersS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of MAILDEFINEDUSER *****************************/

struct C_MAILDEFINEDUSER {
    short FILIALNR;
    char USERNAME[9];
    long UID;
    long GROUPNO;
    long FETCH_REL;
};
/* Structur with real chartype of USERINFORMATION *****************************/

struct C_USERINFORMATION {
    long DATE;
    long VALIDTIMEFROM;
    long VALIDTIMETO;
    char INFOMESSAGE[255];
    short VALIDBRANCHNO;
    short USERBRANCHNO;
    long UID_ANLAGE;
    short PRIORITY;
    long FETCH_REL;
};
/* Structur with real chartype of MAILGROUP ***********************************/

struct C_MAILGROUP {
    long GROUPNO;
    char GROUPNAME[31];
    long FETCH_REL;
};
/* Structur with real chartype of MAILITEMS ***********************************/

struct C_MAILITEMS {
    short FILIALNR;
    long UID;
    long NEWSNO;
    long FETCH_REL;
};
/* Structur with real chartype of MAILMESSAGE *********************************/

struct C_MAILMESSAGE {
    long NEWSNO;
    char MESSAGE[255];
    long TM_DATE;
    long TM_TIME;
    long UID;
    short FILIALNR;
    short PRIORITY;
    long FETCH_REL;
};
/* Structur with real chartype of MAILUSERS ***********************************/

struct C_MAILUSERS {
    long GROUPNO;
    long UID;
    short FILIALNR;
    long FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of MAILDEFINEDUSER ***************************/

struct I_MAILDEFINEDUSER {
    short FILIALNR;
    short USERNAME;
    short UID;
    short GROUPNO;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of USERINFORMATION ***************************/

struct I_USERINFORMATION {
    short DATE;
    short VALIDTIMEFROM;
    short VALIDTIMETO;
    short INFOMESSAGE;
    short VALIDBRANCHNO;
    short USERBRANCHNO;
    short UID_ANLAGE;
    short PRIORITY;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of MAILGROUP *********************************/

struct I_MAILGROUP {
    short GROUPNO;
    short GROUPNAME;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of MAILITEMS *********************************/

struct I_MAILITEMS {
    short FILIALNR;
    short UID;
    short NEWSNO;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of MAILMESSAGE *******************************/

struct I_MAILMESSAGE {
    short NEWSNO;
    short MESSAGE;
    short TM_DATE;
    short TM_TIME;
    short UID;
    short FILIALNR;
    short PRIORITY;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of MAILUSERS *********************************/

struct I_MAILUSERS {
    short GROUPNO;
    short UID;
    short FILIALNR;
    short FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of MAILDEFINEDUSER *************************************/

#if defined (BUF_DESC)
static struct buf_desc MAILDEFINEDUSER_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 8, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MAILDEFINEDUSER_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 8, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of USERINFORMATION *************************************/

#if defined (BUF_DESC)
static struct buf_desc USERINFORMATION_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 254, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc USERINFORMATION_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 254, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of MAILGROUP *******************************************/

#if defined (BUF_DESC)
static struct buf_desc MAILGROUP_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MAILGROUP_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of MAILITEMS *******************************************/

#if defined (BUF_DESC)
static struct buf_desc MAILITEMS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MAILITEMS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of MAILMESSAGE *****************************************/

#if defined (BUF_DESC)
static struct buf_desc MAILMESSAGE_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 254, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MAILMESSAGE_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 254, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of MAILUSERS *******************************************/

#if defined (BUF_DESC)
static struct buf_desc MAILUSERS_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MAILUSERS_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* FunctionNumber-Define of MailDefinedUser ***********************************/

#define MAILDEFINEDUSER_SELALLUSER 1051
#define MAILDEFINEDUSER_SELALLUSERVZ 1322
#define MAILDEFINEDUSER_SELOPENMAIL 1059

/* FunctionNumber-Define of UserInformation ***********************************/

#define USERINFORMATION_CHECKFREE 1547
#define USERINFORMATION_INSERT 1546
#define USERINFORMATION_SELINFO 1545

/* FunctionNumber-Define of mailgroup *****************************************/

#define MAILGROUP_DELETEMAILGROUP 1045
#define MAILGROUP_INSERT 1044
#define MAILGROUP_SELMAILGROUP 1043
#define MAILGROUP_SELMAILGROUPVZ 1323
#define MAILGROUP_UPDATEMAILGROUP 1052

/* FunctionNumber-Define of mailitems *****************************************/

#define MAILITEMS_DELETEMESSAGE 1055
#define MAILITEMS_INSERT 1056
#define MAILITEMS_SELOPENNEWS 1050

/* FunctionNumber-Define of mailmessage ***************************************/

#define MAILMESSAGE_INSERT 1049
#define MAILMESSAGE_SELALLMESSAGE 1058
#define MAILMESSAGE_SELMAILMESSAGE 1054
#define MAILMESSAGE_SELNOTREAD 1057

/* FunctionNumber-Define of mailusers *****************************************/

#define MAILUSERS_DELETE 1048
#define MAILUSERS_DELETEALL 1053
#define MAILUSERS_DELETEALLVZ 1324
#define MAILUSERS_INSERT 1047
#define MAILUSERS_SELALL 1046

#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of MailDefinedUser *******************************/

#define SelAllUser 1051
#define SelAllUserVz 1322
#define SelOpenMail 1059

/* Old-FunctionNumber-Define of UserInformation *******************************/

#define CheckFree 1547
#define Insert 1546
#define SelInfo 1545

/* Old-FunctionNumber-Define of mailgroup *************************************/

#define DeleteMailGroup 1045
#define Insert 1044
#define SelMailGroup 1043
#define SelMailGroupVz 1323
#define UpdateMailGroup 1052

/* Old-FunctionNumber-Define of mailitems *************************************/

#define DeleteMessage 1055
#define Insert 1056
#define SelOpenNews 1050

/* Old-FunctionNumber-Define of mailmessage ***********************************/

#define Insert 1049
#define SelAllMessage 1058
#define SelMailMessage 1054
#define SelNotRead 1057

/* Old-FunctionNumber-Define of mailusers *************************************/

#define Delete 1048
#define DeleteAll 1053
#define DeleteAllVz 1324
#define Insert 1047
#define SelAll 1046

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

class CMAILDEFINEDUSER : public ppDadeVirtual {
public:
    maildefineduserS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<maildefineduserS> lst; // class list

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
                     vector< maildefineduserS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     maildefineduserS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< maildefineduserS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<maildefineduserS>::iterator
                 beginList() { return lst.begin(); }
    vector<maildefineduserS>::iterator
                 endList  () { return lst.end  (); }

    short        GetFilialnr() const { return s.FILIALNR; }
    const char*  GetUsername(ppString & t) const { t = s.USERNAME; t.erasespace(ppString::END); return t.c_str(); }
    long         GetUid() const { return s.UID; }
    long         GetGroupno() const { return s.GROUPNO; }

    const maildefineduserS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetUsername(const ppString & t) { ppGStrCopy(s.USERNAME, t.c_str(), L_MAILDEFINEDUSER_USERNAME); }
    void         SetUid(long t) { s.UID = t; }
    void         SetGroupno(long t) { s.GROUPNO = t; }

    void         SetStruct(const maildefineduserS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelAllUser(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1051, FetchRel, pos); return ret; }
    int          SelAllUserVz(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1322, FetchRel, pos); return ret; }
    int          SelOpenMail(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1059, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMAILDEFINEDUSER() {
        ::buf_default((void *)&s, MAILDEFINEDUSER_BES, MAILDEFINEDUSER_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMAILDEFINEDUSER() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MAILDEFINEDUSER_BES, MAILDEFINEDUSER_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MAILDEFINEDUSER_BES, (int)MAILDEFINEDUSER_ANZ, error_msg);
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
        if ( fkt_nr == 1051 ) return CursorServerCall(1051, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1322 ) return CursorServerCall(1322, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1059 ) return CursorServerCall(1059, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MAILDEFINEDUSER & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.USERNAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MAILDEFINEDUSER_BES, (int)MAILDEFINEDUSER_ANZ, error_msg);
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
        CMAILDEFINEDUSER c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MAILDEFINEDUSER_BES, (int)MAILDEFINEDUSER_ANZ, error_msg);
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

class CUSERINFORMATION : public ppDadeVirtual {
public:
    userinformationS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<userinformationS> lst; // class list

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
                     vector< userinformationS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     userinformationS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< userinformationS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<userinformationS>::iterator
                 beginList() { return lst.begin(); }
    vector<userinformationS>::iterator
                 endList  () { return lst.end  (); }

    long         GetDate() const { return s.DATE; }
    long         GetValidtimefrom() const { return s.VALIDTIMEFROM; }
    long         GetValidtimeto() const { return s.VALIDTIMETO; }
    const char*  GetInfomessage(ppString & t) const { t = s.INFOMESSAGE; t.erasespace(ppString::END); return t.c_str(); }
    short        GetValidbranchno() const { return s.VALIDBRANCHNO; }
    short        GetUserbranchno() const { return s.USERBRANCHNO; }
    long         GetUid_anlage() const { return s.UID_ANLAGE; }
    short        GetPriority() const { return s.PRIORITY; }

    const userinformationS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetDate(long t) { s.DATE = t; }
    void         SetValidtimefrom(long t) { s.VALIDTIMEFROM = t; }
    void         SetValidtimeto(long t) { s.VALIDTIMETO = t; }
    void         SetInfomessage(const ppString & t) { ppGStrCopy(s.INFOMESSAGE, t.c_str(), L_USERINFORMATION_INFOMESSAGE); }
    void         SetValidbranchno(short t) { s.VALIDBRANCHNO = t; }
    void         SetUserbranchno(short t) { s.USERBRANCHNO = t; }
    void         SetUid_anlage(long t) { s.UID_ANLAGE = t; }
    void         SetPriority(short t) { s.PRIORITY = t; }

    void         SetStruct(const userinformationS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          CheckFree(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1547, FetchRel, pos); return ret; }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1546, pos); Strip(s); return ret; }
    int          SelInfo(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1545, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CUSERINFORMATION() {
        ::buf_default((void *)&s, USERINFORMATION_BES, USERINFORMATION_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CUSERINFORMATION() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, USERINFORMATION_BES, USERINFORMATION_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, USERINFORMATION_BES, (int)USERINFORMATION_ANZ, error_msg);
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
        if ( fkt_nr == 1547 ) return CursorServerCall(1547, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1546 ) return UniqueServerCall(1546, pos);
        if ( fkt_nr == 1545 ) return CursorServerCall(1545, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_USERINFORMATION & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.INFOMESSAGE);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, USERINFORMATION_BES, (int)USERINFORMATION_ANZ, error_msg);
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
        CUSERINFORMATION c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, USERINFORMATION_BES, (int)USERINFORMATION_ANZ, error_msg);
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

class CMAILGROUP : public ppDadeVirtual {
public:
    mailgroupS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<mailgroupS> lst; // class list

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
                     vector< mailgroupS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     mailgroupS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< mailgroupS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<mailgroupS>::iterator
                 beginList() { return lst.begin(); }
    vector<mailgroupS>::iterator
                 endList  () { return lst.end  (); }

    long         GetGroupno() const { return s.GROUPNO; }
    const char*  GetGroupname(ppString & t) const { t = s.GROUPNAME; t.erasespace(ppString::END); return t.c_str(); }

    const mailgroupS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetGroupno(long t) { s.GROUPNO = t; }
    void         SetGroupname(const ppString & t) { ppGStrCopy(s.GROUPNAME, t.c_str(), L_MAILGROUP_GROUPNAME); }

    void         SetStruct(const mailgroupS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          DeleteMailGroup(int pos = 0) { return UniqueServerCall(1045, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1044, pos); Strip(s); return ret; }
    int          SelMailGroup(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1043, FetchRel, pos); return ret; }
    int          SelMailGroupVz(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1323, FetchRel, pos); return ret; }
    int          UpdateMailGroup(int pos = 0) { int ret = UniqueServerCall(1052, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMAILGROUP() {
        ::buf_default((void *)&s, MAILGROUP_BES, MAILGROUP_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMAILGROUP() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MAILGROUP_BES, MAILGROUP_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MAILGROUP_BES, (int)MAILGROUP_ANZ, error_msg);
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
        if ( fkt_nr == 1045 ) return UniqueServerCall(1045, pos);
        if ( fkt_nr == 1044 ) return UniqueServerCall(1044, pos);
        if ( fkt_nr == 1043 ) return CursorServerCall(1043, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1323 ) return CursorServerCall(1323, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1052 ) return UniqueServerCall(1052, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MAILGROUP & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.GROUPNAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MAILGROUP_BES, (int)MAILGROUP_ANZ, error_msg);
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
        CMAILGROUP c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MAILGROUP_BES, (int)MAILGROUP_ANZ, error_msg);
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

class CMAILITEMS : public ppDadeVirtual {
public:
    mailitemsS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<mailitemsS> lst; // class list

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
                     vector< mailitemsS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     mailitemsS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< mailitemsS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<mailitemsS>::iterator
                 beginList() { return lst.begin(); }
    vector<mailitemsS>::iterator
                 endList  () { return lst.end  (); }

    short        GetFilialnr() const { return s.FILIALNR; }
    long         GetUid() const { return s.UID; }
    long         GetNewsno() const { return s.NEWSNO; }

    const mailitemsS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetUid(long t) { s.UID = t; }
    void         SetNewsno(long t) { s.NEWSNO = t; }

    void         SetStruct(const mailitemsS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          DeleteMessage(int pos = 0) { return UniqueServerCall(1055, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1056, pos); Strip(s); return ret; }
    int          SelOpenNews(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1050, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMAILITEMS() {
        ::buf_default((void *)&s, MAILITEMS_BES, MAILITEMS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMAILITEMS() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MAILITEMS_BES, MAILITEMS_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MAILITEMS_BES, (int)MAILITEMS_ANZ, error_msg);
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
        if ( fkt_nr == 1055 ) return UniqueServerCall(1055, pos);
        if ( fkt_nr == 1056 ) return UniqueServerCall(1056, pos);
        if ( fkt_nr == 1050 ) return CursorServerCall(1050, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MAILITEMS & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MAILITEMS_BES, (int)MAILITEMS_ANZ, error_msg);
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
        CMAILITEMS c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MAILITEMS_BES, (int)MAILITEMS_ANZ, error_msg);
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

class CMAILMESSAGE : public ppDadeVirtual {
public:
    mailmessageS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<mailmessageS> lst; // class list

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
                     vector< mailmessageS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     mailmessageS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< mailmessageS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<mailmessageS>::iterator
                 beginList() { return lst.begin(); }
    vector<mailmessageS>::iterator
                 endList  () { return lst.end  (); }

    long         GetNewsno() const { return s.NEWSNO; }
    const char*  GetMessage(ppString & t) const { t = s.MESSAGE; t.erasespace(ppString::END); return t.c_str(); }
    long         GetTm_date() const { return s.TM_DATE; }
    long         GetTm_time() const { return s.TM_TIME; }
    long         GetUid() const { return s.UID; }
    short        GetFilialnr() const { return s.FILIALNR; }
    short        GetPriority() const { return s.PRIORITY; }

    const mailmessageS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetNewsno(long t) { s.NEWSNO = t; }
    void         SetMessage(const ppString & t) { ppGStrCopy(s.MESSAGE, t.c_str(), L_MAILMESSAGE_MESSAGE); }
    void         SetTm_date(long t) { s.TM_DATE = t; }
    void         SetTm_time(long t) { s.TM_TIME = t; }
    void         SetUid(long t) { s.UID = t; }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetPriority(short t) { s.PRIORITY = t; }

    void         SetStruct(const mailmessageS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          Insert(int pos = 0) { int ret = UniqueServerCall(1049, pos); Strip(s); return ret; }
    int          SelAllMessage(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1058, FetchRel, pos); return ret; }
    int          SelMailMessage(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1054, FetchRel, pos); return ret; }
    int          SelNotRead(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1057, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMAILMESSAGE() {
        ::buf_default((void *)&s, MAILMESSAGE_BES, MAILMESSAGE_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMAILMESSAGE() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MAILMESSAGE_BES, MAILMESSAGE_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MAILMESSAGE_BES, (int)MAILMESSAGE_ANZ, error_msg);
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
        if ( fkt_nr == 1049 ) return UniqueServerCall(1049, pos);
        if ( fkt_nr == 1058 ) return CursorServerCall(1058, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1054 ) return CursorServerCall(1054, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1057 ) return CursorServerCall(1057, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MAILMESSAGE & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.MESSAGE);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MAILMESSAGE_BES, (int)MAILMESSAGE_ANZ, error_msg);
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
        CMAILMESSAGE c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MAILMESSAGE_BES, (int)MAILMESSAGE_ANZ, error_msg);
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

class CMAILUSERS : public ppDadeVirtual {
public:
    mailusersS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<mailusersS> lst; // class list

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
                     vector< mailusersS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     mailusersS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< mailusersS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<mailusersS>::iterator
                 beginList() { return lst.begin(); }
    vector<mailusersS>::iterator
                 endList  () { return lst.end  (); }

    long         GetGroupno() const { return s.GROUPNO; }
    long         GetUid() const { return s.UID; }
    short        GetFilialnr() const { return s.FILIALNR; }

    const mailusersS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetGroupno(long t) { s.GROUPNO = t; }
    void         SetUid(long t) { s.UID = t; }
    void         SetFilialnr(short t) { s.FILIALNR = t; }

    void         SetStruct(const mailusersS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          Delete(int pos = 0) { return UniqueServerCall(1048, pos); }
    int          DeleteAll(int pos = 0) { return UniqueServerCall(1053, pos); }
    int          DeleteAllVz(int pos = 0) { return UniqueServerCall(1324, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1047, pos); Strip(s); return ret; }
    int          SelAll(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1046, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMAILUSERS() {
        ::buf_default((void *)&s, MAILUSERS_BES, MAILUSERS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMAILUSERS() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MAILUSERS_BES, MAILUSERS_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MAILUSERS_BES, (int)MAILUSERS_ANZ, error_msg);
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
        if ( fkt_nr == 1048 ) return UniqueServerCall(1048, pos);
        if ( fkt_nr == 1053 ) return UniqueServerCall(1053, pos);
        if ( fkt_nr == 1324 ) return UniqueServerCall(1324, pos);
        if ( fkt_nr == 1047 ) return UniqueServerCall(1047, pos);
        if ( fkt_nr == 1046 ) return CursorServerCall(1046, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MAILUSERS & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MAILUSERS_BES, (int)MAILUSERS_ANZ, error_msg);
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
        CMAILUSERS c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MAILUSERS_BES, (int)MAILUSERS_ANZ, error_msg);
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
