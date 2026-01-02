#ifndef __PP_TOURPLANTAG_H_
#define __PP_TOURPLANTAG_H_

/******************************************************************************/
/* c:\Source\Repos\pharmos.outbound.csc_load\dev\src\loadroutes\tourplantag ***/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <pplib/bufkon.h>

/* Length-Define of TOURPLANTAG ***********************************************/

#define L_TOURPLANTAG_IDFNR 11
#define L_TOURPLANTAG_DATUMKOMMI 11
#define L_TOURPLANTAG_TOURID 6
#define L_TOURPLANTAG_REIHENFOLGENR 11
#define L_TOURPLANTAG_FAHRTZEIT 11
#define L_TOURPLANTAG_BEMERKUNGEN 240
#define L_TOURPLANTAG_KZUPD 1
#define L_TOURPLANTAG_ISTVERBUNDTOUR 1
#define L_TOURPLANTAG_VERTRIEBSZENTRUMNR 6
#define L_TOURPLANTAG_KUNDENNR 11
#define L_TOURPLANTAG_KOART 1
#define L_TOURPLANTAG_TOURINAKTIV 1
#define L_TOURPLANTAG_KIPPZEIT 6
#define L_TOURPLANTAG_KZAUTOZUORD 1
#define L_TOURPLANTAG_ISTVATOUR 1
#define L_TOURPLANTAG_KDAUFTRAGART 2
#define L_TOURPLANTAG_DELIVERBRANCHNO 6
#define L_TOURPLANTAG_SENCLOSERDONE 1
#define L_TOURPLANTAG_ORDERLABELCOUNT 6
#define L_TOURPLANTAG_ISBTM 6
#define L_TOURPLANTAG_ISKK 6
#define L_TOURPLANTAG_ISK08 6
#define L_TOURPLANTAG_ISK20 6
#define L_TOURPLANTAG_RETURNSTOUR 6
#define L_TOURPLANTAG_TRANSPEXCLPSYCHO 6
#define L_TOURPLANTAG_TRANSPEXCLCOOLED 6
#define L_TOURPLANTAG_TRANSPEXCLEXPENSIVE 6
#define L_TOURPLANTAG_CHECKPOSITIONS 6
#define L_TOURPLANTAG_CHECKREMARK 40
#define L_TOURPLANTAG_PLANNEDCALL 11

/* Length/Count-Define of TOURPLANTAG *****************************************/

#define LS_TOURPLANTAG_IDFNR 10 + 1
#define LS_TOURPLANTAG_DATUMKOMMI 10 + 1
#define LS_TOURPLANTAG_TOURID 6 + 1
#define LS_TOURPLANTAG_REIHENFOLGENR 10 + 1
#define LS_TOURPLANTAG_FAHRTZEIT 10 + 1
#define LS_TOURPLANTAG_BEMERKUNGEN 240 + 1
#define LS_TOURPLANTAG_KZUPD 1 + 1
#define LS_TOURPLANTAG_ISTVERBUNDTOUR 1 + 1
#define LS_TOURPLANTAG_VERTRIEBSZENTRUMNR 5 + 1
#define LS_TOURPLANTAG_KUNDENNR 10 + 1
#define LS_TOURPLANTAG_KOART 1 + 1
#define LS_TOURPLANTAG_TOURINAKTIV 1 + 1
#define LS_TOURPLANTAG_KIPPZEIT 5 + 1
#define LS_TOURPLANTAG_KZAUTOZUORD 1 + 1
#define LS_TOURPLANTAG_ISTVATOUR 1 + 1
#define LS_TOURPLANTAG_KDAUFTRAGART 2 + 1
#define LS_TOURPLANTAG_DELIVERBRANCHNO 5 + 1
#define LS_TOURPLANTAG_SENCLOSERDONE 1 + 1
#define LS_TOURPLANTAG_ORDERLABELCOUNT 5 + 1
#define LS_TOURPLANTAG_ISBTM 5 + 1
#define LS_TOURPLANTAG_ISKK 5 + 1
#define LS_TOURPLANTAG_ISK08 5 + 1
#define LS_TOURPLANTAG_ISK20 5 + 1
#define LS_TOURPLANTAG_RETURNSTOUR 5 + 1
#define LS_TOURPLANTAG_TRANSPEXCLPSYCHO 5 + 1
#define LS_TOURPLANTAG_TRANSPEXCLCOOLED 5 + 1
#define LS_TOURPLANTAG_TRANSPEXCLEXPENSIVE 5 + 1
#define LS_TOURPLANTAG_CHECKPOSITIONS 5 + 1
#define LS_TOURPLANTAG_CHECKREMARK 40 + 1
#define LS_TOURPLANTAG_PLANNEDCALL 10 + 1

#define TOURPLANTAGIDFNR 0
#define TOURPLANTAGDATUMKOMMI 1
#define TOURPLANTAGTOURID 2
#define TOURPLANTAGREIHENFOLGENR 3
#define TOURPLANTAGFAHRTZEIT 4
#define TOURPLANTAGBEMERKUNGEN 5
#define TOURPLANTAGKZUPD 6
#define TOURPLANTAGISTVERBUNDTOUR 7
#define TOURPLANTAGVERTRIEBSZENTRUMNR 8
#define TOURPLANTAGKUNDENNR 9
#define TOURPLANTAGKOART 10
#define TOURPLANTAGTOURINAKTIV 11
#define TOURPLANTAGKIPPZEIT 12
#define TOURPLANTAGKZAUTOZUORD 13
#define TOURPLANTAGISTVATOUR 14
#define TOURPLANTAGKDAUFTRAGART 15
#define TOURPLANTAGDELIVERBRANCHNO 16
#define TOURPLANTAGSENCLOSERDONE 17
#define TOURPLANTAGORDERLABELCOUNT 18
#define TOURPLANTAGISBTM 19
#define TOURPLANTAGISKK 20
#define TOURPLANTAGISK08 21
#define TOURPLANTAGISK20 22
#define TOURPLANTAGRETURNSTOUR 23
#define TOURPLANTAGTRANSPEXCLPSYCHO 24
#define TOURPLANTAGTRANSPEXCLCOOLED 25
#define TOURPLANTAGTRANSPEXCLEXPENSIVE 26
#define TOURPLANTAGCHECKPOSITIONS 27
#define TOURPLANTAGCHECKREMARK 28
#define TOURPLANTAGPLANNEDCALL 29

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define TOURPLANTAG_H
#define TOURPLANTAG_ANZ ( sizeof(TOURPLANTAG_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of TOURPLANTAG ***************************************************/

#define TOURPLANTAG_LISTE \
        TOURPLANTAG.IDFNR,\
        TOURPLANTAG.DATUMKOMMI,\
        TOURPLANTAG.TOURID,\
        TOURPLANTAG.REIHENFOLGENR,\
        TOURPLANTAG.FAHRTZEIT,\
        TOURPLANTAG.BEMERKUNGEN,\
        TOURPLANTAG.KZUPD,\
        TOURPLANTAG.ISTVERBUNDTOUR,\
        TOURPLANTAG.VERTRIEBSZENTRUMNR,\
        TOURPLANTAG.KUNDENNR,\
        TOURPLANTAG.KOART,\
        TOURPLANTAG.TOURINAKTIV,\
        TOURPLANTAG.KIPPZEIT,\
        TOURPLANTAG.KZAUTOZUORD,\
        TOURPLANTAG.ISTVATOUR,\
        TOURPLANTAG.KDAUFTRAGART,\
        TOURPLANTAG.DELIVERBRANCHNO,\
        TOURPLANTAG.SENCLOSERDONE,\
        TOURPLANTAG.ORDERLABELCOUNT,\
        TOURPLANTAG.ISBTM,\
        TOURPLANTAG.ISKK,\
        TOURPLANTAG.ISK08,\
        TOURPLANTAG.ISK20,\
        TOURPLANTAG.RETURNSTOUR,\
        TOURPLANTAG.TRANSPEXCLPSYCHO,\
        TOURPLANTAG.TRANSPEXCLCOOLED,\
        TOURPLANTAG.TRANSPEXCLEXPENSIVE,\
        TOURPLANTAG.CHECKPOSITIONS,\
        TOURPLANTAG.CHECKREMARK,\
        TOURPLANTAG.PLANNEDCALL
#define TOURPLANTAG_LISTE_390 \
        IDFNR,\
        DATUMKOMMI,\
        TOURID,\
        REIHENFOLGENR,\
        FAHRTZEIT,\
        BEMERKUNGEN,\
        KZUPD,\
        ISTVERBUNDTOUR,\
        VERTRIEBSZENTRUMNR,\
        KUNDENNR,\
        KOART,\
        TOURINAKTIV,\
        KIPPZEIT,\
        KZAUTOZUORD,\
        ISTVATOUR,\
        KDAUFTRAGART,\
        DELIVERBRANCHNO,\
        SENCLOSERDONE,\
        ORDERLABELCOUNT,\
        ISBTM,\
        ISKK,\
        ISK08,\
        ISK20,\
        RETURNSTOUR,\
        TRANSPEXCLPSYCHO,\
        TRANSPEXCLCOOLED,\
        TRANSPEXCLEXPENSIVE,\
        CHECKPOSITIONS,\
        CHECKREMARK,\
        PLANNEDCALL
#define TOURPLANTAG_PLISTE \
        "TOURPLANTAG.IDFNR,"\
        "TOURPLANTAG.DATUMKOMMI,"\
        "TOURPLANTAG.TOURID,"\
        "TOURPLANTAG.REIHENFOLGENR,"\
        "TOURPLANTAG.FAHRTZEIT,"\
        "TOURPLANTAG.BEMERKUNGEN,"\
        "TOURPLANTAG.KZUPD,"\
        "TOURPLANTAG.ISTVERBUNDTOUR,"\
        "TOURPLANTAG.VERTRIEBSZENTRUMNR,"\
        "TOURPLANTAG.KUNDENNR,"\
        "TOURPLANTAG.KOART,"\
        "TOURPLANTAG.TOURINAKTIV,"\
        "TOURPLANTAG.KIPPZEIT,"\
        "TOURPLANTAG.KZAUTOZUORD,"\
        "TOURPLANTAG.ISTVATOUR,"\
        "TOURPLANTAG.KDAUFTRAGART,"\
        "TOURPLANTAG.DELIVERBRANCHNO,"\
        "TOURPLANTAG.SENCLOSERDONE,"\
        "TOURPLANTAG.ORDERLABELCOUNT,"\
        "TOURPLANTAG.ISBTM,"\
        "TOURPLANTAG.ISKK,"\
        "TOURPLANTAG.ISK08,"\
        "TOURPLANTAG.ISK20,"\
        "TOURPLANTAG.RETURNSTOUR,"\
        "TOURPLANTAG.TRANSPEXCLPSYCHO,"\
        "TOURPLANTAG.TRANSPEXCLCOOLED,"\
        "TOURPLANTAG.TRANSPEXCLEXPENSIVE,"\
        "TOURPLANTAG.CHECKPOSITIONS,"\
        "TOURPLANTAG.CHECKREMARK,"\
        "TOURPLANTAG.PLANNEDCALL"
#define TOURPLANTAG_PELISTE \
        "IDFNR,"\
        "DATUMKOMMI,"\
        "TOURID,"\
        "REIHENFOLGENR,"\
        "FAHRTZEIT,"\
        "BEMERKUNGEN,"\
        "KZUPD,"\
        "ISTVERBUNDTOUR,"\
        "VERTRIEBSZENTRUMNR,"\
        "KUNDENNR,"\
        "KOART,"\
        "TOURINAKTIV,"\
        "KIPPZEIT,"\
        "KZAUTOZUORD,"\
        "ISTVATOUR,"\
        "KDAUFTRAGART,"\
        "DELIVERBRANCHNO,"\
        "SENCLOSERDONE,"\
        "ORDERLABELCOUNT,"\
        "ISBTM,"\
        "ISKK,"\
        "ISK08,"\
        "ISK20,"\
        "RETURNSTOUR,"\
        "TRANSPEXCLPSYCHO,"\
        "TRANSPEXCLCOOLED,"\
        "TRANSPEXCLEXPENSIVE,"\
        "CHECKPOSITIONS,"\
        "CHECKREMARK,"\
        "PLANNEDCALL"
#define TOURPLANTAG_UPDLISTE \
        "IDFNR=?,"\
        "DATUMKOMMI=?,"\
        "TOURID=?,"\
        "REIHENFOLGENR=?,"\
        "FAHRTZEIT=?,"\
        "BEMERKUNGEN=?,"\
        "KZUPD=?,"\
        "ISTVERBUNDTOUR=?,"\
        "VERTRIEBSZENTRUMNR=?,"\
        "KUNDENNR=?,"\
        "KOART=?,"\
        "TOURINAKTIV=?,"\
        "KIPPZEIT=?,"\
        "KZAUTOZUORD=?,"\
        "ISTVATOUR=?,"\
        "KDAUFTRAGART=?,"\
        "DELIVERBRANCHNO=?,"\
        "SENCLOSERDONE=?,"\
        "ORDERLABELCOUNT=?,"\
        "ISBTM=?,"\
        "ISKK=?,"\
        "ISK08=?,"\
        "ISK20=?,"\
        "RETURNSTOUR=?,"\
        "TRANSPEXCLPSYCHO=?,"\
        "TRANSPEXCLCOOLED=?,"\
        "TRANSPEXCLEXPENSIVE=?,"\
        "CHECKPOSITIONS=?,"\
        "CHECKREMARK=?,"\
        "PLANNEDCALL=?"
/* SqlMacros-Define of TOURPLANTAG ********************************************/

#define TOURPLANTAG_ZEIGER(x) \
        :x->IDFNR,\
        :x->DATUMKOMMI,\
        :x->TOURID,\
        :x->REIHENFOLGENR,\
        :x->FAHRTZEIT,\
        :x->BEMERKUNGEN,\
        :x->KZUPD,\
        :x->ISTVERBUNDTOUR,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->KOART,\
        :x->TOURINAKTIV,\
        :x->KIPPZEIT,\
        :x->KZAUTOZUORD,\
        :x->ISTVATOUR,\
        :x->KDAUFTRAGART,\
        :x->DELIVERBRANCHNO,\
        :x->SENCLOSERDONE,\
        :x->ORDERLABELCOUNT,\
        :x->ISBTM,\
        :x->ISKK,\
        :x->ISK08,\
        :x->ISK20,\
        :x->RETURNSTOUR,\
        :x->TRANSPEXCLPSYCHO,\
        :x->TRANSPEXCLCOOLED,\
        :x->TRANSPEXCLEXPENSIVE,\
        :x->CHECKPOSITIONS,\
        :x->CHECKREMARK,\
        :x->PLANNEDCALL
#define TOURPLANTAG_ZEIGERSEL(x) \
        :x->IDFNR,\
        :x->DATUMKOMMI,\
        :x->TOURID,\
        :x->REIHENFOLGENR,\
        :x->FAHRTZEIT,\
        :x->BEMERKUNGEN,\
        :x->KZUPD,\
        :x->ISTVERBUNDTOUR,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->KOART,\
        :x->TOURINAKTIV,\
        :x->KIPPZEIT,\
        :x->KZAUTOZUORD,\
        :x->ISTVATOUR,\
        :x->KDAUFTRAGART,\
        :x->DELIVERBRANCHNO,\
        :x->SENCLOSERDONE,\
        :x->ORDERLABELCOUNT,\
        :x->ISBTM,\
        :x->ISKK,\
        :x->ISK08,\
        :x->ISK20,\
        :x->RETURNSTOUR,\
        :x->TRANSPEXCLPSYCHO,\
        :x->TRANSPEXCLCOOLED,\
        :x->TRANSPEXCLEXPENSIVE,\
        :x->CHECKPOSITIONS,\
        :x->CHECKREMARK,\
        :x->PLANNEDCALL
#define TOURPLANTAG_UPDATE(x) \
        TOURPLANTAG.IDFNR=:x->IDFNR,\
        TOURPLANTAG.DATUMKOMMI=:x->DATUMKOMMI,\
        TOURPLANTAG.TOURID=:x->TOURID,\
        TOURPLANTAG.REIHENFOLGENR=:x->REIHENFOLGENR,\
        TOURPLANTAG.FAHRTZEIT=:x->FAHRTZEIT,\
        TOURPLANTAG.BEMERKUNGEN=:x->BEMERKUNGEN,\
        TOURPLANTAG.KZUPD=:x->KZUPD,\
        TOURPLANTAG.ISTVERBUNDTOUR=:x->ISTVERBUNDTOUR,\
        TOURPLANTAG.VERTRIEBSZENTRUMNR=:x->VERTRIEBSZENTRUMNR,\
        TOURPLANTAG.KUNDENNR=:x->KUNDENNR,\
        TOURPLANTAG.KOART=:x->KOART,\
        TOURPLANTAG.TOURINAKTIV=:x->TOURINAKTIV,\
        TOURPLANTAG.KIPPZEIT=:x->KIPPZEIT,\
        TOURPLANTAG.KZAUTOZUORD=:x->KZAUTOZUORD,\
        TOURPLANTAG.ISTVATOUR=:x->ISTVATOUR,\
        TOURPLANTAG.KDAUFTRAGART=:x->KDAUFTRAGART,\
        TOURPLANTAG.DELIVERBRANCHNO=:x->DELIVERBRANCHNO,\
        TOURPLANTAG.SENCLOSERDONE=:x->SENCLOSERDONE,\
        TOURPLANTAG.ORDERLABELCOUNT=:x->ORDERLABELCOUNT,\
        TOURPLANTAG.ISBTM=:x->ISBTM,\
        TOURPLANTAG.ISKK=:x->ISKK,\
        TOURPLANTAG.ISK08=:x->ISK08,\
        TOURPLANTAG.ISK20=:x->ISK20,\
        TOURPLANTAG.RETURNSTOUR=:x->RETURNSTOUR,\
        TOURPLANTAG.TRANSPEXCLPSYCHO=:x->TRANSPEXCLPSYCHO,\
        TOURPLANTAG.TRANSPEXCLCOOLED=:x->TRANSPEXCLCOOLED,\
        TOURPLANTAG.TRANSPEXCLEXPENSIVE=:x->TRANSPEXCLEXPENSIVE,\
        TOURPLANTAG.CHECKPOSITIONS=:x->CHECKPOSITIONS,\
        TOURPLANTAG.CHECKREMARK=:x->CHECKREMARK,\
        TOURPLANTAG.PLANNEDCALL=:x->PLANNEDCALL
/* SqlMacros390-Define of TOURPLANTAG *****************************************/

#define TOURPLANTAG_ZEIGER_390 \
        :IDFNR,\
        :DATUMKOMMI,\
        :TOURID,\
        :REIHENFOLGENR,\
        :FAHRTZEIT,\
        :BEMERKUNGEN,\
        :KZUPD,\
        :ISTVERBUNDTOUR,\
        :VERTRIEBSZENTRUMNR,\
        :KUNDENNR,\
        :KOART,\
        :TOURINAKTIV,\
        :KIPPZEIT,\
        :KZAUTOZUORD,\
        :ISTVATOUR,\
        :KDAUFTRAGART,\
        :DELIVERBRANCHNO,\
        :SENCLOSERDONE,\
        :ORDERLABELCOUNT,\
        :ISBTM,\
        :ISKK,\
        :ISK08,\
        :ISK20,\
        :RETURNSTOUR,\
        :TRANSPEXCLPSYCHO,\
        :TRANSPEXCLCOOLED,\
        :TRANSPEXCLEXPENSIVE,\
        :CHECKPOSITIONS,\
        :CHECKREMARK,\
        :PLANNEDCALL
#define TOURPLANTAG_UPDATE_390 \
        IDFNR=:IDFNR,\
        DATUMKOMMI=:DATUMKOMMI,\
        TOURID=:TOURID,\
        REIHENFOLGENR=:REIHENFOLGENR,\
        FAHRTZEIT=:FAHRTZEIT,\
        BEMERKUNGEN=:BEMERKUNGEN,\
        KZUPD=:KZUPD,\
        ISTVERBUNDTOUR=:ISTVERBUNDTOUR,\
        VERTRIEBSZENTRUMNR=:VERTRIEBSZENTRUMNR,\
        KUNDENNR=:KUNDENNR,\
        KOART=:KOART,\
        TOURINAKTIV=:TOURINAKTIV,\
        KIPPZEIT=:KIPPZEIT,\
        KZAUTOZUORD=:KZAUTOZUORD,\
        ISTVATOUR=:ISTVATOUR,\
        KDAUFTRAGART=:KDAUFTRAGART,\
        DELIVERBRANCHNO=:DELIVERBRANCHNO,\
        SENCLOSERDONE=:SENCLOSERDONE,\
        ORDERLABELCOUNT=:ORDERLABELCOUNT,\
        ISBTM=:ISBTM,\
        ISKK=:ISKK,\
        ISK08=:ISK08,\
        ISK20=:ISK20,\
        RETURNSTOUR=:RETURNSTOUR,\
        TRANSPEXCLPSYCHO=:TRANSPEXCLPSYCHO,\
        TRANSPEXCLCOOLED=:TRANSPEXCLCOOLED,\
        TRANSPEXCLEXPENSIVE=:TRANSPEXCLEXPENSIVE,\
        CHECKPOSITIONS=:CHECKPOSITIONS,\
        CHECKREMARK=:CHECKREMARK,\
        PLANNEDCALL=:PLANNEDCALL
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of TOURPLANTAG *********************************************/

#ifndef TRANSCLASS
typedef struct N_TOURPLANTAG {
    long IDFNR;
    long DATUMKOMMI;
    char TOURID[7];
    long REIHENFOLGENR;
    long FAHRTZEIT;
    char BEMERKUNGEN[241];
    char KZUPD[2];
    char ISTVERBUNDTOUR[2];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char KOART[2];
    char TOURINAKTIV[2];
    short KIPPZEIT;
    char KZAUTOZUORD[2];
    char ISTVATOUR[2];
    char KDAUFTRAGART[3];
    short DELIVERBRANCHNO;
    char SENCLOSERDONE[2];
    short ORDERLABELCOUNT;
    short ISBTM;
    short ISKK;
    short ISK08;
    short ISK20;
    short RETURNSTOUR;
    short TRANSPEXCLPSYCHO;
    short TRANSPEXCLCOOLED;
    short TRANSPEXCLEXPENSIVE;
    short CHECKPOSITIONS;
    char CHECKREMARK[41];
    long PLANNEDCALL;
} tourplantagS;
#else /* TRANSCLASS */
typedef struct N_TOURPLANTAG {
    long IDFNR;
    long DATUMKOMMI;
    char TOURID[7];
    long REIHENFOLGENR;
    long FAHRTZEIT;
    char BEMERKUNGEN[241];
    char KZUPD[2];
    char ISTVERBUNDTOUR[2];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char KOART[2];
    char TOURINAKTIV[2];
    short KIPPZEIT;
    char KZAUTOZUORD[2];
    char ISTVATOUR[2];
    char KDAUFTRAGART[3];
    short DELIVERBRANCHNO;
    char SENCLOSERDONE[2];
    short ORDERLABELCOUNT;
    short ISBTM;
    short ISKK;
    short ISK08;
    short ISK20;
    short RETURNSTOUR;
    short TRANSPEXCLPSYCHO;
    short TRANSPEXCLCOOLED;
    short TRANSPEXCLEXPENSIVE;
    short CHECKPOSITIONS;
    char CHECKREMARK[41];
    long PLANNEDCALL;

    bool operator == (const N_TOURPLANTAG& right) const {
        return (
            IDFNR == right.IDFNR &&
            DATUMKOMMI == right.DATUMKOMMI &&
            !strcmp(TOURID, right.TOURID) &&
            REIHENFOLGENR == right.REIHENFOLGENR &&
            FAHRTZEIT == right.FAHRTZEIT &&
            !strcmp(BEMERKUNGEN, right.BEMERKUNGEN) &&
            !strcmp(KZUPD, right.KZUPD) &&
            !strcmp(ISTVERBUNDTOUR, right.ISTVERBUNDTOUR) &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            !strcmp(KOART, right.KOART) &&
            !strcmp(TOURINAKTIV, right.TOURINAKTIV) &&
            KIPPZEIT == right.KIPPZEIT &&
            !strcmp(KZAUTOZUORD, right.KZAUTOZUORD) &&
            !strcmp(ISTVATOUR, right.ISTVATOUR) &&
            !strcmp(KDAUFTRAGART, right.KDAUFTRAGART) &&
            DELIVERBRANCHNO == right.DELIVERBRANCHNO &&
            !strcmp(SENCLOSERDONE, right.SENCLOSERDONE) &&
            ORDERLABELCOUNT == right.ORDERLABELCOUNT &&
            ISBTM == right.ISBTM &&
            ISKK == right.ISKK &&
            ISK08 == right.ISK08 &&
            ISK20 == right.ISK20 &&
            RETURNSTOUR == right.RETURNSTOUR &&
            TRANSPEXCLPSYCHO == right.TRANSPEXCLPSYCHO &&
            TRANSPEXCLCOOLED == right.TRANSPEXCLCOOLED &&
            TRANSPEXCLEXPENSIVE == right.TRANSPEXCLEXPENSIVE &&
            CHECKPOSITIONS == right.CHECKPOSITIONS &&
            !strcmp(CHECKREMARK, right.CHECKREMARK) &&
            PLANNEDCALL == right.PLANNEDCALL
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        IDFNR = 0;
        DATUMKOMMI = 0;
        strcpy(TOURID, " " );
        REIHENFOLGENR = 0;
        FAHRTZEIT = 0;
        strcpy(BEMERKUNGEN, " " );
        strcpy(KZUPD, " " );
        strcpy(ISTVERBUNDTOUR, " " );
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        strcpy(KOART, " " );
        strcpy(TOURINAKTIV, " " );
        KIPPZEIT = 0;
        strcpy(KZAUTOZUORD, " " );
        strcpy(ISTVATOUR, " " );
        strcpy(KDAUFTRAGART, " " );
        DELIVERBRANCHNO = 0;
        strcpy(SENCLOSERDONE, " " );
        ORDERLABELCOUNT = 0;
        ISBTM = 0;
        ISKK = 0;
        ISK08 = 0;
        ISK20 = 0;
        RETURNSTOUR = 0;
        TRANSPEXCLPSYCHO = 0;
        TRANSPEXCLCOOLED = 0;
        TRANSPEXCLEXPENSIVE = 0;
        CHECKPOSITIONS = 0;
        strcpy(CHECKREMARK, " " );
        PLANNEDCALL = 0;
#endif
    }
} tourplantagS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of TOURPLANTAG ***************************************/

struct S_TOURPLANTAG {
    char IDFNR[11];
    char DATUMKOMMI[11];
    char TOURID[6 + 1];
    char REIHENFOLGENR[11];
    char FAHRTZEIT[11];
    char BEMERKUNGEN[240 + 1];
    char KZUPD[1 + 1];
    char ISTVERBUNDTOUR[1 + 1];
    char VERTRIEBSZENTRUMNR[7];
    char KUNDENNR[11];
    char KOART[1 + 1];
    char TOURINAKTIV[1 + 1];
    char KIPPZEIT[7];
    char KZAUTOZUORD[1 + 1];
    char ISTVATOUR[1 + 1];
    char KDAUFTRAGART[2 + 1];
    char DELIVERBRANCHNO[7];
    char SENCLOSERDONE[1 + 1];
    char ORDERLABELCOUNT[7];
    char ISBTM[7];
    char ISKK[7];
    char ISK08[7];
    char ISK20[7];
    char RETURNSTOUR[7];
    char TRANSPEXCLPSYCHO[7];
    char TRANSPEXCLCOOLED[7];
    char TRANSPEXCLEXPENSIVE[7];
    char CHECKPOSITIONS[7];
    char CHECKREMARK[40 + 1];
    char PLANNEDCALL[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of TOURPLANTAG **********************/

struct O_TOURPLANTAG {
    char IDFNR[11];
    char DATUMKOMMI[11];
    char TOURID[6];
    char REIHENFOLGENR[11];
    char FAHRTZEIT[11];
    char BEMERKUNGEN[240];
    char KZUPD[1];
    char ISTVERBUNDTOUR[1];
    char VERTRIEBSZENTRUMNR[7];
    char KUNDENNR[11];
    char KOART[1];
    char TOURINAKTIV[1];
    char KIPPZEIT[7];
    char KZAUTOZUORD[1];
    char ISTVATOUR[1];
    char KDAUFTRAGART[2];
    char DELIVERBRANCHNO[7];
    char SENCLOSERDONE[1];
    char ORDERLABELCOUNT[7];
    char ISBTM[7];
    char ISKK[7];
    char ISK08[7];
    char ISK20[7];
    char RETURNSTOUR[7];
    char TRANSPEXCLPSYCHO[7];
    char TRANSPEXCLCOOLED[7];
    char TRANSPEXCLEXPENSIVE[7];
    char CHECKPOSITIONS[7];
    char CHECKREMARK[40];
    char PLANNEDCALL[11];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of TOURPLANTAG *********************************/

struct C_TOURPLANTAG {
    long IDFNR;
    long DATUMKOMMI;
    char TOURID[7];
    long REIHENFOLGENR;
    long FAHRTZEIT;
    char BEMERKUNGEN[241];
    char KZUPD;
    char ISTVERBUNDTOUR;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char KOART;
    char TOURINAKTIV;
    short KIPPZEIT;
    char KZAUTOZUORD;
    char ISTVATOUR;
    char KDAUFTRAGART[3];
    short DELIVERBRANCHNO;
    char SENCLOSERDONE;
    short ORDERLABELCOUNT;
    short ISBTM;
    short ISKK;
    short ISK08;
    short ISK20;
    short RETURNSTOUR;
    short TRANSPEXCLPSYCHO;
    short TRANSPEXCLCOOLED;
    short TRANSPEXCLEXPENSIVE;
    short CHECKPOSITIONS;
    char CHECKREMARK[41];
    long PLANNEDCALL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of TOURPLANTAG *******************************/

struct I_TOURPLANTAG {
    short IDFNR;
    short DATUMKOMMI;
    short TOURID;
    short REIHENFOLGENR;
    short FAHRTZEIT;
    short BEMERKUNGEN;
    short KZUPD;
    short ISTVERBUNDTOUR;
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short KOART;
    short TOURINAKTIV;
    short KIPPZEIT;
    short KZAUTOZUORD;
    short ISTVATOUR;
    short KDAUFTRAGART;
    short DELIVERBRANCHNO;
    short SENCLOSERDONE;
    short ORDERLABELCOUNT;
    short ISBTM;
    short ISKK;
    short ISK08;
    short ISK20;
    short RETURNSTOUR;
    short TRANSPEXCLPSYCHO;
    short TRANSPEXCLCOOLED;
    short TRANSPEXCLEXPENSIVE;
    short CHECKPOSITIONS;
    short CHECKREMARK;
    short PLANNEDCALL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of TOURPLANTAG *****************************************/

#if defined (BUF_DESC)
static struct buf_desc TOURPLANTAG_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 240, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 2, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 40, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc TOURPLANTAG_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 240, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 2, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 40, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* description for datatypes of TOURPLANTAG ***********************************/

 #define TOURPLANTAG_S390 \
         long IDFNR; \
         long DATUMKOMMI; \
         char TOURID[7]; \
         long REIHENFOLGENR; \
         long FAHRTZEIT; \
         char BEMERKUNGEN[241]; \
         char KZUPD; \
         char ISTVERBUNDTOUR; \
         short VERTRIEBSZENTRUMNR; \
         long KUNDENNR; \
         char KOART; \
         char TOURINAKTIV; \
         short KIPPZEIT; \
         char KZAUTOZUORD; \
         char ISTVATOUR; \
         char KDAUFTRAGART[3]; \
         short DELIVERBRANCHNO; \
         char SENCLOSERDONE; \
         short ORDERLABELCOUNT; \
         short ISBTM; \
         short ISKK; \
         short ISK08; \
         short ISK20; \
         short RETURNSTOUR; \
         short TRANSPEXCLPSYCHO; \
         short TRANSPEXCLCOOLED; \
         short TRANSPEXCLEXPENSIVE; \
         short CHECKPOSITIONS; \
         char CHECKREMARK[41]; \
         long PLANNEDCALL; \



/* Copy-Function Struct to single Data TOURPLANTAG ****************************/

 #define TOURPLANTAG_S390_COPY_TO_SINGLE(_x_) \
         IDFNR=_x_->IDFNR;\
         DATUMKOMMI=_x_->DATUMKOMMI;\
          strcpy(TOURID,_x_->TOURID);\
         REIHENFOLGENR=_x_->REIHENFOLGENR;\
         FAHRTZEIT=_x_->FAHRTZEIT;\
          strcpy(BEMERKUNGEN,_x_->BEMERKUNGEN);\
         KZUPD=_x_->KZUPD;\
         ISTVERBUNDTOUR=_x_->ISTVERBUNDTOUR;\
         VERTRIEBSZENTRUMNR=_x_->VERTRIEBSZENTRUMNR;\
         KUNDENNR=_x_->KUNDENNR;\
         KOART=_x_->KOART;\
         TOURINAKTIV=_x_->TOURINAKTIV;\
         KIPPZEIT=_x_->KIPPZEIT;\
         KZAUTOZUORD=_x_->KZAUTOZUORD;\
         ISTVATOUR=_x_->ISTVATOUR;\
          strcpy(KDAUFTRAGART,_x_->KDAUFTRAGART);\
         DELIVERBRANCHNO=_x_->DELIVERBRANCHNO;\
         SENCLOSERDONE=_x_->SENCLOSERDONE;\
         ORDERLABELCOUNT=_x_->ORDERLABELCOUNT;\
         ISBTM=_x_->ISBTM;\
         ISKK=_x_->ISKK;\
         ISK08=_x_->ISK08;\
         ISK20=_x_->ISK20;\
         RETURNSTOUR=_x_->RETURNSTOUR;\
         TRANSPEXCLPSYCHO=_x_->TRANSPEXCLPSYCHO;\
         TRANSPEXCLCOOLED=_x_->TRANSPEXCLCOOLED;\
         TRANSPEXCLEXPENSIVE=_x_->TRANSPEXCLEXPENSIVE;\
         CHECKPOSITIONS=_x_->CHECKPOSITIONS;\
          strcpy(CHECKREMARK,_x_->CHECKREMARK);\
         PLANNEDCALL=_x_->PLANNEDCALL;\

 #define TOURPLANTAG_S390_COPY_TO_STRUCT(_x_) \
          _x_->IDFNR=IDFNR;\
          _x_->DATUMKOMMI=DATUMKOMMI;\
          strcpy(_x_->TOURID,TOURID);\
          _x_->REIHENFOLGENR=REIHENFOLGENR;\
          _x_->FAHRTZEIT=FAHRTZEIT;\
          strcpy(_x_->BEMERKUNGEN,BEMERKUNGEN);\
          _x_->KZUPD=KZUPD;\
          _x_->ISTVERBUNDTOUR=ISTVERBUNDTOUR;\
          _x_->VERTRIEBSZENTRUMNR=VERTRIEBSZENTRUMNR;\
          _x_->KUNDENNR=KUNDENNR;\
          _x_->KOART=KOART;\
          _x_->TOURINAKTIV=TOURINAKTIV;\
          _x_->KIPPZEIT=KIPPZEIT;\
          _x_->KZAUTOZUORD=KZAUTOZUORD;\
          _x_->ISTVATOUR=ISTVATOUR;\
          strcpy(_x_->KDAUFTRAGART,KDAUFTRAGART);\
          _x_->DELIVERBRANCHNO=DELIVERBRANCHNO;\
          _x_->SENCLOSERDONE=SENCLOSERDONE;\
          _x_->ORDERLABELCOUNT=ORDERLABELCOUNT;\
          _x_->ISBTM=ISBTM;\
          _x_->ISKK=ISKK;\
          _x_->ISK08=ISK08;\
          _x_->ISK20=ISK20;\
          _x_->RETURNSTOUR=RETURNSTOUR;\
          _x_->TRANSPEXCLPSYCHO=TRANSPEXCLPSYCHO;\
          _x_->TRANSPEXCLCOOLED=TRANSPEXCLCOOLED;\
          _x_->TRANSPEXCLEXPENSIVE=TRANSPEXCLEXPENSIVE;\
          _x_->CHECKPOSITIONS=CHECKPOSITIONS;\
          strcpy(_x_->CHECKREMARK,CHECKREMARK);\
          _x_->PLANNEDCALL=PLANNEDCALL;\



/* FunctionNumber-Define of tourplantag ***************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of tourplantag ***********************************/


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

class CTOURPLANTAG : public ppDadeVirtual {
public:
    tourplantagS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<tourplantagS> lst; // class list

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
                     vector< tourplantagS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     tourplantagS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< tourplantagS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<tourplantagS>::iterator
                 beginList() { return lst.begin(); }
    vector<tourplantagS>::iterator
                 endList  () { return lst.end  (); }

    long         GetIdfnr() const { return s.IDFNR; }
    long         GetDatumkommi() const { return s.DATUMKOMMI; }
    const char*  GetTourid(ppString & t) const { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
    long         GetReihenfolgenr() const { return s.REIHENFOLGENR; }
    long         GetFahrtzeit() const { return s.FAHRTZEIT; }
    const char*  GetBemerkungen(ppString & t) const { t = s.BEMERKUNGEN; t.erasespace(ppString::END); return t.c_str(); }
    char         GetKzupd() const { return s.KZUPD[0]; }
    char         GetIstverbundtour() const { return s.ISTVERBUNDTOUR[0]; }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    char         GetKoart() const { return s.KOART[0]; }
    char         GetTourinaktiv() const { return s.TOURINAKTIV[0]; }
    short        GetKippzeit() const { return s.KIPPZEIT; }
    char         GetKzautozuord() const { return s.KZAUTOZUORD[0]; }
    char         GetIstvatour() const { return s.ISTVATOUR[0]; }
    const char*  GetKdauftragart(ppString & t) const { t = s.KDAUFTRAGART; t.erasespace(ppString::END); return t.c_str(); }
    short        GetDeliverbranchno() const { return s.DELIVERBRANCHNO; }
    char         GetSencloserdone() const { return s.SENCLOSERDONE[0]; }
    short        GetOrderlabelcount() const { return s.ORDERLABELCOUNT; }
    short        GetIsbtm() const { return s.ISBTM; }
    short        GetIskk() const { return s.ISKK; }
    short        GetIsk08() const { return s.ISK08; }
    short        GetIsk20() const { return s.ISK20; }
    short        GetReturnstour() const { return s.RETURNSTOUR; }
    short        GetTranspexclpsycho() const { return s.TRANSPEXCLPSYCHO; }
    short        GetTranspexclcooled() const { return s.TRANSPEXCLCOOLED; }
    short        GetTranspexclexpensive() const { return s.TRANSPEXCLEXPENSIVE; }
    short        GetCheckpositions() const { return s.CHECKPOSITIONS; }
    const char*  GetCheckremark(ppString & t) const { t = s.CHECKREMARK; t.erasespace(ppString::END); return t.c_str(); }
    long         GetPlannedcall() const { return s.PLANNEDCALL; }

    const tourplantagS &
                 GetStruct() const { return s; }
    void         SetIdfnr(long t) { s.IDFNR = t; }
    void         SetDatumkommi(long t) { s.DATUMKOMMI = t; }
    void         SetTourid(const ppString & t) { ppGStrCopy(s.TOURID, t.c_str(), L_TOURPLANTAG_TOURID); }
    void         SetReihenfolgenr(long t) { s.REIHENFOLGENR = t; }
    void         SetFahrtzeit(long t) { s.FAHRTZEIT = t; }
    void         SetBemerkungen(const ppString & t) { ppGStrCopy(s.BEMERKUNGEN, t.c_str(), L_TOURPLANTAG_BEMERKUNGEN); }
    void         SetKzupd(char t) { s.KZUPD[0] = t; s.KZUPD[1] = '\0';}
    void         SetIstverbundtour(char t) { s.ISTVERBUNDTOUR[0] = t; s.ISTVERBUNDTOUR[1] = '\0';}
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetKoart(char t) { s.KOART[0] = t; s.KOART[1] = '\0';}
    void         SetTourinaktiv(char t) { s.TOURINAKTIV[0] = t; s.TOURINAKTIV[1] = '\0';}
    void         SetKippzeit(short t) { s.KIPPZEIT = t; }
    void         SetKzautozuord(char t) { s.KZAUTOZUORD[0] = t; s.KZAUTOZUORD[1] = '\0';}
    void         SetIstvatour(char t) { s.ISTVATOUR[0] = t; s.ISTVATOUR[1] = '\0';}
    void         SetKdauftragart(const ppString & t) { ppGStrCopy(s.KDAUFTRAGART, t.c_str(), L_TOURPLANTAG_KDAUFTRAGART); }
    void         SetDeliverbranchno(short t) { s.DELIVERBRANCHNO = t; }
    void         SetSencloserdone(char t) { s.SENCLOSERDONE[0] = t; s.SENCLOSERDONE[1] = '\0';}
    void         SetOrderlabelcount(short t) { s.ORDERLABELCOUNT = t; }
    void         SetIsbtm(short t) { s.ISBTM = t; }
    void         SetIskk(short t) { s.ISKK = t; }
    void         SetIsk08(short t) { s.ISK08 = t; }
    void         SetIsk20(short t) { s.ISK20 = t; }
    void         SetReturnstour(short t) { s.RETURNSTOUR = t; }
    void         SetTranspexclpsycho(short t) { s.TRANSPEXCLPSYCHO = t; }
    void         SetTranspexclcooled(short t) { s.TRANSPEXCLCOOLED = t; }
    void         SetTranspexclexpensive(short t) { s.TRANSPEXCLEXPENSIVE = t; }
    void         SetCheckpositions(short t) { s.CHECKPOSITIONS = t; }
    void         SetCheckremark(const ppString & t) { ppGStrCopy(s.CHECKREMARK, t.c_str(), L_TOURPLANTAG_CHECKREMARK); }
    void         SetPlannedcall(long t) { s.PLANNEDCALL = t; }

    void         SetStruct(const tourplantagS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CTOURPLANTAG() {
        ::buf_default((void *)&s, TOURPLANTAG_BES, TOURPLANTAG_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CTOURPLANTAG() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, TOURPLANTAG_BES, TOURPLANTAG_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, TOURPLANTAG_BES, (int)TOURPLANTAG_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, TOURPLANTAG_BES, (int)TOURPLANTAG_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_TOURPLANTAG & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.TOURID);
        ppGStripLast(d.BEMERKUNGEN);
        ppGStripLast(d.KDAUFTRAGART);
        ppGStripLast(d.CHECKREMARK);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, TOURPLANTAG_BES, (int)TOURPLANTAG_ANZ, error_msg);
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
/* CreateSqlStatement of TOURPLANTAG ******************************************/

 #define TOURPLANTAG_CREATE(x) EXEC SQL create table x (\
         IDFNR integer default 0 not null,\
         DATUMKOMMI integer default 0 not null,\
         TOURID char(6) default " " not null,\
         REIHENFOLGENR integer default 0 not null,\
         FAHRTZEIT integer default 0 not null,\
         BEMERKUNGEN varchar(240,0) default " " not null,\
         KZUPD char(1) default " " not null,\
         ISTVERBUNDTOUR char(1) default " " not null,\
         VERTRIEBSZENTRUMNR smallint default 0 not null,\
         KUNDENNR integer default 0 not null,\
         KOART char(1) default " " not null,\
         TOURINAKTIV char(1) default " " not null,\
         KIPPZEIT smallint default 0 not null,\
         KZAUTOZUORD char(1) default " " not null,\
         ISTVATOUR char(1) default " " not null,\
         KDAUFTRAGART char(2) default " " not null,\
         DELIVERBRANCHNO smallint default 0 not null,\
         SENCLOSERDONE char(1) default " " not null,\
         ORDERLABELCOUNT smallint default 0 not null,\
         ISBTM smallint default 0 not null,\
         ISKK smallint default 0 not null,\
         ISK08 smallint default 0 not null,\
         ISK20 smallint default 0 not null,\
         RETURNSTOUR smallint default 0 not null,\
         TRANSPEXCLPSYCHO smallint default 0 not null,\
         TRANSPEXCLCOOLED smallint default 0 not null,\
         TRANSPEXCLEXPENSIVE smallint default 0 not null,\
         CHECKPOSITIONS smallint default 0 not null,\
         CHECKREMARK char(40) default " " not null,\
         PLANNEDCALL integer default 0 not null) in KscCustomer extent size 1020 next size 104 lock mode row;



/* CreateIndexStatement of TOURPLANTAG ****************************************/

 #define TOURPLANTAG_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_tourplantag_2 on _X_(\
              VertriebszentrumNr,\
              KundenNr,\
              datumkommi,\
              tourid ) in KscCustomerIdx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index tourplantagx on _X_(\
              idfnr,\
              datumkommi,\
              tourid ) in KscCustomerIdx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of TOURPLANTAG ****************************************/

 #define TOURPLANTAG_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_tourplantag_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index tourplantagx;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
