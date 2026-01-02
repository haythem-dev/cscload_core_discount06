#ifndef __PP_KDVERBUND_H_
#define __PP_KDVERBUND_H_

/******************************************************************************/
/* d:\prj\DF\UNIX\tpldauftr\kdverbund *****************************************/
/* produced by DADE 6.22.0 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <pplib/bufkon.h>

/* Length-Define of KDVERBUND *************************************************/

#define L_KDVERBUND_HERKUNFTFILIALE 6
#define L_KDVERBUND_KDAUFTRAGNR 11
#define L_KDVERBUND_VBSTATUS 1
#define L_KDVERBUND_KDAUFTRAGART 2
#define L_KDVERBUND_KOART 1
#define L_KDVERBUND_BUCHART 1
#define L_KDVERBUND_IDFNR 11
#define L_KDVERBUND_NAMEAPO 40
#define L_KDVERBUND_STRASSE 30
#define L_KDVERBUND_POSTLEITZAHL 10
#define L_KDVERBUND_ORT 30
#define L_KDVERBUND_TELNR 20
#define L_KDVERBUND_TELNRDAFUE 20
#define L_KDVERBUND_FAXNR 25
#define L_KDVERBUND_ANREDEKZ 6
#define L_KDVERBUND_KDGRUPPE 2
#define L_KDVERBUND_PERSONALNRVERTR 11
#define L_KDVERBUND_IMSBEZIRKNR 11
#define L_KDVERBUND_NAMEINHABER 30
#define L_KDVERBUND_TOURID 6
#define L_KDVERBUND_KUNDETEXT 240
#define L_KDVERBUND_BEMERKUNGEN 240
#define L_KDVERBUND_DATUM 11
#define L_KDVERBUND_UHRZEIT 11
#define L_KDVERBUND_FILIALNR 6
#define L_KDVERBUND_LAGRECHTOUR 11
#define L_KDVERBUND_BGANR 11
#define L_KDVERBUND_SBAAUFTRAG 1
#define L_KDVERBUND_WEEKDAY 6
#define L_KDVERBUND_KZSPRACHE 2
#define L_KDVERBUND_SKDVERSANDAPO 1
#define L_KDVERBUND_PAYMENT_TERM 4
#define L_KDVERBUND_IBTTYPE 6

/* Length/Count-Define of KDVERBUND *******************************************/

#define LS_KDVERBUND_HERKUNFTFILIALE 5 + 1
#define LS_KDVERBUND_KDAUFTRAGNR 10 + 1
#define LS_KDVERBUND_VBSTATUS 1 + 1
#define LS_KDVERBUND_KDAUFTRAGART 2 + 1
#define LS_KDVERBUND_KOART 1 + 1
#define LS_KDVERBUND_BUCHART 1 + 1
#define LS_KDVERBUND_IDFNR 10 + 1
#define LS_KDVERBUND_NAMEAPO 40 + 1
#define LS_KDVERBUND_STRASSE 30 + 1
#define LS_KDVERBUND_POSTLEITZAHL 10 + 1
#define LS_KDVERBUND_ORT 30 + 1
#define LS_KDVERBUND_TELNR 20 + 1
#define LS_KDVERBUND_TELNRDAFUE 20 + 1
#define LS_KDVERBUND_FAXNR 25 + 1
#define LS_KDVERBUND_ANREDEKZ 5 + 1
#define LS_KDVERBUND_KDGRUPPE 2 + 1
#define LS_KDVERBUND_PERSONALNRVERTR 10 + 1
#define LS_KDVERBUND_IMSBEZIRKNR 10 + 1
#define LS_KDVERBUND_NAMEINHABER 30 + 1
#define LS_KDVERBUND_TOURID 6 + 1
#define LS_KDVERBUND_KUNDETEXT 240 + 1
#define LS_KDVERBUND_BEMERKUNGEN 240 + 1
#define LS_KDVERBUND_DATUM 10 + 1
#define LS_KDVERBUND_UHRZEIT 10 + 1
#define LS_KDVERBUND_FILIALNR 5 + 1
#define LS_KDVERBUND_LAGRECHTOUR 10 + 1
#define LS_KDVERBUND_BGANR 10 + 1
#define LS_KDVERBUND_SBAAUFTRAG 1 + 1
#define LS_KDVERBUND_WEEKDAY 5 + 1
#define LS_KDVERBUND_KZSPRACHE 2 + 1
#define LS_KDVERBUND_SKDVERSANDAPO 1 + 1
#define LS_KDVERBUND_PAYMENT_TERM 4 + 1
#define LS_KDVERBUND_IBTTYPE 5 + 1

#define KDVERBUNDHERKUNFTFILIALE 0
#define KDVERBUNDKDAUFTRAGNR 1
#define KDVERBUNDVBSTATUS 2
#define KDVERBUNDKDAUFTRAGART 3
#define KDVERBUNDKOART 4
#define KDVERBUNDBUCHART 5
#define KDVERBUNDIDFNR 6
#define KDVERBUNDNAMEAPO 7
#define KDVERBUNDSTRASSE 8
#define KDVERBUNDPOSTLEITZAHL 9
#define KDVERBUNDORT 10
#define KDVERBUNDTELNR 11
#define KDVERBUNDTELNRDAFUE 12
#define KDVERBUNDFAXNR 13
#define KDVERBUNDANREDEKZ 14
#define KDVERBUNDKDGRUPPE 15
#define KDVERBUNDPERSONALNRVERTR 16
#define KDVERBUNDIMSBEZIRKNR 17
#define KDVERBUNDNAMEINHABER 18
#define KDVERBUNDTOURID 19
#define KDVERBUNDKUNDETEXT 20
#define KDVERBUNDBEMERKUNGEN 21
#define KDVERBUNDDATUM 22
#define KDVERBUNDUHRZEIT 23
#define KDVERBUNDFILIALNR 24
#define KDVERBUNDLAGRECHTOUR 25
#define KDVERBUNDBGANR 26
#define KDVERBUNDSBAAUFTRAG 27
#define KDVERBUNDWEEKDAY 28
#define KDVERBUNDKZSPRACHE 29
#define KDVERBUNDSKDVERSANDAPO 30
#define KDVERBUNDPAYMENT_TERM 31
#define KDVERBUNDIBTTYPE 32

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define KDVERBUND_H
#define KDVERBUND_ANZ ( sizeof(KDVERBUND_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of KDVERBUND *****************************************************/

#define KDVERBUND_LISTE \
        KDVERBUND.HERKUNFTFILIALE,\
        KDVERBUND.KDAUFTRAGNR,\
        KDVERBUND.VBSTATUS,\
        KDVERBUND.KDAUFTRAGART,\
        KDVERBUND.KOART,\
        KDVERBUND.BUCHART,\
        KDVERBUND.IDFNR,\
        KDVERBUND.NAMEAPO,\
        KDVERBUND.STRASSE,\
        KDVERBUND.POSTLEITZAHL,\
        KDVERBUND.ORT,\
        KDVERBUND.TELNR,\
        KDVERBUND.TELNRDAFUE,\
        KDVERBUND.FAXNR,\
        KDVERBUND.ANREDEKZ,\
        KDVERBUND.KDGRUPPE,\
        KDVERBUND.PERSONALNRVERTR,\
        KDVERBUND.IMSBEZIRKNR,\
        KDVERBUND.NAMEINHABER,\
        KDVERBUND.TOURID,\
        KDVERBUND.KUNDETEXT,\
        KDVERBUND.BEMERKUNGEN,\
        KDVERBUND.DATUM,\
        KDVERBUND.UHRZEIT,\
        KDVERBUND.FILIALNR,\
        KDVERBUND.LAGRECHTOUR,\
        KDVERBUND.BGANR,\
        KDVERBUND.SBAAUFTRAG,\
        KDVERBUND.WEEKDAY,\
        KDVERBUND.KZSPRACHE,\
        KDVERBUND.SKDVERSANDAPO,\
        KDVERBUND.PAYMENT_TERM,\
        KDVERBUND.IBTTYPE
#define KDVERBUND_LISTE_390 \
        HERKUNFTFILIALE,\
        KDAUFTRAGNR,\
        VBSTATUS,\
        KDAUFTRAGART,\
        KOART,\
        BUCHART,\
        IDFNR,\
        NAMEAPO,\
        STRASSE,\
        POSTLEITZAHL,\
        ORT,\
        TELNR,\
        TELNRDAFUE,\
        FAXNR,\
        ANREDEKZ,\
        KDGRUPPE,\
        PERSONALNRVERTR,\
        IMSBEZIRKNR,\
        NAMEINHABER,\
        TOURID,\
        KUNDETEXT,\
        BEMERKUNGEN,\
        DATUM,\
        UHRZEIT,\
        FILIALNR,\
        LAGRECHTOUR,\
        BGANR,\
        SBAAUFTRAG,\
        WEEKDAY,\
        KZSPRACHE,\
        SKDVERSANDAPO,\
        PAYMENT_TERM,\
        IBTTYPE
#define KDVERBUND_PLISTE \
        "KDVERBUND.HERKUNFTFILIALE,"\
        "KDVERBUND.KDAUFTRAGNR,"\
        "KDVERBUND.VBSTATUS,"\
        "KDVERBUND.KDAUFTRAGART,"\
        "KDVERBUND.KOART,"\
        "KDVERBUND.BUCHART,"\
        "KDVERBUND.IDFNR,"\
        "KDVERBUND.NAMEAPO,"\
        "KDVERBUND.STRASSE,"\
        "KDVERBUND.POSTLEITZAHL,"\
        "KDVERBUND.ORT,"\
        "KDVERBUND.TELNR,"\
        "KDVERBUND.TELNRDAFUE,"\
        "KDVERBUND.FAXNR,"\
        "KDVERBUND.ANREDEKZ,"\
        "KDVERBUND.KDGRUPPE,"\
        "KDVERBUND.PERSONALNRVERTR,"\
        "KDVERBUND.IMSBEZIRKNR,"\
        "KDVERBUND.NAMEINHABER,"\
        "KDVERBUND.TOURID,"\
        "KDVERBUND.KUNDETEXT,"\
        "KDVERBUND.BEMERKUNGEN,"\
        "KDVERBUND.DATUM,"\
        "KDVERBUND.UHRZEIT,"\
        "KDVERBUND.FILIALNR,"\
        "KDVERBUND.LAGRECHTOUR,"\
        "KDVERBUND.BGANR,"\
        "KDVERBUND.SBAAUFTRAG,"\
        "KDVERBUND.WEEKDAY,"\
        "KDVERBUND.KZSPRACHE,"\
        "KDVERBUND.SKDVERSANDAPO,"\
        "KDVERBUND.PAYMENT_TERM,"\
        "KDVERBUND.IBTTYPE"
#define KDVERBUND_PELISTE \
        "HERKUNFTFILIALE,"\
        "KDAUFTRAGNR,"\
        "VBSTATUS,"\
        "KDAUFTRAGART,"\
        "KOART,"\
        "BUCHART,"\
        "IDFNR,"\
        "NAMEAPO,"\
        "STRASSE,"\
        "POSTLEITZAHL,"\
        "ORT,"\
        "TELNR,"\
        "TELNRDAFUE,"\
        "FAXNR,"\
        "ANREDEKZ,"\
        "KDGRUPPE,"\
        "PERSONALNRVERTR,"\
        "IMSBEZIRKNR,"\
        "NAMEINHABER,"\
        "TOURID,"\
        "KUNDETEXT,"\
        "BEMERKUNGEN,"\
        "DATUM,"\
        "UHRZEIT,"\
        "FILIALNR,"\
        "LAGRECHTOUR,"\
        "BGANR,"\
        "SBAAUFTRAG,"\
        "WEEKDAY,"\
        "KZSPRACHE,"\
        "SKDVERSANDAPO,"\
        "PAYMENT_TERM,"\
        "IBTTYPE"
#define KDVERBUND_UPDLISTE \
        "HERKUNFTFILIALE=?,"\
        "KDAUFTRAGNR=?,"\
        "VBSTATUS=?,"\
        "KDAUFTRAGART=?,"\
        "KOART=?,"\
        "BUCHART=?,"\
        "IDFNR=?,"\
        "NAMEAPO=?,"\
        "STRASSE=?,"\
        "POSTLEITZAHL=?,"\
        "ORT=?,"\
        "TELNR=?,"\
        "TELNRDAFUE=?,"\
        "FAXNR=?,"\
        "ANREDEKZ=?,"\
        "KDGRUPPE=?,"\
        "PERSONALNRVERTR=?,"\
        "IMSBEZIRKNR=?,"\
        "NAMEINHABER=?,"\
        "TOURID=?,"\
        "KUNDETEXT=?,"\
        "BEMERKUNGEN=?,"\
        "DATUM=?,"\
        "UHRZEIT=?,"\
        "FILIALNR=?,"\
        "LAGRECHTOUR=?,"\
        "BGANR=?,"\
        "SBAAUFTRAG=?,"\
        "WEEKDAY=?,"\
        "KZSPRACHE=?,"\
        "SKDVERSANDAPO=?,"\
        "PAYMENT_TERM=?,"\
        "IBTTYPE=?"
/* SqlMacros-Define of KDVERBUND **********************************************/

#define KDVERBUND_ZEIGER(x) \
        :x->HERKUNFTFILIALE,\
        :x->KDAUFTRAGNR,\
        :x->VBSTATUS,\
        :x->KDAUFTRAGART,\
        :x->KOART,\
        :x->BUCHART,\
        :x->IDFNR,\
        :x->NAMEAPO,\
        :x->STRASSE,\
        :x->POSTLEITZAHL,\
        :x->ORT,\
        :x->TELNR,\
        :x->TELNRDAFUE,\
        :x->FAXNR,\
        :x->ANREDEKZ,\
        :x->KDGRUPPE,\
        :x->PERSONALNRVERTR,\
        :x->IMSBEZIRKNR,\
        :x->NAMEINHABER,\
        :x->TOURID,\
        :x->KUNDETEXT,\
        :x->BEMERKUNGEN,\
        :x->DATUM,\
        :x->UHRZEIT,\
        :x->FILIALNR,\
        :x->LAGRECHTOUR,\
        :x->BGANR,\
        :x->SBAAUFTRAG,\
        :x->WEEKDAY,\
        :x->KZSPRACHE,\
        :x->SKDVERSANDAPO,\
        :x->PAYMENT_TERM,\
        :x->IBTTYPE
#define KDVERBUND_ZEIGERSEL(x) \
        :x->HERKUNFTFILIALE,\
        :x->KDAUFTRAGNR,\
        :x->VBSTATUS,\
        :x->KDAUFTRAGART,\
        :x->KOART,\
        :x->BUCHART,\
        :x->IDFNR,\
        :x->NAMEAPO,\
        :x->STRASSE,\
        :x->POSTLEITZAHL,\
        :x->ORT,\
        :x->TELNR,\
        :x->TELNRDAFUE,\
        :x->FAXNR,\
        :x->ANREDEKZ,\
        :x->KDGRUPPE,\
        :x->PERSONALNRVERTR,\
        :x->IMSBEZIRKNR,\
        :x->NAMEINHABER,\
        :x->TOURID,\
        :x->KUNDETEXT,\
        :x->BEMERKUNGEN,\
        :x->DATUM,\
        :x->UHRZEIT,\
        :x->FILIALNR,\
        :x->LAGRECHTOUR,\
        :x->BGANR,\
        :x->SBAAUFTRAG,\
        :x->WEEKDAY,\
        :x->KZSPRACHE,\
        :x->SKDVERSANDAPO,\
        :x->PAYMENT_TERM,\
        :x->IBTTYPE
#define KDVERBUND_UPDATE(x) \
        KDVERBUND.HERKUNFTFILIALE=:x->HERKUNFTFILIALE,\
        KDVERBUND.KDAUFTRAGNR=:x->KDAUFTRAGNR,\
        KDVERBUND.VBSTATUS=:x->VBSTATUS,\
        KDVERBUND.KDAUFTRAGART=:x->KDAUFTRAGART,\
        KDVERBUND.KOART=:x->KOART,\
        KDVERBUND.BUCHART=:x->BUCHART,\
        KDVERBUND.IDFNR=:x->IDFNR,\
        KDVERBUND.NAMEAPO=:x->NAMEAPO,\
        KDVERBUND.STRASSE=:x->STRASSE,\
        KDVERBUND.POSTLEITZAHL=:x->POSTLEITZAHL,\
        KDVERBUND.ORT=:x->ORT,\
        KDVERBUND.TELNR=:x->TELNR,\
        KDVERBUND.TELNRDAFUE=:x->TELNRDAFUE,\
        KDVERBUND.FAXNR=:x->FAXNR,\
        KDVERBUND.ANREDEKZ=:x->ANREDEKZ,\
        KDVERBUND.KDGRUPPE=:x->KDGRUPPE,\
        KDVERBUND.PERSONALNRVERTR=:x->PERSONALNRVERTR,\
        KDVERBUND.IMSBEZIRKNR=:x->IMSBEZIRKNR,\
        KDVERBUND.NAMEINHABER=:x->NAMEINHABER,\
        KDVERBUND.TOURID=:x->TOURID,\
        KDVERBUND.KUNDETEXT=:x->KUNDETEXT,\
        KDVERBUND.BEMERKUNGEN=:x->BEMERKUNGEN,\
        KDVERBUND.DATUM=:x->DATUM,\
        KDVERBUND.UHRZEIT=:x->UHRZEIT,\
        KDVERBUND.FILIALNR=:x->FILIALNR,\
        KDVERBUND.LAGRECHTOUR=:x->LAGRECHTOUR,\
        KDVERBUND.BGANR=:x->BGANR,\
        KDVERBUND.SBAAUFTRAG=:x->SBAAUFTRAG,\
        KDVERBUND.WEEKDAY=:x->WEEKDAY,\
        KDVERBUND.KZSPRACHE=:x->KZSPRACHE,\
        KDVERBUND.SKDVERSANDAPO=:x->SKDVERSANDAPO,\
        KDVERBUND.PAYMENT_TERM=:x->PAYMENT_TERM,\
        KDVERBUND.IBTTYPE=:x->IBTTYPE
/* SqlMacros390-Define of KDVERBUND *******************************************/

#define KDVERBUND_ZEIGER_390 \
        :HERKUNFTFILIALE,\
        :KDAUFTRAGNR,\
        :VBSTATUS,\
        :KDAUFTRAGART,\
        :KOART,\
        :BUCHART,\
        :IDFNR,\
        :NAMEAPO,\
        :STRASSE,\
        :POSTLEITZAHL,\
        :ORT,\
        :TELNR,\
        :TELNRDAFUE,\
        :FAXNR,\
        :ANREDEKZ,\
        :KDGRUPPE,\
        :PERSONALNRVERTR,\
        :IMSBEZIRKNR,\
        :NAMEINHABER,\
        :TOURID,\
        :KUNDETEXT,\
        :BEMERKUNGEN,\
        :DATUM,\
        :UHRZEIT,\
        :FILIALNR,\
        :LAGRECHTOUR,\
        :BGANR,\
        :SBAAUFTRAG,\
        :WEEKDAY,\
        :KZSPRACHE,\
        :SKDVERSANDAPO,\
        :PAYMENT_TERM,\
        :IBTTYPE
#define KDVERBUND_UPDATE_390 \
        HERKUNFTFILIALE=:HERKUNFTFILIALE,\
        KDAUFTRAGNR=:KDAUFTRAGNR,\
        VBSTATUS=:VBSTATUS,\
        KDAUFTRAGART=:KDAUFTRAGART,\
        KOART=:KOART,\
        BUCHART=:BUCHART,\
        IDFNR=:IDFNR,\
        NAMEAPO=:NAMEAPO,\
        STRASSE=:STRASSE,\
        POSTLEITZAHL=:POSTLEITZAHL,\
        ORT=:ORT,\
        TELNR=:TELNR,\
        TELNRDAFUE=:TELNRDAFUE,\
        FAXNR=:FAXNR,\
        ANREDEKZ=:ANREDEKZ,\
        KDGRUPPE=:KDGRUPPE,\
        PERSONALNRVERTR=:PERSONALNRVERTR,\
        IMSBEZIRKNR=:IMSBEZIRKNR,\
        NAMEINHABER=:NAMEINHABER,\
        TOURID=:TOURID,\
        KUNDETEXT=:KUNDETEXT,\
        BEMERKUNGEN=:BEMERKUNGEN,\
        DATUM=:DATUM,\
        UHRZEIT=:UHRZEIT,\
        FILIALNR=:FILIALNR,\
        LAGRECHTOUR=:LAGRECHTOUR,\
        BGANR=:BGANR,\
        SBAAUFTRAG=:SBAAUFTRAG,\
        WEEKDAY=:WEEKDAY,\
        KZSPRACHE=:KZSPRACHE,\
        SKDVERSANDAPO=:SKDVERSANDAPO,\
        PAYMENT_TERM=:PAYMENT_TERM,\
        IBTTYPE=:IBTTYPE
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of KDVERBUND ***********************************************/

#ifndef TRANSCLASS
typedef struct N_KDVERBUND {
    short HERKUNFTFILIALE;
    long KDAUFTRAGNR;
    char VBSTATUS[2];
    char KDAUFTRAGART[3];
    char KOART[2];
    char BUCHART[2];
    long IDFNR;
    char NAMEAPO[41];
    char STRASSE[31];
    char POSTLEITZAHL[11];
    char ORT[31];
    char TELNR[21];
    char TELNRDAFUE[21];
    char FAXNR[26];
    short ANREDEKZ;
    char KDGRUPPE[3];
    long PERSONALNRVERTR;
    long IMSBEZIRKNR;
    char NAMEINHABER[31];
    char TOURID[7];
    char KUNDETEXT[241];
    char BEMERKUNGEN[241];
    long DATUM;
    long UHRZEIT;
    short FILIALNR;
    long LAGRECHTOUR;
    long BGANR;
    char SBAAUFTRAG[2];
    short WEEKDAY;
    char KZSPRACHE[3];
    char SKDVERSANDAPO[2];
    char PAYMENT_TERM[5];
    short IBTTYPE;
} kdverbundS;
#else /* TRANSCLASS */
typedef struct N_KDVERBUND {
    short HERKUNFTFILIALE;
    long KDAUFTRAGNR;
    char VBSTATUS[2];
    char KDAUFTRAGART[3];
    char KOART[2];
    char BUCHART[2];
    long IDFNR;
    char NAMEAPO[41];
    char STRASSE[31];
    char POSTLEITZAHL[11];
    char ORT[31];
    char TELNR[21];
    char TELNRDAFUE[21];
    char FAXNR[26];
    short ANREDEKZ;
    char KDGRUPPE[3];
    long PERSONALNRVERTR;
    long IMSBEZIRKNR;
    char NAMEINHABER[31];
    char TOURID[7];
    char KUNDETEXT[241];
    char BEMERKUNGEN[241];
    long DATUM;
    long UHRZEIT;
    short FILIALNR;
    long LAGRECHTOUR;
    long BGANR;
    char SBAAUFTRAG[2];
    short WEEKDAY;
    char KZSPRACHE[3];
    char SKDVERSANDAPO[2];
    char PAYMENT_TERM[5];
    short IBTTYPE;

    bool operator == (const N_KDVERBUND& right) const {
        return (
            HERKUNFTFILIALE == right.HERKUNFTFILIALE &&
            KDAUFTRAGNR == right.KDAUFTRAGNR &&
            !strcmp(VBSTATUS, right.VBSTATUS) &&
            !strcmp(KDAUFTRAGART, right.KDAUFTRAGART) &&
            !strcmp(KOART, right.KOART) &&
            !strcmp(BUCHART, right.BUCHART) &&
            IDFNR == right.IDFNR &&
            !strcmp(NAMEAPO, right.NAMEAPO) &&
            !strcmp(STRASSE, right.STRASSE) &&
            !strcmp(POSTLEITZAHL, right.POSTLEITZAHL) &&
            !strcmp(ORT, right.ORT) &&
            !strcmp(TELNR, right.TELNR) &&
            !strcmp(TELNRDAFUE, right.TELNRDAFUE) &&
            !strcmp(FAXNR, right.FAXNR) &&
            ANREDEKZ == right.ANREDEKZ &&
            !strcmp(KDGRUPPE, right.KDGRUPPE) &&
            PERSONALNRVERTR == right.PERSONALNRVERTR &&
            IMSBEZIRKNR == right.IMSBEZIRKNR &&
            !strcmp(NAMEINHABER, right.NAMEINHABER) &&
            !strcmp(TOURID, right.TOURID) &&
            !strcmp(KUNDETEXT, right.KUNDETEXT) &&
            !strcmp(BEMERKUNGEN, right.BEMERKUNGEN) &&
            DATUM == right.DATUM &&
            UHRZEIT == right.UHRZEIT &&
            FILIALNR == right.FILIALNR &&
            LAGRECHTOUR == right.LAGRECHTOUR &&
            BGANR == right.BGANR &&
            !strcmp(SBAAUFTRAG, right.SBAAUFTRAG) &&
            WEEKDAY == right.WEEKDAY &&
            !strcmp(KZSPRACHE, right.KZSPRACHE) &&
            !strcmp(SKDVERSANDAPO, right.SKDVERSANDAPO) &&
            !strcmp(PAYMENT_TERM, right.PAYMENT_TERM) &&
            IBTTYPE == right.IBTTYPE
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        HERKUNFTFILIALE = 0;
        KDAUFTRAGNR = 0;
        strcpy(VBSTATUS, " " );
        strcpy(KDAUFTRAGART, " " );
        strcpy(KOART, " " );
        strcpy(BUCHART, " " );
        IDFNR = 0;
        strcpy(NAMEAPO, " " );
        strcpy(STRASSE, " " );
        strcpy(POSTLEITZAHL, " " );
        strcpy(ORT, " " );
        strcpy(TELNR, " " );
        strcpy(TELNRDAFUE, " " );
        strcpy(FAXNR, " " );
        ANREDEKZ = 0;
        strcpy(KDGRUPPE, " " );
        PERSONALNRVERTR = 0;
        IMSBEZIRKNR = 0;
        strcpy(NAMEINHABER, " " );
        strcpy(TOURID, " " );
        strcpy(KUNDETEXT, " " );
        strcpy(BEMERKUNGEN, " " );
        DATUM = 0;
        UHRZEIT = 0;
        FILIALNR = 0;
        LAGRECHTOUR = 0;
        BGANR = 0;
        strcpy(SBAAUFTRAG, " " );
        WEEKDAY = 0;
        strcpy(KZSPRACHE, " " );
        strcpy(SKDVERSANDAPO, " " );
        strcpy(PAYMENT_TERM, " " );
        IBTTYPE = 0;
#endif
    }
} kdverbundS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of KDVERBUND *****************************************/

struct S_KDVERBUND {
    char HERKUNFTFILIALE[7];
    char KDAUFTRAGNR[11];
    char VBSTATUS[1 + 1];
    char KDAUFTRAGART[2 + 1];
    char KOART[1 + 1];
    char BUCHART[1 + 1];
    char IDFNR[11];
    char NAMEAPO[40 + 1];
    char STRASSE[30 + 1];
    char POSTLEITZAHL[10 + 1];
    char ORT[30 + 1];
    char TELNR[20 + 1];
    char TELNRDAFUE[20 + 1];
    char FAXNR[25 + 1];
    char ANREDEKZ[7];
    char KDGRUPPE[2 + 1];
    char PERSONALNRVERTR[11];
    char IMSBEZIRKNR[11];
    char NAMEINHABER[30 + 1];
    char TOURID[6 + 1];
    char KUNDETEXT[240 + 1];
    char BEMERKUNGEN[240 + 1];
    char DATUM[11];
    char UHRZEIT[11];
    char FILIALNR[7];
    char LAGRECHTOUR[11];
    char BGANR[11];
    char SBAAUFTRAG[1 + 1];
    char WEEKDAY[7];
    char KZSPRACHE[2 + 1];
    char SKDVERSANDAPO[1 + 1];
    char PAYMENT_TERM[4 + 1];
    char IBTTYPE[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of KDVERBUND ************************/

struct O_KDVERBUND {
    char HERKUNFTFILIALE[7];
    char KDAUFTRAGNR[11];
    char VBSTATUS[1];
    char KDAUFTRAGART[2];
    char KOART[1];
    char BUCHART[1];
    char IDFNR[11];
    char NAMEAPO[40];
    char STRASSE[30];
    char POSTLEITZAHL[10];
    char ORT[30];
    char TELNR[20];
    char TELNRDAFUE[20];
    char FAXNR[25];
    char ANREDEKZ[7];
    char KDGRUPPE[2];
    char PERSONALNRVERTR[11];
    char IMSBEZIRKNR[11];
    char NAMEINHABER[30];
    char TOURID[6];
    char KUNDETEXT[240];
    char BEMERKUNGEN[240];
    char DATUM[11];
    char UHRZEIT[11];
    char FILIALNR[7];
    char LAGRECHTOUR[11];
    char BGANR[11];
    char SBAAUFTRAG[1];
    char WEEKDAY[7];
    char KZSPRACHE[2];
    char SKDVERSANDAPO[1];
    char PAYMENT_TERM[4];
    char IBTTYPE[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of KDVERBUND ***********************************/

struct C_KDVERBUND {
    short HERKUNFTFILIALE;
    long KDAUFTRAGNR;
    char VBSTATUS;
    char KDAUFTRAGART[3];
    char KOART;
    char BUCHART;
    long IDFNR;
    char NAMEAPO[41];
    char STRASSE[31];
    char POSTLEITZAHL[11];
    char ORT[31];
    char TELNR[21];
    char TELNRDAFUE[21];
    char FAXNR[26];
    short ANREDEKZ;
    char KDGRUPPE[3];
    long PERSONALNRVERTR;
    long IMSBEZIRKNR;
    char NAMEINHABER[31];
    char TOURID[7];
    char KUNDETEXT[241];
    char BEMERKUNGEN[241];
    long DATUM;
    long UHRZEIT;
    short FILIALNR;
    long LAGRECHTOUR;
    long BGANR;
    char SBAAUFTRAG;
    short WEEKDAY;
    char KZSPRACHE[3];
    char SKDVERSANDAPO;
    char PAYMENT_TERM[5];
    short IBTTYPE;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of KDVERBUND *********************************/

struct I_KDVERBUND {
    short HERKUNFTFILIALE;
    short KDAUFTRAGNR;
    short VBSTATUS;
    short KDAUFTRAGART;
    short KOART;
    short BUCHART;
    short IDFNR;
    short NAMEAPO;
    short STRASSE;
    short POSTLEITZAHL;
    short ORT;
    short TELNR;
    short TELNRDAFUE;
    short FAXNR;
    short ANREDEKZ;
    short KDGRUPPE;
    short PERSONALNRVERTR;
    short IMSBEZIRKNR;
    short NAMEINHABER;
    short TOURID;
    short KUNDETEXT;
    short BEMERKUNGEN;
    short DATUM;
    short UHRZEIT;
    short FILIALNR;
    short LAGRECHTOUR;
    short BGANR;
    short SBAAUFTRAG;
    short WEEKDAY;
    short KZSPRACHE;
    short SKDVERSANDAPO;
    short PAYMENT_TERM;
    short IBTTYPE;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of KDVERBUND *******************************************/

#if defined (BUF_DESC)
static struct buf_desc KDVERBUND_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 40, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 10, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 20, 0 },
   { TYP_C, 20, 0 },
   { TYP_C, 25, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 2, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 240, 0 },
   { TYP_C, 240, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 4, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc KDVERBUND_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 40, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 10, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 20, 0 },
   { TYP_C, 20, 0 },
   { TYP_C, 25, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 2, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 240, 0 },
   { TYP_C, 240, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 4, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* description for datatypes of KDVERBUND *************************************/

 #define KDVERBUND_S390 \
         short HERKUNFTFILIALE; \
         long KDAUFTRAGNR; \
         char VBSTATUS; \
         char KDAUFTRAGART[3]; \
         char KOART; \
         char BUCHART; \
         long IDFNR; \
         char NAMEAPO[41]; \
         char STRASSE[31]; \
         char POSTLEITZAHL[11]; \
         char ORT[31]; \
         char TELNR[21]; \
         char TELNRDAFUE[21]; \
         char FAXNR[26]; \
         short ANREDEKZ; \
         char KDGRUPPE[3]; \
         long PERSONALNRVERTR; \
         long IMSBEZIRKNR; \
         char NAMEINHABER[31]; \
         char TOURID[7]; \
         char KUNDETEXT[241]; \
         char BEMERKUNGEN[241]; \
         long DATUM; \
         long UHRZEIT; \
         short FILIALNR; \
         long LAGRECHTOUR; \
         long BGANR; \
         char SBAAUFTRAG; \
         short WEEKDAY; \
         char KZSPRACHE[3]; \
         char SKDVERSANDAPO; \
         char PAYMENT_TERM[5]; \
         short IBTTYPE; \



/* Copy-Function Struct to single Data KDVERBUND ******************************/

 #define KDVERBUND_S390_COPY_TO_SINGLE(_x_) \
         HERKUNFTFILIALE=_x_->HERKUNFTFILIALE;\
         KDAUFTRAGNR=_x_->KDAUFTRAGNR;\
         VBSTATUS=_x_->VBSTATUS;\
          strcpy(KDAUFTRAGART,_x_->KDAUFTRAGART);\
         KOART=_x_->KOART;\
         BUCHART=_x_->BUCHART;\
         IDFNR=_x_->IDFNR;\
          strcpy(NAMEAPO,_x_->NAMEAPO);\
          strcpy(STRASSE,_x_->STRASSE);\
          strcpy(POSTLEITZAHL,_x_->POSTLEITZAHL);\
          strcpy(ORT,_x_->ORT);\
          strcpy(TELNR,_x_->TELNR);\
          strcpy(TELNRDAFUE,_x_->TELNRDAFUE);\
          strcpy(FAXNR,_x_->FAXNR);\
         ANREDEKZ=_x_->ANREDEKZ;\
          strcpy(KDGRUPPE,_x_->KDGRUPPE);\
         PERSONALNRVERTR=_x_->PERSONALNRVERTR;\
         IMSBEZIRKNR=_x_->IMSBEZIRKNR;\
          strcpy(NAMEINHABER,_x_->NAMEINHABER);\
          strcpy(TOURID,_x_->TOURID);\
          strcpy(KUNDETEXT,_x_->KUNDETEXT);\
          strcpy(BEMERKUNGEN,_x_->BEMERKUNGEN);\
         DATUM=_x_->DATUM;\
         UHRZEIT=_x_->UHRZEIT;\
         FILIALNR=_x_->FILIALNR;\
         LAGRECHTOUR=_x_->LAGRECHTOUR;\
         BGANR=_x_->BGANR;\
         SBAAUFTRAG=_x_->SBAAUFTRAG;\
         WEEKDAY=_x_->WEEKDAY;\
          strcpy(KZSPRACHE,_x_->KZSPRACHE);\
         SKDVERSANDAPO=_x_->SKDVERSANDAPO;\
          strcpy(PAYMENT_TERM,_x_->PAYMENT_TERM);\
         IBTTYPE=_x_->IBTTYPE;\

 #define KDVERBUND_S390_COPY_TO_STRUCT(_x_) \
          _x_->HERKUNFTFILIALE=HERKUNFTFILIALE;\
          _x_->KDAUFTRAGNR=KDAUFTRAGNR;\
          _x_->VBSTATUS=VBSTATUS;\
          strcpy(_x_->KDAUFTRAGART,KDAUFTRAGART);\
          _x_->KOART=KOART;\
          _x_->BUCHART=BUCHART;\
          _x_->IDFNR=IDFNR;\
          strcpy(_x_->NAMEAPO,NAMEAPO);\
          strcpy(_x_->STRASSE,STRASSE);\
          strcpy(_x_->POSTLEITZAHL,POSTLEITZAHL);\
          strcpy(_x_->ORT,ORT);\
          strcpy(_x_->TELNR,TELNR);\
          strcpy(_x_->TELNRDAFUE,TELNRDAFUE);\
          strcpy(_x_->FAXNR,FAXNR);\
          _x_->ANREDEKZ=ANREDEKZ;\
          strcpy(_x_->KDGRUPPE,KDGRUPPE);\
          _x_->PERSONALNRVERTR=PERSONALNRVERTR;\
          _x_->IMSBEZIRKNR=IMSBEZIRKNR;\
          strcpy(_x_->NAMEINHABER,NAMEINHABER);\
          strcpy(_x_->TOURID,TOURID);\
          strcpy(_x_->KUNDETEXT,KUNDETEXT);\
          strcpy(_x_->BEMERKUNGEN,BEMERKUNGEN);\
          _x_->DATUM=DATUM;\
          _x_->UHRZEIT=UHRZEIT;\
          _x_->FILIALNR=FILIALNR;\
          _x_->LAGRECHTOUR=LAGRECHTOUR;\
          _x_->BGANR=BGANR;\
          _x_->SBAAUFTRAG=SBAAUFTRAG;\
          _x_->WEEKDAY=WEEKDAY;\
          strcpy(_x_->KZSPRACHE,KZSPRACHE);\
          _x_->SKDVERSANDAPO=SKDVERSANDAPO;\
          strcpy(_x_->PAYMENT_TERM,PAYMENT_TERM);\
          _x_->IBTTYPE=IBTTYPE;\



/* FunctionNumber-Define of kdverbund *****************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of kdverbund *************************************/


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

class CKDVERBUND : public ppDadeVirtual {
public:
    kdverbundS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<kdverbundS> lst; // class list

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
                     vector< kdverbundS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     kdverbundS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< kdverbundS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<kdverbundS>::iterator
                 beginList() { return lst.begin(); }
    vector<kdverbundS>::iterator
                 endList  () { return lst.end  (); }

    short        GetHerkunftfiliale() const { return s.HERKUNFTFILIALE; }
    long         GetKdauftragnr() const { return s.KDAUFTRAGNR; }
    char         GetVbstatus() const { return s.VBSTATUS[0]; }
    const char*  GetKdauftragart(ppString & t) const { t = s.KDAUFTRAGART; t.erasespace(ppString::END); return t.c_str(); }
    char         GetKoart() const { return s.KOART[0]; }
    char         GetBuchart() const { return s.BUCHART[0]; }
    long         GetIdfnr() const { return s.IDFNR; }
    const char*  GetNameapo(ppString & t) const { t = s.NAMEAPO; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetStrasse(ppString & t) const { t = s.STRASSE; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetPostleitzahl(ppString & t) const { t = s.POSTLEITZAHL; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetOrt(ppString & t) const { t = s.ORT; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetTelnr(ppString & t) const { t = s.TELNR; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetTelnrdafue(ppString & t) const { t = s.TELNRDAFUE; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetFaxnr(ppString & t) const { t = s.FAXNR; t.erasespace(ppString::END); return t.c_str(); }
    short        GetAnredekz() const { return s.ANREDEKZ; }
    const char*  GetKdgruppe(ppString & t) const { t = s.KDGRUPPE; t.erasespace(ppString::END); return t.c_str(); }
    long         GetPersonalnrvertr() const { return s.PERSONALNRVERTR; }
    long         GetImsbezirknr() const { return s.IMSBEZIRKNR; }
    const char*  GetNameinhaber(ppString & t) const { t = s.NAMEINHABER; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetTourid(ppString & t) const { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetKundetext(ppString & t) const { t = s.KUNDETEXT; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetBemerkungen(ppString & t) const { t = s.BEMERKUNGEN; t.erasespace(ppString::END); return t.c_str(); }
    long         GetDatum() const { return s.DATUM; }
    long         GetUhrzeit() const { return s.UHRZEIT; }
    short        GetFilialnr() const { return s.FILIALNR; }
    long         GetLagrechtour() const { return s.LAGRECHTOUR; }
    long         GetBganr() const { return s.BGANR; }
    char         GetSbaauftrag() const { return s.SBAAUFTRAG[0]; }
    short        GetWeekday() const { return s.WEEKDAY; }
    const char*  GetKzsprache(ppString & t) const { t = s.KZSPRACHE; t.erasespace(ppString::END); return t.c_str(); }
    char         GetSkdversandapo() const { return s.SKDVERSANDAPO[0]; }
    const char*  GetPayment_term(ppString & t) const { t = s.PAYMENT_TERM; t.erasespace(ppString::END); return t.c_str(); }
    short        GetIbttype() const { return s.IBTTYPE; }

    const kdverbundS &
                 GetStruct() const { return s; }
    void         SetHerkunftfiliale(short t) { s.HERKUNFTFILIALE = t; }
    void         SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
    void         SetVbstatus(char t) { s.VBSTATUS[0] = t; s.VBSTATUS[1] = '\0';}
    void         SetKdauftragart(const ppString & t) { ppGStrCopy(s.KDAUFTRAGART, t.c_str(), L_KDVERBUND_KDAUFTRAGART); }
    void         SetKoart(char t) { s.KOART[0] = t; s.KOART[1] = '\0';}
    void         SetBuchart(char t) { s.BUCHART[0] = t; s.BUCHART[1] = '\0';}
    void         SetIdfnr(long t) { s.IDFNR = t; }
    void         SetNameapo(const ppString & t) { ppGStrCopy(s.NAMEAPO, t.c_str(), L_KDVERBUND_NAMEAPO); }
    void         SetStrasse(const ppString & t) { ppGStrCopy(s.STRASSE, t.c_str(), L_KDVERBUND_STRASSE); }
    void         SetPostleitzahl(const ppString & t) { ppGStrCopy(s.POSTLEITZAHL, t.c_str(), L_KDVERBUND_POSTLEITZAHL); }
    void         SetOrt(const ppString & t) { ppGStrCopy(s.ORT, t.c_str(), L_KDVERBUND_ORT); }
    void         SetTelnr(const ppString & t) { ppGStrCopy(s.TELNR, t.c_str(), L_KDVERBUND_TELNR); }
    void         SetTelnrdafue(const ppString & t) { ppGStrCopy(s.TELNRDAFUE, t.c_str(), L_KDVERBUND_TELNRDAFUE); }
    void         SetFaxnr(const ppString & t) { ppGStrCopy(s.FAXNR, t.c_str(), L_KDVERBUND_FAXNR); }
    void         SetAnredekz(short t) { s.ANREDEKZ = t; }
    void         SetKdgruppe(const ppString & t) { ppGStrCopy(s.KDGRUPPE, t.c_str(), L_KDVERBUND_KDGRUPPE); }
    void         SetPersonalnrvertr(long t) { s.PERSONALNRVERTR = t; }
    void         SetImsbezirknr(long t) { s.IMSBEZIRKNR = t; }
    void         SetNameinhaber(const ppString & t) { ppGStrCopy(s.NAMEINHABER, t.c_str(), L_KDVERBUND_NAMEINHABER); }
    void         SetTourid(const ppString & t) { ppGStrCopy(s.TOURID, t.c_str(), L_KDVERBUND_TOURID); }
    void         SetKundetext(const ppString & t) { ppGStrCopy(s.KUNDETEXT, t.c_str(), L_KDVERBUND_KUNDETEXT); }
    void         SetBemerkungen(const ppString & t) { ppGStrCopy(s.BEMERKUNGEN, t.c_str(), L_KDVERBUND_BEMERKUNGEN); }
    void         SetDatum(long t) { s.DATUM = t; }
    void         SetUhrzeit(long t) { s.UHRZEIT = t; }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetLagrechtour(long t) { s.LAGRECHTOUR = t; }
    void         SetBganr(long t) { s.BGANR = t; }
    void         SetSbaauftrag(char t) { s.SBAAUFTRAG[0] = t; s.SBAAUFTRAG[1] = '\0';}
    void         SetWeekday(short t) { s.WEEKDAY = t; }
    void         SetKzsprache(const ppString & t) { ppGStrCopy(s.KZSPRACHE, t.c_str(), L_KDVERBUND_KZSPRACHE); }
    void         SetSkdversandapo(char t) { s.SKDVERSANDAPO[0] = t; s.SKDVERSANDAPO[1] = '\0';}
    void         SetPayment_term(const ppString & t) { ppGStrCopy(s.PAYMENT_TERM, t.c_str(), L_KDVERBUND_PAYMENT_TERM); }
    void         SetIbttype(short t) { s.IBTTYPE = t; }

    void         SetStruct(const kdverbundS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CKDVERBUND() {
        ::buf_default((void *)&s, KDVERBUND_BES, KDVERBUND_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CKDVERBUND() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, KDVERBUND_BES, KDVERBUND_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, KDVERBUND_BES, (int)KDVERBUND_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, KDVERBUND_BES, (int)KDVERBUND_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_KDVERBUND & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.KDAUFTRAGART);
        ppGStripLast(d.NAMEAPO);
        ppGStripLast(d.STRASSE);
        ppGStripLast(d.POSTLEITZAHL);
        ppGStripLast(d.ORT);
        ppGStripLast(d.TELNR);
        ppGStripLast(d.TELNRDAFUE);
        ppGStripLast(d.FAXNR);
        ppGStripLast(d.KDGRUPPE);
        ppGStripLast(d.NAMEINHABER);
        ppGStripLast(d.TOURID);
        ppGStripLast(d.KUNDETEXT);
        ppGStripLast(d.BEMERKUNGEN);
        ppGStripLast(d.KZSPRACHE);
        ppGStripLast(d.PAYMENT_TERM);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, KDVERBUND_BES, (int)KDVERBUND_ANZ, error_msg);
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
/* CreateSqlStatement of KDVERBUND ********************************************/

 #define KDVERBUND_CREATE(x) EXEC SQL create table x (\
         HERKUNFTFILIALE smallint default 0 not null,\
         KDAUFTRAGNR integer default 0 not null,\
         VBSTATUS char(1) default " " not null,\
         KDAUFTRAGART char(2) default " " not null,\
         KOART char(1) default " " not null,\
         BUCHART char(1) default " " not null,\
         IDFNR integer default 0 not null,\
         NAMEAPO char(40) default " " not null,\
         STRASSE char(30) default " " not null,\
         POSTLEITZAHL char(10) default " " not null,\
         ORT char(30) default " " not null,\
         TELNR char(20) default " " not null,\
         TELNRDAFUE char(20) default " " not null,\
         FAXNR char(25) default " " not null,\
         ANREDEKZ smallint default 0 not null,\
         KDGRUPPE char(2) default " " not null,\
         PERSONALNRVERTR integer default 0 not null,\
         IMSBEZIRKNR integer default 0 not null,\
         NAMEINHABER char(30) default " " not null,\
         TOURID char(6) default " " not null,\
         KUNDETEXT varchar(240,0) default " " not null,\
         BEMERKUNGEN varchar(240,0) default " " not null,\
         DATUM integer default 0 not null,\
         UHRZEIT integer default 0 not null,\
         FILIALNR smallint default 0 not null,\
         LAGRECHTOUR integer default 0 not null,\
         BGANR integer default 0 not null,\
         SBAAUFTRAG char(1) default " " not null,\
         WEEKDAY smallint default 0 not null,\
         KZSPRACHE char(2) default " " not null,\
         SKDVERSANDAPO char(1) default " " not null,\
         PAYMENT_TERM char(4) default " " not null,\
         IBTTYPE smallint default 0 not null) in KscOrder extent size 192 next size 20 lock mode row;



/* CreateIndexStatement of KDVERBUND ******************************************/

 #define KDVERBUND_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_kdverbund_1 on _X_(\
              filialnr,\
              herkunftfiliale,\
              kdauftragnr,\
              ibttype ) in KscOrderIdx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         EXEC SQL create   index i_kdverbund_2 on _X_(\
              vbstatus,\
              filialnr ) in KscOrderIdx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of KDVERBUND ******************************************/

 #define KDVERBUND_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_kdverbund_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         EXEC SQL drop index i_kdverbund_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
